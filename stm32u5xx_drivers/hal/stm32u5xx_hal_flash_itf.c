/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_flash_itf.c
  * @brief   This file provides Flash interface services.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
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

/** @addtogroup FLASH_ITF
  * @{
- This file provides firmware functions to manage the following the Flash interface functionalities:

- Flash ITF lock and unlock
- Flash ITF control
- Flash ITF option bytes configuration
- Flash ITF option bytes process

# Flash interface main features

- The Flash interface, including advanced peripheral interfacing features and "option bytes" configurations
  which often referred to as "OB" in the context of microcontrollers, are a set of configuration settings
  that can be programmed to further customize the behavior of the Flash memory and the microcontroller's features.
  The option bytes are typically stored in a special area of the Flash memory and are used to control various
  aspects of the device's operation.

## Lock mechanism:
After reset, several registers are protected against write access. An unlock sequence is mandatory.
Protected features are:
- Flash programming registers
- Option bytes programming registers

## Access latency:
- To correctly read data from flash memory, the number of wait states (latency) must be correctly programmed
  according to the frequency of the core clock and the internal voltage range of the device VCORE.

## Prefetch:
- Prefetch tends to increase the code execution performance at the cost of extra flash memory accesses.
  It must be used carefully in a low power mode application.

## Power down during run mode:
- After reset, both banks are in normal mode. In order to reduce power consumption,
  each bank can be independently put in power down during run mode.

## Power down during sleep mode:
- After reset, the flash memory is in idle mode during sleep mode. In order to reduce power consumption,
  the flash memory can be put in power down mode during sleep mode.

## Low power read mode:
- After reset, the flash memory is in normal read mode. In order to reduce power consumption,
  each bank can be independently put in low power during read mode.

## Error Code Correction:
- The flash memory is programmed in 137 bits at a time (128-bit data + 9 bits ECC).
  The ECC mechanism allows:
  - One bit error correction.
  - Two bits error detection.In this case an NMI is generated.
- The ECC mechanism protects and verifies the correctness of the flash area content. Handling of ECC errors is
  integrated within the Flash IO module. However, the control of the ECC, including enabling, disabling,
  and checking its status, is integrated within the Flash ITF module.

## Option bytes configuration:
- WRP: The user area in flash memory can be protected against unwanted write operations.
        Two write-protected (WRP) areas can be defined in each bank, with page granularity.

- RDP: The readout protection protects the flash main memory, the option bytes, the backup registers, the backup RAM
        and the SRAMs. In order to reach the best protection level, it is recommended to activate TrustZone
        and to set the RDP Level 2 with password authentication regression enabled.

- Secure Watermark-based area: When TrustZone security is active (TZEN = 1), a part of the flash memory can be
                               protected against NSecure read and write accesses. Up to two different non-volatile
                               secure areas can be defined by option bytes, and can be read or written by a secure
                               access only: one area per bank can be selected with a page granularity

- Secure hide protection area: The secure HDP area is part of the flash memory watermark-based secure area.
                               Access to the hide-protection area can be denied. When is set, instruction fetch,
                               data read, write, and erase operations on this HDP area are denied.

- Boot lock: Available only when the TrustZone is enabled, some option bytes cannot be modified when the boot lock
             mechanism is enabled.

- Boot address: The boot address option bytes are used to program any boot memory address. However, the allowed
                address space depends on flash memory read protection RDP level.

- User option bytes: There are option bytes that must include additional options to customize their behavior such as:
                     Brown-out reset level, reset generation in low power modes, memories erase, watchdog selection,
                     Independent watchdog counter freeze and unfreeze, Bank swapping, Single/Dual bank topology,
                     SRAM ECC Memories, boot0, PA15 IO PullUp, High speed VDD low voltage, TrustZone.

## Option bytes programming:
- When all new options bytes are updated in the flash memory, they are not applied to the system.
  They affect the system when they are loaded. The option bytes loading is performed in two cases:
  - When OBL_LAUNCH is set.
  - After a power reset (BOR reset or exit from Standby or Shutdown mode).

# How to use the FLASH_ITF HAL module driver

## lock and unlock functions:
- Use HAL_FLASH_ITF_Lock() to lock the access to the Flash memory area.
- Use HAL_FLASH_ITF_Unlock() to unlock the access to the Flash memory area.
- Use HAL_FLASH_ITF_IsLocked() to check the access lock state to the Flash memory area.
- Use HAL_FLASH_ITFNS_Lock() to lock the access to the NSecure Flash memory area from secure context.
- Use HAL_FLASH_ITFNS_Unlock() to unlock the access to the NSecure Flash memory area from secure context.
- Use HAL_FLASH_ITFNS_IsLocked() to check the access lock state to the NSecure Flash memory area from secure context.
- Use HAL_FLASH_ITF_OB_Lock() to lock the access to the Flash option bytes programming.
- Use HAL_FLASH_ITF_OB_Unlock() to unlock the access to the Flash option bytes programming.
- Use HAL_FLASH_ITF_OB_IsLocked() to check the lock access state to the Flash option bytes programming.

## Control functions:
- Use HAL_FLASH_ITF_SetLatency() to set the Flash latency.
- Use HAL_FLASH_ITF_GetLatency() to get the Flash latency.
- Use HAL_FLASH_ITF_EnablePrefetch() to enable the Flash prefetch feature.
- Use HAL_FLASH_ITF_DisablePrefetch() to disable the Flash prefetch feature.
- Use HAL_FLASH_ITF_IsEnabledPrefetch() to return the Flash prefetch status.
- Use HAL_FLASH_ITF_EnablePWRDownRunMode() to enable the Flash power down during run mode feature.
- Use HAL_FLASH_ITF_IsEnabledRunModePWRDown() to check the Flash power down during run mode status.
- Use HAL_FLASH_ITF_EnablePWRDownSleepMode() to enable the Flash power down during sleep mode feature.
- Use HAL_FLASH_ITF_DisablePWRDownSleepMode() to disable the Flash power down during sleep mode feature.
- Use HAL_FLASH_ITF_IsEnabledSleepModePWRDown() to check the Flash power down during sleep mode status.
- Use HAL_FLASH_ITF_EnableLowPWRReadMode() to enable the Flash low power read mode feature.
- Use HAL_FLASH_ITF_DisableLowPWRReadMode() disable the Flash low power read mode feature.
- Use HAL_FLASH_ITF_IsEnabledLowPWRReadMode() to check the Flash low power read mode status.
- Use HAL_FLASH_ITF_ECC_EnableIT() to enable the Flash ECC interruption.
- Use HAL_FLASH_ITF_ECC_DisableIT() to disable the Flash ECC interruption.
- Use HAL_FLASH_ITF_ECC_IsEnabledIT() to check the Flash ECC interruption configuration status.
- Use HAL_FLASH_ITF_IsLockedRDPOEM1Key() to check the readout protection OEM1 key lock mechanism state.
- Use HAL_FLASH_ITF_IsLockedRDPOEM2Key() to check the readout protection OEM2 key lock mechanism state.

## Option bytes configuration functions:

## WRP area configuration:
- Use HAL_FLASH_ITF_OB_SetWRPArea() to set the Flash OB WRP area boundaries configuration.
- Use HAL_FLASH_ITF_OB_GetWRPArea() to get the Flash OB WRP area boundaries configuration.
- Use HAL_FLASH_ITF_OB_LockWRPAreaConfig() to lock the Flash OB WRP area boundaries configuration.
- Use HAL_FLASH_ITF_OB_UnlockWRPAreaConfig() to unlock the Flash OB WRP area boundaries configuration.
- Use HAL_FLASH_ITF_OB_IsLockedWRPAreaConfig() to Check the Flash OB WRP area boundaries configuration status.

## RDP level configuration:
- Use HAL_FLASH_ITF_OB_SetRDPLevel() to set the Flash OB readout protection level.
- Use HAL_FLASH_ITF_OB_GetRDPLevel() to get the Flash OB readout protection level.
- Use HAL_FLASH_ITF_OB_SetRDPOEM1Key() to set the Flash OB readout protection OEM1 key.
- Use HAL_FLASH_ITF_OB_SetRDPOEM2Key() to set the Flash OB readout protection OEM2 key.

## BOR level configuration:
- Use HAL_FLASH_ITF_OB_SetBORLevel() to set the Flash OB BOR level.
- Use HAL_FLASH_ITF_OB_GetBORLevel() to get the Flash OB BOR level.

## Enter low power mode reset generation configuration:
- Use HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() to set the Flash OB enter low power mode
  reset generation.
- Use HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() to get the Flash OB enter low power mode
  reset generation.

## SRAM Erase system reset configuration:
- Use HAL_FLASH_ITF_OB_SetSystemRstSRAMErase() to set the Flash OB SRAM erase system reset configuration.
- Use HAL_FLASH_ITF_OB_GetSystemRstSRAMErase() to get the Flash OB SRAM erase system reset configuration.

## WDG Mode configuration:
- Use HAL_FLASH_ITF_OB_SetIWDGMode() to set the Flash OB IWDG mode.
- Use HAL_FLASH_ITF_OB_GetIWDGMode() to get the Flash OB IWDG mode.
- Use HAL_FLASH_ITF_OB_SetWWDGMode() to set the Flash OB WWDG mode.
- Use HAL_FLASH_ITF_OB_GetWWDGMode() to get the Flash OB WWDG mode.

## WDG Counter freeze configuration:
- Use HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode() to freeze the Flash OB IWDG counter in stop mode
  or standby mode.
- Use HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode() to unfreeze the Flash OB IWDG counter in stop mode
  or standby mode.
- Use HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode() to check the Flash OB IWDG stop mode or standby mode
  counter freeze configuration status.

## Bank Swapping configuration:
- Use HAL_FLASH_ITF_OB_SetBankSwap() to set the Flash OB swap bank configuration.
- Use HAL_FLASH_ITF_OB_GetBankSwap() to get the Flash OB swap bank configuration.

## Bank Topology configuration:
- Use HAL_FLASH_ITF_OB_SetBankTopology() to set the Flash OB single dual bank configuration.
- Use HAL_FLASH_ITF_OB_GetBankTopology() to get the Flash OB single dual bank configuration.

## SRAM ECC configuration:
- Use HAL_FLASH_ITF_OB_EnableSRAMECC() to enable the Flash OB SRAM ECC configuration.
- Use HAL_FLASH_ITF_OB_DisableSRAMECC() to disable the Flash OB SRAM ECC configuration.
- Use HAL_FLASH_ITF_OB_IsEnabledSRAMECC() to check the Flash OB SRAM ECC configuration status.

## boot0 configuration:
- Use HAL_FLASH_ITF_OB_SetBoot0() to set the Flash OB boot0 configuration.
- Use HAL_FLASH_ITF_OB_GetBoot0() to get the Flash OB boot0 configuration.

## I/O PullUP configuration:
- Use HAL_FLASH_ITF_OB_SetIOPull() to set the Flash OB PA15 PullUP configuration.
- Use HAL_FLASH_ITF_OB_GetIOPull() to get the Flash OB PA15 PullUP configuration status.

## High-speed IO at low VDD voltage configuration:
- Use HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage() to enable the Flash OB High-speed IO at low VDD
  voltage configuration
- Use HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage() to disable the Flash OB High-speed IO at low VDD
  voltage configuration
- Use HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage() to check the Flash OB High-speed IO at low VDD
  voltage configuration status.

## TrustZone configuration:
- Use HAL_FLASH_ITF_OB_EnableTrustZone() to enable the Flash OB TrustZone configuration.
- Use HAL_FLASH_ITF_OB_DisableTrustZone() to disable the Flash OB TrustZone configuration.
- Use HAL_FLASH_ITF_OB_IsEnabledTrustZone() to check the Flash OB TrustZone configuration status.

## Secure WaterMark configuration:
- Use HAL_FLASH_ITF_OB_SetSecureWMArea() to set the Flash OB secure watermark area boundaries configuration.
- Use HAL_FLASH_ITF_OB_GetSecureWMArea() to get the Flash OB secure watermark area boundaries configuration.

## Hide protection configuration:
- Use HAL_FLASH_ITF_OB_SetConfigHDPArea() to set the Flash OB hide protection area boundaries configuration.
- Use HAL_FLASH_ITF_OB_GetConfigHDPArea() to get the Flash OB hide protection area boundaries configuration.
- Use HAL_FLASH_ITF_OB_EnableHDPArea() to enable the Flash OB hide protection area boundaries configuration.
- Use HAL_FLASH_ITF_OB_DisableHDPArea() to disable the Flash OB hide protection area boundaries configuration.
- Use HAL_FLASH_ITF_OB_IsEnabledHDPArea() to Check the Flash OB hide protection area configuration status.

## Boot address configuration:
- Use HAL_FLASH_ITF_OB_SetSecureBootAddr() to set the Flash OB secure boot address configuration.
- Use HAL_FLASH_ITF_OB_GetSecureBootAddr() to get the Flash OB secure boot address configuration.
- Use HAL_FLASH_ITF_OB_SetNSecureBootAddr() to set the Flash OB NSecure boot address configuration.
- Use HAL_FLASH_ITF_OB_GetNSecureBootAddr() to get the Flash OB NSecure boot address configuration.
- Use HAL_FLASH_ITF_OB_LockBootConfig() to lock the Flash OB secure boot address configuration.
- Use HAL_FLASH_ITF_OB_UnlockBootConfig() to unlock the Flash OB secure boot address configuration.
- Use HAL_FLASH_ITF_OB_IsLockedBootConfig() to Check the Flash OB secure boot address configuration status.

## IRQHandler and Callback functions:
- Use HAL_FLASH_ITF_IRQHandler() to handle Flash OB write and error operations.
- Use HAL_FLASH_ITF_OB_ProgramCpltCallback() to be redefined within user application for the OB complete write
  operation callback.
- Use HAL_FLASH_ITF_OB_ErrorCallback() to be redefined within user application for the OB write error
  operation callback.

## Option bytes programming
- Use HAL_FLASH_ITF_OB_Program() to program the Flash option bytes interface.
- Use HAL_FLASH_ITF_OB_Launch() to launch Flash option bytes interface.

# Configuration inside the Flash ITF driver

Configuration defines         | Description     | Default value     | Note                                             |
------------------------------|-----------------|-------------------|--------------------------------------------------|
PRODUCT                       | from IDE        |        NA         | The selected device (e.g., STM32U575xx)          |
USE_HAL_FLASH_ITF_MODULE      | from hal_conf.h |         1         | Allows usage of Flash interface HAL module       |
USE_HAL_FLASH_ITF_ECC         | from hal_conf.h |         1         | Allows enabling ECC mechanism interrupt          |
USE_ASSERT_DBG_PARAM          | from IDE        |       None        | Allows usage of parameter assertions             |
USE_HAL_CHECK_PARAM           | from hal_conf.h |         0         | Allows usage of run-time parameter checks        |
__ARM_FEATURE_CMSE            | from IDE        |         3         | Allows usage of secure access for current context|

  */

