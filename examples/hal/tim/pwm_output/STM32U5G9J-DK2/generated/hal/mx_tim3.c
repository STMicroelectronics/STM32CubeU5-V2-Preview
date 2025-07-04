/**
  ******************************************************************************
  * @file           : mx_tim3.c
  * @brief          : Peripheral initialization
  *                   File per peripheral instance that is handling the peripheral
  *                   initialization and the IRQ handlers. Init parameters provided
  *                   as a set of defines configurable/generated for a given target
  *                   through the  hal_tim_settings.json and the config tool.
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
#include "mx_tim3.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_tim_handle_t hTIM3;
  
/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for TIM3 in HAL layer (SW instance MyTIM_1) */
/******************************************************************************/

hal_tim_handle_t *mx_tim3_hal_init(void)
{
  hal_tim_config_t config;

  if (HAL_TIM_Init(&hTIM3, HAL_TIM3) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_TIM3_EnableClock();

  /* Timer configuration to reach the output frequency at 24390 Hz */
  config.prescaler              = 159;
  config.counter_mode           = HAL_TIM_COUNTER_UP;
  config.period                 = 0x28;
  config.clock_division         = HAL_TIM_CLK_DIVISION_DIV1;
  config.repetition_counter     = 0;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  if (HAL_TIM_SetConfig(&hTIM3, &config) != HAL_OK)
  {
    return NULL;
  }

  /* Configure Channels */
  hal_tim_oc_channel_config_t oc_config;

  oc_config.polarity    = HAL_TIM_OC_HIGH;
  oc_config.idle_state  = HAL_TIM_OC_IDLE_STATE_RESET;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM3, HAL_TIM_CHANNEL_2, &oc_config) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x14;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM3, hal_tim_oc_channel_to_compare_unit(HAL_TIM_CHANNEL_2),
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  oc_config.polarity    = HAL_TIM_OC_HIGH;
  oc_config.idle_state  = HAL_TIM_OC_IDLE_STATE_RESET;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM3, HAL_TIM_CHANNEL_3, &oc_config) != HAL_OK)
  {
    return NULL;
  }

  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x10;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM3, hal_tim_oc_channel_to_compare_unit(HAL_TIM_CHANNEL_3),
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  /* Configure Master mode */
  /* HAL_TIM_SetTriggerOutput(&hTIM3, HAL_TIM_TRGO_RESET); */

  /* Configure Encoder interface */
  /* Configure the external trigger input */
  hal_tim_ext_trig_config_t ext_trig;
  ext_trig.source     = HAL_TIM_EXT_TRIG_TIM3_GPIO;
  ext_trig.polarity   = HAL_TIM_EXT_TRIG_NONINVERTED;
  ext_trig.prescaler  = HAL_TIM_EXT_TRIG_DIV1;
  ext_trig.filter     = HAL_TIM_FDIV1;
  if (HAL_TIM_SetExternalTriggerInput(&hTIM3, &ext_trig) != HAL_OK)
  {
    return NULL;
  }

  /* HAL_TIM_SetCaptureCompareDMAReqSource(&hTIM3, HAL_TIM_CC_DMAREQ_CC); */

  /* GPIO configuration for channel2 */
  /* GPIO configuration for channel3 */
  HAL_RCC_GPIOB_EnableClock();


    hal_gpio_config_t  gpio_config;

  /**
    TIM3 GPIO Configuration
    PB5   --------->  TIM3_CH2
    PB0   --------->  TIM3_CH3
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_2;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_5 | HAL_GPIO_PIN_0, &gpio_config);


  return &hTIM3;
}

void mx_tim3_hal_deinit(void)
{
  (void)HAL_TIM_DeInit(&hTIM3);

  HAL_RCC_TIM3_Reset();

  HAL_RCC_TIM3_DisableClock();

  /* Deinitialization of TIM3: TIM3_CH2  */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_5);

  /* Deinitialization of TIM3: TIM3_CH3  */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_0);



}

hal_tim_handle_t *mx_tim3_hal_gethandle(void)
{
  return &hTIM3;
}

