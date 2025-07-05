/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_lptim.c
  * @brief   LPTIM HAL module driver.
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  *  @{
  */

/** @addtogroup LPTIM
  *  @{

  The LPTIM HAL driver can be used as follows
  ===============

  # (Non optional call) Call HAL_LPTIM_Init(), to initialize the LPTIM driver by establishing a link with
    the LPTIM physical instance.

  # (Non optional call) Call HAL_LPTIM_SetConfig(), to Configure the timebase unit :
      <ul>
        <li> Select the clock source @ref hal_lptim_clk_src_t :
        <ul>
          <li> @ref HAL_LPTIM_CLK_INTERNAL : \n
            LPTIM is clocked by internal clock source
            The counter is incremented following each internal clock pulse
          <li> @ref HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS : \n
            The LPTIM counter clock signal is generated  from the external input 1 signal. \n
            The LPTIM external Input1 is sampled with the internal clock provided to the LPTIM. \n
            LPTIM Input 1 can be configured with @ref HAL_LPTIM_SetConfigInput1(). \n
          <li> @ref HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS : \n
            The LPTIM counter clock signal is generated from the external input1 signal. \n
            The LPTIM external input 1 can be configured by calling HAL_LPTIM_SetConfigInput1() . \n
          <li> @ref HAL_LPTIM_CLK_ENCODER_SUBMODE_1 to @ref HAL_LPTIM_CLK_ENCODER_SUBMODE_3 : \n
            The LPTIM counter clock signal is generated from the two external input signals, input1 and input2.
        </ul>
        <li> Select the <b>prescaler</b> division factor @ref hal_lptim_clk_src_presc_t
        <li> Set <b>period</b> value : number between 0 to 65535 (0x0000 to 0xFFFF)
        <li> set <b>repetition counter</b> value: number between 0 to 255 (0x00 to 0xFF)
        <li> Select the functioning mode with @ref hal_lptim_mode_t :
        <ul>
          <li> @ref HAL_LPTIM_ONE_SHOT :
                When the LPTIM counter is stopped a trigger event starts it.
                The counter is stopped on update event.
          <li> @ref HAL_LPTIM_SET_ONCE :
                A first trigger event starts the LPTIM counter for a single one-shot cycle
          <li> @ref HAL_LPTIM_CONTINUOUS :
                The LPTIM counter starts from trigger event and never stops until the timer is disabled.
          <li> @ref HAL_LPTIM_TIMEOUT :
                The detection of an active edge on one selected trigger input can be used to reset the LPTIM counter.
        </ul>
      </ul>

  # If needed, HAL_LPTIM_DeInit() can be called to reset the driver.

  # When an external clock is used, configure the LPTIM input1 by calling the HAL_LPTIM_SetConfigInput1()
    <ul>
      <li> Select the input1 source with @ref hal_lptim_input1_src_t
      <li> Select the input1 polarity with @ref hal_lptim_input1_polarity_t
      <li> Select the input1 filter with @ref hal_lptim_filter_t
    </ul>

# select your usage :
  - To use LPTIM instance as a simple counter:
  --------------------------------------------
    - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_CONTINUOUS
      when calling HAL_LPTIM_SetConfig() .
    - Start the LPTIM counter, two execution mode are available:
      - Polling : HAL_LPTIM_Start()
      - Interrupt : HAL_LPTIM_Start_IT(), in this case, the update interrupt is enabled
    - Stop the LPTIM counter, call HAL_LPTIM_Stop() and HAL_LPTIM_Stop_IT(), as per selected execution mode.
    @note If needed, some configurations parameters can be changed on the fly (e.g: Period @ref HAL_LPTIM_SetPeriod()).

  - To generate a PWM signal:
  --------------------------------------------
  - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_CONTINUOUS
    when calling HAL_LPTIM_SetConfig() .
  - Configure the output channel(s) by calling HAL_LPTIM_OC_SetConfigChannel() .
  - To start PWM signal generation, first start the output channel, then the LPTIM time base unit
    by calling HAL_LPTIM_Start() .
  Three execution mode are available:
    - Polling : HAL_LPTIM_OC_StartChannel()
    - Interrupt : HAL_LPTIM_OC_StartChannel_IT(), in this case, the compare match interrupt is enabled
  - Stop the PWM signal generation, call HAL_LPTIM_OC_StopChannel() or HAL_LPTIM_OC_StopChannel_IT()
  as per selected execution mode.
  @note If needed, some configurations parameters can be changed on the fly
    (e.g: PWM duty cycle @ref HAL_LPTIM_OC_SetChannelPulse()).

  - To generate a One pulse signal:
  --------------------------------------------
  - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_ONE_SHOT
    when calling HAL_LPTIM_SetConfig() .
  - Configure the output channel(s) by calling HAL_LPTIM_OC_SetConfigChannel() .
  - If the pulse generation is triggered when an active edge is detected on the external trigger input,
    configure the external trigger input by calling the HAL_LPTIM_SetConfigExtTrigInput() .
  - To start pulse generation, first start the output channel(s), then the LPTIM time base unit
    by calling HAL_LPTIM_Start() .
  Three execution mode are available:
    - Polling : HAL_LPTIM_OC_StartChannel()
    - Interrupt : HAL_LPTIM_OC_StartChannel_IT(), in this case, the compare match interrupt is enabled
  - Stop signal generation, call HAL_LPTIM_OC_StopChannel() or HAL_LPTIM_OC_StopChannel_IT()
     as per selected execution mode.
  @note In case of software start (external trigger not configured),
    call HAL_LPTIM_Start() to starts the LPTIM counter for one-shot counting. \n
    In one pulse mode the output waveform is similar to the one of the PWM mode for the first pulse,
      then the output is permanently reset.

  - To generate a set once signal:
  --------------------------------------------
  - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_SET_ONCE
    when calling HAL_LPTIM_SetConfig() .
  - If the signal generation is triggered when an active edge is detected on the external trigger input,
      configure the external trigger input by calling the HAL_LPTIM_SetConfigExtTrigInput() .
  - The output channel(s) must be configured by calling HAL_LPTIM_OC_SetConfigChannel()
  - To start signal generation, first start the channel(s), then the LPTIM time base unit by calling HAL_LPTIM_Start().
  Two execution mode are available:
    - Polling : HAL_LPTIM_OC_StartChannel()
    - Interrupt : HAL_LPTIM_OC_StartChannel_IT(), in this case, the compare match interrupt is enabled
  - Stop signal generation, call HAL_LPTIM_OC_StopChannel() or HAL_LPTIM_OC_StopChannel_IT(),
    as per selected execution mode.
    @note if needed, some configurations parameters can be changed on the fly
      (e.g: PWM duty cycle @ref HAL_LPTIM_OC_SetChannelPulse()).

  - To capture an input signal:
  --------------------------------------------
  - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_CONTINUOUS
    when calling HAL_LPTIM_SetConfig() .
  - The input channel(s) must be configured by calling HAL_LPTIM_IC_SetConfigChannel()
  - To start a capture, first start the input channel, then the LPTIM time base unit (HAL_LPTIM_Start())
  Three execution mode are available:
    - Polling : HAL_LPTIM_IC_StartChannel()
    - Interrupt : HAL_LPTIM_IC_StartChannel_IT(), in this case, the capture interrupt is enabled
    - DMA : HAL_LPTIM_IC_StartChannel_DMA(), in this case, the capture DMA request is enabled
  - Stop input signal capture, call HAL_LPTIM_IC_StopChannel() or HAL_LPTIM_IC_StopChannel_IT()
    or HAL_LPTIM_IC_StopChannel_DMA(),
    as per selected execution mode.

  - To use the LPTIM timeout feature:
  --------------------------------------------
  - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_TIMEOUT
    when calling HAL_LPTIM_SetConfig() .
  - Configure the external trigger input by calling the HAL_LPTIM_SetConfigExtTrigInput() .
  - Configure the timeout value by calling HAL_LPTIM_OC_SetPulse()
  Two execution mode are available:
    - Polling : HAL_LPTIM_Start()
    - Interrupt : HAL_LPTIM_Start_IT(), in this case, the update event is enabled
  - To stop pulse generation, HAL_LPTIM_Stop and HAL_LPTIM_Stop_IT(),
    as per selected execution mode.
    @note if needed, some configurations parameters can be changed on the fly
      (e.g: PWM duty cycle @ref HAL_LPTIM_OC_SetChannelPulse()).

  - To use the LPTIM encoder interface:
  --------------------------------------------
  - Configure LPTIM time base unit. The functioning mode must be set to @ref HAL_LPTIM_CONTINUOUS \n
  and encoder mode must be selected as LPTIM clock source when calling HAL_LPTIM_SetConfig() .
  - The encoder interface (LPTIM input 1 and input 2) must be configured by calling HAL_LPTIM_SetConfigEncoder.
  Two execution mode are available:
    - Polling : HAL_LPTIM_Start()
    - Interrupt : HAL_LPTIM_Start_IT(), in this case, the update event is enabled
  - To stop encoder interface, call HAL_LPTIM_Stop() and HAL_LPTIM_Stop_IT(), as per selected execution mode.
    @note if needed, some configurations parameters can be changed on the fly (e.g: Period @ref HAL_LPTIM_SetPeriod()).

  # Callbacks definition in Interrupt or DMA mode
      - When the compilation define <b>USE_HAL_LPTIM_REGISTER_CALLBACKS</b> is set to 1,
      the user can configure dynamically the driver callbacks, via its own method:

  Callback name                | Default callback                       | Register callback
  -----------------------------|----------------------------------------|----------------------------------------
  ErrorCallback                |  HAL_LPTIM_ErrorCallback               | HAL_LPTIM_RegisterErrorCallback
  StopCallback                 |  HAL_LPTIM_StopCallback                | HAL_LPTIM_RegisterStopCallback
  InputCaptureStopCallback     |  HAL_LPTIM_InputCaptureStopCallback    | HAL_LPTIM_RegisterChannelStopCallback
  UpdateCallback               |  HAL_LPTIM_UpdateCallback              | HAL_LPTIM_RegisterUpdateCallback
  UpdateHalfCpltCallback       |  HAL_LPTIM_UpdateHalfCpltCallback      | HAL_LPTIM_RegisterUpdateHalfCpltCallback
  RepUpdateCallback            |  HAL_LPTIM_RepUpdateCallback           | HAL_LPTIM_RegisterRepUpdateCallback
  TriggerCallback              |  HAL_LPTIM_TriggerCallback             | HAL_LPTIM_RegisterTriggerCallback
  InputCaptureCallback         |  HAL_LPTIM_InputCaptureCallback        | HAL_LPTIM_RegisterInputCaptureCallback
  InputCaptureHalfCpltCallback | HAL_LPTIM_InputCaptureHalfCpltCallback | HAL_LPTIM_RegisterInputCaptureHalfCpltCallback
  InputOverCaptureCallback     |  HAL_LPTIM_InputOverCaptureCallback    | HAL_LPTIM_RegisterOverCaptureCallback
  CompareMatchCallback         |  HAL_LPTIM_CompareMatchCallback        | HAL_LPTIM_RegisterCompareMatchCallback
  CompareUpdateCallback        |  HAL_LPTIM_CompareUpdateCallback       | HAL_LPTIM_RegisterCompareUpdateCallback
  AutoReloadMatchCallback      |  HAL_LPTIM_AutoReloadMatchCallback     | HAL_LPTIM_RegisterAutoReloadMatchCallback
  AutoReloadUpdateCallback     |  HAL_LPTIM_AutoReloadUpdateCallback    | HAL_LPTIM_RegisterAutoReloadUpdateCallback
  DirectionDownCallback        |  HAL_LPTIM_DirectionDownCallback       | HAL_LPTIM_RegisterDirectionDownCallback
  DirectionUpCallback          |  HAL_LPTIM_DirectionUpCallback         | HAL_LPTIM_RegisterDirectionUpCallback

  If one needs to unregister a callback, register the default callback via the registration function.

  By default, after the HAL_LPTIM_Init() and when the state is @ref HAL_LPTIM_STATE_INIT, all callbacks are set to the
  corresponding default weak functions.

  Callbacks can be registered in handle global_state @ref HAL_LPTIM_STATE_INIT and @ref HAL_LPTIM_STATE_IDLE.

  When the compilation define <b>USE_HAL_LPTIM_REGISTER_CALLBACKS</b> is set to 0 or not defined,
  the callback registration
  feature is not available and weak callbacks are used, represented by the default value in the table above.

  ## Configuration inside the HAL LPTIM driver:

  Config defines                   | Where        | Default value     | Note
  -------------------------------  | -------------| ------------------| -------------------------------------------
  USE_HAL_LPTIM_MODULE             | hal_conf.h   |         1         | Enable the HAL LPTIM module
  USE_HAL_LPTIM_REGISTER_CALLBACKS | hal_conf.h   |         0         | Allow user to define his own callback
  USE_HAL_LPTIM_CLK_ENABLE_MODEL   | hal_conf.h   | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
  USE_HAL_LPTIM_USER_DATA          | hal_conf.h   |         0         | Add an user data inside HAL LPTIM handle
  USE_HAL_LPTIM_GET_LAST_ERRORS    | hal_conf.h   |         0         | Enable retrieving last processes error codes
  USE_HAL_LPTIM_DMA                | hal_conf.h   |         1         | Enable DMA code inside HAL LPTIM
  USE_HAL_CHECK_PARAM              | hal_conf.h   |         0         | Enable checking of vital parameters at runtime
  USE_HAL_MUTEX                    | hal_conf.h   |         0         | Enable the use of semaphore in the HAL driver
  USE_HAL_CHECK_PROCESS_STATE      | hal_conf.h   |         0         | Enable atomic access to process state check
  USE_ASSERT_DBG_PARAM             | PreProc env  |        NONE       | Enable check parameters for HAL
  USE_ASSERT_DBG_STATE             | PreProc env  |        NONE       | Enable check state for HAL

  **********************************************************************************************************************

  */

#if defined(USE_HAL_LPTIM_MODULE) && (USE_HAL_LPTIM_MODULE == 1)

/** @defgroup LPTIM_Private_Types LPTIM Private Types
  *  @{
  */

/**
  * @brief Alias for the CMSIS instance type definition
  */
typedef LPTIM_TypeDef lptim_t;

/**
  *  @}
  */

/** @defgroup LPTIM_Private_Constants  LPTIM Private Constants
  *  @{
  */
/**
  * @brief Timeout
  */
#define LPTIM_TIMEOUT 50

/**
  * @brief LL LPTIM Channels lookup table (indexes are given by hal_lptim_channel_t)
  */
static const uint32_t ll_lptim_channels[] =
{
  LL_LPTIM_CHANNEL_CH1,
  LL_LPTIM_CHANNEL_CH2,
};

typedef struct
{
  uint32_t ll_value;
  hal_lptim_t instance;
  union
  {
    hal_lptim_ext_trig_src_t  exttrig_src;
    hal_lptim_ic_src_t   channel_src;
  };
} lptim_mapping_t;

static lptim_mapping_t extrig_mapping[] =
{
  /* GPIO applies to all compatible instances */
  {0x00000000UL, (hal_lptim_t)0xFFFF, {.exttrig_src = HAL_LPTIM_EXT_TRIG_GPIO}},

  /* ALRA_TRG applies to all compatible instances*/
  {LL_LPTIM_TRIG_SOURCE_RTCALARMA, (hal_lptim_t)0xFFFF, {.exttrig_src = HAL_LPTIM_EXT_TRIG_RTC_ALMA_TRG}},

  /* ALRB_TRG applies to all compatible instances */
  {LL_LPTIM_TRIG_SOURCE_RTCALARMB, (hal_lptim_t)0xFFFF, {.exttrig_src = HAL_LPTIM_EXT_TRIG_RTC_ALMB_TRG}},

  {LL_LPTIM_TRIG_SOURCE_RTCTAMP1, HAL_LPTIM1, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG1}},
  {LL_LPTIM_TRIG_SOURCE_RTCTAMP1, HAL_LPTIM2, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG1}},
  {LL_LPTIM_TRIG_SOURCE_RTCTAMP1, HAL_LPTIM3, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG1}},
  {LL_LPTIM_TRIG_SOURCE_LPDMA_CH0_TCF, HAL_LPTIM4, {.exttrig_src = HAL_LPTIM_EXT_TRIG_LPDMA_CH0_TC}},

  {LL_LPTIM_TRIG_SOURCE_RTCTAMP2, HAL_LPTIM1, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG2}},
  {LL_LPTIM_TRIG_SOURCE_GPDMA_CH0_TCF, HAL_LPTIM2, {.exttrig_src = HAL_LPTIM_EXT_TRIG_GPDMA_CH0_TC}},
  {LL_LPTIM_TRIG_SOURCE_LPDMA_CH1_TCF, HAL_LPTIM3, {.exttrig_src = HAL_LPTIM_EXT_TRIG_LPDMA_CH1_TC}},
  {LL_LPTIM_TRIG_SOURCE_RTCTAMP2, HAL_LPTIM4, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG2}},

  {LL_LPTIM_TRIG_SOURCE_LPDMA_CH2_TCF, HAL_LPTIM1, {.exttrig_src = HAL_LPTIM_EXT_TRIG_LPDMA_CH2_TC}},
  {LL_LPTIM_TRIG_SOURCE_GPDMA_CH4_TCF, HAL_LPTIM2, {.exttrig_src = HAL_LPTIM_EXT_TRIG_GPDMA_CH4_TC}},
  {LL_LPTIM_TRIG_SOURCE_RTCTAMP3, HAL_LPTIM3, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG3}},
  {LL_LPTIM_TRIG_SOURCE_RTCTAMP3, HAL_LPTIM4, {.exttrig_src = HAL_LPTIM_EXT_TRIG_TAMP_TRG3}},

  /* COMP1 applies to all compatible instances */
  {LL_LPTIM_TRIG_SOURCE_COMP1, (hal_lptim_t)0xFFFF, {.exttrig_src = HAL_LPTIM_EXT_TRIG_COMP1}},

  /* COMP2 applies to all compatible instances */
  {LL_LPTIM_TRIG_SOURCE_COMP2, (hal_lptim_t)0xFFFF, {.exttrig_src = HAL_LPTIM_EXT_TRIG_COMP2}},

  /* End of map */
  {.ll_value = 0xFFFFFFFFU}
};


static lptim_mapping_t ic1_mapping[] =
{
  {LL_LPTIM_LPTIM1_IC1_RMP_GPIO, HAL_LPTIM1, {.channel_src = HAL_LPTIM_INPUT_GPIO}},
  {LL_LPTIM_LPTIM2_IC1_RMP_GPIO, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_GPIO}},
  {LL_LPTIM_LPTIM3_IC1_RMP_GPIO, HAL_LPTIM3, {.channel_src = HAL_LPTIM_INPUT_GPIO}},

  {LL_LPTIM_LPTIM1_IC1_RMP_COMP1, HAL_LPTIM1, {.channel_src = HAL_LPTIM_INPUT_COMP1}},
  {LL_LPTIM_LPTIM2_IC1_RMP_COMP1, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_COMP1}},
  {LL_LPTIM_LPTIM3_IC1_RMP_COMP1, HAL_LPTIM3, {.channel_src = HAL_LPTIM_INPUT_COMP1}},

#if defined(COMP2)
  {LL_LPTIM_LPTIM1_IC1_RMP_COMP2, HAL_LPTIM1, {.channel_src = HAL_LPTIM_INPUT_COMP2}},
  {LL_LPTIM_LPTIM2_IC1_RMP_COMP2, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_COMP2}},
  {LL_LPTIM_LPTIM3_IC1_RMP_COMP2, HAL_LPTIM3, {.channel_src = HAL_LPTIM_INPUT_COMP2}},
#endif /* COMP2 */

  /* End of map */
  {.ll_value = 0xFFFFFFFFU}
};

static lptim_mapping_t ic2_mapping[] =
{
  {LL_LPTIM_LPTIM1_IC2_RMP_GPIO, HAL_LPTIM1, {.channel_src = HAL_LPTIM_INPUT_GPIO}},
  {LL_LPTIM_LPTIM1_IC2_RMP_LSI, HAL_LPTIM1, {.channel_src = HAL_LPTIM_INPUT_LSI}},
  {LL_LPTIM_LPTIM1_IC2_RMP_LSE, HAL_LPTIM1, {.channel_src = HAL_LPTIM_INPUT_LSE}},

  {LL_LPTIM_LPTIM2_IC2_RMP_GPIO, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_GPIO}},
  {LL_LPTIM_LPTIM2_IC2_RMP_HSI, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_HSI_256}},
  {LL_LPTIM_LPTIM2_IC2_RMP_MSIS_1024, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_MSI_1024}},
  {LL_LPTIM_LPTIM2_IC2_RMP_MSIS_4, HAL_LPTIM2, {.channel_src = HAL_LPTIM_INPUT_MSI_4}},

  {LL_LPTIM_LPTIM3_IC2_RMP_GPIO, HAL_LPTIM3, {.channel_src = HAL_LPTIM_INPUT_GPIO}},

  /* End of map */
  {.ll_value = 0xFFFFFFFFU}
};


/**
  * @brief Define channel state idle, whether it is an OC or an IC channel
  */
#define LPTIM_CHANNEL_STATE_IDLE \
  (HAL_LPTIM_OC_CHANNEL_STATE_IDLE | HAL_LPTIM_IC_CHANNEL_STATE_IDLE)

/**
  * @brief Mask for the clock source prescaler.
  */
#define LPTIM_CLOCK_SOURCE_PRESCALER_MASK \
  LPTIM_CFGR_PRESC

/**
  * @brief Mask for the polarity bits of of the clock
  */
#define LPTIM_CLOCK_POLARITY_MASK \
  (LL_LPTIM_CLK_POLARITY_FALLING | LL_LPTIM_CLK_POLARITY_RISING_FALLING)

