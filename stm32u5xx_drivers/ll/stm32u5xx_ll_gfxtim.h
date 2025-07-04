/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_gfxtim.h
  * @brief   Header file of GFXTIM LL module.
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
#ifndef STM32U5XX_LL_GFXTIM_H
#define STM32U5XX_LL_GFXTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (GFXTIM)

/** @defgroup GFXTIM_LL GFXTIM
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GFXTIM_LL_Exported_Constants GFXTIM Exported Constants
  * @{
  */

/** @defgroup GFXTIM_LL_EC_TEARING_EFFECT_SOURCE GFXTIM Tearing-effect source
  * @{
  */
#define LL_GFXTIM_TEARING_EFFECT_GPIO   0x0U            /*!< Input pad rising  */
#define LL_GFXTIM_TEARING_EFFECT_HSYNC  GFXTIM_CR_TES_1 /*!< HSYNC rising      */
#define LL_GFXTIM_TEARING_EFFECT_VSYNC  GFXTIM_CR_TES   /*!< VSYNC rising      */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_TEARING_EFFECT_POLARITY GFXTIM Tearing-effect polarity
  * @{
  */
#define LL_GFXTIM_TEARING_EFFECT_RISING_EDGE  0U               /*!< Tearing Effect active on rizing edge  */
#define LL_GFXTIM_TEARING_EFFECT_FALLING_EDGE GFXTIM_CR_TEPOL  /*!< Tearing Effect active on falling edge */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_LINE_CLOCK_SOURCE GFXTIM Line clock source
  * @{
  */
#define LL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW   0U                                                           /*!< Line Clock Counter underflow  */
#define LL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW   GFXTIM_CGCR_LCS_0                                            /*!< Frame Clock Counter underflow */
#define LL_GFXTIM_CLKGEN_LINE_HSYNC_RISING     GFXTIM_CGCR_LCS_1                                            /*!< HSYNC rising edge             */
#define LL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING    (GFXTIM_CGCR_LCS_0 | GFXTIM_CGCR_LCS_1)                      /*!< HSYNC falling edge            */
#define LL_GFXTIM_CLKGEN_LINE_VSYNC_RISING     GFXTIM_CGCR_LCS_2                                            /*!< VSYNC rising edge             */
#define LL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING    (GFXTIM_CGCR_LCS_2 | GFXTIM_CGCR_LCS_0)                      /*!< VSYNC falling edge            */
#define LL_GFXTIM_CLKGEN_LINE_TE_RISING        (GFXTIM_CGCR_LCS_2 | GFXTIM_CGCR_LCS_1)                      /*!< TE rising edge                */
#define LL_GFXTIM_CLKGEN_LINE_TE_FALLING       (GFXTIM_CGCR_LCS_2 | GFXTIM_CGCR_LCS_1 | GFXTIM_CGCR_LCS_0)  /*!< TE falling edge               */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_LINE_CLOCK_COUNTER_CLOCK_SOURCE GFXTIM Line clock counter clock source
  * @{
  */
#define LL_GFXTIM_CLKGEN_LINE_COUNT_NONE        0U                 /*!< Disable line clock counter        */
#define LL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK  GFXTIM_CGCR_LCCCS  /*!< hclk as line clock counter source */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_CLOCK_COUNTER_FORCE_RELOAD GFXTIM  Counter clock generator force reload
  * @{
  */
#define LL_GFXTIM_LINE_FORCE_RELOAD       GFXTIM_CGCR_LCCFR                       /*!< Line clock counter force reload           */
#define LL_GFXTIM_FRAME_FORCE_RELOAD      GFXTIM_CGCR_FCCFR                       /*!< Frame clock counter force reload          */
#define LL_GFXTIM_LINE_FRAME_FORCE_RELOAD (GFXTIM_CGCR_LCCFR | GFXTIM_CGCR_FCCFR) /*!< Line and frame clock counter force reload */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_LINE_CLOCK_COUNTER_HW_REALOD GFXTIM Line clock counter hardware reload
  * @{
  */
#define LL_GFXTIM_CLKGEN_LCNT_NO_RELOAD               0U                                                                   /*!< No hardware reload */
#define LL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD  GFXTIM_CGCR_LCCHRS_0                                                 /*!< FCC underflow      */
#define LL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD     GFXTIM_CGCR_LCCHRS_1                                                 /*!< HSYNC rising       */
#define LL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD    (GFXTIM_CGCR_LCCHRS_0 | GFXTIM_CGCR_LCCHRS_1)                        /*!< HSYNC falling      */
#define LL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD     GFXTIM_CGCR_LCCHRS_2                                                 /*!< VSYNC rising       */
#define LL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD    (GFXTIM_CGCR_LCCHRS_2 | GFXTIM_CGCR_LCCHRS_0)                        /*!< VSYNC falling      */
#define LL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD        (GFXTIM_CGCR_LCCHRS_2 | GFXTIM_CGCR_LCCHRS_1)                        /*!< TE rising          */
#define LL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD       (GFXTIM_CGCR_LCCHRS_2 | GFXTIM_CGCR_LCCHRS_1 | GFXTIM_CGCR_LCCHRS_0) /*!< TE falling         */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_FRAME_CLOCK_SOURCE GFXTIM Frame clock source
  * @{
  */
#define LL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW   0U                                                          /*!< Line Clock Counter underflow  */
#define LL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW   GFXTIM_CGCR_FCS_0                                           /*!< Frame Clock Counter underflow */
#define LL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING     GFXTIM_CGCR_FCS_1                                           /*!< HSYNC rising edge             */
#define LL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING    (GFXTIM_CGCR_FCS_0 | GFXTIM_CGCR_FCS_1)                     /*!< HSYNC falling edge            */
#define LL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING     GFXTIM_CGCR_FCS_2                                           /*!< VSYNC rising edge             */
#define LL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING    (GFXTIM_CGCR_FCS_2 | GFXTIM_CGCR_FCS_0)                     /*!< VSYNC falling edge            */
#define LL_GFXTIM_CLKGEN_FRAME_TE_RISING        (GFXTIM_CGCR_FCS_2 | GFXTIM_CGCR_FCS_1)                     /*!< TE rising edge                */
#define LL_GFXTIM_CLKGEN_FRAME_TE_FALLING       (GFXTIM_CGCR_FCS_2 | GFXTIM_CGCR_FCS_1 | GFXTIM_CGCR_FCS_0) /*!< TE falling edge               */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_FRAME_CLOCK_COUNTER_CLOCK_SOURCE GFXTIM Frame clock counter clock source
  * @{
  */
#define LL_GFXTIM_CLKGEN_FCNT_DISABLE         0U                                                                /*!< Disable                      */
#define LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW  GFXTIM_CGCR_FCCCS_0                                               /*!< Line Clock Counter underflow */
#define LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING    GFXTIM_CGCR_FCCCS_1                                               /*!< HSYNC rising edge            */
#define LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING   (GFXTIM_CGCR_FCCCS_0 | GFXTIM_CGCR_FCCCS_1)                       /*!< HSYNC falling edge           */
#define LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING    GFXTIM_CGCR_FCCCS_2                                               /*!< VSYNC rising edge            */
#define LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING   (GFXTIM_CGCR_FCCCS_2 | GFXTIM_CGCR_FCCCS_0)                       /*!< VSYNC falling edge           */
#define LL_GFXTIM_CLKGEN_FCNT_TE_RISING       (GFXTIM_CGCR_FCCCS_2 | GFXTIM_CGCR_FCCCS_1)                       /*!< TE rising edge               */
#define LL_GFXTIM_CLKGEN_FCNT_TE_FALLING      (GFXTIM_CGCR_FCCCS_2 | GFXTIM_CGCR_FCCCS_1 | GFXTIM_CGCR_FCCCS_0) /*!< TE falling edge              */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_FRAME_CLOCK_COUNTER_HW_REALOD GFXTIM Frame clock counter hardware reload
  * @{
  */
#define LL_GFXTIM_CLKGEN_FCNT_NO_RELOAD               0U                                                                   /*!< No hardware reload           */
#define LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD   GFXTIM_CGCR_FCCHRS_0                                                 /*!< Line Clock Counter underflow */
#define LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD     GFXTIM_CGCR_FCCHRS_1                                                 /*!< HSYNC rising edge            */
#define LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD    (GFXTIM_CGCR_FCCHRS_0 | GFXTIM_CGCR_FCCHRS_1)                        /*!< HSYNC falling edge           */
#define LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD     GFXTIM_CGCR_FCCHRS_2                                                 /*!< VSYNC rising edge            */
#define LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD    (GFXTIM_CGCR_FCCHRS_2 | GFXTIM_CGCR_FCCHRS_0)                        /*!< VSYNC falling edge           */
#define LL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD        (GFXTIM_CGCR_FCCHRS_2 | GFXTIM_CGCR_FCCHRS_1)                        /*!< TE rising edge               */
#define LL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD       (GFXTIM_CGCR_FCCHRS_2 | GFXTIM_CGCR_FCCHRS_1 | GFXTIM_CGCR_FCCHRS_0) /*!< TE falling edge              */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_ABSTIM_LINE_COMPARE GFXTIM Absolute line compare
  * @{
  */
#define LL_GFXTIM_ABSTIM_LINE_COMP_1  0U   /*!< Absolute line compare 1 */
#define LL_GFXTIM_ABSTIM_LINE_COMP_2  4U   /*!< Absolute line compare 2 */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_ABSOLUTE_TIMER_COUNTER GFXTIM Absolute timer counter
  * @{
  */
#define LL_GFXTIM_ABSTIM_LINE_COUNTER        GFXTIM_TCR_ALCEN                      /*!< Enable absolute line counter                 */
#define LL_GFXTIM_ABSTIM_FRAME_COUNTER       GFXTIM_TCR_AFCEN                      /*!< Enable absolute frame counter                */
#define LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER  (GFXTIM_TCR_ALCEN | GFXTIM_TCR_AFCEN) /*!< Enable absolute line absolute frame counters */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_ABSOLUTE_COUNTER_RESET GFXTIM Absolute counter reset
  * @{
  */
#define LL_GFXTIM_ABSTIM_LINE_COUNTER_RESET        GFXTIM_TCR_FALCR                      /*!< Force absolute line counter reset            */
#define LL_GFXTIM_ABSTIM_FRAME_COUNTER_RESET       GFXTIM_TCR_FAFCR                      /*!< Force absolute frame counter reset           */
#define LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER_RESET  (GFXTIM_TCR_FALCR | GFXTIM_TCR_FAFCR) /*!< Force absolute line and frame counters reset */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_RELTIM_FRAME_COUNTER GFXTIM Relative frame counter(s)
  * @{
  */
#define LL_GFXTIM_RELTIM_COUNTER_1    GFXTIM_TCR_RFC1EN                        /*!< Relative frame counter 1    */
#define LL_GFXTIM_RELTIM_COUNTER_2    GFXTIM_TCR_RFC2EN                        /*!< Relative frame counter 2    */
#define LL_GFXTIM_RELTIM_COUNTER_ALL  (GFXTIM_TCR_RFC1EN | GFXTIM_TCR_RFC2EN)  /*!< All Relative frame counters */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_RELTIM_FRAME_COUNTER_MODE GFXTIM Relative frame counter mode
  * @{
  */
#define LL_GFXTIM_RELTIM_COUNTER_ONESHOT         0U                       /*!< Relative frame counter in one shot mode     */
#define LL_GFXTIM_RELTIM_COUNTER_CONTINUOUS      1U                       /*!< Relative frame counter in continuous mode   */
#define LL_GFXTIM_RELTIM_COUNTER_1_CONTINUOUS    GFXTIM_TCR_RFC1CM        /*!< Relative frame counter 1 in continuous mode */
#define LL_GFXTIM_RELTIM_COUNTER_2_CONTINUOUS    GFXTIM_TCR_RFC2CM        /*!< Relative frame counter 2 in continuous mode */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_RELTIM_FRAME_COUNTER_FORCE_RELOAD GFXTIM Relative frame counter(s) force reload
  * @{
  */
#define LL_GFXTIM_RELTIM_COUNTER_1_FORCE_RELOAD    GFXTIM_TCR_FRFC1R                       /*!< Relative frame counter 1 force reload    */
#define LL_GFXTIM_RELTIM_COUNTER_2_FORCE_RELOAD    GFXTIM_TCR_FRFC2R                       /*!< Relative frame counter 2 force reload    */
#define LL_GFXTIM_RELTIM_COUNTER_ALL_FORCE_RELOAD  (GFXTIM_TCR_FRFC1R | GFXTIM_TCR_FRFC2R) /*!< Relative frame aLL counters force reload */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_EVENTGEN GFXTIM Event generator
  * @{
  */
#define LL_GFXTIM_EVENTGEN_EVENT_1     GFXTIM_EVCR_EV1EN                         /*!< Event generator 1    */
#define LL_GFXTIM_EVENTGEN_EVENT_2     GFXTIM_EVCR_EV2EN                         /*!< Event generator 2    */
#define LL_GFXTIM_EVENTGEN_EVENT_3     GFXTIM_EVCR_EV3EN                         /*!< Event generator 3    */
#define LL_GFXTIM_EVENTGEN_EVENT_4     GFXTIM_EVCR_EV4EN                         /*!< Event generator 4    */
#define LL_GFXTIM_EVENTGEN_EVENT_ALL   (GFXTIM_EVCR_EV1EN | GFXTIM_EVCR_EV2EN | \
                                        GFXTIM_EVCR_EV3EN | GFXTIM_EVCR_EV4EN)   /*!< All event generators */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_EVENTGEN_LINE GFXTIM Line event generator
  * @{
  */
#define LL_GFXTIM_EVENTGEN_LINE_NONE          0U                                        /*!< Line none                       */
#define LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW  GFXTIM_EVSR_LES1_0                        /*!< Absolute line counter overflow  */
#define LL_GFXTIM_EVENTGEN_TEARING_EFFECT     GFXTIM_EVSR_LES1_1                        /*!< Tearing effect                  */
#define LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP    GFXTIM_EVSR_LES1_2                        /*!< Absolute line counter 1 compare */
#define LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP    (GFXTIM_EVSR_LES1_0 | GFXTIM_EVSR_LES1_2) /*!< Absolute line counter 2 compare */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_EVENTGEN_FRAME GFXTIM Frame event generator
  * @{
  */
#define LL_GFXTIM_EVENTGEN_FRAME_NONE         0U                                        /*!< Frame none                      */
#define LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW  GFXTIM_EVSR_FES1_0                        /*!< Absolute frame counter overflow */
#define LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP      GFXTIM_EVSR_FES1_1                        /*!< Absolute frame counter compare  */
#define LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD  GFXTIM_EVSR_FES1_2                        /*!< Relative frame counter 1 reload */
#define LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD  (GFXTIM_EVSR_FES1_0 | GFXTIM_EVSR_FES1_2) /*!< Relative frame counter 1 reload */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_WATCHDOG_TIMER_CLOCK_SOURCE GFXTIM Watchdog timer clock source
  * @{
  */
#define LL_GFXTIM_WDG_CLK_LINE_CLK        0U                                                                       /*!< Watchdog Line Clock                  */
#define LL_GFXTIM_WDG_CLK_FRAME_CLK       GFXTIM_WDGTCR_WDGCS_0                                                    /*!< Watchdog Frame Clock                 */
#define LL_GFXTIM_WDG_CLK_HSYNC_RISING    GFXTIM_WDGTCR_WDGCS_1                                                    /*!< Watchdog HSYNC rising edge           */
#define LL_GFXTIM_WDG_CLK_HSYNC_FALLING   (GFXTIM_WDGTCR_WDGCS_0 | GFXTIM_WDGTCR_WDGCS_1)                          /*!< Watchdog HSYNC falling edge          */
#define LL_GFXTIM_WDG_CLK_VSYNC_RISING    GFXTIM_WDGTCR_WDGCS_2                                                    /*!< Watchdog VSYNC rising edge           */
#define LL_GFXTIM_WDG_CLK_VSYNC_FALLING   (GFXTIM_WDGTCR_WDGCS_0 | GFXTIM_WDGTCR_WDGCS_2)                          /*!< Watchdog VSYNC falling edge          */
#define LL_GFXTIM_WDG_CLK_TE_RISING       (GFXTIM_WDGTCR_WDGCS_1 | GFXTIM_WDGTCR_WDGCS_2)                          /*!< Watchdog Tearing Effect rising edge  */
#define LL_GFXTIM_WDG_CLK_TE_FALLING      (GFXTIM_WDGTCR_WDGCS_0 | GFXTIM_WDGTCR_WDGCS_1 | GFXTIM_WDGTCR_WDGCS_2)  /*!< Watchdog Tearing Effect falling edge */
#define LL_GFXTIM_WDG_CLK_EVENT_1         GFXTIM_WDGTCR_WDGCS_3                                                    /*!< Watchdog Event Generator 1 output    */
#define LL_GFXTIM_WDG_CLK_EVENT_2         (GFXTIM_WDGTCR_WDGCS_0 | GFXTIM_WDGTCR_WDGCS_3)                          /*!< Watchdog Event Generator 2 output    */
#define LL_GFXTIM_WDG_CLK_EVENT_3         (GFXTIM_WDGTCR_WDGCS_1 | GFXTIM_WDGTCR_WDGCS_3)                          /*!< Watchdog Event Generator 3 output    */
#define LL_GFXTIM_WDG_CLK_EVENT_4         (GFXTIM_WDGTCR_WDGCS_0 | GFXTIM_WDGTCR_WDGCS_1 | GFXTIM_WDGTCR_WDGCS_3)  /*!< Watchdog Event Generator 4 output    */
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_FLAG GFXTIM flags
  * @{
  */
#define LL_GFXTIM_FLAG_AFCO      GFXTIM_ISR_AFCOF     /*!< Absolute Frame Counter Overflow Flag  */
#define LL_GFXTIM_FLAG_ALCO      GFXTIM_ISR_ALCOF     /*!< Absolute Line Counter Overflow Flag   */
#define LL_GFXTIM_FLAG_TE        GFXTIM_ISR_TEF       /*!< Tearing Effect Flag                   */
#define LL_GFXTIM_FLAG_AFCC1     GFXTIM_ISR_AFCC1F    /*!< Absolute Frame Counter Compare 1 Flag */
#define LL_GFXTIM_FLAG_ALCC1     GFXTIM_ISR_ALCC1F    /*!< Absolute Line Counter Compare 1 Flag  */
#define LL_GFXTIM_FLAG_ALCC2     GFXTIM_ISR_ALCC2F    /*!< Absolute Line Counter Compare 2 Flag  */
#define LL_GFXTIM_FLAG_RFC1R     GFXTIM_ISR_RFC1RF    /*!< Relative Frame Counter 1 Reload Flag  */
#define LL_GFXTIM_FLAG_RFC2R     GFXTIM_ISR_RFC2RF    /*!< Relative Frame Counter 2 Reload Flag  */
#define LL_GFXTIM_FLAG_EV1       GFXTIM_ISR_EV1F      /*!< Event 1 Flag                          */
#define LL_GFXTIM_FLAG_EV2       GFXTIM_ISR_EV2F      /*!< Event 2 Flag                          */
#define LL_GFXTIM_FLAG_EV3       GFXTIM_ISR_EV3F      /*!< Event 3 Flag                          */
#define LL_GFXTIM_FLAG_EV4       GFXTIM_ISR_EV4F      /*!< Event 4 Flag                          */
#define LL_GFXTIM_FLAG_WDGA      GFXTIM_ISR_WDGAF     /*!< Watchdog Alarm Flag                   */
#define LL_GFXTIM_FLAG_WDGP      GFXTIM_ISR_WDGPF     /*!< Watchdog Pre-alarm Flag               */
#define LL_GFXTIM_FLAG_ALL       (GFXTIM_ISR_AFCOF | GFXTIM_ISR_ALCOF  | GFXTIM_ISR_TEF    | GFXTIM_ISR_AFCC1F | \
                                  GFXTIM_ISR_ALCC1F | GFXTIM_ISR_ALCC2F | GFXTIM_ISR_RFC1RF | GFXTIM_ISR_RFC2RF | \
                                  GFXTIM_ISR_EV1F   | GFXTIM_ISR_EV2F   | GFXTIM_ISR_EV3F   | GFXTIM_ISR_EV4F   | \
                                  GFXTIM_ISR_WDGAF  |  GFXTIM_ISR_WDGPF )
/**
  * @}
  */

/** @defgroup GFXTIM_LL_EC_INTERRUPT GFXTIM Interrupt
  * @{
  */
#define LL_GFXTIM_NONE_IT                         0U                  /*!< No interruptions                                                        */
#define LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT  GFXTIM_IER_AFCOIE   /*!< Enable absolute frame counter overflow interruption                     */
#define LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT   GFXTIM_IER_ALCOIE   /*!< Enable absolute line counter overflow interruption                      */
#define LL_GFXTIM_TEARING_EFFECT_IT               GFXTIM_IER_TEIE     /*!< Enable tearing-effect interruption                                      */
#define LL_GFXTIM_ABSTIM_FRAME_COMP_IT            GFXTIM_IER_AFCC1IE  /*!< Enable absolute frame counter compare 1 interruption                    */
#define LL_GFXTIM_ABSTIM_LINE_COMP1_IT            GFXTIM_IER_ALCC1IE  /*!< Enable absolute line counter compare 1 interruption                     */
#define LL_GFXTIM_ABSTIM_LINE_COMP2_IT            GFXTIM_IER_ALCC2IE  /*!< Enable absolute line counter compare 2 interruption                     */
#define LL_GFXTIM_ABSTIM_LINE_ALL_IT              (GFXTIM_IER_ALCOIE | GFXTIM_IER_ALCC1IE | \
                                                   GFXTIM_IER_ALCC2IE) /*!< Enable all absolute line counter interruptions                         */

#define LL_GFXTIM_ABSTIM_FRAME_ALL_IT             (GFXTIM_IER_AFCOIE | GFXTIM_IER_AFCC1IE) /*!< Enable all absolute frame interruptions            */

#define LL_GFXTIM_RELTIM_COUNT_1_IT               GFXTIM_IER_RFC1RIE  /*!< Enable relative frame counter 1 interruption                            */
#define LL_GFXTIM_RELTIM_COUNT_2_IT               GFXTIM_IER_RFC2RIE  /*!< Enable relative frame counter 2 interruption                            */
#define LL_GFXTIM_EVENTGEN_EVENT_1_IT             GFXTIM_IER_EV1IE    /*!< Enable event generator 1 interruption                                   */
#define LL_GFXTIM_EVENTGEN_EVENT_2_IT             GFXTIM_IER_EV2IE    /*!< Enable event generator 2 interruption                                   */
#define LL_GFXTIM_EVENTGEN_EVENT_3_IT             GFXTIM_IER_EV3IE    /*!< Enable event generator 3 interruption                                   */
#define LL_GFXTIM_EVENTGEN_EVENT_4_IT             GFXTIM_IER_EV4IE    /*!< Enable event generator 4 interruption                                   */
#define LL_GFXTIM_WDG_PREALARM_IT                 GFXTIM_IER_WDGPIE   /*!< Enable watchdog pre-alarm interruption                                  */
#define LL_GFXTIM_WDG_ALARM_IT                    GFXTIM_IER_WDGAIE   /*!< Enable watchdog alarm interruption                                      */
#define LL_GFXTIM_WDG_ALL_IT                      (GFXTIM_IER_WDGAIE | GFXTIM_IER_WDGPIE)  /*!< Enable watchdog alarm and pre-alarm interruption s */

#define LL_GFXTIM_ALL_IT                          (GFXTIM_IER_AFCOIE  | GFXTIM_IER_ALCOIE  | GFXTIM_IER_TEIE    | \
                                                   GFXTIM_IER_AFCC1IE | GFXTIM_IER_ALCC1IE | GFXTIM_IER_ALCC2IE | \
                                                   GFXTIM_IER_RFC1RIE | GFXTIM_IER_RFC2RIE | GFXTIM_IER_EV1IE   | \
                                                   GFXTIM_IER_EV2IE   | GFXTIM_IER_EV3IE   | GFXTIM_IER_EV4IE   | \
                                                   GFXTIM_IER_WDGPIE  | GFXTIM_IER_WDGAIE)  /*!< Enable all interruptions                           */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macros ---------------------------------------------------------------------------------------------------*/

/** @defgroup GFXTIM_LL_Exported_Macros GFXTIM Exported Macros
  * @{
  */

/** @defgroup GFXTIM_LL_EM_COMMON_WRITE_READ_REGISTERS Common Write and Read Registers macros
  * @{
  */

/**
  * @brief  Read a value in GFXTIM register.
  * @param  instance GFXTIM Instance.
  * @param  reg      Register to be read.
  * @retval Register value.
  */
#define LL_GFXTIM_READ_REG(instance, reg) READ_REG((instance)->reg)

/**
  * @brief  Write a value in GFXTIM register.
  * @param  instance GFXTIM Instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_GFXTIM_WRITE_REG(instance, reg, value) WRITE_REG(((instance)->reg), (value))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GFXTIM_LL_Exported_Functions GFXTIM Exported Functions
  * @{
  */

/** @defgroup GFXTIM_LL_EF_GFXTIM GFXTIM
  * @{
  */

/** @defgroup LL_GFXTIM_TEARING_EFFECT GFXTIM Tearing-effect
  * @{
  */

/**
  * @brief  Set the tearing-effect (source and polarity).
  * @rmtoll
  *  CR              TES          LL_GFXTIM_TE_Config \n
  *  CR              TEPOL        LL_GFXTIM_TE_Config
  * @param  gfxtim   GFXTIM instance.
  * @param  source   This parameter can be one of the following values:
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_GPIO
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_HSYNC
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_VSYNC
  * @param  polarity This parameter can be one of the following values:
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_RISING_EDGE
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_FALLING_EDGE
  */
__STATIC_INLINE void LL_GFXTIM_TE_Config(GFXTIM_TypeDef *gfxtim, uint32_t source, uint32_t polarity)
{
  MODIFY_REG(gfxtim->CR, (GFXTIM_CR_TES | GFXTIM_CR_TEPOL), (source | polarity));
}

/**
  * @brief  Set the tearing-effect source.
  * @rmtoll
  *  CR        TES      LL_GFXTIM_TE_SetSource
  * @param  gfxtim GFXTIM instance.
  * @param  source This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_TEARING_EFFECT_GPIO
  *                @arg @ref LL_GFXTIM_TEARING_EFFECT_HSYNC
  *                @arg @ref LL_GFXTIM_TEARING_EFFECT_VSYNC
  */
__STATIC_INLINE void LL_GFXTIM_TE_SetSource(GFXTIM_TypeDef *gfxtim, uint32_t source)
{
  MODIFY_REG(gfxtim->CR, GFXTIM_CR_TES, source);
}

/**
  * @brief  Get the tearing-effect source.
  * @rmtoll
  *  CR              TES          LL_GFXTIM_TE_GetSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_TEARING_EFFECT_GPIO
  *         @arg @ref LL_GFXTIM_TEARING_EFFECT_HSYNC
  *         @arg @ref LL_GFXTIM_TEARING_EFFECT_VSYNC
  */
__STATIC_INLINE uint32_t LL_GFXTIM_TE_GetSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CR, GFXTIM_CR_TES));
}

/**
  * @brief  Set the tearing-effect polarity.
  * @rmtoll
  *  CR        TEPOL      LL_GFXTIM_TE_SetPolarity
  * @param  gfxtim   GFXTIM instance.
  * @param  polarity This parameter can be one of the following values:
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_RISING_EDGE
  *                  @arg @ref LL_GFXTIM_TEARING_EFFECT_FALLING_EDGE
  */
__STATIC_INLINE void LL_GFXTIM_TE_SetPolarity(GFXTIM_TypeDef *gfxtim, uint32_t polarity)
{
  MODIFY_REG(gfxtim->CR, GFXTIM_CR_TEPOL, polarity);
}

/**
  * @brief  Get the tearing-effect polarity.
  * @rmtoll
  *  CR              TEPOL          LL_GFXTIM_TE_GetPolarity
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_TEARING_EFFECT_RISING_EDGE
  *         @arg @ref LL_GFXTIM_TEARING_EFFECT_FALLING_EDGE
  */
__STATIC_INLINE uint32_t LL_GFXTIM_TE_GetPolarity(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CR, GFXTIM_CR_TEPOL));
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_CLOCK_GENERATOR GFXTIM Clock generator
  * @{
  */

/**
  * @brief  Set line clock counter reload value.
  * @rmtoll
  *  LCCRR        RELOAD      LL_GFXTIM_CLKGEN_SetLineReloadValue
  * @param  gfxtim     GFXTIM instance.
  * @param  reload_val Value between 0x0 and 0x3FFFFF
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetLineReloadValue(GFXTIM_TypeDef *gfxtim, uint32_t reload_val)
{
  MODIFY_REG(gfxtim->LCCRR, GFXTIM_LCCRR_RELOAD, reload_val);
}

/**
  * @brief  Get line clock counter reload value.
  * @rmtoll
  *  LCCRR        RELOAD      LL_GFXTIM_CLKGEN_GetLineReloadValue
  * @param  gfxtim GFXTIM instance.
  * @retval value between 0x0 and 0x3FFFFF
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetLineReloadValue(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->LCCRR, GFXTIM_LCCRR_RELOAD));
}

/**
  * @brief  Set line clock counter hardware reload source.
  * @rmtoll
  *  CGCR        LCCHRS      LL_GFXTIM_CLKGEN_SetLineReloadSource
  * @param  gfxtim     GFXTIM instance.
  * @param  reload_src This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_NO_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetLineReloadSource(GFXTIM_TypeDef *gfxtim, uint32_t reload_src)
{
  MODIFY_REG(gfxtim->CGCR, GFXTIM_CGCR_LCCHRS, reload_src);
}

/**
  * @brief  Get line clock counter hardware reload source.
  * @rmtoll
  *  CGCR        LCCHRS      LL_GFXTIM_CLKGEN_SetLineReloadSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_NO_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetLineReloadSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CGCR, GFXTIM_CGCR_LCCHRS));
}

/**
  * @brief  Set line clock counter clock source.
  * @rmtoll
  *  CGCR        LCCCS      LL_GFXTIM_CLKGEN_SetLineCounterSource
  * @param  gfxtim      GFXTIM instance.
  * @param  counter_src This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_NONE
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetLineCounterSource(GFXTIM_TypeDef *gfxtim, uint32_t counter_src)
{
  MODIFY_REG(gfxtim->CGCR, GFXTIM_CGCR_LCCCS, counter_src);
}

/**
  * @brief  Get line clock counter clock source.
  * @rmtoll
  *  CGCR        LCCCS      LL_GFXTIM_CLKGEN_GetLineCounterSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_NONE
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetLineCounterSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CGCR, GFXTIM_CGCR_LCCCS));
}

/**
  * @brief  Set line clock source.
  * @rmtoll
  *  CGCR        LCS      LL_GFXTIM_CLKGEN_SetLineClockSource
  * @param  gfxtim    GFXTIM instance.
  * @param  clock_src This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_RISING
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_RISING
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_RISING
  *                   @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_FALLING
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetLineClockSource(GFXTIM_TypeDef *gfxtim, uint32_t clock_src)
{
  MODIFY_REG(gfxtim->CGCR, GFXTIM_CGCR_LCS, clock_src);
}

/**
  * @brief  Get line clock source.
  * @rmtoll
  *  CGCR        LCS      LL_GFXTIM_CLKGEN_GetLineClockSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_FALLING
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetLineClockSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CGCR, GFXTIM_CGCR_LCS));
}

/**
  * @brief  Set line clock generator.
  * @rmtoll
  *  CGCR        LCCHRS    LL_GFXTIM_CLKGEN_ConfigLineClock \n
  *  CGCR        LCS       LL_GFXTIM_CLKGEN_ConfigLineClock \n
  *  CGCR        LCCCS     LL_GFXTIM_CLKGEN_ConfigLineClock
  * @param  gfxtim      GFXTIM instance.
  * @param  reload_src  This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_NO_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD
  * @param  counter_src This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_NONE
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK
  * @param  clock_src   This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_FALLING
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_ConfigLineClock(GFXTIM_TypeDef *gfxtim, uint32_t reload_src, uint32_t counter_src,
                                                      uint32_t clock_src)
{
  MODIFY_REG(gfxtim->CGCR, (GFXTIM_CGCR_LCCHRS | GFXTIM_CGCR_LCCCS | GFXTIM_CGCR_LCS),
             (reload_src | counter_src | clock_src));
}


/**
  * @brief  Set frame clock counter reload value.
  * @rmtoll
  *  FCCRR        RELOAD      LL_GFXTIM_CLKGEN_SetFrameReloadValue
  * @param  gfxtim GFXTIM instance.
  * @param  reload_val Value between 0x0 and 0xFFF
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetFrameReloadValue(GFXTIM_TypeDef *gfxtim, uint32_t reload_val)
{
  MODIFY_REG(gfxtim->FCCRR, GFXTIM_FCCRR_RELOAD, reload_val);
}

/**
  * @brief  Get frame clock counter reload value.
  * @rmtoll
  *  FCCRR        RELOAD      LL_GFXTIM_CLKGEN_GetFrameReloadValue
  * @param  gfxtim GFXTIM instance.
  * @retval value between 0x0 and 0xFFF
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetFrameReloadValue(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->FCCRR, GFXTIM_FCCRR_RELOAD));
}

/**
  * @brief  Set frame clock counter hardware reload source.
  * @rmtoll
  *  CGCR        FCCHRS      LL_GFXTIM_CLKGEN_SetFrameReloadSource
  * @param  gfxtim     GFXTIM instance.
  * @param  reload_src This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_NO_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetFrameReloadSource(GFXTIM_TypeDef *gfxtim, uint32_t reload_src)
{
  MODIFY_REG(gfxtim->CGCR, GFXTIM_CGCR_FCCHRS, reload_src);
}

/**
  * @brief  Get frame clock counter hardware reload source.
  * @rmtoll
  *  CGCR        FCCHRS      LL_GFXTIM_CLKGEN_GetFrameReloadSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_NO_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetFrameReloadSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CGCR, GFXTIM_CGCR_FCCHRS));
}

/**
  * @brief  Set frame clock counter clock source.
  * @rmtoll
  *  CGCR        FCCCS      LL_GFXTIM_CLKGEN_SetFrameCounterSource
  * @param  gfxtim      GFXTIM instance.
  * @param  counter_src This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_DISABLE
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetFrameCounterSource(GFXTIM_TypeDef *gfxtim, uint32_t counter_src)
{
  MODIFY_REG(gfxtim->CGCR, GFXTIM_CGCR_FCCCS, counter_src);
}

/**
  * @brief  Get line clock counter clock source.
  * @rmtoll
  *  CGCR        FCCCS      LL_GFXTIM_CLKGEN_GetFrameCounterSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_DISABLE
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetFrameCounterSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CGCR, GFXTIM_CGCR_FCCCS));
}

/**
  * @brief  Set line clock source.
  * @rmtoll
  *  CGCR        FCS      LL_GFXTIM_CLKGEN_SetFrameClockSource
  * @param  gfxtim    GFXTIM instance.
  * @param  clock_src This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_RISING
  *                   @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_FALLING
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_SetFrameClockSource(GFXTIM_TypeDef *gfxtim, uint32_t clock_src)
{
  MODIFY_REG(gfxtim->CGCR, GFXTIM_CGCR_FCS, clock_src);
}

/**
  * @brief  Get line clock source.
  * @rmtoll
  *  CGCR        FCS      LL_GFXTIM_CLKGEN_GetFrameClockSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_RISING
  *         @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_FALLING
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_GetFrameClockSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->CGCR, GFXTIM_CGCR_FCS));
}

/**
  * @brief  Set line clock generator.
  * @rmtoll
  *  CGCR        LCCHRS    LL_GFXTIM_CLKGEN_ConfigFrameClock \n
  *  CGCR        LCS       LL_GFXTIM_CLKGEN_ConfigFrameClock \n
  *  CGCR        LCCCS     LL_GFXTIM_CLKGEN_ConfigFrameClock
  * @param  gfxtim      GFXTIM instance.
  * @param  reload_src  This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_NO_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD
  * @param  counter_src This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_DISABLE
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING
  * @param  clock_src   This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_FALLING
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_ConfigFrameClock(GFXTIM_TypeDef *gfxtim, uint32_t reload_src,
                                                       uint32_t counter_src,
                                                       uint32_t clock_src)
{
  MODIFY_REG(gfxtim->CGCR, (GFXTIM_CGCR_FCCHRS | GFXTIM_CGCR_FCCCS | GFXTIM_CGCR_FCS),
             (reload_src | counter_src | clock_src));
}

/**
  * @brief  Set the frame and line clock generator.
  * @rmtoll
  *  CGCR        LCCHRS | LCS | LCCCS   LL_GFXTIM_CLKGEN_ConfigFrameLineClock \n
  *  CGCR        FCCHRS | FCS | FCCCS   LL_GFXTIM_CLKGEN_ConfigFrameLineClock
  * @param  gfxtim       GFXTIM instance.
  * @param frame_config This parameter must be a combination of the following values:
  *                     frame_config = (frame_reload_src | frame_counter_src | frame_clock_src)
  * @param line_config  This parameter must be a combination of the following values:
  *                     line_config = (line_reload_src | line_counter_src | line_clock_src)
  *
  *   frame_reload_src  This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_NO_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD
  *
  *   frame_counter_src This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_DISABLE
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FCNT_TE_FALLING
  *
  *   frame_clock_src   This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_RISING
  *                     @arg @ref LL_GFXTIM_CLKGEN_FRAME_TE_FALLING
  *
  *   line_reload_src  This parameter must be a combination of all the following values:
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_NO_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD
  *                    @arg @ref LL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD
  *
  *   line_counter_src This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_NONE
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK
  *
  *   line_clock_src   This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_RISING
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_RISING
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_RISING
  *                    @arg @ref LL_GFXTIM_CLKGEN_LINE_TE_FALLING
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_ConfigFrameLineClock(GFXTIM_TypeDef *gfxtim, uint32_t frame_config,
                                                           uint32_t line_config)
{
  MODIFY_REG(gfxtim->CGCR, (GFXTIM_CGCR_FCCHRS | GFXTIM_CGCR_FCCCS | GFXTIM_CGCR_FCS | GFXTIM_CGCR_LCCHRS |
                            GFXTIM_CGCR_LCCCS | GFXTIM_CGCR_LCS), (frame_config | line_config));
}

/**
  * @brief  Force reload the clock generator counter(s).
  * @rmtoll
  *  CGCR                 FCCFR      LL_GFXTIM_CLKGEN_ForceReloadCounter \n
  *  CGCR                 LCCFR      LL_GFXTIM_CLKGEN_ForceReloadCounter
  * @param  gfxtim         GFXTIM instance.
  * @param  counter_reload This parameter can be one of the following values:
  *                        @arg @ref LL_GFXTIM_LINE_FORCE_RELOAD
  *                        @arg @ref LL_GFXTIM_FRAME_FORCE_RELOAD
  *                        @arg @ref LL_GFXTIM_LINE_FRAME_FORCE_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_ForceReloadCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter_reload)
{
  SET_BIT(gfxtim->CGCR, counter_reload);
}

/**
  * @brief  Enable the frame clock calibration output.
  * @rmtoll
  *  CR        FCCOE      LL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->CR, GFXTIM_CR_FCCOE);
}

/**
  * @brief  Disable the frame clock calibration output.
  * @rmtoll
  *  CR        FCCOE      LL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->CR, GFXTIM_CR_FCCOE);
}

/**
  * @brief  Check if the frame clock calibration output is enabled.
  * @rmtoll
  *  CR        FCCOE      LL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->CR, GFXTIM_CR_FCCOE) == (GFXTIM_CR_FCCOE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the frame clock calibration output.
  * @rmtoll
  *  CR        FCCOE      LL_GFXTIM_CLKGEN_EnableLineClkCalibOutput
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_EnableLineClkCalibOutput(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->CR, GFXTIM_CR_LCCOE);
}

/**
  * @brief  Disable the frame clock calibration output.
  * @rmtoll
  *  CR        FCCOE      LL_GFXTIM_CLKGEN_DisableLineClkCalibOutput
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_CLKGEN_DisableLineClkCalibOutput(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->CR, GFXTIM_CR_LCCOE);
}

/**
  * @brief  Check if the frame clock calibration output is enabled.
  * @rmtoll
  *  CR        FCCOE      LL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->CR, GFXTIM_CR_LCCOE) == (GFXTIM_CR_LCCOE)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_ABSOLUTE_TIMER GFXTIM Absolute timer
  * @{
  */

/**
  * @brief  Set the absolute line compare 1 value.
  * @rmtoll
  *  ALCC2R      LINE      LL_GFXTIM_ABSTIM_SetLineCompare1Value
  * @param  gfxtim GFXTIM instance.
  * @param  value  Value between 0x0 and 0xFFF
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_SetLineCompare1Value(GFXTIM_TypeDef *gfxtim, uint32_t value)
{
  MODIFY_REG(gfxtim->ALCC1R, GFXTIM_ALCC1R_LINE, value);
}

/**
  * @brief  Get the absolute line compare 1 value.
  * @rmtoll
  *  ALCC1R      LINE      LL_GFXTIM_ABSTIM_GetLineCompare1Value
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetLineCompare1Value(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->ALCC1R, GFXTIM_ALCC1R_LINE));
}

/**
  * @brief  Set the absolute line compare 2 value.
  * @rmtoll
  *  ALCC2R      LINE      LL_GFXTIM_ABSTIM_SetLineCompare2Value
  * @param  gfxtim GFXTIM instance.
  * @param  value  Value between 0x0 and 0xFFF
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_SetLineCompare2Value(GFXTIM_TypeDef *gfxtim, uint32_t value)
{
  MODIFY_REG(gfxtim->ALCC2R, GFXTIM_ALCC2R_LINE, value);
}

/**
  * @brief  Get the absolute line compare 2 value.
  * @rmtoll
  *  ALCC2R      LINE      LL_GFXTIM_ABSTIM_GetLineCompare2Value
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetLineCompare2Value(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->ALCC2R, GFXTIM_ALCC2R_LINE));
}

/**
  * @brief  Set the absolute line compare value.
  * @rmtoll
  *  ALCC1R      LINE      LL_GFXTIM_ABSTIM_SetLineCompareValue \n
  *  ALCC2R      LINE      LL_GFXTIM_ABSTIM_SetLineCompareValue
  * @param  gfxtim GFXTIM instance.
  * @param  comp   This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP_1
  *                @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP_2
  * @param  value  Value between 0x0 and 0xFFF
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_SetLineCompareValue(const GFXTIM_TypeDef *gfxtim, uint32_t comp, uint32_t value)
{
  uint32_t reg_addr = (uint32_t)&gfxtim->ALCC1R;
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + comp), GFXTIM_ALCC1R_LINE, value);
}

/**
  * @brief  Get the absolute line compare value.
  * @rmtoll
  *  ALCC1R      LINE      LL_GFXTIM_ABSTIM_GetLineCompareValue \n
  *  ALCC2R      LINE      LL_GFXTIM_ABSTIM_GetLineCompareValue
  * @param  gfxtim GFXTIM instance.
  * @param  comp   This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP_1
  *                @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP_2
  * @retval Value between 0x0 and 0xFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetLineCompareValue(const GFXTIM_TypeDef *gfxtim, uint32_t comp)
{
  uint32_t reg_addr = (uint32_t) &(gfxtim->ALCC1R) + comp;
  return (READ_BIT(*(__IO uint32_t *)reg_addr, GFXTIM_ALCC1R_LINE));
}

/**
  * @brief  Set the absolute line counter value.
  * @rmtoll
  *  ALCR      LINE      LL_GFXTIM_ABSTIM_SetLineCounter
  * @param  gfxtim GFXTIM instance.
  * @param  value  Value between 0x0 and 0xFFF
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_SetLineCounter(GFXTIM_TypeDef *gfxtim, uint32_t value)
{
  MODIFY_REG(gfxtim->ALCR, GFXTIM_ALCR_LINE, value);
}

/**
  * @brief  Get the absolute line counter value.
  * @rmtoll
  *  ALCR      LINE      LL_GFXTIM_ABSTIM_GetLineCounterStartValue
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetLineCounter(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->ALCR, GFXTIM_ALCR_LINE));
}

/**
  * @brief  Enable the absolute line counter.
  * @rmtoll
  *  TCR        ALCEN      LL_GFXTIM_ABSTIM_EnableLineCounter
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_EnableLineCounter(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_ALCEN);
}

/**
  * @brief  Disable the absolute line counter.
  * @rmtoll
  *  TDR        ALCDIS      LL_GFXTIM_ABSTIM_DisableLineCounter
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_DisableLineCounter(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TDR, GFXTIM_TDR_ALCDIS);
}

/**
  * @brief  Check that absolute line counter is enabled.
  * @rmtoll
  *  TSR        ALCS      LL_GFXTIM_ABSTIM_IsEnabledLineCounter
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_IsEnabledLineCounter(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->TSR, GFXTIM_TSR_ALCS) == (GFXTIM_TSR_ALCS)) ? 1UL : 0UL);
}

/**
  * @brief  Force reset the absolute line counter.
  * @rmtoll
  *  TCR        FALCR      LL_GFXTIM_ABSTIM_ForceResetLineCounter
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_ForceResetLineCounter(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_FALCR);
}

/**
  * @brief  Set the absolute frame compare value.
  * @rmtoll
  *  AFCC1R      FRAME      LL_GFXTIM_ABSTIM_SetFrameCompareValue
  * @param  gfxtim GFXTIM instance.
  * @param  value  Value between 0x0 and 0xFFFFF.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_SetFrameCompareValue(GFXTIM_TypeDef *gfxtim, uint32_t value)
{
  MODIFY_REG(gfxtim->AFCC1R, GFXTIM_AFCC1R_FRAME, value);
}

/**
  * @brief  Get the absolute frame compare value.
  * @rmtoll
  *  AFCC1R      FRAME      LL_GFXTIM_ABSTIM_GetFrameCompareValue
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetFrameCompareValue(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->AFCC1R, GFXTIM_AFCC1R_FRAME));
}

/**
  * @brief  Set the absolute frame start counter value.
  * @rmtoll
  *  AFCR      FRAME      LL_GFXTIM_ABSTIM_SetFrameCounter
  * @param  gfxtim GFXTIM instance.
  * @param  value  Value between 0x0 and 0xFFFFF.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_SetFrameCounter(GFXTIM_TypeDef *gfxtim, uint32_t value)
{
  MODIFY_REG(gfxtim->AFCR, GFXTIM_AFCR_FRAME, value);
}

/**
  * @brief  Get the absolute frame start counter value.
  * @rmtoll
  *  AFCR      FRAME      LL_GFXTIM_ABSTIM_GetFrameCounter
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetFrameCounter(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->AFCR, GFXTIM_AFCR_FRAME));
}

/**
  * @brief  Enable the absolute frame counter.
  * @rmtoll
  *  TCR        AFCEN      LL_GFXTIM_ABSTIM_EnableFrameCounter
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_EnableFrameCounter(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_AFCEN);
}

/**
  * @brief  Disable the absolute frame counter.
  * @rmtoll
  *  TDR        AFCDIS      LL_GFXTIM_ABSTIM_DisableFrameCounter
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_DisableFrameCounter(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TDR, GFXTIM_TDR_AFCDIS);
}

/**
  * @brief  Check that absolute frame counter is enabled.
  * @rmtoll
  *  TSR        AFCS      LL_GFXTIM_ABSTIM_IsEnabledFrameCounter
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_IsEnabledFrameCounter(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->TSR, GFXTIM_TSR_AFCS) == (GFXTIM_TSR_AFCS)) ? 1UL : 0UL);
}

/**
  * @brief  Force reset the absolute frame counter.
  * @rmtoll
  *  TCR        FAFCR      LL_GFXTIM_ABSTIM_ForceResetFrameCounter
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_ForceResetFrameCounter(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_FAFCR);
}

/**
  * @brief  Get the absolute line and frame counters value.
  * @rmtoll
  *  ATR      LINE      LL_GFXTIM_ABSTIM_GetCounter \n
  *  ATR      FRAME     LL_GFXTIM_ABSTIM_GetCounter
  * @param  gfxtim GFXTIM instance.
  * @note   The return value contains absolute line and frame value:
  *         - Absolute line value : from bit 0 to bit 11.
  *         - Absolute frame value: from bit 12 to bit 31.
  * @retval Value between 0x0 and 0xFFFFFFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_GetCounter(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->ATR, (GFXTIM_ATR_LINE | GFXTIM_ATR_FRAME)));
}

/**
  * @brief  Enable the absolute timer(s).
  * @rmtoll
  *  TCR        AFCEN      LL_GFXTIM_ABSTIM_EnableCounter \n
  *  TCR        ACCEN      LL_GFXTIM_ABSTIM_EnableCounter
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNTER
  *                 @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNTER
  *                 @arg @ref LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_EnableCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  MODIFY_REG(gfxtim->TCR, (GFXTIM_TCR_ALCEN | GFXTIM_TCR_AFCEN), counter);
}

/**
  * @brief  Disable the absolute timer(s).
  * @rmtoll
  *  TDR        AFCDIS      LL_GFXTIM_ABSTIM_DisableCounter \n
  *  TDR        ALCDIS      LL_GFXTIM_ABSTIM_DisableCounter
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNTER
  *                 @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNTER
  *                 @arg @ref LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_DisableCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  SET_BIT(gfxtim->TDR, counter);
}

/**
  * @brief  Check that absolute timer  is enabled.
  * @rmtoll
  *  TDR        ALCS      LL_GFXTIM_ABSTIM_IsEnabledCounter \n
  *  TDR        AFCS      LL_GFXTIM_ABSTIM_IsEnabledCounter
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNTER
  *                 @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNTER
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_ABSTIM_IsEnabledCounter(const GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  return ((READ_BIT(gfxtim->TSR, counter) == (counter)) ? 1UL : 0UL);
}

/**
  * @brief  Force reset the absolute counter.
  * @rmtoll
  *  TCR        FAFCR      LL_GFXTIM_ABSTIM_ForceResetCounter \n
  *  TCR        FALCR      LL_GFXTIM_ABSTIM_ForceResetCounter
  * @param  gfxtim        GFXTIM instance.
  * @param  counter_reset This parameter can be one of the following values:
  *                       @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNTER_RESET
  *                       @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNTER_RESET
  *                       @arg @ref LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER_RESET
  */
__STATIC_INLINE void LL_GFXTIM_ABSTIM_ForceResetCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter_reset)
{
  MODIFY_REG(gfxtim->TCR, (GFXTIM_TCR_FAFCR | GFXTIM_TCR_FALCR), counter_reset);
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_RELATIVE_TIMER GFXTIM Relative timer
  * @{
  */

/**
  * @brief  Enable the relative frame counter 1.
  * @rmtoll
  *  TCR        RFC1EN      LL_GFXTIM_RELTIM_EnableFrameCounter1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_EnableFrameCounter1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_RFC1EN);
}

/**
  * @brief  Disable the relative frame counter 1.
  * @rmtoll
  *  TDR        RFC1DIS      LL_GFXTIM_RELTIM_DisableFrameCounter1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_DisableFrameCounter1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TDR, GFXTIM_TDR_RFC1DIS);
}

/**
  * @brief  Check that relative frame counter 1 is enabled.
  * @rmtoll
  *  TSR        RFC1DIS      LL_GFXTIM_RELTIM_IsEnabledFrameCounter1
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_IsEnabledFrameCounter1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->TSR, GFXTIM_TSR_RFC1S) == (GFXTIM_TSR_RFC1S)) ? 1UL : 0UL);
}

/**
  * @brief  Set the relative frame counter 1 mode.
  * @rmtoll
  *  TCR        RFC1CM      LL_GFXTIM_RELTIM_SetCounter1Mode
  * @param  gfxtim GFXTIM instance.
  * @param  mode   This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_RELTIM_COUNTER_ONESHOT
  *                @arg @ref LL_GFXTIM_RELTIM_COUNTER_1_CONTINUOUS
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_SetCounter1Mode(GFXTIM_TypeDef *gfxtim, uint32_t mode)
{
  MODIFY_REG(gfxtim->TCR, GFXTIM_TCR_RFC1CM, mode);
}

/**
  * @brief  Get the relative frame counter 1 mode.
  * @rmtoll
  *  TCR        RFC1CM      LL_GFXTIM_RELTIM_GetCounter1Mode
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_RELTIM_COUNTER_ONESHOT
  *         @arg @ref LL_GFXTIM_RELTIM_COUNTER_1_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_GetCounter1Mode(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->TCR, GFXTIM_TCR_RFC1CM));
}

/**
  * @brief  Enable the relative frame counter 2.
  * @rmtoll
  *  TCR        RFC2EN      LL_GFXTIM_RELTIM_EnableFrameCounter2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_EnableFrameCounter2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_RFC2EN);
}

/**
  * @brief  Disable the relative frame counter 2.
  * @rmtoll
  *  TDR        RFC2DIS      LL_GFXTIM_RELTIM_DisableFrameCounter2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_DisableFrameCounter2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TDR, GFXTIM_TDR_RFC2DIS);
}

/**
  * @brief  Check that relative frame counter 2 is enabled.
  * @rmtoll
  *  TSR        RFC2S      LL_GFXTIM_RELTIM_IsEnabledFrameCounter2
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_IsEnabledFrameCounter2(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->TSR, GFXTIM_TSR_RFC2S) == (GFXTIM_TSR_RFC2S)) ? 1UL : 0UL);
}

/**
  * @brief  Set the relative frame counter 2 mode.
  * @rmtoll
  *  TCR        RFC2CM      LL_GFXTIM_RELTIM_SetCounter2Mode
  * @param  gfxtim GFXTIM instance.
  * @param  mode   This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_RELTIM_COUNTER_ONESHOT
  *                @arg @ref LL_GFXTIM_RELTIM_COUNTER_2_CONTINUOUS
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_SetCounter2Mode(GFXTIM_TypeDef *gfxtim, uint32_t mode)
{
  MODIFY_REG(gfxtim->TCR, GFXTIM_TCR_RFC2CM, mode);
}

/**
  * @brief  Get the relative frame counter 2 mode.
  * @rmtoll
  *  TCR        RFC2CM      LL_GFXTIM_RELTIM_GetCounter2Mode
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_RELTIM_COUNTER_ONESHOT
  *         @arg @ref LL_GFXTIM_RELTIM_COUNTER_2_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_GetCounter2Mode(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->TCR, GFXTIM_TCR_RFC2CM));
}

/**
  * @brief  Enable the relative frame counter.
  * @rmtoll
  *  TCR        RFC1EN      LL_GFXTIM_RELTIM_EnableFrameCounter \n
  *  TCR        RFC2EN      LL_GFXTIM_RELTIM_EnableFrameCounter
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_EnableFrameCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  MODIFY_REG(gfxtim->TCR, (GFXTIM_TCR_RFC1EN | GFXTIM_TCR_RFC2EN), counter);
}

/**
  * @brief  Disable the relative frame counter.
  * @rmtoll
  *  TDR        RFC1DIS      LL_GFXTIM_RELTIM_DisableFrameCounter \n
  *  TDR        RFC2DIS      LL_GFXTIM_RELTIM_DisableFrameCounter
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_DisableFrameCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  MODIFY_REG(gfxtim->TDR, (GFXTIM_TDR_RFC1DIS | GFXTIM_TDR_RFC2DIS), counter);
}

/**
  * @brief  Check that relative frame counter 2 is enabled.
  * @rmtoll
  *  TSR        RFC1S      LL_GFXTIM_RELTIM_IsEnabledFrameCounter \n
  *  TSR        RFC2S      LL_GFXTIM_RELTIM_IsEnabledFrameCounter
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_IsEnabledFrameCounter(const GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  return ((READ_BIT(gfxtim->TSR, counter) == (counter)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the relative counter in continuous mode.
  * @rmtoll
  *  TCR        RFC1EN      LL_GFXTIM_RELTIM_EnableContinuous \n
  *  TCR        RFC2EN      LL_GFXTIM_RELTIM_EnableContinuous
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_EnableContinuous(GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  SET_BIT(gfxtim->TCR, ((counter << 1U) | counter));
}

/**
  * @brief  Enable the relative counter in one shot mode.
  * @rmtoll
  *  TCR        RFC1EN      LL_GFXTIM_RELTIM_EnableOneShot \n
  *  TCR        RFC2EN      LL_GFXTIM_RELTIM_EnableOneShot
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_EnableOneShot(GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  uint32_t mask = READ_REG(gfxtim->TCR);
  mask &= ~(counter << 1U);
  MODIFY_REG(gfxtim->TCR, (GFXTIM_TCR_RFC1CM | GFXTIM_TCR_RFC1EN | GFXTIM_TCR_RFC2CM | GFXTIM_TCR_RFC2EN),
             (mask | counter));
}

/**
  * @brief  Set the relative frame counter mode.
  * @rmtoll
  *  TCR        RFC1CM      LL_GFXTIM_RELTIM_SetCounterMode \n
  *  TCR        RFC2CM      LL_GFXTIM_RELTIM_SetCounterMode
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  * @param  mode    This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_ONESHOT
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_CONTINUOUS
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_SetCounterMode(GFXTIM_TypeDef *gfxtim, uint32_t counter, uint32_t mode)
{
  MODIFY_REG(gfxtim->TCR, (GFXTIM_TCR_RFC1CM | GFXTIM_TCR_RFC2CM), ((mode << 1U) << POSITION_VAL(counter)));
}

/**
  * @brief  Get the relative frame counter mode.
  * @rmtoll
  *  TCR        RFC1CM      LL_GFXTIM_RELTIM_GetCounterMode \n
  *  TCR        RFC2CM      LL_GFXTIM_RELTIM_GetCounterMode
  * @param  gfxtim   GFXTIM instance.
  * @param  counter  This parameter can be one of the following values:
  *                  @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                  @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_RELTIM_COUNTER_ONESHOT
  *         @arg @ref LL_GFXTIM_RELTIM_COUNTER_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_GetCounterMode(const GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  return (READ_BIT(gfxtim->TCR, (counter << 1U)));
}

/**
  * @brief  Set reload value of the relative frame counter.
  * @rmtoll
  *  RFC1RR            FRAME      LL_GFXTIM_RELTIM_SetReloadValue \n
  *  RFC2RR            FRAME      LL_GFXTIM_RELTIM_SetReloadValue
  * @param  gfxtim         GFXTIM instance.
  * @param  counter        This parameter can be one of the following values:
  *                        @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                        @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  * @param  autoreload_val This parameter can be a value between 0x0 and 0xFFF.
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_SetReloadValue(const GFXTIM_TypeDef *gfxtim, uint32_t counter,
                                                     uint32_t autoreload_val)
{
  uint32_t reg_addr = (uint32_t)&gfxtim->RFC1RR;
  MODIFY_REG(*(__IO uint32_t *)(reg_addr + ((POSITION_VAL(counter) - 16U) * 2U)), GFXTIM_RFC1RR_FRAME, autoreload_val);
}

/**
  * @brief  Force reload the relative frame counter.
  * @rmtoll
  *  TCR               FRFC1R      LL_GFXTIM_RELTIM_ForceReloadCounter \n
  *  TCR               FRFC2R      LL_GFXTIM_RELTIM_ForceReloadCounter
  * @param  gfxtim         GFXTIM instance.
  * @param  counter_reload This parameter can be one of the following values:
  *                        @arg @ref LL_GFXTIM_RELTIM_COUNTER_1_FORCE_RELOAD
  *                        @arg @ref LL_GFXTIM_RELTIM_COUNTER_2_FORCE_RELOAD
  *                        @arg @ref LL_GFXTIM_RELTIM_COUNTER_ALL_FORCE_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_ForceReloadCounter(GFXTIM_TypeDef *gfxtim, uint32_t counter_reload)
{
  MODIFY_REG(gfxtim->TCR, (GFXTIM_TCR_FRFC1R | GFXTIM_TCR_FRFC2R), counter_reload);
}

/**
  * @brief  Force reload the relative frame counter 1.
  * @rmtoll
  *  TCR        FRFC1R      LL_GFXTIM_RELTIM_ForceReloadCounter1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_ForceReloadCounter1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_FRFC1R);
}

/**
  * @brief  Force reload the relative frame counter 2.
  * @rmtoll
  *  TCR        FRFC1R      LL_GFXTIM_RELTIM_ForceReloadCounter2
  */
__STATIC_INLINE void LL_GFXTIM_RELTIM_ForceReloadCounter2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->TCR, GFXTIM_TCR_FRFC2R);
}
/**
  * @brief  Get the relative frame counter value.
  * @rmtoll
  *  RFC1R      FRAME      LL_GFXTIM_RELTIM_GetCounterValue \n
  *  RFC2R      FRAME      LL_GFXTIM_RELTIM_GetCounterValue
  * @param  gfxtim  GFXTIM instance.
  * @param  counter This parameter can be one of the following values:
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_1
  *                 @arg @ref LL_GFXTIM_RELTIM_COUNTER_2
  * @retval Value between 0x0 and 0xFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_RELTIM_GetCounterValue(const GFXTIM_TypeDef *gfxtim, uint32_t counter)
{
  uint32_t reg_addr = (uint32_t)&gfxtim->RFC1R;
  return (READ_BIT(*(__IO uint32_t *)(reg_addr + ((POSITION_VAL(counter) - 16U) * 2U)), GFXTIM_RFC1R_FRAME));
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_EVENT_GENERATOR GFXTIM Event generator
  * @{
  */

/**
  * @brief  Configure the event generator.
  * @rmtoll
  *  EVSR        FESx x = [1..4]     LL_GFXTIM_EVENTGEN_Config \n
  *  EVSR        LESx x = [1..4]     LL_GFXTIM_EVENTGEN_Config
  * @param  gfxtim      GFXTIM instance.
  * @param  event_gen   This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  * @param  line_event  This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  * @param  frame_event This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_Config(GFXTIM_TypeDef *gfxtim, uint32_t event_gen, uint32_t line_event,
                                               uint32_t frame_event)
{
  MODIFY_REG(gfxtim->EVSR, ((GFXTIM_EVSR_LES1 | GFXTIM_EVSR_FES1) << (POSITION_VAL(event_gen) * 8U)),
             ((line_event | frame_event) << (POSITION_VAL(event_gen) * 8U)));
}

/**
  * @brief  Configure the line event generator.
  * @rmtoll
  *  EVSR        LESx x = [1..4]     LL_GFXTIM_EVENTGEN_SetLineEventSel
  * @param  gfxtim     GFXTIM instance.
  * @param  event_gen  This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                    @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                    @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                    @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  * @param  line_event This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetLineEventSel(GFXTIM_TypeDef *gfxtim, uint32_t event_gen, uint32_t line_event)
{
  MODIFY_REG(gfxtim->EVSR, (GFXTIM_EVSR_LES1 << (POSITION_VAL(event_gen) * 8U)),
             (line_event << (POSITION_VAL(event_gen) * 8U)));
}

/**
  * @brief  Get line event generator configuration.
  * @rmtoll
  *  EVSR         LESx   x = [1..4]    LL_GFXTIM_EVENTGEN_GetLineEventSel
  * @param  gfxtim   GFXTIM instance.
  * @param  event_gen This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *         @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetLineEventSel(const GFXTIM_TypeDef *gfxtim, uint32_t event_gen)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_LES1 << (POSITION_VAL(event_gen) * 8U)) >> (POSITION_VAL(event_gen) * 8U));
}

/**
  * @brief  Configure the event generator.
  * @rmtoll
  *  EVSR        FESx x = [1..4]     LL_GFXTIM_EVENTGEN_SetFrameEventSel
  * @param  gfxtim      GFXTIM instance.
  * @param  event_gen   This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                     @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  * @param  frame_event This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetFrameEventSel(GFXTIM_TypeDef *gfxtim, uint32_t event_gen,
                                                         uint32_t frame_event)
{
  MODIFY_REG(gfxtim->EVSR, (GFXTIM_EVSR_FES1 << (POSITION_VAL(event_gen) * 8U)),
             (frame_event << (POSITION_VAL(event_gen) * 8U)));
}

/**
  * @brief  Get frame event generator configuration.
  * @rmtoll
  *  EVSR      LESx  LESx x = [1..4]    LL_GFXTIM_EVENTGEN_GetFrameEventSel
  * @param  gfxtim    GFXTIM instance.
  * @param  event_gen This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *         @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *         @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetFrameEventSel(const GFXTIM_TypeDef *gfxtim, uint32_t event_gen)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_FES1 << (POSITION_VAL(event_gen) * 8U)) >> (POSITION_VAL(event_gen) * 8U));
}

/**
  * @brief  Set the line event generator 1.
  * @rmtoll
  *  EVSR        LES1             LL_GFXTIM_EVENTGEN_SetLineEventSel1
  * @param  gfxtim     GFXTIM instance.
  * @param  line_event This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetLineEventSel1(GFXTIM_TypeDef *gfxtim, uint32_t line_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_LES1, (line_event << GFXTIM_EVSR_LES1_Pos));
}

/**
  * @brief  Get line event generator 1.
  * @rmtoll
  *  EVSR        LES1             LL_GFXTIM_EVENTGEN_GetLine1
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *         @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *         @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetLineEventSel1(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_LES1));
}

/**
  * @brief  Set the frame event generator 1.
  * @rmtoll
  *  EVSR        FES1             LL_GFXTIM_EVENTGEN_SetFrameEventSel1
  * @param  gfxtim      GFXTIM instance.
  * @param  frame_event This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetFrameEventSel1(GFXTIM_TypeDef *gfxtim, uint32_t frame_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_FES1, (frame_event << GFXTIM_EVSR_LES1_Pos));
}

/**
  * @brief  Get frame event generator 1.
  * @rmtoll
  *  EVSR        FES1             LL_GFXTIM_EVENTGEN_GetFrame1
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetFrameEventSel1(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_FES1));
}

/**
  * @brief  Set the line event generator 2.
  * @rmtoll
  *  EVSR        LES2             LL_GFXTIM_EVENTGEN_SetLineEventSel2
  * @param  gfxtim     GFXTIM instance.
  * @param  line_event This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetLineEventSel2(GFXTIM_TypeDef *gfxtim, uint32_t line_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_LES2, (line_event << GFXTIM_EVSR_LES2_Pos));
}

/**
  * @brief  Get line event generator 2.
  * @rmtoll
  *  EVSR        LES2             LL_GFXTIM_EVENTGEN_GetLineEventSel2
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetLineEventSel2(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_LES2) >> GFXTIM_EVSR_LES2_Pos);
}

/**
  * @brief  Set the frame event generator 2.
  * @rmtoll
  *  EVSR        FES2             LL_GFXTIM_EVENTGEN_SetFrameEventSel2
  * @param  gfxtim      GFXTIM instance.
  * @param  frame_event This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetFrameEventSel2(GFXTIM_TypeDef *gfxtim, uint32_t frame_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_FES2, (frame_event << GFXTIM_EVSR_LES2_Pos));
}

/**
  * @brief  Get frame event generator 2.
  * @rmtoll
  *  EVSR        FES2             LL_GFXTIM_EVENTGEN_GetFrameEventSel2
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetFrameEventSel2(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_FES2) >> GFXTIM_EVSR_LES2_Pos);
}

/**
  * @brief  Set the line event generator 3.
  * @rmtoll
  *  EVSR        LES3             LL_GFXTIM_EVENTGEN_SetLineEventSel3
  * @param  gfxtim     GFXTIM instance.
  * @param  line_event This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetLineEventSel3(GFXTIM_TypeDef *gfxtim, uint32_t line_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_LES3, (line_event << GFXTIM_EVSR_LES3_Pos));
}

/**
  * @brief  Get line event generator 3.
  * @rmtoll
  *  EVSR        LES3             LL_GFXTIM_EVENTGEN_GetLineEventSel3
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetLineEventSel3(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_LES3) >> GFXTIM_EVSR_LES3_Pos);
}

/**
  * @brief  Set the frame event generator 3.
  * @rmtoll
  *  EVSR        FES3             LL_GFXTIM_EVENTGEN_SetFrameEventSel3
  * @param  gfxtim      GFXTIM instance.
  * @param  frame_event This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetFrameEventSel3(GFXTIM_TypeDef *gfxtim, uint32_t frame_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_FES3, (frame_event << GFXTIM_EVSR_LES3_Pos));
}

/**
  * @brief  Get frame event generator 3.
  * @rmtoll
  *  EVSR        FES3             LL_GFXTIM_EVENTGEN_GetFrameEventSel3
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetFrameEventSel3(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_FES3) >> GFXTIM_EVSR_LES3_Pos);
}

/**
  * @brief  Set the line event generator 4.
  * @rmtoll
  *  EVSR        LES4             LL_GFXTIM_EVENTGEN_SetLineEventSel4
  * @param  gfxtim     GFXTIM instance.
  * @param  line_event This parameter can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetLineEventSel4(GFXTIM_TypeDef *gfxtim, uint32_t line_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_LES4, (line_event << GFXTIM_EVSR_LES4_Pos));
}

/**
  * @brief  Get line event generator 4.
  * @rmtoll
  *  EVSR        LES4             LL_GFXTIM_EVENTGEN_GetLineEventSel4
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                    @arg @ref LL_GFXTIM_EVENTGEN_LINE_NONE
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW
  *                    @arg @ref LL_GFXTIM_EVENTGEN_TEARING_EFFECT
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP
  *                    @arg @ref LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetLineEventSel4(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_LES4) >> GFXTIM_EVSR_LES4_Pos);
}

/**
  * @brief  Set the frame event generator 4.
  * @rmtoll
  *  EVSR        FES4             LL_GFXTIM_EVENTGEN_SetFrameEventSel4
  * @param  gfxtim      GFXTIM instance.
  * @param  frame_event This parameter can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_SetFrameEventSel4(GFXTIM_TypeDef *gfxtim, uint32_t frame_event)
{
  MODIFY_REG(gfxtim->EVSR, GFXTIM_EVSR_FES4, (frame_event << GFXTIM_EVSR_LES4_Pos));
}

/**
  * @brief  Get frame event generator 4.
  * @rmtoll
  *  EVSR        FES4             LL_GFXTIM_EVENTGEN_GetFrameEventSel4
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *                     @arg @ref LL_GFXTIM_EVENTGEN_FRAME_NONE
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW
  *                     @arg @ref LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD
  *                     @arg @ref LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_GetFrameEventSel4(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->EVSR, GFXTIM_EVSR_FES4) >> GFXTIM_EVSR_LES4_Pos);
}

/**
  * @brief  Enable the event generator.
  * @rmtoll
  *  EVCR        EVxEN x = [1..4]     LL_GFXTIM_EVENTGEN_Enable
  * @param  gfxtim    GFXTIM instance.
  * @param  event_gen This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_Enable(GFXTIM_TypeDef *gfxtim, uint32_t event_gen)
{
  SET_BIT(gfxtim->EVCR, event_gen);
}

/**
  * @brief  Disable the event generator.
  * @rmtoll
  *  EVCR        EVxEN x = [1..4]     LL_GFXTIM_EVENTGEN_Disable
  * @param  gfxtim    GFXTIM instance.
  * @param  event_gen This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  */
__STATIC_INLINE void LL_GFXTIM_EVENTGEN_Disable(GFXTIM_TypeDef *gfxtim, uint32_t event_gen)
{
  CLEAR_BIT(gfxtim->EVCR, event_gen);
}

/**
  * @brief  Check that event generator is enabled.
  * @rmtoll
  *  EVCR        EVxEN x = [1..4]      LL_GFXTIM_EVENTGEN_IsEnabled
  * @param  gfxtim    GFXTIM instance.
  * @param  event_gen This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_EVENTGEN_IsEnabled(const GFXTIM_TypeDef *gfxtim, uint32_t event_gen)
{
  return ((READ_BIT(gfxtim->EVCR, event_gen) == (event_gen)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_WATCHDOG_TIMER GFXTIM Watchdog timer
  * @{
  */

/**
  * @brief  Set the watchdog clock source.
  * @rmtoll
  *  WDGTCR        WDGCS     LL_GFXTIM_WDG_SetSource
  * @param  gfxtim GFXTIM instance.
  * @param  source This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_WDG_CLK_LINE_CLK
  *                @arg @ref LL_GFXTIM_WDG_CLK_FRAME_CLK
  *                @arg @ref LL_GFXTIM_WDG_CLK_HSYNC_RISING
  *                @arg @ref LL_GFXTIM_WDG_CLK_HSYNC_FALLING
  *                @arg @ref LL_GFXTIM_WDG_CLK_VSYNC_RISING
  *                @arg @ref LL_GFXTIM_WDG_CLK_VSYNC_FALLING
  *                @arg @ref LL_GFXTIM_WDG_CLK_TE_RISING
  *                @arg @ref LL_GFXTIM_WDG_CLK_TE_FALLING
  *                @arg @ref LL_GFXTIM_WDG_CLK_EVENT_1
  *                @arg @ref LL_GFXTIM_WDG_CLK_EVENT_2
  *                @arg @ref LL_GFXTIM_WDG_CLK_EVENT_3
  *                @arg @ref LL_GFXTIM_WDG_CLK_EVENT_4
  */
__STATIC_INLINE void LL_GFXTIM_WDG_SetSource(GFXTIM_TypeDef *gfxtim, uint32_t source)
{
  MODIFY_REG(gfxtim->WDGTCR, GFXTIM_WDGTCR_WDGCS, source);
}

/**
  * @brief  Get the watchdog source.
  * @rmtoll
  *  WDGTCR        WDGCS     LL_GFXTIM_WDG_GetSource
  * @param  gfxtim GFXTIM instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GFXTIM_WDG_CLK_LINE_CLK
  *         @arg @ref LL_GFXTIM_WDG_CLK_FRAME_CLK
  *         @arg @ref LL_GFXTIM_WDG_CLK_HSYNC_RISING
  *         @arg @ref LL_GFXTIM_WDG_CLK_HSYNC_FALLING
  *         @arg @ref LL_GFXTIM_WDG_CLK_VSYNC_RISING
  *         @arg @ref LL_GFXTIM_WDG_CLK_VSYNC_FALLING
  *         @arg @ref LL_GFXTIM_WDG_CLK_TE_RISING
  *         @arg @ref LL_GFXTIM_WDG_CLK_TE_FALLING
  *         @arg @ref LL_GFXTIM_WDG_CLK_EVENT_1
  *         @arg @ref LL_GFXTIM_WDG_CLK_EVENT_2
  *         @arg @ref LL_GFXTIM_WDG_CLK_EVENT_3
  *         @arg @ref LL_GFXTIM_WDG_CLK_EVENT_4
  */
__STATIC_INLINE uint32_t LL_GFXTIM_WDG_GetSource(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->WDGTCR, GFXTIM_WDGTCR_WDGCS));
}

/**
  * @brief  Set the watchdog reload value.
  * @rmtoll
  *  WDGRR        REALOAD     LL_GFXTIM_WDG_SetReloadValue
  * @param  gfxtim     GFXTIM instance.
  * @param  reload_val This parameter can be a value between 0x0 and 0xFFFF
  */
__STATIC_INLINE void LL_GFXTIM_WDG_SetReloadValue(GFXTIM_TypeDef *gfxtim, uint32_t reload_val)
{
  MODIFY_REG(gfxtim->WDGRR, GFXTIM_WDGRR_RELOAD, reload_val);
}

/**
  * @brief  Get the watchdog reload value.
  * @rmtoll
  *  WDGRR        REALOAD     LL_GFXTIM_WDG_GetReloadValue
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_WDG_GetReloadValue(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->WDGRR, GFXTIM_WDGRR_RELOAD));
}

/**
  * @brief  Get the watchdog counter value.
  * @rmtoll
  *  WDGCR        VALUE     LL_GFXTIM_WDG_GetCounter
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_WDG_GetCounter(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->WDGCR, GFXTIM_WDGCR_VALUE));
}

/**
  * @brief  Set the watchdog pre-alarm value.
  * @rmtoll
  *  WDGPAR        PREALARM     LL_GFXTIM_WDG_SetPrealarmValue
  * @param  gfxtim       GFXTIM instance.
  * @param  prealarm_val This parameter can be a value between 0x0 and 0xFFFF
  */
__STATIC_INLINE void LL_GFXTIM_WDG_SetPrealarmValue(GFXTIM_TypeDef *gfxtim, uint32_t prealarm_val)
{
  MODIFY_REG(gfxtim->WDGPAR, GFXTIM_WDGPAR_PREALARM, prealarm_val);
}

/**
  * @brief  Get the watchdog pre-alarm value.
  * @rmtoll
  *  WDGPAR        PREALARM     LL_GFXTIM_WDG_GetPrealarmValue
  * @param  gfxtim GFXTIM instance.
  * @retval Value between 0x0 and 0xFFFF.
  */
__STATIC_INLINE uint32_t LL_GFXTIM_WDG_GetPrealarmValue(const GFXTIM_TypeDef *gfxtim)
{
  return (READ_BIT(gfxtim->WDGPAR, GFXTIM_WDGPAR_PREALARM));
}

/**
  * @brief  Enable the watchdog timer.
  * @rmtoll
  *  WDGTCR        WDGEN    LL_GFXTIM_WDG_Enable
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_WDG_Enable(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->WDGTCR, GFXTIM_WDGTCR_WDGEN);
}

/**
  * @brief  Disable the watchdog timer.
  * @rmtoll
  *  WDGTCR        WDGDIS    LL_GFXTIM_WDG_Disable
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_WDG_Disable(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->WDGTCR, GFXTIM_WDGTCR_WDGDIS);
}

/**
  * @brief  Check that relative frame counter 2 is enabled.
  * @rmtoll
  *  WDGTCR        WDGS      LL_GFXTIM_WDG_IsEnabled
  * @param  gfxtim GFXTIM instance.
  * @retval State of bit (1UL or 0UL).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_WDG_IsEnabled(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->WDGTCR, GFXTIM_WDGTCR_WDGS) == (GFXTIM_WDGTCR_WDGS)) ? 1UL : 0UL);
}

/**
  * @brief  Refrech the watchdog timer.
  * @rmtoll
  *  WDGTCR        FWDGR    LL_GFXTIM_WDG_Refresh
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_WDG_Refresh(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->WDGTCR, GFXTIM_WDGTCR_FWDGR);
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_IT_MANAGEMENT GFXTIM Interrupt management
  * @{
  */

/**
  * @brief  Enable the specified GFXTIM interrupt.
  * @rmtoll
  *  IER        AFCOIE/ ALCOIE/TEIE/AFCC1IE/ALCC1IE/ALCC2IE              LL_GFXTIM_EnableIT \n
  *             RFC1RIE/RFC2RIE/EV1IE/EV2IE/EV3IE/EV4IE/WDGAIE/WDGPIE    LL_GFXTIM_EnableIT
  * @param  gfxtim    GFXTIM instance.
  * @param  interrupt This parameter can be one or a combination of the following values:
  *                   @arg @ref LL_GFXTIM_NONE_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT
  *                   @arg @ref LL_GFXTIM_TEARING_EFFECT_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_FRAME_COMP_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP1_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP2_IT
  *                   @arg @ref LL_GFXTIM_RELTIM_COUNT_1_IT
  *                   @arg @ref LL_GFXTIM_RELTIM_COUNT_2_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4_IT
  *                   @arg @ref LL_GFXTIM_WDG_PREALARM_IT
  *                   @arg @ref LL_GFXTIM_WDG_ALARM_IT
  *                   @arg @ref LL_GFXTIM_ALL_IT
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT(GFXTIM_TypeDef *gfxtim, uint32_t interrupt)
{
  SET_BIT(gfxtim->IER, interrupt);
}

/**
  * @brief  Disable the specified GFXTIM interrupt.
  * @rmtoll
  *  IER        AFCOIE/ ALCOIE/TEIE/AFCC1IE/ALCC1IE/ALCC2IE              LL_GFXTIM_DisableIT \n
  *             RFC1RIE/RFC2RIE/EV1IE/EV2IE/EV3IE/EV4IE/WDGAIE/WDGPIE    LL_GFXTIM_DisableIT
  * @param  gfxtim    GFXTIM instance.
  * @param  interrupt This parameter can be one or a combination of the following values:
  *                   @arg @ref LL_GFXTIM_NONE_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT
  *                   @arg @ref LL_GFXTIM_TEARING_EFFECT_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_FRAME_COMP_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP1_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP2_IT
  *                   @arg @ref LL_GFXTIM_RELTIM_COUNT_1_IT
  *                   @arg @ref LL_GFXTIM_RELTIM_COUNT_2_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4_IT
  *                   @arg @ref LL_GFXTIM_WDG_PREALARM_IT
  *                   @arg @ref LL_GFXTIM_WDG_ALARM_IT
  *                   @arg @ref LL_GFXTIM_ALL_IT
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT(GFXTIM_TypeDef *gfxtim, uint32_t interrupt)
{
  CLEAR_BIT(gfxtim->IER, interrupt);
}

/**
  * @brief  check if the specified GFXTIM interrupt is enabled.
  * @rmtoll
  *  IER        AFCOIE/ ALCOIE/TEIE/AFCC1IE/ALCC1IE/ALCC2IE              LL_GFXTIM_IsEnabledIT \n
  *  IER        RFC1RIE/RFC2RIE/EV1IE/EV2IE/EV3IE/EV4IE/WDGAIE/WDGPIE    LL_GFXTIM_IsEnabledIT
  * @param  gfxtim   GFXTIM instance.
  * @param interrupt This parameter can be one of the following values:
  *                   @arg @ref LL_GFXTIM_NONE_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT
  *                   @arg @ref LL_GFXTIM_TEARING_EFFECT_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_FRAME_COMP_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP1_IT
  *                   @arg @ref LL_GFXTIM_ABSTIM_LINE_COMP2_IT
  *                   @arg @ref LL_GFXTIM_RELTIM_COUNT_1_IT
  *                   @arg @ref LL_GFXTIM_RELTIM_COUNT_2_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_1_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_2_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_3_IT
  *                   @arg @ref LL_GFXTIM_EVENTGEN_EVENT_4_IT
  *                   @arg @ref LL_GFXTIM_WDG_PREALARM_IT
  *                   @arg @ref LL_GFXTIM_WDG_ALARM_IT
  * @retval State of interrupt (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT(const GFXTIM_TypeDef *gfxtim, uint32_t interrupt)
{
  return ((READ_BIT(gfxtim->IER, interrupt) == (interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the absolute frame counter overflow interrupt.
  * @rmtoll
  *  IER        AFCOIE              LL_GFXTIM_EnableIT_AFCO
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_AFCO(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_AFCOIE);
}

/**
  * @brief  Disable the absolute frame counter overflow interrupt.
  * @rmtoll
  *  IER        AFCOIE              LL_GFXTIM_DisableIT_AFCO
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_AFCO(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_AFCOIE);
}

/**
  * @brief  Check if the absolute frame counter overflow interrupt is enabled.
  * @rmtoll
  *  IER        AFCOIE              LL_GFXTIM_IsEnabledIT_AFCO
  * @param  gfxtim GFXTIM instance.
  * @retval State of AFCO (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_AFCO(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_AFCOIE) == (GFXTIM_IER_AFCOIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the absolute line counter overflow interrupt.
  * @rmtoll
  *  IER        ALCOIE              LL_GFXTIM_EnableIT_ALCO
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_ALCO(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_ALCOIE);
}

/**
  * @brief  Disable the absolute line counter overflow interrupt.
  * @rmtoll
  *  IER        ALCOIE              LL_GFXTIM_DisableIT_ALCO
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_ALCO(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_ALCOIE);
}

/**
  * @brief  Check if the absolute line counter overflow interrupt is enabled.
  * @rmtoll
  *  IER        ALCOIE              LL_GFXTIM_IsEnabledIT_ALCO
  * @param  gfxtim GFXTIM instance.
  * @retval State of ALCO (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_ALCO(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_ALCOIE) == (GFXTIM_IER_ALCOIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the tearing-effect interrupt.
  * @rmtoll
  *  IER        TEIE              LL_GFXTIM_EnableIT_TE
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_TE(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_TEIE);
}

/**
  * @brief  Disable the tearing-effect interrupt.
  * @rmtoll
  *  IER        TEIE              LL_GFXTIM_DisableIT_TE
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_TE(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_TEIE);
}

/**
  * @brief  Check if the tearing-effect interrupt is enabled.
  * @rmtoll
  *  IER        TEIE              LL_GFXTIM_IsEnabledIT_TE
  * @param  gfxtim GFXTIM instance.
  * @retval State of TE (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_TE(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_TEIE) == (GFXTIM_IER_TEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the absolute frame counter compare 1 interrupt.
  * @rmtoll
  *  IER        AFCC1IE              LL_GFXTIM_EnableIT_AFCC1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_AFCC1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_AFCC1IE);
}

/**
  * @brief  Disable the absolute frame counter compare 1 interrupt.
  * @rmtoll
  *  IER        AFCC1IE              LL_GFXTIM_DisableIT_AFCC1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_AFCC1(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_AFCC1IE);
}

/**
  * @brief  Check if the absolute frame counter compare 1 interrupt is enabled.
  * @rmtoll
  *  IER        AFCC1IE              LL_GFXTIM_IsEnabledIT_AFCC1
  * @param  gfxtim GFXTIM instance.
  * @retval State of AFCC1 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_AFCC1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_AFCC1IE) == (GFXTIM_IER_AFCC1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the absolute line counter compare 1 interrupt.
  * @rmtoll
  *  IER        ALCC1IE              LL_GFXTIM_EnableIT_ALCC1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_ALCC1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_ALCC1IE);
}

/**
  * @brief  Disable the absolute line counter compare 1 interrupt.
  * @rmtoll
  *  IER        ALCC1IE              LL_GFXTIM_DisableIT_ALCC1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_ALCC1(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_ALCC1IE);
}

/**
  * @brief  Check if the absolute line counter compare 1 interrupt is enabled.
  * @rmtoll
  *  IER        ALCC1IE              LL_GFXTIM_IsEnabledIT_ALCC1
  * @param  gfxtim GFXTIM instance.
  * @retval State of ALCC1 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_ALCC1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_ALCC1IE) == (GFXTIM_IER_ALCC1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the absolute line counter compare 2 interrupt.
  * @rmtoll
  *  IER        ALCC2IE              LL_GFXTIM_EnableIT_ALCC2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_ALCC2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_ALCC2IE);
}

/**
  * @brief  Disable the absolute line counter compare 2 interrupt.
  * @rmtoll
  *  IER        ALCC2IE              LL_GFXTIM_DisableIT_ALCC2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_ALCC2(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_ALCC2IE);
}

/**
  * @brief  Check if the absolute line counter compare 2 interrupt is enabled.
  * @rmtoll
  *  IER        ALCC2IE              LL_GFXTIM_IsEnabledIT_ALCC2
  * @param  gfxtim GFXTIM instance.
  * @retval State of ALCC2 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_ALCC2(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_ALCC2IE) == (GFXTIM_IER_ALCC2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the relative frame counter 1 reload interrupt.
  * @rmtoll
  *  IER        RFC1RIE              LL_GFXTIM_EnableIT_RFC1R
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_RFC1R(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_RFC1RIE);
}

/**
  * @brief  Disable the relative frame counter 1 reload interrupt.
  * @rmtoll
  *  IER        RFC1RIE              LL_GFXTIM_DisableIT_RFC1R
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_RFC1R(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_RFC1RIE);
}

/**
  * @brief  Check if the relative frame counter 1 reload interrupt is enabled.
  * @rmtoll
  *  IER        RFC1RIE              LL_GFXTIM_IsEnabledIT_RFC1R
  * @param  gfxtim GFXTIM instance.
  * @retval State of RFC1R (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_RFC1R(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_RFC1RIE) == (GFXTIM_IER_RFC1RIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the relative frame counter 2 reload interrupt.
  * @rmtoll
  *  IER        RFC2RIE              LL_GFXTIM_EnableIT_RFC2R
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_RFC2R(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_RFC2RIE);
}

/**
  * @brief  Disable the relative frame counter 2 reload interrupt.
  * @rmtoll
  *  IER        RFC2RIE              LL_GFXTIM_DisableIT_RFC2R
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_RFC2R(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_RFC2RIE);
}

/**
  * @brief  Check if the relative frame counter 2 reload interrupt is enabled.
  * @rmtoll
  *  IER        RFC2RIE              LL_GFXTIM_IsEnabledIT_RFC2R
  * @param  gfxtim GFXTIM instance.
  * @retval State of RFC2R (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_RFC2R(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_RFC2RIE) == (GFXTIM_IER_RFC2RIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the event generator 1 interrupt.
  * @rmtoll
  *  IER        EV1IE              LL_GFXTIM_EnableIT_EV1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_EV1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_EV1IE);
}

/**
  * @brief  Disable the event generator 1 interrupt.
  * @rmtoll
  *  IER        EV1IE              LL_GFXTIM_DisableIT_EV1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_EV1(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_EV1IE);
}

/**
  * @brief  Check if the event generator 1 interrupt is enabled.
  * @rmtoll
  *  IER        EV1IE              LL_GFXTIM_IsEnabledIT_EV1
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV1 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_EV1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_EV1IE) == (GFXTIM_IER_EV1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the event generator 2 interrupt.
  * @rmtoll
  *  IER        EV2IE              LL_GFXTIM_EnableIT_EV2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_EV2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_EV2IE);
}

/**
  * @brief  Disable the event generator 2 interrupt.
  * @rmtoll
  *  IER        EV2IE              LL_GFXTIM_DisableIT_EV2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_EV2(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_EV2IE);
}

/**
  * @brief  Check if the event generator 2 interrupt is enabled.
  * @rmtoll
  *  IER        EV2IE              LL_GFXTIM_IsEnabledIT_EV2
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV2 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_EV2(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_EV2IE) == (GFXTIM_IER_EV2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the event generator 3 interrupt.
  * @rmtoll
  *  IER        EV3IE              LL_GFXTIM_EnableIT_EV3
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_EV3(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_EV3IE);
}

/**
  * @brief  Disable the event generator 3 interrupt.
  * @rmtoll
  *  IER        EV3IE              LL_GFXTIM_DisableIT_EV3
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_EV3(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_EV3IE);
}

/**
  * @brief  Check if the event generator 3 interrupt is enabled.
  * @rmtoll
  *  IER        EV3IE              LL_GFXTIM_IsEnabledIT_EV3
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV3 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_EV3(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_EV3IE) == (GFXTIM_IER_EV3IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the event generator 4 interrupt.
  * @rmtoll
  *  IER        EV4IE              LL_GFXTIM_EnableIT_EV4
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_EV4(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_EV4IE);
}

/**
  * @brief  Disable the event generator 3 interrupt.
  * @rmtoll
  *  IER        EV4IE              LL_GFXTIM_DisableIT_EV4
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_EV4(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_EV4IE);
}

/**
  * @brief  Check if the event generator 3 interrupt is enabled.
  * @rmtoll
  *  IER        EV4IE              LL_GFXTIM_IsEnabledIT_EV4
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV4 (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_EV4(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_EV4IE) == (GFXTIM_IER_EV4IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the watchdog alarm interrupt.
  * @rmtoll
  *  IER        WDGAIE              LL_GFXTIM_EnableIT_WDGA
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_WDGA(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_WDGAIE);
}

/**
  * @brief  Disable the watchdog alarm interrupt.
  * @rmtoll
  *  IER        WDGAIE              LL_GFXTIM_DisableIT_WDGA
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_WDGA(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_WDGAIE);
}

/**
  * @brief  Check if the watchdog alarm interrupt is enabled.
  * @rmtoll
  *  IER        WDGAIE              LL_GFXTIM_IsEnabledIT_WDGA
  * @param  gfxtim GFXTIM instance.
  * @retval State of WDGA (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_WDGA(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_WDGAIE) == (GFXTIM_IER_WDGAIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the watchdog pre-alarm interrupt.
  * @rmtoll
  *  IER        WDGPIE              LL_GFXTIM_EnableIT_WDGP
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_EnableIT_WDGP(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->IER, GFXTIM_IER_WDGPIE);
}

/**
  * @brief  Disable the watchdog pre-alarm interrupt.
  * @rmtoll
  *  IER        WDGPIE              LL_GFXTIM_DisableIT_WDGP
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_DisableIT_WDGP(GFXTIM_TypeDef *gfxtim)
{
  CLEAR_BIT(gfxtim->IER, GFXTIM_IER_WDGPIE);
}

/**
  * @brief  Check if the watchdog pre-alarm interrupt is enabled.
  * @rmtoll
  *  IER        WDGPIE              LL_GFXTIM_IsEnabledIT_WDGP
  * @param  gfxtim GFXTIM instance.
  * @retval State of WDGP (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsEnabledIT_WDGP(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->IER, GFXTIM_IER_WDGPIE) == (GFXTIM_IER_WDGPIE)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup LL_GFXTIM_FLAG_MANAGEMENT GFXTIM Flag management
  * @{
  */

/**
  * @brief  Clear the specified GFXTIM flag.
  * @rmtoll
  *  ICR      CAFCOF/CALCOF/CTEF/CAFCC1F/CALCC1F/CALCC2F               LL_GFXTIM_ClearFlag \n
  *  ICR      CRFC1RF/CRFC2RF/CEV1F/CEV2F/CEV3F/CEV4F/CWDGAF/CWDGPF    LL_GFXTIM_ClearFlag
  * @param  gfxtim GFXTIM instance.
  * @param  flag   This parameter can be one or a combination of the following values:
  *                @arg @ref LL_GFXTIM_FLAG_AFCO   Absolute Frame Counter Overflow Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALCO   Absolute Line Counter Overflow Flag
  *                @arg @ref LL_GFXTIM_FLAG_TE     Tearing Effect Flag
  *                @arg @ref LL_GFXTIM_FLAG_AFCC1  Absolute Frame Counter Compare 1 Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALCC1  Absolute Line Counter Compare 1 Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALCC2  Absolute Line Counter Compare 2 Flag
  *                @arg @ref LL_GFXTIM_FLAG_RFC1R  Relative Frame Counter 1 Reload Flag
  *                @arg @ref LL_GFXTIM_FLAG_RFC2R  Relative Frame Counter 2 Reload Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV1    Event 1 Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV2    Event 2 Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV3    Event 3 Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV4    Event 4 Flag
  *                @arg @ref LL_GFXTIM_FLAG_WDGA   Watchdog Alarm Flag
  *                @arg @ref LL_GFXTIM_FLAG_WDGP   Watchdog Pre-alarm Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALL    All Flags
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag(GFXTIM_TypeDef *gfxtim, uint32_t flag)
{
  WRITE_REG(gfxtim->ICR, flag);
}

/**
  * @brief  Check whether the specified GFXTIM flag is set or not.
  * @rmtoll
  *  ISR      AFCOF/ALCOF/TEF/AFCC1F/ALCC1F/ALCC2F               LL_GFXTIM_IsActiveFlag \n
  *  ISR      RFC1RF/RFC2RF/EV1F/EV2F/EV3F/EV4F/WDGAF/CWDGPF     LL_GFXTIM_IsActiveFlag
  * @param  gfxtim GFXTIM instance.
  * @param  flag   This parameter can be one of the following values:
  *                @arg @ref LL_GFXTIM_FLAG_AFCO   Absolute Frame Counter Overflow Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALCO   Absolute Line Counter Overflow Flag
  *                @arg @ref LL_GFXTIM_FLAG_TE     Tearing Effect Flag
  *                @arg @ref LL_GFXTIM_FLAG_AFCC1  Absolute Frame Counter Compare 1 Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALCC1  Absolute Line Counter Compare 1 Flag
  *                @arg @ref LL_GFXTIM_FLAG_ALCC2  Absolute Line Counter Compare 2 Flag
  *                @arg @ref LL_GFXTIM_FLAG_RFC1R  Relative Frame Counter 1 Reload Flag
  *                @arg @ref LL_GFXTIM_FLAG_RFC2R  Relative Frame Counter 2 Reload Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV1    Event 1 Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV2    Event 2 Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV3    Event 3 Flag
  *                @arg @ref LL_GFXTIM_FLAG_EV4    Event 4 Flag
  *                @arg @ref LL_GFXTIM_FLAG_WDGA   Watchdog Alarm Flag
  *                @arg @ref LL_GFXTIM_FLAG_WDGP   Watchdog Pre-alarm Flag
  * @retval State of flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag(const GFXTIM_TypeDef *gfxtim, uint32_t flag)
{
  return ((READ_BIT(gfxtim->ISR, flag) == (flag)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the absolute frame counter overflow flag.
  * @rmtoll
  *  ICR      CAFCOF               LL_GFXTIM_ClearFlag_AFCO
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_AFCO(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CAFCOF);
}

/**
  * @brief  Check if the absolute frame counter overflow  flag is active.
  * @rmtoll
  *  ISR      AFCOF               LL_GFXTIM_IsActiveFlag_AFCO
  * @param  gfxtim GFXTIM instance.
  * @retval State of AFCO flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_AFCO(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_AFCOF) == (GFXTIM_ISR_AFCOF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the absolute line counter overflow flag.
  * @rmtoll
  *  ICR      CALCOF               LL_GFXTIM_ClearFlag_ALCO
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_ALCO(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CALCOF);
}

/**
  * @brief  Check if the absolute line counter overflow flag is active.
  * @rmtoll
  *  ISR      ALCOF               LL_GFXTIM_IsActiveFlag_ALCO
  * @param  gfxtim GFXTIM instance.
  * @retval State of ALCO flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_ALCO(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_ALCOF) == (GFXTIM_ISR_ALCOF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Tearing-effect flag.
  * @rmtoll
  *  ICR      CTEF               LL_GFXTIM_ClearFlag_TE
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_TE(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CTEF);
}

/**
  * @brief  Check if the Tearing-effect flag is active.
  * @rmtoll
  *  ISR      TEF               LL_GFXTIM_IsActiveFlag_TE
  * @param  gfxtim GFXTIM instance.
  * @retval State of TE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_TE(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_TEF) == GFXTIM_ISR_TEF) ? 1UL : 0UL);
}

/**
  * @brief  Clear the absolute frame counter compare 1 flag.
  * @rmtoll
  *  ICR      CAFCC1F               LL_GFXTIM_ClearFlag_AFCC1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_AFCC1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CAFCC1F);
}

/**
  * @brief  Check if the absolute frame counter compare 1 flag is active.
  * @rmtoll
  *  ISR      AFCC1F               LL_GFXTIM_IsActiveFlag_AFCC1
  * @param  gfxtim GFXTIM instance.
  * @retval State of AFCC1 flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_AFCC1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_AFCC1F) == (GFXTIM_ISR_AFCC1F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the absolute line counter compare 1 flag.
  * @rmtoll
  *  ICR      CALCC1F               LL_GFXTIM_ClearFlag_ALCC1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_ALCC1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CALCC1F);
}

/**
  * @brief  Check if the absolute line counter compare 1 flag is active.
  * @rmtoll
  *  ISR      ALCC1F               LL_GFXTIM_IsActiveFlag_ALCC1
  * @param  gfxtim GFXTIM instance.
  * @retval State of ALCC1F flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_ALCC1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_ALCC1F) == (GFXTIM_ISR_ALCC1F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the absolute line counter compare 2 flag.
  * @rmtoll
  *  ICR      CALCC2F               LL_GFXTIM_ClearFlag_ALCC2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_ALCC2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CALCC2F);
}

/**
  * @brief  Check if the absolute line counter compare 2 flag is active.
  * @rmtoll
  *  ISR      ALCC2F               LL_GFXTIM_IsActiveFlag_ALCC2
  * @param  gfxtim GFXTIM instance.
  * @retval State of ALCC2F flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_ALCC2(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_ALCC2F) == (GFXTIM_ISR_ALCC2F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the relative frame counter 1 reload flag.
  * @rmtoll
  *  ICR      CRFC1RF               LL_GFXTIM_ClearFlag_RFC1R
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_RFC1R(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CRFC1RF);
}

/**
  * @brief  Check if the relative frame counter 1 reload flag is active.
  * @rmtoll
  *  ISR      RFC1RF               LL_GFXTIM_IsActiveFlag_RFC1R
  * @param  gfxtim GFXTIM instance.
  * @retval State of RFC1RF flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_RFC1R(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_RFC1RF) == (GFXTIM_ISR_RFC1RF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the relative frame counter 2 reload flag.
  * @rmtoll
  *  ICR      CRFC2RF               LL_GFXTIM_ClearFlag_RFC2R
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_RFC2R(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CRFC2RF);
}

/**
  * @brief  Check if the relative frame counter 1 reload flag is active.
  * @rmtoll
  *  ISR      RFC2RF               LL_GFXTIM_IsActiveFlag_RFC2R
  * @param  gfxtim GFXTIM instance.
  * @retval State of RFC2RF flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_RFC2R(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_RFC2RF) == (GFXTIM_ISR_RFC2RF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the event generator 1 flag.
  * @rmtoll
  *  ICR      CEV1F               LL_GFXTIM_ClearFlag_EV1
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_EV1(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CEV1F);
}

/**
  * @brief  Check if the event generator 1 flag is active.
  * @rmtoll
  *  ISR      EV1F               LL_GFXTIM_IsActiveFlag_EV1
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV1F flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_EV1(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_EV1F) == (GFXTIM_ISR_EV1F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the event generator 2 flag.
  * @rmtoll
  *  ICR      CEV2F               LL_GFXTIM_ClearFlag_EV2
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_EV2(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CEV2F);
}

/**
  * @brief  Check if the event generator 2 flag is active.
  * @rmtoll
  *  ISR      EV2F               LL_GFXTIM_IsActiveFlag_EV2
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV2F flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_EV2(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_EV2F) == (GFXTIM_ISR_EV2F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the event generator 3 flag.
  * @rmtoll
  *  ICR      CEV3F               LL_GFXTIM_ClearFlag_EV3
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_EV3(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CEV3F);
}

/**
  * @brief  Check if the event generator 3 flag is active.
  * @rmtoll
  *  ISR      EV3F               LL_GFXTIM_IsActiveFlag_EV3
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV3F flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_EV3(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_EV3F) == (GFXTIM_ISR_EV3F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the event generator 4 flag.
  * @rmtoll
  *  ICR      CEV4F               LL_GFXTIM_ClearFlag_EV4
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_EV4(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CEV4F);
}

/**
  * @brief  Check if the event generator 4 flag is active.
  * @rmtoll
  *  ISR      EV4F               LL_GFXTIM_IsActiveFlag_EV4
  * @param  gfxtim GFXTIM instance.
  * @retval State of EV4F flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_EV4(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_EV4F) == (GFXTIM_ISR_EV4F)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the watchdog alarm flag.
  * @rmtoll
  *  ICR      CWDGAF               LL_GFXTIM_ClearFlag_WDGA
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_WDGA(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CWDGAF);
}

/**
  * @brief  Check if the watchdog alarm flag is active.
  * @rmtoll
  *  ISR      WDGAF               LL_GFXTIM_IsActiveFlag_WDGA
  * @param  gfxtim GFXTIM instance.
  * @retval State of WDGAF flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_WDGA(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_WDGAF) == (GFXTIM_ISR_WDGAF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the watchdog pre-alarm flag.
  * @rmtoll
  *  ICR      CWDGPF               LL_GFXTIM_ClearFlag_WDGP
  * @param  gfxtim GFXTIM instance.
  */
__STATIC_INLINE void LL_GFXTIM_ClearFlag_WDGP(GFXTIM_TypeDef *gfxtim)
{
  SET_BIT(gfxtim->ICR, GFXTIM_ICR_CWDGPF);
}

/**
  * @brief  Check if the watchdog pre-alarm flag is active.
  * @rmtoll
  *  ISR      WDGPF               LL_GFXTIM_IsActiveFlag_WDGP
  * @param  gfxtim GFXTIM instance.
  * @retval State of WDGPF flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_GFXTIM_IsActiveFlag_WDGP(const GFXTIM_TypeDef *gfxtim)
{
  return ((READ_BIT(gfxtim->ISR, GFXTIM_ISR_WDGPF) == (GFXTIM_ISR_WDGPF)) ? 1UL : 0UL);
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

/**
  * @}
  */

#endif /* defined (GFXTIM) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_GFXTIM_H */
