/**
  ******************************************************************************
  * @file    stm32u5xx_hal_mdf.c
  * @brief   MDF HAL module driver.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup MDF
  * @{
# How to use the HAL MDF driver

## The HAL MDF driver can be used as follows:

MDFx HW IP is composed of a common clock generator and blocks.
Each block is composed of sub-blocks:
  - a serial interface.
  - a bitstream matrix.
  - a short-circuit detector.
  - a digital filter.
  - an out-of-limit detector.

Configuration and activation of common clock generator must be first performed.

### Common clock generator usage

1. Declare a hal_mdf_handle_t handle structure and initialize the MDFx driver with a MDFx HW instance by calling
   the HAL_MDF_Init().
   The MDFx clock is enabled inside the HAL_MDF_Init() if USE_HAL_MDF_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

2. Configure the low level hardware (GPIO, CLOCK, NVIC, DMA...):
  - Enable the MDFx clock if USE_HAL_MDF_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO.
  - MDFx pins configuration:
    - Enable the clock for the MDFx GPIOs
    - Configure MDFx pins as alternate function pull-up
  - NVIC configuration if you need to use interrupt process
    - Configure the MDFx interrupt priority.
    - Enable the NVIC MDFx IRQ handle.
  - DMA configuration if you need to use DMA process
    - Declare a DMA handle structure.
    - Enable the DMAx clock.
    - Configure the declared DMA handle structure with the required parameters.
    - Associate the initialized DMA handle to the MDF DMA handle using HAL_MDF_SetDMA().
    - Configure the corresponding NVIC line priority and enable it.
  - MDFx kernel source clock has to be activated and selected.

3. Configure the processing clock divider by calling HAL_MDF_SetConfig().

4. Configure and/or enable advanced features.
   All these advanced configurations are optional (not mandatory) and concerns:
  - Output clocks (for instance by calling HAL_MDF_SetConfigOutputClock() and HAL_MDF_EnableOutputClock()).
  - Interleaved filters (by calling HAL_MDF_SetInterleavedFilters).

5. Activate the clock generator by calling HAL_MDF_Start().

### Serial interface usage

1. Configure mode, clock source and threshold of a serial interface by calling HAL_MDF_SITF_SetConfig().

2. Activate a serial interface by calling HAL_MDF_SITF_Start().

3. Clock absence detection feature is available on each serial interface and can be used:
  - By calling HAL_MDF_SITF_IsClockAbsenceDetected in polling mode.
  - By calling HAL_MDF_SITF_StartClockAbsenceDetect_IT in interrupt mode.

### Bitstream matrix usage

Connect one serial interface to a bitstream matrix and select edge by calling HAL_MDF_BSMX_SetConfig().

### Short-circuit detector usage

1. Configure threshold and break signals of a short-circuit detector by calling HAL_MDF_SCD_SetConfig().

2. Activate a short-circuit detector:
  - By calling HAL_MDF_SCD_Start in polling mode.
  - By calling HAL_MDF_SCD_Start_IT in interrupt mode.

### Digital filter usage

1. Configure data source, CIC mode, decimation ratio, gain, acquisition mode and trigger parameters
   of a digital filter by calling HAL_MDF_DFLT_SetConfig().

2. Configure and/or enable advanced features.
   All these advanced configurations are optional (not mandatory) and concerns:
  - Samples delay by calling HAL_MDF_DFLT_SetSamplesDelay().
  - Offset compensation by calling HAL_MDF_DFLT_SetOffsetCompensation().
  - Integrator by calling HAL_MDF_DFLT_SetIntegrator().
  - FIFO threshold by calling HAL_MDF_DFLT_SetFifoThreshold().
  - Discard samples by calling HAL_MDF_DFLT_SetDiscardSamples().
  - Snapshot format by calling HAL_MDF_DFLT_SetSnapshotFormat().
  - Reshape filter by calling HAL_MDF_DFLT_EnableReshapeFilter().
  - High-pass filter by calling HAL_MDF_DFLT_EnableHighPassFilter().

3. Acquisitions.
  - Polling mode:
    - Start acquisition by calling HAL_MDF_DFLT_StartAcq().
    - Wait for the end of acquisition by calling HAL_MDF_DFLT_PollForAcq() or HAL_MDF_DFLT_PollForSnapshotAcq().
    - Get acquisition value by calling HAL_MDF_DFLT_GetAcqValue() or HAL_MDF_DFLT_GetSnapshotAcqValue().
    - Stop acquisition by calling HAL_MDF_DFLT_StopAcq().

  - Interrupt mode:
    - Start acquisition by calling HAL_MDF_DFLT_StartAcq_IT() or HAL_MDF_DFLT_StartAcq_IT_Opt().
    - Wait for the end of acquisition (HAL_MDF_DFLT_AcqCpltCallback() occurrence).
    - Get acquisition value by calling HAL_MDF_DFLT_GetAcqValue() or HAL_MDF_DFLT_GetSnapshotAcqValue().
    - Stop acquisition by calling HAL_MDF_DFLT_StopAcq_IT().

  - DMA mode:
    - Start acquisition by calling HAL_MDF_DFLT_StartAcq_DMA() or HAL_MDF_DFLT_StartAcq_DMA_Opt().
    - Wait for acquisitions (HAL_MDF_DFLT_AcqHalfCpltCallback() and HAL_MDF_DFLT_AcqCpltCallback() occurrences).
    - Stop acquisition by calling HAL_MDF_DFLT_StopAcq_DMA().

### Out-of-limit detector usage

1. Configure CIC order, decimation ratio, thresholds, event configuration and break signals of an
   out-of-limit detector by calling HAL_MDF_OLD_SetConfig().

2. Activate an out-of-limit detector:
  - By calling HAL_MDF_OLD_Start in polling mode.
  - By calling HAL_MDF_OLD_Start_IT in interrupt mode.

### Callbacks definition in interrupt or DMA mode:

  When the compilation define USE_HAL_MDF_REGISTER_CALLBACKS is set to 1, the user can configure dynamically the
  driver callbacks, via its own method:

Callback name               | Default value                      | Callback registration function
----------------------------| -----------------------------------| --------------------------------------------
DFLT_AcqCpltCallback        | HAL_MDF_DFLT_AcqCpltCallback()     | HAL_MDF_DFLT_RegisterAcqCpltCallback()
DFLT_AcqHalfCpltCallback    | HAL_MDF_DFLT_AcqHalfCpltCallback() | HAL_MDF_DFLT_RegisterAcqHalfCpltCallback()
DFLT_AcqStopCpltCallback    | HAL_MDF_DFLT_AcqStopCpltCallback() | HAL_MDF_DFLT_RegisterAcqStopCpltCallback()
OLD_Callback                | HAL_MDF_OLD_Callback()             | HAL_MDF_OLD_RegisterCallback()
ErrorCallback               | HAL_MDF_ErrorCallback()            | HAL_MDF_RegisterErrorCallback()

  If one needs to unregister a callback, register the default callback via the registration function.

  By default, after the HAL_MDF_Init() and when the state is @ref HAL_MDF_STATE_INIT, all callbacks are set to the
  corresponding default weak functions.

  Callbacks can be registered in handle global_state @ref HAL_MDF_STATE_INIT and @ref HAL_MDF_STATE_IDLE.

  When the compilation define USE_HAL_MDF_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
  feature is not available and weak callbacks are used, represented by the default value in the table above.

### Configuration inside the HAL MDF driver:

Config defines                 | Where            | Default value     | Note
-------------------------------| -----------------| ------------------| -------------------------------------------
USE_HAL_MDF_MODULE             | hal_conf.h       |         1         | Enable the HAL MDF module
USE_HAL_MDF_REGISTER_CALLBACKS | hal_conf.h       |         0         | Allow user to define his own callback
USE_HAL_MDF_CLK_ENABLE_MODEL   | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_MDF_USER_DATA          | hal_conf.h       |         0         | Add an user data inside HAL MDF handle
USE_HAL_MDF_GET_LAST_ERRORS    | hal_conf.h       |         0         | Enable retrieving last processes error codes
USE_HAL_MDF_DMA                | hal_conf.h       |         1         | Enable DMA code inside HAL MDF
USE_HAL_CHECK_PARAM            | hal_conf.h       |         0         | Enable checking of vital parameters at runtime
USE_HAL_CHECK_PROCESS_STATE    | hal_conf.h       |         0         | Enable atomic access to process state check
USE_ASSERT_DBG_PARAM           | PreProcessor env |        NONE       | Enable check parameters for HAL
USE_ASSERT_DBG_STATE           | PreProcessor env |        NONE       | Enable check state for HAL
  */

#if defined(USE_HAL_MDF_MODULE) && (USE_HAL_MDF_MODULE == 1)

/* Private macros ------------------------------------------------------------*/
/** @defgroup MDF_Private_Macros MDF Private Macros
  * @{
  */

/**
  * @brief Get MDF instance from the selected HAL MDF handle
  */
#define MDF_GET_INSTANCE(hmdf) ((MDF_TypeDef *)((uint32_t)(hmdf)->instance))

/**
  * @brief Get MDF block from the selected HAL MDF handle and index
  */
#define MDF_GET_BLOCK(hmdf, index) ((MDF_Block_TypeDef *)(((uint32_t)(hmdf)->instance) \
                                                          + (MDF1_BLOCK_SIZE * ((uint32_t)(index) + 1U))))

/**
  * @brief Processing clock divider
  */
#define IS_MDF_PROC_CLOCK_DIVIDER(value) ((1U <= (value)) && ((value) <= 128U))

/**
  * @brief Output clock pins
  */
#define IS_MDF_OUTPUT_CLOCK_PINS(pins) (((pins) == HAL_MDF_OUTPUT_CLOCK_NONE) \
                                        || ((pins) == HAL_MDF_OUTPUT_CLOCK_CCK0) \
                                        || ((pins) == HAL_MDF_OUTPUT_CLOCK_CCK1) \
                                        || ((pins) == HAL_MDF_OUTPUT_CLOCK_ALL))

/**
  * @brief Output clock divider
  */
#define IS_MDF_OUTPUT_CLOCK_DIVIDER(value) ((1U <= (value)) && ((value) <= 16U))

/**
  * @brief Output clock trigger source
  */
#define IS_MDF_OUTPUT_CLOCK_TRIGGER_SOURCE(source) (((source) == HAL_MDF_OUT_CLOCK_TRIG_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM1_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM1_TRGO2) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM8_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM8_TRGO2) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM3_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM4_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM16_OC1) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM6_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_TIM7_TRGO) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_SAD_DET) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_EXTI11) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_EXTI15) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_LPTIM1_OUT) \
                                                    || ((source) == HAL_MDF_OUT_CLOCK_TRIG_SAD_TRGO))

/**
  * @brief Output clock trigger edge
  */
#define IS_MDF_OUTPUT_CLOCK_TRIGGER_EDGE(edge) (((edge) == HAL_MDF_OUT_CLOCK_TRIG_RISING_EDGE) \
                                                || ((edge) == HAL_MDF_OUT_CLOCK_TRIG_FALLING_EDGE))

/**
  * @brief Interleaved filters
  */
#define IS_MDF_INTERLEAVED_FILTERS(value) ((value) <= (MDF1_BLOCKS_NUMBER - 1U))

/**
  * @brief Block index
  */
#define IS_MDF_BLOCK_INDEX(value) ((value) <= (MDF1_BLOCKS_NUMBER - 1U))

/**
  * @brief Serial interface mode
  */
#define IS_MDF_SITF_MODE(mode) (((mode) == HAL_MDF_SITF_MODE_LF_MASTER_SPI) \
                                || ((mode) == HAL_MDF_SITF_MODE_NORMAL_SPI) \
                                || ((mode) == HAL_MDF_SITF_MODE_MANCHESTER_FALLING) \
                                || ((mode) == HAL_MDF_SITF_MODE_MANCHESTER_RISING))

/**
  * @brief Serial interface clock source
  */
#define IS_MDF_SITF_CLOCK_SOURCE(source) (((source) == HAL_MDF_SITF_CLOCK_SOURCE_CCK0) \
                                          || ((source) == HAL_MDF_SITF_CLOCK_SOURCE_CCK1) \
                                          || ((source) == HAL_MDF_SITF_CLOCK_SOURCE_CKI))

/**
  * @brief Serial interface threshold
  */
#define IS_MDF_SITF_THRESHOLD(value) ((4U <= (value)) && ((value) <= 31U))

/**
  * @brief Bitstream matrix input edge
  */
#define IS_MDF_BSMX_INPUT_EDGE(edge) (((edge) == HAL_MDF_BSMX_INPUT_RISING) \
                                      || ((edge) == HAL_MDF_BSMX_INPUT_FALLING))

/**
  * @brief Short-circuit detector threshold
  */
#define IS_MDF_SCD_THRESHOLD(value) ((2U <= (value)) && ((value) <= 256U))

/**
  * @brief Break signals
  */
#define IS_MDF_BREAK_SIGNALS(value) ((value) <= 15U)

/**
  * @brief Digital filter data source
  */
#if defined(ADC2)
#define IS_MDF_DFLT_DATA_SOURCE(source) (((source) == HAL_MDF_DFLT_DATA_SOURCE_BSMX) \
                                         || ((source) == HAL_MDF_DFLT_DATA_SOURCE_ADCITF1) \
                                         || ((source) == HAL_MDF_DFLT_DATA_SOURCE_ADCITF2))
#else
#define IS_MDF_DFLT_DATA_SOURCE(source) (((source) == HAL_MDF_DFLT_DATA_SOURCE_BSMX) \
                                         || ((source) == HAL_MDF_DFLT_DATA_SOURCE_ADCITF1))
#endif /* ADC2 */

/**
  * @brief Digital filter CIC mode
  */
#define IS_MDF_DFLT_CIC_MODE(mode) (((mode) == HAL_MDF_DFLT_CIC_SPLIT_FASTSINC_MCIC) \
                                    || ((mode) == HAL_MDF_DFLT_CIC_SPLIT_SINC1_MCIC) \
                                    || ((mode) == HAL_MDF_DFLT_CIC_SPLIT_SINC2_MCIC) \
                                    || ((mode) == HAL_MDF_DFLT_CIC_SPLIT_SINC3_MCIC) \
                                    || ((mode) == HAL_MDF_DFLT_CIC_ONE_FILTER_SINC4) \
                                    || ((mode) == HAL_MDF_DFLT_CIC_ONE_FILTER_SINC5))

/**
  * @brief Digital filter decimation ratio
  */
#define IS_MDF_DFLT_DECIMATION_RATIO(value) ((2U <= (value)) && ((value) <= 512U))

/**
  * @brief Digital filter gain
  */
#define IS_MDF_DFLT_GAIN(value) ((-16 <= (value)) && ((value) <= 24))

/**
  * @brief Digital filter acquisition mode
  */
#define IS_MDF_DFLT_ACQUISITION_MODE(mode) (((mode) == HAL_MDF_DFLT_ACQ_MODE_ASYNC_CONT) \
                                            || ((mode) == HAL_MDF_DFLT_ACQ_MODE_ASYNC_SINGLE) \
                                            || ((mode) == HAL_MDF_DFLT_ACQ_MODE_SYNC_CONT) \
                                            || ((mode) == HAL_MDF_DFLT_ACQ_MODE_SYNC_SINGLE) \
                                            || ((mode) == HAL_MDF_DFLT_ACQ_MODE_WINDOW_CONT) \
                                            || ((mode) == HAL_MDF_DFLT_ACQ_MODE_SYNC_SNAPSHOT))

/**
  * @brief Digital filter trigger source
  */
