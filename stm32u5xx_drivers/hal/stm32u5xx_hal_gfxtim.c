/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gfxtim.c
  * @brief   GFXTIM HAL module driver.
  **********************************************************************************************************************
    * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

#if defined(GFXTIM)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
/** @addtogroup GFXTIM
  * @{

# GFXTIM peripheral overview

The Graphic Timer peripheral (GFXTIM) allows a smart management of graphical events for frame or line counting.

This file provides firmware functions to manage the following functionalities:
   - Initialization and de-initialization functions
   - Frame and line clock generator functions
   - Tearing-effect functions
   - Absolute timer functions
   - Relative timers functions
   - Event generators functions
   - Watchdog timer functions

# How to use the GFXTIM HAL module driver

## The GFXTIM HAL driver can be used as follows:

This module provides 10 sets of APIs that allows to:

1. Initialize and De-Initialize the logical object:
   - To initialize the GFXTIM, use the HAL_GFXTIM_Init() function to:
     - Associate physical instance to logical object.
     - Enable the GFXTIM peripheral Clock:
      - Call the HAL_RCC_GFXTIM_EnableClock() function, which directly enables the clock for the GFXTIM peripheral.
      - Set the USE_HAL_GFXTIM_CLK_ENABLE_MODEL to HAL_CLK_ENABLE_PERIPH_ONLY in the stm32tnxx_hal_conf.h module.
        With this configuration, the GFXTIM peripheral clock will be automatically enabled during the initialization
        process by HAL_GFXTIM_Init().

   - To de-initiliaze the GFXTIM peripheral, use the HAL_GFXTIM_DeInit() function that stops any ongoing processes and
     sets the GFXTIM handle states to reset.

2. Manage the clock generator
   Several APIs are available to manage the clock generator (Line clock generator and/ or Frame clock generator)
   - Configure the frame and line clock generator:
     - This functionality is provided by HAL_GFXTIM_CLKGEN_SetConfigLineFrameClock() function.
   - Get the line clock generator configuration:
     - This functionality is provided by HAL_GFXTIM_CLKGEN_GetConfigLineClock() function.
   - Configure the frame clock generator:
     - This functionality is provided by HAL_GFXTIM_CLKGEN_SetConfigFrameClock() function.
   - Get the frame clock generator configuration:
     - This functionality is provided by HAL_GFXTIM_CLKGEN_GetConfigFrameClock() function.
   - Force reload counter of clock generator:
     - This functionality is provided by HAL_GFXTIM_CLKGEN_ForceReloadCounter() function.
   - Enable, disable and check the line-clock calibration output:
     - These functionalities are provided respectively by HAL_GFXTIM_CLKGEN_EnableLineClkCalibOutput(),
       HAL_GFXTIM_CLKGEN_DisableLineClkCalibOutput() and HAL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput().
   - Enable, disable and check the frame-clock calibration output:
     - These functionalities are provided respectively by HAL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput(),
       HAL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput() and HAL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput().

3. Control the Tearing-effect detection:
   - The Tearing-effect detection can be used to detect the tearing-effect in order to generate an interruption.
   - Configure the tearing-effect detection:
     - This functionality is provided by HAL_GFXTIM_SetConfigTearingEffect() function.
   - Get the tearing-effect detection configuration:
     - This functionality is provided by HAL_GFXTIM_GetConfigTearingEffect() function.
   - Enable and disable and check the tearing-effect detection interruption:
     - These functionalities are provided respectively by HAL_GFXTIM_EnableTearingEffectIT(),
       HAL_GFXTIM_DisableTearingEffectIT() and HAL_GFXTIM_IsEnabledTearingEffectIT().

4. Manage the absolute line and the absolute frame:
   After clock generator configuration, the absolute timer (absolute line and/ or absolute frame) can be used.
   - Set and get the absolute line compare value:
     - These functionalities are provided respectively by HAL_GFXTIM_ABSTIM_SetLineCompareValue() and
       HAL_GFXTIM_ABSTIM_GetLineCompareValue().
   - Set and get the absolute line counter value:
     - These functionalities are provided by HAL_GFXTIM_ABSTIM_SetLineCounter() and HAL_GFXTIM_ABSTIM_GetLineCounter()
       functions.
   - Set and get the absolute frame compare value:
     - These functionalities are provided respectively by HAL_GFXTIM_ABSTIM_SetFrameCompareValue() and
       HAL_GFXTIM_ABSTIM_GetFrameCompareValue() functions.
   - Set and get the absolute frame counter value:
     - These functionalities are provided by HAL_GFXTIM_ABSTIM_SetFrameCounter() and HAL_GFXTIM_ABSTIM_GetFrameCounter()
       functions.
   - Use HAL_GFXTIM_ABSTIM_Start() and HAL_GFXTIM_ABSTIM_Stop() functions to start and stop the absolute counter(s)
   - Use HAL_GFXTIM_ABSTIM_Pause() and HAL_GFXTIM_ABSTIM_Resume() functions to suspend and resume
     the absolute counter(s).
   - Get the absolute line and frame counters value simultaneously:
     - This functionality is provided by HAL_GFXTIM_ABSTIM_GetCounter() function.

5. Manage the relative timers:
   After frame clock generator configuration, the relative frame can be used.
   Several APIs are available to manage the relative timers.
   - Start and stop the relative frame counter in continuous mode:
     - These functionalities are provided respectively by HAL_GFXTIM_RELTIM_StartContinuous() and
       HAL_GFXTIM_RELTIM_StopContinuous() functions.
   - Set and force reload value of counter:
     - These functionalities are provided respectively by HAL_GFXTIM_RELTIM_SetReloadValue() and
       HAL_GFXTIM_RELTIM_ForceReload() functions.
   - Get the relative frame counter value:
     - This functionality is provided by HAL_GFXTIM_RELTIM_GetCounter() function.
   - Start the relative frame counter in one shot mode:
     - This functionality is provided  by HAL_GFXTIM_RELTIM_StartOneShot() function.
   - Poll the relative frame counter in one shot mode when the interruptions are disabled. In this case a fixed
     timeout can be configured by user:
     - This functionality is provided by HAL_GFXTIM_RELTIM_PollForOneShot() function.

6. Configure the event generators:
   This feature is used to generate a complex event.
   - Configure the event generator:
     - This functionality is provided by HAL_GFXTIM_EVENTGEN_SetConfig() function.
   - Get the event generator configuration:
     - This functionality is provided by HAL_GFXTIM_EVENTGEN_GetConfig() function.
   - Start the event generator:
     - This functionality is provided by HAL_GFXTIM_EVENTGEN_Start() function.
   - Stop the event generator:
     - This functionality is provided by HAL_GFXTIM_EVENTGEN_Stop() function.

7. Manage the watchdog timer:
   The GFXTIM watchdog timer is used to generate an alarm and pre-alarm events.
   - Configure the watchdog timer:
     - This functionality is provided by HAL_GFXTIM_WDG_SetConfig() function.
   - Get the watchdog timer configuration:
     - This functionality is provided by HAL_GFXTIM_WDG_GetConfig() function.
   - Start the watchdog timer:
     - This functionality is provided by HAL_GFXTIM_WDG_Start() function.
   - Stop the watchdog timer:
     - This functionality is provided by HAL_GFXTIM_WDG_Stop() function.
   - Refresh the watchdog timer:
     - This functionality is provided by HAL_GFXTIM_WDG_Refresh() function.

8. Peripheral state Functions:
   - Use HAL_GFXTIM_GetState() function to get the GFXTIM current global state.
   - Use HAL_GFXTIM_CLKGEN_GetState() function to get the GFXTIM clock generator state.
   - Use HAL_GFXTIM_ABSTIM_GetLineState() function to get the GFXTIM absolute line state.
   - Use HAL_GFXTIM_ABSTIM_GetFrameState() function to get the GFXTIM absolute frame state.
   - Use HAL_GFXTIM_RELTIM_GetState() function to get the GFXTIM relative frame state.
   - Use HAL_GFXTIM_WDG_GetState() function to get the GFXTIM watchdog counter state.

9. IRQHandler and Callbacks Functions:
  - Use HAL_GFXTIM_IRQHandler() function to handle all GFXTIM interrupts.
  - Use HAL_GFXTIM_TearingEffectIRQHandler() function to handle only the tearing-effect interrupt.
  - Use HAL_GFXTIM_ABSTIM_FrameIRQHandler() function to handle only the absolute frame interrupts.
  - Use HAL_GFXTIM_ABSTIM_LineIRQHandler() function to handle only the absolute line interrupts.
  - Use HAL_GFXTIM_RELTIM_IRQHandler() function to handle only the relative framed interrupts.
  - Use HAL_GFXTIM_EVENTGEN_IRQHandler() function to handle only the event generator interrupts.
  - Use HAL_GFXTIM_WDG_IRQHandler() function to handle only the GFXTIM watchdog interrupts.
  - By default, after the HAL_GFXTIM_Init(), all callbacks are reset to the corresponding legacy weak (surcharged)
    functions:
    When the compilation flag **USE_HAL_GFXTIM_REGISTER_CALLBACKS** is set to 1,
    use **HAL_GFXTIM_RegisterXxxCallback()** functions to register an interrupt callback.
  - HAL_GFXTIM_RegisterTearingEffectCallback()          : A Callback when a tearing-effect interrupt has occurred
  - HAL_GFXTIM_ABSTIM_RegisterFCmpCallback()            : A Callback when an absolute frame counter compare interrupt
                                                          has occurred.
  - HAL_GFXTIM_ABSTIM_RegisterFCntOverFlowCallback()    : A Callback when an absolute frame counter overflow interrupt
                                                          has occurred.
  - HAL_GFXTIM_ABSTIM_RegisterLCmpCallback()            : A Callback when an absolute line counter compare(s) interrupt
                                                          has occurred.
  - HAL_GFXTIM_ABSTIM_RegisterLCntOverFlowCallback()    : A Callback when an absolute line counter overflow interrupt
                                                          has occurred.
  - HAL_GFXTIM_RELTIM_RegisterFCntReloadCallback()      : A Callback when a relative frame counter reload interrupt
                                                          has occurred.
  - HAL_GFXTIM_EVENTGEN_RegisterEventCallback()         : A Callback when an abort is completed.
  - HAL_GFXTIM_WDG_RegisterAlarmCallback()              : A Callback when a watchdog alarm interrupt has occurred.
  - HAL_GFXTIM_WDG_RegisterPreAlarmCallback()           : A Callback when a watchdog pre-alarm interrupt has occurred.

    When the compilation flag is set to 0 or not defined, the callback registration feature is not available
    and all callbacks are set to the corresponding weak functions.

10. User data Functions:
  - Use HAL_GFXTIM_SetUserData() function to set the GFXTIM user data.
  - Use HAL_GFXTIM_GetUserData() function to get the GFXTIM user data.

## Configuration inside the GFXTIM driver

Config defines                    | Description      | Default value     | Note
--------------------------------- | -----------------| ----------------- | -------------------------------------------
USE_HAL_GFXTIM_MODULE             | from hal_conf.h  | 1                 | When set, HAL GFXTIM module is enabled.
USE_ASSERT_DBG_PARAM              | from IDE         | None              | When defined, enable the params assert.
USE_ASSERT_DBG_STATE              | from IDE         | None              | When defined, enable the state assert.
USE_HAL_CHECK_PARAM               | from hal_conf.h  | 0                 | Allows to use the run-time checks parameters.
USE_HAL_GFXTIM_CLK_ENABLE_MODEL   | from hal_conf.h  | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_GFXTIM_REGISTER_CALLBACKS | from hal_conf.h  | 0                 | When set, enable the register callbacks
USE_HAL_GFXTIM_USER_DATA          | from hal_conf.h  | 0                 | When set, user data is defined in handle.
  */

