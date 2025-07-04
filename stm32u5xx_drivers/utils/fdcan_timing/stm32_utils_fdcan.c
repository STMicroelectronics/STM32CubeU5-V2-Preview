/**
  **********************************************************************************************************************
  * @file    stm32_utils_fdcan.c
  * @brief   STM32 UTILS FDCAN module.
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
#include "stm32_utils_fdcan.h"

/** @addtogroup STM32_UTILS
  * @{
  */

/** @addtogroup FDCAN
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup FDCAN_Private_Constants FDCAN Private Constants
  * @{
  */

#define FDCAN_NOMINAL_PRESCALER_MIN (1U)    /*!< Nominal prescaler min value                       */
#define FDCAN_NOMINAL_PRESCALER_MAX (512U)  /*!< Nominal prescaler max value                       */
#define FDCAN_NOMINAL_TIME_SEG1_MIN (2U)    /*!< Nominal time segment 1 min value                  */
#define FDCAN_NOMINAL_TIME_SEG1_MAX (256U)  /*!< Nominal time segment 1 max value                  */
#define FDCAN_NOMINAL_TIME_SEG2_MIN (2U)    /*!< Nominal time segment 2 min value                  */
#define FDCAN_NOMINAL_TIME_SEG2_MAX (128U)  /*!< Nominal time segment 2 max value                  */

#define FDCAN_DATA_PRESCALER_MIN    (1U)    /*!< Data prescaler min value                          */
#define FDCAN_DATA_PRESCALER_MAX    (32U)   /*!< Data prescaler max value                          */
#define FDCAN_DATA_TIME_SEG1_MIN    (1U)    /*!< Data time segment 1 min value                     */
#define FDCAN_DATA_TIME_SEG1_MAX    (32U)   /*!< Data time segment 1 max value                     */
#define FDCAN_DATA_TIME_SEG2_MIN    (1U)    /*!< Data time segment 2 min value                     */
#define FDCAN_DATA_TIME_SEG2_MAX    (16U)   /*!< Data time segment 2 max value                     */

