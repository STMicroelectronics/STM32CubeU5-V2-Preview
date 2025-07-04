/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gpu2d.c
  * @brief   GPU2D HAL module driver.
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

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (GPU2D)

/** @addtogroup GPU2D
  * @{
# How to use the GPU2D HAL module driver

The sequence below describes how to use this driver to covers only the low layer services allowing to access to the
HW registers read/write , to intercept and manage the interrupts and to signal errors or events to the upper MW layer.

A set of functions allowing to initialize the HAL GPU2D driver and link it to a physical GPU2D peripheral instance and
to deinitialize the GPU2D peripheral by resetting the HAL GPU2D handle state:
  - HAL_GPU2D_Init()
  - HAL_GPU2D_DeInit()

HAL_GPU2D_ReadRegister()  : Read GPU2D register, in order to ensure higher-level library functionality.

HAL_GPU2D_WriteRegister() : Write to GPU2D register.

# Callback registration
  - When the compilation flag USE_HAL_GPU2D_REGISTER_CALLBACKS is set to 1, it allows the user to configure dynamically
    the driver callbacks instead of weak functions:
    - HAL_GPU2D_ErrorCallback()           : GPU2D error callback.
    - HAL_GPU2D_CommandListCpltCallback() : GPU2D command list complete callback.

  - When the compilation flag USE_HAL_GPU2D_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
    feature is not available and all callbacks are set to the corresponding weak functions, in this case user can
    provide his own implementation of these weak functions at user application side.

## Configuration inside the GPU2D driver

Config defines                   | Description           | Default value | Note                                        |
-------------------------------- | --------------------- | ------------- | ------------------------------------------- |
PRODUCT                          | from PreProcessor env |       NA      | The selected device (ex STM32U599xx)        |
USE_ASSERT_DBG_PARAM             | from PreProcessor env |      None     | Allows to use the assert check parameters   |
USE_ASSERT_DBG_STATE             | from PreProcessor env |      None     | Allows to use the assert check states       |
USE_HAL_GPU2D_MODULE             | from hal_conf.h       |       1       | Allows to use HAL GPU2D module              |
USE_HAL_CHECK_PARAM              | from hal_conf.h       |       0       | Allows to use the run-time checks parameters|
USE_HAL_GPU2D_REGISTER_CALLBACKS | from hal_conf.h       |       0       | Allows to use the load and store exclusive  |
USE_HAL_GPU2D_USER_DATA          | from hal_conf.h       |       0       | Allows to use user data inside GPU2D        |
USE_HAL_GPU2D_CLK_ENABLE_MODEL|from hal_conf.h|HAL_CLK_ENABLE_NO|Allows to use the clock interface management for GPU2D|
  */

