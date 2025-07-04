/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dma2d.h
  * @brief   Header file of DMA2D HAL module.
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
#ifndef STM32U5XX_HAL_DMA2D_H
#define STM32U5XX_HAL_DMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_dma2d.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (DMA2D)

/** @defgroup DMA2D DMA2D
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Constants DMA2D Exported Constants
  * @{
  */

#if defined (USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
/** @defgroup DMA2D_Error_Code DMA2D Error Code
  * @{
  */
#define HAL_DMA2D_ERROR_NONE     0x00000000U          /*!< No error             */
#define HAL_DMA2D_ERROR_TE       LL_DMA2D_FLAG_TEIF   /*!< Transfer error       */
#define HAL_DMA2D_ERROR_CE       LL_DMA2D_FLAG_CEIF   /*!< Configuration error  */
#define HAL_DMA2D_ERROR_CAE      LL_DMA2D_FLAG_CAEIF  /*!< CLUT access error    */
/**
  * @}
  */
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */

/**
  * @}
  */


/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Types DMA2D Exported Types
  * @{
  */

/**
  * @brief  HAL DMA2D Global state
  */
typedef enum
{
  HAL_DMA2D_STATE_RESET                 = 0U << 0U,     /*!< DMA2D not yet initialized                    */
  HAL_DMA2D_STATE_IDLE                  = 1U << 31U,    /*!< DMA2D Configured and ready for use           */
  HAL_DMA2D_STATE_XFER_ACTIVE           = 1U << 30U,    /*!< DMA2D processing one of the 6 Xfer modes     */
  HAL_DMA2D_STATE_XFER_SUSPEND          = 1U << 29U,    /*!< DMA2D Xfer suspended                         */
  HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE   = 1U << 28U,    /*!< DMA2D Loading the FG or BG CLUT              */
  HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND  = 1U << 27U     /*!< DMA2D CLUT Loading suspended                 */
} hal_dma2d_state_t;

/**
  * @brief HAL DMA2D Instance Definition
  */
typedef enum
{
  HAL_DMA2D = (uint32_t)DMA2D /*!< Instance DMA2D  */
} hal_dma2d_t;

typedef struct hal_dma2d_handle_s hal_dma2d_handle_t; /*!< DMA2D Handle type Definition */

#if defined(USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/*! DMA2D process callback type definition */
typedef void (*hal_dma2d_cb_t)(hal_dma2d_handle_t *hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

/**
  * @brief DMA2D handle Structure Definition
  */
struct hal_dma2d_handle_s
{
  hal_dma2d_t                 instance;     /*!< DMA2D instance */

  volatile hal_dma2d_state_t  global_state; /*!< DMA2D global state */

  uint32_t           cfg_xfer_mode;         /*!< DMA2D configured transfer mode */

#if defined(USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
  volatile uint32_t last_error_codes;       /*!< DMA2D error codes   */
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */

#if defined(USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
  hal_dma2d_cb_t              p_xfer_cplt_cb;         /*!< DMA2D transfer complete callback */
  hal_dma2d_cb_t              p_error_cb;             /*!< DMA2D error callback */
  hal_dma2d_cb_t              p_watermark_cb;         /*!< DMA2D line watermark callback */
#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
  hal_dma2d_cb_t              p_clut_loading_cplt_cb; /*!< DMA2D CLUT loading complete callback */
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

#if defined(USE_HAL_DMA2D_USER_DATA) && (USE_HAL_DMA2D_USER_DATA == 1)
  const void                  *p_user_data; /*!< DMA2D  user data */
#endif /* USE_HAL_DMA2D_USER_DATA */
};

/**
  * @brief DMA2D CLUT Color Mode Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_CLUT_COLOR_ARGB8888          = LL_DMA2D_CLUT_COLOR_MODE_ARGB8888,  /*!< ARGB8888 DMA2D CLUT color mode */
  HAL_DMA2D_CLUT_COLOR_RGB888            = LL_DMA2D_CLUT_COLOR_MODE_RGB888     /*!< RGB888 DMA2D CLUT color mode   */
} hal_dma2d_clut_color_mode_t;

/**
  * @brief DMA2D Input Source Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_INPUT_BG      = 0x00U,   /*!< Background input source   */
  HAL_DMA2D_INPUT_FG      = 0x01U    /*!< Foreground input source   */
} hal_dma2d_input_t;