#define IS_MDF_DFLT_TRIGGER_SOURCE(source) (((source) == HAL_MDF_DFLT_TRIG_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_OLD_EVENT) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM1_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM1_TRGO2) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM8_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM8_TRGO2) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM3_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM4_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM16_OC1) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM6_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_TIM7_TRGO) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_ADF_SAD_DET) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_EXTI11) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_EXTI15) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_LPTIM1_OUT) \
                                            || ((source) == HAL_MDF_DFLT_TRIG_ADF_TRGO))

/**
  * @brief Digital filter trigger edge
  */
#define IS_MDF_DFLT_TRIGGER_EDGE(edge) (((edge) == HAL_MDF_DFLT_TRIG_RISING_EDGE) \
                                        || ((edge) == HAL_MDF_DFLT_TRIG_FALLING_EDGE))

/**
  * @brief Digital filter samples delay
  */
#define IS_MDF_DFLT_SAMPLES_DELAY(value) ((value) <= 127U)

/**
  * @brief Digital filter offset compensation
  */
#define IS_MDF_DFLT_OFFSET_COMPENSATION(value) ((-33554432 <= (value)) && ((value) <= 33554431))

/**
  * @brief Digital filter integrator value
  */
#define IS_MDF_DFLT_INTEGRATOR_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

/**
  * @brief Digital filter integrator output division
  */
#define IS_MDF_DFLT_INTEGRATOR_OUTPUT_DIVISION(value) (((value) == HAL_MDF_DLFT_INT_OUTPUT_DIV_128) \
                                                       || ((value) == HAL_MDF_DLFT_INT_OUTPUT_DIV_32) \
                                                       || ((value) == HAL_MDF_DLFT_INT_OUTPUT_DIV_4) \
                                                       || ((value) == HAL_MDF_DLFT_INT_OUTPUT_NO_DIV))

/**
  * @brief Digital filter FIFO threshold
  */
#define IS_MDF_DFLT_FIFO_THRESHOLD(value) (((value) == HAL_MDF_DFLT_FIFO_THRESHOLD_NOT_EMPTY) \
                                           || ((value) == HAL_MDF_DFLT_FIFO_THRESHOLD_HALF_FULL))

/**
  * @brief Digital filter discard samples
  */
#define IS_MDF_DFLT_DISCARD_SAMPLES(value) ((value) <= 255U)

/**
  * @brief Digital filter snapshot format
  */
#define IS_MDF_DFLT_SNAPSHOT_FORMAT(value) (((value) == HAL_MDF_DFLT_SNAPSHOT_23BITS) \
                                            || ((value) == HAL_MDF_DFLT_SNAPSHOT_16BITS))

/**
  * @brief Digital filter reshape filter decimation ratio
  */
#define IS_MDF_DFLT_RSF_DECIMATION_RATIO(value) (((value) == HAL_MDF_DFLT_RSF_DR_4) \
                                                 || ((value) == HAL_MDF_DFLT_RSF_DR_1))

/**
  * @brief Digital filter high-pass filter cut-off frequency
  */
#define IS_MDF_DFLT_HPF_CUT_OFF_FREQUENCY(value) (((value) == HAL_MDF_DFLT_HPF_CUT_OFF_0_000625FPCM) \
                                                  || ((value) == HAL_MDF_DFLT_HPF_CUT_OFF_0_00125FPCM) \
                                                  || ((value) == HAL_MDF_DFLT_HPF_CUT_OFF_0_0025FPCM) \
                                                  || ((value) == HAL_MDF_DFLT_HPF_CUT_OFF_0_0095FPCM))

/**
  * @brief Digital filter optional interruptions
  */
#define IS_MDF_DFLT_OPTIONAL_IT(value) ((value) <= HAL_MDF_DFLT_OPT_IT_ALL)

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
/**
  * @brief Digital filter DMA data resolution
  */
#define IS_MDF_DFLT_DMA_DATA_RESOLUTION(value) (((value) == HAL_MDF_DMA_DATA_RESOLUTION_FULL) \
                                                || ((value) == HAL_MDF_DMA_DATA_RESOLUTION_MSB_ONLY))
#endif /* USE_HAL_MDF_DMA */

/**
  * @brief Out-of-limit detector CIC order
  */
#define IS_MDF_OLD_CIC_ORDER(value) (((value) == HAL_MDF_OLD_CIC_ORDER_FASTSINC) \
                                     || ((value) == HAL_MDF_OLD_CIC_ORDER_SINC1) \
                                     || ((value) == HAL_MDF_OLD_CIC_ORDER_SINC2) \
                                     || ((value) == HAL_MDF_OLD_CIC_ORDER_SINC3))

/**
  * @brief Out-of-limit detector decimation ratio
  */
#define IS_MDF_OLD_DECIMATION_RATIO(value) ((1U <= (value)) && ((value) <= 32U))

/**
  * @brief Out-of-limit detector threshold
  */
#define IS_MDF_OLD_THRESHOLD(value) ((-33554432 <= (value)) && ((value) <= 33554431))

/**
  * @brief Out-of-limit detector event configuration
  */
#define IS_MDF_OLD_EVENT_CONFIG(value) (((value) == HAL_MDF_OLD_EVENT_OUTSIDE_THRESHOLDS) \
                                        || ((value) == HAL_MDF_OLD_EVENT_IN_THRESHOLDS))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup MDF_Private_Functions MDF Private Functions
  * @{
  */

static uint32_t MDF_AdjustGainToRegisterValue(int32_t gain);
static int32_t  MDF_AdjustGainFromRegisterValue(uint32_t register_gain);

static void MDF_DFLT_EnableInterruptions(MDF_Block_TypeDef *p_mdf_block);
static void MDF_DFLT_EnableInterruptions_Opt(MDF_Block_TypeDef *p_mdf_block, uint32_t interruptions);

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
static hal_mdf_block_index_t MDF_DFLT_GetBlockIndexFromDmaHandle(const hal_mdf_handle_t *hmdf,
                                                                 const hal_dma_handle_t *hdma);
static void MDF_DFLT_DMA_Cplt(hal_dma_handle_t *hdma);
static void MDF_DFLT_DMA_HalfCplt(hal_dma_handle_t *hdma);
static void MDF_DFLT_DMA_Error(hal_dma_handle_t *hdma);
static void MDF_DFLT_DMA_Abort(hal_dma_handle_t *hdma);
#endif /* USE_HAL_MDF_DMA */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup MDF_Exported_Functions
  * @{
  */

/** @addtogroup MDF_Exported_Functions_Group1
  * @{
This section provides a set of functions allowing to initialize and deinitialize the MDF peripheral:
  - Call the function HAL_MDF_Init() to initialize the selected MDF handle.
  - Call the function HAL_MDF_DeInit() to deinitialize the MDF.
  */

/**
  * @brief  Initialize the MDF according to the associated handle.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  instance          HAL MDF instance.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to HAL MDF handle is NULL.
  */
hal_status_t HAL_MDF_Init(hal_mdf_handle_t *hmdf, hal_mdf_t instance)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_ALL_INSTANCE((MDF_TypeDef *)(uint32_t)instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hmdf == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->instance = instance;

#if defined(USE_HAL_MDF_CLK_ENABLE_MODEL) && (USE_HAL_MDF_CLK_ENABLE_MODEL >= HAL_CLK_ENABLE_PERIPH_ONLY)
  HAL_RCC_MDF1_EnableClock();
#endif /* USE_HAL_MDF_CLK_ENABLE_MODEL */

#if defined (USE_HAL_MDF_USER_DATA) && (USE_HAL_MDF_USER_DATA == 1)
  hmdf->p_user_data = (void *) NULL;
#endif /* USE_HAL_MDF_USER_DATA */

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  /* Initialize HAL MDF callbacks */
  hmdf->p_out_of_limit_detector_cb = HAL_MDF_OLD_Callback;
  hmdf->p_acquisition_cplt_cb      = HAL_MDF_DFLT_AcqCpltCallback;
  hmdf->p_acquisition_half_cplt_cb = HAL_MDF_DFLT_AcqHalfCpltCallback;
  hmdf->p_acquisition_stop_cb      = HAL_MDF_DFLT_AcqStopCpltCallback;
  hmdf->p_error_cb                 = HAL_MDF_ErrorCallback;
#endif  /* USE_HAL_MDF_REGISTER_CALLBACKS */

  for (uint8_t i = 0U; i < MDF1_BLOCKS_NUMBER; i++)
  {
#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
    hmdf->hdma[i] = NULL;
#endif /* USE_HAL_MDF_DMA */

#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[i] = HAL_MDF_ERROR_NONE;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Reset all sub-block states */
    hmdf->serial_interface_states[i]     = HAL_MDF_SITF_STATE_RESET;
    hmdf->short_circuit_detect_states[i] = HAL_MDF_SCD_STATE_RESET;
    hmdf->digital_filter_states[i]       = HAL_MDF_DFLT_STATE_RESET;
    hmdf->out_of_limit_detect_states[i]  = HAL_MDF_OLD_STATE_RESET;
  }

  hmdf->global_state = HAL_MDF_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-initialize the MDF.
  * @param hmdf Pointer to a hal_mdf_handle_t.
  */
void HAL_MDF_DeInit(hal_mdf_handle_t *hmdf)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_ALL_INSTANCE((MDF_TypeDef *)(uint32_t)hmdf->instance));

  for (uint8_t i = 0U; i < MDF1_BLOCKS_NUMBER; i++)
  {
    p_mdf_block = MDF_GET_BLOCK(hmdf, i);

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
    /* Abort potential DMA in progress */
    if ((hmdf->digital_filter_states[i] == HAL_MDF_DFLT_STATE_ACTIVE) && (hmdf->hdma[i] != NULL))
    {
      (void) HAL_DMA_Abort(hmdf->hdma[i]);
    }
#endif /* USE_HAL_MDF_DMA */

    /* Disable all sub-blocks */
    CLEAR_BIT(p_mdf_block->OLDCR, MDF_OLDCR_OLDEN);
    CLEAR_BIT(p_mdf_block->SCDCR, MDF_SCDCR_SCDEN);
    CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);
    CLEAR_BIT(p_mdf_block->SITFCR, MDF_SITFCR_SITFEN);

    /* Disable all block interruptions */
    CLEAR_REG(p_mdf_block->DFLTIER);

    /* Clear block pending flags */
    WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_OLDF | MDF_DFLTISR_SSOVRF
                                     | MDF_DFLTISR_SCDF | MDF_DFLTISR_SATF | MDF_DFLTISR_CKABF | MDF_DFLTISR_RFOVRF));

    /* Reset all sub-block states */
    hmdf->serial_interface_states[i]     = HAL_MDF_SITF_STATE_RESET;
    hmdf->short_circuit_detect_states[i] = HAL_MDF_SCD_STATE_RESET;
    hmdf->digital_filter_states[i]       = HAL_MDF_DFLT_STATE_RESET;
    hmdf->out_of_limit_detect_states[i]  = HAL_MDF_OLD_STATE_RESET;
  }

  /* Disable clock generator */
  CLEAR_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CKGDEN);

  hmdf->global_state = HAL_MDF_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group2
  * @{
This section provides a set of functions allowing to configure common clock generator and features:
  - Call the function HAL_MDF_SetConfig() to configure processing clock divider.
  - Call the function HAL_MDF_GetConfig() to get the current processing clock divider.
  - Call the function HAL_MDF_SetConfigOutputClock() to configure output clock pins and divider.
  - Call the function HAL_MDF_GetConfigOutputClock() to get the current output clock pins and divider.
  - Call the function HAL_MDF_SetConfigOutputClockTrigger() to configure output clock trigger and edge.
  - Call the function HAL_MDF_GetConfigOutputClockTrigger() to get the current output clock trigger and edge.
  - Call the function HAL_MDF_SetInterleavedFilters() to set the number of interleaved filters.
  - Call the function HAL_MDF_GetInterleavedFilters() to get the current number of interleaved filters.
  - Call the function HAL_MDF_SetDMA() to link DMA handle for a specified block to the MDF handle.
  - Call the function HAL_MDF_GetClockFreq() to get the current MDF kernel clock frequency.
  - Call the function HAL_MDF_SetUserData() to set user data in MDF handle.
  - Call the function HAL_MDF_GetUserData() to get user data from MDF handle.
  - Call the function HAL_MDF_GetLastErrorCodes() to get last error codes on a specified block.

This section provides also a set of functions allowing to control common features:
  - Call the function HAL_MDF_EnableOutputClock() to enable output clock pins.
  - Call the function HAL_MDF_DisableOutputClock() to disable output clock pins.
  - Call the function HAL_MDF_IsEnabledOutputClock() to check output clock pins status.
  - Call the function HAL_MDF_EnableOutputClockTrigger() to enable output clock trigger.
  - Call the function HAL_MDF_DisableOutputClockTrigger() to disable output clock trigger.
  - Call the function HAL_MDF_IsEnabledOutputClockTrigger() to check output clock trigger status.
  - Call the function HAL_MDF_EnableTriggerOutput() to enable trigger output.
  - Call the function HAL_MDF_IsEnabledTriggerOutput() to check trigger output status.

This section provides also a set of functions allowing to process common clock generator:
  - Call the function HAL_MDF_Start() to activate clock generator.
  - Call the function HAL_MDF_Stop() to deactivate clock generator.
  */

/* Configuration functions */
/**
  * @brief  Configure processing clock divider.
  * @param  hmdf               Pointer to a hal_mdf_handle_t.
  * @param  proc_clock_divider Processing clock divider.
  *                            This parameter must be a number between Min_Data = 1 and Max_Data = 128.
  * @retval HAL_OK             Operation completed successfully.
  */
hal_status_t HAL_MDF_SetConfig(hal_mdf_handle_t *hmdf, uint32_t proc_clock_divider)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_PROC_CLOCK_DIVIDER(proc_clock_divider));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_INIT | (uint32_t)HAL_MDF_STATE_IDLE);

  MODIFY_REG(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_PROCDIV_Msk, (proc_clock_divider - 1U) << MDF_CKGCR_PROCDIV_Pos);

  hmdf->global_state = HAL_MDF_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current processing clock divider.
  * @param hmdf                 Pointer to a hal_mdf_handle_t.
  * @param p_proc_clock_divider Pointer to processing clock divider.
  */
void HAL_MDF_GetConfig(const hal_mdf_handle_t *hmdf, uint32_t *p_proc_clock_divider)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_proc_clock_divider != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  *p_proc_clock_divider = ((READ_REG(MDF_GET_INSTANCE(hmdf)->CKGCR) & MDF_CKGCR_PROCDIV_Msk)
                           >> MDF_CKGCR_PROCDIV_Pos) + 1U;
}

/**
  * @brief  Configure output clock pins and divider.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  pins                 Output clock pins.
  * @param  output_clock_divider Output clock divider.
  *                              This parameter must be a number between Min_Data = 1 and Max_Data = 16.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_SetConfigOutputClock(const hal_mdf_handle_t *hmdf, hal_mdf_output_clock_pins_t pins,
                                          uint32_t output_clock_divider)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_OUTPUT_CLOCK_PINS(pins));
  ASSERT_DBG_PARAM(IS_MDF_OUTPUT_CLOCK_DIVIDER(output_clock_divider));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE);

  MODIFY_REG(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CCK0DIR_Msk | MDF_CKGCR_CCK1DIR_Msk | MDF_CKGCR_CCKDIV_Msk,
             (uint32_t)pins | ((output_clock_divider - 1U) << MDF_CKGCR_CCKDIV_Pos));

  return HAL_OK;
}

/**
  * @brief Get the current output clock pins and divider.
  * @param hmdf                   Pointer to a hal_mdf_handle_t.
  * @param p_pins                 Pointer to output clock pins.
  * @param p_output_clock_divider Pointer to output clock divider.
  */
