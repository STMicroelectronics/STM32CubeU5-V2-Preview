/**
  **********************************************************************************************************************
  * @file   stm32u5xx_hal_dcmi.c
  * @brief  DCMI HAL module driver
  *         This file provides firmware functions to manage the Digital Camera Interface (DCMI) peripheral.
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

/** @addtogroup DCMI
  * @{
# How to use the DCMI HAL module driver

The sequence below describes how to use this driver to capture image from a camera module connected to the DCMI
Interface.
This sequence does not take into account the configuration of the camera module, which must be made before configuring
and enabling the DCMI to capture images.

A set of functions allowing to initialize the HAL DCMI driver and link it to a physical DCMI peripheral instance and
to deinitialize the DCMI peripheral by aborting/stopping any ongoing process and resetting the HAL DCMI handle state:
  - HAL_DCMI_Init()
  - HAL_DCMI_DeInit()

# Mandatory Configuration
  - Requirements configuration programmed via the following parameters:
    horizontal/vertical polarity, pixel clock polarity, image format and data width using
    HAL_DCMI_PARALLEL_SetConfig() function and for the Capture Rate is configured by HAL_DCMI_SetConfigPipe()

# Optional Configuration
  - Embedded synchronisation mode can be selected and configured the code attached to the frame through these functions:
    - HAL_DCMI_PARALLEL_SetSyncMode()
    - HAL_DCMI_PARALLEL_SetEmbSyncCode()
    - HAL_DCMI_PARALLEL_SetEmbSyncMask()

  - The Horizontal/Vertical resolution can be adjusted using the following functions:
    - HAL_DCMI_SetPipeBytesDecimation()
    - HAL_DCMI_SetPipeLinesDecimation()

  - The CROP feature is configured and enabled to select a window from the image received using these functions:
    - HAL_DCMI_SetConfigPipeCrop()
    - HAL_DCMI_EnablePipeCrop()
    - HAL_DCMI_DisablePipeCrop()

HAL_DCMI_StartPipe_DMA() : Start a frame capture process according to the given parameters:
                           capture mode (continuous/snapshot), destination memory Buffer address and the data length

HAL_DCMI_StartPipe_DMA_Opt() : Provide one additional parameter allowing to select the optional interrupts that can be
                               enabled during the capture process

Configure the selected DMA channel to transfer Data from DCMI DR register to the destination memory buffer.

The capture can be stopped using HAL_DCMI_StopPipe_DMA() function.

The capture can be suspend using HAL_DCMI_SuspendPipe() function and resume by HAL_DCMI_ResumePipe() function.

# Callback registration
  - When the compilation flag USE_HAL_DCMI_REGISTER_CALLBACKS is set to 1, it allows the user to configure dynamically
    the driver callbacks instead of weak functions:
    - HAL_DCMI_PipeStopCallback()       : DCMI Pipe stop callback.
    - HAL_DCMI_PipeFrameEventCallback() : DCMI Pipe frame event callback.
    - HAL_DCMI_PipeVsyncEventCallback() : DCMI Pipe Vsync event callback.
    - HAL_DCMI_PipeLineEventCallback()  : DCMI Pipe line event callback.
    - HAL_DCMI_PipeErrorCallback()      : DCMI Pipe error callback.
    - HAL_DCMI_ErrorCallback()          : DCMI error callback.

  - When the compilation flag USE_HAL_DCMI_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
    feature is not available and all callbacks are set to the corresponding weak functions or in this case user can
    provide his own implementation of these weak functions at user application side.

## Configuration inside the DCMI driver

Config defines                  | Description           | Default value | Note                                         |
------------------------------- | --------------------- | ------------- | -------------------------------------------- |
PRODUCT                         | from PreProcessor env |       NA      | The selected device (ex STM32XXXXxx)         |
USE_ASSERT_DBG_PARAM            | from PreProcessor env |      None     | Allows to use the assert check parameters.   |
USE_ASSERT_DBG_STATE            | from PreProcessor env |      None     | Allows to use the assert check states.       |
USE_HAL_DCMI_MODULE             | from hal_conf.h       |       1       | Allows to use HAL DCMI module.               |
USE_HAL_CHECK_PARAM             | from hal_conf.h       |       0       | Allows to use the run-time checks parameters.|
USE_HAL_DCMI_REGISTER_CALLBACKS | from hal_conf.h       |       0       | Allows to use the load and store exclusive.  |
USE_HAL_DCMI_GET_LAST_ERRORS    | from hal_conf.h       |       0       | Allows to use error code mechanism.          |
USE_HAL_DCMI_USER_DATA          | from hal_conf.h       |       0       | Allows to use user data inside DCMI.         |
USE_HAL_DCMI_CLK_ENABLE_MODEL|from hal_conf.h|HAL_CLK_ENABLE_NO| Allows to use the clock interface management for DCMI.|
  */

#if defined (USE_HAL_DCMI_MODULE) && (USE_HAL_DCMI_MODULE == 1U)

/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup DCMI_Private_Constants DCMI Private constants
  * @{
  */

#define DCMI_TIMEOUT_STOP        1000U       /*!< Set timeout to 1s                                                */
#define DCMI_NB_OF_CYCLE_DIVIDER 160U        /*!< The number of instruction cycles needed for the loop instruction */
#define DCMI_DMA_MAX_SIZE        0xFFFFU     /*!< DMA Maximum transfer size (64 KB)                                */
#define DCMI_UNMASK_ALL_CODE     0xFFFFFFFFU /*!< All codes are compared                                           */

/**
  * @}
  */
/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup DCMI_Private_Macros DCMI Private Macros
  * @{
  */

/*! Macro to check DCMI PIPE */
#define IS_DCMI_PIPE(pipe) ((pipe) == HAL_DCMI_PIPE_0)

/*! Macro to check Capture mode */
#define IS_DCMI_CAPTURE_MODE(mode) (((mode) == HAL_DCMI_CAPTURE_CONTINUOUS) || ((mode) == HAL_DCMI_CAPTURE_SNAPSHOT))

/*! Macro to check JPEG mode */
#define IS_DCMI_FORMAT(format) (((format) == HAL_DCMI_FORMAT_UNCOMPRESSED) || ((format) == HAL_DCMI_FORMAT_JPEG))

/*! Macro to check Pixel clock polarity */
#define IS_DCMI_PCKPOLARITY(polarity) (((polarity) == HAL_DCMI_PIXEL_CLOCK_FALLING) \
                                       || ((polarity) == HAL_DCMI_PIXEL_CLOCK_RISING))

/*! Macro to check Horizontal synchronization polarity */
#define IS_DCMI_HSPOLARITY(polarity) (((polarity) == HAL_DCMI_HSYNC_LOW) || ((polarity) == HAL_DCMI_HSYNC_HIGH))

/*! Macro to check Vertical synchronization polarity */
#define IS_DCMI_VSPOLARITY(polarity) (((polarity) == HAL_DCMI_VSYNC_LOW) || ((polarity) == HAL_DCMI_VSYNC_HIGH))

/*! Macro to check capture rate control */
#define IS_DCMI_CAPTURE_RATE(rate) (((rate) == HAL_DCMI_FRAME_CAPTURE_ALL)             \
                                    || ((rate) == HAL_DCMI_FRAME_CAPTURE_1FRAME_OUT_2) \
                                    || ((rate) == HAL_DCMI_FRAME_CAPTURE_1FRAME_OUT_4))

/*! Macro to check Extended data mode */
#define IS_DCMI_EXTENDED_DATA(data) (((data) == HAL_DCMI_EXTENDED_DATA_8_BITS)     \
                                     || ((data) == HAL_DCMI_EXTENDED_DATA_10_BITS) \
                                     || ((data) == HAL_DCMI_EXTENDED_DATA_12_BITS) \
                                     || ((data) == HAL_DCMI_EXTENDED_DATA_14_BITS))

/*! Macro to check synchronization mode */
#define IS_DCMI_SYNC_MODE(mode) (((mode) == HAL_DCMI_SYNC_HARDWARE) || ((mode) == HAL_DCMI_SYNC_EMBEDDED))

