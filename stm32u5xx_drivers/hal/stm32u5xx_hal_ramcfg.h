/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_ramcfg.h
  * @brief   Header file of RAMCFG HAL module.
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
#ifndef STM32U5XX_HAL_RAMCFG_H
#define STM32U5XX_HAL_RAMCFG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_ramcfg.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup RAMCFG
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMCFG_Exported_Constants RAMCFG Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup RAMCFG_Exported_Types RAMCFG Exported Types
  * @{
  */

/*! HAL RAMCFG interrupt enumeration definition */
typedef enum
{
  HAL_RAMCFG_IT_SE     = LL_RAMCFG_IT_SE,                     /*!< RAMCFG single error interrupt enable             */
  HAL_RAMCFG_IT_DE     = LL_RAMCFG_IT_DE,                     /*!< RAMCFG double error interrupt enable             */
  HAL_RAMCFG_IT_NMI    = LL_RAMCFG_IT_NMI,                    /*!< RAMCFG NMI interrupt enable                      */
  HAL_RAMCFG_IT_SE_DE  = LL_RAMCFG_IT_SE | LL_RAMCFG_IT_DE,   /*!< RAMCFG single and double error interrupts enable */
  HAL_RAMCFG_IT_SE_NMI = LL_RAMCFG_IT_SE | LL_RAMCFG_IT_NMI,  /*!< RAMCFG single error and NMI interrupts enable    */
} hal_ramcfg_it_t;

/*! RAMCFG Wait State enumeration definition */
typedef enum
{
  HAL_RAMCFG_WAIT_STATE_0 = LL_RAMCFG_WAIT_STATE_0, /*!< RAMCFG wait state 0 */
  HAL_RAMCFG_WAIT_STATE_1 = LL_RAMCFG_WAIT_STATE_1, /*!< RAMCFG wait state 1 */
} hal_ramcfg_wait_state_t;

/*! RAMCFG instance enumeration definition */
typedef enum
{
  HAL_RAMCFG_SRAM1  = LL_RAMCFG_SRAM1,  /*!< SRAM1 instance  */
  HAL_RAMCFG_SRAM2  = LL_RAMCFG_SRAM2,  /*!< SRAM2 instance  */
#if defined (RAMCFG_SRAM3)
  HAL_RAMCFG_SRAM3  = LL_RAMCFG_SRAM3,  /*!< SRAM3 instance  */
#endif /* RAMCFG_SRAM3 */
  HAL_RAMCFG_SRAM4  = LL_RAMCFG_SRAM4,  /*!< SRAM4 instance  */
  HAL_RAMCFG_BKPRAM = LL_RAMCFG_BKPRAM, /*!< BKPRAM instance */
#if defined (RAMCFG_SRAM5)
  HAL_RAMCFG_SRAM5  = LL_RAMCFG_SRAM5,  /*!< SRAM5 instance  */
#endif /* RAMCFG_SRAM5 */
#if defined (RAMCFG_SRAM6)
  HAL_RAMCFG_SRAM6  = LL_RAMCFG_SRAM6   /*!< SRAM6 instance  */
#endif /* RAMCFG_SRAM6 */
} hal_ramcfg_t;

/*! HAL RAMCFG write protection status enumeration definition */
typedef enum
{
  HAL_RAMCFG_WRP_PAGE_NOT_PROTECTED = 0U, /*!< RAMCFG not write protected page */
  HAL_RAMCFG_WRP_PAGE_PROTECTED     = 1U  /*!< RAMCFG write protected page     */
} hal_ramcfg_wrp_page_status_t;

/*! HAL RAMCFG ECC fail type enumeration definition */
typedef enum
{
  HAL_RAMCFG_ERROR_ECC_NONE = 0U,                /*!< RAMCFG ECC fail none                                  */
  HAL_RAMCFG_ERROR_ECC_SE   = LL_RAMCFG_FLAG_SE, /*!< RAMCFG ECC fail single error detection and correction */
  HAL_RAMCFG_ERROR_ECC_DE   = LL_RAMCFG_FLAG_DE  /*!< RAMCFG ECC fail double error detection                */
} hal_ramcfg_ecc_fail_type_t;

/*! HAL RAMCFG ECC fail structure definition */
typedef struct
{
  hal_ramcfg_ecc_fail_type_t type;    /*!< RAMCFG ECC fail type    */
  uint32_t                   address; /*!< RAMCFG ECC fail address */
} hal_ramcfg_ecc_fail_info_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMCFG_Exported_Functions RAMCFG Exported Functions
  * @{
  */

/** @defgroup RAMCFG_Exported_Functions_Group1 ECC operation functions
  * @{
  */
/* Enable and Disable ECC process APIs */
hal_status_t HAL_RAMCFG_ECC_Enable(hal_ramcfg_t instance);
hal_status_t HAL_RAMCFG_ECC_Enable_IT(hal_ramcfg_t instance, hal_ramcfg_it_t interrupt);
hal_status_t HAL_RAMCFG_ECC_Disable(hal_ramcfg_t instance);
void         HAL_RAMCFG_ECC_GetFailInfo(const hal_ramcfg_t instance, hal_ramcfg_ecc_fail_info_t *p_info);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group2 Configure wait state functions
  * @{
  */
/* Wait state latency APIs */
hal_status_t            HAL_RAMCFG_SetWaitState(hal_ramcfg_t instance, hal_ramcfg_wait_state_t wait_state);
hal_ramcfg_wait_state_t HAL_RAMCFG_GetWaitState(hal_ramcfg_t instance);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group3 Write protection functions
  * @{
  */
/* Write protection APIs */
hal_status_t HAL_RAMCFG_EnablePageWRP(hal_ramcfg_t instance, uint32_t start_page, uint32_t page_nbr);
hal_status_t HAL_RAMCFG_EnableWRPByAddr(hal_ramcfg_t instance, uint32_t sram_addr, uint32_t size_byte);
hal_ramcfg_wrp_page_status_t HAL_RAMCFG_IsEnabledPageWRP(hal_ramcfg_t instance, uint32_t page);
hal_ramcfg_wrp_page_status_t HAL_RAMCFG_IsEnabledWRPByAddr(hal_ramcfg_t instance, uint32_t sram_addr);

/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group4 Erase operation functions
  * @{
  */
/* Erase APIs */
hal_status_t HAL_RAMCFG_MassErase(hal_ramcfg_t instance, uint32_t timeout);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group5 Handle interrupt and callbacks functions
  * @{
  */
/* IRQHandler APIs */
void HAL_RAMCFG_IRQHandler(hal_ramcfg_t instance);
hal_status_t HAL_RAMCFG_NMI_IRQHandler(hal_ramcfg_t instance);

/* Callback APIs */
hal_status_t HAL_RAMCFG_ECC_ErrorCallback(hal_ramcfg_t instance);

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

#endif /* STM32U5XX_HAL_RAMCFG_H */
/**
  * @}
  */
