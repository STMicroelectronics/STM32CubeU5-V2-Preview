/**
  ******************************************************************************
  * @file    basic_stdio_itf_io.h
  * @brief   public API header for the Basic stdio utility
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
#ifndef BASIC_STDIO_ITF_IO_H
#define BASIC_STDIO_ITF_IO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
/* Internal functions ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
  * @defgroup Basicstdio_Interface_API
  * @{
  */

/**
  * @brief interface initialization function
  * @param pObj pointer on an HAL handle.
  */
void interface_io_Init(void *pObj);

/**
  * @brief interface to send data.
  * @param pObj pointer on an HAL handle.
  * @param Ptr  data pointer
  * @param Size number of data to transfer
  */
uint32_t interface_io_Send(void *pObj, const uint8_t *Ptr, uint16_t Size);

/**
  * }@
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BASIC_STDIO_ITF_IO_H */