/*! Macro to check Decimate Byte Select */
#define IS_DCMI_BYTE_SELECT_MODE(byte_mode) (((byte_mode)    == HAL_DCMI_BYTE_CAPTURE_ALL)              \
                                             || ((byte_mode) == HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_2_ODD)  \
                                             || ((byte_mode) == HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_2_EVEN) \
                                             || ((byte_mode) == HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_4_ODD)  \
                                             || ((byte_mode) == HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_4_EVEN) \
                                             || ((byte_mode) == HAL_DCMI_BYTE_CAPTURE_2BYTE_OUT_4_ODD)  \
                                             || ((byte_mode) == HAL_DCMI_BYTE_CAPTURE_2BYTE_OUT_4_EVEN))

/*! Macro to check Decimate Line Select */
#define IS_DCMI_LINE_SELECT_MODE(line_mode) (((line_mode)    == HAL_DCMI_LINE_CAPTURE_ALL)              \
                                             || ((line_mode) == HAL_DCMI_LINE_CAPTURE_1LINE_OUT_2_ODD)  \
                                             || ((line_mode) == HAL_DCMI_LINE_CAPTURE_1LINE_OUT_2_EVEN))

/*! Macro to check Optional Interrupts */
#define IS_DCMI_OPT_IT(interrupt) (((interrupt) == HAL_DCMI_OPT_IT_NONE)          \
                                   || ((interrupt) == HAL_DCMI_OPT_IT_PIPE0_LINE) \
                                   || ((interrupt) == HAL_DCMI_OPT_IT_DEFAULT))

/*! Macro to Window Height */
#define IS_DCMI_WINDOW_VST(coordinate) ((coordinate) <= 0x1FFFU)

/*! Macro to check Window Coordinate */
#define IS_DCMI_WINDOW_COORDINATE(coordinate) ((coordinate) <= 0x3FFFU)

/*! Convert the HAL DCMI instance into CMSIS DCMI instance */
#define DCMI_GET_INSTANCE(handle) ((DCMI_TypeDef *)((uint32_t)(handle)->instance))

/**
  * @}
  */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup DCMI_Private_Functions DCMI Private Functions
  * @{
  */
static void         DCMI_DMAXferCplt(hal_dma_handle_t *hdma);
static void         DCMI_Error(hal_dma_handle_t *hdma);
static void         DCMI_PipeError(hal_dma_handle_t *hdma);
static void         DCMI_Stop(hal_dma_handle_t *hdma);
static hal_status_t DCMI_StartPipe_DMA_Opt(hal_dcmi_handle_t *hdcmi,
                                           uint32_t dest_addr,
                                           uint32_t size_byte,
                                           hal_dcmi_capture_t capture,
                                           uint32_t interrupt);
/**
  * @}
  */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup DCMI_Exported_Functions
  * @{
  */

/** @addtogroup DCMI_Exported_Functions_Group1
  * @{
A set of functions allowing to initialize and deinitialize the DCMI peripheral :
 - HAL_DCMI_Init()   : Initialize the HAL DCMI handle and associate it to a given DCMI peripheral instance.
 - HAL_DCMI_DeInit() : De-initialize the HAL DCMI handle and stop/abort any ongoing capture process.
  */

/**
  * @brief  Initialize the HAL DCMI handle and associate it to a given DCMI peripheral instance.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  instance           Value from @ref hal_dcmi_t enumeration
  * @retval HAL_INVALID_PARAM  Invalid parameter when hdcmi pointer is NULL
  * @retval HAL_OK             DCMI is successfully initialized
  */
hal_status_t HAL_DCMI_Init(hal_dcmi_handle_t *hdcmi, hal_dcmi_t instance)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_ALL_INSTANCE((DCMI_TypeDef *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdcmi == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->instance = instance;

#if defined (USE_HAL_DCMI_CLK_ENABLE_MODEL) && (USE_HAL_DCMI_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_DCMI_PSSI_EnableClock();
#endif /* USE_HAL_DCMI_CLK_ENABLE_MODEL */

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
  hdcmi->pipe_stop_cb        = HAL_DCMI_PipeStopCallback;
  hdcmi->pipe_frame_event_cb = HAL_DCMI_PipeFrameEventCallback;
  hdcmi->pipe_vsync_event_cb = HAL_DCMI_PipeVsyncEventCallback;
  hdcmi->pipe_line_event_cb  = HAL_DCMI_PipeLineEventCallback;
  hdcmi->pipe_error_cb       = HAL_DCMI_PipeErrorCallback;
  hdcmi->error_cb            = HAL_DCMI_ErrorCallback;
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */

#if defined (USE_HAL_DCMI_USER_DATA) && (USE_HAL_DCMI_USER_DATA == 1)
  hdcmi->p_user_data = NULL;
#endif /* USE_HAL_DCMI_USER_DATA */

#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
  hdcmi->last_error_codes = HAL_DCMI_ERROR_NONE;
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

  hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_RESET;
  hdcmi->global_state = HAL_DCMI_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initialize the HAL DCMI handle and stop/abort any ongoing capture process.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  */
void HAL_DCMI_DeInit(hal_dcmi_handle_t *hdcmi)
{
  uint32_t count = DCMI_TIMEOUT_STOP * (SystemCoreClock / DCMI_NB_OF_CYCLE_DIVIDER / 1000U);
  __IO uint32_t *cr_register;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_ALL_INSTANCE(DCMI_GET_INSTANCE(hdcmi)));

  cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

  CLEAR_BIT(*cr_register, DCMI_CR_CAPTURE);
  do
  {
    count--;
    if (count == 0U)
    {
      return;
    }
  } while (READ_BIT(*cr_register, DCMI_CR_CAPTURE) != 0U);

  CLEAR_BIT(*cr_register, DCMI_CR_ENABLE);

  (void)HAL_DMA_Abort(hdcmi->hdma);

  hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_RESET;
  hdcmi->global_state = HAL_DCMI_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group2
  * @{
A set of functions allowing to configure the DCMI peripheral:

- Global configuration :
  - HAL_DCMI_PARALLEL_SetConfig() : Configure the DCMI according to the specified parameters.
  - HAL_DCMI_PARALLEL_GetConfig() : Retrieve the DCMI configuration.

- Embedded Synchronization :
  - HAL_DCMI_PARALLEL_SetSyncMode()    : Set synchronization mode.
  - HAL_DCMI_PARALLEL_GetSyncMode()    : Get synchronization mode.

  - HAL_DCMI_PARALLEL_SetEmbSyncCode() : Set embedded synchronization code.
  - HAL_DCMI_PARALLEL_GetEmbSyncCode() : Get embedded synchronization code.

  - HAL_DCMI_PARALLEL_SetEmbSyncMask() : Set embedded synchronization delimiters masks.
  - HAL_DCMI_PARALLEL_GetEmbSyncMask() : Get embedded synchronization delimiters masks.
  */

/**
  * @brief  Configure the DCMI according to the specified parameters.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  p_config           Pointer to a hal_dcmi_parallel_config_t structure
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK             DCMI is successfully configured
  */
hal_status_t HAL_DCMI_PARALLEL_SetConfig(hal_dcmi_handle_t *hdcmi, const hal_dcmi_parallel_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_FORMAT(p_config->format));
  ASSERT_DBG_PARAM(IS_DCMI_PCKPOLARITY(p_config->pixel_polarity));
  ASSERT_DBG_PARAM(IS_DCMI_HSPOLARITY(p_config->hsync_polarity));
  ASSERT_DBG_PARAM(IS_DCMI_VSPOLARITY(p_config->vsync_polarity));
  ASSERT_DBG_PARAM(IS_DCMI_EXTENDED_DATA(p_config->data_width));

  ASSERT_DBG_STATE(hdcmi->global_state, ((uint32_t)HAL_DCMI_STATE_INIT | (uint32_t)HAL_DCMI_STATE_CONFIGURED));
  ASSERT_DBG_STATE(hdcmi->pipe_states[HAL_DCMI_PIPE_0],
                   ((uint32_t)HAL_DCMI_PIPE_STATE_RESET | (uint32_t)HAL_DCMI_PIPE_STATE_IDLE));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(DCMI_GET_INSTANCE(hdcmi)->CR,
             (DCMI_CR_JPEG | DCMI_CR_PCKPOL | DCMI_CR_HSPOL | DCMI_CR_VSPOL | DCMI_CR_EDM),
             ((uint32_t)p_config->format
              | (uint32_t)p_config->pixel_polarity
              | (uint32_t)p_config->hsync_polarity
              | (uint32_t)p_config->vsync_polarity
              | (uint32_t)p_config->data_width));

  hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_RESET;
  hdcmi->global_state = HAL_DCMI_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Retrieve the DCMI configuration.
  * @param  hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param  p_config  Pointer to a hal_dcmi_parallel_config_t structure
  */
void HAL_DCMI_PARALLEL_GetConfig(const hal_dcmi_handle_t *hdcmi, hal_dcmi_parallel_config_t *p_config)
{
  uint32_t config;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);

  config = READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR,
                    (DCMI_CR_JPEG | DCMI_CR_PCKPOL | DCMI_CR_HSPOL | DCMI_CR_VSPOL | DCMI_CR_EDM));
  p_config->format         = (hal_dcmi_format_t)(uint32_t)(config & DCMI_CR_JPEG);
  p_config->pixel_polarity = (hal_dcmi_pixel_clock_polarity_t)(uint32_t)(config & DCMI_CR_PCKPOL);
  p_config->hsync_polarity = (hal_dcmi_hsync_polarity_t)(uint32_t)(config & DCMI_CR_HSPOL);
  p_config->vsync_polarity = (hal_dcmi_vsync_polarity_t)(uint32_t)(config & DCMI_CR_VSPOL);
  p_config->data_width     = (hal_dcmi_extended_data_mode_t)(uint32_t)(config & DCMI_CR_EDM);
}

/**
  * @brief  Set synchronization mode.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  mode               Value from @ref hal_dcmi_sync_mode_t enumeration
  * @retval HAL_INVALID_PARAM  Invalid parameter when incompatible sync mode with other parameters
  * @retval HAL_OK             DCMI synchro mode is successfully configured
  */
hal_status_t HAL_DCMI_PARALLEL_SetSyncMode(hal_dcmi_handle_t *hdcmi, hal_dcmi_sync_mode_t mode)
{
  __IO uint32_t *cr_register;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_SYNC_MODE(mode));

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hdcmi->pipe_states[HAL_DCMI_PIPE_0], HAL_DCMI_PIPE_STATE_RESET);

  cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  uint32_t tmp_cr_reg = READ_REG(*cr_register);

  /* The Embedded Syncro mode is supported only for 8-bit parallel data width and uncompressed data transfer format */
  if ((mode != HAL_DCMI_SYNC_HARDWARE)
      && (((hal_dcmi_format_t)(uint32_t)(tmp_cr_reg & DCMI_CR_JPEG) != HAL_DCMI_FORMAT_UNCOMPRESSED)
          || ((hal_dcmi_extended_data_mode_t)(uint32_t)(tmp_cr_reg & DCMI_CR_EDM) != HAL_DCMI_EXTENDED_DATA_8_BITS)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(*cr_register, DCMI_CR_ESS, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Get synchronization mode.
  * @param  hdcmi                   Pointer to a hal_dcmi_handle_t structure
  * @retval HAL_DCMI_SYNC_HARDWARE  Hardware synchronization mode
  * @retval HAL_DCMI_SYNC_EMBEDDED  Embedded synchronization mode
  */
hal_dcmi_sync_mode_t HAL_DCMI_PARALLEL_GetSyncMode(const hal_dcmi_handle_t *hdcmi)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);

  return ((hal_dcmi_sync_mode_t)(uint32_t)READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_ESS));
}

/**
  * @brief  Set embedded synchronization code (frame start/end , line start/end).
  * @param  hdcmi              Pointer to hal_dcmi_handle_t structure
  * @param  p_config           Pointer to hal_dcmi_parallel_emb_sync_config_t structure
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK             DCMI delimiter code is successfully configured
  */
hal_status_t HAL_DCMI_PARALLEL_SetEmbSyncCode(hal_dcmi_handle_t *hdcmi,
                                              const hal_dcmi_parallel_emb_sync_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM((p_config->frame_end != p_config->line_end) && (p_config->frame_end != p_config->line_start));

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hdcmi->pipe_states[HAL_DCMI_PIPE_0], HAL_DCMI_PIPE_STATE_RESET);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  WRITE_REG(DCMI_GET_INSTANCE(hdcmi)->ESCR, (((uint32_t)p_config->frame_start  << DCMI_ESCR_FSC_Pos)
                                             | ((uint32_t)p_config->line_start << DCMI_ESCR_LSC_Pos)
                                             | ((uint32_t)p_config->line_end   << DCMI_ESCR_LEC_Pos)
                                             | ((uint32_t)p_config->frame_end  << DCMI_ESCR_FEC_Pos)));

  WRITE_REG(DCMI_GET_INSTANCE(hdcmi)->ESUR, DCMI_UNMASK_ALL_CODE);

  return HAL_OK;
}

/**
  * @brief  Get embedded synchronization code.
  * @param  hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param  p_config  Pointer to a hal_dcmi_parallel_emb_sync_config_t structure
  */
void HAL_DCMI_PARALLEL_GetEmbSyncCode(const hal_dcmi_handle_t *hdcmi,
                                      hal_dcmi_parallel_emb_sync_config_t *p_config)
{
  uint32_t delimiter_code;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);

  delimiter_code = READ_REG(DCMI_GET_INSTANCE(hdcmi)->ESCR);
  p_config->frame_start = (uint8_t)((delimiter_code & DCMI_ESCR_FSC) >> DCMI_ESCR_FSC_Pos);
  p_config->line_start  = (uint8_t)((delimiter_code & DCMI_ESCR_LSC) >> DCMI_ESCR_LSC_Pos);
  p_config->line_end    = (uint8_t)((delimiter_code & DCMI_ESCR_LEC) >> DCMI_ESCR_LEC_Pos);
  p_config->frame_end   = (uint8_t)((delimiter_code & DCMI_ESCR_FEC) >> DCMI_ESCR_FEC_Pos);
}

