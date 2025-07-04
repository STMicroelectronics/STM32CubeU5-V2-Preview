/**
  **********************************************************************************************************************
  * @file   stm32u5xx_hal_dcmi.h
  * @brief  Header file of DCMI HAL module.
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
#ifndef STM32U5XX_HAL_DCMI_H
#define STM32U5XX_HAL_DCMI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup DCMI DCMI
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DCMI_Exported_Constants DCMI Exported Constants
  * @{
  */

/** @defgroup DCMI_Interrupt_Sources DCMI Interrupt Sources
  * @{
  */
#define HAL_DCMI_IT_PIPE0_FRAME       DCMI_IER_FRAME_IE                 /*!< Capture complete interrupt      */
#define HAL_DCMI_IT_PIPE0_OVR         DCMI_IER_OVR_IE                   /*!< Overrun interrupt               */
#define HAL_DCMI_IT_PARALLEL_SYNC_ERR DCMI_IER_ERR_IE                   /*!< Synchronization error interrupt */
#define HAL_DCMI_IT_PIPE0_VSYNC       DCMI_IER_VSYNC_IE                 /*!< VSYNC interrupt                 */
#define HAL_DCMI_IT_PIPE0_LINE        DCMI_IER_LINE_IE                  /*!< Line interrupt                  */
#define HAL_DCMI_IT_ALL               (HAL_DCMI_IT_PIPE0_FRAME   \
                                       | HAL_DCMI_IT_PIPE0_OVR   \
                                       | HAL_DCMI_IT_PIPE0_VSYNC \
                                       | HAL_DCMI_IT_PIPE0_LINE  \
                                       | HAL_DCMI_IT_PARALLEL_SYNC_ERR) /*!< All interrupt                   */
/**
  * @}
  */

/** @defgroup DCMI_Optional_Interrupts DCMI Optional Interrupts
  * @{
  */
#define HAL_DCMI_OPT_IT_NONE       0U               /*!< DCMI Line interrupt disabled */
#define HAL_DCMI_OPT_IT_PIPE0_LINE DCMI_IER_LINE_IE /*!< DCMI Line interrupt enabled  */
#define HAL_DCMI_OPT_IT_DEFAULT    DCMI_IER_LINE_IE /*!< DCMI Line interrupt enabled  */
/**
  * @}
  */

/** @defgroup DCMI_Flags DCMI flags
  * @{
  */
#define HAL_DCMI_FLAG_PIPE0_HSYNC       (0x2000 | DCMI_SR_HSYNC)            /*!< HSYNC state (sync line active)  */
#define HAL_DCMI_FLAG_PIPE0_VSYNC_PIN   (0x2000 | DCMI_SR_VSYNC)            /*!< VSYNC state (sync frame active) */
#define HAL_DCMI_FLAG_PIPE0_FNE         (0x2000 | DCMI_SR_FNE)              /*!< FIFO not empty flag             */
#define HAL_DCMI_FLAG_PIPE0_FRAME       DCMI_RIS_FRAME_RIS                  /*!< Frame capture complete flag     */
#define HAL_DCMI_FLAG_PIPE0_OVR         DCMI_RIS_OVR_RIS                    /*!< Overrun flag                    */
#define HAL_DCMI_FLAG_PARALLEL_SYNC_ERR DCMI_RIS_ERR_RIS                    /*!< Synchronization error flag      */
#define HAL_DCMI_FLAG_PIPE0_VSYNC       DCMI_RIS_VSYNC_RIS                  /*!< VSYNC flag                      */
#define HAL_DCMI_FLAG_PIPE0_LINE        DCMI_RIS_LINE_RIS                   /*!< Line flag                       */
#define HAL_DCMI_FLAG_ALL               (HAL_DCMI_FLAG_PIPE0_FRAME   \
                                         | HAL_DCMI_FLAG_PIPE0_OVR   \
                                         | HAL_DCMI_FLAG_PIPE0_VSYNC \
                                         | HAL_DCMI_FLAG_PIPE0_LINE  \
                                         | HAL_DCMI_FLAG_PARALLEL_SYNC_ERR) /*!< All flag                        */
