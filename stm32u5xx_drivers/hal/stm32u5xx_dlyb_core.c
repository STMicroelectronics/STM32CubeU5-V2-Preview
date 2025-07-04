/**
  **********************************************************************************************************************
  * @file    stm32u5xx_dlyb_core.c
  * @brief   DelayBlock Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the DelayBlock peripheral:
  *           + input clock frequency
  *           + up to 12 oversampling phases
  *
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************

# DLYB peripheral feature :
The DelayBlock is used to generate an Output clock which is de-phased from the Input clock.
The phase of the Output clock is programmed by FW. The Output clock is then used to clock the receive data in
an SDMMC, OSPI or QSPI interface.
The delay is Voltage and Temperature dependent, which could require FW to do re-tuning and recenter the Output clock
phase of the receive data.
The DelayBlock features include the following:
- Input clock frequency.
- Up to 12 oversampling phases.

# How to use this driver :
This driver is a considered as a driver of service for external device drivers that interfaces with the delayblock
peripheral.

- The DLYB_ConfigureUnitDelay() function set the length of a Delay UNIT cell so that the delay line length covers the
span of one input clock cycle.
- The DLYB_CalculateMaxOutputClockPhase() function determine how many delay unit cells (max)span one input clock period.
- The DLYB_SetOutputClockPhase() function sets the output clock phase value.
- The DLYB_GetOutputClockPhase () function gets the output clock phase value.
- The DLYB_SetConfig() sets context of CFGR register (UNIT and SEL).
- The DLYB_GetConfig() gets context of CFGR register (UNIT and SEL).

To properly use this driver, the user must follow these steps :

- Enable the delay block using the static inline DLYB_Enable() function.
- Set the length of the Delay UNIT so that the delay line length covers the span of one input clock cycle using
the DLYB_ConfigureUnitDelay() function.
- Determine how many Delay UNITs cover the span of an input clock period using DLYB_CalculateMaxOutputClockPhase()
function, the returned value will be used later.
- Set the output clock phase to a desired value using the DLYB_SetOutputClockPhase(), this value must be not exceed
the value returned by DLYB_CalculateMaxOutputClockPhase().
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup DLYB_CORE DLYB Core
  * @{
  */

#if (defined (USE_HAL_SD_MODULE) && (USE_HAL_SD_MODULE == 1)) \
    || (defined (USE_HAL_MMC_MODULE) && (USE_HAL_MMC_MODULE == 1)) \
    || (defined (USE_HAL_SDIO_MODULE) && (USE_HAL_SDIO_MODULE == 1)) \
    || (defined (USE_HAL_XSPI_MODULE) && (USE_HAL_XSPI_MODULE == 1))