/**
  * @brief  Set embedded synchronization delimiters masks (Frame start/end masks values, Line start/end masks values).
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  p_config           Pointer to a hal_dcmi_parallel_emb_sync_config_t structure
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK             DCMI delimiter mask is successfully configured
  */
hal_status_t HAL_DCMI_PARALLEL_SetEmbSyncMask(hal_dcmi_handle_t *hdcmi,
                                              const hal_dcmi_parallel_emb_sync_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hdcmi->pipe_states[HAL_DCMI_PIPE_0], HAL_DCMI_PIPE_STATE_RESET);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  WRITE_REG(DCMI_GET_INSTANCE(hdcmi)->ESUR, (((uint32_t)(p_config->frame_start)  << DCMI_ESUR_FSU_Pos)
                                             | ((uint32_t)(p_config->line_start) << DCMI_ESUR_LSU_Pos)
                                             | ((uint32_t)(p_config->line_end)   << DCMI_ESUR_LEU_Pos)
                                             | ((uint32_t)(p_config->frame_end)  << DCMI_ESUR_FEU_Pos)));

  return HAL_OK;
}

/**
  * @brief  Get embedded synchronization delimiters unmasks.
  * @param  hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param  p_config  Pointer to a hal_dcmi_parallel_emb_sync_config_t structure
  */
