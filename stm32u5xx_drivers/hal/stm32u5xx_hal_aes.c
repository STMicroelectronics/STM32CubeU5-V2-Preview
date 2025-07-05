/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_aes.c
  * @brief   AES HAL module driver.
  *          This file provides Cryptography AES/SAES peripheral services.
  *
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

/* Includes ------------------------------------------------------------------ */
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined(AES) || defined(SAES)

/** @addtogroup AES
  * @{
  */
/** @defgroup AES_Introduction AES Introduction
  * @{

  - This introduction is under development.

  */
/**
  * @}
  */

/** @defgroup AES_How_To_Use AES How To Use
  * @{

# How to use the AES HAL module driver

## The AES main features:

This AES HAL driver is a generic driver which contains a set of APIs allowing to configure the AES/SAES
peripheral to an advanced encryption standard compliant algorithm in order to perform data encryption or decryption.

## The AES HAL driver can be used as follows:

### Initialization/De-initialization

- Declare a hal_aes_handle_t handle structure, for example: hal_aes_handle_t  haes

- Initialize the AES low level resources:
  - Enable the AES/SAES peripheral clock:
    - Either at the application level by calling the:
      - **HAL_RCC_AES_EnableClock()** API for AES instance
      - **HAL_RCC_SAES_EnableClock()** API for SAES instance
    - Or by setting the USE_HAL_AES_CLK_ENABLE_MODEL define to HAL_CLK_ENABLE_PERIPH_ONLY within the
      stm32u5xx_hal_conf.h file, in this case, the AES/SAES clock is enabled within
      the HAL_AES_Init() API
  - NVIC configuration to use interrupt process APIs (HAL_AES_Encrypt_IT() and HAL_AES_Decrypt_IT()):
    - Configure the AES interrupt priority
    - Enable the NVIC AES IRQ Channel
  - DMA Configuration to use DMA process APIs(HAL_AES_Encrypt_DMA() and HAL_AES_Decrypt_DMA()):
    - Declare a hal_dma_handle_t handle structure for the transfer input or transfer output channel
    - Enable the DMAx interface clock using
    - Configure the DMA handle parameters
    - Configure the DMA Inx or Outx channel
    - Associate the initialized DMA handle to the haes DMA In or Out handle
    - Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA In or Out channel

- Initialize the AES handle by calling the HAL_AES_Init() API that performs these operations:
  - The association of the instance to the handle
  - The initialization of the handle state to the HAL_AES_STATE_INIT

- De-initialize the AES/SAES peripheral by calling the HAL_AES_DeInit() API that performs these operations:
  - The disable of the AES/SAES peripheral
  - The abort of the DMA input and output transfers
  - The de-initialization of the current handle object
  - The reset of the handle state to the HAL_AES_STATE_RESET

### Configuration

- The Configuration of the AES/SAES peripheral is ensured through three steps:
  - Step1 (Chaining mode(algorithm) configuration according to the defined compilation algorithm flag):
    - By default, all the compilation algorithm flags are defined but the user can undefine the not needed ones to well
      optimize his code and gain footprint.
    - The AES compilation algorithm flags are:
       - USE_HAL_AES_ECB_CBC_ALGO flag: The AES/SAES peripheral can be configured with one of the
       two following chaining modes:
           - Electronic Code Book algorithm(ECB) by using HAL_AES_ECB_SetConfig() API, the user has not to set any
             parameter
           - Cipher Block Chaining algorithm(CBC) by using HAL_AES_CBC_SetConfig() API where the user must provide the
             initial vector
       - USE_HAL_AES_CTR_ALGO flag: The AES peripheral is configured to Counter chaining mode(CTR) by using
         HAL_AES_CTR_SetConfig() API where the user must provide the initial vector
       - USE_HAL_AES_GCM_GMAC_ALGO flag: The AES peripheral is configured to Galois/counter chaining mode(GCM/GMAC) by
         using HAL_AES_GCM_GMAC_SetConfig() API where the user must provide the header, its size and the initial vector
       - USE_HAL_AES_CCM_ALGO flag: The AES peripheral is configured to Counter with Cipher Block Chaining-Message(CCM)
         by using HAL_AES_CCM_SetConfig() API where the user must provide the header, its size and the B0
  - Step2 (Key configuration according to one of the following use cases):
    - Use the application normal key:
        - Call HAL_AES_SetNormalKey() API where the user must provide the key and its size
        - This API is available with AES/SAES peripheral
    - Use the SAES Hardware key:
        - Call HAL_AES_SetHWKey() API where the user must set the SAES hardware key and set its size and the key mode:
            - The normal key mode is set when to use the HW key to encrypt/decrypt application messages
            - The wrap key mode is set when to use the HW key to wrap/unwrap the application key
            - The share key mode is set when to use the HW key to share/unshare the application key
        - This API is only available with SAES peripheral
        - When the selected HW key is either the BHK or the DHUK_XOR_BHK, the user application must read it from TAMP
          backup registers before doing any encryption/decryption
    - Use the application key shared by SAES peripheral:
      This key mode aims to let the AES instance receive the key shared by SAES peripheral via secure hardware buses:
        - Call HAL_AES_SetSharedKey() API where the user must set the key size
        - This API is only available with AES peripheral
    - Use the application wrapped key:
      This key mode aims to let the SAES instance secure an application key by encrypting it with SAES Hardware key
      (wrapper key) and when the user intends to use it, he must decrypt it with the same wrapper key. This mode is
      ensured by applying the following sequence:
        - Call HAL_AES_SetHWKey() API where the user must select the SAES hardware key and set its size(Wrapper key),and
          set the key mode to wrapped mode
        - Call HAL_AES_WrapKey() API where the user must provide his application key to be encrypted with the configured
          wrapper key and an output key buffer where to write the encrypted key.
        - When the process ends, the user application must delete the original key to be secure.
        - When need to use the original key, the SAES peripheral must configure the same wrapper key by calling the
          HAL_AES_SetHWKey() API and unwrap the encrypted key by calling HAL_AES_UnwrapKey() API,
          when the process ends the decrypted key can't be read and it's loaded automatically into keys registers
          to be used for further encrypt/decrypt operations.
        - This API is only available with SAES peripheral
      The key size provided by the user as a parameter of HAL_AES_SetHWKey() API must be the same one provided for the
      HAL_AES_WrapKey() and HAL_AES_UnwrapKey() APIs
      When the selected wrapper key is either the BHK or the DHUK_XOR_BHK, the user application must read it from TAMP
      backup registers before calling both APIs HAL_AES_WrapKey() and HAL_AES_UnwrapKey()
  - Step3 (Configure the data swapping):
     - By default, the AES is configured to no swap. If the user provides swapped data he must configure the swap mode
       by using the HAL_AES_SetDataSwapping() API

- Skipping configuration steps use cases:
  - The step1 Configuration is always required before each one-shot message encrypt or decrypt, but when to encrypt or
    decrypt a single message with consecutive calls of processing API, the user must apply the configuration only before
    processing the first piece of this message.
  - The step2 Configuration is not required as long as the configured key has not been changed (step 2 must be redo
    after ECB or CBC decrypt as those algorithms decryption derivate the original key)
  - The step3 is always required before each one- shot message Encrypt/Decrypt when the provided data are swapped

### Sharing SAES key

The SAES peripheral can share user application keys with AES peripheral without being exposed in clear text.
The key sharing sequence involves both sides(The SAES sharing key peripheral and the AES target peripheral receiving the
shared key):
  - SAES peripheral sharing key:
    - Call HAL_AES_SetHWKey() API where the user must select the SAES hardware key and set its size(Wrapper key),and
      set the key mode to shared mode
    - Call HAL_AES_EncryptSharedKey() API where the user must provide his application key to be encrypted with the
      configured wrapper key and an output key buffer where to write the encrypted key in share mode.
      The user must specify the peripheral receiving the shared key by providing the target_id (target_id value is
      equal to 0 for U5 families)
    - When the process ends, the user application must delete the original key to be secure.
    - When need to share the original key with AES peripheral, the SAES peripheral must configure the same wrapper key
      by calling the HAL_AES_SetHWKey() API and decrypt the encrypted key in share mode using the
      HAL_AES_DecryptSharedKey() API
      when the decryption ends, the decrypted key can't be read and it's loaded automatically into hardware buses and
      shared with AES to be used for further AES encrypt/decrypt operations.
  - AES peripheral target receiving the shared key:
    - On the other side, the receiver of the shared key must be configured via HAL_AES_SetSharedKey() API

The key size provided by the user as a parameter of HAL_AES_SetHWKey() API must be the same one provided for the
HAL_AES_EncryptSharedKey() and HAL_AES_DecryptSharedKey() APIs
When the selected wrapper key is either the BHK or the DHUK_XOR_BHK, the user application must read it from TAMP backup
registers before calling both APIs HAL_AES_EncryptSharedKey() and HAL_AES_DecryptSharedKey()

### Polling mode IO operation

- Encrypt an amount of data in blocking mode using HAL_AES_Encrypt()
- Decrypt an amount of data in blocking mode using HAL_AES_Decrypt()

  - The driver only pads the missing words within a block (One block is equal to four words), when the user provides a
    data size not multiple of words, he must pad the missing bytes within his last word with zeros for GCM and CCM
    algorithms.

### TAG Generation

- Generate tag after encryption or decryption by using either HAL_AES_GCM_GenerateAuthTAG() API for GCM algorithm
  or HAL_AES_CCM_GenerateAuthTAG() API for CCM algorithm

### Interrupt mode IO operation

- Encrypt an amount of data in interrupt mode using HAL_AES_Encrypt_IT()
  - At end of transfer of data between user buffer and AES/SAES peripheral, HAL_AES_InCpltCallback() and
    HAL_AES_OutCpltCallback() are executed
- Decrypt an amount of data in interrupt mode using HAL_AES_Decrypt_IT()
  - At end of transfer of data between user buffer and AES/SAES peripheral, HAL_AES_InCpltCallback() and
    HAL_AES_OutCpltCallback() are executed

  - The driver only pads the missing words within a block (One block is equal to four words), when the user provides a
    data size not multiple of words, he must pad the missing bytes within his last word with zeros for GCM and CCM
    algorithms.

### DMA mode IO operation

- Encrypt/decrypt an amount of data after transfer from input user buffer to AES/SAES peripheral and get
  encrypted / decrypted data from AES/SAES peripheral via DMA using HAL_AES_Encrypt_DMA() or
  HAL_AES_Decrypt_DMA()
  - The minimum data amount transferred with DMA must be equal to one block (four complete words), as the DMA transfer
    does not support the padding(the driver handles the padding with a direct transfer of the incomplete data without
    using the DMA)
  - At the end of a transfer of data from the user buffer to the AES/SAES peripheral, one of these
    callbacks is generated:
    - AES_ECB_CBC_CTR_DMAInCplt() which generates the HAL_AES_InCpltCallback() callback
    - AES_GCM_GMAC_CCM_DMAInCplt() is executed after the header phase blocks transfer to handle the padding if exist and
      to initiate the payload phase in case of plaintext not null. The HAL_AES_InCpltCallback() is then generated

  - At the end of a transfer of data from AES/SAES peripheral to the user buffer, one of these callbacks is
   generated:
     - AES_ECB_CBC_CTR_DMAOutCplt() where the operation is completed and the AES is disabled and which generates the
       HAL_AES_OutCpltCallback() callback
     - AES_GCM_GMAC_CCM_DMAOutCplt() is executed after the payload phase blocks transfer to handle the padding if exist
       and to end the operation by generating the HAL_AES_OutCpltCallback()

  - If a hardware AES DMA error happens during DMA transfer a AES_DMAError() callback is generated to end the operation
    and generates HAL_AES_ErrorCallback()

### Suspend Resume management

The user can resort to the suspend/resume feature for two purposes and under the following conditions:
  - The USE_HAL_AES_SUSPEND_RESUME compilation flag must be defined
  - Suspend conditions:
      - Only IT mode processes can be suspended
      - The suspension is only possible after the completion of processing an entire block
      - The suspension is not possible when one block only lasts to be processed (It's too late to suspend
        the operation)
  - Purpose1(without context modification): Suspend a process due to time constraints and resume it later
      - Call HAL_AES_RequestSuspend() API to request suspension
      - When suspended, a HAL_AES_SuspendCallback callback is generated
      - Call HAL_AES_Resume() API to restore the suspended process from the suspended endpoint
  - Purpose2(with context modification): Suspend a low priority message processing to process a high priority message
    instead
      - Call HAL_AES_RequestSuspend() API to request suspension
      - When suspended, a HAL_AES_SuspendCallback callback is generated
      - Call HAL_AES_SaveContext() API where the user must provide a structure to save in it all the internal data
        needed to restart later on, then the user application must change the context in order to process the
        high priority message (Change the peripheral, the configuration , the AES operation ...)
      - When the high priority message processing is over, call the HAL_AES_RestoreContext() API with the already filled
        structure to restore the low priority suspended context
      - Call HAL_AES_Resume() API to restore the suspended process from the suspended endpoint

### Callback registration

The USE_HAL_AES_REGISTER_CALLBACKS compilation flag when set to 1 allows the user to configure dynamically the driver
following callbacks:
 - HAL_AES_RegisterInTransferCpltCallback: callback for end of transfer of data
 - HAL_AES_RegisterOutTransferCpltCallback: callback for end of transfer of data
 - HAL_AES_RegisterErrorCallback: callback for error.
 - HAL_AES_RegisterSuspendCallback: callback for suspend.
When the compilation flag is set to 0 or not defined, the callback registration feature is not available and all
callbacks are set to the corresponding weak functions.
  */
/**
  * @}
  */

/** @defgroup AES_Configuration_Table AES Configuration Table
  * @{
## Configuration inside the AES driver

Config defines                 | Description     | Default value     | Note
------------------------------ | --------------- | ----------------- | ----------------------------------------
PRODUCT                        | from IDE        | NA                | Ex:STM32U5xx
USE_HAL_AES_MODULE             | from hal_conf.h | 1                 | Enable the HAL AES module
USE_HAL_AES_CLK_ENABLE_MODEL   | from hal_conf.h | HAL_CLK_ENABLE_NO | Enable the HAL_AES_CLK
USE_ASSERT_DBG_PARAM           | from IDE        | NA                | Enable the parameters asserts
USE_ASSERT_DBG_STATE           | from IDE        | NA                | Enable the state asserts
USE_HAL_CHECK_PARAM            | from hal_conf.h | 0                 | Parameters runtime check
USE_HAL_SECURE_CHECK_PARAM     | from hal_conf.h | 0                 | Parameters runtime check for sensitive APIs
USE_HAL_CHECK_PROCESS_STATE    | from hal_conf.h | 0                 | Allows to use the load and store exclusive.
USE_HAL_AES_DMA                | from hal_conf.h | 1                 | Allows to use DMA mode
USE_HAL_AES_ECB_CBC_ALGO       | from hal_conf.h | 1                 | Allows to use ECB and CBC algorithms
USE_HAL_AES_CTR_ALGO           | from hal_conf.h | 1                 | Allows to use CTR algorithm
USE_HAL_AES_GCM_GMAC_ALGO      | from hal_conf.h | 1                 | Allows to use GCM and GMAC algorithms
USE_HAL_AES_CCM_ALGO           | from hal_conf.h | 1                 | Allows to use CCM algorithm
USE_HAL_AES_SUSPEND_RESUME     | from hal_conf.h | 1                 | Allows to use Suspend features
USE_HAL_AES_REGISTER_CALLBACKS | from hal_conf h | 0                 | Allows to use register callbacks
USE_HAL_AES_GET_LAST_ERRORS    | from hal_conf.h | 0                 | Allows to use error code mechanism
USE_HAL_AES_USER_DATA          | from hal_conf.h | 0                 | Allows to use user data
  */
/**
  * @}
  */
#if defined(USE_HAL_AES_MODULE) && (USE_HAL_AES_MODULE == 1U)
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
    || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1)) \
    || (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1))\
    || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))

/* Private constants ---------------------------------------------------------*/
/** @defgroup AES_Private_Constants AES Private Constants
  * @{
  */
/*! AES Algorithm Modes */
#define AES_ALGORITHM_ECB      0x00000000U                       /*!< Electronic codebook chaining algorithm */
#define AES_ALGORITHM_CBC      AES_CR_CHMOD_0                    /*!< Cipher block chaining algorithm */
#define AES_ALGORITHM_CTR      AES_CR_CHMOD_1                    /*!< Counter mode chaining algorithm */
#define AES_ALGORITHM_GCM_GMAC (AES_CR_CHMOD_0 | AES_CR_CHMOD_1) /*!< Galois counter mode - Galois message
                                                                      authentication code */
#define AES_ALGORITHM_CCM      AES_CR_CHMOD_2                    /*!< Counter with Cipher Mode */

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
/*! AES suspend request enumeration definition */
#define AES_SUSPEND_NONE 0x00U /*!< AES processing suspension is not requested */
#define AES_SUSPEND      0x01U /*!< AES processing suspension is requested */
#endif /* USE_HAL_AES_SUSPEND_RESUME */

/*! AES Operating Modes */
#define AES_OPERATING_MODE_ENCRYPT       0x00000000U   /*!< Encryption mode */
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
#define AES_OPERATING_MODE_KEYDERIVATION AES_CR_MODE_0 /*!< Key derivation mode only used when performing ECB and CBC
                                                            decryptions */
#endif /* USE_HAL_AES_ECB_CBC_ALGO */
#define AES_OPERATING_MODE_DECRYPT       AES_CR_MODE_1 /*!< Decryption mode */

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1))\
|| (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
/*! AES GCM GMAC CCM Phases */
#define AES_PHASE_INIT              0x00000000U    /*!< GCM/GMAC (or CCM) init phase */
#define AES_PHASE_HEADER            AES_CR_GCMPH_0 /*!< GCM/GMAC or CCM header phase */
#define AES_PHASE_PAYLOAD           AES_CR_GCMPH_1 /*!< GCM(/CCM) payload phase      */
#define AES_PHASE_FINAL             AES_CR_GCMPH   /*!< GCM/GMAC or CCM final phase */
#endif /* USE_HAL_AES_GCM_GMAC_ALGO || USE_HAL_AES_CCM_ALGO */

/*! AES Timeout Values */
#define AES_GENERAL_TIMEOUT_MS      82U  /*!< General AES operation timeout in milliseconds */
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1))\
|| (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
#define AES_INIT_PHASE_LATENCY      88U  /*!< The latency of GCM/CCM init phase to prepare hash subkey */
#define AES_HEADER_PHASE_LATENCY    240U /*!< The latency of GCM/CCM header phase is 240 clock cycles */
#define AES_PAYLOAD_PHASE_LATENCY   486U /*!< The latency of GCM/CCM header phase is 486 clock cycles */
#endif /* USE_HAL_AES_GCM_GMAC_ALGO || USE_HAL_AES_CCM_ALGO */
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
#define AES_KEY_DERIVATION_LATENCY  82U  /*!< The latency of key preparation operation is 82 clock cycles */
#endif /* USE_HAL_AES_ECB_CBC_ALGO */
#define SAES_KEY_DERIVATION_LATENCY 324U /*!< The latency of key preparation operation is 324 clock cycles */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup AES_Private_Macros AES Private Macros
  * @{
  */
/*! Macro to get the handle instance */
#define AES_GET_INSTANCE(handle) ((AES_TypeDef *)((uint32_t)(handle)->instance))

/*! Macro to check the key size */
#define IS_AES_KEY_SIZE(key_size) (((key_size) == HAL_AES_KEY_SIZE_128BIT) || ((key_size) == HAL_AES_KEY_SIZE_256BIT))

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
/*! Macro to check the key size alignment between the wrapper key and the user key */
#define IS_AES_HW_KEY_SIZE(handle,key_size) ((uint32_t)key_size == \
                                             ((AES_GET_INSTANCE(handle)->CR) & (AES_CR_KEYSIZE)))
/*! Macro to check the key select */
#define IS_AES_KEY_SELECT(key_select) (((key_select) == HAL_AES_KEY_SELECT_DHUK) \
                                       || ((key_select) == HAL_AES_KEY_SELECT_BHK) \
                                       || ((key_select) == HAL_AES_KEY_SELECT_DHUK_XOR_BHK))

/*! Macro to check the key mode */
#define IS_AES_KEY_MODE(key_mode) (((key_mode) == HAL_AES_KEY_MODE_NORMAL) || ((key_mode) == HAL_AES_KEY_MODE_WRAPPED) \
                                   || ((key_mode) == HAL_AES_KEY_MODE_SHARED))
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

/*! Macro to check the data swapping */
#define IS_AES_DATA_SWAPPING(data_swapping) (((data_swapping) == HAL_AES_DATA_SWAPPING_NO) \
                                             || ((data_swapping) == HAL_AES_DATA_SWAPPING_HALFWORD) \
                                             || ((data_swapping) == HAL_AES_DATA_SWAPPING_BYTE) \
                                             || ((data_swapping) == HAL_AES_DATA_SWAPPING_BIT))

