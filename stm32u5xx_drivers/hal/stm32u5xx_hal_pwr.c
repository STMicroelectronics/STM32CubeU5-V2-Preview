/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_pwr.c
  * @brief   PWR HAL module driver.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
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

/** @addtogroup PWR
  * @{

# PWR peripheral overview

The Power control peripheral (PWR) provides an overview of the supply architecture for the different power domains
and of the supply configuration controller.

This file provides firmware functions to manage the following functionalities :
   - Wakeup pins management functions.
   - RTC domain write protection management functions.
   - Main regulator management functions.
   - Low power mode management functions.
   - Voltage monitoring management functions.
   - Items retention management functions.
   - Items fast wakeup management functions.
   - Battery management functions.
   - I/O Pull management functions.

# How to use the PWR HAL module driver

## The PWR HAL driver can be used as follows:

This module manages all device power supplies and power modes transitions

After startup, power management peripheral is not active by default. Use HAL_RCC_PWR_EnableClock() function to enable
power interface.

This module provides 9 different set of APIs that allows to :

1. Configure the wakeup pin :
   The wakeup pin is used to wakeup the system from low power modes.
   - Configure the wakeup pin polarity and selection independently and without enabling it :
     - This functionality is ensured by HAL_PWR_LP_SetConfigWakeupPin() function. The p_config pointer allows to
       configure wakeup polarity and selection.
       - When p_config is null,this function returns an HAL_INVALID_PARAM.
   - Get the wakeup pin polarity and selection configuration:
     - This functionality is ensured by HAL_PWR_LP_GetConfigWakeupPin() function.
   - Enable, disable and check the wakeup pin :
     - These functionalities are ensured respectively by HAL_PWR_LP_EnableWakeupPin(), HAL_PWR_LP_DisableWakeupPin() and
       HAL_PWR_LP_IsEnabledWakeupPin() functions.

2. Manage the RTC domain write protection :
   After a system reset, the RTC domain is protected against possible unwanted write accesses.
   - Enable, disable and check the write access to RTC domain :
     - These functionalities are ensured respectively by HAL_PWR_EnableRTCDomainWriteProtection(),
       HAL_PWR_DisableRTCDomainWriteProtection() and HAL_PWR_IsEnabledRTCDomainWriteProtection() functions.

3. Control power supply :
   The power supplies can be configured to manage application power consumption and performance.
   - Configure the main regulator voltage scaling range for different power modes :
     - This functionality is ensured by HAL_PWR_SetMainRegulatorVoltageScalingRange() function.
   - Get the voltage scaling range configuration :
     - This functionality is ensured by HAL_PWR_GetMainRegulatorVoltageScalingRange() function.
   - Configure the main regulator supply:
     - This functionality is ensured by HAL_PWR_SetMainRegulatorSupply() function.
   - Get the main regulator supply configuration :
     - This functionality is ensured by HAL_PWR_GetMainRegulatorSupply() function.
   - Set and get the main regulator fast startup mode:
     - These functionalities are ensured respectively by HAL_PWR_SetMainRegulatorStartupMode()
       and HAL_PWR_GetMainRegulatorStartupMode() functions.
   - Configure the analog IO switch supply:
     - This functionality is ensured by HAL_PWR_SetAnalogIOSwitchSupply() function.
   - Get the analog IO switch supply:
     - This functionality is ensured by HAL_PWR_GetAnalogIOSwitchSupply() function.
   - Enable, disable and check the Vdd USB independent supply:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddUSBIndependentSupply(),
       HAL_PWR_DisableVddUSBIndependentSupply() and HAL_PWR_IsEnabledVddUSBIndependentSupply() functions.
   - Enable, disable and check the Vdd IO2 independent supply:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddIO2IndependentSupply(),
       HAL_PWR_DisableVddIO2IndependentSupply() and HAL_PWR_IsEnabledVddIO2IndependentSupply() functions.
   - Enable, disable and check the Vdd analog independent supply:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddAIndependentSupply(),
       HAL_PWR_DisableVddAIndependentSupply() and HAL_PWR_IsEnabledVddAIndependentSupply() functions.
   - Enable, disable and check the Vdd11 USB independent supply: (*)
     - These functionalities are ensured respectively by HAL_PWR_EnableVdd11USBIndependentSupply(),
       HAL_PWR_DisableVdd11USBIndependentSupply() and HAL_PWR_IsEnabledVdd11USBIndependentSupply() functions.
   - Enable, disable and check the internal USB HS transceiver supply: (*)
     - These functionalities are ensured respectively by HAL_PWR_EnableVddUSBHSTransceiverSupply(),
       HAL_PWR_DisableVddUSBHSTransceiverSupply() and HAL_PWR_IsEnabledVddUSBHSTransceiverSupply() functions.
     - (*) feature not available in all devices

4. Manage low power mode:
   Several power modes are available to manage power consumption.
   - Clear Core pending event to clear internal cortex event before entring sleep or stop mode:
     - This functionality is ensured by HAL_PWR_ClearCorePendingEvent() function.
   - Enter the MCU to low power modes:
     - Enter the MCU to sleep mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterSleepMode() function.
     - Enter the MCU to stop x mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterStopMode() function.
     - Enter the MCU to standby mode:
       - This functionality is ensured by HAL_PWR_EnterStandbyMode() function.
     - Enter the MCU to shutdown mode:
       - This functionality is ensured by HAL_PWR_EnterShutdownMode() function.
   - Configure the core deep sleep mode:
     - This functionality is ensured by HAL_PWR_SetCoreSleepMode() function.
   - Get the core deep sleep mode configuration:
     - This functionality is ensured by HAL_PWR_GetCoreSleepMode() function.
   - Enable and disable and check the core sleep on exit to re-entry in sleep mode after an interruption is over:
     - These functionalities are ensured respectively by HAL_PWR_EnableCoreSleepOnExit(),
         HAL_PWR_DisableCoreSleepOnExit() and HAL_PWR_IsEnabledCoreSleepOnExit() functions.
   - Enable, disable and check the core send event on pending to wakeup after any pending event/ interrupt:
     - these functionalities are ensured respectively by HAL_PWR_EnableCoreSendEventOnPending(),
         HAL_PWR_DisableCoreSendEventOnPending() and HAL_PWR_IsEnabledCoreSendEventOnPending() functions.
   - Set the Smart Run Domain mode when the system in stop mode (stop 0/1/2):
     - This functionality is ensured by HAL_PWR_LP_SetSmartRunDomainMode() function.
   - Get the SmartRun Domain state when the system in stop mode (stop 0/1/2):
     - This functionality is ensured by HAL_PWR_LP_GetSmartRunDomainMode() function.
   - Set the brownout reset mode in standby mode:
     - This functionality is ensured by HAL_PWR_LP_SetBrownoutResetMode() function.
   - Get the brownout reset mode:
     - This functionality is ensured by HAL_PWR_LP_GetBrownoutResetMode() function.
   - Handle the PWR wakeup interrupt from stop 3:
     - This functionality is ensured by HAL_PWR_Stop3Wakeup_IRQHandler() function.

5. Monitor configuration:
   The monitor can be used to manage the power supplies and supply domains.
   - Configure the voltage threshold detector by the programmable voltage detector:
     - This functionality is ensured by HAL_PWR_SetProgrammableVoltageDetectorLevel() function.
   - Get the programmable voltage detector configuration:
     - This functionality is ensured by HAL_PWR_GetProgrammableVoltageDetectorLevel() function.
   - Enable, disable and check the programmable voltage detector:
     - These functionalities are ensured respectively by HAL_PWR_EnableProgrammableVoltageDetector(),
       HAL_PWR_DisableProgrammableVoltageDetector() and  HAL_PWR_IsEnabledProgrammableVoltageDetector() functions.
   - Enable, disable and check the Vdd USB voltage monitor:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddUSBMonitor(), HAL_PWR_DisableVddUSBMonitor()
       and HAL_PWR_IsEnabledVddUSBMonitor() functions.
   - Enable, disable and check the Vdd IO2 voltage monitor:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddIO2Monitor(), HAL_PWR_DisableVddIO2Monitor()
       and HAL_PWR_IsEnabledVddIO2Monitor() functions.
   - Enable, disable and check the Vdd Analog voltage monitor 1:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddAMonitor1(), HAL_PWR_DisableVddAMonitor1()
       and HAL_PWR_IsEnabledVddAMonitor1() functions.
   - Enable, disable and check the Vdd Analog voltage monitor 2:
     - These functionalities are ensured respectively by HAL_PWR_EnableVddAMonitor2(), HAL_PWR_DisableVddAMonitor2()
       and HAL_PWR_IsEnabledVddAMonitor2() functions.
   - Enable, disable and check the temperature and VBAT monitor:
     - These functionalities are ensured respectively by HAL_PWR_EnableTemperatureVbatMonitor(),
       HAL_PWR_DisableTemperatureVbatMonitor() and HAL_PWR_IsEnabledTemperatureVbatMonitor() functions.

6. Manage memory retention:
   After entering low power mode, the memories content retention can be managed.
   - Enable, disable and check memory retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableMemoryRetention(), HAL_PWR_LP_DisableMemoryRetention() and
      HAL_PWR_LP_IsEnabledMemoryRetention() functions.
   - Enable, disable and check the memory pages retention:
     - These functionalities are ensured respectively by HAL_PWR_LP_EnableMemoryPageRetention(),
       HAL_PWR_LP_DisableMemoryPageRetention() and HAL_PWR_LP_IsEnabledMemoryPageRetention() functions.
   - Enable, disable and check the UCPD retention: (*)
     - These functionalities are ensured by HAL_PWR_LP_EnableUCPDRetention(), HAL_PWR_LP_DisableUCPDRetention()
       and HAL_PWR_LP_IsEnabledUCPDRetention() functions.
   - Enable, disable and check the OTG HS PHY power during low power modes (Stop2, 3 and Standby): (*)
     - These functionalities are ensured respectively by HAL_PWR_LP_EnableOTGHSPHYRetention(),
       HAL_PWR_LP_DisableOTGHSPHYRetention() and HAL_PWR_LP_IsEnabledOTGHSPHYRetention() functions.
     - (*) feature not available in all devices

7. Manage memories wakeup:
   This feature is used to obtain the best trade-off between low-power consumption and wakeup time when exiting
   the Stop x modes.
   - Enable, disable and check the memories fast wakeup:
     - These functonalities are ensured respectively by HAL_PWR_LP_EnableMemoryFastWakeup(),
       HAL_PWR_LP_DisableMemoryFastWakeup() and HAL_PWR_LP_IsEnabledMemoryFastWakeup() functions.

8. Control the battery Backup domain:
   Several API are available to retain the content of the backup registers:
   - Configure the battery charging resistor:
     - This functionality is ensured by HAL_PWR_SetConfigBatteryCharging() function.
   - Get the battery charging resistor configuration:
     - This functionality is ensured by HAL_PWR_GetConfigBatteryCharging() function.
   - Enable, disable and check the battery charging:
     - These functionalities are ensured by HAL_PWR_EnableBatteryCharging(), HAL_PWR_DisableBatteryCharging()
       and HAL_PWR_IsEnabledBatteryCharging() functions respectively to enable, disable and check that enabled or not.
   - Enable, disable and check the UCPD dead battery: (*)
     - These functionalies are ensured respectively by HAL_PWR_LP_EnableUCPDDeadBattery(),
       HAL_PWR_LP_DisableUCPDDeadBattery() and HAL_PWR_LP_IsEnabledUCPDDeadBattery() functions.
     - (*) feature not available in all devices

9. Control Power GPIO Pull:
   Several API are available to control the power GPIO pull.
   - Configure the GPIO Pull:
     - This functionality is ensured by HAL_PWR_SetConfigGPIOPull() function.
   - Get the GPIO Pull configuration:
     - This functionality is ensured by HAL_PWR_GetConfigGPIOPull() function.
   - Enable, disable and check GPIO Pull configuration:
     - These functionalities are ansured respectively by HAL_PWR_EnableGPIOPull(), HAL_PWR_DisableGPIOPull() and
       HAL_PWR_IsEnabledGPIOPull() functions.

## Configuration inside the PWR driver

Config defines       | Description        | Default value | Note
---------------------| ---------------    | ------------- | ------------------------------------------------------------
USE_HAL_PWR_MODULE   | from hal_conf.h    | 1U            | When set, HAL PWR module is enabled.
USE_ASSERT_DBG_PARAM | from IDE           | None          | When defined, enable the params assert.
USE_HAL_CHECK_PARAM  | from hal_conf.h    | 0U            | When set, parameters are checked in runtime.
  */

