/**
  ******************************************************************************
  * @file           : mx_spi1.c
  * @brief          : SPI1 Peripheral initialization
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
#include "mx_spi1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_spi_handle_t hSPI1;
  /******************************************************************************/
/* Exported functions for SPI in HAL layer (SW instance MySPI_1) */
/******************************************************************************/
hal_spi_handle_t *mx_spi1_hal_init(void)
{
  hal_spi_config_t spi_config;

  if (HAL_SPI_Init(&hSPI1, HAL_SPI1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_SPI1_EnableClock();
  if (HAL_RCC_SPI1_SetKernelClkSource(HAL_RCC_SPI1_CLK_SRC_SYSCLK) != HAL_OK)
  {
    return NULL;
  }
  spi_config.mode = HAL_SPI_MODE_SLAVE;
  spi_config.direction = HAL_SPI_DIRECTION_FULL_DUPLEX;
  spi_config.data_width = HAL_SPI_DATA_WIDTH_8_BIT;
  spi_config.clock_polarity = HAL_SPI_CLOCK_POLARITY_LOW;
  spi_config.clock_phase = HAL_SPI_CLOCK_PHASE_1_EDGE;
  spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_2;
  spi_config.first_bit = HAL_SPI_MSB_FIRST;
  spi_config.nss_pin_management = HAL_SPI_NSS_PIN_MGMT_INTERNAL;

  if (HAL_SPI_SetConfig(&hSPI1, &spi_config) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_GPIOA_EnableClock();


    hal_gpio_config_t  gpio_config;

  /**
    SPI1 GPIO Configuration
    PA5   --------->  SPI1_SCK
    PA6   --------->  SPI1_MISO
    PA7   --------->  SPI1_MOSI
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7, &gpio_config);

  return &hSPI1;
}

void mx_spi1_hal_deinit(void)
{
  (void)HAL_SPI_DeInit(&hSPI1);

  HAL_RCC_SPI1_Reset();

  HAL_RCC_SPI1_DisableClock();

  /* Deinitialization of SPI1: SPI1_SCK,SPI1_MISO,SPI1_MOSI  */
  HAL_GPIO_DeInit(HAL_GPIOA, HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7);



}

hal_spi_handle_t *mx_spi1_hal_gethandle(void)
{
  return &hSPI1;
}


