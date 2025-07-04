/**
  ******************************************************************************
  * @file    stm32u5xx_hal_sai.c
  * @brief   SAI HAL module driver.
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

/** @addtogroup SAI
  * @{
# How to use the HAL SAI driver

## The HAL SAI driver can be used as follows:

1. Declare a hal_sai_handle_t handle structure and initialize the SAIx driver with a SAI HW block by calling
   the HAL_SAI_Init().
   The SAIx clock is enabled inside the HAL_SAI_Init() if USE_HAL_SAI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.
2. Configure the low level hardware (GPIO, CLOCK, NVIC, DMA...):
  - Enable the SAIx clock if USE_HAL_SAI_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO.
  - SAIx pins configuration:
    - Enable the clock for the SAIx GPIOs
    - Configure SAIx pins as alternate function pull-up
  - NVIC configuration if you need to use interrupt process
    - Configure the SAIx interrupt priority.
    - Enable the NVIC SAIx IRQ handle.
  - DMA configuration if you need to use DMA process
    - Declare a DMA handle structure for the Tx/Rx stream.
    - Enable the DMAx interface clock.
    - Configure the declared DMA handle structure with the required Tx/Rx parameters.
    - Configure the DMA Tx/Rx Stream.
    - Associate the initialized DMA handle to the SAI DMA Tx/Rx handle.
    - Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx Stream.
  - SAI kernel clock has to be activated and selected.

3. Configure the minimal configuration needed for the SAI driver by calling HAL_SAI_SetConfig().
4. Configure and/or enable advanced features. For instance, HAL_SAI_SetCompanding() or HAL_SAI_EnableOutputDrive().
   All these advanced configurations are optional (not mandatory).

  - In master Tx mode: enabling the audio block immediately generates the bit clock
    for the external slaves even if there is no data in the FIFO. However, FS signal
    generation is conditioned by the presence of data in the FIFO.

  - In master Rx mode: enabling the audio block immediately generates the bit clock
    and FS signal for the external slaves.

  - It is mandatory to respect the following conditions in order to avoid bad SAI behavior:
    - First bit Offset <= (Slot size - Data size)
    - Data size <= Slot size
    - Number of Slots x Slot size = Frame length
    - The number of slots must be even when @ref HAL_SAI_FS_CHANNEL_IDENTIFICATION is selected.

  - PDM interface can be activated through HAL_SAI_EnablePdm() function.
    Please note that PDM interface is only available for SAI1 block A.
    PDM microphone delays can be tuned with HAL_SAI_SetPdmMicDelay() function.

5. Operation modes
  - Polling mode operation:

    - Send an amount of samples in blocking mode using HAL_SAI_Transmit().
    - Receive an amount of samples in blocking mode using HAL_SAI_Receive().

  - Interrupt mode operation:

    - Send an amount of samples in non-blocking mode using HAL_SAI_Transmit_IT().
    - At transmission end of transfer, HAL_SAI_TxCpltCallback() is executed and user can
      add his own code by overriding this weak callback function or by registering a callback function.
    - Receive an amount of samples in non-blocking mode using HAL_SAI_Receive_IT().
    - At reception end of transfer, HAL_SAI_RxCpltCallback() is executed and user can
      add his own code by overriding this weak callback function or by registering a callback function.
    - In case of flag error, HAL_SAI_ErrorCallback() function is executed and user can
      add his own code by overriding this weak callback function or by registering a callback function.

  - DMA mode operation:

    - Send an amount of samples in non-blocking mode (DMA) using HAL_SAI_Transmit_DMA().
    - At transmission end of transfer, HAL_SAI_TxCpltCallback() is executed and user can
      add his own code by overriding this weak callback function or by registering a callback function.
    - Receive an amount of samples in non-blocking mode (DMA) using HAL_SAI_Receive_DMA().
    - At reception end of transfer, HAL_SAI_RxCpltCallback() is executed and user can
      add his own code by overriding this weak callback function or by registering a callback function.
    - In case of flag error, HAL_SAI_ErrorCallback() function is executed and user can
      add his own code by overriding this weak callback function or by registering a callback function.
    - Pause the DMA Transfer using HAL_SAI_Pause_DMA().
    - Resume the DMA Transfer using HAL_SAI_Resume_DMA().
    - Abort the current transfer: HAL_SAI_Abort() or HAL_SAI_Abort_IT().

  - Mute management:

    - HAL_SAI_MuteTx(): Enable the mute in Tx mode.
    - HAL_SAI_UnmuteTx(): Disable the mute in Tx mode.
    - HAL_SAI_EnableMuteRxDetection(): Enable the mute in Rx mode.
    - HAL_SAI_DisableMuteRxDetection(): Disable the mute in Rx mode.
    - HAL_SAI_IsEnabledMuteRxDetection(): Get the mute Rx detection status.

6. Callbacks definition in Interrupt or DMA mode:

  When the compilation define USE_HAL_SAI_REGISTER_CALLBACKS is set to 1, the user can configure dynamically the
  driver callbacks, via its own method:

Callback name               | Default value                      | Callback registration function
----------------------------| -----------------------------------| --------------------------------------------
TxHalfCpltCallback          | HAL_SAI_TxHalfCpltCallback()       | HAL_SAI_RegisterTxHalfCpltCallback()
TxCpltCallback              | HAL_SAI_TxCpltCallback()           | HAL_SAI_RegisterTxCpltCallback()
RxHalfCpltCallback          | HAL_SAI_RxHalfCpltCallback()       | HAL_SAI_RegisterRxHalfCpltCallback()
RxCpltCallback              | HAL_SAI_RxCpltCallback()           | HAL_SAI_RegisterRxCpltCallback()
MuteCallback                | HAL_SAI_MuteCallback()             | HAL_SAI_RegisterMuteCallback()
ErrorCallback               | HAL_SAI_ErrorCallback()            | HAL_SAI_RegisterErrorCallback()
AbortCpltCallback           | HAL_SAI_AbortCpltCallback()        | HAL_SAI_RegisterAbortCpltCallback()

  If one needs to unregister a callback, register the default callback via the registration function.

  By default, after the HAL_SAI_Init() and when the state is @ref HAL_SAI_STATE_INIT, all callbacks are set to the
  corresponding default weak functions.

  Callbacks can be registered in handle global_state @ref HAL_SAI_STATE_INIT and @ref HAL_SAI_STATE_IDLE.

  When the compilation define USE_HAL_SAI_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
  feature is not available and weak callbacks are used, represented by the default value in the table above.

## Acquire/Release the SAI bus

  When the compilation flag USE_HAL_MUTEX is set to 1, it allows the user to acquire/reserve the whole SAI bus for
  executing process.
  The HAL Acquire/Release are based on the HAL OS abstraction layer (stm32_hal_os.c/.h osal):
  HAL_SAI_AcquireBus() for acquire the bus or wait for it.
  HAL_SAI_ReleaseBus() for releasing the bus.
  When the compilation flag USE_HAL_MUTEX is set to 0 or not defined, HAL_SAI_AcquireBus()/HAL_SAI_ReleaseBus()
  are not available.

## Configuration inside the HAL SAI driver:

Config defines                 | Where            | Default value     | Note
-------------------------------| -----------------| ------------------| -------------------------------------------
USE_HAL_SAI_MODULE             | hal_conf.h       |         1         | Enable the HAL SAI module
USE_HAL_SAI_REGISTER_CALLBACKS | hal_conf.h       |         0         | Allow user to define his own callback
USE_HAL_SAI_CLK_ENABLE_MODEL   | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_SAI_USER_DATA          | hal_conf.h       |         0         | Add an user data inside HAL SAI handle
USE_HAL_SAI_GET_LAST_ERRORS    | hal_conf.h       |         0         | Enable retrieving last processes error codes
USE_HAL_SAI_DMA                | hal_conf.h       |         1         | Enable DMA code inside HAL SAI
USE_HAL_CHECK_PARAM            | hal_conf.h       |         0         | Enable checking of vital parameters at runtime
USE_HAL_MUTEX                  | hal_conf.h       |         0         | Enable the use of semaphore in the HAL driver
USE_HAL_CHECK_PROCESS_STATE    | hal_conf.h       |         0         | Enable atomic access to process state check
USE_ASSERT_DBG_PARAM           | PreProcessor env |        NONE       | Enable check parameters for HAL
USE_ASSERT_DBG_STATE           | PreProcessor env |        NONE       | Enable check state for HAL
  */

#if defined(USE_HAL_SAI_MODULE) && (USE_HAL_SAI_MODULE == 1)

/* Private types -------------------------------------------------------------*/
/** @defgroup SAI_Private_Types SAI Private Types
  * @{
  */

/**
  * @brief SAI mode definitions.
  */
typedef enum
{
  SAI_MODE_DMA, /*!< DMA mode */
  SAI_MODE_IT   /*!< Interrupt mode */
} sai_mode_t;

/**
  * @brief SAI FIFO status definitions.
  */
typedef enum
{
  SAI_FIFO_STATUS_EMPTY         =  0U,                               /*!< FIFO empty (transmitter and
                                                                          receiver modes) */
  SAI_FIFO_STATUS_LESS_1_4_FULL =  SAI_xSR_FLVL_0,                   /*!< FIFO lower or equal to quarter
                                                                          but not empty (transmitter mode),
                                                                          FIFO lower than quarter but not empty
                                                                          (receiver mode) */
  SAI_FIFO_STATUS_1_4_FULL      =  SAI_xSR_FLVL_1,                   /*!< quarter lower than FIFO lower or
                                                                          equal to half (transmitter mode),
                                                                          quarter lower or equal to FIFO
                                                                          lower than half (receiver mode) */
  SAI_FIFO_STATUS_1_2_FULL      = (SAI_xSR_FLVL_1 | SAI_xSR_FLVL_0), /*!< half lower than FIFO lower or equal to
                                                                          three-quarter (transmitter mode),
                                                                          half lower or equal to FIFO lower than
                                                                          three-quarter (receiver mode) */
  SAI_FIFO_STATUS_3_4_FULL      =  SAI_xSR_FLVL_2,                   /*!< three-quarter lower than FIFO
                                                                          but not full (transmitter mode),
                                                                          three-quarter lower or equal to FIFO
                                                                          but not full
                                                                          (receiver mode) */
  SAI_FIFO_STATUS_FULL          = (SAI_xSR_FLVL_2 | SAI_xSR_FLVL_0)  /*!< FIFO full (transmitter and
                                                                              receiver modes) */
} sai_fifo_status_t;
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup SAI_Private_Constants SAI Private Constants
  * @{
  */
#define SAI_DEFAULT_TIMEOUT        4U    /*!< SAI default timeout */
#define SAI_LONG_TIMEOUT           1000U /*!< SAI long timeout */
#define SAI_SPDIF_FRAME_LENGTH     64U   /*!< SAI SPDIF frame length */
#define SAI_AC97_FRAME_LENGTH      256U  /*!< SAI AC97 frame length */
#define SAI_PDM_DELAY_MASK         0x77U /*!< SAI PDM delay mask */
#define SAI_PDM_DELAY_OFFSET       8U    /*!< SAI PDM delay offset */
#define SAI_PDM_RIGHT_DELAY_OFFSET 4U    /*!< SAI PDM right delay offset */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SAI_Private_Macros SAI Private Macros
  * @{
  */

/**
  * @brief Synchronization output
  */
#if defined(SAI2)
#define IS_SAI_SYNC_OUTPUT(output) (((output) == HAL_SAI_SYNC_OUTPUT_DISABLE) \
                                    || ((output) == HAL_SAI_SYNC_OUTPUT_BLOCK_A_ENABLE) \
                                    || ((output) == HAL_SAI_SYNC_OUTPUT_BLOCK_B_ENABLE))
#endif /* SAI2 */

/**
  * @brief Audio frequency
  */
#define IS_SAI_AUDIO_FREQUENCY(frequency) (((frequency) == HAL_SAI_AUDIO_FREQUENCY_MCLK_DIV) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_8KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_11KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_16KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_22KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_32KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_44KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_48KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_96KHZ) \
                                           || ((frequency) == HAL_SAI_AUDIO_FREQUENCY_192KHZ))

/**
  * @brief Master clock oversampling
  */
#define IS_SAI_MCLK_OVERSAMPLING(value) (((value) == HAL_SAI_MCLK_OVERSAMPLING_DISABLE) \
                                         || ((value) == HAL_SAI_MCLK_OVERSAMPLING_ENABLE))

/**
  * @brief PDM clock
  */
#define IS_SAI_PDM_CLOCK(clock) (((clock) == HAL_SAI_PDM_CLOCK1_CLOCK2_DISABLE) \
                                 || ((clock) == HAL_SAI_PDM_CLOCK1_ENABLE) \
                                 || ((clock) == HAL_SAI_PDM_CLOCK2_ENABLE) \
                                 || ((clock) == HAL_SAI_PDM_CLOCK1_CLOCK2_ENABLE))

/**
  * @brief Mode
  */
#define IS_SAI_MODE(mode)  (((mode) == HAL_SAI_MODE_MASTER_TX) \
                            || ((mode) == HAL_SAI_MODE_MASTER_RX) \
                            || ((mode) == HAL_SAI_MODE_SLAVE_TX) \
                            || ((mode) == HAL_SAI_MODE_SLAVE_RX))

/**
  * @brief Protocol
  */
#define IS_SAI_PROTOCOL(protocol) (((protocol) == HAL_SAI_PROTOCOL_FREE) \
                                   || ((protocol) == HAL_SAI_PROTOCOL_SPDIF) \
                                   || ((protocol) == HAL_SAI_PROTOCOL_AC97))

/**
  * @brief Data size
  */
#define IS_SAI_DATA_SIZE(size) (((size) == HAL_SAI_DATA_SIZE_8BITS ) \
                                || ((size) == HAL_SAI_DATA_SIZE_10BITS) \
                                || ((size) == HAL_SAI_DATA_SIZE_16BITS) \
                                || ((size) == HAL_SAI_DATA_SIZE_20BITS) \
                                || ((size) == HAL_SAI_DATA_SIZE_24BITS) \
                                || ((size) == HAL_SAI_DATA_SIZE_32BITS))

/**
  * @brief Bit order
  */
#define IS_SAI_BIT_ORDER(order) (((order) == HAL_SAI_BIT_ORDER_MSB) || ((order) == HAL_SAI_BIT_ORDER_LSB))

/**
  * @brief Clock strobing edge
  */