/**
  * @brief Mask for the filter bits of the clock
  */
#define LPTIM_CLOCK_FILTER_SHIFT 3U
/**
  * @brief Mask for the filter bits of the clock with shift
  */
#define LPTIM_CLOCK_FILTER_MASK (3U << LPTIM_CLOCK_FILTER_SHIFT)

/**
  * @brief Mask for the source bits in CFGR of the external trigger
  */
#define LPTIM_ETR_SRC_MASK LPTIM_CFGR_TRIGSEL_Msk

/**
  * @brief Mask for the polarity bits in CFGR of the external trigger
  */
#define LPTIM_ETR_POLARITY_MASK LL_LPTIM_TRIG_POLARITY_RISING_FALLING

/**
  * @brief Mask for the filter bits of of the input trigger
  */
#define LPTIM_ETR_FILTER_SHIFT 6U
/**
  * @brief Mask for the filter bits of of the input trigger with shift
  */
#define LPTIM_ETR_FILTER_MASK (3U << LPTIM_ETR_FILTER_SHIFT)

/**
  * @brief Mask to know if the clock source is internal, external or encoder.
  * The mask let us select the ENC, the COUNTMODE and the CKSEL of the
  * CFGR register.
  */
#define LPTIM_CLOCK_TYPE_MASK       \
  (LL_LPTIM_CLK_SOURCE_EXTERNAL   | \
   LL_LPTIM_COUNTER_MODE_EXTERNAL | \
   LL_LPTIM_ENCODER_MODE_ENABLE)

/**
  * @brief List of all flags interrupt
  */
#define LPTIM_FLAG_ALL    \
  (LL_LPTIM_ISR_CC1OF   | \
   LL_LPTIM_ISR_CC2OF   | \
   LL_LPTIM_ISR_CC1IF   | \
   LL_LPTIM_ISR_CC2IF   | \
   LL_LPTIM_ISR_CMP1OK  | \
   LL_LPTIM_ISR_CMP2OK  | \
   LL_LPTIM_ISR_DIEROK  | \
   LL_LPTIM_ISR_REPOK   | \
   LL_LPTIM_ISR_UE      | \
   LL_LPTIM_ISR_DOWN    | \
   LL_LPTIM_ISR_UP      | \
   LL_LPTIM_ISR_ARROK   | \
   LL_LPTIM_ISR_EXTTRIG | \
   LL_LPTIM_ISR_ARRM)

/**
  *  @}
  */

/** @defgroup  LPTIM_Private_Macros LPTIM Private Macros
  *  @{
  */

/**
  * @brief Check if Flag is active
  */
#define IS_LPTIM_ACTIVEFLAG(reg, bitState) \
  ((READ_BIT(reg, bitState) == bitState) ? 1UL : 0UL)

/**
  * @brief Check an interrupt flag in the status register
  */
#define LPTIM_IS_INTERRUPT_FLAG(sr_reg, flag) \
  (((sr_reg) & flag) == flag)

/**
  * @brief Check that an interrupt is enabled or not
  */
#define LPTIM_IS_ENABLED_IT(ie_reg, it) \
  (((ie_reg) & it) == it)

/**
  * @brief Check channel output Compare corresponding to channel available
  */
#define IS_LPTIM_CC_CHANNEL(instance, channel) \
  ((((channel) == HAL_LPTIM_CHANNEL_1)         \
    && IS_LPTIM_CC1_INSTANCE((instance)))      \
   || (((channel) == HAL_LPTIM_CHANNEL_2)      \
       && IS_LPTIM_CC2_INSTANCE((instance))))

/**
  * @brief Is timeout period expired
  */
#define LPTIM_TIMEOUT_PERIOD_EXPIRED(delta_ticks) \
  ((delta_ticks) > (uint32_t)LPTIM_TIMEOUT)

/**
  * @brief Access the LPTIM instance from the handle
  *
  */
#define LPTIM_INSTANCE(hlptim) ((lptim_t *)((uint32_t)((hlptim)->instance)))

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)

/**
  * @brief Interrupt state activated
  */
#define LPTIM_STATE_ACTIVE(interrupts) \
  HAL_LPTIM_STATE_ACTIVE |             \
  ((((interrupts) & HAL_DMA_OPT_IT_SILENT) == HAL_DMA_OPT_IT_SILENT) ? LPTIM_ACTIVE_SILENT : LPTIM_ACTIVE_NOT_SILENT)

/**
  * @brief Input capture channel state activated
  */
#define LPTIM_IC_CHANNEL_STATE_ACTIVE(interrupts) \
  ((IS_BIT_SET((interrupts), (uint32_t)HAL_DMA_OPT_IT_SILENT)) ? \
   HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE_SILENT : HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE)

/**
  * @brief Offset with channel tab for filter configuration
  */
#define  LPTIM_OFFSET_TAB_FILTER(filter, channel)\
  filter << LL_LPTIM_SHIFT_TAB_ICxF[channel];

/**
  * @brief Offset with channel tab for filter configuration
  */
#define  LPTIM_OFFSET_TAB_POLARITY(filter, channel)\
  filter << LL_LPTIM_SHIFT_TAB_ ICxPSC[channel];

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/**
  * @brief Check LPTIM data transfer by DMA in silent mode: DMA must be in circular mode
  */
#define IS_LPTIM_DMA_VALID_SILENT_MODE(handle, channel, interrupts) \
  (((interrupts) == HAL_LPTIM_OPT_DMA_IT_SILENT)                    \
   && (handle->hdma[channel]->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR) ? 0U : 1U)

#endif /* USE_HAL_DMA_LINKEDLIST */
/**
  * @brief Check if DMA is set by SILENT Mode
  */
#define IS_LPTIM_ACTIVE_SILENT(state) \
  ((uint32_t)(state) & (uint32_t)LPTIM_ACTIVE_SILENT)

#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief Is LPTIM Channel exist on chip
  */
#define IS_LPTIM_CHANNEL(channel)     \
  (((channel) == HAL_LPTIM_CHANNEL_1) \
   || ((channel) == HAL_LPTIM_CHANNEL_2))

/**
  * @brief Is LPTIM Channel exist on chip
  */
#if defined(COMP2)
#define IS_LPTIM_CHANNEL_SRC(src)         \
  (((src) == HAL_LPTIM_INPUT_GPIO) \
   || ((src) == HAL_LPTIM_INPUT_LSI) \
   || ((src) == HAL_LPTIM_INPUT_LSE) \
   || ((src) == HAL_LPTIM_INPUT_COMP1) \
   || ((src) == HAL_LPTIM_INPUT_COMP2) \
   || ((src) == HAL_LPTIM_INPUT_HSI_256) \
   || ((src) == HAL_LPTIM_INPUT_MSI_1024) \
   || ((src) == HAL_LPTIM_INPUT_MSI_4))
#else
#define IS_LPTIM_CHANNEL_SRC(src)         \
  (((src) == HAL_LPTIM_INPUT_GPIO) \
   || ((src) == HAL_LPTIM_INPUT_LSI) \
   || ((src) == HAL_LPTIM_INPUT_LSE) \
   || ((src) == HAL_LPTIM_INPUT_COMP1) \
   || ((src) == HAL_LPTIM_INPUT_HSI_256) \
   || ((src) == HAL_LPTIM_INPUT_MSI_1024) \
   || ((src) == HAL_LPTIM_INPUT_MSI_4))
#endif /* COMP2 */

/**
  * @brief Check input1 polarity
  */
#define IS_LPTIM_INPUT1_POLARITY(polarity)     \
  (((polarity) == HAL_LPTIM_INPUT1_RISING)     \
   || ((polarity) == HAL_LPTIM_INPUT1_FALLING) \
   || ((polarity) == HAL_LPTIM_INPUT1_RISING_FALLING))

/**
  * @brief Check input1 source
  */

#define IS_LPTIM_INPUT1_SRC(src) \
  (((src) == HAL_LPTIM_INPUT1_GPIO)\
   || ((src) == HAL_LPTIM_INPUT1_COMP1))

/**
  * @brief Check input2 source
  */
#define IS_LPTIM_INPUT2_SRC(src)       \
  (((src) == HAL_LPTIM_INPUT2_GPIO) \
   || ((src) == HAL_LPTIM_INPUT2_COMP2))

/**
  * @brief Check clock encoder
  */
#define IS_LPTIM_CLK_ENCODER(src)                \
  (((src) == HAL_LPTIM_CLK_ENCODER_SUBMODE_1)    \
   || ((src) == HAL_LPTIM_CLK_ENCODER_SUBMODE_2) \
   || ((src) == HAL_LPTIM_CLK_ENCODER_SUBMODE_3))

/**
  * @brief Check clock source
  */
#define IS_LPTIM_CLK_SRC(instance, src)              \
  (((src) == HAL_LPTIM_CLK_INTERNAL)                 \
   || ((src) == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS)  \
   || ((src) == HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS) \
   || (IS_LPTIM_CLK_ENCODER(src)                     \
       && (IS_LPTIM_ENCODER_INTERFACE_INSTANCE(instance))))

/**
  * @brief Check clock source is External
  */
#define IS_LPTIM_EXTERNAL_CLK_SRC(instance, src) \
  ((src) == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS)  \
  || ((src) == HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS)

/**
  * @brief Check the clock source prescaler.
  * When the clock source is either HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS
  * or HAL_LPTIM_CLK_ENCODER_SUBMODE_x the internal clock provided to
  * the LPTIM must not be prescaled.
  */
#define IS_LPTIM_CLK_SRC_PRESC(clock_source, prescaler)   \
  (((clock_source == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS)) \
   || (IS_LPTIM_CLK_ENCODER(clock_source))                \
   ? ((prescaler) == HAL_LPTIM_CLK_SRC_DIV1)              \
   : (((prescaler) == HAL_LPTIM_CLK_SRC_DIV1)             \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV2)          \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV4)          \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV8)          \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV16)         \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV32)         \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV64)         \
      || ((prescaler) == HAL_LPTIM_CLK_SRC_DIV128)))

/**
  * @brief Check clock mode
  */
#define IS_LPTIM_MODE(clock_source, mode) \
  ((IS_LPTIM_CLK_ENCODER(clock_source)) ? ((mode) == HAL_LPTIM_CONTINUOUS) : (((mode) == HAL_LPTIM_ONE_SHOT)      \
                                                                              || ((mode) == HAL_LPTIM_SET_ONCE)   \
                                                                              || ((mode) == HAL_LPTIM_CONTINUOUS) \
                                                                              || ((mode) == HAL_LPTIM_TIMEOUT)))

/**
  * @brief Check Period
  */
#define IS_LPTIM_PERIOD(period) \
  (((period) > 0U) && ((period) <= 0x0000FFFFU))

/**
  * @brief Check the value to store in the repetition counter register (RCR).
  */
#define IS_LPTIM_REPETITION_COUNTER(rep) \
  ((rep) <= 0x000000FFU)

/**
  * @brief Check DMA Index.
  */
#define IS_LPTIM_DMA_INDEX(idx)       \
  (((idx) == HAL_LPTIM_DMA_ID_UPDATE) \
   || ((idx) == HAL_LPTIM_DMA_ID_CC1) \
   || ((idx) == HAL_LPTIM_DMA_ID_CC2))

/**
  * @brief Check external trigger LPTIM1.
  */
#define IS_LPTIM1_EXT_TRIG_SRC(src)              \
  (((src) == HAL_LPTIM_EXT_TRIG_GPIO) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMA_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMB_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG2) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP2) \
   || ((src) == HAL_LPTIM_EXT_TRIG_LPDMA_CH2_TC))

/**
  * @brief Check external trigger LPTIM2.
  */
#define IS_LPTIM2_EXT_TRIG_SRC(src)              \
  (((src) == HAL_LPTIM_EXT_TRIG_GPIO) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMA_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMB_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP2) \
   || ((src) == HAL_LPTIM_EXT_TRIG_GPDMA_CH0_TC) \
   || ((src) == HAL_LPTIM_EXT_TRIG_GPDMA_CH4_TC))

/**
  * @brief Check external trigger LPTIM3.
  */
#define IS_LPTIM3_EXT_TRIG_SRC(src)              \
  (((src) == HAL_LPTIM_EXT_TRIG_GPIO) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMA_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMB_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG3) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP2) \
   || ((src) == HAL_LPTIM_EXT_TRIG_LPDMA_CH1_TC))


/**
  * @brief Check external trigger LPTIM4.
  */
#define IS_LPTIM4_EXT_TRIG_SRC(src)              \
  (((src) == HAL_LPTIM_EXT_TRIG_GPIO) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMA_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_RTC_ALMB_TRG) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG2) \
   || ((src) == HAL_LPTIM_EXT_TRIG_TAMP_TRG3) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP1) \
   || ((src) == HAL_LPTIM_EXT_TRIG_COMP2) \
   || ((src) == HAL_LPTIM_EXT_TRIG_LPDMA_CH1_TC))

/**
  * @brief Check external trigger.
  */

#define IS_LPTIM_EXT_TRIG_SRC(instance, src)                   \
  (((((instance) == LPTIM1_NS) || ((instance) == LPTIM1_S)) \
    && IS_LPTIM1_EXT_TRIG_SRC((src))) \
   ((((instance) == LPTIM2_NS) || ((instance) == LPTIM2_S)) \
    && IS_LPTIM2_EXT_TRIG_SRC((src))))

/**
  * @brief Check Input capture prescaler.
  */
#define IS_LPTIM_IC_PRESCALER(prescaler) \
  (((prescaler) == HAL_LPTIM_IC_DIV1)    \
   || ((prescaler) == HAL_LPTIM_IC_DIV2) \
   || ((prescaler) == HAL_LPTIM_IC_DIV4) \
   || ((prescaler) == HAL_LPTIM_IC_DIV8))

/**
  * @brief Check External trigger.
  */
#define IS_LPTIM_EXT_TRIG_POLARITY(polarity) \
  (((polarity) == HAL_LPTIM_TRIG_RISING)     \
   || ((polarity) == HAL_LPTIM_TRIG_FALLING) \
   || ((polarity) == HAL_LPTIM_TRIG_RISING_FALLING))

/**
  * @brief Check trigger Selection.
  */
#define IS_LPTIM_TRIG_SEL(sel)  \
  (((sel) == HAL_LPTIM_TRIG_SW) \
   || ((sel) == HAL_LPTIM_TRIG_HW))

/**
  * @brief Check Filter Divider.
  */
#define IS_LPTIM_FILTER(filter)        \
  (((filter) == HAL_LPTIM_FDIV1)       \
   || ((filter) == HAL_LPTIM_FDIV1_N2) \
   || ((filter) == HAL_LPTIM_FDIV1_N4) \
   || ((filter) == HAL_LPTIM_FDIV1_N8))

/**
  * @brief Check Output compare Pulse.
  */
#define IS_LPTIM_OC_PULSE(pulse) \
  (((pulse) > 0x0U) && ((pulse) <= 0xFFFFU))

/**
  * @brief Check Output compare Polarity.
  */
#define IS_LPTIM_OC_POLARITY(polarity) \
  (((polarity) == HAL_LPTIM_OC_HIGH)   \
   || ((polarity) == HAL_LPTIM_OC_LOW))

/**
  * @brief Check Input capture Polarity.
  */
#define IS_LPTIM_IC_POLARITY(polarity)     \
  (((polarity) == HAL_LPTIM_IC_RISING)     \
   || ((polarity) == HAL_LPTIM_IC_FALLING) \
   || ((polarity) == HAL_LPTIM_IC_RISING_FALLING))

/**
  * @brief Check if the clock source is set to external.
  */
#define IS_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS(clk) \
  ((((clk) & LL_LPTIM_CLK_SOURCE_EXTERNAL) != 0U) ? 1U : 0U)

/**
  * @brief Check if the clock type is encoder.
  */
#define IS_LPTIM_CLOCK_TYPE_ENCODER(clk_type) \
  ((((clk_type) & LL_LPTIM_ENCODER_MODE_ENABLE) != 0U) ? 1U : 0U)

/**
  * @brief Extract the clock type (internal, external, encoder) from CFGR register.
  */
#define LPTIM_GET_CLOCK_TYPE(cfgr) \
  ((uint32_t)((cfgr) & LPTIM_CLOCK_TYPE_MASK))

/**
  * @brief Extract the clock filter from instance.CFGR register.
  */
#define LPTIM_GET_CLOCK_FILTER(instance) \
  (uint32_t)(LL_LPTIM_GetClockFilter(instance) >> LPTIM_CFGR_CKFLT_Pos)

/**
  * @brief Convert clock filter from HAL to LL.
  */
#define LPTIM_CFGR_HAL2LL_FILTER(filter) \
  (uint32_t)(filter << LPTIM_CFGR_CKFLT_Pos)

/**
  * @brief Convert input capture filter from HAL to LL.
  */
#define LPTIM_CCMR1_HAL2LL_FILTER(filter) \
  (uint32_t)(filter << LPTIM_CCMR1_IC1F_Pos)

/**
  * @brief Convert input capture filter from LL to HAL.
  */
#define LPTIM_CCMR1_LL2HAL_FILTER(filter) \
  (uint32_t)(filter >> LPTIM_CCMR1_IC1F_Pos)

/**
  * @brief Extract the clock polarity from instance.CFGR register
  *
  */
#define LPTIM_GET_CLOCK_POLARITY(instance) \
  ((uint32_t)(LL_LPTIM_GetClockPolarity(instance)))

/**
  * @brief Extract the clock prescaler from CFGR register
  */
#define LPTIM_GET_CLOCK_SOURCE_PRESCALER(instance) \
  ((uint32_t)(LL_LPTIM_GetPrescaler(instance)))

/**
  * @brief Extract the ETR source from CFGR
  *
  */
#define LPTIM_GET_ETR_SOURCE(cfgr) \
  ((uint32_t)(((cfgr) & LPTIM_ETR_SRC_MASK)))

/**
  * @brief Extract the ETR filter value from CFGR
  *
  */
#define LPTIM_GET_ETR_FILTER(cfgr) \
  ((uint32_t)(((cfgr) & LPTIM_ETR_FILTER_MASK)))

/**
  * @brief Extract the ETR polarity from CFGR
  *
  */
#define LPTIM_GET_ETR_POLARITY(cfgr) \
  ((uint32_t)((cfgr) & LPTIM_ETR_POLARITY_MASK))

/**
  * @brief Reset the clock prescaler from CFGR register
  *
  */
#define LPTIM_RESET_CLOCK_SOURCE_PRESCALER(cfgr) \
  ((cfgr) &= ~(uint32_t)(LPTIM_CLOCK_SOURCE_PRESCALER_MASK))

/**
  * @brief Mask for the mode in CFGR.
  *
  */
#define LPTIM_MODE_CFGR_MASK \
  (LL_LPTIM_OC_WAVEFORM_SETONCE | LPTIM_CFGR_TIMOUT)

/**
  * @brief Mask for the mode in CR.
  *
  */
#define LPTIM_MODE_CR_MASK \
  (LL_LPTIM_OPERATING_MODE_ONESHOT | LL_LPTIM_OPERATING_MODE_CONTINUOUS)

/**
  * @brief Get the low power timer handle registered in the dma handle
  */
#define LPTIM_GET_HDMA_PARENT(hdma) \
  (hal_lptim_handle_t *)((hdma)->p_parent)

/**
  *  @}
  */

/** @defgroup LPTIM_Private_Functions LPTIM Private Functions
  *  @{
  */

#if defined(USE_HAL_LPTIM_CLK_ENABLE_MODEL) && (USE_HAL_LPTIM_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
/**
  * @brief  Clock enabling for a particular instance.
  * @param  instance HAL LPTIM instance
  */
__STATIC_FORCEINLINE void LPTIM_EnableClock(hal_lptim_t instance)
{
  switch (instance)
  {
    case HAL_LPTIM1:
      HAL_RCC_LPTIM1_EnableClock();
      break;
    case HAL_LPTIM2:
      HAL_RCC_LPTIM2_EnableClock();
      break;
    case HAL_LPTIM3:
      HAL_RCC_LPTIM3_EnableClock();
      break;
    case HAL_LPTIM4:
      HAL_RCC_LPTIM4_EnableClock();
      break;
    default:
      break;
  }
}
#endif /* USE_HAL_LPTIM_CLK_ENABLE_MODEL */

/**
  * @brief Wait for a given flag.
  * @param p_lptim           Pointer to CMSIS Instance
  * @param ll_lptim_is_active_flag           Is flag active
  * @warning that is the responsibility of the caller to clear the flag.
  * @return return state of flag
  * @retval 1    flag not activate
  * @retval 0    flag is correctly activate
  */
static uint32_t lptim_wait_flag(const lptim_t *p_lptim,
                                uint32_t (*ll_lptim_is_active_flag)(const lptim_t *p_lptim))
{
  uint32_t tickstart = HAL_GetTick();
  uint8_t isActiveFlag = 0;

  while (isActiveFlag == 0U)
  {
    isActiveFlag = ll_lptim_is_active_flag(p_lptim);
    if (LPTIM_TIMEOUT_PERIOD_EXPIRED(HAL_GetTick() - tickstart))
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (isActiveFlag == 0U)
      {
        return 1;
      }
    }
  }
  return 0;
}

/**
  * @brief Disable LPTIM HW instance.
  * @param p_lptim           Pointer to CMSIS Instance
  * @note  The following sequence is required to solve LPTIM disable HW limitation.
  *         Please check Errata Sheet ES0335 for more details under "MCU remain
  *         stuck in LPTIM interrupt when entering Stop mode" section.
  * @retval None
  */
