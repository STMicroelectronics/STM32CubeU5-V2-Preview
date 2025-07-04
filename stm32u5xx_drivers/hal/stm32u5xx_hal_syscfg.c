/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_syscfg.c
  * @brief   SYSCFG HAL module driver.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2023-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{

# SYSCFG peripheral overview

The System Configuration Controller peripheral (SYSCFG) allows configuring and managing various system parameters.

This file provides firmware functions to manage the following functionalities :
   - Enabling/disabling the FMP high-drive mode of some I/Os and voltage booster for I/Os analog switches.
   - Adjust the HSPI supply capacitance.
   - Enabling/disabling the internal SRAMs cacheability by DCACHE2.
   - Configuring FPU interrupts.
   - Managing the I/O compensation cell.
   - Configuring the USB HS PHY.
   - Managing robustness feature.

# How to use the SYSCFG HAL module driver

## The SYSCFG HAL driver can be used as follows:

After startup, SYSCFG peripheral is not active by default. Use HAL_RCC_SYSCFG_EnableClock() function to enable
SYSCFG APB3 clock.

This module provides 7 different sets of APIs that allows to :

1. General management :
   This section provides global functions that can be used for various purposes
   - Configure the I/O analog switches supply:
     - This functionality is ensured by HAL_SYSCFG_SetAnalogIOSwitchSupply() function.
   - Get the I/O analog switches supply configuration:
     - This functionality is ensured by HAL_SYSCFG_GetAnalogIOSwitchSupply() function.
   - Enable and disable the fast mode plus capability:
     - These functionalities are ensured respectively by HAL_SYSCFG_EnableFastModePlus() and
       HAL_SYSCFG_DisableFastModePlus().
   - Get the fast mode plus capability state:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledFastModePlus() function.
   - Configure the decoupling capacitance on HSPI supply:
     - This functionality is ensured by HAL_SYSCFG_SetHSPISupplyDecouplingCapacitance() function.
   - Get the decoupling capacitance on HSPI supply configuration:
     - This functionality is ensured by HAL_SYSCFG_GetHSPISupplyDecouplingCapacitance() function.
   - Enable and disable the cacheability of internal SRAMx by DCACHE2:
     - These functionalities are ensured respectively by HAL_SYSCFG_EnableDCACHE2SRAMCacheability() and
       HAL_SYSCFG_DisableDCACHE2SRAMCacheability().
   - Get the cacheability of internal SRAMx by DCACHE2 state:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledDCACHE2SRAMCachability() function.

2. Manage floating point unit interrupts :
   Several APIs are available to manage the floating point unit interrupts
   - Enable and disable the floating point unit interrupts:
     - These functionalities are ensured respectively by HAL_SYSCFG_EnableFPUIT() and HAL_SYSCFG_DisableFPUIT().
   - Get the floating point unit interrupts state:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledFPUIT() function.

3. Manage TIM break inputs :
   This feature is used to control the system break interconnect to TIM1/8/15/16/17 break inputs
   - Enable the TIM break inputs:
     - This functionality is ensured by HAL_SYSCFG_EnableTIMBreakInputs() function.
   - Check the TIM break inputs activation:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledTIMBreakInputs() function.
   - \b Note: The TIM break inputs deactivation can only be done by a hardware reset.

4. Control the compensation cell :
   The SYSCFG can be configured to manage the compensation cell
   - Configure the compensation cell code selection :
     - This functionality is ensured by HAL_SYSCFG_SetConfigCompensationCellCode() function.
   - Get the compensation cell code configuration :
     - This functionality is ensured by HAL_SYSCFG_GetConfigCompensationCellCode() function.
   - Enable and disable the compensation cell activation :
     - These functionalities are ensured respectively by HAL_SYSCFG_EnableCompensationCell() and
       HAL_SYSCFG_DisableCompensationCell().
   - Get the compensation cell state:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledCompensationCell() function.

5. Manage the compensation code :
   Several APIs are available to mange the compensation code
   - Get the compensation value of PMOS transistor :
     - This functionality is ensured by HAL_SYSCFG_GetPMOSCompensationCellValue() function.
   - Get the compensation value of NMOS transistor :
     - This functionality is ensured by HAL_SYSCFG_GetNMOSCompensationCellValue() function.
   - Configure the compensation code:
     - This functionality is ensured by HAL_SYSCFG_SetxMOSCompensationCellCode() function.
   - Get the compensation code configuration :
     - This functionality is ensured by HAL_SYSCFG_GetxMOSCompensationCellCode() function.

6. USB HS PHY configuration:
   Several APIs are available to control the USB HS PHY
   - Enable and disable the USB HS PHY feature :
     - These functionalities are ensured respectively by HAL_SYSCFG_EnableUSBHSPHY() and HAL_SYSCFG_DisableUSBHSPHY().
   - Get the USB HS PHY state:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledUSBHSPHY() function.
   - Enable and disable the USB HS PHY power down:
     - These functionalities are ensured respectively by HAL_SYSCFG_EnableUSBHSPHYPowerDown() and
       HAL_SYSCFG_DisableUSBHSPHYPowerDown().
   - Get the USB HS PHY power down state:
     - This functionality is ensured by HAL_SYSCFG_IsEnabledUSBHSPHYPowerDown() function.
   - Configure the USB HS PHY reference clock frequency selection:
     - This functionality is ensured by HAL_SYSCFG_SetUSBHSPHYReferenceClockFrequency() function.
   - Get the USB HS PHY reference clock frequency configuration :
     - This functionality is ensured by HAL_SYSCFG_GetUSBHSPHYReferenceClockFrequency() function.

7. Control USB HS PHY tune:
   Several APIs are available to control the USB HS PHY
   - Configure all USB HS PHY tune simultaneously:
     - This functionality is ensured by HAL_SYSCFG_SetConfigUSBHSPHY() function.
   - Get all USB HS PHY tune simultaneously:
     - This functionality is ensured by HAL_SYSCFG_GetConfigUSBHSPHY() function.
   - Configure the USB HS PHY disconnect threshold adjustment:
     - This functionality is ensured by HAL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment() function.
   - Get the USB HS PHY disconnect threshold adjustment configuration :
     - This functionality is ensured by HAL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment() function.
   - Configure the USB HS PHY squelch threshold adjustment:
     - This functionality is ensured by HAL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment() function.
   - Get the USB HS PHY squelch threshold adjustment configuration :
     - This functionality is ensured by HAL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment() function.
   - Configure the USB HS PHY transmitter preemphasis current :
     - This functionality is ensured by HAL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent() function.
   - Get the USB HS PHY transmitter preemphasis current configuration :
     - This functionality is ensured by HAL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent() function.

## Configuration inside the SYSCFG driver

Config defines        | Description        | Default value | Note
----------------------| -------------------| ------------- | -----------------------------------------------------------
USE_HAL_SYSCFG_MODULE | from hal_conf.h    | 1U            | When set to 1, the HAL SYSCFG module is enabled.
USE_ASSERT_DBG_PARAM  | from IDE           | None          | When defined, enable the params assert.
  */

#if defined(USE_HAL_SYSCFG_MODULE) && (USE_HAL_SYSCFG_MODULE == 1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/** @defgroup SYSCFG_Private_Constants SYSCFG Private Constants
  * @{
  */
#define SYSCFG_CCELL_MAX_DELAY_MS  50U   /*!< Max compensation cell timeout value (unit: milliseconds) */
#define HAL_SYSCFG_CCELL_SIZE      0x0FU /*!< Max size of compensation code                            */
/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

/*! Decoupling capacitance check macro */
#define IS_SYSCFG_DECOUPLING_CAPACITANCE(capacitance)     \
  (((capacitance) == HAL_SYSCFG_CAPACITANCE_OFF)          \
   || ((capacitance) == HAL_SYSCFG_CAPACITANCE_1_DIV_3)   \
   || ((capacitance) == HAL_SYSCFG_CAPACITANCE_2_DIV_3)   \
   || ((capacitance) == HAL_SYSCFG_CAPACITANCE_FULL))

/*! Analog switch supply check macro */
#define IS_SYSCFG_ANALOG_SWITCH_SUPPLY(analog_switch) \
  (((analog_switch) == HAL_SYSCFG_VDDA_SUPPLY)        \
   || ((analog_switch) == HAL_SYSCFG_BOOSTER_SUPPLY)  \
   || ((analog_switch) == HAL_SYSCFG_VDD_SUPPLY))

/*! Fast mode plus check macro */
#define IS_SYSCFG_FAST_MODE_PLUS(fast_mode_plus)           \
  ((((fast_mode_plus) & (HAL_SYSCFG_DRIVE_ALL)) != 0U)     \
   && (((fast_mode_plus) & (~HAL_SYSCFG_DRIVE_ALL)) == 0U))

/*! Get fast mode plus check macro */
#define IS_SYSCFG_GET_FAST_MODE_PLUS(fast_mode_plus) \
  (((fast_mode_plus) == (HAL_SYSCFG_DRIVE_PB6))      \
   || ((fast_mode_plus) == (HAL_SYSCFG_DRIVE_PB7))   \
   || ((fast_mode_plus) == (HAL_SYSCFG_DRIVE_PB8))   \
   || ((fast_mode_plus) == (HAL_SYSCFG_DRIVE_PB9)))

/*! Set floating point unit interrupts check macro */
#define IS_SYSCFG_SET_FLOATING_POINT_IT(floating_point)     \
  ((((floating_point) & (HAL_SYSCFG_IT_FPU_ALL)) != 0U)     \
   && (((floating_point) & (~HAL_SYSCFG_IT_FPU_ALL)) == 0U))

/*! Get floating point unit interrupts check macro */
#define IS_SYSCFG_GET_FLOATING_POINT_IT(floating_point) \
  (((floating_point) == (HAL_SYSCFG_IT_FPU_IOC))        \
   || ((floating_point) == (HAL_SYSCFG_IT_FPU_DZC))     \
   || ((floating_point) == (HAL_SYSCFG_IT_FPU_UFC))     \
   || ((floating_point) == (HAL_SYSCFG_IT_FPU_OFC))     \
   || ((floating_point) == (HAL_SYSCFG_IT_FPU_IDC))     \
   || ((floating_point) == (HAL_SYSCFG_IT_FPU_IXC)))

/*! TIM break inputs check macro */
#define IS_SYSCFG_TIM_BREAK_INPUTS(break_input)                   \
  ((((break_input) & HAL_SYSCFG_TIM_BREAK_INPUTS_ALL) != 0U)      \
   && (((break_input) & (~HAL_SYSCFG_TIM_BREAK_INPUTS_ALL)) == 0U))

/*! Get TIM break inputs check macro */
#define IS_SYSCFG_GET_TIM_BREAK_INPUTS(break_input)       \
  (((break_input) == HAL_SYSCFG_FLASH_ECC_DOUBLE_ERROR)   \
   || ((break_input) == HAL_SYSCFG_PVD)                   \
   || ((break_input) == HAL_SYSCFG_SRAM_ECC_DOUBLE_ERROR) \
   || ((break_input) == HAL_SYSCFG_LOCKUP_OUT))

/*! Compensation cell check macro */
#define IS_SYSCFG_CCELL(comp_cell)                    \
  ((((comp_cell) & HAL_SYSCFG_CCELL_ALL) != 0U)       \
   && (((comp_cell) & (~HAL_SYSCFG_CCELL_ALL)) == 0U))

/*! Compensation code check macro */
#define IS_SYSCFG_CCELL_CODE(code_select)             \
  (((code_select) == HAL_SYSCFG_CCELL_CODE_DEFAULT)   \
   || ((code_select) == HAL_SYSCFG_CCELL_CODE_CUSTOM))

/*! Get compensation cell check macro */
#if defined(SYSCFG_CCCSR_EN3)
#define IS_SYSCFG_GET_CCELL(comp_cell)             \
  (((comp_cell) == HAL_SYSCFG_CCELL_VDDIO)         \
   || ((comp_cell) == HAL_SYSCFG_CCELL_VDDIO2)     \
   || ((comp_cell) == HAL_SYSCFG_CCELL_HSPIIO))
#else
#define IS_SYSCFG_GET_CCELL(comp_cell)             \
  (((comp_cell) == HAL_SYSCFG_CCELL_VDDIO)         \
   || ((comp_cell) == HAL_SYSCFG_CCELL_VDDIO2))
#endif /* SYSCFG_CCCSR_EN3 */

/*! XMOS compensation cell check macro */
#define IS_SYSCFG_XMOS_CCELL_CODE(pmos_code,nmos_code) \
  (((pmos_code) <= HAL_SYSCFG_CCELL_SIZE)              \
   && ((nmos_code) <= HAL_SYSCFG_CCELL_SIZE))

#if defined(SYSCFG_OTGHSPHYCR_EN)
/*! USB HS PHY reference clock frequency check macro */
#define IS_SYSCFG_USBHSPHY_FREQUENCY(clk_frequency) \
  (((clk_frequency) == HAL_SYSCFG_USBHSPHY_16MHZ)         \
   ||((clk_frequency) == HAL_SYSCFG_USBHSPHY_19_2MHZ)     \
   ||((clk_frequency) == HAL_SYSCFG_USBHSPHY_20MHZ)       \
   ||((clk_frequency) == HAL_SYSCFG_USBHSPHY_24MHZ)       \
   ||((clk_frequency) == HAL_SYSCFG_USBHSPHY_26MHZ)       \
   ||((clk_frequency) == HAL_SYSCFG_USBHSPHY_32MHZ))

/*! USB HS PHY squelch threshold adjustment check macro */
#define IS_SYSCFG_USBHSPHY_SQUELCH(squelch_threshold)                    \
  (((squelch_threshold) == HAL_SYSCFG_SQUELCH_ADJUST_0_PERCENT)          \
   || ((squelch_threshold) == HAL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT))

/*! USB HS PHY transmitter preemphasis current check macro */
#define IS_SYSCFG_USBHSPHY_SRC_CURRENT(src_current) \
  (((src_current) == HAL_SYSCFG_SRC_CURRENT_NO)     \
   ||((src_current) == HAL_SYSCFG_SRC_CURRENT_1 )   \
   ||((src_current) == HAL_SYSCFG_SRC_CURRENT_2 )   \
   ||((src_current) == HAL_SYSCFG_SRC_CURRENT_3 ))

/*! USB HS PHY Disconnect threshold adjustment check macro */
#define IS_SYSCFG_USBHSPHY_DISCONNECT(disconnect_threshold)              \
  (((disconnect_threshold) == HAL_SYSCFG_DIS_ADJUST_0_PERCENT)           \
   || ((disconnect_threshold) == HAL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT))
#endif /* SYSCFG_OTGHSPHYCR_EN */
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup SYSCFG_Exported_Functions
  * @{
  */

/** @addtogroup SYSCFG_Exported_Functions_Group1
  * @{
  This section provides functions allowing to global functions :
  - Call HAL_SYSCFG_SetAnalogIOSwitchSupply() function to set the I/O analog switches supply.
  - Call HAL_SYSCFG_GetAnalogIOSwitchSupply() function to get the I/O analog switches supply.
  - Call HAL_SYSCFG_EnableFastModePlus() function to enable the fast mode plus capability.
  - Call HAL_SYSCFG_DisableFastModePlus() function to disable the fast mode plus capability.
  - Call HAL_SYSCFG_IsEnabledFastModePlus() function to check that fast mode plus capability is enabled.
  - Call HAL_SYSCFG_SetHSPISupplyDecouplingCapacitance() function to set the decoupling capacitance on HSPI supply.
  - Call HAL_SYSCFG_GetHSPISupplyDecouplingCapacitance() function to get the decoupling capacitance on HSPI supply.
  - Call HAL_SYSCFG_EnableDCACHE2SRAMCacheability() function to enable the Cacheability of internal SRAMx by DCACHE2.
  - Call HAL_SYSCFG_DisableDCACHE2SRAMCacheability() function to disable the Cacheability of internal SRAMx by DCACHE2.
  - Call HAL_SYSCFG_IsEnabledDCACHE2SRAMCacheability() function to check if the Cacheability of internal SRAMx
    by DCACHE2 is enabled or disabled.
  */

/**
  * @brief  Set the I/O analog switch supply.
  * @param  analog_switch This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_VDDA_SUPPLY
  *         @arg @ref HAL_SYSCFG_BOOSTER_SUPPLY
  *         @arg @ref HAL_SYSCFG_VDD_SUPPLY
  */
void HAL_SYSCFG_SetAnalogIOSwitchSupply(hal_syscfg_analog_switch_t analog_switch)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_ANALOG_SWITCH_SUPPLY(analog_switch));

  LL_SYSCFG_SetAnalogIOSwitchSupply((uint32_t)analog_switch);
}

/**
  * @brief  Get the I/O analog switch supply.
  * @retval hal_syscfg_analog_switch_t I/O Analog switch supply.
  */
hal_syscfg_analog_switch_t HAL_SYSCFG_GetAnalogIOSwitchSupply(void)
{
  return (hal_syscfg_analog_switch_t) LL_SYSCFG_GetAnalogIOSwitchSupply();
}

/**
  * @brief  Enable the fast mode plus driving capability.
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_DRIVE_PB6
  *         @arg @ref HAL_SYSCFG_DRIVE_PB7
  *         @arg @ref HAL_SYSCFG_DRIVE_PB8
  *         @arg @ref HAL_SYSCFG_DRIVE_PB9
  */
void HAL_SYSCFG_EnableFastModePlus(uint32_t fast_mode_plus)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_FAST_MODE_PLUS(fast_mode_plus));

  LL_SYSCFG_EnableFastModePlus(fast_mode_plus);
}

