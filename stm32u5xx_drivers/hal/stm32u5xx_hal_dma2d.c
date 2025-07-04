/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dma2d.c
  * @brief   DMA2D HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Chrom-ART Accelerator (DMA2D) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
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

# How to use the DMA2D HAL module driver

## The DMA2D HAL driver can be used as follows:

- Declare a hal_dma2d_handle_t handle structure, for example:  hal_dma2d_handle_t  hdma2d;

- Initialize the DMA2D low level resources :
  - Enable the DMA2D interface clock (if not enabled in HAL_DMA2D_Init() when USE_HAL_DMA2D_CLK_ENABLE_MODEL
  set to HAL_CLK_ENABLE_NO)

- Use HAL_DMA2D_Init() function to initialize the DMA2D handle and associate the physical instance.

__For DMA2D transfer:__
- Configure the DMA2D driver according to the desired transfer mode by setting one of the following structure :
 - hal_dma2d_blending_config_t : for a DMA2D transfer with blending of the foreground and background input images
 - hal_dma2d_blending_fixed_color_config_t : for a DMA2D transfer with blending of one of the input sources image
 (on the foreground or background) and a fixed color on the other input
 - hal_dma2d_mem_copy_config_t : for a DMA2D transfer aiming to copy an image with or without Pixel Format Conversion
 - hal_dma2d_mem_fill_config_t : for a DMA2D transfer aiming to fill an area with a fixed color

- Then call one of the following dedicated configuration API
 - HAL_DMA2D_SetConfigMemCopy(); to configure a transfer for memory-to-memory without Pixel Format Conversion.
 - HAL_DMA2D_SetConfigMemCopyPFC(); to configure a transfer for memory-to-memory with Pixel Format Conversion.
 - HAL_DMA2D_SetConfigMemFill(); to configure a transfer for memory fill with a fixed color.
 - HAL_DMA2D_SetConfigBlending(); to configure a transfer with bending of the two input (foreground and background)
 - HAL_DMA2D_SetConfigBlendingFixFGColor(); to configure a transfer for bending an image from the background input
 with a fixed color on the foreground input
 - HAL_DMA2D_SetConfigBlendingFixBGColor(); to configure a transfer for bending an image from the foreground input
 with a fixed color on the background input

- And finally start the DMA2D transfer by calling HAL_DMA2D_Start() or HAL_DMA2D_Start_IT()

__For DMA2D CLUT Loading:__
- Configure the DMA2D CLUT configuration structure hal_dma2d_clut_config_t
- And start the DMA2D CLUT by calling HAL_DMA2D_StartCLUTLoad() or HAL_DMA2D_StartCLUTLoad_IT()

## Callback registration

When the compilation flag **USE_HAL_DMA2D_REGISTER_CALLBACKS** is set to 1,
use Functions **HAL_DMA2D_RegisterXxxCallback()** to register an interrupt callback.

When the compilation flag is set to 0 or not defined, the callback registration feature is not available
and all callbacks are set to the corresponding weak functions.

## Configuration inside the DMA2D driver

Config defines                    | Description           | Default value | Note
--------------------------------- | --------------------- | ------------- | -------------------------------------------
USE_HAL_DMA2D_MODULE                | from hal_conf.h       | 1  | When set, HAL DMA2D module is enabled
USE_HAL_DMA2D_REGISTER_CALLBACKS    | from hal_conf.h       | 0  | When set, enable the register callbacks
USE_HAL_DMA2D_CLK_ENABLE_MODEL | from hal_conf.h | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PARAM | from hal_conf.h | 0  | When set, the vital parameters (pointers or sizes) are checked in runtime
USE_ASSERT_DBG_PARAM              | from PreProcessor env | None | When defined, enable the params assert
USE_ASSERT_DBG_STATE              | from PreProcessor env | None | When defined, enable the state assert
USE_HAL_DMA2D_USER_DATA               | from hal_conf.h | 0   | When set, user data is defined in handle
USE_HAL_DMA2D_GET_LAST_ERRORS         | from hal_conf.h | 0   | When set, user can get the last error code
USE_HAL_DMA2D_CLUT_IRQ           | from hal_conf.h | 0   | When set, enable HAL_DMA2D_IRQHandler() handle CLUT interrupt
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (DMA2D)

/** @addtogroup DMA2D
  * @{
  */
#if defined (USE_HAL_DMA2D_MODULE) && (USE_HAL_DMA2D_MODULE == 1)

/* Private types -----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Types DMA2D Private Types
  * @{
  */

/**
  * @}
  */

/* Private defines ---------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Constants DMA2D Private Constants
  * @{
  */

/*!< DMA2D timeout defines                  */
#define DMA2D_TIMEOUT_ABORT           1000U  /*!<  1s  */
#define DMA2D_TIMEOUT_SUSPEND         1000U  /*!<  1s  */

/*!< DMA2D configured transfer mode defines  */
#define DMA2D_XFER_NONE               0U           /*!< DMA2D transfer mode not configured                */
#define DMA2D_XFER_MEM_CPY            (1U << 31U)  /*!< DMA2D transfer mode configured memory-to-memory   */
#define DMA2D_XFER_MEM_CPYPFC         (1U << 30U)  /*!< DMA2D transfer mode configured memory-to-memory
                                                        with pixel format conversion                      */
#define DMA2D_XFER_MEM_FILL           (1U << 29U)  /*!< DMA2D transfer mode configured register-to-memory */
#define DMA2D_XFER_MEM_BLENDING       (1U << 28U)  /*!< DMA2D transfer mode configured memory-to-memory
                                                        with pixel format conversion and blending         */
#define DMA2D_XFER_MEM_BLENDING_FG    (1U << 27U)  /*!< DMA2D transfer mode configured memory-to-memory
                                                        with pixel format conversion, blending
                                                        and fixed color foreground                        */
#define DMA2D_XFER_MEM_BLENDING_BG    (1U << 26U)  /*!< DMA2D transfer mode configured memory-to-memory
                                                        with pixel format conversion, blending
                                                        and fixed color background                        */

#define DMA2D_MAX_CLUT_COLOR_INDEX   (0x000000FFU) /*!< 256                                  */
#define DMA2D_MAX_INPUT_ALPHA        (0x000000FFU) /*!< Maximum allowed input alpha value    */
#define DMA2D_MAX_OFFSET             (0x0000FFFFU) /*!< Maximum allowed offset value         */
#define DMA2D_MAX_LINE_WATERMARK     (0x0000FFFFU) /*!< Maximum allowed line watermark value */
#define DMA2D_MAX_RGB888             (0x00FFFFFFU) /*!< Maximum allowed RGB888 color value   */
/**
  * @}
  */


/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Macros DMA2D Private Macros
  * @{
  */

/**
  * @brief DMA2D get Instance macro
  */
#define DMA2D_GET_INSTANCE(handle)  ((DMA2D_TypeDef *)((uint32_t)(handle)->instance))

/**
  * @brief Assert macro to check if a transfer mode is configured
  */
#define IS_DMA2D_CONFIGURED_XFER_MODE(cfg_xfer_mode) (((cfg_xfer_mode) >= DMA2D_XFER_MEM_BLENDING_BG) \
                                                      && ((cfg_xfer_mode) <= DMA2D_XFER_MEM_CPY))

/**
  * @brief Assert macro for a maximum number of lines
  */
#define IS_DMA2D_LINE(line) ((line) <= DMA2D_NLR_NL)

/**
  * @brief Assert macro for a maximum number of pixels per lines
  */
#define IS_DMA2D_PIXEL(pixel) ((pixel) <= (DMA2D_NLR_PL >> 16U))

/**
  * @brief Assert macro for the input alpha mode
  */
#define IS_DMA2D_INPUT_ALPHA_MODE(input_alpha_mode) (((input_alpha_mode) == HAL_DMA2D_INPUT_ALPHA_NO_MODIF) \
                                                     || ((input_alpha_mode) == HAL_DMA2D_INPUT_ALPHA_REPLACE)  \
                                                     || ((input_alpha_mode) == HAL_DMA2D_INPUT_ALPHA_COMBINE))

/**
  * @brief Assert macro for the input alpha value
  */
#define IS_DMA2D_INPUT_ALPHA_VALUE(input_alpha_mode, input_alpha_value) \
  (((input_alpha_mode) == HAL_DMA2D_INPUT_ALPHA_NO_MODIF)           \
   || ((input_alpha_value) <= DMA2D_MAX_INPUT_ALPHA))

/**
  * @brief Assert macro for the line offset mode
  */
#define IS_DMA2D_LINE_OFFSET_MODE(line_offset_mode) (((line_offset_mode) == HAL_DMA2D_LINE_OFFSET_PIXELS) \
                                                     || ((line_offset_mode) == HAL_DMA2D_LINE_OFFSET_BYTES))

/**
  * @brief Assert macro for the Background input color mode
  */
#define IS_DMA2D_INPUT_BG_CMODE(input_color_mode) (((input_color_mode) == HAL_DMA2D_INPUT_COLOR_ARGB8888) \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_RGB888)   \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_RGB565)   \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_ARGB1555) \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_ARGB4444) \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_L8)       \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_AL44)     \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_AL88)     \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_L4)       \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_A8)       \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_A4)       \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_ABGR8888)\
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_BGR888)  \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_BGR565)  \
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_ABGR1555)\
                                                   || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_ABGR4444))


#if defined(DMA2D_FGPFCCR_CSS)
/**
  * @brief Assert macro for the input chroma subsampling mode
  */
#define IS_DMA2D_INPUT_YCBCR(input_color_mode) (((input_color_mode) == HAL_DMA2D_INPUT_COLOR_YCBCR_444)\
                                                || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_YCBCR_422)\
                                                || ((input_color_mode) == HAL_DMA2D_INPUT_COLOR_YCBCR_420))
