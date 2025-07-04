/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_ltdc.c
  * @brief   LTDC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the LTDC peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
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
#if defined (LTDC)
/** @addtogroup LTDC
  * @{
# How to use the LTDC HAL module driver
## The LTDC HAL driver can be used as follows:
- Declare a hal_ltdc_handle_t handle structure, for example:  hal_ltdc_handle_t  hltdc;
- Initialize the LTDC low level resources :
  - Enable the LTDC interface clock (if not enabled in HAL_LTDC_Init() when USE_HAL_LTDC_CLK_ENABLE_MODEL
  set to HAL_CLK_ENABLE_NO)
  - Configure the LTDC clock source
  - NVIC configuration if you need to use interrupt process
    - Configure the LTDC interrupt priority
    - Enable the NVIC LTDC IRQ Channel
- Use HAL_LTDC_Init() function to initialize the LTDC handle and associate the physical instance.
- Configure the LTDC output timing synchronization using HAL_LTDC_SetConfig() function.
- Configure the needed layer(s) using HAL_LTDC_SetConfigLayer().
- And finally start the LTDC display by calling HAL_LTDC_Start().
## Callback registration
When the compilation flag **USE_HAL_LTDC_REGISTER_CALLBACKS** is set to 1,
use Functions **HAL_LTDC_RegisterXxxCallback()** to register an interrupt callback.
When the compilation flag is set to 0 or not defined, the callback registration feature is not available
and all callbacks are set to the corresponding weak functions.
## Configuration inside the LTDC driver
Config defines                  | Description           | Default value     | Note
--------------------------------| --------------------- | ------------------| ------------------------------------------
USE_HAL_LTDC_MODULE             | from hal_conf.h       | 1                 | When set, HAL LTDC module is enabled
USE_HAL_LTDC_REGISTER_CALLBACKS | from hal_conf.h       | 0                 | When set, enable the register callbacks
USE_HAL_LTDC_CLK_ENABLE_MODEL   | from hal_conf.h       | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PARAM             | from hal_conf.h       | 0                 | When set, the vital parameters (pointers
                                |                       |                   | or sizes) are checked in runtime
USE_ASSERT_DBG_PARAM            | from PreProcessor env | None              | When defined, enable the params assert
USE_ASSERT_DBG_STATE            | from PreProcessor env | None              | When defined, enable the state assert
USE_HAL_LTDC_USER_DATA          | from hal_conf.h       | 0                 | When set, user data is defined in handle
USE_HAL_LTDC_GET_LAST_ERRORS    | from hal_conf.h       | 0                 | When set, user can get the last error code
  */
#if defined (USE_HAL_LTDC_MODULE) && (USE_HAL_LTDC_MODULE == 1)
/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/** @defgroup LTDC_Private_Constants LTDC Private Constants
  * @{
  */

/*! LTDC 100ms timeout define                   */
#define LTDC_TIMEOUT_VALUE ((uint32_t)100)

/*! LTDC Maximum value for rgb888 value define  */
#define LTDC_MAX_RGB888   ((uint32_t)0x00FFFFFF)

/*! LTDC Maximum value for 8 bit define         */
#define LTDC_MAX_8BITS    ((uint32_t)0x000000FF)

/*! LTDC Maximum value for 11 bits define       */
#define LTDC_MAX_11BITS    ((uint32_t)0x000007FF)

/*! LTDC Maximum value for 12 bits define       */
#define LTDC_MAX_12BITS    ((uint32_t)0x00000FFF)

/*! LTDC Maximum value for 16 bits define       */
#define LTDC_MAX_16BITS    ((uint32_t)0x0000FFFF)

/*! LTDC registers offsets define               */
#define LTDC_CFBLR_CFBLL_VAL_OFFSET    ((uint32_t)3)


/**
  * @}
  */
/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup LTDC_Private_Macros LTDC Private Macros
  * @{
  */
/**
  * @brief LTDC get Instance macro
  */
#define LTDC_GET_INSTANCE(handle)  ((LTDC_TypeDef *)((uint32_t)(handle)->instance))
/**
  * @brief LTDC get layer start address
  */
#define LTDC_LAYER(handle, layer)  ((LTDC_Layer_TypeDef *)((((uint32_t)((handle)->instance))  \
                                                            + 0x84U + \
                                                            (0x80U*((uint32_t)layer)))))


/**
  * @brief Assert macro for layer index
  */
#define IS_LTDC_LAYER_INDEX(layer) (((layer) == HAL_LTDC_LAYER_1) \
                                    || ((layer) == HAL_LTDC_LAYER_2))

/**
  * @brief Assert macro for the reload type
  */
#define IS_LTDC_RELOAD(reload_type) (((reload_type) == HAL_LTDC_RELOAD_IMMEDIATE) \
                                     || ((reload_type) == HAL_LTDC_RELOAD_VERTICAL_BLANKING))

/**
  * @brief Assert macro for horizontal synchronization polarity
  */
#define IS_LTDC_HSPOL(hsync_polarity) (((hsync_polarity) == HAL_LTDC_HSYNC_POLARITY_LOW) \
                                       || ((hsync_polarity) == HAL_LTDC_HSYNC_POLARITY_HIGH))

/**
  * @brief Assert macro for vertical synchronization polarity
  */
#define IS_LTDC_VSPOL(vsync_polarity) (((vsync_polarity) == HAL_LTDC_VSYNC_POLARITY_LOW) \
                                       || ((vsync_polarity) == HAL_LTDC_VSYNC_POLARITY_HIGH))

/**
  * @brief Assert macro for data enable polarity
  */
#define IS_LTDC_DEPOL(de_polarity) (((de_polarity) == HAL_LTDC_DATA_ENABLE_POLARITY_LOW) \
                                    || ((de_polarity) == HAL_LTDC_DATA_ENABLE_POLARITY_HIGH))

/**
  * @brief Assert macro for pixel clock polarity
  */
#define IS_LTDC_PCPOL(pc_polarity) (((pc_polarity) == HAL_LTDC_PIXEL_CLOCK_POLARITY_LOW) \
                                    || ((pc_polarity) == HAL_LTDC_PIXEL_CLOCK_POLARITY_HIGH))

/**
  * @brief Assert macro for the horizontal synchronization width value
  */
#define IS_LTDC_HSYNC(hsync) ((hsync - 1U) <= (LTDC_SSCR_HSW >> LTDC_SSCR_HSW_Pos))

/**
  * @brief Assert macro for the vertical synchronization height value
  */
#define IS_LTDC_VSYNC(vsync) ((vsync - 1U) <= LTDC_SSCR_VSH)

/**
  * @brief Assert macro for the accumulated horizontal back porch value
  */
#define IS_LTDC_AHBP(hsync, hbp) ((hsync + hbp - 1U) <= (LTDC_BPCR_AHBP >> LTDC_BPCR_AHBP_Pos))

/**
  * @brief Assert macro for the accumulated vertical back porch value
  */
#define IS_LTDC_AVBP(vsync, vbp) ((vsync + vbp - 1U) <= LTDC_BPCR_AVBP)

/**
  * @brief Assert macro for the accumulated active width value
  */
#define IS_LTDC_AAW(hsync, hbp, aw) ((hsync + hbp + aw - 1U) <= (LTDC_AWCR_AAW >> LTDC_AWCR_AAW_Pos))

/**
  * @brief Assert macro for the accumulated active height value
  */
#define IS_LTDC_AAH(vsync, vbp, ah) ((vsync + vbp + ah - 1U) <= LTDC_AWCR_AAH)

/**
  * @brief Assert macro for the total height value
  */
#define IS_LTDC_TOTALH(vsync, vbp, ah, vfp) ((vsync + vbp + ah + vfp - 1U) <= LTDC_TWCR_TOTALH)

/**
  * @brief Assert macro for the total width value
  */
