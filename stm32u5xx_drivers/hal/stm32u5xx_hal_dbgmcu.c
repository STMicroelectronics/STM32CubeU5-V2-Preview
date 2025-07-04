/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dbgmcu.c
  * @brief   DBGMCU HAL module driver.
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
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup DBGMCU
  * @{

# DBGMCU peripheral overview

The DBGMCU controls the power and the clock behaviours in debug mode.

This file provides firmware functions to manage the following features:
   - Get the revision identification and identification code of the device.
   - Maintain the clock and power to the system debug component when in low power modes
     (Stop0/1/2 and Standby modes).
   - Freeze and unfreeze the clock to certain peripherals when the CPU is stopped in debug mode.

# How to use the DBGMCU HAL module driver

## The DBGMCU HAL driver can be used as follows:

This module provides 3 different sets of APIs that allows to:

1. Identify the device:
   This feature is used to get information about the device.
   - Get the device revision:
     - This functionality is provided by HAL_DBGMCU_GetRevisionID() function.
   - Get the device identifier:
     - This functionality is provided by HAL_DBGMCU_GetDeviceID() function.

2. Debug during low power mode:
   Several APIs are available to debug peripherals during low power modes.
   - Enable, disable the debug module during Stop0/1/2 and Standby modes:
     - These functionalities are provided respectively by HAL_DBGMCU_EnableDebugLowPowerMode() and
       HAL_DBGMCU_DisableDebugLowPowerMode() functions.
   - Check if the debug module is enabled during Stop0/1/2 and Standby modes:
     - This functionality is provided by HAL_DBGMCU_IsEnabledDebugLowPowerMode() function.

3. Freeze and Unfreeze clock peripherals:
   The DBGMCU peripheral allows certain peripherals to be suspended in debug mode when the CPU is halted.
   - Freeze and unfreeze PPPi peripherals:
     - These functionalities are provided by HAL_DBGMCU_PPPi_Freeze() and HAL_DBGMCU_PPPi_UnFreeze() functions.

## Configuration inside the DBGMCU driver

Config defines        | Description        | Default value | Note
----------------------| ---------------    | ------------- | -----------------------------------------------------------
USE_HAL_DBGMCU_MODULE | from hal_conf.h    | 1U            | When set, HAL DBGMCU module is enabled.
USE_ASSERT_DBG_PARAM  | from IDE           | None          | When defined, enable the params assert.

  */

#if defined(USE_HAL_DBGMCU_MODULE) && (USE_HAL_DBGMCU_MODULE == 1U)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup DBGMCU_Private_Macros DBGMCU Private Macros
  * @{
  */

/*! Set Low power mode (Stop0/1/2 and Standby modes) check macro */
#define IS_DBGMCU_DEBUG_LP_MODE(mode)                    \
  ((((mode) & HAL_DBGMCU_LP_MODE_DEBUG_ALL)  != 0U)      \
   && (((mode) & (~HAL_DBGMCU_LP_MODE_DEBUG_ALL)) == 0U))

/*! Get low power mode (Stop0/1/2 and Standby modes) check macro */
#define IS_DBGMCU_GET_DEBUG_LP_MODE(mode)        \
  (((mode) == HAL_DBGMCU_STOP_MODE_DEBUG)        \
   || ((mode) == HAL_DBGMCU_STANDBY_MODE_DEBUG))
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @addtogroup DBGMCU_Exported_Functions
  * @{
  */

/** @addtogroup DBGMCU_Exported_Functions_Group1
  * @{
  This section provides functions allowing to get device identity:
  - Call HAL_DBGMCU_GetRevisionID() function to get the device revision identifier.
  - Call HAL_DBGMCU_GetDeviceID() function to get the device identifier.
  */

/**
  * @brief  Returns the device revision identifier.
  * @note   This field indicates the revision ID of the device.
  *         - For STM32U5Fx/5Gx:
  *             - 0x1000: revision A
  *         - For STM32U59x/5Ax:
  *             - 0x1000: revision A
  *             - 0x2000: revision B
  *             - 0x2001: revision Y
  *             - 0x3000: revision C
  *         - For STM32U575/585:
  *             - 0x1000: revision A
  *             - 0x1001: revision Z
  *             - 0x1003: revision Y
  *             - 0x2000: revision B
  *             - 0x2001: revision X
  *             - 0x3000: revision C
  *         - For STM32U535/545:
  *             - 0x1000: revision A
  * @retval uint32_t Value of device revision ID.
  */
uint32_t HAL_DBGMCU_GetRevisionID(void)
{
  return LL_DBGMCU_GetRevisionID();
}

/**
  * @brief  Returns the device identifier.
  * @retval HAL_DBGMCU_DEV_ID_U535_U545 STM32U5 device ID for STM32U545/535.
  * @retval HAL_DBGMCU_DEV_ID_U575_U585 STM32U5 device ID for STM32U575/585.
  * @retval HAL_DBGMCU_DEV_ID_U595_U5A5 STM32U5 device ID for STM32U59x/5Ax.
  * @retval HAL_DBGMCU_DEV_ID_U5F5_U5G5 STM32U5 device ID for STM32U5Fx/5Gx.
  */
hal_dbgmcu_device_id_t HAL_DBGMCU_GetDeviceID(void)
{
  return (hal_dbgmcu_device_id_t)LL_DBGMCU_GetDeviceID();
}
/**
  * @}
  */

/** @addtogroup DBGMCU_Exported_Functions_Group2
  * @{
  This section provides functions allowing to debug peripherals during low power mode
  (Stop0/1/2 and Standby modes):
  - Call HAL_DBGMCU_EnableDebugLowPowerMode() function to enable the debug module during
    Stop0/1/2 and Standby modes.
  - Call HAL_DBGMCU_DisableDebugLowPowerMode() function to disable the debug module during
    Stop0/1/2 and Standby modes.
  - Call HAL_DBGMCU_IsEnabledDebugLowPowerMode() function to check the debug module during
    Stop0/1/2 and Standby modes activation.
  */

/**
  * @brief Enable the Debug Module during low power mode (Stop0/1/2 and Standby modes).
  * @param mode This parameter can be one or a combination of the following values:
  *             @arg HAL_DBGMCU_STOP_MODE_DEBUG    : Debug during Stop modes.
  *             @arg HAL_DBGMCU_STANDBY_MODE_DEBUG : Debug during Standby mode.
  *             @arg HAL_DBGMCU_LP_MODE_DEBUG_ALL  : Debug during all Low power modes.
  */
void HAL_DBGMCU_EnableDebugLowPowerMode(uint32_t mode)
{
  ASSERT_DBG_PARAM(IS_DBGMCU_DEBUG_LP_MODE(mode));

  LL_DBGMCU_EnableDebugLowPowerMode(mode);
}

/**
  * @brief Disable the Debug Module during low power mode (Stop0/1/2 and Standby modes).
  * @param mode This parameter can be one or a combination of the following values:
  *             @arg HAL_DBGMCU_STOP_MODE_DEBUG    : Debug during Stop modes.
  *             @arg HAL_DBGMCU_STANDBY_MODE_DEBUG : Debug during Standby mode.
  *             @arg HAL_DBGMCU_LP_MODE_DEBUG_ALL  : Debug during all Low power modes.
  */
void HAL_DBGMCU_DisableDebugLowPowerMode(uint32_t mode)
{
  ASSERT_DBG_PARAM(IS_DBGMCU_DEBUG_LP_MODE(mode));

  LL_DBGMCU_DisableDebugLowPowerMode(mode);
}

/**
  * @brief  Check that the Debug Module during low power mode (Stop0/1/2 and Standby modes)
  * is enabled.
  * @param  mode This parameter can be one of the following values:
  *             @arg HAL_DBGMCU_STOP_MODE_DEBUG    : Debug during Stop modes.
  *             @arg HAL_DBGMCU_STANDBY_MODE_DEBUG : Debug during Standby mode.
  * @retval hal_dbgmcu_dbg_low_power_mode_status_t Debug in low power mode activation.
  */
hal_dbgmcu_dbg_low_power_mode_status_t HAL_DBGMCU_IsEnabledDebugLowPowerMode(uint32_t mode)
{
  ASSERT_DBG_PARAM(IS_DBGMCU_GET_DEBUG_LP_MODE(mode));

  return ((hal_dbgmcu_dbg_low_power_mode_status_t)LL_DBGMCU_IsEnabledDebugLowPowerMode(mode));
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_DBGMCU_MODULE */
/**
  * @}
  */

/**
  * @}
  */
