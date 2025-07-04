/**
  ******************************************************************************
  * @file    stm32u5xx_ll_rcc.h
  * @brief   Header file of RCC LL module.
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
#ifndef STM32U5XX_LL_RCC_H
#define STM32U5XX_LL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @defgroup RCC_LL RCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_LL_Private_Constants RCC Private Constants
  * @{
  */
/* Defines used to perform offsets*/
/* Offset used to access to RCC_CCIPR1 and RCC_CCIPR2 registers */
#define RCC_OFFSET_CCIPR1       0U
#define RCC_OFFSET_CCIPR2       0x04U
#define RCC_OFFSET_CCIPR3       0x08U

/* Defines used for security configuration extension */
#define RCC_SECURE_MASK         0x1FFFU
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Constants RCC Exported Constants
  * @{
  */

/** @defgroup RCC_LL_EC_LSIPRE  LSI prescaler
  * @{
  */
#define LL_RCC_LSI_DIV_1                   0x00000000U          /*!< LSI divided by 1   */
#define LL_RCC_LSI_DIV_128                 RCC_BDCR_LSIPREDIV   /*!< LSI divided by 128 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define LL_RCC_LSEDRIVE_LOW                0x00000000U             /*!< Xtal mode lower driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMLOW          RCC_BDCR_LSEDRV_0       /*!< Xtal mode medium low driving capability */
#define LL_RCC_LSEDRIVE_MEDIUMHIGH         RCC_BDCR_LSEDRV_1       /*!< Xtal mode medium high driving capability */
#define LL_RCC_LSEDRIVE_HIGH               RCC_BDCR_LSEDRV         /*!< Xtal mode higher driving capability */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSI_OSCILLATOR MSI clock Trimming
  * @{
  */
#define LL_RCC_MSI_OSCILLATOR_0            0x00000000U     /*!< MSI clock trimming for ranges 0 to 3 */
#define LL_RCC_MSI_OSCILLATOR_1            0x00000005U     /*!< MSI clock trimming for ranges 4 to 7 */
#define LL_RCC_MSI_OSCILLATOR_2            0x0000000AU     /*!< MSI clock trimming for ranges 8 to 11 */
#define LL_RCC_MSI_OSCILLATOR_3            0x0000000FU     /*!< MSI clock trimming for ranges 12 to 15 */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_MSISRANGE MSIS Clock Range
  * @{
  */
#define LL_RCC_MSISRANGE_0                  0x00000000U                                                                                        /*!< MSIS = 48 MHz    */
#define LL_RCC_MSISRANGE_1                  RCC_ICSCR1_MSISRANGE_0                                                                             /*!< MSIS = 24 MHz    */
#define LL_RCC_MSISRANGE_2                  RCC_ICSCR1_MSISRANGE_1                                                                             /*!< MSIS = 16 MHz    */
#define LL_RCC_MSISRANGE_3                  (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_1)                                                  /*!< MSIS = 12 MHz    */
#define LL_RCC_MSISRANGE_4                  RCC_ICSCR1_MSISRANGE_2                                                                             /*!< MSIS = 4 MHz     */
#define LL_RCC_MSISRANGE_5                  (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_2)                                                  /*!< MSIS = 2 MHz     */
#define LL_RCC_MSISRANGE_6                  (RCC_ICSCR1_MSISRANGE_1 | RCC_ICSCR1_MSISRANGE_2)                                                  /*!< MSIS = 1.5 MHz   */
#define LL_RCC_MSISRANGE_7                  (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_1 | RCC_ICSCR1_MSISRANGE_2)                         /*!< MSIS = 1 MHz     */
#define LL_RCC_MSISRANGE_8                   RCC_ICSCR1_MSISRANGE_3                                                                            /*!< MSIS = 3.072 MHz */
#define LL_RCC_MSISRANGE_9                  (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_3)                                                  /*!< MSIS = 1.536 MHz */
#define LL_RCC_MSISRANGE_10                 (RCC_ICSCR1_MSISRANGE_1 | RCC_ICSCR1_MSISRANGE_3)                                                  /*!< MSIS = 1.024 MHz */
#define LL_RCC_MSISRANGE_11                 (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_1 | RCC_ICSCR1_MSISRANGE_3)                         /*!< MSIS = 768 kHz   */
#define LL_RCC_MSISRANGE_12                 (RCC_ICSCR1_MSISRANGE_2 | RCC_ICSCR1_MSISRANGE_3)                                                  /*!< MSIS = 400 kHz   */
#define LL_RCC_MSISRANGE_13                 (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_2 | RCC_ICSCR1_MSISRANGE_3)                         /*!< MSIS = 200 kHz   */
#define LL_RCC_MSISRANGE_14                 (RCC_ICSCR1_MSISRANGE_1 | RCC_ICSCR1_MSISRANGE_2 | RCC_ICSCR1_MSISRANGE_3)                         /*!< MSIS = 150 kHz   */
#define LL_RCC_MSISRANGE_15                 (RCC_ICSCR1_MSISRANGE_0 | RCC_ICSCR1_MSISRANGE_1| RCC_ICSCR1_MSISRANGE_2 | \
                                             RCC_ICSCR1_MSISRANGE_3) /*!< MSIS = 100 kHz   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIKRANGE MSIK Clock Range
  * @{
  */
#define LL_RCC_MSIKRANGE_0                 0x00000000U                                                                                         /*!< MSIK = 48 MHz    */
#define LL_RCC_MSIKRANGE_1                 RCC_ICSCR1_MSIKRANGE_0                                                                              /*!< MSIK = 24 MHz    */
#define LL_RCC_MSIKRANGE_2                 RCC_ICSCR1_MSIKRANGE_1                                                                              /*!< MSIK = 16 MHz    */
#define LL_RCC_MSIKRANGE_3                 (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_1)                                                   /*!< MSIK = 12 MHz    */
#define LL_RCC_MSIKRANGE_4                 RCC_ICSCR1_MSIKRANGE_2                                                                              /*!< MSIK = 4 MHz     */
#define LL_RCC_MSIKRANGE_5                 (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_2)                                                   /*!< MSIK = 2 MHz     */
#define LL_RCC_MSIKRANGE_6                 (RCC_ICSCR1_MSIKRANGE_1 | RCC_ICSCR1_MSIKRANGE_2)                                                   /*!< MSIK = 1.5 MHz   */
#define LL_RCC_MSIKRANGE_7                 (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_1 | RCC_ICSCR1_MSIKRANGE_2)                          /*!< MSIK = 1 MHz     */
#define LL_RCC_MSIKRANGE_8                  RCC_ICSCR1_MSIKRANGE_3                                                                             /*!< MSIK = 3.072 MHz */
#define LL_RCC_MSIKRANGE_9                 (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_3)                                                   /*!< MSIK = 1.536 MHz */
#define LL_RCC_MSIKRANGE_10                (RCC_ICSCR1_MSIKRANGE_1 | RCC_ICSCR1_MSIKRANGE_3)                                                   /*!< MSIK = 1.024 MHz */
#define LL_RCC_MSIKRANGE_11                (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_1 | RCC_ICSCR1_MSIKRANGE_3)                          /*!< MSIK = 768 kHz   */
#define LL_RCC_MSIKRANGE_12                (RCC_ICSCR1_MSIKRANGE_2 | RCC_ICSCR1_MSIKRANGE_3)                                                   /*!< MSIK = 400 kHz   */
#define LL_RCC_MSIKRANGE_13                (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_2 | RCC_ICSCR1_MSIKRANGE_3)                          /*!< MSIK = 200 kHz   */
#define LL_RCC_MSIKRANGE_14                (RCC_ICSCR1_MSIKRANGE_1 | RCC_ICSCR1_MSIKRANGE_2 | RCC_ICSCR1_MSIKRANGE_3)                          /*!< MSIK = 150 kHz   */
#define LL_RCC_MSIKRANGE_15                (RCC_ICSCR1_MSIKRANGE_0 | RCC_ICSCR1_MSIKRANGE_1 | RCC_ICSCR1_MSIKRANGE_2 | \
                                            RCC_ICSCR1_MSIKRANGE_3) /*!< MSIK = 100 kHz   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSISSRANGE  MSIS range after Standby mode
  * @{
  */
#define LL_RCC_MSISSRANGE_4                  RCC_CSR_MSISSRANGE_2                                                /*!< MSIS = 4 MHz    */
#define LL_RCC_MSISSRANGE_5                 (RCC_CSR_MSISSRANGE_2 | RCC_CSR_MSISSRANGE_0)                        /*!< MSIS = 2 MHz    */
#define LL_RCC_MSISSRANGE_6                 (RCC_CSR_MSISSRANGE_2 | RCC_CSR_MSISSRANGE_1)                        /*!< MSIS = 1.5 MHz  */
#define LL_RCC_MSISSRANGE_7                 (RCC_CSR_MSISSRANGE_0 | RCC_CSR_MSISSRANGE_2 | RCC_CSR_MSISSRANGE_1) /*!< MSIS = 1 MHz  */
#define LL_RCC_MSISSRANGE_8                  RCC_CSR_MSISSRANGE_3                                                /*!< MSIS = 3.072 MHz*/
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIKSRANGE  MSIK range after Standby mode
  * @{
  */
#define LL_RCC_MSIKSRANGE_4                  RCC_CSR_MSIKSRANGE_2                                                /*!< MSIK = 4 MHz    */
#define LL_RCC_MSIKSRANGE_5                 (RCC_CSR_MSIKSRANGE_2 | RCC_CSR_MSIKSRANGE_0)                        /*!< MSIK = 2 MHz    */
#define LL_RCC_MSIKSRANGE_6                 (RCC_CSR_MSIKSRANGE_2 | RCC_CSR_MSIKSRANGE_1)                        /*!< MSIK = 1.5 MHz  */
#define LL_RCC_MSIKSRANGE_7                 (RCC_CSR_MSIKSRANGE_2 | RCC_CSR_MSIKSRANGE_1 | RCC_CSR_MSIKSRANGE_0) /*!< MSIK = 1 MHz  */
#define LL_RCC_MSIKSRANGE_8                  RCC_CSR_MSIKSRANGE_3                                                /*!< MSIK = 3.072 MHz*/
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIPLLMODE  MSIS/MSIK Pll Mode
  * @{
  */
#define LL_RCC_PLLMODE_MSIK                  0U                 /*!< MSIK selection for Pll Mode */
#define LL_RCC_PLLMODE_MSIS                  RCC_CR_MSIPLLSEL   /*!< MSIS selection for Pll Mode  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIPLLFAST_ACTIVATION  MSI PLL mode fast startup
  * @{
  */
#define LL_RCC_PLLFAST_NORMAL            0U                /*!< MSI PLL normal start-up */
#define LL_RCC_PLLFAST_FAST              RCC_CR_MSIPLLFAST /*!< MSI PLL fast start-up   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIBIASMODE  MSI BIAS Mode
  * @{
  */
#define LL_RCC_MSIBIASMODE_SAMPLING           RCC_ICSCR1_MSIBIAS   /*!< Sampling mode selection for MSI*/
#define LL_RCC_MSIBIASMODE_CONTINUOUS         0U                   /*!< Continuous mode selection for MSI*/
/**
  * @}
  */

/** @defgroup RCC_LL_EC_HSEEXT  EXTERNAL HSE Mode
  * @{
  */
#define LL_RCC_HSE_ANALOG_MODE               0U                    /*!< HSE clock used as ANALOG clock source */
#define LL_RCC_HSE_DIGITAL_MODE              RCC_CR_HSEEXT         /*!< HSE clock used as DIGITAL clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LSCO_CLKSOURCE  LSCO Selection
  * @{
  */
#define LL_RCC_LSCO_CLKSOURCE_LSI            0x00000000U           /*!< LSI selection for low speed clock  */
#define LL_RCC_LSCO_CLKSOURCE_LSE            RCC_BDCR_LSCOSEL      /*!< LSE selection for low speed clock  */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_PLL1MBOOST_DIV  EPOD prescaler
  * @{
  */
#define LL_RCC_PLL1MBOOST_DIV_1              0x00000000U                                                                         /*!< PLL1CLK not divided   */
#define LL_RCC_PLL1MBOOST_DIV_2              RCC_PLL1CFGR_PLL1MBOOST_0                                                           /*!< PLL1CLK divided by 2  */
#define LL_RCC_PLL1MBOOST_DIV_4              RCC_PLL1CFGR_PLL1MBOOST_1                                                           /*!< PLL1CLK divided by 4  */
#define LL_RCC_PLL1MBOOST_DIV_6              (RCC_PLL1CFGR_PLL1MBOOST_1 | RCC_PLL1CFGR_PLL1MBOOST_0)                             /*!< PLL1CLK divided by 6  */
#define LL_RCC_PLL1MBOOST_DIV_8              RCC_PLL1CFGR_PLL1MBOOST_2                                                           /*!< PLL1CLK divided by 8  */
#define LL_RCC_PLL1MBOOST_DIV_10             (RCC_PLL1CFGR_PLL1MBOOST_2 | RCC_PLL1CFGR_PLL1MBOOST_0)                             /*!< PLL1CLK divided by 10 */
#define LL_RCC_PLL1MBOOST_DIV_12             (RCC_PLL1CFGR_PLL1MBOOST_2 | RCC_PLL1CFGR_PLL1MBOOST_1)                             /*!< PLL1CLK divided by 12 */
#define LL_RCC_PLL1MBOOST_DIV_14             (RCC_PLL1CFGR_PLL1MBOOST_2 | RCC_PLL1CFGR_PLL1MBOOST_1 | \
                                              RCC_PLL1CFGR_PLL1MBOOST_0) /*!< PLL1CLK divided by 14 */
#define LL_RCC_PLL1MBOOST_DIV_16             RCC_PLL1CFGR_PLL1MBOOST_3                                                           /*!< PLL1CLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_MSIS            0x00000000U                         /*!< MSIS selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSI             RCC_CFGR1_SW_0                      /*!< HSI oscillator selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_HSE             RCC_CFGR1_SW_1                      /*!< HSE selection as system clock */
#define LL_RCC_SYS_CLKSOURCE_PLL1            (RCC_CFGR1_SW_1 | RCC_CFGR1_SW_0)   /*!< PLL selection as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define LL_RCC_SYS_CLKSOURCE_STATUS_MSIS     0x00000000U                          /*!< MSIS used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSI      RCC_CFGR1_SWS_0                      /*!< HSI used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_HSE      RCC_CFGR1_SWS_1                      /*!< HSE used as system clock */
#define LL_RCC_SYS_CLKSOURCE_STATUS_PLL1     (RCC_CFGR1_SWS_1 | RCC_CFGR1_SWS_0)  /*!< PLL1 used as system clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSTICK_CLKSOURCE  SYSTICK clock source selection
  * @{
  */
#define LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8    0x00000000U             /*!< HCLKDIV8 clock used as SYSTICK clock source */
#define LL_RCC_SYSTICK_CLKSOURCE_LSI         RCC_CCIPR1_SYSTICKSEL_0 /*!< LSI clock used as SYSTICK clock source */
#define LL_RCC_SYSTICK_CLKSOURCE_LSE         RCC_CCIPR1_SYSTICKSEL_1 /*!< LSE clock used as SYSTICK clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define LL_RCC_HCLK_PRESCALER_1                  0x00000000U                                                                /*!< SYSCLK not divided */
#define LL_RCC_HCLK_PRESCALER_2                  RCC_CFGR2_HPRE_3                                                           /*!< SYSCLK divided by 2 */
#define LL_RCC_HCLK_PRESCALER_4                  (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_0)                                      /*!< SYSCLK divided by 4 */
#define LL_RCC_HCLK_PRESCALER_8                  (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1)                                      /*!< SYSCLK divided by 8 */
#define LL_RCC_HCLK_PRESCALER_16                 (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0)                   /*!< SYSCLK divided by 16 */
#define LL_RCC_HCLK_PRESCALER_64                 (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2)                                      /*!< SYSCLK divided by 64 */
#define LL_RCC_HCLK_PRESCALER_128                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_0)                   /*!< SYSCLK divided by 128 */
#define LL_RCC_HCLK_PRESCALER_256                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1)                   /*!< SYSCLK divided by 256 */
#define LL_RCC_HCLK_PRESCALER_512                (RCC_CFGR2_HPRE_3 | RCC_CFGR2_HPRE_2 | RCC_CFGR2_HPRE_1 | RCC_CFGR2_HPRE_0)/*!< SYSCLK divided by 512 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB1_DIV  APB low-speed prescaler (APB1)
  * @{
  */
#define LL_RCC_APB1_PRESCALER_1                    0x00000000U                                                 /*!< HCLK not divided */
#define LL_RCC_APB1_PRESCALER_2                    RCC_CFGR2_PPRE1_2                                           /*!< HCLK divided by 2 */
#define LL_RCC_APB1_PRESCALER_4                    (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_0)                     /*!< HCLK divided by 4 */
#define LL_RCC_APB1_PRESCALER_8                    (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1)                     /*!< HCLK divided by 8 */
#define LL_RCC_APB1_PRESCALER_16                   (RCC_CFGR2_PPRE1_2 | RCC_CFGR2_PPRE1_1 | RCC_CFGR2_PPRE1_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_APB2_DIV  APB high-speed prescaler (APB2)
  * @{
  */
#define LL_RCC_APB2_PRESCALER_1                    0x00000000U                                                 /*!< HCLK not divided */
#define LL_RCC_APB2_PRESCALER_2                    RCC_CFGR2_PPRE2_2                                           /*!< HCLK divided by 2 */
#define LL_RCC_APB2_PRESCALER_4                    (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_0)                     /*!< HCLK divided by 4 */
#define LL_RCC_APB2_PRESCALER_8                    (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1)                     /*!< HCLK divided by 8 */
#define LL_RCC_APB2_PRESCALER_16                   (RCC_CFGR2_PPRE2_2 | RCC_CFGR2_PPRE2_1 | RCC_CFGR2_PPRE2_0) /*!< HCLK divided by 16 */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_APB3_DIV  APB high-speed prescaler (APB3)
  * @{
  */
#define LL_RCC_APB3_PRESCALER_1                    0x00000000U                                                 /*!< HCLK not divided */
#define LL_RCC_APB3_PRESCALER_2                    RCC_CFGR3_PPRE3_2                                           /*!< HCLK divided by 2 */
#define LL_RCC_APB3_PRESCALER_4                    (RCC_CFGR3_PPRE3_2 | RCC_CFGR3_PPRE3_0)                     /*!< HCLK divided by 4 */
#define LL_RCC_APB3_PRESCALER_8                    (RCC_CFGR3_PPRE3_2 | RCC_CFGR3_PPRE3_1)                     /*!< HCLK divided by 8 */
#define LL_RCC_APB3_PRESCALER_16                   (RCC_CFGR3_PPRE3_2 | RCC_CFGR3_PPRE3_1 | RCC_CFGR3_PPRE3_0) /*!< HCLK divided by 16 */
/**
  * @}
  */

#if defined(RCC_CFGR2_PPRE_DPHY)
/** @defgroup RCC_LL_EC_DPHY_DIV  DSI PHY clock prescaler (DCLK)
  * @{
  */
#define LL_RCC_DPHY_DIV_1                    0x00000000U                                                                  /*!< DCLK not divided */
#define LL_RCC_DPHY_DIV_2                    RCC_CFGR2_PPRE_DPHY_2                                                        /*!< DCLK divided by 2 */
#define LL_RCC_DPHY_DIV_4                    (RCC_CFGR2_PPRE_DPHY_2 | RCC_CFGR2_PPRE_DPHY_0)                              /*!< DCLK divided by 4 */
#define LL_RCC_DPHY_DIV_8                    (RCC_CFGR2_PPRE_DPHY_2 | RCC_CFGR2_PPRE_DPHY_1)                              /*!< DCLK divided by 8 */
#define LL_RCC_DPHY_DIV_16                   (RCC_CFGR2_PPRE_DPHY_2 | RCC_CFGR2_PPRE_DPHY_1 | RCC_CFGR2_PPRE_DPHY_0)      /*!< DCLK divided by 16 */
/**
  * @}
  */
#endif /* RCC_CFGR2_PPRE_DPHY */

/** @defgroup RCC_LL_EC_STOP_WAKEUPCLOCK  Wakeup from Stop and CSS backup clock selection
  * @{
  */
#define LL_RCC_STOP_WAKEUPCLOCK_MSIS         0x00000000U             /*!< MSIS selection after wake-up from STOP */
#define LL_RCC_STOP_WAKEUPCLOCK_HSI          RCC_CFGR1_STOPWUCK      /*!< HSI selection after wake-up from STOP */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_STOP_WAKEUPKERCLOCK  Wakeup from Stop kernel clock automatic enable selection
  * @{
  */
#define LL_RCC_STOP_WAKEUPKERCLOCK_MSIK      0x00000000U             /*!< MSIK oscillator automatically enabled when exiting Stop mode  */
#define LL_RCC_STOP_WAKEUPKERCLOCK_HSI       RCC_CFGR1_STOPKERWUCK   /*!< HSI oscillator automatically enabled when exiting Stop mode */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define LL_RCC_MCO1SOURCE_NOCLOCK            0x00000000U                                                  /*!< MCO output disabled, no clock on MCO */
#define LL_RCC_MCO1SOURCE_SYSCLK             RCC_CFGR1_MCOSEL_0                                           /*!< SYSCLK selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_MSIS                RCC_CFGR1_MCOSEL_1                                          /*!< MSIS selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSI                (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_1)                    /*!< HSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSE                RCC_CFGR1_MCOSEL_2                                           /*!< HSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_PLLCLK             (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_2)                    /*!< Main PLL selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSI                (RCC_CFGR1_MCOSEL_1 | RCC_CFGR1_MCOSEL_2)                    /*!< LSI selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_LSE                (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_1| RCC_CFGR1_MCOSEL_2)/*!< LSE selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_HSI48              RCC_CFGR1_MCOSEL_3                                           /*!< HSI48 selection as MCO1 source */
#define LL_RCC_MCO1SOURCE_MSIK               (RCC_CFGR1_MCOSEL_0 | RCC_CFGR1_MCOSEL_3)                    /*!< MSIK selection as MCO1 source   */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */
#define LL_RCC_MCO1_PRESCALER_1                    0x00000000U                                     /*!< MCO not divided */
#define LL_RCC_MCO1_PRESCALER_2                    RCC_CFGR1_MCOPRE_0                              /*!< MCO divided by 2 */
#define LL_RCC_MCO1_PRESCALER_4                    RCC_CFGR1_MCOPRE_1                              /*!< MCO divided by 4 */
#define LL_RCC_MCO1_PRESCALER_8                    (RCC_CFGR1_MCOPRE_1 | RCC_CFGR1_MCOPRE_0)       /*!< MCO divided by 8 */
#define LL_RCC_MCO1_PRESCALER_16                   RCC_CFGR1_MCOPRE_2                              /*!< MCO divided by 16 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define LL_RCC_RTC_CLKSOURCE_NONE            0x00000000U             /*!< No clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSE             RCC_BDCR_RTCSEL_0       /*!< LSE oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_LSI             RCC_BDCR_RTCSEL_1       /*!< LSI oscillator clock used as RTC clock */
#define LL_RCC_RTC_CLKSOURCE_HSE_DIV32       RCC_BDCR_RTCSEL         /*!< HSE oscillator clock divided by 32 used as RTC clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USART_CLKSOURCE  Peripheral USARTx clock source selection
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE_PCLK2       ((RCC_OFFSET_CCIPR1 << 24U)| (RCC_CCIPR1_USART1SEL_Pos << 16U))  /*!< PCLK2 clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_SYSCLK      ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART1SEL_Pos << 16U) | (RCC_CCIPR1_USART1SEL_0 >> RCC_CCIPR1_USART1SEL_Pos)) /*!< SYSCLK clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_HSI         ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART1SEL_Pos << 16U) | (RCC_CCIPR1_USART1SEL_1 >> RCC_CCIPR1_USART1SEL_Pos)) /*!< HSI clock used as USART1 clock source */
#define LL_RCC_USART1_CLKSOURCE_LSE         ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART1SEL_Pos << 16U) | (RCC_CCIPR1_USART1SEL >> RCC_CCIPR1_USART1SEL_Pos))   /*!< LSE clock used as USART1 clock source */
#if defined(USART2)
#define LL_RCC_USART2_CLKSOURCE_PCLK1       ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART2SEL_Pos << 16U))   /*!< PCLK1 clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_SYSCLK      ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART2SEL_Pos << 16U) | (RCC_CCIPR1_USART2SEL_0 >> RCC_CCIPR1_USART2SEL_Pos)) /*!< SYSCLK clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_HSI         ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART2SEL_Pos << 16U) | (RCC_CCIPR1_USART2SEL_1 >> RCC_CCIPR1_USART2SEL_Pos)) /*!< HSI clock used as USART2 clock source */
#define LL_RCC_USART2_CLKSOURCE_LSE         ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART2SEL_Pos << 16U) | (RCC_CCIPR1_USART2SEL >> RCC_CCIPR1_USART2SEL_Pos))   /*!< LSE clock used as USART2 clock source */
#endif /* USART2 */
#define LL_RCC_USART3_CLKSOURCE_PCLK1       ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART3SEL_Pos << 16U))                           /*!< PCLK3 clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_SYSCLK      ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART3SEL_Pos << 16U) | (RCC_CCIPR1_USART3SEL_0 >> RCC_CCIPR1_USART3SEL_Pos)) /*!< SYSCLK clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_HSI         ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART3SEL_Pos << 16U) | (RCC_CCIPR1_USART3SEL_1 >> RCC_CCIPR1_USART3SEL_Pos)) /*!< HSI clock used as USART3 clock source */
#define LL_RCC_USART3_CLKSOURCE_LSE         ((RCC_OFFSET_CCIPR1 << 24U) |(RCC_CCIPR1_USART3SEL_Pos << 16U) | (RCC_CCIPR1_USART3SEL >> RCC_CCIPR1_USART3SEL_Pos))   /*!< LSE clock used as USART3 clock source */
#if defined (RCC_CCIPR2_USART6SEL)
#define LL_RCC_USART6_CLKSOURCE_PCLK1       ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_USART6SEL_Pos << 16U))                        /*!< PCLK1 clock used as USART6 clock source */
#define LL_RCC_USART6_CLKSOURCE_SYSCLK      ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_USART6SEL_Pos << 16U) | (RCC_CCIPR2_USART6SEL_0 >> RCC_CCIPR2_USART6SEL_Pos)) /*!< SYSCLK clock used as USART6 clock source */
#define LL_RCC_USART6_CLKSOURCE_HSI         ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_USART6SEL_Pos << 16U) | (RCC_CCIPR2_USART6SEL_1 >> RCC_CCIPR2_USART6SEL_Pos)) /*!< HSI clock used as USART6 clock source */
#define LL_RCC_USART6_CLKSOURCE_LSE         ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_USART6SEL_Pos << 16U) | (RCC_CCIPR2_USART6SEL >> RCC_CCIPR2_USART6SEL_Pos))   /*!< LSE clock used as USART6 clock source */
/* Legacy define */
#define LL_RCC_USART6_CLKSOURCE_PCLK2       LL_RCC_USART6_CLKSOURCE_PCLK1
#endif /* RCC_CCIPR2_USART6SEL */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UART_CLKSOURCE  Peripheral UARTx clock source selection
  * @{
  */
#define LL_RCC_UART4_CLKSOURCE_PCLK1        (RCC_CCIPR1_UART4SEL << 16U)                            /*!< PCLK1 clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_SYSCLK       ((RCC_CCIPR1_UART4SEL << 16U) | RCC_CCIPR1_UART4SEL_0)  /*!< SYSCLK clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_HSI          ((RCC_CCIPR1_UART4SEL << 16U) | RCC_CCIPR1_UART4SEL_1)  /*!< HSI clock used as UART4 clock source */
#define LL_RCC_UART4_CLKSOURCE_LSE          ((RCC_CCIPR1_UART4SEL << 16U) | RCC_CCIPR1_UART4SEL)    /*!< LSE clock used as UART4 clock source */
#define LL_RCC_UART5_CLKSOURCE_PCLK1        (RCC_CCIPR1_UART5SEL << 16U)                            /*!< PCLK1 clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_SYSCLK       ((RCC_CCIPR1_UART5SEL << 16U) | RCC_CCIPR1_UART5SEL_0)  /*!< SYSCLK clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_HSI          ((RCC_CCIPR1_UART5SEL << 16U) | RCC_CCIPR1_UART5SEL_1)  /*!< HSI clock used as UART5 clock source */
#define LL_RCC_UART5_CLKSOURCE_LSE          ((RCC_CCIPR1_UART5SEL << 16U) | RCC_CCIPR1_UART5SEL)    /*!< LSE clock used as UART5 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART_CLKSOURCE  Peripheral LPUARTx clock source selection
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE_PCLK3       0x00000000U                                        /*!< PCLK3 clock used as LPUART1 clock source  */
#define LL_RCC_LPUART1_CLKSOURCE_SYSCLK     RCC_CCIPR3_LPUART1SEL_0                             /*!< SYSCLK clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_HSI        RCC_CCIPR3_LPUART1SEL_1                             /*!< HSI clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_LSE        (RCC_CCIPR3_LPUART1SEL_0 | RCC_CCIPR3_LPUART1SEL_1) /*!< LSE clock used as LPUART1 clock source */
#define LL_RCC_LPUART1_CLKSOURCE_MSIK       RCC_CCIPR3_LPUART1SEL_2                             /*!< MSIK clock used as LPUART1 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_I2C_CLKSOURCE  Peripheral I2Cx clock source selection
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE_PCLK1         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U))                                                    /*!< PCLK1 clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C1SEL_0 >> RCC_CCIPR1_I2C1SEL_Pos)) /*!< SYSCLK clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C1SEL_1 >> RCC_CCIPR1_I2C1SEL_Pos)) /*!< HSI clock used as I2C1 clock source */
#define LL_RCC_I2C1_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C1SEL >> RCC_CCIPR1_I2C1SEL_Pos))   /*!< MSIK clock used as I2C1 clock source */
#define LL_RCC_I2C2_CLKSOURCE_PCLK1         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C2SEL_Pos << 16U)) /*!< PCLK1 clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C2SEL_0 >> RCC_CCIPR1_I2C2SEL_Pos)) /*!< SYSCLK clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C2SEL_1 >> RCC_CCIPR1_I2C2SEL_Pos)) /*!< HSI clock used as I2C2 clock source */
#define LL_RCC_I2C2_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C2SEL >> RCC_CCIPR1_I2C2SEL_Pos))   /*!< MSIK clock used as I2C2 clock source */
#define LL_RCC_I2C3_CLKSOURCE_PCLK3         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U)) /*!< PCLK3 clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_I2C3SEL_0 >> RCC_CCIPR3_I2C3SEL_Pos)) /*!< SYSCLK clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_I2C3SEL_1 >> RCC_CCIPR3_I2C3SEL_Pos)) /*!< HSI clock used as I2C3 clock source */
#define LL_RCC_I2C3_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_I2C3SEL >> RCC_CCIPR3_I2C3SEL_Pos))   /*!< MSIK clock used as I2C3 clock source */
#define LL_RCC_I2C4_CLKSOURCE_PCLK1         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C4SEL_Pos << 16U)) /*!< PCLK1 clock used as I2C4 clock source */
#define LL_RCC_I2C4_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C4SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C4SEL_0 >> RCC_CCIPR1_I2C4SEL_Pos)) /*!< SYSCLK clock used as I2C4 clock source */
#define LL_RCC_I2C4_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C4SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C4SEL_1 >> RCC_CCIPR1_I2C4SEL_Pos)) /*!< HSI clock used as I2C4 clock source */
#define LL_RCC_I2C4_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C4SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_I2C4SEL >> RCC_CCIPR1_I2C4SEL_Pos))   /*!< MSIK clock used as I2C4 clock source */
#if defined (RCC_CCIPR2_I2C5SEL)
#define LL_RCC_I2C5_CLKSOURCE_PCLK1         ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C5SEL_Pos << 16U)) /*!< PCLK1 clock used as I2C5 clock source */
#define LL_RCC_I2C5_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C5SEL_Pos << 16U) | \
                                             (RCC_CCIPR2_I2C5SEL_0 >> RCC_CCIPR2_I2C5SEL_Pos)) /*!< SYSCLK clock used as I2C5 clock source */
#define LL_RCC_I2C5_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C5SEL_Pos << 16U) | \
                                             (RCC_CCIPR2_I2C5SEL_1 >> RCC_CCIPR2_I2C5SEL_Pos)) /*!< HSI clock used as I2C5 clock source */
#define LL_RCC_I2C5_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C5SEL_Pos << 16U) | \
                                             (RCC_CCIPR2_I2C5SEL >> RCC_CCIPR2_I2C5SEL_Pos))   /*!< MSIK clock used as I2C5 clock source */
#endif /* RCC_CCIPR2_I2C5SEL */
#if defined (RCC_CCIPR2_I2C6SEL)
#define LL_RCC_I2C6_CLKSOURCE_PCLK1         ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C6SEL_Pos << 16U)) /*!< PCLK1 clock used as I2C6 clock source */
#define LL_RCC_I2C6_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C6SEL_Pos << 16U) | \
                                             (RCC_CCIPR2_I2C6SEL_0 >> RCC_CCIPR2_I2C6SEL_Pos)) /*!< SYSCLK clock used as I2C6 clock source */
#define LL_RCC_I2C6_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C6SEL_Pos << 16U) | \
                                             (RCC_CCIPR2_I2C6SEL_1 >> RCC_CCIPR2_I2C6SEL_Pos)) /*!< HSI clock used as I2C6 clock source */
#define LL_RCC_I2C6_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C6SEL_Pos << 16U) | \
                                             (RCC_CCIPR2_I2C6SEL >> RCC_CCIPR2_I2C6SEL_Pos))   /*!< MSIK clock used as I2C6 clock source */
#endif /* RCC_CCIPR2_I2C6SEL */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPI_CLKSOURCE  Peripheral SPIx clock source selection
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE_PCLK2         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U))                                                    /*!< PCLK2 clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_SPI1SEL_0 >> RCC_CCIPR1_SPI1SEL_Pos)) /*!< SYSCLK clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_SPI1SEL_1 >> RCC_CCIPR1_SPI1SEL_Pos)) /*!< HSI clock used as SPI1 clock source */
#define LL_RCC_SPI1_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_SPI1SEL >> RCC_CCIPR1_SPI1SEL_Pos))   /*!< MSIK clock used as SPI1 clock source */
#define LL_RCC_SPI2_CLKSOURCE_PCLK1         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI2SEL_Pos << 16U))                                                    /*!< PCLK1 clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_SPI2SEL_0 >> RCC_CCIPR1_SPI2SEL_Pos)) /*!< SYSCLK clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_SPI2SEL_1 >> RCC_CCIPR1_SPI2SEL_Pos)) /*!< HSI clock used as SPI2 clock source */
#define LL_RCC_SPI2_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_SPI2SEL >> RCC_CCIPR1_SPI2SEL_Pos))  /*!< MSIK clock used as SPI2 clock source */
#define LL_RCC_SPI3_CLKSOURCE_PCLK3         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U))                                                    /*!< PCLK3 clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_SYSCLK        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_SPI3SEL_0 >> RCC_CCIPR3_SPI3SEL_Pos)) /*!< SYSCLK clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_HSI           ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_SPI3SEL_1 >> RCC_CCIPR3_SPI3SEL_Pos)) /*!< HSI clock used as SPI3 clock source */
#define LL_RCC_SPI3_CLKSOURCE_MSIK          ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_SPI3SEL >> RCC_CCIPR3_SPI3SEL_Pos))   /*!< MSIK clock used as SPI3 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM_CLKSOURCE  Peripheral LPTIMx clock source selection
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE_MSIK        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U))                                                           /*!< MSIK clock used as LPTIM1 clock source */
#define LL_RCC_LPTIM1_CLKSOURCE_LSI         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_LPTIM1SEL_0 >> RCC_CCIPR3_LPTIM1SEL_Pos))    /*!< LSI clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM1_CLKSOURCE_HSI         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_LPTIM1SEL_1 >> RCC_CCIPR3_LPTIM1SEL_Pos))    /*!< HSI clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM1_CLKSOURCE_LSE         ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_LPTIM1SEL >> RCC_CCIPR3_LPTIM1SEL_Pos))      /*!< LSE clock used as LPTIM1 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_PCLK1       ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U))                                                           /*!< PCLK1 clock used as LPTIM2 clock source */
#define LL_RCC_LPTIM2_CLKSOURCE_LSI         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_LPTIM2SEL_0 >> RCC_CCIPR1_LPTIM2SEL_Pos))    /*!< LSI clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_HSI         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_LPTIM2SEL_1 >> RCC_CCIPR1_LPTIM2SEL_Pos))    /*!< HSI clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM2_CLKSOURCE_LSE         ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | \
                                             (RCC_CCIPR1_LPTIM2SEL >> RCC_CCIPR1_LPTIM2SEL_Pos))      /*!< LSE clock used as LPTIM2 clock source  */