#if defined (USE_HAL_GFXTIM_MODULE) && (USE_HAL_GFXTIM_MODULE == 1U)

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup GFXTIM_Private_Macros GFXTIM Private Macros
  * @{
  */

/**
  * @brief GFXTIM get Instance macro
  */
#define GFXTIM_GET_INSTANCE(handle)  ((GFXTIM_TypeDef *)((uint32_t)(handle)->instance))

/*! Tearing-effect detection source check macro */
#define IS_GFXTIM_TE_SRC(param)                      \
  (((param) == HAL_GFXTIM_TEARING_EFFECT_GPIO)       \
   || ((param) == HAL_GFXTIM_TEARING_EFFECT_HSYNC)   \
   || ((param) == HAL_GFXTIM_TEARING_EFFECT_VSYNC))

/*! Tearing-effect detection polarity check macro */
#define IS_GFXTIM_TE_POLARITY(param)                      \
  (((param) == HAL_GFXTIM_TEARING_EFFECT_RISING_EDGE)     \
   ||((param) == HAL_GFXTIM_TEARING_EFFECT_FALLING_EDGE))

/*! Line clock counter hardware reload source check macro */
#define IS_GFXTIM_CLKGEN_LINE_RELOAD_SRC(param)                  \
  (((param) == HAL_GFXTIM_CLKGEN_LCNT_NO_RELOAD)                 \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD) \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD)    \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD)   \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD)    \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD)   \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD)       \
   || ((param) == HAL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD))

/*! Line clock counter reload value check macro */
#define IS_GFXTIM_CLKGEN_LINE_RELOAD_VALUE(param) ((param) <= 4194303U)

/*! Line clock counter clock source check macro */
#define IS_GFXTIM_CLKGEN_LINE_COUNTER_SRC(param)        \
  (((param) == HAL_GFXTIM_CLKGEN_LINE_COUNT_NONE)       \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK))

/*! Line clock source check macro */
#define IS_GFXTIM_CLKGEN_LINE_CLK_SRC(param)                   \
  (((param) == HAL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW)          \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW)       \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_HSYNC_RISING)         \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING)        \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_VSYNC_RISING)         \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING)        \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_TE_RISING)            \
   || ((param) == HAL_GFXTIM_CLKGEN_LINE_TE_FALLING))

/*! Frame clock counter hardware reload source check macro */
#define IS_GFXTIM_CLKGEN_FRAME_RELOAD_SRC(param)                  \
  (((param) == HAL_GFXTIM_CLKGEN_FCNT_NO_RELOAD)                  \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD)   \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD)     \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD)    \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD)     \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD)    \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD)        \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD))

/*! Frame clock counter reload value check macro */
#define IS_GFXTIM_CLKGEN_FRAME_RELOAD_VALUE(param) ((param) <= 4095U)

/*! Frame clock counter clock source check macro */
#define IS_GFXTIM_CLKGEN_FRAME_COUNTER_SRC(param)          \
  (((param) == HAL_GFXTIM_CLKGEN_FCNT_DISABLE)             \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW)   \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING)     \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING)    \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING)     \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING)    \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_TE_RISING)        \
   || ((param) == HAL_GFXTIM_CLKGEN_FCNT_TE_FALLING))

/*! Frame clock source check macro */
#define IS_GFXTIM_CLKGEN_FRAME_CLK_SRC(param)                   \
  (((param) == HAL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW)          \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW)       \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING)         \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING)        \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING)         \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING)        \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_TE_RISING)            \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_TE_FALLING))

/*! Clock generator counter check macro */
#define IS_GFXTIM_CLKGEN_COUNTER(param)                 \
  (((param) == HAL_GFXTIM_CLKGEN_LINE_CLK_COUNTER)      \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_CLK_COUNTER)  \
   || ((param) == HAL_GFXTIM_CLKGEN_FRAME_LINE_CLK_COUNTER))

/*! Absolute frame value check macro */
#define IS_GFXTIM_ABSOLUTE_FRAME_VALUE(param) ((param) <= 1048575U)

/*! Absolute line value check macro */
#define IS_GFXTIM_ABSTIM_LINE_VALUE(param)  ((param) <= 4095U)

/*! Absolute line compare check macro */
#define IS_GFXTIM_ABSTIM_LINE_COMP(param)         \
  (((param) == HAL_GFXTIM_ABSTIM_LINE_COMP_1)     \
   || ((param) == HAL_GFXTIM_ABSTIM_LINE_COMP_2))

/*! Absolute timer counter check macro */
#define IS_GFXTIM_ABSTIM_COUNTER(param)                  \
  (((param) == HAL_GFXTIM_ABSTIM_LINE_COUNTER)           \
   || ((param) == HAL_GFXTIM_ABSTIM_FRAME_COUNTER)       \
   || ((param) == HAL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER))

/*! Absolute timer interrupt check macro */
#define IS_GFXTIM_ABSTIM_IT(counter, it)                                                                     \
  (((counter) == HAL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER)                                                       \
   ||((it) == HAL_GFXTIM_NONE_IT)                                                                            \
   ||(((counter) == HAL_GFXTIM_ABSTIM_LINE_COUNTER)  && (((HAL_GFXTIM_ABSTIM_LINE_ALL_IT) & (it)) == (it)))  \
   ||(((counter) == HAL_GFXTIM_ABSTIM_FRAME_COUNTER) && (((HAL_GFXTIM_ABSTIM_FRAME_ALL_IT) & (it)) == (it))))

/*! Relative timers selection check macro */
#define IS_GFXTIM_RELTIM_COUNTER(param)        \
  (((param) == HAL_GFXTIM_RELTIM_COUNTER_1)    \
   ||((param) == HAL_GFXTIM_RELTIM_COUNTER_2))

/*! Relative timers Interrupt check macro */
#define IS_GFXTIM_RELTIM_IT(param)            \
  (((param) == HAL_GFXTIM_NONE_IT)            \
   ||((param) == HAL_GFXTIM_RELTIM_COUNT_IT))

/*! Relative timers auto-reload value check macro */
#define IS_GFXTIM_RELTIM_REALOAD_VALUE(param) ((param) <= 4095U)

/*! Line event source selection check macro */
#define IS_GFXTIM_EVENTGEN_LINE(param)                    \
  (((param) == HAL_GFXTIM_EVENTGEN_LINE_NONE)             \
   || ((param) == HAL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW)  \
   || ((param) == HAL_GFXTIM_EVENTGEN_TEARING_EFFECT)     \
   || ((param) == HAL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP)    \
   || ((param) == HAL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP))

/*! Frame event source selection check macro */
#define IS_GFXTIM_EVENTGEN_FRAME(param)                  \
  (((param) == HAL_GFXTIM_EVENTGEN_FRAME_NONE)           \
   || ((param) == HAL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW) \
   || ((param) == HAL_GFXTIM_EVENTGEN_ABS_FCNT_COMP)     \
   || ((param) == HAL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD) \
   || ((param) == HAL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD))

/*! Event generator check macro */
#define IS_GFXTIM_EVENTGEN_EVENT(param)        \
  (((param) == HAL_GFXTIM_EVENTGEN_EVENT_1)    \
   || ((param) == HAL_GFXTIM_EVENTGEN_EVENT_2) \
   || ((param) == HAL_GFXTIM_EVENTGEN_EVENT_3) \
   || ((param) == HAL_GFXTIM_EVENTGEN_EVENT_4))

/*! Event generator Interrupt check macro */
#define IS_GFXTIM_EVENTGEN_INTERRUPT(param)      \
  (((param) == HAL_GFXTIM_NONE_IT)               \
   || ((param) == HAL_GFXTIM_EVENTGEN_EVENT_IT))

/*! Watchdog hardware reload check macro */
#define IS_GFXTIM_WDG_HW_RELOAD(param)                   \
  (((param) == HAL_GFXTIM_WDG_HW_RELOAD_DISABLED)        \
   || ((param) == HAL_GFXTIM_WDG_HW_RELOAD_RISING_EDGE)  \
   || ((param) == HAL_GFXTIM_WDG_HW_RELOAD_FALLING_EDGE))

/*! Watchdog clock source check macro */
#define IS_GFXTIM_WDG_CLK_SRC(param)                \
  (((param) == HAL_GFXTIM_WDG_CLK_LINE_CLK)         \
   || ((param) == HAL_GFXTIM_WDG_CLK_FRAME_CLK)     \
   || ((param) == HAL_GFXTIM_WDG_CLK_HSYNC_RISING)  \
   || ((param) == HAL_GFXTIM_WDG_CLK_HSYNC_FALLING) \
   || ((param) == HAL_GFXTIM_WDG_CLK_VSYNC_RISING)  \
   || ((param) == HAL_GFXTIM_WDG_CLK_VSYNC_FALLING) \
   || ((param) == HAL_GFXTIM_WDG_CLK_TE_RISING)     \
   || ((param) == HAL_GFXTIM_WDG_CLK_TE_FALLING)    \
   || ((param) == HAL_GFXTIM_WDG_CLK_EVENT_1)       \
   || ((param) == HAL_GFXTIM_WDG_CLK_EVENT_2)       \
   || ((param) == HAL_GFXTIM_WDG_CLK_EVENT_3)       \
   || ((param) == HAL_GFXTIM_WDG_CLK_EVENT_4))

/*! Watchdog counter value check macro */
#define IS_GFXTIM_WDG_COUNTER_VALUE(param)  ((param) <= 65535U)

