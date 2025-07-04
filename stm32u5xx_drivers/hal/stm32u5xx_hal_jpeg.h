/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_jpeg.h
  * @brief   Header file of JPEG HAL module.
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
#ifndef STM32U5XX_HAL_JPEG_H
#define STM32U5XX_HAL_JPEG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (JPEG)

/** @defgroup JPEG  JPEG
  * @{
  */

/** @defgroup JPEG_Exported_Types JPEG Exported Types
  * @{
  */

/*! JPEG Header processing (generation/parsing) status enumeration definition */
typedef enum
{
  HAL_JPEG_HEADER_PROCESSING_DISABLED = 0U, /*!< Header parsing feature disabled  */
  HAL_JPEG_HEADER_PROCESSING_ENABLED  = 1U  /*!< Header parsing feature Enabled   */
} hal_jpeg_header_processing_state_t;

/*! JPEG JPEG_ColorSpace definition */
typedef enum
{
  HAL_JPEG_IN_FORMAT_GRAYSCALE  = 0x0U,                                     /*!< Grayscale Colorspace */

  HAL_JPEG_IN_FORMAT_YCBCR_444  = JPEG_CONFR1_NF_1
                                  | JPEG_CONFR4_HSF_0 | JPEG_CONFR4_VSF_0,  /*!< YCbCr Colorspace : Subsampling 4:4:4 */
  HAL_JPEG_IN_FORMAT_YCBCR_422  = JPEG_CONFR1_NF_1
                                  | JPEG_CONFR4_HSF_1 | JPEG_CONFR4_VSF_0
                                  | JPEG_CONFR4_NB_1,                       /*!< YCbCr Colorspace : Subsampling 4:2:2 */
  HAL_JPEG_IN_FORMAT_YCBCR_420  = JPEG_CONFR1_NF_1
                                  | JPEG_CONFR4_HSF_1 | JPEG_CONFR4_VSF_1
                                  | JPEG_CONFR4_NB_0 | JPEG_CONFR4_NB_1,    /*!< YCbCr Colorspace : Subsampling 4:2:0 */
  HAL_JPEG_IN_FORMAT_CMYK       = JPEG_CONFR1_NF                            /*!< CMYK Colorspace : No Subsampling */
} hal_jpeg_input_format_t;

/*! JPEG Configuration for encoding structure definition */
typedef struct
{
  hal_jpeg_input_format_t input_format;  /*!< Image Color space : gray-scale, YCBCR or CMYK
                                              This parameter can be a value of JPEG_ColorSpace */
  uint32_t                image_height;  /*!< Image height : number of lines */
  uint32_t                image_width;   /*!< Image width : number of pixels per line */
  uint32_t                image_quality; /*!< Quality of the JPEG encoding : from 1 to 100 */
} hal_jpeg_config_t;

/*! JPEG State machine definition */
typedef enum
{
  HAL_JPEG_STATE_RESET         = (0U),        /*!< JPEG not yet initialized or disabled       */
  HAL_JPEG_STATE_IDLE          = (1UL << 31), /*!< JPEG configured and ready for use          */
  HAL_JPEG_STATE_ACTIVE_DECODE = (1UL << 30), /*!< JPEG internal decode processing is ongoing */
  HAL_JPEG_STATE_ACTIVE_ENCODE = (1UL << 29)  /*!< JPEG internal encode processing is ongoing */
} hal_jpeg_state_t;

/*! JPEG Encode configuration state definition */
typedef enum
{
  HAL_JPEG_ENCODE_CONFIG_STATE_RESET      = (1UL << 31), /*!< The Encode configuration not yet done */
  HAL_JPEG_ENCODE_CONFIG_STATE_CONFIGURED = (1UL << 30)  /*!< The Encode configuration Done and ready for use*/
} hal_jpeg_encode_config_state_t;

/*! JPEG Instance definition */
typedef enum
{
  HAL_JPEG = (uint32_t)JPEG, /*!< JPEG Instance */
} hal_jpeg_t;

typedef struct hal_jpeg_handle_s hal_jpeg_handle_t; /*!< JPEG Handle type definition */

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
/*! Pointer to a generic JPEG callback */
typedef void (*hal_jpeg_cb_t)(hal_jpeg_handle_t *hjpeg);