/*! Macro to enable the AES/SAES peripheral */
#define AES_ENABLE(handle) (AES_GET_INSTANCE(handle)->CR |=  AES_CR_EN)

/*! Macro to disable the AES/SAES peripheral */
#define AES_DISABLE(handle) (AES_GET_INSTANCE(handle)->CR &=  ~AES_CR_EN)
/**
  * @}
  */

/** @defgroup AES_Private_Functions AES Private Functions
  * @{
  */
static void AES_SetNormalKey(hal_aes_handle_t *haes, hal_aes_key_size_t key_size, const uint32_t *p_key);
static hal_status_t AES_WaitForSetKey(hal_aes_handle_t *haes);
static void AES_SetIV(hal_aes_handle_t *haes, const uint32_t *p_init_vect);
static hal_status_t AES_ProcessOneblock(hal_aes_handle_t *haes, uint32_t timeout_ms);
static hal_status_t AES_WaitOnCCFlag(hal_aes_handle_t *haes, uint32_t timeout_ms);
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
   || (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
static hal_status_t AES_WaitOnCCFlag_NonBlocking(hal_aes_handle_t *haes, uint32_t latency_clock_cycle);
#endif /* USE_HAL_AES_ECB_CBC_ALGO or USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
static void AES_DMAError(hal_dma_handle_t *hdma);
#endif /* USE_HAL_AES_DMA */

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
static hal_status_t AES_RNGFetchGetStatus(hal_aes_handle_t *haes);
static hal_status_t AES_KeyDerivation(hal_aes_handle_t *haes);
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
static hal_status_t AES_ECB_CBC_CTR_Process(hal_aes_handle_t *haes, uint32_t timeout_ms);
static void AES_ECB_CBC_CTR_Start_Process_IT(hal_aes_handle_t *haes);
static void AES_ECB_CBC_CTR_Process_IT(hal_aes_handle_t *haes);
#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
static hal_status_t AES_ECB_CBC_CTR_Process_DMA(hal_aes_handle_t *haes);
static void AES_ECB_CBC_CTR_DMAInCplt(hal_dma_handle_t *hdma);
static void AES_ECB_CBC_CTR_DMAOutCplt(hal_dma_handle_t *hdma);
#endif /* USE_HAL_AES_DMA */
#endif /* USE_HAL_AES_ECB_CBC_ALGO or USE_HAL_AES_CTR_ALGO */

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
static hal_status_t AES_GCM_GMAC_CCM_Process(hal_aes_handle_t *haes, uint32_t timeout_ms);
static hal_status_t AES_SetInitPhase(hal_aes_handle_t *haes, uint32_t timeout_ms);
static hal_status_t AES_SetHeaderPhase(hal_aes_handle_t *haes, uint32_t timeout_ms);
static hal_status_t AES_SetPayloadPhase(hal_aes_handle_t *haes, uint32_t timeout_ms);
static hal_status_t AES_PaddingData(hal_aes_handle_t *haes, const uint32_t *p_tmp_in_buff, uint32_t remaining_bytes,
                                    uint32_t timeout_ms);
static hal_status_t AES_GCM_GMAC_CCM_Start_Process_IT(hal_aes_handle_t *haes);
static hal_status_t AES_SetInitPhase_NonBlocking(hal_aes_handle_t *haes);
static void AES_SetHeaderPhase_IT(hal_aes_handle_t *haes);
static void AES_StartPayloadPhase_IT(hal_aes_handle_t *haes);
static void AES_SetPayloadPhase_IT(hal_aes_handle_t *haes);
static void AES_PaddingData_IT(hal_aes_handle_t *haes, const uint32_t *p_tmp_in_buff, uint32_t remaining_bytes);
#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
static hal_status_t AES_GCM_GMAC_CCM_Process_DMA(hal_aes_handle_t *haes);
static hal_status_t AES_SetPayloadPhase_DMA(hal_aes_handle_t *haes);
static hal_status_t AES_SetHeaderPhase_DMA(hal_aes_handle_t *haes);
static hal_status_t AES_PaddingData_DMA(hal_aes_handle_t *haes, const uint32_t *p_tmp_in_buff, uint32_t remaining_bytes,
                                        uint32_t latency_clock_cycle);
static void AES_GCM_GMAC_CCM_DMAInCplt(hal_dma_handle_t *hdma);
static void AES_GCM_GMAC_CCM_DMAOutCplt(hal_dma_handle_t *hdma);
#endif /* USE_HAL_AES_DMA */
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup AES_Exported_Functions
  * @{
  */

/** @addtogroup AES_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the AES/SAES
peripheral:
- The HAL_AES_Init() API: Allows initializing the HAL AES driver so it can be configured and used to encrypt
  a plaintext
  or decrypt a ciphertext
  This API is the first API to call when using the HAL AES, it takes 2 parameters as input:
 - The HAL AES handle: A pointer to a @ref hal_aes_handle_t structure
 - The AES instance: A value from the enumeration  @ref hal_aes_t
- The HAL_AES_DeInit() API: Allows de-initializing the HAL AES driver by:
   - Disabling the AES/SAES peripheral
   - Abort DMA input and output transfers
   - De-initializing the current handle object
   - Resetting the handle global state to the **HAL_AES_STATE_RESET**
  */

/**
  * @brief  Initialize the HAL AES handle and associate it to an instance.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  instance          @ref hal_aes_t enumerated type variable to be set according to the physical instance
  * @retval HAL_INVALID_PARAM Invalid param return when the AES handle is NULL
  * @retval HAL_OK            The HAL AES driver is initialized according to the given handle and instance
  */
hal_status_t HAL_AES_Init(hal_aes_handle_t *haes, hal_aes_t instance)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM((IS_AES_ALL_INSTANCE((AES_TypeDef *)(uint32_t)instance))
                   || (IS_SAES_ALL_INSTANCE((AES_TypeDef *)(uint32_t)instance)));

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  haes->instance = instance;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  haes->p_in_cplt_cb  = HAL_AES_InCpltCallback;  /* Input FIFO transfer completed callback */
  haes->p_out_cplt_cb = HAL_AES_OutCpltCallback; /* Output FIFO transfer completed callback */
  haes->p_error_cb    = HAL_AES_ErrorCallback;
#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
  haes->p_suspend_cb  = HAL_AES_SuspendCallback;
#endif /* defined (USE_HAL_AES_SUSPEND_RESUME) */
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

#if defined(USE_HAL_AES_USER_DATA) && (USE_HAL_AES_USER_DATA == 1)
  haes->p_user_data = NULL;
#endif /* (USE_HAL_AES_USER_DATA) */

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1U)
  haes->hdma_in = (hal_dma_handle_t *)NULL;
  haes->hdma_out = (hal_dma_handle_t *)NULL;
#endif /* USE_HAL_AES_DMA */

#if defined(USE_HAL_AES_CLK_ENABLE_MODEL) && (USE_HAL_AES_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  if (haes->instance == HAL_AES)
  {
    HAL_RCC_AES_EnableClock();
  }
  else
  {
    HAL_RCC_RNG_EnableClock();
    HAL_RCC_SAES_EnableClock();
  }
#endif /* USE_HAL_AES_CLK_ENABLE_MODEL */

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
  haes->suspend_request = AES_SUSPEND_NONE;
#endif /* USE_HAL_AES_SUSPEND_RESUME */
  haes->global_state = HAL_AES_STATE_INIT;
  return HAL_OK;
}

/**
  * @brief  De-initialize the AES/SAES peripheral.
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  */
void HAL_AES_DeInit(hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_AES_ALL_INSTANCE(AES_GET_INSTANCE(haes)) || IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
  uint32_t tmp = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN | AES_CR_DMAOUTEN);

  if (tmp  != 0U)
  {
    /* Disable the DMA transfer */
    CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN | AES_CR_DMAOUTEN);

    /* Disable the DMA transmit on the DMA side */
    (void)HAL_DMA_Abort(haes->hdma_in);

    /* Disable the DMA receive on the DMA side */
    (void)HAL_DMA_Abort(haes->hdma_out);
  }
#endif /* USE_HAL_AES_DMA */

  AES_DISABLE(haes);

  /* Set IPRST for software reset */
  SET_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_IPRST);

  /* Clear IPRST to allow writing registers */
  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_IPRST);

  haes->global_state = HAL_AES_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup AES_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the AES/SAES peripheral through
three steps:
- Step1: Chaining mode(algorithm) configuration APIs:
       - HAL_AES_ECB_SetConfig()      :Allowing to configure the AES/SAES peripheral with the ECB algorithm
       - HAL_AES_CBC_SetConfig()      :Allowing to configure the AES/SAES peripheral with the CBC algorithm
       - HAL_AES_CTR_SetConfig()      :Allowing to configure the AES peripheral with the CTR algorithm
       - HAL_AES_GCM_GMAC_SetConfig() :Allowing to configure the AES peripheral with the GCM_GMAC algorithms
       - HAL_AES_CCM_SetConfig()      :Allowing to configure the AES peripheral with the CCM algorithm
- Step2: Key configuration APIs:
       - HAL_AES_SetNormalKey()       :Allowing to configure the application normal key
       - HAL_AES_SetHWKey()           :Allowing to configure the SAES peripheral hardware key for normal, wrap or share
                                       mode use
       - HAL_AES_SetSharedKey()       :Allowing to configure the AES peripheral shared key
- Step3: Data swapping mode configuration APIs:
       - HAL_AES_SetDataSwapping()    :Allowing to configure the data swapping mode
       - HAL_AES_GetDataSwapping()    :Allowing to retrieve the data swapping mode
- Other configuration APIs:
   - HAL_AES_EnableKeyProtection()    :Allowing to protect the SAES key from being accessed by another peripheral
   - HAL_AES_DisableKeyProtection()   :Allowing to disable the SAES key protection
   - HAL_AES_IsEnabledKeyProtection() :Allowing to check if the SAES key protection is enabled or disabled
  */
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
/**
  * @brief  Configure the AES/SAES peripheral with ECB algorithm.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @note   The user has not to set any parameter
  * @retval HAL_INVALID_PARAM Invalid param return when the AES handle is NULL
  * @retval HAL_ERROR Error detected while fetching a random number from RNG peripheral (only for SAES instance)
  * @retval HAL_OK    AES/SAES peripheral has been correctly configured with ECB algorithm
  */
hal_status_t HAL_AES_ECB_SetConfig(hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  /* Fetch random numbers from RNG after enabling RNG and SAES clocks, SAES supports only ECB and CBC algorithms */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if ((haes->instance == (uint32_t)SAES_S) || (haes->instance == (uint32_t)SAES_NS))
#else
  if (haes->instance == HAL_SAES)
#endif /* USE_HAL_SECURE_CHECK_PARAM */
  {
    if (AES_RNGFetchGetStatus(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  AES_DISABLE(haes);
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_KEYSEL | AES_CR_DATATYPE, AES_ALGORITHM_ECB);

  haes->data_size_sum_byte = 0U;
  haes->algorithm = AES_ALGORITHM_ECB;

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  Configure the AES/SAES peripheral with CBC algorithm.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_init_vect       Pointer to **const uint32_t** four words buffer provided by the user. For CBC algorithm,
  *                           the init vector is used to process only the first data block
  * @retval HAL_INVALID_PARAM Invalid param return when the provided init vector pointer or handle pointer is null
  * @retval HAL_ERROR         Error detected while fetching a random number from RNG peripheral (only for SAES instance)
  * @retval HAL_OK            AES/SAES peripheral has been correctly configured with CBC algorithm
  */
hal_status_t HAL_AES_CBC_SetConfig(hal_aes_handle_t *haes, const uint32_t *p_init_vect)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_init_vect != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_init_vect == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  /* Fetch random numbers from RNG after enabling RNG and SAES clocks, SAES supports only ECB and CBC algorithms */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if ((haes->instance == (uint32_t)SAES_S) || (haes->instance == (uint32_t)SAES_NS))
#else
  if (haes->instance == HAL_SAES)
#endif /* USE_HAL_SECURE_CHECK_PARAM */
  {
    if (AES_RNGFetchGetStatus(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  AES_DISABLE(haes);
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_KEYSEL | AES_CR_DATATYPE, AES_ALGORITHM_CBC);

  AES_SetIV(haes, p_init_vect);

  haes->data_size_sum_byte = 0U;
  haes->algorithm = AES_ALGORITHM_CBC;

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  Configure the SAES Hardware key.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @param  key_select        key selection with a **hal_aes_key_select_t** type
  * @param  key_mode          key mode with a **hal_aes_key_mode_t** type
  * @retval HAL_INVALID_PARAM Invalid param return when the handle instance is other than SAES or the handle pointer
  *                           is null
  * @retval HAL_ERROR         Error when loading the key into registers exceeds the dedicated timeout
  * @retval HAL_OK            Hardware key has been configured
  */
hal_status_t HAL_AES_SetHWKey(hal_aes_handle_t *haes, hal_aes_key_size_t key_size, hal_aes_key_select_t key_select,
                              hal_aes_key_mode_t key_mode)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(IS_AES_KEY_SIZE(key_size));
  ASSERT_DBG_PARAM(IS_AES_KEY_SELECT(key_select));
  ASSERT_DBG_PARAM(IS_AES_KEY_MODE(key_mode));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (haes->instance != HAL_SAES)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_AES_ClearFlagKERR(haes);

  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYSEL | AES_CR_KEYSIZE | AES_CR_KMOD,
             (uint32_t)key_select | (uint32_t)key_size | (uint32_t)key_mode);

  if (AES_WaitForSetKey(haes) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the protection of the SAES key from being accessed by another security context application.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_INVALID_PARAM Invalid param return when the handle instance is other than SAES or the handle pointer
  *                           is null
  * @retval HAL_OK            SAES key protection has been enabled
  */
hal_status_t HAL_AES_EnableKeyProtection(hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (haes->instance != HAL_SAES)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  AES_DISABLE(haes);
  SET_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYPROT);

  return HAL_OK;
}

/**
  * @brief  Disable the SAES key protection.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_INVALID_PARAM Invalid param return when the handle instance is other than SAES or the handle pointer
  *                           is null
  * @retval HAL_OK            SAES key protection has been disabled
  */
hal_status_t HAL_AES_DisableKeyProtection(hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (haes->instance != HAL_SAES)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  AES_DISABLE(haes);
  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYPROT);

  return HAL_OK;
}

/**
  * @brief  Check whether the SAES key protection is already enabled or not.
  * @param  haes                            Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_AES_KEY_PROTECTION_ENABLED  The SAES key protection is enabled
  * @retval HAL_AES_KEY_PROTECTION_DISABLED The SAES key protection is disabled
  */
hal_aes_key_protection_status_t HAL_AES_IsEnabledKeyProtection(const hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

  return ((READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYPROT) != 0U) ? HAL_AES_KEY_PROTECTION_ENABLED
          : HAL_AES_KEY_PROTECTION_DISABLED);
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1)
/**
  * @brief  Configure the AES peripheral with the CTR algorithm, available only with AES instance.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_init_vect       Pointer to **const uint32_t** four words buffer provided by the user. For CTR algorithm,
  *                           the init vector is used to process each data block
  * @retval HAL_INVALID_PARAM Invalid param return when the provided init vector pointer is null or the handle pointer
  *                           is null
  *                           or the handle instance is not HAL_AES
  * @retval HAL_OK            AES peripheral has been correctly configured with the CTR algorithm
  */
hal_status_t HAL_AES_CTR_SetConfig(hal_aes_handle_t *haes, const uint32_t *p_init_vect)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_AES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_init_vect != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_init_vect == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (haes->instance != HAL_AES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  AES_DISABLE(haes);
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_DATATYPE, AES_ALGORITHM_CTR);

  AES_SetIV(haes, p_init_vect);

  haes->data_size_sum_byte = 0U;
  haes->algorithm = AES_ALGORITHM_CTR;

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* USE_HAL_AES_CTR_ALGO */

#if defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)
/**
  * @brief  Configure the AES peripheral with the GCM_GMAC algorithm, available only with AES instance.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_config          Pointer to a @ref hal_aes_gcm_config_t structure that contains the AES configuration with
  *                           GCM_GMAC algorithms
  * @retval HAL_INVALID_PARAM  Invalid param return when:
  *                           - The configuration structure pointer is null
  *                           - The provided init vector pointer within the configuration structure is null
  *                           - The provided header within the configuration structure is null but its size is not null
  *                           - The handle pointer is null
  *                           - The handle instance is not HAL_AES
  * @retval HAL_OK            AES peripheral has been correctly configured with the GCM_GMAC algorithm
  */
hal_status_t HAL_AES_GCM_GMAC_SetConfig(hal_aes_handle_t *haes, const hal_aes_gcm_config_t *p_config)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_AES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_init_vect != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_init_vect == NULL) || ((p_config->p_header == NULL)
                                                                && (p_config->header_size_byte != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (haes->instance != HAL_AES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  AES_DISABLE(haes);
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_DATATYPE | AES_CR_GCMPH | AES_CR_NPBLB,
             AES_ALGORITHM_GCM_GMAC);

  AES_SetIV(haes, p_config->p_init_vect);

  haes->p_header = p_config->p_header;
  haes->header_size_byte = p_config->header_size_byte;
  haes->data_size_sum_byte = 0U;
  haes->algorithm = AES_ALGORITHM_GCM_GMAC;

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* USE_HAL_AES_GCM_GMAC_ALGO */

#if defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1)
/**
  * @brief  Configure the AES with the CCM algorithm, available only with AES instance.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_config          Pointer to a @ref hal_aes_ccm_config_t structure
  * @retval HAL_INVALID_PARAM Invalid param return when:
  *                           - The configuration structure pointer is null
  *                           - The provided b0 within the configuration structure is null
  *                           - The provided header within the configuration structure is null but its size is not null
  *                           - The handle pointer is null
  *                           - The handle instance is not HAL_AES
  * @retval HAL_OK            AES peripheral has been correctly configured with the CCM algorithm
  */
hal_status_t HAL_AES_CCM_SetConfig(hal_aes_handle_t *haes, const hal_aes_ccm_config_t *p_config)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_AES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_b0 != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_b0 == NULL) || ((p_config->p_header == NULL)
                                                         && (p_config->header_size_byte != 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (haes->instance != HAL_AES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  AES_DISABLE(haes);
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_DATATYPE | AES_CR_GCMPH | AES_CR_NPBLB,
             AES_ALGORITHM_CCM);

  AES_SetIV(haes, p_config->p_b0);

  haes->p_header = p_config->p_header;
  haes->header_size_byte = p_config->header_size_byte;
  haes->data_size_sum_byte = 0U;
  haes->algorithm = AES_ALGORITHM_CCM;

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* USE_HAL_AES_CCM_ALGO */

/**
  * @brief  Configure the AES Normal key(key size, key value), supports both AES and SAES instances.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @param  p_key             A **uint32_t** AES key that must be coherent with the **key_size**
  * @retval HAL_INVALID_PARAM Invalid param return when the provided pointer key is null or the handle
  *                           pointer is null
  * @retval HAL_ERROR         Error when loading the key into registers exceeds the dedicated timeout
  * @retval HAL_OK            Normal key has been configured
  */
hal_status_t HAL_AES_SetNormalKey(hal_aes_handle_t *haes, hal_aes_key_size_t key_size, const uint32_t *p_key)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_key != NULL);
  ASSERT_DBG_PARAM(IS_AES_KEY_SIZE(key_size));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_key == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_AES_ClearFlagKERR(haes);

  if (haes->instance == HAL_AES)
  {
    MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYSIZE, (uint32_t)key_size);
  }
  else
  {
    MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYSIZE | AES_CR_KEYSEL, (uint32_t)key_size);
  }

  AES_SetNormalKey(haes, key_size, p_key);

  if (AES_WaitForSetKey(haes) != HAL_OK)
  {
    return HAL_ERROR;
  }

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
  haes->p_key = p_key;
#endif /* USE_HAL_AES_SUSPEND_RESUME */

  return HAL_OK;
}

/**
  * @brief  Configure the AES shared key mode to acquire the key shared by the SAES peripheral.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @warning The configured size must be the same as the size of the shared key
  * @retval  HAL_INVALID_PARAM Invalid param return when the handle instance is other than AES or the handle
  *                            pointer is null
  * @retval  HAL_ERROR         Error when loading the key into registers exceeds the dedicated timeout
  * @retval  HAL_OK            Normal key has been configured
  */
