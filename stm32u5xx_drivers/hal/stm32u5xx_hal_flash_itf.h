/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_flash_itf.h
  * @brief   Header file of FLASH interface HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_FLASH_ITF_H
#define STM32U5XX_HAL_FLASH_ITF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_flash.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup FLASH_ITF FLASH Interface
  * @{
  */
/* Exported Constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Constants FLASH Interface Exported Constants
  * @{
  */
#define HAL_FLASH_ITF_OB_STOP_MODE     1U /*!< FLASH ITF OB stop mode     */
#define HAL_FLASH_ITF_OB_STANDBY_MODE  2U /*!< FLASH ITF OB standby mode  */
#define HAL_FLASH_ITF_OB_SHUTDOWN_MODE 4U /*!< FLASH ITF OB shutdown mode */

#define HAL_FLASH_ITF_OB_BKPRAM        1U /*!< FLASH ITF OB BKPRAM        */
#define HAL_FLASH_ITF_OB_SRAM2         2U /*!< FLASH ITF OB SRAM2         */
#if defined (SRAM3_BASE)
#define HAL_FLASH_ITF_OB_SRAM3         4U /*!< FLASH ITF OB SRAM3         */
#endif /* SRAM3_BASE */
#define HAL_FLASH_ITF_OB_SRAM          8U /*!< FLASH ITF OB SRAM          */

#define HAL_FLASH_ITF_OB_PA15          0U /*!< FLASH ITF OB PA15 pin      */

#define HAL_FLASH_ITF_OB_VDDIO         1U /*!< FLASH ITF OB VDDIO         */
#define HAL_FLASH_ITF_OB_VDDIO2        2U /*!< FLASH ITF OB VDDIO2        */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Types FLASH Interface Exported Types
  * @{
  */

/*! HAL FLASH ITF lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_UNLOCKED = 0U, /*!< FLASH unlocked */
  HAL_FLASH_ITF_LOCKED   = 1U  /*!< FLASH locked   */
} hal_flash_itf_lock_status_t;

/*! HAL FLASH ITF latency enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_LATENCY_0  = LL_FLASH_LATENCY_0WS,  /*!< FLASH ITF zero wait state      */
  HAL_FLASH_ITF_LATENCY_1  = LL_FLASH_LATENCY_1WS,  /*!< FLASH ITF one wait state       */
  HAL_FLASH_ITF_LATENCY_2  = LL_FLASH_LATENCY_2WS,  /*!< FLASH ITF two wait states      */
  HAL_FLASH_ITF_LATENCY_3  = LL_FLASH_LATENCY_3WS,  /*!< FLASH ITF three wait states    */
  HAL_FLASH_ITF_LATENCY_4  = LL_FLASH_LATENCY_4WS,  /*!< FLASH ITF four wait states     */
  HAL_FLASH_ITF_LATENCY_5  = LL_FLASH_LATENCY_5WS,  /*!< FLASH ITF five wait states     */
  HAL_FLASH_ITF_LATENCY_6  = LL_FLASH_LATENCY_6WS,  /*!< FLASH ITF six wait states      */
  HAL_FLASH_ITF_LATENCY_7  = LL_FLASH_LATENCY_7WS,  /*!< FLASH ITF seven wait states    */
  HAL_FLASH_ITF_LATENCY_8  = LL_FLASH_LATENCY_8WS,  /*!< FLASH ITF eight wait states    */
  HAL_FLASH_ITF_LATENCY_9  = LL_FLASH_LATENCY_9WS,  /*!< FLASH ITF nine wait states     */
  HAL_FLASH_ITF_LATENCY_10 = LL_FLASH_LATENCY_10WS, /*!< FLASH ITF ten wait states      */
  HAL_FLASH_ITF_LATENCY_11 = LL_FLASH_LATENCY_11WS, /*!< FLASH ITF eleven wait states   */
  HAL_FLASH_ITF_LATENCY_12 = LL_FLASH_LATENCY_12WS, /*!< FLASH ITF twelve wait states   */
  HAL_FLASH_ITF_LATENCY_13 = LL_FLASH_LATENCY_13WS, /*!< FLASH ITF thirteen wait states */
  HAL_FLASH_ITF_LATENCY_14 = LL_FLASH_LATENCY_14WS, /*!< FLASH ITF fourteen wait states */
  HAL_FLASH_ITF_LATENCY_15 = LL_FLASH_LATENCY_15WS  /*!< FLASH ITF fifteen wait states  */
} hal_flash_itf_latency_t;