void HAL_DCMI_PARALLEL_GetEmbSyncMask(const hal_dcmi_handle_t *hdcmi,
                                      hal_dcmi_parallel_emb_sync_config_t *p_config)
{
  uint32_t delimiter_unmask;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);

  delimiter_unmask = READ_REG(DCMI_GET_INSTANCE(hdcmi)->ESUR);
  p_config->frame_start = (uint8_t)((delimiter_unmask & DCMI_ESUR_FSU) >> DCMI_ESUR_FSU_Pos);
  p_config->line_start  = (uint8_t)((delimiter_unmask & DCMI_ESUR_LSU) >> DCMI_ESUR_LSU_Pos);
  p_config->line_end    = (uint8_t)((delimiter_unmask & DCMI_ESUR_LEU) >> DCMI_ESUR_LEU_Pos);
  p_config->frame_end   = (uint8_t)((delimiter_unmask & DCMI_ESUR_FEU) >> DCMI_ESUR_FEU_Pos);
}
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group3
  * @{
A set of functions allowing to configure the DCMI pipe peripheral:

- Capture Rate :
  - HAL_DCMI_SetConfigPipe() : Configure the frames to be captured (all frames, 1 frame out of 2 or 1 frame out of 4).
  - HAL_DCMI_GetConfigPipe() : Get the frame capture config.

- Horizontal resolution :
  - HAL_DCMI_SetPipeBytesDecimation() : Set the bytes decimation.
  - HAL_DCMI_GetPipeBytesDecimation() : Get the bytes decimation.

- Vertical resolution :
  - HAL_DCMI_SetPipeLinesDecimation() : Set the lines decimation.
  - HAL_DCMI_GetPipeLinesDecimation() : Get the lines decimation.

- Crop Feature :
  - HAL_DCMI_SetConfigPipeCrop() : Set the DCMI CROP coordinates configuration.
  - HAL_DCMI_GetConfigPipeCrop() : Get the DCMI CROP coordinates configuration.

  - HAL_DCMI_EnablePipeCrop()    : Enable the Crop feature.
  - HAL_DCMI_DisablePipeCrop()   : Disable the Crop feature.
  - HAL_DCMI_IsEnabledPipeCrop() : Check the status of DCMI Crop feature.
  */

/**
  * @brief  Configure the frames to be captured.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_config           Pointer to a hal_dcmi_pipe_config_t structure
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK             DCMI frame capture rate is successfully configured
  */
hal_status_t HAL_DCMI_SetConfigPipe(hal_dcmi_handle_t *hdcmi,
                                    hal_dcmi_pipe_t pipe,
                                    const hal_dcmi_pipe_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));
  ASSERT_DBG_PARAM(IS_DCMI_CAPTURE_RATE(p_config->frame_rate));

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t)HAL_DCMI_PIPE_STATE_RESET | (uint32_t)HAL_DCMI_PIPE_STATE_IDLE));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_FCRC, (uint32_t)p_config->frame_rate);

  hdcmi->pipe_states[pipe] = HAL_DCMI_PIPE_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the frame capture config.
  * @param  hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param  pipe      Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_config  Pointer to a hal_dcmi_pipe_config_t structure
  */
void HAL_DCMI_GetConfigPipe(const hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe, hal_dcmi_pipe_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->global_state, HAL_DCMI_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  p_config->frame_rate = (hal_dcmi_frame_capture_rate_t)(uint32_t)READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_FCRC);

  STM32_UNUSED(pipe);
}

/**
  * @brief  Set the bytes decimation.
  * @param  hdcmi                 Pointer to a hal_dcmi_handle_t structure
  * @param  pipe                  Value from @ref hal_dcmi_pipe_t enumeration
  * @param  byte_decimation_mode  Value from @ref hal_dcmi_byte_decimation_mode_t enumeration
  * @retval HAL_INVALID_PARAM     Invalid parameter when incompatible bytes decimation mode with data width
  * @retval HAL_OK                DCMI horizontal resolution is successfully configured
  */
hal_status_t HAL_DCMI_SetPipeBytesDecimation(hal_dcmi_handle_t *hdcmi,
                                             hal_dcmi_pipe_t pipe,
                                             hal_dcmi_byte_decimation_mode_t byte_decimation_mode)
{
  __IO uint32_t *cr_register;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));
  ASSERT_DBG_PARAM(IS_DCMI_BYTE_SELECT_MODE(byte_decimation_mode));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_IDLE);

  cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  uint32_t tmp_cr_reg = READ_REG(*cr_register);

  /* The Bytes Decimation mode is supported only for 8-bit parallel data width */
  if ((byte_decimation_mode != HAL_DCMI_BYTE_CAPTURE_ALL)
      && ((hal_dcmi_extended_data_mode_t)(uint32_t)(tmp_cr_reg & DCMI_CR_EDM) != HAL_DCMI_EXTENDED_DATA_8_BITS))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(*cr_register, (DCMI_CR_BSM | DCMI_CR_OEBS), (uint32_t)byte_decimation_mode);

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Get the bytes decimation.
  * @param  hdcmi                                   Pointer to a hal_dcmi_handle_t structure
  * @param  pipe                                    Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_DCMI_BYTE_CAPTURE_ALL               All received data captured
  * @retval HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_2_ODD   One byte out of 2 odd parts captured
  * @retval HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_2_EVEN  One byte out of 2 even parts captured
  * @retval HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_4_ODD   One byte out of 4 odd parts captured
  * @retval HAL_DCMI_BYTE_CAPTURE_1BYTE_OUT_4_EVEN  One byte out of 4 even parts captured
  * @retval HAL_DCMI_BYTE_CAPTURE_2BYTE_OUT_4_ODD   Two byte out of 4 odd parts captured
  * @retval HAL_DCMI_BYTE_CAPTURE_2BYTE_OUT_4_EVEN  Two byte out of 4 even parts captured
  */
hal_dcmi_byte_decimation_mode_t HAL_DCMI_GetPipeBytesDecimation(const hal_dcmi_handle_t *hdcmi,
                                                                hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  STM32_UNUSED(pipe);

  return (hal_dcmi_byte_decimation_mode_t)(uint32_t)READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR,
                                                             (DCMI_CR_BSM | DCMI_CR_OEBS));
}

/**
  * @brief  Set the lines decimation.
  * @param  hdcmi                 Pointer to a hal_dcmi_handle_t structure
  * @param  pipe                  Value from @ref hal_dcmi_pipe_t enumeration
  * @param  line_decimation_mode  Value from @ref hal_dcmi_line_decimation_mode_t enumeration
  * @retval HAL_OK                DCMI vertical resolution is successfully configured
  */
hal_status_t HAL_DCMI_SetPipeLinesDecimation(hal_dcmi_handle_t *hdcmi,
                                             hal_dcmi_pipe_t pipe,
                                             hal_dcmi_line_decimation_mode_t line_decimation_mode)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));
  ASSERT_DBG_PARAM(IS_DCMI_LINE_SELECT_MODE(line_decimation_mode));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_IDLE);

  MODIFY_REG(DCMI_GET_INSTANCE(hdcmi)->CR, (DCMI_CR_LSM | DCMI_CR_OELS), (uint32_t)line_decimation_mode);

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Get the lines decimation.
  * @param  hdcmi                                   Pointer to a hal_dcmi_handle_t structure
  * @param  pipe                                    Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_DCMI_LINE_CAPTURE_ALL               All received data captured
  * @retval HAL_DCMI_LINE_CAPTURE_1LINE_OUT_2_ODD   One line out of 2 odd parts captured
  * @retval HAL_DCMI_LINE_CAPTURE_1LINE_OUT_2_EVEN  One line out of 2 even parts captured
  */
hal_dcmi_line_decimation_mode_t HAL_DCMI_GetPipeLinesDecimation(const hal_dcmi_handle_t *hdcmi,
                                                                hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  STM32_UNUSED(pipe);

  return (hal_dcmi_line_decimation_mode_t)(uint32_t)READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR,
                                                             (DCMI_CR_LSM | DCMI_CR_OELS));
}

/**
  * @brief  Configure the DCMI CROP coordinate.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_config           Pointer to a hal_dcmi_crop_config_t structure
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_config pointer is NULL
  * @retval HAL_OK             DCMI crop coordinate is successfully configured
  */
hal_status_t HAL_DCMI_SetConfigPipeCrop(hal_dcmi_handle_t *hdcmi,
                                        hal_dcmi_pipe_t pipe,
                                        const hal_dcmi_crop_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));
  ASSERT_DBG_PARAM(IS_DCMI_WINDOW_COORDINATE(p_config->x0_pixel));
  ASSERT_DBG_PARAM(IS_DCMI_WINDOW_VST(p_config->y0_line));
  ASSERT_DBG_PARAM(IS_DCMI_WINDOW_COORDINATE(p_config->xsize_pixel));
  ASSERT_DBG_PARAM(IS_DCMI_WINDOW_COORDINATE(p_config->ysize_line));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  WRITE_REG(DCMI_GET_INSTANCE(hdcmi)->CWSTRTR, ((p_config->x0_pixel  << DCMI_CWSTRT_HOFFCNT_Pos)
                                                | (p_config->y0_line << DCMI_CWSTRT_VST_Pos)));
  WRITE_REG(DCMI_GET_INSTANCE(hdcmi)->CWSIZER, ((p_config->xsize_pixel  << DCMI_CWSIZE_CAPCNT_Pos)
                                                | (p_config->ysize_line << DCMI_CWSIZE_VLINE_Pos)));

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Get the DCMI CROP coordinate.
  * @param  hdcmi     Pointer to a hal_dcmi_handle_t structure
  * @param  pipe      Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_config  Pointer to a hal_dcmi_crop_config_t structure
  */