hal_status_t HAL_AES_SetSharedKey(hal_aes_handle_t *haes, hal_aes_key_size_t key_size)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_AES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(IS_AES_KEY_SIZE(key_size));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (haes->instance != HAL_AES)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_AES_ClearFlagKERR(haes);

  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_KMOD | AES_CR_KEYSIZE,
             (uint32_t)AES_CR_KMOD_1 | (uint32_t)key_size);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KERR) == 0U)
  {
    if (AES_WaitForSetKey(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the AES data swapping.
  * @param  haes          Pointer to a @ref hal_aes_handle_t structure
  * @param  data_swapping AES data swapping with a **hal_aes_data_swapping_t** type
  * @retval HAL_OK        The AES data swapping mode is set
  */
hal_status_t HAL_AES_SetDataSwapping(hal_aes_handle_t *haes, hal_aes_data_swapping_t data_swapping)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_AES_DATA_SWAPPING(data_swapping));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_DATATYPE, (uint32_t)data_swapping);

  return HAL_OK;
}

/**
  * @brief  Retrieve the AES configured data swapping.
  * @param  haes                  Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_AES_NO_SWAP       The bit order of the input and output data is not affected
  * @retval HAL_AES_HALFWORD_SWAP The bit- reversal is done by halfword Ex: 0011 1100 0100 1101 --> 0100 1101 0011 1100
  * @retval HAL_AES_BYTE_SWAP     The bit- reversal is done by byte Ex: 0011 1100 0100 1101 --> 1101 0100 1100 0011
  * @retval HAL_AES_BIT_SWAP      The bit- reversal is done by bit Ex: 0011 1100 0100 1101 --> 1011 0010 0011 1100
  */
hal_aes_data_swapping_t HAL_AES_GetDataSwapping(const hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

  return ((hal_aes_data_swapping_t)(uint32_t)READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DATATYPE));
}
/**
  * @}
  */

/** @addtogroup AES_Exported_Functions_Group3
  * @{
 This subsection provides a set of functions allowing to perform AES processing and manage suspension/resumption:
  - HAL_AES_Encrypt()        :Allowing to encrypt a plaintext within a dedicated timeout
  - HAL_AES_Decrypt()        :Allowing to decrypt a ciphertext within a dedicated timeout
  - HAL_AES_Encrypt_IT()     :Allowing to encrypt a plaintext using the AES interrupt
  - HAL_AES_Decrypt_IT()     :Allowing to decrypt a ciphertext using the AES interrupt
  - HAL_AES_Encrypt_DMA()    :Allowing to encrypt a plaintext using the DMA
  - HAL_AES_Decrypt_DMA()    :Allowing to decrypt a ciphertext using the DMA
  - HAL_AES_RequestSuspend() :Allowing to request an IT process suspension
  - HAL_AES_SaveContext()    :Allowing to save the context of the suspended process to start another high priority one
  - HAL_AES_RestoreContext() :Allowing to restore the saved context of the low prior process
  - HAL_AES_Resume()         :Allowing to resume the low prior process
  */
/**
  * @brief  Encrypt user data in polling mode.
  *       - For ECB, CBC or CTR algorithms:
  *                           - the padding is not supported
  *                           - only the encryption of the plaintext is available (no preparation for tag generation)
  *       - For GCM algorithm:- HAL_AES_Encrypt() is used either to:
  *                           - Encrypt a plaintext and use the header to prepare for the tag generation
  *                           - or just do the encryption (header null)
  *                           - or just prepare for tag generation (plaintext null)
  *       - For GMAC algorithm: Prepare for the tag generation only (plaintext null)
  *       - For CCM algorithm:- HAL_AES_Encrypt() is used either to:
  *                           - Encrypt a plaintext and use the header to prepare for the tag generation
  *                           - or just do the encryption (header null)
  *                           - or just prepare for tag generation (plaintext null)(not recommended by NIST)
  * @param   haes              Pointer to a @ref hal_aes_handle_t structure
  * @param   p_input           Pointer to aligned **const void** plaintext
  * @param   size_byte         Length of the plaintext buffer that must be in byte
  * @param   p_output          Pointer to aligned **void** data buffer to be filled with the encrypted text
  * @param   timeout_ms        Specify timeout value in milliseconds
  * @warning No swapped user data must be provided in big-endian. When data are provided in little-endian, the user must
  *          configure the swapping mode before starting the process (ex when data are provided as little- endian bytes
  *          the swap mode must be set to HAL_AES_BYTE_SWAP or when data are provided as little- endian halfwords, the
  *          ,swap mode must be set to HAL_AES_HALFWORD_SWAP)
  * @retval  HAL_INVALID_PARAM For ECB, CBC or CTR algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null
  *                             - Or the output data buffer pointer is null
  *                             - Or the input buffer is empty \n
  *                            For GCM_GMAC or CCM algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null but its size is # 0U
  *                            The handle pointer is null
  *                            The provided timeout is null
  * @retval  HAL_BUSY          Another AES process is ongoing
  * @retval  HAL_ERROR         Error return when the loaded key is invalid
  * @retval  HAL_TIMEOUT       AES encryption exceeds user timeout
  * @retval  HAL_OK            AES encryption is successfully accomplished
  */
hal_status_t HAL_AES_Encrypt(hal_aes_handle_t *haes, const void *p_input, uint16_t size_byte, void *p_output,
                             uint32_t timeout_ms)
{
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_PARAM(haes != NULL);
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    ASSERT_DBG_PARAM(p_input != NULL);
    ASSERT_DBG_PARAM(p_output != NULL);
    ASSERT_DBG_PARAM(size_byte != 0U);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if ((p_input == NULL) || (p_output == NULL) || (size_byte == 0U))
    {
      return HAL_INVALID_PARAM;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
    || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if ((p_input == NULL) && (size_byte != 0U))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* SAES key mode must be normal to do encryption with any key:
     SAES configurable keys (normal,HW)
     or using a wrapped key
     or using a shared key (unshare)
     AES key mode must be normal when encrypt/decrypt */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_ENCRYPT);

  haes->p_in_buff = (const uint32_t *)p_input;
  haes->p_out_buff = (uint32_t *)p_output;
  haes->data_size_byte = size_byte;
  haes->block_count = 0U;

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if (AES_ECB_CBC_CTR_Process(haes, timeout_ms) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))

    if (AES_GCM_GMAC_CCM_Process(haes, timeout_ms) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_TIMEOUT;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  Decrypt user data in polling mode.
  *       - For ECB, CBC or CTR algorithms:
  *                           - The padding is not supported
  *                           - Only the decryption of the ciphertext is available (no preparation for tag generation)
  *       - For GCM algorithm:- HAL_AES_Decrypt() is used either to:
  *                           - Decrypt a ciphertext and use the header to prepare for the tag generation
  *                           - or just do the decryption (header null)
  *                           - or just prepare for tag generation (ciphertext null)
  *       - For GMAC algorithm: Prepare for the tag generation only (ciphertext null)
  *       - For CCM algorithm:- HAL_AES_Decrypt() is used either to:
  *                           - Decrypt a ciphertext and use the header to prepare for the tag generation
  *                           - or just do the decryption (header null)
  *                           - or just prepare for tag generation (ciphertext null)(not recommended by NIST)
  * @param   haes              Pointer to a @ref hal_aes_handle_t structure
  * @param   p_input           Pointer to aligned **const void** ciphertext
  * @param   size_byte         Length of the ciphertext buffer that must be in byte
  * @param   p_output          Pointer to aligned **void** data buffer to be filled with the decrypted text
  * @param   timeout_ms        Specify timeout value in milliseconds
  * @warning No swapped user data must be provided in big-endian. When data are provided in little-endian, the user must
  *          configure the swapping mode before starting the process (ex when data are provided as little- endian bytes
  *          ,the swap mode must be set to HAL_AES_BYTE_SWAP or when data are provided as little- endian halfwords, the
  *          swap mode must be set to HAL_AES_HALFWORD_SWAP)
  * @retval  HAL_INVALID_PARAM For ECB, CBC or CTR algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null
  *                             - Or the output data buffer pointer is null
  *                             - Or the input buffer is empty \n
  *                            For GCM_GMAC or CCM algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null but its size is # 0U
  *                            The handle pointer is null
  *                            The provided timeout is null
  * @retval  HAL_BUSY          Another AES process is ongoing
  * @retval  HAL_ERROR         Error return when the loaded key is invalid or when the key derivation exceeds the
  *                            dedicated timeout
  * @retval  HAL_TIMEOUT       AES decryption exceeds user timeout
  * @retval  HAL_OK            AES decryption is successfully accomplished
  */
hal_status_t HAL_AES_Decrypt(hal_aes_handle_t *haes, const void *p_input, uint16_t size_byte, void *p_output,
                             uint32_t timeout_ms)
{
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  uint32_t data_size_sum_byte_tmp;
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_PARAM(haes != NULL);
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    ASSERT_DBG_PARAM(p_input != NULL);
    ASSERT_DBG_PARAM(p_output != NULL);
    ASSERT_DBG_PARAM(size_byte != 0U);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if ((p_input == NULL) || (p_output == NULL) || (size_byte == 0U))
    {
      return HAL_INVALID_PARAM;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if ((p_input == NULL) && (size_byte != 0U))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  data_size_sum_byte_tmp = haes->data_size_sum_byte;

  if (((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC))
      && (data_size_sum_byte_tmp == 0U))
  {
    if (AES_KeyDerivation(haes) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_ERROR;
    }
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Set decrypt mode
     SAES key mode must be normal to do decryption with any key:
     SAES configurable keys (normal,HW)
     or using a wrapped key
     or using a shared key (unshare)
     AES key mode must be normal when encrypt/decrypt */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_DECRYPT);

  haes->p_in_buff = (const uint32_t *)p_input;
  haes->p_out_buff = (uint32_t *)p_output;
  haes->data_size_byte = size_byte;
  haes->block_count = 0U;

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if (AES_ECB_CBC_CTR_Process(haes, timeout_ms) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_TIMEOUT;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))

    if (AES_GCM_GMAC_CCM_Process(haes, timeout_ms) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_TIMEOUT;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  Encrypt user data in interrupt mode.
  *       - For ECB, CBC or CTR algorithms:
  *                           - the padding is not supported
  *                           - only the encryption of the plaintext is available (no preparation for tag generation)
  *       - For GCM algorithm:- HAL_AES_Encrypt_IT() is used either to:
  *                           - Encrypt a plaintext and use the header to prepare for the tag generation
  *                           - or just do the encryption (header null)
  *                           - or just prepare for tag generation (plaintext null)
  *       - For GMAC algorithm: Prepare for the tag generation only (plaintext null)
  *       - For CCM algorithm:- HAL_AES_Encrypt_IT() is used either to:
  *                           - Encrypt a plaintext and use the header to prepare for the tag generation
  *                           - or just do the encryption (header null)
  *                           - or just prepare for tag generation (plaintext null)(not recommended by NIST)
  * @param   haes              Pointer to a @ref hal_aes_handle_t structure
  * @param   p_input           Pointer to aligned **const void** plaintext
  * @param   size_byte         Length of the plaintext buffer that must be in byte
  * @param   p_output          Pointer to aligned **void** data buffer to be filled with the encrypted text
  * @warning No swapped user data must be provided in big-endian. When data are provided in little-endian, the user must
  *          configure the swapping mode before starting the process ( ex when data are provided as little- endian bytes
  *          , the swap mode must be set to HAL_AES_BYTE_SWAP or when data are provided as little- endian halfwords, the
  *          swap mode must be set to HAL_AES_HALFWORD_SWAP)
  * @retval  HAL_INVALID_PARAM For ECB, CBC or CTR algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null
  *                             - Or the output data buffer pointer is null
  *                             - Or the input buffer is empty \n
  *                            For GCM_GMAC or CCM algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null but its size is # 0U
  *                            The handle pointer is null
  * @retval  HAL_BUSY          Another AES process is ongoing
  * @retval  HAL_ERROR         Error return when the loaded key is invalid
  * @retval  HAL_OK            AES encryption is successfully accomplished
  */
hal_status_t HAL_AES_Encrypt_IT(hal_aes_handle_t *haes, const void *p_input, uint16_t size_byte, void *p_output)
{
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_PARAM(haes != NULL);

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    ASSERT_DBG_PARAM(p_input != NULL);
    ASSERT_DBG_PARAM(p_output != NULL);
    ASSERT_DBG_PARAM(size_byte != 0U);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if ((p_input == NULL) || (p_output == NULL) || (size_byte == 0U))
    {
      return HAL_INVALID_PARAM;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if ((p_input == NULL) && (size_byte != 0U))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* SAES key mode must be normal to do encryption with any key:
     SAES configurable keys (normal,HW)
     or using a wrapped key
     or using a shared key (unshare)
     AES key mode must be normal when encrypt/decrypt */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_ENCRYPT);

  haes->p_in_buff = (const uint32_t *)p_input;
  haes->p_out_buff = (uint32_t *)p_output;
  haes->data_size_byte = size_byte;
  haes->block_count = 0U;

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
    || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    /* Enable interrupts and Process one block to generate the computation complete interrupt */
    AES_ECB_CBC_CTR_Start_Process_IT(haes);
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    /* The computation complete interrupt is generated with:
      - Case 1: Accomplish the Init phase for first encrypt call
      - Case 2: Skip the Init phase in case of processing the message with several encrypt runs */
    if (AES_GCM_GMAC_CCM_Start_Process_IT(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }

  return HAL_OK;
}

/**
  * @brief  Decrypt user data in interrupt mode.
  *       - For ECB, CBC or CTR algorithms:
  *                           - the padding is not supported
  *                           - only the decryption of the ciphertext is available (no preparation for tag generation)
  *       - For GCM algorithm:- HAL_AES_Decrypt_IT() is used either to:
  *                           - Decrypt a ciphertext and use the header to prepare for the tag generation
  *                           - or just do the decryption (header null)
  *                           - or just prepare for tag generation (ciphertext null)
  *       - For GMAC algorithm: Prepare for the tag generation only (ciphertext null)
  *       - For CCM algorithm:- HAL_AES_Decrypt_IT() is used either to:
  *                           - Decrypt a ciphertext and use the header to prepare for the tag generation
  *                           - or just do the decryption (header null)
  *                           - or just prepare for tag generation (ciphertext null)( not recommended by NIST)
  * @param   haes              Pointer to a @ref hal_aes_handle_t structure
  * @param   p_input           Pointer to aligned **const void** ciphertext
  * @param   size_byte         Length of the ciphertext buffer that must be in byte
  * @param   p_output          Pointer to aligned **void** data buffer to be filled with the decrypted text
  * @warning No swapped user data must be provided in big-endian. When data are provided in little-endian, the user must
  *          configure the swapping mode before starting the process ( ex when data are provided as little- endian bytes
  *          , the swap mode must be set to HAL_AES_BYTE_SWAP or when data are provided as little- endian halfwords, the
  *          swap mode must be set to HAL_AES_HALFWORD_SWAP)
  * @retval  HAL_INVALID_PARAM For ECB, CBC or CTR algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null
  *                             - Or the output data buffer pointer is null
  *                             - Or the input buffer is empty \n
  *                            For GCM_GMAC or CCM algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null but its size is # 0U
  *                            The handle pointer is null
  * @retval  HAL_BUSY          Another AES process is ongoing
  * @retval  HAL_ERROR         Error return when the loaded key is invalid or when the key derivation exceeds the
  *                            dedicated timeout
  * @retval  HAL_OK            AES decryption is successfully accomplished
  */
hal_status_t HAL_AES_Decrypt_IT(hal_aes_handle_t *haes, const void *p_input, uint16_t size_byte, void *p_output)
{
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  uint32_t data_size_sum_byte_tmp;
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_PARAM(haes != NULL);
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    ASSERT_DBG_PARAM(p_input != NULL);
    ASSERT_DBG_PARAM(p_output != NULL);
    ASSERT_DBG_PARAM(size_byte != 0U);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if ((p_input == NULL) || (p_output == NULL) || (size_byte == 0U))
    {
      return HAL_INVALID_PARAM;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if ((p_input == NULL) && (size_byte != 0U))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  data_size_sum_byte_tmp = haes->data_size_sum_byte;
  if (
    ((haes->algorithm == AES_ALGORITHM_ECB)
     || (haes->algorithm == AES_ALGORITHM_CBC))
    && (data_size_sum_byte_tmp == 0U)
  )
  {
    if (AES_KeyDerivation(haes) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_ERROR;
    }
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Set decrypt mode
     SAES key mode must be normal to do a decryption with any key:
     SAES keys (normal,HW)
     or to use a wrapped key
     or to use a shared key (unshare key)
     AES key mode must be normal when encrypt/decrypt */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_DECRYPT);

  haes->p_in_buff = (const uint32_t *)p_input;
  haes->p_out_buff = (uint32_t *)p_output;
  haes->data_size_byte = size_byte;
  haes->block_count = 0U;

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
    || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    /* Enable interrupts and Process one block to generate computation complete interrupt */
    AES_ECB_CBC_CTR_Start_Process_IT(haes);
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    /* The computation complete interrupt is generated with:
      - Case 1: Accomplish the Init phase for first encrypt call
      - Case 2: Skip the Init phase in case of processing the message with several encrypt runs */
    if (AES_GCM_GMAC_CCM_Start_Process_IT(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }

  return HAL_OK;
}

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)

/**
  * @brief  Encrypt user data in DMA mode.
  *       - For ECB, CBC or CTR algorithms:
  *                           - the padding is not supported
  *                           - only the encryption of the plaintext is available (no preparation for tag generation)
  *       - For GCM algorithm:- HAL_AES_Encrypt_DMA() is used either to:
  *                           - Encrypt a plaintext and use the header to prepare for the tag generation
  *                           - or just do the encryption (header null)
  *                           - or just prepare for tag generation (plaintext null)
  *       - For GMAC algorithm: Prepare for the tag generation only (plaintext null)
  *       - For CCM algorithm:- HAL_AES_Encrypt_DMA() is used either to:
  *                           - Encrypt a plaintext and use the header to prepare for the tag generation
  *                           - or just do the encryption (header null)
  *                           - or just prepare for tag generation (plaintext null)(not recommended by NIST)
  * @param   haes              Pointer to a @ref hal_aes_handle_t structure
  * @param   p_input           Pointer to aligned **const void** plaintext
  * @param   size_byte         Length of the plaintext buffer that must be in byte
  * @param   p_output          Pointer to aligned **void** data buffer to be filled with the encrypted text
  * @warning No swapped user data must be provided in big-endian. When data are provided in little-endian, the user must
  *          configure the swapping mode before starting the process (ex when data are provided as little- endian bytes
  *          , the swap mode must be set to HAL_AES_BYTE_SWAP or when data are provided as little- endian halfwords, the
  *          swap mode must be set to HAL_AES_HALFWORD_SWAP)
  * @retval  HAL_INVALID_PARAM For ECB, CBC or CTR algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null
  *                             - Or the output data buffer pointer is null
  *                             - Or the input buffer is empty \n
  *                            For GCM_GMAC or CCM algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null but its size is # 0U
  *                            The handle pointer is null
  * @retval  HAL_BUSY          Another AES process is ongoing
  * @retval  HAL_ERROR         Error return when the loaded key is invalid
  * @retval  HAL_OK            AES encryption is successfully accomplished
  */
hal_status_t HAL_AES_Encrypt_DMA(hal_aes_handle_t *haes, const void *p_input, uint16_t size_byte, void *p_output)
{
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_PARAM(haes != NULL);
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    ASSERT_DBG_PARAM(p_input != NULL);
    ASSERT_DBG_PARAM(p_output != NULL);
    ASSERT_DBG_PARAM(size_byte != 0U);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if ((p_input == NULL) || (p_output == NULL) || (size_byte == 0U))
    {
      return HAL_INVALID_PARAM;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if ((p_input == NULL) && (size_byte != 0U))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* SAES key mode must be normal to do encryption with any key:
     SAES configurable keys (normal,HW)
     or using a wrapped key
     or using a shared key (unshare)
     AES key mode must be normal when encrypt/decrypt */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_ENCRYPT);

  haes->p_in_buff = (const uint32_t *)p_input;
  haes->p_out_buff = (uint32_t *)p_output;
  haes->data_size_byte = size_byte;
  haes->block_count = 0U;

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if (AES_ECB_CBC_CTR_Process_DMA(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if (AES_GCM_GMAC_CCM_Process_DMA(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }

  return HAL_OK;
}

/**
  * @brief  Decrypt user data in DMA mode.
  *       - For ECB, CBC or CTR algorithms:
  *                           - the padding is not supported
  *                           - only the decryption of the ciphertext is available (no preparation for tag generation)
  *       - For GCM algorithm:- HAL_AES_Decrypt_DMA() is used either to:
  *                           - Decrypt a ciphertext and use the header to prepare for the tag generation
  *                           - or just do the decryption (header null)
  *                           - or just prepare for tag generation (ciphertext null)
  *       - For GMAC algorithm: Prepare for the tag generation only (ciphertext null)
  *       - For CCM algorithm:- HAL_AES_Decrypt_DMA() is used either to:
  *                           - Decrypt a ciphertext and use the header to prepare for the tag generation
  *                           - or just do the decryption (header null)
  *                           - or just prepare for tag generation (ciphertext null)(not recommended by NIST)
  * @param   haes              Pointer to a @ref hal_aes_handle_t structure
  * @param   p_input           Pointer to aligned **const void** ciphertext
  * @param   size_byte         Length of the ciphertext buffer that must be in byte
  * @param   p_output          Pointer to aligned **void** data buffer to be filled with the decrypted text
  * @warning No swapped user data must be provided in big-endian. When data are provided in little-endian, the user must
  *          configure the swapping mode before starting the process (ex when data are provided as little- endian bytes
  *          , the swap mode must be set to HAL_AES_BYTE_SWAP or when data are provided as little- endian halfwords, the
  *          swap mode must be set to HAL_AES_HALFWORD_SWAP)
  * @retval  HAL_INVALID_PARAM For ECB, CBC or CTR algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null
  *                             - Or the output data buffer pointer is null
  *                             - Or the input buffer is empty \n
  *                            For GCM_GMAC or CCM algorithms Invalid param return when:
  *                             - The provided input data buffer pointer is null but its size is # 0U
  *                            The handle pointer is null
  * @retval  HAL_BUSY          Another AES process is ongoing
  * @retval  HAL_ERROR         Error return when the loaded key is invalid or when the key derivation exceeds the
  *                            dedicated timeout
  * @retval  HAL_OK            AES decryption is successfully accomplished
  */
hal_status_t HAL_AES_Decrypt_DMA(hal_aes_handle_t *haes, const void *p_input, uint16_t size_byte, void *p_output)
{
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  uint32_t data_size_sum_byte_tmp;
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  ASSERT_DBG_PARAM(haes != NULL);

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    ASSERT_DBG_PARAM(p_input != NULL);
    ASSERT_DBG_PARAM(p_output != NULL);
    ASSERT_DBG_PARAM(size_byte != 0U);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if ((p_input == NULL) || (p_output == NULL) || (size_byte == 0U))
    {
      return HAL_INVALID_PARAM;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if ((p_input == NULL) && (size_byte != 0U))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  data_size_sum_byte_tmp = haes->data_size_sum_byte;

  if (
    ((haes->algorithm == AES_ALGORITHM_ECB)
     || (haes->algorithm == AES_ALGORITHM_CBC))
    && (data_size_sum_byte_tmp  == 0U)
  )
  {
    if (AES_KeyDerivation(haes) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_ERROR;
    }
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Set decrypt mode
     SAES key mode must be normal to do decryption with any key:
     SAES configurable keys (normal,HW)
     or using a wrapped key
     or using a shared key (unshare)
     AES key mode must be normal when encrypt/decrypt */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_DECRYPT);

  haes->p_in_buff = (const uint32_t *)p_input;
  haes->p_out_buff = (uint32_t *)p_output;
  haes->data_size_byte = size_byte;
  haes->block_count = 0U;

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
      || (haes->algorithm == AES_ALGORITHM_CTR))
  {
    if (AES_ECB_CBC_CTR_Process_DMA(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
  else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
    if (AES_GCM_GMAC_CCM_Process_DMA(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  }

  return HAL_OK;
}
#endif /* USE_HAL_AES_DMA */

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
/**
  * @brief  Request suspension for AES interrupt mode processing.
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  * @note   Set the handle field suspend_request to HAL_AES_SUSPEND so that the on-going AES processing is suspended as
  *         soon as the required conditions are met (The current block is entirely processed and it's not the last one)
  * @retval HAL_INVALID_PARAM When the handle pointer is NULL.
  * @retval HAL_OK            The AES processing suspension is well requested
  */
hal_status_t HAL_AES_RequestSuspend(hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_ACTIVE);
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */
  haes->suspend_request = AES_SUSPEND;

  return HAL_OK;
}

/**
  * @brief  Resumption of the suspended AES processing.
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  * @note   Processing restarts at the exact point where it was suspended, if the AES context has been changed
  *         @ref HAL_AES_SaveContext and @ref HAL_AES_RestoreContext must be used before resumption.
  * @retval HAL_INVALID_PARAM When the handle pointer is NULL.
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_OK            AES suspended processing is resumed
  */
hal_status_t HAL_AES_Resume(hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_SUSPENDED);
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_SUSPENDED, HAL_AES_STATE_ACTIVE);

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_GCM_GMAC) || (haes->algorithm == AES_ALGORITHM_CCM))
  {
    AES_ENABLE(haes);

    if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_HEADER)
    {
      AES_SetHeaderPhase_IT(haes);
      HAL_AES_EnableIT(haes, HAL_AES_IT_ALL);
    }
    else
    {
      AES_StartPayloadPhase_IT(haes);
      HAL_AES_EnableIT(haes, HAL_AES_IT_ALL);
    }
  }
  else
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  {
#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
    || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))

    /* Enable interrupts and Process one block to generate the computation complete interrupt */
    AES_ECB_CBC_CTR_Start_Process_IT(haes);

#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
  }

  return HAL_OK;
}

/**
  * @brief  Save parameters of the suspended AES processing.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @param  p_context Pointer to a @ref hal_aes_save_context_t structure where to store the parameters of the suspend
  *                   AES processing
  * @retval HAL_INVALID_PARAM The provided save context pointer structure or the handle pointer is null
  * @retval HAL_OK            AES suspended processing parameters are saved
  */
hal_status_t HAL_AES_SaveContext(hal_aes_handle_t *haes, hal_aes_save_context_t *p_context)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_context != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_SUSPENDED);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_context == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
    || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_GCM_GMAC) || (haes->algorithm == AES_ALGORITHM_CCM))
  {
    p_context->SUSPxR[0] = AES_GET_INSTANCE(haes)->SUSP7R;
    p_context->SUSPxR[1] = AES_GET_INSTANCE(haes)->SUSP6R;
    p_context->SUSPxR[2] = AES_GET_INSTANCE(haes)->SUSP5R;
    p_context->SUSPxR[3] = AES_GET_INSTANCE(haes)->SUSP4R;
    p_context->SUSPxR[4] = AES_GET_INSTANCE(haes)->SUSP3R;
    p_context->SUSPxR[5] = AES_GET_INSTANCE(haes)->SUSP2R;
    p_context->SUSPxR[6] = AES_GET_INSTANCE(haes)->SUSP1R;
    p_context->SUSPxR[7] = AES_GET_INSTANCE(haes)->SUSP0R;
  }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */

  if (haes->algorithm != AES_ALGORITHM_ECB)
  {
    /* Save Initialization Vector registers */
    p_context->iv_buff[0] = AES_GET_INSTANCE(haes)->IVR3;
    p_context->iv_buff[1] = AES_GET_INSTANCE(haes)->IVR2;
    p_context->iv_buff[2] = AES_GET_INSTANCE(haes)->IVR1;
    p_context->iv_buff[3] = AES_GET_INSTANCE(haes)->IVR0;
  }

  AES_DISABLE(haes);

  /* Save the configuration register */
  p_context->CR = AES_GET_INSTANCE(haes)->CR;
  p_context->instance           = haes->instance;
  p_context->previous_state     = haes->global_state;
  p_context->algorithm          = haes->algorithm;
  p_context->data_size_byte     = haes->data_size_byte;
  p_context->data_size_sum_byte = haes->data_size_sum_byte;
  p_context->p_in_buff          = haes->p_in_buff;
  p_context->p_out_buff         = haes->p_out_buff;
  p_context->block_count        = haes->block_count;
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
  p_context->p_header           = haes->p_header;
  p_context->header_size_byte   = haes->header_size_byte;
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  p_context->suspend_request    = haes->suspend_request;
  p_context->p_key              = haes->p_key;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  p_context->p_in_cplt_cb       = haes->p_in_cplt_cb;
  p_context->p_out_cplt_cb      = haes->p_out_cplt_cb;
  p_context->p_error_cb         = haes->p_error_cb;
  p_context->p_suspend_cb       = haes->p_suspend_cb;
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

  haes->global_state = HAL_AES_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Resumption for the saved parameters of the suspended AES processing.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @param  p_context Pointer to a @ref hal_aes_save_context_t structure where the parameters of the suspend AES
  *                   processing are stored
  * @retval HAL_INVALID_PARAM When the handle pointer is NULL.
  * @retval HAL_ERROR         AES key derivation exceeds the dedicated timeout
  * @retval HAL_OK            AES suspended processing parameters are restored
  */
hal_status_t HAL_AES_RestoreContext(hal_aes_handle_t *haes, const hal_aes_save_context_t *p_context)
{
  uint32_t key_size;

  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_context != NULL);
  ASSERT_DBG_PARAM(p_context->previous_state == HAL_AES_STATE_SUSPENDED);

  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (haes == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */
  AES_DISABLE(haes);

  AES_GET_INSTANCE(haes)->CR = p_context->CR;

  haes->instance           = p_context->instance;
  haes->algorithm          = p_context->algorithm;
  haes->data_size_byte     = p_context->data_size_byte;
  haes->data_size_sum_byte = p_context->data_size_sum_byte;
  haes->p_in_buff          = p_context->p_in_buff;
  haes->p_out_buff         = p_context->p_out_buff;
  haes->block_count        = p_context->block_count;

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
  haes->p_header           = p_context->p_header;
  haes->header_size_byte   = p_context->header_size_byte;
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
  haes->suspend_request    = p_context->suspend_request;
  haes->p_key              = p_context->p_key;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  haes->p_in_cplt_cb       = p_context->p_in_cplt_cb;
  haes->p_out_cplt_cb      = p_context->p_out_cplt_cb;
  haes->p_error_cb         = p_context->p_error_cb;
  haes->p_suspend_cb       = p_context->p_suspend_cb;
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

  key_size = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYSIZE);

  if (haes->algorithm != AES_ALGORITHM_ECB)
  {
    AES_SetIV(haes, p_context->iv_buff);
  }

  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_KEYSEL) == 0U)
  {
    AES_SetNormalKey(haes, (hal_aes_key_size_t)key_size, haes->p_key);
  }

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  if ((READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE) == AES_OPERATING_MODE_DECRYPT)
      && ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)))
  {
    if (AES_KeyDerivation(haes) != HAL_OK)
    {
      return HAL_ERROR;
    }

    MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_DECRYPT);
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
  if ((haes->algorithm == AES_ALGORITHM_GCM_GMAC) || (haes->algorithm == AES_ALGORITHM_CCM))
  {
    AES_GET_INSTANCE(haes)->SUSP7R = p_context->SUSPxR[0];
    AES_GET_INSTANCE(haes)->SUSP6R = p_context->SUSPxR[1];
    AES_GET_INSTANCE(haes)->SUSP5R = p_context->SUSPxR[2];
    AES_GET_INSTANCE(haes)->SUSP4R = p_context->SUSPxR[3];
    AES_GET_INSTANCE(haes)->SUSP3R = p_context->SUSPxR[4];
    AES_GET_INSTANCE(haes)->SUSP2R = p_context->SUSPxR[5];
    AES_GET_INSTANCE(haes)->SUSP1R = p_context->SUSPxR[6];
    AES_GET_INSTANCE(haes)->SUSP0R = p_context->SUSPxR[7];
  }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */

  haes->global_state = HAL_AES_STATE_SUSPENDED;

  return HAL_OK;
}
#endif /* USE_HAL_AES_SUSPEND_RESUME */
/**
  * @}
  */

