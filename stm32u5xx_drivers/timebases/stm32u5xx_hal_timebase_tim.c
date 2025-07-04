/**
  ******************************************************************************
  * @file    stm32_hal_timebase_tim.c
  * @brief This pattern read only components that are not configurable, neither need to be customized by the user
  ******************************************************************************
  * @attention
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

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_hal_def.h"

/* Privates types ------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/*! Check HAL tick frequency value */
#define IS_TICK_FREQ(freq) (((freq) == HAL_TICK_FREQ_10HZ)     \
                            || ((freq) == HAL_TICK_FREQ_100HZ) \
                            || ((freq) == HAL_TICK_FREQ_1KHZ))

/*! Check HAL tick priority value */
#define IS_TICK_PRIO(prio) ((prio) <= ((1UL << __NVIC_PRIO_BITS) - 1UL))


/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern hal_tick_freq_t uwTickFreq;
static hal_tim_handle_t *hTIM = NULL;

/* Private function prototypes -----------------------------------------------*/


#if defined(USE_HAL_TIM_REGISTER_CALLBACKS) && (USE_HAL_TIM_REGISTER_CALLBACKS == 1U)
void TimeBase_TIM_UpdateCallback(hal_tim_handle_t *htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the TIMx as a time base source.
  *         The time source is configured  to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
  * @param  TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
hal_status_t HAL_InitTick(hal_tick_freq_t tick_freq,
                          uint32_t tick_priority)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_TICK_FREQ(tick_freq));
  ASSERT_DBG_PARAM(IS_TICK_PRIO(tick_priority));

  switch (tick_freq)
  {
    case HAL_TICK_FREQ_1KHZ:
      uwTickFreq = HAL_TICK_FREQ_1KHZ;
      hTIM = tim_timebase_1ms_init();
      break;

    case HAL_TICK_FREQ_100HZ:
      uwTickFreq = HAL_TICK_FREQ_100HZ;
      hTIM = tim_timebase_10ms_init();
      break;

    case HAL_TICK_FREQ_10HZ:
      uwTickFreq = HAL_TICK_FREQ_10HZ;
      hTIM = tim_timebase_100ms_init();
      break;

    default:
      status = HAL_INVALID_PARAM;
  }

  if (status == HAL_OK)
  {
    if (tick_priority < (1UL << __NVIC_PRIO_BITS))
    {
#if defined(USE_HAL_TIM_REGISTER_CALLBACKS) && (USE_HAL_TIM_REGISTER_CALLBACKS == 1U)
      HAL_TIM_RegisterUpdateCallback(hTIM, TimeBase_TIM_UpdateCallback);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */

      HAL_CORTEX_NVIC_SetPriority(TIM_TIMEBASE_IRQN, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
      HAL_TIM_Start_IT(hTIM);
    }
  }

  return status;
}

#if defined(USE_HAL_TIM_REGISTER_CALLBACKS) && (USE_HAL_TIM_REGISTER_CALLBACKS == 1U)
void TimeBase_TIM_UpdateCallback(hal_tim_handle_t *htim)
#else
void HAL_TIM_UpdateCallback(hal_tim_handle_t *htim)
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
{
  STM32_UNUSED(htim);

  HAL_IncTick();
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIMx update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
  HAL_TIM_Stop_IT(hTIM);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIMx update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  HAL_TIM_Start_IT(hTIM);
}
