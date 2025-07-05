/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_pka.c
  * @brief   PKA HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of public key accelerator(PKA):
  *           + Initialization and de-initialization functions
  *           + Start an operation
  *           + Retrieve the operation result
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

#if defined(PKA)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup PKA
  * @{

An explanation on PKA overall usage :
- PKA is the abbreviation of public key accelerator. It's intended for the computation of cryptographic public key
  primitives, specifically those related to RSA, Diffie-Hellmann or ECC (elliptic curve
  cryptography) over GF(p) (Galois fields). To achieve high performance at a reasonable cost,
  these operations are executed in the Montgomery domain.

- For a given operation, all needed computations are performed within the accelerator, so no
  further hardware/software elaboration is needed to process the inputs or the outputs.

This file provides firmware functions to manage the following functionalities of PKA peripheral:

- Initialization and De-initialization functions
- Configuration functions
- Process management functions
- Callback functions
- State and Error functions

# How to use the PKA HAL module driver

## Initialization and de-initialization functions:

- Declare a hal_pka_handle_t handle structure, for example: hal_pka_handle_t hpka.
- Use HAL_PKA_Init() function to initialize the PKA handle and associate the physical instance.
- Use HAL_PKA_DeInit() function to abort any ongoing operation then reset the state.

## Configuration functions

- Use HAL_PKA_SetConfigModExp() function to configure the Modular exponentiation operating mode.
- Use HAL_PKA_SetConfigModExpFast() function to configure the Modular exponentiation (fast) operating mode.
- Use HAL_PKA_SetConfigModExpProtect() function to configure the Modular exponentiation (protected) operating mode.
- Use HAL_PKA_SetConfigAdd() function to configure the Arithmetic addition operating mode.
- Use HAL_PKA_SetConfigSub() function to configure the Arithmetic subtraction operating mode.
- Use HAL_PKA_SetConfigCmp() function to configure the Arithmetic comparison operating mode.
- Use HAL_PKA_SetConfigMul() function to configure the Arithmetic multiplication operating mode.
- Use HAL_PKA_SetConfigModAdd() function to configure the Modular addition operating mode.
- Use HAL_PKA_SetConfigModSub() function to configure the Modular subtraction operating mode.
- Use HAL_PKA_SetConfigModInv() function to configure the Modular inversion operating mode.
- Use HAL_PKA_SetConfigModRed() function to configure the Modular reduction operating mode.
- Use HAL_PKA_SetConfigMontgomeryMul() function to configure the Montgomery multiplication operating mode.
- Use HAL_PKA_SetConfigMontgomery() function to configure the Montgomery parameter operating mode.
- Use HAL_PKA_ECDSA_SetConfigSignature() function to configure the elliptic curves over prime fields signature operating
  mode.
- Use HAL_PKA_ECDSA_SetConfigVerifSignature() function to configure the elliptic curves over prime fields verification
  operating mode.
- Use HAL_PKA_RSA_SetConfigCRTExp() function to configure the RSA CRT exponentiation operating mode.
- Use HAL_PKA_RSA_SetConfigSignature() function to configure the RSA signature operating mode.
- Use HAL_PKA_RSA_SetConfigVerifSignature() function to configure the RSA verification operating mode.
- Use HAL_PKA_ECC_SetConfigPointCheck() function to configure the Point on elliptic curve check operating mode.
- Use HAL_PKA_ECC_SetConfigMul() function to configure the ECC scalar multiplication operating mode.
- Use HAL_PKA_ECC_SetConfigDoubleBaseLadder() function to configure the ECC double base ladder operating mode.
- Use HAL_PKA_ECC_SetConfigProjectiveToAffine() function to configure the ECC projective to affine operating mode.
- Use HAL_PKA_ECC_SetConfigCompleteAdd() function to configure the ECC complete addition operating mode.

## Process management functions

- Use HAL_PKA_Compute() function to execute the operation in blocking mode.
- Use HAL_PKA_Compute_IT() function to execute the operation in interrupt mode.
- Use HAL_PKA_IRQHandler() function called under PKA NVIC vector interrupt subroutine to handle any PKA interrupt.
- Use HAL_PKA_Abort() function to abort any on-going operation.
  This API must not be called from an interrupt service routine.
- Use HAL_PKA_GetResultModExp() function to retrieve the result of the Modular exponentiation operation.
- Use HAL_PKA_GetResultModExpFast() function to retrieve the result of the Modular exponentiation (Fast) operation.
- Use HAL_PKA_GetResultModExpProtected() function to retrieve the result of the Modular exponentiation (Protected)
  operation.
- Use HAL_PKA_GetResultAdd() function to retrieve the result of the addition operation.
- Use HAL_PKA_GetResultSub() function to retrieve the result of the subtraction operation.
- Use HAL_PKA_GetResultMul() function to retrieve the result of the multiplication operation.
- Use HAL_PKA_GetResultCmp() function to retrieve the result of the comparison operation.
- Use HAL_PKA_GetResultModAdd() function to retrieve the result of the Modular addition operation.
- Use HAL_PKA_GetResultModSub() function to retrieve the result of the Modular subtraction operation.
- Use HAL_PKA_GetResultModInv() function to retrieve the result of the Modular inversion operation.
- Use HAL_PKA_GetResultModRed() function to retrieve the result of the Modular reduction operation.
- Use HAL_PKA_GetResultMontgomeryMul() function to retrieve the result of the Montgomery parameter operation.
- Use HAL_PKA_GetResultMontgomery() function to retrieve the result of the Montgomery parameter operation.
- Use HAL_PKA_ECDSA_GetResultSignature() function to retrieve the result of the elliptic curves over prime fields
  signature operation.
- Use HAL_PKA_ECDSA_IsValidVerifSignature() function to check if the signature is verified or not.
- Use HAL_PKA_RSA_GetResultCRTExp() function to retrieve the result of the RSA CRT exponentiation operation.
- Use HAL_PKA_RSA_GetResultSignature() function to retrieve the result of the RSA signature operation.
- Use HAL_PKA_RSA_IsValidVerifSignature() function to check if the signature is verified or not.
- Use HAL_PKA_ECC_IsPointCheckOnCurve() function to check if the point is on curve or not.
- Use HAL_PKA_ECC_GetResultMul() function to retrieve the result of the ECC scalar multiplication operation.
- Use HAL_PKA_ECC_GetResultDoubleBaseLadder() function to retrieve the result of the ECC double base ladder
  operation.
- Use HAL_PKA_ECC_GetResultProjectiveToAffine() function to retrieve the result of the ECC projective to affine
  operation.
- Use HAL_PKA_ECC_GetResultCompleteAdd() function to retrieve the result of the ECC complete addition
  operation.

## Callback functions

- The HAL_PKA_OperationCpltCallback() function is called when the process is complete.
- The HAL_PKA_ErrorCallback() function is called in case of an error.
- Use the function HAL_PKA_RegisterOperationCpltCallback() to register the PKA Operation Complete Callback to be used
  instead of the weak HAL_PKA_OperationCpltCallback() predefined callback.
- Use the function HAL_PKA_RegisterErrorCallback() to register the PKA Error Callback to be used instead of the weak
  HAL_PKA_ErrorCallback() predefined callback.

## Peripheral state, Error functions

- Use HAL_PKA_GetState() function to get the current state of the HAL PKA driver.
- Use HAL_PKA_GetLastErrorCodes() function to Get last error codes.
- Use HAL_PKA_SetUserData() function to set the PKA user data.
- Use HAL_PKA_GetUserData() function to get the PKA user data.

## PKA RAM Erase function

- Use HAL_PKA_RAMMassErase() to fully erase the content of PKA RAM.

## Configuration inside the PKA driver

Config defines                | Description     |Default value  | Note                                                 |
------------------------------| ------------    |-------------  | -----------------------------------------------------|
PRODUCT                       | from IDE        |      NA       | The selected device (ex stm32u5xx )            |
USE_ASSERT_DBG_PARAM          | from IDE        |     None      | Allows to use the assert check parameters.           |
USE_ASSERT_DBG_STATE          | from IDE        |     None      | Allows to use the assert check states.               |
USE_HAL_CHECK_PARAM           | from hal_conf.h |       0       | Parameters run-time check.                           |
USE_HAL_SECURE_CHECK_PARAM    | from hal_conf.h |       0       | Parameters run-time check for sensitive APIs         |
USE_HAL_CHECK_PROCESS_STATE   | from hal_conf.h |       0       | Allows to use the load and store exclusive.          |
USE_HAL_PKA_MODULE            | from hal_conf.h |       1       | Allows to use HAL PKA module.                        |
USE_HAL_PKA_CLK_ENABLE_MODEL| from hal_conf.h |HAL_CLK_ENABLE_NO| Allows to use the clock interface management for PKA.|
USE_HAL_PKA_GET_LAST_ERRORS   | from hal_conf.h |       0       | Allows to use error code mechanism.                  |
USE_HAL_PKA_USER_DATA         | from hal_conf.h |       0       | Allows to use user data.                             |
USE_HAL_PKA_REGISTER_CALLBACKS| from hal_conf.h |       0       | Enable the register callbacks assert                 |
  */

#if defined(USE_HAL_PKA_MODULE) && (USE_HAL_PKA_MODULE == 1)

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup PKA_Private_Constants PKA Private Constants
  * @{
  */
#define PKA_RAM_SIZE                                  1334U                            /*!< PKA RAM size             */
#define PKA_INITIALIZATION_TIMEOUT                    1000UL                           /*!< 1s is the timeout for
                                                                                            initializing PKA device  */
#define PKA_OPERATION_ERROR_NONE                      0xD60DUL                         /*!< Point on curve           */
#define PKA_ROS_RESULT_MAX_SIZE                       520UL                            /*!< Max size of the RSA result
                                                                                            in byte                  */
#define PKA_EOS_RESULT_MAX_SIZE                       80UL                             /*!< Max size of the ECC result
                                                                                            in byte                  */
#define PKA_CMP_RESULT_SIZE                           2UL                              /*!< Size of the cmp result in
                                                                                            byte                     */
#define PKA_OPERATION_NO_ERROR_OFFSET                 0UL                              /*!< PKA no result error      */
#define PKA_OPERATION_MOD_EXP_PROT_ERROR_OFFSET       PKA_MODULAR_EXP_OUT_ERROR        /*!< PKA modular exponentiation
                                                                                            (protected) result error */
#define PKA_OPERATION_ECDSA_SIGN_ERROR_OFFSET         PKA_ECDSA_SIGN_OUT_ERROR         /*!< PKA ECDSA signature result
                                                                                            error                    */
#define PKA_OPERATION_ECC_SCALAR_MUL_ERROR_OFFSET     PKA_ECC_SCALAR_MUL_OUT_ERROR     /*!< PKA ECC scalar
                                                                                            multiplication result
                                                                                            error                    */
#define PKA_OPERATION_ECC_DOUBLE_LADDER_ERROR_OFFSET  PKA_ECC_DOUBLE_LADDER_OUT_ERROR  /*!< PKA ECC double base ladder
                                                                                            result error             */
#define PKA_OPERATION_ECC_PROJECTIVE_AFF_ERROR_OFFSET PKA_ECC_PROJECTIVE_AFF_OUT_ERROR /*!< PKA ECC projective affine
                                                                                            result error             */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup PKA_Private_Macros PKA Private Macros
  * @{
  */
/**
  * @brief Get the PKA instance
  */
#define PKA_GET_INSTANCE(handle) ((PKA_TypeDef *)((uint32_t)(handle)->instance))

/**
  * @brief PKA RAM word access
  */
#define PKA_RAM_WORD_ACCESS(handle, idx) (*(volatile uint32_t *)(uint32_t) \
                                          &((PKA_TypeDef *)((uint32_t)(handle)->instance))->RAM[idx * 4U])
/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup PKA_Private_Functions PKA Private Functions
  * @{
  */
static void         PKA_SetConfigArithmetic(hal_pka_handle_t *hpka, const uint32_t size_byte,
                                            const uint8_t *p_operand_1, const uint8_t *p_operand_2,
                                            const uint8_t *p_operand_3);
static hal_status_t PKA_CheckError(hal_pka_handle_t *hpka, uint32_t operation);
static uint32_t     PKA_CheckRAMError(hal_pka_handle_t *hpka, uint32_t operation);
static uint32_t     PKA_GetOptBitSize_u8(uint32_t nbr_byte, uint8_t msb);
static void         PKA_Memcpy_u8_to_u32(volatile uint32_t *p_dst, const uint8_t *p_src, size_t nbr_byte);
static void         PKA_Memcpy_u8_to_u8(volatile uint8_t *p_dst, volatile const uint8_t *p_src, size_t nbr_byte);
static hal_status_t PKA_WaitInitOkUntilTimeout(hal_pka_handle_t *hpka, uint32_t flag_state,
                                               uint32_t timeout_ms);
static uint32_t     PKA_GetResultSize(const hal_pka_handle_t *hpka, uint32_t start_index, uint32_t max_size);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup PKA_Exported_Functions
  * @{
  */

/** @addtogroup PKA_Exported_Functions_Group1
  * @{
This sub-section provides a set of functions allowing to initialize and de-initialize the PKA peripheral:

- Call the function HAL_PKA_Init() to initialize the HAL PKA handle and associate a PKA peripheral instance.
- Call the function HAL_PKA_DeInit() to de-initialize the HAL PKA instance by stopping any ongoing process and
  resetting the state machine.

  */

/**
  * @brief  Initialize the PKA handle and associate physical instance.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  instance          Specify the PKA instance.
  * @retval HAL_INVALID_PARAM Invalid parameter when hpka pointer is NULL.
  * @retval HAL_OK            PKA is successfully initialized.

  */
hal_status_t HAL_PKA_Init(hal_pka_handle_t *hpka, hal_pka_t instance)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(IS_PKA_ALL_INSTANCE((PKA_TypeDef *)((uint32_t)instance)));
#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
     || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

  hpka->instance = instance;

#if defined(USE_HAL_PKA_CLK_ENABLE_MODEL) && (USE_HAL_PKA_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_PKA_EnableClock();
#endif /* USE_HAL_PKA_CLK_ENABLE_MODEL */

#if defined (USE_HAL_PKA_REGISTER_CALLBACKS) && (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
  hpka->p_operation_cplt_cb = HAL_PKA_OperationCpltCallback;
  hpka->p_error_cb          = HAL_PKA_ErrorCallback;
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

#if defined(USE_HAL_PKA_USER_DATA) && (USE_HAL_PKA_USER_DATA == 1)
  hpka->p_user_data = NULL;
#endif /* USE_HAL_PKA_USER_DATA */

#if defined (USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->global_state = HAL_PKA_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief De-initialize the PKA handle by aborting any PKA operation in progress.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  */
void HAL_PKA_DeInit(hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(IS_PKA_ALL_INSTANCE(PKA_GET_INSTANCE(hpka)));

  LL_PKA_Disable(PKA_GET_INSTANCE(hpka));
  LL_PKA_ClearFlag(PKA_GET_INSTANCE(hpka), LL_PKA_FLAG_ALL);

  hpka->global_state = HAL_PKA_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group2
  * @{
This sub-section provides a set of functions allowing to configure the PKA operations.


  PKA Modular exponentiation configuration functions

- Call the function HAL_PKA_SetConfigModExp() to configure the Modular exponentiation operation.
- Call the function HAL_PKA_SetConfigModExpFast() to configure the Modular exponentiation (fast) operation.
- Call the function HAL_PKA_SetConfigModExpProtect() to configure the Modular exponentiation (protected) operation.

  PKA arithmetic configuration functions

- Call the function HAL_PKA_SetConfigAdd() to configure the Arithmetic addition operation.
- Call the function HAL_PKA_SetConfigSub() to configure the Arithmetic subtraction operation.
- Call the function HAL_PKA_SetConfigCmp() to configure the Arithmetic comparison operation.
- Call the function HAL_PKA_SetConfigMul() to configure the Arithmetic multiplication operation.
- Call the function HAL_PKA_SetConfigModAdd() to configure the Modular addition operation.
- Call the function HAL_PKA_SetConfigModSub() to configure the Modular subtraction operation.
- Call the function HAL_PKA_SetConfigModInv() to configure the Modular inversion operation.
- Call the function HAL_PKA_SetConfigModRed() to configure the Modular reduction operation.
- Call the function HAL_PKA_SetConfigMontgomeryMul() to configure the Montgomery multiplication operation.
- Call the function HAL_PKA_SetConfigMontgomery() to configure the Montgomery parameter operation.

  PKA RSA configuration functions

- Call the function HAL_PKA_RSA_SetConfigCRTExp() to configure the RSA CRT exponentiation operation.
- Call the function HAL_PKA_RSA_SetConfigSignature() to configure the RSA signature operation.
- Call the function HAL_PKA_RSA_SetConfigVerifSignature() to configure the RSA verification operation.

  PKA ECDSA configuration functions

- Call the function HAL_PKA_ECDSA_SetConfigSignature() to configure the elliptic curves over prime fields signature
  operation.
- Call the function HAL_PKA_ECDSA_SetConfigVerifSignature() to configure the elliptic curves over prime fields
  verification operation.

  PKA ECC configuration functions

- Call the function HAL_PKA_ECC_SetConfigPointCheck() to configure the Point on elliptic curve check operation.
- Call the function HAL_PKA_ECC_SetConfigMul() to configure the ECC scalar multiplication operation.
- Call the function HAL_PKA_ECC_SetConfigDoubleBaseLadder() to configure the ECC double base ladder operation.
- Call the function HAL_PKA_ECC_SetConfigProjectiveToAffine() to configure the ECC projective to affine operation.
- Call the function HAL_PKA_ECC_SetConfigCompleteAdd() to configure the ECC complete addition operation.
  */

/**
  * @brief  Set the Modular exponentiation configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_exp_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular exponentiation is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModExp(hal_pka_handle_t *hpka, const hal_pka_mod_exp_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_exponent != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->exponent_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->operand_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_exponent == NULL) || (p_config->p_operand == NULL) \
      || (p_config->p_modulus == NULL) || (p_config->exponent_size_byte == 0U) || (p_config->operand_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_EXP);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_OP_NB_BITS)  = p_config->operand_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXP_NB_BITS) = p_config->exponent_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT_BASE),
                       p_config->p_operand, p_config->operand_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT),
                       p_config->p_exponent, p_config->exponent_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_MODULUS),
                       p_config->p_modulus, p_config->operand_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the Modular exponentiation (fast) Mode configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_exp_fast_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular exponentiation (fast) is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModExpFast(hal_pka_handle_t *hpka, const hal_pka_mod_exp_fast_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_exponent != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_montgomery_param != NULL);
  ASSERT_DBG_PARAM(p_config->exponent_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->operand_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_exponent == NULL) || (p_config->p_operand == NULL) \
      || (p_config->p_modulus == NULL) || (p_config->p_montgomery_param == NULL)            \
      || (p_config->exponent_size_byte == 0U) || (p_config->operand_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_EXP_FAST);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_OP_NB_BITS)  = p_config->operand_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXP_NB_BITS) = p_config->exponent_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT_BASE),
                       p_config->p_operand, p_config->operand_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT),
                       p_config->p_exponent, p_config->exponent_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_MODULUS),
                       p_config->p_modulus, p_config->operand_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_MONTGOMERY_PARAM),
                       p_config->p_montgomery_param, p_config->operand_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the Modular exponentiation (protected) configuration.
  *         Useful when a secret information is involved (RSA decryption).
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_exp_protect_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular exponentiation (protected) is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModExpProtect(hal_pka_handle_t *hpka, const hal_pka_mod_exp_protect_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_exponent != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_phi != NULL);
  ASSERT_DBG_PARAM(p_config->exponent_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->operand_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_exponent == NULL) || (p_config->p_operand == NULL)                  \
      || (p_config->p_modulus == NULL) || (p_config->p_phi == NULL)  || (p_config->exponent_size_byte == 0U) \
      || (p_config->operand_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_EXP_PROTECT);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_OP_NB_BITS)  = p_config->operand_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXP_NB_BITS) = p_config->exponent_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT_BASE),
                       p_config->p_operand, p_config->operand_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_PROTECT_IN_EXPONENT),
                       p_config->p_exponent, p_config->exponent_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_PROTECT_IN_MODULUS),
                       p_config->p_modulus, p_config->operand_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_PROTECT_IN_PHI),
                       p_config->p_phi, p_config->operand_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_MOD_EXP_PROT_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the message signature configuration using elliptic curves over prime fields.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_ecdsa_signature_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Signature of a message is successfully configured.
  */
hal_status_t HAL_PKA_ECDSA_SetConfigSignature(hal_pka_handle_t *hpka, const hal_pka_ecdsa_signature_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_b != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_integer != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y != NULL);
  ASSERT_DBG_PARAM(p_config->p_hash != NULL);
  ASSERT_DBG_PARAM(p_config->p_private_key != NULL);
  ASSERT_DBG_PARAM(p_config->p_prime_order != NULL);
  ASSERT_DBG_PARAM(p_config->prime_order_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->coeff_sign != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_coeff == NULL) || (p_config->p_coeff_b == NULL) || (p_config->p_hash == NULL) \
      || (p_config->p_integer == NULL) || (p_config->p_base_pt_x == NULL) || (p_config->p_base_pt_y == NULL)           \
      || (p_config->p_modulus == NULL) || (p_config->p_private_key == NULL) || (p_config->p_prime_order == NULL)       \
      || (p_config->prime_order_size_byte == 0U) || (p_config->modulus_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ECDSA_SIGNATURE);

  PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_ORDER_NB_BITS) = PKA_GetOptBitSize_u8(p_config->prime_order_size_byte,
                                                               *(p_config->p_prime_order));
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_MOD_NB_BITS)   = PKA_GetOptBitSize_u8(p_config->modulus_size_byte,
                                                               *(p_config->p_modulus));
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_A_COEFF_SIGN)  = p_config->coeff_sign;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_A_COEFF), p_config->p_coeff,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_B_COEFF), p_config->p_coeff_b,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_MOD_GF), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_K), p_config->p_integer,
                       p_config->prime_order_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_INITIAL_POINT_X), p_config->p_base_pt_x,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_INITIAL_POINT_Y), p_config->p_base_pt_y,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_HASH_E), p_config->p_hash,
                       p_config->prime_order_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_PRIVATE_KEY_D), p_config->p_private_key,
                       p_config->prime_order_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_SIGN_IN_ORDER_N), p_config->p_prime_order,
                       p_config->prime_order_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_ECDSA_SIGN_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the configuration for verifying the validity of a signature using elliptic curves over prime fields.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_ecdsa_verif_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            The verification of signature validity is successfully configured.
  */
