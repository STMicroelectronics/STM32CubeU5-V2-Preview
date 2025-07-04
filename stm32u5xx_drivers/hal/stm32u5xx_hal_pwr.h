/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_pwr.h
  * @brief   Header file of PWR HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_PWR_H
#define STM32U5XX_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_pwr.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/*! HAL PWR wakeup pin polarity enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_POLARITY_LOW  = LL_PWR_WAKEUP_PIN_POLARITY_LOW,  /*!< Wakeup pin low polarity  */
  HAL_PWR_WAKEUP_PIN_POLARITY_HIGH = LL_PWR_WAKEUP_PIN_POLARITY_HIGH  /*!< Wakeup pin high polarity */
} hal_pwr_wakeup_pin_polarity_t;

/*! HAL PWR wakeup pin source enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_SOURCE_0 = LL_PWR_WAKEUP_PIN_SELECTION_0, /*!< Wakeup pin source 0 */
  HAL_PWR_WAKEUP_PIN_SOURCE_1 = LL_PWR_WAKEUP_PIN_SELECTION_1, /*!< Wakeup pin source 1 */
  HAL_PWR_WAKEUP_PIN_SOURCE_2 = LL_PWR_WAKEUP_PIN_SELECTION_2, /*!< Wakeup pin source 2 */
  HAL_PWR_WAKEUP_PIN_SOURCE_3 = LL_PWR_WAKEUP_PIN_SELECTION_3  /*!< Wakeup pin source 3 */
} hal_pwr_wakeup_pin_source_t;

/*! HAL PWR wakeup pin status enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_DISABLED = 0U, /*!< Wakeup pin disabled */
  HAL_PWR_WAKEUP_PIN_ENABLED  = 1U  /*!< Wakeup pin enabled  */
} hal_pwr_wakeup_pin_status_t;

/*! HAL PWR wakeup pin configuration structure definition */
typedef struct
{
  hal_pwr_wakeup_pin_polarity_t polarity; /*!< Wakeup pin polarity */
  hal_pwr_wakeup_pin_source_t   source;   /*!< Wakeup pin source   */
} hal_pwr_wakeup_pin_config_t;

/*! HAL PWR RTC domain write protection status enumeration definition */
typedef enum
{
  HAL_PWR_RTC_DOMAIN_WRP_DISABLED = 0U, /*!< RTC domain write protection disabled */
  HAL_PWR_RTC_DOMAIN_WRP_ENABLED  = 1U  /*!< RTC domain write protection enabled  */
} hal_pwr_rtc_domain_wrp_status_t;

/*! HAL PWR voltage scaling range enumeration definition */
typedef enum
{
  HAL_PWR_VOLT_SCALE_1 = LL_PWR_REGU_VOLT_SCALE_1, /*!< Voltage scaling range 1 */
  HAL_PWR_VOLT_SCALE_2 = LL_PWR_REGU_VOLT_SCALE_2, /*!< Voltage scaling range 2 */
  HAL_PWR_VOLT_SCALE_3 = LL_PWR_REGU_VOLT_SCALE_3, /*!< Voltage scaling range 3 */
  HAL_PWR_VOLT_SCALE_4 = LL_PWR_REGU_VOLT_SCALE_4  /*!< Voltage scaling range 4 */
} hal_pwr_volt_scale_range_t;

/*! HAL PWR main regulator source enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_LDO_SUPPLY  = LL_PWR_MAIN_REGU_LDO_SUPPLY, /*!< Main regulator LDO source  */
  HAL_PWR_MAIN_REGULATOR_SMPS_SUPPLY = LL_PWR_MAIN_REGU_SMPS_SUPPLY /*!< Main regulator SMPS source */
} hal_pwr_main_regulator_supply_t;

/*! HAL PWR IO analog switch enumeration definition */
typedef enum
{
  HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY    = LL_SYSCFG_VDDA_SUPPLY,    /*!< PWR Analog IO switch to VddA supply     */
  HAL_PWR_ANALOG_IO_SWITCH_VDD_2V4_SUPPLY = LL_SYSCFG_VDD_2V4_SUPPLY, /*!< PWR Analog IO switch to Vdd 2.4V supply */
  HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY = LL_SYSCFG_BOOSTER_SUPPLY  /*!< PWR Analog IO switch to booster supply  */
} hal_pwr_analog_io_switch_supply_t;

/*! HAL PWR fast soft start mode enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_SLOW_STARTUP = LL_PWR_MAIN_REGU_SLOW_STARTUP, /*!< Main regulator slow startup (limited inrush current) */
  HAL_PWR_MAIN_REGULATOR_FAST_STARTUP = LL_PWR_MAIN_REGU_FAST_STARTUP  /*!< Main regulator fast startup                          */
} hal_pwr_main_regulator_fast_startup_mode_t;