#define IS_SAI_CLOCK_STROBING_EDGE(edge) (((edge) == HAL_SAI_CLOCK_STROBING_FALLING_EDGE) \
                                          || ((edge) == HAL_SAI_CLOCK_STROBING_RISING_EDGE))

/**
  * @brief Synchronization
  */
#if defined(SAI2)
#define IS_SAI_SYNC(sync) (((sync) == HAL_SAI_SYNC_NO) \
                           || ((sync) == HAL_SAI_SYNC_INTERNAL) \
                           || ((sync) == HAL_SAI_SYNC_EXTERNAL))
#else
#define IS_SAI_SYNC(sync) (((sync) == HAL_SAI_SYNC_NO) \
                           || ((sync) == HAL_SAI_SYNC_INTERNAL))
#endif /* SAI2 */

/**
  * @brief Master divider
  */
#define IS_SAI_MASTER_DIVIDER(value) (((value) == HAL_SAI_MASTER_DIVIDER_ENABLE) \
                                      || ((value) == HAL_SAI_MASTER_DIVIDER_DISABLE))

/**
  * @brief Frame length
  */
#define IS_SAI_FRAME_LENGTH(length) ((8U <= (length)) && ((length) <= 256U))

/**
  * @brief Active frame length
  */
#define IS_SAI_ACTIVE_FRAME_LENGTH(length) ((1U <= (length)) && ((length) <= 128U))

/**
  * @brief Frame synchronization definition
  */
#define IS_SAI_FS_DEFINITION(definition) (((definition) == HAL_SAI_FS_START_FRAME) \
                                          || ((definition) == HAL_SAI_FS_CHANNEL_IDENTIFICATION))

/**
  * @brief Frame synchronization polarity
  */
#define IS_SAI_FS_POLARITY(polarity) (((polarity) == HAL_SAI_FS_POLARITY_FALLING) \
                                      || ((polarity) == HAL_SAI_FS_POLARITY_RISING))

/**
  * @brief Frame synchronization offset
  */
#define IS_SAI_FS_OFFSET(offset) (((offset) == HAL_SAI_FS_FIRST_BIT) \
                                  || ((offset) == HAL_SAI_FS_BEFORE_FIRST_BIT))

/**
  * @brief Slot first bit offset
  */
#define IS_SAI_SLOT_FIRST_BIT_OFFSET(value) ((value) <= 24U)

/**
  * @brief Slot size
  */
#define IS_SAI_SLOT_SIZE(size) (((size) == HAL_SAI_SLOT_SIZE_DATA_SIZE) \
                                || ((size) == HAL_SAI_SLOT_SIZE_16BITS) \
                                || ((size) == HAL_SAI_SLOT_SIZE_32BITS))

/**
  * @brief Slot number
  */
#define IS_SAI_SLOT_NUMBER(number) ((1U <= (number)) && ((number) <= 16U))

/**
  * @brief Slot active
  */
#define IS_SAI_SLOT_ACTIVE(value)  ((value) <= HAL_SAI_SLOT_ACTIVE_ALL)

/**
  * @brief FIFO threshold
  */
#define IS_SAI_FIFO_THRESHOLD(threshold) (((threshold) == HAL_SAI_FIFO_THRESHOLD_EMPTY) \
                                          || ((threshold) == HAL_SAI_FIFO_THRESHOLD_1_4) \
                                          || ((threshold) == HAL_SAI_FIFO_THRESHOLD_1_2) \
                                          || ((threshold) == HAL_SAI_FIFO_THRESHOLD_3_4) \
                                          || ((threshold) == HAL_SAI_FIFO_THRESHOLD_FULL))

/**
  * @brief Companding
  */
#define IS_SAI_COMPANDING(value)    (((value) == HAL_SAI_COMPANDING_NO) \
                                     || ((value) == HAL_SAI_COMPANDING_ULAW_1CPL) \
                                     || ((value) == HAL_SAI_COMPANDING_ALAW_1CPL) \
                                     || ((value) == HAL_SAI_COMPANDING_ULAW_2CPL) \
                                     || ((value) == HAL_SAI_COMPANDING_ALAW_2CPL))

/**
  * @brief Mute mode
  */
#define IS_SAI_MUTE_MODE(mode)    (((mode) == HAL_SAI_MUTE_MODE_ZERO_VALUE) \
                                   || ((mode) == HAL_SAI_MUTE_MODE_LAST_VALUE))

/**
  * @brief Mute counter
  */
#define IS_SAI_MUTE_COUNTER(counter) ((counter) <= 63U)

/**
  * @brief Master clock divider
  */
#define IS_SAI_MCLK_DIVIDER(value) ((value) <= 63U)

/**
  * @brief PDM micro pairs number
  */
#define IS_SAI_PDM_MIC_PAIRS_NUMBER(value)   ((1U <= (value)) && ((value) <= 3U))

/**
  * @brief PDM micro delay
  */
#define IS_SAI_PDM_MIC_DELAY(value)   ((value) <= 7U)

/**
  * @brief Block
  */
#define SAI_BLOCK(hsai)   ((SAI_Block_TypeDef *)((uint32_t)(hsai)->block))

/**
  * @brief Instance
  */
#if defined(SAI2)
#define SAI_GET_INSTANCE(hsai) ((((hsai->block) == HAL_SAI1_BLOCK_A) \
                                 || ((hsai->block) == HAL_SAI1_BLOCK_B)) ? (SAI1) : (SAI2))
#else
#define SAI_GET_INSTANCE(hsai) SAI1
#endif /* SAI2 */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SAI_Private_Functions SAI Private Functions
  * @{
  */
static void SAI_FillFifo(hal_sai_handle_t *hsai);
static uint32_t SAI_InterruptFlag(const hal_sai_handle_t *hsai, sai_mode_t mode);

static hal_status_t SAI_Disable(hal_sai_handle_t *hsai);
static void SAI_StopTransfer(hal_sai_handle_t *hsai);
static void SAI_Transmit_IT8Bit(hal_sai_handle_t *hsai);
static void SAI_Transmit_IT16Bit(hal_sai_handle_t *hsai);
static void SAI_Transmit_IT32Bit(hal_sai_handle_t *hsai);
static void SAI_TransmitCplt_IT(hal_sai_handle_t *hsai);
static void SAI_Receive_IT8Bit(hal_sai_handle_t *hsai);
static void SAI_Receive_IT16Bit(hal_sai_handle_t *hsai);
static void SAI_Receive_IT32Bit(hal_sai_handle_t *hsai);
static void SAI_ReceiveCplt_IT(hal_sai_handle_t *hsai);

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
static void SAI_IRQ_DMAAbort(hal_sai_handle_t *hsai, uint32_t flag);
static void SAI_DMATxCplt(hal_dma_handle_t *hdma);
static void SAI_DMATxHalfCplt(hal_dma_handle_t *hdma);
static void SAI_DMARxCplt(hal_dma_handle_t *hdma);
static void SAI_DMARxHalfCplt(hal_dma_handle_t *hdma);
static void SAI_DMAError(hal_dma_handle_t *hdma);
static void SAI_DMAAbort(hal_dma_handle_t *hdma);
#endif /* USE_HAL_SAI_DMA */
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @addtogroup SAI_Exported_Functions
  * @{
  */

/** @addtogroup SAI_Exported_Functions_Group1
  * @{

This section provides a set of functions allowing to initialize and deinitialize the SAI peripheral:

- Call the function HAL_SAI_Init() to initialize the selected SAI handle and associate a SAI block.
- Call the function HAL_SAI_DeInit() to deinitialize the SAI.
  */

/**
  * @brief  Initialize the SAI according to the associated handle.
  * @param  hsai  Pointer to a hal_sai_handle_t.
  * @param  block SAI block.
  * @retval HAL_INVALID_PARAM When the handle is NULL.
  * @retval HAL_OK            SAI driver correctly initialized for the given SAI block.
  * @retval HAL_ERROR         SAI semaphore creation is failed (USE_HAL_MUTEX is set to 1).
  */
hal_status_t HAL_SAI_Init(hal_sai_handle_t *hsai, hal_sai_block_t block)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_ALL_INSTANCE((SAI_Block_TypeDef *)(uint32_t)block));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hsai == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsai->block = block;

#if defined(USE_HAL_SAI_CLK_ENABLE_MODEL) && (USE_HAL_SAI_CLK_ENABLE_MODEL >= HAL_CLK_ENABLE_PERIPH_ONLY)
  if ((block == HAL_SAI1_BLOCK_A) || (block == HAL_SAI1_BLOCK_B))
  {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SAI1);
  }
#if defined(SAI2)
  else /* SAI2 blocks */
  {
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SAI2);
  }
#endif /* SAI2 */
#endif /* USE_HAL_SAI_CLK_ENABLE_MODEL */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  (void)HAL_OS_SemaphoreCreate(&hsai->semaphore);
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
  hsai->hdma_tx = NULL;
  hsai->hdma_rx = NULL;
#endif /* USE_HAL_SAI_DMA */

#if defined (USE_HAL_SAI_USER_DATA) && (USE_HAL_SAI_USER_DATA == 1)
  hsai->p_user_data = (void *) NULL;
#endif /* USE_HAL_SAI_USER_DATA */

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  /* Initialize the SAI callback settings */
  hsai->p_rx_cplt_cb      = HAL_SAI_RxCpltCallback;     /* Receive complete callback */
  hsai->p_rx_half_cplt_cb = HAL_SAI_RxHalfCpltCallback; /* Receive half complete callback */
  hsai->p_tx_cplt_cb      = HAL_SAI_TxCpltCallback;     /* Transmit complete callback */
  hsai->p_tx_half_cplt_cb = HAL_SAI_TxHalfCpltCallback; /* Transmit half complete callback */
  hsai->p_mute_cb         = HAL_SAI_MuteCallback;       /* Mute callback */
  hsai->p_abort_cplt_cb   = HAL_SAI_AbortCpltCallback;  /* Abort complete callback */
  hsai->p_error_cb        = HAL_SAI_ErrorCallback;      /* Error callback */
#endif  /* USE_HAL_SAI_REGISTER_CALLBACKS */

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

  hsai->global_state = HAL_SAI_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the SAI.
  * @param  hsai Pointer to a hal_sai_handle_t.
  */
void HAL_SAI_DeInit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_ALL_INSTANCE((SAI_Block_TypeDef *)(uint32_t)hsai->block));

  p_sai_block = SAI_BLOCK(hsai);

  (void)SAI_Disable(hsai);

  HAL_SAI_DisableIT(p_sai_block, HAL_SAI_IT_OVRUDR | HAL_SAI_IT_MUTEDET | HAL_SAI_IT_WCKCFG | HAL_SAI_IT_FREQ
                    | HAL_SAI_IT_CNRDY | HAL_SAI_IT_AFSDET | HAL_SAI_IT_LFSDET);

  HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG | HAL_SAI_FLAG_FREQ
                    | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

  /* Flush the FIFO */
  SET_BIT(p_sai_block->CR2, SAI_xCR2_FFLUSH);

  /* Disable SAI PDM interface */
  if (hsai->block == HAL_SAI1_BLOCK_A)
  {
    /* Reset PDM delays */
    CLEAR_REG(SAI1->PDMDLY);

    /* Disable PDM interface */
    CLEAR_BIT(SAI1->PDMCR, SAI_PDMCR_PDMEN);
  }

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  (void)HAL_OS_SemaphoreDelete(&hsai->semaphore);
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_SAI_USER_DATA) && (USE_HAL_SAI_USER_DATA == 1)
  hsai->p_user_data = NULL;
