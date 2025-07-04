/**
  ******************************************************************************
  * @file    tcpp01_io.h
  * @brief   tcpp01 header IO driver file for ADC
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
#ifndef TCPP01_IO_H
#define TCPP01_IO_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/**
  * @brief Macros definitions
  */
/* ADC conversion time out value (unit: ms) */
#define TCPP01_ADC_CONVERSION_TIMEOUT  10U

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
#define TCPP01_CALLBACKS 1
#endif /* USE_HAL_EXTI_USER_DATA */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

/* Exported types ------------------------------------------------------------*/

typedef struct tcpp01_io_s tcpp01_io_t;   /*!< IO structure type */

#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)
/** @param io_trigger: 0=RISING, 1=FALLING */

typedef void (*tcpp01_io_callback_t)(tcpp01_io_t *pio, uint8_t io_trigger, void *p_arg);  /*!< IO callback function pointer definition */

/**
  * @brief Callback context structure
  */
typedef struct
{
  tcpp01_io_callback_t io_callback;   /*!< IO callback function to register        */
  void *parg;                          /*!< Optional argument given to the callback */
} tcpp01_io_cb_ctx_t;
#endif /* TCPP01_CALLBACKS */

/**
  * @brief ADC EXTI IO interface structure
  */

struct tcpp01_io_s
{
  hal_exti_handle_t  *hexti;        /*!< EXTI HAL handle for FLT pin               */
  hal_adc_handle_t   *hadc;         /*!< ADC HAL handle for VBUS sensing           */
  uint32_t           dev_id;        /*!< Configuration ID                          */
  uint32_t           Ra;            /*!< VBUS voltage divider RA                   */
  uint32_t           Rb;            /*!< VBUS voltage divider RA                   */
  uint32_t           Vdd;           /*!< Value of VDD in mv                        */
  uint8_t            active_state;  /*!< Hardware active dead battery pin state    */
  hal_gpio_t         db_port;       /*!< Hardware dead battery port                */
  uint32_t           db_pin;        /*!< Hardware dead battery pin                 */
  IRQn_Type          irq_line;      /*!< TCPP01 interrupt request line             */
#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)
  tcpp01_io_cb_ctx_t     exti_cb_ctx;     /*!< EXTI callback */
#endif /* TCPP01_CALLBACKS */
};


int32_t tcpp01_io_init(tcpp01_io_t *pio);
void tcpp01_io_enable_dead_battery(tcpp01_io_t *pio);
void tcpp01_io_disable_dead_battery(tcpp01_io_t *pio);
uint32_t tcpp01_io_get_adc_value(tcpp01_io_t *pio);
uint32_t tcpp01_io_get_vbus_voltage(tcpp01_io_t *pio, uint32_t AdcValue);

int32_t tcpp01_io_stop(tcpp01_io_t *pio);
int32_t tcpp01_io_start(tcpp01_io_t *pio);
int32_t tcpp01_io_start_it(tcpp01_io_t *pio);
int32_t tcpp01_io_stop_it(tcpp01_io_t *pio);
void tcpp01_io_enable_irq(tcpp01_io_t *pio);
void tcpp01_io_disable_irq(tcpp01_io_t *pio);
void tcpp01_io_clear_irq(tcpp01_io_t *pio);
#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)
int32_t tcpp01_io_register_callback(tcpp01_io_t *pio, tcpp01_io_callback_t io_cb, void *p_arg);
#endif /* USE_TCPP01_CALLBACKS */

#ifdef __cplusplus
}
#endif

#endif /* TCPP01_IO_H */


