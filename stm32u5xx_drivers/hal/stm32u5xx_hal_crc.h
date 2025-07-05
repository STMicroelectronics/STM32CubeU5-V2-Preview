/**
  ******************************************************************************
  * @file    stm32u5xx_hal_crc.h
  * @brief   Header file of CRC HAL module.
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
#ifndef STM32U5XX_HAL_CRC_H
#define STM32U5XX_HAL_CRC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_crc.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup CRC CRC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CRC_Exported_Types CRC Exported Types
  * @{
  */

/** @defgroup CRC_Exported_Types_Group1 Enumerations
  * @{
  */

/*! CRC Instance Definition */

typedef enum
{
  HAL_CRC = (uint32_t)CRC /*!< CRC instance */
} hal_crc_t;

/*! CRC Global State Definition */
typedef enum
{
  HAL_CRC_STATE_RESET  = 0UL,          /*!< CRC is de-initialized          */
  HAL_CRC_STATE_IDLE   = (1UL << 31U), /*!< CRC initialized and configured */
  HAL_CRC_STATE_ACTIVE = (1UL << 30U)  /*!< CRC calculation ongoing        */
} hal_crc_state_t;

/*! CRC Polynomial Size Definition */
typedef enum
{
  HAL_CRC_POLY_SIZE_32B = LL_CRC_POLY_SIZE_32B, /*!< Resort to a 32-bit size generating polynomial */
  HAL_CRC_POLY_SIZE_16B = LL_CRC_POLY_SIZE_16B, /*!< Resort to a 16-bit size generating polynomial */
  HAL_CRC_POLY_SIZE_8B  = LL_CRC_POLY_SIZE_8B,  /*!< Resort to a 8-bit size generating polynomial  */
  HAL_CRC_POLY_SIZE_7B  = LL_CRC_POLY_SIZE_7B   /*!< Resort to a 7-bit size generating polynomial  */
} hal_crc_polynomial_size_t;

/*! CRC Input Data Reversibility Mode Definition */
typedef enum
{
  HAL_CRC_INDATA_REVERSE_NONE      = LL_CRC_INDATA_REVERSE_NONE,     /*!< No input data reversibility           */
  HAL_CRC_INDATA_REVERSE_BYTE      = LL_CRC_INDATA_REVERSE_BYTE,     /*!< Byte-wise input data reverse mode     */
  HAL_CRC_INDATA_REVERSE_HALFWORD  = LL_CRC_INDATA_REVERSE_HALFWORD, /*!< Halfword-wise input data reverse mode */
  HAL_CRC_INDATA_REVERSE_WORD      = LL_CRC_INDATA_REVERSE_WORD      /*!< Word-wise input data reverse mode     */
} hal_crc_input_data_reverse_mode_t;

/*! CRC Output Data Reversibility Mode Definition */
typedef enum
{
  HAL_CRC_OUTDATA_REVERSE_NONE             = LL_CRC_OUTDATA_REVERSE_NONE, /*!< No output data reversibility */
  HAL_CRC_OUTDATA_REVERSE_BIT              = LL_CRC_OUTDATA_REVERSE_BIT,  /*!< Byte-wise output data reverse mode */
} hal_crc_output_data_reverse_mode_t;

/**
  * @}
  */

/** @defgroup CRC_Exported_Types_Group2 Handle Structure
  * @{
  */

typedef struct hal_crc_handle_s hal_crc_handle_t; /*!< CRC Handle type Definition */

/*! CRC Handle Structure Definition */
struct hal_crc_handle_s
{
  hal_crc_t                instance;     /*!< CRC peripheral instance corresponding to the CRC peripheral registers
                                            base address */

  volatile hal_crc_state_t global_state; /*!< CRC state */

#if defined(USE_HAL_CRC_USER_DATA) && (USE_HAL_CRC_USER_DATA == 1)
  const void               *p_user_data;      /*!< User Data Pointer */
#endif /* (USE_HAL_CRC_USER_DATA) */
} ;

/**
  * @}
  */

/** @defgroup CRC_Exported_Types_Group3 Configuration Structure
  * @{
  */