#if defined (USE_HAL_FLASH_ITF_MODULE) && (USE_HAL_FLASH_ITF_MODULE == 1U)

/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Constants FLASH ITF Private Constants
  * @{
  */
#define FLASH_ITF_BANK_MAX_PAGE_NBR (FLASH_SIZE_DEFAULT / FLASH_PAGE_SIZE / 2U) /*!< Flash ITF Max page number
                                                                                     per bank                  */
#define FLASH_ITF_OB_LOW_PWR_MSK    (HAL_FLASH_ITF_OB_STOP_MODE    | \
                                     HAL_FLASH_ITF_OB_STANDBY_MODE | \
                                     HAL_FLASH_ITF_OB_SHUTDOWN_MODE)            /*!< Flash ITF Low power mask  */

#define FLASH_ITF_OB_SRAM_ERASE_MSK (HAL_FLASH_ITF_OB_SRAM | \
                                     HAL_FLASH_ITF_OB_SRAM2)                    /*!< Flash ITF SRAM erase mask */

#define FLASH_ITF_OB_WDG_MSK        (HAL_FLASH_ITF_OB_IWDG | \
                                     HAL_FLASH_ITF_OB_WWDG)                     /*!< Flash ITF WDG mask        */

#if defined (SRAM3_BASE)
#define FLASH_ITF_OB_SRAM_ECC_MSK   (HAL_FLASH_ITF_OB_BKPRAM | \
                                     HAL_FLASH_ITF_OB_SRAM2  | \
                                     HAL_FLASH_ITF_OB_SRAM3)                    /*!< Flash ITF SRAM ECC mask   */
#else
#define FLASH_ITF_OB_SRAM_ECC_MSK   (HAL_FLASH_ITF_OB_BKPRAM | \
                                     HAL_FLASH_ITF_OB_SRAM2)                    /*!< Flash ITF SRAM ECC mask   */
#endif /* SRAM3_BASE */

#define HAL_FLASH_ITF_OB_VDDIO_MSK  (HAL_FLASH_ITF_OB_VDDIO | \
                                     HAL_FLASH_ITF_OB_VDDIO2)                   /*!< Flash ITF VDDIO mask      */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Macros FLASH ITF Private Macros
  * @{
  */

/*! Macro to check Flash ITF latency value */
#define IS_FLASH_ITF_LATENCY(value) (((value) == HAL_FLASH_ITF_LATENCY_0)     \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_1)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_2)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_3)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_4)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_5)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_6)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_7)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_8)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_9)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_10) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_11) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_12) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_13) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_14) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_15))

/*! Macro to check Flash ITF Bank Selection */
#define IS_FLASH_ITF_BANK(value) (((value) == HAL_FLASH_ITF_BANK_1) \
                                  || ((value) == HAL_FLASH_ITF_BANK_2))

/*! Macro to check Flash ITF OB Bank Area */
#define IS_FLASH_ITF_OB_BANK_AREA(value) (((value) == HAL_FLASH_ITF_OB_BANK_AREA_A) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_AREA_B))

/*! Macro to check Flash ITF OB RDP Level */
#define IS_FLASH_ITF_OB_RDP_LEVEL(value) (((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_0)      \
                                          || ((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_0_5) \
                                          || ((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_1)   \
                                          || ((value) == HAL_FLASH_ITF_OB_RDP_LEVEL_2))

/*! Macro to check Flash ITF OB RDP OEM key */
#define IS_FLASH_ITF_OB_RDP_OEM_KEY_TYPE(value) (((value) == HAL_FLASH_ITF_OB_RDP_KEY_OEM1) \
                                                 || ((value) == HAL_FLASH_ITF_OB_RDP_KEY_OEM2))

/*! Macro to check Flash ITF OB BOR Level */
#define IS_FLASH_ITF_OB_BOR_LEVEL(value) (((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_0)    \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_1) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_2) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_3) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_4))

/*! Macro to check Flash ITF OB Low power mode */
#define IS_FLASH_ITF_OB_LOW_PWR_MODE(value) (((value) == HAL_FLASH_ITF_OB_STOP_MODE)       \
                                             || ((value) == HAL_FLASH_ITF_OB_STANDBY_MODE) \
                                             || ((value) == HAL_FLASH_ITF_OB_SHUTDOWN_MODE))

/*! Macro to check Flash ITF OB Low power mode reset generation */
#define IS_FLASH_OB_RST_GENERATION(value) (((value) == HAL_FLASH_ITF_OB_RST_GENERATION) \
                                           || ((value) == HAL_FLASH_ITF_OB_NO_RST_GENERATION))

/*! Macro to check Flash ITF OB SRAM Erase*/
#define IS_FLASH_ITF_OB_SRAM_ERASE(value) (((value) == HAL_FLASH_ITF_OB_SRAM2) \
                                           || ((value) == HAL_FLASH_ITF_OB_SRAM))

/*! Macro to check Flash ITF OB SRAM erase system reset */
#define IS_FLASH_ITF_OB_SYS_RST_SRAM_ERASE(value) (((value) == HAL_FLASH_ITF_OB_SYS_RST_SRAM_ERASE) \
                                                   || ((value) == HAL_FLASH_ITF_OB_SYS_RST_SRAM_NO_ERASE))

/*! Macro to check Flash ITF OB WDG */
#define IS_FLASH_ITF_OB_WDG(value) (((value) == HAL_FLASH_ITF_OB_IWDG) \
                                    || ((value) == HAL_FLASH_ITF_OB_WWDG))

/*! Macro to check Flash ITF OB WDG Mode */
#define IS_FLASH_ITF_OB_WDG_HW_SW_MODE(value) (((value) == HAL_FLASH_ITF_OB_WDG_HARDWARE) \
                                               || ((value) == HAL_FLASH_ITF_OB_WDG_SOFTWARE))

