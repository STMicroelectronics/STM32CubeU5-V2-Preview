/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gfxmmu.h
  * @brief   Header file of GFXMMU HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_GFXMMU_H
#define STM32U5XX_HAL_GFXMMU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

#if defined (GFXMMU)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup GFXMMU GFXMMU
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GFXMMU_Exported_Constants GFXMMU Exported Constants
  * @{
  */
#if defined(USE_HAL_GFXMMU_GET_LAST_ERRORS) && (USE_HAL_GFXMMU_GET_LAST_ERRORS == 1U)
/** @defgroup GFXMMU_Error_Code GFXMMU Error Code
  * @{
  */
#define HAL_GFXMMU_ERROR_NONE           0x00U                          /*!< No error          */
#define HAL_GFXMMU_ERROR_BUFF0_OVERFLOW GFXMMU_SR_B0OF                 /*!< Buffer 0 overflow */
#define HAL_GFXMMU_ERROR_BUFF1_OVERFLOW GFXMMU_SR_B1OF                 /*!< Buffer 1 overflow */
#define HAL_GFXMMU_ERROR_BUFF2_OVERFLOW GFXMMU_SR_B2OF                 /*!< Buffer 2 overflow */
#define HAL_GFXMMU_ERROR_BUFF3_OVERFLOW GFXMMU_SR_B3OF                 /*!< Buffer 3 overflow */
#define HAL_GFXMMU_ERROR_AHB_MASTER     GFXMMU_SR_AMEF                 /*!< AHB master error  */
/**
  * @}
  */
#endif /* USE_HAL_GFXMMU_GET_LAST_ERRORS */

/** @defgroup GFXMMU_Interrupts GFXMMU interrupts
  * @{
  */

#define HAL_GFXMMU_IT_AHB_MASTER_ERROR GFXMMU_CR_AMEIE                 /*!< AHB master error interrupt  */
#define HAL_GFXMMU_IT_BUFF0_OVERFLOW   GFXMMU_CR_B0OIE                 /*!< Buffer 0 overflow interrupt */
#define HAL_GFXMMU_IT_BUFF1_OVERFLOW   GFXMMU_CR_B1OIE                 /*!< Buffer 1 overflow interrupt */
#define HAL_GFXMMU_IT_BUFF2_OVERFLOW   GFXMMU_CR_B2OIE                 /*!< Buffer 2 overflow interrupt */
#define HAL_GFXMMU_IT_BUFF3_OVERFLOW   GFXMMU_CR_B3OIE                 /*!< Buffer 3 overflow interrupt */
/**
  * @}
  */

/** @defgroup GFXMMU_Flags_sources Flags Sources
  * @{
  */
#define HAL_GFXMMU_FLAG_AHB_MASTER_ERROR GFXMMU_SR_AMEF                 /*!< AHB master error flag  */
#define HAL_GFXMMU_FLAG_BUFF0_OVERFLOW   GFXMMU_SR_B0OF                 /*!< Buffer 0 overflow flag */
#define HAL_GFXMMU_FLAG_BUFF1_OVERFLOW   GFXMMU_SR_B1OF                 /*!< Buffer 1 overflow flag */
#define HAL_GFXMMU_FLAG_BUFF2_OVERFLOW   GFXMMU_SR_B2OF                 /*!< Buffer 2 overflow flag */
#define HAL_GFXMMU_FLAG_BUFF3_OVERFLOW   GFXMMU_SR_B3OF                 /*!< Buffer 3 overflow flag */
/**
  * @}
  */

/** @defgroup  GFXMMU_Buffers_Virtual_Addresses Buffers Virtual Addresses
  * @{
  */
#define HAL_GFXMMU_BUFF0_ADDR   GFXMMU_VIRTUAL_BUFFER0_BASE  /*!< Buffer 0 base address */
#define HAL_GFXMMU_BUFF1_ADDR   GFXMMU_VIRTUAL_BUFFER1_BASE  /*!< Buffer 1 base address */
#define HAL_GFXMMU_BUFF2_ADDR   GFXMMU_VIRTUAL_BUFFER2_BASE  /*!< Buffer 2 base address */
#define HAL_GFXMMU_BUFF3_ADDR   GFXMMU_VIRTUAL_BUFFER3_BASE  /*!< Buffer 3 base address */
/**
  * @}
  */

/** @defgroup GFXMMU_Buffers_Number Buffers Number
  * @{
 */
#define HAL_GFXMMU_BUFF_NBR 4U  /*!< Buffers number */
/**
  * @}
  */
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup GFXMMU_Exported_Types GFXMMU Exported Types
  * @{
  */

/**
  * @brief GFXMMU Instance Definition
  */
typedef enum
{
  HAL_GFXMMU = (uint32_t)GFXMMU /*!< Instance GFXMMU  */
} hal_gfxmmu_t;

/**
  * @brief GFXMMU states definition
  */
typedef enum
{
  HAL_GFXMMU_STATE_RESET      = 0UL,                 /*!< GFXMMU not initialized            */
  HAL_GFXMMU_STATE_INIT       = (1UL << 31U),        /*!< GFXMMU  initialized               */
  HAL_GFXMMU_STATE_CONFIGURED = (1UL << 30U)         /*!< GFXMMU initialized and configured */
} hal_gfxmmu_state_t;

/**
  * @brief  GFXMMU LUT states definition
  */
typedef enum
{
  HAL_GFXMMU_LUT_STATE_RESET      = (1UL << 31U),    /*!< LUT not configured */
  HAL_GFXMMU_LUT_STATE_ACTIVE     = (1UL << 30U),    /*!< LUT active         */
} hal_gfxmmu_lut_state_t;

/**
  * @brief GFXMMU buffer states definition
  */
typedef enum
{
  HAL_GFXMMU_BUFF_STATE_RESET      = (1UL << 31U),     /*!< Buff not configured */
  HAL_GFXMMU_BUFF_STATE_CONFIGURED = (1UL << 30U)      /*!< Buff configured     */
} hal_gfxmmu_buff_state_t;

/**
  * @brief GFXMMU blocks per line
  */
typedef enum
{
  HAL_GFXMMU_BLOCK_PER_LINE_192 = GFXMMU_CR_192BM,              /*!< 192 blocks of 16 bytes per line */
  HAL_GFXMMU_BLOCK_PER_LINE_256 = (0U << GFXMMU_CR_192BM_Pos)   /*!< 256 blocks of 16 bytes per line */
} hal_gfxmmu_block_per_line_t;

/**
  * @brief  GFXMMU buffers index
  */
typedef enum
{
  HAL_GFXMMU_BUFF_0 = 0U,          /*!< Buffer 0 */
  HAL_GFXMMU_BUFF_1 = 1U,          /*!< Buffer 1 */
  HAL_GFXMMU_BUFF_2 = 2U,          /*!< Buffer 2 */
  HAL_GFXMMU_BUFF_3 = 3U           /*!< Buffer 3 */
} hal_gfxmmu_buff_t;

/**
  * @brief  GFXMMU config structure definition
  */
typedef struct
{
  hal_gfxmmu_block_per_line_t blocks_per_line;     /*!< Number of blocks of 16 bytes per line */
} hal_gfxmmu_config_t;

/**
  * @brief GFXMMU cache status
  */
typedef enum
{
  HAL_GFXMMU_CACHE_DISABLED = 0x00U,
#if defined(GFXMMU_CR_CE)
  HAL_GFXMMU_CACHE_ENABLED  = GFXMMU_CR_CE
#else
  HAL_GFXMMU_CACHE_ENABLED  = GFXMMU_CR_ACE
#endif /* GFXMMU_CR_CE */
} hal_gfxmmu_cache_status_t;

/**
  * @brief GFXMMU cache lock status
  */
typedef enum
{
  HAL_GFXMMU_CACHE_LOCK_DISABLED = 0x00U,
#if defined(GFXMMU_CR_CE)
  HAL_GFXMMU_CACHE_LOCK_ENABLED  = GFXMMU_CR_CL
#else
  HAL_GFXMMU_CACHE_LOCK_ENABLED  = GFXMMU_CR_ACLB
#endif /* GFXMMU_CR_CE */
} hal_gfxmmu_cache_lock_status_t;

#if defined(GFXMMU_CR_CE)
/**
  * @brief GFXMMU bufferability status
  */
typedef enum
{
  HAL_GFXMMU_OUTER_BUFFERABILITY_DISABLE = 0x00U,          /*!< No bufferable */
  HAL_GFXMMU_OUTER_BUFFERABILITY_ENABLE  = GFXMMU_CR_OB    /*!< Bufferable    */
} hal_gfxmmu_outer_bufferability_t;

/**
  * @brief GFXMMU cachability status
  */
typedef enum
{
  HAL_GFXMMU_OUTER_CACHABILITY_DISABLE = 0x00U,        /*!< No cacheable */
  HAL_GFXMMU_OUTER_CACHABILITY_ENABLE  = GFXMMU_CR_OC  /*!< Cacheable    */
} hal_gfxmmu_outer_cachability_t;

/**
  * @brief GFXMMU cache structure definition
  */
typedef struct
{
  hal_gfxmmu_outer_bufferability_t outer_bufferability; /*!< Bufferability of an access generated by the GFXMMU cache */

  hal_gfxmmu_outer_cachability_t outer_cachability;     /*!< Cachability of an access generated by the GFXMMU cache   */
} hal_gfxmmu_cache_config_t;

/**
  * @brief GFXMMU cache force status
  */
typedef enum
{
  HAL_GFXMMU_CACHE_FORCE_DISABLED = 0x00U,
  HAL_GFXMMU_CACHE_FORCE_ENABLED  = GFXMMU_CR_FC
} hal_gfxmmu_cache_force_status_t;

/**
  * @brief GFXMMU prefetch status
  */
typedef enum
{
  HAL_GFXMMU_PREFETCH_DISABLED = GFXMMU_CR_PD,
  HAL_GFXMMU_PREFETCH_ENABLED  = 0x00U
} hal_gfxmmu_prefetch_status_t;

#endif /* GFXMMU_CR_CE */

/**
  * @brief  GFXMMU LUT line structure definition
  */
typedef struct
{
  union
  {
    uint32_t raw;                        /*!< 32-bit word - GFXMMU LUT line low element                          */
    struct
    {
      uint32_t line_enable: 1;           /*!< 1-bit - Enable/disable the current line                            */

      uint32_t: 7;                       /*!< 7-bit - Reserved field                                             */

      uint32_t first_visible_block: 8;   /*!< 8-bit - First visible block on this line.
                                              This parameter must be a number between Min_Data = 0 and Max_Data = 255
                                                                                                                 */

      uint32_t last_visible_block: 8;    /*!< 8-bit - Last visible block on this line.
                                         This parameter must be a number between Min_Data = 0 and Max_Data = 255 */

      uint32_t: 8;                       /*!< 8-bit - Reserved field                                             */
    } fields;
  } lut_low;                             /*!< GFXMMU LUT line low                                                */

  union
  {
    uint32_t raw;                 /*!< 32-bit word - GFXMMU LUT line high element                                */
    struct
    {
      uint32_t: 4;                /*!< 4-bit - Reserved field                                                    */

      uint32_t line_offset: 18;    /*!< 18-bit - Offset of block 0 of the current line in physical buffer
                                        This parameter must be a number between Min_Data = -4080 and Max_Data = 4190208
                                        @note Line offset must be computed with the following formula:
                                        LineOffset = [(Blocks already used) - (1st visible block)]*BlockSize
                                                                                                                 */

      uint32_t: 10;               /*!< 10-bit - Reserved field                                                   */
    } fields;
  } lut_high;                     /*!< GFXMMU LUT line high                                                      */
} hal_gfxmmu_lut_t;

/**
  * @brief  GFXMMU config structure definition
  */
typedef struct
{
  uint32_t first_line;                             /*!< First line covered by the LUT         */

  hal_gfxmmu_lut_t *lut;                           /*!< GFXMMU LUT lines structure            */

  uint32_t lut_size_lines;                         /*!< Size of lut in lines                  */

}
hal_gfxmmu_lut_config_t;

typedef struct hal_gfxmmu_handle_s hal_gfxmmu_handle_t; /*!< GFXMMU handle structure type */
#if defined(USE_HAL_GFXMMU_REGISTER_CALLBACKS) && (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1U)
/*! GFXMMU process callback type definition */
typedef void (*hal_gfxmmu_cb_t)(hal_gfxmmu_handle_t *gfxmmu);
#endif /* USE_HAL_gfxmmu_REGISTER_CALLBACKS */

/**
  * @brief  GFXMMU handle structure definition
  */
struct hal_gfxmmu_handle_s
{
  hal_gfxmmu_t                          instance;                             /*!< GFXMMU instance               */
  volatile hal_gfxmmu_state_t           global_state;                         /*!< GFXMMU global state           */
  volatile hal_gfxmmu_buff_state_t      buff_states[HAL_GFXMMU_BUFF_NBR];     /*!< GFXMMU buffers state          */
  volatile hal_gfxmmu_lut_state_t       lut_state;                            /*!< GFXMMU lut state              */
  uint32_t                              first_line;                           /*!< First line covered by the LUT */
  uint32_t                              lut_size_lines;                       /*!< Size of lut in lines          */
  hal_gfxmmu_lut_t                      *lut;                                 /*!< GFXMMU LUT lines structure    */
#if defined(USE_HAL_GFXMMU_GET_LAST_ERRORS) && (USE_HAL_GFXMMU_GET_LAST_ERRORS == 1U)
  volatile uint32_t          last_error_codes;                                /*!< GFXMMU last error codes       */
#endif /* USE_HAL_GFXMMU_REGISTER_CALLBACKS */
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1U)
  hal_gfxmmu_cb_t               p_error_cb;                                   /*!< GFXMMU error callback         */
#endif /* USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1U */
#if defined(USE_HAL_GFXMMU_USER_DATA) && (USE_HAL_GFXMMU_USER_DATA == 1U)
  const void                 *p_user_data;                                    /*!< GFXMMU user data              */
#endif /* USE_HAL_GFXMMU_USER_DATA */
};

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GFXMMU_Exported_Functions GFXMMU Exported Functions
  * @{
  */

/** @defgroup GFXMMU_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
/* Initialization and de-initialization functions */
hal_status_t HAL_GFXMMU_Init(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_t instance);
void HAL_GFXMMU_DeInit(hal_gfxmmu_handle_t *hgfxmmu);
/**
  * @}
  */

/** @defgroup GFXMMU_Exported_Functions_Group2 Operations functions
  * @{
  */
/* Operation functions */
hal_status_t HAL_GFXMMU_SetConfig(hal_gfxmmu_handle_t *hgfxmmu, const hal_gfxmmu_config_t *p_config);
void HAL_GFXMMU_GetConfig(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_config_t *p_config);

hal_status_t HAL_GFXMMU_SetLUT(hal_gfxmmu_handle_t *hgfxmmu, const hal_gfxmmu_lut_config_t *p_config);

hal_status_t HAL_GFXMMU_SetBuffPhysicalAddr(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff,
                                            uint32_t buff_physical_addr);
uint32_t HAL_GFXMMU_GetBuffPhysicalAddr(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff);

hal_status_t HAL_GFXMMU_SetDefaultReturnVal(hal_gfxmmu_handle_t *hgfxmmu, uint32_t val);
uint32_t HAL_GFXMMU_GetDefaultReturnVal(const hal_gfxmmu_handle_t *hgfxmmu);

hal_status_t HAL_GFXMMU_ResetLutLines(hal_gfxmmu_handle_t *hgfxmmu, uint32_t start_line, uint32_t lines_nbr);

hal_status_t HAL_GFXMMU_EnableCache(hal_gfxmmu_handle_t *hgfxmmu);
hal_status_t HAL_GFXMMU_DisableCache(hal_gfxmmu_handle_t *hgfxmmu);
hal_gfxmmu_cache_status_t HAL_GFXMMU_IsEnabledCache(const hal_gfxmmu_handle_t *hgfxmmu);

hal_status_t HAL_GFXMMU_EnableCacheLockBuff(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff);
hal_status_t HAL_GFXMMU_DisableCacheLockBuff(hal_gfxmmu_handle_t *hgfxmmu);
hal_gfxmmu_cache_lock_status_t HAL_GFXMMU_IsEnabledCacheLockBuff(const hal_gfxmmu_handle_t *hgfxmmu);

#if defined(GFXMMU_CR_CE)
hal_status_t HAL_GFXMMU_SetConfigCache(hal_gfxmmu_handle_t *hgfxmmu, const hal_gfxmmu_cache_config_t *p_config);
void HAL_GFXMMU_GetConfigCache(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_cache_config_t *p_config);

hal_status_t HAL_GFXMMU_EnablePrefetch(hal_gfxmmu_handle_t *hgfxmmu);
hal_status_t HAL_GFXMMU_DisablePrefetch(hal_gfxmmu_handle_t *hgfxmmu);
hal_gfxmmu_prefetch_status_t HAL_GFXMMU_IsEnabledPrefetch(const hal_gfxmmu_handle_t *hgfxmmu);

hal_status_t HAL_GFXMMU_EnableForceCache(hal_gfxmmu_handle_t *hgfxmmu);
hal_status_t HAL_GFXMMU_DisableForceCache(hal_gfxmmu_handle_t *hgfxmmu);
hal_gfxmmu_cache_force_status_t HAL_GFXMMU_IsEnabledForceCache(const hal_gfxmmu_handle_t *hgfxmmu);

hal_status_t HAL_GFXMMU_InvalidateCache(hal_gfxmmu_handle_t *hgfxmmu);

hal_status_t HAL_GFXMMU_CleanCache(hal_gfxmmu_handle_t *hgfxmmu);

hal_status_t HAL_GFXMMU_CleanInvalidateCache(hal_gfxmmu_handle_t *hgfxmmu);
#endif /* GFXMMU_CR_CE */
/**
  * @}
  */

/** @defgroup GFXMMU_Exported_Functions_Group3 IRQHandler and callback function
  * @{
  */
void HAL_GFXMMU_IRQHandler(hal_gfxmmu_handle_t *hgfxmmu);
#if defined(USE_HAL_GFXMMU_REGISTER_CALLBACKS) && (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1U)
hal_status_t HAL_GFXMMU_RegisterErrorCallback(hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_cb_t callback);
#endif /* USE_HAL_GFXMMU_REGISTER_CALLBACKS */
void HAL_GFXMMU_ErrorCallback(hal_gfxmmu_handle_t *hgfxmmu);
/**
  * @}
  */

/** @defgroup GFXMMU_Exported_Functions_Group4 State functions
  * @{
  */
/* State function */
hal_gfxmmu_state_t HAL_GFXMMU_GetState(const hal_gfxmmu_handle_t *hgfxmmu);
hal_gfxmmu_buff_state_t HAL_GFXMMU_GetBuffState(const hal_gfxmmu_handle_t *hgfxmmu, hal_gfxmmu_buff_t buff);
hal_gfxmmu_lut_state_t HAL_GFXMMU_GetLUTState(const hal_gfxmmu_handle_t *hgfxmmu);

#if defined(USE_HAL_GFXMMU_GET_LAST_ERRORS) && (USE_HAL_GFXMMU_GET_LAST_ERRORS == 1U)
uint32_t HAL_GFXMMU_GetLastErrorCodes(const hal_gfxmmu_handle_t *hgfxmmu);
#endif /* USE_HAL_GFXMMU_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined (USE_HAL_GFXMMU_USER_DATA) && (USE_HAL_GFXMMU_USER_DATA == 1U)
/** @defgroup GFXMMU_Exported_Functions_Group5 User Data functions
  * @{
  */
void HAL_GFXMMU_SetUserData(hal_gfxmmu_handle_t *hgfxmmu, const void *p_user_data);
const void *HAL_GFXMMU_GetUserData(const hal_gfxmmu_handle_t *hgfxmmu);
/**
  * @}
  */
#endif /* USE_HAL_GFXMMU_USER_DATA */

/** @defgroup GFXMMU_Exported_Functions_Group6 Interrupt functions
  * @{
This subsection provides a set of APIs allowing to manage the GFXMMU interrupts and flags:

- HAL_GFXMMU_EnableIT() to enable the specified GFXMMU interrupt
- HAL_GFXMMU_DisableIT() to disable the specified GFXMMU interrupt
- HAL_GFXMMU_IsEnabledIT() to check whether the specified GFXMMU interrupt source is enabled or not
- HAL_GFXMMU_IsActiveFlag() to Check whether the specified GFXMMU flag is set or not
- HAL_GFXMMU_ClearFlag() to clear the GFXMMU pending flags
  */

/** @brief  Enable the specified GFXMMU interrupt
  * @param  hgfxmmu specifies the GFXMMU handle
  * @param  it_source specifies the GFXMMU interrupt source to enable
  *          This parameter can be a combination of the following values:
  *            @arg HAL_GFXMMU_IT_AHB_MASTER_ERROR: AHB master error interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER0_OVERFLOW: Buffer 0 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER1_OVERFLOW: Buffer 1 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER2_OVERFLOW: Buffer 2 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER3_OVERFLOW: Buffer 3 overflow interrupt
  */
__STATIC_INLINE void HAL_GFXMMU_EnableIT(hal_gfxmmu_handle_t *hgfxmmu, uint32_t it_source)
{
  SET_BIT(((GFXMMU_TypeDef *)((uint32_t) hgfxmmu->instance))->CR, it_source);
}

/** @brief  Disable the specified GFXMMU interrupt
  * @param  hgfxmmu specifies the GFXMMU handle
  * @param  it_source specifies the GFXMMU interrupt source to disable
  *          This parameter can be a combination of the following values:
  *            @arg HAL_GFXMMU_IT_AHB_MASTER_ERROR: AHB master error interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER0_OVERFLOW: Buffer 0 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER1_OVERFLOW: Buffer 1 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER2_OVERFLOW: Buffer 2 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER3_OVERFLOW: Buffer 3 overflow interrupt
  */
__STATIC_INLINE void HAL_GFXMMU_DisableIT(hal_gfxmmu_handle_t *hgfxmmu, uint32_t it_source)
{
  CLEAR_BIT(((GFXMMU_TypeDef *)((uint32_t) hgfxmmu->instance))->CR, it_source);
}

/** @brief  Check whether the specified GFXMMU interrupt source is enabled or not
  * @param  hgfxmmu specifies the GFXMMU handle
  * @param  it_source specifies the GFXMMU interrupt source to check
  *          This parameter must be one of the following values:
  *            @arg HAL_GFXMMU_IT_AHB_MASTER_ERROR: AHB master error interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER0_OVERFLOW: Buffer 0 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER1_OVERFLOW: Buffer 1 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER2_OVERFLOW: Buffer 2 overflow interrupt
  *            @arg HAL_GFXMMU_IT_BUFFER3_OVERFLOW: Buffer 3 overflow interrupt
  * @retval The new state of it_source (SET or RESET)
  */
__STATIC_INLINE uint32_t HAL_GFXMMU_IsEnabledIT(const hal_gfxmmu_handle_t *hgfxmmu, uint32_t it_source)
{
  return (uint32_t)((READ_BIT(((GFXMMU_TypeDef *)((uint32_t)hgfxmmu->instance))->CR,
                              it_source) == it_source) ? 1U : 0U);
}

/**
  * @brief Check whether the specified GFXMMU flag is set or not
  * @param  hgfxmmu specifies the GFXMMU handle
  * @param flag Specifies the flag source to check
  *          This parameter must be one of the following values:
  *            @arg HAL_GFXMMU_FLAG_AHB_MASTER_ERROR: AHB master error flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER0_OVERFLOW: Buffer 0 overflow flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER1_OVERFLOW: Buffer 1 overflow flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER2_OVERFLOW: Buffer 2 overflow flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER3_OVERFLOW: Buffer 3 overflow flag
  * @retval The new state of GFXMMU_FLAG (SET or RESET)
  */
__STATIC_INLINE uint32_t HAL_GFXMMU_IsActiveFlag(const hal_gfxmmu_handle_t *hgfxmmu, uint32_t flag)
{
  return (uint32_t)((READ_BIT(((GFXMMU_TypeDef *)((uint32_t)hgfxmmu->instance))->SR,
                              flag) == flag) ? 1U : 0U);
}

/**
  * @brief Clear the GFXMMU pending flags.
  * @param  hgfxmmu specifies the GFXMMU handle
  * @param flag Specifies the flag source to check
  *          This parameter can be a combination of the following values:
  *            @arg HAL_GFXMMU_FLAG_AHB_MASTER_ERROR: AHB master error flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER0_OVERFLOW: Buffer 0 overflow flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER1_OVERFLOW: Buffer 1 overflow flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER2_OVERFLOW: Buffer 2 overflow flag
  *            @arg HAL_GFXMMU_FLAG_BUFFER3_OVERFLOW: Buffer 3 overflow flag
  */
__STATIC_INLINE void HAL_GFXMMU_ClearFlag(hal_gfxmmu_handle_t *hgfxmmu, uint32_t flag)
{
  SET_BIT(((GFXMMU_TypeDef *)((uint32_t) hgfxmmu->instance))->FCR, flag);
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

#endif /* GFXMMU */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_GFXMMU_H */