void HAL_MDF_GetConfigOutputClock(const hal_mdf_handle_t *hmdf, hal_mdf_output_clock_pins_t *p_pins,
                                  uint32_t *p_output_clock_divider)
{
  uint32_t ckgcr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_pins != NULL);
  ASSERT_DBG_PARAM(p_output_clock_divider != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  ckgcr_reg = READ_REG(MDF_GET_INSTANCE(hmdf)->CKGCR);
  *p_pins = (hal_mdf_output_clock_pins_t)(uint32_t)(ckgcr_reg & (MDF_CKGCR_CCK0DIR_Msk | MDF_CKGCR_CCK1DIR_Msk));
  *p_output_clock_divider = ((ckgcr_reg & MDF_CKGCR_CCKDIV_Msk) >> MDF_CKGCR_CCKDIV_Pos) + 1U;
}

/**
  * @brief  Configure output clock trigger and edge.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @param  source Output clock trigger source.
  * @param  edge   Output clock trigger edge.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_SetConfigOutputClockTrigger(const hal_mdf_handle_t *hmdf,
                                                 hal_mdf_output_clock_trigger_source_t source,
                                                 hal_mdf_output_clock_trigger_edge_t edge)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_OUTPUT_CLOCK_TRIGGER_SOURCE(source));
  ASSERT_DBG_PARAM(IS_MDF_OUTPUT_CLOCK_TRIGGER_EDGE(edge));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE);

  MODIFY_REG(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_TRGSRC_Msk | MDF_CKGCR_TRGSENS_Msk,
             (uint32_t)source | (uint32_t)edge);

  return HAL_OK;
}

/**
  * @brief Get the current output clock trigger and edge.
  * @param hmdf     Pointer to a hal_mdf_handle_t.
  * @param p_source Pointer to output clock trigger source.
  * @param p_edge   Pointer to output clock trigger edge.
  */
void HAL_MDF_GetConfigOutputClockTrigger(const hal_mdf_handle_t *hmdf,
                                         hal_mdf_output_clock_trigger_source_t *p_source,
                                         hal_mdf_output_clock_trigger_edge_t *p_edge)
{
  uint32_t ckgcr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_source != NULL);
  ASSERT_DBG_PARAM(p_edge != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  ckgcr_reg = READ_REG(MDF_GET_INSTANCE(hmdf)->CKGCR);
  *p_source = (hal_mdf_output_clock_trigger_source_t)(uint32_t)(ckgcr_reg & MDF_CKGCR_TRGSRC_Msk);
  *p_edge = (hal_mdf_output_clock_trigger_edge_t)(uint32_t)(ckgcr_reg & MDF_CKGCR_TRGSENS_Msk);
}

/**
  * @brief  Set the number of interleaved filters.
  * @param  hmdf                Pointer to a hal_mdf_handle_t.
  * @param  interleaved_filters Number of interleaved filters.
  *                             This parameter must be a number between Min_Data = 0 and Max_Data = 5.
  * @retval HAL_OK              Operation completed successfully.
  */
hal_status_t HAL_MDF_SetInterleavedFilters(const hal_mdf_handle_t *hmdf, uint32_t interleaved_filters)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_INTERLEAVED_FILTERS(interleaved_filters));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[0U],
                   (uint32_t)HAL_MDF_DFLT_STATE_RESET | (uint32_t)HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_INSTANCE(hmdf)->GCR, MDF_GCR_ILVNB_Msk, interleaved_filters << MDF_GCR_ILVNB_Pos);

  return HAL_OK;
}

/**
  * @brief  Get the current number of interleaved filters.
  * @param  hmdf     Pointer to a hal_mdf_handle_t.
  * @retval uint32_t Number of interleaved filters.
  */
uint32_t HAL_MDF_GetInterleavedFilters(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  return ((READ_REG(MDF_GET_INSTANCE(hmdf)->GCR) & MDF_GCR_ILVNB_Msk) >> MDF_GCR_ILVNB_Pos);
}

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
/**
  * @brief  Link DMA handle for a specified block to the MDF handle.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  block_index       Block index.
  * @param  hdma              Pointer to DMA handle.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to DMA handle is NULL.
  */
hal_status_t HAL_MDF_SetDMA(hal_mdf_handle_t *hmdf,
                            hal_mdf_block_index_t block_index,
                            hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)block_index));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[block_index],
                   (uint32_t)HAL_MDF_DFLT_STATE_RESET | (uint32_t)HAL_MDF_DFLT_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->hdma[block_index] = hdma;
  hdma->p_parent = hmdf;

  return HAL_OK;
}
#endif /* USE_HAL_MDF_DMA */

/**
  * @brief  Get the current MDF kernel clock frequency.
  * @param  hmdf     Pointer to a hal_mdf_handle_t.
  * @retval uint32_t MDF kernel clock frequency in Hz.
  * @retval 0        MDF source clock not configured or not ready.
  */
uint32_t HAL_MDF_GetClockFreq(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_INIT | (uint32_t)HAL_MDF_STATE_IDLE
                   | (uint32_t)HAL_MDF_STATE_ACTIVE);

#if (!defined(USE_ASSERT_DBG_STATE) && !defined(USE_ASSERT_DBG_PARAM))
  STM32_UNUSED(hmdf);
#endif /* (!defined(USE_ASSERT_DBG_STATE) && !defined(USE_ASSERT_DBG_PARAM)) */

  return HAL_RCC_MDF1_GetKernelClkFreq();
}

#if defined (USE_HAL_MDF_USER_DATA) && (USE_HAL_MDF_USER_DATA == 1)
/**
  * @brief Set user data in MDF handle.
  * @param hmdf        Pointer to a hal_mdf_handle_t.
  * @param p_user_data Pointer to user data structure.
  */
void HAL_MDF_SetUserData(hal_mdf_handle_t *hmdf, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  hmdf->p_user_data = p_user_data;
}

/**
  * @brief  Get user data from MDF handle.
  * @param  hmdf Pointer to a hal_mdf_handle_t.
  * @retval void Pointer to user data structure.
  */
const void *HAL_MDF_GetUserData(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  return hmdf->p_user_data;
}
#endif /* USE_HAL_MDF_USER_DATA */

#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last error codes on a specified block.
  * @param  hmdf        Pointer to a hal_mdf_handle_t.
  * @param  block_index Block index.
  * @retval uint32_t    Last error codes on the specified block.
  *                     This return value can be a combination of the following values:
  *                       @arg @ref HAL_MDF_ERROR_NONE
  *                       @arg @ref HAL_MDF_ERROR_DFLT_ACQ_OVERFLOW
  *                       @arg @ref HAL_MDF_ERROR_DFLT_RSF_OVERRUN
  *                       @arg @ref HAL_MDF_ERROR_SITF_CLOCK_ABSENCE
  *                       @arg @ref HAL_MDF_ERROR_SHORT_CIRCUIT
  *                       @arg @ref HAL_MDF_ERROR_DFLT_SATURATION
  *                       @arg @ref HAL_MDF_ERROR_DMA
  */
uint32_t HAL_MDF_GetLastErrorCodes(const hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t block_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)block_index));

  return hmdf->last_error_codes[block_index];
}
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

/* Control functions */
/**
  * @brief  Enable output clock pins.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @param  pins   Output clock pins.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_EnableOutputClock(const hal_mdf_handle_t *hmdf, hal_mdf_output_clock_pins_t pins)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_OUTPUT_CLOCK_PINS(pins));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  SET_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, (uint32_t)pins >> 4U);

  return HAL_OK;
}

/**
  * @brief  Disable output clock pins.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @param  pins   Output clock pins.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_DisableOutputClock(const hal_mdf_handle_t *hmdf, hal_mdf_output_clock_pins_t pins)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_OUTPUT_CLOCK_PINS(pins));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  CLEAR_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, (uint32_t)pins >> 4U);

  return HAL_OK;
}

/**
  * @brief  Check output clock pins status.
  * @param  hmdf                          Pointer to a hal_mdf_handle_t.
  * @retval hal_mdf_output_clock_status_t Output clock pins status.
  */
hal_mdf_output_clock_status_t HAL_MDF_IsEnabledOutputClock(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  return (hal_mdf_output_clock_status_t)(uint32_t)((READ_REG(MDF_GET_INSTANCE(hmdf)->CKGCR)
                                                    & (MDF_CKGCR_CCK0EN_Msk | MDF_CKGCR_CCK1EN_Msk)) >> 1U);
}

/**
  * @brief  Enable output clock trigger.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_EnableOutputClockTrigger(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE);

  SET_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CKGMOD);

  return HAL_OK;
}

/**
  * @brief  Disable output clock trigger.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_DisableOutputClockTrigger(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE);

  CLEAR_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CKGMOD);

  return HAL_OK;
}

/**
  * @brief  Check output clock trigger status.
  * @param  hmdf                                  Pointer to a hal_mdf_handle_t.
  * @retval hal_mdf_output_clock_trigger_status_t Output clock trigger status.
  */
hal_mdf_output_clock_trigger_status_t HAL_MDF_IsEnabledOutputClockTrigger(const hal_mdf_handle_t *hmdf)
{
  hal_mdf_output_clock_trigger_status_t status;

  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  status = (IS_BIT_SET(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CKGMOD)) ? HAL_MDF_OUT_CLOCK_TRIG_ENABLED
           : HAL_MDF_OUT_CLOCK_TRIG_DISABLED;

  return status;
}

/**
  * @brief  Enable trigger output.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_EnableTriggerOutput(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  SET_BIT(MDF_GET_INSTANCE(hmdf)->GCR, MDF_GCR_TRGO);

  return HAL_OK;
}

/**
  * @brief  Check trigger output status.
  * @param  hmdf                            Pointer to a hal_mdf_handle_t.
  * @retval hal_mdf_trigger_output_status_t Trigger output status.
  */
hal_mdf_trigger_output_status_t HAL_MDF_IsEnabledTriggerOutput(const hal_mdf_handle_t *hmdf)
{
  hal_mdf_trigger_output_status_t status;

  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE | (uint32_t)HAL_MDF_STATE_ACTIVE);

  status = (IS_BIT_SET(MDF_GET_INSTANCE(hmdf)->GCR, MDF_GCR_TRGO)) ? HAL_MDF_TRIGGER_OUTPUT_ENABLED
           : HAL_MDF_TRIGGER_OUTPUT_DISABLED;

  return status;
}

/* Process functions */
/**
  * @brief  Activate clock generator.
  * @param  hmdf     Pointer to a hal_mdf_handle_t.
  * @retval HAL_OK   Operation completed successfully.
  * @retval HAL_BUSY The global state is not HAL_MDF_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_Start(hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, global_state, HAL_MDF_STATE_IDLE, HAL_MDF_STATE_ACTIVE);

  SET_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CKGDEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate clock generator.
  * @param  hmdf   Pointer to a hal_mdf_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_MDF_Stop(hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_ACTIVE);

  for (uint8_t i = 0U; i < MDF1_BLOCKS_NUMBER; i++)
  {
    ASSERT_DBG_STATE(hmdf->serial_interface_states[i], (uint32_t)HAL_MDF_SITF_STATE_RESET
                     | (uint32_t)HAL_MDF_SITF_STATE_IDLE);
    ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[i], (uint32_t)HAL_MDF_SCD_STATE_RESET
                     | (uint32_t)HAL_MDF_SCD_STATE_IDLE);
    ASSERT_DBG_STATE(hmdf->digital_filter_states[i], (uint32_t)HAL_MDF_DFLT_STATE_RESET
                     | (uint32_t)HAL_MDF_DFLT_STATE_IDLE);
    ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[i], (uint32_t)HAL_MDF_OLD_STATE_RESET
                     | (uint32_t)HAL_MDF_OLD_STATE_IDLE);
  }

  CLEAR_BIT(MDF_GET_INSTANCE(hmdf)->CKGCR, MDF_CKGCR_CKGDEN);

  hmdf->global_state = HAL_MDF_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group3
  * @{
This section provides a set of functions allowing to configure and process serial interface:
  - Call the function HAL_MDF_SITF_SetConfig() to configure a specified serial interface.
  - Call the function HAL_MDF_SITF_GetConfig() to get the current configuration of a specified serial interface.
  - Call the function HAL_MDF_SITF_Start() to activate a specified serial interface.
  - Call the function HAL_MDF_SITF_Stop() to deactivate a specified serial interface.

This section provides also a set of functions for clock absence detection feature:
  - Call the function HAL_MDF_SITF_IsClockAbsenceDetected() to check clock absence detection status on a specified
    serial interface.
  - Call the function HAL_MDF_SITF_StartClockAbsenceDetect_IT() to start clock absence detection in interrupt mode
    on a specified serial interface.
  - Call the function HAL_MDF_SITF_StopClockAbsenceDetect_IT() to stop clock absence detection in interrupt mode
    on a specified serial interface.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified serial interface.
  * @param  hmdf                   Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @param  p_config               Pointer to serial interface configuration structure.
  * @retval HAL_OK                 Operation completed successfully.
  * @retval HAL_INVALID_PARAM      Pointer to serial interface configuration structure is NULL.
  */
hal_status_t HAL_MDF_SITF_SetConfig(hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t serial_interface_index,
                                    const hal_mdf_serial_interface_config_t *p_config)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_MDF_SITF_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_MDF_SITF_CLOCK_SOURCE(p_config->clock_source));
  ASSERT_DBG_PARAM(IS_MDF_SITF_THRESHOLD(p_config->threshold));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], (uint32_t)HAL_MDF_SITF_STATE_RESET
                   | (uint32_t)HAL_MDF_SITF_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, serial_interface_index)->SITFCR,
             MDF_SITFCR_SCKSRC_Msk | MDF_SITFCR_SITFMOD_Msk | MDF_SITFCR_STH_Msk,
             (uint32_t)p_config->clock_source | (uint32_t)p_config->mode
             | (p_config->threshold << MDF_SITFCR_STH_Pos));

  hmdf->serial_interface_states[serial_interface_index] = HAL_MDF_SITF_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current configuration of a specified serial interface.
  * @param hmdf                   Pointer to a hal_mdf_handle_t.
  * @param serial_interface_index Serial interface index.
  * @param p_config               Pointer to serial interface configuration structure.
  */
void HAL_MDF_SITF_GetConfig(const hal_mdf_handle_t *hmdf,
                            hal_mdf_block_index_t serial_interface_index,
                            hal_mdf_serial_interface_config_t *p_config)
{
  uint32_t sitfcr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hmdf->global_state, (uint32_t)HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], (uint32_t)HAL_MDF_SITF_STATE_IDLE
                   | (uint32_t)HAL_MDF_SITF_STATE_ACTIVE);

  sitfcr_reg = READ_REG(MDF_GET_BLOCK(hmdf, serial_interface_index)->SITFCR);
  p_config->mode = (hal_mdf_serial_interface_mode_t)(uint32_t)(sitfcr_reg & MDF_SITFCR_SITFMOD_Msk);
  p_config->clock_source = (hal_mdf_serial_interface_clock_source_t)(uint32_t)(sitfcr_reg & MDF_SITFCR_SCKSRC_Msk);
  p_config->threshold = ((sitfcr_reg & MDF_SITFCR_STH_Msk) >> MDF_SITFCR_STH_Pos);
}

/* Process functions */
/**
  * @brief  Activate a specified serial interface.
  * @param  hmdf                   Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  * @retval HAL_BUSY               The serial interface state is not HAL_MDF_SITF_STATE_IDLE
  *                                (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_SITF_Start(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], HAL_MDF_SITF_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, serial_interface_states[serial_interface_index], HAL_MDF_SITF_STATE_IDLE,
                         HAL_MDF_SITF_STATE_ACTIVE);

  SET_BIT(MDF_GET_BLOCK(hmdf, serial_interface_index)->SITFCR, MDF_SITFCR_SITFEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified serial interface.
  * @param  hmdf                   Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_MDF_SITF_Stop(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], HAL_MDF_SITF_STATE_ACTIVE);

  CLEAR_BIT(MDF_GET_BLOCK(hmdf, serial_interface_index)->SITFCR, MDF_SITFCR_SITFEN);

  hmdf->serial_interface_states[serial_interface_index] = HAL_MDF_SITF_STATE_IDLE;

  return HAL_OK;
}

/* Clock absence detection functions */
/**
  * @brief  Check clock absence detection status on a specified serial interface.
  * @param  hmdf                       Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index     Serial interface index.
  * @retval hal_mdf_sitf_ckab_status_t Clock absence detection status.
  */