/*! Watchdog timer Interrupt check macro */
#define IS_GFXTIM_WDG_IT(param)                           \
  (((param) == HAL_GFXTIM_NONE_IT)                        \
   || ((((param) & HAL_GFXTIM_WDG_ALL_IT) != 0U)          \
       &&  (((param) & (~HAL_GFXTIM_WDG_ALL_IT)) == 0U)))
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private functions prototypes --------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup GFXTIM_Exported_Functions
  * @{
  */

/** @addtogroup GFXTIM_Exported_Functions_Group1
  * @{
  This subsection provides a set of functions allowing to initialize and de-initialize the GFXTIM peripheral:
  - Call HAL_GFXTIM_Init() to initialize the GFXTIM handle and associate associate a physical instance.
  - Call HAL_GFXTIM_DeInit() to de-initialize the GFXTIM handle.
  */

/**
  * @brief  Initialize the GFXTIM handle and associate a physical GFXTIM instance.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  instance          Specifies the GFXTIM instance based on \ref hal_gfxtim_t enumeration.
  * @retval HAL_INVALID_PARAM Invalid parameter when hgfxtim pointer is NULL.
  * @retval HAL_OK            GFXTIM is successfully initialized.
  */
hal_status_t HAL_GFXTIM_Init(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_t instance)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ALL_INSTANCE((GFXTIM_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hgfxtim == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->instance = instance;

#if defined(USE_HAL_GFXTIM_CLK_ENABLE_MODEL) && (USE_HAL_GFXTIM_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_GFXTIM_EnableClock();
#endif /* USE_HAL_GFXTIM_CLK_ENABLE_MODEL */

#if defined (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
  hgfxtim->p_tearing_effect_cb      = HAL_GFXTIM_TearingEffectCallback;
  hgfxtim->p_abs_frame_comp_cb      = HAL_GFXTIM_ABSTIM_FCmpCallback;
  hgfxtim->p_abs_frame_ovf_cb       = HAL_GFXTIM_ABSTIM_FCntOverFlowCallback;
  hgfxtim->p_abs_line_comp_cb       = HAL_GFXTIM_ABSTIM_LCmpCallback;
  hgfxtim->p_abs_line_ovf_cb        = HAL_GFXTIM_ABSTIM_LCntOverFlowCallback;
  hgfxtim->p_rel_counter_cb         = HAL_GFXTIM_RELTIM_FCntReloadCallback;
  hgfxtim->p_eventgen_cb            = HAL_GFXTIM_EVENTGEN_EventCallback;
  hgfxtim->p_wdg_alarm_cb           = HAL_GFXTIM_WDG_AlarmCallback;
  hgfxtim->p_wdg_prealarm_cb        = HAL_GFXTIM_WDG_PreAlarmCallback;
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */

#if defined(USE_HAL_GFXTIM_USER_DATA) && (USE_HAL_GFXTIM_USER_DATA == 1U)
  hgfxtim->p_user_data = NULL;
#endif /* USE_HAL_GFXTIM_USER_DATA */

  hgfxtim->clkgen_state       = HAL_GFXTIM_CLKGEN_STATE_RESET;
  hgfxtim->abstim_line_state  = HAL_GFXTIM_ABSTIM_LINE_STATE_IDLE;
  hgfxtim->abstim_frame_state = HAL_GFXTIM_ABSTIM_FRAME_STATE_IDLE;
  hgfxtim->reltim_1_state     = HAL_GFXTIM_RELTIM_STATE_IDLE;
  hgfxtim->reltim_2_state     = HAL_GFXTIM_RELTIM_STATE_IDLE;
  hgfxtim->wdg_state          = HAL_GFXTIM_WDG_STATE_RESET;
  hgfxtim->global_state       = HAL_GFXTIM_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initialize the GFXTIM handle.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_DeInit(hal_gfxtim_handle_t *hgfxtim)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ALL_INSTANCE(GFXTIM_GET_INSTANCE(hgfxtim)));

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  LL_GFXTIM_DisableIT(p_gfxtim, LL_GFXTIM_ALL_IT);

  LL_GFXTIM_WRITE_REG(p_gfxtim, CR, 0x0U);

  LL_GFXTIM_WRITE_REG(p_gfxtim, TDR, (LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER | LL_GFXTIM_RELTIM_COUNTER_ALL));

  LL_GFXTIM_EVENTGEN_Disable(p_gfxtim, LL_GFXTIM_EVENTGEN_EVENT_ALL);

  LL_GFXTIM_WDG_Disable(p_gfxtim);

  LL_GFXTIM_ClearFlag(p_gfxtim, LL_GFXTIM_FLAG_ALL);

  hgfxtim->clkgen_state       = HAL_GFXTIM_CLKGEN_STATE_RESET;
  hgfxtim->abstim_line_state  = HAL_GFXTIM_ABSTIM_LINE_STATE_RESET;
  hgfxtim->abstim_frame_state = HAL_GFXTIM_ABSTIM_FRAME_STATE_RESET;
  hgfxtim->reltim_1_state     = HAL_GFXTIM_RELTIM_STATE_RESET;
  hgfxtim->reltim_2_state     = HAL_GFXTIM_RELTIM_STATE_RESET;
  hgfxtim->wdg_state          = HAL_GFXTIM_WDG_STATE_RESET;
  hgfxtim->global_state       = HAL_GFXTIM_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group2
  * @{
  This subsection provides a set of functions allowing to manage the clock generator:
  - Call HAL_GFXTIM_CLKGEN_SetConfigLineFrameClock()to configure the line and frame clock generator.
  - Call HAL_GFXTIM_CLKGEN_GetConfigLineClock() to get the line clock generator configuration.
  - Call HAL_GFXTIM_CLKGEN_SetConfigFrameClock() to configure the frame clock generator.
  - Call HAL_GFXTIM_CLKGEN_GetConfigFrameClock() to get the frame clock generator configuration.
  - Call HAL_GFXTIM_CLKGEN_ForceReloadCounter() to force reload the clock generator counter(s).
  - Call HAL_GFXTIM_CLKGEN_EnableLineClkCalibOutput() to enable the line clock calibration output.
  - Call HAL_GFXTIM_CLKGEN_DisableLineClkCalibOutput() to disable the line clock calibration output.
  - Call HAL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput() to check that line clock calibration output is enabled.
  - Call HAL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput() to enable the frame clock calibration output.
  - Call HAL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput() to disable the frame clock calibration output.
  - Call HAL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput() to check that frame clock calibration output is enabled.
  */

/**
  * @brief  Configure the line and frame clock generator.
  * @param  hgfxtim            Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_line_clk_config  Pointer to \ref hal_gfxtim_clkgen_line_config_t configuration structure.
  * @param  p_frame_clk_config Pointer to \ref hal_gfxtim_clkgen_frame_config_t configuration structure.
  * @retval HAL_INVALID_PARAM  Invalid parameter when p_line_clk_config and/or p_frame_clk_config pointer are NULL.
  * @retval HAL_OK             The Clock generator is successfully configured.
  */
hal_status_t HAL_GFXTIM_CLKGEN_SetConfigLineFrameClock(hal_gfxtim_handle_t *hgfxtim,
                                                       const hal_gfxtim_clkgen_frame_config_t *p_frame_clk_config,
                                                       const hal_gfxtim_clkgen_line_config_t *p_line_clk_config)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_line_clk_config != NULL);
  ASSERT_DBG_PARAM(p_frame_clk_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_LINE_RELOAD_SRC(p_line_clk_config->reload_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_LINE_RELOAD_VALUE(p_line_clk_config->reload_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_LINE_COUNTER_SRC(p_line_clk_config->counter_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_LINE_CLK_SRC(p_line_clk_config->clock_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_RELOAD_SRC(p_frame_clk_config->reload_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_RELOAD_VALUE(p_frame_clk_config->reload_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_COUNTER_SRC(p_frame_clk_config->counter_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_CLK_SRC(p_frame_clk_config->clock_src));

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_STATE_RESET |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_line_clk_config == NULL) || (p_frame_clk_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  LL_GFXTIM_CLKGEN_ConfigFrameLineClock(p_gfxtim, ((uint32_t)p_frame_clk_config->reload_src  |
                                                   (uint32_t)p_frame_clk_config->counter_src |
                                                   (uint32_t)p_frame_clk_config->clock_src),
                                        ((uint32_t)p_line_clk_config->reload_src |
                                         (uint32_t)p_line_clk_config->counter_src |
                                         (uint32_t)p_line_clk_config->clock_src));

  LL_GFXTIM_CLKGEN_SetFrameReloadValue(p_gfxtim, (uint32_t) p_frame_clk_config->reload_val);

  LL_GFXTIM_CLKGEN_SetLineReloadValue(p_gfxtim, (uint32_t)p_line_clk_config->reload_val);

  hgfxtim->clkgen_state = HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the line clock generator configuration.
  * @param  hgfxtim  Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_config Pointer to \ref hal_gfxtim_clkgen_line_config_t structure that will be filled by the line clock
  *                  generator configuration.
  */
void HAL_GFXTIM_CLKGEN_GetConfigLineClock(const hal_gfxtim_handle_t *hgfxtim,
                                          hal_gfxtim_clkgen_line_config_t *p_config)
{
  GFXTIM_TypeDef *p_gfxtim;
  uint32_t tmp_cgcr;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  tmp_cgcr = LL_GFXTIM_READ_REG(p_gfxtim, CGCR);
  p_config->reload_src  = (hal_gfxtim_clkgen_line_count_reload_src_t)(uint32_t)(tmp_cgcr & GFXTIM_CGCR_LCCHRS);
  p_config->counter_src = (hal_gfxtim_clkgen_line_count_src_t)(uint32_t)(tmp_cgcr & GFXTIM_CGCR_LCCCS);
  p_config->clock_src   = (hal_gfxtim_clkgen_line_clk_src_t)(uint32_t)(tmp_cgcr & GFXTIM_CGCR_LCS);

  p_config->reload_val  = LL_GFXTIM_CLKGEN_GetLineReloadValue(p_gfxtim);
}

/**
  * @brief  Configure the frame clock generator.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_clk_config      Pointer to \ref hal_gfxtim_clkgen_frame_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_clk_config pointer is NULL.
  * @retval HAL_OK            The frame clock generator is successfully configured.
  */
hal_status_t HAL_GFXTIM_CLKGEN_SetConfigFrameClock(hal_gfxtim_handle_t *hgfxtim,
                                                   const hal_gfxtim_clkgen_frame_config_t *p_clk_config)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_clk_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_RELOAD_SRC(p_clk_config->reload_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_RELOAD_VALUE(p_clk_config->reload_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_COUNTER_SRC(p_clk_config->counter_src));
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_FRAME_CLK_SRC(p_clk_config->clock_src));

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_STATE_RESET |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_clk_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  LL_GFXTIM_CLKGEN_ConfigFrameClock(p_gfxtim, (uint32_t)p_clk_config->reload_src, (uint32_t)p_clk_config->counter_src,
                                    (uint32_t)p_clk_config->clock_src);

  LL_GFXTIM_CLKGEN_SetFrameReloadValue(p_gfxtim, (uint32_t) p_clk_config->reload_val);

  /* Update the frame clock generator state */
  hgfxtim->clkgen_state = HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED;

  return HAL_OK;
}

/**
  * @brief  Get the frame clock generator configuration.
  * @param  hgfxtim    Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_config Pointer to \ref hal_gfxtim_clkgen_frame_config_t structure that will be filled by the frame clock
  *                  generator configuration.
  */
void HAL_GFXTIM_CLKGEN_GetConfigFrameClock(const hal_gfxtim_handle_t *hgfxtim,
                                           hal_gfxtim_clkgen_frame_config_t *p_config)
{
  GFXTIM_TypeDef *p_gfxtim;
  uint32_t tmp_cgcr;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  tmp_cgcr = LL_GFXTIM_READ_REG(p_gfxtim, CGCR);
  p_config->reload_src  = (hal_gfxtim_clkgen_frame_count_reload_src_t)(uint32_t)(tmp_cgcr & GFXTIM_CGCR_FCCHRS);
  p_config->counter_src = (hal_gfxtim_clkgen_frame_count_src_t)(uint32_t)(tmp_cgcr & GFXTIM_CGCR_FCCCS);
  p_config->clock_src   = (hal_gfxtim_clkgen_frame_clk_src_t)(uint32_t)(tmp_cgcr & GFXTIM_CGCR_FCS);

  p_config->reload_val  = LL_GFXTIM_CLKGEN_GetFrameReloadValue(p_gfxtim);
}

/**
  * @brief  Force reload the clock generator counter(s).
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_clkgen_counter_t enumeration.
  * @retval HAL_OK  The clcok generator counter is successfully force reloaded.
  */
hal_status_t HAL_GFXTIM_CLKGEN_ForceReloadCounter(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_clkgen_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_CLKGEN_COUNTER(counter));

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_CLKGEN_LINE_CLK_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  }
  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_CLK_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED);
  }

  LL_GFXTIM_CLKGEN_ForceReloadCounter(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Enable the line clock calibration output.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The line clock generator calibration output is successfully enabled.
  */
hal_status_t HAL_GFXTIM_CLKGEN_EnableLineClkCalibOutput(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_CLKGEN_EnableLineClkCalibOutput(GFXTIM_GET_INSTANCE(hgfxtim));

  return HAL_OK;
}

/**
  * @brief  Disable the line clock calibration output.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The line clock generator calibration output is successfully disabled.
  */
hal_status_t HAL_GFXTIM_CLKGEN_DisableLineClkCalibOutput(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_CLKGEN_DisableLineClkCalibOutput(GFXTIM_GET_INSTANCE(hgfxtim));

  return HAL_OK;
}

/**
  * @brief  Check that clock generator line clock calibration output is enabled or disabled.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_clkgen_line_clk_calib_status_t Line clock calibration output activation.
  */
hal_gfxtim_clkgen_line_clk_calib_status_t HAL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  return (hal_gfxtim_clkgen_line_clk_calib_status_t)
         LL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput(GFXTIM_GET_INSTANCE(hgfxtim));
}

/**
  * @brief  Enable the frame clock calibration output.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The frame clock generator calibration output is successfully enabled.
  */
hal_status_t HAL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput(GFXTIM_GET_INSTANCE(hgfxtim));

  return HAL_OK;
}

/**
  * @brief  Disable the frame clock calibration output.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The frame clock generator calibration output is successfully disabled.
  */
hal_status_t HAL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput(GFXTIM_GET_INSTANCE(hgfxtim));

  return HAL_OK;
}

/**
  * @brief  Check that clock generator frame clock calibration output is enabled or disabled.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_clkgen_frame_clk_calib_status_t Frame clock calibration output activation.
  */
hal_gfxtim_clkgen_frame_clk_calib_status_t HAL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  return (hal_gfxtim_clkgen_frame_clk_calib_status_t)
         LL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput(GFXTIM_GET_INSTANCE(hgfxtim));
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group3
  * @{
  This subsection provides a set of functions allowing to manage the tearing-effect detection:
  - Call HAL_GFXTIM_SetConfigTearingEffect() to configure the tearing-effect source and polarity.
  - Call HAL_GFXTIM_GetConfigTearingEffect() to get the tearing-effect configuration.
  - Call HAL_GFXTIM_EnableTearingEffectIT() to enable the tearing-effect detection interruption.
  - Call HAL_GFXTIM_DisableTearingEffectIT() to disable the tearing-effect detection interruption.
  - Call HAL_GFXTIM_IsEnabledTearingEffectIT() to check that tearing-effect detection interruption is enabled.
  */

/**
  * @brief  Configure the tearing-effect detection.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_config          Pointer to \ref hal_gfxtim_tearing_effect_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_config pointer is NULL.
  * @retval HAL_OK            The Tearing-effect is successfully configured.
  */
hal_status_t HAL_GFXTIM_SetConfigTearingEffect(hal_gfxtim_handle_t *hgfxtim,
                                               const hal_gfxtim_tearing_effect_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_TE_SRC(p_config->src));
  ASSERT_DBG_PARAM(IS_GFXTIM_TE_POLARITY(p_config->polarity));

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_GFXTIM_TE_Config(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)p_config->src,
                      (uint32_t)p_config->polarity);

  return HAL_OK;
}

/**
  * @brief  Get the tearing-effect detection configuration.
  * @param  hgfxtim  Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_config Pointer to \ref hal_gfxtim_tearing_effect_config_t structure that will be filled by the GFXTIM
  *                  tearing-effect configuration.
  */
void HAL_GFXTIM_GetConfigTearingEffect(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_tearing_effect_config_t *p_config)
{
  uint32_t tmp_cr;
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);

  tmp_cr = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), CR);
  p_config->src      = (hal_gfxtim_tearing_effect_src_t)(uint32_t)(tmp_cr & GFXTIM_CR_TES);
  p_config->polarity = (hal_gfxtim_tearing_effect_polarity_t)(uint32_t)(tmp_cr & GFXTIM_CR_TEPOL);
}

