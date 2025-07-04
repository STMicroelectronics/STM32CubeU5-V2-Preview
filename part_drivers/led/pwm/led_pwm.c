/**
  ******************************************************************************
  * @file    led_pwm.c
  * @brief   PWM LED Parts Driver
  *          This file contains all the functions for the board LEDs
  *          driven by PWM, whatever the STM32 family.
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
#include "led_pwm.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define PATTERN_SIZE                   128U  /* Number of value. */
#define PATTERN_MAX_VALUE             2048U  /* Maximum value for a pattern element. */
#define PRESCALER_MULTIPLIER_FAST        1U  /* Prescaler multiplier value for fast speed. */
#define PRESCALER_MULTIPLIER_MEDIUM      4U  /* Prescaler multiplier value for medium speed. */
#define PRESCALER_MULTIPLIER_SLOW        8U  /* Prescaler multiplier value for slow speed. */


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t TimDmaRunning = 0;
/* Private constants ---------------------------------------------------------*/
static const uint16_t PWM_Sine_Pattern [PATTERN_SIZE] =
{
  1024, 1074, 1124, 1174, 1224, 1273, 1321, 1369, 1416, 1462, 1507, 1550, 1593, 1634, 1674, 1712, 1748, 1783, 1816,
  1846, 1875, 1902, 1927, 1950, 1970, 1988, 2004, 2017, 2028, 2037, 2043, 2047, 2048, 2047, 2043, 2037, 2028, 2017,
  2004, 1988, 1970, 1950, 1927, 1902, 1875, 1846, 1816, 1783, 1748, 1712, 1674, 1634, 1593, 1550, 1507, 1462, 1416,
  1369, 1321, 1273, 1224, 1174, 1124, 1074, 1024, 974, 924, 874, 824, 775, 727, 679, 632, 586, 541, 498, 455, 414, 374,
  336, 300, 265, 232, 202, 173, 146, 121, 98, 78, 60, 44, 31, 20, 11, 5, 1, 0, 1, 5, 11, 20, 31, 44, 60, 78, 98, 121,
  146, 173, 202, 232, 265, 300, 336, 374, 414, 455, 498, 541, 586, 632, 679, 727, 775, 824, 874, 924, 974
};

/**
  * @brief pattern array used to generate a PWM Square
  */
static const uint16_t PWM_Square_Pattern [PATTERN_SIZE] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
  2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
  2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048,
  2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048, 2048
};

/* Private functions prototype -----------------------------------------------*/

static void start_led_pwm_dma_pattern(const led_pwm_t *p_led_pwm,
                                      led_speed_t speed,
                                      const uint16_t PWM_DMA_Pattern [PATTERN_SIZE]);
static hal_status_t stop_led_pwm_dma_pattern(const led_pwm_t *p_led_pwm);
/* Private function ----------------------------------------------------------*/

static void start_led_pwm_dma_pattern(const led_pwm_t *p_led_pwm,
                                      led_speed_t speed,
                                      const uint16_t PWM_DMA_Pattern [PATTERN_SIZE])
{
  hal_tim_oc_compare_unit_t compare_unit;
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;
  hal_tim_dmaburst_base_addr_reg_t  tim_dmaburst_base_addr_ccrx;
  uint16_t prescaler = UINT16_MAX;

  tim_dmaburst_base_addr_ccrx = hal_tim_channel_to_dmaburst_base_address(p_led_pwm->pwm_channel);
  hal_tim_dmaburst_config_t tim_dma_burst = { .address = tim_dmaburst_base_addr_ccrx,
                                              .source = HAL_TIM_DMABURST_UPD,
                                              .length  = HAL_TIM_DMABURST_1TRANSFER,
                                            };

  HAL_TIM_SetConfigDMABurst(p_led_pwm->htim, &tim_dma_burst);

  switch (speed)
  {
    case LED_SPEED_FAST:
      if (p_led_pwm->tim_prescaler < (UINT16_MAX / PRESCALER_MULTIPLIER_FAST))
      {
        prescaler = p_led_pwm->tim_prescaler * PRESCALER_MULTIPLIER_FAST;
      }
      break;
    case LED_SPEED_SLOW:
      if (p_led_pwm->tim_prescaler < (UINT16_MAX / PRESCALER_MULTIPLIER_SLOW))
      {
        prescaler = p_led_pwm->tim_prescaler * PRESCALER_MULTIPLIER_SLOW;
      }
      break;
    default:
    case LED_SPEED_MEDIUM:
      if (p_led_pwm->tim_prescaler < (UINT16_MAX / PRESCALER_MULTIPLIER_MEDIUM))
      {
        prescaler = p_led_pwm->tim_prescaler * PRESCALER_MULTIPLIER_MEDIUM;
      }
      break;
  }

  HAL_TIM_SetPrescaler(p_led_pwm->htim, prescaler);

  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = PWM_DMA_Pattern[0];
  compare_unit = hal_tim_oc_channel_to_compare_unit(p_led_pwm->pwm_channel);
  HAL_TIM_OC_SetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);
  if (HAL_OK != HAL_TIM_StartDMABurst(p_led_pwm->htim,
                                      HAL_TIM_DMABURST_WRITE,
                                      (uint8_t *)PWM_DMA_Pattern,
                                      sizeof(PWM_DMA_Pattern[0]) * PATTERN_SIZE))
  {
    return;
  }

  TimDmaRunning = 1;

}