hal_mdf_sitf_ckab_status_t HAL_MDF_SITF_IsClockAbsenceDetected(const hal_mdf_handle_t *hmdf,
                                                               hal_mdf_block_index_t serial_interface_index)
{
  hal_mdf_sitf_ckab_status_t status;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], HAL_MDF_SITF_STATE_ACTIVE);

  status = (IS_BIT_SET(MDF_GET_BLOCK(hmdf, serial_interface_index)->DFLTISR, MDF_DFLTISR_CKABF))
           ? HAL_MDF_SITF_CKAB_DETECTED : HAL_MDF_SITF_CKAB_NOT_DETECTED;

  return status;
}

/**
  * @brief  Start clock absence detection in interrupt mode on a specified serial interface.
  * @param  hmdf                   Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_MDF_SITF_StartClockAbsenceDetect_IT(const hal_mdf_handle_t *hmdf,
                                                     hal_mdf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], HAL_MDF_SITF_STATE_ACTIVE);

  SET_BIT(MDF_GET_BLOCK(hmdf, serial_interface_index)->DFLTIER, MDF_DFLTIER_CKABIE);

  return HAL_OK;
}

/**
  * @brief  Stop clock absence detection in interrupt mode on a specified serial interface.
  * @param  hmdf                   Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index Serial interface index.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_MDF_SITF_StopClockAbsenceDetect_IT(const hal_mdf_handle_t *hmdf,
                                                    hal_mdf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->serial_interface_states[serial_interface_index], HAL_MDF_SITF_STATE_ACTIVE);

  CLEAR_BIT(MDF_GET_BLOCK(hmdf, serial_interface_index)->DFLTIER, MDF_DFLTIER_CKABIE);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group4
  * @{
This section provides a set of functions allowing to configure bitstream matrix:
  - Call the function HAL_MDF_BSMX_SetConfig() to configure a specified bitstream matrix.
  - Call the function HAL_MDF_BSMX_GetConfig() to get the current configuration of a specified bitstream matrix.
  */

/* Configuration functions */
/**
  * @brief  Connect a specified bitstream matrix to a specified serial interface and configure input edge.
  * @param  hmdf                   Pointer to a hal_mdf_handle_t.
  * @param  bitstream_matrix_index Bitstream matrix index.
  * @param  serial_interface_index Serial interface index.
  * @param  edge                   Input edge.
  * @retval HAL_OK                 Operation completed successfully.
  */
hal_status_t HAL_MDF_BSMX_SetConfig(const hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t bitstream_matrix_index,
                                    hal_mdf_block_index_t serial_interface_index,
                                    hal_mdf_bitstream_input_edge_t edge)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)bitstream_matrix_index));
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));
  ASSERT_DBG_PARAM(IS_MDF_BSMX_INPUT_EDGE(edge));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[bitstream_matrix_index], (uint32_t)HAL_MDF_SCD_STATE_RESET
                   | (uint32_t)HAL_MDF_SCD_STATE_IDLE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[bitstream_matrix_index], (uint32_t)HAL_MDF_DFLT_STATE_RESET
                   | (uint32_t)HAL_MDF_DFLT_STATE_IDLE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[bitstream_matrix_index], (uint32_t)HAL_MDF_OLD_STATE_RESET
                   | (uint32_t)HAL_MDF_OLD_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, bitstream_matrix_index)->BSMXCR, MDF_BSMXCR_BSSEL_Msk,
             ((uint32_t)serial_interface_index << 1U) | (uint32_t)edge);

  return HAL_OK;
}

/**
  * @brief Get the current serial interface connected to a specified bitstream matrix and current input edge.
  * @param hmdf                     Pointer to a hal_mdf_handle_t.
  * @param bitstream_matrix_index   Bitstream matrix index.
  * @param p_serial_interface_index Pointer to serial interface index.
  * @param p_edge                   Pointer to input edge.
  */
void HAL_MDF_BSMX_GetConfig(const hal_mdf_handle_t *hmdf,
                            hal_mdf_block_index_t bitstream_matrix_index,
                            hal_mdf_block_index_t *p_serial_interface_index,
                            hal_mdf_bitstream_input_edge_t *p_edge)
{
  uint32_t bsmxcr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)bitstream_matrix_index));
  ASSERT_DBG_PARAM(p_serial_interface_index != NULL);
  ASSERT_DBG_PARAM(p_edge != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);

  bsmxcr_reg = READ_REG(MDF_GET_BLOCK(hmdf, bitstream_matrix_index)->BSMXCR);
  *p_serial_interface_index = (hal_mdf_block_index_t)(uint32_t)((bsmxcr_reg & MDF_BSMXCR_BSSEL_Msk) >> 1U);
  *p_edge = (hal_mdf_bitstream_input_edge_t)(uint32_t)(bsmxcr_reg & 1U);
}

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group5
  * @{
This section provides a set of functions allowing to configure, process and control short-circuit detector:
  - Call the function HAL_MDF_SCD_SetConfig() to configure a specified short-circuit detector.
  - Call the function HAL_MDF_SCD_GetConfig() to get the current configuration of a specified short-circuit detector.
  - Call the function HAL_MDF_SCD_Start() to activate a specified short-circuit detector in polling mode.
  - Call the function HAL_MDF_SCD_Stop() to deactivate a specified short-circuit detector in polling mode.
  - Call the function HAL_MDF_SCD_Start_IT() to activate a specified short-circuit detector in interrupt mode.
  - Call the function HAL_MDF_SCD_Stop_IT() to deactivate a specified short-circuit detector in interrupt mode.
  - Call the function HAL_MDF_SCD_IsDetected() to check detection status on a specified short-circuit detector.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified short-circuit detector.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @param  threshold                    Threshold.
  *                                      This parameter must be a number between Min_Data = 2 and Max_Data = 256.
  * @param  break_signals                Break signals.
  *                                      This parameter must be a combination of the following values:
  *                                        @arg @ref HAL_MDF_SIGNAL_NO_BREAK
  *                                        @arg @ref HAL_MDF_SIGNAL_TIM1_BREAK
  *                                        @arg @ref HAL_MDF_SIGNAL_TIM1_BREAK2
  *                                        @arg @ref HAL_MDF_SIGNAL_TIM8_BREAK
  *                                        @arg @ref HAL_MDF_SIGNAL_TIM8_BREAK2
  * @retval HAL_OK                       Operation completed successfully.
  */
hal_status_t HAL_MDF_SCD_SetConfig(hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t short_circuit_detector_index,
                                   uint32_t threshold,
                                   uint32_t break_signals)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));
  ASSERT_DBG_PARAM(IS_MDF_SCD_THRESHOLD(threshold));
  ASSERT_DBG_PARAM(IS_MDF_BREAK_SIGNALS(break_signals));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], (uint32_t)HAL_MDF_SCD_STATE_RESET
                   | (uint32_t)HAL_MDF_SCD_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, short_circuit_detector_index)->SCDCR, MDF_SCDCR_BKSCD_Msk | MDF_SCDCR_SCDT_Msk,
             (break_signals << MDF_SCDCR_BKSCD_Pos) | ((threshold - 1U) << MDF_SCDCR_SCDT_Pos));

  hmdf->short_circuit_detect_states[short_circuit_detector_index] = HAL_MDF_SCD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current configuration of a specified short-circuit detector.
  * @param hmdf                           Pointer to a hal_mdf_handle_t.
  * @param short_circuit_detector_index   Short-circuit detector index.
  * @param p_threshold                    Pointer to threshold.
  * @param p_break_signals                Pointer to break signals.
  */
void HAL_MDF_SCD_GetConfig(const hal_mdf_handle_t *hmdf,
                           hal_mdf_block_index_t short_circuit_detector_index,
                           uint32_t *p_threshold,
                           uint32_t *p_break_signals)
{
  uint32_t scdcr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));
  ASSERT_DBG_PARAM(p_threshold != NULL);
  ASSERT_DBG_PARAM(p_break_signals != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], (uint32_t)HAL_MDF_SCD_STATE_IDLE
                   | (uint32_t)HAL_MDF_SCD_STATE_ACTIVE);

  scdcr_reg = READ_REG(MDF_GET_BLOCK(hmdf, short_circuit_detector_index)->SCDCR);
  *p_threshold = ((scdcr_reg & MDF_SCDCR_SCDT_Msk) >> MDF_SCDCR_SCDT_Pos) + 1U;
  *p_break_signals = ((scdcr_reg & MDF_SCDCR_BKSCD_Msk) >> MDF_SCDCR_BKSCD_Pos);
}

/* Process functions */
/**
  * @brief  Activate a specified short-circuit detector in polling mode.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @retval HAL_OK                       Operation completed successfully.
  * @retval HAL_BUSY                     The short-circuit detector state is not HAL_MDF_SCD_STATE_IDLE
  *                                      (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_SCD_Start(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_IDLE,
                         HAL_MDF_SCD_STATE_ACTIVE);

  SET_BIT(MDF_GET_BLOCK(hmdf, short_circuit_detector_index)->SCDCR, MDF_SCDCR_SCDEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified short-circuit detector in polling mode.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @retval HAL_OK                       Operation completed successfully.
  */
hal_status_t HAL_MDF_SCD_Stop(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_ACTIVE);

  /* Deactivate short-circuit detector and clear potential pending flag */
  p_mdf_block = MDF_GET_BLOCK(hmdf, short_circuit_detector_index);
  CLEAR_BIT(p_mdf_block->SCDCR, MDF_SCDCR_SCDEN);
  SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SCDF);

  hmdf->short_circuit_detect_states[short_circuit_detector_index] = HAL_MDF_SCD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Activate a specified short-circuit detector in interrupt mode.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @retval HAL_OK                       Operation completed successfully.
  * @retval HAL_BUSY                     The short-circuit detector state is not HAL_MDF_SCD_STATE_IDLE
  *                                      (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_SCD_Start_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_IDLE,
                         HAL_MDF_SCD_STATE_ACTIVE);

  /* Enable short-circuit detector interrupt */
  p_mdf_block = MDF_GET_BLOCK(hmdf, short_circuit_detector_index);
  SET_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_SCDIE);

  /* Activate short-circuit detector */
  SET_BIT(p_mdf_block->SCDCR, MDF_SCDCR_SCDEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified short-circuit detector in interrupt mode.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @retval HAL_OK                       Operation completed successfully.
  */
hal_status_t HAL_MDF_SCD_Stop_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t short_circuit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_ACTIVE);

  /* Deactivate short-circuit detector, disable interrupt and clear potential pending flag */
  p_mdf_block = MDF_GET_BLOCK(hmdf, short_circuit_detector_index);
  CLEAR_BIT(p_mdf_block->SCDCR, MDF_SCDCR_SCDEN);
  CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_SCDIE);
  SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SCDF);

  hmdf->short_circuit_detect_states[short_circuit_detector_index] = HAL_MDF_SCD_STATE_IDLE;

  return HAL_OK;
}

/* Control functions */
/**
  * @brief  Check detection status on a specified short-circuit detector.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @retval hal_mdf_scd_status_t         Short-circuit detection status.
  */
hal_mdf_scd_status_t HAL_MDF_SCD_IsDetected(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t short_circuit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;
  hal_mdf_scd_status_t status;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->short_circuit_detect_states[short_circuit_detector_index], HAL_MDF_SCD_STATE_ACTIVE);

  p_mdf_block = MDF_GET_BLOCK(hmdf, short_circuit_detector_index);
  if (IS_BIT_SET(p_mdf_block->DFLTISR, MDF_DFLTISR_SCDF))
  {
    status = HAL_MDF_SHORT_CIRCUIT_DETECTED;

    /* Clear short-circuit detection flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SCDF);
  }
  else
  {
    status = HAL_MDF_SHORT_CIRCUIT_NOT_DETECTED;
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group6
  * @{
This section provides a set of functions allowing to configure digital filter:
  - Call the function HAL_MDF_DFLT_SetConfig() to configure a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetConfig() to get current configuration of a specified digital filter.
  - Call the function HAL_MDF_DFLT_SetSamplesDelay() to set samples delay on a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetSamplesDelay() to get current samples delay on a specified digital filter.
  - Call the function HAL_MDF_DFLT_SetOffsetCompensation() to set offset compensation on a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetOffsetCompensation() to get current offset compensation on a specified
    digital filter.
  - Call the function HAL_MDF_DFLT_SetGain() to set gain on a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetGain() to get current gain on a specified digital filter.
  - Call the function HAL_MDF_DFLT_SetIntegrator() to set integrator value and output division on a specified
    digital filter.
  - Call the function HAL_MDF_DFLT_GetIntegrator() to get current integrator value and output division on a specified
    digital filter.
  - Call the function HAL_MDF_DFLT_SetFifoThreshold() to set FIFO threshold on a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetFifoThreshold() to get current FIFO threshold on a specified digital filter.
  - Call the function HAL_MDF_DFLT_SetDiscardSamples() to set discard samples on a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetDiscardSamples() to get current discard samples on a specified digital filter.
  - Call the function HAL_MDF_DFLT_SetSnapshotFormat() to set snapshot format on a specified digital filter.
  - Call the function HAL_MDF_DFLT_GetSnapshotFormat() to get current snapshot format on a specified digital filter.

This section provides also a set of functions allowing to control digital filter:
  - Call the function HAL_MDF_DFLT_EnableReshapeFilter() to enable reshape filter on a specified digital filter.
  - Call the function HAL_MDF_DFLT_DisableReshapeFilter() to disable reshape filter on a specified digital filter.
  - Call the function HAL_MDF_DFLT_IsEnabledReshapeFilter() to check reshape filter status on a specified
    digital filter.
  - Call the function HAL_MDF_DFLT_GetReshapeFilterDecimationRatio() to get current reshape filter decimation ratio
    on a specified digital filter.
  - Call the function HAL_MDF_DFLT_EnableHighPassFilter() to enable high-pass filter on a specified digital filter.
  - Call the function HAL_MDF_DFLT_DisableHighPassFilter() to disable high-pass filter on a specified digital filter.
  - Call the function HAL_MDF_DFLT_IsEnabledHighPassFilter() to check high-pass filter status on a specified
    digital filter.
  - Call the function HAL_MDF_DFLT_GetHighPassFilterCutOffFrequency() to get current high-pass filter cut-off frequency
    on a specified digital filter.

This section provides also a set of functions allowing to process digital filter:
  - Call the function HAL_MDF_DFLT_StartAcq() to start acquisition on a specified digital filter in polling mode.
  - Call the function HAL_MDF_DFLT_StopAcq() to stop acquisition on a specified digital filter in polling mode.
  - Call the function HAL_MDF_DFLT_PollForAcq() to wait available acquisition on a specified digital filter
    in polling mode.
  - Call the function HAL_MDF_DFLT_GetAcqValue() to get acquisition value on a specified digital filter.
  - Call the function HAL_MDF_DFLT_PollForSnapshotAcq() to wait available snapshot acquisition on a specified
    digital filter in polling mode.
  - Call the function HAL_MDF_DFLT_GetSnapshotAcqValue() to get snapshot acquisition value on a specified
    digital filter.
  - Call the function HAL_MDF_DFLT_StartAcq_IT() to start acquisition on a specified digital filter in interrupt mode.
  - Call the function HAL_MDF_DFLT_StopAcq_IT() to stop acquisition on a specified digital filter in interrupt mode.
  - Call the function HAL_MDF_DFLT_StartAcq_IT_Opt() to start acquisition on a specified digital filter
    in interrupt mode with optional interruptions.
  - Call the function HAL_MDF_DFLT_StartAcq_DMA() to start acquisition on a specified digital filter in DMA mode.
  - Call the function HAL_MDF_DFLT_StopAcq_DMA() to stop acquisition on a specified digital filter in DMA mode.
  - Call the function HAL_MDF_DFLT_StartAcq_DMA_Opt() to start acquisition on a specified digital filter
    in DMA mode with optional interruptions.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  p_config             Pointer to digital filter configuration structure.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_INVALID_PARAM    Pointer to digital filter configuration structure is NULL.
  */
hal_status_t HAL_MDF_DFLT_SetConfig(hal_mdf_handle_t *hmdf,
                                    hal_mdf_block_index_t digital_filter_index,
                                    const hal_mdf_digital_filter_config_t *p_config)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_MDF_DFLT_DATA_SOURCE(p_config->data_source));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_CIC_MODE(p_config->cic_mode));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_DECIMATION_RATIO(p_config->decimation_ratio));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_GAIN(p_config->gain));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_ACQUISITION_MODE(p_config->acquisition_mode));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_TRIGGER_SOURCE(p_config->trigger.source));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_TRIGGER_EDGE(p_config->trigger.edge));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_RESET
                   | (uint32_t)HAL_MDF_DFLT_STATE_IDLE);

  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  MODIFY_REG(p_mdf_block->DFLTCICR, MDF_DFLTCICR_DATSRC_Msk | MDF_DFLTCICR_CICMOD_Msk | MDF_DFLTCICR_MCICD_Msk
             | MDF_DFLTCICR_SCALE_Msk, (uint32_t)p_config->data_source | (uint32_t)p_config->cic_mode
             | ((p_config->decimation_ratio - 1U) << MDF_DFLTCICR_MCICD_Pos)
             | (MDF_AdjustGainToRegisterValue(p_config->gain) << MDF_DFLTCICR_SCALE_Pos));
  MODIFY_REG(p_mdf_block->DFLTCR, MDF_DFLTCR_ACQMOD_Msk | MDF_DFLTCR_TRGSENS_Msk | MDF_DFLTCR_TRGSRC_Msk,
             (uint32_t)p_config->acquisition_mode | (uint32_t)p_config->trigger.edge
             | (uint32_t)p_config->trigger.source);

  hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get current configuration of a specified digital filter.
  * @param hmdf                 Pointer to a hal_mdf_handle_t.
  * @param digital_filter_index Digital filter index.
  * @param p_config             Pointer to digital filter configuration structure.
  */
