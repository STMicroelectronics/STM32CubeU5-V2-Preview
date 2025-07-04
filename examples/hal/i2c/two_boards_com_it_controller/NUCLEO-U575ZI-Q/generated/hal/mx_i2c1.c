/**
  ******************************************************************************
  * @file           : mx_i2c1.c
  * @brief          : I2C1 Peripheral initialization
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
#include "mx_i2c1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_i2c_handle_t hI2C1;
  
/******************************************************************************/
/* Exported functions for I2C1 in HAL layer (SW instance MyI2C_1) */
/******************************************************************************/
hal_i2c_handle_t *mx_i2c1_hal_init(void)
{
  hal_i2c_config_t i2c_config;

  if (HAL_I2C_Init(&hI2C1, HAL_I2C1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_I2C1_EnableClock();

  /*
    Timing automatically calculated with:
     - I2C1 input clock at 160000000 Hz
     - I2C clock speed at 1000000 Hz
  */
  i2c_config.timing           = 0xA0100306;
  i2c_config.addressing_mode  = HAL_I2C_ADDRESSING_7BIT;
  i2c_config.own_address1     = 93 << 1U;
  if (HAL_I2C_SetConfig(&hI2C1, &i2c_config) != HAL_OK)
  {
    return NULL;
  }

  HAL_I2C_EnableAnalogFilter(&hI2C1);

  HAL_RCC_GPIOB_EnableClock();


    hal_gpio_config_t  gpio_config;

  /**
    I2C1 GPIO Configuration
    PB8   --------->  I2C1_SCL
    PB9   --------->  I2C1_SDA
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_4;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_8 | HAL_GPIO_PIN_9, &gpio_config);


  if (HAL_RCC_I2C1_SetKernelClkSource(HAL_RCC_I2C1_CLK_SRC_PCLK1) != HAL_OK)
  {
    return NULL;
  }
  /* Enable the Event interruption for I2C */
  HAL_CORTEX_NVIC_SetPriority(I2C1_EV_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(I2C1_EV_IRQn);

  /* Enable the Error interruption for I2C */
  HAL_CORTEX_NVIC_SetPriority(I2C1_ERR_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(I2C1_ERR_IRQn);

  return &hI2C1;
}

void mx_i2c1_hal_deinit(void)
{
  /* Disable the Event interruption for I2C */
  HAL_CORTEX_NVIC_DisableIRQ(I2C1_ERR_IRQn);

  /* Disable the Error interruption for I2C */
  HAL_CORTEX_NVIC_DisableIRQ(I2C1_ERR_IRQn);

  (void)HAL_I2C_DeInit(&hI2C1);

  HAL_RCC_I2C1_Reset();

  HAL_RCC_I2C1_DisableClock();

  /* Deinitialization of I2C1: I2C1_SCL,I2C1_SDA  */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_8 | HAL_GPIO_PIN_9);

}

hal_i2c_handle_t *mx_i2c1_hal_gethandle(void)
{
  return &hI2C1;
}

/******************************************************************************/
/*                     I2C1 event interrupt                    */
/******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&hI2C1);
}

/******************************************************************************/
/*                     I2C1 error interrupt                    */
/******************************************************************************/
void I2C1_ERR_IRQHandler(void)
{
  HAL_I2C_ER_IRQHandler(&hI2C1);
}