hal_status_t HAL_PKA_ECDSA_SetConfigVerifSignature(hal_pka_handle_t *hpka, const hal_pka_ecdsa_verif_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_r_sign != NULL);
  ASSERT_DBG_PARAM(p_config->p_s_sign != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y != NULL);
  ASSERT_DBG_PARAM(p_config->p_hash != NULL);
  ASSERT_DBG_PARAM(p_config->p_pub_key_curve_pt_x != NULL);
  ASSERT_DBG_PARAM(p_config->p_pub_key_curve_pt_y != NULL);
  ASSERT_DBG_PARAM(p_config->p_prime_order != NULL);
  ASSERT_DBG_PARAM(p_config->prime_order_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->coeff_sign != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_coeff == NULL) || (p_config->p_modulus == NULL) || (p_config->p_hash == NULL) \
      || (p_config->p_r_sign == NULL) || (p_config->p_s_sign == NULL) || (p_config->p_base_pt_x == NULL)               \
      || (p_config->p_base_pt_y == NULL) || (p_config->p_pub_key_curve_pt_x == NULL)                                   \
      || (p_config->p_pub_key_curve_pt_y == NULL) || (p_config->p_prime_order == NULL)                                 \
      || (p_config->prime_order_size_byte == 0U) || (p_config->modulus_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ECDSA_VERIFICATION);

  PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_ORDER_NB_BITS) = PKA_GetOptBitSize_u8(p_config->prime_order_size_byte,
                                                                *(p_config->p_prime_order));
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_MOD_NB_BITS)   = PKA_GetOptBitSize_u8(p_config->modulus_size_byte,
                                                                *(p_config->p_modulus));
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_A_COEFF_SIGN)  = p_config->coeff_sign;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_A_COEFF), p_config->p_coeff,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_MOD_GF), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_INITIAL_POINT_X), p_config->p_base_pt_x,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_INITIAL_POINT_Y), p_config->p_base_pt_y,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_PUBLIC_KEY_POINT_X),
                       p_config->p_pub_key_curve_pt_x, p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_PUBLIC_KEY_POINT_Y),
                       p_config->p_pub_key_curve_pt_y, p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_SIGNATURE_R), p_config->p_r_sign,
                       p_config->prime_order_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_SIGNATURE_S), p_config->p_s_sign,
                       p_config->prime_order_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_HASH_E), p_config->p_hash,
                       p_config->prime_order_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_IN_ORDER_N), p_config->p_prime_order,
                       p_config->prime_order_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the RSA CRT exponentiation configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_rsa_crt_exp_config_t  configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            RSA CRT exponentiation is successfully configured.
  */