/**
  * @brief  Disable the fast mode plus driving capability.
  * @param  fast_mode_plus This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_DRIVE_PB6
  *         @arg @ref HAL_SYSCFG_DRIVE_PB7
  *         @arg @ref HAL_SYSCFG_DRIVE_PB8
  *         @arg @ref HAL_SYSCFG_DRIVE_PB9
  */
void HAL_SYSCFG_DisableFastModePlus(uint32_t fast_mode_plus)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_FAST_MODE_PLUS(fast_mode_plus));

  LL_SYSCFG_DisableFastModePlus(fast_mode_plus);
}

/**
  * @brief  Check that fast mode plus driving capability is enabled.
  * @param  fast_mode_plus This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_DRIVE_PB6
  *         @arg @ref HAL_SYSCFG_DRIVE_PB7
  *         @arg @ref HAL_SYSCFG_DRIVE_PB8
  *         @arg @ref HAL_SYSCFG_DRIVE_PB9
  * @retval hal_syscfg_fast_mode_plus_status_t Fast mode plus status
  */
hal_syscfg_fast_mode_plus_status_t HAL_SYSCFG_IsEnabledFastModePlus(uint32_t fast_mode_plus)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_FAST_MODE_PLUS(fast_mode_plus));

  return (hal_syscfg_fast_mode_plus_status_t)LL_SYSCFG_IsEnabledFastModePlus(fast_mode_plus);
}