/**
  * @brief  Enable the tearing-effect detection interruption.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The tearing-effect interruption is successfully enabled.
  */
hal_status_t HAL_GFXTIM_EnableTearingEffectIT(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);

  LL_GFXTIM_EnableIT(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_TEARING_EFFECT_IT);

  return HAL_OK;
}

/**
  * @brief  Disable the tearing-effect detection interruption.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The tearing-effect interruption is successfully disabled.
  */
hal_status_t HAL_GFXTIM_DisableTearingEffectIT(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);

  LL_GFXTIM_DisableIT(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_TEARING_EFFECT_IT);

  return HAL_OK;
}

/**
  * @brief  Check that tearing-effect detection interruption is enabled or disabled.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_tearing_effect_it_status_t Tearing-effect detection interruption activation.
  */
hal_gfxtim_tearing_effect_it_status_t HAL_GFXTIM_IsEnabledTearingEffectIT(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);

  return (hal_gfxtim_tearing_effect_it_status_t)LL_GFXTIM_IsEnabledIT(GFXTIM_GET_INSTANCE(hgfxtim),
                                                                      LL_GFXTIM_TEARING_EFFECT_IT);
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group4
  * @{
  This subsection provides a set of functions allowing to manage the absolute timers:
  - Call HAL_GFXTIM_ABSTIM_SetLineCompareValue() to set the absolute line compare value.
  - Call HAL_GFXTIM_ABSTIM_GetLineCompareValue() to get the absolute line compare value.
  - Call HAL_GFXTIM_ABSTIM_SetLineCounter() to set the absolute line counter value.
  - Call HAL_GFXTIM_ABSTIM_GetLineCounter() to get the absolute line counter value.
  - Call HAL_GFXTIM_ABSTIM_SetFrameCompareValue() to set the absolute frame compare value.
  - Call HAL_GFXTIM_ABSTIM_GetFrameCompareValue() to get the absolute frame compare value.
  - Call HAL_GFXTIM_ABSTIM_SetFrameCounter() to set the absolute frame counter value.
  - Call HAL_GFXTIM_ABSTIM_GetFrameCounter() to get the absolute frame counter value.
  - Call HAL_GFXTIM_ABSTIM_Start() to start the absolute line and/ or frame counter(s).
  - Call HAL_GFXTIM_ABSTIM_Stop() to stop the absolute line and/ or frame counter(s).
  - Call HAL_GFXTIM_ABSTIM_Pause() to pause the absolute line and/ or frame counter(s).
  - Call HAL_GFXTIM_ABSTIM_Resume() to resume the absolute line and/ or frame counter(s).
  - Call HAL_GFXTIM_ABSTIM_GetCounter() to Get the absolute line and frame counters value simultaneously.
  */

/**
  * @brief  Set the absolute line compare value.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  line_comp This parameter is an element of \ref hal_gfxtim_abstim_line_comp_t enumeration.
  * @param  val       This parameter can be a number between 0x000 and 0xFFF.
  * @retval HAL_OK    Absolute line compare value is successfully configured.
  */
hal_status_t HAL_GFXTIM_ABSTIM_SetLineCompareValue(hal_gfxtim_handle_t *hgfxtim,
                                                   hal_gfxtim_abstim_line_comp_t line_comp, uint32_t val)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_LINE_COMP(line_comp));
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_LINE_VALUE(val));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_ABSTIM_SetLineCompareValue(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)line_comp, val);

  return HAL_OK;
}

/**
  * @brief  Get the absolute line compare value.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  line_comp This parameter is an element of \ref hal_gfxtim_abstim_line_comp_t enumeration.
  * @retval uint32_t  Value of the absolute line compare.
  */
uint32_t HAL_GFXTIM_ABSTIM_GetLineCompareValue(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_line_comp_t line_comp)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_LINE_COMP(line_comp));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  return LL_GFXTIM_ABSTIM_GetLineCompareValue(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)line_comp);
}

/**
  * @brief  Set the absolute line counter value.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  val       This parameter can be a number between 0x000 and 0xFFF.
  * @note   The value of the absolute line counter can only be set when the absolute line counter is disabled.
  * @retval HAL_ERROR The absolute line counter is already enabled.
  * @retval HAL_OK    Absolute line counter value is successfully set.
  */
hal_status_t HAL_GFXTIM_ABSTIM_SetLineCounter(const hal_gfxtim_handle_t *hgfxtim, uint32_t val)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_LINE_VALUE(val));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hgfxtim->abstim_line_state, (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_IDLE |
                   (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_PAUSED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (LL_GFXTIM_ABSTIM_IsEnabledLineCounter(p_gfxtim) != 0U)
  {
    return HAL_ERROR;
  }

  else
  {
    LL_GFXTIM_ABSTIM_SetLineCounter(p_gfxtim, val);
  }

  return HAL_OK;
}

/**
  * @brief  Get the absolute line counter value.
  * @param  hgfxtim  Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval uint32_t Value of the absolute line counter value.
  */
uint32_t HAL_GFXTIM_ABSTIM_GetLineCounter(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  return LL_GFXTIM_ABSTIM_GetLineCounter(GFXTIM_GET_INSTANCE(hgfxtim));
}

/**
  * @brief  Set the absolute frame compare value.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  val     This parameter can be a number between 0x00000 and 0xFFFFF.
  * @retval HAL_OK  Absolute frame compare is successfully set.
  */
hal_status_t HAL_GFXTIM_ABSTIM_SetFrameCompareValue(hal_gfxtim_handle_t *hgfxtim, uint32_t val)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSOLUTE_FRAME_VALUE(val));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_ABSTIM_SetFrameCompareValue(GFXTIM_GET_INSTANCE(hgfxtim), val);

  return HAL_OK;
}

/**
  * @brief  Get the absolute frame compare value.
  * @param  hgfxtim  Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval uint32_t Value of the absolute frame compare value.
  */
uint32_t HAL_GFXTIM_ABSTIM_GetFrameCompareValue(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED);

  return LL_GFXTIM_ABSTIM_GetFrameCompareValue(GFXTIM_GET_INSTANCE(hgfxtim));
}

/**
  * @brief  Start the absolute frame counter value.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  val       This parameter can be a number between 0x000 and 0xFFF.
  * @note   The value of the absolute frame counter can only be set when the absolute frame counter is disabled.
  * @retval HAL_ERROR The absolute frame counter is already enabled.
  * @retval HAL_OK    The Absolute frame counter is successfully set.
  */