#if defined(USE_HAL_PWR_MODULE) && (USE_HAL_PWR_MODULE == 1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/**
  * @brief PWR_Private_TypeDef PWR Private Typedef
  * @{
  */
typedef struct
{
  uint32_t pos;  /*!< Memory page position */
  uint32_t msk;  /*!< Memory page mask     */
} pwr_memory_pages_retention_map_t;
/**
  * @}
  */

/* Private defines ---------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
/* Time out value of flags setting */
#define PWR_VOS_SELECT_MAX_DELAY           0x32U   /*!< Max VOS timeout              */
#define PWR_REGULATOR_SELECT_MAX_DELAY     0x32U   /*!< Max regulator select timeout */
#define PWR_LUT_DEFAULT_VALUE              0x00U   /*!< LUT unused case              */
#define PWR_SRAM2_RETENTION_PAGES_MAX      0x02U   /*!< SRAM2 max pages number       */
#if defined(PWR_CR5_SRAM6PDS1)
#define PWR_SRAM1_RETENTION_PAGES_MAX      0x0CU   /*!< SRAM1 max pages number       */
#define PWR_SRAM3_RETENTION_PAGES_MAX      0x0DU   /*!< SRAM3 max pages number       */
#define PWR_SRAM5_RETENTION_PAGES_MAX      0x0DU   /*!< SRAM5 max pages number       */
#define PWR_SRAM6_RETENTION_PAGES_MAX      0x08U   /*!< SRAM6 max pages number       */
#elif defined(PWR_CR4_SRAM5PDS1)
#define PWR_SRAM1_RETENTION_PAGES_MAX      0x0CU   /*!< SRAM1 max pages number       */
#define PWR_SRAM3_RETENTION_PAGES_MAX      0x0DU   /*!< SRAM3 max pages number       */
#define PWR_SRAM5_RETENTION_PAGES_MAX      0x0DU   /*!< SRAM5 max pages number       */
#elif defined(PWR_CR2_SRAM3PDS1)
#define PWR_SRAM1_RETENTION_PAGES_MAX      0x03U   /*!< SRAM1 max pages number       */
#define PWR_SRAM3_RETENTION_PAGES_MAX      0x08U   /*!< SRAM3 max pages number       */
#else
#define PWR_SRAM1_RETENTION_PAGES_MAX      0x03U   /*!< SRAM1 max pages number       */
#endif /* PWR_CR5_SRAM6PDS1 */
#if defined(PWR_PUCRJ_PU0)
#define PWR_GPIO_PULL_PORT_I_MASK          0xFFFFU /*!< Port I mask                  */
#define PWR_GPIO_PULL_PORT_J_MASK          0x0FFFU /*!< Port J mask                  */
#else
#define PWR_GPIO_PULL_PORT_I_MASK          0x00FFU /*!< Port I mask                  */
#endif /* PWR_PUCRJ_PU0 */
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Variables PWR Private Variables
  * @{
  */
/*! Memory retention mapping table */
static const uint32_t PWR_MemoryFullRetentionMap[] =
{
#if defined(PWR_CR5_SRAM6PDS1)
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM3_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  LL_PWR_SRAM5_RUN_FULL_RETENTION,
  LL_PWR_SRAM6_RUN_FULL_RETENTION,
  LL_PWR_SRAM1_STOP_1_3_RETENTION,
  LL_PWR_SRAM2_STOP_FULL_RETENTION,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_SRAM3_STOP_1_8_RETENTION,
  LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_JPEGRAM_STOP_FULL_RETENTION,
  LL_PWR_SRAM5_STOP_FULL_RETENTION,
  LL_PWR_SRAM6_STOP_FULL_RETENTION,
  LL_PWR_SRAM2_SB_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_DSIRAMPDS)
  LL_PWR_DSIRAM_STOP_FULL_RETENTION,
#endif /* defined(PWR_CR2_DSIRAMPDS) */
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR4_SRAM5PDS1)
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM3_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  LL_PWR_SRAM5_RUN_FULL_RETENTION,
  LL_PWR_SRAM1_STOP_1_3_RETENTION,
  LL_PWR_SRAM2_STOP_FULL_RETENTION,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_SRAM3_STOP_1_8_RETENTION,
  LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_SRAM5_STOP_FULL_RETENTION,
  LL_PWR_SRAM2_SB_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_DSIRAMPDS)
  LL_PWR_DSIRAM_STOP_FULL_RETENTION,
#endif /* defined(PWR_CR2_DSIRAMPDS) */
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR2_SRAM3PDS1)
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM3_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  LL_PWR_SRAM1_STOP_1_3_RETENTION,
  LL_PWR_SRAM2_STOP_FULL_RETENTION,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_SRAM3_STOP_1_8_RETENTION,
  LL_PWR_SRAM2_SB_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#else
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  LL_PWR_SRAM1_STOP_1_3_RETENTION,
  LL_PWR_SRAM2_STOP_FULL_RETENTION,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_SRAM2_SB_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#endif /* PWR_CR5_SRAM6PDS1 */
};

/*! Memory retention mapping table */
static const uint32_t PWR_GetMemoryFullRetentionMap[] =
{
#if defined(PWR_CR5_SRAM6PDS1)
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM3_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  LL_PWR_SRAM5_RUN_FULL_RETENTION,
  LL_PWR_SRAM6_RUN_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION,
  LL_PWR_JPEGRAM_STOP_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_DSIRAMPDS)
  LL_PWR_DSIRAM_STOP_FULL_RETENTION,
#endif /* defined(PWR_CR2_DSIRAMPDS) */
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR4_SRAM5PDS1)
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM3_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  LL_PWR_SRAM5_RUN_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_DSIRAMPDS)
  LL_PWR_DSIRAM_STOP_FULL_RETENTION,
#endif /* defined(PWR_CR2_DSIRAMPDS) */
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR2_SRAM3PDS1)
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM3_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#else
  LL_PWR_SRAM1_RUN_FULL_RETENTION,
  LL_PWR_SRAM2_RUN_FULL_RETENTION,
  LL_PWR_SRAM4_RUN_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  LL_PWR_SRAM4_STOP_FULL_RETENTION,
  LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
  LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
  LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
#if defined(PWR_CR2_PKARAMPDS)
  LL_PWR_PKARAM_STOP_FULL_RETENTION
#endif /* defined(PWR_CR2_PKARAMPDS) */
#endif /* PWR_CR5_SRAM6PDS1 */
};

#if defined(USE_ASSERT_DBG_PARAM)
/*! Memory max pages retention mapping table */
static const uint32_t PWR_MemoryMaxPagesRetentionMap[] =
{
#if defined(PWR_CR5_SRAM6PDS1)
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM1_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM3_RETENTION_PAGES_MAX,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM5_RETENTION_PAGES_MAX,
  PWR_SRAM6_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX
#elif defined(PWR_CR4_SRAM5PDS1)
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM1_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM3_RETENTION_PAGES_MAX,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM5_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX
#elif defined(PWR_CR2_SRAM3PDS1)
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM1_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM3_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX
#else
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM1_RETENTION_PAGES_MAX,
  PWR_SRAM2_RETENTION_PAGES_MAX,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_LUT_DEFAULT_VALUE,
  PWR_SRAM2_RETENTION_PAGES_MAX
#endif /* PWR_CR5_SRAM6PDS1 */
};
#endif /* USE_ASSERT_DBG_PARAM */

/*! Memory pages retention mapping table for CR2 register */
static const pwr_memory_pages_retention_map_t PWR_MemoryPagesRetentionCR2Map[] =
{
#if defined(PWR_CR5_SRAM6PDS1)
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM1PDS1_Pos, (LL_PWR_SRAM1_STOP_1_3_RETENTION >> PWR_CR2_SRAM1PDS1_Pos) },
  {PWR_CR2_SRAM2PDS1_Pos, (LL_PWR_SRAM2_STOP_FULL_RETENTION >> PWR_CR2_SRAM2PDS1_Pos)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM3PDS1_Pos, (LL_PWR_SRAM3_STOP_1_8_RETENTION >> PWR_CR2_SRAM3PDS1_Pos) },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR1_RRSB1_Pos, (LL_PWR_SRAM2_SB_FULL_RETENTION >> PWR_CR1_RRSB1_Pos)          }
#elif defined(PWR_CR4_SRAM5PDS1)
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM1PDS1_Pos, (LL_PWR_SRAM1_STOP_1_3_RETENTION >> PWR_CR2_SRAM1PDS1_Pos) },
  {PWR_CR2_SRAM2PDS1_Pos, (LL_PWR_SRAM2_STOP_FULL_RETENTION >> PWR_CR2_SRAM2PDS1_Pos)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM3PDS1_Pos, (LL_PWR_SRAM3_STOP_1_8_RETENTION >> PWR_CR2_SRAM3PDS1_Pos) },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR1_RRSB1_Pos, (LL_PWR_SRAM2_SB_FULL_RETENTION >> PWR_CR1_RRSB1_Pos)          }
#elif defined(PWR_CR2_SRAM3PDS1)
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM1PDS1_Pos, (LL_PWR_SRAM1_STOP_1_3_RETENTION >> PWR_CR2_SRAM1PDS1_Pos) },
  {PWR_CR2_SRAM2PDS1_Pos, (LL_PWR_SRAM2_STOP_FULL_RETENTION >> PWR_CR2_SRAM2PDS1_Pos)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM3PDS1_Pos, (LL_PWR_SRAM3_STOP_1_8_RETENTION >> PWR_CR2_SRAM3PDS1_Pos) },
  {PWR_CR1_RRSB1_Pos, (LL_PWR_SRAM2_SB_FULL_RETENTION >> PWR_CR1_RRSB1_Pos)          }
#else
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR2_SRAM1PDS1_Pos, (LL_PWR_SRAM1_STOP_1_3_RETENTION >> PWR_CR2_SRAM1PDS1_Pos) },
  {PWR_CR2_SRAM2PDS1_Pos, (LL_PWR_SRAM2_STOP_FULL_RETENTION >> PWR_CR2_SRAM2PDS1_Pos)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR1_RRSB1_Pos, (LL_PWR_SRAM2_SB_FULL_RETENTION >> PWR_CR1_RRSB1_Pos)          }
#endif /* PWR_CR5_SRAM6PDS1 */
};

#if defined(PWR_CR4_SRAM5PDS1)
/*! Memory pages retention mapping table for CR4 register */
static const pwr_memory_pages_retention_map_t PWR_MemoryPagesRetentionCR4Map[] =
{
#if defined(PWR_CR5_SRAM6PDS1)
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_CR4_SRAM1PDS4_Pos, ((LL_PWR_SRAM1_STOP_4_12_RETENTION >> PWR_CR4_SRAM1PDS4_Pos) << 3U)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_CR4_SRAM3PDS9_Pos, ((LL_PWR_SRAM3_STOP_9_13_RETENTION >> PWR_CR4_SRAM3PDS9_Pos) << 8U)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_CR4_SRAM5PDS1_Pos, (LL_PWR_SRAM5_STOP_FULL_RETENTION >> PWR_CR4_SRAM5PDS1_Pos)        }
#else
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_CR4_SRAM1PDS4_Pos, ((LL_PWR_SRAM1_STOP_4_12_RETENTION >> PWR_CR4_SRAM1PDS4_Pos) << 3U)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_CR4_SRAM3PDS9_Pos, ((LL_PWR_SRAM3_STOP_9_13_RETENTION >> PWR_CR4_SRAM3PDS9_Pos) << 8U)},
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                              },
  {PWR_CR4_SRAM5PDS1_Pos, (LL_PWR_SRAM5_STOP_FULL_RETENTION >> PWR_CR4_SRAM5PDS1_Pos)        }
#endif /* PWR_CR5_SRAM6PDS1 */
};
#endif /* defined(PWR_CR4_SRAM5PDS1) */

#if defined(PWR_CR5_SRAM6PDS1)
/*! Memory pages retention mapping table for CR5 register */
static const pwr_memory_pages_retention_map_t PWR_MemoryPagesRetentionCR5Map[] =
{
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_LUT_DEFAULT_VALUE, PWR_LUT_DEFAULT_VALUE                                      },
  {PWR_CR5_SRAM6PDS1_Pos, (LL_PWR_SRAM6_STOP_FULL_RETENTION >> PWR_CR5_SRAM6PDS1_Pos)}
};
#endif /* defined(PWR_CR5_SRAM6PDS1) */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/*! Set wakeup pins check macro */
#define IS_PWR_SET_WAKEUP_PIN(pin) \
  ((((pin) & HAL_PWR_WAKEUP_PIN_ALL) != 0U) && (((pin) & (~HAL_PWR_WAKEUP_PIN_ALL)) == 0U))

/*! Wakeup pin polarity check macro */
#define IS_PWR_WAKEUP_PIN_POLARITY(polarity) \
  (((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_HIGH ) || ((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_LOW))

/*! Wakeup source check macro */
#define IS_PWR_WAKEUP_PIN_SOURCE(source)        \
  (((source) == HAL_PWR_WAKEUP_PIN_SOURCE_0)    \
   || ((source) == HAL_PWR_WAKEUP_PIN_SOURCE_1) \
   || ((source) == HAL_PWR_WAKEUP_PIN_SOURCE_2) \
   || ((source) == HAL_PWR_WAKEUP_PIN_SOURCE_3))

/*! Get wakeup pins check macro */
#define IS_PWR_GET_WAKEUP_PIN(pin)    \
  (((pin) == HAL_PWR_WAKEUP_PIN_1)    \
   || ((pin) == HAL_PWR_WAKEUP_PIN_2) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_3) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_4) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_5) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_6) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_7) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_8))

/*! Voltage scaling range check macro */
#define IS_PWR_VOLTAGE_SCALING_RANGE(range)        \
  (((range) == HAL_PWR_VOLT_SCALE_1)    \
   || ((range) == HAL_PWR_VOLT_SCALE_2) \
   || ((range) == HAL_PWR_VOLT_SCALE_3) \
   || ((range) == HAL_PWR_VOLT_SCALE_4))

/*! Main regulator supply check macro */
#define IS_PWR_MAIN_REGULATOR_SUPPLY(regulator) \
  (((regulator) == HAL_PWR_MAIN_REGULATOR_LDO_SUPPLY) || ((regulator) == HAL_PWR_MAIN_REGULATOR_SMPS_SUPPLY))

/*! Main regulator startup mode check macro */
#define IS_PWR_MAIN_REGULATOR_STARTUP_MODE(mode)     \
  (((mode) == HAL_PWR_MAIN_REGULATOR_SLOW_STARTUP)   \
   || ((mode) == HAL_PWR_MAIN_REGULATOR_FAST_STARTUP))