/*! Macro to check Flash ITF OB Bank Swap*/
#define IS_FLASH_ITF_OB_SWAP_BANK(value) (((value) == HAL_FLASH_ITF_OB_BANK_NO_SWAP) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_SWAP))

/*! Macro to check Flash ITF OB Bank Topology */
#define IS_FLASH_ITF_OB_SINGLE_DUAL_BANK(value) (((value) == HAL_FLASH_ITF_OB_SINGLE_BANK) \
                                                 || ((value) == HAL_FLASH_ITF_OB_DUAL_BANK))

/*! Macro to check Flash ITF OB SRAM ECC */
#if defined (SRAM3_BASE)
#define IS_FLASH_ITF_OB_SRAM_ECC(value) (((value) == HAL_FLASH_ITF_OB_BKPRAM)   \
                                         || ((value) == HAL_FLASH_ITF_OB_SRAM2) \
                                         || ((value) == HAL_FLASH_ITF_OB_SRAM3))
#else
#define IS_FLASH_ITF_OB_SRAM_ECC(value) (((value) == HAL_FLASH_ITF_OB_BKPRAM) \
                                         || ((value) == HAL_FLASH_ITF_OB_SRAM2))
#endif /* SRAM3_BASE */

/*! Macro to check Flash ITF OB boot0 Selection */
#define IS_FLASH_ITF_OB_BOOT0_SELECTION(value) (((value) == HAL_FLASH_ITF_OB_BOOT_PIN) \
                                                || ((value) == HAL_FLASH_ITF_OB_BOOT_OPTION_BIT))

/*! Macro to check Flash ITF OB boot0 State */
#define IS_FLASH_ITF_OB_BOOT_STATE(value) (((value) == HAL_FLASH_ITF_OB_BOOT_LOW) \
                                           || ((value) == HAL_FLASH_ITF_OB_BOOT_HIGH))

/*! Macro to check Flash ITF OB pull mode */
#define IS_FLASH_ITF_OB_PULL_MODE(value) (((value) == HAL_FLASH_ITF_OB_PULL_NO)      \
                                          || ((value) == HAL_FLASH_ITF_OB_PULL_DOWN) \
                                          || ((value) == HAL_FLASH_ITF_OB_PULL_UP))

/*! Macro to check Flash ITF OB vdd */
#define IS_FLASH_ITF_OB_VDD(value) (((value) == HAL_FLASH_ITF_OB_VDDIO) \
                                    || ((value) == HAL_FLASH_ITF_OB_VDDIO2))

/*! Macro to check Flash ITF OB address index */
#define IS_FLASH_ITF_OB_ADDR_IDX(value) (((value) == HAL_FLASH_ITF_OB_ADDR_0) \
                                         || ((value) == HAL_FLASH_ITF_OB_ADDR_1))

/*! Macro to get the Flash Bank power down key 1 */
#define FLASH_ITF_GET_PWR_DOWN_BANK_KEY1(value) (((value) == HAL_FLASH_ITF_BANK_1) ? LL_FLASH_PDKEY1_1 \
                                                 : LL_FLASH_PDKEY2_1)

/*! Macro to get the Flash Bank power down key 2 */
#define FLASH_ITF_GET_PWR_DOWN_BANK_KEY2(value) (((value) == HAL_FLASH_ITF_BANK_1) ? LL_FLASH_PDKEY1_2 \
                                                 : LL_FLASH_PDKEY2_2)

/*! Macro to get the Flash Bank power down request*/
#define FLASH_ITF_GET_PWR_DOWN_BANK_REQUEST(value) (((value) == HAL_FLASH_ITF_BANK_1) ? LL_FLASH_PWR_DOWN_RUN_BANK_1 \
                                                    : LL_FLASH_PWR_DOWN_RUN_BANK_2)

/*! Macro to get the Flash Bank power down */
#define FLASH_ITF_GET_PWR_DOWN_BANK(value) (((value) == HAL_FLASH_ITF_BANK_1) ? LL_FLASH_FLAG_PD1 \
                                            : LL_FLASH_FLAG_PD2)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_ITF_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group1
  * @{
  * This subsection provides a set of functions for the Flash interface lock and unlock features:

  * - Call HAL_FLASH_ITF_Lock() to lock the access to the Flash memory area.

  * - Call HAL_FLASH_ITF_Unlock() to unlock the access to the Flash memory area.

  * - Call HAL_FLASH_ITF_IsLocked() to check the access lock state to the Flash memory area.

  * - Call HAL_FLASH_ITFNS_Lock() to lock the access to the Flash memory area from secure context.

  * - Call HAL_FLASH_ITFNS_Unlock() to unlock the access to the NSecure Flash memory area from secure context.

  * - Call HAL_FLASH_ITFNS_IsLocked() to check the access lock state to the NSecure Flash memory area
      from secure context.

  * - Call HAL_FLASH_ITF_OB_Lock() to lock the access to the Flash option bytes programming.

  * - Call HAL_FLASH_ITF_OB_Unlock() to unlock the access to the Flash option bytes programming.

  * - Call HAL_FLASH_ITF_OB_IsLocked() to check the lock access state to the Flash option bytes programming.

  */

/**
  * @brief  Lock the access to the Flash memory area.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash control register access is successfully locked.
  */
hal_status_t HAL_FLASH_ITF_Lock(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_Lock(flash);

  return HAL_OK;
}

/**
  * @brief  Unlock the access to the Flash memory area.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash control register access is successfully unlocked.
  */
hal_status_t HAL_FLASH_ITF_Unlock(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  if (LL_FLASH_IsLocked(flash) != 0U)
  {
    LL_FLASH_SetUnlockKey(flash, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(flash, LL_FLASH_KEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check the access lock state to the Flash memory area.
  * @param  flash                                  Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_lock_status_t            Flash control register access lock status.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_lock_status_t)LL_FLASH_IsLocked(flash));
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the access to the NSecure Flash memory area from secure context.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash NSecure control register access is successfully locked.
  */
hal_status_t HAL_FLASH_ITFNS_Lock(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_NS_Lock(flash);

  return HAL_OK;
}

/**
  * @brief  Unlock the access to the NSecure Flash memory area from secure context.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash NSecure control register access is successfully unlocked.
  */
hal_status_t HAL_FLASH_ITFNS_Unlock(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  if (LL_FLASH_NS_IsLocked(flash) != 0U)
  {
    LL_FLASH_NS_SetUnlockKey(flash, LL_FLASH_KEY1);
    LL_FLASH_NS_SetUnlockKey(flash, LL_FLASH_KEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check the access lock state to the NSecure Flash memory area from secure context.
  * @param  flash                                  Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_lock_status_t            Flash NSecure control register access lock status.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITFNS_IsLocked(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_lock_status_t)LL_FLASH_NS_IsLocked(flash));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Lock the Flash OB control register access.
  * @warning When locking the flash OB, the flash will not be locked.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash OB control register access is successfully locked.
  */
hal_status_t HAL_FLASH_ITF_OB_Lock(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_OB_Lock(flash);

  return HAL_OK;
}

/**
  * @brief  Unlock the Flash OB control register access.
  * @warning When unlocking the flash OB, the flash is unlocked as side effect.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash OB control register access is successfully unlocked.
  */
hal_status_t HAL_FLASH_ITF_OB_Unlock(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if (LL_FLASH_NS_IsLocked(flash) == 1U)
  {
    LL_FLASH_NS_SetUnlockKey(flash, LL_FLASH_KEY1);
    LL_FLASH_NS_SetUnlockKey(flash, LL_FLASH_KEY2);
  }
#else
  if (LL_FLASH_IsLocked(flash) == 1U)
  {
    LL_FLASH_SetUnlockKey(flash, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(flash, LL_FLASH_KEY2);
  }
#endif /* __ARM_FEATURE_CMSE */

  if (LL_FLASH_OB_IsLocked(flash) == 1U)
  {
    LL_FLASH_OB_SetUnlockKey(flash, LL_FLASH_OB_OPTKEY1);
    LL_FLASH_OB_SetUnlockKey(flash, LL_FLASH_OB_OPTKEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check the Flash OB control register access lock status.
  * @param  flash                                     Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_lock_status_t            Flash OB control register access lock status.
  */
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return (hal_flash_itf_ob_lock_status_t)LL_FLASH_OB_IsLocked(flash);
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group2
  * @{
  * This subsection provides a set of functions for the Flash interface control features:

  * - Call HAL_FLASH_ITF_SetLatency() to set the Flash latency value.

  * - Call HAL_FLASH_ITF_GetLatency() to get the Flash latency value.

  * - Call HAL_FLASH_ITF_EnablePrefetch() to enable the Flash prefetch feature.

  * - Call HAL_FLASH_ITF_DisablePrefetch() to disable the Flash prefetch feature.

  * - Call HAL_FLASH_ITF_IsEnabledPrefetch() to check the status of the Flash prefetch feature.

  * - Call HAL_FLASH_ITF_EnablePWRDownRunMode() to enable Flash power down during run mode feature.

  * - Call HAL_FLASH_ITF_IsEnabledRunModePWRDown() to check the status of Flash power down during run mode feature.

  * - Call HAL_FLASH_ITF_EnablePWRDownSleepMode() to enable Flash power down during sleep mode feature.

  * - Call HAL_FLASH_ITF_DisablePWRDownSleepMode() to disable Flash power down during sleep mode feature.

  * - Call HAL_FLASH_ITF_IsEnabledSleepModePWRDown() to check the status of Flash power down during sleep mode feature.

  * - Call HAL_FLASH_ITF_EnableLowPWRReadMode() to enable Flash low power during read mode feature.

  * - Call HAL_FLASH_ITF_DisableLowPWRReadMode() to disable Flash low power during read mode feature.

  * - Call HAL_FLASH_ITF_IsEnabledLowPWRReadMode() to check the status of Flash low power during read mode feature.

  * - Call HAL_FLASH_ITF_ECC_EnableIT() to enable Flash ECC interruption.

  * - Call HAL_FLASH_ITF_ECC_DisableIT() to disable Flash ECC interruption.

  * - Call HAL_FLASH_ITF_ECC_IsEnabledIT() to check the Flash ECC interruption configuration status.

  * - Call HAL_FLASH_ITF_IsLockedRDPOEM1Key() to check the Readout protection OEM1 key lock status.

  * - Call HAL_FLASH_ITF_IsLockedRDPOEM2Key() to check the Readout protection OEM2 key lock status.

  */

/**
  * @brief  Set the Flash latency configuration.
  * @param  flash              Pointer to FLASH_TypeDef structure.
  * @param  latency            This parameter is an element of \ref hal_flash_itf_latency_t enumeration.
  * @retval HAL_OK             Flash latency is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetLatency(FLASH_TypeDef *flash, hal_flash_itf_latency_t latency)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_LATENCY(latency));

  LL_FLASH_SetLatency(flash, (uint32_t)latency);

  return HAL_OK;
}

/**
  * @brief  Get the Flash latency configuration.
  * @param  flash                              Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_latency_t            Flash latency value.
  */
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_latency_t)LL_FLASH_GetLatency(flash));
}

/**
  * @brief  Enable the Flash prefetch feature.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash prefetch feature is successfully enabled.
  */
hal_status_t HAL_FLASH_ITF_EnablePrefetch(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_EnablePrefetch(flash);

  return HAL_OK;
}

/**
  * @brief  Disable the Flash prefetch feature.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash prefetch feature is successfully disabled.
  */
hal_status_t HAL_FLASH_ITF_DisablePrefetch(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_DisablePrefetch(flash);

  return HAL_OK;
}

/**
  * @brief  Return the Flash prefetch status
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_prefetch_status_t            Flash prefetch status.
  */
hal_flash_itf_prefetch_status_t HAL_FLASH_ITF_IsEnabledPrefetch(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_prefetch_status_t)LL_FLASH_IsEnabledPrefetch(flash));
}

/**
  * @brief  Enable the Flash power down during run mode configuration.
  * @note   Any access to the Flash memory can disable the power down during run mode.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @retval HAL_OK          Flash power down during run mode configuration is successfully enabled.
  */
hal_status_t HAL_FLASH_ITF_EnablePWRDownRunMode(FLASH_TypeDef *flash, hal_flash_itf_bank_t bank)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  LL_FLASH_BANK_SetPWRDownRunModeKey(flash, (uint32_t)bank, FLASH_ITF_GET_PWR_DOWN_BANK_KEY1(bank));
  LL_FLASH_BANK_SetPWRDownRunModeKey(flash, (uint32_t)bank, FLASH_ITF_GET_PWR_DOWN_BANK_KEY2(bank));

  LL_FLASH_BANK_RequestPWRDownRunMode(flash, FLASH_ITF_GET_PWR_DOWN_BANK_REQUEST(bank));

  return HAL_OK;
}

/**
  * @brief  Check the Flash power down during run mode configuration status.
  * @note   Any access to the Flash memory can disable the power down during run mode.
  * @param  flash                                     Pointer to FLASH_TypeDef structure.
  * @param  bank                                      Element of \ref hal_flash_itf_bank_t enumeration.
  * @retval hal_flash_itf_pwr_down_run_status_t       Flash power down during run mode configuration status.
  */
hal_flash_itf_pwr_down_run_status_t HAL_FLASH_ITF_IsEnabledRunModePWRDown(const FLASH_TypeDef *flash,
                                                                          const hal_flash_itf_bank_t bank)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  return ((hal_flash_itf_pwr_down_run_status_t)LL_FLASH_IsActiveFlag_PD(flash, FLASH_ITF_GET_PWR_DOWN_BANK(bank)));
}

/**
  * @brief  Enable the Flash power down during sleep mode configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash power down during sleep mode configuration is successfully enabled.
  */
hal_status_t HAL_FLASH_ITF_EnablePWRDownSleepMode(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_SetPWRDownSleepMode(flash, LL_FLASH_PWR_DOWN_SLEEP_MODE);

  return HAL_OK;
}

/**
  * @brief  Disable the Flash power down during sleep mode configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash power down during sleep mode configuration is successfully disabled.
  */
hal_status_t HAL_FLASH_ITF_DisablePWRDownSleepMode(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_SetPWRDownSleepMode(flash, LL_FLASH_IDLE_SLEEP_MODE);

  return HAL_OK;
}

/**
  * @brief  Check the Flash power down during sleep mode configuration status.
  * @param  flash                                            Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_pwr_down_sleep_status_t            Flash power down during sleep mode configuration status.
  */
hal_flash_itf_pwr_down_sleep_status_t HAL_FLASH_ITF_IsEnabledSleepModePWRDown(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_pwr_down_sleep_status_t)
          ((uint32_t)(LL_FLASH_GetPWRDownSleepMode(flash) >> FLASH_ACR_SLEEP_PD_Pos)));
}

/**
  * @brief  Enable the Flash low power read mode configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Low power read mode configuration is successfully enabled.
  */
hal_status_t HAL_FLASH_ITF_EnableLowPWRReadMode(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_EnableLowPWRReadMode(flash);

  return HAL_OK;
}

/**
  * @brief  Disable the Flash low power read mode configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Low power read mode is successfully disabled.
  */
hal_status_t HAL_FLASH_ITF_DisableLowPWRReadMode(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_DisableLowPWRReadMode(flash);

  return HAL_OK;
}

/**
  * @brief  Check the Flash low power read mode configuration status.
  * @param  flash                                          Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_low_pwr_read_status_t            Flash low power read mode configuration status.
  */
hal_flash_itf_low_pwr_read_status_t HAL_FLASH_ITF_IsEnabledLowPWRReadMode(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_low_pwr_read_status_t)LL_FLASH_IsEnabledLowPWRReadMode(flash));
}