__STATIC_INLINE hal_status_t LPTIM_CcDisable(lptim_t *p_lptim)
{
  /* save LPTIM Config */
  lptim_t cpyInstance = *p_lptim;

  /* Enter critical section */
  uint32_t primask_bit = __get_PRIMASK();
  __set_PRIMASK(1);

  switch ((uint32_t)p_lptim)
  {
    case HAL_LPTIM1:
      HAL_RCC_LPTIM1_Reset();
      break;
    case HAL_LPTIM2:
      HAL_RCC_LPTIM2_Reset();
      break;
    case HAL_LPTIM3:
      HAL_RCC_LPTIM3_Reset();
      break;
    case HAL_LPTIM4:
      HAL_RCC_LPTIM4_Reset();
      break;
    default:
      break;
  }

  uint32_t DIER_reg = LL_LPTIM_READ_REG(&cpyInstance, DIER);
  uint32_t ARR_reg = LL_LPTIM_READ_REG(&cpyInstance, ARR);

  if (DIER_reg != 0U || ARR_reg != 0U)
  {
    LL_LPTIM_Enable(p_lptim);
    LL_LPTIM_WRITE_REG(p_lptim, DIER, LL_LPTIM_READ_REG(&cpyInstance, DIER));
    if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
    {
      return HAL_ERROR;
    }
    LL_LPTIM_SetAutoReload(p_lptim, LL_LPTIM_READ_REG(&cpyInstance, ARR));
    if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_ARROK) != 0U)
    {
      return HAL_ERROR;
    }
    LL_LPTIM_Disable(p_lptim);
  }

  LL_LPTIM_OC_SetCompareCH1(p_lptim, LL_LPTIM_READ_REG(&cpyInstance, CCR1));
  LL_LPTIM_OC_SetCompareCH2(p_lptim, LL_LPTIM_READ_REG(&cpyInstance, CCR2));
  LL_LPTIM_SetRepetition(p_lptim, LL_LPTIM_READ_REG(&cpyInstance, RCR));
  LL_LPTIM_WRITE_REG(p_lptim, CFGR, LL_LPTIM_READ_REG(&cpyInstance, CFGR));
  LL_LPTIM_WRITE_REG(p_lptim, CFGR2, LL_LPTIM_READ_REG(&cpyInstance, CFGR2));
  LL_LPTIM_WRITE_REG(p_lptim, CCMR1, LL_LPTIM_READ_REG(&cpyInstance, CCMR1));

  /* Restore LPTIM_Config */
  __set_PRIMASK(primask_bit);
  return HAL_OK;
}

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
/**
  * @brief  Callbacks initialization function.
  * @param hlptim Pointer to the handle of the LPTIM instance.
  */
__STATIC_FORCEINLINE void LPTIM_InitCallbacks(hal_lptim_handle_t *hlptim)
{
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /* LPTIM Error Callback */
  hlptim->error_callback = HAL_LPTIM_ErrorCallback;

  hlptim->stop_callback = HAL_LPTIM_StopCallback;

  hlptim->input_capture_stop_callback = HAL_LPTIM_InputCaptureStopCallback;
#endif /* USE_HAL_LPTIM_DMA */

  /* LPTIM Period Elapsed Callback */
  hlptim->update_callback = HAL_LPTIM_UpdateCallback;

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /* LPTIM Period Elapsed half complete Callback */
  hlptim->update_half_cplt_callback = HAL_LPTIM_UpdateHalfCpltCallback;
#endif /* USE_HAL_LPTIM_DMA */

  /* LPTIM Auto Reload Update Callback */
  hlptim->auto_reload_update_callback = HAL_LPTIM_AutoReloadUpdateCallback;

  /* LPTIM Auto Reload Match Callback */
  hlptim->auto_reload_match_callback = HAL_LPTIM_AutoReloadMatchCallback;

  /* LPTIM Repetition Update Callback */
  hlptim->rep_update_callback = HAL_LPTIM_RepUpdateCallback;

  /* LPTIM Trigger Callback */
  hlptim->trigger_callback = HAL_LPTIM_TriggerCallback;

  /* LPTIM Output Compare Delay Elapsed Callback */
  hlptim->compare_match_callback = HAL_LPTIM_CompareMatchCallback;

  /* LPTIM Output Compare Update Callback */
  hlptim->compare_update_callback = HAL_LPTIM_CompareUpdateCallback;

  /* LPTIM Input Capture Callback */
  hlptim->input_capture_callback = HAL_LPTIM_InputCaptureCallback;

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
  /* LPTIM Input Capture half complete Callback */
  hlptim->input_capture_half_cplt_callback = HAL_LPTIM_InputCaptureHalfCpltCallback;
#endif /* USE_HAL_LPTIM_DMA */

  /* LPTIM Over capture Callback */
  hlptim->input_over_capture_callback = HAL_LPTIM_InputOverCaptureCallback;

  /* LPTIM Direction UP Change Callback */
  hlptim->direction_up_callback = HAL_LPTIM_DirectionUpCallback;

  /* LPTIM Direction DOWN Change Callback */
  hlptim->direction_down_callback = HAL_LPTIM_DirectionDownCallback;
}
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */

/**
  * @brief Convert External Trigger sources to ll value.
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param exttrig_src External Trigger sources need to be convert to ll .
  * @param LL value selector .
  * @return @ref hal_lptim_ext_trig_src_t
  */
__STATIC_INLINE uint32_t LPTIM_ConvertHALToLLExttrig(const hal_lptim_handle_t *hlptim,
                                                     hal_lptim_ext_trig_src_t exttrig_src)
{
  uint32_t trigsel = LL_LPTIM_TRIG_SOURCE_GPIO;
  uint32_t i = 0;

  while (extrig_mapping[i].ll_value != 0xFFFF)
  {
    if (extrig_mapping[i].exttrig_src == exttrig_src
        && (extrig_mapping[i].instance == 0xFFFF
            || extrig_mapping[i].instance == hlptim->instance))
    {
      trigsel = extrig_mapping[i].ll_value;
      break;
    }
    ++i;
  }
  return trigsel;
}

/**
  * @brief Convert ll External trigger source to HAL source value.
  * @param hlptim             Pointer to a hal_lptim_handle_t
  * @param trigsel LL value needed to convert into external_trigger source.
  * @return @ref hal_lptim_ext_trig_src_t
  */
__STATIC_INLINE hal_lptim_ext_trig_src_t LPTIM_ConvertLLToHALExttrig(const hal_lptim_handle_t *hlptim,
                                                                     uint32_t trigsel)
{
  hal_lptim_ext_trig_src_t exttrig_src = HAL_LPTIM_EXT_TRIG_GPIO;
  uint32_t i = 0;

  while (extrig_mapping[i].ll_value != 0xFFFFU)
  {
    if (extrig_mapping[i].ll_value == trigsel
        && (extrig_mapping[i].instance == 0xFFFF
            || extrig_mapping[i].instance == hlptim->instance))
    {
      exttrig_src = extrig_mapping[i].exttrig_src;
      break;
    }
    ++i;
  }

  return exttrig_src;
}

/**
  * @brief Convert input channel sources to ll value.
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel LPTIM Channels identifier.
  * @param channel_src Input channel sources need to be convert to ll.
  * @return LL value selector
  */
__STATIC_INLINE uint32_t LPTIM_ConvertHALToLLIcx(const hal_lptim_handle_t *hlptim,
                                                 hal_lptim_channel_t channel,
                                                 hal_lptim_ic_src_t channel_src)
{
  uint32_t icxsel = 0x00000000UL; /*ICx_GPIO */
  uint32_t i = 0;
  lptim_mapping_t *icx_mapping = NULL;

  switch (channel)
  {
    case HAL_LPTIM_CHANNEL_1:
      icx_mapping = ic1_mapping;
      break;
    case HAL_LPTIM_CHANNEL_2:
      icx_mapping = ic2_mapping;
      break;
    default:
      break;
  }

  while (icx_mapping[i].ll_value != 0xFFFFU)
  {
    if (icx_mapping[i].channel_src == channel_src
        && (icx_mapping[i].instance == 0xFFFF
            || icx_mapping[i].instance == hlptim->instance))
    {
      icxsel = icx_mapping[i].ll_value;
      break;
    }
    ++i;
  }
  return icxsel;
}

/**
  * @brief Convert ll input source to HAL channel input source value.
  * @param hlptim             Pointer to a hal_lptim_handle_t
  * @param value LL value for channel input sources .
  * @param channel Output Channel to check convert .
  * @return @ref hal_lptim_ic_src_t
  */
__STATIC_INLINE hal_lptim_ic_src_t LPTIM_ConvertLLToHALIcx(const hal_lptim_handle_t *hlptim,
                                                           hal_lptim_channel_t channel,
                                                           uint32_t icxsel)
{
  uint32_t i = 0;
  hal_lptim_ic_src_t channel_src = HAL_LPTIM_INPUT_GPIO;
  lptim_mapping_t *icx_mapping = NULL;

  switch (channel)
  {
    case HAL_LPTIM_CHANNEL_1:
      icx_mapping = ic1_mapping;
      break;
    case HAL_LPTIM_CHANNEL_2:
      icx_mapping = ic2_mapping;
      break;
    default:
      break;
  }

  while (icx_mapping[i].ll_value != 0xFFFFU)
  {
    if (icx_mapping[i].ll_value == icxsel
        && (icx_mapping[i].instance == 0xFFFF
            || icx_mapping[i].instance == hlptim->instance))
    {
      channel_src = icx_mapping[i].channel_src;
      break;
    }
    ++i;
  }
  return channel_src;

}

/**
  * @brief Set the clock.
  * Update the fields of CFGR register:
  *  - COUNTMODE,
  *  - CKSEL,
  *  - PRESC,
  *    Note: setting the prescaler is done whether it is meaningful or not and
  *          whether it is 'legal' or not (i.e. an assert in the caller must check
  *          that prescaler is 0 if an internal clock is provided to sample an input.
  *          (i.e. whenever the clock source is neither HAL_LPTIM_CLK_INTERNAL nor
  *          HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS.)
  *          (see the macro IS_LPTIM_CLK_SRC_PRESC)
  *  - CKPOL Only if in encoder mode (clock_source == HAL_LPTIM_CLK_ENCODER_SUBMODE_x))
  *
  * The LPTIM_CFGR register must only be modified when the LPTIM is disabled
  * which is guaranteed due to the fact that the config is done either in state
  * HAL_LPTIM_STATE_INIT or HAL_LPTIM_STATE_IDLE.
  * @param p_lptim           Pointer to CMSIS Instance
  * @param clk_src Clock source mode.
  * @param prescaler Clock source prescaler divider.
  */
__STATIC_INLINE void LPTIM_SetClock(lptim_t *p_lptim,
                                    hal_lptim_clk_src_t clk_src,
                                    hal_lptim_clk_src_presc_t prescaler)
{
  /* Configure the clock. */
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);

  /* Reset CKSEL (which is set to 1 only when clk_src is
     HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS. */
  cfgr &= ~((uint32_t)(HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS));

  /* Reset COUNTMODE. */
  cfgr &= ~LL_LPTIM_COUNTER_MODE_EXTERNAL;

  if (IS_LPTIM_CLOCK_TYPE_ENCODER((uint32_t)clk_src) == 1U)
  {
    /* Reset the polarity. */
    cfgr &= ~LPTIM_CLOCK_POLARITY_MASK;
  }

  cfgr |= (uint32_t)clk_src;
  cfgr |= (uint32_t)prescaler;

  LL_LPTIM_WRITE_REG(p_lptim, CFGR, cfgr);
}

/**
  * @brief Get the clock source and prescaler value
  * @param p_lptim           Pointer to CMSIS Instance
  * @param p_clk_src           Return clock source value
  * @param p_prescaler           Return prescaler value
  */
__STATIC_INLINE void LPTIM_GetClock(const lptim_t *p_lptim,
                                    hal_lptim_clk_src_t *p_clk_src,
                                    hal_lptim_clk_src_presc_t *p_prescaler)
{
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);
  uint32_t clk_src = (uint32_t)LPTIM_GET_CLOCK_TYPE(cfgr);

  if (IS_LPTIM_CLOCK_TYPE_ENCODER((uint32_t)clk_src) == 1U)
  {
    /* For the encoder mode the polarity gives the submode. */
    clk_src |= (cfgr & LPTIM_CLOCK_POLARITY_MASK);

    /* COUNTMODE force clean... */
    clk_src &= ~LL_LPTIM_COUNTER_MODE_EXTERNAL;

    clk_src &= (cfgr | LPTIM_CFGR_CKPOL_Pos);

  }
  else
  {
    if (IS_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS((uint32_t)clk_src) == 1U)
    {
      /* Just to make sure that LL_LPTIM_COUNTER_MODE_EXTERNAL is 0. */
      clk_src &= ~LL_LPTIM_COUNTER_MODE_EXTERNAL;
    }
  }

  *p_clk_src = (hal_lptim_clk_src_t)clk_src;
  *p_prescaler = (hal_lptim_clk_src_presc_t)LPTIM_GET_CLOCK_SOURCE_PRESCALER(p_lptim);
}

/**
  * @brief Set the clock source (LPTIM is supposed to be disabled)
  * @param p_lptim           Pointer to CMSIS Instance
  * @param clk_src           Config clock source
  */
__STATIC_FORCEINLINE void LPTIM_SetClkSrc(lptim_t *p_lptim, hal_lptim_clk_src_t clk_src)
{
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);
  uint32_t clk_tmp = (uint32_t)clk_src;

  /* Reset CKSEL (which is set to 1 only when clk_src is
     HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS */
  cfgr &= ~((uint32_t)(HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS));

  /* Reset COUNTMODE */
  cfgr &= ~LL_LPTIM_COUNTER_MODE_EXTERNAL;

  if (IS_LPTIM_CLOCK_TYPE_ENCODER((uint32_t)clk_tmp) == 1U)
  {
    /* Reset the polarity. */
    cfgr &= ~LPTIM_CLOCK_POLARITY_MASK;
  }

  cfgr |= (uint32_t)clk_src;

  /* If the clock source is HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or
     HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3] the prescaler must be
     HAL_LPTIM_CLK_SRC_DIV1 (that is 000). */
  if (((hal_lptim_clk_src_t)clk_src == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS)
      || (IS_LPTIM_CLOCK_TYPE_ENCODER((uint32_t)clk_tmp) == 1U))
  {
    LPTIM_RESET_CLOCK_SOURCE_PRESCALER(cfgr);
  }

  LL_LPTIM_WRITE_REG(p_lptim, CFGR, cfgr);
}

/**
  * @brief Get the clock source
  * @param p_lptim           Pointer to CMSIS Instance
  * @return @ref hal_lptim_clk_src_t
  */
__STATIC_FORCEINLINE hal_lptim_clk_src_t LPTIM_GetClkSrc(const lptim_t *p_lptim)
{
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);
  uint32_t clk_src = LPTIM_GET_CLOCK_TYPE(cfgr);

  if (IS_LPTIM_CLOCK_TYPE_ENCODER(clk_src) == 1U)
  {
    /* For the encoder mode the polarity gives the submode. */
    clk_src |= (cfgr & LPTIM_CLOCK_POLARITY_MASK);

    /* COUNTMODE is meanigless */
    clk_src &= ~LL_LPTIM_COUNTER_MODE_EXTERNAL;
  }
  else
  {
    if (IS_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS(clk_src) == 1U)
    {
      /* Just to make sure that LL_LPTIM_COUNTER_MODE_EXTERNAL is 0. */
      clk_src &= ~LL_LPTIM_COUNTER_MODE_EXTERNAL;
    }
  }

  return (hal_lptim_clk_src_t)clk_src;
}

/**
  * @brief Set the clock source prescaler
  * @param p_lptim           Pointer to CMSIS Instance
  * @param clk_src_presc     Config source prescaler
  * @warning
  * - it is the caller's responsibility to check the validity of this prescaler setting
  *      see macro IS_LPTIM_CLK_SRC_PRESC.
  * - LPTIM is disabled
  */
__STATIC_FORCEINLINE void LPTIM_SetClkSrcPresc(lptim_t *p_lptim,
                                               hal_lptim_clk_src_presc_t clk_src_presc)
{
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);

  LPTIM_RESET_CLOCK_SOURCE_PRESCALER(cfgr);

  cfgr |= (uint32_t)clk_src_presc;
  LL_LPTIM_WRITE_REG(p_lptim, CFGR, cfgr);
}

/**
  * @brief Set output channel pulse
  * @param p_lptim           Pointer to CMSIS Instance
  * @param channel       Output channel of interest to enable.
  * @param pulse         Config pulse.
  * @retval     1            Flag can't be writing
  * @retval     0            No error
  */
static uint32_t LPTIM_OC_SetPulse(lptim_t *p_lptim,
                                  hal_lptim_channel_t channel,
                                  uint32_t pulse)
{
  /* LPTIM has to be disabled to modify CFGR, so we store the state and
  set it back once the operation is done. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  /* LPTIM has to be enabled to modify ARR. */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  if (channel == HAL_LPTIM_CHANNEL_1)
  {
    /* Clear the compare register 1 update flag */
    LL_LPTIM_WRITE_REG(p_lptim, ICR, LL_LPTIM_ISR_CMP1OK);

    /* Write to CCR1 register the pulse value */
    LL_LPTIM_OC_SetCompareCH1(p_lptim, pulse);
    if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_CMP1OK) != 0U)
    {
      return 1;
    }
  }
  else /* HAL_LPTIM_CHANNEL_2 */
  {
    /* Clear the compare register 2 update flag */
    LL_LPTIM_WRITE_REG(p_lptim, ICR, LL_LPTIM_ISR_CMP2OK);

    /* Write to CCR2 register the pulse value */
    LL_LPTIM_OC_SetCompareCH2(p_lptim, pulse);
    if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_CMP2OK) != 0U)
    {
      return 1;
    }
  }

  /* If it was disable, stop LPTIM. */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  return 0;
}

/**
  * @brief Get pulse Input channel.
  * @param p_lptim           Pointer to CMSIS Instance
  * @param channel       Output channel of interest to enable.
  * @return pulsation of input channel
  */
__STATIC_FORCEINLINE uint32_t LPTIM_OC_GetPulse(lptim_t *p_lptim,
                                                hal_lptim_channel_t channel)
{
  if (channel == HAL_LPTIM_CHANNEL_1)
  {
    return LL_LPTIM_OC_GetCompareCH1(p_lptim);
  }
  else
  {
    return LL_LPTIM_OC_GetCompareCH2(p_lptim);
  }
}

/**
  * @brief Start mode chosen
  * @param      p_lptim      Pointer to the handler of the LPTIM instance.
  * @param      mode         Mode clock start (list mode here : @ref hal_lptim_mode_t).
  * @retval     1            error, clock encoder init but continuous mode set
  * @retval     0            No Error
  *
  */
static uint32_t LPTIM_Start(lptim_t *p_lptim, uint32_t mode)
{
  /* LPTIM is supposed to be disabled but we still do it. */
  LL_LPTIM_Disable(p_lptim);

  /* Check the mode is compatible with the clock.
   * If the clock source is HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3] then
   * the mode has to be HAL_LPTIM_CONTINUOUS.
   * If the mode is HAL_LPTIM_TIMEOUT any clock source but
   * HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3] is valid.
   */
  /* Reset/set the WAVE bit and reset/set the TIMOUT bit in CFGR. */
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);

  if ((IS_LPTIM_CLOCK_TYPE_ENCODER(LPTIM_GET_CLOCK_TYPE(cfgr)) == 1U) && (mode != (uint32_t)HAL_LPTIM_CONTINUOUS))
  {
    return 1;
  }

  cfgr &= ~LPTIM_MODE_CFGR_MASK;
  cfgr |= (mode & LPTIM_MODE_CFGR_MASK);
  LL_LPTIM_WRITE_REG(p_lptim, CFGR, cfgr);

  return 0;
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)

/**
  * @brief  Get the channel associated to a DMA handler
  * @param  hlptim Pointer to the handle of the LPTIM instance.
  * @param  hdma Pointer to the handle of the DMA instance.
  * @return @ref hal_lptim_channel_t Channel number of handler
  */
__STATIC_INLINE hal_lptim_channel_t LPTIM_GetCCxDmaHandler(hal_lptim_handle_t *hlptim,
                                                           hal_dma_handle_t *hdma)
{
  if (hdma == hlptim->hdma[HAL_LPTIM_DMA_ID_CC1])
  {
    return HAL_LPTIM_CHANNEL_1;
  }
  else
  {
    return HAL_LPTIM_CHANNEL_2;
  }
}


/**
  * @brief Capture half complete
  * @param hdma Pointer to the DMA Handler.
  */
static void LPTIM_DMACaptureHalfcpltCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

  /* Identify the channel */
  hal_lptim_channel_t channel = LPTIM_GetCCxDmaHandler(hlptim, hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->input_capture_half_cplt_callback(hlptim, channel);
#else
  HAL_LPTIM_InputCaptureHalfCpltCallback(hlptim, channel);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
}

/**
  * @brief Capture complete
  * @param hdma       Pointer to the DMA Handler.
  *
  */
static void LPTIM_DMACaptureCpltCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

  /* Identify the channel */
  hal_lptim_channel_t channel = LPTIM_GetCCxDmaHandler(hlptim, hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->input_capture_callback(hlptim, channel);
#else
  HAL_LPTIM_InputCaptureCallback(hlptim, channel);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
}

/**
  * @brief DMA transfer error callback.
  * @param hdma Pointer to the DMA Handler.
  *
  */
static void LPTIM_DMAErrorCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->error_callback(hlptim);
#else
  HAL_LPTIM_ErrorCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
}

/**
  * @brief DMA transfer stopped callback when triggered by a lptimer update event.
  * @param hdma Pointer to the DMA Handler.
  *
  */
