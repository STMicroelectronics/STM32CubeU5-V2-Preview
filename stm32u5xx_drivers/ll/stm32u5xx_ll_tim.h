/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_tim.h
  * @brief   Header file of TIM LL module.
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
#ifndef STM32U5XX_LL_TIM_H
#define STM32U5XX_LL_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (TIM1)  \
 || defined (TIM2)  \
 || defined (TIM3)  \
 || defined (TIM4)  \
 || defined (TIM5)  \
 || defined (TIM6)  \
 || defined (TIM7)  \
 || defined (TIM8)  \
 || defined (TIM15) \
 || defined (TIM16) \
 || defined (TIM17)

/** @defgroup TIM_LL TIM
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup TIM_LL_Private_Variables TIM Private Variables
  * @{
  */
static const uint8_t LL_TIM_OFFSET_TAB_CCMRx[] =
{
  0x00U   /* 0: TIMx_CH1  */
  , 0x00U   /* 1: TIMx_CH1N */
  , 0x00U   /* 2: TIMx_CH2  */
  , 0x00U   /* 3: TIMx_CH2N */
  , 0x04U   /* 4: TIMx_CH3  */
  , 0x04U   /* 5: TIMx_CH3N */
  , 0x04U   /* 6: TIMx_CH4  */
  , 0x04U   /* 7: TIMx_CH4N */
  , 0x38U   /* 8: TIMx_CH5  */
  , 0x38U    /* 9: TIMx_CH6  */
};

static const uint8_t LL_TIM_OFFSET_TAB_CCRx[] =
{
  0x00U             /* 0: CCR1 */
  , 0x04U           /* 1: CCR2 */
  , 0x08U           /* 2: CCR3 */
  , 0x0CU           /* 3: CCR4 */
  , 0x14U           /* 4: CCR5 */
  , (0x14U + 0x4U)  /* 5: CCR6 */
};

static const uint8_t LL_TIM_SHIFT_TAB_OCxx[] =
{
  0U             /* 0: OC1M, OC1FE, OC1PE  */
  , 0U           /* 1: - NA */
  , 8U           /* 2: OC2M, OC2FE, OC2PE  */
  , 0U           /* 3: - NA */
  , 0U           /* 4: OC3M, OC3FE, OC3PE  */
  , 0U           /* 5: - NA */
  , 8U           /* 6: OC4M, OC4FE, OC4PE  */
  , 0U           /* 7: - NA */
  , 0U           /* 8: OC5M, OC5FE, OC5PE  */
  , 8U           /* 9: OC6M, OC6FE, OC6PE  */
};

static const uint8_t LL_TIM_SHIFT_TAB_ICxx[] =
{
  0U             /* 0: CC1S, IC1PSC, IC1F */
  , 0U           /* 1: - NA */
  , 8U           /* 2: CC2S, IC2PSC, IC2F */
  , 0U           /* 3: - NA */
  , 0U           /* 4: CC3S, IC3PSC, IC3F */
  , 0U           /* 5: - NA */
  , 8U           /* 6: CC4S, IC4PSC, IC4F */
  , 0U           /* 7: - NA */
  , 0U           /* 8: - NA */
  , 0U           /* 9: - NA */
};

static const uint8_t LL_TIM_SHIFT_TAB_CCxP[] =
{
  0U             /* 0: CC1P  */
  , 2U           /* 1: CC1NP */
  , 4U           /* 2: CC2P  */
  , 6U           /* 3: CC2NP */
  , 8U           /* 4: CC3P  */
  , 10U          /* 5: CC3NP */
  , 12U          /* 6: CC4P  */
  , 14U          /* 7: CC4NP */
  , 16U          /* 8: CC5P  */
  , 20U          /* 9: CC6P  */
};

static const uint8_t LL_TIM_SHIFT_TAB_OISx[] =
{
  0U             /* 0: OIS1  */
  , 1U           /* 1: OIS1N */
  , 2U           /* 2: OIS2  */
  , 3U           /* 3: OIS2N */
  , 4U           /* 4: OIS3  */
  , 5U           /* 5: OIS3N */
  , 6U           /* 6: OIS4  */
  , 7U           /* 7: OIS4N */
  , 8U           /* 8: OIS5  */
  , 10U          /* 9: OIS6  */
};

static const uint32_t LL_TIM_MASK_TAB_BKxE[] =
{
  TIM_BDTR_BKE,  /* 0: BKIN */
  TIM_BDTR_BK2E  /* 1: BKIN2 */
};

static const uint32_t LL_TIM_MASK_TAB_BKxP[] =
{
  TIM_BDTR_BKP,  /* 0: BKIN */
  TIM_BDTR_BK2P  /* 1: BKIN2 */
};

static const uint32_t LL_TIM_MASK_TAB_BKxF[] =
{
  TIM_BDTR_BKF,  /* 0: BKIN */
  TIM_BDTR_BK2F  /* 1: BKIN2 */
};

static const uint32_t LL_TIM_MASK_TAB_BKxBID[] =
{
  TIM_BDTR_BKBID,  /* 0: BKIN */
  TIM_BDTR_BK2BID  /* 1: BKIN2 */
};

/* Shift for IC config */
#define LL_TIM_IC_CONFIG_POS  (16U)
/**
  * @}
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup TIM_LL_Private_Constants TIM Private Constants
  * @{
  */


/* Mask used to set the TDG[x:0] of the DTG bits of the TIMx_BDTR register */
#define LL_TIM_DT_DELAY_1 ((uint8_t)0x7F)
#define LL_TIM_DT_DELAY_2 ((uint8_t)0x3F)
#define LL_TIM_DT_DELAY_3 ((uint8_t)0x1F)
#define LL_TIM_DT_DELAY_4 ((uint8_t)0x1F)

/* Mask used to set the DTG[7:5] bits of the DTG bits of the TIMx_BDTR register */
#define LL_TIM_DT_RANGE_1 ((uint8_t)0x00)
#define LL_TIM_DT_RANGE_2 ((uint8_t)0x80)
#define LL_TIM_DT_RANGE_3 ((uint8_t)0xC0)
#define LL_TIM_DT_RANGE_4 ((uint8_t)0xE0)

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup TIM_LL_Private_Macros TIM Private Macros
  * @{
  */

/* Defines used for the bit position in the register and perform offsets */
#define LL_TIM_TIM_POSITION_BRK_SOURCE(source)  \
  (POSITION_VAL((source)) & 0x1FUL)

/** @brief  Convert channel id into channel index.
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval Channel index.
  */
#define LL_TIM_TIM_GET_CHANNEL_INDEX(channel) (((channel) == LL_TIM_CHANNEL_CH1) ? 0U :\
                                               ((channel) == LL_TIM_CHANNEL_CH1N) ? 1U :\
                                               ((channel) == LL_TIM_CHANNEL_CH2) ? 2U :\
                                               ((channel) == LL_TIM_CHANNEL_CH2N) ? 3U :\
                                               ((channel) == LL_TIM_CHANNEL_CH3) ? 4U :\
                                               ((channel) == LL_TIM_CHANNEL_CH3N) ? 5U :\
                                               ((channel) == LL_TIM_CHANNEL_CH4) ? 6U :\
                                               ((channel) == LL_TIM_CHANNEL_CH4N) ? 7U :\
                                               ((channel) == LL_TIM_CHANNEL_CH5) ? 8U : 9U)

/** @brief  Calculate the deadtime sampling period (in ps).
  * @param  tim_clk timer input clock frequency (in Hz).
  * @param  clk_div This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV1
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV2
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV4
  * @retval Deadtime sampling period (in ps).
  */
#define LL_TIM_TIM_CALC_DTS(tim_clk, clk_div) (((clk_div) == LL_TIM_CLOCKDIVISION_DIV1) ? \
                                               ((uint64_t)1000000000000U/(tim_clk)) : \
                                               ((clk_div) == LL_TIM_CLOCKDIVISION_DIV2) ? \
                                               ((uint64_t)1000000000000U/((tim_clk) >> 1U)) : \
                                               ((uint64_t)1000000000000U/((tim_clk) >> 2U)))
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup TIM_LL_Exported_Constants TIM Exported Constants
  * @{
  */

/** @defgroup TIM_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_TIM_READ_REG function.
  * @{
  */
#define LL_TIM_SR_UIF              TIM_SR_UIF              /*!< Update interrupt flag */
#define LL_TIM_SR_CC1IF            TIM_SR_CC1IF            /*!< Capture/compare 1 interrupt flag */
#define LL_TIM_SR_CC2IF            TIM_SR_CC2IF            /*!< Capture/compare 2 interrupt flag */
#define LL_TIM_SR_CC3IF            TIM_SR_CC3IF            /*!< Capture/compare 3 interrupt flag */
#define LL_TIM_SR_CC4IF            TIM_SR_CC4IF            /*!< Capture/compare 4 interrupt flag */
#define LL_TIM_SR_CC5IF            TIM_SR_CC5IF            /*!< Capture/compare 5 interrupt flag */
#define LL_TIM_SR_CC6IF            TIM_SR_CC6IF            /*!< Capture/compare 6 interrupt flag */
#define LL_TIM_SR_COMIF            TIM_SR_COMIF            /*!< COM interrupt flag */
#define LL_TIM_SR_TIF              TIM_SR_TIF              /*!< Trigger interrupt flag */
#define LL_TIM_SR_BIF              TIM_SR_BIF              /*!< Break interrupt flag */
#define LL_TIM_SR_B2IF             TIM_SR_B2IF             /*!< Second break interrupt flag */
#define LL_TIM_SR_SBIF             TIM_SR_SBIF             /*!< System Break interrupt flag  */
#define LL_TIM_SR_CC1OF            TIM_SR_CC1OF            /*!< Capture/Compare 1 overcapture flag */
#define LL_TIM_SR_CC2OF            TIM_SR_CC2OF            /*!< Capture/Compare 2 overcapture flag */
#define LL_TIM_SR_CC3OF            TIM_SR_CC3OF            /*!< Capture/Compare 3 overcapture flag */
#define LL_TIM_SR_CC4OF            TIM_SR_CC4OF            /*!< Capture/Compare 4 overcapture flag */
#define LL_TIM_SR_IDXF             TIM_SR_IDXF             /*!< Index interrupt flag  */
#define LL_TIM_SR_DIRF             TIM_SR_DIRF             /*!< Direction Change interrupt flag  */
#define LL_TIM_SR_IERRF            TIM_SR_IERRF            /*!< Index Error flag  */
#define LL_TIM_SR_TERRF            TIM_SR_TERRF            /*!< Transition Error flag  */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK_ENABLE Break Enable
  * @{
  */
#define LL_TIM_BREAK_DISABLE            0x00000000U        /*!< Break function disabled */
#define LL_TIM_BREAK_ENABLE             TIM_BDTR_BKE       /*!< Break function enabled */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK2_ENABLE Break2 Enable
  * @{
  */
#define LL_TIM_BREAK2_DISABLE            0x00000000U       /*!< Break2 function disabled */
#define LL_TIM_BREAK2_ENABLE             TIM_BDTR_BK2E     /*!< Break2 function enabled */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_AUTOMATICOUTPUT_ENABLE Automatic output enable
  * @{
  */
#define LL_TIM_AUTOMATICOUTPUT_DISABLE      0x00000000U    /*!< MOE can be set only by software */
#define LL_TIM_AUTOMATICOUTPUT_ENABLE       TIM_BDTR_AOE   /*!< MOE can be set by software or automatically
                                                             at the next update event */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_TIM_READ_REG and LL_TIM_WRITE_REG functions.
  * @{
  */
#define LL_TIM_DIER_UIE                        TIM_DIER_UIE         /*!< Update interrupt enable */
#define LL_TIM_DIER_CC1IE                      TIM_DIER_CC1IE       /*!< Capture/compare 1 interrupt enable */
#define LL_TIM_DIER_CC2IE                      TIM_DIER_CC2IE       /*!< Capture/compare 2 interrupt enable */
#define LL_TIM_DIER_CC3IE                      TIM_DIER_CC3IE       /*!< Capture/compare 3 interrupt enable */
#define LL_TIM_DIER_CC4IE                      TIM_DIER_CC4IE       /*!< Capture/compare 4 interrupt enable */
#define LL_TIM_DIER_COMIE                      TIM_DIER_COMIE       /*!< COM interrupt enable */
#define LL_TIM_DIER_TIE                        TIM_DIER_TIE         /*!< Trigger interrupt enable */
#define LL_TIM_DIER_BIE                        TIM_DIER_BIE         /*!< Break interrupt enable */
#define LL_TIM_DIER_IDXIE                      TIM_DIER_IDXIE       /*!< Index interrupt enable */
#define LL_TIM_DIER_DIRIE                      TIM_DIER_DIRIE       /*!< Direction Change interrupt enable */
#define LL_TIM_DIER_IERRIE                     TIM_DIER_IERRIE      /*!< Index Error interrupt enable */
#define LL_TIM_DIER_TERRIE                     TIM_DIER_TERRIE      /*!< Transition Error interrupt enable */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_DMA  DMA request Defines
  * @brief    DMA request defines which can be used with LL_TIM_READ_REG and LL_TIM_WRITE_REG functions.
  * @{
  */
#define LL_TIM_DIER_UDE             TIM_DIER_UDE                    /*!< Update DMA request enable */
#define LL_TIM_DIER_CC1DE           TIM_DIER_CC1DE                  /*!< Capture/compare 1 DMA request enable */
#define LL_TIM_DIER_CC2DE           TIM_DIER_CC2DE                  /*!< Capture/compare 2 DMA request enable */
#define LL_TIM_DIER_CC3DE           TIM_DIER_CC3DE                  /*!< Capture/compare 3 DMA request enable */
#define LL_TIM_DIER_CC4DE           TIM_DIER_CC4DE                  /*!< Capture/compare 4 DMA request enable */
#define LL_TIM_DIER_COMDE           TIM_DIER_COMDE                  /*!< COM DMA request enable */
#define LL_TIM_DIER_TDE             TIM_DIER_TDE                    /*!< Trigger DMA request enable */
/**
  * @}
  *
  */

/** @defgroup TIM_LL_EC_UPDATESOURCE Update Source
  * @{
  */
#define LL_TIM_UPDATESOURCE_REGULAR   0x00000000U    /*!< Counter overflow/underflow, Setting the UG bit or Update
                                                      generation through the slave mode controller
                                                      generates an update request */
#define LL_TIM_UPDATESOURCE_COUNTER   TIM_CR1_URS    /*!< Only counter overflow/underflow generates an update request */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_COUNTERMODE Counter Mode
  * @{
  */
#define LL_TIM_COUNTERMODE_UP              0x00000000U       /*!< Counter used as upcounter */
#define LL_TIM_COUNTERMODE_DOWN            TIM_CR1_DIR       /*!< Counter used as downcounter */
#define LL_TIM_COUNTERMODE_CENTER_DOWN     TIM_CR1_CMS_0     /*!< The counter counts up and down alternatively.
                                                              Output compare interrupt flags of output channels
                                                              are set only when the counter is counting down. */
#define LL_TIM_COUNTERMODE_CENTER_UP       TIM_CR1_CMS_1     /*!< The counter counts up and down alternatively.
                                                              Output compare interrupt flags of output channels
                                                              are set only when the counter is counting up */
#define LL_TIM_COUNTERMODE_CENTER_UP_DOWN  TIM_CR1_CMS       /*!< The counter counts up and down alternatively.
                                                              Output compare interrupt flags of output channels
                                                              are set only when the counter is counting up or down. */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CLOCKDIVISION_DIV Clock Division
  * @{
  */
#define LL_TIM_CLOCKDIVISION_DIV1              0x00000000U                         /*!< tDTS=tTIM_KER_CK   */
#define LL_TIM_CLOCKDIVISION_DIV2              TIM_CR1_CKD_0                       /*!< tDTS=2*tTIM_KER_CK */
#define LL_TIM_CLOCKDIVISION_DIV4              TIM_CR1_CKD_1                       /*!< tDTS=4*tTIM_KER_CK */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_COUNTERDIRECTION Counter Direction
  * @{
  */
#define LL_TIM_COUNTERDIRECTION_UP        0x00000000U /*!< Timer counter counts up */
#define LL_TIM_COUNTERDIRECTION_DOWN      TIM_CR1_DIR /*!< Timer counter counts down */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CCUPDATESOURCE Capture Compare Update Source
  * @{
  */
#define LL_TIM_CCUPDATESOURCE_SOFTWARE               0x00000000U   /*!< Capture/compare control bits are updated
                                                                        by setting the COMG bit only */
#define LL_TIM_CCUPDATESOURCE_SOFTWARE_AND_TRIGGER   TIM_CR2_CCUS  /*!< Capture/compare control bits are updated
                                                                        by setting the COMG bit or when a rising edge
                                                                        occurs on trigger input (TRGI) */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CCDMAREQUEST Capture Compare DMA Request
  * @{
  */
#define LL_TIM_CCDMAREQUEST_CC             0x00000000U      /*!< CCx DMA request sent when CCx event occurs */
#define LL_TIM_CCDMAREQUEST_UPD            TIM_CR2_CCDS     /*!< CCx DMA requests sent when update event occurs */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_LOCKLEVEL Lock Level
  * @{
  */
#define LL_TIM_LOCKLEVEL_OFF                   0x00000000U          /*!< LOCK OFF - No bit is write protected */
#define LL_TIM_LOCKLEVEL_1                     TIM_BDTR_LOCK_0      /*!< LOCK Level 1 */
#define LL_TIM_LOCKLEVEL_2                     TIM_BDTR_LOCK_1      /*!< LOCK Level 2 */
#define LL_TIM_LOCKLEVEL_3                     TIM_BDTR_LOCK        /*!< LOCK Level 3 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CHANNEL Channel
  * @{
  */
#define LL_TIM_CHANNEL_CH1             TIM_CCER_CC1E             /*!< Timer input/output channel 1 */
#define LL_TIM_CHANNEL_CH1N            TIM_CCER_CC1NE            /*!< Timer complementary output channel 1 */
#define LL_TIM_CHANNEL_CH2             TIM_CCER_CC2E             /*!< Timer input/output channel 2 */
#define LL_TIM_CHANNEL_CH2N            TIM_CCER_CC2NE            /*!< Timer complementary output channel 2 */
#define LL_TIM_CHANNEL_CH3             TIM_CCER_CC3E             /*!< Timer input/output channel 3 */
#define LL_TIM_CHANNEL_CH3N            TIM_CCER_CC3NE            /*!< Timer complementary output channel 3 */
#define LL_TIM_CHANNEL_CH4             TIM_CCER_CC4E             /*!< Timer input/output channel 4 */
#define LL_TIM_CHANNEL_CH4N            TIM_CCER_CC4NE            /*!< Timer complementary output channel 4 */
#define LL_TIM_CHANNEL_CH5             TIM_CCER_CC5E             /*!< Timer output channel 5 */
#define LL_TIM_CHANNEL_CH6             TIM_CCER_CC6E             /*!< Timer output channel 6 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OCSTATE Output Configuration State
  * @{
  */
#define LL_TIM_OCSTATE_DISABLE          0x00000000U      /*!< OCx is not active */
#define LL_TIM_OCSTATE_ENABLE           TIM_CCER_CC1E    /*!< OCx signal is output on the corresponding output pin */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OCMODE Output Configuration Mode
  * @{
  */
#define LL_TIM_OCMODE_FROZEN             0x00000000U                            /*!<The comparison between the output
                                                                                 compare register TIMx_CCRy and
                                                                                 the counter TIMx_CNT has no effect on
                                                                                 the output channel level */
#define LL_TIM_OCMODE_ACTIVE_ON_MATCH    TIM_CCMR1_OC1M_0                       /*!<OCyREF is forced high on compare
                                                                                 match */
#define LL_TIM_OCMODE_INACTIVE_ON_MATCH  TIM_CCMR1_OC1M_1                       /*!<OCyREF is forced low on compare
                                                                                 match */
#define LL_TIM_OCMODE_TOGGLE             (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)  /*!<OCyREF toggles on compare match */
#define LL_TIM_OCMODE_FORCED_INACTIVE    TIM_CCMR1_OC1M_2                       /*!<OCyREF is forced low */
#define LL_TIM_OCMODE_FORCED_ACTIVE      (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)  /*!<OCyREF is forced high */
#define LL_TIM_OCMODE_PWM1               (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)  /*!<In upcounting, channel y is active
                                                                                as long as TIMx_CNT<TIMx_CCRy else
                                                                                inactive.In downcounting, channel y
                                                                                is inactive as long as
                                                                                TIMx_CNT>TIMx_CCRy else active */
#define LL_TIM_OCMODE_PWM2               (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 \
                                          | TIM_CCMR1_OC1M_0)                   /*!<In upcounting, channel y is
                                                                                inactive as long as TIMx_CNT<TIMx_CCRy
                                                                                else active. In downcounting, channel y
                                                                                is active as long as TIMx_CNT>TIMx_CCRy
                                                                                else inactive */
#define LL_TIM_OCMODE_RETRIGERRABLE_OPM1  TIM_CCMR1_OC1M_3                       /*!<Retrigerrable OPM mode 1 */
#define LL_TIM_OCMODE_RETRIGERRABLE_OPM2  (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_0)  /*!<Retrigerrable OPM mode 2 */
#define LL_TIM_OCMODE_COMBINED_PWM1      (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2)   /*!<Combined PWM mode 1 */
#define LL_TIM_OCMODE_COMBINED_PWM2      (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2 \
                                          | TIM_CCMR1_OC1M_0)                    /*!<Combined PWM mode 2 */
#define LL_TIM_OCMODE_ASYMMETRIC_PWM1    (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2 \
                                          | TIM_CCMR1_OC1M_1)                    /*!<Asymmetric PWM mode 1 */
#define LL_TIM_OCMODE_ASYMMETRIC_PWM2    (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2 \
                                          | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0) /*!<Asymmetric PWM mode 2 */
#define LL_TIM_OCMODE_PULSE_ON_COMPARE   (TIM_CCMR2_OC3M_3 | TIM_CCMR2_OC3M_1)   /*!<Pulse on Compare mode */
#define LL_TIM_OCMODE_DIRECTION_OUTPUT   (TIM_CCMR2_OC3M_3 | TIM_CCMR2_OC3M_1 \
                                          | TIM_CCMR2_OC3M_0)                    /*!<Direction output mode */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OCPOLARITY Output Configuration Polarity
  * @{
  */
#define LL_TIM_OCPOLARITY_HIGH                 0x00000000U                        /*!< OCx active high */
#define LL_TIM_OCPOLARITY_LOW                  TIM_CCER_CC1P                      /*!< OCx active low */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OCIDLESTATE Output Configuration Idle State
  * @{
  */
#define LL_TIM_OCIDLESTATE_RESET               0x00000000U             /*!< OCx/OCxN=0 (after a dead-time
                                                                       if OC is implemented) when MOE=0 */
#define LL_TIM_OCIDLESTATE_SET                 TIM_CR2_OIS1            /*!< OCx/OCxN=1 (after a dead-time
                                                                       if OC is implemented) when MOE=0 */
/**
  * @}
  */


/** @defgroup TIM_LL_EC_OC_COMPARE_UNIT Compare Unit
  * @{
  */
#define LL_TIM_OC_COMPARE_UNIT_1             0U             /*!< Timer compare unit 1 */
#define LL_TIM_OC_COMPARE_UNIT_2             1U             /*!< Timer compare unit 2 */
#define LL_TIM_OC_COMPARE_UNIT_3             2U             /*!< Timer compare unit 3 */
#define LL_TIM_OC_COMPARE_UNIT_4             3U             /*!< Timer compare unit 4 */
#define LL_TIM_OC_COMPARE_UNIT_5             4U             /*!< Timer compare unit 5 */
#define LL_TIM_OC_COMPARE_UNIT_6             5U             /*!< Timer compare unit 6 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_GROUPCH5 GROUPCH5
  * @{
  */
#define LL_TIM_GROUPCH5_NONE            0x00000000U        /*!< No effect of OC5REF on OC1REFC, OC2REFC and OC3REFC */
#define LL_TIM_GROUPCH5_AND_OC1REFC     TIM_CCR5_GC5C1     /*!< OC1REFC is the logical AND of OC1REFC  and OC5REF */
#define LL_TIM_GROUPCH5_AND_OC2REFC     TIM_CCR5_GC5C2     /*!< OC2REFC is the logical AND of OC2REFC and OC5REF */
#define LL_TIM_GROUPCH5_AND_OC3REFC     TIM_CCR5_GC5C3     /*!< OC3REFC is the logical AND of OC3REFC and OC5REF */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_ACTIVEINPUT Active Input Selection
  * @{
  */
#define LL_TIM_ACTIVEINPUT_DIRECT       (TIM_CCMR1_CC1S_0 << LL_TIM_IC_CONFIG_POS)  /*!< ICx is mapped on TIx */
#define LL_TIM_ACTIVEINPUT_INDIRECT     (TIM_CCMR1_CC1S_1 << LL_TIM_IC_CONFIG_POS)  /*!< ICx is mapped on TIy */
#define LL_TIM_ACTIVEINPUT_TRC          (TIM_CCMR1_CC1S << LL_TIM_IC_CONFIG_POS)    /*!< ICx is mapped on TRC */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_ICPSC Input Configuration Prescaler
  * @{
  */
#define LL_TIM_ICPSC_DIV1        0x00000000U                                /*!< No prescaler, capture is done each time
                                                                             an edge is detected on the capture input */
#define LL_TIM_ICPSC_DIV2        (TIM_CCMR1_IC1PSC_0 << LL_TIM_IC_CONFIG_POS)  /*!< Capture is done once every 2 events */
#define LL_TIM_ICPSC_DIV4        (TIM_CCMR1_IC1PSC_1 << LL_TIM_IC_CONFIG_POS)  /*!< Capture is done once every 4 events */
#define LL_TIM_ICPSC_DIV8        (TIM_CCMR1_IC1PSC << LL_TIM_IC_CONFIG_POS)    /*!< Capture is done once every 8 events */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_IC_FILTER Input Configuration Filter
  * @{
  */
#define LL_TIM_IC_FILTER_FDIV1          0x00000000U                                  /*!< No filter, sampling is done at fDTS */
#define LL_TIM_IC_FILTER_FDIV1_N2       (TIM_CCMR1_IC1F_0 << LL_TIM_IC_CONFIG_POS)      /*!< fSAMPLING=fCK_INT, N=2 */
#define LL_TIM_IC_FILTER_FDIV1_N4       (TIM_CCMR1_IC1F_1 << LL_TIM_IC_CONFIG_POS)      /*!< fSAMPLING=fCK_INT, N=4 */
#define LL_TIM_IC_FILTER_FDIV1_N8       ((TIM_CCMR1_IC1F_1 \
                                          | TIM_CCMR1_IC1F_0) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fCK_INT, N=8 */
#define LL_TIM_IC_FILTER_FDIV2_N6       (TIM_CCMR1_IC1F_2 << LL_TIM_IC_CONFIG_POS)      /*!< fSAMPLING=fDTS/2, N=6 */
#define LL_TIM_IC_FILTER_FDIV2_N8       ((TIM_CCMR1_IC1F_2 \
                                          | TIM_CCMR1_IC1F_0) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/2, N=8 */
#define LL_TIM_IC_FILTER_FDIV4_N6       ((TIM_CCMR1_IC1F_2 \
                                          | TIM_CCMR1_IC1F_1) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/4, N=6 */
#define LL_TIM_IC_FILTER_FDIV4_N8       ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1\
                                          | TIM_CCMR1_IC1F_0) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/4, N=8 */
#define LL_TIM_IC_FILTER_FDIV8_N6       (TIM_CCMR1_IC1F_3 << LL_TIM_IC_CONFIG_POS)      /*!< fSAMPLING=fDTS/8, N=6 */
#define LL_TIM_IC_FILTER_FDIV8_N8       ((TIM_CCMR1_IC1F_3 \
                                          | TIM_CCMR1_IC1F_0) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/8, N=8 */
#define LL_TIM_IC_FILTER_FDIV16_N5      ((TIM_CCMR1_IC1F_3 \
                                          | TIM_CCMR1_IC1F_1) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_IC_FILTER_FDIV16_N6      ((TIM_CCMR1_IC1F_3| TIM_CCMR1_IC1F_1 \
                                          | TIM_CCMR1_IC1F_0) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/16, N=6 */
#define LL_TIM_IC_FILTER_FDIV16_N8      ((TIM_CCMR1_IC1F_3 \
                                          | TIM_CCMR1_IC1F_2) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_IC_FILTER_FDIV32_N5      ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 \
                                          | TIM_CCMR1_IC1F_0) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/32, N=5 */
#define LL_TIM_IC_FILTER_FDIV32_N6      ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 \
                                          | TIM_CCMR1_IC1F_1) << LL_TIM_IC_CONFIG_POS)  /*!< fSAMPLING=fDTS/32, N=6 */
#define LL_TIM_IC_FILTER_FDIV32_N8      (TIM_CCMR1_IC1F << LL_TIM_IC_CONFIG_POS)        /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_IC_POLARITY Input Configuration Polarity
  * @{
  */
#define LL_TIM_IC_POLARITY_RISING           0x00000000U            /*!< The circuit is sensitive to TIxFP1 rising edge,
                                                                   TIxFP1 is not inverted */
#define LL_TIM_IC_POLARITY_FALLING          TIM_CCER_CC1P          /*!< The circuit is sensitive to TIxFP1 falling edge,
                                                                   TIxFP1 is inverted */
#define LL_TIM_IC_POLARITY_RISING_FALLING   (TIM_CCER_CC1P \
                                             | TIM_CCER_CC1NP)     /*!< The circuit is sensitive to both TIxFP1 rising
                                                                   and falling edges, TIxFP1 is not inverted */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CLK Clock Sources
  * @{
  */
#define LL_TIM_CLK_INTERNAL                   0x00000000U                 /*!< The timer is clocked by the internal
                                                                          clock provided from the RCC */
#define LL_TIM_CLK_EXTERNAL_MODE1             (TIM_SMCR_SMS_2 \
                                               | TIM_SMCR_SMS_1 \
                                               | TIM_SMCR_SMS_0)          /*!< Counter counts at each rising or
                                                                          falling edge on a selected input*/
#define LL_TIM_CLK_EXTERNAL_MODE2             TIM_SMCR_ECE                /*!< Counter counts at each rising or falling
                                                                          edge on the external trigger input ETR */
#define LL_TIM_CLK_ENCODER_X1_TI1             (TIM_SMCR_SMS_3 \
                                               | TIM_SMCR_SMS_2 \
                                               | TIM_SMCR_SMS_1)          /*!< Quadrature encoder mode:
                                                                          x1 mode, counting on TI1FP1 edges only,
                                                                          edge sensitivity is set by CC1P */
#define LL_TIM_CLK_ENCODER_X1_TI2             (TIM_SMCR_SMS_3 \
                                               | TIM_SMCR_SMS_2 \
                                               | TIM_SMCR_SMS_1 \
                                               | TIM_SMCR_SMS_0)          /*!< Quadrature encoder mode: x1 mode,
                                                                          counting on TI2FP2 edges only,
                                                                          edge sensitivity is set by CC1P */
#define LL_TIM_CLK_ENCODER_X2_TI1             TIM_SMCR_SMS_0              /*!< Quadrature encoder mode 1:
                                                                          x2 mode, Counter counts up/down
                                                                          on TI1FP1 edge depending on TI2FP2 level */
#define LL_TIM_CLK_ENCODER_X2_TI2             TIM_SMCR_SMS_1              /*!< Quadrature encoder mode 2:
                                                                          x2 mode, Counter counts up/down
                                                                          on TI2FP2 edge depending on TI1FP1 level */
#define LL_TIM_CLK_ENCODER_X4_TI12            (TIM_SMCR_SMS_1 \
                                               | TIM_SMCR_SMS_0)          /*!< Quadrature encoder mode 3:
                                                                          x4 mode, Counter counts up/down
                                                                          on both TI1FP1 and TI2FP2 edges
                                                                          depending on the level of the other input */
#define LL_TIM_CLK_ENCODER_CLK_PLUS_X2        (TIM_SMCR_SMS_3 \
                                               | TIM_SMCR_SMS_1)          /*!< Encoder mode: Clock plus direction,
                                                                          x2 mode */
#define LL_TIM_CLK_ENCODER_CLK_PLUS_X1        (TIM_SMCR_SMS_3 \
                                               | TIM_SMCR_SMS_1 \
                                               | TIM_SMCR_SMS_0)          /*!< Encoder mode:Clock plus direction,
                                                                          x1 mode, TI2FP2 edge sensitivity is set
                                                                          by CC2P */
#define LL_TIM_CLK_ENCODER_DIR_CLK_X2         (TIM_SMCR_SMS_3 \
                                               | TIM_SMCR_SMS_2)          /*!< Encoder mode: Directional Clock,
                                                                          x2 mode */
#define LL_TIM_CLK_ENCODER_DIR_CLK_X1_TI12    (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_2 \
                                               | TIM_SMCR_SMS_0)          /*!< Encoder mode: Directional Clock,
                                                                          x1 mode, TI1FP1 and TI2FP2 edge sensitivity
                                                                          is set by CC1P and CC2P */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TRGO Trigger Output
  * @{
  */
#define LL_TIM_TRGO_RESET        0x00000000U       /*!< UG bit from the TIMx_EGR register is used as trigger output */
#define LL_TIM_TRGO_ENABLE       TIM_CR2_MMS_0     /*!< Counter Enable signal (CNT_EN) is used as trigger output */
#define LL_TIM_TRGO_UPDATE       TIM_CR2_MMS_1                    /*!< Update event is used as trigger output */
#define LL_TIM_TRGO_CC1IF        (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)  /*!< CC1 capture or a compare match is used as trigger
                                                                   output */
#define LL_TIM_TRGO_OC1          TIM_CR2_MMS_2                    /*!< OC1REFC signal is used as trigger output */
#define LL_TIM_TRGO_OC2          (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)  /*!< OC2REFC signal is used as trigger output */
#define LL_TIM_TRGO_OC3          (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)  /*!< OC3REFC signal is used as trigger output */
#define LL_TIM_TRGO_OC4          (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 \
                                  | TIM_CR2_MMS_0)                /*!< OC4REFC signal is used as trigger output */
#define LL_TIM_TRGO_ENCODERCLK   TIM_CR2_MMS_3                    /*!< Encoder clock signal is used as trigger output */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TRGO2 Trigger Output 2
  * @{
  */
#define LL_TIM_TRGO2_RESET      0x00000000U      /*!< UG bit from the TIMx_EGR register is used as trigger output 2 */
#define LL_TIM_TRGO2_ENABLE     TIM_CR2_MMS2_0   /*!< Counter Enable signal (CNT_EN) is used as trigger output 2 */
#define LL_TIM_TRGO2_UPDATE     TIM_CR2_MMS2_1   /*!< Update event is used as trigger output 2 */
#define LL_TIM_TRGO2_CC1F       (TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)     /*!< CC1 capture or a compare match
                                                                      is used as trigger output 2 */
#define LL_TIM_TRGO2_OC1        TIM_CR2_MMS2_2                        /*!< OC1REFC signal is used as trigger output 2 */
#define LL_TIM_TRGO2_OC2        (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_0)     /*!< OC2REFC signal is used as trigger output 2 */
#define LL_TIM_TRGO2_OC3        (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1)     /*!< OC3REFC signal is used as trigger output 2 */
#define LL_TIM_TRGO2_OC4        (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1 \
                                 | TIM_CR2_MMS2_0)                    /*!< OC4REFC signal is used as trigger output 2 */