#if defined (USE_HAL_FLASH_ITF_ECC) && (USE_HAL_FLASH_ITF_ECC == 1U)
/**
  * @brief  Enable the Flash Error code correction interruption.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash Error code correction interruption is successfully enabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_EnableIT_ECC(flash);

  return HAL_OK;
}

/**
  * @brief  Disable the Flash Error code correction interruption.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash Error code correction interruption is successfully disabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_DisableIT_ECC(flash);

  return HAL_OK;
}

/**
  * @brief  Check the Flash ECC interrupt status.
  * @param  flash                          Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ecc_it_status_t  Flash ECC interrupt status.
  */
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledIT(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ecc_it_status_t)LL_FLASH_IsEnabledIT_ECC(flash));
}
#endif /* USE_HAL_FLASH_ITF_ECC */

/**
  * @brief  Check the Flash Readout Protection OEM1 key lock status.
  * @param  flash                                Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_rdp_key_lock_status_t  Flash Readout Protection OEM1 key lock status.
  */
hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPOEM1Key(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_rdp_key_lock_status_t)LL_FLASH_IsActiveFlag_OEM1LOCK(flash));
}

/**
  * @brief  Check the Flash Readout Protection OEM2 key lock status.
  * @param  flash                                Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_rdp_key_lock_status_t  Flash Readout Protection OEM2 key lock status.
  */
hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPOEM2Key(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_rdp_key_lock_status_t)LL_FLASH_IsActiveFlag_OEM1LOCK(flash));
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group3
  * @{
  * This subsection provides a set of functions to configure the Flash option bytes interface:

  * - Call HAL_FLASH_ITF_OB_SetWRPArea() to set the Flash OB WRP area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_GetWRPArea() to get the Flash OB WRP area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_LockWRPAreaConfig() to lock the Flash OB WRP area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_UnlockWRPAreaConfig() to unlock the Flash OB WRP area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_IsLockedWRPAreaConfig() to check the lock status of the Flash OB WRP area boundaries
      configuration.

  * - Call HAL_FLASH_ITF_OB_SetRDPLevel() to set the Flash OB readout protection level.

  * - Call HAL_FLASH_ITF_OB_GetRDPLevel() to get the Flash OB readout protection level.

  * - Call HAL_FLASH_ITF_OB_SetRDPOEMKey() to set the Flash OB readout protection OEM keys.

  * - Call HAL_FLASH_ITF_OB_SetBORLevel() to set the Flash OB BOR level.

  * - Call HAL_FLASH_ITF_OB_GetBORLevel() to get the Flash OB BOR level.

  * - Call HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() to set the Flash OB low power mode reset generation.

  * - Call HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() to get the Flash OB low power mode reset generation.

  * - Call HAL_FLASH_ITF_OB_SetSystemRstSRAMErase() to set the Flash OB SRAM erase upon system reset.

  * - Call HAL_FLASH_ITF_OB_GetSystemRstSRAMErase() to get the Flash OB SRAM erase upon system reset.

  * - Call HAL_FLASH_ITF_OB_SetIWDGMode() to set the Flash OB IWDG mode selection.

  * - Call HAL_FLASH_ITF_OB_GetIWDGMode() to get the Flash OB IWDG mode selection.

  * - Call HAL_FLASH_ITF_OB_SetWWDGMode() to set the Flash OB WWDG mode selection.

  * - Call HAL_FLASH_ITF_OB_GetWWDGMode() to get the Flash OB WWDG mode selection.

  * - Call HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode() to freeze the Flash OB IWDG counter in low power mode
      configuration.

  * - Call HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode() to unfreeze the Flash OB IWDG counter in low power mode
      configuration.

  * - Call HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode() to check the status of the Flash OB IWDG counter in low
      power mode configuration.

  * - Call HAL_FLASH_ITF_OB_SetBankSwap() to set the Flash OB bank swapping configuration.

  * - Call HAL_FLASH_ITF_OB_GetBankSwap() to get the Flash OB bank swapping configuration.

  * - Call HAL_FLASH_ITF_OB_SetBankTopology() to set the Flash OB bank topology configuration.

  * - Call HAL_FLASH_ITF_OB_GetBankTopology() to get the Flash OB bank topology configuration.

  * - Call HAL_FLASH_ITF_OB_EnableSRAMECC() to enable the Flash OB SRAM ECC configuration.

  * - Call HAL_FLASH_ITF_OB_DisableSRAMECC() to disable the Flash OB SRAM ECC configuration.

  * - Call HAL_FLASH_ITF_OB_IsEnabledSRAMECC() to check the status of the Flash OB SRAM ECC configuration.

  * - Call HAL_FLASH_ITF_OB_SetBoot0() to set the Flash OB boot0 configuration.

  * - Call HAL_FLASH_ITF_OB_GetBoot0() to get the Flash OB boot0 configuration.

  * - Call HAL_FLASH_ITF_OB_SetIOPull() to set the Flash OB PA15 pull-up configuration.

  * - Call HAL_FLASH_ITF_OB_GetIOPull() to get the Flash OB PA15 pull-up configuration.

  * - Call HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage() to enable the Flash OB HSLV VDDIO configuration.

  * - Call HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage() to disable the Flash OB HSLV VDDIO configuration.

  * - Call HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage() to check the status of the Flash OB HSLV VDDIO
      configuration.
.
  * - Call HAL_FLASH_ITF_OB_EnableTrustZone() to enable the Flash OB TrustZone configuration.

  * - Call HAL_FLASH_ITF_OB_DisableTrustZone() to disable the Flash OB TrustZone configuration.

  * - Call HAL_FLASH_ITF_OB_IsEnabledTrustZone() to check the status of the Flash OB TrustZone configuration.

  * - Call HAL_FLASH_ITF_OB_SetSecureWMArea() to set the Flash OB secure watermark area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_GetSecureWMArea() to get the Flash OB secure watermark area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_SetConfigHDPArea() to set the Flash OB hide protection area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_GetConfigHDPArea() to get the Flash OB hide protection area boundaries configuration.

  * - Call HAL_FLASH_ITF_OB_EnableHDPArea() to enable the Flash OB hide protection area configuration.

  * - Call HAL_FLASH_ITF_OB_DisableHDPArea() to disable the Flash OB hide protection area configuration.

  * - Call HAL_FLASH_ITF_OB_IsEnabledHDPArea() to check the status of the Flash OB hide protection area configuration.

  * - Call HAL_FLASH_ITF_OB_SetNSecureBootAddr() to set the NSecure Flash OB boot address configuration.

  * - Call HAL_FLASH_ITF_OB_GetNSecureBootAddr() to get the NSecure Flash OB boot address configuration.

  * - Call HAL_FLASH_ITF_OB_SetSecureBootAddr() to set the Flash OB secure boot address configuration.

  * - Call HAL_FLASH_ITF_OB_GetSecureBootAddr() to get the Flash OB secure boot address configuration.

  * - Call HAL_FLASH_ITF_OB_LockBootConfig() to lock the Flash OB secure boot address configuration.

  * - Call HAL_FLASH_ITF_OB_UnlockBootConfig() to unlock the Flash OB secure boot address configuration.

  * - Call HAL_FLASH_ITF_OB_IsLockedBootConfig() to check the status of the Flash OB secure boot address configuration.

  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the Flash OB secure watermark area boundaries configuration.
  * @note   To disable the secure watermark the page_nbr must be equal to zero independently of start_page.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  start_page      Start page of the secure watermark area start boundary.
  * @param  page_nbr        Number of page(s) of the secure watermark area to be configured.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  * @retval HAL_OK          Flash OB secure watermark area boundaries are successfully configured.
  */
hal_status_t HAL_FLASH_ITF_OB_SetSecureWMArea(FLASH_TypeDef *flash,
                                              hal_flash_itf_bank_t bank,
                                              uint32_t start_page,
                                              uint32_t page_nbr)
{
  uint32_t end_page_secwm;

  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(start_page < FLASH_ITF_BANK_MAX_PAGE_NBR);
  ASSERT_DBG_PARAM((start_page + page_nbr) <= FLASH_ITF_BANK_MAX_PAGE_NBR);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if (page_nbr == 0U)
  {
    LL_FLASH_OB_BANK_ConfigSecureWMArea(flash, (uint32_t)bank, 1U, 0U);
  }
  else
  {
    end_page_secwm = start_page + page_nbr - 1U;
    LL_FLASH_OB_BANK_ConfigSecureWMArea(flash, (uint32_t)bank, start_page, end_page_secwm);
  }

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB secure watermark area boundaries configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  p_start_page    Pointer to the start page of of the configured secure watermark area.
  * @param  p_page_nbr      Pointer to the number of page(s) of the configured secure watermark area.
  */
void HAL_FLASH_ITF_OB_GetSecureWMArea(const FLASH_TypeDef *flash,
                                      const hal_flash_itf_bank_t bank,
                                      uint32_t *p_start_page,
                                      uint32_t *p_page_nbr)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(p_start_page != NULL);
  ASSERT_DBG_PARAM(p_page_nbr != NULL);

  *p_start_page = LL_FLASH_OB_BANK_GetWMAreaStartPage(flash, (uint32_t)bank);
  *p_page_nbr   = (((LL_FLASH_OB_BANK_GetWMAreaEndPage(flash, (uint32_t)bank) \
                     >> FLASH_SECWM1R1_SECWM1_PEND_Pos) - *p_start_page) + 1U);
}

/**
  * @brief  Set the Flash OB hide protection area boundaries configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  page_nbr        Number of page(s) for the hide protection area to be configured.
  * @retval HAL_OK          Flash OB hide protection area boundaries are successfully configured.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
                            Flash OB hide protection area boundaries configuration error occurred.
  */
hal_status_t HAL_FLASH_ITF_OB_SetConfigHDPArea(FLASH_TypeDef *flash,
                                               hal_flash_itf_bank_t bank,
                                               uint32_t page_nbr)
{
  uint32_t start_page_secwm;
  uint32_t end_page_secwm;
  uint32_t end_page_hdp;

  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM((page_nbr > 0U) && (page_nbr < FLASH_ITF_BANK_MAX_PAGE_NBR));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  start_page_secwm = LL_FLASH_OB_BANK_GetWMAreaStartPage(flash, (uint32_t)bank);
  end_page_secwm = LL_FLASH_OB_BANK_GetWMAreaEndPage(flash, (uint32_t)bank);
  end_page_hdp = start_page_secwm + page_nbr - 1U;

  if (end_page_hdp > end_page_secwm)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_SetHDPAreaEndPage(flash, (uint32_t)bank, end_page_hdp);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB hide protection area boundaries configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  p_page_nbr      Pointer to the number of page(s) of the configured hide protection area.
  */
void HAL_FLASH_ITF_OB_GetConfigHDPArea(const FLASH_TypeDef *flash,
                                       const hal_flash_itf_bank_t bank,
                                       uint32_t *p_page_nbr)
{
  uint32_t start_page;

  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(p_page_nbr != NULL);

  start_page = LL_FLASH_OB_BANK_GetWMAreaStartPage(flash, (uint32_t)bank);
  *p_page_nbr = (((LL_FLASH_OB_BANK_GetHDPAreaEndPage(flash, ((uint32_t)bank)) \
                   >> FLASH_SECWM1R2_HDP1_PEND_Pos) - start_page) + 1U);
}

/**
  * @brief  Enable the Flash OB hide protection area configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @retval HAL_OK          Flash OB hide protection area is successfully enabled.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableHDPArea(FLASH_TypeDef *flash, hal_flash_itf_bank_t bank)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_EnableHDPArea(flash, (uint32_t)bank);

  return HAL_OK;
}

/**
  * @brief  Disable the Flash OB hide protection area configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @retval HAL_OK          Flash OB hide protection area is successfully disabled.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableHDPArea(FLASH_TypeDef *flash, hal_flash_itf_bank_t bank)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_DisableHDPArea(flash, (uint32_t)bank);

  return HAL_OK;
}

/**
  * @brief  Check if the Flash OB hide protection area configuration status.
  * @param  flash                               Pointer to FLASH_TypeDef structure.
  * @param  bank                                This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @retval hal_flash_itf_ob_hdp_area_status_t  Flash OB hide protection area configuration status.
  */
hal_flash_itf_ob_hdp_area_status_t HAL_FLASH_ITF_OB_IsEnabledHDPArea(const FLASH_TypeDef *flash,
                                                                     const hal_flash_itf_bank_t bank)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));

  return ((hal_flash_itf_ob_hdp_area_status_t)LL_FLASH_OB_BANK_IsEnabledHDPArea(flash, (uint32_t)bank));
}

/**
  * @brief  Set the Flash OB secure boot address 0 configuration.
  * @param  flash                Pointer to FLASH_TypeDef structure.
  * @param  boot_addr            Flash OB secure boot address 0 to be configured.
  * @retval HAL_OK               Flash OB secure boot address 0 is successfully configured.
  * @retval HAL_ERROR            Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetSecureBootAddr(FLASH_TypeDef *flash, uint32_t boot_addr)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(boot_addr != 0U);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetSecBootAddr0(flash, boot_addr);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB secure boot address 0 configuration.
  * @param  flash               Pointer to FLASH_TypeDef structure.
  * @retval uint32_t            Flash OB secure boot address 0 configuration.
  */
uint32_t HAL_FLASH_ITF_OB_GetSecureBootAddr(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return LL_FLASH_OB_GetSecBootAddr0(flash);
}

/**
  * @brief  Lock the Flash OB secure boot address configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash OB boot address configuration is successfully locked.
  * @retval HAL_ERROR         Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_LockBootConfiguration(flash);

  return HAL_OK;
}

/**
  * @brief  Unlock the Flash OB secure boot address configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash OB boot address configuration is successfully unlocked.
  * @retval HAL_ERROR         Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_UnlockBootConfiguration(flash);

  return HAL_OK;
}

/**
  * @brief  Check the Flash OB secure boot configuration status.
  * @param  flash                                          Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_boot_lock_status_t            Flash OB secure boot configuration is locked or unlocked.
  */
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ob_boot_lock_status_t)LL_FLASH_OB_IsLockedBootConfiguration(flash));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Set the Flash OB write protection area boundaries configuration.
  * @note   To disable the write protection area the page_nbr must be equal to zero independently of start_page.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  area            This parameter is an element of \ref hal_flash_itf_ob_bank_area_t enumeration.
  * @param  start_page      Start page for the write protection area start boundary.
  * @param  page_nbr        End page for the write protection area end boundary.
  * @retval HAL_OK          Flash OB write protection area boundaries are successfully configured.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetWRPArea(FLASH_TypeDef *flash,
                                         hal_flash_itf_bank_t bank,
                                         hal_flash_itf_ob_bank_area_t area,
                                         uint32_t start_page,
                                         uint32_t page_nbr)
{
  uint32_t end_page_wrp;

  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BANK_AREA(area));
  ASSERT_DBG_PARAM(start_page < FLASH_ITF_BANK_MAX_PAGE_NBR);
  ASSERT_DBG_PARAM((start_page + page_nbr) <= FLASH_ITF_BANK_MAX_PAGE_NBR);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if (page_nbr == 0U)
  {
    LL_FLASH_OB_BANK_ConfigAreaWRP(flash, (uint32_t)bank, (uint32_t)area, 1U, 0U);
  }
  else
  {
    end_page_wrp = start_page + page_nbr - 1U;
    LL_FLASH_OB_BANK_ConfigAreaWRP(flash, (uint32_t)bank, (uint32_t)area, start_page, end_page_wrp);
  }

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB write protection area boundaries configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  area            This parameter is an element of \ref hal_flash_itf_ob_bank_area_t enumeration.
  * @param  p_start_page    Pointer to the write protection area start boundary.
  * @param  p_page_nbr      Pointer to the number of page(s) of the write protection area to be configured.
  */