/** @addtogroup AES_Exported_Functions_Group4
  * @{
This subsection provides the IRQHandler and a set of callback functions allowing to manage the data transfer between the
user input/output buffer and the AES/SAES peripheral:
  - HAL_AES_IRQHandler()                      :Allowing to handle the AES interrupts

  - HAL_AES_InCpltCallback()                  :Input transfer complete callback
  - HAL_AES_OutCpltCallback()                 :Output transfer complete callback
  - HAL_AES_ErrorCallback()                   :Error callback
  - HAL_AES_SuspendCallback()                 :Suspend callback

  - HAL_AES_RegisterInTransferCpltCallback()  :Allowing to register the input transfer complete callback
  - HAL_AES_RegisterOutTransferCpltCallback() :Allowing to register the output transfer complete callback
  - HAL_AES_RegisterErrorCallback()           :Allowing to register the error callback
  - HAL_AES_RegisterSuspendCallback()         :Allowing to register the suspend callback

  - HAL_AES_SetInDMA()                        :Allowing to link the input FIFO HAL DMA handle into the HAL AES handle
  - HAL_AES_SetOutDMA()                       :Allowing to link the output FIFO HAL DMA handle into the HAL AES handle

  */
/**
  * @brief Handle any AES interrupt.
  * @param haes Pointer to a @ref hal_aes_handle_t structure
  */
void HAL_AES_IRQHandler(hal_aes_handle_t *haes)
{
  uint32_t its;
  uint32_t flags_sr;
  uint32_t flags_isr;

  ASSERT_DBG_PARAM(haes != NULL);

  its = READ_REG(AES_GET_INSTANCE(haes)->IER);
  flags_sr = READ_REG(AES_GET_INSTANCE(haes)->SR);
  flags_isr = READ_REG(AES_GET_INSTANCE(haes)->ISR);

  /* Check if Read or write error occurred */
  if (READ_BIT((flags_isr & its), HAL_AES_FLAG_RDWRERR) != 0U)
  {
    /* If non blocking write Error occurred */
    if ((flags_sr & HAL_AES_FLAG_WRERR) != 0U)
    {
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
      haes->last_error_codes |= HAL_AES_ERROR_WRITE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */
    }

    /* If non blocking read Error occurred */
    if ((flags_sr & HAL_AES_FLAG_RDERR) != 0U)
    {
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
      haes->last_error_codes |= HAL_AES_ERROR_READ;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */
    }

    HAL_AES_ClearFlagRDWRERR(haes);
  }

  /* Check if Key error occurred */
  if (READ_BIT((flags_isr & its), HAL_AES_FLAG_KERR) != 0U)
  {
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
    haes->last_error_codes |= HAL_AES_ERROR_KEY;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */
  }

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
  /* Check if RNG error occurred */
  if (READ_BIT((flags_isr & its), HAL_AES_FLAG_RNGERR) != 0U)
  {
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
    haes->last_error_codes |= HAL_AES_ERROR_RNG;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */
  }
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

  if (READ_BIT((flags_isr & its), HAL_AES_FLAG_KERR | HAL_AES_FLAG_RNGERR) != 0U)
  {
    HAL_AES_ClearFlagKERR(haes);

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
    HAL_AES_ClearFlagRNGERR(haes);
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

    haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
    haes->p_error_cb(haes);
#else
    HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

    return;
  }

  if (READ_BIT((flags_isr & its), HAL_AES_FLAG_CC) != 0U)
  {
    HAL_AES_ClearFlagCC(haes);

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
    if ((haes->algorithm == AES_ALGORITHM_ECB) || (haes->algorithm == AES_ALGORITHM_CBC)
        || (haes->algorithm == AES_ALGORITHM_CTR))
    {
      /* Process data in IT mode: Each block write to DINR generates a computation complete interrupt */
      AES_ECB_CBC_CTR_Process_IT(haes);
    }
    else
#endif /* USE_HAL_AES_ECB_CBC_ALGO OR USE_HAL_AES_CTR_ALGO */
    {
#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
     || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
      /* A computation complete interrupt generated via INIT phase */
      if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_INIT)
      {
        /* Set header phase */
        if (haes->header_size_byte != 0U)
        {
          MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_HEADER);
          AES_ENABLE(haes);
          AES_SetHeaderPhase_IT(haes);
        }
        /* Skip header phase (header null) and start payload phase */
        else
        {
          MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
          AES_ENABLE(haes);
          AES_StartPayloadPhase_IT(haes);
        }
      }
      /* A computation complete interrupt generated via HEADER phase */
      else if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_HEADER)
      {
        /* Set header phase */
        AES_SetHeaderPhase_IT(haes);
      }
      /* A computation complete interrupt generated via PAYLOAD phase */
      else
      {
        /* Set payload phase */
        AES_SetPayloadPhase_IT(haes);
      }
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
    }
  }
}

/**
  * @brief Input FIFO transfer completed callback.
  * @param haes Pointer to a @ref hal_aes_handle_t structure
  */
__WEAK void HAL_AES_InCpltCallback(hal_aes_handle_t *haes)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(haes);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_AES_InCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Output FIFO transfer completed callback.
  * @param haes Pointer to a @ref hal_aes_handle_t structure
  */
__WEAK void HAL_AES_OutCpltCallback(hal_aes_handle_t *haes)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(haes);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_AES_OutCpltCallback could be implemented in the user file
  */
}

/**
  * @brief Error callback.
  * @param haes Pointer to a @ref hal_aes_handle_t structure
  */
__WEAK void HAL_AES_ErrorCallback(hal_aes_handle_t *haes)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(haes);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_AES_ErrorCallback could be implemented in the user file
  */
}

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
/**
  * @brief Suspend callback.
  * @param haes Pointer to a @ref hal_aes_handle_t structure
  */
__WEAK void HAL_AES_SuspendCallback(hal_aes_handle_t *haes)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(haes);

  /* NOTE: This function must not be modified, when the callback is needed,
  the HAL_AES_SuspendCallback could be implemented in the user file
  */
}
#endif /* defined (USE_HAL_AES_SUSPEND_RESUME) */

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the input transfer complete callback.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_callback        Pointer to the hal_aes_cb_t callback function.
  * @retval HAL_INVALID_PARAM When the callback pointer is NULL.
  * @retval HAL_OK            Callback registered successfully.
  */
hal_status_t HAL_AES_RegisterInTransferCpltCallback(hal_aes_handle_t *haes, hal_aes_cb_t p_callback)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  haes->p_in_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the output transfer complete callback.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_callback        Pointer to the hal_aes_cb_t callback function.
  * @retval HAL_INVALID_PARAM When the callback pointer is NULL.
  * @retval HAL_OK            Callback registered successfully.
  */
hal_status_t HAL_AES_RegisterOutTransferCpltCallback(hal_aes_handle_t *haes, hal_aes_cb_t p_callback)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  haes->p_out_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the error callback.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_callback        Pointer to the hal_aes_cb_t callback function.
  * @retval HAL_INVALID_PARAM When the callback pointer is NULL.
  * @retval HAL_OK            Callback registered successfully.
  */
hal_status_t HAL_AES_RegisterErrorCallback(hal_aes_handle_t *haes, hal_aes_cb_t p_callback)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  haes->p_error_cb = p_callback;

  return HAL_OK;
}

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
/**
  * @brief  Register the suspend callback.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_callback        Pointer to the hal_aes_cb_t callback function.
  * @retval HAL_INVALID_PARAM When the callback pointer is NULL.
  * @retval HAL_OK            Callback registered successfully.
  */
hal_status_t HAL_AES_RegisterSuspendCallback(hal_aes_handle_t *haes, hal_aes_cb_t p_callback)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  haes->p_suspend_cb = p_callback;

  return HAL_OK;
}
#endif /* defined (USE_HAL_AES_SUSPEND_RESUME) */
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
/**
  * @brief  Link/Store Input FIFO HAL DMA handle into the HAL AES handle.
  * @param  haes     Pointer to a @ref hal_aes_handle_t structure
  * @param  hdma_in  Pointer to a hal_dma_handle_t
  * @retval HAL_INVALID_PARAM When the DMA handle pointer is NULL
  * @retval HAL_OK            The DMA handle has been correctly linked to the AES handle
  */
hal_status_t HAL_AES_SetInDMA(hal_aes_handle_t *haes, hal_dma_handle_t *hdma_in)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(hdma_in != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma_in == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  haes->hdma_in     = hdma_in;
  hdma_in->p_parent = haes;

  return HAL_OK;
}

/**
  * @brief  Link/Store Output FIFO HAL DMA handle into the HAL AES handle.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @param  hdma_out  Pointer to a hal_dma_handle_t
  * @retval HAL_INVALID_PARAM When the DMA handle pointer is NULL
  * @retval HAL_OK            The DMA handle has been correctly linked to the AES handle
  */
hal_status_t HAL_AES_SetOutDMA(hal_aes_handle_t *haes, hal_dma_handle_t *hdma_out)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(hdma_out != NULL);
  ASSERT_DBG_STATE(haes->global_state, (uint32_t)HAL_AES_STATE_INIT | (uint32_t)HAL_AES_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma_out == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  haes->hdma_out     = hdma_out;
  hdma_out->p_parent = haes;

  return HAL_OK;
}
#endif /* USE_HAL_AES_DMA */

/**
  * @}
  */

