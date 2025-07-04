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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
app_status_t ExecStatus = EXEC_STATUS_UNKNOWN; /* application status */

/* Private functions prototype -----------------------------------------------*/

/** brief:  The application entry point.
  * retval: none but we specify int to comply with C99 standard
  */
int main(void)
{
  /** System Init: this generated code placed in targets folder initializes your system.
    * It calls the initialization (and sets the initial configuration) of the peripherals.
    * You can use STM32CubeMX to generate and call this code or not in this project.
    * It also contains the HAL|LL initialization and the initial clock configuration.
    */
  if (mx_system_init() != SYSTEM_OK)
  {
    ExecStatus = EXEC_STATUS_ERROR; /* memorize the error */
  }
  else
  {
    ExecStatus = app_init();

    /* Run endlessly times if no error occurs */
    while ((ExecStatus != EXEC_STATUS_ERROR))
    {
      ExecStatus = app_process();
    } /* end while */
  } /* end applicative part */


  /* This point must not be reached */
  return (0);
} /* end main */

/** The functions below are used to report the example status.
  * ----------------------------------------------------------
  */

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
