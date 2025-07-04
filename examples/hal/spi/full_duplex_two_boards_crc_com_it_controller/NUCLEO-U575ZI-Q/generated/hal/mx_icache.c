/**
  ******************************************************************************
  * @file           : mx_icache.c
  * @brief          : ICACHE Peripheral initialization
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
#include "mx_icache.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_icache_handle_t hICACHE;

/******************************************************************************/
/* Exported functions for ICACHE in HAL layer (SW instance MyICACHE_1) */
/******************************************************************************/
hal_icache_handle_t *mx_icache_hal_init(void)
{
  if (HAL_ICACHE_Init(&hICACHE, HAL_ICACHE) != HAL_OK)
  {
    return NULL;
  }
  /* Associativity mode set to default value 2-ways */



  return &hICACHE;
}

void mx_icache_hal_deinit(void)
{
  (void)HAL_ICACHE_DeInit(&hICACHE);
}

hal_icache_handle_t *mx_icache_hal_gethandle(void)
{
  return &hICACHE;
}


