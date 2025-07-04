/**
  ******************************************************************************
  * @file    stm32u5xx_ll_cordic.h
  * @brief   Header file of CORDIC LL module.
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
#ifndef STM32U5XX_LL_CORDIC_H
#define STM32U5XX_LL_CORDIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(CORDIC)

/** @defgroup CORDIC_LL CORDIC
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Constants CORDIC Exported Constants
  * @{
  */

/** @defgroup CORDIC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_CORDIC_READ_REG function.
  * @{
  */
#define LL_CORDIC_FLAG_RRDY CORDIC_CSR_RRDY
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_WRITE_FLAG DMA WRITE Flags Defines
  * @brief    Flags defines if the DMA WRITE is enabled.
  * @{
  */
#define LL_CORDIC_FLAG_DMAWEN CORDIC_CSR_DMAWEN
/**
  * @}
  */

/** @defgroup CORDIC_LL_READ_GET_FLAG DMA READ Flags Defines
  * @brief    Flags defines if the DMA READ is enabled.
  * @{
  */
#define LL_CORDIC_FLAG_DMAREN CORDIC_CSR_DMAREN
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_CORDIC_READ_REG and LL_CORDIC_WriteReg functions.
  * @{
  */
#define LL_CORDIC_IT_IEN CORDIC_CSR_IEN /*!< Result Ready interrupt enable */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_FUNCTION FUNCTION
  * @{
  */
#define LL_CORDIC_FUNCTION_COSINE      (0x00000000U)                                       /*!< Cosine                */
#define LL_CORDIC_FUNCTION_SINE        ((uint32_t)(CORDIC_CSR_FUNC_0))                     /*!< Sine                  */
#define LL_CORDIC_FUNCTION_PHASE       ((uint32_t)(CORDIC_CSR_FUNC_1))                     /*!< Phase                 */
#define LL_CORDIC_FUNCTION_MODULUS     ((uint32_t)(CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0)) /*!< Modulus               */
#define LL_CORDIC_FUNCTION_ARCTANGENT  ((uint32_t)(CORDIC_CSR_FUNC_2))                     /*!< Arctangent            */
#define LL_CORDIC_FUNCTION_HCOSINE     ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_0)) /*!< Hyperbolic Cosine     */
#define LL_CORDIC_FUNCTION_HSINE       ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1)) /*!< Hyperbolic Sine       */
#define LL_CORDIC_FUNCTION_HARCTANGENT ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1 \
                                                   | CORDIC_CSR_FUNC_0))                   /*!< Hyperbolic Arctangent */
#define LL_CORDIC_FUNCTION_NATURALLOG  ((uint32_t)(CORDIC_CSR_FUNC_3))                     /*!< Natural Logarithm     */
#define LL_CORDIC_FUNCTION_SQUAREROOT  ((uint32_t)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_0)) /*!< Square Root           */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_PRECISION PRECISION
  * @{
  */
#define LL_CORDIC_PRECISION_1CYCLE   ((uint32_t)(CORDIC_CSR_PRECISION_0))                            /*!< 1 cycle   */
#define LL_CORDIC_PRECISION_2CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_1))                            /*!< 2 cycles  */
#define LL_CORDIC_PRECISION_3CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))   /*!< 3 cycles  */
#define LL_CORDIC_PRECISION_4CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_2))                            /*!< 4 cycles  */
#define LL_CORDIC_PRECISION_5CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))   /*!< 5 cycles  */
#define LL_CORDIC_PRECISION_6CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))   /*!< 6 cycles  */
#define LL_CORDIC_PRECISION_7CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_2 \
                                                 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0)) /*!< 7 cycles  */
#define LL_CORDIC_PRECISION_8CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_3))                            /*!< 8 cycles  */
#define LL_CORDIC_PRECISION_9CYCLES  ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_0))   /*!< 9 cycles  */
#define LL_CORDIC_PRECISION_10CYCLES ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_1))   /*!< 10 cycles */
#define LL_CORDIC_PRECISION_11CYCLES ((uint32_t)(CORDIC_CSR_PRECISION_3 \
                                                 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0)) /*!< 11 cycles */