#define IS_LTDC_TOTALW(hsync, hbp, aw, hfp) ((hsync + hbp + aw + hfp - 1U) <= (LTDC_TWCR_TOTALW >> \
                                                                               LTDC_TWCR_TOTALW_Pos))

/**
  * @brief Assert macro for the window horizontal start position
  */
#define IS_LTDC_WHSTPOS(x0) ((x0) <= LTDC_LxWHPCR_WHSTPOS)

/**
  * @brief Assert macro for the window horizontal stop position
  */
#define IS_LTDC_WHSPPOS(x1) ((x1) <= (LTDC_LxWHPCR_WHSPPOS >> LTDC_LxWHPCR_WHSPPOS_Pos))

/**
  * @brief Assert macro for the window vertical start position
  */
#define IS_LTDC_WVSTPOS(y0) ((y0) <= LTDC_LxWVPCR_WVSTPOS)

/**
  * @brief Assert macro for the window vertical stop position
  */
#define IS_LTDC_WVSPPOS(y1) ((y1) <= (LTDC_LxWVPCR_WVSPPOS >> LTDC_LxWVPCR_WVSPPOS_Pos))

/**
  * @brief Assert macro for the pixel format
  */
#define IS_LTDC_PIXEL_FORMAT(pixel_format) (((uint32_t)pixel_format) <= 0x07U)

/**
  * @brief Assert macro for the blending factor 1
  */
#define IS_LTDC_BLENDING_FACTOR1(blending_factor1) ((((uint32_t)blending_factor1) == HAL_LTDC_BLENDING_FACTOR1_CA)  \
                                                    || (((uint32_t)blending_factor1) ==                             \
                                                        HAL_LTDC_BLENDING_FACTOR1_PA_X_CA))

/**
  * @brief Assert macro for the blending factor 2
  */
#define IS_LTDC_BLENDING_FACTOR2(blending_factor2) ((((uint32_t)blending_factor2) ==         \
                                                     HAL_LTDC_BLENDING_FACTOR2_1_MINUS_CA)   \
                                                    || (((uint32_t)blending_factor2) ==      \
                                                        HAL_LTDC_BLENDING_FACTOR2_1_MINUS_PA_X_CA))

/**
  * @brief Assert macro for the frame buffer width
  */
#define IS_LTDC_BUFFER_WIDTH(frame_buffer_width) ((frame_buffer_width) <= LTDC_LxCFBLR_CFBLL)

/**
  * @brief Assert macro for the frame buffer height
  */
#define IS_LTDC_BUFFER_HEIGHT(frame_buffer_height) ((frame_buffer_height) <= LTDC_LxCFBLNR_CFBLNBR)

/**
  * @brief Assert macro for the LTDC pitch in byte value
  */
#define IS_LTDC_PITCH_IN_BYTES(pitch_byte) ((pitch_byte) <= (LTDC_LxCFBLR_CFBP >> LTDC_LxCFBLR_CFBP_Pos))

/**
  * @brief Assert macro for Transfer Error and FIFO Underrun interrupts
  */
#define IS_LTDC_ERROR_INTERRUPT(interrupts) (((interrupts) == HAL_LTDC_IT_NONE)              \
                                             || ((interrupts) == HAL_LTDC_IT_FIFO_UNDERRUN)  \
                                             || ((interrupts) == HAL_LTDC_IT_TRANSFER_ERROR) \
                                             || ((interrupts) == (HAL_LTDC_IT_FIFO_UNDERRUN  \
                                                                  | HAL_LTDC_IT_TRANSFER_ERROR)))

/**
  * @brief Assert macro for the line detection interrupt position
  */
#define IS_LTDC_LIPOS(line) ((line) <= LTDC_MAX_11BITS)
/**
  * @}
  */
/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup LTDC_Private_Variables LTDC Private Variables
  * @{
  */
/*! Number of byte per pixel for each pixel format.*/
static const uint32_t LTDC_BytePerPixelMap[] = {4, 3, 2, 2, 2, 1, 1, 2};
/**
  * @}
  */
/* Private functions prototypes --------------------------------------------------------------------------------------*/
/** @addtogroup LTDC_Private_Functions LTDC Private Functions
  * @{
  */
static void LTDC_HandleErrorIT(hal_ltdc_handle_t *hltdc, uint32_t flag_status, uint32_t it_sources);
/**
  * @}
  */
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup LTDC_Exported_Functions
  * @{
  */
/** @addtogroup LTDC_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and deinitialize the LTDC peripheral:
- HAL_LTDC_Init() to initialize the selected HAL LTDC handle and associate an LTDC peripheral instance
- HAL_LTDC_DeInit() to de-initialize the given HAL LTDC instance by disabling the LTDC and LTDC layers,
and resetting the state machine
  */
/**
  * @brief  Initialize the selected HAL LTDC handle and associate a LTDC peripheral instance.
  * @param  hltdc             Pointer to a hal_ltdc_handle_t structure.
  * @param  instance          Specify the LTDC instance.
  * @retval HAL_INVALID_PARAM Invalid parameter when hltdc pointer is NULL.
  * @retval HAL_OK            HAL LTDC handle has been correctly initialized.
  */
hal_status_t HAL_LTDC_Init(hal_ltdc_handle_t *hltdc, hal_ltdc_t instance)
{
  ASSERT_DBG_PARAM(hltdc != NULL);

  ASSERT_DBG_PARAM(IS_LTDC_ALL_INSTANCE((LTDC_TypeDef *)(uint32_t)instance));
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hltdc == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hltdc->instance = instance;

#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
  hltdc->p_line_detection_cb = HAL_LTDC_LineDetectionCallback;
  hltdc->p_reload_event_cb   = HAL_LTDC_ReloadEventCallback;
  hltdc->p_error_cb          = HAL_LTDC_ErrorCallback;
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */

#if defined(USE_HAL_LTDC_USER_DATA) && (USE_HAL_LTDC_USER_DATA == 1)
  hltdc->p_user_data = NULL;
#endif /* USE_HAL_LTDC_USER_DATA */

#if defined (USE_HAL_LTDC_GET_LAST_ERRORS) && (USE_HAL_LTDC_GET_LAST_ERRORS == 1)
  hltdc->last_error_codes = HAL_LTDC_ERROR_NONE;
#endif /* USE_HAL_LTDC_GET_LAST_ERRORS */

#if defined(USE_HAL_LTDC_CLK_ENABLE_MODEL) && (USE_HAL_LTDC_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_LTDC_EnableClock();
#endif /* USE_HAL_LTDC_CLK_ENABLE_MODEL */

  hltdc->layer_state[HAL_LTDC_LAYER_1] = HAL_LTDC_LAYER_STATE_RESET;
  hltdc->layer_state[HAL_LTDC_LAYER_2] = HAL_LTDC_LAYER_STATE_RESET;

  hltdc->global_state   = HAL_LTDC_STATE_INIT;
  return HAL_OK;
}

/**
  * @brief  De-initialize the given HAL LTDC instance by disabling all interrupts,
  *         disabling the LTDC layers and LTDC display, and resetting the state machine.
  * @param  hltdc    Pointer to a hal_ltdc_handle_t structure.
  */
void HAL_LTDC_DeInit(hal_ltdc_handle_t *hltdc)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_ALL_INSTANCE(LTDC_GET_INSTANCE(hltdc)));

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  CLEAR_REG(p_ltdc->IER);

  CLEAR_REG(LTDC_LAYER(hltdc, (uint32_t)HAL_LTDC_LAYER_1)->CR);
  CLEAR_REG(LTDC_LAYER(hltdc, (uint32_t)HAL_LTDC_LAYER_2)->CR);
  CLEAR_REG(p_ltdc->GCR);

#if defined(USE_HAL_LTDC_USER_DATA) && (USE_HAL_LTDC_USER_DATA == 1)
  hltdc->p_user_data = NULL;
#endif /* USE_HAL_LTDC_USER_DATA */

  hltdc->layer_state[HAL_LTDC_LAYER_1] = HAL_LTDC_LAYER_STATE_RESET;
  hltdc->layer_state[HAL_LTDC_LAYER_2] = HAL_LTDC_LAYER_STATE_RESET;
  hltdc->global_state = HAL_LTDC_STATE_RESET;
}