void HAL_DCMI_GetConfigPipeCrop(const hal_dcmi_handle_t *hdcmi,
                                hal_dcmi_pipe_t pipe,
                                hal_dcmi_crop_config_t *p_config)
{
  uint32_t crop_start;
  uint32_t crop_size;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  crop_start = READ_REG(DCMI_GET_INSTANCE(hdcmi)->CWSTRTR);
  p_config->x0_pixel = (crop_start & DCMI_CWSTRT_HOFFCNT) >> DCMI_CWSTRT_HOFFCNT_Pos;
  p_config->y0_line  = (crop_start & DCMI_CWSTRT_VST) >> DCMI_CWSTRT_VST_Pos;

  crop_size  = READ_REG(DCMI_GET_INSTANCE(hdcmi)->CWSIZER);
  p_config->xsize_pixel = (crop_size & DCMI_CWSIZE_CAPCNT) >> DCMI_CWSIZE_CAPCNT_Pos;
  p_config->ysize_line  = (crop_size & DCMI_CWSIZE_VLINE) >> DCMI_CWSIZE_VLINE_Pos;

  STM32_UNUSED(pipe);
}

/**
  * @brief  Enable the Crop feature.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_INVALID_PARAM  Invalid parameter when the API is called while the DCMI is configured in JPEG format
  *                            that does not support crop feature
  * @retval HAL_OK             DCMI crop feature is successfully enabled
  */
hal_status_t HAL_DCMI_EnablePipeCrop(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  __IO uint32_t *cr_register;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* The crop feature is supported only in the uncompressed format */
  if ((hal_dcmi_format_t)(uint32_t)READ_BIT(*cr_register, DCMI_CR_JPEG) != HAL_DCMI_FORMAT_UNCOMPRESSED)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  SET_BIT(*cr_register, DCMI_CR_CROP);

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Disable the Crop feature.
  * @param  hdcmi   Pointer to a hal_dcmi_handle_t structure
  * @param  pipe    Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_OK  DCMI crop feature is successfully disabled
  */
hal_status_t HAL_DCMI_DisablePipeCrop(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  CLEAR_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_CROP);

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Check the status of DCMI Crop feature.
  * @param  hdcmi                   Pointer to a hal_dcmi_handle_t structure
  * @param  pipe                    Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_DCMI_CROP_DISABLED  The full image is captured
  * @retval HAL_DCMI_CROP_ENABLED   Specify window is captured
  */
hal_dcmi_crop_status_t HAL_DCMI_IsEnabledPipeCrop(const hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_IDLE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_ACTIVE
                    | (uint32_t) HAL_DCMI_PIPE_STATE_SUSPEND));

  STM32_UNUSED(pipe);

  return ((hal_dcmi_crop_status_t)(uint32_t)READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_CROP));
}
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group4
  * @{
A set of functions allowing to manage the DCMI data transfers:
 - HAL_DCMI_StartPipe_DMA()     : Start the DCMI capture using the DMA by enabling the required interrupts(Frame, Vsync,
                                  Overrun and Error sync) and the optional interrupt (line) is enabled by default.
 - HAL_DCMI_StartPipe_DMA_Opt() : Start the DCMI capture using the DMA by enabling the required interrupts
                                  (Frame, Vsync, Overrun and Error sync) and by offering the user a parameter to enable
                                  if needed the optional interrupt (line).
 - HAL_DCMI_StopPipe_DMA()      : Stop the DCMI capture.
 - HAL_DCMI_SuspendPipe()       : Suspend DCMI capture.
 - HAL_DCMI_ResumePipe()        : Resume DCMI capture.
  */

/**
  * @brief  Start the DCMI capture using the DMA by enabling the required interrupts.
  * @param  hdcmi      Pointer to a hal_dcmi_handle_t structure
  * @param  pipe       Value from @ref hal_dcmi_pipe_t enumeration
  * @param  capture    DCMI capture mode snapshot or continuous grab
  *                    This parameter can be a value of @ref hal_dcmi_capture_t enumeration
  * @param  dest_addr  The destination memory Buffer address (LCD Frame buffer)
  * @param  size_byte  The length of capture to be transferred
  * @note   The required interrupts are: Frame, Vsync, Overrun and Error sync.
            The optional interrupt (line) is enabled by default.
  * @retval HAL_ERROR  The transfer mode parameter is linked-list linear or the DMA channel state is active
  * @retval HAL_BUSY   If USE_HAL_CHECK_PROCESS_STATE is set to "1" and the current pipe state is not IDLE
  * @retval HAL_OK     The DMA channel peripheral transfer is successfully started
  */
hal_status_t HAL_DCMI_StartPipe_DMA(hal_dcmi_handle_t *hdcmi,
                                    hal_dcmi_pipe_t pipe,
                                    hal_dcmi_capture_t capture,
                                    uint32_t dest_addr,
                                    uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));
  ASSERT_DBG_PARAM(IS_DCMI_CAPTURE_MODE(capture));
  ASSERT_DBG_PARAM(size_byte != 0U);

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdcmi, pipe_states[pipe], HAL_DCMI_PIPE_STATE_IDLE, HAL_DCMI_PIPE_STATE_ACTIVE);

  if (DCMI_StartPipe_DMA_Opt(hdcmi, dest_addr, size_byte, capture, HAL_DCMI_OPT_IT_DEFAULT) != HAL_OK)
  {
#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
    hdcmi->last_error_codes = HAL_DCMI_ERROR_PIPE0_DMA;
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

    hdcmi->pipe_states[pipe] = HAL_DCMI_PIPE_STATE_IDLE;

    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Start the DCMI capture using the DMA by enabling the required interrupts (Frame, Vsync, Overrun and Error)
            and by offering the user a parameter to enable if needed the optional interrupt (line).
  * @param  hdcmi       Pointer to a hal_dcmi_handle_t structure
  * @param  pipe        Value from @ref hal_dcmi_pipe_t enumeration
  * @param  capture     DCMI capture mode snapshot or continuous grab
  *                     This parameter can be a value of @ref hal_dcmi_capture_t enumeration
  * @param  dest_addr   The destination memory Buffer address (LCD Frame buffer)
  * @param  size_byte   The length of capture to be transferred
  * @param  interrupts  DCMI Optional Interrupts
  *                     This parameter can be a value of @ref DCMI_Optional_Interrupts group
  * @retval HAL_ERROR   The transfer mode parameter is linked-list linear or the DMA channel state is active
  * @retval HAL_BUSY    If USE_HAL_CHECK_PROCESS_STATE is set to "1" and the current pipe state is not IDLE
  * @retval HAL_OK      The DMA channel peripheral transfer is successfully started
  */
hal_status_t HAL_DCMI_StartPipe_DMA_Opt(hal_dcmi_handle_t *hdcmi,
                                        hal_dcmi_pipe_t pipe,
                                        hal_dcmi_capture_t capture,
                                        uint32_t dest_addr,
                                        uint32_t size_byte,
                                        uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));
  ASSERT_DBG_PARAM(IS_DCMI_CAPTURE_MODE(capture));
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_DCMI_OPT_IT(interrupts));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdcmi, pipe_states[pipe], HAL_DCMI_PIPE_STATE_IDLE, HAL_DCMI_PIPE_STATE_ACTIVE);

  if (DCMI_StartPipe_DMA_Opt(hdcmi, dest_addr, size_byte, capture, interrupts) != HAL_OK)
  {
#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
    hdcmi->last_error_codes = HAL_DCMI_ERROR_PIPE0_DMA;
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

    hdcmi->pipe_states[pipe] = HAL_DCMI_PIPE_STATE_IDLE;

    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Stop the DCMI capture.
  * @param  hdcmi      Pointer to a hal_dcmi_handle_t structure
  * @param  pipe       Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_OK     The DMA channel peripheral transfer is successfully stopped
  */
hal_status_t HAL_DCMI_StopPipe_DMA(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_ACTIVE);

  hdcmi->pipe_states[pipe] = HAL_DCMI_PIPE_STATE_ABORT;

  CLEAR_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_CAPTURE);

  hdcmi->hdma->p_xfer_abort_cb = DCMI_Stop;
  if (HAL_DMA_Abort_IT(hdcmi->hdma) != HAL_OK)
  {
    DCMI_Stop(hdcmi->hdma);
  }

  return HAL_OK;
}