/**
  * @brief This function stop the
  * of the LED, the LED is set to inactive state.
  * The TIM peripheral must be initialized beforehand, and his 'input clock must be set to 1MHz' to work as expected.
  * Usually it is initialized by auto generated code otherwise
  * it is up to the user to correctly initialize the PWM peripheral.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @retval None
  */

static hal_status_t stop_led_pwm_dma_pattern(const led_pwm_t *p_led_pwm)
{
  hal_status_t ret_status = HAL_OK;
  if (TimDmaRunning == 1)
  {
    ret_status = HAL_TIM_StopDMABurst(p_led_pwm->htim);
    TimDmaRunning = 0;
  }
  return ret_status;
}
/**l
  * @} LED_PWM_PART_Driver_Private_Functions
  */
/**
  * @brief pattern array used to generate a PWM sinus
  */
/* Exported functions --------------------------------------------------------*/
/**
  * @brief This function does a logical initialization
  * of the LED, the LED is set to inactive state.
  * The TIM peripheral must be initialized beforehand, and his 'input clock must be set to 1MHz' to work as expected.
  * Usually it is initialized by auto generated code otherwise
  * it is up to the user to correctly initialize the PWM peripheral.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @retval None
  */
void led_pwm_init(led_pwm_t *p_led_pwm, uint32_t id)
{
  p_led_pwm->id = id;
  led_pwm_io_init(p_led_pwm);

  hal_tim_oc_compare_unit_t compare_unit;
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;
  compare_unit = hal_tim_oc_channel_to_compare_unit(p_led_pwm->pwm_channel);

  /* Starts timer  PWM period value */
  if (HAL_OK != HAL_TIM_SetPeriod(p_led_pwm->htim, PATTERN_MAX_VALUE - 1))
  {
    goto _led_pwm_init_exit;
  }
  /* Configures channel compare units */
  oc_compare_unit_config.mode = HAL_TIM_OC_FORCED_INACTIVE;
  oc_compare_unit_config.pulse = 0;
  if (HAL_OK != HAL_TIM_OC_SetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config))
  {
    goto _led_pwm_init_exit;
  }


  if (HAL_OK != HAL_TIM_SetCaptureCompareDMAReqSource(p_led_pwm->htim, HAL_TIM_CC_DMAREQ_UPD))
  {
    goto _led_pwm_init_exit;
  }

  /* Starts Output compare channel configuration */
  if (HAL_OK != HAL_TIM_OC_StartChannel(p_led_pwm->htim, p_led_pwm->pwm_channel))
  {
    goto _led_pwm_init_exit;
  }

  /* Starts timer  */
  if (HAL_OK != HAL_TIM_Start(p_led_pwm->htim))
  {
    goto _led_pwm_init_exit;
  }

_led_pwm_init_exit:
  return;
}

__WEAK void led_pwm_io_init(led_pwm_t *p_led_pwm)
{
  (void) p_led_pwm;
}

