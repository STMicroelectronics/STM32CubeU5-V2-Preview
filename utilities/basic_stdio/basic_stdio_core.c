/**
  ******************************************************************************
  * @file    basic_stdio_core.c
  * @brief   This file contains the basic stdio utility functions based on ITM.
  ******************************************************************************
  * @attention
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
#include "basic_stdio_core.h"
#include "basic_stdio_itf_io.h"

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
void *io_interface_Object = NULL;
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

void UTIL_BASIC_STDIO_Init(void *pobj)
{
  /* keep object value */
  io_interface_Object = pobj;
  interface_io_Init(io_interface_Object);
}

#if defined(WRITE_PROTO)
WRITE_PROTO(file, ptr, len)
{
  (void)(file); /* prevent "unused variable" warnings */
  return interface_io_Send(io_interface_Object, (const uint8_t *)ptr, len);
}
#else
int fputc(int c, FILE *f)
{
  (void)(f); /* prevent "unused variable" warnings */

  uint32_t res ;
  res = interface_io_Send(io_interface_Object, (const uint8_t *)&c, 1);
  if (res != 1)
  {
    return EOF;
  }
  return res;
}
#endif /* WRITE_PROTO */