/** @addtogroup AES_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to get the AES error information and state:
  - HAL_AES_GetState()            :Allowing to retrieve the AES state
  - HAL_AES_GetLastErrorCodes()   :Allowing to retrieve the AES error code
  - HAL_AES_SetUserData()         :Allowing to store application user data pointer into the handle
  - HAL_AES_GetUserData()         :Allowing to retrieve the application user data pointer from the handle
  - HAL_AES_CBC_GetLastOutputIV() :Allowing to retrieve the the last output IV for CBC mode.
  - HAL_AES_CTR_GetLastOutputIV() :Allowing to retrieve the the last output IV for CTR mode.
  */
/**
  * @brief  Retrieve the HAL AES Global State.
  * @param  haes                    Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_AES_STATE_RESET     AES/SAES peripheral is not yet initialized
  * @retval HAL_AES_STATE_INIT      AES/SAES peripheral is initialized but not yet configured
  * @retval HAL_AES_STATE_IDLE      AES/SAES peripheral is initialized and configured
  * @retval HAL_AES_STATE_ACTIVE    AES internal processing is ongoing
  * @retval HAL_AES_STATE_SUSPENDED AES internal processing is suspended
  */
hal_aes_state_t HAL_AES_GetState(const hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);

  return haes->global_state;
}

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last error codes.
  * @param  haes     Pointer to a @ref hal_aes_handle_t structure
  * @retval uint32_t Last error codes which can be a combination of @ref AES_Error_Code
  */
uint32_t HAL_AES_GetLastErrorCodes(const hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);

  return haes->last_error_codes;
}
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

#if defined (USE_HAL_AES_USER_DATA) && (USE_HAL_AES_USER_DATA == 1)
/**
  * @brief  Store application user data pointer into the handle.
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  p_user_data Pointer to the user data
  */
void HAL_AES_SetUserData(hal_aes_handle_t *haes, const void *p_user_data)
{
  ASSERT_DBG_PARAM(haes != NULL);

  haes->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the application user data pointer from the handle.
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  * @retval Pointer to the user data
  */
const void *HAL_AES_GetUserData(const hal_aes_handle_t *haes)
{
  ASSERT_DBG_PARAM(haes != NULL);

  return (haes->p_user_data);
}
#endif /* USE_HAL_AES_USER_DATA == 1 */
/**
  * @}
  */

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1))
/**
  * @brief  Get the last output IV for CBC mode.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_last_iv         Pointer to the user buffer to be updated with the last output IV
  * @param  last_iv_size      Size of the p_last_iv buffer
  * @retval HAL_INVALID_PARAM Invalid param return when the provided last output IV pointer is null
  *                           or the handle pointer is null
  * @retval HAL_ERROR         Error return when the selected algorithm is not CBC algorithm or when
  *                           the data_size_sum_byte is null
  * @retval HAL_OK            AES process is successfully accomplished
  */
hal_status_t HAL_AES_CBC_GetLastOutputIV(const hal_aes_handle_t *haes, const uint8_t *p_last_iv, uint8_t last_iv_size)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_last_iv != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((haes == NULL) || (p_last_iv == NULL))
  {
    return HAL_INVALID_PARAM;
  }
  if (last_iv_size != 16U)
  {
    return HAL_INVALID_PARAM;
  }
#else
  /* Prevent unused argument compilation warning */
  STM32_UNUSED(last_iv_size);
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  if (haes->algorithm != AES_ALGORITHM_CBC)
  {
    return HAL_ERROR;
  }

  if (haes->data_size_sum_byte == 0U)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Read the IV registers and store them in the user buffer */
    uint32_t last_iv = (uint32_t)p_last_iv;

    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR3);
    last_iv += 4U;
    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR2);
    last_iv += 4U;
    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR1);
    last_iv += 4U;
    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR0);

    return HAL_OK;

  }


}
#endif /* USE_HAL_AES_ECB_CBC_ALGO*/
#if (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
/**
  * @brief  Get the last output IV for CTR mode.
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_last_iv         Pointer to the user buffer to be updated with the last output IV
  * @param  last_iv_size      Size of the p_last_iv buffer
  * @retval HAL_INVALID_PARAM Invalid param return when the provided last output IV pointer is null
  *                           or the handle pointer is null
  * @retval HAL_ERROR         Error return when the selected algorithm is not CTR algorithm or when
  *                           the data_size_sum_byte is null
  * @retval HAL_OK            AES process is successfully accomplished
  */
hal_status_t HAL_AES_CTR_GetLastOutputIV(const hal_aes_handle_t *haes, const uint8_t *p_last_iv, uint8_t last_iv_size)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_last_iv != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((haes == NULL) || (p_last_iv == NULL))
  {
    return HAL_INVALID_PARAM;
  }
  if (last_iv_size != 16U)
  {
    return HAL_INVALID_PARAM;
  }
#else
  /* Prevent unused argument compilation warning */
  STM32_UNUSED(last_iv_size);
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  if (haes->algorithm != AES_ALGORITHM_CTR)
  {
    return HAL_ERROR;
  }

  if (haes->data_size_sum_byte == 0U)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Read the IV registers and store them in the user buffer */
    uint32_t last_iv = (uint32_t)p_last_iv;

    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR3);
    last_iv += 4U;
    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR2);
    last_iv += 4U;
    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR1);
    last_iv += 4U;
    *(uint32_t *)(last_iv) = (uint32_t)(AES_GET_INSTANCE(haes)->IVR0);

    return HAL_OK;

  }

}
#endif /*USE_HAL_AES_CTR_ALGO */

/** @addtogroup AES_Exported_Functions_Group6
  * @{
This subsection provides a set of functions allowing TAG generation for GCM and CCM algorithms:
 - HAL_AES_GCM_GenerateAuthTAG()   :Allowing to generate a tag for GCM algorithm
 - HAL_AES_CCM_GenerateAuthTAG()   :Allowing to generate a tag for CCM algorithm
  */

#if defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)
/**
  * @brief  Generate the GCM authentication TAG, available only with AES instance. \n
  *         This API can only be called after accomplishing either an encryption or a decryption process
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_auth_tag        Pointer to the authentication buffer the p_auth_tag generated here is 128bits length,
  *                           if the TAG length is less than 128bits, user must consider only the valid part of
  *                           p_auth_tag buffer which corresponds exactly to TAG length.
  * @param  timeout_ms        Specify Timeout value in milliseconds
  * @retval HAL_INVALID_PARAM The provided input tag pointer is null
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_TIMEOUT       AES tag generation exceeds user timeout
  * @retval HAL_ERROR         AES tag generation sequence is not well performed
  * @retval HAL_OK            AES tag is successfully generated
  */
hal_status_t HAL_AES_GCM_GenerateAuthTAG(hal_aes_handle_t *haes, uint32_t *p_auth_tag, uint32_t timeout_ms)
{
  uint32_t headerlength;
  uint32_t inputlength;
  uint32_t *p_tmp_auth_tag;
  uint32_t phase;

  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_auth_tag != NULL);
  ASSERT_DBG_PARAM(haes->algorithm == AES_ALGORITHM_GCM_GMAC);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_auth_tag == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  headerlength = (uint32_t)(haes->header_size_byte * 8U); /* Header length in bits */
  inputlength = (uint32_t)(haes->data_size_sum_byte * 8U); /* Input length in bits */
  p_tmp_auth_tag = p_auth_tag;

  phase = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH);
  if ((phase == AES_PHASE_HEADER) || (phase == AES_PHASE_PAYLOAD))
  {
    MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_FINAL);

    AES_GET_INSTANCE(haes)->DINR  = 0U;
    AES_GET_INSTANCE(haes)->DINR  = headerlength;
    AES_GET_INSTANCE(haes)->DINR  = 0U;
    AES_GET_INSTANCE(haes)->DINR  = inputlength;

    if (AES_WaitOnCCFlag(haes, timeout_ms) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_TIMEOUT;
    }

    /* Read the authentication TAG from the output FIFO */
    for (uint32_t i = 0U; i < 4U; i++)
    {
      *p_tmp_auth_tag = AES_GET_INSTANCE(haes)->DOUTR;
      p_tmp_auth_tag ++;
    }
  }
  else
  {
    AES_DISABLE(haes);
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagCC(haes);
  AES_DISABLE(haes);

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* (USE_HAL_AES_GCM_GMAC_ALGO) */

#if defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1)
/**
  * @brief  Generate the CCM authentication TAG, available only with AES instance. \n
  *         This API can only be called after accomplishing either an encryption or a decryption process
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_auth_tag        Pointer to the authentication buffer the p_auth_tag generated here is 128bits length,
  *                           if the TAG length is less than 128bits, user must consider only the valid part of
  *                           p_auth_tag buffer which corresponds exactly to TAG length.
  * @param  timeout_ms        Specify Timeout value in milliseconds
  * @retval HAL_INVALID_PARAM The provided input tag pointer is null
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_TIMEOUT       AES tag generation exceeds user timeout
  * @retval HAL_ERROR         AES tag generation sequence is not well performed
  * @retval HAL_OK            AES tag is successfully generated
  */
hal_status_t HAL_AES_CCM_GenerateAuthTAG(hal_aes_handle_t *haes, uint32_t *p_auth_tag, uint32_t timeout_ms)
{
  uint32_t *p_tmp_auth_tag;
  uint32_t phase;

  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(p_auth_tag != NULL);
  ASSERT_DBG_PARAM(haes->algorithm == AES_ALGORITHM_CCM);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_auth_tag == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  p_tmp_auth_tag = p_auth_tag;
  phase = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH);
  if ((phase == AES_PHASE_HEADER) || (phase == AES_PHASE_PAYLOAD))
  {
    MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_FINAL);

    if (AES_WaitOnCCFlag(haes, timeout_ms) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_TIMEOUT;
    }

    /* Read the authentication TAG in the output FIFO */
    for (uint32_t i = 0U; i < 4U; i++)
    {
      *p_tmp_auth_tag = AES_GET_INSTANCE(haes)->DOUTR;
      p_tmp_auth_tag ++;
    }
  }
  else
  {
    AES_DISABLE(haes);
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagCC(haes);
  AES_DISABLE(haes);

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* (USE_HAL_AES_CCM_ALGO) */
/**
  * @}
  */

/** @addtogroup AES_Exported_Functions_Group7
  * @{
This subsection provides a set of functions allowing AES key processing:
 - HAL_AES_WrapKey()          :Allowing to wrap an SAES application key
 - HAL_AES_UnwrapKey()        :Allowing to unwrap the wrapped key to be used by SAES peripheral to encrypt/decrypt
                               messages
 - HAL_AES_EncryptSharedKey() :Allowing to encrypt an SAES application key in share mode
 - HAL_AES_DecryptSharedKey() :Allowing to decrypt the SAES encrypted key to be shared with AES peripheral
  */
#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
/**
  * @brief  Encrypt an application key with SAES HW keys(wrapper key). \n
  *         This API is only available with SAES instance,
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_key_in          Pointer to **uint32_t** input key provided by the user to be encrypted with a HW key
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @param  p_key_output      Pointer to **uint32_t** output key provided by the user to be filled with the encrypted
  *                           application key
  * @param  timeout_ms        Specify Timeout value in milliseconds
  * @note   This API aims to build a secure application context following this sequence:
  *       - Call HAL_AES_WrapKey() API which encrypts the application key and write it into the output key buffer
  *       - Delete the original key at the application level
  *       - When need to use the original application key to encrypt/decrypt messages, call the HAL_AES_UnwrapKey() API
  *         which unwraps the encrypted key using the same wrapper key and load the unexposed result into registers
  * @warning The key size must be the same one as the wrapper key which is provided as a parameter of the
             HAL_AES_SetHWKey() API
  * @retval HAL_INVALID_PARAM Invalid param return when:
  *                           - The handle instance is not the SAES one
  *                           - The provided application input key pointer is null
  *                           - The provided application output key pointer is null
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_ERROR         Error return when the selected wrapper key is invalid
  * @retval HAL_TIMEOUT       AES key wrapping exceeds user timeout
  * @retval HAL_OK            AES key wrapping is successfully accomplished
  */
hal_status_t HAL_AES_WrapKey(hal_aes_handle_t *haes, const uint32_t *p_key_in, hal_aes_key_size_t key_size,
                             uint32_t *p_key_output, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_key_in != NULL);
  ASSERT_DBG_PARAM(IS_AES_HW_KEY_SIZE(haes, key_size));
  ASSERT_DBG_PARAM(p_key_output != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_key_in == NULL) || (p_key_output == NULL) || (haes->instance != HAL_SAES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Encrypt the SAES application key with the wrapper key already set by HAL_AES_SetHWKey() API in wrap mode: The SAES
    application key becomes protected(encrypted) and can be used only after being decrypted with the same wrapper key */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_ENCRYPT
             | (uint32_t)HAL_AES_KEY_MODE_WRAPPED);

  haes->p_in_buff = p_key_in;
  haes->p_out_buff = p_key_output;

  if (key_size == HAL_AES_KEY_SIZE_128BIT)
  {
    haes->data_size_byte = 16U;
  }
  else
  {
    haes->data_size_byte = 32U;
  }
  haes->block_count = 0U;

  if (AES_ECB_CBC_CTR_Process(haes, timeout_ms) != HAL_OK)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
/**
  * @brief  Decrypt an application key with the same SAES HW key(wrapper key) used by the HAL_AES_WrapKey() API. \n
  *         This API is only available with SAES instance,
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_key_in          Pointer to **uint32_t** key already encrypted with HAL_AES_WrapKey() API
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @param  timeout_ms        Specify Timeout value in milliseconds
  * @note   This API aims to build a secure application context following this sequence:
  *       - Call HAL_AES_WrapKey() API which encrypts the application key and write it into the output key buffer
  *       - Delete the original key at the application level
  *       - When need to use the original application key to encrypt/decrypt messages, call the HAL_AES_UnwrapKey() API
  *         which unwraps the encrypted key using the same wrapper key and load the unexposed result into registers
  * @warning The key size must be the same one as the wrapper key which is provided as a parameter of the
             HAL_AES_SetHWKey() API
  * @retval HAL_INVALID_PARAM Invalid param return when:
  *                           - The handle instance is not the SAES one
  *                           - The provided application input key pointer is null
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_ERROR         Error return when the selected wrapper key is invalid or when the key derivation exceeds
  *                           the dedicated timeout
  * @retval HAL_TIMEOUT       AES key unwrapping exceeds user timeout
  * @retval HAL_OK            AES key unwrapping is successfully accomplished
  */
hal_status_t HAL_AES_UnwrapKey(hal_aes_handle_t *haes, const uint32_t *p_key_in, hal_aes_key_size_t key_size,
                               uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_key_in != NULL);
  ASSERT_DBG_PARAM(IS_AES_HW_KEY_SIZE(haes, key_size));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_key_in == NULL) || (haes->instance != HAL_SAES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  if (AES_KeyDerivation(haes) != HAL_OK)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Decrypt the SAES application normal key with the unwrapper key already set by HAL_AES_SetHWKey() API in wrap mode:
    The SAES application key becomes usable (decrypted) and can be used to encrypt/decrypt SAES messages */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD, AES_OPERATING_MODE_DECRYPT
             | (uint32_t)HAL_AES_KEY_MODE_WRAPPED);

  haes->p_in_buff = p_key_in;

  if (key_size == HAL_AES_KEY_SIZE_128BIT)
  {
    haes->data_size_byte = 16U;
  }
  else
  {
    haes->data_size_byte = 32U;
  }
  haes->block_count = 0U;

  if (AES_ECB_CBC_CTR_Process(haes, timeout_ms) != HAL_OK)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
/**
  * @brief  Encrypt an application key to be shared with AES peripheral, using SAES HW key. \n
  *         This API is only available with SAES instance,
  * @param  haes              Pointer to a @ref hal_aes_handle_t structure
  * @param  p_key_in          Pointer to **uint32_t** input key provided by the user to be encrypted
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @param  p_key_output      Pointer to **uint32_t** output key provided by the user to be filled with the encrypted
  *                           application key
  * @param  target_id        Specify which AES target can receive the SAES shared key
  *                          00: AES peripheral
  * @param  timeout_ms       Specify Timeout value in milliseconds
  * @note   This API aims to build a secure application context following this sequence:
  *       - Call HAL_AES_EncryptSharedKey() API to encrypt the application key and write it into the output key buffer
  *       - Delete the original key at the application level
  *       - When need to share the original application key with the specified AES target, call the
  *         HAL_AES_DecryptSharedKey() API which decrypts the encrypted key using the same SAES HW keys (wrapper key)
  *         and automatically transfers the unreadable result to the target via secure HW buses. This target must be
  *         configured with the HAL_AES_SetSharedKey() API, then the target keys registers are loaded automatically with
  *         the transferred key.
  * @warning The key size must be the same one as the wrapper key which is provided as a parameter of the
             HAL_AES_SetHWKey() API
  * @retval HAL_INVALID_PARAM Invalid param return when:
  *                           - The handle instance is not the SAES one
  *                           - The provided application input key pointer is null
  *                           - The provided application output key pointer is null
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_ERROR         Error return when the selected wrapper key is invalid
  * @retval HAL_TIMEOUT       AES key wrapping exceeds user timeout
  * @retval HAL_OK            AES key wrapping is successfully accomplished
  */
hal_status_t HAL_AES_EncryptSharedKey(hal_aes_handle_t *haes, const uint32_t *p_key_in, hal_aes_key_size_t key_size,
                                      uint32_t *p_key_output, uint32_t target_id, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_key_in != NULL);
  ASSERT_DBG_PARAM(IS_AES_HW_KEY_SIZE(haes, key_size));
  ASSERT_DBG_PARAM(p_key_output != NULL);
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_key_in == NULL) || (p_key_output == NULL) || (haes->instance != HAL_SAES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Encrypt the SAES application key with the wrapper key already set by HAL_AES_SetHWKey() API in share mode: The SAES
  application key becomes protected(encrypted) and can be shared only after being decrypted with the same wrapper key */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD | AES_CR_KSHAREID,
             AES_OPERATING_MODE_ENCRYPT | (uint32_t)HAL_AES_KEY_MODE_SHARED | target_id);

  haes->p_in_buff = p_key_in;
  haes->p_out_buff = p_key_output;

  if (key_size == HAL_AES_KEY_SIZE_128BIT)
  {
    haes->data_size_byte = 16U;
  }
  else
  {
    haes->data_size_byte = 32U;
  }
  haes->block_count = 0U;

  if (AES_ECB_CBC_CTR_Process(haes, timeout_ms) != HAL_OK)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  Decrypt an application key to be shared with AES peripheral with the same SAES HW key (wrapper key)
  *         used by the HAL_AES_EncryptSharedKey() API. \n
  *         This API is only available with SAES instance.
  * @param  haes             Pointer to a @ref hal_aes_handle_t structure
  * @param  p_key_in         Pointer to **uint32_t** input key provided by the user to be encrypted
  *                          parameters of the application key and the selected wrapper key (The key to be used to
  *                          encrypt the key application)
  * @param  key_size          AES key size with a **hal_aes_key_size_t** type
  * @param  target_id        Specify which target can read the SAES key registers after a decryption
  *                          00: AES peripheral
  * @param  timeout_ms        Specify Timeout value in milliseconds
  * @note   This API aims to build a secure application context following this sequence:
  *       - Call HAL_AES_EncryptSharedKey() API to encrypt the application key and write it into the output key buffer
  *       - Delete the original key at the application level
  *       - When need to share the original application key with the specified AES target, call the
  *         HAL_AES_DecryptSharedKey() API which decrypts the encrypted key using the same SAES HW keys (wrapper key)
  *         and automatically transfers the unreadable result to the target via secure HW buses. This target must be
  *         configured with the HAL_AES_SetSharedKey() API, then the target keys registers are loaded automatically with
  *         the transferred key.
  * @warning The key size must be the same one as the wrapper key which is provided as a parameter of the
             HAL_AES_SetHWKey() API
  * @retval HAL_INVALID_PARAM Invalid param return when:
  *                           - The handle instance is not the SAES one
  *                           - The provided application input key pointer is null
  * @retval HAL_BUSY          Another AES process is ongoing
  * @retval HAL_ERROR         Error return when the selected wrapper key is invalid or when the key derivation exceeds
  *                           the dedicated timeout
  * @retval HAL_TIMEOUT       AES key unwrapping exceeds user timeout
  * @retval HAL_OK            AES key unwrapping is successfully accomplished
  */
