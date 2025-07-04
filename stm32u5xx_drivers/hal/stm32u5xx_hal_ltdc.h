/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_ltdc.h
  * @brief   Header file of LTDC HAL module.
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
#ifndef STM32U5XX_HAL_LTDC_H
#define STM32U5XX_HAL_LTDC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

#if defined (LTDC)

/** @addtogroup STM32U5XX_HAL_Driver
  * @{
  */
/** @defgroup LTDC LTDC
  * @brief LTDC HAL module driver
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Constants LTDC Exported Constants
  * @{
  */
#define HAL_LTDC_MAX_LAYER  2U    /*!< Number of LTDC layers available */
#if defined (USE_HAL_LTDC_GET_LAST_ERRORS) && (USE_HAL_LTDC_GET_LAST_ERRORS == 1)
/** @defgroup LTDC_Error_Code LTDC Error Code
  * @{
  */
#define HAL_LTDC_ERROR_NONE               0x0U             /*!< LTDC No error             */
#define HAL_LTDC_ERROR_FIFO_UNDERRUN      LTDC_ISR_FUIF    /*!< LTDC FIFO Underrun        */
#define HAL_LTDC_ERROR_TRANSFER_ERROR     LTDC_ISR_TERRIF  /*!< LTDC Transfer error       */
/**
  * @}
  */
#endif /* USE_HAL_LTDC_GET_LAST_ERRORS */
/** @defgroup LTDC_Interrupts LTDC Interrupts
  * @{
  */
#define HAL_LTDC_IT_NONE                 0x0U                /*!< LTDC Interrupt None                  */
#define HAL_LTDC_IT_LINE_INTERRUPT       LTDC_IER_LIE        /*!< LTDC Line Interrupt                  */
#define HAL_LTDC_IT_FIFO_UNDERRUN        LTDC_IER_FUIE       /*!< LTDC FIFO Underrun Interrupt         */
#define HAL_LTDC_IT_TRANSFER_ERROR       LTDC_IER_TERRIE     /*!< LTDC Transfer Error Interrupt        */
#define HAL_LTDC_IT_RELOAD               LTDC_IER_RRIE       /*!< LTDC Register Reload Interrupt       */
/**
  * @}
  */
/** @defgroup LTDC_Flags LTDC Flags
  * @{
  */
#define HAL_LTDC_FLAG_LINE_INTERRUPT      LTDC_ISR_LIF       /*!< LTDC Line Interrupt Flag            */
#define HAL_LTDC_FLAG_FIFO_UNDERRUN       LTDC_ISR_FUIF      /*!< LTDC FIFO Underrun interrupt Flag   */
#define HAL_LTDC_FLAG_TRANSFER_ERROR      LTDC_ISR_TERRIF    /*!< LTDC Transfer Error interrupt Flag  */
#define HAL_LTDC_FLAG_RELOAD              LTDC_ISR_RRIF      /*!< LTDC Register Reload interrupt Flag */
/**
  * @}
  */
/**
  * @}
  */
