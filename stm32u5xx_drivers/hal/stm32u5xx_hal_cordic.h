/**
  ******************************************************************************
  * @file    stm32u5xx_hal_cordic.h
  * @brief   This file contains all the functions prototypes for the CORDIC firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5XX_HAL_CORDIC_H
#define STM32U5XX_HAL_CORDIC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_cordic.h"

#if defined(CORDIC)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup CORDIC CORDIC
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Constants CORDIC Exported Constants
  * @{
  */

#if defined (USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
/** @defgroup CORDIC_Error_Code CORDIC Error code
  * @{
  */
#define HAL_CORDIC_ERROR_NONE 0U         /*!< No error  */
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
#define HAL_CORDIC_ERROR_DMA  (1U << 0U) /*!< DMA error */
#endif /* USE_HAL_CORDIC_DMA */
/**
  * @}
  */
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */

/** @defgroup CORDIC_DMA_optional_Interrupt CORDIC DMA optional interrupt
  * @{
  */
#define HAL_CORDIC_OPT_DMA_NONE         0UL        /*!< All optional IT are disabled     */
#define HAL_CORDIC_OPT_DMA_IT_HALF_CPLT (1UL << 1U) /*!< Enable optional IT half complete */
#define HAL_CORDIC_OPT_DMA_ALL          (1UL << 2U) /*!< Enable all optional IT           */
/**
  * @}
  */

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Types CORDIC Exported Types
  * @{
  */

/** @defgroup CORDIC_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief HAL CORDIC instance
  */
typedef enum
{
  HAL_CORDIC = (uint32_t)CORDIC /*!< HAL CORDIC Peripheral instance */
} hal_cordic_t;

/**
  * @brief  CORDIC HAL State Structure definition
  */
typedef enum
{
  HAL_CORDIC_STATE_RESET  = 0UL,          /*!< CORDIC not yet initialized or disabled          */
  HAL_CORDIC_STATE_INIT   = (1UL << 31U), /*!< CORDIC initialized but not yet configured       */
  HAL_CORDIC_STATE_IDLE   = (1UL << 30U), /*!< CORDIC initialized  and a global config applied */
  HAL_CORDIC_STATE_ACTIVE = (1UL << 29U), /*!< CORDIC internal process is ongoing              */
  HAL_CORDIC_STATE_ABORT  = (1UL << 28U)  /*!< CORDIC internal process is aborted              */
} hal_cordic_state_t;

/**
  * @brief CORDIC Function
  */
typedef enum
{
  HAL_CORDIC_FUNCTION_COSINE      = LL_CORDIC_FUNCTION_COSINE,      /*!< Cosine                */
  HAL_CORDIC_FUNCTION_SINE        = LL_CORDIC_FUNCTION_SINE,        /*!< Sine                  */
  HAL_CORDIC_FUNCTION_PHASE       = LL_CORDIC_FUNCTION_PHASE,       /*!< Phase                 */
  HAL_CORDIC_FUNCTION_MODULUS     = LL_CORDIC_FUNCTION_MODULUS,     /*!< Modulus               */
  HAL_CORDIC_FUNCTION_ARCTANGENT  = LL_CORDIC_FUNCTION_ARCTANGENT,  /*!< Arctangent            */
  HAL_CORDIC_FUNCTION_HCOSINE     = LL_CORDIC_FUNCTION_HCOSINE,     /*!< Hyperbolic Cosine     */
  HAL_CORDIC_FUNCTION_HSINE       = LL_CORDIC_FUNCTION_HSINE,       /*!< Hyperbolic Sine       */
  HAL_CORDIC_FUNCTION_HARCTANGENT = LL_CORDIC_FUNCTION_HARCTANGENT, /*!< Hyperbolic Arctangent */
  HAL_CORDIC_FUNCTION_NATURAL_LOG = LL_CORDIC_FUNCTION_NATURALLOG,  /*!< Natural Logarithm     */
  HAL_CORDIC_FUNCTION_SQUARE_ROOT = LL_CORDIC_FUNCTION_SQUAREROOT   /*!< Square Root           */
} hal_cordic_function_t;

/**
  * @brief CORDIC Precision in cycles number (Number of iterations /4)
  */
typedef enum
{
  HAL_CORDIC_PRECISION_1CYCLE   = LL_CORDIC_PRECISION_1CYCLE,   /*!< 1*4 iterations  */
  HAL_CORDIC_PRECISION_2CYCLES  = LL_CORDIC_PRECISION_2CYCLES,  /*!< 2*4 iterations  */
  HAL_CORDIC_PRECISION_3CYCLES  = LL_CORDIC_PRECISION_3CYCLES,  /*!< 3*4 iterations  */
  HAL_CORDIC_PRECISION_4CYCLES  = LL_CORDIC_PRECISION_4CYCLES,  /*!< 4*4 iterations  */
  HAL_CORDIC_PRECISION_5CYCLES  = LL_CORDIC_PRECISION_5CYCLES,  /*!< 5*4 iterations  */
  HAL_CORDIC_PRECISION_6CYCLES  = LL_CORDIC_PRECISION_6CYCLES,  /*!< 6*4 iterations  */
  HAL_CORDIC_PRECISION_7CYCLES  = LL_CORDIC_PRECISION_7CYCLES,  /*!< 7*4 iterations  */
  HAL_CORDIC_PRECISION_8CYCLES  = LL_CORDIC_PRECISION_8CYCLES,  /*!< 8*4 iterations  */
  HAL_CORDIC_PRECISION_9CYCLES  = LL_CORDIC_PRECISION_9CYCLES,  /*!< 9*4 iterations  */
  HAL_CORDIC_PRECISION_10CYCLES = LL_CORDIC_PRECISION_10CYCLES, /*!< 10*4 iterations */
  HAL_CORDIC_PRECISION_11CYCLES = LL_CORDIC_PRECISION_11CYCLES, /*!< 11*4 iterations */
  HAL_CORDIC_PRECISION_12CYCLES = LL_CORDIC_PRECISION_12CYCLES, /*!< 12*4 iterations */
  HAL_CORDIC_PRECISION_13CYCLES = LL_CORDIC_PRECISION_13CYCLES, /*!< 13*4 iterations */
  HAL_CORDIC_PRECISION_14CYCLES = LL_CORDIC_PRECISION_14CYCLES, /*!< 14*4 iterations */
  HAL_CORDIC_PRECISION_15CYCLES = LL_CORDIC_PRECISION_15CYCLES  /*!< 15*4 iterations */
} hal_cordic_precision_t;

/**
  * @brief CORDIC scaling factor
  * Scale factor value 'n' implies that the input data have been multiplied
  * by a factor 2exp(-n), and/or the output data need to be multiplied by 2exp(n).
  */
typedef enum
{
  HAL_CORDIC_SCALE_0 = LL_CORDIC_SCALE_0, /*!< Scaling factor - Arguments Mulltiplied by 2^0 */
  HAL_CORDIC_SCALE_1 = LL_CORDIC_SCALE_1, /*!< Scaling factor - Arguments Mulltiplied by 2^1 */
  HAL_CORDIC_SCALE_2 = LL_CORDIC_SCALE_2, /*!< Scaling factor - Arguments Mulltiplied by 2^2 */
  HAL_CORDIC_SCALE_3 = LL_CORDIC_SCALE_3, /*!< Scaling factor - Arguments Mulltiplied by 2^3 */
  HAL_CORDIC_SCALE_4 = LL_CORDIC_SCALE_4, /*!< Scaling factor - Arguments Mulltiplied by 2^4 */
  HAL_CORDIC_SCALE_5 = LL_CORDIC_SCALE_5, /*!< Scaling factor - Arguments Mulltiplied by 2^5 */
  HAL_CORDIC_SCALE_6 = LL_CORDIC_SCALE_6, /*!< Scaling factor - Arguments Mulltiplied by 2^6 */
  HAL_CORDIC_SCALE_7 = LL_CORDIC_SCALE_7  /*!< Scaling factor - Arguments Mulltiplied by 2^7 */
} hal_cordic_scale_factor_t;

/**
  * @brief CORDIC Number of 32-bit arguments required for one calculus
  */
typedef enum
{
  HAL_CORDIC_ARG_NB_1 = LL_CORDIC_NBWRITE_1, /*!< One 32-bits write for either one data input in q1.31 format
                                                  or two 16-bits data input in q1.15 format packed in one 32-bits */
  HAL_CORDIC_ARG_NB_2 = LL_CORDIC_NBWRITE_2  /*!< Two 32-bits writes for two data inputs in q1.31 format          */
} hal_cordic_arg_nb_t;

/**
  * @brief CORDIC  Number of 32-bit result required after one calculus
  */
typedef enum
{
  HAL_CORDIC_RESULT_NB_1 = LL_CORDIC_NBREAD_1, /*!< One 32-bits read for either one data output in q1.31 format
                                                    or two 16-bits data outputs in q1.15 format packed in one 32 bits */
  HAL_CORDIC_RESULT_NB_2 = LL_CORDIC_NBREAD_2  /*!< Two 32-bits reads for two 32-bits data output in q1.31 format     */
} hal_cordic_result_nb_t;

/**
  * @brief CORDIC input data size
  */
typedef enum
{
  HAL_CORDIC_IN_SIZE_32BITS = LL_CORDIC_INSIZE_32BITS, /*!< 32 bits input data size (q1.31 format) */
  HAL_CORDIC_IN_SIZE_16BITS = LL_CORDIC_INSIZE_16BITS  /*!< 16 bits input data size (q1.15 format) */
} hal_cordic_in_size_t;

/**
  * @brief CORDIC output data size
  */
typedef enum
{
  HAL_CORDIC_OUT_SIZE_32BITS = LL_CORDIC_OUTSIZE_32BITS, /*!< 32 bits output data size (q1.31 format) */
  HAL_CORDIC_OUT_SIZE_16BITS = LL_CORDIC_OUTSIZE_16BITS  /*!< 16 bits output data size (q1.15 format) */
} hal_cordic_out_size_t;
/**
  * @}
  */

/** @defgroup CORDIC_Exported_Types_Group2 CORDIC Configuration Structure
  * @{
  */

/**
  * @brief  CORDIC  data buffer descriptor
  */
typedef struct
{
  int32_t  *p_data;   /*!< data pointer             */
  uint32_t size_word; /*!< 32bits data buffer size. */
} hal_cordic_buffer_desc_t;

/**
  * @brief  CORDIC Function Global Config Structure definition
  */
typedef struct
{
  hal_cordic_function_t     function;   /*!< Function to apply.                                                   */
  hal_cordic_scale_factor_t scale;      /*!< Scaling factor to apply to the arguments and/or results.             */
  hal_cordic_in_size_t      in_size;    /*!< Width of input data (16bits or 32bits).                              */
  hal_cordic_out_size_t     out_size;   /*!< Width of output data (16bits or 32bits).                             */
  hal_cordic_precision_t    precision;  /*!< Precision required (number of iterations).                           */
  hal_cordic_arg_nb_t       nb_args;    /*!< Number of arguments (one 32-bits value or two 32-bit values)
                                             expected by the CORDIC_WDATA register.                               */
  hal_cordic_result_nb_t    nb_results; /*!< Number of results (one 32-bits value/two 16_bit values or two 32-bits
                                             values) in the CORDIC_RDATA register.                                */
} hal_cordic_config_t;

/**
  * @}
  */

/** @defgroup CORDIC_Exported_Types_Group3 CORDIC Handle Structure
  * @{
  */
typedef struct hal_cordic_handle_s hal_cordic_handle_t; /*!< CORDIC handle structure type */

#if defined (USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1U)
typedef void (*hal_cordic_cb_t)(hal_cordic_handle_t *hcordic); /*!< Pointer to CORDIC callback function */
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */

/**
  * @brief  HAL CORDIC handle structure definition
  */
struct hal_cordic_handle_s
{
  hal_cordic_t                instance;             /*!< CORDIC instance                                     */
  const int32_t               *p_input_buffer;      /*!< Pointer to CORDIC input data buffer                 */
  int32_t                     *p_output_buffer;     /*!< Pointer to CORDIC output data buffer                */
  uint32_t                    nb_calculus_to_do;    /*!< Remaining number of calculus to do                  */
  uint32_t                    nb_calculus_to_get;   /*!< Remaining number of calculus result to get          */

#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
  hal_dma_handle_t            *p_dma_in;            /*!< CORDIC peripheral input data DMA handle parameters  */
  hal_dma_handle_t            *p_dma_out;           /*!< CORDIC peripheral output data DMA handle parameters */
#endif /* USE_HAL_CORDIC_DMA */

  volatile hal_cordic_state_t global_state;         /*!< CORDIC state                                        */

#if defined (USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1U)
  hal_cordic_cb_t             p_calculate_cpt_cb;   /*!< CORDIC calculate complete callback                  */
  hal_cordic_cb_t             p_write_cpt_cb;       /*!< CORDIC write complete callback                      */
  hal_cordic_cb_t             p_abort_cplt_cb;      /*!< CORDIC abort complete callback                      */
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
  hal_cordic_cb_t             p_write_half_cplt_cb; /*!< DMA write half complete callback                    */
  hal_cordic_cb_t             p_read_half_cplt_cb;  /*!< DMA read half complete callback                     */
#endif /* USE_HAL_CORDIC_DMA */
  hal_cordic_cb_t             p_error_cb;           /*!< CORDIC error callback                               */
#endif /* (USE_HAL_CORDIC_REGISTER_CALLBACKS) */

#if defined(USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
  volatile uint32_t           last_error_codes;     /*!< CORDIC peripheral error code                        */
#endif /* USE_HAL_CORDIC_GET_LAST_ERRORS */

#if defined (USE_HAL_CORDIC_USER_DATA) && (USE_HAL_CORDIC_USER_DATA == 1)
  const void                  *p_user_data;         /*!< User data pointer                                   */
#endif /* USE_HAL_CORDIC_USER_DATA */
};
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CORDIC_Exported_Functions CORDIC Exported functions
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_CORDIC_Init(hal_cordic_handle_t *hcordic, hal_cordic_t instance);
void HAL_CORDIC_DeInit(hal_cordic_handle_t *hcordic);
/**
  * @}
  */

/** @defgroup CORDIC_Exported_Functions_Group2 Configuration functions
  * @{
  */
/* Global configuration for Cordic functions */
hal_status_t HAL_CORDIC_SetConfig(hal_cordic_handle_t *hcordic, const hal_cordic_config_t *p_config);
void HAL_CORDIC_GetConfig(const hal_cordic_handle_t *hcordic, hal_cordic_config_t *p_config);

/* Function to operate */
hal_status_t HAL_CORDIC_SetFunction(hal_cordic_handle_t *hcordic, hal_cordic_function_t function);
hal_cordic_function_t HAL_CORDIC_GetFunction(const hal_cordic_handle_t *hcordic);

/*  Width of Input Data  16bits or 32bits  */
hal_status_t HAL_CORDIC_SetWidthInputSize(hal_cordic_handle_t *hcordic, const hal_cordic_in_size_t input_size);
hal_cordic_in_size_t HAL_CORDIC_GetWidthInputSize(const hal_cordic_handle_t *hcordic);

/*  Width of Output Data  16bits or 32bits */
hal_status_t HAL_CORDIC_SetWidthOutputSize(hal_cordic_handle_t *hcordic, const hal_cordic_out_size_t output_size);
hal_cordic_out_size_t HAL_CORDIC_GetWidthOutputSize(const hal_cordic_handle_t *hcordic);

/*  Number of Arguments   1 or 2 */
hal_status_t HAL_CORDIC_SetNumberArguments(hal_cordic_handle_t *hcordic, const hal_cordic_arg_nb_t nb_argument);
hal_cordic_arg_nb_t HAL_CORDIC_GetNumberArguments(const hal_cordic_handle_t *hcordic);

/*  Number of Results   1 or 2 */
hal_status_t HAL_CORDIC_SetNumberResults(hal_cordic_handle_t *hcordic, const hal_cordic_result_nb_t nb_results);
hal_cordic_result_nb_t HAL_CORDIC_GetNumberResults(const hal_cordic_handle_t *hcordic);

/*  Precision */
hal_status_t HAL_CORDIC_SetPrecision(hal_cordic_handle_t *hcordic, const hal_cordic_precision_t precision);
hal_cordic_precision_t HAL_CORDIC_GetPrecision(const hal_cordic_handle_t *hcordic);

/*  Scaling factor */
hal_status_t HAL_CORDIC_SetScale(hal_cordic_handle_t *hcordic, const hal_cordic_scale_factor_t scaling_factor);
hal_cordic_scale_factor_t HAL_CORDIC_GetScale(const hal_cordic_handle_t *hcordic);

#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
hal_status_t HAL_CORDIC_SetWriteDMA(hal_cordic_handle_t *hcordic, hal_dma_handle_t *hdma_wr);
hal_status_t HAL_CORDIC_SetReadDMA(hal_cordic_handle_t *hcordic, hal_dma_handle_t *hdma_rd);
#endif /* USE_HAL_CORDIC_DMA */


/* CORDIC_WDATA and CORDIC_RDATA can be directly written or read by a periphal (ADC, DAC, etc.).
   Get the read and write register address */
volatile uint32_t *HAL_CORDIC_GetWriteAddress(const hal_cordic_handle_t *hcordic);
volatile uint32_t *HAL_CORDIC_GetReadAddress(const hal_cordic_handle_t *hcordic);

/* WDATA and RDATA can be directly written or read by a peripheral (ADC, DAC, etc.) */
hal_status_t HAL_CORDIC_LockWriteAccessForExternPeriph(hal_cordic_handle_t *hcordic);
hal_status_t HAL_CORDIC_UnlockWriteAccessForExternPeriph(hal_cordic_handle_t *hcordic);

/**
  * @}
  */

/** @defgroup CORDIC_Exported_Functions_Group4 Process functions
  * @{
  */
/* Polling mode*/
hal_status_t HAL_CORDIC_Calculate(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                  hal_cordic_buffer_desc_t *p_buff_out, uint32_t timeout_ms);
/* IT mode*/
hal_status_t HAL_CORDIC_Calculate_IT(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                     hal_cordic_buffer_desc_t *p_buff_out);
/* DMA mode*/
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
hal_status_t HAL_CORDIC_Calculate_DMA(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                      hal_cordic_buffer_desc_t *p_buff_out);
#endif /* USE_HAL_CORDIC_DMA */

/* Zero-Overhead specific mode */
hal_status_t HAL_CORDIC_CalculateZeroOverhead(hal_cordic_handle_t *hcordic,
                                              const hal_cordic_buffer_desc_t *p_buff_in,
                                              hal_cordic_buffer_desc_t *p_buff_out, uint32_t timeout_ms);
/* Abort function */
hal_status_t HAL_CORDIC_Abort(hal_cordic_handle_t *hcordic);
hal_status_t HAL_CORDIC_Abort_IT(hal_cordic_handle_t *hcordic);

/* CORDIC_WDATA and CORDIC_RDATA can be directly written or read by a peripheral (ADC, DAC, etc.) in Polling mode */
hal_status_t HAL_CORDIC_Write(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                              uint32_t timeout_ms);
hal_status_t HAL_CORDIC_Read(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out,
                             uint32_t timeout_ms);

/* CORDIC_WDATA and CORDIC_RDATA can be directly written or read by a peripheral (ADC, DAC, etc.) in IT mode */
hal_status_t HAL_CORDIC_Write_IT(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in);
hal_status_t HAL_CORDIC_Read_IT(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out);

#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
/* CORDIC_WDATA and CORDIC_RDATA can be directly written or read by a peripheral (ADC, DAC, etc.) in DMA mode*/
hal_status_t HAL_CORDIC_Write_DMA(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in);
hal_status_t HAL_CORDIC_Write_DMA_opt(hal_cordic_handle_t *hcordic, const hal_cordic_buffer_desc_t *p_buff_in,
                                      uint32_t opt_it);
hal_status_t HAL_CORDIC_Read_DMA(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out);
hal_status_t HAL_CORDIC_Read_DMA_opt(hal_cordic_handle_t *hcordic, hal_cordic_buffer_desc_t *p_buff_out,
                                     uint32_t opt_it);
#endif /* USE_HAL_CORDIC_DMA */
/**
  * @}
  */

/** @defgroup CORDIC_Exported_Functions_Group5 IRQHandler and Callbacks functions
  * @{
  */
void HAL_CORDIC_IRQHandler(hal_cordic_handle_t *hcordic);
void HAL_CORDIC_ErrorCallback(hal_cordic_handle_t *hcordic);
void HAL_CORDIC_CalculateCpltCallback(hal_cordic_handle_t *hcordic);
void HAL_CORDIC_WriteDataCpltCallback(hal_cordic_handle_t *hcordic);
void HAL_CORDIC_AbortCpltCallback(hal_cordic_handle_t *hcordic);
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
void HAL_CORDIC_WriteHalfCpltCallback(hal_cordic_handle_t *hcordic);
void HAL_CORDIC_ReadHalfCpltCallback(hal_cordic_handle_t *hcordic);
#endif /* USE_HAL_CORDIC_DMA */

#if defined(USE_HAL_CORDIC_REGISTER_CALLBACKS) && (USE_HAL_CORDIC_REGISTER_CALLBACKS == 1)
/* Callbacks Register  functions   */
hal_status_t HAL_CORDIC_RegisterErrorCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback);
hal_status_t HAL_CORDIC_RegisterCalculateCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback);
hal_status_t HAL_CORDIC_RegisterWriteDataCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback);
hal_status_t HAL_CORDIC_RegisterAbortCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback);
#if defined (USE_HAL_CORDIC_DMA) && (USE_HAL_CORDIC_DMA == 1)
hal_status_t HAL_CORDIC_RegisterWriteHalfCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback);
hal_status_t HAL_CORDIC_RegisterReadHalfCpltCallback(hal_cordic_handle_t *hcordic, hal_cordic_cb_t p_callback);
#endif /* USE_HAL_CORDIC_DMA */
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
/**
  * @}
  */

#if defined (USE_HAL_CORDIC_GET_LAST_ERRORS) && (USE_HAL_CORDIC_GET_LAST_ERRORS == 1)
/** @defgroup CORDIC_Exported_Functions_Group6 Error function
  * @{
  */
uint32_t HAL_CORDIC_GetLastErrorCodes(const hal_cordic_handle_t *hcordic);
/**
  * @}
  */
#endif  /* USE_HAL_CORDIC_GET_LAST_ERRORS */

/** @defgroup CORDIC_Exported_Functions_Group7 State function
  * @{
  */
hal_cordic_state_t HAL_CORDIC_GetState(const hal_cordic_handle_t *hcordic);
/**
  * @}
  */

#if defined (USE_HAL_CORDIC_USER_DATA) && (USE_HAL_CORDIC_USER_DATA == 1)
/** @defgroup CORDIC_Exported_Functions_Group8 User Data functions
  * @{
  */
void HAL_CORDIC_SetUserData(hal_cordic_handle_t *hcordic, const void *p_user_data);
const void *HAL_CORDIC_GetUserData(const hal_cordic_handle_t *hcordic);
/**
  * @}
  */
#endif /* USE_HAL_CORDIC_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* CORDIC */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_CORDIC_H */