hal_status_t HAL_AES_DecryptSharedKey(hal_aes_handle_t *haes, const uint32_t *p_key_in, hal_aes_key_size_t key_size,
                                      uint32_t target_id, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(haes != NULL);
  ASSERT_DBG_PARAM(IS_SAES_ALL_INSTANCE(AES_GET_INSTANCE(haes)));
  ASSERT_DBG_PARAM(p_key_in != NULL);
  ASSERT_DBG_PARAM(IS_AES_HW_KEY_SIZE(haes, key_size));
  ASSERT_DBG_STATE(haes->global_state, HAL_AES_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((haes == NULL) || (timeout_ms == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_key_in == NULL) || (haes->instance != HAL_SAES))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(haes, global_state, HAL_AES_STATE_IDLE, HAL_AES_STATE_ACTIVE);

  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_KEYVALID) == 0U)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  if (AES_KeyDerivation(haes) != HAL_OK)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagRDWRERR(haes);
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes = HAL_AES_ERROR_NONE;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  /* Decrypt the SAES application normal key with the unwrapper key already set by HAL_AES_SetHWKey() API in share mode:
     The SAES application key becomes shareable and can be shared with AES peripherals to encrypt/decrypt messages */
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD | AES_CR_KSHAREID,
             AES_OPERATING_MODE_DECRYPT | (uint32_t)HAL_AES_KEY_MODE_SHARED | target_id);

  haes->p_in_buff = p_key_in;

  if (key_size == HAL_AES_KEY_SIZE_128BIT)
  {
    haes->data_size_byte = 16U;
  }
  else
  {
    haes->data_size_byte = 32U;
  }
  haes->block_count = 0U;

  if (AES_ECB_CBC_CTR_Process(haes, timeout_ms) != HAL_OK)
  {
    haes->global_state = HAL_AES_STATE_IDLE;
    return HAL_TIMEOUT;
  }

  haes->global_state = HAL_AES_STATE_IDLE;
  return HAL_OK;
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO */
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup AES_Private_Functions
  * @{
This subsection provides a set of functions allowing to:
 - Perform configuration operations:
  - AES_SetNormalKey()                 :Allowing to load the key into keys registers
  - AES_WaitForSetKey()                :Allowing to wait for the key to be loaded into keys registers
  - AES_SetIV()                        :Allowing to load the initial vector into IV registers
  - AES_RNGFetchGetStatus()            :Allowing to get status of random numbers fetched from RNG for (SAES only)
 - Manage data transfer between user buffers and the AES/SAES peripheral:
  - AES_ProcessOneblock()              :Allowing to process one block of data(Four words)
  - AES_WaitOnCCFlag()                 :Allowing to Wait for the Computation complete in blocking mode
  - AES_WaitOnCCFlag_NonBlocking()     :Allowing to wait for computation complete flag in non blocking mode
  - AES_KeyDerivation()                :Allowing to derivate the key before performing an ECB/CBC decryption
  - AES_ECB_CBC_CTR_Process()          :Allowing to process data for ECB/CBC/CTR algorithms in polling mode
  - AES_ECB_CBC_CTR_Start_Process_IT() :Allowing to start the ECB/CBC/CTR IT process
  - AES_ECB_CBC_CTR_Process_IT()       :Allowing to process data for ECB/CBC/CTR algorithms in IT mode
  - AES_ECB_CBC_CTR_Process_DMA()      :Allowing to process data for ECB/CBC/CTR algorithms in dma mode
  - AES_ECB_CBC_CTR_DMAInCplt()        :Allowing to manage the DMA input transfer complete callback for ECB/CBC/CTR
  - AES_ECB_CBC_CTR_DMAOutCplt()       :Allowing to manage the DMA output transfer complete callback for ECB/CBC/CTR
  - AES_DMAError()                     :Allowing to manage the DMA error callback
  - AES_GCM_GMAC_CCM_Process()         :Allowing to process data for GCM_GMAC/CCM algorithms in polling mode
  - AES_SetInitPhase()                 :Allowing to perform the INIT phase for GCM_GMAC/CCM algorithms in polling mode
  - AES_SetHeaderPhase()               :Allowing to perform the HEADER phase for GCM_GMAC/CCM algorithms in polling mode
  - AES_SetPayloadPhase()              :Allowing to perform the PAYLOAD phase for GCM_GMAC/CCM algorithms in polling
                                        mode
  - AES_PaddingData()                  :Allowing to perform the data padding for GCM_GMAC/CCM algorithms in polling mode
  - AES_GCM_GMAC_CCM_Start_Process_IT():Allowing to start the GCM_GMAC/CCM IT process
  - AES_SetInitPhase_NonBlocking()     :Allowing to perform the INIT phase for GCM_GMAC/CCM in non blocking mode
  - AES_StartPayloadPhase_IT()         :Allowing to start the GCM_GMAC/CCM IT PAYLOAD phase
  - AES_SetHeaderPhase_IT()            :Allowing to perform the HEADER phase for GCM_GMAC/CCM algorithms in IT mode
  - AES_SetPayloadPhase_IT()           :Allowing to perform the PAYLOAD phase for GCM_GMAC/CCM algorithms in IT mode
  - AES_PaddingData_IT()               :Allowing to perform the data padding for GCM_GMAC/CCM algorithms in IT mode
  - AES_GCM_GMAC_CCM_Process_DMA()     :Allowing to process data for GCM_GMAC/CCM algorithms in dma mode
  - AES_GCM_GMAC_CCM_DMAInCplt()       :Allowing to manage the DMA input transfer complete callback for GCM_GMAC/CCM
  - AES_GCM_GMAC_CCM_DMAOutCplt()      :Allowing to manage the DMA output transfer complete callback for GCM_GMAC/CCM
  - AES_PaddingData_DMA()              :Allowing to perform the data padding for GCM_GMAC/CCM algorithms in DMA mode
  */
/**
  * @brief  Load the AES application key into key registers.
  * @param  haes     Pointer to a @ref hal_aes_handle_t structure
  * @param  key_size AES key size with a **hal_aes_key_size_t** type
  * @param  p_key    A **uint32_t** AES key that must be odd and coherent with the **key_size**
  */
static void AES_SetNormalKey(hal_aes_handle_t *haes, hal_aes_key_size_t key_size, const uint32_t *p_key)
{
  if (key_size == HAL_AES_KEY_SIZE_256BIT)
  {
    AES_GET_INSTANCE(haes)->KEYR7 = *(const uint32_t *)(p_key);
    AES_GET_INSTANCE(haes)->KEYR6 = *(const uint32_t *)(p_key + 1U);
    AES_GET_INSTANCE(haes)->KEYR5 = *(const uint32_t *)(p_key + 2U);
    AES_GET_INSTANCE(haes)->KEYR4 = *(const uint32_t *)(p_key + 3U);
    AES_GET_INSTANCE(haes)->KEYR3 = *(const uint32_t *)(p_key + 4U);
    AES_GET_INSTANCE(haes)->KEYR2 = *(const uint32_t *)(p_key + 5U);
    AES_GET_INSTANCE(haes)->KEYR1 = *(const uint32_t *)(p_key + 6U);
    AES_GET_INSTANCE(haes)->KEYR0 = *(const uint32_t *)(p_key + 7U);
  }
  else
  {
    AES_GET_INSTANCE(haes)->KEYR3 = *(const uint32_t *)(p_key);
    AES_GET_INSTANCE(haes)->KEYR2 = *(const uint32_t *)(p_key + 1U);
    AES_GET_INSTANCE(haes)->KEYR1 = *(const uint32_t *)(p_key + 2U);
    AES_GET_INSTANCE(haes)->KEYR0 = *(const uint32_t *)(p_key + 3U);
  }
}

/**
  * @brief  Wait for the AES application key to be loaded into key registers.
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @note   This is only a key loading without a check for its validity. This check must be done inside the process
  * @retval HAL_ERROR   AES key loading into key registers exceeds the general timeout
  * @retval HAL_OK      AES key loading into key registers is accomplished
  */
static hal_status_t AES_WaitForSetKey(hal_aes_handle_t *haes)
{
  uint32_t tickstart;

  /* Wait for Key to be completely loaded */
  tickstart = HAL_GetTick();
  while (HAL_AES_GetFlag(haes, HAL_AES_FLAG_BUSY) != 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > AES_GENERAL_TIMEOUT_MS)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1)) \
   || (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1)) \
   || (defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1))
/**
  * @brief  Load the AES initial vector into IV registers.
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  p_init_vect Pointer to **const uint32_t** four words buffer provided by the user. For the CTR algorithm, the
  *                     init vector is used to process each data block
  */