/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Types LTDC Exported Types
  * @{
  */
/**
  * @brief  HAL LTDC State structures definition
  */
typedef enum
{
  HAL_LTDC_STATE_RESET      = 0x00UL,       /*!< LTDC is not yet initialized                */
  HAL_LTDC_STATE_INIT       = (1UL << 31U), /*!< LTDC is initialized but not yet configured */
  HAL_LTDC_STATE_CONFIGURED = (1UL << 30U), /*!< LTDC configured                            */
  HAL_LTDC_STATE_ACTIVE     = (1UL << 29U)  /*!< LTDC active                                */
} hal_ltdc_state_t;
/**
  * @brief  HAL LTDC State structures definition
  */
typedef enum
{
  HAL_LTDC_LAYER_STATE_RESET      = (1UL << 31U), /*!< LTDC layer is not yet configured */
  HAL_LTDC_LAYER_STATE_CONFIGURED = (1UL << 30U)  /*!< LTDC layer is configured         */
} hal_ltdc_layer_state_t;
/**
  * @brief LTDC Layer Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_LAYER_1 = 0x00U, /*!< Layer 1 */
  HAL_LTDC_LAYER_2 = 0x01U  /*!< Layer 2 */
} hal_ltdc_layer_t;
/**
  * @brief LTDC Layer Pixel Format Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_PIXEL_FORMAT_ARGB8888   = 0X00UL,  /*!< ARGB8888 LTDC pixel format */
  HAL_LTDC_PIXEL_FORMAT_RGB888     = 0X01UL,  /*!< RGB888 LTDC pixel format   */
  HAL_LTDC_PIXEL_FORMAT_RGB565     = 0X02UL,  /*!< RGB565 LTDC pixel format   */
  HAL_LTDC_PIXEL_FORMAT_ARGB1555   = 0X03UL,  /*!< ARGB1555 LTDC pixel format */
  HAL_LTDC_PIXEL_FORMAT_ARGB4444   = 0X04UL,  /*!< ARGB4444 LTDC pixel format */
  HAL_LTDC_PIXEL_FORMAT_L8         = 0X05UL,  /*!< L8 LTDC pixel format       */
  HAL_LTDC_PIXEL_FORMAT_AL44       = 0X06UL,  /*!< AL44 LTDC pixel format     */
  HAL_LTDC_PIXEL_FORMAT_AL88       = 0X07UL,  /*!< AL88 LTDC pixel format     */
} hal_ltdc_pixel_format_t;
/**
  * @brief LTDC Horizontal Synchronization Polarity Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_HSYNC_POLARITY_LOW  = 0x0U,          /*!< Horizontal Synchronization is active low.  */
  HAL_LTDC_HSYNC_POLARITY_HIGH = LTDC_GCR_HSPOL /*!< Horizontal Synchronization is active high. */
} hal_ltdc_hsync_polarity_t;
/**
  * @brief LTDC Vertical Synchronization Polarity Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_VSYNC_POLARITY_LOW  = 0x0U,          /*!< Vertical Synchronization is active low.  */
  HAL_LTDC_VSYNC_POLARITY_HIGH = LTDC_GCR_VSPOL /*!< Vertical Synchronization is active high. */
} hal_ltdc_vsync_polarity_t;
/**
  * @brief LTDC Data Enable Polarity Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_DATA_ENABLE_POLARITY_LOW  = 0x0U,          /*!< Data Enable is active low.  */
  HAL_LTDC_DATA_ENABLE_POLARITY_HIGH = LTDC_GCR_DEPOL /*!< Data Enable is active high. */
} hal_ltdc_data_enable_polarity_t;
/**
  * @brief LTDC Pixel Clock Polarity Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_PIXEL_CLOCK_POLARITY_LOW  =  0x0U,          /*!< Pixel Clock Polarity is active low. */
  HAL_LTDC_PIXEL_CLOCK_POLARITY_HIGH =  LTDC_GCR_PCPOL /*!< Pixel Clock Polarity is active high */
} hal_ltdc_pixel_clock_polarity_t;
/**
  * @brief LTDC Blending Factor 1 Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_BLENDING_FACTOR1_CA      = 0x400U, /*!< Blending factor : Constant Alpha               */
  HAL_LTDC_BLENDING_FACTOR1_PA_X_CA = 0x600U  /*!< Blending factor : Constant Alpha x Pixel Alpha */
} hal_ltdc_blending_factor1_t;
/**
  * @brief LTDC Blending Factor 2 Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_BLENDING_FACTOR2_1_MINUS_CA      = 0x5U, /*!< Blending factor : 1 -  Constant Alpha                */
  HAL_LTDC_BLENDING_FACTOR2_1_MINUS_PA_X_CA = 0x7U  /*!< Blending factor : 1 - (Constant Alpha x Pixel Alpha) */
} hal_ltdc_blending_factor2_t;
/**
  * @brief LTDC Reload Type Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_RELOAD_IMMEDIATE         = LTDC_SRCR_IMR, /*!< Immediate Reload         */
  HAL_LTDC_RELOAD_VERTICAL_BLANKING = LTDC_SRCR_VBR  /*!< Vertical Blanking Reload */
} hal_ltdc_reload_type_t;
/**
  * @brief LTDC Color Keying Enable and Disable Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_COLOR_KEYING_DISABLED = 0x00U, /*!< Color keying disabled */
  HAL_LTDC_COLOR_KEYING_ENABLED  = 0x01U  /*!< Color keying enabled  */
} hal_ltdc_color_keying_status_t;
/**
  * @brief LTDC Color Dither Enable and Disable Enumeration Definition
  */