#define LL_CORDIC_PRECISION_12CYCLES ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2))   /*!< 12 cycles */
#define LL_CORDIC_PRECISION_13CYCLES ((uint32_t)(CORDIC_CSR_PRECISION_3 \
                                                 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0)) /*!< 13 cycles */
#define LL_CORDIC_PRECISION_14CYCLES ((uint32_t)(CORDIC_CSR_PRECISION_3 \
                                                 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1)) /*!< 14 cycles */
#define LL_CORDIC_PRECISION_15CYCLES ((uint32_t)(CORDIC_CSR_PRECISION_3 \
                                                 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1 \
                                                 | CORDIC_CSR_PRECISION_0))                          /*!< 15 cycles */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_SCALE SCALE
  * @{
  */
#define LL_CORDIC_SCALE_0 (0x00000000U)                                         /*!< Scaling factor - Arguments * 2^0 */
#define LL_CORDIC_SCALE_1 ((uint32_t)(CORDIC_CSR_SCALE_0))                      /*!< Scaling factor - Arguments * 2^1 */
#define LL_CORDIC_SCALE_2 ((uint32_t)(CORDIC_CSR_SCALE_1))                      /*!< Scaling factor - Arguments * 2^2 */
#define LL_CORDIC_SCALE_3 ((uint32_t)(CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0)) /*!< Scaling factor - Arguments * 2^3 */
#define LL_CORDIC_SCALE_4 ((uint32_t)(CORDIC_CSR_SCALE_2))                      /*!< Scaling factor - Arguments * 2^4 */
#define LL_CORDIC_SCALE_5 ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_0)) /*!< Scaling factor - Arguments * 2^5 */
#define LL_CORDIC_SCALE_6 ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1)) /*!< Scaling factor - Arguments * 2^6 */
#define LL_CORDIC_SCALE_7 ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1 \
                                      | CORDIC_CSR_SCALE_0))                    /*!< Scaling factor - Arguments * 2^7 */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_NBWRITE NBWRITE
  * @{
  */
#define LL_CORDIC_NBWRITE_1 (0x00000000U)    /*!< One 32-bits write containing either only one
                                                  32-bit data input (Q1.31 format), or two
                                                  16-bit data input (Q1.15 format) packed
                                                  in one 32 bits Data */
#define LL_CORDIC_NBWRITE_2 CORDIC_CSR_NARGS /*!< Two 32-bit write containing two 32-bits data input
                                                  (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_NBREAD NBREAD
  * @{
  */
#define LL_CORDIC_NBREAD_1 (0x00000000U)   /*!< One 32-bits read containing either only one
                                                32-bit data output (Q1.31 format), or two
                                                16-bit data output (Q1.15 format) packed
                                                in one 32 bits Data */
#define LL_CORDIC_NBREAD_2 CORDIC_CSR_NRES /*!< Two 32-bit Data containing two 32-bits data output
                                                (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_INSIZE INSIZE
  * @{
  */
#define LL_CORDIC_INSIZE_32BITS (0x00000000U)      /*!< 32 bits input data size (Q1.31 format) */
#define LL_CORDIC_INSIZE_16BITS CORDIC_CSR_ARGSIZE /*!< 16 bits input data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_OUTSIZE OUTSIZE
  * @{
  */
#define LL_CORDIC_OUTSIZE_32BITS (0x00000000U)      /*!< 32 bits output data size (Q1.31 format) */
#define LL_CORDIC_OUTSIZE_16BITS CORDIC_CSR_RESSIZE /*!< 16 bits output data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_DMA_REG_DATA DMA register data
  * @{
  */
#define LL_CORDIC_DMA_REG_DATA_IN  (0x00000000U) /*!< Get address of input data register  */
#define LL_CORDIC_DMA_REG_DATA_OUT (0x00000001U) /*!< Get address of output data register */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Macros CORDIC Exported Macros
  * @{
  */

/** @defgroup CORDIC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in CORDIC register.
  * @param  instance CORDIC Instance
  * @param  reg Register to be written
  * @param value Value to be written in the register
  */
#define LL_CORDIC_WRITE_REG(instance, reg,value) WRITE_REG(instance->reg, (value))

/**
  * @brief  Read a value in CORDIC register.
  * @param  instance CORDIC Instance
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_CORDIC_READ_REG(instance, reg) READ_REG(instance->reg)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup CORDIC_LL_Exported_Functions CORDIC Exported Functions
  * @{
  */

/** @defgroup CORDIC_LL_EF_Configuration CORDIC Configuration functions
  * @{
  */

/**
  * @brief  Configure the CORDIC processing.
  * @note   This function set all parameters of CORDIC processing.
  *         These parameters can also be set individually using
  *         dedicated functions:
  *         - @ref LL_CORDIC_SetFunction()
  *         - @ref LL_CORDIC_SetPrecision()
  *         - @ref LL_CORDIC_SetScale()
  *         - @ref LL_CORDIC_SetNbWrite()
  *         - @ref LL_CORDIC_SetNbRead()
  *         - @ref LL_CORDIC_SetInSize()
  *         - @ref LL_CORDIC_SetOutSize()
  * @rmtoll
  *  CSR          FUNC          LL_CORDIC_Config \n
  *  CSR          PRECISION     LL_CORDIC_Config \n
  *  CSR          SCALE         LL_CORDIC_Config \n
  *  CSR          NARGS         LL_CORDIC_Config \n
  *  CSR          NRES          LL_CORDIC_Config \n
  *  CSR          ARGSIZE       LL_CORDIC_Config \n
  *  CSR          RESIZE        LL_CORDIC_Config
  * @param  p_cordic CORDIC instance
  * @param  function parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_FUNCTION_COSINE
  *         @arg @ref LL_CORDIC_FUNCTION_SINE
  *         @arg @ref LL_CORDIC_FUNCTION_PHASE
  *         @arg @ref LL_CORDIC_FUNCTION_MODULUS
  *         @arg @ref LL_CORDIC_FUNCTION_ARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_HCOSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_NATURALLOG
  *         @arg @ref LL_CORDIC_FUNCTION_SQUAREROOT
  * @param  precision parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_PRECISION_1CYCLE
  *         @arg @ref LL_CORDIC_PRECISION_2CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_3CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_4CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_5CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_6CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_7CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_8CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_9CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_10CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_11CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_12CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_13CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_14CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_15CYCLES
  * @param  scale parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_SCALE_0
  *         @arg @ref LL_CORDIC_SCALE_1
  *         @arg @ref LL_CORDIC_SCALE_2
  *         @arg @ref LL_CORDIC_SCALE_3
  *         @arg @ref LL_CORDIC_SCALE_4
  *         @arg @ref LL_CORDIC_SCALE_5
  *         @arg @ref LL_CORDIC_SCALE_6
  *         @arg @ref LL_CORDIC_SCALE_7
  * @param  number_write parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBWRITE_1
  *         @arg @ref LL_CORDIC_NBWRITE_2
  * @param  number_read parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBREAD_1
  *         @arg @ref LL_CORDIC_NBREAD_2
  * @param  input_size parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_INSIZE_32BITS
  *         @arg @ref LL_CORDIC_INSIZE_16BITS
  * @param  output_size parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_OUTSIZE_32BITS
  *         @arg @ref LL_CORDIC_OUTSIZE_16BITS
  */
__STATIC_INLINE void LL_CORDIC_Config(CORDIC_TypeDef *p_cordic, uint32_t function, uint32_t precision, uint32_t scale,
                                      uint32_t number_write, uint32_t number_read, uint32_t input_size,
                                      uint32_t output_size)
{
  MODIFY_REG(p_cordic->CSR,
             CORDIC_CSR_FUNC | CORDIC_CSR_PRECISION | CORDIC_CSR_SCALE |
             CORDIC_CSR_NARGS | CORDIC_CSR_NRES | CORDIC_CSR_ARGSIZE | CORDIC_CSR_RESSIZE,
             function | precision | scale |
             number_write | number_read | input_size | output_size);
}

/**
  * @brief  Configure function.
  * @rmtoll
  *  CSR          FUNC          LL_CORDIC_SetFunction
  * @param  p_cordic CORDIC Instance
  * @param  function parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_FUNCTION_COSINE
  *         @arg @ref LL_CORDIC_FUNCTION_SINE
  *         @arg @ref LL_CORDIC_FUNCTION_PHASE
  *         @arg @ref LL_CORDIC_FUNCTION_MODULUS
  *         @arg @ref LL_CORDIC_FUNCTION_ARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_HCOSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_NATURALLOG
  *         @arg @ref LL_CORDIC_FUNCTION_SQUAREROOT
  */
__STATIC_INLINE void LL_CORDIC_SetFunction(CORDIC_TypeDef *p_cordic, uint32_t function)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_FUNC, function);
}

/**
  * @brief  Return function.
  * @rmtoll
  *  CSR          FUNC          LL_CORDIC_GetFunction
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_FUNCTION_COSINE
  *         @arg @ref LL_CORDIC_FUNCTION_SINE
  *         @arg @ref LL_CORDIC_FUNCTION_PHASE
  *         @arg @ref LL_CORDIC_FUNCTION_MODULUS
  *         @arg @ref LL_CORDIC_FUNCTION_ARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_HCOSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_NATURALLOG
  *         @arg @ref LL_CORDIC_FUNCTION_SQUAREROOT
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetFunction(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_FUNC));
}

/**
  * @brief  Configure precision in cycles number.
  * @rmtoll
  *  CSR          PRECISION     LL_CORDIC_SetPrecision
  * @param  p_cordic CORDIC Instance
  * @param  precision parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_PRECISION_1CYCLE
  *         @arg @ref LL_CORDIC_PRECISION_2CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_3CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_4CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_5CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_6CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_7CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_8CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_9CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_10CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_11CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_12CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_13CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_14CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_15CYCLES
  */
__STATIC_INLINE void LL_CORDIC_SetPrecision(CORDIC_TypeDef *p_cordic, uint32_t precision)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_PRECISION, precision);
}

/**
  * @brief  Return precision in cycles number.
  * @rmtoll
  *  CSR          PRECISION     LL_CORDIC_GetPrecision
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_PRECISION_1CYCLE
  *         @arg @ref LL_CORDIC_PRECISION_2CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_3CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_4CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_5CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_6CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_7CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_8CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_9CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_10CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_11CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_12CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_13CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_14CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_15CYCLES
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetPrecision(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_PRECISION));
}

/**
  * @brief  Configure scaling factor.
  * @rmtoll
  *  CSR          SCALE         LL_CORDIC_SetScale
  * @param  p_cordic CORDIC Instance
  * @param  scale parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_SCALE_0
  *         @arg @ref LL_CORDIC_SCALE_1
  *         @arg @ref LL_CORDIC_SCALE_2
  *         @arg @ref LL_CORDIC_SCALE_3
  *         @arg @ref LL_CORDIC_SCALE_4
  *         @arg @ref LL_CORDIC_SCALE_5
  *         @arg @ref LL_CORDIC_SCALE_6
  *         @arg @ref LL_CORDIC_SCALE_7
  */
__STATIC_INLINE void LL_CORDIC_SetScale(CORDIC_TypeDef *p_cordic, uint32_t scale)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_SCALE, scale);
}

/**
  * @brief  Return scaling factor.
  * @rmtoll
  *  CSR          SCALE         LL_CORDIC_GetScale
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_SCALE_0
  *         @arg @ref LL_CORDIC_SCALE_1
  *         @arg @ref LL_CORDIC_SCALE_2
  *         @arg @ref LL_CORDIC_SCALE_3
  *         @arg @ref LL_CORDIC_SCALE_4
  *         @arg @ref LL_CORDIC_SCALE_5
  *         @arg @ref LL_CORDIC_SCALE_6
  *         @arg @ref LL_CORDIC_SCALE_7
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetScale(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_SCALE));
}

/**
  * @brief  Configure number of 32-bit write expected for one calculation.
  * @rmtoll
  *  CSR          NARGS         LL_CORDIC_SetNbWrite
  * @param  p_cordic CORDIC Instance
  * @param  number_write parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBWRITE_1
  *         @arg @ref LL_CORDIC_NBWRITE_2
  */
__STATIC_INLINE void LL_CORDIC_SetNbWrite(CORDIC_TypeDef *p_cordic, uint32_t number_write)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_NARGS, number_write);
}

