/**
  **********************************************************************************************************************
  * @file   stm32u5xx_hal_gpu2d.h
  * @brief  Header file of GPU2D HAL module.
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
#ifndef STM32U5XX_HAL_GPU2D_H
#define STM32U5XX_HAL_GPU2D_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (GPU2D)

/** @defgroup GPU2D GPU2D
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup GPU2D_Private_Constants GPU2D Private Constants
  * @{
  */

/** @defgroup GPU2D_Register_Offset GPU2D Register Offset
  * @{
  */
#define HAL_GPU2D_ITCTRL        0x00F8U /*!< GPU2D Interrupt Control Register Offset            */
#define HAL_GPU2D_CLID          0x0148U /*!< GPU2D Last Command List Identifier Register Offset */
#define HAL_GPU2D_BREAKPOINT    0x0080U /*!< GPU2D Breakpoint Register Offset                   */
#define HAL_GPU2D_SYS_INTERRUPT 0x0FF8U /*!< GPU2D System Interrupt Register Offset             */
/**
  * @}
  */

/** @defgroup GPU2D_Offset GPU2D Last Register Offset
  * @{
  */
#define HAL_GPU2D_OFFSET 0x1000U /*!< Last GPU2D Register Offset */
/**
  * @}
  */

/**
  * @}
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GPU2D_Exported_Constants GPU2D Exported Constants
  * @{
  */

/** @defgroup GPU2D_Interrupt_Source GPU2D Interrupt Source
  * @{
  */
#define HAL_GPU2D_IT_CLC 0x00000001U /*!< Command List Complete interrupt */
/**
  * @}
  */

/** @defgroup GPU2D_Flag GPU2D Flag
  * @{
  */
#define HAL_GPU2D_FLAG_CLC 0x00000001U /*!< Command List Complete flag  */
/**
  * @}
  */