hal_status_t HAL_PKA_RSA_SetConfigCRTExp(hal_pka_handle_t *hpka, const hal_pka_rsa_crt_exp_config_t  *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_a != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_dp != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_dq != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_qinv != NULL);
  ASSERT_DBG_PARAM(p_config->p_prime_p != NULL);
  ASSERT_DBG_PARAM(p_config->p_prime_q != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_a == NULL) || (p_config->p_operand_dp == NULL)                  \
      || (p_config->p_operand_dq == NULL) || (p_config->p_operand_qinv == NULL) || (p_config->p_prime_p == NULL) \
      || (p_config->p_prime_q == NULL) || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_RSA_CRT_EXP);

  PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_MOD_NB_BITS) = p_config->size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_DP_CRT), p_config->p_operand_dp,
                       p_config->size_byte / 2UL);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_DQ_CRT), p_config->p_operand_dq,
                       p_config->size_byte / 2UL);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_QINV_CRT), p_config->p_operand_qinv,
                       p_config->size_byte / 2UL);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_PRIME_P), p_config->p_prime_p,
                       p_config->size_byte / 2UL);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_PRIME_Q), p_config->p_prime_q,
                       p_config->size_byte / 2UL);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_EXPONENT_BASE),
                       p_config->p_operand_a, p_config->size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the message signature configuration using RSA CRT exponentiation.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_rsa_signature_config_t  configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            RSA CRT exponentiation is successfully configured.
  */
hal_status_t HAL_PKA_RSA_SetConfigSignature(hal_pka_handle_t *hpka, const hal_pka_rsa_signature_config_t  *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_private_key != NULL);
  ASSERT_DBG_PARAM(p_config->p_hash != NULL);
  ASSERT_DBG_PARAM(p_config->private_key_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->hash_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_modulus == NULL) || (p_config->p_private_key == NULL) \
      || (p_config->p_hash == NULL) || (p_config->private_key_size_byte == 0U) || (p_config->hash_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_RSA_SIGNATURE);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_OP_NB_BITS)  = p_config->hash_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXP_NB_BITS) = p_config->private_key_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT_BASE), p_config->p_hash,
                       p_config->hash_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT), p_config->p_private_key,
                       p_config->private_key_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_MODULUS), p_config->p_modulus,
                       p_config->hash_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the configuration for verifying the validity of a signature using RSA CRT exponentiation.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_rsa_verif_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            The verification of signature validity is successfully configured.
  */