#define LL_RCC_LPTIM34_CLKSOURCE_MSIK       ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM34SEL_Pos << 16U))                                                          /*!< MSIK clock used as LPTIM34 clock source*/
#define LL_RCC_LPTIM34_CLKSOURCE_LSI        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM34SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_LPTIM34SEL_0 >> RCC_CCIPR3_LPTIM34SEL_Pos)) /*!< LSI clock used as LPTIM34 clock source */
#define LL_RCC_LPTIM34_CLKSOURCE_HSI        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM34SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_LPTIM34SEL_1 >> RCC_CCIPR3_LPTIM34SEL_Pos)) /*!< HSI clock used as LPTIM34 clock source */
#define LL_RCC_LPTIM34_CLKSOURCE_LSE        ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM34SEL_Pos << 16U) | \
                                             (RCC_CCIPR3_LPTIM34SEL >> RCC_CCIPR3_LPTIM34SEL_Pos))   /*!< LSE clock used as LPTIM34 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN_CLKSOURCE  Peripheral FDCAN kernel clock source selection
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE_HSE          0x00000000U           /*!< HSE clock used as FDCAN kernel clock source */
#define LL_RCC_FDCAN_CLKSOURCE_PLL1         RCC_CCIPR1_FDCANSEL_0 /*!< PLL1 Q clock used as FDCAN kernel clock source */
#define LL_RCC_FDCAN_CLKSOURCE_PLL2         RCC_CCIPR1_FDCANSEL_1 /*!< PLL2 P clock used as FDCAN kernel clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SAI_CLKSOURCE  Peripheral SAIx clock source selection
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE_PLL2          (RCC_CCIPR2_SAI1SEL << 16U)                          /*!< PLL2 clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_PLL3          ((RCC_CCIPR2_SAI1SEL << 16U) | RCC_CCIPR2_SAI1SEL_0) /*!< PLL3 clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_PLL1          ((RCC_CCIPR2_SAI1SEL << 16U) | RCC_CCIPR2_SAI1SEL_1) /*!< PLL1 clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_HSI           ((RCC_CCIPR2_SAI1SEL << 16U) | RCC_CCIPR2_SAI1SEL_2) /*!< HSI clock used as SAI1 clock source */
#define LL_RCC_SAI1_CLKSOURCE_PIN           ((RCC_CCIPR2_SAI1SEL << 16U) | (RCC_CCIPR2_SAI1SEL_1 | \
                                                                            RCC_CCIPR2_SAI1SEL_0))  /*!< External input clock used as SAI1 clock source */
#if defined(SAI2)
#define LL_RCC_SAI2_CLKSOURCE_PLL2          (RCC_CCIPR2_SAI2SEL << 16U)                          /*!< PLL2 clock used as SAI2 clock source */
#define LL_RCC_SAI2_CLKSOURCE_PLL3          ((RCC_CCIPR2_SAI2SEL << 16U) | RCC_CCIPR2_SAI2SEL_0) /*!< PLL3 clock used as SAI2 clock source */
#define LL_RCC_SAI2_CLKSOURCE_PLL1          ((RCC_CCIPR2_SAI2SEL << 16U) | RCC_CCIPR2_SAI2SEL_1) /*!< PLL1clock used as SAI2 clock source */
#define LL_RCC_SAI2_CLKSOURCE_HSI           ((RCC_CCIPR2_SAI2SEL << 16U) | RCC_CCIPR2_SAI2SEL_2) /*!< HSI clock used as SAI2 clock source */
#define LL_RCC_SAI2_CLKSOURCE_PIN           ((RCC_CCIPR2_SAI2SEL << 16U) | (RCC_CCIPR2_SAI2SEL_1 | \
                                                                            RCC_CCIPR2_SAI2SEL_0))  /*!< External input clock used as SAI2 clock source */
#endif /* SAI2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC_KERNELCLKSOURCE  Peripheral SDMMC1/2 kernel clock source selection
  * @{
  */
#define LL_RCC_SDMMC12_KERCLKSOURCE_48CLK  0x00000000U         /*!< 48MHz clock from internal multiplexor used as SDMMC1/2 clock source */
#define LL_RCC_SDMMC12_KERCLKSOURCE_PLL1   RCC_CCIPR2_SDMMCSEL /*!< PLL1 "P" used as SDMMC1/2 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC12_CLKSOURCE  Peripheral SDMMC clock source selection
  * @{
  */
#define LL_RCC_SDMMC12_CLKSOURCE_HSI48      0x00000000U             /*!< HSI48 clock used as SDMMC1/2 clock source */
#define LL_RCC_SDMMC12_CLKSOURCE_PLL2       RCC_CCIPR1_ICLKSEL_0    /*!< PLL2 "Q" clock used as SDMMC1/2 clock source */
#define LL_RCC_SDMMC12_CLKSOURCE_PLL1       RCC_CCIPR1_ICLKSEL_1    /*!< PLL1 "Q" clock used as SDMMC1/2 clock source */
#define LL_RCC_SDMMC12_CLKSOURCE_MSIK       RCC_CCIPR1_ICLKSEL      /*!< MSIK clock used as SDMMC1/2 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RNG_CLKSOURCE  Peripheral RNG clock source selection
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE_HSI48         0x00000000U            /*!< HSI48 clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_HSI48_DIV2    RCC_CCIPR2_RNGSEL_0    /*!< HSI48/2 clock used as RNG clock source */
#define LL_RCC_RNG_CLKSOURCE_HSI           RCC_CCIPR2_RNGSEL_1    /*!< HSI clock used as RNG clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USB_CLKSOURCE  Peripheral USB clock source selection
  * @{
  */
#define LL_RCC_USB_CLKSOURCE_HSI48         0x00000000U            /*!< HSI48 clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_PLL2          RCC_CCIPR1_ICLKSEL_0   /*!< PLL2 "Q" clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_PLL1          RCC_CCIPR1_ICLKSEL_1   /*!< PLL1 "Q" clock used as USB clock source */
#define LL_RCC_USB_CLKSOURCE_MSIK          RCC_CCIPR1_ICLKSEL     /*!< MSIK clock used as USB clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADCDAC_CLKSOURCE  Peripheral ADCx and DAC1 clock source selection
  * @{
  */
#define LL_RCC_ADCDAC_CLKSOURCE_HCLK       0x00000000U                                       /*!< No clock used as ADCx/DAC1 clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_SYSCLK     RCC_CCIPR3_ADCDACSEL_0                            /*!< SYSCLK clock used as ADCx/DAC1 clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_PLL2       RCC_CCIPR3_ADCDACSEL_1                            /*!< PLL2 clock used as ADCx/DAC1 clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_HSI        RCC_CCIPR3_ADCDACSEL_2                            /*!< HSI clock used as ADCx/DAC1 clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_HSE        (RCC_CCIPR3_ADCDACSEL_1 | RCC_CCIPR3_ADCDACSEL_0) /*!< HSE clock used as ADCx/DAC1 clock source */
#define LL_RCC_ADCDAC_CLKSOURCE_MSIK       (RCC_CCIPR3_ADCDACSEL_2 | RCC_CCIPR3_ADCDACSEL_0) /*!< MSIK clock used as ADCx/DAC1 clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DAC1_CLKSOURCE  Peripheral DAC1 clock source selection
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE_LSE         0x00000000U                                   /*!< LSE clock used as DAC1 clock */
#define LL_RCC_DAC1_CLKSOURCE_LSI         RCC_CCIPR3_DAC1SEL                            /*!< LSI clock used as DAC1 clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADF1_CLKSOURCE  Peripheral ADF1 clock source selection
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE_HCLK        0x00000000U                                   /*!< HCLK clock used as ADF1 clock */
#define LL_RCC_ADF1_CLKSOURCE_PLL1        RCC_CCIPR3_ADF1SEL_0                          /*!< PLL1 clock used as ADF1 clock */
#define LL_RCC_ADF1_CLKSOURCE_PLL3        RCC_CCIPR3_ADF1SEL_1                          /*!< PLL3 clock used as ADF1 clock */
#define LL_RCC_ADF1_CLKSOURCE_MSIK        RCC_CCIPR3_ADF1SEL_2                          /*!< MSIK clock used as ADF1 clock */
#define LL_RCC_ADF1_CLKSOURCE_PIN         (RCC_CCIPR3_ADF1SEL_1 | RCC_CCIPR3_ADF1SEL_0) /*!< PIN SAI1_EXTCLK clock used as ADF1 clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MDF1_CLKSOURCE  Peripheral MDF1 clock source selection
  * @{
  */
#define LL_RCC_MDF1_CLKSOURCE_HCLK        0x00000000U                                   /*!< HCLK clock used as MDF1 clock */
#define LL_RCC_MDF1_CLKSOURCE_PLL1        RCC_CCIPR2_MDF1SEL_0                          /*!< PLL1 clock used as MDF1 clock */
#define LL_RCC_MDF1_CLKSOURCE_PLL3        RCC_CCIPR2_MDF1SEL_1                          /*!< PLL3 clock used as MDF1 clock */
#define LL_RCC_MDF1_CLKSOURCE_MSIK        RCC_CCIPR2_MDF1SEL_2                          /*!< MSIK clock used as MDF1 clock */
#define LL_RCC_MDF1_CLKSOURCE_PIN         (RCC_CCIPR2_MDF1SEL_1 | RCC_CCIPR2_MDF1SEL_0) /*!< PIN SAI1_EXTCLK clock used as MDF1 clock */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_OCTOSPI_CLKSOURCE  Peripheral OCTOSPI kernel clock source selection
  * @{
  */
#define LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK    0x00000000U                                        /*!< SYSCLK clock used as OctoSPI kernel clock source */
#define LL_RCC_OCTOSPI_CLKSOURCE_MSIK      RCC_CCIPR2_OCTOSPISEL_0                            /*!< MSIK clock used as OctoSPI kernel clock source */
#define LL_RCC_OCTOSPI_CLKSOURCE_PLL1      RCC_CCIPR2_OCTOSPISEL_1                            /*!< PLL1 "Q" clock used as OctoSPI kernel clock source */
#define LL_RCC_OCTOSPI_CLKSOURCE_PLL2      (RCC_CCIPR2_OCTOSPISEL_1|RCC_CCIPR2_OCTOSPISEL_0)  /*!< PLL2 "Q" clock used as OctoSPI kernel clock source */
/**
  * @}
  */

#if defined (HSPI1)
/** @defgroup RCC_LL_EC_HSPI1_CLKSOURCE  Peripheral HSPI1 kernel clock source selection
  * @{
  */
#define LL_RCC_HSPI_CLKSOURCE_SYSCLK     0U
#define LL_RCC_HSPI_CLKSOURCE_PLL1       RCC_CCIPR2_HSPISEL_0
#define LL_RCC_HSPI_CLKSOURCE_PLL2       RCC_CCIPR2_HSPISEL_1
#define LL_RCC_HSPI_CLKSOURCE_PLL3       RCC_CCIPR2_HSPISEL
/**
  * @}
  */
#endif /* HSPI1 */

/** @defgroup RCC_LL_EC_TIM_INPUT_CAPTURE_CLOCKSource TIM Input capture clock source selection
  * @{
  */
#define LL_RCC_TIMIC_CLKSOURCE_NONE                  0x00000000U                                                             /*!< No clock available for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256            RCC_CCIPR1_TIMICSEL_2                                                   /*!< HSI/256 selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV1024          RCC_CCIPR1_TIMICSEL_2                                                   /*!< MSIS/1024 selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV4             (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1)                         /*!< MSIS/4 selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV4             (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_0)                         /*!< MSIK/4 selected for TIM16/TIM17 and LPTIM2 input capture */
#define LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV1024          (RCC_CCIPR1_TIMICSEL_2 | RCC_CCIPR1_TIMICSEL_1 | \
                                                      RCC_CCIPR1_TIMICSEL_0) /*!< MSIK/1024 selected for TIM16/TIM17 and LPTIM2 input capture */
/**
  * @}
  */


#if defined(SAES)
/** @defgroup RCC_LL_EC_SAES_CLKSOURCE  Peripheral SAES clock source selection
  * @{
  */
#define LL_RCC_SAES_CLKSOURCE_SHSI          0x00000000U           /*!< SHSI clock used as SAES clock source */
#define LL_RCC_SAES_CLKSOURCE_SHSI_DIV2     RCC_CCIPR2_SAESSEL    /*!< SHSI_DIV2 clock used as SAES clock source */
/**
  * @}
  */
#endif /* SAES */

/** @defgroup RCC_LL_EC_USART Peripheral USARTx get clock source
  * @{
  */
#define LL_RCC_USART1_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_USART1SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_USART1SEL >> RCC_CCIPR1_USART1SEL_Pos)) /*!< USART1 Clock source selection */
#if defined(USART2)
#define LL_RCC_USART2_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_USART2SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_USART2SEL >> RCC_CCIPR1_USART2SEL_Pos)) /*!< USART2 Clock source selection */
#endif /* USART2 */
#define LL_RCC_USART3_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_USART3SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_USART3SEL >> RCC_CCIPR1_USART3SEL_Pos)) /*!< USART3 Clock source selection */
#if defined (RCC_CCIPR2_USART6SEL)
#define LL_RCC_USART6_CLKSOURCE           ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_USART6SEL_Pos << 16U) | \
                                           (RCC_CCIPR2_USART6SEL >> RCC_CCIPR2_USART6SEL_Pos)) /*!< USART6 Clock source selection */
#endif /* RCC_CCIPR2_USART6SEL */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_UART Peripheral UARTx get clock source
  * @{
  */
#define LL_RCC_UART4_CLKSOURCE             RCC_CCIPR1_UART4SEL /*!< UART4 Clock source selection */
#define LL_RCC_UART5_CLKSOURCE             RCC_CCIPR1_UART5SEL /*!< UART5 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SPI Peripheral SPIx get clock source
  * @{
  */
#define LL_RCC_SPI1_CLKSOURCE            ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI1SEL_Pos << 16U) | \
                                          (RCC_CCIPR1_SPI1SEL >> RCC_CCIPR1_SPI1SEL_Pos)) /*!< SPI1 Clock source selection */
#define LL_RCC_SPI2_CLKSOURCE            ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_SPI2SEL_Pos << 16U) | \
                                          (RCC_CCIPR1_SPI2SEL >> RCC_CCIPR1_SPI2SEL_Pos)) /*!< SPI2 Clock source selection */
#define LL_RCC_SPI3_CLKSOURCE            ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_SPI3SEL_Pos << 16U) | \
                                          (RCC_CCIPR3_SPI3SEL >> RCC_CCIPR3_SPI3SEL_Pos)) /*!< SPI3 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPUART Peripheral LPUARTx get clock source
  * @{
  */
#define LL_RCC_LPUART1_CLKSOURCE          RCC_CCIPR3_LPUART1SEL /*!< LPUART1 Clock source selection */
/**
  * @}
  */

#if defined(DSI)
/** @defgroup RCC_LL_EC_DSI_CLKSOURCE  Peripheral DSI clock source selection
  * @{
  */
#define LL_RCC_DSI_CLKSOURCE_PLL3         0U                    /*!< PLL3 "P" (pll3_p_ck) selected */
#define LL_RCC_DSI_CLKSOURCE_PHY          RCC_CCIPR2_DSIHOSTSEL /*!< DSI PHY PLL output selected   */
/**
  * @}
  */
#endif /* DSI */

#if defined(LTDC)
/** @defgroup RCC_LL_EC_LTDC_CLKSOURCE  Peripheral LTDC clock source selection
  * @{
  */
#define LL_RCC_LTDC_CLKSOURCE_PLL3        0U                  /*!< PLL3 "R" (pll3_r_ck) selected */
#define LL_RCC_LTDC_CLKSOURCE_PLL2        RCC_CCIPR2_LTDCSEL  /*!< PLL2 "R" (pll2_r_ck) selected */
/**
  * @}
  */
#endif /* LTDC */

#if defined (RCC_CCIPR2_OTGHSSEL)
/** @defgroup RCC_LL_EC_USBPHY_CLKSOURCE  Peripheral USB HS PHY clock source selection
  * @{
  */
#define LL_RCC_USBHSPHYCLKSOURCE_HSE                0U   /*!< HSE clock selected as USB HS PHY clock */
#define LL_RCC_USBHSPHYCLKSOURCE_HSE_DIV2           RCC_CCIPR2_OTGHSSEL_1      /*!< HSE clock divided by 2 selected as USB HS PHY clock */
#define LL_RCC_USBHSPHYCLKSOURCE_PLL1               RCC_CCIPR2_OTGHSSEL_0      /*!< PLL1 divider P selected as USB HS PHY clock */
#define LL_RCC_USBHSPHYCLKSOURCE_PLL1_DIV2          (RCC_CCIPR2_OTGHSSEL_1 | RCC_CCIPR2_OTGHSSEL_0) /*!< PLL1 divider P divided by 2 selected as USB HS PHY clock */
/**
  * @}
  */
#endif /* RCC_CCIPR2_OTGHSSEL */

/** @defgroup RCC_LL_EC_I2C Peripheral I2Cx get clock source
  * @{
  */
#define LL_RCC_I2C1_CLKSOURCE             ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C1SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_I2C1SEL >> RCC_CCIPR1_I2C1SEL_Pos)) /*!< I2C1 Clock source selection */
#define LL_RCC_I2C2_CLKSOURCE             ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C2SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_I2C2SEL >> RCC_CCIPR1_I2C2SEL_Pos)) /*!< I2C2 Clock source selection */
#define LL_RCC_I2C3_CLKSOURCE             ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_I2C3SEL_Pos << 16U) | \
                                           (RCC_CCIPR3_I2C3SEL >> RCC_CCIPR3_I2C3SEL_Pos)) /*!< I2C3 Clock source selection */
#define LL_RCC_I2C4_CLKSOURCE             ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_I2C4SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_I2C4SEL >> RCC_CCIPR1_I2C4SEL_Pos)) /*!< I2C4 Clock source selection */
#if defined (RCC_CCIPR2_I2C5SEL)
#define LL_RCC_I2C5_CLKSOURCE             ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C5SEL_Pos << 16U) | \
                                           (RCC_CCIPR2_I2C5SEL >> RCC_CCIPR2_I2C5SEL_Pos)) /*!< I2C1 Clock source selection */
#endif /* RCC_CCIPR2_I2C5SEL */
#if defined (RCC_CCIPR2_I2C6SEL)
#define LL_RCC_I2C6_CLKSOURCE             ((RCC_OFFSET_CCIPR2 << 24U) | (RCC_CCIPR2_I2C6SEL_Pos << 16U) | \
                                           (RCC_CCIPR2_I2C6SEL >> RCC_CCIPR2_I2C6SEL_Pos)) /*!< I2C1 Clock source selection */
#endif /* RCC_CCIPR2_I2C6SEL */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_LPTIM Peripheral LPTIMx get clock source
  * @{
  */
#define LL_RCC_LPTIM1_CLKSOURCE           ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM1SEL_Pos << 16U) | \
                                           (RCC_CCIPR3_LPTIM1SEL >> RCC_CCIPR3_LPTIM1SEL_Pos)) /*!< LPTIM1 Clock source selection */
#define LL_RCC_LPTIM2_CLKSOURCE           ((RCC_OFFSET_CCIPR1 << 24U) | (RCC_CCIPR1_LPTIM2SEL_Pos << 16U) | \
                                           (RCC_CCIPR1_LPTIM2SEL >> RCC_CCIPR1_LPTIM2SEL_Pos)) /*!< LPTIM2 Clock source selection */
#define LL_RCC_LPTIM34_CLKSOURCE          ((RCC_OFFSET_CCIPR3 << 24U) | (RCC_CCIPR3_LPTIM34SEL_Pos << 16U) | \
                                           (RCC_CCIPR3_LPTIM34SEL >> RCC_CCIPR3_LPTIM34SEL_Pos)) /*!< LPTIM3 and LPTIM4 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SAI  Peripheral SAIx get clock source
  * @{
  */