/*! HAL PWR independent supply status enumeration definition */
typedef enum
{
  HAL_PWR_INDEPENDENT_SUPPLY_DISABLED = 0U, /*!< Independent supply disabled */
  HAL_PWR_INDEPENDENT_SUPPLY_ENABLED  = 1U  /*!< Independent supply enabled  */
} hal_pwr_independent_supply_status_t;

/*! HAL PWR low power mode entry request enumeration definition */
typedef enum
{
  HAL_PWR_LOW_PWR_MODE_WFE = 0U, /*!< Low power mode wait for event request     */
  HAL_PWR_LOW_PWR_MODE_WFI = 1U  /*!< Low power mode wait for interrupt request */
} hal_pwr_low_pwr_mode_entry_t;

/*! HAL PWR Stop mode enumeration definition */
typedef enum
{
  HAL_PWR_STOP0_MODE = LL_PWR_STOP0_MODE, /*!< Stop 0 mode */
  HAL_PWR_STOP1_MODE = LL_PWR_STOP1_MODE, /*!< Stop 1 mode */
  HAL_PWR_STOP2_MODE = LL_PWR_STOP2_MODE, /*!< Stop 2 mode */
  HAL_PWR_STOP3_MODE = LL_PWR_STOP3_MODE  /*!< Stop 3 mode */
} hal_pwr_stop_mode_t;

/*! HAL PWR core sleep enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SLEEP      = LL_PWR_CORE_SLEEP,      /*!< Core sleep mode      */
  HAL_PWR_CORE_DEEP_SLEEP = LL_PWR_CORE_DEEP_SLEEP  /*!< Core deep sleep mode */
} hal_pwr_core_sleep_mode_t;

/*! HAL PWR core sleep status enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SLEEP_ON_EXIT_DISABLED = 0U, /*!< PWR Core sleep on exit disabled */
  HAL_PWR_CORE_SLEEP_ON_EXIT_ENABLED  = 1U  /*!< PWR Core sleep on exit enabled  */
} hal_pwr_core_sleep_on_exit_status_t;


/*! HAL PWR core send event on pending status enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SEV_ON_PEND_DISABLED = 0U, /*!< Core send event on pendinhg disabled */
  HAL_PWR_CORE_SEV_ON_PEND_ENABLED  = 1U  /*!< Core send event on pendinhg enabled  */
} hal_pwr_core_sev_on_pending_status_t;

/*! HAL PWR low power smart run domain mode in system mode enumeration definition */
typedef enum
{
  HAL_PWR_SYSTEM_STOP_SRD_STOP = LL_PWR_SRD_STOP_MODE, /*!< Smart run domain in Stop mode when system goes to Stop mode */
  HAL_PWR_SYSTEM_STOP_SRD_RUN  = LL_PWR_SRD_RUN_MODE   /*!< Smart run domain in Run mode when system goes to Stop mode  */
} hal_pwr_system_mode_srd_mode_t;

/*! HAL PWR brownout reset mode enumeration definition */
typedef enum
{
  HAL_PWR_BROWNOUT_RESET_CONTINUOUS_MODE    = LL_PWR_BOR_CONTINUOUS_MODE,   /*!< Brownout reset continuous mode    */
  HAL_PWR_BROWNOUT_RESET_DISCONTINUOUS_MODE = LL_PWR_BOR_DISCONTINUOUS_MODE /*!< Brownout reset discontinuous mode */
} hal_pwr_brownout_reset_mode_t;

/*! HAL PWR power voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_PVD_LEVEL_0 = LL_PWR_PVDLEVEL_0, /*!< Voltage threshold detected by PVD 2.0 V                          */
  HAL_PWR_PVD_LEVEL_1 = LL_PWR_PVDLEVEL_1, /*!< Voltage threshold detected by PVD 2.2 V                          */
  HAL_PWR_PVD_LEVEL_2 = LL_PWR_PVDLEVEL_2, /*!< Voltage threshold detected by PVD 2.4 V                          */
  HAL_PWR_PVD_LEVEL_3 = LL_PWR_PVDLEVEL_3, /*!< Voltage threshold detected by PVD 2.5 V                          */
  HAL_PWR_PVD_LEVEL_4 = LL_PWR_PVDLEVEL_4, /*!< Voltage threshold detected by PVD 2.6 V                          */
  HAL_PWR_PVD_LEVEL_5 = LL_PWR_PVDLEVEL_5, /*!< Voltage threshold detected by PVD 2.8 V                          */
  HAL_PWR_PVD_LEVEL_6 = LL_PWR_PVDLEVEL_6, /*!< Voltage threshold detected by PVD 2.9 V                          */
  HAL_PWR_PVD_LEVEL_7 = LL_PWR_PVDLEVEL_7  /*!< External input on PVD_IN pin, compared to internal VREFINT level */
} hal_pwr_pvd_level_t;