#if defined (DLYB_SDMMC1) || defined (DLYB_SDMMC2) || defined (DLYB_OCTOSPI1) || defined (DLYB_OCTOSPI2)

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup DLYB_CORE_Exported_Functions
  *  @{
  */

/** @addtogroup DLYB_CORE_Group1 Output clock phase tuning functions
  * @{
This section provides functions allowing to tune the DLYB output clock phase :
- Call the function DLYB_ConfigureUnitDelay() to Set the length of a delay UNIT.
- Call the function DLYB_CalculateMaxOutputClockPhase() to determine how many delay UNITs cover the span of an input
  clock cycle.
  */
/**
  * @brief Set the length of a Delay UNIT.
  * @param dlybx Pointer to DLYB instance.
  * @retval HAL_ERROR The Delay value is not set.
  * @retval HAL_OK    The Delay value is set.
  */
hal_status_t DLYB_ConfigureUnitDelay(DLYB_TypeDef *dlybx)
{
  uint32_t unit = 0U;
  uint32_t tickstart =  HAL_GetTick();

  SET_BIT(dlybx->CR, DLYB_CR_SEN);

  /* Delay line length detection */
  while (unit < DLYB_MAX_UNIT_DELAY_CELL)
  {
    MODIFY_REG(dlybx->CFGR, DLYB_CFGR_UNIT | DLYB_CFGR_SEL,
               DLYB_MAX_TUNING_OUTPUT_CLK_PHASE | (unit << DLYB_CFGR_UNIT_Pos));

    /* Waiting for a LNG valid value */
    while ((dlybx->CFGR & DLYB_CFGR_LNGF) == 0U)
    {
      if ((HAL_GetTick() - tickstart) >= DLYB_TIMEOUT_MS)
      {
        if ((dlybx->CFGR & DLYB_CFGR_LNGF) == 0U)
        {
          CLEAR_BIT(dlybx->CR, DLYB_CR_SEN);
          return HAL_ERROR;
        }
      }
    }

    if ((dlybx->CFGR & DLYB_LNG_10_0_MSK) != 0U)
    {
      if ((dlybx->CFGR & (DLYB_CFGR_LNG_11 | DLYB_CFGR_LNG_10)) != DLYB_LNG_11_10_MSK)
      {
        /* Delay line length is configured to one input clock period */
        break;
      }
    }

    unit++;
  }
  CLEAR_BIT(dlybx->CR, DLYB_CR_SEN);

  return HAL_OK;
}

/**
  * @brief Determine how many delay unit cells  (max) span one input clock period.
  * @param dlybx Pointer to DLYB instance.
  * @retval uint32_t max number of units that span a full input clock cycle.
  */
uint32_t DLYB_CalculateMaxOutputClockPhase(DLYB_TypeDef *dlybx)
{
  uint32_t len = (dlybx->CFGR & DLYB_CFGR_LNG) >> DLYB_CFGR_LNG_Pos;
  uint32_t max = DLYB_MAX_USED_OUTPUT_CLK_PHASE;

  SET_BIT(dlybx->CR, DLYB_CR_SEN);

  /* Determine how many delay unit cells  (max) span one input clock period */
  while ((max > 0U) && ((len >> max) == 0U))
  {
    max--;
  }

  CLEAR_BIT(dlybx->CR, DLYB_CR_SEN);

  return max;
}
/**
  * @}
  */
/** @addtogroup DLYB_CORE_Group2 Set and Get Output Clock Phase Value Functions
  * @{
This section provides functions allowing to tune the DLYB output clock phase :
- Call the function DLYB_SetOutputClockPhase() to set the output clock phase value.
- Call the function DLYB_GetOutputClockPhase() to get the output clock phase value.
@note : The output clock phase value must be not exceed the value returned by DLYB_CalculateMaxOutputClockPhase().
  */
/**
  * @brief Set the output clock phase value.
  * @param dlybx             Pointer to DLYB instance.
  * @param clock_phase_value The desired output clock phase value.
  */
void DLYB_SetOutputClockPhase(DLYB_TypeDef *dlybx, uint32_t clock_phase_value)
{

  SET_BIT(dlybx->CR, DLYB_CR_SEN);
  MODIFY_REG(dlybx->CFGR, DLYB_CFGR_SEL, clock_phase_value);
  CLEAR_BIT(dlybx->CR, DLYB_CR_SEN);
}

/**
  * @brief Get the output clock phase value.
  * @param dlybx Pointer to DLYB instance.
  * @retval the output clock phase value.
  */
uint32_t DLYB_GetOutputClockPhase(const DLYB_TypeDef *dlybx)
{
  return (READ_BIT(dlybx->CFGR, DLYB_CFGR_SEL));
}
/**
  * @}
  */

/** @addtogroup DLYB_CORE_Group3 Set and Get DLYB CFGR register context
  * @{
This section provides functions allowing Set and Get the context of CFGR store then restore the content of this register
when needed:
- Call the function DLYB_SetConfig() to set context of CFGR register (UNIT and SEL).
- Call the function DLYB_GetConfig() to store context of CFGR register (UNIT and SEL).
  */
/**
  * @brief Set DLYB CFGR context.
  * @param dlybx DLYB Instance.
  * @param unit  The unit to set.
  * @param sel   The sel to set.
  */
void DLYB_SetConfig(DLYB_TypeDef *dlybx, uint32_t unit, uint32_t sel)
{
  SET_BIT(dlybx->CR, DLYB_CR_SEN);
  MODIFY_REG(dlybx->CFGR, (DLYB_CFGR_SEL | DLYB_CFGR_UNIT), sel + (unit << DLYB_CFGR_UNIT_Pos));
  CLEAR_BIT(dlybx->CR, DLYB_CR_SEN);
}

/**
  *@brief Get DLYB CFGR context.
  * @param dlybx  DLYB Instance.
  * @param p_unit The unit to set.
  * @param p_sel  The sel to set.
  */

void DLYB_GetConfig(DLYB_TypeDef *dlybx, uint32_t *p_unit, uint32_t *p_sel)
{
  *p_sel = READ_BIT(dlybx->CFGR, DLYB_CFGR_SEL);
  *p_unit = READ_BIT(dlybx->CFGR, DLYB_CFGR_UNIT >> DLYB_CFGR_UNIT_Pos);
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* DLYB_SDMMC1 || DLYB_SDMMC2 || DLYB_OCTOSPI1 || DLYB_OCTOSPI2 */
#endif /* USE_HAL_SD_MODULE || USE_HAL_MMC_MODULE || USE_HAL_SDIO_MODULE || USE_HAL_XSPI_MODULE */
/**
  * @}
  */

/**
  * @}
  */