hal_status_t HAL_GFXTIM_ABSTIM_SetFrameCounter(const hal_gfxtim_handle_t *hgfxtim, uint32_t val)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSOLUTE_FRAME_VALUE(val));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  ASSERT_DBG_STATE(hgfxtim->abstim_frame_state, (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_IDLE |
                   (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_PAUSED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (LL_GFXTIM_ABSTIM_IsEnabledFrameCounter(p_gfxtim) != 0U)
  {
    return HAL_ERROR;
  }
  else
  {
    LL_GFXTIM_ABSTIM_SetFrameCounter(p_gfxtim, val);
  }

  return HAL_OK;
}

/**
  * @brief  Get the absolute frame counter value.
  * @param  hgfxtim  Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval uint32_t Value of the absolute line counter value.
  */
uint32_t HAL_GFXTIM_ABSTIM_GetFrameCounter(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED);

  return LL_GFXTIM_ABSTIM_GetFrameCounter(GFXTIM_GET_INSTANCE(hgfxtim));
}

/**
  * @brief  Start the absolute timer(s).
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_abstim_counter_t enumeration.
  * @param  interrupts This parameter can be one or a combination of the following values:
  *                    @arg HAL_GFXTIM_NONE_IT                       : No interruption.
  *                    @arg HAL_GFXTIM_ABSTIM_LINE_COMP1_IT          : Absolute line counter compare 1 interruption.
  *                    @arg HAL_GFXTIM_ABSTIM_LINE_COMP2_IT          : Absolute line counter compare 2 interruption.
  *                    @arg HAL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT : Absolute line counter overflow interruption.
  *                    @arg HAL_GFXTIM_ABSTIM_LINE_ALL_IT            : All absolute line counter interruptions.
  *                    @arg HAL_GFXTIM_ABSTIM_FRAME_COMP_IT          : Absolute frame counter compare 1 interruption.
  *                    @arg HAL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT: Absolute frame counter overflow interruption.
  *                    @arg HAL_GFXTIM_ABSTIM_FRAME_ALL_IT           : All absolute frame counter interruptions.
  * @note   The interruptions are activated according to the chosen counter.
  * @retval HAL_OK  Absolute timer counter is successfully started.
  */
hal_status_t HAL_GFXTIM_ABSTIM_Start(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter,
                                     uint32_t interrupts)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_COUNTER(counter));
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_IT(counter, interrupts));

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_LINE_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_line_state, (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_IDLE);

    HAL_CHECK_UPDATE_STATE(hgfxtim, abstim_line_state, HAL_GFXTIM_ABSTIM_LINE_STATE_IDLE,
                           HAL_GFXTIM_ABSTIM_LINE_STATE_ACTIVE);

    LL_GFXTIM_EnableIT(p_gfxtim, (interrupts & HAL_GFXTIM_ABSTIM_LINE_ALL_IT));
  }

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_frame_state, (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_IDLE);

    HAL_CHECK_UPDATE_STATE(hgfxtim, abstim_frame_state, HAL_GFXTIM_ABSTIM_FRAME_STATE_IDLE,
                           HAL_GFXTIM_ABSTIM_FRAME_STATE_ACTIVE);

    LL_GFXTIM_EnableIT(p_gfxtim, (interrupts & HAL_GFXTIM_ABSTIM_FRAME_ALL_IT));
  }

  LL_GFXTIM_ABSTIM_EnableCounter(p_gfxtim, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Stop the absolute timer(s).
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_abstim_counter_t enumeration.
  * @retval HAL_OK  Absolute line counter is successfully stopped.
  */
hal_status_t HAL_GFXTIM_ABSTIM_Stop(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_COUNTER(counter));

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_LINE_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_line_state, (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_ACTIVE |
                     (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_PAUSED);

    LL_GFXTIM_DisableIT(p_gfxtim, LL_GFXTIM_ABSTIM_LINE_ALL_IT);

    LL_GFXTIM_ABSTIM_DisableCounter(p_gfxtim, LL_GFXTIM_ABSTIM_LINE_COUNTER);

    hgfxtim->abstim_line_state = HAL_GFXTIM_ABSTIM_LINE_STATE_IDLE;
  }
  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_frame_state, (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_ACTIVE |
                     (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_PAUSED);

    LL_GFXTIM_DisableIT(p_gfxtim, LL_GFXTIM_ABSTIM_FRAME_ALL_IT);

    LL_GFXTIM_ABSTIM_DisableCounter(p_gfxtim, LL_GFXTIM_ABSTIM_FRAME_COUNTER);

    hgfxtim->abstim_frame_state = HAL_GFXTIM_ABSTIM_FRAME_STATE_IDLE;
  }

  return HAL_OK;
}

/**
  * @brief  Pause the absolute timer(s).
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_abstim_counter_t enumeration.
  * @retval HAL_OK  Absolute line counter is successfully paused.
  */
hal_status_t HAL_GFXTIM_ABSTIM_Pause(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_COUNTER(counter));

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_LINE_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_line_state, (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_ACTIVE);

    hgfxtim->abstim_line_state = HAL_GFXTIM_ABSTIM_LINE_STATE_PAUSED;

    LL_GFXTIM_ABSTIM_DisableCounter(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_ABSTIM_LINE_COUNTER);
  }

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_frame_state, (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_ACTIVE);

    hgfxtim->abstim_frame_state = HAL_GFXTIM_ABSTIM_FRAME_STATE_PAUSED;

    LL_GFXTIM_ABSTIM_DisableCounter(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_ABSTIM_FRAME_COUNTER);
  }

  return HAL_OK;
}

/**
  * @brief  Resume the absolute timer(s).
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_abstim_counter_t enumeration.
  * @retval HAL_OK  Absolute line counter is successfully resumed.
  */
hal_status_t HAL_GFXTIM_ABSTIM_Resume(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_COUNTER(counter));

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_LINE_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_line_state, (uint32_t)HAL_GFXTIM_ABSTIM_LINE_STATE_PAUSED);

    LL_GFXTIM_ABSTIM_EnableCounter(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)counter);

    hgfxtim->abstim_line_state = HAL_GFXTIM_ABSTIM_LINE_STATE_ACTIVE;
  }

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
    ASSERT_DBG_STATE(hgfxtim->abstim_frame_state, (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_STATE_PAUSED);

    LL_GFXTIM_ABSTIM_EnableCounter(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)counter);

    hgfxtim->abstim_frame_state = HAL_GFXTIM_ABSTIM_FRAME_STATE_ACTIVE;
  }

  return HAL_OK;
}

/**
  * @brief  Force reset the absolute counter(s).
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_abstim_counter_t enumeration.
  * @retval HAL_OK  Absolute line counter is successfully resumed.
  */
hal_status_t HAL_GFXTIM_ABSTIM_Reset(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_ABSTIM_COUNTER(counter));

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_LINE_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  }

  if (((uint32_t)counter & (uint32_t)HAL_GFXTIM_ABSTIM_FRAME_COUNTER) != 0U)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  }

  LL_GFXTIM_ABSTIM_ForceResetCounter(GFXTIM_GET_INSTANCE(hgfxtim), (((uint32_t)counter) << 1U));

  return HAL_OK;
}

/**
  * @brief  Get the absolute line and frame counters value simultaneously.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_frame Pointer to the absolute frame counter.
  * @param  p_line  Pointer to the absolute line counter.
  */
void HAL_GFXTIM_ABSTIM_GetCounter(hal_gfxtim_handle_t *hgfxtim, uint32_t *p_frame, uint32_t *p_line)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->global_state, (uint32_t)HAL_GFXTIM_STATE_INIT);

  *p_line = (LL_GFXTIM_ABSTIM_GetCounter(GFXTIM_GET_INSTANCE(hgfxtim)) & GFXTIM_ATR_LINE);
  *p_frame = (LL_GFXTIM_ABSTIM_GetCounter(GFXTIM_GET_INSTANCE(hgfxtim)) >> GFXTIM_ATR_FRAME_Pos);
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group5
  * @{
  This subsection provides a set of functions allowing to manage the relative timers:
  - Call HAL_GFXTIM_RELTIM_StartContinuous() to start the relative frame counter in continuous mode.
  - Call HAL_GFXTIM_RELTIM_StopContinuous() to stop the relative frame counter in continuous mode.
  - Call HAL_GFXTIM_RELTIM_SetReloadValue() to set the relative frame counter reload value.
  - Call HAL_GFXTIM_RELTIM_ForceReload() to force reload the relative frame counter.
  - Call HAL_GFXTIM_RELTIM_GetCounter() to get the relative frame counter value.
  - Call HAL_GFXTIM_RELTIM_StartOneShot() to start the relative frame counter in one shot mode.
  - Call HAL_GFXTIM_RELTIM_PollForOneShot() to poll the relative frame counter for one shot mode.
  */

/**
  * @brief  Start the relative frame counter in continuous mode.
  * @param  hgfxtim        Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter        This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @param  autoreload_val Value between 0x0 and 0xFFF.
  * @param  interrupt      This parameter can be one of the following values:
  *                        @arg HAL_GFXTIM_NONE_IT: No interruption.
  *                        @arg HAL_GFXTIM_RELTIM_COUNT_IT: Relative frame counter interrupt enabled.
  * @retval HAL_OK         Relative frame counter is successfully started in continuous mode.
  */
hal_status_t HAL_GFXTIM_RELTIM_StartContinuous(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                               uint32_t autoreload_val, uint32_t interrupt)
{
  GFXTIM_TypeDef *p_gfxtim;

  uint32_t pos_it;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_REALOAD_VALUE(autoreload_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_IT(interrupt));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (counter == HAL_GFXTIM_RELTIM_COUNTER_1)
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_1_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_IDLE);

    HAL_CHECK_UPDATE_STATE(hgfxtim, reltim_1_state, HAL_GFXTIM_RELTIM_STATE_IDLE,
                           HAL_GFXTIM_RELTIM_STATE_ACTIVE_CONTINUOUS);

    pos_it = 0U;
  }
  else
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_2_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_IDLE);

    HAL_CHECK_UPDATE_STATE(hgfxtim, reltim_2_state, HAL_GFXTIM_RELTIM_STATE_IDLE,
                           HAL_GFXTIM_RELTIM_STATE_ACTIVE_CONTINUOUS);

    pos_it = 1U;
  }

  LL_GFXTIM_EnableIT(p_gfxtim, (interrupt << pos_it));

  LL_GFXTIM_RELTIM_SetReloadValue(p_gfxtim, (uint32_t)counter, autoreload_val);

  LL_GFXTIM_RELTIM_EnableContinuous(p_gfxtim, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Stop the relative frame counter in continuous mode.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @retval HAL_OK    Relative frame counter is successfully stopped.
  */
hal_status_t HAL_GFXTIM_RELTIM_StopContinuous(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (counter == HAL_GFXTIM_RELTIM_COUNTER_1)
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_1_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_ACTIVE_CONTINUOUS);

    LL_GFXTIM_DisableIT(p_gfxtim, LL_GFXTIM_RELTIM_COUNT_1_IT);

    hgfxtim->reltim_1_state = HAL_GFXTIM_RELTIM_STATE_IDLE;
  }
  else
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_2_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_ACTIVE_CONTINUOUS);

    LL_GFXTIM_DisableIT(p_gfxtim, LL_GFXTIM_RELTIM_COUNT_2_IT);

    hgfxtim->reltim_2_state = HAL_GFXTIM_RELTIM_STATE_IDLE;
  }

  LL_GFXTIM_RELTIM_DisableFrameCounter(p_gfxtim, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Force reload the relative frame counter.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @retval HAL_OK    Relative frame counter is successfully reload forced.
  */
hal_status_t HAL_GFXTIM_RELTIM_ForceReload(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));
  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_RELTIM_ForceReloadCounter(GFXTIM_GET_INSTANCE(hgfxtim), (((uint32_t)counter) << 2U));

  return HAL_OK;
}

/**
  * @brief  Set the relative frame counter reload value.
  * @param  hgfxtim        Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter      This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @param  autoreload_val This parameter can be a number between 0x000 and 0xFFF.
  * @retval HAL_OK         Relative frame counter is successfully reloaded.
  */
hal_status_t HAL_GFXTIM_RELTIM_SetReloadValue(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                              uint32_t autoreload_val)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_REALOAD_VALUE(autoreload_val));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  LL_GFXTIM_RELTIM_SetReloadValue(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)counter, autoreload_val);

  return HAL_OK;
}

/**
  * @brief  Get the relative frame counter value.
  * @param  hgfxtim  Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter  This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @retval uint32_t Value of the relative frame counter.
  */
uint32_t HAL_GFXTIM_RELTIM_GetCounter(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  return (LL_GFXTIM_RELTIM_GetCounterValue(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)counter));
}