/**
  * @}
  */

/** @defgroup DCMI_Error_Codes DCMI Error Codes
  * @{
  */
#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
#define HAL_DCMI_ERROR_NONE          (0U)        /*!< No error              */
#define HAL_DCMI_ERROR_PIPE0_OVR     (1UL << 0U) /*!< Overrun error         */
#define HAL_DCMI_ERROR_PARALLEL_SYNC (1UL << 1U) /*!< Synchronization error */
#define HAL_DCMI_ERROR_PIPE0_DMA     (1UL << 2U) /*!< DMA error             */
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DCMI_Exported_Types DCMI Exported Types
  * @{
  */
/*! DCMI Instance */
typedef enum
{
  HAL_DCMI = (uint32_t)DCMI, /*!< Peripheral instance DCMI */
} hal_dcmi_t;

/*! DCMI Pipe Index */
typedef enum
{
  HAL_DCMI_PIPE_0 = 0U, /*!< DCMI Pipe0 (Dump pipe) */
} hal_dcmi_pipe_t;

/*! DCMI Global State */
typedef enum
{
  HAL_DCMI_STATE_RESET      = 0U,        /*!< DCMI not yet initialized or disabled    */
  HAL_DCMI_STATE_INIT       = 1U << 31U, /*!< DCMI initialized but not yet configured */
  HAL_DCMI_STATE_CONFIGURED = 1U << 30U, /*!< DCMI initialized and configured         */
} hal_dcmi_state_t;

/*! DCMI Pipe State */
typedef enum
{
  HAL_DCMI_PIPE_STATE_RESET   = 1U << 31U, /*!< DCMI pipe not yet initialized or disabled  */
  HAL_DCMI_PIPE_STATE_IDLE    = 1U << 30U, /*!< DCMI pipe is configured                    */
  HAL_DCMI_PIPE_STATE_ACTIVE  = 1U << 29U, /*!< DCMI pipe internal processing is ongoing   */
  HAL_DCMI_PIPE_STATE_SUSPEND = 1U << 28U, /*!< DCMI pipe internal processing is suspended */
  HAL_DCMI_PIPE_STATE_ABORT   = 1U << 27U, /*!< DCMI pipe internal processing is aborted   */
} hal_dcmi_pipe_state_t;

/*! DCMI Capture Mode */
typedef enum
{
  HAL_DCMI_CAPTURE_CONTINUOUS = 0U,         /*!< The capture process depends on each start frame */
  HAL_DCMI_CAPTURE_SNAPSHOT   = DCMI_CR_CM, /*!< Single frame is captured                        */
} hal_dcmi_capture_t;

/*! DCMI Crop Feature */
typedef enum
{
  HAL_DCMI_CROP_DISABLED = 0U,           /*!< The full image is captured                        */
  HAL_DCMI_CROP_ENABLED  = DCMI_CR_CROP, /*!< Only data within the window specified is captured */
} hal_dcmi_crop_status_t;

/*! DCMI Format */
typedef enum
{
  HAL_DCMI_FORMAT_UNCOMPRESSED = 0U,           /*!< Mode JPEG Disabled */
  HAL_DCMI_FORMAT_JPEG         = DCMI_CR_JPEG, /*!< Mode JPEG Enabled  */
} hal_dcmi_format_t;

/*! DCMI Synchronization Mode */
typedef enum
{
  HAL_DCMI_SYNC_HARDWARE = 0U,          /*!< Hardware synchronization by the HSYNC/VSYNC signals */
  HAL_DCMI_SYNC_EMBEDDED = DCMI_CR_ESS, /*!< Embedded synchronization by coding ESCR registre    */
} hal_dcmi_sync_mode_t;

/*! DCMI PIXCK Polarity */
typedef enum
{
  HAL_DCMI_PIXEL_CLOCK_FALLING = 0U,             /*!< Pixel clock active on Falling edge */
  HAL_DCMI_PIXEL_CLOCK_RISING  = DCMI_CR_PCKPOL, /*!< Pixel clock active on Rising edge  */
} hal_dcmi_pixel_clock_polarity_t;

/*! DCMI HSYNC Polarity */
typedef enum
{
  HAL_DCMI_HSYNC_LOW  = 0U,            /*!< Horizontal synchronization active Low  */
  HAL_DCMI_HSYNC_HIGH = DCMI_CR_HSPOL, /*!< Horizontal synchronization active High */
} hal_dcmi_hsync_polarity_t;

/*! DCMI VSYNC Polarity */
typedef enum
{
  HAL_DCMI_VSYNC_LOW  = 0U,            /*!< Vertical synchronization active Low  */
  HAL_DCMI_VSYNC_HIGH = DCMI_CR_VSPOL, /*!< Vertical synchronization active High */
} hal_dcmi_vsync_polarity_t;

/*! DCMI Capture Rate */
typedef enum
{
  HAL_DCMI_FRAME_CAPTURE_ALL          = 0U,             /*!< All frames are captured        */
  HAL_DCMI_FRAME_CAPTURE_1FRAME_OUT_2 = DCMI_CR_FCRC_0, /*!< Every alternate frame captured */
  HAL_DCMI_FRAME_CAPTURE_1FRAME_OUT_4 = DCMI_CR_FCRC_1, /*!< One frame in 4 frames captured */
} hal_dcmi_frame_capture_rate_t;

/*! DCMI Extended Data Mode */
typedef enum
{
  HAL_DCMI_EXTENDED_DATA_8_BITS  = 0U,                              /*!< 8-bit  data on every pixel clock */
  HAL_DCMI_EXTENDED_DATA_10_BITS = DCMI_CR_EDM_0,                   /*!< 10-bit data on every pixel clock */
  HAL_DCMI_EXTENDED_DATA_14_BITS = DCMI_CR_EDM_1,                   /*!< 12-bit data on every pixel clock */
  HAL_DCMI_EXTENDED_DATA_12_BITS = (DCMI_CR_EDM_0 | DCMI_CR_EDM_1), /*!< 14-bit data on every pixel clock */
} hal_dcmi_extended_data_mode_t;

/*! DCMI Byte Select Mode */
typedef enum
{
  HAL_DCMI_BYTE_CAPTURE_ALL              = 0U,                              /*!< All received data            */
  HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_2_ODD  = DCMI_CR_BSM_0,                   /*!< One byte out of 2 odd parts  */
  HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_2_EVEN = (DCMI_CR_BSM_0 | DCMI_CR_OEBS),  /*!< One byte out of 2 even parts */
  HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_4_ODD  = DCMI_CR_BSM_1,                   /*!< One byte out of 4 odd parts  */
  HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_4_EVEN = (DCMI_CR_BSM_1 | DCMI_CR_OEBS),  /*!< One byte out of 4 even parts */
  HAL_DCMI_BYTE_CAPTURE_2BYTE_OUT_4_ODD  = (DCMI_CR_BSM_1 | DCMI_CR_BSM_0), /*!< Two byte out of 4 odd parts  */
  HAL_DCMI_BYTE_CAPTURE_2BYTE_OUT_4_EVEN = (DCMI_CR_BSM_1 | DCMI_CR_BSM_0
                                            | DCMI_CR_OEBS),                /*!< Two byte out of 4 even parts */
} hal_dcmi_byte_decimation_mode_t;

/*! DCMI Line Select Mode */
typedef enum
{
  HAL_DCMI_LINE_CAPTURE_ALL              = 0U,                           /*!< All received data            */
  HAL_DCMI_LINE_CAPTURE_1LINE_OUT_2_ODD  = DCMI_CR_LSM,                  /*!< One line out of 2 odd parts  */
  HAL_DCMI_LINE_CAPTURE_1LINE_OUT_2_EVEN = (DCMI_CR_LSM | DCMI_CR_OELS), /*!< One line out of 2 even parts */
} hal_dcmi_line_decimation_mode_t;

/**
  * @brief DCMI embedded synchronization configuration structure definition
  */
typedef struct
{
  uint8_t frame_start; /*!< Specify the frame start code or line delimiter unmask */
  uint8_t line_start;  /*!< Specify the line start code or line delimiter unmask  */
  uint8_t line_end;    /*!< Specify the line end code or line delimiter unmask    */
  uint8_t frame_end;   /*!< Specify the frame end code or line delimiter unmask   */
} hal_dcmi_parallel_emb_sync_config_t;

/**
  * @brief DCMI Crop Coordinate structure definition
  */
typedef struct
{
  uint32_t x0_pixel;    /*!< DCMI pixel X0 coordinate for cropping */
  uint32_t y0_line;     /*!< DCMI pixel Y0 coordinate for cropping */
  uint32_t xsize_pixel; /*!< DCMI Pixel per line                   */
  uint32_t ysize_line;  /*!< DCMI Line number                      */
} hal_dcmi_crop_config_t;

/**
  * @brief DCMI Pipe configuration structure definition
  */
typedef struct
{
  hal_dcmi_frame_capture_rate_t frame_rate; /*!< DCMI Pipe Frame Rate configuration */
} hal_dcmi_pipe_config_t;

/**
  * @brief DCMI Parallel configuration structure definition
  */
typedef struct
{
  hal_dcmi_format_t               format;         /*!< DCMI Format JPEG: Compressed/UnCompressed   */
  hal_dcmi_pixel_clock_polarity_t pixel_polarity; /*!< DCMI Pixel clock polarity: Falling/Rising   */
  hal_dcmi_hsync_polarity_t       hsync_polarity; /*!< DCMI Horizontal synchro polarity: High/Low  */
  hal_dcmi_vsync_polarity_t       vsync_polarity; /*!< DCMI Vertical synchro polarity: High/Low    */
  hal_dcmi_extended_data_mode_t   data_width;     /*!< DCMI Data width: 8-bit/10-bit/12-bit/14-bit */
} hal_dcmi_parallel_config_t;

/**
  * @brief DCMI handle structure definition
  */
typedef struct hal_dcmi_handle_s hal_dcmi_handle_t; /*!< DCMI handle structure type */

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
/*! DCMI callback pointer definition */
typedef void (*hal_dcmi_cb_t)(hal_dcmi_handle_t *hdcmi);

/*! DCMI Pipe callback pointer definition */
typedef void (*hal_dcmi_pipe_cb_t)(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */

/*! HAL DCMI handle structure definition */
struct hal_dcmi_handle_s
{
  hal_dcmi_t                     instance;                     /*!< Peripheral instance              */

  volatile hal_dcmi_state_t      global_state;                 /*!< DCMI state                       */

  volatile hal_dcmi_pipe_state_t pipe_states[DCMI_NB_OF_PIPE]; /*!< DCMI Pipe state                  */

  volatile uint32_t              xfer_count;                   /*!< DMA transfer counter             */

  uint32_t                       xfer_size;                    /*!< DMA transfer size                */

  uint32_t                       xfer_number;                  /*!< DMA transfer number              */

  uint32_t                       buff_addr;                    /*!< Address of the DMA output buffer */

  hal_dma_handle_t               *hdma;                        /*!< Pointer to the DMA handler       */

#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
  volatile uint32_t              last_error_codes;             /*!< DCMI Error code                  */
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

#if defined (USE_HAL_DCMI_USER_DATA) && (USE_HAL_DCMI_USER_DATA == 1)
  const void                     *p_user_data;                 /*!< User Data Pointer                */
#endif /* USE_HAL_DCMI_USER_DATA */

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
  hal_dcmi_pipe_cb_t              pipe_stop_cb;                /*!< DCMI Pipe Stop callback          */
  hal_dcmi_pipe_cb_t              pipe_frame_event_cb;         /*!< DCMI Pipe Frame Event callback   */
  hal_dcmi_pipe_cb_t              pipe_vsync_event_cb;         /*!< DCMI Pipe Vsync Event callback   */
  hal_dcmi_pipe_cb_t              pipe_line_event_cb;          /*!< DCMI Pipe Line Event callback    */
  hal_dcmi_pipe_cb_t              pipe_error_cb;               /*!< DCMI Pipe Error callback         */
  hal_dcmi_cb_t                   error_cb;                    /*!< DCMI Error callback              */
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DCMI_Exported_Functions DCMI exported functions
  * @{
  */

/** @defgroup DCMI_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_DCMI_Init(hal_dcmi_handle_t *hdcmi, hal_dcmi_t instance);
void         HAL_DCMI_DeInit(hal_dcmi_handle_t *hdcmi);
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group2 PARALLEL Configuration functions
  * @{
  */
/* Global configuration */
hal_status_t HAL_DCMI_PARALLEL_SetConfig(hal_dcmi_handle_t *hdcmi, const hal_dcmi_parallel_config_t *p_config);
void         HAL_DCMI_PARALLEL_GetConfig(const hal_dcmi_handle_t *hdcmi, hal_dcmi_parallel_config_t *p_config);

/* Synchronization mode */
hal_status_t         HAL_DCMI_PARALLEL_SetSyncMode(hal_dcmi_handle_t *hdcmi, hal_dcmi_sync_mode_t mode);
hal_dcmi_sync_mode_t HAL_DCMI_PARALLEL_GetSyncMode(const hal_dcmi_handle_t *hdcmi);

hal_status_t HAL_DCMI_PARALLEL_SetEmbSyncCode(hal_dcmi_handle_t *hdcmi,
                                              const hal_dcmi_parallel_emb_sync_config_t *p_config);
void         HAL_DCMI_PARALLEL_GetEmbSyncCode(const hal_dcmi_handle_t *hdcmi,
                                              hal_dcmi_parallel_emb_sync_config_t *p_config);

hal_status_t HAL_DCMI_PARALLEL_SetEmbSyncMask(hal_dcmi_handle_t *hdcmi,
                                              const hal_dcmi_parallel_emb_sync_config_t *p_config);
void         HAL_DCMI_PARALLEL_GetEmbSyncMask(const hal_dcmi_handle_t *hdcmi,
                                              hal_dcmi_parallel_emb_sync_config_t *p_config);
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group3 PIPE configuration functions
  * @{
  */
/* Capture Rate */
hal_status_t HAL_DCMI_SetConfigPipe(hal_dcmi_handle_t *hdcmi,
                                    hal_dcmi_pipe_t pipe,
                                    const hal_dcmi_pipe_config_t *p_config);
void         HAL_DCMI_GetConfigPipe(const hal_dcmi_handle_t *hdcmi,
                                    hal_dcmi_pipe_t pipe,
                                    hal_dcmi_pipe_config_t *p_config);

/* Horizontal Resolution */
hal_status_t                    HAL_DCMI_SetPipeBytesDecimation(hal_dcmi_handle_t *hdcmi,
                                                                hal_dcmi_pipe_t pipe,
                                                                hal_dcmi_byte_decimation_mode_t byte_decimation_mode);
hal_dcmi_byte_decimation_mode_t HAL_DCMI_GetPipeBytesDecimation(const hal_dcmi_handle_t *hdcmi,
                                                                hal_dcmi_pipe_t pipe);

/* Vertical Resolution */
hal_status_t                    HAL_DCMI_SetPipeLinesDecimation(hal_dcmi_handle_t *hdcmi,
                                                                hal_dcmi_pipe_t pipe,
                                                                hal_dcmi_line_decimation_mode_t line_decimation_mode);
hal_dcmi_line_decimation_mode_t HAL_DCMI_GetPipeLinesDecimation(const hal_dcmi_handle_t *hdcmi,
                                                                hal_dcmi_pipe_t pipe);

/* Crop Feature */
hal_status_t           HAL_DCMI_SetConfigPipeCrop(hal_dcmi_handle_t *hdcmi,
                                                  hal_dcmi_pipe_t pipe,
                                                  const hal_dcmi_crop_config_t *p_config);
void                   HAL_DCMI_GetConfigPipeCrop(const hal_dcmi_handle_t *hdcmi,
                                                  hal_dcmi_pipe_t pipe,
                                                  hal_dcmi_crop_config_t *p_config);
hal_status_t           HAL_DCMI_EnablePipeCrop(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
hal_status_t           HAL_DCMI_DisablePipeCrop(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
hal_dcmi_crop_status_t HAL_DCMI_IsEnabledPipeCrop(const hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group4 Input and Output operation functions
  * @{
  */
hal_status_t HAL_DCMI_StartPipe_DMA(hal_dcmi_handle_t *hdcmi,
                                    hal_dcmi_pipe_t pipe,
                                    hal_dcmi_capture_t capture,
                                    uint32_t dest_addr,
                                    uint32_t size_byte);
hal_status_t HAL_DCMI_StartPipe_DMA_Opt(hal_dcmi_handle_t *hdcmi,
                                        hal_dcmi_pipe_t pipe,
                                        hal_dcmi_capture_t capture,
                                        uint32_t dest_addr,
                                        uint32_t size_byte,
                                        uint32_t interrupts);

hal_status_t HAL_DCMI_StopPipe_DMA(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);

hal_status_t HAL_DCMI_SuspendPipe(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
hal_status_t HAL_DCMI_ResumePipe(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group5 IRQHandler and Register callbacks functions
  * @{
  */
void HAL_DCMI_IRQHandler(hal_dcmi_handle_t *hdcmi);

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_DCMI_RegisterPipeStopCallback(hal_dcmi_handle_t *hdcmi,
                                               hal_dcmi_pipe_t pipe,
                                               hal_dcmi_pipe_cb_t p_callback);
hal_status_t HAL_DCMI_RegisterPipeFrameEventCallback(hal_dcmi_handle_t *hdcmi,
                                                     hal_dcmi_pipe_t pipe,
                                                     hal_dcmi_pipe_cb_t p_callback);
hal_status_t HAL_DCMI_RegisterPipeVsyncEventCallback(hal_dcmi_handle_t *hdcmi,
                                                     hal_dcmi_pipe_t pipe,
                                                     hal_dcmi_pipe_cb_t p_callback);
hal_status_t HAL_DCMI_RegisterPipeLineEventCallback(hal_dcmi_handle_t *hdcmi,
                                                    hal_dcmi_pipe_t pipe,
                                                    hal_dcmi_pipe_cb_t p_callback);
hal_status_t HAL_DCMI_RegisterPipeErrorCallback(hal_dcmi_handle_t *hdcmi,
                                                hal_dcmi_pipe_t pipe,
                                                hal_dcmi_pipe_cb_t p_callback);
hal_status_t HAL_DCMI_RegisterErrorCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_cb_t p_callback);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group6 callbacks functions
  * @{
  */
void HAL_DCMI_PipeStopCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
void HAL_DCMI_PipeFrameEventCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
void HAL_DCMI_PipeVsyncEventCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
void HAL_DCMI_PipeLineEventCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
void HAL_DCMI_PipeErrorCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
void HAL_DCMI_ErrorCallback(hal_dcmi_handle_t *hdcmi);
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group7 link DMA function
  * @{
  */
hal_status_t HAL_DCMI_SetDMA(hal_dcmi_handle_t *hdcmi, hal_dma_handle_t *hdma);
/**
  * @}
  */

/** @defgroup DCMI_Exported_Functions_Group8 Peripheral State and Error functions
  * @{
  */
hal_dcmi_state_t      HAL_DCMI_GetState(const hal_dcmi_handle_t *hdcmi);
hal_dcmi_pipe_state_t HAL_DCMI_GetPipeState(const hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe);
#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
uint32_t              HAL_DCMI_GetLastErrorCodes(const hal_dcmi_handle_t *hdcmi);
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined (USE_HAL_DCMI_USER_DATA) && (USE_HAL_DCMI_USER_DATA == 1)
/** @defgroup DCMI_Exported_Functions_Group9 Set/Get user data
  * @{
  */
void        HAL_DCMI_SetUserData(hal_dcmi_handle_t *hdcmi, const void *p_user_data);
const void *HAL_DCMI_GetUserData(const hal_dcmi_handle_t *hdcmi);
/**
  * @}
  */
#endif /* USE_HAL_DCMI_USER_DATA */

/** @defgroup DCMI_Exported_Functions_Group10 Interrupt and Flag management
  * @{
 - HAL_DCMI_IsActiveFlag()           : Check whether or not the specified DCMI flag is set.
 - HAL_DCMI_ClearFlag()              : Clear the specified DCMI flags.
 - HAL_DCMI_EnableIT()               : Enable the specified DCMI interrupts.
 - HAL_DCMI_DisableIT()              : Disable the specified DCMI interrupts.
 - HAL_DCMI_IsEnabledIT()            : Check whether or not the specified DCMI interrupt is set.
 - HAL_HAL_DCMI_IsActiveMaskedFlag() : Check whether or not the specified DCMI flag masked with interrupt is set.
 - HAL_HAL_DCMI_ReadMaskedFlag()     : Read which DCMI flags masked with interrupt are active.
  */

/**
  * @brief  Check whether or not the specified DCMI flag is set.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  flag   Specify the DCMI flag to check
  *                This parameter can be only one of the following values:
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_HSYNC       : HSYNC pin state (synchronization between lines)
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_VSYNC_PIN   : VSYNC pin state (synchronization between frames)
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_FNE         : FIFO empty flag
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_FRAME       : Frame capture complete flag
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_OVR         : Overrun flag
  *                @arg @ref HAL_DCMI_FLAG_PARALLEL_SYNC_ERR : Synchronization error flag
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_VSYNC       : VSYNC flag
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_LINE        : Line flag
  * @retval The state of DCMI flag (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_DCMI_IsActiveFlag(const hal_dcmi_handle_t *hdcmi, uint32_t flag)
{
  return ((uint32_t)(((flag & 0x2000U) == 0U) ?                                                        \
                     ((READ_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->RISR, flag) == flag)) : \
                     ((READ_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->SR, flag) == (flag & 0x1FU)))));
}

/**
  * @brief Clear the specified DCMI flags.
  * @param hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param flag   Specify the DCMI flag to clear
  *               This parameter can be any combination of the following values:
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_FRAME       : Frame capture complete flag
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_OVR         : Overrun flag
  *               @arg @ref HAL_DCMI_FLAG_PARALLEL_SYNC_ERR : Synchronization error flag
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_VSYNC       : VSYNC flag
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_LINE        : Line flag
  *               @arg @ref HAL_DCMI_FLAG_ALL               : All flags within raw interrupt status register (DCMI_RIS)
  */
__STATIC_INLINE void HAL_DCMI_ClearFlag(hal_dcmi_handle_t *hdcmi, uint32_t flag)
{
  SET_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->ICR, flag);
}

/**
  * @brief Enable the specified DCMI interrupts.
  * @param hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param interrupt Specify the DCMI interrupt to enable
  *                  This parameter can be any combination of the following values:
  *                  @arg @ref HAL_DCMI_IT_PIPE0_FRAME       : Frame capture complete interrupt
  *                  @arg @ref HAL_DCMI_IT_PIPE0_OVR         : Overrun interrupt
  *                  @arg @ref HAL_DCMI_IT_PARALLEL_SYNC_ERR : Synchronization error interrupt
  *                  @arg @ref HAL_DCMI_IT_PIPE0_VSYNC       : VSYNC interrupt
  *                  @arg @ref HAL_DCMI_IT_PIPE0_LINE        : Line interrupt
  *                  @arg @ref HAL_DCMI_IT_ALL               : All interrupt within interrupt enable register (DCMI_IER)
  */
__STATIC_INLINE void HAL_DCMI_EnableIT(hal_dcmi_handle_t *hdcmi, uint32_t interrupt)
{
  SET_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->IER, interrupt);
}

/**
  * @brief Disable the specified DCMI interrupts.
  * @param hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param interrupt Specify the DCMI interrupt to disable
  *                  This parameter can be any combination of the following values:
  *                  @arg @ref HAL_DCMI_IT_PIPE0_FRAME       : Frame capture complete interrupt
  *                  @arg @ref HAL_DCMI_IT_PIPE0_OVR         : Overrun interrupt
  *                  @arg @ref HAL_DCMI_IT_PARALLEL_SYNC_ERR : Synchronization error interrupt
  *                  @arg @ref HAL_DCMI_IT_PIPE0_VSYNC       : VSYNC interrupt
  *                  @arg @ref HAL_DCMI_IT_PIPE0_LINE        : Line interrupt
  *                  @arg @ref HAL_DCMI_IT_ALL               : All interrupt within interrupt enable register (DCMI_IER)
  */
__STATIC_INLINE void HAL_DCMI_DisableIT(hal_dcmi_handle_t *hdcmi, uint32_t interrupt)
{
  CLEAR_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->IER, interrupt);
}

/**
  * @brief  Check whether or not the specified DCMI interrupt is set.
  * @param  hdcmi      Pointer to a hal_dcmi_handle_t structure
  * @param  interrupt  Specify the DCMI interrupt to check their status
  *                    This parameter can be only one of the following values:
  *                    @arg @ref HAL_DCMI_IT_PIPE0_FRAME       : Frame capture complete interrupt
  *                    @arg @ref HAL_DCMI_IT_PIPE0_OVR         : Overrun interrupt
  *                    @arg @ref HAL_DCMI_IT_PARALLEL_SYNC_ERR : Synchronization error interrupt
  *                    @arg @ref HAL_DCMI_IT_PIPE0_VSYNC       : VSYNC interrupt
  *                    @arg @ref HAL_DCMI_IT_PIPE0_LINE        : Line interrupt
  * @retval The state of DCMI interrupt (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_DCMI_IsEnabledIT(const hal_dcmi_handle_t *hdcmi, uint32_t interrupt)
{
  return ((uint32_t)((READ_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->IER, interrupt) == interrupt)));
}

/**
  * @brief  Check whether or not the specified DCMI flag masked with interrupt is set.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  flag   Specify the DCMI flag to check their status
  *                This parameter can be only one of the following values:
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_FRAME       : Frame capture complete flag masked interrupt
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_OVR         : Overrun flag masked interrupt
  *                @arg @ref HAL_DCMI_FLAG_PARALLEL_SYNC_ERR : Synchronization error flag masked interrupt
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_VSYNC       : VSYNC flag masked interrupt
  *                @arg @ref HAL_DCMI_FLAG_PIPE0_LINE        : Line flag masked interrupt
  * @retval The state of DCMI flag masked with interrupt (0 or 1)
  */
__STATIC_INLINE uint32_t HAL_HAL_DCMI_IsActiveMaskedFlag(const hal_dcmi_handle_t *hdcmi, uint32_t flag)
{
  return ((uint32_t)((READ_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->MISR, flag) == flag)));
}

/**
  * @brief  Read which DCMI flags masked with interrupt are active.
  * @param  hdcmi Pointer to a hal_dcmi_handle_t structure
  * @param  flag  Specify the DCMI flag to check
  *               This parameter can be any combination of the following values:
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_FRAME       : Frame capture complete flag masked interrupt
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_OVR         : Overrun flag masked interrupt
  *               @arg @ref HAL_DCMI_FLAG_PARALLEL_SYNC_ERR : Synchronization error flag masked interrupt
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_VSYNC       : VSYNC flag masked interrupt
  *               @arg @ref HAL_DCMI_FLAG_PIPE0_LINE        : Line flag masked interrupt
  *               @arg @ref HAL_DCMI_FLAG_ALL              : All flag within masked interrupt status register (DCMI_MIS)
  * @retval Which DCMI flags masked with interrupt are active
  */
__STATIC_INLINE uint32_t HAL_HAL_DCMI_ReadMaskedFlag(const hal_dcmi_handle_t *hdcmi, uint32_t flag)
{
  return ((uint32_t)READ_BIT(((DCMI_TypeDef *)(uint32_t)(hdcmi->instance))->MISR, flag));
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
#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_DCMI_H */
