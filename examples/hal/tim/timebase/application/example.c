/**
  ******************************************************************************
  * file           : example.c
  * brief          : TIM timebase with HAL API
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

hal_tim_handle_t *pTIM;  /* pointer referencing the PPP handle from the generated code */

/* Private functions prototype -----------------------------------------------*/
static void TimebaseCallback(hal_tim_handle_t *hTIM);

/** ########## Step 1 ##########
  * Initializes the GPIO and the TIM for time base generation.
  * The init of the TIM and the GPIO instance is triggered by the applicative code.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pTIM = mx_example_tim_init();
  if (pTIM != NULL)
  {
    if (HAL_TIM_RegisterUpdateCallback(pTIM, TimebaseCallback) != HAL_OK)
    {
      goto _app_init_exit;
    }

    if (mx_example_gpio_init() != 0)
    {
      goto _app_init_exit;
    }

    return_status = EXEC_STATUS_INIT_OK;
  }

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_OK;

  /** ########## Step 2 ##########
    * Starts timer base generation
    */
  if (HAL_TIM_Start_IT(pTIM) != HAL_OK)
  {
    return_status = EXEC_STATUS_ERROR;
  }

  return return_status;
} /* end app_process */


/** De-initialization function of the TIM and the GPIO instance is provided as reference.
  */
app_status_t app_deinit(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (mx_example_gpio_deinit() != 0)
  {
    goto _app_deinit_exit;
  }

  mx_example_tim_deinit();

  return_status = EXEC_STATUS_OK;
_app_deinit_exit:
  return return_status;
} /* end app_deinit */


/** ########## Step 3 ##########
  *  Interrupt callback triggered by the timer counter update event.
  */
static void TimebaseCallback(hal_tim_handle_t *htim)
{
  /* Time base generation, LED toggled in accordance with the selected time base frequency. */
  HAL_GPIO_TogglePin(MX_STATUS_LED_GPIO_PORT, MX_STATUS_LED_PIN);
}