/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to set and get the global LTDC peripheral configuration:
- HAL_LTDC_SetConfig() : Allowing to set the LTDC timing parameters. Once done the HAL LTDC global state goes to IDLE.
- HAL_LTDC_GetConfig() : Allowing to retrieve the LTDC timing parameters.
  */

/**
  * @brief  Configure the LTDC according to the user parameters.
  * @param  hltdc             Pointer to a hal_ltdc_handle_t structure.
  * @param  p_config          Pointer to a hal_ltdc_config_t structure that contains the LTDC configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK            LTDC instance has been correctly configured.
  */
hal_status_t HAL_LTDC_SetConfig(hal_ltdc_handle_t *hltdc, const hal_ltdc_config_t *p_config)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_HSPOL(p_config->hsync_polarity));
  ASSERT_DBG_PARAM(IS_LTDC_VSPOL(p_config->vsync_polarity));
  ASSERT_DBG_PARAM(IS_LTDC_DEPOL(p_config->data_enable_polarity));
  ASSERT_DBG_PARAM(IS_LTDC_PCPOL(p_config->pixel_clock_polarity));
  ASSERT_DBG_PARAM(IS_LTDC_HSYNC(p_config->hsync));
  ASSERT_DBG_PARAM(IS_LTDC_VSYNC(p_config->vsync));
  ASSERT_DBG_PARAM(IS_LTDC_AHBP(p_config->hsync, p_config->h_back_porch));
  ASSERT_DBG_PARAM(IS_LTDC_AVBP(p_config->vsync, p_config->v_back_porch));
  ASSERT_DBG_PARAM(IS_LTDC_AAH(p_config->hsync, p_config->h_back_porch, p_config->active_height));
  ASSERT_DBG_PARAM(IS_LTDC_AAW(p_config->vsync, p_config->v_back_porch, p_config->active_width));
  ASSERT_DBG_PARAM(IS_LTDC_TOTALW(p_config->hsync, p_config->h_back_porch, p_config->active_width,
                                  p_config->h_front_porch));
  ASSERT_DBG_PARAM(IS_LTDC_TOTALH(p_config->vsync, p_config->v_back_porch, p_config->active_height,
                                  p_config->v_front_porch));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_INIT | (uint32_t)HAL_LTDC_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  WRITE_REG(p_ltdc->SSCR, (((p_config->hsync) - 1U) << LTDC_SSCR_HSW_Pos) | ((p_config->vsync) - 1U));
  WRITE_REG(p_ltdc->BPCR, (((p_config->hsync) + (p_config->h_back_porch) - 1U) \
                           << LTDC_BPCR_AHBP_Pos) | ((p_config->vsync) + (p_config->v_back_porch) - 1U));
  WRITE_REG(p_ltdc->AWCR, (((p_config->hsync) + (p_config->h_back_porch)\
                            + (p_config->active_width) - 1U) << LTDC_AWCR_AAW_Pos) | ((p_config->vsync)\
                                + (p_config->v_back_porch) + (p_config->active_height) - 1U));
  WRITE_REG(p_ltdc->TWCR, (((p_config->hsync) + (p_config->h_back_porch) \
                            + (p_config->active_width) + (p_config->h_front_porch) - 1U) << LTDC_TWCR_TOTALW_Pos) \
            | ((p_config->vsync) + (p_config->v_back_porch) + (p_config->active_height) \
               + (p_config->v_front_porch) - 1U));
  MODIFY_REG(p_ltdc->GCR, (LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL), \
             ((uint32_t)(p_config->hsync_polarity) | (uint32_t)(p_config->vsync_polarity) \
              | (uint32_t)(p_config->data_enable_polarity) | (uint32_t)(p_config->pixel_clock_polarity)));

  hltdc->global_state = HAL_LTDC_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the LTDC configuration.
  * @param  hltdc    Pointer to a hal_ltdc_handle_t structure.
  * @param  p_config Pointer to a hal_ltdc_config_t structure that contains the LTDC configuration.
  */
void HAL_LTDC_GetConfig(const hal_ltdc_handle_t *hltdc, hal_ltdc_config_t *p_config)
{
  const LTDC_TypeDef *p_ltdc;

  uint32_t tmp;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  tmp = READ_REG(p_ltdc->SSCR);
  p_config->hsync = (tmp >> LTDC_SSCR_HSW_Pos) + 1U;
  p_config->vsync = (tmp & LTDC_SSCR_VSH) + 1U;
  tmp = READ_REG(p_ltdc->BPCR);
  p_config->h_back_porch = (tmp >> LTDC_BPCR_AHBP_Pos) - p_config->hsync + 1U;
  p_config->v_back_porch = (tmp & LTDC_BPCR_AVBP) - p_config->vsync + 1U;
  tmp = READ_REG(p_ltdc->AWCR);
  p_config->active_height = (tmp & LTDC_AWCR_AAH) - p_config->vsync - p_config->v_back_porch + 1U;
  p_config->active_width  = (tmp >> LTDC_AWCR_AAW_Pos) - p_config->hsync - p_config->h_back_porch + 1U;
  tmp = READ_REG(p_ltdc->TWCR);
  p_config->h_front_porch = (tmp >> LTDC_TWCR_TOTALW_Pos) - p_config->hsync - p_config->h_back_porch \
                            - p_config->active_width + 1U;
  p_config->v_front_porch = (tmp & LTDC_TWCR_TOTALH) - p_config->vsync - p_config->v_back_porch \
                            - p_config->active_height + 1U;
  tmp = READ_REG(p_ltdc->GCR);
  p_config->hsync_polarity = ((tmp & LTDC_GCR_HSPOL) == 0U) \
                             ? HAL_LTDC_HSYNC_POLARITY_LOW : HAL_LTDC_HSYNC_POLARITY_HIGH;
  p_config->vsync_polarity = ((tmp & LTDC_GCR_VSPOL) == 0U) \
                             ? HAL_LTDC_VSYNC_POLARITY_LOW : HAL_LTDC_VSYNC_POLARITY_HIGH;
  p_config->data_enable_polarity = ((tmp & LTDC_GCR_DEPOL) == 0U) \
                                   ? HAL_LTDC_DATA_ENABLE_POLARITY_LOW : HAL_LTDC_DATA_ENABLE_POLARITY_HIGH;
  p_config->pixel_clock_polarity = ((tmp & LTDC_GCR_PCPOL) == 0U) \
                                   ? HAL_LTDC_PIXEL_CLOCK_POLARITY_LOW : HAL_LTDC_PIXEL_CLOCK_POLARITY_HIGH;
}

