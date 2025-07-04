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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EXAMPLE_H */