/*! HAL PWR programmable voltage detector status enumeration definition */
typedef enum
{
  HAL_PWR_PVD_DISABLED = 0U, /*!< PWR PVD disabled */
  HAL_PWR_PVD_ENABLED  = 1U  /*!< PWR PVD enabled  */
} hal_pwr_pvd_status_t;

/*! HAL PWR voltage monitor status enumeration definition */
typedef enum
{
  HAL_PWR_MONITOR_DISABLED = 0U, /*!< PWR Voltage monitor disabled */
  HAL_PWR_MONITOR_ENABLED  = 1U  /*!< PWR Voltage monitor enabled  */
} hal_pwr_monitor_status_t;

/*! HAL PWR memory retention status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_DISABLED = 0U, /*!< PWR memory retention disabled */
  HAL_PWR_MEMORY_RETENTION_ENABLED  = 1U, /*!< PWR memory retention enabled  */
} hal_pwr_memory_retention_status_t;

/*! HAL PWR paginated memory retention status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_PAGE_RETENTION_DISABLED = 0U, /*!< PWR memory page retention disabled */
  HAL_PWR_MEMORY_PAGE_RETENTION_ENABLED  = 1U, /*!< PWR memory page retention enabled  */
} hal_pwr_memory_page_retention_status_t;

/*! HAL PWR memory retention enumeration definition */
typedef enum
{
#if defined(PWR_CR5_SRAM6PDS1)
  HAL_PWR_MEMORY_RETENTION_SRAM1_RUN                 = 0U,  /*!< SRAM1 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM2_RUN                 = 1U,  /*!< SRAM2 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM3_RUN                 = 2U,  /*!< SRAM3 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM4_RUN                 = 3U,  /*!< SRAM4 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM5_RUN                 = 4U,  /*!< SRAM5 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM6_RUN                 = 5U,  /*!< SRAM6 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123            = 6U,  /*!< SRAM1 memory retention in Stop0123 mode (12 pages)         */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012             = 7U,  /*!< SRAM2 memory retention in Stop012 mode (2 pages)           */
  HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123            = 8U,  /*!< SRAM4 memory retention in Stop0123 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123          = 9U,  /*!< DCACHE2 memory retention in Stop0123 mode (1 page)         */
  HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123           = 10U, /*!< ICACHE memory retention in Stop0123 mode (1 page)          */
  HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123          = 11U, /*!< DCACHE1 memory retention in Stop0123 mode (1 page)         */
  HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123         = 12U, /*!< DMA2DRAM memory retention in Stop0123 mode (1 page)        */
  HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123        = 13U, /*!< PERIPHRAM memory retention in Stop0123 mode (1 page)       */
  HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123            = 14U, /*!< SRAM3 memory retention in Stop0123 mode  (13 pages)        */
  HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123 = 15U, /*!< GPRAM memory retention in Stop0123 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_JPEGRAM_STOP01            = 16U, /*!< JPEGRAM memory retention in Stop01 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123            = 17U, /*!< SRAM5 memory retention in Stop0123 mode (13 pages)         */
  HAL_PWR_MEMORY_RETENTION_SRAM6_STOP0123            = 18U, /*!< SRAM6 memory retention in Stop0123 mode (13 pages)         */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY       = 19U, /*!< SRAM2 memory retention in Stop3 and Standby mode (2 pages) */
  HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT       = 20U, /*!< BKPRAM memory retention in Standby and Vbat (1 page)       */
#if defined(PWR_CR2_DSIRAMPDS)
  HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01             = 21U, /*!< DSIRAM memory retention in Stop01 mode (1 page)            */
#endif /* defined(PWR_CR2_DSIRAMPDS) */
#if defined(PWR_CR2_PKARAMPDS)
  HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123         = 22U  /*!< PKA32RAM memory retention in Stop0123 mode (1 page)        */
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR4_SRAM5PDS1)
  HAL_PWR_MEMORY_RETENTION_SRAM1_RUN                 = 0U,  /*!< SRAM1 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM2_RUN                 = 1U,  /*!< SRAM2 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM3_RUN                 = 2U,  /*!< SRAM3 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM4_RUN                 = 3U,  /*!< SRAM4 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM5_RUN                 = 4U,  /*!< SRAM5 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123            = 5U,  /*!< SRAM1 memory retention in Stop0123 mode (12 pages)         */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012             = 6U,  /*!< SRAM2 memory retention in Stop012 mode (2 pages)           */
  HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123            = 7U,  /*!< SRAM4 memory retention in Stop0123 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_DCACHE2_STOP0123          = 8U,  /*!< DCACHE2 memory retention in Stop0123 mode (1 page)         */
  HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123           = 9U,  /*!< ICACHE memory retention in Stop0123 mode 1 page)           */
  HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123          = 10U, /*!< DCACHE1 memory retention in Stop0123 mode (1 page)         */
  HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123         = 11U, /*!< DMA2DRAM memory retention in Stop0123 mode (1 page)        */
  HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123        = 12U, /*!< PERIPHRAM memory retention in Stop0123 mode (1 page)       */
  HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123            = 13U, /*!< SRAM3 memory retention in Stop0123 mode (13 pages)         */
  HAL_PWR_MEMORY_RETENTION_GRAPHICPERIPHRAM_STOP0123 = 14U, /*!< GPRAM memory retention in Stop0123 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_SRAM5_STOP0123            = 15U, /*!< SRAM5 memory retention in Stop0123 mode (13 pages)         */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY       = 16U, /*!< SRAM2 memory retention in Stop3 and Standby mode (2 pages) */
  HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT       = 17U, /*!< BKPRAM memory retention in Standby and Vbat (1 page)       */