#endif /* USE_HAL_SAI_USER_DATA */

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

  hsai->global_state = HAL_SAI_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup SAI_Exported_Functions_Group2
  * @{

This section provides a set of functions allowing to configure the SAI driver:

- Call the function HAL_SAI_SetConfig() to set the different fields needed before starting the SAI driver.
- Call the function HAL_SAI_GetConfig() to retrieve the configuration.
- Call the function HAL_SAI_SetSync() to set the synchronization.
- Call the function HAL_SAI_GetSync() to retrieve the synchronization.
- Call the function HAL_SAI_SetSyncOutput() to set the synchronization output.
- Call the function HAL_SAI_GetSyncOutput() to retrieve the synchronization output.
- Call the function HAL_SAI_SetFifoThreshold() to set the FIFO threshold.
- Call the function HAL_SAI_GetFifoThreshold() to retrieve the FIFO threshold.
- Call the function HAL_SAI_SetCompanding() to set the companding.
- Call the function HAL_SAI_GetCompanding() to retrieve the companding.
- Call the function HAL_SAI_SetPdmMicDelay() to set the PDM micro delay.
- Call the function HAL_SAI_GetPdmMicDelay() to retrieve the PDM micro delay.
- Call the function HAL_SAI_SetTxDMA() to set the DMA channel for transmission.
- Call the function HAL_SAI_SetRxDMA() to set the DMA channel for reception.
- Call the function HAL_SAI_SetAudioFrequency() to set the audio frequency.
- Call the function HAL_SAI_GetAudioFrequency() to retrieve the audio frequency.
- Call the function HAL_SAI_GetRealAudioFrequency() to retrieve the real audio frequency.
- Call the function HAL_SAI_SetDataSize() to set the data size.
- Call the function HAL_SAI_GetDataSize() to retrieve the data size.
- Call the function HAL_SAI_SetSlotActive() to set the slot active.
- Call the function HAL_SAI_GetSlotActive() to retrieve the slot active.
  */

/**
  * @brief  Configure the SAI driver.
  * @param  hsai     Pointer to a hal_sai_handle_t.
  * @param  p_config Pointer on @ref hal_sai_config_t structure.
  * @retval HAL_OK            SAI block has been correctly configured.
  * @retval HAL_INVALID_PARAM When the p_config pointer is NULL.
  */
hal_status_t HAL_SAI_SetConfig(hal_sai_handle_t *hsai, const hal_sai_config_t *p_config)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_clock_strobing_edge_t clock_strobing_edge;
  uint32_t mclk_div;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_SAI_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_SAI_MASTER_DIVIDER(p_config->divider));
  ASSERT_DBG_PARAM(IS_SAI_AUDIO_FREQUENCY(p_config->audio_frequency));
  ASSERT_DBG_PARAM(IS_SAI_MCLK_OVERSAMPLING(p_config->mclk_oversampling));
  ASSERT_DBG_PARAM(IS_SAI_PROTOCOL(p_config->protocol));
  ASSERT_DBG_PARAM(IS_SAI_DATA_SIZE(p_config->data_size));
  ASSERT_DBG_PARAM(IS_SAI_BIT_ORDER(p_config->bit_order));
  ASSERT_DBG_PARAM(IS_SAI_CLOCK_STROBING_EDGE(p_config->clock_strobing_edge));
  ASSERT_DBG_PARAM(IS_SAI_FRAME_LENGTH(p_config->frame.frame_length));
  ASSERT_DBG_PARAM(IS_SAI_ACTIVE_FRAME_LENGTH(p_config->frame.active_frame_length));
  ASSERT_DBG_PARAM(IS_SAI_FS_DEFINITION(p_config->frame.fs_definition));
  ASSERT_DBG_PARAM(IS_SAI_FS_POLARITY(p_config->frame.fs_polarity));
  ASSERT_DBG_PARAM(IS_SAI_FS_OFFSET(p_config->frame.fs_offset));
  ASSERT_DBG_PARAM(IS_SAI_SLOT_FIRST_BIT_OFFSET(p_config->slot.slot_first_bit_offset));
  ASSERT_DBG_PARAM(IS_SAI_SLOT_SIZE(p_config->slot.slot_size));
  ASSERT_DBG_PARAM(IS_SAI_SLOT_NUMBER(p_config->slot.slot_number));
  ASSERT_DBG_PARAM(IS_SAI_SLOT_ACTIVE(p_config->slot.slot_active));

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);

  clock_strobing_edge = p_config->clock_strobing_edge;
  mclk_div = p_config->mclk_div;

  if ((p_config->audio_frequency) != HAL_SAI_AUDIO_FREQUENCY_MCLK_DIV)
  {
    uint32_t clock_freq;
    uint32_t fs_freq;

    /* In this case, the mclk_div value is calculated to get audio frequency */
#if defined(SAI2)
    if ((hsai->block == HAL_SAI1_BLOCK_A) || (hsai->block == HAL_SAI1_BLOCK_B))
    {
      clock_freq = HAL_RCC_SAI1_GetKernelClkFreq();
    }
    else
    {
      clock_freq = HAL_RCC_SAI2_GetKernelClkFreq();
    }
#else
    clock_freq = HAL_RCC_SAI1_GetKernelClkFreq();
#endif /* SAI2 */

    /* Configure Master Clock Divider (mclk_div) using the following formula :
       - If NODIV = 1 :
         MCKDIV[5:0] = SAI_CK_x / (FS * (FRL + 1))
       - If NODIV = 0 :
         MCKDIV[5:0] = SAI_CK_x / (FS * (OSR + 1) * 256) */
    if (p_config->divider == HAL_SAI_MASTER_DIVIDER_DISABLE)
    {
      /* NODIV = 1 */
      uint32_t frame_length;
      if (p_config->protocol == HAL_SAI_PROTOCOL_SPDIF)
      {
        /* For SPDIF protocol, frame length is set by hardware to 64 */
        frame_length = SAI_SPDIF_FRAME_LENGTH;
      }
      else if (p_config->protocol == HAL_SAI_PROTOCOL_AC97)
      {
        /* For AC97 protocol, frame length is set by hardware to 256 */
        frame_length = SAI_AC97_FRAME_LENGTH;
      }
      else
      {
        /* For free protocol, frame length is set by user */
        frame_length = p_config->frame.frame_length;
      }

      /* (clock_freq x 10) to keep significant digits */
      fs_freq = (clock_freq * 10U) / ((uint32_t)p_config->audio_frequency * frame_length);
    }
    else
    {
      /* NODIV = 0 */
      uint32_t mclk_oversampling;

      if (p_config->mclk_oversampling == HAL_SAI_MCLK_OVERSAMPLING_ENABLE)
      {
        mclk_oversampling = 2U;
      }
      else
      {
        mclk_oversampling = 1U;
      }
      /* (clock_freq x 10) to keep significant digits */
      fs_freq = (clock_freq * 10U) / ((uint32_t)p_config->audio_frequency * mclk_oversampling * 256U);
    }
    mclk_div = fs_freq / 10U;

    /* Round result to the nearest integer */
    if ((fs_freq % 10U) > 8U)
    {
      mclk_div += 1U;
    }

    /* For SPDIF protocol, SAI must provide a bit clock twice faster than the symbol-rate */
    if (p_config->protocol == HAL_SAI_PROTOCOL_SPDIF)
    {
      mclk_div = mclk_div >> 1;
    }
  }

  ASSERT_DBG_PARAM(IS_SAI_MCLK_DIVIDER(mclk_div));

  /* Compute CKSTR bits of SAI CR1 according the clock strobing edge and audio mode */
  if ((p_config->mode == HAL_SAI_MODE_MASTER_TX) || (p_config->mode == HAL_SAI_MODE_SLAVE_TX))
  {
    /* Transmit */
    if (p_config->clock_strobing_edge == HAL_SAI_CLOCK_STROBING_RISING_EDGE)
    {
      clock_strobing_edge = HAL_SAI_CLOCK_STROBING_FALLING_EDGE;
    }
    else
    {
      /* Receive */
      clock_strobing_edge = HAL_SAI_CLOCK_STROBING_RISING_EDGE;
    }
  }

  /* SAI Block Configuration -------------------------------------------------*/
  /* SAI CR1 Configuration */
  MODIFY_REG(p_sai_block->CR1, SAI_xCR1_MODE | SAI_xCR1_PRTCFG |  SAI_xCR1_DS | SAI_xCR1_LSBFIRST | SAI_xCR1_CKSTR
             | SAI_xCR1_NODIV | SAI_xCR1_MCKDIV | SAI_xCR1_OSR, (uint32_t)p_config->mode | (uint32_t)p_config->protocol
             | (uint32_t)p_config->data_size | (uint32_t)p_config->bit_order | (uint32_t)clock_strobing_edge
             | (uint32_t)p_config->divider | (mclk_div << SAI_xCR1_MCKDIV_Pos)
             | (uint32_t)p_config->mclk_oversampling);

  /* SAI Frame Configuration -----------------------------------------*/
  MODIFY_REG(p_sai_block->FRCR, SAI_xFRCR_FRL | SAI_xFRCR_FSALL | SAI_xFRCR_FSDEF | SAI_xFRCR_FSPOL | SAI_xFRCR_FSOFF,
             (p_config->frame.frame_length - 1U) | ((p_config->frame.active_frame_length - 1U) << SAI_xFRCR_FSALL_Pos)
             | (uint32_t)p_config->frame.fs_definition
             | (uint32_t)p_config->frame.fs_polarity | (uint32_t)p_config->frame.fs_offset);

  /* SAI Block_x SLOT Configuration ------------------------------------------*/
  /* This register has no meaning in AC 97 and SPDIF audio protocol */
  MODIFY_REG(p_sai_block->SLOTR, SAI_xSLOTR_FBOFF | SAI_xSLOTR_SLOTSZ | SAI_xSLOTR_NBSLOT | SAI_xSLOTR_SLOTEN,
             p_config->slot.slot_first_bit_offset | (uint32_t)p_config->slot.slot_size
             | ((p_config->slot.slot_number - 1U) << SAI_xSLOTR_NBSLOT_Pos)
             | (p_config->slot.slot_active << SAI_xSLOTR_SLOTEN_Pos));

  hsai->global_state = HAL_SAI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the configuration.
  * @param  hsai     Pointer to a hal_sai_handle_t.
  * @param  p_config Pointer on @ref hal_sai_config_t structure.
  */
void HAL_SAI_GetConfig(const hal_sai_handle_t *hsai, hal_sai_config_t *p_config)
{
  const SAI_Block_TypeDef *p_sai_block;
  uint32_t cr1_config;
  uint32_t frame_config;
  uint32_t slot_config;
  hal_sai_clock_strobing_edge_t clock_strobing_edge;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  p_sai_block = SAI_BLOCK(hsai);

  cr1_config = READ_REG(p_sai_block->CR1);
  frame_config = READ_REG(p_sai_block->FRCR);
  slot_config = READ_REG(p_sai_block->SLOTR);
  clock_strobing_edge = (hal_sai_clock_strobing_edge_t)(uint32_t)(cr1_config & SAI_xCR1_CKSTR);

  p_config->mode = (hal_sai_mode_t)(uint32_t)(cr1_config & SAI_xCR1_MODE);
  p_config->divider = (hal_sai_master_divider_t)(uint32_t)(cr1_config & SAI_xCR1_NODIV);
  p_config->audio_frequency = HAL_SAI_GetAudioFrequency(hsai);
  p_config->mclk_div = ((cr1_config & SAI_xCR1_MCKDIV) >> SAI_xCR1_MCKDIV_Pos);
  p_config->mclk_oversampling = (hal_sai_mclk_oversampling_t)(uint32_t)(cr1_config & SAI_xCR1_OSR);
  p_config->protocol = (hal_sai_protocol_t)(uint32_t)(cr1_config & SAI_xCR1_PRTCFG);
  p_config->data_size = (hal_sai_data_size_t)(uint32_t)(cr1_config & SAI_xCR1_DS);
  p_config->bit_order = (hal_sai_bit_order_t)(uint32_t)(cr1_config & SAI_xCR1_LSBFIRST);

  if ((p_config->mode == HAL_SAI_MODE_MASTER_TX) || (p_config->mode == HAL_SAI_MODE_SLAVE_TX))
  {
    /* Transmit */
    if (clock_strobing_edge == HAL_SAI_CLOCK_STROBING_RISING_EDGE)
    {
      p_config->clock_strobing_edge = HAL_SAI_CLOCK_STROBING_FALLING_EDGE;
    }
    else
    {
      /* Receive */
      p_config->clock_strobing_edge = HAL_SAI_CLOCK_STROBING_RISING_EDGE;
    }
  }

  p_config->frame.frame_length = ((frame_config & SAI_xFRCR_FRL) + 1U);
  p_config->frame.active_frame_length = (((frame_config & SAI_xFRCR_FSALL) >> SAI_xFRCR_FSALL_Pos) + 1U);
  p_config->frame.fs_definition = (hal_sai_fs_definition_t)(uint32_t)(frame_config & SAI_xFRCR_FSDEF);
  p_config->frame.fs_polarity = (hal_sai_fs_polarity_t)(uint32_t)(frame_config & SAI_xFRCR_FSPOL);
  p_config->frame.fs_offset = (hal_sai_fs_offset_t)(uint32_t)(frame_config & SAI_xFRCR_FSOFF);

  p_config->slot.slot_first_bit_offset = (slot_config & SAI_xSLOTR_FBOFF);
  p_config->slot.slot_size = (hal_sai_slot_size_t)(uint32_t)(slot_config & SAI_xSLOTR_SLOTSZ);
  p_config->slot.slot_number = (((slot_config & SAI_xSLOTR_NBSLOT) >> SAI_xSLOTR_NBSLOT_Pos) + 1U);
  p_config->slot.slot_active = ((slot_config & SAI_xSLOTR_SLOTEN) >> SAI_xSLOTR_SLOTEN_Pos);
}

/**
  * @brief  Set the synchronization.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @param  sync Synchronization.
  * @retval HAL_OK    SAI synchronization has been correctly configured.
  */
hal_status_t HAL_SAI_SetSync(hal_sai_handle_t *hsai, hal_sai_sync_t sync)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_SYNC(sync));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  MODIFY_REG(SAI_BLOCK(hsai)->CR1, SAI_xCR1_SYNCEN, (uint32_t)sync);

#if defined(SAI2)
  if (((hsai->block == HAL_SAI1_BLOCK_A) || (hsai->block == HAL_SAI1_BLOCK_B)) && (sync == HAL_SAI_SYNC_EXTERNAL))
  {
    SET_BIT(SAI1->GCR, SAI_GCR_SYNCIN_0);
  }
  else
  {
    CLEAR_BIT(SAI1->GCR, SAI_GCR_SYNCIN_0);
  }
#endif /* SAI2 */

  return HAL_OK;
}

/**
  * @brief  Get the synchronization.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_sync_t SAI synchronization.
  */
hal_sai_sync_t HAL_SAI_GetSync(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  return (hal_sai_sync_t)(uint32_t)(READ_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_SYNCEN));
}

#if defined(SAI2)
/**
  * @brief  Set the synchronization output.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  sync_output Synchronization output.
  * @retval HAL_OK    SAI synchronization output has been correctly configured.
  */
hal_status_t HAL_SAI_SetSyncOutput(hal_sai_handle_t *hsai, hal_sai_sync_output_t sync_output)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_SYNC_OUTPUT(sync_output));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  MODIFY_REG(SAI_GET_INSTANCE(hsai)->GCR, SAI_GCR_SYNCOUT, (uint32_t)sync_output);

  return HAL_OK;
}

/**
  * @brief  Get the synchronization output.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_sync_output_t SAI synchronization output.
  */
hal_sai_sync_output_t HAL_SAI_GetSyncOutput(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  return (hal_sai_sync_output_t)(uint32_t)READ_BIT(SAI_GET_INSTANCE(hsai)->GCR, SAI_GCR_SYNCOUT);
}
#endif /* SAI2 */

/**
  * @brief  Set the FIFO threshold.
  * @param  hsai           Pointer to a hal_sai_handle_t.
  * @param  fifo_threshold FIFO threshold.
  * @retval HAL_OK SAI FIFO threshold has been correctly configured.
  */
hal_status_t HAL_SAI_SetFifoThreshold(hal_sai_handle_t *hsai, hal_sai_fifo_threshold_t fifo_threshold)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_FIFO_THRESHOLD(fifo_threshold));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  MODIFY_REG(SAI_BLOCK(hsai)->CR2, SAI_xCR2_FTH, (uint32_t)fifo_threshold);

  return HAL_OK;
}

/**
  * @brief  Get the FIFO threshold.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_fifo_threshold_t SAI FIFO threshold.
  */
hal_sai_fifo_threshold_t HAL_SAI_GetFifoThreshold(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  return (hal_sai_fifo_threshold_t)(uint32_t)(READ_BIT(SAI_BLOCK(hsai)->CR2, SAI_xCR2_FTH));
}

/**
  * @brief   Set the companding.
  * @param   hsai       Pointer to a hal_sai_handle_t.
  * @param   companding Companding mode.
  * @warning Companding mode is applicable only when free protocol mode is selected.
  * @retval  HAL_OK    SAI companding mode has been correctly configured.
  */
