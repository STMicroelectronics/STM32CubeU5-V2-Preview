/**
  ******************************************************************************
  * @file    stm32u5xx_hal_hash.h
  * @brief   Header file of HASH HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_HASH_H
#define STM32U5XX_HAL_HASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
#if defined (HASH)
/** @defgroup HASH HASH
  * @brief HASH HAL module driver.
  * @{
  */
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup HASH_Private_Constants HASH Private Constants
  * @{
  */
#define HAL_HASH_NUMBER_OF_CSR_REGISTERS   54U  /*!< Number of Context Swap Registers */
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup HASH_Exported_Constants HASH Exported Constants
  * @{
  */

/** @defgroup HASH_Error_Definition HASH Error Definition
  * @{
  */
#define HAL_HASH_ERROR_NONE  0x00000000U /*!< No error                */
#if defined(USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1U)
#define HAL_HASH_ERROR_DMA   0x00000002U /*!< DMA-based process error */
#endif /* USE_HAL_HASH_DMA */
/**
  * @}
  */

/** @defgroup HASH_flags_definition HASH flags definitions
  * @{
  */
#define HAL_HASH_FLAG_DINI   HASH_SR_DINIS /*!< Data input interrupt status                                */
#define HAL_HASH_FLAG_DCI    HASH_SR_DCIS  /*!< Digest calculation complete                                */
#define HAL_HASH_FLAG_DMA    HASH_SR_DMAS  /*!< DMA interface is enabled (DMAE=1) or a transfer is ongoing */
#define HAL_HASH_FLAG_BUSY   HASH_SR_BUSY  /*!< The hash core is Busy, processing a block of data          */
#define HAL_HASH_FLAG_DINNE  HASH_SR_DINNE /*!< Data input not empty                                       */
/**
  * @}
  */

/** @defgroup HASH_interrupts_definition HASH interrupts definitions
  * @{
  */
#define HAL_HASH_IT_DIN      HASH_IMR_DINIE /*!< A new block can be entered into the input buffer (DIN) */
#define HAL_HASH_IT_DC       HASH_IMR_DCIE  /*!< Digest calculation complete                            */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup HASH_Exported_Types HASH Exported Types
  * @{
  */
/*! HASH instance */
typedef enum
{
  HAL_HASH = (uint32_t)HASH, /*!< HAL HASH instance */
} hal_hash_t;

/*! HAL State structure definition */
typedef enum
{
  HAL_HASH_STATE_RESET     = (0U),        /*!< HASH is not initialized                      */
  HAL_HASH_STATE_INIT      = (1U << 31U), /*!< HASH is initialized but not yet configured   */
  HAL_HASH_STATE_IDLE      = (1U << 30U), /*!< HASH initialized and a global config applied */
  HAL_HASH_STATE_ACTIVE    = (1U << 29U), /*!< HASH active process is ongoing               */
  HAL_HASH_STATE_SUSPENDED = (1U << 28U), /*!< HASH is Suspended                            */
  HAL_HASH_STATE_ABORT     = (1U << 27U)  /*!< HASH is Aborted                              */
} hal_hash_state_t;

/*! HASH algorithm selection */
typedef enum
{
  HAL_HASH_ALGO_SHA1      = 0x00000000U,                                      /*!< HASH algorithm is SHA1      */
  HAL_HASH_ALGO_MD5       = HASH_CR_ALGO_0,                                   /*!< HASH algorithm is MD5       */
  HAL_HASH_ALGO_SHA224    = HASH_CR_ALGO_1,                                   /*!< HASH algorithm is SHA224    */
  HAL_HASH_ALGO_SHA256    = HASH_CR_ALGO,                                     /*!< HASH algorithm is SHA256    */
} hal_hash_algo_t;

/*! HASH input data type */
typedef enum
{
  HAL_HASH_DATA_SWAP_NO       = 0x00000000U,        /*!< 32-bit data. No swapping                     */
  HAL_HASH_DATA_SWAP_HALFWORD = HASH_CR_DATATYPE_0, /*!< 16-bit data. Each half word is swapped       */
  HAL_HASH_DATA_SWAP_BYTE     = HASH_CR_DATATYPE_1, /*!< 8-bit data. All bytes are swapped            */
  HAL_HASH_DATA_SWAP_BIT      = HASH_CR_DATATYPE    /*!< 1-bit data. In the word all bits are swapped */
} hal_hash_data_swapping_t;

/*! HASH Configuration structure definition */
typedef struct
{
  hal_hash_data_swapping_t data_swapping; /*!< no swap (32-bit data), half word swap (16-bit data), byte swap
                                               (8-bit data) or bit swap (1-bit data).
                                               This parameter can be a value of @ref hal_hash_data_swapping_t. */
  hal_hash_algo_t          algorithm;     /*!< HASH algorithm MD5, SHA1 or SHA224 OR SHA256.
                                               This parameter can be a value of @ref hal_hash_algo_t           */
} hal_hash_config_t;

/*! HASH HMAC Configuration structure definition */
typedef struct
{
  hal_hash_data_swapping_t data_swapping;  /*!< no swap (32-bit data), half word swap (16-bit data), byte swap
                                                (8-bit data) or bit swap (1-bit data).
                                                This parameter can be a value of @ref hal_hash_data_swapping_t. */

  hal_hash_algo_t          algorithm;      /*!< HASH algorithm MD5, SHA1 or SHA224 OR SHA256.
                                               This parameter can be a value of @ref hal_hash_algo_t            */

  uint8_t                  *p_key;         /*!< Identifier of the key to use for the HMAC operation             */

  uint32_t                 key_size_byte;  /*!< The key size in bytes                                           */
} hal_hash_hmac_config_t;

typedef struct hal_hash_handle_s hal_hash_handle_t; /*!< HASH handle Structure type */

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
typedef void (*hal_hash_cb_t)(hal_hash_handle_t *hhash); /*!< HAL HASH Callback pointer definition */
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */

/*! HASH suspend resume context structure */
typedef struct
{
  uint32_t csr_reg[HAL_HASH_NUMBER_OF_CSR_REGISTERS];  /*!< Copy of HASH context swap register when processing is
                                                            suspended                                                 */
  uint32_t imr_reg;                                    /*!< Copy of HASH interrupt enable register when processing is
                                                            suspended                                                 */
  uint32_t str_reg;                                    /*!< Copy of HASH start register when processing is suspended  */

  uint32_t cr_reg;                                     /*!< Copy of HASH control register when processing is
                                                            suspended                                                 */

  volatile  uint32_t update_flag;                      /*!< Copy of HASH multi buffers update flag                    */

  uint32_t input_data_count_byte;                      /*!< Copy of Counter of inputted data                          */

  uint32_t input_size_byte;                            /*!< Copy of buffer input_size to be processed in bytes        */

  uint32_t key_size_byte;                              /*!< Copy of HASH Key's size in byte                           */

  uint32_t phase;                                      /*!< Copy of HASH peripheral phase                             */

#if defined(USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1U)
  hal_dma_handle_t *hdma_in;                           /*!< Copy of HASH In DMA handle parameters                     */
#endif /* USE_HAL_HASH_DMA */

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  hal_hash_cb_t p_digest_cplt_callback;               /*!< Copy of HASH digest computation completion callback        */
  hal_hash_cb_t p_input_cplt_callback;                /*!< Copy of HASH input completion callback                     */
  hal_hash_cb_t p_error_callback;                     /*!< Copy of HASH error callback                                */
  hal_hash_cb_t p_abort_cplt_callback;                /*!< Copy of HASH Abort callback                                */
  hal_hash_cb_t p_suspend_cplt_callback;              /*!< Copy of HASH Suspend callback                              */
#endif /* (USE_HAL_HASH_REGISTER_CALLBACKS) */

  const uint8_t *p_input_buff;                        /*!< Copy of Pointer to input buffer                            */

  uint8_t *p_output_buff;                             /*!< Copy of Pointer to output buffer (digest)                  */

  uint8_t *p_key_buff;                                /*!< Copy of Pointer to key buffer (HMAC only)                  */

  uint8_t *p_key_saved;                               /*!< Copy of Pointer to key buffer (HMAC only)                  */

  uint8_t  dma_operation_active;                      /*!< Copy of DMA flag operation ongoing                         */

  hal_hash_state_t previous_state;                    /*!< Copy of HASH peripheral state                              */

} hal_hash_suspended_context_t;

/*! HASH handle structure definition */
struct hal_hash_handle_s
{
  hal_hash_t                  instance;                /*!< HASH Register base address                  */

  uint32_t                    input_size_byte;         /*!< buffer input_size to be processed in bytes  */

  uint32_t                    *p_output_size_byte;     /*!< buffer output size processed in bytes       */

  uint32_t                    input_data_count_byte;   /*!< Counter of inputted data                    */

  uint32_t                    key_size_byte;           /*!< HASH Key's size in byte                     */

  volatile  uint32_t          update_flag;             /*!< HASH multi buffers update flag              */

  volatile uint32_t           suspend_request;         /*!< HASH peripheral suspension request flag     */

  uint32_t                    phase;                   /*!< HASH peripheral phase                       */

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
  volatile  uint32_t          last_error_codes;        /*!< HASH Last Error codes                       */
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

  const uint8_t               *p_input_buff;           /*!< Pointer to input buffer                     */

  uint8_t                     *p_output_buff;          /*!< Pointer to output buffer (digest)           */

  uint8_t                     *p_key_buff;             /*!< Pointer to key buffer (HMAC only)           */

  uint8_t                     *p_key_saved;            /*!< Pointer to key buffer (HMAC only)           */

  uint8_t                     remain_bytes[3];         /*!< HASH remaining bytes                        */

  uint8_t                     remain_bytes_number;     /*!< HASH remaining bytes number                 */

  uint8_t                     operation_process;       /*!< HASH ongoing operation process              */

  uint8_t                     dma_operation_active;    /*!< DMA flag operation ongoing                  */

  volatile hal_hash_state_t   global_state;            /*!< HASH peripheral state                       */

#if defined(USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1U)
  hal_dma_handle_t           *hdma_in;                 /*!< HASH In DMA handle parameters               */
#endif /* USE_HAL_HASH_DMA */

#if defined (USE_HAL_HASH_USER_DATA) && (USE_HAL_HASH_USER_DATA == 1)
  const void                  *p_user_data;            /*!< HASH user data                              */
#endif /* USE_HAL_HASH_USER_DATA */

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
  hal_hash_cb_t               p_input_cplt_callback;   /*!< HASH input completion callback              */
  hal_hash_cb_t               p_digest_cplt_callback;  /*!< HASH digest computation completion callback */
  hal_hash_cb_t               p_error_callback;        /*!< HASH error callback                         */
  hal_hash_cb_t               p_suspend_cplt_callback; /*!< HASH Suspend callback                       */
  hal_hash_cb_t               p_abort_cplt_callback;   /*!< HASH Abort callback                         */
#endif /* (USE_HAL_HASH_REGISTER_CALLBACKS) */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup HASH_Exported_Functions HASH Exported Functions
  * @{
  */

/** @defgroup HASH_Exported_Functions_Group1 HASH initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_HASH_Init(hal_hash_handle_t *hhash, hal_hash_t instance);
void HAL_HASH_DeInit(hal_hash_handle_t *hhash);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group2 HASH Set and Get configurations functions
  * @{
  */
hal_status_t HAL_HASH_SetConfig(hal_hash_handle_t *hhash, const hal_hash_config_t *p_config);
void HAL_HASH_GetConfig(hal_hash_handle_t *hhash, hal_hash_config_t *p_config);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group3 HASH processing functions
  * @{
  */
hal_status_t HAL_HASH_Compute(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                              void *p_output_buffer, uint32_t *p_output_size_byte, uint32_t timeout_ms);
hal_status_t HAL_HASH_Compute_IT(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                 void *p_output_buffer, uint32_t *p_output_size_byte);
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
hal_status_t HAL_HASH_Compute_DMA(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                  void *p_output_buffer, uint32_t *p_output_size_byte);
#endif /* USE_HAL_HASH_DMA */

hal_status_t HAL_HASH_Update(hal_hash_handle_t *hhash, const void *p_add_input_buffer, uint32_t input_size_byte,
                             uint32_t timeout_ms);

hal_status_t HAL_HASH_Update_IT(hal_hash_handle_t *hhash, const void *p_add_input_buffer, uint32_t input_size_byte);

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
hal_status_t HAL_HASH_Update_DMA(hal_hash_handle_t *hhash, const void *p_add_input_buffer,
                                 uint32_t input_size_byte);
#endif /* USE_HAL_HASH_DMA */

hal_status_t HAL_HASH_Finish(hal_hash_handle_t *hhash, void *p_output_buffer, uint32_t *p_output_size_byte,
                             uint32_t timeout_ms);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group4 HASH HMAC Set and Get configurations functions
  * @{
  */
hal_status_t HAL_HASH_HMAC_SetConfig(hal_hash_handle_t *hhash, const hal_hash_hmac_config_t *p_config);
void HAL_HASH_HMAC_GetConfig(hal_hash_handle_t *hhash, hal_hash_hmac_config_t *p_config);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group5 HMAC processing functions
  * @{
  */
hal_status_t HAL_HASH_HMAC_Compute(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                   void *p_output_buffer, uint32_t *p_output_size_byte, uint32_t timeout_ms);
hal_status_t HAL_HASH_HMAC_Compute_IT(hal_hash_handle_t *hhash, const void *p_input_buffer,
                                      uint32_t input_size_byte, void *p_output_buffer, uint32_t *p_output_size_byte);
#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
hal_status_t HAL_HASH_HMAC_Compute_DMA(hal_hash_handle_t *hhash, const void *p_input_buffer, uint32_t input_size_byte,
                                       void *p_output_buffer, uint32_t *p_output_size_byte);
#endif /* USE_HAL_HASH_DMA */

hal_status_t HAL_HASH_HMAC_Update(hal_hash_handle_t *hhash, const void *p_add_input_buffer, uint32_t input_size_byte,
                                  uint32_t timeout_ms);

hal_status_t HAL_HASH_HMAC_Update_IT(hal_hash_handle_t *hhash, const void *p_add_input_buffer,
                                     uint32_t input_size_byte);

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
hal_status_t HAL_HASH_HMAC_Update_DMA(hal_hash_handle_t *hhash, const void *p_add_input_buffer,
                                      uint32_t input_size_byte);
#endif /* USE_HAL_HASH_DMA */

hal_status_t HAL_HASH_HMAC_Finish(hal_hash_handle_t *hhash, void *p_output_buffer, uint32_t *p_output_size_byte,
                                  uint32_t timeout_ms);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group6 HASH Abort functions
  * @{
  */
hal_status_t HAL_HASH_Abort(hal_hash_handle_t *hhash, uint32_t timeout_ms);
hal_status_t HAL_HASH_Abort_IT(hal_hash_handle_t *hhash);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group7 HASH IRQ handler management
  * @{
  */
void HAL_HASH_IRQHandler(hal_hash_handle_t *hhash);
void HAL_HASH_InputCpltCallback(hal_hash_handle_t *hhash);
void HAL_HASH_DigestCpltCallback(hal_hash_handle_t *hhash);
void HAL_HASH_ErrorCallback(hal_hash_handle_t *hhash);
void HAL_HASH_SuspendCallback(hal_hash_handle_t *hhash);
void HAL_HASH_AbortCallback(hal_hash_handle_t *hhash);

#if defined (USE_HAL_HASH_REGISTER_CALLBACKS ) && (USE_HAL_HASH_REGISTER_CALLBACKS == 1)
hal_status_t HAL_HASH_RegisterInputCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback);
hal_status_t HAL_HASH_RegisterDigestComputationCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback);
hal_status_t HAL_HASH_RegisterErrorCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback);
hal_status_t HAL_HASH_RegisterSuspendCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback);
hal_status_t HAL_HASH_RegisterAbortCpltCallback(hal_hash_handle_t *hhash, hal_hash_cb_t callback);
#endif /* USE_HAL_HASH_REGISTER_CALLBACKS */

#if defined (USE_HAL_HASH_DMA) && (USE_HAL_HASH_DMA == 1)
hal_status_t HAL_HASH_SetInDMA(hal_hash_handle_t *hhash, hal_dma_handle_t *hdma_in);
#endif /* USE_HAL_HASH_DMA */
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group8 HASH Suspend/Resume functions
  * @{
  */
hal_status_t HAL_HASH_RequestSuspendComputation(hal_hash_handle_t *hhash);
hal_status_t HAL_HASH_ResumeComputation(hal_hash_handle_t *hhash);
hal_status_t HAL_HASH_RequestSuspendUpdate(hal_hash_handle_t *hhash);
hal_status_t HAL_HASH_ResumeUpdate(hal_hash_handle_t *hhash);
void HAL_HASH_SaveContext(hal_hash_handle_t *hhash, hal_hash_suspended_context_t *p_context);
void HAL_HASH_RestoreContext(hal_hash_handle_t *hhash, const hal_hash_suspended_context_t *p_context);
/**
  * @}
  */

/** @defgroup HASH_Exported_Functions_Group9 HASH peripheral State, Error and User data functions
  * @{
  */
hal_hash_state_t HAL_HASH_GetState(const hal_hash_handle_t *hhash);

#if defined(USE_HAL_HASH_GET_LAST_ERRORS) && (USE_HAL_HASH_GET_LAST_ERRORS == 1)
uint32_t HAL_HASH_GetLastErrorCodes(const hal_hash_handle_t *hhash);
#endif /* USE_HAL_HASH_GET_LAST_ERRORS */

#if defined (USE_HAL_HASH_USER_DATA) && (USE_HAL_HASH_USER_DATA == 1)
void HAL_HASH_SetUserData(hal_hash_handle_t *hhash, const void *p_user_data);
const void *HAL_HASH_GetUserData(const hal_hash_handle_t *hhash);
#endif /* USE_HAL_HASH_USER_DATA */
/**
  * @}
  */

/** @addtogroup HASH_Exported_Functions_Group10 HASH Interrupt And Flag Configuration
  * @{
This section provides functions allowing to initialize and de-initialize the HASH card device :
- Call the function HAL_HASH_IsActiveFlag() to check whether the specified HASH flag is set or not.
- Call the function HAL_HASH_GetITSource() to check whether the specified HASH interrupt source is enabled or not.
- Call the function HAL_HASH_EnableIT() to enable the HASH device interrupt.
- Call the function HAL_HASH_DisableIT() to disable the device interrupt.
- Call the function HAL_HASH_ClearFlag() to clear the specified HASH flag.
  */
/** @brief Check whether or not the specified HASH flag is set.
  * @param hhash specifies the HASH handle.
  * @param flag  specifies the flag to check.
  *        This parameter must be a combination of @ref HASH_flags_definition.
  * @retval uint32_t The state of flag (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_HASH_IsActiveFlag(const hal_hash_handle_t *hhash, uint32_t flag)
{
  return (uint32_t)(((((HASH_TypeDef *)((uint32_t)(hhash->instance)))->SR & (flag)) == (flag)) ? 1U : 0U);
}

/** @brief Check whether the specified HASH interrupt source is enabled or not.
  * @param hhash     specifies the HASH handle.
  * @param interrupt source to check
  *         This parameter must be a combination of @ref HASH_interrupts_definition.
  * @retval uint32_t State of interruption (0 or 1).
  */
__STATIC_INLINE uint32_t HAL_HASH_GetITSource(const hal_hash_handle_t *hhash, uint32_t interrupt)
{
  return ((READ_BIT(((HASH_TypeDef *)((uint32_t)hhash->instance))->IMR, (uint32_t)interrupt)
           == (uint32_t)interrupt) ? 1U : 0U);
}

/** @brief Enable the specified HASH interrupt.
  * @param hhash     specifies the HASH handle.
  * @param interrupt specifies the HASH interrupt source to enable.
  *         This parameter must be a combination of @ref HASH_interrupts_definition.
  */
__STATIC_INLINE void HAL_HASH_EnableIT(hal_hash_handle_t *hhash, uint32_t interrupt)
{
  SET_BIT(((HASH_TypeDef *)((uint32_t)(hhash->instance)))->IMR, interrupt);
}

/** @brief Disable the specified HASH interrupt.
  * @param hhash     specifies the HASH handle.
  * @param interrupt specifies the HASH interrupt source to disable.
  *         This parameter must be a combination of @ref HASH_interrupts_definition.
  */
__STATIC_INLINE void HAL_HASH_DisableIT(hal_hash_handle_t *hhash, uint32_t interrupt)
{
  CLEAR_BIT(((HASH_TypeDef *)((uint32_t)(hhash->instance)))->IMR, interrupt);
}

/** @brief Clear the specified HASH flag.
  * @param hhash specifies the HASH handle.
  * @param flag  specifies the flag to clear.
  *        This parameter must be a combination of @ref HASH_flags_definition.
  */
__STATIC_INLINE void HAL_HASH_ClearFlag(hal_hash_handle_t *hhash, uint32_t flag)
{
  CLEAR_BIT(((HASH_TypeDef *)((uint32_t)(hhash->instance)))->SR, (flag));
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
#endif /* HASH */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_HASH_H */
