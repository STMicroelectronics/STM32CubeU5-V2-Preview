/**
  ******************************************************************************
  * @file    tcpp01.c
  * @modify  MCD Application Team
  * @brief   TCPP01 driver file
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
#include "tcpp01.h"
#include "interfaces/adc_exti/tcpp01_io.h"


/**
  * @brief  Initialize the TCPP01 component and configure the needed hardware resources
  * @param  pobj     : Part object pointer.
  * @param  dev_id   : configuration ID
  * @retval Part status
  */
tcpp01_status_t tcpp01_init(tcpp01_obj_t *pobj, uint32_t dev_id)
{
  pobj->pio.dev_id = dev_id;
  /* Initialize the IO BUS layer */
  if (pobj->is_initialized == 0U)
  {
    if (tcpp01_io_init(&pobj->pio) != 0)
    {
      return TCPP01_ERROR;
    }
    /* disable dead battery */
    tcpp01_io_disable_dead_battery(&pobj->pio);
    pobj->is_initialized = 1U;
  }

  return TCPP01_OK;
}

/**
  * @brief  Deinitialize the TCPP01 component
  * @param  pobj     : Part object pointer.
  * @retval Part status
  */
tcpp01_status_t tcpp01_deinit(tcpp01_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  if (pobj->is_initialized != 0U)
  {
    /* enable dead battery */
    tcpp01_io_enable_dead_battery(&(pobj->pio));
    /* Update State */
    pobj->is_initialized = 0U;
    /* Update part status */
    ret = TCPP01_OK;
  }

  /* Return part status */
  return ret;
}

/**
  * @brief Clear, Enable and Start interrupt request on type-C cable plug event.
  * @param  pobj       : Part object pointer.
  * @retval Part status
  */
tcpp01_status_t tcpp01_enable_it(tcpp01_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  /* Clear interrupt pending bit of the selected EXTI line */
  tcpp01_io_clear_irq(&(pobj->pio));

  /* Enable external interrupt pin */
  tcpp01_io_enable_irq(&(pobj->pio));

  /* Start interrupt request */
  if (tcpp01_io_start_it(&(pobj->pio)) == 0)
  {
    /* Update part status */
    ret = TCPP01_OK;
  }

  /* Return part status */
  return ret;
}

/**
  * @brief Clear, Disable and Stop the interrupt for type-C cable plugged event.
  * @param  pobj       : Part object pointer.
  * @retval Part status
  */
tcpp01_status_t tcpp01_disable_it(tcpp01_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  /* Clear interrupt pending bit of the selected EXTI line */
  tcpp01_io_clear_irq(&(pobj->pio));

  /* Disable external interrupt pin */
  tcpp01_io_disable_irq(&(pobj->pio));

  /* Stop interrupt request */
  if (tcpp01_io_stop_it(&(pobj->pio)) == 0)
  {
    /* Update part status */
    ret = TCPP01_OK;
  }

  /* Return part status */
  return ret;
}

/**
  * @brief Clear interrupt request on type-C cable detect event.
  * @param  pobj       : Part object pointer.
  */
void tcpp01_clear_it(tcpp01_obj_t *pobj)
{
  /* Enable external interrupt pin */
  tcpp01_io_clear_irq(&(pobj->pio));
}

#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)

static void tcpp01_io_falling_callback(tcpp01_io_t *pio, uint8_t io_trigger, void *p_arg)
{
  (void)(pio);
  tcpp01_obj_t *pobj = p_arg;
  /* io_trigger = 1 means falling edge */
  if (io_trigger == 1U)
  {
    pobj->cb_falling_ctx.callback(pobj, pobj->cb_falling_ctx.parg);
  }
  tcpp01_clear_it(pobj);
}

static void tcpp01_io_rising_callback(tcpp01_io_t *pio, uint8_t io_trigger, void *p_arg)
{
  (void)(pio);
  tcpp01_obj_t *pobj = p_arg;
  /*io_trigger = 0 means rising edge */
  if (io_trigger == 0U)
  {
    pobj->cb_rising_ctx.callback(pobj, pobj->cb_rising_ctx.parg);
  }
  tcpp01_clear_it(pobj);
}

/**
  * @brief This function registers a callback function for the tcpp01.
  * @param pobj  : Part object pointer.
  * @param pcb   : Callback function
  * @param p_arg   : Optional argument given to the callback
  * @retval      Part status
  */

tcpp01_status_t tcpp01_register_cable_plugged_callback(tcpp01_obj_t *pobj, tcpp01_callback_t pcb, void *p_arg)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  pobj->cb_falling_ctx.callback = pcb;
  pobj->cb_falling_ctx.parg = p_arg;
  /* Register falling callback */
  if (tcpp01_io_register_callback(&(pobj->pio), tcpp01_io_falling_callback, pobj) == 0)
  {
    /* Update part status */
    ret = TCPP01_OK;
  }

  /* Return part status */
  return ret;
}

/**
  * @brief This function registers a callback function for the tcpp01.
  * @param pobj  : Part object pointer.
  * @param pcb   : Callback function
  * @param p_arg   : Optional argument given to the callback
  * @retval      Part status
  */

tcpp01_status_t tcpp01_register_cable_unplugged_callback(tcpp01_obj_t *pobj, tcpp01_callback_t pcb, void *p_arg)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  pobj->cb_rising_ctx.callback = pcb;
  pobj->cb_rising_ctx.parg = p_arg;
  /* Register rising callback */
  if (tcpp01_io_register_callback(&(pobj->pio), tcpp01_io_rising_callback, pobj) == 0)
  {
    /* Update part status */
    ret = TCPP01_OK;
  }

  /* Return part status */
  return ret;
}
#endif /* USE_TCPP01_CALLBACKS */


/**
  * @brief  Get actual voltage level measured on the VBUS line.
  * @param  pobj : Pointer to component object
  * @param  p_voltage_mv : Pointer on measured voltage level (in mV)
  * @retval Part status
  */
tcpp01_status_t tcpp01_get_vbus_voltage(tcpp01_obj_t *pobj, uint32_t *p_voltage_mv)
{
  uint32_t Voltage;
  uint32_t AdcValue;

  AdcValue = tcpp01_io_get_adc_value(&pobj->pio);

  Voltage = tcpp01_io_get_vbus_voltage(&pobj->pio, AdcValue);

  *p_voltage_mv = Voltage;

  return TCPP01_OK;
}

/**
  * @brief This function starts the ADC conversion to obtain the actual voltage level
  * measured on the VBUS line.
  * @param  pobj       : Part object pointer.
  * @retval Part status
  */
tcpp01_status_t  tcpp01_start(tcpp01_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  if (tcpp01_io_start(&pobj->pio) == 0)
  {
    ret = TCPP01_OK;
  }

  /* Return part status */
  return ret;
}

/**
  * @brief This function stops the ADC conversion.
  * @param  pobj       : Part object pointer.
  * @retval Part status
  */
tcpp01_status_t  tcpp01_stop(tcpp01_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp01_status_t ret = TCPP01_ERROR;

  if (tcpp01_io_stop(&pobj->pio) == 0)
  {
    ret = TCPP01_OK;
  }


  /* Return part status */
  return ret;
}

