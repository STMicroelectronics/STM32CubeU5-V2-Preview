/**
  ******************************************************************************
  * @file    stm32u5xx_hal_rcc.h
  * @brief   Header file of RCC HAL  module.
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
#ifndef STM32U5XX_HAL_RCC_H
#define STM32U5XX_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_rcc.h"
#include "stm32u5xx_ll_bus.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define HAL_RCC_RESET_FLAG_OBL   RCC_CSR_OBLRSTF    /*!< Option Byte Loader reset flag */
#define HAL_RCC_RESET_FLAG_PIN   RCC_CSR_PINRSTF    /*!< PIN reset flag */
#define HAL_RCC_RESET_FLAG_PWR   RCC_CSR_BORRSTF    /*!< BOR or POR/PDR reset flag */
#define HAL_RCC_RESET_FLAG_SW    RCC_CSR_SFTRSTF    /*!< Software Reset flag */
#define HAL_RCC_RESET_FLAG_IWDG  RCC_CSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define HAL_RCC_RESET_FLAG_WWDG  RCC_CSR_WWDGRSTF   /*!< Window watchdog reset flag */
#define HAL_RCC_RESET_FLAG_LPWR  RCC_CSR_LPWRRSTF   /*!< Low power reset flag */
#define HAL_RCC_RESET_FLAG_ALL   (HAL_RCC_RESET_FLAG_OBL | HAL_RCC_RESET_FLAG_PIN | HAL_RCC_RESET_FLAG_PWR |  \
                                  HAL_RCC_RESET_FLAG_SW | HAL_RCC_RESET_FLAG_IWDG | HAL_RCC_RESET_FLAG_WWDG | \
                                  HAL_RCC_RESET_FLAG_LPWR) /*!< Reset all the RCC flags */
/**
  * @}
  */

/**
  * @brief Default HSI trimming value
  * @{
  */
#define HAL_RCC_HSICALIBRATION_DEFAULT     0x10U /* Default HSI trimming value */
/**
  * @}
  */

/**
  * @brief Default MSI trimming value
  * @{
  */
#define HAL_RCC_MSICALIBRATION_DEFAULT     0x10U /*!< Default MSI trimming value */
/**
  * @}
  */

/**
  * @brief Peripheral clock activation status
  */
typedef enum
{
  HAL_RCC_CLK_DISABLED = 0,
  HAL_RCC_CLK_ENABLED = ! HAL_RCC_CLK_DISABLED
} hal_rcc_clk_status_t;

/**
  * @brief PLL activation status
  */
typedef enum
{
  HAL_RCC_PLL_DISABLED = 0,
  HAL_RCC_PLL_ENABLED = ! HAL_RCC_PLL_DISABLED
} hal_rcc_pll_status_t;

/**
  * @brief Oscillator Stop mode enable status.
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED_IN_STOP_MODE = 0,                                     /*!< Oscillator is enabled
                                                                                  for Run mode only    */
  HAL_RCC_OSC_ENABLED_IN_STOP_MODE  = ! HAL_RCC_OSC_DISABLED_IN_STOP_MODE,   /*!< Oscillator is enabled
                                                                                 for Run and Stop modes */
} hal_rcc_osc_stop_mode_status_t;

/**
  * @brief Oscillator ready status.
  */
typedef enum
{
  HAL_RCC_OSC_NOT_READY = 0,                             /*!< Oscillator is not ready */
  HAL_RCC_OSC_READY     = ! HAL_RCC_OSC_NOT_READY,       /*!< Oscillator is ready     */
} hal_rcc_osc_ready_status_t;

/**
  * @brief Oscillator enable status.
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED = 0,                               /*!< Oscillator is disabled   */
  HAL_RCC_OSC_ENABLED  = ! HAL_RCC_OSC_DISABLED,          /*!< Oscillator is enabled    */
} hal_rcc_osc_enable_status_t;

#if defined(HSE_VALUE)
/**
  * @brief HSE state
  */
typedef enum
{
  HAL_RCC_HSE_ON             = RCC_CR_HSEON,                                   /*!< HSE clock activation              */
  HAL_RCC_HSE_BYPASS         = (RCC_CR_HSEBYP | RCC_CR_HSEON),                 /*!< External Analog clock source for
                                                                                    HSE clock */
  HAL_RCC_HSE_BYPASS_DIGITAL = (RCC_CR_HSEEXT | RCC_CR_HSEBYP | RCC_CR_HSEON), /*!< External Digital clock source for
                                                                                    HSE clock      */
} hal_rcc_hse_t;
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/**
  * @brief LSE State
  */
typedef enum
{
  HAL_RCC_LSE_ON_RTC_ONLY     = RCC_BDCR_LSEON,                       /*!< LSE clock activation for RTC/TAMP/CSS only */
  HAL_RCC_LSE_ON              = (RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON), /*!< LSE clock activation for RTC/TAMP/CSS and
                                                                           peripherals                                */
  HAL_RCC_LSE_BYPASS_RTC_ONLY = (RCC_BDCR_LSEBYP | RCC_BDCR_LSEON),   /*!< External clock source for LSE clock used for
                                                                           RTC/TAMP/CSS only                          */
  HAL_RCC_LSE_BYPASS          = (RCC_BDCR_LSEBYP | RCC_BDCR_LSESYSEN | RCC_BDCR_LSEON), /*!< External clock source for
                                                                      LSE clock used for RTC/TAMP/CSS and peripherals */
} hal_rcc_lse_t;
#endif /* LSE_VALUE */

/**
  * @brief LSI Div
  */
typedef enum
{
  HAL_RCC_LSI_DIV1                  = LL_RCC_LSI_DIV_1,    /*!< LSI clock not divided    */
  HAL_RCC_LSI_DIV128                = LL_RCC_LSI_DIV_128,  /*!< LSI clock divided by 128 */
} hal_rcc_lsi_div_t;

/** @defgroup RCC_PLL1_Clock_Output  RCC PLL Clock Output
  * @{
  */
#define HAL_RCC_PLL1_OUTPUT_P  LL_RCC_PLL1_OUTPUT_P /*!< Output used by SDMMC1, SDMMC2, SAI1, SAI2, MDF1 and ADF1 */
#define HAL_RCC_PLL1_OUTPUT_Q  LL_RCC_PLL1_OUTPUT_Q /*!< Output used by ICLK, FDCAN, OCTOSPI1, OCTOSPI2, MDF1 and ADF1*/
#define HAL_RCC_PLL1_OUTPUT_R  LL_RCC_PLL1_OUTPUT_R /*!< Output used for system clock or MCO */
/*! All PLL1 outputs                                                                                 */
#define HAL_RCC_PLL1_OUTPUT_ALL (LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_R)

#define HAL_RCC_PLL1_SYSCLK   HAL_RCC_PLL1_OUTPUT_R    /*!< Define used for legacy purpose */
/**
  * @}
  */

/**
  * @brief PLLMBOOST EPOD Clock Divider
  */
typedef enum
{
  HAL_RCC_PLLMBOOST_DIV1          = LL_RCC_PLL1MBOOST_DIV_1,  /*!< PLL1CLK not divided   */
  HAL_RCC_PLLMBOOST_DIV2          = LL_RCC_PLL1MBOOST_DIV_2,  /*!< PLL1CLK divided by 2  */
  HAL_RCC_PLLMBOOST_DIV4          = LL_RCC_PLL1MBOOST_DIV_4,  /*!< PLL1CLK divided by 4  */
  HAL_RCC_PLLMBOOST_DIV6          = LL_RCC_PLL1MBOOST_DIV_6,  /*!< PLL1CLK divided by 6  */
  HAL_RCC_PLLMBOOST_DIV8          = LL_RCC_PLL1MBOOST_DIV_8,  /*!< PLL1CLK divided by 8  */
  HAL_RCC_PLLMBOOST_DIV10         = LL_RCC_PLL1MBOOST_DIV_10, /*!< PLL1CLK divided by 10 */
  HAL_RCC_PLLMBOOST_DIV12         = LL_RCC_PLL1MBOOST_DIV_12, /*!< PLL1CLK divided by 12 */
  HAL_RCC_PLLMBOOST_DIV14         = LL_RCC_PLL1MBOOST_DIV_14, /*!< PLL1CLK divided by 14 */
  HAL_RCC_PLLMBOOST_DIV16         = LL_RCC_PLL1MBOOST_DIV_16, /*!< PLL1CLK divided by 16 */
} hal_rcc_pll_mboost_div_t;

/**
  * @brief  RCC PLLx VCI Range
  */
typedef enum
{
  HAL_RCC_PLLVCI_RANGE_0 = LL_RCC_PLLINPUTRANGE_4_8,   /*!< PLLx input clock range frequency between 4 and 8 MHz  */
  HAL_RCC_PLLVCI_RANGE_1 = LL_RCC_PLLINPUTRANGE_8_16,  /*!< PLLx input clock range frequency between 8 and 16 MHz */
} hal_rcc_pll_vci_range_t;

/**
  * @brief  RCC PLL Clock Source
  */
typedef enum
{
  HAL_RCC_PLL_SRC_MSIS  = LL_RCC_PLL1SOURCE_MSIS, /*!< MSIS clock selected as main PLLx entry clock source */
  HAL_RCC_PLL_SRC_HSI   = LL_RCC_PLL1SOURCE_HSI,  /*!< HSI clock selected as main PLLx entry clock source  */
  HAL_RCC_PLL_SRC_HSE   = LL_RCC_PLL1SOURCE_HSE,  /*!< HSE clock selected as main PLLx entry clock source  */
} hal_rcc_pll_src_t;

/**
  * @brief MSIS Clock Range
  */
typedef enum
{
  HAL_RCC_MSIS_FREQ_48MHZ            = LL_RCC_MSISRANGE_0,  /*!< MSI = 48 MHz    (range 0)   */
  HAL_RCC_MSIS_FREQ_24MHZ            = LL_RCC_MSISRANGE_1,  /*!< MSI = 24 MHz    (range 1)   */
  HAL_RCC_MSIS_FREQ_16MHZ            = LL_RCC_MSISRANGE_2,  /*!< MSI = 16 MHz    (range 2)   */
  HAL_RCC_MSIS_FREQ_12MHZ            = LL_RCC_MSISRANGE_3,  /*!< MSI = 12 MHz    (range 3)   */
  HAL_RCC_MSIS_FREQ_4MHZ             = LL_RCC_MSISRANGE_4,  /*!< MSI = 4 MHz     (range 4)   */
  HAL_RCC_MSIS_FREQ_2MHZ             = LL_RCC_MSISRANGE_5,  /*!< MSI = 2 MHz     (range 5)   */
  HAL_RCC_MSIS_FREQ_1330KHZ          = LL_RCC_MSISRANGE_6,  /*!< MSI = 1.33 MHz  (range 6)   */
  HAL_RCC_MSIS_FREQ_1MHZ             = LL_RCC_MSISRANGE_7,  /*!< MSI = 1 MHz     (range 7)   */
  HAL_RCC_MSIS_FREQ_3072KHZ          = LL_RCC_MSISRANGE_8,  /*!< MSI = 3.072 MHz (range 8)   */
  HAL_RCC_MSIS_FREQ_1536KHZ          = LL_RCC_MSISRANGE_9,  /*!< MSI = 1.536 MHz (range 9)   */
  HAL_RCC_MSIS_FREQ_1024KHZ          = LL_RCC_MSISRANGE_10, /*!< MSI = 1.024 MHz (range 10)  */
  HAL_RCC_MSIS_FREQ_768KHZ           = LL_RCC_MSISRANGE_11, /*!< MSI = 768 kHz   (range 11)  */
  HAL_RCC_MSIS_FREQ_400KHZ           = LL_RCC_MSISRANGE_12, /*!< MSI = 400 kHz   (range 12)  */
  HAL_RCC_MSIS_FREQ_200KHZ           = LL_RCC_MSISRANGE_13, /*!< MSI = 200 kHz   (range 13)  */
  HAL_RCC_MSIS_FREQ_133KHZ           = LL_RCC_MSISRANGE_14, /*!< MSI = 133 kHz   (range 14)  */
  HAL_RCC_MSIS_FREQ_100KHZ           = LL_RCC_MSISRANGE_15, /*!< MSI = 100 kHz   (range 15)  */
} hal_rcc_msis_range_t;

/**
  * @brief MSIK Clock Range
  */
typedef enum
{
  HAL_RCC_MSIK_FREQ_48MHZ           = LL_RCC_MSIKRANGE_0,  /*!< MSIK = 48 MHz    (range 0)  */
  HAL_RCC_MSIK_FREQ_24MHZ           = LL_RCC_MSIKRANGE_1,  /*!< MSIK = 24 MHz    (range 1)  */
  HAL_RCC_MSIK_FREQ_16MHZ           = LL_RCC_MSIKRANGE_2,  /*!< MSIK = 16 MHz    (range 2)  */
  HAL_RCC_MSIK_FREQ_12MHZ           = LL_RCC_MSIKRANGE_3,  /*!< MSIK = 12 MHz    (range 3)  */
  HAL_RCC_MSIK_FREQ_4MHZ            = LL_RCC_MSIKRANGE_4,  /*!< MSIK = 4 MHz     (range 4)  */
  HAL_RCC_MSIK_FREQ_2MHZ            = LL_RCC_MSIKRANGE_5,  /*!< MSIK = 2 MHz     (range 5)  */
  HAL_RCC_MSIK_FREQ_1330KHZ         = LL_RCC_MSIKRANGE_6,  /*!< MSIK = 1.33 MHz  (range 6)  */
  HAL_RCC_MSIK_FREQ_1MHZ            = LL_RCC_MSIKRANGE_7,  /*!< MSIK = 1 MHz     (range 7)  */
  HAL_RCC_MSIK_FREQ_3072KHZ         = LL_RCC_MSIKRANGE_8,  /*!< MSIK = 3.072 MHz (range 8)  */
  HAL_RCC_MSIK_FREQ_1536KHZ         = LL_RCC_MSIKRANGE_9,  /*!< MSIK = 1.536 MHz (range 9)  */
  HAL_RCC_MSIK_FREQ_1024KHZ         = LL_RCC_MSIKRANGE_10, /*!< MSIK = 1.024 MHz (range 10) */
  HAL_RCC_MSIK_FREQ_768KHZ          = LL_RCC_MSIKRANGE_11, /*!< MSIK = 768 kHz   (range 11) */
  HAL_RCC_MSIK_FREQ_400KHZ          = LL_RCC_MSIKRANGE_12, /*!< MSIK = 400 kHz   (range 12) */
  HAL_RCC_MSIK_FREQ_200KHZ          = LL_RCC_MSIKRANGE_13, /*!< MSIK = 200 kHz   (range 13) */
  HAL_RCC_MSIK_FREQ_133KHZ          = LL_RCC_MSIKRANGE_14, /*!< MSIK = 133 kHz   (range 14) */
  HAL_RCC_MSIK_FREQ_100KHZ          = LL_RCC_MSIKRANGE_15, /*!< MSIK = 100 kHz   (range 15) */
} hal_rcc_msik_range_t;

/**
  * @brief MSIS/MSIK Clock Range for calibration
  */
typedef enum
{
  HAL_RCC_MSI_RANGE_CALIB_0_TO_3   = LL_RCC_MSI_OSCILLATOR_0,  /*!< MSI clock trimming for ranges 0 to 3   */
  HAL_RCC_MSI_RANGE_CALIB_4_TO_7   = LL_RCC_MSI_OSCILLATOR_1,  /*!< MSI clock trimming for ranges 4 to 7   */
  HAL_RCC_MSI_RANGE_CALIB_8_TO_11  = LL_RCC_MSI_OSCILLATOR_2,  /*!< MSI clock trimming for ranges 8 to 11  */
  HAL_RCC_MSI_RANGE_CALIB_12_TO_15 = LL_RCC_MSI_OSCILLATOR_3,  /*!< MSI clock trimming for ranges 12 to 15 */
} hal_rcc_msi_range_calib_t;

#if defined(LSE_VALUE)
/**
  * @brief MSI Pll Mode Selection (MSIK or MSIS).
  */
typedef enum
{
  HAL_RCC_MSI_PLL_MODE_SEL_MSIK       = LL_RCC_PLLMODE_MSIK,  /*!< PLL mode applied to MSIK (MSI kernel) clock output */
  HAL_RCC_MSI_PLL_MODE_SEL_MSIS       = LL_RCC_PLLMODE_MSIS,  /*!< PLL mode applied to MSIS (MSI system) clock output */
} hal_rcc_msi_pll_mode_sel_t;

/**
  * @brief MSI PLL mode fast startup activation
  */
typedef enum
{
  HAL_RCC_MSI_PLL_MODE_NORMAL = LL_RCC_PLLFAST_NORMAL, /*!< MSI PLL normal start-up    */
  HAL_RCC_MSI_PLL_MODE_FAST   = LL_RCC_PLLFAST_FAST,   /*!< MSI PLL fast start-up      */
} hal_rcc_msi_pll_mode_startup_t;
#endif /* LSE_VALUE*/

/**
  * @brief MSI bias mode selection
  */
typedef enum
{
  /** MSI bias continuous mode (clock accuracy fast settling time) */
  HAL_RCC_MSI_BIAS_MODE_CONTINUOUS = LL_RCC_MSIBIASMODE_CONTINUOUS,
  /** MSI bias sampling mode (ultra-low-power mode) */
  HAL_RCC_MSI_BIAS_MODE_SAMPLING   = LL_RCC_MSIBIASMODE_SAMPLING,
} hal_rcc_msi_bias_mode_t;

/**
  * @brief System Clock Source
  */
typedef enum
{
  HAL_RCC_SYSCLK_SRC_MSIS           = LL_RCC_SYS_CLKSOURCE_MSIS, /*!< MSIS selection as system clock  */
  HAL_RCC_SYSCLK_SRC_HSI            = LL_RCC_SYS_CLKSOURCE_HSI,  /*!< HSI selection as system clock   */
  HAL_RCC_SYSCLK_SRC_HSE            = LL_RCC_SYS_CLKSOURCE_HSE,  /*!< HSE selection as system clock   */
  HAL_RCC_SYSCLK_SRC_PLLCLK         = LL_RCC_SYS_CLKSOURCE_PLL1, /*!< PLL1 selection as system clock  */
} hal_rcc_sysclk_src_t;

/**
  * @brief SYSTICK Clock Source
  */
typedef enum
{
  HAL_RCC_SYSTICK_CLK_SRC_HCLKDIV8  = LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8,
  HAL_RCC_SYSTICK_CLK_SRC_LSI       = LL_RCC_SYSTICK_CLKSOURCE_LSI,
  HAL_RCC_SYSTICK_CLK_SRC_LSE       = LL_RCC_SYSTICK_CLKSOURCE_LSE,
} hal_rcc_systick_clk_src_t;

/**
  * @brief AHB Clock Source
  */
typedef enum
{
  HAL_RCC_HCLK_PRESCALER1               = LL_RCC_HCLK_PRESCALER_1,   /*!< SYSCLK not divided    */
  HAL_RCC_HCLK_PRESCALER2               = LL_RCC_HCLK_PRESCALER_2,   /*!< SYSCLK divided by 2   */
  HAL_RCC_HCLK_PRESCALER4               = LL_RCC_HCLK_PRESCALER_4,   /*!< SYSCLK divided by 4   */
  HAL_RCC_HCLK_PRESCALER8               = LL_RCC_HCLK_PRESCALER_8,   /*!< SYSCLK divided by 8   */
  HAL_RCC_HCLK_PRESCALER16              = LL_RCC_HCLK_PRESCALER_16,  /*!< SYSCLK divided by 16  */
  HAL_RCC_HCLK_PRESCALER64              = LL_RCC_HCLK_PRESCALER_64,  /*!< SYSCLK divided by 64  */
  HAL_RCC_HCLK_PRESCALER128             = LL_RCC_HCLK_PRESCALER_128, /*!< SYSCLK divided by 128 */
  HAL_RCC_HCLK_PRESCALER256             = LL_RCC_HCLK_PRESCALER_256, /*!< SYSCLK divided by 256 */
  HAL_RCC_HCLK_PRESCALER512             = LL_RCC_HCLK_PRESCALER_512, /*!< SYSCLK divided by 512 */
} hal_rcc_hclk_prescaler_t;