/**
  * @brief  Suspend DCMI capture.
  * @param  hdcmi      Pointer to a hal_dcmi_handle_t structure
  * @param  pipe       Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_ERROR  The DCMI capture bit not cleared
  * @retval HAL_OK     The DCMI capture is successfully suspended
  */
hal_status_t HAL_DCMI_SuspendPipe(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  uint32_t count = DCMI_TIMEOUT_STOP * (SystemCoreClock / DCMI_NB_OF_CYCLE_DIVIDER / 1000U);
  __IO uint32_t *cr_register;

  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_ACTIVE);

  cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

  CLEAR_BIT(*cr_register, DCMI_CR_CAPTURE);
  do
  {
    count--;
    if (count == 0U)
    {
      return HAL_ERROR;
    }
  } while (READ_BIT(*cr_register, DCMI_CR_CAPTURE) != 0U);

  hdcmi->pipe_states[pipe] = HAL_DCMI_PIPE_STATE_SUSPEND;

  return HAL_OK;
}

/**
  * @brief  Resume DCMI capture.
  * @param  hdcmi      Pointer to a hal_dcmi_handle_t structure
  * @param  pipe       Value from @ref hal_dcmi_pipe_t enumeration
  * @retval HAL_BUSY   If USE_HAL_CHECK_PROCESS_STATE is set to "1" and the current pipe state is not SUSPEND
  * @retval HAL_OK     The DCMI capture is successfully resumed
  */
hal_status_t HAL_DCMI_ResumePipe(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  ASSERT_DBG_STATE(hdcmi->pipe_states[pipe], HAL_DCMI_PIPE_STATE_SUSPEND);

  HAL_CHECK_UPDATE_STATE(hdcmi, pipe_states[pipe], HAL_DCMI_PIPE_STATE_SUSPEND, HAL_DCMI_PIPE_STATE_ACTIVE);

  SET_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_CAPTURE);

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group5
  * @{
A set of function to handle the DCMI interruptions :
  - HAL_DCMI_IRQHandler() : Handles DCMI interrupt request.
  */

/**
  * @brief  Handles DCMI interrupt request.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  */
void HAL_DCMI_IRQHandler(hal_dcmi_handle_t *hdcmi)
{
  uint32_t isr_value;

  ASSERT_DBG_PARAM(hdcmi != NULL);

  isr_value = HAL_HAL_DCMI_ReadMaskedFlag(hdcmi, HAL_DCMI_FLAG_ALL);

  /* Frame interrupt management ***************************************************************************************/
  if ((isr_value & HAL_DCMI_FLAG_PIPE0_FRAME) != 0U)
  {
    if (READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_CM) == (uint32_t)HAL_DCMI_CAPTURE_SNAPSHOT)
    {
      HAL_DCMI_DisableIT(hdcmi, (HAL_DCMI_IT_PIPE0_LINE | HAL_DCMI_IT_PIPE0_VSYNC | HAL_DCMI_IT_PIPE0_OVR
                                 | HAL_DCMI_IT_PARALLEL_SYNC_ERR));
    }

    HAL_DCMI_DisableIT(hdcmi, HAL_DCMI_IT_PIPE0_FRAME);
    HAL_DCMI_ClearFlag(hdcmi, HAL_DCMI_IT_PIPE0_FRAME);

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
    hdcmi->pipe_frame_event_cb(hdcmi, HAL_DCMI_PIPE_0);
#else
    HAL_DCMI_PipeFrameEventCallback(hdcmi, HAL_DCMI_PIPE_0);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */

    return;
  }

  /* VSync interrupt management ***************************************************************************************/
  if ((isr_value & HAL_DCMI_FLAG_PIPE0_VSYNC) != 0U)
  {
    HAL_DCMI_ClearFlag(hdcmi, HAL_DCMI_FLAG_PIPE0_VSYNC);

    hdcmi->xfer_count = hdcmi->xfer_number;

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
    hdcmi->pipe_vsync_event_cb(hdcmi, HAL_DCMI_PIPE_0);
#else
    HAL_DCMI_PipeVsyncEventCallback(hdcmi, HAL_DCMI_PIPE_0);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */

    return;
  }

  /* Line interrupt management ****************************************************************************************/
  if ((isr_value & HAL_DCMI_FLAG_PIPE0_LINE) != 0U)
  {
    HAL_DCMI_ClearFlag(hdcmi, HAL_DCMI_FLAG_PIPE0_LINE);

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
    hdcmi->pipe_line_event_cb(hdcmi, HAL_DCMI_PIPE_0);
#else
    HAL_DCMI_PipeLineEventCallback(hdcmi, HAL_DCMI_PIPE_0);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */

    return;
  }

  /* Error interrupt management ***************************************************************************************/
  if ((isr_value & (HAL_DCMI_FLAG_PARALLEL_SYNC_ERR | HAL_DCMI_FLAG_PIPE0_OVR)) != 0U)
  {
    HAL_DCMI_DisableIT(hdcmi, HAL_DCMI_IT_ALL);
    HAL_DCMI_ClearFlag(hdcmi, HAL_DCMI_FLAG_ALL);

    if ((isr_value & HAL_DCMI_FLAG_PIPE0_OVR) != 0U)
    {
#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
      hdcmi->last_error_codes = HAL_DCMI_ERROR_PIPE0_OVR;
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

      hdcmi->hdma->p_xfer_abort_cb = DCMI_PipeError;
      if (HAL_DMA_Abort_IT(hdcmi->hdma) != HAL_OK)
      {
        DCMI_PipeError(hdcmi->hdma);
      }
    }
    else
    {
#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
      hdcmi->last_error_codes = HAL_DCMI_ERROR_PARALLEL_SYNC;
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */

      hdcmi->hdma->p_xfer_abort_cb = DCMI_Error;
      if (HAL_DMA_Abort_IT(hdcmi->hdma) != HAL_OK)
      {
        DCMI_Error(hdcmi->hdma);
      }
    }
  }
}

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the DCMI Pipe Stop callback to be used instead of
  *         the weak HAL_DCMI_PipeStopCallback() predefined callback.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_callback         Pointer to the hal_dcmi_pipe_cb_t Callback function
  * @retval HAL_INVALID_PARAM  Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK             DCMI pipe stop callback is successfully stored
  */
