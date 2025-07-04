/**
  ******************************************************************************
  * file           : mx_led.h
  * brief          : Code generation for the LED part driver.
  ******************************************************************************
  * attention
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
#ifndef MX_LED_H
#define MX_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------ */
#include "led.h"
#include "mx_hal_def.h"

/* Exported macros ----------------------------------------------------------- */

/* LED names - GPIO flavor */
/* These names are just identifiers without a value.
 * The LED part driver uses those names to construct pin property macros.
 * e.g. `led_on(MX_STATUS_LED)` translates to
 * `HAL_GPIO_WritePin(MX_STATUS_LED_GPIO_PORT, MX_STATUS_LED_PIN, MX_STATUS_LED_ACTIVE_STATE)`.
 */

/* derived from the LED Instance */
#define MYLED_1                   MYLED_1
/* defined with a User Label */
#define MX_STATUS_LED                   MX_STATUS_LED

/* LED GPIO - pin property macros */
#define MYLED_1_GPIO_PORT          HAL_GPIOE
#define MYLED_1_PIN           HAL_GPIO_PIN_13
#define MYLED_1_ACTIVE_STATE  HAL_GPIO_PIN_SET
#define MYLED_1_INACTIVE_STATE  HAL_GPIO_PIN_RESET

#define MX_STATUS_LED_GPIO_PORT          MYLED_1_GPIO_PORT
#define MX_STATUS_LED_PIN           MYLED_1_PIN
#define MX_STATUS_LED_ACTIVE_STATE  MYLED_1_ACTIVE_STATE
#define MX_STATUS_LED_INACTIVE_STATE  MYLED_1_INACTIVE_STATE

#ifdef __cplusplus
}
#endif

#endif /* MX_LED_H */