/**
  * @brief  Return number of 32-bit write expected for one calculation.
  * @rmtoll
  *  CSR          NARGS         LL_CORDIC_GetNbWrite
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_NBWRITE_1
  *         @arg @ref LL_CORDIC_NBWRITE_2
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetNbWrite(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_NARGS));
}

/**
  * @brief  Configure number of 32-bit read expected after one calculation.
  * @rmtoll
  *  CSR          NRES          LL_CORDIC_SetNbRead
  * @param  p_cordic CORDIC Instance
  * @param  number_read parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBREAD_1
  *         @arg @ref LL_CORDIC_NBREAD_2
  */
__STATIC_INLINE void LL_CORDIC_SetNbRead(CORDIC_TypeDef *p_cordic, uint32_t number_read)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_NRES, number_read);
}

/**
  * @brief  Return number of 32-bit read expected after one calculation.
  * @rmtoll
  *  CSR          NRES          LL_CORDIC_GetNbRead
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_NBREAD_1
  *         @arg @ref LL_CORDIC_NBREAD_2
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetNbRead(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_NRES));
}

/**
  * @brief  Configure width of input data.
  * @rmtoll
  *  CSR          ARGSIZE       LL_CORDIC_SetInSize
  * @param  p_cordic CORDIC Instance
  * @param  input_size parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_INSIZE_32BITS
  *         @arg @ref LL_CORDIC_INSIZE_16BITS
  */