#endif /* DMA2D_FGPFCCR_CSS */

/**
  * @brief Assert macro for the input color mode
  */
#if defined(DMA2D_FGPFCCR_CSS)
#define IS_DMA2D_INPUT_COLOR_MODE(input_color_mode) IS_DMA2D_INPUT_BG_CMODE(input_color_mode) \
  || IS_DMA2D_INPUT_YCBCR(input_color_mode)
#else
#define IS_DMA2D_INPUT_COLOR_MODE(input_color_mode) IS_DMA2D_INPUT_BG_CMODE(input_color_mode)
#endif /* GENERATOR_YCBCR_AVAILABLE_XXX_DEVICES */
/**
  * @brief Assert macro for the output color mode
  */
#define IS_DMA2D_OUTPUT_CMODE(output_color_mode) (((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ARGB8888) \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_RGB888)   \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_RGB565)   \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ARGB1555) \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ARGB4444) \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ABGR8888) \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_BGR888)   \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_BGR565)   \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ABGR1555) \
                                                  || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ABGR4444))

/**
  * @brief Assert macro for the output color
  */
#define IS_DMA2D_OUTPUT_COLOR(output_color_mode, color) (((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ARGB8888) \
                                                         || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_RGB888)   \
                                                         || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_ABGR8888) \
                                                         || ((output_color_mode) == HAL_DMA2D_OUTPUT_COLOR_BGR888)   \
                                                         || ((color) <= 0xFFFFU) )

/**
  * @brief Assert macro for the input layer
  */
#define IS_DMA2D_INPUT_SOURCE(input) (((input) == HAL_DMA2D_INPUT_BG) \
                                      || ((input) == HAL_DMA2D_INPUT_FG))

/**
  * @brief Assert macro for the CLUT color mode
  */
#define IS_DMA2D_CLUT_CMODE(color_mode) (((color_mode) == HAL_DMA2D_CLUT_COLOR_ARGB8888) \
                                         || ((color_mode) == HAL_DMA2D_CLUT_COLOR_RGB888))

/**
  * @}
  */

/* Private functions prototypes --------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Functions DMA2D Private Functions
  * @{
  */
static void DMA2D_SetConfigBackground(DMA2D_TypeDef *p_dma2d, const hal_dma2d_input_config_t *bg_cfg);
static void DMA2D_SetConfigForeground(DMA2D_TypeDef *p_dma2d, const hal_dma2d_input_config_t *fg_cfg);
static void DMA2D_SetConfigOutput(DMA2D_TypeDef *p_dma2d, const hal_dma2d_output_config_t *output_cfg, \
                                  uint32_t width, uint32_t height);
