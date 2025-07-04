/**
  ******************************************************************************
  * @file    tcpp01_io.c
  * @brief   TCPP01 IO driver file for ADC
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
#include <stdint.h>

#include "tcpp01_io.h"


/**
  * @brief  Initialize the TCPP01 IO ADC flavor
  * @param  pio : the IO instance object
  * @retval -1 (always fails)
  */
__WEAK int32_t tcpp01_io_init(tcpp01_io_t *pio)
{
  (void)(pio);
  return  -1;
}

/**
  * @brief Dead battery Pin control.
  * @param  pio      : the IO instance object
  * @param  state    : the pin state
  */
static void tcpp01_io_set_db_pin(tcpp01_io_t *pio, uint8_t state)
{
  /* pin state */
  hal_gpio_pin_state_t pin_state;

  if (state == 1U)
  {
    pin_state = HAL_GPIO_PIN_SET;
  }
  else
  {
    /* reset pin in other case */
    pin_state = HAL_GPIO_PIN_RESET;
  }

  /* Update Pin State */
  HAL_GPIO_WritePin(pio->db_port, pio->db_pin, pin_state);

}

/**
  * @brief Enable the TCPP01 dead batteries, open the CC switches.
  * @param  pio      : the IO instance object
  */
void tcpp01_io_enable_dead_battery(tcpp01_io_t *pio)
{
  /* Power ON */
  tcpp01_io_set_db_pin(pio, (pio->active_state == 0U) ? 1U : 0U);
}

/**
  * @brief Disable the TCPP01 dead batteries, close the CC switches.
  * @param  pio      : the IO instance object
  */
void tcpp01_io_disable_dead_battery(tcpp01_io_t *pio)
{
  /* Power OFF */
  tcpp01_io_set_db_pin(pio, pio->active_state);
}

/**
  * @brief  Get actual ADC value measured on the VBUS line.
  * @param  pio : the IO instance object
  * @retval measured adc value
  */
uint32_t tcpp01_io_get_adc_value(tcpp01_io_t *pio)
{
  uint32_t AdcValue;
  hal_adc_config_t Config;
  uint32_t AdcFullScale;


  /* Retrieve the ADC conversion data */
  HAL_ADC_GetConfig(pio->hadc, &Config);
  AdcFullScale = (uint32_t)(HAL_ADC_DIGITAL_SCALE(Config.resolution));
  /* Retrieve the ADC conversion data */
  AdcValue = (uint32_t)HAL_ADC_REG_GetValue(pio->hadc);
  AdcValue = (uint32_t)((AdcValue * VDD_VALUE) / AdcFullScale);

  return AdcValue;
}

/**
  * @brief This function starts the ADC conversion.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise.
  */
int32_t tcpp01_io_start(tcpp01_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  if (HAL_ADC_REG_StartConv(pio->hadc) == HAL_OK)
  {
    if (HAL_ADC_REG_PollForConv(pio->hadc, TCPP01_ADC_CONVERSION_TIMEOUT) == HAL_OK)
    {
      /* Update part status */
      ret_val = 0;
    }
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function stops the ADC conversion.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise.
  */
int32_t tcpp01_io_stop(tcpp01_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  if (HAL_ADC_REG_StopConv(pio->hadc) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief  Get actual voltage level measured on the VBUS line.
  * @note   Voltage level is measured though a voltage divider.
  * @note   AdcValue = Voltage * Rb /(Ra + Rb)
  * @param  pio : the IO instance object
  * @param  adc_value : measured ADC value
  * @retval measured voltage value
  */
uint32_t tcpp01_io_get_vbus_voltage(tcpp01_io_t *pio, uint32_t adc_value)
{
  uint32_t Voltage;

  Voltage = (uint32_t)(adc_value * (pio->Ra + pio->Rb) / pio->Rb);

  return Voltage;
}


/**
  * @brief This function starts interrupt request on type-C Cable plug event.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise.
  */
int32_t tcpp01_io_start_it(tcpp01_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Start the selected EXTI line on Interrupt Mode. */
  if (HAL_EXTI_Enable(pio->hexti, HAL_EXTI_MODE_INTERRUPT) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function stops interrupt request on type-C cable plug event.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise.
  */
int32_t tcpp01_io_stop_it(tcpp01_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Stop the selected EXTI line. */
  if (HAL_EXTI_Disable(pio->hexti) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function enables interrupt request on type-C cable plug event.
  * @param  pio         : the IO instance object
  */
void tcpp01_io_enable_irq(tcpp01_io_t *pio)
{
  /* Enable NVIC interrupt request for the selected EXTI line.*/
  HAL_CORTEX_NVIC_EnableIRQ(pio->irq_line);
}

/**
  * @brief This function disables the interrupt for type-C cable plug event.
  * @param  pio         : the IO instance object
  */
void tcpp01_io_disable_irq(tcpp01_io_t *pio)
{
  /* Disable NVIC interrupt request for the selected EXTI line.*/
  HAL_CORTEX_NVIC_DisableIRQ(pio->irq_line);
}

/**
  * @brief This function Clears interrupt pending bit of the selected EXTI line.
  * @param  pio         : the IO instance object
  */
void tcpp01_io_clear_irq(tcpp01_io_t *pio)
{
  /* Clear interrupt pending bit of the selected EXTI line. */
  HAL_EXTI_ClearPending(pio->hexti, HAL_EXTI_TRIGGER_RISING_FALLING);
}

#if defined (TCPP01_CALLBACKS) && (TCPP01_CALLBACKS == 1)

static void EXTI_Callback(hal_exti_handle_t *p_exti, hal_exti_trigger_t trigger)
{
  tcpp01_io_t *pio = (tcpp01_io_t *)HAL_EXTI_GetUserData(p_exti);
  pio->exti_cb_ctx.io_callback(pio, (trigger == HAL_EXTI_TRIGGER_FALLING), pio->exti_cb_ctx.parg);
}

/**
  * @brief Registration of exti falling callback.
  * @param pio     : The IO instance object.
  * @param  io_cb  : Callback function to be registered.
  * @param  p_arg    : Optional argument given to the callback
  * @retval 0 in case of success, -1 otherwise.
  */

int32_t tcpp01_io_register_callback(tcpp01_io_t *pio, tcpp01_io_callback_t io_cb, void *p_arg)
{
  pio->exti_cb_ctx.io_callback = io_cb;
  pio->exti_cb_ctx.parg = p_arg;
  HAL_EXTI_SetUserData(pio->hexti, pio);

  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Register callback*/
  if (HAL_EXTI_RegisterTriggerCallback(pio->hexti, EXTI_Callback) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }
  /* Return part io status */
  return ret_val;
}
#endif /* USE_TCPP01_CALLBACKS */