#if defined(SYSCFG_CFGR1_ENDCAP)
/**
  * @brief  Set the decoupling capacitance on HSPI supply.
  * @param  capacitance This parameter is an element of \ref hal_syscfg_capacitance_t enumeration.
  */
void HAL_SYSCFG_SetHSPISupplyDecouplingCapacitance(hal_syscfg_capacitance_t capacitance)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_DECOUPLING_CAPACITANCE(capacitance));

  LL_SYSCFG_SetHSPISupplyDecouplingCapacitance((uint32_t) capacitance);
}

/**
  * @brief  Get the decoupling capacitance on HSPI supply.
  * @retval hal_syscfg_capacitance_t Decoupling capacitance value.
  */
hal_syscfg_capacitance_t HAL_SYSCFG_GetHSPISupplyDecouplingCapacitance(void)
{
  return ((hal_syscfg_capacitance_t)LL_SYSCFG_GetHSPISupplyDecouplingCapacitance());
}
#endif /* SYSCFG_CFGR1_ENDCAP */

#if defined(SYSCFG_CFGR1_SRAMCACHED)
/**
  * @brief  Enable the cacheability of internal SRAMx by DCACHE2.
  */
void HAL_SYSCFG_EnableDCACHE2SRAMCacheability(void)
{
  LL_SYSCFG_EnableDCACHE2SRAMCacheability();
}

