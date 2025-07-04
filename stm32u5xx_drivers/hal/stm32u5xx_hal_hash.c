/**
  ******************************************************************************
  * @file    stm32u5xx_hal_hash.c
  * @brief   HASH HAL module driver.
  *          This file provides firmware functions to manage HASH peripheral
  *
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

#if defined (HASH)

/** @addtogroup HASH
  * @{
# How to use this driver
The HASH HAL driver can be used as follows:

1. Initialize and de-initialize the logical HASH object :
  - To initialize the HASH peripheral, Use the HAL_HASH_Init() function to initialize the HAL HASH driver for the given
    handle object
    - The HAL_HASH_Init() API allow to associate physical instance to logical object(handle) and
      initialize the internal parameters of the handle.

    - The HAL_HASH_Init() API allows to enable the peripheral clock when USE_HASH_CLK_ENABLE_MODEL is different from
      HAL_CLK_ENABLE_NO. In case of the USE_HASH_CLK_ENABLE_MODEL compilation is not defined or define to
      HAL_CLK_ENABLE_NO, the application needs to explicitly call the HAL RCC API HAL_RCC_HASH_EnableClock() in order
      to enable the clock of HASH peripheral.

  - To de-initiliaze the HASH peripheral, use the HAL_HASH_DeInit() function that stop any ongoing process and
    set the HASH handle state to reset.

2. Set and Get HASH configuration:
 - To apply the HASH peripheral configuration, use the HAL_HASH_SetConfig().
   HASH Parameters are :
      - Data Swapping : no swap or half word swap or bit swap or byte swap.
      - algorithm : MD5 or SHA1 or SHA224 or SHA256.
 - To get the HASH peripheral configuration, use the HAL_HASH_GetConfig() to retrieve the current HASH configuration.

3. Set and Get HASH HMAC configuration:
 - To apply the HASH HMAC peripheral configuration, use the HAL_HASH_HMAC_SetConfig().
   HASH HMAC Parameters are :
      - Data Swapping : no swap or half word swap or bit swap or byte swap.
      - algorithm : MD5 or SHA1 or SHA224 or SHA256.
      - Key : Identifier of the key to use for the HMAC operation.
      - key size in bytes.
 - To get the HASH HMAC peripheral configuration, use the HAL_HASH_HMAC_GetConfig() to retrieve the current HASH HMAC
   configuration.

4. There are 2 families of API:
  - OneShot API: handling one single/complete buffer and providing the HASH result.
  - Update APIs: allowing the user to update several buffers then provide the HASH result corresponding
    to the data provided by the sum of these updated buffers.

5. Three processing modes are available:
 - OneShot APIs:
   - Polling mode: Processing APIs are blocking functions.
     These APIs process the data and wait till the digest computation is finished.
     Use function HAL_HASH_Compute() for HASH or HAL_HASH_HMAC_Compute() for HMAC.
   - Interrupt mode: processing APIs are not blocking functions.
     It process the data under interruption.
     Use the function HAL_HASH_Compute_IT() for HASH or HAL_HASH_HMAC_Compute_IT() for HMAC.
   - DMA mode: processing APIs are not blocking functions and the CPU is not used for data transfer.
     The data transfer is ensured by DMA.
     Use the function HAL_HASH_Compute_DMA() for HASH or HAL_HASH_HMAC_Compute_DMA() for HMAC.

 - Update APIs:
   - Polling mode:
     - HASH context mode :
       API HAL_HASH_Update() must be called to start hashing and update several input buffers.
       User must resort to HAL_HASH_Finish() to retrieve as well the computed digest.
     - HMAC context mode :
       The key and the key size are entered in config API HAL_HASH_HMAC_SetConfig().
       API HAL_HASH_HMAC_Update() must be called to start hashing and update several input buffers.
       User must resort to HAL_HASH_HMAC_Finish() to retrieve as well the computed digest.

   - Interrupt mode:
     - HASH context mode :
       API HAL_HASH_Update_IT() must be called to start hashing and update several input buffers.
       User must resort to HAL_HASH_Finish() to retrieve as well the computed digest.

     - HMAC context mode :
       The key and the key size are entered in config API HAL_HASH_HMAC_SetConfig().
       API HAL_HASH_HMAC_Update_IT() must be called to start hashing and update several input buffers.
       User must resort to HAL_HASH_HMAC_Finish() to retrieve as well the computed digest.

   - DMA mode:
     - HASH context mode :
       API HAL_HASH_Update_DMA() must be called to start hashing and update several input buffers.
       User must resort to HAL_HASH_Finish() to retrieve as well the computed digest.
     - HMAC context mode :
       The key and the key size are entered in config API HAL_HASH_HMAC_SetConfig().
       API HAL_HASH_HMAC_Update_DMA() must be called to start hashing and update several input buffers.
       User must resort to HAL_HASH_HMAC_Finish() to retrieve as well the computed digest.

6. Switch context:
 - Two APIs are available to suspend HASH or HMAC processing:
   - For computation process : The user need to call the function HAL_HASH_RequestSuspendComputation()
     when a computation process is ongoing.
   - For update process: The user need to call the function HAL_HASH_RequestSuspendUpdate() when an
     update process is ongoing.
 - Two APIs are available to resume HASH or HMAC processing:
   - For computation process : The user need to call the function HAL_HASH_ResumeComputation() to resume the prior
     computation process and set the HAL HASH handle state to HAL_HASH_STATE_ACTIVE_COMPUTE.
   - For update process: The user need to call the function HAL_HASH_ResumeUpdate() to resume the prior
     update process and set the HAL HASH handle state to HAL_HASH_STATE_ACTIVE_UPDATE.

 - When HASH or HMAC processing is suspended, the user can use the function HAL_HASH_SaveContext() to save the
   peripheral context. This context can be restored afterwards.
 - Before resuming the HASH or HMAC processing user can call HAL_HASH_RestoreContext() to restore the saved context
   needed if the HASH peripheral was used by another applicative process to perform some other hashing tasks.

 - Once the HASH Peripheral context has been restored to the same configuration as that at suspension time, processing
   can be Resumed thanks to the APIs HAL_HASH_ResumeComputation()/HAL_HASH_ResumeUpdate() from the proper location
   reached at suspend time and with the same parameters (the required parameters to resume the operation are saved
   into the handle).

7. Remarks on message length:
 - HAL in interruption mode (interruptions driven):
    - Due to HASH peripheral hardware design, the peripheral interruption is triggered every 64 bytes.

 - HAL in DMA mode
    - Again, due to hardware design, the DMA transfer to feed the data can only be done on a word-basis.
      The same field described above in HASH_STR is used to specify which bits to discard at the end of the DMA transfer
      to process only the message bits and not extra bits. Due to hardware implementation,
      this is possible only at the end of the complete message. When several DMA transfers are needed to enter the
      message, this is not applicable at the end of the intermediary transfers.

8. Callback registration:
  - By default, after the HAL_HASH_Init, all callbacks are reset to the corresponding legacy weak functions:
     - HAL_HASH_InputCpltCallback()  : A Callback when an input data transfer complete has occurred.
     - HAL_HASH_DigestCpltCallback() : A Callback when a digest computation complete has occurred.
     - HAL_HASH_ErrorCallback()      : A Callback when an error has occurred.
     - HAL_HASH_SuspendCallback()    : A callback when a suspend operation has occurred.
     - HAL_HASH_AbortCallback()      : A callback when an abort operation has occurred.
  - The compilation define USE_HAL_HASH_REGISTER_CALLBACKS when set to 1 allows the user to configure dynamically
    the driver callbacks.
  - Use function HAL_HASH_RegisterInputCpltCallback() to register a user callback for input completion.
  - Use function HAL_HASH_RegisterDigestComputationCpltCallback() to register a user callback for input completion.
  - Use function HAL_HASH_RegisterErrorCpltCallback() to register a user callback for error callback.
  - Use function HAL_HASH_RegisterSuspendCpltCallback() to register a user callback for suspend callback.
  - Use function HAL_HASH_RegisterAbortCpltCallback() to register a user callback for abort callback.

  - When The compilation define USE_HAL_HASH_REGISTER_CALLBACKS is set to 0 or not defined, the callback registering
    feature is not available and weak (surcharged) callbacks are used.

## Configuration inside the HASH driver

Config defines                 | Description     |   Default value | Note
-------------------------------| --------------- |-----------------| ---------------------------------------------
PRODUCT                        | from IDE        |     NA          | STM32U5XX
USE_ASSERT_DBG_PARAM           | from the IDE    |     NONE        | Allows to use the assert checks parameters.
USE_ASSERT_DBG_STATE           | from the IDE    |     NONE        | Allows to use the assert checks states.
USE_HAL_HASH_MODULE            | from hal_conf.h |      1          | Enable the HAL HASH module
USE_HAL_CHECK_PARAM            | from hal_conf.h |      0          | Allows to use the runtime checks parameters.
USE_HAL_HASH_REGISTER_CALLBACKS| from hal_conf.h |      0          | Allows to provide specific callback functions.
USE_HAL_HASH_GET_LAST_ERRORS   | from hal_conf.h |      0          | Allows to get last errors codes.
USE_HAL_HASH_USER_DATA         | from hal_conf.h |      0          | Allows to enable/disable user data.
USE_HAL_HASH_CLK_ENABLE_MODEL  | from hal_conf.h |HAL_CLK_ENABLE_NO| Allows to enable the clock model for the HASH.
USE_HAL_HASH_DMA               | from hal_conf.h |      1          | Allows to enable the HASH DMA module service.
USE_HAL_SECURE_CHECK_PARAM     | from hal_conf.h |      0          | Allows to use the runtime check for sensitive APIs.
USE_HAL_CHECK_PROCESS_STATE    | from hal_conf.h |      0          | Allows to use the load and store exclusive
  */

#if defined (USE_HAL_HASH_MODULE) && (USE_HAL_HASH_MODULE == 1)

/* Private function prototypes --------------------------------------------------------------------------------------*/
/** @defgroup HASH_Private_Functions HASH Private Functions
  * @{
  */
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
static void HASH_DMAXferCplt(hal_dma_handle_t *hdma);
static void HASH_DMAAbort(hal_dma_handle_t *hdma);
static void HASH_DMAError(hal_dma_handle_t *hdma);
static hal_status_t HASH_SuspendDMA(hal_hash_handle_t *hhash);
static hal_status_t HASH_ResumeDMA(hal_hash_handle_t *hhash);
#endif /* USE_HAL_HASH_DMA */

static hal_status_t HASH_WriteKey(hal_hash_handle_t *hhash, const uint8_t *p_key, uint32_t key_size_byte);
static hal_status_t HASH_WriteData_IT(hal_hash_handle_t *hhash, uint8_t operation);
static hal_status_t HASH_HMAC_WriteData_IT(hal_hash_handle_t *hhash, uint8_t operation);
static void HASH_GetDigestMsg(const hal_hash_handle_t *hhash, const uint8_t *p_msg_digest, uint8_t input_size_byte);
static hal_status_t HASH_WaitOnFlagUntilTimeout(hal_hash_handle_t *hhash, uint32_t flag, uint32_t flag_state,
                                                uint32_t timeout_ms);
static void HASH_UpdateCRAccordingAlgo(hal_hash_handle_t *hhash, uint32_t size_byte);
__STATIC_INLINE uint8_t HAL_HASH_GetDigestLength(const hal_hash_handle_t *hhash);

static hal_status_t HASH_Write_Data(hal_hash_handle_t *hhash, const uint8_t *p_input_buffer, uint32_t input_size_byte,
                                    uint32_t operation);
/**
  * @}
  */

/* Private constants ------------------------------------------------------------------------------------------------*/
/** @defgroup HASH_Private_Constants HASH Private Constants
  * @{
  */
#define HASH_TIMEOUT_MS                1000U         /*!< Time-out value in millisecond                         */
#define HASH_BLOCK_SIZE_64B            64U           /*!< block Size equal to 64 bytes                          */
#define HASH_BLOCK_SIZE_128B           128U          /*!< block Size equal to 128 bytes                         */

#define HASH_ALGO_MODE_HMAC            HASH_CR_MODE  /*!< HASH HMAC algorithm mode selected                     */

#define HASH_LONG_KEY                  HASH_CR_LKEY  /*!< HMAC Key size is > block size (64 or 128 bytes)       */

#define HASH_PHASE_READY               0x01U         /*!< HASH peripheral is ready to start                     */
#define HASH_PHASE_PROCESS             0x02U         /*!< HASH peripheral is in HASH processing phase           */
#define HASH_PHASE_HMAC_STEP_1         0x03U         /*!< HASH peripheral is in HMAC step 1 processing phase
                                                         (It consists in entering the inner hash function key)  */
#define HASH_PHASE_HMAC_STEP_2         0x04U         /*!< HASH peripheral is in HMAC step 2 processing phase
                                                          (It consists in entering the message text)            */
#define HASH_PHASE_HMAC_STEP_3         0x05U         /*!< HASH peripheral is in HMAC step 3 processing phase
                                                      (It consists in entering the outer hash function key)     */

#define HASH_FLAG_STATE_RESET          0x00U         /*!< HASH flag is in reset state                           */
#define HASH_FLAG_STATE_SET            0x01U         /*!< HASH flag is in set state                             */

#define HASH_SUSPEND_NONE              0x00U         /*!< HASH peripheral suspension not requested              */
#define HASH_SUSPEND                   0x01U         /*!< HASH peripheral suspension is requested               */

#define HASH_UPDATE_PROCESS            0x01U         /*!< HASH peripheral update process ongoing                */
#define HASH_COMPUTE_PROCESS           0x02U         /*!< HASH peripheral compute process ongoing               */
#define HASH_FINISH_PROCESS            0x00U         /*!< HASH peripheral Finish process ongoing                */
/**
  * @}
  */

/* Private macros --------------------------------------------------------------------------------------------------*/
/** @defgroup HASH_Private_Macros   HASH Private Macros
  * @{
  */
/*! Macro to get the handle instance */
#define HASH_GET_INSTANCE(handle)    ((HASH_TypeDef *)((uint32_t)(handle)->instance))

/*! Ensure that HASH input data type is valid */
#define IS_HASH_DATA_SWAPPING(data_swapping) (((data_swapping) == HAL_HASH_DATA_SWAP_NO)          \
                                              || ((data_swapping) == HAL_HASH_DATA_SWAP_HALFWORD) \
                                              || ((data_swapping) == HAL_HASH_DATA_SWAP_BYTE)     \
                                              || ((data_swapping) == HAL_HASH_DATA_SWAP_BIT))