hal_status_t HAL_PKA_RSA_SetConfigVerifSignature(hal_pka_handle_t *hpka, const hal_pka_rsa_verif_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_public_key != NULL);
  ASSERT_DBG_PARAM(p_config->p_sign != NULL);
  ASSERT_DBG_PARAM(p_config->public_key_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->sign_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_modulus == NULL) || (p_config->p_public_key == NULL) \
      || (p_config->p_sign == NULL) || (p_config->public_key_size_byte == 0U) || (p_config->sign_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_RSA_VERIFICATION);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_OP_NB_BITS)  = p_config->sign_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXP_NB_BITS) = p_config->public_key_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT_BASE), p_config->p_sign,
                       p_config->sign_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_EXPONENT), p_config->p_public_key,
                       p_config->public_key_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_EXP_IN_MODULUS), p_config->p_modulus,
                       p_config->sign_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Arithmetic Addition Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_add_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Arithmetic Addition is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigAdd(hal_pka_handle_t *hpka, const hal_pka_add_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ARITHMETIC_ADD);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2, NULL);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Arithmetic subtraction Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_sub_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Arithmetic subtraction is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigSub(hal_pka_handle_t *hpka, const hal_pka_sub_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ARITHMETIC_SUB);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2, NULL);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set comparison Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_cmp_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Comparison is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigCmp(hal_pka_handle_t *hpka, const hal_pka_cmp_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_COMPARISON);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2, NULL);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Arithmetic multiplication Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mul_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Arithmetic multiplication is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigMul(hal_pka_handle_t *hpka, const hal_pka_mul_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ARITHMETIC_MUL);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2, NULL);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Modular Addition Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_add_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular Addition is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModAdd(hal_pka_handle_t *hpka, const hal_pka_mod_add_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_3 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->p_operand_3 == NULL) || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_ADD);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2,
                          p_config->p_operand_3);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Modular subtraction Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_sub_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular subtraction is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModSub(hal_pka_handle_t *hpka, const hal_pka_mod_sub_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_3 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->p_operand_3 == NULL) || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_SUB);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2,
                          p_config->p_operand_3);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Modular Inversion Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_inv_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular Inversion is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModInv(hal_pka_handle_t *hpka, const hal_pka_mod_inv_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand == NULL) || (p_config->p_modulus == NULL) \
      || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_INV);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_INV_NB_BITS) = p_config->size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_INV_IN_OP1), p_config->p_operand, p_config->size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_INV_IN_OP2_MOD), p_config->p_modulus,
                       p_config->size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the Modular Reduction configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_mod_red_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Modular reduction is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigModRed(hal_pka_handle_t *hpka, const hal_pka_mod_red_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->operand_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand == NULL) || (p_config->p_modulus == NULL) \
      || (p_config->operand_size_byte == 0U) || (p_config->modulus_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MODULAR_REDUC);

  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_REDUC_IN_OP_LENGTH)  = p_config->operand_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_REDUC_IN_MOD_LENGTH) = p_config->modulus_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_REDUC_IN_OPERAND), p_config->p_operand,
                       p_config->operand_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_REDUC_IN_MODULUS), p_config->p_modulus,
                       p_config->modulus_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Montgomery multiplication Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_montgomery_mul_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Montgomery multiplication is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigMontgomeryMul(hal_pka_handle_t *hpka, const hal_pka_montgomery_mul_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand_3 != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand_1 == NULL) || (p_config->p_operand_2 == NULL) \
      || (p_config->p_operand_3 == NULL) || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MONTGOMERY_MUL);

  PKA_SetConfigArithmetic(hpka, p_config->size_byte, p_config->p_operand_1, p_config->p_operand_2,
                          p_config->p_operand_3);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Montgomery parameter Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_montgomery_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Montgomery parameter is successfully configured.
  */
hal_status_t HAL_PKA_SetConfigMontgomery(hal_pka_handle_t *hpka, const hal_pka_montgomery_config_t *p_config)
{
  uint32_t byte_to_skip = 0UL;
  uint32_t new_size;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_operand != NULL);
  ASSERT_DBG_PARAM(p_config->size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_operand == NULL) || (p_config->size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_MONTGOMERY_PARAM);

  if (p_config->p_operand != NULL)
  {
    while ((byte_to_skip < p_config->size_byte) && (p_config->p_operand[byte_to_skip] == 0UL))
    {
      byte_to_skip++;
    }

    new_size = p_config->size_byte - byte_to_skip;

    PKA_RAM_WORD_ACCESS(hpka, PKA_MONTGOMERY_PARAM_IN_MOD_NB_BITS) =
      PKA_GetOptBitSize_u8(new_size, p_config->p_operand [byte_to_skip]);
    PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_MONTGOMERY_PARAM_IN_MODULUS), p_config->p_operand,
                         p_config->size_byte);
  }

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set Point on elliptic curve check configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_point_check_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            Point on elliptic curve check is successfully configured.
  */
hal_status_t HAL_PKA_ECC_SetConfigPointCheck(hal_pka_handle_t *hpka, const hal_pka_point_check_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_montgomery_param != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_a != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_b != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_config->p_pt_y != NULL);
  ASSERT_DBG_PARAM(p_config->coeff_sign != 0U);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_montgomery_param == NULL) || (p_config->p_coeff_a == NULL)   \
      || (p_config->p_coeff_b == NULL) || (p_config->p_modulus == NULL) || (p_config->p_pt_x == NULL) \
      || (p_config->p_pt_y == NULL) || (p_config->modulus_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_POINT_CHECK);

  PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_MOD_NB_BITS)  = PKA_GetOptBitSize_u8(p_config->modulus_size_byte,
                                                               *(p_config->p_modulus));
  PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_A_COEFF_SIGN) = p_config->coeff_sign;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_A_COEFF), p_config->p_coeff_a,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_B_COEFF), p_config->p_coeff_b,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_MOD_GF), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_INITIAL_POINT_X), p_config->p_pt_x,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_INITIAL_POINT_Y), p_config->p_pt_y,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_IN_MONTGOMERY_PARAM), p_config->p_montgomery_param,
                       p_config->modulus_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set the ECC scalar multiplication configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_ecc_mul_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            ECC scalar multiplication is successfully configured.
  */
hal_status_t HAL_PKA_ECC_SetConfigMul(hal_pka_handle_t *hpka, const hal_pka_ecc_mul_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_scalar_mul != NULL);
  ASSERT_DBG_PARAM(p_config->p_prime_order != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_a != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_b != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_config->p_pt_y != NULL);
  ASSERT_DBG_PARAM(p_config->coeff_sign != 0U);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->prime_order_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->scalar_mul_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_scalar_mul == NULL) || (p_config->p_prime_order == NULL)        \
      || (p_config->p_coeff_a == NULL) || (p_config->p_coeff_b == NULL) || (p_config->p_modulus == NULL) \
      || (p_config->p_pt_x == NULL) || (p_config->p_pt_y == NULL) || (p_config->modulus_size_byte == 0U) \
      || (p_config->prime_order_size_byte == 0U) || (p_config->scalar_mul_size_byte == 0U))              \
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ECC_MUL);

  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_EXP_NB_BITS)  = PKA_GetOptBitSize_u8(p_config->prime_order_size_byte,
                                                                  *(p_config->p_prime_order));
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_OP_NB_BITS)   = PKA_GetOptBitSize_u8(p_config->modulus_size_byte,
                                                                  *(p_config->p_modulus));
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_A_COEFF_SIGN) = p_config->coeff_sign;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_A_COEFF), p_config->p_coeff_a,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_B_COEFF), p_config->p_coeff_b,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_MOD_GF), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_K), p_config->p_scalar_mul,
                       p_config->scalar_mul_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_X), p_config->p_pt_x,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_INITIAL_POINT_Y), p_config->p_pt_y,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_SCALAR_MUL_IN_N_PRIME_ORDER), p_config->p_prime_order,
                       p_config->modulus_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_ECC_SCALAR_MUL_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set ECC double base ladder Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_ecc_double_base_ladder_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            ECC double base ladder is successfully configured.
  */
hal_status_t HAL_PKA_ECC_SetConfigDoubleBaseLadder(hal_pka_handle_t *hpka,
                                                   const hal_pka_ecc_double_base_ladder_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_a != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_integer_k != NULL);
  ASSERT_DBG_PARAM(p_config->p_integer_m != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_z_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_z_2 != NULL);
  ASSERT_DBG_PARAM(p_config->prime_order_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->coeff_sign != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_coeff_a == NULL) || (p_config->p_modulus == NULL)                             \
      || (p_config->p_integer_k == NULL) || (p_config->p_integer_m == NULL) || (p_config->p_base_pt_x_1 == NULL)       \
      || (p_config->p_base_pt_y_1 == NULL) || (p_config->p_base_pt_z_1 == NULL) || (p_config->p_base_pt_x_2 == NULL)   \
      || (p_config->p_base_pt_y_2 == NULL) || (p_config->p_base_pt_z_2 == NULL) || (p_config->modulus_size_byte == 0U) \
      || (p_config->prime_order_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_DOUBLE_BASE_LADDER);

  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_PRIME_ORDER_NB_BITS) = p_config->prime_order_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_MOD_NB_BITS)         = p_config->modulus_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_A_COEFF_SIGN)        = p_config->coeff_sign;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_A_COEFF), p_config->p_coeff_a,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_MOD_P), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_K_INTEGER), p_config->p_integer_k,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_M_INTEGER), p_config->p_integer_m,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_POINT1_X), p_config->p_base_pt_x_1,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_POINT1_Y), p_config->p_base_pt_y_1,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_POINT1_Z), p_config->p_base_pt_z_1,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_POINT2_X), p_config->p_base_pt_x_2,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_POINT2_Y), p_config->p_base_pt_y_2,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_POINT2_Z), p_config->p_base_pt_z_2,
                       p_config->modulus_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_ECC_DOUBLE_LADDER_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set ECC projective to affine Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_config          Pointer to @ref hal_pka_ecc_projective_to_affine_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            ECC projective to affine is successfully configured.
  */