/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group3
  * @{
This subsection provides the function allowing to set the LTDC layers configuration:
- HAL_LTDC_SetConfigLayer()                : Configure the given LTDC layer according to the user parameters.
  */
/**
  * @brief  Configure the LTDC layer according to the user parameters.
  * @param  hltdc             Pointer to a hal_ltdc_handle_t structure.
  * @param  layer             Layer index. This parameter can be one of the following values:
  *                           HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2.
  * @param  p_layer_config    Pointer to a hal_ltdc_layer_config_t structure that contains the LTDC layer configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_layer_config pointer is NULL
  * @retval HAL_OK            LTDC layer has been correctly configured.
  */
hal_status_t HAL_LTDC_SetConfigLayer(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                     const hal_ltdc_layer_config_t *p_layer_config)
{
  uint32_t tmp;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_layer_config != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));
  ASSERT_DBG_PARAM(IS_LTDC_WHSTPOS(p_layer_config->window_x0));
  ASSERT_DBG_PARAM(IS_LTDC_WHSPPOS(p_layer_config->window_x1));
  ASSERT_DBG_PARAM(IS_LTDC_WVSTPOS(p_layer_config->window_y0));
  ASSERT_DBG_PARAM(IS_LTDC_WVSPPOS(p_layer_config->window_y1));
  ASSERT_DBG_PARAM(IS_LTDC_PIXEL_FORMAT(p_layer_config->frame_buffer.pixel_format));
  ASSERT_DBG_PARAM(IS_LTDC_BLENDING_FACTOR1(p_layer_config->blending_factor1));
  ASSERT_DBG_PARAM(IS_LTDC_BLENDING_FACTOR2(p_layer_config->blending_factor2));
  ASSERT_DBG_PARAM(IS_LTDC_BUFFER_WIDTH(p_layer_config->frame_buffer.width));
  ASSERT_DBG_PARAM(IS_LTDC_BUFFER_HEIGHT(p_layer_config->frame_buffer.height));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED \
                   | (uint32_t) HAL_LTDC_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_layer_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  const LTDC_TypeDef *p_ltdc;
  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  tmp = READ_REG(p_ltdc->BPCR);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->WHPCR, (((uint32_t)p_layer_config->window_x1 << LTDC_LxWHPCR_WHSPPOS_Pos) \
                                              + (tmp & LTDC_BPCR_AHBP)) \
            | ((uint32_t)p_layer_config->window_x0 + 1U \
               + ((tmp & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos)));

  WRITE_REG(LTDC_LAYER(hltdc, layer)->WVPCR, (((uint32_t)p_layer_config->window_y1 \
                                               + (tmp & LTDC_BPCR_AVBP)) << LTDC_BPCR_AHBP_Pos) \
            | ((uint32_t)p_layer_config->window_y0 + 1U + (tmp & LTDC_BPCR_AVBP)));

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CACR, p_layer_config->alpha);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->BFCR, ((uint32_t)p_layer_config->blending_factor1 \
                                             | (uint32_t)p_layer_config->blending_factor2));

  WRITE_REG(LTDC_LAYER(hltdc, layer)->DCCR, p_layer_config->background_color_argb88888);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBAR, p_layer_config->frame_buffer.address);

  tmp = LTDC_BytePerPixelMap[p_layer_config->frame_buffer.pixel_format];

  WRITE_REG(LTDC_LAYER(hltdc, layer)->PFCR, (uint32_t)p_layer_config->frame_buffer.pixel_format);


  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBLR, \
            ((((uint32_t)p_layer_config->frame_buffer.width * tmp) << LTDC_LxCFBLR_CFBP_Pos) \
             | ((((uint32_t)p_layer_config->window_x1 - (uint32_t)p_layer_config->window_x0) * tmp) \
                + LTDC_CFBLR_CFBLL_VAL_OFFSET)));

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBLNR, p_layer_config->frame_buffer.height);

  SET_BIT(LTDC_LAYER(hltdc, layer)->CR, LTDC_LxCR_LEN);

  hltdc->layer_state[layer] = HAL_LTDC_LAYER_STATE_CONFIGURED;

  return HAL_OK;
}


/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group4
  * @{
This subsection provides a set of function allowing to start and stop the LTDC peripheral:
- HAL_LTDC_Start() : Start the LTDC display.
- HAL_LTDC_Stop()  : Stop the LTDC display.
  */

/**
  * @brief  Start the LTDC.
  * @param  hltdc      LTDC handle
  * @param  interrupts Specify the LTDC interrupt sources to be enabled while starting.
  *         This parameter can be
  *            @arg HAL_LTDC_IT_NONE : Neither FIFO Underrun Interrupt nor Transfer Error interrupt to be enabled
  *            Or any combination of the following values:
  *            @arg HAL_LTDC_IT_FIFO_UNDERRUN : FIFO Underrun Interrupt
  *            @arg HAL_LTDC_IT_TRANSFER_ERROR: Transfer Error interrupt
  * @retval HAL_OK     LTDC started.
  */
hal_status_t HAL_LTDC_Start(hal_ltdc_handle_t *hltdc, uint32_t interrupts)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_ERROR_INTERRUPT(interrupts));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED);
  HAL_CHECK_UPDATE_STATE(hltdc, global_state, HAL_LTDC_STATE_CONFIGURED, HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  HAL_LTDC_EnableIT(hltdc, interrupts | HAL_LTDC_IT_RELOAD);
  HAL_LTDC_Enable(hltdc);

  WRITE_REG(p_ltdc->SRCR, (uint32_t)HAL_LTDC_RELOAD_IMMEDIATE);

  return HAL_OK;
}

/**
  * @brief  Stop the LTDC.
  * @param  hltdc      LTDC handle
  * @retval HAL_OK     LTDC stopped.
  */
hal_status_t HAL_LTDC_Stop(hal_ltdc_handle_t *hltdc)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  CLEAR_REG(p_ltdc->IER);

  HAL_LTDC_Disable(hltdc);

  hltdc->global_state = HAL_LTDC_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group5
  * @{
 This subsection provides the IRQ handler APIs allowing to handle LTDC interruptions, and Register user Callbacks APIs.
 - HAL_LTDC_IRQHandler() handle all LTDC interrupts.
 - HAL_LTDC_ERR_IRQHandler() handle only LTDC transfer error and FIFO underrun interrupts.
 - HAL_LTDC_LineDetectionIRQHandler() handle only LTDC line detection interrupt.
 - HAL_LTDC_ReloadEventIRQHandler() handle only LTDC register reload interrupt.
 - HAL_LTDC_RegisterErrorCallback() Register the LTDC user Error callback.
 - HAL_LTDC_RegisterLineDetectionCallback() Register the LTDC user Line Detection callback.
 - HAL_LTDC_RegisterReloadEventCallback() Register the LTDC user Reload Event callback.
  */
/**
  * @brief  Handle the LTDC interrupt request.
  * @param  hltdc  Pointer to LTDC handle.
  */
void HAL_LTDC_IRQHandler(hal_ltdc_handle_t *hltdc)
{
  const LTDC_TypeDef *p_ltdc;

  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hltdc != NULL);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  flag_status = READ_REG(p_ltdc->ISR);
  it_sources  = READ_REG(p_ltdc->IER);

  /* Error management *********************/
  LTDC_HandleErrorIT(hltdc, flag_status, it_sources);

  /* Line Interrupt management *********************/
  if ((flag_status & it_sources & HAL_LTDC_FLAG_LINE_INTERRUPT) != 0U)
  {
    HAL_LTDC_DisableIT(hltdc, HAL_LTDC_IT_LINE_INTERRUPT);
    HAL_LTDC_ClearFlag(hltdc, HAL_LTDC_FLAG_LINE_INTERRUPT);
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    hltdc->p_line_detection_cb(hltdc);
#else
    HAL_LTDC_LineDetectionCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }

  /* Register reload Interrupt management *********************/
  if ((flag_status & it_sources & HAL_LTDC_FLAG_RELOAD) != 0U)
  {
    HAL_LTDC_DisableIT(hltdc, HAL_LTDC_IT_RELOAD);
    HAL_LTDC_ClearFlag(hltdc, HAL_LTDC_FLAG_RELOAD);
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    hltdc->p_reload_event_cb(hltdc);
#else
    HAL_LTDC_ReloadEventCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }

}

/**
  * @brief  handle LTDC transfer error and FIFO underrun interrupts.
  * @param  hltdc  Pointer to LTDC handle.
  */
void HAL_LTDC_ERR_IRQHandler(hal_ltdc_handle_t *hltdc)
{
  const LTDC_TypeDef *p_ltdc;

  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hltdc != NULL);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  flag_status = READ_REG(p_ltdc->ISR);
  it_sources  = READ_REG(p_ltdc->IER);

  LTDC_HandleErrorIT(hltdc, flag_status, it_sources);
}

/**
  * @brief  handle LTDC line detection interrupt.
  * @param  hltdc  Pointer to LTDC handle.
  */
