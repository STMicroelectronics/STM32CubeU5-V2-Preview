/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body (GPIO toggle with HAL API)
  ******************************************************************************
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
#include "example.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype -----------------------------------------------*/

/** ########## Step 1 ##########
  * The applicative code initializes the GPIO.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (mx_example_gpio_init() == 0)
  {
    return_status = EXEC_STATUS_INIT_OK;
  }

  return return_status;
} /* end app_init */


/** ########## Step 2 ##########
  * Toggles the GPIO state.
  */
app_status_t app_process(void)
{
  HAL_GPIO_TogglePin(MX_EXAMPLE_GPIO_GPIO_PORT, MX_EXAMPLE_GPIO_PIN);
  return EXEC_STATUS_OK;
} /* end app_process */


app_status_t app_deinit(void)
{
  /** This API is not used in this example (infinite loop).
    * It is optimized out by the toolchain.
    */
  return EXEC_STATUS_ERROR;
} /* end app_deinit */
