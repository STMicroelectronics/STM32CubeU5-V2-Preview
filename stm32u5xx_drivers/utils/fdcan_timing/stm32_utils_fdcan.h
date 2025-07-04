/**
  ******************************************************************************
  * @file    stm32_utils_fdcan.h
  * @brief   Header file for STM32 UTILS FDCAN module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_UTILS_FDCAN_H
#define STM32_UTILS_FDCAN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>

/** @addtogroup STM32_UTILS
  * @{
  */

/** @addtogroup FDCAN
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  FDCAN_Exported_Types FDCAN Exported Types
  * @{
  */

/**
  * @brief  FDCAN Utils Status structures definition
  */
typedef enum
{
  STM32_UTILS_FDCAN_OK            = 0x00000000U, /*!< Utils FDCAN operation completed successfully */
  STM32_UTILS_FDCAN_ERROR         = 0xFFFFFFFFU, /*!< Utils FDCAN operation completed with error   */
  STM32_UTILS_FDCAN_INVALID_PARAM = 0xAAAAAAAAU, /*!< Utils FDCAN invalid parameter                */
} stm32_utils_fdcan_status_t;

/**
  * @brief FDCAN Output real bus parameters obtained with computed bit timings
  */
typedef struct
{
  uint32_t real_bitrate_kbps;           /*!< Real bus bitrate in kbit/s                            */
  uint16_t real_sample_point_per_mille; /*!< Real sample point in in per mille (percent * 10)      */
} stm32_utils_fdcan_output_config_t;

/**
  * @brief FDCAN Input bus parameters
  */
typedef struct
{
  uint32_t fdcan_ker_clk_khz;           /*!< FDCAN kernel clk in kHz                               */
  uint32_t desired_bitrate_kbps;        /*!< Desired bus bitrate in kbit/s                         */
  uint16_t sample_point_per_mille;      /*!< Sample point in per mille (percent * 10)              */
  uint8_t  bitrate_tolerance_per_mille; /*!< Maximum bitrate tolerance in per mille (percent * 10) */
} stm32_utils_fdcan_input_bus_param_t;

/**
  * @brief FDCAN Timing structure definition. Applicable to nominal or data bit timing.
  */
typedef struct
{
  uint32_t prescaler;       /*!< Specifies the value by which the oscillator frequency is divided
                                 for generating the nominal bit time quanta.                        */
  uint32_t sync_jump_width; /*!< Specifies the maximum number of time quanta the FDCAN hardware is
                                 allowed to lengthen or shorten a bit to perform resynchronization. */
  uint32_t time_seg1;       /*!< Specifies the number of time quanta in Bit Segment 1.              */
  uint32_t time_seg2;       /*!< Specifies the number of time quanta in Bit Segment 2.              */
} stm32_utils_fdcan_bit_timing_t;

/**
  * @brief FDCAN Nominal or data bit timing types
  */
typedef enum
{
  STM32_UTILS_FDCAN_BIT_TIMING_TYPE_NOMINAL = 0U, /*!< Nominal bit timing */
  STM32_UTILS_FDCAN_BIT_TIMING_TYPE_DATA    = 1U, /*!< Data bit timing    */
} stm32_utils_fdcan_bit_timing_type_t;

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Functions FDCAN Exported Functions
  * @{
  */

stm32_utils_fdcan_status_t STM32_UTILS_FDCAN_ComputeBitTiming(const stm32_utils_fdcan_input_bus_param_t *p_bus_param,
                                                              stm32_utils_fdcan_bit_timing_type_t bit_timing_type,
                                                              stm32_utils_fdcan_bit_timing_t *p_output_bit_timing,
                                                              stm32_utils_fdcan_output_config_t *p_output_config);

stm32_utils_fdcan_status_t STM32_UTILS_FDCAN_ComputeBitrate(const stm32_utils_fdcan_bit_timing_t *p_bit_timing,
                                                            uint32_t fdcan_clk_khz,
                                                            stm32_utils_fdcan_output_config_t *p_output_config);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_UTILS_FDCAN_H */
