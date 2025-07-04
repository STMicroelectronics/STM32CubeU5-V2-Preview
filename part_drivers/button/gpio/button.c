/**
  ******************************************************************************
  * @file    button.c
  * @brief   This file contains all the functions for the board Button
  *          whatever the STM32 family.
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
#include "button.h"

#if defined (BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)
static void button_exti_callback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger);
#endif /* BUTTON_CALLBACKS */

/**
  * @brief logical button initialization
  * @param p_button button object to initialize
  * @param id configuration id to apply to the button (used by @ref button_io_init)
  * @retval error status
  */
button_status_t button_init(button_t *p_button, uint32_t id)
{
  button_status_t status;
  p_button->id = id;
#if (defined BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)
  p_button->cb_ctx.cb = NULL;
#endif /* BUTTON_CALLBACKS */
  if (button_io_init(p_button) != 0)
  {
    status = BUTTON_ERROR;
  }
  else if (button_disableit(p_button) != BUTTON_OK)
  {
    status = BUTTON_ERROR;
  }
  else
  {
    status = BUTTON_OK;
  }
  return status;
}

/**
  * @brief low-level IO init function
  * @param p_button pointer to the button object to initialize
  * @retval 0 in case of success, -1 otherwise
  */
__WEAK int32_t button_io_init(button_t *p_button)
{
  (void)p_button; /* prevent the "unused argument" warning */
  return -1; /* this function must be overridden and always fails */
}

/**
  * @brief This function enables interrupt request on button event.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for selected button.
  *
  */
button_status_t button_enableit(button_t *p_button)
{
  /* Clear interrupt pending bit of the selected EXTI line. */
  HAL_EXTI_ClearPending(p_button->exti_handle, HAL_EXTI_TRIGGER_RISING_FALLING);

#if defined(BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)
  /* store the button pointer in the exti handle for retrieval by the callback function */
  HAL_EXTI_SetUserData(p_button->exti_handle, p_button);

  /* Start the selected EXTI line on Interrupt Mode. */
  if (HAL_EXTI_RegisterTriggerCallback(p_button->exti_handle, button_exti_callback) != HAL_OK)
  {
    return BUTTON_ERROR;
  }
#endif /* BUTTON_CALLBACKS */

  if (HAL_EXTI_Enable(p_button->exti_handle, HAL_EXTI_MODE_INTERRUPT) != HAL_OK)
  {
    return BUTTON_ERROR;
  }
  else
  {
    return BUTTON_OK;
  }
}

/**
  * @brief This function disables the interrupt for the button.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for selected button.
  *
  */
button_status_t button_disableit(button_t *p_button)
{
  button_status_t retval = BUTTON_OK;

  /* Stop the selected EXTI line. */
  if (HAL_EXTI_Disable(p_button->exti_handle) != HAL_OK)
  {
    retval = BUTTON_ERROR;
  }

  /* Clear interrupt pending bit of the selected EXTI line. */
  HAL_EXTI_ClearPending(p_button->exti_handle, HAL_EXTI_TRIGGER_RISING_FALLING);

  return retval;
}

/**
  * @brief This function returns the state of the button BUTTON_PRESSED or BUTTON_UNPRESSED.
  *
  * @param p_button  A pointer to the type button_t, that can be defined using the macro DEFINE_BUTTON
  * for selected button.
  *
  */
button_state_t button_get_state(button_t *p_button)
{
#if defined(BUTTON_DEBOUNCE) && (BUTTON_DEBOUNCE == 1)
  if ((p_button->last_event == HAL_EXTI_TRIGGER_RISING) && (p_button->active_state == HAL_GPIO_PIN_SET))
  {
    return BUTTON_PRESSED;
  }
  if ((p_button->last_event == HAL_EXTI_TRIGGER_FALLING) && (p_button->active_state == HAL_GPIO_PIN_RESET))
  {
    return BUTTON_PRESSED;
  }
  return BUTTON_UNPRESSED;
#else /* BUTTON_DEBOUNCE*/
  if (HAL_GPIO_ReadPin(p_button->port, p_button->pin) == p_button->active_state)
  {
    return BUTTON_PRESSED;
  }
  else
  {
    return BUTTON_UNPRESSED;
  }
#endif /* BUTTON_DEBOUNCE */
}

#if defined (BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)

static void button_exti_callback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger)
{
  button_t *p_button = (button_t *) HAL_EXTI_GetUserData(hexti);

  /* debounce management based on HAL_GetTick() */
#if defined(BUTTON_DEBOUNCE) && (BUTTON_DEBOUNCE == 1)
  uint32_t current_tick = HAL_GetTick();
  if (current_tick - p_button->last_event_tick >= p_button->debounce_duration)
  {
    p_button->last_event_tick = current_tick;
    p_button->last_event = trigger;
  }
  else /* this is a rebound, ignoring this event */
  {
    return;
  }
#endif /* BUTTON_DEBOUNCE */

  if (p_button->cb_ctx.cb != NULL)
  {
    /* call the user callback if appropriate */
    switch (p_button->cb_ctx.event)
    {
      case BUTTON_EVENT_PRESSED:
        if ((trigger == HAL_EXTI_TRIGGER_RISING && p_button->active_state == HAL_GPIO_PIN_SET)
            || (trigger == HAL_EXTI_TRIGGER_FALLING && p_button->active_state == HAL_GPIO_PIN_RESET))
        {
          p_button->cb_ctx.cb(p_button, p_button->cb_ctx.arg);
        }
        break;
      case BUTTON_EVENT_UNPRESSED:
        if ((trigger == HAL_EXTI_TRIGGER_RISING && p_button->active_state == HAL_GPIO_PIN_RESET)
            || (trigger == HAL_EXTI_TRIGGER_FALLING && p_button->active_state == HAL_GPIO_PIN_SET))
        {
          p_button->cb_ctx.cb(p_button, p_button->cb_ctx.arg);
        }
        break;
      case BUTTON_EVENT_ANY:
        p_button->cb_ctx.cb(p_button, p_button->cb_ctx.arg);
        break;
      default:
        break;
    }
  }
}

/**
  * @brief This function register a callback function for the button.
  * The callback function is called on the selected button event.
  */
button_status_t button_register_callback(button_t *p_button, button_callback_t callback, button_event_t event,
                                         void *arg)
{
  p_button->cb_ctx.cb = callback;
  p_button->cb_ctx.event = event;
  p_button->cb_ctx.arg = arg;

  HAL_EXTI_SetUserData(p_button->exti_handle, p_button);
  if (HAL_EXTI_RegisterTriggerCallback(p_button->exti_handle, button_exti_callback) == HAL_OK)
  {
    return BUTTON_OK;
  }
  else
  {
    return BUTTON_ERROR;
  }
}
#endif /* BUTTON_CALLBACKS */
