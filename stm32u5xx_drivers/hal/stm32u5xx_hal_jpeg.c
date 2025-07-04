/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_jpeg.c
  * @brief   JPEG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the JPEG encoder/decoder peripheral:
  *           + Initialization and de-initialization functions
  *           + JPEG processing functions encoding and decoding
  *           + JPEG decoding Getting Info and encoding configuration setting
  *           + JPEG enable/disable header parsing functions
  *           + JPEG Input/Output Buffer configuration
  *           + JPEG callback functions
  *           + JPEG Abort/Pause/Resume functions
  *           + JPEG custom quantization tables setting functions
  *           + IRQ handler management
  *           + Peripheral State and Error functions
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

#if defined (JPEG)
/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup JPEG
  * @{

  ==============================================================================
                      The HAL JPEG driver can be used as follows:
  ==============================================================================
      - Initialize the JPEG handle by calling the HAL_JPEG_Init() API that performs these operations:
         - Associate instance to the handle
         - Enable the JPEG clock interface (When USE_HAL_JPEG_CLK_ENABLE_MODEL compilation flag is set to
           HAL_CLK_ENABLE_PERIPH_ONLY or HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM in the stm32u5xx_hal_conf.h module)
         - The initialization of the handle state to the HAL_JPEG_STATE_IDLE.

      - For JPEG encoding, use the HAL_JPEG_SetConfigEncoding() function to set the encoding parameters.
        This step is mandatory before calling the encoding function.
        The application can adjust the image_quality parameter, ranging from 1 to 100, to balance visual
        quality against the original raw image and the resulting JPEG file size.
        Higher values result in better visual quality but larger file sizes,
        while lower values produce smaller file sizes with reduced visual quality.

      - Note that for decoding operation the JPEG peripheral output data are organized in
         YCbCr blocks called MCU (Minimum Coded Unit) as defined in the JPEG specification
         ISO/IEC 10918-1 standard.
         It is up to the application to transform these YCbCr blocks to RGB data that can be display.

         Respectively, for Encoding operation the JPEG peripheral input must be organized
         in YCbCr MCU blocks. It is up to the application to perform the necessary RGB to YCbCr
         MCU blocks transformation before feeding the JPEG peripheral with data.

      - Use functions HAL_JPEG_Encode() and HAL_JPEG_Decode() to start respectively
         a JPEG encoding/decoding operation in polling method (blocking).

      - Use functions HAL_JPEG_Encode_IT() and HAL_JPEG_Decode_IT() to start respectively
         a JPEG encoding/decoding operation with Interrupt method (not blocking).

      - Use functions HAL_JPEG_Encode_DMA() and HAL_JPEG_Decode_DMA() to start respectively
         a JPEG encoding/decoding operation with DMA method (not blocking).

      - Callback definition:

          - Callback HAL_JPEG_InfoReadyCallback() is asserted if the current operation
            is a JPEG decoding to provide the application with JPEG image  parameters.
            This callback is asserted when the JPEG peripheral successfully parse the
            JPEG header.

          - Callback HAL_JPEG_GetDataCallback() is asserted for both encoding and decoding
            operations to inform the application that the input buffer has been
            consumed by the peripheral and to ask for a new data chunk if the operation
            (encoding/decoding) has not been complete yet.

              -  This CallBack must be implemented in the application side. It must
                call the function HAL_JPEG_UpdateInputBuffer() if new input data are available,
                or call HAL_JPEG_PauseInputBuffer()
                to inform the JPEG HAL driver that the ongoing operation must pause waiting for the
                application to provide a new input data chunk.
                Once the application succeed getting new data and if the input has been paused,
                the application can call the function HAL_JPEG_UpdateInputBuffer() to set the new
                input buffer and size, then resume the JPEG HAL input by calling new function
                HAL_JPEG_ResumeInputBuffer().
                If the application has ended feeding the HAL JPEG with input data (no more input data), the application
                must call the function HAL_JPEG_UpdateInputBuffer() (within the callback HAL_JPEG_GetDataCallback())
                with the parameter in_data_length_byte set to zero.

              - The mechanism of HAL_JPEG_UpdateInputBuffer()/ HAL_JPEG_PauseInputBuffer() and
                  HAL_JPEG_ResumeInputBuffer() allows to the application to provide the input data
                  (for encoding or decoding) by chunks.
                  If the new input data chunk is not available (because data must be read from an input file
                  for example) the application can pause the JPEG input (using function HAL_JPEG_PauseInputBuffer())
                  Once the new input data chunk is available ( read from a file for example), the application
                  can call the function HAL_JPEG_UpdateInputBuffer() to provide the HAL with the new chunk
                  then resume the JPEG HAL input by calling function HAL_JPEG_ResumeInputBuffer().

              - When the Input is paused, the application can call functions HAL_JPEG_UpdateInputBuffer()
                  then HAL_JPEG_ResumeInputBuffer() any time(outside the HAL_JPEG_GetDataCallback())
                  Once the new input chunk data available.
                  However, to keep data coherency, the function HAL_JPEG_PauseInputBuffer must be imperatively called
                  (if necessary) within the callback HAL_JPEG_GetDataCallback(), i.e when the HAL JPEG has ended
                  Transferring the previous chunk buffer to the JPEG peripheral.

          - Callback HAL_JPEG_DataReadyCallback() is asserted when the HAL JPEG driver
            has filled the given output buffer with the given size.

              - This CallBack must be implemented in the application side. It must
                  call the function HAL_JPEG_UpdateOutputBuffer() to provide the HAL JPEG driver
                  with the new output buffer location and size to be used  to store next data chunk.
                  if the application is not ready to provide the output chunk location then it can
                  call the function HAL_JPEG_PauseOutputBuffer()
                  to inform the JPEG HAL driver that it must pause output data. Once the application
                  is ready to receive the new data chunk (output buffer location free or available) it must call
                  the function HAL_JPEG_UpdateOutputBuffer() to provide the HAL JPEG driver
                  with the new output chunk buffer location and size, then call HAL_JPEG_ResumeOutputBuffer()
                  to inform the HAL that it must resume outputting data in the given output buffer.

              - The mechanism of HAL_JPEG_UpdateOutputBuffer()/HAL_JPEG_PauseOutputBuffer()/
                 HAL_JPEG_ResumeOutputBuffer() allows the application to receive data from the JPEG peripheral
                  by chunks. when a chunk is received, the application can pause the HAL JPEG output data
                  to be able to process these received data (YCbCr to RGB conversion in case of decoding or data
                  storage in case of encoding).

              - When the output is paused, the application can call functions HAL_JPEG_UpdateOutputBuffer()
                  then HAL_JPEG_ResumeOutputBuffer() any time(outside the HAL_JPEG_DataReadyCallback()) Once the output
                  data buffer is free to use.However, to keep data coherency, the function HAL_JPEG_PauseOutputBuffer()
                   must be imperatively called(if necessary) within the callback HAL_JPEG_ DataReadyCallback(),
                  i.e when the HAL JPEG has ended Transferring the previous chunk buffer from the JPEG peripheral
                  to the application.

          - Callback HAL_JPEG_EncodeCpltCallback() is asserted when the HAL JPEG driver has
            ended the current JPEG encoding operation, and all output data has been transmitted
            to the application.

          - Callback HAL_JPEG_DecodeCpltCallback() is asserted when the HAL JPEG driver has
            ended the current JPEG decoding operation. and all output data has been transmitted
            to the application.

          - Callback HAL_JPEG_ErrorCallback() is asserted when an error occurred during
            the current operation. the application can call the function HAL_JPEG_GetError()
            to retrieve the error codes.

      - By default the HAL JPEG driver uses the default quantization tables
         as provide in the JPEG specification (ISO/IEC 10918-1 standard) for encoding.
         User can change these default tables if necessary using the function HAL_JPEG_SetUserQuantTableX()
         Note that for decoding the quantization tables are automatically extracted from
         the JPEG header.

      - To get the HAL JPEG global_state you can use the following function: HAL_JPEG_GetState()

      - Callback registration

          - The compilation define  USE_HAL_JPEG_REGISTER_CALLBACKS when set to 1
          allows the user to configure dynamically the driver callbacks.
          Use Function  HAL_JPEG_RegisterXXXCallback()
          to register an interrupt callback.

            - HAL_JPEG_EncodeCpltCallback()  : callback for end of encoding operation.
            - HAL_JPEG_DecodeCpltCallback()  : callback for end of decoding operation.
            - HAL_JPEG_ErrorCallback()       : callback for error detection.
            - HAL_JPEG_InfoReadyCallback()   : callback for Info Ready.
            - HAL_JPEG_GetDataCallback()     : callback for Get Data.
            - HAL_JPEG_DataReadyCallback()   : callback for  Data Ready.

            By default, after the HAL_JPEG_Init() and when the global_state is HAL_JPEG_STATE_IDLE
              all callbacks are set to the corresponding weak functions :
              examples HAL_JPEG_DecodeCpltCallback() , HAL_JPEG_GetDataCallback() ,.

              Callbacks can be registered in HAL_JPEG_STATE_IDLE global_state only.
              When The compilation define USE_HAL_JPEG_REGISTER_CALLBACKS is set to 0 or
              not defined, the callback registration feature is not available and all callbacks
              are set to the corresponding weak functions.

      - Interrupt functions

          - Use HAL_JPEG_EnableIT() function to enable the interrupts.
          - Use HAL_JPEG_DisableIT() function to disable the interrupts.
          - Use HAL_JPEG_IsEnabledIT() function to get the source of interrupt.
          - Use HAL_JPEG_IsActiveFlag() function to get flags.
          - Use HAL_JPEG_ClearFlag() function to clear flags.

      - Configuration inside the JPEG driver
 Config defines                  | Description     | Default value     | Note
 ------------------------------- | --------------- | ----------------- | --------------------------------------------
 PRODUCT                         | from IDE        | None              | The selected device.
 USE_HAL_JPEG_MODULE             | from hal_conf.h | 1U                | Allows to use HAL JPEG module.
 USE_ASSERT_DBG_PARAM            | from IDE        | None              | Allows to use the assert check parameters.
 USE_ASSERT_DBG_STATE            | from IDE        | None              | Allows to use the assert check states.
 USE_HAL_CHECK_PARAM             | from hal_conf.h | 0                 | Allows to use the run-time checks parameters.
 USE_HAL_JPEG_DMA                | from hal_conf.h | 0                 | Allows to use DMA mode.
 USE_HAL_JPEG_REGISTER_CALLBACKS | from hal_conf.h | 0                 | Allows to use register callbacks.
 USE_HAL_JPEG_CLK_ENABLE_MODEL   | from hal_conf.h | HAL_CLK_ENABLE_NO | Allows to use the clock enable model.
 USE_HAL_DMA_GET_LAST_ERRORS     | from hal_conf.h | 0                 | Allows to use error code mechanism.
  */

#if defined (USE_HAL_JPEG_MODULE) && (USE_HAL_JPEG_MODULE == 1)

/* Private defines --------------------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Private_Constants  JPEG Private Constants
  * @{
  */
#define JPEG_TIMEOUT_VALUE       1000U     /*!< 1s */
#define JPEG_AC_HUFF_TABLE_SIZE  162U      /*!< Huffman AC table size : 162 codes*/
#define JPEG_DC_HUFF_TABLE_SIZE  12U       /*!< Huffman DC table size : 12 codes*/

#define JPEG_QUANT_TABLE_SIZE  64U         /*!< JPEG Quantization Table Size in bytes  */
#define JPEG_QUANTVAL_MAX 255U             /*!< Quantization values are 8-bit numbers*/
#define JPEG_LOW_QUALITY_REFERENCE  5000U  /*!< Reference value to generate scaling factor
                                                for low quality factors (<50) */
#define JPEG_HIGH_QUALITY_REFERENCE 200U   /*!< Reference value to generate scaling factor
                                                for high quality factors (>=50)*/
#define JPEG_FIFO_SIZE    16U              /*!< JPEG Input/Output HW FIFO size in words (4 byte unit ) */

#define JPEG_FIFO_TH_SIZE 4U               /*!< JPEG Input/Output HW FIFO Threshold in words (4 byte unit )*/

#define JPEG_DMA_IDMA  JPEG_CR_IDMAEN                   /*!< DMA request for the input FIFO */
#define JPEG_DMA_ODMA  JPEG_CR_ODMAEN                   /*!< DMA request for the output FIFO */
#define JPEG_DMA_MASK  (JPEG_DMA_IDMA | JPEG_DMA_ODMA ) /*!< JPEG DMA request Mask*/

#define JPEG_INTERRUPT_MASK (HAL_JPEG_IT_IFT    \
                             | HAL_JPEG_IT_IFNF \
                             | HAL_JPEG_IT_OFT  \
                             | HAL_JPEG_IT_OFNE \
                             | HAL_JPEG_IT_EOC  \
                             | HAL_JPEG_IT_HPD)  /*!< JPEG Interrupt Mask*/

#define JPEG_CONTEXT_ENCODE          (0x1U)      /*!< JPEG context : operation is encoding*/
#define JPEG_CONTEXT_DECODE          (0x2U)      /*!< JPEG context : operation is decoding*/
#define JPEG_CONTEXT_OPERATION_MASK  (0x3U)      /*!< JPEG context : operation Mask */

#define JPEG_CONTEXT_POLLING         (0x04U)     /*!< JPEG context : Transfer use Polling */
#define JPEG_CONTEXT_IT              (0x08U)     /*!< JPEG context : Transfer use Interrupt */
#define JPEG_CONTEXT_DMA             (0x10U)     /*!< JPEG context : Transfer use DMA */
#define JPEG_CONTEXT_METHOD_MASK     (0x01CU)    /*!< JPEG context : Transfer Mask */

#define JPEG_CONTEXT_CONF_ENCODING   (0x0100U)   /*!< JPEG context : encoding configuration done */

#define JPEG_CONTEXT_PAUSE_INPUT     (0x1000U)   /*!< JPEG context : Pause Input */
#define JPEG_CONTEXT_PAUSE_OUTPUT    (0x2000U)   /*!< JPEG context : Pause Output */

#define JPEG_CONTEXT_CUSTOM_TABLES   (0x4000U)   /*!< JPEG context : Use custom quantization tables */

#define JPEG_CONTEXT_ENDING_DMA      (0x8000U)   /*!< JPEG context : ending with DMA in progress */

#define JPEG_PROCESS_ONGOING         (0x0U)      /*!< Process is on going */
#define JPEG_PROCESS_DONE            (0x1U)      /*!< Process is done (ends) */

/*! Get the DMA remain data */
#define JPEG_GET_DMA_REMAIN_DATA(dma_instance)     (LL_DMA_GetBlkDataLength((dma_instance))\
                                                    + LL_DMA_GetFIFOLevel((dma_instance)))
/**
  * @}
  */


/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Private_Macros JPEG Private Macros
  * @{
  */
/*!< Check whether the value of input format is one of the defined values */
#define IS_JPEG_IN_FORMAT(input_format) (((input_format) == HAL_JPEG_IN_FORMAT_GRAYSCALE) \
                                         || ((input_format) == HAL_JPEG_IN_FORMAT_YCBCR_444) \
                                         || ((input_format) == HAL_JPEG_IN_FORMAT_YCBCR_422) \
                                         || ((input_format) == HAL_JPEG_IN_FORMAT_YCBCR_420) \
                                         || ((input_format) == HAL_JPEG_IN_FORMAT_CMYK))

/*! Check whether the value of quality is within the specific range 0-100 */
#define IS_JPEG_IMAGE_QUALITY(number) (((number) >= HAL_JPEG_IMAGE_QUALITY_MIN) \
                                       && ((number) <= HAL_JPEG_IMAGE_QUALITY_MAX))

/*! Check of the input buffer size */
#define IS_IN_DATA_LENGTH_BYTE(length) ((length) >= 4UL)

/*! Check of the output buffer size */
#define IS_OUT_DATA_LENGTH_BYTE(length) ((length) >= 4UL)