void HAL_FLASH_ITF_OB_GetWRPArea(const FLASH_TypeDef *flash,
                                 const hal_flash_itf_bank_t bank,
                                 const hal_flash_itf_ob_bank_area_t area,
                                 uint32_t *p_start_page,
                                 uint32_t *p_page_nbr)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BANK_AREA(area));
  ASSERT_DBG_PARAM(p_start_page != NULL);
  ASSERT_DBG_PARAM(p_page_nbr != NULL);

  *p_start_page = LL_FLASH_OB_BANK_GetAreaWRPStartPage(flash, (uint32_t)bank, (uint32_t)area);
  *p_page_nbr   = (((LL_FLASH_OB_BANK_GetAreaWRPEndPage(flash, (uint32_t)bank,
                                                        (uint32_t)area) >> FLASH_WRP1AR_WRP1A_PEND_Pos) - \
                    *p_start_page) + 1U);
}

/**
  * @brief  Lock the Flash OB write protection area configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  area            This parameter is an element of \ref hal_flash_itf_ob_bank_area_t enumeration.
  * @retval HAL_OK          Flash OB write protection area configuration is successfully locked.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_LockWRPAreaConfig(FLASH_TypeDef *flash,
                                                hal_flash_itf_bank_t bank,
                                                hal_flash_itf_ob_bank_area_t area)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BANK_AREA(area));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_LockAreaWRP(flash, (uint32_t)bank, (uint32_t)area);

  return HAL_OK;
}

/**
  * @brief  Unlock the Flash OB write protection area configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  bank            This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  area            This parameter is an element of \ref hal_flash_itf_ob_bank_area_t enumeration.
  * @retval HAL_OK          Flash OB write protection area configuration is successfully unlocked.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_UnlockWRPAreaConfig(FLASH_TypeDef *flash,
                                                  hal_flash_itf_bank_t bank,
                                                  hal_flash_itf_ob_bank_area_t area)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BANK_AREA(area));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_BANK_UnlockAreaWRP(flash, (uint32_t)bank, (uint32_t)area);

  return HAL_OK;
}

/**
  * @brief  Check if the Flash OB write protection area configuration lock status.
  * @param  flash                               Pointer to FLASH_TypeDef structure.
  * @param  bank                                This parameter is an element of \ref hal_flash_itf_bank_t enumeration.
  * @param  area                                This parameter is an element of \ref hal_flash_itf_ob_bank_area_t
                                                enumeration.
  * @retval hal_flash_itf_ob_wrp_lock_status_t  Flash OB write protection area configuration is locked or unlocked.
  */
hal_flash_itf_ob_wrp_lock_status_t HAL_FLASH_ITF_OB_IsLockedWRPAreaConfig(const FLASH_TypeDef *flash,
                                                                          const hal_flash_itf_bank_t bank,
                                                                          const hal_flash_itf_ob_bank_area_t area)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BANK_AREA(area));

  return ((hal_flash_itf_ob_wrp_lock_status_t)LL_FLASH_OB_BANK_IsLockedAreaWRP(flash, (uint32_t)bank, (uint32_t)area));
}

/**
  * @brief  Set the Flash OB readout protection level.
  * @param  flash                Pointer to FLASH_TypeDef structure.
  * @param  rdp_level            This parameter is an element of \ref hal_flash_itf_ob_rdp_level_t enumeration.
  * @retval HAL_OK               Flash OB readout protection level is successfully configured.
  * @retval HAL_ERROR            Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetRDPLevel(FLASH_TypeDef *flash, hal_flash_itf_ob_rdp_level_t rdp_level)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_RDP_LEVEL(rdp_level));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetRDPLevel(flash, (uint32_t)rdp_level);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB readout protection level.
  * @param  flash                         Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_rdp_level_t  Flash OB readout protection level.
  */
hal_flash_itf_ob_rdp_level_t HAL_FLASH_ITF_OB_GetRDPLevel(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ob_rdp_level_t)LL_FLASH_OB_GetRDPLevel(flash));
}

/**
  * @brief  Set the Flash OB readout protection OEM1 key.
  * @param  flash                  Pointer to FLASH_TypeDef structure.
  * @param  p_key                  Pointer to Flash OB Readout Protection OEM key structure
  * @retval HAL_OK                 Flash OB readout protection OEM1 key is successfully configured.
  * @retval HAL_ERROR              Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetRDPOEM1Key(FLASH_TypeDef *flash, hal_flash_itf_ob_rdp_oem_key_t *p_key)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(p_key != NULL);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_SetOEM1KeyLowBytes(flash, p_key ->key_w1);
  LL_FLASH_SetOEM1KeyHighBytes(flash, p_key ->key_w2);

  return HAL_OK;
}

/**
  * @brief  Set the Flash OB readout protection OEM2 key.
  * @param  flash                  Pointer to FLASH_TypeDef structure.
  * @param  p_key                  Pointer to Flash OB Readout Protection OEM key structure
  * @retval HAL_OK                 Flash OB readout protection OEM2 key is successfully configured.
  * @retval HAL_ERROR              Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetRDPOEM2Key(FLASH_TypeDef *flash, hal_flash_itf_ob_rdp_oem_key_t *p_key)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(p_key != NULL);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_SetOEM2KeyLowBytes(flash, p_key ->key_w1);
  LL_FLASH_SetOEM2KeyHighBytes(flash, p_key ->key_w2);

  return HAL_OK;
}

/**
  * @brief  Set the Flash OB BOR level value.
  * @param  flash                Pointer to FLASH_TypeDef structure.
  * @param  bor_level            This parameter is an element of \ref hal_flash_itf_ob_bor_level_t enumeration.
  * @retval HAL_OK               Flash OB BOR level value is successfully configured.
  * @retval HAL_ERROR            Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBORLevel(FLASH_TypeDef *flash, hal_flash_itf_ob_bor_level_t bor_level)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOR_LEVEL(bor_level));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBORLevel(flash, (uint32_t)bor_level);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB BOR level value.
  * @param  flash                         Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_bor_level_t  Flash OB BOR level value.
  */
hal_flash_itf_ob_bor_level_t HAL_FLASH_ITF_OB_GetBORLevel(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ob_bor_level_t)((uint32_t)LL_FLASH_OB_GetBORLevel(flash)));
}

/**
  * @brief  Set the Flash OB low power mode reset generation configuration.
  * @param  flash                   Pointer to FLASH_TypeDef structure.
  * @param  low_pwr_mode            Flash OB Low power mode selection.
  * @param  rst_gen                 Element from the \ref hal_flash_itf_ob_rst_generation_status_t enumeration.
  * @retval HAL_OK                  Flash OB low power mode reset generation is successfully configured.
  * @retval HAL_ERROR               Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(FLASH_TypeDef *flash,
                                                              uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);
  ASSERT_DBG_PARAM(IS_FLASH_OB_RST_GENERATION(rst_gen));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_SetNRSTStopMode(flash, (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STOP_MODE);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_SetNRSTStandbyMode(flash, (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STDBY_MODE);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_SHUTDOWN_MODE) == HAL_FLASH_ITF_OB_SHUTDOWN_MODE)
  {
    LL_FLASH_OB_SetNRSTShutdownMode(flash, (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_SHDW_MODE);
  }

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB low power reset generation configuration.
  * @param  flash                                     Pointer to FLASH_TypeDef structure.
  * @param  low_pwr_mode                              Flash OB low power mode selection.
  * @retval hal_flash_itf_ob_rst_generation_status_t  Flash OB low power mode reset generation configuration.
  */
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(const FLASH_TypeDef *flash,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStopMode(flash) >> FLASH_OPTR_nRST_STOP_Pos));
  }
  else if (low_pwr_mode == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStandbyMode(flash) >> FLASH_OPTR_nRST_STDBY_Pos));
  }
  else
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTShutdownMode(flash) >> FLASH_OPTR_nRST_SHDW_Pos));
  }
}

/**
  * @brief  Set the Flash OB system reset SRAM erase configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  sram            Flash OB SRAM selection.
  * @param  sram_erase      Element from the \ref hal_flash_itf_ob_sys_rst_sram_erase_t enumeration.
  * @retval HAL_OK          Flash OB SRAM erase memories is successfully configured.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetSystemRstSRAMErase(FLASH_TypeDef *flash,
                                                    uint32_t sram,
                                                    hal_flash_itf_ob_sys_rst_sram_erase_t sram_erase)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ERASE_MSK) == sram);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SYS_RST_SRAM_ERASE(sram_erase));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM2) == HAL_FLASH_ITF_OB_SRAM2)
  {
    LL_FLASH_OB_SetSystemRstSRAM2Erase(flash, (uint32_t)sram_erase * LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST);
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM) == HAL_FLASH_ITF_OB_SRAM)
  {
    LL_FLASH_OB_SetSystemRstSRAMErase(flash, (uint32_t)sram_erase * LL_FLASH_OB_NOT_ERASED_SRAM_SYS_RST);
  }

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB system reset SRAM erase configuration.
  * @param  flash                                     Pointer to FLASH_TypeDef structure.
  * @param  sram                                      Flash OB SRAM selection.
  * @retval hal_flash_itf_ob_sys_rst_sram_erase_t     Flash OB system reset SRAM erase configuration.
  */
hal_flash_itf_ob_sys_rst_sram_erase_t HAL_FLASH_ITF_OB_GetSystemRstSRAMErase(const FLASH_TypeDef *flash, uint32_t sram)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ERASE(sram));

  if (sram == HAL_FLASH_ITF_OB_SRAM2)
  {
    return (hal_flash_itf_ob_sys_rst_sram_erase_t)
           ((uint32_t)(LL_FLASH_OB_GetSystemRstSRAM2Erase(flash) >> FLASH_OPTR_SRAM2_RST_Pos));
  }
  else
  {
    return (hal_flash_itf_ob_sys_rst_sram_erase_t)
           ((uint32_t)(LL_FLASH_OB_GetSystemRstSRAMErase(flash) >> FLASH_OPTR_SRAM_RST_Pos));
  }
}