/**
  * @brief APB1 APB2 APB3 Clock Source
  */
typedef enum
{
  HAL_RCC_PCLK_PRESCALER1                 = LL_RCC_APB1_PRESCALER_1,  /*!< HCLK not divided   */
  HAL_RCC_PCLK_PRESCALER2                 = LL_RCC_APB1_PRESCALER_2,  /*!< HCLK divided by 2  */
  HAL_RCC_PCLK_PRESCALER4                 = LL_RCC_APB1_PRESCALER_4,  /*!< HCLK divided by 4  */
  HAL_RCC_PCLK_PRESCALER8                 = LL_RCC_APB1_PRESCALER_8,  /*!< HCLK divided by 8  */
  HAL_RCC_PCLK_PRESCALER16                = LL_RCC_APB1_PRESCALER_16, /*!< HCLK divided by 16 */
} hal_rcc_pclk_prescaler_t;

/**
  * @brief RTC Clock Source
  */
typedef enum
{
  HAL_RCC_RTC_CLK_SRC_NO_CLK       = LL_RCC_RTC_CLKSOURCE_NONE,   /*!< No clock used as RTC clock                 */
  HAL_RCC_RTC_CLK_SRC_LSE          = LL_RCC_RTC_CLKSOURCE_LSE,    /*!< LSE oscillator clock used as RTC clock     */
  HAL_RCC_RTC_CLK_SRC_LSI          = LL_RCC_RTC_CLKSOURCE_LSI,    /*!< LSI oscillator clock used as RTC clock     */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV32    = LL_RCC_RTC_CLKSOURCE_HSE_DIV32, /*!< HSE oscillator clock divided by 32 used as
                                                                           RTC clock */
} hal_rcc_rtc_clk_src_t;

/**
  * @brief MCO Clock Source
  */
typedef enum
{
  HAL_RCC_MCO_SRC_NOCLOCK        = LL_RCC_MCO1SOURCE_NOCLOCK, /*!< MCO output disabled, no clock on MCO */
  HAL_RCC_MCO_SRC_SYSCLK         = LL_RCC_MCO1SOURCE_SYSCLK,  /*!< SYSCLK selection as MCO source */
  HAL_RCC_MCO_SRC_MSI            = LL_RCC_MCO1SOURCE_MSIS,    /*!< MSI selection as MCO source */
  HAL_RCC_MCO_SRC_HSI            = LL_RCC_MCO1SOURCE_HSI,     /*!< HSI selection as MCO source */
  HAL_RCC_MCO_SRC_HSE            = LL_RCC_MCO1SOURCE_HSE,     /*!< HSE selection as MCO source */
  HAL_RCC_MCO_SRC_PLL1CLK        = LL_RCC_MCO1SOURCE_PLLCLK,  /*!< PLL1CLK selection as MCO source */
  HAL_RCC_MCO_SRC_LSI            = LL_RCC_MCO1SOURCE_LSI,     /*!< LSI selection as MCO source */
  HAL_RCC_MCO_SRC_LSE            = LL_RCC_MCO1SOURCE_LSE,     /*!< LSE selection as MCO source */
  HAL_RCC_MCO_SRC_HSI48          = LL_RCC_MCO1SOURCE_HSI48,   /*!< HSI48 selection as MCO source */
  HAL_RCC_MCO_SRC_MSIK           = LL_RCC_MCO1SOURCE_MSIK,    /*!< MSIK selection as MCO source */
} hal_rcc_mco_src_t;

/**
  * @brief MCO Clock Prescaler
  */
typedef enum
{
  HAL_RCC_MCO_PRESCALER1                  = LL_RCC_MCO1_PRESCALER_1,  /*!< MCO clock divided by 1 */
  HAL_RCC_MCO_PRESCALER2                  = LL_RCC_MCO1_PRESCALER_2,  /*!< MCO clock divided by 2 */
  HAL_RCC_MCO_PRESCALER4                  = LL_RCC_MCO1_PRESCALER_4,  /*!< MCO clock divided by 4 */
  HAL_RCC_MCO_PRESCALER8                  = LL_RCC_MCO1_PRESCALER_8,  /*!< MCO clock divided by 8 */
  HAL_RCC_MCO_PRESCALER16                 = LL_RCC_MCO1_PRESCALER_16, /*!< MCO clock divided by 16 */
} hal_rcc_mco_prescaler_t;

#if defined(LSE_VALUE)
/**
  * @brief LSE Drive Config
  */
typedef enum
{
  HAL_RCC_LSE_DRIVE_LOW                = LL_RCC_LSEDRIVE_LOW,        /*!< LSE low drive capability         */
  HAL_RCC_LSE_DRIVE_MEDIUMLOW          = LL_RCC_LSEDRIVE_MEDIUMLOW,  /*!< LSE medium low drive capability  */
  HAL_RCC_LSE_DRIVE_MEDIUMHIGH         = LL_RCC_LSEDRIVE_MEDIUMHIGH, /*!< LSE medium high drive capability */
  HAL_RCC_LSE_DRIVE_HIGH               = LL_RCC_LSEDRIVE_HIGH,       /*!< LSE high drive capability        */
} hal_rcc_lse_drive_t;

/**
  * @brief LSE clock glitch filter
  */
typedef enum
{
  HAL_RCC_LSE_GLITCH_FILTER_DISABLE   = 0U,               /*!< LSE glitch filter disabled         */
  HAL_RCC_LSE_GLITCH_FILTER_ENABLE    = RCC_BDCR_LSEGFON, /*!< LSE glitch filter enabled          */
} hal_rcc_lse_glitch_filter_t;
#endif /* LSE_VALUE*/

/**
  * @brief Wake-Up from STOP Clock
  */
typedef enum
{
  HAL_RCC_STOP_WAKEUPCLOCK_MSI      = LL_RCC_STOP_WAKEUPCLOCK_MSIS, /*!< MSI selection after wake-up from STOP */
  HAL_RCC_STOP_WAKEUPCLOCK_HSI      = LL_RCC_STOP_WAKEUPCLOCK_HSI,  /*!< HSI selection after wake-up from STOP */
} hal_rcc_stop_wakeup_clk_t;

/**
  * @brief  RCC Stop KernelWakeUpClock
  */
typedef enum
{
  HAL_RCC_STOP_KERWAKEUPCLOCK_MSI   = LL_RCC_STOP_WAKEUPKERCLOCK_MSIK, /*!< MSI kernel clock selection after wake-up
                                                                            from STOP */
  HAL_RCC_STOP_KERWAKEUPCLOCK_HSI   = LL_RCC_STOP_WAKEUPKERCLOCK_HSI,  /*!< HSI kernel clock selection after wake-up
                                                                            from STOP */
} hal_rcc_stop_wakeup_kerclk_t;

/**
  * @brief Low Speed Clock Source
  */
typedef enum
{
  HAL_RCC_LSCO_SRC_LSI            = LL_RCC_LSCO_CLKSOURCE_LSI,      /*!< LSI selection for low speed clock output */
  HAL_RCC_LSCO_SRC_LSE            = LL_RCC_LSCO_CLKSOURCE_LSE,      /*!< LSE selection for low speed clock output */
} hal_rcc_lsco_src_t;

/** @defgroup RCC_PLL2_Clock_Output  RCC PLL2 Clock Output
  * @{
  */
#define HAL_RCC_PLL2_OUTPUT_P                LL_RCC_PLL2_OUTPUT_P /*!< Output used for ADC1, ADC4 and DAC1          */
#define HAL_RCC_PLL2_OUTPUT_Q                LL_RCC_PLL2_OUTPUT_Q /*!< Output used for ICLK, OCTOSPI1, OCTOSPI2     */
#define HAL_RCC_PLL2_OUTPUT_R                LL_RCC_PLL2_OUTPUT_R /*!< Output used for FDCAN, SAI1, SAI2 and DAC1  */
#define HAL_RCC_PLL2_OUTPUT_ALL              (LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R)
/*!< All PLL2 output                              */
/**
  * @}
  */

/** @defgroup RCC_PLL3_Clock_Output  RCC PLL3 Clock Output
  * @{
  */
#define HAL_RCC_PLL3_OUTPUT_P                LL_RCC_PLL3_OUTPUT_P  /*!< Output used for SAI1, SAI2 */
#define HAL_RCC_PLL3_OUTPUT_Q                LL_RCC_PLL3_OUTPUT_Q  /*!< Output used for ADF1 and MDF1 */
#define HAL_RCC_PLL3_OUTPUT_R                LL_RCC_PLL3_OUTPUT_R  /*!< No output */
#define HAL_RCC_PLL3_OUTPUT_ALL              (LL_RCC_PLL3_OUTPUT_P | LL_RCC_PLL3_OUTPUT_Q | LL_RCC_PLL3_OUTPUT_R)
/*!< All PLL2 output                              */
/**
  * @}
  */

/**
  * @brief USART1 Clock Source
  */
typedef enum
{
  HAL_RCC_USART1_CLK_SRC_PCLK2     = LL_RCC_USART1_CLKSOURCE_PCLK2,
  HAL_RCC_USART1_CLK_SRC_SYSCLK    = LL_RCC_USART1_CLKSOURCE_SYSCLK,
  HAL_RCC_USART1_CLK_SRC_HSI       = LL_RCC_USART1_CLKSOURCE_HSI,
  HAL_RCC_USART1_CLK_SRC_LSE       = LL_RCC_USART1_CLKSOURCE_LSE,
} hal_rcc_usart1_clk_src_t;

#if defined (USART2)
/**
  * @brief USART2 Clock Source
  */
typedef enum
{
  HAL_RCC_USART2_CLK_SRC_PCLK1     = LL_RCC_USART2_CLKSOURCE_PCLK1,
  HAL_RCC_USART2_CLK_SRC_SYSCLK    = LL_RCC_USART2_CLKSOURCE_SYSCLK,
  HAL_RCC_USART2_CLK_SRC_HSI       = LL_RCC_USART2_CLKSOURCE_HSI,
  HAL_RCC_USART2_CLK_SRC_LSE       = LL_RCC_USART2_CLKSOURCE_LSE,
} hal_rcc_usart2_clk_src_t;
#endif /* defined (USART2) */

/**
  * @brief USART3 Clock Source
  */
typedef enum
{
  HAL_RCC_USART3_CLK_SRC_PCLK1     = LL_RCC_USART3_CLKSOURCE_PCLK1,
  HAL_RCC_USART3_CLK_SRC_SYSCLK    = LL_RCC_USART3_CLKSOURCE_SYSCLK,
  HAL_RCC_USART3_CLK_SRC_HSI       = LL_RCC_USART3_CLKSOURCE_HSI,
  HAL_RCC_USART3_CLK_SRC_LSE       = LL_RCC_USART3_CLKSOURCE_LSE,
} hal_rcc_usart3_clk_src_t;

/**
  * @brief UART4 Clock Source
  */
typedef enum
{
  HAL_RCC_UART4_CLK_SRC_PCLK1      = LL_RCC_UART4_CLKSOURCE_PCLK1,
  HAL_RCC_UART4_CLK_SRC_SYSCLK     = LL_RCC_UART4_CLKSOURCE_SYSCLK,
  HAL_RCC_UART4_CLK_SRC_HSI        = LL_RCC_UART4_CLKSOURCE_HSI,
  HAL_RCC_UART4_CLK_SRC_LSE        = LL_RCC_UART4_CLKSOURCE_LSE,
} hal_rcc_uart4_clk_src_t;

/**
  * @brief UART5 Clock Source
  */
typedef enum
{
  HAL_RCC_UART5_CLK_SRC_PCLK1      = LL_RCC_UART5_CLKSOURCE_PCLK1,
  HAL_RCC_UART5_CLK_SRC_SYSCLK     = LL_RCC_UART5_CLKSOURCE_SYSCLK,
  HAL_RCC_UART5_CLK_SRC_HSI        = LL_RCC_UART5_CLKSOURCE_HSI,
  HAL_RCC_UART5_CLK_SRC_LSE        = LL_RCC_UART5_CLKSOURCE_LSE,
} hal_rcc_uart5_clk_src_t;

#if defined(USART6)
/**
  * @brief USART6 Clock Source
  */
typedef enum
{
  HAL_RCC_USART6_CLK_SRC_PCLK1     = LL_RCC_USART6_CLKSOURCE_PCLK1,
  HAL_RCC_USART6_CLK_SRC_SYSCLK    = LL_RCC_USART6_CLKSOURCE_SYSCLK,
  HAL_RCC_USART6_CLK_SRC_HSI       = LL_RCC_USART6_CLKSOURCE_HSI,
  HAL_RCC_USART6_CLK_SRC_LSE       = LL_RCC_USART6_CLKSOURCE_LSE,
} hal_rcc_usart6_clk_src_t;
#endif /* USART6 */

/**
  * @brief LPUART1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPUART1_CLK_SRC_PCLK3    = LL_RCC_LPUART1_CLKSOURCE_PCLK3,
  HAL_RCC_LPUART1_CLK_SRC_SYSCLK   = LL_RCC_LPUART1_CLKSOURCE_SYSCLK,
  HAL_RCC_LPUART1_CLK_SRC_HSI      = LL_RCC_LPUART1_CLKSOURCE_HSI,
  HAL_RCC_LPUART1_CLK_SRC_LSE      = LL_RCC_LPUART1_CLKSOURCE_LSE,
  HAL_RCC_LPUART1_CLK_SRC_MSIK     = LL_RCC_LPUART1_CLKSOURCE_MSIK,
} hal_rcc_lpuart1_clk_src_t;

/**
  * @brief I2C1 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C1_CLK_SRC_PCLK1       = LL_RCC_I2C1_CLKSOURCE_PCLK1,
  HAL_RCC_I2C1_CLK_SRC_SYSCLK      = LL_RCC_I2C1_CLKSOURCE_SYSCLK,
  HAL_RCC_I2C1_CLK_SRC_HSI         = LL_RCC_I2C1_CLKSOURCE_HSI,
  HAL_RCC_I2C1_CLK_SRC_MSIK        = LL_RCC_I2C1_CLKSOURCE_MSIK,
} hal_rcc_i2c1_clk_src_t;

/**
  * @brief I2C2 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C2_CLK_SRC_PCLK1       = LL_RCC_I2C2_CLKSOURCE_PCLK1,
  HAL_RCC_I2C2_CLK_SRC_SYSCLK      = LL_RCC_I2C2_CLKSOURCE_SYSCLK,
  HAL_RCC_I2C2_CLK_SRC_HSI         = LL_RCC_I2C2_CLKSOURCE_HSI,
  HAL_RCC_I2C2_CLK_SRC_MSIK        = LL_RCC_I2C2_CLKSOURCE_MSIK,
} hal_rcc_i2c2_clk_src_t;

/**
  * @brief I2C3 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C3_CLK_SRC_PCLK3       = LL_RCC_I2C3_CLKSOURCE_PCLK3,
  HAL_RCC_I2C3_CLK_SRC_SYSCLK      = LL_RCC_I2C3_CLKSOURCE_SYSCLK,
  HAL_RCC_I2C3_CLK_SRC_HSI         = LL_RCC_I2C3_CLKSOURCE_HSI,
  HAL_RCC_I2C3_CLK_SRC_MSIK        = LL_RCC_I2C3_CLKSOURCE_MSIK,
} hal_rcc_i2c3_clk_src_t;

/**
  * @brief I2C4 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C4_CLK_SRC_PCLK1       = LL_RCC_I2C4_CLKSOURCE_PCLK1,
  HAL_RCC_I2C4_CLK_SRC_SYSCLK      = LL_RCC_I2C4_CLKSOURCE_SYSCLK,
  HAL_RCC_I2C4_CLK_SRC_HSI         = LL_RCC_I2C4_CLKSOURCE_HSI,
  HAL_RCC_I2C4_CLK_SRC_MSIK        = LL_RCC_I2C4_CLKSOURCE_MSIK,
} hal_rcc_i2c4_clk_src_t;

#if defined(I2C5)
/**
  * @brief I2C5 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C5_CLK_SRC_PCLK1       = LL_RCC_I2C5_CLKSOURCE_PCLK1,
  HAL_RCC_I2C5_CLK_SRC_SYSCLK      = LL_RCC_I2C5_CLKSOURCE_SYSCLK,
  HAL_RCC_I2C5_CLK_SRC_HSI         = LL_RCC_I2C5_CLKSOURCE_HSI,
  HAL_RCC_I2C5_CLK_SRC_MSIK        = LL_RCC_I2C5_CLKSOURCE_MSIK,
} hal_rcc_i2c5_clk_src_t;
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @brief I2C6 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C6_CLK_SRC_PCLK1       = LL_RCC_I2C6_CLKSOURCE_PCLK1,
  HAL_RCC_I2C6_CLK_SRC_SYSCLK      = LL_RCC_I2C6_CLKSOURCE_SYSCLK,
  HAL_RCC_I2C6_CLK_SRC_HSI         = LL_RCC_I2C6_CLKSOURCE_HSI,
  HAL_RCC_I2C6_CLK_SRC_MSIK        = LL_RCC_I2C6_CLKSOURCE_MSIK,
} hal_rcc_i2c6_clk_src_t;
#endif /* I2C6 */

/**
  * @brief  RNG Clock Source
  */
typedef enum
{
  HAL_RCC_RNG_CLK_SRC_HSI48        = LL_RCC_RNG_CLKSOURCE_HSI48,
  HAL_RCC_RNG_CLK_SRC_HSI48_DIV2   = LL_RCC_RNG_CLKSOURCE_HSI48_DIV2,
  HAL_RCC_RNG_CLK_SRC_HSI          = LL_RCC_RNG_CLKSOURCE_HSI,
} hal_rcc_rng_clk_src_t;

#if defined(SAES)
/**
  * @brief SAES Clock Source
  */
typedef enum
{
  HAL_RCC_SAES_CLK_SRC_SHSI        = LL_RCC_SAES_CLKSOURCE_SHSI,
  HAL_RCC_SAES_CLK_SRC_SHSI_DIV2   = LL_RCC_SAES_CLKSOURCE_SHSI_DIV2,
} hal_rcc_saes_clk_src_t;
#endif /* SAES */

