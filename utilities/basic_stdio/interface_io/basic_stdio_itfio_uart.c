/**
  ******************************************************************************
  * @file    _basic_stdio_itfio_uart.c
  * @brief   This file contains the io interface functions based on UART.
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
#include "basic_stdio_itf_io.h"

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*
 * Static (private) variable holding the UART handle to use. Initialized to NULL.
 */

/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

void interface_io_Init(void *pObj)
{
  (void)pObj;
}

uint32_t interface_io_Send(void *pObj, const uint8_t *Ptr, uint16_t Size)
{
  if (HAL_UART_Transmit(pObj, Ptr, Size, 0xFFFFU) == HAL_OK)
  {
    return Size;
  }
  else
  {
    return 0;
  }
}