/*! HAL FLASH ITF Prefetch enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PREFETCH_DISABLED  = 0U, /*!< FLASH ITF prefetch disabled */
  HAL_FLASH_ITF_PREFETCH_ENABLED   = 1U  /*!< FLASH ITF prefetch enabled  */
} hal_flash_itf_prefetch_status_t;

/*! HAL FLASH ITF power down in run mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PWR_DOWN_RUN_DISABLED = 0U, /*!< FLASH ITF power-down in run mode disabled */
  HAL_FLASH_ITF_PWR_DOWN_RUN_ENABLED  = 1U  /*!< FLASH ITF power-down in run mode enabled  */
} hal_flash_itf_pwr_down_run_status_t;

/*! HAL FLASH ITF power down in sleep mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PWR_DOWN_SLEEP_DISABLED = 0U, /*!< FLASH ITF power-down in sleep mode disabled */
  HAL_FLASH_ITF_PWR_DOWN_SLEEP_ENABLED  = 1U  /*!< FLASH ITF power-down in sleep mode enabled  */
} hal_flash_itf_pwr_down_sleep_status_t;

/*! HAL FLASH ITF low power in read mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_LOW_PWR_READ_DISABLED = 0U, /*!< FLASH ITF low power in read mode disabled */
  HAL_FLASH_ITF_LOW_PWR_READ_ENABLED  = 1U  /*!< FLASH ITF low power in read mode enabled  */
} hal_flash_itf_low_pwr_read_status_t;

/*! HAL FLASH ITF ECC interrupt status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_ECC_IT_DISABLED = 0U, /*!< FLASH ITF ECC interrupt disabled */
  HAL_FLASH_ITF_ECC_IT_ENABLED  = 1U  /*!< FLASH ITF ECC interrupt enabled  */
} hal_flash_itf_ecc_it_status_t;

/*! HAL FLASH ITF Readout Protection key lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_RDP_KEY_UNLOCKED = 0x0U, /*!< FLASH ITF Readout Protection OEM key unlocked */
  HAL_FLASH_ITF_RDP_KEY_LOCKED   = 0x1U  /*!< FLASH ITF Readout Protection OEM key locked   */
} hal_flash_itf_rdp_key_lock_status_t;

/*! HAL FLASH ITF OB lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_UNLOCKED = 0U, /*!< FLASH ITF OB unlocked */
  HAL_FLASH_ITF_OB_LOCKED   = 1U  /*!< FLASH ITF OB locked   */
} hal_flash_itf_ob_lock_status_t;

/*! HAL FLASH ITF OB bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_BANK_1 = LL_FLASH_BANK_1, /*!< FLASH ITF OB Bank 1 */
  HAL_FLASH_ITF_BANK_2 = LL_FLASH_BANK_2  /*!< FLASH ITF OB Bank 1 */
} hal_flash_itf_bank_t;

/*! HAL FLASH ITF OB Area enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_AREA_A = LL_FLASH_OB_BANK_AREA_A, /*!< FLASH ITF OB Bank Area A */
  HAL_FLASH_ITF_OB_BANK_AREA_B = LL_FLASH_OB_BANK_AREA_B  /*!< FLASH ITF OB Bank Area B */
} hal_flash_itf_ob_bank_area_t;