static void AES_SetIV(hal_aes_handle_t *haes, const uint32_t *p_init_vect)
{
  /* Set the Initialization Vector */
  AES_GET_INSTANCE(haes)->IVR3 = *(const uint32_t *)p_init_vect;
  AES_GET_INSTANCE(haes)->IVR2 = *(const uint32_t *)(p_init_vect + 1U);
  AES_GET_INSTANCE(haes)->IVR1 = *(const uint32_t *)(p_init_vect + 2U);
  AES_GET_INSTANCE(haes)->IVR0 = *(const uint32_t *)(p_init_vect + 3U);
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO or USE_HAL_AES_CTR_ALGO or USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO
          or USE_HAL_AES_SUSPEND_RESUME */

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1)) \
   || (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
/**
  * @brief  Process one block (equal to four words) : Perform a write to DINR register and a read from DOUTR register.
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES process exceeds user timeout
  * @retval HAL_OK      AES process is successfully accomplished
  */
static hal_status_t AES_ProcessOneblock(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  uint32_t offset = haes->block_count * 4U;
  uint32_t temp[4] = {0};
  uint32_t i;

  /* Write the input block(4 words) in the IN FIFO */
  for (i = 0U; i < 4U ; i++)
  {
    AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)(haes->p_in_buff + offset + i);
  }

  if (AES_WaitOnCCFlag(haes, timeout_ms) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  HAL_AES_ClearFlagCC(haes);

  /* The wrapped SAES application key can be used(encrypt/decrypt messages) only when it is decrypted but it must stay
     secret and can't be read after decryption */
  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE | AES_CR_KMOD)
      != (AES_OPERATING_MODE_DECRYPT | (uint32_t)HAL_AES_KEY_MODE_WRAPPED))
  {
    for (i = 0U; i < 4U ; i++)
    {
      temp[i] = AES_GET_INSTANCE(haes)->DOUTR;
    }
    i = 0U;
    while ((offset < ((haes->data_size_byte + 3U) / 4U)) && (i < 4U))
    {
      *(uint32_t *)(haes->p_out_buff + offset) = temp[i];
      offset++;
      i++;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Handle AES hardware block timeout when waiting for the computation complete flag to be raised.
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES block computation exceeds user timeout
  * @retval HAL_OK      AES block computation is completed
  */
static hal_status_t AES_WaitOnCCFlag(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  uint32_t tickstart;

  /* Wait for computation complete flag to be raised */
  tickstart = HAL_GetTick();
  while (HAL_AES_GetFlag(haes, HAL_AES_FLAG_CC) == 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      AES_DISABLE(haes);
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO or USE_HAL_AES_CTR_ALGO or USE_HAL_AES_GCM_GMAC_ALGO
          or USE_HAL_AES_CCM_ALGO */

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
   || (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
   || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
/**
  * @brief  Handle AES hardware block timeout when waiting for the computation complete flag to be raised in
  *         non blocking mode.
  * @param  haes                 Pointer to a @ref hal_aes_handle_t structure
  * @param  latency_clock_cycle  Specify Latency value in clock cycles
  * @retval HAL_ERROR            AES block computation exceeds timeout
  * @retval HAL_OK               AES block computation is completed
  */
static hal_status_t AES_WaitOnCCFlag_NonBlocking(hal_aes_handle_t *haes, uint32_t latency_clock_cycle)
{
  uint32_t count = latency_clock_cycle;

  do
  {
    count--;
  } while ((HAL_AES_GetFlag(haes, HAL_AES_FLAG_CC) == 0U) && (count != 0U));

  if (count == 0U)
  {
    AES_DISABLE(haes);
    return HAL_ERROR;
  }
  return HAL_OK;
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO or USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
/**
  * @brief  DMA AES error callback. \n
  *         This callback is generated when an error occurred during the DMA input or output transfer.
  * @param  hdma DMA handle
  */
static void AES_DMAError(hal_dma_handle_t *hdma)
{
  hal_aes_handle_t *haes = (hal_aes_handle_t *)(hdma->p_parent);

  /* Disable the DMA transfer */
  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN | AES_CR_DMAOUTEN);

  HAL_AES_ClearFlagCC(haes);

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
  haes->last_error_codes |= HAL_AES_ERROR_DMA;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

  haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  haes->p_error_cb(haes);
#else
  HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
}
#endif /* USE_HAL_AES_DMA */

#if defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)
/**
  * @brief  Get the status of the fetch random numbers operation from RNG after enabling RNG and SAES clocks.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_ERROR Error detected while fetching a random number from RNG peripheral (only for SAES instance)
  * @retval HAL_OK    SAES fetching random number from RNG peripheral is well completed
  */
static hal_status_t AES_RNGFetchGetStatus(hal_aes_handle_t *haes)
{
  uint32_t tickstart;

  /* Verify no RNG random number fetch in progress */
  tickstart = HAL_GetTick();
  while (HAL_AES_GetFlag(haes, HAL_AES_FLAG_BUSY) != 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > AES_GENERAL_TIMEOUT_MS)
    {
      AES_DISABLE(haes);
      return HAL_ERROR;
    }
  }

  /* Verify no random number fetching error flagged */
  if (HAL_AES_GetFlag(haes, HAL_AES_FLAG_RNGERR) != 0U)
  {
#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
    haes->last_error_codes |= HAL_AES_ERROR_RNG;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */
    HAL_AES_ClearFlagRDWRERR(haes);
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  AES key derivation: A mandatory step before decryption.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_ERROR AES key derivation is not yet completed and exceeds the timeout
  * @retval HAL_OK    AES key derivation is completed
  */
static hal_status_t AES_KeyDerivation(hal_aes_handle_t *haes)
{
  uint32_t key_derivation_latency;

  AES_DISABLE(haes);
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_MODE, AES_OPERATING_MODE_KEYDERIVATION);

  AES_ENABLE(haes);

  if (haes->instance == HAL_AES)
  {
    key_derivation_latency = AES_KEY_DERIVATION_LATENCY;
  }
  else
  {
    key_derivation_latency = SAES_KEY_DERIVATION_LATENCY;
  }

  if (AES_WaitOnCCFlag_NonBlocking(haes, key_derivation_latency) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagCC(haes);

  return HAL_OK;
}
#endif /* USE_HAL_AES_ECB_CBC_ALGO */

#if (defined(USE_HAL_AES_ECB_CBC_ALGO) && (USE_HAL_AES_ECB_CBC_ALGO == 1)) \
 || (defined(USE_HAL_AES_CTR_ALGO) && (USE_HAL_AES_CTR_ALGO == 1))
/**
  * @brief  Process all user data by blocks from the user input buffer to the input data register and from the output
  *         data register to the output data buffer. \n
  *         The Padding is not supported.
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES process exceeds user timeout
  * @retval HAL_OK      AES process is successfully accomplished
  */
static hal_status_t AES_ECB_CBC_CTR_Process(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  uint32_t data_block_numbers = (haes->data_size_byte + 15U) / 16U;
  uint32_t block_count;
  uint32_t data_size_sum_byte_tmp;

  AES_ENABLE(haes);

  for (block_count = haes->block_count; block_count < data_block_numbers; block_count++)
  {
    haes->block_count = block_count;
    if (AES_ProcessOneblock(haes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  }

  AES_DISABLE(haes);

  data_size_sum_byte_tmp = haes->data_size_sum_byte;
  haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

  return HAL_OK;
}

/**
  * @brief Enable interrupts and Process one block from the user input buffer to the input data register. \n
  *        Once processed, a computation complete interrupt is then generated, the program enters the IRQHandler, reads
  *        the encrypted block from the output data register and performs the write of a new block, then a second
  *        interrupt is generated.
  * @param haes  Pointer to a @ref hal_aes_handle_t structure
  */
static void AES_ECB_CBC_CTR_Start_Process_IT(hal_aes_handle_t *haes)
{
  uint32_t block_count = haes->block_count;

  AES_ENABLE(haes);

  /* Write one first block(4 words), then a computation Complete interrupt is generated */
  for (uint32_t i = 0U; i < 4U ; i++)
  {
    AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)(haes->p_in_buff + (block_count * 4U) + i);
  }

  HAL_AES_EnableIT(haes, HAL_AES_IT_ALL);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if ((haes->instance == (uint32_t)SAES_S) || (haes->instance == (uint32_t)SAES_NS))
#else
  if (haes->instance == HAL_SAES)
#endif /* USE_HAL_SECURE_CHECK_PARAM */
  {
    HAL_AES_EnableIT(haes, HAL_AES_IT_RNGERR);
  }
}

/**
  * @brief AES interrupt process for ECB, CBC and CTR algorithms. \n
  *        Once a computation complete interrupt is generated, t, the program enters the IRQHandler, reads the
  *        encrypted block from the output data register and performs the write of a new block, then a second interrupt
  *        is generated. \n
  *        The Padding is not supported.
  * @param  haes  Pointer to a @ref hal_aes_handle_t structure
  */
static void AES_ECB_CBC_CTR_Process_IT(hal_aes_handle_t *haes)
{
  uint32_t data_block_numbers = ((haes->data_size_byte + 15U) / 16U);
  uint32_t block_count = haes->block_count;
  uint32_t offset = block_count * 4U;
  uint32_t temp[4] = {0};
  uint32_t i;
  uint32_t data_size_sum_byte_tmp;

  /* Read from DOUTR */
  if (block_count < data_block_numbers)
  {
    /* The wrapped SAES application key can be used(encrypt/decrypt messages) only when it is decrypted but it must
       stay secret and can't be read after decryption */
    if (READ_BIT(AES_GET_INSTANCE(haes)->CR,
                 AES_CR_MODE | AES_CR_KMOD) != (AES_OPERATING_MODE_DECRYPT | (uint32_t)HAL_AES_KEY_MODE_WRAPPED))
      /* Read from DOUTR after each computation complete interrupt: Start to read the first block processed
         via AES_ECB_CBC_CTR_Start_Process_IT */
    {
      for (i = 0U; i < 4U ; i++)
      {
        temp[i] = AES_GET_INSTANCE(haes)->DOUTR;
      }
      i = 0U;
      while ((offset < ((haes->data_size_byte + 3U) / 4U)) && (i < 4U))
      {
        *(uint32_t *)(haes->p_out_buff + offset) = temp[i];
        offset++;
        i++;
      }
    }

    /* Disable interrupts when all the data is processed (The padding is not supported for those algorithms) */
    if (block_count == (data_block_numbers - 1U))
    {
      data_size_sum_byte_tmp = haes->data_size_sum_byte;
      haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

      /* Disable Computation Complete flag and errors interrupts */
      HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
      if ((haes->instance == (uint32_t)SAES_S) || (haes->instance == (uint32_t)SAES_NS))
#else
      if (haes->instance == HAL_SAES)
#endif /* USE_HAL_SECURE_CHECK_PARAM */
      {
        HAL_AES_DisableIT(haes, HAL_AES_IT_RNGERR);
      }

      AES_DISABLE(haes);

      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_out_cplt_cb(haes);
#else
      HAL_AES_OutCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
    }
  }

  /* New block to be processed */
  block_count++;
  haes->block_count = block_count;

  /* Write to DINR generates a computation complete interrupt */
  if (block_count < data_block_numbers)
  {
#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
    /* A suspension is already requested */
    if (haes->suspend_request == AES_SUSPEND)
    {
      HAL_AES_ClearFlagCC(haes);

      haes->suspend_request = AES_SUSPEND_NONE;

      /* Disable Computation Complete flag and errors interrupts */
      HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
      if ((haes->instance == (uint32_t)SAES_S) || (haes->instance == (uint32_t)SAES_NS))
#else
      if (haes->instance == HAL_SAES)
#endif /* USE_HAL_SECURE_CHECK_PARAM */
      {
        HAL_AES_DisableIT(haes, HAL_AES_IT_RNGERR);
      }

      AES_DISABLE(haes);

      haes->global_state = HAL_AES_STATE_SUSPENDED;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_suspend_cb(haes);
#else
      HAL_AES_SuspendCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
    }
    else
#endif /* USE_HAL_AES_SUSPEND_RESUME */
    {
      /* Write the input block(4 words) in the IN FIFO */
      for (i = 0U; i < 4U ; i++)
      {
        AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)(haes->p_in_buff + (block_count * 4U) + i);
      }

      if (block_count == (data_block_numbers - 1U))
      {
#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
        haes->p_in_cplt_cb(haes);
#else
        HAL_AES_InCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      }
    }
  }
}

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
/**
  * @brief AES DMA process for ECB, CBC and CTR algorithms. \n
  *      - Set the DMA configuration
  *      - Start the DMA data transfer from the input user buffer to the AES peripheral, at the end of the transfer, a
  *        callback is then generated
  *      - Start the DMA data transfer from the AES peripheral to the output user buffer, at the end of the transfer a
  *        callback is generated \n
  *        The Padding is not supported.
  * @param  haes      Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_ERROR Error return when the DMA start transfer fails
  * @retval HAL_OK    DMA process is successfully accomplished
  */
static hal_status_t AES_ECB_CBC_CTR_Process_DMA(hal_aes_handle_t *haes)
{
  haes->hdma_in->p_xfer_cplt_cb = AES_ECB_CBC_CTR_DMAInCplt;
  haes->hdma_in->p_xfer_error_cb = AES_DMAError;
  haes->hdma_out->p_xfer_cplt_cb = AES_ECB_CBC_CTR_DMAOutCplt;

  haes->hdma_out->p_xfer_error_cb = AES_DMAError;

  AES_ENABLE(haes);

  if (HAL_DMA_StartPeriphXfer_IT_Opt(haes->hdma_in, (uint32_t)haes->p_in_buff, (uint32_t)&AES_GET_INSTANCE(haes)->DINR,
                                     haes->data_size_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    AES_DISABLE(haes);

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
    haes->last_error_codes |= HAL_AES_ERROR_DMA;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

    haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
    haes->p_error_cb(haes);
#else
    HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

    return HAL_ERROR;
  }

  if (HAL_DMA_StartPeriphXfer_IT_Opt(haes->hdma_out, (uint32_t)&AES_GET_INSTANCE(haes)->DOUTR,
                                     (uint32_t)haes->p_out_buff, haes->data_size_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    AES_DISABLE(haes);

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
    haes->last_error_codes |= HAL_AES_ERROR_DMA;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

    haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
    haes->p_error_cb(haes);
#else
    HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

    return HAL_ERROR;
  }

  SET_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN | AES_CR_DMAOUTEN);

  return HAL_OK;
}

/**
  * @brief  DMA AES transfer in the complete callback for ECB, CBC and CTR algorithms.
  * @param  hdma DMA handle
  */
static void AES_ECB_CBC_CTR_DMAInCplt(hal_dma_handle_t *hdma)
{
  hal_aes_handle_t *haes = (hal_aes_handle_t *)(hdma->p_parent);

  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN);

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  haes->p_in_cplt_cb(haes);
#else
  HAL_AES_InCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
}

/**
  * @brief  DMA AES transfer out complete callback for ECB, CBC and CTR algorithms.
  * @param  hdma DMA handle
  */
static void AES_ECB_CBC_CTR_DMAOutCplt(hal_dma_handle_t *hdma)
{
  uint32_t data_size_sum_byte_tmp;

  hal_aes_handle_t *haes = (hal_aes_handle_t *)(hdma->p_parent);

  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAOUTEN);

  HAL_AES_ClearFlagCC(haes);

  AES_DISABLE(haes);

  data_size_sum_byte_tmp = haes->data_size_sum_byte;
  haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

  haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  haes->p_out_cplt_cb(haes);
#else
  HAL_AES_OutCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
}
#endif /* USE_HAL_AES_DMA */

#endif /* USE_HAL_AES_ECB_CBC_ALGO or USE_HAL_AES_CTR_ALGO */

#if (defined(USE_HAL_AES_GCM_GMAC_ALGO) && (USE_HAL_AES_GCM_GMAC_ALGO == 1)) \
 || (defined(USE_HAL_AES_CCM_ALGO) && (USE_HAL_AES_CCM_ALGO == 1))
/**
  * @brief Process the user data through three phases.
  *      - Initial phase: A mandatory phase which consists of:
  *                      - for GCM: Preparing the hash subkey
  *                      - for CCM: Computing the counter using b0
  *      - Header phase: This phase is skipped for GCM and CCM when the user provides a null header (b1). It consists of
  *                      - for GCM: Processing the additional authenticated data (AAD), with hash computation only,
  *                                 which is the input of GF2mul function to generate the tag
  *                      - for CCM: Processing the associated data (A), with tag computation only
  *      - Payload phase: This phase is skipped for GCM and CCM when the user provided null plaintext. It consists of
  *                       Processing all user data by blocks from the user input buffer to the input data register and
  *                       from the output data register to the output data buffer
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES process exceeds user timeout
  * @retval HAL_OK      AES process is successfully accomplished
  */
static hal_status_t AES_GCM_GMAC_CCM_Process(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  if (haes->data_size_sum_byte  == 0U)
  {
    if (AES_SetInitPhase(haes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    if (haes->header_size_byte == 0U)
    {
      if (haes->data_size_byte == 0U)
      {
        MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
        AES_ENABLE(haes);
        return HAL_OK;
      }
    }
    else
    {
      if (AES_SetHeaderPhase(haes, timeout_ms) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if ((haes->data_size_byte != 0U) && (haes->p_in_buff != NULL))
  {
    if (AES_SetPayloadPhase(haes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initial AES process mandatory phase which consists of:
  *         - for GCM: preparing the hash subkey
  *         - for CCM: computing the counter using b0
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES process exceeds user timeout
  * @retval HAL_OK      AES process is successfully accomplished
  */
static hal_status_t AES_SetInitPhase(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_INIT);
  AES_ENABLE(haes);

  if (AES_WaitOnCCFlag(haes, timeout_ms) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  HAL_AES_ClearFlagCC(haes);

  return HAL_OK;
}

/**
  * @brief  Header AES process phase.
  *       - This phase is skipped when the user provided a null header (b1)
  *       - It consists of processing all header data by blocks from the user input buffer to the input data register
  *       - The driver pads the missing words of the last block with zeros
  *       - No read from AES output data register is required
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES process exceeds user timeout
  * @retval HAL_OK      AES process is successfully accomplished
  */
static hal_status_t AES_SetHeaderPhase(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  uint32_t valid_header_block_numbers = haes->header_size_byte / 16U;
  uint32_t remaining_header_bytes = haes->header_size_byte % 16U;
  uint32_t offset;
  uint32_t header_block_count;

  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_HEADER);
  AES_ENABLE(haes);

  /* Write all the valid blocks (multiple of 4 words), no read to be performed for the header */
  for (header_block_count = 0U; header_block_count < valid_header_block_numbers; header_block_count++)
  {
    haes->block_count = header_block_count;
    offset = haes->block_count * 4U;
    /* Write the input block in the IN FIFO */
    for (uint32_t i = 0U; i < 4U ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)((haes->p_header + offset) + i);
    }

    if (AES_WaitOnCCFlag(haes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
    HAL_AES_ClearFlagCC(haes);
  }

  haes->block_count = header_block_count;

  /* Process the last incomplete block if exist:If some bytes lasts they must be processed in one last block */
  if (remaining_header_bytes != 0U)
  {
    if (AES_PaddingData(haes, haes->p_header, remaining_header_bytes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Payload AES process phase.
  *       - This phase is skipped when the user provided null plaintext
  *       - It consists of processing all user data by blocks from the user input buffer to the input data register and
  *         from the output data register to the output data buffer
  *       - The driver pads the missing words of the last block with zeros
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @param  timeout_ms  Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT AES process exceeds user timeout
  * @retval HAL_OK      AES process is successfully accomplished
  */
static hal_status_t AES_SetPayloadPhase(hal_aes_handle_t *haes, uint32_t timeout_ms)
{
  uint32_t valid_payload_block_numbers = haes->data_size_byte / 16U;
  uint32_t remaining_payload_bytes = haes->data_size_byte % 16U;
  uint32_t tmp;
  uint32_t payload_block_count;
  uint32_t data_size_sum_byte_tmp;

  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
  AES_ENABLE(haes);

  /* Process all the valid blocks (multiple of 4 words) */
  for (payload_block_count = 0U; payload_block_count < valid_payload_block_numbers; payload_block_count++)
  {
    haes->block_count = payload_block_count;
    if (AES_ProcessOneblock(haes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  }

  haes->block_count = payload_block_count;

  /* Process the last incomplete block if exist: If some bytes lasts they must be processed in one last block */
  if (remaining_payload_bytes != 0U)
  {
    tmp = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_MODE);
    if ((tmp == (AES_ALGORITHM_GCM_GMAC | AES_OPERATING_MODE_ENCRYPT))
        || (tmp == (AES_ALGORITHM_CCM | AES_OPERATING_MODE_DECRYPT)))
    {
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_NPBLB, (16U - remaining_payload_bytes) << 20U);
    }

    if (AES_PaddingData(haes, haes->p_in_buff, remaining_payload_bytes, timeout_ms) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
  }

  data_size_sum_byte_tmp = haes->data_size_sum_byte;
  haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

  return HAL_OK;
}

/**
  * @brief  Padding the missing words within the last block with zeros then process a complete padded block.
  * @param  haes            Pointer to a @ref hal_aes_handle_t structure
  * @param  p_tmp_in_buff   Input buffer (Plaintext, ciphertext or header)
  * @param  remaining_bytes The number of bytes within the last block
  * @param  timeout_ms      Specify Timeout value in milliseconds
  * @retval HAL_TIMEOUT     AES process exceeds user timeout
  * @retval HAL_OK          AES process is successfully accomplished
  */
static hal_status_t AES_PaddingData(hal_aes_handle_t *haes, const uint32_t *p_tmp_in_buff, uint32_t remaining_bytes,
                                    uint32_t timeout_ms)
{
  uint32_t last_block_valid_words_numbers;
  uint32_t offset = haes->block_count * 4U;
  const uint32_t *current_address;
  uint32_t counter = 0;
  uint32_t temp[4] = {0};
  uint32_t i;
  uint32_t tmp;
  uint32_t size_tmp = haes->header_size_byte;
  const uint32_t mask[16] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32- bit data type */
                             0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16- bit data type */
                             0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU,  /* 8- bit data type */
                             0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU,  /* 1- bit data type */
                            };

  current_address = (const uint32_t *)(p_tmp_in_buff + offset);

  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_HEADER)
  {
    last_block_valid_words_numbers = remaining_bytes / 4U;
    /* Process valid words within the last block */
    for (i = 0U; i < last_block_valid_words_numbers ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)current_address;
      current_address ++;
    }
    /* Enter last bytes, padded with zeros */
    if ((remaining_bytes % 4U) != 0U)
    {
      tmp =  *current_address;
      tmp &= mask[(READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DATATYPE) * 2U) + (size_tmp % 4U)];
      AES_GET_INSTANCE(haes)->DINR = tmp;
      last_block_valid_words_numbers++;
    }
  }
  else
  {
    last_block_valid_words_numbers = (remaining_bytes + 3U) / 4U;
    /* Process valid words within the last block */
    for (i = 0U; i < last_block_valid_words_numbers ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)current_address;
      current_address ++;
    }
  }

  /* Process the remaining words within the last block as zeros if exist */
  while (counter < (4U - last_block_valid_words_numbers))
  {
    AES_GET_INSTANCE(haes)->DINR = 0x0U;
    counter++;
  }

  if (AES_WaitOnCCFlag(haes, timeout_ms) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }

  HAL_AES_ClearFlagCC(haes);

  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_PAYLOAD)
  {
    for (i = 0U; i < 4U ; i++)
    {
      temp[i] = AES_GET_INSTANCE(haes)->DOUTR;
    }
    i = 0U;
    while ((offset < ((haes->data_size_byte + 3U) / 4U)) && (i < 4U))
    {
      *(uint32_t *)(haes->p_out_buff + offset) = temp[i];
      offset++;
      i++;
    }
  }

  return HAL_OK;
}

/**
  * @brief Enable interrupts and generate computation complete interrupt via one of two cases:
  *        - Case 1: Accomplish the Init phase for the first encrypt call
  *        - Case 2: Skip the Init phase in case of processing the message with several encrypt runs and starts the
  *          payload phase by processing calling the AES_StartPayloadPhase_IT() API
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_ERROR  Error return when the Init phase fails
  * @retval HAL_OK     AES starting IT process is successfully accomplished
  */
static hal_status_t AES_GCM_GMAC_CCM_Start_Process_IT(hal_aes_handle_t *haes)
{
  uint32_t size_tmp = haes->data_size_byte;

  /* Enable interrupts and generate computation complete interrupt by setting the Init phase for first encrypt call */
  if (haes->data_size_sum_byte  == 0U)
  {
    if ((haes->header_size_byte == 0U) && ((size_tmp == 0U)))
    {
      if (AES_SetInitPhase_NonBlocking(haes) != HAL_OK)
      {
        haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
        haes->p_error_cb(haes);
#else
        HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
        return HAL_ERROR;
      }
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
      AES_ENABLE(haes);
      haes->global_state = HAL_AES_STATE_IDLE;
    }
    else
    {
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_INIT);
      AES_ENABLE(haes);

      HAL_AES_EnableIT(haes, HAL_AES_IT_ALL);
    }
  }
  /* Skip the Init phase in case of processing the message with several encrypt runs, Enable interrupts and generate the
    computation complete interrupt via AES_StartPayloadPhase_IT: process one block */
  else
  {
    if ((size_tmp != 0U) && (haes->p_in_buff != NULL))
    {
      AES_StartPayloadPhase_IT(haes);
      HAL_AES_EnableIT(haes, HAL_AES_IT_ALL);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initial AES process in non blocking mode which consists of:
  *         - for GCM: preparing the hash subkey
  *         - for CCM: computing the counter using b0
  * @param  haes       Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_ERROR  AES Init phase exceeds AES_INIT_PHASE_LATENCY
  * @retval HAL_OK     AES Init phase is successfully accomplished
  */
static hal_status_t AES_SetInitPhase_NonBlocking(hal_aes_handle_t *haes)
{
  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_INIT);
  AES_ENABLE(haes);

  if (AES_WaitOnCCFlag_NonBlocking(haes, AES_INIT_PHASE_LATENCY) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagCC(haes);

  return HAL_OK;
}

/**
  * @brief Performing the header phase in interrupt mode for GCM, GMAC and CCM algorithms. \n
  *        Once the Init phase is set by AES_GCM_GMAC_CCM_Start_Process_IT() API, a computation complete interrupt is
  *        generated, then the program enters the IRQHandler, and starts performing the header phase: Each block
  *        writing generates the computation complete interrupt (No block reading during the header phase).
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  */
static void AES_SetHeaderPhase_IT(hal_aes_handle_t *haes)
{
  uint32_t header_block_numbers = (haes->header_size_byte + 15U) / 16U;
  uint32_t valid_header_block_numbers = haes->header_size_byte / 16U;
  uint32_t remaining_header_bytes = haes->header_size_byte % 16U;
  uint32_t offset;
  uint32_t header_block_count = haes->block_count;

  /* Process all the valid blocks (multiple of 4 words):Write blocks only */
  if (header_block_count < valid_header_block_numbers)
  {
#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
    /* A suspension is already requested */
    if ((haes->suspend_request == AES_SUSPEND) && (header_block_count > 0U))
    {
      haes->suspend_request = AES_SUSPEND_NONE;
      HAL_AES_ClearFlagCC(haes);
      /* Disable Computation Complete flag and errors interrupts */
      HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);

      haes->global_state = HAL_AES_STATE_SUSPENDED;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_suspend_cb(haes);
#else
      HAL_AES_SuspendCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
    }
    else
#endif /* USE_HAL_AES_SUSPEND_RESUME */
    {
      offset = header_block_count * 4U;
      /* Write the input block in the IN FIFO */
      for (uint32_t i = 0U; i < 4U ; i++)
      {
        AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)((haes->p_header + offset) + i);
      }

      header_block_count++;
      haes->block_count = header_block_count;
    }
  }
  /* Process the last padded block ( if exist) */
  else
  {
    /* No last block, all header was processed */
    if (header_block_count == header_block_numbers)
    {
      /* When all the header is processed there are two possible cases:
      Case1: Proceed to payload phase: AES_StartPayloadPhase_IT
      Case2: Plaintext null: Disable interrupts and end process */
      if ((haes->data_size_byte != 0U) && (haes->p_in_buff != NULL))
      {
        haes->block_count = 0U;
        HAL_AES_ClearFlagCC(haes);
        MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
        AES_StartPayloadPhase_IT(haes);
      }
      else
      {
        /* Disable Computation Complete flag and errors interrupts */
        HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);
        haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
        haes->p_in_cplt_cb(haes);
#else
        HAL_AES_InCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      }
    }
    else
    {
      AES_PaddingData_IT(haes, haes->p_header, remaining_header_bytes);
      header_block_count++;
      haes->block_count = header_block_count;
    }
  }
}

/**
  * @brief  Start the payload phase by writing the first block to generate a computation complete interrupt.
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  */
static void AES_StartPayloadPhase_IT(hal_aes_handle_t *haes)
{
  uint32_t valid_payload_block_numbers = haes->data_size_byte / 16U;
  uint32_t remaining_payload_bytes = haes->data_size_byte % 16U;
  uint32_t tmp;

  /* Process the first valid block if exist to generate the computation complete interrupt */
  if ((valid_payload_block_numbers - haes->block_count) != 0U)
  {
    /* Write the input block(4 words) in the IN FIFO */
    for (uint32_t i = 0U; i < 4U ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)(haes->p_in_buff + (haes->block_count * 4U) + i);
    }
  }
  /* No valid block exist: Pad the only one last block and Process it to generate the computation complete interrupt */
  else
  {
    tmp = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_MODE);
    if ((tmp == (AES_ALGORITHM_GCM_GMAC | AES_OPERATING_MODE_ENCRYPT))
        || (tmp == (AES_ALGORITHM_CCM | AES_OPERATING_MODE_DECRYPT)))
    {
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_NPBLB, (16U - remaining_payload_bytes) << 20U);
    }

    AES_PaddingData_IT(haes, haes->p_in_buff, remaining_payload_bytes);

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
    haes->p_in_cplt_cb(haes);
#else
    HAL_AES_InCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
  }
}

/**
  * @brief Performing the payload phase in interrupt mode for GCM, GMAC and CCM algorithms. \n
  *        Once a computation complete interrupt is generated by the AES_StartPayloadPhase_IT() API, the program enters
  *        the IRQHandler, reads the encrypted block from the output data register and performs the write of a new block
  *        , then a second interrupt is generated.
  * @param  haes Pointer to a @ref hal_aes_handle_t structure
  */
static void AES_SetPayloadPhase_IT(hal_aes_handle_t *haes)
{
  uint32_t data_block_numbers = (haes->data_size_byte + 15U) / 16U;
  uint32_t valid_block_numbers = haes->data_size_byte / 16U;
  uint32_t remaining_payload_bytes = haes->data_size_byte % 16U;
  uint32_t offset;
  uint32_t block_count = haes->block_count;
  uint32_t tmp;
  uint32_t temp[4] = {0};
  uint32_t i;
  uint32_t data_size_sum_byte_tmp;

  /* Read from DOUTR after each computation complete interrupt
     First start to read the first block processed via AES_StartPayloadPhase_IT */
  if (block_count < data_block_numbers)
  {
    offset = block_count * 4U;
    for (i = 0U; i < 4U ; i++)
    {
      temp[i] = AES_GET_INSTANCE(haes)->DOUTR;
    }
    i = 0U;
    while ((offset < ((haes->data_size_byte + 3U) / 4U)) && (i < 4U))
    {
      *(uint32_t *)(haes->p_out_buff + offset) = temp[i];
      offset++;
      i++;
    }
  }

  block_count++;
  haes->block_count = block_count;
  offset = block_count * 4U;

#if defined(USE_HAL_AES_SUSPEND_RESUME) && (USE_HAL_AES_SUSPEND_RESUME == 1)
  /* A suspension is already requested */
  if (haes->suspend_request == AES_SUSPEND)
  {
    if (block_count <= valid_block_numbers)
    {
      HAL_AES_ClearFlagCC(haes);

      haes->suspend_request = AES_SUSPEND_NONE;

      /* Disable Computation Complete flag and errors interrupts */
      HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);

      haes->global_state = HAL_AES_STATE_SUSPENDED;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_suspend_cb(haes);
#else
      HAL_AES_SuspendCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
    }
  }
  else
#endif /* USE_HAL_AES_SUSPEND_RESUME */
  {
    /* Process valid blocks: write to DINR generates a computation complete interrupt */
    if (block_count < valid_block_numbers)
    {
      /* Write the input block in the IN FIFO */
      for (i = 0U; i < 4U ; i++)
      {
        AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)((haes->p_in_buff + offset) + i);
      }
    }
    /* If all valid blocks are processed: Two possible cases
     Case 1: Pad data and process the last padded block if exist
     Case 2: Invalid block does not exist and all the data is processed :Disable interrupts and end process */
    else if (block_count == valid_block_numbers)
    {
      /* Case1 : Pad data and process the last padded block if exist */
      if (remaining_payload_bytes != 0U)
      {
        tmp = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_MODE);
        if ((tmp == (AES_ALGORITHM_GCM_GMAC | AES_OPERATING_MODE_ENCRYPT))
            || (tmp == (AES_ALGORITHM_CCM | AES_OPERATING_MODE_DECRYPT)))
        {
          MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_NPBLB, (16U - remaining_payload_bytes) << 20U);
        }

        AES_PaddingData_IT(haes, haes->p_in_buff, remaining_payload_bytes);
      }
      /* Case 2: Invalid block does not exist and all the data is processed :Disable interrupts and end process */
      else
      {
        data_size_sum_byte_tmp = haes->data_size_sum_byte;
        haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

        /* Disable Computation Complete flag and errors interrupts */
        HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);

        haes->global_state = HAL_AES_STATE_IDLE;
      }

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_in_cplt_cb(haes);
#else
      HAL_AES_InCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
    }
    /* If all data is processed: The last padded block was just processed in the previous interrupt */
    else
    {
      data_size_sum_byte_tmp = haes->data_size_sum_byte;
      haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

      /* Disable Computation Complete flag and errors interrupts */
      HAL_AES_DisableIT(haes, HAL_AES_IT_ALL);

      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_out_cplt_cb(haes);
#else
      HAL_AES_OutCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
    }
  }
}

/**
  * @brief  Padding the missing words within the last block with zeros then process a complete padded block in IT mode.
  * @param  haes            Pointer to a @ref hal_aes_handle_t structure
  * @param  p_tmp_in_buff   Input buffer (Plaintext, ciphertext or header)
  * @param  remaining_bytes The number of bytes within the last block
  */
static void AES_PaddingData_IT(hal_aes_handle_t *haes, const uint32_t *p_tmp_in_buff, uint32_t remaining_bytes)
{
  uint32_t last_block_valid_words_numbers;
  uint32_t offset = haes->block_count * 4U;
  const uint32_t *current_address;
  uint32_t counter = 0;
  uint32_t i;
  uint32_t tmp;
  uint32_t size_tmp = haes->header_size_byte;
  const uint32_t mask[16] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32- bit data type */
                             0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16- bit data type */
                             0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU,  /* 8- bit data type */
                             0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU,  /* 1- bit data type */
                            };

  current_address = (const uint32_t *)(p_tmp_in_buff + offset);

  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_HEADER)
  {
    last_block_valid_words_numbers = remaining_bytes / 4U;
    /* Process valid words within the last block */
    for (i = 0U; i < last_block_valid_words_numbers ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)current_address;
      current_address ++;
    }
    /* Enter last bytes, padded with zeros */
    if ((remaining_bytes % 4U) != 0U)
    {
      tmp =  *current_address;
      tmp &= mask[(READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DATATYPE) * 2U) + (size_tmp % 4U)];
      AES_GET_INSTANCE(haes)->DINR = tmp;
      last_block_valid_words_numbers++;
    }
  }
  else
  {
    last_block_valid_words_numbers = (remaining_bytes + 3U) / 4U;
    /* Process valid words within the last block */
    for (i = 0U; i < last_block_valid_words_numbers ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)current_address;
      current_address ++;
    }
  }

  /* Process the remaining words within the last block as zeros if exist */
  while (counter < (4U - last_block_valid_words_numbers))
  {
    AES_GET_INSTANCE(haes)->DINR = 0x0U;
    counter++;
  }
}