#if defined(PWR_CR2_DSIRAMPDS)
  HAL_PWR_MEMORY_RETENTION_DSIRAM_STOP01             = 18U, /*!< DSIRAM memory retention in Stop01 mode (1 page)            */
#endif /* defined(PWR_CR2_DSIRAMPDS) */
#if defined(PWR_CR2_PKARAMPDS)
  HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123         = 19U  /*!< PKA32RAM memory retention in Stop0123 mode (1 page)        */
#endif /* defined(PWR_CR2_PKARAMPDS) */
#elif defined(PWR_CR2_SRAM3PDS1)
  HAL_PWR_MEMORY_RETENTION_SRAM1_RUN                 = 0U,  /*!< SRAM1 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM2_RUN                 = 1U,  /*!< SRAM2 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM3_RUN                 = 2U,  /*!< SRAM3 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM4_RUN                 = 3U,  /*!< SRAM4 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123            = 4U,  /*!< SRAM1 memory retention in Stop0123 mode (3 pages)          */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012             = 5U,  /*!< SRAM2 memory retention in Stop012 mode (2 pages)           */
  HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123            = 6U,  /*!< SRAM4 memory retention in Stop0123 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123           = 7U,  /*!< ICACHE memory retention in Stop0123 mode (1 page)          */
  HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123          = 8U,  /*!< DCACHE1 memory retention in Stop0123 mode (1 page)         */
  HAL_PWR_MEMORY_RETENTION_DMA2DRAM_STOP0123         = 9U,  /*!< DMA2DRAM memory retention in Stop0123 mode (1 page)        */
  HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123        = 10U, /*!< PERIPHRAM memory retention in Stop0123 mode (1 page)       */
  HAL_PWR_MEMORY_RETENTION_SRAM3_STOP0123            = 11U, /*!< SRAM3 memory retention in Stop0123 mode (3 pages)          */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY       = 12U, /*!< SRAM2 memory retention in Stop3 and Standby mode (2 pages) */
  HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT       = 13U, /*!< BKPRAM memory retention in Standby and Vbat (1 page)       */
#if defined(PWR_CR2_PKARAMPDS)
  HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123         = 14U  /*!< PKA32RAM memory retention in Stop0123 mode (1 page)        */
#endif /* defined(PWR_CR2_PKARAMPDS) */
#else
  HAL_PWR_MEMORY_RETENTION_SRAM1_RUN                 = 0U,  /*!< SRAM1 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM2_RUN                 = 1U,  /*!< SRAM2 memory retention in Run mode (1 page)                */
  HAL_PWR_MEMORY_RETENTION_SRAM4_RUN                 = 2U,  /*!< SRAM4 memory retention in Run mode  (1 page)               */
  HAL_PWR_MEMORY_RETENTION_SRAM1_STOP0123            = 3U,  /*!< SRAM1 memory retention in Stop0123 mode (3 pages)          */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP012             = 4U,  /*!< SRAM2 memory retention in Stop012 mode (2 pages)           */
  HAL_PWR_MEMORY_RETENTION_SRAM4_STOP0123            = 5U,  /*!< SRAM4 memory retention in Stop0123 mode (1 page)           */
  HAL_PWR_MEMORY_RETENTION_ICACHE_STOP0123           = 6U,  /*!< ICACHE memory retention in Stop0123 mode (1 page)          */
  HAL_PWR_MEMORY_RETENTION_DCACHE1_STOP0123          = 7U,  /*!< DCACHE1 memory retention in Stop0123 mode (1 page)         */
  HAL_PWR_MEMORY_RETENTION_PERIPHRAM_STOP0123        = 8U,  /*!< PERIPHRAM memory retention in Stop0123 mode (2 pages)      */
  HAL_PWR_MEMORY_RETENTION_SRAM2_STOP3_STANDBY       = 9U,  /*!< SRAM2 memory retention in Stop3 and Standby mode (2 pages) */
  HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT       = 10U, /*!< BKPRAM memory retention in Standby and Vbat (1 page)       */