hal_status_t HAL_PKA_ECC_SetConfigProjectiveToAffine(hal_pka_handle_t *hpka,
                                                     const hal_pka_ecc_projective_to_affine_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_z != NULL);
  ASSERT_DBG_PARAM(p_config->p_montgomery_param != NULL);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_modulus == NULL) || (p_config->p_base_pt_x == NULL)                          \
      || (p_config->p_base_pt_y == NULL) || (p_config->p_base_pt_z == NULL) || (p_config->p_montgomery_param == NULL) \
      || (p_config->modulus_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ECC_PROJECTIVE_AFF);

  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_PROJECTIVE_AFF_IN_MOD_NB_BITS) = p_config->modulus_size_byte * 8UL;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_PROJECTIVE_AFF_IN_MOD_P), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_PROJECTIVE_AFF_IN_POINT_X), p_config->p_base_pt_x,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_PROJECTIVE_AFF_IN_POINT_Y), p_config->p_base_pt_y,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_PROJECTIVE_AFF_IN_POINT_Z), p_config->p_base_pt_z,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_PROJECTIVE_AFF_IN_MONTGOMERY_PARAM_R2),
                       p_config->p_montgomery_param, p_config->modulus_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_ECC_PROJECTIVE_AFF_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Set ECC complete addition Configuration.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle..
  * @param  p_config          Pointer to @ref hal_pka_ecc_complete_add_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL.
  * @retval HAL_ERROR         PKA is not correctly initialized.
  * @retval HAL_OK            ECC complete addition is successfully configured.
  */
hal_status_t HAL_PKA_ECC_SetConfigCompleteAdd(hal_pka_handle_t *hpka, const hal_pka_ecc_complete_add_config_t *p_config)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_config->p_modulus != NULL);
  ASSERT_DBG_PARAM(p_config->p_coeff_a != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_z_1 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_x_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_y_2 != NULL);
  ASSERT_DBG_PARAM(p_config->p_base_pt_z_2 != NULL);
  ASSERT_DBG_PARAM(p_config->modulus_size_byte != 0U);
  ASSERT_DBG_PARAM(p_config->coeff_sign != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if ((p_config == NULL) || (p_config->p_modulus == NULL) || (p_config->p_coeff_a == NULL)                           \
      || (p_config->p_base_pt_x_1 == NULL) || (p_config->p_base_pt_y_1 == NULL) || (p_config->p_base_pt_z_1 == NULL) \
      || (p_config->p_base_pt_x_2 == NULL) || (p_config->p_base_pt_y_2 == NULL) || (p_config->p_base_pt_z_2 == NULL) \
      || (p_config->modulus_size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

  if (PKA_WaitInitOkUntilTimeout(hpka, 0UL, PKA_INITIALIZATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_PKA_SetMode(PKA_GET_INSTANCE(hpka), LL_PKA_MODE_ECC_COMPLETE_ADD);

  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_MOD_NB_BITS)   = p_config->modulus_size_byte * 8UL;
  PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_DOUBLE_LADDER_IN_A_COEFF_SIGN) = p_config->coeff_sign;
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_MOD_P), p_config->p_modulus,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_A_COEFF), p_config->p_coeff_a,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_POINT1_X), p_config->p_base_pt_x_1,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_POINT1_Y), p_config->p_base_pt_y_1,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_POINT1_Z), p_config->p_base_pt_z_1,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_POINT2_X), p_config->p_base_pt_x_2,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_POINT2_Y), p_config->p_base_pt_y_2,
                       p_config->modulus_size_byte);
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ECC_COMPLETE_ADD_IN_POINT2_Z), p_config->p_base_pt_z_2,
                       p_config->modulus_size_byte);

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = HAL_PKA_ERROR_NONE;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  hpka->operation    = PKA_OPERATION_NO_ERROR_OFFSET;
  hpka->global_state = HAL_PKA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group3
  * @{
This sub-section provides a set of functions allowing to manage the calculation data for an operation.

PKA calculating process functions

- Call the function HAL_PKA_Compute() to start the computation in blocking mode.
- Call the function HAL_PKA_Compute_IT() to start the computation in interrupt mode.

- Call the function HAL_PKA_IRQHandler() to handle PKA event interrupt request.
- Call the function HAL_PKA_Abort() to abort any ongoing operation.

PKA Modular exponentiation result functions

- Call the function HAL_PKA_GetResultModExp() to retrieve the result of the Modular exponentiation operation.
- Call the function HAL_PKA_GetResultModExpFast() to retrieve the result of the Modular exponentiation (Fast) operation.
- Call the function HAL_PKA_GetResultModExpProtected() to retrieve the result of the Modular exponentiation (Protected)
  operation.

  PKA arithmetic result functions

- Call the function HAL_PKA_GetResultAdd() to retrieve the result of the Addition operation.
- Call the function HAL_PKA_GetResultSub() to retrieve the result of the subtraction operation.
- Call the function HAL_PKA_GetResultMul() to retrieve the result of the multiplication operation.
- Call the function HAL_PKA_GetResultCmp() to retrieve the result of the comparison operation.
- Call the function HAL_PKA_GetResultModAdd() to retrieve the result of the Modular Addition operation.
- Call the function HAL_PKA_GetResultModSub() to retrieve the result of the Modular subtraction operation.
- Call the function HAL_PKA_GetResultModInv() to retrieve the result of the Modular Inversion operation.
- Call the function HAL_PKA_GetResultModRed() to retrieve the result of the Modular Reduction operation.
- Call the function HAL_PKA_GetResultMontgomeryMul() to retrieve the result of the Montgomery parameter operation.
- Call the function HAL_PKA_GetResultMontgomery() to retrieve the result of Montgomery parameter operation.

  PKA RSA result functions

- Call the function HAL_PKA_RSA_GetResultCRTExp() to retrieve the result of RSA CRT exponentiation operation.
- Call the function HAL_PKA_RSA_GetResultSignature() to retrieve the result of the RSA signature operation.
- Call the function HAL_PKA_RSA_IsValidVerifSignature() to check if the signature is verified or not.

  PKA ECDSA result functions

- Call the function HAL_PKA_ECDSA_GetResultSignature() to retrieve the result of elliptic curves over prime fields
  signature operation.
- Call the function HAL_PKA_ECDSA_IsValidVerifSignature() to check if the signature is verified or not.

  PKA ECC result functions

- Call the function HAL_PKA_ECC_IsPointCheckOnCurve() to check if the point is on curve or not.
- Call the function HAL_PKA_ECC_GetResultMul() to retrieve the result of ECC scalar multiplication operation.
- Call the function HAL_PKA_ECC_GetResultDoubleBaseLadder() to retrieve the result of ECC double base ladder operation.
- Call the function HAL_PKA_ECC_GetResultProjectiveToAffine() to retrieve the result of ECC projective to affine
  operation.
- Call the function HAL_PKA_ECC_GetResultCompleteAdd() to retrieve the result of ECC complete addition operation.

  */

/**
  * @brief  Generic function to start a PKA operation in blocking mode.
  * @param  hpka              PKA handle.
  * @param  timeout_ms        Timeout duration.
  * @retval HAL_INVALID_PARAM Invalid parameter return when hpka pointer or timeout_ms are NULL.
  * @retval HAL_TIMEOUT       In case of user timeout.
  * @retval HAL_ERROR         PKA error is occurred.
  * @retval HAL_BUSY          PKA state is active when calling this API.
  * @retval HAL_OK            Operation is successfully computed.
  */
hal_status_t HAL_PKA_Compute(hal_pka_handle_t *hpka, uint32_t timeout_ms)
{
  hal_status_t status = HAL_TIMEOUT;
  uint32_t tickstart  = HAL_GetTick();

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(timeout_ms != 0U);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_IDLE);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (timeout_ms == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hpka, global_state, HAL_PKA_STATE_IDLE, HAL_PKA_STATE_ACTIVE);

  /* Start the computation */
  LL_PKA_Start(PKA_GET_INSTANCE(hpka));
  while ((PKA_GET_INSTANCE(hpka)->SR & PKA_SR_PROCENDF) == 0UL)
  {
    if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0UL))
    {
      if ((PKA_GET_INSTANCE(hpka)->SR & PKA_SR_PROCENDF) == 0UL)
      {
        /* Abort any ongoing operation */
        LL_PKA_Disable(PKA_GET_INSTANCE(hpka));
        LL_PKA_Enable(PKA_GET_INSTANCE(hpka));

        hpka->global_state = HAL_PKA_STATE_INIT;

        return status;
      }
    }
  }

  LL_PKA_ClearFlag_PROCEND(PKA_GET_INSTANCE(hpka));

  status = PKA_CheckError(hpka, hpka->operation);

  hpka->global_state = HAL_PKA_STATE_INIT;

  return status;
}