static void LPTIM_DMAStopCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->stop_callback(hlptim);
#else
  HAL_LPTIM_StopCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
}

/**
  * @brief DMA data transfer aborted callback.
  * @param hdma Pointer to the DMA Handler.
  *
  */
static void LPTIM_DMAAbortCallback(hal_dma_handle_t *hdma)
{
  hdma->p_xfer_abort_cb = NULL;
}

/**
  * @brief Callback dma stop Channel
  * @param hdma Pointer to the DMA Handler.
  *
  */
static void LPTIM_DMAChannelStopCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

  /* Identify the channel */
  hal_lptim_channel_t channel = LPTIM_GetCCxDmaHandler(hlptim, hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->input_capture_stop_callback(hlptim, channel);
#else
  HAL_LPTIM_InputCaptureStopCallback(hlptim, channel);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
}

/**
  * @brief Callback dma update half complete
  * @param  hdma  Pointer to the DMA handle.
  *
  */
static void LPTIM_DMAUpdateHalfcpltCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->update_half_cplt_callback(hlptim);
#else
  HAL_LPTIM_UpdateHalfCpltCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
}

/**
  * @brief Callback dma update complete
  * @param  hdma  Pointer to the DMA handle.
  *
  */
static void LPTIM_DMAUpdateCpltCallback(hal_dma_handle_t *hdma)
{
  hal_lptim_handle_t *hlptim = LPTIM_GET_HDMA_PARENT(hdma);

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  hlptim->update_callback(hlptim);
#else
  HAL_LPTIM_UpdateCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
}

/**
  * @brief  Start dma with interrupts
  * @param  hlptim       Pointer handle LPTIM.
  * @param  p_data       Pointer to p_data.
  * @param  size_byte    Size of p_data.
  * @param  interrupts  Selection of the DMA interrupts. \n
  *                     Can be any of (meaningful) those values:
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_NONE
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_HT
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_DEFAULT
  * @if (USE_HAL_DMA_LINKEDLIST)
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_SILENT
  * @endif
  * @retval HAL_ERROR    DMA is not started
  * @retval HAL_OK       DMA start correctly
  */
static hal_status_t LPTIM_Start_DMA_Opt(hal_lptim_handle_t *hlptim,
                                        const void *p_data,
                                        uint32_t size_byte,
                                        uint32_t interrupts)
{

  hal_dma_handle_t *hdma = hlptim->hdma[HAL_LPTIM_DMA_ID_UPDATE];
  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM((hdma != NULL));


  /* LPTIM has to be enabled to modify DIER, so we store the state and
  set it back once the operation is done. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  LL_LPTIM_EnableDMAReq_UPDATE(p_lptim);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  ASSERT_DBG_PARAM(IS_LPTIM_DMA_VALID_SILENT_MODE(hlptim, HAL_LPTIM_DMA_ID_UPDATE, interrupts));
#endif /* USE_HAL_DMA_LINKEDLIST */

  /* Set DMA channel callback function pointers */
  hdma->p_xfer_halfcplt_cb = LPTIM_DMAUpdateHalfcpltCallback;
  hdma->p_xfer_cplt_cb = LPTIM_DMAUpdateCpltCallback;
  hdma->p_xfer_error_cb = LPTIM_DMAErrorCallback;
  hdma->p_xfer_abort_cb = LPTIM_DMAAbortCallback;

  /* Start DMA transfer in IT mode: from Memory to ARR register */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hdma, (uint32_t)p_data,
                                     (uint32_t)((uint32_t *)(&p_lptim->ARR)),
                                     size_byte, interrupts) != HAL_OK)
  {
#if defined(USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)
    hlptim->last_error_codes |= HAL_LPTIM_ERROR_DMA;
#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */

    hlptim->global_state = HAL_LPTIM_STATE_IDLE;

    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
  * @brief  IC start channel with DMA and interrupts
  * @param  hlptim       Pointer to a hal_lptim_handle_t
  * @param  channel      Channel id.
  * @param  p_data       Pointer to p_data.
  * @param  size_byte    Size of p_data.
  * @param  interrupts  Selection of the DMA interrupts. \n
  *                     Can be any of (meaningful) those values:
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_NONE
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_HT
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_DEFAULT
  * @if (USE_HAL_DMA_LINKEDLIST)
  *                     - @ref HAL_LPTIM_OPT_DMA_IT_SILENT
  * @endif
  * @retval HAL_ERROR    Input channel with DMA and interrupts is not start correctly
  * @retval HAL_OK       Input channel with DMA and interrupts start correctly
  */
__STATIC_INLINE hal_status_t LPTIM_IC_StartChannel_DMA_Opt(hal_lptim_handle_t *hlptim,
                                                           hal_lptim_channel_t channel,
                                                           const void *p_data,
                                                           uint32_t size_byte,
                                                           uint32_t interrupts)
{
  hal_dma_handle_t *hdma;
  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  typedef struct
  {
    uint32_t id_dma;
    uint32_t src_addr;
    void (*lptim_enable_dma_cb)(lptim_t *);
  } lptim_mapping_dma_t;

  lptim_mapping_dma_t mapping_dma[] =
  {
    {HAL_LPTIM_DMA_ID_CC1, (uint32_t)((uint32_t *)(&p_lptim->CCR1)), LL_LPTIM_EnableDMAReq_CC1},
    {HAL_LPTIM_DMA_ID_CC2, (uint32_t)((uint32_t *)(&p_lptim->CCR2)), LL_LPTIM_EnableDMAReq_CC2},
  };

  /* Temporary enable the peripheral to modify DIER impact by EnableDMAReq. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);
  LL_LPTIM_Enable(p_lptim);

  hdma = hlptim->hdma[mapping_dma[(uint32_t)channel].id_dma];

  ASSERT_DBG_PARAM((hdma != NULL));
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  ASSERT_DBG_PARAM(IS_LPTIM_DMA_VALID_SILENT_MODE(hlptim, mapping_dma[(uint32_t)channel].id_dma, interrupts));
#endif /* USE_HAL_DMA_LINKEDLIST */

  /* Set DMA channel callback function pointers */
  hdma->p_xfer_halfcplt_cb = LPTIM_DMACaptureHalfcpltCallback;
  hdma->p_xfer_cplt_cb = LPTIM_DMACaptureCpltCallback;
  hdma->p_xfer_error_cb = LPTIM_DMAErrorCallback;

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hdma,
                                     mapping_dma[(uint32_t)channel].src_addr,
                                     (uint32_t)p_data,
                                     size_byte, interrupts) != HAL_OK)
  {
#if defined(USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)
    hlptim->last_error_codes |= HAL_LPTIM_ERROR_DMA;
#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */
    hlptim->channel_states[channel] = HAL_LPTIM_IC_CHANNEL_STATE_IDLE;
    return HAL_ERROR;
  }

  mapping_dma[(uint32_t)channel].lptim_enable_dma_cb(p_lptim);

  /* if LPTIM was not enable, disabled it */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  /* Enable channel */
  LL_LPTIM_CC_EnableChannel(p_lptim, channel);

  return HAL_OK;

}

/**
  * @brief  Abort any ongoing DMA channel transfer.
  * @param  hlptim     Pointer to the handle of the TIM instance.
  * @param  dma_idx  DMA handle index
  * @param  active_silent_mode  Status of the silent mode.
  */
__STATIC_INLINE void LPTIM_Abort_DMA(hal_lptim_handle_t *hlptim,
                                     hal_lptim_dma_index_t dma_idx,
                                     uint32_t active_silent_mode)
{
  hal_dma_cb_t xfer_abort_cb;
  hal_dma_handle_t *hdma = hlptim->hdma[dma_idx];

  ASSERT_DBG_PARAM((hdma != NULL));

  if (active_silent_mode == LPTIM_ACTIVE_SILENT)
  {
    (void)HAL_DMA_Abort(hdma);

    return;
  }

  /* dma stop callback function pointer depends on the dma request source */
  if (dma_idx == HAL_LPTIM_DMA_ID_UPDATE)
  {
    xfer_abort_cb = LPTIM_DMAStopCallback;
  }
  else
  {
    xfer_abort_cb = LPTIM_DMAChannelStopCallback;
  }

  hdma->p_xfer_abort_cb = xfer_abort_cb;
  if (HAL_DMA_Abort_IT(hdma) != HAL_OK)
  {
    xfer_abort_cb(hdma);
  }
}

/**
  * @brief Stop a lptimer's channel that was started in DMA mode.
  * @param hlptim   Pointer to a hal_lptim_handle_t
  * @param p_lptim  Pointer to CMSIS Instance
  * @param channel  Channel number to disable.
  * @param active_silent_mode Active silent mode.
  */
static void LPTIM_IC_StopChannel_DMA(hal_lptim_handle_t *hlptim,
                                     lptim_t *p_lptim,
                                     hal_lptim_channel_t channel,
                                     uint32_t active_silent_mode)
{
  typedef struct
  {
    hal_lptim_dma_index_t id_dma;
    void (*lptim_disable_dma_cb)(lptim_t *);
  } lptim_mapping_dma_t;

  lptim_mapping_dma_t mapping_dma[] =
  {
    {HAL_LPTIM_DMA_ID_CC1, LL_LPTIM_DisableDMAReq_CC1},
    {HAL_LPTIM_DMA_ID_CC2, LL_LPTIM_DisableDMAReq_CC2},
  };

  /* Disable capture/compare channel match DMA request */
  mapping_dma[(uint32_t)channel].lptim_disable_dma_cb(p_lptim);

  /* Abort DMA */
  LPTIM_Abort_DMA(hlptim,
                  mapping_dma[(uint32_t)channel].id_dma,
                  active_silent_mode);

}

#endif /* USE_HAL_LPTIM_DMA */

/**
  *  @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup LPTIM_Exported_Functions
  *  @{
  */

/** @addtogroup LPTIM_Exported_Functions_Group1
  *  @{
     This section provides a set of function allowing to:
    - Initialize and deinitialize LPTIM with HAL_LPTIM_Init() and HAL_LPTIM_DeInit()
    - Associate DMA channels to LPTIM DMA requests with HAL_LPTIM_SetDMA()
  */

/**
  * @brief  Initialization function.
  *         Initialize the LPTIM handle and associate an instance.
  * @param  hlptim     Pointer to the handler of the LPTIM instance.
  * @param  instance   One of the values of the hal_lptim_t enumeration.
  * @retval HAL_OK
  * @retval HAL_INVALID_PARAM Input parameter is invalid
  *                           (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_Init(hal_lptim_handle_t *hlptim, hal_lptim_t instance)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM(IS_LPTIM_INSTANCE((lptim_t *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hlptim == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the LPTIM instance */
  hlptim->instance = instance;

#if defined(USE_HAL_LPTIM_CLK_ENABLE_MODEL) && (USE_HAL_LPTIM_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  LPTIM_EnableClock(instance);
#endif /* USE_HAL_LPTIM_CLK_ENABLE_MODEL */

#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
  LPTIM_InitCallbacks(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */

  /* Init the handle internal parameters */

#if defined(USE_HAL_LPTIM_USER_DATA) && (USE_HAL_LPTIM_USER_DATA == 1)
  hlptim->p_user_data = NULL;
#endif /* USE_HAL_LPTIM_USER_DATA */

  /* Reset channels state */
  for (uint32_t i = 0; i < HAL_LPTIM_CHANNELS; ++i)
  {
    hlptim->channel_states[i] = HAL_LPTIM_CHANNEL_STATE_RESET;
  }

#if defined(USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)
  hlptim->last_error_codes = HAL_LPTIM_ERROR_NONE;
#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */

  hlptim->global_state = HAL_LPTIM_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief   Reset function.\n
  *          Stop all current operations and reset states.\n
  *          Hence: \n
  *          @arg stop the counter
  *          @arg disable interrupts / DMA transfers
  *          @arg clear status flags
  *          @arg set channels' states to RESET
  *          @arg set global state to RESET
  *
  * @param   hlptim  Pointer to the handler of the LPTIM instance.
  * @retval  HAL_OK Operation completes successfully
  * @retval  HAL_ERROR In case of timeout.
  * @warning Be careful if you used an external clock to have called HAL_LPTIM_SetConfigInput1() before Deinit!
  */
void HAL_LPTIM_DeInit(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_INSTANCE(p_lptim));

  /* Temporary enable the peripheral to modify DIER. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  /* Clean CCMR1 if supported by the instance */
  if (IS_LPTIM_CC2_INSTANCE(p_lptim))
  {
    LL_LPTIM_WRITE_REG(p_lptim, CCMR1, 0U);
  }

  /* Clear all flags */
  LL_LPTIM_WRITE_REG(p_lptim, ICR, LPTIM_FLAG_ALL);

  /* Disable all interrupts:
   * 1. Clear all interrupt flags (already done)
   * 2. Disable interrupts (reset DIER to 0).
   * 3. Wait for the completion of the writing operation (reading ISR register).
   *    In case of success, clear the flag (this is done at the end).
   */
  LL_LPTIM_WRITE_REG(p_lptim, DIER, 0U);

  /* Clear CCR1:
   * 1. Clear the Compare register 1 update flag (CMP1OK) (already done)
   * 2. Reset CCR1 to 0.
   * 3. Wait for the completion of the writing operation (reading ISR register).
   *    In case of success, clear the flag (this is done at the end).
   */

  LL_LPTIM_WRITE_REG(p_lptim, CCR1, 0U);

  /* Clear CCR2 if supported by the instance:
   * 1. Clear the Compare register 2 update flag (CMP2OK) (already done)
   * 2. Reset CCR2 to 0.
   * 3. Wait for the completion of the writing operation (reading ISR register).
   *    In case of success, clear the flag (this is done at the end).
   */
  if (IS_LPTIM_CC2_INSTANCE(p_lptim))
  {
    LL_LPTIM_WRITE_REG(p_lptim, CCR2, 0U);
  }

  /* Reset ARR:
   * 1. Clear the autoreload register update flag (ARROK) (already done)
   * 2. Reset ARR to 0.
   * 3. Wait for the completion of the writing operation (reading ISR register).
   *    In case of success, clear the flag (this is done at the end).
   */
  LL_LPTIM_SetAutoReload(p_lptim, 0U);

  /* Clear previously set flags (DIEROK, CMP1OK, CMP2OK, ARROK). */
  LL_LPTIM_WRITE_REG(p_lptim, ICR, LPTIM_FLAG_ALL);

  /* Disable the LPTIM instance */
  LL_LPTIM_Disable(p_lptim);

  /* Reset the config registers.
     This means among other thing that LPTIM counter is not started
     by an external trigger (TRIGEN reset to 00)
   */
  LL_LPTIM_WRITE_REG(p_lptim, CFGR, 0U);
  LL_LPTIM_WRITE_REG(p_lptim, CFGR2, 0U);

  /* Reset channels state */
  for (uint32_t i = 0; i < HAL_LPTIM_CHANNELS; ++i)
  {
    uint32_t ll_channel = ll_lptim_channels[i];
    LL_LPTIM_CC_DisableChannel(p_lptim, ll_channel);
    hlptim->channel_states[i] = HAL_LPTIM_CHANNEL_STATE_RESET;
  }

  /* Reset global state */
  hlptim->global_state = HAL_LPTIM_STATE_RESET;
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)

/**
  * @brief Link a DMA handle to a DMA request.
  * @param hlptim     Pointer to the handle of the LPTIM instance.
  * @param dma_idx    Index of the DMA request.
  * @param hdma       Pointer to a handle of the DMA instance.
  * @retval     HAL_OK In case of DMA Set correctly.
  */
hal_status_t HAL_LPTIM_SetDMA(hal_lptim_handle_t *hlptim,
                              hal_lptim_dma_index_t dma_idx,
                              hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((hdma != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  ASSERT_DBG_PARAM(IS_LPTIM_DMA_INDEX(dma_idx));

  /* link the DMA handle to the LPTIM handle */
  hlptim->hdma[(uint32_t)dma_idx] = hdma;
  hdma->p_parent = hlptim;

  return HAL_OK;
}

#endif /* USE_HAL_LPTIM_DMA */

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group2
  *  @{
  * This section provides a set of functions for the states and error management.
  *  - Call HAL_LPTIM_GetState() to have information about low power timer state
  *  - Call HAL_LPTIM_GetChannelState() to have channel's state
  *  - Call HAL_LPTIM_GetLastErrorCodes() to get last error code.
  */

/**
  * @brief  Get the low power timer state.
  * @param  hlptim  Pointer to the handler of the LPTIM instance.
  * @retval hal_lptim_state_t HAL LPTIM state
  */
hal_lptim_state_t HAL_LPTIM_GetState(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  return hlptim->global_state;
}

/**
  * @brief  Get the state of a channel.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel Channel of interest
  * @retval hal_lptim_channel_state_t LPTIM channel state
  */
hal_lptim_channel_state_t HAL_LPTIM_GetChannelState(const hal_lptim_handle_t *hlptim,
                                                    hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));
  return hlptim->channel_states[channel];
}

#if defined(USE_HAL_LPTIM_GET_LAST_ERRORS) && (USE_HAL_LPTIM_GET_LAST_ERRORS == 1)

/**
  * @brief  Retrieve the HAL LPTIM Last Errors.
  * @param  hlptim   Pointer to the handler of the LPTIM instance.
  * @retval uint32_t HAL LPTIM Bit Mapped Last Errors.\n
  *                  Values can be:\n
  *                  @ref HAL_LPTIM_ERROR_NONE \n
  *                  @ref HAL_LPTIM_ERROR_DMA \n
  *                  @ref HAL_LPTIM_ERROR_TIMEOUT
  */
uint32_t HAL_LPTIM_GetLastErrorCodes(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  return hlptim->last_error_codes;
}

#endif /* USE_HAL_LPTIM_GET_LAST_ERRORS */

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group3
  *  @{
  *     This group contains the functions used to configure and control
  *           the time base unit.
  *
  *           - Call HAL_LPTIM_SetConfig() to set LPTIM configuration
  *           - Call HAL_LPTIM_GetConfig() to get LPTIM configuration
  *           - Call HAL_LPTIM_SetMode() to set LPTIM mode (CONTINUOUS or ONE-SHOT MODE)
  *           - Call HAL_LPTIM_GetMode() to get LPTIM mode
  *           - Call HAL_LPTIM_SetClockSource() to set LPTIM clock source (INTERNAL, EXTERNAL SYNCHRONOUS,
  *                                               EXTERNAL ASYNCHRONOUS, ENCODER SUBMODE 1 TO 3)
  *           - Call HAL_LPTIM_GetClockSource() to get LPTIM clock source
  *           - Call HAL_LPTIM_SetClockSourcePrescaler() to set LPTIM clock source prescaler division
  *           - Call HAL_LPTIM_GetClockSourcePrescaler() to get LPTIM clock source prescaler division
  *           - Call HAL_LPTIM_SetPeriod() to set period
  *           - Call HAL_LPTIM_GetPeriod() to get period
  *           - Call HAL_LPTIM_SetRepetitionCounter() to set repetition counter
  *           - Call HAL_LPTIM_GetRepetitionCounter() to get repetition counter
  *           - Call HAL_LPTIM_GetCounter() to get counter
  *           - Call HAL_LPTIM_ResetCounter() to reset counter
  *           - Call HAL_LPTIM_EnableResetCounterAfterRead() to enable Reset Counter After read
  *           - Call HAL_LPTIM_DisableResetCounterAfterRead() to Disable Reset Counter After read
  *           - Call HAL_LPTIM_IsEnableResetCounterAfterRead() to Check if Reset Counter After read is enabled
  *           - Call HAL_LPTIM_EnablePreload() to enable preload
  *           - Call HAL_LPTIM_DisablePreload() to disable preload
  *           - Call HAL_LPTIM_IsEnabledPreload() to check if preload is enabled
  *           - Call HAL_LPTIM_SetConfigInput1() to configure input 1
  *           - Call HAL_LPTIM_GetConfigInput1() to get configure for input 1
  *           - Call HAL_LPTIM_SetInput1Source() to set the input1 src
  *           - Call HAL_LPTIM_GetInput1Source() to get the input1 src setup
  *           - Call HAL_LPTIM_SetInput1Polarity() to set input1 polarity (RISING, FALLING or both)
  *           - Call HAL_LPTIM_GetInput1Polarity() to get the input1 polarity setup
  *           - Call HAL_LPTIM_SetInput1Filter() to set the input1 filter
  *           - Call HAL_LPTIM_GetInput1Filter() to get the input1 filter setup
  *
  * @note When the clock source is HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3]
  *       selection of the sources (2 signals from quadrature encoders)
  *       is done with HAL_LPTIM_SetConfigEncoder().
  *
  */

/**
  * @brief  Configure the low power timer's time-base unit.
  *
  * @param  hlptim     Pointer to the handle of the LPTIM instance.
  * @param  p_config   Pointer to the time-base unit configuration structure.
  * @retval HAL_OK            Configuration correctly set
  * @retval HAL_ERROR         Set configuration failed.
  * @retval HAL_INVALID_PARAM Input parameter is invalid (only if USE_HAL_CHECK_PARAM == 1)
  *
  * @note Writing CNTSTRT or SNGSTRT of the CR register is done in the process function HAL_LPTIM_Start()
  */
hal_status_t HAL_LPTIM_SetConfig(hal_lptim_handle_t *hlptim,
                                 const hal_lptim_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_CLK_SRC(p_lptim, p_config->clock_source));
  ASSERT_DBG_PARAM(IS_LPTIM_MODE(p_config->clock_source,
                                 p_config->mode));
  ASSERT_DBG_PARAM(IS_LPTIM_CLK_SRC_PRESC(p_config->clock_source,
                                          p_config->prescaler));
  ASSERT_DBG_PARAM(IS_LPTIM_PERIOD(p_config->period));
  ASSERT_DBG_PARAM(IS_LPTIM_REPETITION_COUNTER(p_config->repetition_counter));

  /* Store the mode (writing is done in the process function) */
  hlptim->mode = p_config->mode;

  /* Temporary enable the peripheral to modify DIER. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  /* Clear all flags */
  LL_LPTIM_WRITE_REG(p_lptim, ICR, LPTIM_FLAG_ALL);

  /* Set the repetition counter. */
  LL_LPTIM_SetRepetition(p_lptim, p_config->repetition_counter);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_REPOK) != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the period. */
  LL_LPTIM_SetAutoReload(p_lptim, p_config->period);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_ARROK) != 0U)
  {
    return HAL_ERROR;
  }

  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  /* Clock configuration (clock source and clock prescaler) */
  LPTIM_SetClock(p_lptim, p_config->clock_source, p_config->prescaler);

  /* Reset channels (needed only if in IDLE state but done by default) */
  for (uint32_t i = 0; i < HAL_LPTIM_CHANNELS; ++i)
  {
    hlptim->channel_states[i] = HAL_LPTIM_CHANNEL_STATE_RESET;
  }

  hlptim->global_state = HAL_LPTIM_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the configuration of the low power timer's time-base unit.
  * @param  hlptim     Pointer to the handle of the LPTIM instance.
  * @param  p_config   Pointer to a time-base unit configuration structure to fill.
  */