__STATIC_INLINE void LL_CORDIC_SetInSize(CORDIC_TypeDef *p_cordic, uint32_t input_size)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_ARGSIZE, input_size);
}

/**
  * @brief  Return width of input data.
  * @rmtoll
  *  CSR          ARGSIZE       LL_CORDIC_GetInSize
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_INSIZE_32BITS
  *         @arg @ref LL_CORDIC_INSIZE_16BITS
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetInSize(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_ARGSIZE));
}

/**
  * @brief  Configure width of output data.
  * @rmtoll
  *  CSR          RESIZE       LL_CORDIC_SetOutSize
  * @param  p_cordic CORDIC Instance
  * @param  output_size parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_OUTSIZE_32BITS
  *         @arg @ref LL_CORDIC_OUTSIZE_16BITS
  */
__STATIC_INLINE void LL_CORDIC_SetOutSize(CORDIC_TypeDef *p_cordic, uint32_t output_size)
{
  MODIFY_REG(p_cordic->CSR, CORDIC_CSR_RESSIZE, output_size);
}

/**
  * @brief  Return width of output data.
  * @rmtoll
  *  CSR          RESIZE       LL_CORDIC_GetOutSize
  * @param  p_cordic CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_OUTSIZE_32BITS
  *         @arg @ref LL_CORDIC_OUTSIZE_16BITS
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetOutSize(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_BIT(p_cordic->CSR, CORDIC_CSR_RESSIZE));
}

/**
  * @}
  */