/**
  * @brief SPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI1_CLK_SRC_PCLK2       = LL_RCC_SPI1_CLKSOURCE_PCLK2,
  HAL_RCC_SPI1_CLK_SRC_SYSCLK      = LL_RCC_SPI1_CLKSOURCE_SYSCLK,
  HAL_RCC_SPI1_CLK_SRC_HSI         = LL_RCC_SPI1_CLKSOURCE_HSI,
  HAL_RCC_SPI1_CLK_SRC_MSIK        = LL_RCC_SPI1_CLKSOURCE_MSIK,
} hal_rcc_spi1_clk_src_t;

/**
  * @brief SPI2 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI2_CLK_SRC_PCLK1       = LL_RCC_SPI2_CLKSOURCE_PCLK1,
  HAL_RCC_SPI2_CLK_SRC_SYSCLK      = LL_RCC_SPI2_CLKSOURCE_SYSCLK,
  HAL_RCC_SPI2_CLK_SRC_HSI         = LL_RCC_SPI2_CLKSOURCE_HSI,
  HAL_RCC_SPI2_CLK_SRC_MSIK        = LL_RCC_SPI2_CLKSOURCE_MSIK,
} hal_rcc_spi2_clk_src_t;

/**
  * @brief SPI3 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI3_CLK_SRC_PCLK3       = LL_RCC_SPI3_CLKSOURCE_PCLK3,
  HAL_RCC_SPI3_CLK_SRC_SYSCLK      = LL_RCC_SPI3_CLKSOURCE_SYSCLK,
  HAL_RCC_SPI3_CLK_SRC_HSI         = LL_RCC_SPI3_CLKSOURCE_HSI,
  HAL_RCC_SPI3_CLK_SRC_MSIK        = LL_RCC_SPI3_CLKSOURCE_MSIK,
} hal_rcc_spi3_clk_src_t;

/**
  * @brief LPTIM34 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM34_CLK_SRC_MSIK      = LL_RCC_LPTIM34_CLKSOURCE_MSIK,
  HAL_RCC_LPTIM34_CLK_SRC_LSI       = LL_RCC_LPTIM34_CLKSOURCE_LSI,
  HAL_RCC_LPTIM34_CLK_SRC_HSI       = LL_RCC_LPTIM34_CLKSOURCE_HSI,
  HAL_RCC_LPTIM34_CLK_SRC_LSE       = LL_RCC_LPTIM34_CLKSOURCE_LSE,
} hal_rcc_lptim34_clk_src_t;

/**
  * @brief LPTIM1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM1_CLK_SRC_MSIK      = LL_RCC_LPTIM1_CLKSOURCE_MSIK,
  HAL_RCC_LPTIM1_CLK_SRC_LSI       = LL_RCC_LPTIM1_CLKSOURCE_LSI,
  HAL_RCC_LPTIM1_CLK_SRC_HSI       = LL_RCC_LPTIM1_CLKSOURCE_HSI,
  HAL_RCC_LPTIM1_CLK_SRC_LSE       = LL_RCC_LPTIM1_CLKSOURCE_LSE,
} hal_rcc_lptim1_clk_src_t;

/**
  * @brief LPTIM2 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM2_CLK_SRC_PCLK1     = LL_RCC_LPTIM2_CLKSOURCE_PCLK1,
  HAL_RCC_LPTIM2_CLK_SRC_LSI       = LL_RCC_LPTIM2_CLKSOURCE_LSI,
  HAL_RCC_LPTIM2_CLK_SRC_HSI       = LL_RCC_LPTIM2_CLKSOURCE_HSI,
  HAL_RCC_LPTIM2_CLK_SRC_LSE       = LL_RCC_LPTIM2_CLKSOURCE_LSE,
} hal_rcc_lptim2_clk_src_t;

/**
  * @brief FDCAN Kernel Clock Source
  */
typedef enum
{
  HAL_RCC_FDCAN_CLK_SRC_HSE        = LL_RCC_FDCAN_CLKSOURCE_HSE,
  HAL_RCC_FDCAN_CLK_SRC_PLL1Q      = LL_RCC_FDCAN_CLKSOURCE_PLL1,
  HAL_RCC_FDCAN_CLK_SRC_PLL2P      = LL_RCC_FDCAN_CLKSOURCE_PLL2,
} hal_rcc_fdcan_clk_src_t;

/**
  * @brief ICLK Clock Source
  */
typedef enum
{
  HAL_RCC_ICLK_CLK_SRC_HSI48       = LL_RCC_USB_CLKSOURCE_HSI48,
  HAL_RCC_ICLK_CLK_SRC_PLL2Q       = LL_RCC_USB_CLKSOURCE_PLL2,
  HAL_RCC_ICLK_CLK_SRC_PLL1Q       = LL_RCC_USB_CLKSOURCE_PLL1,
  HAL_RCC_ICLK_CLK_SRC_MSIK        = LL_RCC_USB_CLKSOURCE_MSIK,
} hal_rcc_iclk_clk_src_t;

/**
  * @brief ADC1 Clock Source
  */
typedef enum
{
  HAL_RCC_ADCDAC_CLK_SRC_HCLK         = LL_RCC_ADCDAC_CLKSOURCE_HCLK,
  HAL_RCC_ADCDAC_CLK_SRC_SYSCLK       = LL_RCC_ADCDAC_CLKSOURCE_SYSCLK,
  HAL_RCC_ADCDAC_CLK_SRC_PLL2R        = LL_RCC_ADCDAC_CLKSOURCE_PLL2,
  HAL_RCC_ADCDAC_CLK_SRC_HSE          = LL_RCC_ADCDAC_CLKSOURCE_HSE,
  HAL_RCC_ADCDAC_CLK_SRC_HSI          = LL_RCC_ADCDAC_CLKSOURCE_HSI,
  HAL_RCC_ADCDAC_CLK_SRC_MSIK         = LL_RCC_ADCDAC_CLKSOURCE_MSIK,
} hal_rcc_adcdac_clk_src_t;

/**
  * @brief MDF1 Clock Source
  */
typedef enum
{
  HAL_RCC_MDF1_CLK_SRC_HCLK      = LL_RCC_MDF1_CLKSOURCE_HCLK,
  HAL_RCC_MDF1_CLK_SRC_PLL1P     = LL_RCC_MDF1_CLKSOURCE_PLL1,
  HAL_RCC_MDF1_CLK_SRC_PLL3Q     = LL_RCC_MDF1_CLKSOURCE_PLL3,
  HAL_RCC_MDF1_CLK_SRC_PIN       = LL_RCC_MDF1_CLKSOURCE_PIN,
  HAL_RCC_MDF1_CLK_SRC_MSIK      = LL_RCC_MDF1_CLKSOURCE_MSIK,
} hal_rcc_mdf1_clk_src_t;

/**
  * @brief ADF1 Clock Source
  */
typedef enum
{
  HAL_RCC_ADF1_CLK_SRC_HCLK      = LL_RCC_ADF1_CLKSOURCE_HCLK,
  HAL_RCC_ADF1_CLK_SRC_PLL1P     = LL_RCC_ADF1_CLKSOURCE_PLL1,
  HAL_RCC_ADF1_CLK_SRC_PLL3Q     = LL_RCC_ADF1_CLKSOURCE_PLL3,
  HAL_RCC_ADF1_CLK_SRC_PIN       = LL_RCC_ADF1_CLKSOURCE_PIN,
  HAL_RCC_ADF1_CLK_SRC_MSIK      = LL_RCC_ADF1_CLKSOURCE_MSIK,
} hal_rcc_adf1_clk_src_t;

/**
  * @brief SAI1 Clock Source
  */
typedef enum
{
  HAL_RCC_SAI1_CLK_SRC_PLL2P      = LL_RCC_SAI1_CLKSOURCE_PLL2,
  HAL_RCC_SAI1_CLK_SRC_PLL3P      = LL_RCC_SAI1_CLKSOURCE_PLL3,
  HAL_RCC_SAI1_CLK_SRC_PLL1P      = LL_RCC_SAI1_CLKSOURCE_PLL1,
  HAL_RCC_SAI1_CLK_SRC_PIN        = LL_RCC_SAI1_CLKSOURCE_PIN,
  HAL_RCC_SAI1_CLK_SRC_HSI        = LL_RCC_SAI1_CLKSOURCE_HSI,
} hal_rcc_sai1_clk_src_t;

#if defined (SAI2)
/**
  * @brief SAI2 Clock Source
  */
typedef enum
{
  HAL_RCC_SAI2_CLK_SRC_PLL2P       = LL_RCC_SAI2_CLKSOURCE_PLL2,
  HAL_RCC_SAI2_CLK_SRC_PLL3P       = LL_RCC_SAI2_CLKSOURCE_PLL3,
  HAL_RCC_SAI2_CLK_SRC_PLL1P       = LL_RCC_SAI2_CLKSOURCE_PLL1,
  HAL_RCC_SAI2_CLK_SRC_PIN         = LL_RCC_SAI2_CLKSOURCE_PIN,
  HAL_RCC_SAI2_CLK_SRC_HSI         = LL_RCC_SAI2_CLKSOURCE_HSI,
} hal_rcc_sai2_clk_src_t;
#endif /* defined (SAI2) */

/**
  * @brief SDMMC1/2 Clock Source
  */
typedef enum
{
  HAL_RCC_SDMMC_CLK_SRC_CLK48    = LL_RCC_SDMMC12_KERCLKSOURCE_48CLK,
  HAL_RCC_SDMMC_CLK_SRC_PLL1P    = LL_RCC_SDMMC12_KERCLKSOURCE_PLL1,
} hal_rcc_sdmmc_clk_src_t;

/**
  * @brief OctoSPI Clock Source
  */
typedef enum
{
  HAL_RCC_OCTOSPI_CLK_SRC_SYSCLK    = LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK,
  HAL_RCC_OCTOSPI_CLK_SRC_MSIK      = LL_RCC_OCTOSPI_CLKSOURCE_MSIK,
  HAL_RCC_OCTOSPI_CLK_SRC_PLL1Q     = LL_RCC_OCTOSPI_CLKSOURCE_PLL1,
  HAL_RCC_OCTOSPI_CLK_SRC_PLL2Q     = LL_RCC_OCTOSPI_CLKSOURCE_PLL2,
} hal_rcc_octospi_clk_src_t;

#if defined(HSPI1)
/**
  * @brief HexaSPI Clock Source
  */
typedef enum
{
  HAL_RCC_HSPI1_CLK_SRC_SYSCLK    = LL_RCC_HSPI_CLKSOURCE_SYSCLK,
  HAL_RCC_HSPI1_CLK_SRC_PLL1Q     = LL_RCC_HSPI_CLKSOURCE_PLL1,
  HAL_RCC_HSPI1_CLK_SRC_PLL2Q     = LL_RCC_HSPI_CLKSOURCE_PLL2,
  HAL_RCC_HSPI1_CLK_SRC_PLL3R     = LL_RCC_HSPI_CLKSOURCE_PLL3,
} hal_rcc_hspi1_clk_src_t;
#endif /* HSPI1 */

/**
  * @brief DAC1 sample-and-hold clock source
  */
typedef enum
{
  HAL_RCC_DAC1_CLK_SRC_LSE      = LL_RCC_DAC1_CLKSOURCE_LSE,
  HAL_RCC_DAC1_CLK_SRC_LSI      = LL_RCC_DAC1_CLKSOURCE_LSI,
} hal_rcc_dac1_clk_src_t;

/**
  * @brief Clocks sources for TIM16,TIM17 and LPTIM2 internal input capture
  */
typedef enum
{
  /** No clock available for TIM16/TIM17 and LPTIM2 input capture */
  HAL_RCC_TIMIC_CLK_SRC_NONE      = LL_RCC_TIMIC_CLKSOURCE_NONE,
  /** HSI/256 selected for Timer16/17 and LPTIM2 input capture    */
  HAL_RCC_TIMIC_CLK_SRC_HSI_256   = LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256,
  /** MSIS/1024 selected for Timer16/17 and LPTIM2 input capture */
  HAL_RCC_TIMIC_CLK_SRC_MSIS_1024 = LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV1024,
  /** MSIS/4 selected for Timer16/17 and LPTIM2 input capture    */
  HAL_RCC_TIMIC_CLK_SRC_MSIS_4    = LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV4,
  /** MSIK/1024 selected for Timer16/17 and LPTIM2 input capture */
  HAL_RCC_TIMIC_CLK_SRC_MSIK_4    = LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV4,
  /** MSIK/4 selected for Timer16/17 and LPTIM2 input capture    */
  HAL_RCC_TIMIC_CLK_SRC_MSIK_1024 = LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV1024,
} hal_rcc_timic_clk_src_t;

#if defined(LTDC)
/**
  * @brief LTDC Clock Source
  */
typedef enum
{
  /** PLL3 divider R clock selected as LTDC kernel clock */
  HAL_RCC_LTDC_CLK_SRC_PLL3R = LL_RCC_LTDC_CLKSOURCE_PLL3,
  /** PLL2 divider R clock selected as LTDC kernel clock */
  HAL_RCC_LTDC_CLK_SRC_PLL2R = LL_RCC_LTDC_CLKSOURCE_PLL2,
} hal_rcc_ltdc_clk_src_t;
#endif /* LTDC */

#if defined(DSI)
/**
  * @brief DSI Clock Source
  */
typedef enum
{
  HAL_RCC_DSI_CLK_SRC_DSIPHY = LL_RCC_DSI_CLKSOURCE_PHY,   /*!< DSI-PHY is selected as DSI byte lane clock
                                                                 (usual case) */
  HAL_RCC_DSI_CLK_SRC_PLL3   = LL_RCC_DSI_CLKSOURCE_PLL3,  /*!< PLL3 divider P clock selected as DSI byte lane clock
                                                                 (low power case) */
} hal_rcc_dsi_clk_src_t;
#endif /* DSI */

#if defined(USB_OTG_HS)
/**
  * @brief USB HS PHY Clock Source
  */
typedef enum
{
  /** HSE clock selected as USB HS PHY                                     */
  HAL_RCC_USBHSPHY_CLK_SRC_HSE        = LL_RCC_USBHSPHYCLKSOURCE_HSE,
  /** HSE clock div by 2 selected as USB HS PHY                            */
  HAL_RCC_USBHSPHY_CLK_SRC_HSE_DIV2   = LL_RCC_USBHSPHYCLKSOURCE_HSE_DIV2,
  /** PLL1 div P selected as USB HS PHY                                  */
  HAL_RCC_USBHSPHY_CLK_SRC_PLL1P      = LL_RCC_USBHSPHYCLKSOURCE_PLL1,
  /** PLL1 div P divided by 2 selected as USB HS PHY                     */
  HAL_RCC_USBHSPHY_CLK_SRC_PLL1P_DIV2 = LL_RCC_USBHSPHYCLKSOURCE_PLL1_DIV2,
} hal_rcc_usbhsphy_clk_src_t;
#endif /* USB_OTG_HS */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC PLL configuration structure definition
  * @note   VCO range is being calculated automatically in PLL configurations functions.
  */
typedef struct
{
  uint16_t pll_n;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 4 and Max_Data = 512   */

  uint16_t pll_fracn;   /*!< PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
                            PLL1 VCO It must be a value between 0 and 32767                           */

  uint8_t pll_m;       /*!< PLLM: Division factor for PLL VCO input clock.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 16    */

  uint8_t pll_p;       /*!< PLLP: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint8_t pll_q;       /*!< PLLQ: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 128   */

  uint8_t pll_r;       /*!< PLLR: Division factor for system clock.
                            This parameter must be a number between Min_Data = 2 and Max_Data = 128
                            For PLL1R, only division by 1 and even division factors are allowed.
                            (no such restiction in PLL2R and PLL3R)                                   */

  hal_rcc_pll_mboost_div_t pll_m_boost;  /*!< PLLMBOOST: Prescaler for EPOD booster input clock.
                                              This parameter is valid only for PLL1 (ignore for PLL2 and PLL3)*/

  hal_rcc_pll_src_t pll_source;        /*!< RCC_PLLSource: PLL entry clock source                     */

} hal_rcc_pll_config_t;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  hal_rcc_hclk_prescaler_t hclk_prescaler; /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock
                                           (SYSCLK).                  */

  hal_rcc_pclk_prescaler_t pclk1_prescaler;  /*!< The APB1 clock (PCLK1) divider.
                                             This clock is derived from the AHB clock (HCLK).       */

  hal_rcc_pclk_prescaler_t pclk2_prescaler;  /*!< The APB2 clock (PCLK2) divider.
                                             This clock is derived from the AHB clock (HCLK).       */

  hal_rcc_pclk_prescaler_t pclk3_prescaler;  /*!< The APB3 clock (PCLK3) divider.
                                            This clock is derived from the AHB clock (HCLK).       */
} hal_rcc_bus_clk_config_t;

/**
  * @brief  RCC PLL Clocks structure definition
  */
typedef struct
{
  uint32_t pll_p_freq; /*!< PLLx outputP frequency */
  uint32_t pll_q_freq; /*!< PLLx outputQ frequency */
  uint32_t pll_r_freq; /*!< PLLx outputR frequency */
} hal_rcc_pll_output_freq_t;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  *
  */

/** @defgroup RCC_Exported_Functions_Group1 Oscillators, PLLs, bus configurations and system clock reset functions
  This section provides functions allowing to configure the internal and external oscillators
  (HSE, HSI, LSE, MSIS, MSIK, LSI, PLL), CSS, MCO and the System busses clocks (SYSCLK, AHB, APB1, APB2
  and APB3).

  - Internal/external clock and PLL configuration:

    - HSI (High-Speed Internal): 16 MHz factory-trimmed RC used directly or through
    the PLL as System clock source and also used for peripherals as kernel clock.

    - MSIS (Multiple Speed Internal System): MSIS configurable to several ranges, selecting automatically by hw
    corresponding RC and these RC are trimmable.
    The MSIS is used as System clock source or input from different PLLs.

    - MSIK (Multiple Speed Internal Kernel): MSIK configurable to several ranges, selecting automatically by hw
    corresponding RC and these RC are trimmable.
    It can be selected by some peripherals as kernel clock.

    - SW or HW MSI calibration

    - LSI (Low-Speed Internal): 32 kHz (or 250 Hz depending on the LSIPREDIV bit) low consumption RC used as IWDG
    and/or RTC clock source. It can be selected by some peripherals as kernel clock.

    - HSE (High-Speed External): crystal or clock, from 4 to 50 MHz, used directly or
    through the PLL as System clock source. Can be used also optionally as RTC clock source.

    - LSE (low-speed external): 32.768 kHz oscillator used optionally as RTC clock source.

    - PLL1 providing up to three independent output clocks:

      - as main PLL, PLL1, that is generally used to provide clocks to the CPU and to some
      peripherals

    - PLL2 & PLL3 providing up to three independent output clocks:

      - to generate the kernel clock for peripherals

  - System, AHB and APB busses clocks configuration:

    - Several clock sources can be used to drive the System clock (SYSCLK): MSIS, HSI,
    HSE and main PLL.
    The AHB clock (HCLK) is derived from System clock through configurable
    prescaler and used to clock the CPU, memory and peripherals mapped
    on AHB bus (DMA, GPIO...). APB1 (PCLK1), APB2 (PCLK2) and APB3 (PCLK3) clocks are derived
    from AHB clock through configurable prescalers and used to clock
    the peripherals mapped on these busses.

    - All the peripheral bus clocks are derived from the System clock (SYSCLK) except:

      - IWDG: LSI clock.
      - UCPD1: HSI clock
      - Peripherals using a kernel clock selected by HAL_RCC_{PERIPHx}_SetKernelClkSource function
      (functions described in @ref RCC_Exported_Functions_Group4 section)

    - The maximum frequency of the SYSCLK, HCLK, PCLK1, PCLK2 and PCLK3 is 160 MHz.
    To correctly read data from Flash memory, the number of wait states (latency) must be
    correctly programmed in the FLASH register according to the
    frequency of the CPU clock (HCLK) and the internal voltage range of the device VCORE.

    When changing the CPU frequency, a software sequence must be applied
    in order to tune the number of wait states needed to access the flash memory:
    - FLASH latency must be increased before increasing the HCLK frequency
    - FLASH latency can be decreased only after decreasing the HCLK frequency

    The below tables show the correspondence between wait states and CPU clock frequency.

    Table 1. HCLK clock frequency for devices depending on FLASH latency and voltage range (LPM = 0).

    |   Latency       | range 1<br>1.1V-1.2V| range 2<br>1.0V-1.1V| range 3<br>0.9 V-1.0V| range 4<br>0.9V |
    |-----------------|---------------------|---------------------|----------------------|-----------------|
    |0WS(1 CPU cycle) |  0 < HCLK <= 32     |  0 < HCLK <= 30     |    0 < HCLK <= 24    |  0 < HCLK <= 12 |
    |1WS(2 CPU cycles)| 32 < HCLK <= 64     | 30 < HCLK <= 60     |   24 < HCLK <= 48    | 12 < HCLK <= 25 |
    |2WS(3 CPU cycles)| 64 < HCLK <= 96     | 60 < HCLK <= 90     |   48 < HCLK <= 55    |        -        |
    |3WS(4 CPU cycles)| 96 < HCLK <= 128    | 90 < HCLK <= 110    |         -            |        -        |
    |4WS(5 CPU cycles)|128 < HCLK <= 160    |         -           |         -            |        -        |

    The Flash memory supports a low-power read mode when setting the LPM bit in the FLASH
    register. The table below shows the correspondence between wait states and CPU clock frequency when LPM bit is set.

    Table 2. HCLK clock frequency for devices depending on FLASH latency and voltage range (LPM = 1).

    |   Latency         | range 1/2/3<br>0.9V-1.2V  | range 4<br>0.9V |
    |-------------------|---------------------------|-----------------|
    |0WS(1 CPU cycles)  |                           |  0 < HCLK <= 8  |
    |1WS(2 CPU cycles)  | WS >= HCLK (MHz) / 10 -1   |  8 < HCLK <= 16 |
    |2WS(3 CPU cycles)  |      Maximum HCLK         | 16 < HCLK <= 25 |
    |3WS(4 CPU cycles)  |      frequency is         |        -        |
    |       ...         |    given by Table 1       |        -        |
    |15WS(16 CPU cycles)|                           |        -        |

  - Reset function:

    - Reset the RCC clock configuration to the default system clock (MSIS at 4 MHz).
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1_0 Reset System clock to default function
  * @brief    Functions to reset the system clock to MSIS (4MHz)
  * @{
  */