hal_status_t HAL_DCMI_RegisterPipeStopCallback(hal_dcmi_handle_t *hdcmi,
                                               hal_dcmi_pipe_t pipe,
                                               hal_dcmi_pipe_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->pipe_stop_cb = p_callback;

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Register the DCMI Pipe Frame event callback to be used instead of
  *         the weak HAL_DCMI_PipeFrameEventCallback() predefined callback.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_callback         Pointer to the hal_dcmi_pipe_cb_t Callback function
  * @retval HAL_INVALID_PARAM  Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK             DCMI pipe frame event callback is successfully stored
  */
hal_status_t HAL_DCMI_RegisterPipeFrameEventCallback(hal_dcmi_handle_t *hdcmi,
                                                     hal_dcmi_pipe_t pipe,
                                                     hal_dcmi_pipe_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->pipe_frame_event_cb = p_callback;

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Register the DCMI Pipe Vsync event callback to be used instead of
  *         the weak HAL_DCMI_PipeVsyncEventCallback() predefined callback.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_callback         Pointer to the hal_dcmi_pipe_cb_t Callback function
  * @retval HAL_INVALID_PARAM  Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK             DCMI pipe Vsync event callback is successfully stored
  */
hal_status_t HAL_DCMI_RegisterPipeVsyncEventCallback(hal_dcmi_handle_t *hdcmi,
                                                     hal_dcmi_pipe_t pipe,
                                                     hal_dcmi_pipe_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->pipe_vsync_event_cb = p_callback;

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Register the DCMI Pipe Line event callback to be used instead of
  *         the weak HAL_DCMI_PipeLineEventCallback() predefined callback.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_callback         Pointer to the hal_dcmi_pipe_cb_t Callback function
  * @retval HAL_INVALID_PARAM  Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK             DCMI pipe line event callback is successfully stored
  */
hal_status_t HAL_DCMI_RegisterPipeLineEventCallback(hal_dcmi_handle_t *hdcmi,
                                                    hal_dcmi_pipe_t pipe,
                                                    hal_dcmi_pipe_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->pipe_line_event_cb = p_callback;

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Register the DCMI Pipe error callback to be used instead of
  *         the weak HAL_DCMI_PipeErrorCallback() predefined callback.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  pipe               Value from @ref hal_dcmi_pipe_t enumeration
  * @param  p_callback         Pointer to the hal_dcmi_pipe_cb_t Callback function
  * @retval HAL_INVALID_PARAM  Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK             DCMI pipe error callback is successfully stored
  */
hal_status_t HAL_DCMI_RegisterPipeErrorCallback(hal_dcmi_handle_t *hdcmi,
                                                hal_dcmi_pipe_t pipe,
                                                hal_dcmi_pipe_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->pipe_error_cb = p_callback;

  STM32_UNUSED(pipe);

  return HAL_OK;
}

/**
  * @brief  Register the DCMI Error callback to be used instead of
  *         the weak HAL_DCMI_ErrorCallback() predefined callback.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  p_callback         Pointer to the hal_dcmi_cb_t Callback function
  * @retval HAL_INVALID_PARAM  Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK             DCMI error callback is successfully stored
  */
hal_status_t HAL_DCMI_RegisterErrorCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group6
  * @{
A set of Weak functions (or default Callbacks functions if USE_HAL_DCMI_REGISTER_CALLBACKS is set to 1) which are used
to asynchronously inform the application.
The HAL DCMI driver provides these callbacks as weak empty functions. When needed these functions are to be implemented
in the user file:
  - HAL_DCMI_PipeStopCallback()       : DCMI Pipe stop callback.
  - HAL_DCMI_PipeFrameEventCallback() : DCMI Pipe frame event callback.
  - HAL_DCMI_PipeVsyncEventCallback() : DCMI Pipe Vsync event callback.
  - HAL_DCMI_PipeLineEventCallback()  : DCMI Pipe line event callback.
  - HAL_DCMI_PipeErrorCallback()      : DCMI Pipe error callback.
  - HAL_DCMI_ErrorCallback()          : DCMI error callback.
  */

/**
  * @brief  DCMI Pipe stop callback.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  pipe   Value from @ref hal_dcmi_pipe_t enumeration
  */
__WEAK void HAL_DCMI_PipeStopCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  STM32_UNUSED(hdcmi);
  STM32_UNUSED(pipe);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_DCMI_PipeStopCallback could be implemented in the user file.
   */
}

/**
  * @brief  DCMI Pipe frame event callback.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  pipe   Value from @ref hal_dcmi_pipe_t enumeration
  */
__WEAK void HAL_DCMI_PipeFrameEventCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  STM32_UNUSED(hdcmi);
  STM32_UNUSED(pipe);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_DCMI_PipeFrameEventCallback could be implemented in the user file.
   */
}

/**
  * @brief  DCMI Pipe Vsync event callback.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  pipe   Value from @ref hal_dcmi_pipe_t enumeration
  */
__WEAK void HAL_DCMI_PipeVsyncEventCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  STM32_UNUSED(hdcmi);
  STM32_UNUSED(pipe);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_DCMI_PipeVsyncEventCallback could be implemented in the user file.
   */
}

/**
  * @brief  DCMI Pipe line event callback.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  pipe   Value from @ref hal_dcmi_pipe_t enumeration
  */
__WEAK void HAL_DCMI_PipeLineEventCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  STM32_UNUSED(hdcmi);
  STM32_UNUSED(pipe);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_DCMI_PipeLineEventCallback could be implemented in the user file.
   */
}

/**
  * @brief  DCMI Pipe error callback.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @param  pipe   Value from @ref hal_dcmi_pipe_t enumeration
  */
__WEAK void HAL_DCMI_PipeErrorCallback(hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  STM32_UNUSED(hdcmi);
  STM32_UNUSED(pipe);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_DCMI_PipeErrorCallback could be implemented in the user file.
   */
}

/**
  * @brief  DCMI error callback.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  */
__WEAK void HAL_DCMI_ErrorCallback(hal_dcmi_handle_t *hdcmi)
{
  STM32_UNUSED(hdcmi);
  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_DCMI_ErrorCallback could be implemented in the user file.
   */
}
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group7
  * @{
This subsection provides a function to:
  - HAL_DCMI_SetDMA() : Link the DMA handle to the DCMI handle.
  */

/**
  * @brief  Link the DMA handle to the DCMI handle.
  * @param  hdcmi              Pointer to a hal_dcmi_handle_t structure
  * @param  hdma               Pointer to a hal_dma_handle_t structure
  * @retval HAL_INVALID_PARAM  Invalid parameter when pointer to DMA handle is NULL
  * @retval HAL_OK             DCMI handle and DMA handle are successfully linked
  */
hal_status_t HAL_DCMI_SetDMA(hal_dcmi_handle_t *hdcmi, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);

  ASSERT_DBG_STATE(hdcmi->global_state, ((uint32_t)HAL_DCMI_STATE_INIT | (uint32_t)HAL_DCMI_STATE_CONFIGURED));
  ASSERT_DBG_STATE(hdcmi->pipe_states[HAL_DCMI_PIPE_0],
                   ((uint32_t) HAL_DCMI_PIPE_STATE_RESET | (uint32_t) HAL_DCMI_PIPE_STATE_IDLE));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdcmi->hdma    = hdma;
  hdma->p_parent = hdcmi;

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group8
  * @{
This subsection provides functions allowing to
 - HAL_DCMI_GetState()          : Check the DCMI state.
 - HAL_DCMI_GetPipeState()      : Check the DCMI Pipe state.
 - HAL_DCMI_GetLastErrorCodes() : Get the specific DCMI error flag.
  */

/**
  * @brief  Return the DCMI state.
  * @param  hdcmi             Pointer to a hal_dcmi_handle_t structure
  * @retval hal_dcmi_state_t  DCMI global state
  */
hal_dcmi_state_t HAL_DCMI_GetState(const hal_dcmi_handle_t *hdcmi)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);

  return hdcmi->global_state;
}

/**
  * @brief  Return the DCMI pipe state.
  * @param  hdcmi                  Pointer to a hal_dcmi_handle_t structure
  * @param  pipe                   Value from @ref hal_dcmi_pipe_t enumeration
  * @retval hal_dcmi_pipe_state_t  DCMI pipe state
  */
hal_dcmi_pipe_state_t HAL_DCMI_GetPipeState(const hal_dcmi_handle_t *hdcmi, hal_dcmi_pipe_t pipe)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);
  ASSERT_DBG_PARAM(IS_DCMI_PIPE(pipe));

  return hdcmi->pipe_states[pipe];
}

#if defined (USE_HAL_DCMI_GET_LAST_ERRORS) && (USE_HAL_DCMI_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the DCMI error code.
  * @param  hdcmi    Pointer to a hal_dcmi_handle_t structure
  * @retval uint32_t Error code value which can be a combination of:
  *                  @arg @ref HAL_DCMI_ERROR_NONE          : No error
  *                  @arg @ref HAL_DCMI_ERROR_PIPE0_OVR     : Overrun pipe error
  *                  @arg @ref HAL_DCMI_ERROR_PARALLEL_SYNC : Synchronization error
  *                  @arg @ref HAL_DCMI_ERROR_PIPE0_DMA     : DMA error
  */
uint32_t HAL_DCMI_GetLastErrorCodes(const hal_dcmi_handle_t *hdcmi)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);

  return hdcmi->last_error_codes;
}
#endif /* USE_HAL_DCMI_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined (USE_HAL_DCMI_USER_DATA) && (USE_HAL_DCMI_USER_DATA == 1)
/** @addtogroup DCMI_Exported_Functions_Group9
  * @{
A set of functions allowing to manage a user data pointer stored to the DCMI handle:
 - HAL_DCMI_SetUserData() Set the user data into the handle
 - HAL_DCMI_GetUserData() Get the user data from the handle
  */