/**
  * @brief  Start the relative frame counter in one shot mode.
  * @param  hgfxtim        Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter      This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @param  autoreload_val This parameter can be a number between 0x000 and 0xFFF.
  * @param  interrupt      This parameter can be one of the following values:
  *                        @arg HAL_GFXTIM_NONE_IT: No interruption.
  *                        @arg HAL_GFXTIM_RELTIM_COUNT_IT: Relative frame counter interruption.
  * @note   The interruptions are activated according to the chosen relative frame counter.
  * @retval HAL_OK         Relative frame counter is successfully started in one shot mode.
  */
hal_status_t HAL_GFXTIM_RELTIM_StartOneShot(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                            uint32_t autoreload_val, uint32_t interrupt)
{
  GFXTIM_TypeDef *p_gfxtim;

  uint32_t pos_it;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_REALOAD_VALUE(autoreload_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_IT(interrupt));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  if (counter == HAL_GFXTIM_RELTIM_COUNTER_1)
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_1_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_IDLE);

    HAL_CHECK_UPDATE_STATE(hgfxtim, reltim_1_state, HAL_GFXTIM_RELTIM_STATE_IDLE,
                           HAL_GFXTIM_RELTIM_STATE_ACTIVE_ONESHOT);

    pos_it = 0U;
  }
  else
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_2_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_IDLE);

    HAL_CHECK_UPDATE_STATE(hgfxtim, reltim_2_state, HAL_GFXTIM_RELTIM_STATE_IDLE,
                           HAL_GFXTIM_RELTIM_STATE_ACTIVE_ONESHOT);

    pos_it = 1U;
  }

  LL_GFXTIM_EnableIT(p_gfxtim, (interrupt << pos_it));

  LL_GFXTIM_RELTIM_SetReloadValue(p_gfxtim, (uint32_t)counter, autoreload_val);

  LL_GFXTIM_RELTIM_EnableOneShot(p_gfxtim, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Polling the relative frame counter for one shot mode.
  * @param  hgfxtim     Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter   This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @param  timeout_ms  Specifies the user timeout in millisecond.
  * @retval HAL_TIMEOUT User timeout.
  * @retval HAL_OK      Polling for one shot mode is successfully.
  */
hal_status_t HAL_GFXTIM_RELTIM_PollForOneShot(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                              uint32_t timeout_ms)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  tickstart = HAL_GetTick();

  if (counter == HAL_GFXTIM_RELTIM_COUNTER_1)
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_1_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_ACTIVE_ONESHOT);

    while (LL_GFXTIM_IsActiveFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_RFC1R) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > timeout_ms)
      {
        return HAL_TIMEOUT;
      }
    }

    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_RFC1R);

    hgfxtim->reltim_1_state = HAL_GFXTIM_RELTIM_STATE_IDLE;
  }
  else
  {
    ASSERT_DBG_STATE(hgfxtim->reltim_2_state, (uint32_t)HAL_GFXTIM_RELTIM_STATE_ACTIVE_ONESHOT);

    while (LL_GFXTIM_IsActiveFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_RFC2R) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > timeout_ms)
      {
        return HAL_TIMEOUT;
      }
    }

    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_RFC2R);

    hgfxtim->reltim_2_state = HAL_GFXTIM_RELTIM_STATE_IDLE;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group6
  * @{
  This subsection provides a set of functions allowing to manage the event generator:
  - Call HAL_GFXTIM_EVENTGEN_SetConfig() to configure the event generator.
  - Call HAL_GFXTIM_EVENTGEN_GetConfig() to get the event generator configuration.
  - Call HAL_GFXTIM_EVENTGEN_Start() to start the event generator.
  - Call HAL_GFXTIM_EVENTGEN_Stop() to stop the event generator.
  */

/**
  * @brief  Configure the event generator.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  event_gen This parameter is an element of \ref hal_gfxtim_eventgen_event_t enumeration.
  * @param  p_config  Pointer to hal_gfxtim_eventgen_config_t structure.
  * @retval HAL_OK    Event generator is successfully configured.
  */
hal_status_t HAL_GFXTIM_EVENTGEN_SetConfig(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen,
                                           const hal_gfxtim_eventgen_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_EVENT(event_gen));
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_LINE(p_config->line_event));
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_FRAME(p_config->frame_event));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);;

  LL_GFXTIM_EVENTGEN_Config(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)event_gen, (uint32_t)p_config->line_event,
                            (uint32_t)p_config->frame_event);

  return HAL_OK;
}

/**
  * @brief  Get the event generator configuration.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  event_gen This parameter is an element of \ref hal_gfxtim_eventgen_event_t enumeration.
  * @param  p_config  Pointer to hal_gfxtim_eventgen_config_t structure that will be filled by the GFXTIM
  *                   event generator configuration.
  */
void HAL_GFXTIM_EVENTGEN_GetConfig(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen,
                                   hal_gfxtim_eventgen_config_t *p_config)
{
  uint32_t tmp_evsr;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_EVENT(event_gen));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  tmp_evsr = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), EVSR);
  p_config->line_event = (hal_gfxtim_eventgen_line_src_t)(uint32_t)((tmp_evsr & (GFXTIM_EVSR_LES1 << \
                                                                                 (POSITION_VAL((uint32_t)event_gen) \
                                                                                  * 8U))) >> \
                                                                    (POSITION_VAL((uint32_t)event_gen) * 8U));
  p_config->frame_event = (hal_gfxtim_eventgen_frame_src_t)(uint32_t)((tmp_evsr & (GFXTIM_EVSR_FES1 << \
                                                                       (POSITION_VAL((uint32_t)event_gen) * 8U))) >> \
                                                                      (POSITION_VAL((uint32_t)event_gen) * 8U));
}

/**
  * @brief  Start the event generator.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  event_gen This parameter is an element of \ref hal_gfxtim_eventgen_event_t enumeration.
  * @param  interrupt This parameter can be one of the following values:
  *                   @arg HAL_GFXTIM_NONE_IT: No interruption.
  *                   @arg HAL_GFXTIM_EVENTGEN_EVENT_IT: Event Generator interruption.
  * @retval HAL_OK    Event generator is successfully started.
  */
hal_status_t HAL_GFXTIM_EVENTGEN_Start(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen,
                                       uint32_t interrupt)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_EVENT(event_gen));
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_INTERRUPT(interrupt));

  ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                   (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  LL_GFXTIM_EnableIT(p_gfxtim, (interrupt << POSITION_VAL((uint32_t)event_gen)));

  LL_GFXTIM_EVENTGEN_Enable(p_gfxtim, (uint32_t)event_gen);

  return HAL_OK;
}

/**
  * @brief  Stop the event generator.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  event_gen This parameter is an element of \ref hal_gfxtim_eventgen_event_t enumeration.
  * @retval HAL_OK    Event generator is successfully stopped.
  */
hal_status_t HAL_GFXTIM_EVENTGEN_Stop(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_EVENTGEN_EVENT(event_gen));

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  LL_GFXTIM_DisableIT(p_gfxtim, (LL_GFXTIM_EVENTGEN_EVENT_1_IT << (POSITION_VAL((uint32_t)event_gen))));

  LL_GFXTIM_EVENTGEN_Disable(p_gfxtim, (uint32_t)event_gen);

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group7
  * @{
  This subsection provides a set of functions allowing to manage the watchdog counter:
  - Call HAL_GFXTIM_WDG_SetConfig() to configure the watchdog counter.
  - Call HAL_GFXTIM_WDG_GetConfig() to get the watchdog counter configuration.
  - Call HAL_GFXTIM_WDG_Start() to start the watchdog counter.
  - Call HAL_GFXTIM_WDG_Stop() to stop the watchdog counter.
  - Call HAL_GFXTIM_WDG_Refresh() to refrech the watchdog counter.
  */

/**
  * @brief  Configure the GFXTIM watchdog counter.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_config  Pointer to \ref hal_gfxtim_wdg_config_t structure.
  * @retval HAL_OK    Watchdog counter is successfully configured.
  */
hal_status_t HAL_GFXTIM_WDG_SetConfig(hal_gfxtim_handle_t *hgfxtim, const hal_gfxtim_wdg_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_WDG_CLK_SRC(p_config->src));

  if (p_config->src == HAL_GFXTIM_WDG_CLK_LINE_CLK)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  }
  if (p_config->src == HAL_GFXTIM_WDG_CLK_FRAME_CLK)
  {
    ASSERT_DBG_STATE(hgfxtim->clkgen_state, (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED |
                     (uint32_t)HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED);
  }

  ASSERT_DBG_STATE(hgfxtim->wdg_state, (uint32_t)HAL_GFXTIM_WDG_STATE_RESET | (uint32_t)HAL_GFXTIM_WDG_STATE_IDLE);

  LL_GFXTIM_WDG_SetSource(GFXTIM_GET_INSTANCE(hgfxtim), (uint32_t)p_config->src);

  hgfxtim->wdg_state = HAL_GFXTIM_WDG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the watchdog counter configuration.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_config  Pointer to \ref hal_gfxtim_wdg_config_t structure that will be filled by the GFXTIM
  *                   watchdog configuration.
  */
void HAL_GFXTIM_WDG_GetConfig(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_wdg_config_t *p_config)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hgfxtim->wdg_state, (uint32_t)HAL_GFXTIM_WDG_STATE_IDLE | (uint32_t)HAL_GFXTIM_WDG_STATE_ACTIVE);

  p_config->src = (hal_gfxtim_wdg_clk_src_t) LL_GFXTIM_WDG_GetSource(GFXTIM_GET_INSTANCE(hgfxtim));
}

/**
  * @brief  Start the GFXTIM watchdog counter.
  * @param  hgfxtim      Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  reload_val   Value between 0x0 and 0xFFFF.
  * @param  prealarm_val Value between 0x0 and 0xFFFF.
  * @param  interrupts   This parameter can be one or a combination of the following values:
  *                      @arg HAL_GFXTIM_NONE_IT: No interruption.
  *                      @arg HAL_GFXTIM_WDG_ALARM_IT: Watchdog alarm interruption.
  *                      @arg HAL_GFXTIM_WDG_PREALARM_IT: Watchdog pre-alarm interruption.
  *                      @arg HAL_GFXTIM_WDG_ALL_IT: All watchdog interruption.
  * @retval HAL_OK  Watchdog counter is successfully started.
  */
hal_status_t HAL_GFXTIM_WDG_Start(hal_gfxtim_handle_t *hgfxtim, uint32_t reload_val, uint32_t prealarm_val,
                                  uint32_t interrupts)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_WDG_COUNTER_VALUE(reload_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_WDG_COUNTER_VALUE(prealarm_val));
  ASSERT_DBG_PARAM(IS_GFXTIM_WDG_IT(interrupts));

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  ASSERT_DBG_STATE(hgfxtim->wdg_state, (uint32_t)HAL_GFXTIM_WDG_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hgfxtim, wdg_state, HAL_GFXTIM_WDG_STATE_IDLE, HAL_GFXTIM_WDG_STATE_ACTIVE);

  LL_GFXTIM_EnableIT(p_gfxtim, interrupts);

  LL_GFXTIM_WDG_SetReloadValue(p_gfxtim, reload_val);

  LL_GFXTIM_WDG_SetPrealarmValue(p_gfxtim, prealarm_val);

  LL_GFXTIM_WDG_Enable(p_gfxtim);

  return HAL_OK;
}

/**
  * @brief  Stop the watchdog counter.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  Watchdog counter is successfully stopped.
  */