#define LL_TIM_TRGO2_OC5        TIM_CR2_MMS2_3                        /*!< OC5REFC signal is used as trigger output 2 */
#define LL_TIM_TRGO2_OC6        (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_0)     /*!< OC6REFC signal is used as trigger output 2 */
#define LL_TIM_TRGO2_OC4_RISING_FALLING      (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1)     /*!< OC4REFC rising or falling edges
                                                                                    are used as trigger output 2 */
#define LL_TIM_TRGO2_OC6_RISING_FALLING      (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1 \
                                              | TIM_CR2_MMS2_0)                    /*!< OC6REFC rising or falling edges
                                                                                    are used as trigger output 2 */
#define LL_TIM_TRGO2_OC4_RISING_OC6_RISING   (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2)     /*!< OC4REFC or OC6REFC rising edges
                                                                                    are used as trigger output 2 */
#define LL_TIM_TRGO2_OC5_RISING_OC6_RISING   (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 \
                                              | TIM_CR2_MMS2_1)                     /*!< OC5REFC or OC6REFC rising edges
                                                                                    are used as trigger output 2 */
#define LL_TIM_TRGO2_OC4_RISING_OC6_FALLING  (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 \
                                              | TIM_CR2_MMS2_0)                    /*!< OC4REFC rising or OC6REFC falling
                                                                                   edges are used as trigger output 2 */
#define LL_TIM_TRGO2_OC5_RISING_OC6_FALLING  (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 \
                                              | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)   /*!< OC5REFC rising or OC6REFC falling
                                                                                   edges are used as trigger output 2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_SLAVEMODE Slave Mode
  * @{
  */
#define LL_TIM_SLAVEMODE_DISABLED      0x00000000U                        /*!< Slave mode disabled */
#define LL_TIM_SLAVEMODE_RESET         TIM_SMCR_SMS_2                     /*!< Reset Mode - Rising edge of
                                                                          the selected trigger input (TRGI)
                                                                          reinitializes the counter */
#define LL_TIM_SLAVEMODE_GATED         (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)  /*!< Gated Mode - The counter clock
                                                                          is enabled when the trigger input
                                                                          (TRGI) is high */
#define LL_TIM_SLAVEMODE_TRIGGER       (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)  /*!< Trigger Mode - The counter starts
                                                                          at a rising edge of the trigger TRGI */
#define LL_TIM_SLAVEMODE_COMBINED_RESET_TRIGGER  TIM_SMCR_SMS_3           /*!< Combined reset + trigger mode - Rising
                                                                          edge of the selected trigger input (TRGI)
                                                                          reinitializes the counter, generates an update
                                                                          of the registers and starts the counter */
#define LL_TIM_SLAVEMODE_COMBINED_GATED_RESET    (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_0) /*!< Combined gated + reset mode
                                                                                  - The counter clock is enabled when
                                                                                  the trigger input (TRGI) is high.
                                                                                  The counter stops and is reset) as
                                                                                  soon as the trigger becomes low.Both
                                                                                  startand stop of the counter
                                                                                  are controlled. */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_SMS_PRELOAD_SOURCE SMS Preload Source
  * @{
  */
#define LL_TIM_SLAVE_MODE_PRELOAD_UPDATE   0x00000000U     /*!< The SMS preload transfer is triggered
                                                                by the Timer's Update event */
#define LL_TIM_SLAVE_MODE_PRELOAD_INDEX    TIM_SMCR_SMSPS  /*!< The SMS preload transfer is triggered
                                                                by the Index event */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TS Trigger Selection
  * @{
  */
#define LL_TIM_TS_ITR0      0x00000000U                            /*!< Internal Trigger 0 (ITR0) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR1      TIM_SMCR_TS_0                          /*!< Internal Trigger 1 (ITR1) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR2      TIM_SMCR_TS_1                          /*!< Internal Trigger 2 (ITR2) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR3      (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)        /*!< Internal Trigger 3 (ITR3) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR4      TIM_SMCR_TS_3                          /*!< Internal Trigger 4 (ITR4) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR5      (TIM_SMCR_TS_3 | TIM_SMCR_TS_0)        /*!< Internal Trigger 5 (ITR5) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR6      (TIM_SMCR_TS_3 | TIM_SMCR_TS_1)        /*!< Internal Trigger 6 (ITR6) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR7      (TIM_SMCR_TS_3 | TIM_SMCR_TS_1 \
                             | TIM_SMCR_TS_0)                      /*!< Internal Trigger 7 (ITR7) is used as
                                                                    trigger input */
#define LL_TIM_TS_ITR8      (TIM_SMCR_TS_3 | TIM_SMCR_TS_2)        /*!< Internal Trigger 8 (ITR8) is used as
                                                                    trigger input */
#if defined(USB_OTG_FS)
#define LL_TIM_TS_ITR11     (TIM_SMCR_TS_0 | TIM_SMCR_TS_1 \
                             | TIM_SMCR_TS_2 | TIM_SMCR_TS_3)      /*!< Internal Trigger 11 (ITR11) is used as
                                                                    trigger input */
#endif /* USB_OTG_FS */
#define LL_TIM_TS_TI1F_ED   TIM_SMCR_TS_2                          /*!< TI1 Edge Detector (TI1F_ED) is used as
                                                                    trigger input */
#define LL_TIM_TS_TI1FP1    (TIM_SMCR_TS_2 | TIM_SMCR_TS_0)        /*!< Filtered Timer Input 1 (TI1FP1) is used as
                                                                    trigger input */
#define LL_TIM_TS_TI2FP2    (TIM_SMCR_TS_2 | TIM_SMCR_TS_1)        /*!< Filtered Timer Input 2 (TI12P2) is used as
                                                                    trigger input */
#define LL_TIM_TS_ETRF      (TIM_SMCR_TS_2 | TIM_SMCR_TS_1 \
                             | TIM_SMCR_TS_0)                      /*!< Filtered external Trigger (ETRF) is used as
                                                                    trigger input */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_ETR_POLARITY External Trigger Polarity
  * @{
  */
#define LL_TIM_ETR_POLARITY_NONINVERTED   0x00000000U   /*!< ETR is non-inverted, active at high level or rising edge */
#define LL_TIM_ETR_POLARITY_INVERTED      TIM_SMCR_ETP  /*!< ETR is inverted, active at low level or falling edge */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_ETR_PRESCALER External Trigger Prescaler
  * @{
  */
#define LL_TIM_ETR_PRESCALER_DIV1              0x00000000U             /*!< ETR prescaler OFF */
#define LL_TIM_ETR_PRESCALER_DIV2              TIM_SMCR_ETPS_0         /*!< ETR frequency is divided by 2 */
#define LL_TIM_ETR_PRESCALER_DIV4              TIM_SMCR_ETPS_1         /*!< ETR frequency is divided by 4 */
#define LL_TIM_ETR_PRESCALER_DIV8              TIM_SMCR_ETPS           /*!< ETR frequency is divided by 8 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_ETR_FILTER External Trigger Filter
  * @{
  */
#define LL_TIM_ETR_FILTER_FDIV1         0x00000000U                          /*!< No filter, sampling is done at fDTS */
#define LL_TIM_ETR_FILTER_FDIV1_N2      TIM_SMCR_ETF_0                       /*!< fSAMPLING=fCK_INT, N=2 */
#define LL_TIM_ETR_FILTER_FDIV1_N4      TIM_SMCR_ETF_1                       /*!< fSAMPLING=fCK_INT, N=4 */
#define LL_TIM_ETR_FILTER_FDIV1_N8      (TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)    /*!< fSAMPLING=fCK_INT, N=8 */
#define LL_TIM_ETR_FILTER_FDIV2_N6      TIM_SMCR_ETF_2                       /*!< fSAMPLING=fDTS/2, N=6 */
#define LL_TIM_ETR_FILTER_FDIV2_N8      (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)    /*!< fSAMPLING=fDTS/2, N=8 */
#define LL_TIM_ETR_FILTER_FDIV4_N6      (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)    /*!< fSAMPLING=fDTS/4, N=6 */
#define LL_TIM_ETR_FILTER_FDIV4_N8      (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 \
                                         | TIM_SMCR_ETF_0)                   /*!< fSAMPLING=fDTS/4, N=8 */
#define LL_TIM_ETR_FILTER_FDIV8_N6      TIM_SMCR_ETF_3                       /*!< fSAMPLING=fDTS/8, N=6 */
#define LL_TIM_ETR_FILTER_FDIV8_N8      (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_0)    /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_ETR_FILTER_FDIV16_N5     (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1)    /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_ETR_FILTER_FDIV16_N6     (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1 \
                                         | TIM_SMCR_ETF_0)                   /*!< fSAMPLING=fDTS/16, N=6 */
#define LL_TIM_ETR_FILTER_FDIV16_N8     (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2)    /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_ETR_FILTER_FDIV32_N5     (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 \
                                         | TIM_SMCR_ETF_0)                   /*!< fSAMPLING=fDTS/32, N=5 */
#define LL_TIM_ETR_FILTER_FDIV32_N6     (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 \
                                         | TIM_SMCR_ETF_1)                   /*!< fSAMPLING=fDTS/32, N=6 */
