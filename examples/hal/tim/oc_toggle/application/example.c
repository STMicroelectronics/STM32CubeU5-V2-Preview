/**
  ******************************************************************************
  * file           : example.c
  * brief          : TIM output compare with HAL API
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
hal_tim_handle_t *pTIM;  /* pointer referencing the TIM handle from the generated code */


/* Private functions prototype -----------------------------------------------*/

app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /** ########## Step 1 ##########
    * Initializes the TIM for output compare.
    */
  pTIM = mx_example_tim_init();
  if (pTIM != NULL)
  {
    return_status = EXEC_STATUS_INIT_OK;
  }

  return return_status;
} /* end app_init */


/** ########## Step 2 ##########
    * Starts the timer in Output Capture mode for each channel.
    */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (HAL_TIM_OC_StartChannel(pTIM, PWM_CHANNEL_Y) != HAL_OK)
  {
    goto _app_process_exit;
  }

  if (HAL_TIM_OC_StartChannel(pTIM, PWM_CHANNEL_Z) != HAL_OK)
  {
    goto _app_process_exit;
  }

  if (HAL_TIM_Start(pTIM) != HAL_OK)
  {
    goto _app_process_exit;
  }

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** Deinitializes the TIM peripheral before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  mx_example_tim_deinit();
  return EXEC_STATUS_OK;
} /* end app_deinit */
