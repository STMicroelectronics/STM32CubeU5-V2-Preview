/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gfxmmu.c
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Graphic MMU (GFXMMU) peripheral:
  *           + Initialization and de-initialization functions
  *           + Configuration functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2025 STMicroelectronics.
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

/** @addtogroup GFXMMU
  * @{
# GFXMMU peripheral overview
- The GFXMMU is a graphical oriented memory management unit which aims to optimize the memory usage depending on the
  display shape.
- This peripheral allows the microcontroller to store only the visible parts of non-rectangular
  displays in a contiguous physical memory area, reducing the framebuffer memory footprint.

# How to use this driver

## The HAL GFXMMU driver can be used as follows:

- Initialize the GFXMMU handle by calling the HAL_GFXMMU_Init() API that performs these operations:
  - Associate instance to the handle.
  - Enable the GFXMMU clock interface (When USE_HAL_GFXMMU_CLK_ENABLE_MODEL compilation flag is set to
    HAL_CLK_ENABLE_PERIPH_ONLY in the stm32u5xx_hal_conf.h module).
  - When the USE_HAL_GFXMMU_CLK_ENABLE_MODEL is not defined or defined to HAL_CLK_ENABLE_NO,then the user needs to
    enable the GFXMMU clock at application side using the HAL_RCC_GFXMMU_EnableClock API.
  - The initialization of the handle state to the HAL_GFXMMU_STATE_INIT.

- Configure the GFXMMU module with user values:
  - Declare a hal_gfxmmu_config_t structure.
  - Fill all parameters of the declared configuration structure.
  - Call HAL_GFXMMU_SetConfig() function, this function:
    Updates the GFXMMU registers according to the user configuration provided by the input config structure.

- The GFXMMU allows up to four virtual buffers to be set. Each buffer can be associated to a physical address
  by calling HAL_GFXMMU_SetBuffPhysicalAddr().
- The default value to be returned when reading from a virtual memory location that is not physically mapped is set
  by calling HAL_GFXMMU_SetDefaultReturnVal().
- When there is a need to reset the LUT configuration use the HAL_GFXMMU_ResetLutLines(), this function:
    Deactivate all LUT lines (or a range of lines).

- When needed to enable/disable the cache and prefetch mechanism use:
  - HAL_GFXMMU_SetConfigCache() to set the outer cachability or/and bufferability (*).
  - HAL_GFXMMU_EnableCache() to enable the (cache or address cache) (**).
  - HAL_GFXMMU_DisableCache() to disable the (cache or address cache) (**).
  - HAL_GFXMMU_EnableCacheLockBuff() to lock the (cache or address cache) to a buffer (**).
  - HAL_GFXMMU_DisableCacheLockBuff() to unlock the (cache or address cache) from a buffer (**).
  - HAL_GFXMMU_EnablePrefetch() to enable the prefetch mechanism (*).
  - HAL_GFXMMU_DisablePrefetch() to disable the prefetch mechanism (*).
  - HAL_GFXMMU_EnableForceCache() to enable the force cache (*).
  - HAL_GFXMMU_DisableForceCache() to disable the force cache (*).
  - HAL_GFXMMU_InvalidateCache() to invalidate the cache content (*).
  - HAL_GFXMMU_CleanCache() to clean the cache content (*).
  - HAL_GFXMMU_CleanInvalidateCache() to clean and invalidate the cache content (*).

- To deinitialize the GFXMMU peripheral use HAL_GFXMMU_DeInit().

- Retrieve the HAL GFXMMU information:
  - Use HAL_GFXMMU_GetState() to return the GFXMMU state.
  - Use HAL_GFXMMU_GetBuffState() to return the GFXMMU buffers state.
  - Use HAL_GFXMMU_GetLUTState() to return the GFXMMU look up table state.
  - Use HAL_GFXMMU_GetConfig() to get the GFXMMU configurations.
  - HAL_GFXMMU_GetBuffPhysicalAddr() to get the physical buffer address.
  - HAL_GFXMMU_GetDefaultReturnVal() to get the default value when virtual memory location not physically mapped.
  - HAL_GFXMMU_GetConfigCache() to get the cache configuration (*).
  - Use HAL_GFXMMU_IsEnabledCache() to check whether the (cache or address cache) is enabled or not (**).
  - Use HAL_GFXMMU_IsEnabledCacheLockBuff() to check whether the (cache or address cache) is locked or not (**).
  - Use HAL_GFXMMU_IsEnabledForceCache() to check whether the force cache is enabled or not (*).
  - Use HAL_GFXMMU_IsEnabledPrefetch() to check whether the prefetch is enabled or not (*).
 @note
      - (*) feature not available on all devices.
      - (**) the selected cache or address cache is based on the used devices.
             For more information please refer to the section "GFXMMU implementation" in the reference manual.

  - Set the compilation flag USE_HAL_GFXMMU_USER_DATA to 1U in the stm32u5xx_hal_conf.h module
    to allow storing (into the handle) and retrieving the user data respectively through
    the HAL_GFXMMU_SetUserData and HAL_GFXMMU_GetUserData() APIs.

- Register callback:
  - When the compilation flag USE_HAL_GFXMMU_REGISTER_CALLBACKS is set to 1 in the stm32u5xx_hal_conf.h,
    it allows to configure dynamically the driver callbacks instead of using the default ones.
  - Call HAL_GFXMMU_RegisterErrorCallback() to register a user error callback.

## Configuration inside the GFXMMU driver

Config defines                    | Description      | Default value            | Note
--------------------------------- | -----------------| ------------------------ | --------------------------------
PRODUCT                           | from IDE         | NA                       | Ex:STM32U5XX.
USE_ASSERT_DBG_PARAM              | from IDE         | NA                       | Enable the parameters asserts.
USE_ASSERT_DBG_STATE              | from IDE         | NA                       | Enable the state asserts.
USE_HAL_CHECK_PARAM               | from hal_conf.h  | 0                        | Parameters runtime check.
USE_HAL_GFXMMU_MODULE             | from hal_conf.h  | 1                        | Enable the HAL GFXMMU module.
USE_HAL_GFXMMU_CLK_ENABLE_MODEL   | from hal_conf.h  | HAL_CLK_ENABLE_NO        | Enable the HAL_GFXMMU_CLK.
USE_HAL_GFXMMU_REGISTER_CALLBACKS | from hal_conf.h  | 0                        | Enable the register callbacks assert.
USE_HAL_GFXMMU_GET_LAST_ERRORS    | from hal_conf.h  | 0                        | Allows to get the last errors codes.
USE_HAL_GFXMMU_USER_DATA          | from hal_conf.h  | 0                        | Allows to Enable/Disable user data.
  */

