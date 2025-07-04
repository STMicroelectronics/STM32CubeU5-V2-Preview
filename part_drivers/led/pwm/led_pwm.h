/**
  ******************************************************************************
  * @file    led_pwm.h
  * @brief   This file contains all the functions prototypes for the board LEDs
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LED_PWM_H
#define LED_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/

/**
  * @brief Structure defining the property for a LED PWM.
  */
typedef struct
{
  hal_gpio_t              port;           /*!< GPIO port configured with a pwm channel to drive the LED  */
  uint32_t                pin;            /*!< GPIO pin configured with as pwm channel to drive the LED  */
  hal_tim_handle_t       *htim;           /*!< handle of the timer used to drive the LED */
  hal_tim_channel_t       pwm_channel;    /*!< Timer PWM CHANNEL used to drive the LED  */
  uint16_t                tim_prescaler;  /*!< timer prescaler used to have the timer input clock set to 512MHz */
  uint32_t                id;             /*!< device ID to ensure correct initialization */
} led_pwm_t;


/**
  * @brief Enumeration defining 3 possible speeds for the LED dynamic features, such as fading and blinking.
  */
typedef enum
{
  LED_SPEED_FAST = 1,    /*!< Select fast speed */
  LED_SPEED_MEDIUM = 2,  /*!< Select medium speed */
  LED_SPEED_SLOW = 4     /*!< Select slow speed */
} led_speed_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported function ---------------------------------------------------------*/
void led_pwm_init(led_pwm_t *p_led_pwm, uint32_t id);

void led_pwm_io_init(led_pwm_t *p_led_pwm);

void led_pwm_on(led_pwm_t *p_led_pwm);
void led_pwm_off(led_pwm_t *p_led_pwm);
void led_pwm_toggle(led_pwm_t *p_led_pwm);
void led_pwm_set_brightness(led_pwm_t *p_led_pwm, uint8_t brightness);
void led_pwm_fade(led_pwm_t *p_led_pwm, led_speed_t speed);
void led_pwm_blink(led_pwm_t *p_led_pwm, led_speed_t speed);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LED_PWM_H */
