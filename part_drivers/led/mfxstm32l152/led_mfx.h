/**
  ******************************************************************************
  * @file    led_mfx.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the board LEDs
  *          driven with IO Expender, whatever the STM32 family.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LED_IOE_H
#define LED_IOE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "mfxstm32l152.h"

/**
  * @brief LED IOE (MFXSTM32L152) object structure
  */
typedef struct
{
  uint32_t                      id;            /*!< configuration id             */
  uint32_t                      pin;           /*!< IOE pin driving the LED      */
  mfxstm32l152_gpio_pin_state_t active_state;  /*!< pin state to turn on the LED */
  mfxstm32l152_obj_t            *mfx_obj;      /*!< IOE object handled           */
} led_mfx_t;

/**
  * @brief LED MFX status enum
  */
typedef enum
{
  LED_MFX_OK,
  LED_MFX_ERROR,
} led_mfx_status_t;

led_mfx_status_t led_mfx_init(led_mfx_t *pled, uint32_t id);

led_mfx_status_t led_mfx_on(led_mfx_t *pled);
led_mfx_status_t led_mfx_off(led_mfx_t *pled);
led_mfx_status_t led_mfx_toggle(led_mfx_t *pled);

int32_t led_mfx_io_init(led_mfx_t *p_led);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LED_IOE_H */