#if defined(PWR_CR2_PKARAMPDS)
  HAL_PWR_MEMORY_RETENTION_PKA32RAM_STOP0123         = 11U  /*!< PKA32RAM memory retention in Stop0123 mode (1 page)        */
#endif /* defined(PWR_CR2_PKARAMPDS) */
#endif /* PWR_CR5_SRAM6PDS1 */
} hal_pwr_memory_retention_t;

#if defined(PWR_UCPDR_UCPD_STDBY)
/*! HAL PWR UCPD retention status enumeration definition */
typedef enum
{
  HAL_PWR_UCPD_RETENTION_DISABLED = 0U, /*!< PWR UCPD retention disabled */
  HAL_PWR_UCPD_RETENTION_ENABLED  = 1U  /*!< PWR UCPD retention enabled  */
} hal_pwr_ucpd_retention_status_t;
#endif /* PWR_UCPDR_UCPD_STDBY */

#if defined(PWR_CR1_FORCE_USBPWR)
/*! HAL PWR OTG PHY retention status enumeration definition */
typedef enum
{
  HAL_PWR_OTGHSPHY_RETENTION_DISABLED = 0U, /*!< PWR OTG HS PHY retention disabled */
  HAL_PWR_OTGHSPHY_RETENTION_ENABLED  = 1U  /*!< PWR OTG HS PHY retention enabled  */
} hal_pwr_otghsphy_retention_status_t;
#endif /* PWR_UCPDR_UCPD_STDBY */

/*! HAL PWR Memory fast wakeup status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_FAST_WAKEUP_DISABLED = 0U, /*!< Memory fast wakeup disabled */
  HAL_PWR_MEMORY_FAST_WAKEUP_ENABLED  = 1U  /*!< Memory fast wakeup enabled  */
} hal_pwr_memory_fast_wakeup_status_t;

/*! HAL PWR battery charging resistor value enumeration definition */
typedef enum
{
  HAL_PWR_BATTERY_CHARGING_RES_5K   = LL_PWR_BATT_CHARG_RESISTOR_5K,  /*!< Battery charging resistor 5KOhm   */
  HAL_PWR_BATTERY_CHARGING_RES_1_5K = LL_PWR_BATT_CHARG_RESISTOR_1_5K /*!< Battery charging resistor 1.5KOhm */
} hal_pwr_battery_charging_res_value_t;

/*! HAL PWR battery charging status enumeration definition */
typedef enum
{
  HAL_PWR_BATTERY_CHARGING_DISABLED = 0U, /*!< Battery charging disabled */
  HAL_PWR_BATTERY_CHARGING_ENABLED  = 1U  /*!< Battery charging enabled  */
} hal_pwr_battery_charging_status_t;

#if defined(PWR_UCPDR_UCPD_DBDIS)
/*! HAL PWR UCPD dead battery status enumeration definition */
typedef enum
{
  HAL_PWR_UCPD_DEAD_BATTERY_DISABLED = 0U, /*!< UCPD dead battery disabled */
  HAL_PWR_UCPD_DEAD_BATTERY_ENABLED  = 1U  /*!< UCPD dead battery enabled  */
} hal_pwr_ucpd_dead_battery_status_t;
#endif /* PWR_UCPDR_UCPD_DBDIS */

/*! HAL PWR gpio port enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_PORT_A = LL_PWR_GPIO_PORTA, /*!< GPIO port A */
  HAL_PWR_GPIO_PORT_B = LL_PWR_GPIO_PORTB, /*!< GPIO port B */
  HAL_PWR_GPIO_PORT_C = LL_PWR_GPIO_PORTC, /*!< GPIO port C */
  HAL_PWR_GPIO_PORT_D = LL_PWR_GPIO_PORTD, /*!< GPIO port D */
  HAL_PWR_GPIO_PORT_E = LL_PWR_GPIO_PORTE, /*!< GPIO port E */
#if defined (PWR_PUCRF_PU0)
  HAL_PWR_GPIO_PORT_F = LL_PWR_GPIO_PORTF, /*!< GPIO port F */
