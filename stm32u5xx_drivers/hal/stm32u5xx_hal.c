/**
  ******************************************************************************
  * @file    stm32u5xx_hal.c
  * @brief   HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of HAL module:
  *           + Initialization and de-initialization functions
  *           + HAL tick operation functions
  *           + HAL driver and device identification functions
  *
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
#include "stm32u5xx_ll_bus.h"
#if defined(USE_HAL_FLASH_PREFETCH) && (USE_HAL_FLASH_PREFETCH == 1)
#include "stm32u5xx_ll_flash.h"
#endif /* USE_HAL_FLASH_PREFETCH */

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
# How to use the HAL module driver

## The HAL module (also called HAL generic) main features:

- System configuration to make device ready for other HAL modules operation
- HAL time base (used by other HAL modules for timeout)
- Identification features (HAL driver version, device identification data)

## Configuration inside the HAL driver

Config defines            | Description           | Default value      | Note
------------------------- | --------------------- | ------------------ | -----------------------------------------------
USE_ASSERT_DBG_PARAM      | from PreProcessor env | None               | When defined, enable the params assert
USE_HAL_CHECK_PARAM       | from hal_conf.h       | 0                  | Enable the runtime check parameters
TICK_INT_PRIORITY         | from hal_conf.h       | bitfield range max | HAL tick interrupt priority (lowest by default)
USE_HAL_FLASH_PREFETCH    | from hal_conf.h       | 0                  | When set, Flash prefetch is enabled

  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup HAL_Private_Constants HAL Private Constants
  * @{
  */
/*! Reset all AHB1_GRP1 peripherals (except system ones needed for code execution) */
#if defined(LL_AHB1_GRP1_PERIPH_DCACHE2)
#define AHB1_GRP1_PERIPH_RESET (LL_AHB1_GRP1_PERIPH_ALL & ~(LL_AHB1_GRP1_PERIPH_SRAM1 \
                                                            | LL_AHB1_GRP1_PERIPH_DCACHE1 \
                                                            | LL_AHB1_GRP1_PERIPH_DCACHE2 \
                                                            | LL_AHB1_GRP1_PERIPH_BKPSRAM \
                                                            | LL_AHB1_GRP1_PERIPH_FLASH))
#else
#define AHB1_GRP1_PERIPH_RESET (LL_AHB1_GRP1_PERIPH_ALL & ~(LL_AHB1_GRP1_PERIPH_SRAM1 \
                                                            | LL_AHB1_GRP1_PERIPH_DCACHE1 \
                                                            | LL_AHB1_GRP1_PERIPH_BKPSRAM \
                                                            | LL_AHB1_GRP1_PERIPH_FLASH))
#endif /* defined(LL_AHB1_GRP1_PERIPH_DCACHE2) */

/*! Reset all AHB2_GRP1 peripherals (except system ones needed for code execution) */
#if defined(LL_AHB2_GRP1_PERIPH_SRAM3)
#define AHB2_GRP1_PERIPH_RESET (LL_AHB2_GRP1_PERIPH_ALL & ~(LL_AHB2_GRP1_PERIPH_SRAM2 \
                                                            | LL_AHB2_GRP1_PERIPH_SRAM3))
#else
#define AHB2_GRP1_PERIPH_RESET (LL_AHB2_GRP1_PERIPH_ALL & ~(LL_AHB2_GRP1_PERIPH_SRAM2))
#endif /* defined(LL_AHB2_GRP1_PERIPH_SRAM3) */

/*! Reset all AHB2_GRP2 peripherals (except system ones needed for code execution) */
#if defined(LL_AHB2_GRP2_PERIPH_SRAM5) && defined(LL_AHB2_GRP2_PERIPH_SRAM6)
#define AHB2_GRP2_PERIPH_RESET (LL_AHB2_GRP2_PERIPH_ALL & ~(LL_AHB2_GRP2_PERIPH_SRAM5 \
                                                            | LL_AHB2_GRP2_PERIPH_SRAM6))
#elif defined(LL_AHB2_GRP2_PERIPH_SRAM5)
#define AHB2_GRP2_PERIPH_RESET (LL_AHB2_GRP2_PERIPH_ALL & ~(LL_AHB2_GRP2_PERIPH_SRAM5))
#else
#define AHB2_GRP2_PERIPH_RESET (LL_AHB2_GRP2_PERIPH_ALL)
#endif /* defined(LL_AHB2_GRP2_PERIPH_SRAM5) && defined(LL_AHB2_GRP2_PERIPH_SRAM6) */

