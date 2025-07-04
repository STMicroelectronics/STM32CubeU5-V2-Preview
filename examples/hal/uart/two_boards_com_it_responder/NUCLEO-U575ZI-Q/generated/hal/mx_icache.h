/**
  ******************************************************************************
  * @file           : mx_icache.h
  * @brief          : Header for mx_icache.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_ICACHE_H
#define MX_ICACHE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for ICACHE in HAL layer */
/******************************************************************************/
/**
  * @brief mx_icache_hal init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_icache_handle_t *mx_icache_hal_init(void);

/**
  * @brief  De-initialize icache instance and return it.
  */
void mx_icache_hal_deinit(void);

/**
  * @brief  Get the ICACHE object.
  * @retval Pointer on the ICACHE Handle
  */
hal_icache_handle_t *mx_icache_hal_gethandle(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_ICACHE_H */