void         HAL_RCC_Reset(void);
hal_status_t HAL_RCC_ResetSystemClock(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_1 RCC oscillators config service
  * @brief    Functions to configure the different oscillators.
  * @note     The following functions configure and activate the different oscillators.
  *           Configuration can be done:
  *           - using the atomic functions defined for each oscillators and PLL
  *             -# like HAL_RCC_{OSC}_Enable: {OSC} is HSI/MSI/MSIK/HSI48/LSI/LSE/SHSI/HSE
  *           - atomic function used for main PLL is described in the @ref RCC_Exported_Functions_Group1_3
  *
  *           example: enable HSE oscillator
  *           - using atomic function (footprint optimisation):
  *             @code
  *             HAL_RCC_HSE_Enable(HAL_RCC_HSE_ON);
  *             @endcode
  * @{
  */

/* HSI oscillator configuration and activation    ******************************/
hal_status_t        HAL_RCC_HSI_Enable(void);
hal_status_t        HAL_RCC_HSI_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_HSI_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_HSI_IsReady(void);
void                HAL_RCC_HSI_SetTrimming(uint32_t value);
uint32_t            HAL_RCC_HSI_GetTrimming(void);
uint32_t            HAL_RCC_HSI_GetCalibration(void);
hal_status_t        HAL_RCC_HSI_EnableInStopMode(void);
hal_status_t        HAL_RCC_HSI_DisableInStopMode(void);
hal_rcc_osc_stop_mode_status_t   HAL_RCC_HSI_IsEnabledInStopMode(void);

/* HSI48 oscillator configuration and activation    ******************************/
hal_status_t        HAL_RCC_HSI48_Enable(void);
hal_status_t        HAL_RCC_HSI48_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_HSI48_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_HSI48_IsReady(void);

/* SHSI oscillator configuration and activation    ******************************/
hal_status_t        HAL_RCC_SHSI_Enable(void);
hal_status_t        HAL_RCC_SHSI_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_SHSI_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_SHSI_IsReady(void);

/* MSIS and MSIK oscillators configuration and activation    ******************************/
hal_status_t        HAL_RCC_MSIS_Enable(hal_rcc_msis_range_t clock_range);
hal_status_t        HAL_RCC_MSIS_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_MSIS_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_MSIS_IsReady(void);
hal_rcc_msis_range_t HAL_RCC_MSIS_GetRange(void);
void                HAL_RCC_MSIS_SetStandbyRange(hal_rcc_msis_range_t msi_range);
hal_status_t        HAL_RCC_MSIK_Enable(hal_rcc_msik_range_t clock_range);
hal_status_t        HAL_RCC_MSIK_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_MSIK_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_MSIK_IsReady(void);
hal_rcc_msik_range_t HAL_RCC_MSIK_GetRange(void);
void                HAL_RCC_MSIK_SetStandbyRange(hal_rcc_msik_range_t msik_range);
hal_status_t        HAL_RCC_MSIK_EnableInStopMode(void);
hal_status_t        HAL_RCC_MSIK_DisableInStopMode(void);
hal_rcc_osc_stop_mode_status_t   HAL_RCC_MSIK_IsEnabledInStopMode(void);

void                HAL_RCC_MSI_SetTrimming(uint32_t value, hal_rcc_msi_range_calib_t ranges);
uint32_t            HAL_RCC_MSI_GetTrimming(hal_rcc_msi_range_calib_t ranges);
uint32_t            HAL_RCC_MSI_GetCalibration(hal_rcc_msi_range_calib_t ranges);
#if defined(LSE_VALUE)
hal_status_t        HAL_RCC_MSI_EnableHWAutoCalib(hal_rcc_msi_pll_mode_sel_t type,
                                                  hal_rcc_msi_pll_mode_startup_t pll_mode);
void                HAL_RCC_MSI_DisableHWAutoCalib(void);
hal_status_t        HAL_RCC_MSI_EnablePLLModeSelection(hal_rcc_msi_pll_mode_sel_t msipll_mode_selection);
hal_status_t        HAL_RCC_MSI_EnablePLLFastStartup(void);
hal_status_t        HAL_RCC_MSI_DisablePLLFastStartup(void);
hal_status_t        HAL_RCC_MSI_EnablePLLMode(void);
void                HAL_RCC_MSI_DisablePLLMode(void);
#endif /* LSE_VALUE*/
void                HAL_RCC_MSI_SetBiasMode(hal_rcc_msi_bias_mode_t bias_mode);
hal_rcc_msi_bias_mode_t HAL_RCC_MSI_GetBiasMode(void);

/* LSI oscillator configuration and activation    ******************************/
hal_status_t        HAL_RCC_LSI_Enable(hal_rcc_lsi_div_t divider);
hal_status_t        HAL_RCC_LSI_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_LSI_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_LSI_IsReady(void);

#if defined(HSE_VALUE)
/* HSE oscillator configuration and activation    ******************************/
hal_status_t        HAL_RCC_HSE_Enable(hal_rcc_hse_t mode);
hal_status_t        HAL_RCC_HSE_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_HSE_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_HSE_IsReady(void);
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/* LSE oscillator configuration and activation    ******************************/
hal_status_t        HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive, \
                                       hal_rcc_lse_glitch_filter_t glitch_filter);
hal_status_t        HAL_RCC_LSE_Disable(void);
hal_rcc_osc_enable_status_t   HAL_RCC_LSE_IsEnabled(void);
hal_rcc_osc_ready_status_t    HAL_RCC_LSE_IsReady(void);
#endif /* LSE_VALUE */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_2 RCC clock config service
  * @brief    Functions to configure the bus prescalers and retrieve bus clock frequencies (SYSCLK, HCLK and PCLKx).
  * @note     On some devices, DPHY prescaler used in DSI block is configured through the following APIs.
  * @note     Unitary functions can be used to configure independently each bus.
  *
  *           example: all the BUS prescalers are set
  *
  *           - Call the global @ref HAL_RCC_SetBusClockConfig
  *             @code
  *               LL_FLASH_SetLatency(LL_FLASH_LATENCY_4WS);
  *               HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_PLLCLK);
  *               hal_rcc_bus_clk_config_t config_bus;
  *               config_bus.hclk_prescaler  = HAL_RCC_HCLK_PRESCALER1;
  *               config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk3_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               HAL_RCC_SetBusClockConfig(&config_bus);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source);
hal_rcc_sysclk_src_t  HAL_RCC_GetSYSCLKSource(void);
hal_status_t          HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK3Prescaler(hal_rcc_pclk_prescaler_t prescaler);
#if defined(RCC_CFGR2_PPRE_DPHY)
void                  HAL_RCC_DSI_SetDPHYPrescaler(hal_rcc_pclk_prescaler_t prescaler);
#endif /* RCC_CFGR2_PPRE_DPHY */
hal_rcc_hclk_prescaler_t    HAL_RCC_GetHCLKPrescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK1Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK2Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK3Prescaler(void);
#if defined(RCC_CFGR2_PPRE_DPHY)
hal_rcc_pclk_prescaler_t    HAL_RCC_DSI_GetDPHYPrescaler(void);
#endif /* RCC_CFGR2_PPRE_DPHY */
hal_status_t          HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config);
void                  HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config);

uint32_t              HAL_RCC_GetSYSCLKFreq(void);
uint32_t              HAL_RCC_GetHCLKFreq(void);
uint32_t              HAL_RCC_GetPCLK1Freq(void);
uint32_t              HAL_RCC_GetPCLK2Freq(void);
uint32_t              HAL_RCC_GetPCLK3Freq(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_3 RCC management of PLL1
  * @brief    Functions to configure the different PLL1
  * @details  PLL1 (main PLL) might be used for system clock.
  *           PLL1 is configured and enabled respectively with HAL_RCC_PLL1_SetConfig() and HAL_RCC_PLL1_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL1.
  *
  *           example1: activation main PLL
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable();
  *               HAL_RCC_HSI_SetTrimmingConfig(HAL_RCC_HSICALIBRATION_DEFAULT);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               HAL_RCC_PLL1_SetConfig(&config_pll);
  *               HAL_RCC_PLL1_Enable();
  *               HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL1_Enable(void);
hal_status_t          HAL_RCC_PLL1_Disable(void);
hal_status_t          HAL_RCC_PLL1_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL1_DisableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL1_Reset(void);
void                  HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config);
uint32_t              HAL_RCC_PLL1_GetOutput(void);
hal_rcc_pll_status_t  HAL_RCC_PLL1_IsReady(void);
void                  HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);
hal_status_t          HAL_RCC_PLL1_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL1_GetFRACN(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_4 RCC management of PLL2
  * @brief    Functions to configure the different PLL2
  * @details  PLL2 is configured and enabled respectively with HAL_RCC_PLL2_SetConfig() and HAL_RCC_PLL2_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL2.
  *
  *           example1: activation PLL2 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_MSI_Enable(HAL_RCC_MSIS_FREQ_4MHZ);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_MSIS;
  *               config_pll.pll_m = 1;
  *               config_pll.pll_n = 43;
  *               config_pll.pll_p = 7;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2;
  *               config_pll.pll_fracn = 0;
  *               HAL_RCC_PLL2_SetConfig(&config_pll);
  *               HAL_RCC_PLL2_Enable();
  *               HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL2_OUTPUT_P | HAL_RCC_PLL2_OUTPUT_Q | HAL_RCC_PLL2_OUTPUT_R);
  *             @endcode
  *
  *           example2: activation PLL2 in activating as source of SAI1
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_MSI_Enable(HAL_RCC_MSIS_FREQ_4MHZ);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_MSIS;
  *               config_pll.pll_m = 1;
  *               config_pll.pll_n = 8;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2;
  *               HAL_RCC_PLL2_SetConfig(&config_pll);
  *               HAL_RCC_PLL2_Enable();
  *               HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL2_OUTPUT_P);
  *               HAL_RCC_SAI1_SetKernelClkSource(HAL_RCC_SAI1CLKSOURCE_PLL2);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL2_Enable(void);
hal_status_t          HAL_RCC_PLL2_Disable(void);
hal_status_t          HAL_RCC_PLL2_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL2_DisableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL2_Reset(void);
void                  HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config);
uint32_t              HAL_RCC_PLL2_GetOutput(void);
hal_rcc_pll_status_t  HAL_RCC_PLL2_IsReady(void);
void                  HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);
hal_status_t          HAL_RCC_PLL2_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL2_GetFRACN(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_5 RCC management of PLL3
  * @brief    Functions to configure the different PLL3
  * @details  PLL3 is configured and enabled respectively with HAL_RCC_PLL3_SetConfig() and HAL_RCC_PLL3_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL3.
  *
  *           example1: activation PLL3 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_MSI_Enable(HAL_RCC_MSIS_FREQ_4MHZ);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_MSIS;
  *               config_pll.pll_m = 1;
  *               config_pll.pll_n = 43;
  *               config_pll.pll_p = 7;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2;
  *               config_pll.pll_fracn = 0;
  *               HAL_RCC_PLL3_SetConfig(&config_pll);
  *               HAL_RCC_PLL3_Enable();
  *               HAL_RCC_PLL3_EnableOutput(HAL_RCC_PLL3_OUTPUT_P | HAL_RCC_PLL3_OUTPUT_Q | HAL_RCC_PLL3_OUTPUT_R);
  *             @endcode
  *
  *           example2: activation PLL3 in activating as source of SAI1
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_MSI_Enable(HAL_RCC_MSIS_FREQ_4MHZ);
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_MSIS;
  *               config_pll.pll_m = 1;
  *               config_pll.pll_n = 8;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2;
  *               HAL_RCC_PLL3_SetConfig(&config_pll);
  *               HAL_RCC_PLL3_Enable();
  *               HAL_RCC_PLL3_EnableOutput(HAL_RCC_PLL3_OUTPUT_P);
  *               HAL_RCC_SAI1_SetKernelClkSource(HAL_RCC_SAI1CLKSOURCE_PLL3);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL3_SetConfig(const hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL3_Enable(void);
hal_status_t          HAL_RCC_PLL3_Disable(void);
hal_status_t          HAL_RCC_PLL3_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL3_DisableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL3_Reset(void);
void                  HAL_RCC_PLL3_GetConfig(hal_rcc_pll_config_t *p_config);
uint32_t              HAL_RCC_PLL3_GetOutput(void);
hal_rcc_pll_status_t  HAL_RCC_PLL3_IsReady(void);
void                  HAL_RCC_PLL3_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);
hal_status_t          HAL_RCC_PLL3_SetFRACN(uint16_t fracn);
uint16_t              HAL_RCC_PLL3_GetFRACN(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group1_6 RCC management of Systick external clock source
  * @brief    Functions to Set, Get the Systick external clock source and frequency.
  * @{
  */

void                         HAL_RCC_SetSysTickExternalClkSource(hal_rcc_systick_clk_src_t clk_src);
hal_rcc_systick_clk_src_t    HAL_RCC_GetSysTickExternalClkSource(void);
uint32_t                     HAL_RCC_GetSysTickExternalClkFreq(void);

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Clock management on buses
  This subsection provides a set of functions (on AHB1, AHB2, AHB3, APB1, APB2 or APB3 buses) allowing to:

  - Enable or disable the peripherals clock.
  - Reset of peripherals clock.
  - Enable or disable the peripherals clock in low power mode.
  - Enable or disable the peripherals clock in autonomous mode.
  * @{
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function enables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the CORDIC clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the FMAC clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_FMAC);
}
/**
  * @details This function enables the TSC clock.
  */
__STATIC_INLINE void HAL_RCC_TSC_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_TSC);
}
/**
  * @details This function enables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC);
}

#if defined(JPEG)
/**
  * @details This function enables the JPEG clock.
  */
__STATIC_INLINE void HAL_RCC_JPEG_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_JPEG);
}
#endif /* JPEG */

/**
  * @details This function enables the RAMCFG clock.
  */
__STATIC_INLINE void HAL_RCC_RAMCFG_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_RAMCFG);
}
/**
  * @details This function enables the FLASH clock.
  */
__STATIC_INLINE void HAL_RCC_FLASH_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the MDF1 clock.
  */
__STATIC_INLINE void HAL_RCC_MDF1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_MDF1);
}

#if defined(DMA2D)
/**
  * @details This function enables the DMA2D clock.
  */
__STATIC_INLINE void HAL_RCC_DMA2D_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2D);
}
#endif /* DMA2D */

#if defined(GFXMMU)
/**
  * @details This function enables the GFXMMU clock.
  */
__STATIC_INLINE void HAL_RCC_GFXMMU_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GFXMMU);
}
#endif /* GFXMMU */

#if defined(GPU2D)
/**
  * @details This function enables the GPU2D clock.
  */
__STATIC_INLINE void HAL_RCC_GPU2D_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPU2D);
}
#endif /* GPU2D */

#if defined(DCACHE2)
/**
  * @details This function enables the DCACHE2 clock.
  */
__STATIC_INLINE void HAL_RCC_DCACHE2_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DCACHE2);
}
#endif /* DCACHE2 */

/**
  * @details This function enables the GTZC1 clock.
  */
__STATIC_INLINE void HAL_RCC_GTZC1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GTZC1);
}

/**
  * @details This function enables the BKPSRAM clock.
  */
__STATIC_INLINE void HAL_RCC_BKPSRAM_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}

/**
  * @details This function enables the DCACHE1 clock.
  */
__STATIC_INLINE void HAL_RCC_DCACHE1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DCACHE1);
}

/**
  * @details This function enables the SRAM1 clock.
  */
__STATIC_FORCEINLINE void HAL_RCC_SRAM1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @details This function disables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the CORDIC clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the FMAC clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_FMAC);
}

/**
  * @details This function disables the MDF1 clock.
  */
__STATIC_INLINE void HAL_RCC_MDF1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_MDF1);
}

/**
  * @details This function disables the FLASH clock.
  */
__STATIC_INLINE void HAL_RCC_FLASH_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CRC);
}

#if defined(JPEG)
/**
  * @details This function disables the JPEG clock.
  */
__STATIC_INLINE void HAL_RCC_JPEG_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_JPEG);
}
#endif /* JPEG */

/**
  * @details This function disables the TSC clock.
  */
__STATIC_INLINE void HAL_RCC_TSC_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_TSC);
}

/**
  * @details This function disables the RAMCFG clock.
  */
__STATIC_INLINE void HAL_RCC_RAMCFG_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

#if defined(DMA2D)
/**
  * @details This function disables the DMA2D clock.
  */
__STATIC_INLINE void HAL_RCC_DMA2D_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA2D);
}
#endif /* DMA2D */

#if defined(GFXMMU)
/**
  * @details This function disables the GFXMMU clock.
  */
__STATIC_INLINE void HAL_RCC_GFXMMU_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GFXMMU);
}
#endif /* GFXMMU */

#if defined(GPU2D)
/**
  * @details This function disables the GPU2D clock.
  */
__STATIC_INLINE void HAL_RCC_GPU2D_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPU2D);
}
#endif /* GPU2D */

#if defined(DCACHE2)
/**
  * @details This function disables the DCACHE2 clock.
  */
__STATIC_INLINE void HAL_RCC_DCACHE2_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DCACHE2);
}
#endif /* DCACHE2 */

/**
  * @details This function disables the GTZC1 clock.
  */
__STATIC_INLINE void HAL_RCC_GTZC1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GTZC1);
}

/**
  * @details This function disables the BKPSRAM clock.
  */
__STATIC_INLINE void HAL_RCC_BKPSRAM_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}

/**
  * @details This function disables the DCACHE1 clock.
  */
__STATIC_INLINE void HAL_RCC_DCACHE1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DCACHE1);
}