#define LL_RCC_SAI1_CLKSOURCE             RCC_CCIPR2_SAI1SEL /*!< SAI1 Clock source selection */
#if defined (SAI2)
#define LL_RCC_SAI2_CLKSOURCE             RCC_CCIPR2_SAI2SEL /*!< SAI2 Clock source selection */
#endif /* SAI2 */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC_KERNEL  Peripheral SDMMC get kernel clock source
  * @{
  */
#define LL_RCC_SDMMC_KERNELCLKSOURCE      RCC_CCIPR2_SDMMCSEL  /*!< SDMMC1/2 Kernel Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_SDMMC1/2  Peripheral SDMMC get clock source
  * @{
  */
#define LL_RCC_SDMMC_CLKSOURCE            RCC_CCIPR1_ICLKSEL /*!< SDMMC1/2 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_RNG  Peripheral RNG get clock source
  * @{
  */
#define LL_RCC_RNG_CLKSOURCE              RCC_CCIPR2_RNGSEL    /*!< RNG Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_USB  Peripheral USB get clock source
  * @{
  */
#define LL_RCC_USB_CLKSOURCE              RCC_CCIPR1_ICLKSEL /*!< USB Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADCDAC  Peripheral ADCDAC get clock source
  * @{
  */
#define LL_RCC_ADCDAC_CLKSOURCE           RCC_CCIPR3_ADCDACSEL /*!< ADCDACs Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MDF1  Peripheral MDF1 get clock source
  * @{
  */
#define LL_RCC_MDF1_CLKSOURCE             RCC_CCIPR2_MDF1SEL /* MDF1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_DAC1  Peripheral DAC1 get clock source
  * @{
  */
#define LL_RCC_DAC1_CLKSOURCE             RCC_CCIPR3_DAC1SEL /* DAC1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_ADF1  Peripheral ADF1 get clock source
  * @{
  */
#define LL_RCC_ADF1_CLKSOURCE             RCC_CCIPR3_ADF1SEL  /*!< ADF1 Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_FDCAN Peripheral FDCAN get kernel clock source
  * @{
  */
#define LL_RCC_FDCAN_CLKSOURCE            RCC_CCIPR1_FDCANSEL     /*!< FDCAN Kernel Clock source selection */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_OCTOSPI  Peripheral OCTOSPI get clock source
  * @{
  */
#define LL_RCC_OCTOSPI_CLKSOURCE          RCC_CCIPR2_OCTOSPISEL    /*!< OctoSPI Clock source selection */
/**
  * @}
  */
#if defined (HSPI1)
/** @defgroup RCC_LL_EC_HSPI  Peripheral HSPI get clock source
  * @{
  */
#define LL_RCC_HSPI_CLKSOURCE          RCC_CCIPR2_HSPISEL    /*!< HSPI Clock source selection */
/**
  * @}
  */
#endif /* HSPI */

#if defined(SAES)
/** @defgroup RCC_LL_EC_SAES  Peripheral SAES get clock source
  * @{
  */
#define LL_RCC_SAES_CLKSOURCE             RCC_CCIPR2_SAESSEL  /*!< SAES Clock source selection */
/**
  * @}
  */
#endif /* SAES */

#if defined(DSI)
/** @defgroup RCC_LL_EC_DSI  Peripheral DSI get clock source
  * @{
  */
#define LL_RCC_DSI_CLKSOURCE              RCC_CCIPR2_DSIHOSTSEL /*!< DSI Clock source selection */
/**
  * @}
  */
#endif /* DSI */

#if defined(LTDC)
/** @defgroup RCC_LL_EC_LTDC  Peripheral LTDC get clock source
  * @{
  */
#define LL_RCC_LTDC_CLKSOURCE             RCC_CCIPR2_LTDCSEL    /*!< LTDC Clock source selection */
/**
  * @}
  */
#endif /* LTDC */

#if defined (RCC_CCIPR2_OTGHSSEL)
/** @defgroup RCC_LL_EC_USBPHY  Peripheral USB HS PHY get clock source
  * @{
  */
#define LL_RCC_USBHSPHY_CLKSOURCE           RCC_CCIPR2_OTGHSSEL /*!< USB HS PHY Clock source selection */
/**
  * @}
  */
#endif /* RCC_CCIPR2_OTGHSSEL */

/** @defgroup RCC_LL_EC_PLL1SOURCE  PLL1 entry clock source
  * @{
  */
#define LL_RCC_PLL1SOURCE_NONE             0x00000000U                                       /*!< No clock selected as main PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_MSIS             RCC_PLL1CFGR_PLL1SRC_0                            /*!< MSIS clock selected as main PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_HSI              RCC_PLL1CFGR_PLL1SRC_1                            /*!< HSI clock selected as main PLL1 entry clock source */
#define LL_RCC_PLL1SOURCE_HSE              (RCC_PLL1CFGR_PLL1SRC_0 | RCC_PLL1CFGR_PLL1SRC_1) /*!< HSE clock selected as main PLL1 entry clock source */

/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL1_OUTPUT  PLL1  Clock Output
  * @{
  */
#define LL_RCC_PLL1_OUTPUT_P                RCC_PLL1CFGR_PLL1PEN /*!< pll1_p_ck output enabled  */
#define LL_RCC_PLL1_OUTPUT_Q                RCC_PLL1CFGR_PLL1QEN /*!< pll1_q_ck output enabled  */
#define LL_RCC_PLL1_OUTPUT_R                RCC_PLL1CFGR_PLL1REN /*!< pll1_r_ck output enabled  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLLINPUTRANGE   All PLLs input ranges
  * @{
  */
#define LL_RCC_PLLINPUTRANGE_4_8           0x00000000U          /*!< VCO input range: 4 to 8 MHz  */
#define LL_RCC_PLLINPUTRANGE_8_16          RCC_PLL1CFGR_PLL1RGE /*!< VCO input range: 8 to 16 MHz */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2SOURCE  PLL2 entry clock source
  * @{
  */
#define LL_RCC_PLL2SOURCE_NONE             0x00000000U                                       /*!< No clock selected as main PLL2 entry clock source */
#define LL_RCC_PLL2SOURCE_MSIS             RCC_PLL2CFGR_PLL2SRC_0                            /*!< MSIS clock selected as main PLL2 entry clock source */
#define LL_RCC_PLL2SOURCE_HSI              RCC_PLL2CFGR_PLL2SRC_1                            /*!< HSI clock selected as main PLL2 entry clock source */
#define LL_RCC_PLL2SOURCE_HSE              (RCC_PLL2CFGR_PLL2SRC_0 | RCC_PLL2CFGR_PLL2SRC_1) /*!< HSE clock selected as main PLL2 entry clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL2_OUTPUT  PLL2  Clock Output
  * @{
  */
#define LL_RCC_PLL2_OUTPUT_P                RCC_PLL2CFGR_PLL2PEN /*!< pll2_p_ck output enabled  */
#define LL_RCC_PLL2_OUTPUT_Q                RCC_PLL2CFGR_PLL2QEN /*!< pll2_q_ck output enabled  */
#define LL_RCC_PLL2_OUTPUT_R                RCC_PLL2CFGR_PLL2REN /*!< pll2_r_ck output enabled  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL3SOURCE  PLL3 entry clock source
  * @{
  */
#define LL_RCC_PLL3SOURCE_NONE             0x00000000U                                       /*!< No clock selected as main PLL3 entry clock source */
#define LL_RCC_PLL3SOURCE_MSIS             RCC_PLL3CFGR_PLL3SRC_0                            /*!< MSIS clock selected as main PLL3 entry clock source */
#define LL_RCC_PLL3SOURCE_HSI              RCC_PLL3CFGR_PLL3SRC_1                            /*!< HSI clock selected as main PLL3 entry clock source */
#define LL_RCC_PLL3SOURCE_HSE              (RCC_PLL3CFGR_PLL3SRC_0 | RCC_PLL3CFGR_PLL3SRC_1) /*!< HSE clock selected as main PLL3 entry clock source */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_PLL3_OUTPUT  PLL3  Clock Output
  * @{
  */
#define LL_RCC_PLL3_OUTPUT_P                RCC_PLL3CFGR_PLL3PEN /*!< pll3_p_ck output enabled  */
#define LL_RCC_PLL3_OUTPUT_Q                RCC_PLL3CFGR_PLL3QEN /*!< pll3_q_ck output enabled  */
#define LL_RCC_PLL3_OUTPUT_R                RCC_PLL3CFGR_PLL3REN /*!< pll3_r_ck output enabled  */
/**
  * @}
  */

/** @defgroup RCC_LL_EC_MSIRANGESEL  MSI clock range selection
  * @{
  */
#define LL_RCC_MSIRANGESEL_STANDBY         0U                  /*!< MSI Range is provided by MSISRANGE */
#define LL_RCC_MSIRANGESEL_RUN             1U                  /*!< MSI Range is provided by MSISRANGE */
/**
  * @}
  */

/** @defgroup RCC_LL_FLAGS RCC Flags
  * @{
  */
#define LL_RCC_IT_LSIRDY                  RCC_CIFR_LSIRDYF      /*!< LSI Ready interrupt flag */
#define LL_RCC_IT_LSERDY                  RCC_CIFR_LSERDYF      /*!< LSE Ready interrupt flag */
#define LL_RCC_IT_MSIRDY                  RCC_CIFR_MSISRDYF     /*!< MSI Ready interrupt flag */
#define LL_RCC_IT_HSIRDY                  RCC_CIFR_HSIRDYF      /*!< HSI16 Ready interrupt flag */
#define LL_RCC_IT_HSERDY                  RCC_CIFR_HSERDYF      /*!< HSE Ready interrupt flag */
#define LL_RCC_IT_HSI48RDY                RCC_CIFR_HSI48RDYF    /*!< HSI48 Ready interrupt flag */
#define LL_RCC_IT_PLLRDY                  RCC_CIFR_PLL1RDYF     /*!< PLL1 Ready interrupt flag */
#define LL_RCC_IT_PLL2RDY                 RCC_CIFR_PLL2RDYF     /*!< PLL2 Ready interrupt flag */
#define LL_RCC_IT_PLL3RDY                 RCC_CIFR_PLL3RDYF     /*!< PLL3 Ready interrupt flag */
#define LL_RCC_IT_HSECSS                  RCC_CIFR_CSSF         /*!< Clock Security System interrupt flag */
#define LL_RCC_IT_MSIKRDY                 RCC_CIFR_MSIKRDYF     /*!< MSIK Ready interrupt flag */
#define LL_RCC_IT_SHSIRDY                 RCC_CIFR_SHSIRDYF     /*!< SHSI Ready interrupt flag */
/**
  * @}
  */


/** @defgroup RCC_LL_EC_Security_Services Security Services
  * @note Only available when system implements security (TZEN=1).
  * @{
  */
#define LL_RCC_ALL_NSEC                    0U                      /*!< No security on RCC resources (default) */
#define LL_RCC_ALL_SEC                     RCC_SECURE_MASK         /*!< Security on all RCC resources          */

#define LL_RCC_HSI_SEC                     RCC_SECCFGR_HSISEC      /*!< HSI clock configuration security */
#define LL_RCC_HSI_NSEC                    0U                      /*!< HSI clock configuration secure/non-secure access */
#define LL_RCC_HSE_SEC                     RCC_SECCFGR_HSESEC      /*!< HSE clock configuration security */
#define LL_RCC_HSE_NSEC                    0U                      /*!< HSE clock configuration secure/non-secure access */
#define LL_RCC_MSI_SEC                     RCC_SECCFGR_MSISEC      /*!< MSI clock configuration security */
#define LL_RCC_MSI_NSEC                    0U                      /*!< MSI clock configuration secure/non-secure access */
#define LL_RCC_LSE_SEC                     RCC_SECCFGR_LSESEC      /*!< LSE clock configuration security */
#define LL_RCC_LSE_NSEC                    0U                      /*!< LSE clock configuration secure/non-secure access */
#define LL_RCC_LSI_SEC                     RCC_SECCFGR_LSISEC      /*!< LSI clock configuration security */
#define LL_RCC_LSI_NSEC                    0U                      /*!< LSI clock configuration secure/non-secure access */
#define LL_RCC_SYSCLK_SEC                  RCC_SECCFGR_SYSCLKSEC   /*!< SYSCLK clock; STOPWUCK and MCO output configuration security */
#define LL_RCC_SYSCLK_NSEC                 0U                      /*!< SYSCLK clock; STOPWUCK and MCO output configuration secure/non-secure access */
#define LL_RCC_PRESCALERS_SEC              RCC_SECCFGR_PRESCSEC    /*!< AHBx/APBx prescaler configuration security */
#define LL_RCC_PRESCALERS_NSEC             0U                      /*!< AHBx/APBx prescaler configuration secure/non-secure access */
#define LL_RCC_PLL1_SEC                    RCC_SECCFGR_PLL1SEC     /*!< PLL1 clock configuration security */
#define LL_RCC_PLL1_NSEC                   0U                      /*!< main PLL1 clock configuration secure/non-secure access */
#define LL_RCC_PLL2_SEC                    RCC_SECCFGR_PLL2SEC     /*!< PLL2 clock configuration security */
#define LL_RCC_PLL2_NSEC                   0U                      /*!< main PLL2 clock configuration secure/non-secure access */
#define LL_RCC_PLL3_SEC                    RCC_SECCFGR_PLL3SEC     /*!< PLL3 clock configuration security */
#define LL_RCC_PLL3_NSEC                   0U                      /*!< main PLL3 clock configuration secure/non-secure access */
#define LL_RCC_ICLK_SEC                    RCC_SECCFGR_ICLKSEC     /*!< ICLK clock source selection security */
#define LL_RCC_ICLK_NSEC                   0U                      /*!< ICLK clock source selection secure/non-secure access */
#define LL_RCC_HSI48_SEC                   RCC_SECCFGR_HSI48SEC    /*!< HSI48 clock configuration security */
#define LL_RCC_HSI48_NSEC                  0U                      /*!< HSI48 clock configuration secure/non-secure access */
#define LL_RCC_RESET_FLAGS_SEC             RCC_SECCFGR_RMVFSEC     /*!< Remove reset flag security */
#define LL_RCC_RESET_FLAGS_NSEC            0U
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Macros RCC Exported Macros
  * @{
  */

/** @defgroup RCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RCC register
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_RCC_WRITE_REG(reg, value) WRITE_REG(RCC->reg, (value))

/**
  * @brief  Read a value in RCC register
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_RCC_READ_REG(reg) READ_REG(RCC->reg)
/**
  * @}
  */

/** @defgroup RCC_LL_EM_CALC_FREQ Calculate frequencies
  * @{
  */

/**
  * @brief  Helper macro to calculate the PLL1CLK frequency on system domain
  * @param input_freq PLL1 Input frequency (based on MSI/HSE/HSI)
  * @param pll1m parameter can be a value between 1 and 16
  * @param pll1n parameter can be a value between 4 and 512
  * @param pll1r parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note ex: @ref LL_RCC_CALC_PLL1CLK_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetR ()).
  * @retval PLL1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_FREQ(input_freq, pll1m, pll1n, pll1r) ((((input_freq) /(pll1m)) * (pll1n)) / (pll1r))

/**
  * @brief  Helper macro to calculate the PLL1CLK frequency used on SAI domain
  * @param input_freq PLL1 Input frequency (based on MSI/HSE/HSI)
  * @param pll1m parameter can be a value between 1 and 16
  * @param pll1n parameter can be a value between 4 and 512
  * @param pll1p parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL1CLK_SAI_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetP ()).
  * @retval PLL1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_SAI_FREQ(input_freq, pll1m, pll1n, pll1p) ((((input_freq) / (pll1m)) * (pll1n)) / (pll1p))

/**
  * @brief  Helper macro to calculate the PLL1CLK frequency used on 48M domain
  * @param input_freq PLL1 Input frequency (based on MSI/HSE/HSI)
  * @param pll1m parameter can be a value between 1 and 16
  * @param pll1n parameter can be a value between 4 and 512
  * @param pll1q parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL1CLK_48M_FREQ (HSE_VALUE,@ref LL_RCC_PLL1_GetDivider (),
  *             @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetQ ()).
  * @retval PLL clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL1CLK_48M_FREQ(input_freq, pll1m, pll1n, pll1q) ((((input_freq) / (pll1m)) * (pll1n)) / (pll1q))

/**
  * @brief  Helper macro to calculate the PLL2 frequency used for SAI domain
  * @param input_freq PLL Input frequency (based on MSI/HSE/HSI)
  * @param pll2m parameter can be a value between 1 and 16
  * @param pll2n parameter can be a value between 4 and 512
  * @param pll2p parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL2CLK_SAI_FREQ (HSE_ALUE,@ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetP ()).
  * @retval PLL2 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_SAI_FREQ(input_freq, pll2m, pll2n, pll2p) ((((input_freq) / (pll2m)) * (pll2n)) / (pll2p))

/**
  * @brief  Helper macro to calculate the PLL2 frequency used on 48M domain
  * @param input_freq PLL Input frequency (based on MSI/HSE/HSI)
  * @param pll2m parameter can be a value between 1 and 16
  * @param pll2n parameter can be a value between 4 and 512
  * @param pll2q parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL2CLK_48M_FREQ (HSE_VALUE,@ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetQ ()).
  * @retval PLL2 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_48M_FREQ(input_freq, pll2m, pll2n, pll2q) ((((input_freq) / (pll2m)) * (pll2n)) / (pll2q))

/**
  * @brief  Helper macro to calculate the PLL2 frequency used on ADC domain
  * @param input_freq PLL2 Input frequency (based on MSI/HSE/HSI)
  * @param pll2m parameter can be a value between 1 and 16
  * @param pll2n parameter can be a value between 4 and 512
  * @param pll2r parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL2CLK_ADC_FREQ (HSE_VALUE,@ref LL_RCC_PLL2_GetDivider (),
  *             @ref LL_RCC_PLL2_GetN (), @ref LL_RCC_PLL2_GetR ()).
  * @retval PLL2 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL2CLK_ADC_FREQ(input_freq, pll2m, pll2n, pll2r) ((((input_freq) / (pll2m)) * (pll2n)) / (pll2r))

/**
  * @brief  Helper macro to calculate the PLL3 frequency used for SAI domain
  * @param input_freq PLL3 Input frequency (based on MSI/HSE/HSI)
  * @param pll3m parameter can be a value between 1 and 16
  * @param pll3n parameter can be a value between 4 and 512
  * @param pll3p parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL3CLK_SAI_FREQ (HSE_VALUE,@ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetP ()).
  * @retval PLL3 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_SAI_FREQ(input_freq, pll3m, pll3n, pll3p)((((input_freq) / (pll3m)) * (pll3n)) / (pll3p))

/**
  * @brief  Helper macro to calculate the PLL2 frequency used on 48M domain
  * @param input_freq PLL3 Input frequency (based on MSI/HSE/HSI)
  * @param pll3m parameter can be a value between 1 and 16
  * @param pll3n parameter can be a value between 4 and 512
  * @param pll3q parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL3CLK_48M_FREQ (HSE_VALUE,@ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetQ ()).
  * @retval PLL3 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_48M_FREQ(input_freq, pll3m, pll3n, pll3q) ((((input_freq) / (pll3m)) * (pll3n)) / (pll3q))

#if defined(HSPI1) || defined(LTDC)
/**
  * @brief  Helper macro to calculate the PLL3 frequency used on HSPI domain
  * @param input_freq PLL3 Input frequency (based on MSI/HSE/HSI)
  * @param pll3m parameter can be a value between 1 and 16
  * @param pll3n parameter can be a value between 4 and 512
  * @param pll3r parameter can be a value between 1 and 128
  * @note ex: @ref LL_RCC_CALC_PLL3CLK_HSPI_LTDC_FREQ (HSE_VALUE,@ref LL_RCC_PLL3_GetDivider (),
  *             @ref LL_RCC_PLL3_GetN (), @ref LL_RCC_PLL3_GetQ ()).
  * @retval PLL3 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PLL3CLK_HSPI_LTDC_FREQ(input_freq, pll3m, pll3n, pll3r) ((((input_freq) \
                                                                               /(pll3m)) * (pll3n)) / (pll3r))
#endif /* HSPI1 || LTDC */

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @param  sysclk_freq SYSCLK frequency (based on MSI/HSE/HSI/PLLCLK)
  * @param  ahb_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  * @retval HCLK clock frequency (in Hz)
  */
#define LL_RCC_CALC_HCLK_FREQ(sysclk_freq, ahb_prescaler) ((sysclk_freq) >> \
                                                           AHBPrescTable[((ahb_prescaler)& RCC_CFGR2_HPRE) \
                                                                         >>  RCC_CFGR2_HPRE_Pos])

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (ABP1)
  * @param  hclk_freq HCLK frequency
  * @param  apb1_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK1_FREQ(hclk_freq, apb1_prescaler) ((hclk_freq) >> \
                                                           (APBPrescTable[((apb1_prescaler)& \
                                                                           RCC_CFGR2_PPRE1) >>  RCC_CFGR2_PPRE1_Pos]))

/**
  * @brief  Helper macro to calculate the PCLK2 frequency (ABP2)
  * @param  hclk_freq HCLK frequency
  * @param  apb2_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  * @retval PCLK2 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK2_FREQ(hclk_freq, apb2_prescaler) ((hclk_freq) >>\
                                                           APBPrescTable[(apb2_prescaler) >> \
                                                                         RCC_CFGR2_PPRE2_Pos])

/**
  * @brief  Helper macro to calculate the PCLK3 frequency (ABP3)
  * @param  hclk_freq HCLK frequency
  * @param  apb3_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  * @retval PCLK3 clock frequency (in Hz)
  */
#define LL_RCC_CALC_PCLK3_FREQ(hclk_freq, apb3_prescaler) ((hclk_freq) >> \
                                                           APBPrescTable[(apb3_prescaler) >> \
                                                                         RCC_CFGR3_PPRE3_Pos])

/**
  * @brief  Helper macro to calculate the MSIS frequency (in Hz)
  * @param  msis_sel This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGESEL_STANDBY
  *         @arg @ref LL_RCC_MSIRANGESEL_RUN
  * @param  msis_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_0
  *         @arg @ref LL_RCC_MSISRANGE_1
  *         @arg @ref LL_RCC_MSISRANGE_2
  *         @arg @ref LL_RCC_MSISRANGE_3
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  *         @arg @ref LL_RCC_MSISRANGE_8
  *         @arg @ref LL_RCC_MSISRANGE_9
  *         @arg @ref LL_RCC_MSISRANGE_10
  *         @arg @ref LL_RCC_MSISRANGE_11
  *         @arg @ref LL_RCC_MSISRANGE_12
  *         @arg @ref LL_RCC_MSISRANGE_13
  *         @arg @ref LL_RCC_MSISRANGE_14
  *         @arg @ref LL_RCC_MSISRANGE_15
  * @note msis_sel can be retrieved thanks to function LL_RCC_MSI_IsEnabledRangeSelect().
  * @note if msis_sel is equal to LL_RCC_MSIRANGESEL_STANDBY,
  *        msis_range can be retrieved by LL_RCC_MSIS_GetRangeAfterStandby()
  *        else by LL_RCC_MSIS_GetRange()
  *        ex: LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
  *              (LL_RCC_MSI_IsEnabledRangeSelect()?
  *               LL_RCC_MSIS_GetRange():
  *               LL_RCC_MSIS_GetRangeAfterStandby())).
  * @retval MSI clock frequency (in Hz)
  */
#define LL_RCC_CALC_MSIS_FREQ(msis_sel, msis_range)   (((msis_sel) == LL_RCC_MSIRANGESEL_RUN) ? \
                                                       (MSIRangeTable[((msis_range) >> 28U) & 0x0FU]) : \
                                                       (MSIRangeTable[((msis_range) >> 12U) & 0x0FU]))


/**
  * @brief  Helper macro to calculate the MSIK frequency (in Hz)
  * @param  msik_sel This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIRANGESEL_STANDBY
  *         @arg @ref LL_RCC_MSIRANGESEL_RUN
  * @param  msik_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIKRANGE_0
  *         @arg @ref LL_RCC_MSIKRANGE_1
  *         @arg @ref LL_RCC_MSIKRANGE_2
  *         @arg @ref LL_RCC_MSIKRANGE_3
  *         @arg @ref LL_RCC_MSIKRANGE_4
  *         @arg @ref LL_RCC_MSIKRANGE_5
  *         @arg @ref LL_RCC_MSIKRANGE_6
  *         @arg @ref LL_RCC_MSIKRANGE_7
  *         @arg @ref LL_RCC_MSIKRANGE_8
  *         @arg @ref LL_RCC_MSIKRANGE_9
  *         @arg @ref LL_RCC_MSIKRANGE_10
  *         @arg @ref LL_RCC_MSIKRANGE_11
  *         @arg @ref LL_RCC_MSIKRANGE_12
  *         @arg @ref LL_RCC_MSIKRANGE_13
  *         @arg @ref LL_RCC_MSIKRANGE_14
  *         @arg @ref LL_RCC_MSIKRANGE_15
  * @note msik_sel can be retrieved thanks to function LL_RCC_MSIK_IsEnabledRangeSelect().
  * @note if msik_sel is equal to LL_RCC_MSIKRANGESEL_STANDBY,
  *        __MSIKRANGE__can be retrieved by LL_RCC_MSIK_GetRangeAfterStandby()
  *        else by LL_RCC_MSIK_GetRange()
  *        ex: LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSIK_IsEnabledRangeSelect(),
  *              (LL_RCC_MSIK_IsEnabledRangeSelect()?
  *               LL_RCC_MSIK_GetRange():
  *               LL_RCC_MSIK_GetRangeAfterStandby())).
  * @retval MSIK clock frequency (in Hz)
  */
#define LL_RCC_CALC_MSIK_FREQ(msik_sel, msik_range)   (((msik_sel) == LL_RCC_MSIRANGESEL_RUN) ? \
                                                       (MSIRangeTable[((msik_range) >> 24U) & 0x0FU]) : \
                                                       (MSIRangeTable[((msik_range) >> 8U) & 0x0FU]))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_LL_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_LL_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable the Clock Security System.
  * @rmtoll
  *  CR           CSSON         LL_RCC_HSE_EnableCSS
  */
__STATIC_INLINE void LL_RCC_HSE_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_CSSON);
}

/**
  * @brief  Enable HSE external oscillator (HSE Bypass)
  * @rmtoll
  *  CR           HSEBYP        LL_RCC_HSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_HSE_EnableBypass(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Configure HSE external oscillator in bypass
  * @rmtoll
  *  CR         HSEBYP        LL_RCC_HSE_ConfigBypass \n
  *  CR         HSEEXT        LL_RCC_HSE_ConfigBypass
  * @param  hse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  */
__STATIC_INLINE void LL_RCC_HSE_ConfigBypass(uint32_t hse_mode)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSEBYP | RCC_CR_HSEEXT, RCC_CR_HSEBYP | hse_mode);
}

/**
  * @brief  Disable HSE external oscillator (HSE Bypass)
  * @rmtoll
  *  CR           HSEBYP        LL_RCC_HSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_HSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Check if HSE is bypassed
  * @rmtoll
  *  CR           HSEBYP        LL_RCC_HSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsBypassed(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEBYP) == RCC_CR_HSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSE crystal oscillator (HSE ON)
  * @rmtoll
  *  CR           HSEON         LL_RCC_HSE_Enable
  */
__STATIC_INLINE void LL_RCC_HSE_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Disable HSE crystal oscillator (HSE ON)
  * @rmtoll
  *  CR           HSEON         LL_RCC_HSE_Disable
  */
__STATIC_INLINE void LL_RCC_HSE_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Check if HSE oscillator is enabled
  * @rmtoll
  *  CR           HSEON        LL_RCC_HSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSEON) == (RCC_CR_HSEON)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE oscillator Ready
  * @rmtoll
  *  CR           HSERDY        LL_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == RCC_CR_HSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Set external HSE clock mode
  * @rmtoll
  *  CR         HSEEXT        LL_RCC_HSE_SetClockMode
  * @param  hse_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  * @note This bit can be written only if the HSE oscillator is disabled.
  */
__STATIC_INLINE void LL_RCC_HSE_SetClockMode(uint32_t hse_mode)
{
  MODIFY_REG(RCC->CR, RCC_CR_HSEEXT, hse_mode);
}

/**
  * @brief  Get External HSE clock mode
  * @rmtoll
  *  CR         HSEEXT        LL_RCC_HSE_GetClockMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSE_ANALOG_MODE
  *         @arg @ref LL_RCC_HSE_DIGITAL_MODE
  */
__STATIC_INLINE uint32_t LL_RCC_HSE_GetClockMode(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSEEXT));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI even in stop mode
  * @rmtoll
  *  CR           HSIKERON      LL_RCC_HSI_EnableInStopMode
  * @note HSI oscillator is forced ON even in Stop mode.
  */
__STATIC_INLINE void LL_RCC_HSI_EnableInStopMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Disable HSI in stop mode
  * @rmtoll
  *  CR           HSIKERON      LL_RCC_HSI_DisableInStopMode
  */
__STATIC_INLINE void LL_RCC_HSI_DisableInStopMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSIKERON);
}

/**
  * @brief  Check if HSI is enabled in stop mode
  * @rmtoll
  *  CR           HSIKERON        LL_RCC_HSI_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIKERON) == RCC_CR_HSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Enable HSI oscillator
  * @rmtoll
  *  CR           HSION         LL_RCC_HSI_Enable
  */
__STATIC_INLINE void LL_RCC_HSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Disable HSI oscillator
  * @rmtoll
  *  CR           HSION         LL_RCC_HSI_Disable
  */
__STATIC_INLINE void LL_RCC_HSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Check if HSI oscillator is enabled
  * @rmtoll
  *  CR           HSION        LL_RCC_HSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSION) == (RCC_CR_HSION)) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI clock is ready
  * @rmtoll
  *  CR           HSIRDY        LL_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RCC_CR_HSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI Calibration value
  * @rmtoll
  *  ICSCR3       HSICAL        LL_RCC_HSI_GetCalibration
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value.
  * @retval Between Min_Data = 0 and Max_Data = 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR3, RCC_ICSCR3_HSICAL) >> RCC_ICSCR3_HSICAL_Pos);
}

