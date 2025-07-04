/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_lptim.h
  * @brief   Header file of LPTIM LL module.
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
#ifndef STM32U5xx_LL_LPTIM_H
#define STM32U5xx_LL_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */
/** @defgroup LPTIM_LL LPTIM
  * @{
  */
#if defined (LPTIM1) || defined (LPTIM2) || defined (LPTIM3) || defined (LPTIM4)

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup LPTIM_LL_Private_variables LPTIM Private variables
  * @{
  */


static const uint8_t LL_LPTIM_SHIFT_TAB_CCxx[] =
{
  0U,                              /* CC1P */
  16U                              /* CC2P */
};

static const uint8_t LL_LPTIM_SHIFT_TAB_CCxP[] =
{
  0U,                              /* CC1P */
  16U                              /* CC2P */
};

static const uint8_t LL_LPTIM_SHIFT_TAB_ICxF[] =
{
  0U,                              /* IC1F */
  16U                              /* IC2F */
};

static const uint8_t LL_LPTIM_SHIFT_TAB_ICxPSC[] =
{
  0U,                              /* IC1PSC */
  16U                              /* IC2PSC */
};

static const uint8_t LL_LPTIM_SHIFT_TAB_CCxSEL[] =
{
  0U,                              /* CC1SEL */
  16U                              /* CC2SEL */
};

static const uint8_t LL_LPTIM_SHIFT_TAB_CCxE[] =
{
  LPTIM_CCMR1_CC1E_Pos,            /* CC1E */
  LPTIM_CCMR1_CC2E_Pos             /* CC2E */
};

/**
  * @}
  */

/* Private constants -------------------------------------------------------------------------------------------------*/

/* Private macros ----------------------------------------------------------------------------------------------------*/

/* Exported types ----------------------------------------------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup LPTIM_LL_Exported_Constants LPTIM Exported Constants
  * @{
  */
/** @defgroup LPTIM_LL_EC_TIMEOUT_ENABLE  Timeout Enable
  * @brief Alias for the TIMOUT bit in CFGR.
  * @{
  */
#define LL_LPTIM_TIMEOUT_ENABLE  LPTIM_CFGR_TIMOUT
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_LPTIM_READREG function
  * @{
  */
#define LL_LPTIM_ISR_CMP1OK                   LPTIM_ISR_CMP1OK   /*!< Compare register 1 update OK        */
#define LL_LPTIM_ISR_CMP2OK                   LPTIM_ISR_CMP2OK   /*!< Compare register 2 update OK        */
#define LL_LPTIM_ISR_CC1IF                    LPTIM_ISR_CC1IF    /*!< Capture/Compare 1 interrupt flag    */
#define LL_LPTIM_ISR_CC2IF                    LPTIM_ISR_CC2IF    /*!< Capture/Compare 2 interrupt flag    */

#define LL_LPTIM_ISR_CC1OF                    LPTIM_ISR_CC1OF    /*!< Capture/Compare 1 over-capture flag */
#define LL_LPTIM_ISR_CC2OF                    LPTIM_ISR_CC2OF    /*!< Capture/Compare 2 over-capture flag */

#define LL_LPTIM_ISR_DIEROK                   LPTIM_ISR_DIEROK   /*!< Interrupt enable register update OK */
#define LL_LPTIM_ISR_ARRM                     LPTIM_ISR_ARRM     /*!< Autoreload match                    */
#define LL_LPTIM_ISR_EXTTRIG                  LPTIM_ISR_EXTTRIG  /*!< External trigger edge event         */
#define LL_LPTIM_ISR_ARROK                    LPTIM_ISR_ARROK    /*!< Autoreload register update OK       */
#define LL_LPTIM_ISR_UP                       LPTIM_ISR_UP       /*!< Counter direction change down to up */
#define LL_LPTIM_ISR_DOWN                     LPTIM_ISR_DOWN     /*!< Counter direction change up to down */
#define LL_LPTIM_ISR_UE                       LPTIM_ISR_UE       /*!< Update event                        */
#define LL_LPTIM_ISR_REPOK                    LPTIM_ISR_REPOK    /*!< Repetition register update OK       */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_LPTIM_READREG and  LL_LPTIM_WRITE_REG functions
  * @{
  */
#define LL_LPTIM_DIER_CMP1OKIE                 LPTIM_DIER_CMP1OKIE   /*!< Compare register 1 update OK        */
#define LL_LPTIM_DIER_CMP2OKIE                 LPTIM_DIER_CMP2OKIE   /*!< Compare register 2 update OK        */
#define LL_LPTIM_DIER_CC1IE                    LPTIM_DIER_CC1IE      /*!< Capture/Compare 1 interrupt flag    */
#define LL_LPTIM_DIER_CC2IE                    LPTIM_DIER_CC2IE      /*!< Capture/Compare 2 interrupt flag    */
#define LL_LPTIM_DIER_CC1OFIE                  LPTIM_DIER_CC1OIE     /*!< Capture/Compare 1 over-capture flag */
#define LL_LPTIM_DIER_CC2OFIE                  LPTIM_DIER_CC2OIE     /*!< Capture/Compare 2 over-capture flag */
#define LL_LPTIM_DIER_ARRMIE                   LPTIM_DIER_ARRMIE     /*!< Autoreload match                    */
#define LL_LPTIM_DIER_EXTTRIGIE                LPTIM_DIER_EXTTRIGIE  /*!< External trigger edge event         */
#define LL_LPTIM_DIER_ARROKIE                  LPTIM_DIER_ARROKIE    /*!< Autoreload register update OK       */
#define LL_LPTIM_DIER_UPIE                     LPTIM_DIER_UPIE       /*!< Counter direction change down to up */
#define LL_LPTIM_DIER_DOWNIE                   LPTIM_DIER_DOWNIE     /*!< Counter direction change up to down */
#define LL_LPTIM_DIER_UEIE                     LPTIM_DIER_UEIE       /*!< Update event                        */
#define LL_LPTIM_DIER_REPOKIE                  LPTIM_DIER_REPOKIE    /*!< Repetition register update OK       */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_DMA DMA Defines
  * @brief
  * @{
  */
#define LL_LPTIM_DIER_UEDE    LPTIM_DIER_UEDE
#define LL_LPTIM_DIER_CC1DE   LPTIM_DIER_CC1DE
#define LL_LPTIM_DIER_CC2DE   LPTIM_DIER_CC2DE
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_OPERATING_MODE Operating Mode
  * @{
  */
#define LL_LPTIM_OPERATING_MODE_CONTINUOUS    LPTIM_CR_CNTSTRT /*!<LP Timer starts in continuous mode*/
#define LL_LPTIM_OPERATING_MODE_ONESHOT       LPTIM_CR_SNGSTRT /*!<LP Timer starts in single mode   */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_UPDATE_MODE Update Mode
  * @{
  */
#define LL_LPTIM_PRELOAD_DISABLED        0x00000000U        /*!<Preload is disabled: registers are updated
                                                                     after each APB bus write access     */
#define LL_LPTIM_PRELOAD_ENABLED      LPTIM_CFGR_PRELOAD /*!<Preload is enabled: registers are updated at
                                                                     the end of the current LPTIM period */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_COUNTER_MODE Counter Mode
  * @{
  */
#define LL_LPTIM_COUNTER_MODE_INTERNAL        0x00000000U          /*!<The counter is incremented following each
                                                                       internal clock pulse                          */
#define LL_LPTIM_COUNTER_MODE_EXTERNAL        LPTIM_CFGR_COUNTMODE /*!<The counter is incremented following each
                                                                       valid clock pulse on the LPTIM external Input1*/
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_OC_WAVEFORM Output Waveform Type
  * @{
  */
#define LL_LPTIM_OC_WAVEFORM_PWM          0x00000000U     /*!<LPTIM  generates either a PWM waveform or a One pulse
                                                                  waveform depending on chosen operating mode CONTINUOUS
                                                                  or SINGLE                            */
#define LL_LPTIM_OC_WAVEFORM_SETONCE      LPTIM_CFGR_WAVE /*!<LPTIM  generates a Set Once waveform */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_OUTPUT_POLARITY Output Polarity
  * @{
  */
#define LL_LPTIM_OCPOLARITY_HIGH      0x00000000U        /*!<The LPTIM output reflects the compare results
                                                                     between LPTIMx_ARR and LPTIMx_CCRx registers */
#define LL_LPTIM_OCPOLARITY_LOW      LPTIM_CCMR1_CC1P_0 /*!<The LPTIM output reflects the inverse of the
                                                                     compare results between LPTIMx_ARR and LPTIMx_CCx
                                                                     registers                                    */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CHANNEL Channel
  * @{
  */
#define LL_LPTIM_CHANNEL_CH1                  0x00000000U     /*!< LPTIM input/output channel 1 */
#define LL_LPTIM_CHANNEL_CH2                  0x00000001U     /*!< LPTIM input/output channel 2 */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_LPTIM_IC_PRESCALER Input Capture Prescaler
  * @{
  */
#define LL_LPTIM_ICPSC_DIV1                   0x00000000UL                                /*!< Capture performed each
                                                                                               time an edge is detected
                                                                                               on the capture input */
#define LL_LPTIM_ICPSC_DIV2                   LPTIM_CCMR1_IC1PSC_0                        /*!< Capture performed once
                                                                                               every 2 events       */
#define LL_LPTIM_ICPSC_DIV4                   LPTIM_CCMR1_IC1PSC_1                        /*!< Capture performed once
                                                                                               every 4 events       */
#define LL_LPTIM_ICPSC_DIV8                   (LPTIM_CCMR1_IC1PSC_0|LPTIM_CCMR1_IC1PSC_1) /*!< Capture performed once
                                                                                               every 8 events       */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_LPTIM_IC_FILTER Input Capture Filter
  * @{
  */
#define LL_LPTIM_ICFLT_CLOCK_DIV1             0x00000000UL                            /*!< any external input capture
                                                                                           signal level change is
                                                                                           considered as a valid
                                                                                           transition       */
#define LL_LPTIM_ICFLT_CLOCK_DIV2             LPTIM_CCMR1_IC1F_0                      /*!< external input capture signal
                                                                                           level change must be stable
                                                                                           for at least 2 clock periods
                                                                                           before it is considered as
                                                                                           valid transition */
#define LL_LPTIM_ICFLT_CLOCK_DIV4             LPTIM_CCMR1_IC1F_1                      /*!< external input capture signal
                                                                                           level change must be stable
                                                                                           for at least 4 clock periods
                                                                                           before it is considered as
                                                                                           valid transition */
#define LL_LPTIM_ICFLT_CLOCK_DIV8             (LPTIM_CCMR1_IC1F_0|LPTIM_CCMR1_IC1F_1) /*!< external input capture signal
                                                                                           level change must be stable
                                                                                           for at least 8 clock periods
                                                                                           before it is considered as
                                                                                           valid transition */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_LPTIM_IC_POLARITY  Input Capture Polarity
  * @{
  */
#define LL_LPTIM_ICPOLARITY_RISING            0x00000000UL                            /*!< Capture/Compare input rising
                                                                                           polarity               */
#define LL_LPTIM_ICPOLARITY_FALLING           LPTIM_CCMR1_CC1P_0                      /*!< Capture/Compare input falling
                                                                                           polarity               */
#define LL_LPTIM_ICPOLARITY_RISING_FALLING    (LPTIM_CCMR1_CC1P_0|LPTIM_CCMR1_CC1P_1) /*!< Capture/Compare input rising
                                                                                           and falling polarities */
/**
  * @}
  */
/** @defgroup LPTIM_LL_EC_LPTIM_IC_Selection  Input Capture selection
  * @{
  */
#define LL_LPTIM_CCMODE_OUTPUT_PWM            0x00000000UL                              /*!< Select PWM mode          */
#define LL_LPTIM_CCMODE_INPUTCAPTURE          LPTIM_CCMR1_CC1SEL                        /*!< Select Input Capture mode*/
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_PRESCALER Prescaler Value
  * @{
  */
#define LL_LPTIM_PRESCALER_DIV1               0x00000000U                               /*!<Prescaler division factor
                                                                                            is set to 1   */
#define LL_LPTIM_PRESCALER_DIV2               LPTIM_CFGR_PRESC_0                        /*!<Prescaler division factor
                                                                                            is set to 2   */
#define LL_LPTIM_PRESCALER_DIV4               LPTIM_CFGR_PRESC_1                        /*!<Prescaler division factor
                                                                                            is set to 4   */
#define LL_LPTIM_PRESCALER_DIV8               (LPTIM_CFGR_PRESC_1 | LPTIM_CFGR_PRESC_0) /*!<Prescaler division factor
                                                                                            is set to 8   */
#define LL_LPTIM_PRESCALER_DIV16              LPTIM_CFGR_PRESC_2                        /*!<Prescaler division factor
                                                                                            is set to 16  */
#define LL_LPTIM_PRESCALER_DIV32              (LPTIM_CFGR_PRESC_2 | LPTIM_CFGR_PRESC_0) /*!<Prescaler division factor
                                                                                            is set to 32  */
#define LL_LPTIM_PRESCALER_DIV64              (LPTIM_CFGR_PRESC_2 | LPTIM_CFGR_PRESC_1) /*!<Prescaler division factor
                                                                                            is set to 64  */
#define LL_LPTIM_PRESCALER_DIV128             LPTIM_CFGR_PRESC                          /*!<Prescaler division factor
                                                                                            is set to 128 */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_TRIG_SOURCE Trigger Source
  * @{
  */

#define LL_LPTIM_TRIG_SOURCE_GPIO             0x00000000U                                                 /*!<External input trigger is connected to TIMx_ETR input*/
#define LL_LPTIM_TRIG_SOURCE_RTCALARMA        LPTIM_CFGR_TRIGSEL_0                                        /*!<External input trigger is connected to RTC Alarm A*/
#define LL_LPTIM_TRIG_SOURCE_RTCALARMB        LPTIM_CFGR_TRIGSEL_1                                        /*!<External input trigger is connected to RTC Alarm B*/
#define LL_LPTIM_TRIG_SOURCE_RTCTAMP1         (LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_0)               /*!<External input trigger is connected to RTC Tamper 1*/
#define LL_LPTIM_TRIG_SOURCE_RTCTAMP2         LPTIM_CFGR_TRIGSEL_2                                        /*!<External input trigger is connected to RTC Tamper 2*/
#define LL_LPTIM_TRIG_SOURCE_RTCTAMP3         (LPTIM_CFGR_TRIGSEL_2 | LPTIM_CFGR_TRIGSEL_0)               /*!<External input trigger is connected to RTC Tamper 3*/
#define LL_LPTIM_TRIG_SOURCE_COMP1            (LPTIM_CFGR_TRIGSEL_2 | LPTIM_CFGR_TRIGSEL_1)               /*!<External input trigger is connected to COMP1 output*/
#define LL_LPTIM_TRIG_SOURCE_COMP2            LPTIM_CFGR_TRIGSEL                                          /*!<External input trigger is connected to COMP2 output*/
#define LL_LPTIM_TRIG_SOURCE_LPDMA_CH0_TCF    (LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_0)               /*!<External input trigger is connected to LPDMA CH0 transfer complete */
#define LL_LPTIM_TRIG_SOURCE_LPDMA_CH1_TCF    LPTIM_CFGR_TRIGSEL_2                                        /*!<External input trigger is connected to LPDMA CH1 transfer complete */
#define LL_LPTIM_TRIG_SOURCE_LPDMA_CH2_TCF    (LPTIM_CFGR_TRIGSEL_2 | LPTIM_CFGR_TRIGSEL_0)               /*!<External input trigger is connected to LPDMA CH2 transfer complete */
#define LL_LPTIM_TRIG_SOURCE_GPDMA_CH0_TCF    LPTIM_CFGR_TRIGSEL_2                                        /*!<External input trigger is connected to GPDMA CH0 transfer complete */
#define LL_LPTIM_TRIG_SOURCE_GPDMA_CH4_TCF    (LPTIM_CFGR_TRIGSEL_2 | LPTIM_CFGR_TRIGSEL_0)               /*!<External input trigger is connected to GPDMA CH4 transfer complete */

/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_TRIG_FILTER Trigger Filter
  * @{
  */
#define LL_LPTIM_TRIG_FILTER_NONE             0x00000000U         /*!<Any trigger active level change is considered
                                                                      as a valid trigger */
#define LL_LPTIM_TRIG_FILTER_2                LPTIM_CFGR_TRGFLT_0 /*!<Trigger active level change must be stable for
                                                                      at least 2 clock periods before it is considered
                                                                      as valid trigger */
#define LL_LPTIM_TRIG_FILTER_4                LPTIM_CFGR_TRGFLT_1 /*!<Trigger active level change must be stable for at
                                                                      least 4 clock periods before it is considered
                                                                      as valid trigger */
#define LL_LPTIM_TRIG_FILTER_8                LPTIM_CFGR_TRGFLT   /*!<Trigger active level change must be stable for at
                                                                      least 8 clock periods before it is considered as
                                                                      valid trigger */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_TRIG_POLARITY Trigger Polarity
  * @{
  */
#define LL_LPTIM_TRIG_POLARITY_RISING         LPTIM_CFGR_TRIGEN_0 /*!<LPTIM counter starts when
                                                                      a rising edge is detected              */
#define LL_LPTIM_TRIG_POLARITY_FALLING        LPTIM_CFGR_TRIGEN_1 /*!<LPTIM counter starts when
                                                                      a falling edge is detected             */
#define LL_LPTIM_TRIG_POLARITY_RISING_FALLING LPTIM_CFGR_TRIGEN   /*!<LPTIM counter starts when
                                                                      a rising or a falling edge is detected */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_CLK_SOURCE Clock Source
  * @{
  */
#define LL_LPTIM_CLK_SOURCE_INTERNAL          0x00000000U      /*!<LPTIM is clocked by internal clock source
                                                                   (APB clock or any of the embedded oscillators) */
#define LL_LPTIM_CLK_SOURCE_EXTERNAL          LPTIM_CFGR_CKSEL /*!<LPTIM is clocked by an external clock source through
                                                                   the LPTIM external Input1*/
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_CLK_FILTER Clock Filter
  * @{
  */
#define LL_LPTIM_CLK_FILTER_NONE              0x00000000U        /*!<Any external clock signal level change is
                                                                     considered as a valid transition */
#define LL_LPTIM_CLK_FILTER_2                 LPTIM_CFGR_CKFLT_0 /*!<External clock signal level change must be stable
                                                                     for at least 2 clock periods before it is
                                                                     considered as valid transition   */
#define LL_LPTIM_CLK_FILTER_4                 LPTIM_CFGR_CKFLT_1 /*!<External clock signal level change must be stable
                                                                     for at least 4 clock periods before it is
                                                                     considered as valid transition   */
#define LL_LPTIM_CLK_FILTER_8                 LPTIM_CFGR_CKFLT   /*!<External clock signal level change must be stable
                                                                     for at least 8 clock periods before it is
                                                                     considered as valid transition   */
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_CLK_POLARITY Clock Polarity
  * @{
  */
#define LL_LPTIM_CLK_POLARITY_RISING          0x00000000U        /*!< The rising edge is the active
                                                                      edge used for counting*/
#define LL_LPTIM_CLK_POLARITY_FALLING         LPTIM_CFGR_CKPOL_0 /*!< The falling edge is the active
                                                                      edge used for counting*/
#define LL_LPTIM_CLK_POLARITY_RISING_FALLING  LPTIM_CFGR_CKPOL_1 /*!< Both edges are active edges*/
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_ENCODER_MODE Encoder Mode
  * @{
  */
#define LL_LPTIM_ENCODER_MODE_RISING          0x00000000U        /*!< The rising edge is the active
                                                                      edge used for counting     */
#define LL_LPTIM_ENCODER_MODE_FALLING         LPTIM_CFGR_CKPOL_0 /*!< The falling edge is the active
                                                                      edge used for counting     */
#define LL_LPTIM_ENCODER_MODE_RISING_FALLING  LPTIM_CFGR_CKPOL_1 /*!< Both edges are active edges*/
/**
  * @}
  */

/** @defgroup LPTIM_LL_EC_ENCODER_MODE_ENABLE Encoder Mode Enable
  * @{
  */
#define LL_LPTIM_ENCODER_MODE_ENABLE         LPTIM_CFGR_ENC
#define LL_LPTIM_ENCODER_MODE_DISABLE        (~LL_LPTIM_ENCODER_MODE_ENABLE)
/**
  * @}
  */

/** @defgroup LPTIM_EC_INPUT1_SRC Input1 Source
  * @{
  */
#define LL_LPTIM_INPUT1_SRC_GPIO         0x00000000UL                 /*!< For LPTIM1, LPTIM2, LPTIM3 and LPTIM4 */
#define LL_LPTIM_INPUT1_SRC_COMP1        LPTIM_CFGR2_IN1SEL_0         /*!< For LPTIM1, LPTIM2, LPTIM3 and LPTIM4 */

/**
  * @}
  */

/** @defgroup LPTIM_EC_INPUT2_SRC Input2 Source
  * @{
  */
#define LL_LPTIM_INPUT2_SRC_GPIO         0x00000000UL                 /*!< For LPTIM1 and LPTIM2 */
#define LL_LPTIM_INPUT2_SRC_COMP2        LPTIM_CFGR2_IN2SEL_0         /*!< For LPTIM1 and LPTIM2 */

/**
  * @}
  */

/** @defgroup LPTIM_EC_LPTIM1_IC1_RMP LPTIM1 Input Ch1 Remap
  * @{
  */
#define LL_LPTIM_LPTIM1_IC1_RMP_GPIO     0x00000000UL                 /*!< IC1 connected to GPIO */
#define LL_LPTIM_LPTIM1_IC1_RMP_COMP1    LPTIM_CFGR2_IC1SEL_0         /*!< IC1 connected to COMP1 */
#define LL_LPTIM_LPTIM1_IC1_RMP_COMP2    LPTIM_CFGR2_IC1SEL_1         /*!< IC1 connected to COMP2 */

/**
  * @}
  */

/** @defgroup LPTIM_EC_LPTIM1_IC2_RMP LPTIM1 Input Ch2 Remap
  * @{
  */
#define LL_LPTIM_LPTIM1_IC2_RMP_GPIO      0x00000000UL                 /*!< IC2 connected to GPIO */
#define LL_LPTIM_LPTIM1_IC2_RMP_LSI       LPTIM_CFGR2_IC2SEL_0         /*!< IC2 connected to LSI */
#define LL_LPTIM_LPTIM1_IC2_RMP_LSE       LPTIM_CFGR2_IC2SEL_1         /*!< IC2 connected to LSE */

/**
  * @}
  */

/** @defgroup LPTIM_EC_LPTIM2_IC1_RMP LPTIM2 Input Ch1 Remap
  * @{
  */
#define LL_LPTIM_LPTIM2_IC1_RMP_GPIO     0x00000000UL                 /*!< IC1 connected to GPIO */
#define LL_LPTIM_LPTIM2_IC1_RMP_COMP1    LPTIM_CFGR2_IC1SEL_0         /*!< IC1 connected to COMP1 */
#define LL_LPTIM_LPTIM2_IC1_RMP_COMP2    LPTIM_CFGR2_IC1SEL_1         /*!< IC1 connected to COMP2 */
/**
  * @}
  */

/** @defgroup LPTIM_EC_LPTIM2_IC2_RMP LPTIM2 Input Ch2 Remap
  * @{
  */
#define LL_LPTIM_LPTIM2_IC2_RMP_GPIO     0x00000000UL                /*!< IC2 connected to GPIO */
#define LL_LPTIM_LPTIM2_IC2_RMP_HSI      LPTIM_CFGR2_IC2SEL_0        /*!< IC2 connected to HSI */
#define LL_LPTIM_LPTIM2_IC2_RMP_MSIS_1024 LPTIM_CFGR2_IC2SEL_1       /*!< IC2 connected to MSIS/1024 */
#define LL_LPTIM_LPTIM2_IC2_RMP_MSIS_4    \
  (LPTIM_CFGR2_IC2SEL_1|LPTIM_CFGR2_IC2SEL_0)                /*!< IC2 connected to MSIS/4 */
/**
  * @}
  */

/** @defgroup LPTIM_EC_LPTIM3_IC1_RMP LPTIM3 Input Ch1 Remap
  * @{
  */
#define LL_LPTIM_LPTIM3_IC1_RMP_GPIO     0x00000000UL               /*!< IC1 connected to GPIO */
#define LL_LPTIM_LPTIM3_IC1_RMP_COMP1    LPTIM_CFGR2_IC1SEL_0       /*!< IC1 connected to COMP1 */
#define LL_LPTIM_LPTIM3_IC1_RMP_COMP2    LPTIM_CFGR2_IC1SEL_1       /*!< IC1 connected to COMP2 */
/**
  * @}
  */

/** @defgroup LPTIM_EC_LPTIM3_IC2_RMP LPTIM3 Input Ch2 Remap
  * @{
  */
#define LL_LPTIM_LPTIM3_IC2_RMP_GPIO     0x00000000UL                            /*!< IC2 connected to GPIO */
/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPTIM_LL_Exported_Macros LPTIM Exported Macros
  * @{
  */


/** @defgroup LPTIM_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in LPTIM register.
  * @param  instance LPTIM Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_LPTIM_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in LPTIM register.
  * @param  instance LPTIM Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_LPTIM_READ_REG(instance, reg) READ_REG((instance)->reg)


/**
  * @brief  LPTimer Input Capture Get Offset(in counter step unit)
  * @note   The real capture value corresponding to the input capture trigger can be calculated using
  *         the formula hereafter : Real capture value = captured(LPTIM_CCRx) - offset
  *         The Offset value is depending on the glitch filter value for the channel
  *         and the value of the prescaler for the kernel clock.
  *         Please check Errata Sheet V1_8 for more details under "variable latency
  *         on input capture channel" section.
  * @param  __PSC__ This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_PRESCALER_DIV1
  *         @arg @ref LL_LPTIM_PRESCALER_DIV2
  *         @arg @ref LL_LPTIM_PRESCALER_DIV4
  *         @arg @ref LL_LPTIM_PRESCALER_DIV8
  *         @arg @ref LL_LPTIM_PRESCALER_DIV16
  *         @arg @ref LL_LPTIM_PRESCALER_DIV32
  *         @arg @ref LL_LPTIM_PRESCALER_DIV64
  *         @arg @ref LL_LPTIM_PRESCALER_DIV128
  * @param  __FLT__ This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV1
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV2
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV4
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV8
  * @retval offset value
  */
#define LL_LPTIM_IC_GET_OFFSET(__PSC__, __FLT__) LL_LPTIM_OFFSET_TAB_ICx\
  [((__PSC__) & LPTIM_CFGR_PRESC_Msk) >> LPTIM_CFGR_PRESC_Pos]\
  [((__FLT__) & LPTIM_CCMR1_IC1F_Msk) >> LPTIM_CCMR1_IC1F_Pos]
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup LPTIM_LL_Exported_Functions LPTIM Exported Functions
  * @{
  */


/** @defgroup LPTIM_LL_EF_LPTIM_Configuration LPTIM Configuration
  * @{
  */

/**
  * @brief  Enable the LPTIM instance
  * @note After setting the ENABLE bit, a delay of two counter clock is needed
  *       before the LPTIM instance is actually enabled.
  * @rmtoll
  *  CR           ENABLE        LL_LPTIM_Enable
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_Enable(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->CR, LPTIM_CR_ENABLE);
}

/**
  * @brief  Disable the LPTIM instance
  * @rmtoll
  *  CR           ENABLE        LL_LPTIM_Disable
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_Disable(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->CR, LPTIM_CR_ENABLE);
}

/**
  * @brief  Indicates whether the LPTIM instance is enabled.
  * @rmtoll
  *  CR           ENABLE        LL_LPTIM_IsEnabled
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabled(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->CR, LPTIM_CR_ENABLE) == LPTIM_CR_ENABLE) ? 1UL : 0UL));
}

/**
  * @brief  Starts the LPTIM counter in the desired mode.
  * @note LPTIM instance must be enabled before starting the counter.
  * @note It is possible to change on the fly from One Shot mode to
  *       Continuous mode.
  * @rmtoll
  *  CR           CNTSTRT       LL_LPTIM_StartCounter \n
  *  CR           SNGSTRT       LL_LPTIM_StartCounter
  * @param  lptimx Low-Power Timer instance
  * @param  operating_mode This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_OPERATING_MODE_CONTINUOUS
  *         @arg @ref LL_LPTIM_OPERATING_MODE_ONESHOT
  */
__STATIC_INLINE void LL_LPTIM_StartCounter(LPTIM_TypeDef *lptimx, uint32_t operating_mode)
{
  MODIFY_REG(lptimx->CR, LPTIM_CR_CNTSTRT | LPTIM_CR_SNGSTRT, operating_mode);
}

/**
  * @brief  Enable reset after read.
  * @note After calling this function any read access to LPTIM_CNT
  *        register will asynchronously reset the LPTIM_CNT register content.
  * @rmtoll
  *  CR           RSTARE        LL_LPTIM_EnableResetAfterRead
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableResetAfterRead(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->CR, LPTIM_CR_RSTARE);
}

/**
  * @brief  Disable reset after read.
  * @rmtoll
  *  CR           RSTARE        LL_LPTIM_DisableResetAfterRead
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableResetAfterRead(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->CR, LPTIM_CR_RSTARE);
}

/**
  * @brief  Indicate whether the reset after read feature is enabled.
  * @rmtoll
  *  CR           RSTARE        LL_LPTIM_IsEnabledResetAfterRead
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledResetAfterRead(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->CR, LPTIM_CR_RSTARE) == LPTIM_CR_RSTARE) ? 1UL : 0UL));
}

/**
  * @brief  Reset of the LPTIM_CNT counter register (synchronous).
  * @note Due to the synchronous nature of this reset, it only takes
  *       place after a synchronization delay of 3 LPTIM core clock cycles
  *      (LPTIM core clock can be different from APB clock).
  * @note COUNTRST is automatically cleared by hardware
  * @rmtoll
  *  CR           COUNTRST       LL_LPTIM_ResetCounter
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ResetCounter(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->CR, LPTIM_CR_COUNTRST);
}

/**
  * @brief  Set the LPTIM registers update mode (enable/disable register preload)
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll
  *  CFGR         PRELOAD       LL_LPTIM_SetUpdateMode
  * @param  lptimx Low-Power Timer instance
  * @param  update_mode This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_PRELOAD_DISABLED
  *         @arg @ref LL_LPTIM_PRELOAD_ENABLED
  */
__STATIC_INLINE void LL_LPTIM_SetUpdateMode(LPTIM_TypeDef *lptimx, uint32_t update_mode)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_PRELOAD, update_mode);
}

/**
  * @brief  Get the LPTIM registers update mode
  * @rmtoll
  *  CFGR         PRELOAD       LL_LPTIM_GetUpdateMode
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_PRELOAD_DISABLED
  *         @arg @ref LL_LPTIM_PRELOAD_ENABLED
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetUpdateMode(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_PRELOAD));
}

/**
  * @brief  Set the auto reload value
  * @note The LPTIMx_ARR register content must only be modified when the LPTIM is enabled
  * @note After a write to the LPTIMx_ARR register a new write operation to the
  *       same register can only be performed when the previous write operation
  *       is completed. Any successive write before  the ARROK flag is set, will
  *       lead to unpredictable results.
  * @note autoreload value be strictly greater than the compare value.
  * @rmtoll
  *  ARR          ARR           LL_LPTIM_SetAutoReload
  * @param  lptimx Low-Power Timer instance
  * @param  auto_reload Value between Min_Data=0x0001 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_LPTIM_SetAutoReload(LPTIM_TypeDef *lptimx, uint32_t auto_reload)
{
  MODIFY_REG(lptimx->ARR, LPTIM_ARR_ARR, auto_reload);
}

/**
  * @brief  Get actual auto reload value
  * @rmtoll
  *  ARR          ARR           LL_LPTIM_GetAutoReload
  * @param  lptimx Low-Power Timer instance
  * @retval AutoReload Value between Min_Data=0x0001 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetAutoReload(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->ARR, LPTIM_ARR_ARR));
}

/**
  * @brief  Set the repetition value
  * @note The LPTIMx_RCR register content must only be modified when the LPTIM is enabled
  * @rmtoll
  *  RCR          REP           LL_LPTIM_SetRepetition
  * @param  lptimx Low-Power Timer instance
  * @param  repetition Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE void LL_LPTIM_SetRepetition(LPTIM_TypeDef *lptimx, uint32_t repetition)
{
  MODIFY_REG(lptimx->RCR, LPTIM_RCR_REP, repetition);
}

/**
  * @brief  Get the repetition value
  * @rmtoll
  *  RCR          REP           LL_LPTIM_GetRepetition
  * @param  lptimx Low-Power Timer instance
  * @retval Repetition Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetRepetition(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->RCR, LPTIM_RCR_REP));
}

/**
  * @brief  Enable capture/compare channel.
  * @rmtoll
  *  CCMR1         CC1E          LL_LPTIM_CC_EnableChannel \n
  *  CCMR1         CC2E          LL_LPTIM_CC_EnableChannel
  * @param  lptimx LPTimer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  */
__STATIC_INLINE void LL_LPTIM_CC_EnableChannel(LPTIM_TypeDef *lptimx, uint32_t channel)
{
  SET_BIT(lptimx->CCMR1, 0x1UL << LL_LPTIM_SHIFT_TAB_CCxE[channel]);
}

/**
  * @brief  Disable capture/compare channel.
  * @rmtoll
  *  CCMR1         CC1E          LL_LPTIM_CC_DisableChannel \n
  *  CCMR1         CC2E          LL_LPTIM_CC_DisableChannel
  * @param  lptimx LPTimer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  */
__STATIC_INLINE void LL_LPTIM_CC_DisableChannel(LPTIM_TypeDef *lptimx, uint32_t channel)
{
  CLEAR_BIT(lptimx->CCMR1, 0x1UL << LL_LPTIM_SHIFT_TAB_CCxE[channel]);
}

/**
  * @brief  Indicate whether channel is enabled.
  * @rmtoll
  *  CCMR1         CC1E          LL_LPTIM_CC_IsEnabledChannel \n
  *  CCMR1         CC2E          LL_LPTIM_CC_IsEnabledChannel
  * @param  lptimx LPTimer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_CC_IsEnabledChannel(const LPTIM_TypeDef *lptimx, uint32_t channel)
{
  return ((READ_BIT(lptimx->CCMR1, 0x1UL << LL_LPTIM_SHIFT_TAB_CCxE[channel]) ==                                       \
           (0x1UL << LL_LPTIM_SHIFT_TAB_CCxE[channel])) ? 1UL : 0UL);
}

/**
  * @brief  Set the compare value
  * @note After a write to the LPTIMx_CCR1 register a new write operation to the
  *       same register can only be performed when the previous write operation
  *       is completed. Any successive write before the CMP1OK flag is set, will
  *       lead to unpredictable results.
  * @rmtoll
  *  CCR1          CCR1           LL_LPTIM_OC_SetCompareCH1
  * @param  lptimx Low-Power Timer instance
  * @param  compare_value Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_LPTIM_OC_SetCompareCH1(LPTIM_TypeDef *lptimx, uint32_t compare_value)
{
  MODIFY_REG(lptimx->CCR1, LPTIM_CCR1_CCR1, compare_value);
}

/**
  * @brief  Get actual compare value
  * @rmtoll
  *  CCR1          CCR1           LL_LPTIM_OC_GetCompareCH1
  * @param  lptimx Low-Power Timer instance
  * @retval CompareValue Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_LPTIM_OC_GetCompareCH1(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CCR1, LPTIM_CCR1_CCR1));
}

/**
  * @brief  Set the compare value
  * @note After a write to the LPTIMx_CCR2 register a new write operation to the
  *       same register can only be performed when the previous write operation
  *       is completed. Any successive write before the CMP2OK flag is set, will
  *       lead to unpredictable results.
  * @rmtoll
  *  CCR2          CCR2           LL_LPTIM_OC_SetCompareCH2
  * @param  lptimx Low-Power Timer instance
  * @param  compare_value Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE void LL_LPTIM_OC_SetCompareCH2(LPTIM_TypeDef *lptimx, uint32_t compare_value)
{
  MODIFY_REG(lptimx->CCR2, LPTIM_CCR2_CCR2, compare_value);
}

/**
  * @brief  Get actual compare value
  * @rmtoll
  *  CCR2          CCR2           LL_LPTIM_OC_GetCompareCH2
  * @param  lptimx Low-Power Timer instance
  * @retval CompareValue Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_LPTIM_OC_GetCompareCH2(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CCR2, LPTIM_CCR2_CCR2));
}

/**
  * @brief  Get actual counter value
  * @note When the LPTIM instance is running with an asynchronous clock, reading
  *       the LPTIMx_CNT register can be return unreliable values. So in this case
  *       it is necessary to perform two consecutive read accesses and verify
  *       that the two returned values are identical.
  * @rmtoll
  *  CNT          CNT           LL_LPTIM_GetCounter
  * @param  lptimx Low-Power Timer instance
  * @retval Counter value
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetCounter(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CNT, LPTIM_CNT_CNT));
}

/**
  * @brief  Set the counter mode (selection of the LPTIM counter clock source).
  * @note The counter mode can be set only when the LPTIM instance is disabled.
  * @rmtoll
  *  CFGR         COUNTMODE     LL_LPTIM_SetCounterMode
  * @param  lptimx Low-Power Timer instance
  * @param  counter_mode This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_COUNTER_MODE_INTERNAL
  *         @arg @ref LL_LPTIM_COUNTER_MODE_EXTERNAL
  */
__STATIC_INLINE void LL_LPTIM_SetCounterMode(LPTIM_TypeDef *lptimx, uint32_t counter_mode)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_COUNTMODE, counter_mode);
}

/**
  * @brief  Get the counter mode
  * @rmtoll
  *  CFGR         COUNTMODE     LL_LPTIM_GetCounterMode
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_COUNTER_MODE_INTERNAL
  *         @arg @ref LL_LPTIM_COUNTER_MODE_EXTERNAL
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetCounterMode(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_COUNTMODE));
}

/**
  * @brief  Set  waveform shape
  * @rmtoll
  *  CFGR         WAVE          LL_LPTIM_SetWaveform
  * @param  lptimx   Low-Power Timer instance
  * @param  waveform This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_OUTPUT_WAVEFORM_PWM
  *         @arg @ref LL_LPTIM_OUTPUT_WAVEFORM_SETONCE
  */
__STATIC_INLINE void LL_LPTIM_SetWaveform(LPTIM_TypeDef *lptimx, uint32_t waveform)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_WAVE, waveform);
}

/**
  * @brief  Get actual waveform shape
  * @rmtoll
  *  CFGR         WAVE          LL_LPTIM_GetWaveform
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_OUTPUT_WAVEFORM_PWM
  *         @arg @ref LL_LPTIM_OUTPUT_WAVEFORM_SETONCE
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetWaveform(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_WAVE));
}

/**
  * @brief  Set the polarity of an output channel.
  * @rmtoll
  *  CCMR1         CC1P          LL_LPTIM_OC_SetPolarity \n
  *  CCMR1         CC2P          LL_LPTIM_OC_SetPolarity
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_OCPOLARITY_HIGH
  *         @arg @ref LL_LPTIM_OCPOLARITY_LOW
  */
__STATIC_INLINE void LL_LPTIM_OC_SetPolarity(LPTIM_TypeDef *lptimx, uint32_t channel, uint32_t polarity)
{
  if (lptimx == LPTIM4)
  {
    MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_WAVPOL, ((polarity >> LPTIM_CCMR1_CC1P_Pos) << LPTIM_CFGR_WAVPOL_Pos));
  }
  else
  {
    MODIFY_REG(lptimx->CCMR1, (LPTIM_CCMR1_CC1P << LL_LPTIM_SHIFT_TAB_CCxP[channel]),
               (polarity << LL_LPTIM_SHIFT_TAB_CCxP[channel]));
  }
}

/**
  * @brief  Get the polarity of an output channel.
  * @rmtoll
  *  CCMR1         CC1P          LL_LPTIM_OC_GetPolarity \n
  *  CCMR1         CC2P          LL_LPTIM_OC_GetPolarity
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_OCPOLARITY_HIGH
  *         @arg @ref LL_LPTIM_OCPOLARITY_LOW
  */
__STATIC_INLINE uint32_t LL_LPTIM_OC_GetPolarity(const LPTIM_TypeDef *lptimx, uint32_t channel)
{
  if (lptimx == LPTIM4)
  {
    return (uint32_t)((READ_BIT(lptimx->CFGR, LPTIM_CFGR_WAVPOL) >> LPTIM_CFGR_WAVPOL_Pos) << LPTIM_CCMR1_CC1P_Pos);
  }
  else
  {
    return (uint32_t)(READ_BIT(lptimx->CCMR1, LPTIM_CCMR1_CC1P << LL_LPTIM_SHIFT_TAB_CCxP[channel]) >>                 \
                      LL_LPTIM_SHIFT_TAB_CCxP[channel]);
  }
}

/**
  * @brief  Set actual prescaler division ratio.
  * @note This function must be called when the LPTIM instance is disabled.
  * @note When the LPTIM is configured to be clocked by an internal clock source
  *       and the LPTIM counter is configured to be updated by active edges
  *       detected on the LPTIM external Input1, the internal clock provided to
  *       the LPTIM must be not be prescaled.
  * @rmtoll
  *  CFGR         PRESC         LL_LPTIM_SetPrescaler
  * @param  lptimx Low-Power Timer instance
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_PRESCALER_DIV1
  *         @arg @ref LL_LPTIM_PRESCALER_DIV2
  *         @arg @ref LL_LPTIM_PRESCALER_DIV4
  *         @arg @ref LL_LPTIM_PRESCALER_DIV8
  *         @arg @ref LL_LPTIM_PRESCALER_DIV16
  *         @arg @ref LL_LPTIM_PRESCALER_DIV32
  *         @arg @ref LL_LPTIM_PRESCALER_DIV64
  *         @arg @ref LL_LPTIM_PRESCALER_DIV128
  */
__STATIC_INLINE void LL_LPTIM_SetPrescaler(LPTIM_TypeDef *lptimx, uint32_t prescaler)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_PRESC, prescaler);
}

/**
  * @brief  Get actual prescaler division ratio.
  * @rmtoll
  *  CFGR         PRESC         LL_LPTIM_GetPrescaler
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_PRESCALER_DIV1
  *         @arg @ref LL_LPTIM_PRESCALER_DIV2
  *         @arg @ref LL_LPTIM_PRESCALER_DIV4
  *         @arg @ref LL_LPTIM_PRESCALER_DIV8
  *         @arg @ref LL_LPTIM_PRESCALER_DIV16
  *         @arg @ref LL_LPTIM_PRESCALER_DIV32
  *         @arg @ref LL_LPTIM_PRESCALER_DIV64
  *         @arg @ref LL_LPTIM_PRESCALER_DIV128
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetPrescaler(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_PRESC));
}

/**
  * @brief  Set LPTIM input 1 source (default GPIO).
  * @rmtoll
  *  CFGR2      IN1SEL       LL_LPTIM_SetInput1Source
  * @param  lptimx Low-Power Timer instance
  * @param  src This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_INPUT1_SRC_GPIO
  *         @arg @ref LL_LPTIM_INPUT1_SRC_COMP1
  */
__STATIC_INLINE void LL_LPTIM_SetInput1Source(LPTIM_TypeDef *lptimx, uint32_t src)
{
  MODIFY_REG(lptimx->CFGR2, LPTIM_CFGR2_IN1SEL, src);
}

/**
  * @brief  Get LPTIM input 1 source.
  * @rmtoll
  *  CFGR2      IN1SEL       LL_LPTIM_GetInput1Source
  * @param  lptimx Low-Power Timer instance
  * @retval uint32_t Input1 source
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetInput1Source(LPTIM_TypeDef *lptimx)
{
  return (READ_REG(lptimx->CFGR2) & LPTIM_CFGR2_IN1SEL);
}

/**
  * @brief  Set LPTIM input 2 source (default GPIO).
  * @rmtoll
  *  CFGR2      IN2SEL       LL_LPTIM_SetInput2Source
  * @param  lptimx Low-Power Timer instance
  * @param  src This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_INPUT2_SRC_GPIO
  *         @arg @ref LL_LPTIM_INPUT2_SRC_COMP2
  */
__STATIC_INLINE void LL_LPTIM_SetInput2Source(LPTIM_TypeDef *lptimx, uint32_t src)
{
  MODIFY_REG(lptimx->CFGR2, LPTIM_CFGR2_IN2SEL, src);
}

/**
  * @brief  Get LPTIM input 2 source (default GPIO).
  * @rmtoll
  *  CFGR2      IN2SEL       LL_LPTIM_GetInput2Source
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_INPUT2_SRC_GPIO
  *         @arg @ref LL_LPTIM_INPUT2_SRC_COMP2
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetInput2Source(LPTIM_TypeDef *lptimx)
{
  return (READ_REG(lptimx->CFGR2) & LPTIM_CFGR2_IN2SEL);
}

/**
  * @brief  Set LPTIM input source (default GPIO).
  * @rmtoll
  *  CFGR2      IC1SEL        LL_LPTIM_SetRemap \n
  *  CFGR2      IC2SEL        LL_LPTIM_SetRemap
  * @param  lptimx Low-Power Timer instance
  * @param  src This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_LPTIM1_IC1_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM1_IC1_RMP_COMP1
  *         @arg @ref LL_LPTIM_LPTIM1_IC1_RMP_COMP2
  *         @arg @ref LL_LPTIM_LPTIM1_IC2_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM1_IC2_RMP_LSI
  *         @arg @ref LL_LPTIM_LPTIM1_IC2_RMP_LSE
  *         @arg @ref LL_LPTIM_LPTIM2_IC1_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM2_IC1_RMP_COMP1
  *         @arg @ref LL_LPTIM_LPTIM2_IC1_RMP_COMP2
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_HSI
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_MSIS_1024
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_MSIS_4
  *         @arg @ref LL_LPTIM_LPTIM3_IC1_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM3_IC1_RMP_COMP1
  *         @arg @ref LL_LPTIM_LPTIM3_IC1_RMP_COMP2
  */
__STATIC_INLINE void LL_LPTIM_SetRemap(LPTIM_TypeDef *lptimx, uint32_t src)
{
  MODIFY_REG(lptimx->CFGR2, LPTIM_CFGR2_IC1SEL | LPTIM_CFGR2_IC2SEL, src);
}

/**
  * @brief  Get LPTIM input source (default GPIO).
  * @rmtoll
  *  CFGR2      IC1SEL        LL_LPTIM_GetRemap \n
  *  CFGR2      IC2SEL        LL_LPTIM_GetRemap
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_LPTIM1_IC1_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM1_IC1_RMP_COMP1
  *         @arg @ref LL_LPTIM_LPTIM1_IC1_RMP_COMP2
  *         @arg @ref LL_LPTIM_LPTIM1_IC2_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM1_IC2_RMP_LSI
  *         @arg @ref LL_LPTIM_LPTIM1_IC2_RMP_LSE

  *         @arg @ref LL_LPTIM_LPTIM2_IC1_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM2_IC1_RMP_COMP1
  *         @arg @ref LL_LPTIM_LPTIM2_IC1_RMP_COMP2
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_HSI
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_MSIS_1024
  *         @arg @ref LL_LPTIM_LPTIM2_IC2_RMP_MSIS_4

  *         @arg @ref LL_LPTIM_LPTIM3_IC1_RMP_GPIO
  *         @arg @ref LL_LPTIM_LPTIM3_IC1_RMP_COMP1
  *         @arg @ref LL_LPTIM_LPTIM3_IC1_RMP_COMP2
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetRemap(LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_REG(lptimx->CFGR2) & (LPTIM_CFGR2_IC1SEL | LPTIM_CFGR2_IC2SEL)) ;
}

/**
  * @brief  Set the polarity of IC channel 1.
  * @rmtoll
  *  CCMR1         CC1P          LL_LPTIM_IC_SetPolarity \n
  *  CCMR1         CC2P          LL_LPTIM_IC_SetPolarity
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_ICPOLARITY_RISING
  *         @arg @ref LL_LPTIM_ICPOLARITY_FALLING
  *         @arg @ref LL_LPTIM_ICPOLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_LPTIM_IC_SetPolarity(LPTIM_TypeDef *lptimx, uint32_t channel, uint32_t polarity)
{
  MODIFY_REG(lptimx->CCMR1, LPTIM_CCMR1_CC1P << LL_LPTIM_SHIFT_TAB_CCxP[channel],
             polarity << LL_LPTIM_SHIFT_TAB_CCxP[channel]);
}

/**
  * @brief  Get the polarity of IC channels.
  * @rmtoll
  *  CCMR1         CC1P          LL_LPTIM_IC_GetPolarity \n
  *  CCMR1         CC2P          LL_LPTIM_IC_GetPolarity
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_ICPOLARITY_RISING
  *         @arg @ref LL_LPTIM_ICPOLARITY_FALLING
  *         @arg @ref LL_LPTIM_ICPOLARITY_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_LPTIM_IC_GetPolarity(const LPTIM_TypeDef *lptimx, uint32_t channel)
{
  return (uint32_t)((READ_BIT(lptimx->CCMR1, LPTIM_CCMR1_CC1P << LL_LPTIM_SHIFT_TAB_CCxP[channel])) >>                 \
                    LL_LPTIM_SHIFT_TAB_CCxP[channel]);
}

/**
  * @brief  Configure input channel.
  * @rmtoll
  *  CCMR1         CC1P          LL_LPTIM_IC_Config \n
  *  CCMR1         CC2P          LL_LPTIM_IC_Config \n
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV1 or ... or @ref LL_LPTIM_ICFLT_CLOCK_DIV8
  *         @arg @ref LL_LPTIM_ICPSC_DIV1 or ... or @ref LL_LPTIM_ICPSC_DIV8
  *         @arg @ref LL_LPTIM_OCPOLARITY_HIGH or LL_LPTIM_OCPOLARITY_LOW
  */
__STATIC_INLINE void LL_LPTIM_IC_Config(LPTIM_TypeDef *lptimx, uint32_t channel, uint32_t configuration)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&lptimx->CCMR1)));
  MODIFY_REG(*pReg, ((LPTIM_CCMR1_IC1F | LPTIM_CCMR1_CC1P | LPTIM_CCMR1_IC1PSC) << LL_LPTIM_SHIFT_TAB_CCxx[channel]), \
             configuration);
}

/**
  * @brief  Set the filter of IC channels.
  * @rmtoll
  *  CCMR1         IC1F          LL_LPTIM_IC_SetFilter \n
  *  CCMR1         IC2F          LL_LPTIM_IC_SetFilter
  * @param  lptimx  Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @param  filter This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV1
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV2
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV4
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV8
  */
__STATIC_INLINE void LL_LPTIM_IC_SetFilter(LPTIM_TypeDef *lptimx, uint32_t channel, uint32_t filter)
{
  MODIFY_REG(lptimx->CCMR1, LPTIM_CCMR1_IC1F << LL_LPTIM_SHIFT_TAB_ICxF[channel],
             filter << LL_LPTIM_SHIFT_TAB_ICxF[channel]);
}

/**
  * @brief  Get the filter of IC channels.
  * @rmtoll
  *  CCMR1         IC1F          LL_LPTIM_IC_GetFilter \n
  *  CCMR1         IC2F          LL_LPTIM_IC_GetFilter
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV1
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV2
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV4
  *         @arg @ref LL_LPTIM_ICFLT_CLOCK_DIV8
  */
__STATIC_INLINE uint32_t LL_LPTIM_IC_GetFilter(const LPTIM_TypeDef *lptimx, uint32_t channel)
{
  return (uint32_t)((READ_BIT(lptimx->CCMR1, LPTIM_CCMR1_IC1F << LL_LPTIM_SHIFT_TAB_ICxF[channel])) >>                 \
                    LL_LPTIM_SHIFT_TAB_ICxF[channel]);
}

/**
  * @brief  Set the prescaler of IC channels.
  * @rmtoll
  *  CCMR1         IC1PSC        LL_LPTIM_IC_SetPrescaler \n
  *  CCMR1         IC2PSC        LL_LPTIM_IC_SetPrescaler
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_ICPSC_DIV1
  *         @arg @ref LL_LPTIM_ICPSC_DIV2
  *         @arg @ref LL_LPTIM_ICPSC_DIV4
  *         @arg @ref LL_LPTIM_ICPSC_DIV8
  */
__STATIC_INLINE void LL_LPTIM_IC_SetPrescaler(LPTIM_TypeDef *lptimx, uint32_t channel, uint32_t prescaler)
{
  MODIFY_REG(lptimx->CCMR1, LPTIM_CCMR1_IC1PSC << LL_LPTIM_SHIFT_TAB_ICxPSC[channel],
             prescaler << LL_LPTIM_SHIFT_TAB_ICxPSC[channel]);
}

/**
  * @brief  Get the prescaler of IC channels.
  * @rmtoll
  *  CCMR1         IC1PSC        LL_LPTIM_IC_GetPrescaler \n
  *  CCMR1         IC2PSC        LL_LPTIM_IC_GetPrescaler
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_ICPSC_DIV1
  *         @arg @ref LL_LPTIM_ICPSC_DIV2
  *         @arg @ref LL_LPTIM_ICPSC_DIV4
  *         @arg @ref LL_LPTIM_ICPSC_DIV8
  */
__STATIC_INLINE uint32_t LL_LPTIM_IC_GetPrescaler(const LPTIM_TypeDef *lptimx, uint32_t channel)
{
  return (uint32_t)((READ_BIT(lptimx->CCMR1, LPTIM_CCMR1_IC1PSC << LL_LPTIM_SHIFT_TAB_ICxPSC[channel])) >>            \
                    LL_LPTIM_SHIFT_TAB_ICxPSC[channel]);
}

/**
  * @brief  Set the channel  Mode.
  * @rmtoll
  *  CCMR1         CC1SEL          LL_LPTIM_CC_SetChannelMode \n
  *  CCMR1         CC2SEL          LL_LPTIM_CC_SetChannelMode
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @param  cc_mode This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CCMODE_OUTPUT_PWM
  *         @arg @ref LL_LPTIM_CCMODE_INPUTCAPTURE
  */
__STATIC_INLINE void  LL_LPTIM_CC_SetChannelMode(LPTIM_TypeDef *lptimx, uint32_t channel, uint32_t cc_mode)
{
  MODIFY_REG(lptimx->CCMR1, LPTIM_CCMR1_CC1SEL << LL_LPTIM_SHIFT_TAB_CCxSEL[channel],
             cc_mode << LL_LPTIM_SHIFT_TAB_CCxSEL[channel]);
}

/**
  * @brief  Get the channel  Mode.
  * @rmtoll
  *  CCMR1         CC1SEL          LL_LPTIM_CC_GetChannelMode \n
  *  CCMR1         CC2SEL          LL_LPTIM_CC_GetChannelMode
  * @param  lptimx Low-Power Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CHANNEL_CH1
  *         @arg @ref LL_LPTIM_CHANNEL_CH2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_CCMODE_OUTPUT_PWM
  *         @arg @ref LL_LPTIM_CCMODE_INPUTCAPTURE
  */
__STATIC_INLINE uint32_t  LL_LPTIM_CC_GetChannelMode(const LPTIM_TypeDef *lptimx, uint32_t channel)
{
  return (uint32_t)((READ_BIT(lptimx->CCMR1, LPTIM_CCMR1_CC1SEL << LL_LPTIM_SHIFT_TAB_CCxSEL[channel])) >>            \
                    LL_LPTIM_SHIFT_TAB_CCxSEL[channel]);
}

/**
  * @brief  Get captured value for input channel 1.
  * @rmtoll
  *  CCR1         CCR1          LL_LPTIM_IC_GetCaptureCH1
  * @note   The real capture value corresponding to the input capture trigger can be calculated using
  *         the formula hereafter : Real capture value = captured(LPTIM_CCRx) - offset
  *         where offset can be retrieved by calling @ref LL_LPTIM_IC_GET_OFFSET
  * @param  lptimx Low-Power Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_LPTIM_IC_GetCaptureCH1(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CCR1, LPTIM_CCR1_CCR1));
}

/**
  * @brief  Get captured value for input channel 2.
  * @rmtoll
  *  CCR2         CCR2          LL_LPTIM_IC_GetCaptureCH2
  * @note   The real capture value corresponding to the input capture trigger can be calculated using
  *         the formula hereafter : Real capture value = captured(LPTIM_CCRx) - offset
  *         where offset can be retrieved by calling @ref LL_LPTIM_IC_GET_OFFSET
  * @param  lptimx Low-Power Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_LPTIM_IC_GetCaptureCH2(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CCR2, LPTIM_CCR2_CCR2));
}

/**
  * @}
  */
/** @defgroup LPTIM_LL_EF_Trigger_Configuration Trigger Configuration
  * @{
  */

/**
  * @brief  Enable the timeout function
  * @note This function must be called when the LPTIM instance is disabled.
  * @note The first trigger event will start the timer, any successive trigger
  *       event will reset the counter and the timer will restart.
  * @note The timeout value corresponds to the compare value; if no trigger
  *       occurs within the expected time frame, the MCU is waked-up by the
  *       compare match event.
  * @rmtoll
  *  CFGR         TIMOUT        LL_LPTIM_EnableTimeout
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableTimeout(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->CFGR, LPTIM_CFGR_TIMOUT);
}

/**
  * @brief  Disable the timeout function
  * @note This function must be called when the LPTIM instance is disabled.
  * @note A trigger event arriving when the timer is already started will be
  *       ignored.
  * @rmtoll
  *  CFGR         TIMOUT        LL_LPTIM_DisableTimeout
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableTimeout(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->CFGR, LPTIM_CFGR_TIMOUT);
}

/**
  * @brief  Indicate whether the timeout function is enabled.
  * @rmtoll
  *  CFGR         TIMOUT        LL_LPTIM_IsEnabledTimeout
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledTimeout(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->CFGR, LPTIM_CFGR_TIMOUT) == LPTIM_CFGR_TIMOUT) ? 1UL : 0UL));
}

/**
  * @brief  Start the LPTIM counter
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll
  *  CFGR         TRIGEN        LL_LPTIM_TrigSw
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_TrigSw(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->CFGR, LPTIM_CFGR_TRIGEN);
}

/**
  * @brief  Configure the external trigger used as a trigger event for the LPTIM.
  * @note This function must be called when the LPTIM instance is disabled.
  * @note An internal clock source must be present when a digital filter is
  *       required for the trigger.
  * @rmtoll
  *  CFGR         TRIGSEL       LL_LPTIM_ConfigTrigger \n
  *  CFGR         TRGFLT        LL_LPTIM_ConfigTrigger \n
  *  CFGR         TRIGEN        LL_LPTIM_ConfigTrigger
  * @param  lptimx    Low-Power Timer instance
  * @param  source    This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPIO
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCALARMA
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCALARMB
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP1
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP2
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP3
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_COMP1
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_COMP2
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH0_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH1_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH2_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPDMA_CH0_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPDMA_CH4_TCF
  * @param  filter    This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_FILTER_NONE
  *         @arg @ref LL_LPTIM_TRIG_FILTER_2
  *         @arg @ref LL_LPTIM_TRIG_FILTER_4
  *         @arg @ref LL_LPTIM_TRIG_FILTER_8
  * @param  polarity  This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_RISING
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_FALLING
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_LPTIM_ConfigTrigger(LPTIM_TypeDef *lptimx, uint32_t source, uint32_t filter, uint32_t polarity)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_TRIGSEL | LPTIM_CFGR_TRGFLT | LPTIM_CFGR_TRIGEN, source | filter | polarity);
}


/**
  * @brief  Set external trigger source.
  * @rmtoll
  *  CFGR         TRIGSEL       LL_LPTIM_SetTriggerSource
  * @param  lptimx Low-Power Timer instance
  * @param  source Trigger's source.
  *         Can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPIO
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCALARMA
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCALARMB
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP1
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP2
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP3
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_COMP1
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_COMP2
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH0_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH1_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH2_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPDMA_CH0_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPDMA_CH4_TCF
  */
__STATIC_INLINE void LL_LPTIM_SetTriggerSource(LPTIM_TypeDef *lptimx, uint32_t source)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_TRIGSEL, source);
}

/**
  * @brief  Get actual external trigger source.
  * @rmtoll
  *  CFGR         TRIGSEL       LL_LPTIM_GetTriggerSource
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPIO
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCALARMA
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCALARMB
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP1
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP2
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_RTCTAMP3
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_COMP1
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_COMP2
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH0_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH1_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_LPDMA_CH2_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPDMA_CH0_TCF
  *         @arg @ref LL_LPTIM_TRIG_SOURCE_GPDMA_CH4_TCF
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetTriggerSource(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_TRIGSEL));
}

/**
  * @brief  Set external trigger filter.
  * @rmtoll
  *  CFGR         TRGFLT        LL_LPTIM_GetTriggerFilter
  * @param  lptimx Low-Power Timer instance
  * @param  filter ETR filter.
  *         Can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_FILTER_NONE
  *         @arg @ref LL_LPTIM_TRIG_FILTER_2
  *         @arg @ref LL_LPTIM_TRIG_FILTER_4
  *         @arg @ref LL_LPTIM_TRIG_FILTER_8
  */
__STATIC_INLINE void LL_LPTIM_SetTriggerFilter(LPTIM_TypeDef *lptimx, uint32_t filter)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_TRGFLT, filter);
}

/**
  * @brief  Get actual external trigger filter.
  * @rmtoll
  *  CFGR         TRGFLT        LL_LPTIM_GetTriggerFilter
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_FILTER_NONE
  *         @arg @ref LL_LPTIM_TRIG_FILTER_2
  *         @arg @ref LL_LPTIM_TRIG_FILTER_4
  *         @arg @ref LL_LPTIM_TRIG_FILTER_8
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetTriggerFilter(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_TRGFLT));
}

/**
  * @brief  Set external trigger polarity.
  * @rmtoll
  *  CFGR         TRIGEN        LL_LPTIM_GetTriggerPolarity
  * @param  lptimx Low-Power Timer instance
  * @param  polarity Trigger's polarity.
  *         Can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_RISING
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_FALLING
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_LPTIM_SetTriggerPolarity(LPTIM_TypeDef *lptimx, uint32_t polarity)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_TRIGEN, polarity);
}

/**
  * @brief  Get actual external trigger polarity.
  * @rmtoll
  *  CFGR         TRIGEN        LL_LPTIM_GetTriggerPolarity
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_RISING
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_FALLING
  *         @arg @ref LL_LPTIM_TRIG_POLARITY_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetTriggerPolarity(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_TRIGEN));
}

/**
  * @}
  */

/** @defgroup LPTIM_LL_EF_Clock_Configuration Clock Configuration
  * @{
  */

/**
  * @brief  Set the source of the clock used by the LPTIM instance.
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll
  *  CFGR         CKSEL         LL_LPTIM_SetClockSource
  * @param  lptimx       Low-Power Timer instance
  * @param  clock_source This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_SOURCE_INTERNAL
  *         @arg @ref LL_LPTIM_CLK_SOURCE_EXTERNAL
  */
__STATIC_INLINE void LL_LPTIM_SetClockSource(LPTIM_TypeDef *lptimx, uint32_t clock_source)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_CKSEL, clock_source);
}

/**
  * @brief  Get actual LPTIM instance clock source.
  * @rmtoll
  *  CFGR         CKSEL         LL_LPTIM_GetClockSource
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_SOURCE_INTERNAL
  *         @arg @ref LL_LPTIM_CLK_SOURCE_EXTERNAL
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetClockSource(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_CKSEL));
}

/**
  * @brief  Configure the active edge or edges used by the counter when
            the LPTIM is clocked by an external clock source.
  * @note This function must be called when the LPTIM instance is disabled.
  * @note When both external clock signal edges are considered active ones,
  *       the LPTIM must also be clocked by an internal clock source with a
  *       frequency equal to at least four times the external clock frequency.
  * @note An internal clock source must be present when a digital filter is
  *       required for external clock.
  * @rmtoll
  *  CFGR         CKFLT         LL_LPTIM_ConfigClock
  *  CFGR         CKPOL         LL_LPTIM_ConfigClock
  * @param  lptimx         Low-Power Timer instance
  * @param  clock_filter   This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_FILTER_NONE
  *         @arg @ref LL_LPTIM_CLK_FILTER_2
  *         @arg @ref LL_LPTIM_CLK_FILTER_4
  *         @arg @ref LL_LPTIM_CLK_FILTER_8
  * @param  clock_polarity This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_POLARITY_RISING
  *         @arg @ref LL_LPTIM_CLK_POLARITY_FALLING
  *         @arg @ref LL_LPTIM_CLK_POLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_LPTIM_ConfigClock(LPTIM_TypeDef *lptimx, uint32_t clock_filter, uint32_t clock_polarity)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_CKFLT | LPTIM_CFGR_CKPOL, clock_filter | clock_polarity);
}

/**
  * @brief  Set clock polarity
  * @rmtoll
  *  CFGR         CKPOL         LL_LPTIM_SetClockPolarity
  * @param  lptimx Low-Power Timer instance
  * @param  clock_polarity This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_POLARITY_RISING
  *         @arg @ref LL_LPTIM_CLK_POLARITY_FALLING
  *         @arg @ref LL_LPTIM_CLK_POLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_LPTIM_SetClockPolarity(LPTIM_TypeDef *lptimx, uint32_t clock_polarity)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_CKPOL, clock_polarity);
}

/**
  * @brief  Get actual clock polarity
  * @rmtoll
  *  CFGR         CKPOL         LL_LPTIM_GetClockPolarity
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_POLARITY_RISING
  *         @arg @ref LL_LPTIM_CLK_POLARITY_FALLING
  *         @arg @ref LL_LPTIM_CLK_POLARITY_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetClockPolarity(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_CKPOL));
}

/**
  * @brief  Set clock filter
  * @rmtoll
  *  CFGR         CKFLT         LL_LPTIM_SetClockFilter
  * @param  lptimx Low-Power Timer instance
  * @param  clock_filter This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_FILTER_NONE
  *         @arg @ref LL_LPTIM_CLK_FILTER_2
  *         @arg @ref LL_LPTIM_CLK_FILTER_4
  *         @arg @ref LL_LPTIM_CLK_FILTER_8
  */
__STATIC_INLINE void LL_LPTIM_SetClockFilter(LPTIM_TypeDef *lptimx, uint32_t clock_filter)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_CKFLT, clock_filter);
}

/**
  * @brief  Get actual clock digital filter
  * @rmtoll
  *  CFGR         CKFLT         LL_LPTIM_GetClockFilter
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_CLK_FILTER_NONE
  *         @arg @ref LL_LPTIM_CLK_FILTER_2
  *         @arg @ref LL_LPTIM_CLK_FILTER_4
  *         @arg @ref LL_LPTIM_CLK_FILTER_8
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetClockFilter(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_CKFLT));
}

/**
  * @}
  */

/** @defgroup LPTIM_LL_EF_Encoder_Mode Encoder Mode
  * @{
  */

/**
  * @brief  Configure the encoder mode.
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll
  *  CFGR         CKPOL         LL_LPTIM_SetEncoderMode
  * @param  lptimx Low-Power Timer instance
  * @param  encoder_mode This parameter can be one of the following values:
  *         @arg @ref LL_LPTIM_ENCODER_MODE_RISING
  *         @arg @ref LL_LPTIM_ENCODER_MODE_FALLING
  *         @arg @ref LL_LPTIM_ENCODER_MODE_RISING_FALLING
  */
__STATIC_INLINE void LL_LPTIM_SetEncoderMode(LPTIM_TypeDef *lptimx, uint32_t encoder_mode)
{
  MODIFY_REG(lptimx->CFGR, LPTIM_CFGR_CKPOL, encoder_mode);
}

/**
  * @brief  Get actual encoder mode.
  * @rmtoll
  *  CFGR         CKPOL         LL_LPTIM_GetEncoderMode
  * @param  lptimx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPTIM_ENCODER_MODE_RISING
  *         @arg @ref LL_LPTIM_ENCODER_MODE_FALLING
  *         @arg @ref LL_LPTIM_ENCODER_MODE_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_LPTIM_GetEncoderMode(const LPTIM_TypeDef *lptimx)
{
  return (uint32_t)(READ_BIT(lptimx->CFGR, LPTIM_CFGR_CKPOL));
}

/**
  * @brief  Enable the encoder mode
  * @note This function must be called when the LPTIM instance is disabled.
  * @note In this mode the LPTIM instance must be clocked by an internal clock
  *       source. Also, the prescaler division ratio must be equal to 1.
  * @note LPTIM instance must be configured in continuous mode prior enabling
  *       the encoder mode.
  * @rmtoll
  *  CFGR         ENC           LL_LPTIM_EnableEncoderMode
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableEncoderMode(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->CFGR, LPTIM_CFGR_ENC);
}

/**
  * @brief  Disable the encoder mode
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll
  *  CFGR         ENC           LL_LPTIM_DisableEncoderMode
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableEncoderMode(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->CFGR, LPTIM_CFGR_ENC);
}

/**
  * @brief  Indicates whether the LPTIM operates in encoder mode.
  * @rmtoll
  *  CFGR         ENC           LL_LPTIM_IsEnabledEncoderMode
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledEncoderMode(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->CFGR, LPTIM_CFGR_ENC) == LPTIM_CFGR_ENC) ? 1UL : 0UL));
}

/**
  * @}
  */

/** @defgroup LPTIM_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear the compare match flag for channel 1 (CC1CF)
  * @rmtoll
  *  ICR          CC1CF        LL_LPTIM_ClearFlag_CC1
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_CC1(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_CC1CF);
}

/**
  * @brief  Inform application whether a capture/compare interrupt has occurred for channel 1.
  * @rmtoll
  *  ISR          CC1IF         LL_LPTIM_IsActiveFlag_CC1
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_CC1(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_CC1IF) == LPTIM_ISR_CC1IF) ? 1UL : 0UL));
}

/**
  * @brief  Clear the compare match flag for channel 2 (CC2CF)
  * @rmtoll
  *  ICR          CC2CF        LL_LPTIM_ClearFlag_CC2
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_CC2(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_CC2CF);
}

/**
  * @brief  Inform application whether a capture/compare interrupt has occurred for channel 2.
  * @rmtoll
  *  ISR          CC2IF          LL_LPTIM_IsActiveFlag_CC2
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_CC2(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_CC2IF) == LPTIM_ISR_CC2IF) ? 1UL : 0UL));
}

/**
  * @brief  Clear the Capture/Compare 1 over-capture flag for channel 1 (CC1OCF)
  * @rmtoll
  *  ICR          CC1OCF       LL_LPTIM_ClearFlag_CC1O
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_CC1O(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_CC1OCF);
}

/**
  * @brief  Inform application whether a Capture/Compare 1 over-capture  has occurred for channel 1.
  * @rmtoll
  *  ISR          CC1OF          LL_LPTIM_IsActiveFlag_CC1O
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_CC1O(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_CC1OF) == LPTIM_ISR_CC1OF) ? 1UL : 0UL));
}

/**
  * @brief  Clear the Capture/Compare 2 over-capture flag for channel 2 (CC2OCF)
  * @rmtoll
  *  ICR          CC2OCF       LL_LPTIM_ClearFlag_CC2O
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_CC2O(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_CC2OCF);
}

/**
  * @brief  Inform application whether a Capture/Compare 2 over-capture  has occurred for channel 2.
  * @rmtoll
  *  ISR          CC2OF          LL_LPTIM_IsActiveFlag_CC2O
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_CC2O(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_CC2OF) == LPTIM_ISR_CC2OF) ? 1UL : 0UL));
}

/**
  * @brief  Clear the autoreload match flag (ARRMCF)
  * @rmtoll
  *  ICR          ARRMCF        LL_LPTIM_ClearFlag_ARRM
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_ARRM(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_ARRMCF);
}

/**
  * @brief  Inform application whether a autoreload match interrupt has occurred.
  * @rmtoll
  *  ISR          ARRM          LL_LPTIM_IsActiveFlag_ARRM
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_ARRM(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_ARRM) == LPTIM_ISR_ARRM) ? 1UL : 0UL));
}

/**
  * @brief  Clear the external trigger valid edge flag(EXTTRIGCF).
  * @rmtoll
  *  ICR          EXTTRIGCF     LL_LPTIM_ClearFlag_EXTTRIG
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_EXTTRIG(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_EXTTRIGCF);
}

/**
  * @brief  Inform application whether a valid edge on the selected external trigger input has occurred.
  * @rmtoll
  *  ISR          EXTTRIG       LL_LPTIM_IsActiveFlag_EXTTRIG
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_EXTTRIG(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_EXTTRIG) == LPTIM_ISR_EXTTRIG) ? 1UL : 0UL));
}

/**
  * @brief  Clear the compare register update interrupt flag (CMP1OKCF).
  * @rmtoll
  *  ICR          CMP1OKCF       LL_LPTIM_ClearFlag_CMP1OK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_CMP1OK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_CMP1OKCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_CCR1 register has been successfully
            completed. If so, a new one can be initiated.
  * @rmtoll
  *  ISR          CMP1OK         LL_LPTIM_IsActiveFlag_CMP1OK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_CMP1OK(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_CMP1OK) == LPTIM_ISR_CMP1OK) ? 1UL : 0UL));
}

/**
  * @brief  Clear the compare register update interrupt flag (CMP2OKCF).
  * @rmtoll
  *  ICR          CMP2OKCF       LL_LPTIM_ClearFlag_CMP2OK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_CMP2OK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_CMP2OKCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_CCR2 register has been successfully
            completed. If so, a new one can be initiated.
  * @rmtoll
  *  ISR          CMP2OK         LL_LPTIM_IsActiveFlag_CMP2OK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_CMP2OK(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_CMP2OK) == LPTIM_ISR_CMP2OK) ? 1UL : 0UL));
}

/**
  * @brief  Clear the interrupt register update interrupt flag (DIEROKCF).
  * @rmtoll
  *  ICR       DIEROKCF          LL_LPTIM_ClearFlag_DIEROK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_DIEROK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_DIEROKCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_DIER register has been successfully
            completed. If so, a new one can be initiated.
  * @rmtoll
  *  ISR          DIEROK            LL_LPTIM_IsActiveFlag_DIEROK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_DIEROK(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->ISR, LPTIM_ISR_DIEROK) == (LPTIM_ISR_DIEROK)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the autoreload register update interrupt flag (ARROKCF).
  * @rmtoll
  *  ICR          ARROKCF       LL_LPTIM_ClearFlag_ARROK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_ARROK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_ARROKCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_ARR register has been successfully
            completed. If so, a new one can be initiated.
  * @rmtoll
  *  ISR          ARROK         LL_LPTIM_IsActiveFlag_ARROK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_ARROK(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_ARROK) == LPTIM_ISR_ARROK) ? 1UL : 0UL));
}

/**
  * @brief  Clear the counter direction change to up interrupt flag (UPCF).
  * @rmtoll
  *  ICR          UPCF          LL_LPTIM_ClearFlag_UP
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_UP(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_UPCF);
}

/**
  * @brief  Informs the application whether the counter direction has changed from down to up (when the LPTIM instance
            operates in encoder mode).
  * @rmtoll
  *  ISR          UP            LL_LPTIM_IsActiveFlag_UP
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_UP(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_UP) == LPTIM_ISR_UP) ? 1UL : 0UL));
}

/**
  * @brief  Clear the counter direction change to down interrupt flag (DOWNCF).
  * @rmtoll
  *  ICR          DOWNCF        LL_LPTIM_ClearFlag_DOWN
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_DOWN(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_DOWNCF);
}

/**
  * @brief  Informs the application whether the counter direction has changed from up to down (when the LPTIM instance
            operates in encoder mode).
  * @rmtoll
  *  ISR          DOWN          LL_LPTIM_IsActiveFlag_DOWN
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_DOWN(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->ISR, LPTIM_ISR_DOWN) == LPTIM_ISR_DOWN) ? 1UL : 0UL));
}

/**
  * @brief  Clear the repetition register update interrupt flag (REPOKCF).
  * @rmtoll
  *  ICR          REPOKCF       LL_LPTIM_ClearFlag_REPOK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_REPOK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_REPOKCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_RCR register has been successfully
            completed; If so, a new one can be initiated.
  * @rmtoll
  *  ISR          REPOK         LL_LPTIM_IsActiveFlag_REPOK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_REPOK(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->ISR, LPTIM_ISR_REPOK) == (LPTIM_ISR_REPOK)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the update event flag (UECF).
  * @rmtoll
  *  ICR          UECF          LL_LPTIM_ClearFlag_UE
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_ClearFlag_UE(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->ICR, LPTIM_ICR_UECF);
}

/**
  * @brief  Informs application whether the lptimx update event has occurred.
  * @rmtoll
  *  ISR          UE            LL_LPTIM_IsActiveFlag_UE
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsActiveFlag_UE(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->ISR, LPTIM_ISR_UE) == (LPTIM_ISR_UE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup LPTIM_LL_EF_IT_Management Interrupt Management
  * @{
  */
/**
  * @brief  Enable capture/compare 1 interrupt (CC1IE).
  * @rmtoll
  *  DIER         CC1IE        LL_LPTIM_EnableIT_CC1
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_CC1(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CC1IE);
}

/**
  * @brief  Disable capture/compare 1 interrupt (CC1IE).
  * @rmtoll
  *  DIER          CC1IE        LL_LPTIM_DisableIT_CC1
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_CC1(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CC1IE);
}

/**
  * @brief  Indicates whether the capture/compare 1 interrupt (CC1IE) is enabled.
  * @rmtoll
  *  DIER          CC1IE        LL_LPTIM_IsEnabledIT_CC1
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_CC1(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_CC1IE) == LPTIM_DIER_CC1IE) ? 1UL : 0UL));
}

/**
  * @brief  Enable capture/compare 1 interrupt (CC2IE).
  * @rmtoll
  *  DIER         CC2IE        LL_LPTIM_EnableIT_CC2
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_CC2(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CC2IE);
}

/**
  * @brief  Disable capture/compare 2 interrupt (CC2IE).
  * @rmtoll
  *  DIER          CC2IE        LL_LPTIM_DisableIT_CC2
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_CC2(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CC2IE);
}

/**
  * @brief  Indicates whether the capture/compare 2 interrupt (CC2IE) is enabled.
  * @rmtoll
  *  DIER          CC2IE        LL_LPTIM_IsEnabledIT_CC2
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_CC2(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_CC2IE) == LPTIM_DIER_CC2IE) ? 1UL : 0UL));
}

/**
  * @brief  Enable capture/compare 1 over-capture interrupt (CC1OIE).
  * @rmtoll
  *  DIER         CC1OIE        LL_LPTIM_EnableIT_CC1O
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_CC1O(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CC1OIE);
}

/**
  * @brief  Disable capture/compare 1 over-capture interrupt (CC1OIE).
  * @rmtoll
  *  DIER          CC1OIE        LL_LPTIM_DisableIT_CC1O
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_CC1O(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CC1OIE);
}

/**
  * @brief  Indicates whether the capture/compare 1 over-capture interrupt (CC1OIE) is enabled.
  * @rmtoll
  *  DIER          CC1OIE        LL_LPTIM_IsEnabledIT_CC1O
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_CC1O(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_CC1OIE) == LPTIM_DIER_CC1OIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable capture/compare 1 over-capture interrupt (CC2OIE).
  * @rmtoll
  *  DIER         CC2OIE        LL_LPTIM_EnableIT_CC2O
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_CC2O(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CC2OIE);
}

/**
  * @brief  Disable capture/compare 1 over-capture interrupt (CC2OIE).
  * @rmtoll
  *  DIER          CC2OIE        LL_LPTIM_DisableIT_CC2O
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_CC2O(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CC2OIE);
}

/**
  * @brief  Indicates whether the capture/compare 2 over-capture interrupt (CC2OIE) is enabled.
  * @rmtoll
  *  DIER          CC2OIE        LL_LPTIM_IsEnabledIT_CC2O
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_CC2O(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_CC2OIE) == LPTIM_DIER_CC2OIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable autoreload match interrupt (ARRMIE).
  * @rmtoll
  *  DIER          ARRMIE        LL_LPTIM_EnableIT_ARRM
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_ARRM(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_ARRMIE);
}

/**
  * @brief  Disable autoreload match interrupt (ARRMIE).
  * @rmtoll
  *  DIER          ARRMIE        LL_LPTIM_DisableIT_ARRM
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_ARRM(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_ARRMIE);
}

/**
  * @brief  Indicates whether the autoreload match interrupt (ARRMIE) is enabled.
  * @rmtoll
  *  DIER          ARRMIE        LL_LPTIM_IsEnabledIT_ARRM
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_ARRM(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_ARRMIE) == LPTIM_DIER_ARRMIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable external trigger valid edge interrupt (EXTTRIGIE).
  * @rmtoll
  *  DIER          EXTTRIGIE     LL_LPTIM_EnableIT_EXTTRIG
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_EXTTRIG(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_EXTTRIGIE);
}

/**
  * @brief  Disable external trigger valid edge interrupt (EXTTRIGIE).
  * @rmtoll
  *  DIER          EXTTRIGIE     LL_LPTIM_DisableIT_EXTTRIG
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_EXTTRIG(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_EXTTRIGIE);
}

/**
  * @brief  Indicates external trigger valid edge interrupt (EXTTRIGIE) is enabled.
  * @rmtoll
  *  DIER          EXTTRIGIE     LL_LPTIM_IsEnabledIT_EXTTRIG
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_EXTTRIG(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_EXTTRIGIE) == LPTIM_DIER_EXTTRIGIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable compare register write completed interrupt (CMP1OKIE).
  * @rmtoll
  *  IER          CMP1OKIE       LL_LPTIM_EnableIT_CMP1OK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_CMP1OK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CMP1OKIE);
}

/**
  * @brief  Disable compare register write completed interrupt (CMP1OKIE).
  * @rmtoll
  *  IER          CMPO1KIE       LL_LPTIM_DisableIT_CMP1OK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_CMP1OK(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CMP1OKIE);
}

/**
  * @brief  Indicates whether the compare register write completed interrupt (CMP1OKIE) is enabled.
  * @rmtoll
  *  IER          CMP1OKIE       LL_LPTIM_IsEnabledIT_CMP1OK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_CMP1OK(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_CMP1OKIE) == LPTIM_DIER_CMP1OKIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable compare register write completed interrupt (CMP2OKIE).
  * @rmtoll
  *  IER          CMP2OKIE       LL_LPTIM_EnableIT_CMP2OK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_CMP2OK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CMP2OKIE);
}

/**
  * @brief  Disable compare register write completed interrupt (CMP2OKIE).
  * @rmtoll
  *  IER          CMP2OKIE       LL_LPTIM_DisableIT_CMP2OK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_CMP2OK(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CMP2OKIE);
}

/**
  * @brief  Indicates whether the compare register write completed interrupt (CMP2OKIE) is enabled.
  * @rmtoll
  *  IER          CMP2OKIE       LL_LPTIM_IsEnabledIT_CMP2OK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_CMP2OK(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_CMP2OKIE) == LPTIM_DIER_CMP2OKIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable autoreload register write completed interrupt (ARROKIE).
  * @rmtoll
  *  DIER         ARROKIE       LL_LPTIM_EnableIT_ARROK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_ARROK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_ARROKIE);
}

/**
  * @brief  Disable autoreload register write completed interrupt (ARROKIE).
  * @rmtoll
  *  DIER         ARROKIE       LL_LPTIM_DisableIT_ARROK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_ARROK(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_ARROKIE);
}

/**
  * @brief  Indicates whether the autoreload register write completed interrupt (ARROKIE) is enabled.
  * @rmtoll
  *  DIER         ARROKIE       LL_LPTIM_IsEnabledIT_ARROK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit(1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_ARROK(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_ARROKIE) == LPTIM_DIER_ARROKIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable direction change to up interrupt (UPIE).
  * @rmtoll
  *  DIER         UPIE          LL_LPTIM_EnableIT_UP
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_UP(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_UPIE);
}

/**
  * @brief  Disable direction change to up interrupt (UPIE).
  * @rmtoll
  *  DIER         UPIE          LL_LPTIM_DisableIT_UP
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_UP(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_UPIE);
}

/**
  * @brief  Indicates whether the direction change to up interrupt (UPIE) is enabled.
  * @rmtoll
  *  DIER         UPIE          LL_LPTIM_IsEnabledIT_UP
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit(1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_UP(const LPTIM_TypeDef *lptimx)
{
  return (((READ_BIT(lptimx->DIER, LPTIM_DIER_UPIE) == LPTIM_DIER_UPIE) ? 1UL : 0UL));
}

/**
  * @brief  Enable direction change to down interrupt (DOWNIE).
  * @rmtoll
  *  DIER         DOWNIE        LL_LPTIM_EnableIT_DOWN
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_DOWN(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_DOWNIE);
}

/**
  * @brief  Disable direction change to down interrupt (DOWNIE).
  * @rmtoll
  *  DIER         DOWNIE        LL_LPTIM_DisableIT_DOWN
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_DOWN(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_DOWNIE);
}

/**
  * @brief  Indicates whether the direction change to down interrupt (DOWNIE) is enabled.
  * @rmtoll
  *  DIER         DOWNIE        LL_LPTIM_IsEnabledIT_DOWN
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit(1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_DOWN(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->DIER, LPTIM_DIER_DOWNIE) == LPTIM_DIER_DOWNIE) ? 1UL : 0UL);
}

/**
  * @brief  Enable repetition register update successfully completed interrupt (REPOKIE).
  * @rmtoll
  *  DIER         REPOKIE       LL_LPTIM_EnableIT_REPOK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_REPOK(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_REPOKIE);
}

/**
  * @brief  Disable repetition register update successfully completed interrupt (REPOKIE).
  * @rmtoll
  *  DIER         REPOKIE       LL_LPTIM_DisableIT_REPOK
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_REPOK(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_REPOKIE);
}

/**
  * @brief  Indicates whether the repetition register update successfully completed interrupt (REPOKIE) is enabled.
  * @rmtoll
  *  DIER         REPOKIE       LL_LPTIM_IsEnabledIT_REPOK
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit(1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_REPOK(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->DIER, LPTIM_DIER_REPOKIE) == (LPTIM_DIER_REPOKIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable update event interrupt (UEIE).
  * @rmtoll
  *  DIER         UEIE          LL_LPTIM_EnableIT_UE
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableIT_UE(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_UEIE);
}

/**
  * @brief  Disable update event interrupt (UEIE).
  * @rmtoll
  *  DIER          UEIE         LL_LPTIM_DisableIT_UE
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableIT_UE(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_UEIE);
}

/**
  * @brief  Indicates whether the update event interrupt (UEIE) is enabled.
  * @rmtoll
  *  DIER         UEIE          LL_LPTIM_IsEnabledIT_UE
  * @param  lptimx Low-Power Timer instance
  *@ retval State of bit(1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledIT_UE(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->DIER, LPTIM_DIER_UEIE) == (LPTIM_DIER_UEIE)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_DMA_Management DMA Management
  * @{
  */
/**
  * @brief  Enable update DMA request.
  * @rmtoll
  *  DIER         UEDE          LL_LPTIM_EnableDMAReq_UPDATE
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableDMAReq_UPDATE(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_UEDE);
}

/**
  * @brief  Disable update DMA request.
  * @rmtoll
  *  DIER         UEDE          LL_LPTIM_DisableDMAReq_UPDATE
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableDMAReq_UPDATE(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_UEDE);
}

/**
  * @brief  Indicates whether the update DMA request is enabled.
  * @rmtoll
  *  DIER         UEDE          LL_LPTIM_IsEnabledDMAReq_UPDATE
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledDMAReq_UPDATE(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->DIER, LPTIM_DIER_UEDE) == (LPTIM_DIER_UEDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 1 DMA request (CC1DE).
  * @rmtoll
  *  DIER         CC1DE         LL_LPTIM_EnableDMAReq_CC1
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableDMAReq_CC1(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CC1DE);
}

/**
  * @brief  Disable capture/compare 1  DMA request (CC1DE).
  * @rmtoll
  *  DIER         CC1DE         LL_LPTIM_DisableDMAReq_CC1
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableDMAReq_CC1(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CC1DE);
}

/**
  * @brief  Indicates whether the capture/compare 1 DMA request (CC1DE) is enabled.
  * @rmtoll
  *  DIER         CC1DE         LL_LPTIM_IsEnabledDMAReq_CC1
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledDMAReq_CC1(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->DIER, LPTIM_DIER_CC1DE) == (LPTIM_DIER_CC1DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 2 DMA request (CC2DE).
  * @rmtoll
  *  DIER         CC2DE         LL_LPTIM_EnableDMAReq_CC2
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_EnableDMAReq_CC2(LPTIM_TypeDef *lptimx)
{
  SET_BIT(lptimx->DIER, LPTIM_DIER_CC2DE);
}

/**
  * @brief  Disable capture/compare 2  DMA request (CC2DE).
  * @rmtoll
  *  DIER         CC2DE         LL_LPTIM_DisableDMAReq_CC2
  * @param  lptimx Low-Power Timer instance
  */
__STATIC_INLINE void LL_LPTIM_DisableDMAReq_CC2(LPTIM_TypeDef *lptimx)
{
  CLEAR_BIT(lptimx->DIER, LPTIM_DIER_CC2DE);
}

/**
  * @brief  Indicates whether the capture/compare 2 DMA request (CC2DE) is enabled.
  * @rmtoll
  *  DIER         CC2DE         LL_LPTIM_IsEnabledDMAReq_CC2
  * @param  lptimx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPTIM_IsEnabledDMAReq_CC2(const LPTIM_TypeDef *lptimx)
{
  return ((READ_BIT(lptimx->DIER, LPTIM_DIER_CC2DE) == (LPTIM_DIER_CC2DE)) ? 1UL : 0UL);
}

/**
  * @}
  */

#endif /* LPTIM1 || LPTIM2 ||  LPTIM3 || LPTIM4 */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_LPTIM_H */