void HAL_MDF_DFLT_GetConfig(const hal_mdf_handle_t *hmdf,
                            hal_mdf_block_index_t digital_filter_index,
                            hal_mdf_digital_filter_config_t *p_config)
{
  const MDF_Block_TypeDef *p_mdf_block;
  uint32_t reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  reg = READ_REG(p_mdf_block->DFLTCICR);
  p_config->data_source = (hal_mdf_dflt_data_source_t)(uint32_t)(reg & MDF_DFLTCICR_DATSRC_Msk);
  p_config->cic_mode = (hal_mdf_dflt_cic_mode_t)(uint32_t)(reg & MDF_DFLTCICR_CICMOD_Msk);
  p_config->decimation_ratio = ((reg & MDF_DFLTCICR_MCICD_Msk) >> MDF_DFLTCICR_MCICD_Pos) + 1U;
  p_config->gain = MDF_AdjustGainFromRegisterValue((reg & MDF_DFLTCICR_SCALE_Msk) >> MDF_DFLTCICR_SCALE_Pos);
  reg = READ_REG(p_mdf_block->DFLTCR);
  p_config->acquisition_mode = (hal_mdf_dflt_acquisition_mode_t)(uint32_t)(reg & MDF_DFLTCR_ACQMOD_Msk);
  p_config->trigger.source = (hal_mdf_dflt_trigger_source_t)(uint32_t)(reg & MDF_DFLTCR_TRGSRC_Msk);
  p_config->trigger.edge = (hal_mdf_dflt_trigger_edge_t)(uint32_t)(reg & MDF_DFLTCR_TRGSENS_Msk);
}

/**
  * @brief  Set samples delay on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  samples_delay        Samples delay.
  *                              This parameter must be a number between Min_Data = 0 and Max_Data = 127.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetSamplesDelay(const hal_mdf_handle_t *hmdf,
                                          hal_mdf_block_index_t digital_filter_index,
                                          uint32_t samples_delay)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_SAMPLES_DELAY(samples_delay));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DLYCR, MDF_DLYCR_SKPDLY_Msk, samples_delay);

  return HAL_OK;
}

/**
  * @brief  Get current samples delay on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval uint32_t             Samples delay.
  */
uint32_t HAL_MDF_DFLT_GetSamplesDelay(const hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DLYCR, MDF_DLYCR_SKPDLY_Msk));
}

/**
  * @brief  Set offset compensation on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  offset_compensation  Offset compensation.
  *                              This parameter must be a number between Min_Data = -33554432 and Max_Data = 33554431.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetOffsetCompensation(const hal_mdf_handle_t *hmdf,
                                                hal_mdf_block_index_t digital_filter_index,
                                                int32_t offset_compensation)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_OFFSET_COMPENSATION(offset_compensation));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->OECCR, MDF_OECCR_OFFSET_Msk, (uint32_t)offset_compensation);

  return HAL_OK;
}

/**
  * @brief  Get current offset compensation on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval int32_t              Offset compensation.
  */
int32_t HAL_MDF_DFLT_GetOffsetCompensation(const hal_mdf_handle_t *hmdf,
                                           hal_mdf_block_index_t digital_filter_index)
{
  uint32_t register_offset_value;
  int32_t  offset_compensation;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  register_offset_value = READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->OECCR, MDF_OECCR_OFFSET_Msk);
  if (register_offset_value > (MDF_OECCR_OFFSET_Msk >> 1U))
  {
    /* Negative value */
    register_offset_value |= ~(MDF_OECCR_OFFSET_Msk);
    offset_compensation = (int32_t) register_offset_value;
  }
  else
  {
    /* Positive value */
    offset_compensation = (int32_t) register_offset_value;
  }

  return offset_compensation;
}

/**
  * @brief  Set gain on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  gain                 Gain in step of around 3db (from -48db to 72dB).
  *                              This parameter must be a number between Min_Data = -16 and Max_Data = 24.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetGain(const hal_mdf_handle_t *hmdf,
                                  hal_mdf_block_index_t digital_filter_index,
                                  int32_t gain)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_GAIN(gain));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCICR, MDF_DFLTCICR_SCALE_Msk,
             (MDF_AdjustGainToRegisterValue(gain) << MDF_DFLTCICR_SCALE_Pos));

  return HAL_OK;
}

/**
  * @brief  Get current gain on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval int32_t              Gain.
  */
int32_t HAL_MDF_DFLT_GetGain(const hal_mdf_handle_t *hmdf,
                             hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return MDF_AdjustGainFromRegisterValue((READ_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCICR)
                                          & MDF_DFLTCICR_SCALE_Msk) >> MDF_DFLTCICR_SCALE_Pos);
}

/**
  * @brief  Set integrator value and output division on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  value                Integrator value.
  *                              This parameter must be a number between Min_Data = 1 (bypass) and Max_Data = 128.
  * @param  output_division      Integrator output division.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetIntegrator(const hal_mdf_handle_t *hmdf,
                                        hal_mdf_block_index_t digital_filter_index,
                                        uint32_t value,
                                        hal_mdf_dflt_int_output_division_t output_division)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_INTEGRATOR_VALUE(value));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_INTEGRATOR_OUTPUT_DIVISION(output_division));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTINTR, MDF_DFLTINTR_INTVAL_Msk | MDF_DFLTINTR_INTDIV_Msk,
             ((value - 1U) << MDF_DFLTINTR_INTVAL_Pos) | (uint32_t)output_division);

  return HAL_OK;
}

/**
  * @brief Get current integrator value and output division on a specified digital filter.
  * @param hmdf                   Pointer to a hal_mdf_handle_t.
  * @param digital_filter_index   Digital filter index.
  * @param p_value                Pointer on integrator value.
  * @param p_output_division      Pointer on integrator output division.
  */
void HAL_MDF_DFLT_GetIntegrator(const hal_mdf_handle_t *hmdf,
                                hal_mdf_block_index_t digital_filter_index,
                                uint32_t *p_value,
                                hal_mdf_dflt_int_output_division_t *p_output_division)
{
  uint32_t dfltintr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_value != NULL);
  ASSERT_DBG_PARAM(p_output_division != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  dfltintr_reg = READ_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTINTR);
  *p_value = ((dfltintr_reg & MDF_DFLTINTR_INTVAL_Msk) >> MDF_DFLTINTR_INTVAL_Pos) + 1U;
  *p_output_division = (hal_mdf_dflt_int_output_division_t)(uint32_t)(dfltintr_reg & MDF_DFLTINTR_INTDIV_Msk);
}

/**
  * @brief  Set FIFO threshold on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  fifo_threshold       FIFO threshold.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetFifoThreshold(const hal_mdf_handle_t *hmdf,
                                           hal_mdf_block_index_t digital_filter_index,
                                           hal_mdf_dflt_fifo_threshold_t fifo_threshold)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_FIFO_THRESHOLD(fifo_threshold));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR, MDF_DFLTCR_FTH_Msk, (uint32_t)fifo_threshold);

  return HAL_OK;
}

/**
  * @brief  Get current FIFO threshold on a specified digital filter.
  * @param  hmdf                          Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index          Digital filter index.
  * @retval hal_mdf_dflt_fifo_threshold_t FIFO threshold.
  */
hal_mdf_dflt_fifo_threshold_t HAL_MDF_DFLT_GetFifoThreshold(const hal_mdf_handle_t *hmdf,
                                                            hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (hal_mdf_dflt_fifo_threshold_t)(uint32_t)READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR,
                                                           MDF_DFLTCR_FTH_Msk);
}

/**
  * @brief  Set discard samples on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  discard_samples      Discard samples.
  *                              This parameter must be a number between Min_Data = 0 and Max_Data = 255.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetDiscardSamples(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t digital_filter_index,
                                            uint32_t discard_samples)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_DISCARD_SAMPLES(discard_samples));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR, MDF_DFLTCR_NBDIS_Msk,
             discard_samples << MDF_DFLTCR_NBDIS_Pos);

  return HAL_OK;
}

/**
  * @brief  Get current discard samples on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval uint32_t             Discard samples.
  */
uint32_t HAL_MDF_DFLT_GetDiscardSamples(const hal_mdf_handle_t *hmdf,
                                        hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR, MDF_DFLTCR_NBDIS_Msk) >> MDF_DFLTCR_NBDIS_Pos);
}

/**
  * @brief  Set snapshot format on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  snapshot_format      Snapshot format.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_SetSnapshotFormat(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t digital_filter_index,
                                            hal_mdf_dflt_snapshot_format_t snapshot_format)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_SNAPSHOT_FORMAT(snapshot_format));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR, MDF_DFLTCR_SNPSFMT_Msk, (uint32_t)snapshot_format);

  return HAL_OK;
}

/**
  * @brief  Get current snapshot format on a specified digital filter.
  * @param  hmdf                           Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index           Digital filter index.
  * @retval hal_mdf_dflt_snapshot_format_t Snapshot format.
  */
hal_mdf_dflt_snapshot_format_t HAL_MDF_DFLT_GetSnapshotFormat(const hal_mdf_handle_t *hmdf,
                                                              hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (hal_mdf_dflt_snapshot_format_t)(uint32_t)READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR,
                                                            MDF_DFLTCR_SNPSFMT_Msk);
}

/* Control functions */
/**
  * @brief  Enable reshape filter on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  decimation_ratio     Reshape filter decimation ratio.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_EnableReshapeFilter(const hal_mdf_handle_t *hmdf,
                                              hal_mdf_block_index_t digital_filter_index,
                                              hal_mdf_dflt_rsf_decimation_ratio_t decimation_ratio)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_RSF_DECIMATION_RATIO(decimation_ratio));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR, MDF_DFLTRSFR_RSFLTBYP_Msk | MDF_DFLTRSFR_RSFLTD_Msk,
             (uint32_t)decimation_ratio);

  return HAL_OK;
}

/**
  * @brief  Disable reshape filter on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_DisableReshapeFilter(const hal_mdf_handle_t *hmdf,
                                               hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  SET_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR, MDF_DFLTRSFR_RSFLTBYP);

  return HAL_OK;
}

/**
  * @brief  Check reshape filter status on a specified digital filter.
  * @param  hmdf                      Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index      Digital filter index.
  * @retval hal_mdf_dflt_rsf_status_t Reshape filter status.
  */
hal_mdf_dflt_rsf_status_t HAL_MDF_DFLT_IsEnabledReshapeFilter(const hal_mdf_handle_t *hmdf,
                                                              hal_mdf_block_index_t digital_filter_index)
{
  hal_mdf_dflt_rsf_status_t status;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  status = (IS_BIT_SET(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR, MDF_DFLTRSFR_RSFLTBYP))
           ? HAL_MDF_DFLT_RSF_DISABLED : HAL_MDF_DFLT_RSF_ENABLED;

  return status;
}

/**
  * @brief  Get current reshape filter decimation ratio on a specified digital filter.
  * @param  hmdf                                Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index                Digital filter index.
  * @retval hal_mdf_dflt_rsf_decimation_ratio_t Reshape filter decimation ratio.
  */
hal_mdf_dflt_rsf_decimation_ratio_t HAL_MDF_DFLT_GetReshapeFilterDecimationRatio(const hal_mdf_handle_t *hmdf,
    hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (hal_mdf_dflt_rsf_decimation_ratio_t)(uint32_t)READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR,
                                                                 MDF_DFLTRSFR_RSFLTD_Msk);
}

/**
  * @brief  Enable high-pass filter on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  cut_off_frequency    High-pass filter cut-off frequency.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_EnableHighPassFilter(const hal_mdf_handle_t *hmdf,
                                               hal_mdf_block_index_t digital_filter_index,
                                               hal_mdf_dflt_hpf_cut_off_frequency_t cut_off_frequency)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_HPF_CUT_OFF_FREQUENCY(cut_off_frequency));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  MODIFY_REG(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR, MDF_DFLTRSFR_HPFBYP_Msk | MDF_DFLTRSFR_HPFC_Msk,
             (uint32_t)cut_off_frequency);

  return HAL_OK;
}

/**
  * @brief  Disable high-pass filter on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_DisableHighPassFilter(const hal_mdf_handle_t *hmdf,
                                                hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  SET_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR, MDF_DFLTRSFR_HPFBYP);

  return HAL_OK;
}

/**
  * @brief  Check high-pass filter status on a specified digital filter.
  * @param  hmdf                      Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index      Digital filter index.
  * @retval hal_mdf_dflt_hpf_status_t High-pass filter status.
  */
hal_mdf_dflt_hpf_status_t HAL_MDF_DFLT_IsEnabledHighPassFilter(const hal_mdf_handle_t *hmdf,
                                                               hal_mdf_block_index_t digital_filter_index)
{
  hal_mdf_dflt_hpf_status_t status;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  status = (IS_BIT_SET(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR, MDF_DFLTRSFR_HPFBYP))
           ? HAL_MDF_DFLT_HPF_DISABLED : HAL_MDF_DFLT_HPF_ENABLED;

  return status;
}