/**
  * @brief DMA2D Input Color Mode Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_INPUT_COLOR_ARGB8888   = LL_DMA2D_INPUT_MODE_ARGB8888,                        /*!< ARGB8888 color mode   */
  HAL_DMA2D_INPUT_COLOR_RGB888     = LL_DMA2D_INPUT_MODE_RGB888,                          /*!< RGB888 color mode     */
  HAL_DMA2D_INPUT_COLOR_RGB565     = LL_DMA2D_INPUT_MODE_RGB565,                          /*!< RGB565 color mode     */
  HAL_DMA2D_INPUT_COLOR_ARGB1555   = LL_DMA2D_INPUT_MODE_ARGB1555,                        /*!< ARGB1555 color mode   */
  HAL_DMA2D_INPUT_COLOR_ARGB4444   = LL_DMA2D_INPUT_MODE_ARGB4444,                        /*!< ARGB4444 color mode   */
  HAL_DMA2D_INPUT_COLOR_ABGR8888   = LL_DMA2D_INPUT_MODE_ARGB8888 | LL_DMA2D_RB_MODE_SWAP,/*!< ABGR8888 color mode   */
  HAL_DMA2D_INPUT_COLOR_BGR888     = LL_DMA2D_INPUT_MODE_RGB888   | LL_DMA2D_RB_MODE_SWAP,/*!< BGR888 color mode     */
  HAL_DMA2D_INPUT_COLOR_BGR565     = LL_DMA2D_INPUT_MODE_RGB565   | LL_DMA2D_RB_MODE_SWAP,/*!< BGR565 color mode     */
  HAL_DMA2D_INPUT_COLOR_ABGR1555   = LL_DMA2D_INPUT_MODE_ARGB1555 | LL_DMA2D_RB_MODE_SWAP,/*!< ABGR1555 color mode   */
  HAL_DMA2D_INPUT_COLOR_ABGR4444   = LL_DMA2D_INPUT_MODE_ARGB4444 | LL_DMA2D_RB_MODE_SWAP,/*!< ABGR4444 color mode   */
  HAL_DMA2D_INPUT_COLOR_L8         = LL_DMA2D_INPUT_MODE_L8,                              /*!< L8 color mode         */
  HAL_DMA2D_INPUT_COLOR_AL44       = LL_DMA2D_INPUT_MODE_AL44,                            /*!< AL44 color mode       */
  HAL_DMA2D_INPUT_COLOR_AL88       = LL_DMA2D_INPUT_MODE_AL88,                            /*!< AL88 color mode       */
  HAL_DMA2D_INPUT_COLOR_L4         = LL_DMA2D_INPUT_MODE_L4,                              /*!< L4 color mode         */
  HAL_DMA2D_INPUT_COLOR_A8         = LL_DMA2D_INPUT_MODE_A8,                              /*!< A8 color mode         */
  HAL_DMA2D_INPUT_COLOR_A4         = LL_DMA2D_INPUT_MODE_A4,                              /*!< A4 color mode         */
#if defined(DMA2D_FGPFCCR_CSS)
  HAL_DMA2D_INPUT_COLOR_YCBCR_444  = LL_DMA2D_INPUT_MODE_YCBCR | LL_DMA2D_CSS_444, /*!< YCbCr color mode with CSS_444*/
  HAL_DMA2D_INPUT_COLOR_YCBCR_422  = LL_DMA2D_INPUT_MODE_YCBCR | LL_DMA2D_CSS_422, /*!< YCbCr color mode with CSS_422*/
  HAL_DMA2D_INPUT_COLOR_YCBCR_420  = LL_DMA2D_INPUT_MODE_YCBCR | LL_DMA2D_CSS_420  /*!< YCbCr color mode with CSS_420*/
#endif /* DMA2D_FGPFCCR_CSS  */
} hal_dma2d_input_color_mode_t;

/**
  * @brief DMA2D Input Alpha Mode Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_INPUT_ALPHA_NO_MODIF  = LL_DMA2D_ALPHA_MODE_NO_MODIF,  /*!< No modification of the alpha value        */
  HAL_DMA2D_INPUT_ALPHA_REPLACE   = LL_DMA2D_ALPHA_MODE_REPLACE,   /*!< Replace original alpha value by programmed
                                                                         alpha value                              */
  HAL_DMA2D_INPUT_ALPHA_COMBINE   = LL_DMA2D_ALPHA_MODE_COMBINE    /*!< Combine programmed alpha value with
                                                                          original alpha value                    */
} hal_dma2d_input_alpha_mode_t;