/**
  * @details This function disables the SRAM1 clock.
  */
__STATIC_FORCEINLINE void HAL_RCC_SRAM1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_SRAM1);
}
/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable AHB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function enables the GPIOA clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOB clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOC clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOD clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOE clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
}

#if defined(GPIOF)
/**
  * @details This function enables the GPIOF clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
}
#endif /* GPIOF */

/**
  * @details This function enables the GPIOG clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOH clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
}

#if defined(GPIOI)
/**
  * @details This function enables the GPIOI clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOI);
}
#endif /* GPIOI */

#if defined(GPIOJ)
/**
  * @details This function enables the GPIOJ clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOJ_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOJ);
}

#endif /* GPIOJ */

/**
  * @details This function enables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the DCMI_PSSI clock.
  */
__STATIC_INLINE void HAL_RCC_DCMI_PSSI_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
}
#if defined (USB_OTG_HS)
/**
  * @details This function enables the USB_OTG_HS clock.
  */
__STATIC_INLINE void HAL_RCC_USB_OTG_HS_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTG_HS);
}
#endif /* USB_OTG_HS */

#if defined (USB_OTG_FS)
/**
  * @details This function enables the USB_OTG_FS clock.
  */
__STATIC_INLINE void HAL_RCC_USB_OTG_FS_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTG_FS);
}
#endif /* USB_OTG_FS */

#if defined(USB_OTG_HS)
/**
  * @details This function enables the USBHSPHY clock.
  */
__STATIC_INLINE void HAL_RCC_USBHSPHY_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTGHSPHY);
}
#endif /* USB_OTG_HS */

#if defined(AES)
/**
  * @details This function enables the AES clock.
  */
__STATIC_INLINE void HAL_RCC_AES_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AES);
}
#endif /* AES */

#if defined(HASH)
/**
  * @details This function enables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_HASH);
}
#endif /* HASH */

/**
  * @details This function enables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_RNG);
}

#if defined(PKA)
/**
  * @details This function enables the PKA clock.
  */
__STATIC_INLINE void HAL_RCC_PKA_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_PKA);
}
#endif /* PKA */

#if defined(SAES)
/**
  * @details This function enables the SAES clock.
  */
__STATIC_INLINE void HAL_RCC_SAES_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(OCTOSPIM)
/**
  * @details This function enables the OCTOSPIM clock.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPIM_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
}
#endif /* OCTOSPIM */

#if defined(OTFDEC1)
/**
  * @details This function enables the OTFDEC1 clock.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC1_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

#if defined(OTFDEC2)
/**
  * @details This function enables the OTFDEC2 clock.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_OTFDEC2);
}
#endif /* OTFDEC2 */

/**
  * @details This function enables the SDMMC1 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_SDMMC1);
}

#if defined(SDMMC2)
/**
  * @details This function enables the SDMMC2 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_SDMMC2);
}
#endif /* SDMMC2 */

/**
  * @details This function enables the SRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_SRAM2);
}

#if defined (SRAM3_BASE)
/**
  * @details This function enables the SRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM3_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined(FMC_BASE)
/**
  * @details This function enables the FSMC clock.
  */
__STATIC_INLINE void HAL_RCC_FSMC_EnableClock(void)
{
  LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_FSMC);
}
#endif /* FMC_BASE */

/**
  * @details This function enables the OCTOSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPI1_EnableClock(void)
{
  LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
}

#if defined(OCTOSPI2)
/**
  * @details This function enables the OCTOSPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPI2_EnableClock(void)
{
  LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
}
#endif /* OCTOSPI2 */

/**
  * @details This function disables the GPIOA clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOB clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOC clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOD clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOE clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
}

#if defined(GPIOF)
/**
  * @details This function disables the GPIOF clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
}
#endif /* GPIOF */

/**
  * @details This function disables the GPIOG clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOH clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
}

#if defined(GPIOI)
/**
  * @details This function disables the GPIOI clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOI);
}
#endif /* GPIOI */

#if defined(GPIOJ)
/**
  * @details This function disables the GPIOJ clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOJ_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
#endif /* GPIOJ */

/**
  * @details This function disables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the DCMI_PSSI clock.
  */
__STATIC_INLINE void HAL_RCC_DCMI_PSSI_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
}

#if defined(USB_OTG_HS)
/**
  * @details This function disables the USB_OTG_HS clock.
  */
__STATIC_INLINE void HAL_RCC_USB_OTG_HS_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_OTG_HS);
}
#endif /* USB_OTG_HS */

#if defined (USB_OTG_FS)
/**
  * @details This function disables the USB_OTG_FS clock.
  */
__STATIC_INLINE void HAL_RCC_USB_OTG_FS_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_OTG_FS);
}
#endif /* USB_OTG_FS */

#if defined(USB_OTG_HS)
/**
  * @details This function disables the USBHSPHY clock.
  */
__STATIC_INLINE void HAL_RCC_USBHSPHY_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_OTGHSPHY);
}
#endif /* USB_OTG_HS */

#if defined(AES)
/**
  * @details This function disables the AES clock.
  */
__STATIC_INLINE void HAL_RCC_AES_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AES);
}
#endif /* AES */

#if defined(HASH)
/**
  * @details This function disables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_HASH);
}
#endif /* HASH */

/**
  * @details This function disables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_RNG);
}

#if defined(PKA)
/**
  * @details This function disables the PKA clock.
  */
__STATIC_INLINE void HAL_RCC_PKA_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_PKA);
}
#endif /* PKA */

#if defined(SAES)
/**
  * @details This function disables the SAES clock.
  */
__STATIC_INLINE void HAL_RCC_SAES_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(OCTOSPIM)
/**
  * @details This function disables the OCTOSPIM clock.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPIM_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
}
#endif /* OCTOSPIM */

#if defined(OTFDEC1)
/**
  * @details This function disables the OTFDEC1 clock.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC1_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

#if defined (OTFDEC2)
/**
  * @details This function disables the OTFDEC2 clock.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_OTFDEC2);
}
#endif /* OTFDEC2 */

/**
  * @details This function disables the SDMMC1 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_SDMMC1);
}

#if defined (SDMMC2)
/**
  * @details This function disables the SDMMC2 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_SDMMC2);
}
#endif /* SDMMC2 */

/**
  * @details This function disables the SRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_SRAM2);
}

#if defined (SRAM3_BASE)
/**
  * @details This function disables the SRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM3_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined(HSPI1)
/**
  * @details This function enables the HSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_HSPI1_EnableClock(void)
{
  LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_HSPI1);
}
#endif /* HSPI1 */

#if defined (SRAM6_BASE)
/**
  * @details This function enables the SRAM6 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM6_EnableClock(void)
{
  LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_SRAM6);
}
#endif /* SRAM6_BASE */

#if defined (SRAM5_BASE)
/**
  * @details This function enables the SRAM5 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM5_EnableClock(void)
{
  LL_AHB2_GRP2_EnableClock(LL_AHB2_GRP2_PERIPH_SRAM5);
}
#endif /* SRAM5_BASE */

#if defined (FMC_BASE)
/**
  * @details This function disables the FSMC clock.
  */
__STATIC_INLINE void HAL_RCC_FSMC_DisableClock(void)
{
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_FSMC);
}
#endif /* FMC_BASE */

/**
  * @details This function disables the OCTOSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPI1_DisableClock(void)
{
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
}

#if defined (OCTOSPI2)
/**
  * @details This function disables the OCTOSPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPI2_DisableClock(void)
{
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
}
#endif /* OCTOSPI2 */

#if defined(HSPI1)
/**
  * @details This function disables the HSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_HSPI1_DisableClock(void)
{
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_HSPI1);
}
#endif /* HSPI1 */

#if defined (SRAM6_BASE)
/**
  * @details This function disables the SRAM6 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM6_DisableClock(void)
{
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_SRAM6);
}
#endif /* SRAM6_BASE */

#if defined (SRAM5_BASE)
/**
  * @details This function disables the SRAM5 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM5_DisableClock(void)
{
  LL_AHB2_GRP2_DisableClock(LL_AHB2_GRP2_PERIPH_SRAM5);
}
#endif /* SRAM5_BASE */
/**
  * @}
  */

/** @defgroup RCC_AHB3_Clock_Enable_Disable AHB3ENR Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB3ENR peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

/**
  * @details This function enables the LPGPIO1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPGPIO1_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_LPGPIO1);
}

/**
  * @details This function enables the PWR clock.
  */
__STATIC_INLINE void HAL_RCC_PWR_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_PWR);
}

/**
  * @details This function enables the ADC4 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC4_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_ADC4);
}

/**
  * @details This function enables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the LPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPDMA1_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_LPDMA1);
}

/**
  * @details This function enables the ADF1 clock.
  */
__STATIC_INLINE void HAL_RCC_ADF1_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_ADF1);
}

/**
  * @details This function enables the GTZC2 clock.
  */
__STATIC_INLINE void HAL_RCC_GTZC2_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_GTZC2);
}

/**
  * @details This function enables the SRAM4 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM4_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_SRAM4);
}

/**
  * @details This function disables the LPGPIO1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPGPIO1_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_LPGPIO1);
}

/**
  * @details This function disables the PWR clock.
  */
__STATIC_INLINE void HAL_RCC_PWR_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_PWR);
}

/**
  * @details This function disables the ADC4 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC4_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ADC4);
}

/**
  * @details This function disables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the LPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPDMA1_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_LPDMA1);
}

/**
  * @details This function disables the ADF1 clock.
  */
__STATIC_INLINE void HAL_RCC_ADF1_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the GTZC2 clock.
  */
__STATIC_INLINE void HAL_RCC_GTZC2_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_GTZC2);
}

/**
  * @details This function disables the SRAM4 clock.
  */
__STATIC_INLINE void HAL_RCC_SRAM4_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_SRAM4);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

/**
  * @details This function enables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM6 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM6_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM7 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM7_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the WWDG clock.
  */
__STATIC_INLINE void HAL_RCC_WWDG_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined (USART2)
/**
  * @details This function enables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
}
#endif /* USART2 */

/**
  * @details This function enables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the UART4 clock.
  */
__STATIC_INLINE void HAL_RCC_UART4_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART5 clock.
  */
__STATIC_INLINE void HAL_RCC_UART5_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the I2C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C2 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_CRS);
}


#if defined(USART6)
/**
  * @details This function enables the USART6 clock.
  */
__STATIC_INLINE void HAL_RCC_USART6_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART6);
}
#endif /* USART6 */

/**
  * @details This function enables the I2C4 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C4_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_I2C4);
}

/**
  * @details This function enables the LPTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_LPTIM2);
}

#if defined(I2C5)
/**
  * @details This function enables the I2C5 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C5_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_I2C5);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @details This function enables the I2C6 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C6_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_I2C6);
}
#endif /* I2C6 */

/**
  * @details This function enables the FDCAN clock.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_FDCAN1);
}

#if defined (UCPD1)
/**
  * @details This function enables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @details This function disables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM6 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM6_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM7 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM7_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined (USART2)
/**
  * @details This function disables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
}
#endif /* USART2 */
/**
  * @details This function disables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the UART4 clock.
  */
__STATIC_INLINE void HAL_RCC_UART4_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART5 clock.
  */
__STATIC_INLINE void HAL_RCC_UART5_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the I2C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C2 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_CRS);
}

#if defined(USART6)
/**
  * @details This function disables the USART6 clock.
  */
__STATIC_INLINE void HAL_RCC_USART6_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART6);
}
#endif /* USART6 */

/**
  * @details This function disables the I2C4 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C4_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_I2C4);
}

/**
  * @details This function disables the LPTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_LPTIM2);
}

#if defined(I2C5)
/**
  * @details This function disables the I2C5 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C5_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_I2C5);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @details This function disables the I2C6 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C6_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_I2C6);
}
#endif /* I2C6 */

/**
  * @details This function disables the FDCAN clock.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_FDCAN1);
}

#if defined(UCPD1)
/**
  * @details This function disables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function enables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
}


/**
  * @details This function enables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the TIM15 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM15_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM16 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM16_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM17 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM17_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the SAI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SAI1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SAI1);
}

#if defined (SAI2)
/**
  * @details This function enables the SAI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SAI2_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SAI2);
}
#endif /* SAI2 */

#if defined(GFXTIM)
/**
  * @details This function enables the GFXTIM clock.
  */
__STATIC_INLINE void HAL_RCC_GFXTIM_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GFXTIM);
}
#endif /* GFXTIM */

#if defined(LTDC)
/**
  * @details This function enables the LTDC clock.
  */
__STATIC_INLINE void HAL_RCC_LTDC_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_LTDC);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @details This function enables the DSI clock.
  */
__STATIC_INLINE void HAL_RCC_DSI_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_DSI);
}
#endif /* DSI */

#if defined(USB_DRD_FS)
/**
  * @details This function enables the USB_FS clock.
  */
__STATIC_INLINE void HAL_RCC_USB_DRD_FS_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USB_FS);
}
#endif /* USB_DRD_FS */

/**
  * @details This function disables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the TIM15 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM15_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM16 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM16_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM17 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM17_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the SAI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SAI1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SAI1);
}

#if defined (SAI2)
/**
  * @details This function disables the SAI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SAI2_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SAI2);
}
#endif /* SAI2 */

#if defined(GFXTIM)
/**
  * @details This function disables the GFXTIM clock.
  */
__STATIC_INLINE void HAL_RCC_GFXTIM_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GFXTIM);
}
#endif /* GFXTIM */

#if defined(LTDC)
/**
  * @details This function disables the LTDC clock.
  */
__STATIC_INLINE void HAL_RCC_LTDC_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_LTDC);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @details This function disables the DSI clock.
  */
__STATIC_INLINE void HAL_RCC_DSI_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_DSI);
}
#endif /* DSI */

#if defined(USB_DRD_FS)
/**
  * @details This function disables the USB_FS clock.
  */
__STATIC_INLINE void HAL_RCC_USB_DRD_FS_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USB_FS);
}
#endif /* USB_DRD_FS */

/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Enable_Disable APB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function enables the SYSCFG clock.
  */
__STATIC_INLINE void HAL_RCC_SYSCFG_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_SYSCFG);
}

/**
  * @details This function enables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the LPTIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the OPAMP clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_OPAMP);
}

/**
  * @details This function enables the COMP clock.
  */
__STATIC_INLINE void HAL_RCC_COMP_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_COMP);
}

/**
  * @details This function enables the VREF clock.
  */
__STATIC_INLINE void HAL_RCC_VREF_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_VREF);
}

/**
  * @details This function enables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_EnableClock(void)
{
  LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the SYSCFG clock.
  */
__STATIC_INLINE void HAL_RCC_SYSCFG_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_SYSCFG);
}

/**
  * @details This function disables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the LPTIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the OPAMP clock.
  */
__STATIC_INLINE void HAL_RCC_OPAMP_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_OPAMP);
}

/**
  * @details This function disables the COMP clock.
  */
__STATIC_INLINE void HAL_RCC_COMP_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_COMP);
}

/**
  * @details This function disables the VREF clock.
  */
__STATIC_INLINE void HAL_RCC_VREF_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_VREF);
}

/**
  * @details This function disables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_DisableClock(void)
{
  LL_APB3_GRP1_DisableClock(LL_APB3_GRP1_PERIPH_RTCAPB);
}
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Status AHB1 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function checks if the GPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function checks if the CORDIC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CORDIC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CORDIC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CORDIC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function checks if the FMAC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMAC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMAC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMAC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_FMAC);
}

/**
  * @details This function checks if the MDF1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED MDF1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  MDF1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_MDF1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_MDF1);
}

/**
  * @details This function checks if the FLASH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FLASH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FLASH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FLASH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function checks if the CRC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_CRC);
}

#if defined(JPEG)
/**
  * @details This function checks if the JPEG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED JPEG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  JPEG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_JPEG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_JPEG);
}
#endif /* JPEG */

/**
  * @details This function checks if the TSC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TSC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TSC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TSC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_TSC);
}

/**
  * @details This function checks if the RAMCFG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RAMCFG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RAMCFG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RAMCFG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

#if defined(DMA2D)
/**
  * @details This function checks if the DMA2D clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DMA2D clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DMA2D clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DMA2D_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DMA2D);
}
#endif /* DMA2D */

#if defined(GFXMMU)
/**
  * @details This function checks if the GFXMMU clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GFXMMU clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GFXMMU clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GFXMMU_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GFXMMU);
}
#endif /* GFXMMU */

#if defined(GPU2D)
/**
  * @details This function checks if the GPU2D clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPU2D clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPU2D clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPU2D_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPU2D);
}
#endif /* GPU2D */

#if defined(DCACHE2)
/**
  * @details This function checks if the DCACHE2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DCACHE2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DCACHE2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DCACHE2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DCACHE2);
}
#endif /* DCACHE2 */

/**
  * @details This function checks if the GTZC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GTZC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GTZC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GTZC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GTZC1);
}

/**
  * @details This function checks if the BKPSRAM clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED BKPSRAM clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  BKPSRAM clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_BKPSRAM_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}

/**
  * @details This function checks if the DCACHE1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DCACHE1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DCACHE1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DCACHE1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_DCACHE1);
}

/**
  * @details This function checks if the SRAM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM1 clock is enabled
 */
__STATIC_FORCEINLINE hal_rcc_clk_status_t HAL_RCC_SRAM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Status AHB2 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function checks if the GPIOA clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOA clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOA clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOA_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function checks if the GPIOB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function checks if the GPIOC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function checks if the GPIOD clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOD clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOD clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOD_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function checks if the GPIOE clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOE clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOE clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOE_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOE);
}

#if defined (GPIOF)
/**
  * @details This function checks if the GPIOF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOF);
}
#endif /* GPIOF */

/**
  * @details This function checks if the GPIOG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function checks if the GPIOH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOH);
}

#if defined(GPIOI)
/**
  * @details This function checks if the GPIOI clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOI clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOI clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOI_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOI);
}
#endif /* GPIOI */

#if defined(GPIOJ)
/**
  * @details This function checks if the GPIOJ clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOJ clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOJ clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOJ_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
#endif /* GPIOJ */

/**
  * @details This function checks if the ADC12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_ADC12);
}

/**
  * @details This function checks if the DCMI_PSSI clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DCMI_PSSI clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DCMI_PSSI clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DCMI_PSSI_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
}

#if defined(USB_OTG_HS)
/**
  * @details This function checks if the USB_OTG_HS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USB_OTG_HS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USB_OTG_HS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USB_OTG_HS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_OTG_HS);
}
#endif /* USB_OTG_HS */

#if defined (USB_OTG_FS)
/**
  * @details This function checks if the USB_OTG_FS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USB_OTG_FS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USB_OTG_FS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USB_OTG_FS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_OTG_FS);
}
#endif /* USB_OTG_FS */

#if defined(USB_OTG_HS)
/**
  * @details This function checks if the USBHSPHY clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USBHSPHY clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USBHSPHY clock is enabled
  */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USBHSPHY_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_OTGHSPHY);
}
#endif /* USB_OTG_HS */

#if defined(AES)
/**
  * @details This function checks if the AES clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AES clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AES clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AES_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AES);
}
#endif /* AES */

#if defined(HASH)
/**
  * @details This function checks if the HASH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HASH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HASH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HASH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_HASH);
}
#endif /* HASH */

/**
  * @details This function checks if the RNG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RNG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RNG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RNG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_RNG);
}

#if defined(PKA)
/**
  * @details This function checks if the PKA clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED PKA clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  PKA clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_PKA_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_PKA);
}
#endif /* PKA */