/**
  * @}
  */
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup GPU2D_Exported_Types GPU2D Exported Types
  * @{
  */

/*! GPU2D Instance */
typedef enum
{
  HAL_GPU2D = GPU2D, /*!< Peripheral instance GPU2D */
} hal_gpu2d_t;

/*! GPU2D Global State */
typedef enum
{
  HAL_GPU2D_STATE_RESET = 0U,        /*!< GPU2D not yet initialized or disabled */
  HAL_GPU2D_STATE_INIT  = 1U << 31U, /*!< GPU2D Initialized and ready for use   */
} hal_gpu2d_state_t;

/**
  * @brief GPU2D handle structure definition
  */
typedef struct hal_gpu2d_handle_s hal_gpu2d_handle_t; /*!< GPU2D handle structure type */

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
/*! GPU2D callback pointer definition */
typedef void (*hal_gpu2d_cb_t)(hal_gpu2d_handle_t *hgpu2d);

/*! GPU2D command list complete callback pointer definition */
typedef void (*hal_gpu2d_clc_cb_t)(hal_gpu2d_handle_t *hgpu2d, uint32_t cmd_list_id);
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */

/*! HAL GPU2D handle structure definition */
struct hal_gpu2d_handle_s
{
  hal_gpu2d_t                instance;             /*!< Peripheral instance                  */

  volatile hal_gpu2d_state_t global_state;         /*!< GPU2D state                          */

#if defined (USE_HAL_GPU2D_USER_DATA) && (USE_HAL_GPU2D_USER_DATA == 1)
  const void                 *p_user_data;         /*!< User Data Pointer                    */
#endif /* USE_HAL_GPU2D_USER_DATA */

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
  hal_gpu2d_cb_t             error_cb;             /*!< GPU2D Error Callback                 */
  hal_gpu2d_clc_cb_t         command_list_cplt_cb; /*!< GPU2D Command list Complete Callback */
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */
};
/**
  * @}
  */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GPU2D_Exported_Functions GPU2D Exported Functions
  * @{
  */

/** @defgroup GPU2D_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_GPU2D_Init(hal_gpu2d_handle_t *hgpu2d, hal_gpu2d_t instance);
void         HAL_GPU2D_DeInit(hal_gpu2d_handle_t *hgpu2d);
/**
  * @}
  */

/** @defgroup GPU2D_Exported_Functions_Group2 IO operation functions
  * @{
  */
uint32_t     HAL_GPU2D_ReadRegister(const hal_gpu2d_handle_t *hgpu2d, uint32_t offset);
hal_status_t HAL_GPU2D_WriteRegister(hal_gpu2d_handle_t *hgpu2d, uint32_t offset, uint32_t value);
/**
  * @}
  */

/** @defgroup GPU2D_Exported_Functions_Group3 IRQHandler and Register callbacks functions
  * @{
  */
void HAL_GPU2D_IRQHandler(hal_gpu2d_handle_t *hgpu2d);
void HAL_GPU2D_ERR_IRQHandler(hal_gpu2d_handle_t *hgpu2d);

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
hal_status_t HAL_GPU2D_RegisterCommandListCpltCallback(hal_gpu2d_handle_t *hgpu2d, hal_gpu2d_clc_cb_t p_callback);
hal_status_t HAL_GPU2D_RegisterErrorCallback(hal_gpu2d_handle_t *hgpu2d, hal_gpu2d_cb_t p_callback);
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup GPU2D_Exported_Functions_Group4 Callbacks functions
  * @{
  */
void HAL_GPU2D_CommandListCpltCallback(hal_gpu2d_handle_t *hgpu2d, uint32_t cmd_list_id);
void HAL_GPU2D_ErrorCallback(hal_gpu2d_handle_t *hgpu2d);
/**
  * @}
  */

/** @defgroup GPU2D_Exported_Functions_Group5 Peripheral Get State function
  * @{
  */
hal_gpu2d_state_t HAL_GPU2D_GetState(const hal_gpu2d_handle_t *hgpu2d);
/**
  * @}
  */

#if defined (USE_HAL_GPU2D_USER_DATA) && (USE_HAL_GPU2D_USER_DATA == 1)
/** @defgroup GPU2D_Exported_Functions_Group6 Set/Get user data
  * @{
  */
void        HAL_GPU2D_SetUserData(hal_gpu2d_handle_t *hgpu2d, const void *p_user_data);
const void *HAL_GPU2D_GetUserData(const hal_gpu2d_handle_t *hgpu2d);
/**
  * @}
  */
#endif /* USE_HAL_GPU2D_USER_DATA */

/** @defgroup GPU2D_Exported_Functions_Group7 Interrupt and Flag management
  * @{
 - HAL_GPU2D_IsActiveFlag() : Get the GPU2D pending flags.
 - HAL_GPU2D_ClearFlag()    : Clear the GPU2D pending flags.
 - HAL_GPU2D_EnableIT()     : Enable the specified GPU2D interrupts.
 - HAL_GPU2D_DisableIT()    : Disable the specified GPU2D interrupts.
 - HAL_GPU2D_IsEnabledIT()  : Check whether the specified GPU2D interrupt source is enabled or not.
  */

/**
  * @brief  Get the GPU2D pending flags.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  * @param  flag    Specify the GPU2D flag to check
  *                 This parameter can be only one of the following values:
  *                 @arg @ref HAL_GPU2D_FLAG_CLC : Command List Complete flag
  * @retval The state of GPU2D flag (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_GPU2D_IsActiveFlag(const hal_gpu2d_handle_t *hgpu2d, uint32_t flag)
{
  return (uint32_t)(READ_BIT(*(__IO uint32_t *)((uint32_t)(hgpu2d->instance) + HAL_GPU2D_ITCTRL), flag) == flag);
}

/**
  * @brief Clear the GPU2D pending flags.
  * @param hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  * @param flag    Specify the GPU2D flag to clear
  *                This parameter can be any combination of the following value:
  *                @arg @ref HAL_GPU2D_FLAG_CLC : Command List Complete flag
  */
__STATIC_INLINE void HAL_GPU2D_ClearFlag(hal_gpu2d_handle_t *hgpu2d, uint32_t flag)
{
  CLEAR_BIT(*(__IO uint32_t *)((uint32_t)(hgpu2d->instance) + HAL_GPU2D_ITCTRL), flag);
}

/**
  * @brief Enable the specified GPU2D interrupt.
  * @param hgpu2d     Pointer to a hal_gpu2d_handle_t structure
  * @param interrupt  Specify the GPU2D interrupt to enable
  *                   This parameter can be any combination of the following value:
  *                   @arg @ref HAL_GPU2D_IT_CLC : Command List Complete interrupt
  */
__STATIC_INLINE void HAL_GPU2D_EnableIT(hal_gpu2d_handle_t *hgpu2d, uint32_t interrupt)
{
  SET_BIT(*(__IO uint32_t *)((uint32_t)(hgpu2d->instance) + HAL_GPU2D_ITCTRL), interrupt);
}

/**
  * @brief Disable the specified GPU2D interrupts.
  * @param hgpu2d     Pointer to a hal_gpu2d_handle_t structure
  * @param interrupt  Specify the GPU2D interrupt to disable
  *                   This parameter can be any combination of the following value:
  *                   @arg @ref HAL_GPU2D_IT_CLC : Command List Complete interrupt
  */
__STATIC_INLINE void HAL_GPU2D_DisableIT(hal_gpu2d_handle_t *hgpu2d, uint32_t interrupt)
{
  CLEAR_BIT(*(__IO uint32_t *)((uint32_t)(hgpu2d->instance) + HAL_GPU2D_ITCTRL), interrupt);
}

/**
  * @brief  Check whether the specified GPU2D interrupt source is enabled or not.
  * @param  hgpu2d     Pointer to a hal_gpu2d_handle_t structure
  * @param  interrupt  Specify the GPU2D interrupt to check their status
  *                    This parameter can be only one of the following value:
  *                    @arg @ref HAL_GPU2D_IT_CLC : Command List Complete interrupt
  * @retval The state of GPU2D interrupt (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_GPU2D_IsEnabledIT(const hal_gpu2d_handle_t *hgpu2d, uint32_t interrupt)
{
  return (uint32_t)(READ_BIT(*(__IO uint32_t *)((uint32_t)(hgpu2d->instance) + HAL_GPU2D_ITCTRL),
                             interrupt) == interrupt);
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

#endif /* GPU2D */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_GPU2D_H */
