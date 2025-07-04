/**
  ******************************************************************************
  * @file           : mx_usart1.c
  * @brief          : USART1 Peripheral initialization
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
/* Includes ------------------------------------------------------------------*/
#include "mx_usart1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/* Handle for UART */
static hal_uart_handle_t hUSART1;


/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for UART in HAL layer */
/******************************************************************************/


hal_uart_handle_t *mx_usart1_hal_uart_init(void)
{
  hal_uart_config_t uart_config;

  /* Basic configuration */
  if (HAL_UART_Init(&hUSART1, HAL_UART1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_USART1_EnableClock();
  if (HAL_RCC_USART1_SetKernelClkSource(HAL_RCC_USART1_CLK_SRC_PCLK2) != HAL_OK)
  {
    return NULL;
  }

  uart_config.baud_rate = 115200;
  uart_config.clock_prescaler = HAL_UART_PRESCALER_DIV1;
  uart_config.word_length = HAL_UART_WORD_LENGTH_8_BIT;
  uart_config.stop_bits = HAL_UART_STOP_BIT_1;
  uart_config.parity = HAL_UART_PARITY_NONE;
  uart_config.direction = HAL_UART_DIRECTION_TX;
  uart_config.hw_flow_ctl = HAL_UART_HW_CONTROL_NONE;
  uart_config.oversampling = HAL_UART_OVERSAMPLING_16;
  uart_config.one_bit_sampling = HAL_UART_ONE_BIT_SAMPLE_DISABLE;

  if (HAL_UART_SetConfig(&hUSART1, &uart_config) != HAL_OK)
  {
    return NULL;
  }


  /* GPIO */
  HAL_RCC_GPIOA_EnableClock();


    hal_gpio_config_t  gpio_config;

  /**
    USART1 GPIO Configuration
    PA9   --------->  USART1_TX
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_7;
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_9, &gpio_config);

  return &hUSART1;
}

void mx_usart1_hal_uart_deinit(void)
{
(void)HAL_UART_DeInit(&hUSART1);

  HAL_RCC_USART1_Reset();

  HAL_RCC_USART1_DisableClock();

  /* Deinitialization of USART1: USART1_TX  */
  HAL_GPIO_DeInit(HAL_GPIOA, HAL_GPIO_PIN_9);

}
hal_uart_handle_t *mx_usart1_hal_uart_gethandle(void)
{
  return &hUSART1;
}