hal_status_t HAL_GFXTIM_WDG_Stop(hal_gfxtim_handle_t *hgfxtim)
{
  GFXTIM_TypeDef *p_gfxtim;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->wdg_state, (uint32_t)HAL_GFXTIM_WDG_STATE_ACTIVE);

  p_gfxtim = GFXTIM_GET_INSTANCE(hgfxtim);

  LL_GFXTIM_DisableIT(p_gfxtim, LL_GFXTIM_WDG_ALL_IT);

  LL_GFXTIM_WDG_Disable(p_gfxtim);

  hgfxtim->wdg_state = HAL_GFXTIM_WDG_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Refresh the GFXTIM watchdog counter.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval HAL_OK  The GFXTIM Watchdog counter is successfully refreshed.
  */
hal_status_t HAL_GFXTIM_WDG_Refresh(hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  ASSERT_DBG_STATE(hgfxtim->wdg_state, (uint32_t)HAL_GFXTIM_WDG_STATE_ACTIVE);

  LL_GFXTIM_WDG_Refresh(GFXTIM_GET_INSTANCE(hgfxtim));

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group8
  * @{
  This subsection provides a set of functions allowing to retrieve peripheral state:
  - Call HAL_GFXTIM_GetState() to return the GFXTIM global state.
  - Call HAL_GFXTIM_CLKGEN_GetState() to return the GFXTIM clock generator state.
  - Call HAL_GFXTIM_ABSTIM_GetLineState() to return the GFXTIM absolute line state.
  - Call HAL_GFXTIM_ABSTIM_GetFrameState() to return the GFXTIM absolute frame state.
  - Call HAL_GFXTIM_RELTIM_GetState() to return the GFXTIM relative frame state.
  - Call HAL_GFXTIM_WDG_GetState() to return the GFXTIM watchdog state.
  */

/**
  * @brief  Get the GFXTIM current global state.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_state_t Global state.
  */
hal_gfxtim_state_t HAL_GFXTIM_GetState(const hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  return hgfxtim->global_state;
}

/**
  * @brief  Get the GFXTIM clock generator state.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_clkgen_state_t Clock generator state.
  */
hal_gfxtim_clkgen_state_t HAL_GFXTIM_CLKGEN_GetState(const hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  return hgfxtim->clkgen_state;
}

/**
  * @brief  Get the GFXTIM absolute line state.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_abstim_line_state_t Absolute line state.
  */
hal_gfxtim_abstim_line_state_t HAL_GFXTIM_ABSTIM_GetLineState(const hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  return hgfxtim->abstim_line_state;
}

/**
  * @brief  Get the GFXTIM absolute frame state.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_abstim_frame_state_t Absolute frame state.
  */
hal_gfxtim_abstim_frame_state_t HAL_GFXTIM_ABSTIM_GetFrameState(const hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  return hgfxtim->abstim_frame_state;
}

/**
  * @brief  Get the GFXTIM relative frame state.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  * @retval hal_gfxtim_reltim_state_t Relative frame x (1 or 2) state.
  */
hal_gfxtim_reltim_state_t HAL_GFXTIM_RELTIM_GetState(const hal_gfxtim_handle_t *hgfxtim,
                                                     hal_gfxtim_reltim_counter_t counter)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);
  ASSERT_DBG_PARAM(IS_GFXTIM_RELTIM_COUNTER(counter));

  if (counter == HAL_GFXTIM_RELTIM_COUNTER_1)
  {
    return hgfxtim->reltim_1_state;
  }
  else
  {
    return hgfxtim->reltim_2_state;
  }
}

/**
  * @brief  Get the GFXTIM watchdog counter state.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval hal_gfxtim_wdg_state_t Watchdog counter state.
  */
hal_gfxtim_wdg_state_t HAL_GFXTIM_WDG_GetState(const hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  return hgfxtim->wdg_state;
}
/**
  * @}
  */

/** @addtogroup GFXTIM_Exported_Functions_Group9
  * @{
 This subsection provides the IRQ handler APIs allowing to handle GFXTIM interruptions and register user Callbacks APIs:
  - Call HAL_GFXTIM_IRQHandler() to handle all GFXTIM interrupts.
  - Call HAL_GFXTIM_TearingEffectIRQHandler() to handle only the tearing-effect interrupt.
  - Call HAL_GFXTIM_ABSTIM_FrameIRQHandler() to handle only the absolute frame interrupts.
  - Call HAL_GFXTIM_ABSTIM_LineIRQHandler() to handle only the absolute line interrupts.
  - Call HAL_GFXTIM_RELTIM_IRQHandler() to handle only the relative framed interrupts.
  - Call HAL_GFXTIM_EVENTGEN_IRQHandler() to handle only the event generator interrupts.
  - Call HAL_GFXTIM_WDG_IRQHandler() to handle only the GFXTIM watchdog interrupts.
  - Call HAL_GFXTIM_RegisterTearingEffectCallback() to register the tearing-effect callback.
  - Call HAL_GFXTIM_ABSTIM_RegisterFCmpCallback() to register the absolute frame counter compare 1 callback.
  - Call HAL_GFXTIM_ABSTIM_RegisterFCntOverFlowCallback() to register the absolute frame counter overflow callback.
  - Call HAL_GFXTIM_ABSTIM_RegisterLCmpCallback() to register the absolute line counter compares callback.
  - Call HAL_GFXTIM_ABSTIM_RegisterLCntOverFlowCallback() to register the absolute line counter overflow callback.
  - Call HAL_GFXTIM_RELTIM_RegisterFCntReloadCallback() to register the relative frame counter reload callback.
  - Call HAL_GFXTIM_EVENTGEN_RegisterEventCallback() to register the event generator callback.
  - Call HAL_GFXTIM_WDG_RegisterAlarmCallback() to register the watchdog alarm callback.
  - Call HAL_GFXTIM_WDG_RegisterPreAlarmCallback() to register the watchdog pre-alarm callback.
  */
/**
  * @brief  Handle the GFXTIM interrupt request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_IRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;
  hal_gfxtim_eventgen_event_t  event_gen;
  hal_gfxtim_reltim_counter_t   counter;
  hal_gfxtim_abstim_line_comp_t line_comp;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources   = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  if (((flag_status & LL_GFXTIM_FLAG_TE) != 0U) && ((it_sources & LL_GFXTIM_TEARING_EFFECT_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_TE);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_tearing_effect_cb(hgfxtim);
#else
    HAL_GFXTIM_TearingEffectCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_AFCC1) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_FRAME_COMP_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_AFCC1);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_frame_comp_cb(hgfxtim);
#else
    HAL_GFXTIM_ABSTIM_FCmpCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_AFCO) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_AFCO);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_frame_ovf_cb(hgfxtim);
#else
    HAL_GFXTIM_ABSTIM_FCntOverFlowCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & (LL_GFXTIM_FLAG_ALCC1 | LL_GFXTIM_FLAG_ALCC2)) != 0U) \
      && ((it_sources & (LL_GFXTIM_ABSTIM_LINE_COMP1_IT | LL_GFXTIM_ABSTIM_LINE_COMP2_IT)) != 0U))
  {
    if (((flag_status & LL_GFXTIM_FLAG_ALCC1) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_LINE_COMP1_IT) != 0U))
    {
      line_comp = HAL_GFXTIM_ABSTIM_LINE_COMP_1;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_ALCC1);
    }
    else
    {
      line_comp = HAL_GFXTIM_ABSTIM_LINE_COMP_2;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_ALCC2);
    }

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_line_comp_cb(hgfxtim, line_comp);
#else
    HAL_GFXTIM_ABSTIM_LCmpCallback(hgfxtim, line_comp);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_ALCO) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_ALCO);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_line_ovf_cb(hgfxtim);
#else
    HAL_GFXTIM_ABSTIM_LCntOverFlowCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & (LL_GFXTIM_FLAG_RFC1R | LL_GFXTIM_FLAG_RFC2R)) != 0U) \
      && ((it_sources & (LL_GFXTIM_RELTIM_COUNT_1_IT | LL_GFXTIM_RELTIM_COUNT_2_IT)) != 0U))
  {
    if (((flag_status & LL_GFXTIM_FLAG_RFC1R) != 0U) && ((it_sources & LL_GFXTIM_RELTIM_COUNT_1_IT) != 0U))
    {
      counter = HAL_GFXTIM_RELTIM_COUNTER_1;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_RFC1R);
    }
    else
    {
      counter = HAL_GFXTIM_RELTIM_COUNTER_2;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_RFC2R);
    }

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_rel_counter_cb(hgfxtim, counter);
#else
    HAL_GFXTIM_RELTIM_FCntReloadCallback(hgfxtim, counter);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & (LL_GFXTIM_FLAG_EV1 | LL_GFXTIM_FLAG_EV2 | LL_GFXTIM_FLAG_EV3 | LL_GFXTIM_FLAG_EV4)) != 0U) \
      && ((it_sources & (LL_GFXTIM_EVENTGEN_EVENT_1_IT | LL_GFXTIM_EVENTGEN_EVENT_2_IT | LL_GFXTIM_EVENTGEN_EVENT_3_IT |
                         LL_GFXTIM_EVENTGEN_EVENT_4_IT)) != 0U))
  {
    if (((flag_status & LL_GFXTIM_FLAG_EV1) != 0U) && ((it_sources & LL_GFXTIM_EVENTGEN_EVENT_1_IT) != 0U))
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_1;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_EV1);
    }
    else if (((flag_status & LL_GFXTIM_FLAG_EV2) != 0U) && ((it_sources & LL_GFXTIM_EVENTGEN_EVENT_2_IT) != 0U))
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_2;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_EV2);
    }
    else if (((flag_status & LL_GFXTIM_FLAG_EV3) != 0U) && ((it_sources & LL_GFXTIM_EVENTGEN_EVENT_3_IT) != 0U))
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_3;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_EV3);
    }
    else
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_4;

      LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_EV4);
    }

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_eventgen_cb(hgfxtim, event_gen);
#else
    HAL_GFXTIM_EVENTGEN_EventCallback(hgfxtim, event_gen);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_WDGA) != 0U) && ((it_sources & LL_GFXTIM_WDG_ALARM_IT) != 0U))
  {

    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_WDGA);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_wdg_alarm_cb(hgfxtim);
#else
    HAL_GFXTIM_WDG_AlarmCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_WDGP) != 0U) && ((it_sources & LL_GFXTIM_WDG_PREALARM_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_WDGP);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_wdg_prealarm_cb(hgfxtim);
#else
    HAL_GFXTIM_WDG_PreAlarmCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle the GFXTIM tearing-effect interrupt request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_TearingEffectIRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources   = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_TE);

  if (((flag_status & LL_GFXTIM_FLAG_TE) != 0U) && ((it_sources & LL_GFXTIM_TEARING_EFFECT_IT) != 0U))
  {

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_tearing_effect_cb(hgfxtim);
#else
    HAL_GFXTIM_TearingEffectCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle the GFXTIM absolute frame interrupts request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_ABSTIM_FrameIRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources  = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_ABSTIM_FRAME_ALL_IT);

  if (((flag_status & LL_GFXTIM_FLAG_AFCC1) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_FRAME_COMP_IT) != 0U))
  {

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_frame_comp_cb(hgfxtim);
#else
    HAL_GFXTIM_ABSTIM_FCmpCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_AFCO) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT) != 0U))
  {

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_frame_ovf_cb(hgfxtim);
#else
    HAL_GFXTIM_ABSTIM_FCntOverFlowCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle the GFXTIM absolute line interrupts request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_ABSTIM_LineIRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;
  hal_gfxtim_abstim_line_comp_t line_comp;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources  = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_ABSTIM_LINE_ALL_IT);

  if (((flag_status & (LL_GFXTIM_FLAG_ALCC1 | LL_GFXTIM_FLAG_ALCC2)) != 0U) \
      && ((it_sources & (LL_GFXTIM_ABSTIM_LINE_COMP1_IT | LL_GFXTIM_ABSTIM_LINE_COMP2_IT)) != 0U))
  {
    if (((flag_status & LL_GFXTIM_FLAG_ALCC1) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_LINE_COMP1_IT) != 0U))
    {
      line_comp = HAL_GFXTIM_ABSTIM_LINE_COMP_1;
    }
    else
    {
      line_comp = HAL_GFXTIM_ABSTIM_LINE_COMP_2;
    }

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_line_comp_cb(hgfxtim, line_comp);
#else
    HAL_GFXTIM_ABSTIM_LCmpCallback(hgfxtim, line_comp);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_ALCO) != 0U) && ((it_sources & LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT) != 0U))
  {

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_abs_line_ovf_cb(hgfxtim);
#else
    HAL_GFXTIM_ABSTIM_LCntOverFlowCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Handle the GFXTIM relative frame interrupts request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_RELTIM_IRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;
  hal_gfxtim_reltim_counter_t counter;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources   = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), (LL_GFXTIM_FLAG_RFC1R | LL_GFXTIM_FLAG_RFC2R));

  if (((flag_status & (LL_GFXTIM_FLAG_RFC1R | LL_GFXTIM_FLAG_RFC2R)) != 0U) \
      && ((it_sources & (LL_GFXTIM_RELTIM_COUNT_1_IT | LL_GFXTIM_RELTIM_COUNT_2_IT)) != 0U))
  {
    if (((flag_status & LL_GFXTIM_FLAG_RFC1R) != 0U) && ((it_sources & LL_GFXTIM_RELTIM_COUNT_1_IT) != 0U))
    {
      counter = HAL_GFXTIM_RELTIM_COUNTER_1;
    }
    else
    {
      counter = HAL_GFXTIM_RELTIM_COUNTER_2;
    }

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_rel_counter_cb(hgfxtim, counter);
#else
    HAL_GFXTIM_RELTIM_FCntReloadCallback(hgfxtim, counter);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */

  }
}