#if defined(USE_HAL_GFXMMU_MODULE) && (USE_HAL_GFXMMU_MODULE == 1U)
#if defined (GFXMMU)

/* Private define ----------------------------------------------------------------------------------------------------*/
/** @defgroup GFXMMU_Private_Constants GFXMMU Private Constants
  * @{
  */
/**
  * @brief  GFXMMU Mask for interrupt
  */
#define GFXMMU_CR_ITS_MASK          (GFXMMU_CR_B0OIE | GFXMMU_CR_B1OIE | GFXMMU_CR_B2OIE | GFXMMU_CR_B3OIE \
                                     | GFXMMU_CR_AMEIE)

/**
  * @brief  GFXMMU Max line number
  */
#define HAL_GFXMM_LUT_LINES_NBR     1024U
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup GFXMMU_Private_Macros GFXMMU Private Macros
  * @{
  */

/*! Check the number of blocks per line */
#define IS_GFXMMU_BLOCKS_PER_LINE(value) (((value) == HAL_GFXMMU_BLOCK_PER_LINE_192) \
                                          || ((value) == HAL_GFXMMU_BLOCK_PER_LINE_256))

/*! Check the lut line */
#define IS_GFXMMU_LUT_LINE(value) ((value) < HAL_GFXMM_LUT_LINES_NBR)

/*! Check the lut size */
#define IS_GFXMMU_LUT_SIZE(value) ((value) <= HAL_GFXMM_LUT_LINES_NBR)

/*! The address must be 4 bytes aligned */
#define IS_GFXMMU_BUFFER_ADDRESS(value) (((value) & 0xFU) == 0U)

/*! Check the buffer index */
#define IS_GFXMMU_BUFFER(value) (((value) == HAL_GFXMMU_BUFF_0) \
                                 || ((value) == HAL_GFXMMU_BUFF_1) \
                                 || ((value) == HAL_GFXMMU_BUFF_2) \
                                 || ((value) == HAL_GFXMMU_BUFF_3))

#if defined(GFXMMU_CR_CE)

/*! Check the outer bufferability */
#define IS_GFXMMU_OUTER_BUFFERABILITY(value) (((value) == HAL_GFXMMU_OUTER_BUFFERABILITY_DISABLE) \
                                              || ((value) == HAL_GFXMMU_OUTER_BUFFERABILITY_ENABLE))