static hal_status_t DMA2D_Abort(hal_dma2d_handle_t *hdma2d);
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Variables DMA2D Private Variables
  * @{
  */

/**
  * @}
  */


/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup DMA2D_Exported_Functions
  * @{
  */

/** @addtogroup DMA2D_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and deinitialize the DMA2D peripheral:
- HAL_DMA2D_Init() to initialize the selected HAL DMA2D handle and associate an DMA2D peripheral instance
- HAL_DMA2D_DeInit() to de-initialize the given HAL DMA2D instance by aborting any ongoing process
and resetting the state machine
  */

/**
  * @brief  Initialize the selected HAL DMA2D handle and associate a DMA2D peripheral instance
  * @param  hdma2d            Pointer to a hal_dma2d_handle_t structure
  * @param  instance          Specifie the DMA2D instance
  * @retval HAL_INVALID_PARAM Invalid parameter when hdma2d pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly Initialized
  */
hal_status_t HAL_DMA2D_Init(hal_dma2d_handle_t *hdma2d, hal_dma2d_t instance)
{

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_ALL_INSTANCE((DMA2D_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (hdma2d == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */


  hdma2d->instance = instance;

  hdma2d->cfg_xfer_mode = DMA2D_XFER_NONE;


#if defined(USE_HAL_DMA2D_CLK_ENABLE_MODEL) && (USE_HAL_DMA2D_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_DMA2D_EnableClock();
#endif /* USE_HAL_DMA2D_CLK_ENABLE_MODEL */

#if defined (USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
  hdma2d->p_xfer_cplt_cb          = HAL_DMA2D_XferCpltCallback;
  hdma2d->p_error_cb              = HAL_DMA2D_ErrorCallback;
  hdma2d->p_watermark_cb          = HAL_DMA2D_WaterMarkCallback;
#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
  hdma2d->p_clut_loading_cplt_cb  = HAL_DMA2D_CLUTLoadingCpltCallback;
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

#if defined(USE_HAL_DMA2D_USER_DATA) && (USE_HAL_DMA2D_USER_DATA == 1)
  hdma2d->p_user_data = NULL;
#endif /* USE_HAL_DMA2D_USER_DATA */

#if defined (USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
  hdma2d->last_error_codes = HAL_DMA2D_ERROR_NONE;
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */

  hdma2d->global_state   = HAL_DMA2D_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  De-initialize the given HAL DMA2D instance by aborting any ongoing process, and resetting the state machine
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure
  */
void HAL_DMA2D_DeInit(hal_dma2d_handle_t *hdma2d)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_ALL_INSTANCE((DMA2D_TypeDef *)(uint32_t)hdma2d->instance));

  (void)DMA2D_Abort(hdma2d);

  hdma2d->global_state = HAL_DMA2D_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group2
  * @{

This subsection provides a set of global configuration APIs allowing to configure the DMA2D peripheral transfer mode.
- HAL_DMA2D_SetConfigMemFill() set the configuration for Register-to-memory DMA2D transfer mode
- HAL_DMA2D_SetConfigMemCopy() set the configuration for Memory-to-memory DMA2D transfer mode
- HAL_DMA2D_SetConfigMemCopyPFC() set the configuration for Memory-to-memory with pixel format conversion
DMA2D transfer mode
- HAL_DMA2D_SetConfigBlending() set the configuration for Memory-to-memory with pixel format conversion and blending
DMA2D transfer mode
- HAL_DMA2D_SetConfigBlendingFixFGColor() set the configuration for Memory-to memory with pixel format conversion,
blending and fixed color foreground DMA2D transfer mode
- HAL_DMA2D_SetConfigBlendingFixBGColor() set the configuration for Memory-to memory with pixel format conversion,
blending and fixed color background DMA2D transfer mode
  */

/**
  * @brief  Configure the DMA2D in memory-to-memory transfer mode according to the user parameters
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  * @param  p_config Pointer to a hal_dma2d_mem_copy_config_t structure that contains the DMA2D configuration
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigMemCopy(hal_dma2d_handle_t *hdma2d, const hal_dma2d_mem_copy_config_t *p_config)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE(p_config->height));
  ASSERT_DBG_PARAM(IS_DMA2D_PIXEL(p_config->width));
  ASSERT_DBG_PARAM(p_config->input.p_src != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->input.alpha_mode));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_VALUE(p_config->input.alpha_mode, p_config->input.alpha_value));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_COLOR_MODE(p_config->input.color_mode));
  ASSERT_DBG_PARAM(p_config->input.offset <= DMA2D_MAX_OFFSET);
  ASSERT_DBG_PARAM(p_config->output.p_dest != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_CMODE(p_config->output.color_mode));
  ASSERT_DBG_PARAM(p_config->output.offset <= DMA2D_MAX_OFFSET);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetMode(p_dma2d, LL_DMA2D_MODE_M2M);

  DMA2D_SetConfigOutput(p_dma2d, &p_config->output, p_config->width, p_config->height);

  DMA2D_SetConfigForeground(p_dma2d, &p_config->input);

  hdma2d->cfg_xfer_mode = DMA2D_XFER_MEM_CPY;

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D in memory-to-memory with pixel format conversion transfer mode according to the user
  *         parameters
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  * @param  p_config Pointer to a hal_dma2d_mem_copy_config_t structure that contains the DMA2D configuration
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigMemCopyPFC(hal_dma2d_handle_t *hdma2d, const hal_dma2d_mem_copy_config_t *p_config)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE(p_config->height));
  ASSERT_DBG_PARAM(IS_DMA2D_PIXEL(p_config->width));
  ASSERT_DBG_PARAM(p_config->input.p_src != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->input.alpha_mode));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_VALUE(p_config->input.alpha_mode, p_config->input.alpha_value));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_COLOR_MODE(p_config->input.color_mode));
  ASSERT_DBG_PARAM(p_config->input.offset <= DMA2D_MAX_OFFSET);
  ASSERT_DBG_PARAM(p_config->output.p_dest != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_CMODE(p_config->output.color_mode));
  ASSERT_DBG_PARAM(p_config->output.offset <= DMA2D_MAX_OFFSET);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetMode(p_dma2d, LL_DMA2D_MODE_M2M_PFC);

  DMA2D_SetConfigOutput(p_dma2d, &p_config->output, p_config->width, p_config->height);

  DMA2D_SetConfigForeground(p_dma2d, &p_config->input);

  hdma2d->cfg_xfer_mode = DMA2D_XFER_MEM_CPYPFC;

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D in register-to-memory transfer mode according to the user parameters
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  * @param  p_config Pointer to a hal_dma2d_mem_fill_config_t structure that contains the DMA2D configuration
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigMemFill(hal_dma2d_handle_t *hdma2d, const hal_dma2d_mem_fill_config_t *p_config)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE(p_config->height));
  ASSERT_DBG_PARAM(IS_DMA2D_PIXEL(p_config->width));
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_COLOR(p_config->output.color_mode, p_config->fixed_color));
  ASSERT_DBG_PARAM(p_config->output.p_dest != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_CMODE(p_config->output.color_mode));
  ASSERT_DBG_PARAM(p_config->output.offset <= DMA2D_MAX_OFFSET);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetMode(p_dma2d, LL_DMA2D_MODE_R2M);

  DMA2D_SetConfigOutput(p_dma2d, &p_config->output, p_config->width, p_config->height);

  LL_DMA2D_SetOutputColor(p_dma2d, p_config->fixed_color);

  hdma2d->cfg_xfer_mode = DMA2D_XFER_MEM_FILL;

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D in transfer with blending mode according to the user parameters
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  * @param  p_config Pointer to a hal_dma2d_blending_config_t structure that contains the DMA2D configuration
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigBlending(hal_dma2d_handle_t *hdma2d, const hal_dma2d_blending_config_t *p_config)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE(p_config->height));
  ASSERT_DBG_PARAM(IS_DMA2D_PIXEL(p_config->width));
  ASSERT_DBG_PARAM(p_config->fg_input.p_src != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->fg_input.alpha_mode));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_VALUE(p_config->fg_input.alpha_mode, p_config->fg_input.alpha_value));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_COLOR_MODE(p_config->fg_input.color_mode));
  ASSERT_DBG_PARAM(p_config->fg_input.offset <= DMA2D_MAX_OFFSET);
  ASSERT_DBG_PARAM(p_config->bg_input.p_src != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->bg_input.alpha_mode));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_VALUE(p_config->bg_input.alpha_mode, p_config->bg_input.alpha_value));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_BG_CMODE(p_config->bg_input.color_mode));
  ASSERT_DBG_PARAM(p_config->bg_input.offset <= DMA2D_MAX_OFFSET);
  ASSERT_DBG_PARAM(p_config->output.p_dest != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_CMODE(p_config->output.color_mode));
  ASSERT_DBG_PARAM(p_config->output.offset <= DMA2D_MAX_OFFSET);


  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetMode(p_dma2d, LL_DMA2D_MODE_M2M_BLEND);

  DMA2D_SetConfigOutput(p_dma2d, &p_config->output, p_config->width, p_config->height);

  DMA2D_SetConfigForeground(p_dma2d, &p_config->fg_input);

  DMA2D_SetConfigBackground(p_dma2d, &p_config->bg_input);

  hdma2d->cfg_xfer_mode = DMA2D_XFER_MEM_BLENDING;

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D in transfer with blending with fixed foreground color mode according to the user
  *         parameters
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  * @param  p_config Pointer to a hal_dma2d_blending_fixed_color_config_t structure that contains the DMA2D
  *                  configuration
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigBlendingFixFGColor(hal_dma2d_handle_t *hdma2d,
                                                   const hal_dma2d_blending_fixed_color_config_t *p_config)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE(p_config->height));
  ASSERT_DBG_PARAM(IS_DMA2D_PIXEL(p_config->width));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->fixed_color_alpha_mode));
  ASSERT_DBG_PARAM(p_config->mem_input.p_src != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->mem_input.alpha_mode));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_VALUE(p_config->mem_input.alpha_mode, p_config->mem_input.alpha_value));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_BG_CMODE(p_config->mem_input.color_mode));
  ASSERT_DBG_PARAM(p_config->mem_input.offset <= DMA2D_MAX_OFFSET);
  ASSERT_DBG_PARAM(p_config->output.p_dest != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_CMODE(p_config->output.color_mode));
  ASSERT_DBG_PARAM(p_config->output.offset <= DMA2D_MAX_OFFSET);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetMode(p_dma2d, LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_FG);

  DMA2D_SetConfigOutput(p_dma2d, &p_config->output, p_config->width, p_config->height);

  LL_DMA2D_FGND_SetRGBColor(p_dma2d, (p_config->fixed_color_argb8888) & DMA2D_MAX_RGB888);

  LL_DMA2D_FGND_SetARGBMode(p_dma2d, (uint32_t)HAL_DMA2D_INPUT_COLOR_RGB888, \
                            (uint32_t)p_config->fixed_color_alpha_mode, \
                            (p_config->fixed_color_argb8888) >> DMA2D_FGPFCCR_ALPHA_Pos);

  DMA2D_SetConfigBackground(p_dma2d, &p_config->mem_input);

  hdma2d->cfg_xfer_mode = DMA2D_XFER_MEM_BLENDING_FG;

  return HAL_OK;
}

/**
  * @brief  Configure the DMA2D in transfer with blending with fixed background color mode according to the user
  *         parameters
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  * @param  p_config Pointer to a hal_dma2d_blending_fixed_color_config_t structure that contains the DMA2D
  *                  configuration
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            DMA2D instance has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigBlendingFixBGColor(hal_dma2d_handle_t *hdma2d,
                                                   const hal_dma2d_blending_fixed_color_config_t *p_config)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE(p_config->height));
  ASSERT_DBG_PARAM(IS_DMA2D_PIXEL(p_config->width));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->fixed_color_alpha_mode));
  ASSERT_DBG_PARAM(p_config->mem_input.p_src != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_MODE(p_config->mem_input.alpha_mode));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_ALPHA_VALUE(p_config->mem_input.alpha_mode, p_config->mem_input.alpha_value));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_COLOR_MODE(p_config->mem_input.color_mode));
  ASSERT_DBG_PARAM(p_config->mem_input.offset <= DMA2D_MAX_OFFSET);
  ASSERT_DBG_PARAM(p_config->output.p_dest != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_OUTPUT_CMODE(p_config->output.color_mode));
  ASSERT_DBG_PARAM(p_config->output.offset <= DMA2D_MAX_OFFSET);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetMode(p_dma2d, LL_DMA2D_MODE_M2M_BLEND_FIXED_COLOR_BG);

  DMA2D_SetConfigOutput(p_dma2d, &p_config->output, p_config->width, p_config->height);

  LL_DMA2D_BGND_SetRGBColor(p_dma2d, (p_config->fixed_color_argb8888) & DMA2D_MAX_RGB888);

  LL_DMA2D_BGND_SetARGBMode(p_dma2d, (uint32_t)HAL_DMA2D_INPUT_COLOR_RGB888, \
                            (uint32_t)p_config->fixed_color_alpha_mode, \
                            (p_config->fixed_color_argb8888) >> DMA2D_BGPFCCR_ALPHA_Pos);

  DMA2D_SetConfigForeground(p_dma2d, &p_config->mem_input);

  hdma2d->cfg_xfer_mode = DMA2D_XFER_MEM_BLENDING_BG;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group3
  * @{
This subsection provides a set of process management APIs allowing to start, stop, suspend, resume
and abort a DMA2D transfer or CLUT Loading
- HAL_DMA2D_Start() start the DMA2D transfer
- HAL_DMA2D_Start_IT() enable interrupts and start the DMA2D transfer
- HAL_DMA2D_Suspend() suspend the ongoing DMA2D transfer
- HAL_DMA2D_Resume() resume the suspended DMA2D transfer
- HAL_DMA2D_Abort() abort a suspended, or ongoing DMA2D transfer
- HAL_DMA2D_PollForTransfer() poll for DMA2D transfer complete
- HAL_DMA2D_StartCLUTLoad() start the CLUT foreground or background loading
- HAL_DMA2D_StartCLUTLoad_IT() enable interrupts and start the CLUT foreground or background loading
- HAL_DMA2D_SuspendCLUTLoad() suspend the ongoing CLUT foreground or background loading
- HAL_DMA2D_ResumeCLUTLoad() resume the suspended CLUT foreground or background loading
- HAL_DMA2D_AbortCLUTLoad() abort a suspended, or ongoing CLUT foreground or background loading
- HAL_DMA2D_PollForCLUTLoad() poll for CLUT foreground or background loading complete
  */

/* Xfer functions  ****************************************************************************************************/

/**
  * @brief  Start the DMA2D transfer
  * @param  hdma2d   Pointer to a hal_dma2d_handle_t structure that contains
  *                  the configuration information for the DMA2D
  * @retval HAL_OK   DMA2D data transfer is successfully started
  */
hal_status_t HAL_DMA2D_Start(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;


  ASSERT_DBG_PARAM(hdma2d != NULL);


  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  ASSERT_DBG_PARAM(IS_DMA2D_CONFIGURED_XFER_MODE(hdma2d->cfg_xfer_mode));

  HAL_CHECK_UPDATE_STATE(hdma2d, global_state, HAL_DMA2D_STATE_IDLE, HAL_DMA2D_STATE_XFER_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_Start(p_dma2d);

  return HAL_OK;
}

/**
  * @brief  Start the DMA2D transfer with interrupt enabled
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure that contains
  *                   the configuration information for the DMA2D
  * @retval HAL_OK    DMA2D data transfer is successfully started
  */
hal_status_t HAL_DMA2D_Start_IT(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t cr_reg;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  ASSERT_DBG_PARAM(IS_DMA2D_CONFIGURED_XFER_MODE(hdma2d->cfg_xfer_mode));

  HAL_CHECK_UPDATE_STATE(hdma2d, global_state, HAL_DMA2D_STATE_IDLE, HAL_DMA2D_STATE_XFER_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  /* Enable the transfer complete, transfer error and configuration error interrupts and start the transfer*/
  cr_reg = LL_DMA2D_READ_REG(p_dma2d, CR);

  LL_DMA2D_WRITE_REG(p_dma2d, CR, \
                     DMA2D_CR_CEIE | DMA2D_CR_TCIE | DMA2D_CR_TEIE | DMA2D_CR_START | cr_reg);

  return HAL_OK;
}

/**
  * @brief  Suspend the ongoing DMA2D transfer
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure that contains
  *                   the configuration information for the DMA2D
  * @retval HAL_OK       DMA2D transfer is successfully suspended
  * @retval HAL_ERROR    DMA2D transfer could not suspend or transfer already completed
  */
hal_status_t HAL_DMA2D_Suspend(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_IsTransferOngoing(p_dma2d) == 0U)
  {
    return HAL_ERROR;
  }

  LL_DMA2D_Suspend(p_dma2d);

  tickstart = HAL_GetTick();

  /* Check if the DMA2D is effectively suspended */
  while ((LL_DMA2D_READ_REG(p_dma2d, CR) & (DMA2D_CR_SUSP | DMA2D_CR_START)) == DMA2D_CR_START)
  {
    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_SUSPEND)
    {
      break;
    }
  }

  if ((LL_DMA2D_READ_REG(p_dma2d, CR) & (DMA2D_CR_SUSP | DMA2D_CR_START)) == (DMA2D_CR_SUSP | DMA2D_CR_START))
  {
    hdma2d->global_state = HAL_DMA2D_STATE_XFER_SUSPEND;

    return HAL_OK;
  }
  else
  {
    hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

    return HAL_ERROR;
  }
}

/**
  * @brief  Resume instantantly any suspended DMA2D transfer or CLUT loading
  * @param  hdma2d   Pointer to a hal_dma2d_handle_t structure that contains
  *                  the configuration information for the DMA2D
  * @retval HAL_OK    DMA2D transfer is successfully resumed
  * @retval HAL_ERROR DMA2D transfer not resumed
  */
hal_status_t HAL_DMA2D_Resume(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_IsSuspended(p_dma2d) != 0U)
  {
    hdma2d->global_state = HAL_DMA2D_STATE_XFER_ACTIVE;

    LL_DMA2D_Resume(p_dma2d);
    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Abort an ongoing DMA2D transfer
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure that contains
  *                   the configuration information for the DMA2D
  * @retval HAL_ERROR DMA2D not aborted
  * @retval HAL_OK    DMA2D data transfer is successfully aborted
  */
hal_status_t HAL_DMA2D_Abort(hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_IsTransferOngoing(p_dma2d) != 0U)
  {
    if (DMA2D_Abort(hdma2d) == HAL_OK)
    {
      hdma2d->global_state = HAL_DMA2D_STATE_IDLE;
      status = HAL_OK;
    }
  }

  return status;
}

/**
  * @brief  Polling for DMA2D transfer complete
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure that contains
  *                      the configuration information for the DMA2D
  * @param  timeout_msec Specifies the user timeout in milli-second, or set to **HAL_MAX_DELAY**
  *                      if you would like to repeat until transfer complete or, transfer error or configuration error
  * @retval HAL_TIMEOUT  User timeout
  * @retval HAL_ERROR    DMA2D error
  * @retval HAL_OK       Polling for transfer is successfully executed
  */
hal_status_t HAL_DMA2D_PollForTransfer(hal_dma2d_handle_t *hdma2d, uint32_t timeout_msec)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t tickstart;
  uint32_t isrflags;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE);

  tickstart = HAL_GetTick();

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  do
  {
    isrflags = LL_DMA2D_READ_REG(p_dma2d, ISR);

    if ((isrflags & (LL_DMA2D_FLAG_CEIF | LL_DMA2D_FLAG_TEIF)) != 0U)
    {
#if defined(USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
      if ((isrflags & LL_DMA2D_FLAG_CEIF) != 0U)
      {
        hdma2d->last_error_codes |= HAL_DMA2D_ERROR_CE;
      }
      if ((isrflags & LL_DMA2D_FLAG_TEIF) != 0U)
      {
        hdma2d->last_error_codes |= HAL_DMA2D_ERROR_TE;
      }
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */
      LL_DMA2D_WRITE_REG(p_dma2d, IFCR, LL_DMA2D_FLAG_CEIF | LL_DMA2D_FLAG_TEIF);

      hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

      return HAL_ERROR;
    }

    if (timeout_msec != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_msec) || (timeout_msec == 0U))
      {
        if (LL_DMA2D_IsActiveFlag_TC(p_dma2d) == 0U)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  } while ((isrflags & LL_DMA2D_FLAG_TCIF) != LL_DMA2D_FLAG_TCIF);

  LL_DMA2D_ClearFlag_TC(p_dma2d);

  hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

  return HAL_OK;
}

/* CLUT functions  ****************************************************************************************************/

/**
  * @brief  Start the DMA2D CLUT loading
  * @param  hdma2d   Pointer to a hal_dma2d_handle_t structure that contains
  *                  the configuration information for the DMA2D
  * @param  p_clut_config Pointer to a hal_dma2d_clut_config_t structure that contains
  *                       the configuration information for the color look up table
  * @param  input         Input source. This parameter can be one of the following values:
  *                       HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_OK        DMA2D CLUT loading is successfully started
  */
hal_status_t HAL_DMA2D_StartCLUTLoad(hal_dma2d_handle_t *hdma2d, const hal_dma2d_clut_config_t *p_clut_config,
                                     hal_dma2d_input_t input)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t reg;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM((p_clut_config != NULL));
  ASSERT_DBG_PARAM((p_clut_config->p_clut != NULL));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));
  ASSERT_DBG_PARAM(IS_DMA2D_CLUT_CMODE(p_clut_config->color_mode));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdma2d, global_state, HAL_DMA2D_STATE_IDLE, HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (input == HAL_DMA2D_INPUT_BG)
  {
    LL_DMA2D_BGND_SetCLUTMemAddr(p_dma2d, (uint32_t) p_clut_config->p_clut);

    /* Set the background CLUT size and CLUT color mode, and start the CLUT loading */
    reg  = LL_DMA2D_READ_REG(p_dma2d, BGPFCCR) & (~(DMA2D_BGPFCCR_CCM | DMA2D_BGPFCCR_CS));
    reg |= (uint32_t)(p_clut_config->color_mode) | (((uint32_t) p_clut_config->size) << DMA2D_BGPFCCR_CS_Pos);
    reg |= DMA2D_BGPFCCR_START;

    LL_DMA2D_WRITE_REG(p_dma2d, BGPFCCR, reg);
  }
  else
  {
    LL_DMA2D_FGND_SetCLUTMemAddr(p_dma2d, (uint32_t) p_clut_config->p_clut);

    /* Set the foreground CLUT size and CLUT color mode, and start the CLUT loading */
    reg  = LL_DMA2D_READ_REG(p_dma2d, FGPFCCR) & (~(DMA2D_FGPFCCR_CCM | DMA2D_FGPFCCR_CS));
    reg |= (uint32_t)(p_clut_config->color_mode) | (((uint32_t) p_clut_config->size) << DMA2D_FGPFCCR_CS_Pos);
    reg |= DMA2D_FGPFCCR_START;

    LL_DMA2D_WRITE_REG(p_dma2d, FGPFCCR, reg);
  }

  return HAL_OK;
}

/**
  * @brief  Start the DMA2D CLUT loading with interrupt enabled
  * @param  hdma2d   Pointer to a hal_dma2d_handle_t structure that contains
  *                  the configuration information for the DMA2D
  * @param  p_clut_config Pointer to a hal_dma2d_clut_config_t structure that contains
  *                       the configuration information for the color look up table
  * @param  input         Input source. This parameter can be one of the following values:
  *                       HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_OK        DMA2D CLUT loading is successfully started
  */
hal_status_t HAL_DMA2D_StartCLUTLoad_IT(hal_dma2d_handle_t *hdma2d, const hal_dma2d_clut_config_t *p_clut_config,
                                        hal_dma2d_input_t input)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t reg;


  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM((p_clut_config != NULL));
  ASSERT_DBG_PARAM((p_clut_config->p_clut != NULL));
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));
  ASSERT_DBG_PARAM(IS_DMA2D_CLUT_CMODE(p_clut_config->color_mode));


  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);


  HAL_CHECK_UPDATE_STATE(hdma2d, global_state, HAL_DMA2D_STATE_IDLE, HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_EnableIT(p_dma2d, LL_DMA2D_IT_CTCIE | LL_DMA2D_IT_TEIE | LL_DMA2D_IT_CEIE | LL_DMA2D_IT_CAEIE);

  if (input == HAL_DMA2D_INPUT_BG)
  {
    LL_DMA2D_BGND_SetCLUTMemAddr(p_dma2d, (uint32_t) p_clut_config->p_clut);

    reg  = LL_DMA2D_READ_REG(p_dma2d, BGPFCCR) & (~(DMA2D_BGPFCCR_CCM | DMA2D_BGPFCCR_CS));
    reg |= (uint32_t)(p_clut_config->color_mode) | (((uint32_t) p_clut_config->size) << DMA2D_BGPFCCR_CS_Pos);
    reg |= DMA2D_BGPFCCR_START;

    LL_DMA2D_WRITE_REG(p_dma2d, BGPFCCR, reg);
  }
  else
  {

    LL_DMA2D_FGND_SetCLUTMemAddr(p_dma2d, (uint32_t) p_clut_config->p_clut);

    reg  = LL_DMA2D_READ_REG(p_dma2d, FGPFCCR) & (~(DMA2D_FGPFCCR_CCM | DMA2D_FGPFCCR_CS));
    reg |= (uint32_t)(p_clut_config->color_mode) | (((uint32_t) p_clut_config->size) << DMA2D_FGPFCCR_CS_Pos);
    reg |= DMA2D_FGPFCCR_START;

    LL_DMA2D_WRITE_REG(p_dma2d, FGPFCCR, reg);
  }

  return HAL_OK;
}