/** @defgroup CORDIC_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable the CORDIC interrupt when result is ready
  * @rmtoll
  *  CSR          IEN         LL_CORDIC_EnableIT
  * @param  p_cordic pointer to CORDIC handle.
  */
__STATIC_INLINE void LL_CORDIC_EnableIT(CORDIC_TypeDef *p_cordic)
{
  SET_BIT(p_cordic->CSR, LL_CORDIC_IT_IEN);
}

/**
  * @brief  Disable the CORDIC interrupt
  * @rmtoll
  *  CSR          IEN         LL_CORDIC_DisableIT
  * @param  p_cordic pointer to CORDIC handle.
  */
__STATIC_INLINE void LL_CORDIC_DisableIT(CORDIC_TypeDef *p_cordic)
{
  CLEAR_BIT(p_cordic->CSR, LL_CORDIC_IT_IEN);
}

/**
  * @brief  Check whether the specified CORDIC status flag is set or not.
  * @param  p_cordic pointer to CORDIC handle.
  * @param  mask CORDIC flag to check
  *         This parameter can be one of the following values:
  *            @arg @ref CORDIC_FLAG_RRDY Result Ready Flag
  * @retval 1UL (flag is set) or 0UL (flag is reset)
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsActiveFlag(const CORDIC_TypeDef *p_cordic, uint32_t mask)
{
  return ((READ_BIT(p_cordic->CSR, mask) == (mask)) ? 1UL : 0UL);
}

/**
  * @brief  Clear specified CORDIC status flag. Dummy macro as no flag can be cleared.
  * @param  p_cordic pointer to CORDIC handle.
  * @param  mask CORDIC flag to clear
  */