/*! Check the outer cachability */
#define IS_GFXMMU_OUTER_CACHABILITY(value) (((value) == HAL_GFXMMU_OUTER_CACHABILITY_DISABLE) \
                                            || ((value) == HAL_GFXMMU_OUTER_CACHABILITY_ENABLE))
#endif /* GFXMMU_CR_CE */

/*! Get the handle instance */
#define GFXMMU_GET_INSTANCE(handle) ((GFXMMU_TypeDef *)((uint32_t)(handle)->instance))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup GFXMMU_Exported_Functions
  * @{
  */

/** @addtogroup GFXMMU_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the GFXMMU peripheral:
- HAL_GFXMMU_Init() to initialize the selected HAL GFXMMU handle and associate a GFXMMU peripheral instance.
- HAL_GFXMMU_DeInit() to de-initialize the given HAL GFXMMU instance and reset the state machine.
  */

/**
  * @brief  Initialize the GFXMMU handle and associates an instance.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  instance          one of the values of the enumeration @ref hal_gfxmmu_t.
  * @retval HAL_OK GFXMMU     handle has been correctly initialized.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_GFXMMU_Init(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_t instance)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_ALL_INSTANCE((GFXMMU_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hgfxmmu == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxmmu->instance = instance;
  hgfxmmu->first_line = 0U;
  hgfxmmu->lut_size_lines = 0U;
  hgfxmmu->lut = NULL;
#if defined (USE_HAL_GFXMMU_CLK_ENABLE_MODEL) && (USE_HAL_GFXMMU_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_GFXMMU_EnableClock();
#endif /* USE_HAL_GFXMMU_CLK_ENABLE_MODEL */

#if defined(USE_HAL_GFXMMU_REGISTER_CALLBACKS) && (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1U)
  hgfxmmu->p_error_cb = HAL_GFXMMU_ErrorCallback;
#endif /* USE_HAL_GFXMMU_REGISTER_CALLBACKS */

#if defined(USE_HAL_GFXMMU_GET_LAST_ERRORS) && (USE_HAL_GFXMMU_GET_LAST_ERRORS== 1U)
  hgfxmmu->last_error_codes = HAL_GFXMMU_ERROR_NONE;
#endif /* USE_HAL_GFXMMU_GET_LAST_ERRORS */

  for (uint32_t i = 0U; i < HAL_GFXMMU_BUFF_NBR; i++)
  {
    hgfxmmu->buff_states[i] = HAL_GFXMMU_BUFF_STATE_RESET;
  }
  hgfxmmu->lut_state = HAL_GFXMMU_LUT_STATE_RESET;

  hgfxmmu->global_state = HAL_GFXMMU_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the GFXMMU peripheral.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  */
void HAL_GFXMMU_DeInit(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_ALL_INSTANCE(GFXMMU_GET_INSTANCE(hgfxmmu)));

  CLEAR_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR);
  CLEAR_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->DVR);
  WRITE_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->FCR, 0x1FU);

  for (uint32_t i = 0UL; i < HAL_GFXMM_LUT_LINES_NBR; i++)
  {
    CLEAR_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->LUT[2U * i]);
    CLEAR_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->LUT[(2U * i) + 1U]);
  }

  for (uint32_t i = 0UL; i < HAL_GFXMMU_BUFF_NBR; i++)
  {
    CLEAR_REG(*(&(GFXMMU_GET_INSTANCE(hgfxmmu)->B0CR) + i));
    hgfxmmu->buff_states[i] = HAL_GFXMMU_BUFF_STATE_RESET;
  }
  hgfxmmu->lut_state = HAL_GFXMMU_LUT_STATE_RESET;

  hgfxmmu->global_state = HAL_GFXMMU_STATE_RESET;

}
/**
  * @}
  */