/*! Ensure that HASH input algorithm is valid */
#define IS_HASH_ALGORITHM(algorithm) (((algorithm) == HAL_HASH_ALGO_SHA1)      \
                                      || ((algorithm) == HAL_HASH_ALGO_SHA224) \
                                      || ((algorithm) == HAL_HASH_ALGO_SHA256) \
                                      || ((algorithm) == HAL_HASH_ALGO_MD5))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup HASH_Exported_Functions HASH Exported Functions
  * @{
  */
/** @addtogroup HASH_Exported_Functions_Group1
  * @{
This section provides functions allowing to:
- Initialize the HASH handle and associate it to a given HASH peripheral instance.
- DeInitialize the HASH peripheral.
  */
/**
  * @brief Initialize the selected HAL HASH handle and associate an HASH peripheral instance.
  * @param  hhash             Pointer to a hal_hash_handle_t structure.
  * @param  instance          HASH instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            HASH handle has been correctly initialized.
  */
hal_status_t HAL_HASH_Init(hal_hash_handle_t *hhash, hal_hash_t instance)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(IS_HASH_ALL_INSTANCE((HASH_TypeDef *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hhash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  /* Associate physical instance to logical object */
  hhash->instance = instance;

#if defined (USE_HAL_HASH_CLK_ENABLE_MODEL) && (USE_HAL_HASH_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_PERIPH_ONLY)
#if defined(HASH)
  HAL_RCC_HASH_EnableClock();
#endif /* HASH */
#endif /* USE_HAL_HASH_CLK_ENABLE_MODEL */

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  hhash->p_input_cplt_callback   = HAL_HASH_InputCpltCallback;
  hhash->p_digest_cplt_callback  = HAL_HASH_DigestCpltCallback;
  hhash->p_error_callback        = HAL_HASH_ErrorCallback;
  hhash->p_suspend_cplt_callback = HAL_HASH_SuspendCallback;
  hhash->p_abort_cplt_callback   = HAL_HASH_AbortCallback;
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
  hhash->last_error_codes = HAL_HASH_ERROR_NONE;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

#if defined(USE_HAL_HASH_USER_DATA) && (USE_HAL_HASH_USER_DATA == 1)
  hhash->p_user_data = NULL;
#endif /* USE_HAL_HASH_USER_DATA */

  hhash->global_state = HAL_HASH_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief DeInitialize the HASH peripheral.
  * @param hhash Pointer to a hal_hash_handle_t structure.
  */
void HAL_HASH_DeInit(hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(IS_HASH_ALL_INSTANCE(HASH_GET_INSTANCE(hhash)));

#if defined(USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  if ((HASH_GET_INSTANCE(hhash)->CR & HASH_CR_DMAE) != 0U)
  {
    CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

    (void)HAL_DMA_Abort(hhash->hdma_in);
  }
#endif /* USE_HAL_HASH_DMA */

  hhash->phase                 = HASH_PHASE_READY;
  hhash->input_data_count_byte = 0U;
  hhash->update_flag           = 0U;
  hhash->input_size_byte       = 0U;
  hhash->suspend_request       = HASH_SUSPEND_NONE;
  hhash->dma_operation_active  = 0U;
  hhash->global_state          = HAL_HASH_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to set and get the HASH configuration.
- Use the function HAL_HASH_SetConfig() to Configure HASH with the specified parameters in the hal_hash_config_t
  Parameters which are :
   - Data Swapping : no swap or half word swap or bit swap or byte swap.
   - algorithm : MD5 or SHA1 or SH224 or SH256.
- Use the function HAL_HASH_GetConfig() to retrieve the HAL HASH configuration.
  */
/**
  * @brief Configure the HASH according to the specified parameters in the hal_hash_config_t.
  * @param  hhash             Pointer to a hal_hash_handle_t structure
  * @param  p_config          Pointer to a hal_hash_config_t structure that contains the configuration for HASH module.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            HASH instance has been correctly configured.
  */
hal_status_t HAL_HASH_SetConfig(hal_hash_handle_t *hhash, const hal_hash_config_t *p_config)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_HASH_DATA_SWAPPING(p_config->data_swapping));
  ASSERT_DBG_PARAM(IS_HASH_ALGORITHM(p_config->algorithm));

  ASSERT_DBG_STATE(hhash->global_state, ((uint32_t)HAL_HASH_STATE_INIT) | (uint32_t)HAL_HASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hhash == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  /* Set the data type and algorithm */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DATATYPE | HASH_CR_ALGO | HASH_CR_INIT,
             (((uint32_t)p_config->data_swapping | (uint32_t)p_config->algorithm)));

  hhash->phase           = HASH_PHASE_READY;
  hhash->suspend_request = HASH_SUSPEND_NONE;
  hhash->global_state    = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get HASH Configuration parameters.
  * @param hhash    Pointer to a hal_hash_handle_t structure.
  * @param p_config Pointer to a hal_hash_config_t structure.
  */
void HAL_HASH_GetConfig(hal_hash_handle_t *hhash, hal_hash_config_t *p_config)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE | (uint32_t)HAL_HASH_STATE_ACTIVE);

  p_config->data_swapping = (hal_hash_data_swapping_t)(uint32_t)((HASH_GET_INSTANCE(hhash)->CR) & (HASH_CR_DATATYPE));
  p_config->algorithm = (hal_hash_algo_t)(uint32_t)((HASH_GET_INSTANCE(hhash)->CR) & (HASH_CR_ALGO));
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group3
  * @{
This section provides API allowing to calculate the hash value using one of the HASH algorithms supported by
the peripheral.

For a single buffer to be hashed, user can resort to one of three processing functions available:
- Polling mode   : HAL_HASH_Compute()
- Interrupt mode : HAL_HASH_Compute_IT()
- DMA mode       : HAL_HASH_Compute_DMA()

In case of multi-buffer HASH processing (a single digest is computed while several buffers are fed to the peripheral),
the user can resort to successive calls to :
- Polling mode : Call HAL_HASH_Update() to continue HASH update process.
- Interrupt mode : Call HAL_HASH_Update_IT() to continue HASH update process.
- DMA mode: Call HAL_HASH_Update_DMA() to continue HASH update process.

To retrieve the digest computation, call HAL_HASH_Finish().
  */
/**
  * @brief Compute HASH input buffer in polling mode then retrieve the computed digest in the output buffer.
  * @param  hhash              Pointer to a hal_hash_handle_t structure.
  * @param  p_input_buffer     Pointer to the input buffer (buffer to be hashed).
  * @param  input_size_byte    length of the input buffer in bytes.
  * @param  p_output_buffer    Pointer to the computed digest.
  * @param  p_output_size_byte Pointer to the length of the computed digest in bytes.
  * @param  timeout_ms         Specify timeout value in millisecond
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  * @retval HAL_TIMEOUT        A timeout has occurred.
  * @retval HAL_BUSY           Process is already ongoing.
  * @retval HAL_OK             Operation completed.
  */
hal_status_t HAL_HASH_Compute(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                              void *p_output_buffer, uint32_t *p_output_size_byte, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_input_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_input_buffer == NULL) || (input_size_byte == 0U) || (p_output_buffer == NULL)
      || (p_output_size_byte == NULL) || (hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->p_input_buff          = (const uint8_t *)p_input_buffer;
  hhash->p_output_buff         = (uint8_t *)p_output_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->p_output_size_byte    = p_output_size_byte;

  MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT | HASH_CR_MODE, HASH_CR_INIT);

  /* Configure the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * (input_size_byte % 4U));

  hhash->phase = HASH_PHASE_PROCESS;

  (void)HASH_Write_Data(hhash, (const uint8_t *)p_input_buffer, input_size_byte, HASH_COMPUTE_PROCESS);

  /* Start the message padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_DCI, HASH_FLAG_STATE_RESET, timeout_ms) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  HASH_GetDigestMsg(hhash, (const uint8_t *)p_output_buffer, HAL_HASH_GetDigestLength(hhash));
  *p_output_size_byte = HAL_HASH_GetDigestLength(hhash);

  hhash->phase = HASH_PHASE_READY;
  hhash->global_state = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Compute HASH input buffer in interrupt mode then retrieve the computed digest in the output buffer.
  * @param  hhash              Pointer to a hal_hash_handle_t structure.
  * @param  p_input_buffer     Pointer to the input buffer (buffer to be hashed).
  * @param  input_size_byte    length of the input buffer in bytes.
  * @param  p_output_buffer    Pointer to the computed digest.
  * @param  p_output_size_byte Pointer to the length of the computed digest in bytes.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            Operation started correctly.
  */
hal_status_t HAL_HASH_Compute_IT(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                 void *p_output_buffer, uint32_t *p_output_size_byte)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_input_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_input_buffer == NULL) || (input_size_byte == 0U) || (p_output_buffer == NULL)
      || (p_output_size_byte == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->input_data_count_byte = 0U;
  hhash->p_input_buff          = (const uint8_t *)p_input_buffer;
  hhash->p_output_buff         = (uint8_t *)p_output_buffer;
  hhash->input_size_byte       = input_size_byte;
  hhash->p_output_size_byte    = p_output_size_byte;
  hhash->update_flag           = 0U;

  MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT | HASH_CR_MODE, HASH_CR_INIT);

  /* Configure the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * (input_size_byte % 4U));
  hhash->phase = HASH_PHASE_PROCESS;

  if (HASH_WriteData_IT(hhash, HASH_COMPUTE_PROCESS) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;

    return HAL_ERROR;
  }

  HAL_HASH_EnableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);

  return HAL_OK;
}

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/**
  * @brief Compute HASH input buffer in DMA mode then retrieve the computed digest in the output buffer.
  * @param  hhash              Pointer to a hal_hash_handle_t structure.
  * @param  p_input_buffer     pointer to the input buffer (buffer to be hashed).
  * @param  input_size_byte    length of the input buffer in bytes.
  * @param  p_output_buffer    Pointer to the computed digest.
  * @param  p_output_size_byte Pointer to the length of the computed digest in bytes.
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  * @retval HAL_ERROR          An error has occurred.
  * @retval HAL_BUSY           Process is already ongoing.
  * @retval HAL_OK             Operation started correctly.
  */
hal_status_t HAL_HASH_Compute_DMA(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                  void *p_output_buffer, uint32_t *p_output_size_byte)
{
  uint32_t input_addr = (uint32_t)p_input_buffer;
  uint32_t tmp_input_size;

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_input_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_input_buffer == NULL) || (input_size_byte == 0U) || (p_output_buffer == NULL)
      || (p_output_size_byte == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
  hhash->last_error_codes = HAL_HASH_ERROR_NONE;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

  hhash->p_input_buff          = (const uint8_t *)p_input_buffer;
  hhash->p_output_buff         = (uint8_t *)p_output_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->p_output_size_byte    = p_output_size_byte;
  hhash->dma_operation_active  = 1U;

  hhash->hdma_in->p_xfer_cplt_cb  = HASH_DMAXferCplt;
  hhash->hdma_in->p_xfer_error_cb = HASH_DMAError;
  hhash->hdma_in->p_xfer_abort_cb = HASH_DMAAbort;

  MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT | HASH_CR_MODE, HASH_CR_INIT);
  hhash->phase = HASH_PHASE_PROCESS;

  /* Configure the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->input_size_byte) % 4U));

  tmp_input_size = (((hhash->input_size_byte % 4U) != 0U) ?
                    (hhash->input_size_byte + (4U - (hhash->input_size_byte % 4U))) : (hhash->input_size_byte));

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hhash->hdma_in, input_addr,
                                     (uint32_t) &((HASH_TypeDef *)((uint32_t)(hhash)->instance))->DIN, tmp_input_size,
                                     HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
    hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif /* USE_HAL_HASH_DMA */

/**
  * @brief HASH update process in polling mode with several input buffers.
  * @param  hhash              Pointer to a hal_hash_handle_t structure.
  * @param  p_add_input_buffer Pointer to the input buffer (buffer to be hashed).
  * @param  input_size_byte    length of the input buffer in bytes.
  * @param  timeout_ms         Specify timeout value in millisecond.
  * @note   Consecutive calls to HAL_HASH_Update() can be used to feed several input buffersback-to-back to the
  *         peripheral that will yield a single HASH signature once all buffers have been entered.
  *         Wrap-up of input buffers feeding and retrieval of digest is done by a call to HAL_HASH_Finish().
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  * @retval HAL_TIMEOUT        A timeout has occurred.
  * @retval HAL_BUSY           Process is already ongoing.
  * @retval HAL_OK             Input buffer fed correctly.
  */
hal_status_t HAL_HASH_Update(hal_hash_handle_t *hhash, const void *p_add_input_buffer, uint32_t input_size_byte,
                             uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_add_input_buffer != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_add_input_buffer == NULL) || (input_size_byte == 0U) || (hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->p_input_buff          = (const uint8_t *)p_add_input_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;

  if (hhash->phase == HASH_PHASE_READY)
  {
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT | HASH_CR_MODE, HASH_CR_INIT);
    hhash->phase = HASH_PHASE_PROCESS;
  }

  (void)HASH_Write_Data(hhash, (const uint8_t *)p_add_input_buffer, input_size_byte, HASH_UPDATE_PROCESS);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, timeout_ms) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  hhash->global_state = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  HASH update process in interrupt mode several input buffers.
  * @param  hhash              Pointer to a hal_hash_handle_t structure.
  * @param  p_add_input_buffer Pointer to the input buffer (buffer to be hashed).
  * @param  input_size_byte    length of the input buffer in bytes.
  * @note   Consecutive calls to HAL_HASH_Update_IT() can be used to feed several input buffers back-to-back
  *         to the peripheral that will yield a single HASH signature once all buffers have been entered.
  *         Wrap-up of input buffers feeding and retrieval of digest is done by a call to HAL_HASH_Finish().
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  * @retval HAL_ERROR          An error has occurred.
  * @retval HAL_BUSY           Process is already ongoing.
  * @retval HAL_OK             The update of the given buffer has been processed correctly.
  */
hal_status_t HAL_HASH_Update_IT(hal_hash_handle_t *hhash, const void *p_add_input_buffer, uint32_t input_size_byte)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_add_input_buffer != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_add_input_buffer == NULL) || (input_size_byte == 0U) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  if (hhash->phase == HASH_PHASE_READY)
  {
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT | HASH_CR_MODE, HASH_CR_INIT);
    hhash->phase = HASH_PHASE_PROCESS;
  }

  hhash->p_input_buff = (const uint8_t *)p_add_input_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte = input_size_byte;
  hhash->update_flag = 1U;

  if (HASH_WriteData_IT(hhash, HASH_UPDATE_PROCESS) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_HASH_EnableIT(hhash, HAL_HASH_IT_DIN);

  return HAL_OK;
}

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/**
  * @brief  HASH update process in DMA mode with several input buffers.
  * @param  hhash              Pointer to a hal_hash_handle_t structure.
  * @param  p_add_input_buffer Pointer to the input buffer (buffer to be hashed).
  * @param  input_size_byte    length of the input buffer in bytes.
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  * @retval HAL_ERROR          An error has occurred.
  * @retval HAL_BUSY           Process is already ongoing.
  * @retval HAL_OK             The update of the given buffer has been processed correctly.
  */
