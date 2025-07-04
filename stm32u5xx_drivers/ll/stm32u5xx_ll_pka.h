/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_pka.h
  * @brief   Header file of PKA LL module.
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
 @verbatim
  ======================================================================================================================
                      --------- LL PKA driver acronyms ---------
  ======================================================================================================================
  [..]  Acronyms table :
                   ========================================================
                   | Acronym |                                            |
                   ========================================================
                   | RSA     | Rivest Shamir Adleman                      |
                   | ECDSA   | Elliptic Curve Digital Signature Algorithm |
                   | ECC     | Elliptic curve cryptography                |
                   | CRT     | Chinese Remainder Theorem                  |
                   | Mod     | Modular                                    |
                   | Exp     | Exponentiation                             |
                   | Mul     | Multiplication                             |
                   | Add     | Addition                                   |
                   | Sub     | Subtraction                                |
                   | Cmp     | Comparison                                 |
                   | Inv     | Inversion                                  |
                   | Red     | Reduction                                  |
                   | Sign    | Signature                                  |
                   | Verif   | Verification                               |
                   ========================================================
 @endverbatim
  **********************************************************************************************************************
  */
/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_LL_PKA_H
#define STM32U5XX_LL_PKA_H
#ifdef __cplusplus
extern "C" {
#endif
/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"
#if defined(PKA)
/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */
/** @defgroup PKA_LL PKA
  * @{
  */
/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Constants PKA Exported Constants
  * @{
  */
/** @defgroup PKA_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PKA_ReadReg function
  * @{
  */
#define LL_PKA_FLAG_ADDRERR   PKA_SR_ADDRERRF                               /*!< Address error flag                 */
#define LL_PKA_FLAG_RAMERR    PKA_SR_RAMERRF                                /*!< RAM error flag                     */
#define LL_PKA_FLAG_PROCEND   PKA_SR_PROCENDF                               /*!< End of process flag                */
#define LL_PKA_FLAG_BUSY      PKA_SR_BUSY                                   /*!< Busy flag                          */
#define LL_PKA_FLAG_INITOK    PKA_SR_INITOK                                 /*!< Init OK flag                       */
#define LL_PKA_FLAG_OPERR     PKA_SR_OPERRF                                 /*!< Operation error flag               */
#define LL_PKA_FLAG_ALL       (PKA_SR_ADDRERRF | PKA_SR_RAMERRF \
                               | PKA_SR_PROCENDF | PKA_SR_OPERRF)           /*!< All flags                          */
#define LL_PKA_FLAG_ERROR_ALL (PKA_SR_ADDRERRF | PKA_SR_RAMERRF \
                               | PKA_SR_OPERRF)                             /*!< All error flags                    */
/**
  * @}
  */
/** @defgroup PKA_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_PKA_ReadReg and  LL_PKA_WriteReg functions
  * @{
  */
#define LL_PKA_IT_ADDRERR PKA_CR_ADDRERRIE                                 /*!< Address error interrupt            */
#define LL_PKA_IT_RAMERR  PKA_CR_RAMERRIE                                  /*!< RAM error interrupt                */
#define LL_PKA_IT_PROCEND PKA_CR_PROCENDIE                                 /*!< End of process interrupt           */
#define LL_PKA_IT_OPERR   PKA_CR_OPERRIE                                   /*!< Operation error interrupt          */
#define LL_PKA_IT_ALL (PKA_CR_ADDRERRIE | PKA_CR_RAMERRIE  \
                       | PKA_CR_PROCENDIE  | PKA_CR_OPERRIE)               /*!< All interrupts                     */
/**
  * @}
  */
/** @defgroup PKA_LL_EC_MODE Operation Mode
  * @brief    List of operation mode.
  * @{
  */
