/**
  ******************************************************************************
  * @file    stm32u5xx_hal_timebase_rtc_alarm_template.c
  * @brief   HAL time base based on the hardware RTC_ALARM Template.
  *
  *          This file overrides the native HAL time base functions (defined as weak)
  *          to use the RTC ALARM for time base generation:
  *           + Initializes the RTC peripheral to increment the seconds registers each 1ms
  *           + The alarm is configured to assert an interrupt when the RTC reaches 1ms
  *           + HAL_IncTick is called at each Alarm event
  *           + HSE (default), LSE or LSI can be selected as RTC clock source
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
 @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
    This file must be copied to the application folder and modified as follows:
    (#) Rename it to 'stm32u5xx_hal_timebase_rtc_alarm.c'
    (#) Add this file and the RTC HAL drivers to your project and uncomment
       USE_HAL_RTC_MODULE define in stm32u5xx_hal_conf.h

    [..]
    (@) HAL RTC alarm and HAL RTC wakeup drivers can not be used with low power modes:
        The wake up capability of the RTC can be intrusive in case of prior low power mode
        configuration requiring different wake up sources.
        Application/Example behavior is no more guaranteed
    (@) The stm32u5xx_hal_timebase_tim use is recommended for the Applications/Examples
          requiring low power modes

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"
/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_TimeBase_RTC_Alarm_Template  HAL TimeBase RTC Alarm Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Uncomment the line below to select the appropriate RTC Clock source for your application:
  + RTC_CLOCK_SOURCE_HSE: can be selected for applications requiring timing precision.
  + RTC_CLOCK_SOURCE_LSE: can be selected for applications with low constraint on timing
                          precision.
  + RTC_CLOCK_SOURCE_LSI: can be selected for applications with low constraint on timing
                          precision.
  */
/* #define RTC_CLOCK_SOURCE_HSE */
/* #define RTC_CLOCK_SOURCE_LSE */
/* #define RTC_CLOCK_SOURCE_LSI */

/* The time base must be 1ms
   Time base = ((RTC_ASYNCH_PREDIV + 1) * (RTC_SYNCH_PREDIV + 1)) / RTC_CLOCK
*/
#if defined (RTC_CLOCK_SOURCE_HSE)
#define RTC_ASYNCH_PREDIV      99U
#define RTC_SYNCH_PREDIV        4U
#elif defined (RTC_CLOCK_SOURCE_LSE)
#define RTC_ASYNCH_PREDIV       0U
#define RTC_SYNCH_PREDIV       32U
#elif defined (RTC_CLOCK_SOURCE_LSI)
#define RTC_ASYNCH_PREDIV       0U
#define RTC_SYNCH_PREDIV       31U
#else
#error Please select the RTC Clock source
#endif /* RTC_CLOCK_SOURCE_LSE */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void RTC_IRQHandler(void);
#if (USE_HAL_RTC_REGISTER_CALLBACKS == 1U)
void TimeBase_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
#endif /* USE_HAL_RTC_REGISTER_CALLBACKS */
/* Private functions ---------------------------------------------------------*/

/**
  * @brief This function configures the time base frequency and interruption priority.
  * @warning HAL tick is updated from interrupts at regular time intervals.
  *        Care must be taken if HAL_Delay() is called from a peripheral interruption process:
  *        the tick interrupt line must have higher priority (numerically lower) than the peripheral interrupt,
  *        otherwise the caller interruption process will be blocked.
  * @note  This function is called at the beginning of program by HAL_Init()
  *        or at any time when system core clock is modified (for instance, called by HAL RCC driver when needed).
  * @note  This function is declared as __WEAK to be overridden in case of other
  *        implementations in user file.
  * @param tick_freq  Tick frequency with a **hal_tick_freq_t** type (to keep current value, use global variable
  *        @ref uwTickFreq)
  * @param tick_priority Tick interrupt priority (to keep current value, use global variable @ref uwTickPrio)
  * @retval HAL_OK HAL time base correctly configured
  * @retval HAL_ERROR Error occurred during HAL time base configuration (refer to HAL services called in this function)
  * @retval HAL_INVALID_PARAM Input parameter(s) not in expected range
  */
hal_status_t HAL_InitTick(hal_tick_freq_t tick_freq, uint32_t tick_priority)
{
  /*
    Driver is under construction
    */
  return HAL_ERROR;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling RTC ALARM interrupt.
  * @retval None
  */
void HAL_SuspendTick(void)
{
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling RTC ALARM interrupt.
  * @retval None
  */
void HAL_ResumeTick(void)
{
}

/**
  * @brief  This function handles RTC ALARM interrupt request.
  * @retval None
  */
void RTC_IRQHandler(void)
{
}

/**
  * @}
  */

/**
  * @}
  */