/**
  * @}
  */

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Private_Types   JPEG Private Types
  * @{
  */

/*
 JPEG Huffman Table Structure definition :
 This implementation of Huffman table structure is compliant with ISO/IEC 10918-1 standard,
 Annex C Huffman Table specification
 */

/*! JPEG AC DHT marker struct definition */
typedef struct
{
  /* These two fields directly represent the contents of a JPEG DHT marker */
  uint8_t bits[16];        /*!< bits[k] = # of symbols with codes of length k bits,
                                this parameter corresponds to bits list in the Annex C */

  uint8_t huff_val[162];    /*!< The symbols, in order of incremented code length,
                                 this parameter corresponds to huff_val list in the Annex C */
} hal_jpeg_ac_huff_table_t;

/*! JPEG DC DHT marker struct definition */
typedef struct
{
  /* These two fields directly represent the contents of a JPEG DHT marker */
  uint8_t bits[16];        /*!< bits[k] = # of symbols with codes of length k bits,
                                this parameter corresponds to bits list in the Annex C */

  uint8_t huff_val[12];    /*!< The symbols, in order of incremented code length,
                                this parameter corresponds to huff_val list in the Annex C */

} hal_jpeg_dc_huff_table_t;

/*! JPEG AC huffman code struct definition */
typedef struct
{
  uint8_t code_length[JPEG_AC_HUFF_TABLE_SIZE];      /*!< Code length  */

  uint32_t huffman_code[JPEG_AC_HUFF_TABLE_SIZE];    /*!< huffman_code */

} hal_jpeg_ac_huff_code_table_t;

/*! JPEG DC huffman code struct definition */
typedef struct
{
  uint8_t code_length[JPEG_DC_HUFF_TABLE_SIZE];        /*!< Code length  */

  uint32_t huffman_code[JPEG_DC_HUFF_TABLE_SIZE];    /*!< huffman_code */

} hal_jpeg_dc_huff_code_table_t;

/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Private_Configuration_Macros  JPEG Private Configuration Macros
  * @{
  */
/**
  * @brief JPEG get Instance macro
  */
#define JPEG_GET_INSTANCE(handle)  ((JPEG_TypeDef *)((uint32_t)(handle)->instance))

/*! JPEG Enable DMA requests*/
#define JPEG_ENABLE_DMA(handle, dma)  (JPEG_GET_INSTANCE(handle)->CR |= ((dma) & JPEG_DMA_MASK))

#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
/*! note : To disable a DMA request we must use MODIFY_REG macro to avoid writing "1" to the FIFO flush bits
         located in the same DMA request enable register (CR register). */
#define JPEG_DISABLE_DMA(handle, dma) MODIFY_REG(JPEG_GET_INSTANCE(handle)->CR, ((dma) &\
                                                 JPEG_DMA_MASK), 0UL)
#endif /* USE_HAL_JPEG_DMA */
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Private_Variables  JPEG Private Variables
  * @{
  */
/*! JPEG  DC luminance huffman table */
static const hal_jpeg_dc_huff_table_t jpeg_dc_lum_huff_table =
{
  { 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },    /*!< Number of symbols with codes of length k bits
                                                              where k is the position of the symbol in the array */

  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb }             /*!< huff_val : symbols values  */

};
/*! JPEG  DC chrominance huffman table */
static const hal_jpeg_dc_huff_table_t jpeg_dc_chrom_huff_table =
{
  { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },    /*!< Number of symbols with codes of length k bits
                                                              where k is the position of the symbol in the array  */

  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb }             /*!< huff_val : symbols values  */
};

/*! JPEG  AC luminance huffman table */
static const hal_jpeg_ac_huff_table_t jpeg_ac_lum_huff_table =
{
  { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d }, /*!< Number of symbols with codes of length k bits
                                                              where k is the position of the symbol in the array  */
  {
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,      /*!< huff_val : symbols values  */
    0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
    0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
    0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
    0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
    0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
    0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
    0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa
  }
};

/*! JPEG  AC chrominance huffman table */
static const hal_jpeg_ac_huff_table_t jpeg_ac_chrom_huff_table =
{
  { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 }, /*!< Number of symbols with codes of length k bits
                                                              where k is the position of the symbol in the array  */
  {
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,      /*!< huff_val : symbols values  */
    0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
    0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
    0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
    0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
    0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
    0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
    0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
    0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
    0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
    0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa
  }
};

/*! JPEG zigzag order table */
static const uint8_t jpeg_zigzag_order[JPEG_QUANT_TABLE_SIZE] =
{
  0,   1,   8,  16,   9,   2,   3,  10,
  17,  24,  32,  25,  18,  11,   4,   5,
  12,  19,  26,  33,  40,  48,  41,  34,
  27,  20,  13,   6,   7,  14,  21,  28,
  35,  42,  49,  56,  57,  50,  43,  36,
  29,  22,  15,  23,  30,  37,  44,  51,
  58,  59,  52,  45,  38,  31,  39,  46,
  53,  60,  61,  54,  47,  55,  62,  63
};
/**
  * @}
  */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup JPEG_Private_Functions_Prototypes JPEG Private Functions
  * @{
  */
static void JPEG_Bits_To_SizeCodes(const uint8_t *p_bits, uint8_t *p_huff_size, uint32_t *p_huff_code,
                                   uint8_t *p_last_k);
static void JPEG_DCHuff_BitsVals_To_SizeCodes(hal_jpeg_dc_huff_table_t *p_dc_bits_vals_table,
                                              hal_jpeg_dc_huff_code_table_t *p_dc_size_codes_table);
static void JPEG_ACHuff_BitsVals_To_SizeCodes(hal_jpeg_ac_huff_table_t *p_ac_bits_vals_table,
                                              hal_jpeg_ac_huff_code_table_t *p_ac_size_codes_table);
static void JPEG_Set_HuffDC_Mem(const hal_jpeg_handle_t *hjpeg, hal_jpeg_dc_huff_table_t *p_huff_table_dc,
                                const volatile uint32_t *p_dc_table_address);
static void JPEG_Set_HuffAC_Mem(const hal_jpeg_handle_t *hjpeg, hal_jpeg_ac_huff_table_t *p_huff_table_ac,
                                const volatile uint32_t *p_ac_table_address);
static void JPEG_Set_HuffEnc_Mem(hal_jpeg_handle_t *hjpeg);
static void JPEG_Set_Huff_DHTMem(const hal_jpeg_handle_t *hjpeg);
static hal_status_t  JPEG_Set_Quantization_Mem(const uint8_t *p_qtable,
                                               volatile uint32_t *p_qtable_address, uint32_t imgage_quality);
static void JPEG_SetColorYCBCR(hal_jpeg_handle_t *hjpeg, hal_jpeg_input_format_t input_format);
static void JPEG_SetColorGrayScale(hal_jpeg_handle_t *hjpeg);
static void JPEG_SetColorCMYK(hal_jpeg_handle_t *hjpeg);

static void JPEG_Init_Process(hal_jpeg_handle_t *hjpeg);
static uint32_t JPEG_Process(hal_jpeg_handle_t *hjpeg);
static void JPEG_ReadInputData(hal_jpeg_handle_t *hjpeg, uint32_t nb_request_words_byte);
static void JPEG_StoreOutputData(hal_jpeg_handle_t *hjpeg, uint32_t nb_output_words_byte);
static uint32_t JPEG_GetQuality(const hal_jpeg_handle_t *hjpeg);

#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
static hal_status_t JPEG_DMA_StartProcess(hal_jpeg_handle_t *hjpeg);
static void JPEG_DMA_ContinueProcess(hal_jpeg_handle_t *hjpeg);
static void JPEG_DMA_EndProcess(hal_jpeg_handle_t *hjpeg);
static void JPEG_DMA_PollResidualData(hal_jpeg_handle_t *hjpeg);
static void JPEG_DMAOutCpltCallback(hal_dma_handle_t *hdma);
static void JPEG_DMAInCpltCallback(hal_dma_handle_t *hdma);
static void JPEG_DMAErrorCallback(hal_dma_handle_t *hdma);
static void JPEG_DMAOutAbortCallback(hal_dma_handle_t *hdma);
#endif /* USE_HAL_JPEG_DMA */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup JPEG_Exported_Functions
  * @{
  */

/** @addtogroup JPEG_Exported_Functions_Group1 Initialization de-initialization functions
  *  @brief    Initialization and de-initialization functions.
  *
  ==============================================================================
               Initialization and de-initialization functions
  ==============================================================================
      This section provides functions allowing to:
        - HAL_JPEG_Init()  : Initialize the JPEG peripheral and creates the associated handle
        - HAL_JPEG_DeInit(): DeInitialize the JPEG peripheral
  @{
  */

/**
  * @brief  Initialize the HAL JPEG handle and associate instance
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure
  * @param  instance  one of the values of the enumeration @ref hal_jpeg_t
  * @retval HAL_INVALID_PARAM  Invalid parameter when hjpeg pointer is NULL
  * @retval HAL_OK             JPEG instance has been correctly Initialized
  */
hal_status_t HAL_JPEG_Init(hal_jpeg_handle_t *hjpeg, hal_jpeg_t instance)
{
  /*! Quantization tables given in JPEG spec ISO/IEC 10918-1 standard , section K.1. */
  static const uint8_t jpeg_lum_quant_table[JPEG_QUANT_TABLE_SIZE] =
  {
    16,  11,  10,  16,  24,  40,  51,  61,
    12,  12,  14,  19,  26,  58,  60,  55,
    14,  13,  16,  24,  40,  57,  69,  56,
    14,  17,  22,  29,  51,  87,  80,  62,
    18,  22,  37,  56,  68, 109, 103,  77,
    24,  35,  55,  64,  81, 104, 113,  92,
    49,  64,  78,  87, 103, 121, 120, 101,
    72,  92,  95,  98, 112, 100, 103,  99
  };
  static const uint8_t jpeg_chrom_quant_table[JPEG_QUANT_TABLE_SIZE] =
  {
    17,  18,  24,  47,  99,  99,  99,  99,
    18,  21,  26,  66,  99,  99,  99,  99,
    24,  26,  56,  99,  99,  99,  99,  99,
    47,  66,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99
  };
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(IS_JPEG_ALL_INSTANCE((JPEG_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hjpeg == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->instance = instance;

#if defined(USE_HAL_JPEG_CLK_ENABLE_MODEL) && (USE_HAL_JPEG_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_JPEG_EnableClock();
#endif /* USE_HAL_JPEG_CLK_ENABLE_MODEL */

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
  hjpeg->p_info_ready_cb           = HAL_JPEG_InfoReadyCallback;
  hjpeg->p_encode_cplt_cb          = HAL_JPEG_EncodeCpltCallback;
  hjpeg->p_decode_cplt_cb          = HAL_JPEG_DecodeCpltCallback;
  hjpeg->p_error_cb                = HAL_JPEG_ErrorCallback;
  hjpeg->p_get_data_cb             = HAL_JPEG_GetDataCallback;
  hjpeg->p_data_ready_cb           = HAL_JPEG_DataReadyCallback;
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

#if defined(USE_HAL_JPEG_USER_DATA) && (USE_HAL_JPEG_USER_DATA == 1)
  hjpeg->p_user_data = NULL;
#endif /* USE_HAL_JPEG_USER_DATA */

#if defined (USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
  hjpeg->last_error_codes = HAL_JPEG_ERROR_NONE;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

  /* Private fields */
  hjpeg->context = 0;
  hjpeg->p_quant_table0 = (uint8_t *)((uint32_t)jpeg_lum_quant_table);
  hjpeg->p_quant_table1 = (uint8_t *)((uint32_t)jpeg_chrom_quant_table);

  /* Enable Header processing */
  hjpeg->header_processing = HAL_JPEG_HEADER_PROCESSING_ENABLED;

  hjpeg->encode_config_state = HAL_JPEG_ENCODE_CONFIG_STATE_RESET;

  hjpeg->global_state = HAL_JPEG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the JPEG peripheral.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
void HAL_JPEG_DeInit(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(IS_JPEG_ALL_INSTANCE((JPEG_TypeDef *)(uint32_t)hjpeg->instance));

  /* Clear all pending flags */
  HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_ALL);

  /* Disable all interrupts */
  HAL_JPEG_DisableIT(hjpeg, HAL_JPEG_IT_ALL);

  /* Disable the JPEG core */
  CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_CR_JCEN);

  hjpeg->encode_config_state = HAL_JPEG_ENCODE_CONFIG_STATE_RESET;

  hjpeg->global_state = HAL_JPEG_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup JPEG_Exported_Functions_Group2 Encoding/Decoding Configuration functions
  *  @brief    JPEG Configuration functions.
  *
  ==============================================================================
               Configuration functions
  ==============================================================================
      This section provides functions allowing to:
        - HAL_JPEG_SetConfigEncoding()         : JPEG encoding configuration.
        - HAL_JPEG_GetLastDecodeInfo()         : Get the image configuration from the JPEG header during the decoding.
        - HAL_JPEG_EnableHeaderProcessing()    : Enable JPEG Header parsing and generation.
        - HAL_JPEG_DisableHeaderProcessing()   : Disable JPEG Header parsing and generation.
        - HAL_JPEG_SetUserQuantTables1()       : Modify the default Quantization tables_1 used for JPEG encoding.
        - HAL_JPEG_SetUserQuantTables2()       : Modify the default Quantization tables_2 used for JPEG encoding.
        - HAL_JPEG_SetUserQuantTables3()       : Modify the default Quantization tables_3 used for JPEG encoding.
        - HAL_JPEG_SetUserQuantTables4()       : Modify the default Quantization tables_4 used for JPEG encoding.

  * @{
  */

/**
  * @brief  Set the JPEG encoding configuration.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_config Pointer to a hal_jpeg_config_t structure that contains
  *         the encoding configuration.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_config structure pointer is NULL.
  * @retval HAL_ERROR          failed to initialize the default Huffman tables or failed to configure the JPEG Core
                               registers according to the color space.
  * @retval HAL_OK             The configuration of the JPEG Core according to the asserted configuration structure
                               is successfully Done.
  */
hal_status_t HAL_JPEG_SetConfigEncoding(hal_jpeg_handle_t *hjpeg, const hal_jpeg_config_t *p_config)
{
  hal_status_t status ;

  /* The number of MCUs  minus 1 in the JPEG image */
  uint32_t number_mcu;

  /* Number of samples per lines within the MCU */
  uint32_t h_factor ;

  /* Number of samples per columns within MCU */
  uint32_t v_factor ;

  /* The number of MCUs per horizontal lines */
  uint32_t h_mcu;

  /* The number of MCUs per  vertical columns */
  uint32_t v_mcu;

  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_JPEG_IN_FORMAT(p_config->input_format));
  ASSERT_DBG_PARAM(IS_JPEG_IMAGE_QUALITY(p_config->image_quality));

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_CR_JCEN);

  JPEG_Set_HuffEnc_Mem(hjpeg);

  CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_COLORSPACE);

  status  = JPEG_Set_Quantization_Mem(hjpeg->p_quant_table0, (JPEG_GET_INSTANCE(hjpeg)->QMEM0),
                                      p_config->image_quality);

  if (status != HAL_OK)
  {
    return  status;
  }
  else
  {
    switch (p_config->input_format)
    {
      case HAL_JPEG_IN_FORMAT_CMYK:

        JPEG_SetColorCMYK(hjpeg);

        if ((hjpeg->context & JPEG_CONTEXT_CUSTOM_TABLES) != 0UL)
        {
          /* Use the user customized quantization tables, one table per component
          use 4 quantization tables , one for each component */

          (void) JPEG_Set_Quantization_Mem(hjpeg->p_quant_table1, (JPEG_GET_INSTANCE(hjpeg)->QMEM1),
                                           p_config->image_quality);
          (void) JPEG_Set_Quantization_Mem(hjpeg->p_quant_table2, (JPEG_GET_INSTANCE(hjpeg)->QMEM2),
                                           p_config->image_quality);
          (void) JPEG_Set_Quantization_Mem(hjpeg->p_quant_table3, (JPEG_GET_INSTANCE(hjpeg)->QMEM3),
                                           p_config->image_quality);

          SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR5, JPEG_CONFR5_QT_0);
          SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR6, JPEG_CONFR6_QT_1);
          SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR7, JPEG_CONFR7_QT);

          /* Set the number of quantization tables, number of components for scan & the number of color components */
          SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_COLORSPACE | JPEG_CONFR1_NF | JPEG_CONFR1_NS);
        }
        else
        {
          /* One Quantisation table is used for the 4 components
          just set the number of components for scan & the number of color components */
          SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, (JPEG_CONFR1_NF | JPEG_CONFR1_NS));
        }

        break;

      case HAL_JPEG_IN_FORMAT_GRAYSCALE:

        JPEG_SetColorGrayScale(hjpeg);

        break ;

      case HAL_JPEG_IN_FORMAT_YCBCR_444:
      case HAL_JPEG_IN_FORMAT_YCBCR_422:
      case HAL_JPEG_IN_FORMAT_YCBCR_420:

        JPEG_SetColorYCBCR(hjpeg, p_config->input_format);

        (void) JPEG_Set_Quantization_Mem(hjpeg->p_quant_table1, (JPEG_GET_INSTANCE(hjpeg)->QMEM1),
                                         p_config->image_quality);

        if ((hjpeg->context & JPEG_CONTEXT_CUSTOM_TABLES)  != 0UL)
        {
          /* Use user customized quantization tables */
          (void) JPEG_Set_Quantization_Mem(hjpeg->p_quant_table2, (JPEG_GET_INSTANCE(hjpeg)->QMEM2),
                                           p_config->image_quality);
          MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR6, JPEG_CONFR5_QT, JPEG_CONFR6_QT_1);

          /* Three  quantization tables are used one table per component
             set the number of components for scan & the number of color components */
          MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR1, (JPEG_CONFR1_COLORSPACE | JPEG_CONFR1_NF | JPEG_CONFR1_NS),
                     (JPEG_CONFR1_COLORSPACE_1 | JPEG_CONFR1_NF_1 | JPEG_CONFR1_NS_1));
        }
        else
        {
          /* Tow  quantization tables are used, one for Luminance(Y) and one for both Chrominances (Cb & Cr)
             Set the number of components for scan & the number of color components */
          MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR1, (JPEG_CONFR1_COLORSPACE | JPEG_CONFR1_NF | JPEG_CONFR1_NS),
                     (JPEG_CONFR1_COLORSPACE_0 | JPEG_CONFR1_NF_1 | JPEG_CONFR1_NS_1));
        }

        break ;
      default:
        status = HAL_ERROR;
        break ;
    }

    if (status != HAL_OK)
    {
      return  status;
    }
    else
    {
      MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_YSIZE, p_config->image_height << JPEG_CONFR1_YSIZE_Pos);
      MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR3, JPEG_CONFR3_XSIZE, p_config->image_width << JPEG_CONFR3_XSIZE_Pos);

      if (p_config->input_format == HAL_JPEG_IN_FORMAT_YCBCR_420)
      {
        h_factor = 16;
        v_factor = 16;
      }
      else if (p_config->input_format == HAL_JPEG_IN_FORMAT_YCBCR_422)
      {
        h_factor = 16;
        v_factor = 8;
      }
      else
      {
        h_factor = 8;
        v_factor = 8;
      }

      h_mcu = (p_config->image_width / h_factor);
      if ((p_config->image_width % h_factor) != 0UL)
      {
        h_mcu++; /*+1 for horizontal incomplete MCU */
      }

      v_mcu = (p_config->image_height / v_factor);
      if ((p_config->image_height % v_factor) != 0UL)
      {
        v_mcu++; /*+1 for vertical incomplete MCU */
      }
      number_mcu = (h_mcu * v_mcu) - 1UL; /* Bit Field JPEG_CONFR2_NMCU must be set to NB_MCU - 1*/
      WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR2, number_mcu);
      hjpeg->context |= JPEG_CONTEXT_CONF_ENCODING;
      hjpeg->encode_config_state = HAL_JPEG_ENCODE_CONFIG_STATE_CONFIGURED;

      return HAL_OK;
    }
  }
}