/**
  * @brief  Set HSI Calibration trimming
  * @rmtoll
  *  ICSCR3        HSITRIM       LL_RCC_HSI_SetCalibTrimming
  * @param  value Between Min_Data = 0 and Max_Data = 127
  * @note user-programmable trimming value that is added to the HSICAL.
  * @note Default value is 64, which, when added to the HSICAL value,
  *       trim the HSI to 16 MHz +/- 1 %.
  */
__STATIC_INLINE void LL_RCC_HSI_SetCalibTrimming(uint32_t value)
{
  MODIFY_REG(RCC->ICSCR3, RCC_ICSCR3_HSITRIM, value << RCC_ICSCR3_HSITRIM_Pos);
}

/**
  * @brief  Get HSI Calibration trimming
  * @rmtoll
  *  ICSC3R        HSITRIM       LL_RCC_HSI_GetCalibTrimming
  * @retval Between Min_Data = 0 and Max_Data = 127
  */
__STATIC_INLINE uint32_t LL_RCC_HSI_GetCalibTrimming(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR3, RCC_ICSCR3_HSITRIM) >> RCC_ICSCR3_HSITRIM_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_HSI48 HSI48
  * @{
  */

/**
  * @brief  Enable HSI48
  * @rmtoll
  *  CR          HSI48ON       LL_RCC_HSI48_Enable
  */
__STATIC_INLINE void LL_RCC_HSI48_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Disable HSI48
  * @rmtoll
  *  CR          HSI48ON       LL_RCC_HSI48_Disable
  */
__STATIC_INLINE void LL_RCC_HSI48_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSI48ON);
}

/**
  * @brief  Check if HSI48 oscillator is enabled
  * @rmtoll
  *  CR           HSI48ON        LL_RCC_HSI48_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSI48ON) == RCC_CR_HSI48ON) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48 oscillator Ready
  * @rmtoll
  *  CR          HSI48RDY      LL_RCC_HSI48_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_HSI48RDY) == RCC_CR_HSI48RDY) ? 1UL : 0UL);
}

/**
  * @brief  Get HSI48 Calibration value
  * @rmtoll
  *  CRRCR          HSI48CAL      LL_RCC_HSI48_GetCalibration
  * @retval Between Min_Data = 0x00 and Max_Data = 0x1FF
  */
__STATIC_INLINE uint32_t LL_RCC_HSI48_GetCalibration(void)
{
  return (uint32_t)(READ_BIT(RCC->CRRCR, RCC_CRRCR_HSI48CAL) >> RCC_CRRCR_HSI48CAL_Pos);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll
  *  BDCR         LSEON         LL_RCC_LSE_Enable
  */
__STATIC_INLINE void LL_RCC_LSE_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll
  *  BDCR         LSEON         LL_RCC_LSE_Disable
  */
__STATIC_INLINE void LL_RCC_LSE_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll
  *  BDCR         LSEBYP        LL_RCC_LSE_EnableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_EnableBypass(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll
  *  BDCR         LSEBYP        LL_RCC_LSE_DisableBypass
  */
__STATIC_INLINE void LL_RCC_LSE_DisableBypass(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Check if LSE oscillator is bypassed
  * @rmtoll
  *  BDCR         RCC_BDCR_LSEBYP        LL_RCC_LSE_IsBypassed
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsBypassed(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP) ? 1UL : 0UL);
}

/**
  * @brief  Set LSE oscillator drive capability
  * @rmtoll
  *  BDCR         LSEDRV        LL_RCC_LSE_SetDriveCapability
  * @param  lse_drive This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  */
__STATIC_INLINE void LL_RCC_LSE_SetDriveCapability(uint32_t lse_drive)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, lse_drive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll
  *  BDCR         LSEDRV        LL_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSEDRIVE_LOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref LL_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref LL_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_GetDriveCapability(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSEDRV));
}

/**
  * @brief  Enable Clock security system on LSE.
  * @rmtoll
  *  BDCR         LSECSSON      LL_RCC_LSE_EnableCSS
  */
__STATIC_INLINE void LL_RCC_LSE_EnableCSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable Clock security system on LSE.
  * @rmtoll
  *  BDCR         LSECSSON      LL_RCC_LSE_DisableCSS
  * @note Clock security system can be disabled only after a LSE
  *       failure detection. In that case it must be disabled by software.
  */
__STATIC_INLINE void LL_RCC_LSE_DisableCSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Check if LSE oscillator is enabled
  * @rmtoll
  *  BDCR           LSEON        LL_RCC_LSE_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEON) == (RCC_BDCR_LSEON)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll
  *  BDCR         LSERDY        LL_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == RCC_BDCR_LSERDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE oscillator propagation for system clock
  * @rmtoll
  *  BDCR         LSESYSEN      LL_RCC_LSE_EnablePropagation
  */
__STATIC_INLINE void LL_RCC_LSE_EnablePropagation(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Disable LSE oscillator propagation for system clock
  * @rmtoll
  *  BDCR         LSESYSEN      LL_RCC_LSE_DisablePropagation
  */
__STATIC_INLINE void LL_RCC_LSE_DisablePropagation(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);
}

/**
  * @brief  Check if LSE oscillator propagation is enabled
  * @rmtoll
  *  BDCR         RCC_BDCR_LSESYSEN     LL_RCC_LSE_IsPropagationEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsPropagationEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN) == RCC_BDCR_LSESYSEN) ? 1UL : 0UL);
}


/**
  * @brief  Check if LSE oscillator propagation for system clock Ready
  * @rmtoll
  *  BDCR         LSESYSRDY     LL_RCC_LSE_IsPropagationReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsPropagationReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) == RCC_BDCR_LSESYSRDY) ? 1UL : 0UL);
}

/**
  * @brief  Check if CSS on LSE failure Detection
  * @rmtoll
  *  BDCR         LSECSSD       LL_RCC_LSE_IsCSSDetected
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsCSSDetected(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) == RCC_BDCR_LSECSSD) ? 1UL : 0UL);
}

/**
  * @brief  Enable LSE clock glitch filter.
  * @rmtoll
  *  BDCR         LSEGFON      LL_RCC_LSE_EnableGlitchFilter
  * @note   The glitches on LSE can be filtred by setting the LSEGFON.
  * @note   LSEGFON must be written when the LSE is disabled (LSEON = 0 and LSERDY = 0).
  */
__STATIC_INLINE void LL_RCC_LSE_EnableGlitchFilter(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEGFON);
}

/**
  * @brief  Disable LSE clock glitch filter.
  * @rmtoll
  *  BDCR         LSEGFON      LL_RCC_LSE_DisableGlitchFilter
  * @note   LSEGFON must be written when the LSE is disabled (LSEON = 0 and LSERDY = 0).
  */
__STATIC_INLINE void LL_RCC_LSE_DisableGlitchFilter(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEGFON);
}

/**
  * @brief  Check if LSE clock glitch filter is enabled
  * @rmtoll
  *  BDCR         LSEGFON        LL_RCC_LSE_IsGlitchFilterEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSE_IsGlitchFilterEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSEGFON) == RCC_BDCR_LSEGFON) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI Oscillator
  * @rmtoll
  *  BDCR          LSION         LL_RCC_LSI_Enable
  */
__STATIC_INLINE void LL_RCC_LSI_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSION);
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll
  *  BDCR          LSION         LL_RCC_LSI_Disable
  */
__STATIC_INLINE void LL_RCC_LSI_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSION);
}

/**
  * @brief  Check if LSI oscillator is enabled
  * @rmtoll
  *  BDCR           LSION        LL_RCC_LSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSION) == (RCC_BDCR_LSION)) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll
  *  BDCR          LSIRDY        LL_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_IsReady(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_LSIRDY) == RCC_BDCR_LSIRDY) ? 1UL : 0UL);
}

/**
  * @brief  Set LSI prescaler
  * @rmtoll
  *  BDCR          LSIPREDIV        LL_RCC_LSI_SetPrescaler
  * @param  lsi_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSI_DIV_1
  *         @arg @ref LL_RCC_LSI_DIV_128
  */
__STATIC_INLINE void LL_RCC_LSI_SetPrescaler(uint32_t lsi_prescaler)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSIPREDIV, lsi_prescaler);
}

/**
  * @brief  Get LSI prescaler
  * @rmtoll
  *  BDCR          LSIPREDIV        LL_RCC_LSI_GetPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSI_DIV_1
  *         @arg @ref LL_RCC_LSI_DIV_128
  */
__STATIC_INLINE uint32_t LL_RCC_LSI_GetPrescaler(void)
{
  return (READ_BIT(RCC->BDCR, RCC_BDCR_LSIPREDIV));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_SHSI SHSI
  * @{
  */

/**
  * @brief  Enable SHSI oscillator
  * @rmtoll
  *  CR           SHSION         LL_RCC_SHSI_Enable
  */
__STATIC_INLINE void LL_RCC_SHSI_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_SHSION);
}

/**
  * @brief  Disable SHSI oscillator
  * @rmtoll
  *  CR           SHSION         LL_RCC_SHSI_Disable
  */
__STATIC_INLINE void LL_RCC_SHSI_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_SHSION);
}

/**
  * @brief  Check if SHSI oscillator is enabled
  * @rmtoll
  *  CR          SHSION      LL_RCC_SHSI_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_SHSI_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_SHSION) == RCC_CR_SHSION) ? 1UL : 0UL);
}

/**
  * @brief  Check if SHSI oscillator Ready
  * @rmtoll
  *  CR           SHSIRDY        LL_RCC_SHSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_SHSI_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_SHSIRDY) == RCC_CR_SHSIRDY) ? 1UL : 0UL);
}
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MSI MSI
  * @{
  */

/**
  * @brief  Enable MSIS oscillator
  * @rmtoll
  *  CR           MSISON         LL_RCC_MSIS_Enable
  */
__STATIC_INLINE void LL_RCC_MSIS_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSISON);
}

/**
  * @brief  Disable MSIS oscillator
  * @rmtoll
  *  CR           MSISON         LL_RCC_MSIS_Disable
  */
__STATIC_INLINE void LL_RCC_MSIS_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSISON);
}

/**
  * @brief  Check if MSIS oscillator is enabled
  * @rmtoll
  *  CR           MSISON        LL_RCC_MSIS_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSISON) == RCC_CR_MSISON) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSIS oscillator Ready
  * @rmtoll
  *  CR           MSISRDY        LL_RCC_MSIS_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSISRDY) == RCC_CR_MSISRDY) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSI PLL-mode (Hardware auto calibration with LSE)
  * @rmtoll
  *  CR           MSIPLLEN      LL_RCC_MSI_EnablePLLMode
  * @note MSIPLLEN must be enabled after LSE is enabled (LSEON enabled)
  *       and ready (LSERDY set by hardware).
  * @note hardware protection to avoid enabling MSIPLLEN if LSE is not ready.
  */
__STATIC_INLINE void LL_RCC_MSI_EnablePLLMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Disable MSI-PLL mode
  * @rmtoll
  *  CR           MSIPLLEN      LL_RCC_MSI_DisablePLLMode
  * @note cleared by hardware when LSE is disabled (LSEON = 0) or when
  *       the Clock Security System on LSE detects a LSE failure.
  */
__STATIC_INLINE void LL_RCC_MSI_DisablePLLMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Check if MSI-PLL mode has been enabled or not
  * @rmtoll
  *  CR           MSIPLLEN      LL_RCC_IsEnabledPLLMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledPLLMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIPLLEN) == RCC_CR_MSIPLLEN) ? 1UL : 0UL);
}

/**
  * @brief Set clock source in PLL mode
  * @rmtoll
  *  CR          MSIPLLSEL         LL_RCC_SetMSIPLLMode
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLMODE_MSIS
  *         @arg @ref LL_RCC_PLLMODE_MSIK
  * @note   Bit can be written only when the MSI PLL mode is disabled (MSIPLLEN = 0)
  */
__STATIC_INLINE void LL_RCC_SetMSIPLLMode(uint32_t source)
{
  MODIFY_REG(RCC->CR, RCC_CR_MSIPLLSEL, source);
}

/**
  * @brief  Get Clock source in PLL Mode
  * @rmtoll
  *  CR         MSIPLLSEL        LL_RCC_GetMSIPLLMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLLMODE_MSIS
  *         @arg @ref LL_RCC_PLLMODE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetMSIPLLMode(void)
{
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_MSIPLLSEL));
}

/**
  * @brief Configure the HW auto calibration with LSE.
  * @rmtoll
  *  CR          MSIPLLSEL         LL_RCC_MSI_ConfigHWAutoCalib \n
  *  CR          MSIPLLFAST        LL_RCC_MSI_ConfigHWAutoCalib
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLMODE_MSIS
  *         @arg @ref LL_RCC_PLLMODE_MSIK
  * @param  pll_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLFAST_NORMAL
  *         @arg @ref LL_RCC_PLLFAST_FAST
  * @note   Bit can be written only when the MSI PLL mode is disabled (MSIPLLEN = 0)
  */
__STATIC_INLINE void LL_RCC_MSI_ConfigHWAutoCalib(uint32_t source, uint32_t pll_mode)
{
  MODIFY_REG(RCC->CR, RCC_CR_MSIPLLSEL | RCC_CR_MSIPLLFAST, source | pll_mode);
}


/**
  * @brief  Enable MSI fast mode
  * @rmtoll
  *  CR           MSIPLLFAST        LL_RCC_Enable_MSIPLLFAST
  * @note     This bit is used only if PLL mode is selected.
  */
__STATIC_INLINE void LL_RCC_Enable_MSIPLLFAST(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLLFAST);
}

/**
  * @brief  Disable MSI fast mode
  * @rmtoll
  *  CR           MSIPLLFAST        LL_RCC_Disable_MSIPLLFAST
  * @note     This bit is used only if PLL mode is selected.
  */
__STATIC_INLINE void LL_RCC_Disable_MSIPLLFAST(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLFAST);
}

/**
  * @brief  Check if MSI PLL Fast Mode is enable
  * @rmtoll
  *  CR           MSIPLLFAST        LL_RCC_MSI_IsEnabledMSIPLLFAST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsEnabledMSIPLLFAST(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIPLLFAST) == RCC_CR_MSIPLLFAST) ? 1UL : 0UL);
}

/**
  * @brief  Set MSI Bias mode
  * @rmtoll
  *  ICSCR1         MSIBIAS        LL_RCC_MSI_SetMSIBiasMode
  * @param  bias_mode This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIBIASMODE_CONTINUOUS
  *         @arg @ref LL_RCC_MSIBIASMODE_SAMPLING

  */
__STATIC_INLINE void LL_RCC_MSI_SetMSIBiasMode(uint32_t bias_mode)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIBIAS, bias_mode);
}

/**
  * @brief  Get MSI Bias mode
  * @rmtoll
  *  ICSCR1         MSIBIAS        LL_RCC_MSI_GetMSIBiasMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIBIASMODE_CONTINUOUS
  *         @arg @ref LL_RCC_MSIBIASMODE_SAMPLING

  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetMSIBiasMode(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIBIAS));
}

/**
  * @brief  Enable MSIK even in stop mode
  * @rmtoll
  *  CR           MSIKERON      LL_RCC_MSIK_EnableInStopMode
  * @note MSIK oscillator is forced ON even in Stop mode.
  */
__STATIC_INLINE void LL_RCC_MSIK_EnableInStopMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIKERON);
}

/**
  * @brief  Disable MSIK in stop mode
  * @rmtoll
  *  CR           MSIKERON      LL_RCC_MSIK_DisableInStopMode
  */
__STATIC_INLINE void LL_RCC_MSIK_DisableInStopMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIKERON);
}

/**
  * @brief  Check if MSIK is enabled in stop mode
  * @rmtoll
  *  CR           MSIKERON        LL_RCC_MSIK_IsEnabledInStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_IsEnabledInStopMode(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIKERON) == RCC_CR_MSIKERON) ? 1UL : 0UL);
}

/**
  * @brief  Enable MSI clock range selection with MSIRANGE register
  * @rmtoll
  *  ICSCR1         MSIRGSEL      LL_RCC_MSI_EnableRangeSelection
  * @note Write 0 has no effect. After a standby or a reset.
  *       MSIRGSEL is at 0 and the MSI range value is provided by MSISRANGE.
  */
__STATIC_INLINE void LL_RCC_MSI_EnableRangeSelection(void)
{
  SET_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL);
}

/**
  * @brief  Check if MSI clock range is selected with MSIRANGE register
  * @rmtoll
  *  ICSCR1         MSIRGSEL      LL_RCC_MSI_IsEnabledRangeSelect
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_IsEnabledRangeSelect(void)
{
  return ((READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL) == RCC_ICSCR1_MSIRGSEL) ? 1UL : 0UL);
}

/**
  * @brief  Configure the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll
  *  ICSCR1         MSISRANGE      LL_RCC_MSIS_SetRange
  * @param  range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_0
  *         @arg @ref LL_RCC_MSISRANGE_1
  *         @arg @ref LL_RCC_MSISRANGE_2
  *         @arg @ref LL_RCC_MSISRANGE_3
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  *         @arg @ref LL_RCC_MSISRANGE_8
  *         @arg @ref LL_RCC_MSISRANGE_9
  *         @arg @ref LL_RCC_MSISRANGE_10
  *         @arg @ref LL_RCC_MSISRANGE_11
  *         @arg @ref LL_RCC_MSISRANGE_12
  *         @arg @ref LL_RCC_MSISRANGE_13
  *         @arg @ref LL_RCC_MSISRANGE_14
  *         @arg @ref LL_RCC_MSISRANGE_15
  */
__STATIC_INLINE void LL_RCC_MSIS_SetRange(uint32_t range)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSISRANGE, range);
}

/**
  * @brief  Switch automatically to the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll
  *  ICSCR1         MSISRANGE      LL_RCC_MSIS_SwitchRange \n
  *  ICSCR1         MSIRGSEL       LL_RCC_MSIS_SwitchRange
  * @param  range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_0
  *         @arg @ref LL_RCC_MSISRANGE_1
  *         @arg @ref LL_RCC_MSISRANGE_2
  *         @arg @ref LL_RCC_MSISRANGE_3
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  *         @arg @ref LL_RCC_MSISRANGE_8
  *         @arg @ref LL_RCC_MSISRANGE_9
  *         @arg @ref LL_RCC_MSISRANGE_10
  *         @arg @ref LL_RCC_MSISRANGE_11
  *         @arg @ref LL_RCC_MSISRANGE_12
  *         @arg @ref LL_RCC_MSISRANGE_13
  *         @arg @ref LL_RCC_MSISRANGE_14
  *         @arg @ref LL_RCC_MSISRANGE_15
  * @note   MSI clock range selection is automatically set
  */
__STATIC_INLINE void LL_RCC_MSIS_SwitchRange(uint32_t range)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL | RCC_ICSCR1_MSISRANGE, RCC_ICSCR1_MSIRGSEL | range);
}

/**
  * @brief  Get the Internal Multi Speed oscillator (MSI) clock range in run mode.
  * @rmtoll
  *  ICSCR1          MSISRANGE      LL_RCC_MSIS_GetRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSISRANGE_0
  *         @arg @ref LL_RCC_MSISRANGE_1
  *         @arg @ref LL_RCC_MSISRANGE_2
  *         @arg @ref LL_RCC_MSISRANGE_3
  *         @arg @ref LL_RCC_MSISRANGE_4
  *         @arg @ref LL_RCC_MSISRANGE_5
  *         @arg @ref LL_RCC_MSISRANGE_6
  *         @arg @ref LL_RCC_MSISRANGE_7
  *         @arg @ref LL_RCC_MSISRANGE_8
  *         @arg @ref LL_RCC_MSISRANGE_9
  *         @arg @ref LL_RCC_MSISRANGE_10
  *         @arg @ref LL_RCC_MSISRANGE_11
  *         @arg @ref LL_RCC_MSISRANGE_12
  *         @arg @ref LL_RCC_MSISRANGE_13
  *         @arg @ref LL_RCC_MSISRANGE_14
  *         @arg @ref LL_RCC_MSISRANGE_15
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_GetRange(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSISRANGE));
}

/**
  * @brief  Configure MSIS range used after standby
  * @rmtoll
  *  CSR          MSISSRANGE     LL_RCC_MSIS_SetRangeAfterStandby
  * @param  range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSISSRANGE_4
  *         @arg @ref LL_RCC_MSISSRANGE_5
  *         @arg @ref LL_RCC_MSISSRANGE_6
  *         @arg @ref LL_RCC_MSISSRANGE_7
  *         @arg @ref LL_RCC_MSISSRANGE_8
  */
__STATIC_INLINE void LL_RCC_MSIS_SetRangeAfterStandby(uint32_t range)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_MSISSRANGE, range);
}

/**
  * @brief  Get MSIS range used after standby
  * @rmtoll
  *  CSR          MSISSRANGE     LL_RCC_MSIS_GetRangeAfterStandby
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSISSRANGE_4
  *         @arg @ref LL_RCC_MSISSRANGE_5
  *         @arg @ref LL_RCC_MSISSRANGE_6
  *         @arg @ref LL_RCC_MSISSRANGE_7
  *         @arg @ref LL_RCC_MSISSRANGE_8
  */
__STATIC_INLINE uint32_t LL_RCC_MSIS_GetRangeAfterStandby(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSISSRANGE));
}

/**
  * @brief  Set MSI OSCILLATORx Calibration trimming
  * @rmtoll
  *  ICSCR2        MSITRIMx       LL_RCC_MSI_SetCalibTrimming
  * @param  value Between Min_Data = 0 and Max_Data = 31
  * @param  Oscillator  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_0
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_1
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_2
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_3
  * @note user-programmable trimming value that is added to the MSICALx.
  */
__STATIC_INLINE void LL_RCC_MSI_SetCalibTrimming(uint32_t value, uint32_t Oscillator)
{
  MODIFY_REG(RCC->ICSCR2, (RCC_ICSCR2_MSITRIM0  >> Oscillator),
             value << (uint8_t)(RCC_ICSCR2_MSITRIM0_Pos - (Oscillator & 0xFU)));
}

/**
  * @brief  Get MSI OSCILLATORx Calibration trimming
  * @rmtoll
  *  ICSCR2        MSITRIMx       LL_RCC_MSI_GetCalibTrimming
  * @retval Between 0 and 31
  * @param  Oscillator  This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_0
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_1
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_2
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_3
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibTrimming(uint32_t Oscillator)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR2, (RCC_ICSCR2_MSITRIM0  >> Oscillator))
                    >> (uint8_t)(RCC_ICSCR2_MSITRIM0_Pos - (Oscillator & 0xFU)));
}

/**
  * @brief  Get MSI OSCILLATORx Calibration value
  * @rmtoll
  *  ICSCR1        MSICALx        LL_RCC_MSI_GetCalibration
  * @param  Oscillator   This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_0
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_1
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_2
  *         @arg @ref LL_RCC_MSI_OSCILLATOR_3
  * @note When MSITRIMx is written, MSICALx is updated with the sum of
  *       MSITRIMx and the factory trim value.
  * @retval Between Min_Data = 0 and Max_Data = 31
  */
__STATIC_INLINE uint32_t LL_RCC_MSI_GetCalibration(uint32_t Oscillator)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, (RCC_ICSCR1_MSICAL0 >> Oscillator))
                    >> (uint8_t)(RCC_ICSCR1_MSICAL0_Pos - (Oscillator & 0xFU)));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MSIK MSIK
  * @{
  */

/**
  * @brief  Enable MSIK oscillator
  * @rmtoll
  *  CR           MSIKON         LL_RCC_MSIK_Enable
  */
__STATIC_INLINE void LL_RCC_MSIK_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIKON);
}

/**
  * @brief  Disable MSIK oscillator
  * @rmtoll
  *  CR           MSIKON         LL_RCC_MSIK_Disable
  */
__STATIC_INLINE void LL_RCC_MSIK_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIKON);
}

/**
  * @brief  Check if MSIK oscillator is enabled
  * @rmtoll
  *  CR           MSIKON        LL_RCC_MSIK_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_IsEnabled(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIKON) == RCC_CR_MSIKON) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSIK oscillator Ready
  * @rmtoll
  *  CR           MSIKRDY        LL_RCC_MSIK_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_MSIKRDY) == RCC_CR_MSIKRDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure the Internal Multi Speed oscillator (MSIK) clock range in run mode.
  * @rmtoll
  *  ICSCR1         MSIKRANGE      LL_RCC_MSIK_SetRange
  * @param  range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIKRANGE_0
  *         @arg @ref LL_RCC_MSIKRANGE_1
  *         @arg @ref LL_RCC_MSIKRANGE_2
  *         @arg @ref LL_RCC_MSIKRANGE_3
  *         @arg @ref LL_RCC_MSIKRANGE_4
  *         @arg @ref LL_RCC_MSIKRANGE_5
  *         @arg @ref LL_RCC_MSIKRANGE_6
  *         @arg @ref LL_RCC_MSIKRANGE_7
  *         @arg @ref LL_RCC_MSIKRANGE_8
  *         @arg @ref LL_RCC_MSIKRANGE_9
  *         @arg @ref LL_RCC_MSIKRANGE_10
  *         @arg @ref LL_RCC_MSIKRANGE_11
  *         @arg @ref LL_RCC_MSIKRANGE_12
  *         @arg @ref LL_RCC_MSIKRANGE_13
  *         @arg @ref LL_RCC_MSIKRANGE_14
  *         @arg @ref LL_RCC_MSIKRANGE_15
  */
__STATIC_INLINE void LL_RCC_MSIK_SetRange(uint32_t range)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIKRANGE, range);
}

/**
  * @brief  Switch automatically to the Internal Multi Speed oscillator (MSIK) clock range in run mode.
  * @rmtoll
  *  ICSCR1         MSIKRANGE      LL_RCC_MSIK_SwitchRange \n
  *  ICSCR1         MSIRGSEL       LL_RCC_MSIK_SwitchRange
  * @param  range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIKRANGE_0
  *         @arg @ref LL_RCC_MSIKRANGE_1
  *         @arg @ref LL_RCC_MSIKRANGE_2
  *         @arg @ref LL_RCC_MSIKRANGE_3
  *         @arg @ref LL_RCC_MSIKRANGE_4
  *         @arg @ref LL_RCC_MSIKRANGE_5
  *         @arg @ref LL_RCC_MSIKRANGE_7
  *         @arg @ref LL_RCC_MSIKRANGE_6
  *         @arg @ref LL_RCC_MSIKRANGE_8
  *         @arg @ref LL_RCC_MSIKRANGE_9
  *         @arg @ref LL_RCC_MSIKRANGE_10
  *         @arg @ref LL_RCC_MSIKRANGE_11
  *         @arg @ref LL_RCC_MSIKRANGE_12
  *         @arg @ref LL_RCC_MSIKRANGE_13
  *         @arg @ref LL_RCC_MSIKRANGE_14
  *         @arg @ref LL_RCC_MSIKRANGE_15
  * @note   MSI clock range selection is automatically set
  */
__STATIC_INLINE void LL_RCC_MSIK_SwitchRange(uint32_t range)
{
  MODIFY_REG(RCC->ICSCR1, RCC_ICSCR1_MSIRGSEL | RCC_ICSCR1_MSIKRANGE, RCC_ICSCR1_MSIRGSEL | range);
}

/**
  * @brief  Get the Internal Multi Speed oscillator (MSIK) clock range in run mode.
  * @rmtoll
  *  ICSCR1           MSIKRANGE      LL_RCC_MSIK_GetRange
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIKRANGE_0
  *         @arg @ref LL_RCC_MSIKRANGE_1
  *         @arg @ref LL_RCC_MSIKRANGE_2
  *         @arg @ref LL_RCC_MSIKRANGE_3
  *         @arg @ref LL_RCC_MSIKRANGE_4
  *         @arg @ref LL_RCC_MSIKRANGE_5
  *         @arg @ref LL_RCC_MSIKRANGE_6
  *         @arg @ref LL_RCC_MSIKRANGE_7
  *         @arg @ref LL_RCC_MSIKRANGE_8
  *         @arg @ref LL_RCC_MSIKRANGE_9
  *         @arg @ref LL_RCC_MSIKRANGE_10
  *         @arg @ref LL_RCC_MSIKRANGE_11
  *         @arg @ref LL_RCC_MSIKRANGE_12
  *         @arg @ref LL_RCC_MSIKRANGE_13
  *         @arg @ref LL_RCC_MSIKRANGE_14
  *         @arg @ref LL_RCC_MSIKRANGE_15
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_GetRange(void)
{
  return (uint32_t)(READ_BIT(RCC->ICSCR1, RCC_ICSCR1_MSIKRANGE));
}

/**
  * @brief  Configure MSIK range used after standby
  * @rmtoll
  *  CSR          MSIKSRANGE     LL_RCC_MSIK_SetRangeAfterStandby
  * @param  range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MSIKSRANGE_4
  *         @arg @ref LL_RCC_MSIKSRANGE_5
  *         @arg @ref LL_RCC_MSIKSRANGE_6
  *         @arg @ref LL_RCC_MSIKSRANGE_7
  *         @arg @ref LL_RCC_MSIKSRANGE_8
  */