#if defined(USE_HAL_AES_DMA) && (USE_HAL_AES_DMA == 1)
/**
  * @brief  AES DMA process for GCM, GMAC and CCM algorithm through three phases:
  *       - Initial phase: A mandatory phase Handled only by AES (No DMA transfer) and consists of:
  *                        - for GCM: preparing hash subkey
  *                        - for CCM: computing the counter using b0
  *       - Header phase: This phase is skipped for GCM and CCM when the user provides a null header (b1).
  *                       It consists of:
  *                       - processing all valid header blocks(four words) from the provided user header to the AES
  *                        peripheral (The padding is handled without DMA)
  *       - Payload phase: This phase is skipped for GCM and CCM when the user provides a null plaintext.It consists of:
  *                       - processing all valid plaintext blocks (The padding is handled without DMA)
  * @param  haes       Pointer to a @ref hal_aes_handle_t structure
  * @retval HAL_ERROR  Error return when the DMA start transfer fails or when the AES process exceeds INIT PHASE latency
  * @retval HAL_OK     DMA process is successfully accomplished
  */
static hal_status_t AES_GCM_GMAC_CCM_Process_DMA(hal_aes_handle_t *haes)
{
  hal_status_t status = HAL_ERROR;
  uint32_t size_tmp = haes->data_size_byte;

  if (haes->data_size_sum_byte  == 0U)
  {
    if (AES_SetInitPhase_NonBlocking(haes) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      return HAL_ERROR;
    }

    if ((haes->header_size_byte == 0U) && ((size_tmp == 0U)))
    {
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
      AES_ENABLE(haes);
      haes->global_state = HAL_AES_STATE_IDLE;
      return HAL_OK;
    }
    else if (haes->header_size_byte != 0U)
    {
      status = AES_SetHeaderPhase_DMA(haes);
    }
    else
    {
      status = AES_SetPayloadPhase_DMA(haes);
    }
  }
  else if ((size_tmp != 0U) && (haes->p_in_buff != NULL))
  {
    status = AES_SetPayloadPhase_DMA(haes);
  }
  else
  {
    /* Nothing to do */
  }

  return status;
}

/**
  * @brief AES DMA Payload phase process.
  *      - This phase is skipped when the user provided null plaintext
  *      - There are two possible cases to process data:
  *       - Case1:When there is valid data blocks, the AES_SetPayloadPhase_DMA() acts as follows:
  *         - set the DMA configuration
  *         - start the DMA transfer of all valid data blocks from the input user buffer to the AES peripheral, at the
  *          end of the transfer a callback is generated
  *         - start the DMA data transfer from the AES peripheral to the output user buffer, at the end of the transfer
  *          a callback is generated and handle the invalid last block if exists(Pad missing words with zeros  and
  *          transfer the last block without DMA from the input buffer to the AES peripheral and read out its equivalent
  *          encrypted block
  *       - Case2:When there is any valid data block, (only unique incomplete block) the AES_SetPayloadPhase_DMA() acts
  *         as follows:
  *         - Pad missing words with zeros and transfer data without DMA from the input buffer to the AES peripheral
  *           and read out its equivalent encrypted block
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @note   The minimum data amount transferred with DMA is equal to one block (four complete words), as the DMA
            transfer does not support the padding(the driver handles the padding with a direct transfer of incomplete
            data without using the DMA)
  * @retval HAL_ERROR   Error return when the DMA start transfer fails or when the payload phase exceeds payload latency
  * @retval HAL_OK      DMA process is successfully accomplished
  */
static hal_status_t AES_SetPayloadPhase_DMA(hal_aes_handle_t *haes)
{
  uint32_t tmp;
  uint32_t data_size_sum_byte_tmp;
  uint32_t valid_payload_block_numbers = haes->data_size_byte / 16U;
  uint32_t remaining_payload_bytes = haes->data_size_byte % 16U;


  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_PAYLOAD);
  AES_ENABLE(haes);

  /* If the payload size is at least equal to 16 bytes, feed the payload through DMA.
     If the size_in_bytes is not a multiple of blocks (is not a multiple of four 32- bit words ),
     last bytes feeding and padding is done in AES_DMAInCplt() */
  if (valid_payload_block_numbers > 0U)
  {
    /* Set the AES DMA In transfer complete callback */
    haes->hdma_in->p_xfer_cplt_cb = AES_GCM_GMAC_CCM_DMAInCplt;
    /* Set the DMA In error callback */
    haes->hdma_in->p_xfer_error_cb = AES_DMAError;

    /* Set the AES DMA Out transfer complete callback */
    haes->hdma_out->p_xfer_cplt_cb = AES_GCM_GMAC_CCM_DMAOutCplt;
    /* Set the DMA Out error callback */
    haes->hdma_out->p_xfer_error_cb = AES_DMAError;

    if (HAL_DMA_StartPeriphXfer_IT_Opt(haes->hdma_in, (uint32_t)haes->p_in_buff,
                                       (uint32_t)&AES_GET_INSTANCE(haes)->DINR,
                                       valid_payload_block_numbers * 16U, HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
      AES_DISABLE(haes);

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
      haes->last_error_codes |= HAL_AES_ERROR_DMA;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

      return HAL_ERROR;
    }

    if (HAL_DMA_StartPeriphXfer_IT_Opt(haes->hdma_out, (uint32_t)&AES_GET_INSTANCE(haes)->DOUTR,
                                       (uint32_t)haes->p_out_buff, valid_payload_block_numbers * 16U,
                                       HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
      AES_DISABLE(haes);

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
      haes->last_error_codes |= HAL_AES_ERROR_DMA;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

      return HAL_ERROR;
    }

    /* Enable the DMA transfer by setting the DMAEN bit */
    SET_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN | AES_CR_DMAOUTEN);
  }
  else
  {
    tmp = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_MODE);
    if ((tmp == (AES_ALGORITHM_GCM_GMAC | AES_OPERATING_MODE_ENCRYPT))
        || (tmp == (AES_ALGORITHM_CCM | AES_OPERATING_MODE_DECRYPT)))
    {
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_NPBLB, (16U - remaining_payload_bytes) << 20U);
    }
    if (AES_PaddingData_DMA(haes, haes->p_in_buff, remaining_payload_bytes, AES_PAYLOAD_PHASE_LATENCY) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      return HAL_ERROR;
    }

    data_size_sum_byte_tmp = haes->data_size_sum_byte;
    haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;
    haes->global_state = HAL_AES_STATE_IDLE;
  }

  return HAL_OK;
}

/**
  * @brief  AES DMA Header phase process.
  *       - This phase is skipped when the user provided a null header
  *       - Two possible cases to process data:
  *        - Case1: When there is valid data blocks, the AES_SetHeaderPhase_DMA() acts as follows:
  *          - set the DMA configuration
  *          - start the DMA transfer of all valid data blocks from the input user header to the AES peripheral, at the
  *           end of the transfer a callback is generated and accomplish the following operations:
  *          - Handles the invalid last block if exist(Pad missing words with zeros  and transfer last block without
  *            DMA from input header to AES peripheral
  *          - Initiate the payload phase if plaintext is not null
  *        - Case2: When there is any valid data block, (only unique incomplete block) the AES_SetHeaderPhase_DMA() acts
  *          as follows:
  *          - Pad missing words with zeros  and transfer data without DMA from input header to AES peripheral
  *          - Initiate the payload phase if plaintext is not null
  * @param  haes        Pointer to a @ref hal_aes_handle_t structure
  * @note   The minimum data amount transferred with DMA is equal to one block (four complete words), as the DMA
  *         transfer does not support the padding(the driver handles the padding with a direct transfer of incomplete
  *         data without using the DMA)
  * @retval HAL_ERROR   Error return when the DMA start transfer fails or when the header phase exceeds header latency
  * @retval HAL_OK      DMA process is successfully  accomplished
  */
static hal_status_t AES_SetHeaderPhase_DMA(hal_aes_handle_t *haes)
{
  uint32_t valid_header_block_numbers = haes->header_size_byte / 16U;
  uint32_t remaining_header_bytes = haes->header_size_byte % 16U;

  haes->hdma_in->p_xfer_cplt_cb = AES_GCM_GMAC_CCM_DMAInCplt;
  haes->hdma_in->p_xfer_error_cb = AES_DMAError;

  MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH, AES_PHASE_HEADER);
  AES_ENABLE(haes);

  /* If the header size is at least equal to 16 bytes, feed the header via DMA. else if it is not a multiple of block
     , the last bytes feeding and padding is done in AES_DMAInCplt() */
  if (valid_header_block_numbers > 0U)
  {

    if (HAL_DMA_StartPeriphXfer_IT_Opt(haes->hdma_in, (uint32_t)haes->p_header, (uint32_t)&AES_GET_INSTANCE(haes)->DINR,
                                       valid_header_block_numbers * 16U, HAL_DMA_OPT_IT_NONE) == HAL_OK)
    {
      SET_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN);
    }
    else
    {
      AES_DISABLE(haes);

#if defined(USE_HAL_AES_GET_LAST_ERRORS) && (USE_HAL_AES_GET_LAST_ERRORS == 1)
      haes->last_error_codes |= HAL_AES_ERROR_DMA;
#endif /* USE_HAL_AES_GET_LAST_ERRORS */

      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

      return HAL_ERROR;
    }
  }
  else
  {
    if (AES_PaddingData_DMA(haes, haes->p_header, remaining_header_bytes, AES_HEADER_PHASE_LATENCY) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      return HAL_ERROR;
    }

    if ((haes->data_size_byte != 0U) && (haes->p_in_buff != NULL))
    {
      haes->block_count = 0U;
      if (AES_SetPayloadPhase_DMA(haes) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      HAL_AES_ClearFlagCC(haes);
      haes->global_state = HAL_AES_STATE_IDLE;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Padding the missing words within the last block with zeros during a DMA transfer.
  * @param  haes                Pointer to a @ref hal_aes_handle_t structure
  * @param  p_tmp_in_buff       Input buffer (Plaintext, ciphertext or header)
  * @param  remaining_bytes     The number of bytes within the last block
  * @param  latency_clock_cycle Specify Latency value in clock cycles
  * @retval HAL_ERROR           Error return when the DMA padding exceeds latency
  * @retval HAL_OK              DMA padding is successfully  accomplished
  */
static hal_status_t AES_PaddingData_DMA(hal_aes_handle_t *haes, const uint32_t *p_tmp_in_buff, uint32_t remaining_bytes,
                                        uint32_t latency_clock_cycle)
{
  uint32_t last_block_valid_words_numbers;
  uint32_t offset = haes->block_count * 4U;
  const uint32_t *current_address;
  uint32_t counter = 0;
  uint32_t temp[4] = {0};
  uint32_t i;
  uint32_t tmp;
  uint32_t size_tmp = haes->header_size_byte;
  const uint32_t mask[16] = {0x0U, 0xFF000000U, 0xFFFF0000U, 0xFFFFFF00U,  /* 32- bit data type */
                             0x0U, 0x0000FF00U, 0x0000FFFFU, 0xFF00FFFFU,  /* 16- bit data type */
                             0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU,  /* 8- bit data type */
                             0x0U, 0x000000FFU, 0x0000FFFFU, 0x00FFFFFFU,  /* 1- bit data type */
                            };

  current_address = (const uint32_t *)(p_tmp_in_buff + offset);

  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_HEADER)
  {
    last_block_valid_words_numbers = remaining_bytes / 4U;
    /* Process valid words within the last block */
    for (i = 0U; i < last_block_valid_words_numbers ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)current_address;
      current_address ++;
    }
    /* Enter last bytes, padded with zeros */
    if ((remaining_bytes % 4U) != 0U)
    {
      tmp =  *current_address;
      tmp &= mask[(READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DATATYPE) * 2U) + (size_tmp % 4U)];
      AES_GET_INSTANCE(haes)->DINR = tmp;
      last_block_valid_words_numbers++;
    }
  }
  else
  {
    last_block_valid_words_numbers = (remaining_bytes + 3U) / 4U;
    /* Process valid words within the last block */
    for (i = 0U; i < last_block_valid_words_numbers ; i++)
    {
      AES_GET_INSTANCE(haes)->DINR  = *(const uint32_t *)current_address;
      current_address ++;
    }
  }

  /* Process the remaining words within the last block as zeros if exist */
  while (counter < (4U - last_block_valid_words_numbers))
  {
    AES_GET_INSTANCE(haes)->DINR = 0x0U;
    counter++;
  }

  /* Wait for Computation Complete Flag (CCF) to raise then clear it */
  if (AES_WaitOnCCFlag_NonBlocking(haes, latency_clock_cycle) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_AES_ClearFlagCC(haes);

  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_PAYLOAD)
  {
    for (i = 0U; i < 4U ; i++)
    {
      temp[i] = AES_GET_INSTANCE(haes)->DOUTR;
    }
    i = 0U;
    while ((offset < ((haes->data_size_byte + 3U) / 4U)) && (i < 4U))
    {
      *(uint32_t *)(haes->p_out_buff + offset) = temp[i];
      offset++;
      i++;
    }
  }

  return HAL_OK;
}

/**
  * @brief  DMA AES transfer in complete callback for GCM, GMAC and CCM algorithms.
  * @param  hdma DMA handle
  */
static void AES_GCM_GMAC_CCM_DMAInCplt(hal_dma_handle_t *hdma)
{
  hal_aes_handle_t *haes = (hal_aes_handle_t *)(hdma->p_parent);

  uint32_t valid_header_block_numbers = haes->header_size_byte / 16U;
  uint32_t remaining_header_bytes = haes->header_size_byte % 16U;

  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAINEN);

  /* A DMA transfer complete callback generated from HEADER phase */
  if (READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_GCMPH) == AES_PHASE_HEADER)
  {
    /* Wait for Computation Complete Flag (CCF) to raise then clear it */
    if (AES_WaitOnCCFlag_NonBlocking(haes, AES_HEADER_PHASE_LATENCY) != HAL_OK)
    {

      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      return;
    }

    HAL_AES_ClearFlagCC(haes);

    /* Pad last block if exist */
    if (remaining_header_bytes != 0U)
    {
      haes->block_count = valid_header_block_numbers;
      if (AES_PaddingData_DMA(haes, haes->p_header, remaining_header_bytes, AES_HEADER_PHASE_LATENCY) != HAL_OK)
      {
        haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
        haes->p_error_cb(haes);
#else
        HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
        return;
      }
    }

    if ((haes->data_size_byte != 0U) && (haes->p_in_buff != NULL))
    {
      haes->block_count = 0U;
      (void) AES_SetPayloadPhase_DMA(haes);
    }
    else
    {
      HAL_AES_ClearFlagCC(haes);
      haes->global_state = HAL_AES_STATE_IDLE;
    }
  }
  else /* Payload input complete */
  {
#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
    haes->p_in_cplt_cb(haes);
#else
    HAL_AES_InCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
  }
}

/**
  * @brief  DMA AES transfer out complete callback for GCM, GMAC and CCM algorithms.
  * @param  hdma DMA handle
  */
static void AES_GCM_GMAC_CCM_DMAOutCplt(hal_dma_handle_t *hdma)
{
  hal_aes_handle_t *haes = (hal_aes_handle_t *)(hdma->p_parent);

  uint32_t valid_payload_block_numbers = haes->data_size_byte / 16U;
  uint32_t remaining_payload_bytes = haes->data_size_byte % 16U;
  uint32_t tmp;
  uint32_t data_size_sum_byte_tmp;

  CLEAR_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_DMAOUTEN);

  /* Check if last block exists after DMA transfer complete callback generated from PAYLOAD phase */
  if (remaining_payload_bytes != 0U)
  {
    HAL_AES_ClearFlagCC(haes);
    tmp = READ_BIT(AES_GET_INSTANCE(haes)->CR, AES_CR_CHMOD | AES_CR_MODE);
    if ((tmp == (AES_ALGORITHM_GCM_GMAC | AES_OPERATING_MODE_ENCRYPT))
        || (tmp == (AES_ALGORITHM_CCM | AES_OPERATING_MODE_DECRYPT)))
    {
      MODIFY_REG(AES_GET_INSTANCE(haes)->CR, AES_CR_NPBLB, (16U - remaining_payload_bytes) << 20U);
    }

    haes->block_count = valid_payload_block_numbers;

    if (AES_PaddingData_DMA(haes, haes->p_in_buff, remaining_payload_bytes, AES_PAYLOAD_PHASE_LATENCY) != HAL_OK)
    {
      haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
      haes->p_error_cb(haes);
#else
      HAL_AES_ErrorCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */
      return;
    }
  }

  HAL_AES_ClearFlagCC(haes);

  data_size_sum_byte_tmp = haes->data_size_sum_byte;
  haes->data_size_sum_byte = data_size_sum_byte_tmp + haes->data_size_byte;

  haes->global_state = HAL_AES_STATE_IDLE;

#if defined(USE_HAL_AES_REGISTER_CALLBACKS) && (USE_HAL_AES_REGISTER_CALLBACKS == 1)
  haes->p_out_cplt_cb(haes);
#else
  HAL_AES_OutCpltCallback(haes);
#endif /* (USE_HAL_AES_REGISTER_CALLBACKS) */

}
#endif /* USE_HAL_AES_DMA */
#endif /* USE_HAL_AES_GCM_GMAC_ALGO or USE_HAL_AES_CCM_ALGO */
/**
  * @}
  */
#endif /* USE_HAL_AES_ECB_CBC_ALGO || USE_HAL_AES_CTR_ALGO || USE_HAL_AES_GCM_GMAC_ALGO || USE_HAL_AES_CCM_ALGO*/
#endif /* USE_HAL_AES_MODULE */

/**
  * @}
  */
#endif /* AES or SAES */
/**
  * @}
  */