#if defined (USE_HAL_GPU2D_MODULE) && (USE_HAL_GPU2D_MODULE == 1)

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup GPU2D_Private_Macros GPU2D Private Macros
  * @{
  */
/*! Macro to check GPU2D offset */
#define IS_GPU2D_OFFSET(offset) ((offset) < HAL_GPU2D_OFFSET)

/*! Macro to write a value in GPU2D register */
#define GPU2D_WRITE_REG(handle, reg, value) WRITE_REG(*(__IO uint32_t *)((uint32_t)(handle->instance) + (reg)), (value))

/*! Macro to read a value in GPU2D register */
#define GPU2D_READ_REG(handle, reg) READ_REG(*(__IO uint32_t *)((uint32_t)(handle->instance) + (reg)))
/**
  * @}
  */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup GPU2D_Exported_Functions GPU2D Exported Functions
  * @{
  */

/** @addtogroup GPU2D_Exported_Functions_Group1
  * @{
A set of functions allowing to initialize and deinitialize the GPU2D peripheral :
 - HAL_GPU2D_Init()   : Initialize the HAL GPU2D handle and associate it to a given GPU2D peripheral instance.
 - HAL_GPU2D_DeInit() : De-initialize the HAL GPU2D.
  */

/**
  * @brief  Initialize the HAL GPU2D handle and associate it to a given GPU2D peripheral instance.
  * @param  hgpu2d              Pointer to a hal_gpu2d_handle_t structure
  * @param  instance            Value from @ref hal_gpu2d_t enumeration
  * @retval HAL_INVALID_PARAM   Invalid parameter when hgpu2d pointer is NULL
  * @retval HAL_OK              GPU2D is successfully initialized
  */
hal_status_t HAL_GPU2D_Init(hal_gpu2d_handle_t *hgpu2d, hal_gpu2d_t instance)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);
  ASSERT_DBG_PARAM(IS_GPU2D_ALL_INSTANCE((uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hgpu2d == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgpu2d->instance = instance;

#if defined (USE_HAL_GPU2D_CLK_ENABLE_MODEL) && (USE_HAL_GPU2D_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_GPU2D_EnableClock();
#endif /* USE_HAL_GPU2D_CLK_ENABLE_MODEL */

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
  hgpu2d->error_cb             = HAL_GPU2D_ErrorCallback;
  hgpu2d->command_list_cplt_cb = HAL_GPU2D_CommandListCpltCallback;
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */

#if defined (USE_HAL_GPU2D_USER_DATA) && (USE_HAL_GPU2D_USER_DATA == 1)
  hgpu2d->p_user_data = NULL;
#endif /* USE_HAL_GPU2D_USER_DATA */

  hgpu2d->global_state = HAL_GPU2D_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initialize the HAL GPU2D.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  */
void HAL_GPU2D_DeInit(hal_gpu2d_handle_t *hgpu2d)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);
  ASSERT_DBG_PARAM(IS_GPU2D_ALL_INSTANCE((uint32_t)hgpu2d->instance));

  hgpu2d->global_state = HAL_GPU2D_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup GPU2D_Exported_Functions_Group2
  * @{
A set of functions allowing to manage the GPU2D data transfers:
 - HAL_GPU2D_ReadRegister()  : Read GPU2D register, in order to ensure higher-level library functionality.
 - HAL_GPU2D_WriteRegister() : Write to GPU2D register.
  */

/**
  * @brief  Read GPU2D register, in order to ensure higher-level library functionality.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  * @param  offset  The register offset from GPU2D base address to read.
  *                 This parameter can be a value of @ref GPU2D_Register_Offset group
  * @retval Register value
  */
uint32_t HAL_GPU2D_ReadRegister(const hal_gpu2d_handle_t *hgpu2d, uint32_t offset)
{
  uint32_t value;

  ASSERT_DBG_PARAM(hgpu2d != NULL);
  ASSERT_DBG_PARAM(IS_GPU2D_OFFSET(offset));

  ASSERT_DBG_STATE(hgpu2d->global_state, HAL_GPU2D_STATE_INIT);

  value = GPU2D_READ_REG(hgpu2d, offset);

  return value;
}

/**
  * @brief  Write to GPU2D register.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  * @param  offset  The register offset from GPU2D base address to read.
  *                 This parameter can be a value of @ref GPU2D_Register_Offset group
  * @param  value   The value to be written to provided register.
  * @retval HAL_OK  Value is successfully written to provided register
  */
hal_status_t HAL_GPU2D_WriteRegister(hal_gpu2d_handle_t *hgpu2d, uint32_t offset, uint32_t value)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);
  ASSERT_DBG_PARAM(IS_GPU2D_OFFSET(offset));

  ASSERT_DBG_STATE(hgpu2d->global_state, HAL_GPU2D_STATE_INIT);

  GPU2D_WRITE_REG(hgpu2d, offset, value);

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup GPU2D_Exported_Functions_Group3
  * @{
A set of function to handle the GPU2D interruptions :
  - HAL_GPU2D_IRQHandler()     : Handle GPU2D interrupt request.
  - HAL_GPU2D_ERR_IRQHandler() : Handle GPU2D Error interrupt request.
  */

/**
  * @brief  Handles GPU2D interrupt request.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  */
void HAL_GPU2D_IRQHandler(hal_gpu2d_handle_t *hgpu2d)
{
  uint32_t last_cl_id;
  uint32_t isr_flags;

  ASSERT_DBG_PARAM(hgpu2d != NULL);

  isr_flags = GPU2D_READ_REG(hgpu2d, HAL_GPU2D_ITCTRL);

  /* Command List Complete Interrupt management */
  if ((isr_flags & HAL_GPU2D_FLAG_CLC) != 0U)
  {
    HAL_GPU2D_ClearFlag(hgpu2d, HAL_GPU2D_FLAG_CLC);

    last_cl_id = GPU2D_READ_REG(hgpu2d, HAL_GPU2D_CLID);

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
    hgpu2d->command_list_cplt_cb(hgpu2d, last_cl_id);
#else
    HAL_GPU2D_CommandListCpltCallback(hgpu2d, last_cl_id);
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle GPU2D Error interrupt request.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  */
void HAL_GPU2D_ERR_IRQHandler(hal_gpu2d_handle_t *hgpu2d)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
  hgpu2d->error_cb(hgpu2d);
#else
  HAL_GPU2D_ErrorCallback(hgpu2d);
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */
}

#if defined (USE_HAL_GPU2D_REGISTER_CALLBACKS) && (USE_HAL_GPU2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the GPU2D command list complete callback to be used instead of
  *         the weak HAL_GPU2D_CommandListCpltCallback() predefined callback.
  * @param  hgpu2d              Pointer to a hal_gpu2d_handle_t structure
  * @param  p_callback          Pointer to the hal_gpu2d_clc_cb_t Callback function
  * @retval HAL_INVALID_PARAM   Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK              GPU2D command list complete callback is successfully stored
  */
hal_status_t HAL_GPU2D_RegisterCommandListCpltCallback(hal_gpu2d_handle_t *hgpu2d, hal_gpu2d_clc_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgpu2d->command_list_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the GPU2D Error callback to be used instead of
  *         the weak HAL_GPU2D_ErrorCallback() predefined callback.
  * @param  hgpu2d              Pointer to a hal_gpu2d_handle_t structure
  * @param  p_callback          Pointer to the hal_gpu2d_cb_t Callback function
  * @retval HAL_INVALID_PARAM   Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK              GPU2D error callback is successfully stored
  */
hal_status_t HAL_GPU2D_RegisterErrorCallback(hal_gpu2d_handle_t *hgpu2d, hal_gpu2d_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgpu2d->error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_GPU2D_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup GPU2D_Exported_Functions_Group4
  * @{
A set of Weak functions (or default Callbacks functions if USE_HAL_GPU2D_REGISTER_CALLBACKS is set to 0 or no defined)
which are used to asynchronously inform the application.
The HAL GPU2D driver provides these callbacks as weak empty functions. When needed these functions are to be implemented
in the user file:
  - HAL_GPU2D_ErrorCallback()           : GPU2D Error handler callback.
  - HAL_GPU2D_CommandListCpltCallback() : GPU2D Command List Complete callback.
  */

/**
  * @brief  GPU2D Command List Complete callback.
  * @param  hgpu2d       Pointer to a hal_gpu2d_handle_t structure
  * @param  cmd_list_id  Command list ID that got completed
  */
__WEAK void HAL_GPU2D_CommandListCpltCallback(hal_gpu2d_handle_t *hgpu2d, uint32_t cmd_list_id)
{
  STM32_UNUSED(hgpu2d);
  STM32_UNUSED(cmd_list_id);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_GPU2D_CommandListCpltCallback could be implemented in the user file.
   */
}

/**
  * @brief  GPU2D Error handler callback.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  */
__WEAK void HAL_GPU2D_ErrorCallback(hal_gpu2d_handle_t *hgpu2d)
{
  STM32_UNUSED(hgpu2d);
  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_GPU2D_ErrorCallback could be implemented in the user file.
   */
}
/**
  * @}
  */

/** @addtogroup GPU2D_Exported_Functions_Group5
  * @{
This subsection provides function allowing to
 - HAL_GPU2D_GetState() : Check the GPU2D global state.
  */

/**
  * @brief  Return the GPU2D global state.
  * @param  hgpu2d             Pointer to a hal_gpu2d_handle_t structure
  * @retval hal_gpu2d_state_t  GPU2D global state
  */
hal_gpu2d_state_t HAL_GPU2D_GetState(const hal_gpu2d_handle_t *hgpu2d)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);

  return hgpu2d->global_state;
}
/**
  * @}
  */

#if defined (USE_HAL_GPU2D_USER_DATA) && (USE_HAL_GPU2D_USER_DATA == 1)
/** @addtogroup GPU2D_Exported_Functions_Group6
  * @{
A set of functions allowing to manage a user data pointer stored to the GPU2D handle:
 - HAL_GPU2D_SetUserData() Set the user data into the handle
 - HAL_GPU2D_GetUserData() Get the user data from the handle
  */

/**
  * @brief  Set the user data pointer into the handle.
  * @param  hgpu2d       Pointer to a hal_gpu2d_handle_t structure
  * @param  p_user_data  Pointer to the user data
  */
void HAL_GPU2D_SetUserData(hal_gpu2d_handle_t *hgpu2d, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);

  hgpu2d->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer from the handle.
  * @param  hgpu2d  Pointer to a hal_gpu2d_handle_t structure
  * @retval Pointer to the user data.
  */
const void *HAL_GPU2D_GetUserData(const hal_gpu2d_handle_t *hgpu2d)
{
  ASSERT_DBG_PARAM(hgpu2d != NULL);

  return (hgpu2d->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_GPU2D_USER_DATA */

/**
  * @}
  */

#endif /* HAL_GPU2D_MODULE_ENABLED */

/**
  * @}
  */

#endif /* GPU2D */

/**
  * @}
  */