/**
  * @brief  Extract the image configuration from the JPEG header during the decoding.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_info Pointer to a hal_jpeg_config_t structure to be filled with
  *         the JPEG decoded header information.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_info structure pointer is NULL.
  * @retval HAL_ERROR          Failed to read the configuration parameters from the JPEG registers.
  * @retval HAL_OK             Extract the image configuration is successfully done.
  */
hal_status_t HAL_JPEG_GetLastDecodeInfo(hal_jpeg_handle_t *hjpeg, hal_jpeg_config_t *p_info)
{
  uint8_t y_block_nb;
  uint8_t cb_block_nb;
  uint8_t cr_block_nb;
  uint32_t nb_color_component;

  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE | (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_info == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get  the CONFR1 register values */
  nb_color_component = READ_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_NF) ;

  switch (nb_color_component)

  {
    case 0UL :
      p_info->input_format = HAL_JPEG_IN_FORMAT_GRAYSCALE ;
      break ;

    case JPEG_CONFR1_NF :
      p_info->input_format = HAL_JPEG_IN_FORMAT_CMYK ;
      break ;

    case JPEG_CONFR1_NF_1 :

      y_block_nb  = (uint8_t)(READ_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR4, JPEG_CONFR4_NB) >> 4);
      cb_block_nb = (uint8_t)(READ_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR5, JPEG_CONFR4_NB) >> 4);
      cr_block_nb = (uint8_t)(READ_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR6, JPEG_CONFR4_NB) >> 4);

      if ((y_block_nb == 1UL) && (cb_block_nb == 0UL) && (cr_block_nb == 0UL))
      {
        p_info->input_format = HAL_JPEG_IN_FORMAT_YCBCR_422;
      }
      else if ((y_block_nb == 0UL) && (cb_block_nb == 0UL) && (cr_block_nb == 0UL))
      {
        p_info->input_format = HAL_JPEG_IN_FORMAT_YCBCR_444;
      }
      else if ((y_block_nb == 3UL) && (cb_block_nb == 0UL) && (cr_block_nb == 0UL))
      {
        p_info->input_format = HAL_JPEG_IN_FORMAT_YCBCR_420;
      }
      else
      {
        return HAL_ERROR ;
      }
      break ;

    default:
      return HAL_ERROR ;
      break;
  }

  /* Get image height & width */
  p_info->image_height = READ_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_YSIZE) >> JPEG_CONFR1_YSIZE_Pos;
  p_info->image_width  = READ_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR3, JPEG_CONFR3_XSIZE) >> JPEG_CONFR3_XSIZE_Pos;

  /* Get image quality */
  p_info->image_quality = JPEG_GetQuality(hjpeg);

  return HAL_OK;
}

/**
  * @brief  Enable JPEG Header parsing and generation.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_INVALID_PARAM  Invalid parameter when hjpeg pointer is NULL.
  * @retval HAL_OK             The header processing is successfully enabled.
  */
hal_status_t HAL_JPEG_EnableHeaderProcessing(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hjpeg == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

  hjpeg ->header_processing = HAL_JPEG_HEADER_PROCESSING_ENABLED ;

  return HAL_OK;
}

/**
  * @brief  Disable JPEG Header parsing and generation.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_INVALID_PARAM  Invalid parameter when hjpeg pointer is NULL.
  * @retval HAL_OK             The header processing is successfully Disabled.
  */
hal_status_t HAL_JPEG_DisableHeaderProcessing(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hjpeg == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

  /* Disable header processing */
  hjpeg ->header_processing = HAL_JPEG_HEADER_PROCESSING_DISABLED ;

  return HAL_OK;
}

/**
  * @brief  Modify the default Quantization tables for color component 1 used for JPEG encoding.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_qtable1  pointer to uint8_t , define the user quantification table for color component 1.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_qtable1 pointer is NULL.
  * @retval HAL_OK             The user quantification table for color component 1 is successfully registered.
  */
hal_status_t  HAL_JPEG_SetUserQuantTables1(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable1)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_qtable1 != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_qtable1 == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->context |= JPEG_CONTEXT_CUSTOM_TABLES;

  hjpeg->p_quant_table0 = p_qtable1;

  return HAL_OK;
}

/**
  * @brief  Modify the default Quantization tables for color component 2 used for JPEG encoding.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_qtable2  Pointer to uint8_t , define the user quantification table for color component 2.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_qtable2 pointer is NULL.
  * @retval HAL_OK             The user quantification table for color component 2 is successfully registered.
  */
hal_status_t  HAL_JPEG_SetUserQuantTables2(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable2)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_qtable2 != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_qtable2 == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->context |= JPEG_CONTEXT_CUSTOM_TABLES;

  hjpeg->p_quant_table1 = p_qtable2;

  return HAL_OK;
}

/**
  * @brief  Modify the default quantization tables for color component 3 used for JPEG encoding.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_qtable3  Pointer to uint8_t , define the user quantification table for color component 3.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_qtable3 pointer is NULL.
  * @retval HAL_OK             The user quantification table for color component 3 is successfully registered.
  */
hal_status_t  HAL_JPEG_SetUserQuantTables3(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable3)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_qtable3 != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_qtable3 == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->context |= JPEG_CONTEXT_CUSTOM_TABLES;
  hjpeg->p_quant_table2 = p_qtable3;

  return HAL_OK;
}

/**
  * @brief  Modify the default quantization tables for color component 4 used for JPEG encoding.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_qtable4  Pointer to uint8_t , define the user quantification table for color component 4.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_qtable4 pointer is NULL.
  * @retval HAL_OK             The user quantification table for color component 4 is successfully registered.
  */
hal_status_t  HAL_JPEG_SetUserQuantTables4(hal_jpeg_handle_t *hjpeg, const uint8_t *p_qtable4)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_qtable4 != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_qtable4 == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->context |= JPEG_CONTEXT_CUSTOM_TABLES;

  hjpeg->p_quant_table3 = p_qtable4;

  return HAL_OK;

}
/**
  * @}
  */

/** @addtogroup JPEG_Exported_Functions_Group3 JPEG processing functions
  *  @brief   processing functions.
  *
  ==============================================================================
                       JPEG processing functions
  ==============================================================================
    This section provides functions allowing to:
      - HAL_JPEG_Encode()             : JPEG encoding with polling process
      - HAL_JPEG_Decode()             : JPEG decoding with polling process
      - HAL_JPEG_Encode_IT()          : JPEG encoding with interrupt process
      - HAL_JPEG_Decode_IT()          : JPEG decoding with interrupt process
      - HAL_JPEG_Encode_DMA()         : JPEG encoding with DMA process
      - HAL_JPEG_Decode_DMA()         : JPEG decoding with DMA process
      - HAL_JPEG_PauseInputBuffer()   : Pause the Input processing
      - HAL_JPEG_PauseOutputBuffer()  : Pause the Output processing
      - HAL_JPEG_ResumeInputBuffer()  : Resume the JPEG Input processing
      - HAL_JPEG_ResumeOutputBuffer() : Resume the JPEG Output processing
      - HAL_JPEG_UpdateInputBuffer()  : Configure Encoding/Decoding Input Buffer
      - HAL_JPEG_UpdateOutputBuffer() : Configure Encoding/Decoding Output Buffer
      - HAL_JPEG_Abort()              : Aborts the JPEG Encoding/Decoding


  * @{
  */

/**
  * @brief  Starts JPEG encoding with polling processing.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  * @param  p_data_in_mcu Pointer to the Input buffer.
  * @param  in_data_length_byte size in bytes of the input buffer.
  * @param  p_data_out Pointer to the jpeg output data buffer.
  * @param  out_data_length_byte size in bytes of the Output buffer.
  * @param  timeout_ms Specify timeout value.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_data_in_mcu/p_data_out pointer is NULL.
  * @retval HAL_TIMEOUT        User timeout
  * @retval HAL_OK             JPEG encoding with. polling processing is successfully completed.
  */
hal_status_t  HAL_JPEG_Encode(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in_mcu, uint32_t in_data_length_byte,
                              uint8_t *p_data_out, uint32_t out_data_length_byte, uint32_t timeout_ms)
{
  uint32_t tick_start;

  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(IS_IN_DATA_LENGTH_BYTE(in_data_length_byte));
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));
  ASSERT_DBG_PARAM(p_data_in_mcu != NULL);
  ASSERT_DBG_PARAM(p_data_out != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);
  ASSERT_DBG_STATE(hjpeg->encode_config_state, (uint32_t)HAL_JPEG_ENCODE_CONFIG_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data_in_mcu == NULL) || (p_data_out == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hjpeg, global_state, HAL_JPEG_STATE_IDLE, HAL_JPEG_STATE_ACTIVE_ENCODE);

  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK);
  hjpeg->context |= (JPEG_CONTEXT_ENCODE | JPEG_CONTEXT_POLLING);

  hjpeg->p_jpeg_in_buff = p_data_in_mcu;
  hjpeg->p_jpeg_out_buff = p_data_out;
  hjpeg->in_data_length_byte = in_data_length_byte - (in_data_length_byte % 4UL); /* Input Data length must be multiple
                                                                                     of 4 Bytes (1 word)*/
  hjpeg->out_data_length_byte = out_data_length_byte - (out_data_length_byte % 4UL); /* Output Data length must be
                                                                                        multiple of 4 Bytes (1 word)*/

  hjpeg->jpeg_in_count_byte = 0;
  hjpeg->jpeg_out_count_byte = 0;

  JPEG_Init_Process(hjpeg);

  tick_start = HAL_GetTick();
  while ((JPEG_Process(hjpeg) == JPEG_PROCESS_ONGOING))
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) > timeout_ms) || (timeout_ms == 0UL))
      {
        hjpeg->global_state = HAL_JPEG_STATE_IDLE;

        return HAL_TIMEOUT;
      }
    }
  }

  hjpeg->global_state = HAL_JPEG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Starts JPEG decoding with polling processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_data_in Pointer to the input data buffer.
  * @param  in_data_length_byte Size in bytes of the Input buffer.
  * @param  p_data_out_mcu Pointer to the Output data buffer.
  * @param  out_data_length_byte Size in bytes of the Output buffer.
  * @param  timeout_ms Specify timeout value.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_data_out_mcu/p_data_in pointer is NULL.
  * @retval HAL_TIMEOUT        User timeout.
  * @retval HAL_OK             JPEG decoding with polling processing is successfully completed.
  */
hal_status_t  HAL_JPEG_Decode(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in, uint32_t in_data_length_byte,
                              uint8_t *p_data_out_mcu, uint32_t out_data_length_byte, uint32_t timeout_ms)
{
  uint32_t tick_start;
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(IS_IN_DATA_LENGTH_BYTE(in_data_length_byte));
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));
  ASSERT_DBG_PARAM(p_data_in != NULL);
  ASSERT_DBG_PARAM(p_data_out_mcu != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data_in == NULL) || (p_data_out_mcu == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hjpeg, global_state, HAL_JPEG_STATE_IDLE, HAL_JPEG_STATE_ACTIVE_DECODE);
  hjpeg->encode_config_state = HAL_JPEG_ENCODE_CONFIG_STATE_RESET;
  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK);
  hjpeg->context |= (JPEG_CONTEXT_DECODE | JPEG_CONTEXT_POLLING);

  hjpeg->p_jpeg_in_buff = p_data_in;
  hjpeg->p_jpeg_out_buff = p_data_out_mcu;
  hjpeg->in_data_length_byte = in_data_length_byte - (in_data_length_byte % 4UL); /* Input Data length must be multiple
                                                                                     of 4 Bytes (1 word) */

  hjpeg->out_data_length_byte = out_data_length_byte - (out_data_length_byte % 4UL); /* Output Data length must be
                                                                                        multiple of 4 Bytes (1 word) */
  hjpeg->jpeg_in_count_byte = 0;
  hjpeg->jpeg_out_count_byte = 0;

  JPEG_Init_Process(hjpeg);
  tick_start = HAL_GetTick();

  while ((JPEG_Process(hjpeg) == JPEG_PROCESS_ONGOING))
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) > timeout_ms) || (timeout_ms == 0UL))
      {
        hjpeg->global_state = HAL_JPEG_STATE_IDLE;
        return HAL_TIMEOUT;
      }
    }
  }
  hjpeg->global_state = HAL_JPEG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Starts JPEG encoding with interrupt processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_data_in_mcu Pointer to the Input buffer.
  * @param  in_data_length_byte size in bytes of the Input buffer.
  * @param  p_data_out Pointer to the jpeg output data buffer.
  * @param  out_data_length_byte Size in bytes of the output buffer.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_data_in_mcu/p_data_out pointer is NULL.
  * @retval HAL_OK             JPEG Encoding with interrupt processing is successfully initialized.
  */