__STATIC_INLINE void LL_RCC_MSIK_SetRangeAfterStandby(uint32_t range)
{
  MODIFY_REG(RCC->CSR, RCC_CSR_MSIKSRANGE, range);
}

/**
  * @brief  Get MSIK range used after standby
  * @rmtoll
  *  CSR          MSIKSRANGE     LL_RCC_MSIK_GetRangeAfterStandby
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MSIKSRANGE_4
  *         @arg @ref LL_RCC_MSIKSRANGE_5
  *         @arg @ref LL_RCC_MSIKSRANGE_6
  *         @arg @ref LL_RCC_MSIKSRANGE_7
  *         @arg @ref LL_RCC_MSIKSRANGE_8
  */
__STATIC_INLINE uint32_t LL_RCC_MSIK_GetRangeAfterStandby(void)
{
  return (uint32_t)(READ_BIT(RCC->CSR, RCC_CSR_MSIKSRANGE));
}
/**
  * @}
  */

/** @defgroup RCC_LL_EF_LSCO LSCO
  * @{
  */

/**
  * @brief  Enable Low speed clock
  * @rmtoll
  *  BDCR         LSCOEN        LL_RCC_LSCO_Enable
  */
__STATIC_INLINE void LL_RCC_LSCO_Enable(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Disable Low speed clock
  * @rmtoll
  *  BDCR         LSCOEN        LL_RCC_LSCO_Disable
  */
__STATIC_INLINE void LL_RCC_LSCO_Disable(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);
}

/**
  * @brief  Configure Low speed clock selection
  * @rmtoll
  *  BDCR         LSCOSEL       LL_RCC_LSCO_SetSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE void LL_RCC_LSCO_SetSource(uint32_t source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL, source);
}

/**
  * @brief  Get Low speed clock selection
  * @rmtoll
  *  BDCR         LSCOSEL       LL_RCC_LSCO_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_LSCO_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSCOSEL));
}

/**
  * @brief  Configure Low speed clock
  * @rmtoll
  *  BDCR         LSCOSEL       LL_RCC_ConfigLSCO\n
  *         BDCR         LSCOEN        LL_RCC_ConfigLSCO
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LSCO_CLKSOURCE_LSE
  * @note  PWR and backup domain must be previously enabled.
  */
__STATIC_INLINE void LL_RCC_ConfigLSCO(uint32_t source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL | RCC_BDCR_LSCOEN, source | RCC_BDCR_LSCOEN);
}


/**
  * @}
  */

/** @defgroup RCC_LL_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll
  *  CFGR1         SW           LL_RCC_SetSysClkSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_MSIS
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_PLL1
  */
__STATIC_INLINE void LL_RCC_SetSysClkSource(uint32_t source)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, source);
}

/**
  * @brief  Get the system clock source
  * @rmtoll
  *  CFGR1        SWS           LL_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_MSIS
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref LL_RCC_SYS_CLKSOURCE_STATUS_PLL1
  */
__STATIC_INLINE uint32_t LL_RCC_GetSysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS));
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll
  *  CFGR2        HPRE          LL_RCC_SetAHBPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  */
__STATIC_INLINE void LL_RCC_SetAHBPrescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_HPRE, prescaler);
}

/**
  * @brief  Set Systick clock source
  * @rmtoll
  *  CCIPR1      SYSTICKSEL    LL_RCC_SetSystickClockSource
  * @param  SystickSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  */
__STATIC_INLINE void LL_RCC_SetSystickClockSource(uint32_t SystickSource)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL, SystickSource);
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll
  *  CFGR2         PPRE1         LL_RCC_SetAPB1Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB1Prescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE1, prescaler);
}

/**
  * @brief  Set APB2 prescaler
  * @rmtoll
  *  CFGR2         PPRE2         LL_RCC_SetAPB2Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB2Prescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE2, prescaler);
}

/**
  * @brief  Set APB3 prescaler
  * @rmtoll
  *  CFGR3         PPRE3         LL_RCC_SetAPB3Prescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_SetAPB3Prescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_PPRE3, prescaler);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll
  *  CFGR2         HPRE          LL_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  */
__STATIC_INLINE uint32_t LL_RCC_GetAHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_HPRE));
}

/**
  * @brief  Get Sysctick clock source
  * @rmtoll
  *  CCIPR1       SYSTICKSEL    LL_RCC_GetSystickClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_SYSTICK_CLKSOURCE_HCLKDIV8
  */
__STATIC_INLINE uint32_t LL_RCC_GetSystickClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_SYSTICKSEL));
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll
  *  CFGR2         PPRE1         LL_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE1));
}

/**
  * @brief  Get APB2 prescaler
  * @rmtoll
  *  CFGR2         PPRE2         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE2));
}

/**
  * @brief  Get APB3 prescaler
  * @rmtoll
  *  CFGR3         PPRE3         LL_RCC_GetAPB2Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetAPB3Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR3, RCC_CFGR3_PPRE3));
}

/**
  * @brief  Configure buses prescalers (AHB, APB1, APB2 & APB3)
  * @rmtoll
  *  CFGR2         HPRE          LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE1         LL_RCC_ConfigBusClock \n
  *  CFGR2         PPRE2         LL_RCC_ConfigBusClock \n
  *  CFGR3         PPRE3         LL_RCC_ConfigBusClock
  * @param  ahb_abp1_abp2_pres Bus Prescalers values of AHB, APB1 & APB2
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_HCLK_PRESCALER_1
  *         @arg @ref LL_RCC_HCLK_PRESCALER_2
  *         @arg @ref LL_RCC_HCLK_PRESCALER_4
  *         @arg @ref LL_RCC_HCLK_PRESCALER_8
  *         @arg @ref LL_RCC_HCLK_PRESCALER_16
  *         @arg @ref LL_RCC_HCLK_PRESCALER_64
  *         @arg @ref LL_RCC_HCLK_PRESCALER_128
  *         @arg @ref LL_RCC_HCLK_PRESCALER_256
  *         @arg @ref LL_RCC_HCLK_PRESCALER_512
  *         @arg @ref LL_RCC_APB1_PRESCALER_1
  *         @arg @ref LL_RCC_APB1_PRESCALER_2
  *         @arg @ref LL_RCC_APB1_PRESCALER_4
  *         @arg @ref LL_RCC_APB1_PRESCALER_8
  *         @arg @ref LL_RCC_APB1_PRESCALER_16
  *         @arg @ref LL_RCC_APB2_PRESCALER_1
  *         @arg @ref LL_RCC_APB2_PRESCALER_2
  *         @arg @ref LL_RCC_APB2_PRESCALER_4
  *         @arg @ref LL_RCC_APB2_PRESCALER_8
  *         @arg @ref LL_RCC_APB2_PRESCALER_16
  * @param  apb3_pres This parameter can be one of the following values:
  *         @arg @ref LL_RCC_APB3_PRESCALER_1
  *         @arg @ref LL_RCC_APB3_PRESCALER_2
  *         @arg @ref LL_RCC_APB3_PRESCALER_4
  *         @arg @ref LL_RCC_APB3_PRESCALER_8
  *         @arg @ref LL_RCC_APB3_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_ConfigBusClock(uint32_t ahb_abp1_abp2_pres, uint32_t apb3_pres)
{
  MODIFY_REG(RCC->CFGR2, (RCC_CFGR2_HPRE | RCC_CFGR2_PPRE1 | RCC_CFGR2_PPRE2), ahb_abp1_abp2_pres);
  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_PPRE3, apb3_pres);
}

#if defined(RCC_CFGR2_PPRE_DPHY)
/**
  * @brief  Set DPHY clock prescaler
  * @rmtoll
  *  CFGR2         PPRE_DPHY         LL_RCC_SetDPHYPrescaler
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DPHY_DIV_1
  *         @arg @ref LL_RCC_DPHY_DIV_2
  *         @arg @ref LL_RCC_DPHY_DIV_4
  *         @arg @ref LL_RCC_DPHY_DIV_8
  *         @arg @ref LL_RCC_DPHY_DIV_16
  */
__STATIC_INLINE void LL_RCC_SetDPHYPrescaler(uint32_t prescaler)
{
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PPRE_DPHY, prescaler);
}

/**
  * @brief  Get DPHY clock prescaler
  * @rmtoll
  *  CFGR2         PPRE_DPHY         LL_RCC_GetDPHYPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DPHY_DIV_1
  *         @arg @ref LL_RCC_DPHY_DIV_2
  *         @arg @ref LL_RCC_DPHY_DIV_4
  *         @arg @ref LL_RCC_DPHY_DIV_8
  *         @arg @ref LL_RCC_DPHY_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetDPHYPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PPRE_DPHY));
}
#endif /* RCC_CFGR2_PPRE_DPHY */

/**
  * @brief  Set Clock After Wake-Up From Stop mode
  * @rmtoll
  *  CFGR1       STOPWUCK      LL_RCC_SetClkAfterWakeFromStop
  * @param  clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_MSIS
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  */
__STATIC_INLINE void LL_RCC_SetClkAfterWakeFromStop(uint32_t clock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_STOPWUCK, clock);
}

/**
  * @brief  Get Clock After Wake-Up From Stop mode
  * @rmtoll
  *  CFGR1         STOPWUCK      LL_RCC_GetClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_MSIS
  *         @arg @ref LL_RCC_STOP_WAKEUPCLOCK_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetClkAfterWakeFromStop(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_STOPWUCK));
}

/**
  * @brief  Set Kernel Clock After Wake-Up From Stop mode
  * @rmtoll
  *  CFGR1       STOPKERWUCK LL_RCC_SetKerClkAfterWakeFromStop
  * @param  clock This parameter can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_MSIK
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_HSI
  */
__STATIC_INLINE void LL_RCC_SetKerClkAfterWakeFromStop(uint32_t clock)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_STOPKERWUCK, clock);
}

/**
  * @brief  Get Kernel Clock After Wake-Up From Stop mode
  * @rmtoll
  *  CFGR1         STOPKERWUCK LL_RCC_GetKerClkAfterWakeFromStop
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_MSIK
  *         @arg @ref LL_RCC_STOP_WAKEUPKERCLOCK_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetKerClkAfterWakeFromStop(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR1, RCC_CFGR1_STOPKERWUCK));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll
  *  CFGR1         MCOSEL        LL_RCC_ConfigMCO \n
  *  CFGR1         MCOPRE        LL_RCC_ConfigMCO
  * @param  mcox_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1SOURCE_NOCLOCK
  *         @arg @ref LL_RCC_MCO1SOURCE_SYSCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_MSIS
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI
  *         @arg @ref LL_RCC_MCO1SOURCE_HSE
  *         @arg @ref LL_RCC_MCO1SOURCE_HSI48
  *         @arg @ref LL_RCC_MCO1SOURCE_PLLCLK
  *         @arg @ref LL_RCC_MCO1SOURCE_LSI
  *         @arg @ref LL_RCC_MCO1SOURCE_LSE
  * @param  mcox_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MCO1_PRESCALER_1
  *         @arg @ref LL_RCC_MCO1_PRESCALER_2
  *         @arg @ref LL_RCC_MCO1_PRESCALER_4
  *         @arg @ref LL_RCC_MCO1_PRESCALER_8
  *         @arg @ref LL_RCC_MCO1_PRESCALER_16
  */
__STATIC_INLINE void LL_RCC_ConfigMCO(uint32_t mcox_source, uint32_t mcox_prescaler)
{
  MODIFY_REG(RCC->CFGR1, RCC_CFGR1_MCOSEL | RCC_CFGR1_MCOPRE, mcox_source | mcox_prescaler);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure USARTx clock source
  * @rmtoll
  *  CCIPR1       USART1SEL     LL_RCC_SetUSARTClockSource \n
  *  CCIPR1       USART2SEL     LL_RCC_SetUSARTClockSource \n
  *  CCIPR1       USART3SEL     LL_RCC_SetUSARTClockSource \n
  *  CCIPR2       USART6SEL     LL_RCC_SetUSARTClockSource
  * @param  usartx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  * @if USART2
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @endif
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE
  * @if RCC_CCIPR2_USART6SEL
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_SYSCLK (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_LSE (*)
  * @endif
  *         (*) Availability depends on devices.
  */
__STATIC_INLINE void LL_RCC_SetUSARTClockSource(uint32_t usartx_source)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (usartx_source >> 24U));
  MODIFY_REG(*reg, 3UL << ((usartx_source & 0x001F0000U) >> 16U), ((usartx_source & 0x000000FFU) <<
                                                                   ((usartx_source & 0x001F0000U) >> 16U)));
}

/**
  * @brief  Configure UARTx clock source
  * @rmtoll
  *  CCIPR1       UART4SEL      LL_RCC_SetUARTClockSource \n
  *  CCIPR1       UART5SEL      LL_RCC_SetUARTClockSource
  * @param  uartx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  */
__STATIC_INLINE void LL_RCC_SetUARTClockSource(uint32_t uartx_source)
{
  MODIFY_REG(RCC->CCIPR1, uartx_source >> 16U, (uartx_source & 0x0000FFFFU));
}

/**
  * @brief  Configure LPUARTx clock source
  * @rmtoll
  *  CCIPR3       LPUART1SEL    LL_RCC_SetLPUARTClockSource
  * @param  lpuartx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_MSIK
  */
__STATIC_INLINE void LL_RCC_SetLPUARTClockSource(uint32_t lpuartx_source)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_LPUART1SEL, lpuartx_source);
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll
  *  CCIPR1       I2C1SEL       LL_RCC_SetI2CClockSource \n
  *  CCIPR1       I2C2SEL       LL_RCC_SetI2CClockSource \n
  *  CCIPR3       I2C3SEL       LL_RCC_SetI2CClockSource \n
  *  CCIPR1       I2C4SEL       LL_RCC_SetI2CClockSource
  * @param  i2cx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_MSIK
  */
__STATIC_INLINE void LL_RCC_SetI2CClockSource(uint32_t i2cx_source)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (i2cx_source >> 24U));
  MODIFY_REG(*reg, 3U << (((i2cx_source & 0x00FF0000U) >> 16U) & 0x1FU),
             ((i2cx_source & 0x000000FFU) << (((i2cx_source & 0x00FF0000U) >> 16U) & 0x1FU)));
}

/**
  * @brief  Configure SPIx clock source
  * @rmtoll
  *  CCIPR1    SPI1SEL       LL_RCC_SetSPIClockSource \n
  *  CCIPR1    SPI1SEL       LL_RCC_SetSPIClockSource \n
  *  CCIPR1    SPI2SEL       LL_RCC_SetSPIClockSource \n
  *  CCIPR3    SPI3SEL       LL_RCC_SetSPIClockSource
  * @param  spix_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_MSIK
  */
__STATIC_INLINE void LL_RCC_SetSPIClockSource(uint32_t spix_source)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (spix_source >> 24U));
  MODIFY_REG(*reg, 3U << (((spix_source & 0x00FF0000U) >> 16U) & 0x1FU),
             ((spix_source & 0x000000FFU) << (((spix_source & 0x00FF0000U) >> 16U) & 0x1FU)));
}

/**
  * @brief  Configure LPTIMx clock source
  * @rmtoll
  *  CCIPR1       LPTIM2SEL     LL_RCC_SetLPTIMClockSource \n
  *  CCIPR3       LPTIM2SEL     LL_RCC_SetLPTIMClockSource \n
  *  CCIPR3       LPTIM34SEL    LL_RCC_SetLPTIMClockSource
  * @param  lptimx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSE
  */
__STATIC_INLINE void LL_RCC_SetLPTIMClockSource(uint32_t lptimx_source)
{
  __IO uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (lptimx_source >> 24U));
  MODIFY_REG(*reg, 3U << (((lptimx_source & 0x00FF0000U) >> 16U) & 0x1FU),
             ((lptimx_source & 0x000000FFU) << (((lptimx_source & 0x00FF0000U) >> 16U) & 0x1FU)));
}

/**
  * @brief  Configure FDCAN kernel clock source
  * @rmtoll
  *  CCIPR1       FDCANSEL      LL_RCC_SetFDCANClockSource
  * @param  fdcanx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2
  */
__STATIC_INLINE void LL_RCC_SetFDCANClockSource(uint32_t fdcanx_source)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_FDCANSEL, fdcanx_source);
}

/**
  * @brief  Configure SAIx clock source
  * @rmtoll
  *  CCIPR2       SAI1SEL       LL_RCC_SetSAIClockSource \n
  *  CCIPR2       SAI2SEL       LL_RCC_SetSAIClockSource
  * @param  saix_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL3
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_HSI
  * @if SAI2
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL1 (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL2 (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL3 (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PIN (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_HSI (*)
  * @endif
  *
  *         (*) Availability depends on devices.
  *
  */
__STATIC_INLINE void LL_RCC_SetSAIClockSource(uint32_t saix_source)
{
  MODIFY_REG(RCC->CCIPR2, (saix_source >> 16U), (saix_source & 0x0000FFFFU));
}

/**
  * @brief  Configure SDMMC1/2 kernel clock source
  * @rmtoll
  *  CCIPR2       SDMMCSEL      LL_RCC_SetSDMMCKernelClockSource
  * @param  sdmmcx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC12_KERCLKSOURCE_48CLK
  *         @arg @ref LL_RCC_SDMMC12_KERCLKSOURCE_PLL1 "P"
  */
__STATIC_INLINE void LL_RCC_SetSDMMCKernelClockSource(uint32_t sdmmcx_source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SDMMCSEL, sdmmcx_source);
}

/**
  * @brief  Configure SDMMC1/2 clock source
  * @rmtoll
  *  CCIPR1       ICLKSEL      LL_RCC_SetSDMMCClockSource
  * @param  sdmmcx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_MSIK
  */
__STATIC_INLINE void LL_RCC_SetSDMMCClockSource(uint32_t sdmmcx_source)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ICLKSEL, sdmmcx_source);
}

/**
  * @brief  Configure RNG clock source
  * @rmtoll
  *  CCIPR2       RNGSEL      LL_RCC_SetRNGClockSource
  * @param  rngx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48_DIV2
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI
  */
__STATIC_INLINE void LL_RCC_SetRNGClockSource(uint32_t rngx_source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_RNGSEL, rngx_source);
}

#if defined(RCC_CCIPR2_OTGHSSEL)
/**
  * @brief  Configure USB HS PHY clock source (OTG_HS)
  * @rmtoll
  *  CCIPR2         OTGHSSEL        LL_RCC_SetUSBHSPHYClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_HSE
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_HSE_DIV2
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_PLL1
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_PLL1_DIV2
  */
__STATIC_INLINE void LL_RCC_SetUSBHSPHYClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_OTGHSSEL, source);
}
#endif /* RCC_CCIPR2_OTGHSSEL */

/**
  * @brief  Configure USB clock source (OTG_FS or USB)
  * @rmtoll
  *  CCIPR1       ICLKSEL      LL_RCC_SetUSBClockSource
  * @param  usbx_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_USB_CLKSOURCE_MSIK
  */
__STATIC_INLINE void LL_RCC_SetUSBClockSource(uint32_t usbx_source)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_ICLKSEL, usbx_source);
}

/**
  * @brief  Configure ADC clock source
  * @rmtoll
  *  CCIPR3       ADCDACSEL        LL_RCC_SetADCDACClockSource
  * @param  adcx_dac1_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_MSIK
  */
__STATIC_INLINE void LL_RCC_SetADCDACClockSource(uint32_t adcx_dac1_source)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ADCDACSEL, adcx_dac1_source);
}

/**
  * @brief  Configure DAC1 clock source
  * @rmtoll
  *  CCIPR3        DAC1SEL        LL_RCC_SetDAC1ClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_LSI
  */
__STATIC_INLINE void LL_RCC_SetDAC1ClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_DAC1SEL, source);
}

/**
  * @brief  Configure ADF1 clock source
  * @rmtoll
  *  CCIPR3        ADF1SEL        LL_RCC_SetADF1ClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL3
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PIN
  */
__STATIC_INLINE void LL_RCC_SetADF1ClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR3, RCC_CCIPR3_ADF1SEL, source);
}

/**
  * @brief  Configure MDF1 clock source
  * @rmtoll
  *  CCIPR3        MDF1SEL        LL_RCC_SetMDF1ClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_PLL3
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_PIN
  */
__STATIC_INLINE void LL_RCC_SetMDF1ClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_MDF1SEL, source);
}

/**
  * @brief  Configure OCTOSPI kernel clock source
  * @rmtoll
  *  CCIPR2         OSPISEL        LL_RCC_SetOCTOSPIClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_PLL2
  */
__STATIC_INLINE void LL_RCC_SetOCTOSPIClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_OCTOSPISEL, source);
}

#if defined (HSPI1)
/**
  * @brief  Configure HSPI kernel clock source
  * @rmtoll
  *  CCIPR2         HSPISEL        LL_RCC_SetHSPIClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_PLL3
  */
__STATIC_INLINE void LL_RCC_SetHSPIClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_HSPISEL, source);
}
#endif /* HSPI1 */

#if defined(SAES)
/**
  * @brief  Configure SAES clock source
  * @rmtoll
  *  CCIPR2        SAESSEL        LL_RCC_SetSAESClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAES_CLKSOURCE_SHSI
  *         @arg @ref LL_RCC_SAES_CLKSOURCE_SHSI_DIV2
  */
__STATIC_INLINE void LL_RCC_SetSAESClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_SAESSEL, source);
}
#endif /* SAES */

#if defined(DSI)
/**
  * @brief  Configure DSIx clock source
  * @rmtoll
  *  CCIPR2         DSISEL        LL_RCC_SetDSIClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DSI_CLKSOURCE_PHY
  *         @arg @ref LL_RCC_DSI_CLKSOURCE_PLL3
  */
__STATIC_INLINE void LL_RCC_SetDSIClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_DSIHOSTSEL, source);
}
#endif /* DSI */

#if defined(LTDC)
/**
  * @brief  Configure LTDCx clock source
  * @rmtoll
  *  CCIPR2         LTDCSEL        LL_RCC_SetLTDCClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LTDC_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_LTDC_CLKSOURCE_PLL3
  */
__STATIC_INLINE void LL_RCC_SetLTDCClockSource(uint32_t source)
{
  MODIFY_REG(RCC->CCIPR2, RCC_CCIPR2_LTDCSEL, source);
}
#endif /* LTDC */
/**
  * @brief  Get USARTx clock source
  * @rmtoll
  *  CCIPR1       USART1SEL     LL_RCC_GetUSARTClockSource \n
  *  CCIPR1       USART2SEL     LL_RCC_GetUSARTClockSource \n
  *  CCIPR1       USART3SEL     LL_RCC_GetUSARTClockSource \n
  *  CCIPR2       USART6SEL     LL_RCC_GetUSARTClockSource
  * @param  usartx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  * @if USART2
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  * @endif
  *         @arg @ref LL_RCC_USART3_CLKSOURCE
  * @if RCC_CCIPR2_USART6SEL
  *         @arg @ref LL_RCC_USART6_CLKSOURCE (*)
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART1_CLKSOURCE_LSE
  * @if USART2
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART2_CLKSOURCE_LSE
  * @endif
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_USART3_CLKSOURCE_LSE
  * @if RCC_CCIPR2_USART6SEL
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_PCLK1 (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_SYSCLK (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_HSI (*)
  *         @arg @ref LL_RCC_USART6_CLKSOURCE_LSE (*)
  * @endif
  *         (*) Availability depends on devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSARTClockSource(uint32_t usartx)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (usartx >> 24U));
  return (uint32_t)((READ_BIT(*reg, 3UL << ((usartx & 0x001F0000U) >> 16U)) >>
                     ((usartx & 0x001F0000U) >> 16U)) | (usartx & 0xFFFF0000U));
}

/**
  * @brief  Get UARTx clock source
  * @rmtoll
  *  CCIPR1       UART4SEL      LL_RCC_GetUARTClockSource \n
  *  CCIPR1       UART5SEL      LL_RCC_GetUARTClockSource
  * @param  uartx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART4_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_UART5_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetUARTClockSource(uint32_t uartx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, uartx) | (uartx << 16U));
}

/**
  * @brief  Get LPUARTx clock source
  * @rmtoll
  *  CCIPR1       LPUART1SEL    LL_RCC_GetLPUARTClockSource
  * @param  lpuartx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPUARTClockSource(uint32_t lpuartx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, lpuartx));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll
  *  CCIPR1       I2C1SEL       LL_RCC_GetI2CClockSource \n
  *  CCIPR1       I2C2SEL       LL_RCC_GetI2CClockSource \n
  *  CCIPR3       I2C3SEL       LL_RCC_GetI2CClockSource \n
  *  CCIPR1       I2C4SEL       LL_RCC_GetI2CClockSource
  * @param  i2cx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE_HSI
 */
__STATIC_INLINE uint32_t LL_RCC_GetI2CClockSource(uint32_t i2cx)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (i2cx >> 24U));
  return (uint32_t)((READ_BIT(*reg, (3UL << (((i2cx & 0x00FF0000UL) >> 16U) & 0x1FUL))) >>
                     (((i2cx & 0x00FF0000UL) >> 16U) & 0x1FUL)) | (i2cx & 0xFFFF0000UL));
}

/**
  * @brief  Get SPIx clock source
  * @rmtoll
  *  CCIPR1       SPI1SEL       LL_RCC_GetSPIClockSource \n
  *  CCIPR1       SPI2SEL       LL_RCC_GetSPIClockSource \n
  *  CCIPR3       SPI3SEL       LL_RCC_GetSPIClockSource
  * @param  spix This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_PCLK2
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_PCLK3
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE_MSIK
 */
__STATIC_INLINE uint32_t LL_RCC_GetSPIClockSource(uint32_t spix)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (spix >> 24U));
  return (uint32_t)((READ_BIT(*reg, (3UL << (((spix & 0x00FF0000UL) >> 16U) & 0x1FUL))) >>
                     (((spix & 0x00FF0000UL) >> 16U) & 0x1FUL)) | (spix & 0xFFFF0000UL));
}

/**
  * @brief  Get LPTIMx clock source
  * @rmtoll
  *  CCIPR1       LPTIM2SEL     LL_RCC_GetLPTIMClockSource \n
  *  CCIPR3       LPTIM2SEL     LL_RCC_GetLPTIMClockSource \n
  *  CCIPR3       LPTIM34SEL    LL_RCC_GetLPTIMClockSource
  * @param  lptimx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_PCLK1
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_HSI
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE_LSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetLPTIMClockSource(uint32_t lptimx)
{
  __IO const uint32_t *reg = (__IO uint32_t *)(uint32_t)(RCC_BASE + 0xE0U + (lptimx >> 24U));
  return (uint32_t)((READ_BIT(*reg, (3UL << (((lptimx & 0x00FF0000UL) >> 16U) & 0x1FUL))) >>
                     (((lptimx & 0x00FF0000UL) >> 16U) & 0x1FUL)) | (lptimx & 0xFFFF0000UL));
}

/**
  * @brief  Set Tim Input capture clock source
  * @rmtoll
  *  CCIPR1       TIMICSEL      LL_RCC_SetTIMICClockSource
  * @param  timic_source This parameter can be one of the following combined values:
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_NONE
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV1024
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV4
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV4
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV1024
  * @note    HSI, MSI and MSIK clocks without division are also available when TIMICSEL[2] is 1.
  * @note    combination to be avoided :
  *                       LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV1024 and LL_RCC_CLKSOURCE_TIMIC_MSIK_DIV1024
  *                       LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV4 and LL_RCC_CLKSOURCE_TIMIC_MSIK_DIV4.
  */
__STATIC_INLINE void LL_RCC_SetTIMICClockSource(uint32_t timic_source)
{
  MODIFY_REG(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL, timic_source);
}

/**
  * @brief  Get Tim Input capture clock source
  * @rmtoll
  *  CCIPR1       TIMICSEL      LL_RCC_GetTIMICClockSource
  * @retval Returned value can be one of the following combined values:
  *          @arg @ref   LL_RCC_TIMIC_CLKSOURCE_NONE
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_HSI_DIV256
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV1024
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIS_DIV4
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV4
  *          @arg @ref    LL_RCC_TIMIC_CLKSOURCE_MSIK_DIV1024
  */
__STATIC_INLINE uint32_t LL_RCC_GetTIMICClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, RCC_CCIPR1_TIMICSEL));
}

/**
  * @brief  Get FDCAN kernel clock source
  * @rmtoll
  *  CCIPR1         FDCANSEL        LL_RCC_GetFDCANClockSource
  * @param  fdcanx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_HSE
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE_PLL2
  */
__STATIC_INLINE uint32_t LL_RCC_GetFDCANClockSource(uint32_t fdcanx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, fdcanx));
}

