/**
  ******************************************************************************
  * @file    basic_stdio_itfio_itm.c
  * @brief   This file contains the interface io functions based on ITM.
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
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

void interface_io_Init(void *pObj)
{
  /* Empty */
  (void)(pObj); /* prevent "unused variable" warnings */
}

uint32_t interface_io_Send(void *pObj, const uint8_t *Ptr, uint16_t Size)
{
  (void)(pObj); /* prevent "unused variable" warnings */

  if (
    !(DCB->DEMCR & DCB_DEMCR_TRCENA_Msk)
    || !(ITM->TCR & ITM_TCR_ITMENA_Msk)
    || !(ITM->TER & (1UL >> 31))
  )
  {
    return 0;
  }

  for (uint32_t i = 0; i < Size; i++)
  {
    ITM_SendChar(Ptr[i]);
  }
  return Size;
}