/**
  * @brief  Set the user data pointer into the handle.
  * @param  hdcmi        Pointer to a hal_dcmi_handle_t structure
  * @param  p_user_data  Pointer to the user data
  */
void HAL_DCMI_SetUserData(hal_dcmi_handle_t *hdcmi, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);

  hdcmi->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer from the handle.
  * @param  hdcmi  Pointer to a hal_dcmi_handle_t structure
  * @retval Pointer to the user data.
  */
const void *HAL_DCMI_GetUserData(const hal_dcmi_handle_t *hdcmi)
{
  ASSERT_DBG_PARAM(hdcmi != NULL);

  return (hdcmi->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_DCMI_USER_DATA */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup DCMI_Private_Functions
  * @{
  */

/**
  * @brief  Start the DCMI capture using the DMA by enabling the required interrupts.
  * @param  hdcmi       Pointer to a hal_dcmi_handle_t structure
  * @param  capture     DCMI capture mode snapshot or continuous grab
  *                     This parameter can be a value of @ref hal_dcmi_capture_t enumeration
  * @param  dest_addr   The destination memory Buffer address (LCD Frame buffer)
  * @param  size_byte   The length of capture to be transferred
  * @param  interrupts  DCMI Optional Interrupts
  *                     This parameter can be a value of @ref DCMI_Optional_Interrupts group
  * @retval HAL_ERROR   The transfer mode parameter is linked-list linear or the DMA channel state is active
  * @retval HAL_OK      The DMA channel peripheral transfer is successfully started
  */
static hal_status_t DCMI_StartPipe_DMA_Opt(hal_dcmi_handle_t *hdcmi,
                                           uint32_t dest_addr,
                                           uint32_t size_byte,
                                           hal_dcmi_capture_t capture,
                                           uint32_t interrupts)
{
  uint32_t tmp_size = size_byte;
  uint32_t tmp_addr = dest_addr;
  __IO uint32_t *cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

  hdcmi->hdma->p_xfer_cplt_cb  = DCMI_DMAXferCplt;
  hdcmi->hdma->p_xfer_error_cb = DCMI_Error;

  MODIFY_REG(*cr_register, DCMI_CR_CM, (uint32_t)capture);

  SET_BIT(*cr_register, DCMI_CR_ENABLE);

  hdcmi->xfer_size = 0U;

  if (tmp_size > DCMI_DMA_MAX_SIZE)
  {
    hdcmi->xfer_count = 1U;
    hdcmi->xfer_size  = tmp_size;
    hdcmi->buff_addr  = tmp_addr;

    while (hdcmi->xfer_size > DCMI_DMA_MAX_SIZE)
    {
      hdcmi->xfer_size  = hdcmi->xfer_size  / 2U;
      hdcmi->xfer_count = hdcmi->xfer_count * 2U;
    }

    hdcmi->xfer_number = hdcmi->xfer_count - 1U;
    tmp_size           = hdcmi->xfer_size;
    tmp_addr           = tmp_addr + tmp_size;
  }

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hdcmi->hdma,
                                     (uint32_t) &(DCMI_GET_INSTANCE(hdcmi)->DR),
                                     tmp_addr,
                                     tmp_size,
                                     HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  HAL_DCMI_ClearFlag(hdcmi, HAL_DCMI_FLAG_ALL);

  HAL_DCMI_EnableIT(hdcmi, ((uint32_t)interrupts
                            | (uint32_t)HAL_DCMI_IT_PIPE0_VSYNC
                            | (uint32_t)HAL_DCMI_IT_PIPE0_OVR
                            | (uint32_t)HAL_DCMI_IT_PARALLEL_SYNC_ERR
                            | (uint32_t)HAL_DCMI_IT_PIPE0_FRAME));

  SET_BIT(*cr_register, DCMI_CR_CAPTURE);

  return HAL_OK;
}

/**
  * @brief DMA conversion complete callback.
  * @param hdma  Pointer to a hal_dma_handle_t structure
  */
static void DCMI_DMAXferCplt(hal_dma_handle_t *hdma)
{
  hal_dcmi_handle_t *hdcmi        = (hal_dcmi_handle_t *)(hdma->p_parent);
  hal_dcmi_capture_t capture_mode = (hal_dcmi_capture_t)(uint32_t)READ_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_CM);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  uint32_t tmp_buff_addr;
  uint32_t tmp_xfer_size;
  uint32_t tmp_xfer_number;
  uint32_t tmp_xfer_count;

  if (hdcmi->xfer_size != 0U)
  {
    tmp_buff_addr   = hdcmi->buff_addr;
    tmp_xfer_size   = hdcmi->xfer_size;
    tmp_xfer_number = hdcmi->xfer_number;
    tmp_xfer_count  = hdcmi->xfer_count - 1U;

    hdma->p_head_node->regs[4U] = tmp_buff_addr + ((tmp_xfer_number - tmp_xfer_count + 1U) * tmp_xfer_size);
    hdcmi->xfer_count--;

    if (hdcmi->xfer_count == 0U)
    {
      hdma->p_head_node->regs[4U] = tmp_buff_addr;

      if (capture_mode == HAL_DCMI_CAPTURE_CONTINUOUS)
      {
        hdcmi->xfer_count = hdcmi->xfer_number + 1U;
      }
      else
      {
        hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_IDLE;
      }

      HAL_DCMI_EnableIT(hdcmi, HAL_DCMI_IT_PIPE0_FRAME);
    }
  }
  else
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    if (capture_mode == HAL_DCMI_CAPTURE_SNAPSHOT)
    {
      hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_IDLE;
    }
  }
}

/**
  * @brief DMA error callback.
  * @param hdma  Pointer to a hal_dma_handle_t structure
  */
static void DCMI_Error(hal_dma_handle_t *hdma)
{
  hal_dcmi_handle_t *hdcmi = (hal_dcmi_handle_t *)(hdma->p_parent);

  CLEAR_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_ENABLE);

  hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_IDLE;

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
  hdcmi->error_cb(hdcmi);
#else
  HAL_DCMI_ErrorCallback(hdcmi);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA abort complete callback.
  * @param hdma  Pointer to a hal_dma_handle_t structure
  */
static void DCMI_PipeError(hal_dma_handle_t *hdma)
{
  hal_dcmi_handle_t *hdcmi = (hal_dcmi_handle_t *)(hdma->p_parent);

  CLEAR_BIT(DCMI_GET_INSTANCE(hdcmi)->CR, DCMI_CR_ENABLE);

  hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_IDLE;

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
  hdcmi->pipe_error_cb(hdcmi, HAL_DCMI_PIPE_0);
#else
  HAL_DCMI_PipeErrorCallback(hdcmi, HAL_DCMI_PIPE_0);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */
}

/**
  * @brief DMA abort complete callback.
  * @param hdma  Pointer to a hal_dma_handle_t structure
  */
static void DCMI_Stop(hal_dma_handle_t *hdma)
{
  hal_dcmi_handle_t *hdcmi = (hal_dcmi_handle_t *)(hdma->p_parent);
  uint32_t count = DCMI_TIMEOUT_STOP * (SystemCoreClock / DCMI_NB_OF_CYCLE_DIVIDER / 1000U);
  __IO uint32_t *cr_register;

  cr_register = &DCMI_GET_INSTANCE(hdcmi)->CR;

  do
  {
    count--;

  } while ((READ_BIT(*cr_register, DCMI_CR_CAPTURE) != 0U) && (count > 0U));

  CLEAR_BIT(*cr_register, DCMI_CR_ENABLE);

  hdcmi->pipe_states[HAL_DCMI_PIPE_0] = HAL_DCMI_PIPE_STATE_IDLE;

#if defined (USE_HAL_DCMI_REGISTER_CALLBACKS) && (USE_HAL_DCMI_REGISTER_CALLBACKS == 1)
  hdcmi->pipe_stop_cb(hdcmi, HAL_DCMI_PIPE_0);
#else
  HAL_DCMI_PipeStopCallback(hdcmi, HAL_DCMI_PIPE_0);
#endif /* USE_HAL_DCMI_REGISTER_CALLBACKS */
}
/**
  * @}
  */

#endif /* USE_HAL_DCMI_MODULE */
/**
  * @}
  */

/**
  * @}
  */