/**
  * @brief DMA2D Output Color Mode Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_OUTPUT_COLOR_ARGB8888 = LL_DMA2D_OUTPUT_MODE_ARGB8888,                         /*!< ARGB8888 color mode  */
  HAL_DMA2D_OUTPUT_COLOR_RGB888   = LL_DMA2D_OUTPUT_MODE_RGB888,                           /*!< RGB888 color mode    */
  HAL_DMA2D_OUTPUT_COLOR_RGB565   = LL_DMA2D_OUTPUT_MODE_RGB565,                           /*!< RGB565 color mode    */
  HAL_DMA2D_OUTPUT_COLOR_ARGB1555 = LL_DMA2D_OUTPUT_MODE_ARGB1555,                         /*!< ARGB1555 color mode  */
  HAL_DMA2D_OUTPUT_COLOR_ARGB4444 = LL_DMA2D_OUTPUT_MODE_ARGB4444,                         /*!< ARGB4444 color mode  */
  HAL_DMA2D_OUTPUT_COLOR_ABGR8888 = LL_DMA2D_OUTPUT_MODE_ARGB8888 | LL_DMA2D_RB_MODE_SWAP, /*!< ABGR8888 color mode  */
  HAL_DMA2D_OUTPUT_COLOR_BGR888   = LL_DMA2D_OUTPUT_MODE_RGB888   | LL_DMA2D_RB_MODE_SWAP, /*!< BGR888 color mode    */
  HAL_DMA2D_OUTPUT_COLOR_BGR565   = LL_DMA2D_OUTPUT_MODE_RGB565   | LL_DMA2D_RB_MODE_SWAP, /*!< BGR565 color mode    */
  HAL_DMA2D_OUTPUT_COLOR_ABGR1555 = LL_DMA2D_OUTPUT_MODE_ARGB1555 | LL_DMA2D_RB_MODE_SWAP, /*!< ABGR1555 color mode  */
  HAL_DMA2D_OUTPUT_COLOR_ABGR4444 = LL_DMA2D_OUTPUT_MODE_ARGB4444 | LL_DMA2D_RB_MODE_SWAP  /*!< ABGR4444 color mode  */
} hal_dma2d_output_color_mode_t;

/**
  * @brief DMA2D Inputs and Output Alpha Inversion Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_ALPHA_INVERSION_DISABLED  = 0x00U,  /*!< No modification of the alpha value */
  HAL_DMA2D_ALPHA_INVERSION_ENABLED   = 0x01U   /*!< Invert the alpha value             */
} hal_dma2d_alpha_inversion_status_t;

/**
  * @brief DMA2D Inputs and Output Line Offset Mode Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_LINE_OFFSET_PIXELS   = LL_DMA2D_LINE_OFFSET_PIXELS,    /*!< Line offsets expressed in pixels */
  HAL_DMA2D_LINE_OFFSET_BYTES    = LL_DMA2D_LINE_OFFSET_BYTES      /*!< Line offsets expressed in bytes  */
} hal_dma2d_line_offset_mode_t;

/**
  * @brief DMA2D Output Byte Swap Mode Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_BYTE_SWAP_DISABLED         = 0x00U,  /*!< Bytes are in regular order in output FIFO */
  HAL_DMA2D_BYTE_SWAP_ENABLED          = 0x01U   /*!< Bytes are swapped two by two in output FIFO */
} hal_dma2d_byte_swap_status_t;

/**
  * @brief DMA2D WaterMark Status Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_WATER_MARK_DISABLED         = 0x00U,           /*!< Disable the transfer watermark interrupt */
  HAL_DMA2D_WATER_MARK_ENABLED          = 0x01U            /*!< Enable the transfer watermark interrupt  */
} hal_dma2d_watermark_status_t;

/**
  * @brief DMA2D Dead Time Status Enumeration Definition
  */
typedef enum
{
  HAL_DMA2D_DEAD_TIME_DISABLED          = 0x00U,  /*!< Disable the dead time between two consecutive accesses
                                                       on the AHB master port                          */
  HAL_DMA2D_DEAD_TIME_ENABLED           = 0x01U   /*!< Enable the dead time between two consecutive accesses
                                                       on the AHB master port                          */
} hal_dma2d_dead_time_status_t;

/**
  * @brief DMA2D CLUT Configuration Structure Definition
  */