hal_status_t HAL_SAI_SetCompanding(hal_sai_handle_t *hsai, hal_sai_companding_t companding)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_COMPANDING(companding));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  MODIFY_REG(SAI_BLOCK(hsai)->CR2, SAI_xCR2_COMP | SAI_xCR2_CPL, (uint32_t)companding);

  return HAL_OK;
}

/**
  * @brief  Get the companding.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_companding_t SAI companding mode.
  */
hal_sai_companding_t HAL_SAI_GetCompanding(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  return (hal_sai_companding_t)(uint32_t)(READ_BIT(SAI_BLOCK(hsai)->CR2, SAI_xCR2_COMP | SAI_xCR2_CPL));
}

/**
  * @brief  Configure the PDM micro delay.
  * @param  hsai            Pointer to a hal_sai_handle_t.
  * @param  p_pdm_mic_delay Pointer on @ref hal_sai_pdm_mic_delay_t structure.
  * @retval HAL_OK            SAI PDM micro delay has been correctly configured.
  * @retval HAL_ERROR         SAI PDM micro delay cannot be configured.
  * @retval HAL_INVALID_PARAM When the p_pdm_mic_delay pointer is NULL.
  */
hal_status_t HAL_SAI_SetPdmMicDelay(const hal_sai_handle_t *hsai, const hal_sai_pdm_mic_delay_t *p_pdm_mic_delay)
{
  hal_status_t status = HAL_OK;
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hsai->block == HAL_SAI1_BLOCK_A);
  ASSERT_DBG_PARAM(p_pdm_mic_delay != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_pdm_mic_delay == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_SAI_PDM_MIC_PAIRS_NUMBER(p_pdm_mic_delay->pdm_mic_pairs_nbr));
  ASSERT_DBG_PARAM(IS_SAI_PDM_MIC_DELAY(p_pdm_mic_delay->pdm_left_delay));
  ASSERT_DBG_PARAM(IS_SAI_PDM_MIC_DELAY(p_pdm_mic_delay->pdm_right_delay));

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_RX_PAUSED);

  if (hsai->block == HAL_SAI1_BLOCK_A)
  {
    uint32_t offset;

    /* Compute offset on PDMDLY register according mic pair number */
    offset = SAI_PDM_DELAY_OFFSET * (p_pdm_mic_delay->pdm_mic_pairs_nbr - 1U);

    /* Reset current delays for specified microphone and apply new microphone delays */
    MODIFY_REG(SAI1->PDMDLY, (SAI_PDM_DELAY_MASK << offset),
               (((p_pdm_mic_delay->pdm_right_delay << SAI_PDM_RIGHT_DELAY_OFFSET)
                 | p_pdm_mic_delay->pdm_left_delay) << offset));
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Get the PDM micro delay.
  * @param  hsai            Pointer to a hal_sai_handle_t.
  * @param  p_pdm_mic_delay Pointer on @ref hal_sai_pdm_mic_delay_t structure.
  * @note   pdm_mic_pairs_nbr must be filled before calling this function.
  */
void HAL_SAI_GetPdmMicDelay(const hal_sai_handle_t *hsai, hal_sai_pdm_mic_delay_t *p_pdm_mic_delay)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hsai->block == HAL_SAI1_BLOCK_A);
  ASSERT_DBG_PARAM(p_pdm_mic_delay != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  if (hsai->block == HAL_SAI1_BLOCK_A)
  {
    uint32_t pdm_delay_config;
    uint32_t offset;

    pdm_delay_config = READ_REG(SAI1->PDMDLY);

    /* Compute offset on PDMDLY register according mic pair number */
    offset = SAI_PDM_DELAY_OFFSET * (p_pdm_mic_delay->pdm_mic_pairs_nbr - 1U);

    p_pdm_mic_delay->pdm_left_delay = ((pdm_delay_config >> offset) & SAI_PDMDLY_DLYM1L);
    p_pdm_mic_delay->pdm_right_delay = (((pdm_delay_config >> offset) & SAI_PDMDLY_DLYM1R) >> SAI_PDMDLY_DLYM1R_Pos);
  }
}

#if defined (USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
/**
  * @brief  Set DMA channel for transmission.
  * @param  hsai    Pointer to a hal_sai_handle_t.
  * @param  hdma_tx Pointer to a hal_dma_handle_t structure which contains the DMA instance.
  * @retval HAL_OK            The channel has been correctly set.
  * @retval HAL_INVALID_PARAM hdma_tx is NULL.
  */
hal_status_t HAL_SAI_SetTxDMA(hal_sai_handle_t *hsai, hal_dma_handle_t *hdma_tx)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hdma_tx != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma_tx == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsai->hdma_tx = hdma_tx;
  hdma_tx->p_parent = hsai;

  return HAL_OK;
}

/**
  * @brief  Set DMA channel for reception.
  * @param  hsai    Pointer to a hal_sai_handle_t.
  * @param  hdma_rx Pointer to a hal_dma_handle_t structure which contains the DMA instance.
  * @retval HAL_OK            The channel has been correctly set.
  * @retval HAL_INVALID_PARAM hdma_rx is NULL.
  */
hal_status_t HAL_SAI_SetRxDMA(hal_sai_handle_t *hsai, hal_dma_handle_t *hdma_rx)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hdma_rx != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma_rx == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hsai->hdma_rx = hdma_rx;
  hdma_rx->p_parent = hsai;

  return HAL_OK;
}
#endif /* USE_HAL_SAI_DMA */

/**
  * @brief  Set the audio frequency.
  * @param  hsai            Pointer to a hal_sai_handle_t.
  * @param  audio_frequency Audio frequency.
  * @retval HAL_OK SAI audio frequency has been correctly configured.
  */
hal_status_t HAL_SAI_SetAudioFrequency(hal_sai_handle_t *hsai, hal_sai_audio_frequency_t audio_frequency)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t mclk_div;
  uint32_t clock_freq;
  uint32_t fs_freq;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_AUDIO_FREQUENCY(audio_frequency));
  ASSERT_DBG_PARAM(audio_frequency != HAL_SAI_AUDIO_FREQUENCY_MCLK_DIV);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);

  clock_freq = HAL_RCC_SAI_GetKernelClkFreq(SAI_GET_INSTANCE(hsai));

  /* Configure Master Clock Divider (mclk_div) using the following formula :
     - If NODIV = 1 :
       MCKDIV[5:0] = SAI_CK_x / (FS * (FRL + 1))
     - If NODIV = 0 :
       MCKDIV[5:0] = SAI_CK_x / (FS * (OSR + 1) * 256) */
  if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_NODIV))
  {
    /* NODIV = 1 */
    uint32_t frame_length;
    if (READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG) == SAI_xCR1_PRTCFG_0)
    {
      /* For SPDIF protocol, frame length is set by hardware to 64 */
      frame_length = SAI_SPDIF_FRAME_LENGTH;
    }
    else if (READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG) == SAI_xCR1_PRTCFG_1)
    {
      /* For AC97 protocol, frame length is set by hardware to 256 */
      frame_length = SAI_AC97_FRAME_LENGTH;
    }
    else
    {
      /* For free protocol, frame length is set by user */
      frame_length = READ_BIT(p_sai_block->FRCR, SAI_xFRCR_FRL) + 1U;
    }

    /* (clock_freq x 10) to keep significant digits */
    fs_freq = (clock_freq * 10U) / ((uint32_t)audio_frequency * frame_length);
  }
  else
  {
    /* NODIV = 0 */
    uint32_t mclk_oversampling;

    if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_OSR))
    {
      mclk_oversampling = 2U;
    }
    else
    {
      mclk_oversampling = 1U;
    }
    /* (clock_freq x 10) to keep significant digits */
    fs_freq = (clock_freq * 10U) / ((uint32_t)audio_frequency * mclk_oversampling * 256U);
  }
  mclk_div = fs_freq / 10U;

  /* Round result to the nearest integer */
  if ((fs_freq % 10U) > 8U)
  {
    mclk_div += 1U;
  }

  /* For SPDIF protocol, SAI must provide a bit clock twice faster than the symbol-rate */
  if (READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG) == SAI_xCR1_PRTCFG_0)
  {
    mclk_div = mclk_div >> 1;
  }

  ASSERT_DBG_PARAM(IS_SAI_MCLK_DIVIDER(mclk_div));

  MODIFY_REG(p_sai_block->CR1, SAI_xCR1_MCKDIV, (mclk_div << SAI_xCR1_MCKDIV_Pos));

  return HAL_OK;
}

/**
  * @brief  Get the audio frequency.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_audio_frequency_t SAI audio frequency.
  */
hal_sai_audio_frequency_t HAL_SAI_GetAudioFrequency(const hal_sai_handle_t *hsai)
{
  uint32_t tmp_index;
  uint32_t index;
  uint32_t real_freq;
  hal_sai_audio_frequency_t audio_frequencies[9U] = {HAL_SAI_AUDIO_FREQUENCY_8KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_11KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_16KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_22KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_32KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_44KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_48KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_96KHZ,
                                                     HAL_SAI_AUDIO_FREQUENCY_192KHZ
                                                    };

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  real_freq = HAL_SAI_GetRealAudioFrequency(hsai);

  tmp_index = 0U;
  while ((real_freq > (uint32_t)audio_frequencies[tmp_index]) && (tmp_index < 8U))
  {
    tmp_index++;
  }

  if ((tmp_index == 0U) || (tmp_index == 8U))
  {
    index = tmp_index;
  }
  else
  {
    if ((real_freq - (uint32_t)audio_frequencies[tmp_index - 1U])
        > ((uint32_t)audio_frequencies[tmp_index] - real_freq))
    {
      index = tmp_index;
    }
    else
    {
      index = tmp_index - 1U;
    }
  }

  return audio_frequencies[index];
}

/**
  * @brief  Get the real audio frequency.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval uint32_t SAI real audio frequency in hertz.
  */
uint32_t HAL_SAI_GetRealAudioFrequency(const hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t mclk_div;
  uint32_t clock_freq;
  uint32_t audio_freq;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  p_sai_block = SAI_BLOCK(hsai);

  clock_freq = HAL_RCC_SAI_GetKernelClkFreq(SAI_GET_INSTANCE(hsai));

  mclk_div = (READ_BIT(p_sai_block->CR1, SAI_xCR1_MCKDIV) >> SAI_xCR1_MCKDIV_Pos);

  if (mclk_div == 0U)
  {
    mclk_div = 1U;
  }

  /* Compute audio frequency using the following formula :
     - If NODIV = 1 :
       FS = SAI_CK_x / (MCKDIV[5:0] * (FRL + 1))
     - If NODIV = 0 :
       FS = SAI_CK_x / (MCKDIV[5:0] * (OSR + 1) * 256) */
  if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_NODIV))
  {
    /* NODIV = 1 */
    uint32_t frame_length;
    if (READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG) == SAI_xCR1_PRTCFG_0)
    {
      /* For SPDIF protocol, frame length is set by hardware to 64 */
      frame_length = SAI_SPDIF_FRAME_LENGTH;
    }
    else if (READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG) == SAI_xCR1_PRTCFG_1)
    {
      /* For AC97 protocol, frame length is set by hardware to 256 */
      frame_length = SAI_AC97_FRAME_LENGTH;
    }
    else
    {
      /* For free protocol, frame length is set by user */
      frame_length = READ_BIT(p_sai_block->FRCR, SAI_xFRCR_FRL) + 1U;
    }
    audio_freq = clock_freq / (mclk_div * frame_length);
  }
  else
  {
    /* NODIV = 0 */
    uint32_t mclk_oversampling;

    if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_OSR))
    {
      mclk_oversampling = 2U;
    }
    else
    {
      mclk_oversampling = 1U;
    }
    /* (clock_freq x 10) to keep significant digits */
    audio_freq = clock_freq / (mclk_div * mclk_oversampling * 256U);
  }

  /* For SPDIF protocol, SAI must provide a bit clock twice faster than the symbol-rate */
  if (READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG) == SAI_xCR1_PRTCFG_0)
  {
    audio_freq = audio_freq >> 1U;
  }

  return audio_freq;
}

/**
  * @brief  Set the data size.
  * @param  hsai      Pointer to a hal_sai_handle_t.
  * @param  data_size Data size.
  * @retval HAL_OK SAI data size has been correctly configured.
  */
hal_status_t HAL_SAI_SetDataSize(hal_sai_handle_t *hsai, hal_sai_data_size_t data_size)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_DATA_SIZE(data_size));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  MODIFY_REG(SAI_BLOCK(hsai)->CR1, SAI_xCR1_DS, (uint32_t)data_size);

  return HAL_OK;
}

/**
  * @brief  Get the data size.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_data_size_t SAI data size.
  */
hal_sai_data_size_t HAL_SAI_GetDataSize(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  return (hal_sai_data_size_t)(uint32_t)(READ_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_DS));
}

/**
  * @brief  Set the slot active.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  slot_active Slot active.
  * @retval HAL_OK SAI slot active has been correctly configured.
  */
hal_status_t HAL_SAI_SetSlotActive(hal_sai_handle_t *hsai, uint32_t slot_active)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_SLOT_ACTIVE(slot_active));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  MODIFY_REG(SAI_BLOCK(hsai)->SLOTR, SAI_xSLOTR_SLOTEN, (slot_active << SAI_xSLOTR_SLOTEN_Pos));

  return HAL_OK;
}

/**
  * @brief  Get the slot active.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval uint32_t SAI slot active.
  *          This parameter can be a combination of @ref SAI_Block_Slot_Active.
  */
uint32_t HAL_SAI_GetSlotActive(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  return (READ_BIT(SAI_BLOCK(hsai)->SLOTR, SAI_xSLOTR_SLOTEN) >> SAI_xSLOTR_SLOTEN_Pos);
}
/**
  * @}
  */

/** @addtogroup SAI_Exported_Functions_Group3
  * @{

This section provides a set of functions allowing to enable/disable SAI features:

- Call the functions HAL_SAI_EnableMclkOutput(), HAL_SAI_DisableMclkOutput() and HAL_SAI_IsEnabledMclkOutput()
  to enable, disable the master clock output and check if it is enabled or not.
- Call the functions HAL_SAI_EnableOutputDrive(), HAL_SAI_DisableOutputDrive() and HAL_SAI_IsEnabledOutputDrive()
  to enable, disable the output drive and check if it is enabled or not.
- Call the functions HAL_SAI_EnableTristateSDOutput(), HAL_SAI_DisableTristateSDOutput() and
  HAL_SAI_IsEnabledTristateSDOutput() to enable, disable the tristate SD output and check if it is enabled or not.
- Call the functions HAL_SAI_EnableMonoMode(), HAL_SAI_DisableMonoMode() and HAL_SAI_IsEnabledMonoMode()
  to enable, disable the mono mode and check if it is enabled or not.
- Call the functions HAL_SAI_EnablePdm(), HAL_SAI_DisablePdm() and HAL_SAI_IsEnabledPdm()
  to enable, disable the PDM and check if it is enabled or not.
  */

