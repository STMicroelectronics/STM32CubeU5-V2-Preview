/**
  ******************************************************************************
  * @file           : mx_tim2.h
  * @brief          : Header for mx_tim2.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_TIM2_H
#define STM32_TIM2_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
  
#define MX_EXAMPLE_TIM_IRQN       TIM2_IRQn
#define MX_EXAMPLE_TIM_IRQHANDLER TIM2_IRQHandler
#define MYTIM_1_IRQN       MX_EXAMPLE_TIM_IRQN
#define MYTIM_1_IRQHANDLER MX_EXAMPLE_TIM_IRQHANDLER
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/******************************************************************************/
/* Exported functions for TIM in HAL layer */
/******************************************************************************/
/**
  * @brief mx_tim2_hal init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_tim_handle_t *mx_tim2_hal_init(void);

/**
  * @brief  De-initialize mx_tim2_hal instance and return it.
  */
void mx_tim2_hal_deinit(void);

/**
  * @brief  Get the mx_tim2_hal object.
  * @retval Pointer on the mx_tim2_hal Handle
  */
hal_tim_handle_t *mx_tim2_hal_gethandle(void);

/******************************************************************************/
/*                     TIM2 global interrupt                    */
/******************************************************************************/
void TIM2_IRQHandler(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_TIM2_H */

