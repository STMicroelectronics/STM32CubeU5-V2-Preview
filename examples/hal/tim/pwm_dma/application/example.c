/**
  ******************************************************************************
  * file           : example.c
  * brief          : TIM PWM DMA with HAL API
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
#define BUFFER_SIZE 3U
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_tim_handle_t *pTIM;   /* pointer referencing the TIM handle from the generated code */

/* Compare buffer */
uint32_t CompareBuffer[BUFFER_SIZE] =
{
  MX_PERIOD_VALUE * 1 / 4,
  MX_PERIOD_VALUE * 2 / 4,
  MX_PERIOD_VALUE * 3 / 4
};

/* Private functions prototype -----------------------------------------------*/
/** ########## Step 1 ##########
  * Initializes the GPIO and the TIM for PWM generation.
  * The init of the TIM and the GPIO is triggered by the applicative code.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pTIM = mx_example_tim_init();
  if (pTIM == NULL)
  {
    goto _app_init_exit;
  }

  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /** ########## Step 2 ##########
    * Starts the Timer PWM generation with variable duty cycle using DMA after each update event
    * Data buffer size in byte
    */
  if (HAL_TIM_OC_StartChannel_DMA(pTIM, MX_TIM_CHANNEL, (uint8_t *)CompareBuffer,
                                  BUFFER_SIZE * sizeof(uint32_t)) != HAL_OK)
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


/** Deinitializes the GPIO and TIM peripherals before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  app_status_t return_status = EXEC_STATUS_OK;

  mx_example_tim_deinit();

  return return_status;
} /* end app_deinit */