/**
  * @brief  Get current high-pass filter cut-off frequency on a specified digital filter.
  * @param  hmdf                                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index                 Digital filter index.
  * @retval hal_mdf_dflt_hpf_cut_off_frequency_t High-pass filter cut-off frequency.
  */
hal_mdf_dflt_hpf_cut_off_frequency_t HAL_MDF_DFLT_GetHighPassFilterCutOffFrequency(const hal_mdf_handle_t *hmdf,
    hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (hal_mdf_dflt_hpf_cut_off_frequency_t)(uint32_t)READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTRSFR,
                                                                  MDF_DFLTRSFR_HPFC_Msk);
}

/* Process functions */
/**
  * @brief  Start acquisition on a specified digital filter in polling mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_BUSY             The digital filter state is not HAL_MDF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_DFLT_StartAcq(hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE,
                         HAL_MDF_DFLT_STATE_ACTIVE);

  SET_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTCR, MDF_DFLTCR_DFLTEN);

  return HAL_OK;
}

/**
  * @brief  Stop acquisition on a specified digital filter in polling mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_StopAcq(hal_mdf_handle_t *hmdf,
                                  hal_mdf_block_index_t digital_filter_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_ACTIVE);

  /* Deactivate digital filter and clear potential pending flags */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);
  WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                   | MDF_DFLTISR_RFOVRF));

  hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Wait available acquisition on a specified digital filter in polling mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  timeout_ms           Acquisition timeout value.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_TIMEOUT          Operation exceeds user timeout.
  */
hal_status_t HAL_MDF_DFLT_PollForAcq(hal_mdf_handle_t *hmdf,
                                     hal_mdf_block_index_t digital_filter_index,
                                     uint32_t timeout_ms)
{
  MDF_Block_TypeDef *p_mdf_block;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_ACTIVE);

  tickstart = HAL_GetTick();

  /* Check if an acquisition is available */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  while (IS_BIT_CLR(p_mdf_block->DFLTISR, MDF_DFLTISR_RXNEF))
  {
    /* Check for the timeout */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* If acquisition mode is asynchronous single shot, set digital filter state to idle */
  if (READ_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_ACQMOD_Msk) == (uint32_t)HAL_MDF_DFLT_ACQ_MODE_ASYNC_SINGLE)
  {
    /* Deactivate digital filter and clear potential pending flags */
    CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);
    WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                     | MDF_DFLTISR_RFOVRF));

    hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;
  }

  return HAL_OK;
}

/**
  * @brief  Get acquisition value on a specified digital filter.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval int32_t              Acquisition value.
  */
int32_t HAL_MDF_DFLT_GetAcqValue(const hal_mdf_handle_t *hmdf,
                                 hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  return (int32_t)(uint32_t)READ_BIT(MDF_GET_BLOCK(hmdf, digital_filter_index)->DFLTDR, MDF_DFLTDR_DR_Msk);
}

/**
  * @brief  Wait available snapshot acquisition on a specified digital filter in polling mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  timeout_ms           Snapshot acquisition timeout value.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_TIMEOUT          Operation exceeds user timeout.
  */
hal_status_t HAL_MDF_DFLT_PollForSnapshotAcq(const hal_mdf_handle_t *hmdf,
                                             hal_mdf_block_index_t digital_filter_index,
                                             uint32_t timeout_ms)
{
  const MDF_Block_TypeDef *p_mdf_block;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_ACTIVE);

  tickstart = HAL_GetTick();

  /* Check if a snapshot acquisition is available */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  while (IS_BIT_CLR(p_mdf_block->DFLTISR, MDF_DFLTISR_SSDRF))
  {
    /* Check for the timeout */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Get snapshot acquisition value, decimation and integrator counters on a specified digital filter.
  * @param hmdf                 Pointer to a hal_mdf_handle_t.
  * @param digital_filter_index Digital filter index.
  * @param p_snapshot_param     Pointer to a snapshot parameters structure.
  */
void HAL_MDF_DFLT_GetSnapshotAcqValue(const hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index,
                                      hal_mdf_dflt_snapshot_param_t *p_snapshot_param)
{
  MDF_Block_TypeDef *p_mdf_block;
  uint32_t snpsdr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_snapshot_param != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  /* Get snapshot acquisition, decimation and integrator counter values */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  snpsdr_reg = READ_REG(p_mdf_block->SNPSDR);
  if (READ_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_SNPSFMT) == (uint32_t)HAL_MDF_DFLT_SNAPSHOT_16BITS)
  {
    p_snapshot_param->value = (int32_t)(uint32_t)(snpsdr_reg & MDF_SNPSDR_SDR_Msk);
    p_snapshot_param->integrator_counter = ((snpsdr_reg & MDF_SNPSDR_EXTSDR_Msk) >> MDF_SNPSDR_EXTSDR_Pos);
  }
  else
  {
    p_snapshot_param->value = (int32_t)(uint32_t)(snpsdr_reg & (MDF_SNPSDR_SDR_Msk | MDF_SNPSDR_EXTSDR_Msk));
  }
  p_snapshot_param->decimation_counter = snpsdr_reg & MDF_SNPSDR_MCICDC_Msk;

  /* Clear snapshot data ready flag */
  SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SSDRF);
}

/**
  * @brief  Start acquisition on a specified digital filter in interrupt mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_BUSY             The digital filter state is not HAL_MDF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_DFLT_StartAcq_IT(hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE,
                         HAL_MDF_DFLT_STATE_ACTIVE);

  /* Enable all acquisition interruptions */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  MDF_DFLT_EnableInterruptions(p_mdf_block);

  /* Activate digital filter */
  SET_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

  return HAL_OK;
}

/**
  * @brief  Stop acquisition on a specified digital filter in interrupt mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_StopAcq_IT(hal_mdf_handle_t *hmdf,
                                     hal_mdf_block_index_t digital_filter_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_ACTIVE);

  /* Deactivate digital filter */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

  /* Disable all acquisition interruptions */
  CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE
            | MDF_DFLTIER_SATIE | MDF_DFLTIER_RFOVRIE);

  /* Clear potential pending flags */
  WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                   | MDF_DFLTISR_RFOVRF));

  hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Start acquisition on a specified digital filter in interrupt mode with optional interruptions.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  interruptions        Optional interruptions.
  *                              This parameter must be a combination of the following values:
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_NONE
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_ACQ_OVR
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_RSF_OVR
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_SAT
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_ALL
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_BUSY             The digital filter state is not HAL_MDF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_DFLT_StartAcq_IT_Opt(hal_mdf_handle_t *hmdf,
                                          hal_mdf_block_index_t digital_filter_index,
                                          uint32_t interruptions)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(IS_MDF_DFLT_OPTIONAL_IT(interruptions));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE,
                         HAL_MDF_DFLT_STATE_ACTIVE);

  /* Enable only acquisition complete and specified optional interruptions */
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  MDF_DFLT_EnableInterruptions_Opt(p_mdf_block, interruptions);

  /* Activate digital filter */
  SET_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

  return HAL_OK;
}

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
/**
  * @brief  Start acquisition on a specified digital filter in DMA mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  p_dma_config         Pointer to DMA configuration structure.
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_ERROR            Operation error.
  * @retval HAL_INVALID_PARAM    Pointer to DMA configuration structure is NULL.
  * @retval HAL_BUSY             The digital filter state is not HAL_MDF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_DFLT_StartAcq_DMA(hal_mdf_handle_t *hmdf,
                                       hal_mdf_block_index_t digital_filter_index,
                                       const hal_mdf_dma_config_t *p_dma_config)
{
  hal_status_t status = HAL_ERROR;
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_dma_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dma_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(p_dma_config->data_length_byte != 0U);
  ASSERT_DBG_PARAM(IS_MDF_DFLT_DMA_DATA_RESOLUTION(p_dma_config->data_resolution));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE,
                         HAL_MDF_DFLT_STATE_ACTIVE);

  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  if (hmdf->hdma[digital_filter_index] != NULL)
  {
    uint32_t src_address;

    /* Set DMA callbacks on DMA handle */
    hmdf->hdma[digital_filter_index]->p_xfer_halfcplt_cb = MDF_DFLT_DMA_HalfCplt;
    hmdf->hdma[digital_filter_index]->p_xfer_cplt_cb = MDF_DFLT_DMA_Cplt;
    hmdf->hdma[digital_filter_index]->p_xfer_error_cb = MDF_DFLT_DMA_Error;

    src_address = (p_dma_config->data_resolution == HAL_MDF_DMA_DATA_RESOLUTION_MSB_ONLY) ?
                  (((uint32_t)&p_mdf_block->DFLTDR) + 2U) : (uint32_t)&p_mdf_block->DFLTDR;


    status = HAL_DMA_StartPeriphXfer_IT_Opt(hmdf->hdma[digital_filter_index], src_address, p_dma_config->address,
                                            p_dma_config->data_length_byte, HAL_DMA_OPT_IT_HT);
  }

  if (status == HAL_OK)
  {
    /* Enable all acquisition interruptions */
    MDF_DFLT_EnableInterruptions(p_mdf_block);

    /* Enable DMA request */
    SET_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DMAEN);

    /* Activate digital filter */
    SET_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);
  }
  else
  {
#if defined (USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[digital_filter_index] |= HAL_MDF_ERROR_DMA;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Stop acquisition on a specified digital filter in DMA mode.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @retval HAL_OK               Operation completed successfully.
  */
hal_status_t HAL_MDF_DFLT_StopAcq_DMA(hal_mdf_handle_t *hmdf,
                                      hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_ACTIVE);

  hmdf->hdma[digital_filter_index]->p_xfer_abort_cb = MDF_DFLT_DMA_Abort;
  if (HAL_DMA_Abort_IT(hmdf->hdma[digital_filter_index]) != HAL_OK)
  {
    MDF_Block_TypeDef *p_mdf_block;

    /* Deactivate digital filter */
    p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
    CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

    /* Disable all acquisition interruptions */
    CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE
              | MDF_DFLTIER_SATIE | MDF_DFLTIER_RFOVRIE);

    /* Clear potential pending flags */
    WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                     | MDF_DFLTISR_RFOVRF));

    /* Disable DMA request */
    CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DMAEN);

    hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_acquisition_stop_cb(hmdf, digital_filter_index);
#else
    HAL_MDF_DFLT_AcqStopCpltCallback(hmdf, digital_filter_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Start acquisition on a specified digital filter in DMA mode with optional interruptions.
  * @param  hmdf                 Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index Digital filter index.
  * @param  p_dma_config         Pointer to DMA configuration structure.
  * @param  interruptions        Optional interruptions.
  *                              This parameter must be a combination of the following values:
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_NONE
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_ACQ_OVR
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_RSF_OVR
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_SAT
  *                                @arg @ref HAL_MDF_DFLT_OPT_IT_ALL
  * @retval HAL_OK               Operation completed successfully.
  * @retval HAL_ERROR            Operation error.
  * @retval HAL_INVALID_PARAM    Pointer to DMA configuration structure is NULL.
  * @retval HAL_BUSY             The digital filter state is not HAL_MDF_DFLT_STATE_IDLE
  *                              (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_DFLT_StartAcq_DMA_Opt(hal_mdf_handle_t *hmdf,
                                           hal_mdf_block_index_t digital_filter_index,
                                           const hal_mdf_dma_config_t *p_dma_config,
                                           uint32_t interruptions)
{
  hal_status_t status = HAL_ERROR;
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));
  ASSERT_DBG_PARAM(p_dma_config != NULL);
  ASSERT_DBG_PARAM(IS_MDF_DFLT_OPTIONAL_IT(interruptions));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dma_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(p_dma_config->data_length_byte != 0U);
  ASSERT_DBG_PARAM(IS_MDF_DFLT_DMA_DATA_RESOLUTION(p_dma_config->data_resolution));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, digital_filter_states[digital_filter_index], HAL_MDF_DFLT_STATE_IDLE,
                         HAL_MDF_DFLT_STATE_ACTIVE);

  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);
  if (hmdf->hdma[digital_filter_index] != NULL)
  {
    uint32_t src_address;

    /* Set DMA callbacks on DMA handle */
    hmdf->hdma[digital_filter_index]->p_xfer_halfcplt_cb = MDF_DFLT_DMA_HalfCplt;
    hmdf->hdma[digital_filter_index]->p_xfer_cplt_cb = MDF_DFLT_DMA_Cplt;
    hmdf->hdma[digital_filter_index]->p_xfer_error_cb = MDF_DFLT_DMA_Error;

    src_address = (p_dma_config->data_resolution == HAL_MDF_DMA_DATA_RESOLUTION_MSB_ONLY) ?
                  (((uint32_t)&p_mdf_block->DFLTDR) + 2U) : (uint32_t)&p_mdf_block->DFLTDR;


    status = HAL_DMA_StartPeriphXfer_IT_Opt(hmdf->hdma[digital_filter_index], src_address, p_dma_config->address,
                                            p_dma_config->data_length_byte, HAL_DMA_OPT_IT_HT);
  }

  if (status == HAL_OK)
  {
    /* Enable only acquisition complete and specified optional interruptions */
    MDF_DFLT_EnableInterruptions_Opt(p_mdf_block, interruptions);

    /* Enable DMA request */
    SET_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DMAEN);

    /* Activate digital filter */
    SET_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);
  }
  else
  {
#if defined (USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[digital_filter_index] |= HAL_MDF_ERROR_DMA;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;
  }

  return status;
}
#endif /* USE_HAL_MDF_DMA */

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group7
  * @{
This section provides a set of functions allowing to configure, process and control out-of-limit detector:
  - Call the function HAL_MDF_OLD_SetConfig() to configure a specified out-of-limit detector.
  - Call the function HAL_MDF_OLD_GetConfig() to get the current configuration of a specified out-of-limit detector.
  - Call the function HAL_MDF_OLD_Start() to activate a specified out-of-limit detector in polling mode.
  - Call the function HAL_MDF_OLD_Stop() to deactivate a specified out-of-limit detector in polling mode.
  - Call the function HAL_MDF_OLD_Start_IT() to activate a specified out-of-limit detector in interrupt mode.
  - Call the function HAL_MDF_OLD_Stop_IT() to deactivate a specified out-of-limit detector in interrupt mode.
  - Call the function HAL_MDF_OLD_IsDetected() to check detection status on a specified out-of-limit detector.
  */

/* Configuration functions */
/**
  * @brief  Configure a specified out-of-limit detector.
  * @param  hmdf                        Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index Out-of-limit detector index.
  * @param  p_config                    Pointer to out-of-limit detector configuration structure.
  * @retval HAL_OK                      Operation completed successfully.
  * @retval HAL_INVALID_PARAM           Pointer to out-of-limit detector configuration structure is NULL.
  */
hal_status_t HAL_MDF_OLD_SetConfig(hal_mdf_handle_t *hmdf,
                                   hal_mdf_block_index_t out_of_limit_detector_index,
                                   const hal_mdf_old_config_t *p_config)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_MDF_OLD_CIC_ORDER(p_config->cic_order));
  ASSERT_DBG_PARAM(IS_MDF_OLD_DECIMATION_RATIO(p_config->decimation_ratio));
  ASSERT_DBG_PARAM(IS_MDF_OLD_THRESHOLD(p_config->high_threshold));
  ASSERT_DBG_PARAM(IS_MDF_OLD_THRESHOLD(p_config->low_threshold));
  ASSERT_DBG_PARAM(IS_MDF_OLD_EVENT_CONFIG(p_config->event_config));
  ASSERT_DBG_PARAM(IS_MDF_BREAK_SIGNALS(p_config->break_signals));
  /* Check that digital filter of this block has a CIC split in two filters */
  p_mdf_block = MDF_GET_BLOCK(hmdf, out_of_limit_detector_index);
  ASSERT_DBG_PARAM(READ_BIT(p_mdf_block->DFLTCICR, MDF_DFLTCICR_CICMOD) < (uint32_t)HAL_MDF_DFLT_CIC_ONE_FILTER_SINC4);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], (uint32_t)HAL_MDF_OLD_STATE_RESET
                   | (uint32_t)HAL_MDF_OLD_STATE_IDLE);
  ASSERT_DBG_STATE(hmdf->digital_filter_states[out_of_limit_detector_index], (uint32_t)HAL_MDF_DFLT_STATE_IDLE
                   | (uint32_t)HAL_MDF_DFLT_STATE_ACTIVE);

  MODIFY_REG(p_mdf_block->OLDCR, MDF_OLDCR_THINB_Msk | MDF_OLDCR_BKOLD_Msk | MDF_OLDCR_ACICN_Msk | MDF_OLDCR_ACICD_Msk,
             (uint32_t)p_config->event_config | (p_config->break_signals << MDF_OLDCR_BKOLD_Pos)
             | (uint32_t)p_config->cic_order | ((p_config->decimation_ratio - 1U) << MDF_OLDCR_ACICD_Pos));
  WRITE_REG(p_mdf_block->OLDTHLR, (uint32_t)p_config->low_threshold);
  WRITE_REG(p_mdf_block->OLDTHHR, (uint32_t)p_config->high_threshold);

  hmdf->out_of_limit_detect_states[out_of_limit_detector_index] = HAL_MDF_OLD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the current configuration of a specified out-of-limit detector.
  * @param hmdf                        Pointer to a hal_mdf_handle_t.
  * @param out_of_limit_detector_index Out-of-limit detector index.
  * @param p_config                    Pointer to out-of-limit detector configuration structure.
  */