hal_status_t  HAL_JPEG_Encode_IT(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in_mcu, uint32_t in_data_length_byte,
                                 uint8_t *p_data_out, uint32_t out_data_length_byte)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM(IS_IN_DATA_LENGTH_BYTE(in_data_length_byte));
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));
  ASSERT_DBG_PARAM((p_data_in_mcu != NULL));
  ASSERT_DBG_PARAM((p_data_out != NULL));

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);
  ASSERT_DBG_STATE(hjpeg->encode_config_state, (uint32_t)HAL_JPEG_ENCODE_CONFIG_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data_in_mcu == NULL) || (p_data_out == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hjpeg, global_state, HAL_JPEG_STATE_IDLE, HAL_JPEG_STATE_ACTIVE_ENCODE);

  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK);
  hjpeg->context |= (JPEG_CONTEXT_ENCODE | JPEG_CONTEXT_IT);

  hjpeg->p_jpeg_in_buff  = p_data_in_mcu;
  hjpeg->p_jpeg_out_buff = p_data_out;
  hjpeg->in_data_length_byte  = in_data_length_byte - (in_data_length_byte % 4UL); /* Input Data length must be multiple
                                                                                       of 4 Bytes (1 word)*/
  hjpeg->out_data_length_byte = out_data_length_byte - (out_data_length_byte % 4UL); /* Output Data length must be
                                                                                        multiple of 4 Bytes (1 word)*/

  hjpeg->jpeg_in_count_byte = 0;
  hjpeg->jpeg_out_count_byte = 0;

  JPEG_Init_Process(hjpeg);

  return HAL_OK;
}

/**
  * @brief  Starts JPEG decoding with interrupt processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_data_in Pointer to the input data buffer.
  * @param  in_data_length_byte Size in bytes of the Input buffer.
  * @param  p_data_out_mcu Pointer to the Output data buffer.
  * @param  out_data_length_byte Size in bytes of the Output buffer.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_data_out_mcu/p_data_in pointer is NULL.
  * @retval HAL_OK             JPEG decoding with interrupt processing is successfully Initialized.
  */
hal_status_t  HAL_JPEG_Decode_IT(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in, uint32_t in_data_length_byte,
                                 uint8_t *p_data_out_mcu, uint32_t out_data_length_byte)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM(IS_IN_DATA_LENGTH_BYTE(in_data_length_byte));
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));
  ASSERT_DBG_PARAM((p_data_in != NULL));
  ASSERT_DBG_PARAM((p_data_out_mcu != NULL));
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data_out_mcu == NULL) || (p_data_in == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hjpeg, global_state, HAL_JPEG_STATE_IDLE, HAL_JPEG_STATE_ACTIVE_DECODE);

  hjpeg->encode_config_state = HAL_JPEG_ENCODE_CONFIG_STATE_RESET;

  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK);
  hjpeg->context |= (JPEG_CONTEXT_DECODE | JPEG_CONTEXT_IT);

  hjpeg->p_jpeg_in_buff  = p_data_in;
  hjpeg->p_jpeg_out_buff = p_data_out_mcu;
  hjpeg->in_data_length_byte = in_data_length_byte - (in_data_length_byte % 4UL);  /* Input Data length must be multiple
                                                                                      of 4 Bytes (1 word)*/
  hjpeg->out_data_length_byte = out_data_length_byte - (out_data_length_byte % 4UL); /* Output Data length must be
                                                                                        multiple of 4 Bytes (1 word)*/

  hjpeg->jpeg_in_count_byte = 0;
  hjpeg->jpeg_out_count_byte = 0;

  JPEG_Init_Process(hjpeg);

  return HAL_OK;
}

#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
/**
  * @brief  Starts JPEG encoding with DMA processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_data_in_mcu Pointer to the Input buffer.
  * @param  in_data_length_byte Size in bytes of the Input buffer.
  * @param  p_data_out Pointer to the jpeg output data buffer.
  * @param  out_data_length_byte Size in bytes of the Output buffer.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_data_in_mcu/p_data_out/ pointer is NULL or
                               in_data_length_byte/out_data_length_byte < 4 byte.
  * @retval HAL_ERROR          DMA FIFO In/out transfer failed.
  * @retval HAL_OK             JPEG encoding with DMA processing is successfully finished.
  */
hal_status_t  HAL_JPEG_Encode_DMA(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in_mcu,
                                  uint32_t in_data_length_byte, uint8_t *p_data_out, uint32_t out_data_length_byte)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM(IS_IN_DATA_LENGTH_BYTE(in_data_length_byte));
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));
  ASSERT_DBG_PARAM((p_data_in_mcu != NULL));
  ASSERT_DBG_PARAM((p_data_out != NULL));

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);
  ASSERT_DBG_STATE(hjpeg->encode_config_state, (uint32_t)HAL_JPEG_ENCODE_CONFIG_STATE_CONFIGURED);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data_in_mcu == NULL) || (p_data_out == NULL) || (in_data_length_byte < 4UL)
      || (out_data_length_byte < 4UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hjpeg, global_state, HAL_JPEG_STATE_IDLE, HAL_JPEG_STATE_ACTIVE_ENCODE);

#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
  hjpeg->last_error_codes = HAL_JPEG_ERROR_NONE;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK);
  hjpeg->context |= (JPEG_CONTEXT_ENCODE | JPEG_CONTEXT_DMA);
  hjpeg->p_jpeg_in_buff = p_data_in_mcu;
  hjpeg->p_jpeg_out_buff = p_data_out;
  hjpeg->in_data_length_byte = in_data_length_byte;
  hjpeg->out_data_length_byte = out_data_length_byte;

  hjpeg->jpeg_in_count_byte = 0;
  hjpeg->jpeg_out_count_byte = 0;

  JPEG_Init_Process(hjpeg);

  if (JPEG_DMA_StartProcess(hjpeg) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
  * @brief  Starts JPEG decoding with DMA processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_data_in Pointer to the input data buffer.
  * @param  in_data_length_byte Size in bytes of the Input buffer.
  * @param  p_data_out_mcu Pointer to the Output data buffer.
  * @param  out_data_length_byte Size in bytes of the Output buffer.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_data_in/p_data_out_mcu pointer is NULL or
                               in_data_length_byte/out_data_length_byte < 4 byte.
  * @retval HAL_ERROR          DMA FIFO In/out transfer failed.
  * @retval HAL_OK             JPEG decoding with DMA processing is successfully finished.
  */
hal_status_t  HAL_JPEG_Decode_DMA(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_in, uint32_t in_data_length_byte,
                                  uint8_t *p_data_out_mcu, uint32_t out_data_length_byte)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(IS_IN_DATA_LENGTH_BYTE(in_data_length_byte));
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));
  ASSERT_DBG_PARAM(p_data_in != NULL);
  ASSERT_DBG_PARAM(p_data_out_mcu != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data_in == NULL) || (p_data_out_mcu == NULL) || (in_data_length_byte < 4UL)
      || (out_data_length_byte < 4UL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  HAL_CHECK_UPDATE_STATE(hjpeg, global_state, HAL_JPEG_STATE_IDLE, HAL_JPEG_STATE_ACTIVE_DECODE);

#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
  hjpeg->last_error_codes = HAL_JPEG_ERROR_NONE;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

  hjpeg->encode_config_state = HAL_JPEG_ENCODE_CONFIG_STATE_RESET;

  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK);
  hjpeg->context |= (JPEG_CONTEXT_DECODE | JPEG_CONTEXT_DMA);

  hjpeg->p_jpeg_in_buff = p_data_in;
  hjpeg->p_jpeg_out_buff = p_data_out_mcu;
  hjpeg->in_data_length_byte = in_data_length_byte;
  hjpeg->out_data_length_byte = out_data_length_byte;

  hjpeg->jpeg_in_count_byte = 0;
  hjpeg->jpeg_out_count_byte = 0;

  JPEG_Init_Process(hjpeg);

  if (JPEG_DMA_StartProcess(hjpeg) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
  * @brief  link/store Tx HAL DMA handle into the HAL JPEG handle.
  * @param  hjpeg    Pointer to a hal_jpeg_handle_t.
  * @param  hdma Pointer to a hal_dma_handle_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_JPEG_SetTxDMA(hal_jpeg_handle_t *hjpeg, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_RESET | (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the JPEG handle */
  hjpeg->hdma_out = hdma;
  hdma->p_parent  = hjpeg;

  return HAL_OK;
}

/**
  * @brief  link/store Rx HAL DMA handle into the HAL JPEG handle.
  * @param  hjpeg    Pointer to a hal_jpeg_handle_t.
  * @param  hdma     Pointer to a hal_dma_handle_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_JPEG_SetRxDMA(hal_jpeg_handle_t *hjpeg, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_RESET | (uint32_t)HAL_JPEG_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the JPEG handle */
  hjpeg->hdma_in = hdma;
  hdma->p_parent = hjpeg;

  return HAL_OK;
}

#endif /* USE_HAL_JPEG_DMA */
/**
  * @brief  Pause the JPEG input processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_OK  The JPEG input processing is paused.
  */
hal_status_t  HAL_JPEG_PauseInputBuffer(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE);
#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)

  hjpeg->context |= JPEG_CONTEXT_PAUSE_INPUT;
  if ((hjpeg->context & JPEG_CONTEXT_DMA) != 0UL)
  {
    JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_IDMA);
  }
  else
#endif /* USE_HAL_JPEG_DMA */

    if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
    {
      HAL_JPEG_DisableIT(hjpeg, (HAL_JPEG_IT_IFT | HAL_JPEG_IT_IFNF));
    }
    else
    {
      /* Nothing to do */
    }
  return HAL_OK;
}

/**
  * @brief  Pause the JPEG output processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_OK  The JPEG output processing is paused.
  */
hal_status_t  HAL_JPEG_PauseOutputBuffer(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE);

  hjpeg->context |= JPEG_CONTEXT_PAUSE_OUTPUT;
#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)

  if ((hjpeg->context & JPEG_CONTEXT_DMA) != 0UL)
  {
    JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_ODMA);
  }
  else
#endif /* USE_HAL_JPEG_DMA */

    if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
    {
      HAL_JPEG_DisableIT(hjpeg, (HAL_JPEG_IT_OFT | HAL_JPEG_IT_OFNE | HAL_JPEG_IT_EOC));
    }
    else
    {
      /* Nothing to do */
    }
  return HAL_OK;
}

/**
  * @brief  Resume the JPEG input processing.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_ERROR  The JPEG input processing is not paused or the DMA FIFO In transfer failed.
  * @retval HAL_OK     The JPEG input processing is Resumed.

  */
hal_status_t  HAL_JPEG_ResumeInputBuffer(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE);

  if ((hjpeg->context & (JPEG_CONTEXT_PAUSE_INPUT)) == 0UL)
  {
    return HAL_ERROR;
  }

  hjpeg->context &= (~JPEG_CONTEXT_PAUSE_INPUT);

#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)

  if ((hjpeg->context & JPEG_CONTEXT_DMA) != 0UL)
  {

    /*JPEG Input DMA transfer data number must be multiple of DMA buffer size
      as the destination is a 32 bits register */
    hjpeg->in_data_length_byte = hjpeg->in_data_length_byte - (hjpeg->in_data_length_byte % 4UL);

    if (hjpeg->in_data_length_byte > 0UL)
    {
      if (HAL_DMA_StartPeriphXfer_IT_Opt(hjpeg->hdma_in, (uint32_t)hjpeg->p_jpeg_in_buff,
                                         (uint32_t)&JPEG_GET_INSTANCE(hjpeg)->DIR,
                                         hjpeg->in_data_length_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
      {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
        hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */
        return HAL_ERROR;
      }
    }
    JPEG_ENABLE_DMA(hjpeg, JPEG_DMA_IDMA);
  }
  else
#endif /* USE_HAL_JPEG_DMA */

    if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
    {
      HAL_JPEG_EnableIT(hjpeg, (HAL_JPEG_IT_IFT | HAL_JPEG_IT_IFNF));
    }
    else
    {
      /* Nothing to do */
    }

  return HAL_OK;
}

/**
  * @brief  Resume the JPEG output processing.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_ERROR  The JPEG output processing is not paused or the DMA FIFO Out transfer failed.
  * @retval HAL_OK     The JPEG output processing is Resumed.
  */
hal_status_t  HAL_JPEG_ResumeOutputBuffer(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE);

  if ((hjpeg->context & (JPEG_CONTEXT_PAUSE_OUTPUT)) == 0UL)
  {
    return HAL_ERROR;
  }

  hjpeg->context &= (~JPEG_CONTEXT_PAUSE_OUTPUT);

#if defined (USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)

  if ((hjpeg->context & JPEG_CONTEXT_DMA) != 0UL)
  {
    if ((hjpeg->context & JPEG_CONTEXT_ENDING_DMA) != 0UL)
    {
      JPEG_DMA_PollResidualData(hjpeg);
    }
    else
    {

      if (HAL_DMA_StartPeriphXfer_IT_Opt(hjpeg->hdma_out, (uint32_t)&JPEG_GET_INSTANCE(hjpeg)->DOR,
                                         (uint32_t)hjpeg->p_jpeg_out_buff,
                                         hjpeg->out_data_length_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
      {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
        hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */
        return HAL_ERROR;
      }
    }
    JPEG_ENABLE_DMA(hjpeg, JPEG_DMA_ODMA);
  }
  else
#endif /* USE_HAL_JPEG_DMA */

    if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
    {
      HAL_JPEG_EnableIT(hjpeg, (HAL_JPEG_IT_OFT | HAL_JPEG_IT_OFNE | HAL_JPEG_IT_EOC));
    }
    else
    {
      /* Nothing to do */
    }

  return HAL_OK;
}

/**
  * @brief  Configure encoding/decoding input buffer.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_new_input_buffer Pointer to the new input data buffer.
  * @param  in_data_length_byte Size in bytes of the new Input data buffer.
  * @retval HAL_OK  The encoding/decoding input buffer is successfully updated.
  */
hal_status_t HAL_JPEG_UpdateInputBuffer(hal_jpeg_handle_t *hjpeg, const uint8_t *p_new_input_buffer,
                                        uint32_t in_data_length_byte)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_new_input_buffer != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE);

  hjpeg->p_jpeg_in_buff =  p_new_input_buffer;
  hjpeg->in_data_length_byte = in_data_length_byte;

  return HAL_OK;
}

/**
  * @brief  Configure encoding/decoding output Buffer.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_new_output_buffer Pointer to the new output data buffer.
  * @param  out_data_length_byte Size in bytes of the new Output data buffer.
  * @retval HAL_OK  The encoding/decoding output buffer is successfully updated.
  */

hal_status_t HAL_JPEG_UpdateOutputBuffer(hal_jpeg_handle_t *hjpeg, uint8_t *p_new_output_buffer,
                                         uint32_t out_data_length_byte)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  ASSERT_DBG_PARAM(p_new_output_buffer != NULL);
  ASSERT_DBG_PARAM(IS_OUT_DATA_LENGTH_BYTE(out_data_length_byte));

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE);

  hjpeg->p_jpeg_out_buff = p_new_output_buffer;
  hjpeg->out_data_length_byte = out_data_length_byte;

  return HAL_OK;
}

/**
  * @brief  Aborts the JPEG Encoding/Decoding.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_ERROR  The JPEG Codec not yet disabled when JPEG_TIMEOUT_VALUE reached.
  * @retval HAL_OK     The JPEG encoding/decoding operation is successfully Aborted.
  */