hal_status_t HAL_HASH_Update_DMA(hal_hash_handle_t *hhash, const void *p_add_input_buffer, uint32_t input_size_byte)
{
  uint32_t tmp_input_addr = (uint32_t)p_add_input_buffer;
  uint32_t tmp;
  uint32_t total_size;
  uint32_t tmp_input_size;
  uint8_t remain_size;

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_add_input_buffer != NULL);
  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
  || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_add_input_buffer == NULL) || (input_size_byte == 0U) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  tmp_input_size               = input_size_byte;
  hhash->p_input_buff          = (const uint8_t *)p_add_input_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->dma_operation_active  = 1U;

  hhash->hdma_in->p_xfer_cplt_cb  = HASH_DMAXferCplt;
  hhash->hdma_in->p_xfer_error_cb = HASH_DMAError;
  hhash->hdma_in->p_xfer_abort_cb = HASH_DMAAbort;

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

  if (hhash->phase == HASH_PHASE_READY)
  {
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT | HASH_CR_MODE, HASH_CR_INIT);
    hhash->phase = HASH_PHASE_PROCESS;
    SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT);
  }

  /* Process the remaining bytes of the previous buffer */
  if (hhash->remain_bytes_number > 0U)
  {
    tmp = 0U;
    for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
    {
      tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
    }

    for (uint32_t i = 0U; (i < (4U - (uint32_t)hhash->remain_bytes_number)) && (i < tmp_input_size); i++)
    {
      tmp |= (uint32_t)(*(uint8_t *)tmp_input_addr) << ((i + hhash->remain_bytes_number) * 8U);
      tmp_input_addr += 1U;
      hhash->input_data_count_byte += 1U;
    }

    HASH_GET_INSTANCE(hhash)->DIN = tmp;

    tmp_input_size -= (tmp_input_size > (4U - (uint32_t)hhash->remain_bytes_number)) ?
                      (4U - (uint32_t)hhash->remain_bytes_number) : tmp_input_size;
    hhash->remain_bytes_number = 0U;
  }

  hhash->input_size_byte = tmp_input_size;

  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 0U);
  total_size = tmp_input_size;
  remain_size = (uint8_t)(total_size % 4U);
  tmp_input_size = total_size - remain_size;

  if (tmp_input_size > 0U)
  {
    if (HAL_DMA_StartPeriphXfer_IT_Opt(hhash->hdma_in,
                                       tmp_input_addr,
                                       (uint32_t) &((HASH_TypeDef *)((uint32_t)(hhash)->instance))->DIN,
                                       tmp_input_size,
                                       HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
      hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */
      hhash->global_state = HAL_HASH_STATE_IDLE;
      return HAL_ERROR;
    }
  }
  else
  {
    hhash->global_state = HAL_HASH_STATE_IDLE;
  }

  /* Store remaining bytes in remain_bytes */
  if (remain_size > 0U)
  {
    for (uint32_t i = 0U; i < remain_size; i++)
    {
      hhash->remain_bytes[i] = ((uint8_t *)tmp_input_addr)[tmp_input_size + i];
    }
    hhash->remain_bytes_number = remain_size;
  }

  return HAL_OK;
}
#endif /* USE_HAL_HASH_DMA */

/**
  * @brief Finish HASH update process.
  * @param  hhash               Pointer to a hal_hash_handle_t structure.
  * @param  p_output_buffer     Pointer to the computed digest.
  * @param  p_output_size_byte  Pointer to the length of the computed digest in bytes.
  * @param  timeout_ms          Specify timeout value in millisecond.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  * @retval HAL_TIMEOUT         A timeout has occurred.
  * @retval HAL_BUSY            Process is already ongoing.
  * @retval HAL_OK              Hash operation correctly completed and digest available in the output buffer.
  */
hal_status_t HAL_HASH_Finish(hal_hash_handle_t *hhash, void *p_output_buffer, uint32_t *p_output_size_byte,
                             uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_output_buffer == NULL) || (p_output_size_byte == NULL) || (hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->p_output_buff = (uint8_t *)p_output_buffer;
  hhash->p_output_size_byte = p_output_size_byte;
  hhash->update_flag = 0U;

  if ((hhash->input_data_count_byte != hhash->input_size_byte) && (hhash->remain_bytes_number != 0U))
  {
    /* Configure the number of valid bits in last word of the message */
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, (8U * (uint32_t)hhash->remain_bytes_number));

    (void)HASH_Write_Data(hhash, (const uint8_t *)hhash->remain_bytes, hhash->remain_bytes_number, HASH_FINISH_PROCESS);
  }
  else
  {
    /* Configure the number of valid bits in last word of the message */
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * (hhash->input_size_byte % 4U));
  }

  /* Start the message padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_DCI, HASH_FLAG_STATE_RESET, timeout_ms) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  if (IS_BIT_SET(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT))
  {
    CLEAR_BIT(((HASH_TypeDef *)((uint32_t)(hhash->instance)))->CR, HASH_CR_MDMAT);
  }

  HASH_GetDigestMsg(hhash, (const uint8_t *)p_output_buffer, HAL_HASH_GetDigestLength(hhash));
  *p_output_size_byte = HAL_HASH_GetDigestLength(hhash);

  hhash->dma_operation_active = 1U;
  hhash->remain_bytes_number = 0U;
  hhash->phase = HASH_PHASE_READY;
  hhash->global_state = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to set and get the HASH HMAC configuration.
- Use the function HAL_HASH_HMAC_SetConfig() to Configure HASH HMAC with the specified parameters in the
  hal_hash_hmac_config_t Parameters which are :
   - Data Swapping : no swap or half word swap or bit swap or byte swap.
   - algorithm : MD5 or SHA1 or SH224 or SH256.
   - Key and key size in byte to use for the HMAC operation
- Use the function HAL_HASH_HMAC_GetConfig() to retrieve the HAL HASH HMAC configuration.
  */
/**
  * @brief Configure the HASH HMAC according to the specified parameters in the hal_hash_hmac_config_t.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_config           Pointer to a hal_hash_hmac_config_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_ERROR         A timeout has occurred.
  * @retval HAL_OK            Operation started correctly.
  */
hal_status_t HAL_HASH_HMAC_SetConfig(hal_hash_handle_t *hhash, const hal_hash_hmac_config_t *p_config)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_HASH_DATA_SWAPPING(p_config->data_swapping));
  ASSERT_DBG_PARAM(IS_HASH_ALGORITHM(p_config->algorithm));
  ASSERT_DBG_PARAM(p_config->p_key != NULL);
  ASSERT_DBG_PARAM(p_config->key_size_byte != 0U);

  ASSERT_DBG_STATE(hhash->global_state, ((uint32_t)HAL_HASH_STATE_INIT) | (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hhash == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  /* Set the data type and algorithm */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DATATYPE | HASH_CR_ALGO | HASH_CR_INIT,
             (((uint32_t)p_config->data_swapping | (uint32_t)p_config->algorithm)));

  hhash->phase = HASH_PHASE_READY;

  hhash->p_key_buff            = p_config->p_key;
  hhash->key_size_byte         = p_config->key_size_byte;
  hhash->p_key_saved           = p_config->p_key;
  hhash->input_data_count_byte = 0U;
  HASH_UpdateCRAccordingAlgo(hhash, hhash->key_size_byte);

  hhash->phase = HASH_PHASE_PROCESS;

  /* Configure the number of valid bits in last word of the Key */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((p_config->key_size_byte) % 4U));

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT);
  (void)HASH_WriteKey(hhash, p_config->p_key, p_config->key_size_byte);

  /* Start the Key padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, HASH_TIMEOUT_MS) != HAL_OK)
  {
    hhash->phase = HASH_PHASE_READY;
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_ERROR;
  }

  hhash->phase           = HASH_PHASE_HMAC_STEP_2;
  hhash->suspend_request = HASH_SUSPEND_NONE;
  hhash->global_state    = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get HASH HMAC Configuration parameters.
  * @param hhash       Pointer to a hal_hash_handle_t structure.
  * @param p_config    Pointer to a hal_hash_hmac_config_t structure.
  */
void HAL_HASH_HMAC_GetConfig(hal_hash_handle_t *hhash, hal_hash_hmac_config_t *p_config)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE | (uint32_t)HAL_HASH_STATE_ACTIVE);

  p_config->data_swapping = (hal_hash_data_swapping_t)(uint32_t)((HASH_GET_INSTANCE(hhash)->CR) & (HASH_CR_DATATYPE));
  p_config->algorithm     = (hal_hash_algo_t)(uint32_t)((HASH_GET_INSTANCE(hhash)->CR) & (HASH_CR_ALGO));
  p_config->p_key         = hhash->p_key_saved;
  p_config->key_size_byte = hhash->key_size_byte;
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group5
  * @{
This section provides API allowing to calculate the HMAC (keyed-hash message authentication code).

To calculate the HMAC for a single buffer, user can resort to one of three processing functions available:
- Polling mode : HAL_HASH_HMAC_Compute()
- Interrupt mode : HAL_HASH_HMAC_Compute_IT()
- DMA mode : HAL_HASH_HMAC_Compute_DMA()

In case of multi-buffer HMAC processing (a single digest is computed while several buffers are fed to the peripheral),
the user can resort to successive calls to :
- Polling mode : Call HAL_HASH_HMAC_Update() to continue HASH HMAC update process.
- Interrupt mode : Call HAL_HASH_HMAC_Update_IT() to continue HASH HMAC update process.
- DMA mode: Call HAL_HASH_HMAC_Update_DMA() to continue HASH HMAC update process.

To retrieve the digest computation, call HAL_HASH_HMAC_Finish().
  */
/**
  * @brief Compute HASH HMAC input buffer in polling mode, then retrieve the computed digest in the output buffer.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_input_buffer     Pointer to the input buffer (buffer to be hashed).
  * @param input_size_byte    length of the input buffer in bytes.
  * @param p_output_buffer    Pointer to the computed digest.
  * @param p_output_size_byte Pointer to the length of the computed digest in bytes.
  * @param timeout_ms         Specify timeout value in millisecond.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_HASH_HMAC_Compute(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                   void *p_output_buffer, uint32_t *p_output_size_byte, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_input_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_input_buffer == NULL) || (input_size_byte == 0U) || (p_output_buffer == NULL)
      || (p_output_size_byte == NULL) || (hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->phase                 = HASH_PHASE_READY;
  hhash->p_input_buff          = (const uint8_t *)p_input_buffer;
  hhash->p_output_buff         = (uint8_t *)p_output_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->p_output_size_byte    = p_output_size_byte;

  HASH_UpdateCRAccordingAlgo(hhash, hhash->key_size_byte);

  /* Configure the number of valid bits in last word of the Key */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));

  hhash->phase = HASH_PHASE_PROCESS;
  (void)HASH_Write_Data(hhash, hhash->p_key_saved, hhash->key_size_byte, HASH_COMPUTE_PROCESS);

  /* Start the Key padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, timeout_ms) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  /* Configure the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * (input_size_byte % 4U));

  (void)HASH_Write_Data(hhash, (const uint8_t *)p_input_buffer, input_size_byte, HASH_COMPUTE_PROCESS);

  /* Start the message padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, timeout_ms) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  /* Configure the number of valid bits in last word of the Key */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));

  (void)HASH_Write_Data(hhash, hhash->p_key_saved, hhash->key_size_byte, HASH_COMPUTE_PROCESS);

  /* Start the Key padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_DCI, HASH_FLAG_STATE_RESET, timeout_ms) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  HASH_GetDigestMsg(hhash, (const uint8_t *)p_output_buffer, HAL_HASH_GetDigestLength(hhash));
  *p_output_size_byte = HAL_HASH_GetDigestLength(hhash);

  hhash->phase           = HASH_PHASE_READY;
  hhash->global_state    = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Compute HASH HMAC input buffer in interrupt mode, retrieve the computed digest in the output buffer.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_input_buffer     Pointer to the input buffer (buffer to be hashed).
  * @param input_size_byte    length of the input buffer in bytes.
  * @param p_output_buffer    Pointer to the computed digest.
  * @param p_output_size_byte Pointer to the length of the computed digest in bytes.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            Operation started correctly.
  */
hal_status_t HAL_HASH_HMAC_Compute_IT(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                      void *p_output_buffer, uint32_t *p_output_size_byte)
{

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_input_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_input_buffer == NULL) || (input_size_byte == 0U) || (p_output_buffer == NULL)
      || (p_output_size_byte == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->phase = HASH_PHASE_READY;

  hhash->p_input_buff          = (const uint8_t *)p_input_buffer;
  hhash->p_output_buff         = (uint8_t *)p_output_buffer;
  hhash->p_key_buff            = hhash->p_key_saved;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->p_output_size_byte    = p_output_size_byte;

  HASH_UpdateCRAccordingAlgo(hhash, hhash->key_size_byte);

  /* Configure the number of valid bits in last word of the Key */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));

  hhash->phase = HASH_PHASE_PROCESS;

  if (HASH_HMAC_WriteData_IT(hhash, HASH_COMPUTE_PROCESS) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_HASH_EnableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);

  return HAL_OK;
}

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/**
  * @brief Compute HASH HMAC input buffer in DMA mode, then retrieve the computed digest in the output buffer.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_input_buffer     Pointer to the input buffer (buffer to be hashed).
  * @param input_size_byte    length of the input buffer in bytes.
  * @param p_output_buffer    Pointer to the computed digest.
  * @param p_output_size_byte Pointer to the length of the computed digest in bytes.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            Operation started correctly.
  */
hal_status_t HAL_HASH_HMAC_Compute_DMA(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                       void *p_output_buffer, uint32_t *p_output_size_byte)
{
  uint32_t src_addr;
  uint32_t size_byte;

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_input_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_input_buffer == NULL) || (input_size_byte == 0U) || (p_output_buffer == NULL)
      || (p_output_size_byte == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
  hhash->last_error_codes = HAL_HASH_ERROR_NONE;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

  hhash->p_input_buff          = (const uint8_t *)p_input_buffer;
  hhash->p_output_buff         = (uint8_t *)p_output_buffer;
  hhash->p_key_buff            = hhash->p_key_saved;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->p_output_size_byte    = p_output_size_byte;
  hhash->dma_operation_active  = 1U;

  CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT);

  if (hhash->phase == HASH_PHASE_READY)
  {
    HASH_UpdateCRAccordingAlgo(hhash, hhash->key_size_byte);

    /* Configure the number of valid bits in last word of the Key */
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));

    (void)HASH_WriteKey(hhash, hhash->p_key_saved, hhash->key_size_byte);

    /* Start the Key padding then the Digest calculation */
    SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

    if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, HASH_TIMEOUT_MS) != HAL_OK)
    {
      hhash->phase           = HASH_PHASE_READY;
      hhash->global_state    = HAL_HASH_STATE_IDLE;
      return HAL_ERROR;
    }
  }

  hhash->phase = HASH_PHASE_HMAC_STEP_2;
  /* Configure the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->input_size_byte) % 4U));

  hhash->hdma_in->p_xfer_cplt_cb = HASH_DMAXferCplt;
  hhash->hdma_in->p_xfer_error_cb = HASH_DMAError;
  hhash->hdma_in->p_xfer_abort_cb = HASH_DMAAbort;

  src_addr = (uint32_t)p_input_buffer;
  size_byte =
    (((hhash->input_size_byte % 4U) != 0U) ?
     (hhash->input_size_byte + (4U - (hhash->input_size_byte % 4U))) : (hhash->input_size_byte));

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hhash->hdma_in, src_addr,
                                     (uint32_t) &((HASH_TypeDef *)((uint32_t)(hhash)->instance))->DIN, size_byte,
                                     HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
    hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_ERROR;
  }

  return HAL_OK;
}
#endif /* USE_HAL_HASH_DMA */