/** @addtogroup GFXMMU_Exported_Functions_Group2
  * @{
This subsection provides a set of APIs allowing to configure the GFXMMU peripheral:

- HAL_GFXMMU_SetConfig() to configure the GFXMMU with the specified parameters in the @ref hal_gfxmmu_config_t.
- HAL_GFXMMU_GetConfig() to get the GFXMMU configurations.
- HAL_GFXMMU_SetLUT() to configure the LUT with the specified parameters in the @ref hal_gfxmmu_lut_config_t.
- HAL_GFXMMU_SetBuffPhysicalAddr() to set a physical address of a given logical buffer.
- HAL_GFXMMU_GetBuffPhysicalAddr() to get the physical address associated to a given logical buffer.
- HAL_GFXMMU_SetDefaultReturnVal() to set the default value that is returned when virtual memory location is not
  physically mapped.
- HAL_GFXMMU_GetDefaultReturnVal() to get the default value when virtual memory location is not physically mapped.
- HAL_GFXMMU_ResetLutLines() to deactivate all LUT lines (or a range of lines).
- HAL_GFXMMU_SetConfigCache() to set the outer cachability or/and bufferability.
- HAL_GFXMMU_GetConfigCache() to get the cache configuration.
- HAL_GFXMMU_EnableCache() to Enable the cache.
- HAL_GFXMMU_IsEnabledCache() to check whether the cache is enabled or not.
- HAL_GFXMMU_EnableCacheLockBuff() to lock the cache to a buffer.
- HAL_GFXMMU_IsEnabledCacheLockBuff() to check whether the cache lock is enabled or not.
- HAL_GFXMMU_EnablePrefetch() to enable the prefetch mechanism.
- HAL_GFXMMU_IsEnabledPrefetch() to check whether the prefetch is enabled or not.
- HAL_GFXMMU_EnableForceCache() to enable the force cache (*).
- HAL_GFXMMU_IsEnabledForceCache() to check whether the force cache is enabled or not.
- HAL_GFXMMU_InvalidateCache() to invalidate the cache content.
- HAL_GFXMMU_CleanCache() to clean the cache content.
- HAL_GFXMMU_CleanInvalidateCache() to clean and invalidate the cache content.
 @note - (*) For more information about this feature please refer to the subsection Cache maintenance operation in
             the reference manual.
  */

/**
  * @brief  Configure the GFXMMU configuration with the specified parameters in the @ref hal_gfxmmu_config_t.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  p_config          pointer to @ref hal_gfxmmu_config_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_GFXMMU_SetConfig(hal_gfxmmu_handle_t *hgfxmmu, const hal_gfxmmu_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_BLOCKS_PER_LINE(p_config->blocks_per_line));

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t) HAL_GFXMMU_STATE_INIT | (uint32_t) HAL_GFXMMU_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, 1U << GFXMMU_CR_192BM_Pos, (uint32_t)p_config->blocks_per_line);

  hgfxmmu->global_state = HAL_GFXMMU_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the GFXMMU configuration and fill parameters in the @ref hal_gfxmmu_config_t.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  p_config          pointer to @ref hal_gfxmmu_config_t structure.
  */
void HAL_GFXMMU_GetConfig(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);


  p_config->blocks_per_line = (hal_gfxmmu_block_per_line_t)((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR,
                                                                               GFXMMU_CR_192BM));

}

/**
  * @brief  Configure the LUT with the specified parameters in the @ref hal_gfxmmu_lut_config_t.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  p_config          pointer to @ref hal_gfxmmu_lut_config_t structure.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_GFXMMU_SetLUT(hal_gfxmmu_handle_t *hgfxmmu, const hal_gfxmmu_lut_config_t *p_config)
{
  uint32_t current_line;
  uint32_t counter;

  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_LUT_LINE(p_config->first_line));
  ASSERT_DBG_PARAM(IS_GFXMMU_LUT_LINE((p_config->lut_size_lines) + (p_config->first_line)));
  ASSERT_DBG_PARAM((p_config->lut) != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t) HAL_GFXMMU_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hgfxmmu->first_line = p_config->first_line;
  hgfxmmu->lut_size_lines = p_config->lut_size_lines;
  hgfxmmu->lut = p_config->lut;
  current_line = p_config->first_line;
  counter = 0;

  while (current_line < (p_config->first_line + p_config->lut_size_lines))
  {
    WRITE_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->LUT[2U * current_line], p_config->lut[counter].lut_low.raw);
    WRITE_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->LUT[(2U * current_line) + 1U], p_config->lut[counter].lut_high.raw);
    current_line++;
    counter++;
  }

  hgfxmmu->lut_state = HAL_GFXMMU_LUT_STATE_ACTIVE;

  return HAL_OK;
}

/**
  * @brief  Set the physical buffer address.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  buff              one of the values of the enumeration @ref hal_gfxmmu_buff_t.
  * @param  buff_physical_addr physical address associated to the buffer.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_SetBuffPhysicalAddr(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff,
                                            uint32_t buff_physical_addr)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_BUFFER(buff));

  ASSERT_DBG_STATE(hgfxmmu->global_state, HAL_GFXMMU_STATE_CONFIGURED);

  WRITE_REG(*((&GFXMMU_GET_INSTANCE(hgfxmmu)->B0CR) + (uint32_t)buff), buff_physical_addr);

  hgfxmmu->buff_states[buff] = HAL_GFXMMU_BUFF_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the buffer physical address.
  * @param  hgfxmmu        pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  buff           one of the values of the enumeration @ref hal_gfxmmu_buff_t.
  * @retval buffer physical address.
  */