void HAL_LPTIM_GetConfig(const hal_lptim_handle_t *hlptim,
                         hal_lptim_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  p_config->mode = hlptim->mode;

  LPTIM_GetClock(p_lptim, &(p_config->clock_source), &(p_config->prescaler));

  p_config->period = LL_LPTIM_GetAutoReload(p_lptim);

  p_config->repetition_counter = LL_LPTIM_GetRepetition(p_lptim);
}

/**
  * @brief  Set the mode of the low power timer's time-base unit.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  mode    Mode in which to run the timer.
  * @retval HAL_OK Mode set correctly
  *
  * @warning Calling this function while the clock source is
  *       HAL_LPTIM_CLK_ENCODER_SUBMODE_x has no effect.
  *
  * @note Setting the mode on-the-fly is supported by the HW
  *       but we are not doing it (i.e. calling HAL_LPTIM_SetMode() is valid only
  *       in state HAL_LPTIM_STATE_IDLE.)
  *
  * @note Writing CNTSTRT or SNGSTRT of the CR register and TIMEOUT or WAVE of
  *       the CFGR register is done in the process function (HAL_LPTIM_Start()))
  */
hal_status_t HAL_LPTIM_SetMode(hal_lptim_handle_t *hlptim,
                               hal_lptim_mode_t mode)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  lptim_t *p_lptim = (lptim_t *)LPTIM_INSTANCE(hlptim);

  hal_lptim_clk_src_t clk_src = LPTIM_GetClkSrc(p_lptim);

  if (IS_LPTIM_CLK_ENCODER(clk_src) == 0U)
  {
    /* Store the mode */
    hlptim->mode = mode;
  }

  return HAL_OK;
}

/**
  * @brief  Get the mode of the low power timer's time-base unit.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_mode_t  Mode in which the low power timer runs.
  */
hal_lptim_mode_t HAL_LPTIM_GetMode(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return hlptim->mode;
}

/**
  * @brief  Set the clock source of the low power timer's time-base unit.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  clk_src  Clock source of the LPTIM instance.
  * @retval HAL_OK Clock Source set correctly
  *
  */
hal_status_t HAL_LPTIM_SetClockSource(const hal_lptim_handle_t *hlptim,
                                      hal_lptim_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM(IS_LPTIM_CLK_SRC(LPTIM_INSTANCE(hlptim), clk_src));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  LPTIM_SetClkSrc(LPTIM_INSTANCE(hlptim), clk_src);

  return HAL_OK;
}

/**
  * @brief  Get the clock source of the low power timer's time-base unit.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_clk_src_t  Clock source of the LPTIM instance.
  *
  */
hal_lptim_clk_src_t HAL_LPTIM_GetClockSource(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return LPTIM_GetClkSrc(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Set the clock source prescaler of the low power timer.
  * @param  hlptim         Pointer to the handle of the LPTIM instance.
  * @param  clk_src_presc  Clock source prescaler of the LPTIM instance.
  * @retval HAL_OK Clock Source Prescaler set correctly
  *
  * @note
  * - Clock prescaler setting has no effect if the clock source is
  * HAL_LPTIM_CLK_ENCODER_SUBMODE_[1|2|3].
  * - The prescaler must not be used (DIV1) when the LPTIM external Input1 is sampled with the
  * internal clock (HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS).
  *
  * @warning Setting the clock source prescaler is authorized only if the clock
  *       source is HAL_LPTIM_CLK_INTERNAL or HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS
  *       (but in this last case it has no effect).
  */

hal_status_t HAL_LPTIM_SetClockSourcePrescaler(const hal_lptim_handle_t *hlptim,
                                               hal_lptim_clk_src_presc_t clk_src_presc)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM(IS_LPTIM_CLK_SRC_PRESC(LPTIM_GetClkSrc(LPTIM_INSTANCE(hlptim)),
                                          clk_src_presc));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  LPTIM_SetClkSrcPresc(LPTIM_INSTANCE(hlptim), clk_src_presc);

  return HAL_OK;
}

/**
  * @brief  Get the clock source prescaler of the low power timer.
  * @param  hlptim         Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_clk_src_presc_t  Clock source prescaler of the LPTIM instance.
  *
  */
hal_lptim_clk_src_presc_t HAL_LPTIM_GetClockSourcePrescaler(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_clk_src_presc_t)LPTIM_GET_CLOCK_SOURCE_PRESCALER(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Set the period of the low power timer's time-base unit.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  period   Period for the time base unit.
  * @retval HAL_OK   Period set correctly

  * @retval HAL_ERROR  Set period failed.
  */
hal_status_t HAL_LPTIM_SetPeriod(const hal_lptim_handle_t *hlptim,
                                 uint32_t period)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_PERIOD(period));

  /* LPTIM has to be disabled to modify CFGR, so we store the state and
  set it back once the operation is done. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  /* LPTIM has to be enabled to modify ARR. */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  /* Clear flag */
  LL_LPTIM_WRITE_REG(p_lptim, ICR, LL_LPTIM_ISR_ARROK);

  /* Set the period and wait for the register to be updated. */
  LL_LPTIM_SetAutoReload(p_lptim, period);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_ARROK) != 0U)
  {
    return HAL_ERROR;
  }
  /* If it was disable, stop LPTIM. */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  return HAL_OK;
}

/**
  * @brief  Get the period of the low power timer.
  * @param  hlptim          Pointer to the handle of the LPTIM instance.
  * @return uint32_t        Period Value
  */
uint32_t HAL_LPTIM_GetPeriod(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return LL_LPTIM_GetAutoReload(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Set the repetition counter of the low power timer's time-base unit.
  * @param  hlptim             Pointer to the handle of the LPTIM instance.
  * @param  repetition_counter   Repetition value for the time base unit.
  * @retval HAL_ERROR  Set repetitioncounter failed.
  * @retval HAL_OK Repetition Counter set correctly
  */
hal_status_t HAL_LPTIM_SetRepetitionCounter(const hal_lptim_handle_t *hlptim,
                                            uint32_t repetition_counter)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  ASSERT_DBG_PARAM(IS_LPTIM_REPETITION_COUNTER(repetition_counter));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* LPTIM has to be enabled to modify RCR. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  /* LPTIM has to be enabled to modify ARR. */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  /* Clear flag */
  LL_LPTIM_WRITE_REG(p_lptim, ICR, LL_LPTIM_ISR_REPOK);

  /* Set the repetition counter and wait for the register to be updated. */
  LL_LPTIM_SetRepetition(p_lptim, repetition_counter);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_REPOK) != 0U)
  {
    return HAL_ERROR;
  }

  /* LPTIM has to be enabled to modify ARR. */
  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  return HAL_OK;
}

/**
  * @brief  Get the value of the repetition counter of the low power timer.
  * @param  hlptim            Pointer to the handle of the LPTIM instance.
  * @retval uint32_t          Value of the repetition counter.
  */
uint32_t HAL_LPTIM_GetRepetitionCounter(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return LL_LPTIM_GetRepetition(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Get Counter Register (LPTIMx_CNT) value.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval uint32_t  Counter register value.
  *
  * @warning When the LPTIM instance is running, reading
  *       the LPTIMx_CNT register can return unreliable values. So in this case
  *       it is necessary to perform two consecutive read accesses and verify
  *       that the two returned values are identical.
  */
uint32_t HAL_LPTIM_GetCounter(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return LL_LPTIM_GetCounter(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Reset Counter Register (LPTIMx_CNT) value.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK   Reset counter done correctly
  */
hal_status_t HAL_LPTIM_ResetCounter(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  LL_LPTIM_ResetCounter(LPTIM_INSTANCE(hlptim));
  return HAL_OK;
}

/**
  * @brief  Enable Reset Counter After read, Register (LPTIMx_RSTARE) value.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK   Reset counter after read enabled correctly
  */
hal_status_t HAL_LPTIM_EnableResetCounterAfterRead(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_ACTIVE);

  LL_LPTIM_EnableResetAfterRead(LPTIM_INSTANCE(hlptim));
  return HAL_OK;
}

/**
  * @brief  Disable Reset Counter After read, Register (LPTIMx_RSTARE) value.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK   Reset counter after read disabled correctly
  */
hal_status_t HAL_LPTIM_DisableResetCounterAfterRead(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_ACTIVE);

  LL_LPTIM_DisableResetAfterRead(LPTIM_INSTANCE(hlptim));
  return HAL_OK;
}

/**
  * @brief  Check Reset Counter After read, Register (LPTIMx_RSTARE) value.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_reset_after_read_status_t Registers update mode.
  */
hal_lptim_reset_after_read_status_t HAL_LPTIM_IsEnableResetCounterAfterRead(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_reset_after_read_status_t)LL_LPTIM_IsEnabledResetAfterRead(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Enable the preload (registers ARR, RCR and CCRx are updated at the
  *         end of the current LPTIM period).
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK   Preload enabled correctly
  */
hal_status_t HAL_LPTIM_EnablePreload(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* LPTIM has to be disabled to modify CFGR, so we store the state and
     set it back once the operation is done. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);
  LL_LPTIM_Disable(p_lptim);
  LL_LPTIM_SetUpdateMode(p_lptim, (uint32_t)HAL_LPTIM_PRELOAD_ENABLED);
  if (is_lptim_enabled == 1U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the preload (registers ARR, RCR and CCR are updated after
  *         each APB bus access.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK   Preload disabled correctly
  */
hal_status_t HAL_LPTIM_DisablePreload(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* LPTIM has to be disabled to modify CFGR, so we store the state and
     set it back once the operation is done. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);
  LL_LPTIM_Disable(p_lptim);
  LL_LPTIM_SetUpdateMode(p_lptim, (uint32_t)HAL_LPTIM_PRELOAD_DISABLED);
  if (is_lptim_enabled == 1U)
  {
    LL_LPTIM_Enable(p_lptim);
  }

  return HAL_OK;
}

/**
  * @brief  Check preload state.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_preload_status_t Registers update mode.
  */
hal_lptim_preload_status_t HAL_LPTIM_IsEnabledPreload(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_preload_status_t)LL_LPTIM_GetUpdateMode(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Configure Input1.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @param  p_config  Pointer to the input1 configuration structure.
  * @retval HAL_OK   Config input 1 has been correctly configured
  * @retval HAL_ERROR When called with clock source different from
  *                   HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or
  *                   HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS.
  *
  * @note When Input1 is used as external clock, configure the clock source as either
  *         HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS).
  *
  * @warning - This function must be called only after the clock source is
  *         configured.
  *       - if the clock is HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS but the filter
  *         is not HAL_LPTIM_FDIV1, or the polarity is
  *         HAL_LPTIM_INPUT1_RISING_FALLING then an auxiliary clock (one of the
  *         Low power oscillator) must be active.
  *
  */

hal_status_t HAL_LPTIM_SetConfigInput1(const hal_lptim_handle_t *hlptim,
                                       const hal_lptim_input1_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_INSTANCE(p_lptim));
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_SRC(p_config->src));
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(p_config->filter));

  /* Get the clock source config. */
  hal_lptim_clk_src_t clk_src = LPTIM_GetClkSrc(p_lptim);

  if (!((clk_src == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS)
        || (clk_src == HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS)))
  {
    return HAL_ERROR;
  }


  /* Set the input1 source (bits IN1SEL in CFGR2) */
  LL_LPTIM_SetInput1Source(p_lptim, (uint32_t)p_config->src);

  /* Configure the polarity and the filter together (CKPOL and CKFLT in CFGR). */
  LL_LPTIM_ConfigClock(p_lptim, (uint32_t)(p_config->polarity), LPTIM_CFGR_HAL2LL_FILTER(p_config->filter));

  return HAL_OK;
}

/**
  * @brief  Get Input1 configuration.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @param  p_config  Pointer to the input1 configuration structure to fill.
  */
void HAL_LPTIM_GetConfigInput1(const hal_lptim_handle_t *hlptim,
                               hal_lptim_input1_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  p_config->polarity = (hal_lptim_input1_polarity_t)LPTIM_GET_CLOCK_POLARITY(p_lptim);
  p_config->filter = (hal_lptim_filter_t)(LPTIM_GET_CLOCK_FILTER(p_lptim));
  p_config->src = (hal_lptim_input1_src_t)LL_LPTIM_GetInput1Source(p_lptim);
}

/**
  * @brief  Set Input1 source.
  * @param  hlptim     Pointer to the handle of the LPTIM instance.
  * @param  input1_src Source of Input1.
  * @retval HAL_OK  SetInput1Source has been correctly configured
  * @retval HAL_ERROR When called with clock source different from
  *                   HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or
  *                   HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS.
  *
  * @warning This function must be called only after the clock source is
  *       configured.
  */
hal_status_t HAL_LPTIM_SetInput1Source(const hal_lptim_handle_t *hlptim,
                                       hal_lptim_input1_src_t input1_src)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_INSTANCE(p_lptim));
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_SRC(input1_src));

  /* Get the clock source config. */
  hal_lptim_clk_src_t clk_src = LPTIM_GetClkSrc(p_lptim);

  if (!((clk_src == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS) || (clk_src == HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS)))
  {
    return HAL_ERROR;
  }

  /* Set the input1 source. */
  LL_LPTIM_SetInput1Source(p_lptim, (uint32_t)input1_src);

  return HAL_OK;
}

/**
  * @brief  Get Input1 source.
  * @param  hlptim     Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_input1_src_t Input1 source.
  */
hal_lptim_input1_src_t HAL_LPTIM_GetInput1Source(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_input1_src_t)LL_LPTIM_GetInput1Source(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Set Input1 polarity.
  * @param  hlptim     Pointer to the handle of the LPTIM instance.
  * @param  polarity polarity of Input1.
  * @retval HAL_OK Input 1 Polarity has been correctly configured
  * @retval HAL_ERROR When called with clock source different from
  *                   HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or
  *                   HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS.
  *
  * @warning - This function must be called only after the clock source is
  *         configured.
  *       - An auxiliary clock (one of the Low power oscillator) must be active
  *         if the polarity is HAL_LPTIM_INPUT1_RISING_FALLING.
  */
hal_status_t HAL_LPTIM_SetInput1Polarity(const hal_lptim_handle_t *hlptim,
                                         hal_lptim_input1_polarity_t polarity)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);
  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_INSTANCE(p_lptim));
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_POLARITY(polarity));

  /* Get the clock source. */
  hal_lptim_clk_src_t clk_src = LPTIM_GetClkSrc(p_lptim);

  if (!((clk_src == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS) || (clk_src == HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS)))
  {
    return HAL_ERROR;
  }

  LL_LPTIM_SetClockPolarity(p_lptim, (uint32_t)polarity);

  return HAL_OK;
}

/**
  * @brief  Get Input1 polarity.
  * @param  hlptim     Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_input1_polarity_t Input1 active edge(s).
  */
hal_lptim_input1_polarity_t HAL_LPTIM_GetInput1Polarity(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_input1_polarity_t)LL_LPTIM_GetClockPolarity(LPTIM_INSTANCE(hlptim));
}

/**
  * @brief  Set Input1 filter.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  filter   Filter for Input1.
  * @retval HAL_OK Input 1 Filter has been correctly configured
  * @retval HAL_ERROR When called with clock source different from
  *                   HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS or
  *                   HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS.
  *
  * @note If filtering is used, an auxiliary clock must be active.
  *
  * @warning - This function must be called only after the clock source is
  *         configured.
  *       - An auxiliary clock (one of the Low power oscillator) must be active
  *         if the value of the filter is different from HAL_LPTIM_FDIV1.
  */

hal_status_t HAL_LPTIM_SetInput1Filter(const hal_lptim_handle_t *hlptim,
                                       hal_lptim_filter_t filter)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_INPUT1_INSTANCE(p_lptim));
  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(filter));

  /* Get the clock source config. */
  hal_lptim_clk_src_t clk_src = LPTIM_GetClkSrc(p_lptim);

  if (!((clk_src == HAL_LPTIM_CLK_EXTERNAL_SYNCHRONOUS) || (clk_src == HAL_LPTIM_CLK_EXTERNAL_ASYNCHRONOUS)))
  {
    return HAL_ERROR;
  }

  /* Configure the filter (CKFLT in CFGR). */
  LL_LPTIM_SetClockFilter(p_lptim,
                          LPTIM_CFGR_HAL2LL_FILTER(filter));

  return HAL_OK;
}

/**
  * @brief  Get Input1 filter.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @return @ref hal_lptim_filter_t Filter value applied to Input1.
  */
hal_lptim_filter_t HAL_LPTIM_GetInput1Filter(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_filter_t)LPTIM_GET_CLOCK_FILTER(LPTIM_INSTANCE(hlptim));
}

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group4
  * @{
  * This section provides a set of function to Start and Stop LPTIM services
  * - Call HAL_LPTIM_Start() to start LPTIM driver in polling mode
  * - Call HAL_LPTIM_Stop() to stop LPTIM driver
  * - Call HAL_LPTIM_Start_IT() to start LPTIM driver in interrupt mode
  * - Call HAL_LPTIM_Stop_IT() to stop LPTIM driver and disable interrupt
  * - Call HAL_LPTIM_Start_DMA_Opt() to start LPTIM driver in DMA mode with interrupt option
  * - Call HAL_LPTIM_Start_DMA() to start LPTIM driver in DMA mode
  * - Call HAL_LPTIM_Stop_DMA() to stop LPTIM driver in DMA mode
  */

/**
  * @brief  Start the low power timer in polling mode.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK LPTIM has been correctly started
  * @retval HAL_ERROR When there is a mismatch between the mode and the current clock source.
  */
hal_status_t HAL_LPTIM_Start(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hlptim, global_state, HAL_LPTIM_STATE_IDLE,
                         HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  if (LPTIM_Start(p_lptim, (uint32_t)hlptim->mode) != 0U)
  {
    return HAL_ERROR;
  }

  /* Enable the peripheral. */
  LL_LPTIM_Enable(p_lptim);

  /* Start the counter in continuous or single counting mode (set the
     CNTSTRT bit or the SNGSTRT bit in CR.)
     Note that the counter starts only if TRIGEN is 00 in CFGR which is
     the case unless an external trigger source was set. */
  LL_LPTIM_StartCounter(p_lptim, (LPTIM_MODE_CR_MASK & (uint32_t)(hlptim->mode)));

  return HAL_OK;
}

/**
  * @brief  Stop the low power timer that was started in polling mode.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK  LPTIM has correctly been stopped
  */
hal_status_t HAL_LPTIM_Stop(hal_lptim_handle_t *hlptim)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Disable the peripheral. */
  status = LPTIM_CcDisable(p_lptim);

  /* Reset the WAVE bit and the TIMOUT bit in CFGR. */
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);
  cfgr &= ~LPTIM_MODE_CFGR_MASK;
  LL_LPTIM_WRITE_REG(p_lptim, CFGR, cfgr);

  hlptim->global_state = HAL_LPTIM_STATE_IDLE;

  return status;
}

/**
  * @brief  Start the low power timer in interrupt mode.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK LPTIM with IT has correctly been start
  * @retval HAL_ERROR When there is a mismatch between the mode
  *         and the current clock source, or when enabling the
  *         interrupts failed.
  */
hal_status_t HAL_LPTIM_Start_IT(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hlptim, global_state, HAL_LPTIM_STATE_IDLE,
                         HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  if (LPTIM_Start(p_lptim, (uint32_t)hlptim->mode) != 0U)
  {
    return HAL_ERROR;
  }

  /* Enable the peripheral. */
  LL_LPTIM_Enable(p_lptim);

  /* Clear DIEROK flag in the ISR (i.e. write 1 to DIEROKCF bit in ICR). */
  LL_LPTIM_ClearFlag_DIEROK(p_lptim);

  /* Enable interrupts */
  volatile uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);


  /* if encoder is enabled, need to activate DOWN and UP flag */
  if (LL_LPTIM_IsEnabledEncoderMode(p_lptim) == 1U)
  {
    dier |= (LL_LPTIM_DIER_UPIE | LL_LPTIM_DIER_DOWNIE);
  }
  else if (LL_LPTIM_IsEnabledTimeout(p_lptim) == 1U)
  {
    dier |= LL_LPTIM_DIER_CC1IE;
  }
  else
  {
    dier |= (LL_LPTIM_DIER_ARROKIE | LL_LPTIM_DIER_ARRMIE |
             LL_LPTIM_DIER_REPOKIE | LL_LPTIM_DIER_UEIE);
  }

  LL_LPTIM_WRITE_REG(p_lptim, DIER, dier);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

  /* Start the counter in continuous or single counting mode (set the
     CNTSTRT bit or the SNGSTRT bit in CR.)
     Note that the counter starts only if TRIGEN is 00 in CFGR which is
     the case unless an external trigger source was set. */
  LL_LPTIM_StartCounter(p_lptim, (LPTIM_MODE_CR_MASK & (uint32_t)hlptim->mode));

  return HAL_OK;
}

