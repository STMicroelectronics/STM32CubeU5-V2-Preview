/**
  ******************************************************************************
  * @file           : mx_i2c1.h
  * @brief          : Header for mx_i2c1.c file.
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
#ifndef STM32_I2C1_H
#define STM32_I2C1_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for I2C in HAL layer */
/******************************************************************************/
/**
  * @brief mx_i2c1_hal init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_i2c_handle_t *mx_i2c1_hal_init(void);

/**
  * @brief  De-initialize i2c1 instance and return it.
  */
void mx_i2c1_hal_deinit(void);

/**
  * @brief  Get the I2C1 object.
  * @retval Pointer on the I2C1 Handle
  */
hal_i2c_handle_t *mx_i2c1_hal_gethandle(void);

/******************************************************************************/
/*                     I2C1 event interrupt                    */
/******************************************************************************/
void I2C1_EV_IRQHandler(void);

/******************************************************************************/
/*                     I2C1 error interrupt                    */
/******************************************************************************/
void I2C1_ERR_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_I2C1_H */
