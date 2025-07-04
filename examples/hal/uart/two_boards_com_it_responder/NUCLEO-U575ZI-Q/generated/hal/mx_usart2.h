/**
  ******************************************************************************
  * @file           : mx_usart2.h
  * @brief          : Header for mx_usart2.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_USART2_H
#define MX_USART2_H

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
/* Exported functions for UART in HAL layer */
/******************************************************************************/

/**
  * @brief mx_usart2_hal_uart init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_uart_handle_t *mx_usart2_hal_uart_init(void);

/**
  * @brief  De-initialize mx_usart2_hal_uart instance and return it.
  * @retval None
  */
void mx_usart2_hal_uart_deinit(void);

/**
  * @brief  Get the mx_usart2_hal_uart object.
  * @retval Pointer on the mx_usart2_hal_uartHandle
  */
hal_uart_handle_t *mx_usart2_hal_uart_gethandle(void);

/******************************************************************************/
/*                     USART2 global interrupt                    */
/******************************************************************************/
void USART2_IRQHandler(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_USART2_H */