/*! HAL FLASH ITF OB write protection lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WRP_UNLOCKED = 0U, /*!< FLASH ITF OB Write protection unlocked */
  HAL_FLASH_ITF_OB_WRP_LOCKED   = 1U  /*!< FLASH ITF OB Write protection locked   */
} hal_flash_itf_ob_wrp_lock_status_t;

/*! HAL FLASH ITF OB Read Protection level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RDP_LEVEL_0   = LL_FLASH_OB_RDP_LEVEL_0,   /*!< FLASH ITF OB Read protection level 0   */
  HAL_FLASH_ITF_OB_RDP_LEVEL_0_5 = LL_FLASH_OB_RDP_LEVEL_0_5, /*!< FLASH ITF OB Read protection level 0.5 */
  HAL_FLASH_ITF_OB_RDP_LEVEL_1   = LL_FLASH_OB_RDP_LEVEL_1,   /*!< FLASH ITF OB Read protection level 1   */
  HAL_FLASH_ITF_OB_RDP_LEVEL_2   = LL_FLASH_OB_RDP_LEVEL_2    /*!< FLASH ITF OB Read protection level 2   */
} hal_flash_itf_ob_rdp_level_t;

/*! HAL FLASH ITF OB BOR Level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOR_LEVEL_0 = LL_FLASH_OB_BOR_LEVEL_0, /*!< FLASH ITF OB BOR level 0 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_1 = LL_FLASH_OB_BOR_LEVEL_1, /*!< FLASH ITF OB BOR level 1 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_2 = LL_FLASH_OB_BOR_LEVEL_2, /*!< FLASH ITF OB BOR level 2 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_3 = LL_FLASH_OB_BOR_LEVEL_3, /*!< FLASH ITF OB BOR level 3 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_4 = LL_FLASH_OB_BOR_LEVEL_4  /*!< FLASH ITF OB BOR level 4 */
} hal_flash_itf_ob_bor_level_t;

/*! HAL FLASH ITF OB reset generation when enter in low power mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RST_GENERATION    = 0U, /*!< FLASH ITF OB reset generation when enter in low power mode    */
  HAL_FLASH_ITF_OB_NO_RST_GENERATION = 1U  /*!< FLASH ITF OB no reset generation when enter in low power mode */
} hal_flash_itf_ob_rst_generation_status_t;

/*! HAL FLASH ITF OB Erased sram when system reset enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SYS_RST_SRAM_ERASE    = 0U, /*!< FLASH ITF OB Erased SRAM when system reset occurs    */
  HAL_FLASH_ITF_OB_SYS_RST_SRAM_NO_ERASE = 1U  /*!< FLASH ITF OB No erased SRAM when system reset occurs */
} hal_flash_itf_ob_sys_rst_sram_erase_t;

/*! HAL FLASH ITF OB WDG hardware/software mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_HARDWARE = 0U, /*!< FLASH ITF OB WDG hardware select */
  HAL_FLASH_ITF_OB_WDG_SOFTWARE = 1U  /*!< FLASH ITF OB WDG software select */
} hal_flash_itf_ob_wdg_mode_t;

/*! HAL FLASH ITF OB WDG counter low power mode freeze enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_FROZEN   = 1U, /*!< FLASH ITF OB WDG counter low power mode frozen  */
  HAL_FLASH_ITF_OB_WDG_UNFROZEN = 0U  /*!< FLASH ITF OB WDG counter low power mode running */
} hal_flash_itf_ob_wdg_freeze_status_t;

/*! HAL FLASH ITF OB Swapping bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_NO_SWAP = LL_FLASH_OB_BANK_NOT_SWAPPED, /*!< FLASH ITF OB Bank not swapped */
  HAL_FLASH_ITF_OB_BANK_SWAP    = LL_FLASH_OB_BANK_SWAPPED      /*!< FLASH ITF OB Bank swapped     */
} hal_flash_itf_ob_bank_swap_t;