/**
  * @brief  Stop the low power timer that was started in interrupt mode.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK LPTIM with IT has correctly been stopped
  * @retval HAL_ERROR When disabling the interrupts failed.
  */
hal_status_t HAL_LPTIM_Stop_IT(hal_lptim_handle_t *hlptim)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  LL_LPTIM_Enable(p_lptim);

  /* Clear DIEROK flag in the ISR (i.e. write 1 to DIEROKCF bit in ICR). */
  LL_LPTIM_ClearFlag_DIEROK(p_lptim);

  /* Disable interrupts (the peripheral is supposed to be enabled) */
  volatile uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);
  dier &= ~(LL_LPTIM_DIER_ARROKIE | LL_LPTIM_DIER_ARRMIE |
            LL_LPTIM_DIER_REPOKIE | LL_LPTIM_DIER_UEIE);
  LL_LPTIM_WRITE_REG(p_lptim, DIER, dier);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

  /* Disable the peripheral. */
  status = LPTIM_CcDisable(p_lptim);

  /* Reset the WAVE bit and the TIMOUT bit in CFGR. */
  volatile uint32_t cfgr = LL_LPTIM_READ_REG(p_lptim, CFGR);
  cfgr &= ~LPTIM_MODE_CFGR_MASK;
  LL_LPTIM_WRITE_REG(p_lptim, CFGR, cfgr);

  hlptim->global_state = HAL_LPTIM_STATE_IDLE;

  return status;
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
/**
  * @brief  Start the low power timer in DMA mode.
  * @param  hlptim      Pointer to the handle of the LPTIM instance.
  * @param  p_data      Pointer to the data buffer.
  * @param  size_byte   Data buffer size (in bytes).
  * @param  interrupts Selection of the DMA interrupts. \n
  *                    Can be any of the (meaningful) those values:
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_NONE
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_HT
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_DEFAULT
  * @if (USE_HAL_DMA_LINKEDLIST)
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_SILENT
  * @endif
  * @retval HAL_OK LPTIM with DMA has correctly been started
  * @retval HAL_ERROR   Failed to start the DMA transfer.
  * @retval HAL_INVALID_PARAM Input parameter is invalid
  *         (only if USE_HAL_CHECK_PARAM == 1)
  *
  * @warning    HAL_LPTIM_SetDMA() is to be called with the correct DMA index (see
  *          hal_lptim_dma_index_t) before calling this function.
  */
hal_status_t HAL_LPTIM_Start_DMA_Opt(hal_lptim_handle_t *hlptim,
                                     const void *p_data,
                                     uint32_t size_byte,
                                     uint32_t interrupts)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_data != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */


  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  if (LPTIM_Start_DMA_Opt(hlptim, p_data, size_byte, interrupts) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_LPTIM_Start(hlptim);
}

/**
  * @brief  Start the low power timer in DMA mode.
  * @param  hlptim      Pointer to the handle of the LPTIM instance.
  * @param  p_data      Pointer to the data buffer.
  * @param  size_byte   Data buffer size (in bytes).
  *
  * @retval HAL_OK LPTIM with DMA has correctly been started
  * @retval HAL_ERROR   Failed to start the DMA transfer.
  * @retval HAL_INVALID_PARAM Input parameter is invalid
  *         (only if USE_HAL_CHECK_PARAM == 1)
  *
  * @warning    HAL_LPTIM_SetDMA() is to be called with the correct DMA index (see
  *          hal_lptim_dma_index_t) before calling this function.
  */
hal_status_t HAL_LPTIM_Start_DMA(hal_lptim_handle_t *hlptim,
                                 const void *p_data,
                                 uint32_t size_byte)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_data != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  if (LPTIM_Start_DMA_Opt(hlptim, p_data, size_byte, HAL_LPTIM_OPT_DMA_IT_DEFAULT) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_LPTIM_Start(hlptim);
}

/**
  * @brief  Stop the timer that was started in DMA mode.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval HAL_OK LPTIM with DMA has correctly been stopped
  */
hal_status_t HAL_LPTIM_Stop_DMA(hal_lptim_handle_t *hlptim)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  if (LL_LPTIM_IsEnabledDMAReq_UPDATE(p_lptim) == 1U)
  {
    /* Disable Update DMA request */
    LL_LPTIM_DisableDMAReq_UPDATE(p_lptim);

    LPTIM_Abort_DMA(hlptim,
                    HAL_LPTIM_DMA_ID_UPDATE,
                    (IS_LPTIM_ACTIVE_SILENT(hlptim->global_state)));
  }

  /* Disable Update DMA request */
  LL_LPTIM_DisableDMAReq_UPDATE(p_lptim);

  /* Disable the peripheral. */
  status = LPTIM_CcDisable(p_lptim);

  hlptim->global_state = HAL_LPTIM_STATE_IDLE;

  return status;
}
#endif /* USE_HAL_LPTIM_DMA */

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group5
  * @{
  *  This group contains the functions used to configure and control
  *    the output stage of the LP Timer's capture/compare channels.
  *
  *     - Call HAL_LPTIM_OC_SetConfigChannel() to set output channel's configuration
  *     - Call HAL_LPTIM_OC_GetConfigChannel() to get output channel's configuration
  *     - Call HAL_LPTIM_OC_SetChannelPolarity() to set output channel's polarity
  *     - Call HAL_LPTIM_OC_GetChannelPolarity() to get output channel's polarity
  *     - Call HAL_LPTIM_OC_SetChannelPulse() to set output channel's pulse width
  *     - Call HAL_LPTIM_OC_GetChannelPulse() to get output channel's pulse width
  *     - Call HAL_LPTIM_OC_StartChannel() to start output channel
  *     - Call HAL_LPTIM_OC_StopChannel() to stop output channel
  *     - Call HAL_LPTIM_OC_StartChannel_IT() to start output channel with compare IT
  *     - Call HAL_LPTIM_OC_StopChannel_IT() to stop output channel with compare IT
  */

/**
  * @brief Configure the Output channel/Output Compare
  * @param hlptim              Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param p_config            Pointer on @ref hal_lptim_oc_config_t
  * @retval HAL_OK             LPTIM driver has been correctly configured
  * @retval HAL_INVALID_PARAM  When p_config pointer is NULL
  * @retval HAL_ERROR          When LPTIM driver set pwm failed
  */
hal_status_t HAL_LPTIM_OC_SetConfigChannel(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           const hal_lptim_oc_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Check channel configuration parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_OC_PULSE(p_config->pulse));
  ASSERT_DBG_PARAM(IS_LPTIM_OC_POLARITY(p_config->polarity));

  LL_LPTIM_OC_SetPolarity(p_lptim, channel, p_config->polarity);

  if (LPTIM_OC_SetPulse(p_lptim, channel, p_config->pulse) != 0U)
  {
    return HAL_ERROR;
  }

  hlptim->channel_states[channel] = HAL_LPTIM_OC_CHANNEL_STATE_IDLE;

  /* Note: Setting the channel has output is done in the start function. */
  return HAL_OK;
}

/**
  * @brief Get the actual configuration
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param p_config Pointer on @ref hal_lptim_oc_config_t
  */
void HAL_LPTIM_OC_GetConfigChannel(hal_lptim_handle_t *hlptim,
                                   hal_lptim_channel_t channel,
                                   hal_lptim_oc_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  p_config->polarity = (hal_lptim_oc_polarity_t)LL_LPTIM_OC_GetPolarity(p_lptim, channel);
  p_config->pulse = LPTIM_OC_GetPulse(p_lptim, channel);
}

/**
  * @brief Set output channel's polarity
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param polarity output channel's polarity
  * @warning the channel is supposed to be disabled
  * @retval HAL_OK LPTIM output channel's polarity correctly setup
  */
hal_status_t HAL_LPTIM_OC_SetChannelPolarity(hal_lptim_handle_t *hlptim,
                                             hal_lptim_channel_t channel,
                                             hal_lptim_oc_polarity_t polarity)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Check channel polarity parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_OC_POLARITY(polarity));

  /* Control the channel state (to be checked) */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (LPTIM_CHANNEL_STATE_IDLE));

  LL_LPTIM_OC_SetPolarity(p_lptim, channel, polarity);

  /* Note: Setting the channel has output is done in the start function. */

  return HAL_OK;
}

/**
  * @brief Get output channel's polarity
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @return hal_lptim_oc_polarity_t output channel's polarity mode
  */
hal_lptim_oc_polarity_t HAL_LPTIM_OC_GetChannelPolarity(const hal_lptim_handle_t *hlptim,
                                                        hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_oc_polarity_t)LL_LPTIM_OC_GetPolarity(LPTIM_INSTANCE(hlptim),
                                                          channel);
}

/**
  * @brief Set output channel's pulse
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @param pulse value pulse width needs to compare it
  * @retval HAL_ERROR if pulse set failed
  * @retval HAL_OK output channel's pulse correctly setup
  */
hal_status_t HAL_LPTIM_OC_SetChannelPulse(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel,
                                          uint32_t pulse)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Check channel the pulse parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_OC_PULSE(pulse));

  /* Control the channel state (to be checked) */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (LPTIM_CHANNEL_STATE_IDLE | HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE));

  if (LPTIM_OC_SetPulse(p_lptim, channel, pulse) != 0U)
  {
    return HAL_ERROR;
  }

  /* Note: Setting the channel has output is done in the start function. */

  return HAL_OK;
}

/**
  * @brief Get output channel's pulse
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @return uint32_t pulse value from channel number
  */
uint32_t HAL_LPTIM_OC_GetChannelPulse(const hal_lptim_handle_t *hlptim,
                                      hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(LPTIM_INSTANCE(hlptim), channel)));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return LPTIM_OC_GetPulse(LPTIM_INSTANCE(hlptim), channel);
}

/*
  Setting the channel has output is done in the start function.
  That is, the CCxSEL bit is reset to 0 (default value).
*/
/**
  * @brief Start a LP-Timer's output channel in polling mode.
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @retval HAL_OK output channel has been correctly started
  */
hal_status_t HAL_LPTIM_OC_StartChannel(hal_lptim_handle_t *hlptim,
                                       hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_OC_CHANNEL_STATE_IDLE);
  HAL_CHECK_UPDATE_STATE(hlptim, channel_states[channel],
                         HAL_LPTIM_OC_CHANNEL_STATE_IDLE,
                         HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE);

  /* Disable channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  /* Set the channel as output. */
  LL_LPTIM_CC_SetChannelMode(p_lptim, channel,
                             LL_LPTIM_CCMODE_OUTPUT_PWM);

  /* Enable channel */
  LL_LPTIM_CC_EnableChannel(p_lptim, channel);

  return HAL_OK;
}

/**
  * @brief Stop channel LPTIM driver with output channel/output compare
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @retval HAL_OK output channel has been correctly stopped
  */
hal_status_t HAL_LPTIM_OC_StopChannel(hal_lptim_handle_t *hlptim,
                                      hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE);

  /* Disable the channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  hlptim->channel_states[channel] = HAL_LPTIM_OC_CHANNEL_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Start channel LPTIM driver output channel/output compare with interrupt
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @retval HAL_ERROR No flag has been given
  * @retval HAL_OK output channel has been correctly started
  */
hal_status_t HAL_LPTIM_OC_StartChannel_IT(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_OC_CHANNEL_STATE_IDLE);
  HAL_CHECK_UPDATE_STATE(hlptim, channel_states[channel],
                         HAL_LPTIM_OC_CHANNEL_STATE_IDLE,
                         HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE);

  /* Temporary enable the peripheral to modify DIER. */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  LL_LPTIM_Enable(p_lptim);

  /* Clear flag */
  LL_LPTIM_ClearFlag_DIEROK(p_lptim);
  volatile uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);

  /* if HAL_LPTIM_SET_ONCE */
  if (hlptim->mode == HAL_LPTIM_SET_ONCE)
  {
    /* Enable interrupts */
    dier |= (LL_LPTIM_DIER_ARROKIE | LL_LPTIM_DIER_ARRMIE | LL_LPTIM_DIER_REPOKIE |
             LL_LPTIM_DIER_UEIE);
    if (channel == HAL_LPTIM_CHANNEL_1)
    {
      dier |= LL_LPTIM_DIER_CMP1OKIE;
    }
    else
    {
      dier |= LL_LPTIM_DIER_CMP2OKIE;
    }
  }

  /* Enable Compare interrupt */
  if (channel == HAL_LPTIM_CHANNEL_1)
  {
    dier |= LPTIM_DIER_CC1IE;
  }
  else /* necessary channel 2 (checked only by assert) */
  {
    dier |= LPTIM_DIER_CC2IE;
  }

  LL_LPTIM_WRITE_REG(p_lptim, DIER, dier);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

  /* Disable channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  /* Set the channel as output. */
  LL_LPTIM_CC_SetChannelMode(p_lptim, channel,
                             LL_LPTIM_CCMODE_OUTPUT_PWM);

  /* Enable channel */
  LL_LPTIM_CC_EnableChannel(p_lptim, channel);

  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  return HAL_OK;
}

/**
  * @brief Stop channel LPTIM driver output channel/output compare with interrupt compare
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param  channel    Output channel of interest to enable.
  * @retval HAL_ERROR No flags have been given
  * @retval HAL_OK output channel has been correctly stopped
  */
hal_status_t HAL_LPTIM_OC_StopChannel_IT(hal_lptim_handle_t *hlptim,
                                         hal_lptim_channel_t channel)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check the channel is supported by the instance */
  ASSERT_DBG_PARAM((IS_LPTIM_CC_CHANNEL(p_lptim, channel)));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_OC_CHANNEL_STATE_ACTIVE);

  LL_LPTIM_Enable(p_lptim);

  /* Disable the channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  /* Disable Compare interrupt */
  if (channel == HAL_LPTIM_CHANNEL_1)
  {
    LL_LPTIM_DisableIT_CC1(p_lptim);
  }
  else
  {
    LL_LPTIM_DisableIT_CC2(p_lptim);
  }

  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }
  status = LPTIM_CcDisable(p_lptim);

  hlptim->channel_states[channel] = HAL_LPTIM_OC_CHANNEL_STATE_IDLE;

  return status;
}


/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group6
  * @{
  *
  * This group contains the functions used to configure and control
  * the input stage of the timer's capture/compare channels.
  *    - Call HAL_LPTIM_IC_SetConfigChannel() to set input channel's configuration
  *    - Call HAL_LPTIM_IC_GetConfigChannel() to get input channel's configuration
  *    - Call HAL_LPTIM_IC_SetChannelSource() to set input channel's source
  *    - Call HAL_LPTIM_IC_GetChannelSource() to get input channel's source
  *    - Call HAL_LPTIM_IC_SetChannelPolarity() to set input channel's polarity
  *    - Call HAL_LPTIM_IC_GetChannelPolarity() to get input channel's polarity
  *    - Call HAL_LPTIM_IC_GetChannelFilter() to get input channel's filter
  *    - Call HAL_LPTIM_IC_SetChannelFilter() to set input channel's filter
  *    - Call HAL_LPTIM_IC_GetChannelPrescaler() to get input channel's prescaler
  *    - Call HAL_LPTIM_IC_SetChannelPrescaler() to set input channel's prescaler
  *    - Call HAL_LPTIM_IC_StartChannel() to start input channel
  *    - Call HAL_LPTIM_IC_StopChannel() to stop input channel
  *    - Call HAL_LPTIM_IC_StartChannel_IT() to start input channel with capture IT
  *    - Call HAL_LPTIM_IC_StopChannel_IT() to stop input channel with capture IT
  *    - Call HAL_LPTIM_IC_StartChannel_DMA() to start input channel with capture DMA
  *    - Call HAL_LPTIM_IC_StartChannel_DMA_Opt() to start input channel with capture DMA with DMA IT specific options
  *    - Call HAL_LPTIM_IC_StopChannel_DMA() to stop input channel with capture DMA
  *    - Call HAL_LPTIM_IC_ReadChannelCapturedValue() to read value captured of timer's input channel
  */

/**
  * @brief Configure the Input channel/Input Capture
  * @param hlptim              Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param p_config            Pointer on @ref hal_lptim_ic_config_t
  * @retval HAL_OK             LPTIM driver has been correctly configured
  * @retval HAL_INVALID_PARAM  When p_config pointer is NULL
  * @retval HAL_ERROR          When LPTIM driver set pwm failed
  */
hal_status_t HAL_LPTIM_IC_SetConfigChannel(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           const hal_lptim_ic_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Check channel configuration parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL_SRC(p_config->source));
  ASSERT_DBG_PARAM(IS_LPTIM_IC_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(p_config->filter));
  ASSERT_DBG_PARAM(IS_LPTIM_IC_PRESCALER(p_config->prescaler));

  /* Control the channel state */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (HAL_LPTIM_CHANNEL_STATE_RESET | LPTIM_CHANNEL_STATE_IDLE));

  uint32_t ll_channelsource = LPTIM_ConvertHALToLLIcx(hlptim, channel, p_config->source);
  LL_LPTIM_SetRemap(p_lptim, ll_channelsource);

  LL_LPTIM_IC_SetPolarity(p_lptim, channel, p_config->polarity);
  LL_LPTIM_IC_SetFilter(p_lptim, channel, LPTIM_CCMR1_HAL2LL_FILTER(p_config->filter));
  LL_LPTIM_IC_SetPrescaler(p_lptim, channel, p_config->prescaler);

  hlptim->channel_states[channel] = HAL_LPTIM_IC_CHANNEL_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the Input channel configuration
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param p_config Pointer on @ref hal_lptim_ic_config_t
  */
void HAL_LPTIM_IC_GetConfigChannel(const hal_lptim_handle_t *hlptim,
                                   hal_lptim_channel_t channel,
                                   hal_lptim_ic_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (HAL_LPTIM_IC_CHANNEL_STATE_IDLE | HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE));

  p_config->source = (hal_lptim_ic_src_t)LPTIM_ConvertLLToHALIcx(hlptim, channel, LL_LPTIM_GetRemap(p_lptim));

  p_config->polarity = (hal_lptim_ic_polarity_t)LL_LPTIM_IC_GetPolarity(p_lptim,
                                                                        channel);

  p_config->filter = (hal_lptim_filter_t)(LPTIM_CCMR1_LL2HAL_FILTER(LL_LPTIM_IC_GetFilter(p_lptim, channel)));
  p_config->prescaler = (hal_lptim_ic_prescaler_t)LL_LPTIM_IC_GetPrescaler(p_lptim, channel);
}

/**
  * @brief Set input channel's source
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param source input channel's source
  * @warning the channel is supposed to be disabled
  * @retval HAL_OK LPTIM input channel's source correctly setup
  */
hal_status_t HAL_LPTIM_IC_SetChannelSource(const hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           hal_lptim_ic_src_t source)
{
  STM32_UNUSED(channel);

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (HAL_LPTIM_IC_CHANNEL_STATE_IDLE | HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE));


  uint32_t ll_channelsource = LPTIM_ConvertHALToLLIcx(hlptim, channel, source);
  LL_LPTIM_SetRemap(p_lptim, ll_channelsource);

  /* Note: Setting the channel has output is done in the start function. */
  return HAL_OK;
}

/**
  * @brief Get input channel's source
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @warning the channel is supposed to be disabled
  * @retval hal_lptim_ic_src_t channel input sources
  */
hal_lptim_ic_src_t HAL_LPTIM_IC_GetChannelSource(const hal_lptim_handle_t *hlptim,
                                                 hal_lptim_channel_t channel)
{
  STM32_UNUSED(channel);

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (HAL_LPTIM_IC_CHANNEL_STATE_IDLE | HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE));

  return LPTIM_ConvertLLToHALIcx(hlptim, channel, LL_LPTIM_GetRemap(p_lptim));
}

/**
  * @brief Set input channel's polarity
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param polarity input channel's polarity
  * @warning the channel is supposed to be disabled
  * @retval HAL_OK LPTIM input channel's polarity correctly setup
  */
hal_status_t HAL_LPTIM_IC_SetChannelPolarity(const hal_lptim_handle_t *hlptim,
                                             hal_lptim_channel_t channel,
                                             hal_lptim_ic_polarity_t polarity)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_INIT);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(LPTIM_INSTANCE(hlptim)));

  /* Check channel polarity parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_IC_POLARITY(polarity));

  /* Control the channel state (to be checked) */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (LPTIM_CHANNEL_STATE_IDLE));

  LL_LPTIM_IC_SetPolarity(LPTIM_INSTANCE(hlptim), channel, polarity);

  /* Note: Setting the channel has output is done in the start function. */
  return HAL_OK;
}

/**
  * @brief Get input channel's polarity
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @return hal_lptim_ic_polarity_t input channel's polarity mode
  */
hal_lptim_ic_polarity_t HAL_LPTIM_IC_GetChannelPolarity(const hal_lptim_handle_t *hlptim,
                                                        hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_ic_polarity_t)LL_LPTIM_IC_GetPolarity(LPTIM_INSTANCE(hlptim),
                                                          channel);
}

/**
  * @brief Set input channel's filter
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param filter input channel's filter
  * @warning the channel is supposed to be disabled
  * @retval HAL_OK LPTIM input channel's filter correctly setup
  */