void HAL_MDF_OLD_GetConfig(const hal_mdf_handle_t *hmdf,
                           hal_mdf_block_index_t out_of_limit_detector_index,
                           hal_mdf_old_config_t *p_config)
{
  const MDF_Block_TypeDef *p_mdf_block;
  uint32_t old_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], (uint32_t)HAL_MDF_OLD_STATE_IDLE
                   | (uint32_t)HAL_MDF_OLD_STATE_ACTIVE);

  p_mdf_block = MDF_GET_BLOCK(hmdf, out_of_limit_detector_index);
  old_reg = READ_REG(p_mdf_block->OLDCR);
  p_config->cic_order = (hal_mdf_old_cic_order_t)(uint32_t)(old_reg & MDF_OLDCR_ACICN_Msk);
  p_config->decimation_ratio = ((old_reg & MDF_OLDCR_ACICD_Msk) >> MDF_OLDCR_ACICD_Pos) + 1U;
  p_config->event_config = (hal_mdf_old_event_config_t)(uint32_t)(old_reg & MDF_OLDCR_THINB_Msk);
  p_config->break_signals = ((old_reg & MDF_OLDCR_BKOLD_Msk) >> MDF_OLDCR_BKOLD_Pos);
  old_reg = READ_REG(p_mdf_block->OLDTHLR);
  if (old_reg > (MDF_OLDTHLR_OLDTHL_Msk >> 1U))
  {
    /* Negative value */
    old_reg |= ~(MDF_OLDTHLR_OLDTHL_Msk);
    p_config->low_threshold = (int32_t) old_reg;
  }
  else
  {
    /* Positive value */
    p_config->low_threshold = (int32_t) old_reg;
  }
  old_reg = READ_REG(p_mdf_block->OLDTHHR);
  if (old_reg > (MDF_OLDTHHR_OLDTHH_Msk >> 1U))
  {
    /* Negative value */
    old_reg |= ~(MDF_OLDTHHR_OLDTHH_Msk);
    p_config->high_threshold = (int32_t) old_reg;
  }
  else
  {
    /* Positive value */
    p_config->high_threshold = (int32_t) old_reg;
  }
}

/* Process functions */
/**
  * @brief  Activate a specified out-of-limit detector in polling mode.
  * @param  hmdf                        Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index Out-of-limit detector index.
  * @retval HAL_OK                      Operation completed successfully.
  * @retval HAL_BUSY                    The out-of-limit detector state is not HAL_MDF_OLD_STATE_IDLE
  *                                     (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_OLD_Start(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_IDLE,
                         HAL_MDF_OLD_STATE_ACTIVE);

  SET_BIT(MDF_GET_BLOCK(hmdf, out_of_limit_detector_index)->OLDCR, MDF_OLDCR_OLDEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified out-of-limit detector in polling mode.
  * @param  hmdf                        Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index Out-of-limit detector index.
  * @retval HAL_OK                      Operation completed successfully.
  */
hal_status_t HAL_MDF_OLD_Stop(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_ACTIVE);

  /* Deactivate out-of-limit detector and clear potential pending flags */
  p_mdf_block = MDF_GET_BLOCK(hmdf, out_of_limit_detector_index);
  CLEAR_BIT(p_mdf_block->OLDCR, MDF_OLDCR_OLDEN);
  SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_OLDF);

  hmdf->out_of_limit_detect_states[out_of_limit_detector_index] = HAL_MDF_OLD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Activate a specified out-of-limit detector in interrupt mode.
  * @param  hmdf                        Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index Out-of-limit detector index.
  * @retval HAL_OK                      Operation completed successfully.
  * @retval HAL_BUSY                    The out-of-limit detector state is not HAL_MDF_OLD_STATE_IDLE
  *                                     (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_MDF_OLD_Start_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hmdf, out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_IDLE,
                         HAL_MDF_OLD_STATE_ACTIVE);

  /* Enable out-of-limit detector interrupt */
  p_mdf_block = MDF_GET_BLOCK(hmdf, out_of_limit_detector_index);
  SET_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_OLDIE);

  /* Activate out-of-limit detector */
  SET_BIT(p_mdf_block->OLDCR, MDF_OLDCR_OLDEN);

  return HAL_OK;
}

/**
  * @brief  Deactivate a specified out-of-limit detector in interrupt mode.
  * @param  hmdf                        Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index Out-of-limit detector index.
  * @retval HAL_OK                      Operation completed successfully.
  */
hal_status_t HAL_MDF_OLD_Stop_IT(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t out_of_limit_detector_index)
{
  MDF_Block_TypeDef *p_mdf_block;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_ACTIVE);

  /* Deactivate out-of-limit detector, disable interrupt and clear potential pending flags */
  p_mdf_block = MDF_GET_BLOCK(hmdf, out_of_limit_detector_index);
  CLEAR_BIT(p_mdf_block->OLDCR, MDF_OLDCR_OLDEN);
  CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_OLDIE);
  SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_OLDF);

  hmdf->out_of_limit_detect_states[out_of_limit_detector_index] = HAL_MDF_OLD_STATE_IDLE;

  return HAL_OK;
}

/* Control functions */
/**
  * @brief  Check detection status on a specified out-of-limit detector.
  * @param  hmdf                          Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index   Out-of-limit detector index.
  * @param  p_threshold_info              Pointer to threshold information.
  * @retval hal_mdf_old_status_t          Out-of-limit detection status.
  */
hal_mdf_old_status_t HAL_MDF_OLD_IsDetected(const hal_mdf_handle_t *hmdf,
                                            hal_mdf_block_index_t out_of_limit_detector_index,
                                            hal_mdf_old_threshold_info_t *p_threshold_info)
{
  MDF_Block_TypeDef *p_mdf_block;
  hal_mdf_old_status_t status;
  uint32_t dfltisr_reg;

  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));
  ASSERT_DBG_PARAM(p_threshold_info != NULL);

  ASSERT_DBG_STATE(hmdf->global_state, HAL_MDF_STATE_ACTIVE);
  ASSERT_DBG_STATE(hmdf->out_of_limit_detect_states[out_of_limit_detector_index], HAL_MDF_OLD_STATE_ACTIVE);

  /* Check out-of-limit detection status */
  p_mdf_block = MDF_GET_BLOCK(hmdf, out_of_limit_detector_index);
  dfltisr_reg = READ_REG(p_mdf_block->DFLTISR);
  if (IS_BIT_SET(dfltisr_reg, MDF_DFLTISR_OLDF))
  {
    status = HAL_MDF_OUT_OF_LIMIT_DETECTED;

    /* Get threshold information */
    if (IS_BIT_CLR(dfltisr_reg, MDF_DFLTISR_THLF | MDF_DFLTISR_THHF))
    {
      *p_threshold_info = HAL_MDF_OLD_THRESHOLDS_IN;
    }
    else if (IS_BIT_SET(dfltisr_reg, MDF_DFLTISR_THLF))
    {
      *p_threshold_info = HAL_MDF_OLD_THRESHOLD_LOW;
    }
    else
    {
      *p_threshold_info = HAL_MDF_OLD_THRESHOLD_HIGH;
    }

    /* Clear out-of-limit detection flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_OLDF);
  }
  else
  {
    status = HAL_MDF_OUT_OF_LIMIT_NOT_DETECTED;
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group8
  * @{
This section provides function allowing to handle the MDF interrupt request on blocks, HAL_MDF_IRQHandler().

This section provides also a set of functions allowing to handle callbacks:
  - HAL_MDF_DFLT_AcqCpltCallback() is called when acquisition complete occurs on a specified digital filter.
  - HAL_MDF_DFLT_AcqHalfCpltCallback() is called when acquisition half complete occurs on a specified digital filter.
  - HAL_MDF_DFLT_AcqStopCpltCallback() is called when acquisition stop complete occurs on a specified digital filter.
  - HAL_MDF_OLD_Callback() is called when out-of-limit detection occurs on a specified out-of-limit detector.
  - HAL_MDF_ErrorCallback() is called when an error occurs on a specified block.

This section provides also a set of functions allowing to register callbacks:
  - Call the function HAL_MDF_DFLT_RegisterAcqCpltCallback() to register acquisition complete callback.
  - Call the function HAL_MDF_DFLT_RegisterAcqHalfCpltCallback() to register acquisition half complete callback.
  - Call the function HAL_MDF_DFLT_RegisterAcqStopCpltCallback() to register acquisition stop complete callback.
  - Call the function HAL_MDF_OLD_RegisterCallback() to register out-of-limit detection callback.
  - Call the function HAL_MDF_RegisterErrorCallback() to register error callback.
  */

/**
  * @brief Handle the MDF interrupt request on a specified block.
  * @param hmdf        Pointer to a hal_mdf_handle_t.
  * @param block_index Block index.
  */
void HAL_MDF_IRQHandler(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t block_index)
{
  MDF_Block_TypeDef *p_mdf_block;
  uint32_t interruptions;
  uint32_t flags;

  p_mdf_block = MDF_GET_BLOCK(hmdf, block_index);
  interruptions = READ_REG(p_mdf_block->DFLTIER);
  flags = READ_REG(p_mdf_block->DFLTISR);
  interruptions &= flags;

  /* RXFIFO threshold interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_FTHF))
  {
    /* If acquisition mode is asynchronous single shot, set digital filter state to idle */
    if (READ_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_ACQMOD_Msk) == (uint32_t)HAL_MDF_DFLT_ACQ_MODE_ASYNC_SINGLE)
    {
      /* Deactivate digital filter, disable acquisition interruptions and clear potential pending flags */
      CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);
      CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE
                | MDF_DFLTIER_SATIE | MDF_DFLTIER_RFOVRIE);
      WRITE_REG(p_mdf_block->DFLTISR, MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                | MDF_DFLTISR_RFOVRF);

      hmdf->digital_filter_states[block_index] = HAL_MDF_DFLT_STATE_IDLE;
    }

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_acquisition_cplt_cb(hmdf, block_index);
#else
    HAL_MDF_DFLT_AcqCpltCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Snapshot data ready interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_SSDRF))
  {
    /* Clear snapshot data ready flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SSDRF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_acquisition_cplt_cb(hmdf, block_index);
#else
    HAL_MDF_DFLT_AcqCpltCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Out-of-limit detector interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_OLDF))
  {
    /* Get threshold information */
    hal_mdf_old_threshold_info_t threshold_info;
    if (IS_BIT_CLR(flags, MDF_DFLTISR_THLF | MDF_DFLTISR_THHF))
    {
      threshold_info = HAL_MDF_OLD_THRESHOLDS_IN;
    }
    else if (IS_BIT_SET(flags, MDF_DFLTISR_THLF))
    {
      threshold_info = HAL_MDF_OLD_THRESHOLD_LOW;
    }
    else
    {
      threshold_info = HAL_MDF_OLD_THRESHOLD_HIGH;
    }

    /* Clear out-of-limit detection flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_OLDF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_out_of_limit_detector_cb(hmdf, block_index, threshold_info);
#else
    HAL_MDF_OLD_Callback(hmdf, block_index, threshold_info);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Data overflow interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_DOVRF))
  {
#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[block_index] |= HAL_MDF_ERROR_DFLT_ACQ_OVERFLOW;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Clear data overflow flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_DOVRF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_error_cb(hmdf, block_index);
#else
    HAL_MDF_ErrorCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Snapshot overrun interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_SSOVRF))
  {
#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[block_index] |= HAL_MDF_ERROR_DFLT_ACQ_OVERFLOW;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Clear snapshot overrun flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SSOVRF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_error_cb(hmdf, block_index);
#else
    HAL_MDF_ErrorCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Saturation interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_SATF))
  {
#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[block_index] |= HAL_MDF_ERROR_DFLT_SATURATION;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Clear saturation flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SATF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_error_cb(hmdf, block_index);
#else
    HAL_MDF_ErrorCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Reshape filter overrun interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_RFOVRF))
  {
#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[block_index] |= HAL_MDF_ERROR_DFLT_RSF_OVERRUN;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Clear reshape filter overrun flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_RFOVRF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_error_cb(hmdf, block_index);
#else
    HAL_MDF_ErrorCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Clock absence detection interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_CKABF))
  {
#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[block_index] |= HAL_MDF_ERROR_SITF_CLOCK_ABSENCE;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Clear clock absence detection flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_CKABF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_error_cb(hmdf, block_index);
#else
    HAL_MDF_ErrorCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }

  /* Short-circuit detection interruption occurrence */
  if (IS_BIT_SET(interruptions, MDF_DFLTISR_SCDF))
  {
#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
    hmdf->last_error_codes[block_index] |= HAL_MDF_ERROR_SHORT_CIRCUIT;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

    /* Clear short-circuit detection flag */
    SET_BIT(p_mdf_block->DFLTISR, MDF_DFLTISR_SCDF);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
    hmdf->p_error_cb(hmdf, block_index);
#else
    HAL_MDF_ErrorCallback(hmdf, block_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
  }
}

/**
  * @brief   Acquisition complete callback.
  * @param   hmdf                 Pointer to a hal_mdf_handle_t.
  * @param   digital_filter_index Digital filter index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_MDF_DFLT_AcqCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t digital_filter_index)
{
  STM32_UNUSED(hmdf);
  STM32_UNUSED(digital_filter_index);
}

/**
  * @brief   Acquisition half complete callback.
  * @param   hmdf                 Pointer to a hal_mdf_handle_t.
  * @param   digital_filter_index Digital filter index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_MDF_DFLT_AcqHalfCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t digital_filter_index)
{
  STM32_UNUSED(hmdf);
  STM32_UNUSED(digital_filter_index);
}

/**
  * @brief   Acquisition stop callback.
  * @param   hmdf                 Pointer to a hal_mdf_handle_t.
  * @param   digital_filter_index Digital filter index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_MDF_DFLT_AcqStopCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t digital_filter_index)
{
  STM32_UNUSED(hmdf);
  STM32_UNUSED(digital_filter_index);
}

/**
  * @brief   Out-of-limit detection callback.
  * @param   hmdf                         Pointer to a hal_mdf_handle_t.
  * @param   out_of_limit_detector_index  Out-of-limit detector index.
  * @param   threshold_info               Threshold information.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_MDF_OLD_Callback(hal_mdf_handle_t *hmdf,
                                 hal_mdf_block_index_t out_of_limit_detector_index,
                                 hal_mdf_old_threshold_info_t threshold_info)
{
  STM32_UNUSED(hmdf);
  STM32_UNUSED(out_of_limit_detector_index);
  STM32_UNUSED(threshold_info);
}

/**
  * @brief   Error callback.
  * @param   hmdf        Pointer to a hal_mdf_handle_t.
  * @param   block_index Block index.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_MDF_ErrorCallback(hal_mdf_handle_t *hmdf, hal_mdf_block_index_t block_index)
{
  STM32_UNUSED(hmdf);
  STM32_UNUSED(block_index);
}

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a user acquisition complete callback.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_MDF_DFLT_RegisterAcqCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->p_acquisition_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user acquisition half complete callback.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_MDF_DFLT_RegisterAcqHalfCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->p_acquisition_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user acquisition stop callback.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_MDF_DFLT_RegisterAcqStopCpltCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->p_acquisition_stop_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user out-of-limit detection callback.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_MDF_OLD_RegisterCallback(hal_mdf_handle_t *hmdf, hal_mdf_old_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->p_out_of_limit_detector_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user error callback.
  * @param  hmdf              Pointer to a hal_mdf_handle_t.
  * @param  p_callback        Pointer to the callback function.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer to the callback function is NULL.
  */
hal_status_t HAL_MDF_RegisterErrorCallback(hal_mdf_handle_t *hmdf, hal_mdf_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hmdf->p_error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup MDF_Exported_Functions_Group9
  * @{
This section provides a set of functions allowing to get all current states:
  - Call the function HAL_MDF_GetState() to get the current global state.
  - Call the function HAL_MDF_SITF_GetState() to get the current state of a specified serial interface.
  - Call the function HAL_MDF_SCD_GetState() to get the current state of a specified short-circuit detector.
  - Call the function HAL_MDF_DFLT_GetState() to get the current state of a specified digital filter.
  - Call the function HAL_MDF_OLD_GetState() to get the current state of a specified out-of-limit detector.
  */

/**
  * @brief  Get the current global state.
  * @param  hmdf            Pointer to a hal_mdf_handle_t.
  * @retval hal_mdf_state_t Global state.
  */
hal_mdf_state_t HAL_MDF_GetState(const hal_mdf_handle_t *hmdf)
{
  ASSERT_DBG_PARAM(hmdf != NULL);

  return hmdf->global_state;
}

/**
  * @brief  Get the current state of a specified serial interface.
  * @param  hmdf                             Pointer to a hal_mdf_handle_t.
  * @param  serial_interface_index           Serial interface index.
  * @retval hal_mdf_serial_interface_state_t Serial interface state.
  */
hal_mdf_serial_interface_state_t HAL_MDF_SITF_GetState(const hal_mdf_handle_t *hmdf,
                                                       hal_mdf_block_index_t serial_interface_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)serial_interface_index));

  return hmdf->serial_interface_states[serial_interface_index];
}