#define LL_TIM_ETR_FILTER_FDIV32_N8     TIM_SMCR_ETF                         /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM1_ETRSOURCE External Trigger Source TIM1
  * @{
  */
#define LL_TIM_TIM1_ETRSOURCE_GPIO        0x00000000U                                                  /*!< ETR input is connected to GPIO */
#define LL_TIM_TIM1_ETRSOURCE_COMP1       TIM1_AF1_ETRSEL_0                                            /*!< ETR input is connected to COMP1_OUT */
#if defined (COMP2)
#define LL_TIM_TIM1_ETRSOURCE_COMP2       TIM1_AF1_ETRSEL_1                                            /*!< ETR input is connected to COMP2_OUT */
#endif /* COMP2 */
#define LL_TIM_TIM1_ETRSOURCE_MSIK        (TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)                      /*!< ETR input is connected to MSIK */
#define LL_TIM_TIM1_ETRSOURCE_HSI         TIM1_AF1_ETRSEL_2                                            /*!< ETR input is connected to HSI */
#define LL_TIM_TIM1_ETRSOURCE_MSIS        (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)                      /*!< ETR input is connected to MSIS */
#if defined(ADC2)
#define LL_TIM_TIM1_ETRSOURCE_ADC2_AWD2   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)                      /*!< ADC2 analog watchdog 2 */
#define LL_TIM_TIM1_ETRSOURCE_ADC2_AWD3   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1| TIM1_AF1_ETRSEL_0)   /*!< ADC2 analog watchdog 3 */
#endif /* ADC2*/
#define LL_TIM_TIM1_ETRSOURCE_ADC1_AWD1   TIM1_AF1_ETRSEL_3                                            /*!< ADC1 analog watchdog 1 */
#define LL_TIM_TIM1_ETRSOURCE_ADC1_AWD2   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_0)                      /*!< ADC1 analog watchdog 2 */
#define LL_TIM_TIM1_ETRSOURCE_ADC1_AWD3   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1)                      /*!< ADC1 analog watchdog 3 */
#define LL_TIM_TIM1_ETRSOURCE_ADC4_AWD1   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)  /*!< ADC4 analog watchdog 1 */
#define LL_TIM_TIM1_ETRSOURCE_ADC4_AWD2   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2)                      /*!< ADC4 analog watchdog 2 */
#define LL_TIM_TIM1_ETRSOURCE_ADC4_AWD3   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)  /*!< ADC4 analog watchdog 3 */
#if defined(ADC2)
#define LL_TIM_TIM1_ETRSOURCE_ADC2_AWD1   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)  /*!< ADC2 analog watchdog 1 */
#endif /* ADC2*/
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM2_ETRSOURCE External Trigger Source TIM2
  * @{
  */
#define LL_TIM_TIM2_ETRSOURCE_GPIO         0x00000000U                                                 /*!< ETR input is connected to GPIO */
#define LL_TIM_TIM2_ETRSOURCE_COMP1        TIM1_AF1_ETRSEL_0                                           /*!< ETR input is connected to COMP1_OUT */
#if defined (COMP2)
#define LL_TIM_TIM2_ETRSOURCE_COMP2        TIM1_AF1_ETRSEL_1                                           /*!< ETR input is connected to COMP2_OUT */
#endif /* COMP2 */
#define LL_TIM_TIM2_ETRSOURCE_MSIK         (TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIK */
#define LL_TIM_TIM2_ETRSOURCE_HSI          TIM1_AF1_ETRSEL_2                                           /*!< ETR input is connected to HSI */
#define LL_TIM_TIM2_ETRSOURCE_MSIS         (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIS */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM2_ETRSOURCE_DCMI_VSYNC        (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)                /*!< ETR input is connected to DCMI VSYNC   */
#define LL_TIM_TIM2_ETRSOURCE_LTDC_VSYNC        (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1| TIM1_AF1_ETRSEL_0)  /*!< ETR input is connected to LTDC_VSYNC   */
#endif /* DCMI && LTDC */
#define LL_TIM_TIM2_ETRSOURCE_TIM3_ETR     TIM1_AF1_ETRSEL_3                                           /*!< ETR input is connected to TIM3 ETR */
#define LL_TIM_TIM2_ETRSOURCE_TIM4_ETR     (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to TIM4 ETR */
#define LL_TIM_TIM2_ETRSOURCE_TIM5_ETR     (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1)                     /*!< ETR input is connected to TIM5 ETR */
#define LL_TIM_TIM2_ETRSOURCE_LSE          (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to LSE */
#if defined(DSI)
#define LL_TIM_TIM2_ETRSOURCE_DSI_TE       (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to DSI_TE       */
#endif /* DSI */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM2_ETRSOURCE_DCMI_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1) /*!< ETR input is connected to DCMI HSYNC   */
#define LL_TIM_TIM2_ETRSOURCE_LTDC_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to LTDC HSYNC   */
#endif /* DCMI && LTDC */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM3_ETRSOURCE External Trigger Source TIM3
  * @{
  */
#define LL_TIM_TIM3_ETRSOURCE_GPIO         0x00000000U                                                 /*!< ETR input is connected to GPIO */
#define LL_TIM_TIM3_ETRSOURCE_COMP1        TIM1_AF1_ETRSEL_0                                           /*!< ETR input is connected to COMP1_OUT */
#if defined (COMP2)
#define LL_TIM_TIM3_ETRSOURCE_COMP2        TIM1_AF1_ETRSEL_1                                           /*!< ETR input is connected to COMP2_OUT */
#endif /* COMP2 */
#define LL_TIM_TIM3_ETRSOURCE_MSIK         (TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIK */
#define LL_TIM_TIM3_ETRSOURCE_HSI          TIM1_AF1_ETRSEL_2                                           /*!< ETR input is connected to HSI */
#define LL_TIM_TIM3_ETRSOURCE_MSIS         (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIS */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM3_ETRSOURCE_DCMI_VSYNC   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)                     /*!< ETR input is connected to DCMI VSYNC   */
#define LL_TIM_TIM3_ETRSOURCE_LTDC_VSYNC   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1| TIM1_AF1_ETRSEL_0)  /*!< ETR input is connected to LTDC_VSYNC   */
#endif /* DCMI && LTDC */
#define LL_TIM_TIM3_ETRSOURCE_TIM2_ETR     TIM1_AF1_ETRSEL_3                                           /*!< ETR input is connected to TIM2 ETR */
#define LL_TIM_TIM3_ETRSOURCE_TIM4_ETR     (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to TIM4 ETR */
#if defined(DSI)
#define LL_TIM_TIM3_ETRSOURCE_DSI_TE       (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1)                     /*!< ETR input is connected to DSI_TE       */
#endif /* DSI */
#define LL_TIM_TIM3_ETRSOURCE_ADC1_AWD1    (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ADC1 analog watchdog 1 */
#define LL_TIM_TIM3_ETRSOURCE_ADC1_AWD2    (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2)                     /*!< ADC1 analog watchdog 2 */
#define LL_TIM_TIM3_ETRSOURCE_ADC1_AWD3    (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0) /*!< ADC1 analog watchdog 3 */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM3_ETRSOURCE_DCMI_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1) /*!< ETR input is connected to DCMI HSYNC   */
#define LL_TIM_TIM3_ETRSOURCE_LTDC_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to LTDC HSYNC   */
#endif /* DCMI && LTDC */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM4_ETRSOURCE External Trigger Source TIM4
  * @{
  */
#define LL_TIM_TIM4_ETRSOURCE_GPIO         0x00000000U                                                 /*!< ETR input is connected to GPIO */
#define LL_TIM_TIM4_ETRSOURCE_COMP1        TIM1_AF1_ETRSEL_0                                           /*!< ETR input is connected to COMP1_OUT */
#if defined (COMP2)
#define LL_TIM_TIM4_ETRSOURCE_COMP2        TIM1_AF1_ETRSEL_1                                           /*!< ETR input is connected to COMP2_OUT */
#endif /* COMP2 */
#define LL_TIM_TIM4_ETRSOURCE_MSIK         (TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIK */
#define LL_TIM_TIM4_ETRSOURCE_HSI          TIM1_AF1_ETRSEL_2                                           /*!< ETR input is connected to HSI */
#define LL_TIM_TIM4_ETRSOURCE_MSIS         (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIS */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM4_ETRSOURCE_DCMI_VSYNC   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)                     /*!< ETR input is connected to DCMI VSYNC   */
#define LL_TIM_TIM4_ETRSOURCE_LTDC_VSYNC   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1| TIM1_AF1_ETRSEL_0)  /*!< ETR input is connected to LTDC_VSYNC   */
#endif /* DCMI && LTDC */
#define LL_TIM_TIM4_ETRSOURCE_TIM3_ETR     TIM1_AF1_ETRSEL_3                                           /*!< ETR input is connected to TIM3 ETR */
#define LL_TIM_TIM4_ETRSOURCE_TIM5_ETR     (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to TIM5 ETR */
#if defined(DSI)
#define LL_TIM_TIM4_ETRSOURCE_DSI_TE       (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1)                     /*!< TIM2_ETR is connected to DSI_TE       */
#endif /* DSI */
#if defined(ADC2)
#define LL_TIM_TIM4_ETRSOURCE_ADC2_AWD1    (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to ADC2 AWD1    */
#define LL_TIM_TIM4_ETRSOURCE_ADC2_AWD2    (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2)                     /*!< ETR input is connected to ADC2 AWD2    */
#define LL_TIM_TIM4_ETRSOURCE_ADC2_AWD3    (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to ADC2 AWD3    */
#endif /* ADC2 */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM4_ETRSOURCE_DCMI_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1) /*!< ETR input is connected to DCMI HSYNC   */
#define LL_TIM_TIM4_ETRSOURCE_LTDC_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to LTDC HSYNC   */
#endif /* DCMI && LTDC */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM5_ETRSOURCE External Trigger Source TIM5
  * @{
  */
#define LL_TIM_TIM5_ETRSOURCE_GPIO         0x00000000U                                                 /*!< ETR input is connected to GPIO */
#define LL_TIM_TIM5_ETRSOURCE_COMP1        TIM1_AF1_ETRSEL_0                                           /*!< ETR input is connected to COMP1_OUT */
#if defined (COMP2)
#define LL_TIM_TIM5_ETRSOURCE_COMP2        TIM1_AF1_ETRSEL_1                                           /*!< ETR input is connected to COMP2_OUT */
#endif /* COMP2 */
#define LL_TIM_TIM5_ETRSOURCE_MSIK         (TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIK */
#define LL_TIM_TIM5_ETRSOURCE_HSI          TIM1_AF1_ETRSEL_2                                           /*!< ETR input is connected to HSI */
#define LL_TIM_TIM5_ETRSOURCE_MSIS         (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to MSIS */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM5_ETRSOURCE_DCMI_VSYNC   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)                     /*!< ETR input is connected to DCMI VSYNC   */
#define LL_TIM_TIM5_ETRSOURCE_LTDC_VSYNC   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to LTDC_VSYNC   */
#endif /* DCMI && LTDC */
#define LL_TIM_TIM5_ETRSOURCE_TIM2_ETR     TIM1_AF1_ETRSEL_3                                           /*!< ETR input is connected to TIM2 ETR */
#define LL_TIM_TIM5_ETRSOURCE_TIM3_ETR     (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_0)                     /*!< ETR input is connected to TIM3 ETR */
#if defined(DSI)
#define LL_TIM_TIM5_ETRSOURCE_DSI_TE       (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1)                     /*!< ETR input is connected to DSI_TE       */
#endif /* DSI */
#if defined(DCMI) && defined(LTDC)
#define LL_TIM_TIM5_ETRSOURCE_DCMI_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1) /*!< ETR input is connected to DCMI HSYNC   */
#define LL_TIM_TIM5_ETRSOURCE_LTDC_HSYNC   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0) /*!< ETR input is connected to LTDC HSYNC   */
#endif /* DCMI && LTDC */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM8_ETRSOURCE External Trigger Source TIM8
  * @{
  */
#define LL_TIM_TIM8_ETRSOURCE_GPIO        0x00000000U                                                  /*!< ETR input is connected to GPIO */
#define LL_TIM_TIM8_ETRSOURCE_COMP1       TIM1_AF1_ETRSEL_0                                            /*!< ETR input is connected to COMP1_OUT */
#if defined (COMP2)
#define LL_TIM_TIM8_ETRSOURCE_COMP2       TIM1_AF1_ETRSEL_1                                            /*!< ETR input is connected to COMP2_OUT */
#endif /* COMP2 */
#define LL_TIM_TIM8_ETRSOURCE_MSIK        (TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)                      /*!< ETR input is connected to MSIK */
#define LL_TIM_TIM8_ETRSOURCE_HSI         TIM1_AF1_ETRSEL_2                                            /*!< ETR input is connected to HSI */
#define LL_TIM_TIM8_ETRSOURCE_MSIS        (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)                      /*!< ETR input is connected to MSIS */
#if defined (ADC2)
#define LL_TIM_TIM8_ETRSOURCE_ADC2_AWD2   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)                      /*!< ETR input is connected to ADC2 AWD2    */
#define LL_TIM_TIM8_ETRSOURCE_ADC2_AWD3   (TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1| TIM1_AF1_ETRSEL_0)   /*!< ETR input is connected to ADC2 AWD3    */
#endif /* ADC2 */
#define LL_TIM_TIM8_ETRSOURCE_ADC1_AWD1   TIM1_AF1_ETRSEL_3                                            /*!< ADC1 analog watchdog 1 */
#define LL_TIM_TIM8_ETRSOURCE_ADC1_AWD2   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_0)                      /*!< ADC1 analog watchdog 2 */
#define LL_TIM_TIM8_ETRSOURCE_ADC1_AWD3   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1)                      /*!< ADC1 analog watchdog 3 */
#define LL_TIM_TIM8_ETRSOURCE_ADC4_AWD1   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_1 | TIM1_AF1_ETRSEL_0)  /*!< ADC4 analog watchdog 1 */
#define LL_TIM_TIM8_ETRSOURCE_ADC4_AWD2   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2)                      /*!< ADC4 analog watchdog 2 */
#define LL_TIM_TIM8_ETRSOURCE_ADC4_AWD3   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_0)  /*!< ADC4 analog watchdog 3 */
#if defined (ADC2)
#define LL_TIM_TIM8_ETRSOURCE_ADC2_AWD1   (TIM1_AF1_ETRSEL_3 | TIM1_AF1_ETRSEL_2 | TIM1_AF1_ETRSEL_1)  /*!< ETR input is connected to ADC2 AWD1    */
#endif /* ADC2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK_POLARITY break polarity
  * @{
  */
#define LL_TIM_BREAK_POLARITY_LOW              0x00000000U               /*!< Break input BRK is active low */
#define LL_TIM_BREAK_POLARITY_HIGH             TIM_BDTR_BKP              /*!< Break input BRK is active high */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK_FILTER break filter
  * @{
  */
#define LL_TIM_BREAK_FILTER_FDIV1              0x00000000U   /*!< No filter, BRK acts asynchronously */
#define LL_TIM_BREAK_FILTER_FDIV1_N2           0x00010000U   /*!< fSAMPLING=fCK_INT, N=2 */
#define LL_TIM_BREAK_FILTER_FDIV1_N4           0x00020000U   /*!< fSAMPLING=fCK_INT, N=4 */
#define LL_TIM_BREAK_FILTER_FDIV1_N8           0x00030000U   /*!< fSAMPLING=fCK_INT, N=8 */
#define LL_TIM_BREAK_FILTER_FDIV2_N6           0x00040000U   /*!< fSAMPLING=fDTS/2, N=6 */
#define LL_TIM_BREAK_FILTER_FDIV2_N8           0x00050000U   /*!< fSAMPLING=fDTS/2, N=8 */
#define LL_TIM_BREAK_FILTER_FDIV4_N6           0x00060000U   /*!< fSAMPLING=fDTS/4, N=6 */
#define LL_TIM_BREAK_FILTER_FDIV4_N8           0x00070000U   /*!< fSAMPLING=fDTS/4, N=8 */
#define LL_TIM_BREAK_FILTER_FDIV8_N6           0x00080000U   /*!< fSAMPLING=fDTS/8, N=6 */
#define LL_TIM_BREAK_FILTER_FDIV8_N8           0x00090000U   /*!< fSAMPLING=fDTS/8, N=8 */
#define LL_TIM_BREAK_FILTER_FDIV16_N5          0x000A0000U   /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_BREAK_FILTER_FDIV16_N6          0x000B0000U   /*!< fSAMPLING=fDTS/16, N=6 */
#define LL_TIM_BREAK_FILTER_FDIV16_N8          0x000C0000U   /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_BREAK_FILTER_FDIV32_N5          0x000D0000U   /*!< fSAMPLING=fDTS/32, N=5 */
#define LL_TIM_BREAK_FILTER_FDIV32_N6          0x000E0000U   /*!< fSAMPLING=fDTS/32, N=6 */
#define LL_TIM_BREAK_FILTER_FDIV32_N8          0x000F0000U   /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK2_POLARITY BREAK2 POLARITY
  * @{
  */
#define LL_TIM_BREAK2_POLARITY_LOW             0x00000000U             /*!< Break input BRK2 is active low */
#define LL_TIM_BREAK2_POLARITY_HIGH            TIM_BDTR_BK2P           /*!< Break input BRK2 is active high */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK2_FILTER BREAK2 FILTER
  * @{
  */
#define LL_TIM_BREAK2_FILTER_FDIV1             0x00000000U   /*!< No filter, BRK acts asynchronously */
#define LL_TIM_BREAK2_FILTER_FDIV1_N2          0x00100000U   /*!< fSAMPLING=fCK_INT, N=2 */
#define LL_TIM_BREAK2_FILTER_FDIV1_N4          0x00200000U   /*!< fSAMPLING=fCK_INT, N=4 */
#define LL_TIM_BREAK2_FILTER_FDIV1_N8          0x00300000U   /*!< fSAMPLING=fCK_INT, N=8 */
#define LL_TIM_BREAK2_FILTER_FDIV2_N6          0x00400000U   /*!< fSAMPLING=fDTS/2, N=6 */
#define LL_TIM_BREAK2_FILTER_FDIV2_N8          0x00500000U   /*!< fSAMPLING=fDTS/2, N=8 */
#define LL_TIM_BREAK2_FILTER_FDIV4_N6          0x00600000U   /*!< fSAMPLING=fDTS/4, N=6 */
#define LL_TIM_BREAK2_FILTER_FDIV4_N8          0x00700000U   /*!< fSAMPLING=fDTS/4, N=8 */
#define LL_TIM_BREAK2_FILTER_FDIV8_N6          0x00800000U   /*!< fSAMPLING=fDTS/8, N=6 */
#define LL_TIM_BREAK2_FILTER_FDIV8_N8          0x00900000U   /*!< fSAMPLING=fDTS/8, N=8 */
#define LL_TIM_BREAK2_FILTER_FDIV16_N5         0x00A00000U   /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_BREAK2_FILTER_FDIV16_N6         0x00B00000U   /*!< fSAMPLING=fDTS/16, N=6 */
#define LL_TIM_BREAK2_FILTER_FDIV16_N8         0x00C00000U   /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_BREAK2_FILTER_FDIV32_N5         0x00D00000U   /*!< fSAMPLING=fDTS/32, N=5 */
#define LL_TIM_BREAK2_FILTER_FDIV32_N6         0x00E00000U   /*!< fSAMPLING=fDTS/32, N=6 */
#define LL_TIM_BREAK2_FILTER_FDIV32_N8         0x00F00000U   /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OSSI OSSI
  * @{
  */
#define LL_TIM_OSSI_DISABLE      0x00000000U       /*!< When inactive, OCx/OCxN outputs are disabled */
#define LL_TIM_OSSI_ENABLE       TIM_BDTR_OSSI     /*!< When inactive, OxC/OCxN outputs are first forced with their
                                                        inactive level then forced to their idle level after the 
                                                        deadtime */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OSSR OSSR
  * @{
  */
#define LL_TIM_OSSR_DISABLE      0x00000000U       /*!< When inactive, OCx/OCxN outputs are disabled */
#define LL_TIM_OSSR_ENABLE       TIM_BDTR_OSSR     /*!< When inactive, OCx/OCxN outputs are enabled with their inactive
                                                        level as soon as CCxE=1 or CCxNE=1 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK_INPUT BREAK INPUT
  * @{
  */
#define LL_TIM_BREAK_INPUT_1                   0x00000000U  /*!< TIMx_BKIN input */
#define LL_TIM_BREAK_INPUT_2                   0x00000001U  /*!< TIMx_BKIN2 input */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BKIN_SOURCE BKIN SOURCE
  * @{
  */
#define LL_TIM_BKIN_SOURCE_GPIO                TIM1_AF1_BKINE      /*!< BKIN input from AF controller */
#define LL_TIM_BKIN_SOURCE_COMP1               TIM1_AF1_BKCMP1E    /*!< internal signal: COMP1 output */
#if defined(COMP2)
#define LL_TIM_BKIN_SOURCE_COMP2               TIM1_AF1_BKCMP2E    /*!< internal signal: COMP2 output */
#endif /* COMP2 */
#define LL_TIM_BKIN_SOURCE_MDF1                TIM1_AF1_BKDF1BK0E  /*!< internal signal: Digital filter break output */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BKIN_POLARITY BKIN POLARITY
  * @{
  */
#define LL_TIM_BREAK_INPUT_SRC_NONINVERTED     0x00000000U              /*!< BRK BKIN input is active high */
#define LL_TIM_BREAK_INPUT_SRC_INVERTED        TIM1_AF1_BKINP            /*!< BRK BKIN input is active low */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK_AFMODE BREAK AF MODE
  * @{
  */
#define LL_TIM_BREAK_AFMODE_INPUT              0x00000000U              /*!< Break input BRK in input mode */
#define LL_TIM_BREAK_AFMODE_BIDIRECTIONAL      TIM_BDTR_BKBID           /*!< Break input BRK in bidirectional mode */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_BREAK2_AFMODE BREAK2 AF MODE
  * @{
  */
#define LL_TIM_BREAK2_AFMODE_INPUT             0x00000000U             /*!< Break2 input BRK2 in input mode */
#define LL_TIM_BREAK2_AFMODE_BIDIRECTIONAL     TIM_BDTR_BK2BID         /*!< Break2 input BRK2 in bidirectional mode */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_DMABURST_BASEADDR DMA Burst Base Address
  * @{
  */
#define LL_TIM_DMABURST_BASEADDR_CR1            0x00000000U                        /*!< TIMx_CR1 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CR2            TIM_DCR_DBA_0                      /*!< TIMx_CR2 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_SMCR           TIM_DCR_DBA_1                      /*!< TIMx_SMCR register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_DIER           (TIM_DCR_DBA_1 |  TIM_DCR_DBA_0)   /*!< TIMx_DIER register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_SR             TIM_DCR_DBA_2                      /*!< TIMx_SR register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_EGR            (TIM_DCR_DBA_2 | TIM_DCR_DBA_0)    /*!< TIMx_EGR register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCMR1          (TIM_DCR_DBA_2 | TIM_DCR_DBA_1)    /*!< TIMx_CCMR1 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCMR2          (TIM_DCR_DBA_2 | TIM_DCR_DBA_1 \
                                                 | TIM_DCR_DBA_0)                  /*!< TIMx_CCMR2 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCER           TIM_DCR_DBA_3                      /*!< TIMx_CCER register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CNT            (TIM_DCR_DBA_3 | TIM_DCR_DBA_0)    /*!< TIMx_CNT register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_PSC            (TIM_DCR_DBA_3 | TIM_DCR_DBA_1)    /*!< TIMx_PSC register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_ARR            (TIM_DCR_DBA_3 | TIM_DCR_DBA_1 \
                                                 | TIM_DCR_DBA_0)                  /*!< TIMx_ARR register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_RCR            (TIM_DCR_DBA_3 | TIM_DCR_DBA_2)    /*!< TIMx_RCR register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCR1           (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 \
                                                 | TIM_DCR_DBA_0)                  /*!< TIMx_CCR1 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCR2           (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 \
                                                 | TIM_DCR_DBA_1)                  /*!< TIMx_CCR2 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCR3           (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 \
                                                 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0)  /*!< TIMx_CCR3 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCR4           TIM_DCR_DBA_4                      /*!< TIMx_CCR4 register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_BDTR           (TIM_DCR_DBA_4 | TIM_DCR_DBA_0)    /*!< TIMx_BDTR register is the DMA
                                                                                        base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCR5           (TIM_DCR_DBA_4 | TIM_DCR_DBA_1)                                  /*!< TIMx_CCR5 register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCR6           (TIM_DCR_DBA_4 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0)                  /*!< TIMx_CCR6 register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_CCMR3          (TIM_DCR_DBA_4 | TIM_DCR_DBA_2)                                  /*!< TIMx_CCMR3 register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_DTR2           (TIM_DCR_DBA_4 | TIM_DCR_DBA_2 | TIM_DCR_DBA_0)                  /*!< TIMx_DTR2 register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_ECR            (TIM_DCR_DBA_4 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1)                  /*!< TIMx_ECR register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_TISEL          (TIM_DCR_DBA_4 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0)  /*!< TIMx_TISEL register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_AF1           (TIM_DCR_DBA_4 | TIM_DCR_DBA_3)                                  /*!< TIMx_AF1 register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_AF2           (TIM_DCR_DBA_4 | TIM_DCR_DBA_3 | TIM_DCR_DBA_0)                  /*!< TIMx_AF2 register is the DMA base address for DMA burst */
#define LL_TIM_DMABURST_BASEADDR_OR1           (TIM_DCR_DBA_4 | TIM_DCR_DBA_3 | TIM_DCR_DBA_1)                  /*!< TIMx_OR1 register is the DMA base address for DMA burst */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_DMABURST_LENGTH DMA Burst Length
  * @{
  */
#define LL_TIM_DMABURST_LENGTH_1TRANSFER       0x00000000U                        /*!< Transfer is done to 1 register
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_2TRANSFERS      TIM_DCR_DBL_0                      /*!< Transfer is done to 2 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_3TRANSFERS      TIM_DCR_DBL_1                      /*!< Transfer is done to 3 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_4TRANSFERS      (TIM_DCR_DBL_1 | TIM_DCR_DBL_0)    /*!< Transfer is done to 4 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_5TRANSFERS      TIM_DCR_DBL_2                      /*!< Transfer is done to 5 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_6TRANSFERS      (TIM_DCR_DBL_2 | TIM_DCR_DBL_0)    /*!< Transfer is done to 6 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_7TRANSFERS      (TIM_DCR_DBL_2 | TIM_DCR_DBL_1)    /*!< Transfer is done to 7 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_8TRANSFERS      (TIM_DCR_DBL_2 | TIM_DCR_DBL_1 \
                                                | TIM_DCR_DBL_0)                  /*!< Transfer is done to 1 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_9TRANSFERS      TIM_DCR_DBL_3                      /*!< Transfer is done to 9 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_10TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_0)    /*!< Transfer is done to 10 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_11TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_1)    /*!< Transfer is done to 11 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_12TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_1 \
                                                | TIM_DCR_DBL_0)                  /*!< Transfer is done to 12 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_13TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2)    /*!< Transfer is done to 13 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_14TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 \
                                                | TIM_DCR_DBL_0)                  /*!< Transfer is done to 14 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_15TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 \
                                                | TIM_DCR_DBL_1)                  /*!< Transfer is done to 15 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_16TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 \
                                                | TIM_DCR_DBL_1 | TIM_DCR_DBL_0)  /*!< Transfer is done to 16 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_17TRANSFERS     TIM_DCR_DBL_4                      /*!< Transfer is done to 17 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_18TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_0)    /*!< Transfer is done to 18 registers
                                                                                  starting from the DMA burst base
                                                                                  address */
#define LL_TIM_DMABURST_LENGTH_19TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_1)                                 /*!< Transfer is done to 19 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_20TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0)                 /*!< Transfer is done to 20 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_21TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_2)                                 /*!< Transfer is done to 21 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_22TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_2 | TIM_DCR_DBL_0)                 /*!< Transfer is done to 22 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_23TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_2 | TIM_DCR_DBL_1)                 /*!< Transfer is done to 23 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_24TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_2 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0) /*!< Transfer is done to 24 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_25TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_3)                                 /*!< Transfer is done to 25 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_26TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_3 | TIM_DCR_DBL_0)                 /*!< Transfer is done to 26 registers starting from the DMA burst base address */
#define LL_TIM_DMABURST_LENGTH_27TRANSFERS     (TIM_DCR_DBL_4 | TIM_DCR_DBL_3 | TIM_DCR_DBL_1)                 /*!< Transfer is done to 27 registers starting from the DMA burst base address */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_DMABURST_SOURCE DMA Burst Source
  * @{
  */
#define LL_TIM_DMABURST_UPD                    TIM_DCR_DBSS_0                                                  /*!< Transfer source is update event */
#define LL_TIM_DMABURST_CC1                    TIM_DCR_DBSS_1                                                  /*!< Transfer source is CC1 event */
#define LL_TIM_DMABURST_CC2                    (TIM_DCR_DBSS_1 |  TIM_DCR_DBSS_0)                              /*!< Transfer source is CC2 event */
#define LL_TIM_DMABURST_CC3                    TIM_DCR_DBSS_2                                                  /*!< Transfer source is CC3 event */
#define LL_TIM_DMABURST_CC4                    (TIM_DCR_DBSS_2 | TIM_DCR_DBSS_0)                               /*!< Transfer source is CC4 event */
#define LL_TIM_DMABURST_COM                    (TIM_DCR_DBSS_2 | TIM_DCR_DBSS_1)                               /*!< Transfer source is COM event */
#define LL_TIM_DMABURST_TRGI                   (TIM_DCR_DBSS_2 | TIM_DCR_DBSS_1 | TIM_DCR_DBSS_0)              /*!< Transfer source is trigger event */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM1_TI1_RMP  TIM1 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM1_TI1_RMP_GPIO                 0x00000000U                                        /*!< TIM1 TI1 is connected to GPIO */
#define LL_TIM_TIM1_TI1_RMP_COMP1                TIM_TISEL_TI1SEL_0                                 /*!< TIM1 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM1_TI1_RMP_COMP2                TIM_TISEL_TI1SEL_1                                 /*!< TIM1 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM1_TI2_RMP  TIM1 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM1_TI2_RMP_GPIO                 0x00000000U                                        /*!< TIM1 TI2 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM1_TI3_RMP  TIM1 External Input Ch3 Remap
  * @{
  */
#define LL_TIM_TIM1_TI3_RMP_GPIO                 0x00000000U                                        /*!< TIM1 TI3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM1_TI4_RMP  TIM1 External Input Ch4 Remap
  * @{
  */
#define LL_TIM_TIM1_TI4_RMP_GPIO                 0x00000000U                                        /*!< TIM1 TI4 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM2_TI1_RMP  TIM2 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM2_TI1_RMP_GPIO                0x00000000U                                        /*!< TIM2 TI1 is connected to GPIO */
#define LL_TIM_TIM2_TI1_RMP_COMP1               TIM_TISEL_TI1SEL_0                                 /*!< TIM2 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM2_TI1_RMP_COMP2               TIM_TISEL_TI1SEL_1                                 /*!< TIM2 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM2_TI2_RMP  TIM16 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM2_TI2_RMP_GPIO                0x00000000U                                        /*!< TIM2 TI2 is connected to GPIO */
#define LL_TIM_TIM2_TI2_RMP_COMP1               TIM_TISEL_TI2SEL_0                                 /*!< TIM2 TI2 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM2_TI2_RMP_COMP2               TIM_TISEL_TI2SEL_1                                 /*!< TIM2 TI2 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM2_TI3_RMP  TIM2 External Input Ch3 Remap
  * @{
  */
#define LL_TIM_TIM2_TI3_RMP_GPIO                 0x00000000U                                        /*!< TIM2 TI3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM2_TI4_RMP  TIM2 External Input Ch4 Remap
  * @{
  */
#define LL_TIM_TIM2_TI4_RMP_GPIO                0x00000000U                                       /*!< TIM2 TI4 is connected to COMP1 output */
#define LL_TIM_TIM2_TI4_RMP_COMP1               TIM_TISEL_TI4SEL_0                                /*!< TIM2 TI4 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM2_TI4_RMP_COMP2               TIM_TISEL_TI4SEL_1                                /*!< TIM2 TI4 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM3_TI1_RMP  TIM3 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM3_TI1_RMP_GPIO                0x00000000U                                        /*!< TIM3 TI1 is connected to GPIO */
#define LL_TIM_TIM3_TI1_RMP_COMP1               TIM_TISEL_TI1SEL_0                                 /*!< TIM3 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM3_TI1_RMP_COMP2               TIM_TISEL_TI1SEL_1                                 /*!< TIM3 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM3_TI2_RMP  TIM3 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM3_TI2_RMP_GPIO                0x00000000U                                        /*!< TIM3 TI2 is connected to GPIO */
#define LL_TIM_TIM3_TI2_RMP_COMP1               TIM_TISEL_TI2SEL_0                                 /*!< TIM3 TI2 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM3_TI2_RMP_COMP2               TIM_TISEL_TI2SEL_1                                 /*!< TIM3 TI2 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM3_TI3_RMP  TIM3 External Input Ch3 Remap
  * @{
  */
#define LL_TIM_TIM3_TI3_RMP_GPIO                 0x00000000U                                        /*!< TIM3 TI3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM3_TI4_RMP  TIM3 External Input Ch4 Remap
  * @{
  */
#define LL_TIM_TIM3_TI4_RMP_GPIO                 0x00000000U                                        /*!< TIM3 TI4 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM4_TI1_RMP  TIM4 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM4_TI1_RMP_GPIO                0x00000000U                                        /*!< TIM4 TI1 is connected to GPIO */
#define LL_TIM_TIM4_TI1_RMP_COMP1               TIM_TISEL_TI1SEL_0                                 /*!< TIM4 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM4_TI1_RMP_COMP2               TIM_TISEL_TI1SEL_1                                 /*!< TIM4 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM4_TI2_RMP  TIM4 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM4_TI2_RMP_GPIO                0x00000000U                                        /*!< TIM4 TI2 is connected to GPIO */
#define LL_TIM_TIM4_TI2_RMP_COMP1               TIM_TISEL_TI2SEL_0                                 /*!< TIM4 TI2 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM4_TI2_RMP_COMP2               TIM_TISEL_TI2SEL_1                                 /*!< TIM4 TI2 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM4_TI3_RMP  TIM4 External Input Ch3 Remap
  * @{
  */
#define LL_TIM_TIM4_TI3_RMP_GPIO                 0x00000000U                                        /*!< TIM4 TI3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM4_TI4_RMP  TIM4 External Input Ch4 Remap
  * @{
  */
#define LL_TIM_TIM4_TI4_RMP_GPIO                 0x00000000U                                        /*!< TIM4 TI4 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM5_TI1_RMP  TIM5 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM5_TI1_RMP_GPIO               0x00000000U                                        /*!<  TIM5 TI1 is connected to GPIO */
#define LL_TIM_TIM5_TI1_RMP_LSI                TIM_TISEL_TI1SEL_0                                 /*!<  TIM5 TI1 is connected to LSI */
#define LL_TIM_TIM5_TI1_RMP_LSE                TIM_TISEL_TI1SEL_1                                 /*!<  TIM5 TI1 is connected to LSE */
#define LL_TIM_TIM5_TI1_RMP_RTC_WKUP           (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)          /*!<  TIM5 TI1 is connected to RTC Wakeup */
#define LL_TIM_TIM5_TI1_RMP_COMP1              TIM_TISEL_TI1SEL_2                                 /*!<  TIM5 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM5_TI1_RMP_COMP2              (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_0)          /*!<  TIM5 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM5_TI2_RMP  TIM5 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM5_TI2_RMP_GPIO               0x00000000U                                        /*!< TIM5 TI2 is connected to GPIO */
#define LL_TIM_TIM5_TI2_RMP_COMP1              TIM_TISEL_TI2SEL_0                                 /*!< TIM5 TI2 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM5_TI2_RMP_COMP2              TIM_TISEL_TI2SEL_1                                 /*!< TIM5 TI2 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM5_TI3_RMP  TIM5 External Input Ch3 Remap
  * @{
  */
#define LL_TIM_TIM5_TI3_RMP_GPIO                 0x00000000U                                        /*!< TIM5 TI3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM5_TI4_RMP  TIM5 External Input Ch4 Remap
  * @{
  */
#define LL_TIM_TIM5_TI4_RMP_GPIO                 0x00000000U                                        /*!< TIM5 TI4 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM8_TI1_RMP  TIM8 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM8_TI1_RMP_GPIO               0x00000000U                                        /*!< TIM8 TI1 is connected to GPIO */
#define LL_TIM_TIM8_TI1_RMP_COMP1              TIM_TISEL_TI1SEL_0                                 /*!< TIM8 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM8_TI1_RMP_COMP2              TIM_TISEL_TI1SEL_1                                 /*!< TIM8 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM8_TI2_RMP  TIM8 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM8_TI2_RMP_GPIO                 0x00000000U                                        /*!< TIM8 TI2 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM8_TI3_RMP  TIM8 External Input Ch3 Remap
  * @{
  */
#define LL_TIM_TIM8_TI3_RMP_GPIO                 0x00000000U                                        /*!< TIM8 TI3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM8_TI4_RMP  TIM8 External Input Ch4 Remap
  * @{
  */
#define LL_TIM_TIM8_TI4_RMP_GPIO                 0x00000000U                                        /*!< TIM8 TI4 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM15_TI1_RMP  TIM15 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM15_TI1_RMP_GPIO              0x00000000U                                        /*!< TIM15 TI1 is connected to GPIO */
#define LL_TIM_TIM15_TI1_RMP_LSE               TIM_TISEL_TI1SEL_0                                 /*!< TIM15 TI1 is connected to LSE */
#define LL_TIM_TIM15_TI1_RMP_COMP1             TIM_TISEL_TI1SEL_1                                 /*!< TIM15 TI1 is connected to COMP1 output */
#if defined(COMP2)
#define LL_TIM_TIM15_TI1_RMP_COMP2             (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)          /*!< TIM15 TI1 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM15_TI2_RMP  TIM15 External Input Ch2 Remap
  * @{
  */
#define LL_TIM_TIM15_TI2_RMP_GPIO              0x00000000U                                        /*!< TIM15 TI2 is connected to GPIO */
#if defined(COMP2)
#define LL_TIM_TIM15_TI2_RMP_COMP2              TIM_TISEL_TI2SEL_0                                /*!< TIM15 TI2 is connected to COMP2 output */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM16_TI1_RMP  TIM16 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM16_TI1_RMP_GPIO              0x00000000U                                                    /*!< TIM16 TI1 is connected to GPIO */
#define LL_TIM_TIM16_TI1_RMP_MCO               TIM_TISEL_TI1SEL_1                                             /*!< TIM16 TI1 is connected to MCO */
#define LL_TIM_TIM16_TI1_RMP_HSE_DIV32         (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)                      /*!< TIM16 TI1 is connected to HSE Div32 */
#define LL_TIM_TIM16_TI1_RMP_RTC_WKUP          TIM_TISEL_TI1SEL_2                                             /*!< TIM16 TI1 is connected to RTC Wakeup */
#define LL_TIM_TIM16_TI1_RMP_LSE               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_0)                      /*!< TIM16 TI1 is connected to LSE */
#define LL_TIM_TIM16_TI1_RMP_LSI               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1)                      /*!< TIM16 TI1 is connected to LSI */
#define LL_TIM_TIM16_TI1_RMP_MSIS_DIV1024      (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0) /*!< TIM16 TI1 is connected to MSIS/1024 */
#define LL_TIM_TIM16_TI1_RMP_MSIS_DIV4         TIM_TISEL_TI1SEL_3                                             /*!< TIM16 TI1 is connected to MSIS/4 */
#define LL_TIM_TIM16_TI1_RMP_HSI_DIV256        (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_0)                      /*!< TIM16 TI1 is connected to HSI/256 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_TIM17_TI1_RMP  TIM17 External Input Ch1 Remap
  * @{
  */
#define LL_TIM_TIM17_TI1_RMP_GPIO              0x00000000U                                                    /*!< TIM17 TI1 is connected to GPIO */
#define LL_TIM_TIM17_TI1_RMP_MCO               TIM_TISEL_TI1SEL_1                                             /*!< TIM17 TI1 is connected to MCO */
#define LL_TIM_TIM17_TI1_RMP_HSE_DIV32         (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)                      /*!< TIM17 TI1 is connected to HSE Div32 */
#define LL_TIM_TIM17_TI1_RMP_RTC_WKUP          TIM_TISEL_TI1SEL_2                                             /*!< TIM17 TI1 is connected to RTC Wakeup */
#define LL_TIM_TIM17_TI1_RMP_LSE               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_0)                      /*!< TIM17 TI1 is connected to LSE */
#define LL_TIM_TIM17_TI1_RMP_LSI               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1)                      /*!< TIM17 TI1 is connected to LSI */
#define LL_TIM_TIM17_TI1_RMP_MSIS_DIV1024      (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0) /*!< TIM17 TI1 is connected to MSIS/1024 */
#define LL_TIM_TIM17_TI1_RMP_MSIS_DIV4         TIM_TISEL_TI1SEL_3                                             /*!< TIM17 TI1 is connected to MSIS/4 */
#define LL_TIM_TIM17_TI1_RMP_HSI_DIV256        (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_0)                      /*!< TIM17 TI1 is connected to HSI/256 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OCREF_CLR_INT OCREF clear input selection
  * @{
  */
#define LL_TIM_OCREF_CLR_INT_ETR         TIM_SMCR_OCCS      /*!< OCREF_CLR_INT is connected to ETRF */
#define LL_TIM_OCREF_CLR_INT_COMP1       0x00000000U                 /*!< OCREF clear input is connected to COMP1_OUT */
#if defined(COMP2)
#define LL_TIM_OCREF_CLR_INT_COMP2       TIM1_AF2_OCRSEL_0           /*!< OCREF clear input is connected to COMP2_OUT */
#endif /* COMP2 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_INDEX_DIR index direction selection
  * @{
  */
#define LL_TIM_INDEX_UP_DOWN     0x00000000U         /*!< Index resets the counter whatever the direction */
#define LL_TIM_INDEX_UP          TIM_ECR_IDIR_0      /*!< Index resets the counter when up-counting only */
#define LL_TIM_INDEX_DOWN        TIM_ECR_IDIR_1      /*!< Index resets the counter when down-counting only */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_INDEX_BLANK index blanking selection
  * @{
  */
#define LL_TIM_INDEX_BLANK_ALWAYS     0x00000000U         /*!< Index always active */
#define LL_TIM_INDEX_BLANK_TI3        TIM_ECR_IBLK_0      /*!< Index disabled when TI3 input is active,
                                                           as per CC3P bitfield */
#define LL_TIM_INDEX_BLANK_TI4        TIM_ECR_IBLK_1      /*!< Index disabled when TI4 input is active,
                                                           as per CC4P bitfield */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_INDEX_POSITION index positioning selection
  * @{
  */
#define LL_TIM_INDEX_POSITION_DOWN_DOWN    0x00000000U                  /*!< Index resets the counter when AB = 00 */
#define LL_TIM_INDEX_POSITION_DOWN_UP      TIM_ECR_IPOS_0               /*!< Index resets the counter when AB = 01 */
#define LL_TIM_INDEX_POSITION_UP_DOWN      TIM_ECR_IPOS_1               /*!< Index resets the counter when AB = 10 */
#define LL_TIM_INDEX_POSITION_UP_UP        (TIM_ECR_IPOS_1 \
                                            | TIM_ECR_IPOS_0)           /*!< Index resets the counter when AB = 11 */
#define LL_TIM_INDEX_POSITION_DOWN         0x00000000U                  /*!< Index resets the counter when clock is 0 */
#define LL_TIM_INDEX_POSITION_UP           TIM_ECR_IPOS_0               /*!< Index resets the counter when clock is 1 */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_FIRST_INDEX first index selection
  * @{
  */
#define LL_TIM_INDEX_ALL           0x00000000U                           /*!< Index is always active */
#define LL_TIM_INDEX_FIRST_ONLY    TIM_ECR_FIDX                          /*!< The first Index only resets the counter */
/**
  * @}
  */
/** @defgroup TIM_LL_EC_PWPRSC Pulse on compare pulse width prescaler
  * @{
  */
#define LL_TIM_PWPRSC_DIV1     0x00000000U                           /*!< Pulse on compare pulse width prescaler 1 */
#define LL_TIM_PWPRSC_DIV2     TIM_ECR_PWPRSC_0                      /*!< Pulse on compare pulse width prescaler 2 */
#define LL_TIM_PWPRSC_DIV4     TIM_ECR_PWPRSC_1                      /*!< Pulse on compare pulse width prescaler 4 */
#define LL_TIM_PWPRSC_DIV8     (TIM_ECR_PWPRSC_1 | TIM_ECR_PWPRSC_0) /*!< Pulse on compare pulse width prescaler 8 */
#define LL_TIM_PWPRSC_DIV16    TIM_ECR_PWPRSC_2                      /*!< Pulse on compare pulse width prescaler 16 */
#define LL_TIM_PWPRSC_DIV32    (TIM_ECR_PWPRSC_2 | TIM_ECR_PWPRSC_0) /*!< Pulse on compare pulse width prescaler 32 */
#define LL_TIM_PWPRSC_DIV64    (TIM_ECR_PWPRSC_2 | TIM_ECR_PWPRSC_1) /*!< Pulse on compare pulse width prescaler 64 */
#define LL_TIM_PWPRSC_DIV128   (TIM_ECR_PWPRSC_2 | TIM_ECR_PWPRSC_1 \
                                | TIM_ECR_PWPRSC_0)                  /*!< Pulse on compare pulse width prescaler 128 */
/**
  * @}
  */


/** @defgroup TIM_LL_EC_SW_EVENT Software Event
  * @{
  */
#define LL_TIM_SW_EVENT_UPD       TIM_EGR_UG      /*!< Update generation */
#define LL_TIM_SW_EVENT_CC1       TIM_EGR_CC1G    /*!< Capture/Compare 1 generation */
#define LL_TIM_SW_EVENT_CC2       TIM_EGR_CC2G    /*!< Capture/Compare 2 generation */
#define LL_TIM_SW_EVENT_CC3       TIM_EGR_CC3G    /*!< Capture/Compare 3 generation */
#define LL_TIM_SW_EVENT_CC4       TIM_EGR_CC4G    /*!< Capture/Compare 4 generation */
#define LL_TIM_SW_EVENT_COM       TIM_EGR_COMG    /*!< Commutation generation */
#define LL_TIM_SW_EVENT_TRGI      TIM_EGR_TG      /*!< Trigger generation */
#define LL_TIM_SW_EVENT_BRK       TIM_EGR_BG      /*!< Break generation */
#define LL_TIM_SW_EVENT_BRK2      TIM_EGR_B2G     /*!< Break 2 generation */

/** Legacy definitions for compatibility purpose
  * @cond LEGACY_DEFINITIONS
  */
#define LL_TIM_BKIN_SOURCE_DFBK  LL_TIM_BKIN_SOURCE_DF1BK
/**
  * @endcond
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup TIM_LL_Exported_Macros TIM Exported Macros
  * @{
  */

/** @defgroup TIM_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */
/**
  * @brief  Write a value in TIM register.
  * @param  instance TIM Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_TIM_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in TIM register.
  * @param  instance TIM Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_TIM_READ_REG(instance, reg) READ_REG((instance)->reg)
/**
  * @}
  */

/**
  * @brief  HELPER macro retrieving the UIFCPY flag from the counter value.
  * @param  cnt Counter value
  * @note   e.g. LL_TIM_GETFLAG_UIFCPY (@ref LL_TIM_GetCounter ());
  * @note   Relevant only if UIF flag remapping has been enabled  (UIF status bit is copied
  *         to TIMx_CNT register bit 31)
  * @retval UIF status bit
  */
#define LL_TIM_GETFLAG_UIFCPY(cnt)  \
  (READ_BIT((cnt), TIM_CNT_UIFCPY) >> TIM_CNT_UIFCPY_Pos)

/**
  * @brief  HELPER macro calculating DTG[0:7] in the TIMx_BDTR register to achieve the requested dead time duration.
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  clk_div This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV1
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV2
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV4
  * @param  dt deadtime duration (in ns)
  * @note   e.g. LL_TIM_CALC_DEADTIME(80000000, @ref LL_TIM_GetClockDivision(), 120);
  * @retval DTG[0:7]
  */
#define LL_TIM_CALC_DEADTIME(tim_clk, clk_div, dt)  \
  ( (((uint64_t)((dt)*1000U)) < ((LL_TIM_DT_DELAY_1+1U) * LL_TIM_TIM_CALC_DTS((tim_clk), (clk_div))))    ?  \
    (uint8_t)(((uint64_t)((dt)*1000U) / LL_TIM_TIM_CALC_DTS((tim_clk), (clk_div)))  & LL_TIM_DT_DELAY_1) :      \
    (((uint64_t)((dt)*1000U)) < ((64U + (LL_TIM_DT_DELAY_2+1U)) * 2U * LL_TIM_TIM_CALC_DTS((tim_clk), (clk_div))))  ?  \
    (uint8_t)(LL_TIM_DT_RANGE_2 | ((uint8_t)((uint8_t)((((uint64_t)((dt)*1000U))/ LL_TIM_TIM_CALC_DTS((tim_clk),   \
                                                        (clk_div))) >> 1U) - (uint8_t) 64) & LL_TIM_DT_DELAY_2)) :\
    (((uint64_t)((dt)*1000U)) < ((32U + (LL_TIM_DT_DELAY_3+1U)) * 8U * LL_TIM_TIM_CALC_DTS((tim_clk), (clk_div))))  ?  \
    (uint8_t)(LL_TIM_DT_RANGE_3 | ((uint8_t)((uint8_t)(((((uint64_t)(dt)*1000U))/ LL_TIM_TIM_CALC_DTS((tim_clk),  \
                                                        (clk_div))) >> 3U) - (uint8_t) 32) & LL_TIM_DT_DELAY_3)) :\
    (((uint64_t)((dt)*1000U)) < ((32U + (LL_TIM_DT_DELAY_4+1U)) * 16U * LL_TIM_TIM_CALC_DTS((tim_clk), (clk_div)))) ?  \
    (uint8_t)(LL_TIM_DT_RANGE_4 | ((uint8_t)((uint8_t)(((((uint64_t)(dt)*1000U))/ LL_TIM_TIM_CALC_DTS((tim_clk),  \
                                                        (clk_div))) >> 4U) - (uint8_t) 32) & LL_TIM_DT_DELAY_4)) :\
    0U)

/**
  * @brief  HELPER macro calculating the prescaler value to achieve the required counter clock frequency.
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  cnt_clk counter clock frequency (in Hz)
  * @note   e.g. LL_TIM_CALC_PSC(80000000, 1000000);
  * @retval Prescaler value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_PSC(tim_clk, cnt_clk)   \
  (((tim_clk) >= (cnt_clk)) ? (uint32_t)((((tim_clk) + (cnt_clk)/2U)/(cnt_clk)) - 1U) : 0U)

/**
  * @brief  HELPER macro calculating the auto-reload value to achieve the required output signal frequency.
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  psc prescaler
  * @param  freq output signal frequency (in Hz)
  * @note   e.g. LL_TIM_CALC_ARR(1000000, @ref LL_TIM_GetPrescaler(), 10000);
  * @retval  Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_ARR(tim_clk, psc, freq) \
  ((((tim_clk)/((psc) + 1U)) >= (freq)) ? (((tim_clk)/((freq) * ((psc) + 1U))) - 1U) : 0U)

/**
  * @brief  HELPER macro calculating the auto-reload value, with dithering feature enabled, to achieve the required
  *         output signal frequency.
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  psc prescaler
  * @param  freq output signal frequency (in Hz)
  * @note   e.g. LL_TIM_CALC_ARR_DITHER(1000000, @ref LL_TIM_GetPrescaler(), 10000);
  * @retval  Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_ARR_DITHER(tim_clk, psc, freq) \
  ((((tim_clk)/((psc) + 1U)) >= (freq)) ? \
   (uint32_t)((((uint64_t)(tim_clk) * 16U/((freq) * ((psc) + 1U))) - 16U)) : 0U)

/**
  * @brief  HELPER macro calculating the compare value required to achieve the required timer output compare
  *         active/inactive delay.
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  psc prescaler
  * @param  delay timer output compare active/inactive delay (in us)
  * @note   e.g. LL_TIM_CALC_DELAY(1000000, @ref LL_TIM_GetPrescaler(), 10);
  * @retval Compare value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_DELAY(tim_clk, psc, delay)  \
  ((uint32_t)(((uint64_t)(tim_clk) * (uint64_t)(delay)) \
              / ((uint64_t)1000000U * (uint64_t)((psc) + 1U))))

/**
  * @brief  HELPER macro calculating the compare value, with dithering feature enabled, to achieve the required timer
  *         output compare active/inactive delay.
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  psc prescaler
  * @param  delay timer output compare active/inactive delay (in us)
  * @note   e.g. LL_TIM_CALC_DELAY_DITHER(1000000, @ref LL_TIM_GetPrescaler(), 10);
  * @retval Compare value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_DELAY_DITHER(tim_clk, psc, delay)  \
  ((uint32_t)(((uint64_t)(tim_clk) * (uint64_t)(delay) * 16U) \
              / ((uint64_t)1000000U * (uint64_t)((psc) + 1U))))

/**
  * @brief  HELPER macro calculating the auto-reload value to achieve the required pulse duration
  *         (when the timer operates in one pulse mode).
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  psc prescaler
  * @param  delay timer output compare active/inactive delay (in us)
  * @param  pulse pulse duration (in us)
  * @note   e.g. LL_TIM_CALC_PULSE(1000000, @ref LL_TIM_GetPrescaler(), 10, 20);
  * @retval Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_PULSE(tim_clk, psc, delay, pulse)  \
  ((uint32_t)(LL_TIM_CALC_DELAY((tim_clk), (psc), (pulse)) \
              + LL_TIM_CALC_DELAY((tim_clk), (psc), (delay))))

/**
  * @brief  HELPER macro calculating the auto-reload value, with dithering feature enabled, to achieve the required
  *         pulse duration (when the timer operates in one pulse mode).
  * @param  tim_clk timer input clock frequency (in Hz)
  * @param  psc prescaler
  * @param  delay timer output compare active/inactive delay (in us)
  * @param  pulse pulse duration (in us)
  * @note   e.g. LL_TIM_CALC_PULSE_DITHER(1000000, @ref LL_TIM_GetPrescaler(), 10, 20);
  * @retval Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define LL_TIM_CALC_PULSE_DITHER(tim_clk, psc, delay, pulse)  \
  ((uint32_t)(LL_TIM_CALC_DELAY_DITHER((tim_clk), (psc), (pulse)) \
              + LL_TIM_CALC_DELAY_DITHER((tim_clk), (psc), (delay))))

/**
  * @brief  HELPER macro retrieving the ratio of the input capture prescaler
  * @param  ic_psc This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ICPSC_DIV1
  *         @arg @ref LL_TIM_ICPSC_DIV2
  *         @arg @ref LL_TIM_ICPSC_DIV4
  *         @arg @ref LL_TIM_ICPSC_DIV8
  * @note   e.g. LL_TIM_GET_ICPSC_RATIO(@ref LL_TIM_IC_GetPrescaler());
  * @retval Input capture prescaler ratio (1, 2, 4 or 8)
  */
#define LL_TIM_GET_ICPSC_RATIO(ic_psc)  \
  ((uint32_t)(0x01U << (((ic_psc) >> 16U) >> TIM_CCMR1_IC1PSC_Pos)))


/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup TIM_LL_Exported_Functions TIM Exported Functions
  * @{
  */

/** @defgroup TIM_LL_EF_Time_Base Time Base configuration
  * @{
  */
/**
  * @brief  Enable timer counter.
  * @rmtoll
  *  CR1          CEN           LL_TIM_EnableCounter
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableCounter(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR1, TIM_CR1_CEN);
}

/**
  * @brief  Disable timer counter.
  * @rmtoll
  *  CR1          CEN           LL_TIM_DisableCounter
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableCounter(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR1, TIM_CR1_CEN);
}

/**
  * @brief  Indicates whether the timer counter is enabled.
  * @rmtoll
  *  CR1          CEN           LL_TIM_IsEnabledCounter
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledCounter(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR1, TIM_CR1_CEN) == (TIM_CR1_CEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable update event generation.
  * @rmtoll
  *  CR1          UDIS          LL_TIM_EnableUpdateEvent
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableUpdateEvent(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR1, TIM_CR1_UDIS);
}

/**
  * @brief  Disable update event generation.
  * @rmtoll
  *  CR1          UDIS          LL_TIM_DisableUpdateEvent
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableUpdateEvent(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR1, TIM_CR1_UDIS);
}

/**
  * @brief  Indicates whether update event generation is enabled.
  * @rmtoll
  *  CR1          UDIS          LL_TIM_IsEnabledUpdateEvent
  * @param  timx Timer instance
  * @retval Inverted state of bit (0 or 1).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledUpdateEvent(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR1, TIM_CR1_UDIS) == (uint32_t)RESET) ? 1UL : 0UL);
}

/**
  * @brief  Set update event source
  * @note Update event source set to LL_TIM_UPDATESOURCE_REGULAR: any of the following events
  *       generate an update interrupt or DMA request if enabled:
  *        - Counter overflow/underflow
  *        - Setting the UG bit
  *        - Update generation through the slave mode controller
  * @note Update event source set to LL_TIM_UPDATESOURCE_COUNTER: only counter
  *       overflow/underflow generates an update interrupt or DMA request if enabled.
  * @rmtoll
  *  CR1          URS           LL_TIM_SetUpdateSource
  * @param  timx Timer instance
  * @param  update_source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_UPDATESOURCE_REGULAR
  *         @arg @ref LL_TIM_UPDATESOURCE_COUNTER
  */
__STATIC_INLINE void LL_TIM_SetUpdateSource(TIM_TypeDef *timx, uint32_t update_source)
{
  MODIFY_REG(timx->CR1, TIM_CR1_URS, update_source);
}

/**
  * @brief  Get actual event update source
  * @rmtoll
  *  CR1          URS           LL_TIM_GetUpdateSource
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_UPDATESOURCE_REGULAR
  *         @arg @ref LL_TIM_UPDATESOURCE_COUNTER
  */
__STATIC_INLINE uint32_t LL_TIM_GetUpdateSource(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CR1, TIM_CR1_URS));
}

/**
  * @brief  Enable one-pulse mode (OPM).
  * @rmtoll
  *  CR1          OPM           LL_TIM_EnableOnePulseMode
  * @param  timx Timer instance
  * @note   When OPM is set, the timer stops counting at the next update event (UEV).
  */
__STATIC_INLINE void LL_TIM_EnableOnePulseMode(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR1, TIM_CR1_OPM);
}

/**
  * @brief  Disable one-pulse mode (OPM).
  * @rmtoll
  *  CR1          OPM           LL_TIM_DisableOnePulseMode
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableOnePulseMode(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR1, TIM_CR1_OPM);
}

/**
  * @brief  Indicates whether one-pulse mode (OPM) is enabled.
  * @rmtoll
  *  CR1          OPM           LL_TIM_IsEnabledOnePulseMode
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledOnePulseMode(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR1, TIM_CR1_OPM) == (TIM_CR1_OPM)) ? 1UL : 0UL);
}

/**
  * @brief  Set the timer counter counting mode.
  * @note Macro IS_TIM_COUNTER_MODE_SELECT_INSTANCE(timx) can be used to
  *       check whether or not the counter mode selection feature is supported
  *       by a timer instance.
  * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
  *       requires a timer reset to avoid unexpected direction
  *       due to DIR bit readonly in center aligned mode.
  * @rmtoll
  *  CR1          DIR           LL_TIM_SetCounterMode \n
  *  CR1          CMS           LL_TIM_SetCounterMode
  * @param  timx Timer instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_COUNTERMODE_UP
  *         @arg @ref LL_TIM_COUNTERMODE_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP_DOWN
  */
__STATIC_INLINE void LL_TIM_SetCounterMode(TIM_TypeDef *timx, uint32_t mode)
{
  MODIFY_REG(timx->CR1, (TIM_CR1_DIR | TIM_CR1_CMS), mode);
}

/**
  * @brief  Get actual counter mode.
  * @note Macro IS_TIM_COUNTER_MODE_SELECT_INSTANCE(timx) can be used to
  *       check whether or not the counter mode selection feature is supported
  *       by a timer instance.
  * @rmtoll
  *  CR1          DIR           LL_TIM_GetCounterMode \n
  *  CR1          CMS           LL_TIM_GetCounterMode
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_COUNTERMODE_UP
  *         @arg @ref LL_TIM_COUNTERMODE_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP_DOWN
  */
__STATIC_INLINE uint32_t LL_TIM_GetCounterMode(const TIM_TypeDef *timx)
{
  uint32_t counter_mode;

  counter_mode = (uint32_t)(READ_BIT(timx->CR1, TIM_CR1_CMS));

  if (counter_mode == 0U)
  {
    counter_mode = (uint32_t)(READ_BIT(timx->CR1, TIM_CR1_DIR));
  }

  return counter_mode;
}

/**
  * @brief  Enable auto-reload (ARR) preload.
  * @rmtoll
  *  CR1          ARPE          LL_TIM_EnableARRPreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableARRPreload(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR1, TIM_CR1_ARPE);
}

/**
  * @brief  Disable auto-reload (ARR) preload.
  * @rmtoll
  *  CR1          ARPE          LL_TIM_DisableARRPreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableARRPreload(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR1, TIM_CR1_ARPE);
}

/**
  * @brief  Indicates whether auto-reload (ARR) preload is enabled.
  * @rmtoll
  *  CR1          ARPE          LL_TIM_IsEnabledARRPreload
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledARRPreload(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR1, TIM_CR1_ARPE) == (TIM_CR1_ARPE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the division ratio between the timer kernel clock (tim_ker_ck) and the DTS sampling clock (DTS_ck)
  *         used by the dead-time generators (when supported), the break/break2 filters and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(timx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @rmtoll
  *  CR1          CKD           LL_TIM_SetClockDivision
  * @param  timx Timer instance
  * @param  clock_division This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV1
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV2
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV4
  */
__STATIC_INLINE void LL_TIM_SetClockDivision(TIM_TypeDef *timx, uint32_t clock_division)
{
  MODIFY_REG(timx->CR1, TIM_CR1_CKD, clock_division);
}

/**
  * @brief  Get the actual division ratio between the timer kernel clock (tim_ker_ck) and the DTS sampling clock
  *         (DTS_ck) used by the dead-time generators (when supported), the break/break2 filters and the digital
  *         filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(timx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @rmtoll
  *  CR1          CKD           LL_TIM_GetClockDivision
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV1
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV2
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV4
  */
__STATIC_INLINE uint32_t LL_TIM_GetClockDivision(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CR1, TIM_CR1_CKD));
}

/**
  * @brief  Set the counter value.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the Counter value interpretation
  * @rmtoll
  *  CNT          CNT           LL_TIM_SetCounter
  * @param  timx Timer instance
  * @param  counter Counter value (between Min_Data=0 and Max_Data=0xFFFF or 0xFFFFFFFF)
  */
__STATIC_INLINE void LL_TIM_SetCounter(TIM_TypeDef *timx, uint32_t counter)
{
  WRITE_REG(timx->CNT, counter);
}

/**
  * @brief  Get the counter value.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the Counter value interpretation
  * @rmtoll
  *  CNT          CNT           LL_TIM_GetCounter
  * @param  timx Timer instance
  * @retval Counter value (between Min_Data=0 and Max_Data=0xFFFF or 0xFFFFFFFF)
  */
__STATIC_INLINE uint32_t LL_TIM_GetCounter(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CNT));
}

/**
  * @brief  Get the current direction of the counter
  * @rmtoll
  *  CR1          DIR           LL_TIM_GetDirection
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_COUNTERDIRECTION_UP
  *         @arg @ref LL_TIM_COUNTERDIRECTION_DOWN
  */
__STATIC_INLINE uint32_t LL_TIM_GetDirection(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CR1, TIM_CR1_DIR));
}

/**
  * @brief  Set the prescaler value.
  * @note The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
  * @note The prescaler can be changed on the fly as this control register is buffered. The new
  *       prescaler ratio is taken into account at the next update event.
  * @note Helper macro @ref LL_TIM_CALC_PSC can be used to calculate the prescaler parameter
  * @rmtoll
  *  PSC          PSC           LL_TIM_SetPrescaler
  * @param  timx Timer instance
  * @param  prescaler between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_SetPrescaler(TIM_TypeDef *timx, uint32_t prescaler)
{
  WRITE_REG(timx->PSC, prescaler);
}

/**
  * @brief  Get the prescaler value.
  * @rmtoll
  *  PSC          PSC           LL_TIM_GetPrescaler
  * @param  timx Timer instance
  * @retval  Prescaler value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE uint32_t LL_TIM_GetPrescaler(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->PSC));
}

/**
  * @brief  Set the auto-reload value.
  * @note The counter is blocked while the auto-reload value is null.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Helper macro @ref LL_TIM_CALC_ARR can be used to calculate the auto_reload parameter
  *       In case dithering is activated,macro LL_TIM_CALC_ARR_DITHER can be used instead, to calculate the auto_reload
  *       parameter.
  * @rmtoll
  *  ARR          ARR           LL_TIM_SetAutoReload
  * @param  timx Timer instance
  * @param  auto_reload between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_SetAutoReload(TIM_TypeDef *timx, uint32_t auto_reload)
{
  WRITE_REG(timx->ARR, auto_reload);
}

/**
  * @brief  Get the auto-reload value.
  * @rmtoll
  *  ARR          ARR           LL_TIM_GetAutoReload
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the returned value interpretation
  * @param  timx Timer instance
  * @retval Auto-reload value
  */
__STATIC_INLINE uint32_t LL_TIM_GetAutoReload(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->ARR));
}

/**
  * @brief  Set the repetition counter value.
  * @note For advanced timer instances repetition_counter can be up to 65535.
  * @note Macro IS_TIM_REPETITION_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a repetition counter.
  * @rmtoll
  *  RCR          REP           LL_TIM_SetRepetitionCounter
  * @param  timx Timer instance
  * @param  repetition_counter between Min_Data=0 and Max_Data=255 or 65535 for advanced timer.
  */
__STATIC_INLINE void LL_TIM_SetRepetitionCounter(TIM_TypeDef *timx, uint32_t repetition_counter)
{
  WRITE_REG(timx->RCR, repetition_counter);
}

/**
  * @brief  Get the repetition counter value.
  * @note Macro IS_TIM_REPETITION_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a repetition counter.
  * @rmtoll
  *  RCR          REP           LL_TIM_GetRepetitionCounter
  * @param  timx Timer instance
  * @retval Repetition counter value
  */
__STATIC_INLINE uint32_t LL_TIM_GetRepetitionCounter(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->RCR));
}

/**
  * @brief  Force a continuous copy of the update interrupt flag (UIF) into the timer counter register (bit 31).
  * @note This allows both the counter value and a potential roll-over condition signalled by the UIFCPY flag to be read
  *       in an atomic way.
  * @rmtoll
  *  CR1          UIFREMAP      LL_TIM_EnableUIFRemap
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableUIFRemap(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR1, TIM_CR1_UIFREMAP);
}

/**
  * @brief  Disable update interrupt flag (UIF) remapping.
  * @rmtoll
  *  CR1          UIFREMAP      LL_TIM_DisableUIFRemap
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableUIFRemap(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR1, TIM_CR1_UIFREMAP);
}

/**
  * @brief  Indicates whether the update interrupt flag (UIF)
  *         remapping is enabled.
  * @rmtoll
  *  CR1          UIFREMAP      LL_TIM_IsEnabledUIFRemap
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledUIFRemap(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR1, TIM_CR1_UIFREMAP) == (TIM_CR1_UIFREMAP)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether update interrupt flag (UIF) copy is set.
  * @param  Counter Counter value
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveUIFCPY(const uint32_t Counter)
{
  return (((READ_BIT(Counter, TIM_CNT_UIFCPY)) == (TIM_CNT_UIFCPY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable dithering.
  * @rmtoll
  *  CR1          DITHEN          LL_TIM_EnableDithering
  * @param  timx Timer instance
  * @warning Dithering can only be enabled when the counter is disabled.
  */
__STATIC_INLINE void LL_TIM_EnableDithering(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR1, TIM_CR1_DITHEN);
}

/**
  * @brief  Disable dithering.
  * @rmtoll
  *  CR1          DITHEN          LL_TIM_DisableDithering
  * @param  timx Timer instance
  * @warning Dithering can only be disabled when the counter is disabled.
  */
__STATIC_INLINE void LL_TIM_DisableDithering(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR1, TIM_CR1_DITHEN);
}

/**
  * @brief  Indicates whether dithering is activated.
  * @rmtoll
  *  CR1          DITHEN          LL_TIM_IsEnabledDithering
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDithering(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR1, TIM_CR1_DITHEN) == (TIM_CR1_DITHEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Capture_Compare Capture Compare configuration
  * @{
  */
/**
  * @brief  Enable  the capture/compare control bits (CCxE, CCxNE and OCxM) preload.
  * @note CCxE, CCxNE and OCxM bits are preloaded, after having been written,
  *       they are updated only when a commutation event (COM) occurs.
  * @note Only on channels that have a complementary output.
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(timx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll
  *  CR2          CCPC          LL_TIM_CC_EnablePreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_CC_EnablePreload(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR2, TIM_CR2_CCPC);
}

/**
  * @brief  Disable  the capture/compare control bits (CCxE, CCxNE and OCxM) preload.
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(timx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll
  *  CR2          CCPC          LL_TIM_CC_DisablePreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_CC_DisablePreload(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR2, TIM_CR2_CCPC);
}

/**
  * @brief  Indicates whether the capture/compare control bits (CCxE, CCxNE and OCxM) preload is enabled.
  * @rmtoll
  *  CR2          CCPC          LL_TIM_CC_IsEnabledPreload
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_CC_IsEnabledPreload(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR2, TIM_CR2_CCPC) == (TIM_CR2_CCPC)) ? 1UL : 0UL);
}

/**
  * @brief  Set the updated source of the capture/compare control bits (CCxE, CCxNE and OCxM).
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(timx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll
  *  CR2          CCUS          LL_TIM_CC_SetUpdate
  * @param  timx Timer instance
  * @param  cc_update_source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CCUPDATESOURCE_SOFTWARE
  *         @arg @ref LL_TIM_CCUPDATESOURCE_SOFTWARE_AND_TRIGGER
  */
__STATIC_INLINE void LL_TIM_CC_SetUpdate(TIM_TypeDef *timx, uint32_t cc_update_source)
{
  MODIFY_REG(timx->CR2, TIM_CR2_CCUS, cc_update_source);
}

/**
  * @brief  Get the updated source of the capture/compare control bits (CCxE, CCxNE and OCxM).
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(timx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll
  *  CR2          CCUS          LL_TIM_CC_GetUpdate
  * @param  timx Timer instance
  * @retval The returned value can be one of the following values:
  *         @arg @ref LL_TIM_CCUPDATESOURCE_SOFTWARE
  *         @arg @ref LL_TIM_CCUPDATESOURCE_SOFTWARE_AND_TRIGGER
  */
__STATIC_INLINE uint32_t LL_TIM_CC_GetUpdate(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CR2, TIM_CR2_CCUS));
}

/**
  * @brief  Set the trigger of the capture/compare DMA request.
  * @rmtoll
  *  CR2          CCDS          LL_TIM_CC_SetDMAReqTrigger
  * @param  timx Timer instance
  * @param  dma_req_trigger This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CCDMAREQUEST_CC
  *         @arg @ref LL_TIM_CCDMAREQUEST_UPD
  */
__STATIC_INLINE void LL_TIM_CC_SetDMAReqTrigger(TIM_TypeDef *timx, uint32_t dma_req_trigger)
{
  MODIFY_REG(timx->CR2, TIM_CR2_CCDS, dma_req_trigger);
}

/**
  * @brief  Get actual trigger of the capture/compare DMA request.
  * @rmtoll
  *  CR2          CCDS          LL_TIM_CC_GetDMAReqTrigger
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_CCDMAREQUEST_CC
  *         @arg @ref LL_TIM_CCDMAREQUEST_UPD
  */
__STATIC_INLINE uint32_t LL_TIM_CC_GetDMAReqTrigger(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CR2, TIM_CR2_CCDS));
}

/**
  * @brief  Set the lock level to freeze the
  *         configuration of several capture/compare parameters.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       the lock mechanism is supported by a timer instance.
  * @rmtoll
  *  BDTR         LOCK          LL_TIM_CC_SetLockLevel
  * @param  timx Timer instance
  * @param  lock_level This parameter can be one of the following values:
  *         @arg @ref LL_TIM_LOCKLEVEL_OFF
  *         @arg @ref LL_TIM_LOCKLEVEL_1
  *         @arg @ref LL_TIM_LOCKLEVEL_2
  *         @arg @ref LL_TIM_LOCKLEVEL_3
  */
__STATIC_INLINE void LL_TIM_CC_SetLockLevel(TIM_TypeDef *timx, uint32_t lock_level)
{
  MODIFY_REG(timx->BDTR, TIM_BDTR_LOCK, lock_level);
}

/**
  * @brief  Get the lock level that freezes the
  *         configuration of several capture/compare parameters.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       the lock mechanism is supported by a timer instance.
  * @rmtoll
  *  BDTR         LOCK          LL_TIM_CC_GetLockLevel
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_LOCKLEVEL_OFF
  *         @arg @ref LL_TIM_LOCKLEVEL_1
  *         @arg @ref LL_TIM_LOCKLEVEL_2
  *         @arg @ref LL_TIM_LOCKLEVEL_3
  */
__STATIC_INLINE uint32_t LL_TIM_CC_GetLockLevel(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->BDTR, TIM_BDTR_LOCK));
}

/**
  * @brief  Enable capture/compare channels.
  * @rmtoll
  *  CCER         CC1E          LL_TIM_CC_EnableChannel \n
  *  CCER         CC1NE         LL_TIM_CC_EnableChannel \n
  *  CCER         CC2E          LL_TIM_CC_EnableChannel \n
  *  CCER         CC2NE         LL_TIM_CC_EnableChannel \n
  *  CCER         CC3E          LL_TIM_CC_EnableChannel \n
  *  CCER         CC3NE         LL_TIM_CC_EnableChannel \n
  *  CCER         CC4E          LL_TIM_CC_EnableChannel \n
  *  CCER         CC4NE         LL_TIM_CC_EnableChannel \n
  *  CCER         CC5E          LL_TIM_CC_EnableChannel \n
  *  CCER         CC6E          LL_TIM_CC_EnableChannel
  * @param  timx Timer instance
  * @param  channels This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_CC_EnableChannel(TIM_TypeDef *timx, uint32_t channels)
{
  SET_BIT(timx->CCER, channels);
}

/**
  * @brief  Disable capture/compare channels.
  * @rmtoll
  *  CCER         CC1E          LL_TIM_CC_DisableChannel \n
  *  CCER         CC1NE         LL_TIM_CC_DisableChannel \n
  *  CCER         CC2E          LL_TIM_CC_DisableChannel \n
  *  CCER         CC2NE         LL_TIM_CC_DisableChannel \n
  *  CCER         CC3E          LL_TIM_CC_DisableChannel \n
  *  CCER         CC3NE         LL_TIM_CC_DisableChannel \n
  *  CCER         CC4E          LL_TIM_CC_DisableChannel \n
  *  CCER         CC4NE         LL_TIM_CC_DisableChannel \n
  *  CCER         CC5E          LL_TIM_CC_DisableChannel \n
  *  CCER         CC6E          LL_TIM_CC_DisableChannel
  * @param  timx Timer instance
  * @param  channels This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_CC_DisableChannel(TIM_TypeDef *timx, uint32_t channels)
{
  CLEAR_BIT(timx->CCER, channels);
}

/**
  * @brief  Indicate whether channel(s) is(are) enabled.
  * @rmtoll
  *  CCER         CC1E          LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC1NE         LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC2E          LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC2NE         LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC3E          LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC3NE         LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC4E          LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC4NE         LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC5E          LL_TIM_CC_IsEnabledChannel \n
  *  CCER         CC6E          LL_TIM_CC_IsEnabledChannel
  * @param  timx Timer instance
  * @param  channels This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_CC_IsEnabledChannel(const TIM_TypeDef *timx, uint32_t channels)
{
  return ((READ_BIT(timx->CCER, channels) == (channels)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Output_Channel Output channel configuration
  * @{
  */
/**
  * @brief  Configure an output channel.
  * @rmtoll
  *  CCMR1        CC1S          LL_TIM_OC_ConfigOutput \n
  *  CCMR1        CC2S          LL_TIM_OC_ConfigOutput \n
  *  CCMR2        CC3S          LL_TIM_OC_ConfigOutput \n
  *  CCMR2        CC4S          LL_TIM_OC_ConfigOutput \n
  *  CCER         CC1P          LL_TIM_OC_ConfigOutput \n
  *  CCER         CC2P          LL_TIM_OC_ConfigOutput \n
  *  CCER         CC3P          LL_TIM_OC_ConfigOutput \n
  *  CCER         CC4P          LL_TIM_OC_ConfigOutput \n
  *  CCER         CC5P          LL_TIM_OC_ConfigOutput \n
  *  CCER         CC6P          LL_TIM_OC_ConfigOutput \n
  *  CR2          OIS1          LL_TIM_OC_ConfigOutput \n
  *  CR2          OIS2          LL_TIM_OC_ConfigOutput \n
  *  CR2          OIS3          LL_TIM_OC_ConfigOutput \n
  *  CR2          OIS4          LL_TIM_OC_ConfigOutput \n
  *  CR2          OIS5          LL_TIM_OC_ConfigOutput \n
  *  CR2          OIS6          LL_TIM_OC_ConfigOutpu
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_TIM_OCPOLARITY_HIGH or @ref LL_TIM_OCPOLARITY_LOW
  *         @arg @ref LL_TIM_OCIDLESTATE_RESET or @ref LL_TIM_OCIDLESTATE_SET
  */
__STATIC_INLINE void LL_TIM_OC_ConfigOutput(TIM_TypeDef *timx, uint32_t channel, uint32_t configuration)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_CC1S << LL_TIM_SHIFT_TAB_OCxx[ichannel]));
  MODIFY_REG(timx->CCER, (TIM_CCER_CC1P << LL_TIM_SHIFT_TAB_CCxP[ichannel]),
             (configuration & TIM_CCER_CC1P) << LL_TIM_SHIFT_TAB_CCxP[ichannel]);
  MODIFY_REG(timx->CR2, (TIM_CR2_OIS1 << LL_TIM_SHIFT_TAB_OISx[ichannel]),
             (configuration & TIM_CR2_OIS1) << LL_TIM_SHIFT_TAB_OISx[ichannel]);
}

/**
  * @brief  Define the behavior of the output reference signal OCxREF from which
  *         OCx and OCxN (when relevant) are derived.
  * @rmtoll
  *  CCMR1        OC1M          LL_TIM_OC_SetMode \n
  *  CCMR1        OC2M          LL_TIM_OC_SetMode \n
  *  CCMR2        OC3M          LL_TIM_OC_SetMode \n
  *  CCMR2        OC4M          LL_TIM_OC_SetMode \n
  *  CCMR3        OC5M          LL_TIM_OC_SetMode \n
  *  CCMR3        OC6M          LL_TIM_OC_SetMode
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCMODE_FROZEN
  *         @arg @ref LL_TIM_OCMODE_ACTIVE_ON_MATCH
  *         @arg @ref LL_TIM_OCMODE_INACTIVE_ON_MATCH
  *         @arg @ref LL_TIM_OCMODE_TOGGLE
  *         @arg @ref LL_TIM_OCMODE_FORCED_INACTIVE
  *         @arg @ref LL_TIM_OCMODE_FORCED_ACTIVE
  *         @arg @ref LL_TIM_OCMODE_PWM1
  *         @arg @ref LL_TIM_OCMODE_PWM2
  *         @arg @ref LL_TIM_OCMODE_RETRIGERRABLE_OPM1
  *         @arg @ref LL_TIM_OCMODE_RETRIGERRABLE_OPM2
  *         @arg @ref LL_TIM_OCMODE_COMBINED_PWM1
  *         @arg @ref LL_TIM_OCMODE_COMBINED_PWM2
  *         @arg @ref LL_TIM_OCMODE_ASYMMETRIC_PWM1
  *         @arg @ref LL_TIM_OCMODE_ASYMMETRIC_PWM2
  *         @arg @ref LL_TIM_OCMODE_PULSE_ON_COMPARE   (for channel 3 or channel 4 only)
  *         @arg @ref LL_TIM_OCMODE_DIRECTION_OUTPUT   (for channel 3 or channel 4 only)
  */
__STATIC_INLINE void LL_TIM_OC_SetMode(TIM_TypeDef *timx, uint32_t channel, uint32_t mode)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_OC1M  | TIM_CCMR1_CC1S) << LL_TIM_SHIFT_TAB_OCxx[ichannel]),
             mode << LL_TIM_SHIFT_TAB_OCxx[ichannel]);
}

/**
  * @brief  Get the output compare mode of an output channel.
  * @rmtoll
  *  CCMR1        OC1M          LL_TIM_OC_GetMode \n
  *  CCMR1        OC2M          LL_TIM_OC_GetMode \n
  *  CCMR2        OC3M          LL_TIM_OC_GetMode \n
  *  CCMR2        OC4M          LL_TIM_OC_GetMode \n
  *  CCMR3        OC5M          LL_TIM_OC_GetMode \n
  *  CCMR3        OC6M          LL_TIM_OC_GetMode
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCMODE_FROZEN
  *         @arg @ref LL_TIM_OCMODE_ACTIVE_ON_MATCH
  *         @arg @ref LL_TIM_OCMODE_INACTIVE_ON_MATCH
  *         @arg @ref LL_TIM_OCMODE_TOGGLE
  *         @arg @ref LL_TIM_OCMODE_FORCED_INACTIVE
  *         @arg @ref LL_TIM_OCMODE_FORCED_ACTIVE
  *         @arg @ref LL_TIM_OCMODE_PWM1
  *         @arg @ref LL_TIM_OCMODE_PWM2
  *         @arg @ref LL_TIM_OCMODE_RETRIGERRABLE_OPM1
  *         @arg @ref LL_TIM_OCMODE_RETRIGERRABLE_OPM2
  *         @arg @ref LL_TIM_OCMODE_COMBINED_PWM1
  *         @arg @ref LL_TIM_OCMODE_COMBINED_PWM2
  *         @arg @ref LL_TIM_OCMODE_ASYMMETRIC_PWM1
  *         @arg @ref LL_TIM_OCMODE_ASYMMETRIC_PWM2
  *         @arg @ref LL_TIM_OCMODE_PULSE_ON_COMPARE   (for channel 3 or channel 4 only)
  *         @arg @ref LL_TIM_OCMODE_DIRECTION_OUTPUT   (for channel 3 or channel 4 only)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetMode(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  return (READ_BIT(*pReg, ((TIM_CCMR1_OC1M | TIM_CCMR1_CC1S) << LL_TIM_SHIFT_TAB_OCxx[ichannel])) \
          >> LL_TIM_SHIFT_TAB_OCxx[ichannel]);
}

/**
  * @brief  Set the polarity of an output channel.
  * @rmtoll
  *  CCER         CC1P          LL_TIM_OC_SetPolarity \n
  *  CCER         CC1NP         LL_TIM_OC_SetPolarity \n
  *  CCER         CC2P          LL_TIM_OC_SetPolarity \n
  *  CCER         CC2NP         LL_TIM_OC_SetPolarity \n
  *  CCER         CC3P          LL_TIM_OC_SetPolarity \n
  *  CCER         CC3NP         LL_TIM_OC_SetPolarity \n
  *  CCER         CC4P          LL_TIM_OC_SetPolarity \n
  *  CCER         CC4NP         LL_TIM_OC_SetPolarity \n
  *  CCER         CC5P          LL_TIM_OC_SetPolarity \n
  *  CCER         CC6P          LL_TIM_OC_SetPolarity
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCPOLARITY_HIGH
  *         @arg @ref LL_TIM_OCPOLARITY_LOW
  */
__STATIC_INLINE void LL_TIM_OC_SetPolarity(TIM_TypeDef *timx, uint32_t channel, uint32_t polarity)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  MODIFY_REG(timx->CCER, (TIM_CCER_CC1P << LL_TIM_SHIFT_TAB_CCxP[ichannel]),
             polarity << LL_TIM_SHIFT_TAB_CCxP[ichannel]);
}

/**
  * @brief  Get the polarity of an output channel.
  * @rmtoll
  *  CCER         CC1P          LL_TIM_OC_GetPolarity \n
  *  CCER         CC1NP         LL_TIM_OC_GetPolarity \n
  *  CCER         CC2P          LL_TIM_OC_GetPolarity \n
  *  CCER         CC2NP         LL_TIM_OC_GetPolarity \n
  *  CCER         CC3P          LL_TIM_OC_GetPolarity \n
  *  CCER         CC3NP         LL_TIM_OC_GetPolarity \n
  *  CCER         CC4P          LL_TIM_OC_GetPolarity \n
  *  CCER         CC4NP         LL_TIM_OC_GetPolarity \n
  *  CCER         CC5P          LL_TIM_OC_GetPolarity \n
  *  CCER         CC6P          LL_TIM_OC_GetPolarity
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCPOLARITY_HIGH
  *         @arg @ref LL_TIM_OCPOLARITY_LOW
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetPolarity(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  return (READ_BIT(timx->CCER, (TIM_CCER_CC1P << LL_TIM_SHIFT_TAB_CCxP[ichannel])) >> LL_TIM_SHIFT_TAB_CCxP[ichannel]);
}

/**
  * @brief  Set the idle state of an output channel.
  * @note This function is significant only for the timer instances
  *       supporting the break feature. Macro IS_TIM_BREAK_INSTANCE(timx)
  *       can be used to check whether or not a timer instance provides
  *       a break input.
  * @rmtoll
  *  CR2         OIS1          LL_TIM_OC_SetIdleState \n
  *  CR2         OIS2N         LL_TIM_OC_SetIdleState \n
  *  CR2         OIS2          LL_TIM_OC_SetIdleState \n
  *  CR2         OIS2N         LL_TIM_OC_SetIdleState \n
  *  CR2         OIS3          LL_TIM_OC_SetIdleState \n
  *  CR2         OIS3N         LL_TIM_OC_SetIdleState \n
  *  CR2         OIS4          LL_TIM_OC_SetIdleState \n
  *  CR2         OIS4N         LL_TIM_OC_SetIdleState \n
  *  CR2         OIS5          LL_TIM_OC_SetIdleState \n
  *  CR2         OIS6          LL_TIM_OC_SetIdleState
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @param  idle_state This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCIDLESTATE_RESET
  *         @arg @ref LL_TIM_OCIDLESTATE_SET
  */
__STATIC_INLINE void LL_TIM_OC_SetIdleState(TIM_TypeDef *timx, uint32_t channel, uint32_t idle_state)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  MODIFY_REG(timx->CR2, (TIM_CR2_OIS1 << LL_TIM_SHIFT_TAB_OISx[ichannel]),
             idle_state << LL_TIM_SHIFT_TAB_OISx[ichannel]);
}

/**
  * @brief  Get the idle state of an output channel.
  * @rmtoll
  *  CR2         OIS1          LL_TIM_OC_GetIdleState \n
  *  CR2         OIS2N         LL_TIM_OC_GetIdleState \n
  *  CR2         OIS2          LL_TIM_OC_GetIdleState \n
  *  CR2         OIS2N         LL_TIM_OC_GetIdleState \n
  *  CR2         OIS3          LL_TIM_OC_GetIdleState \n
  *  CR2         OIS3N         LL_TIM_OC_GetIdleState \n
  *  CR2         OIS4          LL_TIM_OC_GetIdleState \n
  *  CR2         OIS4N         LL_TIM_OC_GetIdleState \n
  *  CR2         OIS5          LL_TIM_OC_GetIdleState \n
  *  CR2         OIS6          LL_TIM_OC_GetIdleState
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH4N
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCIDLESTATE_RESET
  *         @arg @ref LL_TIM_OCIDLESTATE_SET
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetIdleState(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  return (READ_BIT(timx->CR2, (TIM_CR2_OIS1 << LL_TIM_SHIFT_TAB_OISx[ichannel])) >> LL_TIM_SHIFT_TAB_OISx[ichannel]);
}

/**
  * @brief  Enable fast mode for the output channel.
  * @note Acts only if the channel is configured in PWM1 or PWM2 mode.
  * @rmtoll
  *  CCMR1        OC1FE          LL_TIM_OC_EnableFast \n
  *  CCMR1        OC2FE          LL_TIM_OC_EnableFast \n
  *  CCMR2        OC3FE          LL_TIM_OC_EnableFast \n
  *  CCMR2        OC4FE          LL_TIM_OC_EnableFast \n
  *  CCMR3        OC5FE          LL_TIM_OC_EnableFast \n
  *  CCMR3        OC6FE          LL_TIM_OC_EnableFast
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_OC_EnableFast(TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1FE << LL_TIM_SHIFT_TAB_OCxx[ichannel]));

}

/**
  * @brief  Disable fast mode for the output channel.
  * @rmtoll
  *  CCMR1        OC1FE          LL_TIM_OC_DisableFast \n
  *  CCMR1        OC2FE          LL_TIM_OC_DisableFast \n
  *  CCMR2        OC3FE          LL_TIM_OC_DisableFast \n
  *  CCMR2        OC4FE          LL_TIM_OC_DisableFast \n
  *  CCMR3        OC5FE          LL_TIM_OC_DisableFast \n
  *  CCMR3        OC6FE          LL_TIM_OC_DisableFast
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_OC_DisableFast(TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1FE << LL_TIM_SHIFT_TAB_OCxx[ichannel]));

}

/**
  * @brief  Indicates whether fast mode is enabled for the output channel.
  * @rmtoll
  *  CCMR1        OC1FE          LL_TIM_OC_IsEnabledFast \n
  *  CCMR1        OC2FE          LL_TIM_OC_IsEnabledFast \n
  *  CCMR2        OC3FE          LL_TIM_OC_IsEnabledFast \n
  *  CCMR2        OC4FE          LL_TIM_OC_IsEnabledFast \n
  *  CCMR3        OC5FE          LL_TIM_OC_IsEnabledFast \n
  *  CCMR3        OC6FE          LL_TIM_OC_IsEnabledFast
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_OC_IsEnabledFast(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  uint32_t bitfield = TIM_CCMR1_OC1FE << LL_TIM_SHIFT_TAB_OCxx[ichannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Enable compare register (TIMx_CCRx) preload for the output channel.
  * @rmtoll
  *  CCMR1        OC1PE          LL_TIM_OC_EnablePreload \n
  *  CCMR1        OC2PE          LL_TIM_OC_EnablePreload \n
  *  CCMR2        OC3PE          LL_TIM_OC_EnablePreload \n
  *  CCMR2        OC4PE          LL_TIM_OC_EnablePreload \n
  *  CCMR3        OC5PE          LL_TIM_OC_EnablePreload \n
  *  CCMR3        OC6PE          LL_TIM_OC_EnablePreload
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_OC_EnablePreload(TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1PE << LL_TIM_SHIFT_TAB_OCxx[ichannel]));
}

/**
  * @brief  Disable compare register (TIMx_CCRx) preload for the output channel.
  * @rmtoll
  *  CCMR1        OC1PE          LL_TIM_OC_DisablePreload \n
  *  CCMR1        OC2PE          LL_TIM_OC_DisablePreload \n
  *  CCMR2        OC3PE          LL_TIM_OC_DisablePreload \n
  *  CCMR2        OC4PE          LL_TIM_OC_DisablePreload \n
  *  CCMR3        OC5PE          LL_TIM_OC_DisablePreload \n
  *  CCMR3        OC6PE          LL_TIM_OC_DisablePreload
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_OC_DisablePreload(TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1PE << LL_TIM_SHIFT_TAB_OCxx[ichannel]));
}

/**
  * @brief  Indicates whether compare register (TIMx_CCRx) preload is enabled for the output channel.
  * @rmtoll
  *  CCMR1        OC1PE          LL_TIM_OC_IsEnabledPreload \n
  *  CCMR1        OC2PE          LL_TIM_OC_IsEnabledPreload \n
  *  CCMR2        OC3PE          LL_TIM_OC_IsEnabledPreload \n
  *  CCMR2        OC4PE          LL_TIM_OC_IsEnabledPreload \n
  *  CCMR3        OC5PE          LL_TIM_OC_IsEnabledPreload \n
  *  CCMR3        OC6PE          LL_TIM_OC_IsEnabledPreload
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_OC_IsEnabledPreload(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  uint32_t bitfield = TIM_CCMR1_OC1PE << LL_TIM_SHIFT_TAB_OCxx[ichannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Enable clearing the output channel on an external event.
  * @note This function can only be used in Output compare and PWM modes. It does not work in Forced mode.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(timx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll
  *  CCMR1        OC1CE          LL_TIM_OC_EnableClear \n
  *  CCMR1        OC2CE          LL_TIM_OC_EnableClear \n
  *  CCMR2        OC3CE          LL_TIM_OC_EnableClear \n
  *  CCMR2        OC4CE          LL_TIM_OC_EnableClear \n
  *  CCMR3        OC5CE          LL_TIM_OC_EnableClear \n
  *  CCMR3        OC6CE          LL_TIM_OC_EnableClear
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_OC_EnableClear(TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1CE << LL_TIM_SHIFT_TAB_OCxx[ichannel]));
}

/**
  * @brief  Disable clearing the output channel on an external event.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(timx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll
  *  CCMR1        OC1CE          LL_TIM_OC_DisableClear \n
  *  CCMR1        OC2CE          LL_TIM_OC_DisableClear \n
  *  CCMR2        OC3CE          LL_TIM_OC_DisableClear \n
  *  CCMR2        OC4CE          LL_TIM_OC_DisableClear \n
  *  CCMR3        OC5CE          LL_TIM_OC_DisableClear \n
  *  CCMR3        OC6CE          LL_TIM_OC_DisableClear
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  */
__STATIC_INLINE void LL_TIM_OC_DisableClear(TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1CE << LL_TIM_SHIFT_TAB_OCxx[ichannel]));
}

/**
  * @brief  Indicates clearing the output channel on an external event is enabled for the output channel.
  * @note This function enables clearing the output channel on an external event.
  * @note This function can only be used in Output compare and PWM modes. It does not work in Forced mode.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(timx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll
  *  CCMR1        OC1CE          LL_TIM_OC_IsEnabledClear \n
  *  CCMR1        OC2CE          LL_TIM_OC_IsEnabledClear \n
  *  CCMR2        OC3CE          LL_TIM_OC_IsEnabledClear \n
  *  CCMR2        OC4CE          LL_TIM_OC_IsEnabledClear \n
  *  CCMR3        OC5CE          LL_TIM_OC_IsEnabledClear \n
  *  CCMR3        OC6CE          LL_TIM_OC_IsEnabledClear
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  *         @arg @ref LL_TIM_CHANNEL_CH5
  *         @arg @ref LL_TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_OC_IsEnabledClear(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  uint32_t bitfield = TIM_CCMR1_OC1CE << LL_TIM_SHIFT_TAB_OCxx[ichannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Set the dead-time delay (delay inserted between the rising edge of the OCxREF signal and the rising edge of
  *         the Ocx and OCxN signals).
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       dead-time insertion feature is supported by a timer instance.
  * @note Helper macro @ref LL_TIM_CALC_DEADTIME can be used to calculate the deadtime parameter
  * @rmtoll
  *  BDTR         DTG           LL_TIM_OC_SetDeadTime
  * @param  timx Timer instance
  * @param  deadtime between Min_Data=0 and Max_Data=255
  */
__STATIC_INLINE void LL_TIM_OC_SetDeadTime(TIM_TypeDef *timx, uint32_t deadtime)
{
  MODIFY_REG(timx->BDTR, TIM_BDTR_DTG, deadtime);
}

/**
  * @brief  Get the dead-time delay (delay inserted between the rising edge of the
  *         OCxREF signal and the rising edge of the Ocx and OCxN signals).
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       dead-time insertion feature is supported by a timer instance.
  * @note Helper macro @ref LL_TIM_CALC_DEADTIME can be used to calculate the deadtime parameter
  * @rmtoll
  *  BDTR         DTG           LL_TIM_OC_GetDeadTime
  * @param  timx Timer instance
  * @retval deadtime between Min_Data=0 and Max_Data=255
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetDeadTime(const TIM_TypeDef *timx)
{
  return (READ_REG(timx->BDTR) & TIM_BDTR_DTG);
}

/**
  * @brief  Set compare value for output channel 1 (TIMx_CCR1).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(timx) can be used to check whether or not
  *       output channel 1 is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR1         CCR1          LL_TIM_OC_SetCompareCH1
  * @param  timx Timer instance
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareCH1(TIM_TypeDef *timx, uint32_t compare_value)
{
  WRITE_REG(timx->CCR1, compare_value);
}

/**
  * @brief  Set compare value for output channel 2 (TIMx_CCR2).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(timx) can be used to check whether or not
  *       output channel 2 is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR2         CCR2          LL_TIM_OC_SetCompareCH2
  * @param  timx Timer instance
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareCH2(TIM_TypeDef *timx, uint32_t compare_value)
{
  WRITE_REG(timx->CCR2, compare_value);
}

/**
  * @brief  Set compare value for output channel 3 (TIMx_CCR3).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(timx) can be used to check whether or not
  *       output channel is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR3         CCR3          LL_TIM_OC_SetCompareCH3
  * @param  timx Timer instance
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareCH3(TIM_TypeDef *timx, uint32_t compare_value)
{
  WRITE_REG(timx->CCR3, compare_value);
}

/**
  * @brief  Set compare value for output channel 4 (TIMx_CCR4).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(timx) can be used to check whether or not
  *       output channel 4 is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR4         CCR4          LL_TIM_OC_SetCompareCH4
  * @param  timx Timer instance
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareCH4(TIM_TypeDef *timx, uint32_t compare_value)
{
  WRITE_REG(timx->CCR4, compare_value);
}

/**
  * @brief  Set compare value for output channel 5 (TIMx_CCR5).
  * @note Macro IS_TIM_CC5_INSTANCE(timx) can be used to check whether or not
  *       output channel 5 is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR5         CCR5          LL_TIM_OC_SetCompareCH5
  * @param  timx Timer instance
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareCH5(TIM_TypeDef *timx, uint32_t compare_value)
{
  MODIFY_REG(timx->CCR5, TIM_CCR5_CCR5, compare_value);
}

/**
  * @brief  Set compare value for output channel 6 (TIMx_CCR6).
  * @note Macro IS_TIM_CC6_INSTANCE(timx) can be used to check whether or not
  *       output channel 6 is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR6         CCR6          LL_TIM_OC_SetCompareCH6
  * @param  timx Timer instance
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareCH6(TIM_TypeDef *timx, uint32_t compare_value)
{
  WRITE_REG(timx->CCR6, compare_value);
}

/**
  * @brief  Set compare value for the selected compare unit.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CCx_INSTANCE(timx) can be used to check whether or not
  *       capture unit x is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR1         CCR1          LL_TIM_OC_SetCompareValue \n
  *  CCR2         CCR2          LL_TIM_OC_SetCompareValue \n
  *  CCR3         CCR3          LL_TIM_OC_SetCompareValue \n
  *  CCR4         CCR4          LL_TIM_OC_SetCompareValue \n
  *  CCR5         CCR5          LL_TIM_OC_SetCompareValue \n
  *  CCR6         CCR6          LL_TIM_OC_SetCompareValue
  * @param  timx Timer instance
  * @param  compare_unit This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_1
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_2
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_3
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_4
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_5
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_6
  * @param  compare_value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE void LL_TIM_OC_SetCompareValue(TIM_TypeDef *timx, uint32_t compare_unit, uint32_t compare_value)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCR1) + LL_TIM_OFFSET_TAB_CCRx[compare_unit]));
  uint32_t compare_mask = (compare_unit < LL_TIM_OC_COMPARE_UNIT_5) ? TIM_CCR1_CCR1 : TIM_CCR5_CCR5;
  MODIFY_REG(*pReg, compare_mask, compare_value);
}

/**
  * @brief  Get compare value (TIMx_CCR1) set for output channel 1.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(timx) can be used to check whether or not
  *       output channel 1 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR1         CCR1          LL_TIM_OC_GetCompareCH1
  * @param  timx Timer instance
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH1(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR1));
}

/**
  * @brief  Get compare value (TIMx_CCR2) set for output channel 2.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(timx) can be used to check whether or not
  *       output channel 2 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR2         CCR2          LL_TIM_OC_GetCompareCH2
  * @param  timx Timer instance
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH2(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR2));
}

/**
  * @brief  Get compare value (TIMx_CCR3) set for output channel 3.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(timx) can be used to check whether or not
  *       output channel 3 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR3         CCR3          LL_TIM_OC_GetCompareCH3
  * @param  timx Timer instance
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH3(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR3));
}

/**
  * @brief  Get compare value (TIMx_CCR4) set for output channel 4.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(timx) can be used to check whether or not
  *       output channel 4 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR4         CCR4          LL_TIM_OC_GetCompareCH4
  * @param  timx Timer instance
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH4(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR4));
}

/**
  * @brief  Get compare value (TIMx_CCR5) set for output channel 5.
  * @note Macro IS_TIM_CC5_INSTANCE(timx) can be used to check whether or not
  *       output channel 5 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR5         CCR5          LL_TIM_OC_GetCompareCH5
  * @param  timx Timer instance
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH5(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CCR5, TIM_CCR5_CCR5));
}

/**
  * @brief  Get compare value (TIMx_CCR6) set for output channel 6.
  * @note Macro IS_TIM_CC6_INSTANCE(timx) can be used to check whether or not
  *       output channel 6 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR6         CCR6          LL_TIM_OC_GetCompareCH6
  * @param  timx Timer instance
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH6(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR6));
}

/**
  * @brief  Get compare value for the selected compare unit.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CCx_INSTANCE(timx) can be used to check whether or not
  *       capture unit x is supported by a timer instance.
  * @note If dithering is activated, compare_value can be calculated with macro @ref LL_TIM_CALC_DELAY_DITHER .
  * @rmtoll
  *  CCR1         CCR1          LL_TIM_OC_GetCompareValue \n
  *  CCR2         CCR2          LL_TIM_OC_GetCompareValue \n
  *  CCR3         CCR3          LL_TIM_OC_GetCompareValue \n
  *  CCR4         CCR4          LL_TIM_OC_GetCompareValue \n
  *  CCR5         CCR5          LL_TIM_OC_GetCompareValue \n
  *  CCR6         CCR6          LL_TIM_OC_GetCompareValue
  * @param  timx Timer instance
  * @param  compare_unit This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_1
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_2
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_3
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_4
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_5
  *         @arg @ref LL_TIM_OC_COMPARE_UNIT_6
  * @retval compare_value (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareValue(TIM_TypeDef *timx, uint32_t compare_unit)
{
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCR1) + \
                                                           LL_TIM_OFFSET_TAB_CCRx[compare_unit]));
  uint32_t compare_mask = (compare_unit < LL_TIM_OC_COMPARE_UNIT_5) ? TIM_CCR1_CCR1 : TIM_CCR5_CCR5;
  return (uint32_t)(READ_BIT(*pReg, compare_mask));
}

/**
  * @brief  Select on which reference signal the OC5REF is combined to.
  * @note Macro IS_TIM_COMBINED3PHASEPWM_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the combined 3-phase PWM mode.
  * @rmtoll
  *  CCR5         GC5C1          LL_TIM_SetCH5CombinedChannels \n
  *  CCR5         GC5C2          LL_TIM_SetCH5CombinedChannels \n
  *  CCR5         GC5C3          LL_TIM_SetCH5CombinedChannels
  * @param  timx Timer instance
  * @param  group_ch5 This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_GROUPCH5_NONE
  *         @arg @ref LL_TIM_GROUPCH5_AND_OC1REFC
  *         @arg @ref LL_TIM_GROUPCH5_AND_OC2REFC
  *         @arg @ref LL_TIM_GROUPCH5_AND_OC3REFC
  */
__STATIC_INLINE void LL_TIM_SetCH5CombinedChannels(TIM_TypeDef *timx, uint32_t group_ch5)
{
  MODIFY_REG(timx->CCR5, (TIM_CCR5_GC5C3 | TIM_CCR5_GC5C2 | TIM_CCR5_GC5C1), group_ch5);
}

/**
  * @brief  Get on which reference signal the OC5REF is combined to.
  * @note Macro IS_TIM_COMBINED3PHASEPWM_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the combined 3-phase PWM mode.
  * @param  timx Timer instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_TIM_GROUPCH5_NONE
  *         @arg @ref LL_TIM_GROUPCH5_AND_OC1REFC
  *         @arg @ref LL_TIM_GROUPCH5_AND_OC2REFC
  *         @arg @ref LL_TIM_GROUPCH5_AND_OC3REFC
  */
__STATIC_INLINE uint32_t LL_TIM_GetCH5CombinedChannels(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->CCR5, (TIM_CCR5_GC5C3 | TIM_CCR5_GC5C2 | TIM_CCR5_GC5C1)));
}

/**
  * @brief  Set the pulse on compare pulse width prescaler.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(timx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll
  *  ECR          PWPRSC           LL_TIM_OC_SetPulseWidthPrescaler
  * @param  timx Timer instance
  * @param  pulse_width_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_TIM_PWPRSC_DIV1
  *         @arg @ref LL_TIM_PWPRSC_DIV2
  *         @arg @ref LL_TIM_PWPRSC_DIV4
  *         @arg @ref LL_TIM_PWPRSC_DIV8
  *         @arg @ref LL_TIM_PWPRSC_DIV16
  *         @arg @ref LL_TIM_PWPRSC_DIV32
  *         @arg @ref LL_TIM_PWPRSC_DIV64
  *         @arg @ref LL_TIM_PWPRSC_DIV128
  */
__STATIC_INLINE void LL_TIM_OC_SetPulseWidthPrescaler(TIM_TypeDef *timx, uint32_t pulse_width_prescaler)
{
  MODIFY_REG(timx->ECR, TIM_ECR_PWPRSC, pulse_width_prescaler);
}

/**
  * @brief  Get the pulse on compare pulse width prescaler.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(timx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll
  *  ECR          PWPRSC           LL_TIM_OC_GetPulseWidthPrescaler
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_PWPRSC_DIV1
  *         @arg @ref LL_TIM_PWPRSC_DIV2
  *         @arg @ref LL_TIM_PWPRSC_DIV4
  *         @arg @ref LL_TIM_PWPRSC_DIV8
  *         @arg @ref LL_TIM_PWPRSC_DIV16
  *         @arg @ref LL_TIM_PWPRSC_DIV32
  *         @arg @ref LL_TIM_PWPRSC_DIV64
  *         @arg @ref LL_TIM_PWPRSC_DIV128
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetPulseWidthPrescaler(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->ECR, TIM_ECR_PWPRSC));
}

/**
  * @brief  Set the pulse on compare pulse width duration.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(timx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll
  *  ECR          PW           LL_TIM_OC_SetPulseWidth
  * @param  timx Timer instance
  * @param  pulse_width This parameter can be between Min_Data=0 and Max_Data=255
  */
__STATIC_INLINE void LL_TIM_OC_SetPulseWidth(TIM_TypeDef *timx, uint32_t pulse_width)
{
  MODIFY_REG(timx->ECR, TIM_ECR_PW, pulse_width << TIM_ECR_PW_Pos);
}

/**
  * @brief  Get the pulse on compare pulse width duration.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(timx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll
  *  ECR          PW           LL_TIM_OC_GetPulseWidth
  * @param  timx Timer instance
  * @retval Returned value can be between Min_Data=0 and Max_Data=255:
  */
__STATIC_INLINE uint32_t LL_TIM_OC_GetPulseWidth(const TIM_TypeDef *timx)
{
  return (uint32_t)((READ_BIT(timx->ECR, TIM_ECR_PW)) >> TIM_ECR_PW_Pos);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Input_Channel Input channel configuration
  * @{
  */
/**
  * @brief  Configure input channel.
  * @rmtoll
  *  CCMR1        CC1S          LL_TIM_IC_Config \n
  *  CCMR1        IC1PSC        LL_TIM_IC_Config \n
  *  CCMR1        IC1F          LL_TIM_IC_Config \n
  *  CCMR1        CC2S          LL_TIM_IC_Config \n
  *  CCMR1        IC2PSC        LL_TIM_IC_Config \n
  *  CCMR1        IC2F          LL_TIM_IC_Config \n
  *  CCMR2        CC3S          LL_TIM_IC_Config \n
  *  CCMR2        IC3PSC        LL_TIM_IC_Config \n
  *  CCMR2        IC3F          LL_TIM_IC_Config \n
  *  CCMR2        CC4S          LL_TIM_IC_Config \n
  *  CCMR2        IC4PSC        LL_TIM_IC_Config \n
  *  CCMR2        IC4F          LL_TIM_IC_Config \n
  *  CCER         CC1P          LL_TIM_IC_Config \n
  *  CCER         CC1NP         LL_TIM_IC_Config \n
  *  CCER         CC2P          LL_TIM_IC_Config \n
  *  CCER         CC2NP         LL_TIM_IC_Config \n
  *  CCER         CC3P          LL_TIM_IC_Config \n
  *  CCER         CC3NP         LL_TIM_IC_Config \n
  *  CCER         CC4P          LL_TIM_IC_Config \n
  *  CCER         CC4NP         LL_TIM_IC_Config
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_TIM_ACTIVEINPUT_DIRECT or @ref LL_TIM_ACTIVEINPUT_INDIRECT or @ref LL_TIM_ACTIVEINPUT_TRC
  *         @arg @ref LL_TIM_ICPSC_DIV1 or ... or @ref LL_TIM_ICPSC_DIV8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1 or ... or @ref LL_TIM_IC_FILTER_FDIV32_N8
  *         @arg @ref LL_TIM_IC_POLARITY_RISING or @ref LL_TIM_IC_POLARITY_FALLING or
                 @ref LL_TIM_IC_POLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_TIM_IC_Config(TIM_TypeDef *timx, uint32_t channel, uint32_t configuration)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC | TIM_CCMR1_CC1S) << LL_TIM_SHIFT_TAB_ICxx[ichannel]),
             ((configuration >> 16U) & (TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC | TIM_CCMR1_CC1S))                \
             << LL_TIM_SHIFT_TAB_ICxx[ichannel]);
  MODIFY_REG(timx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << LL_TIM_SHIFT_TAB_CCxP[ichannel]),
             (configuration & (TIM_CCER_CC1NP | TIM_CCER_CC1P)) << LL_TIM_SHIFT_TAB_CCxP[ichannel]);
}

/**
  * @brief  Set the active input.
  * @rmtoll
  *  CCMR1        CC1S          LL_TIM_IC_SetActiveInput \n
  *  CCMR1        CC2S          LL_TIM_IC_SetActiveInput \n
  *  CCMR2        CC3S          LL_TIM_IC_SetActiveInput \n
  *  CCMR2        CC4S          LL_TIM_IC_SetActiveInput
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @param  ic_active_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ACTIVEINPUT_DIRECT
  *         @arg @ref LL_TIM_ACTIVEINPUT_INDIRECT
  *         @arg @ref LL_TIM_ACTIVEINPUT_TRC
  */
__STATIC_INLINE void LL_TIM_IC_SetActiveInput(TIM_TypeDef *timx, uint32_t channel, uint32_t ic_active_input)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_CC1S) << LL_TIM_SHIFT_TAB_ICxx[ichannel]),
             (ic_active_input >> LL_TIM_IC_CONFIG_POS) << LL_TIM_SHIFT_TAB_ICxx[ichannel]);
}

/**
  * @brief  Get the current active input.
  * @rmtoll
  *  CCMR1        CC1S          LL_TIM_IC_GetActiveInput \n
  *  CCMR1        CC2S          LL_TIM_IC_GetActiveInput \n
  *  CCMR2        CC3S          LL_TIM_IC_GetActiveInput \n
  *  CCMR2        CC4S          LL_TIM_IC_GetActiveInput
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_ACTIVEINPUT_DIRECT
  *         @arg @ref LL_TIM_ACTIVEINPUT_INDIRECT
  *         @arg @ref LL_TIM_ACTIVEINPUT_TRC
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetActiveInput(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_CC1S) << LL_TIM_SHIFT_TAB_ICxx[ichannel])) >> LL_TIM_SHIFT_TAB_ICxx[ichannel]) \
          << LL_TIM_IC_CONFIG_POS);
}

/**
  * @brief  Set the prescaler of input channel.
  * @rmtoll
  *  CCMR1        IC1PSC        LL_TIM_IC_SetPrescaler \n
  *  CCMR1        IC2PSC        LL_TIM_IC_SetPrescaler \n
  *  CCMR2        IC3PSC        LL_TIM_IC_SetPrescaler \n
  *  CCMR2        IC4PSC        LL_TIM_IC_SetPrescaler
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @param  ic_prescaler This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ICPSC_DIV1
  *         @arg @ref LL_TIM_ICPSC_DIV2
  *         @arg @ref LL_TIM_ICPSC_DIV4
  *         @arg @ref LL_TIM_ICPSC_DIV8
  */
__STATIC_INLINE void LL_TIM_IC_SetPrescaler(TIM_TypeDef *timx, uint32_t channel, uint32_t ic_prescaler)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1PSC) << LL_TIM_SHIFT_TAB_ICxx[ichannel]),
             (ic_prescaler >> LL_TIM_IC_CONFIG_POS) << LL_TIM_SHIFT_TAB_ICxx[ichannel]);
}

