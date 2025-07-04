/**
  ******************************************************************************
  * @file           : mx_tim2.c
  * @brief          : Peripheral initialization
  *                   File per peripheral instance that is handling the peripheral
  *                   initialization and the IRQ handlers. Init parameters provided
  *                   as a set of defines configurable/generated for a given target
  *                   through the  hal_tim_settings.json and the config tool.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "mx_tim2.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_tim_handle_t hTIM2;
  
/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for TIM2 in HAL layer (SW instance MyTIM_1) */
/******************************************************************************/

hal_tim_handle_t *mx_tim2_hal_init(void)
{
  hal_tim_config_t config;

  if (HAL_TIM_Init(&hTIM2, HAL_TIM2) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_TIM2_EnableClock();

  /* Timer configuration to reach the output frequency at 2000 Hz */
  config.prescaler              = 15999;
  config.counter_mode           = HAL_TIM_COUNTER_UP;
  config.period                 = 0x4;
  config.clock_division         = HAL_TIM_CLK_DIVISION_DIV1;
  config.repetition_counter     = 0;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  if (HAL_TIM_SetConfig(&hTIM2, &config) != HAL_OK)
  {
    return NULL;
  }

  /* Configure Channels */
  /* Configure Master mode */
  /* HAL_TIM_SetTriggerOutput(&hTIM2, HAL_TIM_TRGO_RESET); */

  /* Configure Encoder interface */
  /* Configure the external trigger input */
  hal_tim_ext_trig_config_t ext_trig;
  ext_trig.source     = HAL_TIM_EXT_TRIG_TIM2_GPIO;
  ext_trig.polarity   = HAL_TIM_EXT_TRIG_NONINVERTED;
  ext_trig.prescaler  = HAL_TIM_EXT_TRIG_DIV1;
  ext_trig.filter     = HAL_TIM_FDIV1;
  if (HAL_TIM_SetExternalTriggerInput(&hTIM2, &ext_trig) != HAL_OK)
  {
    return NULL;
  }

  /* HAL_TIM_SetCaptureCompareDMAReqSource(&hTIM2, HAL_TIM_CC_DMAREQ_CC); */


    /* Enable the Timer global interrupt */
  HAL_CORTEX_NVIC_SetPriority(TIM2_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(TIM2_IRQn);


  return &hTIM2;
}

void mx_tim2_hal_deinit(void)
{
  /* Disable Timer global interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(TIM2_IRQn);

  (void)HAL_TIM_DeInit(&hTIM2);

  HAL_RCC_TIM2_Reset();

  HAL_RCC_TIM2_DisableClock();



}

hal_tim_handle_t *mx_tim2_hal_gethandle(void)
{
  return &hTIM2;
}

/******************************************************************************/
/*                     TIM2 global interrupt                    */
/******************************************************************************/
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&hTIM2);
}