/**
  * @brief  Disable the cacheability of internal SRAMx by DCACHE2.
  */
void HAL_SYSCFG_DisableDCACHE2SRAMCacheability(void)
{
  LL_SYSCFG_DisableDCACHE2SRAMCacheability();
}

/**
  * @brief  Check that cacheability of internal SRAMx by DCACHE2 is enabled.
  * @retval hal_syscfg_dcache2_sram_status_t DCACHE2 SRAM capability status.
  */
hal_syscfg_dcache2_sram_status_t HAL_SYSCFG_IsEnabledDCACHE2SRAMCacheability(void)
{
  return (hal_syscfg_dcache2_sram_status_t)LL_SYSCFG_IsEnabledDCACHE2SRAMCacheability();
}
#endif /* SYSCFG_CFGR1_SRAMCACHED */
/**
  * @}
  */

/** @addtogroup SYSCFG_Exported_Functions_Group2
  * @{
  This section provides functions allowing to manage the floating point interrupts:
  - Call HAL_SYSCFG_EnableFPUIT() to enable floating point unit interrupts.
  - Call HAL_SYSCFG_DisableFPUIT() to disable floating point unit Interrupts.
  - Call HAL_SYSCFG_IsEnabledFPUIT() to check that floating point unit Interrupts is enabled.
  */

/**
  * @brief  Enable the floating point unit interrupts.
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_IT_FPU_IOC
  *         @arg @ref HAL_SYSCFG_IT_FPU_DZC
  *         @arg @ref HAL_SYSCFG_IT_FPU_UFC
  *         @arg @ref HAL_SYSCFG_IT_FPU_OFC
  *         @arg @ref HAL_SYSCFG_IT_FPU_IDC
  *         @arg @ref HAL_SYSCFG_IT_FPU_IXC
  *         @arg @ref HAL_SYSCFG_IT_FPU_ALL
  */