typedef struct
{
  uint32_t                    *p_clut;         /*!< Configures the DMA2D CLUT memory address. */
  hal_dma2d_clut_color_mode_t color_mode;      /*!< Configures the DMA2D CLUT color mode.
                                                    This parameter can be one value of
                                                    @ref hal_dma2d_clut_color_mode_t. */
  uint8_t                     size;            /*!< Configures the DMA2D CLUT size.
                                                     This parameter must be a number between
                                                     Min_Data = 0x00 and Max_Data = 0xFF. */
} hal_dma2d_clut_config_t;

/**
  * @brief DMA2D Input Source Configuration Structure Definition
  */
typedef struct
{
  const void                        *p_src;            /*!< Configures the input source address                       */
  hal_dma2d_input_alpha_mode_t      alpha_mode;        /*!< Configures the DMA2D foreground or background alpha mode.
                                                          This parameter can be one value of
                                                          @ref hal_dma2d_input_alpha_mode_t.                          */
  uint32_t                          alpha_value;       /*!< Specifies the DMA2D foreground or background alpha value.
                                                          This parameter must be a number between Min_Data = 0x00
                                                          and Max_Data = 0xFF.                                        */
  hal_dma2d_input_color_mode_t      color_mode;        /*!< Configures the DMA2D foreground or background color mode.
                                                          This parameter can be one value of
                                                          @ref hal_dma2d_input_color_mode_t.                          */
  uint32_t                          offset;            /*!< Configures the DMA2D foreground or background offset.
                                                          When the hal_dma2d_line_offset_mode_t is expressed in bytes,
                                                          this parameter must be a number between
                                                          Min_Data = 0x0000 and Max_Data = 0xFFFF.
                                                          When the hal_dma2d_line_offset_mode_t is expressed in pixels,
                                                          this parameter must be a number between
                                                          Min_Data = 0x0000 and Max_Data = 0x3FFF.                    */
} hal_dma2d_input_config_t;

/**
  * @brief DMA2D Output Configuration Structure Definition
  */
typedef struct
{
  const void                        *p_dest;          /*!< Configures the output address                              */
  hal_dma2d_output_color_mode_t     color_mode;       /*!< Configures the color format of the output image.
                                                          This parameter can be one value of
                                                          @ref hal_dma2d_output_color_mode_t.                         */
  uint32_t                          offset;           /*!< Specifies the Offset value.
                                                          When the hal_dma2d_line_offset_mode_t is expressed in bytes,
                                                          this parameter must be a number between
                                                          Min_Data = 0x0000 and Max_Data = 0xFFFF.
                                                          When the hal_dma2d_line_offset_mode_t is expressed in pixels,
                                                          this parameter must be a number between
                                                          Min_Data = 0x0000 and Max_Data = 0x3FFF.                    */
} hal_dma2d_output_config_t;

/**
  * @brief DMA2D Xfer with Blending Mode Configuration Structure Definition
  */
typedef struct
{
  hal_dma2d_input_config_t          fg_input;         /*!< Configures the foreground input structure                */
  hal_dma2d_input_config_t          bg_input;         /*!< Configures the background input structure                */
  hal_dma2d_output_config_t         output;           /*!< Configures the output structure                          */
  uint32_t                          width;            /*!< The width of data to be transferred from source
                                                           to destination (expressed in number of pixels per line). */
  uint32_t                          height;           /*!< The height of data to be transferred from source
                                                           to destination (expressed in number of lines).           */
} hal_dma2d_blending_config_t;
/**
  * @brief DMA2D Xfer with Blending and Fixed Color Modes Configuration Structure Definition
  */
typedef struct
{
  hal_dma2d_input_config_t          mem_input;          /*!< Configures the input source structure                   */
  uint32_t                          fixed_color_argb8888;  /*!< Configures the fixed RGB888 color, and alpha value   */
  hal_dma2d_input_alpha_mode_t      fixed_color_alpha_mode;/*!< Configures the fixed color alpha mode.
                                                            When HAL_DMA2D_INPUT_ALPHA_NO_MODIF is selected, the default
                                                            alpha value 0xFF is set.
                                                            Otherwise, the alpha value of the fixed_color_argb8888
                                                            is applied */
  hal_dma2d_output_config_t         output;             /*!< Configures the output structure                        */
  uint32_t                          width;              /*!< The width of data to be transferred from source
                                                           to destination (expressed in number of pixels per line). */
  uint32_t                          height;             /*!< The height of data to be transferred from source
                                                           to destination (expressed in number of lines).           */
} hal_dma2d_blending_fixed_color_config_t;