/**
  * @brief  This function sets the LED on.
  *
  * @param p_led_pwm  A pointer to the type led_pwm_t,...
  *
  * @retval None
  */

void led_pwm_on(led_pwm_t *p_led_pwm)
{
  hal_tim_oc_compare_unit_t compare_unit;
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  compare_unit = hal_tim_oc_channel_to_compare_unit(p_led_pwm->pwm_channel);

  if (HAL_OK != stop_led_pwm_dma_pattern(p_led_pwm))
  {
    return;
  }

  /* Configures channel compare units */
  HAL_TIM_OC_GetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);
  oc_compare_unit_config.mode = HAL_TIM_OC_FORCED_ACTIVE;
  HAL_TIM_OC_SetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);
}

/**
  * @brief  This function sets the LED off.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @retval None
  */
void led_pwm_off(led_pwm_t *p_led_pwm)
{
  hal_tim_oc_compare_unit_t compare_unit;
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  compare_unit = hal_tim_oc_channel_to_compare_unit(p_led_pwm->pwm_channel);

  if (HAL_OK != stop_led_pwm_dma_pattern(p_led_pwm))
  {
    return;
  }

  HAL_TIM_OC_GetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);
  oc_compare_unit_config.mode = HAL_TIM_OC_FORCED_INACTIVE;
  HAL_TIM_OC_SetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);
}

/**
  * @brief  This function toggles the state of the LED.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @retval None
  */
void led_pwm_toggle(led_pwm_t *p_led_pwm)
{
  hal_tim_oc_compare_unit_t compare_unit;
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  compare_unit = hal_tim_oc_channel_to_compare_unit(p_led_pwm->pwm_channel);

  if (HAL_OK != stop_led_pwm_dma_pattern(p_led_pwm))
  {
    return;
  }

  HAL_TIM_OC_GetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);

  if (oc_compare_unit_config.mode == HAL_TIM_OC_FORCED_INACTIVE)
  {
    oc_compare_unit_config.mode = HAL_TIM_OC_FORCED_ACTIVE;
  }
  else
  {
    /** When the timer mode is different from inactive (led off) is considered as "active" (led on, dimming...)
      * so the we toggle the mode to forced inactive (led off).
      */
    oc_compare_unit_config.mode = HAL_TIM_OC_FORCED_INACTIVE;
  }
  HAL_TIM_OC_SetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);
}

/**
  * @brief  This function toggles the state of the LED.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @param brightness  An 8 bits integer value defining the value of the brightness. Value 0 turn off the led.
  *
  * @retval None
  */
void led_pwm_set_brightness(led_pwm_t *p_led_pwm, uint8_t brightness)
{
  hal_tim_oc_compare_unit_t compare_unit;
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;
  uint32_t tim_period = 0;

  compare_unit = hal_tim_oc_channel_to_compare_unit(p_led_pwm->pwm_channel);


  HAL_TIM_OC_GetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);

  /* tim_period = ARR + 1 */
  tim_period = HAL_TIM_GetPeriod(p_led_pwm->htim) + 1;

  oc_compare_unit_config.mode = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = (tim_period * (uint32_t)brightness) / (uint32_t)UINT8_MAX;
  HAL_TIM_OC_SetConfigCompareUnit(p_led_pwm->htim, compare_unit, &oc_compare_unit_config);

}

/**
  * @brief  This function make the LED fading.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @param speed  Set the the fading speed of the LED.
  *
  * @retval None
  */
void led_pwm_fade(led_pwm_t *p_led_pwm, led_speed_t speed)
{
  start_led_pwm_dma_pattern(p_led_pwm, speed, PWM_Sine_Pattern);
}


/**
  * @brief  This function make the LED blinking.
  *
  * @param p_led_pwm  A pointer to the LED IO structure defined in the file mx_led.h.
  *
  * @param speed  Set the the blinking speed of the LED.
  *
  * @retval None
  */
void led_pwm_blink(led_pwm_t *p_led_pwm, led_speed_t speed)
{
  start_led_pwm_dma_pattern(p_led_pwm, speed, PWM_Square_Pattern);
}