typedef enum
{
  HAL_LTDC_COLOR_DITHER_DISABLED = 0x00U, /*!< Dither disabled */
  HAL_LTDC_COLOR_DITHER_ENABLED  = 0x01U  /*!< Dither enabled  */
} hal_ltdc_color_dither_status_t;
/**
  * @brief  LTDC Global configuration structure definition
  */
typedef struct
{
  hal_ltdc_hsync_polarity_t       hsync_polarity;       /*!< configures the horizontal synchronization polarity.      */
  hal_ltdc_vsync_polarity_t       vsync_polarity;       /*!< configures the vertical synchronization polarity.        */
  hal_ltdc_data_enable_polarity_t data_enable_polarity; /*!< configures the data enable polarity.                     */
  hal_ltdc_pixel_clock_polarity_t pixel_clock_polarity; /*!< configures the pixel clock polarity.                     */
  uint32_t                        hsync;                /*!< Configures the number of Horizontal synchronization width.
                                                             This parameter must be a number between
                                                             Min_Data = 0x000 and Max_Data = 0xFFF.                   */
  uint32_t                        vsync;                /*!< Configures the number of Vertical synchronization height.
                                                             This parameter must be a number between
                                                             Min_Data = 0x000 and Max_Data = 0x7FF.                   */
  uint32_t                        h_back_porch;         /*!< Configures the accumulated horizontal back porch width.
                                                             This parameter must be a number between
                                                             Min_Data = 0x000 and Max_Data = 0xFFF.
                                                             (hsync + h_back_porch -1) must not exceed 0xFFF.         */
  uint32_t                        v_back_porch;         /*!< Configures the accumulated vertical back porch height.
                                                             This parameter must be a number between
                                                             Min_Data = vsync and Max_Data = 0x7FF.
                                                             (vsync + v_back_porch -1) must not exceed 0x7FF.         */
  uint32_t                        active_width;         /*!< Configures the accumulated active width.
                                                             This parameter must be a number between
                                                             Min_Data = accumulated_hbp and Max_Data = 0xFFF.
                                                             (hsync + h_back_porch + active_width -1) must not
                                                             exceed 0xFFF.                                            */
  uint32_t                        active_height;        /*!< Configures the accumulated active height.
                                                             This parameter must be a number between
                                                             Min_Data = accumulated_vbp and Max_Data = 0x7FF.
                                                             (vsync + v_back_porch + active_height -1) must not
                                                             exceed 0x7FF.                                            */
  uint32_t                        h_front_porch;        /*!< Configures the total width.
                                                             This parameter must be a number between
                                                             Min_Data = accumulated_active_width and Max_Data = 0xFFF.
                                                             (hsync + h_back_porch + active_width + h_front_porch - 1)
                                                             must not exceed 0xFFF.                                   */
  uint32_t                        v_front_porch;        /*!< Configures the total height.
                                                             This parameter must be a number between
                                                             Min_Data = accumulated_active_height and Max_Data = 0x7FF.
                                                             (vsync + v_back_porch + active_height + v_front_porch -1)
                                                             must not exceed 0x7FF.                                   */
} hal_ltdc_config_t;
/**
  * @brief  LTDC Layer frame buffer structure definition
  */
typedef struct
{
  uint32_t                address;      /*!< Configures the color frame buffer address        */
  uint32_t                width;        /*!< Configures the color frame buffer line length
                                             in pixels .This parameter must be a number
                                             between Min_Data = 0x0000 and Max_Data = 0x1FFF. */
  uint32_t                height;       /*!< Specifies the number of line in pixels in
                                             frame buffer. This parameter must be a number
                                             between Min_Data = 0x000 and Max_Data = 0x7FF.   */
  hal_ltdc_pixel_format_t pixel_format; /*!< Specifies the pixel format.                      */
} hal_ltdc_frame_buffer_t;
/**
  * @brief  LTDC Layer structure definition
  */
