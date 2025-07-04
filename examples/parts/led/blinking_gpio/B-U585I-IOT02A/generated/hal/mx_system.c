/**
  ******************************************************************************
  * @file           : mx_system.c
  * @brief          : STM32 system program body
  *                   Applicative target system level initialization
  *                   (system clock, cache, TZ...) and system level peripherals
  *                   initialization. mx_system_init() service is called by the main
  *                   before jumping the example entry point.
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
#include "mx_system.h"
#include "mx_cortex_nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
system_status_t mx_system_init(void)
{
  if (pre_system_init_hook() != SYSTEM_OK)
  {
    return SYSTEM_PRESYSTEM_ERROR;
  }

  /*
    startup system section
  */
  if (HAL_Init() != HAL_OK)
  {
    return SYSTEM_STARTUP_ERROR;
  }

  /*
    Interruptions section
  */
  if (mx_cortex_nvic_init() != SYSTEM_OK)
  {
    return SYSTEM_INTERRUPTS_ERROR;
  }

  /*
    myicache_1_init
  */
  if (mx_icache_hal_init() == NULL)
  {
    return SYSTEM_STARTUP_ERROR;
  }

  /* ICACHE automatically started at startup */
  if (HAL_ICACHE_Start(mx_icache_hal_gethandle(), HAL_ICACHE_IT_NONE) != HAL_OK)
  {
    return SYSTEM_STARTUP_ERROR;
  }

  /*
    Clock system section
  */
  if (mx_rcc_hal_init() != SYSTEM_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /* peripherals clock configuration and activation
    is centralized: no clock activation/deactivation in pppi_init */

  if (mx_rcc_peripherals_clock_config() != SYSTEM_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /*
    Peripheral init section
  */
  /*
    mygpio_1_init
    mx_gpio_status_led_init
  */
  if (mx_gpio_default_hal_init() != SYSTEM_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }


  if (post_system_init_hook() != SYSTEM_OK)
  {
    return SYSTEM_POSTSYSTEM_ERROR;
  }

  return SYSTEM_OK;
}

/**
  * @brief  User hook function called before the HAL_Init() function
  * @retval system_status_t System status
  */
__WEAK system_status_t pre_system_init_hook(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the pre_system_init_hook can be implemented in the user file
   */
  return SYSTEM_OK;
}

/**
  * @brief  User hook function called after the HAL_Init() and Peripheral init functions
  * @retval system_status_t System status
  */
__WEAK system_status_t post_system_init_hook(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the post_system_init_hook can be implemented in the user file
   */
  return SYSTEM_OK;
}
