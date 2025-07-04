/**
  ******************************************************************************
  * @file           : mx_cortex_nvic.c
  * @brief          : STM32 CORTEX NVIC body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "mx_cortex_nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
system_status_t mx_cortex_nvic_init(void)
{
  /* Configure the Priority grouping */
  HAL_CORTEX_NVIC_SetPriorityGrouping(HAL_CORTEX_NVIC_PRIORITY_GROUP_4);

  return SYSTEM_OK;
}

/******************************************************************************/
/*                            Systick Handler                                 */
/******************************************************************************/
/**
  * @brief  This function handles SysTick Handler.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_CORTEX_SYSTICK_IRQHandler();
}

/******************************************************************************/
/*                              NMI Handler                                   */
/******************************************************************************/
/**
  * @brief  This function handles NMI Handler.
  */
void NMI_IRQHandler(void)
{

  // user code if required
  while(1);
}

/* IRQ handler for PPPi are generated inside mx_pppi.c */