void HAL_SYSCFG_EnableFPUIT(uint32_t floating_point)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_SET_FLOATING_POINT_IT(floating_point));

  LL_SYSCFG_EnableFPUIT(floating_point);
}

/**
  * @brief  Disable the floating point unit interrupts.
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_IT_FPU_IOC
  *         @arg @ref HAL_SYSCFG_IT_FPU_DZC
  *         @arg @ref HAL_SYSCFG_IT_FPU_UFC
  *         @arg @ref HAL_SYSCFG_IT_FPU_OFC
  *         @arg @ref HAL_SYSCFG_IT_FPU_IDC
  *         @arg @ref HAL_SYSCFG_IT_FPU_IXC
  *         @arg @ref HAL_SYSCFG_IT_FPU_ALL
  */
void HAL_SYSCFG_DisableFPUIT(uint32_t floating_point)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_SET_FLOATING_POINT_IT(floating_point));

  LL_SYSCFG_DisableFPUIT(floating_point);
}

/**
  * @brief  Check that floating point unit interrupts is enabled.
  * @param  floating_point This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_IT_FPU_IOC
  *         @arg @ref HAL_SYSCFG_IT_FPU_DZC
  *         @arg @ref HAL_SYSCFG_IT_FPU_UFC
  *         @arg @ref HAL_SYSCFG_IT_FPU_OFC
  *         @arg @ref HAL_SYSCFG_IT_FPU_IDC
  *         @arg @ref HAL_SYSCFG_IT_FPU_IXC
  * @retval hal_syscfg_it_fpu_status_t Floating point interrupt status.
  */
hal_syscfg_it_fpu_status_t HAL_SYSCFG_IsEnabledFPUIT(uint32_t floating_point)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_FLOATING_POINT_IT(floating_point));

  return (hal_syscfg_it_fpu_status_t)LL_SYSCFG_IsenabledFPUIT(floating_point);
}
/**
  * @}
  */

/** @addtogroup SYSCFG_Exported_Functions_Group3
  * @{
  This section provides functions allowing to manage the TIM break inputs:
  - Call HAL_SYSCFG_EnableTIMBreakInputs() to enable the TIM break inputs.
  - Call HAL_SYSCFG_IsEnabledTIMBreakInputs() to check that the TIM break inputs is enabled.
  - \b Note: The TIM break inputs deactivation can only be done by a hardware reset.
  */
/**
  * @brief  Enable the TIM break inputs.
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SYSCFG_PVD
  *         @arg @ref HAL_SYSCFG_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SYSCFG_LOCKUP_OUT
  * @note   The TIM break input deactivation can only be done by a hardware reset.
  */
void HAL_SYSCFG_EnableTIMBreakInputs(uint32_t break_input)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_TIM_BREAK_INPUTS(break_input));

  LL_SYSCFG_EnableTIMBreakInputs(break_input);
}

/**
  * @brief  Check that TIM break inputs is enabled.
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SYSCFG_PVD
  *         @arg @ref HAL_SYSCFG_SRAM_ECC_DOUBLE_ERROR
  *         @arg @ref HAL_SYSCFG_LOCKUP_OUT
  * @retval hal_syscfg_tim_break_input_status_t TIM break inputs status.
  */
hal_syscfg_tim_break_input_status_t HAL_SYSCFG_IsEnabledTIMBreakInputs(uint32_t break_input)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_TIM_BREAK_INPUTS(break_input));

  return (hal_syscfg_tim_break_input_status_t)LL_SYSCFG_IsEnabledTIMBreakInputs(break_input);
}
/**
  * @}
  */

/** @addtogroup SYSCFG_Exported_Functions_Group4
  * @{
  This section provides functions allowing to control the compensation cell:
  - Call HAL_SYSCFG_SetConfigCompensationCellCode() to configure the code selection for each compensation cell.
  - Call HAL_SYSCFG_GetConfigCompensationCellCode() to get the compensation cell code.
  - Call HAL_SYSCFG_EnableCompensationCell() to enable the I/O compensation cell.
  - Call HAL_SYSCFG_DisableCompensationCell() to disable the I/O compensation cell.
  - Call HAL_SYSCFG_IsEnabledCompensationCell() to check that I/O compensation cell is enabled.
  */

/**
  * @brief  Configure the compensation cell code.
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *         @arg @ref HAL_SYSCFG_CCELL_ALL
  * @param  code_select This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_CODE_DEFAULT
  *         @arg @ref HAL_SYSCFG_CCELL_CODE_CUSTOM
  * @note   (*) value not defined in all devices
  */
void HAL_SYSCFG_SetConfigCompensationCellCode(uint32_t comp_cell, hal_syscfg_ccell_code_t code_select)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_CCELL_CODE(code_select));
  ASSERT_DBG_PARAM(IS_SYSCFG_CCELL(comp_cell));

  LL_SYSCFG_SetConfigCompensationCellCodeSource(comp_cell, (uint32_t)code_select);
}

/**
  * @brief  Get the compensation cell code.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval hal_syscfg_ccell_code_t Compensation cell code.
  */
hal_syscfg_ccell_code_t HAL_SYSCFG_GetConfigCompensationCellCode(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_CCELL(comp_cell));

  return (hal_syscfg_ccell_code_t)LL_SYSCFG_GetConfigCompensationCellCodeSource(comp_cell);
}

/**
  * @brief   Enable the I/O compensation cell.
  * @param   comp_cell This parameter can be one or a combination of the following values:
  *          @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *          @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *          @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *          @arg @ref HAL_SYSCFG_CCELL_ALL
  * @note    (*) value not defined in all devices
  * @warning Before enabling the VDDIO2 compensation cell, it is mandatory to ensure that the independent IO2 supply
  *          is enabled through the use of the HAL_PWR_EnableIndependentVddIO2Supply() function
  * @retval  hal_status_t Compensation cell status.
  */
