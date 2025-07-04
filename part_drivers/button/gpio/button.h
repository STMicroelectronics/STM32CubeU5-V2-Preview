/**
  ******************************************************************************
  * @file    button.h
  * @brief   This file contains all the functions prototypes for the board
  *          button driven by GPIO, whatever the STM32 family.
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
#ifndef BUTTON_H
#define BUTTON_H


/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Debounce support enabled by default */
#ifndef BUTTON_DEBOUNCE
#define BUTTON_DEBOUNCE 1
#endif /* BUTTON_DEBOUNCE */

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/**
  * @brief Enumeration defining the state of a Button
  */
typedef enum
{
  BUTTON_UNPRESSED = 0,  /*!< Indicate that the button state is not pressed */
  BUTTON_PRESSED         /*!< Indicate that the button state is pressed */
} button_state_t;

/**
  * @brief Enumeration representing the button state change event, used to register callbacks function.
  */
typedef enum
{
  BUTTON_EVENT_PRESSED = 0,       /*!< Event when the button state changes from unpressed to pressed  */
  BUTTON_EVENT_UNPRESSED,         /*!< Event when the button state changes from pressed to unpressed */
  BUTTON_EVENT_ANY                /*!< Event when the button state changes */
} button_event_t;

typedef enum
{
  BUTTON_OK,
  BUTTON_ERROR,
} button_status_t;

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
#define BUTTON_CALLBACKS 1
#endif /* USE_HAL_EXTI_USER_DATA */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

typedef struct button_s button_t;

#if defined (BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)
typedef void (*button_callback_t)(button_t *button, void *arg);
typedef struct
{
  button_callback_t cb;  /**< callback executed from EXTI interrupt */
  button_event_t    event; /**< event to react to (pressed, unpressed, any) */
  void *arg;              /**< optional argument given to that callback */
} button_ctx_t;
#endif /* BUTTON_CALLBACKS */

/**
  * @brief Structure defining the properties for a Button.
  */
struct button_s
{
  uint32_t             id;              /*!< LED GPIO device Id */
  hal_gpio_t            port;           /*!< Button input GPIO port */
  uint16_t              pin;            /*!< Button input GPIO pin */
  hal_gpio_pin_state_t  active_state;   /*!< Button input GPIO pin state (high or low) define the button active state */
  hal_exti_handle_t    *exti_handle;    /*!< EXTI handle for asynchronous features */
#if defined (BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)
  button_ctx_t          cb_ctx;
#endif /* BUTTON_CALLBACKS */
#if defined (BUTTON_DEBOUNCE) && (BUTTON_DEBOUNCE == 1)
  uint32_t debounce_duration;
  volatile uint32_t last_event_tick;
  volatile hal_exti_trigger_t last_event;
#endif /* BUTTON_DEBOUNCE */
};

/* Exported functions ---------------------------------------------------------*/

button_status_t button_init(button_t *p_button, uint32_t id);

int32_t button_io_init(button_t *p_button);

#if defined (BUTTON_CALLBACKS) && (BUTTON_CALLBACKS == 1)
button_status_t button_register_callback(button_t *p_button, button_callback_t callback, button_event_t event,
                                         void *arg);
#endif /* BUTTON_CALLBACKS */

button_state_t button_get_state(button_t *p_button);
button_status_t button_enableit(button_t *p_button);
button_status_t button_disableit(button_t *p_button);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BUTTON_H */