/**
  * @brief  Handle the GFXTIM event generator interrupts request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_EVENTGEN_IRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;
  hal_gfxtim_eventgen_event_t event_gen;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources   = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), (LL_GFXTIM_FLAG_EV1 | LL_GFXTIM_FLAG_EV2 | \
                                                     LL_GFXTIM_FLAG_EV3 | LL_GFXTIM_FLAG_EV4));

  if (((flag_status & (LL_GFXTIM_FLAG_EV1 | LL_GFXTIM_FLAG_EV2 | LL_GFXTIM_FLAG_EV3 | LL_GFXTIM_FLAG_EV4)) != 0U) \
      && ((it_sources & (LL_GFXTIM_EVENTGEN_EVENT_1_IT | LL_GFXTIM_EVENTGEN_EVENT_2_IT | LL_GFXTIM_EVENTGEN_EVENT_3_IT |
                         LL_GFXTIM_EVENTGEN_EVENT_4_IT)) != 0U))
  {
    if (((flag_status & LL_GFXTIM_FLAG_EV1) != 0U) && ((it_sources & LL_GFXTIM_EVENTGEN_EVENT_1_IT) != 0U))
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_1;
    }
    else if (((flag_status & LL_GFXTIM_FLAG_EV2) != 0U) && ((it_sources & LL_GFXTIM_EVENTGEN_EVENT_2_IT) != 0U))
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_2;
    }
    else if (((flag_status & LL_GFXTIM_FLAG_EV3) != 0U) && ((it_sources & LL_GFXTIM_EVENTGEN_EVENT_3_IT) != 0U))
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_3;
    }
    else
    {
      event_gen = HAL_GFXTIM_EVENTGEN_EVENT_4;
    }

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_eventgen_cb(hgfxtim, event_gen);
#else
    HAL_GFXTIM_EVENTGEN_EventCallback(hgfxtim, event_gen);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */

  }
}

/**
  * @brief  Handle the GFXTIM watchdog timer interrupts request.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
void HAL_GFXTIM_WDG_IRQHandler(hal_gfxtim_handle_t *hgfxtim)
{
  uint32_t flag_status;
  uint32_t it_sources;

  ASSERT_DBG_PARAM(hgfxtim != NULL);

  flag_status = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), ISR);
  it_sources   = LL_GFXTIM_READ_REG(GFXTIM_GET_INSTANCE(hgfxtim), IER);

  if (((flag_status & LL_GFXTIM_FLAG_WDGA) != 0U) && ((it_sources & LL_GFXTIM_WDG_ALARM_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_WDGA);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_wdg_alarm_cb(hgfxtim);
#else
    HAL_GFXTIM_WDG_AlarmCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }

  if (((flag_status & LL_GFXTIM_FLAG_WDGP) != 0U) && ((it_sources & LL_GFXTIM_WDG_PREALARM_IT) != 0U))
  {
    LL_GFXTIM_ClearFlag(GFXTIM_GET_INSTANCE(hgfxtim), LL_GFXTIM_FLAG_WDGP);

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
    hgfxtim->p_wdg_prealarm_cb(hgfxtim);
#else
    HAL_GFXTIM_WDG_PreAlarmCallback(hgfxtim);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  GFXTIM Tearing-effect callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
__WEAK void HAL_GFXTIM_TearingEffectCallback(hal_gfxtim_handle_t *hgfxtim)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_TearingEffectCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Absolute frame counter compare callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
__WEAK void HAL_GFXTIM_ABSTIM_FCmpCallback(hal_gfxtim_handle_t *hgfxtim)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);

  /* WARNING : This function must not be modified, when the function is needed,
   *            the HAL_GFXTIM_ABSTIM_FCmpCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Absolute frame counter overflow callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
__WEAK void HAL_GFXTIM_ABSTIM_FCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_ABSTIM_FCntOverFlowCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Absolute line counter compares callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  line_comp This parameter is an element of \ref hal_gfxtim_abstim_line_comp_t enumeration.
  */
__WEAK void HAL_GFXTIM_ABSTIM_LCmpCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_line_comp_t line_comp)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);
  STM32_UNUSED(line_comp);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_ABSTIM_LineCompCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Absolute line counter overflow callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
__WEAK void HAL_GFXTIM_ABSTIM_LCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_ABSTIM_LCntOverFlowCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Relative frame counters reload callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  counter This parameter is an element of \ref hal_gfxtim_reltim_counter_t enumeration.
  */
__WEAK void HAL_GFXTIM_RELTIM_FCntReloadCallback(hal_gfxtim_handle_t *hgfxtim,
                                                 hal_gfxtim_reltim_counter_t counter)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);
  STM32_UNUSED(counter);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_RELTIM_FCntReloadCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Event generator callback.
  * @param  hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  event_gen This parameter is an element of \ref hal_gfxtim_eventgen_event_t enumeration.
  */
__WEAK void HAL_GFXTIM_EVENTGEN_EventCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);
  STM32_UNUSED(event_gen);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_EVENTGEN_EventCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Watchdog alarm callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
__WEAK void HAL_GFXTIM_WDG_AlarmCallback(hal_gfxtim_handle_t *hgfxtim)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_WDG_AlarmCallback could be implemented in the user file
   */
}

/**
  * @brief  GFXTIM Watchdog pre-alarm callback.
  * @param  hgfxtim Pointer to \ref hal_gfxtim_handle_t structure.
  */
__WEAK void HAL_GFXTIM_WDG_PreAlarmCallback(hal_gfxtim_handle_t *hgfxtim)
{
  /* Prevent STM32_UNUSED argument(s) compilation warning */
  STM32_UNUSED(hgfxtim);

  /* WARNING : This function must not be modified, when the function is needed,
   *           the HAL_GFXTIM_WDG_PreAlarmCallback could be implemented in the user file
   */
}

#if (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the tearing-effect callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the tearing effect callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM tearing-effect callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_RegisterTearingEffectCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_tearing_effect_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the absolute frame counter compare callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the absolute frame counter compare callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM absolute frame counter compare callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_ABSTIM_RegisterFCmpCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_abs_frame_comp_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the absolute frame counter overflow callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the absolute frame counter overflow callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM absolute frame counter overflow callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_ABSTIM_RegisterFCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_abs_frame_ovf_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the absolute line counter compares callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the absolute line counter compare callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM absolute line counter compares callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_ABSTIM_RegisterLCmpCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_line_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_abs_line_comp_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the absolute line counter overflow callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the absolute line counter overflow callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM absolute line counter overflow callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_ABSTIM_RegisterLCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim,
                                                            hal_gfxtim_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_abs_line_ovf_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the relative frame counter reload callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the relative frame counter reload callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM relative frame counter reload callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_RELTIM_RegisterFCntReloadCallback(hal_gfxtim_handle_t *hgfxtim,
                                                          hal_gfxtim_frame_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_rel_counter_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the event generator callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the event generator callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM event generator callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_EVENTGEN_RegisterEventCallback(hal_gfxtim_handle_t *hgfxtim,
                                                       hal_gfxtim_eventgen_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_eventgen_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the watchdog alarm callback.
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the watchdog alarm callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM watchdog alarm callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_WDG_RegisterAlarmCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_wdg_alarm_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the watchdog pre-alarm callback
  * @param  hgfxtim           Pointer to \ref hal_gfxtim_handle_t structure.
  * @param  p_callback        Specifies the watchdog pre-alarm callback.
  * @retval HAL_INVALID_PARAM Invalid parameter when p_callback pointer is NULL.
  * @retval HAL_OK            GFXTIM watchdog pre-alarm callback is successfully registered.
 */
hal_status_t HAL_GFXTIM_WDG_RegisterPreAlarmCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hgfxtim != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hgfxtim->p_wdg_prealarm_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */

/**
  * @}
  */

#if defined(USE_HAL_GFXTIM_USER_DATA) && (USE_HAL_GFXTIM_USER_DATA == 1U)
/** @addtogroup GFXTIM_Exported_Functions_Group10
  * @{
  This subsection provides a set of functions allowing to manage the user data pointer:
   - Call HAL_GFXTIM_SetUserData() to set the GFXTIM user data in GFXTIM handle.
   - Call HAL_GFXTIM_GetUserData() to get the GFXTIM user data from GFXTIM handle.
  */

/**
  * @brief Store the user data into the GFXTIM handle.
  * @param hgfxtim      Pointer to \ref hal_gfxtim_handle_t structure.
  * @param p_user_data  Pointer to the user data.
  */
void HAL_GFXTIM_SetUserData(hal_gfxtim_handle_t *hgfxtim, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  hgfxtim->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the GFXTIM handle.
  * @param hgfxtim   Pointer to \ref hal_gfxtim_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_GFXTIM_GetUserData(const hal_gfxtim_handle_t *hgfxtim)
{
  ASSERT_DBG_PARAM(hgfxtim != NULL);

  return (hgfxtim->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_GFXTIM_USER_DATA */

/**
  * @}
  */

#endif /* USE_HAL_GFXTIM_MODULE */
/**
  * @}
  */

/**
  * @}
  */
#endif /* defined(GFXTIM) */