uint32_t HAL_GFXMMU_GetBuffPhysicalAddr(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_BUFFER(buff));

  ASSERT_DBG_STATE(hgfxmmu->global_state, HAL_GFXMMU_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hgfxmmu->buff_states[buff], HAL_GFXMMU_BUFF_STATE_CONFIGURED);

  return  READ_REG(*((&GFXMMU_GET_INSTANCE(hgfxmmu)->B0CR) + (uint32_t)buff));
}

/**
  * @brief  Set the default return value.
  * @param  hgfxmmu    pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  val        value returned when virtual memory location not physically mapped.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_SetDefaultReturnVal(hal_gfxmmu_handle_t *hgfxmmu, uint32_t val)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  WRITE_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->DVR, val);

  return HAL_OK;
}

/**
  * @brief  Get the default return value.
  * @param  hgfxmmu    pointer to @ref hal_gfxmmu_handle_t structure.
  * @retval uint32_t default return value.
  */
uint32_t HAL_GFXMMU_GetDefaultReturnVal(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  return READ_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->DVR);
}

/**
  * @brief  Disable a range of LUT lines.
  * @param  hgfxmmu     pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  start_line  first line to disable on LUT.
  * @param  lines_nbr   number of lines to disable on LUT.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_ResetLutLines(hal_gfxmmu_handle_t *hgfxmmu, uint32_t start_line, uint32_t lines_nbr)
{
  uint32_t current_line;

  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_LUT_LINE(start_line));
  ASSERT_DBG_PARAM(IS_GFXMMU_LUT_LINE(lines_nbr));
  ASSERT_DBG_PARAM(IS_GFXMMU_LUT_SIZE(start_line + lines_nbr));

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  current_line = start_line;

  while (current_line < (start_line + lines_nbr))
  {
    CLEAR_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->LUT[2U * current_line]);
    CLEAR_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->LUT[(2U * current_line) + 1U]);
    current_line++;
  }

  return HAL_OK;
}

/**
  * @brief  Enable cache or address cache.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @note   the selected cache or address cache is based on the used devices.
  *         For more information please refer to the section "GFXMMU implementation" in the reference manual.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_EnableCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

#if defined(GFXMMU_CR_CE)
  SET_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_CE);
#endif /* GFXMMU_CR_CE */

#if defined(GFXMMU_CR_ACE)
  SET_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_ACE);
#endif /* GFXMMU_CR_ACE */

  return HAL_OK;
}

/**
  * @brief  Disable cache or address cache.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @note   the selected cache or address cache is based on the used devices.
  *         For more information please refer to the section "GFXMMU implementation" in the reference manual.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_DisableCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

#if defined(GFXMMU_CR_CE)
  CLEAR_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_CE);
#endif /* GFXMMU_CR_CE */
#if defined(GFXMMU_CR_ACE)
  CLEAR_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_ACE);
#endif /* GFXMMU_CR_ACE */
  return HAL_OK;
}

/**
  * @brief  Check the cache or the address cache status.
  * @param  hgfxmmu                   pointer to @ref hal_gfxmmu_handle_t structure.
  * @note   the selected cache or address cache is based on the used devices.
  *         For more information please refer to the section "GFXMMU implementation" in the reference manual.
  * @retval HAL_GFXMMU_CACHE_ENABLED  cache is enabled.
  * @retval HAL_GFXMMU_CACHE_DISABLED cache is disabled.
  */
hal_gfxmmu_cache_status_t HAL_GFXMMU_IsEnabledCache(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

#if defined(GFXMMU_CR_CE)
  return ((hal_gfxmmu_cache_status_t)((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_CE)));
#endif /* GFXMMU_CR_CE */
#if defined(GFXMMU_CR_ACE)
  return ((hal_gfxmmu_cache_status_t)((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_ACE)));
#endif /* GFXMMU_CR_ACE */
}

/**
  * @brief  Lock the cache or the address cache to a buffer.
  * @param  hgfxmmu   pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  buff    one of the values of the enumeration @ref hal_gfxmmu_buff_t.
  * @note   the selected cache or address cache is based on the used devices.
  *         For more information please refer to the section "GFXMMU implementation" in the reference manual.
  * @retval HAL_OK    cache lock has been correctly configured.
  * @retval HAL_ERROR configuration fail.
  */
