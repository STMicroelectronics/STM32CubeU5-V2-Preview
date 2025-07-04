/**
  **********************************************************************************************************************
  * @file    stm32_utils_i2c.h
  * @brief   Header file of UTILS I2C module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32_UTILS_I2C_H
#define STM32_UTILS_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"
#include <stdint.h>


/** @addtogroup STM32_UTILS
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */

/**
  * @brief  I2C Utils Status structures definition
  */
typedef enum
{
  STM32_UTILS_I2C_OK            = 0x00000000U, /*!< Utils I2C operation completed successfully */
  STM32_UTILS_I2C_ERROR         = 0xFFFFFFFFU, /*!< Utils I2C operation completed with error   */
  STM32_UTILS_I2C_INVALID_PARAM = 0xAAAAAAAAU, /*!< Utils I2C invalid parameter                */
} stm32_utils_i2c_status_t;

/**
  * @brief  I2C Utils Analog Filter mode structures definition
  */
typedef enum
{
  STM32_UTILS_I2C_ANALOG_FILTER_DISABLED = 0x00000000U,  /*!< Analog filter is not enabled */
  STM32_UTILS_I2C_ANALOG_FILTER_ENABLED  = 0x00000001U,  /*!< Analog filter is enabled */
} stm32_utils_i2c_analog_filter_mode_t;

/**
  * @brief  I2C Utils SMBUS TimeoutA mode structures definition
  */
typedef enum
{
  STM32_UTILS_I2C_SMBUS_TIMEOUTA_MODE_SCL_LOW      = 0x00000000U,  /*!< timeouta is used to detect
                                                                        SCL low level timeout.               */
  STM32_UTILS_I2C_SMBUS_TIMEOUTA_MODE_SDA_SCL_HIGH = 0x00000001U,  /*!< timeouta is used to detect
                                                                        both SCL and SDA high level timeout. */
} stm32_utils_i2c_smbus_timeouta_mode_t;

/**
  * @brief  I2C Utils SMBUS Device mode structures definition
  */
typedef enum
{
  STM32_UTILS_I2C_SMBUS_MASTER_MODE = 0x00000001U,  /*!< Device in master mode */
  STM32_UTILS_I2C_SMBUS_SLAVE_MODE  = 0x00000000U,  /*!< Device in slave mode */
} stm32_utils_i2c_smbus_device_mode_t;

/**
  * @brief  I2C Utils Timings basic Configuration Structure definition
  */
typedef struct
{
  uint32_t clock_src_freq_hz; /*!< Specifie the I2C clock source in Hz.
                                   User can use HAL_I2C_GetClockFreq() to get the I2Cx clock source frequency.
                                   Very handy but this HAL service must be called after RCC configuration.
                                   That s why it is recommended to call it just before calling HAL_I2C_SetConfig. */

  uint32_t i2c_freq_hz;       /*!< Required I2C clock in Hz, for instance 4000000 for 400kHz on SCL */
} stm32_utils_i2c_timing_basic_config_t;


/**
  * @brief  I2C Utils TImings advanced Configuration Structure definition
  */
typedef struct
{
  uint32_t clock_src_freq_hz;              /*!< Clock source frequency in Hz */

  uint32_t i2c_freq_hz;                    /*!< I2C required bus clock in Hz */

  uint32_t trise_ns;                       /*!< Rise time max in ns */

  uint32_t tfall_ns;                       /*!< Fall time max in ns */

  uint32_t dnf;                            /*!< Digital noise filter coefficient.
                                                This parameter must be a number between Min_Data=0 and Max_Data=0x0F */

  stm32_utils_i2c_analog_filter_mode_t af; /*!< Analog filter mode. This parameter must be a value of
                                                @ref stm32_utils_i2c_analog_filter_mode_t */
} stm32_utils_i2c_timing_advanced_config_t;

/**
  * @brief  I2C SMBUS UTILS Timeout A Configuration Structure definition
  */
typedef struct
{
  uint32_t clock_src_freq_hz;                           /*!< Source clock frequency of I2C Instance */
  stm32_utils_i2c_smbus_timeouta_mode_t timeouta_mode;  /*!< IDLE Timeout mode. This parameter must be a value of
                                                             @ref stm32_utils_i2c_smbus_timeouta_mode_t */
  uint32_t timeout_ns;                                  /*!< Timeout to be applied in ns */
} stm32_utils_i2c_smbus_timeouta_config_t;

/**
  * @brief  I2C SMBUS UTILS Timeout B Configuration Structure definition
  */
typedef struct
{
  uint32_t clock_src_freq_hz;                             /*!< Source clock frequency of I2C Instance */
  stm32_utils_i2c_smbus_device_mode_t smbus_device_mode;  /*!< SMBUS device mode. This parameter must be a value of
                                                               @ref stm32_utils_i2c_smbus_device_mode_t */
  uint32_t timeout_ns;                                    /*!< Timeout to be applied in ns */
} stm32_utils_i2c_smbus_timeoutb_config_t;


/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup I2C_Exported_Functions
  * @{
  */
stm32_utils_i2c_status_t STM32_UTILS_I2C_ComputeTimingBasic(const stm32_utils_i2c_timing_basic_config_t *p_config,
                                                            uint32_t *p_output_timing_reg);
stm32_utils_i2c_status_t STM32_UTILS_I2C_ComputeAdvanced(const stm32_utils_i2c_timing_advanced_config_t *p_config,
                                                         uint32_t *p_output_timing_reg);
stm32_utils_i2c_status_t STM32_UTILS_I2C_SMBUS_ComputeTimeoutA(const stm32_utils_i2c_smbus_timeouta_config_t *p_config,
                                                               uint32_t *p_output_timeout_reg);
stm32_utils_i2c_status_t STM32_UTILS_I2C_SMBUS_ComputeTimeoutB(const stm32_utils_i2c_smbus_timeoutb_config_t *p_config,
                                                               uint32_t *p_output_timeout_reg);

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
#endif

#endif /* STM32_UTILS_I2C_H */