/**
  * @brief  Generic function to start a PKA operation in non-blocking mode with interrupt.
  * @param  hpka              PKA handle.
  * @retval HAL_INVALID_PARAM Invalid parameter return when hpka pointer is NULL.
  * @retval HAL_BUSY          PKA state is active when calling this API.
  * @retval HAL_OK            Operation is successfully computed.
  */
hal_status_t HAL_PKA_Compute_IT(hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_IDLE);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hpka, global_state, HAL_PKA_STATE_IDLE, HAL_PKA_STATE_ACTIVE);

  LL_PKA_EnableIT(PKA_GET_INSTANCE(hpka), LL_PKA_IT_ALL);

  LL_PKA_Start(PKA_GET_INSTANCE(hpka));

  return HAL_OK;
}

/**
  * @brief  This function handles PKA event interrupt request.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  */
void HAL_PKA_IRQHandler(hal_pka_handle_t *hpka)
{
  uint32_t flag_status;

  ASSERT_DBG_PARAM(hpka != NULL);

  flag_status = LL_PKA_READ_REG(PKA_GET_INSTANCE(hpka), SR);

  if ((flag_status & LL_PKA_FLAG_PROCEND) != 0UL)
  {
    LL_PKA_ClearFlag_PROCEND(PKA_GET_INSTANCE(hpka));

    hpka->global_state = HAL_PKA_STATE_INIT;

#if defined (USE_HAL_PKA_REGISTER_CALLBACKS) && (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
    hpka->p_operation_cplt_cb(hpka);
#else
    HAL_PKA_OperationCpltCallback(hpka);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

    return;
  }

  if ((flag_status & LL_PKA_FLAG_ERROR_ALL) != 0UL)
  {
#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
    hpka->last_error_codes = flag_status & LL_PKA_FLAG_ERROR_ALL;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

    LL_PKA_ClearFlag(PKA_GET_INSTANCE(hpka), LL_PKA_FLAG_ERROR_ALL);

#if defined (USE_HAL_PKA_REGISTER_CALLBACKS) && (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
    hpka->p_error_cb(hpka);
#else
    HAL_PKA_ErrorCallback(hpka);
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Abort any ongoing operation.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval HAL_INVALID_PARAM Invalid parameter return when hpka pointer is NULL.
  * @retval HAL_OK            Operation is successfully aborted.
  */
hal_status_t HAL_PKA_Abort(hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  ASSERT_DBG_STATE(hpka->global_state, (uint32_t)HAL_PKA_STATE_IDLE | (uint32_t)HAL_PKA_STATE_ACTIVE);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  LL_PKA_Disable(PKA_GET_INSTANCE(hpka));

  LL_PKA_ClearFlag(PKA_GET_INSTANCE(hpka), LL_PKA_FLAG_ALL);

  hpka->global_state = HAL_PKA_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  Retrieve Modular exponentiation operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultModExp(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_EXP_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_EXP_OUT_RESULT * 4U], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Modular exponentiation (Fast) operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultModExpFast(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_EXP_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_EXP_OUT_RESULT * 4U], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Modular exponentiation (Protected) operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of result error or invalid parameter.
  */
uint32_t HAL_PKA_GetResultModExpProtected(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  if (PKA_CheckRAMError(hpka, PKA_OPERATION_MOD_EXP_PROT_ERROR_OFFSET) == HAL_PKA_ERROR_NONE)
  {
    size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_EXP_OUT_RESULT * 4UL, PKA_ROS_RESULT_MAX_SIZE);
    PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_EXP_OUT_RESULT * 4UL], size_byte);
  }

  return size_byte;
}

/**
  * @brief  Retrieve ECDSA signaure operation result.
  * @param  hpka         Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result     Pointer to @ref hal_pka_ecdsa_signature_result_t result structure.
  * @param  p_result_ext Pointer to @ref hal_pka_ecdsa_signature_result_ext_config_t structure (optional).
  * @retval size_byte    Size of result in byte.
  * @retval 0            In case of result error or invalid parameter.
  */
uint32_t HAL_PKA_ECDSA_GetResultSignature(hal_pka_handle_t *hpka, hal_pka_ecdsa_signature_result_t *p_result,
                                          hal_pka_ecdsa_signature_result_ext_config_t *p_result_ext)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(p_result->p_r_sign != NULL);
  ASSERT_DBG_PARAM(p_result->p_s_sign != NULL);
  ASSERT_DBG_PARAM(p_result_ext != NULL);
  ASSERT_DBG_PARAM(p_result_ext->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_result_ext->p_pt_y != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL)  || (p_result->p_r_sign == NULL) || (p_result->p_s_sign == NULL) \
      || (p_result_ext == NULL) || (p_result_ext->p_pt_x == NULL) || (p_result_ext->p_pt_y == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  if (PKA_CheckRAMError(hpka, PKA_OPERATION_ECDSA_SIGN_ERROR_OFFSET) == HAL_PKA_ERROR_NONE)
  {
    size_byte = PKA_GetResultSize(hpka, PKA_ECDSA_SIGN_OUT_SIGNATURE_R * 4U, PKA_EOS_RESULT_MAX_SIZE);
    PKA_Memcpy_u8_to_u8(p_result->p_r_sign, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECDSA_SIGN_OUT_SIGNATURE_R * 4UL],
                        size_byte);
    PKA_Memcpy_u8_to_u8(p_result->p_s_sign, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECDSA_SIGN_OUT_SIGNATURE_S * 4UL],
                        size_byte);
    PKA_Memcpy_u8_to_u8(p_result_ext->p_pt_x, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECDSA_SIGN_OUT_FINAL_POINT_X * 4UL],
                        size_byte);
    PKA_Memcpy_u8_to_u8(p_result_ext->p_pt_y, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECDSA_SIGN_OUT_FINAL_POINT_Y * 4UL],
                        size_byte);
  }

  return size_byte;
}

/**
  * @brief  Retrieve ECDSA verification signature result.
  * @param  hpka                          Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval PKA_ECDSA_SIGNATURE_VALID     Signature validated.
  * @retval PKA_ECDSA_SIGNATURE_NOT_VALID In case of signature not validated or invalid parameter.
  */
hal_pka_ecdsa_signature_status_t HAL_PKA_ECDSA_IsValidVerifSignature(const hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return PKA_ECDSA_SIGNATURE_NOT_VALID;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  return (PKA_RAM_WORD_ACCESS(hpka, PKA_ECDSA_VERIF_OUT_RESULT) != PKA_OPERATION_ERROR_NONE) ?
         PKA_ECDSA_SIGNATURE_NOT_VALID : PKA_ECDSA_SIGNATURE_VALID;
}

/**
  * @brief  Retrieve RSA CRT exponentiation operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_RSA_GetResultCRTExp(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_EXP_OUT_RESULT * 4UL,
                                (PKA_RAM_WORD_ACCESS(hpka, PKA_RSA_CRT_EXP_IN_MOD_NB_BITS) / 8U) + 1U);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_RSA_CRT_EXP_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve RSA signature operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_RSA_GetResultSignature(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_EXP_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_EXP_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve RSA verification signature result.
  * @param  hpka                        Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_hash                      Pointer to hashed message provided by the user.
  * @retval PKA_RSA_SIGNATURE_VALID     Signature validated.
  * @retval PKA_RSA_SIGNATURE_NOT_VALID In case of signature not validated or invalid parameter.
  */
hal_pka_rsa_signature_status_t HAL_PKA_RSA_IsValidVerifSignature(hal_pka_handle_t *hpka, const uint8_t *p_hash)
{
  uint32_t size_byte;
  uint32_t index;
  uint8_t  p_result[PKA_ROS_RESULT_MAX_SIZE * 8U] = {0};

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_hash != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_hash == NULL))
  {
    return PKA_RSA_SIGNATURE_NOT_VALID;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_EXP_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_EXP_OUT_RESULT * 4UL], size_byte);

  for (index = 0; index < size_byte; index++)
  {
    if (p_result[index] != p_hash[index])
    {
      return PKA_RSA_SIGNATURE_NOT_VALID;
    }
  }

  return PKA_RSA_SIGNATURE_VALID;
}