/**
  * @brief  Suspend an ongoing DMA2D CLUT loading
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure that contains
  *                   the configuration information for the DMA2D
  * @param  input     Input source. This parameter can be one of the following values:
  *                   HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_OK       DMA2D CLUT loading is successfully suspended
  * @retval HAL_ERROR    DMA2D CLUT Loading could not suspended
  */
hal_status_t HAL_DMA2D_SuspendCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t tickstart;
  uint32_t bg_state;
  uint32_t fg_state;
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  bg_state = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
  fg_state = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

  if (((input == HAL_DMA2D_INPUT_BG) && (bg_state != 0U)) \
      || ((input == HAL_DMA2D_INPUT_FG) && (fg_state != 0U)))
  {
    LL_DMA2D_Suspend(p_dma2d);

    tickstart = HAL_GetTick();

    while (((LL_DMA2D_IsSuspended(p_dma2d)) == 0U) && ((bg_state | fg_state) != 0U))
    {
      if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_SUSPEND)
      {
        break;
      }
      bg_state = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
      fg_state = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);
    }

    bg_state = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
    fg_state = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

    if ((LL_DMA2D_IsSuspended(p_dma2d) != 0U) && ((bg_state | fg_state) != 0U))
    {

      hdma2d->global_state = HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND;
      status =  HAL_OK;
    }
  }

  return status;
}