/**
  * @brief HASH HMAC update process in polling mode with several input buffers.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_add_input_buffer Pointer to the input buffer (buffer to be hashed).
  * @param input_size_byte    length of the input buffer in bytes.
  * @param timeout_ms         Specify timeout value in millisecond.
  * @note  Consecutive calls to HAL_HASH_HMAC_Update() can be used to feed several input buffers back-to-back to
  *        the peripheral that will yield a single HASH signature once all buffers have been entered. Wrap-up of input
  *        buffers feeding and retrieval of digest is done by a call to HAL_HASH_HMAC_Finish().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            The update of the given buffer has been processed correctly.
  */
hal_status_t HAL_HASH_HMAC_Update(hal_hash_handle_t *hhash, const void *p_add_input_buffer,
                                  uint32_t input_size_byte, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_add_input_buffer != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_add_input_buffer == NULL) || (input_size_byte == 0U) || (hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->p_input_buff = (const uint8_t *)p_add_input_buffer;
  hhash->input_size_byte = input_size_byte;
  hhash->input_data_count_byte = 0U;

  /* Change the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 0U);

  (void)HASH_Write_Data(hhash, (const uint8_t *)p_add_input_buffer, input_size_byte, HASH_UPDATE_PROCESS);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, timeout_ms) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  hhash->global_state    = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief HASH HMAC update process in IT mode with several input buffers.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_add_input_buffer Pointer to the input buffer (buffer to be hashed).
  * @param input_size_byte    length of the input buffer in bytes.
  * @note  Consecutive calls to HAL_HASH_HMAC_Update_IT() can be used to feed several input buffers back-to-back to
  *        the peripheral that will yield a single HASH signature once all buffers have been entered. Wrap-up of input
  *        buffers feeding and retrieval of digest is done by a call to HAL_HASH_HMAC_Finish().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            The update of the given buffer has been processed correctly.
  */
hal_status_t HAL_HASH_HMAC_Update_IT(hal_hash_handle_t *hhash, const void *p_add_input_buffer,
                                     uint32_t input_size_byte)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_add_input_buffer != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_add_input_buffer == NULL) || (input_size_byte == 0U) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->p_input_buff          = (const uint8_t *)p_add_input_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->update_flag           = 1U;

  if (HASH_HMAC_WriteData_IT(hhash, HASH_UPDATE_PROCESS) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_ERROR;
  }

  if (hhash->remain_bytes_number == 0U)
  {
    HAL_HASH_EnableIT(hhash, HAL_HASH_IT_DIN);
  }

  return HAL_OK;
}

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/**
  * @brief HASH HMAC update process in DMA mode with several input buffers.
  * @param hhash              Pointer to a hal_hash_handle_t structure.
  * @param p_add_input_buffer Pointer to the input buffer (buffer to be hashed).
  * @param input_size_byte    length of the input buffer in bytes.
  * @note  Multi-buffer HMAC processing is possible, consecutive calls to HAL_HASH_HMAC_Update_DMA() can be used to
  *        feed several input buffers back-to-back to the peripheral that will yield a single HASH signature once all
  *        buffers have been entered. Wrap-up of input buffers feeding and retrieval of digest is done by a call to
  *        HAL_HASH_HMAC_Finish().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         An error has occurred.
  * @retval HAL_BUSY          Process is already ongoing.
  * @retval HAL_OK            The update of the given buffer has been processed correctly.
  */
hal_status_t HAL_HASH_HMAC_Update_DMA(hal_hash_handle_t *hhash, const void *p_add_input_buffer,
                                      uint32_t input_size_byte)
{
  uint32_t tmp_input_addr = (uint32_t)p_add_input_buffer;
  uint32_t tmp_input_size;
  uint32_t tmp;
  uint32_t total_size;
  uint8_t remain_size;

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_add_input_buffer != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_add_input_buffer == NULL) || (input_size_byte == 0U) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  tmp_input_size               = input_size_byte;
  hhash->p_input_buff          = (const uint8_t *)p_add_input_buffer;
  hhash->input_data_count_byte = 0U;
  hhash->input_size_byte       = input_size_byte;
  hhash->dma_operation_active  = 1U;

  hhash->hdma_in->p_xfer_cplt_cb  = HASH_DMAXferCplt;
  hhash->hdma_in->p_xfer_error_cb = HASH_DMAError;
  hhash->hdma_in->p_xfer_abort_cb = HASH_DMAAbort;

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT);

  /* Process the remaining bytes of the previous buffer */
  if (hhash->remain_bytes_number > 0U)
  {
    tmp = 0U;
    for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
    {
      tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
    }

    for (uint32_t i = 0U; (i < (4U - (uint32_t)hhash->remain_bytes_number)) && (i < tmp_input_size); i++)
    {
      tmp |= (uint32_t)(*(uint8_t *)tmp_input_addr) << ((i + hhash->remain_bytes_number) * 8U);
      tmp_input_addr += 1U;
      hhash->input_data_count_byte += 1U;
    }

    MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 0U);

    HASH_GET_INSTANCE(hhash)->DIN = tmp;

    tmp_input_size -= (tmp_input_size > (4U - (uint32_t)hhash->remain_bytes_number)) ?
                      (4U - (uint32_t)hhash->remain_bytes_number) : tmp_input_size;
    hhash->remain_bytes_number = 0U;
  }

  /* Configure the number of valid bits in last word of the message */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 0U);

  total_size = tmp_input_size;
  remain_size = (uint8_t)(total_size % 4U);
  tmp_input_size = total_size - remain_size;

  if (tmp_input_size > 0U)
  {
    SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

    if (HAL_DMA_StartPeriphXfer_IT_Opt(hhash->hdma_in,
                                       tmp_input_addr,
                                       (uint32_t) &((HASH_TypeDef *)((uint32_t)(hhash)->instance))->DIN,
                                       tmp_input_size,
                                       HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
      hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */
      hhash->global_state    = HAL_HASH_STATE_IDLE;
      return HAL_ERROR;
    }
  }
  else
  {
    hhash->global_state    = HAL_HASH_STATE_IDLE;
  }

  /* Store remaining bytes */
  if (remain_size > 0U)
  {
    for (uint32_t i = 0U; i < remain_size; i++)
    {
      hhash->remain_bytes[i] = ((uint8_t *)tmp_input_addr)[tmp_input_size + i];
    }
    hhash->remain_bytes_number = remain_size;
  }

  return HAL_OK;
}
#endif /* USE_HAL_HASH_DMA */

/**
  * @brief Finish HASH update process.
  * @param  hhash               Pointer to a hal_hash_handle_t structure.
  * @param  p_output_buffer     Pointer to the computed digest.
  * @param  p_output_size_byte  Pointer to the length of the computed digest in bytes.
  * @param  timeout_ms          Specify timeout value in millisecond.
  * @retval HAL_INVALID_PARAM   Invalid parameter.
  * @retval HAL_TIMEOUT         A timeout has occurred.
  * @retval HAL_BUSY            Process is already ongoing.
  * @retval HAL_OK              Hash operation correctly completed and digest available in the output buffer.
  */
hal_status_t HAL_HASH_HMAC_Finish(hal_hash_handle_t *hhash, void *p_output_buffer, uint32_t *p_output_size_byte,
                                  uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_output_buffer != NULL);
  ASSERT_DBG_PARAM(p_output_size_byte != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((p_output_buffer == NULL) || (p_output_size_byte == NULL) || (hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_IDLE, HAL_HASH_STATE_ACTIVE);

  hhash->p_output_buff      = (uint8_t *)p_output_buffer;
  hhash->p_output_size_byte = p_output_size_byte;

  if ((hhash->input_data_count_byte != hhash->input_size_byte) && (hhash->remain_bytes_number != 0U))
  {
    hhash->input_data_count_byte = 0U;
    /* Configure the number of valid bits in last word of the message */
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, (8U * (uint32_t)hhash->remain_bytes_number));

    (void)HASH_Write_Data(hhash, (const uint8_t *)hhash->remain_bytes, hhash->remain_bytes_number, HASH_FINISH_PROCESS);
  }
  else
  {
    /* Configure the number of valid bits in last word of the message */
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 0U);
  }

  /* Start the message padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, timeout_ms) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  hhash->input_data_count_byte = 0U;
  /* Configure the number of valid bits in last word of the Key */
  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));
  (void)HASH_WriteKey(hhash, hhash->p_key_buff, hhash->key_size_byte);

  /* Start the Key padding then the Digest calculation */
  SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_DCI, HASH_FLAG_STATE_RESET, timeout_ms) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  if (IS_BIT_SET(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT))
  {
    CLEAR_BIT(((HASH_TypeDef *)((uint32_t)(hhash->instance)))->CR, HASH_CR_MDMAT);
  }

  HASH_GetDigestMsg(hhash, (const uint8_t *)p_output_buffer, HAL_HASH_GetDigestLength(hhash));
  *p_output_size_byte = HAL_HASH_GetDigestLength(hhash);

  hhash->update_flag          = 0U;
  hhash->remain_bytes_number  = 0U;
  hhash->dma_operation_active = 0U;
  hhash->phase                = HASH_PHASE_READY;
  hhash->global_state         = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group6
  * @{
This section provides functions allowing to:
- Abort in polling mode with HAL_HASH_Abort().
- Abort in IT and DMA mode with HAL_HASH_Abort_IT().
  */
/**
  * @brief Abort HASH/HMAC in polling mode.
  * @param  hhash       Pointer to a hal_hash_handle_t structure.
  * @param  timeout_ms  Specify timeout value in millisecond.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_TIMEOUT       A timeout has occurred.
  * @retval HAL_ERROR         In case of user timeout.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_HASH_Abort(hal_hash_handle_t *hhash, uint32_t timeout_ms)
{
  hal_hash_state_t tmp_state;

  ASSERT_DBG_PARAM(hhash != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_ACTIVE | (uint32_t)HAL_HASH_STATE_SUSPENDED);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hhash == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  tmp_state = hhash->global_state;
  hhash->global_state = HAL_HASH_STATE_ABORT;
  HAL_HASH_DisableIT(hhash, HAL_HASH_FLAG_DCI | HAL_HASH_FLAG_DINI);
  if (tmp_state == HAL_HASH_STATE_SUSPENDED)
  {
    HAL_HASH_ClearFlag(hhash, (uint32_t)HAL_HASH_FLAG_DCI | HAL_HASH_FLAG_DINI);
    /* Reset the hash processor core */
    SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT);
    hhash->input_data_count_byte = 0U;
    hhash->update_flag           = 0U;
    hhash->input_size_byte       = 0U;
    hhash->suspend_request       = HASH_SUSPEND_NONE;
    hhash->phase                 = HASH_PHASE_READY;
    hhash->global_state          = HAL_HASH_STATE_IDLE;
    return HAL_OK;
  }

#if defined(USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  if ((HASH_GET_INSTANCE(hhash)->CR & HASH_CR_DMAE) != 0U)
  {
    CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

    if (HAL_DMA_Abort(hhash->hdma_in) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
#endif /* USE_HAL_HASH_DMA */
  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_BUSY, HASH_FLAG_STATE_SET, timeout_ms) != HAL_OK)
  {
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  /* Reset the hash processor core */
  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT);
  HAL_HASH_ClearFlag(hhash, (uint32_t)HAL_HASH_FLAG_DCI | HAL_HASH_FLAG_DINI);

  hhash->global_state = HAL_HASH_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Abort HASH/HMAC in interrupt mode.
  * @param hhash Pointer to a hal_hash_handle_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_HASH_Abort_IT(hal_hash_handle_t *hhash)
{
  hal_hash_state_t tmp_state;

  ASSERT_DBG_PARAM(hhash != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE | (uint32_t)HAL_HASH_STATE_ACTIVE
                   | (uint32_t)HAL_HASH_STATE_SUSPENDED);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hhash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  tmp_state    = hhash->global_state;
  hhash->global_state    = HAL_HASH_STATE_ABORT;

  if (tmp_state == HAL_HASH_STATE_SUSPENDED)
  {
    HAL_HASH_DisableIT(hhash, HAL_HASH_FLAG_DCI | HAL_HASH_FLAG_DINI);
    HAL_HASH_ClearFlag(hhash, (uint32_t)HAL_HASH_FLAG_DCI | HAL_HASH_FLAG_DINI);
    /* Reset the hash processor core */
    SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT);
    hhash->input_data_count_byte = 0U;
    hhash->update_flag           = 0U;
    hhash->input_size_byte       = 0U;
    hhash->suspend_request       = HASH_SUSPEND_NONE;
    hhash->phase                 = HASH_PHASE_READY;
    hhash->global_state          = HAL_HASH_STATE_IDLE;
    return HAL_OK;
  }

#if defined(USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  if (((HASH_GET_INSTANCE(hhash)->CR & HASH_CR_DMAE) != 0U) || (hhash->dma_operation_active == 1U))
  {
    /* Disable the DMA transfer on the HASH side */
    CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);
    /* Disable the DMA transmit on the DMA side */
    (void)HAL_DMA_Abort_IT(hhash->hdma_in);
  }