__STATIC_INLINE void LL_CORDIC_ClearFlag(CORDIC_TypeDef *p_cordic, uint32_t mask)
{
  CLEAR_BIT(p_cordic->CSR, mask);
}

/**
  * @brief  Check whether the specified CORDIC interrupt is enabled or not.
  * @rmtoll
  *  CSR          IEN           LL_CORDIC_IsEnabledIT
  * @param  p_cordic pointer to CORDIC handle.
  * @retval 1UL (flag is set) or 0UL (flag is reset)
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsEnabledIT(const CORDIC_TypeDef *p_cordic)
{
  return ((READ_BIT(p_cordic->CSR, LL_CORDIC_IT_IEN) == (LL_CORDIC_IT_IEN)) ? 1UL : 0UL);
}

/** @brief  Check whether the specified CORDIC interrupt is enabled or not.
  * @param  p_cordic CORDIC instance.
  * @param  interrupt CORDIC interrupt to check
  * @retval value of the interrupt in the register
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetITSource(const CORDIC_TypeDef *p_cordic, uint32_t interrupt)
{
  return ((LL_CORDIC_READ_REG((p_cordic), CSR) & interrupt));
}
/**
  * @}
  */

/** @defgroup CORDIC_LL_EF_DMA_Management DMA_Management
  * @{
  */

/**
  * @brief  Enable CORDIC DMA read channel request.
  * @rmtoll
  *  CSR          DMAREN        LL_CORDIC_EnableDMAReq_RD
  * @param  p_cordic CORDIC Instance
  */
__STATIC_INLINE void LL_CORDIC_EnableDMAReq_RD(CORDIC_TypeDef *p_cordic)
{
  SET_BIT(p_cordic->CSR, CORDIC_CSR_DMAREN);
}

/**
  * @brief  Disable CORDIC DMA read channel request.
  * @rmtoll
  *  CSR          DMAREN        LL_CORDIC_DisableDMAReq_RD
  * @param  p_cordic CORDIC Instance
  */
__STATIC_INLINE void LL_CORDIC_DisableDMAReq_RD(CORDIC_TypeDef *p_cordic)
{
  CLEAR_BIT(p_cordic->CSR, CORDIC_CSR_DMAREN);
}

/**
  * @brief  Check CORDIC DMA read channel request state.
  * @rmtoll
  *  CSR          DMAREN        LL_CORDIC_IsEnabledDMAReq_RD
  * @param  p_cordic CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsEnabledDMAReq_RD(const CORDIC_TypeDef *p_cordic)
{
  return ((READ_BIT(p_cordic->CSR, CORDIC_CSR_DMAREN) == (CORDIC_CSR_DMAREN)) ? 1U : 0U);
}

/**
  * @brief  Enable CORDIC DMA write channel request.
  * @rmtoll
  *  CSR          DMAWEN        LL_CORDIC_EnableDMAReq_WR
  * @param  p_cordic CORDIC Instance
  */