/**
  * @brief  Get the current prescaler value acting on an  input channel.
  * @rmtoll
  *  CCMR1        IC1PSC        LL_TIM_IC_GetPrescaler \n
  *  CCMR1        IC2PSC        LL_TIM_IC_GetPrescaler \n
  *  CCMR2        IC3PSC        LL_TIM_IC_GetPrescaler \n
  *  CCMR2        IC4PSC        LL_TIM_IC_GetPrescaler
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_ICPSC_DIV1
  *         @arg @ref LL_TIM_ICPSC_DIV2
  *         @arg @ref LL_TIM_ICPSC_DIV4
  *         @arg @ref LL_TIM_ICPSC_DIV8
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetPrescaler(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_IC1PSC) << LL_TIM_SHIFT_TAB_ICxx[ichannel])) \
           >> LL_TIM_SHIFT_TAB_ICxx[ichannel]) << LL_TIM_IC_CONFIG_POS);
}

/**
  * @brief  Set the input filter duration.
  * @rmtoll
  *  CCMR1        IC1F          LL_TIM_IC_SetFilter \n
  *  CCMR1        IC2F          LL_TIM_IC_SetFilter \n
  *  CCMR2        IC3F          LL_TIM_IC_SetFilter \n
  *  CCMR2        IC4F          LL_TIM_IC_SetFilter
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @param  ic_filter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N8
  */