hal_status_t HAL_JPEG_Abort(hal_jpeg_handle_t *hjpeg)
{
  uint32_t tick_start;

  ASSERT_DBG_PARAM(hjpeg != NULL);

  ASSERT_DBG_STATE(hjpeg->global_state, (uint32_t)HAL_JPEG_STATE_ACTIVE_DECODE
                   | (uint32_t)HAL_JPEG_STATE_ACTIVE_ENCODE);


#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
  uint32_t tmp_context;
  tmp_context = hjpeg->context;
#endif /* USE_HAL_JPEG_DMA */

  hjpeg->context &= ~(JPEG_CONTEXT_OPERATION_MASK | JPEG_CONTEXT_METHOD_MASK | JPEG_CONTEXT_ENDING_DMA);

#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
  if ((tmp_context & JPEG_CONTEXT_DMA) != 0UL)
  {
    if (HAL_DMA_Abort_IT(hjpeg->hdma_out) != HAL_OK)
    {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
      hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */
    }

    if (HAL_DMA_Abort_IT(hjpeg->hdma_in) != HAL_OK)
    {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
      hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */
    }
  }
#endif /* USE_HAL_JPEG_DMA */
  CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);

  tick_start = HAL_GetTick();

  while (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_CO) != 0UL)
  {
    if ((HAL_GetTick() - tick_start) > JPEG_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
  /* Disable interrupts , DMA , flush Input & output FIFO */
  MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_INTERRUPT_MASK | JPEG_DMA_MASK, JPEG_CR_IFF | JPEG_CR_OFF);
#else  /* USE_HAL_JPEG_DMA */
  /* Disable interrupts , flush Input & output FIFO */
  MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_INTERRUPT_MASK, JPEG_CR_IFF | JPEG_CR_OFF);
#endif /* USE_HAL_JPEG_DMA */

  HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_ALL);

  hjpeg->jpeg_in_count_byte = 0U;
  hjpeg->jpeg_out_count_byte = 0U;
  hjpeg->context &= ~(JPEG_CONTEXT_PAUSE_INPUT | JPEG_CONTEXT_PAUSE_OUTPUT);
  hjpeg->global_state = HAL_JPEG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup JPEG_Exported_Functions_Group4 JPEG Decode/Encode callback functions
  *  @brief   JPEG process callback functions.
  *

  ==============================================================================
                JPEG Decode and Encode callback functions
  ==============================================================================
      This section provides callback functions:
        - HAL_JPEG_InfoReadyCallback()  : Decoding JPEG Info ready callback
        - HAL_JPEG_EncodeCpltCallback() : Encoding complete callback.
        - HAL_JPEG_DecodeCpltCallback() : Decoding complete callback.
        - HAL_JPEG_ErrorCallback()      : JPEG error callback.
        - HAL_JPEG_GetDataCallback()    : Get New Data chunk callback.
        - HAL_JPEG_DataReadyCallback()  : Decoded/Encoded Data ready  callback.

  * @{
  */

/**
  * @brief  Decoding JPEG Info ready callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  */
__WEAK void HAL_JPEG_InfoReadyCallback(hal_jpeg_handle_t *hjpeg)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hjpeg);

  /* Warning : This function must not be modified; when the callback is needed,
   *           the HAL_JPEG_InfoReadyCallback() can be implemented in the user file
   */
}

/**
  * @brief  Encoding complete callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  */
__WEAK void HAL_JPEG_EncodeCpltCallback(hal_jpeg_handle_t *hjpeg)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hjpeg);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_JPEG_EncodeCpltCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Decoding complete callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  */
__WEAK void HAL_JPEG_DecodeCpltCallback(hal_jpeg_handle_t *hjpeg)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hjpeg);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_JPEG_DecodeCpltCallback() can be implemented in the user file.
   */
}

/**
  * @brief  JPEG error callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  */
__WEAK void HAL_JPEG_ErrorCallback(hal_jpeg_handle_t *hjpeg)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hjpeg);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_JPEG_ErrorCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Get New Data chunk callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  * @param  nb_decoded_data_byte Number of consumed data in the previous chunk in bytes.
  */
__WEAK void HAL_JPEG_GetDataCallback(hal_jpeg_handle_t *hjpeg, uint32_t nb_decoded_data_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hjpeg);
  STM32_UNUSED(nb_decoded_data_byte);

  /* Warning : This function must not be modified, when the callback is needed,
   *           the HAL_JPEG_GetDataCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Decoded/Encoded Data ready  callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure
  * @param  p_data_out pointer to the output data buffer.
  * @param  out_data_length_byte number in bytes of data available in the specified output buffer.
  */
__WEAK void HAL_JPEG_DataReadyCallback(hal_jpeg_handle_t *hjpeg, const uint8_t *p_data_out,
                                       uint32_t out_data_length_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hjpeg);
  STM32_UNUSED(p_data_out);
  STM32_UNUSED(out_data_length_byte);

  /* Warning : This function must not be modified; when the callback is needed,
   *           the HAL_JPEG_DataReadyCallback() can be implemented in the user file
   */
}

/**
  * @}
  */


/** @addtogroup JPEG_Exported_Functions_Group5 JPEG IRQ handler management and callbacks functions registration
  *  @brief   JPEG IRQ handler.
  *
  ==============================================================================
                  JPEG IRQ handler management
  ==============================================================================
      This section provides JPEG IRQ handler function :
      - HAL_JPEG_IRQHandler()  : handles JPEG interrupt request
      - HAL_JPEG_RegisterInfoReadyCallback()  : handles JPEG interrupt request.
      - HAL_JPEG_RegisterGetDataCallback()    : handles JPEG interrupt request.
      - HAL_JPEG_RegisterDataReadyCallback()  : handles JPEG interrupt request.
      - HAL_JPEG_RegisterEncodeCpltCallback() : handles JPEG interrupt request.
      - HAL_JPEG_RegisterDecodeCpltCallback() : handles JPEG interrupt request.
      - HAL_JPEG_RegisterErrorCallback()      : handles JPEG interrupt request.

  * @{
  */

/**
  * @brief  This function handles JPEG interrupt request.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
void HAL_JPEG_IRQHandler(hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

  if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
  {
    (void) JPEG_Process(hjpeg);
  }
#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
  else if ((hjpeg->context & JPEG_CONTEXT_DMA) != 0UL)
  {
    JPEG_DMA_ContinueProcess(hjpeg);
  }
  else
  {
    /* Nothing to do */
  }
#endif /* USE_HAL_JPEG_DMA */
}


#if (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register Encode Complete JPEG Callback.
  *         To be used instead of the weak HAL_JPEG_RegisterEncodeCpltCallback() predefined callback.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  callback pointer to the Encode Complete Callback function.
  * @retval HAL_INVALID_PARAM  Invalid parameter when callback pointer is NULL.
  * @retval HAL_OK             JPEG Encode Complete Callback is successfully registered.
 */
hal_status_t HAL_JPEG_RegisterEncodeCpltCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback)
{

  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->p_encode_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register Decode Complete JPEG Callback.
  *         To be used instead of the weak HAL_JPEG_RegisterDecodeCpltCallback() predefined callback.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  callback Pointer to the Decode Complete Callback function.
  * @retval HAL_INVALID_PARAM  Invalid parameter when callback pointer is NULL.
  * @retval HAL_OK             JPEG Decode Complete Callback is successfully registered.
  */
hal_status_t HAL_JPEG_RegisterDecodeCpltCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->p_decode_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register Error JPEG Callback.
  *         To be used instead of the weak HAL_JPEG_RegisterErrorCallback() predefined callback.
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure.
  * @param  callback Pointer to the Error JPEG Callback function.
  * @retval HAL_INVALID_PARAM  Invalid parameter when callback pointer is NULL.
  * @retval HAL_OK             JPEG Error Callback is successfully registered.
  */
hal_status_t HAL_JPEG_RegisterErrorCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->p_error_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register Info Ready JPEG Callback.
  *         To be used instead of the weak HAL_JPEG_InfoReadyCallback() predefined callback.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  callback Pointer to the Info Ready Callback function.
  * @retval HAL_INVALID_PARAM  Invalid parameter when callback pointer is NULL.
  * @retval HAL_OK             JPEG Info Ready Callback is successfully registered.
  */
hal_status_t HAL_JPEG_RegisterInfoReadyCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_cb_t callback)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->p_info_ready_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register Get Data JPEG Callback.
  *         To be used instead of the weak HAL_JPEG_GetDataCallback() predefined callback.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  callback Pointer to the Get Data Callback function.
  * @retval HAL_INVALID_PARAM  Invalid parameter when callback pointer is NULL.
  * @retval HAL_OK             JPEG Get Data Callback is successfully registered.
  */
hal_status_t HAL_JPEG_RegisterGetDataCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_get_data_cb_t callback)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->p_get_data_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Register Data Ready JPEG Callback.
  *         To be used instead of the weak HAL_JPEG_DataReadyCallback() predefined callback.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  callback Pointer to the Data Ready Callback function.
  * @retval HAL_INVALID_PARAM  Invalid parameter when callback pointer is NULL.
  * @retval HAL_OK             JPEG Data Ready Callback is successfully registered.
  */