/**
  * @brief  Enable the master clock output.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI master clock output has been correctly enabled.
  */
hal_status_t HAL_SAI_EnableMclkOutput(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  SET_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_MCKEN);

  return HAL_OK;
}

/**
  * @brief  Disable the master clock output.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI master clock output has been correctly disabled.
  */
hal_status_t HAL_SAI_DisableMclkOutput(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  CLEAR_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_MCKEN);

  return HAL_OK;
}

/**
  * @brief  Get the master clock output status.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_mclk_output_status_t SAI master clock output status.
  */
hal_sai_mclk_output_status_t HAL_SAI_IsEnabledMclkOutput(const hal_sai_handle_t *hsai)
{
  hal_sai_mclk_output_status_t mclk_output_status;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  if (IS_BIT_SET(SAI_BLOCK(hsai)->CR1, SAI_xCR1_MCKEN))
  {
    mclk_output_status = HAL_SAI_MCLK_OUTPUT_ENABLED;
  }
  else
  {
    mclk_output_status = HAL_SAI_MCLK_OUTPUT_DISABLED;
  }

  return mclk_output_status;
}

/**
  * @brief  Enable the output drive.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI output drive has been correctly enabled.
  */
hal_status_t HAL_SAI_EnableOutputDrive(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  SET_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_OUTDRIV);

  return HAL_OK;
}

/**
  * @brief  Disable the output drive.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI output drive has been correctly disabled.
  */
hal_status_t HAL_SAI_DisableOutputDrive(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  CLEAR_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_OUTDRIV);

  return HAL_OK;
}

/**
  * @brief  Get the output drive status.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_output_drive_status_t SAI output drive status.
  */
hal_sai_output_drive_status_t HAL_SAI_IsEnabledOutputDrive(const hal_sai_handle_t *hsai)
{
  hal_sai_output_drive_status_t output_drive_status;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  if (IS_BIT_SET(SAI_BLOCK(hsai)->CR1, SAI_xCR1_OUTDRIV))
  {
    output_drive_status = HAL_SAI_OUTPUT_DRIVE_ENABLED;
  }
  else
  {
    output_drive_status = HAL_SAI_OUTPUT_DRIVE_DISABLED;
  }

  return output_drive_status;
}

/**
  * @brief  Enable the tristate SD output.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI tristate SD output has been correctly enabled.
  */
hal_status_t HAL_SAI_EnableTristateSDOutput(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  SET_BIT(SAI_BLOCK(hsai)->CR2, SAI_xCR2_TRIS);

  return HAL_OK;
}

/**
  * @brief  Disable the tristate SD output.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI tristate SD output has been correctly disabled.
  */
hal_status_t HAL_SAI_DisableTristateSDOutput(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  CLEAR_BIT(SAI_BLOCK(hsai)->CR2, SAI_xCR2_TRIS);

  return HAL_OK;
}

/**
  * @brief  Get the tristate SD output status.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_tristate_sd_output_status_t SAI tristate SD output status.
  */
hal_sai_tristate_sd_output_status_t HAL_SAI_IsEnabledTristateSDOutput(const hal_sai_handle_t *hsai)
{
  hal_sai_tristate_sd_output_status_t tristate_sd_output_status;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  if (IS_BIT_SET(SAI_BLOCK(hsai)->CR2, SAI_xCR2_TRIS))
  {
    tristate_sd_output_status = HAL_SAI_TRISTATE_SD_OUTPUT_RELEASED;
  }
  else
  {
    tristate_sd_output_status = HAL_SAI_TRISTATE_SD_OUTPUT_NOT_RELEASED;
  }

  return tristate_sd_output_status;
}

/**
  * @brief  Enable the mono mode.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI mono mode has been correctly enabled.
  */
hal_status_t HAL_SAI_EnableMonoMode(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  SET_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_MONO);

  return HAL_OK;
}

/**
  * @brief  Disable the mono mode.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI mono mode has been correctly disabled.
  */
hal_status_t HAL_SAI_DisableMonoMode(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  CLEAR_BIT(SAI_BLOCK(hsai)->CR1, SAI_xCR1_MONO);

  return HAL_OK;
}

/**
  * @brief  Get the mono mode status.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_mono_mode_status_t SAI mono mode status.
  */
hal_sai_mono_mode_status_t HAL_SAI_IsEnabledMonoMode(const hal_sai_handle_t *hsai)
{
  hal_sai_mono_mode_status_t mono_mode_status;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  if (IS_BIT_SET(SAI_BLOCK(hsai)->CR1, SAI_xCR1_MONO))
  {
    mono_mode_status = HAL_SAI_MONO_MODE_ENABLED;
  }
  else
  {
    mono_mode_status = HAL_SAI_MONO_MODE_DISABLED;
  }

  return mono_mode_status;
}

/**
  * @brief  Enable the PDM.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @param  pdm_mic_pairs_nbr Number of micros pairs.
  * @param  clock PDM clock.
  * @retval HAL_OK    SAI PDM has been correctly enabled.
  * @retval HAL_ERROR SAI PDM cannot be enabled.
  */
hal_status_t HAL_SAI_EnablePdm(const hal_sai_handle_t *hsai, uint32_t pdm_mic_pairs_nbr, hal_sai_pdm_clock_t clock)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hsai->block == HAL_SAI1_BLOCK_A);
  ASSERT_DBG_PARAM(IS_SAI_PDM_MIC_PAIRS_NUMBER(pdm_mic_pairs_nbr));
  ASSERT_DBG_PARAM(IS_SAI_PDM_CLOCK(clock));

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  if (hsai->block == HAL_SAI1_BLOCK_A)
  {
    WRITE_REG(SAI1->PDMCR, ((uint32_t)clock | ((pdm_mic_pairs_nbr - 1U) << SAI_PDMCR_MICNBR_Pos)));
    SET_BIT(SAI1->PDMCR, SAI_PDMCR_PDMEN);
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Disable the PDM.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK SAI PDM has been correctly disabled.
  * @retval HAL_ERROR SAI PDM cannot be enabled.
  */
hal_status_t HAL_SAI_DisablePdm(const hal_sai_handle_t *hsai)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hsai->block == HAL_SAI1_BLOCK_A);

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  if (hsai->block == HAL_SAI1_BLOCK_A)
  {
    CLEAR_BIT(SAI1->PDMCR, SAI_PDMCR_PDMEN);
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Get the PDM status.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_pdm_status_t SAI PDM status.
  */
hal_sai_pdm_status_t HAL_SAI_IsEnabledPdm(const hal_sai_handle_t *hsai)
{
  hal_sai_pdm_status_t pdm_status;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(hsai->block == HAL_SAI1_BLOCK_A);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  pdm_status = HAL_SAI_PDM_DISABLED;

  if (hsai->block == HAL_SAI1_BLOCK_A)
  {
    if (IS_BIT_SET(SAI1->PDMCR, SAI_PDMCR_PDMEN))
    {
      pdm_status = HAL_SAI_PDM_ENABLED;
    }
  }

  return pdm_status;
}

/**
  * @}
  */

/** @addtogroup SAI_Exported_Functions_Group4
  * @{

This section provides a set of functions allowing to manage the SAI data transfers.

There are two modes of transfer:
- Blocking mode: The communication is performed in the polling mode.
  The status of all data processing is returned by the same function after finishing transfer.
  - Blocking mode functions are:
    - HAL_SAI_Transmit()
    - HAL_SAI_Receive()
    - HAL_SAI_Abort()
- Non-blocking mode: The communication is performed using interrupts or DMA.
  These functions return the status of the transfer startup. The end of the data processing is indicated through
  the dedicated SAI IRQ when using Interrupt mode or the DMA IRQ when using DMA mode.
  - Non-blocking mode functions with interrupts are:
    - HAL_SAI_Transmit_IT()
    - HAL_SAI_Receive_IT()
    - HAL_SAI_Abort_IT()
  - Non-blocking mode functions with DMA are:
    - HAL_SAI_Transmit_DMA()
    - HAL_SAI_Receive_DMA()
    - HAL_SAI_Pause_DMA()
    - HAL_SAI_Resume_DMA()

The SAI has also the mute management:
- HAL_SAI_MuteTx()
- HAL_SAI_UnmuteTx()
- HAL_SAI_EnableMuteRxDetection()
- HAL_SAI_DisableMuteRxDetection()
- HAL_SAI_IsEnabledMuteRxDetection()
  */

/**
  * @brief  Transmit an amount of samples in blocking mode.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  p_data      Pointer to data buffer.
  * @param  size_sample Amount of samples to be sent.
  * @param  timeout_ms  Timeout duration (in ms).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       Operation exceeds user timeout.
  * @retval HAL_BUSY          The global_state is not HAL_SAI_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_SAI_Transmit(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample, uint32_t timeout_ms)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;
  uint32_t tickstart;
  uint32_t temp;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_sample != 0U);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_sample == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);
  tickstart = HAL_GetTick();

  HAL_CHECK_UPDATE_STATE(hsai, global_state, HAL_SAI_STATE_IDLE, HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_buff = (uint8_t *)p_data;
  hsai->xfer_size = size_sample;
  hsai->xfer_count = size_sample;
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);

  /* Fill the fifo before starting the communication */
  SAI_FillFifo(hsai);

  HAL_SAI_Enable(p_sai_block);

  while (hsai->xfer_count > 0U)
  {
    /* Write data if the FIFO is not full */
    if ((p_sai_block->SR & SAI_xSR_FLVL) != (uint32_t)SAI_FIFO_STATUS_FULL)
    {
      if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
      {
        p_sai_block->DR = *hsai->p_buff;
        hsai->p_buff++;
      }
      else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
      {
        temp = (uint32_t)(*hsai->p_buff);
        hsai->p_buff++;
        temp |= ((uint32_t)(*hsai->p_buff) << 8U);
        hsai->p_buff++;
        p_sai_block->DR = temp;
      }
      else /* Data size > 16 bits */
      {
        temp = (uint32_t)(*hsai->p_buff);
        hsai->p_buff++;
        temp |= ((uint32_t)(*hsai->p_buff) << 8U);
        hsai->p_buff++;
        temp |= ((uint32_t)(*hsai->p_buff) << 16U);
        hsai->p_buff++;
        temp |= ((uint32_t)(*hsai->p_buff) << 24U);
        hsai->p_buff++;
        p_sai_block->DR = temp;
      }
      hsai->xfer_count--;
    }
    else
    {
      /* Check for the timeout */
      if (timeout_ms != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
        {
          HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG
                            | HAL_SAI_FLAG_FREQ | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

          (void)SAI_Disable(hsai);

          /* Flush the FIFO */
          SET_BIT(p_sai_block->CR2, SAI_xCR2_FFLUSH);

          hsai->global_state = HAL_SAI_STATE_IDLE;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  hsai->global_state = HAL_SAI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Receive an amount of samples in blocking mode.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  p_data      Pointer to data buffer.
  * @param  size_sample Amount of samples to be received.
  * @param  timeout_ms  Timeout duration (in ms).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       Operation exceeds user timeout.
  * @retval HAL_BUSY          The global_state is not HAL_SAI_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_SAI_Receive(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample, uint32_t timeout_ms)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;
  uint32_t tickstart;
  uint32_t temp;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_sample != 0U);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_sample == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);
  tickstart = HAL_GetTick();

  HAL_CHECK_UPDATE_STATE(hsai, global_state, HAL_SAI_STATE_IDLE, HAL_SAI_STATE_RX_ACTIVE);

  hsai->p_buff = (uint8_t *)p_data;
  hsai->xfer_size = size_sample;
  hsai->xfer_count = size_sample;
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);

  HAL_SAI_Enable(p_sai_block);

  while (hsai->xfer_count > 0U)
  {
    /* Receive data if the FIFO is not empty */
    if ((p_sai_block->SR & SAI_xSR_FLVL) != (uint32_t)SAI_FIFO_STATUS_EMPTY)
    {
      if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
      {
        *hsai->p_buff = (uint8_t)p_sai_block->DR;
        hsai->p_buff++;
      }
      else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
      {
        temp = p_sai_block->DR;
        *hsai->p_buff = (uint8_t)temp;
        hsai->p_buff++;
        *hsai->p_buff = (uint8_t)(temp >> 8U);
        hsai->p_buff++;

      }
      else /* Data size 20 bits or 24 bits or 32 bits */
      {
        temp = p_sai_block->DR;
        *hsai->p_buff = (uint8_t)temp;
        hsai->p_buff++;
        *hsai->p_buff = (uint8_t)(temp >> 8U);
        hsai->p_buff++;
        *hsai->p_buff = (uint8_t)(temp >> 16U);
        hsai->p_buff++;
        *hsai->p_buff = (uint8_t)(temp >> 24U);
        hsai->p_buff++;
      }
      hsai->xfer_count--;
    }
    else
    {
      /* Check for the timeout */
      if (timeout_ms != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
        {
          HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG
                            | HAL_SAI_FLAG_FREQ | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

          (void)SAI_Disable(hsai);

          /* Flush the FIFO */
          SET_BIT(p_sai_block->CR2, SAI_xCR2_FFLUSH);

          hsai->global_state = HAL_SAI_STATE_IDLE;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  hsai->global_state = HAL_SAI_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Transmit an amount of samples in non-blocking mode with Interrupt.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  p_data      Pointer to data buffer.
  * @param  size_sample Amount of samples to be sent.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          The global_state is not HAL_SAI_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_SAI_Transmit_IT(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_sample != 0U);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_sample == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);

  HAL_CHECK_UPDATE_STATE(hsai, global_state, HAL_SAI_STATE_IDLE, HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_buff = (uint8_t *)p_data;
  hsai->xfer_size = size_sample;
  hsai->xfer_count = size_sample;
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);

  if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
  {
    hsai->p_isr = SAI_Transmit_IT8Bit;
  }
  else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
  {
    hsai->p_isr = SAI_Transmit_IT16Bit;
  }
  else
  {
    hsai->p_isr = SAI_Transmit_IT32Bit;
  }

  /* Fill the FIFO before starting the communication */
  SAI_FillFifo(hsai);

  /* Enable FRQ and OVRUDR interrupts */
  HAL_SAI_EnableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_IT));

  HAL_SAI_Enable(p_sai_block);

  return HAL_OK;
}

/**
  * @brief  Receive an amount of samples in non-blocking mode with Interrupt.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  p_data      Pointer to data buffer.
  * @param  size_sample Amount of samples to be received.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          The global_state is not HAL_SAI_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_SAI_Receive_IT(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_sample != 0U);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_sample == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);

  HAL_CHECK_UPDATE_STATE(hsai, global_state, HAL_SAI_STATE_IDLE, HAL_SAI_STATE_RX_ACTIVE);

  hsai->p_buff = (uint8_t *)p_data;
  hsai->xfer_size = size_sample;
  hsai->xfer_count = size_sample;
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);

  if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
  {
    hsai->p_isr = SAI_Receive_IT8Bit;
  }
  else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
  {
    hsai->p_isr = SAI_Receive_IT16Bit;
  }
  else
  {
    hsai->p_isr = SAI_Receive_IT32Bit;
  }

  /* Enable TXE and OVRUDR interrupts */
  HAL_SAI_EnableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_IT));

  HAL_SAI_Enable(p_sai_block);

  return HAL_OK;
}

