/**
  ******************************************************************************
  * file           : example.c
  * brief          : led example with BSP part led
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


/* Private define ------------------------------------------------------------*/
/* @user: configure the wait delay in milliseconds after the LED state is changed */
#define EXAMPLE_WAIT_DELAY_ON_MS (500U)
#define EXAMPLE_WAIT_DELAY_OFF_MS (500U)

/* Exported functions ---------------------------------------------------------*/

/** ########## Step 1 ##########
  * Initializes the LED
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_INIT_OK;

  led_init(MX_STATUS_LED);

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{

  /** ########## Step 2 ##########
    * Turns on, then off, the MX_STATUS_LED
    */
  led_on(MX_STATUS_LED);
  HAL_Delay(EXAMPLE_WAIT_DELAY_ON_MS);

  led_off(MX_STATUS_LED);
  HAL_Delay(EXAMPLE_WAIT_DELAY_OFF_MS);


  /** ########## Step 3 ##########
    * Toggles twice the MX_STATUS_LED
    */
  led_toggle(MX_STATUS_LED);
  HAL_Delay(EXAMPLE_WAIT_DELAY_ON_MS);

  led_toggle(MX_STATUS_LED);
  HAL_Delay(EXAMPLE_WAIT_DELAY_OFF_MS);

  return EXEC_STATUS_OK;
} /* end app_process */


/** De-initializes the applicative part before leaving the scenario.
  * In this example, app_deinit is never called and it is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  app_status_t return_status = EXEC_STATUS_OK;

  /* No de-init concept for a LED part. */

  return return_status;
} /* end app_deinit */
