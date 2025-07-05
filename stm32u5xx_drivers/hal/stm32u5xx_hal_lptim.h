/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_lptim.h
  * @brief   Header file of LPTIM HAL module.
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
#ifndef STM32U5XX_HAL_LPTIM_H
#define STM32U5XX_HAL_LPTIM_H

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_lptim.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32U5xx_HAL_Driver
  *  @{
  */

/** @defgroup LPTIM LPTIM
  *  @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @addtogroup LPTIM_Private_Constants
  *  @{
  */

/**
  * @brief Maximum number of channels
  */
#define HAL_LPTIM_CHANNELS 2U

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
/**
  * @brief Maximum number of DMA requests
  */
#define LPTIM_DMA_REQUESTS 3U

/* Substate of an active state */
#define LPTIM_ACTIVE_NOT_SILENT (0U)
#define LPTIM_ACTIVE_SILENT     (1U)

#endif /* USE_HAL_LPTIM_DMA */

/**
  * @}
  */
/* End of private constants ------------------------------------------------------------------------------------------*/

/* Private macro     -------------------------------------------------------------------------------------------------*/

/* End of private macro     ------------------------------------------------------------------------------------------*/

/* Exported macros    ------------------------------------------------------------------------------------------------*/

/* End of exported macros    -----------------------------------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Constants LPTIM Exported Constants
  *  @{
  */

#if defined (USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)
/** @defgroup  LPTIM_Error_Code Error Code definition reflecting the processes
  * asynchronous errors
  * @{
  */

/** No error                                                      */
#define  HAL_LPTIM_ERROR_NONE      (0UL)

/** DMA transfer error                                            */
#define  HAL_LPTIM_ERROR_DMA       (1UL << 0)

/** Timeout on the write operation in register (CCRx, ARR, DIER, REPOK). */
#define  HAL_LPTIM_ERROR_TIMEOUT   (1UL << 1)

/**
  * @}
  */
#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)

/**
  * @brief DMA optional DMA interrupt disable
  */
#define HAL_LPTIM_OPT_DMA_IT_NONE   HAL_DMA_OPT_IT_NONE
/**
  * @brief optional DMA Interrupt half transfer interrupt enabled
  */
#define HAL_LPTIM_OPT_DMA_IT_HT   HAL_DMA_OPT_IT_HT
/**
  * @brief ALL DMA interrupts enabled
  */
#define HAL_LPTIM_OPT_DMA_IT_DEFAULT    HAL_DMA_OPT_IT_DEFAULT
/**
  * @brief all optional DMA interrupts disable
  */
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#define HAL_LPTIM_OPT_DMA_IT_SILENT HAL_DMA_OPT_IT_SILENT
#endif /* USE_HAL_DMA_LINKEDLIST */

#endif /* USE_HAL_LPTIM_DMA */
/**
  * @}
  */
/* End of exported constants -----------------------------------------------------------------------------------------*/

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Types LPTIM Exported Types
  *  @{
  */

/** @defgroup LPTIM_Exported_Types_Group1 Enumerations
  * @{
 */

/**
  * @brief HAL LPTIM instance
  */
typedef enum
{
  /** LPTIM1 */
  HAL_LPTIM1  = (uint32_t)LPTIM1,

  /** LPTIM2 */
  HAL_LPTIM2  = (uint32_t)LPTIM2,

  /** LPTIM3 */
  HAL_LPTIM3  = (uint32_t)LPTIM3,

  /** LPTIM4 */
  HAL_LPTIM4  = (uint32_t)LPTIM4,

} hal_lptim_t;


/**
  * @brief  HAL LPTIM Global States definition
  */
typedef enum
{
  /** Peripheral not yet initialized                     */
  HAL_LPTIM_STATE_RESET   = 0UL,

  /** Peripheral initialized but not yet configured      */
  HAL_LPTIM_STATE_INIT    = (1UL << 31U),

  /** Peripheral initialized and a global config applied */
  HAL_LPTIM_STATE_IDLE    = (1UL << 30U),

  /** Counter is running */
  HAL_LPTIM_STATE_ACTIVE  = (1UL << 29U),

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** Counter is running with Silent DMA mode */
  HAL_LPTIM_STATE_ACTIVE_SILENT = (HAL_LPTIM_STATE_ACTIVE | LPTIM_ACTIVE_SILENT),
#endif /* USE_HAL_LPTIM_DMA */
} hal_lptim_state_t;


/**
  * @brief  LPTIM Channel States definition
  */
typedef enum
{
  /** LPTIM Channel initial state                                */
  HAL_LPTIM_CHANNEL_STATE_RESET       = (1UL << 31U),

  /** LPTIM Channel ready for use as output channel              */
  HAL_LPTIM_OC_CHANNEL_STATE_IDLE     = (1UL << 30U),

  /** An internal process is ongoing on the LPTIM output channel */
  HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE   = (1UL << 29U),

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** An internal process is ongoing on the LPTIM output channel in DMA silent mode. */
  HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE_SILENT = (HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE |
                                              LPTIM_ACTIVE_SILENT),
#endif /* USE_HAL_LPTIM_DMA */

  /** LPTIM Channel ready for use as input channel               */
  HAL_LPTIM_IC_CHANNEL_STATE_IDLE     = (1UL << 28U),

  /** An internal process is ongoing on the LPTIM input channel */
  HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE   = (1UL << 27U),

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** An internal process is ongoing on the LPTIM input channel in DMA silent mode. */
  HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE_SILENT = (HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE |
                                              LPTIM_ACTIVE_SILENT),
#endif /* USE_HAL_LPTIM_DMA */
} hal_lptim_channel_state_t;

/**
  * @brief  HAL LPTIM Channels identifier definition
  */
typedef enum
{
  /** LP Timer input/output channel 1         */
  HAL_LPTIM_CHANNEL_1   = LL_LPTIM_CHANNEL_CH1,

  /** LP Timer input/output channel 2         */
  HAL_LPTIM_CHANNEL_2   = LL_LPTIM_CHANNEL_CH2,

} hal_lptim_channel_t;

/**
  * @brief  HAL LPTIM Counter Mode Configuration.
  *
  * The counter mode configuration let us select how the counter is started and reset.
  *     -The counter can be in continuous counting mode or in one-shot
  *         counting mode which defines how the counter is started.
  *
  *         - Continuous mode: the timer is free running, the timer is
  *           started from a trigger event and never stops until the timer
  *           is disabled.
  *           This mode is further divided in two submodes:
  *           - regular: a trigger event arriving starts the counter and
  *                      subsequent external trigger event is discarded.
  *           - Timeout: the first trigger event starts the timer,
  *                      any successive trigger event resets the LPTIM
  *                      counter and the repetition counter and the timer
  *                      restarts.
  *
  *         - One-shot mode: the timer starts from a trigger event and
  *           stops when an LPTIM update event is generated.
  *           This mode is further divided in two submodes:
  *           - regular: the counter is stopped on update event once the
  *                      repetition counter is 0. Then, a subsequent trigger
  *                      starts a new one-shot counting cycle.
  *           - Set-once: the counter is only started once following the
  *                       first trigger, and any subsequent trigger event is
  *                       discarded.
  *
  *
  * @note: The waveform on an output channel depending on the counter mode.
  *        In One-shot mode the output waveform is a PWM signal for the
  *        duration of the one-shot cycle (that is pulse waveform, where
  *        the number of pulses generated depends on the repetition counter).
  *        In Set-once mode, there is only one 'one-shot cycle'.
  *        At the end of the counting period, the output level is frozen as per the configured polarity.
  *        To obtain a typical (continuous) PWM signal on an output channel,
  *        the countinuous counting mode must be selected
  */
typedef enum
{
  /** One-shot.
      When the counter is stopped a trigger event starts it.
      The counter is stopped on update event. */
  HAL_LPTIM_ONE_SHOT   = LL_LPTIM_OPERATING_MODE_ONESHOT,

  /** Set-once.
      A first trigger event starts the counter for a single
      one-shot cycle. */
  HAL_LPTIM_SET_ONCE   = (LL_LPTIM_OPERATING_MODE_ONESHOT |
                          LL_LPTIM_OC_WAVEFORM_SETONCE),

  /** Continuous.
      The timer is started from a trigger event and never stops
      until it is disabled. */
  HAL_LPTIM_CONTINUOUS = LL_LPTIM_OPERATING_MODE_CONTINUOUS,

  /** Timeout.
      Similar to 'Continuous' mode, except that any new trigger after the start
      resets the counter.
      @note The value for the timeout is set using
            HAL_LPTIM_OC_SetConfigChannel() or
            HAL_LPTIM_OC_SetChannelPulse(). */
  HAL_LPTIM_TIMEOUT    = (LL_LPTIM_OPERATING_MODE_CONTINUOUS |
                          LL_LPTIM_TIMEOUT_ENABLE),

} hal_lptim_mode_t;

/**
  * @brief HAL LPTIM input channel sources
  */
typedef enum
{
  /** IC1 connected to GPIO */
  HAL_LPTIM_INPUT_GPIO,

  /** IC2 connected to LSI */
  HAL_LPTIM_INPUT_LSI,

  /** IC2 connected to LSE */
  HAL_LPTIM_INPUT_LSE,

  /** IC1 connected to COMP1 */
  HAL_LPTIM_INPUT_COMP1,

#if defined (COMP2)
  /** IC1 connected to COMP2 */
  HAL_LPTIM_INPUT_COMP2,
#endif /* COMP2 */

  /** IC2 connected to HSI */
  HAL_LPTIM_INPUT_HSI_256,

  /** IC2 connected to MSI1024 */
  HAL_LPTIM_INPUT_MSI_1024,

  /** IC2 connected to MSI/4 */
  HAL_LPTIM_INPUT_MSI_4,

} hal_lptim_ic_src_t;


/**
  * @brief HAL LPTIM Clock Source Prescaler definition
  *
  * @note In encoder mode the prescaler division factor
  *       must be set to 1.
  */
typedef enum
{
  /** Prescaler division factor is set to 1            */
  HAL_LPTIM_CLK_SRC_DIV1   = LL_LPTIM_PRESCALER_DIV1,

  /** Prescaler division factor is set to 2            */
  HAL_LPTIM_CLK_SRC_DIV2   = LL_LPTIM_PRESCALER_DIV2,

  /** Prescaler division factor is set to 4            */
  HAL_LPTIM_CLK_SRC_DIV4   = LL_LPTIM_PRESCALER_DIV4,

  /** Prescaler division factor is set to 8            */
  HAL_LPTIM_CLK_SRC_DIV8   = LL_LPTIM_PRESCALER_DIV8,

  /** Prescaler division factor is set to 16           */
  HAL_LPTIM_CLK_SRC_DIV16  = LL_LPTIM_PRESCALER_DIV16,

  /** Prescaler division factor is set to 32           */
  HAL_LPTIM_CLK_SRC_DIV32  = LL_LPTIM_PRESCALER_DIV32,

  /** Prescaler division factor is set to 64           */
  HAL_LPTIM_CLK_SRC_DIV64  = LL_LPTIM_PRESCALER_DIV64,

  /** Prescaler division factor is set to 128          */
  HAL_LPTIM_CLK_SRC_DIV128 = LL_LPTIM_PRESCALER_DIV128,

} hal_lptim_clk_src_presc_t;


/**
  * @brief HAL LPTIM Input1 (IN1) Polarity definition.
  *
  * When LPTIM_IN1 is used as external clock source(HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or
  * HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS), the active edge of the signal can be selected
  *
  * @note  For encoder mode the polarity of Input1 is configured by selecting
  *        the encoder submode (HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3])
  *
  * @note
  *        If both edges are configured to be active ones, an internal clock
  *        signal must also be provided.
  */
typedef enum
{
  /** The rising edge is the active edge used for counting            */
  HAL_LPTIM_INPUT1_RISING         = LL_LPTIM_CLK_POLARITY_RISING,

  /** The falling edge is the active edge used for counting           */
  HAL_LPTIM_INPUT1_FALLING        = LL_LPTIM_CLK_POLARITY_FALLING,

  /** Both edges are active edges.
      This is valid only if an internal clock is provided. That is, the clock
      source is HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS.
      The internal clock signal frequency must be at least four times higher
      than the external clock signal frequency. */
  HAL_LPTIM_INPUT1_RISING_FALLING = LL_LPTIM_CLK_POLARITY_RISING_FALLING,

} hal_lptim_input1_polarity_t;

/**
  * @brief HAL LPTIM Input1 source definition
  *
  * When LPTIM is clocked by an external clock signal injected on
  * LPTIM_IN1 or configured in Encoder mode it is possible to
  * select the source connected to Input1.
  * (@ref HAL_LPTIM_SetInput1Source()).
  */
typedef enum
{
  HAL_LPTIM_INPUT1_GPIO  = LL_LPTIM_INPUT1_SRC_GPIO,

  HAL_LPTIM_INPUT1_COMP1 = LL_LPTIM_INPUT1_SRC_COMP1,

} hal_lptim_input1_src_t;


/**
  * @brief HAL LPTIM Input2 source definition
  *
  * When LPTIM is configured in Encoder mode it is
  * possible to select the source connected to Input2 using
  * the function to configure the encoder (@ref HAL_LPTIM_SetConfigEncoder()).
  */
typedef enum
{
  HAL_LPTIM_INPUT2_GPIO  = LL_LPTIM_INPUT2_SRC_GPIO,

#if defined(COMP2)
  HAL_LPTIM_INPUT2_COMP2 = LL_LPTIM_INPUT2_SRC_COMP2,
#endif /* COMP2 */

} hal_lptim_input2_src_t;


/**
  * @brief HAL LPTIM Clock Source selection
  */
typedef enum
{
  /*---------------------------------------- Internal clock source ---------------------------------------------------*/
  /** LPTIM is clocked by internal clock source (APB clock or any of the
  embedded oscillators). \n
  The counter is incremented following each internal clock pulse.
  */
  HAL_LPTIM_CLK_INTERNAL = (LL_LPTIM_CLK_SOURCE_INTERNAL |
                            LL_LPTIM_COUNTER_MODE_INTERNAL),

  /*------------------------------------- External clock source with internal clock --------------------------------- */
  /** The LPTIM external Input1 is sampled with the internal clock (APB clock
   or any of the embedded oscillators) provided to the LPTIM. \n
   It is possible to configure the external clock source (Input1 signal
   conditioning) through dedicated functions:
                      - @ref HAL_LPTIM_SetConfigInput1()
                      - @ref HAL_LPTIM_SetInput1Source()
                      - @ref HAL_LPTIM_SetInput1Polarity()
                      - @ref HAL_LPTIM_SetInput1Filter()
  */
  HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS = (LL_LPTIM_CLK_SOURCE_INTERNAL |
                                        LL_LPTIM_COUNTER_MODE_EXTERNAL),

  /*------------------------------------- External clock source only ------------------------------------------------ */
  /** The signal injected on the LPTIM external Input1 is used as system
   clock for the LPTIM. \n
   It is possible to configure the external clock source (Input1 signal
   conditioning) through dedicated functions:
                      - @ref HAL_LPTIM_SetConfigInput1()
                      - @ref HAL_LPTIM_SetInput1Source()
                      - @ref HAL_LPTIM_SetInput1Polarity()
                      - @ref HAL_LPTIM_SetInput1Filter()
   @note: If the polarity is configured on 'both edges', or if filtering is
         used, an auxiliary clock (one of the Low power oscillator) must
         be active.
  */
  HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS = LL_LPTIM_CLK_SOURCE_EXTERNAL,

  /*-------------------------------------------------- Encoder mode ------------------------------------------------- */
  /* LPTIM is in encoder mode. It is clocked by internal clock source with   */
  /* prescaler division ratio at 1 (reset value).                            */
  /* The clock signal for the counter is generated from the two external     */
  /* inputs (Input1 and Input2).                                             */
  /* The signals frequency on both Input1 and Input2 inputs must not exceed  */
  /* the LPTIM internal clock frequency divided by 4.                        */
  /* It is possible to configure the Input1 and Input2 conditioning     */
  /* through a dedicated function @ref HAL_LPTIM_SetConfigEncoder(). */

  /** Quadrature encoder sub-mode 1: rising edge is the active edge.

      Count Down when:
      - a rising edge on Input1 when Input2 is high
      - a rising edge on Input2 when Input1 is low

      Count Up when:
      - a rising edge on Input1 when Input2 is low
      - a rising edge on Input2 when Input1 is high
   */
  HAL_LPTIM_CLK_ENCODER_SUBMODE_1 = (LL_LPTIM_CLK_SOURCE_INTERNAL |
                                     LL_LPTIM_ENCODER_MODE_RISING |
                                     LL_LPTIM_ENCODER_MODE_ENABLE),

  /** Quadrature encoder sub-mode 2: falling edge is the active edge.

      Count Down when:
      - a falling edge on Input1 when Input2 is low
      - a falling edge on Input2 when Input1 is high

      Count Up when:
      - a falling edge on Input1 when Input2 is high
      - a falling edge on Input2 when Input1 is low
  */
  HAL_LPTIM_CLK_ENCODER_SUBMODE_2 = (LL_LPTIM_CLK_SOURCE_INTERNAL |
                                     LL_LPTIM_ENCODER_MODE_FALLING |
                                     LL_LPTIM_ENCODER_MODE_ENABLE),

  /** Quadrature encoder sub-mode 3: both edges are active edges.

      Count Down with:
      - a rising edge on Input1 when Input2 is high
      - a rising edge on Input2 when Input1 is low
      - a falling edge on Input1 when Input2 is low
      - a falling edge on Input2 when Input1 is high

      Count Up with:
      - a rising edge on Input1 when Input2 is low
      - a rising edge on Input2 when Input1 is high
      - a falling edge on Input1 when Input2 is high
      - a falling edge on Input2 when Input1 is low
  */
  HAL_LPTIM_CLK_ENCODER_SUBMODE_3 = (LL_LPTIM_CLK_SOURCE_INTERNAL |
                                     LL_LPTIM_ENCODER_MODE_RISING_FALLING |
                                     LL_LPTIM_ENCODER_MODE_ENABLE),

} hal_lptim_clk_src_t;

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
/**
  *  @brief LPTIM DMA Handle Index
  */
typedef enum
{
  /** Index of the DMA handle used for Update DMA requests                 */
  HAL_LPTIM_DMA_ID_UPDATE      = 0x0U,

  /** Index of the DMA handle used for input capture event 1 DMA requests */
  HAL_LPTIM_DMA_ID_CC1         = 0x1U,

  /** Index of the DMA handle used for input capture event 2 DMA requests */
  HAL_LPTIM_DMA_ID_CC2         = 0x2U,

} hal_lptim_dma_index_t;
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief HAL LPTIM External Trigger Selection.
  */
typedef enum
{
  /** External input trigger is connected to TIMx_ETR input */
  HAL_LPTIM_EXT_TRIG_GPIO,

  /** External input trigger is connected to RTC Alarm A    */
  HAL_LPTIM_EXT_TRIG_RTC_ALMA_TRG,

  /** External input trigger is connected to RTC Alarm B    */
  HAL_LPTIM_EXT_TRIG_RTC_ALMB_TRG,

  /** External input trigger is connected to RTC Tamper 1   */
  HAL_LPTIM_EXT_TRIG_TAMP_TRG1,

  /** External input trigger is connected to RTC Tamper 2   */
  HAL_LPTIM_EXT_TRIG_TAMP_TRG2,

  /** External input trigger is connected to RTC Tamper 3   */
  HAL_LPTIM_EXT_TRIG_TAMP_TRG3,

  /** External input trigger is connected to COMP1 output   */
  HAL_LPTIM_EXT_TRIG_COMP1,

  /** External input trigger is connected to COMP2 output   */
  HAL_LPTIM_EXT_TRIG_COMP2,

  /** External input trigger is connected to LPDMA CH0 transfer complete */
  HAL_LPTIM_EXT_TRIG_LPDMA_CH0_TC,

  /** External input trigger is connected to LPDMA CH1 transfer complete */
  HAL_LPTIM_EXT_TRIG_LPDMA_CH1_TC,

  /** External input trigger is connected to LPDMA CH2 transfer complete */
  HAL_LPTIM_EXT_TRIG_LPDMA_CH2_TC,

  /** External input trigger is connected to GPDMA CH0 transfer complete */
  HAL_LPTIM_EXT_TRIG_GPDMA_CH0_TC,

  /** External input trigger is connected to GPDMA CH4 transfer complete */
  HAL_LPTIM_EXT_TRIG_GPDMA_CH4_TC,

} hal_lptim_ext_trig_src_t;


/**
  * @brief HAL LPTIM External Trigger Polarity.
  */
typedef enum
{
  /** LPTIM counter starts when a rising edge is detected  */
  HAL_LPTIM_TRIG_RISING = LL_LPTIM_TRIG_POLARITY_RISING,

  /** LPTIM counter starts when a falling edge is detected */
  HAL_LPTIM_TRIG_FALLING = LL_LPTIM_TRIG_POLARITY_FALLING,

  /** LPTIM counter starts when a rising or a falling edge is detected */
  HAL_LPTIM_TRIG_RISING_FALLING = LL_LPTIM_TRIG_POLARITY_RISING_FALLING,

} hal_lptim_ext_trig_polarity_t;

/**
  * @brief HAL LPTIM Digital Filter definition
  *        The LPTIM inputs, either external (connected to GPIOs) or internal
  *        (connected to other built-in peripherals), are
  *        protected with digital filters that prevent any glitches and noise
  *        perturbations to propagate inside the LPTIM.
  *
  *        The digital filters are divided into three groups:
  *        - The first group of digital filters protects the LPTIM internal or
  *          external inputs. The digital filters sensitivity is controlled by
  *          the CKFLT bits,
  *        - The second group of digital filters protects the LPTIM internal or
  *          external trigger inputs. The digital filters sensitivity is
  *          controlled by the TRGFLT bits.
  *        - The third group of digital filters protects the LPTIM internal or
  *          external input captures. The digital filters sensitivity is
  *          controlled by the ICxF bits.
  *
  * @note  Internal clock signal must be provided to the LPTIM
  */
typedef enum
{
  /** No filter                                          */
  HAL_LPTIM_FDIV1    = 0x0U,

  /** Active level change must be stable for at least
      2 clock  periods before it is considered as valid  */
  HAL_LPTIM_FDIV1_N2 = 0x1U,

  /** Active level change must be stable for at least
      4 clock  periods before it is considered as valid  */
  HAL_LPTIM_FDIV1_N4 = 0x2U,

  /** Active level change must be stable for at least
      8 clock  periods before it is considered as valid  */
  HAL_LPTIM_FDIV1_N8 = 0x3U,

} hal_lptim_filter_t;


/**
  * @brief HAL LPTIM Preload Status.
  *        When preload is enabled the update of the autoreload and repetition counter
  *        of the compare values is done at the end of current period.
  *
  *        @note If repetition counter is used then preload must be enabled
  *        otherwise unpredictable behavior is occur.
  */
typedef enum
{
  /** LPTIMx ARR/RCR/CCRx registers are not preloaded.
      Registers are updated after each APB bus write access. */
  HAL_LPTIM_PRELOAD_DISABLED = LL_LPTIM_PRELOAD_DISABLED,

  /** LPTIMx ARR/RCR/CCRx registers are preloaded.
      Registers are updated at next LPTIM update event, if the
      timer has been already started. */
  HAL_LPTIM_PRELOAD_ENABLED  = LL_LPTIM_PRELOAD_ENABLED,

} hal_lptim_preload_status_t;

/**
  * @brief HAL LPTIM Reset counter after read Status.
  *        When Reset counter after read is enabled, counter will be reset after each
  *        @ref HAL_LPTIM_GetCounter call.
  */
typedef enum
{
  HAL_LPTIM_RESET_AFTER_READ_DISABLED = 0U,

  HAL_LPTIM_RESET_AFTER_READ_ENABLED  = 1U,

} hal_lptim_reset_after_read_status_t;


/**
  * @brief HAL LPTIM Output Channel Polarity
  */
typedef enum
{
  /** Output Channel active high. The LPTIM output reflects the compare
      results between LPTIM_ARR and LPTIM_CCRx registers.                 */
  HAL_LPTIM_OC_HIGH = LL_LPTIM_OCPOLARITY_HIGH,

  /** Output Channel active low. The LPTIM output reflects the inverse
      of the compare results between LPTIMx_ARR and LPTIMx_CCx registers. */
  HAL_LPTIM_OC_LOW  = LL_LPTIM_OCPOLARITY_LOW,

} hal_lptim_oc_polarity_t;


/**
  * @brief HAL LPTIM Input Channel Polarity
  */
typedef enum
{
  /** Rising edges are detected in input channel                  */
  HAL_LPTIM_IC_RISING         = LL_LPTIM_ICPOLARITY_RISING,

  /** Falling edges are detected on input channel                 */
  HAL_LPTIM_IC_FALLING        = LL_LPTIM_ICPOLARITY_FALLING,

  /** Both rising and falling edges are detected on input channel */
  HAL_LPTIM_IC_RISING_FALLING = LL_LPTIM_ICPOLARITY_RISING_FALLING,

} hal_lptim_ic_polarity_t;


/**
  * @brief HAL LPTIM Input Channel Prescaler
  */
typedef enum
{
  /** Capture performed each time an edge is detected on the input channel */
  HAL_LPTIM_IC_DIV1 = LL_LPTIM_ICPSC_DIV1,

  /** Capture performed once every 2 events                                */
  HAL_LPTIM_IC_DIV2 = LL_LPTIM_ICPSC_DIV2,

  /** Capture performed once every 4 events                                */
  HAL_LPTIM_IC_DIV4 = LL_LPTIM_ICPSC_DIV4,

  /** Capture performed once every 8 events                                */
  HAL_LPTIM_IC_DIV8 = LL_LPTIM_ICPSC_DIV8,

} hal_lptim_ic_prescaler_t;

/**
  * @}
  */

/** @defgroup LPTIM_Exported_Types_Group2 Structures
  * @{
 */

/**
  * @brief HAL LPTIM Time Base Handle type declaration
  */
struct hal_lptim_handle_s;
/**
  * @brief Typedef HAL LPTIM Time Base Handle type declaration
  */
typedef struct hal_lptim_handle_s hal_lptim_handle_t;

/*
 * Types definitions for the callbacks
 */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
/** HAL LPTIM generic callback pointer definition */
typedef void (* hal_lptim_cb_t)(hal_lptim_handle_t *);
/** HAL LPTIM callback pointer definition with channel parameter */
typedef void (* hal_lptim_channel_cb_t)(hal_lptim_handle_t *, hal_lptim_channel_t);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */


/**
  * @brief HAL LPTIM Time Base Handle Structure definition
  */
struct hal_lptim_handle_s
{
  /** HAL LPTIM instance */
  hal_lptim_t instance;

  /** LPTIM mode */
  hal_lptim_mode_t mode;

  /** LPTIM global state */
  volatile hal_lptim_state_t global_state;

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** DMA Handlers array. (Handler can be listed with @ref hal_lptim_dma_index_t) */
  hal_dma_handle_t *hdma[LPTIM_DMA_REQUESTS];
#endif /* USE_HAL_LPTIM_DMA */

  /** LPTIM channels state array */
  volatile hal_lptim_channel_state_t channel_states[HAL_LPTIM_CHANNELS];

#if defined(USE_HAL_LPTIM_USER_DATA) && (USE_HAL_LPTIM_USER_DATA == 1)
  /** User Data Pointer  */
  const void *p_user_data;
#endif /* USE_HAL_LPTIM_USER_DATA */

#if defined (USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)
  /**
    * @brief Store last error code
    */
  volatile uint32_t last_error_codes;
#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** LPTIM Error callback */
  hal_lptim_cb_t error_callback;

  /** LPTIM Update DMA stop callback */
  hal_lptim_cb_t stop_callback;

  /** LPTIM capture/Compare DMA stop callback */
  hal_lptim_channel_cb_t input_capture_stop_callback;
#endif /* USE_HAL_LPTIM_DMA */

  /** LPTIM Update callback */
  hal_lptim_cb_t update_callback;

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** LPTIM Update Half Complete callback. */
  hal_lptim_cb_t update_half_cplt_callback;
#endif /* USE_HAL_LPTIM_DMA */

  /** LPTIM Auto Reload Update callback */
  hal_lptim_cb_t auto_reload_update_callback;

  /** LPTIM Auto Reload Match callback */
  hal_lptim_cb_t auto_reload_match_callback;

  /** LPTIM Repetition Update callback */
  hal_lptim_cb_t rep_update_callback;

  /** LPTIM Trigger callback */
  hal_lptim_cb_t trigger_callback;

  /** LPTIM Compare Match callback */
  hal_lptim_channel_cb_t compare_match_callback;

  /** LPTIM Compare Update callback */
  hal_lptim_channel_cb_t compare_update_callback;

  /** LPTIM Input Capture callback */
  hal_lptim_channel_cb_t input_capture_callback;

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /** LPTIM Input Capture Half Complete callback */
  hal_lptim_channel_cb_t input_capture_half_cplt_callback;
#endif /* USE_HAL_LPTIM_DMA */

  /** Over capture Callback */
  hal_lptim_channel_cb_t input_over_capture_callback;

  /** LPTIM Direction UP Change callback */
  hal_lptim_cb_t direction_up_callback;

  /** LPTIM Direction DOWN Change callback */
  hal_lptim_cb_t direction_down_callback;

#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
};


/**
  * @brief HAL LPTIM Input1 Configuration Structure definition
  *
  */
typedef struct
{
  /** Select the source connected to Input1. */
  hal_lptim_input1_src_t src;

  /** Select the active edge(s) of the signal. */
  hal_lptim_input1_polarity_t polarity;

  /** Select a digital filter protection. */
  hal_lptim_filter_t filter;

} hal_lptim_input1_config_t;


/**
  * @brief  LPTIM Input Channel Configuration Structure definition
  */
typedef struct
{
  /** Specify source selected for IC channel.      */
  hal_lptim_ic_src_t source;

  /** Specify the active edge of the input signal. */
  hal_lptim_ic_polarity_t polarity;

  /** Specify the input channel filter.            */
  hal_lptim_filter_t filter;

  /** Specify the input channel prescaler.         */
  hal_lptim_ic_prescaler_t prescaler;

} hal_lptim_ic_config_t;


/**
  * @brief HAL LPTIM Output Channel Configuration
  */
typedef struct
{
  /** Duration (in clock cycles) of the pulse generated on the output channel. */
  uint32_t pulse;

  /** Polarity of the output channel */
  hal_lptim_oc_polarity_t polarity;

} hal_lptim_oc_config_t;


/**
  * @brief HAL LPTIM External Trigger Configuration Structure definition.
  *
  */
typedef struct
{
  /** Specify the external trigger input source.    */
  hal_lptim_ext_trig_src_t source;

  /** Specify the external trigger input polarity.  */
  hal_lptim_ext_trig_polarity_t polarity;

  /** Specify the external trigger input filter (Trigger Sample Time).    */
  hal_lptim_filter_t filter;

} hal_lptim_ext_trig_config_t;


/**
  * @brief HAL LPTIM Encoder Structure Configuration definition.
  *
  * When the Low-Power Timer (LPTIM) is configured in Encoder mode, it operates as follows:
  *     - External Input Signals: The LPTIM uses two external input signals, referred to as Input1 and Input2.
  *     - Clock Signal Generation: These input signals generate a clock signal that is used to clock the
  *         LPTIM counter. The clock source is specified by the parameter HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3].
  *     - Quadrature Encoder Signals: The two signals from quadrature encoders can be filtered to ensure
  *         accurate counting and noise reduction.
  */
typedef struct
{
  /** Selection of the first input of the encoder. */
  hal_lptim_input1_src_t input1;

  /** Selection of the second input of the encoder. */
  hal_lptim_input2_src_t input2;

  /** Filter for the encoder inputs.
      @note The digital filters sensitivity is controlled by groups.
            Therefore, it is not possible to configure each digital
            filter sensitivity separately for input1 and input2. */
  hal_lptim_filter_t filter;

} hal_lptim_encoder_config_t;


/**
  * @brief HAL LPTIM Time Base Configuration Structure definition
  */
typedef struct
{
  /** Clock selection.\n
      Specify the source of the clock feeding the timer's prescaler. */
  hal_lptim_clk_src_t clock_source;

  /** Counter mode selection.\n
      Specify how the counter counts. */
  hal_lptim_mode_t mode;

  /** Specify the prescaler value used to divide the LPTIM clock.\n
      This parameter is valid only if the clock is either
      HAL_LPTIM_CLK_INTERNAL, or  HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS
      (for this last it has no effect).\n
      When the clock is HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS the prescaler division factor
      is set to 1.
      In encoder mode (HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3]) the prescaler
      division factor is set to 1. */
  hal_lptim_clk_src_presc_t prescaler;

  /** Specify the period value to be loaded into the active
      Auto-Reload Register.\n
      This parameter can be a number between Min_Data = 0x0000
      and Max_Data = 0xFFFF. */
  uint32_t period;

  /** Specify the repetition counter value.\n
      If the repetition counter is used, the update event (UEV) is generated
      after upcounting is repeated for the number of times programmed in the
      repetition counter register (RCR).\n
      Else the update event is generated at each counter overflow.
      This parameter must be a number between Min_Data = 0x00 and
      Max_Data = 0xFF.
      @warning When using repetition counter with PRELOAD = 0, LPTIM_RCR register
            must be changed at least five counter cycles before the autoreload
            match event, otherwise an unpredictable behavior is occur.
            Therefore, it is strongly advised to enable preload in order to
            avoid unpredictable behavior when using repetition counter. */
  uint32_t repetition_counter;

  /**
      @note: Counter Trigger selection.
      One external trigger input (LPTIM_ETR) that can be connected to up to 8 different sources.
      After reset or a stop counter, software trigger is enabled (TRIGEN == 00).
      To enable a external trigger, HAL_LPTIM_SetConfigExtTrigInput()
      must be called to configure the external trigger.
  */

} hal_lptim_config_t;
/**
  * @}
  */

/**
  * @}
  */
/* End of exported types ---------------------------------------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Functions LPTIM Exported Functions
  *  @{
  */

/** @defgroup LPTIM_Exported_Functions_Group1 LP Timer Initialization/Deinitialization function
  *  @{
  */
hal_status_t HAL_LPTIM_Init(hal_lptim_handle_t *hlptim, hal_lptim_t instance);
void HAL_LPTIM_DeInit(hal_lptim_handle_t *hlptim);
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
hal_status_t HAL_LPTIM_SetDMA(hal_lptim_handle_t *hlptim,
                              hal_lptim_dma_index_t dma_idx,
                              hal_dma_handle_t *hdma);
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @}
  */


/** @defgroup LPTIM_Exported_Functions_Group2 LP Timer Peripheral State, Error functions
  *           This group gathers the functions for the states and error management.
  *  @{
  */
hal_lptim_state_t HAL_LPTIM_GetState(const hal_lptim_handle_t *hlptim);

hal_lptim_channel_state_t HAL_LPTIM_GetChannelState(const hal_lptim_handle_t *hlptim,
                                                    hal_lptim_channel_t channel);

#if defined (USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)

uint32_t HAL_LPTIM_GetLastErrorCodes(const hal_lptim_handle_t *hlptim);

#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */
/**
  *  @}
  */


/** @defgroup LPTIM_Exported_Functions_Group3 LP Timer Timebase configuration and control.
  *  @{
  */
hal_status_t HAL_LPTIM_SetConfig(hal_lptim_handle_t *hlptim,
                                 const hal_lptim_config_t *p_config);
void HAL_LPTIM_GetConfig(const hal_lptim_handle_t *hlptim,
                         hal_lptim_config_t *p_config);

hal_status_t HAL_LPTIM_SetMode(hal_lptim_handle_t *hlptim,
                               hal_lptim_mode_t mode);
hal_lptim_mode_t HAL_LPTIM_GetMode(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetClockSource(const hal_lptim_handle_t *hlptim,
                                      hal_lptim_clk_src_t clk_src);
hal_lptim_clk_src_t HAL_LPTIM_GetClockSource(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetClockSourcePrescaler(const hal_lptim_handle_t *hlptim,
                                               hal_lptim_clk_src_presc_t clk_src_presc);
hal_lptim_clk_src_presc_t HAL_LPTIM_GetClockSourcePrescaler(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetPeriod(const hal_lptim_handle_t *hlptim,
                                 uint32_t period);
uint32_t HAL_LPTIM_GetPeriod(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetRepetitionCounter(const hal_lptim_handle_t *hlptim,
                                            uint32_t repetition_counter);
uint32_t HAL_LPTIM_GetRepetitionCounter(const hal_lptim_handle_t *hlptim);

uint32_t HAL_LPTIM_GetCounter(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_ResetCounter(const hal_lptim_handle_t *hlptim);
hal_status_t HAL_LPTIM_EnableResetCounterAfterRead(const hal_lptim_handle_t *hlptim);
hal_status_t HAL_LPTIM_DisableResetCounterAfterRead(const hal_lptim_handle_t *hlptim);
hal_lptim_reset_after_read_status_t HAL_LPTIM_IsEnableResetCounterAfterRead(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_EnablePreload(const hal_lptim_handle_t *hlptim);
hal_status_t HAL_LPTIM_DisablePreload(const hal_lptim_handle_t *hlptim);
hal_lptim_preload_status_t HAL_LPTIM_IsEnabledPreload(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetConfigInput1(const hal_lptim_handle_t *hlptim,
                                       const hal_lptim_input1_config_t *p_config);

void HAL_LPTIM_GetConfigInput1(const hal_lptim_handle_t *hlptim,
                               hal_lptim_input1_config_t *p_config);

hal_status_t HAL_LPTIM_SetInput1Source(const hal_lptim_handle_t *hlptim,
                                       hal_lptim_input1_src_t input1_src);
hal_lptim_input1_src_t HAL_LPTIM_GetInput1Source(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetInput1Polarity(const hal_lptim_handle_t *hlptim,
                                         hal_lptim_input1_polarity_t polarity);
hal_lptim_input1_polarity_t HAL_LPTIM_GetInput1Polarity(const hal_lptim_handle_t *hlptim);

/* If filtering is  used, an auxiliary clock  must be active. */
hal_status_t HAL_LPTIM_SetInput1Filter(const hal_lptim_handle_t *hlptim,
                                       hal_lptim_filter_t filter);
hal_lptim_filter_t HAL_LPTIM_GetInput1Filter(const hal_lptim_handle_t *hlptim);

/**
  * @}
  */


/** @defgroup LPTIM_Exported_Functions_Group4 Low power timer starts services functions.
  *
  * @{
  */
hal_status_t HAL_LPTIM_Start(hal_lptim_handle_t *hlptim);
hal_status_t HAL_LPTIM_Stop(hal_lptim_handle_t *hlptim);
hal_status_t HAL_LPTIM_Start_IT(hal_lptim_handle_t *hlptim);
hal_status_t HAL_LPTIM_Stop_IT(hal_lptim_handle_t *hlptim);
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
hal_status_t HAL_LPTIM_Start_DMA_Opt(hal_lptim_handle_t *hlptim,
                                     const void *p_data,
                                     uint32_t size_byte,
                                     uint32_t interrupts);
hal_status_t HAL_LPTIM_Start_DMA(hal_lptim_handle_t *hlptim,
                                 const void *p_data,
                                 uint32_t size_byte);
hal_status_t HAL_LPTIM_Stop_DMA(hal_lptim_handle_t *hlptim);
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @}
  */


/** @defgroup LPTIM_Exported_Functions_Group5 Low power timer Output Channel functions

  * @{
  */
hal_status_t HAL_LPTIM_OC_SetConfigChannel(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           const hal_lptim_oc_config_t *p_config);
void HAL_LPTIM_OC_GetConfigChannel(hal_lptim_handle_t *hlptim,
                                   hal_lptim_channel_t channel,
                                   hal_lptim_oc_config_t *p_config);

hal_status_t HAL_LPTIM_OC_SetChannelPolarity(hal_lptim_handle_t *hlptim,
                                             hal_lptim_channel_t channel,
                                             hal_lptim_oc_polarity_t polarity);
hal_lptim_oc_polarity_t HAL_LPTIM_OC_GetChannelPolarity(const hal_lptim_handle_t *hlptim,
                                                        hal_lptim_channel_t channel);

hal_status_t HAL_LPTIM_OC_SetChannelPulse(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel,
                                          uint32_t pulse);
uint32_t HAL_LPTIM_OC_GetChannelPulse(const hal_lptim_handle_t *hlptim,
                                      hal_lptim_channel_t channel);


hal_status_t HAL_LPTIM_OC_StartChannel(hal_lptim_handle_t *hlptim,
                                       hal_lptim_channel_t channel);
hal_status_t HAL_LPTIM_OC_StopChannel(hal_lptim_handle_t *hlptim,
                                      hal_lptim_channel_t channel);
hal_status_t HAL_LPTIM_OC_StartChannel_IT(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel);
hal_status_t HAL_LPTIM_OC_StopChannel_IT(hal_lptim_handle_t *hlptim,
                                         hal_lptim_channel_t channel);
/**
  *  @}
  */


/** @defgroup LPTIM_Exported_Functions_Group6 Low Power Timer Input Channel functions.
  *  @{
  */
hal_status_t HAL_LPTIM_IC_SetConfigChannel(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           const hal_lptim_ic_config_t *p_config);
void HAL_LPTIM_IC_GetConfigChannel(const hal_lptim_handle_t *hlptim,
                                   hal_lptim_channel_t channel,
                                   hal_lptim_ic_config_t *p_config);

hal_status_t HAL_LPTIM_IC_SetChannelSource(const hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           hal_lptim_ic_src_t source);
hal_lptim_ic_src_t HAL_LPTIM_IC_GetChannelSource(const hal_lptim_handle_t *hlptim,
                                                 hal_lptim_channel_t channel);

hal_status_t HAL_LPTIM_IC_SetChannelPolarity(const hal_lptim_handle_t *hlptim,
                                             hal_lptim_channel_t channel,
                                             hal_lptim_ic_polarity_t polarity);
hal_lptim_ic_polarity_t HAL_LPTIM_IC_GetChannelPolarity(const hal_lptim_handle_t *hlptim,
                                                        hal_lptim_channel_t channel);

hal_status_t HAL_LPTIM_IC_SetChannelFilter(const hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           hal_lptim_filter_t filter);
hal_lptim_filter_t HAL_LPTIM_IC_GetChannelFilter(const hal_lptim_handle_t *hlptim,
                                                 hal_lptim_channel_t channel);

hal_status_t HAL_LPTIM_IC_SetChannelPrescaler(const hal_lptim_handle_t *hlptim,
                                              hal_lptim_channel_t channel,
                                              hal_lptim_ic_prescaler_t prescaler);
hal_lptim_ic_prescaler_t HAL_LPTIM_IC_GetChannelPrescaler(const hal_lptim_handle_t *hlptim,
                                                          hal_lptim_channel_t channel);


hal_status_t HAL_LPTIM_IC_StartChannel(hal_lptim_handle_t *hlptim,
                                       hal_lptim_channel_t channel);
hal_status_t HAL_LPTIM_IC_StopChannel(hal_lptim_handle_t *hlptim,
                                      hal_lptim_channel_t channel);

hal_status_t HAL_LPTIM_IC_StartChannel_IT(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel);
hal_status_t HAL_LPTIM_IC_StopChannel_IT(hal_lptim_handle_t *hlptim,
                                         hal_lptim_channel_t channel);

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
hal_status_t HAL_LPTIM_IC_StartChannel_DMA(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           const void *p_data,
                                           uint32_t size_byte);
hal_status_t HAL_LPTIM_IC_StartChannel_DMA_Opt(hal_lptim_handle_t *hlptim,
                                               hal_lptim_channel_t channel,
                                               const void *p_data,
                                               uint32_t size_byte,
                                               uint32_t interrupts);
hal_status_t HAL_LPTIM_IC_StopChannel_DMA(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel);
#endif /* USE_HAL_LPTIM_DMA */

uint32_t HAL_LPTIM_IC_ReadChannelCapturedValue(const hal_lptim_handle_t *hlptim,
                                               hal_lptim_channel_t channel);
/**
  * @}
  */


/** @defgroup LPTIM_Exported_Functions_Group7 Low Power Timer Encoder functions.
  *  @{
  *
  */
hal_status_t HAL_LPTIM_SetConfigEncoder(const hal_lptim_handle_t *hlptim,
                                        const hal_lptim_encoder_config_t *p_encoder);
void HAL_LPTIM_GetConfigEncoder(const hal_lptim_handle_t *hlptim,
                                hal_lptim_encoder_config_t *p_encoder);

/**
  *  @}
  */


/**
  * @defgroup LPTIM_Exported_Functions_Group8 Config external trigger
  *
  * @{
  *
  */
hal_status_t HAL_LPTIM_SetConfigExtTrigInput(const hal_lptim_handle_t *hlptim,
                                             const hal_lptim_ext_trig_config_t *p_config);
void HAL_LPTIM_GetConfigExtTrigInput(const hal_lptim_handle_t *hlptim,
                                     hal_lptim_ext_trig_config_t *p_config);

hal_status_t HAL_LPTIM_SetExtTrigInputSource(const hal_lptim_handle_t *hlptim,
                                             hal_lptim_ext_trig_src_t source);
hal_lptim_ext_trig_src_t HAL_LPTIM_GetExtTrigInputSource(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetExtTrigInputPolarity(const hal_lptim_handle_t *hlptim,
                                               hal_lptim_ext_trig_polarity_t polarity);
hal_lptim_ext_trig_polarity_t HAL_LPTIM_GetExtTrigInputPolarity(const hal_lptim_handle_t *hlptim);

hal_status_t HAL_LPTIM_SetExtTrigInputFilter(const hal_lptim_handle_t *hlptim,
                                             hal_lptim_filter_t filter);
hal_lptim_filter_t HAL_LPTIM_GetExtTrigInputFilter(const hal_lptim_handle_t *hlptim);
/**
  *  @}
  */


/** @defgroup LPTIM_Exported_Functions_Group9 Low Power Timer IRQ Handler and Callbacks functions
  *  @{
  */

/* Interrupt Handler functions   **************************************************************************************/
void HAL_LPTIM_IRQHandler(hal_lptim_handle_t *hlptim);
void HAL_LPTIM_UPD_IRQHandler(hal_lptim_handle_t *hlptim);
void HAL_LPTIM_CC_IRQHandler(hal_lptim_handle_t *hlptim);
void HAL_LPTIM_TRGI_IRQHandler(hal_lptim_handle_t *hlptim);

/* Declaration for the weak callbacks *********************************************************************************/
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
void HAL_LPTIM_ErrorCallback(hal_lptim_handle_t *hlptim);
void HAL_LPTIM_StopCallback(hal_lptim_handle_t *hlptim);
void HAL_LPTIM_InputCaptureStopCallback(hal_lptim_handle_t *hlptim,
                                        hal_lptim_channel_t channel);
#endif /* USE_HAL_LPTIM_DMA */

void HAL_LPTIM_UpdateCallback(hal_lptim_handle_t *hlptim);

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
void HAL_LPTIM_UpdateHalfCpltCallback(hal_lptim_handle_t *hlptim);
#endif /* USE_HAL_LPTIM_DMA */

void HAL_LPTIM_RepUpdateCallback(hal_lptim_handle_t *hlptim);

void HAL_LPTIM_TriggerCallback(hal_lptim_handle_t *hlptim);

void HAL_LPTIM_InputCaptureCallback(hal_lptim_handle_t *hlptim,
                                    hal_lptim_channel_t channel);

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
void HAL_LPTIM_InputCaptureHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                            hal_lptim_channel_t channel);
#endif /* USE_HAL_LPTIM_DMA */

void HAL_LPTIM_InputOverCaptureCallback(hal_lptim_handle_t *hlptim,
                                        hal_lptim_channel_t channel);

void HAL_LPTIM_CompareMatchCallback(hal_lptim_handle_t *hlptim,
                                    hal_lptim_channel_t channel);

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
void HAL_LPTIM_CompareMatchHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                            hal_lptim_channel_t channel);
#endif /* USE_HAL_LPTIM_DMA */

void HAL_LPTIM_CompareUpdateCallback(hal_lptim_handle_t *hlptim,
                                     hal_lptim_channel_t channel);

void HAL_LPTIM_AutoReloadMatchCallback(hal_lptim_handle_t *hlptim);

void HAL_LPTIM_AutoReloadUpdateCallback(hal_lptim_handle_t *hlptim);

void HAL_LPTIM_DirectionUpCallback(hal_lptim_handle_t *hlptim);

void HAL_LPTIM_DirectionDownCallback(hal_lptim_handle_t *hlptim);

/* Interfaces for registering callbacks *******************************************************************************/
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
hal_status_t HAL_LPTIM_RegisterStopCallback(hal_lptim_handle_t *hlptim,
                                            hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterChannelStopCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_channel_cb_t fct);
hal_status_t HAL_LPTIM_RegisterErrorCallback(hal_lptim_handle_t *hlptim,
                                             hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterUpdateCallback(hal_lptim_handle_t *hlptim,
                                              hal_lptim_cb_t fct);
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
hal_status_t HAL_LPTIM_RegisterUpdateHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                                      hal_lptim_cb_t fct);
#endif /* USE_HAL_LPTIM_DMA */
hal_status_t HAL_LPTIM_RegisterRepUpdateCallback(hal_lptim_handle_t *hlptim,
                                                 hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterTriggerCallback(hal_lptim_handle_t *hlptim,
                                               hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterInputCaptureCallback(hal_lptim_handle_t *hlptim,
                                                    hal_lptim_channel_cb_t fct);
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
hal_status_t HAL_LPTIM_RegisterInputCaptureHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                                            hal_lptim_channel_cb_t fct);
#endif /* USE_HAL_LPTIM_DMA */
hal_status_t HAL_LPTIM_RegisterOverCaptureCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_channel_cb_t fct);
hal_status_t HAL_LPTIM_RegisterCompareMatchCallback(hal_lptim_handle_t *hlptim,
                                                    hal_lptim_channel_cb_t fct);
hal_status_t HAL_LPTIM_RegisterCompareUpdateCallback(hal_lptim_handle_t *hlptim,
                                                     hal_lptim_channel_cb_t fct);
hal_status_t HAL_LPTIM_RegisterAutoReloadUpdateCallback(hal_lptim_handle_t *hlptim,
                                                        hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterAutoReloadMatchCallback(hal_lptim_handle_t *hlptim,
                                                       hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterDirectionUpCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_cb_t fct);
hal_status_t HAL_LPTIM_RegisterDirectionDownCallback(hal_lptim_handle_t *hlptim,
                                                     hal_lptim_cb_t fct);

#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
/**
  *  @}
  */

#if defined (USE_HAL_LPTIM_USER_DATA) && (USE_HAL_LPTIM_USER_DATA == 1)
/** @defgroup LPTIM_Exported_Functions_Group10 Low Power Timer Setter and Getter of the user data.
  *  @{
  */
void HAL_LPTIM_SetUserData(hal_lptim_handle_t *hlptim, const void *p_user_data);
const void *HAL_LPTIM_GetUserData(const hal_lptim_handle_t *hlptim);

/**
  *  @}
  */
#endif /* USE_HAL_LPTIM_USER_DATA */


/** @defgroup LPTIM_Exported_Functions_Group11 Peripheral clock frequency for LPTIMx
  *  @{
  */
uint32_t HAL_LPTIM_GetClockFreq(hal_lptim_handle_t *hlptim);
/**
  *  @}
  */

/**
  * @}
  */
/* End of exported functions -----------------------------------------------------------------------------------------*/

/**
  *  @}
  */

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5xx_HAL_LPTIM_H */