hal_status_t HAL_JPEG_RegisterDataReadyCallback(hal_jpeg_handle_t *hjpeg, hal_jpeg_data_ready_cb_t callback)
{
  ASSERT_DBG_PARAM((hjpeg != NULL));
  ASSERT_DBG_PARAM((callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hjpeg->p_data_ready_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

/**
  * @}
  */
/** @addtogroup JPEG_Exported_Functions_Group6 Peripheral State and Error functions
  *
  *
  ==============================================================================
                    Peripheral global_state and Error functions
  ==============================================================================
        This section provides JPEG global_state and Errors function :
           - HAL_JPEG_GetState()           : permits to get in run-time the JPEG global_state.
           - HAL_JPEG_GetEncoderState()    : permits to get in run-time the JPEG global_state.
           - HAL_JPEG_GetLastErrorCodes()  : Returns last occurred error code.

  * @{
  */

/**
  * @brief  Returns the JPEG global_state.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval hal_jpeg_state_t , value can be one of the following :
  *                    - HAL_JPEG_STATE_RESET
  *                    - HAL_JPEG_STATE_IDLE
  *                    - HAL_JPEG_STATE_ACTIVE_DECODE
  *                    - HAL_JPEG_STATE_ACTIVE_ENCODE
  */
hal_jpeg_state_t HAL_JPEG_GetState(const hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

  return hjpeg->global_state;
}

/**
  * @brief  Returns the JPEG encoder state.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval hal_jpeg_encode_config_state_t , value can be one of the following:
  *                    - HAL_JPEG_ENCODE_CONFIG_STATE_RESET
  *                    - HAL_JPEG_ENCODE_CONFIG_STATE_CONFIGURED
  */
hal_jpeg_encode_config_state_t HAL_JPEG_GetEncoderState(const hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

  return hjpeg->encode_config_state;
}

/** @brief  Return the JPEG error code.
  * @param  hjpeg  Pointer to a hal_jpeg_handle_t structure.
  * @retval JPEG last Error Code.
  */
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
uint32_t HAL_JPEG_GetLastErrorCodes(const hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

  return (hjpeg->last_error_codes);
}
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */
/**
  * @}
  */

/** @addtogroup JPEG_Exported_Functions_Group7  Set/Get user data functions
  *
  ==============================================================================
                     Set/Get user data functions
  ==============================================================================
        This section provides JPEG global_state and Errors function :
           - HAL_JPEG_SetUserData()  : permits to Store the user data into the JPEG handle.
           - HAL_JPEG_GetUserData()  : permits to get the user data from the JPEG handle.
  * @{
  */

#if defined(USE_HAL_JPEG_USER_DATA) && (USE_HAL_JPEG_USER_DATA == 1)
/**
  * @brief Store the user data into the JPEG handle.
  * @param hjpeg  Pointer to a hal_jpeg_handle_t structure.
  * @param p_user_data  Pointer to the user data.
  */
void HAL_JPEG_SetUserData(hal_jpeg_handle_t *hjpeg, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);
  hjpeg->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the JPEG handle.
  * @param  hjpeg  Pointer to a hal_jpeg_handle_t structure.
  * @retval the internal handle user data.
  */
const void *HAL_JPEG_GetUserData(const hal_jpeg_handle_t *hjpeg)
{
  ASSERT_DBG_PARAM(hjpeg != NULL);

  return (hjpeg->p_user_data);
}
#endif /* USE_HAL_JPEG_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup JPEG_Private_Functions_Prototypes JPEG Private Functions
  * @{
  */

/**
  * @brief  Generates Huffman sizes/Codes Table from bits/vals Table.
  * @param  p_bits Pointer to bits table.
  * @param  p_huff_size Pointer to sizes table.
  * @param  p_huff_code Pointer to codes table.
  * @param  p_last_k pointer to last Coeff (table dimension).
  */
static void JPEG_Bits_To_SizeCodes(const uint8_t *p_bits, uint8_t *p_huff_size, uint32_t *p_huff_code,
                                   uint8_t *p_last_k)
{
  uint32_t i;
  uint32_t j;
  uint32_t k;
  uint32_t code;
  uint32_t si;

  /* Figure C.1: Generation of table of Huffman code sizes */
  j = 0;
  for (k = 0; k < 16UL; k++)
  {
    i = (uint32_t)p_bits[k];

    while (i != 0UL)
    {
      p_huff_size[j] = (uint8_t)k + 1U;
      j++;
      i--;
    }
  }
  p_huff_size[j] = 0;
  *p_last_k = (uint8_t)j;

  /* Figure C.2: Generation of table of Huffman codes */
  code = 0;
  si = p_huff_size[0];
  j = 0;
  while (p_huff_size[j] != 0U)
  {
    while (((uint32_t) p_huff_size[j]) == si)
    {
      p_huff_code[j] = code;
      j++;
      code++;
    }

    code <<= 1;
    si++;
  }
}

/**
  * @brief  Transform a bits/Vals AC Huffman table to sizes/Codes huffman Table
  *         that can programmed to the JPEG encoder registers.
  * @param  p_ac_bits_vals_table Pointer to AC huffman bits/vals table.
  * @param  p_ac_size_codes_table Pointer to AC huffman Sizes/Codes table.
  */
static void JPEG_ACHuff_BitsVals_To_SizeCodes(hal_jpeg_ac_huff_table_t *p_ac_bits_vals_table,
                                              hal_jpeg_ac_huff_code_table_t *p_ac_size_codes_table)
{
  uint8_t k;
  uint8_t i;
  uint8_t lsb;
  uint8_t msb;
  uint8_t last_k;
  uint8_t huff_size[257];
  uint32_t huff_code[257] = {0};

  JPEG_Bits_To_SizeCodes(p_ac_bits_vals_table->bits, huff_size, huff_code, &last_k);

  /* Figure C.3: Ordering procedure for encoding procedure code tables */
  k = 0;

  while (k < last_k)
  {
    i = p_ac_bits_vals_table->huff_val[k];
    if (i == 0U)
    {
      i = JPEG_AC_HUFF_TABLE_SIZE - 2U; /*i = 0x00 EOB code*/
    }
    else if (i == 0xF0U) /* i = 0xF0 ZRL code*/
    {
      i = JPEG_AC_HUFF_TABLE_SIZE - 1U;
    }
    else
    {
      msb = (i & 0xF0U) >> 4;
      lsb = (i & 0x0FU);
      i = (msb * 10U) + lsb - 1U;
    }
    p_ac_size_codes_table->huffman_code[i] = huff_code[k];
    p_ac_size_codes_table->code_length[i] = huff_size[k] - 1U;
    k++;
  }
}

/**
  * @brief  Transform a bits/Vals DC Huffman table to sizes/Codes huffman Table
  *         that can programmed to the JPEG encoder registers.
  * @param  p_dc_bits_vals_table Pointer to DC huffman bits/vals table.
  * @param  p_dc_size_codes_table Pointer to DC huffman Sizes/Codes table.
  */
static void JPEG_DCHuff_BitsVals_To_SizeCodes(hal_jpeg_dc_huff_table_t *p_dc_bits_vals_table,
                                              hal_jpeg_dc_huff_code_table_t *p_dc_size_codes_table)
{
  uint8_t k;
  uint8_t i;
  uint8_t last_k;
  uint8_t huff_size[257];
  uint32_t huff_code[257] = {0};

  JPEG_Bits_To_SizeCodes(p_dc_bits_vals_table->bits, huff_size, huff_code, &last_k);

  /* Figure C.3: ordering procedure for encoding procedure code tables */
  k = 0;

  while (k < last_k)
  {
    i = p_dc_bits_vals_table->huff_val[k];
    p_dc_size_codes_table->huffman_code[i] = huff_code[k];
    p_dc_size_codes_table->code_length[i]  = huff_size[k] - 1U;
    k++;
  }
}

/**
  * @brief  Set the JPEG register with an DC huffman table at the given DC table address.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_huff_table_dc Pointer to DC huffman table.
  * @param  p_dc_table_address Encoder DC huffman table address it could be HUFFENC_DC0 or HUFFENC_DC1.
  */
static void  JPEG_Set_HuffDC_Mem(const hal_jpeg_handle_t *hjpeg, hal_jpeg_dc_huff_table_t *p_huff_table_dc,
                                 const volatile uint32_t *p_dc_table_address)
{
  uint32_t i;
  uint32_t lsb;
  uint32_t msb;
  volatile uint32_t *p_address;
  volatile uint32_t *p_address_def;
  hal_jpeg_dc_huff_code_table_t dc_size_codes_table = { {0}, {0} };

  if (p_dc_table_address == (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_DC0))
  {
    p_address = (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_DC0 + (JPEG_DC_HUFF_TABLE_SIZE >> 1));
  }
  else /* p_dc_table_address == (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_DC1) */
  {
    p_address = (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_DC1 + (JPEG_DC_HUFF_TABLE_SIZE >> 1));
  }

  JPEG_DCHuff_BitsVals_To_SizeCodes(p_huff_table_dc, &dc_size_codes_table);
  p_address_def = p_address;
  *p_address_def = 0x0FFF0FFF;
  p_address_def++;
  *p_address_def = 0x0FFF0FFF;

  i = JPEG_DC_HUFF_TABLE_SIZE;
  while (i > 1UL)
  {
    i--;
    p_address --;
    msb = ((uint32_t)(((uint32_t)dc_size_codes_table.code_length[i] & 0xFU) << 8)) |
          ((uint32_t)dc_size_codes_table.huffman_code[i] & 0xFFUL);
    i--;
    lsb = ((uint32_t)(((uint32_t)dc_size_codes_table.code_length[i] & 0xFU) << 8)) |
          ((uint32_t)dc_size_codes_table.huffman_code[i] & 0xFFUL);

    *p_address = lsb | (msb << 16);
  }
}

/**
  * @brief  Set the JPEG register with an AC huffman table at the given AC table address.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  p_huff_table_ac Pointer to AC huffman table.
  * @param  p_ac_table_adress Encoder AC huffman table address it could be HUFFENC_AC0 or HUFFENC_AC1.
  */
static void JPEG_Set_HuffAC_Mem(const hal_jpeg_handle_t *hjpeg, hal_jpeg_ac_huff_table_t *p_huff_table_ac,
                                const volatile uint32_t *p_ac_table_adress)
{
  hal_jpeg_ac_huff_code_table_t acSizeCodesTable;
  uint32_t i;
  uint32_t lsb;
  uint32_t msb;
  volatile uint32_t *p_address;
  volatile uint32_t *p_address_def;

  if (p_ac_table_adress == (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_AC0))
  {
    p_address = (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_AC0 + (JPEG_AC_HUFF_TABLE_SIZE >> 1));
  }
  else  /* p_ac_table_adress == (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_AC1) */
  {
    p_address = (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_AC1 + (JPEG_AC_HUFF_TABLE_SIZE >> 1));
  }

  JPEG_ACHuff_BitsVals_To_SizeCodes(p_huff_table_ac, &acSizeCodesTable);

  /* Default values settings: 162:167 FFFh , 168:175 FD0h_FD7h */
  /* Locations 162:175 of each AC table contain information used internally by the core */

  p_address_def = p_address;
  for (i = 0; i < 3UL; i++)
  {
    *p_address_def = 0x0FFF0FFF;
    p_address_def++;
  }
  *p_address_def = 0x0FD10FD0;
  p_address_def++;
  *p_address_def = 0x0FD30FD2;
  p_address_def++;
  *p_address_def = 0x0FD50FD4;
  p_address_def++;
  *p_address_def = 0x0FD70FD6;
  /* end of Locations 162:175  */

  i = JPEG_AC_HUFF_TABLE_SIZE;
  while (i > 1UL)
  {
    i--;
    p_address--;
    msb = ((uint32_t)(((uint32_t)acSizeCodesTable.code_length[i] & 0xFU) << 8)) |
          ((uint32_t)acSizeCodesTable.huffman_code[i] & 0xFFUL);
    i--;
    lsb = ((uint32_t)(((uint32_t)acSizeCodesTable.code_length[i] & 0xFU) << 8)) |
          ((uint32_t)acSizeCodesTable.huffman_code[i] & 0xFFUL);

    *p_address = lsb | (msb << 16);
  }
}

/**
  * @brief  Configure the JPEG encoder register huffman tables to used during
  *         the encdoing operation.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure
  */
static void JPEG_Set_HuffEnc_Mem(hal_jpeg_handle_t *hjpeg)
{
  JPEG_Set_Huff_DHTMem(hjpeg);
  JPEG_Set_HuffAC_Mem(hjpeg, (hal_jpeg_ac_huff_table_t *)(uint32_t)&jpeg_ac_lum_huff_table,
                      (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_AC0));

  JPEG_Set_HuffAC_Mem(hjpeg, (hal_jpeg_ac_huff_table_t *)(uint32_t)&jpeg_ac_chrom_huff_table,
                      (JPEG_GET_INSTANCE(hjpeg)->HUFFENC_AC1));

  JPEG_Set_HuffDC_Mem(hjpeg, (hal_jpeg_dc_huff_table_t *)(uint32_t)&jpeg_dc_lum_huff_table,
                      JPEG_GET_INSTANCE(hjpeg)->HUFFENC_DC0);

  JPEG_Set_HuffDC_Mem(hjpeg, (hal_jpeg_dc_huff_table_t *)(uint32_t)&jpeg_dc_chrom_huff_table,
                      JPEG_GET_INSTANCE(hjpeg)->HUFFENC_DC1);
}

/**
  * @brief  Configure the JPEG register huffman tables to be included in the JPEG
  *         file header (used for encoding only)
  * @param  hjpeg pointer to a hal_jpeg_handle_t structure
  */
static void JPEG_Set_Huff_DHTMem(const hal_jpeg_handle_t *hjpeg)
{
  hal_jpeg_ac_huff_table_t *p_huff_table_ac0 = (hal_jpeg_ac_huff_table_t *)(uint32_t)&jpeg_ac_lum_huff_table;
  hal_jpeg_ac_huff_table_t *p_huff_table_ac1 = (hal_jpeg_ac_huff_table_t *)(uint32_t)&jpeg_ac_chrom_huff_table;
  hal_jpeg_dc_huff_table_t *p_huff_table_dc0 = (hal_jpeg_dc_huff_table_t *)(uint32_t)&jpeg_dc_lum_huff_table;
  hal_jpeg_dc_huff_table_t *p_huff_table_dc1 = (hal_jpeg_dc_huff_table_t *)(uint32_t)&jpeg_dc_chrom_huff_table;

  uint32_t value;
  uint32_t index;
  volatile uint32_t *p_address;

  /* DC0 Huffman Table : bits*/
  /* DC0 bits is a 16 Bytes table i.e 4x32bits words from DHTMEM base address to DHTMEM + 3 */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 3);
  index = 16;
  while (index > 3UL)
  {

    *p_address = (((uint32_t)p_huff_table_dc0->bits[index - 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_dc0->bits[index - 2UL] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_dc0->bits[index - 3UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_dc0->bits[index - 4UL] & 0xFFUL);
    p_address--;
    index -= 4UL;

  }
  /* DC0 Huffman Table : Val */
  /* DC0 VALS is a 12 Bytes table i.e 3x32bits words from DHTMEM base address +4 to DHTMEM + 6 */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 6);
  index = 12;
  while (index > 3UL)
  {
    *p_address = (((uint32_t)p_huff_table_dc0->huff_val[index - 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_dc0->huff_val[index - 2UL] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_dc0->huff_val[index - 3UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_dc0->huff_val[index - 4UL] & 0xFFUL);
    p_address--;
    index -= 4UL;
  }

  /* AC0 Huffman Table : bits */
  /* AC0 bits is a 16 Bytes table i.e 4x32bits words from DHTMEM base address + 7 to DHTMEM + 10 */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 10UL);
  index = 16;
  while (index > 3UL)
  {

    *p_address = (((uint32_t)p_huff_table_ac0->bits[index - 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_ac0->bits[index - 2UL] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_ac0->bits[index - 3UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_ac0->bits[index - 4UL] & 0xFFUL);
    p_address--;
    index -= 4UL;

  }
  /* AC0 Huffman Table : Val */
  /* AC0 VALS is a 162 Bytes table i.e 41x32bits words from DHTMEM base address + 11 to DHTMEM + 51 */
  /* only Byte 0 and Byte 1 of the last word (@ DHTMEM + 51) belong to AC0 VALS table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 51);
  value = *p_address & 0xFFFF0000U;
  value = value | (((uint32_t)p_huff_table_ac0->huff_val[161] & 0xFFUL) << 8) |
          ((uint32_t)p_huff_table_ac0->huff_val[160] & 0xFFUL);
  *p_address = value;

  /*continue setting 160 AC0 huffman values */
  p_address--; /* address = JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 50 */
  index = JPEG_AC_HUFF_TABLE_SIZE - 2UL;
  while (index > 3UL)
  {
    *p_address = (((uint32_t)p_huff_table_ac0->huff_val[index - 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_ac0->huff_val[index - 2UL] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_ac0->huff_val[index - 3UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_ac0->huff_val[index - 4UL] & 0xFFUL);
    p_address--;
    index -= 4UL;
  }

  /* DC1 Huffman Table : bits */
  /* DC1 bits is a 16 Bytes table i.e 4x32bits words from DHTMEM + 51 base address to DHTMEM + 55 */
  /* only Byte 2 and Byte 3 of the first word (@ DHTMEM + 51) belong to DC1 bits table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 51);
  value = *p_address & 0x0000FFFFU;
  value = value | (((uint32_t)p_huff_table_dc1->bits[1] & 0xFFUL) << 24) |
          (((uint32_t)p_huff_table_dc1->bits[0] & 0xFFUL) << 16);
  *p_address = value;

  /* only Byte 0 and Byte 1 of the last word (@ DHTMEM + 55) belong to DC1 bits table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 55);
  value = *p_address & 0xFFFF0000U;
  value = value | (((uint32_t)p_huff_table_dc1->bits[15] & 0xFFUL) << 8) |
          ((uint32_t)p_huff_table_dc1->bits[14] & 0xFFUL);
  *p_address = value;

  /* continue setting 12 DC1 huffman bits from DHTMEM + 54 down to DHTMEM + 52 */
  p_address--;
  index = 12;
  while (index > 3UL)
  {

    *p_address = (((uint32_t)p_huff_table_dc1->bits[index + 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_dc1->bits[index] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_dc1->bits[index - 1UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_dc1->bits[index - 2UL] & 0xFFUL);
    p_address--;
    index -= 4UL;

  }
  /* DC1 Huffman Table : Val*/
  /* DC1 VALS is a 12 Bytes table i.e 3x32bits words from DHTMEM base address +55 to DHTMEM + 58 */
  /* only Byte 2 and Byte 3 of the first word (@ DHTMEM + 55) belong to DC1 Val table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 55);
  value = *p_address & 0x0000FFFFUL;
  value = value | (((uint32_t)p_huff_table_dc1->huff_val[1] & 0xFFUL) << 24) |
          (((uint32_t)p_huff_table_dc1->huff_val[0] & 0xFFUL) << 16);
  *p_address = value;

  /* only Byte 0 and Byte 1 of the last word (@ DHTMEM + 58) belong to DC1 Val table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 58);
  value = *p_address & 0xFFFF0000UL;
  value = value | (((uint32_t)p_huff_table_dc1->huff_val[11] & 0xFFUL) << 8) |
          ((uint32_t)p_huff_table_dc1->huff_val[10] & 0xFFUL);
  *p_address = value;

  /* continue setting 8 DC1 huffman val from DHTMEM + 57 down to DHTMEM + 56 */
  p_address--;
  index = 8;
  while (index > 3UL)
  {
    *p_address = (((uint32_t)p_huff_table_dc1->huff_val[index + 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_dc1->huff_val[index] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_dc1->huff_val[index - 1UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_dc1->huff_val[index - 2UL] & 0xFFUL);
    p_address--;
    index -= 4UL;
  }

  /* AC1 Huffman Table : bits */
  /* AC1 bits is a 16 Bytes table i.e 4x32bits words from DHTMEM base address + 58 to DHTMEM + 62 */
  /* only Byte 2 and Byte 3 of the first word (@ DHTMEM + 58) belong to AC1 bits table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 58);
  value = *p_address & 0x0000FFFFU;
  value = value | (((uint32_t)p_huff_table_ac1->bits[1] & 0xFFUL) << 24) |
          (((uint32_t)p_huff_table_ac1->bits[0] & 0xFFUL) << 16);
  *p_address = value;

  /* only Byte 0 and Byte 1 of the last word (@ DHTMEM + 62) belong to bits Val table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 62);
  value = *p_address & 0xFFFF0000U;
  value = value | (((uint32_t)p_huff_table_ac1->bits[15] & 0xFFUL) << 8) |
          ((uint32_t)p_huff_table_ac1->bits[14] & 0xFFUL);
  *p_address = value;

  /* continue setting 12 AC1 huffman bits from DHTMEM + 61 down to DHTMEM + 59 */
  p_address--;
  index = 12;
  while (index > 3UL)
  {

    *p_address = (((uint32_t)p_huff_table_ac1->bits[index + 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_ac1->bits[index] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_ac1->bits[index - 1UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_ac1->bits[index - 2UL] & 0xFFUL);
    p_address--;
    index -= 4UL;

  }
  /* AC1 Huffman Table : Val */
  /* AC1 VALS is a 162 Bytes table i.e 41x32bits words from DHTMEM base address + 62 to DHTMEM + 102 */
  /* only Byte 2 and Byte 3 of the first word (@ DHTMEM + 62) belong to AC1 VALS table */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 62);
  value = *p_address & 0x0000FFFFUL;
  value = value | (((uint32_t)p_huff_table_ac1->huff_val[1] & 0xFFUL) << 24) |
          (((uint32_t)p_huff_table_ac1->huff_val[0] & 0xFFUL) << 16);
  *p_address = value;

  /*continue setting 160 AC1 huffman values from DHTMEM + 63 to DHTMEM+102 */
  p_address = (JPEG_GET_INSTANCE(hjpeg)->DHTMEM + 102);
  index = JPEG_AC_HUFF_TABLE_SIZE - 2UL;
  while (index > 3UL)
  {
    *p_address = (((uint32_t)p_huff_table_ac1->huff_val[index + 1UL] & 0xFFUL) << 24) |
                 (((uint32_t)p_huff_table_ac1->huff_val[index] & 0xFFUL) << 16) |
                 (((uint32_t)p_huff_table_ac1->huff_val[index - 1UL] & 0xFFUL) << 8) |
                 ((uint32_t)p_huff_table_ac1->huff_val[index - 2UL] & 0xFFUL);
    p_address--;
    index -= 4UL;
  }

}

/**
  * @brief  Configure the JPEG registers with a given quantization table.
  * @param  p_qtable Pointer to an array of 64 bytes giving the quantization table.
  * @param  p_qtable_address destination quantization address in the JPEG peripheral
  *         it could be QMEM0, QMEM1, QMEM2 or QMEM3.
  * @param  imgage_quality Quality of the JPEG image.
  * @retval HAL_OK    : The JPEG register configured with the given quantization table.
  * @retval HAL_ERROR : Wrong image_quality.
  */
static hal_status_t JPEG_Set_Quantization_Mem(const uint8_t *p_qtable,
                                              volatile uint32_t *p_qtable_address, uint32_t imgage_quality)
{
  uint32_t i;
  uint32_t j;
  uint32_t quant_row;
  uint32_t quant_val;
  uint32_t scale_factor;
  volatile uint32_t *p_table_adress;

  p_table_adress = p_qtable_address;

  if ((imgage_quality >= 50UL) && (imgage_quality <= 100UL))
  {
    scale_factor = JPEG_HIGH_QUALITY_REFERENCE - (imgage_quality * 2UL);
  }
  else if ((imgage_quality > 0UL) && (imgage_quality < 50UL))
  {
    scale_factor = JPEG_LOW_QUALITY_REFERENCE / ((uint32_t)imgage_quality);
  }
  else
  {
    return HAL_ERROR;
  }

  i = 0;
  while (i < (JPEG_QUANT_TABLE_SIZE - 3UL))
  {
    quant_row = 0;
    for (j = 0; j < 4UL; j++)
    {
      quant_val = ((((uint32_t) p_qtable[jpeg_zigzag_order[i + j]]) * scale_factor) + 50UL) / 100UL;

      if (quant_val == 0UL)
      {
        quant_val = 1UL;
      }
      else if (quant_val > 255UL)
      {
        quant_val = JPEG_QUANTVAL_MAX;
      }
      else
      {
        /* Nothing to do */
      }

      quant_row |= ((quant_val & 0xFFUL) << (8UL * j));
    }

    i += 4UL;
    *p_table_adress = quant_row;
    p_table_adress ++;
  }

  return HAL_OK;
}

/**
  * @brief  Configure the JPEG registers for YCbCr color space.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  input_format  Specifies the input_format value.
  *         This parameter can be one of the following values:
  *          @arg HAL_JPEG_IN_FORMAT_YCBCR_444
  *          @arg HAL_JPEG_IN_FORMAT_YCBCR_422
  *          @arg HAL_JPEG_IN_FORMAT_YCBCR_420
  */
static void JPEG_SetColorYCBCR(hal_jpeg_handle_t *hjpeg, hal_jpeg_input_format_t input_format)
{

  uint32_t confr4_config ;

  /* Get the appropriate sampling  factor & block number */
  confr4_config = (((uint32_t)input_format) & (JPEG_CONFR4_HSF | JPEG_CONFR4_VSF | JPEG_CONFR4_NB));

  /*configure the number of component to scan on JPEG Header & the number of color components */
  MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR1, (JPEG_CONFR1_NF | JPEG_CONFR1_NS), JPEG_CONFR1_NF_1 | JPEG_CONFR1_NS_1);

  /* luminance (Y) configuration : sampling factors ,number of blocks and associated  quantization table */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR4, confr4_config);

  /* Blue chrominance (Cb) configuration : sampling factors and associated quantization table */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR5, (JPEG_CONFR5_HSF_0 | JPEG_CONFR5_VSF_0 | JPEG_CONFR5_QT_0
                                               | JPEG_CONFR5_HA | JPEG_CONFR5_HD));

  /* Red chrominance (Cr) configuration : sampling factors  and associated quantization table */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR6, (JPEG_CONFR6_HSF_0 | JPEG_CONFR6_VSF_0 | JPEG_CONFR6_QT_0
                                               | JPEG_CONFR6_HA | JPEG_CONFR6_HD));
}

/**
  * @brief  Configure the JPEG registers for GrayScale color space.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
static void JPEG_SetColorGrayScale(hal_jpeg_handle_t *hjpeg)
{
  /*configure the number of component to scan on JPEG Header & the number of color components */
  CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, (JPEG_CONFR1_NF | JPEG_CONFR1_NS));

  /* luminance (Y) configuration : Horizental and Vertical sampling factors */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR4, (JPEG_CONFR4_HSF_0 | JPEG_CONFR4_VSF_0));
}

/**
  * @brief  Configure the JPEG registers for CMYK color space.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
static void JPEG_SetColorCMYK(hal_jpeg_handle_t *hjpeg)
{
  /* Component 1 configuration (Cyan) */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR4, (JPEG_CONFR4_HSF_0 | JPEG_CONFR4_VSF_0));

  /* Component 2 configuration (Maganta) */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR5, (JPEG_CONFR5_HSF_0 | JPEG_CONFR5_VSF_0));

  /* Component 3 configuration (Yellow) */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR6, (JPEG_CONFR6_HSF_0 | JPEG_CONFR6_VSF_0));

  /* Component 4  configuration (Black) */
  WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->CONFR7, (JPEG_CONFR7_HSF_0 | JPEG_CONFR7_VSF_0));
}

/**
  * @brief  Init the JPEG encoding/decoding process in case of Polling or Interrupt and DMA.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
static void JPEG_Init_Process(hal_jpeg_handle_t *hjpeg)
{
  hjpeg->context &= (~(JPEG_CONTEXT_PAUSE_INPUT | JPEG_CONTEXT_PAUSE_OUTPUT));

  SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_CR_JCEN);

  if ((hjpeg->header_processing) == HAL_JPEG_HEADER_PROCESSING_DISABLED)
  {
    CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_HDR);
  }
  else /* hjpeg->header_processing == HAL_JPEG_HEADER_PROCESSING_ENABLED */
  {
    SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_HDR);
  }

  if ((hjpeg->context & JPEG_CONTEXT_OPERATION_MASK) == JPEG_CONTEXT_DECODE)
  {
    SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_DE);
  }
  else
  {
    CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR1, JPEG_CONFR1_DE);
  }

  CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);

#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)
  /* Disable interrupts , DMA , flush input & output FIFO */
  MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_INTERRUPT_MASK | JPEG_DMA_MASK, JPEG_CR_IFF | JPEG_CR_OFF);
#else  /* USE_HAL_JPEG_DMA */
  /* Disable interrupts , flush input & output FIFO */
  MODIFY_REG(JPEG_GET_INSTANCE(hjpeg)->CR, JPEG_INTERRUPT_MASK, JPEG_CR_IFF | JPEG_CR_OFF);
#endif /* USE_HAL_JPEG_DMA */
  HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_ALL);

  SET_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);

  if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
  {
    HAL_JPEG_EnableIT(hjpeg, HAL_JPEG_IT_IFT | HAL_JPEG_IT_IFNF | HAL_JPEG_IT_OFT | HAL_JPEG_IT_OFNE
                      | HAL_JPEG_IT_EOC | HAL_JPEG_IT_HPD);
  }
  else if ((hjpeg->context & JPEG_CONTEXT_DMA) != 0UL)
  {
    HAL_JPEG_EnableIT(hjpeg, HAL_JPEG_IT_EOC | HAL_JPEG_IT_HPD);

  }
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief  JPEG encoding/decoding process in case of Polling or Interrupt.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval JPEG_PROCESS_DONE if the process has ends.
  * @retval JPEG_PROCESS_ONGOING if the process is ongoing.
  */
static uint32_t JPEG_Process(hal_jpeg_handle_t *hjpeg)
{
  uint32_t tmp_context;

  if ((hjpeg->context & JPEG_CONTEXT_OPERATION_MASK) == JPEG_CONTEXT_DECODE)
  {
    if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_HPD) != 0UL)
    {
      HAL_JPEG_DisableIT(hjpeg, HAL_JPEG_IT_HPD);
      HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_HPD);
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_info_ready_cb(hjpeg);
#else
      HAL_JPEG_InfoReadyCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
    }
  }
  if ((hjpeg->context &  JPEG_CONTEXT_PAUSE_INPUT) == 0UL)
  {
    if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_IFT) != 0UL)
    {
      JPEG_ReadInputData(hjpeg, JPEG_FIFO_TH_SIZE);
    }
    else if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_IFNF) != 0UL)
    {
      JPEG_ReadInputData(hjpeg, 1);
    }
    else
    {
      /* Nothing to do */
    }
  }
  if ((hjpeg->context &  JPEG_CONTEXT_PAUSE_OUTPUT) == 0UL)
  {
    if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_OFT) != 0UL)
    {
      JPEG_StoreOutputData(hjpeg, JPEG_FIFO_TH_SIZE);
    }
    else if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_OFNE) != 0UL)
    {
      JPEG_StoreOutputData(hjpeg, 1);
    }
    else
    {
      /* Nothing to do */
    }
  }

  if (READ_BIT(JPEG_GET_INSTANCE(hjpeg)->SR, HAL_JPEG_FLAG_EOC | HAL_JPEG_FLAG_OFT | HAL_JPEG_FLAG_OFNE) \
      == HAL_JPEG_FLAG_EOC)
  {
    CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);

    if ((hjpeg->context & JPEG_CONTEXT_IT) != 0UL)
    {
      HAL_JPEG_DisableIT(hjpeg, JPEG_INTERRUPT_MASK);
    }

    HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_ALL);

    if (hjpeg->jpeg_out_count_byte > 0UL)
    {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

      hjpeg->jpeg_out_count_byte = 0;
    }

    tmp_context = hjpeg->context;

    hjpeg->context &= (JPEG_CONTEXT_CONF_ENCODING | JPEG_CONTEXT_CUSTOM_TABLES);

    if ((tmp_context & JPEG_CONTEXT_OPERATION_MASK) == JPEG_CONTEXT_DECODE)
    {

      hjpeg->global_state = HAL_JPEG_STATE_IDLE;
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_decode_cplt_cb(hjpeg);
#else
      HAL_JPEG_DecodeCpltCallback(hjpeg);
#endif /*USE_HAL_JPEG_REGISTER_CALLBACKS*/
    }
    else
    {
      hjpeg->global_state = HAL_JPEG_STATE_IDLE;

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_encode_cplt_cb(hjpeg);
#else
      HAL_JPEG_EncodeCpltCallback(hjpeg);
#endif /*USE_HAL_JPEG_REGISTER_CALLBACKS*/
    }

    return JPEG_PROCESS_DONE;
  }

  return JPEG_PROCESS_ONGOING;
}