#endif /* USE_HAL_HASH_DMA */

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group7
  * @{
This section provides HASH IRQ handler and callback functions.
- HAL_HASH_IRQHandler()         : HASH interrupt request.
- HAL_HASH_InputCpltCallback()  : Input data transfer complete callback.
- HAL_HASH_DigestCpltCallback() : Digest computation complete callback.
- HAL_HASH_ErrorCallback()      : HASH error callback.
- HAL_HASH_SuspendCallback()    : HASH suspend callback.
- HAL_HASH_AbortCallback()      : HASH abort callback.

The compilation define USE_HAL_HASH_REGISTER_CALLBACKS when set to 1 allows the user to register custom callbacks.
- Use Function HAL_HASH_RegisterInputCpltCallback() to register a user input complete callback.
- Use Function HAL_HASH_RegisterDigestComputationCpltCallback() to register a user digestcomputation complete callback.
- Use Function HAL_HASH_RegisterErrorCpltCallback() to register a user error callback.
- Use Function HAL_HASH_RegisterSuspendCpltCallback() to register a user suspend callback.
- Use Function HAL_HASH_RegisterAbortCpltCallback() to register a user abort callback.
- Use Function HAL_HASH_SetInDMA() to link the input FIFO HAL DMA handle into the HAL HASH handle.
  */
/**
  * @brief HASH interrupt request.
  * @param hhash Pointer to a hal_hash_handle_t structure.
  * @note  HAL_HASH_IRQHandler() handles interrupts in HMAC processing as well.
  */
void HAL_HASH_IRQHandler(hal_hash_handle_t *hhash)
{
  uint32_t itsource;
  uint32_t itflag;

  ASSERT_DBG_PARAM(hhash != NULL);

  itsource = HASH_GET_INSTANCE(hhash)->IMR;
  itflag   = HASH_GET_INSTANCE(hhash)->SR;

  if ((itflag & HAL_HASH_FLAG_DCI) == HAL_HASH_FLAG_DCI)
  {
    HASH_GetDigestMsg(hhash, hhash->p_output_buff, HAL_HASH_GetDigestLength(hhash));
    *hhash->p_output_size_byte = HAL_HASH_GetDigestLength(hhash);
    HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
    hhash->p_digest_cplt_callback(hhash);
#else
    HAL_HASH_DigestCpltCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
    return;
  }

  /* If peripheral ready to accept new data */
  if ((itflag & HAL_HASH_FLAG_DINI) == HAL_HASH_FLAG_DINI)
  {
    if ((itsource & HAL_HASH_IT_DIN) == HAL_HASH_IT_DIN)
    {
      if (hhash->global_state == HAL_HASH_STATE_ABORT)
      {
        HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
        hhash->global_state = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
        hhash->p_abort_cplt_callback(hhash);
#else
        HAL_HASH_AbortCallback(hhash);
#endif /* (USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1) */
      }
      else
      {
        if (READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MODE) == 0U)
        {
          if (HASH_WriteData_IT(hhash, hhash->operation_process) != HAL_OK)
          {
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
            hhash->p_error_callback(hhash);
#else
            HAL_HASH_ErrorCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
          }
        }
        else /* HMAC */
        {
          if (HASH_HMAC_WriteData_IT(hhash, hhash->operation_process) != HAL_OK)
          {
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
            hhash->p_error_callback(hhash);
#else
            HAL_HASH_ErrorCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
          }
        }
      }
    }
  }
}

/**
  * @brief Input data transfer complete callback.
  * @param hhash pointer to a hal_hash_handle_t structure.
  * @warning HAL_HASH_InputCpltCallback() is called when the complete input message has been fed to the peripheral.
  *          This API is invoked only when input data are entered under interruption or through DMA.
  * @warning In case of HASH or HMAC update DMA feeding case, HAL_HASH_InputCpltCallback() is
  *          called at the end of each buffer feeding to the peripheral.
  */
__WEAK void HAL_HASH_InputCpltCallback(hal_hash_handle_t *hhash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhash);

  /* WARNING: This function must not be modified, when the callback is needed,
    *          HAL_HASH_InputCpltCallback() can be implemented in the user file.
    */
}

/**
  * @brief Digest computation complete callback.
  * @param hhash pointer to a hal_hash_handle_t structure.
  * @note  HAL_HASH_DigestCpltCallback() is used under interruption, is not relevant with DMA.
  */
__WEAK void HAL_HASH_DigestCpltCallback(hal_hash_handle_t *hhash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhash);

  /* WARNING: This function must not be modified, when the callback is needed,
    *          HAL_HASH_DigestCpltCallback() can be implemented in the user file.
    */
}

/**
  * @brief HASH error callback.
  * @param hhash pointer to a hal_hash_handle_t structure.
  */
__WEAK void HAL_HASH_ErrorCallback(hal_hash_handle_t *hhash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhash);

  /* WARNING: This function must not be modified, when the callback is needed,
    *          HAL_HASH_ErrorCallback() can be implemented in the user file.
    */
}

/**
  * @brief HASH suspend callback.
  * @param hhash pointer to a hal_hash_handle_t structure.
  */
__WEAK void HAL_HASH_SuspendCallback(hal_hash_handle_t *hhash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhash);

  /* WARNING: This function must not be modified, when the callback is needed,
    *          HAL_HASH_SuspendCallback() can be implemented in the user file.
    */
}

/**
  * @brief HASH abort callback.
  * @param hhash pointer to a hal_hash_handle_t structure.
  */
__WEAK void HAL_HASH_AbortCallback(hal_hash_handle_t *hhash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhash);

  /* WARNING: This function must not be modified, when the callback is needed,
    *          HAL_HASH_AbortCallback() can be implemented in the user file.
    */
}

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
/**
  * @brief Register the user hash input callback to be used instead of the weak (surcharged) predefined callback.
  * @param hhash    Pointer to a hal_hash_handle_t structure.
  * @param callback Pointer to the callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register callback completed successfully.
  */