/*! Pointer to a JPEG get data callback */
typedef void (*hal_jpeg_get_data_cb_t)(hal_jpeg_handle_t *hjpeg, uint32_t nb_decoded_data_byte);

/*! Pointer to a JPEG data ready callback */
typedef void (*hal_jpeg_data_ready_cb_t)(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_out,
                                         uint32_t out_data_length_byte);

#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

/*! JPEG Handle structure definition */
struct hal_jpeg_handle_s
{
  hal_jpeg_t                                   instance;            /*!< JPEG peripheral register base address  */
  volatile hal_jpeg_state_t                    global_state;        /*!< JPEG global state                      */
  volatile hal_jpeg_encode_config_state_t      encode_config_state; /*!< Encode configuration state             */
  volatile uint32_t                            context;             /*!< JPEG internal context                  */
  volatile hal_jpeg_header_processing_state_t header_processing;    /*!< Enable/Disable the header processing   */

#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
  volatile uint32_t  last_error_codes;      /*!< JPEG  error codes   */
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

  const uint8_t      *p_jpeg_in_buff;      /*!< Pointer to JPEG processing (encoding, decoding,...) input buffer      */
  uint8_t            *p_jpeg_out_buff;     /*!< Pointer to JPEG processing (encoding, decoding,...) output buffer     */
  volatile uint32_t  jpeg_in_count_byte;   /*!< Internal counter of input data                                        */
  volatile uint32_t  jpeg_out_count_byte;  /*!< Internal counter of output data                                       */
  uint32_t           in_data_length_byte;  /*!< Input buffer length in bytes                                          */
  uint32_t           out_data_length_byte; /*!< Output buffer length in bytes                                         */
  const uint8_t      *p_quant_table0;      /*!< Basic quantization table for component 0                              */
  const uint8_t      *p_quant_table1;      /*!< Basic quantization table for component 1                              */
  const uint8_t      *p_quant_table2;      /*!< Basic quantization table for component 2                              */
  const uint8_t      *p_quant_table3;      /*!< Basic quantization table for component 3                              */
  uint8_t            custom_quant_table;   /*!< If set to 1 specify that user customized quantization tables are used */
#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
  hal_dma_handle_t    *hdma_in;             /*!< JPEG In DMA handle parameters  */
  hal_dma_handle_t    *hdma_out;            /*!< JPEG Out DMA handle parameters */
#endif /* USE_HAL_JPEG_DMA */

#if defined (USE_HAL_JPEG_USER_DATA) && (USE_HAL_JPEG_USER_DATA == 1)
  const void         *p_user_data;          /*!< JPEG  user data */
#endif /* USE_HAL_JPEG_USER_DATA */

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
  hal_jpeg_cb_t               p_encode_cplt_cb;  /*!< JPEG Encode complete callback */
  hal_jpeg_cb_t               p_decode_cplt_cb;  /*!< JPEG Decode complete callback */
  hal_jpeg_cb_t               p_error_cb;        /*!< JPEG Error callback           */
  hal_jpeg_cb_t               p_info_ready_cb;   /*!< JPEG Info ready callback      */
  hal_jpeg_get_data_cb_t      p_get_data_cb;     /*!< JPEG Get Data callback        */
  hal_jpeg_data_ready_cb_t    p_data_ready_cb;   /*!< JPEG Data ready callback      */
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
};

/**
  * @}
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup JPEG_Exported_Constants JPEG Exported Constants
  * @{
  */

/** @defgroup JPEG_Error_Code_definition JPEG Error Code definition
  * @brief  JPEG Error Code definition
  * @{
  */
#define HAL_JPEG_ERROR_NONE 0x0U    /*!< No error             */
#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
#define HAL_JPEG_ERROR_DMA  0x1U    /*!< DMA transfer error   */
#endif /*USE_HAL_JPEG_DMA*/
/**
  * @}
  */

/** @defgroup JPEG_Quantization_Table_Size JPEG Quantization Table Size
  * @brief  JPEG Quantization Table Size
  * @{
  */