#if defined (USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
/**
  * @brief  Transmit an amount of samples in non-blocking mode with DMA.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  p_data      Pointer to data buffer.
  * @param  size_sample Amount of samples to be sent.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY          The global_state is not HAL_SAI_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_SAI_Transmit_DMA(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;
  uint32_t dma_src_size;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_sample != 0U);
  ASSERT_DBG_PARAM(hsai->hdma_tx != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_sample == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);

  HAL_CHECK_UPDATE_STATE(hsai, global_state, HAL_SAI_STATE_IDLE, HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_buff = (uint8_t *)p_data;
  hsai->xfer_size = size_sample;
  hsai->xfer_count = size_sample;
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);
  tickstart = HAL_GetTick();

  if (hsai->hdma_tx != NULL)
  {
    /* Set the SAI Tx DMA Half transfer complete callback */
    hsai->hdma_tx->p_xfer_halfcplt_cb = SAI_DMATxHalfCplt;

    /* Set the SAI Tx DMA transfer complete callback */
    hsai->hdma_tx->p_xfer_cplt_cb = SAI_DMATxCplt;

    /* Set the DMA error callback */
    hsai->hdma_tx->p_xfer_error_cb = SAI_DMAError;

    /* Reset the DMA Tx abort callback */
    hsai->hdma_tx->p_xfer_abort_cb = NULL;

    /* For transmission, the DMA source is data buffer.
       We have to compute DMA size of a source block transfer in bytes according SAI data size. */
    if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
    {
      dma_src_size = (uint32_t)size_sample;
    }
    else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
    {
      dma_src_size = 2U * (uint32_t)size_sample;
    }
    else
    {
      dma_src_size = 4U * (uint32_t)size_sample;
    }

    /* Enable the Tx DMA Stream */
    if (HAL_DMA_StartPeriphXfer_IT_Opt(hsai->hdma_tx, (uint32_t)hsai->p_buff, (uint32_t)&p_sai_block->DR, dma_src_size,
                                       HAL_DMA_OPT_IT_HT) != HAL_OK)
    {
      hsai->global_state = HAL_SAI_STATE_IDLE;

      return HAL_ERROR;
    }
  }

  /* Enable the interrupts for error handling */
  HAL_SAI_EnableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_DMA));

  /* Enable SAI Tx DMA Request */
  SET_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

  /* Wait until FIFO is not empty */
  while ((p_sai_block->SR & SAI_xSR_FLVL) == (uint32_t)SAI_FIFO_STATUS_EMPTY)
  {
    /* Check for the timeout */
    if ((HAL_GetTick() - tickstart) > SAI_LONG_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  HAL_SAI_Enable(p_sai_block);

  return HAL_OK;
}

/**
  * @brief  Receive an amount of samples in non-blocking mode with DMA.
  * @param  hsai        Pointer to a hal_sai_handle_t.
  * @param  p_data      Pointer to data buffer.
  * @param  size_sample Amount of samples to be received.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Operation error.
  * @retval HAL_BUSY          The global_state is not HAL_SAI_STATE_IDLE (USE_HAL_CHECK_PROCESS_STATE is set to 1).
  */
hal_status_t HAL_SAI_Receive_DMA(hal_sai_handle_t *hsai, void *p_data, uint32_t size_sample)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;
  uint32_t dma_src_size;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(size_sample != 0U);
  ASSERT_DBG_PARAM(hsai->hdma_rx != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_sample == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, HAL_SAI_STATE_IDLE);

  p_sai_block = SAI_BLOCK(hsai);

  HAL_CHECK_UPDATE_STATE(hsai, global_state, HAL_SAI_STATE_IDLE, HAL_SAI_STATE_RX_ACTIVE);

  hsai->p_buff = (uint8_t *)p_data;
  hsai->xfer_size = size_sample;
  hsai->xfer_count = size_sample;
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes = HAL_SAI_ERROR_NONE;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);

  if (hsai->hdma_rx != NULL)
  {
    /* Set the SAI Rx DMA Half transfer complete callback */
    hsai->hdma_rx->p_xfer_halfcplt_cb = SAI_DMARxHalfCplt;

    /* Set the SAI Rx DMA transfer complete callback */
    hsai->hdma_rx->p_xfer_cplt_cb = SAI_DMARxCplt;

    /* Set the DMA error callback */
    hsai->hdma_rx->p_xfer_error_cb = SAI_DMAError;

    /* Reset the DMA Rx abort callback */
    hsai->hdma_rx->p_xfer_abort_cb = NULL;

    /* For reception, the DMA source is SAI DR register.
       We have to compute DMA size of a source block transfer in bytes according SAI data size. */
    if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
    {
      dma_src_size = (uint32_t)size_sample;
    }
    else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
    {
      dma_src_size = 2U * (uint32_t)size_sample;
    }
    else
    {
      dma_src_size = 4U * (uint32_t)size_sample;
    }

    /* Enable the Rx DMA Stream */
    if (HAL_DMA_StartPeriphXfer_IT_Opt(hsai->hdma_rx, (uint32_t)&p_sai_block->DR, (uint32_t)hsai->p_buff, dma_src_size,
                                       HAL_DMA_OPT_IT_HT) != HAL_OK)
    {
      hsai->global_state = HAL_SAI_STATE_IDLE;

      return HAL_ERROR;
    }
  }

  /* Enable the interrupts for error handling */
  HAL_SAI_EnableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_DMA));

  /* Enable SAI Rx DMA Request */
  SET_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

  HAL_SAI_Enable(p_sai_block);

  return HAL_OK;
}

/**
  * @brief  Pause the audio stream playing from the Media.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_SAI_Pause_DMA(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_mode_t mode;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  p_sai_block = SAI_BLOCK(hsai);
  mode = (hal_sai_mode_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_MODE);

  /* Pause the audio file playing by disabling the SAI DMA requests */
  CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

  if ((mode == HAL_SAI_MODE_MASTER_RX) || (mode == HAL_SAI_MODE_SLAVE_RX))
  {
    hsai->global_state = HAL_SAI_STATE_RX_PAUSED;
  }
  else
  {
    hsai->global_state = HAL_SAI_STATE_TX_PAUSED;
  }

  return HAL_OK;
}

/**
  * @brief  Resume the audio stream playing from the Media.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_SAI_Resume_DMA(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_mode_t mode;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_RX_PAUSED | (uint32_t)HAL_SAI_STATE_TX_PAUSED);

  p_sai_block = SAI_BLOCK(hsai);
  mode = (hal_sai_mode_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_MODE);

  /* Enable the SAI DMA requests */
  SET_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

  if ((mode == HAL_SAI_MODE_MASTER_RX) || (mode == HAL_SAI_MODE_SLAVE_RX))
  {
    hsai->global_state = HAL_SAI_STATE_RX_ACTIVE;
  }
  else
  {
    hsai->global_state = HAL_SAI_STATE_TX_ACTIVE;
  }

  return HAL_OK;
}
#endif /* USE_HAL_SAI_DMA */

/**
  * @brief  Abort a SAI IT or DMA process communication in blocking mode.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation error.
  */
hal_status_t HAL_SAI_Abort(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED);

  hsai->global_state = HAL_SAI_STATE_ABORT;

  if (SAI_Disable(hsai) != HAL_OK)
  {
    return HAL_ERROR;
  }

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
  SAI_Block_TypeDef *p_sai_block = SAI_BLOCK(hsai);

  if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_DMAEN))
  {
    /* Disable the SAI DMA request */
    CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

    /* Abort the SAI Tx DMA Stream: use blocking DMA Abort API (no callback) */
    if (hsai->hdma_tx != NULL)
    {
      hsai->hdma_tx->p_xfer_abort_cb = NULL;
      (void)HAL_DMA_Abort(hsai->hdma_tx);
    }

    /* Abort the SAI Rx DMA Stream: use blocking DMA Abort API (no callback) */
    if (hsai->hdma_rx != NULL)
    {
      hsai->hdma_rx->p_xfer_abort_cb = NULL;
      (void)HAL_DMA_Abort(hsai->hdma_rx);
    }
  }
#endif /* USE_HAL_SAI_DMA */

  SAI_StopTransfer(hsai);

  return HAL_OK;
}

/**
  * @brief  Abort a SAI IT or DMA process communication in non-blocking mode with Interrupt.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation error.
  */
hal_status_t HAL_SAI_Abort_IT(hal_sai_handle_t *hsai)
{
  uint32_t abort_cplt;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED);

  abort_cplt = 1U;

  hsai->global_state = HAL_SAI_STATE_ABORT;

  if (SAI_Disable(hsai) != HAL_OK)
  {
    return HAL_ERROR;
  }

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
  SAI_Block_TypeDef *p_sai_block = SAI_BLOCK(hsai);

  if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_DMAEN))
  {
    /* Disable the SAI DMA request */
    CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

    /* Abort the SAI Tx DMA Stream: use non-blocking DMA Abort API (callback) */
    if (hsai->hdma_tx != NULL)
    {
      if (hsai->hdma_tx->global_state == HAL_DMA_STATE_ACTIVE)
      {
        hsai->hdma_tx->p_xfer_abort_cb = SAI_DMAAbort;
        if (HAL_DMA_Abort_IT(hsai->hdma_tx) != HAL_OK)
        {
          hsai->hdma_tx->p_xfer_abort_cb = NULL;
        }
        else
        {
          abort_cplt = 0U;
        }
      }
    }

    /* Abort the SAI Rx DMA Stream: use non-blocking DMA Abort API (callback) */
    if (hsai->hdma_rx != NULL)
    {
      if (hsai->hdma_rx->global_state == HAL_DMA_STATE_ACTIVE)
      {
        hsai->hdma_rx->p_xfer_abort_cb = SAI_DMAAbort;
        if (HAL_DMA_Abort_IT(hsai->hdma_rx) != HAL_OK)
        {
          hsai->hdma_rx->p_xfer_abort_cb = NULL;
        }
        else
        {
          abort_cplt = 0U;
        }
      }
    }
  }