hal_status_t HAL_HASH_RegisterInputCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((callback == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhash->p_input_cplt_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the user hash digest Callback to be used instead of the weak (surcharged) predefined callback.
  * @param hhash    Pointer to a hal_hash_handle_t structure.
  * @param callback Pointer to the callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register callback completed successfully.
  */
hal_status_t HAL_HASH_RegisterDigestComputationCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((callback == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhash->p_digest_cplt_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the user hash error Callback to be used instead of the weak (surcharged) predefined callback.
  * @param hhash    Pointer to a hal_hash_handle_t structure.
  * @param callback Pointer to the callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register callback completed successfully.
  */
hal_status_t HAL_HASH_RegisterErrorCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((callback == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhash->p_error_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the user hash suspend Callback to be used instead of the weak (surcharged) predefined callback.
  * @param hhash    Pointer to a hal_hash_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register callback completed successfully.
  */
hal_status_t HAL_HASH_RegisterSuspendCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((callback == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhash->p_suspend_cplt_callback = callback;

  return HAL_OK;
}

/**
  * @brief Register the user hash abort Callback to be used instead of the weak (surcharged) predefined callback.
  * @param hhash    Pointer to a hal_hash_handle_t structure.
  * @param callback Pointer to the Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register callback completed successfully.
  */
hal_status_t HAL_HASH_RegisterAbortCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((callback == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhash->p_abort_cplt_callback = callback;

  return HAL_OK;
}
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/**
  * @brief link/store HAL DMA handle into the HAL HASH handle.
  * @param hhash   Pointer to a hal_hash_handle_t structure.
  * @param hdma_in Pointer to a hal_dma_handle_t.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Operation completed.
  */
hal_status_t HAL_HASH_SetInDMA(hal_hash_handle_t *hhash, hal_dma_handle_t *hdma_in)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(hdma_in != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_INIT | (uint32_t)HAL_HASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hdma_in == NULL) || (hhash == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hhash->hdma_in    = hdma_in;
  hdma_in->p_parent = hhash;

  return HAL_OK;
}
#endif /*USE_HAL_HASH_DMA*/
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group8
  * @{
This section provides HASH Suspend and Resume functions.
- Use Function HAL_HASH_RequestSuspendComputation() to request an IT computation process suspension.
- Use Function HAL_HASH_RequestSuspendUpdate() to request an IT update process suspension.
- Use Function HAL_HASH_ResumeComputation() to resume the low prior computation process.
- Use Function HAL_HASH_ResumeUpdate() to resume the low prior update process.
- Use Function HAL_HASH_SaveContext() to save the context of the suspended process to start another high priority one.
- Use Function HAL_HASH_RestoreContext() to restore the saved context of the low prior process.

- Note that these APIs are also valid for HMAC operations.
  */
/**
  * @brief Request suspension for hash interrupt mode computation.
  * @param hhash   Pointer to a hal_hash_handle_t structure.
  * @retval HAL_OK The HASH processing suspension is well requested.
  */
hal_status_t HAL_HASH_RequestSuspendComputation(hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_STATE(hhash->global_state, HAL_HASH_STATE_ACTIVE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hhash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  /* suspension in DMA mode*/
  if (HAL_HASH_IsActiveFlag(hhash, HAL_HASH_FLAG_DMA) != HASH_FLAG_STATE_RESET)
  {
    if (HASH_SuspendDMA(hhash) != HAL_OK)
    {
      return HAL_ERROR;
    }
    else
    {
      hhash->global_state = HAL_HASH_STATE_SUSPENDED;
    }
  }
  else /* suspension when in interruption mode*/
  {
#endif /* USE_HAL_HASH_DMA */
    hhash->suspend_request = HASH_SUSPEND;
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  }
#endif /* USE_HAL_HASH_DMA */
  return HAL_OK;
}

/**
  * @brief Resumption of the suspended HASH processing computation.
  * @param hhash     Pointer to a hal_hash_handle_t structure.
  * @retval HAL_BUSY Process is already ongoing.
  * @retval HAL_OK   HASH suspended processing is resumed.
  */
hal_status_t HAL_HASH_ResumeComputation(hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_STATE(hhash->global_state, HAL_HASH_STATE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hhash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_SUSPENDED, HAL_HASH_STATE_ACTIVE);

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  if ((hhash->hdma_in != NULL) && (hhash->dma_operation_active == 1U))
  {
    if (HASH_ResumeDMA(hhash) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  {
#endif /* USE_HAL_HASH_DMA */
    HAL_HASH_EnableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  }
#endif /* USE_HAL_HASH_DMA */

  return HAL_OK;
}

/**
  * @brief  Request suspension for hash interrupt mode processing update.
  * @param  hhash   Pointer to a hal_hash_handle_t structure.
  * @retval HAL_OK The HASH processing suspension is well requested.
  */
hal_status_t HAL_HASH_RequestSuspendUpdate(hal_hash_handle_t *hhash)
{

  ASSERT_DBG_PARAM(hhash != NULL);

  ASSERT_DBG_STATE(hhash->global_state, HAL_HASH_STATE_ACTIVE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hhash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  /* suspension in DMA mode*/
  if (HAL_HASH_IsActiveFlag(hhash, HAL_HASH_FLAG_DMA) != HASH_FLAG_STATE_RESET)
  {
    if (HASH_SuspendDMA(hhash) != HAL_OK)
    {
      return HAL_ERROR;
    }
    else
    {
      hhash->global_state = HAL_HASH_STATE_SUSPENDED;
    }
  }
  else /* suspension when in interruption mode*/
  {
#endif /* USE_HAL_HASH_DMA */
    hhash->suspend_request = HASH_SUSPEND;
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  }
#endif /* USE_HAL_HASH_DMA */

  return HAL_OK;
}

/**
  * @brief Resumption of the suspended HASH processing update.
  * @param hhash   Pointer to a hal_hash_handle_t structure.
  * @retval HAL_BUSY Process is already ongoing.
  * @retval HAL_OK   HASH suspended processing is resumed.
  */
hal_status_t HAL_HASH_ResumeUpdate(hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_STATE(hhash->global_state, HAL_HASH_STATE_SUSPENDED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hhash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hhash, global_state, HAL_HASH_STATE_SUSPENDED, HAL_HASH_STATE_ACTIVE);

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  if ((hhash->hdma_in != NULL) && (hhash->dma_operation_active == 1U))
  {
    if (HASH_ResumeDMA(hhash) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  {
#endif /* USE_HAL_HASH_DMA */
    HAL_HASH_EnableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  }
#endif /* USE_HAL_HASH_DMA */
  return HAL_OK;
}

/**
  * @brief Save parameters of the suspended HASH processing.
  * @param hhash     Pointer to a hal_hash_handle_t structure.
  * @param p_context Pointer to a hal_hash_suspended_context_t structure where to store the parameters of the suspend
  *                  HASH processing.
  */
void HAL_HASH_SaveContext(hal_hash_handle_t *hhash, hal_hash_suspended_context_t *p_context)
{
  uint32_t csr_ptr;

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_context != NULL);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_SUSPENDED);

  csr_ptr = (uint32_t)(HASH_GET_INSTANCE(hhash)->CSR);

  STM32_UNUSED(hhash);

  p_context->imr_reg = READ_BIT(HASH_GET_INSTANCE(hhash)->IMR, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
  p_context->str_reg = READ_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW);
  p_context->cr_reg = READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE | HASH_CR_DATATYPE | HASH_CR_MODE |
                               HASH_CR_ALGO | HASH_CR_LKEY | HASH_CR_MDMAT);

  /* Save all CSRs registers */
  for (uint32_t i = HAL_HASH_NUMBER_OF_CSR_REGISTERS; i > 0U; i--)
  {
    p_context->csr_reg[HAL_HASH_NUMBER_OF_CSR_REGISTERS - i] = *(uint32_t *)csr_ptr;
    csr_ptr += 4U;
  }

  p_context->update_flag             = hhash->update_flag;
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  p_context->hdma_in                 = hhash->hdma_in;
#endif /* USE_HAL_HASH_DMA */
  p_context->input_data_count_byte   = hhash->input_data_count_byte;
  p_context->input_size_byte         = hhash->input_size_byte;
  p_context->key_size_byte           = hhash->key_size_byte;
  p_context->phase                   = hhash->phase;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  p_context->p_abort_cplt_callback   = hhash->p_abort_cplt_callback;
  p_context->p_digest_cplt_callback  = hhash->p_digest_cplt_callback;
  p_context->p_error_callback        = hhash->p_error_callback;
  p_context->p_input_buff            = hhash->p_input_buff;
  p_context->p_output_buff           = hhash->p_output_buff;
  p_context->p_input_cplt_callback   = hhash->p_input_cplt_callback;
  p_context->p_suspend_cplt_callback = hhash->p_suspend_cplt_callback;
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
  p_context->p_key_buff              = hhash->p_key_buff;
  p_context->p_key_saved             = hhash->p_key_saved;
  p_context->dma_operation_active    = hhash->dma_operation_active;
  p_context->previous_state          = hhash->global_state;

  hhash->global_state = HAL_HASH_STATE_IDLE;
}

/**
  * @brief Restore the HASH context in case of processing resumption.
  * @param hhash     Pointer to a hal_hash_handle_t structure.
  * @param p_context Pointer to a hal_hash_suspended_context_t structure where to store the parameters of the suspend
  *                  HASH processing.
  */
void HAL_HASH_RestoreContext(hal_hash_handle_t *hhash, const hal_hash_suspended_context_t *p_context)
{
  uint32_t csr_ptr;

  ASSERT_DBG_PARAM(hhash != NULL);
  ASSERT_DBG_PARAM(p_context != NULL);
  ASSERT_DBG_PARAM(p_context->previous_state == HAL_HASH_STATE_SUSPENDED);

  ASSERT_DBG_STATE(hhash->global_state, (uint32_t)HAL_HASH_STATE_IDLE);

  STM32_UNUSED(hhash);

  csr_ptr = (uint32_t)(HASH_GET_INSTANCE(hhash)->CSR);

  WRITE_REG(HASH_GET_INSTANCE(hhash)->IMR, p_context->imr_reg);
  WRITE_REG(HASH_GET_INSTANCE(hhash)->STR, p_context->str_reg);
  WRITE_REG(HASH_GET_INSTANCE(hhash)->CR, p_context->cr_reg);

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT);

  /* Restore all CSR registers */
  for (uint32_t i = HAL_HASH_NUMBER_OF_CSR_REGISTERS; i > 0U; i--)
  {
    WRITE_REG((*(uint32_t *)(csr_ptr)), p_context->csr_reg[HAL_HASH_NUMBER_OF_CSR_REGISTERS - i]);
    csr_ptr += 4U;
  }

  hhash->update_flag             = p_context->update_flag;
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
  hhash->hdma_in                 = p_context->hdma_in;
#endif /* USE_HAL_HASH_DMA */
  hhash->input_data_count_byte   = p_context->input_data_count_byte;
  hhash->input_size_byte         = p_context->input_size_byte;
  hhash->key_size_byte           = p_context->key_size_byte;
  hhash->phase                   = p_context->phase;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  hhash->p_abort_cplt_callback   = p_context->p_abort_cplt_callback;
  hhash->p_digest_cplt_callback  = p_context->p_digest_cplt_callback;
  hhash->p_error_callback        = p_context->p_error_callback;
  hhash->p_input_buff            = p_context->p_input_buff;
  hhash->p_output_buff           = p_context->p_output_buff;
  hhash->p_input_cplt_callback   = p_context->p_input_cplt_callback;
  hhash->p_suspend_cplt_callback = p_context->p_suspend_cplt_callback;
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
  hhash->p_key_buff              = p_context->p_key_buff;
  hhash->p_key_saved             = p_context->p_key_saved;
  hhash->dma_operation_active    = p_context->dma_operation_active;

  hhash->global_state = HAL_HASH_STATE_SUSPENDED;
}
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group9
  * @{
This subsection provides a set of functions to get the HASH error information and state:
- Use function HAL_HASH_GetState() to get the HASH global state.
- Use function HAL_HASH_GetLastErrorCodes() to get the last error codes.
- Use function HAL_HASH_SetUserData() to set the user data.
- Use function HAL_HASH_GetUserData() to get the user data.
  */

/**
  * @brief Return the HASH handle state.
  * @param hhash Pointer to a hal_hash_handle_t structure.
  * @retval HAL HASH global state.
  */
hal_hash_state_t HAL_HASH_GetState(const hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);

  return hhash->global_state;
}

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
/**
  * @brief Return the HASH handle error code.
  * @param hhash pointer to a hal_hash_handle_t structure.
  * @retval HASH last error Codes.
  * @note When the return is 0xAAAAAAAAU this is a HAL_INVALID_PARAM
  */
uint32_t HAL_HASH_GetLastErrorCodes(const hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1) \
    || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hhash == NULL)
  {
    return (uint32_t)HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM || USE_HAL_SECURE_CHECK_PARAM */

  return hhash->last_error_codes;
}
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

#if defined (USE_HAL_HASH_USER_DATA) && (USE_HAL_HASH_USER_DATA == 1)
/**
  * @brief Store the user data pointer into the HASH handle.
  * @param hhash Pointer to a hal_hash_handle_t structure.
  * @param p_user_data Pointer to the user data.
  */
void HAL_HASH_SetUserData(hal_hash_handle_t *hhash, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hhash != NULL);

  hhash->p_user_data = p_user_data;
}

/**
  * @brief Retrieve the user data from the HASH handle.
  * @param hhash Pointer to a hal_hash_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_HASH_GetUserData(const hal_hash_handle_t *hhash)
{
  ASSERT_DBG_PARAM(hhash != NULL);

  return (hhash->p_user_data);
}
#endif /* USE_HAL_HASH_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup HASH_Private_Functions
  * @{
  */
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/**
  * @brief DMA HASH Input Data transfer completion callback.
  * @param hdma DMA handle.
  */
static void HASH_DMAXferCplt(hal_dma_handle_t *hdma)
{
  hal_hash_handle_t *hhash = (hal_hash_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;
  uint32_t count;

  if (READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MODE) == 0U)
  {
    if ((HASH_GET_INSTANCE(hhash)->CR & HASH_CR_MDMAT) == 0U)
    {
      CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

      count = HASH_TIMEOUT_MS;
      do
      {
        count--;
        if (count == 0U)
        {
          hhash->global_state = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
          hhash->p_error_callback(hhash);
#else
          HAL_HASH_ErrorCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
        }
      } while (IS_BIT_CLR(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DCI));

      /* Call Input data transfer complete callback */
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
      hhash->p_input_cplt_callback(hhash);
#else
      HAL_HASH_InputCpltCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */

      HASH_GetDigestMsg(hhash, hhash->p_output_buff, HAL_HASH_GetDigestLength(hhash));
      *hhash->p_output_size_byte  = HAL_HASH_GetDigestLength(hhash);
      hhash->phase                = HASH_PHASE_READY;
      hhash->dma_operation_active = 0U;
      hhash->global_state         = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
      hhash->p_digest_cplt_callback(hhash);
#else
      HAL_HASH_DigestCpltCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
    }
    else /* (READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_MDMAT) == HASH_CR_MDMAT) */
    {
      hhash->global_state = HAL_HASH_STATE_IDLE;
    }
  }
  else /* HMAC DMA */
  {
    if (hhash->phase == HASH_PHASE_HMAC_STEP_2)
    {
      if ((HASH_GET_INSTANCE(hhash)->CR & HASH_CR_MDMAT) == 0U)
      {
        hhash->phase = HASH_PHASE_HMAC_STEP_3;
        /* Configure the number of valid bits in last word of the Key */
        MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));
        (void)HASH_WriteKey(hhash, hhash->p_key_saved, hhash->key_size_byte);

        /* Start the Key padding then the Digest calculation */
        SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);

        count = HASH_TIMEOUT_MS;
        do
        {
          count--;
          if (count == 0U)
          {
            /* Disable the DMA transfer */
            CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
            hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */
            hhash->global_state = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
            hhash->p_error_callback(hhash);
#else
            HAL_HASH_ErrorCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
            return;
          }
        } while (IS_BIT_CLR(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DCI));

        HASH_GetDigestMsg(hhash, hhash->p_output_buff, HAL_HASH_GetDigestLength(hhash));
        *hhash->p_output_size_byte = HAL_HASH_GetDigestLength(hhash);
        hhash->phase               = HASH_PHASE_READY;
        hhash->global_state        = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
        hhash->p_digest_cplt_callback(hhash);
#else
        HAL_HASH_DigestCpltCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
      }
      else
      {
        hhash->update_flag     = 1;
        hhash->global_state    = HAL_HASH_STATE_IDLE;
      }
    }
  }
}

/**
  * @brief DMA HASH Abort callback.
  * @param hdma DMA handle.
  */
static void HASH_DMAAbort(hal_dma_handle_t *hdma)
{
  hal_hash_handle_t *hhash = (hal_hash_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_INIT);
  hhash->input_data_count_byte = 0U;
  hhash->update_flag           = 0U;
  hhash->input_size_byte       = 0U;
  hhash->suspend_request       = HASH_SUSPEND_NONE;
  hhash->phase                 = HASH_PHASE_READY;
  hhash->global_state          = HAL_HASH_STATE_IDLE;
#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  hhash->p_abort_cplt_callback(hhash);
#else
  HAL_HASH_AbortCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
}

/**
  * @brief DMA HASH communication error callback.
  * @param hdma DMA handle.
  */
static void HASH_DMAError(hal_dma_handle_t *hdma)
{
  hal_hash_handle_t *hhash = (hal_hash_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
  hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

  hhash->global_state = HAL_HASH_STATE_IDLE;

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  hhash->p_error_callback(hhash);
#else
  HAL_HASH_ErrorCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_HASH_DMA */

/**
  * @brief Feed the input key buffer to the HASH peripheral in polling.
  * @param hhash         Pointer to a hal_hash_handle_t structure.
  * @param p_key         Pointer to input buffer.
  * @param key_size_byte Specifies the size of input buffer in bytes.
  * @retval HAL_OK       Operation completed.
  */
static hal_status_t HASH_WriteKey(hal_hash_handle_t *hhash, const uint8_t *p_key, uint32_t key_size_byte)
{
  uint32_t buffer_counter;
  volatile uint32_t inputaddr = (uint32_t) p_key;
  uint32_t tmp;
  hal_hash_data_swapping_t data_swapping;

  for (buffer_counter = 0U; buffer_counter < (key_size_byte / 4U); buffer_counter++)
  {
    /* Write input data 4 bytes at a time */
    HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
    inputaddr += 4U;
    hhash->input_data_count_byte += 4U;
  }

  if ((key_size_byte % 4U) != 0U)
  {
    data_swapping = (hal_hash_data_swapping_t)(uint32_t)READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DATATYPE);
    if (data_swapping == HAL_HASH_DATA_SWAP_HALFWORD)
    {
      if ((key_size_byte % 4U) <= 2U)
      {
        HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
      }
      if ((key_size_byte % 4U) == 3U)
      {
        HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
      }
    }
    else if ((data_swapping == HAL_HASH_DATA_SWAP_BYTE) || (data_swapping == HAL_HASH_DATA_SWAP_BIT))
    {
      if ((key_size_byte % 4U) == 1U)
      {
        HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint8_t *)inputaddr;
      }
      if ((key_size_byte % 4U) == 2U)
      {
        HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
      }
      if ((key_size_byte % 4U) == 3U)
      {
        tmp  = *(uint32_t *)inputaddr;
        tmp |= *(uint32_t *)(inputaddr + 1U) << 8U;
        tmp |= *(uint32_t *)(inputaddr + 2U) << 16U;
        HASH_GET_INSTANCE(hhash)->DIN = tmp;
      }
    }
    else
    {
      HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
    }
    hhash->input_data_count_byte += 4U;
  }

  return HAL_OK;
}

/**
  * @brief Feed the input buffer to the HASH peripheral in polling.
  * @param hhash           Pointer to a hal_hash_handle_t structure.
  * @param p_input_buffer  Pointer to input buffer.
  * @param input_size_byte Specifies the size of input buffer in bytes.
  * @param operation       Specifies HASH operation process.
  * @retval HAL_OK         Operation completed.
  */
static hal_status_t HASH_Write_Data(hal_hash_handle_t *hhash, const uint8_t *p_input_buffer, uint32_t input_size_byte,
                                    uint32_t operation)
{
  uint32_t buffer_counter;
  volatile uint32_t inputaddr = (uint32_t)p_input_buffer;
  uint32_t tmp = 0U;
  uint32_t tmp_input_size_byte = input_size_byte;
  hal_hash_data_swapping_t data_swapping;

  if ((operation == HASH_UPDATE_PROCESS) && (hhash->remain_bytes_number != 0U))
  {
    /* Process additional bytes */
    tmp = 0U;
    for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
    {
      tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
    }

    /* Process the first bytes of the buffer to complete the 4 bytes */
    for (uint32_t i = 0U; (i < (4U - (uint32_t)hhash->remain_bytes_number)) && (i < tmp_input_size_byte); i++)
    {
      tmp |= (*(uint32_t *)inputaddr) << ((i + (uint32_t)hhash->remain_bytes_number) * 8U);
      inputaddr += 1U;
      hhash->input_data_count_byte += 1U;
    }
    HASH_GET_INSTANCE(hhash)->DIN = tmp;

    /* Adjust buffer size after processing first bytes */
    tmp_input_size_byte -= (tmp_input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ?
                           (4U - (uint32_t)hhash->remain_bytes_number) :
                           tmp_input_size_byte;
  }

  if (operation != HASH_FINISH_PROCESS)
  {
    for (buffer_counter = 0U; buffer_counter < (tmp_input_size_byte / 4U); buffer_counter++)
    {
      /* Write input data 4 bytes at a time */
      HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
      inputaddr += 4U;
      hhash->input_data_count_byte += 4U;
    }
  }

  if (operation == HASH_UPDATE_PROCESS)
  {
    /* Save remaining bytes in additional_bytes */
    hhash->remain_bytes_number = (uint8_t)(tmp_input_size_byte % 4U);
    for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
    {
      hhash->remain_bytes[i] = *(uint8_t *)(inputaddr + i);
    }
  }
  else
  {
    if ((tmp_input_size_byte % 4U) != 0U)
    {
      data_swapping = (hal_hash_data_swapping_t)(uint32_t)READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DATATYPE);
      if (data_swapping == HAL_HASH_DATA_SWAP_HALFWORD)
      {
        if ((tmp_input_size_byte % 4U) <= 2U)
        {
          HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
        }
        if ((tmp_input_size_byte % 4U) == 3U)
        {
          HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
        }
      }
      else if ((data_swapping == HAL_HASH_DATA_SWAP_BYTE) || (data_swapping == HAL_HASH_DATA_SWAP_BIT))
      {
        if ((tmp_input_size_byte % 4U) == 1U)
        {
          HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint8_t *)inputaddr;
        }
        if ((tmp_input_size_byte % 4U) == 2U)
        {
          HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
        }
        if ((tmp_input_size_byte % 4U) == 3U)
        {
          tmp = *(uint32_t *)inputaddr;
          tmp |= *(uint32_t *)(inputaddr + 1U) << 8U;
          tmp |= *(uint32_t *)(inputaddr + 2U) << 16U;
          HASH_GET_INSTANCE(hhash)->DIN = tmp;
        }
      }
      else
      {
        HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
      }
      hhash->input_data_count_byte += 4U;
    }
  }

  return HAL_OK;
}

/**
  * @brief Feed the input buffer to the HASH peripheral in interruption mode.
  * @param hhash      Pointer to a hal_hash_handle_t structure.
  * @param operation  Specifies HASH operation process.
  * @retval HAL_ERROR An error has been occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t HASH_WriteData_IT(hal_hash_handle_t *hhash, uint8_t operation)
{
  uint32_t buffer_counter;
  uint32_t count;
  volatile uint32_t inputaddr = (uint32_t)(hhash->p_input_buff);
  uint32_t tmp;
  hal_hash_data_swapping_t data_swapping;

  hhash->operation_process = operation;

  /* Nb byte  to enter in HASH fifo to trig a partial HASH computation */
  volatile uint32_t nbbytePartialHash = (((HASH_GET_INSTANCE(hhash)->SR) >> 16U) * 4U);

  if (hhash->suspend_request == HASH_SUSPEND)
  {
    hhash->suspend_request = HASH_SUSPEND_NONE;
    HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_OK;
  }
  else if (hhash->global_state == HAL_HASH_STATE_IDLE)
  {
    hhash->suspend_request = HASH_SUSPEND_NONE;
    HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
    hhash->global_state = HAL_HASH_STATE_SUSPENDED;
#if defined(USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
    hhash->p_suspend_cplt_callback(hhash);
#else
    HAL_HASH_SuspendCallback(hhash);
#endif /* (USE_HAL_HASH_REGISTER_CALLBACKS) */
    return HAL_OK;
  }
  else /* HAL_HASH_STATE_ACTIVE_COMPUTE | HAL_HASH_STATE_ACTIVE_UPDATE */
  {
    if ((HASH_GET_INSTANCE(hhash)->CR & HASH_CR_MODE) == 0U)
    {
      if (((hhash->input_data_count_byte) + nbbytePartialHash) < (hhash->input_size_byte))
      {
        if ((hhash->remain_bytes_number != 0U) && (hhash->operation_process == HASH_UPDATE_PROCESS))
        {
          /* Process extra bytes */
          tmp = 0U;
          for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
          {
            tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
          }

          /* Process the first bytes of the buffer to complete the 4 bytes */
          for (uint32_t i = 0U; (i < ((4U - (uint32_t)hhash->remain_bytes_number))) \
               && (i < hhash->input_size_byte); i++)
          {
            tmp |= (uint32_t)(*(uint8_t *)inputaddr) << ((i + hhash->remain_bytes_number) * 8U);
            inputaddr += 1U;
            hhash->p_input_buff += 1U;
            hhash->input_data_count_byte += 1U;
          }
          HASH_GET_INSTANCE(hhash)->DIN = tmp;

          hhash->input_data_count_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                          (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

          /* Adjust buffer size after processing first bytes */
          hhash->input_size_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                    (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

          /* Save the new remaining bytes */
          hhash->remain_bytes_number = (uint8_t)(hhash->input_size_byte % 4U);
        }

        buffer_counter = 0U;
        while (buffer_counter < nbbytePartialHash)
        {
          /* Write input data 4 bytes at a time */
          HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
          hhash->input_data_count_byte += 4U;
          inputaddr += 4U;
          hhash->p_input_buff += 4U;
          buffer_counter += 4U;
        }
      }
      else
      {
        if ((hhash->input_data_count_byte) < hhash->input_size_byte)
        {
          if (((operation == HASH_COMPUTE_PROCESS) || (operation == HASH_UPDATE_PROCESS))
              && ((hhash->input_size_byte % 4U) == 0U))
          {
            if (hhash->remain_bytes_number != 0U)
            {
              /* Process extra bytes */
              tmp = 0U;
              for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
              {
                tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
              }

              /* Process the first bytes of the buffer to complete the 4 bytes */
              for (uint32_t i = 0U; (i < ((4U - (uint32_t)hhash->remain_bytes_number))) \
                   && (i < hhash->input_size_byte); i++)
              {
                tmp |= (uint32_t)(*(uint8_t *)inputaddr) << ((i + hhash->remain_bytes_number) * 8U);
                inputaddr += 1U;
                hhash->p_input_buff += 1U;
                hhash->input_data_count_byte += 1U;
              }
              HASH_GET_INSTANCE(hhash)->DIN = tmp;

              /* Adjust buffer size after processing first bytes */
              hhash->input_size_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                        (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

              /* Save the new remaining bytes */
              hhash->remain_bytes_number = (uint8_t)(hhash->input_size_byte % 4U);
            }

            if (hhash->input_size_byte >= 4U)
            {
              while ((hhash->input_data_count_byte) < hhash->input_size_byte)
              {
                /* Write input data 4 bytes at a time */
                HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                inputaddr += 4U;
                hhash->input_data_count_byte += 4U;
                hhash->p_input_buff += 4U;
              }
              /* Wait for HAL_HASH_IT_DIN flag to be set */
              count = HASH_TIMEOUT_MS;
              do
              {
                count--;
                if (count == 0U)
                {
                  HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
                  hhash->global_state = HAL_HASH_STATE_IDLE;
                  return HAL_ERROR;
                }
              } while (IS_BIT_SET(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DINI));
            }

            if (hhash->remain_bytes_number != 0U)
            {
              for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
              {
                hhash->remain_bytes[i] = *(uint8_t *)(inputaddr + i);
              }
            }
          }
          else /* hhash->input_size_byte % 4 != 0U */
          {
            if (operation == HASH_UPDATE_PROCESS)
            {
              if (hhash->remain_bytes_number != 0U)
              {
                /* Process extra bytes */
                tmp = 0U;
                for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
                {
                  tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
                }

                /* Process the first bytes of the buffer to complete the 4 bytes */
                for (uint32_t i = 0U; (i < ((4U - (uint32_t)hhash->remain_bytes_number))) \
                     && (i < hhash->input_size_byte); i++)
                {
                  tmp |= (uint32_t)(*(uint8_t *)inputaddr) << ((i + hhash->remain_bytes_number) * 8U);
                  inputaddr += 1U;
                  hhash->p_input_buff += 1U;
                  hhash->input_data_count_byte += 1U;
                }
                HASH_GET_INSTANCE(hhash)->DIN = tmp;

                hhash->input_data_count_byte -=
                  (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                  (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

                /* Adjust buffer size after processing first bytes */
                hhash->input_size_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                          (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

                /* Save the new remaining bytes */
                hhash->remain_bytes_number = (uint8_t)(hhash->input_size_byte % 4U);
              }
              else
              {
                count = ((hhash->input_size_byte - hhash->input_data_count_byte) / 4U);
                for (buffer_counter = 0U; buffer_counter < count; buffer_counter++)
                {
                  /* Write input data 4 bytes at a time */
                  HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                  inputaddr += 4U;
                  hhash->input_data_count_byte += 4U;
                  hhash->p_input_buff += 4U;
                }
              }
            }

            if (operation != HASH_FINISH_PROCESS)
            {
              count = ((hhash->input_size_byte - hhash->input_data_count_byte) / 4U);
              for (buffer_counter = 0U; buffer_counter < count; buffer_counter++)
              {
                /* Write input data 4 bytes at a time */
                HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                inputaddr += 4U;
                hhash->p_input_buff += 4U;
                hhash->input_data_count_byte += 4U;
              }
            }

            if (operation == HASH_UPDATE_PROCESS)
            {
              /* Save remaining bytes in additional_bytes */
              hhash->remain_bytes_number = (uint8_t)(hhash->input_size_byte % 4U);
              for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
              {
                hhash->remain_bytes[i] = *(uint8_t *)(inputaddr + i);
              }
            }
            else
            {
              if ((hhash->input_size_byte % 4U) != 0U)
              {
                data_swapping = (hal_hash_data_swapping_t)(uint32_t)READ_BIT(HASH_GET_INSTANCE(hhash)->CR,
                                                                             HASH_CR_DATATYPE);
                if (data_swapping == HAL_HASH_DATA_SWAP_HALFWORD)
                {
                  if ((hhash->input_size_byte % 4U) <= 2U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
                  }
                  if ((hhash->input_size_byte % 4U) == 3U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                  }
                }
                else if ((data_swapping == HAL_HASH_DATA_SWAP_BYTE) || (data_swapping == HAL_HASH_DATA_SWAP_BIT))
                {
                  if ((hhash->input_size_byte % 4U) == 1U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint8_t *)inputaddr;
                  }
                  if ((hhash->input_size_byte % 4U) == 2U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
                  }
                  if ((hhash->input_size_byte % 4U) == 3U)
                  {
                    tmp = *(uint32_t *)inputaddr;
                    tmp |= *(uint32_t *)(inputaddr + 1U) << 8U;
                    tmp |= *(uint32_t *)(inputaddr + 2U) << 16U;
                    HASH_GET_INSTANCE(hhash)->DIN = tmp;
                  }
                }
                else
                {
                  HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                }
                hhash->input_data_count_byte += 4U;
              }
            }
          }
        }
#if defined(USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
        hhash->p_input_cplt_callback(hhash);
#else
        HAL_HASH_InputCpltCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
        if (hhash->update_flag == 0U)
        {
          /* Start the message padding then the Digest calculation */
          SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);
          count = HASH_TIMEOUT_MS;
          do
          {
            count--;
            if (count == 0U)
            {
              HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
              hhash->global_state = HAL_HASH_STATE_IDLE;
              return HAL_ERROR;
            }
          } while (IS_BIT_CLR(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DCI));
        }
        else
        {
          hhash->update_flag = 0U;
          HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN);
          hhash->global_state = HAL_HASH_STATE_IDLE;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Feed the input buffer to the HASH HMAC peripheral in interruption mode.
  * @param hhash      Pointer to a hal_hash_handle_t structure.
  * @param operation  Specifies HASH operation process..
  * @retval HAL_ERROR An error has been occurred.
  * @retval HAL_OK    Operation completed.
  */
static hal_status_t HASH_HMAC_WriteData_IT(hal_hash_handle_t *hhash, uint8_t operation)
{
  uint32_t count;
  uint32_t buffer_counter;
  volatile uint32_t keyaddr = (uint32_t)(hhash->p_key_buff);
  uint32_t inputaddr = (uint32_t)(hhash->p_input_buff);

  uint32_t tmp;
  hal_hash_data_swapping_t data_swapping;

  /* Number of byte to enter in HASH fifo to trig a partial HASH computation */
  volatile uint32_t nbbytePartialHash = (((HASH_GET_INSTANCE(hhash)->SR) >> 16U) * 4U);
  uint32_t input_data_count_byte = hhash->input_data_count_byte;
  uint32_t input_size_byte = hhash->input_size_byte;

  hhash->operation_process = operation;

  if (hhash->suspend_request == HASH_SUSPEND)
  {
    HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
    hhash->suspend_request = HASH_SUSPEND_NONE;
    hhash->global_state = HAL_HASH_STATE_IDLE;
    return HAL_OK;
  }
  else if (hhash->global_state == HAL_HASH_STATE_ABORT)
  {
    HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
    return HAL_OK;
  }
  else /* HAL_HASH_STATE_ACTIVE_COMPUTE | HAL_HASH_STATE_ACTIVE_UPDATE */
  {
    /* Data computation or update in step 2 HASH_PHASE_HMAC_STEP_2 */
    if (hhash->phase == HASH_PHASE_HMAC_STEP_2)
    {
      if (hhash->global_state == HAL_HASH_STATE_IDLE)
      {
        hhash->suspend_request = HASH_SUSPEND_NONE;
        HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
        hhash->global_state    = HAL_HASH_STATE_SUSPENDED;
#if defined(USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
        hhash->p_suspend_cplt_callback(hhash);
#else
        HAL_HASH_SuspendCallback(hhash);
#endif /* (USE_HAL_HASH_REGISTER_CALLBACKS) */
      }
      else
      {
        if (hhash->update_flag == 0U)
        {
          /* Configure the number of valid bits in last word of the message */
          MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * (hhash->input_size_byte % 4U));
        }

        if ((input_data_count_byte + nbbytePartialHash) < input_size_byte)
        {
          if ((hhash->remain_bytes_number != 0U) && (hhash->operation_process == HASH_UPDATE_PROCESS))
          {
            /* Process extra bytes */
            tmp = 0U;
            for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
            {
              tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
            }

            /* Process the first bytes of the buffer to complete the 4 bytes */
            for (uint32_t i = 0U; (i < ((4U - (uint32_t)hhash->remain_bytes_number))) \
                 && (i < hhash->input_size_byte); i++)
            {
              tmp |= (uint32_t)(*(uint8_t *)inputaddr) << ((i + hhash->remain_bytes_number) * 8U);
              inputaddr += 1U;
              hhash->p_input_buff += 1U;
              hhash->input_data_count_byte += 1U;
            }
            hhash->input_data_count_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                            (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

            /* Adjust buffer size after processing first bytes */
            hhash->input_size_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                      (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

            /* reset the remain bytes number */
            hhash->remain_bytes_number = 0U;

            HASH_GET_INSTANCE(hhash)->DIN = tmp;
          }
          nbbytePartialHash = (((HASH_GET_INSTANCE(hhash)->SR) >> 16U) * 4U);

          buffer_counter = 0U;
          while ((buffer_counter < nbbytePartialHash) && ((hhash->input_size_byte - hhash->input_data_count_byte) > 4U))
          {
            /* Write input data 4 bytes at a time */
            HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
            hhash->p_input_buff += 4U;
            hhash->input_data_count_byte += 4U;
            buffer_counter += 4U;
            inputaddr += 4U;
          }
        }
        else
        {
          if (((operation == HASH_COMPUTE_PROCESS) || (operation == HASH_UPDATE_PROCESS))
              && ((hhash->input_size_byte % 4U) == 0U))
          {
            while ((hhash->input_data_count_byte) < hhash->input_size_byte)
            {
              hhash->input_data_count_byte += 4U;
              /* Write input data 4 bytes at a time */
              HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
              inputaddr += 4U;
              hhash->p_input_buff += 4U;
            }
          }
          else /* hhash->input_size_byte % 4 != 0U */
          {
            if (operation == HASH_UPDATE_PROCESS)
            {
              if (hhash->remain_bytes_number != 0U)
              {
                /* Process extra bytes */
                tmp = 0U;
                for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
                {
                  tmp |= ((uint32_t)hhash->remain_bytes[i] << ((uint32_t)(i * 8U)));
                }

                /* Process the first bytes of the buffer to complete the 4 bytes */
                for (uint32_t i = 0U; (i < ((4U - (uint32_t)hhash->remain_bytes_number))) \
                     && (i < hhash->input_size_byte); i++)
                {
                  tmp |= (uint32_t)(*(uint8_t *)inputaddr) << ((i + hhash->remain_bytes_number) * 8U);
                  inputaddr += 1U;
                  hhash->p_input_buff += 1U;
                  hhash->input_data_count_byte += 1U;
                }
                HASH_GET_INSTANCE(hhash)->DIN = tmp;

                hhash->input_data_count_byte -=
                  (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                  (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

                /* Adjust buffer size after processing first bytes */
                hhash->input_size_byte -= (hhash->input_size_byte > (4U - (uint32_t)hhash->remain_bytes_number)) ? \
                                          (4U - (uint32_t)hhash->remain_bytes_number) : hhash->input_size_byte;

                /* Save the new remaining bytes */
                hhash->remain_bytes_number = (uint8_t)(hhash->input_size_byte % 4U);
              }
              else
              {
                count = ((hhash->input_size_byte - hhash->input_data_count_byte) / 4U);
                for (buffer_counter = 0U; buffer_counter < count; buffer_counter++)
                {
                  /* Write input data 4 bytes at a time */
                  HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                  inputaddr += 4U;
                  hhash->p_input_buff += 4U;
                  hhash->input_data_count_byte += 4U;
                }
              }
            }

            if ((hhash->input_data_count_byte == 0U) && (operation != HASH_FINISH_PROCESS))
            {
              for (buffer_counter = 0U; buffer_counter < (hhash->input_size_byte / 4U); buffer_counter++)
              {
                /* Write input data 4 bytes at a time */
                HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                inputaddr += 4U;
                hhash->p_input_buff += 4U;
                hhash->input_data_count_byte += 4U;
              }
            }

            if (operation == HASH_UPDATE_PROCESS)
            {
              /* Save remaining bytes in additional_bytes */
              hhash->remain_bytes_number = (uint8_t)(hhash->input_size_byte % 4U);
              for (uint32_t i = 0U; i < hhash->remain_bytes_number; i++)
              {
                hhash->remain_bytes[i] = *(uint8_t *)(inputaddr + i);
              }
            }
            else
            {
              if ((hhash->input_size_byte % 4U) != 0U)
              {
                data_swapping = (hal_hash_data_swapping_t)(uint32_t)READ_BIT(HASH_GET_INSTANCE(hhash)->CR,
                                                                             HASH_CR_DATATYPE);
                if (data_swapping == HAL_HASH_DATA_SWAP_HALFWORD)
                {
                  if ((hhash->input_size_byte % 4U) <= 2U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
                  }
                  if ((hhash->input_size_byte % 4U) == 3U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                  }
                }
                else if ((data_swapping == HAL_HASH_DATA_SWAP_BYTE) || (data_swapping == HAL_HASH_DATA_SWAP_BIT))
                {
                  if ((hhash->input_size_byte % 4U) == 1U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint8_t *)inputaddr;
                  }
                  if ((hhash->input_size_byte % 4U) == 2U)
                  {
                    HASH_GET_INSTANCE(hhash)->DIN = (uint32_t) * (uint16_t *)inputaddr;
                  }
                  if ((hhash->input_size_byte % 4U) == 3U)
                  {
                    tmp = *(uint32_t *)inputaddr;
                    tmp |= *(uint32_t *)(inputaddr + 1U) << 8U;
                    tmp |= *(uint32_t *)(inputaddr + 2U) << 16U;
                    HASH_GET_INSTANCE(hhash)->DIN = tmp;
                  }
                }
                else
                {
                  HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)inputaddr;
                }
                hhash->input_data_count_byte += 4U;
              }
            }
          }
#if defined(USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
          hhash->p_input_cplt_callback(hhash);
#else
          HAL_HASH_InputCpltCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */

          if (hhash->update_flag == 0U)
          {
            if (HAL_HASH_GetITSource(hhash, HAL_HASH_IT_DIN) == HAL_HASH_IT_DIN)
            {
              /* Start the message padding then the Digest calculation */
              SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);
              count = HASH_TIMEOUT_MS;
              do
              {
                count--;
                if (count == 0U)
                {
                  /* Disable interrupts */
                  HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
                  hhash->global_state = HAL_HASH_STATE_IDLE;
                  return HAL_ERROR;
                }
              } while (IS_BIT_SET(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_BUSY));

              hhash->phase = HASH_PHASE_HMAC_STEP_3;
              hhash->input_data_count_byte = 0U;
              hhash->p_key_buff = hhash->p_key_saved;
            }
          }
          else
          {
            HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
            hhash->global_state = HAL_HASH_STATE_IDLE;
            return HAL_OK;
          }
        }
      }
    }
    else if (hhash->phase == HASH_PHASE_HMAC_STEP_3) /* loading Key during the computation */
    {
      /* Configure the number of valid bits in last word of the Key */
      MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 8U * ((hhash->key_size_byte) % 4U));

      if ((input_data_count_byte + nbbytePartialHash) < (hhash->key_size_byte))
      {
        buffer_counter = 0U;
        while (buffer_counter < nbbytePartialHash)
        {
          /* Write input data 4 bytes at a time */
          HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)keyaddr;
          keyaddr += 4U;
          hhash->input_data_count_byte += 4U;
          hhash->p_key_buff += 4U;
          buffer_counter += 4U;
        }
        count = HASH_TIMEOUT_MS;
        do
        {
          count--;
          if (count == 0U)
          {
            HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
            hhash->global_state = HAL_HASH_STATE_IDLE;
            return HAL_ERROR;
          }
        } while (IS_BIT_CLR(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DINI));
      }
      else
      {
        while ((hhash->input_data_count_byte) < (hhash->key_size_byte))
        {
          /* Write input data 4 bytes at a time */
          HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)keyaddr;
          keyaddr += 4U;
          hhash->input_data_count_byte += 4U;
        }
        /* Start the message padding then the Digest calculation */
        SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);
        count = HASH_TIMEOUT_MS;
        do
        {
          count--;
          if (count == 0U)
          {
            HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
            hhash->global_state = HAL_HASH_STATE_IDLE;
            return HAL_ERROR;
          }
        } while (IS_BIT_CLR(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DCI));
      }
    }
    else /* First step: loading key during the computation */
    {
      hhash->phase = HASH_PHASE_HMAC_STEP_1;
      if (hhash->suspend_request == HASH_SUSPEND)
      {
        hhash->suspend_request = HASH_SUSPEND_NONE;
        HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
        hhash->global_state    = HAL_HASH_STATE_SUSPENDED;
#if defined(USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
        hhash->p_suspend_cplt_callback(hhash);
#else
        HAL_HASH_SuspendCallback(hhash);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */
      }
      else
      {
        if ((input_data_count_byte + nbbytePartialHash) < hhash->key_size_byte)
        {
          buffer_counter = 0U;
          while (buffer_counter < nbbytePartialHash)
          {
            /* Write input data 4 bytes at a time */
            HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)keyaddr;
            keyaddr += 4U;
            hhash->input_data_count_byte += 4U;
            hhash->p_key_buff += 4U;
            buffer_counter += 4U;
          }
          count = HASH_TIMEOUT_MS;
          do
          {
            count--;
            if (count == 0U)
            {
              HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
              hhash->global_state    = HAL_HASH_STATE_IDLE;
              return HAL_ERROR;
            }
          } while (IS_BIT_CLR(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_DINI));
        }
        else
        {
          while ((hhash->input_data_count_byte) < (hhash->key_size_byte))
          {
            /* Write input data 4 bytes at a time */
            HASH_GET_INSTANCE(hhash)->DIN = *(uint32_t *)keyaddr;
            keyaddr += 4U;
            hhash->input_data_count_byte += 4U;
            hhash->p_key_buff += 4U;
          }
          /* Start the message padding then the Digest calculation */
          SET_BIT(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_DCAL);
          count = HASH_TIMEOUT_MS;
          do
          {
            count--;
            if (count == 0U)
            {
              HAL_HASH_DisableIT(hhash, HAL_HASH_IT_DIN | HAL_HASH_IT_DC);
              hhash->global_state    = HAL_HASH_STATE_IDLE;
              return HAL_ERROR;
            }
          } while (IS_BIT_SET(HASH_GET_INSTANCE(hhash)->SR, HAL_HASH_FLAG_BUSY));

          hhash->phase = HASH_PHASE_HMAC_STEP_2;
          hhash->input_data_count_byte = 0U;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief Retrieve the message digest.
  * @param hhash HASH handle.
  * @param p_msg_digest pointer to the computed digest.
  * @param input_size_byte message digest size in bytes.
  */
static void HASH_GetDigestMsg(const hal_hash_handle_t *hhash, const uint8_t *p_msg_digest, uint8_t input_size_byte)
{
  uint32_t msg_digest = (uint32_t)p_msg_digest;
  uint8_t i;
  for (i = 0U; i < (input_size_byte / 4U); i++)
  {
    *(uint32_t *)(msg_digest) = __REV(HASH_GET_INSTANCE(hhash)->HR[i]);
    msg_digest += 4U;
  }

}

/**
  * @brief Handle HASH processing timeout.
  * @param hhash        HASH handle.
  * @param flag         Specifies the HASH flag to check.
  * @param flag_state   The Flag status (SET or RESET).
  * @param timeout_ms   Specify timeout value in millisecond.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_OK      Operation completed.
  */
static hal_status_t HASH_WaitOnFlagUntilTimeout(hal_hash_handle_t *hhash, uint32_t flag, uint32_t flag_state,
                                                uint32_t timeout_ms)
{
  uint32_t tickstart = HAL_GetTick();

  while (HAL_HASH_IsActiveFlag(hhash, flag) == flag_state)
  {
    /* Check for the timeout */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        hhash->global_state    = HAL_HASH_STATE_IDLE;
        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief update CR register according to HASH algorithm.
  * @param hhash     HASH handle.
  * @param size_byte Specifie size inputs in bytes.
  */
static void HASH_UpdateCRAccordingAlgo(hal_hash_handle_t *hhash, uint32_t size_byte)
{
  uint32_t block_size;
  hal_hash_algo_t algorithm;

  algorithm = (hal_hash_algo_t)(uint32_t)READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_ALGO);
  if ((algorithm == HAL_HASH_ALGO_SHA1) || (algorithm == HAL_HASH_ALGO_SHA224) || (algorithm == HAL_HASH_ALGO_SHA256))
  {
    block_size = HASH_BLOCK_SIZE_64B;
  }
  else
  {
    block_size = HASH_BLOCK_SIZE_128B;
  }

  if (size_byte > block_size)
  {
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_LKEY | HASH_CR_MODE | HASH_CR_INIT, HASH_ALGO_MODE_HMAC |
               HASH_LONG_KEY | HASH_CR_INIT);
  }
  else
  {
    MODIFY_REG(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_LKEY | HASH_CR_MODE | HASH_CR_INIT, HASH_ALGO_MODE_HMAC |
               HASH_CR_INIT);
  }
}

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
/** @brief suspend the DMA.
  * @param hhash specifies the HASH handle.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_ERROR   An error has been occurred.
  * @retval HAL_OK      DMA suspended.
  */
static hal_status_t HASH_SuspendDMA(hal_hash_handle_t *hhash)
{
  uint32_t remaining_words; /*remaining number in of source block to be transferred.*/
  uint32_t size_in_words;   /* number in word of source block to be transferred.*/

  /* Clear the DMAE bit to disable the DMA interface */
  CLEAR_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

  /* Wait until the last DMA transfer is complete (DMAS = 0 in the HASH_SR register) */
  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_DMA, HASH_FLAG_STATE_SET, HASH_TIMEOUT_MS) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  /* At this point, DMA interface is disabled and no transfer is on-going */
  /* Retrieve from the DMA handle how many words remain to be written */
  /* DMA3 used, DMA_CBR1_BNDT in bytes, DMA_CSR_FIFOL in words */
  remaining_words = ((((DMA_Channel_TypeDef *)hhash->hdma_in->instance)->CBR1) & DMA_CBR1_BNDT) / 4U;
  remaining_words += ((((DMA_Channel_TypeDef *)hhash->hdma_in->instance)->CSR) & DMA_CSR_FIFOL) >> DMA_CSR_FIFOL_Pos;

  /* Disable DMA channel */
  /* Note that the Abort function will
    - Clear the transfer error flags
    - Unlock
    - Set the State
    */
  if (HAL_DMA_Abort(hhash->hdma_in) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Wait until the hash processor is ready (no block is being processed), that is wait for DINIS=1 in HASH_SR */
  if (HASH_WaitOnFlagUntilTimeout(hhash, HAL_HASH_FLAG_DINI, HASH_FLAG_STATE_RESET, HASH_TIMEOUT_MS) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  if (HAL_HASH_IsActiveFlag(hhash, HAL_HASH_FLAG_DCI) != HASH_FLAG_STATE_RESET)
  {
    return HAL_ERROR;
  }

  if (remaining_words == 0U)
  {
    /* All the DMA transfer is actually done. Suspension occurred at the very end
    of the transfer. Either the digest computation is about to start (HASH case)
    or processing is about to move from one step to another (HMAC case).
    In both cases, the processing can't be suspended at this point. It is
    safer to
    - retrieve the low priority block digest before starting the high
    priority block processing (HASH case)
    - re-attempt a new suspension (HMAC case)
    */
    return HAL_ERROR;
  }
  else
  {
    /* Compute how many words were supposed to be transferred by DMA */
    size_in_words = (((hhash->input_size_byte % 4U) != 0U) ? \
                     ((hhash->input_size_byte + 3U) / 4U) : (hhash->input_size_byte / 4U));

    /* Accordingly, update the input pointer that points at the next word to be transferred to the Peripheral by DMA */
    hhash->p_input_buff += 4U * (size_in_words - remaining_words);

    /* And store in input_data_count_byte the remaining size to transfer (in bytes) */
    hhash->input_size_byte = 4U * remaining_words;

    return HAL_OK;

  }
}

/** @brief Resume the DMA.
  * @param hhash specifies the HASH handle.
  * @retval HAL_TIMEOUT A timeout has occurred.
  * @retval HAL_ERROR   An error has been occurred.
  * @retval HAL_OK      DMA resumed.
  */
static hal_status_t HASH_ResumeDMA(hal_hash_handle_t *hhash)
{
  uint32_t tmp_input_size;

  MODIFY_REG(HASH_GET_INSTANCE(hhash)->STR, HASH_STR_NBLW, 0U);

  tmp_input_size = (((hhash->input_size_byte % 4U) != 0U) ?
                    (hhash->input_size_byte + (4U - (hhash->input_size_byte % 4U))) : (hhash->input_size_byte));


  SET_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_DMAE);

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hhash->hdma_in,
                                     (uint32_t)hhash->p_input_buff,
                                     (uint32_t) &((HASH_TypeDef *)((uint32_t)(hhash)->instance))->DIN,
                                     tmp_input_size,
                                     HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    hhash->phase           = HASH_PHASE_READY;
    hhash->global_state    = HAL_HASH_STATE_IDLE;
#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
    hhash->last_error_codes |= HAL_HASH_ERROR_DMA;
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

    return HAL_ERROR;
  }

  return HAL_OK;

}
#endif /* USE_HAL_HASH_DMA */

/** @brief Get the digest length in byte.
  * @param hhash specifies the HASH handle.
  * @retval digest length.
  */
__STATIC_INLINE uint8_t HAL_HASH_GetDigestLength(const hal_hash_handle_t *hhash)
{
  uint32_t algorithm = (READ_BIT(HASH_GET_INSTANCE(hhash)->CR, HASH_CR_ALGO));

  if (algorithm == (uint32_t)HAL_HASH_ALGO_SHA1)
  {
    return 20U;
  }
  else if (algorithm == (uint32_t)HASH_CR_ALGO_1)
  {
    return 28U;
  }
  else if (algorithm == (uint32_t)HASH_CR_ALGO)
  {
    return 32U;
  }
  else
  {
    return 16U;
  }
}
/**
  * @}
  */

#endif /* USE_HAL_HASH_MODULE */

/**
  * @}
  */

#endif /* HASH */

/**
  * @}
  */