#if defined(SAES)
/**
  * @details This function checks if the SAES clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SAES clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SAES clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SAES_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(OCTOSPIM)
/**
  * @details This function checks if the OCTOSPIM clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OCTOSPIM clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OCTOSPIM clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OCTOSPIM_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
}
#endif /* OCTOSPIM */

#if defined(OTFDEC1)
/**
  * @details This function checks if the OTFDEC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OTFDEC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OTFDEC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OTFDEC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

#if defined(OTFDEC2)
/**
  * @details This function checks if the OTFDEC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OTFDEC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OTFDEC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OTFDEC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_OTFDEC2);
}
#endif /* OTFDEC2 */

/**
  * @details This function checks if the SDMMC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SDMMC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SDMMC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SDMMC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_SDMMC1);
}

#if defined(SDMMC2)
/**
  * @details This function checks if the SDMMC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SDMMC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SDMMC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SDMMC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_SDMMC2);
}
#endif /* SDMMC2 */

/**
  * @details This function checks if the SRAM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_SRAM2);
}

#if defined (SRAM3_BASE)
/**
  * @details This function checks if the SRAM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined (FMC_BASE)
/**
  * @details This function checks if the FSMC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FSMC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FSMC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FSMC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_FSMC);
}
#endif /* FMC_BASE */

/**
  * @details This function checks if the OCTOSPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OCTOSPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OCTOSPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OCTOSPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
}

#if defined (OCTOSPI2)
/**
  * @details This function checks if the OCTOSPI2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OCTOSPI2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OCTOSPI2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OCTOSPI2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
}
#endif /* OCTOSPI2 */

#if defined(HSPI1)
/**
  * @details This function checks if the HSPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HSPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HSPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HSPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_HSPI1);
}
#endif /* HSPI1 */

#if defined (SRAM6_BASE)
/**
  * @details This function checks if the SRAM6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_SRAM6);
}
#endif /* SRAM6_BASE */

#if defined (SRAM5_BASE)
/**
  * @details This function checks if the SRAM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP2_IsEnabledClock(LL_AHB2_GRP2_PERIPH_SRAM5);
}
#endif /* SRAM5_BASE */

/**
  * @}
  */

/** @defgroup RCC_AHB3_Peripheral_Clock_Enable_Status AHB3 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB3 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function checks if the LPGPIO1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPGPIO1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPGPIO1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPGPIO1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_LPGPIO1);
}

/**
  * @details This function checks if the PWR clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED PWR clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  PWR clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_PWR_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_PWR);
}

/**
  * @details This function checks if the ADC4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_ADC4);
}

/**
  * @details This function checks if the DAC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function checks if the LPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_LPDMA1);
}

/**
  * @details This function checks if the ADF1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADF1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADF1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADF1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_ADF1);
}

/**
  * @details This function checks if the GTZC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GTZC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GTZC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GTZC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_GTZC2);
}

/**
  * @details This function checks if the SRAM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SRAM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SRAM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SRAM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_SRAM4);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Status APB1 Peripheral Clock Enabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function checks if the TIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function checks if the TIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function checks if the TIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function checks if the TIM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function checks if the TIM6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function checks if the TIM7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function checks if the WWDG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED WWDG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  WWDG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_WWDG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function checks if the SPI2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined (USART2)
/**
  * @details This function checks if the USART2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART2);
}
#endif /* USART2 */
/**
  * @details This function checks if the USART3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function checks if the UART4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function checks if the UART5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function checks if the I2C1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function checks if the I2C2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function checks if the CRS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_CRS);
}

#if defined(USART6)
/**
  * @details This function checks if the USART6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART6);
}
#endif /* USART6 */

/**
  * @details This function checks if the I2C4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_I2C4);
}

/**
  * @details This function checks if the LPTIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_LPTIM2);
}

#if defined(I2C5)
/**
  * @details This function checks if the I2C5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_I2C5);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @details This function checks if the I2C6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_I2C6);
}
#endif /* I2C6 */

/**
  * @details This function checks if the FDCAN clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FDCAN clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FDCAN clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FDCAN_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_FDCAN1);
}

#if defined (UCPD1)
/**
  * @details This function checks if the UCPD1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UCPD1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UCPD1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UCPD1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Status APB2 Peripheral Clock Enabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */

/**
  * @details This function checks if the TIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function checks if the SPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function checks if the TIM8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function checks if the USART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function checks if the TIM15 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM15 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM15 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM15_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function checks if the TIM16 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM16 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM16 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM16_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function checks if the TIM17 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM17 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM17 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM17_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function checks if the SAI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SAI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SAI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SAI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SAI1);
}

#if defined (SAI2)
/**
  * @details This function checks if the SAI2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SAI2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SAI2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SAI2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SAI2);
}
#endif /* SAI2 */

#if defined(GFXTIM)
/**
  * @details This function checks if the GFXTIM clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GFXTIM clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GFXTIM clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GFXTIM_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GFXTIM);
}
#endif /* GFXTIM */

#if defined(LTDC)
/**
  * @details This function checks if the LTDC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LTDC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LTDC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LTDC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_LTDC);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @details This function checks if the DSI clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DSI clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DSI clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DSI_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_DSI);
}
#endif /* DSI */

#if defined(USB_DRD_FS)
/**
  * @details This function checks if the USB_FS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USB_FS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USB_FS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USB_DRD_FS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USB_FS);
}
#endif /* USB_DRD_FS */

/**
  * @}
  */

/** @defgroup RCC_APB3_Peripheral_Clock_Enable_Status APB3 Peripheral Clock Enabled Status
  * @brief  Check whether the APB3 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @{
  */
/**
  * @details This function checks if the SYSCFG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SYSCFG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SYSCFG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SYSCFG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_SYSCFG);
}

/**
  * @details This function checks if the SPI3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_SPI3);
}

/**
  * @details This function checks if the LPUART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPUART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPUART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPUART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function checks if the I2C3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_I2C3);
}

/**
  * @details This function checks if the LPTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function checks if the LPTIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function checks if the LPTIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function checks if the OPAMP clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OPAMP clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OPAMP clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OPAMP_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_OPAMP);
}

/**
  * @details This function checks if the COMP clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_COMP);
}

/**
  * @details This function checks if the VREF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED VREF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  VREF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_VREF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_VREF);
}

/**
  * @details This function checks if the RTCAPB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RTCAPB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RTCAPB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RTCAPB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB3_GRP1_IsEnabledClock(LL_APB3_GRP1_PERIPH_RTCAPB);
}

/**
  * @}
  */

/** @defgroup RCC_AHB1_Reset AHB1 PeripheralReset
  * @brief  AHB1 peripheral reset.
  * @{
  */
/**
  * @details This function resets the GPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function resets the CORDIC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_CORDIC);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function resets the FMAC peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMAC_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_FMAC);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_FMAC);
}

/**
  * @details This function resets the MDF1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_MDF1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_MDF1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_MDF1);
}

/**
  * @details This function resets the CRC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRC_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_CRC);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_CRC);
}

#if defined(JPEG)
/**
  * @details This function resets the JPEG peripheral.
  */
__STATIC_INLINE void HAL_RCC_JPEG_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_JPEG);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_JPEG);
}
#endif /* JPEG */

/**
  * @details This function resets the TSC peripheral.
  */
__STATIC_INLINE void HAL_RCC_TSC_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_TSC);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_TSC);
}

/**
  * @details This function resets the RAMCFG peripheral.
  */
__STATIC_INLINE void HAL_RCC_RAMCFG_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_RAMCFG);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

#if defined (DMA2D)
/**
  * @details This function resets the DMA2D peripheral.
  */
__STATIC_INLINE void HAL_RCC_DMA2D_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA2D);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA2D);
}
#endif /* DMA2D */

#if defined(GFXMMU)
/**
  * @details This function resets the GFXMMU peripheral.
  */
__STATIC_INLINE void HAL_RCC_GFXMMU_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GFXMMU);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GFXMMU);
}
#endif /* GFXMMU */

#if defined(GPU2D)
/**
  * @details This function resets the GPU2D peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPU2D_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPU2D);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPU2D);
}
#endif /* GPU2D */
/**
  * @}
  */

/** @defgroup RCC_AHB2_Reset AHB2 Peripheral Reset
  * @brief  AHB2 peripheral reset.
  * @{
  */
/**
  * @details This function resets the GPIOA peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOA);
}
/**
  * @details This function resets the GPIOB peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function resets the GPIOC peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function resets the GPIOD peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOD);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function resets the GPIOE peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOE);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOE);
}

#if defined (GPIOF)
/**
  * @details This function resets the GPIOF peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOF);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOF);
}
#endif /* GPIOF */

/**
  * @details This function resets the GPIOG peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOG);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function resets the GPIOH peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOH);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOH);
}

#if defined (GPIOI)
/**
  * @details This function resets the GPIOI peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOI);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOI);
}
#endif /* GPIOI */

#if defined(GPIOJ)
/**
  * @details This function resets the GPIOJ peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOJ_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_GPIOJ);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
#endif /* GPIOJ */

/**
  * @details This function resets the ADC12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC12_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_ADC12);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_ADC12);
}

/**
  * @details This function resets the DCMI_PSSI peripheral.
  */
__STATIC_INLINE void HAL_RCC_DCMI_PSSI_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
}

#if defined(USB_OTG_HS)
/**
  * @details This function resets the USB_OTG_HS peripheral.
  */
__STATIC_INLINE void HAL_RCC_USB_OTG_HS_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_OTG_HS);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_OTG_HS);
}
#endif /* USB_OTG_HS */

#if defined (USB_OTG_FS)
/**
  * @details This function resets the USB_OTG_FS peripheral.
  */
__STATIC_INLINE void HAL_RCC_USB_OTG_FS_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_OTG_FS);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_OTG_FS);
}
#endif /* USB_OTG_FS */

#if defined(AES)
/**
  * @details This function resets the AES peripheral.
  */
__STATIC_INLINE void HAL_RCC_AES_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_AES);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_AES);
}
#endif  /* AES */

/**
  * @details This function resets the HASH peripheral.
  */
__STATIC_INLINE void HAL_RCC_HASH_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_HASH);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_HASH);
}

/**
  * @details This function resets the RNG peripheral.
  */
__STATIC_INLINE void HAL_RCC_RNG_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_RNG);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_RNG);
}

#if defined(PKA)
/**
  * @details This function resets the PKA peripheral.
  */
__STATIC_INLINE void HAL_RCC_PKA_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_PKA);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_PKA);
}
#endif /* PKA */

#if defined(SAES)
/**
  * @details This function resets the SAES peripheral.
  */
__STATIC_INLINE void HAL_RCC_SAES_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_SAES);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined (OCTOSPIM)
/**
  * @details This function resets the OCTOSPIM peripheral.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPIM_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
}
#endif /* OCTOSPIM */

#if defined(OTFDEC1)
/**
  * @details This function resets the OTFDEC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC1_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_OTFDEC1);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

#if defined(OTFDEC2)
/**
  * @details This function resets the OTFDEC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OTFDEC2_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_OTFDEC2);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_OTFDEC2);
}
#endif /* OTFDEC2 */

/**
  * @details This function resets the SDMMC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_SDMMC1);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_SDMMC1);
}

#if defined (SDMMC2)
/**
  * @details This function resets the SDMMC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SDMMC2_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_SDMMC2);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_SDMMC2);
}
#endif /* SDMMC2 */

#if defined (FMC_BASE)
/**
  * @details This function resets the FMSC peripheral.
  */
__STATIC_INLINE void HAL_RCC_FSMC_Reset(void)
{
  LL_AHB2_GRP2_ForceReset(LL_AHB2_GRP2_PERIPH_FSMC);
  LL_AHB2_GRP2_ReleaseReset(LL_AHB2_GRP2_PERIPH_FSMC);
}
#endif /* FMC_BASE */

/**
  * @details This function resets the OCTOSPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPI1_Reset(void)
{
  LL_AHB2_GRP2_ForceReset(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
  LL_AHB2_GRP2_ReleaseReset(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
}

#if defined (OCTOSPI2)
/**
  * @details This function resets the OCTOSPI2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_OCTOSPI2_Reset(void)
{
  LL_AHB2_GRP2_ForceReset(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
  LL_AHB2_GRP2_ReleaseReset(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
}
#endif /* OCTOSPI2 */

#if defined(HSPI1)
/**
  * @details This function resets the HSPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HSPI1_Reset(void)
{
  LL_AHB2_GRP2_ForceReset(LL_AHB2_GRP2_PERIPH_HSPI1);
  LL_AHB2_GRP2_ReleaseReset(LL_AHB2_GRP2_PERIPH_HSPI1);
}
#endif /* HSPI1 */
/**
  * @}
  */

/** @defgroup RCC_AHB3_Reset AHB3 Peripheral Reset
  * @brief  AHB3 peripheral reset.
  * @{
  */
/**
  * @details This function resets the LPGPIO1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPGPIO1_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_LPGPIO1);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_LPGPIO1);
}

/**
  * @details This function resets the ADC4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC4_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ADC4);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ADC4);
}

/**
  * @details This function resets the DAC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC1_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC1);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function resets the LPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPDMA1_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_LPDMA1);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_LPDMA1);
}

/**
  * @details This function resets the ADF1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADF1_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ADF1);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ADF1);
}
/**
  * @}
  */

/** @defgroup RCC_APB1_Reset APB1 Peripheral Reset
  * @brief  APB1 peripheral reset.
  * @{
  */
/**
  * @details This function resets the TIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function resets the TIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function resets the TIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM4_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM4);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function resets the TIM5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM5_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM5);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM5);
}


/**
  * @details This function resets the TIM6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM6_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM6);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function resets the TIM7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM7_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM7);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function resets the SPI2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined (USART2)
/**
  * @details This function resets the USART2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART2);
}
#endif /* USART2 */

/**
  * @details This function resets the USART3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function resets the UART4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART4_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART4);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function resets the UART5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART5_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART5);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function resets the I2C1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function resets the I2C2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function resets the CRS peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRS_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_CRS);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_CRS);
}

#if defined(USART6)
/**
  * @details This function resets the USART6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART6_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART6);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART6);
}
#endif /* USART6 */

/**
  * @details This function resets the I2C4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C4_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_I2C4);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_I2C4);
}

/**
  * @details This function resets the LPTIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_LPTIM2);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_LPTIM2);
}

#if defined(I2C5)
/**
  * @details This function resets the I2C5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C5_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_I2C5);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_I2C5);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @details This function resets the I2C6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C6_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_I2C6);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_I2C6);
}
#endif /* I2C6 */

/**
  * @details This function resets the FDCAN peripheral.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_FDCAN1);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_FDCAN1);
}

#if defined (UCPD1)
/**
  * @details This function resets the UCPD1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_UCPD1);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */
/**
  * @}
  */

/** @defgroup RCC_APB2_Reset APB2 Peripheral Reset
  * @brief  APB2 peripheral reset.
  * @{
  */
/**
  * @details This function resets the TIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function resets the SPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function resets the TIM8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM8_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM8);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function resets the USART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function resets the TIM15 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM15_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM15);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function resets the TIM16 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM16_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM16);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function resets the TIM17 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM17_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM17);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function resets the SAI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SAI1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SAI1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SAI1);
}

#if defined (SAI2)
/**
  * @details This function resets the SAI2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SAI2_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SAI2);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SAI2);
}
#endif /* SAI2 */

#if defined(GFXTIM)
/**
  * @details This function resets the GFXTIM peripheral.
  */
__STATIC_INLINE void HAL_RCC_GFXTIM_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_GFXTIM);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_GFXTIM);
}
#endif /* GFXTIM */

#if defined(LTDC)
/**
  * @details This function resets the LTDC peripheral.
  */
__STATIC_INLINE void HAL_RCC_LTDC_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_LTDC);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_LTDC);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @details This function resets the DSI peripheral.
  */
__STATIC_INLINE void HAL_RCC_DSI_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_DSI);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_DSI);
}
#endif /* DSI */

#if defined(USB_DRD_FS)
/**
  * @details This function resets the USB_FS peripheral.
  */
__STATIC_INLINE void HAL_RCC_USB_DRD_FS_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USB_FS);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USB_FS);
}
#endif /* USB_DRD_FS */

/**
  * @}
  */

/** @defgroup RCC_APB3_Reset APB3 Peripheral Reset
  * @brief  APB3 peripheral reset.
  * @{
  */
/**
  * @details This function resets the SYSCFG peripheral.
  */
__STATIC_INLINE void HAL_RCC_SYSCFG_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_SYSCFG);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_SYSCFG);
}

/**
  * @details This function resets the SPI3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI3_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_SPI3);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_SPI3);
}

/**
  * @details This function resets the LPUART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_LPUART1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function resets the I2C3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C3_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_I2C3);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_I2C3);
}

/**
  * @details This function resets the LPTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_LPTIM1);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function resets the LPTIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_LPTIM3);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function resets the LPTIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_LPTIM4);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function resets the OPAMP peripheral.
  */
__STATIC_INLINE void HAL_RCC_OPAMP_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_OPAMP);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_OPAMP);
}

/**
  * @details This function resets the COMP peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_COMP);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_COMP);
}

/**
  * @details This function resets the VREF peripheral.
  */
__STATIC_INLINE void HAL_RCC_VREF_Reset(void)
{
  LL_APB3_GRP1_ForceReset(LL_APB3_GRP1_PERIPH_VREF);
  LL_APB3_GRP1_ReleaseReset(LL_APB3_GRP1_PERIPH_VREF);
}
/**
  * @}
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enable_Disable AHB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
/**
  * @details This function enables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the GPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the CORDIC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the FMAC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_FMAC);
}

/**
  * @details This function enables the MDF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_MDF1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_MDF1);
}
/**
  * @details This function enables the MDF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_MDF1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_MDF1);
}

/**
  * @details This function enables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_CRC);
}

#if defined(JPEG)
/**
  * @details This function enables the JPEG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_JPEG_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_JPEG);
}
#endif /* JPEG */

/**
  * @details This function enables the TSC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TSC_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_TSC);
}

/**
  * @details This function enables the RAMCFG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RAMCFG_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

#if defined(DMA2D)
/**
  * @details This function enables the DMA2D clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DMA2D_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_DMA2D);
}
#endif /* DMA2D */

#if defined(GFXMMU)
/**
  * @details This function enables the GFXMMU clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GFXMMU_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_GFXMMU);
}
#endif /* GFXMMU */

#if defined(GPU2D)
/**
  * @details This function enables the GPU2D clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPU2D_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_GPU2D);
}
#endif /* GPU2D */

#if defined(DCACHE2)
/**
  * @details This function enables the DCACHE2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCACHE2_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_DCACHE2);
}
#endif /* DCACHE2 */

/**
  * @details This function enables the GTZC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GTZC1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_GTZC1);
}

/**
  * @details This function enables the BKPSRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPSRAM_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}
/**
  * @details This function enables the BKPSRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPSRAM_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}

/**
  * @details This function enables the ICACHE1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ICACHE1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_ICACHE1);
}

/**
  * @details This function enables the DCACHE1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCACHE1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_DCACHE1);
}

/**
  * @details This function enables the SRAM1 clock in sleep mode.
  */
__STATIC_FORCEINLINE void HAL_RCC_LP_SRAM1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_SRAM1);
}
/**
  * @details This function enables the SRAM1 clock in stop mode.
  */