hal_status_t HAL_LPTIM_IC_SetChannelFilter(const hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           hal_lptim_filter_t filter)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_INIT);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Check channel polarity parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(filter));

  /* Control the channel state (to be checked) */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (LPTIM_CHANNEL_STATE_IDLE));

  LL_LPTIM_IC_SetFilter(p_lptim, channel, LPTIM_CCMR1_HAL2LL_FILTER(filter));

  /* Note: Setting the channel has output is done in the start function. */
  return HAL_OK;
}

/**
  * @brief Get input channel's filter
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @return hal_lptim_filter_t input channel's filter mode
  */
hal_lptim_filter_t HAL_LPTIM_IC_GetChannelFilter(const hal_lptim_handle_t *hlptim,
                                                 hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_filter_t)LPTIM_CCMR1_LL2HAL_FILTER(LL_LPTIM_IC_GetFilter(LPTIM_INSTANCE(hlptim), channel));
}

/**
  * @brief Set input channel's prescaler
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param prescaler input channel's prescaler
  * @warning the channel is supposed to be disabled
  * @retval HAL_OK LPTIM input channel's prescaler correctly setup
  */
hal_status_t HAL_LPTIM_IC_SetChannelPrescaler(const hal_lptim_handle_t *hlptim,
                                              hal_lptim_channel_t channel,
                                              hal_lptim_ic_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Check channel polarity parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_IC_PRESCALER(prescaler));

  /* Control the channel state (to be checked) */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   (LPTIM_CHANNEL_STATE_IDLE));

  LL_LPTIM_IC_SetPrescaler(p_lptim, channel, (uint32_t)prescaler);

  return HAL_OK;
}

/**
  * @brief Get input channel's prescaler
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @return hal_lptim_ic_prescaler_t input channel's prescaler mode
  */
hal_lptim_ic_prescaler_t HAL_LPTIM_IC_GetChannelPrescaler(const hal_lptim_handle_t *hlptim,
                                                          hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_ic_prescaler_t)LL_LPTIM_IC_GetPrescaler(LPTIM_INSTANCE(hlptim), channel);
}

/**
  * @brief Start channel LPTIM driver with input channel/input capture
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @retval HAL_OK input channel has been correctly started
  */
hal_status_t HAL_LPTIM_IC_StartChannel(hal_lptim_handle_t *hlptim,
                                       hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_IC_CHANNEL_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hlptim, channel_states[channel],
                         HAL_LPTIM_IC_CHANNEL_STATE_IDLE,
                         HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE);

  /* Set the channel as output. */
  LL_LPTIM_CC_SetChannelMode(p_lptim, channel,
                             LL_LPTIM_CCMODE_INPUTCAPTURE);

  /* Enable channel */
  LL_LPTIM_CC_EnableChannel(p_lptim, channel);

  return HAL_OK;
}

/**
  * @brief Stop channel LPTIM driver with input channel/input capture
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @retval HAL_OK input channel has been correctly stopped
  */
hal_status_t HAL_LPTIM_IC_StopChannel(hal_lptim_handle_t *hlptim,
                                      hal_lptim_channel_t channel)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE);

  /* Disable the channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  status = LPTIM_CcDisable(p_lptim);

  hlptim->channel_states[channel] = HAL_LPTIM_IC_CHANNEL_STATE_IDLE;

  return status;
}

/**
  * @brief Start channel LPTIM driver input channel/input capture with interrupt
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @retval HAL_ERROR No flag has been given
  * @retval HAL_OK input channel has been correctly started
  */
hal_status_t HAL_LPTIM_IC_StartChannel_IT(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_IC_CHANNEL_STATE_IDLE);
  HAL_CHECK_UPDATE_STATE(hlptim, channel_states[channel],
                         HAL_LPTIM_IC_CHANNEL_STATE_IDLE,
                         HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE);

  LL_LPTIM_Enable(p_lptim);

  /* Clear flag */
  LL_LPTIM_ClearFlag_DIEROK(p_lptim);
  LL_LPTIM_WRITE_REG(p_lptim, ICR, LL_LPTIM_ISR_DIEROK);

  /* Enable Compare interrupt */
  if (channel == HAL_LPTIM_CHANNEL_1)
  {
    LL_LPTIM_EnableIT_CC1(p_lptim);
  }
  else /* necessary channel 2 (checked only by assert) */
  {
    LL_LPTIM_EnableIT_CC2(p_lptim);
  }

  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

  /* Set the channel as output. */
  LL_LPTIM_CC_SetChannelMode(p_lptim, channel,
                             LL_LPTIM_CCMODE_INPUTCAPTURE);

  /* Enable channel */
  LL_LPTIM_CC_EnableChannel(p_lptim, channel);

  return HAL_OK;
}

/**
  * @brief Stop channel LPTIM driver input channel/input capture with interrupt compare
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @retval HAL_ERROR No flags have been given.
  * @retval HAL_OK input channel has been correctly stopped
  */
hal_status_t HAL_LPTIM_IC_StopChannel_IT(hal_lptim_handle_t *hlptim,
                                         hal_lptim_channel_t channel)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE);

  /* Disable the channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  LL_LPTIM_Enable(p_lptim);

  /* Disable Compare interrupt */
  if (channel == HAL_LPTIM_CHANNEL_1)
  {
    LL_LPTIM_DisableIT_CC1(p_lptim);
  }
  else /* necessary channel 2 (checked only by assert) */
  {
    LL_LPTIM_DisableIT_CC2(p_lptim);
  }

  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

  status = LPTIM_CcDisable(p_lptim);

  hlptim->channel_states[channel] = HAL_LPTIM_IC_CHANNEL_STATE_IDLE;

  return status;
}

/**
  * @brief Start channel LPTIM driver input channel/input capture with DMA
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param p_data pointer to the data buffer
  * @param size_byte data buffer size
  * @retval HAL_ERROR No flag has been given
  * @retval HAL_OK input channel has been correctly started
  */
#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
hal_status_t HAL_LPTIM_IC_StartChannel_DMA(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel,
                                           const void *p_data,
                                           uint32_t size_byte)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* use_hal_check_param */

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(LPTIM_INSTANCE(hlptim)));

  /* Check the instance is supported by DMA interrupt mode */
  ASSERT_DBG_PARAM((IS_LPTIM_DMA_INSTANCE(LPTIM_INSTANCE(hlptim))));

  /* control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_IC_CHANNEL_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hlptim, channel_states[channel],
                         HAL_LPTIM_IC_CHANNEL_STATE_IDLE,
                         HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE);

  return LPTIM_IC_StartChannel_DMA_Opt(hlptim, channel, p_data, size_byte, HAL_LPTIM_OPT_DMA_IT_DEFAULT);
}

/**
  * @brief Start channel LPTIM driver input channel/input capture with DMA
  *
  * @param hlptim Pointer to a hal_lptim_handle_t
  * @param channel    Output channel of interest to enable.
  * @param p_data pointer to the data buffer
  * @param size_byte data buffer size
  * @param  interrupts Selection of the DMA interrupts.
  *                    Can be any of the (meaningful) those values:
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_NONE
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_HT
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_DEFAULT
  * @if (USE_HAL_DMA_LINKEDLIST)
  *                    - @ref HAL_LPTIM_OPT_DMA_IT_SILENT
  * @endif
  * @retval HAL_ERROR No flag has been given
  * @retval HAL_OK input channel has been correctly started
  */
hal_status_t HAL_LPTIM_IC_StartChannel_DMA_Opt(hal_lptim_handle_t *hlptim,
                                               hal_lptim_channel_t channel,
                                               const void *p_data,
                                               uint32_t size_byte,
                                               uint32_t interrupts)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* use_hal_check_param */

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(LPTIM_INSTANCE(hlptim)));

  /* Check the instance is supported by DMA interrupt mode */
  ASSERT_DBG_PARAM(IS_LPTIM_DMA_INSTANCE(LPTIM_INSTANCE(hlptim)));

  /* control the channel state and update it. */
  ASSERT_DBG_STATE(hlptim->channel_states[channel],
                   HAL_LPTIM_IC_CHANNEL_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hlptim, channel_states[channel],
                         HAL_LPTIM_IC_CHANNEL_STATE_IDLE,
                         LPTIM_IC_CHANNEL_STATE_ACTIVE(interrupts));

  return LPTIM_IC_StartChannel_DMA_Opt(hlptim, channel, p_data, size_byte, interrupts);
}

/**
  * @brief  Stop a timer's input channel that was started in DMA mode.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @param  channel Input Channel of interest.
  * @retval HAL_OK Input Capture with DMA has correctly been stopped
  */
hal_status_t HAL_LPTIM_IC_StopChannel_DMA(hal_lptim_handle_t *hlptim,
                                          hal_lptim_channel_t channel)
{
  hal_status_t status;
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  /* Check the instance can support Input Capture mode */
  ASSERT_DBG_PARAM(IS_LPTIM_INPUT_CAPTURE_INSTANCE(p_lptim));

  /* Check the instance can support DMA interrupt mode */
  ASSERT_DBG_PARAM(IS_LPTIM_DMA_INSTANCE(p_lptim));

  hal_lptim_channel_state_t channel_state = hlptim->channel_states[channel];

  /* Ensure that the channel is in active or active silent mode */
  ASSERT_DBG_STATE(channel_state,
                   HAL_LPTIM_IC_CHANNEL_STATE_ACTIVE);

  /* Stop DMA transfer and disable compare match DMA request */
  LPTIM_IC_StopChannel_DMA(hlptim, p_lptim, channel,
                           (IS_LPTIM_ACTIVE_SILENT(channel_state)));

  /* Disable the channel */
  LL_LPTIM_CC_DisableChannel(p_lptim, channel);

  status = LPTIM_CcDisable(p_lptim);
  hlptim->channel_states[channel] = HAL_LPTIM_IC_CHANNEL_STATE_IDLE;

  return status;
}
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief  Read value captured of timer's input channel.
  * @param  hlptim    Pointer to the handle of the LPTIM instance.
  * @param  channel Input Channel of interest.
  * @retval uint32_t  Value captured of timer's input channel
  */
uint32_t HAL_LPTIM_IC_ReadChannelCapturedValue(const hal_lptim_handle_t *hlptim,
                                               hal_lptim_channel_t channel)
{
  uint32_t capture_value;

  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check if the channel is supported by the instance */
  ASSERT_DBG_PARAM(IS_LPTIM_CHANNEL(channel));

  switch (channel)
  {
    case HAL_LPTIM_CHANNEL_1:
      capture_value = LL_LPTIM_READ_REG(p_lptim, CCR1);
      break;
    case HAL_LPTIM_CHANNEL_2:
      capture_value = LL_LPTIM_READ_REG(p_lptim, CCR2);
      break;
    default:
      capture_value = 0;
      break;
  }
  return capture_value;
}

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group7
  *  @{
  *  This group contains the functions used to configure the encoder stage of the timer.
  *     - Call HAL_LPTIM_SetConfigEncoder() to set the config for the encoder.
  *     - Call HAL_LPTIM_GetConfigEncoder() to get the config for the encoder.
  *
  */

/**
  * @brief  Configure the encoder interface.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  p_encoder Pointer to the encoder configuration structure.
  * @retval HAL_OK   Configuration correctly set.
  */
hal_status_t HAL_LPTIM_SetConfigEncoder(const hal_lptim_handle_t *hlptim,
                                        const hal_lptim_encoder_config_t *p_encoder)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_encoder != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(p_encoder->filter));

  ASSERT_DBG_PARAM(IS_LPTIM_ENCODER_INTERFACE_INSTANCE(p_lptim));

  /* The signals frequency on both Input1 and Input2 inputs must not exceed the LPTIM internal
    clock frequency divided by 4.*/
  ASSERT_DBG_PARAM((p_encoder->filter <= HAL_LPTIM_FDIV1_N4));

  /* Setup source input */
  LL_LPTIM_SetInput1Source(p_lptim, (uint32_t)p_encoder->input1);
  LL_LPTIM_SetInput2Source(p_lptim, (uint32_t)p_encoder->input2);
  /* Setup divider filter */
  LL_LPTIM_SetClockFilter(p_lptim, LPTIM_CFGR_HAL2LL_FILTER(p_encoder->filter));

  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);

  LL_LPTIM_Disable(p_lptim);

  /* Enable the encoder mode */
  LL_LPTIM_EnableEncoderMode(p_lptim);

  /* Restore lptim state */
  if (is_lptim_enabled == 1U)
  {
    LL_LPTIM_Enable(p_lptim);
  }
  return HAL_OK;
}

/**
  * @brief Get encoder interface configuration.
  * @param hlptim Pointer to the handle of the LPTIM instance.
  * @param p_encoder Pointer to the encoder configuration structure.
  */
void HAL_LPTIM_GetConfigEncoder(const hal_lptim_handle_t *hlptim,
                                hal_lptim_encoder_config_t *p_encoder)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_encoder != NULL));

  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE);

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Get sources input information */
  p_encoder->input1 = (hal_lptim_input1_src_t)LL_LPTIM_GetInput1Source(p_lptim);
  p_encoder->input2 = (hal_lptim_input2_src_t)LL_LPTIM_GetInput2Source(p_lptim);
  p_encoder->filter = (hal_lptim_filter_t)(LPTIM_GET_CLOCK_FILTER(p_lptim));
}

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group8
  *  @{
  *  This section provides a set of function to configure external trigger
  *      - Call HAL_LPTIM_SetConfigExtTrigInput() Set External trigger input
  *      - Call HAL_LPTIM_GetConfigExtTrigInput() Get Configuration external trigger input
  *      - Call HAL_LPTIM_SetExtTrigInputSource() Set external trigger input Source
  *      - Call HAL_LPTIM_GetExtTrigInputSource() Get External trigger input Source
  *      - Call HAL_LPTIM_SetExtTrigInputPolarity() Set External trigger input Polarity
  *      - Call HAL_LPTIM_GetExtTrigInputPolarity() Get external trigger input Polarity
  *      - Call HAL_LPTIM_SetExtTrigInputFilter() Set External trigger input Filter
  *      - Call HAL_LPTIM_GetExtTrigInputFilter() Get external trigger input Filter
  */

/**
  * @brief  Configure External Trigger (ETR) input.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  p_config Pointer to the ETR configuration structure.
  * @retval HAL_OK   Configuration correctly set.
  */
hal_status_t HAL_LPTIM_SetConfigExtTrigInput(const hal_lptim_handle_t *hlptim,
                                             const hal_lptim_ext_trig_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  /* Check configuration parameters */
  ASSERT_DBG_PARAM(IS_LPTIM_EXT_TRIG_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(p_config->filter));

  /* Configure ETR input (the peripheral is supposed to be disabled) */
  uint32_t is_lptim_enabled = LL_LPTIM_IsEnabled(p_lptim);
  LL_LPTIM_Disable(p_lptim);

  uint32_t trig_src = LPTIM_ConvertHALToLLExttrig(hlptim, p_config->source);
  LL_LPTIM_ConfigTrigger(p_lptim,
                         (uint32_t)trig_src,
                         (uint32_t)(p_config->filter) << LPTIM_CFGR_TRGFLT_Pos,
                         (uint32_t)p_config->polarity);

  /* Enable external trigger interrupt */
  LL_LPTIM_Enable(p_lptim);

  /* Enable the encoder mode */
  LL_LPTIM_EnableIT_EXTTRIG(p_lptim);
  if (lptim_wait_flag(p_lptim, LL_LPTIM_IsActiveFlag_DIEROK) != 0U)
  {
    return HAL_ERROR;
  }

  if (is_lptim_enabled == 0U)
  {
    LL_LPTIM_Disable(p_lptim);
  }

  return HAL_OK;
}

/**
  * @brief  Get the External Trigger (ETR) input configuration.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  p_config Pointer to the ETR configuration structure.
  */
void HAL_LPTIM_GetConfigExtTrigInput(const hal_lptim_handle_t *hlptim,
                                     hal_lptim_ext_trig_config_t *p_config)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  volatile uint32_t cfgr = LL_LPTIM_READ_REG(LPTIM_INSTANCE(hlptim), CFGR);

  p_config->polarity = (hal_lptim_ext_trig_polarity_t)LPTIM_GET_ETR_POLARITY(cfgr);
  p_config->filter = (hal_lptim_filter_t)(uint32_t)(LPTIM_GET_ETR_FILTER(cfgr) >> LPTIM_CFGR_TRGFLT_Pos);
  p_config->source = (hal_lptim_ext_trig_src_t)LPTIM_ConvertLLToHALExttrig(hlptim, LPTIM_GET_ETR_SOURCE(cfgr));
}

/**
  * @brief  Set the External Trigger (ETR) input source.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  source  Source selection for the ETR.
  * @retval HAL_OK External Trigger Input Src has been configured correctly
  */
hal_status_t HAL_LPTIM_SetExtTrigInputSource(const hal_lptim_handle_t *hlptim,
                                             hal_lptim_ext_trig_src_t source)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  uint32_t trig_src = LPTIM_ConvertHALToLLExttrig(hlptim, source);

  /* Set the ETR source (the peripheral is supposed to be disabled) */
  LL_LPTIM_SetTriggerSource(p_lptim, (uint32_t)trig_src);

  return HAL_OK;
}

/**
  * @brief  Get the External Trigger (ETR) input source.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_ext_trig_src_t Source selected for the ETR.
  */
hal_lptim_ext_trig_src_t HAL_LPTIM_GetExtTrigInputSource(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  uint32_t trig_src = LL_LPTIM_GetTriggerSource(LPTIM_INSTANCE(hlptim));

  return (LPTIM_ConvertLLToHALExttrig(hlptim, trig_src));
}

/**
  * @brief  Set the External Trigger (ETR) input polarity.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @param  polarity Polarity of the ETR input.
  * @retval HAL_OK External Trigger Input Polarity has configured correctly
  */
hal_status_t HAL_LPTIM_SetExtTrigInputPolarity(const hal_lptim_handle_t *hlptim,
                                               hal_lptim_ext_trig_polarity_t polarity)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_EXT_TRIG_POLARITY(polarity));

  /* Set the ETR polarity (the peripheral is supposed to be disabled) */
  LL_LPTIM_SetTriggerPolarity(p_lptim, (uint32_t)polarity);

  return HAL_OK;
}

/**
  * @brief  Get the External Trigger (ETR) input polarity.
  * @param  hlptim   Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_ext_trig_polarity_t External trigger polarity.
  */
hal_lptim_ext_trig_polarity_t HAL_LPTIM_GetExtTrigInputPolarity(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return ((hal_lptim_ext_trig_polarity_t)
          LL_LPTIM_GetTriggerPolarity(LPTIM_INSTANCE(hlptim)));
}

/**
  * @brief  Set the External Trigger (ETR) input filter.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  filter  Filter the ETR input.
  * @retval HAL_OK External Trigger Input Filter has configured correctly
  */
hal_status_t HAL_LPTIM_SetExtTrigInputFilter(const hal_lptim_handle_t *hlptim,
                                             hal_lptim_filter_t filter)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  ASSERT_DBG_PARAM(IS_LPTIM_FILTER(filter));

  /* Set the ETR filter (the peripheral is supposed to be disabled) */
  LL_LPTIM_SetTriggerFilter(p_lptim,
                            (uint32_t)(filter) << LPTIM_CFGR_TRGFLT_Pos);

  return HAL_OK;
}

/**
  * @brief  Get the External Trigger (ETR) input filter.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @retval hal_lptim_filter_t Filter value for the ETR input.
  */
hal_lptim_filter_t HAL_LPTIM_GetExtTrigInputFilter(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  ASSERT_DBG_STATE(hlptim->global_state,
                   (HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE));

  return (hal_lptim_filter_t)(uint32_t)(LL_LPTIM_GetTriggerFilter(LPTIM_INSTANCE(hlptim)) >> LPTIM_CFGR_TRGFLT_Pos);
}

/**
  *  @}
  */

/** @addtogroup LPTIM_Exported_Functions_Group9 Low Power Timer IRQ Handler and Callbacks functions
  *
  *  This section provides LPTIM IRQ Handler and callback function called within the IRQ Handler

  *     IRQ Handler:
       - Call HAL_LPTIM_IRQHandler() LPTIM interrupt global request handler
       - Call HAL_LPTIM_UPD_IRQHandler() LPTIM interrupt Update request handler
       - Call HAL_LPTIM_CC_IRQHandler() LPTIM interrupt Capture/Compare request handler
       - Call HAL_LPTIM_TRGI_IRQHandler() LPTIM interrupt Trigger Direction request handler

        Weak Callback:
       - Call HAL_LPTIM_ErrorCallback() Error Callback
       - Call HAL_LPTIM_StopCallback() Stop Callback
       - Call HAL_LPTIM_InputCaptureStopCallback() Channel Stop Callback
       - Call HAL_LPTIM_UpdateCallback() Update Callback
       - Call HAL_LPTIM_UpdateHalfCpltCallback() Update Half Cplt Callback
       - Call HAL_LPTIM_RepUpdateCallback() Rep Update Callback
       - Call HAL_LPTIM_TriggerCallback() Trigger Callback
       - Call HAL_LPTIM_InputCaptureCallback() Input Capture Callback
       - Call HAL_LPTIM_InputCaptureHalfCpltCallback() Input Capture Half Cplt Callback
       - Call HAL_LPTIM_InputOverCaptureCallback() Input Over Capture Callback
       - Call HAL_LPTIM_CompareMatchCallback() Compare Match Callback
       - Call HAL_LPTIM_CompareMatchHalfCpltCallback() Compare Match Half Cplt Callback
       - Call HAL_LPTIM_CompareUpdateCallback() Compare Update Callback
       - Call HAL_LPTIM_AutoReloadMatchCallback() AutoReload Match Callback
       - Call HAL_LPTIM_AutoReloadUpdateCallback() AutoReload Update Callback
       - Call HAL_LPTIM_DirectionUpCallback() Direction Up Callback
       - Call HAL_LPTIM_DirectionDownCallback() Direction Down Callback

       And there register callback:
       - Call HAL_LPTIM_RegisterErrorCallback() Error Callback
       - Call HAL_LPTIM_RegisterStopCallback() Stop Callback
       - Call HAL_LPTIM_RegisterChannelStopCallback() Stop Callback
       - Call HAL_LPTIM_RegisterUpdateCallback() Update Callback
       - Call HAL_LPTIM_RegisterUpdateHalfCpltCallback() Update Half Cplt Callback
       - Call HAL_LPTIM_RegisterRepUpdateCallback() Rep Update Callback
       - Call HAL_LPTIM_RegisterTriggerCallback() Trigger Callback
       - Call HAL_LPTIM_RegisterInputCaptureCallback() Input Capture Callback
       - Call HAL_LPTIM_RegisterInputCaptureHalfCpltCallback() Input Capture Half Cplt Callback
       - Call HAL_LPTIM_RegisterOverCaptureCallback() Input Over Capture Callback
       - Call HAL_LPTIM_RegisterCompareMatchCallback() Compare Match Callback
       - Call HAL_LPTIM_RegisterCompareUpdateCallback() Compare Update Callback
       - Call HAL_LPTIM_RegisterAutoReloadMatchCallback() AutoReload Match Callback
       - Call HAL_LPTIM_RegisterAutoReloadUpdateCallback() AutoReload Update Callback
       - Call HAL_LPTIM_RegisterDirectionUpCallback() Direction Up Callback
       - Call HAL_LPTIM_RegisterDirectionDownCallback() Direction Down Callback
  *  @{
  */