/**
  * @brief  Get the current state of a specified short-circuit detector.
  * @param  hmdf                         Pointer to a hal_mdf_handle_t.
  * @param  short_circuit_detector_index Short-circuit detector index.
  * @retval hal_mdf_scd_state_t          Short-circuit detector state.
  */
hal_mdf_scd_state_t HAL_MDF_SCD_GetState(const hal_mdf_handle_t *hmdf,
                                         hal_mdf_block_index_t short_circuit_detector_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)short_circuit_detector_index));

  return hmdf->short_circuit_detect_states[short_circuit_detector_index];
}

/**
  * @brief  Get the current state of a specified digital filter.
  * @param  hmdf                           Pointer to a hal_mdf_handle_t.
  * @param  digital_filter_index           Digital filter index.
  * @retval hal_mdf_digital_filter_state_t Digital filter state.
  */
hal_mdf_digital_filter_state_t HAL_MDF_DFLT_GetState(const hal_mdf_handle_t *hmdf,
                                                     hal_mdf_block_index_t digital_filter_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)digital_filter_index));

  return hmdf->digital_filter_states[digital_filter_index];
}

/**
  * @brief  Get the current state of a specified out-of-limit detector.
  * @param  hmdf                        Pointer to a hal_mdf_handle_t.
  * @param  out_of_limit_detector_index Out-of-limit detector index.
  * @retval hal_mdf_old_state_t         Out-of-limit detector state.
  */
hal_mdf_old_state_t HAL_MDF_OLD_GetState(const hal_mdf_handle_t *hmdf,
                                         hal_mdf_block_index_t out_of_limit_detector_index)
{
  ASSERT_DBG_PARAM(hmdf != NULL);
  ASSERT_DBG_PARAM(IS_MDF_BLOCK_INDEX((uint32_t)out_of_limit_detector_index));

  return hmdf->out_of_limit_detect_states[out_of_limit_detector_index];
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup MDF_Private_Functions
  * @{
  */

/**
  * @brief  Adjust gain to register value.
  * @param  gain    User gain.
  * @retval int32_t Register gain value.
  */
static uint32_t MDF_AdjustGainToRegisterValue(int32_t gain)
{
  uint32_t register_gain;

  if (gain < 0)
  {
    int32_t adjust_gain;

    /* adjust gain value to set on register for negative value (offset of -16) */
    adjust_gain = gain - 16;
    register_gain = ((uint32_t)adjust_gain) & (MDF_DFLTCICR_SCALE_Msk >> MDF_DFLTCICR_SCALE_Pos);
  }
  else
  {
    /* for positive value, no offset to apply */
    register_gain = (uint32_t)gain;
  }

  return register_gain;
}

/**
  * @brief  Adjust gain from register value.
  * @param  register_gain Register gain value.
  * @retval uint32_t      User gain.
  */
static int32_t MDF_AdjustGainFromRegisterValue(uint32_t register_gain)
{
  int32_t gain;

  if (register_gain > 31U)
  {
    /* adjust gain value to set on register for negative value (offset of +16) */
    gain = (int32_t)(uint32_t)(register_gain | ~(MDF_DFLTCICR_SCALE_Msk >> MDF_DFLTCICR_SCALE_Pos)) + 16;
  }
  else
  {
    /* for positive value, no offset to apply */
    gain = (int32_t) register_gain;
  }

  return gain;
}

/**
  * @brief  Enable all acquisition interruptions for a specified digital filter.
  * @param  p_mdf_block Pointer to a specified MDF block.
  */
static void MDF_DFLT_EnableInterruptions(MDF_Block_TypeDef *p_mdf_block)
{
  uint32_t it_enable;

  if (READ_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_ACQMOD_Msk) == (uint32_t)HAL_MDF_DFLT_ACQ_MODE_SYNC_SNAPSHOT)
  {
    it_enable = MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE | MDF_DFLTIER_SATIE;
  }
  else
  {
    it_enable = MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SATIE;
  }
  if (IS_BIT_CLR(p_mdf_block->DFLTRSFR, MDF_DFLTRSFR_RSFLTBYP))
  {
    it_enable |= MDF_DFLTIER_RFOVRIE;
  }
  MODIFY_REG(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE_Msk | MDF_DFLTIER_DOVRIE_Msk | MDF_DFLTIER_SSDRIE_Msk
             | MDF_DFLTIER_SSOVRIE_Msk | MDF_DFLTIER_SATIE_Msk | MDF_DFLTIER_RFOVRIE_Msk, it_enable);
}

/**
  * @brief  Enable only acquisition complete and optional interruptions for a specified digital filter.
  * @param  p_mdf_block Pointer to MDF block.
  * @param  interruptions Optional interruptions.
  *                       This parameter must be a combination of the following values:
  *                         @arg @ref HAL_MDF_DFLT_OPT_IT_NONE
  *                         @arg @ref HAL_MDF_DFLT_OPT_IT_ACQ_OVR
  *                         @arg @ref HAL_MDF_DFLT_OPT_IT_RSF_OVR
  *                         @arg @ref HAL_MDF_DFLT_OPT_IT_SAT
  *                         @arg @ref HAL_MDF_DFLT_OPT_IT_ALL
  */
static void MDF_DFLT_EnableInterruptions_Opt(MDF_Block_TypeDef *p_mdf_block, uint32_t interruptions)
{
  uint32_t it_enable;

  if (READ_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_ACQMOD_Msk) == (uint32_t)HAL_MDF_DFLT_ACQ_MODE_SYNC_SNAPSHOT)
  {
    it_enable = MDF_DFLTIER_SSDRIE;
    if ((interruptions & HAL_MDF_DFLT_OPT_IT_ACQ_OVR) == HAL_MDF_DFLT_OPT_IT_ACQ_OVR)
    {
      it_enable |= MDF_DFLTIER_SSOVRIE;
    }
  }
  else
  {
    it_enable = MDF_DFLTIER_FTHIE;
    if ((interruptions & HAL_MDF_DFLT_OPT_IT_ACQ_OVR) == HAL_MDF_DFLT_OPT_IT_ACQ_OVR)
    {
      it_enable |= MDF_DFLTIER_DOVRIE;
    }
  }
  if ((interruptions & HAL_MDF_DFLT_OPT_IT_SAT) == HAL_MDF_DFLT_OPT_IT_SAT)
  {
    it_enable |= MDF_DFLTIER_SATIE;
  }
  if ((interruptions & HAL_MDF_DFLT_OPT_IT_RSF_OVR) == HAL_MDF_DFLT_OPT_IT_RSF_OVR)
  {
    it_enable |= MDF_DFLTIER_RFOVRIE;
  }
  MODIFY_REG(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE_Msk | MDF_DFLTIER_DOVRIE_Msk | MDF_DFLTIER_SSDRIE_Msk
             | MDF_DFLTIER_SSOVRIE_Msk | MDF_DFLTIER_SATIE_Msk | MDF_DFLTIER_RFOVRIE_Msk, it_enable);
}

#if defined (USE_HAL_MDF_DMA) && (USE_HAL_MDF_DMA == 1)
/**
  * @brief  Get block index corresponding to DMA handle on MDF handle.
  * @param  hmdf                  Pointer to a hal_mdf_handle_t.
  * @param  hdma                  Pointer to a hal_dma_handle_t.
  * @retval hal_mdf_block_index_t Digital filter index.
  */
static hal_mdf_block_index_t MDF_DFLT_GetBlockIndexFromDmaHandle(const hal_mdf_handle_t *hmdf,
                                                                 const hal_dma_handle_t *hdma)
{
  uint32_t index = 0U;

  while ((hmdf->hdma[index] != hdma) && (index < (MDF1_BLOCKS_NUMBER - 1U)))
  {
    index++;
  }

  return (hal_mdf_block_index_t) index;
}

/**
  * @brief  DMA transfer complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void MDF_DFLT_DMA_Cplt(hal_dma_handle_t *hdma)
{
  hal_mdf_handle_t *hmdf = (hal_mdf_handle_t *) hdma->p_parent;
  hal_mdf_block_index_t digital_filter_index;
  MDF_Block_TypeDef *p_mdf_block;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = MDF_DFLT_GetBlockIndexFromDmaHandle(hmdf, hdma);
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    /* Deactivate digital filter */
    CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

    /* Disable DMA request */
    CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DMAEN);

    /* Disable all acquisition interruptions */
    CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE
              | MDF_DFLTIER_SATIE | MDF_DFLTIER_RFOVRIE);

    /* Clear potential pending flags */
    WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                     | MDF_DFLTISR_RFOVRF));

    hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;
  }

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  hmdf->p_acquisition_cplt_cb(hmdf, digital_filter_index);
#else
  HAL_MDF_DFLT_AcqCpltCallback(hmdf, digital_filter_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA half transfer complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void MDF_DFLT_DMA_HalfCplt(hal_dma_handle_t *hdma)
{
  hal_mdf_handle_t *hmdf = (hal_mdf_handle_t *) hdma->p_parent;
  hal_mdf_block_index_t digital_filter_index;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = MDF_DFLT_GetBlockIndexFromDmaHandle(hmdf, hdma);

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  hmdf->p_acquisition_half_cplt_cb(hmdf, digital_filter_index);
#else
  HAL_MDF_DFLT_AcqHalfCpltCallback(hmdf, digital_filter_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA error callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void MDF_DFLT_DMA_Error(hal_dma_handle_t *hdma)
{
  hal_mdf_handle_t *hmdf = (hal_mdf_handle_t *) hdma->p_parent;
  hal_mdf_block_index_t digital_filter_index;
  MDF_Block_TypeDef *p_mdf_block;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = MDF_DFLT_GetBlockIndexFromDmaHandle(hmdf, hdma);
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);

#if defined(USE_HAL_MDF_GET_LAST_ERRORS) && (USE_HAL_MDF_GET_LAST_ERRORS == 1)
  hmdf->last_error_codes[digital_filter_index] |= HAL_MDF_ERROR_DMA;
#endif /* USE_HAL_MDF_GET_LAST_ERRORS */

  /* Deactivate digital filter */
  CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

  /* Disable DMA request */
  CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DMAEN);

  /* Disable all acquisition interruptions */
  CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE
            | MDF_DFLTIER_SATIE | MDF_DFLTIER_RFOVRIE);

  /* Clear potential pending flags */
  WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                   | MDF_DFLTISR_RFOVRF));

  hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  hmdf->p_error_cb(hmdf, digital_filter_index);
#else
  HAL_MDF_ErrorCallback(hmdf, digital_filter_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA abort callback.
  * @param  hdma Pointer to a hal_dma_handle_t.
  */
static void MDF_DFLT_DMA_Abort(hal_dma_handle_t *hdma)
{
  hal_mdf_handle_t *hmdf = (hal_mdf_handle_t *) hdma->p_parent;
  hal_mdf_block_index_t digital_filter_index;
  MDF_Block_TypeDef *p_mdf_block;

  /* Retrieve digital filter index from DMA handle */
  digital_filter_index = MDF_DFLT_GetBlockIndexFromDmaHandle(hmdf, hdma);
  p_mdf_block = MDF_GET_BLOCK(hmdf, digital_filter_index);

  /* Deactivate digital filter */
  CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DFLTEN);

  /* Disable DMA request */
  CLEAR_BIT(p_mdf_block->DFLTCR, MDF_DFLTCR_DMAEN);

  /* Disable all acquisition interruptions */
  CLEAR_BIT(p_mdf_block->DFLTIER, MDF_DFLTIER_FTHIE | MDF_DFLTIER_DOVRIE | MDF_DFLTIER_SSDRIE | MDF_DFLTIER_SSOVRIE
            | MDF_DFLTIER_SATIE | MDF_DFLTIER_RFOVRIE);

  /* Clear potential pending flags */
  WRITE_REG(p_mdf_block->DFLTISR, (MDF_DFLTISR_DOVRF | MDF_DFLTISR_SSDRF | MDF_DFLTISR_SSOVRF | MDF_DFLTISR_SATF
                                   | MDF_DFLTISR_RFOVRF));

  hmdf->digital_filter_states[digital_filter_index] = HAL_MDF_DFLT_STATE_IDLE;

#if defined(USE_HAL_MDF_REGISTER_CALLBACKS) && (USE_HAL_MDF_REGISTER_CALLBACKS == 1)
  hmdf->p_acquisition_stop_cb(hmdf, digital_filter_index);
#else
  HAL_MDF_DFLT_AcqStopCpltCallback(hmdf, digital_filter_index);
#endif /* USE_HAL_MDF_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_MDF_DMA */

/**
  * @}
  */

#endif /* USE_HAL_MDF_MODULE */

/**
  * @}
  */

/**
  * @}
  */
