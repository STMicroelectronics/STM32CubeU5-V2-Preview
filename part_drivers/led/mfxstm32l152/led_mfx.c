/**
  ******************************************************************************
  * @file    led_mfx.c
  * @author  MCD Application Team
  * @brief   GPIO LED Parts Driver
  *          This file contains all the functions for the board LEDs
  *          driven by GPIO, whatever the STM32 family.
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

/* Includes ------------------------------------------------------------------*/
#include "led_mfx.h"

/**
  * @brief LED MFX driver init (logical initialization, not HW resource init)
  * @param pled LED object
  * @param id configuration ID to apply
  * @note This function handles the configuration of the output pin on the MFX, but not the resources of the main STM32 MCU.
  * @retval error status
  */
led_mfx_status_t led_mfx_init(led_mfx_t *pled, uint32_t id)
{
  pled->id = id;

  if (led_mfx_io_init(pled) != 0)
  {
    return LED_MFX_ERROR;
  }

  led_mfx_status_t retval = LED_MFX_OK;
  mfxstm32l152_pin_config_t pin_cfg =
  {
    .io_pin = pled->pin,
    .io_mode = MFXSTM32L152_GPIO_MODE_OUTPUT_PP,
    .io_pull = MFXSTM32L152_GPIO_NOPULL,
  };
  if (mfxstm32l152_pin_start(pled->mfx_obj, pled->pin) != MFXSTM32L152_OK)
  {
    retval = LED_MFX_ERROR;
  }
  else if (mfxstm32l152_pin_set_config(pled->mfx_obj, &pin_cfg) != MFXSTM32L152_OK)
  {
    retval = LED_MFX_ERROR;
  }
  else if (led_mfx_off(pled) != LED_MFX_OK)
  {
    retval = LED_MFX_ERROR;
  }

  return retval;
}

/**
  * @brief Low-level initialization function: fills the pio structure according to its .id value.
  * @param pled LED object
  * @retval -1 (always fails)
  * @note this function must be overridden with a proper implementation
  */
__WEAK int32_t led_mfx_io_init(led_mfx_t *pled)
{
  (void)pled;
  return -1;
}

/**
  * @brief Turns the LED on.
  * @param pled LED object
  * @retval error status
  */
led_mfx_status_t led_mfx_on(led_mfx_t *pled)
{
  if (mfxstm32l152_pin_write(pled->mfx_obj, pled->pin, pled->active_state) == MFXSTM32L152_OK)
  {
    return LED_MFX_OK;
  }
  else
  {
    return LED_MFX_ERROR;
  }
}

/**
  * @brief Turns the LED off.
  * @param pled LED object
  * @retval error status
  */
led_mfx_status_t led_mfx_off(led_mfx_t *pled)
{
  if (mfxstm32l152_pin_write(pled->mfx_obj, pled->pin,
                             pled->active_state == MFXSTM32L152_PIN_SET ? MFXSTM32L152_PIN_RESET : MFXSTM32L152_PIN_SET) == MFXSTM32L152_OK)
  {
    return LED_MFX_OK;
  }
  else
  {
    return LED_MFX_ERROR;
  }
}

/**
  * @brief Toggles the LED state.
  * @param pled LED object
  * @retval error status
  */
led_mfx_status_t led_mfx_toggle(led_mfx_t *pled)
{
  mfxstm32l152_gpio_pin_state_t current_state;
  led_mfx_status_t retval = LED_MFX_OK;
  if (mfxstm32l152_pin_read(pled->mfx_obj, pled->pin, &current_state) != MFXSTM32L152_OK)
  {
    retval = LED_MFX_ERROR;
  }
  else if (mfxstm32l152_pin_write(pled->mfx_obj, pled->pin,
                                  current_state == MFXSTM32L152_PIN_SET ? MFXSTM32L152_PIN_RESET : MFXSTM32L152_PIN_SET) != MFXSTM32L152_OK)
  {
    retval = LED_MFX_ERROR;
  }
  return retval;
}