/**
  * @brief  Handler IRQ global.
  *      - Capture/Compare 1 interrupt
  *      - Capture/Compare 2 interrupt
  *      - Compare update interrupt
  *      - Over Capture 1 & 2 interrupt
  *      - Autoreload matched interrupt
  *      - Autoreload update interrupt
  *      - Trigger detected interrupt
  *      - Direction counter changed from down to up
  *      - Direction counter changed from up to down
  *      - Repetition counter underflowed or == 0 and LPTIM counter overflow
  *      - Successful APB bus write to repetition counter register
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
void HAL_LPTIM_IRQHandler(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  const uint32_t isr = LL_LPTIM_READ_REG(p_lptim, ISR);
  const uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);

  /* Capture compare 1 interrupt caught */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_CC1IF) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CC1IE))
  {
    LL_LPTIM_ClearFlag_CC1(p_lptim); /* Clear flag */
    uint32_t ccmr1 = LL_LPTIM_READ_REG(p_lptim, CCMR1);
    /* input capture catching an event in*/
    if (IS_LPTIM_ACTIVEFLAG(ccmr1, LPTIM_CCMR1_CC1SEL) == 1U)
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->input_capture_callback(hlptim, HAL_LPTIM_CHANNEL_1);
#else
      HAL_LPTIM_InputCaptureCallback(hlptim, HAL_LPTIM_CHANNEL_1);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
    else
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->compare_match_callback(hlptim, HAL_LPTIM_CHANNEL_1);
#else
      HAL_LPTIM_CompareMatchCallback(hlptim, HAL_LPTIM_CHANNEL_1);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
  }
  /* Capture compare 2 interrupt caught */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_CC2IF) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CC2IE))
  {
    LL_LPTIM_ClearFlag_CC2(p_lptim); /* Clear flag */
    uint32_t ccmr1 = LL_LPTIM_READ_REG(p_lptim, CCMR1);
    if (IS_LPTIM_ACTIVEFLAG(ccmr1, LPTIM_CCMR1_CC2SEL) == 1U)
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->input_capture_callback(hlptim, HAL_LPTIM_CHANNEL_2);
#else
      HAL_LPTIM_InputCaptureCallback(hlptim, HAL_LPTIM_CHANNEL_2);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
    else
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->compare_match_callback(hlptim, HAL_LPTIM_CHANNEL_2);
#else
      HAL_LPTIM_CompareMatchCallback(hlptim, HAL_LPTIM_CHANNEL_2);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
  }
  /* Compare update interrupt Channel 1*/
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_CMP1OK) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CMP1OKIE))
  {
    LL_LPTIM_ClearFlag_CMP1OK(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->compare_update_callback(hlptim, HAL_LPTIM_CHANNEL_1);
#else
    HAL_LPTIM_CompareUpdateCallback(hlptim, HAL_LPTIM_CHANNEL_1);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Compare update interrupt Channel 2*/
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_CMP2OK) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CMP2OKIE))
  {
    LL_LPTIM_ClearFlag_CMP2OK(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->compare_update_callback(hlptim, HAL_LPTIM_CHANNEL_2);
#else
    HAL_LPTIM_CompareUpdateCallback(hlptim, HAL_LPTIM_CHANNEL_2);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Over capture 1 interrupt caught */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_CC1OF) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CC1OIE))
  {
    LL_LPTIM_ClearFlag_CC1O(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->input_over_capture_callback(hlptim, HAL_LPTIM_CHANNEL_1);
#else
    HAL_LPTIM_InputOverCaptureCallback(hlptim, HAL_LPTIM_CHANNEL_1);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Over capture 2 interrupt caught */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_CC2OF) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CC2OIE))
  {
    LL_LPTIM_ClearFlag_CC2O(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->input_over_capture_callback(hlptim, HAL_LPTIM_CHANNEL_2);
#else
    HAL_LPTIM_InputOverCaptureCallback(hlptim, HAL_LPTIM_CHANNEL_2);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Autoreload matched interrupt */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_ARRM) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_ARRMIE))
  {
    LL_LPTIM_ClearFlag_ARRM(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->auto_reload_match_callback(hlptim);
#else
    HAL_LPTIM_AutoReloadMatchCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Autoreload update interrupt */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_ARROK) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_ARROKIE))
  {
    LL_LPTIM_ClearFlag_ARROK(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->auto_reload_update_callback(hlptim);
#else
    HAL_LPTIM_AutoReloadUpdateCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Trigger detected interrupt */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_EXTTRIG) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_EXTTRIGIE))
  {
    LL_LPTIM_ClearFlag_EXTTRIG(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->trigger_callback(hlptim);
#else
    HAL_LPTIM_TriggerCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Direction counter changed from up to down */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_DOWN) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_DOWNIE))
  {
    LL_LPTIM_ClearFlag_DOWN(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->direction_down_callback(hlptim);
#else
    HAL_LPTIM_DirectionDownCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Direction counter changed from down to up */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_UP) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_UPIE))
  {
    LL_LPTIM_ClearFlag_UP(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->direction_up_callback(hlptim);
#else
    HAL_LPTIM_DirectionUpCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Repetition counter underflowed or == 0 and LPTIM counter overflow */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_UE) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_UEIE))
  {
    LL_LPTIM_ClearFlag_UE(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->update_callback(hlptim);
#else
    HAL_LPTIM_UpdateCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
  /* Successful APB bus write to repetition counter register */
  if ((LPTIM_IS_INTERRUPT_FLAG(isr, LPTIM_ISR_REPOK) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_REPOKIE))
  {
    LL_LPTIM_ClearFlag_REPOK(p_lptim); /* Clear flag */
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->rep_update_callback(hlptim);
#else
    HAL_LPTIM_RepUpdateCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handler IRQ for interrupt's capture and compare.
  * - Capture/Compare 1 interrupt
  * - Capture/Compare 2 interrupt
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
void HAL_LPTIM_CC_IRQHandler(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  const uint32_t isr = LL_LPTIM_READ_REG(p_lptim, ISR);
  const uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);

  /* Capture compare 1 interrupt caught */
  if ((IS_LPTIM_ACTIVEFLAG(isr, LPTIM_ISR_CC1IF) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CC1IE))
  {
    LL_LPTIM_ClearFlag_CC1(p_lptim); /* Clear flag */
    uint32_t ccmr1 = LL_LPTIM_READ_REG(p_lptim, CCMR1);
    /* input capture catching an event in*/
    if (IS_LPTIM_ACTIVEFLAG(ccmr1, LPTIM_CCMR1_CC1SEL) == 1U)
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->input_capture_callback(hlptim, HAL_LPTIM_CHANNEL_1);
#else
      HAL_LPTIM_InputCaptureCallback(hlptim, HAL_LPTIM_CHANNEL_1);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
    else
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->compare_match_callback(hlptim, HAL_LPTIM_CHANNEL_1);
#else
      HAL_LPTIM_CompareMatchCallback(hlptim, HAL_LPTIM_CHANNEL_1);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
  }
  /* Capture compare 2 interrupt caught */
  if ((IS_LPTIM_ACTIVEFLAG(isr, LPTIM_ISR_CC2IF) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_CC2IE))
  {
    LL_LPTIM_ClearFlag_CC2(p_lptim); /* Clear flag */
    uint32_t ccmr1 = LL_LPTIM_READ_REG(p_lptim, CCMR1);
    if (IS_LPTIM_ACTIVEFLAG(ccmr1, LPTIM_CCMR1_CC2SEL) == 1U)
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->input_capture_callback(hlptim, HAL_LPTIM_CHANNEL_2);
#else
      HAL_LPTIM_InputCaptureCallback(hlptim, HAL_LPTIM_CHANNEL_2);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
    else
    {
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
      hlptim->compare_match_callback(hlptim, HAL_LPTIM_CHANNEL_2);
#else
      HAL_LPTIM_CompareMatchCallback(hlptim, HAL_LPTIM_CHANNEL_2);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  Handler IRQ for Update interrupt's.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
void HAL_LPTIM_UPD_IRQHandler(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  const uint32_t isr = LL_LPTIM_READ_REG(p_lptim, ISR);
  const uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);

  /* Repetition counter underflowed or == 0 and LPTIM counter overflow */
  if ((IS_LPTIM_ACTIVEFLAG(isr, LPTIM_ISR_UE) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_UEIE))
  {
    LL_LPTIM_ClearFlag_UE(p_lptim);
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->update_callback(hlptim);
#else
    HAL_LPTIM_UpdateCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handler IRQ for trigger and direction change interrupt's.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
void HAL_LPTIM_TRGI_IRQHandler(hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  lptim_t *p_lptim = LPTIM_INSTANCE(hlptim);

  const uint32_t isr = LL_LPTIM_READ_REG(p_lptim, ISR);
  const uint32_t dier = LL_LPTIM_READ_REG(p_lptim, DIER);

  /* Trigger detected interrupt */
  if ((IS_LPTIM_ACTIVEFLAG(isr, LPTIM_ISR_EXTTRIG) == 1U)
      && LPTIM_IS_ENABLED_IT(dier, LPTIM_DIER_EXTTRIGIE))
  {
    LL_LPTIM_ClearFlag_EXTTRIG(p_lptim);
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)
    hlptim->trigger_callback(hlptim);
#else
    HAL_LPTIM_TriggerCallback(hlptim);
#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */
  }
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
/**
  * @brief Update Half Complete callback.\n
  *        Function called when the DMA transfer triggered by the timer update
  *        DMA request is half completed.
  * @param hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_UpdateHalfCpltCallback(hal_lptim_handle_t *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_UpdateHalfCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief DMA Error callback. \n
  *        This function is called in case of a DMA transfer error.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_ErrorCallback(hal_lptim_handle_t *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_ErrorCallback can be implemented in the user file.
   */
}

/**
  * @brief DMA Stop callback. \n
  *        This function is called after stopping a DMA transfer triggered
  *        by the timer update event.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_StopCallback(hal_lptim_handle_t *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_StopCallback can be implemented in the user file.
   */
}

/**
  * @brief DMA Channel Stop callback. \n
  *        This function is called after stopping a DMA transfer triggered
  *        by a capture/compare event.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel Input Channel of interest.
  */
__WEAK void HAL_LPTIM_InputCaptureStopCallback(hal_lptim_handle_t *hlptim,
                                               hal_lptim_channel_t channel)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hlptim);
  STM32_UNUSED(channel);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_InputCaptureStopCallback can be implemented in the user file.
   */
}
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief Update callback. \n
  *        Function called when the timer update interrupt is generated or when
  *        the DMA transfer triggered by the timer update DMA request is completed.
  *
  * @param hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_UpdateCallback(hal_lptim_handle_t *hlptim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_UpdateCallback can be implemented in the user file.
   */
}

/**
  * @brief Repetition Update Callback
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_RepUpdateCallback(hal_lptim_handle_t *hlptim)
{
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_RepUpdateCallback can be implemented in the user file.
   */
}

/**
  * @brief Trigger callback. \n
  *        Function called when the timer trigger interrupt is generated or when
  *        the DMA transfer triggered by the timer trigger DMA request is completed.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_TriggerCallback(hal_lptim_handle_t *hlptim)
{
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_TriggerCallback can be implemented in the user file.
   */
}

/**
  * @brief Input Capture Callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel    input channel of interest to enable.
  */
__WEAK void HAL_LPTIM_InputCaptureCallback(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel)
{
  STM32_UNUSED(hlptim);
  STM32_UNUSED(channel);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_InputCaptureCallback can be implemented in the user file.
   */
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
/**
  * @brief  Callback for the DMA Half Complete transfer triggered by an Input Capture event.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel    input channel of interest to enable.
  */
__WEAK void HAL_LPTIM_InputCaptureHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_channel_t channel)
{
  STM32_UNUSED(hlptim);
  STM32_UNUSED(channel);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_InputCaptureHalfCpltCallback can be implemented in the user file.
   */
}
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief Input Over Capture callback. \n
  *        Function called when an input over capture interrupt is generated.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel    input channel of interest to enable.
  */
__WEAK void HAL_LPTIM_InputOverCaptureCallback(hal_lptim_handle_t *hlptim,
                                               hal_lptim_channel_t channel)
{
  STM32_UNUSED(hlptim);
  STM32_UNUSED(channel);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_InputOverCaptureCallback can be implemented in the user file.
   */
}

/**
  * @brief Compare match Callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel    Output channel of interest to enable.
  */
__WEAK void HAL_LPTIM_CompareMatchCallback(hal_lptim_handle_t *hlptim,
                                           hal_lptim_channel_t channel)
{
  STM32_UNUSED(hlptim);
  STM32_UNUSED(channel);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_CompareMatchCallback can be implemented in the user file.
   */
}

/**
  * @brief Compare update Callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  channel    Output channel of interest to enable.
  */
__WEAK void HAL_LPTIM_CompareUpdateCallback(hal_lptim_handle_t *hlptim,
                                            hal_lptim_channel_t channel)
{
  STM32_UNUSED(hlptim);
  STM32_UNUSED(channel);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_CompareUpdateCallback can be implemented in the user file.
   */
}

/**
  * @brief AutoReload Match callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_AutoReloadMatchCallback(hal_lptim_handle_t *hlptim)
{
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_AutoReloadMatchCallback can be implemented in the user file.
   */
}

/**
  * @brief Autoreload Update callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_AutoReloadUpdateCallback(hal_lptim_handle_t *hlptim)
{
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_AutoReloadUpdateCallback can be implemented in the user file.
   */
}

/**
  * @brief Direction UP callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_DirectionUpCallback(hal_lptim_handle_t *hlptim)
{
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_DirectionUpCallback can be implemented in the user file.
   */
}

/**
  * @brief Direction Down callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  */
__WEAK void HAL_LPTIM_DirectionDownCallback(hal_lptim_handle_t *hlptim)
{
  STM32_UNUSED(hlptim);

  /*
   * NOTE: This function must preferably not be modified, when the callback is needed,
   *        HAL_LPTIM_DirectionDownCallback can be implemented in the user file.
   */
}

/* Interfaces for registering callbacks ***************************************/
#if defined(USE_HAL_LPTIM_REGISTER_CALLBACKS) && (USE_HAL_LPTIM_REGISTER_CALLBACKS == 1)

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)

/**
  * @brief  Callback registration for the DMA Error.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterErrorCallback(hal_lptim_handle_t *hlptim,
                                             hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(use_hal_check_param) && (use_hal_check_param == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* use_hal_check_param */

  hlptim->error_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Stop callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterStopCallback(hal_lptim_handle_t *hlptim,
                                            hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* use_hal_check_param */

  hlptim->error_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Channel Stop callback.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterChannelStopCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_channel_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* use_hal_check_param */

  hlptim->input_capture_stop_callback = fct;

  return HAL_OK;
}

#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief  Callback registration for the Update Event.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterUpdateCallback(hal_lptim_handle_t *hlptim,
                                              hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->update_callback = fct;

  return HAL_OK;
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)

/**
  * @brief  Callback registration for the DMA Half Complete transfer
  *            triggered on Update event
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterUpdateHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                                      hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->update_half_cplt_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief  Callback registration for Repetition Update.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterRepUpdateCallback(hal_lptim_handle_t *hlptim,
                                                 hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->rep_update_callback = fct;

  return HAL_OK;
}
/**
  * @brief  Callback registration for the Trigger event.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterTriggerCallback(hal_lptim_handle_t *hlptim,
                                               hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->trigger_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Input Capture event.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterInputCaptureCallback(hal_lptim_handle_t *hlptim,
                                                    hal_lptim_channel_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->input_capture_callback = fct;

  return HAL_OK;
}

#if defined(USE_HAL_LPTIM_DMA) && (USE_HAL_LPTIM_DMA == 1)
/**
  * @brief  Callback registration for the Input Capture Half Complete.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterInputCaptureHalfCpltCallback(hal_lptim_handle_t *hlptim,
                                                            hal_lptim_channel_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->input_capture_half_cplt_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_LPTIM_DMA */

/**
  * @brief  Callback registration for Over Capture.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterOverCaptureCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_channel_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->input_over_capture_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Compare Match.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterCompareMatchCallback(hal_lptim_handle_t *hlptim,
                                                    hal_lptim_channel_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->compare_match_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Compare Update.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterCompareUpdateCallback(hal_lptim_handle_t *hlptim,
                                                     hal_lptim_channel_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->compare_update_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Autoreload Update.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterAutoReloadUpdateCallback(hal_lptim_handle_t *hlptim,
                                                        hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->auto_reload_update_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the Autoreload Match.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterAutoReloadMatchCallback(hal_lptim_handle_t *hlptim,
                                                       hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->auto_reload_match_callback = fct;

  return HAL_OK;
}
/**
  * @brief  Callback registration for the Direction UP changes.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterDirectionUpCallback(hal_lptim_handle_t *hlptim,
                                                   hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->direction_up_callback = fct;

  return HAL_OK;
}
/**
  * @brief  Callback registration for the Direction Down changes.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK Register correctly setup
  * @retval HAL_INVALID_PARAM fct is NULL (only if USE_HAL_CHECK_PARAM == 1)
  */
hal_status_t HAL_LPTIM_RegisterDirectionDownCallback(hal_lptim_handle_t *hlptim,
                                                     hal_lptim_cb_t fct)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((fct != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hlptim->direction_down_callback = fct;

  return HAL_OK;
}

#endif /* USE_HAL_LPTIM_REGISTER_CALLBACKS */

/**
  *  @}
  */

#if defined(USE_HAL_LPTIM_USER_DATA) && (USE_HAL_LPTIM_USER_DATA == 1)
/** @addtogroup LPTIM_Exported_Functions_Group10
  *  The user data pointer, *p_user_data, in the HAL LPTIM handle allows user to associate applicative user
  *  data to the HAL LPTIM handle.
  *  The two functions in this group give an application the
  *  possibility to store and retrieve user data pointer into and
  *  from the handle.
  *  - Call HAL_LPTIM_SetUserData() Set user data
  *  - Call HAL_LPTIM_GetUserData() Get user data
  *  @{
  */

/**
  * @brief  Store User Data pointer into the handle.
  * @param  hlptim  Pointer to the handle of the LPTIM instance.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_LPTIM_SetUserData(hal_lptim_handle_t *hlptim, const void *p_user_data)
{
  ASSERT_DBG_PARAM((hlptim != NULL));
  ASSERT_DBG_PARAM((p_user_data != NULL));

  hlptim->p_user_data = p_user_data;
}

/**
  * @brief Retrieve User Data pointer from the handle.
  * @param hlptim  Pointer to the handle of the LPTIM instance.
  * @retval Pointer to the user data.
  */
const void *HAL_LPTIM_GetUserData(const hal_lptim_handle_t *hlptim)
{
  ASSERT_DBG_PARAM((hlptim != NULL));

  return hlptim->p_user_data;
}
/**
  *  @}
  */
#endif /* USE_HAL_LPTIM_USER_DATA */

/** @addtogroup LPTIM_Exported_Functions_Group11
  *  Get clock frequency depends on instance used.
  *  - Call HAL_LPTIM_GetClockFreq() Get the LPTIM instance kernel clock frequency
  *  @{
  */

/**
  * @brief  Return the peripheral clock frequency for LPTIMx
  * @param  hlptim Pointer to a hal_lptim_handle_t structure
  * @retval uint32_t Frequency in Hz
  * @retval 0 source clock of the lptimx not configured or not ready
  */
uint32_t HAL_LPTIM_GetClockFreq(hal_lptim_handle_t *hlptim)
{
  /* Check the LPTIM handle */
  ASSERT_DBG_PARAM((hlptim != NULL));

  /* Check the global state, the driver need to be at least configured */
  ASSERT_DBG_STATE(hlptim->global_state, HAL_LPTIM_STATE_INIT | HAL_LPTIM_STATE_IDLE | HAL_LPTIM_STATE_ACTIVE);
  return HAL_RCC_LPTIM_GetKernelClkFreq(LPTIM_INSTANCE(hlptim));
}

/**
  *  @}
  */

/**
  *  @}
  */

#endif /* USE_HAL_LPTIM_MODULE */

/**
  *  @}
  */

/**
  *  @}
  */