/*! HAL FLASH ITF OB Single/Dual bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SINGLE_BANK = LL_FLASH_OB_SINGLE_BANK, /*!< FLASH ITF OB Single bank */
  HAL_FLASH_ITF_OB_DUAL_BANK   = LL_FLASH_OB_DUAL_BANK    /*!< FLASH ITF OB Dual bank   */
} hal_flash_itf_ob_topology_t ;

/*! HAL FLASH ITF OB SRAM ECC enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SRAM_ECC_DISABLED = 0U, /*!< FLASH ITF OB SRAM ECC disable */
  HAL_FLASH_ITF_OB_SRAM_ECC_ENABLED  = 1U  /*!< FLASH ITF OB SRAM ECC enable  */
} hal_flash_itf_ob_sram_ecc_status_t ;

/*! HAL FLASH ITF OB Software boot0 selection enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_PIN        = LL_FLASH_OB_BOOT0_BOOTPIN, /*!< FLASH ITF OB boot taken from boot pin */
  HAL_FLASH_ITF_OB_BOOT_OPTION_BIT = LL_FLASH_OB_BOOT0_NBOOTBIT /*!< FLASH ITF OB boot taken from boot bit */
} hal_flash_itf_ob_boot_selection_t;

/*! HAL FLASH ITF OB Software boot0 state enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_LOW  = LL_FLASH_OB_BOOT0_LOW, /*!< FLASH ITF OB boot taken from boot address 0 */
  HAL_FLASH_ITF_OB_BOOT_HIGH = LL_FLASH_OB_BOOT0_HIGH /*!< FLASH ITF OB boot taken from boot address 1 */
} hal_flash_itf_ob_boot_state_t;

/*! HAL FLASH ITF OB pull mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_PULL_NO   = 0U, /*!< FLASH ITF OB no pull   */
  HAL_FLASH_ITF_OB_PULL_DOWN = 1U, /*!< FLASH ITF OB pull down */
  HAL_FLASH_ITF_OB_PULL_UP   = 2U  /*!< FLASH ITF OB pull up   */
} hal_flash_itf_ob_pull_mode_t;

/*! HAL FLASH ITF OB pin pull enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_PIN_PULL_DISABLED = 0U, /*!< FLASH ITF OB pullup pin disable */
  HAL_FLASH_ITF_OB_PIN_PULL_ENABLED  = 1U  /*!< FLASH ITF OB pullup pin enable  */
} hal_flash_itf_ob_pin_pull_status_t;

/*! HAL FLASH ITF OB VDDI HSLV enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_VDDX_HSLV_DISABLED = 0U, /*!< FLASH ITF OB VDD HSLV disable */
  HAL_FLASH_ITF_OB_VDDX_HSLV_ENABLED  = 1U  /*!< FLASH ITF OB VDD HSLV enable  */
} hal_flash_itf_ob_vddx_hslv_status_t;

/*! HAL FLASH ITF OB TrustZone enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_TRUSTZONE_DISABLED = 0U, /*!< FLASH ITF OB TrustZone disabled */
  HAL_FLASH_ITF_OB_TRUSTZONE_ENABLED  = 1U  /*!< FLASH ITF OB TrustZone enabled  */
} hal_flash_itf_ob_trustzone_status_t;

/*! HAL FLASH ITF OB address enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_ADDR_0 = 0U, /*!< FLASH ITF OB address 0 */
  HAL_FLASH_ITF_OB_ADDR_1 = 1U  /*!< FLASH ITF OB address 1 */
} hal_flash_itf_ob_addr_idx_t;

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/*! HAL FLASH ITF OB hide protection area enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_HDP_AREA_DISABLED = 0U, /*!< FLASH ITF OB hide protection area disabled */
  HAL_FLASH_ITF_OB_HDP_AREA_ENABLED  = 1U  /*!< FLASH ITF OB hide protection area enabled  */
} hal_flash_itf_ob_hdp_area_status_t;

