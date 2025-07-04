/**
  **********************************************************************************************************************
  * @file    stm32_utils_i2c.c
  * @brief   This utility help to calculate the I2C, SMBUS Timing and SMBUS Timeout.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_utils_i2c.h"
#include "stdio.h"

/** @addtogroup STM32_UTILS
  * @{
  */

/** @addtogroup I2C
  * @{
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup I2C_Private_Constants I2C Private Constants
  * @{
  */

#define I2C_VALID_TIMING_NBR                   (128U)
#define I2C_SPEED_FREQ_STANDARD                (0U)         /* 100 kHz */
#define I2C_SPEED_FREQ_FAST                    (1U)         /* 400 kHz */
#define I2C_SPEED_FREQ_FAST_PLUS               (2U)         /* 1 MHz */
#define I2C_ANALOG_FILTER_DELAY_MIN            (50U)        /* ns */
#define I2C_ANALOG_FILTER_DELAY_MAX            (260U)       /* ns */
#define I2C_DIGITAL_FILTER_COEF                (0U)
#define I2C_PRESC_MAX                          (16U)
#define I2C_SCLDEL_MAX                         (16U)
#define I2C_SDADEL_MAX                         (16U)
#define I2C_SCLH_MAX                           (256U)
#define I2C_SCLL_MAX                           (256U)
#define SMBUS_IDLE_TIMEOUT_MIN                 (25000000UL) /* ns */
#define SMBUS_IDLE_TIMEOUT_MAX                 (35000000UL) /* ns */
#define SMBUS_SLAVE_EXT_LOW_TIMEOUT_MIN        (0U)         /* ns */
#define SMBUS_SLAVE_EXT_LOW_TIMEOUT_MAX        (25000000UL) /* ns */
#define SMBUS_MASTER_EXT_LOW_TIMEOUT_MIN       (0U)         /* ns */
#define SMBUS_MASTER_EXT_LOW_TIMEOUT_MAX       (10000000UL) /* ns */
#define I2C_SCLH_MAX                           (256U)
#define SEC2NSEC                               (1000000000UL)
#define CENT                                   (100UL)

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup I2C_Private_Macros I2C Private Macros
  * @{
  */

/** @brief  Rounds the given number to the nearest multiple of the divisor.
  * @param  x The number to be rounded.
  * @param  d The divisor used for rounding.
  * @return The rounded number.
 */
#define DIV_ROUND_CLOSEST(x, d)  (((x) + ((d) / 2U)) / (d))

/**
  * @}
  */

/* Private types ------------------------------------------------------------*/
/** @defgroup I2C_Private_Types I2C Private Types
  * @{
  */
typedef struct
{
  uint32_t freq;       /* Frequency in Hz */
  uint32_t freq_min;   /* Minimum frequency in Hz */
  uint32_t freq_max;   /* Maximum frequency in Hz */
  uint32_t hddat_min;  /* Minimum data hold time in ns */
  uint32_t vddat_max;  /* Maximum data valid time in ns */
  uint32_t sudat_min;  /* Minimum data setup time in ns */
  uint32_t lscl_min;   /* Minimum low period of the SCL clock in ns */
  uint32_t hscl_min;   /* Minimum high period of SCL clock in ns */
  uint32_t trise_max;  /* Rise time max in ns */
  uint32_t trise_min;  /* Rise time min in ns */
  uint32_t tfall_max;  /* Fall time in ns */
  uint32_t tfall_min;  /* Fall time in ns */
  uint32_t dnf;        /* Digital noise filter coefficient */
} i2c_charac_t;

typedef struct
{
  uint32_t presc;      /* Timing prescaler */
  uint32_t tscldel;    /* SCL delay */
  uint32_t tsdadel;    /* SDA delay */
  uint32_t sclh;       /* SCL high period */
  uint32_t scll;       /* SCL low period */
} i2c_timings_t;

static const i2c_charac_t I2C_Charac[] =
{
  [I2C_SPEED_FREQ_STANDARD] =
  {
    .freq = 100000,
    .freq_min = 80000,
    .freq_max = 120000,
    .hddat_min = 0,
    .vddat_max = 3450,
    .sudat_min = 250,
    .lscl_min = 4700,
    .hscl_min = 4000,
    .trise_min = 0,
    .trise_max = 1000,
    .tfall_min = 0,
    .tfall_max = 300,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
  [I2C_SPEED_FREQ_FAST] =
  {
    .freq = 400000,
    .freq_min = 320000,
    .freq_max = 480000,
    .hddat_min = 0,
    .vddat_max = 900,
    .sudat_min = 100,
    .lscl_min = 1300,
    .hscl_min = 600,
    .trise_min = 20,   /* 20 + 0.1Cb; cb ignored */
    .trise_max = 300,
    .tfall_min = 20,   /* 20 + 0.1Cb; cb ignored */
    .tfall_max = 300,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
  [I2C_SPEED_FREQ_FAST_PLUS] =
  {
    .freq = 1000000,
    .freq_min = 800000,
    .freq_max = 1200000,
    .hddat_min = 0,
    .vddat_max = 450,
    .sudat_min = 50,
    .lscl_min = 500,
    .hscl_min = 260,
    .trise_min = 0,
    .trise_max = 120,
    .tfall_min = 0,
    .tfall_max = 120,
    .dnf = I2C_DIGITAL_FILTER_COEF,
  },
};

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup I2C_Private_Variables I2C Private variables
  * @{
  */
static i2c_timings_t i2c_valid_timing[I2C_VALID_TIMING_NBR];
static uint32_t      i2c_valid_timing_nbr;
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup I2C_Private_function I2C Private function
  * @{
  */
static uint32_t I2C_Compute_SCLL_SCLH(const stm32_utils_i2c_timing_advanced_config_t *p_config, uint32_t I2C_speed);
static stm32_utils_i2c_status_t I2C_Compute_PRESC_SCLDEL_SDADEL(const stm32_utils_i2c_timing_advanced_config_t
                                                                *p_config,
                                                                uint32_t I2C_speed);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @defgroup I2C_UTILS_Exported_Functions I2C Utility Exported Functions
  * @{
  */

/**
  * @brief  Compute I2C timing according current I2C clock source and required I2C clock.
  * @param  p_config Pointer to a @ref stm32_utils_i2c_timing_basic_config_t structure that contains
  *         the required parameter for I2C timing computation.
  * @param  p_output_timing_reg Pointer to a I2C_TIMINGR register value calculated by referring to I2C
            initialization section in reference Manual.
  * @retval STM32_UTILS_I2C_OK Timing calculation successfully
  * @retval STM32_UTILS_I2C_ERROR Timing calculation error
  */
stm32_utils_i2c_status_t STM32_UTILS_I2C_ComputeTimingBasic(const stm32_utils_i2c_timing_basic_config_t *p_config,
                                                            uint32_t *p_output_timing_reg)
{
  stm32_utils_i2c_status_t status = STM32_UTILS_I2C_ERROR;
  uint32_t speed;
  uint32_t idx;
  stm32_utils_i2c_timing_advanced_config_t p_advanced_config;
  i2c_valid_timing_nbr = 0;

  if ((p_config->clock_src_freq_hz != 0U) && (p_config->i2c_freq_hz != 0U))
  {
    for (speed = 0 ; speed <= (uint32_t)I2C_SPEED_FREQ_FAST_PLUS ; speed++)
    {
      if ((p_config->i2c_freq_hz >= I2C_Charac[speed].freq_min) \
          && (p_config->i2c_freq_hz <= I2C_Charac[speed].freq_max))
      {
        p_advanced_config.clock_src_freq_hz = p_config->clock_src_freq_hz;
        p_advanced_config.i2c_freq_hz = p_config->i2c_freq_hz;
        p_advanced_config.trise_ns = I2C_Charac[speed].trise_max / 2;
        p_advanced_config.tfall_ns = I2C_Charac[speed].tfall_max / 2;
        p_advanced_config.dnf   = I2C_Charac[speed].dnf;
        p_advanced_config.af    = STM32_UTILS_I2C_ANALOG_FILTER_ENABLED;

        if (I2C_Compute_PRESC_SCLDEL_SDADEL(&p_advanced_config, speed) != STM32_UTILS_I2C_OK)
        {
          return STM32_UTILS_I2C_ERROR;
        }
        idx = I2C_Compute_SCLL_SCLH(&p_advanced_config, speed);

        if (idx < I2C_VALID_TIMING_NBR)
        {
          *p_output_timing_reg = ((i2c_valid_timing[idx].presc  & 0x0FU) << 28) | \
                                 ((i2c_valid_timing[idx].tscldel & 0x0FU) << 20) | \
                                 ((i2c_valid_timing[idx].tsdadel & 0x0FU) << 16) | \
                                 ((i2c_valid_timing[idx].sclh & 0xFFU) << 8) | \
                                 ((i2c_valid_timing[idx].scll & 0xFFU) << 0);

          status = STM32_UTILS_I2C_OK;
        }
        break;
      }
    }
  }

  return status;
}


/**
  * @brief  Compute I2C timing according current I2C clock source and required I2C clock.
  * @param  p_config Pointer to a @ref stm32_utils_i2c_timing_advanced_config_t structure that contains
  *         the required parameter for I2C timing computation.
  * @param  p_output_timing_reg Pointer to a I2C_TIMINGR register value calculated by referring to I2C
            initialization section in reference Manual.
  * @retval STM32_UTILS_I2C_OK Timing calculation successfully
  * @retval STM32_UTILS_I2C_ERROR Timing calculation error
  */
stm32_utils_i2c_status_t STM32_UTILS_I2C_ComputeAdvanced(const stm32_utils_i2c_timing_advanced_config_t *p_config,
                                                         uint32_t *p_output_timing_reg)
{
  stm32_utils_i2c_status_t status = STM32_UTILS_I2C_ERROR;
  uint32_t idx;
  i2c_valid_timing_nbr = 0;

  if ((p_config->clock_src_freq_hz != 0U) && (p_config->i2c_freq_hz != 0U))
  {
    for (uint32_t speed = 0 ; speed <= (uint32_t)I2C_SPEED_FREQ_FAST_PLUS ; speed++)
    {
      if ((p_config->i2c_freq_hz >= I2C_Charac[speed].freq_min) \
          && (p_config->i2c_freq_hz <= I2C_Charac[speed].freq_max))
      {
        if (I2C_Compute_PRESC_SCLDEL_SDADEL(p_config, speed) != STM32_UTILS_I2C_OK)
        {
          return STM32_UTILS_I2C_ERROR;
        }

        idx = I2C_Compute_SCLL_SCLH(p_config, speed);

        if (idx < I2C_VALID_TIMING_NBR)
        {
          *p_output_timing_reg = ((i2c_valid_timing[idx].presc  & 0x0FU) << 28) | \
                                 ((i2c_valid_timing[idx].tscldel & 0x0FU) << 20) | \
                                 ((i2c_valid_timing[idx].tsdadel & 0x0FU) << 16) | \
                                 ((i2c_valid_timing[idx].sclh & 0xFFU) << 8) | \
                                 ((i2c_valid_timing[idx].scll & 0xFFU) << 0);

          status = STM32_UTILS_I2C_OK;
        }
        break;
      }
    }
  }

  return status;
}

/**
  * @brief  Compute SMBUS timeout A using current I2C clock source, IDLE mode and timeout wanted in ns.
  * @param  p_config Pointer to a @ref stm32_utils_i2c_smbus_timeouta_config_t structure containing the desired
  *         Timeout parameters.
  * @param  p_output_timeout_reg Pointer to a I2C_TIMEOUTR register value calculated.
  * @note   When IDLE mode is disabled timeout value must be between 25000000 ns and 35000000 ns per SMBUS Specification
  * @note   When IDLE mode is enabled timeout value must be under tIDLE= (0xFFF + 1) x 4 x tI2CCLK
  * @retval STM32_UTILS_I2C_OK Timing calculation successfully
  * @retval STM32_UTILS_I2C_INVALID_PARAM in case of invalid parameter.
  */
stm32_utils_i2c_status_t STM32_UTILS_I2C_SMBUS_ComputeTimeoutA(const stm32_utils_i2c_smbus_timeouta_config_t *p_config,
                                                               uint32_t *p_output_timeout_reg)
{
  double ti2cclk;
  stm32_utils_i2c_status_t status = STM32_UTILS_I2C_INVALID_PARAM;
  if (p_config != NULL)
  {
    if (p_config->clock_src_freq_hz != 0U)
    {
      uint32_t timeout_ns = p_config->timeout_ns;
      ti2cclk = (double)SEC2NSEC / p_config->clock_src_freq_hz;
      if (ti2cclk > 0U)
      {
        if (p_config->timeouta_mode == STM32_UTILS_I2C_SMBUS_TIMEOUTA_MODE_SDA_SCL_HIGH)
        {
          /* Compute the p_output_timeout_reg value based on Reference manual formula:
             tIDLE= (TIMEOUTA + 1) x 4 x tI2CCLK */
          *p_output_timeout_reg = (uint32_t)(DIV_ROUND_CLOSEST(timeout_ns, (ti2cclk * 4U)) - 1);
          if (*p_output_timeout_reg <= 0xFFF)
          {
            status = STM32_UTILS_I2C_OK;
          }
        }
        else
        {
          if ((timeout_ns <= SMBUS_IDLE_TIMEOUT_MAX) && (timeout_ns >= SMBUS_IDLE_TIMEOUT_MIN))
          {
            /* Compute the p_output_timeout_reg value based on Reference manual formula:
               tTIMEOUT= (TIMEOUTA + 1) x 2048 x tI2CCLK */
            *p_output_timeout_reg = (uint32_t)(DIV_ROUND_CLOSEST(timeout_ns, (ti2cclk * 2048U)) - 1);

            status = STM32_UTILS_I2C_OK;
          }
        }
      }
    }
  }
  return status;
}

/**
  * @brief  Compute SMBUS timeout B using current I2C clock source, device mode and timeout wanted in ns.
  * @param  p_config Pointer to a @ref stm32_utils_i2c_smbus_timeoutb_config_t structure containing the desired
  *         Timeout parameters.
  * @param  p_output_timeout_reg Pointer to a I2C_TIMEOUTR register value calculated.
  * @retval STM32_UTILS_I2C_OK Timing calculation successfully
  */
stm32_utils_i2c_status_t STM32_UTILS_I2C_SMBUS_ComputeTimeoutB(const stm32_utils_i2c_smbus_timeoutb_config_t *p_config,
                                                               uint32_t *p_output_timeout_reg)
{
  double ti2cclk;
  stm32_utils_i2c_status_t status = STM32_UTILS_I2C_INVALID_PARAM;
  if (p_config != NULL)
  {
    if (p_config->clock_src_freq_hz != 0U)
    {
      uint32_t timeout_ns = p_config->timeout_ns;
      ti2cclk = (double)SEC2NSEC / p_config->clock_src_freq_hz;
      if (ti2cclk > 0U)
      {
        if (p_config->smbus_device_mode == STM32_UTILS_I2C_SMBUS_SLAVE_MODE)
        {
          if (timeout_ns <= SMBUS_SLAVE_EXT_LOW_TIMEOUT_MAX)
          {
            /* Compute the p_output_timeout_reg value based on Reference manual formula:
               tLOW:SEXT= (TIMEOUTB + 1) x 2048 x tI2CCLK */
            *p_output_timeout_reg = (uint32_t)(DIV_ROUND_CLOSEST(timeout_ns, (ti2cclk * 2048U)) - 1);

            status = STM32_UTILS_I2C_OK;
          }
        }
        else
        {
          if (timeout_ns <= SMBUS_MASTER_EXT_LOW_TIMEOUT_MAX)
          {
            /* Compute the p_output_timeout_reg value based on Reference manual formula:
               tLOW:MEXT= (TIMEOUTB + 1) x 2048 x tI2CCLK */
            *p_output_timeout_reg = (uint32_t)(DIV_ROUND_CLOSEST(timeout_ns, (ti2cclk * 2048U)) - 1);

            status = STM32_UTILS_I2C_OK;
          }
        }
      }
    }
  }
  return status;
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Compute PRESC, SCLDEL and SDADEL.
  * @param  p_config Pointer to a @ref stm32_utils_i2c_timing_advanced_config_t structure containing the timing
  *         config parameters.
  * @param  I2C_speed I2C frequency (index).
  * @retval STM32_UTILS_I2C_OK Timing calculation successfully
  * @retval STM32_UTILS_I2C_ERROR Timing calculation error
  */
static stm32_utils_i2c_status_t I2C_Compute_PRESC_SCLDEL_SDADEL(const stm32_utils_i2c_timing_advanced_config_t
                                                                *p_config,
                                                                uint32_t I2C_speed)
{
  stm32_utils_i2c_status_t status = STM32_UTILS_I2C_ERROR;
  uint32_t prev_presc = I2C_PRESC_MAX;
  double ti2cclk, tsdadel_min, tsdadel_max, tscldel_min, tafdel_min, tafdel_max;

  ti2cclk = (double) SEC2NSEC / (double) p_config->clock_src_freq_hz;

  tafdel_min = (p_config->af == STM32_UTILS_I2C_ANALOG_FILTER_ENABLED) ? I2C_ANALOG_FILTER_DELAY_MIN : 0U;
  tafdel_max = (p_config->af == STM32_UTILS_I2C_ANALOG_FILTER_ENABLED) ? I2C_ANALOG_FILTER_DELAY_MAX : 0U;

  /* tDNF = DNF x tI2CCLK
     tPRESC = (PRESC+1) x tI2CCLK
     SDADEL >= {tf +tHD;DAT(min) - tAF(min) - tDNF - [3 x tI2CCLK]} / {tPRESC}
     SDADEL <= {tVD;DAT(max) - tr - tAF(max) - tDNF- [4 x tI2CCLK]} / {tPRESC} */

  tsdadel_min = p_config->tfall_ns + I2C_Charac[I2C_speed].hddat_min -
                tafdel_min - ((p_config->dnf + 3) * ti2cclk);

  tsdadel_max = I2C_Charac[I2C_speed].vddat_max - p_config->trise_ns -
                tafdel_max - ((p_config->dnf + 4) * ti2cclk);


  /* {[tr+ tSU;DAT(min)] / [tPRESC]} - 1 <= SCLDEL */
  tscldel_min = p_config->trise_ns + I2C_Charac[I2C_speed].sudat_min;

  if (tsdadel_min <= 0)
  {
    tsdadel_min = 0;
  }

  if (tsdadel_max <= 0)
  {
    tsdadel_max = 0;
  }

  for (uint32_t presc = 0; presc < I2C_PRESC_MAX; presc++)
  {
    for (uint32_t scldel = 0; scldel < I2C_SCLDEL_MAX; scldel++)
    {
      /* TSCLDEL = (SCLDEL+1) * (PRESC+1) * TI2CCLK */
      double tscldel = (scldel + 1U) * (presc + 1U) * ti2cclk;

      if (tscldel >= tscldel_min)
      {
        for (uint32_t sdadel = 0; sdadel < I2C_SDADEL_MAX; sdadel++)
        {
          /* TSDADEL = SDADEL * (PRESC+1) * TI2CCLK */
          double tsdadel = (sdadel * (presc + 1U)) * ti2cclk;

          if ((tsdadel >= tsdadel_min) && (tsdadel <= tsdadel_max))
          {
            if (presc != prev_presc)
            {
              i2c_valid_timing[i2c_valid_timing_nbr].presc = presc;
              i2c_valid_timing[i2c_valid_timing_nbr].tscldel = scldel;
              i2c_valid_timing[i2c_valid_timing_nbr].tsdadel = sdadel;
              prev_presc = presc;
              i2c_valid_timing_nbr ++;
              if (i2c_valid_timing_nbr >= I2C_VALID_TIMING_NBR)
              {
                return STM32_UTILS_I2C_ERROR;
              }
              else
              {
                status = STM32_UTILS_I2C_OK;
              }
            }
          }
        }
      }
    }
  }

  return status;
}

/**
  * @brief  Calculate SCLL and SCLH and find best configuration.
  * @param  p_config Pointer to a @ref stm32_utils_i2c_timing_advanced_config_t structure containing the timing
  *         config parameters.
  * @param  I2C_speed I2C frequency (index).
  * @retval config index (0 to I2C_VALID_TIMING_NBR), 0xAAAAAAAAU for no valid config.
  */
static uint32_t I2C_Compute_SCLL_SCLH(const stm32_utils_i2c_timing_advanced_config_t *p_config, uint32_t I2C_speed)
{
  uint32_t ret = 0xAAAAAAAAU;
  double ti2cclk, ti2cspeed, prev_error, dnf_delay, clk_min, clk_max, tafdel_min;

  ti2cclk = SEC2NSEC / p_config->clock_src_freq_hz;
  ti2cspeed = SEC2NSEC / p_config->i2c_freq_hz;

  tafdel_min = (p_config->af == STM32_UTILS_I2C_ANALOG_FILTER_ENABLED) ? I2C_ANALOG_FILTER_DELAY_MIN : 0U;

  /* tDNF = DNF x tI2CCLK */
  dnf_delay = p_config->dnf * ti2cclk;

  clk_max = SEC2NSEC / I2C_Charac[I2C_speed].freq_min;
  clk_min = SEC2NSEC / I2C_Charac[I2C_speed].freq_max;

  prev_error = ti2cspeed;

  for (uint32_t count = 0; count < i2c_valid_timing_nbr; count++)
  {
    /* tPRESC = (PRESC+1) x tI2CCLK*/
    double tpresc = (i2c_valid_timing[count].presc + 1U) * ti2cclk;

    for (uint32_t  scll = 0; scll < I2C_SCLL_MAX; scll++)
    {
      /* tLOW(min) <= tAF(min) + tDNF + 2 x tI2CCLK + [(SCLL+1) x tPRESC ] */
      double tscl_l = tafdel_min + dnf_delay + (2U * ti2cclk) + ((scll + 1U) * tpresc);

      /* The I2CCLK period tI2CCLK must respect the following conditions:
      tI2CCLK < (tLOW - tfilters) / 4 and tI2CCLK < tHIGH */
      if ((tscl_l > I2C_Charac[I2C_speed].lscl_min) && (ti2cclk < ((tscl_l - tafdel_min - dnf_delay) / 4U)))
      {
        for (uint32_t  sclh = 0; sclh < I2C_SCLH_MAX; sclh++)
        {
          /* tHIGH(min) <= tAF(min) + tDNF + 2 x tI2CCLK + [(SCLH+1) x tPRESC] */
          double tscl_h = tafdel_min + dnf_delay + (2U * ti2cclk) + ((sclh + 1U) * tpresc);

          /* tSCL = tf + tLOW + tr + tHIGH */
          double tscl = tscl_l + tscl_h + p_config->trise_ns + p_config->tfall_ns;

          if ((tscl >= clk_min) && (tscl <= clk_max) && (tscl_h >= I2C_Charac[I2C_speed].hscl_min)
              && (ti2cclk < tscl_h))
          {
            int32_t error = (int32_t)tscl - (int32_t)ti2cspeed;

            if (error < 0)
            {
              error = -error;
            }

            /* look for the timings with the lowest clock error */
            if (error < prev_error)
            {
              prev_error = error;
              i2c_valid_timing[count].scll = scll;
              i2c_valid_timing[count].sclh = sclh;
              ret = count;
            }
          }
        }
      }
    }
  }

  return ret;
}
/**
  * @}
  */

/**
  * @}
  */