/**
  * @brief  Resume a suspended DMA2D CLUT loading
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure that contains
  *                   the configuration information for the DMA2D
  * @param  input     Input source. This parameter can be one of the following values:
  *                   HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_OK      DMA2D CLUT loading is successfully resumed
  * @retval HAL_ERROR   DMA2D CLUT loading is could not resume
  */
hal_status_t HAL_DMA2D_ResumeCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input)
{
  DMA2D_TypeDef *p_dma2d;
  hal_status_t status = HAL_ERROR;
  uint32_t bg_state;
  uint32_t fg_state;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_IsSuspended(p_dma2d) != 0U)
  {
    bg_state = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
    fg_state = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

    if (((input == HAL_DMA2D_INPUT_BG) && (bg_state != 0U)) \
        || ((input == HAL_DMA2D_INPUT_FG) && (fg_state != 0U)))
    {
      hdma2d->global_state = HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE;

      LL_DMA2D_Resume(p_dma2d);

      status = HAL_OK;
    }
  }
  return status;
}

/**
  * @brief  Abort an ongoing DMA2D CLUT loading
  * @param  hdma2d    Pointer to a hal_dma2d_handle_t structure that contains
  *                   the configuration information for the DMA2D
  * @param  input     Input source. This parameter can be one of the following values:
  *                   HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_ERROR DMA2D not aborted
  * @retval HAL_BUSY  DMA2D state is abort when calling this API
  * @retval HAL_OK    DMA2D CLUT loading is successfully aborted
  */
hal_status_t HAL_DMA2D_AbortCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_status_t status = HAL_ERROR;
  uint32_t bg_state;
  uint32_t fg_state;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  bg_state = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
  fg_state = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

  if (((input == HAL_DMA2D_INPUT_BG) && (bg_state != 0U)) \
      || ((input == HAL_DMA2D_INPUT_FG) && (fg_state != 0U)))
  {
    if (DMA2D_Abort(hdma2d) == HAL_OK)
    {
      hdma2d->global_state = HAL_DMA2D_STATE_IDLE;
      status = HAL_OK;
    }
  }
  return status;
}

/**
  * @brief  Polling for DMA2D CLUT loading complete
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure that contains
  *                      the configuration information for the DMA2D
  * @param  input        Input source. This parameter can be one of the following values:
  *                      HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @param  timeout_msec Specifies the user timeout in milli-second, or set to **HAL_MAX_DELAY**
  *                      if you would like to repeat until transfer complete or, transfer error or configuration error
  * @retval HAL_TIMEOUT  User timeout
  * @retval HAL_ERROR    DMA2D error
  * @retval HAL_OK       Polling for the CLUT loading is successfully executed
  */
hal_status_t HAL_DMA2D_PollForCLUTLoad(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input, uint32_t timeout_msec)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t bg_state;
  uint32_t fg_state;
  uint32_t tickstart;
  uint32_t isrflags;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  bg_state = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
  fg_state = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

  if (((input == HAL_DMA2D_INPUT_BG) && (bg_state != 0U)) \
      || ((input == HAL_DMA2D_INPUT_FG) && (fg_state != 0U)))
  {
    tickstart = HAL_GetTick();

    do
    {
      isrflags = LL_DMA2D_READ_REG(p_dma2d, ISR);

      if ((isrflags & LL_DMA2D_FLAG_CAEIF) != 0U)
      {
#if defined(USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
        hdma2d->last_error_codes |= HAL_DMA2D_ERROR_CAE;
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */
        LL_DMA2D_ClearFlag_CAE(p_dma2d);

        hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

        return HAL_ERROR;
      }

      if (timeout_msec != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > timeout_msec) || (timeout_msec == 0U))
        {
          if (LL_DMA2D_IsActiveFlag_CTC(p_dma2d) == 0U)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    } while ((isrflags & LL_DMA2D_FLAG_CTCIF) == 0U);

    LL_DMA2D_ClearFlag_CTC(p_dma2d);
  }


  hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group4
  * @{
This subsection provides the IRQ handler API allowing to handle DMA2D transfer or CLUT Loading interruptions
- HAL_DMA2D_IRQHandler() handle all DMA2D interrupts

__Note :__ User can set the USE_HAL_DMA2D_CLUT_IRQ define in the hal_conf.h to handle all interrupts,
or set the USE_HAL_DMA2D_CLUT_IRQ define to 0 when user needs to handle only the transfer interrupts
(no CLUT usage within the application).
  */

/**
  * @brief  Handle the DMA2D interrupt request
  * @param  hdma2d Pointer to a hal_dma2d_handle_t structure
  */
void HAL_DMA2D_IRQHandler(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t isr_flag;
  uint32_t it_enabled;

  ASSERT_DBG_PARAM(hdma2d != NULL);

#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE);
#else
  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE);
#endif /* USE_HAL_DMA2D_CLUT_IRQ */

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  isr_flag = LL_DMA2D_READ_REG(p_dma2d, ISR);

#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
  it_enabled = LL_DMA2D_READ_REG(p_dma2d, CR) & (LL_DMA2D_IT_CEIE | LL_DMA2D_IT_CTCIE | LL_DMA2D_IT_CAEIE \
                                                 | LL_DMA2D_IT_TWIE | LL_DMA2D_IT_TCIE | LL_DMA2D_IT_TEIE);
#else
  it_enabled = LL_DMA2D_READ_REG(p_dma2d, CR) & (LL_DMA2D_IT_CEIE | LL_DMA2D_IT_TWIE | LL_DMA2D_IT_TCIE \
                                                 | LL_DMA2D_IT_TEIE);
#endif /* USE_HAL_DMA2D_CLUT_IRQ */

  /* Transfer watermark Interrupt management **************************************************************************/
  if (((isr_flag & LL_DMA2D_FLAG_TWIF) != 0U) && ((it_enabled & LL_DMA2D_IT_TWIE) != 0U))
  {
    LL_DMA2D_DisableIT_TW(p_dma2d);

    LL_DMA2D_ClearFlag_TW(p_dma2d);

#if defined(USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
    hdma2d->p_watermark_cb(hdma2d);
#else
    HAL_DMA2D_WaterMarkCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
    return;
  }

  LL_DMA2D_DisableIT(p_dma2d, (LL_DMA2D_IT_CEIE | LL_DMA2D_IT_CTCIE | LL_DMA2D_IT_CAEIE \
                               | LL_DMA2D_IT_TCIE | LL_DMA2D_IT_TEIE));

  LL_DMA2D_WRITE_REG(p_dma2d, IFCR, (DMA2D_IFCR_CCEIF | DMA2D_IFCR_CCTCIF | DMA2D_IFCR_CAECIF \
                                     | DMA2D_IFCR_CTCIF | DMA2D_IFCR_CTEIF));

  /* Errors Interrupt management **************************************************************************************/
  if ((isr_flag & (it_enabled >> DMA2D_CR_TEIE_Pos) \
       & (LL_DMA2D_FLAG_CEIF | LL_DMA2D_FLAG_CAEIF | LL_DMA2D_FLAG_TEIF)) != 0U)
  {
#if defined(USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
    if (((isr_flag & LL_DMA2D_FLAG_TEIF) != 0U) && ((it_enabled & LL_DMA2D_IT_TEIE) != 0U))
    {
      hdma2d->last_error_codes |= HAL_DMA2D_ERROR_TE;
    }
    if (((isr_flag & LL_DMA2D_FLAG_CEIF) != 0U) && ((it_enabled & LL_DMA2D_IT_CEIE) != 0U))
    {
      hdma2d->last_error_codes |= HAL_DMA2D_ERROR_CE;
    }
#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
    if (((isr_flag & LL_DMA2D_FLAG_CAEIF) != 0U) && ((it_enabled & LL_DMA2D_IT_CAEIE) != 0U))
    {
      hdma2d->last_error_codes |= HAL_DMA2D_ERROR_CAE;
    }
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */

    hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

#if defined(USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
    hdma2d->p_error_cb(hdma2d);
#else
    HAL_DMA2D_ErrorCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
  }

  /* Transfer Complete Interrupt management ***************************************************************************/
  if (((isr_flag & LL_DMA2D_FLAG_TCIF) != 0U) && ((it_enabled & LL_DMA2D_IT_TCIE) != 0U))
  {
    hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

#if defined(USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
    hdma2d->p_xfer_cplt_cb(hdma2d);
#else
    HAL_DMA2D_XferCpltCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
  }

#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
  /* CLUT Transfer Complete Interrupt management **********************************************************************/
  if (((isr_flag & LL_DMA2D_FLAG_CTCIF) != 0U) && ((it_enabled & LL_DMA2D_IT_CTCIE) != 0U))
  {

    hdma2d->global_state = HAL_DMA2D_STATE_IDLE;

#if defined(USE_HAL_DMA2D_REGISTER_CALLBACKS) && (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
    hdma2d->p_clut_loading_cplt_cb(hdma2d);
#else
    HAL_DMA2D_CLUTLoadingCpltCallback(hdma2d);
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
}

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group5
  * @{
This subsection provides a set of optional feature management APIs.
- HAL_DMA2D_EnableInputAlphaInversion()
- HAL_DMA2D_DisableInputAlphaInversion()
- HAL_DMA2D_IsEnabledInputAlphaInversion()
- HAL_DMA2D_EnableOutputAlphaInversion()
- HAL_DMA2D_DisableOutputAlphaInversion()
- HAL_DMA2D_IsEnabledOutputAlphaInversion()
- HAL_DMA2D_SetLineOffsetMode()
- HAL_DMA2D_GetLineOffsetMode()
- HAL_DMA2D_EnableOutputByteSwap()
- HAL_DMA2D_DisableOutputByteSwap()
- HAL_DMA2D_IsEnabledOutputByteSwap()
- HAL_DMA2D_EnableWaterMark()
- HAL_DMA2D_DisableWaterMark()
- HAL_DMA2D_IsEnabledWaterMark()
- HAL_DMA2D_GetWaterMarkLine()
- HAL_DMA2D_EnableDeadTime()
- HAL_DMA2D_DisableDeadTime()
- HAL_DMA2D_IsEnabledDeadTime()
- HAL_DMA2D_SetConfigDeadTime()
- HAL_DMA2D_GetConfigDeadTime()
- HAL_DMA2D_SetCLUTColorIndex()
- HAL_DMA2D_GetCLUTColorIndex()
  */

/**
  * @brief  Enable the output alpha inversion
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       Output alpha inversion successfully enabled
  */
hal_status_t HAL_DMA2D_EnableOutputAlphaInversion(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetOutputAlphaInvMode(p_dma2d, LL_DMA2D_ALPHA_INVERTED);

  return HAL_OK;
}

/**
  * @brief  Disable the output alpha inversion
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       Output alpha inversion successfully disable
  */
hal_status_t HAL_DMA2D_DisableOutputAlphaInversion(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetOutputAlphaInvMode(p_dma2d, LL_DMA2D_ALPHA_REGULAR);

  return HAL_OK;
}

/**
  * @brief  Check if the output alpha inversion is enabled or disabled
  * @param  hdma2d                             Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_DMA2D_ALPHA_INVERSION_DISABLED Output alpha inversion is disabled
  * @retval HAL_DMA2D_ALPHA_INVERSION_ENABLED  Output alpha inversion is enabled
  */
hal_dma2d_alpha_inversion_status_t HAL_DMA2D_IsEnabledOutputAlphaInversion(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_dma2d_alpha_inversion_status_t status = HAL_DMA2D_ALPHA_INVERSION_DISABLED;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_GetOutputAlphaInvMode(p_dma2d) != 0U)
  {
    status = HAL_DMA2D_ALPHA_INVERSION_ENABLED;
  }

  return status;
}

/**
  * @brief  Enable the input alpha inversion
  * @param  hdma2d   Pointer to a hal_dma2d_handle_t structure
  * @param  input    Input source. This parameter can be one of the following values:
  *                  HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_OK   Iuput alpha inversion successfully enabled
  */
hal_status_t HAL_DMA2D_EnableInputAlphaInversion(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));


  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (input == HAL_DMA2D_INPUT_FG)
  {
    LL_DMA2D_FGND_SetAlphaInvMode(p_dma2d, LL_DMA2D_ALPHA_INVERTED);
  }
  else
  {
    LL_DMA2D_BGND_SetAlphaInvMode(p_dma2d, LL_DMA2D_ALPHA_INVERTED);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the input alpha inversion
  * @param  hdma2d   Pointer to a hal_dma2d_handle_t structure
  * @param  input    Input source. This parameter can be one of the following values:
  *                  HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_OK   Input alpha inversion successfully disable
  */
hal_status_t HAL_DMA2D_DisableInputAlphaInversion(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));


  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (input == HAL_DMA2D_INPUT_FG)
  {
    LL_DMA2D_FGND_SetAlphaInvMode(p_dma2d, LL_DMA2D_ALPHA_REGULAR);
  }
  else
  {
    LL_DMA2D_BGND_SetAlphaInvMode(p_dma2d, LL_DMA2D_ALPHA_REGULAR);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the input alpha inversion is enabled or disabled
  * @param  hdma2d                             Pointer to a hal_dma2d_handle_t structure
  * @param  input    Input source. This parameter can be one of the following values:
  *                  HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @retval HAL_DMA2D_ALPHA_INVERSION_DISABLED Input alpha inversion is disabled
  * @retval HAL_DMA2D_ALPHA_INVERSION_ENABLED  Input alpha inversion is enabled
  */
hal_dma2d_alpha_inversion_status_t HAL_DMA2D_IsEnabledInputAlphaInversion(const hal_dma2d_handle_t *hdma2d,
                                                                          hal_dma2d_input_t input)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_dma2d_alpha_inversion_status_t status = HAL_DMA2D_ALPHA_INVERSION_DISABLED;


  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (input == HAL_DMA2D_INPUT_FG)
  {
    if (LL_DMA2D_FGND_GetAlphaInvMode(p_dma2d) != 0U)
    {
      status = HAL_DMA2D_ALPHA_INVERSION_ENABLED;
    }
  }
  else
  {
    if (LL_DMA2D_BGND_GetAlphaInvMode(p_dma2d) != 0U)
    {
      status = HAL_DMA2D_ALPHA_INVERSION_ENABLED;
    }
  }
  return status;
}