void HAL_LTDC_LineDetectionIRQHandler(hal_ltdc_handle_t *hltdc)
{
  const LTDC_TypeDef *p_ltdc;

  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hltdc != NULL);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  flag_status = READ_REG(p_ltdc->ISR);
  it_sources  = READ_REG(p_ltdc->IER);

  if ((flag_status & it_sources & HAL_LTDC_FLAG_LINE_INTERRUPT) != 0U)
  {
    HAL_LTDC_DisableIT(hltdc, HAL_LTDC_IT_LINE_INTERRUPT);
    HAL_LTDC_ClearFlag(hltdc, HAL_LTDC_FLAG_LINE_INTERRUPT);
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    hltdc->p_line_detection_cb(hltdc);
#else
    HAL_LTDC_LineDetectionCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  handle LTDC register reload interrupt.
  * @param  hltdc  Pointer to LTDC handle.
  */
void HAL_LTDC_ReloadEventIRQHandler(hal_ltdc_handle_t *hltdc)
{
  const LTDC_TypeDef *p_ltdc;

  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hltdc != NULL);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  flag_status = READ_REG(p_ltdc->ISR);
  it_sources  = READ_REG(p_ltdc->IER);

  if ((flag_status & it_sources & HAL_LTDC_FLAG_RELOAD) != 0U)
  {
    HAL_LTDC_DisableIT(hltdc, HAL_LTDC_IT_RELOAD);
    HAL_LTDC_ClearFlag(hltdc, HAL_LTDC_FLAG_RELOAD);
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    hltdc->p_reload_event_cb(hltdc);
#else
    HAL_LTDC_ReloadEventCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Error callback.
  * @param  hltdc Pointer to LTDC handle.
  */
__WEAK void HAL_LTDC_ErrorCallback(hal_ltdc_handle_t *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hltdc);
  /*! <b>NOTE:</b> This function must not be modified; when the callback is needed,
                    the HAL_LTDC_ErrorCallback() can be implemented in the user file */
}
/**
  * @brief  Line detection callback.
  * @param  hltdc Pointer to LTDC handle.
  */
__WEAK void HAL_LTDC_LineDetectionCallback(hal_ltdc_handle_t *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hltdc);
  /*! <b>NOTE:</b> This function must not be modified; when the callback is needed,
                    the HAL_LTDC_LineDetectionCallback() can be implemented in the user file */
}
/**
  * @brief  Reload event callback.
  * @param  hltdc Pointer to LTDC handle.
  */
__WEAK void HAL_LTDC_ReloadEventCallback(hal_ltdc_handle_t *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hltdc);
  /*! <b>NOTE:</b> This function must not be modified; when the callback is needed,
                    the HAL_LTDC_ReloadEventCallback() can be implemented in the user file */
}
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the LTDC Error callback
  * @param  hltdc             Pointer to LTDC handle
  * @param  p_callback        Specifies the error callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            LTDC error callback is successfully registered
  */
hal_status_t HAL_LTDC_RegisterErrorCallback(hal_ltdc_handle_t *hltdc, hal_ltdc_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hltdc->p_error_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the LTDC Line Detection callback
  * @param  hltdc             Pointer to LTDC handle
  * @param  p_callback        Specifies the Line Detection callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            LTDC Line Detection callback is successfully registered
  */
hal_status_t HAL_LTDC_RegisterLineDetectionCallback(hal_ltdc_handle_t *hltdc, hal_ltdc_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hltdc->p_line_detection_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the LTDC Reload Event callback
  * @param  hltdc             Pointer to LTDC handle
  * @param  p_callback        Specifies the reload event callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_callback pointer is NULL
  * @retval HAL_OK            LTDC reload event callback is successfully registered
  */
hal_status_t HAL_LTDC_RegisterReloadEventCallback(hal_ltdc_handle_t *hltdc, hal_ltdc_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hltdc->p_reload_event_cb = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group6
  * @{
This subsection provides a set of functions allowing to retrieve peripheral state and last process errors.
- HAL_LTDC_GetState() Returns the LTDC handle state
- HAL_LTDC_GetLayerState() Returns LTDC layer state
- HAL_LTDC_GetLastErrorCodes() Returns last occurred error code
  */

/**
  * @brief  Get the LTDC current state
  * @param hltdc             Pointer to LTDC handle
  * @retval hal_ltdc_state_t LTDC state, can be one of @ref hal_ltdc_state_t enumeration values
  */
hal_ltdc_state_t HAL_LTDC_GetState(const hal_ltdc_handle_t *hltdc)
{
  ASSERT_DBG_PARAM(hltdc != NULL);

  return hltdc->global_state;
}

/**
  * @brief  Get the LTDC layer state
  * @param hltdc                   Pointer to LTDC handle
  * @param layer                   LTDC layer index, can be one of hal_ltdc_layer_t enumeration values
  * @retval hal_ltdc_layer_state_t LTDC layer_i state, can be one of @ref hal_ltdc_layer_state_t enumeration values
  */
hal_ltdc_layer_state_t HAL_LTDC_GetLayerState(const hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  return hltdc->layer_state[layer];
}

#if defined(USE_HAL_LTDC_GET_LAST_ERRORS) && (USE_HAL_LTDC_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last error codes
  * @param  hltdc  Pointer to LTDC handle
  * @retval Last error codes
  */
uint32_t HAL_LTDC_GetLastErrorCodes(const hal_ltdc_handle_t *hltdc)
{
  ASSERT_DBG_PARAM(hltdc != NULL);

  return hltdc->last_error_codes;
}
#endif /* USE_HAL_LTDC_GET_LAST_ERRORS */
/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group7
  * @{
This subsection provides a set of optional feature management APIs.
 - HAL_LTDC_SetBackgroundColor() Set the background color.
 - HAL_LTDC_EnableLineDetection() Set and enable the line detection.
 - HAL_LTDC_DisableLineDetection() Disable the line detection.
 - HAL_LTDC_EnableDither() Enable the dither.
 - HAL_LTDC_DisableDither() Disable the dither.
 - HAL_LTDC_IsEnabledDither() Check if the dither is enabled or disabled.
  */

/**
  * @brief  Set the background color
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  rgb888_color  RGB888 color, This parameter must be a value between
  *                       Min_Data = 0x00000000 and Max_Data = 0x00FFFFFF.
  * @retval HAL_OK        Background color configured.
  */
hal_status_t HAL_LTDC_SetBackgroundColor(const hal_ltdc_handle_t *hltdc, uint32_t rgb888_color)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(rgb888_color <= LTDC_MAX_RGB888);

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_INIT \
                   | (uint32_t)HAL_LTDC_STATE_CONFIGURED \
                   | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  WRITE_REG(p_ltdc->BCCR, rgb888_color);

  return HAL_OK;
}

/**
  * @brief  Set and enable the line detection
  * @param  hltdc  Pointer to a hal_ltdc_handle_t structure
  * @param  line   Line number, This parameter must be a value between
  *                Min_Data = 0x000 and Max_Data = 0x7FF.
  * @retval HAL_OK Line detection enabled.
  */
hal_status_t HAL_LTDC_EnableLineDetection(const hal_ltdc_handle_t *hltdc, uint32_t line)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LIPOS(line));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED \
                   | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  CLEAR_BIT(p_ltdc->IER, HAL_LTDC_IT_LINE_INTERRUPT);

  WRITE_REG(p_ltdc->LIPCR, line);

  SET_BIT(p_ltdc->IER, HAL_LTDC_IT_LINE_INTERRUPT);

  return HAL_OK;
}
/**
  * @brief  Disable the line detection
  * @param  hltdc  Pointer to a hal_ltdc_handle_t structure
  * @retval HAL_OK Line detection disabled.
  */
hal_status_t HAL_LTDC_DisableLineDetection(const hal_ltdc_handle_t *hltdc)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED \
                   | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  CLEAR_BIT(p_ltdc->IER, HAL_LTDC_IT_LINE_INTERRUPT);

  return HAL_OK;
}

/**
  * @brief  Enable the dither
  * @param  hltdc  Pointer to a hal_ltdc_handle_t structure
  * @retval HAL_OK Dither enabled.
  */
hal_status_t HAL_LTDC_EnableDither(const hal_ltdc_handle_t *hltdc)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED \
                   | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  SET_BIT(p_ltdc->GCR, LTDC_GCR_DEN);

  return HAL_OK;
}