#define HAL_JPEG_QUANT_TABLE_SIZE  64U /*!< JPEG Quantization Table Size in bytes  */
/**
  * @}
  */

/** @defgroup JPEG_ImageQuality JPEG Image Quality
  * @brief  JPEG Min and Max Image Quality
  * @{
  */
#define HAL_JPEG_IMAGE_QUALITY_MIN     1U    /*!< Minimum JPEG quality */
#define HAL_JPEG_IMAGE_QUALITY_MAX     100U  /*!< Maximum JPEG quality */
/**
  * @}
  */

/** @defgroup JPEG_Flags_Definition JPEG Flags definition
  * @brief JPEG Flags definition
  * @{
  */
#define HAL_JPEG_FLAG_IFT   JPEG_SR_IFTF       /*!< Input FIFO threshold reached flag                              */
#define HAL_JPEG_FLAG_IFNF  JPEG_SR_IFNFF      /*!< Input FIFO Not full flag                                       */
#define HAL_JPEG_FLAG_OFT   JPEG_SR_OFTF       /*!< Output FIFO threshold reached flag                             */
#define HAL_JPEG_FLAG_OFNE  JPEG_SR_OFNEF      /*!< Output FIFO not empty flag                                     */
#define HAL_JPEG_FLAG_EOC   JPEG_SR_EOCF       /*!< End of conversion flag; converted data sent to the output FIFO */
#define HAL_JPEG_FLAG_HPD   JPEG_SR_HPDF       /*!< Header parsing done flag ,header data in internal registers    */
#define HAL_JPEG_FLAG_CO    JPEG_SR_COF        /*!< JPEG conversion in progress flag                               */
#define HAL_JPEG_FLAG_ALL   (JPEG_SR_IFTF    \
                             | JPEG_SR_IFNFF \
                             | JPEG_SR_OFTF  \
                             | JPEG_SR_OFNEF \
                             | JPEG_SR_EOCF  \
                             | JPEG_SR_HPDF  \
                             | JPEG_SR_COF )    /*!< All JPEG flags                                                 */
/**
  * @}
  */

/** @defgroup JPEG_Interrupt_configuration_definition JPEG Interrupt configuration definition
  * @brief JPEG Interrupt definition
  * @{
  */
#define HAL_JPEG_IT_IFT   JPEG_CR_IFTIE   /*!< Input FIFO threshold interrupt  */
#define HAL_JPEG_IT_IFNF  JPEG_CR_IFNFIE  /*!< Input FIFO not full interrupt   */
#define HAL_JPEG_IT_OFT   JPEG_CR_OFTIE   /*!< Output FIFO threshold interrupt */
#define HAL_JPEG_IT_OFNE  JPEG_CR_OFNEIE  /*!< Output FIFO not empty interrupt */
#define HAL_JPEG_IT_EOC   JPEG_CR_EOCIE   /*!< End of conversion interrupt     */
#define HAL_JPEG_IT_HPD   JPEG_CR_HPDIE   /*!< Header parsing done interrupt   */
#define HAL_JPEG_IT_ALL   (JPEG_CR_IFTIE    \
                           | JPEG_CR_IFNFIE \
                           | JPEG_CR_OFTIE  \
                           | JPEG_CR_OFNEIE \
                           | JPEG_SR_EOCF   \
                           | JPEG_CR_EOCIE  \
                           | JPEG_CR_HPDIE )    /*!< All JPEG interrupt sources */
/**
  * @}
  */