#endif /* USE_HAL_SAI_DMA */

  if (abort_cplt == 1U)
  {
    hsai->p_isr = NULL;

    SAI_StopTransfer(hsai);

    /* As no DMA to be aborted, call directly user abort complete callback */
#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_abort_cplt_cb(hsai);
#else
    HAL_SAI_AbortCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Enable the mute Tx mode.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @param  mode Mode selected.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_SAI_MuteTx(hal_sai_handle_t *hsai, hal_sai_mute_mode_t mode)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_MUTE_MODE(mode));

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED);

  SET_BIT(SAI_BLOCK(hsai)->CR2, SAI_xCR2_MUTE | (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Disable the mute Tx mode.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_SAI_UnmuteTx(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED);

  CLEAR_BIT(SAI_BLOCK(hsai)->CR2, SAI_xCR2_MUTEVAL | SAI_xCR2_MUTE);

  return HAL_OK;
}

/**
  * @brief  Enable the mute Rx detection.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @param  counter Number a data before mute detection (max 63).
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_SAI_EnableMuteRxDetection(hal_sai_handle_t *hsai, uint16_t counter)
{
  SAI_Block_TypeDef *p_sai_block;

  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(IS_SAI_MUTE_COUNTER(counter));

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_RX_PAUSED);

  p_sai_block = SAI_BLOCK(hsai);

  HAL_SAI_EnableIT(p_sai_block, HAL_SAI_IT_MUTEDET);

  SET_BIT(p_sai_block->CR2, (uint32_t)((uint32_t)counter << SAI_xCR2_MUTECNT_Pos));

  return HAL_OK;
}

/**
  * @brief  Disable the mute Rx detection.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_SAI_DisableMuteRxDetection(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_RX_PAUSED);

  p_sai_block = SAI_BLOCK(hsai);

  CLEAR_BIT(p_sai_block->CR2, SAI_xCR2_MUTECNT);

  HAL_SAI_DisableIT(p_sai_block, HAL_SAI_IT_MUTEDET);

  HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_MUTEDET);

  return HAL_OK;
}

/**
  * @brief  Get the mute Rx detection status.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_mute_rx_detection_status_t SAI mute Rx detection status.
  */
hal_sai_mute_rx_detection_status_t HAL_SAI_IsEnabledMuteRxDetection(const hal_sai_handle_t *hsai)
{
  hal_sai_mute_rx_detection_status_t status;

  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

  if (HAL_SAI_GetIT(SAI_BLOCK(hsai), SAI_xIMR_MUTEDETIE) != 1U)
  {
    status = HAL_SAI_MUTE_RX_DETECTION_DISABLED;
  }
  else
  {
    status = HAL_SAI_MUTE_RX_DETECTION_ENABLED;
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup SAI_Exported_Functions_Group5
  * @{

This section provides functions allowing to:
- Handle the SAI interrupt request with HAL_SAI_IRQHandler().
There are two ways to use callbacks: override weak callback functions or register user callback functions.
They are used to indicate:
  - When the Rx transfer is complete (HAL_SAI_RxCpltCallback()
    or callback function registered with HAL_SAI_RegisterRxCpltCallback()).
  - When the Rx half transfer is complete (HAL_SAI_RxHalfCpltCallback()
    or callback function registered with HAL_SAI_RegisterRxHalfCpltCallback()).
  - When the Tx transfer is complete (HAL_SAI_TxCpltCallback()
    or callback function registered with HAL_SAI_RegisterTxCpltCallback()).
  - When the Tx half transfer is complete (HAL_SAI_TxHalfCpltCallback()
    or callback function registered with HAL_SAI_RegisterTxHalfCpltCallback()).
  - When the mute is detected (HAL_SAI_MuteCallback()
    or callback function registered with HAL_SAI_RegisterMuteCallback()).
  - When the abort is complete (HAL_SAI_AbortCpltCallback()
    or callback function registered with HAL_SAI_RegisterAbortCpltCallback()).
  - When the SAI driver encounters an error (HAL_SAI_ErrorCallback() or callback function registered with
    HAL_SAI_RegisterErrorCallback()).
  */

/**
  * @brief Handle SAI interrupt request.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
void HAL_SAI_IRQHandler(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t it_flags_sources;

  p_sai_block = SAI_BLOCK(hsai);

  it_flags_sources = READ_REG(p_sai_block->SR);
  it_flags_sources &= READ_REG(p_sai_block->IMR);

  /* SAI FIFO request interrupt occurred -----------------------------------*/
  if ((it_flags_sources & HAL_SAI_FLAG_FREQ) == HAL_SAI_FLAG_FREQ)
  {
    hsai->p_isr(hsai);
  }

  /* SAI mutedet interrupt occurred ----------------------------------*/
  else if ((it_flags_sources & HAL_SAI_FLAG_MUTEDET) == HAL_SAI_FLAG_MUTEDET)
  {
    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_MUTEDET);

#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_mute_cb(hsai);
#else
    HAL_SAI_MuteCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }

  /* SAI Overrun/Underrun error interrupt occurred ----------------------------------*/
  else if ((it_flags_sources & HAL_SAI_FLAG_OVRUDR) == HAL_SAI_FLAG_OVRUDR)
  {
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
    hal_sai_mode_t mode = (hal_sai_mode_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_MODE);

    if ((mode == HAL_SAI_MODE_MASTER_RX) || (mode == HAL_SAI_MODE_SLAVE_RX))
    {
      hsai->last_error_codes |= HAL_SAI_ERROR_OVR;
    }
    else
    {
      hsai->last_error_codes |= HAL_SAI_ERROR_UDR;
    }
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR);

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_error_cb(hsai);
#else
    HAL_SAI_ErrorCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }

  /* SAI AFSDET interrupt occurred ----------------------------------*/
  else if ((it_flags_sources & HAL_SAI_FLAG_AFSDET) == HAL_SAI_FLAG_AFSDET)
  {
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
    hsai->last_error_codes |= HAL_SAI_ERROR_AFSDET;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_AFSDET);

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
    SAI_IRQ_DMAAbort(hsai, HAL_SAI_FLAG_AFSDET);
#else
    (void)HAL_SAI_Abort(hsai);
#endif /* USE_HAL_SAI_DMA */

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_error_cb(hsai);
#else
    HAL_SAI_ErrorCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }

  /* SAI LFSDET interrupt occurred ----------------------------------*/
  else if ((it_flags_sources & HAL_SAI_FLAG_LFSDET) == HAL_SAI_FLAG_LFSDET)
  {
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
    hsai->last_error_codes |= HAL_SAI_ERROR_LFSDET;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_LFSDET);

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
    SAI_IRQ_DMAAbort(hsai, HAL_SAI_FLAG_LFSDET);
#else
    (void)HAL_SAI_Abort(hsai);
#endif /* USE_HAL_SAI_DMA */

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_error_cb(hsai);
#else
    HAL_SAI_ErrorCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }

  /* SAI WCKCFG interrupt occurred ----------------------------------*/
  else if ((it_flags_sources & HAL_SAI_FLAG_WCKCFG) == HAL_SAI_FLAG_WCKCFG)
  {
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
    hsai->last_error_codes |= HAL_SAI_ERROR_WCKCFG;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_WCKCFG);

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
    SAI_IRQ_DMAAbort(hsai, HAL_SAI_FLAG_WCKCFG);
#else
    /* If WCKCFG occurs, SAI audio block is automatically disabled */
    HAL_SAI_DisableIT(p_sai_block, HAL_SAI_IT_OVRUDR | HAL_SAI_IT_MUTEDET | HAL_SAI_IT_WCKCFG | HAL_SAI_IT_FREQ
                      | HAL_SAI_IT_CNRDY | HAL_SAI_IT_AFSDET | HAL_SAI_IT_LFSDET);

    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG
                      | HAL_SAI_FLAG_FREQ | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

    hsai->global_state = HAL_SAI_STATE_IDLE;

    hsai->xfer_count = 0U;
#endif /* USE_HAL_SAI_DMA */

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_error_cb(hsai);
#else
    HAL_SAI_ErrorCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }

  /* SAI CNRDY interrupt occurred ----------------------------------*/
  else if ((it_flags_sources & HAL_SAI_FLAG_CNRDY) == HAL_SAI_FLAG_CNRDY)
  {
#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
    hsai->last_error_codes |= HAL_SAI_ERROR_CNREADY;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

    HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_CNRDY);

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
    hsai->p_error_cb(hsai);
#else
    HAL_SAI_ErrorCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
  }
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief   Rx transfer completed callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_RxCpltCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

/**
  * @brief   Rx transfer half completed callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_RxHalfCpltCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

/**
  * @brief   Tx transfer completed callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_TxCpltCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

/**
  * @brief   Tx transfer Half completed callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_TxHalfCpltCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

/**
  * @brief   Mute detected callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_MuteCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

/**
  * @brief   Abort completed callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_AbortCpltCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

/**
  * @brief   Error callback.
  * @param   hsai Pointer to a hal_sai_handle_t.
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__weak void HAL_SAI_ErrorCallback(hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  STM32_UNUSED(hsai);
}

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User SAI callback for Rx complete.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterRxCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_rx_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User SAI callback for Rx half complete.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterRxHalfCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_rx_half_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User SAI callback for Tx complete.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterTxCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_tx_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User SAI callback for Tx half complete.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterTxHalfCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_tx_half_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User SAI callback for Mute.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterMuteCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_mute_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User SAI callback for Abort complete.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterAbortCpltCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_abort_cplt_cb = p_callback;
  return HAL_OK;
}

/**
  * @brief  Register a User SAI callback for Error.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Register completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_SAI_RegisterErrorCallback(hal_sai_handle_t *hsai, hal_sai_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hsai != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_RX_ACTIVE | (uint32_t)HAL_SAI_STATE_TX_ACTIVE);

  hsai->p_error_cb = p_callback;
  return HAL_OK;
}

#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */

/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @addtogroup SAI_Exported_Functions_Group6
  * @{

This section provides functions allowing to control the bus of the SAIx instance:
    - HAL_SAI_AcquireBus(): Acquire the bus
    - HAL_SAI_ReleaseBus(): Release the bus.

  For multi task application, it is strongly recommended to use the bus operation functions to avoid race concurrency.
  */

/**
  * @brief  Acquire the current instance bus.
  * @param  hsai       Pointer to a hal_sai_handle_t.
  * @param  timeout_ms Timeout in milliseconds for the Acquire to expire.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_TIMEOUT Operation exceeds user timeout.
  */
hal_status_t HAL_SAI_AcquireBus(hal_sai_handle_t *hsai, uint32_t timeout_ms)
{
  hal_status_t status = HAL_TIMEOUT;

  ASSERT_DBG_PARAM(hsai != NULL);

  if (HAL_OS_SemaphoreTake(&hsai->semaphore, timeout_ms) == HAL_OS_OK)
  {
    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Release the current instance bus.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_SAI_ReleaseBus(hal_sai_handle_t *hsai)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hsai != NULL);

  if (HAL_OS_SemaphoreRelease(&hsai->semaphore) == HAL_OS_OK)
  {
    status = HAL_OK;
  }
  return status;
}

/**
  * @}
  */
#endif /* USE_HAL_MUTEX */


#if defined(USE_HAL_SAI_USER_DATA) && (USE_HAL_SAI_USER_DATA == 1)
/** @addtogroup SAI_Exported_Functions_Group7
  * @{

This section provides functions allowing to set user specific data to a SAIx instance:
    - HAL_SAI_SetUserData(): Set user data in handler.
    - HAL_SAI_GetUserData(): Get user data from handler.
  */

/**
  * @brief Store user data pointer into the handle.
  * @param hsai       Pointer to a hal_sai_handle_t.
  * @param p_user_data Pointer to the user data.
  */
void HAL_SAI_SetUserData(hal_sai_handle_t *hsai, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  hsai->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve user data pointer from the handle.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval void Pointer to the user data.
  */
const void *HAL_SAI_GetUserData(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  return (hsai->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_SAI_USER_DATA */

/** @addtogroup SAI_Exported_Functions_Group8
  * @{

This section permits to get in runtime the state of the SAI block with HAL_SAI_GetState().
  */

/**
  * @brief  Return the SAI handle state.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval hal_sai_state_t SAI state.
  */
hal_sai_state_t HAL_SAI_GetState(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  return hsai->global_state;
}

/**
  * @}
  */

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
/** @addtogroup SAI_Exported_Functions_Group9
  * @{
This section permits to get in runtime the last error codes of the peripheral SAI with HAL_SAI_GetLastErrorCodes().
  */

/**
  * @brief  Get the SAI last error codes.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval uint32_t This return value can be a combination of the following values:
  *         @arg @ref HAL_SAI_ERROR_NONE
  *         @arg @ref HAL_SAI_ERROR_OVR
  *         @arg @ref HAL_SAI_ERROR_UDR
  *         @arg @ref HAL_SAI_ERROR_AFSDET
  *         @arg @ref HAL_SAI_ERROR_LFSDET
  *         @arg @ref HAL_SAI_ERROR_CNREADY
  *         @arg @ref HAL_SAI_ERROR_WCKCFG
  *         @arg @ref HAL_SAI_ERROR_TIMEOUT
  *         @arg @ref HAL_SAI_ERROR_DMA
  */
uint32_t HAL_SAI_GetLastErrorCodes(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  return hsai->last_error_codes;
}

/**
  * @}
  */
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

/** @addtogroup SAI_Exported_Functions_Group10
  * @{
This section permits to get in runtime the kernel clock frequency of the peripheral SAI with HAL_SAI_GetClockFreq().
  */

/**
  * @brief  Get the SAI kernel clock frequency.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval uint32_t Frequency in Hz.
  * @retval 0        Source clock of the hsai not configured or not ready.
  */
uint32_t HAL_SAI_GetClockFreq(const hal_sai_handle_t *hsai)
{
  ASSERT_DBG_PARAM(hsai != NULL);

  ASSERT_DBG_STATE(hsai->global_state, (uint32_t)HAL_SAI_STATE_INIT | (uint32_t)HAL_SAI_STATE_IDLE
                   | (uint32_t)HAL_SAI_STATE_TX_ACTIVE | (uint32_t)HAL_SAI_STATE_RX_ACTIVE
                   | (uint32_t)HAL_SAI_STATE_TX_PAUSED | (uint32_t)HAL_SAI_STATE_RX_PAUSED
                   | (uint32_t)HAL_SAI_STATE_ABORT);

#if (!defined(USE_ASSERT_DBG_STATE) || !defined(USE_ASSERT_DBG_PARAM)) && !defined(SAI2)
  STM32_UNUSED(hsai);
#endif /* (USE_ASSERT_DBG_STATE || USE_ASSERT_DBG_PARAM) && SAI2 */

  return HAL_RCC_SAI_GetKernelClkFreq(SAI_GET_INSTANCE(hsai));
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SAI_Private_Functions
  * @{
  */

/**
  * @brief Fill the FIFO.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_FillFifo(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_sai_data_size_t data_size;
  hal_sai_companding_t companding;
  uint32_t temp;
  uint32_t xfer_count;

  p_sai_block = SAI_BLOCK(hsai);
  data_size = (hal_sai_data_size_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_DS);
  companding = (hal_sai_companding_t)(uint32_t)READ_BIT(p_sai_block->CR2, SAI_xCR2_COMP);
  xfer_count = hsai->xfer_count;

  /* Fill the FIFO with data before to enable the SAI */
  while (((p_sai_block->SR & SAI_xSR_FLVL) != (uint32_t)SAI_FIFO_STATUS_FULL) && (xfer_count > 0U))
  {
    if ((data_size == HAL_SAI_DATA_SIZE_8BITS) && (companding == HAL_SAI_COMPANDING_NO))
    {
      p_sai_block->DR = *hsai->p_buff;
      hsai->p_buff++;
    }
    else if (data_size <= HAL_SAI_DATA_SIZE_16BITS)
    {
      temp = (uint32_t)(*hsai->p_buff);
      hsai->p_buff++;
      temp |= ((uint32_t)(*hsai->p_buff) << 8U);
      hsai->p_buff++;
      p_sai_block->DR = temp;
    }
    else /* Data size 20 bits or 24 bits or 32 bits */
    {
      temp = (uint32_t)(*hsai->p_buff);
      hsai->p_buff++;
      temp |= ((uint32_t)(*hsai->p_buff) << 8U);
      hsai->p_buff++;
      temp |= ((uint32_t)(*hsai->p_buff) << 16U);
      hsai->p_buff++;
      temp |= ((uint32_t)(*hsai->p_buff) << 24U);
      hsai->p_buff++;
      p_sai_block->DR = temp;
    }
    xfer_count--;
  }
  hsai->xfer_count = xfer_count;
}

/**
  * @brief  Return the interrupt flag to set according the SAI setup.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @param  mode SAI_MODE_DMA or SAI_MODE_IT.
  * @retval uint32_t List of the IT flag to enable.
  */
static uint32_t SAI_InterruptFlag(const hal_sai_handle_t *hsai, sai_mode_t mode)
{
  const SAI_Block_TypeDef *p_sai_block;
  uint32_t tmp_it;
  hal_sai_protocol_t protocol;
  hal_sai_mode_t audio_mode;

  p_sai_block = SAI_BLOCK(hsai);
  tmp_it = HAL_SAI_IT_OVRUDR;
  protocol = (hal_sai_protocol_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_PRTCFG);
  audio_mode = (hal_sai_mode_t)(uint32_t)READ_BIT(p_sai_block->CR1, SAI_xCR1_MODE);

  if (mode == SAI_MODE_IT)
  {
    tmp_it |= HAL_SAI_IT_FREQ;
  }

  if ((protocol == HAL_SAI_PROTOCOL_AC97)
      && ((audio_mode == HAL_SAI_MODE_SLAVE_RX) || (audio_mode == HAL_SAI_MODE_MASTER_RX)))
  {
    tmp_it |= HAL_SAI_IT_CNRDY;
  }

  if ((audio_mode == HAL_SAI_MODE_SLAVE_RX) || (audio_mode == HAL_SAI_MODE_SLAVE_TX))
  {
    tmp_it |= HAL_SAI_IT_AFSDET | HAL_SAI_IT_LFSDET;
  }
  else
  {
    /* hsai has been configured in master mode */
    tmp_it |= HAL_SAI_IT_WCKCFG;
  }

  return tmp_it;
}

/**
  * @brief  Disable the SAI and wait for the disabling.
  * @param  hsai Pointer to a hal_sai_handle_t.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation error.
  */
static hal_status_t SAI_Disable(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  hal_status_t status;
  uint32_t count;

  p_sai_block = SAI_BLOCK(hsai);
  count = SAI_DEFAULT_TIMEOUT * (SystemCoreClock / 7U / 1000U);
  status = HAL_OK;

  HAL_SAI_Disable(p_sai_block);

  do
  {
    /* Check for the timeout */
    if (count == 0U)
    {
      status = HAL_ERROR;
      break;
    }
    count--;
  } while ((p_sai_block->CR1 & SAI_xCR1_SAIEN) != 0U);

  return status;
}

/**
  * @brief Stop SAI transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_StopTransfer(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);
  hsai->xfer_count = 0U;

  HAL_SAI_DisableIT(p_sai_block, HAL_SAI_IT_OVRUDR | HAL_SAI_IT_MUTEDET | HAL_SAI_IT_WCKCFG | HAL_SAI_IT_FREQ
                    | HAL_SAI_IT_CNRDY | HAL_SAI_IT_AFSDET | HAL_SAI_IT_LFSDET);

  HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG | HAL_SAI_FLAG_FREQ
                    | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

  /* Flush the FIFO */
  SET_BIT(p_sai_block->CR2, SAI_xCR2_FFLUSH);

  hsai->global_state = HAL_SAI_STATE_IDLE;
}

/**
  * @brief Tx Handler for Transmit in Interrupt mode 8-Bit transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_Transmit_IT8Bit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);

  if (hsai->xfer_count == 0U)
  {
    SAI_TransmitCplt_IT(hsai);
  }
  else
  {
    /* Write data on DR register */
    p_sai_block->DR = *hsai->p_buff;
    hsai->p_buff++;
    hsai->xfer_count--;
  }
}

/**
  * @brief Tx Handler for Transmit in Interrupt mode for 16-Bit transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_Transmit_IT16Bit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t temp;

  p_sai_block = SAI_BLOCK(hsai);

  if (hsai->xfer_count == 0U)
  {
    SAI_TransmitCplt_IT(hsai);
  }
  else
  {
    /* Write data on DR register */
    temp = (uint32_t)(*hsai->p_buff);
    hsai->p_buff++;
    temp |= ((uint32_t)(*hsai->p_buff) << 8U);
    hsai->p_buff++;
    p_sai_block->DR = temp;
    hsai->xfer_count--;
  }
}