hal_status_t HAL_SYSCFG_EnableCompensationCell(uint32_t comp_cell)
{
  uint32_t timeout = (SYSCFG_CCELL_MAX_DELAY_MS * (SystemCoreClock / 1000U)) + 1U;
  uint32_t comp_rdy1;
  uint32_t comp_rdy2;

#if defined(SYSCFG_CCCSR_EN3)
  uint32_t comp_rdy3;
#endif /* SYSCFG_CCCSR_EN3 */

  uint32_t comp_rdy;

  ASSERT_DBG_PARAM(IS_SYSCFG_CCELL(comp_cell));

  LL_SYSCFG_EnableCompensationCell(comp_cell);

  do
  {
    comp_rdy1 = LL_SYSCFG_IsActiveFlag_RDY1() << SYSCFG_CCCSR_EN1_Pos;
    comp_rdy2 = LL_SYSCFG_IsActiveFlag_RDY2() << SYSCFG_CCCSR_EN2_Pos;

#if defined(SYSCFG_CCCSR_EN3)
    comp_rdy3 = LL_SYSCFG_IsActiveFlag_RDY3() << SYSCFG_CCCSR_EN3_Pos;
#endif /* SYSCFG_CCCSR_EN3 */

#if defined(SYSCFG_CCCSR_EN3)
    comp_rdy = (comp_rdy1 | comp_rdy2 | comp_rdy3);
#else
    comp_rdy = (comp_rdy1 | comp_rdy2);
#endif /* SYSCFG_CCCSR_EN3 */

    timeout--;

  } while (((comp_rdy & comp_cell) != comp_cell) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the I/O compensation cell.
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *         @arg @ref HAL_SYSCFG_CCELL_ALL
  * @note   (*) value not defined in all devices
  */
void HAL_SYSCFG_DisableCompensationCell(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_CCELL(comp_cell));

  LL_SYSCFG_DisableCompensationCell(comp_cell);
}

/**
  * @brief  Check that I/O compensation cell is enabled.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval hal_syscfg_ccell_status_t I/O Compensation cell status.
  */
hal_syscfg_ccell_status_t HAL_SYSCFG_IsEnabledCompensationCell(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_CCELL(comp_cell));

  return ((hal_syscfg_ccell_status_t)LL_SYSCFG_IsEnabledCompensationCell(comp_cell));
}
/**
  * @}
  */

/** @addtogroup SYSCFG_Exported_Functions_Group5
  * @{
  This section provides functions allowing to manage backup domain write protection:
  - Call HAL_SYSCFG_GetPMOSCompensationCellValue() to get the PMOS compensation value of selected compensation cell.
  - Call HAL_SYSCFG_GetNMOSCompensationCellValue() to get the NMOS compensation value of selected compensation cell.
  - Call HAL_SYSCFG_SetxMOSCompensationCellCode() to set the compensation cell code.
  - Call HAL_SYSCFG_GetxMOSCompensationCellCode() to get the compensation cell code.
  */

/**
  * @brief  Get the PMOS compensation value.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval Returned value of the PMOS compensation cell
  */
uint32_t HAL_SYSCFG_GetPMOSCompensationCellValue(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_CCELL(comp_cell));

  return (LL_SYSCFG_GetPMOSCompensationCellValue(comp_cell));
}

/**
  * @brief  Get the NMOS compensation value of selected compensation cell.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval uint32_t Value of the NMOS compensation cell
  */
uint32_t HAL_SYSCFG_GetNMOSCompensationCellValue(uint32_t comp_cell)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_CCELL(comp_cell));

  return (LL_SYSCFG_GetNMOSCompensationCellValue(comp_cell));
}

/**
  * @brief  Set the compensation cell code.
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  *         @arg @ref HAL_SYSCFG_CCELL_ALL
  * @param  pmos_code Applied PMOS value of compensation cell
  * @param  nmos_code Applied NMOS value of compensation cell
  * @note   (*) value not defined in all devices
  */
void HAL_SYSCFG_SetxMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code, uint32_t nmos_code)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_CCELL(comp_cell));
  ASSERT_DBG_PARAM(IS_SYSCFG_XMOS_CCELL_CODE(pmos_code, nmos_code));

  if ((comp_cell & HAL_SYSCFG_CCELL_VDDIO) != 0U)
  {
    LL_SYSCFG_SetxMOSVddIOCompensationCellCode(pmos_code, nmos_code);
  }

  if ((comp_cell & HAL_SYSCFG_CCELL_VDDIO2) != 0U)
  {
    LL_SYSCFG_SetxMOSVddIO2CompensationCellCode(pmos_code, nmos_code);
  }

#if defined(SYSCFG_CCCSR_EN3)
  if ((comp_cell & HAL_SYSCFG_CCELL_HSPIIO) != 0U)
  {
    LL_SYSCFG_SetxMOSVddHSPIIOCompensationCellCode(pmos_code, nmos_code);
  }
#endif /* SYSCFG_CCCSR_EN3 */

}

/**
  * @brief  Get the compensation cell code.
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO
  *         @arg @ref HAL_SYSCFG_CCELL_VDDIO2
  * @if SYSCFG_CCCSR_EN3
  *         @arg @ref HAL_SYSCFG_CCELL_HSPIIO (*)
  * @endif
  * @param  p_pmos_code Pointer to PMOS register of selected compensation cell
  * @param  p_nmos_code Pointer to NMOS register of selected compensation cell
  * @note   (*) value not defined in all devices
  */