hal_status_t HAL_GFXMMU_EnableCacheLockBuff(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_BUFFER(buff));

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

#if defined(GFXMMU_CR_CE)
  if ((READ_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR) & GFXMMU_CR_CE) != GFXMMU_CR_CE)
  {
    return HAL_ERROR;
  }

  MODIFY_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, (GFXMMU_CR_CL | GFXMMU_CR_CLB),
             (GFXMMU_CR_CL | ((uint32_t)buff << GFXMMU_CR_CLB_Pos)));
#else
  if ((READ_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR) & GFXMMU_CR_ACE) != GFXMMU_CR_ACE)
  {
    return HAL_ERROR;
  }

  MODIFY_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_ACLB, ((uint32_t)buff << GFXMMU_CR_ACLB_Pos));
#endif /* GFXMMU_CR_CE */
  return HAL_OK;
}

/**
  * @brief  Unlock the cache or the address cache from a buffer.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @note   the selected cache or address cache is based on the used devices.
  *         For more information please refer to the section "GFXMMU implementation" in the reference manual.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_DisableCacheLockBuff(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, HAL_GFXMMU_STATE_CONFIGURED);

#if defined(GFXMMU_CR_CE)
  CLEAR_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, (GFXMMU_CR_CL | GFXMMU_CR_CLB));
#else
  CLEAR_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_ACLB);
#endif /* GFXMMU_CR_CE */
  return HAL_OK;
}

/**
  * @brief  Check whether the cache or the address cache is locked or not.
  * @param  hgfxmmu                        pointer to @ref hal_gfxmmu_handle_t structure.
  * @note   the selected cache or address cache is based on the used devices.
  *         For more information please refer to the section "GFXMMU implementation" in the reference manual.
  * @retval HAL_GFXMMU_CACHE_LOCK_ENABLED  cache is enabled.
  * @retval HAL_GFXMMU_CACHE_LOCK_DISABLED cache is disabled.
  */
hal_gfxmmu_cache_lock_status_t HAL_GFXMMU_IsEnabledCacheLockBuff(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

#if defined(GFXMMU_CR_CE)

  return ((hal_gfxmmu_cache_lock_status_t)((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_CL)));
#else
  if ((READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_ACE) &  GFXMMU_CR_ACE) != GFXMMU_CR_ACE)
  {
    return HAL_GFXMMU_CACHE_LOCK_DISABLED;
  }
  return HAL_GFXMMU_CACHE_LOCK_ENABLED;
#endif /* GFXMMU_CR_CE */

}

#if defined(GFXMMU_CR_CE)
/**
  * @brief  Set the cache configuration with the specified parameters in the @ref hal_gfxmmu_cache_config_t.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  p_config          pointer to @ref hal_gfxmmu_cache_config_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK            configuration succeeded.
  * @retval HAL_INVALID_PARAM invalid parameter.
  */
hal_status_t HAL_GFXMMU_SetConfigCache(hal_gfxmmu_handle_t *hgfxmmu, const hal_gfxmmu_cache_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXMMU_OUTER_CACHABILITY(p_config->outer_cachability));
  ASSERT_DBG_PARAM(IS_GFXMMU_OUTER_BUFFERABILITY(p_config->outer_bufferability));

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, (GFXMMU_CR_OB | GFXMMU_CR_OC),
             ((uint32_t)(p_config->outer_cachability) | (uint32_t)(p_config->outer_bufferability)));

  return HAL_OK;
}

/**
  * @brief  Get the cache configuration and fill parameters in the @ref hal_gfxmmu_cache_config_t.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  p_config          pointer to @ref hal_gfxmmu_cache_config_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  */
void HAL_GFXMMU_GetConfigCache(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_cache_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  p_config->outer_cachability = ((hal_gfxmmu_outer_cachability_t)
                                 ((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_OC)));
  p_config->outer_bufferability = ((hal_gfxmmu_outer_bufferability_t)
                                   ((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_OB)));
}

/**
  * @brief  Enable Prefetch.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_EnablePrefetch(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  CLEAR_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_PD);

  return HAL_OK;
}

/**
  * @brief  Disable prefetch.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_DisablePrefetch(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  SET_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_PD);

  return HAL_OK;
}

/**
  * @brief  Check the prefetch status.
  * @param  hgfxmmu                      pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_GFXMMU_PREFETCH_ENABLED  prefetch is enabled.
  * @retval HAL_GFXMMU_PREFETCH_DISABLED prefetch is disabled.
  */
hal_gfxmmu_prefetch_status_t HAL_GFXMMU_IsEnabledPrefetch(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);
  return ((hal_gfxmmu_prefetch_status_t)((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_PD)));
}

