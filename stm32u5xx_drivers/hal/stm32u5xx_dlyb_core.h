/**
  ******************************************************************************
  * @file    stm32u5xx_dlyb_core.h
  * @brief   Header file of DelayBlock module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_DLYB_CORE_H
#define STM32U5XX_DLYB_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
/** @defgroup DLYB_CORE DLYB Core
  * @{
  */
#if (defined (USE_HAL_SD_MODULE) && (USE_HAL_SD_MODULE == 1)) \
    || (defined (USE_HAL_MMC_MODULE) && (USE_HAL_MMC_MODULE == 1)) \
    || (defined (USE_HAL_SDIO_MODULE) && (USE_HAL_SDIO_MODULE == 1)) \
    || (defined (USE_HAL_XSPI_MODULE) && (USE_HAL_XSPI_MODULE == 1))
#if defined (DLYB_SDMMC1) || defined (DLYB_SDMMC2) || defined (DLYB_OCTOSPI1) || defined (DLYB_OCTOSPI2)
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DLYB_Exported_Constants DLYB CORE Exportyed Constants
  * @{
  */
#define DLYB_FLAG_LNGF                   DLYB_CFGR_LNGF
#define DLYB_TIMEOUT_MS                  0xFFU       /*!< DLYB timeout : 255 ms                           */
#define DLYB_LNG_10_0_MSK                0x07FF0000U /*!< 11 first bits mask of LNG in CFGR register      */
#define DLYB_LNG_11_10_MSK               0x0C000000U /*!< 10th and 11th bits mask of LNG in CFGR register */
#define DLYB_MAX_UNIT_DELAY_CELL         0x00000080U /*!< Max UNIT value (128)                            */
#define DLYB_MAX_TUNING_OUTPUT_CLK_PHASE 0x0000000CU /*!< Max SELECT value (12)                           */
#define DLYB_MAX_USED_OUTPUT_CLK_PHASE   0x0000000AU /*!< Max SELECT value (10)                           */
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DLYB_Exported_Types DLYB Exported Types
  * @{
  */
/*! DLYB state */

typedef enum
{
  DLYB_DISABLED = 0U, /*!< DLYB disabled */
  DLYB_ENABLED,       /*!< DLYB enabled  */
} dlyb_state_t;
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup DLYB_CORE_Exported_Functions DLYB Exported Functions
  * @{
  */

/** @defgroup DLYB_CORE_Group1 Output clock phase tuning functions
  * @{
  */
hal_status_t DLYB_ConfigureUnitDelay(DLYB_TypeDef *dlybx);
uint32_t DLYB_CalculateMaxOutputClockPhase(DLYB_TypeDef *dlybx);
/**
  * @}
  */

/** @defgroup DLYB_CORE_Group2 Set and Get Output Clock Phase Value Functions
  * @{
  */
void DLYB_SetOutputClockPhase(DLYB_TypeDef *dlybx, uint32_t clock_phase_value);
uint32_t DLYB_GetOutputClockPhase(const DLYB_TypeDef *dlybx);
/**
  * @}
  */

/** @defgroup DLYB_CORE_Group3 Set and Get DLYB CFGR register context
  * @{
  */
void DLYB_SetConfig(DLYB_TypeDef *dlybx, uint32_t unit, uint32_t sel);
void DLYB_GetConfig(DLYB_TypeDef *dlybx, uint32_t *p_unit, uint32_t *p_sel);
/**
  * @}
  */

/** @defgroup DLYB_CORE_Group4 Enable and Disable Delay Block functions
  * @{
  */
/**
  * @brief Enable the delay block peripheral.
  * @param dlybx DLYB Instance.
  */
__STATIC_INLINE void DLYB_Enable(DLYB_TypeDef *dlybx)
{
  SET_BIT(dlybx->CR, DLYB_CR_DEN);
}

/**
  * @brief Disable the delay block peripheral.
  * @param dlybx DLYB Instance.
  */
__STATIC_INLINE void DLYB_Disable(DLYB_TypeDef *dlybx)
{
  CLEAR_BIT(dlybx->CR, DLYB_CR_DEN);
}

/**
  * @brief Check whether the delay block peripheral is enabled or not.
  * @param dlybx DLYB Instance.
  * @retval DLYB_ENABLED  if the delay block peripheral is enabled.
  * @retval DLYB_DISABLED if the delay block peripheral is disabled.
  */
__STATIC_INLINE dlyb_state_t DLYB_IsEnabled(const DLYB_TypeDef *dlybx)
{
  return ((READ_BIT(dlybx->CR, DLYB_CR_DEN) == DLYB_CR_DEN) ? DLYB_ENABLED : DLYB_DISABLED);
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* DLYB_SDMMC1 || DLYB_SDMMC2 || DLYB_OCTOSPI1 || DLYB_OCTOSPI2 */
#endif /* USE_HAL_SD_MODULE || USE_HAL_MMC_MODULE || USE_HAL_SDIO_MODULE || USE_HAL_XSPI_MODULE */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus

}

#endif /* __cplusplus */
#endif /* STM32U5XX_DLYB_CORE_H */