#define LL_PKA_MODE_MODULAR_EXP         (0x00000000U) /*!< modular exponentiation              */
#define LL_PKA_MODE_MONTGOMERY_PARAM    (0x00000001U) /*!< Compute Montgomery parameter only   */
#define LL_PKA_MODE_MODULAR_EXP_FAST    (0x00000002U) /*!< modular exponentiation fast mode    */
#define LL_PKA_MODE_MODULAR_EXP_PROTECT (0x00000003U) /*!< modular exponentiation protect mode */
#define LL_PKA_MODE_ECC_MUL             (0x00000020U) /*!< compute ECC kP operation            */
#define LL_PKA_MODE_ECC_COMPLETE_ADD    (0x00000023U) /*!< ECC complete addition               */
#define LL_PKA_MODE_ECDSA_SIGNATURE     (0x00000024U) /*!< ECDSA signature                     */
#define LL_PKA_MODE_ECDSA_VERIFICATION  (0x00000026U) /*!< ECDSA verification                  */
#define LL_PKA_MODE_POINT_CHECK         (0x00000028U) /*!< Point check                         */
#define LL_PKA_MODE_RSA_CRT_EXP         (0x00000007U) /*!< RSA CRT exponentiation              */
#define LL_PKA_MODE_MODULAR_INV         (0x00000008U) /*!< Modular inversion                   */
#define LL_PKA_MODE_ARITHMETIC_ADD      (0x00000009U) /*!< Arithmetic addition                 */
#define LL_PKA_MODE_ARITHMETIC_SUB      (0x0000000AU) /*!< Arithmetic subtraction              */
#define LL_PKA_MODE_ARITHMETIC_MUL      (0x0000000BU) /*!< Arithmetic multiplication           */
#define LL_PKA_MODE_COMPARISON          (0x0000000CU) /*!< Comparison                          */
#define LL_PKA_MODE_MODULAR_REDUC       (0x0000000DU) /*!< Modular reduction                   */
#define LL_PKA_MODE_MODULAR_ADD         (0x0000000EU) /*!< Modular addition                    */
#define LL_PKA_MODE_MODULAR_SUB         (0x0000000FU) /*!< Modular subtraction                 */
#define LL_PKA_MODE_MONTGOMERY_MUL      (0x00000010U) /*!< Montgomery multiplication           */
#define LL_PKA_MODE_DOUBLE_BASE_LADDER  (0x00000027U) /*!< Double base ladder                  */
#define LL_PKA_MODE_ECC_PROJECTIVE_AFF  (0x0000002FU) /*!< ECC projective to affine            */
#define LL_PKA_MODE_RSA_SIGNATURE       (0x00000000U) /*!< RSA signature                       */
#define LL_PKA_MODE_RSA_VERIFICATION    (0x00000000U) /*!< RSA verification                    */
/**
  * @}
  */
/**
  * @}
  */