__STATIC_FORCEINLINE void HAL_RCC_LP_SRAM1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB1_GRP1_EnableClockStopSleep(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @details This function disables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_GPDMA1);
}
/**
  * @details This function disables the GPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPDMA1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the CORDIC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CORDIC_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the FMAC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FMAC_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_FMAC);
}

/**
  * @details This function disables the MDF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_MDF1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_MDF1);
}
/**
  * @details This function disables the MDF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_MDF1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_MDF1);
}

/**
  * @details This function disables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FLASH_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRC_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_CRC);
}

#if defined(JPEG)
/**
  * @details This function disables the JPEG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_JPEG_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_JPEG);
}
#endif /* JPEG */

/**
  * @details This function disables the TSC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TSC_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_TSC);
}

/**
  * @details This function disables the RAMCFG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RAMCFG_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_RAMCFG);
}

#if defined(DMA2D)
/**
  * @details This function disables the DMA2D clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DMA2D_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_DMA2D);
}
#endif /* DMA2D */

#if defined(GFXMMU)
/**
  * @details This function disables the GFXMMU clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GFXMMU_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_GFXMMU);
}
#endif /* GFXMMU */

#if defined(GPU2D)
/**
  * @details This function disables the GPU2D clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPU2D_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_GPU2D);
}
#endif /* GPU2D */

#if defined(DCACHE2)
/**
  * @details This function disables the DCACHE2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCACHE2_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_DCACHE2);
}
#endif /* DCACHE2 */

/**
  * @details This function disables the GTZC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GTZC1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_GTZC1);
}

/**
  * @details This function disables the BKPSRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPSRAM_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}
/**
  * @details This function disables the BKPSRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_BKPSRAM_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_BKPSRAM);
}

/**
  * @details This function disables the ICACHE1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ICACHE1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_ICACHE1);
}

/**
  * @details This function disables the DCACHE1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCACHE1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_DCACHE1);
}

/**
  * @details This function disables the SRAM1 clock in sleep mode.
  */
__STATIC_FORCEINLINE void HAL_RCC_LP_SRAM1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_SRAM1);
}
/**
  * @details This function disables the SRAM1 clock in stop mode.
  */
__STATIC_FORCEINLINE void HAL_RCC_LP_SRAM1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockStopSleep(LL_AHB1_GRP1_PERIPH_SRAM1);
}

/**
  * @}
  */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enable_Disable AHB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
/**
  * @details This function enables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOA);
}
/**
  * @details This function enables the GPIOA clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOB);
}
/**
  * @details This function enables the GPIOB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOC);
}
/**
  * @details This function enables the GPIOC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOD clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOD);
}
/**
  * @details This function enables the GPIOD clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOE);
}
/**
  * @details This function enables the GPIOE clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOE);
}

#if defined(GPIOF)
/**
  * @details This function enables the GPIOF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOF);
}
/**
  * @details This function enables the GPIOF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOF);
}
#endif /* GPIOF */

/**
  * @details This function enables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOG);
}
/**
  * @details This function enables the GPIOG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOH);
}
/**
  * @details This function enables the GPIOH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOH);
}

#if defined(GPIOI)
/**
  * @details This function enables the GPIOI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOI);
}
/**
  * @details This function enables the GPIOI clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOI);
}
#endif /* GPIOI */

#if defined(GPIOJ)
/**
  * @details This function enables the GPIOJ clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOJ_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
/**
  * @details This function enables the GPIOJ clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOJ_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
#endif /* GPIOJ */

/**
  * @details This function enables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the DCMI_PSSI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCMI_PSSI_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
}

#if defined(USB_OTG_HS)
/**
  * @details This function enables the USB_OTG_HS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_OTG_HS_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTG_HS);
}
#endif /* USB_OTG_HS */

#if defined (USB_OTG_FS)
/**
  * @details This function enables the USB_OTG_FS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_OTG_FS_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTG_FS);
}
#endif /* USB_OTG_FS */

#if defined(USB_OTG_HS)
/**
  * @details This function enables the USBHSPHY clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USBHSPHY_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTGHSPHY);
}
#endif /* USB_OTG_HS */

#if defined(AES)
/**
  * @details This function enables the AES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AES_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_AES);
}
#endif /* AES */

#if defined(HASH)
/**
  * @details This function enables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_HASH);
}
#endif /* HASH */

/**
  * @details This function enables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_RNG);
}

#if defined(PKA)
/**
  * @details This function enables the PKA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PKA_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_PKA);
}
#endif /* PKA */

#if defined(SAES)
/**
  * @details This function enables the SAES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAES_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(OCTOSPIM)
/**
  * @details This function enables the OCTOSPIM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OCTOSPIM_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
}
#endif /* OCTOSPIM */

#if defined(OTFDEC1)
/**
  * @details This function enables the OTFDEC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTFDEC1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

#if defined(OTFDEC2)
/**
  * @details This function enables the OTFDEC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTFDEC2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTFDEC2);
}
#endif /* OTFDEC2 */

/**
  * @details This function enables the SDMMC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SDMMC1);
}

#if defined(SDMMC2)
/**
  * @details This function enables the SDMMC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SDMMC2);
}
#endif /* SDMMC2 */

/**
  * @details This function enables the SRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM2);
}
/**
  * @details This function enables the SRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM2);
}

#if defined (SRAM3_BASE)
/**
  * @details This function enables the SRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM3);
}
/**
  * @details This function enables the SRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB2_GRP1_EnableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined(FMC_BASE)
/**
  * @details This function enables the FSMC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FSMC_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_FSMC);
}
#endif /* FMC_BASE */

/**
  * @details This function enables the OCTOSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OCTOSPI1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
}

#if defined(OCTOSPI2)
/**
  * @details This function enables the OCTOSPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OCTOSPI2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
}
#endif /* OCTOSPI2 */

#if defined(HSPI1)
/**
  * @details This function enables the HSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HSPI1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_HSPI1);
}
#endif /* HSPI1 */

#if defined(SRAM6_BASE)
/**
  * @details This function enables the SRAM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM6_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM6);
}
/**
  * @details This function enables the SRAM6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM6_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM6);
}
#endif /* SRAM6_BASE */

#if defined(SRAM5_BASE)
/**
  * @details This function enables the SRAM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM5_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM5);
}
/**
  * @details This function enables the SRAM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM5_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB2_GRP2_EnableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM5);
}
#endif /* SRAM5_BASE */

/**
  * @details This function disables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOA);
}
/**
  * @details This function disables the GPIOA clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOA_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOB);
}
/**
  * @details This function disables the GPIOB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOB_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOC);
}
/**
  * @details This function disables the GPIOC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOC_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOD clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOD);
}
/**
  * @details This function disables the GPIOD clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOD_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOE);
}
/**
  * @details This function disables the GPIOE clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOE_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOE);
}

#if defined(GPIOF)
/**
  * @details This function disables the GPIOF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOF);
}
/**
  * @details This function disables the GPIOF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOF_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOF);
}
#endif /* GPIOF */

/**
  * @details This function disables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOG);
}
/**
  * @details This function disables the GPIOG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOG_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOH);
}
/**
  * @details This function disables the GPIOH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOH_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOH);
}

#if defined(GPIOI)
/**
  * @details This function disables the GPIOI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOI);
}
/**
  * @details This function disables the GPIOI clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOI_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOI);
}
#endif /* GPIOI */

#if defined(GPIOJ)
/**
  * @details This function disables the GPIOJ clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOJ_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
/**
  * @details This function disables the GPIOJ clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GPIOJ_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_GPIOJ);
}
#endif /* GPIOJ */

/**
  * @details This function disables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC12_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the DCMI_PSSI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DCMI_PSSI_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_DCMI_PSSI);
}

#if defined(USB_OTG_HS)
/**
  * @details This function disables the USB_OTG_HS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_OTG_HS_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTG_HS);
}
#endif /* USB_OTG_HS */

#if defined (USB_OTG_FS)
/**
  * @details This function disables the USB_OTG_FS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_OTG_FS_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTG_FS);
}
#endif /* USB_OTG_FS */

#if defined(USB_OTG_HS)
/**
  * @details This function disables the USBHSPHY clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USBHSPHY_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTGHSPHY);
}
#endif /* USB_OTG_HS */

#if defined(AES)
/**
  * @details This function disables the AES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_AES_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_AES);
}
#endif /* AES */

#if defined(HASH)
/**
  * @details This function disables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HASH_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_HASH);
}
#endif /* HASH */

/**
  * @details This function disables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RNG_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_RNG);
}

#if defined(PKA)
/**
  * @details This function disables the PKA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PKA_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_PKA);
}
#endif /* PKA */

#if defined(SAES)
/**
  * @details This function disables the SAES clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAES_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SAES);
}
#endif /* SAES */

#if defined(OCTOSPIM)
/**
  * @details This function disables the OCTOSPIM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OCTOSPIM_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_OCTOSPIM);
}
#endif /* OCTOSPIM */

#if defined(OTFDEC1)
/**
  * @details This function disables the OTFDEC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTFDEC1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTFDEC1);
}
#endif /* OTFDEC1 */

#if defined(OTFDEC2)
/**
  * @details This function disables the OTFDEC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OTFDEC2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_OTFDEC2);
}
#endif /* OTFDEC2 */

/**
  * @details This function disables the SDMMC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SDMMC1);
}

#if defined(SDMMC2)
/**
  * @details This function disables the SDMMC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SDMMC2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SDMMC2);
}
#endif /* SDMMC2 */

/**
  * @details This function disables the SRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM2);
}
/**
  * @details This function disables the SRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM2_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM2);
}

#if defined(SRAM3_BASE)
/**
  * @details This function disables the SRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM3);
}
/**
  * @details This function disables the SRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM3_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockStopSleep(LL_AHB2_GRP1_PERIPH_SRAM3);
}
#endif /* SRAM3_BASE */

#if defined(FMC_BASE)
/**
  * @details This function disables the FSMC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FSMC_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_FSMC);
}
#endif /* FMC_BASE */

/**
  * @details This function disables the OCTOSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OCTOSPI1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_OCTOSPI1);
}

#if defined(OCTOSPI2)
/**
  * @details This function disables the OCTOSPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OCTOSPI2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_OCTOSPI2);
}
#endif /* OCTOSPI2 */

#if defined(HSPI1)
/**
  * @details This function disables the HSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_HSPI1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_HSPI1);
}
#endif /* HSPI1 */

#if defined(SRAM6_BASE)
/**
  * @details This function disables the SRAM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM6_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM6);
}
/**
  * @details This function disables the SRAM6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM6_DisableClockInStopMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM6);
}
#endif /* SRAM6_BASE */

#if defined(SRAM5_BASE)
/**
  * @details This function disables the SRAM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM5_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM5);
}
/**
  * @details This function disables the SRAM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM5_DisableClockInStopMode(void)
{
  LL_AHB2_GRP2_DisableClockStopSleep(LL_AHB2_GRP2_PERIPH_SRAM5);
}
#endif /* SRAM5_BASE */

/**
  * @}
  */

/** @defgroup RCC_AHB3_Clock_Sleep_Enable_Disable AHB3SMENR Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB3SMENR peripheral clock during Low Power (Sleep and STOP ) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */
/**
  * @details This function enables the LPGPIO1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPGPIO1_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPGPIO1);
}
/**
  * @details This function enables the LPGPIO1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPGPIO1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPGPIO1);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPGPIO1);
}

/**
  * @details This function enables the PWR clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PWR_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_PWR);
}

/**
  * @details This function enables the ADC4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC4_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADC4);
}
/**
  * @details This function enables the ADC4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC4_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADC4);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_ADC4);
}

/**
  * @details This function enables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_DAC1);
}
/**
  * @details This function enables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_DAC1);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the LPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPDMA1);
}
/**
  * @details This function enables the LPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPDMA1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPDMA1);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPDMA1);
}

/**
  * @details This function enables the ADF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADF1);
}
/**
  * @details This function enables the ADF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2 */
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADF1);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_ADF1);
}

/**
  * @details This function enables the GTZC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GTZC2_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_GTZC2);
}

/**
  * @details This function enables the SRAM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM4_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_SRAM4);
}
/**
  * @details This function enables the SRAM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM4_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_AHB3_GRP1_EnableClockStopSleep(LL_AHB3_GRP1_PERIPH_SRAM4);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_SRAM4);
}

/**
  * @details This function disables the LPGPIO1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPGPIO1_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPGPIO1);
}
/**
  * @details This function disables the LPGPIO1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPGPIO1_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPGPIO1);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPGPIO1);
}

/**
  * @details This function disables the PWR clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_PWR_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_PWR);
}

/**
  * @details This function disables the ADC4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC4_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADC4);
}
/**
  * @details This function disables the ADC4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADC4_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADC4);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_ADC4);
}

/**
  * @details This function disables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_DAC1);
}
/**
  * @details This function disables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DAC1_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_DAC1);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the LPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPDMA1);
}
/**
  * @details This function disables the LPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPDMA1_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_LPDMA1);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPDMA1);
}

/**
  * @details This function disables the ADF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADF1);
}
/**
  * @details This function disables the ADF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_ADF1_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_ADF1);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the GTZC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GTZC2_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_GTZC2);
}

/**
  * @details This function disables the SRAM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM4_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_SRAM4);
}
/**
  * @details This function disables the SRAM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SRAM4_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockStopSleep(LL_AHB3_GRP1_PERIPH_SRAM4);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_SRAM4);
}

/**
  * @}
  */

/** @defgroup RCC_APB1_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests APB clock.
  * @{
  */
/**
  * @details This function enables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM7_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the SPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_SPI2);
}
/**
  * @details This function enables the SPI2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined(USART2)
/**
  * @details This function enables the USART2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_USART2);
}
/**
  * @details This function enables the USART2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_USART2);
}
#endif /* USART2 */

/**
  * @details This function enables the USART3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_USART3);
}
/**
  * @details This function enables the USART3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the UART4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_UART4);
}
/**
  * @details This function enables the UART4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_UART5);
}
/**
  * @details This function enables the UART5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the I2C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C1);
}
/**
  * @details This function enables the I2C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C2);
}
/**
  * @details This function enables the I2C2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_CRS);
}

#if defined(USART6)
/**
  * @details This function enables the USART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_USART6);
}
/**
  * @details This function enables the USART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP1_EnableClockStopSleep(LL_APB1_GRP1_PERIPH_USART6);
}
#endif /* USART6 */

/**
  * @details This function enables the I2C4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C4);
}
/**
  * @details This function enables the I2C4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C4);
}

/**
  * @details This function enables the LPTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_LPTIM2);
}
/**
  * @details This function enables the LPTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_LPTIM2);
}

#if defined(I2C5)
/**
  * @details This function enables the I2C5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C5);
}
/**
  * @details This function enables the I2C5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C5_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C5);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @details This function enables the I2C6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C6_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C6);
}
/**
  * @details This function enables the I2C6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C6_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C6);
}
#endif /* I2C6 */

/**
  * @details This function enables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_FDCAN1);
}

#if defined(UCPD1)
/**
  * @details This function enables the UCPD1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UCPD1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockStopSleep(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @details This function disables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM6_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM7_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_WWDG_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the SPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_SPI2);
}
/**
  * @details This function disables the SPI2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_SPI2);
}

#if defined(USART2)
/**
  * @details This function disables the USART2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_USART2);
}
/**
  * @details This function disables the USART2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_USART2);
}
#endif /* USART2 */

/**
  * @details This function disables the USART3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_USART3);
}
/**
  * @details This function disables the USART3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the UART4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_UART4);
}
/**
  * @details This function disables the UART4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART4_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_UART5);
}
/**
  * @details This function disables the UART5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UART5_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the I2C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C1);
}
/**
  * @details This function disables the I2C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C2);
}
/**
  * @details This function disables the I2C2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_CRS_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_CRS);
}

#if defined(USART6)
/**
  * @details This function disables the USART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_USART6);
}
/**
  * @details This function disables the USART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART6_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockStopSleep(LL_APB1_GRP1_PERIPH_USART6);
}
#endif /* USART6 */

/**
  * @details This function disables the I2C4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C4);
}
/**
  * @details This function disables the I2C4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C4_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C4);
}

/**
  * @details This function disables the LPTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_LPTIM2);
}
/**
  * @details This function disables the LPTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM2_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_LPTIM2);
}

#if defined(I2C5)
/**
  * @details This function disables the I2C5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C5);
}
/**
  * @details This function disables the I2C5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C5_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C5);
}
#endif /* I2C5 */

#if defined(I2C6)
/**
  * @details This function disables the I2C6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C6_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C6);
}
/**
  * @details This function disables the I2C6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C6_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_I2C6);
}
#endif /* I2C6 */

/**
  * @details This function disables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_FDCAN_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_FDCAN1);
}

#if defined(UCPD1)
/**
  * @details This function disables the UCPD1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_UCPD1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockStopSleep(LL_APB1_GRP2_PERIPH_UCPD1);
}
#endif /* UCPD1 */

/**
  * @}
  */

/** @defgroup RCC_APB2_Clock_Sleep_Enable_Disable APB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP mode, the pseripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests APB clock.
  * @{
  */
/**
  * @details This function enables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the SPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_SPI1);
}
/**
  * @details This function enables the SPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the USART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_USART1);
}
/**
  * @details This function enables the USART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0 and 1 */
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM16 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM16_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the SAI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAI1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_SAI1);
}

#if defined(SAI2)
/**
  * @details This function enables the SAI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAI2_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_SAI2);
}
#endif /* SAI2 */

#if defined(GFXTIM)
/**
  * @details This function enables the GFXTIM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GFXTIM_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_GFXTIM);
}
#endif /* GFXTIM */

#if defined(LTDC)
/**
  * @details This function enables the LTDC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LTDC_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_LTDC);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @details This function enables the DSI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DSI_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_DSI);
}
#endif /* DSI */

#if defined(USB_DRD_FS)
/**
  * @details This function enables the USB_FS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_DRD_FS_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockStopSleep(LL_APB2_GRP1_PERIPH_USB_FS);
}
#endif /* USB_DRD_FS */

/**
  * @details This function disables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the SPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_SPI1);
}
/**
  * @details This function disables the SPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM8_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the USART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_USART1);
}
/**
  * @details This function disables the USART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USART1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM15_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM16 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM16_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_TIM17_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the SAI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAI1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_SAI1);
}

#if defined(SAI2)
/**
  * @details This function disables the SAI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SAI2_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_SAI2);
}
#endif /* SAI2 */

#if defined(GFXTIM)
/**
  * @details This function disables the GFXTIM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_GFXTIM_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_GFXTIM);
}
#endif /* GFXTIM */

#if defined(LTDC)
/**
  * @details This function disables the LTDC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LTDC_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_LTDC);
}
#endif /* LTDC */

#if defined(DSI)
/**
  * @details This function disables the DSI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_DSI_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_DSI);
}
#endif /* DSI */

#if defined(USB_DRD_FS)
/**
  * @details This function disables the USB_FS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_USB_DRD_FS_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockStopSleep(LL_APB2_GRP1_PERIPH_USB_FS);
}
#endif /* USB_DRD_FS */

/**
  * @}
  */

/** @defgroup RCC_APB3_Clock_Sleep_Enable_Disable APB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB3 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce
  *         power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode,in STOP mode peripheral clock
  *         is enabled only when a peripheral requests APB clock.
  * @{
  */
