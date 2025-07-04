/**
  ******************************************************************************
  * file           : example.h
  * brief          : Header for example.c.
  *                  This file contains example-specific declarations to interface with main().
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EXAMPLE_H
#define EXAMPLE_H

/* Includes ------------------------------------------------------------------*/
#include <inttypes.h> /* PRIx8 macros family */
#include <stdio.h> /* printf */

#include "mx_hal_def.h"       /* aliases to the target-specific generated code */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
/* The volatile qualifier ensures the content of variables of this type is always visible in the debugger. */
typedef volatile enum
{
  EXEC_STATUS_ERROR   = -1, /* problem encountered         */
  EXEC_STATUS_UNKNOWN = 0,  /* default value               */
  EXEC_STATUS_INIT_OK = 1,  /* app_init ran as expected    */
  EXEC_STATUS_OK      = 2   /* application ran as expected */
} app_status_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** brief:  User application initialization.
  * retval: example status (see app_status_t)
  */
app_status_t app_init(void);

/** brief:  User application processing.
  * retval: example status (see app_status_t)
  */
app_status_t app_process(void);

/** brief:  User application de-init.
  * retval: example status (see app_status_t)
  */
app_status_t app_deinit(void);

/** logging macro - just redirects to printf()
  * libc's stdout is redirected to UART thanks to the Basic stdio utility.
  *
  * @user You can enable logs by defining USE_TRACE=1 in the build options.
  */
#if defined(USE_TRACE) && USE_TRACE != 0
#define PRINTF(...)    printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif /* defined(USE_TRACE) && USE_TRACE != 0 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXAMPLE_H */
