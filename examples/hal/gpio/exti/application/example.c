/**
  ******************************************************************************
  * file           : example.c
  * brief          : GPIO EXTI detection with HAL API
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
hal_exti_handle_t *pEXTI; /* pointer referencing the EXTI handle from the generated code */

/** Variable to check the EXTI interrupt detection via the IRQ CallBack.
  * Declared as volatile because updated from an external event (interrupt).
  */
volatile uint8_t ExtiDetected = 0;

/* Private functions prototype -----------------------------------------------*/
static void UserDetectedExtiCallback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger);

/** ########## Step 1 ##########
  * Configures a GPIO pin with register callback linked to the corresponding EXTI line.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  mx_example_exti_trigger_init();
  pEXTI = mx_example_exti_trigger_exti_gethandle();

  if (pEXTI != NULL)
  {
    /* Associates user callback function to any interrupt edge event*/
    if (HAL_EXTI_RegisterTriggerCallback(pEXTI, &UserDetectedExtiCallback) == HAL_OK)
    {
      PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
      return_status = EXEC_STATUS_INIT_OK;
    }
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /** ########## Step 2 ##########
    * Starts the EXTI line and wait for the interrupt.
    * User callback function is called when the interrupt is triggered (step 3).
    */
  if (HAL_EXTI_Enable(pEXTI, HAL_EXTI_MODE_INTERRUPT) == HAL_OK)
  {
    PRINTF("[INFO] Step 2: Waiting for the configured EXTI interrupt.\n");
    while (ExtiDetected == 0)
    {
      /** Awaiting Step 3 completion
        * Put CPU in Wait For Interrupt state. An EXTI interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupt mode.
        *        It can be replaced by your own code.
        */
      __WFI();
    };
    return_status = EXEC_STATUS_OK;
    PRINTF("[INFO] Step 3: Interrupt detected on EXTI.\n");
  }
  else
  {
    PRINTF("[ERROR] Step 2: EXTI start error\n");
  }

  return return_status;
} /* end app_process */


/** ########## Step 3 ##########
  *  Defines the user callback function.
  *  This function is triggered when the EXTI interrupt happens according to the configured edge.
  */
static void UserDetectedExtiCallback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger)
{
  STM32_UNUSED(trigger);
  ExtiDetected = 1;
}


/** ########## Step 4 ##########
  * Deinitializes the GPIO before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  /* Stop the EXTI mode for the selected EXTI line */
  HAL_EXTI_Disable(pEXTI);

  PRINTF("[INFO] Step 4: Device deinitialization COMPLETED.\n");

  return EXEC_STATUS_OK;
} /* end app_deinit */