/**
  * @brief  Disable the dither
  * @param  hltdc  Pointer to a hal_ltdc_handle_t structure
  * @retval HAL_OK Dither disabled.
  */
hal_status_t HAL_LTDC_DisableDither(const hal_ltdc_handle_t *hltdc)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_CONFIGURED \
                   | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  CLEAR_BIT(p_ltdc->GCR, LTDC_GCR_DEN);

  return HAL_OK;
}

/**
  * @brief  Check if the dither is enabled or disabled
  * @param  hltdc                          Pointer to a hal_ltdc_handle_t structure
  * @retval HAL_LTDC_COLOR_DITHER_DISABLED  Dither disabled
  * @retval HAL_LTDC_COLOR_DITHER_ENABLED   Dither enabled
  */
hal_ltdc_color_dither_status_t HAL_LTDC_IsEnabledDither(const hal_ltdc_handle_t *hltdc)
{
  const LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t)HAL_LTDC_STATE_INIT | (uint32_t) HAL_LTDC_STATE_CONFIGURED\
                   | (uint32_t)HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  return (READ_BIT(p_ltdc->GCR, LTDC_GCR_DEN) == 0U) ? HAL_LTDC_COLOR_DITHER_DISABLED : HAL_LTDC_COLOR_DITHER_ENABLED;
}


/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group8
  * @{
This subsection provides a set of optional LTDC layer feature management APIs.
 - HAL_LTDC_SetLayerWindowSize() Set the layer window size.(*)
 - HAL_LTDC_SetLayerWindowPosition() Set the layer window position.(*)
 - HAL_LTDC_SetLayerAddress() Set the layer address.
 - HAL_LTDC_SetLayerFrameBuffer() Set a new layer frame buffer including its address, pixel format, width and height.(*)
 - HAL_LTDC_SetLayerPitch() Set the layer pitch value for specific cases where the width is larger than expected to be
   displayed on screen.
 - HAL_LTDC_SetLayerAlpha() Set the layer alpha.
 - HAL_LTDC_SetLayerBackgroundColor() Set the layer background color.
 - HAL_LTDC_SetConfigLayerColorKeying() Set the layer color keying.
 - HAL_LTDC_EnableLayerColorKeying() Enable the layer color keying.
 - HAL_LTDC_DisableLayerColorKeying() Disable the layer color keying.
 - HAL_LTDC_IsEnabledLayerColorKeying() Check if the layer color keying is enabled or disabled.
 - HAL_LTDC_SetConfigLayerCLUT() Configure the LTDC layer CLUT according to the user parameters.
 - HAL_LTDC_EnableLayerCLUT() Enable the LTDC layer CLUT.
 - HAL_LTDC_DisableLayerCLUT() Disable the LTDC layer CLUT.
 - HAL_LTDC_ForceReload() Reload LTDC Layers configuration.
 (*) **WARNING** : Those APIs are meant to be used individually, in case you want to configure more then one feature,
 you must use the HAL_LTDC_SetConfigLayer()
  */

/**
  * @brief  Set the layer window size.
  * @param  hltdc        Pointer to a hal_ltdc_handle_t structure
  * @param  layer        Layer index, This parameter can be one of the following values:
  *                      HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  x_size       Window horizontal size, This parameter must be a value between
  *                      Min_Data = 0x000 and Max_Data = 0xFFF.
  * @param  y_size       Window vertical size, This parameter must be a value between
  *                      Min_Data = 0x000 and Max_Data = 0x7FF.
  * @warning             This API is meant to be used individually, in case you want to configure more then one feature,
  *                      you must use the HAL_LTDC_SetConfigLayer().
  * @retval HAL_OK       Layer window size configured.
  */
hal_status_t HAL_LTDC_SetLayerWindowSize(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                         uint32_t x_size, uint32_t y_size)
{
  uint32_t byte_per_pixel;
  uint32_t start_position;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));
  ASSERT_DBG_PARAM(IS_LTDC_WHSPPOS(x_size));
  ASSERT_DBG_PARAM(IS_LTDC_WVSPPOS(y_size));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

  /* Update the horizontal start and stop position */
  start_position = READ_REG(LTDC_LAYER(hltdc, layer)->WHPCR) & LTDC_LxWHPCR_WHSTPOS;
  WRITE_REG(LTDC_LAYER(hltdc, layer)->WHPCR, ((((start_position + x_size) - 1U) << LTDC_LxWHPCR_WHSPPOS_Pos) \
                                              | start_position));

  /* Update the vertical start and stop position */
  start_position = READ_REG(LTDC_LAYER(hltdc, layer)->WVPCR) & LTDC_LxWVPCR_WVSTPOS;
  WRITE_REG(LTDC_LAYER(hltdc, layer)->WVPCR, ((((start_position + y_size) - 1U) << LTDC_LxWVPCR_WVSPPOS_Pos) \
                                              | start_position));

  /* Update the frame buffer line length */
  byte_per_pixel = LTDC_BytePerPixelMap[READ_REG(LTDC_LAYER(hltdc, layer)->PFCR)];

  MODIFY_REG(LTDC_LAYER(hltdc, layer)->CFBLR, LTDC_LxCFBLR_CFBLL, (x_size * byte_per_pixel)
             + LTDC_CFBLR_CFBLL_VAL_OFFSET);

  return HAL_OK;
}

/**
  * @brief  Set the layer window position.
  * @param  hltdc        Pointer to a hal_ltdc_handle_t structure
  * @param  layer        Layer index, This parameter can be one of the following values:
  *                      HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  x0           Window horizontal start position, This parameter must be a value between
  *                      Min_Data = 0x000 and Max_Data = 0xFFF.
  * @param  y0           Window vertical start position, This parameter must be a value between
  *                      Min_Data = 0x000 and Max_Data = 0x7FF.
  * @warning             This API is meant to be used individually, in case you want to configure more then one feature,
  *                      you must use the HAL_LTDC_SetConfigLayer().
  * @retval HAL_OK       Layer window position configured.
  */
hal_status_t HAL_LTDC_SetLayerWindowPosition(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                             uint32_t x0, uint32_t y0)
{
  const LTDC_TypeDef *p_ltdc;

  uint32_t back_porch;
  uint32_t h_bp;
  uint32_t v_bp;
  uint32_t tmp;
  uint32_t active_width;
  uint32_t height;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));
  ASSERT_DBG_PARAM(IS_LTDC_WHSTPOS(x0));
  ASSERT_DBG_PARAM(IS_LTDC_WVSTPOS(y0));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  back_porch = READ_REG(p_ltdc->BPCR);
  h_bp = ((back_porch & LTDC_BPCR_AHBP) >> LTDC_BPCR_AHBP_Pos);
  v_bp = (back_porch & LTDC_BPCR_AVBP);
  tmp = LTDC_LAYER(hltdc, layer)->WHPCR;
  active_width = ((tmp & LTDC_LxWHPCR_WHSPPOS) >> LTDC_LxWHPCR_WHSPPOS_Pos) - (tmp & LTDC_LxWHPCR_WHSTPOS) + 1U;

  /* Update the horizontal start and stop position */
  WRITE_REG(LTDC_LAYER(hltdc, layer)->WHPCR, (((h_bp + x0 + active_width) << LTDC_LxWHPCR_WHSPPOS_Pos) \
                                              | (h_bp + x0 + 1U)));

  tmp = LTDC_LAYER(hltdc, layer)->WVPCR;

  height = ((tmp & LTDC_LxWVPCR_WVSPPOS) >> LTDC_LxWVPCR_WVSPPOS_Pos) - (tmp & LTDC_LxWVPCR_WVSTPOS) + 1U;

  /* Update the vertical start and stop position */
  WRITE_REG(LTDC_LAYER(hltdc, layer)->WVPCR, (((v_bp + y0 + height) << LTDC_LxWVPCR_WVSPPOS_Pos) \
                                              | (v_bp + y0 + 1U)));

  return HAL_OK;
}