/**
  * @brief  Get SAIx clock source
  * @rmtoll
  *  CCIPR2       SAI1SEL       LL_RCC_GetSAIClockSource\n
  *         CCIPR2       SAI2SEL       LL_RCC_GetSAIClockSource
  * @param  saix This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  * @if SAI2
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE (*)
  * @endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PLL3
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_PIN
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE_HSI
  * @if SAI2
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL1 (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL2 (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PLL3 (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_PIN (*)
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE_HSI (*)
  * @endif
  *
  *         (*) Availability depends on devices.
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAIClockSource(uint32_t saix)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, saix) | (saix << 16U));
}

/**
  * @brief  Get SDMMCx kernel clock source
  * @rmtoll
  *  CCIPR2       SDMMCSEL      LL_RCC_GetSDMMCKernelClockSource
  * @param  sdmmcx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC_KERNELCLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC12_KERCLKSOURCE_48CLK
  *         @arg @ref LL_RCC_SDMMC12_KERCLKSOURCE_PLL1 "P"
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMCKernelClockSource(uint32_t sdmmcx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, sdmmcx));
}

/**
  * @brief  Get SDMMC1/2 clock source
  * @rmtoll
  *  CCIPR1       ICLKSEL      LL_RCC_GetSDMMCClockSource
  * @param  sdmmcx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_SDMMC12_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetSDMMCClockSource(uint32_t sdmmcx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, sdmmcx));
}

/**
  * @brief  Get RNGx clock source
  * @rmtoll
  *  CCIPR2       RNGSEL      LL_RCC_GetRNGClockSource
  * @param  rngx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI48_DIV2
  *         @arg @ref LL_RCC_RNG_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetRNGClockSource(uint32_t rngx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, rngx));
}

#if defined(RCC_CCIPR2_OTGHSSEL)
/**
  * @brief  Get USB HS PHY clock source
  * @rmtoll
  *  CCIPR2         OTGHSSEL        LL_RCC_GetUSBHSPHYClockSource
  * @param  usbphyx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBHSPHY_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_HSE
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_HSE_DIV2
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_PLL1
  *         @arg @ref LL_RCC_USBHSPHYCLKSOURCE_PLL1_DIV2
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBHSPHYClockSource(uint32_t usbphyx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, usbphyx));
}
#endif /* RCC_CCIPR2_OTGHSSEL */

/**
  * @brief  Get USBx clock source
  * @rmtoll
  *  CCIPR1       ICLKSEL      LL_RCC_GetUSBClockSource
  * @param  usbx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE_HSI48
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_USB_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_USB_CLKSOURCE_MSIK
  */
__STATIC_INLINE uint32_t LL_RCC_GetUSBClockSource(uint32_t usbx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR1, usbx));
}

/**
  * @brief  Get ADCx clock source
  * @rmtoll
  *  CCIPR3       ADCDACSEL        LL_RCC_SetADCDACClockSource
  * @param  adcxdac1 This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_GetADCDACClockSource(uint32_t adcxdac1)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, adcxdac1));
}

/**
  * @brief  Get DFSDM Audio Clock Source
  * @rmtoll
  *  CCIPR3         ADF1SEL        LL_RCC_GetADF1ClockSource
  * @param  adfx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PLL3
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE_PIN
  */
__STATIC_INLINE uint32_t LL_RCC_GetADF1ClockSource(uint32_t adfx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, adfx));
}

/**
  * @brief  Get DAC1 Clock Source
  * @rmtoll
  *  CCIPR3        DAC1SEL        LL_RCC_GetDAC1ClockSource
  * @param  dacx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE_LSI
  */
__STATIC_INLINE uint32_t LL_RCC_GetDAC1ClockSource(uint32_t dacx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR3, dacx));
}

/**
  * @brief  Get MDF1 Clock Source
  * @rmtoll
  *  CCIPR2         MDF1SEL        LL_RCC_GetMDF1ClockSource
  * @param  mdfx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_HCLK
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_PLL3
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE_PIN
  */
__STATIC_INLINE uint32_t LL_RCC_GetMDF1ClockSource(uint32_t mdfx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, mdfx));
}

/**
  * @brief  Get OCTOSPI clock source
  * @rmtoll
  *  CCIPR2         OSPISEL        LL_RCC_GetOCTOSPIClockSource
  * @param  octospix This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_MSIK
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE_PLL2
  */
__STATIC_INLINE uint32_t LL_RCC_GetOCTOSPIClockSource(uint32_t octospix)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, octospix));
}

#if defined (HSPI1)
/**
  * @brief  Get HSPI clock source
  * @rmtoll
  *  CCIPR2         HSPISEL        LL_RCC_GetHSPIClockSource
  * @param  hspix This parameter can be one of the following values:
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_SYSCLK
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_PLL1
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_HSPI_CLKSOURCE_PLL3
  */
__STATIC_INLINE uint32_t LL_RCC_GetHSPIClockSource(uint32_t hspix)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, hspix));
}
#endif /* HSPI1 */
/**
  * @}
  */

#if defined(SAES)
/**
  * @brief  Get SAES kernel clock source
  * @rmtoll
  *  CCIPR2       SAESSEL      LL_RCC_GetSAESClockSource
  * @param  saesx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAES_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_SAES_CLKSOURCE_SHSI
  *         @arg @ref LL_RCC_SAES_CLKSOURCE_SHSI_DIV2
  */
__STATIC_INLINE uint32_t LL_RCC_GetSAESClockSource(uint32_t saesx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, saesx));
}
#endif /* SAES */

#if defined(DSI)
/**
  * @brief  Get DSI clock source
  * @rmtoll
  *  CCIPR2         DSISEL        LL_RCC_GetDSIClockSource
  * @param  dsix This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DSI_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_DSI_CLKSOURCE_PHY
  *         @arg @ref LL_RCC_DSI_CLKSOURCE_PLL3
  */
__STATIC_INLINE uint32_t LL_RCC_GetDSIClockSource(uint32_t dsix)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, dsix));
}
#endif /* DSI */

#if defined(LTDC)
/**
  * @brief  Get LTDC clock source
  * @rmtoll
  *  CCIPR2         LTDCSEL        LL_RCC_GetLTDCClockSource
  * @param  ltdcx This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LTDC_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_LTDC_CLKSOURCE_PLL2
  *         @arg @ref LL_RCC_LTDC_CLKSOURCE_PLL3
  */
__STATIC_INLINE uint32_t LL_RCC_GetLTDCClockSource(uint32_t ltdcx)
{
  return (uint32_t)(READ_BIT(RCC->CCIPR2, ltdcx));
}
#endif /* LTDC */

/** @defgroup RCC_LL_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @rmtoll
  *  BDCR         RTCSEL        LL_RCC_SetRTCClockSource
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  * @note Once the RTC clock source has been selected, it cannot be changed anymore unless
  *       the Backup domain is reset, or unless a failure is detected on LSE (LSECSSD is
  *       set). The BDRST bit can be used to reset them.
  */
__STATIC_INLINE void LL_RCC_SetRTCClockSource(uint32_t source)
{
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll
  *  BDCR         RTCSEL        LL_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref LL_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t LL_RCC_GetRTCClockSource(void)
{
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL));
}

/**
  * @brief  Enable RTC
  * @rmtoll
  *  BDCR         RTCEN         LL_RCC_EnableRTC
  */
__STATIC_INLINE void LL_RCC_EnableRTC(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll
  *  BDCR         RTCEN         LL_RCC_DisableRTC
  */
__STATIC_INLINE void LL_RCC_DisableRTC(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll
  *  BDCR         RTCEN         LL_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledRTC(void)
{
  return ((READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == RCC_BDCR_RTCEN) ? 1UL : 0UL);
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll
  *  BDCR         BDRST         LL_RCC_ForceBackupDomainReset
  */
__STATIC_INLINE void LL_RCC_ForceBackupDomainReset(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll
  *  BDCR         BDRST         LL_RCC_ReleaseBackupDomainReset
  */
__STATIC_INLINE void LL_RCC_ReleaseBackupDomainReset(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @}
  */


/** @defgroup RCC_LL_EF_PLL1 PLL1
  * @{
  */

/**
  * @brief  Enable PLL1
  * @rmtoll
  *  CR           PLL1ON         LL_RCC_PLL1_Enable
  */
__STATIC_INLINE void LL_RCC_PLL1_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Disable PLL1
  * @rmtoll
  *  CR           PLLON         LL_RCC_PLL1_Disable
  * @note Cannot be disabled if the PLL1 clock is used as the system clock.
  */
__STATIC_INLINE void LL_RCC_PLL1_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON);
}

/**
  * @brief  Check if PLL1 Ready
  * @rmtoll
  *  CR           PLL1RDY        LL_RCC_PLL1_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL1RDY) == RCC_CR_PLL1RDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL1 used for SYSCLK Domain
  * @rmtoll
  *  PLL1CFGR      PLL1SRC        LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1CFGR      PLL1M          LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1CFGR      PLL1N          LL_RCC_PLL1_ConfigDomain_SYS \n
  *  PLL1CFGR      PLL1R          LL_RCC_PLL1_ConfigDomain_SYS
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param pllr parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @param plln parameter can be a value between 4 and 512
  * @note PLL1 Source, PLLM, PLLN and PLLR can be written only when PLL1 is disabled.
  * @note PLLN/PLLR can be written only when PLL is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_SYS(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllr)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M, source |
             ((pllm - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1R,
             ((plln - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((pllr - 1UL) << RCC_PLL1DIVR_PLL1R_Pos));
}

/**
  * @brief  Configure PLL1 used for SAI domain clock
  * @rmtoll
  *  PLLC1FGR      PLL1SRC        LL_RCC_PLL1_ConfigDomain_SAI \n
  *  PLLC1FGR      PLL1M          LL_RCC_PLL1_ConfigDomain_SAI \n
  *  PLLC1FGR      PLL1N          LL_RCC_PLL1_ConfigDomain_SAI \n
  *  PLLC1FGR      PLL1P          LL_RCC_PLL1_ConfigDomain_SAI
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllp parameter can be a value between 1 and 128
  * @note PLL1 Source, PLLM, PLLN and PLLPDIV can be written only when PLL1 is disabled.
  * @note This can be selected for SAI1 or SAI2.
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_SAI(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M, source |
             ((pllm - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1P,
             ((plln - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((pllp - 1UL) << RCC_PLL1DIVR_PLL1P_Pos));
}

/**
  * @brief  Configure PLL1 used for 48MHz domain clock
  * @rmtoll
  *  PLL1CFGR      PLL1SRC        LL_RCC_PLL1_ConfigDomain_48M \n
  *  PLL1CFGR      PLL1M          LL_RCC_PLL1_ConfigDomain_48M \n
  *  PLL1CFGR      PLL1N          LL_RCC_PLL1_ConfigDomain_48M \n
  *  PLL1CFGR      PLL1Q          LL_RCC_PLL1_ConfigDomain_48M
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllq parameter can be a value between 1 and 128
  * @note PLL1 Source, PLLM, PLLN and PLLQ can be written only when PLL1 is disabled.
  * @note This  can be selected for USB, SDMMC.
  */
__STATIC_INLINE void LL_RCC_PLL1_ConfigDomain_48M(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllq)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M, source |
             ((pllm - 1UL) << RCC_PLL1CFGR_PLL1M_Pos));
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1Q,
             ((plln - 1UL) << RCC_PLL1DIVR_PLL1N_Pos) | ((pllq - 1UL) << RCC_PLL1DIVR_PLL1Q_Pos));
}

/**
  * @brief  Configure PLL1 used for 48MHz domain clock
  * @rmtoll
  *  PLL1CFGR      PLL1SRC        LL_RCC_PLL1_Config \n
  *  PLL1CFGR      PLL1MBOOST     LL_RCC_PLL1_Config \n
  *  PLL1CFGR      PLL1M          LL_RCC_PLL1_Config \n
  *  PLL1CFGR      PLL1N          LL_RCC_PLL1_Config \n
  *  PLL1CFGR      PLL1P          LL_RCC_PLL1_Config \n
  *  PLL1CFGR      PLL1Q          LL_RCC_PLL1_Config \n
  *  PLL1CFGR      PLL1R          LL_RCC_PLL1_Config
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  * @param  boost_div This parameter can be one of the following values:
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_1
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_2
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_4
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_6
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_8
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_10
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_12
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_14
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_16
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllp parameter can be a value between 1 and 128
  * @param pllq parameter can be a value between 1 and 128
  * @param pllr parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note PLL1 Source, PLLM, PLLN and PLLQ can be written only when PLL1 is disabled.
  * @note This  can be selected for USB, SDMMC.
  */
__STATIC_INLINE void LL_RCC_PLL1_Config(uint32_t source, uint32_t boost_div, uint32_t pllm, uint32_t plln,
                                        uint32_t pllp, uint32_t pllq, uint32_t pllr)
{
  MODIFY_REG(RCC->PLL1CFGR, (RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1M | RCC_PLL1CFGR_PLL1MBOOST),
             (source << RCC_PLL1CFGR_PLL1SRC_Pos)
             | ((pllm - 1U) << RCC_PLL1CFGR_PLL1M_Pos)
             | boost_div);
  MODIFY_REG(RCC->PLL1DIVR, (RCC_PLL1DIVR_PLL1N | RCC_PLL1DIVR_PLL1P | RCC_PLL1DIVR_PLL1Q | RCC_PLL1DIVR_PLL1R),
             (((plln - 1U) & RCC_PLL1DIVR_PLL1N)
              | (((pllp - 1U) << RCC_PLL1DIVR_PLL1P_Pos) & RCC_PLL1DIVR_PLL1P)
              | (((pllq - 1U) << RCC_PLL1DIVR_PLL1Q_Pos) & RCC_PLL1DIVR_PLL1Q)
              | (((pllr - 1U) << RCC_PLL1DIVR_PLL1R_Pos) & RCC_PLL1DIVR_PLL1R)));
}

/**
  * @brief  Configure PLL clock source
  * @rmtoll
  *  PLL1CFGR      PLL1SRC        LL_RCC_PLL1_SetMainSource
  * @param  pll1_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_PLL1_SetMainSource(uint32_t pll1_source)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC, pll1_source);
}

/**
  * @brief  Get the oscillator used as PLL1 clock source.
  * @rmtoll
  *  PLL1CFGR      PLL1SRC        LL_RCC_PLL1_GetMainSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL1SOURCE_NONE
  *         @arg @ref LL_RCC_PLL1SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL1SOURCE_HSI
  *         @arg @ref LL_RCC_PLL1SOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetMainSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1SRC));
}

/**
  * @brief  Set Main PLL1 multiplication factor for VCO
  * @rmtoll
  *  PLL1CFGR      PLL1N          LL_RCC_PLL1_SetN
  * @param pll1n parameter can be a value between 4 and 512
  */
__STATIC_INLINE void LL_RCC_PLL1_SetN(uint32_t pll1n)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N, (pll1n - 1UL) << RCC_PLL1DIVR_PLL1N_Pos);
}

/**
  * @brief  Get Main PLL1 multiplication factor for VCO
  * @rmtoll
  *  PLL1CFGR      PLL1N          LL_RCC_PLL1_GetN
  * @retval Between 4 and 512
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1N) >>  RCC_PLL1DIVR_PLL1N_Pos) + 1UL);
}

/**
  * @brief  Set Main PLL1 division factor for PLL1P
  * @rmtoll
  *  PLL1CFGR      PLL1P       LL_RCC_PLL1_SetP
  * @param pll1p parameter can be a value between 1 and 128
  * @note Used for SAI1 and SAI2 clock.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetP(uint32_t pll1p)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1P, (pll1p - 1UL) << RCC_PLL1DIVR_PLL1P_Pos);
}

/**
  * @brief  Get Main PLL1 division factor for PLL1P
  * @rmtoll
  *  PLL1CFGR      PLL1P      LL_RCC_PLL1_GetP
  * @note Used for SAI1 and SAI2 clock.
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1P) >>  RCC_PLL1DIVR_PLL1P_Pos) + 1UL);
}

/**
  * @brief  Set Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL1DIVR      PLL1Q          LL_RCC_PLL1_SetQ
  * @param pll1q parameter can be a value between 1 and 128
  * @note Used for PLL48M1CLK selected for USB, SDMMC (48 MHz clock).
  */
__STATIC_INLINE void LL_RCC_PLL1_SetQ(uint32_t pll1q)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1Q, (pll1q - 1UL) << RCC_PLL1DIVR_PLL1Q_Pos);
}

/**
  * @brief  Get Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL1CFGR      PLL1Q          LL_RCC_PLL1_GetQ
  * @note Used for PLL48M1CLK selected for USB, SDMMC (48 MHz clock).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1Q) >>  RCC_PLL1DIVR_PLL1Q_Pos) + 1UL);
}

/**
  * @brief  Set Main PLL division factor for PLL1R
  * @rmtoll
  *  PLL1DIVR      PLL1R          LL_RCC_PLL1_SetR
  * @param pll1r parameter can be a value between 1 and 128 (Only division by 1 and even division are allowed)
  * @note Used for PLL1CLK selected for USB, SDMMC (48 MHz clock).
  */
__STATIC_INLINE void LL_RCC_PLL1_SetR(uint32_t pll1r)
{
  MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1R, (pll1r - 1UL) << RCC_PLL1DIVR_PLL1R_Pos);
}

/**
  * @brief  Get Main PLL1 division factor for PLL1R
  * @rmtoll
  *  PLL1DIVR      PLL1R          LL_RCC_PLL1_GetR
  * @note Used for PLL1CLK (system clock).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1DIVR, RCC_PLL1DIVR_PLL1R) >>  RCC_PLL1DIVR_PLL1R_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for the main PLL and other PLL
  * @rmtoll
  *  PLL1CFGR      PLL1M          LL_RCC_PLL1_SetDivider
  * @param pll1m parameter can be a value between 1 and 16
  */
__STATIC_INLINE void LL_RCC_PLL1_SetDivider(uint32_t pll1m)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1M, (pll1m - 1UL) << RCC_PLL1CFGR_PLL1M_Pos);
}

/**
  * @brief  Get Division factor for the main PLL and other PLL
  * @rmtoll
  *  PLL1CFGR      PLL1M          LL_RCC_PLL1_GetDivider
  * @retval Between 1 and 16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetDivider(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1M) >>  RCC_PLL1CFGR_PLL1M_Pos) + 1UL);
}

/**
  * @brief  Enable PLL1 output mapped on SAI domain clock
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_EnableDomain_SAI
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableDomain_SAI(void)
{
  SET_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P);
}

/**
  * @brief  Disable PLL1 output mapped on SAI domain clock
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_DisableDomain_SAI
  * @note Cannot be disabled if the PLL1 clock is used as the system
  *       clock.
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableDomain_SAI(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P);
}

/**
  * @brief  Check if PLL1 output mapped on SAI domain clock is enabled
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_IsEnabledDomain_SAI
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledDomain_SAI(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P) == (LL_RCC_PLL1_OUTPUT_P)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL output mapped on 48MHz domain clock
  * @rmtoll
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_EnableDomain_48M
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableDomain_48M(void)
{
  SET_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_Q);
}

/**
  * @brief  Disable PLL1 output mapped on 48MHz domain clock
  * @rmtoll
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_DisableDomain_48M
  * @note Cannot be disabled if the PLL clock is used as the system clock.
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableDomain_48M(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_Q);
}

/**
  * @brief  Check if PLL1 output mapped on 48M domain clock is enabled
  * @rmtoll
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_IsEnabledDomain_48M
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledDomain_48M(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_Q) == (LL_RCC_PLL1_OUTPUT_Q)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1 output mapped on SYSCLK domain
  * @rmtoll
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_EnableDomain_SYS
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableDomain_SYS(void)
{
  SET_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_R);
}

/**
  * @brief  Disable PLL1 output mapped on SYSCLK domain
  * @rmtoll
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_DisableDomain_SYS
  * @note Cannot be disabled if the PLL1 clock is used as the system clock.
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableDomain_SYS(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_R);
}

/**
  * @brief  Check if PLL1 output mapped on SYS domain clock is enabled
  * @rmtoll
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_IsEnabledDomain_SYS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsEnabledDomain_SYS(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_R) == (LL_RCC_PLL1_OUTPUT_R)) ? 1UL : 0UL);
}

/**
  * @brief  Enable 1 or several PLL1 outputs
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_EnableOutput \n
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_EnableOutput \n
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  */
__STATIC_INLINE void LL_RCC_PLL1_EnableOutput(uint32_t outputs)
{
  SET_BIT(RCC->PLL1CFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL1 outputs
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_DisableOutput \n
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_DisableOutput \n
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  * @note Cannot be disabled if the PLL1R output is used as the system clock.
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL1_DisableOutput(uint32_t outputs)
{
  CLEAR_BIT(RCC->PLL1CFGR, outputs);
}

/**
  * @brief Get the list of the outputs activated for PLL1
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_DisableOutput \n
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_DisableOutput \n
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_DisableOutput
  * @retval  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetOutput(void)
{
  return READ_BIT(RCC->PLL1CFGR, LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_R);
}


/**
  * @brief  Check if 1 or several PLL1 outputs are enabled
  * @rmtoll
  *  PLL1CFGR      PLL1PEN        LL_RCC_PLL1_IsOutputEnabled \n
  *  PLL1CFGR      PLL1QEN        LL_RCC_PLL1_IsOutputEnabled \n
  *  PLL1CFGR      PLL1REN        LL_RCC_PLL1_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL1_OUTPUT_P
  *         @arg @ref LL_RCC_PLL1_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL1_OUTPUT_R
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_IsOutputEnabled(uint32_t outputs)
{
  return ((READ_BIT(RCC->PLL1CFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL1 FRACN
  * @rmtoll
  *  PLL1CFGR           PLL1FRACEN         LL_RCC_PLL1FRACN_Enable
  */
__STATIC_INLINE void LL_RCC_PLL1FRACN_Enable(void)
{
  SET_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN);
}

/**
  * @brief  Check if PLL1 FRACN is enabled
  * @rmtoll
  *  PLL1CFGR           PLL1FRACEN         LL_RCC_PLL1FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN) == RCC_PLL1CFGR_PLL1FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL1 FRACN
  * @rmtoll
  *  PLL1CFGR           PLL1FRACEN         LL_RCC_PLL1FRACN_Disable
  */
__STATIC_INLINE void LL_RCC_PLL1FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1FRACEN);
}

/**
  * @brief  Set PLL1 FRACN Coefficient
  * @rmtoll
  *  PLL1FRACR        PLL1FRACN        LL_RCC_PLL1_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL1_SetFRACN(uint32_t fracn)
{
  MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_PLL1FRACN, fracn << RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @brief  Get PLL1 FRACN Coefficient
  * @rmtoll
  *  PLL1FRACR      PLL1FRACN          LL_RCC_PLL1_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL1_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1FRACR, RCC_PLL1FRACR_PLL1FRACN) >>  RCC_PLL1FRACR_PLL1FRACN_Pos);
}

/**
  * @brief  Set PLL1 VCO Input Range
  * @rmtoll
  *  PLL1CFGR        PLL1RGE       LL_RCC_PLL1_SetVCOInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @note   This API must be called only when PLL1 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL1_SetVCOInputRange(uint32_t input_range)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1RGE, input_range);
}

/**
  * @brief  Set PLL1 EPOD Prescaler booster input clock
  * @rmtoll
  *  PLL1CFGR       PLL1MBOOST      LL_RCC_SetPll1EPodPrescaler
  * @param  boost_div This parameter can be one of the following values:
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_1
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_2
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_4
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_6
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_8
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_10
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_12
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_14
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_16
  */
__STATIC_INLINE void LL_RCC_SetPll1EPodPrescaler(uint32_t boost_div)
{
  MODIFY_REG(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1MBOOST, boost_div);
}

/**
  * @brief  Get PLL1 EPOD Prescaler booster input clock
  * @rmtoll
  *  PLL1CFGR       PLL1MBOOST      LL_RCC_GetPll1EPodPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_1
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_2
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_4
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_6
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_8
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_10
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_12
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_14
  *         @arg @ref   LL_RCC_PLL1MBOOST_DIV_16
  */
__STATIC_INLINE uint32_t LL_RCC_GetPll1EPodPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL1CFGR, RCC_PLL1CFGR_PLL1MBOOST));
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL2 PLL2
  * @{
  */

/**
  * @brief  Enable PLL2
  * @rmtoll
  *  CR           PLL2ON     LL_RCC_PLL2_Enable
  */
__STATIC_INLINE void LL_RCC_PLL2_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL2ON);
}

/**
  * @brief  Disable PLL2
  * @rmtoll
  *  CR           PLL2ON     LL_RCC_PLL2_Disable
  */
__STATIC_INLINE void LL_RCC_PLL2_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);
}

/**
  * @brief  Check if PLL2 Ready
  * @rmtoll
  *  CR           PLL2RDY    LL_RCC_PLL2_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL2RDY) == RCC_CR_PLL2RDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL2 used for 48MHz domain clock
  * @rmtoll
  *  PLL2CFGR      PLL2SRC        LL_RCC_PLL2_ConfigDomain_48M \n
  *  PLL2CFGR      PLL2M          LL_RCC_PLL2_ConfigDomain_48M \n
  *  PLL2CFGR      PLL2N          LL_RCC_PLL2_ConfigDomain_48M \n
  *  PLL2CFGR      PLL2Q          LL_RCC_PLL2_ConfigDomain_48M
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllq parameter can be a value between 1 and 128
  * @note PLL2 Source, PLLM, PLLN and PLLQ can be written only when PLL2 is disabled.
  * @note This  can be selected for USB, SDMMC.
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigDomain_48M(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllq)
{
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2M, source |
             ((pllm - 1UL) << RCC_PLL2CFGR_PLL2M_Pos));
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N | RCC_PLL2DIVR_PLL2Q,
             ((plln - 1UL) << RCC_PLL2DIVR_PLL2N_Pos) | ((pllq - 1UL) << RCC_PLL2DIVR_PLL2Q_Pos));
}

/**
  * @brief  Configure PLL2 used for SAI domain clock
  * @rmtoll
  *  PLLC2FGR      PLL2SRC        LL_RCC_PLL2_ConfigDomain_SAI \n
  *  PLLC2FGR      PLL2M          LL_RCC_PLL2_ConfigDomain_SAI \n
  *  PLLC2FGR      PLL2N          LL_RCC_PLL2_ConfigDomain_SAI \n
  *  PLLC2FGR      PLL2P          LL_RCC_PLL2_ConfigDomain_SAI
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllp parameter can be a value between 1 and 128
  * @note PLL1 Source, PLLM, PLLN and PLL2P can be written only when PLL1 is disabled.
  * @note This can be selected for SAI1 or SAI2.
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigDomain_SAI(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp)
{
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2M, source |
             ((pllm - 1UL) << RCC_PLL2CFGR_PLL2M_Pos));
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N | RCC_PLL2DIVR_PLL2P,
             ((plln - 1UL) << RCC_PLL2DIVR_PLL2N_Pos) | ((pllp - 1UL) << RCC_PLL2DIVR_PLL2P_Pos));
}

/**
  * @brief  Configure PLL2 used for ADC domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2SRC    LL_RCC_PLL2_ConfigDomain_ADC \n
  *  PLL2CFGR  PLL2M      LL_RCC_PLL2_ConfigDomain_ADC \n
  *  PLL2CFGR  PLL2N      LL_RCC_PLL2_ConfigDomain_ADC \n
  *  PLL2CFGR  PLL2R      LL_RCC_PLL2_ConfigDomain_ADC
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param pllr parameter can be a value between 1 and 128
  * @param plln parameter can be a value between 4 and 512
  * @note PLL2SRC/PLL2M/PLL2N/PLL2R can be written only when PLL2 is disabled.
  * @note This  can be selected for ADC.
  */
__STATIC_INLINE void LL_RCC_PLL2_ConfigDomain_ADC(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllr)
{
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2M, source |
             ((pllm - 1UL) << RCC_PLL2CFGR_PLL2M_Pos));
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N | RCC_PLL2DIVR_PLL2R,
             ((plln - 1UL) << RCC_PLL2DIVR_PLL2N_Pos) | ((pllr - 1UL) << RCC_PLL2DIVR_PLL2R_Pos));
}

/**
  * @brief  Configure PLL2
  * @rmtoll
  *  PLL2CFGR      PLL2SRC        LL_RCC_PLL2_Config \n
  *  PLL2CFGR      PLL2M          LL_RCC_PLL2_Config \n
  *  PLL2CFGR      PLL2N          LL_RCC_PLL2_Config \n
  *  PLL2CFGR      PLL2P          LL_RCC_PLL2_Config \n
  *  PLL2CFGR      PLL2Q          LL_RCC_PLL2_Config \n
  *  PLL2CFGR      PLL2R          LL_RCC_PLL2_Config
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllp parameter can be a value between 1 and 128
  * @param pllq parameter can be a value between 1 and 128
  * @param pllr parameter can be a value between 1 and 128
  * @note PLL2 Source, PLLM, PLLN and PLLQ can be written only when PLL2 is disabled.
  * @note This  can be selected for USB, SDMMC.
  */