/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Macros PKA Exported Macros
  * @{
  */
/** @defgroup PKA_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */
/**
  * @brief  Write a value in PKA register
  * @param  instance PKA Instance
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_PKA_WRITE_REG(instance, reg, value) WRITE_REG(((instance)->reg), (value))
/**
  * @brief  Read a value in PKA register
  * @param  instance PKA Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_PKA_READ_REG(instance, reg) READ_REG(((instance)->reg))
/**
  * @}
  */
/**
  * @}
  */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup PKA_LL_Exported_Functions PKA Exported Functions
  * @{
  */
/** @defgroup PKA_LL_EF_Configuration Configuration
  * @{
  */
/**
  * @brief  Enable PKA peripheral.
  * @rmtoll
  *  CR           EN            LL_PKA_Enable
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_Enable(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CR, PKA_CR_EN);
}
/**
  * @brief  Disable PKA peripheral.
  * @rmtoll
  *  CR           EN            LL_PKA_Disable
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_Disable(PKA_TypeDef *pkax)
{
  CLEAR_BIT(pkax->CR, PKA_CR_EN);
}
/**
  * @brief  Check if the PKA peripheral is enabled or disabled.
  * @rmtoll
  *  CR           EN            LL_PKA_IsEnabled
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabled(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->CR, PKA_CR_EN) == (PKA_CR_EN)) ? 1UL : 0UL);
}
/**
  * @brief  Set PKA operating mode.
  * @rmtoll
  *  CR           MODE          LL_PKA_SetMode
  * @param  pkax PKA Instance.
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP
  *         @arg @ref LL_PKA_MODE_ECDSA_SIGNATURE
  *         @arg @ref LL_PKA_MODE_ECDSA_VERIFICATION
  *         @arg @ref LL_PKA_MODE_POINT_CHECK
  *         @arg @ref LL_PKA_MODE_RSA_CRT_EXP
  *         @arg @ref LL_PKA_MODE_MODULAR_INV
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_ADD
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_SUB
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_MUL
  *         @arg @ref LL_PKA_MODE_COMPARISON
  *         @arg @ref LL_PKA_MODE_MODULAR_REDUC
  *         @arg @ref LL_PKA_MODE_MODULAR_ADD
  *         @arg @ref LL_PKA_MODE_MODULAR_SUB
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_MUL
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP_PROTECT
  *         @arg @ref LL_PKA_MODE_DOUBLE_BASE_LADDER
  *         @arg @ref LL_PKA_MODE_ECC_PROJECTIVE_AFF
  *         @arg @ref LL_PKA_MODE_ECC_COMPLETE_ADD
  *         @arg @ref LL_PKA_MODE_ECC_MUL
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP_FAST
  */
__STATIC_INLINE void LL_PKA_SetMode(PKA_TypeDef *pkax, uint32_t mode)
{
  MODIFY_REG(pkax->CR, (PKA_CR_MODE), (mode << PKA_CR_MODE_Pos));
}
/**
  * @brief  Get PKA operating mode.
  * @rmtoll
  *  CR           MODE          LL_PKA_GetMode
  * @param  pkax PKA Instance.
  * @retval returned value can be one of the following values:
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_PARAM
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP
  *         @arg @ref LL_PKA_MODE_ECDSA_SIGNATURE
  *         @arg @ref LL_PKA_MODE_ECDSA_VERIFICATION
  *         @arg @ref LL_PKA_MODE_POINT_CHECK
  *         @arg @ref LL_PKA_MODE_RSA_CRT_EXP
  *         @arg @ref LL_PKA_MODE_MODULAR_INV
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_ADD
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_SUB
  *         @arg @ref LL_PKA_MODE_ARITHMETIC_MUL
  *         @arg @ref LL_PKA_MODE_COMPARISON
  *         @arg @ref LL_PKA_MODE_MODULAR_REDUC
  *         @arg @ref LL_PKA_MODE_MODULAR_ADD
  *         @arg @ref LL_PKA_MODE_MODULAR_SUB
  *         @arg @ref LL_PKA_MODE_MONTGOMERY_MUL
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP_PROTECT
  *         @arg @ref LL_PKA_MODE_DOUBLE_BASE_LADDER
  *         @arg @ref LL_PKA_MODE_ECC_PROJECTIVE_AFF
  *         @arg @ref LL_PKA_MODE_ECC_COMPLETE_ADD
  *         @arg @ref LL_PKA_MODE_ECC_MUL
  *         @arg @ref LL_PKA_MODE_MODULAR_EXP_FAST
  */
__STATIC_INLINE uint32_t LL_PKA_GetMode(const PKA_TypeDef *pkax)
{
  return (uint32_t)(READ_BIT(pkax->CR, PKA_CR_MODE) >> PKA_CR_MODE_Pos);
}
/**
  * @brief  Start the operation selected using LL_PKA_SetMode.
  * @rmtoll
  *  CR           START         LL_PKA_Start
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_Start(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CR, PKA_CR_START);
}
/**
  * @}
  */
/** @defgroup PKA_LL_EF_IT_Management IT_Management
  * @{
  */
/**
  * @brief  Enable address error interrupt.
  * @rmtoll
  *  CR           ADDRERRIE     LL_PKA_EnableIT_ADDRERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_EnableIT_ADDRERR(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CR, PKA_CR_ADDRERRIE);
}
/**
  * @brief  Enable RAM error interrupt.
  * @rmtoll
  *  CR           RAMERRIE      LL_PKA_EnableIT_RAMERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_EnableIT_RAMERR(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CR, PKA_CR_RAMERRIE);
}
/**
  * @brief  Enable OPERATION error interrupt.
  * @rmtoll
  *  CR           OPERRIE      LL_PKA_EnableIT_OPERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_EnableIT_OPERR(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CR, PKA_CR_OPERRIE);
}
/**
  * @brief  Enable end of operation interrupt.
  * @rmtoll
  *  CR           PROCENDIE     LL_PKA_EnableIT_PROCEND
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_EnableIT_PROCEND(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CR, PKA_CR_PROCENDIE);
}

/** @brief  Enable the specified PKA interrupt.
  * @param  pkax specifies the PKA Handle
  * @param  it_source specifies the interrupt source to enable.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_PKA_IT_PROCEND End Of Operation interrupt enable
  *            @arg @ref LL_PKA_IT_ADDRERR Address error interrupt enable
  *            @arg @ref LL_PKA_IT_RAMERR RAM error interrupt enable
  *            @arg @ref LL_PKA_IT_OPERR Operation error interrupt enable
  */
__STATIC_INLINE void LL_PKA_EnableIT(PKA_TypeDef *pkax, uint32_t it_source)
{
  SET_BIT(pkax->CR, it_source);
}
/**
  * @brief  Disable address error interrupt.
  * @rmtoll
  *  CR           ADDRERRIE     LL_PKA_DisableIT_ADDERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_DisableIT_ADDERR(PKA_TypeDef *pkax)
{
  CLEAR_BIT(pkax->CR, PKA_CR_ADDRERRIE);
}
/**
  * @brief  Disable RAM error interrupt.
  * @rmtoll
  *  CR           RAMERRIE      LL_PKA_DisableIT_RAMERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_DisableIT_RAMERR(PKA_TypeDef *pkax)
{
  CLEAR_BIT(pkax->CR, PKA_CR_RAMERRIE);
}
/**
  * @brief  Disable End of operation interrupt.
  * @rmtoll
  *  CR           PROCENDIE     LL_PKA_DisableIT_PROCEND
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_DisableIT_PROCEND(PKA_TypeDef *pkax)
{
  CLEAR_BIT(pkax->CR, PKA_CR_PROCENDIE);
}
/**
  * @brief  Disable OPERATION error interrupt.
  * @rmtoll
  *  CR           OPERRIE      LL_PKA_DisableIT_OPERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_DisableIT_OPERR(PKA_TypeDef *pkax)
{
  CLEAR_BIT(pkax->CR, PKA_CR_OPERRIE);
}

/** @brief  Disable the specified PKA interrupt.
  * @param  pkax specifies the PKA Handle
  * @param  it_source specifies the interrupt source to disable.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_PKA_IT_PROCEND End Of Operation interrupt enable
  *            @arg @ref LL_PKA_IT_ADDRERR Address error interrupt enable
  *            @arg @ref LL_PKA_IT_RAMERR RAM error interrupt enable
  *            @arg @ref LL_PKA_IT_OPERR Operation error interrupt enable
  */
__STATIC_INLINE void LL_PKA_DisableIT(PKA_TypeDef *pkax, uint32_t it_source)
{
  CLEAR_BIT(pkax->CR, it_source);
}
/**
  * @brief  Check if address error interrupt is enabled.
  * @rmtoll
  *  CR           ADDRERRIE     LL_PKA_IsEnabledIT_ADDRERR
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_ADDRERR(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->CR, PKA_CR_ADDRERRIE) == (PKA_CR_ADDRERRIE)) ? 1UL : 0UL);
}
/**
  * @brief  Check if RAM error interrupt is enabled.
  * @rmtoll
  *  CR           RAMERRIE      LL_PKA_IsEnabledIT_RAMERR
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_RAMERR(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->CR, PKA_CR_RAMERRIE) == (PKA_CR_RAMERRIE)) ? 1UL : 0UL);
}
/**
  * @brief  Check if OPERATION error interrupt is enabled.
  * @rmtoll
  *  CR           OPERRIE      LL_PKA_IsEnabledIT_OPERR
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_OPERR(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->CR, PKA_CR_OPERRIE) == (PKA_CR_OPERRIE)) ? 1UL : 0UL);
}
/**
  * @brief  Check if end of operation interrupt is enabled.
  * @rmtoll
  *  CR           PROCENDIE     LL_PKA_IsEnabledIT_PROCEND
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsEnabledIT_PROCEND(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->CR, PKA_CR_PROCENDIE) == (PKA_CR_PROCENDIE)) ? 1UL : 0UL);
}
/**
  * @}
  */
/** @defgroup PKA_LL_EF_FLAG_Management PKA flag management
  * @{
  */
/**
  * @brief  Get PKA address error flag.
  * @rmtoll
  *  SR           ADDRERRF      LL_PKA_IsActiveFlag_ADDRERR
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_ADDRERR(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->SR, PKA_SR_ADDRERRF) == (PKA_SR_ADDRERRF)) ? 1UL : 0UL);
}
/**
  * @brief  Get PKA RAM error flag.
  * @rmtoll
  *  SR           RAMERRF       LL_PKA_IsActiveFlag_RAMERR
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_RAMERR(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->SR, PKA_SR_RAMERRF) == (PKA_SR_RAMERRF)) ? 1UL : 0UL);
}
/**
  * @brief  Get PKA OPERATION error flag.
  * @rmtoll
  *  SR           OPERRF       LL_PKA_IsActiveFlag_OPERR
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_OPERR(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->SR, PKA_SR_OPERRF) == (PKA_SR_OPERRF)) ? 1UL : 0UL);
}
/**
  * @brief  Get PKA end of operation flag.
  * @rmtoll
  *  SR           PROCENDF      LL_PKA_IsActiveFlag_PROCEND
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_PROCEND(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->SR, PKA_SR_PROCENDF) == (PKA_SR_PROCENDF)) ? 1UL : 0UL);
}
/**
  * @brief  Get PKA busy flag.
  * @rmtoll
  *  SR           BUSY          LL_PKA_IsActiveFlag_BUSY
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_BUSY(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->SR, PKA_SR_BUSY) == (PKA_SR_BUSY)) ? 1UL : 0UL);
}
/**
  * @brief  Get PKA INITOK flag.
  * @rmtoll
  *  SR           INITOK      LL_PKA_IsActiveFlag_INITOK
  * @param  pkax PKA Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag_INITOK(const PKA_TypeDef *pkax)
{
  return ((READ_BIT(pkax->SR, PKA_SR_INITOK) == (PKA_SR_INITOK)) ? 1UL : 0UL);
}

/**
  * @brief  Get PKA flag.
  * @rmtoll
  *  SR           RAMERRF       LL_PKA_IsActiveFlag_RAMERR
  * @param  pkax PKA Instance.
  * @param  flag This parameter can be one of the following values:
  *              @arg @ref LL_PKA_FLAG_ADDRERR
  *              @arg @ref LL_PKA_FLAG_RAMERR
  *              @arg @ref LL_PKA_FLAG_PROCEND
  *              @arg @ref LL_PKA_FLAG_BUSY
  *              @arg @ref LL_PKA_FLAG_INITOK
  *              @arg @ref LL_PKA_FLAG_OPERR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PKA_IsActiveFlag(const PKA_TypeDef *pkax, uint32_t flag)
{
  return ((READ_BIT(pkax->SR, flag) == (flag)) ? 1UL : 0UL);
}
/**
  * @brief  Clear PKA address error flag.
  * @rmtoll
  *  CLRFR        ADDRERRFC     LL_PKA_ClearFlag_ADDERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_ClearFlag_ADDERR(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CLRFR, PKA_CLRFR_ADDRERRFC);
}
/**
  * @brief  Clear PKA RAM error flag.
  * @rmtoll
  *  CLRFR        RAMERRFC      LL_PKA_ClearFlag_RAMERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_ClearFlag_RAMERR(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CLRFR, PKA_CLRFR_RAMERRFC);
}
/**
  * @brief  Clear PKA OPERATION error flag.
  * @rmtoll
  *  CLRFR        OPERRFC      LL_PKA_ClearFlag_OPERR
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_ClearFlag_OPERR(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CLRFR, PKA_CLRFR_OPERRFC);
}
/**
  * @brief  Clear PKA end of operation flag.
  * @rmtoll
  *  CLRFR        PROCENDFC     LL_PKA_ClearFlag_PROCEND
  * @param  pkax PKA Instance.
  */
__STATIC_INLINE void LL_PKA_ClearFlag_PROCEND(PKA_TypeDef *pkax)
{
  SET_BIT(pkax->CLRFR, PKA_CLRFR_PROCENDFC);
}

/** @brief  Clear the PKA pending flags which are cleared by writing 1 in a specific bit.
  * @param  pkax specifies the PKA Handle
  * @param  clear_flag specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref LL_PKA_FLAG_PROCEND End Of Operation
  *            @arg @ref LL_PKA_FLAG_ADDRERR Address error
  *            @arg @ref LL_PKA_FLAG_RAMERR RAM error
  *            @arg @ref LL_PKA_FLAG_OPERR Operation error
  */
__STATIC_INLINE void LL_PKA_ClearFlag(PKA_TypeDef *pkax, uint32_t clear_flag)
{
  SET_BIT(pkax->CLRFR, clear_flag);
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
/**
  * @}
  */
#endif /* defined(PKA) */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* STM32U5XX_LL_PKA_H */