/**
  * @brief  Enable the force cache to make the operation on the locked buffer always cacheable.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK    configuration succeeded.
  * @retval HAL_ERROR cache lock is disabled.
  */
hal_status_t HAL_GFXMMU_EnableForceCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  /* Check if the cache lock is enabled */
  if (READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_CL) != GFXMMU_CR_CL)
  {
    return HAL_ERROR;
  }

  SET_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_FC);
  return HAL_OK;
}

/**
  * @brief  Disable the force cache.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK.
  */
hal_status_t HAL_GFXMMU_DisableForceCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  CLEAR_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_FC);

  return HAL_OK;
}

/**
  * @brief  Check the the force cache status.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_GFXMMU_CACHE_FORCE_ENABLED  force cache is enabled.
  * @retval HAL_GFXMMU_CACHE_FORCE_DISABLED force cache is disabled.
  */
hal_gfxmmu_cache_force_status_t HAL_GFXMMU_IsEnabledForceCache(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, (uint32_t)HAL_GFXMMU_STATE_CONFIGURED);

  return ((hal_gfxmmu_cache_force_status_t)((uint32_t)READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_FC)));
}

/**
  * @brief  Force invalidate of cache.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK configuration succeeded.
  * @retval HAL_ERROR configuration fail.
  */
hal_status_t HAL_GFXMMU_InvalidateCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, HAL_GFXMMU_STATE_CONFIGURED);

  /* Check if the cache lock is enabled */
  if (READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_FC) != GFXMMU_CR_FC)
  {
    return HAL_ERROR;
  }

  SET_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CCR, GFXMMU_CCR_FI);

  return HAL_OK;
}

/**
  * @brief  Force flush of cache.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK configuration succeeded.
  * @retval HAL_ERROR configuration fail.
  */
hal_status_t HAL_GFXMMU_CleanCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, HAL_GFXMMU_STATE_CONFIGURED);

  /* Check if the cache lock is enabled */
  if (READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_FC) != GFXMMU_CR_FC)
  {
    return HAL_ERROR;
  }

  SET_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CCR, GFXMMU_CCR_FF);
  return HAL_OK;
}

/**
  * @brief  Force flush and invalidate of cache.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @warning This feature is not available on all devices.For more information please refer to the section
  *          GFXMMU implementation in the reference manual.
  * @retval HAL_OK configuration succeeded.
  * @retval HAL_ERROR configuration fail.
  */
hal_status_t HAL_GFXMMU_CleanInvalidateCache(hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  ASSERT_DBG_STATE(hgfxmmu->global_state, HAL_GFXMMU_STATE_CONFIGURED);

  /* Check if the cache lock is enabled */
  if (READ_BIT(GFXMMU_GET_INSTANCE(hgfxmmu)->CR, GFXMMU_CR_FC) != GFXMMU_CR_FC)
  {
    return HAL_ERROR;
  }

  MODIFY_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CCR, (GFXMMU_CCR_FF | GFXMMU_CCR_FI), (GFXMMU_CCR_FF | GFXMMU_CCR_FI));
  return HAL_OK;
}

#endif /* GFXMMU_CR_CE*/

/**
  * @}
  */

/** @addtogroup GFXMMU_Exported_Functions_Group3
  * @{
This subsection provides a set the GFXMMU callbacks registration APIs:
- HAL_GFXMMU_IRQHandler() to handle the interrupt request.
- HAL_GFXMMU_RegisterErrorCallback() to register callback function for interrupts when error occurs.
  */

/**
  * @brief  Handles GFXMMU interrupt request.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  */
void HAL_GFXMMU_IRQHandler(hal_gfxmmu_handle_t *hgfxmmu)
{
  uint32_t flags, interrupts, error;

  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  /* Read current flags and interrupts and determine which error occurs */
  flags = READ_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->SR);
  interrupts = (READ_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->CR) & GFXMMU_CR_ITS_MASK);
  error = (flags & interrupts);

  if (error != 0U)
  {
    /* Clear flags on GFXMMU_FCR register */
    WRITE_REG(GFXMMU_GET_INSTANCE(hgfxmmu)->FCR, error);
#if defined(USE_HAL_GFXMMU_GET_LAST_ERRORS) && (USE_HAL_GFXMMU_GET_LAST_ERRORS == 1U)
    /* Update GFXMMU error code */
    hgfxmmu->last_error_codes |= error;
#endif /* USE_HAL_GFXMMU_GET_LAST_ERRORS */

    /* Call GFXMMU error callback */
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
    hgfxmmu->p_error_cb(hgfxmmu);
#else
    HAL_GFXMMU_ErrorCallback(hgfxmmu);
#endif /* USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1 */
  }
}

