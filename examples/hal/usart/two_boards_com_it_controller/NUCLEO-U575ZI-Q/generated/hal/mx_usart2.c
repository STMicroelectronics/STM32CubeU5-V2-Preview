/**
  ******************************************************************************
  * @file           : mx_usart2.c
  * @brief          : USART2 Peripheral initialization
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
/* Includes ------------------------------------------------------------------*/
#include "mx_usart2.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/* Handle for USART */
static hal_usart_handle_t hUSART2_usart;


/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for USART in HAL layer */
/******************************************************************************/


hal_usart_handle_t *mx_usart2_cfg1_hal_usart_init(void)
{
  hal_usart_config_t usart_config;

  /* Basic configuration */
  if (HAL_USART_Init(&hUSART2_usart, HAL_USART2) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_USART2_EnableClock();

  if (HAL_RCC_USART2_SetKernelClkSource(HAL_RCC_USART2_CLK_SRC_PCLK1) != HAL_OK)
  {
    return NULL;
  }

  usart_config.baud_rate = 115200;
  usart_config.clock_prescaler = HAL_USART_PRESCALER_DIV1;
  usart_config.word_length = HAL_USART_WORD_LENGTH_8_BIT;
  usart_config.stop_bits = HAL_USART_STOP_BIT_1;
  usart_config.parity = HAL_USART_PARITY_NONE;
  usart_config.direction = HAL_USART_DIRECTION_TX_RX;
  usart_config.clock_polarity = HAL_USART_CLOCK_LOW;
  usart_config.clock_phase = HAL_USART_CLOCK_PHASE_1_EDGE;
  usart_config.clock_last_bit = HAL_USART_CLOCK_LAST_BIT_ENABLED;
  usart_config.mode = HAL_USART_MODE_MASTER;

  if (HAL_USART_SetConfig(&hUSART2_usart, &usart_config) != HAL_OK)
  {
    return NULL;
  }


  /* GPIO */
  HAL_RCC_GPIOD_EnableClock();


  hal_gpio_config_t  gpio_config;

  /**
    USART2 GPIO Configuration
    PD5
    PD6
    PD7
                            --------->  USART2_TX
                            --------->  USART2_RX
                            --------->  USART2_SCLK
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_MEDIUM;
  gpio_config.alternate   = HAL_GPIO_AF_7;
  HAL_GPIO_Init(HAL_GPIOD, HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7, &gpio_config);

  /* Enable interrupt */
  HAL_CORTEX_NVIC_SetPriority(USART2_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(USART2_IRQn);


  return &hUSART2_usart;
}

void mx_usart2_cfg1_hal_usart_deinit(void)
{
  /* Disable interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(USART2_IRQn);
  (void)HAL_USART_DeInit(&hUSART2_usart);

  HAL_RCC_USART2_Reset();

  HAL_RCC_USART2_DisableClock();

  /* ###  GPIO pins de-initialization ################################# */
  /* Deinitialization of USART2: USART2_TX  */
  HAL_GPIO_DeInit(HAL_GPIOD, HAL_GPIO_PIN_5);

  /* ###  GPIO pins de-initialization ################################# */
  /* Deinitialization of USART2: USART2_RX  */
  HAL_GPIO_DeInit(HAL_GPIOD, HAL_GPIO_PIN_6);

  /* ###  GPIO pins de-initialization ################################# */
  /* Deinitialization of USART2: USART2_SCLK  */
  HAL_GPIO_DeInit(HAL_GPIOD, HAL_GPIO_PIN_7);
}

hal_usart_handle_t *mx_usart2_hal_usart_gethandle(void)
{
  return &hUSART2_usart;
}

/******************************************************************************/
/*                     USART2 global interrupt                    */
/******************************************************************************/
void USART2_IRQHandler(void)
{
  HAL_USART_IRQHandler(&hUSART2_usart);
}