#endif /* defined (PWR_PUCRF_PU0) */
  HAL_PWR_GPIO_PORT_G = LL_PWR_GPIO_PORTG, /*!< GPIO port G */
  HAL_PWR_GPIO_PORT_H = LL_PWR_GPIO_PORTH, /*!< GPIO port H */
#if defined (PWR_PUCRI_PU0)
  HAL_PWR_GPIO_PORT_I = LL_PWR_GPIO_PORTI, /*!< GPIO port I */
#endif /* defined (PWR_PUCRI_PU0) */
#if defined (PWR_PUCRJ_PU0)
  HAL_PWR_GPIO_PORT_J = LL_PWR_GPIO_PORTJ  /*!< GPIO port J */
#endif /* defined (PWR_PUCRJ_PU0) */
} hal_pwr_gpio_port_t;

/*! HAL PWR gpio pull enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_NOPULL   = 0U, /*!< GPIO no pull   */
  HAL_PWR_GPIO_PULLUP   = 1U, /*!< GPIO pull up   */
  HAL_PWR_GPIO_PULLDOWN = 2U  /*!< GPIO pull down */
} hal_pwr_gpio_pull_t;

/*! HAL PWR gpio pull configuration status enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_CONFIG_NOT_APPLIED = 0U, /*!< GPIO pull configuration not applied */
  HAL_PWR_GPIO_CONFIG_APPLIED     = 1U /*!< GPIO pull configuration applied     */
} hal_pwr_gpio_pull_config_status_t;
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_wakeup_pin PWR wakeup pin definition
  * @{
  */
#define HAL_PWR_WAKEUP_PIN_1   LL_PWR_WAKEUP_PIN1    /*!< Wakeup pin 1   */
#define HAL_PWR_WAKEUP_PIN_2   LL_PWR_WAKEUP_PIN2    /*!< Wakeup pin 2   */
#define HAL_PWR_WAKEUP_PIN_3   LL_PWR_WAKEUP_PIN3    /*!< Wakeup pin 3   */
#define HAL_PWR_WAKEUP_PIN_4   LL_PWR_WAKEUP_PIN4    /*!< Wakeup pin 4   */
#define HAL_PWR_WAKEUP_PIN_5   LL_PWR_WAKEUP_PIN5    /*!< Wakeup pin 5   */
#define HAL_PWR_WAKEUP_PIN_6   LL_PWR_WAKEUP_PIN6    /*!< Wakeup pin 6   */
#define HAL_PWR_WAKEUP_PIN_7   LL_PWR_WAKEUP_PIN7    /*!< Wakeup pin 7   */
#define HAL_PWR_WAKEUP_PIN_8   LL_PWR_WAKEUP_PIN8    /*!< Wakeup pin 8   */
#define HAL_PWR_WAKEUP_PIN_ALL LL_PWR_WAKEUP_PIN_ALL /*!< Wakeup pin all */
/**
  * @}
  */

/** @defgroup PWR_voltage_monitor PWR voltage monitor definition
  * @{
  */
#define HAL_PWR_VDD_ANALOG_MONITOR_1     LL_PWR_ANALOG_VOLTAGE_MONITOR_1 /*!< VDDA voltage monitor versus 1.6 V   */
#define HAL_PWR_VDD_ANALOG_MONITOR_2     LL_PWR_ANALOG_VOLTAGE_MONITOR_2 /*!< VDDA voltage monitor versus 1.8 V   */
/**
  * @}
  */

/** @defgroup PWR_memory_fast_wakeup PWR memory fast wakeup definition
  * @{
  */
#define HAL_PWR_FLASH_STOP01_FAST_WAKEUP  LL_PWR_FLASHFWU    /*!< FLASH fast wakeup        */
#define HAL_PWR_SRAM4_STOP012_FAST_WAKEUP LL_PWR_SRAM4FWU    /*!< SRAM4 fast wakeup        */
#define HAL_PWR_MEMORIES_FAST_WAKEUP_ALL  LL_PWR_MEMORIESFWU /*!< All memories fast wakeup */
/**
  * @}
  */

/** @defgroup PWR_gpio_pin PWR gpio pin definition
  * @{
  */
#define HAL_PWR_GPIO_PIN_0   LL_PWR_GPIO_PIN_0  /*!< GPIO pin 0   */
#define HAL_PWR_GPIO_PIN_1   LL_PWR_GPIO_PIN_1  /*!< GPIO pin 1   */
#define HAL_PWR_GPIO_PIN_2   LL_PWR_GPIO_PIN_2  /*!< GPIO pin 2   */
#define HAL_PWR_GPIO_PIN_3   LL_PWR_GPIO_PIN_3  /*!< GPIO pin 3   */
#define HAL_PWR_GPIO_PIN_4   LL_PWR_GPIO_PIN_4  /*!< GPIO pin 4   */
#define HAL_PWR_GPIO_PIN_5   LL_PWR_GPIO_PIN_5  /*!< GPIO pin 5   */
#define HAL_PWR_GPIO_PIN_6   LL_PWR_GPIO_PIN_6  /*!< GPIO pin 6   */
#define HAL_PWR_GPIO_PIN_7   LL_PWR_GPIO_PIN_7  /*!< GPIO pin 7   */
#define HAL_PWR_GPIO_PIN_8   LL_PWR_GPIO_PIN_8  /*!< GPIO pin 8   */
#define HAL_PWR_GPIO_PIN_9   LL_PWR_GPIO_PIN_9  /*!< GPIO pin 9   */
#define HAL_PWR_GPIO_PIN_10  LL_PWR_GPIO_PIN_10 /*!< GPIO pin 10  */
#define HAL_PWR_GPIO_PIN_11  LL_PWR_GPIO_PIN_11 /*!< GPIO pin 11  */
#define HAL_PWR_GPIO_PIN_12  LL_PWR_GPIO_PIN_12 /*!< GPIO pin 12  */
#define HAL_PWR_GPIO_PIN_13  LL_PWR_GPIO_PIN_13 /*!< GPIO pin 13  */
#define HAL_PWR_GPIO_PIN_14  LL_PWR_GPIO_PIN_14 /*!< GPIO pin 14  */
#define HAL_PWR_GPIO_PIN_15  LL_PWR_GPIO_PIN_15 /*!< GPIO pin 15  */
#define HAL_PWR_GPIO_PIN_ALL 0xFFFFU            /*!< GPIO pin all */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Wakeup pins management functions
  * @{
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config);
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config);
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin);
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin);
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 RTC domain write protection management functions
  * @{
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void);
void HAL_PWR_DisableRTCDomainWriteProtection(void);
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group3 Main regulator management functions
  * @{
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range);
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void);
hal_status_t HAL_PWR_SetMainRegulatorSupply(hal_pwr_main_regulator_supply_t regulator);
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void);

