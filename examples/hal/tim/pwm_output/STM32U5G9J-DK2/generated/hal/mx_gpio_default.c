/**
  ******************************************************************************
  * @file           : mx_gpio_default.c
  * @brief          : gpio_default Peripheral initialization
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
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/

/******************************************************************************/
/* Exported functions for GPIO in HAL layer (SW instance MyGPIO_1) */
/******************************************************************************/
system_status_t mx_gpio_default_hal_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOC_EnableClock();

  /* PC7   --------->  LCD_R1 */

  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = LCD_R1_INIT_STATE;

  if (HAL_GPIO_Init(LCD_R1_GPIO_PORT, LCD_R1_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }


  return SYSTEM_OK;
}

system_status_t mx_gpio_default_hal_deinit(void)
{
  /* PC7   --------->  LCD_R1 */

  HAL_GPIO_DeInit(LCD_R1_GPIO_PORT, LCD_R1_PIN);

#if defined(USE_HAL_GPIO_HSLV) && (USE_HAL_GPIO_HSLV == 1U)
  HAL_GPIO_DisableHighSpeedLowVoltage(LCD_R1_GPIO_PORT, LCD_R1_PIN);
#endif /* USE_HAL_GPIO_HSLV */

  return SYSTEM_OK;
}