__STATIC_INLINE void LL_TIM_IC_SetFilter(TIM_TypeDef *timx, uint32_t channel, uint32_t ic_filter)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1F) << LL_TIM_SHIFT_TAB_ICxx[ichannel]),
             (ic_filter >> LL_TIM_IC_CONFIG_POS) << LL_TIM_SHIFT_TAB_ICxx[ichannel]);
}

/**
  * @brief  Get the input filter duration.
  * @rmtoll
  *  CCMR1        IC1F          LL_TIM_IC_GetFilter \n
  *  CCMR1        IC2F          LL_TIM_IC_GetFilter \n
  *  CCMR2        IC3F          LL_TIM_IC_GetFilter \n
  *  CCMR2        IC4F          LL_TIM_IC_GetFilter
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N8
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetFilter(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCMR1) + \
                                                           LL_TIM_OFFSET_TAB_CCMRx[ichannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_IC1F) << LL_TIM_SHIFT_TAB_ICxx[ichannel])) >> LL_TIM_SHIFT_TAB_ICxx[ichannel]) \
          << LL_TIM_IC_CONFIG_POS);
}

/**
  * @brief  Set the input channel polarity.
  * @rmtoll
  *  CCER         CC1P          LL_TIM_IC_SetPolarity \n
  *  CCER         CC1NP         LL_TIM_IC_SetPolarity \n
  *  CCER         CC2P          LL_TIM_IC_SetPolarity \n
  *  CCER         CC2NP         LL_TIM_IC_SetPolarity \n
  *  CCER         CC3P          LL_TIM_IC_SetPolarity \n
  *  CCER         CC3NP         LL_TIM_IC_SetPolarity \n
  *  CCER         CC4P          LL_TIM_IC_SetPolarity \n
  *  CCER         CC4NP         LL_TIM_IC_SetPolarity
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @param  ic_polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_IC_POLARITY_RISING
  *         @arg @ref LL_TIM_IC_POLARITY_FALLING
  *         @arg @ref LL_TIM_IC_POLARITY_RISING_FALLING
  */
__STATIC_INLINE void LL_TIM_IC_SetPolarity(TIM_TypeDef *timx, uint32_t channel, uint32_t ic_polarity)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  MODIFY_REG(timx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << LL_TIM_SHIFT_TAB_CCxP[ichannel]),
             ic_polarity << LL_TIM_SHIFT_TAB_CCxP[ichannel]);
}

/**
  * @brief  Get the current input channel polarity.
  * @rmtoll
  *  CCER         CC1P          LL_TIM_IC_GetPolarity \n
  *  CCER         CC1NP         LL_TIM_IC_GetPolarity \n
  *  CCER         CC2P          LL_TIM_IC_GetPolarity \n
  *  CCER         CC2NP         LL_TIM_IC_GetPolarity \n
  *  CCER         CC3P          LL_TIM_IC_GetPolarity \n
  *  CCER         CC3NP         LL_TIM_IC_GetPolarity \n
  *  CCER         CC4P          LL_TIM_IC_GetPolarity \n
  *  CCER         CC4NP         LL_TIM_IC_GetPolarity
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_IC_POLARITY_RISING
  *         @arg @ref LL_TIM_IC_POLARITY_FALLING
  *         @arg @ref LL_TIM_IC_POLARITY_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetPolarity(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  return (READ_BIT(timx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << LL_TIM_SHIFT_TAB_CCxP[ichannel])) >>
          LL_TIM_SHIFT_TAB_CCxP[ichannel]);
}

/**
  * @brief  Connect the TIMx_CH1, CH2 and CH3 pins to the TI1 input (XOR combination).
  * @note Macro IS_TIM_XOR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an XOR input.
  * @rmtoll
  *  CR2          TI1S          LL_TIM_IC_EnableXORCombination
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_IC_EnableXORCombination(TIM_TypeDef *timx)
{
  SET_BIT(timx->CR2, TIM_CR2_TI1S);
}

/**
  * @brief  Disconnect the TIMx_CH1, CH2 and CH3 pins from the TI1 input.
  * @note Macro IS_TIM_XOR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an XOR input.
  * @rmtoll
  *  CR2          TI1S          LL_TIM_IC_DisableXORCombination
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_IC_DisableXORCombination(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->CR2, TIM_CR2_TI1S);
}

/**
  * @brief  Indicates whether the TIMx_CH1, CH2 and CH3 pins are connectected to the TI1 input.
  * @note Macro IS_TIM_XOR_INSTANCE(timx) can be used to check whether or not
  * a timer instance provides an XOR input.
  * @rmtoll
  *  CR2          TI1S          LL_TIM_IC_IsEnabledXORCombination
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IC_IsEnabledXORCombination(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->CR2, TIM_CR2_TI1S) == (TIM_CR2_TI1S)) ? 1UL : 0UL);
}

/**
  * @brief  Get captured value for input channel 1.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(timx) can be used to check whether or not
  *       input channel 1 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR1         CCR1          LL_TIM_IC_GetCaptureCH1
  * @param  timx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH1(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR1));
}

/**
  * @brief  Get captured value for input channel 2.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(timx) can be used to check whether or not
  *       input channel 2 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR2         CCR2          LL_TIM_IC_GetCaptureCH2
  * @param  timx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH2(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR2));
}

/**
  * @brief  Get captured value for input channel 3.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(timx) can be used to check whether or not
  *       input channel 3 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR3         CCR3          LL_TIM_IC_GetCaptureCH3
  * @param  timx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH3(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR3));
}

/**
  * @brief  Get captured value for input channel 4.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(timx) can be used to check whether or not
  *       input channel 4 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR4         CCR4          LL_TIM_IC_GetCaptureCH4
  * @param  timx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH4(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CCR4));
}

/**
  * @brief  Get captured value for the selected capture unit.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll
  *  CCR1         CCR1          LL_TIM_IC_GetCapturedValue \n
  *  CCR2         CCR2          LL_TIM_IC_GetCapturedValue \n
  *  CCR3         CCR3          LL_TIM_IC_GetCapturedValue \n
  *  CCR4         CCR4          LL_TIM_IC_GetCapturedValue
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t LL_TIM_IC_GetCapturedValue(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  ichannel >>= 1U; /* Divide by 2 to comply with LL_TIM_OFFSET_TAB_CCRx indexes */
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->CCR1) + \
                                                           LL_TIM_OFFSET_TAB_CCRx[ichannel]));
  return (uint32_t)(READ_REG(*pReg));
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_Clock_Selection Counter clock selection
  * @{
  */
/**
  * @brief  Enable external clock mode 2.
  * @note When external clock mode 2 is enabled the counter is clocked by any active edge on the ETRF signal.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll
  *  SMCR         ECE           LL_TIM_EnableExternalClock
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableExternalClock(TIM_TypeDef *timx)
{
  SET_BIT(timx->SMCR, TIM_SMCR_ECE);
}

/**
  * @brief  Disable external clock mode 2.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll
  *  SMCR         ECE           LL_TIM_DisableExternalClock
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableExternalClock(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->SMCR, TIM_SMCR_ECE);
}

/**
  * @brief  Indicate whether external clock mode 2 is enabled.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll
  *  SMCR         ECE           LL_TIM_IsEnabledExternalClock
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledExternalClock(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SMCR, TIM_SMCR_ECE) == (TIM_SMCR_ECE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the clock source of the counter clock.
  * @note when selected clock source is external clock mode 1, the timer input
  *       the external clock is applied is selected by calling the @ref LL_TIM_SetTriggerInput()
  *       function. This timer input must be configured by calling
  *       the @ref LL_TIM_IC_Config() function.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports external clock mode1.
  * @note Macro IS_TIM_ETR_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @note Macro IS_TIM_ENCODER_INTERFACE_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the encoder mode.
  * @rmtoll
  *  SMCR         SMS           LL_TIM_SetClockSource \n
  *  SMCR         ECE           LL_TIM_SetClockSource
  * @param  timx Timer instance
  * @param  clock_source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CLK_INTERNAL
  *         @arg @ref LL_TIM_CLK_EXTERNAL_MODE1
  *         @arg @ref LL_TIM_CLK_EXTERNAL_MODE2
  *         @arg @ref LL_TIM_CLK_ENCODER_X1_TI1
  *         @arg @ref LL_TIM_CLK_ENCODER_X1_TI2
  *         @arg @ref LL_TIM_CLK_ENCODER_X2_TI1
  *         @arg @ref LL_TIM_CLK_ENCODER_X2_TI2
  *         @arg @ref LL_TIM_CLK_ENCODER_X4_TI12
  *         @arg @ref LL_TIM_CLK_ENCODER_CLK_PLUS_X2
  *         @arg @ref LL_TIM_CLK_ENCODER_CLK_PLUS_X1
  *         @arg @ref LL_TIM_CLK_ENCODER_DIR_CLK_X2
  *         @arg @ref LL_TIM_CLK_ENCODER_DIR_CLK_X1_TI12
  */
__STATIC_INLINE void LL_TIM_SetClockSource(TIM_TypeDef *timx, uint32_t clock_source)
{
  MODIFY_REG(timx->SMCR, TIM_SMCR_SMS | TIM_SMCR_ECE, clock_source);
}

/**
  * @brief  Get the clock source of the counter clock.
  * @rmtoll
  *  SMCR         SMS           LL_TIM_GetClockSource \n
  *  SMCR         ECE           LL_TIM_GetClockSource
  * @param  timx Timer instance
  * @note If external clock mode 1 and external clock mode 2 are enabled
  *       at the same time, the external clock input is tim_etrf.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_CLK_INTERNAL
  *         @arg @ref LL_TIM_CLK_EXTERNAL_MODE1
  *         @arg @ref LL_TIM_CLK_EXTERNAL_MODE2
  *         @arg @ref LL_TIM_CLK_ENCODER_X1_TI1
  *         @arg @ref LL_TIM_CLK_ENCODER_X1_TI2
  *         @arg @ref LL_TIM_CLK_ENCODER_X2_TI1
  *         @arg @ref LL_TIM_CLK_ENCODER_X2_TI2
  *         @arg @ref LL_TIM_CLK_ENCODER_X4_TI12
  *         @arg @ref LL_TIM_CLK_ENCODER_CLK_PLUS_X2
  *         @arg @ref LL_TIM_CLK_ENCODER_CLK_PLUS_X1
  *         @arg @ref LL_TIM_CLK_ENCODER_DIR_CLK_X2
  *         @arg @ref LL_TIM_CLK_ENCODER_DIR_CLK_X1_TI12
  */
__STATIC_INLINE uint32_t LL_TIM_GetClockSource(const TIM_TypeDef *timx)
{
  uint32_t smcr = READ_REG(timx->SMCR);

  return (uint32_t)(((smcr & TIM_SMCR_ECE) == LL_TIM_CLK_EXTERNAL_MODE2) ? \
                    LL_TIM_CLK_EXTERNAL_MODE2 : (smcr & TIM_SMCR_SMS));
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_Timer_Synchronization Timer synchronisation configuration
  * @{
  */
/**
  * @brief  Set the trigger output (TRGO) used for timer synchronization.
  * @note Macro IS_TIM_MASTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance can operate as a master timer.
  * @rmtoll
  *  CR2          MMS           LL_TIM_SetTriggerOutput
  * @param  timx Timer instance
  * @param  timer_synchronization This parameter can be one of the following values:
  *         @arg @ref LL_TIM_TRGO_RESET
  *         @arg @ref LL_TIM_TRGO_ENABLE
  *         @arg @ref LL_TIM_TRGO_UPDATE
  *         @arg @ref LL_TIM_TRGO_CC1IF
  *         @arg @ref LL_TIM_TRGO_OC1
  *         @arg @ref LL_TIM_TRGO_OC2
  *         @arg @ref LL_TIM_TRGO_OC3
  *         @arg @ref LL_TIM_TRGO_OC4
  *         @arg @ref LL_TIM_TRGO_ENCODERCLK
  */
__STATIC_INLINE void LL_TIM_SetTriggerOutput(TIM_TypeDef *timx, uint32_t timer_synchronization)
{
  MODIFY_REG(timx->CR2, TIM_CR2_MMS, timer_synchronization);
}

/**
  * @brief  Get the source of the trigger output (TRGO).
  * @note Macro IS_TIM_MASTER_INSTANCE(timx) can be used to check
  *       whether or not a timer instance can operate as a master timer.
  * @rmtoll
  *  CR2          MMS           LL_TIM_GetTriggerOutput
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_TRGO_RESET
  *         @arg @ref LL_TIM_TRGO_ENABLE
  *         @arg @ref LL_TIM_TRGO_UPDATE
  *         @arg @ref LL_TIM_TRGO_CC1IF
  *         @arg @ref LL_TIM_TRGO_OC1
  *         @arg @ref LL_TIM_TRGO_OC2
  *         @arg @ref LL_TIM_TRGO_OC3
  *         @arg @ref LL_TIM_TRGO_OC4
  *         @arg @ref LL_TIM_TRGO_ENCODERCLK
  */
__STATIC_INLINE uint32_t LL_TIM_GetTriggerOutput(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CR2) & TIM_CR2_MMS);
}

/**
  * @brief  Set the trigger output 2 (TRGO2) used for ADC synchronization .
  * @note Macro IS_TIM_TRGO2_INSTANCE(timx) can be used to check
  *       whether or not a timer instance can be used for ADC synchronization.
  * @rmtoll
  *  CR2          MMS2          LL_TIM_SetTriggerOutput2
  * @param  timx Timer Instance
  * @param  adc_synchronization This parameter can be one of the following values:
  *         @arg @ref LL_TIM_TRGO2_RESET
  *         @arg @ref LL_TIM_TRGO2_ENABLE
  *         @arg @ref LL_TIM_TRGO2_UPDATE
  *         @arg @ref LL_TIM_TRGO2_CC1F
  *         @arg @ref LL_TIM_TRGO2_OC1
  *         @arg @ref LL_TIM_TRGO2_OC2
  *         @arg @ref LL_TIM_TRGO2_OC3
  *         @arg @ref LL_TIM_TRGO2_OC4
  *         @arg @ref LL_TIM_TRGO2_OC5
  *         @arg @ref LL_TIM_TRGO2_OC6
  *         @arg @ref LL_TIM_TRGO2_OC4_RISING_FALLING
  *         @arg @ref LL_TIM_TRGO2_OC6_RISING_FALLING
  *         @arg @ref LL_TIM_TRGO2_OC4_RISING_OC6_RISING
  *         @arg @ref LL_TIM_TRGO2_OC5_RISING_OC6_RISING
  *         @arg @ref LL_TIM_TRGO2_OC4_RISING_OC6_FALLING
  *         @arg @ref LL_TIM_TRGO2_OC5_RISING_OC6_FALLING
  */
__STATIC_INLINE void LL_TIM_SetTriggerOutput2(TIM_TypeDef *timx, uint32_t adc_synchronization)
{
  MODIFY_REG(timx->CR2, TIM_CR2_MMS2, adc_synchronization);
}

/**
  * @brief  Get the source of the trigger output 2 (TRGO2).
  * @note Macro IS_TIM_TRGO2_INSTANCE(timx) can be used to check
  *       whether or not a timer instance can be used for ADC synchronization.
  * @rmtoll
  *  CR2          MMS2          LL_TIM_GetTriggerOutput2
  * @param  timx Timer Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_TRGO2_RESET
  *         @arg @ref LL_TIM_TRGO2_ENABLE
  *         @arg @ref LL_TIM_TRGO2_UPDATE
  *         @arg @ref LL_TIM_TRGO2_CC1F
  *         @arg @ref LL_TIM_TRGO2_OC1
  *         @arg @ref LL_TIM_TRGO2_OC2
  *         @arg @ref LL_TIM_TRGO2_OC3
  *         @arg @ref LL_TIM_TRGO2_OC4
  *         @arg @ref LL_TIM_TRGO2_OC5
  *         @arg @ref LL_TIM_TRGO2_OC6
  *         @arg @ref LL_TIM_TRGO2_OC4_RISING_FALLING
  *         @arg @ref LL_TIM_TRGO2_OC6_RISING_FALLING
  *         @arg @ref LL_TIM_TRGO2_OC4_RISING_OC6_RISING
  *         @arg @ref LL_TIM_TRGO2_OC5_RISING_OC6_RISING
  *         @arg @ref LL_TIM_TRGO2_OC4_RISING_OC6_FALLING
  *         @arg @ref LL_TIM_TRGO2_OC5_RISING_OC6_FALLING
  */
__STATIC_INLINE uint32_t LL_TIM_GetTriggerOutput2(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->CR2) & TIM_CR2_MMS2);
}