void HAL_SYSCFG_GetxMOSCompensationCellCode(uint32_t comp_cell, uint32_t *p_pmos_code, uint32_t *p_nmos_code)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_GET_CCELL(comp_cell));

  *p_pmos_code = (LL_SYSCFG_GetPMOSCompensationCellCode(comp_cell) >> (POSITION_VAL(comp_cell << 1U) * 4U));
  *p_nmos_code = (LL_SYSCFG_GetNMOSCompensationCellCode(comp_cell) >> (POSITION_VAL(comp_cell) * 4U));
}
/**
  * @}
  */

#if defined(SYSCFG_OTGHSPHYCR_EN)
/** @addtogroup SYSCFG_Exported_Functions_Group6
  * @{
  This section provides functions allowing to manage the USB HS PHY:
  - Call HAL_SYSCFG_EnableUSBHSPHY() to enable the USB HS PHY.
  - Call HAL_SYSCFG_DisableUSBHSPHY() to disable the USB HS PHY.
  - Call HAL_SYSCFG_IsEnabledUSBHSPHY() to check that USB HS PHY is enabled.
  - Call HAL_SYSCFG_EnableUSBHSPHYPowerDown() to enable the USB HS PHY power down control.
  - Call HAL_SYSCFG_DisableUSBHSPHYPowerDown() to disable the USB HS PHY power down control.
  - Call HAL_SYSCFG_IsEnabledUSBHSPHYPowerDown() to check that USB HS PHY power down is enabled.
  - Call HAL_SYSCFG_SetUSBHSPHYReferenceClockFrequency() to set the USB HS PHY reference clock frequency selection.
  - Call HAL_SYSCFG_GetUSBHSPHYReferenceClockFrequency() to get the USB HS PHY reference clock frequency selection.
  */

/**
  * @brief  Enable the USB HS PHY feature.
  */
void HAL_SYSCFG_EnableUSBHSPHY(void)
{
  LL_SYSCFG_EnableUSBHSPHY();
}

/**
  * @brief  Disable the USB HS PHY feature.
  */
void HAL_SYSCFG_DisableUSBHSPHY(void)
{
  LL_SYSCFG_DisableUSBHSPHY();
}

/**
  * @brief  Check that USB HS PHY is enabled.
  * @retval hal_syscfg_usbhsphy_status_t USB HS PHY status.
  */
hal_syscfg_usbhsphy_status_t HAL_SYSCFG_IsEnabledUSBHSPHY(void)
{
  return (hal_syscfg_usbhsphy_status_t) LL_SYSCFG_IsEnabledUSBHSPHY();
}

/**
  * @brief  Enable the USB HS PHY  Power Down control.
  */
void HAL_SYSCFG_EnableUSBHSPHYPowerDown(void)
{
  LL_SYSCFG_EnableUSBHSPHYPowerDown();
}

/**
  * @brief  Disable the USB HS PHY  Power Down control.
  */
void HAL_SYSCFG_DisableUSBHSPHYPowerDown(void)
{
  LL_SYSCFG_DisableUSBHSPHYPowerDown();
}

/**
  * @brief  Check that USB HS PHY power down control is enabled.
  * @retval hal_syscfg_usbhsphy_power_down_status_t USB HS PHY power down control status.
  */
hal_syscfg_usbhsphy_power_down_status_t  HAL_SYSCFG_IsEnabledUSBHSPHYPowerDown(void)
{
  return (hal_syscfg_usbhsphy_power_down_status_t) LL_SYSCFG_IsEnabledUSBHSPHYPowerDown();
}

/**
  * @brief  Set the USB HS  PHY reference clock frequency selection.
  * @param  clk_frequency This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_USBHSPHY_16MHZ
  *         @arg @ref HAL_SYSCFG_USBHSPHY_19_2MHZ
  *         @arg @ref HAL_SYSCFG_USBHSPHY_20MHZ
  *         @arg @ref HAL_SYSCFG_USBHSPHY_24MHZ
  *         @arg @ref HAL_SYSCFG_USBHSPHY_26MHZ
  *         @arg @ref HAL_SYSCFG_USBHSPHY_32MHZ
  */
void HAL_SYSCFG_SetUSBHSPHYReferenceClockFrequency(hal_syscfg_usbhsphy_frequency_t clk_frequency)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_FREQUENCY(clk_frequency));

  LL_SYSCFG_SetUSBHSPHYReferenceClockFrequency((uint32_t)clk_frequency);
}

/**
  * @brief  Get the USB PHY reference clock frequency selection.
  * @retval hal_syscfg_usbhsphy_frequency_t Reference clock frequency.
  */
hal_syscfg_usbhsphy_frequency_t HAL_SYSCFG_GetUSBHSPHYReferenceClockFrequency(void)
{
  return ((hal_syscfg_usbhsphy_frequency_t)LL_SYSCFG_GetUSBHSPHYReferenceClockFrequency());
}
/**
  * @}
  */
#endif /* SYSCFG_OTGHSPHYCR_EN */

#if defined(SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE)
/** @addtogroup SYSCFG_Exported_Functions_Group7
  * @{
  This section provides functions allowing to manage backup domain write protection:
  - Call HAL_SYSCFG_SetConfigUSBHSPHY() to set all the USB HS PHY tune simultaneously.
  - Call HAL_SYSCFG_GetConfigUSBHSPHY() to get all the USB HS PHY tune simultaneously.
  - Call HAL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment() to set the USB HS PHY Disconnect Threshold adjustment.
  - Call HAL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment() to get the USB HS PHY Disconnect Threshold adjustment.
  - Call HAL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment() to set the USB HS PHY squelch threshold adjustment.
  - Call HAL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment() to get the USB HS PHY squelch threshold adjustment.
  - Call HAL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent() to set the USB HS HS PHY transmitter preemphasis current.
  - Call HAL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent() to get the USB HS HS PHY transmitter preemphasis current.
  */