/**
  * @brief DMA2D Memory to Memory Xfer Modes Configuration Structure Definition
  */
typedef struct
{
  hal_dma2d_input_config_t          input;           /*!< Configures the foreground input source structure          */
  hal_dma2d_output_config_t         output;          /*!< Configures the output structure                           */
  uint32_t                          width;            /*!< The width of data to be transferred from source
                                                           to destination (expressed in number of pixels per line). */
  uint32_t                          height;           /*!< The height of data to be transferred from source
                                                           to destination (expressed in number of lines).           */
} hal_dma2d_mem_copy_config_t;

/**
  * @brief DMA2D Register to Memory Xfer Mode Configuration Structure Definition
  */
typedef struct
{
  uint32_t                          fixed_color;      /*!< Configures the fixed color
                                                           <b>NOTE:</b> This parameter must be formatted according to
                                                           the selected @ref hal_dma2d_output_color_mode_t            */
  hal_dma2d_output_config_t         output;           /*!< Configures the output structure                          */
  uint32_t                          width;            /*!< The width of data to be transferred from source
                                                           to destination (expressed in number of pixels per line). */
  uint32_t                          height;           /*!< The height of data to be transferred from source
                                                           to destination (expressed in number of lines).           */
} hal_dma2d_mem_fill_config_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Functions DMA2D Exported Functions
  * @{
  */

/** @defgroup DMA2D_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_DMA2D_Init(hal_dma2d_handle_t *hdma2d, hal_dma2d_t instance);
void         HAL_DMA2D_DeInit(hal_dma2d_handle_t *hdma2d);
/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group2 Configuration functions
  * @{
  */
hal_status_t HAL_DMA2D_SetConfigMemCopy(hal_dma2d_handle_t *hdma2d, const hal_dma2d_mem_copy_config_t *p_config);
hal_status_t HAL_DMA2D_SetConfigMemCopyPFC(hal_dma2d_handle_t *hdma2d, const hal_dma2d_mem_copy_config_t *p_config);
hal_status_t HAL_DMA2D_SetConfigMemFill(hal_dma2d_handle_t *hdma2d, const hal_dma2d_mem_fill_config_t *p_config);
hal_status_t HAL_DMA2D_SetConfigBlending(hal_dma2d_handle_t *hdma2d, const hal_dma2d_blending_config_t *p_config);
hal_status_t HAL_DMA2D_SetConfigBlendingFixFGColor(hal_dma2d_handle_t *hdma2d,
                                                   const hal_dma2d_blending_fixed_color_config_t *p_config);
hal_status_t HAL_DMA2D_SetConfigBlendingFixBGColor(hal_dma2d_handle_t *hdma2d,
                                                   const hal_dma2d_blending_fixed_color_config_t *p_config);

/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group3 Process management functions
  * @{
  */

/* Xfer functions  ****************************************************************************************************/
hal_status_t HAL_DMA2D_Start(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_Start_IT(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_Suspend(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_Resume(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_Abort(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_PollForTransfer(hal_dma2d_handle_t *hdma2d, uint32_t timeout_msec);

/* CLUT functions  ****************************************************************************************************/
hal_status_t HAL_DMA2D_StartCLUTLoad(hal_dma2d_handle_t *hdma2d, const hal_dma2d_clut_config_t *p_clut_config,
                                     hal_dma2d_input_t input);
hal_status_t HAL_DMA2D_StartCLUTLoad_IT(hal_dma2d_handle_t *hdma2d, const hal_dma2d_clut_config_t *p_clut_config,
                                        hal_dma2d_input_t input);
hal_status_t HAL_DMA2D_SuspendCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input);
hal_status_t HAL_DMA2D_ResumeCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input);
hal_status_t HAL_DMA2D_AbortCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input);
hal_status_t HAL_DMA2D_PollForCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input, uint32_t timeout_msec);
/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group4 IRQ Handlers
  * @{
  */
void HAL_DMA2D_IRQHandler(hal_dma2d_handle_t *hdma2d);
/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group5 Enable/Disable and Set/Get API - Optional features functions
  * @{
  */
hal_status_t HAL_DMA2D_EnableInputAlphaInversion(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input);
hal_status_t HAL_DMA2D_DisableInputAlphaInversion(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input);
hal_dma2d_alpha_inversion_status_t HAL_DMA2D_IsEnabledInputAlphaInversion(const hal_dma2d_handle_t *hdma2d,
                                                                          hal_dma2d_input_t input);

hal_status_t HAL_DMA2D_EnableOutputAlphaInversion(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_DisableOutputAlphaInversion(hal_dma2d_handle_t *hdma2d);
hal_dma2d_alpha_inversion_status_t HAL_DMA2D_IsEnabledOutputAlphaInversion(const hal_dma2d_handle_t *hdma2d);

hal_status_t HAL_DMA2D_SetLineOffsetMode(hal_dma2d_handle_t *hdma2d,
                                         hal_dma2d_line_offset_mode_t line_offset_mode);
hal_dma2d_line_offset_mode_t HAL_DMA2D_GetLineOffsetMode(const hal_dma2d_handle_t *hdma2d);

hal_status_t HAL_DMA2D_EnableOutputByteSwap(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_DisableOutputByteSwap(hal_dma2d_handle_t *hdma2d);
hal_dma2d_byte_swap_status_t HAL_DMA2D_IsEnabledOutputByteSwap(const hal_dma2d_handle_t *hdma2d);

hal_status_t HAL_DMA2D_EnableWaterMark(hal_dma2d_handle_t *hdma2d, uint32_t line);
hal_status_t HAL_DMA2D_DisableWaterMark(hal_dma2d_handle_t *hdma2d);
hal_dma2d_watermark_status_t HAL_DMA2D_IsEnabledWaterMark(const hal_dma2d_handle_t *hdma2d);
uint32_t HAL_DMA2D_GetWaterMarkLine(const hal_dma2d_handle_t *hdma2d);

hal_status_t HAL_DMA2D_EnableDeadTime(hal_dma2d_handle_t *hdma2d);
hal_status_t HAL_DMA2D_DisableDeadTime(hal_dma2d_handle_t *hdma2d);
hal_dma2d_dead_time_status_t HAL_DMA2D_IsEnabledDeadTime(const hal_dma2d_handle_t *hdma2d);

hal_status_t HAL_DMA2D_SetConfigDeadTime(hal_dma2d_handle_t *hdma2d, uint8_t dead_time_cycle);
uint8_t HAL_DMA2D_GetConfigDeadTime(const hal_dma2d_handle_t *hdma2d);

hal_status_t HAL_DMA2D_SetCLUTColorIndex(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input,
                                         uint32_t color_index,
                                         uint32_t color);
uint32_t     HAL_DMA2D_GetCLUTColorIndex(const hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input,
                                         uint32_t color_index);

/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group6 Callback functions
  * @{
  */
/* Register callback APIs *********************************************************************************************/
#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
hal_status_t HAL_DMA2D_RegisterXferCpltCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback);
hal_status_t HAL_DMA2D_RegisterErrorCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback);
hal_status_t HAL_DMA2D_RegisterWaterMarkCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback);
#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
hal_status_t HAL_DMA2D_RegisterCLUTLoadingCpltCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback);
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

void HAL_DMA2D_XferCpltCallback(hal_dma2d_handle_t *hdma2d);
void HAL_DMA2D_ErrorCallback(hal_dma2d_handle_t *hdma2d);
void HAL_DMA2D_WaterMarkCallback(hal_dma2d_handle_t *hdma2d);
#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
void HAL_DMA2D_CLUTLoadingCpltCallback(hal_dma2d_handle_t *hdma2d);
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group7 Peripheral State and Error functions
  * @{
  */
/* Peripheral State functions *****************************************************************************************/
hal_dma2d_state_t HAL_DMA2D_GetState(const hal_dma2d_handle_t *hdma2d);
#if defined(USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
uint32_t HAL_DMA2D_GetLastErrorCodes(const hal_dma2d_handle_t *hdma2d);
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */
/**
  * @}
  */

/** @defgroup DMA2D_Exported_Functions_Group8 Set/Get user data functions
  * @{
  */
/* Set/Get user data functions ****************************************************************************************/
#if defined(USE_HAL_DMA2D_USER_DATA) && (USE_HAL_DMA2D_USER_DATA == 1)
void HAL_DMA2D_SetUserData(hal_dma2d_handle_t *hdma2d, const void *p_user_data);
const void *HAL_DMA2D_GetUserData(const hal_dma2d_handle_t *hdma2d);
#endif /* USE_HAL_DMA2D_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (DMA2D) */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_DMA2D_H */