/**
  * @brief  Set the synchronization mode of a slave timer.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         SMS           LL_TIM_SetSlaveMode
  * @param  timx Timer instance
  * @param  slave_mode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_SLAVEMODE_DISABLED
  *         @arg @ref LL_TIM_SLAVEMODE_RESET
  *         @arg @ref LL_TIM_SLAVEMODE_GATED
  *         @arg @ref LL_TIM_SLAVEMODE_TRIGGER
  *         @arg @ref LL_TIM_SLAVEMODE_COMBINED_RESET_TRIGGER
  *         @arg @ref LL_TIM_SLAVEMODE_COMBINED_GATED_RESET
  */
__STATIC_INLINE void LL_TIM_SetSlaveMode(TIM_TypeDef *timx, uint32_t slave_mode)
{
  MODIFY_REG(timx->SMCR, TIM_SMCR_SMS, slave_mode);
}

/**
  * @brief  Get the synchronization mode of a slave timer.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         SMS           LL_TIM_GetSlaveMode
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_SLAVEMODE_DISABLED
  *         @arg @ref LL_TIM_SLAVEMODE_RESET
  *         @arg @ref LL_TIM_SLAVEMODE_GATED
  *         @arg @ref LL_TIM_SLAVEMODE_TRIGGER
  *         @arg @ref LL_TIM_SLAVEMODE_COMBINED_RESET_TRIGGER
  *         @arg @ref LL_TIM_SLAVEMODE_COMBINED_GATED_RESET
  */
__STATIC_INLINE uint32_t LL_TIM_GetSlaveMode(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->SMCR) & TIM_SMCR_SMS);
}

/**
  * @brief  Set the selects the trigger input to be used to synchronize the counter.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         TS            LL_TIM_SetTriggerInput
  * @param  timx Timer instance
  * @param  trigger_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_TS_ITR0
  *         @arg @ref LL_TIM_TS_ITR1
  *         @arg @ref LL_TIM_TS_ITR2
  *         @arg @ref LL_TIM_TS_ITR3
  *         @arg @ref LL_TIM_TS_ITR4
  *         @arg @ref LL_TIM_TS_ITR5
  *         @arg @ref LL_TIM_TS_ITR6
  *         @arg @ref LL_TIM_TS_ITR7
  *         @arg @ref LL_TIM_TS_ITR8
  * @if USB_OTG_FS
  *         @arg @ref LL_TIM_TS_ITR11 (*)
  * @endif
  *         @arg @ref LL_TIM_TS_TI1F_ED
  *         @arg @ref LL_TIM_TS_TI1FP1
  *         @arg @ref LL_TIM_TS_TI2FP2
  *         @arg @ref LL_TIM_TS_ETRF
  *
  *         (*)  Value not defined in all devices.
  *
  */
__STATIC_INLINE void LL_TIM_SetTriggerInput(TIM_TypeDef *timx, uint32_t trigger_input)
{
  MODIFY_REG(timx->SMCR, TIM_SMCR_TS, trigger_input);
}

/**
  * @brief  Get the trigger input used to synchronize the counter.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         TS            LL_TIM_GetTriggerInput
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_TS_ITR0
  *         @arg @ref LL_TIM_TS_ITR1
  *         @arg @ref LL_TIM_TS_ITR2
  *         @arg @ref LL_TIM_TS_ITR3
  *         @arg @ref LL_TIM_TS_ITR4
  *         @arg @ref LL_TIM_TS_ITR5
  *         @arg @ref LL_TIM_TS_ITR6
  *         @arg @ref LL_TIM_TS_ITR7
  *         @arg @ref LL_TIM_TS_ITR8
  * @if USB_OTG_FS
  *         @arg @ref LL_TIM_TS_ITR11 (*)
  * @endif
  *         @arg @ref LL_TIM_TS_TI1F_ED
  *         @arg @ref LL_TIM_TS_TI1FP1
  *         @arg @ref LL_TIM_TS_TI2FP2
  *         @arg @ref LL_TIM_TS_ETRF
  *
  *         (*)  Value not defined in all devices.
  *
  */
__STATIC_INLINE uint32_t LL_TIM_GetTriggerInput(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->SMCR) & TIM_SMCR_TS);
}

/**
  * @brief  Enable the Master/Slave mode.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         MSM           LL_TIM_EnableMasterSlaveMode
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableMasterSlaveMode(TIM_TypeDef *timx)
{
  SET_BIT(timx->SMCR, TIM_SMCR_MSM);
}

/**
  * @brief  Disable the Master/Slave mode.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         MSM           LL_TIM_DisableMasterSlaveMode
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableMasterSlaveMode(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->SMCR, TIM_SMCR_MSM);
}

/**
  * @brief Indicates whether the Master/Slave mode is enabled.
  * @note Macro IS_TIM_SLAVE_INSTANCE(timx) can be used to check whether or not
  * a timer instance can operate as a slave timer.
  * @rmtoll
  *  SMCR         MSM           LL_TIM_IsEnabledMasterSlaveMode
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledMasterSlaveMode(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SMCR, TIM_SMCR_MSM) == (TIM_SMCR_MSM)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the external trigger (ETR) input.
  * @note Macro IS_TIM_ETR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an external trigger input.
  * @rmtoll
  *  SMCR         ETP           LL_TIM_ConfigETR \n
  *  SMCR         ETPS          LL_TIM_ConfigETR \n
  *  SMCR         ETF           LL_TIM_ConfigETR
  * @param  timx Timer instance
  * @param  etr_polarity This parameter can be one of the following values: \n
  *         @arg @ref LL_TIM_ETR_POLARITY_NONINVERTED
  *         @arg @ref LL_TIM_ETR_POLARITY_INVERTED
  * @param  etr_prescaler This parameter can be one of the following values: \n
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV1
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV2
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV4
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV8
  * @param  etr_filter This parameter can be one of the following values: \n
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N8
  */
__STATIC_INLINE void LL_TIM_ConfigETR(TIM_TypeDef *timx, uint32_t etr_polarity, uint32_t etr_prescaler,
                                      uint32_t etr_filter)
{
  MODIFY_REG(timx->SMCR, TIM_SMCR_ETP | TIM_SMCR_ETPS | TIM_SMCR_ETF, etr_polarity | etr_prescaler | etr_filter);
}

/**
  * @brief  Get the external trigger (ETR) input configuration.
  * @note Macro IS_TIM_ETR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an external trigger input.
  * @rmtoll
  *  SMCR         ETP           LL_TIM_GetConfigETR \n
  *  SMCR         ETPS          LL_TIM_GetConfigETR \n
  *  SMCR         ETF           LL_TIM_GetConfigETR
  * @param  timx Timer instance
  * @param  p_etr_polarity Pointer to a storage for ETR polarity. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_ETR_POLARITY_NONINVERTED
  *         @arg @ref LL_TIM_ETR_POLARITY_INVERTED
  * @param  p_etr_prescaler Pointer to a storage for ETR prescaler. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV1
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV2
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV4
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV8
  * @param  p_etr_filter Pointer to a storage for ETR filter. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N8
  */
__STATIC_INLINE void LL_TIM_GetConfigETR(TIM_TypeDef *timx, uint32_t *p_etr_polarity, uint32_t *p_etr_prescaler,
                                         uint32_t *p_etr_filter)
{
  const __IO uint32_t smcr = READ_REG(timx->SMCR);

  *p_etr_polarity = smcr & TIM_SMCR_ETP;
  *p_etr_prescaler = smcr & TIM_SMCR_ETPS;
  *p_etr_filter = smcr & TIM_SMCR_ETF;
}

/**
  * @brief  Select the external trigger (ETR) input source.
  * @note Macro IS_TIM_ETRSEL_INSTANCE(timx) can be used to check whether or
  *       not a timer instance supports ETR source selection.
  * @rmtoll
  *  AF1          ETRSEL        LL_TIM_SetETRSource
  * @param  timx Timer instance
  * @param  etr_source This parameter can be one of the following values:
  *
  *         TIM1: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC2_AWD1   (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC2_AWD2   (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC2_AWD3   (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC1_AWD1
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC1_AWD2
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC1_AWD3
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC4_AWD1
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC4_AWD2
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC4_AWD3
  *
  *         TIM2: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_TIM3_ETR
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_TIM4_ETR
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_TIM5_ETR
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_LSE
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM3: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_TIM2_ETR
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_TIM4_ETR
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_ADC1_AWD1
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_ADC1_AWD2
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_ADC1_AWD3
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM4: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_TIM3_ETR
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_TIM5_ETR
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_ADC2_AWD1   (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_ADC2_AWD2   (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_ADC2_AWD3   (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM5: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_TIM2_ETR
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_TIM3_ETR
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM8: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC2_AWD1   (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC2_AWD2   (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC2_AWD3   (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC1_AWD1
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC1_AWD2
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC1_AWD3
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC4_AWD1
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC4_AWD2
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC4_AWD3
  *
  *         (*)  Value not defined in all devices. \n
  *
  */
__STATIC_INLINE void LL_TIM_SetETRSource(TIM_TypeDef *timx, uint32_t etr_source)
{
  MODIFY_REG(timx->AF1, TIM1_AF1_ETRSEL, etr_source);
}

/**
  * @brief  Get the source of the external trigger input (ETR).
  * @note Macro IS_TIM_ETRSEL_INSTANCE(timx) can be used to check whether or
  *       not a timer instance supports ETR source selection.
  * @rmtoll
  *  AF1          ETRSEL        LL_TIM_GetETRSource
  * @param  timx Timer instance
  * @retval  ETR source that can be one of the following values:
  *
  *         TIM1: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC2_AWD1   (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC2_AWD2   (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC2_AWD3   (*)
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC1_AWD1
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC1_AWD2
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC1_AWD3
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC4_AWD1
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC4_AWD2
  *            @arg @ref LL_TIM_TIM1_ETRSOURCE_ADC4_AWD3
  *
  *         TIM2: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_TIM3_ETR
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_TIM4_ETR
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_TIM5_ETR
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_LSE
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM2_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM3: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_TIM2_ETR
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_TIM4_ETR
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_ADC1_AWD1
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_ADC1_AWD2
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_ADC1_AWD3
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM3_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM4: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_TIM3_ETR
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_TIM5_ETR
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_ADC2_AWD1   (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_ADC2_AWD2   (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_ADC2_AWD3   (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM4_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM5: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_DCMI_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_LTDC_VSYNC  (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_TIM2_ETR
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_TIM3_ETR
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_DSI_TE      (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_DCMI_HSYNC  (*)
  *            @arg @ref LL_TIM_TIM5_ETRSOURCE_LTDC_HSYNC  (*)
  *
  *         TIM8: one of the following values:
  *
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_GPIO
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_COMP1
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_COMP2       (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_MSIK
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_HSI
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_MSIS
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC2_AWD1   (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC2_AWD2   (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC2_AWD3   (*)
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC1_AWD1
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC1_AWD2
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC1_AWD3
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC4_AWD1
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC4_AWD2
  *            @arg @ref LL_TIM_TIM8_ETRSOURCE_ADC4_AWD3
  *
  *         (*)  Value not defined in all devices. \n
  *
  */
__STATIC_INLINE uint32_t LL_TIM_GetETRSource(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_REG(timx->AF1) & TIM1_AF1_ETRSEL);
}

/**
  * @brief  Enable SMS preload.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll
  *  SMCR         SMSPE           LL_TIM_EnableSMSPreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableSMSPreload(TIM_TypeDef *timx)
{
  SET_BIT(timx->SMCR, TIM_SMCR_SMSPE);
}

/**
  * @brief  Disable SMS preload.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll
  *  SMCR         SMSPE           LL_TIM_DisableSMSPreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableSMSPreload(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->SMCR, TIM_SMCR_SMSPE);
}

/**
  * @brief  Indicate whether  SMS preload is enabled.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll
  *  SMCR         SMSPE           LL_TIM_IsEnabledSMSPreload
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledSMSPreload(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SMCR, TIM_SMCR_SMSPE) == (TIM_SMCR_SMSPE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the preload source of SMS.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll
  *  SMCR         SMSPS        LL_TIM_SetSMSPreloadSource
  * @param  timx Timer instance
  * @param  preload_source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_SLAVE_MODE_PRELOAD_UPDATE
  *         @arg @ref LL_TIM_SLAVE_MODE_PRELOAD_INDEX
  */
__STATIC_INLINE void LL_TIM_SetSMSPreloadSource(TIM_TypeDef *timx, uint32_t preload_source)
{
  MODIFY_REG(timx->SMCR, TIM_SMCR_SMSPS, preload_source);
}

/**
  * @brief  Get the preload source of SMS.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(timx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll
  *  SMCR         SMSPS        LL_TIM_GetSMSPreloadSource
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_SLAVE_MODE_PRELOAD_UPDATE
  *         @arg @ref LL_TIM_SLAVE_MODE_PRELOAD_INDEX
  */
__STATIC_INLINE uint32_t LL_TIM_GetSMSPreloadSource(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->SMCR, TIM_SMCR_SMSPS));
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Break_Function Break function configuration
  * @{
  */
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         BKE           LL_TIM_EnableBRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableBRK(TIM_TypeDef *timx)
{
  SET_BIT(timx->BDTR, TIM_BDTR_BKE);
}

/**
  * @brief  Disable the break function.
  * @rmtoll
  *  BDTR         BKE           LL_TIM_DisableBRK
  * @param  timx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  */
__STATIC_INLINE void LL_TIM_DisableBRK(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->BDTR, TIM_BDTR_BKE);
}

/**
  * @brief  Configure the break input.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @note Bidirectional mode is only supported by advanced timer instances.
  * @note In bidirectional mode (BKBID bit set), the Break input is configured both
  *        in input mode and in open drain output mode. Any active Break event will
  *        assert a low logic level on the Break input to indicate an internal break
  *        event to external devices.
  * @note When bidirectional mode isn't supported, break_afmode must be set to
  *       LL_TIM_BREAK_AFMODE_INPUT.
  * @rmtoll
  *  BDTR         BKP           LL_TIM_ConfigBRK \n
  *  BDTR         BKF           LL_TIM_ConfigBRK \n
  *  BDTR         BKBID         LL_TIM_ConfigBRK
  * @param  timx Timer instance
  * @param  break_polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK_POLARITY_HIGH
  * @param  break_filter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N8
  * @param  break_afmode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_AFMODE_INPUT
  *         @arg @ref LL_TIM_BREAK_AFMODE_BIDIRECTIONAL
  */
__STATIC_INLINE void LL_TIM_ConfigBRK(TIM_TypeDef *timx, uint32_t break_polarity, uint32_t break_filter,
                                      uint32_t break_afmode)
{
  MODIFY_REG(timx->BDTR, TIM_BDTR_BKP | TIM_BDTR_BKF | TIM_BDTR_BKBID, break_polarity | break_filter | break_afmode);
}

/**
  * @brief  Get the break input configuration.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         BKP           LL_TIM_GetConfigBRK \n
  *  BDTR         BKF           LL_TIM_GetConfigBRK \n
  *  BDTR         BKBID         LL_TIM_GetConfigBRK
  * @param  timx Timer instance
  * @param  p_break_polarity Pointer to a storage for break polarity. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_BREAK_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK_POLARITY_HIGH
  * @param  p_break_filter  Pointer to a storage for break filter. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N8
  * @param  p_break_afmode Pointer to a storage for break afmode. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_BREAK_AFMODE_INPUT
  *         @arg @ref LL_TIM_BREAK_AFMODE_BIDIRECTIONAL
  */
__STATIC_INLINE void LL_TIM_GetConfigBRK(TIM_TypeDef *timx, uint32_t *p_break_polarity, uint32_t *p_break_filter,
                                         uint32_t *p_break_afmode)
{
  const __IO uint32_t bdtr = READ_REG(timx->BDTR);

  *p_break_polarity = bdtr & TIM_BDTR_BKP;
  *p_break_filter = bdtr & TIM_BDTR_BKF;
  *p_break_afmode = bdtr & TIM_BDTR_BKBID;
}

/**
  * @brief  Disarm the break input (when it operates in bidirectional mode).
  * @note  The break input can be disarmed only when it is configured in
  *        bidirectional mode and when when MOE is reset.
  * @note  Purpose is to be able to have the input voltage back to high-state,
  *        whatever the time constant on the output .
  * @rmtoll
  *  BDTR         BKDSRM        LL_TIM_DisarmBRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisarmBRK(TIM_TypeDef *timx)
{
  SET_BIT(timx->BDTR, TIM_BDTR_BKDSRM);
}

/**
  * @brief  Indicates whether the break input is disarmed.
  * @rmtoll
  *  BDTR         BKDSRM        LL_TIM_IsDisarmedBRK
  * @param  timx Timer instance
  * @retval Status of the break input (0: armed, 1: disarmed)
  */
__STATIC_INLINE uint32_t LL_TIM_IsDisarmedBRK(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->BDTR, TIM_BDTR_BKDSRM) == (TIM_BDTR_BKDSRM)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the break 2 function.
  * @note Macro IS_TIM_BKIN2_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @rmtoll
  *  BDTR         BK2E          LL_TIM_EnableBRK2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableBRK2(TIM_TypeDef *timx)
{
  SET_BIT(timx->BDTR, TIM_BDTR_BK2E);
}

/**
  * @brief  Disable the break  2 function.
  * @note Macro IS_TIM_BKIN2_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @rmtoll
  *  BDTR         BK2E          LL_TIM_DisableBRK2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableBRK2(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->BDTR, TIM_BDTR_BK2E);
}

/**
  * @brief  Configure the break 2 input.
  * @note Macro IS_TIM_BKIN2_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @note Bidirectional mode is only supported by advanced timer instances.
  * @note In bidirectional mode (BK2BID bit set), the Break 2 input is configured both
  *        in input mode and in open drain output mode. Any active Break event will
  *        assert a low logic level on the Break 2 input to indicate an internal break
  *        event to external devices.
  * @note When bidirectional mode isn't supported, break2_afmode must be set to
  *       LL_TIM_BREAK2_AFMODE_INPUT.
  * @rmtoll
  *  BDTR         BK2P          LL_TIM_ConfigBRK2 \n
  *  BDTR         BK2F          LL_TIM_ConfigBRK2 \n
  *  BDTR         BK2BID        LL_TIM_ConfigBRK2
  * @param  timx Timer instance
  * @param  break2_polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK2_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK2_POLARITY_HIGH
  * @param  break2_filter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N8
  * @param  break2_afmode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK2_AFMODE_INPUT
  *         @arg @ref LL_TIM_BREAK2_AFMODE_BIDIRECTIONAL
  */
__STATIC_INLINE void LL_TIM_ConfigBRK2(TIM_TypeDef *timx, uint32_t break2_polarity, uint32_t break2_filter,
                                       uint32_t break2_afmode)
{
  MODIFY_REG(timx->BDTR, TIM_BDTR_BK2P | TIM_BDTR_BK2F | TIM_BDTR_BK2BID,
             break2_polarity | break2_filter | break2_afmode);
}

/**
  * @brief  Get the break 2 input configuration.
  * @note Macro IS_TIM_BKIN2_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @rmtoll
  *  BDTR         BK2P           LL_TIM_GetConfigBRK2 \n
  *  BDTR         BK2F           LL_TIM_GetConfigBRK2 \n
  *  BDTR         BK2BID         LL_TIM_GetConfigBRK2
  * @param  timx Timer instance
  * @param  p_break2_polarity Pointer to a storage for break 2 polarity. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_BREAK2_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK2_POLARITY_HIGH
  * @param  p_break2_filter  Pointer to a storage for break 2 filter. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N8
  * @param  p_break2_afmode Pointer to a storage for break 2 afmode. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_BREAK2_AFMODE_INPUT
  *         @arg @ref LL_TIM_BREAK2_AFMODE_BIDIRECTIONAL
  */
__STATIC_INLINE void LL_TIM_GetConfigBRK2(TIM_TypeDef *timx, uint32_t *p_break2_polarity, uint32_t *p_break2_filter,
                                          uint32_t *p_break2_afmode)
{
  const __IO uint32_t bdtr = READ_REG(timx->BDTR);

  *p_break2_polarity = bdtr & TIM_BDTR_BK2P;
  *p_break2_filter = bdtr & TIM_BDTR_BK2F;
  *p_break2_afmode = bdtr & TIM_BDTR_BK2BID;
}

/**
  * @brief  Disarm the break 2 input (when it operates in bidirectional mode).
  * @note  The break 2 input can be disarmed only when it is configured in
  *        bidirectional mode and when when MOE is reset.
  * @note  Purpose is to be able to have the input voltage back to high-state,
  *        whatever the time constant on the output.
  * @rmtoll
  *  BDTR         BK2DSRM       LL_TIM_DisarmBRK2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisarmBRK2(TIM_TypeDef *timx)
{
  SET_BIT(timx->BDTR, TIM_BDTR_BK2DSRM);
}

/**
  * @brief  Indicates whether the break input 2 is disarmed.
  * @rmtoll
  *  BDTR         BK2DSRM       LL_TIM_IsDisarmedBRK2
  * @param  timx Timer instance
  * @retval Status of the break input 2 (0: armed, 1: disarmed)
  */
__STATIC_INLINE uint32_t LL_TIM_IsDisarmedBRK2(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->BDTR, TIM_BDTR_BK2DSRM) == (TIM_BDTR_BK2DSRM)) ? 1UL : 0UL);
}

/**
  * @brief  Disarm the break input.
  * @note  The break input can be disarmed only when it is configured in
  *        bidirectional mode and when when MOE is reset.
  * @rmtoll
  *  BDTR         BKDSRM        LL_TIM_DisarmBreakInput \n
  *  BDTR         BK2DSRM       LL_TIM_DisarmBreakInput
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  */
__STATIC_INLINE void LL_TIM_DisarmBreakInput(TIM_TypeDef *timx, uint32_t break_input)
{
  SET_BIT(timx->BDTR, (TIM_BDTR_BKDSRM << break_input));
}

/**
  * @brief  Indicates whether the break input 2 is disarmed.
  * @rmtoll
  *  BDTR         BKDSRM        LL_TIM_IsDisarmedBreakInput \n
  *  BDTR         BK2DSRM       LL_TIM_IsDisarmedBreakInput
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @retval Status of the break input 2 (0: armed, 1: disarmed)
  */
__STATIC_INLINE uint32_t LL_TIM_IsDisarmedBreakInput(const TIM_TypeDef *timx, uint32_t break_input)
{
  uint32_t disarm_bit = (TIM_BDTR_BKDSRM << break_input);
  return ((READ_BIT(timx->BDTR, disarm_bit) == (disarm_bit)) ? 1UL : 0UL);
}

/**
  * @brief  Select the outputs off state (enabled v.s. disabled) in Idle and Run modes.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         OSSI          LL_TIM_SetOffStates \n
  *  BDTR         OSSR          LL_TIM_SetOffStates
  * @param  timx Timer instance
  * @param  offstate_idle This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OSSI_DISABLE
  *         @arg @ref LL_TIM_OSSI_ENABLE
  * @param  offstate_run This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OSSR_DISABLE
  *         @arg @ref LL_TIM_OSSR_ENABLE
  */
__STATIC_INLINE void LL_TIM_SetOffStates(TIM_TypeDef *timx, uint32_t offstate_idle, uint32_t offstate_run)
{
  MODIFY_REG(timx->BDTR, TIM_BDTR_OSSI | TIM_BDTR_OSSR, offstate_idle | offstate_run);
}

/**
  * @brief  Get actual outputs off state (enabled v.s. disabled) in Idle and Run modes.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         OSSI          LL_TIM_GetOffStates \n
  *  BDTR         OSSR          LL_TIM_GetOffStates
  * @param  timx Timer instance
  * @param  offstate_idle This parameter can store one of the following values:
  *         @arg @ref LL_TIM_OSSI_DISABLE
  *         @arg @ref LL_TIM_OSSI_ENABLE
  * @param  offstate_run This parameter can store of the following values:
  *         @arg @ref LL_TIM_OSSR_DISABLE
  *         @arg @ref LL_TIM_OSSR_ENABLE
  */
__STATIC_INLINE void LL_TIM_GetOffStates(const TIM_TypeDef *timx, uint32_t *offstate_idle, uint32_t *offstate_run)
{
  const __IO uint32_t reg = READ_REG(timx->BDTR);
  *offstate_idle = reg & TIM_BDTR_OSSI;
  *offstate_run = reg & TIM_BDTR_OSSR;
}

/**
  * @brief  Enable automatic output (MOE can be set by software or automatically when a break input is active).
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         AOE           LL_TIM_EnableAutomaticOutput
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableAutomaticOutput(TIM_TypeDef *timx)
{
  SET_BIT(timx->BDTR, TIM_BDTR_AOE);
}

/**
  * @brief  Disable automatic output (MOE can be set only by software).
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         AOE           LL_TIM_DisableAutomaticOutput
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableAutomaticOutput(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->BDTR, TIM_BDTR_AOE);
}

/**
  * @brief  Indicate whether automatic output is enabled.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         AOE           LL_TIM_IsEnabledAutomaticOutput
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledAutomaticOutput(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->BDTR, TIM_BDTR_AOE) == (TIM_BDTR_AOE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the outputs (set the MOE bit in TIMx_BDTR register).
  * @note The MOE bit in TIMx_BDTR register allows to enable /disable the outputs by
  *       software and is reset in case of break or break2 event
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         MOE           LL_TIM_EnableAllOutputs
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableAllOutputs(TIM_TypeDef *timx)
{
  SET_BIT(timx->BDTR, TIM_BDTR_MOE);
}

/**
  * @brief  Disable the outputs (reset the MOE bit in TIMx_BDTR register).
  * @note The MOE bit in TIMx_BDTR register allows to enable /disable the outputs by
  *       software and is reset in case of break or break2 event.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         MOE           LL_TIM_DisableAllOutputs
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableAllOutputs(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->BDTR, TIM_BDTR_MOE);
}

/**
  * @brief  Indicates whether outputs are enabled.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll
  *  BDTR         MOE           LL_TIM_IsEnabledAllOutputs
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledAllOutputs(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->BDTR, TIM_BDTR_MOE) == (TIM_BDTR_MOE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable a break input.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) (IS_TIM_BKIN2_INSTANCE(timx))
  *       can be used to check whether or not a timer instance provides
  *       a break input (resp. a break2 input).
  * @rmtoll
  *  BDTR         BKE     LL_TIM_EnableBreakInput \n
  *  BDTR         BK2E    LL_TIM_EnableBreakInput
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  */
__STATIC_INLINE void LL_TIM_EnableBreakInput(TIM_TypeDef *timx, uint32_t break_input)
{
  SET_BIT(timx->BDTR, LL_TIM_MASK_TAB_BKxE[break_input]);
}

/**
  * @brief  Disable a break input.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) (IS_TIM_BKIN2_INSTANCE(timx))
  *       can be used to check whether or not a timer instance provides
  *       a break input (resp. a break2 input).
  * @rmtoll
  *  BDTR         BKE     LL_TIM_DisableBreakInput \n
  *  BDTR         BK2E    LL_TIM_DisableBreakInput
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  */
__STATIC_INLINE void LL_TIM_DisableBreakInput(TIM_TypeDef *timx, uint32_t break_input)
{
  CLEAR_BIT(timx->BDTR, LL_TIM_MASK_TAB_BKxE[break_input]);
}

/**
  * @brief  Indicates whether the input is enabled or not.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) (IS_TIM_BKIN2_INSTANCE(timx))
  *       can be used to check whether or not a timer instance provides
  *       a break input (resp. a break2 input).
  * @rmtoll
  *  BDTR         BKE     LL_TIM_IsEnabledBreakInput \n
  *  BDTR         BK2E    LL_TIM_IsEnabledBreakInput
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledBreakInput(const TIM_TypeDef *timx, uint32_t break_input)
{
  uint32_t bitfield = LL_TIM_MASK_TAB_BKxE[break_input];
  return ((READ_BIT(timx->BDTR, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Set the polarity of a break input.
  * @rmtoll
  *  BDTR         BKP     LL_TIM_SetBreakInputPolarity \n
  *  BDTR         BK2P    LL_TIM_SetBreakInputPolarity
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  break_polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_POLARITY_LOW  or LL_TIM_BREAK2_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK_POLARITY_HIGH or LL_TIM_BREAK2_POLARITY_HIGH
  */
__STATIC_INLINE void LL_TIM_SetBreakInputPolarity(TIM_TypeDef *timx, uint32_t break_input, uint32_t break_polarity)
{
  MODIFY_REG(timx->BDTR, LL_TIM_MASK_TAB_BKxP[break_input], break_polarity);
}

/**
  * @brief  Get the polarity of a break input.
  * @rmtoll
  *  BDTR         BKP     LL_TIM_GetBreakInputPolarity \n
  *  BDTR         BK2P    LL_TIM_GetBreakInputPolarity
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_POLARITY_LOW  or @arg @ref LL_TIM_BREAK2_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK_POLARITY_HIGH or @arg @ref LL_TIM_BREAK2_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_TIM_GetBreakInputPolarity(const TIM_TypeDef *timx, uint32_t break_input)
{
  return (uint32_t)(READ_BIT(timx->BDTR, LL_TIM_MASK_TAB_BKxP[break_input]));
}

/**
  * @brief  Set the digital filter of a break input.
  * @rmtoll
  *  BDTR         BKF     LL_TIM_SetBreakInputFilter \n
  *  BDTR         BK2F    LL_TIM_SetBreakInputFilter
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  break_filter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1     or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N2  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N4  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N6  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N6  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N6  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N5 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N6 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N8 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N5 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N6 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N8 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N8
  */
__STATIC_INLINE void LL_TIM_SetBreakInputFilter(TIM_TypeDef *timx, uint32_t break_input, uint32_t break_filter)
{
  MODIFY_REG(timx->BDTR, LL_TIM_MASK_TAB_BKxF[break_input], break_filter);
}

/**
  * @brief  Get the digital filter of a break input.
  * @rmtoll
  *  BDTR         BKF     LL_TIM_GetBreakInputFilter \n
  *  BDTR         BK2F    LL_TIM_GetBreakInputFilter
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @retval  Returned value can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1     or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N2  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N4  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV1_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N6  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV2_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N6  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV4_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N6  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV8_N8  or @arg @ref LL_TIM_BREAK2_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N5 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N6 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV16_N8 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N5 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N6 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_BREAK_FILTER_FDIV32_N8 or @arg @ref LL_TIM_BREAK2_FILTER_FDIV32_N8
  */
__STATIC_INLINE uint32_t LL_TIM_GetBreakInputFilter(const TIM_TypeDef *timx, uint32_t break_input)
{
  return (uint32_t)(READ_BIT(timx->BDTR, LL_TIM_MASK_TAB_BKxF[break_input]));
}

/**
  * @brief  Set the mode of a break input.
  * @rmtoll
  *  BDTR         BKBID     LL_TIM_SetBreakInputAFMode \n
  *  BDTR         BK2BID    LL_TIM_SetBreakInputAFMode
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  break_afmode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_AFMODE_INPUT         or @arg @ref LL_TIM_BREAK2_AFMODE_INPUT
  *         @arg @ref LL_TIM_BREAK_AFMODE_BIDIRECTIONAL or @arg @ref LL_TIM_BREAK2_AFMODE_BIDIRECTIONAL
  */
__STATIC_INLINE void LL_TIM_SetBreakInputAFMode(TIM_TypeDef *timx, uint32_t break_input, uint32_t break_afmode)
{
  MODIFY_REG(timx->BDTR, LL_TIM_MASK_TAB_BKxBID[break_input], break_afmode);
}

/**
  * @brief  Get the mode of a break input.
  * @rmtoll
  *  BDTR         BKBID     LL_TIM_SetBreakInputAFMode \n
  *  BDTR         BK2BID    LL_TIM_SetBreakInputAFMode
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @retval  Returned value can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_AFMODE_INPUT         or @arg @ref LL_TIM_BREAK2_AFMODE_INPUT
  *         @arg @ref LL_TIM_BREAK_AFMODE_BIDIRECTIONAL or @arg @ref LL_TIM_BREAK2_AFMODE_BIDIRECTIONAL
  */
__STATIC_INLINE uint32_t LL_TIM_GetBreakInputAFMode(const TIM_TypeDef *timx, uint32_t break_input)
{
  return (uint32_t)(READ_BIT(timx->BDTR, LL_TIM_MASK_TAB_BKxBID[break_input]));
}

/**
  * @brief  Enable the signals connected to the designated timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(timx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll
  *  AF1          BKINE         LL_TIM_EnableBreakInputSource \n
  *  AF1          BKCMP1E       LL_TIM_EnableBreakInputSource \n
  *  AF1          BKCMP2E       LL_TIM_EnableBreakInputSource \n
  *  AF1          BKDF1BK0E     LL_TIM_EnableBreakInputSource \n
  *  AF2          BK2INE        LL_TIM_EnableBreakInputSource \n
  *  AF2          BK2CMP1E      LL_TIM_EnableBreakInputSource \n
  *  AF2          BK2CMP2E      LL_TIM_EnableBreakInputSource \n
  *  AF2          BK2DF1BK1E    LL_TIM_EnableBreakInputSource
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  source This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_BKIN_SOURCE_GPIO
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP2 (*)
  * @endif
  *         @arg @ref LL_TIM_BKIN_SOURCE_MDF1
  *
  *         (*)  Value not defined in all devices.
  */
__STATIC_INLINE void LL_TIM_EnableBreakInputSource(TIM_TypeDef *timx, uint32_t break_input, uint32_t source)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->AF1) + (break_input << 2)));
  SET_BIT(*pReg, source);
}

/**
  * @brief  Disable the signals connected to the designated timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(timx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll
  *  AF1          BKINE         LL_TIM_DisableBreakInputSource \n
  *  AF1          BKCMP1E       LL_TIM_DisableBreakInputSource \n
  *  AF1          BKCMP2E       LL_TIM_DisableBreakInputSource \n
  *  AF1          BKDF1BK0E     LL_TIM_DisableBreakInputSource \n
  *  AF2          BK2INE        LL_TIM_DisableBreakInputSource \n
  *  AF2          BK2CMP1E      LL_TIM_DisableBreakInputSource \n
  *  AF2          BK2CMP2E      LL_TIM_DisableBreakInputSource \n
  *  AF2          BK2DF1BK1E    LL_TIM_DisableBreakInputSource
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  source This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_BKIN_SOURCE_GPIO
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP2 (*)
  * @endif
  *         @arg @ref LL_TIM_BKIN_SOURCE_MDF1
  *
  *         (*)  Value not defined in all devices.
  */
__STATIC_INLINE void LL_TIM_DisableBreakInputSource(TIM_TypeDef *timx, uint32_t break_input, uint32_t source)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->AF1) + (break_input << 2)));
  CLEAR_BIT(*pReg, source);
}