void HAL_PWR_SetMainRegulatorStartupMode(hal_pwr_main_regulator_fast_startup_mode_t mode);
hal_pwr_main_regulator_fast_startup_mode_t HAL_PWR_GetMainRegulatorStartupMode(void);

void HAL_PWR_SetAnalogIOSwitchSupply(hal_pwr_analog_io_switch_supply_t analog_switch_supply);
hal_pwr_analog_io_switch_supply_t HAL_PWR_GetAnalogIOSwitchSupply(void);

hal_status_t HAL_PWR_EnableVddUSBIndependentSupply(void);
void HAL_PWR_DisableVddUSBIndependentSupply(void);
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddUSBIndependentSupply(void);

hal_status_t HAL_PWR_EnableVddIO2IndependentSupply(void);
void HAL_PWR_DisableVddIO2IndependentSupply(void);
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddIO2IndependentSupply(void);

hal_status_t HAL_PWR_EnableVddAIndependentSupply(uint32_t monitor);
void HAL_PWR_DisableVddAIndependentSupply(void);
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddAIndependentSupply(void);

#if defined(PWR_VOSR_VDD11USBDIS)
hal_status_t HAL_PWR_EnableVdd11USBIndependentSupply(void);
void HAL_PWR_DisableVdd11USBIndependentSupply(void);
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVdd11USBIndependentSupply(void);
#endif /* PWR_VOSR_VDD11USBDIS */

