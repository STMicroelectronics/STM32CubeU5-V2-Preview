/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_pwr.h
  * @brief   Header file of PWR LL module.
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
#ifndef STM32U5XX_LL_PWR_H
#define STM32U5XX_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"
#include "stm32u5xx_ll_syscfg.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear flags defines
  * @brief    Flags defines which can be used with LL_PWR_WRITE_REG function
  * @{
  */
#define LL_PWR_SR_CSSF         PWR_SR_CSSF     /*!< Clear Stop and Standby flags */
#define LL_PWR_WUSCR_CWUF1     PWR_WUSCR_CWUF1 /*!< Clear Wakeup flag 1          */
#define LL_PWR_WUSCR_CWUF2     PWR_WUSCR_CWUF2 /*!< Clear Wakeup flag 2          */
#define LL_PWR_WUSCR_CWUF3     PWR_WUSCR_CWUF3 /*!< Clear Wakeup flag 3          */
#define LL_PWR_WUSCR_CWUF4     PWR_WUSCR_CWUF4 /*!< Clear Wakeup flag 4          */
#define LL_PWR_WUSCR_CWUF5     PWR_WUSCR_CWUF5 /*!< Clear Wakeup flag 5          */
#define LL_PWR_WUSCR_CWUF6     PWR_WUSCR_CWUF6 /*!< Clear Wakeup flag 6          */
#define LL_PWR_WUSCR_CWUF7     PWR_WUSCR_CWUF7 /*!< Clear Wakeup flag 7          */
#define LL_PWR_WUSCR_CWUF8     PWR_WUSCR_CWUF8 /*!< Clear Wakeup flag 8          */
#define LL_PWR_WUSCR_CWUF_ALL  PWR_WUSCR_CWUF  /*!< Clear all Wakeup flags       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get flags defines
  * @brief    Flags defines which can be used with LL_PWR_READ_REG function
  * @{
  */
#define LL_PWR_FLAG_VOSRDY      PWR_VOSR_VOSRDY      /*!< Voltage scaling ready flag                               */
#define LL_PWR_FLAG_BOOSTRDY    PWR_VOSR_BOOSTRDY    /*!< VOS EPOD booster ready flag                              */
#if defined (PWR_VOSR_USBBOOSTRDY)
#define LL_PWR_FLAG_USBBOOSTRDY PWR_VOSR_USBBOOSTRDY /*!< USB EPOD booster ready flag                              */
#endif /* defined (PWR_VOSR_USBBOOSTRDY) */
#define LL_PWR_FLAG_STOPF       PWR_SR_STOPF         /*!< Stop flag                                                */
#define LL_PWR_FLAG_SBF         PWR_SR_SBF           /*!< Standby flag                                             */
#define LL_PWR_FLAG_VDDA2RDY    PWR_SVMSR_VDDA2RDY   /*!< VDDA ready flag (versus 1.8 V threshold)                 */
#define LL_PWR_FLAG_VDDA1RDY    PWR_SVMSR_VDDA1RDY   /*!< VDDA ready flag (versus 1.6 V threshold)                 */
#define LL_PWR_FLAG_VDDIO2RDY   PWR_SVMSR_VDDIO2RDY  /*!< VDDIO2 ready flag                                        */
#define LL_PWR_FLAG_VDDUSBRDY   PWR_SVMSR_VDDUSBRDY  /*!< VDDUSB ready flag                                        */
#define LL_PWR_FLAG_ACTVOSRDY   PWR_SVMSR_ACTVOSRDY  /*!< Currently applied VOS ready flag                         */
#define LL_PWR_FLAG_PVDO        PWR_SVMSR_PVDO       /*!< VDD voltage detector output flag                         */
#define LL_PWR_FLAG_REGS        PWR_SVMSR_REGS       /*!< Regulator selection flag                                 */
#define LL_PWR_FLAG_TEMPH       PWR_BDSR_TEMPH       /*!< Temperature level flag (versus high threshold)           */
#define LL_PWR_FLAG_TEMPL       PWR_BDSR_TEMPL       /*!< Temperature level flag (versus low threshold)            */
#define LL_PWR_FLAG_VBATH       PWR_BDSR_VBATH       /*!< Backup domain voltage level flag (versus high threshold) */

#define LL_PWR_WAKEUP_FLAG1     PWR_WUSR_WUF1        /*!< Wakeup flag 1 */
#define LL_PWR_WAKEUP_FLAG2     PWR_WUSR_WUF2        /*!< Wakeup flag 2 */
#define LL_PWR_WAKEUP_FLAG3     PWR_WUSR_WUF3        /*!< Wakeup flag 3 */
#define LL_PWR_WAKEUP_FLAG4     PWR_WUSR_WUF4        /*!< Wakeup flag 4 */
#define LL_PWR_WAKEUP_FLAG5     PWR_WUSR_WUF5        /*!< Wakeup flag 5 */
#define LL_PWR_WAKEUP_FLAG6     PWR_WUSR_WUF6        /*!< Wakeup flag 6 */
#define LL_PWR_WAKEUP_FLAG7     PWR_WUSR_WUF7        /*!< Wakeup flag 7 */
#define LL_PWR_WAKEUP_FLAG8     PWR_WUSR_WUF8        /*!< Wakeup flag 8 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELCTION  Low power mode selection
  * @{
  */
#define LL_PWR_STOP0_MODE    0U                                /*!< Stop 0 mode   */
#define LL_PWR_STOP1_MODE    PWR_CR1_LPMS_0                    /*!< Stop 1 mode   */
#define LL_PWR_STOP2_MODE    PWR_CR1_LPMS_1                    /*!< Stop 2 mode   */
#define LL_PWR_STOP3_MODE    (PWR_CR1_LPMS_0 | PWR_CR1_LPMS_1) /*!< Stop 3 mode   */
#define LL_PWR_STANDBY_MODE  PWR_CR1_LPMS_2                    /*!< Standby mode  */
#define LL_PWR_SHUTDOWN_MODE (PWR_CR1_LPMS_2 | PWR_CR1_LPMS_1) /*!< Shutdown mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MODE_SELECTION PWR Mode selection
  * @{
  */
#define LL_PWR_MEMORIES_RUN_MODE ((uint32_t)&(PWR->CR1)) /*!< Memories Run mode       */
#define LL_PWR_MEMORIES_LP_MODE  ((uint32_t)&(PWR->CR2)) /*!< Memories Low Power mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_CORE_SLEEP_MODE  Core sleep mode
  * @{
  */
#define LL_PWR_CORE_SLEEP       0U                    /*!< Core sleep mode      */
#define LL_PWR_CORE_DEEP_SLEEP  SCB_SCR_SLEEPDEEP_Msk /*!< Core deep sleep mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_SB_CONTENTS_RETENTION PWR SRAM2 Content retention in Standby mode
  * @note  For some products of the U5 family (please see the Reference Manual),
  *        the SRAM2 content is preserved based on the same defines in Stop 3 mode.
  * @{
  */
#define LL_PWR_SRAM2_SB_NO_RETENTION    0U                              /*!< SRAM2 no retention in Stop 3 and Standby mode             */
#define LL_PWR_SRAM2_SB_PAGE1_RETENTION PWR_CR1_RRSB1                   /*!< SRAM2 page 1 (8 KB) retention in Stop 3 and Standby mode  */
#define LL_PWR_SRAM2_SB_PAGE2_RETENTION PWR_CR1_RRSB2                   /*!< SRAM2 page 2 (54 KB) retention in Stop 3 and Standby mode */
#define LL_PWR_SRAM2_SB_FULL_RETENTION  (PWR_CR1_RRSB1 | PWR_CR1_RRSB2) /*!< SRAM2 all pages retention in Stop 3 and Standby mode      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_BOR_MODE_STANDBY Brownout reset in Standby mode
  * @{
  */
#define LL_PWR_BOR_CONTINUOUS_MODE    0U             /*!< BOR continuous mode    */
#define LL_PWR_BOR_DISCONTINUOUS_MODE PWR_CR1_ULPMEN /*!< BOR discontinuous mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM1_STOP_CONTENTS_RETENTION PWR SRAM1 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM1_STOP_NO_RETENTION     0U                   /*!< SRAM1 no retention in Stop mode (Stop 0, 1, 2, 3)              */
#define LL_PWR_SRAM1_STOP_PAGE1_RETENTION  PWR_CR2_SRAM1PDS1    /*!< SRAM1 page 1  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE2_RETENTION  PWR_CR2_SRAM1PDS2    /*!< SRAM1 page 2  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE3_RETENTION  PWR_CR2_SRAM1PDS3    /*!< SRAM1 page 3  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#if defined (PWR_CR4_SRAM1PDS4)
#define LL_PWR_SRAM1_STOP_PAGE4_RETENTION  PWR_CR4_SRAM1PDS4    /*!< SRAM1 page 4  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE5_RETENTION  PWR_CR4_SRAM1PDS5    /*!< SRAM1 page 5  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE6_RETENTION  PWR_CR4_SRAM1PDS6    /*!< SRAM1 page 6  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE7_RETENTION  PWR_CR4_SRAM1PDS7    /*!< SRAM1 page 7  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE8_RETENTION  PWR_CR4_SRAM1PDS8    /*!< SRAM1 page 8  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE9_RETENTION  PWR_CR4_SRAM1PDS9    /*!< SRAM1 page 9  (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE10_RETENTION PWR_CR4_SRAM1PDS10   /*!< SRAM1 page 10 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE11_RETENTION PWR_CR4_SRAM1PDS11   /*!< SRAM1 page 11 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#define LL_PWR_SRAM1_STOP_PAGE12_RETENTION PWR_CR4_SRAM1PDS12   /*!< SRAM1 page 12 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3) */
#endif /* defined (PWR_CR4_SRAM1PDS4) */
#define LL_PWR_SRAM1_STOP_1_3_RETENTION    (PWR_CR2_SRAM1PDS1 | PWR_CR2_SRAM1PDS2 | \
                                            PWR_CR2_SRAM1PDS3)  /*!< SRAM1 pages (1 to 3) retention in Stop mode (Stop 0, 1, 2, 3)  */
#if defined (PWR_CR4_SRAM1PDS4)
#define LL_PWR_SRAM1_STOP_4_12_RETENTION   (PWR_CR4_SRAM1PDS4  | PWR_CR4_SRAM1PDS5  | \
                                            PWR_CR4_SRAM1PDS6  | PWR_CR4_SRAM1PDS7  | \
                                            PWR_CR4_SRAM1PDS8  | PWR_CR4_SRAM1PDS9  | \
                                            PWR_CR4_SRAM1PDS10 | PWR_CR4_SRAM1PDS11 | \
                                            PWR_CR4_SRAM1PDS12) /*!< SRAM1 pages (4 to 12) retention in Stop mode (Stop 0, 1, 2, 3) */
#endif /* defined (PWR_CR4_SRAM1PDS4) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_STOP_CONTENTS_RETENTION PWR SRAM2 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM2_STOP_NO_RETENTION    0U                                      /*!< SRAM2 no retention in Stop mode  (Stop 0, 1, 2)            */
#define LL_PWR_SRAM2_STOP_PAGE1_RETENTION PWR_CR2_SRAM2PDS1                       /*!< SRAM2 page 1 (8 KB) retention in Stop mode  (Stop 0, 1, 2) */
#define LL_PWR_SRAM2_STOP_PAGE2_RETENTION PWR_CR2_SRAM2PDS2                       /*!< SRAM2 page 2 (54 KB) retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_SRAM2_STOP_FULL_RETENTION  (PWR_CR2_SRAM2PDS1 | PWR_CR2_SRAM2PDS2) /*!< SRAM2 all pages retention in Stop mode      (Stop 0, 1, 2) */
/**
  * @}
  */

#if defined (PWR_CR2_SRAM3PDS1)
/** @defgroup PWR_LL_EC_SRAM3_STOP_CONTENTS_RETENTION PWR SRAM3 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM3_STOP_NO_RETENTION     0U                                       /*!< SRAM3 no retention in Stop mode (Stop 0, 1, 2, 3)               */
#define LL_PWR_SRAM3_STOP_PAGE1_RETENTION  PWR_CR2_SRAM3PDS1                        /*!< SRAM3 page 1 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE2_RETENTION  PWR_CR2_SRAM3PDS2                        /*!< SRAM3 page 2 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE3_RETENTION  PWR_CR2_SRAM3PDS3                        /*!< SRAM3 page 3 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE4_RETENTION  PWR_CR2_SRAM3PDS4                        /*!< SRAM3 page 4 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE5_RETENTION  PWR_CR2_SRAM3PDS5                        /*!< SRAM3 page 5 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE6_RETENTION  PWR_CR2_SRAM3PDS6                        /*!< SRAM3 page 6 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE7_RETENTION  PWR_CR2_SRAM3PDS7                        /*!< SRAM3 page 7 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE8_RETENTION  PWR_CR2_SRAM3PDS8                        /*!< SRAM3 page 8 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#if defined (PWR_CR4_SRAM3PDS9)
#define LL_PWR_SRAM3_STOP_PAGE9_RETENTION  PWR_CR4_SRAM3PDS9                        /*!< SRAM3 page 9 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM3_STOP_PAGE10_RETENTION PWR_CR4_SRAM3PDS10                       /*!< SRAM3 page 10 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)  */
#define LL_PWR_SRAM3_STOP_PAGE11_RETENTION PWR_CR4_SRAM3PDS11                       /*!< SRAM3 page 11 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)  */
#define LL_PWR_SRAM3_STOP_PAGE12_RETENTION PWR_CR4_SRAM3PDS12                       /*!< SRAM3 page 12 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)  */
#define LL_PWR_SRAM3_STOP_PAGE13_RETENTION PWR_CR4_SRAM3PDS13                       /*!< SRAM3 page 13 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)  */
#endif /* defined (PWR_CR4_SRAM3PDS9) */
#if defined(PWR_CR2_SRAM3PDS1)
#define LL_PWR_SRAM3_STOP_1_8_RETENTION    (PWR_CR2_SRAM3PDS1 | PWR_CR2_SRAM3PDS2 | PWR_CR2_SRAM3PDS3 | \
                                            PWR_CR2_SRAM3PDS4 | PWR_CR2_SRAM3PDS5 | PWR_CR2_SRAM3PDS6 | \
                                            PWR_CR2_SRAM3PDS7 | PWR_CR2_SRAM3PDS8)  /*!< SRAM3 pages (1 to 8) retention in Stop modes (Stop 0, 1, 2, 3)  */
#endif /* PWR_CR2_SRAM3PDS1 */
#if defined (PWR_CR4_SRAM3PDS9)
#define LL_PWR_SRAM3_STOP_9_13_RETENTION  (PWR_CR4_SRAM3PDS9  | PWR_CR4_SRAM3PDS10 | PWR_CR4_SRAM3PDS11 | \
                                           PWR_CR4_SRAM3PDS12 | PWR_CR4_SRAM3PDS13) /*!< SRAM3 pages (9 to 13) retention in Stop modes (Stop 0, 1, 2, 3) */
#endif /* defined (PWR_CR4_SRAM3PDS9) */
/**
  * @}
  */
#endif /* PWR_CR2_SRAM3PDS1 */

/** @defgroup PWR_LL_EC_SRAM4_STOP_CONTENTS_RETENTION PWR SRAM4 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM4_STOP_NO_RETENTION    0U               /*!< SRAM4 no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_SRAM4_STOP_FULL_RETENTION  PWR_CR2_SRAM4PDS /*!< SRAM4 retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */

#if defined (PWR_CR4_SRAM5PDS1)
/** @defgroup PWR_LL_EC_SRAM5_STOP_CONTENTS_RETENTION PWR SRAM5 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM5_STOP_NO_RETENTION     0U                   /*!< SRAM5 no retention in Stop mode (Stop 0, 1, 2, 3)               */
#define LL_PWR_SRAM5_STOP_PAGE1_RETENTION  PWR_CR4_SRAM5PDS1    /*!< SRAM5 page 1 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE2_RETENTION  PWR_CR4_SRAM5PDS2    /*!< SRAM5 page 2 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE3_RETENTION  PWR_CR4_SRAM5PDS3    /*!< SRAM5 page 3 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE4_RETENTION  PWR_CR4_SRAM5PDS4    /*!< SRAM5 page 4 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE5_RETENTION  PWR_CR4_SRAM5PDS5    /*!< SRAM5 page 5 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE6_RETENTION  PWR_CR4_SRAM5PDS6    /*!< SRAM5 page 6 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE7_RETENTION  PWR_CR4_SRAM5PDS7    /*!< SRAM5 page 7 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE8_RETENTION  PWR_CR4_SRAM5PDS8    /*!< SRAM5 page 8 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE9_RETENTION  PWR_CR4_SRAM5PDS9    /*!< SRAM5 page 4 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE10_RETENTION PWR_CR4_SRAM5PDS10   /*!< SRAM5 page 5 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE11_RETENTION PWR_CR4_SRAM5PDS11   /*!< SRAM5 page 6 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE12_RETENTION PWR_CR4_SRAM5PDS12   /*!< SRAM5 page 7 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_PAGE13_RETENTION PWR_CR4_SRAM5PDS13   /*!< SRAM5 page 8 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM5_STOP_FULL_RETENTION   (PWR_CR4_SRAM5PDS1  | PWR_CR4_SRAM5PDS2  | PWR_CR4_SRAM5PDS3  | \
                                            PWR_CR4_SRAM5PDS4  | PWR_CR4_SRAM5PDS5  | PWR_CR4_SRAM5PDS6  | \
                                            PWR_CR4_SRAM5PDS7  | PWR_CR4_SRAM5PDS8  | PWR_CR4_SRAM5PDS9  | \
                                            PWR_CR4_SRAM5PDS10 | PWR_CR4_SRAM5PDS11 | PWR_CR4_SRAM5PDS12 | \
                                            PWR_CR4_SRAM5PDS13) /*!< SRAM5 pages (1 to 13) retention in Stop modes (Stop 0, 1, 2, 3) */
/**
  * @}
  */
#endif /* defined (PWR_CR4_SRAM5PDS1) */

#if defined (PWR_CR5_SRAM6PDS1)
/** @defgroup PWR_LL_EC_SRAM6_STOP_CONTENTS_RETENTION PWR SRAM6 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM6_STOP_NO_RETENTION     0U                   /*!< SRAM6 no retention in Stop mode (Stop 0, 1, 2, 3)               */
#define LL_PWR_SRAM6_STOP_PAGE1_RETENTION  PWR_CR5_SRAM6PDS1    /*!< SRAM6 page 1 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE2_RETENTION  PWR_CR5_SRAM6PDS2    /*!< SRAM6 page 2 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE3_RETENTION  PWR_CR5_SRAM6PDS3    /*!< SRAM6 page 3 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE4_RETENTION  PWR_CR5_SRAM6PDS4    /*!< SRAM6 page 4 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE5_RETENTION  PWR_CR5_SRAM6PDS5    /*!< SRAM6 page 5 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE6_RETENTION  PWR_CR5_SRAM6PDS6    /*!< SRAM6 page 6 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE7_RETENTION  PWR_CR5_SRAM6PDS7    /*!< SRAM6 page 7 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_PAGE8_RETENTION  PWR_CR5_SRAM6PDS8    /*!< SRAM6 page 8 (64 KB) retention in Stop mode (Stop 0, 1, 2, 3)   */
#define LL_PWR_SRAM6_STOP_FULL_RETENTION   (PWR_CR5_SRAM6PDS1  | PWR_CR5_SRAM6PDS2  | PWR_CR5_SRAM6PDS3  | \
                                            PWR_CR5_SRAM6PDS4  | PWR_CR5_SRAM6PDS5  | PWR_CR5_SRAM6PDS6  | \
                                            PWR_CR5_SRAM6PDS7  | PWR_CR5_SRAM6PDS8)
/*!< SRAM6 pages (1 to 8) retention in Stop modes (Stop 0, 1, 2, 3)  */
/**
  * @}
  */
#endif /* defined (PWR_CR5_SRAM6PDS1)*/

/** @defgroup PWR_LL_EC_ICACHERAM_STOP_CONTENTS_RETENTION PWR ICACHE Content retention in Stop mode
  * @{
  */
#define LL_PWR_ICACHERAM_STOP_NO_RETENTION    0U               /*!< ICACHE SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_ICACHERAM_STOP_FULL_RETENTION  PWR_CR2_ICRAMPDS /*!< ICACHE SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_DCACHE1RAM_STOP_CONTENTS_RETENTION PWR DCACHE1 Content retention in Stop mode
  * @{
  */
#define LL_PWR_DCACHE1RAM_STOP_NO_RETENTION   0U                /*!< DCACHE1 SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION PWR_CR2_DC1RAMPDS /*!< DCACHE1 SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */

#if defined (PWR_CR2_DC2RAMPDS)
/** @defgroup PWR_LL_EC_DCACHE2RAM_STOP_CONTENTS_RETENTION PWR DCACHE2 Content retention in Stop mode
  * @{
  */
#define LL_PWR_DCACHE2RAM_STOP_NO_RETENTION   0U                /*!< DCACHE2 SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION PWR_CR2_DC2RAMPDS /*!< DCACHE2 SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */
#endif /* defined (PWR_CR2_DC2RAMPDS) */

#if defined(PWR_CR2_DMA2DRAMPDS)
/** @defgroup PWR_LL_EC_DMA2DRAM_STOP_CONTENTS_RETENTION PWR DMA2DRAM Content retention in Stop mode
  * @{
  */
#define LL_PWR_DMA2DRAM_STOP_NO_RETENTION    0U                  /*!< DMA2D SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_DMA2DRAM_STOP_FULL_RETENTION  PWR_CR2_DMA2DRAMPDS /*!< DMA2D SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */
#endif /* PWR_CR2_DMA2DRAMPDS */

/** @defgroup PWR_LL_EC_PERIPHRAM_STOP_CONTENTS_RETENTION PWR PERIPHRAM Content retention in Stop mode
  * @{
  */
#define LL_PWR_PERIPHRAM_STOP_NO_RETENTION   0U              /*!< FMAC, FDCAN and USB SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_PERIPHRAM_STOP_FULL_RETENTION PWR_CR2_PRAMPDS /*!< FMAC, FDCAN and USB SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */

#if defined(PWR_CR2_PKARAMPDS)
/** @defgroup PWR_LL_EC_PKARAM_STOP_CONTENTS_RETENTION PWR PKARAM Content retention in Stop mode
  * @{
  */
#define LL_PWR_PKARAM_STOP_NO_RETENTION   0U                /*!< PKA32 SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_PKARAM_STOP_FULL_RETENTION PWR_CR2_PKARAMPDS /*!< PKA32 SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */
#endif /* defined(PWR_CR2_PKARAMPDS) */

#if defined (PWR_CR2_GPRAMPDS)
/** @defgroup PWR_LL_EC_GPRAM_STOP_CONTENTS_RETENTION PWR GPRAM Content retention in Stop mode
  * @{
  */
#define LL_PWR_GRAPHICPERIPHRAM_STOP_NO_RETENTION   0U               /*!< Graphic peripherals (LTDC, GFXMMU) SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION PWR_CR2_GPRAMPDS /*!< Graphic peripherals (LTDC, GFXMMU) SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */
#endif /* defined (PWR_CR2_GPRAMPDS) */

#if defined (PWR_CR2_DSIRAMPDS)
/** @defgroup PWR_LL_EC_DSIRAM_STOP_CONTENTS_RETENTION PWR DSI RAM Content retention in Stop mode
  * @{
  */
#define LL_PWR_DSIRAM_STOP_NO_RETENTION   0U                /*!< DSI SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_DSIRAM_STOP_FULL_RETENTION PWR_CR2_DSIRAMPDS /*!< DSI SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */
#endif /* defined (PWR_CR2_DSIRAMPDS) */

#if defined (PWR_CR2_JPEGRAMPDS)
/** @defgroup PWR_LL_EC_JPEGRAM_STOP_CONTENTS_RETENTION PWR JPEG RAM Content retention in Stop mode
  * @{
  */
#define LL_PWR_JPEGRAM_STOP_NO_RETENTION   0U                 /*!< JPEG SRAM no retention in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_JPEGRAM_STOP_FULL_RETENTION PWR_CR2_JPEGRAMPDS /*!< JPEG SRAM retention in Stop mode (Stop 0, 1, 2)    */
/**
  * @}
  */
#endif /* defined (PWR_CR2_JPEGRAMPDS) */

/** @defgroup PWR_LL_EC_SRAM1_RUN_CONTENTS_RETENTION PWR SRAM1 Content retention in Run mode
  * @{
  */
#define LL_PWR_SRAM1_RUN_NO_RETENTION   0U              /*!< SRAM1 no retention in Run mode */
#define LL_PWR_SRAM1_RUN_FULL_RETENTION PWR_CR1_SRAM1PD /*!< SRAM1 retention in Run mode    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_RUN_CONTENTS_RETENTION PWR SRAM2 Content retention in Run mode
  * @{
  */
#define LL_PWR_SRAM2_RUN_NO_RETENTION   0U              /*!< SRAM2 no retention in Run mode */
#define LL_PWR_SRAM2_RUN_FULL_RETENTION PWR_CR1_SRAM2PD /*!< SRAM2 retention in Run mode    */
/**
  * @}
  */

#if defined (PWR_CR1_SRAM3PD)
/** @defgroup PWR_LL_EC_SRAM3_RUN_CONTENTS_RETENTION PWR SRAM3 Content retention in Run mode
  * @{
  */
#define LL_PWR_SRAM3_RUN_NO_RETENTION   0U              /*!< SRAM3 no retention in Run mode */
#define LL_PWR_SRAM3_RUN_FULL_RETENTION PWR_CR1_SRAM3PD /*!< SRAM3 retention in Run mode    */
/**
  * @}
  */
#endif /* PWR_CR1_SRAM3PD */

/** @defgroup PWR_LL_EC_SRAM4_RUN_CONTENTS_RETENTION PWR SRAM4 Content retention in Run mode
  * @{
  */
#define LL_PWR_SRAM4_RUN_NO_RETENTION   0U              /*!< SRAM4 no retention in Run mode */
#define LL_PWR_SRAM4_RUN_FULL_RETENTION PWR_CR1_SRAM4PD /*!< SRAM4 retention in Run mode    */
/**
  * @}
  */

#if defined (PWR_CR1_SRAM5PD)
/** @defgroup PWR_LL_EC_SRAM5_RUN_CONTENTS_RETENTION PWR SRAM5 Content retention in Run mode
  * @{
  */
#define LL_PWR_SRAM5_RUN_NO_RETENTION   0U              /*!< SRAM5 no retention in Run mode */
#define LL_PWR_SRAM5_RUN_FULL_RETENTION PWR_CR1_SRAM5PD /*!< SRAM5 retention in Run mode    */
/**
  * @}
  */
#endif /* defined (PWR_CR1_SRAM5PD) */

#if defined (PWR_CR1_SRAM6PD)
/** @defgroup PWR_LL_EC_SRAM6_RUN_CONTENTS_RETENTION PWR SRAM6 Content retention in Run mode
  * @{
  */
#define LL_PWR_SRAM6_RUN_NO_RETENTION   0U              /*!< SRAM6 no retention in Run mode */
#define LL_PWR_SRAM6_RUN_FULL_RETENTION PWR_CR1_SRAM6PD /*!< SRAM6 retention in Run mode    */
/**
  * @}
  */
#endif /* defined (PWR_CR1_SRAM6PD) */

/** @defgroup PWR_LL_EC_FLASH_SRAM4_FAST_WAKEUP PWR flash and SRAM4 memory fast Wakeup
  * @{
  */
#define LL_PWR_FLASHFWU    PWR_CR2_FLASHFWU                      /*!< Flash memory fast wakeup from Stop modes (Stop 0, 1)    */
#define LL_PWR_SRAM4FWU    PWR_CR2_SRAM4FWU                      /*!< SRAM4 memory fast wakeup from Stop modes (Stop 0, 1, 2) */
#define LL_PWR_MEMORIESFWU (PWR_CR2_FLASHFWU | PWR_CR2_SRAM4FWU) /*!< All memories fast wakeup from Stop modes                */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRD_MODE PWR Smart Run Domain mode
  * @{
  */
#define LL_PWR_SRD_STOP_MODE  0U             /*!< SmartRun domain AHB3 and APB3 clocks disabled by default in Stop mode (Stop 0, 1, 2) */
#define LL_PWR_SRD_RUN_MODE   PWR_CR2_SRDRUN /*!< SmartRun domain AHB3 and APB3 clocks kept enabled in Stop mode (Stop 0, 1, 2)        */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGULATOR_SUPPLY_SELECTION PWR Regulator supply selection
  * @{
  */
#define LL_PWR_MAIN_REGU_LDO_SUPPLY   0U             /*!< LDO regulator supply  */
#define LL_PWR_MAIN_REGU_SMPS_SUPPLY  PWR_CR3_REGSEL /*!< SMPS regulator supply */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGULATOR_STARTUP_MODE PWR Regulator startup mode
  * @{
  */
#define LL_PWR_MAIN_REGU_SLOW_STARTUP  0U            /*!< Main regulator slow startup */
#define LL_PWR_MAIN_REGU_FAST_STARTUP  PWR_CR3_FSTEN /*!< Main regulator fast startup */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_REGU_VOLT_SCALE_1 PWR_VOSR_VOS   /*!< Voltage scaling range 1 */
#define LL_PWR_REGU_VOLT_SCALE_2 PWR_VOSR_VOS_1 /*!< Voltage scaling range 2 */
#define LL_PWR_REGU_VOLT_SCALE_3 PWR_VOSR_VOS_0 /*!< Voltage scaling range 3 */
#define LL_PWR_REGU_VOLT_SCALE_4 (0x0U)         /*!< Voltage scaling range 4 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVD_LEVEL_SELECTION PWR Programmable voltage detector level selection
  * @{
  */
#define LL_PWR_PVDLEVEL_0 0U                                      /*!< Voltage threshold detected by PVD 2.0 V  */
#define LL_PWR_PVDLEVEL_1 PWR_SVMCR_PVDLS_0                       /*!< Voltage threshold detected by PVD 2.2 V  */
#define LL_PWR_PVDLEVEL_2 PWR_SVMCR_PVDLS_1                       /*!< Voltage threshold detected by PVD 2.4 V  */
#define LL_PWR_PVDLEVEL_3 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_1) /*!< Voltage threshold detected by PVD 2.5 V  */
#define LL_PWR_PVDLEVEL_4 PWR_SVMCR_PVDLS_2                       /*!< Voltage threshold detected by PVD 2.6 V  */
#define LL_PWR_PVDLEVEL_5 (PWR_SVMCR_PVDLS_0 | PWR_SVMCR_PVDLS_2) /*!< Voltage threshold detected by PVD 2.8 V  */
#define LL_PWR_PVDLEVEL_6 (PWR_SVMCR_PVDLS_1 | PWR_SVMCR_PVDLS_2) /*!< Voltage threshold detected by PVD 2.9 V  */
#define LL_PWR_PVDLEVEL_7 PWR_SVMCR_PVDLS                         /*!< External input analog voltage on PVD_IN
                                                                       pin, compared to internal VREFINT level  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVM_PRIPHERAL_ANALOG_VOLTAGE_MONITOR PWR independent analog supply voltage monitor
  * @{
  */
#define LL_PWR_ANALOG_VOLTAGE_MONITOR_1 PWR_SVMCR_AVM1EN                         /*!< VddA1 voltage monitor versus 1.6 V  */
#define LL_PWR_ANALOG_VOLTAGE_MONITOR_2 PWR_SVMCR_AVM2EN                         /*!< VddA2 voltage monitor versus 1.8 V  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_POLARITY PWR Wakeup pin polarity
  * @{
  */
#define LL_PWR_WAKEUP_PIN_POLARITY_HIGH 0U   /*!< Wakeup pin polarity high */
#define LL_PWR_WAKEUP_PIN_POLARITY_LOW  1U   /*!< Wakeup pin polarity low  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN PWR Wakeup pin
  * @{
  */
#define LL_PWR_WAKEUP_PIN1    PWR_WUCR1_WUPEN1 /*!< Wakeup pin 1 enable   */
#define LL_PWR_WAKEUP_PIN2    PWR_WUCR1_WUPEN2 /*!< Wakeup pin 2 enable   */
#define LL_PWR_WAKEUP_PIN3    PWR_WUCR1_WUPEN3 /*!< Wakeup pin 3 enable   */
#define LL_PWR_WAKEUP_PIN4    PWR_WUCR1_WUPEN4 /*!< Wakeup pin 4 enable   */
#define LL_PWR_WAKEUP_PIN5    PWR_WUCR1_WUPEN5 /*!< Wakeup pin 5 enable   */
#define LL_PWR_WAKEUP_PIN6    PWR_WUCR1_WUPEN6 /*!< Wakeup pin 6 enable   */
#define LL_PWR_WAKEUP_PIN7    PWR_WUCR1_WUPEN7 /*!< Wakeup pin 7 enable   */
#define LL_PWR_WAKEUP_PIN8    PWR_WUCR1_WUPEN8 /*!< Wakeup pin 8 enable   */
#define LL_PWR_WAKEUP_PIN_ALL (0xFFU)          /*!< Wakeup all pin enable */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_SELECTION PWR Wakeup pin selection
  * @{
  */
#define LL_PWR_WAKEUP_PIN_SELECTION_0 0UL                /*!< Wakeup pin selection 0 */
#define LL_PWR_WAKEUP_PIN_SELECTION_1 PWR_WUCR3_WUSEL1_0 /*!< Wakeup pin selection 1 */
#define LL_PWR_WAKEUP_PIN_SELECTION_2 PWR_WUCR3_WUSEL1_1 /*!< Wakeup pin selection 2 */
#define LL_PWR_WAKEUP_PIN_SELECTION_3 PWR_WUCR3_WUSEL1   /*!< Wakeup pin selection 3 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_CHARGING_RESISTOR_SELECTION PWR Vbat charging resistor selection
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K   0U             /*!< Charge the battery through a 5 kO resistor   */
#define LL_PWR_BATT_CHARG_RESISTOR_1_5K PWR_BDCR2_VBRS /*!< Charge the battery through a 1.5 kO resistor */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PORT_SELECTION PWR GPIO port selection
  * @{
  */
#define LL_PWR_GPIO_PORTA ((uint32_t)&(PWR->PUCRA))  /*!< GPIO port A */
#define LL_PWR_GPIO_PORTB ((uint32_t)&(PWR->PUCRB))  /*!< GPIO port B */
#define LL_PWR_GPIO_PORTC ((uint32_t)&(PWR->PUCRC))  /*!< GPIO port C */
#define LL_PWR_GPIO_PORTD ((uint32_t)&(PWR->PUCRD))  /*!< GPIO port D */
#define LL_PWR_GPIO_PORTE ((uint32_t)&(PWR->PUCRE))  /*!< GPIO port E */
#if defined(PWR_PUCRF_PU0)
#define LL_PWR_GPIO_PORTF ((uint32_t)&(PWR->PUCRF))  /*!< GPIO port F */
#endif /* defined(PWR_PUCRF_PU0) */
#define LL_PWR_GPIO_PORTG ((uint32_t)&(PWR->PUCRG))  /*!< GPIO port G */
#define LL_PWR_GPIO_PORTH ((uint32_t)&(PWR->PUCRH))  /*!< GPIO port H */
#if defined(PWR_PUCRI_PU0)
#define LL_PWR_GPIO_PORTI ((uint32_t)&(PWR->PUCRI))  /*!< GPIO port I */
#endif /* defined(PWR_PUCRI_PU0) */
#if defined (PWR_PUCRJ_PU0)
#define LL_PWR_GPIO_PORTJ ((uint32_t)&(PWR->PUCRJ))  /*!< GPIO port J */
#endif /* defined (PWR_PUCRJ_PU0) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PIN_MASK PWR GPIO pin mask
  * @{
  */
#define LL_PWR_GPIO_PIN_0  0x0001U /*!< GPIO port I/O pin 0  */
#define LL_PWR_GPIO_PIN_1  0x0002U /*!< GPIO port I/O pin 1  */
#define LL_PWR_GPIO_PIN_2  0x0004U /*!< GPIO port I/O pin 2  */
#define LL_PWR_GPIO_PIN_3  0x0008U /*!< GPIO port I/O pin 3  */
#define LL_PWR_GPIO_PIN_4  0x0010U /*!< GPIO port I/O pin 4  */
#define LL_PWR_GPIO_PIN_5  0x0020U /*!< GPIO port I/O pin 5  */
#define LL_PWR_GPIO_PIN_6  0x0040U /*!< GPIO port I/O pin 6  */
#define LL_PWR_GPIO_PIN_7  0x0080U /*!< GPIO port I/O pin 7  */
#define LL_PWR_GPIO_PIN_8  0x0100U /*!< GPIO port I/O pin 8  */
#define LL_PWR_GPIO_PIN_9  0x0200U /*!< GPIO port I/O pin 9  */
#define LL_PWR_GPIO_PIN_10 0x0400U /*!< GPIO port I/O pin 10 */
#define LL_PWR_GPIO_PIN_11 0x0800U /*!< GPIO port I/O pin 11 */
#define LL_PWR_GPIO_PIN_12 0x1000U /*!< GPIO port I/O pin 12 */
#define LL_PWR_GPIO_PIN_13 0x2000U /*!< GPIO port I/O pin 13 */
#define LL_PWR_GPIO_PIN_14 0x4000U /*!< GPIO port I/O pin 14 */
#define LL_PWR_GPIO_PIN_15 0x8000U /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ITEMS_SECURE_ATTRIBUTE PWR Items secure attribute
  * @{
  */
#define LL_PWR_WAKEUP_PIN1_NSEC 0U                  /*!< Wake up pin 1 nsecure mode            */
#define LL_PWR_WAKEUP_PIN1_SEC  PWR_SECCFGR_WUP1SEC /*!< Wake up pin 1 secure mode             */
#define LL_PWR_WAKEUP_PIN2_NSEC 0U                  /*!< Wake up pin 2 nsecure mode            */
#define LL_PWR_WAKEUP_PIN2_SEC  PWR_SECCFGR_WUP2SEC /*!< Wake up pin 2 secure mode             */
#define LL_PWR_WAKEUP_PIN3_NSEC 0U                  /*!< Wake up pin 3 nsecure mode            */
#define LL_PWR_WAKEUP_PIN3_SEC  PWR_SECCFGR_WUP3SEC /*!< Wake up pin 3 secure mode             */
#define LL_PWR_WAKEUP_PIN4_NSEC 0U                  /*!< Wake up pin 4 nsecure mode            */
#define LL_PWR_WAKEUP_PIN4_SEC  PWR_SECCFGR_WUP4SEC /*!< Wake up pin 4 secure mode             */
#define LL_PWR_WAKEUP_PIN5_NSEC 0U                  /*!< Wake up pin 5 nsecure mode            */
#define LL_PWR_WAKEUP_PIN5_SEC  PWR_SECCFGR_WUP5SEC /*!< Wake up pin 5 secure mode             */
#define LL_PWR_WAKEUP_PIN6_NSEC 0U                  /*!< Wake up pin 6 nsecure mode            */
#define LL_PWR_WAKEUP_PIN6_SEC  PWR_SECCFGR_WUP6SEC /*!< Wake up pin 6 secure mode             */
#define LL_PWR_WAKEUP_PIN7_NSEC 0U                  /*!< Wake up pin 7 nsecure mode            */
#define LL_PWR_WAKEUP_PIN7_SEC  PWR_SECCFGR_WUP7SEC /*!< Wake up pin 7 secure mode             */
#define LL_PWR_WAKEUP_PIN8_NSEC 0U                  /*!< Wake up pin 8 nsecure mode            */
#define LL_PWR_WAKEUP_PIN8_SEC  PWR_SECCFGR_WUP8SEC /*!< Wake up pin 8 secure mode             */

#define LL_PWR_LPM_NSEC 0U                 /*!< Low-power modes nsecure mode                  */
#define LL_PWR_LPM_SEC  PWR_SECCFGR_LPMSEC /*!< Low-power modes secure mode                   */
#define LL_PWR_VDM_NSEC 0U                 /*!< Voltage detection and monitoring nsecure mode */
#define LL_PWR_VDM_SEC  PWR_SECCFGR_VDMSEC /*!< Voltage detection and monitoring secure mode  */
#define LL_PWR_VB_NSEC  0U                 /*!< Backup domain nsecure mode                    */
#define LL_PWR_VB_SEC   PWR_SECCFGR_VBSEC  /*!< Backup domain secure mode                     */
#define LL_PWR_APC_NSEC 0U                 /*!< Pull-up/pull-down nsecure mode                */
#define LL_PWR_APC_SEC  PWR_SECCFGR_APCSEC /*!< Pull-up/pull-down secure mode                 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers macros
  * @{
  */

/**
  * @brief  Write a value in PWR register.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_PWR_WRITE_REG(reg, value) WRITE_REG((PWR)->reg, (value))

/**
  * @brief  Read a value in PWR register.
  * @param  reg      Register to be read.
  * @retval Register value
  */
#define LL_PWR_READ_REG(reg) READ_REG((PWR)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_CONFIGURATION PWR Configuration
  * @{
  */

/**
  * @brief  Set system power mode.
  * @rmtoll
  *  CR1              LPMS          LL_PWR_SetPowerMode
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOP0_MODE
  *         @arg @ref LL_PWR_STOP1_MODE
  *         @arg @ref LL_PWR_STOP2_MODE
  *         @arg @ref LL_PWR_STOP3_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  *         @arg @ref LL_PWR_SHUTDOWN_MODE
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll
  *  CR1              LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOP0_MODE
  *         @arg @ref LL_PWR_STOP1_MODE
  *         @arg @ref LL_PWR_STOP2_MODE
  *         @arg @ref LL_PWR_STOP3_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  *         @arg @ref LL_PWR_SHUTDOWN_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_LPMS));
}

/**
  * @brief  Enable memory content run retention.
  * @rmtoll
  *  CR1          SRAM1PD        LL_PWR_EnableMemoryRunRetention \n
  *  CR1          SRAM2PD        LL_PWR_EnableMemoryRunRetention \n
  *  CR1          SRAM3PD        LL_PWR_EnableMemoryRunRetention \n
  *  CR1          SRAM4PD        LL_PWR_EnableMemoryRunRetention \n
  *  CR1          SRAM5PD        LL_PWR_EnableMemoryRunRetention \n
  *  CR1          SRAM6PD        LL_PWR_EnableMemoryRunRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_RUN_FULL_RETENTION
  *         @arg @ref LL_PWR_SRAM2_RUN_FULL_RETENTION
  * @if (PWR_CR1_SRAM3PD)
  *         @arg @ref LL_PWR_SRAM3_RUN_FULL_RETENTION (*)
  * @endif
  *         @arg @ref LL_PWR_SRAM4_RUN_FULL_RETENTION
  * @if PWR_CR1_SRAM5PD
  *         @arg @ref LL_PWR_SRAM5_RUN_FULL_RETENTION (*)
  * @endif
  * @if PWR_CR1_SRAM6PD
  *         @arg @ref LL_PWR_SRAM6_RUN_FULL_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  **/
__STATIC_INLINE void LL_PWR_EnableMemoryRunRetention(uint32_t memory)
{
  CLEAR_BIT(PWR->CR1, memory);
}

/**
  * @brief  Disable memory content run retention.
  * @rmtoll
  *  CR1          SRAM1PD        LL_PWR_DisableMemoryRunRetention \n
  *  CR1          SRAM2PD        LL_PWR_DisableMemoryRunRetention \n
  *  CR1          SRAM3PD        LL_PWR_DisableMemoryRunRetention \n
  *  CR1          SRAM4PD        LL_PWR_DisableMemoryRunRetention \n
  *  CR1          SRAM5PD        LL_PWR_DisableMemoryRunRetention \n
  *  CR1          SRAM6PD        LL_PWR_DisableMemoryRunRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_RUN_FULL_RETENTION
  *         @arg @ref LL_PWR_SRAM2_RUN_FULL_RETENTION
  * @if (PWR_CR1_SRAM3PD)
  *         @arg @ref LL_PWR_SRAM3_RUN_FULL_RETENTION (*)
  * @endif
  *         @arg @ref LL_PWR_SRAM4_RUN_FULL_RETENTION
  * @if PWR_CR1_SRAM5PD
  *         @arg @ref LL_PWR_SRAM5_RUN_FULL_RETENTION (*)
  * @endif
  * @if PWR_CR1_SRAM6PD
  *         @arg @ref LL_PWR_SRAM6_RUN_FULL_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableMemoryRunRetention(uint32_t memory)
{
  SET_BIT(PWR->CR1, memory);
}

/**
  * @brief  Disable memory content run retention.
  * @rmtoll
  *  CR1          SRAM1PD        LL_PWR_IsEnabledMemoryRunRetention \n
  *  CR1          SRAM2PD        LL_PWR_IsEnabledMemoryRunRetention \n
  *  CR1          SRAM3PD        LL_PWR_IsEnabledMemoryRunRetention \n
  *  CR1          SRAM4PD        LL_PWR_IsEnabledMemoryRunRetention \n
  *  CR1          SRAM5PD        LL_PWR_IsEnabledMemoryRunRetention \n
  *  CR1          SRAM6PD        LL_PWR_IsEnabledMemoryRunRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_RUN_FULL_RETENTION
  *         @arg @ref LL_PWR_SRAM2_RUN_FULL_RETENTION
  * @if (PWR_CR1_SRAM3PD)
  *         @arg @ref LL_PWR_SRAM3_RUN_FULL_RETENTION (*)
  * @endif
  *         @arg @ref LL_PWR_SRAM4_RUN_FULL_RETENTION
  * @if PWR_CR1_SRAM5PD
  *         @arg @ref LL_PWR_SRAM5_RUN_FULL_RETENTION (*)
  * @endif
  * @if PWR_CR1_SRAM6PD
  *         @arg @ref LL_PWR_SRAM6_RUN_FULL_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMemoryRunRetention(uint32_t memory)
{
  return ((READ_BIT(PWR->CR1, memory) == (memory)) ? 0UL : 1UL);
}


/**
  * @brief  Enable memory content standby retention.
  * @rmtoll
  *  CR1              RRSB1          LL_PWR_EnableMemoryStandbyRetention \n
  *  CR1              RRSB2          LL_PWR_EnableMemoryStandbyRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_EnableMemoryStandbyRetention(uint32_t memory)
{
  SET_BIT(PWR->CR1, memory);
}

/**
  * @brief  Disable memory content standby retention.
  * @rmtoll
  *  CR1              RRSB1          LL_PWR_DisableMemoryStandbyRetention \n
  *  CR1              RRSB2          LL_PWR_DisableMemoryStandbyRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_DisableMemoryStandbyRetention(uint32_t memory)
{
  CLEAR_BIT(PWR->CR1, memory);
}

/**
  * @brief  Check if the memory content standby retention.
  * @rmtoll
  *  CR1              RRSB1          LL_PWR_IsEnabledMemoryStandbyRetention \n
  *  CR1              RRSB2          LL_PWR_IsEnabledMemoryStandbyRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE2_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMemoryStandbyRetention(uint32_t memory)
{
  return ((READ_BIT(PWR->CR1, memory) == (memory)) ? 1UL : 0UL);
}

/**
  * @brief  Enable memory content stop retention.
  * @rmtoll
  *  CR2              SRAM1PDSx    (x= 1 to 3)   LL_PWR_EnableMemoryStopRetention \n
  *  CR2              SRAPM2PDSx   (x= 1 to 2)   LL_PWR_EnableMemoryStopRetention \n
  *  CR2              SRAM4PDS                   LL_PWR_EnableMemoryStopRetention \n
  *  CR2              DC2RAMPDS                  LL_PWR_EnableMemoryStopRetention \n
  *  CR2              ICRAMPDS                   LL_PWR_EnableMemoryStopRetention \n
  *  CR2              DC1RAMPDS                  LL_PWR_EnableMemoryStopRetention \n
  *  CR2              DMA2DPDS                   LL_PWR_EnableMemoryStopRetention \n
  *  CR2              PRAMPDS                    LL_PWR_EnableMemoryStopRetention \n
  *  CR2              SRAM3PDSx   (x= 1 to 8)    LL_PWR_EnableMemoryStopRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_1_3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION
  * @if (PWR_CR2_DMA2DRAMPDS)
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_FULL_RETENTION (*)
  * @endif
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_FULL_RETENTION
  * @if PWR_CR2_PKARAMPDS
  *         @arg @ref LL_PWR_PKARAM_STOP_FULL_RETENTION (*)
  * @endif
  * @if (PWR_CR2_SRAM3PDS1)
  *         @arg @ref LL_PWR_SRAM3_STOP_1_8_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableMemoryStopRetention(uint32_t memory)
{
  CLEAR_BIT(PWR->CR2, memory);
}

/**
  * @brief  Disable memory content stop retention.
  * @rmtoll
  *  CR2              SRAM1PDSx    (x= 1 to 3)   LL_PWR_DisableMemoryStopRetention \n
  *  CR2              SRAPM2PDSx   (x= 1 to 2)   LL_PWR_DisableMemoryStopRetention \n
  *  CR2              SRAM4PDS                   LL_PWR_DisableMemoryStopRetention \n
  *  CR2              DC2RAMPDS                  LL_PWR_DisableMemoryStopRetention \n
  *  CR2              ICRAMPDS                   LL_PWR_DisableMemoryStopRetention \n
  *  CR2              DC1RAMPDS                  LL_PWR_DisableMemoryStopRetention \n
  *  CR2              DMA2DPDS                   LL_PWR_DisableMemoryStopRetention \n
  *  CR2              PRAMPDS                    LL_PWR_DisableMemoryStopRetention \n
  *  CR2              SRAM3PDSx   (x= 1 to 8)    LL_PWR_DisableMemoryStopRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_1_3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION
  * @if (PWR_CR2_DMA2DRAMPDS)
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_FULL_RETENTION (*)
  * @endif
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_FULL_RETENTION
  * @if PWR_CR2_PKARAMPDS
  *         @arg @ref LL_PWR_PKARAM_STOP_FULL_RETENTION (*)
  * @endif
  * @if (PWR_CR2_SRAM3PDS1)
  *         @arg @ref LL_PWR_SRAM3_STOP_1_8_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableMemoryStopRetention(uint32_t memory)
{
  SET_BIT(PWR->CR2, memory);
}

/**
  * @brief  Check if memory retention in Stop mode is enabled.
  * @rmtoll
  *  CR2    SRAM6PDSx       LL_PWR_IsEnabledMemoryStopRetention
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION
  * @if (PWR_CR2_DMA2DRAMPDS)
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_FULL_RETENTION (*)
  * @endif
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_FULL_RETENTION
  * @if PWR_CR2_PKARAMPDS
  *         @arg @ref LL_PWR_PKARAM_STOP_FULL_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMemoryStopRetention(uint32_t memory)
{
  return ((READ_BIT(PWR->CR2, memory) == (memory)) ? 0UL : 1UL);
}

/**
  * @brief  Set the SRAM2 page(s) retention in Standby mode.
  * @rmtoll
  *  CR1    RRSB1       LL_PWR_SetSRAM2SBRetention \n
  *  CR1    RRSB2       LL_PWR_SetSRAM2SBRetention
  * @param  SRAM2PageRetention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM2SBRetention(uint32_t SRAM2PageRetention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM2_SB_FULL_RETENTION, SRAM2PageRetention);
}

/**
  * @brief  Get the SRAM2 page(s) retention in Standby mode.
  * @rmtoll
  *  CR1    RRSB1       LL_PWR_GetSRAM2SBRetention \n
  *  CR1    RRSB2       LL_PWR_GetSRAM2SBRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_SB_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_SB_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2SBRetention(void)
{
  return (READ_BIT(PWR->CR1, (PWR_CR1_RRSB1 | PWR_CR1_RRSB2)));
}

/**
  * @brief  Set BOR ultra low power mode.
  * @rmtoll
  *  CR1          UPLMEN        LL_PWR_SetBORStandbyMode
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref  LL_PWR_BOR_CONTINUOUS_MODE
  *         @arg @ref  LL_PWR_BOR_DISCONTINUOUS_MODE
  */
__STATIC_INLINE void LL_PWR_SetBORStandbyMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_ULPMEN, mode);
}

/**
  * @brief  Get BOR ultra low power mode.
  * @rmtoll
  *  CR1          UPLMEN        LL_PWR_GetBORStandbyMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BOR_CONTINUOUS_MODE
  *         @arg @ref LL_PWR_BOR_DISCONTINUOUS_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetBORStandbyMode(void)
{
  return (READ_BIT(PWR->CR1, PWR_CR1_ULPMEN));
}

/**
  * @brief  Enable BOR ultra low power mode.
  * @rmtoll
  *  CR1          UPLMEN        LL_PWR_EnableUltraLowPowerMode
  */
__STATIC_INLINE void LL_PWR_EnableUltraLowPowerMode(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Disable BOR ultra low-power mode.
  * @rmtoll
  *  CR1          UPLMEN        LL_PWR_DisableUltraLowPowerMode
  */
__STATIC_INLINE void LL_PWR_DisableUltraLowPowerMode(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Check if BOR ultra low power mode is enabled.
  * @rmtoll
  *  CR1          UPLMEN        LL_PWR_IsEnabledUltraLowPowerMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUltraLowPowerMode(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_ULPMEN) == (PWR_CR1_ULPMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the SRAM1 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM1PD       LL_PWR_SetSRAM1RunRetention
  * @param  sram1_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_RUN_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM1RunRetention(uint32_t sram1_retention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM1_RUN_FULL_RETENTION, ((~sram1_retention) & LL_PWR_SRAM1_RUN_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM1 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM1PD       LL_PWR_GetSRAM1RunRetention \n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_RUN_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM1RunRetention(void)
{
  return ((~(READ_BIT(PWR->CR1, LL_PWR_SRAM1_RUN_FULL_RETENTION))) & LL_PWR_SRAM1_RUN_FULL_RETENTION);
}

/**
  * @brief  Set the SRAM2 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM2PD       LL_PWR_SetSRAM2RunRetention \n
  * @param  sram2_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_RUN_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM2RunRetention(uint32_t sram2_retention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM2_RUN_FULL_RETENTION, ((~sram2_retention) & LL_PWR_SRAM2_RUN_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM2 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM2PD       LL_PWR_GetSRAM2RunRetention \n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_RUN_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2RunRetention(void)
{
  return ((~(READ_BIT(PWR->CR1, LL_PWR_SRAM2_RUN_FULL_RETENTION))) & LL_PWR_SRAM2_RUN_FULL_RETENTION);
}

#if defined(PWR_CR1_SRAM3PD)
/**
  * @brief  Set the SRAM3 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM3PD       LL_PWR_SetSRAM3RunRetention \n
  * @param  sram3_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_RUN_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM3RunRetention(uint32_t sram3_retention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM3_RUN_FULL_RETENTION, ((~sram3_retention) & LL_PWR_SRAM3_RUN_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM3 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM3PD       LL_PWR_GetSRAM3RunRetention \n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_RUN_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM3RunRetention(void)
{
  return ((~(READ_BIT(PWR->CR1, LL_PWR_SRAM3_RUN_FULL_RETENTION))) & LL_PWR_SRAM3_RUN_FULL_RETENTION);
}
#endif /* defined(PWR_CR1_SRAM3PD) */

/**
  * @brief  Set the SRAM4 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM4PD       LL_PWR_SetSRAM4RunRetention \n
  * @param  sram4_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM4_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM4_RUN_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM4RunRetention(uint32_t sram4_retention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM4_RUN_FULL_RETENTION, ((~sram4_retention) & LL_PWR_SRAM4_RUN_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM4 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM4PD       LL_PWR_GetSRAM4RunRetention \n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM4_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM4_RUN_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM4RunRetention(void)
{
  return ((~(READ_BIT(PWR->CR1, LL_PWR_SRAM4_RUN_FULL_RETENTION))) & LL_PWR_SRAM4_RUN_FULL_RETENTION);
}

#if defined (PWR_CR1_SRAM5PD)
/**
  * @brief  Set the SRAM5 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM5PD       LL_PWR_SetSRAM5RunRetention \n
  * @param  sram5_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM5_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM5_RUN_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM5RunRetention(uint32_t sram5_retention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM5_RUN_FULL_RETENTION, ((~sram5_retention) & LL_PWR_SRAM5_RUN_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM5 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM5PD       LL_PWR_GetSRAM5RunRetention \n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM5_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM5_RUN_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM5RunRetention(void)
{
  return ((~(READ_BIT(PWR->CR1, LL_PWR_SRAM5_RUN_FULL_RETENTION))) & LL_PWR_SRAM5_RUN_FULL_RETENTION);
}
#endif /* defined (PWR_CR1_SRAM5PD) */

#if defined (PWR_CR1_SRAM6PD)
/**
  * @brief  Set the SRAM6 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM6PD       LL_PWR_SetSRAM6RunRetention \n
  * @param  sram6_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM6_RUN_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM6RunRetention(uint32_t sram6_retention)
{
  MODIFY_REG(PWR->CR1, LL_PWR_SRAM6_RUN_FULL_RETENTION, ((~sram6_retention) & LL_PWR_SRAM6_RUN_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM6 retention in Run mode.
  * @rmtoll
  *  CR1    SRAM6PD       LL_PWR_GetSRAM6RunRetention \n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_RUN_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM6_RUN_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM6RunRetention(void)
{
  return ((~(READ_BIT(PWR->CR1, LL_PWR_SRAM6_RUN_FULL_RETENTION))) & LL_PWR_SRAM6_RUN_FULL_RETENTION);
}
#endif /* defined (PWR_CR1_SRAM6PD) */

#if defined (PWR_CR1_FORCE_USBPWR)
/**
  * @brief  Enable OTG_HS PHY power during low power modes (Stop2, Stop 3 and Standby).
  * @rmtoll
  *  CR1          FORCE_USBPWR        LL_PWR_EnableOTGHSPHYLowPowerRetention
  */
__STATIC_INLINE void LL_PWR_EnableOTGHSPHYLowPowerRetention(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_FORCE_USBPWR);
}

/**
  * @brief  Disable OTG_HS PHY power during low power modes (Stop2, Stop 3 and Standby).
  * @rmtoll
  *  CR1          FORCE_USBPWR        LL_PWR_DisableOTGHSPHYLowPowerRetention
  */
__STATIC_INLINE void LL_PWR_DisableOTGHSPHYLowPowerRetention(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_FORCE_USBPWR);
}

/**
  * @brief  Check if OTG_HS PHY power during low power modes (Stop2, Stop 3 and Standby) is enabled.
  * @rmtoll
  *  CR1          FORCE_USBPWR        LL_PWR_IsEnabledOTGHSPHYLowPowerRetention
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledOTGHSPHYLowPowerRetention(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_FORCE_USBPWR) == (PWR_CR1_FORCE_USBPWR)) ? 1UL : 0UL);
}
#endif /* defined (PWR_CR1_FORCE_USBPWR) */

/**
  * @brief  Enable CR2 memory pages retention in Stop mode.
  * @rmtoll
  *  CR2      SRAM1PDSx   (x= 1 to 3)    LL_PWR_DisableMemoryPageStopRetention_CR2 \n
  *  CR2      SRAM2PDSx   (x= 1 to 2)    LL_PWR_DisableMemoryPageStopRetention_CR2 \n
  *  CR2      SRAM3PDSx   (x= 1 to 8)    LL_PWR_DisableMemoryPageStopRetention_CR2
  * @param  ram_page This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_1_3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  * @if (PWR_CR2_SRAM3PDS1)
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_1_8_RETENTION (*)
  * @endif
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  * @if (PWR_CR2_SRAM3PDS1)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE6_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE7_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE8_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableMemoryPageStopRetention_CR2(uint32_t ram_page)
{
  CLEAR_BIT(PWR->CR2, ram_page);
}

/**
  * @brief  Disable CR2 memory pages retention in Stop mode.
  * @rmtoll
  *  CR2      SRAM1PDSx   (x= 1 to 3)    LL_PWR_DisableMemoryPageStopRetention_CR2 \n
  *  CR2      SRAM2PDSx   (x= 1 to 2)    LL_PWR_DisableMemoryPageStopRetention_CR2 \n
  *  CR2      SRAM3PDSx   (x= 1 to 8)    LL_PWR_DisableMemoryPageStopRetention_CR2
  * @param  ram_page This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_1_3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  * @if (PWR_CR2_SRAM3PDS1)
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_1_8_RETENTION (*)
  * @endif
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  * @if (PWR_CR2_SRAM3PDS1)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE6_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE7_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE8_RETENTION (*)
  * @endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableMemoryPageStopRetention_CR2(uint32_t ram_page)
{
  SET_BIT(PWR->CR2, ram_page);
}

#if defined(PWR_CR4_SRAM1PDS4)
/**
  * @brief  Enable CR4 memory page(s) retention in Stop mode.
  * @rmtoll
  *  CR4    SRAM1PDSx (x= 4 to 12)      LL_PWR_EnableMemoryPageStopRetention_CR4 \n
  *  CR4    SRAM3PDSx (x= 9 to 13)      LL_PWR_EnableMemoryPageStopRetention_CR4 \n
  *  CR4    SRAM5PDSx (x= 1 to 13)      LL_PWR_EnableMemoryPageStopRetention_CR4
  * @param  ram_page This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_4_12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_9_13_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_NO_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_FULL_RETENTION (*)
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE9_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE10_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE11_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE12_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE13_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE1_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE2_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE3_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE4_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE5_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE6_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE7_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE8_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE9_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE10_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE11_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE12_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE13_RETENTION (*)
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableMemoryPageStopRetention_CR4(uint32_t ram_page)
{
  CLEAR_BIT(PWR->CR4, ram_page);
}

/**
  * @brief  Disable the CR4 SRAMx page(s) retention in Stop mode.
  * @rmtoll
  *  CR4    SRAM1PDSx (x= 4 to 12)      LL_PWR_EnableMemoryPageStopRetention_CR4 \n
  *  CR4    SRAM3PDSx (x= 9 to 13)      LL_PWR_EnableMemoryPageStopRetention_CR4 \n
  *  CR4    SRAM5PDSx (x= 1 to 13)      LL_PWR_EnableMemoryPageStopRetention_CR4
  * @param  ram_page This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_4_12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_9_13_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_NO_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_FULL_RETENTION (*)
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE9_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE10_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE11_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE12_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE13_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE1_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE2_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE3_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE4_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE5_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE6_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE7_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE8_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE9_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE10_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE11_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE12_RETENTION (*)
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE13_RETENTION (*)
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableMemoryPageStopRetention_CR4(uint32_t ram_page)
{
  SET_BIT(PWR->CR4, ram_page);
}
#endif /* defined(PWR_CR4_SRAM1PDS4) */

#if defined(PWR_CR5_SRAM6PDS1)

/**
  * @brief  Enable CR5 memory page(s) retention in Stop mode.
  * @rmtoll
  *  CR5    SRAM6PDSx   (x= 1 to 8)       LL_PWR_EnableMemoryPageStopRetention_CR5
  * @param  ram_page This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_FULL_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE8_RETENTION
  */
__STATIC_INLINE void LL_PWR_EnableMemoryPageStopRetention_CR5(uint32_t ram_page)
{
  CLEAR_BIT(PWR->CR5, ram_page);
}

/**
  * @brief  Disable the CR5 SRAMx page(s) retention in Stop mode.
  * @rmtoll
  *  CR5    SRAM6PDSx   (x= 1 to 8)       LL_PWR_DisableMemoryPageStopRetention_CR5
  * @param  ram_page This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_FULL_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE8_RETENTION
  */
__STATIC_INLINE void LL_PWR_DisableMemoryPageStopRetention_CR5(uint32_t ram_page)
{
  SET_BIT(PWR->CR5, ram_page);
}
#endif /* defined(PWR_CR5_SRAM6PDS1) */

/**
  * @brief  Set the SRAM1 page(s) (From page 1 to page 3) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM1PDS1       LL_PWR_SetSRAM1StopRetention_1_3 \n
  *  CR2    SRAM1PDS2       LL_PWR_SetSRAM1StopRetention_1_3 \n
  *  CR2    SRAM1PDS3       LL_PWR_SetSRAM1StopRetention_1_3
  * @param  sram1_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_1_3_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM1StopRetention_1_3(uint32_t sram1_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM1_STOP_1_3_RETENTION, ((~sram1_page_retention) & LL_PWR_SRAM1_STOP_1_3_RETENTION));
}

/**
  * @brief  Get the SRAM1 page(s) (From page 1 to page 3) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM1PDS1       LL_PWR_GetSRAM1StopRetention_1_3 \n
  *  CR2    SRAM1PDS2       LL_PWR_GetSRAM1StopRetention_1_3 \n
  *  CR2    SRAM1PDS3       LL_PWR_GetSRAM1StopRetention_1_3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_1_3_RETENTION
  *         Or a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM1StopRetention_1_3(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM1_STOP_1_3_RETENTION))) & LL_PWR_SRAM1_STOP_1_3_RETENTION);
}

/**
  * @brief  Check if SRAM1 retention (From page 4 to page 12) in Stop mode is enabled.
  * @rmtoll
  *  CR2    SRAM1PDSx x = [1..3]      LL_PWR_IsEnabledSRAM1StopRetention_1_3
  * @param  sram1_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE3_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM1StopRetention_1_3(uint32_t sram1_page_retention)
{
  return ((READ_BIT(PWR->CR2, sram1_page_retention) == (sram1_page_retention)) ? 0UL : 1UL);
}

#if defined (PWR_CR4_SRAM1PDS4)
/**
  * @brief  Set the SRAM1 page(s) (From page 4 to page 12) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM1PDS4       LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS5       LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS6       LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS7       LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS8       LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS9       LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS10      LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS11      LL_PWR_SetSRAM1StopRetention_4_12 \n
  *  CR2    SRAM1PDS12      LL_PWR_SetSRAM1StopRetention_4_12
  * @param  sram1_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_4_12_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE12_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM1StopRetention_4_12(uint32_t sram1_page_retention)
{
  MODIFY_REG(PWR->CR4, LL_PWR_SRAM1_STOP_4_12_RETENTION, ((~sram1_page_retention) & LL_PWR_SRAM1_STOP_4_12_RETENTION));
}

/**
  * @brief  Get the SRAM1 page(s) (From page 4 to page 12) retention in Stop mode.
  * @rmtoll
  *  CR4    SRAM1PDS4       LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS5       LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS6       LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS7       LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS8       LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS9       LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS10      LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS11      LL_PWR_GetSRAM1StopRetention_4_12 \n
  *  CR4    SRAM1PDS12      LL_PWR_GetSRAM1StopRetention_4_12
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_4_12_RETENTION
  *         Or a combination of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE12_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM1StopRetention_4_12(void)
{
  return ((~(READ_BIT(PWR->CR4, LL_PWR_SRAM1_STOP_4_12_RETENTION))) & LL_PWR_SRAM1_STOP_4_12_RETENTION);
}

/**
  * @brief  Check if SRAM1 retention (From page 4 to page 12) in Stop mode is enabled.
  * @rmtoll
  *  CR4    SRAM1PDSx x = [4..12]      LL_PWR_IsEnabledSRAM1StopRetention_4_12
  * @param  sram1_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM1_STOP_PAGE12_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM1StopRetention_4_12(uint32_t sram1_page_retention)
{
  return ((READ_BIT(PWR->CR4, sram1_page_retention) == (sram1_page_retention)) ? 0UL : 1UL);
}
#endif /* defined (PWR_CR4_SRAM1PDS4) */

/**
  * @brief  Set the SRAM2 page(s) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM2PDS1       LL_PWR_SetSRAM2StopRetention \n
  *  CR2    SRAM2PDS2       LL_PWR_SetSRAM2StopRetention
  * @param  sram2_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM2StopRetention(uint32_t sram2_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM2_STOP_FULL_RETENTION, ((~sram2_page_retention) & LL_PWR_SRAM2_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM2 page(s) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM2PDS1       LL_PWR_GetSRAM2StopRetention \n
  *  CR2    SRAM2PDS2       LL_PWR_GetSRAM2StopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM2StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM2_STOP_FULL_RETENTION))) & LL_PWR_SRAM2_STOP_FULL_RETENTION);
}

/**
  * @brief  Get the SRAM2 page(s) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM2PDS1       LL_PWR_GetSRAM2StopRetention \n
  *  CR2    SRAM2PDS2       LL_PWR_GetSRAM2StopRetention
  * @param  sram2_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_PAGE2_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM2StopRetention(uint32_t sram2_page_retention)
{
  return ((READ_BIT(PWR->CR2, sram2_page_retention) == (sram2_page_retention)) ? 0UL : 1UL);
}

#if defined(PWR_CR2_SRAM3PDS1)
/**
  * @brief  Set the SRAM3 page(s) (From page 1 to page 8) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM3PDS1       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS2       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS3       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS4       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS5       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS6       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS7       LL_PWR_SetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS8       LL_PWR_SetSRAM3StopRetention_1_8
  * @param  sram3_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_1_8_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE8_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM3StopRetention_1_8(uint32_t sram3_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM3_STOP_1_8_RETENTION, ((~sram3_page_retention) & LL_PWR_SRAM3_STOP_1_8_RETENTION));
}

/**
  * @brief  Get the SRAM3 page(s) (From page 1 to page 8) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM3PDS1       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS2       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS3       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS4       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS5       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS6       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS7       LL_PWR_GetSRAM3StopRetention_1_8 \n
  *  CR2    SRAM3PDS8       LL_PWR_GetSRAM3StopRetention_1_8
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_1_8_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE8_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM3StopRetention_1_8(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM3_STOP_1_8_RETENTION))) & LL_PWR_SRAM3_STOP_1_8_RETENTION);
}

/**
  * @brief  Check if SRAM3 retention (From page 1 to page 8) in Stop mode is enabled.
  * @rmtoll
  *  CR2    SRAM3PDSx x = [1..8]      LL_PWR_IsEnabledSRAM3StopRetention_1_8
  * @param  sram3_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE8_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM3StopRetention_1_8(uint32_t sram3_page_retention)
{
  return ((READ_BIT(PWR->CR2, sram3_page_retention) == (sram3_page_retention)) ? 0UL : 1UL);
}

#endif /* defined(PWR_CR2_SRAM3PDS1) */

#if defined (PWR_CR4_SRAM3PDS9)
/**
  * @brief  Set the SRAM3 page(s) (From page 9 to page 13) retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM3PDS9       LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR2    SRAM3PDS10      LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR2    SRAM3PDS11      LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR2    SRAM3PDS12      LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR2    SRAM3PDS13      LL_PWR_SetSRAM3StopRetention_9_13
  * @param  sram3_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_9_13_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE13_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM3StopRetention_9_13(uint32_t sram3_page_retention)
{
  MODIFY_REG(PWR->CR4, LL_PWR_SRAM3_STOP_9_13_RETENTION, ((~sram3_page_retention) & LL_PWR_SRAM3_STOP_9_13_RETENTION));
}

/**
  * @brief  Get the SRAM3 page(s) (From page 9 to page 13) retention in Stop mode.
  * @rmtoll
  *  CR4    SRAM3PDS9       LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR4    SRAM3PDS10      LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR4    SRAM3PDS11      LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR4    SRAM3PDS12      LL_PWR_SetSRAM3StopRetention_9_13 \n
  *  CR4    SRAM3PDS13      LL_PWR_SetSRAM3StopRetention_9_13
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_9_13_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE13_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM3StopRetention_9_13(void)
{
  return ((~(READ_BIT(PWR->CR4, LL_PWR_SRAM3_STOP_9_13_RETENTION))) & LL_PWR_SRAM3_STOP_9_13_RETENTION);
}

/**
  * @brief  Check if SRAM3 retention (From page 9 to page 13) in Stop mode is enabled.
  * @rmtoll
  *  CR4    SRAM3PDSx  x = [9..13]       LL_PWR_IsEnabledSRAM3StopRetention
  * @param  sram3_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM3_STOP_PAGE13_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM3StopRetention_9_13(uint32_t sram3_page_retention)
{
  return ((READ_BIT(PWR->CR4, sram3_page_retention) == (sram3_page_retention)) ? 0UL : 1UL);
}
#endif /* defined (PWR_CR4_SRAM3PDS9) */

/**
  * @brief  Set the SRAM4 page retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM4PDS       LL_PWR_SetSRAM4StopRetention
  * @param  sram4_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM4_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM4StopRetention(uint32_t sram4_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_SRAM4_STOP_FULL_RETENTION, ((~sram4_page_retention) & LL_PWR_SRAM4_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM4 page retention in Stop mode.
  * @rmtoll
  *  CR2    SRAM4PDS       LL_PWR_GetSRAM4StopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM4_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM4_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM4StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_SRAM4_STOP_FULL_RETENTION))) & LL_PWR_SRAM4_STOP_FULL_RETENTION);
}

#if defined (PWR_CR4_SRAM5PDS1)
/**
  * @brief  Set the SRAM5 page(s) retention in Stop mode.
  * @rmtoll
  *  CR4    SRAM5PDS1       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS2       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS3       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS4       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS5       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS6       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS7       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS8       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS9       LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS10      LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS11      LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS12      LL_PWR_SetSRAM5StopRetention \n
  *  CR4    SRAM5PDS13      LL_PWR_SetSRAM5StopRetention
  * @param  sram5_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM5_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_FULL_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE13_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM5StopRetention(uint32_t sram5_page_retention)
{
  MODIFY_REG(PWR->CR4, LL_PWR_SRAM5_STOP_FULL_RETENTION, ((~sram5_page_retention) & LL_PWR_SRAM5_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the SRAM5 page(s) retention in Stop mode.
  * @rmtoll
  *  CR4    SRAM5PDS1       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS2       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS3       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS4       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS5       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS6       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS7       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS8       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS9       LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS10      LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS11      LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS12      LL_PWR_GetSRAM5StopRetention \n
  *  CR4    SRAM5PDS13      LL_PWR_GetSRAM5StopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM5_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_FULL_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE13_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM5StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR4, LL_PWR_SRAM5_STOP_FULL_RETENTION))) & LL_PWR_SRAM5_STOP_FULL_RETENTION);
}

/**
  * @brief  Check if SRAM5 retention in Stop mode is enabled.
  * @rmtoll
  *  CR4    SRAM5PDSx x =[1..13]       LL_PWR_IsEnabledSRAM6StopRetention
  * @param  sram5_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE8_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE9_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE10_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE11_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE12_RETENTION
  *         @arg @ref LL_PWR_SRAM5_STOP_PAGE13_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM5StopRetention(uint32_t sram5_page_retention)
{
  return ((READ_BIT(PWR->CR4, sram5_page_retention) == (sram5_page_retention)) ? 0UL : 1UL);
}


#endif /* defined (PWR_CR4_SRAM5PDS1) */

#if defined(PWR_CR5_SRAM6PDS1)
/**
  * @brief  Set the SRAM6 page(s) retention in Stop mode.
  * @rmtoll
  *  CR5    SRAM6PDS1       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS2       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS3       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS4       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS5       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS6       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS7       LL_PWR_SetSRAM6StopRetention \n
  *  CR5    SRAM6PDS8       LL_PWR_SetSRAM6StopRetention
  * @param  sram6_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_FULL_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE8_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetSRAM6StopRetention(uint32_t sram6_page_retention)
{
  MODIFY_REG(PWR->CR5, LL_PWR_SRAM6_STOP_FULL_RETENTION, ((~sram6_page_retention) & LL_PWR_SRAM6_STOP_FULL_RETENTION));
}

/**
  * @brief  Check if SRAM6 retention in Stop mode is enabled.
  * @rmtoll
  *  CR5    SRAM6PDSx x = [1..8]      LL_PWR_IsEnabledSRAM6StopRetention
  * @param  sram6_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE8_RETENTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM6StopRetention(uint32_t sram6_page_retention)
{
  return ((READ_BIT(PWR->CR5, sram6_page_retention) == (sram6_page_retention)) ? 0UL : 1UL);
}

/**
  * @brief  Get the SRAM6 page(s) retention in Stop mode.
  * @rmtoll
  *  CR5    SRAM6PDS1       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS2       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS3       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS4       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS5       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS6       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS7       LL_PWR_GetSRAM6StopRetention \n
  *  CR5    SRAM6PDS8       LL_PWR_GetSRAM6StopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_FULL_RETENTION
  *                      Or can be a combination of the following values:
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE1_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE2_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE3_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE4_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE5_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE6_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE7_RETENTION
  *         @arg @ref LL_PWR_SRAM6_STOP_PAGE8_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAM6StopRetention(void)
{
  return ((~(READ_BIT(PWR->CR5, LL_PWR_SRAM6_STOP_FULL_RETENTION))) & LL_PWR_SRAM6_STOP_FULL_RETENTION);
}
#endif /* defined (PWR_CR5_SRAM6PDS1) */

/**
  * @brief  Set the ICACHE SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    ICRAMPDS       LL_PWR_SetICacheRAMStopRetention
  * @param  icache_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ICACHERAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetICacheRAMStopRetention(uint32_t icache_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_ICACHERAM_STOP_FULL_RETENTION,
             ((~icache_page_retention) & LL_PWR_ICACHERAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the ICACHE SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    ICRAMPDS       LL_PWR_GetICacheRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ICACHERAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_ICACHERAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetICacheRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_ICACHERAM_STOP_FULL_RETENTION))) & LL_PWR_ICACHERAM_STOP_FULL_RETENTION);
}

/**
  * @brief  Set the DCACHE1 SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DC1RAMPDS       LL_PWR_SetDCache1RAMStopRetention
  * @param  dcache1_page_retention : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetDCache1RAMStopRetention(uint32_t dcache1_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION,
             ((~dcache1_page_retention) & LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the DCACHE1 SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DC1RAMPDS       LL_PWR_GetDCache1RAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetDCache1RAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION))) & LL_PWR_DCACHE1RAM_STOP_FULL_RETENTION);
}

#if defined (PWR_CR2_DC2RAMPDS)
/**
  * @brief  Set the DCACHE2 SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DC2RAMPDS       LL_PWR_SetDCache2RAMStopRetention
  * @param  dcache2_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DCACHE2RAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetDCache2RAMStopRetention(uint32_t dcache2_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION,
             ((~dcache2_page_retention) & LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the DCACHE2 SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DC2RAMPDS       LL_PWR_GetDCache2RAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_DCACHE2RAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetDCache2RAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION))) & LL_PWR_DCACHE2RAM_STOP_FULL_RETENTION);
}
#endif /* defined (PWR_CR2_DC2RAMPDS) */

#if defined(PWR_CR2_DMA2DRAMPDS)
/**
  * @brief  Set the DMA2D SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DMA2DRAMPDS       LL_PWR_SetDMA2DRAMStopRetention
  * @param  dma2dram_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetDMA2DRAMStopRetention(uint32_t dma2dram_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_DMA2DRAM_STOP_FULL_RETENTION,
             ((~dma2dram_page_retention) & LL_PWR_DMA2DRAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the DMA2D SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DMA2DRAMPDS       LL_PWR_GetDMA2DRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DMA2DRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetDMA2DRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_DMA2DRAM_STOP_FULL_RETENTION))) & LL_PWR_DMA2DRAM_STOP_FULL_RETENTION);
}
#endif /* PWR_CR2_DMA2DRAMPDS */

/**
  * @brief  Set the FMAC, FDCAN and USB SRAMs pages retention in Stop mode.
  * @rmtoll
  *  CR2    PRAMPDS       LL_PWR_SetPeriphRAMStopRetention
  * @param  priph_ram_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetPeriphRAMStopRetention(uint32_t priph_ram_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_PERIPHRAM_STOP_FULL_RETENTION,
             ((~priph_ram_page_retention) & LL_PWR_PERIPHRAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the FMAC, FDCAN and USB SRAMs pages retention in Stop mode.
  * @rmtoll
  *  CR2    PRAMPDS       LL_PWR_GetPeriphRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_PERIPHRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetPeriphRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_PERIPHRAM_STOP_FULL_RETENTION))) & LL_PWR_PERIPHRAM_STOP_FULL_RETENTION);
}

#if defined(PWR_CR2_PKARAMPDS)
/**
  * @brief  Set the PKA32 SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    PKARAMPDS       LL_PWR_SetPKARAMStopRetention
  * @param  pkaram_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PKARAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_PKARAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetPKARAMStopRetention(uint32_t pkaram_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_PKARAM_STOP_FULL_RETENTION,
             ((~pkaram_page_retention) & LL_PWR_PKARAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the PKA32 SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    PKARAMPDS       LL_PWR_GetPKARAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PKARAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_PKARAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetPKARAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_PKARAM_STOP_FULL_RETENTION))) & LL_PWR_PKARAM_STOP_FULL_RETENTION);
}
#endif /* defined(PWR_CR2_PKARAMPDS) */

#if defined (PWR_CR2_GPRAMPDS)
/**
  * @brief  Set the Graphic peripherals (LTDC, GFXMMU) SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    GPRAMPDS       LL_PWR_SetGraphicPeriphRAMStopRetention
  * @param  graphic_periph_ram_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GRAPHICPERIPHRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetGraphicPeriphRAMStopRetention(uint32_t graphic_periph_ram_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION,
             ((~graphic_periph_ram_page_retention) & LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the Graphic peripherals (LTDC, GFXMMU) SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    GPRAMPDS       LL_PWR_GetGraphicPeriphRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_GRAPHICPERIPHRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetGraphicPeriphRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION))) &
          LL_PWR_GRAPHICPERIPHRAM_STOP_FULL_RETENTION);
}
#endif /* defined (PWR_CR2_GPRAMPDS) */

#if defined (PWR_CR2_DSIRAMPDS)
/**
  * @brief  Set the DSI SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DSIRAMPDS       LL_PWR_SetDSIRAMStopRetention
  * @param  dsiram_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DSIRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DSIRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetDSIRAMStopRetention(uint32_t dsiram_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_DSIRAM_STOP_FULL_RETENTION,
             ((~dsiram_page_retention) & LL_PWR_DSIRAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the DSI SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    DSIRAMPDS       LL_PWR_GetDSIRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_DSIRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_DSIRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetDSIRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_DSIRAM_STOP_FULL_RETENTION))) & LL_PWR_DSIRAM_STOP_FULL_RETENTION);
}
#endif /* defined (PWR_CR2_DSIRAMPDS) */

#if defined (PWR_CR2_JPEGRAMPDS)
/**
  * @brief  Set the JPEG SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    JPEGRAMPDS       LL_PWR_SetJPEGRAMStopRetention
  * @param  jpegram_page_retention This parameter can be one of the following values:
  *         @arg @ref LL_PWR_JPEGRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_JPEGRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE void LL_PWR_SetJPEGRAMStopRetention(uint32_t jpegram_page_retention)
{
  MODIFY_REG(PWR->CR2, LL_PWR_JPEGRAM_STOP_FULL_RETENTION,
             ((~jpegram_page_retention) & LL_PWR_JPEGRAM_STOP_FULL_RETENTION));
}

/**
  * @brief  Get the JPEG SRAM page retention in Stop mode.
  * @rmtoll
  *  CR2    JPEGRAMPDS       LL_PWR_GetJPEGRAMStopRetention
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_JPEGRAM_STOP_NO_RETENTION
  *         @arg @ref LL_PWR_JPEGRAM_STOP_FULL_RETENTION
  */
__STATIC_INLINE uint32_t LL_PWR_GetJPEGRAMStopRetention(void)
{
  return ((~(READ_BIT(PWR->CR2, LL_PWR_JPEGRAM_STOP_FULL_RETENTION))) & LL_PWR_JPEGRAM_STOP_FULL_RETENTION);
}
#endif /* defined (PWR_CR2_JPEGRAMPDS) */

/**
  * @brief Enable the flash and SRAM4 memories fast wakeup from Stop mode.
  * @rmtoll
  *  CR2    FLASHFWU       LL_PWR_EnableFastWakeup \n
  *  CR2    SRAM4FWU       LL_PWR_EnableFastWakeup
  * @param items This parameter can be one or a combination of the following values:
  *        @arg @ref LL_PWR_FLASHFWU
  *        @arg @ref LL_PWR_SRAM4FWU
  *        @arg @ref LL_PWR_MEMORIESFWU
  */
__STATIC_INLINE void LL_PWR_EnableFastWakeup(uint32_t items)
{
  SET_BIT(PWR->CR2, items);
}

/**
  * @brief Disable the flash and SRAM4 memories fast wakeup from Stop mode.
  * @rmtoll
  *  CR2    FLASHFWU       LL_PWR_DisableFastWakeup \n
  *  CR2    SRAM4FWU       LL_PWR_DisableFastWakeup
  * @param items This parameter can be one or a combination of the following values:
  *        @arg @ref LL_PWR_FLASHFWU
  *        @arg @ref LL_PWR_SRAM4FWU
  *        @arg @ref LL_PWR_MEMORIESFWU
  */
__STATIC_INLINE void LL_PWR_DisableFastWakeup(uint32_t items)
{
  CLEAR_BIT(PWR->CR2, items);
}

/**
  * @brief Check the flash and SRAM4 memories fast wakeup from Stop mode is enabled.
  * @rmtoll
  *  CR2    FLASHFWU       LL_PWR_IsEnabledFastWakeup \n
  *  CR2    SRAM4FWU       LL_PWR_IsEnabledFastWakeup
  * @param items This parameter can be one of the following values:
  *        @arg @ref LL_PWR_FLASHFWU
  *        @arg @ref LL_PWR_SRAM4FWU
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFastWakeup(uint32_t items)
{
  return ((READ_BIT(PWR->CR2, items) == (items)) ? 1UL : 0UL);
}
/**
  * @brief  Enable the flash memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll
  *  CR2    FLASHFWU       LL_PWR_EnableFlashFastWakeUp
  */
__STATIC_INLINE void LL_PWR_EnableFlashFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Disable the flash memory fast wakeup from Stop mode (Stop 0, 1).
  * @rmtoll
  *  CR2    FLASHFWU       LL_PWR_DisableFlashFastWakeUp
  */
__STATIC_INLINE void LL_PWR_DisableFlashFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Check if the flash memory fast wakeup from Stop mode (Stop 0, 1)
  *         is enabled.
  * @rmtoll
  *  CR2    FLASHFWU       LL_PWR_IsEnabledFlashFastWakeUp
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashFastWakeUp(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_FLASHFWU) == (PWR_CR2_FLASHFWU)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the SRAM4 memory fast wakeup from Stop mode (Stop 0, 1, 2).
  * @rmtoll
  *  CR2    SRAM4FWU       LL_PWR_EnableSRAM4FastWakeUp
  */
__STATIC_INLINE void LL_PWR_EnableSRAM4FastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_SRAM4FWU);
}

/**
  * @brief  Disable the SRAM4 memory fast wakeup from Stop mode (Stop 0, 1, 2).
  * @rmtoll
  *  CR2    SRAM4FWU       LL_PWR_DisableSRAM4FastWakeUp
  */
__STATIC_INLINE void LL_PWR_DisableSRAM4FastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_SRAM4FWU);
}

/**
  * @brief  Check if the SRAM4 memory fast wakeup from Stop mode (Stop 0, 1, 2).
  *         is enabled.
  * @rmtoll
  *  CR2    SRAM4FWU       LL_PWR_IsEnabledSRAM4FastWakeUp
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM4FastWakeUp(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_SRAM4FWU) == (PWR_CR2_SRAM4FWU)) ? 1UL : 0UL);
}

/**
  * @brief  Set the smart run domain mode.
  * @rmtoll
  *  CR2    SRDRUN       LL_PWR_SetSmartRunDomainMode
  * @param  srd_mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRD_RUN_MODE
  *         @arg @ref LL_PWR_SRD_STOP_MODE
  */
__STATIC_INLINE void LL_PWR_SetSmartRunDomainMode(uint32_t srd_mode)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_SRDRUN, srd_mode);
}

/**
  * @brief  Get the smart run domain mode.
  * @rmtoll
  *  CR2    SRDRUN       LL_PWR_GetSmartRunDomainMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRD_RUN_MODE
  *         @arg @ref LL_PWR_SRD_STOP_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetSmartRunDomainMode(void)
{
  return (READ_BIT(PWR->CR2, PWR_CR2_SRDRUN));
}

/**
  * @brief  Set the VCore regulator supply.
  * @rmtoll
  *  CR3    REGSEL       LL_PWR_SetRegulatorSupply
  * @param  regulator_supply This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MAIN_REGU_LDO_SUPPLY
  *         @arg @ref LL_PWR_MAIN_REGU_SMPS_SUPPLY
  */
__STATIC_INLINE void LL_PWR_SetRegulatorSupply(uint32_t regulator_supply)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_REGSEL, regulator_supply);
}

/**
  * @brief  Get the VCore regulator supply.
  * @rmtoll
  *  CR3    REGSEL       LL_PWR_GetRegulatorSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MAIN_REGU_LDO_SUPPLY
  *         @arg @ref LL_PWR_MAIN_REGU_SMPS_SUPPLY
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulatorSupply(void)
{
  return (READ_BIT(PWR->CR3, PWR_CR3_REGSEL));
}

/**
  * @brief  Set the main regulator fast startup mode.
  * @rmtoll
  *  CR3    FSTEN       LL_PWR_SetMainRegulatorStartupMode
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MAIN_REGU_SLOW_STARTUP
  *         @arg @ref LL_PWR_MAIN_REGU_FAST_STARTUP
  */
__STATIC_INLINE void LL_PWR_SetMainRegulatorStartupMode(uint32_t mode)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_FSTEN, mode);
}

/**
  * @brief  Get the main regulator fast startup mode.
  * @rmtoll
  *  CR3    FSTEN       LL_PWR_GetMainRegulatorStartupMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MAIN_REGU_SLOW_STARTUP
  *         @arg @ref LL_PWR_MAIN_REGU_FAST_STARTUP
  */
__STATIC_INLINE uint32_t LL_PWR_GetMainRegulatorStartupMode(void)
{
  return (READ_BIT(PWR->CR3, PWR_CR3_FSTEN));
}

/**
  * @brief  Enable the fast soft start for selected regulator.
  * @rmtoll
  *  CR3    FSTEN       LL_PWR_EnableFastSoftStart
  */
__STATIC_INLINE void LL_PWR_EnableFastSoftStart(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Disable the fast soft start for selected regulator.
  * @rmtoll
  *  CR3    FSTEN       LL_PWR_DisableFastSoftStart
  */
__STATIC_INLINE void LL_PWR_DisableFastSoftStart(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Check if the fast soft start for selected regulator is enabled.
  * @rmtoll
  *  CR3    FSTEN       LL_PWR_IsEnabledFastSoftStart
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFastSoftStart(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_FSTEN) == (PWR_CR3_FSTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the regulator supply output voltage.
  * @rmtoll
  *  VOSR          VOS           LL_PWR_SetRegulVoltageScaling
  * @param  voltage_scaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_3
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_4
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t voltage_scaling)
{
  MODIFY_REG(PWR->VOSR, PWR_VOSR_VOS, voltage_scaling);
}

/**
  * @brief  Get the regulator supply output voltage.
  * @rmtoll
  *  VOSR          VOS           LL_PWR_GetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_3
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_4
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->VOSR, PWR_VOSR_VOS));
}

/**
  * @brief  Enable the EPOD (Embedded Power Distribution) booster.
  * @rmtoll
  *  VOSR    BOOSTEN       LL_PWR_EnableEPODBooster
  */
__STATIC_INLINE void LL_PWR_EnableEPODBooster(void)
{
  SET_BIT(PWR->VOSR, PWR_VOSR_BOOSTEN);
}

/**
  * @brief  Disable the EPOD (Embedded Power Distribution) booster.
  * @rmtoll
  *  VOSR    BOOSTEN       LL_PWR_DisableEPODBooster
  */
__STATIC_INLINE void LL_PWR_DisableEPODBooster(void)
{
  CLEAR_BIT(PWR->VOSR, PWR_VOSR_BOOSTEN);
}

/**
  * @brief  Check if  the EPOD (Embedded Power Distribution) booster is enabled.
  * @rmtoll
  *  VOSR    BOOSTEN       LL_PWR_IsEnabledEPODBooster
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledEPODBooster(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTEN) == (PWR_VOSR_BOOSTEN)) ? 1UL : 0UL);
}

#if defined (PWR_VOSR_USBPWREN)
/**
  * @brief  Enable the USB power supply.
  * @rmtoll
  *  VOSR    USBPWREN       LL_PWR_EnableUSBPowerSupply
  */
__STATIC_INLINE void LL_PWR_EnableUSBPowerSupply(void)
{
  SET_BIT(PWR->VOSR, PWR_VOSR_USBPWREN);
}

/**
  * @brief  Disable the USB power supply.
  * @rmtoll
  *  VOSR    USBPWREN       LL_PWR_DisableUSBPowerSupply
  */
__STATIC_INLINE void LL_PWR_DisableUSBPowerSupply(void)
{
  CLEAR_BIT(PWR->VOSR, PWR_VOSR_USBPWREN);
}

/**
  * @brief  Check if the USB power supply is enabled.
  * @rmtoll
  *  VOSR    USBPWREN       LL_PWR_IsEnabledUSBPowerSupply
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBPowerSupply(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_USBPWREN) == (PWR_VOSR_USBPWREN)) ? 1UL : 0UL);
}
#endif /* defined (PWR_VOSR_USBPWREN) */

#if defined (PWR_VOSR_USBBOOSTEN)
/**
  * @brief  Enable the USB EPOD (Embedded Power Distribution) booster.
  * @rmtoll
  *  VOSR    USBBOOSTEN       LL_PWR_EnableUSBEPODBooster
  */
__STATIC_INLINE void LL_PWR_EnableUSBEPODBooster(void)
{
  SET_BIT(PWR->VOSR, PWR_VOSR_USBBOOSTEN);
}

/**
  * @brief  Disable the USB EPOD (Embedded Power Distribution) booster.
  * @rmtoll
  *  VOSR    USBBOOSTEN       LL_PWR_DisableUSBEPODBooster
  */
__STATIC_INLINE void LL_PWR_DisableUSBEPODBooster(void)
{
  CLEAR_BIT(PWR->VOSR, PWR_VOSR_USBBOOSTEN);
}

/**
  * @brief  Check if the USB EPOD (Embedded Power Distribution) booster is enabled.
  * @rmtoll
  *  VOSR    USBBOOSTEN       LL_PWR_IsEnabledUSBEPODBooster
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBEPODBooster(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_USBBOOSTEN) == (PWR_VOSR_USBBOOSTEN)) ? 1UL : 0UL);
}
#endif /* defined (PWR_VOSR_USBBOOSTEN) */

#if defined (PWR_VOSR_VDD11USBDIS)
/**
  * @brief  Enable the Vdd11USB.
  * @rmtoll
  *  VOSR    VDD11USBDIS       LL_PWR_EnableVdd11USB
  */
__STATIC_INLINE void LL_PWR_EnableVdd11USB(void)
{
  CLEAR_BIT(PWR->VOSR, PWR_VOSR_VDD11USBDIS);
}

/**
  * @brief  Disable the Vdd11USB.
  * @rmtoll
  *  VOSR    VDD11USBDIS       LL_PWR_DisableVdd11USB
  */
__STATIC_INLINE void LL_PWR_DisableVdd11USB(void)
{
  SET_BIT(PWR->VOSR, PWR_VOSR_VDD11USBDIS);
}

/**
  * @brief  Check if the Vdd11USB is enabled.
  * @rmtoll
  *  VOSR    VDD11USBDIS       LL_PWR_IsEnabledVdd11USB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVdd11USB(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_VDD11USBDIS) == (0U)) ? 1UL : 0UL);
}
#endif /* defined (PWR_VOSR_VDD11USBDIS) */

/**
  * @brief  Set the Programmable voltage detector level.
  * @rmtoll
  *  SVMCR    PVDLS         LL_PWR_SetPVDLevel
  * @param  pvd_level This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t pvd_level)
{
  MODIFY_REG(PWR->SVMCR, PWR_SVMCR_PVDLS, pvd_level);
}

/**
  * @brief  Get the Programmable voltage detector level.
  * @rmtoll
  *  SVMCR    PVDLS         LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (READ_BIT(PWR->SVMCR, PWR_SVMCR_PVDLS));
}

/**
  * @brief  Enable the Programmable voltage detector.
  * @rmtoll
  *  SVMCR          PVDE          LL_PWR_EnablePVD
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Disable the Programmable voltage detector.
  * @rmtoll
  *  SVMCR          PVDE          LL_PWR_DisablePVD
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Check if the Programmable voltage detector is enabled.
  * @rmtoll
  *  SVMCR          PVDE          LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_PVDE) == (PWR_SVMCR_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent USB supply.
  * @rmtoll
  *  SVMCR    USV       LL_PWR_EnableVddUSB
  */
__STATIC_INLINE void LL_PWR_EnableVddUSB(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Disable the independent USB supply.
  * @rmtoll
  *  SVMCR    USV       LL_PWR_DisableVDDUSB
  */
__STATIC_INLINE void LL_PWR_DisableVddUSB(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Check if the independent USB supply is enabled.
  * @rmtoll
  *  SVMCR    USV       LL_PWR_IsEnabledVddUSB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddUSB(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_USV) == (PWR_SVMCR_USV)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent I/Os supply.
  * @rmtoll
  *  SVMCR    IO2SV       LL_PWR_EnableVddIO2
  */
__STATIC_INLINE void LL_PWR_EnableVddIO2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Disable the independent I/Os supply.
  * @rmtoll
  *  SVMCR    IO2SV       LL_PWR_DisableVddIO2
  */
__STATIC_INLINE void LL_PWR_DisableVddIO2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Check if the independent I/Os supply is enabled.
  * @rmtoll
  *  SVMCR    IO2SV       LL_PWR_IsEnabledVddIO2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddIO2(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV) == (PWR_SVMCR_IO2SV)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent analog supply.
  * @rmtoll
  *  SVMCR    ASV       LL_PWR_EnableVddA
  */
__STATIC_INLINE void LL_PWR_EnableVddA(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Disable the independent analog supply.
  * @rmtoll
  *  SVMCR    ASV       LL_PWR_DisableVddA
  */
__STATIC_INLINE void LL_PWR_DisableVddA(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Check if the independent analog supply is enabled.
  * @rmtoll
  *  SVMCR    ASV       LL_PWR_IsEnabledVddA
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddA(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_ASV) == (PWR_SVMCR_ASV)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent analog supply voltage monitor.
  * @rmtoll
  *  SVMCR    UVMEN1       LL_PWR_EnableVddAMonitor \n
  *  SVMCR    UVMEN2       LL_PWR_EnableVddAMonitor
  * @param  supply This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ANALOG_VOLTAGE_MONITOR_1
  *         @arg @ref LL_PWR_ANALOG_VOLTAGE_MONITOR_2
  */
__STATIC_INLINE void LL_PWR_EnableVddAMonitor(uint32_t supply)
{
  SET_BIT(PWR->SVMCR, supply);
}

/**
  * @brief  Disable the independent analog supply voltage monitor.
  * @rmtoll
  *  SVMCR    UVMEN1       LL_PWR_DisableVddAMonitor \n
  *  SVMCR    UVMEN2       LL_PWR_DisableVddAMonitor
  * @param  supply This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ANALOG_VOLTAGE_MONITOR_1
  *         @arg @ref LL_PWR_ANALOG_VOLTAGE_MONITOR_2
  */
__STATIC_INLINE void LL_PWR_DisableVddAMonitor(uint32_t supply)
{
  CLEAR_BIT(PWR->SVMCR, supply);
}

/**
  * @brief  Check if the independent analog supply voltage monitor is enabled.
  * @rmtoll
  *  SVMCR    UVMEN1       LL_PWR_IsEnabledVddUSBMonitor \n
  *  SVMCR    UVMEN2       LL_PWR_IsEnabledVddUSBMonitor
  * @param  supply This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ANALOG_VOLTAGE_MONITOR_1
  *         @arg @ref LL_PWR_ANALOG_VOLTAGE_MONITOR_2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddAMonitor(uint32_t supply)
{
  return ((READ_BIT(PWR->SVMCR, supply) == (supply)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent USB supply monitor.
  * @rmtoll
  *  SVMCR    UVMEN       LL_PWR_EnableVddUSBMonitor
  */
__STATIC_INLINE void LL_PWR_EnableVddUSBMonitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Disable the independent USB supply monitor.
  * @rmtoll
  *  SVMCR    UVMEN       LL_PWR_DisableVddUSBMonitor
  */
__STATIC_INLINE void LL_PWR_DisableVddUSBMonitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Check if the independent USB supply monitor is enabled.
  * @rmtoll
  *  SVMCR    UVMEN       LL_PWR_IsEnabledVddUSBMonitor
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddUSBMonitor(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN) == (PWR_SVMCR_UVMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent I/Os supply monitor.
  * @rmtoll
  *  SVMCR    IO2VMEN       LL_PWR_EnableVddIO2Monitor
  */
__STATIC_INLINE void LL_PWR_EnableVddIO2Monitor(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Disable the independent I/Os supply monitor.
  * @rmtoll
  *  SVMCR    IO2VMEN       LL_PWR_DisableVddIO2Monitor
  */
__STATIC_INLINE void LL_PWR_DisableVddIO2Monitor(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Check if the independent I/Os supply monitor is enabled.
  * @rmtoll
  *  SVMCR    IO2VMEN       LL_PWR_IsEnabledVddIO2Monitor
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddIO2Monitor(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN) == (PWR_SVMCR_IO2VMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent analog supply monitor 1.
  * @rmtoll
  *  SVMCR    AVM1EN       LL_PWR_EnableVddAMonitor1
  */
__STATIC_INLINE void LL_PWR_EnableVddAMonitor1(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Disable the independent analog supply monitor 1.
  * @rmtoll
  *  SVMCR    AVM1EN       LL_PWR_DisableVddAMonitor1
  */
__STATIC_INLINE void LL_PWR_DisableVddAMonitor1(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Check if the independent analog supply monitor 1 is enabled.
  * @rmtoll
  *  SVMCR    AVM1EN       LL_PWR_IsEnabledVddAMonitor1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddAMonitor1(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN) == (PWR_SVMCR_AVM1EN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the independent analog supply monitor 2.
  * @rmtoll
  *  SVMCR    AVM2EN       LL_PWR_EnableVddAMonitor2
  */
__STATIC_INLINE void LL_PWR_EnableVddAMonitor2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Disable the independent analog supply monitor 2.
  * @rmtoll
  *  SVMCR    AVM2EN       LL_PWR_DisableVddAMonitor2
  */
__STATIC_INLINE void LL_PWR_DisableVddAMonitor2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Check if the independent analog supply monitor 2 is enabled.
  * @rmtoll
  *  SVMCR    AVM2EN       LL_PWR_IsEnabledVddAMonitor2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVddAMonitor2(void)
{
  return ((READ_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN) == (PWR_SVMCR_AVM2EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll
  *  WUCR2          WUPPx       LL_PWR_SetWakeupPinPolarity
  * @param  pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_HIGH
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_LOW
  */
__STATIC_INLINE void LL_PWR_SetWakeupPinPolarity(uint32_t pin, uint32_t polarity)
{
  MODIFY_REG(PWR->WUCR2, pin, ((0xFFUL * polarity) & pin));
}

/**
  * @brief  Get the wake up pin polarity for the event detection.
  * @rmtoll
  *  WUCR2          WUPPx       LL_PWR_GetWakeUpPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval State of bit (1 : polarity low or 0 : polarity high).
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPolarity(uint32_t wakeup_pin)
{
  return ((READ_BIT(PWR->WUCR2, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}


/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll
  *  WUCR3          WUPPx       LL_PWR_SetWakeupPinSelection
  * @param pin This parameter can be one or a combination of the following values:
  *        @arg @ref LL_PWR_WAKEUP_PIN1
  *        @arg @ref LL_PWR_WAKEUP_PIN2
  *        @arg @ref LL_PWR_WAKEUP_PIN3
  *        @arg @ref LL_PWR_WAKEUP_PIN4
  *        @arg @ref LL_PWR_WAKEUP_PIN5
  *        @arg @ref LL_PWR_WAKEUP_PIN6
  *        @arg @ref LL_PWR_WAKEUP_PIN7
  *        @arg @ref LL_PWR_WAKEUP_PIN8
  *        @arg @ref LL_PWR_WAKEUP_PIN_ALL
  * @param selection This parameter can be one of the following values:
  *        @arg @ref LL_PWR_WAKEUP_PIN_SELECTION_0
  *        @arg @ref LL_PWR_WAKEUP_PIN_SELECTION_1
  *        @arg @ref LL_PWR_WAKEUP_PIN_SELECTION_2
  *        @arg @ref LL_PWR_WAKEUP_PIN_SELECTION_3
  */
__STATIC_INLINE void LL_PWR_SetWakeupPinSelection(uint32_t pin, uint32_t selection)
{
  ATOMIC_MODIFY_REG(PWR->WUCR3, (PWR_WUCR3_WUSEL1 << (POSITION_VAL(pin) * 2U)),
                    (selection << (POSITION_VAL(pin) * 2U)));
}

/**
  * @brief  Get the wake up pin polarity for the event detection.
  * @rmtoll
  *  WUCR2          WUPPx       LL_PWR_GetWakeUpPinPolarity
  * @param pin This parameter can be one of the following values:
  *        @arg @ref LL_PWR_WAKEUP_PIN1
  *        @arg @ref LL_PWR_WAKEUP_PIN2
  *        @arg @ref LL_PWR_WAKEUP_PIN3
  *        @arg @ref LL_PWR_WAKEUP_PIN4
  *        @arg @ref LL_PWR_WAKEUP_PIN5
  *        @arg @ref LL_PWR_WAKEUP_PIN6
  *        @arg @ref LL_PWR_WAKEUP_PIN7
  *        @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeupPinSelection(uint32_t pin)
{
  return (READ_BIT(PWR->WUCR3, (PWR_WUCR3_WUSEL1 << (POSITION_VAL(pin) * 2U))));
}

/**
  * @brief  Enable the wake up pin_x.
  * @rmtoll
  *  WUCR1    WUPENx       LL_PWR_EnableWakeUpPin
  * @param  wakeup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t wakeup_pin)
{
  SET_BIT(PWR->WUCR1, wakeup_pin);
}

/**
  * @brief  Disable the wake up pin_x.
  * @rmtoll
  *  WUCR1    WUPENx       LL_PWR_DisableWakeUpPin
  * @param  wakeup_pin This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t wakeup_pin)
{
  CLEAR_BIT(PWR->WUCR1, wakeup_pin);
}

/**
  * @brief  Check if the wake up pin_x is enabled.
  * @rmtoll
  *  WUCR1    WUPENx       LL_PWR_IsEnabledWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t wakeup_pin)
{
  return ((READ_BIT(PWR->WUCR1, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll
  *  WUCR2          WUPPx       LL_PWR_SetWakeUpPinPolarityLow
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t wakeup_pin)
{
  SET_BIT(PWR->WUCR2, wakeup_pin);
}

/**
  * @brief  Set the wake up pin polarity high for the event detection.
  * @rmtoll
  *  WUCR2          WUPPx       LL_PWR_SetWakeUpPinPolarityHigh
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t wakeup_pin)
{
  CLEAR_BIT(PWR->WUCR2, wakeup_pin);
}

/**
  * @brief  Set the wakeup pin_x selection 0.
  * @rmtoll
  *  WUCR3          WUSELx          LL_PWR_SetWakeUpPinSignal0Selection
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal0Selection(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(wakeup_pin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_0 << (POSITION_VAL(wakeup_pin) * 2U)));
}

/**
  * @brief  Set the wakeup pin_x selection 1.
  * @rmtoll
  *  WUCR3          WUSELx          LL_PWR_SetWakeUpPinSignal1Selection
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal1Selection(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(wakeup_pin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_1 << (POSITION_VAL(wakeup_pin) * 2U)));
}

/**
  * @brief  Set the wakeup pin_x selection 2.
  * @rmtoll
  *  WUCR3          WUSELx          LL_PWR_SetWakeUpPinSignal2Selection
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal2Selection(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(wakeup_pin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_2 << (POSITION_VAL(wakeup_pin) * 2U)));
}

/**
  * @brief  Set the wakeup pin_x selection 3.
  * @rmtoll
  *  WUCR3          WUSELx          LL_PWR_SetWakeUpPinSignal3Selection
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinSignal3Selection(uint32_t wakeup_pin)
{
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(wakeup_pin) * 2U)),
             (LL_PWR_WAKEUP_PIN_SELECTION_3 << (POSITION_VAL(wakeup_pin) * 2U)));
}

/**
  * @brief  Get the wakeup pin_x selection.
  * @rmtoll
  *  WUCR3          WUSELx          LL_PWR_GetWakeUpPinSignalSelection
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  *         @arg @ref LL_PWR_WAKEUP_PIN7
  *         @arg @ref LL_PWR_WAKEUP_PIN8
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinSignalSelection(uint32_t wakeup_pin)
{
  return (READ_BIT(PWR->WUCR3, (3UL << (POSITION_VAL(wakeup_pin) * 2U))));
}

/**
  * @brief   Enable backup regulator.
  * @rmtoll
  *  BDCR1    BREN       LL_PWR_EnableBkUpRegulator
  * @warning When this bit is set, the backup RAM content is kept in Standby and
  *          VBAT modes. If BREN is reset, the backup RAM can still be used in
  *          Run, Sleep and Stop modes. However, its content is lost in Standby,
  *          Shutdown and VBAT modes. This bit can be written only when the
  *          regulator is LDO, which must be configured before switching to SMPS.
  */
__STATIC_INLINE void LL_PWR_EnableBkUpRegulator(void)
{
  SET_BIT(PWR->BDCR1, PWR_BDCR1_BREN);
}

/**
  * @brief  Disable backup regulator.
  * @rmtoll
  *  BDCR1    BREN       LL_PWR_DisableBkUpRegulator
  */
__STATIC_INLINE void LL_PWR_DisableBkUpRegulator(void)
{
  CLEAR_BIT(PWR->BDCR1, PWR_BDCR1_BREN);
}

/**
  * @brief  Check if the backup regulator is enabled.
  * @rmtoll
  *  BDCR1    BREN      LL_PWR_IsEnabledBkUpRegulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpRegulator(void)
{
  return ((READ_BIT(PWR->BDCR1, PWR_BDCR1_BREN) == (PWR_BDCR1_BREN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the backup domain voltage and temperature monitoring.
  * @rmtoll
  *  BDCR1    MONEN       LL_PWR_EnableMonitoring
  */
__STATIC_INLINE void LL_PWR_EnableMonitoring(void)
{
  SET_BIT(PWR->BDCR1, PWR_BDCR1_MONEN);
}

/**
  * @brief  Disable the backup domain voltage and temperature monitoring.
  * @rmtoll
  *  BDCR1    MONEN       LL_PWR_DisableMonitoring
  */
__STATIC_INLINE void LL_PWR_DisableMonitoring(void)
{
  CLEAR_BIT(PWR->BDCR1, PWR_BDCR1_MONEN);
}

/**
  * @brief  Check if the backup domain voltage and temperature monitoring is
  *         enabled.
  * @rmtoll
  *  BDCR1    MONEN      LL_PWR_IsEnabledMonitoring
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMonitoring(void)
{
  return ((READ_BIT(PWR->BDCR1, PWR_BDCR1_MONEN) == (PWR_BDCR1_MONEN)) ? 1UL : 0UL);
}
/**
  * @brief  Enable battery charging.
  * @rmtoll
  *  BDCR2          VBE           LL_PWR_EnableBatteryCharging
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  SET_BIT(PWR->BDCR2, PWR_BDCR2_VBE);
}

/**
  * @brief  Disable battery charging.
  * @rmtoll
  *  BDCR2          VBE           LL_PWR_DisableBatteryCharging
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->BDCR2, PWR_BDCR2_VBE);
}

/**
  * @brief  Check if battery charging is enabled.
  * @rmtoll
  *  BDCR2          VBE           LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((READ_BIT(PWR->BDCR2, PWR_BDCR2_VBE) == (PWR_BDCR2_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the battery charge resistor impedance.
  * @rmtoll
  *  BDCR2          VBRS          LL_PWR_SetBattChargResistor
  * @param  resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t resistor)
{
  MODIFY_REG(PWR->BDCR2, PWR_BDCR2_VBRS, resistor);
}

/**
  * @brief  Get the battery charge resistor impedance.
  * @rmtoll
  *  BDCR2          VBRS          LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (uint32_t)(READ_BIT(PWR->BDCR2, PWR_BDCR2_VBRS));
}

/**
  * @brief  Enable the backup domain write protection.
  * @rmtoll
  *  DBPR    DBP       LL_PWR_EnableBackupDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_EnableBackupDomainWriteProtection(void)
{
  CLEAR_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Disable the backup domain write protection.
  * @rmtoll
  *  DBPR    DBP       LL_PWR_DisableBackupDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_DisableBackupDomainWriteProtection(void)
{
  SET_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Check if the backup domain write protection is enabled.
  * @rmtoll
  *  DBPR    DBP       LL_PWR_IsEnabledBackupDomainWriteProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBackupDomainWriteProtection(void)
{
  return ((READ_BIT(PWR->DBPR, PWR_DBPR_DBP) == (PWR_DBPR_DBP)) ? 0UL : 1UL);
}

#if defined (PWR_UCPDR_UCPD_STDBY)
/**
  * @brief   Enable the USB Type-C and Power Delivery memorization in Standby mode.
  * @rmtoll
  *  UCPDR          UCPD_STDBY    LL_PWR_EnableUCPDStandbyMode
  * @warning This function must be called just before entering Standby mode.
  */
__STATIC_INLINE void LL_PWR_EnableUCPDStandbyMode(void)
{
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STDBY);
}

/**
  * @brief   Disable the USB Type-C and Power Delivery memorization in Standby mode.
  * @rmtoll
  *  UCPDR          UCPD_STDBY     LL_PWR_DisableUCPDStandbyMode
  * @warning This function must be called after exiting Standby mode and before any
  *          UCPD configuration update.
  */
__STATIC_INLINE void LL_PWR_DisableUCPDStandbyMode(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STDBY);
}

/**
  * @brief  Check the USB Type-C and Power Delivery Standby mode memorization state.
  * @rmtoll
  *  UCPDR          UCPD_STDBY           LL_PWR_IsEnabledUCPDStandbyMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDStandbyMode(void)
{
  return ((READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STDBY) == (PWR_UCPDR_UCPD_STDBY)) ? 1UL : 0UL);
}
#endif /* PWR_UCPDR_UCPD_STDBY */

#if defined(PWR_UCPDR_UCPD_DBDIS)
/**
  * @brief   Enable the USB Type-C and power delivery dead battery pull-down behavior
  *          on UCPD CC1 and CC2 pins.
  * @rmtoll
  *  UCPDR          UCPD_DBDIS           LL_PWR_EnableUCPDDeadBattery
  * @warning After exiting reset, the USB Type-C dead battery behavior is enabled,
  *          which might have a pull-down effect on CC1 and CC2 pins. It is recommended
  *          to disable it in all cases, either to stop this pull-down or to hand over
  *          control to the UCPD (which must therefore be initialized before doing the disable).
  */
__STATIC_INLINE void LL_PWR_EnableUCPDDeadBattery(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief   Disable the USB Type-C and power delivery dead battery pull-down behavior
  *          on UCPD CC1 and CC2 pins.
  * @rmtoll
  *  UCPDR          UCPD_DBDIS           LL_PWR_DisableUCPDDeadBattery
  * @warning After exiting reset, the USB Type-C dead battery behavior is enabled,
  *          which might have a pull-down effect on CC1 and CC2 pins. It is recommended
  *          to disable it in all cases, either to stop this pull-down or to hand over
  *          control to the UCPD (which must therefore be initialized before doing the disable).
  */
__STATIC_INLINE void LL_PWR_DisableUCPDDeadBattery(void)
{
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief   Check the USB Type-C and power delivery dead battery pull-down behavior
  *          on UCPD CC1 and CC2 pins.
  * @rmtoll
  *  UCPDR          UCPD_DBDIS           LL_PWR_IsEnabledUCPDDeadBattery
  * @warning After exiting reset, the USB Type-C dead battery behavior is enabled,
  *          which might have a pull-down effect on CC1 and CC2 pins. It is recommended
  *          to disable it in all cases, either to stop this pull-down or to hand over
  *          control to the UCPD (which must therefore be initialized before doing the disable).
  * @retval  State of feature (1 : enabled; 0 : disabled).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDDeadBattery(void)
{
  return ((READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS) == (PWR_UCPDR_UCPD_DBDIS)) ? 0UL : 1UL);
}
#endif /* PWR_UCPDR_UCPD_DBDIS */

/**
  * @brief  Enable the pull-up and pull-down configuration.
  * @rmtoll
  *  APCR          APC           LL_PWR_EnablePUPDConfig
  */
__STATIC_INLINE void LL_PWR_EnablePUPDConfig(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable the pull-up and pull-down configuration.
  * @rmtoll
  *  APCR          APC           LL_PWR_DisablePUPDConfig
  */
__STATIC_INLINE void LL_PWR_DisablePUPDConfig(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Check if the pull-up and pull-down configuration is enabled.
  * @rmtoll
  *  APCR          APC           LL_PWR_IsEnabledPUPDConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDConfig(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_APC) == (PWR_APCR_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-up in Standby and Shutdown modes.
  * @rmtoll
  *  PUCRx        PUx        LL_PWR_EnableGPIOPullUp
  * @param  gpio_port This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  * @if (PWR_PUCRF_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
  * @endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
  * @if (PWR_PUCRI_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTI (*)
  * @endif
  * @if (PWR_PUCRJ_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTJ (*)
  * @endif
  * @param  gpio_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullUp(uint32_t gpio_port, uint32_t gpio_pin)
{
  SET_BIT(*((uint32_t *)gpio_port), gpio_pin);
}

/**
  * @brief  Disable GPIO pull-up in Standby and Shutdown modes.
  * @rmtoll
  *  PUCRx        PUx        LL_PWR_DisableGPIOPullUp
  * @param  gpio_port This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  * @if (PWR_PUCRF_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
  * @endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
  * @if (PWR_PUCRI_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTI (*)
  * @endif
  * @if (PWR_PUCRJ_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTJ (*)
  * @endif
  * @param  gpio_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPullUp(uint32_t gpio_port, uint32_t gpio_pin)
{
  CLEAR_BIT(*((uint32_t *)gpio_port), gpio_pin);
}

/**
  * @brief  Check if GPIO pull-up in Standby and Shutdown modes is enabled.
  * @rmtoll
  *  PUCRx        PUx        LL_PWR_IsEnabledGPIOPullUp
  * @param  gpio_port This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  * @if (PWR_PUCRF_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
  * @endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
  * @if (PWR_PUCRI_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTI (*)
  * @endif
  * @if (PWR_PUCRJ_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTJ (*)
  * @endif
  * @param  gpio_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @note   (*) value not defined in all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullUp(uint32_t gpio_port, uint32_t gpio_pin)
{
  return ((READ_BIT(*((uint32_t *)(gpio_port)), gpio_pin) == (gpio_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-down in Standby and Shutdown modes.
  * @rmtoll
  *  PDCRx        PDx        LL_PWR_EnableGPIOPullDown
  * @param  gpio_port This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  * @if (PWR_PUCRF_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
  * @endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
  * @if (PWR_PUCRI_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTI (*)
  * @endif
  * @if (PWR_PUCRJ_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTJ (*)
  * @endif
  * @param  gpio_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullDown(uint32_t gpio_port, uint32_t gpio_pin)
{
  SET_BIT(*((__IO uint32_t *)(gpio_port + 4U)), gpio_pin);
}

/**
  * @brief  Disable GPIO pull-down in Standby and Shutdown modes.
  * @rmtoll
  *  PDCRx        PDx        LL_PWR_DisableGPIOPullDown
  * @param  gpio_port This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  * @if (PWR_PUCRF_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
  * @endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
  * @if (PWR_PUCRI_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTI (*)
  * @endif
  * @if (PWR_PUCRJ_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTJ (*)
  * @endif
  * @param  gpio_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPullDown(uint32_t gpio_port, uint32_t gpio_pin)
{
  CLEAR_BIT(*((__IO uint32_t *)(gpio_port + 4U)), gpio_pin);
}

/**
  * @brief  Check if GPIO pull-down in Standby and Shutdown modes is enabled.
  * @rmtoll
  *  PDCRx        PDx        LL_PWR_IsEnabledGPIOPullUp
  * @param  gpio_port This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PORTA
  *         @arg @ref LL_PWR_GPIO_PORTB
  *         @arg @ref LL_PWR_GPIO_PORTC
  *         @arg @ref LL_PWR_GPIO_PORTD
  *         @arg @ref LL_PWR_GPIO_PORTE
  * @if (PWR_PUCRF_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTF (*)
  * @endif
  *         @arg @ref LL_PWR_GPIO_PORTG
  *         @arg @ref LL_PWR_GPIO_PORTH
  * @if (PWR_PUCRI_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTI (*)
  * @endif
  * @if (PWR_PUCRJ_PU0)
  *         @arg @ref LL_PWR_GPIO_PORTJ (*)
  * @endif
  * @param  gpio_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_5
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_7
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_9
  *         @arg @ref LL_PWR_GPIO_PIN_10
  *         @arg @ref LL_PWR_GPIO_PIN_11
  *         @arg @ref LL_PWR_GPIO_PIN_12
  *         @arg @ref LL_PWR_GPIO_PIN_13
  *         @arg @ref LL_PWR_GPIO_PIN_14
  *         @arg @ref LL_PWR_GPIO_PIN_15
  * @note   (*) value not defined in all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullDown(uint32_t gpio_port, uint32_t gpio_pin)
{
  return ((READ_BIT(*((__IO uint32_t *)(gpio_port + 4U)), gpio_pin) == (gpio_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Get currently voltage scaling applied to VCORE.
  * @rmtoll
  *  SVMSR            ACTVOS[1:0]          LL_PWR_GetRegulCurrentVOS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_3
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_4
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulCurrentVOS(void)
{
  return (READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOS));
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR Flag management
  * @{
  */

/**
  * @brief  Indicate whether the EPOD (Embedded Power Distribution) booster is
  *         ready OR not.
  * @rmtoll
  *  VOSR   BOOSTRDY       LL_PWR_IsActiveFlag_BOOST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BOOST(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_BOOSTRDY) == (PWR_VOSR_BOOSTRDY)) ? 1UL : 0UL);
}

#if defined (PWR_VOSR_USBBOOSTRDY)
/**
  * @brief  Indicate whether the USB EPOD (Embedded Power Distribution) booster is
  *         ready OR not.
  * @rmtoll
  *  VOSR   USBBOOSTRDY       LL_PWR_IsActiveFlag_USBBOOST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_USBBOOST(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_USBBOOSTRDY) == (PWR_VOSR_USBBOOSTRDY)) ? 1UL : 0UL);
}
#endif /* defined (PWR_VOSR_USBBOOSTRDY) */

/**
  * @brief  Indicate whether the regulator voltage output is above voltage
  *         scaling range or not.
  * @rmtoll
  *  VOSR          VOSRDY          LL_PWR_IsActiveFlag_VOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((READ_BIT(PWR->VOSR, PWR_VOSR_VOSRDY) == (PWR_VOSR_VOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in standby mode or not.
  * @rmtoll
  *  SR          SBF          LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->SR, PWR_SR_SBF) == (PWR_SR_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in stop mode or not.
  * @rmtoll
  *  SR          STOPF          LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->SR, PWR_SR_STOPF) == (PWR_SR_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator supply is LDO or SMPS.
  * @rmtoll
  *  SVMSR          REGS          LL_PWR_IsActiveFlag_REGULATOR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGULATOR(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_REGS) == (PWR_SVMSR_REGS)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD voltage is below the threshold or not.
  * @rmtoll
  *  SVMSR          PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_PVDO) == (PWR_SVMSR_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator voltage output is equal to current
  *         used voltage scaling range or not.
  * @rmtoll
  *  SVMSR          ACTVOSRDY          LL_PWR_IsActiveFlag_ACTVOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOS(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY) == (PWR_SVMSR_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDDUSB is below the threshold of monitor or not.
  * @rmtoll
  *  SVMSR          VDDUSBRDY          LL_PWR_IsActiveFlag_VDDUSB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDUSB(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDUSBRDY) == (PWR_SVMSR_VDDUSBRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDDIO2 is below the threshold of monitor or not.
  * @rmtoll
  *  SVMSR          VDDIO2RDY          LL_PWR_IsActiveFlag_VDDIO2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDIO2(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDIO2RDY) == (PWR_SVMSR_VDDIO2RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDDA1 is below the threshold of monitor 1 or not.
  * @rmtoll
  *  SVMSR          VDDA1RDY          LL_PWR_IsActiveFlag_VDDA1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDA1(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA1RDY) == (PWR_SVMSR_VDDA1RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDDA2 is below the threshold of monitor 2 or not.
  * @rmtoll
  *  SVMSR          VDDA2RDY          LL_PWR_IsActiveFlag_VDDA2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDA2(void)
{
  return ((READ_BIT(PWR->SVMSR, PWR_SVMSR_VDDA2RDY) == (PWR_SVMSR_VDDA2RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is below high threshold or not.
  * @rmtoll
  *  BDSR   VBATH       LL_PWR_IsActiveFlag_VBATH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((READ_BIT(PWR->BDSR, PWR_BDSR_VBATH) == (PWR_BDSR_VBATH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the Core temperature level is above low threshold or not.
  * @rmtoll
  *  BDSR   TEMPL       LL_PWR_IsActiveFlag_TEMPL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((READ_BIT(PWR->BDSR, PWR_BDSR_TEMPL) == (PWR_BDSR_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the Core temperature level is below high threshold or not.
  * @rmtoll
  *  BDSR   TEMPH       LL_PWR_IsActiveFlag_TEMPH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((READ_BIT(PWR->BDSR, PWR_BDSR_TEMPH) == (PWR_BDSR_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 1.
  * @rmtoll
  *  WUSR          WUF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF1) == (PWR_WUSR_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 2.
  * @rmtoll
  *  WUSR          WUF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF2) == (PWR_WUSR_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 3.
  * @rmtoll
  *  WUSR          WUF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF3) == (PWR_WUSR_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 4.
  * @rmtoll
  *  WUSR          WUF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF4) == (PWR_WUSR_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 5.
  * @rmtoll
  *  WUSR          WUF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF5) == (PWR_WUSR_WUF5)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 6.
  * @rmtoll
  *  WUSR          WUF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF6) == (PWR_WUSR_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 7.
  * @rmtoll
  *  WUSR          WUF7          LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF7) == (PWR_WUSR_WUF7)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 8.
  * @rmtoll
  *  WUSR          WUF8          LL_PWR_IsActiveFlag_WU8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((READ_BIT(PWR->WUSR, PWR_WUSR_WUF8) == (PWR_WUSR_WUF8)) ? 1UL : 0UL);
}

/**
  * @brief  Clear stop flag.
  * @rmtoll
  *  SR          CSSF          LL_PWR_ClearFlag_STOP
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  WRITE_REG(PWR->SR, PWR_SR_CSSF);
}

/**
  * @brief  Clear standby flag.
  * @rmtoll
  *  SR          CSSF          LL_PWR_ClearFlag_SB
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  WRITE_REG(PWR->SR, PWR_SR_CSSF);
}

/**
  * @brief  Clear wake up flag 1.
  * @rmtoll
  *  WUSCR          CWUF1         LL_PWR_ClearFlag_WU1
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF1);
}

/**
  * @brief  Clear wake up flag 2.
  * @rmtoll
  *  WUSCR          CWUF2         LL_PWR_ClearFlag_WU2
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF2);
}

/**
  * @brief  Clear wake up flag 3.
  * @rmtoll
  *  WUSCR          CWUF3         LL_PWR_ClearFlag_WU3
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF3);
}

/**
  * @brief  Clear wake up flag 4.
  * @rmtoll
  *  WUSCR          CWUF4         LL_PWR_ClearFlag_WU4
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF4);
}

/**
  * @brief  Clear wake up flag 5.
  * @rmtoll
  *  WUSCR          CWUF5         LL_PWR_ClearFlag_WU5
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF5);
}

/**
  * @brief  Clear wake up flag 6.
  * @rmtoll
  *  WUSCR          CWUF6         LL_PWR_ClearFlag_WU6
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF6);
}

/**
  * @brief  Clear wake up flag 7.
  * @rmtoll
  *  WUSCR          CWUF7         LL_PWR_ClearFlag_WU7
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF7);
}

/**
  * @brief  Clear wake up flag 8.
  * @rmtoll
  *  WUSCR          CWUF8         LL_PWR_ClearFlag_WU8
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU8(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF8);
}

/**
  * @brief  Clear all wake up flags.
  * @rmtoll
  *  WUSCR          CWUF         LL_PWR_ClearFlag_WU
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_ATTRIBUTE_MANAGEMENT PWR Attribute management
  * @{
  */

/**
  * @brief  Enable privileged mode for nsecure items.
  * @rmtoll
  *  PRIVCFGR     NSPRIV        LL_PWR_EnableNSecurePrivilege
  */
__STATIC_INLINE void LL_PWR_EnableNSecurePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Disable privileged mode for nsecure items.
  * @rmtoll
  *  PRIVCFGR     NSPRIV          LL_PWR_DisableNSecurePrivilege
  */
__STATIC_INLINE void LL_PWR_DisableNSecurePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
}

/**
  * @brief  Check if privileged mode for nsecure items is enabled.
  * @rmtoll
  *  PRIVCFGR     NSPRIV          LL_PWR_IsEnabledNSecurePrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledNSecurePrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV) == PWR_PRIVCFGR_NSPRIV) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Enable privileged mode for secure items.
  * @rmtoll
  *  PRIVCFGR     SPRIV        LL_PWR_EnableSecurePrivilege
  */
__STATIC_INLINE void LL_PWR_EnableSecurePrivilege(void)
{
  SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
}

/**
  * @brief  Disable privileged mode for secure items.
  * @rmtoll
  *  PRIVCFGR     SPRIV          LL_PWR_DisableSecurePrivilege
  */
__STATIC_INLINE void LL_PWR_DisableSecurePrivilege(void)
{
  CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
}
#endif /* defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Check if privileged mode for secure items is enabled.
  * @rmtoll
  *  PRIVCFGR     SPRIV          LL_PWR_IsEnabledSecurePrivilege
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSecurePrivilege(void)
{
  return ((READ_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV) == PWR_PRIVCFGR_SPRIV) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure secure attribute mode.
  * @rmtoll
  *  SECCFGR     WUP1SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP2SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP3SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP4SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP5SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP6SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP7SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     WUP8SEC       LL_PWR_ConfigSecure \n
  *  SECCFGR     LPMSEC        LL_PWR_ConfigSecure \n
  *  SECCFGR     VDMSEC        LL_PWR_ConfigSecure \n
  *  SECCFGR     VBSEC         LL_PWR_ConfigSecure \n
  *  SECCFGR     APCSEC        LL_PWR_ConfigSecure
  * @param  secure_config This parameter can be the full combination
  *         of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1_NSEC or LL_PWR_WAKEUP_PIN1_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN2_NSEC or LL_PWR_WAKEUP_PIN2_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN3_NSEC or LL_PWR_WAKEUP_PIN3_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN4_NSEC or LL_PWR_WAKEUP_PIN4_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN5_NSEC or LL_PWR_WAKEUP_PIN5_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN6_NSEC or LL_PWR_WAKEUP_PIN6_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN7_NSEC or LL_PWR_WAKEUP_PIN7_SEC
  *         @arg @ref LL_PWR_WAKEUP_PIN8_NSEC or LL_PWR_WAKEUP_PIN8_SEC
  *         @arg @ref LL_PWR_LPM_NSEC         or LL_PWR_LPM_SEC
  *         @arg @ref LL_PWR_VDM_NSEC         or LL_PWR_VDM_SEC
  *         @arg @ref LL_PWR_VB_NSEC          or LL_PWR_VB_SEC
  *         @arg @ref LL_PWR_APC_NSEC         or LL_PWR_APC_SEC
  * @note   This API can be executed only by Core in secure mode.
  */
__STATIC_INLINE void LL_PWR_ConfigSecure(uint32_t secure_config)
{
  WRITE_REG(PWR->SECCFGR, secure_config);
}

/**
  * @brief   Get secure attribute configuration.
  * @rmtoll
  *  SECCFGR     WUP1SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP2SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP3SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP4SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP5SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP6SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP7SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     WUP8SEC       LL_PWR_GetConfigSecure \n
  *  SECCFGR     LPMSEC        LL_PWR_GetConfigSecure \n
  *  SECCFGR     VDMSEC        LL_PWR_GetConfigSecure \n
  *  SECCFGR     VBSEC         LL_PWR_GetConfigSecure \n
  *  SECCFGR     APCSEC        LL_PWR_GetConfigSecure
  * @retval  Returned value is the combination of the following values:
  *          @arg @ref LL_PWR_WAKEUP_PIN1_NSEC or LL_PWR_WAKEUP_PIN1_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN2_NSEC or LL_PWR_WAKEUP_PIN2_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN3_NSEC or LL_PWR_WAKEUP_PIN3_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN4_NSEC or LL_PWR_WAKEUP_PIN4_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN5_NSEC or LL_PWR_WAKEUP_PIN5_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN6_NSEC or LL_PWR_WAKEUP_PIN6_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN7_NSEC or LL_PWR_WAKEUP_PIN7_SEC
  *          @arg @ref LL_PWR_WAKEUP_PIN8_NSEC or LL_PWR_WAKEUP_PIN8_SEC
  *          @arg @ref LL_PWR_LPM_NSEC         or LL_PWR_LPM_SEC
  *          @arg @ref LL_PWR_VDM_NSEC         or LL_PWR_VDM_SEC
  *          @arg @ref LL_PWR_VB_NSEC          or LL_PWR_VB_SEC
  *          @arg @ref LL_PWR_APC_NSEC         or LL_PWR_APC_SEC
  * @warning This API can be executed only by Core in secure mode.
  */
__STATIC_INLINE uint32_t LL_PWR_GetConfigSecure(void)
{
  return (READ_REG(PWR->SECCFGR));
}
#endif /* defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_LL_PWR_H */