/*! I/O analog switch supply check macro */
#define IS_PWR_ANALOG_IO_SWITCH_SUPPLY(analog_switch_supply) \
  (((analog_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY)        \
   || ((analog_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_VDD_2V4_SUPPLY)  \
   || ((analog_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY))

/*! independent VddA voltage monitor check macro */
#define IS_PWR_INDEPENDENT_VDDA_VOLTAGE_MONITOR(monitor) \
  (((monitor) == HAL_PWR_VDD_ANALOG_MONITOR_1) || ((monitor) == HAL_PWR_VDD_ANALOG_MONITOR_2))

/*! Low power mode entry check macro */
#define IS_PWR_LP_MODE_ENTRY(entry) \
  (((entry) == HAL_PWR_LOW_PWR_MODE_WFE) || ((entry) == HAL_PWR_LOW_PWR_MODE_WFI))

/*! Stop mode check macro */
#define IS_PWR_STOP_MODE(mode)       \
  (((mode) == HAL_PWR_STOP0_MODE)    \
   || ((mode) == HAL_PWR_STOP1_MODE) \
   || ((mode) == HAL_PWR_STOP2_MODE) \
   || ((mode) == HAL_PWR_STOP3_MODE))

/*! Core sleep mode check macro */
#define IS_PWR_CORE_SLEEP_MODE(mode) \
  (((mode) == HAL_PWR_CORE_SLEEP) || ((mode) == HAL_PWR_CORE_DEEP_SLEEP))

/*! SRD mode check macro */
#define IS_PWR_SRD_MODE(mode) \
  (((mode) == HAL_PWR_SYSTEM_STOP_SRD_STOP) || ((mode) == HAL_PWR_SYSTEM_STOP_SRD_RUN))

/*! BOR mode check macro */
#define IS_PWR_BOR_MODE(mode) \
  (((mode) == HAL_PWR_BROWNOUT_RESET_CONTINUOUS_MODE) || ((mode) == HAL_PWR_BROWNOUT_RESET_DISCONTINUOUS_MODE))

/*! PVD level check macro */
#define IS_PWR_PVD_LEVEL(level)        \
  (((level) == HAL_PWR_PVD_LEVEL_0)    \
   || ((level) == HAL_PWR_PVD_LEVEL_1) \
   || ((level) == HAL_PWR_PVD_LEVEL_2) \
   || ((level) == HAL_PWR_PVD_LEVEL_3) \
   || ((level) == HAL_PWR_PVD_LEVEL_4) \
   || ((level) == HAL_PWR_PVD_LEVEL_5) \
   || ((level) == HAL_PWR_PVD_LEVEL_6) \
   || ((level) == HAL_PWR_PVD_LEVEL_7))

/*! Memory retention check macro */
#if defined(PWR_CR5_SRAM6PDS1)
#if defined(PWR_CR2_PKARAMPDS) && defined(PWR_CR2_DSIRAMPDS)
#define IS_PWR_MEMORY_RETENTION(memory)                                \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#elif !defined(PWR_CR2_PKARAMPDS) && defined(PWR_CR2_DSIRAMPDS)
#define IS_PWR_MEMORY_RETENTION(memory)                                \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01))
#elif !defined(PWR_CR2_DSIRAMPDS) && defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_MEMORY_RETENTION(memory)                                \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_MEMORY_RETENTION(memory)                                \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) && defined(PWR_CR2_DSIRAMPDS) */
#elif defined(PWR_CR4_SRAM5PDS1)
#if defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_MEMORY_RETENTION(memory)                                \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_MEMORY_RETENTION(memory)                                \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR2_SRAM3PDS1)
#if defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_MEMORY_RETENTION(memory)                          \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)   \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_MEMORY_RETENTION(memory)                         \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)             \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)           \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)      \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)      \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)       \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)   \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY) \
   ||((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) */
#else
#if defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_MEMORY_RETENTION(memory)                          \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_MEMORY_RETENTION(memory)                          \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) */
#endif /* PWR_CR5_SRAM6PDS1 */

/*! Get the Memory retention check macro */
#if defined(PWR_CR5_SRAM6PDS1)
#if defined(PWR_CR2_PKARAMPDS) && defined(PWR_CR2_DSIRAMPDS)
#define IS_PWR_GET_MEMORY_RETENTION(memory)                            \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#elif !defined(PWR_CR2_PKARAMPDS) && defined(PWR_CR2_DSIRAMPDS)
#define IS_PWR_GET_MEMORY_RETENTION(memory)                            \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01))
#elif !defined(PWR_CR2_DSIRAMPDS) && defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_GET_MEMORY_RETENTION(memory)                            \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_GET_MEMORY_RETENTION(memory)                            \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) && defined(PWR_CR2_DSIRAMPDS) */
#elif defined(PWR_CR4_SRAM5PDS1)
#if defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_GET_MEMORY_RETENTION(memory)                            \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)       \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_GET_MEMORY_RETENTION(memory)                            \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)                    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)                 \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)            \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)          \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)         \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)        \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01)             \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR2_SRAM3PDS1)
#if defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_GET_MEMORY_RETENTION(memory)                      \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)   \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_GET_MEMORY_RETENTION(memory)                      \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123)   \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) */
#else
#if defined(PWR_CR2_PKARAMPDS)
#define IS_PWR_GET_MEMORY_RETENTION(memory)                      \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT) \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123))
#else
#define IS_PWR_GET_MEMORY_RETENTION(memory)                      \
  (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN)              \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN)           \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123)      \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123)     \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123)    \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123)  \
   || ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT))
#endif /* defined(PWR_CR2_PKARAMPDS) */
#endif /* PWR_CR5_SRAM6PDS1 */

/*! Memory page retention check macro */
#if defined(PWR_CR5_SRAM6PDS1)
#define IS_PWR_GET_MEMORY_PAGE_RETENTION(memory, page_idx)            \
  (((page_idx) <= PWR_MemoryMaxPagesRetentionMap[memory])             \
   && ((page_idx) > 0U)                                               \
   && (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)          \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)        \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)  \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)       \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)       \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)))
#elif defined(PWR_CR4_SRAM5PDS1)
#define IS_PWR_GET_MEMORY_PAGE_RETENTION(memory, page_idx)            \
  (((page_idx) <= PWR_MemoryMaxPagesRetentionMap[memory])             \
   && ((page_idx) > 0U)                                               \
   && (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)          \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)        \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)  \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)       \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)))
#elif defined(PWR_CR2_SRAM3PDS1)
#define IS_PWR_GET_MEMORY_PAGE_RETENTION(memory, page_idx)            \
  (((page_idx) <= PWR_MemoryMaxPagesRetentionMap[memory])             \
   &&((page_idx) > 0U)                                                \
   &&(((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)           \
      || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)         \
      || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)   \
      || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)))
#else
#define IS_PWR_GET_MEMORY_PAGE_RETENTION(memory, page_idx)            \
  (((page_idx) <= PWR_MemoryMaxPagesRetentionMap[memory])             \
   && ((page_idx) > 0U)                                               \
   && (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)          \
       ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)         \
       ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)))
#endif /* PWR_CR5_SRAM6PDS1 */

/*! Memory pages retention check macro */
#if defined(PWR_CR5_SRAM6PDS1)
#define IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr)               \
  (((((page_idx) - 1U) + (page_nbr)) <= PWR_MemoryMaxPagesRetentionMap[memory]) \
   && ((((page_idx) - 1U) + (page_nbr)) > 0U)                                   \
   && (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)              \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)            \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)      \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)           \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)           \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)))
#elif defined(PWR_CR4_SRAM5PDS1)
#define IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr)               \
  (((((page_idx) - 1U) + (page_nbr)) <= PWR_MemoryMaxPagesRetentionMap[memory]) \
   && ((((page_idx) - 1U) + (page_nbr)) > 0U)                                   \
   && (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)              \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)            \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)      \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)           \
       || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)))
#elif defined(PWR_CR2_SRAM3PDS1)
#define IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr)               \
  (((((page_idx) - 1U) + (page_nbr)) <= PWR_MemoryMaxPagesRetentionMap[memory]) \
   &&((((page_idx) - 1U) + (page_nbr)) > 0U)                                    \
   &&(((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)               \
      || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
      || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)       \
      || ((memory) == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)))
#else
#define IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr)               \
  (((((page_idx) - 1U) + (page_nbr)) <= PWR_MemoryMaxPagesRetentionMap[memory]) \
   && ((((page_idx) - 1U) + (page_nbr)) > 0U)                                   \
   && (((memory) == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)              \
       ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012)             \
       ||((memory) == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)))
#endif /* PWR_CR5_SRAM6PDS1 */

/*! Memory fast wakeup check macro */
#define IS_PWR_FAST_WAKEUP(memory) \
  ((((memory) & HAL_PWR_MEMORIES_FAST_WAKEUP_ALL) != 0U) && (((memory) & (~HAL_PWR_MEMORIES_FAST_WAKEUP_ALL)) == 0U))

/*! Get memory fast wakeup check macro */
#define IS_PWR_GET_FAST_WAKEUP(memory) \
  (((memory) == HAL_PWR_FLASH_STOP01_FAST_WAKEUP) || ((memory) == HAL_PWR_SRAM4_STOP012_FAST_WAKEUP))

/*! Battery charging resistor selection check macro */
#define IS_PWR_BATTERY_RESISTOR_SELECT(resistor) \
  (((resistor) == HAL_PWR_BATTERY_CHARGING_RES_5K) || ((resistor) == HAL_PWR_BATTERY_CHARGING_RES_1_5K))