/**
  * @brief  Retrieve Addition operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultAdd(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL, (PKA_ROS_RESULT_MAX_SIZE + 1U));
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve subtraction operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultSub(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve multiplication operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultMul(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4U, (PKA_ROS_RESULT_MAX_SIZE * 2U));
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve comparison operation result.
  * @param  hpka                Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result            Pointer to operation result.
  * @retval PKA_CMP_RESULT_SIZE Size of the comparison result in byte.
  * @retval 0                   In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultCmp(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return 0;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL],
                      PKA_CMP_RESULT_SIZE);

  return PKA_CMP_RESULT_SIZE;
}

/**
  * @brief  Retrieve Modular Addition operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultModAdd(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Modular subtraction operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultModSub(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ARITHMETIC_ALL_OPS_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Modular Reduction operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultModRed(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_REDUC_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_REDUC_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Modular Inversion operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultModInv(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MODULAR_INV_OUT_RESULT * 4UL,
                                (PKA_RAM_WORD_ACCESS(hpka, PKA_MODULAR_INV_NB_BITS) / 8U) + 1U);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MODULAR_INV_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Montgomery multiplication operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultMontgomeryMul(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MONTGOMERY_MUL_OUT_RESULT * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MONTGOMERY_MUL_OUT_RESULT * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Montgomery parameter operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to operation result.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_GetResultMontgomery(hal_pka_handle_t *hpka, uint8_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_MONTGOMERY_PARAM_OUT_PARAMETER * 4U, PKA_ROS_RESULT_MAX_SIZE);
  PKA_Memcpy_u8_to_u8(p_result, &PKA_GET_INSTANCE(hpka)->RAM[PKA_MONTGOMERY_PARAM_OUT_PARAMETER * 4UL], size_byte);

  return size_byte;
}

/**
  * @brief  Retrieve Point on elliptic curve check operation result.
  * @param  hpka                       Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval PKA_ECC_POINT_ON_CURVE     ECC point is on curve.
  * @retval PKA_ECC_POINT_NOT_ON_CURVE In case of ECC point is not on curve or invalid parameter.
  */
hal_pka_ecc_point_status_t HAL_PKA_ECC_IsPointCheckOnCurve(const hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return PKA_ECC_POINT_NOT_ON_CURVE;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  return (PKA_RAM_WORD_ACCESS(hpka, PKA_POINT_CHECK_OUT_ERROR) != PKA_OPERATION_ERROR_NONE) ?
         PKA_ECC_POINT_NOT_ON_CURVE : PKA_ECC_POINT_ON_CURVE;
}

/**
  * @brief  Retrieve ECC scalar multiplication operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to @ref hal_pka_ecc_mul_result_t result structure.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of result error or invalid parameter.
  */
uint32_t HAL_PKA_ECC_GetResultMul(hal_pka_handle_t *hpka, hal_pka_ecc_mul_result_t *p_result)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_y != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL) || (p_result->p_pt_x == NULL) || (p_result->p_pt_y == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  if (PKA_CheckRAMError(hpka, PKA_OPERATION_ECC_SCALAR_MUL_ERROR_OFFSET) == HAL_PKA_ERROR_NONE)
  {
    size_byte = PKA_GetResultSize(hpka, PKA_ECC_SCALAR_MUL_OUT_RESULT_X * 4U, PKA_EOS_RESULT_MAX_SIZE);
    PKA_Memcpy_u8_to_u8(p_result->p_pt_x, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_X * 4UL],
                        size_byte);
    PKA_Memcpy_u8_to_u8(p_result->p_pt_y, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_SCALAR_MUL_OUT_RESULT_Y * 4UL],
                        size_byte);
  }

  return size_byte;
}

/**
  * @brief  Retrieve ECC double base ladder operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to @ref hal_pka_ecc_double_base_ladder_result_t result structure.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of result error or invalid parameter.
  */
uint32_t HAL_PKA_ECC_GetResultDoubleBaseLadder(hal_pka_handle_t *hpka,
                                               hal_pka_ecc_double_base_ladder_result_t *p_result)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_y != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL) || (p_result->p_pt_x == NULL) || (p_result->p_pt_y == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  if (PKA_CheckRAMError(hpka, PKA_OPERATION_ECC_DOUBLE_LADDER_ERROR_OFFSET) == HAL_PKA_ERROR_NONE)
  {
    size_byte = PKA_GetResultSize(hpka, PKA_ECC_DOUBLE_LADDER_OUT_RESULT_X * 4U, PKA_EOS_RESULT_MAX_SIZE);
    PKA_Memcpy_u8_to_u8(p_result->p_pt_x, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_DOUBLE_LADDER_OUT_RESULT_X * 4UL],
                        size_byte);
    PKA_Memcpy_u8_to_u8(p_result->p_pt_y, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_DOUBLE_LADDER_OUT_RESULT_Y * 4UL],
                        size_byte);
  }

  return size_byte;
}

/**
  * @brief  Retrieve ECC projective to affine operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to @ref hal_pka_ecc_projective_to_affine_result_t result structure.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of result error or invalid parameter.
  */
uint32_t HAL_PKA_ECC_GetResultProjectiveToAffine(hal_pka_handle_t *hpka,
                                                 hal_pka_ecc_projective_to_affine_result_t *p_result)
{
  uint32_t size_byte = 0U;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_y != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL) || (p_result->p_pt_x == NULL) || (p_result->p_pt_y == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  if (PKA_CheckRAMError(hpka, PKA_OPERATION_ECC_PROJECTIVE_AFF_ERROR_OFFSET) == HAL_PKA_ERROR_NONE)
  {
    size_byte = PKA_GetResultSize(hpka, PKA_ECC_PROJECTIVE_AFF_OUT_RESULT_X * 4U, PKA_EOS_RESULT_MAX_SIZE);
    PKA_Memcpy_u8_to_u8(p_result->p_pt_x, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_PROJECTIVE_AFF_OUT_RESULT_X * 4UL],
                        size_byte);
    PKA_Memcpy_u8_to_u8(p_result->p_pt_y, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_PROJECTIVE_AFF_OUT_RESULT_Y * 4UL],
                        size_byte);
  }

  return size_byte;
}

/**
  * @brief  Retrieve ECC complete addition operation result.
  * @param  hpka      Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_result  Pointer to @ref hal_pka_ecc_complete_add_result_t result structure.
  * @retval size_byte Size of result in byte.
  * @retval 0         In case of invalid parameter.
  */
uint32_t HAL_PKA_ECC_GetResultCompleteAdd(hal_pka_handle_t *hpka, hal_pka_ecc_complete_add_result_t *p_result)
{
  uint32_t size_byte = 0;

  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_x != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_y != NULL);
  ASSERT_DBG_PARAM(p_result->p_pt_z != NULL);

  ASSERT_DBG_STATE(hpka->global_state, HAL_PKA_STATE_INIT);

#if defined (USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if ((hpka == NULL) || (p_result == NULL) || (p_result->p_pt_x == NULL) || (p_result->p_pt_y == NULL) \
      || (p_result->p_pt_z == NULL))
  {
    return size_byte;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  size_byte = PKA_GetResultSize(hpka, PKA_ECC_COMPLETE_ADD_OUT_RESULT_X * 4U, PKA_EOS_RESULT_MAX_SIZE);

  PKA_Memcpy_u8_to_u8(p_result->p_pt_x, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_COMPLETE_ADD_OUT_RESULT_X * 4UL],
                      size_byte);
  PKA_Memcpy_u8_to_u8(p_result->p_pt_y, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_COMPLETE_ADD_OUT_RESULT_Y * 4UL],
                      size_byte);
  PKA_Memcpy_u8_to_u8(p_result->p_pt_z, &PKA_GET_INSTANCE(hpka)->RAM[PKA_ECC_COMPLETE_ADD_OUT_RESULT_Z * 4UL],
                      size_byte);

  return size_byte;
}

/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group4
  * @{
This sub-section provides a set of callback functions allowing to register the PKA operation and error callbacks:

- The HAL_PKA_OperationCpltCallback() function is called when the process is complete
- The HAL_PKA_ErrorCallback() function is called in case of an error
- Call the function HAL_PKA_RegisterOperationCpltCallback() to register the PKA operation complete callback.
- Call the function HAL_PKA_RegisterErrorCallback() to register the PKA error callback.

  */

/**
  * @brief  Process completed callback.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  */
__WEAK void HAL_PKA_OperationCpltCallback(hal_pka_handle_t *hpka)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpka);

  /* NOTE : This function must not be modified. When the callback is needed,
            the HAL_PKA_OperationCpltCallback must be implemented in the user file */
}

/**
  * @brief  Error callback.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  */
__WEAK void HAL_PKA_ErrorCallback(hal_pka_handle_t *hpka)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hpka);

  /* NOTE : This function must not be modified. When the callback is needed,
            the HAL_PKA_ErrorCallback must be implemented in the user file */
}