/**
  * @}
  */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Exported_Functions  JPEG Exported Functions
  * @{
  */

/** @defgroup JPEG_Exported_Functions_Group1 Initialization de-initialization functions
  * @{
  */
/* Initialization/de-initialization functions */
hal_status_t HAL_JPEG_Init(hal_jpeg_handle_t *hjpeg, hal_jpeg_t instance);
void         HAL_JPEG_DeInit(hal_jpeg_handle_t *hjpeg);

/**
  * @}
  */

/** @defgroup JPEG_Exported_Functions_Group2  Encoding/Decoding Configuration functions
  * @{
  */
/* Encoding/Decoding configuration functions */
hal_status_t HAL_JPEG_SetConfigEncoding(hal_jpeg_handle_t *hjpeg, const hal_jpeg_config_t *p_config);
hal_status_t HAL_JPEG_GetLastDecodeInfo(hal_jpeg_handle_t *hjpeg, hal_jpeg_config_t *p_info);
hal_status_t HAL_JPEG_EnableHeaderProcessing(hal_jpeg_handle_t *hjpeg);
hal_status_t HAL_JPEG_DisableHeaderProcessing(hal_jpeg_handle_t *hjpeg);
hal_status_t HAL_JPEG_SetUserQuantTables1(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable1);
hal_status_t HAL_JPEG_SetUserQuantTables2(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable2);
hal_status_t HAL_JPEG_SetUserQuantTables3(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable3);
hal_status_t HAL_JPEG_SetUserQuantTables4(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable4);

/**
  * @}
  */

/** @defgroup JPEG_Exported_Functions_Group3 JPEG processing functions
  * @{
  */
/* JPEG Processing functions */
hal_status_t  HAL_JPEG_Encode(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in_mcu, uint32_t in_data_length_byte,
                              uint8_t *p_data_out, uint32_t out_data_length_byte, uint32_t timeout_ms);
hal_status_t  HAL_JPEG_Decode(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in, uint32_t in_data_length_byte,
                              uint8_t *p_data_out_mcu, uint32_t out_data_length_byte, uint32_t timeout_ms);
hal_status_t  HAL_JPEG_Encode_IT(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in_mcu, uint32_t in_data_length_byte,
                                 uint8_t *p_data_out, uint32_t out_data_length_byte);
hal_status_t  HAL_JPEG_Decode_IT(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in, uint32_t in_data_length_byte,
                                 uint8_t *p_data_out_mcu, uint32_t out_data_length_byte);

#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
hal_status_t  HAL_JPEG_Encode_DMA(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in_mcu, uint32_t in_data_length_byte,
                                  uint8_t *p_data_out, uint32_t out_data_length_byte);
hal_status_t  HAL_JPEG_Decode_DMA(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in, uint32_t in_data_length_byte,
                                  uint8_t *p_data_out_mcu, uint32_t out_data_length_byte);

hal_status_t HAL_JPEG_SetTxDMA(hal_jpeg_handle_t *hjpeg, hal_dma_handle_t *hdma);
hal_status_t HAL_JPEG_SetRxDMA(hal_jpeg_handle_t *hjpeg, hal_dma_handle_t *hdma);
#endif /* USE_HAL_JPEG_DMA */

hal_status_t  HAL_JPEG_PauseInputBuffer(hal_jpeg_handle_t *hjpeg);
hal_status_t  HAL_JPEG_PauseOutputBuffer(hal_jpeg_handle_t *hjpeg);

hal_status_t  HAL_JPEG_ResumeInputBuffer(hal_jpeg_handle_t *hjpeg);
hal_status_t  HAL_JPEG_ResumeOutputBuffer(hal_jpeg_handle_t *hjpeg);

hal_status_t HAL_JPEG_UpdateInputBuffer(hal_jpeg_handle_t *hjpeg, const uint8_t *p_new_input_buffer,
                                        uint32_t in_data_length_byte);
hal_status_t HAL_JPEG_UpdateOutputBuffer(hal_jpeg_handle_t *hjpeg, uint8_t *p_new_output_buffer,
                                         uint32_t out_data_length_byte);
hal_status_t HAL_JPEG_Abort(hal_jpeg_handle_t *hjpeg);


/**
  * @}
  */

/** @defgroup JPEG_Exported_Functions_Group4  JPEG Decode/Encode callback functions
  * @{
  */
/* JPEG Decode/Encode callback functions */

void HAL_JPEG_InfoReadyCallback(hal_jpeg_handle_t *hjpeg);
void HAL_JPEG_EncodeCpltCallback(hal_jpeg_handle_t *hjpeg);
void HAL_JPEG_DecodeCpltCallback(hal_jpeg_handle_t *hjpeg);
void HAL_JPEG_ErrorCallback(hal_jpeg_handle_t *hjpeg);
void HAL_JPEG_GetDataCallback(hal_jpeg_handle_t *hjpeg, uint32_t nb_decoded_data_byte);
void HAL_JPEG_DataReadyCallback(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_out, uint32_t out_data_length_byte);

/**
  * @}
  */

/** @defgroup JPEG_Exported_Functions_Group5 JPEG IRQ handler management and callbacks functions registration
  * @{
  */
/* JPEG IRQ Handler management */
void HAL_JPEG_IRQHandler(hal_jpeg_handle_t *hjpeg);

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
/* JPEG callback registration */
hal_status_t HAL_JPEG_RegisterInfoReadyCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback);
hal_status_t HAL_JPEG_RegisterGetDataCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_get_data_cb_t callback);
hal_status_t HAL_JPEG_RegisterDataReadyCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_data_ready_cb_t callback);
hal_status_t HAL_JPEG_RegisterEncodeCpltCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback);
hal_status_t HAL_JPEG_RegisterDecodeCpltCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback);
hal_status_t HAL_JPEG_RegisterErrorCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback);