/**
  * @brief  Set the layer address.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  address       Frame buffer address
  * @retval HAL_OK        Layer address configured.
  */
hal_status_t HAL_LTDC_SetLayerAddress(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t address)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBAR, address);

  return HAL_OK;
}


/**
  * @brief  Set a new layer frame buffer.
  * @param  hltdc           Pointer to a hal_ltdc_handle_t structure
  * @param  layer           Layer index, This parameter can be one of the following values:
  *                         HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  p_frame_buffer  Pointer to frame buffer structure definition
  * @warning             This API is meant to be used individually, in case you want to configure more then one feature,
  *                      you must use the HAL_LTDC_SetConfigLayer().
  * @retval HAL_OK       Layer frame buffer configured.
  */
hal_status_t HAL_LTDC_SetLayerFrameBuffer(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                          const hal_ltdc_frame_buffer_t *p_frame_buffer)
{
  uint16_t pitch;
  uint32_t byte_per_pixel;
  uint32_t horizontal_positions;
  uint16_t active_width;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));
  ASSERT_DBG_PARAM(IS_LTDC_BUFFER_WIDTH(p_frame_buffer->width));
  ASSERT_DBG_PARAM(IS_LTDC_BUFFER_HEIGHT(p_frame_buffer->height));
  ASSERT_DBG_PARAM(IS_LTDC_PIXEL_FORMAT(p_frame_buffer->pixel_format));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_frame_buffer == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get the old layer active width */
  horizontal_positions = LTDC_LAYER(hltdc, layer)->WHPCR;
  active_width = (uint16_t)(((horizontal_positions & LTDC_LxWHPCR_WHSPPOS) >> LTDC_LxWHPCR_WHSPPOS_Pos) \
                            - (horizontal_positions & LTDC_LxWHPCR_WHSTPOS) + 1U);
  byte_per_pixel = LTDC_BytePerPixelMap[p_frame_buffer->pixel_format];

  pitch = (uint16_t)(p_frame_buffer->width * byte_per_pixel);
  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBLR, (((uint32_t)pitch << LTDC_LxCFBLR_CFBP_Pos) \
                                              | ((active_width * byte_per_pixel) + LTDC_CFBLR_CFBLL_VAL_OFFSET)));

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBAR, p_frame_buffer->address);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->PFCR, (uint32_t)p_frame_buffer->pixel_format);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CFBLNR, p_frame_buffer->height);

  return HAL_OK;
}


/**
  * @brief  Set the layer pitch value for specific cases where the width us larger than expected to be displayed on
  *         screen.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  pitch         New pitch value.
  * @warning              In case of configuring the layer using HAL_LTDC_SetConfigLayer() or
  *                       HAL_LTDC_SetConfigLayerFlexARGB() or HAL_LTDC_SetConfigLayerFlexYUVCoplanar(), or changing the
  *                       layer's frame buffer using HAL_LTDC_SetLayerFrameBuffer() or
  *                       HAL_LTDC_SetLayerFlexARGBFrameBuffer() or HAL_LTDC_SetLayerFlexYUVCoplanarFrameBuffer() this
  *                       function have to be recalled.
  * @retval HAL_OK        Layer alpha configured.
  */
hal_status_t HAL_LTDC_SetLayerPitch(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t pitch_byte)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));
  ASSERT_DBG_PARAM(IS_LTDC_PITCH_IN_BYTES(pitch_byte));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

  MODIFY_REG(LTDC_LAYER(hltdc, layer)->CFBLR, LTDC_LxCFBLR_CFBP, pitch_byte << LTDC_LxCFBLR_CFBP_Pos);

  return HAL_OK;
}

/**
  * @brief  Set the layer alpha.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  alpha         Alpha value, This parameter must be a value between
  *                       Min_Data = 0x00 and Max_Data = 0xFF.
  * @retval HAL_OK        Layer alpha configured.
  */
hal_status_t HAL_LTDC_SetLayerAlpha(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint8_t alpha)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CACR, alpha);

  return HAL_OK;
}

/**
  * @brief  Set the layer background color.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  color         Background color. This parameter must be a value between
  *                       Min_Data = 0x000000 and Max_Data = 0xFFFFFF.
  * @retval HAL_OK        Layer background color configured.
  */
hal_status_t HAL_LTDC_SetLayerBackgroundColor(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t color)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->layer_state[layer], (uint32_t) HAL_LTDC_LAYER_STATE_CONFIGURED);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->DCCR, color);

  return HAL_OK;
}

/**
  * @brief  Set the layer color keying.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @param  rgb888_color  RGB888 Color, This parameter must be a value between
  *                       Min_Data = 0x00000000 and Max_Data = 0x00FFFFFF.
  * @retval HAL_OK        Layer color keying configured.
  */
hal_status_t HAL_LTDC_SetConfigLayerColorKeying(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t rgb888_color)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  WRITE_REG(LTDC_LAYER(hltdc, layer)->CKCR, rgb888_color);

  return HAL_OK;
}

/**
  * @brief  Enable the layer color keying.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @retval HAL_OK        Layer color keying enabled.
  */
hal_status_t HAL_LTDC_EnableLayerColorKeying(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  SET_BIT(LTDC_LAYER(hltdc, layer)->CR, LTDC_LxCR_COLKEN);

  return HAL_OK;
}

/**
  * @brief  Disable the layer color keying.
  * @param  hltdc         Pointer to a hal_ltdc_handle_t structure
  * @param  layer         Layer index, This parameter can be one of the following values:
  *                       HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @retval HAL_OK        Layer color keying disabled.
  */
hal_status_t HAL_LTDC_DisableLayerColorKeying(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  CLEAR_BIT(LTDC_LAYER(hltdc, layer)->CR, LTDC_LxCR_COLKEN);

  return HAL_OK;
}

/**
  * @brief  Check if the layer color keying is enabled or disabled.
  * @param  hltdc                           Pointer to a hal_ltdc_handle_t structure
  * @param  layer                           Layer index, This parameter can be one of the following values:
  *                                         HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2
  * @retval HAL_LTDC_COLOR_KEYING_DISABLED  Color keying disabled
  * @retval HAL_LTDC_COLOR_KEYING_ENABLED   Color keying enabled
  */
hal_ltdc_color_keying_status_t HAL_LTDC_IsEnabledLayerColorKeying(const hal_ltdc_handle_t *hltdc,
                                                                  hal_ltdc_layer_t layer)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  return (((READ_BIT(LTDC_LAYER(hltdc, layer)->CR, LTDC_LxCR_COLKEN)) >> LTDC_LxCR_COLKEN_Pos) == 0U)\
         ? HAL_LTDC_COLOR_KEYING_DISABLED : HAL_LTDC_COLOR_KEYING_ENABLED;
}

/**
  * @brief  Configure the LTDC layer CLUT according to the user parameters.
  * @param  hltdc             Pointer to a hal_ltdc_handle_t structure.
  * @param  layer             Layer index. This parameter can be one of the following values:
  *                           HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2.
  * @param  p_clut            Pointer to a p_clut source address.
  * @param  clut_size_pixel   CLUT size in pixel.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_clut pointer is NULL
  * @retval HAL_OK            LTDC layer CLUT has been correctly configured.
  */