/**
  * @details This function enables the SYSCFG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SYSCFG_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_SYSCFG);
}

/**
  * @details This function enables the SPI3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_SPI3);
}
/**
  * @details This function enables the SPI3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_SPI3);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPUART1);
}
/**
  * @details This function enables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPUART1);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_I2C3);
}
/**
  * @details This function enables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_I2C3);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM1);
}
/**
  * @details This function enables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM1);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the LPTIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM3);
}
/**
  * @details This function enables the LPTIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM3);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM4);
}
/**
  * @details This function enables the LPTIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM4);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the OPAMP clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_OPAMP);
}
/**
  * @details This function enables the OPAMP clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_OPAMP);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_OPAMP);
}

/**
  * @details This function enables the COMP clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_COMP);
}
/**
  * @details This function enables the COMP clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_COMP);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_COMP);
}

/**
  * @details This function enables the VREF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREF_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_VREF);
}
/**
  * @details This function enables the VREF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREF_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1 and 2*/
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_VREF);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_VREF);
}

/**
  * @details This function enables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_EnableClockInSleepMode(void)
{
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_RTCAPB);
}
/**
  * @details This function enables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_EnableClockInStopMode(void)
{
  /* Permitted stop modes : 0, 1, 2 and 3 */
  LL_APB3_GRP1_EnableClockStopSleep(LL_APB3_GRP1_PERIPH_RTCAPB);
  LL_SRDAMR_GRP1_EnableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the SYSCFG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SYSCFG_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_SYSCFG);
}

/**
  * @details This function disables the SPI3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_SPI3);
}
/**
  * @details This function disables the SPI3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_SPI3_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_SPI3);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPUART1);
}
/**
  * @details This function disables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPUART1_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPUART1);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_I2C3);
}
/**
  * @details This function disables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_I2C3_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_I2C3);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM1);
}
/**
  * @details This function disables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM1_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM1);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the LPTIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM3);
}
/**
  * @details This function disables the LPTIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM3_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM3);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM4);
}
/**
  * @details This function disables the LPTIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_LPTIM4_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_LPTIM4);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the OPAMP clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_OPAMP);
}
/**
  * @details This function disables the OPAMP clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_OPAMP_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_OPAMP);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_OPAMP);
}

/**
  * @details This function disables the COMP clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_COMP);
}
/**
  * @details This function disables the COMP clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_COMP_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_COMP);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_COMP);
}

/**
  * @details This function disables the VREF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREF_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_VREF);
}
/**
  * @details This function disables the VREF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_VREF_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_VREF);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_VREF);
}

/**
  * @details This function disables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_DisableClockInSleepMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_RTCAPB);
}
/**
  * @details This function disables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LP_RTCAPB_DisableClockInStopMode(void)
{
  LL_APB3_GRP1_DisableClockStopSleep(LL_APB3_GRP1_PERIPH_RTCAPB);
  LL_SRDAMR_GRP1_DisableAutonomousClock(LL_SRDAMR_GRP1_PERIPH_RTCAPB);
}

/**
  * @}
  */

/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief    Function to force and release the Backup domain.
  * @details  When a Backup domain reset occurs, the following domains are impacted:
  *           - the RTC is stopped and all the RTC registers are set to their reset values
  *             (including the backup registers)
  *           - all TAMP registers can be read or written in both secure and non-secure modes.
  *             The secure boot code can change this security setup, making some registers secure
  *             or not as needed, using TAMP_SECCFGR register.
  *           - The SRAM2 and BKPSRAM are affected by this reset.
  *           - LSE crystal 32kHz oscillator
  *           - RCC_BDCR register
  */
__STATIC_INLINE void HAL_RCC_ResetBackupDomain(void)
{
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group3 RCC services functions
  This subsection provides a set of functions allowing to:

  - Configure the MCO.
    - MCO (Microcontroller Clock Output): used to output MSIS, MSIK, LSI, HSI16, HSI48, LSE, HSE,
    SYSCLK or main PLL clock (through a configurable prescaler) on a pin.

  - Get and clear reset flags

  - Enable the Clock Security System.
    - CSS (Clock Security System): once enabled, if a HSE clock failure occurs
    (HSE used directly or through PLL as System clock source), the System clock
    is automatically switched of the system clock to the MSIS or the HSI16 oscillator
    depending on the STOPWUCK configuration.
    The CSS interrupt is linked to the Cortex-M33 NMI (non-maskable interrupt) exception vector.
    The NMI is executed indefinitely unless the CSSI pending bit is cleared. As a consequence, in the NMI ISR, the user
    must clear the CSSI by setting the CSSC bit.

  - Enable Clock security system on LSE.

  - Configure and get the oscillator clock source for wakeup from Stop and CSS backup clock.

  - Configure and get the oscillator Kernel clock source for wakeup from Stop.

  - Enable output (LSCO) allows one of the low-speed clocks below to be output onto the external LSCO pin:
    - LSI
    - LSE
    This output remains available in all Stop modes, Standby and Shutdown modes

  - Enable RTC and TAMP clock

  - Set the Clocks sources for TIM16,TIM17 and LPTIM2 internal input capture
  *
  * @{
  */

void                         HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mco_src, hal_rcc_mco_prescaler_t mco_div);
uint32_t                     HAL_RCC_GetResetSource(void);
#if defined(HSE_VALUE)
void                         HAL_RCC_HSE_EnableCSS(void);
hal_status_t                 HAL_RCC_NMI_IRQHandler(void);
hal_status_t                 HAL_RCC_HSE_CSSCallback(void);
#endif /* HSE_VALUE */
void                         HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk);
hal_rcc_stop_wakeup_clk_t    HAL_RCC_GetClockAfterWakeFromStop(void);
void                         HAL_RCC_SetKernelClkAfterWakeFromStop(hal_rcc_stop_wakeup_kerclk_t wakeup_clk);
hal_rcc_stop_wakeup_kerclk_t HAL_RCC_GetKernelClkAfterWakeFromStop(void);
#if defined(LSE_VALUE)
void                         HAL_RCC_LSE_EnableCSS(void);
void                         HAL_RCC_LSE_DisableCSS(void);
void                         HAL_RCC_LSECSS_IRQHandler(void);
void                         HAL_RCC_LSE_CSSCallback(void);
void                         HAL_RCC_MSI_PLLUnlock_IRQHandler(void);
void                         HAL_RCC_MSI_PLLUnlock_Callback(void);
#endif /* LSE_VALUE */
hal_status_t                 HAL_RCC_EnableLSCO(hal_rcc_lsco_src_t source);
hal_status_t                 HAL_RCC_DisableLSCO(void);
hal_status_t                 HAL_RCC_RTC_EnableKernelClock(void);
hal_status_t                 HAL_RCC_RTC_DisableKernelClock(void);
hal_status_t                 HAL_RCC_SetTimerInputCaptureClockSource(hal_rcc_timic_clk_src_t clk_src);
hal_rcc_timic_clk_src_t      HAL_RCC_GetTimerInputCaptureClockSource(void);

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group4 Kernel clock source configuration for peripherals
  This subsection provides a set of functions:
  - to control Kernel clock source configuration for peripherals

  Only functions having a kernel clock are handled by these functions.

    The peripheral clock can be selected through the independent API
    HAL_RCC_{PERIPHx}_SetKernelClkSource(hal_rcc_{periphx}_clk_src_t clk_src)
    example: @ref HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src)

    Usage: activate SYSCLK as clock source of USART1

    - with @ref HAL_RCC_USART1_SetKernelClkSource function:
    @code
      HAL_RCC_USART1_SetKernelClkSource(HAL_RCC_USART1_CLK_SRC_SYSCLK);
    @endcode

    - to get the peripheral Clocks frequencies:
      hal_rcc_{periphx}_clk_src_t HAL_RCC_{PERIPHx}_GetKernelClkSource(void)

  * @{
  */

hal_status_t             HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src);
#if defined (USART2)
hal_status_t             HAL_RCC_USART2_SetKernelClkSource(hal_rcc_usart2_clk_src_t clk_src);
#endif /* USART2 */
hal_status_t             HAL_RCC_USART3_SetKernelClkSource(hal_rcc_usart3_clk_src_t clk_src);
hal_status_t             HAL_RCC_UART4_SetKernelClkSource(hal_rcc_uart4_clk_src_t clk_src);
hal_status_t             HAL_RCC_UART5_SetKernelClkSource(hal_rcc_uart5_clk_src_t clk_src);
#if defined(USART6)
hal_status_t             HAL_RCC_USART6_SetKernelClkSource(hal_rcc_usart6_clk_src_t clk_src);
#endif /* USART6 */
hal_status_t             HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src);
hal_status_t             HAL_RCC_I2C1_SetKernelClkSource(hal_rcc_i2c1_clk_src_t clk_src);
hal_status_t             HAL_RCC_I2C2_SetKernelClkSource(hal_rcc_i2c2_clk_src_t clk_src);
hal_status_t             HAL_RCC_I2C3_SetKernelClkSource(hal_rcc_i2c3_clk_src_t clk_src);
hal_status_t             HAL_RCC_I2C4_SetKernelClkSource(hal_rcc_i2c4_clk_src_t clk_src);
#if defined(I2C5)
hal_status_t             HAL_RCC_I2C5_SetKernelClkSource(hal_rcc_i2c5_clk_src_t clk_src);
#endif /* I2C5 */
#if defined(I2C6)
hal_status_t             HAL_RCC_I2C6_SetKernelClkSource(hal_rcc_i2c6_clk_src_t clk_src);
#endif /* I2C6 */
hal_status_t             HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src);
hal_status_t             HAL_RCC_LPTIM2_SetKernelClkSource(hal_rcc_lptim2_clk_src_t clk_src);
hal_status_t             HAL_RCC_LPTIM34_SetKernelClkSource(hal_rcc_lptim34_clk_src_t clk_src);
hal_status_t             HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src);
hal_status_t             HAL_RCC_MDF1_SetKernelClkSource(hal_rcc_mdf1_clk_src_t clk_src);
hal_status_t             HAL_RCC_ADF1_SetKernelClkSource(hal_rcc_adf1_clk_src_t clk_src);
hal_status_t             HAL_RCC_SAI1_SetKernelClkSource(hal_rcc_sai1_clk_src_t clk_src);
#if defined (SAI2)
hal_status_t             HAL_RCC_SAI2_SetKernelClkSource(hal_rcc_sai2_clk_src_t clk_src);
#endif /* SAI2 */
hal_status_t             HAL_RCC_RNG_SetKernelClkSource(hal_rcc_rng_clk_src_t clk_src);
#if defined(SAES)
hal_status_t             HAL_RCC_SAES_SetKernelClkSource(hal_rcc_saes_clk_src_t clk_src);
#endif /* SAES */
hal_status_t             HAL_RCC_ICLK_SetKernelClkSource(hal_rcc_iclk_clk_src_t clk_src);
hal_status_t             HAL_RCC_SDMMC_SetKernelClkSource(hal_rcc_sdmmc_clk_src_t clk_src);
hal_status_t             HAL_RCC_ADCDAC_SetKernelClkSource(hal_rcc_adcdac_clk_src_t clk_src);
hal_status_t             HAL_RCC_DAC1_SetSampleAndHoldClkSource(hal_rcc_dac1_clk_src_t clk_src);
hal_status_t             HAL_RCC_OCTOSPI_SetKernelClkSource(hal_rcc_octospi_clk_src_t clk_src);
#if defined(HSPI1)
hal_status_t             HAL_RCC_HSPI1_SetKernelClkSource(hal_rcc_hspi1_clk_src_t clk_src);
#endif /* HSPI1 */
hal_status_t             HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src);
hal_status_t             HAL_RCC_SPI2_SetKernelClkSource(hal_rcc_spi2_clk_src_t clk_src);
hal_status_t             HAL_RCC_SPI3_SetKernelClkSource(hal_rcc_spi3_clk_src_t clk_src);
hal_status_t             HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src);
#if defined(LTDC)
hal_status_t             HAL_RCC_LTDC_SetKernelClkSource(hal_rcc_ltdc_clk_src_t clk_src);
#endif /* LTDC */
#if defined(DSI)
hal_status_t             HAL_RCC_DSI_SetKernelClkSource(hal_rcc_dsi_clk_src_t clk_src);
#endif /* DSI */
#if defined(USB_OTG_HS)
hal_status_t             HAL_RCC_USBHSPHY_SetKernelClkSource(hal_rcc_usbhsphy_clk_src_t clk_src);
#endif /* USB_OTG_HS */

hal_rcc_usart1_clk_src_t HAL_RCC_USART1_GetKernelClkSource(void);
#if defined (USART2)
hal_rcc_usart2_clk_src_t HAL_RCC_USART2_GetKernelClkSource(void);
#endif /* USART2 */
hal_rcc_usart3_clk_src_t HAL_RCC_USART3_GetKernelClkSource(void);
hal_rcc_uart4_clk_src_t  HAL_RCC_UART4_GetKernelClkSource(void);
hal_rcc_uart5_clk_src_t  HAL_RCC_UART5_GetKernelClkSource(void);
#if defined(USART6)
hal_rcc_usart6_clk_src_t HAL_RCC_USART6_GetKernelClkSource(void);
#endif /* USART6 */
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void);
hal_rcc_i2c1_clk_src_t    HAL_RCC_I2C1_GetKernelClkSource(void);
hal_rcc_i2c2_clk_src_t    HAL_RCC_I2C2_GetKernelClkSource(void);
hal_rcc_i2c3_clk_src_t    HAL_RCC_I2C3_GetKernelClkSource(void);
hal_rcc_i2c4_clk_src_t    HAL_RCC_I2C4_GetKernelClkSource(void);
#if defined(I2C5)
hal_rcc_i2c5_clk_src_t    HAL_RCC_I2C5_GetKernelClkSource(void);
#endif /* I2C5 */
#if defined(I2C6)
hal_rcc_i2c6_clk_src_t    HAL_RCC_I2C6_GetKernelClkSource(void);
#endif /* I2C6 */
hal_rcc_lptim1_clk_src_t  HAL_RCC_LPTIM1_GetKernelClkSource(void);
hal_rcc_lptim2_clk_src_t  HAL_RCC_LPTIM2_GetKernelClkSource(void);
hal_rcc_lptim34_clk_src_t HAL_RCC_LPTIM34_GetKernelClkSource(void);
hal_rcc_fdcan_clk_src_t   HAL_RCC_FDCAN_GetKernelClkSource(void);
hal_rcc_mdf1_clk_src_t    HAL_RCC_MDF1_GetKernelClkSource(void);
hal_rcc_adf1_clk_src_t    HAL_RCC_ADF1_GetKernelClkSource(void);
hal_rcc_sai1_clk_src_t    HAL_RCC_SAI1_GetKernelClkSource(void);
#if defined (SAI2)
hal_rcc_sai2_clk_src_t    HAL_RCC_SAI2_GetKernelClkSource(void);
#endif /* SAI2 */
hal_rcc_rng_clk_src_t     HAL_RCC_RNG_GetKernelClkSource(void);
#if defined(SAES)
hal_rcc_saes_clk_src_t    HAL_RCC_SAES_GetKernelClkSource(void);
#endif /* SAES */
hal_rcc_iclk_clk_src_t    HAL_RCC_ICLK_GetKernelClkSource(void);
hal_rcc_sdmmc_clk_src_t   HAL_RCC_SDMMC_GetKernelClkSource(void);
hal_rcc_adcdac_clk_src_t  HAL_RCC_ADCDAC_GetKernelClkSource(void);
hal_rcc_dac1_clk_src_t    HAL_RCC_DAC1_GetSampleHoldClkSource(void);
hal_rcc_octospi_clk_src_t HAL_RCC_OCTOSPI_GetKernelClkSource(void);
#if defined(HSPI1)
hal_rcc_hspi1_clk_src_t   HAL_RCC_HSPI1_GetKernelClkSource(void);
#endif /* HSPI1 */
hal_rcc_spi1_clk_src_t    HAL_RCC_SPI1_GetKernelClkSource(void);
hal_rcc_spi2_clk_src_t    HAL_RCC_SPI2_GetKernelClkSource(void);
hal_rcc_spi3_clk_src_t    HAL_RCC_SPI3_GetKernelClkSource(void);
hal_rcc_rtc_clk_src_t     HAL_RCC_RTC_GetKernelClkSource(void);
#if defined(LTDC)
hal_rcc_ltdc_clk_src_t    HAL_RCC_LTDC_GetKernelClkSource(void);
#endif /* LTDC */
#if defined(DSI)
hal_rcc_dsi_clk_src_t     HAL_RCC_DSI_GetKernelClkSource(void);
#endif /* DSI */
#if defined(USB_OTG_HS)
hal_rcc_usbhsphy_clk_src_t  HAL_RCC_USBHSPHY_GetKernelClkSource(void);
#endif /* USB_OTG_HS */

uint32_t                 HAL_RCC_RTC_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_SAI_GetKernelClkFreq(const SAI_TypeDef *saix);
uint32_t                 HAL_RCC_SAI1_GetKernelClkFreq(void);
#if defined (SAI2)
uint32_t                 HAL_RCC_SAI2_GetKernelClkFreq(void);
#endif /* SAI2 */
#if defined(SAES)
uint32_t                 HAL_RCC_SAES_GetKernelClkFreq(void);
#endif /* SAES */
uint32_t                 HAL_RCC_ICLK_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_SDMMC_GetKernelClkFreq(const SDMMC_TypeDef *sdmmcx);
uint32_t                 HAL_RCC_SDMMC12_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx);
uint32_t                 HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx);
uint32_t                 HAL_RCC_USART1_GetKernelClkFreq(void);
#if defined (USART2)
uint32_t                 HAL_RCC_USART2_GetKernelClkFreq(void);
#endif /* USART2 */
uint32_t                 HAL_RCC_USART3_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_UART4_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_UART5_GetKernelClkFreq(void);
#if defined(USART6)
uint32_t                 HAL_RCC_USART6_GetKernelClkFreq(void);
#endif /* USART6 */
uint32_t                 HAL_RCC_LPUART1_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_ADC_GetKernelClkFreq(const ADC_TypeDef *adcx);
uint32_t                 HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx);
uint32_t                 HAL_RCC_ADCDAC_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_MDF1_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_ADF1_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx);
uint32_t                 HAL_RCC_I2C1_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_I2C2_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_I2C3_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_I2C4_GetKernelClkFreq(void);
#if defined (I2C5)
uint32_t                 HAL_RCC_I2C5_GetKernelClkFreq(void);
#endif /* I2C5 */
#if defined (I2C6)
uint32_t                 HAL_RCC_I2C6_GetKernelClkFreq(void);
#endif /* I2C6 */
uint32_t                 HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx);
uint32_t                 HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx);
uint32_t                 HAL_RCC_LPTIM34_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_LPTIM1_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_LPTIM2_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_FDCAN_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix);
uint32_t                 HAL_RCC_SPI1_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_SPI2_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_SPI3_GetKernelClkFreq(void);
uint32_t                 HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix);
uint32_t                 HAL_RCC_OCTOSPI_GetKernelClkFreq(void);
#if defined(HSPI1)
uint32_t                 HAL_RCC_HSPI1_GetKernelClkFreq(void);
#endif /* HSPI1 */
uint32_t                 HAL_RCC_DAC1_GetSampleHoldClkFreq(void);
uint32_t                 HAL_RCC_RNG_GetKernelClkFreq(void);
#if defined(LTDC)
uint32_t                 HAL_RCC_LTDC_GetKernelClkFreq(void);
#endif /* LTDC */
#if defined(DSI)
uint32_t                 HAL_RCC_DSI_GetKernelClkFreq(void);
#endif /* DSI */
#if defined(USB_OTG_HS)
uint32_t                 HAL_RCC_USBHSPHY_GetKernelClkFreq(void);
#endif /* USB_OTG_HS */

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
#endif

#endif /* STM32U5XX_HAL_RCC_H */