/*! GPIO set configuration pull check macro */
#if defined(PWR_CR5_SRAM6PDS1)
#define IS_PWR_GPIO_PIN_PULL_SET_CONFIG(port, pin, pull)                           \
  (((((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLUP)            \
     && (((pin) & HAL_PWR_GPIO_PIN_14) == HAL_PWR_GPIO_PIN_14))                    \
    || (((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLDOWN)       \
        && ((((pin) & HAL_PWR_GPIO_PIN_13) == HAL_PWR_GPIO_PIN_13)                 \
            || (((pin) & HAL_PWR_GPIO_PIN_15) == HAL_PWR_GPIO_PIN_15)))            \
    || (((port) == HAL_PWR_GPIO_PORT_B) && ((pull) == HAL_PWR_GPIO_PULLDOWN)       \
        && (((pin) & HAL_PWR_GPIO_PIN_4) == HAL_PWR_GPIO_PIN_4))                   \
    || (((port) == HAL_PWR_GPIO_PORT_J) && (((pin) > PWR_GPIO_PULL_PORT_J_MASK ))) \
    || (((pin)  >  HAL_PWR_GPIO_PIN_ALL) || ((pin) == 0U))                         \
    || ((pull) >  HAL_PWR_GPIO_PULLDOWN) || (((port) <  HAL_PWR_GPIO_PORT_A) || ((port) >  HAL_PWR_GPIO_PORT_J))) == 0U)
#elif defined(PWR_CR4_SRAM5PDS1)
#define IS_PWR_GPIO_PIN_PULL_SET_CONFIG(port, pin, pull)                           \
  (((((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLUP)            \
     && (((pin) & HAL_PWR_GPIO_PIN_14) == HAL_PWR_GPIO_PIN_14))                    \
    || (((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLDOWN)       \
        && ((((pin) & HAL_PWR_GPIO_PIN_13) == HAL_PWR_GPIO_PIN_13)                 \
            || (((pin) & HAL_PWR_GPIO_PIN_15) == HAL_PWR_GPIO_PIN_15)))            \
    || (((port) == HAL_PWR_GPIO_PORT_B) && ((pull) == HAL_PWR_GPIO_PULLDOWN)       \
        && (((pin) & HAL_PWR_GPIO_PIN_4) == HAL_PWR_GPIO_PIN_4))                   \
    || (((port) == HAL_PWR_GPIO_PORT_J) && (((pin) > PWR_GPIO_PULL_PORT_J_MASK ))) \
    || (((pin)  >  HAL_PWR_GPIO_PIN_ALL) || ((pin) == 0U))                         \
    || ((pull) >  HAL_PWR_GPIO_PULLDOWN) || (((port) <  HAL_PWR_GPIO_PORT_A) || ((port) >  HAL_PWR_GPIO_PORT_J))) == 0U)
#elif defined(PWR_CR2_SRAM3PDS1)
#define IS_PWR_GPIO_PIN_PULL_SET_CONFIG(port, pin, pull)                           \
  (((((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLUP)            \
     &&  (((pin) & HAL_PWR_GPIO_PIN_14) == HAL_PWR_GPIO_PIN_14))                   \
    || (((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLDOWN)       \
        && ((((pin) & HAL_PWR_GPIO_PIN_13) == HAL_PWR_GPIO_PIN_13)                 \
            ||  (((pin) & HAL_PWR_GPIO_PIN_15) == HAL_PWR_GPIO_PIN_15)))           \
    || (((port) == HAL_PWR_GPIO_PORT_B) && ((pull) == HAL_PWR_GPIO_PULLDOWN)       \
        &&(((pin) & HAL_PWR_GPIO_PIN_4) == HAL_PWR_GPIO_PIN_4))                    \
    || (((port) == HAL_PWR_GPIO_PORT_I) && (((pin) > PWR_GPIO_PULL_PORT_I_MASK ))) \
    || (((pin)  >  HAL_PWR_GPIO_PIN_ALL) || ((pin) == 0U))                         \
    || ((pull) >  HAL_PWR_GPIO_PULLDOWN) || (((port) <  HAL_PWR_GPIO_PORT_A) || ((port) >  HAL_PWR_GPIO_PORT_I))) == 0U)
#else
#define IS_PWR_GPIO_PIN_PULL_SET_CONFIG(port, pin, pull)                     \
  (((((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLUP)      \
     && (((pin) & HAL_PWR_GPIO_PIN_14) == HAL_PWR_GPIO_PIN_14))              \
    ||(((port) == HAL_PWR_GPIO_PORT_A) && ((pull) == HAL_PWR_GPIO_PULLDOWN)  \
       &&((((pin) & HAL_PWR_GPIO_PIN_13) == HAL_PWR_GPIO_PIN_13)             \
          ||  (((pin) & HAL_PWR_GPIO_PIN_15) == HAL_PWR_GPIO_PIN_15)))       \
    || (((port) == HAL_PWR_GPIO_PORT_B) && ((pull) == HAL_PWR_GPIO_PULLDOWN) \
        && (((pin) & HAL_PWR_GPIO_PIN_4) == HAL_PWR_GPIO_PIN_4))             \
    ||(((port) == HAL_PWR_GPIO_PORT_G)                                       \
       &&((((pin) & HAL_PWR_GPIO_PIN_0) == HAL_PWR_GPIO_PIN_0)               \
          || (((pin) & HAL_PWR_GPIO_PIN_1) == HAL_PWR_GPIO_PIN_1)))          \
    || (((port) == HAL_PWR_GPIO_PORT_H)                                      \
        &&((((pin) & HAL_PWR_GPIO_PIN_2) == HAL_PWR_GPIO_PIN_2)              \
           ||   ((pin) > 0xBU)))                                             \
    || (((pin)  >  HAL_PWR_GPIO_PIN_ALL) || ((pin) == 0U))                   \
    || ((pull) >  HAL_PWR_GPIO_PULLDOWN) || (((port) <  HAL_PWR_GPIO_PORT_A) || ((port) >  HAL_PWR_GPIO_PORT_H))) == 0U)
#endif /* PWR_CR5_SRAM6PDS1 */

/*! GPIO get configuration pull check macro */
#if defined(PWR_CR5_SRAM6PDS1)
#define IS_PWR_GPIO_PIN_PULL_GET_CONFIG(pin, port) \
  (((((pin) != HAL_PWR_GPIO_PIN_0)                 \
     && ((pin) != HAL_PWR_GPIO_PIN_1)              \
     && ((pin) != HAL_PWR_GPIO_PIN_2)              \
     && ((pin) != HAL_PWR_GPIO_PIN_3)              \
     && ((pin) != HAL_PWR_GPIO_PIN_4)              \
     && ((pin) != HAL_PWR_GPIO_PIN_5)              \
     && ((pin) != HAL_PWR_GPIO_PIN_6)              \
     && ((pin) != HAL_PWR_GPIO_PIN_7)              \
     && ((pin) != HAL_PWR_GPIO_PIN_8)              \
     && ((pin) != HAL_PWR_GPIO_PIN_9)              \
     && ((pin) != HAL_PWR_GPIO_PIN_10)             \
     && ((pin) != HAL_PWR_GPIO_PIN_11)             \
     && ((pin) != HAL_PWR_GPIO_PIN_12)             \
     && ((pin) != HAL_PWR_GPIO_PIN_13)             \
     && ((pin) != HAL_PWR_GPIO_PIN_14)             \
     && ((pin) != HAL_PWR_GPIO_PIN_15))            \
    || (((port) <  HAL_PWR_GPIO_PORT_A)            \
        || ((port) > HAL_PWR_GPIO_PORT_J))) == 0U)
#elif defined(PWR_CR4_SRAM5PDS1)
#define IS_PWR_GPIO_PIN_PULL_GET_CONFIG(pin, port) \
  (((((pin) != HAL_PWR_GPIO_PIN_0)                 \
     && ((pin) != HAL_PWR_GPIO_PIN_1)              \
     && ((pin) != HAL_PWR_GPIO_PIN_2)              \
     && ((pin) != HAL_PWR_GPIO_PIN_3)              \
     && ((pin) != HAL_PWR_GPIO_PIN_4)              \
     && ((pin) != HAL_PWR_GPIO_PIN_5)              \
     && ((pin) != HAL_PWR_GPIO_PIN_6)              \
     && ((pin) != HAL_PWR_GPIO_PIN_7)              \
     && ((pin) != HAL_PWR_GPIO_PIN_8)              \
     && ((pin) != HAL_PWR_GPIO_PIN_9)              \
     && ((pin) != HAL_PWR_GPIO_PIN_10)             \
     && ((pin) != HAL_PWR_GPIO_PIN_11)             \
     && ((pin) != HAL_PWR_GPIO_PIN_12)             \
     && ((pin) != HAL_PWR_GPIO_PIN_13)             \
     && ((pin) != HAL_PWR_GPIO_PIN_14)             \
     && ((pin) != HAL_PWR_GPIO_PIN_15))            \
    || (((port) <  HAL_PWR_GPIO_PORT_A)            \
        || ((port) > HAL_PWR_GPIO_PORT_J))) == 0U)
#elif defined(PWR_CR2_SRAM3PDS1)
#define IS_PWR_GPIO_PIN_PULL_GET_CONFIG(pin, port) \
  (((((pin) != HAL_PWR_GPIO_PIN_0)                 \
     && ((pin) != HAL_PWR_GPIO_PIN_1)              \
     && ((pin) != HAL_PWR_GPIO_PIN_2)              \
     && ((pin) != HAL_PWR_GPIO_PIN_3)              \
     && ((pin) != HAL_PWR_GPIO_PIN_4)              \
     && ((pin) != HAL_PWR_GPIO_PIN_5)              \
     && ((pin) != HAL_PWR_GPIO_PIN_6)              \
     && ((pin) != HAL_PWR_GPIO_PIN_7)              \
     && ((pin) != HAL_PWR_GPIO_PIN_8)              \
     && ((pin) != HAL_PWR_GPIO_PIN_9)              \
     && ((pin) != HAL_PWR_GPIO_PIN_10)             \
     && ((pin) != HAL_PWR_GPIO_PIN_11)             \
     && ((pin) != HAL_PWR_GPIO_PIN_12)             \
     && ((pin) != HAL_PWR_GPIO_PIN_13)             \
     && ((pin) != HAL_PWR_GPIO_PIN_14)             \
     && ((pin) != HAL_PWR_GPIO_PIN_15))            \
    || (((port) <  HAL_PWR_GPIO_PORT_A)            \
        || ((port) > HAL_PWR_GPIO_PORT_I))) == 0U)
#else
#define IS_PWR_GPIO_PIN_PULL_GET_CONFIG(pin, port) \
  (((((pin) != HAL_PWR_GPIO_PIN_0)                 \
     && ((pin) != HAL_PWR_GPIO_PIN_1)              \
     && ((pin) != HAL_PWR_GPIO_PIN_2)              \
     && ((pin) != HAL_PWR_GPIO_PIN_3)              \
     && ((pin) != HAL_PWR_GPIO_PIN_4)              \
     && ((pin) != HAL_PWR_GPIO_PIN_5)              \
     && ((pin) != HAL_PWR_GPIO_PIN_6)              \
     && ((pin) != HAL_PWR_GPIO_PIN_7)              \
     && ((pin) != HAL_PWR_GPIO_PIN_8)              \
     && ((pin) != HAL_PWR_GPIO_PIN_9)              \
     && ((pin) != HAL_PWR_GPIO_PIN_10)             \
     && ((pin) != HAL_PWR_GPIO_PIN_11)             \
     && ((pin) != HAL_PWR_GPIO_PIN_12)             \
     && ((pin) != HAL_PWR_GPIO_PIN_13)             \
     && ((pin) != HAL_PWR_GPIO_PIN_14)             \
     && ((pin) != HAL_PWR_GPIO_PIN_15))            \
    || (((port) <  HAL_PWR_GPIO_PORT_A)            \
        || ((port) > HAL_PWR_GPIO_PORT_H))) == 0U)
#endif /* PWR_CR5_SRAM6PDS1 */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1
  * @{
  This section provides functions allowing to configure the wakeup pins:
  - Call HAL_PWR_LP_SetConfigWakeupPin() function to configure wakeup pin.
  - Call HAL_PWR_LP_GetConfigWakeupPin() function to get wakeup pin configuration.
  - Call HAL_PWR_LP_EnableWakeupPin() function to enable wakeup pin.
  - Call HAL_PWR_LP_DisableWakeupPin() function to disable wakeup pin.
  - Call HAL_PWR_LP_IsEnabledWakeupPin() function to check that wakeup pin is enabled.
  */

/**
  * @brief  Set wakeup pin configuration.
  * @param  wakeup_pin        This parameter can be one or a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @param  p_config          Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  * @retval HAL_INVALID_PARAM p_config pointer is NULL.
  * @retval HAL_OK            Wakeup pin has been correctly configured.
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config)
{
  uint32_t tmp_pins_msk = wakeup_pin;
  uint32_t position;
  uint32_t iocurrent;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_SOURCE(p_config->source));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_PWR_SetWakeupPinPolarity(wakeup_pin, (uint32_t)p_config->polarity);

  /* Get wakeup pin information */
  position = POSITION_VAL(tmp_pins_msk);
  iocurrent = 1UL << position;

  while (tmp_pins_msk != 0U)
  {
    LL_PWR_SetWakeupPinSelection(iocurrent, (uint32_t)p_config->source);

    /* Update wakeup pin information */
    tmp_pins_msk &= (~iocurrent);
    position = POSITION_VAL(tmp_pins_msk);
    iocurrent = 1UL << position;
  }

  return HAL_OK;
}

/**
  * @brief  Get wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @param  p_config   Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  */
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  p_config->polarity = (hal_pwr_wakeup_pin_polarity_t)LL_PWR_GetWakeUpPinPolarity(wakeup_pin);

  /* Get wakeup pin selection */
  dummy = LL_PWR_GetWakeupPinSelection(wakeup_pin) >> (POSITION_VAL(wakeup_pin) * 2U);
  p_config->source = (hal_pwr_wakeup_pin_source_t)dummy;
}

/**
  * @brief  Enable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one or a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @note   Wakeup pins are used to wake up the system from Stop 3, Standby and Shutdown modes.
  */
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_EnableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Disable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one or a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @note   Wakeup pins are used to wake up the system from Stop 3, Standby and Shutdown modes.
  */
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_DisableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Check that wakeup pin is enabled.
  * @param  wakeup_pin                  This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @retval hal_pwr_wakeup_pin_status_t The wakeup pin status.
  */
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  return ((hal_pwr_wakeup_pin_status_t)LL_PWR_IsEnabledWakeUpPin(wakeup_pin));
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2
  * @{
  This section provides functions allowing to manage RTC domain write protection:
  - Call HAL_PWR_EnableRTCDomainWriteProtection() to enable the RTC domain write protection.
  - Call HAL_PWR_DisableRTCDomainWriteProtection() to disable the RTC domain write protection.
  - Call HAL_PWR_IsEnabledRTCDomainWriteProtection() to check if the RTC domain write protection is enabled.
  */

/**
  * @brief  Enable the RTC domain write protection (RCC Backup domain control register RCC_BDCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  * @note   After a system reset, the RTC domain is protected against possible unwanted write accesses.
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void)
{
  LL_PWR_EnableBackupDomainWriteProtection();
}

/**
  * @brief  Disable the RTC domain write protection (RCC Backup domain control register RCC_BDCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  */
void HAL_PWR_DisableRTCDomainWriteProtection(void)
{
  LL_PWR_DisableBackupDomainWriteProtection();
}

/**
  * @brief  Check if the RTC domain write protection is enabled.
  * @retval hal_pwr_rtc_domain_wrp_status_t The RTC domain write protection status.
  */
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((hal_pwr_rtc_domain_wrp_status_t)LL_PWR_IsEnabledBackupDomainWriteProtection());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group3
  * @{
  This section provides functions allowing to control power supply.
  - Call HAL_PWR_SetMainRegulatorVoltageScalingRange() function to configure voltage scaling range.
  - Call HAL_PWR_GetMainRegulatorVoltageScalingRange() function to get voltage scaling range configuration.
  - Call HAL_PWR_SetMainRegulatorSupply() function to configure the main regulator supply.
  - Call HAL_PWR_GetMainRegulatorSupply() function to get the main regulator supply configuration.
  - Call HAL_PWR_SetMainRegulatorStartupMode() function to set the main regulator fast startup mode.
  - Call HAL_PWR_GetMainRegulatorStartupMode() function to get if the main regulator fast startup mode.
  - Call HAL_PWR_SetAnalogIOSwitchSupply() function to set the analog IO switch supply.
  - Call HAL_PWR_GetAnalogIOSwitchSupply() function to get the analog IO switch supply configuration.
  - Call HAL_PWR_EnableVddUSBIndependentSupply() function to enable the independent USB voltage supply.
  - Call HAL_PWR_DisableVddUSBIndependentSupply() function to disable the independent USB voltage supply.
  - Call HAL_PWR_IsEnabledVddUSBIndependentSupply() function to check if the independent USB voltage supply is enabled.
  - Call HAL_PWR_EnableVddIO2IndependentSupply() function to enable the independent IO2 voltage supply.
  - Call HAL_PWR_DisableVddIO2IndependentSupply() function to disable the independent IO2 voltage supply.
  - Call HAL_PWR_IsEnabledVddIO2IndependentSupply() function to check if the independent IO2 voltage supply is enabled.
  - Call HAL_PWR_EnableVddAIndependentSupply() function to enable the independent analog voltage supply.
  - Call HAL_PWR_DisableVddAIndependentSupply() function to disable the independent analog voltage supply.
  - Call HAL_PWR_IsEnabledVddAIndependentSupply() function to check if the independent analog voltage supply is enabled.
  - Call HAL_PWR_EnableVdd11USBIndependentSupply() function to enable the independent Vdd11 USB voltage supply.
  - Call HAL_PWR_DisableVdd11USBIndependentSupply() function to disable the independent Vdd11 USB voltage supply.
  - Call HAL_PWR_IsEnabledVdd11USBIndependentSupply() function to check if the independent Vdd11 USB voltage supply
    is enabled.
  - Call HAL_PWR_EnableVddUSBHSTransceiverSupply() function to enable the internal USB HS transceiver supply.
  - Call HAL_PWR_DisableVddUSBHSTransceiverSupply() function to disable the internal USB HS transceiver supply.
  - Call HAL_PWR_IsEnabledVddUSBHSTransceiverSupply() function to check if the internal USB HS transceiver supply
    is enabled.
  */

/**
  * @brief   Set the regulator voltage scaling range.
  * @warning There are no constraints when moving to voltage scaling range 1.
  * @warning Before moving to voltage scaling range 2, it is mandatory to ensure that the system frequency is below
  *          110 MHz.
  * @warning Before moving to voltage scaling range 3, it is mandatory to ensure that the system frequency is below
  *          55 MHz.
  * @warning Before moving to voltage scaling range 4,it is mandatory to ensure that the system frequency is below
  *          25 MHz.
  * @param   range     This parameter is an element of \ref hal_pwr_volt_scale_range_t enumeration.
  * @retval  HAL_ERROR VOS setting timeout.
  * @retval  HAL_OK    Regulator voltage scaling range has been correctly configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range)
{
  uint32_t timeout = ((PWR_VOS_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t vos;
  uint32_t actvos;

  ASSERT_DBG_PARAM(IS_PWR_VOLTAGE_SCALING_RANGE(range));

  LL_PWR_SetRegulVoltageScaling((uint32_t)range);

  if (range > HAL_PWR_VOLT_SCALE_3)
  {
    LL_PWR_EnableEPODBooster();
  }
  else
  {
    LL_PWR_DisableEPODBooster();
  }

  /* Polling on vos and actvos flags */
  do
  {
    vos = LL_PWR_IsActiveFlag_VOS();
    actvos = LL_PWR_IsActiveFlag_ACTVOS();
    timeout--;

  } while (((vos == 0U) || (actvos == 0U)) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get the regulator voltage scaling range.
  * @retval Range The current applied voltage scaling range.
  */
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void)
{
  return ((hal_pwr_volt_scale_range_t)LL_PWR_GetRegulVoltageScaling());
}

/**
  * @brief  Set the system supply regulator configuration.
  * @param  regulator This parameter is an element of \ref hal_pwr_main_regulator_supply_t enumeration.
  * @retval HAL_ERROR regulator setting timeout.
  * @retval HAL_OK    System supply regulator has been correctly configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorSupply(hal_pwr_main_regulator_supply_t regulator)
{
  uint32_t timeout = ((PWR_REGULATOR_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;

  ASSERT_DBG_PARAM(IS_PWR_MAIN_REGULATOR_SUPPLY(regulator));

  LL_PWR_SetRegulatorSupply((uint32_t)regulator);

  /* Polling on regulator state */
  while ((LL_PWR_IsActiveFlag_REGULATOR() != ((uint32_t)regulator >> PWR_SVMSR_REGS_Pos)) && (timeout != 0U))
  {
    timeout--;
  }

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get the system supply regulator configuration.
  * @retval hal_pwr_main_regulator_supply_t System supply regulator configuration.
  */
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void)
{
  return (hal_pwr_main_regulator_supply_t)LL_PWR_GetRegulatorSupply();
}

/**
  * @brief Set the main regulator fast startup mode.
  * @param mode This parameter is an element of \ref hal_pwr_main_regulator_fast_startup_mode_t enumeration.
  */
void HAL_PWR_SetMainRegulatorStartupMode(hal_pwr_main_regulator_fast_startup_mode_t mode)
{
  ASSERT_DBG_PARAM(IS_PWR_MAIN_REGULATOR_STARTUP_MODE(mode));

  LL_PWR_SetMainRegulatorStartupMode((uint32_t)mode);
}

/**
  * @brief Get the main regulator fast startup mode.
  * @retval hal_pwr_main_regulator_fast_startup_mode_t The main regulator fast startup mode.
  */
hal_pwr_main_regulator_fast_startup_mode_t HAL_PWR_GetMainRegulatorStartupMode(void)
{
  return (hal_pwr_main_regulator_fast_startup_mode_t)LL_PWR_GetMainRegulatorStartupMode();
}

/**
  * @brief Set the IO analog switch supply.
  * @param analog_switch_supply This parameter is an element of \ref hal_pwr_analog_io_switch_supply_t enumeration.
  */
void HAL_PWR_SetAnalogIOSwitchSupply(hal_pwr_analog_io_switch_supply_t analog_switch_supply)
{
  ASSERT_DBG_PARAM(IS_PWR_ANALOG_IO_SWITCH_SUPPLY(analog_switch_supply));

  LL_PWR_EnableVddA();
  LL_SYSCFG_SetAnalogIOSwitchSupply((uint32_t)analog_switch_supply);
}

/**
  * @brief  Get the IO analog switch supply.
  * @retval hal_pwr_analog_io_switch_supply_t IO Analog switch supply.
  */
hal_pwr_analog_io_switch_supply_t HAL_PWR_GetAnalogIOSwitchSupply(void)
{
  return (hal_pwr_analog_io_switch_supply_t)LL_SYSCFG_GetAnalogIOSwitchSupply();
}

/**
  * @brief  Enable the Vdd USB independent supply.
  * @retval HAL_ERROR Vdd USB independent supply setting timeout.
  * @retval HAL_OK    Vdd USB independent supply has been correctly configured.
  */
hal_status_t HAL_PWR_EnableVddUSBIndependentSupply(void)
{
  uint32_t timeout = ((PWR_REGULATOR_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t monitor_status = LL_PWR_IsEnabledVddUSBMonitor();

  LL_PWR_EnableVddUSBMonitor();

  /* Polling on VDDUSB flag */
  do
  {
    timeout--;

  } while ((LL_PWR_IsActiveFlag_VDDUSB() == 0U) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  if (monitor_status == 0U)
  {
    LL_PWR_DisableVddUSBMonitor();
  }

  LL_PWR_EnableVddUSB();

  return HAL_OK;
}

/**
  * @brief Disable the Vdd USB independent supply.
  */
void HAL_PWR_DisableVddUSBIndependentSupply(void)
{
  LL_PWR_DisableVddUSB();
}

/**
  * @brief  Check if the Vdd USB independent supply is enabled.
  * @retval hal_pwr_independent_supply_status_t The VddUSB independent supply status.
  */
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddUSBIndependentSupply(void)
{
  return (hal_pwr_independent_supply_status_t)LL_PWR_IsEnabledVddUSB();
}

/**
  * @brief Enable the Vdd IO2 independent supply.
  * @retval HAL_ERROR Vdd IO2 independent supply setting timeout.
  * @retval HAL_OK    Vdd IO2 independent supply has been correctly configured.
  */
hal_status_t HAL_PWR_EnableVddIO2IndependentSupply(void)
{
  uint32_t timeout = ((PWR_REGULATOR_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t monitor_status = LL_PWR_IsEnabledVddIO2Monitor();

  LL_PWR_EnableVddIO2Monitor();

  /* Polling on VDDIO2 flag */
  do
  {
    timeout--;

  } while ((LL_PWR_IsActiveFlag_VDDIO2() == 0U) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  if (monitor_status == 0U)
  {
    LL_PWR_DisableVddIO2Monitor();
  }

  LL_PWR_EnableVddIO2();

  return HAL_OK;
}

/**
  * @brief Disable the Vdd IO2 independent supply.
  */
void HAL_PWR_DisableVddIO2IndependentSupply(void)
{
  LL_PWR_DisableVddIO2();
}

/**
  * @brief  Check if the Vdd USB independent supply is enabled.
  * @retval hal_pwr_independent_supply_status_t The VddIO2 independent supply status.
  */
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddIO2IndependentSupply(void)
{
  return (hal_pwr_independent_supply_status_t)LL_PWR_IsEnabledVddIO2();
}

/**
  * @brief Enable the Vdd analog independent supply.
  * @param monitor This parameter can be one or a combination of the following values:
  *                @arg HAL_PWR_VDD_ANALOG_MONITOR_1 : Independent VddA voltage monitor 1.
  *                @arg HAL_PWR_VDD_ANALOG_MONITOR_2 : Independent VddA voltage monitor 2.
  * @retval HAL_ERROR Independent voltage monitor setting timeout.
  * @retval HAL_OK    Independent voltage monitor has been correctly configured.
  */
hal_status_t HAL_PWR_EnableVddAIndependentSupply(uint32_t monitor)
{
  uint32_t timeout = ((PWR_REGULATOR_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t monitor_status;
  uint32_t monitor_flag;

  ASSERT_DBG_PARAM(IS_PWR_INDEPENDENT_VDDA_VOLTAGE_MONITOR(monitor));

  if (monitor == HAL_PWR_VDD_ANALOG_MONITOR_1)
  {
    monitor_status = LL_PWR_IsEnabledVddAMonitor1();
    monitor_flag = PWR_SVMSR_VDDA1RDY;
  }
  else
  {
    monitor_status = LL_PWR_IsEnabledVddAMonitor2();
    monitor_flag = PWR_SVMSR_VDDA2RDY;
  }

  LL_PWR_EnableVddAMonitor(monitor);

  do
  {
    timeout--;

  } while (((LL_PWR_READ_REG(SVMSR) & monitor_flag) == 0U) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  if (monitor_status == 0U)
  {
    LL_PWR_DisableVddAMonitor(monitor);
  }

  LL_PWR_EnableVddA();

  return HAL_OK;
}

/**
  * @brief Disable the Vdd analog independent supply.
  */
void HAL_PWR_DisableVddAIndependentSupply(void)
{
  LL_PWR_DisableVddA();
}

/**
  * @brief  Check if the Vdd analog independent supply is enabled.
  * @retval hal_pwr_independent_supply_status_t The VddA independent supply status.
  */
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddAIndependentSupply(void)
{
  return (hal_pwr_independent_supply_status_t)LL_PWR_IsEnabledVddA();
}

#if defined(PWR_VOSR_VDD11USBDIS)
/**
  * @brief  Enable the Vdd11 USB independent supply.
  * @retval HAL_OK    The Vdd11 USB  has been correctly enabled.
  */
hal_status_t HAL_PWR_EnableVdd11USBIndependentSupply(void)
{
  LL_PWR_EnableVdd11USB();

  return HAL_OK;
}

/**
  * @brief Disable the Vdd11 USB independent supply.
  */
void HAL_PWR_DisableVdd11USBIndependentSupply(void)
{
  LL_PWR_DisableVdd11USB();
}

/**
  * @brief  Check if the Vdd11 USB independent supply is enabled.
  * @retval hal_pwr_independent_supply_status_t The Vdd11 USB independent supply status.
  */
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVdd11USBIndependentSupply(void)
{
  return (hal_pwr_independent_supply_status_t)LL_PWR_IsEnabledVdd11USB();
}
#endif /* PWR_VOSR_VDD11USBDIS */

#if defined(PWR_VOSR_USBPWREN)
/**
  * @brief  Enable the internal USB HS transceiver supply.
  * @retval HAL_ERROR USB Boost setting timeout or voltage scaling less than range 2.
  * @retval HAL_OK    USB HS has been correctly enabled.
  */
hal_status_t HAL_PWR_EnableVddUSBHSTransceiverSupply(void)
{
  uint32_t timeout = ((PWR_VOS_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;

  if (LL_PWR_GetRegulVoltageScaling() < (uint32_t)HAL_PWR_VOLT_SCALE_2)
  {
    return HAL_ERROR;
  }

  LL_PWR_EnableUSBEPODBooster();
  LL_PWR_EnableUSBPowerSupply();

  do
  {
    timeout--;

  } while ((LL_PWR_IsActiveFlag_USBBOOST() == 0U) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the internal USB HS transceiver supply.
  */
void HAL_PWR_DisableVddUSBHSTransceiverSupply(void)
{
  LL_PWR_DisableUSBPowerSupply();
  LL_PWR_DisableUSBEPODBooster();
}

/**
  * @brief  Check if the internal USB HS transceiver supply is enabled.
  * @retval hal_pwr_independent_supply_status_t The USB HS transceiver supply status.
  */
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddUSBHSTransceiverSupply(void)
{
  return (hal_pwr_independent_supply_status_t)LL_PWR_IsEnabledUSBPowerSupply();
}
#endif /* PWR_VOSR_USBPWREN */
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group4
  * @{
  This section provides functions allowing to manage low power modes:
  - Call HAL_PWR_ClearCorePendingEvent() function to clear the internal cortex event before entering low power mode.
  - Call HAL_PWR_EnterSleepMode() function to enter the Core in sleep mode.
  - Call HAL_PWR_EnterStopMode() function to enter the MCU in stop x mode
  - Call HAL_PWR_EnterStandbyMode() function to enter the MCU in standby mode.
  - Call HAL_PWR_EnterShutdownMode() function to enter the MCU in shutdown mode.
  - Call HAL_PWR_SetCoreSleepMode() function to configure the Core in sleep or deep sleep mode.
  - Call HAL_PWR_GetCoreSleepMode() function to get Core sleep mode configuration.
  - Call HAL_PWR_EnableCoreSleepOnExit() function to enable Core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_DisableCoreSleepOnExit() function to disable Core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_IsEnabledCoreSleepOnExit() function to check that Core to re-entry in sleep mode is enabled.
  - Call HAL_PWR_EnableCoreSendEventOnPending() function to enable Core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_DisableCoreSendEventOnPending() function to disable Core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_IsEnabledCoreSendEventOnPending() function to check that core send event on pending is enabled.
  - Call HAL_PWR_LP_SetSmartRunDomainMode() function to Configure the Smart Run Domain mode.
  - Call HAL_PWR_LP_GetSmartRunDomainMode() function to get the Smart Run Domain mode.
  - Call HAL_PWR_LP_SetBrownoutResetMode() function to configure the brownout reset mode in standby mode.
  - Call HAL_PWR_LP_GetBrownoutResetMode() function to get the brownout reset mode configuration.
  - Call HAL_PWR_Stop3Wakeup_IRQHandler() function to handle the wakeup from Stop 3 interrupt request
  - Call HAL_PWR_Stop3WakeupCallback() function to wakeup from stop 3 interrupt callback.
  */

/**
  * @brief   Clear core pending event.
  * @note    This API clears the pending event in order to enter a given core to Sleep or Stop mode with WFE entry.
  * @warning It must be called just before APIs performing enter Sleep and Stop mode using Wait For Event request
  */
void HAL_PWR_ClearCorePendingEvent(void)
{
  __SEV();
  __WFE();
}

/**
  * @brief  Enter the core in Sleep mode.
  * @param  sleep_entry Parameter to \ref hal_pwr_low_pwr_mode_entry_t enumeration.
  */
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(sleep_entry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  if (sleep_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief  Enter the MCU in Stop mode.
  * @param  stop_entry This parameter is an element of \ref hal_pwr_low_pwr_mode_entry_t enumeration.
  * @param  stop_mode  This parameter is an element of \ref hal_pwr_stop_mode_t enumeration.
  */
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(stop_entry));
  ASSERT_DBG_PARAM(IS_PWR_STOP_MODE(stop_mode));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  LL_PWR_SetPowerMode((uint32_t)stop_mode);

  if (stop_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief  Enter the MCU in Standby mode.
  */
void HAL_PWR_EnterStandbyMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  LL_PWR_SetPowerMode(LL_PWR_STANDBY_MODE);

  /* Wait For Interrupt Request */
  __WFI();
}

/**
  * @brief  Enter the MCU in Shutdown mode.
  */
void HAL_PWR_EnterShutdownMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  LL_PWR_SetPowerMode(LL_PWR_SHUTDOWN_MODE);

  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  Set the core sleep mode configuration.
  * @param  sleep_mode This parameter is an element of \ref hal_pwr_core_sleep_mode_t enumeration.
  */
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_CORE_SLEEP_MODE(sleep_mode));

  MODIFY_REG(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk, (uint32_t)sleep_mode);
}

/**
  * @brief  Get the core sleep mode configuration.
  * @retval hal_pwr_core_sleep_mode_t The core sleep mode configuration.
  */
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void)
{
  return ((hal_pwr_core_sleep_mode_t)((uint32_t)READ_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk)));
}

/**
  * @brief  Enable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_EnableCoreSleepOnExit(void)
{
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Disable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_DisableCoreSleepOnExit(void)
{
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Check if the Core SLEEP-ON-EXIT is enabled or disabled.
  * @retval hal_pwr_core_sleep_on_exit_status_t Core sleep on exit status.
  */
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void)
{
  uint32_t dummy = READ_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk) >> SCB_SCR_SLEEPONEXIT_Pos;

  return ((hal_pwr_core_sleep_on_exit_status_t)(dummy));
}

/**
  * @brief  Enable core Send Event On Pending feature.
  */
void HAL_PWR_EnableCoreSendEventOnPending(void)
{
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable core Send Event On Pending.
  */
void HAL_PWR_DisableCoreSendEventOnPending(void)
{
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Get core Send Event On Pending.
  * @retval hal_pwr_core_sev_on_pending_status_t Core send event on pending status.
  */
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void)
{
  uint32_t dummy = READ_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk) >> SCB_SCR_SEVONPEND_Pos;

  return ((hal_pwr_core_sev_on_pending_status_t)(dummy));
}

/**
  * @brief  Set the Smart Run Domain mode when the System in Stop 0/1/2 mode.
  * @param  mode This parameter is an element of \ref hal_pwr_system_mode_srd_mode_t enumeration.
  */
void HAL_PWR_LP_SetSmartRunDomainMode(hal_pwr_system_mode_srd_mode_t mode)
{
  ASSERT_DBG_PARAM(IS_PWR_SRD_MODE(mode));

  LL_PWR_SetSmartRunDomainMode((uint32_t)mode);
}

/**
  * @brief  Get the Smart Run Domain mode when the System in Stop 0/1/2 mode.
  * @retval hal_pwr_system_mode_srd_mode_t Smart run domain in Run mod status.
  */
hal_pwr_system_mode_srd_mode_t HAL_PWR_LP_GetSmartRunDomainMode(void)
{
  return ((hal_pwr_system_mode_srd_mode_t)LL_PWR_GetSmartRunDomainMode());
}

/**
  * @brief  Set BOR ultra-low power mode.
  * @param  mode This parameter is an element of \ref hal_pwr_brownout_reset_mode_t enumeration.
  * @note   BOR operating can be in discontinuous (ultra-low power) mode in Stop 1, Stop 2, Stop 3 and Standby modes and
  *         when the regulator is in Range 4 (Run, Sleep or Stop 0 mode).
  */
void HAL_PWR_LP_SetBrownoutResetMode(hal_pwr_brownout_reset_mode_t mode)
{
  ASSERT_DBG_PARAM(IS_PWR_BOR_MODE(mode));

  LL_PWR_SetBORStandbyMode((uint32_t)mode);
}

/**
  * @brief  Get BOR ultra-low power mode.
  * @retval hal_pwr_brownout_reset_mode_t Brownout reset mode status.
  */
hal_pwr_brownout_reset_mode_t HAL_PWR_LP_GetBrownoutResetMode(void)
{
  return ((hal_pwr_brownout_reset_mode_t)LL_PWR_GetBORStandbyMode());
}

/**
  * @brief  This function handles the PWR wake-up from Stop 3 interrupt request.
  * @param  wakeup_pin This parameter can be one or a combination of the following values:
  *                    @arg HAL_PWR_WAKEUP_PIN_1  : Wakeup pin 1.
  *                    @arg HAL_PWR_WAKEUP_PIN_2  : Wakeup pin 2.
  *                    @arg HAL_PWR_WAKEUP_PIN_3  : Wakeup pin 3.
  *                    @arg HAL_PWR_WAKEUP_PIN_4  : Wakeup pin 4.
  *                    @arg HAL_PWR_WAKEUP_PIN_5  : Wakeup pin 5.
  *                    @arg HAL_PWR_WAKEUP_PIN_6  : Wakeup pin 6.
  *                    @arg HAL_PWR_WAKEUP_PIN_7  : Wakeup pin 7.
  *                    @arg HAL_PWR_WAKEUP_PIN_8  : Wakeup pin 8
  *                    @arg HAL_PWR_WAKEUP_PIN_ALL: Wakeup pin all.
  */
void HAL_PWR_Stop3Wakeup_IRQHandler(uint32_t wakeup_pin)
{
  uint32_t wakeup_active = LL_PWR_READ_REG(WUSR);
  uint32_t wakeup_source = LL_PWR_READ_REG(WUCR1) & wakeup_active;
  wakeup_source &= wakeup_pin;

  /* Check PWR wakeup pin */
  if (wakeup_source != 0U)
  {
    /* Clear PWR wake up flag */
    LL_PWR_WRITE_REG(WUSCR, wakeup_source);

    HAL_PWR_Stop3WakeupCallback(wakeup_source);
  }
}

/**
  * @brief  PWR wake-up from Stop 3 interrupt request callback.
  * @param  wakeup_pin Specifies the wake-up pin interrupt to be handled. This parameter can be one or a combination of
  *                    the following values:
  *                    @arg HAL_PWR_WAKEUP_PIN_1  : Wakeup pin 1.
  *                    @arg HAL_PWR_WAKEUP_PIN_2  : Wakeup pin 2.
  *                    @arg HAL_PWR_WAKEUP_PIN_3  : Wakeup pin 3.
  *                    @arg HAL_PWR_WAKEUP_PIN_4  : Wakeup pin 4.
  *                    @arg HAL_PWR_WAKEUP_PIN_5  : Wakeup pin 5.
  *                    @arg HAL_PWR_WAKEUP_PIN_6  : Wakeup pin 6.
  *                    @arg HAL_PWR_WAKEUP_PIN_7  : Wakeup pin 7.
  *                    @arg HAL_PWR_WAKEUP_PIN_8  : Wakeup pin 8.
  *                    @arg HAL_PWR_WAKEUP_PIN_ALL: Wakeup pin all.
  */
__WEAK void HAL_PWR_Stop3WakeupCallback(uint32_t wakeup_pin)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(wakeup_pin);

  /* NOTE : This function must not be modified; when the callback is needed,
            HAL_PWR_Stop3Wakeup_IRQHandler() API can be implemented in the user file
   */
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group5
  * @{
  This section provides functions allowing to configure voltage monitoring.
  - Call HAL_PWR_SetProgrammableVoltageDetectorLevel() function to configure the programmable voltage detector.
  - Call HAL_PWR_GetProgrammableVoltageDetectorLevel() function to get the programmable voltage detector configuration.
  - Call HAL_PWR_EnableProgrammableVoltageDetector() function to enable the Programmable Voltage Detector.
  - Call HAL_PWR_DisableProgrammableVoltageDetector() function to disable the Programmable Voltage Detector.
  - Call HAL_PWR_IsEnabledProgrammableVoltageDetector() function to check that Programmable Voltage Detector is enabled.
  - Call HAL_PWR_EnableVddUSBMonitor() function to enable the VddUSB voltage monitor.
  - Call HAL_PWR_DisableVddUSBMonitor() function to disable the VddUSB voltage monitor.
  - Call HAL_PWR_IsEnabledVddUSBMonitor() function to check if the VddUSB voltage monitor is enabled.
  - Call HAL_PWR_EnableVddIO2Monitor() function to enable the VddIO2 voltage monitor.
  - Call HAL_PWR_DisableVddIO2Monitor() function to disable the VddIO2 voltage monitor.
  - Call HAL_PWR_IsEnabledVddIO2Monitor() function to check if the VddIO2 voltage monitor is enabled.
  - Call HAL_PWR_EnableVddAMonitor1() function to enable the Vdd Analog voltage monitor 1.
  - Call HAL_PWR_DisableVddAMonitor1() function to disable the Vdd Analog voltage monitor 1.
  - Call HAL_PWR_IsEnabledVddAMonitor1() function to check if the Vdd Analog voltage monitor 1 is enabled.
  - Call HAL_PWR_EnableVddAMonitor2() function to enable the Vdd Analog voltage monitor 2.
  - Call HAL_PWR_DisableVddAMonitor2() function to disable the Vdd Analog voltage monitor 2.
  - Call HAL_PWR_IsEnabledVddAMonitor2() function to check if the Vdd Analog voltage monitor 2 is enabled.
  - Call HAL_PWR_EnableTemperatureVbatMonitor() function to enable temperature and VBAT monitor.
  - Call HAL_PWR_DisableTemperatureVbatMonitor() function to disable temperature and VBAT monitor.
  - Call HAL_PWR_IsEnabledTemperatureVbatMonitor() function to check if the temperature and VBAT monitor is enabled.
  */

/**
  * @brief  Set the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @param  level This parameter is an element of \ref hal_pwr_pvd_level_t enumeration.
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_PVD_LEVEL(level));

  LL_PWR_SetPVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @retval hal_pwr_pvd_level_t The current PVD level.
  */
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void)
{
  return ((hal_pwr_pvd_level_t)LL_PWR_GetPVDLevel());
}

/**
  * @brief  Enable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_EnableProgrammableVoltageDetector(void)
{
  LL_PWR_EnablePVD();
}

/**
  * @brief  Disable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_DisableProgrammableVoltageDetector(void)
{
  LL_PWR_DisablePVD();
}

/**
  * @brief  Check if the Programmable Voltage Detector (PVD) is enabled.
  * @retval hal_pwr_pvd_status_t The Programmable Voltage Detector status.
  */
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void)
{
  return ((hal_pwr_pvd_status_t)LL_PWR_IsEnabledPVD());
}

/**
  * @brief  Enable the Vdd USB voltage monitor.
  */
void HAL_PWR_EnableVddUSBMonitor(void)
{
  LL_PWR_EnableVddUSBMonitor();
}

/**
  * @brief  Disable the Vdd USB voltage monitor.
  */
void HAL_PWR_DisableVddUSBMonitor(void)
{
  LL_PWR_DisableVddUSBMonitor();
}

/**
  * @brief  Check if the Vdd USB voltage monitor is enabled.
  * @retval hal_pwr_monitor_status_t The Vdd USB voltage monitor status.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddUSBMonitor(void)
{
  return ((hal_pwr_monitor_status_t)LL_PWR_IsEnabledVddUSBMonitor());
}

/**
  * @brief  Enable the Vdd IO2 voltage monitor.
  */
void HAL_PWR_EnableVddIO2Monitor(void)
{
  LL_PWR_EnableVddIO2Monitor();
}

/**
  * @brief  Disable the Vdd IO2 voltage monitor.
  */
void HAL_PWR_DisableVddIO2Monitor(void)
{
  LL_PWR_DisableVddIO2Monitor();
}

/**
  * @brief  Check if the Vdd IO2 voltage monitor is enabled.
  * @retval hal_pwr_monitor_status_t The Vdd IO2 voltage monitor status.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddIO2Monitor(void)
{
  return ((hal_pwr_monitor_status_t)LL_PWR_IsEnabledVddIO2Monitor());
}

/**
  * @brief  Enable the Vdd Analog voltage monitor 1.
  */
void HAL_PWR_EnableVddAMonitor1(void)
{
  LL_PWR_EnableVddAMonitor1();
}

/**
  * @brief  Disable the Vdd Analog voltage monitor 1.
  */
void HAL_PWR_DisableVddAMonitor1(void)
{
  LL_PWR_DisableVddAMonitor1();
}

/**
  * @brief  Check if the Vdd Analog voltage monitor 1 is enabled.
  * @retval hal_pwr_monitor_status_t The Vdd analog voltage monitor 1 status.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddAMonitor1(void)
{
  return (hal_pwr_monitor_status_t)LL_PWR_IsEnabledVddAMonitor1();
}

/**
  * @brief  Enable the Vdd Analog voltage monitor 2.
  */
void HAL_PWR_EnableVddAMonitor2(void)
{
  LL_PWR_EnableVddAMonitor2();
}

/**
  * @brief  Disable the Vdd Analog voltage monitor 2.
  */
void HAL_PWR_DisableVddAMonitor2(void)
{
  LL_PWR_DisableVddAMonitor2();
}

/**
  * @brief  Check if the Vdd Analog voltage monitor 2 is enabled.
  * @retval hal_pwr_monitor_status_t The Vdd analog voltage monitor 2 status.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddAMonitor2(void)
{
  return (hal_pwr_monitor_status_t)LL_PWR_IsEnabledVddAMonitor2();
}

/**
  * @brief  Enable the temperature and VBAT monitor.
  */
void HAL_PWR_EnableTemperatureVbatMonitor(void)
{
  LL_PWR_EnableMonitoring();
}

/**
  * @brief  Disable the temperature and VBAT monitor.
  */
void HAL_PWR_DisableTemperatureVbatMonitor(void)
{
  LL_PWR_DisableMonitoring();
}

/**
  * @brief  Check if the temperature and VBAT monitor is enabled or disabled.
  * @retval hal_pwr_monitor_status_t The temperature and VBAT monitor status.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVbatMonitor(void)
{
  return ((hal_pwr_monitor_status_t)LL_PWR_IsEnabledMonitoring());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group6
  * @{
 This section provides functions allowing to manage memory content retention.
 - Call HAL_PWR_LP_EnableMemoryRetention() function to enable memory Retention.
 - Call HAL_PWR_LP_DisableMemoryRetention() function to disable memory Retention.
 - Call HAL_PWR_LP_IsEnabledMemoryRetention() function to check if memory Retention is enabled.
 - Call HAL_PWR_LP_EnableMemoryPageRetention() function to enable pages memory Retention.
 - Call HAL_PWR_LP_DisableMemoryPageRetention() function to disable pages memory Retention.
 - Call HAL_PWR_LP_IsEnabledMemoryPageRetention() function to check if memory page Retention is enabled
 - Call HAL_PWR_LP_EnableUCPDRetention() function to enable the UCPD configuration memorization in Stop 3 and
   Standby mode.
 - Call HAL_PWR_LP_DisableUCPDRetention() function to disable the UCPD configuration memorization in Stop 3 and
   Standby mode.
 - Call HAL_PWR_LP_IsEnabledUCPDRetention() function to check if the UCPD configuration memorization in Stop 3 and
   Standby mode is enabled.
 - Call HAL_PWR_LP_EnableOTGHSPHYRetention() function to enable OTG HS PHY power during LP modes (Stop2/3 and Standby)
 - Call HAL_PWR_LP_DisableOTGHSPHYRetention() function to disable OTG HS PHY power during LP modes (Stop2/3 and Standby)
 - Call HAL_PWR_LP_IsEnabledOTGHSPHYRetention() function to check if the UOTG HS PHY power during LP modes is enabled.
  */

/**
  * @brief  Enable memory retention.
  * @param  memory This parameter is an element of \ref hal_pwr_memory_retention_t enumeration.
  * @retval HAL_OK The memory retention is successfully enabled.
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  if (memory == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)
  {
    LL_PWR_EnableBkUpRegulator();
  }
  else if (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)
  {
    LL_PWR_EnableMemoryStandbyRetention(PWR_MemoryFullRetentionMap[memory]);
  }
  else if ((memory == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)
#if defined(PWR_CR1_SRAM6PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)\
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#elif defined(PWR_CR1_SRAM5PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#elif defined(PWR_CR1_SRAM3PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#endif /* PWR_CR1_SRAM6PD */
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN))
  {
    LL_PWR_EnableMemoryRunRetention(PWR_MemoryFullRetentionMap[memory]);
  }
  else
  {
#if defined(PWR_CR5_SRAM6PDS1)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)
    {
      LL_PWR_SetSRAM6StopRetention(PWR_MemoryFullRetentionMap[memory]);
    }
#endif /* PWR_CR5_SRAM6PDS1 */

#if defined(PWR_CR4_SRAM5PDS1)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)
    {
      LL_PWR_SetSRAM5StopRetention(PWR_MemoryFullRetentionMap[memory]);
    }
#endif /* PWR_CR4_SRAM5PDS1 */

#if defined(PWR_CR4_SRAM3PDS9)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)
    {
      LL_PWR_SetSRAM3StopRetention_9_13(LL_PWR_SRAM3_STOP_9_13_RETENTION);
    }
#endif /* PWR_CR4_SRAM3PDS9 */

#if defined(PWR_CR4_SRAM1PDS4)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)
    {
      LL_PWR_SetSRAM1StopRetention_4_12(LL_PWR_SRAM1_STOP_4_12_RETENTION);
    }
#endif /* PWR_CR4_SRAM1PDS4 */

#if defined(PWR_CR5_SRAM6PDS1)
    if ((memory != HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123) && (memory != HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123))
#elif defined(PWR_CR4_SRAM5PDS1)
    if (memory != HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)
#endif /* PWR_CR5_SRAM6PDS1 */
    {
      LL_PWR_EnableMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable memory retention.
  * @param  memory  This parameter is an element of \ref hal_pwr_memory_retention_t enumeration.
  */
void HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  if (memory == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)
  {
    LL_PWR_DisableBkUpRegulator();
  }
  else if (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)
  {
    LL_PWR_DisableMemoryStandbyRetention(PWR_MemoryFullRetentionMap[memory]);
  }
  else if ((memory == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)
#if defined(PWR_CR1_SRAM6PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)\
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#elif defined(PWR_CR1_SRAM5PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#elif defined(PWR_CR1_SRAM3PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#endif /* PWR_CR1_SRAM6PD */
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN))
  {
    LL_PWR_DisableMemoryRunRetention(PWR_MemoryFullRetentionMap[memory]);
  }
  else
  {
#if defined(PWR_CR5_SRAM6PDS1)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)
    {
      LL_PWR_SetSRAM6StopRetention(LL_PWR_SRAM6_STOP_NO_RETENTION);
    }
#endif /* PWR_CR5_SRAM6PDS1 */

#if defined(PWR_CR4_SRAM5PDS1)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)
    {
      LL_PWR_SetSRAM5StopRetention(LL_PWR_SRAM5_STOP_NO_RETENTION);
    }
#endif /* PWR_CR4_SRAM5PDS1 */

#if defined(PWR_CR4_SRAM3PDS9)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)
    {
      LL_PWR_SetSRAM3StopRetention_9_13(LL_PWR_SRAM3_STOP_NO_RETENTION);
    }
#endif /* PWR_CR4_SRAM3PDS9 */

#if defined(PWR_CR4_SRAM1PDS4)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)
    {
      LL_PWR_SetSRAM1StopRetention_4_12(LL_PWR_SRAM1_STOP_NO_RETENTION);
    }
#endif /* PWR_CR4_SRAM1PDS4 */

#if defined(PWR_CR5_SRAM6PDS1)
    if ((memory != HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123) && (memory != HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123))
#elif defined(PWR_CR4_SRAM5PDS1)
    if (memory != HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)
#endif /* PWR_CR5_SRAM6PDS1 */
    {
      LL_PWR_DisableMemoryStopRetention(PWR_MemoryFullRetentionMap[memory]);
    }
  }
}

/**
  * @brief  Check if the memory retention is enabled.
  * @param  memory  This parameter is an element of \ref hal_pwr_memory_retention_t enumeration.
  * @retval hal_pwr_memory_retention_status_t The memory retention status.
  */
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory)
{
  uint32_t retention = 0U;

  ASSERT_DBG_PARAM(IS_PWR_GET_MEMORY_RETENTION(memory));

  if (memory == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)
  {
    retention = LL_PWR_IsEnabledBkUpRegulator();
  }
  else if ((memory == HAL_PWR_MEMORY_RETENTION_SRAM1_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_RUN)
#if defined(PWR_CR1_SRAM6PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM6_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN)\
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#elif defined(PWR_CR1_SRAM5PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_RUN) || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#elif defined(PWR_CR1_SRAM3PD)
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_RUN)
#endif /* PWR_CR1_SRAM6PD */
           || (memory == HAL_PWR_MEMORY_RETENTION_SRAM4_RUN))
  {
    retention = LL_PWR_IsEnabledMemoryRunRetention(PWR_GetMemoryFullRetentionMap[memory]);
  }
  else
  {
    retention = LL_PWR_IsEnabledMemoryStopRetention(PWR_GetMemoryFullRetentionMap[memory]);
  }

  return (hal_pwr_memory_retention_status_t)retention;
}

/**
  * @brief  Enable memory pages retention.
  * @param  memory   This parameter is an element of \ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx The starting page of memory.
  * @param  page_nbr The memory pages number.
  */
void HAL_PWR_LP_EnableMemoryPageRetention(hal_pwr_memory_retention_t memory, uint32_t page_idx, uint32_t page_nbr)
{
  uint32_t count;
  uint32_t reg_pages_msk;
  uint32_t all_pages_msk = 0U;
  uint32_t tmp_page_idx = page_idx;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr));

  count = page_nbr + tmp_page_idx;

  /* Calculate the mask to be set in the registers */
  while (tmp_page_idx < count)
  {
    all_pages_msk |= (1UL << (tmp_page_idx - 1U));
    tmp_page_idx ++;
  }

  reg_pages_msk = (all_pages_msk & PWR_MemoryPagesRetentionCR2Map[memory].msk) <<
                  PWR_MemoryPagesRetentionCR2Map[memory].pos;

  if (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)
  {
    LL_PWR_EnableMemoryStandbyRetention(reg_pages_msk);
  }
  else
  {
    LL_PWR_EnableMemoryPageStopRetention_CR2(reg_pages_msk);

#if defined(PWR_CR4_SRAM5PDS1)
    /* Mask to be set in the register CR4 */
    reg_pages_msk = ((all_pages_msk & PWR_MemoryPagesRetentionCR4Map[memory].msk) >>
                     (POSITION_VAL(~PWR_MemoryPagesRetentionCR2Map[memory].msk))) <<
                    PWR_MemoryPagesRetentionCR4Map[memory].pos;

    LL_PWR_EnableMemoryPageStopRetention_CR4(reg_pages_msk);
#endif /* PWR_CR4_SRAM5PDS1 */

#if defined(PWR_CR5_SRAM6PDS1)
    /* Mask to be set in the register CR5 */
    reg_pages_msk = (all_pages_msk & PWR_MemoryPagesRetentionCR5Map[memory].msk) <<
                    PWR_MemoryPagesRetentionCR5Map[memory].pos;

    LL_PWR_EnableMemoryPageStopRetention_CR5(reg_pages_msk);
#endif /* PWR_CR5_SRAM6PDS1 */
  }
}

/**
  * @brief  Disable memory pages retention.
  * @param  memory    This parameter is an element of \ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  The starting page of memory.
  * @param  page_nbr  The memory pages number.
  */
void HAL_PWR_LP_DisableMemoryPageRetention(hal_pwr_memory_retention_t memory, uint32_t page_idx,
                                           uint32_t page_nbr)
{
  uint32_t count;
  uint32_t reg_pages_msk;
  uint32_t all_pages_msk = 0U;
  uint32_t tmp_page_idx = page_idx;

  ASSERT_DBG_PARAM(IS_PWR_MEMORY_PAGES_RETENTION(memory, page_idx, page_nbr));

  count = page_nbr + tmp_page_idx;

  /* Calculate the mask to be set in the registers */
  while (tmp_page_idx < count)
  {
    all_pages_msk |= (1UL << (tmp_page_idx - 1U));
    tmp_page_idx ++;
  }

  reg_pages_msk = (all_pages_msk & PWR_MemoryPagesRetentionCR2Map[memory].msk) <<
                  PWR_MemoryPagesRetentionCR2Map[memory].pos;

  if (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)
  {
    LL_PWR_DisableMemoryStandbyRetention(reg_pages_msk);
  }
  else
  {
    LL_PWR_DisableMemoryPageStopRetention_CR2(reg_pages_msk);

#if defined(PWR_CR4_SRAM5PDS1)
    /* Mask to be set in the register CR4 */
    reg_pages_msk = ((all_pages_msk & PWR_MemoryPagesRetentionCR4Map[memory].msk) >>
                     (POSITION_VAL(~PWR_MemoryPagesRetentionCR2Map[memory].msk))) <<
                    PWR_MemoryPagesRetentionCR4Map[memory].pos;

    LL_PWR_DisableMemoryPageStopRetention_CR4(reg_pages_msk);
#endif /* PWR_CR4_SRAM5PDS1 */

#if defined(PWR_CR5_SRAM6PDS1)
    /* Mask to be set in the register CR5 */
    reg_pages_msk = (all_pages_msk & PWR_MemoryPagesRetentionCR5Map[memory].msk) <<
                    PWR_MemoryPagesRetentionCR5Map[memory].pos;

    LL_PWR_DisableMemoryPageStopRetention_CR5(reg_pages_msk);
#endif /* PWR_CR5_SRAM6PDS1 */
  }
}

/**
  * @brief  Check if the memory page retention is enabled.
  * @param  memory    This parameter is an element of \ref hal_pwr_memory_retention_t enumeration.
  * @param  page_idx  The index of memory page.
  * @retval hal_pwr_memory_page_retention_status_t The memory page retention status.
  */
hal_pwr_memory_page_retention_status_t HAL_PWR_LP_IsEnabledMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                                               uint32_t page_idx)
{
  uint32_t retention = 0U;
  uint32_t pages_msk = (1UL << (page_idx - 1U));

  ASSERT_DBG_PARAM(IS_PWR_GET_MEMORY_PAGE_RETENTION(memory, page_idx));

  if (memory == HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY)
  {
    retention = LL_PWR_IsEnabledMemoryStandbyRetention(pages_msk << 5U);
  }
  else if (memory == HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123)
  {
    retention = LL_PWR_IsEnabledSRAM1StopRetention_1_3(pages_msk);

#if defined(PWR_CR4_SRAM1PDS4)
    if (page_idx > 3U)
    {
      retention = LL_PWR_IsEnabledSRAM1StopRetention_4_12(pages_msk >> 3U);
    }
#endif /* PWR_CR4_SRAM1PDS4 */
  }
  else
  {

#if defined(PWR_CR5_SRAM6PDS1)
    if (memory == HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123)
    {
      retention = LL_PWR_IsEnabledSRAM6StopRetention(pages_msk);
    }
    else
    {
#endif /* PWR_CR5_SRAM6PDS1 */

#if defined(PWR_CR4_SRAM5PDS1)
      if (memory == HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123)
      {
        retention = LL_PWR_IsEnabledSRAM5StopRetention(pages_msk << 16U);
      }
      else
      {
#endif /* PWR_CR4_SRAM5PDS1 */

#if defined(PWR_CR1_SRAM3PD)
        if (memory == HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123)
        {
          retention = LL_PWR_IsEnabledSRAM3StopRetention_1_8(pages_msk << 16U);

#if defined(PWR_CR4_SRAM3PDS9)
          if (page_idx > 8U)
          {
            retention = LL_PWR_IsEnabledSRAM3StopRetention_9_13(pages_msk << 2U);
          }
#endif /* PWR_CR4_SRAM3PDS9 */
        }
        else
        {
#endif /* PWR_CR1_SRAM3PD */

          retention = LL_PWR_IsEnabledSRAM2StopRetention(pages_msk << 4U);

#if defined(PWR_CR1_SRAM3PD)
        }
#endif /* PWR_CR1_SRAM3PD */

#if defined(PWR_CR4_SRAM5PDS1)
      }
#endif /* PWR_CR4_SRAM5PDS1 */

#if defined(PWR_CR5_SRAM6PDS1)
    }
#endif /* PWR_CR5_SRAM6PDS1 */
  }

  return (hal_pwr_memory_page_retention_status_t)retention;
}

#if defined(PWR_UCPDR_UCPD_STDBY)
/**
  * @brief  Enable the UCPD configuration memorization in Stop 3 and Standby mode.
  * @note   This function must be called just before entering Stop 3 or Standby mode.
  */
void HAL_PWR_LP_EnableUCPDRetention(void)
{
  LL_PWR_EnableUCPDStandbyMode();
}

/**
  * @brief  Disable UCPD configuration memorization in Stop 3 and Standby mode.
  * @note   This function must be called on exiting the Stop 3 or Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_DisableUCPDRetention(void)
{
  LL_PWR_DisableUCPDStandbyMode();
}

/**
  * @brief  Check if the UCPD is enabled.
  * @retval hal_pwr_ucpd_retention_status_t The UCPD retention status.
  */
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void)
{
  return (hal_pwr_ucpd_retention_status_t)LL_PWR_IsEnabledUCPDStandbyMode();
}
#endif /* PWR_UCPDR_UCPD_STDBY */

#if defined(PWR_CR1_FORCE_USBPWR)
/**
  * @brief  Enable OTG HS PHY power during low power modes (Stop2, Stop3 and Standby).
  */
void HAL_PWR_LP_EnableOTGHSPHYRetention(void)
{
  LL_PWR_EnableOTGHSPHYLowPowerRetention();
}

/**
  * @brief  Disable OTG HS PHY power during low power modes (Stop2, Stop3 and Standby).
  */
void HAL_PWR_LP_DisableOTGHSPHYRetention(void)
{
  LL_PWR_DisableOTGHSPHYLowPowerRetention();
}

/**
  * @brief  Check if the OTG HS PHY power during low power modes (Stop2, Stop 3 and Standby) is enabled.
  * @retval hal_pwr_otghsphy_retention_status_t The OTG HS PHY status.
  */
hal_pwr_otghsphy_retention_status_t HAL_PWR_LP_IsEnabledOTGHSPHYRetention(void)
{
  return (hal_pwr_otghsphy_retention_status_t)LL_PWR_IsEnabledOTGHSPHYLowPowerRetention();
}
#endif /* PWR_CR1_FORCE_USBPWR */
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group7
  * @{
  This section provides functions allowing to manage memories fast wake-up.
  - Call HAL_PWR_LP_EnableMemoryFastWakeup() function to enable the memories fast wakeup from stop x mode.
  - Call HAL_PWR_LP_DisableMemoryFastWakeup() function to disable the memories fast wakeup from stop x mode.
  - Call HAL_PWR_LP_IsEnabledMemoryFastWakeup() function to check if the memories fast wakeup from stop x mode
    is enabled.
  */

/**
  * @brief  Enable the memories fast wakeup from stop mode.
  * @param  memories Specifies the memories to be selected.
  *                  This parameter can be one or a combination of the following values:
  *                  @arg HAL_PWR_FLASH_STOP01_FAST_WAKEUP  : Flash fast wake-up.
  *                  @arg HAL_PWR_SRAM4_STOP012_FAST_WAKEUP : SRAM4 fast wake-up.
  *                  @arg HAL_PWR_MEMORIES_FAST_WAKEUP_ALL  : All memories fast wake-up.
  */
void HAL_PWR_LP_EnableMemoryFastWakeup(uint32_t memories)
{
  ASSERT_DBG_PARAM(IS_PWR_FAST_WAKEUP(memories));

  LL_PWR_EnableFastWakeup(memories);
}

/**
  * @brief  Disable the  memories fast wakeup from stop mode.
  * @param  memories Specifies the memories to be selected.
  *                  This parameter can be one or a combination of the following values:
  *                  @arg HAL_PWR_FLASH_STOP01_FAST_WAKEUP  : Flash fast wake-up.
  *                  @arg HAL_PWR_SRAM4_STOP012_FAST_WAKEUP : SRAM4 fast wake-up.
  *                  @arg HAL_PWR_MEMORIES_FAST_WAKEUP_ALL  : All memories fast wake-up.
  */
void HAL_PWR_LP_DisableMemoryFastWakeup(uint32_t memories)
{
  ASSERT_DBG_PARAM(IS_PWR_FAST_WAKEUP(memories));

  LL_PWR_DisableFastWakeup(memories);
}

/**
  * @brief Check the flash and SRAM4 memories fast wakeup from Stop mode is enabled.
  * @param memory This parameter can be one of the following values:
  *        @arg @ref HAL_PWR_FLASH_STOP01_FAST_WAKEUP
  *        @arg @ref HAL_PWR_SRAM4_STOP012_FAST_WAKEUP
  * @retval hal_pwr_memory_fast_wakeup_status_t The memory fast wakeup status.
  */
hal_pwr_memory_fast_wakeup_status_t HAL_PWR_LP_IsEnabledMemoryFastWakeup(uint32_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_FAST_WAKEUP(memory));

  return (hal_pwr_memory_fast_wakeup_status_t)LL_PWR_IsEnabledFastWakeup(memory);
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group8
  * @{
  This section provides functions allowing to manage battery charging.
  - Call HAL_PWR_SetConfigBatteryCharging() function to configure the battery charging resistor.
  - Call HAL_PWR_GetConfigBatteryCharging() function to get the battery charging resistor configuration.
  - Call HAL_PWR_EnableBatteryCharging() function to enable the battery charging.
  - Call HAL_PWR_DisableBatteryCharging() function to disable the battery charging.
  - Call HAL_PWR_IsEnabledBatteryCharging() function to check if the battery charging is enabled.
  - Call HAL_PWR_LP_EnableUCPDDeadBattery() function to enable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_DisableUCPDDeadBattery() function to disable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_IsEnabledUCPDDeadBattery() function to check that UCPD dead battery behavior is enabled or disabled.
  */

/**
  * @brief  Set the Battery charging resistor.
  * @param  value Specifies the charging resistor.
  *               This parameter can be one of the following values:
  *               @arg HAL_PWR_BATTERY_CHARGING_RES_5K   : 5 KOhm resistor.
  *               @arg HAL_PWR_BATTERY_CHARGING_RES_1_5K : 1.5 KOhm resistor.
  * @note   When Vdd is present, charge the external battery through an internal resistor.
  */
void HAL_PWR_SetConfigBatteryCharging(hal_pwr_battery_charging_res_value_t value)
{
  ASSERT_DBG_PARAM(IS_PWR_BATTERY_RESISTOR_SELECT(value));

  LL_PWR_SetBattChargResistor((uint32_t)value);
}

/**
  * @brief  Get the Battery charging resistor.
  * @note   When Vdd is present, charge the external battery through an internal resistor.
  * @retval hal_pwr_battery_charging_res_value_t The battery charging resistor value.
  */
hal_pwr_battery_charging_res_value_t HAL_PWR_GetConfigBatteryCharging(void)
{
  return ((hal_pwr_battery_charging_res_value_t)LL_PWR_GetBattChargResistor());
}

/**
  * @brief  Enable the Battery charging.
  */
void HAL_PWR_EnableBatteryCharging(void)
{
  LL_PWR_EnableBatteryCharging();
}

/**
  * @brief  Disable the Battery charging.
  */
void HAL_PWR_DisableBatteryCharging(void)
{
  LL_PWR_DisableBatteryCharging();
}

/**
  * @brief  Check that battery charging is enabled.
  * @retval hal_pwr_battery_charging_status_t The battery charging status.
  */
hal_pwr_battery_charging_status_t HAL_PWR_IsEnabledBatteryCharging(void)
{
  return ((hal_pwr_battery_charging_status_t)LL_PWR_IsEnabledBatteryCharging());
}

#if defined(PWR_UCPDR_UCPD_DBDIS)
/**
  * @brief  Enable dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_EnableUCPDDeadBattery(void)
{
  LL_PWR_EnableUCPDDeadBattery();
}

/**
  * @brief  Disable dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_DisableUCPDDeadBattery(void)
{
  LL_PWR_DisableUCPDDeadBattery();
}

/**
  * @brief  Check that UCPD dead battery battery is enabled.
  * @retval hal_pwr_ucpd_dead_battery_status_t The UCPD dead battery status.
  */
hal_pwr_ucpd_dead_battery_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void)
{
  return (hal_pwr_ucpd_dead_battery_status_t)LL_PWR_IsEnabledUCPDDeadBattery();
}
#endif /* PWR_UCPDR_UCPD_DBDIS */

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group9
  * @{
  This section provides functions allowing to manage power GPIO pull.
  - Call HAL_PWR_SetConfigGPIOPull() function to configure GPIO Pull.
  - Call HAL_PWR_GetConfigGPIOPull() function to get GPIO Pull configuration.
  - Call HAL_PWR_EnableGPIOPull() function to enable GPIO pull configuration.
  - Call HAL_PWR_DisableGPIOPull() function to disable GPIO pull configuration.
  - Call HAL_PWR_IsEnabledGPIOPull() function to check that GPIO pull configuration is enabled or disabled.
  */

/**
  * @brief Set GPIO pull configuration.
  * @param port This parameter is an element of \ref hal_pwr_gpio_port_t enumeration.
  * @param pin  Specify the I/O pin mask to be configured.
  * @param pull This parameter is an element of \ref hal_pwr_gpio_pull_t enumeration.
  */
void HAL_PWR_SetConfigGPIOPull(hal_pwr_gpio_port_t port, uint32_t pin, hal_pwr_gpio_pull_t pull)
{
  ASSERT_DBG_PARAM(IS_PWR_GPIO_PIN_PULL_SET_CONFIG(port, pin, pull));

  if (pull == HAL_PWR_GPIO_NOPULL)
  {
    LL_PWR_DisableGPIOPullUp((uint32_t)port, pin);
    LL_PWR_DisableGPIOPullDown((uint32_t)port, pin);
  }
  else if (pull == HAL_PWR_GPIO_PULLUP)
  {
    LL_PWR_DisableGPIOPullDown((uint32_t)port, pin);
    LL_PWR_EnableGPIOPullUp((uint32_t)port, pin);

  }
  else
  {
    LL_PWR_DisableGPIOPullUp((uint32_t)port, pin);
    LL_PWR_EnableGPIOPullDown((uint32_t)port, pin);
  }
}

/**
  * @brief  Get GPIO pull configuration.
  * @param  port                  This parameter is an element of \ref hal_pwr_gpio_port_t enumeration.
  * @param  pin                   Specify the I/O pins numbers.
  * @retval hal_pwr_gpio_pull_t The GPIO pull configuration.
  */
hal_pwr_gpio_pull_t HAL_PWR_GetConfigGPIOPull(hal_pwr_gpio_port_t port, uint32_t pin)
{
  hal_pwr_gpio_pull_t pull;

  ASSERT_DBG_PARAM(IS_PWR_GPIO_PIN_PULL_GET_CONFIG(pin, port));

  if (LL_PWR_IsEnabledGPIOPullUp((uint32_t)port, pin) != 0U)
  {
    pull = HAL_PWR_GPIO_PULLUP;
  }
  else if (LL_PWR_IsEnabledGPIOPullDown((uint32_t)port, pin) != 0U)
  {
    pull = HAL_PWR_GPIO_PULLDOWN;
  }
  else
  {
    pull = HAL_PWR_GPIO_NOPULL;
  }

  return pull;
}

/**
  * @brief   Enable GPIO pull configuration.
  * @warning When APC bit is set, the I/O pull-up and pull-down configurations defined in PWR_PUCRx and PWR_PDCRx
  *          registers are applied.
  * @note    Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding PDy bit of PWR_PDCRx
  *          register is also set (pull-down configuration priority is higher). HAL_PWR_LP_SetConfigGPIOPull() API
  *          ensure there is no conflict when setting PUy or PDy bit.
  */
void HAL_PWR_EnableGPIOPull(void)
{
  LL_PWR_EnablePUPDConfig();
}

/**
  * @brief   Disable GPIO pull configuration.
  * @warning When APC bit is cleared, the I/O pull-up and pull-down configurations defined in PWR_PUCRx and PWR_PDCRx
  *          registers are not applied.
  */
void HAL_PWR_DisableGPIOPull(void)
{
  LL_PWR_DisablePUPDConfig();
}

/**
  * @brief   Check that gpio pull is enabled.
  * @warning When APC bit is cleared, the I/O pull-up and pull-down configurations defined in PWR_PUCRx and PWR_PDCRx
  *          registers are not applied.
  * @retval  hal_pwr_gpio_pull_config_status_t The GPIO pull status.
  */
hal_pwr_gpio_pull_config_status_t HAL_PWR_IsEnabledGPIOPull(void)
{
  return (hal_pwr_gpio_pull_config_status_t)LL_PWR_IsEnabledPUPDConfig();
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_PWR_MODULE */

/**
  * @}
  */

/**
  * @}
  */
