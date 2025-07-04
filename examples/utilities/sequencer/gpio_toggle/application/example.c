/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body (GPIO toggle using sequencer utility)
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

/* @user: configure the period of toggle in milliseconds                      */
#define EXAMPLE_TOGGLE_PERIOD_MS 1000U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ToggleCounter = 0U;

/* Private functions prototype -----------------------------------------------*/

app_status_t app_init(void)
{
  /** ########## Step 1 ##########
    * The applicative code initializes the GPIO.
    */
  app_status_t return_status = EXEC_STATUS_ERROR;
  if (mx_example_gpio_init() == 0)
  {
    return_status = EXEC_STATUS_INIT_OK;
  }

  /** ########## Step 2 ##########
    * Initialize the sequencer and tasks.
    */
  mx_seq_init();

  return return_status;
} /* end app_init */


/** ########## Step 3 ##########
  * task function gpio_toggle() implementation
  */
void gpio_toggle(void)
{
  /* toggle gpio pin */
  HAL_GPIO_TogglePin(MX_EXAMPLE_GPIO_GPIO_PORT, MX_EXAMPLE_GPIO_PIN);
  /* increment ToggleCounter variable */
  ToggleCounter++;
}/* end gpio_toggle */

/** ########## Step 4 ##########
  * starts the sequencer scheduler.
  */
app_status_t app_process(void)
{
  /* run all registered tasks */
  SEQ_Run(SEQ_DEFAULT);
  return EXEC_STATUS_OK;
} /* end app_process */


app_status_t app_deinit(void)
{
  /** This API is not used in this example (infinite loop).
    * It is optimized out by the toolchain.
    */
  return EXEC_STATUS_ERROR;
} /* end app_deinit */


/**
  * This function handles SysTick Handler to set task every 1 second.
  */
void HAL_CORTEX_SYSTICK_Callback(void)
{
  if ((HAL_GetTick() % EXAMPLE_TOGGLE_PERIOD_MS) == 0)
  {
    /* set the toggle task to program the task execution */
    SEQ_SetTask(MX_TASK_TOGGLE, 0);
  }
}