#define VALUE_1000                  (1000U) /*!< Constant for value 1000, used for unit conversion */

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Macros FDCAN Private Macros
  * @{
  */

/** @brief  Rounds the given number to the nearest multiple of the divisor.
  * @param  x The number to be rounded.
  * @param  d The divisor used for rounding.
  * @return The rounded number.
  */
#define DIV_ROUND_CLOSEST(x, d)   (((x) + ((d) / 2U)) / (d))

/**
  * @brief  Rounds the given number up to the nearest multiple of the divisor.
  * @param  x The number to be rounded.
  * @param  d The divisor used for rounding.
  * @return The rounded number.
  */
#define DIV_ROUND_UP(x, d)        (((x) + ((d) - 1U)) / (d))

/**
  * @}
  */

/* Private types ------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Types FDCAN Private Types
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FDCAN_Exported_Functions
  * @{
  */

/**
  * @brief  Compute the FDCAN nominal or data bit timings from input bus parameters.
  * @param  p_bus_param Pointer to a @ref stm32_utils_fdcan_input_bus_param_t structure containing the desired
  *         bus parameters.
  * @param  bit_timing_type Type of bit timing to compute (nominal or data).
  * @param  p_output_bit_timing Pointer to a @ref stm32_utils_fdcan_bit_timing_t structure to fill
  *         with computed bit timings.
  * @param  p_output_config Pointer to a @ref stm32_utils_fdcan_output_config_t structure containing the real
  *         bus parameters.
  * @note   The given maximum bitrate tolerance takes into account integer rounding, and guarantees that the bitrate
  *         deviation is always below or equal to the maximum given.
  * @note   The @ref stm32_utils_fdcan_bit_timing_t:sync_jump_width parameter is highly dependent on the specific
  *         characteristics of the CAN network, such as the network's length, the propagation delay, the oscillator
  *         tolerance, etc.
  *         Therefore, this function will always set it to the default minimal value 1. This value can be fine-tuned
  *         by the end user if synchronization issues are observed.
  * @retval STM32_UTILS_FDCAN_OK            Configuration matching the bus parameters was found.
  * @retval STM32_UTILS_FDCAN_ERROR         No configuration matching the bus parameters was found. Data output
  *                                         must be discarded.
  * @retval STM32_UTILS_FDCAN_INVALID_PARAM Pointer parameter is NULL.
  */
stm32_utils_fdcan_status_t STM32_UTILS_FDCAN_ComputeBitTiming(const stm32_utils_fdcan_input_bus_param_t *p_bus_param,
                                                              stm32_utils_fdcan_bit_timing_type_t bit_timing_type,
                                                              stm32_utils_fdcan_bit_timing_t *p_output_bit_timing,
                                                              stm32_utils_fdcan_output_config_t *p_output_config)
{
  stm32_utils_fdcan_status_t status;
  uint32_t current_prescaler;
  uint32_t prescaler_max;
  uint16_t real_sample_point_per_mille = 0U;
  uint32_t real_bitrate_kbps = 0U;
  uint8_t  flag_result_found = 0U;
  uint32_t tseg1 = 0U;
  uint32_t tseg2 = 0U;
  uint32_t tseg1_min;
  uint32_t tseg1_max;
  uint32_t tseg2_min;
  uint32_t tseg2_max;
  uint64_t product_presc_bitrate;
  uint64_t tmp_multiply_clk_sample_point;
  uint64_t tmp_num;

  if ((p_output_bit_timing == NULL) || (p_bus_param == NULL) || (p_output_config == NULL))
  {
    return STM32_UTILS_FDCAN_INVALID_PARAM;
  }

  tmp_multiply_clk_sample_point = (uint64_t)p_bus_param->fdcan_ker_clk_khz *
                                  (uint64_t)p_bus_param->sample_point_per_mille;
  tmp_num = (VALUE_1000 * (uint64_t)p_bus_param->fdcan_ker_clk_khz) - (uint64_t)tmp_multiply_clk_sample_point;

  /* Adapt the parameters to nominal or data type requirements */
  if (bit_timing_type == STM32_UTILS_FDCAN_BIT_TIMING_TYPE_NOMINAL)
  {
    current_prescaler = FDCAN_NOMINAL_PRESCALER_MIN;
    prescaler_max     = FDCAN_NOMINAL_PRESCALER_MAX;
    tseg1_min         = FDCAN_NOMINAL_TIME_SEG1_MIN;
    tseg1_max         = FDCAN_NOMINAL_TIME_SEG1_MAX;
    tseg2_min         = FDCAN_NOMINAL_TIME_SEG2_MIN;
    tseg2_max         = FDCAN_NOMINAL_TIME_SEG2_MAX;
  }
  else
  {
    current_prescaler = FDCAN_DATA_PRESCALER_MIN;
    prescaler_max     = FDCAN_DATA_PRESCALER_MAX;
    tseg1_min         = FDCAN_DATA_TIME_SEG1_MIN;
    tseg1_max         = FDCAN_DATA_TIME_SEG1_MAX;
    tseg2_min         = FDCAN_DATA_TIME_SEG2_MIN;
    tseg2_max         = FDCAN_DATA_TIME_SEG2_MAX;
  }

  /* Iterate through the prescaler values */
  while (current_prescaler <= prescaler_max)
  {
    /* Compute variables expressions */
    product_presc_bitrate = ((uint64_t)current_prescaler * (uint64_t)p_bus_param->desired_bitrate_kbps * VALUE_1000);
    if (product_presc_bitrate == 0U)
    {
      /* Avoid future division by zero, go to next prescaler iteration */
      current_prescaler++;
      continue;
    }
    tseg1 = (uint32_t)DIV_ROUND_CLOSEST(tmp_multiply_clk_sample_point, product_presc_bitrate) - 1U;
    tseg2 = (uint32_t)DIV_ROUND_CLOSEST(tmp_num, product_presc_bitrate);

    /* Check if computed time segments are within their valid ranges */
    if ((tseg1_min <= tseg1) && (tseg1 <= tseg1_max) && (tseg2_min <= tseg2) && (tseg2 <= tseg2_max))
    {
      /* Compute the obtained sample point and bitrate with the found time segments values */
      real_sample_point_per_mille = (uint16_t)DIV_ROUND_CLOSEST((VALUE_1000 + (VALUE_1000 * (uint16_t)tseg1)),
                                                                (1U + (uint16_t)tseg1 + (uint16_t)tseg2));
      real_bitrate_kbps = (uint32_t)DIV_ROUND_CLOSEST((p_bus_param->fdcan_ker_clk_khz * real_sample_point_per_mille),
                                                      (VALUE_1000 * (current_prescaler * (1U + tseg1))));

      /* Avoid negative numbers when subtracting */
      if (p_bus_param->desired_bitrate_kbps >= real_bitrate_kbps)
      {
        /* Compute and compare the percentage difference */
        if ((DIV_ROUND_UP((2U * VALUE_1000 * (p_bus_param->desired_bitrate_kbps - real_bitrate_kbps)),
                          (p_bus_param->desired_bitrate_kbps + real_bitrate_kbps)))
            > p_bus_param->bitrate_tolerance_per_mille)
        {
          /* Deviation is not within the maximum tolerance, go to next prescaler iteration */
          current_prescaler++;
          continue;
        }
      }
      else
      {
        /* Compute and compare the percentage difference */
        if ((DIV_ROUND_UP((2U * VALUE_1000 * (real_bitrate_kbps - p_bus_param->desired_bitrate_kbps)),
                          (p_bus_param->desired_bitrate_kbps + real_bitrate_kbps)))
            > p_bus_param->bitrate_tolerance_per_mille)
        {
          /* Deviation is not within the maximum tolerance, go to next prescaler iteration */
          current_prescaler++;
          continue;
        }
      }

      /* If the real bitrate is within the tolerance, flag the result as found and stop iterating */
      flag_result_found = 1U;
      break;
    }

    /* Try with next prescaler */
    current_prescaler++;
  }

  if (flag_result_found != 0U)
  {
    p_output_bit_timing->prescaler               = current_prescaler;
    p_output_bit_timing->time_seg1               = tseg1;
    p_output_bit_timing->time_seg2               = tseg2;
    p_output_bit_timing->sync_jump_width         = 1U;
    p_output_config->real_bitrate_kbps           = real_bitrate_kbps;
    p_output_config->real_sample_point_per_mille = real_sample_point_per_mille;

    status = STM32_UTILS_FDCAN_OK;
  }
  else
  {
    /* No configuration matching the input parameters were found */
    p_output_bit_timing->prescaler               = 0U;
    p_output_bit_timing->time_seg1               = 0U;
    p_output_bit_timing->time_seg2               = 0U;
    p_output_bit_timing->sync_jump_width         = 0U;
    p_output_config->real_bitrate_kbps           = 0U;
    p_output_config->real_sample_point_per_mille = 0U;

    status = STM32_UTILS_FDCAN_ERROR;
  }

  return status;
}

/**
  * @brief  Compute the FDCAN nominal or data bitrate and sampling point from bit timing parameters.
  * @param  p_bit_timing Pointer to a @ref stm32_utils_fdcan_bit_timing_t structure.
  * @param  fdcan_clk_khz FDCAN clk in kHz.
  * @param  p_output_config Pointer to a @ref stm32_utils_fdcan_output_config_t structure containing
  *         the computed bus parameters.
  * @retval STM32_UTILS_FDCAN_OK            Operation completed successfully.
  * @retval STM32_UTILS_FDCAN_INVALID_PARAM Pointer parameter is NULL.
  */
stm32_utils_fdcan_status_t STM32_UTILS_FDCAN_ComputeBitrate(const stm32_utils_fdcan_bit_timing_t *p_bit_timing,
                                                            uint32_t fdcan_clk_khz,
                                                            stm32_utils_fdcan_output_config_t *p_output_config)
{
  if ((p_bit_timing == NULL) || (p_output_config == NULL))
  {
    return STM32_UTILS_FDCAN_INVALID_PARAM;
  }

  /* Compute the sample point and bitrate with the given time segments values */
  p_output_config->real_sample_point_per_mille =
    (uint16_t)DIV_ROUND_CLOSEST((VALUE_1000 + (VALUE_1000 * p_bit_timing->time_seg1)),
                                (1U + p_bit_timing->time_seg1 + p_bit_timing->time_seg2));
  p_output_config->real_bitrate_kbps =
    DIV_ROUND_CLOSEST((fdcan_clk_khz * p_output_config->real_sample_point_per_mille),
                      (VALUE_1000 * (p_bit_timing->prescaler + (p_bit_timing->prescaler * p_bit_timing->time_seg1))));
  return STM32_UTILS_FDCAN_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