/**
  * @brief  Store some output data from the JPEG peripheral to the output buffer.
  *         This function is used when the JPEG peripheral has new data to output
  *         in case of Polling or Interrupt process.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  nb_output_words_byte Number of output words (of 32 bits) ready from the JPEG peripheral.
  */
static void JPEG_StoreOutputData(hal_jpeg_handle_t *hjpeg, uint32_t nb_output_words_byte)
{
  uint32_t index;
  uint32_t nb_words;
  uint32_t nb_bytes;
  uint32_t data_word;

  if (hjpeg->out_data_length_byte >= (hjpeg->jpeg_out_count_byte + (nb_output_words_byte << 2)))
  {
    for (index = 0; index < nb_output_words_byte; index++)
    {
      data_word = JPEG_GET_INSTANCE(hjpeg)->DOR;
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte] = (uint8_t)(data_word & 0x000000FFUL);
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 1UL] = (uint8_t)((data_word & 0x0000FF00UL) >> 8);
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 2UL] = (uint8_t)((data_word & 0x00FF0000UL) >> 16);
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 3UL] = (uint8_t)((data_word & 0xFF000000UL) >> 24);
      hjpeg->jpeg_out_count_byte += 4UL;
    }
    if (hjpeg->out_data_length_byte == hjpeg->jpeg_out_count_byte)
    {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /*USE_HAL_JPEG_REGISTER_CALLBACKS*/
      hjpeg->jpeg_out_count_byte = 0;
    }
  }
  else if (hjpeg->out_data_length_byte > hjpeg->jpeg_out_count_byte)
  {
    nb_words = ((hjpeg->out_data_length_byte - hjpeg->jpeg_out_count_byte) >> 2);
    for (index = 0; index < nb_words; index++)
    {
      data_word = JPEG_GET_INSTANCE(hjpeg)->DOR;
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte] = (uint8_t)(data_word & 0x000000FFUL);
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 1UL] = (uint8_t)((data_word & 0x0000FF00UL) >> 8);
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 2UL] = (uint8_t)((data_word & 0x00FF0000UL) >> 16);
      hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 3UL] = (uint8_t)((data_word & 0xFF000000UL) >> 24);
      hjpeg->jpeg_out_count_byte += 4UL;
    }
    if (hjpeg->out_data_length_byte == hjpeg->jpeg_out_count_byte)
    {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
      hjpeg->jpeg_out_count_byte = 0;
    }
    else
    {
      nb_bytes = hjpeg->out_data_length_byte - hjpeg->jpeg_out_count_byte;
      data_word = JPEG_GET_INSTANCE(hjpeg)->DOR;
      for (index = 0; index < nb_bytes; index++)
      {
        hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte] = (uint8_t)((data_word >> (8UL * (index & 0x3UL))) \
                                                                       & 0xFFUL);
        hjpeg->jpeg_out_count_byte++;
      }
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

      hjpeg->jpeg_out_count_byte = 0;

      nb_bytes = 4UL - nb_bytes;
      for (index = nb_bytes; index < 4UL; index++)
      {
        hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte] = (uint8_t)((data_word >> (8UL * index)) & 0xFFUL);
        hjpeg->jpeg_out_count_byte++;
      }
    }
  }
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief  Read some input Data from the input buffer.
  *         This function is used when the JPEG peripheral needs new data
  *         in case of Polling or Interrupt process.
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @param  nb_request_words_byte Number of input words (of 32 bits) that the JPE peripheral request.
  */
static void JPEG_ReadInputData(hal_jpeg_handle_t *hjpeg, uint32_t nb_request_words_byte)
{
  uint32_t nb_bytes = 0;
  uint32_t nb_words;
  uint32_t index;
  uint32_t data_word;
  uint32_t input_count;
  uint32_t max ;

  if ((hjpeg->in_data_length_byte == 0UL) || (nb_request_words_byte == 0UL))
  {
    (void) HAL_JPEG_PauseInputBuffer(hjpeg);
  }
  else if (hjpeg->in_data_length_byte > hjpeg->jpeg_in_count_byte)
  {
    nb_bytes = hjpeg->in_data_length_byte - hjpeg->jpeg_in_count_byte;
  }
  else if (hjpeg->in_data_length_byte == hjpeg->jpeg_in_count_byte)
  {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
    hjpeg->p_get_data_cb(hjpeg, hjpeg->jpeg_in_count_byte);
#else
    HAL_JPEG_GetDataCallback(hjpeg, hjpeg->jpeg_in_count_byte);
#endif /*USE_HAL_JPEG_REGISTER_CALLBACKS*/

    if (hjpeg->in_data_length_byte > 4UL)
    {
      hjpeg->in_data_length_byte = (((hjpeg->in_data_length_byte + 3UL) >> 2) << 2);
    }
    hjpeg->jpeg_in_count_byte = 0;
    nb_bytes = hjpeg->in_data_length_byte;
  }
  else
  {
    /* Nothing to do */
  }
  if (((hjpeg->context &  JPEG_CONTEXT_PAUSE_INPUT) == 0UL) && (nb_bytes > 0UL))
  {
    nb_words = (nb_bytes >> 2);
    if (nb_words > 0UL)
    {
      if (nb_words >= nb_request_words_byte)
      {
        max = nb_request_words_byte;
      }
      else
      {
        max = nb_words;
      }
      for (index = 0; index < max; index++)
      {
        input_count = hjpeg->jpeg_in_count_byte;
        WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->DIR, (((uint32_t)(hjpeg->p_jpeg_in_buff[input_count])) | \
                                                  (((uint32_t)(hjpeg->p_jpeg_in_buff[input_count + 1UL])) << 8) | \
                                                  (((uint32_t)(hjpeg->p_jpeg_in_buff[input_count + 2UL])) << 16) | \
                                                  (((uint32_t)(hjpeg->p_jpeg_in_buff[input_count + 3UL])) << 24)));
        hjpeg->jpeg_in_count_byte += 4UL;
      }
    }
    else
    {
      /* end of file*/
      data_word = 0;
      for (index = 0; index < nb_bytes; index++)
      {
        data_word |= (uint32_t)hjpeg->p_jpeg_in_buff[hjpeg->jpeg_in_count_byte] << (8UL * (index & 0x03UL));
        hjpeg->jpeg_in_count_byte++;
      }
      WRITE_REG(JPEG_GET_INSTANCE(hjpeg)->DIR, data_word);
    }
  }
}

