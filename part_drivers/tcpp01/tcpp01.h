/**
  ******************************************************************************
  * @file    TCPP01.h
  * @brief   This file contains all the functions prototypes for the
  *          TCPP01.c driver.
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
#ifndef TCPP01_H
#define TCPP01_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "tcpp01_io.h"
#include <stddef.h>


/* Exported types ------------------------------------------------------------*/

typedef struct tcpp01_obj_s tcpp01_obj_t;   /*!< TCPP01 object structure type */

#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)
typedef void (*tcpp01_callback_t)(tcpp01_obj_t *pobj, void *p_arg);  /*!< callback function pointer definition */

/**
  * @brief Callback context structure
  */
typedef struct
{
  tcpp01_callback_t callback;   /*!< Callback function to register           */
  void *parg;                   /*!< Optional argument given to the callback */
} tcpp01_cb_ctx_t;
#endif /* TCPP01_CALLBACKS */

struct tcpp01_obj_s
{
  tcpp01_io_t        pio;               /*!< IO interface                 */
  uint8_t            is_initialized;    /*!< Init state                   */
#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)
  tcpp01_cb_ctx_t     cb_rising_ctx;     /*!< callback context for exti rising event  */
  tcpp01_cb_ctx_t     cb_falling_ctx;    /*!< callback context for exti falling event */
#endif /* TCPP01_CALLBACKS */
};

typedef enum
{
  TCPP01_OK = 0,
  TCPP01_ERROR,
} tcpp01_status_t;


tcpp01_status_t tcpp01_init(tcpp01_obj_t *pobj, uint32_t dev_id);
tcpp01_status_t tcpp01_deinit(tcpp01_obj_t *pobj);

tcpp01_status_t tcpp01_enable_it(tcpp01_obj_t *pobj);
tcpp01_status_t tcpp01_disable_it(tcpp01_obj_t *pobj);
void tcpp01_clear_it(tcpp01_obj_t *pobj);
#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)
tcpp01_status_t tcpp01_register_cable_plugged_callback(tcpp01_obj_t *pobj, tcpp01_callback_t pcb, void *p_arg);
tcpp01_status_t tcpp01_register_cable_unplugged_callback(tcpp01_obj_t *pobj, tcpp01_callback_t pcb, void *p_arg);
#endif /* TCPP01_CALLBACKS */

tcpp01_status_t tcpp01_get_vbus_voltage(tcpp01_obj_t *pobj, uint32_t *p_voltage_mv);
tcpp01_status_t tcpp01_start(tcpp01_obj_t *pobj);
tcpp01_status_t tcpp01_stop(tcpp01_obj_t *pobj);

#ifdef __cplusplus
}
#endif

#endif /* TCPP01_H */

