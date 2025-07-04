/**
  ******************************************************************************
  * @file           : mx_gpio_default.h
  * @brief          : Header for mx_gpio_default.c file.
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
#ifndef MX_GPIO_DEFAULT_H
#define MX_GPIO_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/******************************************************************************/
/* Exported defines for gpio_default in HAL layer (SW instance MyGPIO_1) */
/******************************************************************************/
/* Master labels */
#define PC7_GPIO_PORT      HAL_GPIOC
#define PC7_PIN            HAL_GPIO_PIN_7
#define PC7_INIT_STATE     HAL_GPIO_PIN_RESET
#define PC7_ACTIVE_STATE   HAL_GPIO_PIN_SET
#define PC7_INACTIVE_STATE HAL_GPIO_PIN_RESET
/* Master labels */
#define PC13_GPIO_PORT      HAL_GPIOC
#define PC13_PIN            HAL_GPIO_PIN_13

#define PC13_EXTI_LINE      HAL_EXTI_LINE_13

/* Other labels */
#define MX_EXAMPLE_EXTI_TRIGGER_GPIO_PORT      HAL_GPIOC
#define MX_EXAMPLE_EXTI_TRIGGER_PIN            HAL_GPIO_PIN_13

#define MX_EXAMPLE_EXTI_TRIGGER_EXTI_LINE      HAL_EXTI_LINE_13

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for gpio_default in HAL layer (SW instance MyGPIO_1) */
/******************************************************************************/
/**
  * @brief mx_gpio_default_hal init function
  * This function configures the hardware resources used in this example
  * @retval 0  GPIO group correctly initialized
  * @retval -1 Issue detected during GPIO group initialization
  */
system_status_t mx_gpio_default_hal_init(void);

/**
  * @brief  De-initialize gpio_default instance.
  */
system_status_t mx_gpio_default_hal_deinit(void);

hal_exti_handle_t *mx_gpio_exti13_gethandle(void);

/******************************************************************************/
/*                     EXTI Line13 interrupt                    */
/******************************************************************************/
void EXTI13_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_GPIO_DEFAULT_H */
