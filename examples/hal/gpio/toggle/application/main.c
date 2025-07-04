/**
  ******************************************************************************
  * file           : main.c
  * brief          : Main program body
  *                  main() calls the target system initialization, then calls the example entry point.
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
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* @user: configure the delay in milliseconds between 2 loop rounds */
#define EXAMPLE_LOOP_DELAY_MS 100U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
app_status_t ExecStatus = EXEC_STATUS_UNKNOWN; /* application status */

/* Private functions prototype -----------------------------------------------*/
static void error_handler(void);

/** brief:  The application entry point.
  * retval: none but we specify int to comply with C99 standard
  */
int main(void)
{
  /** System Init: this generated code placed in targets folder initializes your system.
    * It calls the initialization (and sets the initial configuration) of the peripherals.
    * You can use STM32CubeMX to generate and call this code or not in this project.
    * It also contains the HAL initialization and the initial clock configuration.
    */
  if (mx_system_init() != SYSTEM_OK)
  {
    ExecStatus = EXEC_STATUS_ERROR; /* memorize the error */
  }
  else
  {
    /** Example execution: this hardware and IDE agnostic code contains the scenario that we demonstrate.
      * This is the applicative code showing how to use the peripheral (functionality-wise).
      * You might copy/paste it in your own application,
      * while you might keep on generating the initialization and configuration code with STM32CubeMX.
      */
    ExecStatus = app_init();

    /* Run endlessly if no error occurs */
    while (ExecStatus != EXEC_STATUS_ERROR)
    {
      ExecStatus = app_process();

      HAL_Delay(EXAMPLE_LOOP_DELAY_MS);
    } /* end while */
  } /* end applicative part */

  /* Reaching this point means a problem occurred */
  error_handler();

  /* This point must not be reached */
  return (0);
} /* end main */

/** ----------------------------------------------------------
  * The function below is used to report the example status.
  * ---------------------------------------------------------- */
/** brief:  Error notification
  * retval: None (infinite loop)
  */
static void error_handler(void)
{
  while (1);
} /* end error_handler */

/** Redefines the HardFault handler from the startup file.
  * brief:  Hard Fault Handler
  * retval: None (infinite loop)
  *
  * The default handler is redefined here so that:
  * 1. The example status can be updated.
  * 2. You can easily set a breakpoint to investigate the issue.
  */
void HardFault_Handler(void)
{
  /* The example encountered an unrecoverable error */
  ExecStatus = EXEC_STATUS_ERROR;

  /* Unrecoverable error: infinite loop */
  while (1);
}