/**
  * @brief  Set the Flash OB IWDG mode selection.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  mode            Element from the \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  * @retval HAL_OK          Flash OB IWDG mode selection is successfully configured.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(FLASH_TypeDef *flash, hal_flash_itf_ob_wdg_mode_t mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_WDG_HW_SW_MODE(mode));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetIWDGSelection(flash, (uint32_t)mode * LL_FLASH_OB_IWDG_SW);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB IWDG mode selection.
  * @param  flash                                  Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_wdg_mode_t            Flash OB IWDG mode selection.
  */
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return (hal_flash_itf_ob_wdg_mode_t)((uint32_t)(LL_FLASH_OB_GetIWDGSelection(flash) >> FLASH_OPTR_IWDG_SW_Pos));
}

/**
  * @brief  Set the Flash OB WWDG mode selection.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  mode            Element from the \ref hal_flash_itf_ob_wdg_mode_t enumeration.
  * @retval HAL_OK          Flash OB WWDG mode selection is successfully configured.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetWWDGMode(FLASH_TypeDef *flash, hal_flash_itf_ob_wdg_mode_t mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_WDG_HW_SW_MODE(mode));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetWWDGSelection(flash, (uint32_t)mode * LL_FLASH_OB_WWDG_SW);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB WWDG mode selection.
  * @param  flash                                  Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_wdg_mode_t            Flash OB WWDG mode selection.
  */
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetWWDGMode(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return (hal_flash_itf_ob_wdg_mode_t)((uint32_t)(LL_FLASH_OB_GetWWDGSelection(flash) >> FLASH_OPTR_WWDG_SW_Pos));
}

/**
  * @brief  Freeze the Flash OB IWDG low power mode counter configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  low_pwr_mode    Flash OB low power mode selection.
  * @retval HAL_OK          Flash OB IWDG low power counter is frozen.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flash, uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);
  ASSERT_DBG_PARAM((low_pwr_mode & HAL_FLASH_ITF_OB_SHUTDOWN_MODE) == 0U);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStopMode(flash);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStandbyMode(flash);
  }

  return HAL_OK;
}

/**
  * @brief  Unfreeze the Flash OB IWDG low power counter configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  low_pwr_mode    low power mode selection.
  * @retval HAL_OK          Flash OB IWDG low power mode counter is unfrozen.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flash, uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);
  ASSERT_DBG_PARAM((low_pwr_mode & HAL_FLASH_ITF_OB_SHUTDOWN_MODE) == 0U);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStopMode(flash);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStandbyMode(flash);
  }

  return HAL_OK;
}

/**
  * @brief  Check the Flash OB IWDG low power mode counter freeze configuration status.
  * @param  flash                                 Pointer to FLASH_TypeDef structure.
  * @param  low_pwr_mode                          Flash OB low power mode selection.
  * @retval hal_flash_itf_ob_wdg_freeze_status_t  Flash OB IWDG low power mode counter freeze configuration status.
  */
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(const FLASH_TypeDef *flash,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));
  ASSERT_DBG_PARAM((low_pwr_mode & HAL_FLASH_ITF_OB_SHUTDOWN_MODE) == 0U);

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStopMode(flash);
  }
  else
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStandbyMode(flash);
  }
}

/**
  * @brief  Set the Flash OB bank swapping configuration.
  * @param  flash                Pointer to FLASH_TypeDef structure.
  * @param  bank_swap            This parameter is an element of \ref hal_flash_itf_ob_bank_swap_t enumeration.
  * @retval HAL_OK               Flash OB bank swapping is successfully configured.
  * @retval HAL_ERROR            Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(FLASH_TypeDef *flash, hal_flash_itf_ob_bank_swap_t bank_swap)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SWAP_BANK(bank_swap));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetSwapBanks(flash, (uint32_t)bank_swap);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB bank swapping configuration.
  * @param  flash                                   Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_bank_swap_t            Flash OB bank swapping configuration.
  */
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ob_bank_swap_t)LL_FLASH_OB_GetSwapBanks(flash));
}

/**
  * @brief  Set the Flash OB bank topology configuration.
  * @param  flash                    Pointer to FLASH_TypeDef structure.
  * @param  bank_topology            This parameter is an element of \ref hal_flash_itf_ob_topology_t enumeration.
  * @retval HAL_OK                   Flash OB single/dual bank topology is successfully configured.
  * @retval HAL_ERROR                Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBankTopology(FLASH_TypeDef *flash, hal_flash_itf_ob_topology_t bank_topology)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SINGLE_DUAL_BANK(bank_topology));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBank(flash, (uint32_t)bank_topology);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB bank topology configuration.
  * @param  flash                                  Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_topology_t            Flash OB single/dual bank topology configuration.
  */
hal_flash_itf_ob_topology_t HAL_FLASH_ITF_OB_GetBankTopology(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ob_topology_t)LL_FLASH_OB_GetBank(flash));
}

/**
  * @brief  Enable the Flash OB BKPRAM ECC configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  sram            Flash OB SRAM selection.
  * @retval HAL_OK          Flash OB SRAM ECC is successfully enabled.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(FLASH_TypeDef *flash, uint32_t sram)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ECC_MSK) == sram);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_BKPRAM) == HAL_FLASH_ITF_OB_BKPRAM)
  {
    LL_FLASH_OB_EnableECCBKPRAM(flash);
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM2) == HAL_FLASH_ITF_OB_SRAM2)
  {
    LL_FLASH_OB_EnableECCSRAM2(flash);
  }
#if defined (SRAM3_BASE)
  if ((sram & HAL_FLASH_ITF_OB_SRAM3) == HAL_FLASH_ITF_OB_SRAM3)
  {
    LL_FLASH_OB_EnableECCSRAM3(flash);
  }
#endif /* SRAM3_BASE */
  return HAL_OK;
}

/**
  * @brief  Disable the Flash OB SRAM ECC configuration.
  * @param  flash           Pointer to FLASH_TypeDef structure.
  * @param  sram            Flash OB SRAM selection.
  * @retval HAL_OK          Flash OB SRAM ECC is successfully disabled.
  * @retval HAL_ERROR       Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(FLASH_TypeDef *flash, uint32_t sram)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ECC_MSK) == sram);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_BKPRAM) == HAL_FLASH_ITF_OB_BKPRAM)
  {
    LL_FLASH_OB_DisableECCBKPRAM(flash);
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM2) == HAL_FLASH_ITF_OB_SRAM2)
  {
    LL_FLASH_OB_DisableECCSRAM2(flash);
  }
#if defined (SRAM3_BASE)
  if ((sram & HAL_FLASH_ITF_OB_SRAM3) == HAL_FLASH_ITF_OB_SRAM3)
  {
    LL_FLASH_OB_DisableECCSRAM3(flash);
  }
#endif /* SRAM3_BASE */
  return HAL_OK;
}

/**
  * @brief  Check the Flash OB SRAM ECC configuration status.
  * @param  flash                               Pointer to FLASH_TypeDef structure.
  * @param  sram                                Flash OB SRAM selection.
  * @retval hal_flash_itf_ob_sram_ecc_status_t  Flash OB SRAM ECC configuration status.
  */
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(const FLASH_TypeDef *flash, uint32_t sram)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ECC(sram));

  if (sram == HAL_FLASH_ITF_OB_BKPRAM)
  {
    return (hal_flash_itf_ob_sram_ecc_status_t)LL_FLASH_OB_IsEnabledECCBKPRAM(flash);
  }
#if defined (SRAM3_BASE)
  else if (sram == HAL_FLASH_ITF_OB_SRAM3)
  {
    return (hal_flash_itf_ob_sram_ecc_status_t)LL_FLASH_OB_IsEnabledECCSRAM3(flash);
  }
#endif /* SRAM3_BASE */
  else
  {
    return (hal_flash_itf_ob_sram_ecc_status_t)LL_FLASH_OB_IsEnabledECCSRAM2(flash);
  }
}

/**
  * @brief  Set the Flash OB Software boot0 selection.
  * @param  flash                      Pointer to FLASH_TypeDef structure.
  * @param  boot_select                Element from \ref hal_flash_itf_ob_boot_selection_t enumeration.
  * @retval HAL_OK                     Flash OB Software boot0 selection is successfully configured.
  * @retval HAL_ERROR                  Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBootSelection(FLASH_TypeDef *flash, hal_flash_itf_ob_boot_selection_t boot_select)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOOT0_SELECTION(boot_select));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetSWBoot0(flash, (uint32_t)boot_select);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB Software boot0 state configuration.
  * @param  flash                                        Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_boot_selection_t            Flash OB Software boot0 selection configuration.
  */
hal_flash_itf_ob_boot_selection_t HAL_FLASH_ITF_OB_GetBootSelection(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return (hal_flash_itf_ob_boot_selection_t)LL_FLASH_OB_GetSWBoot0(flash);
}

/**
  * @brief  Set the Flash OB Software boot0 state configuration.
  * @param  flash                      Pointer to FLASH_TypeDef structure.
  * @param  state                      Element from \ref hal_flash_itf_ob_boot_state_t enumeration.
  * @retval HAL_OK                     Flash OB Software boot0 state configuration is successfully configured.
  * @retval HAL_ERROR                  Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBoot0(FLASH_TypeDef *flash, hal_flash_itf_ob_boot_state_t state)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOOT_STATE(state));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBoot0(flash, (uint32_t)state);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB Software boot0 state configuration.
  * @param  flash                                    Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_boot_state_t            Flash OB Software boot0 state configuration.
  */
hal_flash_itf_ob_boot_state_t HAL_FLASH_ITF_OB_GetBoot0(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return (hal_flash_itf_ob_boot_state_t)LL_FLASH_OB_GetBoot0(flash);
}

