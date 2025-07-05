/**
  **********************************************************************************************************************
  * @file   stm32u5xx_ll_ramcfg.h
  * @brief  Header file of RAMCFG LL module.
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
#ifndef STM32U5XX_LL_RAMCFG_H
#define STM32U5XX_LL_RAMCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

/** @addtogroup RAMCFG_LL RAMCFG
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMCFG_LL_Exported_Constants RAMCFG LL Exported Constants
  * @{
  */

/** @defgroup RAMCFG_FLAG RAMCFG Monitor Flags
  * @{
  */
#define LL_RAMCFG_FLAG_SRAMBUSY RAMCFG_ISR_SRAMBUSY  /*!< RAMCFG SRAM busy flag                           */
#define LL_RAMCFG_FLAG_SE       RAMCFG_ISR_SEDC      /*!< RAMCFG single error detected and corrected flag */
#define LL_RAMCFG_FLAG_DE       RAMCFG_ISR_DED       /*!< RAMCFG double error detected flag               */
#define LL_RAMCFG_FLAG_ALL      (LL_RAMCFG_FLAG_SE | \
                                 LL_RAMCFG_FLAG_DE)  /*!< RAMCFG single error detected and corrected and
                                                          double error detected flags */
/**
  * @}
  */

/** @defgroup RAMCFG_Interrupt RAMCFG Interrupts
  * @{
  */
#define LL_RAMCFG_IT_SE  RAMCFG_IER_SEIE                      /*!< RAMCFG single error interrupt                   */
#define LL_RAMCFG_IT_DE  RAMCFG_IER_DEIE                      /*!< RAMCFG double error interrupt                   */
#define LL_RAMCFG_IT_NMI RAMCFG_IER_ECCNMI                    /*!< RAMCFG double error redirected to NMI interrupt */
#define LL_RAMCFG_IT_ALL (LL_RAMCFG_IT_SE | \
                          LL_RAMCFG_IT_DE | LL_RAMCFG_IT_NMI) /*!< RAMCFG all RAMCFG interrupts                    */
/**
  * @}
  */

/** @defgroup RAMCFG_WaitState RAMCFG Wait State
  * @{
  */
#define LL_RAMCFG_WAIT_STATE_0 (0U)              /*!< RAMCFG 0 wait state */
#define LL_RAMCFG_WAIT_STATE_1 (RAMCFG_CR_WSC_0) /*!< RAMCFG 1 wait state */
/**
  * @}
  */

/** @defgroup RAMCFG_LL_ENUMERATION_INSTANCE definition
  * @{
  */
#define  LL_RAMCFG_SRAM1    (uint32_t)RAMCFG_SRAM1  /*!< SRAM1 instance  */
#define  LL_RAMCFG_SRAM2    (uint32_t)RAMCFG_SRAM2  /*!< SRAM2 instance  */
#if defined (RAMCFG_SRAM3)
#define  LL_RAMCFG_SRAM3    (uint32_t)RAMCFG_SRAM3  /*!< SRAM3 instance  */
#endif /* RAMCFG_SRAM3 */
#define  LL_RAMCFG_SRAM4    (uint32_t)RAMCFG_SRAM4  /*!< SRAM4 instance  */
#define  LL_RAMCFG_BKPRAM   (uint32_t)RAMCFG_BKPRAM /*!< BKPRAM instance */
#if defined (RAMCFG_SRAM5)
#define  LL_RAMCFG_SRAM5    (uint32_t)RAMCFG_SRAM5  /*!< SRAM5 instance  */
#endif /* RAMCFG_SRAM5 */
#if defined (RAMCFG_SRAM6)
#define  LL_RAMCFG_SRAM6    (uint32_t)RAMCFG_SRAM6   /*!< SRAM6 instance  */
#endif /* RAMCFG_SRAM6 */
/**
  * @}
  */


/** @defgroup RAMCFG_WPR_Page_Attr_Selection RAMCFG Write protection page Attr Selection
  * @{
  */