/*! CRC Global Configuration Definition */
typedef struct
{
  uint32_t                              polynomial_coefficient;     /*!< Set CRC generating polynomial as a 7, 8, 16,
                                                                         or 32-bit long value for a polynomial degree
                                                                         respectively equal to 7, 8, 16 or 32
                                                                         This field is written in normal representation
                                                                         e.g., for a polynomial of degree 7, X^7 +
                                                                         X^6 + X^5 + X^2 + 1 is written 0x65
                                                                    */

  hal_crc_polynomial_size_t             polynomial_size;            /*!< This parameter is a value of
                                                                         @ref hal_crc_polynomial_size_t and indicates
                                                                         polynomial size.
                                                                         Value can be either one of:
                                                                         @arg @ref HAL_CRC_POLY_SIZE_32B
                                                                         (32-bit polynomial),
                                                                         @arg @ref HAL_CRC_POLY_SIZE_16B
                                                                         (16-bit polynomial),
                                                                         @arg @ref HAL_CRC_POLY_SIZE_8B
                                                                         (8-bit polynomial),
                                                                         @arg @ref HAL_CRC_POLY_SIZE_7B
                                                                         (7-bit polynomial).
                                                                    */

  uint32_t                              crc_init_value;             /*!< Init value to initiate CRC computation */

  hal_crc_input_data_reverse_mode_t     input_data_reverse_mode;    /*!< This parameter is a value of
                                                                         @ref hal_crc_input_data_reverse_mode_t and
                                                                         specifies input data reversibility mode.
                                                                         Can be either one of the following values
                                                                         @arg @ref HAL_CRC_INDATA_REVERSE_NONE :
                                                                         no input data reversibility
                                                                         @arg @ref HAL_CRC_INDATA_REVERSE_BYTE :
                                                                         byte-wise reverse mode, 0x1A2B3C4D becomes
                                                                         0x58D43CB2
                                                                         @arg @ref HAL_CRC_INDATA_REVERSE_HALFWORD :
                                                                         halfword-wise reverse mode, 0x1A2B3C4D becomes
                                                                         0xD458B23C
                                                                         @arg @ref HAL_CRC_INDATA_REVERSE_WORD :
                                                                         word-wise reverse mode, 0x1A2B3C4D becomes
                                                                         0xB23CD458
                                                                    */
  hal_crc_output_data_reverse_mode_t    output_data_reverse_mode;   /*!< This parameter is a value of
                                                                         @ref hal_crc_output_data_reverse_mode_t and
                                                                         specifies output data reversibility mode.
                                                                         Can be either
                                                                         @arg @ref HAL_CRC_OUTDATA_REVERSE_NONE :
                                                                         no CRC reversibility,
                                                                         @arg @ref HAL_CRC_OUTDATA_REVERSE_BIT :
                                                                         CRC 0x11223344 is converted into 0x22CC4488
                                                                    */
} hal_crc_config_t;

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup CRC_Exported_Functions CRC Exported Functions
  * @{
  */

/** @defgroup CRC_Exported_Functions_Group1 Initialization and De-initialization functions
  * @{
  */
hal_status_t HAL_CRC_Init(hal_crc_handle_t *hcrc, hal_crc_t instance);
void HAL_CRC_DeInit(hal_crc_handle_t *hcrc);
/**
  * @}
  */


/** @defgroup CRC_Exported_Functions_Group2 Configuration functions
  * @{
  */
hal_status_t HAL_CRC_SetConfig(hal_crc_handle_t *hcrc, const hal_crc_config_t *p_config);
void HAL_CRC_GetConfig(const hal_crc_handle_t *hcrc, hal_crc_config_t *p_config);

void HAL_CRC_ResetConfig(hal_crc_handle_t *hcrc);

hal_status_t HAL_CRC_SetConfigPolynomial(hal_crc_handle_t *hcrc, uint32_t poly_coefficient,
                                         hal_crc_polynomial_size_t poly_size,
                                         uint32_t crc_init_value);

hal_status_t HAL_CRC_SetInputReverseMode(hal_crc_handle_t *hcrc,
                                         hal_crc_input_data_reverse_mode_t input_reverse_mode);
hal_crc_input_data_reverse_mode_t HAL_CRC_GetInputReverseMode(const hal_crc_handle_t *hcrc);

hal_status_t HAL_CRC_SetOutputReverseMode(hal_crc_handle_t *hcrc,
                                          hal_crc_output_data_reverse_mode_t output_reverse_mode);
hal_crc_output_data_reverse_mode_t HAL_CRC_GetOutputReverseMode(const hal_crc_handle_t *hcrc);

hal_status_t HAL_CRC_SetIndependentData(hal_crc_handle_t *hcrc, uint32_t independent_data);
uint32_t HAL_CRC_GetIndependentData(const hal_crc_handle_t *hcrc);
/**
  * @}
  */

/** @defgroup CRC_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
hal_status_t HAL_CRC_Accumulate(hal_crc_handle_t *hcrc, const void *p_data, uint32_t size_byte, uint32_t *p_crc_result);
hal_status_t HAL_CRC_Calculate(hal_crc_handle_t *hcrc, const void *p_data, uint32_t size_byte, uint32_t *p_crc_result);
/**
  * @}
  */

/** @defgroup CRC_Exported_Functions_Group4 Peripheral State functions
  * @{
  */
hal_crc_state_t HAL_CRC_GetState(const hal_crc_handle_t *hcrc);
/**
  * @}
  */

#if defined(USE_HAL_CRC_USER_DATA) && (USE_HAL_CRC_USER_DATA == 1)
/** @defgroup CRC_Exported_Functions_Group5 User data functions
  * @{
  */
void HAL_CRC_SetUserData(hal_crc_handle_t *hcrc, const void *p_user_data);
const void *HAL_CRC_GetUserData(const hal_crc_handle_t *hcrc);
/**
  * @}
  */
#endif /* (USE_HAL_CRC_USER_DATA) */

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
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_CRC_H */