/**
  * @brief  GFXMMU error callback.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  */
__WEAK void HAL_GFXMMU_ErrorCallback(hal_gfxmmu_handle_t *hgfxmmu)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hgfxmmu);

  /** WARNING: This function must not be modified, when the callback is needed,
    *          the HAL_GFXMMU_ErrorCallback could be implemented in the user file.
    */
}

#if defined (USE_HAL_GFXMMU_REGISTER_CALLBACKS) && (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User GFXMMU callback.
  * @param  hgfxmmu           pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  callback          pointer to the callback function
  * @retval HAL_OK            succeed.
  * @retval HAL_INVALID_PARAM invalid callback.
  */
hal_status_t HAL_GFXMMU_RegisterErrorCallback(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_cb_t callback)
{
  ASSERT_DBG_PARAM((hgfxmmu != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxmmu->p_error_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_GFXMMU_REGISTER_CALLBACKS*/

/**
  * @}
  */

/** @addtogroup GFXMMU_Exported_Functions_Group4
  * @{
This subsection provides a set of functions to retrieve the state and the error codes
- HAL_GFXMMU_GetState() to get the global state of the current GFXMMU peripheral.
- HAL_GFXMMU_GetBuffState() to get the buffer state.
- HAL_GFXMMU_GetLUTState() to get the lut state.
- HAL_GFXMMU_GetLastErrorCodes() to get the last error code of the GFXMMU peripheral.
  */

/**
  * @brief  Get the current GFXMMU handle state.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @retval hal_gfxmmu_state_t GFXMMU global state.
  */
hal_gfxmmu_state_t HAL_GFXMMU_GetState(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  return hgfxmmu->global_state;
}

/**
  * @brief  Get the current buffer state.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @param  buff    buffer index.
  * @retval hal_gfxmmu_buff_state_t GFXMMU buffer state.
  */
hal_gfxmmu_buff_state_t HAL_GFXMMU_GetBuffState(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  return hgfxmmu->buff_states[buff];
}

/**
  * @brief  Get the current lut state.
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @retval hal_gfxmmu_lut_state_t GFXMMU lut state.
  */
hal_gfxmmu_lut_state_t HAL_GFXMMU_GetLUTState(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);
  return hgfxmmu->lut_state;
}

#if defined(USE_HAL_GFXMMU_GET_LAST_ERRORS) && (USE_HAL_GFXMMU_GET_LAST_ERRORS == 1U)
/**
  * @brief  Return the GFXMMU handle error code.
  * @param  hgfxmmu  pointer to @ref hal_gfxmmu_handle_t structure.
  * @retval uint32_t GFXMMU last error codes which can be one of the following value @ref GFXMMU_Error_Code
  *
  */
uint32_t HAL_GFXMMU_GetLastErrorCodes(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  return (hgfxmmu->last_error_codes);
}
#endif /* USE_HAL_GFXMMU_GET_LAST_ERRORS */

/**
  * @}
  */
#if defined (USE_HAL_GFXMMU_USER_DATA) && (USE_HAL_GFXMMU_USER_DATA == 1U)
/** @addtogroup GFXMMU_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to Set and Get user data:
- HAL_GFXMMU_SetUserData() store user data pointer into the handle.
- HAL_GFXMMU_GetUserData() get user data pointer from the handle.
  */
/**
  * @brief Store the user data into the GFXMMU handle
  * @param hgfxmmu       pointer to @ref hal_gfxmmu_handle_t structure.
  * @param p_user_data   pointer to the user data
  */
void HAL_GFXMMU_SetUserData(hal_gfxmmu_handle_t *hgfxmmu, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  hgfxmmu->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data from the GFXMMU handle
  * @param  hgfxmmu pointer to @ref hal_gfxmmu_handle_t structure.
  * @retval Pointer to the user data
  */
const void *HAL_GFXMMU_GetUserData(const hal_gfxmmu_handle_t *hgfxmmu)
{
  ASSERT_DBG_PARAM(hgfxmmu != NULL);

  return (hgfxmmu->p_user_data);
}

/**
  * @}
  */
#endif /* USE_HAL_GFXMMU_USER_DATA */
/**
  * @}
  */

#endif /* GFXMMU */
#endif /* USE_HAL_GFXMMU_MODULE */
/**
  * @}
  */

/**
  * @}
  */