/**
  * @brief  Set the line offset mode
  * @param  hdma2d            Pointer to a hal_dma2d_handle_t structure
  * @param  line_offset_mode  Inputs and output line offset mode
  *                           This parameter is an element of hal_dma2d_line_offset_mode_t enumeration
  * @retval HAL_OK            Line offset mode has been correctly configured
  */
hal_status_t HAL_DMA2D_SetLineOffsetMode(hal_dma2d_handle_t *hdma2d,
                                         hal_dma2d_line_offset_mode_t line_offset_mode)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_LINE_OFFSET_MODE(line_offset_mode));

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetLineOffsetMode(p_dma2d, (uint32_t)line_offset_mode);

  return HAL_OK;
}

/**
  * @brief  Get the line offset mode
  * @param  hdma2d                       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_DMA2D_LINE_OFFSET_PIXELS Line offsets expressed in pixels
  * @retval HAL_DMA2D_LINE_OFFSET_BYTES  Line offsets expressed in bytes
  */
hal_dma2d_line_offset_mode_t HAL_DMA2D_GetLineOffsetMode(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;
  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  return (hal_dma2d_line_offset_mode_t) LL_DMA2D_GetLineOffsetMode(p_dma2d);
}


/**
  * @brief  Enable the output byte swap
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       output byte swap successfully enabled
  */
hal_status_t HAL_DMA2D_EnableOutputByteSwap(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetOutputSwapMode(p_dma2d, LL_DMA2D_SWAP_MODE_TWO_BY_TWO);

  return HAL_OK;
}

/**
  * @brief  Disable the output byte swap
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       output byte swap successfully disable
  */
hal_status_t HAL_DMA2D_DisableOutputByteSwap(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetOutputSwapMode(p_dma2d, LL_DMA2D_SWAP_MODE_REGULAR);

  return HAL_OK;
}

/**
  * @brief  Check if the output byte swap is enabled or disabled
  * @param  hdma2d                       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_DMA2D_BYTE_SWAP_DISABLED Bytes in regular order in output FIFO
  * @retval HAL_DMA2D_BYTE_SWAP_ENABLED  Bytes are swapped two by two in output FIFO
  */
hal_dma2d_byte_swap_status_t HAL_DMA2D_IsEnabledOutputByteSwap(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_dma2d_byte_swap_status_t status = HAL_DMA2D_BYTE_SWAP_DISABLED;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_GetOutputSwapMode(p_dma2d) != 0U)
  {
    status = HAL_DMA2D_BYTE_SWAP_ENABLED;
  }

  return status;
}
/**
  * @brief  Enable and configure the line watermark interrupt
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @param  line         Line watermark value between Min_Data=0 and Max_Data=0xFFFF
  * @retval HAL_OK       Line watermark interrupt successfully enabled and configured
  */
hal_status_t HAL_DMA2D_EnableWaterMark(hal_dma2d_handle_t *hdma2d, uint32_t line)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(line <= DMA2D_MAX_LINE_WATERMARK);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetLineWatermark(p_dma2d, line);

  LL_DMA2D_EnableIT_TW(p_dma2d);

  return HAL_OK;
}

/**
  * @brief  Disable line watermark interrupt
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       Line watermark interrupt successfully disable
  */
hal_status_t HAL_DMA2D_DisableWaterMark(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_DisableIT_TW(p_dma2d);

  return HAL_OK;
}

/**
  * @brief  Check if the line watermark interrupt is enabled or disabled
  * @param  hdma2d                        Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_DMA2D_WATER_MARK_DISABLED Transfer watermark interrupt is Disabled
  * @retval HAL_DMA2D_WATER_MARK_ENABLED  Transfer watermark interrupt is Enabled
  */
hal_dma2d_watermark_status_t HAL_DMA2D_IsEnabledWaterMark(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_dma2d_watermark_status_t status = HAL_DMA2D_WATER_MARK_DISABLED;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_IsEnabledIT_TW(p_dma2d) == 1U)
  {
    status = HAL_DMA2D_WATER_MARK_ENABLED;
  }

  return status;
}

/**
  * @brief  Get the line watermark interrupt, expressed on 16 bits ([15:0] bits)
  * @param  hdma2d     Pointer to a hal_dma2d_handle_t structure
  * @retval uint32_t   Line watermark value between Min_Data=0 and Max_Data=0xFFFF
  */
uint32_t HAL_DMA2D_GetWaterMarkLine(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  return LL_DMA2D_GetLineWatermark(p_dma2d);
}

/**
  * @brief  Enable the dead time
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       Dead Time successfully enabled
  */
hal_status_t HAL_DMA2D_EnableDeadTime(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_EnableDeadTime(p_dma2d);

  return HAL_OK;
}