#if defined(PWR_VOSR_USBPWREN)
hal_status_t HAL_PWR_EnableVddUSBHSTransceiverSupply(void);
void HAL_PWR_DisableVddUSBHSTransceiverSupply(void);
hal_pwr_independent_supply_status_t HAL_PWR_IsEnabledVddUSBHSTransceiverSupply(void);
#endif /* PWR_VOSR_USBPWREN */
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group4 Low power mode management functions
  * @{
  */
void HAL_PWR_ClearCorePendingEvent(void);
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry);
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode);
void HAL_PWR_EnterStandbyMode(void);
void HAL_PWR_EnterShutdownMode(void);
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode);
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void);
void HAL_PWR_EnableCoreSleepOnExit(void);
void HAL_PWR_DisableCoreSleepOnExit(void);
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void);
void HAL_PWR_EnableCoreSendEventOnPending(void);
void HAL_PWR_DisableCoreSendEventOnPending(void);
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void);
void HAL_PWR_LP_SetSmartRunDomainMode(hal_pwr_system_mode_srd_mode_t mode);
hal_pwr_system_mode_srd_mode_t HAL_PWR_LP_GetSmartRunDomainMode(void);
void HAL_PWR_LP_SetBrownoutResetMode(hal_pwr_brownout_reset_mode_t mode);
hal_pwr_brownout_reset_mode_t HAL_PWR_LP_GetBrownoutResetMode(void);
void HAL_PWR_Stop3Wakeup_IRQHandler(uint32_t wakeup_pin);
void HAL_PWR_Stop3WakeupCallback(uint32_t wakeup_pin);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group5 Voltage monitoring management functions
  * @{
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level);
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void);
void HAL_PWR_EnableProgrammableVoltageDetector(void);
void HAL_PWR_DisableProgrammableVoltageDetector(void);
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void);
void HAL_PWR_EnableVddUSBMonitor(void);
void HAL_PWR_DisableVddUSBMonitor(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddUSBMonitor(void);
void HAL_PWR_EnableVddIO2Monitor(void);
void HAL_PWR_DisableVddIO2Monitor(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddIO2Monitor(void);
void HAL_PWR_EnableVddAMonitor1(void);
void HAL_PWR_DisableVddAMonitor1(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddAMonitor1(void);
void HAL_PWR_EnableVddAMonitor2(void);
void HAL_PWR_DisableVddAMonitor2(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledVddAMonitor2(void);
void HAL_PWR_EnableTemperatureVbatMonitor(void);
void HAL_PWR_DisableTemperatureVbatMonitor(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVbatMonitor(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group6 Memory retention management functions
  * @{
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory);
void HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory);

void HAL_PWR_LP_EnableMemoryPageRetention(hal_pwr_memory_retention_t memory, uint32_t page_idx, uint32_t page_nbr);
void HAL_PWR_LP_DisableMemoryPageRetention(hal_pwr_memory_retention_t memory, uint32_t page_idx, uint32_t page_nbr);
hal_pwr_memory_page_retention_status_t HAL_PWR_LP_IsEnabledMemoryPageRetention(hal_pwr_memory_retention_t memory,
                                                                               uint32_t page_idx);
#if defined (PWR_UCPDR_UCPD_STDBY)
void HAL_PWR_LP_EnableUCPDRetention(void);
void HAL_PWR_LP_DisableUCPDRetention(void);
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void);
#endif /* PWR_UCPDR_UCPD_STDBY */

#if defined(PWR_CR1_FORCE_USBPWR)
void HAL_PWR_LP_EnableOTGHSPHYRetention(void);
void HAL_PWR_LP_DisableOTGHSPHYRetention(void);
hal_pwr_otghsphy_retention_status_t HAL_PWR_LP_IsEnabledOTGHSPHYRetention(void);
#endif /* PWR_CR1_FORCE_USBPWR */
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group7 Memories fast wake-up management functions
  * @{
  */
void HAL_PWR_LP_EnableMemoryFastWakeup(uint32_t memories);
void HAL_PWR_LP_DisableMemoryFastWakeup(uint32_t memories);
hal_pwr_memory_fast_wakeup_status_t HAL_PWR_LP_IsEnabledMemoryFastWakeup(uint32_t memory);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group8 Battery management functions
  * @{
  */
void HAL_PWR_SetConfigBatteryCharging(hal_pwr_battery_charging_res_value_t value);
hal_pwr_battery_charging_res_value_t HAL_PWR_GetConfigBatteryCharging(void);
void HAL_PWR_EnableBatteryCharging(void);
void HAL_PWR_DisableBatteryCharging(void);
hal_pwr_battery_charging_status_t HAL_PWR_IsEnabledBatteryCharging(void);

#if defined(PWR_UCPDR_UCPD_DBDIS)
void HAL_PWR_LP_EnableUCPDDeadBattery(void);
void HAL_PWR_LP_DisableUCPDDeadBattery(void);
hal_pwr_ucpd_dead_battery_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void);
#endif /* PWR_UCPDR_UCPD_DBDIS */
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group9 I/O Pull management functions
  * @{
  */
void HAL_PWR_SetConfigGPIOPull(hal_pwr_gpio_port_t port, uint32_t pin, hal_pwr_gpio_pull_t pull);
hal_pwr_gpio_pull_t HAL_PWR_GetConfigGPIOPull(hal_pwr_gpio_port_t port, uint32_t pin);
void HAL_PWR_EnableGPIOPull(void);
void HAL_PWR_DisableGPIOPull(void);
hal_pwr_gpio_pull_config_status_t HAL_PWR_IsEnabledGPIOPull(void);
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

#endif /* STM32U5XX_HAL_PWR_H */