/*! HAL FLASH ITF OB boot address lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_UNLOCKED = 0U, /*!< FLASH ITF OB boot unlocked */
  HAL_FLASH_ITF_OB_BOOT_LOCKED   = 1U  /*!< FLASH ITF OB boot locked   */
} hal_flash_itf_ob_boot_lock_status_t;
#endif /* __ARM_FEATURE_CMSE */

/*! HAL FLASH ITF OB Readout Protection OEM key structure definition */
typedef struct
{
  uint32_t key_w1; /*!< FLASH ITF OB OEM Key low bytes */
  uint32_t key_w2; /*!< FLASH ITF OB OEM Key high bytes */
} hal_flash_itf_ob_rdp_oem_key_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Functions FLASH Interface Exported Functions
  * @{
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group1 FLASH Interface Lock and Unlock functions
  * @{
  */
hal_status_t HAL_FLASH_ITF_Lock(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_Unlock(FLASH_TypeDef *flash);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(const FLASH_TypeDef *flash);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
hal_status_t HAL_FLASH_ITFNS_Lock(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITFNS_Unlock(FLASH_TypeDef *flash);
hal_flash_itf_lock_status_t HAL_FLASH_ITFNS_IsLocked(const FLASH_TypeDef *flash);
#endif /* __ARM_FEATURE_CMSE */

hal_status_t HAL_FLASH_ITF_OB_Lock(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_OB_Unlock(FLASH_TypeDef *flash);
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(const FLASH_TypeDef *flash);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group2 FLASH Interface control functions
  * @{
  */
hal_status_t HAL_FLASH_ITF_SetLatency(FLASH_TypeDef *flash, hal_flash_itf_latency_t latency);
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_EnablePrefetch(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_DisablePrefetch(FLASH_TypeDef *flash);
hal_flash_itf_prefetch_status_t HAL_FLASH_ITF_IsEnabledPrefetch(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_EnablePWRDownRunMode(FLASH_TypeDef *flash, hal_flash_itf_bank_t bank);
hal_flash_itf_pwr_down_run_status_t HAL_FLASH_ITF_IsEnabledRunModePWRDown(const FLASH_TypeDef *flash,
                                                                          const hal_flash_itf_bank_t bank);

hal_status_t HAL_FLASH_ITF_EnablePWRDownSleepMode(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_DisablePWRDownSleepMode(FLASH_TypeDef *flash);
hal_flash_itf_pwr_down_sleep_status_t HAL_FLASH_ITF_IsEnabledSleepModePWRDown(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_EnableLowPWRReadMode(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_DisableLowPWRReadMode(FLASH_TypeDef *flash);
hal_flash_itf_low_pwr_read_status_t HAL_FLASH_ITF_IsEnabledLowPWRReadMode(const FLASH_TypeDef *flash);

#if defined (USE_HAL_FLASH_ITF_ECC) && (USE_HAL_FLASH_ITF_ECC == 1U)
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(FLASH_TypeDef *flash);
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledIT(const FLASH_TypeDef *flash);
#endif /* USE_HAL_FLASH_ITF_ECC */

hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPOEM1Key(const FLASH_TypeDef *flash);
hal_flash_itf_rdp_key_lock_status_t HAL_FLASH_ITF_IsLockedRDPOEM2Key(const FLASH_TypeDef *flash);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group3 FLASH Interface option bytes configuration functions
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
hal_status_t HAL_FLASH_ITF_OB_SetSecureWMArea(FLASH_TypeDef *flash,
                                              hal_flash_itf_bank_t bank,
                                              uint32_t start_page,
                                              uint32_t page_nbr);
void HAL_FLASH_ITF_OB_GetSecureWMArea(const FLASH_TypeDef *flash,
                                      const hal_flash_itf_bank_t bank,
                                      uint32_t *p_start_page,
                                      uint32_t *p_page_nbr);

hal_status_t HAL_FLASH_ITF_OB_SetConfigHDPArea(FLASH_TypeDef *flash,
                                               hal_flash_itf_bank_t bank,
                                               uint32_t page_nbr);
void HAL_FLASH_ITF_OB_GetConfigHDPArea(const FLASH_TypeDef *flash,
                                       const hal_flash_itf_bank_t bank,
                                       uint32_t *p_page_nbr);

hal_status_t HAL_FLASH_ITF_OB_EnableHDPArea(FLASH_TypeDef *flash, hal_flash_itf_bank_t bank);
hal_status_t HAL_FLASH_ITF_OB_DisableHDPArea(FLASH_TypeDef *flash, hal_flash_itf_bank_t bank);
hal_flash_itf_ob_hdp_area_status_t HAL_FLASH_ITF_OB_IsEnabledHDPArea(const FLASH_TypeDef *flash,
                                                                     const hal_flash_itf_bank_t bank);

hal_status_t HAL_FLASH_ITF_OB_SetSecureBootAddr(FLASH_TypeDef *flash, uint32_t boot_addr);
uint32_t HAL_FLASH_ITF_OB_GetSecureBootAddr(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(FLASH_TypeDef *flash);
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(const FLASH_TypeDef *flash);
#endif /* __ARM_FEATURE_CMSE */

hal_status_t HAL_FLASH_ITF_OB_SetWRPArea(FLASH_TypeDef *flash,
                                         hal_flash_itf_bank_t bank,
                                         hal_flash_itf_ob_bank_area_t area,
                                         uint32_t start_page,
                                         uint32_t page_nbr);

void HAL_FLASH_ITF_OB_GetWRPArea(const FLASH_TypeDef *flash,
                                 const hal_flash_itf_bank_t bank,
                                 const hal_flash_itf_ob_bank_area_t area,
                                 uint32_t *p_start_page,
                                 uint32_t *p_page_nbr);

hal_status_t HAL_FLASH_ITF_OB_LockWRPAreaConfig(FLASH_TypeDef *flash,
                                                hal_flash_itf_bank_t bank,
                                                hal_flash_itf_ob_bank_area_t area);
hal_status_t HAL_FLASH_ITF_OB_UnlockWRPAreaConfig(FLASH_TypeDef *flash,
                                                  hal_flash_itf_bank_t bank,
                                                  hal_flash_itf_ob_bank_area_t area);
hal_flash_itf_ob_wrp_lock_status_t HAL_FLASH_ITF_OB_IsLockedWRPAreaConfig(const FLASH_TypeDef *flash,
                                                                          const hal_flash_itf_bank_t bank,
                                                                          const hal_flash_itf_ob_bank_area_t area);

hal_status_t HAL_FLASH_ITF_OB_SetRDPLevel(FLASH_TypeDef *flash, hal_flash_itf_ob_rdp_level_t rdp_level);
hal_flash_itf_ob_rdp_level_t HAL_FLASH_ITF_OB_GetRDPLevel(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_SetRDPOEM1Key(FLASH_TypeDef *flash, hal_flash_itf_ob_rdp_oem_key_t *p_key);
hal_status_t HAL_FLASH_ITF_OB_SetRDPOEM2Key(FLASH_TypeDef *flash, hal_flash_itf_ob_rdp_oem_key_t *p_key);

hal_status_t HAL_FLASH_ITF_OB_SetBORLevel(FLASH_TypeDef *flash, hal_flash_itf_ob_bor_level_t bor_level);
hal_flash_itf_ob_bor_level_t HAL_FLASH_ITF_OB_GetBORLevel(const FLASH_TypeDef *flash);


hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(FLASH_TypeDef *flash,
                                                              uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen);
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(const FLASH_TypeDef *flash,
    uint32_t low_pwr_mode);


hal_status_t HAL_FLASH_ITF_OB_SetSystemRstSRAMErase(FLASH_TypeDef *flash,
                                                    uint32_t sram,
                                                    hal_flash_itf_ob_sys_rst_sram_erase_t sram_erase);
hal_flash_itf_ob_sys_rst_sram_erase_t HAL_FLASH_ITF_OB_GetSystemRstSRAMErase(const FLASH_TypeDef *flash,
                                                                             uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(FLASH_TypeDef *flash, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_SetWWDGMode(FLASH_TypeDef *flash, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetWWDGMode(const FLASH_TypeDef *flash);


hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flash, uint32_t low_pwr_mode);
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(FLASH_TypeDef *flash, uint32_t low_pwr_mode);
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(const FLASH_TypeDef *flash,
    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(FLASH_TypeDef *flash, hal_flash_itf_ob_bank_swap_t bank_swap);
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_SetBankTopology(FLASH_TypeDef *flash, hal_flash_itf_ob_topology_t bank_topology);
hal_flash_itf_ob_topology_t HAL_FLASH_ITF_OB_GetBankTopology(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(FLASH_TypeDef *flash, uint32_t sram);
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(FLASH_TypeDef *flash, uint32_t sram);
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(const FLASH_TypeDef *flash, uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_SetBootSelection(FLASH_TypeDef *flash,
                                               hal_flash_itf_ob_boot_selection_t boot_select);
hal_flash_itf_ob_boot_selection_t HAL_FLASH_ITF_OB_GetBootSelection(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_SetBoot0(FLASH_TypeDef *flash, hal_flash_itf_ob_boot_state_t state);
hal_flash_itf_ob_boot_state_t HAL_FLASH_ITF_OB_GetBoot0(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_SetIOPull(FLASH_TypeDef *flash,
                                        uint32_t pin,
                                        hal_flash_itf_ob_pull_mode_t pull_mode);
hal_flash_itf_ob_pin_pull_status_t HAL_FLASH_ITF_OB_GetIOPull(const FLASH_TypeDef *flash, uint32_t pin);

hal_status_t HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage(FLASH_TypeDef *flash, uint32_t vdd);
hal_status_t HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage(FLASH_TypeDef *flash, uint32_t vdd);
hal_flash_itf_ob_vddx_hslv_status_t HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage(const FLASH_TypeDef *flash,
    uint32_t vdd);

hal_status_t HAL_FLASH_ITF_OB_EnableTrustZone(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_OB_DisableTrustZone(FLASH_TypeDef *flash);
hal_flash_itf_ob_trustzone_status_t HAL_FLASH_ITF_OB_IsEnabledTrustZone(const FLASH_TypeDef *flash);

hal_status_t HAL_FLASH_ITF_OB_SetNSecureBootAddr(FLASH_TypeDef *flash,
                                                 hal_flash_itf_ob_addr_idx_t addr_idx,
                                                 uint32_t boot_addr);
uint32_t HAL_FLASH_ITF_OB_GetNSecureBootAddr(const FLASH_TypeDef *flash, const hal_flash_itf_ob_addr_idx_t addr_idx);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group4 FLASH Interface interrupt management functions
  * @{
  */
void HAL_FLASH_ITF_IRQHandler(FLASH_TypeDef *flash);
void HAL_FLASH_ITF_OB_ProgramCpltCallback(FLASH_TypeDef *flash);
void HAL_FLASH_ITF_OB_ErrorCallback(FLASH_TypeDef *flash);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group5 FLASH Interface option bytes process functions
  * @{
  */
hal_status_t HAL_FLASH_ITF_OB_Program(FLASH_TypeDef *flash);
hal_status_t HAL_FLASH_ITF_OB_Launch(FLASH_TypeDef *flash);
/**
  * @}
  */

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

#endif /* STM32U5XX_HAL_FLASH_ITF_H */