/**
  * @brief  Indicates whether a break input source is enabled or not.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(timx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll
  *  AF1          BKINE         LL_TIM_IsEnabledBreakInputSource \n
  *  AF1          BKCMP1E       LL_TIM_IsEnabledBreakInputSource \n
  *  AF1          BKCMP2E       LL_TIM_IsEnabledBreakInputSource \n
  *  AF1          BKDF1BK0E     LL_TIM_IsEnabledBreakInputSource \n
  *  AF2          BK2INE        LL_TIM_IsEnabledBreakInputSource \n
  *  AF2          BK2CMP1E      LL_TIM_IsEnabledBreakInputSource \n
  *  AF2          BK2CMP2E      LL_TIM_IsEnabledBreakInputSource \n
  *  AF2          BK2DF1BK1E    LL_TIM_IsEnabledBreakInputSource
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  source This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_BKIN_SOURCE_GPIO
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP2 (*)
  * @endif
  *         @arg @ref LL_TIM_BKIN_SOURCE_MDF1
  *
  *         (*)  Value not defined in all devices.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledBreakInputSource(const TIM_TypeDef *timx, uint32_t break_input,
                                                          uint32_t source)
{
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->AF1) + (break_input << 2)));
  return ((READ_BIT(*pReg, source) == (source)) ? 1UL : 0UL);
}

/**
  * @brief  Set the polarity of the break signal for the timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(timx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll
  *  AF1          BKINP         LL_TIM_SetBreakInputSourcePolarity \n
  *  AF1          BKCMP1P       LL_TIM_SetBreakInputSourcePolarity \n
  *  AF1          BKCMP2P       LL_TIM_SetBreakInputSourcePolarity \n
  *  AF2          BK2INP        LL_TIM_SetBreakInputSourcePolarity \n
  *  AF2          BK2CMP1P      LL_TIM_SetBreakInputSourcePolarity \n
  *  AF2          BK2CMP2P      LL_TIM_SetBreakInputSourcePolarity
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BKIN_SOURCE_GPIO
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP2 (*)
  * @endif
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_SRC_NONINVERTED
  *         @arg @ref LL_TIM_BREAK_INPUT_SRC_INVERTED
  *
  *         (*)  Value not defined in all devices. \n
  *
  */
__STATIC_INLINE void LL_TIM_SetBreakInputSourcePolarity(TIM_TypeDef *timx, uint32_t break_input, uint32_t source,
                                                        uint32_t polarity)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->AF1) + (break_input << 2)));
  MODIFY_REG(*pReg, (TIM1_AF1_BKINP << LL_TIM_TIM_POSITION_BRK_SOURCE(source)),
             (polarity << LL_TIM_TIM_POSITION_BRK_SOURCE(source)));
}

/**
  * @brief  Get the polarity of the break signal for the timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(timx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll
  *  AF1          BKINP         LL_TIM_GetBreakInputSourcePolarity \n
  *  AF1          BKCMP1P       LL_TIM_GetBreakInputSourcePolarity \n
  *  AF1          BKCMP2P       LL_TIM_GetBreakInputSourcePolarity \n
  *  AF2          BK2INP        LL_TIM_GetBreakInputSourcePolarity \n
  *  AF2          BK2CMP1P      LL_TIM_GetBreakInputSourcePolarity \n
  *  AF2          BK2CMP2P      LL_TIM_GetBreakInputSourcePolarity
  * @param  timx Timer instance
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_1
  *         @arg @ref LL_TIM_BREAK_INPUT_2
  * @param  source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BKIN_SOURCE_GPIO
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_BKIN_SOURCE_COMP2 (*)
  * @endif
  *
  *         (*)  Value not defined in all devices. \n
  *
  * @retval  Returned value can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_INPUT_SRC_NONINVERTED
  *         @arg @ref LL_TIM_BREAK_INPUT_SRC_INVERTED
  */
__STATIC_INLINE uint32_t LL_TIM_GetBreakInputSourcePolarity(const TIM_TypeDef *timx,
                                                            uint32_t break_input,
                                                            uint32_t source)
{
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&timx->AF1) + (break_input << 2)));
  uint32_t bitfield = TIM1_AF1_BKINP << LL_TIM_TIM_POSITION_BRK_SOURCE(source);
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? \
          LL_TIM_BREAK_INPUT_SRC_INVERTED : \
          LL_TIM_BREAK_INPUT_SRC_NONINVERTED);
}

/**
  * @brief  Enable asymmetrical deadtime.
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides asymmetrical deadtime.
  * @rmtoll
  *  DTR2          DTAE          LL_TIM_EnableAsymmetricalDeadTime
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableAsymmetricalDeadTime(TIM_TypeDef *timx)
{
  SET_BIT(timx->DTR2, TIM_DTR2_DTAE);
}

/**
  * @brief  Disable asymmetrical dead-time.
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides asymmetrical deadtime.
  * @rmtoll
  *  DTR2          DTAE          LL_TIM_DisableAsymmetricalDeadTime
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableAsymmetricalDeadTime(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DTR2, TIM_DTR2_DTAE);
}

/**
  * @brief  Indicates whether asymmetrical deadtime is activated.
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides asymmetrical deadtime.
  * @rmtoll
  *  DTR2          DTAE          LL_TIM_IsEnabledAsymmetricalDeadTime
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledAsymmetricalDeadTime(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DTR2, TIM_DTR2_DTAE) == (TIM_DTR2_DTAE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the falling edge dead-time delay (delay inserted between the falling edge of the OCxREF signal and the
  *         rising edge of OCxN signals).
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(timx) can be used to check whether or not
  *       asymmetrical dead-time insertion feature is supported by a timer instance.
  * @note Helper macro @ref LL_TIM_CALC_DEADTIME can be used to calculate the deadtime parameter
  * @note This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been programmed
  *       (LOCK bits in TIMx_BDTR register).
  * @rmtoll
  *  DTR2         DTGF           LL_TIM_SetFallingDeadTime
  * @param  timx Timer instance
  * @param  deadtime between Min_Data=0 and Max_Data=255
  */
__STATIC_INLINE void LL_TIM_SetFallingDeadTime(TIM_TypeDef *timx, uint32_t deadtime)
{
  MODIFY_REG(timx->DTR2, TIM_DTR2_DTGF, deadtime);
}

/**
  * @brief  Get the falling edge dead-time delay (delay inserted between the falling edge of the OCxREF signal and
  *         the rising edge of OCxN signals).
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(timx) can be used to check whether or not
  *       asymmetrical dead-time insertion feature is supported by a timer instance.
  * @note This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been programmed
  *       (LOCK bits in TIMx_BDTR register).
  * @rmtoll
  *  DTR2          DTGF           LL_TIM_GetFallingDeadTime
  * @param  timx Timer instance
  * @retval Returned value can be between Min_Data=0 and Max_Data=255:
  */
__STATIC_INLINE uint32_t LL_TIM_GetFallingDeadTime(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->DTR2, TIM_DTR2_DTGF));
}

/**
  * @brief  Enable deadtime preload.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides deadtime preload.
  * @rmtoll
  *  DTR2          DTPE          LL_TIM_EnableDeadTimePreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDeadTimePreload(TIM_TypeDef *timx)
{
  SET_BIT(timx->DTR2, TIM_DTR2_DTPE);
}

/**
  * @brief  Disable dead-time preload.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides deadtime preload.
  * @rmtoll
  *  DTR2          DTPE          LL_TIM_DisableDeadTimePreload
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDeadTimePreload(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DTR2, TIM_DTR2_DTPE);
}

/**
  * @brief  Indicates whether deadtime preload is activated.
  * @note Macro IS_TIM_BREAK_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides deadtime preload.
  * @rmtoll
  *  DTR2          DTPE          LL_TIM_IsEnabledDeadTimePreload
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDeadTimePreload(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DTR2, TIM_DTR2_DTPE) == (TIM_DTR2_DTPE)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_DMA_Burst_Mode DMA burst mode configuration
  * @{
  */
/**
  * @brief  Configures the timer DMA burst feature.
  * @note Macro IS_TIM_DMABURST_INSTANCE(timx) can be used to check whether or
  *       not a timer instance supports the DMA burst mode.
  * @rmtoll
  *  DCR          DBSS          LL_TIM_ConfigDMABurst \n
  *  DCR          DBL           LL_TIM_ConfigDMABurst \n
  *  DCR          DBA           LL_TIM_ConfigDMABurst
  * @param  timx Timer instance
  * @param  dmaburst_base_address This parameter can be one of the following values:
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CR1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_SMCR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_DIER
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_SR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_EGR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCMR1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCMR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCER
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CNT
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_PSC
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_ARR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_RCR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR3
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR4
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_BDTR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR5
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR6
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCMR3
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_DTR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_ECR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_TISEL
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_AF1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_AF2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_OR1
  * @param  dmaburst_length This parameter can be one of the following values:
  *         @arg @ref LL_TIM_DMABURST_LENGTH_1TRANSFER
  *         @arg @ref LL_TIM_DMABURST_LENGTH_2TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_3TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_4TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_5TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_6TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_7TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_8TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_9TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_10TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_11TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_12TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_13TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_14TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_15TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_16TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_17TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_18TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_19TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_20TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_21TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_22TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_23TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_24TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_25TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_26TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_27TRANSFERS
  * @param  dmaburst_source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_DMABURST_UPD
  *         @arg @ref LL_TIM_DMABURST_CC1
  *         @arg @ref LL_TIM_DMABURST_CC2  (*)
  *         @arg @ref LL_TIM_DMABURST_CC3  (*)
  *         @arg @ref LL_TIM_DMABURST_CC4  (*)
  *         @arg @ref LL_TIM_DMABURST_COM  (*)
  *         @arg @ref LL_TIM_DMABURST_TRGI (*)
  *
  *         (*)  Value not defined for all timer instances. \n
  */
__STATIC_INLINE void LL_TIM_ConfigDMABurst(TIM_TypeDef *timx, uint32_t dmaburst_base_address, uint32_t dmaburst_length,
                                           uint32_t dmaburst_source)
{
  MODIFY_REG(timx->DCR, (TIM_DCR_DBL | TIM_DCR_DBA | TIM_DCR_DBSS),
             (dmaburst_base_address | dmaburst_length | dmaburst_source));
}

/**
  * @brief  Get the timer DMA burst configuration.
  * @note Macro IS_TIM_DMABURST_INSTANCE(timx) can be used to check whether or
  *       not a timer instance supports the DMA burst mode.
  * @rmtoll
  *  DCR          DBSS          LL_TIM_GetConfigDMABurst \n
  *  DCR          DBL           LL_TIM_GetConfigDMABurst \n
  *  DCR          DBA           LL_TIM_GetConfigDMABurst
  * @param  timx Timer instance
  * @param  p_dmaburst_base_address Pointer to a storage for DMA burst base address. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CR1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_SMCR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_DIER
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_SR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_EGR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCMR1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCMR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCER
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CNT
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_PSC
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_ARR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_RCR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR3
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR4
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_BDTR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR5
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCR6
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_CCMR3
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_DTR2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_ECR
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_TISEL
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_AF1
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_AF2
  *         @arg @ref LL_TIM_DMABURST_BASEADDR_OR1
  * @param  p_dmaburst_length Pointer to a storage for DMA burst length. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_DMABURST_LENGTH_1TRANSFER
  *         @arg @ref LL_TIM_DMABURST_LENGTH_2TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_3TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_4TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_5TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_6TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_7TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_8TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_9TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_10TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_11TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_12TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_13TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_14TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_15TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_16TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_17TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_18TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_19TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_20TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_21TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_22TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_23TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_24TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_25TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_26TRANSFERS
  *         @arg @ref LL_TIM_DMABURST_LENGTH_27TRANSFERS
  * @param  p_dmaburst_source Pointer to a storage for DMA burst source. \n
  *         The value can be one of the following values: \n
  *         @arg @ref LL_TIM_DMABURST_UPD
  *         @arg @ref LL_TIM_DMABURST_CC1
  *         @arg @ref LL_TIM_DMABURST_CC2  (*)
  *         @arg @ref LL_TIM_DMABURST_CC3  (*)
  *         @arg @ref LL_TIM_DMABURST_CC4  (*)
  *         @arg @ref LL_TIM_DMABURST_COM  (*)
  *         @arg @ref LL_TIM_DMABURST_TRGI (*)
  *
  *         (*)  Value not defined for all timer instances. \n
  */
__STATIC_INLINE void LL_TIM_GetConfigDMABurst(TIM_TypeDef *timx, uint32_t *p_dmaburst_base_address,
                                              uint32_t *p_dmaburst_length, uint32_t *p_dmaburst_source)
{
  const __IO uint32_t dcr = READ_REG(timx->DCR);

  *p_dmaburst_base_address = (dcr & TIM_DCR_DBA);
  *p_dmaburst_length = (dcr & TIM_DCR_DBL);
  *p_dmaburst_source = (dcr & TIM_DCR_DBSS);
}

/**
  * @brief  Get the DMA burst source.
  * @note Macro IS_TIM_DMABURST_INSTANCE(timx) can be used to check whether or
  *       not a timer instance supports the DMA burst mode.
  * @rmtoll
  *  DCR          DBSS           LL_TIM_GetDMABurstSource
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_DMABURST_UPD
  *         @arg @ref LL_TIM_DMABURST_CC1
  *         @arg @ref LL_TIM_DMABURST_CC2  (*)
  *         @arg @ref LL_TIM_DMABURST_CC3  (*)
  *         @arg @ref LL_TIM_DMABURST_CC4  (*)
  *         @arg @ref LL_TIM_DMABURST_COM  (*)
  *         @arg @ref LL_TIM_DMABURST_TRGI (*)
  *
  *         (*)  Value not defined for all timer instances. \n
  */
__STATIC_INLINE uint32_t LL_TIM_GetDMABurstSource(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->DCR, TIM_DCR_DBSS));
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_Encoder Encoder configuration
  * @{
  */

/**
  * @brief  Enable encoder index.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR         IE           LL_TIM_EnableEncoderIndex
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableEncoderIndex(TIM_TypeDef *timx)
{
  SET_BIT(timx->ECR, TIM_ECR_IE);
}

/**
  * @brief  Disable encoder index.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR         IE           LL_TIM_DisableEncoderIndex
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableEncoderIndex(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->ECR, TIM_ECR_IE);
}

/**
  * @brief  Indicate whether encoder index is enabled.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR         IE           LL_TIM_IsEnabledEncoderIndex
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledEncoderIndex(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->ECR, TIM_ECR_IE) == (TIM_ECR_IE)) ? 1U : 0U);
}

/**
  * @brief  Set index direction
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IDIR           LL_TIM_SetIndexDirection
  * @param  timx Timer instance
  * @param  index_direction This parameter can be one of the following values:
  *         @arg @ref LL_TIM_INDEX_UP_DOWN
  *         @arg @ref LL_TIM_INDEX_UP
  *         @arg @ref LL_TIM_INDEX_DOWN
  */
__STATIC_INLINE void LL_TIM_SetIndexDirection(TIM_TypeDef *timx, uint32_t index_direction)
{
  MODIFY_REG(timx->ECR, TIM_ECR_IDIR, index_direction);
}

/**
  * @brief  Get actual index direction
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IDIR           LL_TIM_GetIndexDirection
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_INDEX_UP_DOWN
  *         @arg @ref LL_TIM_INDEX_UP
  *         @arg @ref LL_TIM_INDEX_DOWN
  */
__STATIC_INLINE uint32_t LL_TIM_GetIndexDirection(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->ECR, TIM_ECR_IDIR));
}

/**
  * @brief  Set index blanking
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IBLK           LL_TIM_SetIndexBlanking
  * @param  timx Timer instance
  * @param  index_blanking This parameter can be one of the following values:
  *         @arg @ref LL_TIM_INDEX_BLANK_ALWAYS
  *         @arg @ref LL_TIM_INDEX_BLANK_TI3
  *         @arg @ref LL_TIM_INDEX_BLANK_TI4
  */
__STATIC_INLINE void LL_TIM_SetIndexBlanking(TIM_TypeDef *timx, uint32_t index_blanking)
{
  MODIFY_REG(timx->ECR, TIM_ECR_IBLK, index_blanking);
}

/**
  * @brief  Get actual index blanking
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IBLK           LL_TIM_GetIndexBlanking
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_INDEX_BLANK_ALWAYS
  *         @arg @ref LL_TIM_INDEX_BLANK_TI3
  *         @arg @ref LL_TIM_INDEX_BLANK_TI4
  */
__STATIC_INLINE uint32_t LL_TIM_GetIndexBlanking(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->ECR, TIM_ECR_IBLK));
}


/**
  * @brief  Enable first index.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          FIDX          LL_TIM_EnableFirstIndex
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableFirstIndex(TIM_TypeDef *timx)
{
  SET_BIT(timx->ECR, TIM_ECR_FIDX);
}

/**
  * @brief  Disable first index.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          FIDX          LL_TIM_DisableFirstIndex
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableFirstIndex(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->ECR, TIM_ECR_FIDX);
}

/**
  * @brief  Indicates whether first index is enabled.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          FIDX          LL_TIM_IsEnabledFirstIndex
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledFirstIndex(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->ECR, TIM_ECR_FIDX) == (TIM_ECR_FIDX)) ? 1UL : 0UL);
}

/**
  * @brief  Set index positioning
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IPOS           LL_TIM_SetIndexPositionning
  * @param  timx Timer instance
  * @param  index_positioning This parameter can be one of the following values:
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN_DOWN
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN_UP
  *         @arg @ref LL_TIM_INDEX_POSITION_UP_DOWN
  *         @arg @ref LL_TIM_INDEX_POSITION_UP_UP
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN
  *         @arg @ref LL_TIM_INDEX_POSITION_UP
  */
__STATIC_INLINE void LL_TIM_SetIndexPositionning(TIM_TypeDef *timx, uint32_t index_positioning)
{
  MODIFY_REG(timx->ECR, TIM_ECR_IPOS, index_positioning);
}

/**
  * @brief  Get actual index positioning
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IPOS           LL_TIM_GetIndexPositionning
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN_DOWN
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN_UP
  *         @arg @ref LL_TIM_INDEX_POSITION_UP_DOWN
  *         @arg @ref LL_TIM_INDEX_POSITION_UP_UP
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN
  *         @arg @ref LL_TIM_INDEX_POSITION_UP
  */
__STATIC_INLINE uint32_t LL_TIM_GetIndexPositionning(const TIM_TypeDef *timx)
{
  return (uint32_t)(READ_BIT(timx->ECR, TIM_ECR_IPOS));
}

/**
  * @brief  Configure encoder index.
  * @note Macro IS_TIM_INDEX_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll
  *  ECR          IDIR          LL_TIM_ConfigEncoderIndex \n
  *  ECR          IBLK          LL_TIM_ConfigEncoderIndex \n
  *  ECR          FIDX          LL_TIM_ConfigEncoderIndex \n
  *  ECR          IPOS          LL_TIM_ConfigEncoderIndex
  * @param  timx Timer instance
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_TIM_INDEX_UP or @ref LL_TIM_INDEX_DOWN or @ref LL_TIM_INDEX_UP_DOWN
  *         @arg @ref LL_TIM_INDEX_BLANK_ALWAYS or @ref LL_TIM_INDEX_BLANK_TI3 or @ref LL_TIM_INDEX_BLANK_TI4
  *         @arg @ref LL_TIM_INDEX_ALL or @ref LL_TIM_INDEX_FIRST_ONLY
  *         @arg @ref LL_TIM_INDEX_POSITION_DOWN_DOWN or ... or @ref LL_TIM_INDEX_POSITION_UP
  */