typedef struct
{
  uint16_t                    window_x0;                  /*!< Configures the Window Horizontal Start Position.
                                                               This parameter must be a number between
                                                               Min_Data = 0x000 and Max_Data = 0xFFF.             */
  uint16_t                    window_x1;                  /*!< Configures the Window Horizontal Stop Position.
                                                               This parameter must be a number between
                                                               Min_Data = 0x000 and Max_Data = 0xFFF.             */
  uint16_t                    window_y0;                  /*!< Configures the Window vertical Start Position.
                                                               This parameter must be a number between
                                                               Min_Data = 0x000 and Max_Data = 0x7FF.             */
  uint16_t                    window_y1;                  /*!< Configures the Window vertical Stop Position.
                                                               This parameter must be a number between
                                                               Min_Data = 0x0000 and Max_Data = 0x7FF.            */
  uint32_t                    background_color_argb88888; /*!< Configures the layer background color.             */
  hal_ltdc_blending_factor1_t blending_factor1;           /*!< Select the blending factor 1.
                                                               Blending factor for the top layer.                 */
  hal_ltdc_blending_factor2_t blending_factor2;           /*!< Select the blending factor 2.
                                                               Blending factor for the bottom layer.              */
  hal_ltdc_frame_buffer_t     frame_buffer;               /*!< Specifies the image frame buffer.                  */
  uint8_t                     alpha;                      /*!< Specifies the constant alpha used for blending.
                                                               This parameter must be a number between
                                                               Min_Data = 0x00 and Max_Data = 0xFF.               */
} hal_ltdc_layer_config_t;
/**
  * @brief HAL LTDC Instance Definition
  */
typedef enum
{
  HAL_LTDC = (uint32_t)LTDC /*!< Instance LTDC  */
} hal_ltdc_t;
typedef struct hal_ltdc_handle_s hal_ltdc_handle_t; /*!< LTDC Handle type Definition */
#if defined (USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
typedef void (*hal_ltdc_cb_t)(hal_ltdc_handle_t *ltdc);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
/**
  * @brief  LTDC Handle Structure definition
  */
struct hal_ltdc_handle_s
{
  hal_ltdc_t                       instance;                         /*!< LTDC Register base address    */
  volatile hal_ltdc_state_t        global_state;                     /*!< LTDC Global state             */
  volatile hal_ltdc_layer_state_t  layer_state[HAL_LTDC_MAX_LAYER]; /*!< LTDC Layers state             */
#if defined(USE_HAL_LTDC_USER_DATA) && (USE_HAL_LTDC_USER_DATA == 1)
  const void                  *p_user_data;                          /*!< User Data Pointer             */
#endif /* USE_HAL_LTDC_USER_DATA */
#if defined(USE_HAL_LTDC_REGISTER_CALLBACKS) && (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
  hal_ltdc_cb_t              p_line_detection_cb;     /*!< LTDC Line Detection Callback        */
  hal_ltdc_cb_t              p_reload_event_cb;       /*!< LTDC Reload Event Callback          */
  hal_ltdc_cb_t              p_error_cb;              /*!< LTDC Error Callback                 */
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
#if defined(USE_HAL_LTDC_GET_LAST_ERRORS) && (USE_HAL_LTDC_GET_LAST_ERRORS == 1)
  volatile uint32_t last_error_codes;                 /*!< LTDC error codes             */
#endif /* USE_HAL_LTDC_GET_LAST_ERRORS */
};
/**
  * @}
  */
/* Exported macro ----------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Functions LTDC Exported Functions
  * @{
  */
/** @defgroup LTDC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_LTDC_Init(hal_ltdc_handle_t *hltdc, hal_ltdc_t instance);
void         HAL_LTDC_DeInit(hal_ltdc_handle_t *hltdc);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group2 Global configuration functions
  * @{
  */