/*! Reset all AHB3_GRP1 peripherals (except system ones needed for code execution) */
#define AHB3_GRP1_PERIPH_RESET (LL_AHB3_GRP1_PERIPH_ALL & ~(LL_AHB3_GRP1_PERIPH_SRAM4 \
                                                            | LL_AHB3_GRP1_PERIPH_GTZC2))

/*! Reset all APB1_GRP1 peripherals (except system ones needed for code execution) */
#define APB1_GRP1_PERIPH_RESET (LL_APB1_GRP1_PERIPH_ALL &~ LL_APB1_GRP1_PERIPH_WWDG)
/*! Reset all APB1_GRP2 peripherals (except system ones needed for code execution) */
#define APB1_GRP2_PERIPH_RESET (LL_APB1_GRP2_PERIPH_ALL)
/*! Reset all APB2_GRP1 peripherals (except system ones needed for code execution) */
#define APB2_GRP1_PERIPH_RESET (LL_APB2_GRP1_PERIPH_ALL)
/*! Reset all APB3_GRP1 peripherals (except system ones needed for code execution) */
#define APB3_GRP1_PERIPH_RESET (LL_APB3_GRP1_PERIPH_ALL)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */

/*! Check HAL tick frequency value */
#define IS_TICK_FREQ(freq) (((freq) == HAL_TICK_FREQ_10HZ) \
                            || ((freq) == HAL_TICK_FREQ_100HZ) \
                            || ((freq) == HAL_TICK_FREQ_1KHZ))