#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup JPEG_Exported_Functions_Group6  Peripheral State and Error functions
  * @{
  */
/* Peripheral State and Error functions */
hal_jpeg_state_t               HAL_JPEG_GetState(const hal_jpeg_handle_t *hjpeg);
hal_jpeg_encode_config_state_t HAL_JPEG_GetEncoderState(const hal_jpeg_handle_t *hjpeg);

#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
uint32_t        HAL_JPEG_GetLastErrorCodes(const hal_jpeg_handle_t *hjpeg);
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */
/**
  * @}
  */
/** @defgroup JPEG_Exported_Functions_Group7 Set/Get user data functions
  * @{
  */
/* Set/Get user data functions */
#if defined(USE_HAL_JPEG_USER_DATA) && (USE_HAL_JPEG_USER_DATA == 1)
void HAL_JPEG_SetUserData(hal_jpeg_handle_t *hjpeg, const void *p_user_data);
const void *HAL_JPEG_GetUserData(const hal_jpeg_handle_t *hjpeg);
#endif /* USE_HAL_JPEG_USER_DATA */
/**
  * @}
  */

/** @defgroup JPEG_Exported_Functions_Group8 JPEG Flags management functions
  * @{
  */
/**
  * @brief  Check the specified JPEG status flag.
  * @param  hjpeg Specifies the JPEG handle.
  * @param  flag  Specifies the flag to check
  *         This parameter can be one of the following values:
  *            @arg HAL_JPEG_FLAG_IFT  : Input FIFO threshold reached flag
  *            @arg HAL_JPEG_FLAG_IFNF : Input FIFO not full flag
  *            @arg HAL_JPEG_FLAG_OFT  : Output FIFO threshold reached flag
  *            @arg HAL_JPEG_FLAG_OFNE : Output FIFO not empty flag
  *            @arg HAL_JPEG_FLAG_EOC  : End of conversion flag; converted data sent to the output FIFO
  *            @arg HAL_JPEG_FLAG_HPD  : Header parsing done flag ,header data in internal registers
  *            @arg HAL_JPEG_FLAG_CO   : JPEG conversion in progress flag
  * @retval The status of JPEG flag (ACTIVE  or NOT ACTIVE)
  */
__STATIC_INLINE uint32_t HAL_JPEG_IsActiveFlag(const hal_jpeg_handle_t *hjpeg, uint32_t flag)
{
  return ((READ_BIT(((JPEG_TypeDef *)((uint32_t) hjpeg->instance))->SR, flag) == flag) ? 1UL : 0UL);
}

/**
  * @brief  Clear the specified JPEG status flag.
  * @param  hjpeg Specifies the JPEG handle.
  * @param  flag  Specifies the flag to clear
  *         This parameter can be a combination of the following values:
  *            @arg HAL_JPEG_FLAG_IFT  : Input FIFO threshold reached flag
  *            @arg HAL_JPEG_FLAG_IFNF : Input FIFO not full flag
  *            @arg HAL_JPEG_FLAG_OFT  : Output FIFO threshold reached flag
  *            @arg HAL_JPEG_FLAG_OFNE : Output FIFO not empty flag
  *            @arg HAL_JPEG_FLAG_EOC  : End of conversion flag; converted data sent to the output FIFO
  *            @arg HAL_JPEG_FLAG_HPD  : Header parsing done flag ,header data in internal registers
  *            @arg HAL_JPEG_FLAG_CO   : JPEG conversion in progress flag
  *            @arg HAL_JPEG_FLAG_ALL  : All JPEG flags
  */
__STATIC_INLINE void HAL_JPEG_ClearFlag(hal_jpeg_handle_t *hjpeg, uint32_t flag)
{
  WRITE_REG(((JPEG_TypeDef *)((uint32_t) hjpeg->instance))->CFR, flag);
}

/**
  * @brief  Enable Interrupt.
  * @param  hjpeg      Specifies the JPEG handle.
  * @param  it_source  Specifies the interrupt to enable
  *         This parameter can be a combination of the following values:
  *            @arg HAL_JPEG_IT_IFT  : Input FIFO threshold interrupt
  *            @arg HAL_JPEG_IT_IFNF : Input FIFO not Full interrupt
  *            @arg HAL_JPEG_IT_OFT  : Output FIFO threshold interrupt
  *            @arg HAL_JPEG_IT_OFNE : Output FIFO not empty interrupt
  *            @arg HAL_JPEG_IT_EOC  : End of conversion interrupt
  *            @arg HAL_JPEG_IT_HPD  : Header parsing done interrupt
  *            @arg HAL_JPEG_IT_ALL  : All JPEG interrupt sources
  */
__STATIC_INLINE void HAL_JPEG_EnableIT(hal_jpeg_handle_t *hjpeg, uint32_t it_source)
{
  SET_BIT(((JPEG_TypeDef *)((uint32_t) hjpeg->instance))->CR, it_source);
}

/**
  * @brief  Disable Interrupt.
  * @param  hjpeg     Specifies the JPEG handle.
  * @param  it_source Specifies the interrupt to disable
  *         This parameter can be a combination of the following values:
  *            @arg HAL_JPEG_IT_IFT  : Input FIFO threshold interrupt
  *            @arg HAL_JPEG_IT_IFNF : Input FIFO not Full interrupt
  *            @arg HAL_JPEG_IT_OFT  : Output FIFO threshold interrupt
  *            @arg HAL_JPEG_IT_OFNE : Output FIFO not empty interrupt
  *            @arg HAL_JPEG_IT_EOC  : End of conversion interrupt
  *            @arg HAL_JPEG_IT_HPD  : Header parsing done interrupt
  *            @arg HAL_JPEG_IT_ALL  : All JPEG interrupt sources
  */
__STATIC_INLINE void HAL_JPEG_DisableIT(hal_jpeg_handle_t *hjpeg, uint32_t it_source)
{
  CLEAR_BIT(((JPEG_TypeDef *)((uint32_t) hjpeg->instance))->CR, it_source);
}

/**
  * @brief  Get Interrupt state.
  * @param  hjpeg      Specifies the JPEG handle.
  * @param  it_source  Specifies the interrupt to check
  *         This parameter can be a combination of the following values:
  *            @arg HAL_JPEG_IT_IFT  : Input FIFO threshold interrupt
  *            @arg HAL_JPEG_IT_IFNF : Input FIFO not Full interrupt
  *            @arg HAL_JPEG_IT_OFT  : Output FIFO threshold interrupt
  *            @arg HAL_JPEG_IT_OFNE : Output FIFO not empty interrupt
  *            @arg HAL_JPEG_IT_EOC  : End of conversion interrupt
  *            @arg HAL_JPEG_IT_HPD  : Header parsing done interrupt
  *
  * @retval returns The new state of it_source (Enabled or disabled)
  */
__STATIC_INLINE uint32_t HAL_JPEG_IsEnabledIT(const hal_jpeg_handle_t *hjpeg, uint32_t it_source)
{
  return ((READ_BIT(((JPEG_TypeDef *)((uint32_t) hjpeg->instance))->CR,
                    (uint32_t)it_source) == (uint32_t)it_source) ? 1U : 0U);
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

#endif /* JPEG */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_JPEG_H */