hal_status_t HAL_LTDC_SetConfig(hal_ltdc_handle_t *hltdc, const hal_ltdc_config_t *p_config);
void         HAL_LTDC_GetConfig(const hal_ltdc_handle_t *hltdc, hal_ltdc_config_t *p_config);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group3 LTDC Layer configuration function
  * @{
  */
hal_status_t HAL_LTDC_SetConfigLayer(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                     const hal_ltdc_layer_config_t *p_layer_config);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group4 LTDC Start/Stop functions
  * @{
  */
hal_status_t HAL_LTDC_Start(hal_ltdc_handle_t *hltdc, uint32_t interrupts);
hal_status_t HAL_LTDC_Stop(hal_ltdc_handle_t *hltdc);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group5 IRQHandler and Callbacks functions
  * @{
  */
void HAL_LTDC_IRQHandler(hal_ltdc_handle_t *hltdc);
void HAL_LTDC_ERR_IRQHandler(hal_ltdc_handle_t *hltdc);
void HAL_LTDC_LineDetectionIRQHandler(hal_ltdc_handle_t *hltdc);
void HAL_LTDC_ReloadEventIRQHandler(hal_ltdc_handle_t *hltdc);
void HAL_LTDC_ErrorCallback(hal_ltdc_handle_t *hltdc);
void HAL_LTDC_LineDetectionCallback(hal_ltdc_handle_t *hltdc);
void HAL_LTDC_ReloadEventCallback(hal_ltdc_handle_t *hltdc);
#if (USE_HAL_LTDC_REGISTER_CALLBACKS == 1)
hal_status_t HAL_LTDC_RegisterErrorCallback(hal_ltdc_handle_t *hltdc, hal_ltdc_cb_t p_callback);
hal_status_t HAL_LTDC_RegisterLineDetectionCallback(hal_ltdc_handle_t *hltdc, hal_ltdc_cb_t p_callback);
hal_status_t HAL_LTDC_RegisterReloadEventCallback(hal_ltdc_handle_t *hltdc, hal_ltdc_cb_t p_callback);
#endif /* USE_HAL_LTDC_REGISTER_CALLBACKS */
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group6 Peripheral State, Error functions
  * @{
  */
hal_ltdc_state_t       HAL_LTDC_GetState(const hal_ltdc_handle_t *hltdc);
hal_ltdc_layer_state_t HAL_LTDC_GetLayerState(const hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer);
#if defined(USE_HAL_LTDC_GET_LAST_ERRORS) && (USE_HAL_LTDC_GET_LAST_ERRORS == 1)
uint32_t               HAL_LTDC_GetLastErrorCodes(const hal_ltdc_handle_t *hltdc);
#endif /* USE_HAL_LTDC_GET_LAST_ERRORS */
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group7 Optional LTDC functions
  * @{
  */
hal_status_t HAL_LTDC_SetBackgroundColor(const hal_ltdc_handle_t *hltdc, uint32_t rgb888_color);
hal_status_t HAL_LTDC_EnableLineDetection(const hal_ltdc_handle_t *hltdc, uint32_t line);
hal_status_t HAL_LTDC_DisableLineDetection(const hal_ltdc_handle_t *hltdc);
hal_status_t HAL_LTDC_EnableDither(const hal_ltdc_handle_t *hltdc);
hal_status_t HAL_LTDC_DisableDither(const hal_ltdc_handle_t *hltdc);
hal_ltdc_color_dither_status_t HAL_LTDC_IsEnabledDither(const hal_ltdc_handle_t *hltdc);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group8 Optional LTDC layer functions
  * @{
  */
hal_status_t HAL_LTDC_SetLayerWindowSize(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                         uint32_t x_size, uint32_t y_size);
hal_status_t HAL_LTDC_SetLayerWindowPosition(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                             uint32_t x0, uint32_t y0);
hal_status_t HAL_LTDC_SetLayerAddress(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t address);
hal_status_t HAL_LTDC_SetLayerFrameBuffer(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                          const hal_ltdc_frame_buffer_t *p_frame_buffer);
hal_status_t HAL_LTDC_SetLayerPitch(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t pitch_byte);
hal_status_t HAL_LTDC_SetLayerAlpha(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint8_t alpha);
hal_status_t HAL_LTDC_SetLayerBackgroundColor(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, uint32_t color);
hal_status_t HAL_LTDC_SetConfigLayerColorKeying(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer,
                                                uint32_t rgb888_color);
hal_status_t HAL_LTDC_EnableLayerColorKeying(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer);
hal_status_t HAL_LTDC_DisableLayerColorKeying(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer);
hal_ltdc_color_keying_status_t HAL_LTDC_IsEnabledLayerColorKeying(const hal_ltdc_handle_t *hltdc,
                                                                  hal_ltdc_layer_t layer);
hal_status_t HAL_LTDC_SetConfigLayerCLUT(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer, const uint32_t *p_clut,
                                         uint32_t clut_size_pixel);
hal_status_t HAL_LTDC_EnableLayerCLUT(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer);
hal_status_t HAL_LTDC_DisableLayerCLUT(hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer);
hal_status_t HAL_LTDC_ForceReload(const hal_ltdc_handle_t *hltdc, hal_ltdc_reload_type_t reload_type);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group9 User data functions
  * @{
  */
#if defined(USE_HAL_LTDC_USER_DATA) && (USE_HAL_LTDC_USER_DATA == 1)
void HAL_LTDC_SetUserData(hal_ltdc_handle_t *hltdc, const void *p_user_data);
const void *HAL_LTDC_GetUserData(const hal_ltdc_handle_t *hltdc);
#endif /* USE_HAL_LTDC_USER_DATA */
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group10 LTDC retrieve clock frequency
  * @{
  */
uint32_t HAL_LTDC_GetClockFreq(const hal_ltdc_handle_t *hltdc);
/**
  * @}
  */
/** @defgroup LTDC_Exported_Functions_Group11 Enable/Disable and interrupt functions
  * @{
  This subsection provides unitary functions allowing to:
   - HAL_LTDC_Enable() Enable the LTDC.
   - HAL_LTDC_Disable() Disable the LTDC.
   - HAL_LTDC_EnableLayer() Enable the given LTDC Layer.
   - HAL_LTDC_DisableLayer() Disable the given LTDC Layer.
   - HAL_LTDC_IsActiveFlag() Get the LTDC pending flags.
   - HAL_LTDC_ClearFlag() Clears the LTDC pending flags.
   - HAL_LTDC_EnableIT() Enables the specified LTDC interrupts.
   - HAL_LTDC_DisableIT() Disables the specified LTDC interrupts.
   - HAL_LTDC_IsEnabledIT() Check whether the specified LTDC interrupt is enabled or not.
  */
/**
  * @brief  Enable the LTDC.
  * @param  hltdc  LTDC handle
  */
__STATIC_INLINE void HAL_LTDC_Enable(hal_ltdc_handle_t *hltdc)
{
  SET_BIT(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->GCR, LTDC_GCR_LTDCEN);
}
/**
  * @brief  Disable the LTDC.
  * @param  hltdc  LTDC handle
  */
__STATIC_INLINE void HAL_LTDC_Disable(hal_ltdc_handle_t *hltdc)
{
  CLEAR_BIT(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->GCR, LTDC_GCR_LTDCEN);
}
/**
  * @brief  Enable the LTDC Layer.
  * @param  hltdc LTDC handle
  * @param  layer Specify the layer to be enabled.
  */
__STATIC_INLINE void HAL_LTDC_EnableLayer(const hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  LTDC_Layer_TypeDef *p_reg;
  p_reg = (LTDC_Layer_TypeDef *)(((uint32_t)((hltdc)->instance)) + 0x84U + (0x80U * ((uint32_t)layer)));
  SET_BIT(p_reg->CR, LTDC_LxCR_LEN);
}
/**
  * @brief  Disable the LTDC Layer.
  * @param  hltdc LTDC handle
  * @param  layer Specify the layer to be disabled.
  */
__STATIC_INLINE void HAL_LTDC_DisableLayer(const hal_ltdc_handle_t *hltdc, hal_ltdc_layer_t layer)
{
  LTDC_Layer_TypeDef *p_reg;
  p_reg = (LTDC_Layer_TypeDef *)(((uint32_t)((hltdc)->instance)) + 0x84U + (0x80U * ((uint32_t)layer)));
  CLEAR_BIT(p_reg->CR, LTDC_LxCR_LEN);
}
/* Interrupt & Flag management */
/**
  * @brief  Get the LTDC pending flags.
  * @param  hltdc  LTDC handle
  * @param  flag   Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg HAL_LTDC_FLAG_LINE_INTERRUPT: Line Interrupt Flag
  *            @arg HAL_LTDC_FLAG_FIFO_UNDERRUN : FIFO Underrun Interrupt Flag
  *            @arg HAL_LTDC_FLAG_TRANSFER_ERROR: Transfer Error interrupt Flag
  *            @arg HAL_LTDC_FLAG_RELOAD        : Register Reload Interrupt Flag
  * @retval 1 when the flag is SET, 0 when the flag is RESET.
  */
__STATIC_INLINE uint32_t HAL_LTDC_IsActiveFlag(const hal_ltdc_handle_t *hltdc, uint32_t flag)
{
  return ((READ_BIT(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->ISR,
                    (uint32_t)flag) == (uint32_t)flag) ? 1U : 0U);
}
/**
  * @brief  Clears the LTDC pending flags.
  * @param  hltdc  LTDC handle
  * @param  flag    Specify the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg HAL_LTDC_FLAG_LINE_INTERRUPT: Line Interrupt Flag
  *            @arg HAL_LTDC_FLAG_FIFO_UNDERRUN : FIFO Underrun Interrupt Flag
  *            @arg HAL_LTDC_FLAG_TRANSFER_ERROR: Transfer Error interrupt Flag
  *            @arg HAL_LTDC_FLAG_RELOAD        : Register Reload Interrupt Flag
  */
__STATIC_INLINE void HAL_LTDC_ClearFlag(hal_ltdc_handle_t *hltdc, uint32_t flag)
{
  WRITE_REG(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->ICR, flag);
}
/**
  * @brief  Enables the specified LTDC interrupts.
  * @param  hltdc  LTDC handle
  * @param  interrupt Specify the LTDC interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg HAL_LTDC_IT_LINE_INTERRUPT: Line Interrupt Flag
  *            @arg HAL_LTDC_IT_FIFO_UNDERRUN : FIFO Underrun Interrupt Flag
  *            @arg HAL_LTDC_IT_TRANSFER_ERROR: Transfer Error interrupt Flag
  *            @arg HAL_LTDC_IT_RELOAD        : Register Reload Interrupt Flag
  */
__STATIC_INLINE void HAL_LTDC_EnableIT(hal_ltdc_handle_t *hltdc, uint32_t interrupt)
{
  SET_BIT(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->IER, interrupt);
}
/**
  * @brief  Disables the specified LTDC interrupts.
  * @param  hltdc  LTDC handle
  * @param  interrupt Specify the LTDC interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg HAL_LTDC_IT_LINE_INTERRUPT: Line Interrupt Flag
  *            @arg HAL_LTDC_IT_FIFO_UNDERRUN : FIFO Underrun Interrupt Flag
  *            @arg HAL_LTDC_IT_TRANSFER_ERROR: Transfer Error interrupt Flag
  *            @arg HAL_LTDC_IT_RELOAD        : Register Reload Interrupt Flag
  */
__STATIC_INLINE void HAL_LTDC_DisableIT(hal_ltdc_handle_t *hltdc, uint32_t interrupt)
{
  CLEAR_BIT(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->IER, interrupt);
}
/**
  * @brief  Check whether the specified LTDC interrupt is enabled or not.
  * @param  hltdc  LTDC handle
  * @param  interrupt Specify the LTDC interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg HAL_LTDC_IT_LINE_INTERRUPT: Line Interrupt Flag
  *            @arg HAL_LTDC_IT_FIFO_UNDERRUN : FIFO Underrun Interrupt Flag
  *            @arg HAL_LTDC_IT_TRANSFER_ERROR: Transfer Error interrupt Flag
  *            @arg HAL_LTDC_IT_RELOAD        : Register Reload Interrupt Flag
  * @retval 1 when the interrupt is enabled, 0 when the interrupt is desabled
  */
__STATIC_INLINE uint32_t HAL_LTDC_IsEnabledIT(const hal_ltdc_handle_t *hltdc, uint32_t interrupt)
{
  return ((READ_BIT(((LTDC_TypeDef *)((uint32_t) hltdc->instance))->IER,
                    (uint32_t)interrupt) == (uint32_t)interrupt) ? 1U : 0U);
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
#endif /* LTDC */
#ifdef __cplusplus
}
#endif
#endif /* STM32U5xx_HAL_LTDC_H */