#if defined (USE_HAL_PKA_REGISTER_CALLBACKS) && (USE_HAL_PKA_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the PKA command complete Callback TO be used instead of
  *         the weak HAL_PKA_OperCpltCallback() predefined callback.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_callback        Pointer to @ref hal_pka_cb_t Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_PKA_RegisterOperationCpltCallback(hal_pka_handle_t *hpka, hal_pka_cb_t  p_callback)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  hpka->p_operation_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the PKA Error Callback to be used instead of
  *         the weak HAL_PKA_ErrorCallback() predefined callback.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_callback        Pointer to @ref hal_pka_cb_t Callback function.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_PKA_RegisterErrorCallback(hal_pka_handle_t *hpka, hal_pka_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hpka != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)) \
  || (defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1))
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM or USE_HAL_SECURE_CHECK_PARAM */
#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  hpka->p_error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_PKA_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group5
  * @{
This sub-section provides a set of functions allowing to get the PKA state, error code, and data information :

- Call the function HAL_PKA_GetState() to get the PKA current state
- Call the function HAL_PKA_GetLastErrorCodes() to get the PKA last hardware or software error codes
- Call the function HAL_PKA_SetUserData() to set the PKA user data
- Call the function HAL_PKA_GetUserData() to get the PKA user data

  */

/**
  * @brief  Retrieve the PKA global state.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval hal_pka_state_t PKA state
  */
hal_pka_state_t HAL_PKA_GetState(const hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  return hpka->global_state;
}

#if defined (USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
/**
  * @brief  Retrieve the PKA error code.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval PKA error code.
  */
uint32_t HAL_PKA_GetLastErrorCodes(const hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  return hpka->last_error_codes;
}
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

#if defined(USE_HAL_PKA_USER_DATA) && (USE_HAL_PKA_USER_DATA == 1)
/**
  * @brief  Store the user data into the pka handle
  * @param  hpka        Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_PKA_SetUserData(hal_pka_handle_t *hpka, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  hpka->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the pka handle
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval Pointer to the user data.
  */
const void *HAL_PKA_GetUserData(const hal_pka_handle_t *hpka)
{
  ASSERT_DBG_PARAM(hpka != NULL);

  return (hpka->p_user_data);
}
#endif /* USE_HAL_PKA_USER_DATA */
/**
  * @}
  */

/** @addtogroup PKA_Exported_Functions_Group6
  * @{
This sub-section provides a function called HAL_PKA_RAMMassErase() allowing to erase the content of the PKA RAM.

  */

/**
  * @brief  Erase the content of PKA RAM.
  * @param  hpka              Pointer to @ref hal_pka_handle_t PKA handle.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            The content of PKA RAM is fully and successfully erased.
  */
hal_status_t HAL_PKA_RAMMassErase(hal_pka_handle_t *hpka)
{
  uint32_t index;

  ASSERT_DBG_PARAM(hpka != NULL);

  ASSERT_DBG_STATE(hpka->global_state, (uint32_t)HAL_PKA_STATE_INIT | (uint32_t)HAL_PKA_STATE_IDLE);

#if defined(USE_HAL_SECURE_CHECK_PARAM) && (USE_HAL_SECURE_CHECK_PARAM == 1)
  if (hpka == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_SECURE_CHECK_PARAM */

  for (index = 0; index < PKA_RAM_SIZE; index++)
  {
    PKA_RAM_WORD_ACCESS(hpka, index) = 0UL;
  }

  hpka->global_state = HAL_PKA_STATE_INIT;

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup PKA_Private_Functions
  * @{
  */

/**
  * @brief  Set Arithmetic Configuration.
  * @param  hpka        Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  size_byte   Size of the operand in byte.
  * @param  p_operand_1 Generic pointer to input data.
  * @param  p_operand_2 Generic pointer to input data.
  * @param  p_operand_3 Generic pointer to input data.
  */
static void PKA_SetConfigArithmetic(hal_pka_handle_t *hpka, const uint32_t size_byte, const uint8_t *p_operand_1,
                                    const uint8_t *p_operand_2, const uint8_t *p_operand_3)
{
  /* Get the number of bit per operand */
  PKA_RAM_WORD_ACCESS(hpka, PKA_ARITHMETIC_ALL_OPS_NB_BITS)  = size_byte * 8UL;

  /* Set operand 1 */
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ARITHMETIC_ALL_OPS_IN_OP1), p_operand_1, size_byte);

  /* Set operand 2 */
  PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ARITHMETIC_ALL_OPS_IN_OP2), p_operand_2, size_byte);

  /* Set operand 3 when operand is not null */
  if (p_operand_3 != NULL)
  {
    PKA_Memcpy_u8_to_u32(&PKA_RAM_WORD_ACCESS(hpka, PKA_ARITHMETIC_ALL_OPS_IN_OP3), p_operand_3, size_byte);
  }
}

/**
  * @brief  PKA operation result error.
  * @param  hpka                 Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  operation            PKA operating mode.
  * @retval HAL_PKA_ERROR_RESULT A result error has occurred in the calculation of the PKA operation.
  * @retval HAL_PKA_ERROR_NONE   No error in calculating PKA operation.
  */
static uint32_t PKA_CheckRAMError(hal_pka_handle_t *hpka, uint32_t operation)
{
  uint32_t error = HAL_PKA_ERROR_RESULT;

  if ((uint32_t)PKA_RAM_WORD_ACCESS(hpka, operation) == PKA_OPERATION_ERROR_NONE)
  {
    error = HAL_PKA_ERROR_NONE;
  }

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = error;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  return error;
}

/**
  * @brief  Check the PKA error flags and the computation error for the selected operation.
  * @param  hpka Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  operation PKA operating mode.
  * @retval HAL_ERROR PKA error is occurred.
  * @retval HAL_OK    No PKA errors occurred.
  */
static hal_status_t PKA_CheckError(hal_pka_handle_t *hpka, uint32_t operation)
{
  hal_status_t status = HAL_ERROR;
  uint32_t     error;

  error = (LL_PKA_READ_REG(PKA_GET_INSTANCE(hpka), SR) & LL_PKA_FLAG_ERROR_ALL);
  if (operation != PKA_OPERATION_NO_ERROR_OFFSET)
  {
    error |= PKA_CheckRAMError(hpka, operation);
  }

#if defined(USE_HAL_PKA_GET_LAST_ERRORS) && (USE_HAL_PKA_GET_LAST_ERRORS == 1)
  hpka->last_error_codes = error;
#endif /* USE_HAL_PKA_GET_LAST_ERRORS */

  LL_PKA_ClearFlag(PKA_GET_INSTANCE(hpka), LL_PKA_FLAG_ERROR_ALL);

  if (error == HAL_PKA_ERROR_NONE)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Get optimal number of bits inside an array of bytes.
  * @param  nbr_byte Number of bytes inside the array.
  * @param  msb      Most significant uint8_t of the array.
  */
static uint32_t PKA_GetOptBitSize_u8(uint32_t nbr_byte, uint8_t msb)
{
  uint32_t position;

  position = 32UL - __CLZ(msb);

  return (((nbr_byte - 1UL) * 8UL) + position);
}

/**
  * @brief  Copy uint8_t array to uint32_t array to fit PKA number representation.
  * @param  p_dst    Pointer to destination.
  * @param  p_src    Pointer to source.
  * @param  nbr_byte Number of uint8_t to copy (must be multiple of 4).
  */
static void PKA_Memcpy_u8_to_u32(volatile uint32_t *p_dst, const uint8_t *p_src, size_t nbr_byte)
{
  uint32_t index = 0UL;

  for (; index < (nbr_byte / 4UL); index++)
  {
    /* Apply the equivalent of __REV from uint8_t to uint32_t */
    p_dst[index] = ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 1UL)])           \
                   | ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 2UL)] << 8UL)  \
                   | ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 3UL)] << 16UL) \
                   | ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 4UL)] << 24UL);
  }

  /* Manage the buffers not aligned on uint32_t */
  if ((nbr_byte % 4UL) == 1UL)
  {
    p_dst[index] = (uint32_t)p_src[(nbr_byte - (index * 4UL) - 1UL)];
  }
  else if ((nbr_byte % 4UL) == 2UL)
  {
    p_dst[index] = ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 1UL)]) \
                   | ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 2UL)] << 8UL);
  }
  else if ((nbr_byte % 4UL) == 3UL)
  {
    p_dst[index] = ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 1UL)])          \
                   | ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 2UL)] << 8UL) \
                   | ((uint32_t)p_src[(nbr_byte - (index * 4UL) - 3UL)] << 16UL);
  }
  else
  {
    /* The last element is already handle in the loop */
  }

  p_dst[index + (nbr_byte % 4UL)]      = 0UL;
  p_dst[index + (nbr_byte % 4UL) + 1U] = 0UL;
}

/**
  * @brief  Copy uint8_t array to uint8_t array.
  * @param  p_dst    Pointer to destination.
  * @param  p_src    Pointer to source.
  * @param  nbr_byte Number of bytes to be handled.
  */
static void PKA_Memcpy_u8_to_u8(volatile uint8_t *p_dst, volatile const uint8_t *p_src, size_t nbr_byte)
{
  for (uint32_t index = nbr_byte; index > 0U; index--)
  {
    p_dst[nbr_byte - index] = p_src[index - 1U];
  }
}

/**
  * @brief  Wait for a flag state until timeout.
  * @param  hpka        Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  flag_state  Flag state (SET or RESET).
  * @param  timeout_ms  Timeout duration.
  * @retval HAL_TIMEOUT In case of user timeout.
  * @retval HAL_OK      Flag is correctly set.
  */
static hal_status_t PKA_WaitInitOkUntilTimeout(hal_pka_handle_t *hpka, uint32_t flag_state, uint32_t timeout_ms)
{
  uint32_t tickstart = HAL_GetTick();
  while (LL_PKA_IsActiveFlag_INITOK(PKA_GET_INSTANCE(hpka)) == flag_state)
  {
    if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the size of result.
  * @param  hpka        Pointer to @ref hal_pka_handle_t PKA handle.
  * @param  start_index Specify the start index of the result in the PKA RAM.
  * @param  max_size    Specify the possible max size of the result in words.
  */
static uint32_t PKA_GetResultSize(const hal_pka_handle_t *hpka, uint32_t start_index, uint32_t max_size)
{
  uint32_t current_index = max_size;

  while ((PKA_GET_INSTANCE(hpka)->RAM[start_index + current_index] == 0UL) && (current_index != 0UL))
  {
    current_index--;
  }

  return current_index + 1U;
}

/**
  * @}
  */

#endif /* USE_HAL_PKA_MODULE */

/**
  * @}
  */

/**
  * @}
  */
#endif /* PKA */