/**
  * @brief  Set the Flash OB PA15 pullup configuration.
  * @param  flash          Pointer to FLASH_TypeDef structure.
  * @param  pin            Flash OB pin selection.
  * @param  pull_mode      Element from \ref hal_flash_itf_ob_pull_mode_t enumeration.
  * @retval HAL_OK         Flash OB PA15 pullup is successfully configured.
  * @retval HAL_ERROR      Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetIOPull(FLASH_TypeDef *flash,
                                        uint32_t pin,
                                        hal_flash_itf_ob_pull_mode_t pull_mode)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(pin == HAL_FLASH_ITF_OB_PA15);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_PULL_MODE(pull_mode));

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if (pull_mode == HAL_FLASH_ITF_OB_PULL_UP)
  {
    LL_FLASH_OB_EnablePA15PullUp(flash);
  }
  else
  {
    LL_FLASH_OB_DisablePA15PullUp(flash);
  }

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(pin);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB PA15 pullup configuration status.
  * @param  flash                               Pointer to FLASH_TypeDef structure.
  * @param  pin                                 Flash OB Pin selection.
  * @retval hal_flash_itf_ob_pin_pull_status_t  Flash OB PA15 pullup configuration is disabled or enabled.
  */
hal_flash_itf_ob_pin_pull_status_t HAL_FLASH_ITF_OB_GetIOPull(const FLASH_TypeDef *flash, uint32_t pin)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(pin == HAL_FLASH_ITF_OB_PA15);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(pin);

  return (hal_flash_itf_ob_pin_pull_status_t)LL_FLASH_OB_IsEnabledPA15PullUp(flash);
}

/**
  * @brief  Enable the Flash OB High speed IO at low VDD voltage configuration.
  * @param  flash          Pointer to FLASH_TypeDef structure.
  * @param  vdd            Flash OB low VDD voltage selection.
  * @retval HAL_OK         Flash OB High speed IO at low VDD voltage configuration is successfully enabled.
  * @retval HAL_ERROR      Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage(FLASH_TypeDef *flash, uint32_t vdd)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((vdd & HAL_FLASH_ITF_OB_VDDIO_MSK) == vdd);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((vdd & HAL_FLASH_ITF_OB_VDDIO) == HAL_FLASH_ITF_OB_VDDIO)
  {
    LL_FLASH_OB_EnableVddIOHSLV(flash);
  }

  if ((vdd & HAL_FLASH_ITF_OB_VDDIO2) == HAL_FLASH_ITF_OB_VDDIO2)
  {
    LL_FLASH_OB_EnableVddIO2HSLV(flash);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Flash OB High speed IO at low VDD voltage configuration.
  * @param  flash          Pointer to FLASH_TypeDef structure.
  * @param  vdd            Flash OB low VDD voltage IO selection.
  * @retval HAL_OK         Flash OB High speed IO at low VDD voltage configuration is successfully disabled.
  * @retval HAL_ERROR      Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage(FLASH_TypeDef *flash, uint32_t vdd)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM((vdd & HAL_FLASH_ITF_OB_VDDIO_MSK) == vdd);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  if ((vdd & HAL_FLASH_ITF_OB_VDDIO) == HAL_FLASH_ITF_OB_VDDIO)
  {
    LL_FLASH_OB_DisableVddIOHSLV(flash);
  }

  if ((vdd & HAL_FLASH_ITF_OB_VDDIO2) == HAL_FLASH_ITF_OB_VDDIO2)
  {
    LL_FLASH_OB_DisableVddIO2HSLV(flash);
  }

  return HAL_OK;
}

/**
  * @brief  Check the Flash OB High speed IO at low VDD voltage configuration status.
  * @param  flash                                 Pointer to FLASH_TypeDef structure.
  * @param  vdd                                   Flash OB low VDD voltage IO selection.
  * @retval hal_flash_itf_ob_vddx_hslv_status_t   Flash OB High speed IO at low VDD voltage configuration status.
  */
hal_flash_itf_ob_vddx_hslv_status_t HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage(const FLASH_TypeDef *flash,
    uint32_t vdd)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_VDD(vdd));

  if (vdd == HAL_FLASH_ITF_OB_VDDIO)
  {
    return (hal_flash_itf_ob_vddx_hslv_status_t)LL_FLASH_OB_IsEnabledVddIOHSLV(flash);
  }
  else
  {
    return (hal_flash_itf_ob_vddx_hslv_status_t)LL_FLASH_OB_IsEnabledVddIO2HSLV(flash);
  }
}

/**
  * @brief  Enable the Flash OB TrustZone security configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash OB TrustZone security configuration is successfully enabled.
  * @retval HAL_ERROR         Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableTrustZone(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_EnableTrustZone(flash);

  return HAL_OK;
}

/**
  * @brief  Disable the Flash OB TrustZone configuration.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash OB TrustZone configuration is successfully disabled.
  * @retval HAL_ERROR         Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableTrustZone(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_DisableTrustZone(flash);

  return HAL_OK;
}

/**
  * @brief  Check the Flash OB TrustZone configuration status.
  * @param  flash                                Pointer to FLASH_TypeDef structure.
  * @retval hal_flash_itf_ob_trustzone_status_t  Flash OB TrustZone configuration status.
  */
hal_flash_itf_ob_trustzone_status_t HAL_FLASH_ITF_OB_IsEnabledTrustZone(const FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  return ((hal_flash_itf_ob_trustzone_status_t)LL_FLASH_OB_IsEnabledTrustZone(flash));
}

/**
  * @brief  Set the Flash OB NSecure boot address configuration.
  * @param  flash               Pointer to FLASH_TypeDef structure.
  * @param  addr_idx            Element from \ref hal_flash_itf_ob_addr_idx_t enumeration.
  * @param  boot_addr           Flash OB NSecure boot address to be configured.
  * @retval HAL_OK              Flash OB NSecure boot address is successfully configured.
  * @retval HAL_ERROR           Flash OB write operation is already in progress.
  */
hal_status_t HAL_FLASH_ITF_OB_SetNSecureBootAddr(FLASH_TypeDef *flash,
                                                 hal_flash_itf_ob_addr_idx_t addr_idx,
                                                 uint32_t boot_addr)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_ADDR_IDX(addr_idx));
  ASSERT_DBG_PARAM(boot_addr != 0U);

  if (LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetNSecBootAddr(flash, (uint32_t)addr_idx, boot_addr);

  return HAL_OK;
}

/**
  * @brief  Get the Flash OB NSecure boot address configuration.
  * @param  flash               Pointer to FLASH_TypeDef structure.
  * @param  addr_idx            Element from \ref hal_flash_itf_ob_addr_idx_t enumeration.
  * @retval uint32_t            The configured boot address.
  */
uint32_t HAL_FLASH_ITF_OB_GetNSecureBootAddr(const FLASH_TypeDef *flash, const hal_flash_itf_ob_addr_idx_t addr_idx)
{
  ASSERT_DBG_PARAM(flash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_ADDR_IDX(addr_idx));

  return LL_FLASH_OB_GetNSecBootAddr(flash, (uint32_t)addr_idx);
}
/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to handle the Flash interface interrupt subroutines:

- Call HAL_FLASH_ITF_IRQHandler() to handle Flash OB write operations.

- Call HAL_FLASH_ITF_OB_ProgramCpltCallback() to be redefined for the Flash OB complete write operation callback.

- Call HAL_FLASH_ITF_OB_ErrorCallback() to be redefined the Flash OB operation write error callback.

  */

/**
  * @brief  Handle the Flash interface interrupts requests.
  * @param  flash               Pointer to FLASH_TypeDef structure.
  */
void HAL_FLASH_ITF_IRQHandler(FLASH_TypeDef *flash)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(flash != NULL);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  flags = LL_FLASH_NS_ReadFlag_SR(flash, LL_FLASH_FLAG_ALL);

  LL_FLASH_NS_ClearFlag(flash, LL_FLASH_FLAG_ALL);
#else
  flags = LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_ALL);

  LL_FLASH_ClearFlag(flash, LL_FLASH_FLAG_ERRORS_ALL);
#endif /* __ARM_FEATURE_CMSE */

  if ((flags & LL_FLASH_FLAG_EOP) != 0U)
  {
    HAL_FLASH_ITF_OB_ProgramCpltCallback(flash);
  }

  if ((flags & LL_FLASH_FLAG_OPERR) != 0U)
  {
    HAL_FLASH_ITF_OB_ErrorCallback(flash);
  }
}

/**
  * @brief  Flash OB complete write operation callback.
  * @param  flash               Pointer to FLASH_TypeDef structure.
  */
__WEAK void HAL_FLASH_ITF_OB_ProgramCpltCallback(FLASH_TypeDef *flash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flash);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed,
                      HAL_FLASH_ITF_OB_ProgramCpltCallback() function could be implemented in the user file */
}

/**
  * @brief  Flash OB operation write error callback.
  * @param  flash               Pointer to FLASH_TypeDef structure.
  */
__WEAK void HAL_FLASH_ITF_OB_ErrorCallback(FLASH_TypeDef *flash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(flash);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed,
                      HAL_FLASH_ITF_OB_ErrorCallback() function could be implemented in the user file */
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group5
  * @{
  * This subsection provides a set of functions for option bytes process:

  * - Call HAL_FLASH_ITF_OB_Program() to program the Flash option bytes interface.

  * - Call HAL_FLASH_ITF_OB_Launch() to launch the Flash option bytes interface.

  */

/**
  * @brief  Program the Flash option bytes interface settings.
  * @param  flash             Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK            Flash option bytes settings successfully programmed.
  * @retval HAL_ERROR         Flash option bytes settings program error occurred.
  */
hal_status_t HAL_FLASH_ITF_OB_Program(FLASH_TypeDef *flash)
{
  uint32_t tmp_sr;

  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_OB_StartModification(flash);

  tmp_sr = LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY);

  while (tmp_sr != 0U)
  {
    tmp_sr = LL_FLASH_ReadFlag_SR(flash, LL_FLASH_FLAG_BSY);
  }

  if (LL_FLASH_IsActiveFlag_OPTWERR(flash) != 0U)
  {
    LL_FLASH_ClearFlag_OPTWERR(flash);

    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Launch the Flash option bytes interface settings.
  * @param  flash                Pointer to FLASH_TypeDef structure.
  * @retval HAL_OK               Flash option bytes settings successfully launched.
  * @retval HAL_ERROR            Flash option bytes settings loading error occurred.
  */
hal_status_t HAL_FLASH_ITF_OB_Launch(FLASH_TypeDef *flash)
{
  ASSERT_DBG_PARAM(flash != NULL);

  LL_FLASH_OB_Launch(flash);

  return HAL_ERROR;
}

/**
  * @}
  */

#endif /* USE_HAL_FLASH_ITF_MODULE */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