#define LL_RAMCFG_WRP_PAGE_0  RAMCFG_WPR1_P0WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 0  */
#define LL_RAMCFG_WRP_PAGE_1  RAMCFG_WPR1_P1WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 1  */
#define LL_RAMCFG_WRP_PAGE_2  RAMCFG_WPR1_P2WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 2  */
#define LL_RAMCFG_WRP_PAGE_3  RAMCFG_WPR1_P3WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 3  */
#define LL_RAMCFG_WRP_PAGE_4  RAMCFG_WPR1_P4WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 4  */
#define LL_RAMCFG_WRP_PAGE_5  RAMCFG_WPR1_P5WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 5  */
#define LL_RAMCFG_WRP_PAGE_6  RAMCFG_WPR1_P6WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 6  */
#define LL_RAMCFG_WRP_PAGE_7  RAMCFG_WPR1_P7WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 7  */
#define LL_RAMCFG_WRP_PAGE_8  RAMCFG_WPR1_P8WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 8  */
#define LL_RAMCFG_WRP_PAGE_9  RAMCFG_WPR1_P9WP  /*!< LL RAMCFG WRITE PROTECTION PAGE 9  */
#define LL_RAMCFG_WRP_PAGE_10 RAMCFG_WPR1_P10WP /*!< LL RAMCFG WRITE PROTECTION PAGE 10 */
#define LL_RAMCFG_WRP_PAGE_11 RAMCFG_WPR1_P11WP /*!< LL RAMCFG WRITE PROTECTION PAGE 11 */
#define LL_RAMCFG_WRP_PAGE_12 RAMCFG_WPR1_P12WP /*!< LL RAMCFG WRITE PROTECTION PAGE 12 */
#define LL_RAMCFG_WRP_PAGE_13 RAMCFG_WPR1_P13WP /*!< LL RAMCFG WRITE PROTECTION PAGE 13 */
#define LL_RAMCFG_WRP_PAGE_14 RAMCFG_WPR1_P14WP /*!< LL RAMCFG WRITE PROTECTION PAGE 14 */
#define LL_RAMCFG_WRP_PAGE_15 RAMCFG_WPR1_P15WP /*!< LL RAMCFG WRITE PROTECTION PAGE 15 */
#define LL_RAMCFG_WRP_PAGE_16 RAMCFG_WPR1_P16WP /*!< LL RAMCFG WRITE PROTECTION PAGE 16 */
#define LL_RAMCFG_WRP_PAGE_17 RAMCFG_WPR1_P17WP /*!< LL RAMCFG WRITE PROTECTION PAGE 17 */
#define LL_RAMCFG_WRP_PAGE_18 RAMCFG_WPR1_P18WP /*!< LL RAMCFG WRITE PROTECTION PAGE 18 */
#define LL_RAMCFG_WRP_PAGE_19 RAMCFG_WPR1_P19WP /*!< LL RAMCFG WRITE PROTECTION PAGE 19 */
#define LL_RAMCFG_WRP_PAGE_20 RAMCFG_WPR1_P20WP /*!< LL RAMCFG WRITE PROTECTION PAGE 20 */
#define LL_RAMCFG_WRP_PAGE_21 RAMCFG_WPR1_P21WP /*!< LL RAMCFG WRITE PROTECTION PAGE 21 */
#define LL_RAMCFG_WRP_PAGE_22 RAMCFG_WPR1_P22WP /*!< LL RAMCFG WRITE PROTECTION PAGE 22 */
#define LL_RAMCFG_WRP_PAGE_23 RAMCFG_WPR1_P23WP /*!< LL RAMCFG WRITE PROTECTION PAGE 23 */
#define LL_RAMCFG_WRP_PAGE_24 RAMCFG_WPR1_P24WP /*!< LL RAMCFG WRITE PROTECTION PAGE 24 */
#define LL_RAMCFG_WRP_PAGE_25 RAMCFG_WPR1_P25WP /*!< LL RAMCFG WRITE PROTECTION PAGE 25 */
#define LL_RAMCFG_WRP_PAGE_26 RAMCFG_WPR1_P26WP /*!< LL RAMCFG WRITE PROTECTION PAGE 26 */
#define LL_RAMCFG_WRP_PAGE_27 RAMCFG_WPR1_P27WP /*!< LL RAMCFG WRITE PROTECTION PAGE 27 */
#define LL_RAMCFG_WRP_PAGE_28 RAMCFG_WPR1_P28WP /*!< LL RAMCFG WRITE PROTECTION PAGE 28 */
#define LL_RAMCFG_WRP_PAGE_29 RAMCFG_WPR1_P29WP /*!< LL RAMCFG WRITE PROTECTION PAGE 29 */
#define LL_RAMCFG_WRP_PAGE_30 RAMCFG_WPR1_P30WP /*!< LL RAMCFG WRITE PROTECTION PAGE 30 */
#define LL_RAMCFG_WRP_PAGE_31 RAMCFG_WPR1_P31WP /*!< LL RAMCFG WRITE PROTECTION PAGE 31 */
#if defined(RAMCFG_WPR2_P32WP)
#define LL_RAMCFG_WRP_PAGE_32 RAMCFG_WPR2_P32WP /*!< LL RAMCFG WRITE PROTECTION PAGE 32 */
#define LL_RAMCFG_WRP_PAGE_33 RAMCFG_WPR2_P33WP /*!< LL RAMCFG WRITE PROTECTION PAGE 33 */
#define LL_RAMCFG_WRP_PAGE_34 RAMCFG_WPR2_P34WP /*!< LL RAMCFG WRITE PROTECTION PAGE 34 */
#define LL_RAMCFG_WRP_PAGE_35 RAMCFG_WPR2_P35WP /*!< LL RAMCFG WRITE PROTECTION PAGE 35 */
#define LL_RAMCFG_WRP_PAGE_36 RAMCFG_WPR2_P36WP /*!< LL RAMCFG WRITE PROTECTION PAGE 36 */
#define LL_RAMCFG_WRP_PAGE_37 RAMCFG_WPR2_P37WP /*!< LL RAMCFG WRITE PROTECTION PAGE 37 */
#define LL_RAMCFG_WRP_PAGE_38 RAMCFG_WPR2_P38WP /*!< LL RAMCFG WRITE PROTECTION PAGE 38 */
#define LL_RAMCFG_WRP_PAGE_39 RAMCFG_WPR2_P39WP /*!< LL RAMCFG WRITE PROTECTION PAGE 39 */
#define LL_RAMCFG_WRP_PAGE_40 RAMCFG_WPR2_P40WP /*!< LL RAMCFG WRITE PROTECTION PAGE 40 */
#define LL_RAMCFG_WRP_PAGE_41 RAMCFG_WPR2_P41WP /*!< LL RAMCFG WRITE PROTECTION PAGE 41 */
#define LL_RAMCFG_WRP_PAGE_42 RAMCFG_WPR2_P42WP /*!< LL RAMCFG WRITE PROTECTION PAGE 42 */
#define LL_RAMCFG_WRP_PAGE_43 RAMCFG_WPR2_P43WP /*!< LL RAMCFG WRITE PROTECTION PAGE 43 */
#define LL_RAMCFG_WRP_PAGE_44 RAMCFG_WPR2_P44WP /*!< LL RAMCFG WRITE PROTECTION PAGE 44 */
#define LL_RAMCFG_WRP_PAGE_45 RAMCFG_WPR2_P45WP /*!< LL RAMCFG WRITE PROTECTION PAGE 45 */
#define LL_RAMCFG_WRP_PAGE_46 RAMCFG_WPR2_P46WP /*!< LL RAMCFG WRITE PROTECTION PAGE 46 */
#define LL_RAMCFG_WRP_PAGE_47 RAMCFG_WPR2_P47WP /*!< LL RAMCFG WRITE PROTECTION PAGE 47 */
#define LL_RAMCFG_WRP_PAGE_48 RAMCFG_WPR2_P48WP /*!< LL RAMCFG WRITE PROTECTION PAGE 48 */
#define LL_RAMCFG_WRP_PAGE_49 RAMCFG_WPR2_P49WP /*!< LL RAMCFG WRITE PROTECTION PAGE 49 */
#define LL_RAMCFG_WRP_PAGE_50 RAMCFG_WPR2_P50WP /*!< LL RAMCFG WRITE PROTECTION PAGE 50 */
#define LL_RAMCFG_WRP_PAGE_51 RAMCFG_WPR2_P51WP /*!< LL RAMCFG WRITE PROTECTION PAGE 51 */
#define LL_RAMCFG_WRP_PAGE_52 RAMCFG_WPR2_P52WP /*!< LL RAMCFG WRITE PROTECTION PAGE 52 */
#define LL_RAMCFG_WRP_PAGE_53 RAMCFG_WPR2_P53WP /*!< LL RAMCFG WRITE PROTECTION PAGE 53 */
#define LL_RAMCFG_WRP_PAGE_54 RAMCFG_WPR2_P54WP /*!< LL RAMCFG WRITE PROTECTION PAGE 54 */
#define LL_RAMCFG_WRP_PAGE_55 RAMCFG_WPR2_P55WP /*!< LL RAMCFG WRITE PROTECTION PAGE 55 */
#define LL_RAMCFG_WRP_PAGE_56 RAMCFG_WPR2_P56WP /*!< LL RAMCFG WRITE PROTECTION PAGE 56 */
#define LL_RAMCFG_WRP_PAGE_57 RAMCFG_WPR2_P57WP /*!< LL RAMCFG WRITE PROTECTION PAGE 57 */
#define LL_RAMCFG_WRP_PAGE_58 RAMCFG_WPR2_P58WP /*!< LL RAMCFG WRITE PROTECTION PAGE 58 */
#define LL_RAMCFG_WRP_PAGE_59 RAMCFG_WPR2_P59WP /*!< LL RAMCFG WRITE PROTECTION PAGE 59 */
#define LL_RAMCFG_WRP_PAGE_60 RAMCFG_WPR2_P60WP /*!< LL RAMCFG WRITE PROTECTION PAGE 60 */
#define LL_RAMCFG_WRP_PAGE_61 RAMCFG_WPR2_P61WP /*!< LL RAMCFG WRITE PROTECTION PAGE 61 */
#define LL_RAMCFG_WRP_PAGE_62 RAMCFG_WPR2_P62WP /*!< LL RAMCFG WRITE PROTECTION PAGE 62 */
#define LL_RAMCFG_WRP_PAGE_63 RAMCFG_WPR2_P63WP /*!< LL RAMCFG WRITE PROTECTION PAGE 63 */
#endif /* RAMCFG_WPR2_P32WP */
/**
  * @}
  */