__STATIC_INLINE void LL_RCC_PLL2_Config(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq,
                                        uint32_t pllr)
{
  MODIFY_REG(RCC->PLL2CFGR, (RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2M),
             (source << RCC_PLL2CFGR_PLL2SRC_Pos)
             | ((pllm - 1U) << RCC_PLL2CFGR_PLL2M_Pos));
  MODIFY_REG(RCC->PLL2DIVR, (RCC_PLL2DIVR_PLL2N | RCC_PLL2DIVR_PLL2P | RCC_PLL2DIVR_PLL2Q | RCC_PLL2DIVR_PLL2R),
             (((plln - 1U) & RCC_PLL2DIVR_PLL2N)
              | (((pllp - 1U) << RCC_PLL2DIVR_PLL2P_Pos) & RCC_PLL2DIVR_PLL2P)
              | (((pllq - 1U) << RCC_PLL2DIVR_PLL2Q_Pos) & RCC_PLL2DIVR_PLL2Q)
              | (((pllr - 1U) << RCC_PLL2DIVR_PLL2R_Pos) & RCC_PLL2DIVR_PLL2R)));
}

/**
  * @brief  Configure PLL2 clock source
  * @rmtoll
  *  PLL2CFGR      PLL2SRC        LL_RCC_PLL2_SetSource
  * @param  pll2_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_PLL2_SetSource(uint32_t pll2_source)
{
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC, pll2_source);
}

/**
  * @brief  Get the oscillator used as PLL2 clock source.
  * @rmtoll
  *  PLL2CFGR      PLL2SRC        LL_RCC_PLL2_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL2SOURCE_NONE
  *         @arg @ref LL_RCC_PLL2SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL2SOURCE_HSI
  *         @arg @ref LL_RCC_PLL2SOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2SRC));
}

/**
  * @brief  Set Main PLL2 multiplication factor for VCO
  * @rmtoll
  *  PLL2CFGR      PLL2N          LL_RCC_PLL2_SetN
  * @param pll2n parameter can be a value between 4 and 512
  */
__STATIC_INLINE void LL_RCC_PLL2_SetN(uint32_t pll2n)
{
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N, (pll2n - 1UL) << RCC_PLL2DIVR_PLL2N_Pos);
}

/**
  * @brief  Get Main PLL2 multiplication factor for VCO
  * @rmtoll
  *  PLL2CFGR      PLL2N          LL_RCC_PLL2_GetN
  * @retval Between 4 and 512
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2N) >>  RCC_PLL2DIVR_PLL2N_Pos) + 1UL);
}


/**
  * @brief  Set Main PLL2 division factor for PLL2P
  * @rmtoll
  *  PLL2CFGR      PLL2P       LL_RCC_PLL2_SetP
  * @param pll2p parameter can be a value between 1 and 128
  * @note Used for SAI1 and SAI2 clock.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetP(uint32_t pll2p)
{
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2P, (pll2p - 1UL) << RCC_PLL2DIVR_PLL2P_Pos);
}

/**
  * @brief  Get Main PLL2 division factor for PLL2P
  * @rmtoll
  *  PLL2CFGR      PLL2P      LL_RCC_PLL2_GetP
  * @note Used for SAI1 and SAI2 clock.
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2P) >>  RCC_PLL2DIVR_PLL2P_Pos) + 1UL);
}


/**
  * @brief  Set Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL2DIVR      PLL2Q          LL_RCC_PLL2_SetQ
  * @param pll2q parameter can be a value between 1 and 128
  * @note Used for PLL48M1CLK selected for USB, SDMMC (48 MHz clock).
  */
__STATIC_INLINE void LL_RCC_PLL2_SetQ(uint32_t pll2q)
{
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2Q, (pll2q - 1UL) << RCC_PLL2DIVR_PLL2Q_Pos);
}

/**
  * @brief  Get Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL2CFGR      PLL2Q          LL_RCC_PLL2_GetQ
  * @note Used for PLL48M1CLK selected for USB, SDMMC (48 MHz clock).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2Q) >>  RCC_PLL2DIVR_PLL2Q_Pos) + 1UL);
}

/**
  * @brief  Set Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL2CFGR      PLL2R          LL_RCC_PLL2_SetR
  * @param pll2r parameter can be a value between 1 and 128
  * @note Used for PLL2CLK selected for USB, SDMMC (48 MHz clock).
  */
__STATIC_INLINE void  LL_RCC_PLL2_SetR(uint32_t pll2r)
{
  MODIFY_REG(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2R, (pll2r - 1UL) << RCC_PLL2DIVR_PLL2R_Pos);
}

/**
  * @brief  Get Main PLL2 division factor for PLL2R
  * @rmtoll
  *  PLL2DIVR      PLL2R          LL_RCC_PLL2_GetR
  * @note Used for PLL2CLK (system clock).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2DIVR, RCC_PLL2DIVR_PLL2Q) >>  RCC_PLL2DIVR_PLL2Q_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for the main PLL and other PLL
  * @rmtoll
  *  PLL2CFGR      PLL2M          LL_RCC_PLL2_SetDivider
  * @param pll2m parameter can be a value between 1 and 16
  */
__STATIC_INLINE void LL_RCC_PLL2_SetDivider(uint32_t pll2m)
{
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2M, (pll2m - 1UL) << RCC_PLL2CFGR_PLL2M_Pos);
}

/**
  * @brief  Get Division factor for the main PLL and other PLL
  * @rmtoll
  *  PLL2CFGR      PLL2M          LL_RCC_PLL2_GetDivider
  * @retval Between 1 and 16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetDivider(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2M) >>  RCC_PLL2CFGR_PLL2M_Pos) + 1UL);
}

/**
  * @brief  Enable PLL2 output mapped on SAI domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2PEN    LL_RCC_PLL2_EnableDomain_SAI
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableDomain_SAI(void)
{
  SET_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_P);
}

/**
  * @brief  Disable PLL2 output mapped on SAI domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2PEN    LL_RCC_PLL2_DisableDomain_SAI
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableDomain_SAI(void)
{
  CLEAR_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_P);
}

/**
  * @brief  Check if PLL2 output mapped on SAI domain clock is enabled
  * @rmtoll
  *  PLL2CFGR      PLL2PEN        LL_RCC_PLL2_IsEnabledDomain_SAI
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledDomain_SAI(void)
{
  return ((READ_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_P) == (LL_RCC_PLL2_OUTPUT_P)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2 output mapped on 48MHz domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2QEN    LL_RCC_PLL2_EnableDomain_48M
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableDomain_48M(void)
{
  SET_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_Q);
}

/**
  * @brief  Disable PLL2 output mapped on 48MHz domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2QEN    LL_RCC_PLL2_DisableDomain_48M
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableDomain_48M(void)
{
  CLEAR_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_Q);
}

/**
  * @brief  Check if PLL2 output mapped on 48M domain clock is enabled
  * @rmtoll
  *  PLL2CFGR      PLL2QEN        LL_RCC_PLL2_IsEnabledDomain_48M
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledDomain_48M(void)
{
  return ((READ_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_Q) == (LL_RCC_PLL2_OUTPUT_Q)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2 output mapped on ADC domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2REN    LL_RCC_PLL2_EnableDomain_ADC
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableDomain_ADC(void)
{
  SET_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_R);
}

/**
  * @brief  Disable PLL2 output mapped on ADC domain clock
  * @rmtoll
  *  PLL2CFGR  PLL2REN    LL_RCC_PLL2_DisableDomain_ADC
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableDomain_ADC(void)
{
  CLEAR_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_R);
}

/**
  * @brief  Check if PLL2 output mapped on ADC domain clock is enabled
  * @rmtoll
  *  PLL2CFGR      PLL2REN        LL_RCC_PLL2_IsEnabledDomain_ADC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsEnabledDomain_ADC(void)
{
  return ((READ_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_R) == (LL_RCC_PLL2_OUTPUT_R)) ? 1UL : 0UL);
}

/**
  * @brief  Enable 1 or several PLL2 outputs
  * @rmtoll
  *  PLL2CFGR      PLL2PEN        LL_RCC_PLL2_EnableOutput \n
  *  PLL2CFGR      PLL2QEN        LL_RCC_PLL2_EnableOutput \n
  *  PLL2CFGR      PLL2REN        LL_RCC_PLL2_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  */
__STATIC_INLINE void LL_RCC_PLL2_EnableOutput(uint32_t outputs)
{
  SET_BIT(RCC->PLL2CFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL2 outputs
  * @rmtoll
  *  PLL2CFGR      PLL2PEN        LL_RCC_PLL2_DisableOutput \n
  *  PLL2CFGR      PLL2QEN        LL_RCC_PLL2_DisableOutput \n
  *  PLL2CFGR      PLL2REN        LL_RCC_PLL2_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  * @note Cannot be disabled if the PLL2R output is used as the system clock.
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL2_DisableOutput(uint32_t outputs)
{
  CLEAR_BIT(RCC->PLL2CFGR, outputs);
}

/**
  * @brief Get the list of the outputs activated for PLL2
  * @rmtoll
  *  PLL2CFGR      PLL2PEN        LL_RCC_PLL2_DisableOutput \n
  *  PLL2CFGR      PLL2QEN        LL_RCC_PLL2_DisableOutput \n
  *  PLL2CFGR      PLL2REN        LL_RCC_PLL2_DisableOutput
  * @retval  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetOutput(void)
{
  return READ_BIT(RCC->PLL2CFGR, LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R);
}

/**
  * @brief  Check if 1 or several PLL2 outputs are enabled
  * @rmtoll
  *  PLL2CFGR      PLL2PEN        LL_RCC_PLL2_IsOutputEnabled \n
  *  PLL2CFGR      PLL2QEN        LL_RCC_PLL2_IsOutputEnabled \n
  *  PLL2CFGR      PLL2REN        LL_RCC_PLL2_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL2_OUTPUT_P
  *         @arg @ref LL_RCC_PLL2_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL2_OUTPUT_R
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_IsOutputEnabled(uint32_t outputs)
{
  return ((READ_BIT(RCC->PLL2CFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2 FRACN
  * @rmtoll
  *  PLL2CFGR           PLL2FRACEN         LL_RCC_PLL2FRACN_Enable
  */
__STATIC_INLINE void LL_RCC_PLL2FRACN_Enable(void)
{
  SET_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN);
}

/**
  * @brief  Check if PLL2 FRACN is enabled
  * @rmtoll
  *  PLL2CFGR           PLL2FRACEN         LL_RCC_PLL2FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN) == RCC_PLL2CFGR_PLL2FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL2 FRACN
  * @rmtoll
  *  PLL2CFGR           PLL2FRACEN         LL_RCC_PLL2FRACN_Disable
  */
__STATIC_INLINE void LL_RCC_PLL2FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2FRACEN);
}

/**
  * @brief  Set PLL2 FRACN Coefficient
  * @rmtoll
  *  PLL2FRACR        PLL2FRACN        LL_RCC_PLL2_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL2_SetFRACN(uint32_t fracn)
{
  MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_PLL2FRACN, fracn << RCC_PLL2FRACR_PLL2FRACN_Pos);
}

/**
  * @brief  Get PLL2 FRACN Coefficient
  * @rmtoll
  *  PLL2FRACR      PLL2FRACN          LL_RCC_PLL2_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL2_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL2FRACR, RCC_PLL2FRACR_PLL2FRACN) >>  RCC_PLL2FRACR_PLL2FRACN_Pos);
}

/**
  * @brief  Set PLL2 VCO Input Range
  * @rmtoll
  *  PLL2CFGR        PLL2RGE       LL_RCC_PLL2_SetVCOInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @note   This API must be called only when PLL2 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL2_SetVCOInputRange(uint32_t input_range)
{
  MODIFY_REG(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2RGE, input_range);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PLL3 PLL3
  * @{
  */

/**
  * @brief  Enable PLL3
  * @rmtoll
  *  CR           PLL3ON     LL_RCC_PLL3_Enable
  */
__STATIC_INLINE void LL_RCC_PLL3_Enable(void)
{
  SET_BIT(RCC->CR, RCC_CR_PLL3ON);
}

/**
  * @brief  Disable PLL3
  * @rmtoll
  *  CR           PLL3ON     LL_RCC_PLL3_Disable
  */
__STATIC_INLINE void LL_RCC_PLL3_Disable(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON);
}

/**
  * @brief  Check if PLL3 Ready
  * @rmtoll
  *  CR           PLL3RDY    LL_RCC_PLL3_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsReady(void)
{
  return ((READ_BIT(RCC->CR, RCC_CR_PLL3RDY) == RCC_CR_PLL3RDY) ? 1UL : 0UL);
}

/**
  * @brief  Configure PLL3 used for SAI domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3SRC    LL_RCC_PLL3_ConfigDomain_SAI \n
  *  PLL3CFGR  PLL3M      LL_RCC_PLL3_ConfigDomain_SAI \n
  *  PLL3CFGR  PLL3N      LL_RCC_PLL3_ConfigDomain_SAI \n
  *  PLL3DIVR  PLL3P      LL_RCC_PLL3_ConfigDomain_SAI
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllp parameter can be a value between 1 and 128
  * @note PLL3SRC/PLL3M/PLL3N/PLL3PDIV can be written only when PLL3 is disabled.
  * @note This  can be selected for SAI1 or SAI2.
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigDomain_SAI(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp)
{
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3SRC | RCC_PLL3CFGR_PLL3M, source |
             ((pllm - 1UL) << RCC_PLL3CFGR_PLL3M_Pos));
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3N | RCC_PLL3DIVR_PLL3P,
             ((plln - 1UL) << RCC_PLL3DIVR_PLL3N_Pos) | ((pllp - 1UL) << RCC_PLL3DIVR_PLL3P_Pos));
}


/**
  * @brief  Configure PLL3 used for 48MHz domain clock
  * @rmtoll
  *  PLL3CFGR      PLL3SRC        LL_RCC_PLL3_ConfigDomain_48M \n
  *  PLL3CFGR      PLL3M          LL_RCC_PLL3_ConfigDomain_48M \n
  *  PLL3CFGR      PLL3N          LL_RCC_PLL3_ConfigDomain_48M \n
  *  PLL3CFGR      PLL3Q          LL_RCC_PLL3_ConfigDomain_48M
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllq parameter can be a value between 1 and 128
  * @note PLL3 Source, PLLM, PLLN and PLLQ can be written only when PLL3 is disabled.
  * @note This  can be selected for USB, SDMMC.
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigDomain_48M(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllq)
{
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3SRC | RCC_PLL3CFGR_PLL3M, source |
             ((pllm - 1UL) << RCC_PLL3CFGR_PLL3M_Pos));
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3N | RCC_PLL3DIVR_PLL3Q,
             ((plln - 1UL) << RCC_PLL3DIVR_PLL3N_Pos) | ((pllq - 1UL) << RCC_PLL3DIVR_PLL3Q_Pos));
}


#if defined(LTDC) || defined(HSPI1)

/**
  * @brief  Configure PLL3 used for HSPI_LTDC domain clock
  * @rmtoll
  *  PLL3CFGR      PLL3SRC        LL_RCC_PLL3_ConfigDomain_HSPI_LTDC \n
  *  PLL3CFGR      PLL3M          LL_RCC_PLL3_ConfigDomain_HSPI_LTDC \n
  *  PLL3CFGR      PLL3N          LL_RCC_PLL3_ConfigDomain_HSPI_LTDC \n
  *  PLL3CFGR      PLL3R          LL_RCC_PLL3_ConfigDomain_HSPI_LTDC
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllr parameter can be a value between 1 and 128
  * @note PLL3 Source, PLLM, PLLN and PLLR can be written only when PLL3 is disabled.
  * @note This  can be selected for HSPI and LTDC.
  */
__STATIC_INLINE void LL_RCC_PLL3_ConfigDomain_HSPI_LTDC(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllr)
{
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3SRC | RCC_PLL3CFGR_PLL3M, source |
             ((pllm - 1UL) << RCC_PLL3CFGR_PLL3M_Pos));
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3N | RCC_PLL3DIVR_PLL3R,
             ((plln - 1UL) << RCC_PLL3DIVR_PLL3N_Pos) | ((pllr - 1UL) << RCC_PLL3DIVR_PLL3R_Pos));
}

#endif /* LTDC || HSPI1 */

/**
  * @brief  Configure PLL3
  * @rmtoll
  *  PLL3CFGR  PLL3SRC    LL_RCC_PLL3_Config \n
  *  PLL3CFGR  PLL3M      LL_RCC_PLL3_Config \n
  *  PLL3CFGR  PLL3N      LL_RCC_PLL3_Config \n
  *  PLL3CFGR  PLL3P      LL_RCC_PLL3_Config \n
  *  PLL3CFGR  PLL3Q      LL_RCC_PLL3_Config \n
  *  PLL3DIVR  PLL3R      LL_RCC_PLL3_Config
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  * @param pllm parameter can be a value between 1 and 16
  * @param plln parameter can be a value between 4 and 512
  * @param pllp parameter can be a value between 1 and 128
  * @param pllq parameter can be a value between 1 and 128
  * @param pllr parameter can be a value between 1 and 128
  * @note PLL3SRC/PLL3M/PLL3N/PLL3PDIV can be written only when PLL3 is disabled.
  * @note This  can be selected for SAI1 or SAI2.
  */
__STATIC_INLINE void LL_RCC_PLL3_Config(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq,
                                        uint32_t pllr)
{
  MODIFY_REG(RCC->PLL3CFGR, (RCC_PLL3CFGR_PLL3SRC | RCC_PLL3CFGR_PLL3M),
             (source << RCC_PLL3CFGR_PLL3SRC_Pos)
             | ((pllm - 1U) << RCC_PLL3CFGR_PLL3M_Pos));
  MODIFY_REG(RCC->PLL3DIVR, (RCC_PLL3DIVR_PLL3N | RCC_PLL3DIVR_PLL3P | RCC_PLL3DIVR_PLL3Q | RCC_PLL3DIVR_PLL3R),
             (((plln - 1U) & RCC_PLL3DIVR_PLL3N)
              | (((pllp - 1U) << RCC_PLL3DIVR_PLL3P_Pos) & RCC_PLL3DIVR_PLL3P)
              | (((pllq - 1U) << RCC_PLL3DIVR_PLL3Q_Pos) & RCC_PLL3DIVR_PLL3Q)
              | (((pllr - 1U) << RCC_PLL3DIVR_PLL3R_Pos) & RCC_PLL3DIVR_PLL3R)));
}

/**
  * @brief  Configure PLL3 clock source
  * @rmtoll
  *  PLL3CFGR      PLL3SRC        LL_RCC_PLL3_SetSource
  * @param  pll3_source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  */
__STATIC_INLINE void LL_RCC_PLL3_SetSource(uint32_t pll3_source)
{
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3SRC, pll3_source);
}

/**
  * @brief  Get the oscillator used as PLL3 clock source.
  * @rmtoll
  *  PLL3CFGR      PLL3SRC        LL_RCC_PLL3_GetSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_RCC_PLL3SOURCE_NONE
  *         @arg @ref LL_RCC_PLL3SOURCE_MSIS
  *         @arg @ref LL_RCC_PLL3SOURCE_HSI
  *         @arg @ref LL_RCC_PLL3SOURCE_HSE
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetSource(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3SRC));
}

/**
  * @brief  Set Main PLL3 multiplication factor for VCO
  * @rmtoll
  *  PLL3CFGR      PLL3N          LL_RCC_PLL3_SetN
  * @param pll3n parameter can be a value between 4 and 512
  */
__STATIC_INLINE void LL_RCC_PLL3_SetN(uint32_t pll3n)
{
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3N, (pll3n - 1UL) << RCC_PLL3DIVR_PLL3N_Pos);
}

/**
  * @brief  Get Main PLL3 multiplication factor for VCO
  * @rmtoll
  *  PLL3CFGR      PLL3N          LL_RCC_PLL3_GetN
  * @retval Between 4 and 512
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetN(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3N) >>  RCC_PLL3DIVR_PLL3N_Pos) + 1UL);
}


/**
  * @brief  Set Main PLL3 division factor for PLL3P
  * @rmtoll
  *  PLL3CFGR      PLL3P       LL_RCC_PLL3_SetP
  * @param pll3p parameter can be a value between 1 and 128
  * @note Used for SAI1 and SAI2 clock.
  */
__STATIC_INLINE void LL_RCC_PLL3_SetP(uint32_t pll3p)
{
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3P, (pll3p - 1UL) << RCC_PLL3DIVR_PLL3P_Pos);
}

/**
  * @brief  Get Main PLL3 division factor for PLL3P
  * @rmtoll
  *  PLL3CFGR      PLL3P      LL_RCC_PLL3_GetP
  * @note Used for SAI1 and SAI2 clock.
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetP(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3P) >>  RCC_PLL3DIVR_PLL3P_Pos) + 1UL);
}


/**
  * @brief  Set Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL3DIVR      PLL3Q          LL_RCC_PLL3_SetQ
  * @param pll3q parameter can be a value between 1 and 128
  * @note Used for PLL48M1CLK selected for USB, SDMMC (48 MHz clock).
  */
__STATIC_INLINE void LL_RCC_PLL3_SetQ(uint32_t pll3q)
{
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3Q, (pll3q - 1UL) << RCC_PLL3DIVR_PLL3Q_Pos);
}

/**
  * @brief  Get Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL3CFGR      PLL3Q          LL_RCC_PLL3_GetQ
  * @note Used for PLL48M1CLK selected for USB, SDMMC (48 MHz clock).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetQ(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3Q) >>  RCC_PLL3DIVR_PLL3Q_Pos) + 1UL);
}

/**
  * @brief  Set Main PLL division factor for PLLQ
  * @rmtoll
  *  PLL3CFGR      PLL3R          LL_RCC_PLL3_SetR
  * @param pll3r parameter can be a value between 1 and 128
  * @note Used for PLL3CLK selected for USB, SDMMC (48 MHz clock).
  */
__STATIC_INLINE void LL_RCC_PLL3_SetR(uint32_t pll3r)
{
  MODIFY_REG(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3R, (pll3r - 1UL) << RCC_PLL3DIVR_PLL3R_Pos);
}

/**
  * @brief  Get Main PLL3 division factor for PLL3R
  * @rmtoll
  *  PLL3DIVR      PLL3R          LL_RCC_PLL3_GetR
  * @note Used for PLL3CLK (system clock).
  * @retval Between 1 and 128
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetR(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3DIVR, RCC_PLL3DIVR_PLL3R) >>  RCC_PLL3DIVR_PLL3R_Pos) + 1UL);
}

/**
  * @brief  Set Division factor for the main PLL and other PLL
  * @rmtoll
  *  PLL3CFGR      PLL3M          LL_RCC_PLL3_SetDivider
  * @param pll3m parameter can be a value between 1 and 16
  */
__STATIC_INLINE void LL_RCC_PLL3_SetDivider(uint32_t pll3m)
{
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3M, (pll3m - 1UL) << RCC_PLL3CFGR_PLL3M_Pos);
}

/**
  * @brief  Get Division factor for the main PLL and other PLL
  * @rmtoll
  *  PLL3CFGR      PLL3M          LL_RCC_PLL3_GetDivider
  * @retval Between 1 and 16
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetDivider(void)
{
  return (uint32_t)((READ_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3M) >> RCC_PLL3CFGR_PLL3M_Pos) + 1UL);
}

/**
  * @brief  Enable PLL3 output mapped on SAI domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3PEN    LL_RCC_PLL3_EnableDomain_SAI
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableDomain_SAI(void)
{
  SET_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_P);
}

/**
  * @brief  Disable PLL3 output mapped on SAI domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3PEN    LL_RCC_PLL3_DisableDomain_SAI
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableDomain_SAI(void)
{
  CLEAR_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_P);
}

/**
  * @brief  Check if PLL3 output mapped on SAI domain clock is enabled
  * @rmtoll
  *  PLL3CFGR      PLL3PEN        LL_RCC_PLL3_IsEnabledDomain_SAI
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledDomain_SAI(void)
{
  return ((READ_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_P) == (LL_RCC_PLL3_OUTPUT_P)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL2 output mapped on 48MHz domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3QEN    LL_RCC_PLL3_EnableDomain_48M
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableDomain_48M(void)
{
  SET_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_Q);
}

/**
  * @brief  Disable PLL3 output mapped on 48MHz domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3QEN    LL_RCC_PLL3_DisableDomain_48M
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableDomain_48M(void)
{
  CLEAR_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_Q);
}

/**
  * @brief  Check if PLL3 output mapped on 48M domain clock is enabled
  * @rmtoll
  *  PLL3CFGR      PLL3QEN        LL_RCC_PLL3_IsEnabledDomain_48M
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledDomain_48M(void)
{
  return ((READ_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_Q) == (LL_RCC_PLL3_OUTPUT_Q)) ? 1UL : 0UL);
}

#if defined(LTDC) || defined(HSPI1)

/**
  * @brief  Enable PLL3 output mapped on HSPI_LTDC domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3REN    LL_RCC_PLL3_EnableDomain_HSPI_LTDC
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableDomain_HSPI_LTDC(void)
{
  SET_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_R);
}

/**
  * @brief  Disable PLL3 output mapped on HSPI_LTDC domain clock
  * @rmtoll
  *  PLL3CFGR  PLL3REN    LL_RCC_PLL3_DisableDomain_HSPI_LTDC
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableDomain_HSPI_LTDC(void)
{
  CLEAR_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_R);
}

/**
  * @brief  Check if PLL3 output mapped on HSPI_LTDC domain clock is enabled
  * @rmtoll
  *  PLL3CFGR      PLL3REN        LL_RCC_PLL3_IsEnabledDomain_HSPI_LTDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsEnabledDomain_HSPI_LTDC(void)
{
  return ((READ_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_R) == (LL_RCC_PLL3_OUTPUT_R)) ? 1UL : 0UL);
}

#endif /* LTDC || HSPI1 */

/**
  * @brief  Enable 1 or several PLL3 outputs
  * @rmtoll
  *  PLL3CFGR      PLL3PEN        LL_RCC_PLL3_EnableOutput \n
  *  PLL3CFGR      PLL3QEN        LL_RCC_PLL3_EnableOutput \n
  *  PLL3CFGR      PLL3REN        LL_RCC_PLL3_EnableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  */
__STATIC_INLINE void LL_RCC_PLL3_EnableOutput(uint32_t outputs)
{
  SET_BIT(RCC->PLL3CFGR, outputs);
}

/**
  * @brief  Disable 1 or several PLL3 outputs
  * @rmtoll
  *  PLL3CFGR      PLL3PEN        LL_RCC_PLL3_DisableOutput \n
  *  PLL3CFGR      PLL3QEN        LL_RCC_PLL3_DisableOutput \n
  *  PLL3CFGR      PLL3REN        LL_RCC_PLL3_DisableOutput
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  * @note Cannot be disabled if the PLL3R output is used as the system clock
  * @note When the PLL output is not used, deactivation saves power.
  */
__STATIC_INLINE void LL_RCC_PLL3_DisableOutput(uint32_t outputs)
{
  CLEAR_BIT(RCC->PLL3CFGR, outputs);
}

/**
  * @brief Get the list of the outputs activated for PLL3
  * @rmtoll
  *  PLL3CFGR      PLL3PEN        LL_RCC_PLL3_DisableOutput \n
  *  PLL3CFGR      PLL3QEN        LL_RCC_PLL3_DisableOutput \n
  *  PLL3CFGR      PLL3REN        LL_RCC_PLL3_DisableOutput
  * @retval  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetOutput(void)
{
  return READ_BIT(RCC->PLL3CFGR, LL_RCC_PLL3_OUTPUT_P | LL_RCC_PLL3_OUTPUT_Q | LL_RCC_PLL3_OUTPUT_R);
}

/**
  * @brief  Check if 1 or several PLL3 outputs are enabled
  * @rmtoll
  *  PLL3CFGR      PLL3PEN        LL_RCC_PLL3_IsOutputEnabled \n
  *  PLL3CFGR      PLL3QEN        LL_RCC_PLL3_IsOutputEnabled \n
  *  PLL3CFGR      PLL3REN        LL_RCC_PLL3_IsOutputEnabled
  * @param  outputs This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_PLL3_OUTPUT_P
  *         @arg @ref LL_RCC_PLL3_OUTPUT_Q
  *         @arg @ref LL_RCC_PLL3_OUTPUT_R
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_IsOutputEnabled(uint32_t outputs)
{
  return ((READ_BIT(RCC->PLL3CFGR, outputs) == (outputs)) ? 1UL : 0UL);
}

/**
  * @brief  Enable PLL3 FRACN
  * @rmtoll
  *  PLL3CFGR           PLL3FRACEN         LL_RCC_PLL3FRACN_Enable
  */
__STATIC_INLINE void LL_RCC_PLL3FRACN_Enable(void)
{
  SET_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3FRACEN);
}

/**
  * @brief  Check if PLL3 FRACN is enabled
  * @rmtoll
  *  PLL3CFGR           PLL3FRACEN         LL_RCC_PLL3FRACN_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3FRACN_IsEnabled(void)
{
  return ((READ_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3FRACEN) == RCC_PLL3CFGR_PLL3FRACEN) ? 1UL : 0UL);
}

/**
  * @brief  Disable PLL3 FRACN
  * @rmtoll
  *  PLL3CFGR           PLL3FRACEN         LL_RCC_PLL3FRACN_Disable
  */