/**
  * @brief  Disable the dead time
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_OK       Dead Time successfully disable
  */
hal_status_t HAL_DMA2D_DisableDeadTime(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_DisableDeadTime(p_dma2d);

  return HAL_OK;
}

/**
  * @brief  Check if the dead time is enabled or disabled
  * @param  hdma2d                        Pointer to a hal_dma2d_handle_t structure
  * @retval HAL_DMA2D_DEAD_TIME_DISABLED  The dead time between two consecutive accesses on the AHB master port
  *                                       is disabled
  * @retval HAL_DMA2D_DEAD_TIME_ENABLED   The dead time between two consecutive accesses on the AHB master port
  *                                       is enabled
  */
hal_dma2d_dead_time_status_t HAL_DMA2D_IsEnabledDeadTime(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;
  hal_dma2d_dead_time_status_t status = HAL_DMA2D_DEAD_TIME_DISABLED;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  if (LL_DMA2D_IsEnabledDeadTime(p_dma2d) == 1U)
  {
    status = HAL_DMA2D_DEAD_TIME_ENABLED;
  }

  return status;
}

/**
  * @brief  Set the minimum clock cycle dead time value between two consecutive accesses on the AHB master port
  * @param  hdma2d            Pointer to a hal_dma2d_handle_t structure
  * @param  dead_time_cycle   Clock cycle dead time value between two consecutive accesses on the AHB master port
  * @retval HAL_OK            Dead time has been correctly configured
  */
hal_status_t HAL_DMA2D_SetConfigDeadTime(hal_dma2d_handle_t *hdma2d, uint8_t dead_time_cycle)
{
  DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_SetDeadTime(p_dma2d, dead_time_cycle);

  return HAL_OK;
}

/**
  * @brief  Get the clock cycle dead time value
  * @param  hdma2d     Pointer to a hal_dma2d_handle_t structure
  * @retval uint8_t    Clock cycle dead time value
  */
uint8_t HAL_DMA2D_GetConfigDeadTime(const hal_dma2d_handle_t *hdma2d)
{
  const DMA2D_TypeDef *p_dma2d;

  ASSERT_DBG_PARAM(hdma2d != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_ACTIVE  \
                   | (uint32_t)HAL_DMA2D_STATE_CLUT_LOADING_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  return (uint8_t) LL_DMA2D_GetDeadTime(p_dma2d);
}

/**
  * @brief  Manually program a CLUT memory index, it can be RGB888 or ARGB8888 format
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure that contains
  *                      the configuration information for the DMA2D
  * @param  input        Input source. This parameter can be one of the following values:
  *                      HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @param  color_index  Index to be loaded
  * @param  color        color to be loaded
  * @warning This API is intended to update one color of th CLUT.
  *          The given color value must respect the given CLUT color format RGB888 or ARGB8888 provided by
  *          the API HAL_DMA2D_StartCLUTLoad or HAL_DMA2D_StartCLUTLoad_IT
  * @retval HAL_OK       CLUT value manually loaded successfully
  */
hal_status_t HAL_DMA2D_SetCLUTColorIndex(hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input, uint32_t color_index, \
                                         uint32_t color)
{
  DMA2D_TypeDef *p_dma2d;
  uint32_t blue_reg;
  uint32_t blue_pos_bit;
  uint32_t *p_clut;
  uint32_t color_mode;
  uint32_t tmp_color;
  uint32_t tmp_reg;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));
  ASSERT_DBG_PARAM(color_index <= DMA2D_MAX_CLUT_COLOR_INDEX);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  /* Get the CLUT address and CLUT color mode */
  if (input == HAL_DMA2D_INPUT_BG)
  {
    p_clut = (uint32_t *)((uint32_t)(&p_dma2d->BGCLUT));
    color_mode = LL_DMA2D_BGND_GetCLUTColorMode(p_dma2d);
  }
  else
  {
    p_clut = (uint32_t *)((uint32_t)(&p_dma2d->FGCLUT));
    color_mode = LL_DMA2D_FGND_GetCLUTColorMode(p_dma2d);
  }

  if (color_mode == LL_DMA2D_CLUT_COLOR_MODE_ARGB8888)
  {
    p_clut[color_index] = color;
  }
  else
  {
    /* CLUT color mode RGB888*/
    blue_reg  = (color_index * 3U) / 4U;
    blue_pos_bit  = ((color_index * 3U) % 4U) * 8U;

    if (blue_pos_bit < 16U)
    {
      tmp_color = (color & 0x00FFFFFFU) << blue_pos_bit;
      tmp_reg = p_clut[blue_reg] & (~(0x00FFFFFFU << blue_pos_bit));

      p_clut[blue_reg] = tmp_color | tmp_reg;
    }
    else
    {
      tmp_color = (color & 0x0000FFFFU) << blue_pos_bit;
      tmp_reg = p_clut[blue_reg] & (~(0x0000FFFFU << blue_pos_bit));

      p_clut[blue_reg] = tmp_color | tmp_reg;

      tmp_color = (color & 0x00FFFF00U) >> (32U - blue_pos_bit);
      tmp_reg = p_clut[blue_reg + 1U] & (~(0x00FFFF00U >> (32U - blue_pos_bit)));
      p_clut[blue_reg + 1U] = tmp_color | tmp_reg;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Read a CLUT memory index. It can be a 24 or 32 bits format
  * @param  hdma2d       Pointer to a hal_dma2d_handle_t structure that contains
  *                      the configuration information for the DMA2D
  * @param  input        Input source. This parameter can be one of the following values:
  *                      HAL_DMA2D_INPUT_BG or HAL_DMA2D_INPUT_FG
  * @param  color_index  Index of the color to read
  * @note   The return color follows the given CLUT color format RGB888 or ARGB8888 provided
  *         by the API HAL_DMA2D_StartCLUTLoad or HAL_DMA2D_StartCLUTLoad_IT
  * @retval uint32_t     This function returns the  color corresponding to the CLUT given color index
  */
uint32_t HAL_DMA2D_GetCLUTColorIndex(const hal_dma2d_handle_t *hdma2d, hal_dma2d_input_t input, uint32_t color_index)
{
  const DMA2D_TypeDef *p_dma2d;
  uint32_t color;
  uint32_t blue_reg;
  uint32_t blue_pos_bit;
  const uint32_t *p_clut;
  uint32_t color_mode;

  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(IS_DMA2D_INPUT_SOURCE(input));
  ASSERT_DBG_PARAM(color_index <= DMA2D_MAX_CLUT_COLOR_INDEX);


  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_ACTIVE \
                   | (uint32_t)HAL_DMA2D_STATE_XFER_SUSPEND);

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  /* Get the CLUT address and CLUT color mode */
  if (input == HAL_DMA2D_INPUT_BG)
  {
    p_clut = (uint32_t *)((uint32_t)(&p_dma2d->BGCLUT));
    color_mode = LL_DMA2D_BGND_GetCLUTColorMode(p_dma2d);
  }
  else
  {
    p_clut = (uint32_t *)((uint32_t)(&p_dma2d->FGCLUT));
    color_mode = LL_DMA2D_FGND_GetCLUTColorMode(p_dma2d);
  }

  if (color_mode == LL_DMA2D_CLUT_COLOR_MODE_ARGB8888)
  {
    color = p_clut[color_index];
  }
  else
  {
    /* CLUT color mode RGB888*/
    blue_reg  = (color_index * 3U) / 4U;
    blue_pos_bit  = ((color_index * 3U) % 4U) * 8U;

    if (blue_pos_bit < 16U)
    {
      color = (p_clut[blue_reg] & (0x00FFFFFFU << blue_pos_bit)) >> blue_pos_bit;
    }
    else
    {
      color = (p_clut[blue_reg] & 0xFFFF0000U) >> blue_pos_bit;
      color |= (p_clut[(blue_reg + 1U)] & 0x0000FFFFU) << (32U - blue_pos_bit);
      color &= 0x00FFFFFFU;
    }
  }

  return color;
}

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group6
  * @{
This subsection provides a set of functions allowing to register the DMA2D process and error callbacks:
- HAL_DMA2D_RegisterXferCpltCallback() register the DMA2D transfer complete callback
- HAL_DMA2D_RegisterErrorCallback() register the DMA2D transfer error callback
- HAL_DMA2D_RegisterWaterMarkCallback() register the DMA2D line watermark callback
- HAL_DMA2D_RegisterCLUTLoadingCpltCallback() register the DMA2D CLUT loading complete callback

The following are the default process and errors weak callbacks:
- HAL_DMA2D_XferCpltCallback() DMA2D transfer complete default weak callback
- HAL_DMA2D_ErrorCallback() DMA2D error default weak callback
- HAL_DMA2D_WaterMarkCallback() DMA2D line watermark transfer complete default weak callback
- HAL_DMA2D_CLUTLoadingCpltCallback() DMA2D CLUT loading complete default weak callback
  */

#if (USE_HAL_DMA2D_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the DMA2D transfer complete callback
  * @param  hdma2d            Pointer to DMA2D handle
  * @param  p_callback        Specifies the transfer complete callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            DMA2D transfer complete callback is successfully registered
  */
hal_status_t HAL_DMA2D_RegisterXferCpltCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma2d->p_xfer_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the DMA2D error callback
  * @param  hdma2d            Pointer to DMA2D handle
  * @param  p_callback        Specifies the error callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            DMA2D error callback is successfully registered
  */
hal_status_t HAL_DMA2D_RegisterErrorCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma2d->p_error_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the DMA2D line watermark transfer complete callback
  * @param  hdma2d            Pointer to DMA2D handle
  * @param  p_callback        Specifies the line watermarked transfer complete callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            DMA2D the line watermarked transfer callback is successfully registered
  */
hal_status_t HAL_DMA2D_RegisterWaterMarkCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma2d->p_watermark_cb = p_callback;

  return HAL_OK;
}

#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
/**
  * @brief  Register the DMA2D CLUT loading complete callback
  * @param  hdma2d            Pointer to DMA2D handle
  * @param  p_callback        Specifies the CLUT loading complete callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            DMA2D CLUT loading complete callback is successfully registered
  */
hal_status_t HAL_DMA2D_RegisterCLUTLoadingCpltCallback(hal_dma2d_handle_t *hdma2d, hal_dma2d_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hdma2d->global_state, (uint32_t)HAL_DMA2D_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma2d->p_clut_loading_cplt_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
#endif /* USE_HAL_DMA2D_REGISTER_CALLBACKS */

/**
  * @brief DMA2D transfer complete default callback
  * @param hdma2d Pointer to DMA2D handle
  */
__WEAK void HAL_DMA2D_XferCpltCallback(hal_dma2d_handle_t *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma2d);

  /*! <b>WARNING:</b> This function must not be modified; when the callback is needed,
                    the HAL_DMA2D_XferCpltCallback() can be implemented in the user file. */
}

/**
  * @brief DMA2D error default callback
  * @param hdma2d Pointer to DMA2D handle
  */
__WEAK void HAL_DMA2D_ErrorCallback(hal_dma2d_handle_t *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma2d);

  /*! <b>WARNING:</b> This function must not be modified; when the callback is needed,
                   the HAL_DMA2D_ErrorCallback() can be implemented in the user file. */
}