/** @defgroup RAMCFG_Erase_Keys RAMCFG Erase Keys
  * @{
  */
#define LL_RAMCFG_ERASE_KEY_1 (0xCAU) /*!< RAMCFG launch erase key 1 */
#define LL_RAMCFG_ERASE_KEY_2 (0x53U) /*!< RAMCFG launch erase key 2 */
/**
  * @}
  */

/** @defgroup RAMCFG_ECC_Keys RAMCFG ECC Keys
  * @{
  */
#define LL_RAMCFG_ECC_KEY_1   (0xAEU) /*!< RAMCFG launch ECC key 1   */
#define LL_RAMCFG_ECC_KEY_2   (0x75U) /*!< RAMCFG launch ECC key 2   */
/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup RAMCFG_LL_Exported_Macros RAMCFG Exported Macros
  * @{
  */

/** @defgroup RAMCFG_LL_EM_COMMON_READ_REGISTERS Common Read Registers macro
  * @{
  */

/**
  * @brief  Write a value in RAMCFG register
  * @param  instance RAMCFG Instance
  * @param  reg   Register to be written
  * @param  value Value to be written in the register
  */
#define LL_RAMCFG_WRITE_REG(instance, reg, value) WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in RAMCFG register.
  * @param  instance RAMCFG Instance.
  * @param  reg      Register to be read.
  * @return Register value.
  */
#define LL_RAMCFG_READ_REG(instance, reg) READ_REG((instance)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMCFG_LL_Exported_Functions RAMCFG Exported Functions
  * @{
  */

/**
  * @brief  Enable the RAMCFG ECC mechanism.
  * @rmtoll CR           ECCE           LL_RAMCFG_EnableECC
  * @rmtoll CR           ALE            LL_RAMCFG_EnableAddressLatch
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_EnableECC(RAMCFG_TypeDef *p_ramcfg)
{
  SET_BIT(p_ramcfg->CR, (RAMCFG_CR_ECCE | RAMCFG_CR_ALE));
}

/**
  * @brief  Disable the RAMCFG ECC mechanism.
  * @rmtoll CR           ECCE           LL_RAMCFG_DisableECC
  * @rmtoll CR           ALE            LL_RAMCFG_DisableAddressLatch
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_DisableECC(RAMCFG_TypeDef *p_ramcfg)
{
  CLEAR_BIT(p_ramcfg->CR, (RAMCFG_CR_ECCE | RAMCFG_CR_ALE));
}

/**
  * @brief  Check whether the RAMCFG ECC mechanism is enabled or not.
  * @rmtoll CR           ECCE           LL_RAMCFG_IsEnabledECC
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of ECC mechanism (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledECC(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->CR, RAMCFG_CR_ECCE) == (RAMCFG_CR_ECCE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the RAMCFG instance address latching error.
  * @rmtoll CR           ALE            LL_RAMCFG_EnableAddressLatch
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_EnableAddressLatch(RAMCFG_TypeDef *p_ramcfg)
{
  SET_BIT(p_ramcfg->CR, RAMCFG_CR_ALE);
}

/**
  * @brief  Disable the RAMCFG instance address latching error.
  * @rmtoll CR           ALE            LL_RAMCFG_DisableAddressLatch
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_DisableAddressLatch(RAMCFG_TypeDef *p_ramcfg)
{
  CLEAR_BIT(p_ramcfg->CR, RAMCFG_CR_ALE);
}

/**
  * @brief  Check whether the RAMCFG address latching error is enabled or not.
  * @rmtoll CR           ALE            LL_RAMCFG_IsEnabledAddressLatch
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of address latching error (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledAddressLatch(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->CR, RAMCFG_CR_ALE) == (RAMCFG_CR_ALE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable RAMCFG Erase operation.
  * @rmtoll CR           SRAMER         LL_RAMCFG_EnableSRAMErase
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_EnableSRAMErase(RAMCFG_TypeDef *p_ramcfg)
{
  SET_BIT(p_ramcfg->CR, RAMCFG_CR_SRAMER);
}

/**
  * @brief  Check whether the RAMCFG erase operation is enabled or not.
  * @rmtoll CR           SRAMER         LL_RAMCFG_IsEnabledSRAMErase
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of erase operation (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledSRAMErase(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->CR, RAMCFG_CR_SRAMER) == (RAMCFG_CR_SRAMER)) ? 1UL : 0UL);
}

/**
  * @brief  Set RAMCFG wait state value.
  * @rmtoll CR           WSC           LL_RAMCFG_SetWaitState
  * @param  p_ramcfg RAMCFG Instance.
  * @param  wait_state :the value of wait state to be configured.
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RAMCFG_WAIT_STATE_0
  *         @arg @ref LL_RAMCFG_WAIT_STATE_1
  */
__STATIC_INLINE void LL_RAMCFG_SetWaitState(RAMCFG_TypeDef *p_ramcfg, uint32_t wait_state)
{
  MODIFY_REG(p_ramcfg->CR, RAMCFG_CR_WSC, wait_state);
}

/**
  * @brief  Get RAMCFG wait state value.
  * @rmtoll CR           WSC           LL_RAMCFG_GetWaitState
  * @param  p_ramcfg RAMCFG Instance.
  * @return the value of wait state configured.
  * @return The return value can be one of the following values :
  *         @arg @ref LL_RAMCFG_WAIT_STATE_0
  *         @arg @ref LL_RAMCFG_WAIT_STATE_1
  */
__STATIC_INLINE uint32_t LL_RAMCFG_GetWaitState(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((uint32_t)READ_BIT(p_ramcfg->CR, RAMCFG_CR_WSC));
}

/**
  * @brief  Get the RAMCFG single error failing address.
  * @rmtoll SEAR           SEAR           LL_RAMCFG_GetECCSingleErrorAddress
  * @param  p_ramcfg RAMCFG Instance.
  * @return Single error address offset.
  */
__STATIC_INLINE uint32_t LL_RAMCFG_GetECCSingleErrorAddress(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((uint32_t)READ_REG(p_ramcfg->SEAR));
}

/**
  * @brief  Get the RAMCFG double error failing address.
  * @rmtoll DEAR           DEAR           LL_RAMCFG_GetECCDoubleErrorAddress
  * @param  p_ramcfg RAMCFG Instance.
  * @return Double error address offset.
  */
__STATIC_INLINE uint32_t LL_RAMCFG_GetECCDoubleErrorAddress(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((uint32_t)READ_REG(p_ramcfg->DEAR));
}

/**
  * @brief  Enable the ramcfg write protection for the given page.
  * @rmtoll WPR1           WPR1           LL_RAMCFG_EnablePageWRP_0_31
  * @param  p_ramcfg RAMCFG instance
  * @param  page_msk
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RAMCFG_WRP_PAGE_0
  *         @arg @ref LL_RAMCFG_WRP_PAGE_1
  *         @arg @ref LL_RAMCFG_WRP_PAGE_2
  *         @arg @ref LL_RAMCFG_WRP_PAGE_3
  *         @arg @ref LL_RAMCFG_WRP_PAGE_4
  *         @arg @ref LL_RAMCFG_WRP_PAGE_5
  *         @arg @ref LL_RAMCFG_WRP_PAGE_6
  *         @arg @ref LL_RAMCFG_WRP_PAGE_7
  *         @arg @ref LL_RAMCFG_WRP_PAGE_8
  *         @arg @ref LL_RAMCFG_WRP_PAGE_9
  *         @arg @ref LL_RAMCFG_WRP_PAGE_10
  *         @arg @ref LL_RAMCFG_WRP_PAGE_11
  *         @arg @ref LL_RAMCFG_WRP_PAGE_12
  *         @arg @ref LL_RAMCFG_WRP_PAGE_13
  *         @arg @ref LL_RAMCFG_WRP_PAGE_14
  *         @arg @ref LL_RAMCFG_WRP_PAGE_15
  *         @arg @ref LL_RAMCFG_WRP_PAGE_16
  *         @arg @ref LL_RAMCFG_WRP_PAGE_17
  *         @arg @ref LL_RAMCFG_WRP_PAGE_18
  *         @arg @ref LL_RAMCFG_WRP_PAGE_19
  *         @arg @ref LL_RAMCFG_WRP_PAGE_20
  *         @arg @ref LL_RAMCFG_WRP_PAGE_21
  *         @arg @ref LL_RAMCFG_WRP_PAGE_22
  *         @arg @ref LL_RAMCFG_WRP_PAGE_23
  *         @arg @ref LL_RAMCFG_WRP_PAGE_24
  *         @arg @ref LL_RAMCFG_WRP_PAGE_25
  *         @arg @ref LL_RAMCFG_WRP_PAGE_26
  *         @arg @ref LL_RAMCFG_WRP_PAGE_27
  *         @arg @ref LL_RAMCFG_WRP_PAGE_28
  *         @arg @ref LL_RAMCFG_WRP_PAGE_29
  *         @arg @ref LL_RAMCFG_WRP_PAGE_30
  *         @arg @ref LL_RAMCFG_WRP_PAGE_31
  */
__STATIC_INLINE void LL_RAMCFG_EnablePageWRP_0_31(RAMCFG_TypeDef *p_ramcfg, uint32_t page_msk)
{
  SET_BIT(p_ramcfg->WPR1, page_msk);
}

/**
  * @brief  Check the ramcfg write protection state for the given page.
  * @rmtoll WPR1           WPR1           LL_RAMCFG_IsEnabledPageWRP_0_31
  * @param  p_ramcfg RAMCFG instance
  * @param  page
  *         This parameter can be one of the following values:
  *         @arg @ref LL_RAMCFG_WRP_PAGE_0
  *         @arg @ref LL_RAMCFG_WRP_PAGE_1
  *         @arg @ref LL_RAMCFG_WRP_PAGE_2
  *         @arg @ref LL_RAMCFG_WRP_PAGE_3
  *         @arg @ref LL_RAMCFG_WRP_PAGE_4
  *         @arg @ref LL_RAMCFG_WRP_PAGE_5
  *         @arg @ref LL_RAMCFG_WRP_PAGE_6
  *         @arg @ref LL_RAMCFG_WRP_PAGE_7
  *         @arg @ref LL_RAMCFG_WRP_PAGE_8
  *         @arg @ref LL_RAMCFG_WRP_PAGE_9
  *         @arg @ref LL_RAMCFG_WRP_PAGE_10
  *         @arg @ref LL_RAMCFG_WRP_PAGE_11
  *         @arg @ref LL_RAMCFG_WRP_PAGE_12
  *         @arg @ref LL_RAMCFG_WRP_PAGE_13
  *         @arg @ref LL_RAMCFG_WRP_PAGE_14
  *         @arg @ref LL_RAMCFG_WRP_PAGE_15
  *         @arg @ref LL_RAMCFG_WRP_PAGE_16
  *         @arg @ref LL_RAMCFG_WRP_PAGE_17
  *         @arg @ref LL_RAMCFG_WRP_PAGE_18
  *         @arg @ref LL_RAMCFG_WRP_PAGE_19
  *         @arg @ref LL_RAMCFG_WRP_PAGE_20
  *         @arg @ref LL_RAMCFG_WRP_PAGE_21
  *         @arg @ref LL_RAMCFG_WRP_PAGE_22
  *         @arg @ref LL_RAMCFG_WRP_PAGE_23
  *         @arg @ref LL_RAMCFG_WRP_PAGE_24
  *         @arg @ref LL_RAMCFG_WRP_PAGE_25
  *         @arg @ref LL_RAMCFG_WRP_PAGE_26
  *         @arg @ref LL_RAMCFG_WRP_PAGE_27
  *         @arg @ref LL_RAMCFG_WRP_PAGE_28
  *         @arg @ref LL_RAMCFG_WRP_PAGE_29
  *         @arg @ref LL_RAMCFG_WRP_PAGE_30
  *         @arg @ref LL_RAMCFG_WRP_PAGE_31
  * @return State of the selected page (1 : write protected, 0 not write protected)
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledPageWRP_0_31(const RAMCFG_TypeDef *p_ramcfg, uint32_t page)
{
  return ((((uint32_t)READ_BIT(p_ramcfg->WPR1, page)) == page) ? 1U : 0U);
}

/**
  * @brief  Get the ramcfg write protection for the given page.
  * @rmtoll WPR1           WPR1           LL_RAMCFG_GetPageWRP_0_31
  * @param  p_ramcfg RAMCFG instance
  * @param  page_msk
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RAMCFG_WRP_PAGE_0
  *         @arg @ref LL_RAMCFG_WRP_PAGE_1
  *         @arg @ref LL_RAMCFG_WRP_PAGE_2
  *         @arg @ref LL_RAMCFG_WRP_PAGE_3
  *         @arg @ref LL_RAMCFG_WRP_PAGE_4
  *         @arg @ref LL_RAMCFG_WRP_PAGE_5
  *         @arg @ref LL_RAMCFG_WRP_PAGE_6
  *         @arg @ref LL_RAMCFG_WRP_PAGE_7
  *         @arg @ref LL_RAMCFG_WRP_PAGE_8
  *         @arg @ref LL_RAMCFG_WRP_PAGE_9
  *         @arg @ref LL_RAMCFG_WRP_PAGE_10
  *         @arg @ref LL_RAMCFG_WRP_PAGE_11
  *         @arg @ref LL_RAMCFG_WRP_PAGE_12
  *         @arg @ref LL_RAMCFG_WRP_PAGE_13
  *         @arg @ref LL_RAMCFG_WRP_PAGE_14
  *         @arg @ref LL_RAMCFG_WRP_PAGE_15
  *         @arg @ref LL_RAMCFG_WRP_PAGE_16
  *         @arg @ref LL_RAMCFG_WRP_PAGE_17
  *         @arg @ref LL_RAMCFG_WRP_PAGE_18
  *         @arg @ref LL_RAMCFG_WRP_PAGE_19
  *         @arg @ref LL_RAMCFG_WRP_PAGE_20
  *         @arg @ref LL_RAMCFG_WRP_PAGE_21
  *         @arg @ref LL_RAMCFG_WRP_PAGE_22
  *         @arg @ref LL_RAMCFG_WRP_PAGE_23
  *         @arg @ref LL_RAMCFG_WRP_PAGE_24
  *         @arg @ref LL_RAMCFG_WRP_PAGE_25
  *         @arg @ref LL_RAMCFG_WRP_PAGE_26
  *         @arg @ref LL_RAMCFG_WRP_PAGE_27
  *         @arg @ref LL_RAMCFG_WRP_PAGE_28
  *         @arg @ref LL_RAMCFG_WRP_PAGE_29
  *         @arg @ref LL_RAMCFG_WRP_PAGE_30
  *         @arg @ref LL_RAMCFG_WRP_PAGE_31
  * @return The return value can be a 0x00000000U or combination of the following values :
  *         @arg @ref LL_RAMCFG_WRP_PAGE_0
  *         @arg @ref LL_RAMCFG_WRP_PAGE_1
  *         @arg @ref LL_RAMCFG_WRP_PAGE_2
  *         @arg @ref LL_RAMCFG_WRP_PAGE_3
  *         @arg @ref LL_RAMCFG_WRP_PAGE_4
  *         @arg @ref LL_RAMCFG_WRP_PAGE_5
  *         @arg @ref LL_RAMCFG_WRP_PAGE_6
  *         @arg @ref LL_RAMCFG_WRP_PAGE_7
  *         @arg @ref LL_RAMCFG_WRP_PAGE_8
  *         @arg @ref LL_RAMCFG_WRP_PAGE_9
  *         @arg @ref LL_RAMCFG_WRP_PAGE_10
  *         @arg @ref LL_RAMCFG_WRP_PAGE_11
  *         @arg @ref LL_RAMCFG_WRP_PAGE_12
  *         @arg @ref LL_RAMCFG_WRP_PAGE_13
  *         @arg @ref LL_RAMCFG_WRP_PAGE_14
  *         @arg @ref LL_RAMCFG_WRP_PAGE_15
  *         @arg @ref LL_RAMCFG_WRP_PAGE_16
  *         @arg @ref LL_RAMCFG_WRP_PAGE_17
  *         @arg @ref LL_RAMCFG_WRP_PAGE_18
  *         @arg @ref LL_RAMCFG_WRP_PAGE_19
  *         @arg @ref LL_RAMCFG_WRP_PAGE_20
  *         @arg @ref LL_RAMCFG_WRP_PAGE_21
  *         @arg @ref LL_RAMCFG_WRP_PAGE_22
  *         @arg @ref LL_RAMCFG_WRP_PAGE_23
  *         @arg @ref LL_RAMCFG_WRP_PAGE_24
  *         @arg @ref LL_RAMCFG_WRP_PAGE_25
  *         @arg @ref LL_RAMCFG_WRP_PAGE_26
  *         @arg @ref LL_RAMCFG_WRP_PAGE_27
  *         @arg @ref LL_RAMCFG_WRP_PAGE_28
  *         @arg @ref LL_RAMCFG_WRP_PAGE_29
  *         @arg @ref LL_RAMCFG_WRP_PAGE_30
  *         @arg @ref LL_RAMCFG_WRP_PAGE_31
  */
__STATIC_INLINE uint32_t LL_RAMCFG_GetPageWRP_0_31(const RAMCFG_TypeDef *p_ramcfg, uint32_t page_msk)
{
  return ((uint32_t)READ_BIT(p_ramcfg->WPR1, page_msk));
}

#if defined(LL_RAMCFG_WRP_PAGE_32)
/**
  * @brief  Enable the ramcfg write protection for the given page.
  * @rmtoll WPR2           WPR2           LL_RAMCFG_EnablePageWRP_32_63
  * @param  p_ramcfg RAMCFG instance
  * @param  page_msk
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RAMCFG_WRP_PAGE_32
  *         @arg @ref LL_RAMCFG_WRP_PAGE_33
  *         @arg @ref LL_RAMCFG_WRP_PAGE_34
  *         @arg @ref LL_RAMCFG_WRP_PAGE_35
  *         @arg @ref LL_RAMCFG_WRP_PAGE_36
  *         @arg @ref LL_RAMCFG_WRP_PAGE_37
  *         @arg @ref LL_RAMCFG_WRP_PAGE_38
  *         @arg @ref LL_RAMCFG_WRP_PAGE_39
  *         @arg @ref LL_RAMCFG_WRP_PAGE_40
  *         @arg @ref LL_RAMCFG_WRP_PAGE_41
  *         @arg @ref LL_RAMCFG_WRP_PAGE_42
  *         @arg @ref LL_RAMCFG_WRP_PAGE_43
  *         @arg @ref LL_RAMCFG_WRP_PAGE_44
  *         @arg @ref LL_RAMCFG_WRP_PAGE_45
  *         @arg @ref LL_RAMCFG_WRP_PAGE_46
  *         @arg @ref LL_RAMCFG_WRP_PAGE_47
  *         @arg @ref LL_RAMCFG_WRP_PAGE_48
  *         @arg @ref LL_RAMCFG_WRP_PAGE_49
  *         @arg @ref LL_RAMCFG_WRP_PAGE_50
  *         @arg @ref LL_RAMCFG_WRP_PAGE_51
  *         @arg @ref LL_RAMCFG_WRP_PAGE_52
  *         @arg @ref LL_RAMCFG_WRP_PAGE_53
  *         @arg @ref LL_RAMCFG_WRP_PAGE_54
  *         @arg @ref LL_RAMCFG_WRP_PAGE_55
  *         @arg @ref LL_RAMCFG_WRP_PAGE_56
  *         @arg @ref LL_RAMCFG_WRP_PAGE_57
  *         @arg @ref LL_RAMCFG_WRP_PAGE_58
  *         @arg @ref LL_RAMCFG_WRP_PAGE_59
  *         @arg @ref LL_RAMCFG_WRP_PAGE_60
  *         @arg @ref LL_RAMCFG_WRP_PAGE_61
  *         @arg @ref LL_RAMCFG_WRP_PAGE_62
  *         @arg @ref LL_RAMCFG_WRP_PAGE_63
  */
__STATIC_INLINE void LL_RAMCFG_EnablePageWRP_32_63(RAMCFG_TypeDef *p_ramcfg, uint32_t page_msk)
{
  SET_BIT(p_ramcfg->WPR2, page_msk);
}

/**
  * @brief  Check the ramcfg write protection state for the given page.
  * @rmtoll WPR2           WPR2           LL_RAMCFG_IsEnabledPageWRP_32_63
  * @param  p_ramcfg RAMCFG instance
  * @param  page
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RAMCFG_WRP_PAGE_32
  *         @arg @ref LL_RAMCFG_WRP_PAGE_33
  *         @arg @ref LL_RAMCFG_WRP_PAGE_34
  *         @arg @ref LL_RAMCFG_WRP_PAGE_35
  *         @arg @ref LL_RAMCFG_WRP_PAGE_36
  *         @arg @ref LL_RAMCFG_WRP_PAGE_37
  *         @arg @ref LL_RAMCFG_WRP_PAGE_38
  *         @arg @ref LL_RAMCFG_WRP_PAGE_39
  *         @arg @ref LL_RAMCFG_WRP_PAGE_40
  *         @arg @ref LL_RAMCFG_WRP_PAGE_41
  *         @arg @ref LL_RAMCFG_WRP_PAGE_42
  *         @arg @ref LL_RAMCFG_WRP_PAGE_43
  *         @arg @ref LL_RAMCFG_WRP_PAGE_44
  *         @arg @ref LL_RAMCFG_WRP_PAGE_45
  *         @arg @ref LL_RAMCFG_WRP_PAGE_46
  *         @arg @ref LL_RAMCFG_WRP_PAGE_47
  *         @arg @ref LL_RAMCFG_WRP_PAGE_48
  *         @arg @ref LL_RAMCFG_WRP_PAGE_49
  *         @arg @ref LL_RAMCFG_WRP_PAGE_50
  *         @arg @ref LL_RAMCFG_WRP_PAGE_51
  *         @arg @ref LL_RAMCFG_WRP_PAGE_52
  *         @arg @ref LL_RAMCFG_WRP_PAGE_53
  *         @arg @ref LL_RAMCFG_WRP_PAGE_54
  *         @arg @ref LL_RAMCFG_WRP_PAGE_55
  *         @arg @ref LL_RAMCFG_WRP_PAGE_56
  *         @arg @ref LL_RAMCFG_WRP_PAGE_57
  *         @arg @ref LL_RAMCFG_WRP_PAGE_58
  *         @arg @ref LL_RAMCFG_WRP_PAGE_59
  *         @arg @ref LL_RAMCFG_WRP_PAGE_60
  *         @arg @ref LL_RAMCFG_WRP_PAGE_61
  *         @arg @ref LL_RAMCFG_WRP_PAGE_62
  *         @arg @ref LL_RAMCFG_WRP_PAGE_63
  * @return State of the selected page (1 : write protected, 0 not write protected)
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledPageWRP_32_63(const RAMCFG_TypeDef *p_ramcfg, uint32_t page)
{
  return ((((uint32_t)READ_BIT(p_ramcfg->WPR2, page)) == page) ? 1U : 0U);
}

/**
  * @brief  Get the ramcfg write protection for the given page.
  * @rmtoll WPR2           WPR2           LL_RAMCFG_GetPageWRP_32_63
  * @param  p_ramcfg RAMCFG instance
  * @param  page_msk
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_RAMCFG_WRP_PAGE_32
  *         @arg @ref LL_RAMCFG_WRP_PAGE_33
  *         @arg @ref LL_RAMCFG_WRP_PAGE_34
  *         @arg @ref LL_RAMCFG_WRP_PAGE_35
  *         @arg @ref LL_RAMCFG_WRP_PAGE_36
  *         @arg @ref LL_RAMCFG_WRP_PAGE_37
  *         @arg @ref LL_RAMCFG_WRP_PAGE_38
  *         @arg @ref LL_RAMCFG_WRP_PAGE_39
  *         @arg @ref LL_RAMCFG_WRP_PAGE_40
  *         @arg @ref LL_RAMCFG_WRP_PAGE_41
  *         @arg @ref LL_RAMCFG_WRP_PAGE_42
  *         @arg @ref LL_RAMCFG_WRP_PAGE_43
  *         @arg @ref LL_RAMCFG_WRP_PAGE_44
  *         @arg @ref LL_RAMCFG_WRP_PAGE_45
  *         @arg @ref LL_RAMCFG_WRP_PAGE_46
  *         @arg @ref LL_RAMCFG_WRP_PAGE_47
  *         @arg @ref LL_RAMCFG_WRP_PAGE_48
  *         @arg @ref LL_RAMCFG_WRP_PAGE_49
  *         @arg @ref LL_RAMCFG_WRP_PAGE_50
  *         @arg @ref LL_RAMCFG_WRP_PAGE_51
  *         @arg @ref LL_RAMCFG_WRP_PAGE_52
  *         @arg @ref LL_RAMCFG_WRP_PAGE_53
  *         @arg @ref LL_RAMCFG_WRP_PAGE_54
  *         @arg @ref LL_RAMCFG_WRP_PAGE_55
  *         @arg @ref LL_RAMCFG_WRP_PAGE_56
  *         @arg @ref LL_RAMCFG_WRP_PAGE_57
  *         @arg @ref LL_RAMCFG_WRP_PAGE_58
  *         @arg @ref LL_RAMCFG_WRP_PAGE_59
  *         @arg @ref LL_RAMCFG_WRP_PAGE_60
  *         @arg @ref LL_RAMCFG_WRP_PAGE_61
  *         @arg @ref LL_RAMCFG_WRP_PAGE_62
  *         @arg @ref LL_RAMCFG_WRP_PAGE_63
  * @return The return value can be a 0x00000000U or combination of the following values :
  *         @arg @ref LL_RAMCFG_WRP_PAGE_32
  *         @arg @ref LL_RAMCFG_WRP_PAGE_33
  *         @arg @ref LL_RAMCFG_WRP_PAGE_34
  *         @arg @ref LL_RAMCFG_WRP_PAGE_35
  *         @arg @ref LL_RAMCFG_WRP_PAGE_36
  *         @arg @ref LL_RAMCFG_WRP_PAGE_37
  *         @arg @ref LL_RAMCFG_WRP_PAGE_38
  *         @arg @ref LL_RAMCFG_WRP_PAGE_39
  *         @arg @ref LL_RAMCFG_WRP_PAGE_40
  *         @arg @ref LL_RAMCFG_WRP_PAGE_41
  *         @arg @ref LL_RAMCFG_WRP_PAGE_42
  *         @arg @ref LL_RAMCFG_WRP_PAGE_43
  *         @arg @ref LL_RAMCFG_WRP_PAGE_44
  *         @arg @ref LL_RAMCFG_WRP_PAGE_45
  *         @arg @ref LL_RAMCFG_WRP_PAGE_46
  *         @arg @ref LL_RAMCFG_WRP_PAGE_47
  *         @arg @ref LL_RAMCFG_WRP_PAGE_48
  *         @arg @ref LL_RAMCFG_WRP_PAGE_49
  *         @arg @ref LL_RAMCFG_WRP_PAGE_50
  *         @arg @ref LL_RAMCFG_WRP_PAGE_51
  *         @arg @ref LL_RAMCFG_WRP_PAGE_52
  *         @arg @ref LL_RAMCFG_WRP_PAGE_53
  *         @arg @ref LL_RAMCFG_WRP_PAGE_54
  *         @arg @ref LL_RAMCFG_WRP_PAGE_55
  *         @arg @ref LL_RAMCFG_WRP_PAGE_56
  *         @arg @ref LL_RAMCFG_WRP_PAGE_57
  *         @arg @ref LL_RAMCFG_WRP_PAGE_58
  *         @arg @ref LL_RAMCFG_WRP_PAGE_59
  *         @arg @ref LL_RAMCFG_WRP_PAGE_60
  *         @arg @ref LL_RAMCFG_WRP_PAGE_61
  *         @arg @ref LL_RAMCFG_WRP_PAGE_62
  *         @arg @ref LL_RAMCFG_WRP_PAGE_63
  */
__STATIC_INLINE uint32_t LL_RAMCFG_GetPageWRP_32_63(const RAMCFG_TypeDef *p_ramcfg, uint32_t page_msk)
{
  return ((uint32_t)READ_BIT(p_ramcfg->WPR2, page_msk));
}
#endif /* LL_RAMCFG_WRP_PAGE_32 */

/**
  * @brief  Set the ramcfg unlock key for the ECC mechanism.
  * @rmtoll ECCKEY           ECCKEY           LL_RAMCFG_SetECCKey
  * @param  p_ramcfg RAMCFG instance
  * @param  key
  *         This parameter must respect the following order:
  *         @arg @ref LL_RAMCFG_ECC_KEY_1
  *         @arg @ref LL_RAMCFG_ECC_KEY_2
  */
__STATIC_INLINE void LL_RAMCFG_SetECCKey(RAMCFG_TypeDef *p_ramcfg, uint32_t key)
{
  WRITE_REG(p_ramcfg->ECCKEY, key);
}

/**
  * @brief  Set the ramcfg unlock key for the Erase operation.
  * @rmtoll ERKEYR           ERASEKEY           LL_RAMCFG_SetEraseKey
  * @param  p_ramcfg RAMCFG instance
  * @param  key
  *         This parameter must respect the following order:
  *         @arg @ref LL_RAMCFG_ERASE_KEY_1
  *         @arg @ref LL_RAMCFG_ERASE_KEY_2
  */
__STATIC_INLINE void LL_RAMCFG_SetEraseKey(RAMCFG_TypeDef *p_ramcfg, uint32_t key)
{
  WRITE_REG(p_ramcfg->ERKEYR, key);
}
/**
  * @}
  */

/** @defgroup RAMCFG_LL_FLAG_Management Flag_Management
  * @{
  */

/**
  * @brief  Clear the RAMCFG pending flags
  * @rmtoll ICR           CSEDC           LL_RAMCFG_ClearFlag
  * @rmtoll ICR           CDED            LL_RAMCFG_ClearFlag
  * @param  p_ramcfg RAMCFG Instance.
  * @param  flags Flag to clear.
  *         This parameter can be one of the following values:
  *            @arg @ref LL_RAMCFG_FLAG_SE  : Single Error Detected and Corrected Flag.
  *            @arg @ref LL_RAMCFG_FLAG_DE  : Double Error Detected Flag.
  *            @arg @ref LL_RAMCFG_FLAG_ALL : RAMCFG single error detected and corrected
                                              and double error detected flags.
  */
__STATIC_INLINE void LL_RAMCFG_ClearFlag(RAMCFG_TypeDef *p_ramcfg, uint32_t flags)
{
  WRITE_REG(p_ramcfg->ICR, flags);
}

/**
  * @brief  Clear the RAMCFG Single Error Detected and Corrected flag.
  * @rmtoll ICR           CSEDC           LL_RAMCFG_ClearFlag
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_ClearFlag_SE(RAMCFG_TypeDef *p_ramcfg)
{
  WRITE_REG(p_ramcfg->ICR, LL_RAMCFG_FLAG_SE);
}

/**
  * @brief  Clear the RAMCFG Double Error Detected flag.
  * @rmtoll ICR           CDED            LL_RAMCFG_ClearFlag
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_ClearFlag_DE(RAMCFG_TypeDef *p_ramcfg)
{
  WRITE_REG(p_ramcfg->ICR, LL_RAMCFG_FLAG_DE);
}

/**
  * @brief  Read the state of the RAMCFG flags
  * @rmtoll ISR           CSEDC           LL_RAMCFG_ClearFlag
  * @rmtoll ICR           CDED            LL_RAMCFG_ClearFlag
  * @param  p_ramcfg RAMCFG Instance.
  * @param  flags Flags to read.
  *         This parameter can be a combination of the following values:
  *           @arg @ref LL_RAMCFG_FLAG_SE       : Single Error Detected and Corrected Flag.
  *           @arg @ref LL_RAMCFG_FLAG_DE       : Double Error Detected Flag.
  *           @arg @ref LL_RAMCFG_FLAG_ALL      : RAMCFG single error detected and corrected
                                                  and double error detected flags.
              @arg @ref LL_RAMCFG_FLAG_SRAMBUSY : SRAM busy with erase operation Flag.
  * @retval State of selected flags.
            The return value can be a combination of the following values:
              @arg @ref LL_RAMCFG_FLAG_SE
              @arg @ref LL_RAMCFG_FLAG_DE
              @arg @ref LL_RAMCFG_FLAG_ALL
              @arg @ref LL_RAMCFG_FLAG_SRAMBUSY
  */
__STATIC_INLINE uint32_t LL_RAMCFG_ReadFlag(const RAMCFG_TypeDef *p_ramcfg, uint32_t flags)
{
  return READ_BIT(p_ramcfg->ISR, flags);
}

/**
  * @brief  Get the RAMCFG Single Error Detected and Corrected flag.
  * @rmtoll ISR           SEDC               LL_RAMCFG_IsActiveFlag_SE
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of SE flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsActiveFlag_SE(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->ISR, LL_RAMCFG_FLAG_SE) == (LL_RAMCFG_FLAG_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMCFG Double Error Detected flag.
  * @rmtoll ISR           DED                LL_RAMCFG_IsActiveFlag_DE
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of DE flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsActiveFlag_DE(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->ISR, LL_RAMCFG_FLAG_DE) == (LL_RAMCFG_FLAG_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMCFG SRAM Busy flag.
  * @rmtoll ISR           SRAMBUSY            LL_RAMCFG_IsActiveFlag_SRAMBusy
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of SRAM Busy flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsActiveFlag_SRAMBusy(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->ISR, LL_RAMCFG_FLAG_SRAMBUSY) == (LL_RAMCFG_FLAG_SRAMBUSY)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup RAMCFG_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable the specified RAMCFG interrupts.
  * @rmtoll IER           SEIE              LL_RAMCFG_EnableIT
  * @rmtoll IER           DEIE              LL_RAMCFG_EnableIT
  * @rmtoll IER           ECCNMI            LL_RAMCFG_EnableIT
  * @param  p_ramcfg RAMCFG Instance.
  * @param  mask Interrupt sources to enable.
  *         This parameter can be a combination of the following values:
  *           @arg @ref LL_RAMCFG_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref LL_RAMCFG_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref LL_RAMCFG_IT_NMI   : Double Error Interrupt redirection to NMI Mask.
  *           @arg @ref LL_RAMCFG_IT_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMCFG_EnableIT(RAMCFG_TypeDef *p_ramcfg, uint32_t mask)
{
  SET_BIT(p_ramcfg->IER, mask);
}

/**
  * @brief  Disable the specified RAMCFG interrupts.
  * @rmtoll IER           SEIE              LL_RAMCFG_DisableIT
  * @rmtoll IER           DEIE              LL_RAMCFG_DisableIT
  * @param  p_ramcfg RAMCFG Instance.
  * @param  mask Interrupt sources to disable.
  *         This parameter can be a combination of the following values:
  *           @arg @ref LL_RAMCFG_IT_SE : Single Error Interrupt Mask.
  *           @arg @ref LL_RAMCFG_IT_DE : Double Error Interrupt Mask.
  * @note   LL_RAMCFG_IT_NMI is cleared only by a global RAMCFG reset.
  */
__STATIC_INLINE void LL_RAMCFG_DisableIT(RAMCFG_TypeDef *p_ramcfg, uint32_t mask)
{
  CLEAR_BIT(p_ramcfg->IER, mask);
}

/**
  * @brief  Enable the ECC single error RAMCFG interrupt.
  * @rmtoll IER           SEIE              LL_RAMCFG_EnableIT_SE
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_EnableIT_SE(RAMCFG_TypeDef *p_ramcfg)
{
  SET_BIT(p_ramcfg->IER, LL_RAMCFG_IT_SE);
}

/**
  * @brief  Disable the ECC single error RAMCFG interrupt.
  * @rmtoll IER           SEIE              LL_RAMCFG_DisableIT_SE
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_DisableIT_SE(RAMCFG_TypeDef *p_ramcfg)
{
  CLEAR_BIT(p_ramcfg->IER, LL_RAMCFG_IT_SE);
}

/**
  * @brief  Check whether the ECC single error RAMCFG interrupt is enabled or not.
  * @rmtoll IER           SEIE              LL_RAMCFG_IsEnabledIT_SE
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledIT_SE(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->IER, LL_RAMCFG_IT_SE) == (LL_RAMCFG_IT_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMCFG interrupt.
  * @rmtoll IER           DEIE              LL_RAMCFG_EnableIT_DE
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_EnableIT_DE(RAMCFG_TypeDef *p_ramcfg)
{
  SET_BIT(p_ramcfg->IER, LL_RAMCFG_IT_DE);
}

/**
  * @brief  Disable the ECC double error RAMCFG interrupt.
  * @rmtoll IER           DEIE              LL_RAMCFG_DisableIT_DE
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_DisableIT_DE(RAMCFG_TypeDef *p_ramcfg)
{
  CLEAR_BIT(p_ramcfg->IER, LL_RAMCFG_IT_DE);
}

/**
  * @brief  Check whether the ECC double error RAMCFG interrupt is enabled or not.
  * @rmtoll IER           DEIE              LL_RAMCFG_IsEnabledIT_DE
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledIT_DE(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->IER, LL_RAMCFG_IT_DE) == (LL_RAMCFG_IT_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMCFG interrupt.
  * @rmtoll IER           ECCNMI            LL_RAMCFG_EnableIT_NMI
  * @param  p_ramcfg RAMCFG Instance.
  */
__STATIC_INLINE void LL_RAMCFG_EnableIT_NMI(RAMCFG_TypeDef *p_ramcfg)
{
  SET_BIT(p_ramcfg->IER, LL_RAMCFG_IT_NMI);
}

/**
  * @brief  Check whether the ECC NMI interrupt is enabled or not.
  * @rmtoll IER           ECCNMI            LL_RAMCFG_IsEnabledIT_NMI
  * @param  p_ramcfg RAMCFG Instance.
  * @return State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMCFG_IsEnabledIT_NMI(const RAMCFG_TypeDef *p_ramcfg)
{
  return ((READ_BIT(p_ramcfg->IER, LL_RAMCFG_IT_NMI) == (LL_RAMCFG_IT_NMI)) ? 1UL : 0UL);
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

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_RAMCFG_H */