__STATIC_INLINE void LL_CORDIC_EnableDMAReq_WR(CORDIC_TypeDef *p_cordic)
{
  SET_BIT(p_cordic->CSR, CORDIC_CSR_DMAWEN);
}

/**
  * @brief  Disable CORDIC DMA write channel request.
  * @rmtoll
  *  CSR          DMAWEN        LL_CORDIC_DisableDMAReq_WR
  * @param  p_cordic CORDIC Instance
  */
__STATIC_INLINE void LL_CORDIC_DisableDMAReq_WR(CORDIC_TypeDef *p_cordic)
{
  CLEAR_BIT(p_cordic->CSR, CORDIC_CSR_DMAWEN);
}

/**
  * @brief  Check CORDIC DMA write channel request state.
  * @rmtoll
  *  CSR          DMAWEN        LL_CORDIC_IsEnabledDMAReq_WR
  * @param  p_cordic CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsEnabledDMAReq_WR(const CORDIC_TypeDef *p_cordic)
{
  return ((READ_BIT(p_cordic->CSR, CORDIC_CSR_DMAWEN) == (CORDIC_CSR_DMAWEN)) ? 1U : 0U);
}

/**
  * @brief  Get the CORDIC data register address used for DMA transfer.
  * @rmtoll
  *  RDATA        RES           LL_CORDIC_DMA_GetRegAddr \n
  *  WDATA        ARG           LL_CORDIC_DMA_GetRegAddr
  * @param  p_cordic CORDIC Instance
  * @param  direction parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_DMA_REG_DATA_IN
  *         @arg @ref LL_CORDIC_DMA_REG_DATA_OUT
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t LL_CORDIC_DMA_GetRegAddr(const CORDIC_TypeDef *p_cordic, uint32_t direction)
{
  uint32_t data_reg_addr;

  if (direction == LL_CORDIC_DMA_REG_DATA_OUT)
  {
    /* return address of RDATA register */
    data_reg_addr = (uint32_t) &(p_cordic->RDATA);
  }
  else
  {
    /* return address of WDATA register */
    data_reg_addr = (uint32_t) &(p_cordic->WDATA);
  }

  return data_reg_addr;
}

/**
  * @}
  */


/** @defgroup CORDIC_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check CORDIC result ready flag state.
  * @rmtoll
  *  CSR          RRDY          LL_CORDIC_IsActiveFlag_RRDY
  * @param  p_cordic CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsActiveFlag_RRDY(const CORDIC_TypeDef *p_cordic)
{
  return ((READ_BIT(p_cordic->CSR, CORDIC_CSR_RRDY) == (CORDIC_CSR_RRDY)) ? 1U : 0U);
}
/**
  * @}
  */


/** @defgroup CORDIC_LL_EF_Data_Management Data_Management
  * @{
  */

/**
  * @brief  Write 32-bit input data for the CORDIC processing.
  * @rmtoll
  *  WDATA        ARG           LL_CORDIC_WriteData
  * @param  p_cordic CORDIC Instance
  * @param  input_data 0 .. 0xFFFFFFFF : 32-bit value to be provided as input data for CORDIC processing.
  */
__STATIC_INLINE void LL_CORDIC_WriteData(CORDIC_TypeDef *p_cordic, uint32_t input_data)
{
  WRITE_REG(p_cordic->WDATA, input_data);
}

/**
  * @brief  Return 32-bit output data of CORDIC processing.
  * @rmtoll
  *  RDATA        RES           LL_CORDIC_ReadData
  * @param  p_cordic CORDIC Instance
  * @retval 32-bit output data of CORDIC processing.
  */
__STATIC_INLINE uint32_t LL_CORDIC_ReadData(const CORDIC_TypeDef *p_cordic)
{
  return (uint32_t)(READ_REG(p_cordic->RDATA));
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

#endif /* CORDIC */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_CORDIC_H */