__STATIC_INLINE void LL_RCC_PLL3FRACN_Disable(void)
{
  CLEAR_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3FRACEN);
}

/**
  * @brief  Set PLL3 FRACN Coefficient
  * @rmtoll
  *  PLL3FRACR        PLL3FRACN        LL_RCC_PLL3_SetFRACN
  * @param  fracn parameter can be a value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE void LL_RCC_PLL3_SetFRACN(uint32_t fracn)
{
  MODIFY_REG(RCC->PLL3FRACR, RCC_PLL3FRACR_PLL3FRACN, fracn << RCC_PLL3FRACR_PLL3FRACN_Pos);
}

/**
  * @brief  Get PLL3 FRACN Coefficient
  * @rmtoll
  *  PLL3FRACR      PLL3FRACN          LL_RCC_PLL3_GetFRACN
  * @retval A value between 0 and 8191 (0x1FFF)
  */
__STATIC_INLINE uint32_t LL_RCC_PLL3_GetFRACN(void)
{
  return (uint32_t)(READ_BIT(RCC->PLL3FRACR, RCC_PLL3FRACR_PLL3FRACN) >>  RCC_PLL3FRACR_PLL3FRACN_Pos);
}

/**
  * @brief  Set PLL3 VCO Input Range
  * @rmtoll
  *  PLL3CFGR        PLL3RGE       LL_RCC_PLL3_SetVCOInputRange
  * @param  input_range This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PLLINPUTRANGE_4_8
  *         @arg @ref LL_RCC_PLLINPUTRANGE_8_16
  * @note   This API must be called only when PLL3 is disabled.
  */
__STATIC_INLINE void LL_RCC_PLL3_SetVCOInputRange(uint32_t input_range)
{
  MODIFY_REG(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3RGE, input_range);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_PRIV Privileged mode
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/**
  * @brief  Enable Secure Privileged mode
  * @rmtoll
  *  PRIVCFGR       SPRIV         LL_RCC_EnableSecPrivilegedMode
  */
__STATIC_INLINE void LL_RCC_EnableSecPrivilegedMode(void)
{
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
}

/**
  * @brief  Disable Secure Privileged mode
  * @rmtoll
  *  PRIVCFGR           SPRIV          LL_RCC_DisableSecPrivilegedMode
  */
__STATIC_INLINE void LL_RCC_DisableSecPrivilegedMode(void)
{
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
}

#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3) */

/**
  * @brief  Check if Secure Privileged mode has been enabled or not
  * @rmtoll
  *  PRIVCFGR           SPRIV          LL_RCC_IsEnabledSecPrivilegedMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledSecPrivilegedMode(void)
{
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV) == RCC_PRIVCFGR_SPRIV) ? 1UL : 0UL);
}

/**
  * @brief  Enable Non Secure Privileged mode
  * @rmtoll
  *  PRIVCFGR       NSPRIV        LL_RCC_EnableNSecPrivilegedMode
  */
__STATIC_INLINE void LL_RCC_EnableNSecPrivilegedMode(void)
{
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Disable Non Secure Privileged mode
  * @rmtoll
  *  PRIVCFGR           NSPRIV          LL_RCC_DisableNSecPrivilegedMode
  */
__STATIC_INLINE void LL_RCC_DisableNSecPrivilegedMode(void)
{
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Check if Non Secure Privileged mode has been enabled or not
  * @rmtoll
  *  PRIVCFGR           NSPRIV          LL_RCC_IsEnabledNSecPrivilegedMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledNSecPrivilegedMode(void)
{
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV) == RCC_PRIVCFGR_NSPRIV) ? 1UL : 0UL);
}


/**
  * @brief  Enable privileged mode
  * @rmtoll
  *  PRIVCFGR       SPRIV         LL_RCC_EnablePrivilegedMode \n
  *  PRIVCFGR       NSPRIV        LL_RCC_EnablePrivilegedMode
  * @note   User might use LL_RCC_EnableSecPrivilegedMode() to enable Secure privilege.
  *         User might use LL_RCC_EnableNSecPrivilegedMode() to enable Non-secure privilege.
  *         This API is kept for legacy purpose only.
  */
__STATIC_INLINE void LL_RCC_EnablePrivilegedMode(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
#else
  SET_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3) */
}

/**
  * @brief  Disable Privileged mode
  * @rmtoll
  *  CR           PRIV          LL_RCC_DisablePrivilegedMode
  * @note   User might use LL_RCC_DisableSecPrivilegedMode() to disable Secure privilege.
  *         User might use LL_RCC_DisableNSecPrivilegedMode() to disable Non-secure privilege.
  *         This API is kept for legacy purpose only.
  */
__STATIC_INLINE void LL_RCC_DisablePrivilegedMode(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV);
#else
  CLEAR_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV);
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3) */
}

/**
  * @brief  Check if Privileged mode has been enabled or not
  * @rmtoll
  *  CR           PRIV          LL_RCC_IsEnabledPrivilegedMode
  * @note   User must use LL_RCC_IsEnabledSecPrivilegedMode() to check Secure privilege setting.
  *         User must use LL_RCC_IsEnabledNSecPrivilegedMode() to check Non-secure privilege setting.
  *         This API is kept for legacy purpose only.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledPrivilegedMode(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_SPRIV) == RCC_PRIVCFGR_SPRIV) ? 1UL : 0UL);
#else
  return ((READ_BIT(RCC->PRIVCFGR, RCC_PRIVCFGR_NSPRIV) == RCC_PRIVCFGR_NSPRIV) ? 1UL : 0UL);
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3) */
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear RCC interrupt flags
  * @rmtoll
  *  CICR         SHSIRDYC      LL_RCC_ClearFlag \n
  *  CICR         MSIKRDYC      LL_RCC_ClearFlag \n
  *  CICR         CSSC          LL_RCC_ClearFlag \n
  *  CICR         PLL3RDYC      LL_RCC_ClearFlag \n
  *  CICR         PLL2RDYC      LL_RCC_ClearFlag \n
  *  CICR         PLL1RDYC      LL_RCC_ClearFlag \n
  *  CICR         HSI48RDYC     LL_RCC_ClearFlag \n
  *  CICR         HSERDYC       LL_RCC_ClearFlag \n
  *  CICR         HSIRDYC       LL_RCC_ClearFlag \n
  *  CICR         MSISRDYC      LL_RCC_ClearFlag \n
  *  CICR         LSERDYC       LL_RCC_ClearFlag \n
  *  CICR         LSIRDYC       LL_RCC_ClearFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_MSIRDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_PLLRDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_HSECSS
  *            @arg @ref LL_RCC_IT_MSIKRDY
  *            @arg @ref LL_RCC_IT_SHSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag(uint32_t mask)
{
  WRITE_REG(RCC->CICR, mask);
}

/**
  * @brief  Clear LSI ready interrupt flag
  * @rmtoll
  *  CICR         LSIRDYC       LL_RCC_ClearFlag_LSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC);
}

/**
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll
  *  CICR         LSERDYC       LL_RCC_ClearFlag_LSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_LSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_LSERDYC);
}

/**
  * @brief  Clear MSI ready interrupt flag
  * @rmtoll
  *  CICR         MSISRDYC       LL_RCC_ClearFlag_MSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSISRDYC);
}

/**
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll
  *  CICR         HSIRDYC       LL_RCC_ClearFlag_HSIRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSIRDYC);
}

/**
  * @brief  Clear HSE ready interrupt flag
  * @rmtoll
  *  CICR         HSERDYC       LL_RCC_ClearFlag_HSERDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSERDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSERDYC);
}


/**
  * @brief  Clear HSI48 ready interrupt flag
  * @rmtoll
  *  CICR          HSI48RDYC     LL_RCC_ClearFlag_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSI48RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_HSI48RDYC);
}

/**
  * @brief  Clear PLL1 ready interrupt flag
  * @rmtoll
  *  CICR         PLL1RDYC       LL_RCC_ClearFlag_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL1RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL1RDYC);
}

/**
  * @brief  Clear PLL2 ready interrupt flag
  * @rmtoll
  *  CICR         PLL2RDYC       LL_RCC_ClearFlag_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL2RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL2RDYC);
}

/**
  * @brief  Clear PLL3 ready interrupt flag
  * @rmtoll
  *  CICR         PLL3RDYC       LL_RCC_ClearFlag_PLL3RDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_PLL3RDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_PLL3RDYC);
}

/**
  * @brief  Clear Clock security system interrupt flag
  * @rmtoll
  *  CICR         CSSC          LL_RCC_ClearFlag_HSECSS
  */
__STATIC_INLINE void LL_RCC_ClearFlag_HSECSS(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_CSSC);
}

/**
  * @brief  Clear MSIK ready interrupt flag
  * @rmtoll
  *  CICR         MSIKRDYC       LL_RCC_ClearFlag_MSIKRDY
  */
__STATIC_INLINE void LL_RCC_ClearFlag_MSIKRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_MSIKRDYC);
}

/**
  * @brief  Clear SHSI ready interrupt flag
  * @rmtoll
  *  CICR         SHSIRDYC       LL_RCC_ClearFlag_SHSIRDY
  */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
__STATIC_INLINE void LL_RCC_ClearFlag_SHSIRDY(void)
{
  SET_BIT(RCC->CICR, RCC_CICR_SHSIRDYC);
}
#endif /*(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)*/


/**
  * @brief  Clear RCC interrupt flags
  * @rmtoll
  *  CICR         SHSIRDYF      LL_RCC_IsActiveFlag \n
  *  CICR         MSIKRDYF      LL_RCC_IsActiveFlag \n
  *  CICR         CSSF          LL_RCC_IsActiveFlag \n
  *  CICR         PLL3RDYF      LL_RCC_IsActiveFlag \n
  *  CICR         PLL2RDYF      LL_RCC_IsActiveFlag \n
  *  CICR         PLL1RDYF      LL_RCC_IsActiveFlag \n
  *  CICR         HSI48RDYF     LL_RCC_IsActiveFlag \n
  *  CICR         HSERDYF       LL_RCC_IsActiveFlag \n
  *  CICR         HSIRDYF       LL_RCC_IsActiveFlag \n
  *  CICR         MSISRDYF      LL_RCC_IsActiveFlag \n
  *  CICR         LSERDYF       LL_RCC_IsActiveFlag \n
  *  CICR         LSIRDYF       LL_RCC_IsActiveFlag
  * @param  mask specifies the RCC flags to be cleared.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_MSIRDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_PLLRDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_HSECSS
  *            @arg @ref LL_RCC_IT_MSIKRDY
  *            @arg @ref LL_RCC_IT_SHSIRDY
  * @retval State of flags (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag(uint32_t mask)
{
  return ((READ_BIT(RCC->CIFR, mask) == mask) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll
  *  CIFR         LSIRDYF       LL_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSIRDYF) == RCC_CIFR_LSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll
  *  CIFR         LSERDYF       LL_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_LSERDYF) == RCC_CIFR_LSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI ready interrupt occurred or not
  * @rmtoll
  *  CIFR         MSISRDYF       LL_RCC_IsActiveFlag_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSISRDYF) == RCC_CIFR_MSISRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSIRDYF       LL_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSIRDYF) == RCC_CIFR_HSIRDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSERDYF       LL_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSERDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSERDYF) == RCC_CIFR_HSERDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48 ready interrupt occurred or not
  * @rmtoll
  *  CIFR         HSI48RDYF     LL_RCC_IsActiveFlag_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_HSI48RDYF) == RCC_CIFR_HSI48RDYF) ? 1UL : 0UL);
}
/**
  * @brief  Check if PLL1 ready interrupt occurred or not
  * @rmtoll
  *  CIFR         PLL1RDYF       LL_RCC_IsActiveFlag_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL1RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL1RDYF) == RCC_CIFR_PLL1RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 ready interrupt occurred or not
  * @rmtoll
  *  CIFR         PLL2RDYF       LL_RCC_IsActiveFlag_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL2RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL2RDYF) == RCC_CIFR_PLL2RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 ready interrupt occurred or not
  * @rmtoll
  *  CIFR         PLL3RDYF       LL_RCC_IsActiveFlag_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PLL3RDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_PLL3RDYF) == RCC_CIFR_PLL3RDYF) ? 1UL : 0UL);
}

/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll
  *  CIFR         CSSF          LL_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_HSECSS(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_CSSF) == RCC_CIFR_CSSF) ? 1UL : 0UL);
}

/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll
  *  CIFR         MSIKRDYF          LL_RCC_IsActiveFlag_MSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_MSIKRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_MSIKRDYF) == RCC_CIFR_MSIKRDYF) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll
  *  CIFR         SHSIRDYF          LL_RCC_IsActiveFlag_SHSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SHSIRDY(void)
{
  return ((READ_BIT(RCC->CIFR, RCC_CIFR_SHSIRDYF) == RCC_CIFR_SHSIRDYF) ? 1UL : 0UL);
}
#endif /*(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)*/

/**
  * @brief  Check if RCC flag Independent Watchdog reset is set or not.
  * @rmtoll
  *  CSR          IWDGRSTF      LL_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_IWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF) == RCC_CSR_IWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll
  *  CSR          LPWRRSTF      LL_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_LPWRRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_LPWRRSTF) == RCC_CSR_LPWRRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag is set or not.
  * @rmtoll
  *  CSR          OBLRSTF       LL_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_OBLRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_OBLRSTF) == RCC_CSR_OBLRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll
  *  CSR          PINRSTF       LL_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_PINRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_PINRSTF) == RCC_CSR_PINRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll
  *  CSR          SFTRSTF       LL_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_SFTRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_SFTRSTF) == RCC_CSR_SFTRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll
  *  CSR          WWDGRSTF      LL_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_WWDGRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_WWDGRSTF) == RCC_CSR_WWDGRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Check if RCC flag BOR reset is set or not.
  * @rmtoll
  *  CSR          BORRSTF       LL_RCC_IsActiveFlag_BORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsActiveFlag_BORRST(void)
{
  return ((READ_BIT(RCC->CSR, RCC_CSR_BORRSTF) == RCC_CSR_BORRSTF) ? 1UL : 0UL);
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll
  *  CSR          RMVF          LL_RCC_ClearResetFlags
  */
__STATIC_INLINE void LL_RCC_ClearResetFlags(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

/**
  * @}
  */

/** @defgroup RCC_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable RCC interrupts
  * @rmtoll
  *  CICR         SHSIRDYIE      LL_RCC_EnableIT \n
  *  CICR         MSIKRDYIE      LL_RCC_EnableIT \n
  *  CICR         PLL3RDYIE      LL_RCC_EnableIT \n
  *  CICR         PLL2RDYIE      LL_RCC_EnableIT \n
  *  CICR         PLL1RDYIE      LL_RCC_EnableIT \n
  *  CICR         HSI48RDYIE     LL_RCC_EnableIT \n
  *  CICR         HSERDYIE       LL_RCC_EnableIT \n
  *  CICR         HSIRDYIE       LL_RCC_EnableIT \n
  *  CICR         MSISRDYIE      LL_RCC_EnableIT \n
  *  CICR         LSERDYIE       LL_RCC_EnableIT \n
  *  CICR         LSIRDYIE       LL_RCC_EnableIT
  * @param  mask specifies the RCC IT to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_MSIRDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_PLLRDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_MSIKRDY
  *            @arg @ref LL_RCC_IT_SHSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT(uint32_t mask)
{
  SET_BIT(RCC->CIER, mask);
}

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll
  *  CIER         LSIRDYIE      LL_RCC_EnableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt
  * @rmtoll
  *  CIER         LSERDYIE      LL_RCC_EnableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_LSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Enable MSI ready interrupt
  * @rmtoll
  *  CIER         MSIRDYIE      LL_RCC_EnableIT_MSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSISRDYIE);
}

/**
  * @brief  Enable HSI ready interrupt
  * @rmtoll
  *  CIER         HSIRDYIE      LL_RCC_EnableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt
  * @rmtoll
  *  CIER         HSERDYIE      LL_RCC_EnableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSERDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Enable HSI48 ready interrupt
  * @rmtoll
  *  CIER          HSI48RDYIE    LL_RCC_EnableIT_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_HSI48RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Enable PLL1 ready interrupt
  * @rmtoll
  *  CIER         PLL1RDYIE      LL_RCC_EnableIT_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL1RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Enable PLL2 ready interrupt
  * @rmtoll
  *  CIER         PLL2RDYIE      LL_RCC_EnableIT_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL2RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE);
}

/**
  * @brief  Enable PLL3 ready interrupt
  * @rmtoll
  *  CIER         PLL3RDYIE      LL_RCC_EnableIT_PLL3RDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_PLL3RDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE);
}

/**
  * @brief  Enable MSIKRDYIE ready interrupt
  * @rmtoll
  *  CIER         MSIKRDYIE      LL_RCC_EnableIT_MSIKRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_MSIKRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_MSIKRDYIE);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/**
  * @brief  Enable SHSIRDYIE ready interrupt
  * @rmtoll
  *  CIER         SHSIRDYIE      LL_RCC_EnableIT_SHSIRDY
  */
__STATIC_INLINE void LL_RCC_EnableIT_SHSIRDY(void)
{
  SET_BIT(RCC->CIER, RCC_CIER_SHSIRDYIE);
}
#endif /*(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)*/

/**
  * @brief  Disable RCC interrupts
  * @rmtoll
  *  CICR         SHSIRDYIE      LL_RCC_DisableIT \n
  *  CICR         MSIKRDYIE      LL_RCC_DisableIT \n
  *  CICR         PLL3RDYIE      LL_RCC_DisableIT \n
  *  CICR         PLL2RDYIE      LL_RCC_DisableIT \n
  *  CICR         PLL1RDYIE      LL_RCC_DisableIT \n
  *  CICR         HSI48RDYIE     LL_RCC_DisableIT \n
  *  CICR         HSERDYIE       LL_RCC_DisableIT \n
  *  CICR         HSIRDYIE       LL_RCC_DisableIT \n
  *  CICR         MSISRDYIE      LL_RCC_DisableIT \n
  *  CICR         LSERDYIE       LL_RCC_DisableIT \n
  *  CICR         LSIRDYIE       LL_RCC_DisableIT
  * @param  mask specifies the RCC IT to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_RCC_IT_LSIRDY
  *            @arg @ref LL_RCC_IT_LSERDY
  *            @arg @ref LL_RCC_IT_MSIRDY
  *            @arg @ref LL_RCC_IT_HSIRDY
  *            @arg @ref LL_RCC_IT_HSERDY
  *            @arg @ref LL_RCC_IT_PLLRDY
  *            @arg @ref LL_RCC_IT_PLL2RDY
  *            @arg @ref LL_RCC_IT_PLL3RDY
  *            @arg @ref LL_RCC_IT_HSI48RDY
  *            @arg @ref LL_RCC_IT_MSIKRDY
  *            @arg @ref LL_RCC_IT_SHSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT(uint32_t mask)
{
  CLEAR_BIT(RCC->CIER, mask);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll
  *  CIER         LSIRDYIE      LL_RCC_DisableIT_LSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt
  * @rmtoll
  *  CIER         LSERDYIE      LL_RCC_DisableIT_LSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_LSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSERDYIE);
}

/**
  * @brief  Disable MSI ready interrupt
  * @rmtoll
  *  CIER         MSISRDYIE      LL_RCC_DisableIT_MSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSISRDYIE);
}

/**
  * @brief  Disable HSI ready interrupt
  * @rmtoll
  *  CIER         HSIRDYIE      LL_RCC_DisableIT_HSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt
  * @rmtoll
  *  CIER         HSERDYIE      LL_RCC_DisableIT_HSERDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSERDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSERDYIE);
}

/**
  * @brief  Disable HSI48 ready interrupt
  * @rmtoll
  *  CIER          HSI48RDYIE    LL_RCC_DisableIT_HSI48RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_HSI48RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE);
}

/**
  * @brief  Disable PLL1 ready interrupt
  * @rmtoll
  *  CIER         PLL1RDYIE      LL_RCC_DisableIT_PLL1RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL1RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE);
}

/**
  * @brief  Disable PLL2 ready interrupt
  * @rmtoll
  *  CIER         PLL2RDYIE      LL_RCC_DisableIT_PLL2RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL2RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE);
}

/**
  * @brief  Disable PLL3 ready interrupt
  * @rmtoll
  *  CIER         PLL3RDYIE      LL_RCC_DisableIT_PLL3RDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_PLL3RDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE);
}

/**
  * @brief  Disable MSIKRDYIE ready interrupt
  * @rmtoll
  *  CIER         MSIKRDYIE      LL_RCC_DisableIT_MSIKRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_MSIKRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_MSIKRDYIE);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/**
  * @brief  Disable SHSIRDYIE ready interrupt
  * @rmtoll
  *  CIER         SHSIRDYIE      LL_RCC_DisableIT_SHSIRDY
  */
__STATIC_INLINE void LL_RCC_DisableIT_SHSIRDY(void)
{
  CLEAR_BIT(RCC->CIER, RCC_CIER_SHSIRDYIE);
}
#endif /*(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)*/

/**
  * @brief  Check if LSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSIRDYIE      LL_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSIRDYIE) == RCC_CIER_LSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if LSE ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         LSERDYIE      LL_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_LSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_LSERDYIE) == RCC_CIER_LSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         MSIRDYIE      LL_RCC_IsEnabledIT_MSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSISRDYIE) == RCC_CIER_MSISRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSIRDYIE      LL_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSIRDYIE) == RCC_CIER_HSIRDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSE ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         HSERDYIE      LL_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSERDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSERDYIE) == RCC_CIER_HSERDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if HSI48 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER          HSI48RDYIE    LL_RCC_IsEnabledIT_HSI48RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_HSI48RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_HSI48RDYIE) == RCC_CIER_HSI48RDYIE) ? 1UL : 0UL);
}
/**
  * @brief  Check if PLL1 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PLL1RDYIE      LL_RCC_IsEnabledIT_PLL1RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL1RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL1RDYIE) == RCC_CIER_PLL1RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL2 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PLL2RDYIE      LL_RCC_IsEnabledIT_PLL2RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL2RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL2RDYIE) == RCC_CIER_PLL2RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if PLL3 ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         PLL3RDYIE      LL_RCC_IsEnabledIT_PLL3RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_PLL3RDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_PLL3RDYIE) == RCC_CIER_PLL3RDYIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if MSIK ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         MSIKRDYIE       LL_RCC_IsEnabledIT_MSIKRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_MSIKRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_MSIKRDYIE) == RCC_CIER_MSIKRDYIE) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/**
  * @brief  Check if SHSI ready interrupt source is enabled or disabled.
  * @rmtoll
  *  CIER         SHSIRDYIE      LL_RCC_IsEnabledIT_SHSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RCC_IsEnabledIT_SHSIRDY(void)
{
  return ((READ_BIT(RCC->CIER, RCC_CIER_SHSIRDYIE) == RCC_CIER_SHSIRDYIE) ? 1UL : 0UL);
}
#endif /*(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)*/

/**
  * @}
  */

/** @defgroup RCC_LL_EF_Security_Services Security Services
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)
/**
  * @brief  Configure RCC resources security
  * @rmtoll
  *  SECCFGR     HSISEC        LL_RCC_ConfigSecure \n
  *  SECCFGR     HSESEC        LL_RCC_ConfigSecure \n
  *  SECCFGR     MSISEC        LL_RCC_ConfigSecure \n
  *  SECCFGR     LSISEC        LL_RCC_ConfigSecure \n
  *  SECCFGR     LSESEC        LL_RCC_ConfigSecure \n
  *  SECCFGR     SYSCLKSEC     LL_RCC_ConfigSecure \n
  *  SECCFGR     PRESCSEC      LL_RCC_ConfigSecure \n
  *  SECCFGR     PLL1SEC       LL_RCC_ConfigSecure \n
  *  SECCFGR     PLL2SEC       LL_RCC_ConfigSecure \n
  *  SECCFGR     PLL3SEC       LL_RCC_ConfigSecure \n
  *  SECCFGR     CLK48MSEC     LL_RCC_ConfigSecure \n
  *  SECCFGR     HSI48SEC      LL_RCC_ConfigSecure \n
  *  SECCFGR     RMVFSEC       LL_RCC_ConfigSecure
  * @param  secure_config This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RCC_ALL_NSEC & LL_RCC_ALL_SEC
  *         @arg @ref LL_RCC_HSI_SEC & LL_RCC_HSI_NSEC
  *         @arg @ref LL_RCC_HSE_SEC & LL_RCC_HSE_NSEC
  *         @arg @ref LL_RCC_MSI_SEC & LL_RCC_MSI_NSEC
  *         @arg @ref LL_RCC_LSE_SEC & LL_RCC_LSE_NSEC
  *         @arg @ref LL_RCC_LSI_SEC & LL_RCC_LSI_NSEC
  *         @arg @ref LL_RCC_SYSCLK_SEC & LL_RCC_SYSCLK_NSEC
  *         @arg @ref LL_RCC_PRESCALERS_SEC & LL_RCC_PRESCALERS_NSEC
  *         @arg @ref LL_RCC_PLL1_SEC & LL_RCC_PLL1_NSEC
  *         @arg @ref LL_RCC_PLL2_SEC & LL_RCC_PLL2_NSEC
  *         @arg @ref LL_RCC_PLL3_SEC & LL_RCC_PLL3_NSEC
  *         @arg @ref LL_RCC_ICLK_SEC & LL_RCC_ICLK_NSEC
  *         @arg @ref LL_RCC_HSI48_SEC & LL_RCC_HSI48_NSEC
  *         @arg @ref LL_RCC_RESET_FLAGS_SEC & LL_RCC_RESET_FLAGS_NSEC
  * @note Only available from secure state when system implements security (TZEN=1).
  */
__STATIC_INLINE void LL_RCC_ConfigSecure(uint32_t secure_config)
{
  WRITE_REG(RCC->SECCFGR, secure_config);
}
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3) */

/**
  * @brief  Get RCC resources security status
  * @rmtoll
  *  SECCFGR     HSISEC        LL_RCC_GetConfigSecure \n
  *  SECCFGR     HSESEC        LL_RCC_GetConfigSecure \n
  *  SECCFGR     MSISEC        LL_RCC_GetConfigSecure \n
  *  SECCFGR     LSISEC        LL_RCC_GetConfigSecure \n
  *  SECCFGR     LSESEC        LL_RCC_GetConfigSecure \n
  *  SECCFGR     SYSCLKSEC     LL_RCC_GetConfigSecure \n
  *  SECCFGR     PRESCSEC      LL_RCC_GetConfigSecure \n
  *  SECCFGR     PLL1SEC       LL_RCC_GetConfigSecure \n
  *  SECCFGR     PLL2SEC       LL_RCC_GetConfigSecure \n
  *  SECCFGR     PLL3SEC       LL_RCC_GetConfigSecure \n
  *  SECCFGR     CLK48MSEC     LL_RCC_GetConfigSecure \n
  *  SECCFGR     HSI48SEC      LL_RCC_GetConfigSecure \n
  *  SECCFGR     RMVFSEC       LL_RCC_GetConfigSecure
  * @note Only available from secure state when system implements security (TZEN=1).
  * @retval Returned value can be one or a combination of the following values:
  *         @arg @ref LL_RCC_ALL_NSEC & LL_RCC_ALL_SEC
  *         @arg @ref LL_RCC_HSI_SEC & LL_RCC_HSI_NSEC
  *         @arg @ref LL_RCC_HSE_SEC & LL_RCC_HSE_NSEC
  *         @arg @ref LL_RCC_MSI_SEC & LL_RCC_MSI_NSEC
  *         @arg @ref LL_RCC_LSE_SEC & LL_RCC_LSE_NSEC
  *         @arg @ref LL_RCC_LSI_SEC & LL_RCC_LSI_NSEC
  *         @arg @ref LL_RCC_SYSCLK_SEC & LL_RCC_SYSCLK_NSEC
  *         @arg @ref LL_RCC_PRESCALERS_SEC & LL_RCC_PRESCALERS_NSEC
  *         @arg @ref LL_RCC_PLL1_SEC & LL_RCC_PLL1_NSEC
  *         @arg @ref LL_RCC_PLL2_SEC & LL_RCC_PLL2_NSEC
  *         @arg @ref LL_RCC_PLL3_SEC & LL_RCC_PLL3_NSEC
  *         @arg @ref LL_RCC_ICLK_SEC & LL_RCC_ICLK_NSEC
  *         @arg @ref LL_RCC_HSI48_SEC & LL_RCC_HSI48_NSEC
  *         @arg @ref LL_RCC_RESET_FLAGS_SEC & LL_RCC_RESET_FLAGS_NSEC
  */
__STATIC_INLINE uint32_t LL_RCC_GetConfigSecure(void)
{
  return (uint32_t)(READ_BIT(RCC->SECCFGR, RCC_SECURE_MASK));
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

#endif /* defined(RCC) */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_RCC_H */
