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
static hal_exti_handle_t hEXTI13;

/******************************************************************************/
/* Exported functions for GPIO in HAL layer (SW instance MyGPIO_1) */
/******************************************************************************/
system_status_t mx_gpio_default_hal_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOC_EnableClock();

  /* PC7   --------->  PC7 */

  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = PC7_INIT_STATE;

  if (HAL_GPIO_Init(PC7_GPIO_PORT, PC7_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /* PC13  --------->  PC13 */
  /* PC13  --------->  MX_EXAMPLE_EXTI_TRIGGER */

  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(PC13_GPIO_PORT, PC13_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  hal_exti_config_t exti_config;

  /* Initialize the EXTI for line 13 */
  HAL_EXTI_Init(&hEXTI13, HAL_EXTI_LINE_13);

  /* Set the trigger as RISING for the GPIOC */
  exti_config.trigger   = HAL_EXTI_TRIGGER_RISING;
  exti_config.gpio_port = HAL_EXTI_GPIOC;
  HAL_EXTI_SetConfig(&hEXTI13, &exti_config);

  /* Set line 13 Interrupt priority */
  HAL_CORTEX_NVIC_SetPriority(EXTI13_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(EXTI13_IRQn);

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_hal_deinit(void)
{
  /* PC7   --------->  PC7 */

  HAL_GPIO_DeInit(PC7_GPIO_PORT, PC7_PIN);

  /* De-initialize the EXTI for GPIOC line13 */
  HAL_EXTI_DeInit(&hEXTI13);

  /* set line 13 Interrupt priority */
  HAL_CORTEX_NVIC_DisableIRQ(EXTI13_IRQn);

  /* PC13  --------->  PC13 */
  /* PC13  --------->  MX_EXAMPLE_EXTI_TRIGGER */

  HAL_GPIO_DeInit(PC13_GPIO_PORT, PC13_PIN);

  return SYSTEM_OK;
}


hal_exti_handle_t *mx_gpio_exti13_gethandle(void)
{
  return &hEXTI13;
}


/******************************************************************************/
/*                     EXTI Line13 interrupt                    */
/******************************************************************************/
void EXTI13_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&hEXTI13);
}