/*! Check HAL tick priority value */
#define IS_TICK_PRIO(prio) ((prio) <= ((1UL << __NVIC_PRIO_BITS) - 1UL))

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup HAL_Exported_Variables_init HAL Exported Variables initialization
  * @{
  * @ref HAL_Exported_Variables
  */
volatile uint32_t uwTick;
uint32_t uwTickPrio = ((1UL << __NVIC_PRIO_BITS) - 1UL); /* Initial value: low priority */
hal_tick_freq_t uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  This subsection provides a set of functions allowing to initialize and deinitialize the HAL module:

  - Function HAL_Init() must be called at the beginning of the program start to make device ready for other HAL modules
    operation. It configures:
    - HAL time base with default parameters: HAL tick from SysTick, interrupt enable, period 1ms
    - System generic features (NVIC priority grouping configuration, ...)

  - Function HAL_DeInit() can be called (optional) to revert HAL configuration.

  - Function HAL_InitTick() is called by HAL_Init() with HAL default parameters and by HAL RCC when system clock
    is updated.
    User can call it from application with different parameters.
    User can override it (function declared as __WEAK) to use HAL tick with different clock source (timer, RTC, ...)
  */

/**
  * @brief  Initialize the HAL module and make device ready to use the various HAL modules.
  * @note   HAL_Init() function is called at the beginning of program after reset and before
  *         the clock configuration.
  * @note   In the default implementation the System Timer (Systick) is used as source of time base.
  *         The Systick configuration is based on MSI clock, as MSI is the clock
  *         used after a system Reset and the NVIC configuration is set to Priority group 4.
  *         Once done, time base tick starts incrementing: the tick variable counter is incremented
  *         each 1ms in the SysTick_Handler() interrupt handler.
  * @retval HAL_OK HAL correctly initialized
  * @retval HAL_ERROR Error occurred during HAL initialization process (refer to HAL services called in this function)
  */
hal_status_t HAL_Init(void)
{
#if defined(USE_HAL_FLASH_PREFETCH) && (USE_HAL_FLASH_PREFETCH == 1)
  /* Configure Flash prefetch */
  LL_FLASH_EnablePrefetch(FLASH);
#endif /* USE_HAL_FLASH_PREFETCH */

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HAL_RCC_GetSYSCLKFreq() >> AHBPrescTable[LL_RCC_GetAHBPrescaler()];


  /* Set SysTick clock source to CPU internal free running clock */
  HAL_CORTEX_SYSTICK_SetClkSource(HAL_CORTEX_SYSTICK_CLKSOURCE_INTERNAL);

  HAL_CORTEX_NVIC_SetPriorityGrouping(HAL_CORTEX_NVIC_PRIORITY_GROUP_4);

  /* Use SysTick as time base source and configure 1ms tick */
  if (HAL_InitTick(HAL_TICK_FREQ_DEFAULT, TICK_INT_PRIORITY) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  DeInitialize the HAL module.
  * @note   Call of this function is optional
  * @retval HAL_OK
  */
hal_status_t HAL_DeInit(void)
{
  /* Reset all peripherals (except system ones needed for code execution) */
  LL_AHB1_GRP1_ForceReset(AHB1_GRP1_PERIPH_RESET);
  LL_AHB2_GRP1_ForceReset(AHB2_GRP1_PERIPH_RESET);
  LL_AHB2_GRP2_ForceReset(AHB2_GRP2_PERIPH_RESET);
  LL_AHB3_GRP1_ForceReset(AHB3_GRP1_PERIPH_RESET);
  LL_APB1_GRP1_ForceReset(APB1_GRP1_PERIPH_RESET);
  LL_APB1_GRP2_ForceReset(APB1_GRP2_PERIPH_RESET);
  LL_APB2_GRP1_ForceReset(APB2_GRP1_PERIPH_RESET);
  LL_APB3_GRP1_ForceReset(APB3_GRP1_PERIPH_RESET);

  LL_AHB1_GRP1_ReleaseReset(AHB1_GRP1_PERIPH_RESET);
  LL_AHB2_GRP1_ReleaseReset(AHB2_GRP1_PERIPH_RESET);
  LL_AHB2_GRP2_ReleaseReset(AHB2_GRP2_PERIPH_RESET);
  LL_AHB3_GRP1_ReleaseReset(AHB3_GRP1_PERIPH_RESET);
  LL_APB1_GRP1_ReleaseReset(APB1_GRP1_PERIPH_RESET);
  LL_APB1_GRP2_ReleaseReset(APB1_GRP2_PERIPH_RESET);
  LL_APB2_GRP1_ReleaseReset(APB2_GRP1_PERIPH_RESET);
  LL_APB3_GRP1_ReleaseReset(APB3_GRP1_PERIPH_RESET);


  return HAL_OK;
}

/**
  * @brief This function configures the time base frequency and interrupt priority.
  * @param tick_freq  Tick frequency with a **hal_tick_freq_t** type (to keep current value, use global variable
  *        @ref uwTickFreq)
  * @param tick_priority Tick interrupt priority (to keep current value, use global variable @ref uwTickPrio)
  * @note  This function is called at the beginning of program by HAL_Init()
  *        or at any time when system core clock is modified (for instance, called by HAL RCC driver when needed).
  * @note  This function is declared as __WEAK to be overridden in case of other
  *        implementations in user file.
  * @warning HAL tick is updated from interrupts at regular time intervals.
  *        Care must be taken if HAL_Delay() is called from a peripheral interrupt process:
  *        the tick interrupt line must have higher priority (numerically lower) than the peripheral interrupt,
  *        otherwise the caller interrupt process will be blocked.
  * @retval HAL_OK HAL time base correctly configured
  * @retval HAL_ERROR Error occurred during HAL time base configuration (refer to HAL services called in this function)
  */
__WEAK hal_status_t HAL_InitTick(hal_tick_freq_t tick_freq, uint32_t tick_priority)
{
  hal_status_t status = HAL_ERROR;

  ASSERT_DBG_PARAM(IS_TICK_FREQ(tick_freq));
  ASSERT_DBG_PARAM(IS_TICK_PRIO(tick_priority));

  /* Check uwTickFreq for MisraC 2012 (despite variable of enum type that does not take value zero) */
  if ((uint32_t)uwTickFreq != 0U)
  {
    /* Note: Value "1000" to convert SysTick frequency value to Hz */
    if (HAL_CORTEX_SYSTICK_SetFreq(1000UL / (uint32_t)tick_freq) == HAL_OK)
    {
      uwTickFreq = tick_freq;

      HAL_CORTEX_NVIC_SetPriority(SysTick_IRQn, (hal_cortex_nvic_preemp_priority_t)tick_priority,
                                  (hal_cortex_nvic_sub_priority_t)0U);
      uwTickPrio = tick_priority;
      status = HAL_OK;
    }
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  This subsection provides a set of functions allowing to control and use HAL tick:

  - Function HAL_IncTick() allowing to increment the @ref uwTick global variable. This function is declared as __WEAK
    to be overridden in case of other implementations in user file.
  - Function HAL_GetTick() allowing to get the @ref uwTick global variable. This function is declared as __WEAK
    to be overridden in case of other implementations in user file.
  - Function HAL_GetTickPrio() allowing to get the tick interrupt priority.
  - Function HAL_GetTickFreq() allowing to get the tick frequency.
  - Function HAL_Delay() allowing to provide a delay in milliseconds. This function is declared as __WEAK to be
    overridden in case of other implementations in user file.
  - Function HAL_SuspendTick() allowing to suspend the tick incrementation. This function is declared as __WEAK
    to be overridden in case of other implementations in user file.
  - Function HAL_ResumeTick() allowing to resume the tick incrementation. This function is declared as __WEAK
    to be overridden in case of other implementations in user file.

  @warning HAL tick is updated from interrupts at regular time intervals.
           Care must be taken if HAL_Delay() is called from a peripheral interrupt process:
           the tick interrupt line must have higher priority (numerically lower) than the peripheral interrupt,
           otherwise the caller interrupt process will be blocked.
  */

/**
  * @brief This function is called to increment a global variable @ref uwTick
  *        used as application time base.
  * @note In the default implementation, this function is called within Systick ISR.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_IncTick(void)
{
  uwTick += (uint32_t)uwTickFreq;
}

/**
  * @brief Provides a tick value in milliseconds.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  * @retval uint32_t HAL tick current value (unit: milliseconds)
  */
__WEAK uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function returns a tick priority.
  * @retval uint32_t HAL tick priority
  */
uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}

/**
  * @brief Return tick frequency.
  * @retval hal_tick_freq_t HAL tick frequency setting
  */
hal_tick_freq_t HAL_GetTickFreq(void)
{
  return uwTickFreq;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based on variable incremented.
  * @param delay_ms delay duration, value range in 32 bit value capacity (unit: milliseconds)
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where HAL_IncTick() is called
  *       to increment the uwTick variable.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_Delay(uint32_t delay_ms)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = delay_ms;

  /* check wait value before increment to avoid integer wraparound */
  if (wait < (HAL_MAX_DELAY - (uint32_t)uwTickFreq))
  {
    /* Add a delay to guarantee a minimum wait of one period of "tick Frequency" */
    wait += (uint32_t)(uwTickFreq);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}

/**
  * @brief This function provides minimum delay (in milliseconds) based on variable incremented
  *        without Systick interrupt.
  * @param delay_ms delay duration, value range in 32 bit value capacity (unit: milliseconds)
  * @note In the default implementation, SysTick timer is the source of time base.
  *       This function is designed to allow users to insert delays without interrupt management,
  *       avoiding constraints related to interrupt priorities.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_Delay_NoISR(uint32_t delay_ms)
{
  LL_Delay_NoISR(delay_ms);
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_SuspendTick(void)
{
  HAL_CORTEX_SYSTICK_Suspend();
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __WEAK to be overridden in case of other
  *       implementations in user file.
  */
__WEAK void HAL_ResumeTick(void)
{
  HAL_CORTEX_SYSTICK_Resume();
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  This subsection provides a set of functions allowing to get HAL driver version:
  - Function HAL_GetVersion() allowing to get the HAL driver version
  */

/**
  * @brief  Returns the HAL revision
  * @retval uint32_t HAL driver version: 0xXYZR (8bits for each decimal, R for release candidate)
  */
uint32_t HAL_GetVersion(void)
{
  return HAL_VERSION;
}

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  This subsection provides a set of functions allowing to get device identification data:
  - Function HAL_GetDeviceUniqueID() allowing to get the device unique identification
  */

/**
  * @brief  Return the device unique identification data
  * @param  p_uid Pointer to hal_device_uid_t structure containing identification data
  * @retval HAL_OK            Clock configuration successfully done
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  */
hal_status_t HAL_GetDeviceUniqueID(hal_device_uid_t *p_uid)
{
  ASSERT_DBG_PARAM((p_uid != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_uid == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_uid->uid_0 = LL_GetUID_Word0();
  p_uid->uid_1 = LL_GetUID_Word1();
  p_uid->uid_2 = LL_GetUID_Word2();

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