/**
  * @brief  Set all USB HS PHY tune simultaneously.
  * @param  disconnect_threshold This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_DIS_ADJUST_0_PERCENT
  *         @arg @ref HAL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT
  * @param  squelch_threshold This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_SQUELCH_ADJUST_0_PERCENT
  *         @arg @ref HAL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT
  * @param  src_current This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_NO
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_1
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_2
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_3
  */
void HAL_SYSCFG_SetConfigUSBHSPHY(hal_syscfg_disconnect_adjustment_t disconnect_threshold,
                                  hal_syscfg_squelch_adjust_t squelch_threshold, hal_syscfg_src_current_t src_current)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_DISCONNECT(disconnect_threshold));
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_SQUELCH(squelch_threshold));
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_SRC_CURRENT(src_current));

  LL_SYSCFG_SetConfigUSBHSPHY((uint32_t)disconnect_threshold, (uint32_t)squelch_threshold,
                              (uint32_t)src_current);
}

/**
  * @brief  Get the USB HS PHY tune.
  * @param  p_disconnect_threshold This parameter is a pointer of \ref hal_syscfg_disconnect_adjustment_t enumeration.
  * @param  p_squelch_threshold    This parameter is a pointer of \ref hal_syscfg_squelch_adjust_t enumeration.
  * @param  p_src_current          This parameter is a pointer of \ref hal_syscfg_src_current_t enumeration.
  */
void HAL_SYSCFG_GetConfigUSBHSPHY(hal_syscfg_disconnect_adjustment_t *p_disconnect_threshold,
                                  hal_syscfg_squelch_adjust_t *p_squelch_threshold,
                                  hal_syscfg_src_current_t *p_src_current)
{
  uint32_t reg_value = (LL_SYSCFG_READ_REG(OTGHSPHYTUNER2) &                              \
                        (SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE | SYSCFG_OTGHSPHYTUNER2_SQRXTUNE | \
                         SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE));

  *p_disconnect_threshold = (hal_syscfg_disconnect_adjustment_t)(uint32_t)(reg_value &
                                                                           SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE);
  *p_squelch_threshold    = (hal_syscfg_squelch_adjust_t)(uint32_t)(reg_value & SYSCFG_OTGHSPHYTUNER2_SQRXTUNE);
  *p_src_current          = (hal_syscfg_src_current_t)(uint32_t)(reg_value & SYSCFG_OTGHSPHYTUNER2_TXPREEMPAMPTUNE);
}

/**
  * @brief  Set the USB HS PHY disconnect threshold adjustment.
  * @param  disconnect_threshold This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_DIS_ADJUST_0_PERCENT
  *         @arg @ref HAL_SYSCFG_DIS_ADJUST_PLUS_5_9_PERCENT
  */
void HAL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment(hal_syscfg_disconnect_adjustment_t disconnect_threshold)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_DISCONNECT(disconnect_threshold));

  LL_SYSCFG_SetUSBHSPHYDisconnectThresholdAdjustment((uint32_t)disconnect_threshold);
}

/**
  * @brief  Get the USB HS PHY disconnect Threshold adjustment.
  * @retval hal_syscfg_disconnect_adjustment_t Disconnect threshold adjustment value.
  */
hal_syscfg_disconnect_adjustment_t HAL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment(void)
{
  return ((hal_syscfg_disconnect_adjustment_t)LL_SYSCFG_GetUSBHSPHYDisconnectThresholdAdjustment());
}


/**
  * @brief  Adjust the voltage level for the threshold used to detect valid high speed data.
  * @param  squelch_threshold This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_SQUELCH_ADJUST_0_PERCENT
  *         @arg @ref HAL_SYSCFG_SQUELCH_ADJUST_PLUS_15_PERCENT
  */
void HAL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment(hal_syscfg_squelch_adjust_t squelch_threshold)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_SQUELCH(squelch_threshold));

  LL_SYSCFG_SetUSBHSPHYSquelchThresholdAdjustment((uint32_t)squelch_threshold);
}

/**
  * @brief  Get the USB HS PHY disconnect threshold adjustment.
  * @retval hal_syscfg_squelch_adjust_t Squelch threshold adjustment value.
  */
hal_syscfg_squelch_adjust_t HAL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment(void)
{
  return ((hal_syscfg_squelch_adjust_t)LL_SYSCFG_GetUSBHSPHYSquelchThresholdAdjustment());
}

/**
  * @brief  Set the USB HS PHY transmitter preemphasis Current control.
  * @param  src_current This parameter can be one of the following values:
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_NO
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_1
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_2
  *         @arg @ref HAL_SYSCFG_SRC_CURRENT_3
  */
void HAL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent(hal_syscfg_src_current_t src_current)
{
  ASSERT_DBG_PARAM(IS_SYSCFG_USBHSPHY_SRC_CURRENT(src_current));

  LL_SYSCFG_SetUSBHSPHYTransmitterPreemphasisCurrent((uint32_t)src_current);
}

/**
  * @brief  Get the USB HS PHY transmitter preemphasis Current control.
  * @retval hal_syscfg_src_current_t Transmitter preemphasis Current control.
  */
hal_syscfg_src_current_t HAL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent(void)
{
  return ((hal_syscfg_src_current_t)LL_SYSCFG_GetUSBHSPHYTransmitterPreemphasisCurrent());
}
/**
  * @}
  */
#endif /* SYSCFG_OTGHSPHYTUNER2_COMPDISTUNE */

/**
  * @}
  */
#endif /* USE_HAL_SYSCFG_MODULE */

/**
  * @}
  */

/**
  * @}
  */