hal_status_t HAL_LTDC_SetConfigLayerCLUT(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                         const uint32_t *p_clut, uint32_t clut_size_pixel)
{
  uint32_t tmp;
  uint32_t counter;
  const uint32_t *pcolorlut;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(p_clut != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_clut == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  pcolorlut = p_clut;

  if (READ_REG(LTDC_LAYER(hltdc, layer)->PFCR) == (uint32_t)HAL_LTDC_PIXEL_FORMAT_AL44)
  {
    for (counter = 0U; (counter < clut_size_pixel); counter++)
    {
      tmp  = (((counter + (16U * counter)) << LTDC_LxCLUTWR_CLUTADD_Pos) |
              ((uint32_t)(*pcolorlut) & (LTDC_LxCLUTWR_BLUE_Msk | LTDC_LxCLUTWR_GREEN_Msk | LTDC_LxCLUTWR_RED_Msk)));
      pcolorlut++;
      /* Configure the C-LUT address and RGB value */
      WRITE_REG(LTDC_LAYER(hltdc, layer)->CLUTWR, tmp);
    }
  }
  else
  {
    for (counter = 0U; (counter < clut_size_pixel); counter++)
    {
      tmp  = ((counter << LTDC_LxCLUTWR_CLUTADD_Pos) |
              ((uint32_t)(*pcolorlut) & (LTDC_LxCLUTWR_BLUE_Msk | LTDC_LxCLUTWR_GREEN_Msk | LTDC_LxCLUTWR_RED_Msk)));
      pcolorlut++;
      /* Configure the C-LUT address and RGB value */
      WRITE_REG(LTDC_LAYER(hltdc, layer)->CLUTWR, tmp);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Enable the LTDC layer CLUT.
  * @param  hltdc      Pointer to a hal_ltdc_handle_t structure.
  * @param  layer      Layer index. This parameter can be one of the following values:
  *                    HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2.
  * @retval HAL_OK     LTDC layer CLUT enabled.
  */
hal_status_t HAL_LTDC_EnableLayerCLUT(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  SET_BIT(LTDC_LAYER(hltdc, layer)->CR, LTDC_LxCR_CLUTEN);

  return HAL_OK;
}

/**
  * @brief  Disable the LTDC layer CLUT.
  * @param  hltdc      Pointer to a hal_ltdc_handle_t structure.
  * @param  layer      Layer index. This parameter can be one of the following values:
  *                    HAL_LTDC_LAYER_1 or HAL_LTDC_LAYER_2.
  * @retval HAL_OK     LTDC layer CLUT disabled.
  */
hal_status_t HAL_LTDC_DisableLayerCLUT(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_LAYER_INDEX(layer));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  CLEAR_BIT(LTDC_LAYER(hltdc, layer)->CR, LTDC_LxCR_CLUTEN);

  return HAL_OK;
}

/**
  * @brief  Reload LTDC Layers configuration.
  * @param  hltdc       Pointer to a hal_ltdc_handle_t structure.
  * @param  reload_type This parameter can be one of the following values :
  *                     HAL_LTDC_RELOAD_IMMEDIATE : Immediate Reload
  *                     HAL_LTDC_RELOAD_VERTICAL_BLANKING  : Reload in the next Vertical Blanking
  * @retval HAL_OK      Configuration reloaded.
  */
hal_status_t HAL_LTDC_ForceReload(const hal_ltdc_handle_t *hltdc, hal_ltdc_reload_type_t reload_type)
{
  LTDC_TypeDef *p_ltdc;

  ASSERT_DBG_PARAM(hltdc != NULL);
  ASSERT_DBG_PARAM(IS_LTDC_RELOAD(reload_type));

  ASSERT_DBG_STATE(hltdc->global_state, (uint32_t) HAL_LTDC_STATE_CONFIGURED | (uint32_t) HAL_LTDC_STATE_ACTIVE);

  p_ltdc = LTDC_GET_INSTANCE(hltdc);

  SET_BIT(p_ltdc->IER, HAL_LTDC_IT_RELOAD);
  WRITE_REG(p_ltdc->SRCR, (uint32_t)reload_type);

  return HAL_OK;
}


/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group9
  * @{
  This subsection provides functions allowing to:
   - HAL_LTDC_SetUserData() Set a user data pointer (ex: a user context) in a HAL LTDC handle,
   - HAL_LTDC_GetUserData() Get a user data pointer (ex: a user context) from a HAL LTDC handle.
  */
#if defined(USE_HAL_LTDC_USER_DATA) && (USE_HAL_LTDC_USER_DATA == 1)
/**
  * @brief Store the user data into the LTDC handle
  * @param hltdc        Pointer to LTDC handle
  * @param p_user_data  Pointer to the user data
  */
void HAL_LTDC_SetUserData(hal_ltdc_handle_t *hltdc, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hltdc != NULL);

  hltdc->p_user_data = p_user_data;
}
/**
  * @brief  Retrieve the user data from the LTDC handle
  * @param hltdc   Pointer to LTDC handle
  * @retval Pointer to the user data
  */
const void *HAL_LTDC_GetUserData(const hal_ltdc_handle_t *hltdc)
{
  ASSERT_DBG_PARAM(hltdc != NULL);

  return (hltdc->p_user_data);
}
#endif /* USE_HAL_LTDC_USER_DATA */
/**
  * @}
  */
/** @addtogroup LTDC_Exported_Functions_Group10
  * @{
This subsection provides the function allowing to retrieve the LTDC clock frequency:
- HAL_LTDC_GetClockFreq() : Retrieve the LTDC clock frequency.
  */
/** @brief  Return the peripheral clock frequency for LTDC
  * @param  hltdc    Pointer to LTDC handle
  * @retval uint32_t Frequency in Hz
  * @retval 0        Source clock of the LTDC not configured or not ready
  */
uint32_t HAL_LTDC_GetClockFreq(const hal_ltdc_handle_t *hltdc)
{
  ASSERT_DBG_PARAM((hltdc != NULL));

  STM32_UNUSED(hltdc);

  return HAL_RCC_LTDC_GetKernelClkFreq();
}
/**
  * @}
  */
/**
  * @}
  */
/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup LTDC_Private_Functions LTDC Private Functions
  * @{
  */
/** @brief  Handle the errors interrupt
  * @param  hltdc        Pointer to LTDC handle
  * @param  flag_status  Interrupt flag status
  * @param  it_sources   Enabled interrupt source
  */
static void LTDC_HandleErrorIT(hal_ltdc_handle_t *hltdc, uint32_t flag_status, uint32_t it_sources)
{
  if ((flag_status & it_sources & (HAL_LTDC_IT_FIFO_UNDERRUN | HAL_LTDC_IT_TRANSFER_ERROR)) != 0U)
  {
#if defined(USE_HAL_LTDC_GET_LAST_ERRORS) && (USE_HAL_LTDC_GET_LAST_ERRORS == 1)
    if ((flag_status & it_sources & HAL_LTDC_IT_TRANSFER_ERROR) != 0U)
    {
      hltdc->last_error_codes |= HAL_LTDC_ERROR_TRANSFER_ERROR;
    }
    if ((flag_status & it_sources & HAL_LTDC_IT_FIFO_UNDERRUN) != 0U)
    {
      hltdc->last_error_codes |= HAL_LTDC_ERROR_FIFO_UNDERRUN;
    }
#endif /* USE_HAL_LTDC_GET_LAST_ERRORS */
    HAL_LTDC_DisableIT(hltdc, flag_status & it_sources & (HAL_LTDC_IT_FIFO_UNDERRUN | HAL_LTDC_IT_TRANSFER_ERROR));
    HAL_LTDC_ClearFlag(hltdc, flag_status & it_sources & (HAL_LTDC_IT_FIFO_UNDERRUN | HAL_LTDC_IT_TRANSFER_ERROR));
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
    hltdc->p_error_cb(hltdc);
#else
    HAL_LTDC_ErrorCallback(hltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
  }
}


/**
  * @}
  */
#endif /* USE_HAL_LTDC_MODULE */
/**
    * @}
    */
#endif /* defined (LTDC) */
/**
  * @}
  */