#if defined(USE_HAL_JPEG_DMA) && (USE_HAL_JPEG_DMA == 1)

/**
  * @brief  Start the JPEG DMA process (encoding/decoding).
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval HAL_ERROR   JPEG DMA FIFO In/out transfer is failed.
  * @retval HAL_OK      JPEG encoding/decoding process using DMA is successfully started.
  */
static hal_status_t JPEG_DMA_StartProcess(hal_jpeg_handle_t *hjpeg)
{
  hjpeg->context &= ~JPEG_CONTEXT_ENDING_DMA;

  JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_ODMA | JPEG_DMA_IDMA);

  hjpeg->hdma_in->p_xfer_cplt_cb = JPEG_DMAInCpltCallback;

  hjpeg->hdma_in->p_xfer_error_cb = JPEG_DMAErrorCallback;
  hjpeg->hdma_out->p_xfer_cplt_cb = JPEG_DMAOutCpltCallback;
  hjpeg->hdma_out->p_xfer_error_cb = JPEG_DMAErrorCallback;
  hjpeg->hdma_out->p_xfer_abort_cb = JPEG_DMAOutAbortCallback;

  /*DMA transfer size must be a multiple of 4 bytes i.e multiple of 32bits words*/
  hjpeg->in_data_length_byte = hjpeg->in_data_length_byte - (hjpeg->in_data_length_byte % 4UL);
  hjpeg->out_data_length_byte = hjpeg->out_data_length_byte - (hjpeg->out_data_length_byte % 4UL);

  /* Enable the Rx DMA Stream */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hjpeg->hdma_in, (uint32_t)hjpeg->p_jpeg_in_buff,
                                     (uint32_t)&JPEG_GET_INSTANCE(hjpeg)->DIR,
                                     hjpeg->in_data_length_byte, HAL_DMA_OPT_IT_NONE)  != HAL_OK)
  {

#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
    hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

    hjpeg->global_state = HAL_JPEG_STATE_IDLE;

    return HAL_ERROR;
  }

  /* Enable the Tx DMA Stream */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hjpeg->hdma_out, (uint32_t)&JPEG_GET_INSTANCE(hjpeg)->DOR,
                                     (uint32_t)hjpeg->p_jpeg_out_buff,
                                     hjpeg->out_data_length_byte, HAL_DMA_OPT_IT_NONE)  != HAL_OK)
  {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
    hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

    hjpeg->global_state = HAL_JPEG_STATE_IDLE;

    return HAL_ERROR;
  }
  JPEG_ENABLE_DMA(hjpeg, JPEG_DMA_IDMA | JPEG_DMA_ODMA);
  return HAL_OK;
}

/**
  * @brief  Continue the current JPEG DMA process (encoding/decoding).
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
static void JPEG_DMA_ContinueProcess(hal_jpeg_handle_t *hjpeg)
{
  if ((hjpeg->context & JPEG_CONTEXT_OPERATION_MASK) == JPEG_CONTEXT_DECODE)
  {
    if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_HPD) != 0UL)
    {

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_info_ready_cb(hjpeg);
#else
      HAL_JPEG_InfoReadyCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

      HAL_JPEG_DisableIT(hjpeg, HAL_JPEG_IT_HPD);
      HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_HPD);
    }
  }

  if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_EOC) != 0UL)
  {
    JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_ODMA | JPEG_DMA_IDMA);

    hjpeg->context |= JPEG_CONTEXT_ENDING_DMA;

    CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);
    HAL_JPEG_DisableIT(hjpeg, JPEG_INTERRUPT_MASK);

    HAL_JPEG_ClearFlag(hjpeg, HAL_JPEG_FLAG_ALL);

    if (hjpeg->hdma_in->global_state == HAL_DMA_STATE_ACTIVE)
    {
      (void) HAL_DMA_Abort_IT(hjpeg->hdma_in);
    }

    if (hjpeg->hdma_out->global_state == HAL_DMA_STATE_ACTIVE)
    {
      (void) HAL_DMA_Abort_IT(hjpeg->hdma_out);
    }
    else
    {
      JPEG_DMA_EndProcess(hjpeg);
    }
  }
}

/**
  * @brief  Finalize the current JPEG DMA process (encoding/decoding).
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
static void JPEG_DMA_EndProcess(hal_jpeg_handle_t *hjpeg)
{
  uint32_t tmp_context;
  hjpeg->jpeg_out_count_byte = hjpeg->out_data_length_byte - JPEG_GET_DMA_REMAIN_DATA((DMA_Channel_TypeDef *) \
                               ((uint32_t)hjpeg->hdma_out->instance));

  if (hjpeg->jpeg_out_count_byte == hjpeg->out_data_length_byte)
  {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
    hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
    HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

    hjpeg->jpeg_out_count_byte = 0;
  }
  if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_OFNE) == 0UL)
  {
    if (hjpeg->jpeg_out_count_byte > 0UL)
    {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

      hjpeg->jpeg_out_count_byte = 0;
    }
    CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);

    tmp_context = hjpeg->context;
    hjpeg->context &= (JPEG_CONTEXT_CONF_ENCODING | JPEG_CONTEXT_CUSTOM_TABLES);

    if ((tmp_context & JPEG_CONTEXT_OPERATION_MASK) == JPEG_CONTEXT_DECODE)
    {
      hjpeg->global_state = HAL_JPEG_STATE_IDLE;
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_decode_cplt_cb(hjpeg);
#else
      HAL_JPEG_DecodeCpltCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
    }
    else
    {
      hjpeg->global_state = HAL_JPEG_STATE_IDLE;
#if (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_encode_cplt_cb(hjpeg);
#else
      HAL_JPEG_EncodeCpltCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
    }
  }
  else if ((hjpeg->context &  JPEG_CONTEXT_PAUSE_OUTPUT) == 0UL)
  {
    JPEG_DMA_PollResidualData(hjpeg);
  }
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief  Poll residual output data when DMA process (encoding/decoding).
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  */
static void JPEG_DMA_PollResidualData(hal_jpeg_handle_t *hjpeg)
{
  uint32_t tmp_context;
  uint32_t count;
  uint32_t data_out;

  for (count = JPEG_FIFO_SIZE; count > 0UL; count--)
  {
    if ((hjpeg->context &  JPEG_CONTEXT_PAUSE_OUTPUT) == 0UL)
    {
      if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_OFNE) != 0UL)
      {
        data_out = JPEG_GET_INSTANCE(hjpeg)->DOR;
        hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte] = (uint8_t)(data_out & 0x000000FFUL);
        hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 1UL] = (uint8_t)((data_out & 0x0000FF00UL) >> 8);
        hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 2UL] = (uint8_t)((data_out & 0x00FF0000UL) >> 16);
        hjpeg->p_jpeg_out_buff[hjpeg->jpeg_out_count_byte + 3UL] = (uint8_t)((data_out & 0xFF000000UL) >> 24);
        hjpeg->jpeg_out_count_byte += 4UL;

        if (hjpeg->jpeg_out_count_byte == hjpeg->out_data_length_byte)
        {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
          hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
          HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

          hjpeg->jpeg_out_count_byte = 0;
        }
      }
    }
  }

  tmp_context = hjpeg->context;

  if ((HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_OFNE) == 0UL) \
      || ((tmp_context & JPEG_CONTEXT_PAUSE_OUTPUT) == 0UL))
  {
    CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);

    if (hjpeg->jpeg_out_count_byte > 0UL)
    {
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

      hjpeg->jpeg_out_count_byte = 0;
    }

    tmp_context = hjpeg->context;

    hjpeg->context &= (JPEG_CONTEXT_CONF_ENCODING | JPEG_CONTEXT_CUSTOM_TABLES);

    if ((tmp_context & JPEG_CONTEXT_OPERATION_MASK) == JPEG_CONTEXT_DECODE)
    {

      hjpeg->global_state = HAL_JPEG_STATE_IDLE;
#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_decode_cplt_cb(hjpeg);
#else
      HAL_JPEG_DecodeCpltCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
    }
    else
    {
      hjpeg->global_state = HAL_JPEG_STATE_IDLE;

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_encode_cplt_cb(hjpeg);
#else
      HAL_JPEG_EncodeCpltCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  DMA input transfer complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure.
  */
static void JPEG_DMAInCpltCallback(hal_dma_handle_t *hdma)
{
  hal_jpeg_handle_t *hjpeg = (hal_jpeg_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  HAL_JPEG_DisableIT(hjpeg, JPEG_INTERRUPT_MASK);

  if ((hjpeg->context & (JPEG_CONTEXT_METHOD_MASK | JPEG_CONTEXT_ENDING_DMA)) ==
      JPEG_CONTEXT_DMA)
  {
    JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_IDMA);

    hjpeg->jpeg_in_count_byte = hjpeg->in_data_length_byte - JPEG_GET_DMA_REMAIN_DATA((DMA_Channel_TypeDef *) \
                                ((uint32_t)hdma->instance));

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
    hjpeg->p_get_data_cb(hjpeg, hjpeg->jpeg_in_count_byte);
#else
    HAL_JPEG_GetDataCallback(hjpeg, hjpeg->jpeg_in_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

    if (hjpeg->in_data_length_byte >= 4UL)
    {
      hjpeg->in_data_length_byte = (((hjpeg->in_data_length_byte + 3UL) >> 2) << 2);
    }
    else
    {
      /* Nothing to do */
    }

    if (((hjpeg->context &  JPEG_CONTEXT_PAUSE_INPUT) == 0UL) && (hjpeg->in_data_length_byte > 0UL))
    {
      if (HAL_DMA_StartPeriphXfer_IT_Opt(hjpeg->hdma_in, (uint32_t)hjpeg->p_jpeg_in_buff,
                                         (uint32_t)&JPEG_GET_INSTANCE(hjpeg)->DIR,
                                         hjpeg->in_data_length_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
      {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
        hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

#if (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
        hjpeg->p_error_cb(hjpeg);
#else
        HAL_JPEG_ErrorCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
        return;
      }
      JPEG_ENABLE_DMA(hjpeg, JPEG_DMA_IDMA);
    }

    HAL_JPEG_EnableIT(hjpeg, HAL_JPEG_IT_EOC | HAL_JPEG_IT_HPD);
  }
}

/**
  * @brief  DMA output transfer complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure.
  */
static void JPEG_DMAOutCpltCallback(hal_dma_handle_t *hdma)
{
  hal_jpeg_handle_t *hjpeg = (hal_jpeg_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  /* Disable The JPEG IT so the DMA Output Callback can not be interrupted by the JPEG EOC IT or JPEG HPD IT */
  HAL_JPEG_DisableIT(hjpeg, JPEG_INTERRUPT_MASK);

  if ((hjpeg->context & (JPEG_CONTEXT_METHOD_MASK | JPEG_CONTEXT_ENDING_DMA)) == JPEG_CONTEXT_DMA)
  {
    if (HAL_JPEG_IsActiveFlag(hjpeg, HAL_JPEG_FLAG_EOC) == 0UL)
    {
      JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_ODMA);
      hjpeg->jpeg_out_count_byte = hjpeg->out_data_length_byte - JPEG_GET_DMA_REMAIN_DATA((DMA_Channel_TypeDef *) \
                                   ((uint32_t)hdma->instance));

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
      hjpeg->p_data_ready_cb(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#else
      HAL_JPEG_DataReadyCallback(hjpeg, hjpeg->p_jpeg_out_buff, hjpeg->jpeg_out_count_byte);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */

      if ((hjpeg->context &  JPEG_CONTEXT_PAUSE_OUTPUT) == 0UL)
      {
        if (HAL_DMA_StartPeriphXfer_IT_Opt(hjpeg->hdma_out, (uint32_t)&JPEG_GET_INSTANCE(hjpeg)->DOR,
                                           (uint32_t)hjpeg->p_jpeg_out_buff,
                                           hjpeg->out_data_length_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
        {
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
          hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
          hjpeg->p_error_cb(hjpeg);
#else
          HAL_JPEG_ErrorCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
          return;
        }
        JPEG_ENABLE_DMA(hjpeg, JPEG_DMA_ODMA);
      }
    }

    HAL_JPEG_EnableIT(hjpeg, HAL_JPEG_IT_EOC | HAL_JPEG_IT_HPD);
  }
}

/**
  * @brief  DMA Transfer error callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure.
  */

static void JPEG_DMAErrorCallback(hal_dma_handle_t *hdma)
{
  hal_jpeg_handle_t *hjpeg = (hal_jpeg_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  CLEAR_BIT(JPEG_GET_INSTANCE(hjpeg)->CONFR0, JPEG_CONFR0_START);
  HAL_JPEG_DisableIT(hjpeg, JPEG_INTERRUPT_MASK);
  JPEG_DISABLE_DMA(hjpeg, JPEG_DMA_MASK);

  hjpeg->global_state = HAL_JPEG_STATE_IDLE;
#if defined(USE_HAL_JPEG_GET_LAST_ERRORS) && (USE_HAL_JPEG_GET_LAST_ERRORS == 1)
  hjpeg->last_error_codes |= HAL_JPEG_ERROR_DMA;
#endif /* USE_HAL_JPEG_GET_LAST_ERRORS */

#if defined (USE_HAL_JPEG_REGISTER_CALLBACKS) && (USE_HAL_JPEG_REGISTER_CALLBACKS == 1)
  hjpeg->p_error_cb(hjpeg);
#else
  HAL_JPEG_ErrorCallback(hjpeg);
#endif /* USE_HAL_JPEG_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA output Abort callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure.
  */
static void JPEG_DMAOutAbortCallback(hal_dma_handle_t *hdma)
{
  hal_jpeg_handle_t *hjpeg = (hal_jpeg_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  if ((hjpeg->context & JPEG_CONTEXT_ENDING_DMA) != 0UL)
  {
    JPEG_DMA_EndProcess(hjpeg);
  }
}

#endif /* USE_HAL_JPEG_DMA */

/**
  * @brief  Calculate the decoded image quality (from 1 to 100).
  * @param  hjpeg Pointer to a hal_jpeg_handle_t structure.
  * @retval JPEG image quality from 1 to 100.
  */
static uint32_t JPEG_GetQuality(const hal_jpeg_handle_t *hjpeg)
{
  uint32_t quality = 0;
  uint32_t quant_row;
  uint32_t quant_val;
  uint32_t scale;
  uint32_t i;
  uint32_t j;
  const volatile uint32_t *p_table_adress = JPEG_GET_INSTANCE(hjpeg)->QMEM0;

  i = 0;
  while (i < (JPEG_QUANT_TABLE_SIZE - 3UL))
  {
    quant_row = *p_table_adress;
    for (j = 0; j < 4UL; j++)
    {
      quant_val = (quant_row >> (8UL * j)) & 0xFFUL;
      if (quant_val == 1UL)
      {
        /* if Quantization value = 1 then quality is 100%*/
        quality += 100UL;
      }
      else
      {
        /* Note that the quantization coefficients must be specified in the table in zigzag order */
        scale = (quant_val * 100UL) / ((uint32_t) hjpeg->p_quant_table0[jpeg_zigzag_order[i + j]]);

        if (scale <= 100UL)
        {
          quality += ((200UL - scale) >> 1);
        }
        else
        {
          quality += 5000UL / scale;
        }
      }
    }

    i += 4UL;
    p_table_adress ++;
  }

  return (quality >> 6);
}
/**
  * @}
  */

#endif /* USE_HAL_JPEG_MODULE */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined(JPEG) */