__STATIC_INLINE void LL_TIM_ConfigEncoderIndex(TIM_TypeDef *timx, uint32_t configuration)
{
  MODIFY_REG(timx->ECR, TIM_ECR_IDIR | TIM_ECR_IBLK | TIM_ECR_FIDX | TIM_ECR_IPOS, configuration);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Timer_Inputs_Remapping Timer input remapping
  * @{
  */
/**
  * @brief  Remap TIM inputs (input channel, internal/external triggers).
  * @note Macro IS_TIM_REMAP_INSTANCE(timx) can be used to check whether or not
  *       a some timer inputs can be remapped.
  * @rmtoll
  *  TISEL    TI1SEL      LL_TIM_SetRemap \n
  *  TISEL    TI2SEL      LL_TIM_SetRemap \n
  *  TISEL    TI3SEL      LL_TIM_SetRemap \n
  *  TISEL    TI4SEL      LL_TIM_SetRemap
  * @param  timx Timer instance
  * @param  remap Remap param depends on the timx. Description available only
  *         in CHM version of the User Manual (not in .pdf).
  *         Otherwise see Reference Manual description of TISEL registers.
  *
  *         Below description summarizes "Timer Instance" and "Remap" param combinations:
  *
  *         TIM1: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI1_RMP_GPIO:                TIM1 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM1_TI1_RMP_COMP1:               TIM1 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM1_TI1_RMP_COMP2:               TIM1 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI2_RMP_GPIO:                TIM1 TI2 is connected to GPIO
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI3_RMP_GPIO:                TIM1 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI4_RMP_GPIO:                TIM1 TI4 is connected to GPIO
  *
  *         TIM2: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI1_RMP_GPIO:                TIM2 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM2_TI1_RMP_COMP1:               TIM2 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM2_TI1_RMP_COMP2:               TIM2 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI2_RMP_GPIO:                TIM2 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM2_TI2_RMP_COMP1:               TIM2 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM2_TI2_RMP_COMP2:               TIM2 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI3_RMP_GPIO:                TIM2 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI4_RMP_GPIO:                TIM2 TI4 is connected to GPIO
  *            @arg LL_TIM_TIM2_TI4_RMP_COMP1:               TIM2 TI4 is connected to COMP1 output
  *            @arg LL_TIM_TIM2_TI4_RMP_COMP2:               TIM2 TI4 is connected to COMP2 output (*)
  *
  *         TIM3: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI1_RMP_GPIO:                TIM3 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM3_TI1_RMP_COMP1:               TIM3 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM3_TI1_RMP_COMP2:               TIM3 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI2_RMP_GPIO:                TIM3 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM3_TI2_RMP_COMP1:               TIM3 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM3_TI2_RMP_COMP2:               TIM3 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI3_RMP_GPIO:                TIM3 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI4_RMP_GPIO:                TIM3 TI4 is connected to GPIO
  *
  *         TIM4: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI1_RMP_GPIO:                TIM4 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM4_TI1_RMP_COMP1:               TIM4 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM4_TI1_RMP_COMP2:               TIM4 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI2_RMP_GPIO:                TIM4 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM4_TI2_RMP_COMP1:               TIM4 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM4_TI2_RMP_COMP2:               TIM4 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI3_RMP_GPIO:                TIM4 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI4_RMP_GPIO:                TIM4 TI4 is connected to GPIO
  *
  *         TIM5: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI1_RMP_GPIO:                TIM5 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM5_TI1_RMP_LSI:                 TIM5 TI1 is connected to LSI
  *            @arg LL_TIM_TIM5_TI1_RMP_LSE:                 TIM5 TI1 is connected to LSE
  *            @arg LL_TIM_TIM5_TI1_RMP_RTC_WKUP:            TIM5 TI1 is connected to RTC Wakeup
  *            @arg LL_TIM_TIM5_TI1_RMP_COMP1:               TIM5 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM5_TI1_RMP_COMP2:               TIM5 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI2_RMP_GPIO:                TIM5 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM5_TI2_RMP_COMP1:               TIM5 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM5_TI2_RMP_COMP2:               TIM5 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI3_RMP_GPIO:                TIM5 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI4_RMP_GPIO:                TIM5 TI4 is connected to GPIO
  *
  *         TIM8: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI1_RMP_GPIO:                TIM8 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM8_TI1_RMP_COMP1:               TIM8 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM8_TI1_RMP_COMP2:               TIM8 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI2_RMP_GPIO:                TIM8 TI2 is connected to GPIO
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI3_RMP_GPIO:                TIM8 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI4_RMP_GPIO:                TIM8 TI4 is connected to GPIO
  *
  *         TIM15: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM15_TI1_RMP_GPIO:               TIM15 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM15_TI1_RMP_LSE:                TIM15 TI1 is connected to LSE
  *            @arg LL_TIM_TIM15_TI1_RMP_COMP1:              TIM15 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM15_TI1_RMP_COMP2:              TIM15 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM15_TI2_RMP_GPIO:               TIM15 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM15_TI2_RMP_COMP2:              TIM15 TI2 is connected to COMP2 output (*)
  *
  *         TIM16: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM16_TI1_RMP_GPIO:               TIM16 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM16_TI1_RMP_MCO:                TIM16 TI1 is connected to MCO
  *            @arg LL_TIM_TIM16_TI1_RMP_HSE_DIV32:          TIM16 TI1 is connected to HSE/32
  *            @arg LL_TIM_TIM16_TI1_RMP_RTC_WKUP:           TIM16 TI1 is connected to RTC Wakeup
  *            @arg LL_TIM_TIM16_TI1_RMP_LSE:                TIM16 TI1 is connected to LSE
  *            @arg LL_TIM_TIM16_TI1_RMP_LSI:                TIM16 TI1 is connected to LSI
  *            @arg LL_TIM_TIM16_TI1_RMP_MSIS_DIV1024:       TIM16 TI1 is connected to MSIS/1024
  *            @arg LL_TIM_TIM16_TI1_RMP_MSIS_DIV4:          TIM16 TI1 is connected to MSIS/4
  *            @arg LL_TIM_TIM16_TI1_RMP_HSI_DIV256:         TIM16 TI1 is connected to HSI/256
  *
  *         TIM17: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM17_TI1_RMP_GPIO:               TIM17 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM17_TI1_RMP_MCO:                TIM17 TI1 is connected to MCO
  *            @arg LL_TIM_TIM17_TI1_RMP_HSE_DIV32:          TIM17 TI1 is connected to HSE/32
  *            @arg LL_TIM_TIM17_TI1_RMP_RTC_WKUP:           TIM17 TI1 is connected to RTC Wakeup
  *            @arg LL_TIM_TIM17_TI1_RMP_LSE:                TIM17 TI1 is connected to LSE
  *            @arg LL_TIM_TIM17_TI1_RMP_LSI:                TIM17 TI1 is connected to LSI
  *            @arg LL_TIM_TIM17_TI1_RMP_MSIS_DIV1024:       TIM17 TI1 is connected to MSIS/1024
  *            @arg LL_TIM_TIM17_TI1_RMP_MSIS_DIV4:          TIM17 TI1 is connected to MSIS/4
  *            @arg LL_TIM_TIM17_TI1_RMP_HSI_DIV256:         TIM17 TI1 is connected to HSI/256
  *
  *         (*)  Value not defined in all devices. \n
  */
__STATIC_INLINE void LL_TIM_SetRemap(TIM_TypeDef *timx, uint32_t remap)
{
  MODIFY_REG(timx->TISEL, (TIM_TISEL_TI1SEL | TIM_TISEL_TI2SEL | TIM_TISEL_TI3SEL | TIM_TISEL_TI4SEL), remap);
}

/**
  * @brief  Get TIM input (input channel, internal/external triggers).
  * @note Macro IS_TIM_REMAP_INSTANCE(timx) can be used to check whether or not
  *       a some timer inputs can be remapped.
  * @rmtoll
  *  TISEL    TI1SEL      LL_TIM_GetRemap \n
  *  TISEL    TI2SEL      LL_TIM_GetRemap \n
  *  TISEL    TI3SEL      LL_TIM_GetRemap \n
  *  TISEL    TI4SEL      LL_TIM_GetRemap
  * @param  timx Timer instance
  * @param  channel This parameter can be one of the following values:
  *           @arg @ref LL_TIM_CHANNEL_CH1
  *           @arg @ref LL_TIM_CHANNEL_CH2
  * @retval  Returned value can be one of the following values:
  *
  *         TIM1: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI1_RMP_GPIO:                TIM1 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM1_TI1_RMP_COMP1:               TIM1 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM1_TI1_RMP_COMP2:               TIM1 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI2_RMP_GPIO:                TIM1 TI2 is connected to GPIO
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI3_RMP_GPIO:                TIM1 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM1_TI4_RMP_GPIO:                TIM1 TI4 is connected to GPIO
  *
  *         TIM2: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI1_RMP_GPIO:                TIM2 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM2_TI1_RMP_COMP1:               TIM2 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM2_TI1_RMP_COMP2:               TIM2 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI2_RMP_GPIO:                TIM2 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM2_TI2_RMP_COMP1:               TIM2 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM2_TI2_RMP_COMP2:               TIM2 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI3_RMP_GPIO:                TIM2 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM2_TI4_RMP_GPIO:                TIM2 TI4 is connected to GPIO
  *            @arg LL_TIM_TIM2_TI4_RMP_COMP1:               TIM2 TI4 is connected to COMP1 output
  *            @arg LL_TIM_TIM2_TI4_RMP_COMP2:               TIM2 TI4 is connected to COMP2 output (*)
  *
  *         TIM3: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI1_RMP_GPIO:                TIM3 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM3_TI1_RMP_COMP1:               TIM3 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM3_TI1_RMP_COMP2:               TIM3 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI2_RMP_GPIO:                TIM3 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM3_TI2_RMP_COMP1:               TIM3 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM3_TI2_RMP_COMP2:               TIM3 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI3_RMP_GPIO:                TIM3 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM3_TI4_RMP_GPIO:                TIM3 TI4 is connected to GPIO
  *
  *         TIM4: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI1_RMP_GPIO:                TIM4 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM4_TI1_RMP_COMP1:               TIM4 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM4_TI1_RMP_COMP2:               TIM4 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI2_RMP_GPIO:                TIM4 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM4_TI2_RMP_COMP1:               TIM4 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM4_TI2_RMP_COMP2:               TIM4 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI3_RMP_GPIO:                TIM4 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM4_TI4_RMP_GPIO:                TIM4 TI4 is connected to GPIO
  *
  *         TIM5: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI1_RMP_GPIO:                TIM5 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM5_TI1_RMP_LSI:                 TIM5 TI1 is connected to LSI
  *            @arg LL_TIM_TIM5_TI1_RMP_LSE:                 TIM5 TI1 is connected to LSE
  *            @arg LL_TIM_TIM5_TI1_RMP_RTC_WKUP:            TIM5 TI1 is connected to RTC Wakeup
  *            @arg LL_TIM_TIM5_TI1_RMP_COMP1:               TIM5 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM5_TI1_RMP_COMP2:               TIM5 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI2_RMP_GPIO:                TIM5 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM5_TI2_RMP_COMP1:               TIM5 TI2 is connected to COMP1 output
  *            @arg LL_TIM_TIM5_TI2_RMP_COMP2:               TIM5 TI2 is connected to COMP2 output (*)
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI3_RMP_GPIO:                TIM5 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM5_TI4_RMP_GPIO:                TIM5 TI4 is connected to GPIO
  *
  *         TIM8: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI1_RMP_GPIO:                TIM8 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM8_TI1_RMP_COMP1:               TIM8 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM8_TI1_RMP_COMP2:               TIM8 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI2_RMP_GPIO:                TIM8 TI2 is connected to GPIO
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI3_RMP_GPIO:                TIM8 TI3 is connected to GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg LL_TIM_TIM8_TI4_RMP_GPIO:                TIM8 TI4 is connected to GPIO
  *
  *         TIM15: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM15_TI1_RMP_GPIO:               TIM15 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM15_TI1_RMP_LSE:                TIM15 TI1 is connected to LSE
  *            @arg LL_TIM_TIM15_TI1_RMP_COMP1:              TIM15 TI1 is connected to COMP1 output
  *            @arg LL_TIM_TIM15_TI1_RMP_COMP2:              TIM15 TI1 is connected to COMP2 output (*)
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg LL_TIM_TIM15_TI2_RMP_GPIO:               TIM15 TI2 is connected to GPIO
  *            @arg LL_TIM_TIM15_TI2_RMP_COMP2:              TIM15 TI2 is connected to COMP2 output (*)
  *
  *         TIM16: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM16_TI1_RMP_GPIO:               TIM16 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM16_TI1_RMP_MCO:                TIM16 TI1 is connected to MCO
  *            @arg LL_TIM_TIM16_TI1_RMP_HSE_DIV32:          TIM16 TI1 is connected to HSE/32
  *            @arg LL_TIM_TIM16_TI1_RMP_RTC_WKUP:           TIM16 TI1 is connected to RTC Wakeup
  *            @arg LL_TIM_TIM16_TI1_RMP_LSE:                TIM16 TI1 is connected to LSE
  *            @arg LL_TIM_TIM16_TI1_RMP_LSI:                TIM16 TI1 is connected to LSI
  *            @arg LL_TIM_TIM16_TI1_RMP_MSIS_DIV1024:       TIM16 TI1 is connected to MSIS/1024
  *            @arg LL_TIM_TIM16_TI1_RMP_MSIS_DIV4:          TIM16 TI1 is connected to MSIS/4
  *            @arg LL_TIM_TIM16_TI1_RMP_HSI_DIV256:         TIM16 TI1 is connected to HSI/256
  *
  *         TIM17: one of the following values:
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg LL_TIM_TIM17_TI1_RMP_GPIO:               TIM17 TI1 is connected to GPIO
  *            @arg LL_TIM_TIM17_TI1_RMP_MCO:                TIM17 TI1 is connected to MCO
  *            @arg LL_TIM_TIM17_TI1_RMP_HSE_DIV32:          TIM17 TI1 is connected to HSE/32
  *            @arg LL_TIM_TIM17_TI1_RMP_RTC_WKUP:           TIM17 TI1 is connected to RTC Wakeup
  *            @arg LL_TIM_TIM17_TI1_RMP_LSE:                TIM17 TI1 is connected to LSE
  *            @arg LL_TIM_TIM17_TI1_RMP_LSI:                TIM17 TI1 is connected to LSI
  *            @arg LL_TIM_TIM17_TI1_RMP_MSIS_DIV1024:       TIM17 TI1 is connected to MSIS/1024
  *            @arg LL_TIM_TIM17_TI1_RMP_MSIS_DIV4:          TIM17 TI1 is connected to MSIS/4
  *            @arg LL_TIM_TIM17_TI1_RMP_HSI_DIV256:         TIM17 TI1 is connected to HSI/256
  *
  *         (*)  Value not defined in all devices. \n
  */
__STATIC_INLINE uint32_t LL_TIM_GetRemap(const TIM_TypeDef *timx, uint32_t channel)
{
  uint32_t ichannel = LL_TIM_TIM_GET_CHANNEL_INDEX(channel);
  return ((ichannel < 7U) ? ((uint32_t)(READ_BIT(timx->TISEL, TIM_TISEL_TI1SEL << (ichannel << 2)))) : 0U);
}

/**
  * @brief  Enable request for HSE/32 clock used for TISEL remap.
  * @note Only TIM16 and TIM17 support HSE/32 remap
  * @note  The Cut1.x contains a limitation when using HSE/32 as input capture for TIM16
  * @note  Bug ID 56: On TIM16, the HSE/32 input capture requires the set of HSE32EN bit of TIM17 Option Register
  * @rmtoll
  *  OR1         HSE32EN           LL_TIM_EnableHSE32
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableHSE32(TIM_TypeDef *timx)
{
  SET_BIT(timx->OR1, TIM_OR1_HSE32EN);
}

/**
  * @brief  Disable request for HSE/32 clock used for TISEL remap.
  * @note Only TIM16 and TIM17 support HSE/32 remap
  * @rmtoll
  *  OR1         HSE32EN           LL_TIM_DisableHSE32
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableHSE32(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->OR1, TIM_OR1_HSE32EN);
}

/**
  * @brief  Indicate whether request for HSE/32 clock is enabled.
  * @note Only TIM16 and TIM17 support HSE/32 remap
  * @rmtoll
  *  OR1         HSE32EN           LL_TIM_IsEnabledHSE32
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledHSE32(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->OR1, TIM_OR1_HSE32EN) == (TIM_OR1_HSE32EN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_OCREF_Clear OCREF_Clear_Management
  * @{
  */
/**
  * @brief  Set the OCREF clear input source
  * @note The OCxREF signal of a given channel can be cleared when a high level is applied on the OCREF_CLR_INPUT
  * @note This function can only be used in Output compare and PWM modes.
  * @rmtoll
  *  SMCR          OCCS                LL_TIM_SetOCRefClearInputSource
  *  AF2           OCRSEL              LL_TIM_SetOCRefClearInputSource
  * @param  timx Timer instance
  * @param  ocrefclear_input_source This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCREF_CLR_INT_ETR
  *         @arg @ref LL_TIM_OCREF_CLR_INT_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_OCREF_CLR_INT_COMP2 (*)
  * @endif
  *
  *         (*)  Value not defined in all devices. \n
  *
  */
__STATIC_INLINE void LL_TIM_SetOCRefClearInputSource(TIM_TypeDef *timx, uint32_t ocrefclear_input_source)
{
  MODIFY_REG(timx->SMCR, TIM_SMCR_OCCS, (ocrefclear_input_source & TIM_SMCR_OCCS));
  MODIFY_REG(timx->AF2, TIM1_AF2_OCRSEL, (ocrefclear_input_source & TIM1_AF2_OCRSEL));
}

/**
  * @brief  Get the OCREF clear input source.
  * @rmtoll
  *  AF2           OCRSEL              LL_TIM_GetOCRefClearInputSource \n
  *  SMCR          OCCS                LL_TIM_GetOCRefClearInputSource
  * @param  timx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCREF_CLR_INT_ETR
  *         @arg @ref LL_TIM_OCREF_CLR_INT_COMP1
  * @if COMP2
  *         @arg @ref LL_TIM_OCREF_CLR_INT_COMP2 (*)
  * @endif
  *
  *         (*)  Value not defined in all devices. \n
  *
  */
__STATIC_INLINE uint32_t LL_TIM_GetOCRefClearInputSource(const TIM_TypeDef *timx)
{
  uint32_t src = (uint32_t)(READ_BIT(timx->SMCR, TIM_SMCR_OCCS));
  src |= (uint32_t)(READ_BIT(timx->AF2, TIM1_AF2_OCRSEL));
  return src;
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_FLAG_Management FLAG-Management
  * @{
  */
/**
  * @brief  Clear the update interrupt flag (UIF).
  * @rmtoll
  *  SR           UIF           LL_TIM_ClearFlag_UPDATE
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_UPDATE(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_UIF));
}

/**
  * @brief  Indicate whether update interrupt flag (UIF) is set (update interrupt is pending).
  * @rmtoll
  *  SR           UIF           LL_TIM_IsActiveFlag_UPDATE
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_UPDATE(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_UIF) == (TIM_SR_UIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 1 interrupt flag (CC1F).
  * @rmtoll
  *  SR           CC1IF         LL_TIM_ClearFlag_CC1
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC1(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC1IF));
}

/**
  * @brief  Indicate whether Capture/Compare 1 interrupt flag (CC1F) is set (Capture/Compare 1 interrupt is pending).
  * @rmtoll
  *  SR           CC1IF         LL_TIM_IsActiveFlag_CC1
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC1(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC1IF) == (TIM_SR_CC1IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 2 interrupt flag (CC2F).
  * @rmtoll
  *  SR           CC2IF         LL_TIM_ClearFlag_CC2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC2(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC2IF));
}

/**
  * @brief  Indicate whether Capture/Compare 2 interrupt flag (CC2F) is set (Capture/Compare 2 interrupt is pending).
  * @rmtoll
  *  SR           CC2IF         LL_TIM_IsActiveFlag_CC2
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC2(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC2IF) == (TIM_SR_CC2IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 3 interrupt flag (CC3F).
  * @rmtoll
  *  SR           CC3IF         LL_TIM_ClearFlag_CC3
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC3(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC3IF));
}

/**
  * @brief  Indicate whether Capture/Compare 3 interrupt flag (CC3F) is set (Capture/Compare 3 interrupt is pending).
  * @rmtoll
  *  SR           CC3IF         LL_TIM_IsActiveFlag_CC3
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC3(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC3IF) == (TIM_SR_CC3IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 4 interrupt flag (CC4F).
  * @rmtoll
  *  SR           CC4IF         LL_TIM_ClearFlag_CC4
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC4(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC4IF));
}

/**
  * @brief  Indicate whether Capture/Compare 4 interrupt flag (CC4F) is set (Capture/Compare 4 interrupt is pending).
  * @rmtoll
  *  SR           CC4IF         LL_TIM_IsActiveFlag_CC4
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC4(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC4IF) == (TIM_SR_CC4IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 5 interrupt flag (CC5F).
  * @rmtoll
  *  SR           CC5IF         LL_TIM_ClearFlag_CC5
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC5(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC5IF));
}

/**
  * @brief  Indicate whether Capture/Compare 5 interrupt flag (CC5F) is set (Capture/Compare 5 interrupt is pending).
  * @rmtoll
  *  SR           CC5IF         LL_TIM_IsActiveFlag_CC5
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC5(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC5IF) == (TIM_SR_CC5IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 6 interrupt flag (CC6F).
  * @rmtoll
  *  SR           CC6IF         LL_TIM_ClearFlag_CC6
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC6(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC6IF));
}

/**
  * @brief  Indicate whether Capture/Compare 6 interrupt flag (CC6F) is set (Capture/Compare 6 interrupt is pending).
  * @rmtoll
  *  SR           CC6IF         LL_TIM_IsActiveFlag_CC6
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC6(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC6IF) == (TIM_SR_CC6IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the commutation interrupt flag (COMIF).
  * @rmtoll
  *  SR           COMIF         LL_TIM_ClearFlag_COM
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_COM(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_COMIF));
}

/**
  * @brief  Indicate whether commutation interrupt flag (COMIF) is set (commutation interrupt is pending).
  * @rmtoll
  *  SR           COMIF         LL_TIM_IsActiveFlag_COM
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_COM(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_COMIF) == (TIM_SR_COMIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the trigger interrupt flag (TIF).
  * @rmtoll
  *  SR           TIF           LL_TIM_ClearFlag_TRIG
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_TRIG(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_TIF));
}

/**
  * @brief  Indicate whether trigger interrupt flag (TIF) is set (trigger interrupt is pending).
  * @rmtoll
  *  SR           TIF           LL_TIM_IsActiveFlag_TRIG
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_TRIG(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_TIF) == (TIM_SR_TIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the break interrupt flag (BIF).
  * @rmtoll
  *  SR           BIF           LL_TIM_ClearFlag_BRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_BRK(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_BIF));
}

/**
  * @brief  Indicate whether break interrupt flag (BIF) is set (break interrupt is pending).
  * @rmtoll
  *  SR           BIF           LL_TIM_IsActiveFlag_BRK
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_BRK(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_BIF) == (TIM_SR_BIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the break 2 interrupt flag (B2IF).
  * @rmtoll
  *  SR           B2IF          LL_TIM_ClearFlag_BRK2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_BRK2(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_B2IF));
}

/**
  * @brief  Indicate whether break 2 interrupt flag (B2IF) is set (break 2 interrupt is pending).
  * @rmtoll
  *  SR           B2IF          LL_TIM_IsActiveFlag_BRK2
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_BRK2(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_B2IF) == (TIM_SR_B2IF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the system break interrupt flag (SBIF).
  * @rmtoll
  *  SR           SBIF          LL_TIM_ClearFlag_SYSBRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_SYSBRK(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_SBIF));
}

/**
  * @brief  Indicate whether system break interrupt flag (SBIF) is set (system break interrupt is pending).
  * @rmtoll
  *  SR           SBIF          LL_TIM_IsActiveFlag_SYSBRK
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_SYSBRK(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_SBIF) == (TIM_SR_SBIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 1 over-capture interrupt flag (CC1OF).
  * @rmtoll
  *  SR           CC1OF         LL_TIM_ClearFlag_CC1OVR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC1OVR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC1OF));
}

/**
  * @brief  Indicate whether Capture/Compare 1 over-capture interrupt flag (CC1OF) is set
  *         (Capture/Compare 1 interrupt is pending).
  * @rmtoll
  *  SR           CC1OF         LL_TIM_IsActiveFlag_CC1OVR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC1OVR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC1OF) == (TIM_SR_CC1OF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 2 over-capture interrupt flag (CC2OF).
  * @rmtoll
  *  SR           CC2OF         LL_TIM_ClearFlag_CC2OVR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC2OVR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC2OF));
}

/**
  * @brief  Indicate whether Capture/Compare 2 over-capture interrupt flag (CC2OF) is set
  *         (Capture/Compare 2 over-capture interrupt is pending).
  * @rmtoll
  *  SR           CC2OF         LL_TIM_IsActiveFlag_CC2OVR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC2OVR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC2OF) == (TIM_SR_CC2OF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 3 over-capture interrupt flag (CC3OF).
  * @rmtoll
  *  SR           CC3OF         LL_TIM_ClearFlag_CC3OVR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC3OVR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC3OF));
}

/**
  * @brief  Indicate whether Capture/Compare 3 over-capture interrupt flag (CC3OF) is set
  *         (Capture/Compare 3 over-capture interrupt is pending).
  * @rmtoll
  *  SR           CC3OF         LL_TIM_IsActiveFlag_CC3OVR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC3OVR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC3OF) == (TIM_SR_CC3OF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Capture/Compare 4 over-capture interrupt flag (CC4OF).
  * @rmtoll
  *  SR           CC4OF         LL_TIM_ClearFlag_CC4OVR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_CC4OVR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_CC4OF));
}

/**
  * @brief  Indicate whether Capture/Compare 4 over-capture interrupt flag (CC4OF) is set
  *         (Capture/Compare 4 over-capture interrupt is pending).
  * @rmtoll
  *  SR           CC4OF         LL_TIM_IsActiveFlag_CC4OVR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC4OVR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_CC4OF) == (TIM_SR_CC4OF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the transition error interrupt flag (TERRF).
  * @rmtoll
  *  SR           TERRF           LL_TIM_ClearFlag_TERR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_TERR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_TERRF));
}

/**
  * @brief  Indicate whether transition error interrupt flag (TERRF) is set (transition error interrupt is pending).
  * @rmtoll
  *  SR           TERRF           LL_TIM_IsActiveFlag_TERR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_TERR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_TERRF) == (TIM_SR_TERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the index error interrupt flag (IERRF).
  * @rmtoll
  *  SR           IERRF           LL_TIM_ClearFlag_IERR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_IERR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_IERRF));
}

/**
  * @brief  Indicate whether index error interrupt flag (IERRF) is set (index error interrupt is pending).
  * @rmtoll
  *  SR           IERRF           LL_TIM_IsActiveFlag_IERR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_IERR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_IERRF) == (TIM_SR_IERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the direction change interrupt flag (DIRF).
  * @rmtoll
  *  SR           DIRF           LL_TIM_ClearFlag_DIR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_DIR(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_DIRF));
}

/**
  * @brief  Indicate whether direction change interrupt flag (DIRF) is set (direction change interrupt is pending).
  * @rmtoll
  *  SR           DIRF           LL_TIM_IsActiveFlag_DIR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_DIR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_DIRF) == (TIM_SR_DIRF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the index interrupt flag (IDXF).
  * @rmtoll
  *  SR           IDXF           LL_TIM_ClearFlag_IDX
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_ClearFlag_IDX(TIM_TypeDef *timx)
{
  WRITE_REG(timx->SR, ~(TIM_SR_IDXF));
}

/**
  * @brief  Indicate whether index interrupt flag (IDXF) is set (index interrupt is pending).
  * @rmtoll
  *  SR           IDXF           LL_TIM_IsActiveFlag_IDX
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_IDX(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->SR, TIM_SR_IDXF) == (TIM_SR_IDXF)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_IT_Management IT-Management
  * @{
  */
/**
  * @brief  Enable update interrupt (UIE).
  * @rmtoll
  *  DIER         UIE           LL_TIM_EnableIT_UPDATE
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_UPDATE(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_UIE);
}

/**
  * @brief  Disable update interrupt (UIE).
  * @rmtoll
  *  DIER         UIE           LL_TIM_DisableIT_UPDATE
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_UPDATE(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_UIE);
}

/**
  * @brief  Indicates whether the update interrupt (UIE) is enabled.
  * @rmtoll
  *  DIER         UIE           LL_TIM_IsEnabledIT_UPDATE
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_UPDATE(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_UIE) == (TIM_DIER_UIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 1 interrupt (CC1IE).
  * @rmtoll
  *  DIER         CC1IE         LL_TIM_EnableIT_CC1
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_CC1(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC1IE);
}

/**
  * @brief  Disable capture/compare 1  interrupt (CC1IE).
  * @rmtoll
  *  DIER         CC1IE         LL_TIM_DisableIT_CC1
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_CC1(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC1IE);
}

/**
  * @brief  Indicates whether the capture/compare 1 interrupt (CC1IE) is enabled.
  * @rmtoll
  *  DIER         CC1IE         LL_TIM_IsEnabledIT_CC1
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC1(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC1IE) == (TIM_DIER_CC1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 2 interrupt (CC2IE).
  * @rmtoll
  *  DIER         CC2IE         LL_TIM_EnableIT_CC2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_CC2(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC2IE);
}

/**
  * @brief  Disable capture/compare 2  interrupt (CC2IE).
  * @rmtoll
  *  DIER         CC2IE         LL_TIM_DisableIT_CC2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_CC2(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC2IE);
}

/**
  * @brief  Indicates whether the capture/compare 2 interrupt (CC2IE) is enabled.
  * @rmtoll
  *  DIER         CC2IE         LL_TIM_IsEnabledIT_CC2
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC2(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC2IE) == (TIM_DIER_CC2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 3 interrupt (CC3IE).
  * @rmtoll
  *  DIER         CC3IE         LL_TIM_EnableIT_CC3
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_CC3(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC3IE);
}

/**
  * @brief  Disable capture/compare 3  interrupt (CC3IE).
  * @rmtoll
  *  DIER         CC3IE         LL_TIM_DisableIT_CC3
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_CC3(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC3IE);
}

/**
  * @brief  Indicates whether the capture/compare 3 interrupt (CC3IE) is enabled.
  * @rmtoll
  *  DIER         CC3IE         LL_TIM_IsEnabledIT_CC3
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC3(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC3IE) == (TIM_DIER_CC3IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 4 interrupt (CC4IE).
  * @rmtoll
  *  DIER         CC4IE         LL_TIM_EnableIT_CC4
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_CC4(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC4IE);
}

/**
  * @brief  Disable capture/compare 4  interrupt (CC4IE).
  * @rmtoll
  *  DIER         CC4IE         LL_TIM_DisableIT_CC4
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_CC4(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC4IE);
}

/**
  * @brief  Indicates whether the capture/compare 4 interrupt (CC4IE) is enabled.
  * @rmtoll
  *  DIER         CC4IE         LL_TIM_IsEnabledIT_CC4
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC4(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC4IE) == (TIM_DIER_CC4IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable commutation interrupt (COMIE).
  * @rmtoll
  *  DIER         COMIE         LL_TIM_EnableIT_COM
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_COM(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_COMIE);
}

/**
  * @brief  Disable commutation interrupt (COMIE).
  * @rmtoll
  *  DIER         COMIE         LL_TIM_DisableIT_COM
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_COM(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_COMIE);
}

/**
  * @brief  Indicates whether the commutation interrupt (COMIE) is enabled.
  * @rmtoll
  *  DIER         COMIE         LL_TIM_IsEnabledIT_COM
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_COM(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_COMIE) == (TIM_DIER_COMIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable trigger interrupt (TIE).
  * @rmtoll
  *  DIER         TIE           LL_TIM_EnableIT_TRIG
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_TRIG(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_TIE);
}

/**
  * @brief  Disable trigger interrupt (TIE).
  * @rmtoll
  *  DIER         TIE           LL_TIM_DisableIT_TRIG
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_TRIG(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_TIE);
}

/**
  * @brief  Indicates whether the trigger interrupt (TIE) is enabled.
  * @rmtoll
  *  DIER         TIE           LL_TIM_IsEnabledIT_TRIG
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_TRIG(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_TIE) == (TIM_DIER_TIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable break interrupt (BIE).
  * @rmtoll
  *  DIER         BIE           LL_TIM_EnableIT_BRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_BRK(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_BIE);
}

/**
  * @brief  Disable break interrupt (BIE).
  * @rmtoll
  *  DIER         BIE           LL_TIM_DisableIT_BRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_BRK(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_BIE);
}

/**
  * @brief  Indicates whether the break interrupt (BIE) is enabled.
  * @rmtoll
  *  DIER         BIE           LL_TIM_IsEnabledIT_BRK
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_BRK(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_BIE) == (TIM_DIER_BIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable transition error interrupt (TERRIE).
  * @note Macro IS_TIM_ENCODER_ERROR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder error management.
  * @rmtoll
  *  DIER         TERRIE           LL_TIM_EnableIT_TERR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_TERR(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_TERRIE);
}

/**
  * @brief  Disable transition error interrupt (TERRIE).
  * @note Macro IS_TIM_ENCODER_ERROR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder error management.
  * @rmtoll
  *  DIER         TERRIE           LL_TIM_DisableIT_TERR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_TERR(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_TERRIE);
}

/**
  * @brief  Indicates whether the transition error interrupt (TERRIE) is enabled.
  * @note Macro IS_TIM_ENCODER_ERROR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder error management.
  * @rmtoll
  *  DIER         TERRIE           LL_TIM_IsEnabledIT_TERR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_TERR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_TERRIE) == (TIM_DIER_TERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable index error interrupt (IERRIE).
  * @note Macro IS_TIM_ENCODER_ERROR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder error management.
  * @rmtoll
  *  DIER         IERRIE           LL_TIM_EnableIT_IERR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_IERR(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_IERRIE);
}

/**
  * @brief  Disable index error interrupt (IERRIE).
  * @note Macro IS_TIM_ENCODER_ERROR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder error management.
  * @rmtoll
  *  DIER         IERRIE           LL_TIM_DisableIT_IERR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_IERR(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_IERRIE);
}

/**
  * @brief  Indicates whether the index error interrupt (IERRIE) is enabled.
  * @note Macro IS_TIM_ENCODER_ERROR_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder error management.
  * @rmtoll
  *  DIER         IERRIE           LL_TIM_IsEnabledIT_IERR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_IERR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_IERRIE) == (TIM_DIER_IERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable direction change interrupt (DIRIE).
  * @note Macro IS_TIM_FUNCTINONAL_ENCODER_INTERRUPT_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder interrupt management.
  * @rmtoll
  *  DIER         DIRIE           LL_TIM_EnableIT_DIR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_DIR(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_DIRIE);
}

/**
  * @brief  Disable direction change interrupt (DIRIE).
  * @note Macro IS_TIM_FUNCTINONAL_ENCODER_INTERRUPT_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder interrupt management.
  * @rmtoll
  *  DIER         DIRIE           LL_TIM_DisableIT_DIR
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_DIR(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_DIRIE);
}

/**
  * @brief  Indicates whether the direction change interrupt (DIRIE) is enabled.
  * @note Macro IS_TIM_FUNCTINONAL_ENCODER_INTERRUPT_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder interrupt management.
  * @rmtoll
  *  DIER         DIRIE           LL_TIM_IsEnabledIT_DIR
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_DIR(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_DIRIE) == (TIM_DIER_DIRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable index interrupt (IDXIE).
  * @note Macro IS_TIM_FUNCTINONAL_ENCODER_INTERRUPT_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder interrupt management.
  * @rmtoll
  *  DIER         IDXIE           LL_TIM_EnableIT_IDX
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableIT_IDX(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_IDXIE);
}

/**
  * @brief  Disable index interrupt (IDXIE).
  * @note Macro IS_TIM_FUNCTINONAL_ENCODER_INTERRUPT_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder interrupt management.
  * @rmtoll
  *  DIER         IDXIE           LL_TIM_DisableIT_IDX
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableIT_IDX(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_IDXIE);
}

/**
  * @brief  Indicates whether the index interrupt (IDXIE) is enabled.
  * @note Macro IS_TIM_FUNCTINONAL_ENCODER_INTERRUPT_INSTANCE(timx) can be used to check whether or not
  *       a timer instance provides encoder interrupt management.
  * @rmtoll
  *  DIER         IDXIE           LL_TIM_IsEnabledIT_IDX
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_IDX(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_IDXIE) == (TIM_DIER_IDXIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the interrupt(s).
  * @rmtoll
  *  DIER         BIE             LL_TIM_EnableIT \n
  *  DIER         UIE             LL_TIM_EnableIT \n
  *  DIER         CC1IE           LL_TIM_EnableIT \n
  *  DIER         CC2IE           LL_TIM_EnableIT \n
  *  DIER         CC3IE           LL_TIM_EnableIT \n
  *  DIER         CC4IE           LL_TIM_EnableIT \n
  *  DIER         COMIE           LL_TIM_EnableIT \n
  *  DIER         IDXIE           LL_TIM_EnableIT \n
  *  DIER         DIRIE           LL_TIM_EnableIT \n
  *  DIER         IERRIE          LL_TIM_EnableIT \n
  *  DIER         TERRIE          LL_TIM_EnableIT \n
  *  DIER         TIE             LL_TIM_EnableIT
  * @param  timx Timer instance
  * @param  it_mask specifies the interrupt source(s) to enable.
  *         This parameter can be any combination of the following values:
  *         @arg @ref LL_TIM_DIER_UIE
  *         @arg @ref LL_TIM_DIER_CC1IE
  *         @arg @ref LL_TIM_DIER_CC2IE
  *         @arg @ref LL_TIM_DIER_CC3IE
  *         @arg @ref LL_TIM_DIER_CC4IE
  *         @arg @ref LL_TIM_DIER_COMIE
  *         @arg @ref LL_TIM_DIER_TIE
  *         @arg @ref LL_TIM_DIER_BIE
  *         @arg @ref LL_TIM_DIER_IDXIE
  *         @arg @ref LL_TIM_DIER_DIRIE
  *         @arg @ref LL_TIM_DIER_IERRIE
  *         @arg @ref LL_TIM_DIER_TERRIE
  */
__STATIC_INLINE void LL_TIM_EnableIT(TIM_TypeDef *timx, uint32_t it_mask)
{
  SET_BIT(timx->DIER, it_mask);
}

/**
  * @brief  Disable the interrupt(s).
  * @rmtoll
  *  DIER         BIE             LL_TIM_DisableIT \n
  *  DIER         UIE             LL_TIM_DisableIT \n
  *  DIER         CC1IE           LL_TIM_DisableIT \n
  *  DIER         CC2IE           LL_TIM_DisableIT \n
  *  DIER         CC3IE           LL_TIM_DisableIT \n
  *  DIER         CC4IE           LL_TIM_DisableIT \n
  *  DIER         COMIE           LL_TIM_DisableIT \n
  *  DIER         IDXIE           LL_TIM_DisableIT \n
  *  DIER         DIRIE           LL_TIM_DisableIT \n
  *  DIER         IERRIE          LL_TIM_DisableIT \n
  *  DIER         TERRIE          LL_TIM_DisableIT \n
  *  DIER         TIE             LL_TIM_DisableIT
  * @param  timx Timer instance
  * @param  it_mask specifies the interrupt source(s) to disable.
  *         This parameter can be any combination of the following values:
  *         @arg @ref LL_TIM_DIER_UIE
  *         @arg @ref LL_TIM_DIER_CC1IE
  *         @arg @ref LL_TIM_DIER_CC2IE
  *         @arg @ref LL_TIM_DIER_CC3IE
  *         @arg @ref LL_TIM_DIER_CC4IE
  *         @arg @ref LL_TIM_DIER_COMIE
  *         @arg @ref LL_TIM_DIER_TIE
  *         @arg @ref LL_TIM_DIER_BIE
  *         @arg @ref LL_TIM_DIER_IDXIE
  *         @arg @ref LL_TIM_DIER_DIRIE
  *         @arg @ref LL_TIM_DIER_IERRIE
  *         @arg @ref LL_TIM_DIER_TERRIE
  */
__STATIC_INLINE void LL_TIM_DisableIT(TIM_TypeDef *timx, uint32_t it_mask)
{
  CLEAR_BIT(timx->DIER, it_mask);
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_DMA_Management DMA Management
  * @{
  */
/**
  * @brief  Enable update DMA request (UDE).
  * @rmtoll
  *  DIER         UDE           LL_TIM_EnableDMAReq_UPDATE
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_UPDATE(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_UDE);
}

/**
  * @brief  Disable update DMA request (UDE).
  * @rmtoll
  *  DIER         UDE           LL_TIM_DisableDMAReq_UPDATE
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_UPDATE(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_UDE);
}

/**
  * @brief  Indicates whether the update DMA request  (UDE) is enabled.
  * @rmtoll
  *  DIER         UDE           LL_TIM_IsEnabledDMAReq_UPDATE
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_UPDATE(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_UDE) == (TIM_DIER_UDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 1 DMA request (CC1DE).
  * @rmtoll
  *  DIER         CC1DE         LL_TIM_EnableDMAReq_CC1
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_CC1(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC1DE);
}

/**
  * @brief  Disable capture/compare 1  DMA request (CC1DE).
  * @rmtoll
  *  DIER         CC1DE         LL_TIM_DisableDMAReq_CC1
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_CC1(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC1DE);
}

/**
  * @brief  Indicates whether the capture/compare 1 DMA request (CC1DE) is enabled.
  * @rmtoll
  *  DIER         CC1DE         LL_TIM_IsEnabledDMAReq_CC1
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC1(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC1DE) == (TIM_DIER_CC1DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 2 DMA request (CC2DE).
  * @rmtoll
  *  DIER         CC2DE         LL_TIM_EnableDMAReq_CC2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_CC2(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC2DE);
}

/**
  * @brief  Disable capture/compare 2  DMA request (CC2DE).
  * @rmtoll
  *  DIER         CC2DE         LL_TIM_DisableDMAReq_CC2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_CC2(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC2DE);
}

/**
  * @brief  Indicates whether the capture/compare 2 DMA request (CC2DE) is enabled.
  * @rmtoll
  *  DIER         CC2DE         LL_TIM_IsEnabledDMAReq_CC2
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC2(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC2DE) == (TIM_DIER_CC2DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 3 DMA request (CC3DE).
  * @rmtoll
  *  DIER         CC3DE         LL_TIM_EnableDMAReq_CC3
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_CC3(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC3DE);
}

/**
  * @brief  Disable capture/compare 3  DMA request (CC3DE).
  * @rmtoll
  *  DIER         CC3DE         LL_TIM_DisableDMAReq_CC3
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_CC3(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC3DE);
}

/**
  * @brief  Indicates whether the capture/compare 3 DMA request (CC3DE) is enabled.
  * @rmtoll
  *  DIER         CC3DE         LL_TIM_IsEnabledDMAReq_CC3
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC3(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC3DE) == (TIM_DIER_CC3DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable capture/compare 4 DMA request (CC4DE).
  * @rmtoll
  *  DIER         CC4DE         LL_TIM_EnableDMAReq_CC4
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_CC4(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_CC4DE);
}

/**
  * @brief  Disable capture/compare 4  DMA request (CC4DE).
  * @rmtoll
  *  DIER         CC4DE         LL_TIM_DisableDMAReq_CC4
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_CC4(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_CC4DE);
}

/**
  * @brief  Indicates whether the capture/compare 4 DMA request (CC4DE) is enabled.
  * @rmtoll
  *  DIER         CC4DE         LL_TIM_IsEnabledDMAReq_CC4
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC4(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_CC4DE) == (TIM_DIER_CC4DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable commutation DMA request (COMDE).
  * @rmtoll
  *  DIER         COMDE         LL_TIM_EnableDMAReq_COM
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_COM(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_COMDE);
}

/**
  * @brief  Disable commutation DMA request (COMDE).
  * @rmtoll
  *  DIER         COMDE         LL_TIM_DisableDMAReq_COM
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_COM(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_COMDE);
}

/**
  * @brief  Indicates whether the commutation DMA request (COMDE) is enabled.
  * @rmtoll
  *  DIER         COMDE         LL_TIM_IsEnabledDMAReq_COM
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_COM(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_COMDE) == (TIM_DIER_COMDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable trigger interrupt (TDE).
  * @rmtoll
  *  DIER         TDE           LL_TIM_EnableDMAReq_TRIG
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq_TRIG(TIM_TypeDef *timx)
{
  SET_BIT(timx->DIER, TIM_DIER_TDE);
}

/**
  * @brief  Disable trigger interrupt (TDE).
  * @rmtoll
  *  DIER         TDE           LL_TIM_DisableDMAReq_TRIG
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq_TRIG(TIM_TypeDef *timx)
{
  CLEAR_BIT(timx->DIER, TIM_DIER_TDE);
}

/**
  * @brief  Indicates whether the trigger interrupt (TDE) is enabled.
  * @rmtoll
  *  DIER         TDE           LL_TIM_IsEnabledDMAReq_TRIG
  * @param  timx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_TRIG(const TIM_TypeDef *timx)
{
  return ((READ_BIT(timx->DIER, TIM_DIER_TDE) == (TIM_DIER_TDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the selected dma request(s).
  * @rmtoll
  *  DIER         UDE             LL_TIM_EnableDMAReq \n
  *  DIER         CC1DE           LL_TIM_EnableDMAReq \n
  *  DIER         CC2DE           LL_TIM_EnableDMAReq \n
  *  DIER         CC3DE           LL_TIM_EnableDMAReq \n
  *  DIER         CC4DE           LL_TIM_EnableDMAReq \n
  *  DIER         COMDE           LL_TIM_EnableDMAReq \n
  *  DIER         TDE             LL_TIM_EnableDMAReq
  * @param  timx Timer instance
  * @param  dma_mask specifies the DMA request source(s) to enable.
  *         This parameter can be any combination of the following values:
  *         @arg @ref LL_TIM_DIER_UDE
  *         @arg @ref LL_TIM_DIER_CC1DE
  *         @arg @ref LL_TIM_DIER_CC2DE
  *         @arg @ref LL_TIM_DIER_CC3DE
  *         @arg @ref LL_TIM_DIER_CC4DE
  *         @arg @ref LL_TIM_DIER_COMDE
  *         @arg @ref LL_TIM_DIER_TDE
  */
__STATIC_INLINE void LL_TIM_EnableDMAReq(TIM_TypeDef *timx, uint32_t dma_mask)
{
  SET_BIT(timx->DIER, dma_mask);
}

/**
  * @brief  Disable the selected dma request(s).
  * @rmtoll
  *  DIER         UDE             LL_TIM_DisableDMAReq \n
  *  DIER         CC1DE           LL_TIM_DisableDMAReq \n
  *  DIER         CC2DE           LL_TIM_DisableDMAReq \n
  *  DIER         CC3DE           LL_TIM_DisableDMAReq \n
  *  DIER         CC4DE           LL_TIM_DisableDMAReq \n
  *  DIER         COMDE           LL_TIM_DisableDMAReq \n
  *  DIER         TDE             LL_TIM_DisableDMAReq
  * @param  timx Timer instance
  * @param  dma_mask specifies the DMA request source(s) to disable.
  *         This parameter can be any combination of the following values:
  *         @arg @ref LL_TIM_DIER_UDE
  *         @arg @ref LL_TIM_DIER_CC1DE
  *         @arg @ref LL_TIM_DIER_CC2DE
  *         @arg @ref LL_TIM_DIER_CC3DE
  *         @arg @ref LL_TIM_DIER_CC4DE
  *         @arg @ref LL_TIM_DIER_COMDE
  *         @arg @ref LL_TIM_DIER_TDE
  */
__STATIC_INLINE void LL_TIM_DisableDMAReq(TIM_TypeDef *timx, uint32_t dma_mask)
{
  CLEAR_BIT(timx->DIER, dma_mask);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_EVENT_Management EVENT-Management
  * @{
  */
/**
  * @brief  Generate an update event.
  * @rmtoll
  *  EGR          UG            LL_TIM_GenerateEvent_UPDATE
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_UPDATE(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_UG);
}

/**
  * @brief  Generate Capture/Compare 1 event.
  * @rmtoll
  *  EGR          CC1G          LL_TIM_GenerateEvent_CC1
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_CC1(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_CC1G);
}

/**
  * @brief  Generate Capture/Compare 2 event.
  * @rmtoll
  *  EGR          CC2G          LL_TIM_GenerateEvent_CC2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_CC2(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_CC2G);
}

/**
  * @brief  Generate Capture/Compare 3 event.
  * @rmtoll
  *  EGR          CC3G          LL_TIM_GenerateEvent_CC3
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_CC3(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_CC3G);
}

/**
  * @brief  Generate Capture/Compare 4 event.
  * @rmtoll
  *  EGR          CC4G          LL_TIM_GenerateEvent_CC4
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_CC4(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_CC4G);
}

/**
  * @brief  Generate commutation event.
  * @rmtoll
  *  EGR          COMG          LL_TIM_GenerateEvent_COM
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_COM(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_COMG);
}

/**
  * @brief  Generate trigger event.
  * @rmtoll
  *  EGR          TG            LL_TIM_GenerateEvent_TRIG
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_TRIG(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_TG);
}

/**
  * @brief  Generate break event.
  * @rmtoll
  *  EGR          BG            LL_TIM_GenerateEvent_BRK
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_BRK(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_BG);
}

/**
  * @brief  Generate break 2 event.
  * @rmtoll
  *  EGR          B2G           LL_TIM_GenerateEvent_BRK2
  * @param  timx Timer instance
  */
__STATIC_INLINE void LL_TIM_GenerateEvent_BRK2(TIM_TypeDef *timx)
{
  SET_BIT(timx->EGR, TIM_EGR_B2G);
}


/**
  * @brief  Generate software event(s).
  * @rmtoll
  *  EGR          UG            LL_TIM_GenerateEvent \n
  *  EGR          CC1G          LL_TIM_GenerateEvent \n
  *  EGR          CC2G          LL_TIM_GenerateEvent \n
  *  EGR          CC3G          LL_TIM_GenerateEvent \n
  *  EGR          CC4G          LL_TIM_GenerateEvent \n
  *  EGR          COMG          LL_TIM_GenerateEvent \n
  *  EGR          TG            LL_TIM_GenerateEvent \n
  *  EGR          BG            LL_TIM_GenerateEvent \n
  *  EGR          B2G           LL_TIM_GenerateEvent
  * @param  timx Timer instance
  * @param  software_event specifies the software event source(s) to generate.
  *         This parameter can be any combination of the following values:
  *         @arg @ref LL_TIM_SW_EVENT_UPD
  *         @arg @ref LL_TIM_SW_EVENT_CC1
  *         @arg @ref LL_TIM_SW_EVENT_CC2
  *         @arg @ref LL_TIM_SW_EVENT_CC3
  *         @arg @ref LL_TIM_SW_EVENT_CC4
  *         @arg @ref LL_TIM_SW_EVENT_COM
  *         @arg @ref LL_TIM_SW_EVENT_TRGI
  *         @arg @ref LL_TIM_SW_EVENT_BRK
  *         @arg @ref LL_TIM_SW_EVENT_BRK2
  */
__STATIC_INLINE void LL_TIM_GenerateEvent(TIM_TypeDef *timx, uint32_t software_event)
{
  SET_BIT(timx->EGR, software_event);
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

#endif /* TIM1 || TIM2 || TIM3 || TIM4 || TIM5 || TIM6 || TIM7 || TIM8 || TIM15 || TIM16 || TIM17 */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_TIM_H */