/**
  * @brief Tx Handler for Transmit in Interrupt mode for 32-Bit transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_Transmit_IT32Bit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t temp;

  p_sai_block = SAI_BLOCK(hsai);

  if (hsai->xfer_count == 0U)
  {
    SAI_TransmitCplt_IT(hsai);
  }
  else
  {
    /* Write data on DR register */
    temp = (uint32_t)(*hsai->p_buff);
    hsai->p_buff++;
    temp |= ((uint32_t)(*hsai->p_buff) << 8U);
    hsai->p_buff++;
    temp |= ((uint32_t)(*hsai->p_buff) << 16U);
    hsai->p_buff++;
    temp |= ((uint32_t)(*hsai->p_buff) << 24U);
    hsai->p_buff++;
    p_sai_block->DR = temp;
    hsai->xfer_count--;
  }
}

/**
  * @brief Transmit complete in Interrupt mode.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_TransmitCplt_IT(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);

  /* Disable FREQ and OVRUDR interrupts */
  HAL_SAI_DisableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_IT));

  hsai->global_state = HAL_SAI_STATE_IDLE;

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_tx_cplt_cb(hsai);
#else
  HAL_SAI_TxCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

/**
  * @brief Rx Handler for Receive in Interrupt mode 8-Bit transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_Receive_IT8Bit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);
  *hsai->p_buff = (uint8_t)p_sai_block->DR;
  hsai->p_buff++;
  hsai->xfer_count--;

  /* Check end of the transfer */
  if (hsai->xfer_count == 0U)
  {
    SAI_ReceiveCplt_IT(hsai);
  }
}

/**
  * @brief Rx Handler for Receive in Interrupt mode for 16-Bit transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_Receive_IT16Bit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t temp;

  p_sai_block = SAI_BLOCK(hsai);
  temp = p_sai_block->DR;
  *hsai->p_buff = (uint8_t)temp;
  hsai->p_buff++;
  *hsai->p_buff = (uint8_t)(temp >> 8U);
  hsai->p_buff++;
  hsai->xfer_count--;

  /* Check end of the transfer */
  if (hsai->xfer_count == 0U)
  {
    SAI_ReceiveCplt_IT(hsai);
  }
}

/**
  * @brief Rx Handler for Receive in Interrupt mode for 32-Bit transfer.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_Receive_IT32Bit(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;
  uint32_t temp;

  p_sai_block = SAI_BLOCK(hsai);
  temp = p_sai_block->DR;
  *hsai->p_buff = (uint8_t)temp;
  hsai->p_buff++;
  *hsai->p_buff = (uint8_t)(temp >> 8U);
  hsai->p_buff++;
  *hsai->p_buff = (uint8_t)(temp >> 16U);
  hsai->p_buff++;
  *hsai->p_buff = (uint8_t)(temp >> 24U);
  hsai->p_buff++;
  hsai->xfer_count--;

  /* Check end of the transfer */
  if (hsai->xfer_count == 0U)
  {
    SAI_ReceiveCplt_IT(hsai);
  }
}

/**
  * @brief Receive complete in Interrupt mode.
  * @param hsai Pointer to a hal_sai_handle_t.
  */
static void SAI_ReceiveCplt_IT(hal_sai_handle_t *hsai)
{
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);

  /* Disable TXE and OVRUDR interrupts */
  HAL_SAI_DisableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_IT));

  HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR);

  hsai->global_state = HAL_SAI_STATE_IDLE;

#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_rx_cplt_cb(hsai);
#else
  HAL_SAI_RxCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

#if defined(USE_HAL_SAI_DMA) && (USE_HAL_SAI_DMA == 1)
/**
  * @brief SAI DMA error on IRQHandler.
  * @param hsai Pointer to a hal_sai_handle_t.
  * @param flag SAI flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref HAL_SAI_FLAG_WCKCFG Wrong clock configuration
  *            @arg @ref HAL_SAI_FLAG_AFSDET Anticipated frame synchronization detection
  *            @arg @ref HAL_SAI_FLAG_LFSDET Late frame synchronization detection
  */
static void SAI_IRQ_DMAAbort(hal_sai_handle_t *hsai, uint32_t flag)
{
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);

  /* Check SAI DMA is enabled */
  if (IS_BIT_SET(p_sai_block->CR1, SAI_xCR1_DMAEN))
  {
    /* Abort the SAI DMA Streams */
    if (hsai->hdma_tx != NULL)
    {
      /* Set the DMA Tx abort callback */
      hsai->hdma_tx->p_xfer_abort_cb = SAI_DMAAbort;

      /* Abort DMA in IT mode */
      (void)HAL_DMA_Abort_IT(hsai->hdma_tx);
    }

    /* Abort DMA Rx */
    if (hsai->hdma_rx != NULL)
    {
      /* Set the DMA Rx abort callback */
      hsai->hdma_rx->p_xfer_abort_cb = SAI_DMAAbort;

      /* Abort DMA in IT mode */
      (void)HAL_DMA_Abort_IT(hsai->hdma_rx);
    }
  }
  else /* DMA is disabled */
  {
    if ((flag == HAL_SAI_FLAG_AFSDET) || (flag == HAL_SAI_FLAG_LFSDET))
    {
      (void)HAL_SAI_Abort(hsai);
    }
    else /* flag is HAL_SAI_FLAG_WCKCFG */
    {
      HAL_SAI_DisableIT(p_sai_block, HAL_SAI_IT_OVRUDR | HAL_SAI_IT_MUTEDET | HAL_SAI_IT_WCKCFG | HAL_SAI_IT_FREQ
                        | HAL_SAI_IT_CNRDY | HAL_SAI_IT_AFSDET | HAL_SAI_IT_LFSDET);

      HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG
                        | HAL_SAI_FLAG_FREQ | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

      hsai->global_state = HAL_SAI_STATE_IDLE;

      hsai->xfer_count = 0U;
    }
  }
}

/**
  * @brief DMA SAI transmit process complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void SAI_DMATxCplt(hal_dma_handle_t *hdma)
{
  hal_sai_handle_t *hsai = (hal_sai_handle_t *)(hdma->p_parent);

  SAI_Block_TypeDef *p_sai_block = SAI_BLOCK(hsai);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    hsai->xfer_count = 0U;

    /* Disable Tx DMA Request */
    CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

    /* Stop the interrupts error handling */
    HAL_SAI_DisableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_DMA));

    hsai->global_state = HAL_SAI_STATE_IDLE;
  }

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_tx_cplt_cb(hsai);
#else
  HAL_SAI_TxCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA SAI transmit process half complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void SAI_DMATxHalfCplt(hal_dma_handle_t *hdma)
{
  hal_sai_handle_t *hsai = (hal_sai_handle_t *)(hdma->p_parent);

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_tx_half_cplt_cb(hsai);
#else
  HAL_SAI_TxHalfCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA SAI receive process complete callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void SAI_DMARxCplt(hal_dma_handle_t *hdma)
{
  hal_sai_handle_t *hsai = (hal_sai_handle_t *)(hdma->p_parent);

  SAI_Block_TypeDef *p_sai_block = SAI_BLOCK(hsai);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check if DMA in circular mode*/
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    hsai->xfer_count = 0U;

    /* Disable Rx DMA Request */
    CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

    /* Stop the interrupts error handling */
    HAL_SAI_DisableIT(p_sai_block, SAI_InterruptFlag(hsai, SAI_MODE_DMA));

    hsai->global_state = HAL_SAI_STATE_IDLE;
  }

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_rx_cplt_cb(hsai);
#else
  HAL_SAI_RxCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA SAI receive process half complete callback
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void SAI_DMARxHalfCplt(hal_dma_handle_t *hdma)
{
  hal_sai_handle_t *hsai = (hal_sai_handle_t *)(hdma->p_parent);

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_rx_half_cplt_cb(hsai);
#else
  HAL_SAI_RxHalfCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA SAI communication error callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void SAI_DMAError(hal_dma_handle_t *hdma)
{
  hal_sai_handle_t *hsai = (hal_sai_handle_t *)(hdma->p_parent);

  SAI_Block_TypeDef *p_sai_block = SAI_BLOCK(hsai);

#if defined(USE_HAL_SAI_GET_LAST_ERRORS) && (USE_HAL_SAI_GET_LAST_ERRORS == 1)
  hsai->last_error_codes |= HAL_SAI_ERROR_DMA;
#endif /* USE_HAL_SAI_GET_LAST_ERRORS */

  /* Disable the SAI DMA request */
  CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

  (void)SAI_Disable(hsai);

  /* Set the SAI state idle to be able to start again the process */
  hsai->global_state = HAL_SAI_STATE_IDLE;

  hsai->xfer_count = 0U;

#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_error_cb(hsai);
#else
  HAL_SAI_ErrorCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA SAI Abort callback.
  * @param hdma Pointer to a hal_dma_handle_t.
  */
static void SAI_DMAAbort(hal_dma_handle_t *hdma)
{
  hal_sai_handle_t *hsai = (hal_sai_handle_t *)(hdma->p_parent);
  SAI_Block_TypeDef *p_sai_block;

  p_sai_block = SAI_BLOCK(hsai);

  if (hsai->hdma_tx != NULL)
  {
    hsai->hdma_tx->p_xfer_abort_cb = NULL;
  }

  if (hsai->hdma_rx != NULL)
  {
    hsai->hdma_rx->p_xfer_abort_cb = NULL;
  }

  (void)SAI_Disable(hsai);

  /* Disable DMA request */
  CLEAR_BIT(p_sai_block->CR1, SAI_xCR1_DMAEN);

  hsai->xfer_count = 0U;

  HAL_SAI_DisableIT(p_sai_block, HAL_SAI_IT_OVRUDR | HAL_SAI_IT_MUTEDET | HAL_SAI_IT_WCKCFG | HAL_SAI_IT_FREQ
                    | HAL_SAI_IT_CNRDY | HAL_SAI_IT_AFSDET | HAL_SAI_IT_LFSDET);

  HAL_SAI_ClearFlag(p_sai_block, HAL_SAI_FLAG_OVRUDR | HAL_SAI_FLAG_MUTEDET | HAL_SAI_FLAG_WCKCFG | HAL_SAI_FLAG_FREQ
                    | HAL_SAI_FLAG_CNRDY | HAL_SAI_FLAG_AFSDET | HAL_SAI_FLAG_LFSDET);

  /* Flush the FIFO */
  SET_BIT(p_sai_block->CR2, SAI_xCR2_FFLUSH);

  hsai->global_state = HAL_SAI_STATE_IDLE;

  /* SAI error Callback */
#if defined(USE_HAL_SAI_REGISTER_CALLBACKS) && (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  hsai->p_abort_cplt_cb(hsai);
#else
  HAL_SAI_AbortCpltCallback(hsai);
#endif /* USE_HAL_SAI_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_SAI_DMA */

/**
  * @}
  */

#endif /* USE_HAL_SAI_MODULE */
/**
  * @}
  */

/**
  * @}
  */