/**
  * @brief DMA2D line watermark default callback
  * @param hdma2d Pointer to DMA2D handle
  */
__WEAK void HAL_DMA2D_WaterMarkCallback(hal_dma2d_handle_t *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma2d);

  /*! <b>WARNING:</b> This function must not be modified; when the callback is needed,
                   the HAL_DMA2D_WaterMarkCallback() can be implemented in the user file. */
}

#if defined(USE_HAL_DMA2D_CLUT_IRQ) && (USE_HAL_DMA2D_CLUT_IRQ == 1)
/**
  * @brief DMA2D CLUT loading complete default callback
  * @param hdma2d Pointer to DMA2D handle
  */
__WEAK void HAL_DMA2D_CLUTLoadingCpltCallback(hal_dma2d_handle_t *hdma2d)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma2d);

  /*! <b>WARNING:</b> This function must not be modified; when the callback is needed,
                   the HAL_DMA2D_CLUTLoadingCpltCallback() can be implemented in the user file. */
}
#endif /* USE_HAL_DMA2D_CLUT_IRQ */
/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group7
  * @{
This subsection provides a set of functions allowing to retrieve peripheral state and last process errors.
- HAL_DMA2D_GetState() Returns the DMA2D handle state
- HAL_DMA2D_GetLastErrorCodes() Returns last occurred error code
  */
/* Peripheral State functions *****************************************************************************************/
/**
  * @brief  Get the DMA2D current state
  * @param hdma2d   Pointer to DMA2D handle
  * @retval DMA2D state, can be one of hal_dma2d_state_t enumeration values
  */
hal_dma2d_state_t HAL_DMA2D_GetState(const hal_dma2d_handle_t *hdma2d)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);

  return hdma2d->global_state;
}
#if defined(USE_HAL_DMA2D_GET_LAST_ERRORS) && (USE_HAL_DMA2D_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last error codes
  * @param  hdma2d  Pointer to DMA2D handle
  * @retval Last error codes
  */
uint32_t HAL_DMA2D_GetLastErrorCodes(const hal_dma2d_handle_t *hdma2d)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);

  return hdma2d->last_error_codes;
}
#endif /* USE_HAL_DMA2D_GET_LAST_ERRORS */
/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group8
  * @{
This subsection provides functions allowing to Set and Get user data
- HAL_DMA2D_SetUserData() Store the user data into the DMA2D handle
- HAL_DMA2D_GetUserData() Retrieve the user data from the DMA2D handle
  */

#if defined(USE_HAL_DMA2D_USER_DATA) && (USE_HAL_DMA2D_USER_DATA == 1)
/**
  * @brief Store the user data into the DMA2D handle
  * @param hdma2d       Pointer to DMA2D handle
  * @param p_user_data  Pointer to the user data
  */
void HAL_DMA2D_SetUserData(hal_dma2d_handle_t *hdma2d, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);

  hdma2d->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the DMA2D handle
  * @param hdma2d   Pointer to DMA2D handle
  * @retval Pointer to the user data
  */
const void *HAL_DMA2D_GetUserData(const hal_dma2d_handle_t *hdma2d)
{
  ASSERT_DBG_PARAM(hdma2d != NULL);

  return (hdma2d->p_user_data);
}
#endif /* USE_HAL_DMA2D_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Functions DMA2D Private Functions
  * @{
  */

/**
  * @brief Configure the background registers
  * @param p_dma2d  Pointer to DMA2D_TypeDef instance registers structure
  * @param bg_cfg   Pointer to the Background Configuration Structure
  */
static void DMA2D_SetConfigBackground(DMA2D_TypeDef *p_dma2d, const hal_dma2d_input_config_t *bg_cfg)
{
  LL_DMA2D_BGND_SetMemAddr(p_dma2d, (uint32_t) bg_cfg->p_src);

  LL_DMA2D_BGND_SetLineOffset(p_dma2d, bg_cfg->offset);

  LL_DMA2D_BGND_SetARGBMode(p_dma2d, (uint32_t) bg_cfg->color_mode, \
                            (uint32_t) bg_cfg->alpha_mode, \
                            (bg_cfg->alpha_value & DMA2D_MAX_INPUT_ALPHA));
}

/**
  * @brief Configure the foreground registers
  * @param p_dma2d  Pointer to DMA2D_TypeDef instance registers structure
  * @param fg_cfg   Pointer to the Foreground Configuration Structure
  */
static void DMA2D_SetConfigForeground(DMA2D_TypeDef *p_dma2d, const hal_dma2d_input_config_t *fg_cfg)
{
  LL_DMA2D_FGND_SetMemAddr(p_dma2d, (uint32_t) fg_cfg->p_src);

  LL_DMA2D_FGND_SetLineOffset(p_dma2d, fg_cfg->offset);

  LL_DMA2D_FGND_SetARGBMode(p_dma2d, (uint32_t) fg_cfg->color_mode, \
                            (uint32_t) fg_cfg->alpha_mode, \
                            (fg_cfg->alpha_value & DMA2D_MAX_INPUT_ALPHA));
}

/**
  * @brief Configure the output registers
  * @param p_dma2d      Pointer to DMA2D_TypeDef instance registers structure
  * @param output_cfg   Pointer to the output Configuration Structure
  * @param width        The width of data to be transferred from source to destination
  *                     Expressed in number of pixels per line
  * @param height       The height of data to be transferred from source to destination
  *                     Expressed in number of lines
  */
static void DMA2D_SetConfigOutput(DMA2D_TypeDef *p_dma2d, const hal_dma2d_output_config_t *output_cfg, \
                                  uint32_t width, uint32_t height)
{
  LL_DMA2D_ConfigAreaSize(p_dma2d, width, height);

  LL_DMA2D_SetOutputMemAddr(p_dma2d, (uint32_t) output_cfg->p_dest);

  /* Set DMA2D output color mode */
  uint32_t cr_reg;
  cr_reg = LL_DMA2D_READ_REG(p_dma2d, OPFCCR) & (~(DMA2D_OPFCCR_CM | DMA2D_OPFCCR_RBS));
  LL_DMA2D_WRITE_REG(p_dma2d, OPFCCR, cr_reg | (uint32_t) output_cfg->color_mode);

  LL_DMA2D_SetLineOffset(p_dma2d, output_cfg->offset);
}

/**
  * @brief Abort an active Xfer or CLUT loading
  * @param hdma2d   Pointer to DMA2D handle
  * @retval HAL_ERROR DMA2D not aborted
  * @retval HAL_OK    DMA2D is successfully aborted the on going transfer or CLUT loading
  */
static hal_status_t DMA2D_Abort(hal_dma2d_handle_t *hdma2d)
{
  DMA2D_TypeDef *p_dma2d;
  hal_status_t status = HAL_ERROR;
  uint32_t tickstart;
  uint32_t xfer_state;
  uint32_t bg_state;
  uint32_t fg_state;

  p_dma2d = DMA2D_GET_INSTANCE(hdma2d);

  LL_DMA2D_DisableIT(p_dma2d, LL_DMA2D_IT_CEIE | LL_DMA2D_IT_CTCIE  \
                     | LL_DMA2D_IT_CAEIE | LL_DMA2D_IT_TWIE  \
                     | LL_DMA2D_IT_TCIE | LL_DMA2D_IT_TEIE);

  LL_DMA2D_ClearFlag(p_dma2d, LL_DMA2D_FLAG_ALL);

  LL_DMA2D_Abort(p_dma2d);


  tickstart = HAL_GetTick();

  do
  {
    xfer_state = LL_DMA2D_IsTransferOngoing(p_dma2d);
    bg_state   = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
    fg_state   = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

    if ((HAL_GetTick() - tickstart) > DMA2D_TIMEOUT_ABORT)
    {
      break;
    }
  } while ((xfer_state | bg_state | fg_state) != 0U);

  xfer_state = LL_DMA2D_IsTransferOngoing(p_dma2d);
  bg_state   = LL_DMA2D_BGND_IsEnabledCLUTLoad(p_dma2d);
  fg_state   = LL_DMA2D_FGND_IsEnabledCLUTLoad(p_dma2d);

  if ((xfer_state | bg_state | fg_state) == 0U)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */

#endif /* USE_HAL_DMA2D_MODULE */

/**
  * @}
  */
#endif /* defined (DMA2D) */
/**
  * @}
  */
