/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_gfxtim.h
  * @brief   Header file of GFXTIM HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_GFXTIM_H
#define STM32U5XX_HAL_GFXTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_gfxtim.h"

#if defined (GFXTIM)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup GFXTIM GFXTIM
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GFXTIM_Exported_Constants GFXTIM Exported Constants
  * @{
  */

/** @defgroup GFXTIM_Interrupt GFXTIM Interrupts
  * @{
  */
#define HAL_GFXTIM_NONE_IT                         LL_GFXTIM_NONE_IT                        /*!< No interrupts                              */
#define HAL_GFXTIM_ABSTIM_LINE_COMP1_IT            LL_GFXTIM_ABSTIM_LINE_COMP1_IT           /*!< Absolute line counter compare 1 interrupt  */
#define HAL_GFXTIM_ABSTIM_LINE_COMP2_IT            LL_GFXTIM_ABSTIM_LINE_COMP2_IT           /*!< Absolute line counter compare 2 interrupt  */
#define HAL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT   LL_GFXTIM_ABSTIM_LINE_COUNT_OVERFLOW_IT  /*!< Absolute line counter overflow interrupt   */
#define HAL_GFXTIM_ABSTIM_LINE_ALL_IT              LL_GFXTIM_ABSTIM_LINE_ALL_IT             /*!< All absolute line counter interrupts       */

#define HAL_GFXTIM_ABSTIM_FRAME_COMP_IT            LL_GFXTIM_ABSTIM_FRAME_COMP_IT           /*!< Absolute frame counter compare 1 interrupt */
#define HAL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT  LL_GFXTIM_ABSTIM_FRAME_COUNT_OVERFLOW_IT /*!< Absolute frame counter overflow interrupt  */
#define HAL_GFXTIM_ABSTIM_FRAME_ALL_IT             LL_GFXTIM_ABSTIM_FRAME_ALL_IT            /*!< All absolute frame counter interrupts      */

#define HAL_GFXTIM_RELTIM_COUNT_IT                 LL_GFXTIM_RELTIM_COUNT_1_IT              /*!< Relative frame counter 1 interrupt         */
#define HAL_GFXTIM_TEARING_EFFECT_IT               LL_GFXTIM_TEARING_EFFECT_IT              /*!< Tearing-effect interrupt                   */
#define HAL_GFXTIM_EVENTGEN_EVENT_IT               LL_GFXTIM_EVENTGEN_EVENT_1_IT            /*!< Event generator 1 interrupt                */
#define HAL_GFXTIM_WDG_PREALARM_IT                 LL_GFXTIM_WDG_PREALARM_IT                /*!< Watchdog pre-alarm interrupt               */
#define HAL_GFXTIM_WDG_ALARM_IT                    LL_GFXTIM_WDG_ALARM_IT                   /*!< Watchdog alarm interrupt                   */
#define HAL_GFXTIM_WDG_ALL_IT                      LL_GFXTIM_WDG_ALL_IT                     /*!< Watchdog alarm and pre-alarm interrupts    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup GFXTIM_Exported_Types  GFXTIM Exported Types
  * @{
  */

/**
  * @brief GFXTIM instances enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM = (uint32_t)GFXTIM, /*!< GFXTIM Instance */
} hal_gfxtim_t;

/**
  * @brief GFXTIM state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_STATE_RESET = (0U),        /*!< GFXTIM is not yet initialized                */
  HAL_GFXTIM_STATE_INIT  = (1UL << 31U), /*!< GFXTIM is initialized but not yet configured */
} hal_gfxtim_state_t;

/**
  * @brief GFXTIM Clock generator state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_STATE_RESET                 = (1UL << 31U), /*!< GFXTIM Clock generator is not yet initialized        */
  HAL_GFXTIM_CLKGEN_FRAME_STATE_CONFIGURED      = (1UL << 30U), /*!< GFXTIM Frame clock generator is configured           */
  HAL_GFXTIM_CLKGEN_FRAME_LINE_STATE_CONFIGURED = (1UL << 29U)  /*!< GFXTIM Frame and line clock generator are configured */
} hal_gfxtim_clkgen_state_t;

/**
  * @brief GFXTIM Absolute line state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_ABSTIM_LINE_STATE_RESET  = (1UL << 31U), /*!< GFXTIM Absolute line is not yet initialized */
  HAL_GFXTIM_ABSTIM_LINE_STATE_IDLE   = (1UL << 30U), /*!< GFXTIM Absolute line is not active          */
  HAL_GFXTIM_ABSTIM_LINE_STATE_ACTIVE = (1UL << 29U), /*!< GFXTIM Absolute line is activated           */
  HAL_GFXTIM_ABSTIM_LINE_STATE_PAUSED = (1UL << 28U)  /*!< GFXTIM Absolute line is paused              */
} hal_gfxtim_abstim_line_state_t;

/**
  * @brief GFXTIM Absolute frame state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_ABSTIM_FRAME_STATE_RESET  = (1UL << 31U), /*!< GFXTIM Absolute frame is not yet initialized  */
  HAL_GFXTIM_ABSTIM_FRAME_STATE_IDLE   = (1UL << 30U), /*!< GFXTIM Absolute frame is not active           */
  HAL_GFXTIM_ABSTIM_FRAME_STATE_ACTIVE = (1UL << 29U), /*!< GFXTIM Absolute frame is activated            */
  HAL_GFXTIM_ABSTIM_FRAME_STATE_PAUSED = (1UL << 28U)  /*!< GFXTIM Absolute frame is paused               */
} hal_gfxtim_abstim_frame_state_t;

/**
  * @brief GFXTIM Relative timer state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_RELTIM_STATE_RESET             = (1UL << 31U), /*!< GFXTIM Relative frame is not yet initialized       */
  HAL_GFXTIM_RELTIM_STATE_IDLE              = (1UL << 30U), /*!< GFXTIM Relative frame is not active                */
  HAL_GFXTIM_RELTIM_STATE_ACTIVE_CONTINUOUS = (1UL << 29U), /*!< GFXTIM Relative frame continuous mode is activated */
  HAL_GFXTIM_RELTIM_STATE_ACTIVE_ONESHOT    = (1UL << 28U)  /*!< GFXTIM Relative frame one shot mode is activated   */
} hal_gfxtim_reltim_state_t;

/**
  * @brief GFXTIM Watchdog timer state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_WDG_STATE_RESET  = (1UL << 31U), /*!< GFXTIM Watchdog is not yet initialized */
  HAL_GFXTIM_WDG_STATE_IDLE   = (1UL << 30U), /*!< GFXTIM Watchdog is not active          */
  HAL_GFXTIM_WDG_STATE_ACTIVE = (1UL << 29U)  /*!< GFXTIM Watchdog is activated           */
} hal_gfxtim_wdg_state_t;

/**
  * @brief GFXTIM Clock generator counter enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_LINE_CLK_COUNTER       = LL_GFXTIM_LINE_FORCE_RELOAD,      /*!< Line clock counter           */
  HAL_GFXTIM_CLKGEN_FRAME_CLK_COUNTER      = LL_GFXTIM_FRAME_FORCE_RELOAD,     /*!< Frame clock counter          */
  HAL_GFXTIM_CLKGEN_FRAME_LINE_CLK_COUNTER = LL_GFXTIM_LINE_FRAME_FORCE_RELOAD /*!< Line and frame clock counter */
} hal_gfxtim_clkgen_counter_t;

/**
  * @brief GFXTIM Line clock counter hardware reload enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_LCNT_NO_RELOAD              = LL_GFXTIM_CLKGEN_LCNT_NO_RELOAD,              /*!< No hardware reload            */
  HAL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD = LL_GFXTIM_CLKGEN_LCNT_FRAME_UNDERFLOW_RELOAD, /*!< Frame Clock Counter underflow */
  HAL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD    = LL_GFXTIM_CLKGEN_LCNT_HSYNC_RISING_RELOAD,    /*!< HSYNC rising                  */
  HAL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD   = LL_GFXTIM_CLKGEN_LCNT_HSYNC_FALLING_RELOAD,   /*!< HSYNC falling                 */
  HAL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD    = LL_GFXTIM_CLKGEN_LCNT_VSYNC_RISING_RELOAD,    /*!< VSYNC rising                  */
  HAL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD   = LL_GFXTIM_CLKGEN_LCNT_VSYNC_FALLING_RELOAD,   /*!< VSYNC falling                 */
  HAL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD       = LL_GFXTIM_CLKGEN_LCNT_TE_RISING_RELOAD,       /*!< TE rising                     */
  HAL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD      = LL_GFXTIM_CLKGEN_LCNT_TE_FALLING_RELOAD       /*!< TE falling                    */
} hal_gfxtim_clkgen_line_count_reload_src_t;

/**
  * @brief GFXTIM Line clock counter clock source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_LINE_COUNT_NONE       = LL_GFXTIM_CLKGEN_LINE_COUNT_NONE,      /*!< Disable line clock counter        */
  HAL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK = LL_GFXTIM_CLKGEN_LINE_COUNT_GFXTIMHCLK /*!< hclk as line clock counter source */
} hal_gfxtim_clkgen_line_count_src_t;

/**
  * @brief GFXTIM Line clock source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW   = LL_GFXTIM_CLKGEN_LINE_LCNT_UNDERFLOW,       /*!< Line Clock Counter underflow  */
  HAL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW   = LL_GFXTIM_CLKGEN_LINE_FCNT_UNDERFLOW,       /*!< Frame Clock Counter underflow */
  HAL_GFXTIM_CLKGEN_LINE_HSYNC_RISING     = LL_GFXTIM_CLKGEN_LINE_HSYNC_RISING,         /*!< HSYNC rising edge             */
  HAL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING    = LL_GFXTIM_CLKGEN_LINE_HSYNC_FALLING,        /*!< HSYNC falling edge            */
  HAL_GFXTIM_CLKGEN_LINE_VSYNC_RISING     = LL_GFXTIM_CLKGEN_LINE_VSYNC_RISING,         /*!< VSYNC rising edge             */
  HAL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING    = LL_GFXTIM_CLKGEN_LINE_VSYNC_FALLING,        /*!< VSYNC falling edge            */
  HAL_GFXTIM_CLKGEN_LINE_TE_RISING        = LL_GFXTIM_CLKGEN_LINE_TE_RISING,            /*!< TE rising edge                */
  HAL_GFXTIM_CLKGEN_LINE_TE_FALLING       = LL_GFXTIM_CLKGEN_LINE_TE_FALLING            /*!< TE falling edge               */
} hal_gfxtim_clkgen_line_clk_src_t;

/**
  * @brief GFXTIM Frame clock counter hardware reload enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_FCNT_NO_RELOAD             = LL_GFXTIM_CLKGEN_FCNT_NO_RELOAD,             /*!< No hardware reload           */
  HAL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD = LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW_RELOAD, /*!< Line Clock Counter underflow */
  HAL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD   = LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING_RELOAD,   /*!< HSYNC rising edge            */
  HAL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD  = LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING_RELOAD,  /*!< HSYNC falling edge           */
  HAL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD   = LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING_RELOAD,   /*!< VSYNC rising edge            */
  HAL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD  = LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING_RELOAD,  /*!< VSYNC falling edge           */
  HAL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD      = LL_GFXTIM_CLKGEN_FCNT_TE_RISING_RELOAD,      /*!< TE rising edge               */
  HAL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD     = LL_GFXTIM_CLKGEN_FCNT_TE_FALLING_RELOAD      /*!< TE falling edge              */
} hal_gfxtim_clkgen_frame_count_reload_src_t;

/**
  * @brief GFXTIM Frame clock counter clock source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_FCNT_DISABLE        = LL_GFXTIM_CLKGEN_FCNT_DISABLE,        /*!< Disable                      */
  HAL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW = LL_GFXTIM_CLKGEN_FCNT_LINE_UNDERFLOW, /*!< Line Clock Counter underflow */
  HAL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING   = LL_GFXTIM_CLKGEN_FCNT_HSYNC_RISING,   /*!< HSYNC rising edge            */
  HAL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING  = LL_GFXTIM_CLKGEN_FCNT_HSYNC_FALLING,  /*!< HSYNC falling edge           */
  HAL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING   = LL_GFXTIM_CLKGEN_FCNT_VSYNC_RISING,   /*!< VSYNC rising edge            */
  HAL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING  = LL_GFXTIM_CLKGEN_FCNT_VSYNC_FALLING,  /*!< VSYNC falling edge           */
  HAL_GFXTIM_CLKGEN_FCNT_TE_RISING      = LL_GFXTIM_CLKGEN_FCNT_TE_RISING,      /*!< TE rising edge               */
  HAL_GFXTIM_CLKGEN_FCNT_TE_FALLING     = LL_GFXTIM_CLKGEN_FCNT_TE_FALLING      /*!< TE falling edge              */
} hal_gfxtim_clkgen_frame_count_src_t;

/**
  * @brief GFXTIM Frame clock source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW = LL_GFXTIM_CLKGEN_FRAME_LCNT_UNDERFLOW,  /*!< Line Clock Counter underflow  */
  HAL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW = LL_GFXTIM_CLKGEN_FRAME_FCNT_UNDERFLOW,  /*!< Frame Clock Counter underflow */
  HAL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING   = LL_GFXTIM_CLKGEN_FRAME_HSYNC_RISING,    /*!< HSYNC rising edge             */
  HAL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING  = LL_GFXTIM_CLKGEN_FRAME_HSYNC_FALLING,   /*!< HSYNC falling edge            */
  HAL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING   = LL_GFXTIM_CLKGEN_FRAME_VSYNC_RISING,    /*!< VSYNC rising edge             */
  HAL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING  = LL_GFXTIM_CLKGEN_FRAME_VSYNC_FALLING,   /*!< VSYNC falling edge            */
  HAL_GFXTIM_CLKGEN_FRAME_TE_RISING      = LL_GFXTIM_CLKGEN_FRAME_TE_RISING,       /*!< TE rising edge                */
  HAL_GFXTIM_CLKGEN_FRAME_TE_FALLING     = LL_GFXTIM_CLKGEN_FRAME_TE_FALLING       /*!< TE falling edge               */
} hal_gfxtim_clkgen_frame_clk_src_t;

/**
  * @brief GFXTIM clock generator line clock calibration output enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_LINE_CALIB_DISABLED = 0U, /*!< Clock generator line clock calibration output disabled */
  HAL_GFXTIM_CLKGEN_LINE_CALIB_ENABLED  = 1U  /*!< Clock generator line clock calibration output enabled  */
} hal_gfxtim_clkgen_line_clk_calib_status_t;

/**
  * @brief GFXTIM Clock generator frame clock calibration output enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_CLKGEN_FRAME_CALIB_DISABLED = 0U, /*!< Clock generator frame clock calibration output disabled */
  HAL_GFXTIM_CLKGEN_FRAME_CALIB_ENABLED  = 1U  /*!< Clock generator frame clock calibration output enabled  */
} hal_gfxtim_clkgen_frame_clk_calib_status_t;

/**
  * @brief GFXTIM Tearing-Effect source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_TEARING_EFFECT_GPIO  = LL_GFXTIM_TEARING_EFFECT_GPIO,  /*!< Input pad rising  */
  HAL_GFXTIM_TEARING_EFFECT_HSYNC = LL_GFXTIM_TEARING_EFFECT_HSYNC, /*!< HSYNC rising      */
  HAL_GFXTIM_TEARING_EFFECT_VSYNC = LL_GFXTIM_TEARING_EFFECT_VSYNC  /*!< VSYNC rising      */
} hal_gfxtim_tearing_effect_src_t;

/**
  * @brief GFXTIM Tearing-Effect polarity enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_TEARING_EFFECT_RISING_EDGE  = LL_GFXTIM_TEARING_EFFECT_RISING_EDGE, /*!< Tearing Effect active on rising edge  */
  HAL_GFXTIM_TEARING_EFFECT_FALLING_EDGE = LL_GFXTIM_TEARING_EFFECT_FALLING_EDGE /*!< Tearing Effect active on falling edge */
} hal_gfxtim_tearing_effect_polarity_t;

/**
  * @brief GFXTIM Tearing Effect interrupts state enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_TEARING_EFFECT_IT_DISABLED = 0U, /*!< Tearing Effect interrupt is disabled */
  HAL_GFXTIM_TEARING_EFFECT_IT_ENABLED  = 1U  /*!< Tearing Effect interrupt is enabled  */
} hal_gfxtim_tearing_effect_it_status_t;

/**
  * @brief GFXTIM Absolute timer counter enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_ABSTIM_LINE_COUNTER       = LL_GFXTIM_ABSTIM_LINE_COUNTER,      /*!< Absolute line counter            */
  HAL_GFXTIM_ABSTIM_FRAME_COUNTER      = LL_GFXTIM_ABSTIM_FRAME_COUNTER,     /*!< Absolute frame counter           */
  HAL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER = LL_GFXTIM_ABSTIM_LINE_FRAME_COUNTER /*!< Absolute line and frame counters */
} hal_gfxtim_abstim_counter_t;

/**
  * @brief GFXTIM Absolute line comparator enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_ABSTIM_LINE_COMP_1 = LL_GFXTIM_ABSTIM_LINE_COMP_1, /*!< Absolute line comparator 1 */
  HAL_GFXTIM_ABSTIM_LINE_COMP_2 = LL_GFXTIM_ABSTIM_LINE_COMP_2  /*!< Absolute line comparator 2 */
} hal_gfxtim_abstim_line_comp_t;

/**
  * @brief GFXTIM Relative timer selection enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_RELTIM_COUNTER_1 = LL_GFXTIM_RELTIM_COUNTER_1, /*!< Relative frame counter 1 */
  HAL_GFXTIM_RELTIM_COUNTER_2 = LL_GFXTIM_RELTIM_COUNTER_2  /*!< Relative frame counter 2 */
} hal_gfxtim_reltim_counter_t;

/**
  * @brief GFXTIM Event generators enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_EVENTGEN_EVENT_1 = LL_GFXTIM_EVENTGEN_EVENT_1, /*!< Event Generator 1 */
  HAL_GFXTIM_EVENTGEN_EVENT_2 = LL_GFXTIM_EVENTGEN_EVENT_2, /*!< Event Generator 2 */
  HAL_GFXTIM_EVENTGEN_EVENT_3 = LL_GFXTIM_EVENTGEN_EVENT_3, /*!< Event Generator 3 */
  HAL_GFXTIM_EVENTGEN_EVENT_4 = LL_GFXTIM_EVENTGEN_EVENT_4  /*!< Event Generator 4 */
} hal_gfxtim_eventgen_event_t;

/**
  * @brief GFXTIM Line event generators source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_EVENTGEN_LINE_NONE         = LL_GFXTIM_EVENTGEN_LINE_NONE,         /*!< No line event                   */
  HAL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW = LL_GFXTIM_EVENTGEN_ABS_LCNT_OVERFLOW, /*!< Absolute line counter overflow  */
  HAL_GFXTIM_EVENTGEN_TEARING_EFFECT    = LL_GFXTIM_EVENTGEN_TEARING_EFFECT,    /*!< Tearing effect                  */
  HAL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP   = LL_GFXTIM_EVENTGEN_ABS_LCNT_1_COMP,   /*!< Absolute line counter 1 compare */
  HAL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP   = LL_GFXTIM_EVENTGEN_ABS_LCNT_2_COMP    /*!< Absolute line counter 2 compare */
} hal_gfxtim_eventgen_line_src_t;

/**
  * @brief GFXTIM Frame event generators source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_EVENTGEN_FRAME_NONE        = LL_GFXTIM_EVENTGEN_FRAME_NONE,        /*!< No frame event                  */
  HAL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW = LL_GFXTIM_EVENTGEN_ABS_FCNT_OVERFLOW, /*!< Absolute frame counter overflow */
  HAL_GFXTIM_EVENTGEN_ABS_FCNT_COMP     = LL_GFXTIM_EVENTGEN_ABS_FCNT_COMP,     /*!< Absolute frame counter compare  */
  HAL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD = LL_GFXTIM_EVENTGEN_REL_FCNT_1_RELOAD, /*!< Relative frame counter 1 reload */
  HAL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD = LL_GFXTIM_EVENTGEN_REL_FCNT_2_RELOAD  /*!< Relative frame counter 2 reload */
} hal_gfxtim_eventgen_frame_src_t;

/**
  * @brief GFXTIM Watchdog timer clock source enumeration definition
  *
  */
typedef enum
{
  HAL_GFXTIM_WDG_CLK_LINE_CLK      = LL_GFXTIM_WDG_CLK_LINE_CLK,      /*!< Line Clock                  */
  HAL_GFXTIM_WDG_CLK_FRAME_CLK     = LL_GFXTIM_WDG_CLK_FRAME_CLK,     /*!< Frame Clock                 */
  HAL_GFXTIM_WDG_CLK_HSYNC_RISING  = LL_GFXTIM_WDG_CLK_HSYNC_RISING,  /*!< HSYNC rising edge           */
  HAL_GFXTIM_WDG_CLK_HSYNC_FALLING = LL_GFXTIM_WDG_CLK_HSYNC_FALLING, /*!< HSYNC falling edge          */
  HAL_GFXTIM_WDG_CLK_VSYNC_RISING  = LL_GFXTIM_WDG_CLK_VSYNC_RISING,  /*!< VSYNC rising edge           */
  HAL_GFXTIM_WDG_CLK_VSYNC_FALLING = LL_GFXTIM_WDG_CLK_VSYNC_FALLING, /*!< VSYNC falling edge          */
  HAL_GFXTIM_WDG_CLK_TE_RISING     = LL_GFXTIM_WDG_CLK_TE_RISING,     /*!< Tearing Effect rising edge  */
  HAL_GFXTIM_WDG_CLK_TE_FALLING    = LL_GFXTIM_WDG_CLK_TE_FALLING,    /*!< Tearing Effect falling edge */
  HAL_GFXTIM_WDG_CLK_EVENT_1       = LL_GFXTIM_WDG_CLK_EVENT_1,       /*!< Event Generator 1 output    */
  HAL_GFXTIM_WDG_CLK_EVENT_2       = LL_GFXTIM_WDG_CLK_EVENT_2,       /*!< Event Generator 2 output    */
  HAL_GFXTIM_WDG_CLK_EVENT_3       = LL_GFXTIM_WDG_CLK_EVENT_3,       /*!< Event Generator 3 output    */
  HAL_GFXTIM_WDG_CLK_EVENT_4       = LL_GFXTIM_WDG_CLK_EVENT_4        /*!< Event Generator 4 output    */
} hal_gfxtim_wdg_clk_src_t;

/**
  * @brief GFXTIM Clock generator structure definition
  *
  */
typedef struct
{
  hal_gfxtim_clkgen_line_count_reload_src_t reload_src;   /*!< Line Clock Counter hardware reload source  */
  uint32_t                                  reload_val;   /*!< Line Clock Counter reload value            */
  hal_gfxtim_clkgen_line_count_src_t        counter_src;  /*!< Line Clock Counter Clock Source            */
  hal_gfxtim_clkgen_line_clk_src_t          clock_src;    /*!< Line Clock Source                          */
} hal_gfxtim_clkgen_line_config_t;

/**
  * @brief GFXTIM Frame clock generator structure definition
  *
  */
typedef struct
{
  hal_gfxtim_clkgen_frame_count_reload_src_t reload_src;  /*!< Frame clock Counter hardware reload source */
  uint32_t                                   reload_val;  /*!< Frame clock Counter reload value           */
  hal_gfxtim_clkgen_frame_count_src_t        counter_src; /*!< Frame clock Counter Clock Source           */
  hal_gfxtim_clkgen_frame_clk_src_t          clock_src;   /*!< Frame clock Source                         */
} hal_gfxtim_clkgen_frame_config_t;

/**
  * @brief GFXTIM Tearing-effect configuration structure definition
  *
  */
typedef struct
{
  hal_gfxtim_tearing_effect_src_t      src;      /*!< Tearing effect source   */
  hal_gfxtim_tearing_effect_polarity_t polarity; /*!< Tearing effect polarity */
} hal_gfxtim_tearing_effect_config_t;

/**
  * @brief GFXTIM Event generator configuration structure definition
  *
  */
typedef struct
{
  hal_gfxtim_eventgen_line_src_t  line_event;  /*!< Line event selection  */
  hal_gfxtim_eventgen_frame_src_t frame_event; /*!< Frame event selection */
} hal_gfxtim_eventgen_config_t;

/**
  * @brief GFXTIM Watchdog configuration structure definition
  *
  */
typedef struct
{
  hal_gfxtim_wdg_clk_src_t src; /*!< Watchdog clock source */
} hal_gfxtim_wdg_config_t;

typedef struct hal_gfxtim_handle_s hal_gfxtim_handle_t; /*!< HAL GFXTIM handle structure type */

#if defined(USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
typedef void (*hal_gfxtim_cb_t)(hal_gfxtim_handle_t *hgfxtim); /*!< Pointer to GFXTIM callback function */
typedef void (*hal_gfxtim_line_cb_t)(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_line_comp_t line_comp);
/*!< Pointer to GFXTIM absolute line compares callback function */

typedef void (*hal_gfxtim_frame_cb_t)(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter);
/*!< Pointer to GFXTIM relative frame counters callback function */

typedef void (*hal_gfxtim_eventgen_cb_t)(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen);
/*!< Pointer to GFXTIM Event generator callbacks function */
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */

/**
  * @brief GFXTIM handle structure definition
  */
struct hal_gfxtim_handle_s
{
  hal_gfxtim_t                                  instance;                /*!< GFXTIM instance               */
  volatile hal_gfxtim_state_t                   global_state;            /*!< GFXTIM global state           */
  volatile hal_gfxtim_clkgen_state_t            clkgen_state;            /*!< GFXTIM clock generator state  */
  volatile hal_gfxtim_abstim_line_state_t       abstim_line_state;       /*!< GFXTIM absolute line state    */
  volatile hal_gfxtim_abstim_frame_state_t      abstim_frame_state;      /*!< GFXTIM absolute frame state   */
  volatile hal_gfxtim_reltim_state_t            reltim_1_state;          /*!< GFXTIM relative timer 1 state */
  volatile hal_gfxtim_reltim_state_t            reltim_2_state;          /*!< GFXTIM relative timer 2 state */
  volatile hal_gfxtim_wdg_state_t               wdg_state;               /*!< GFXTIM watchdog timer state   */

#if defined(USE_HAL_GFXTIM_USER_DATA) && (USE_HAL_GFXTIM_USER_DATA == 1U)
  const void                                *p_user_data;                /*!< User Data Pointer             */
#endif /* USE_HAL_GFXTIM_USER_DATA */

#if defined(USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
  hal_gfxtim_cb_t            p_tearing_effect_cb;               /*!< GFXTIM Tearing effect callback                   */
  hal_gfxtim_cb_t            p_abs_frame_comp_cb;               /*!< GFXTIM Absolute frame counter compare callback   */
  hal_gfxtim_cb_t            p_abs_frame_ovf_cb;                /*!< GFXTIM Absolute frame counter overflow callback  */
  hal_gfxtim_line_cb_t       p_abs_line_comp_cb;                /*!< GFXTIM Absolute line counter compares callback   */
  hal_gfxtim_cb_t            p_abs_line_ovf_cb;                 /*!< GFXTIM Absolute line counter overflow callback   */
  hal_gfxtim_frame_cb_t      p_rel_counter_cb;                  /*!< GFXTIM Relative frame counters reload callback   */
  hal_gfxtim_eventgen_cb_t   p_eventgen_cb;                     /*!< GFXTIM Event events callback                     */
  hal_gfxtim_cb_t            p_wdg_alarm_cb;                    /*!< GFXTIM Watchdog alarm callback                   */
  hal_gfxtim_cb_t            p_wdg_prealarm_cb;                 /*!< GFXTIM Watchdog pre-alarm callback               */
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GFXTIM_Exported_Functions GFXTIM Exported Functions
  * @{
  */

/** @defgroup GFXTIM_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_GFXTIM_Init(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_t instance);
void         HAL_GFXTIM_DeInit(hal_gfxtim_handle_t *hgfxtim);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group2 Clock Generator functions
  * @{
  */
hal_status_t HAL_GFXTIM_CLKGEN_SetConfigLineFrameClock(hal_gfxtim_handle_t *hgfxtim,
                                                       const hal_gfxtim_clkgen_frame_config_t *p_frame_clk_config,
                                                       const hal_gfxtim_clkgen_line_config_t *p_line_clk_config);

void HAL_GFXTIM_CLKGEN_GetConfigLineClock(const hal_gfxtim_handle_t *hgfxtim,
                                          hal_gfxtim_clkgen_line_config_t *p_config);

hal_status_t HAL_GFXTIM_CLKGEN_SetConfigFrameClock(hal_gfxtim_handle_t *hgfxtim,
                                                   const hal_gfxtim_clkgen_frame_config_t *p_clk_config);
void HAL_GFXTIM_CLKGEN_GetConfigFrameClock(const hal_gfxtim_handle_t *hgfxtim,
                                           hal_gfxtim_clkgen_frame_config_t *p_config);

hal_status_t HAL_GFXTIM_CLKGEN_ForceReloadCounter(hal_gfxtim_handle_t *hgfxtim,
                                                  hal_gfxtim_clkgen_counter_t counter);

hal_status_t HAL_GFXTIM_CLKGEN_EnableLineClkCalibOutput(hal_gfxtim_handle_t *hgfxtim);
hal_status_t HAL_GFXTIM_CLKGEN_DisableLineClkCalibOutput(hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_clkgen_line_clk_calib_status_t HAL_GFXTIM_CLKGEN_IsEnabledLineClkCalibOutput(hal_gfxtim_handle_t *hgfxtim);

hal_status_t HAL_GFXTIM_CLKGEN_EnableFrameClkCalibOutput(hal_gfxtim_handle_t *hgfxtim);
hal_status_t HAL_GFXTIM_CLKGEN_DisableFrameClkCalibOutput(hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_clkgen_frame_clk_calib_status_t HAL_GFXTIM_CLKGEN_IsEnabledFrameClkCalibOutput(hal_gfxtim_handle_t *hgfxtim);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group3 Tearing-effect configuration functions
  * @{
  */
hal_status_t HAL_GFXTIM_SetConfigTearingEffect(hal_gfxtim_handle_t *hgfxtim,
                                               const hal_gfxtim_tearing_effect_config_t *p_config);
void HAL_GFXTIM_GetConfigTearingEffect(const hal_gfxtim_handle_t *hgfxtim,
                                       hal_gfxtim_tearing_effect_config_t *p_config);

hal_status_t HAL_GFXTIM_EnableTearingEffectIT(hal_gfxtim_handle_t *hgfxtim);
hal_status_t HAL_GFXTIM_DisableTearingEffectIT(hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_tearing_effect_it_status_t HAL_GFXTIM_IsEnabledTearingEffectIT(hal_gfxtim_handle_t *hgfxtim);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group4 Absolute Timer functions
  * @{
  */
/* Absolute line functions  *******************************************************************************************/
hal_status_t HAL_GFXTIM_ABSTIM_SetLineCompareValue(hal_gfxtim_handle_t *hgfxtim,
                                                   hal_gfxtim_abstim_line_comp_t line_comp, uint32_t val);
uint32_t HAL_GFXTIM_ABSTIM_GetLineCompareValue(hal_gfxtim_handle_t *hgfxtim,
                                               hal_gfxtim_abstim_line_comp_t line_comp);

hal_status_t HAL_GFXTIM_ABSTIM_SetLineCounter(const hal_gfxtim_handle_t *hgfxtim, uint32_t val);
uint32_t HAL_GFXTIM_ABSTIM_GetLineCounter(hal_gfxtim_handle_t *hgfxtim);

/* Absolute frame functions  ******************************************************************************************/
hal_status_t HAL_GFXTIM_ABSTIM_SetFrameCompareValue(hal_gfxtim_handle_t *hgfxtim, uint32_t val);
uint32_t HAL_GFXTIM_ABSTIM_GetFrameCompareValue(hal_gfxtim_handle_t *hgfxtim);

hal_status_t HAL_GFXTIM_ABSTIM_SetFrameCounter(const hal_gfxtim_handle_t *hgfxtim, uint32_t val);
uint32_t HAL_GFXTIM_ABSTIM_GetFrameCounter(hal_gfxtim_handle_t *hgfxtim);

/* Absolute timer functions  ******************************************************************************************/
hal_status_t HAL_GFXTIM_ABSTIM_Start(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter,
                                     uint32_t interrupts);

hal_status_t HAL_GFXTIM_ABSTIM_Stop(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter);
hal_status_t HAL_GFXTIM_ABSTIM_Pause(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter);
hal_status_t HAL_GFXTIM_ABSTIM_Resume(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter);
hal_status_t HAL_GFXTIM_ABSTIM_Reset(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_counter_t counter);
void HAL_GFXTIM_ABSTIM_GetCounter(hal_gfxtim_handle_t *hgfxtim, uint32_t *p_frame, uint32_t *p_line);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group5 Relative Timer functions
  * @{
  */
hal_status_t HAL_GFXTIM_RELTIM_StartContinuous(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                               uint32_t autoreload_val, uint32_t interrupt);

hal_status_t HAL_GFXTIM_RELTIM_StopContinuous(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter);
hal_status_t HAL_GFXTIM_RELTIM_SetReloadValue(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                              uint32_t autoreload_val);
hal_status_t HAL_GFXTIM_RELTIM_ForceReload(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter);
uint32_t HAL_GFXTIM_RELTIM_GetCounter(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter);

hal_status_t HAL_GFXTIM_RELTIM_StartOneShot(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                            uint32_t autoreload_val, uint32_t interrupt);
hal_status_t HAL_GFXTIM_RELTIM_PollForOneShot(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter,
                                              uint32_t timeout_ms);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group6 Event Generator functions
  * @{
  */
hal_status_t HAL_GFXTIM_EVENTGEN_SetConfig(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen,
                                           const hal_gfxtim_eventgen_config_t *p_config);

void HAL_GFXTIM_EVENTGEN_GetConfig(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen,
                                   hal_gfxtim_eventgen_config_t *p_config);

hal_status_t HAL_GFXTIM_EVENTGEN_Start(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen,
                                       uint32_t interrupt);
hal_status_t HAL_GFXTIM_EVENTGEN_Stop(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group7 Watchdog counter functions
  * @{
  */
hal_status_t HAL_GFXTIM_WDG_SetConfig(hal_gfxtim_handle_t *hgfxtim, const hal_gfxtim_wdg_config_t *p_config);
void HAL_GFXTIM_WDG_GetConfig(const hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_wdg_config_t *p_config);

hal_status_t HAL_GFXTIM_WDG_Start(hal_gfxtim_handle_t *hgfxtim, uint32_t reload_val, uint32_t prealarm_val,
                                  uint32_t interrupts);

hal_status_t HAL_GFXTIM_WDG_Stop(hal_gfxtim_handle_t *hgfxtim);
hal_status_t HAL_GFXTIM_WDG_Refresh(hal_gfxtim_handle_t *hgfxtim);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group8 Peripheral State functions
  * @{
  */
hal_gfxtim_state_t HAL_GFXTIM_GetState(const hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_clkgen_state_t HAL_GFXTIM_CLKGEN_GetState(const hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_abstim_line_state_t HAL_GFXTIM_ABSTIM_GetLineState(const hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_abstim_frame_state_t HAL_GFXTIM_ABSTIM_GetFrameState(const hal_gfxtim_handle_t *hgfxtim);
hal_gfxtim_reltim_state_t HAL_GFXTIM_RELTIM_GetState(const hal_gfxtim_handle_t *hgfxtim,
                                                     hal_gfxtim_reltim_counter_t counter);
hal_gfxtim_wdg_state_t HAL_GFXTIM_WDG_GetState(const hal_gfxtim_handle_t *hgfxtim);
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group9 IRQHandler and Callbacks functions
  * @{
  */
void HAL_GFXTIM_IRQHandler(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_TearingEffectIRQHandler(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_ABSTIM_FrameIRQHandler(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_ABSTIM_LineIRQHandler(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_RELTIM_IRQHandler(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_EVENTGEN_IRQHandler(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_WDG_IRQHandler(hal_gfxtim_handle_t *hgfxtim);

void HAL_GFXTIM_TearingEffectCallback(hal_gfxtim_handle_t *hgfxtim);

void HAL_GFXTIM_ABSTIM_FCmpCallback(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_ABSTIM_FCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim);

void HAL_GFXTIM_ABSTIM_LCmpCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_abstim_line_comp_t line_comp);
void HAL_GFXTIM_ABSTIM_LCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim);

void HAL_GFXTIM_RELTIM_FCntReloadCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_reltim_counter_t counter);

void HAL_GFXTIM_EVENTGEN_EventCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_eventgen_event_t event_gen);

void HAL_GFXTIM_WDG_AlarmCallback(hal_gfxtim_handle_t *hgfxtim);
void HAL_GFXTIM_WDG_PreAlarmCallback(hal_gfxtim_handle_t *hgfxtim);

#if defined (USE_HAL_GFXTIM_REGISTER_CALLBACKS) && (USE_HAL_GFXTIM_REGISTER_CALLBACKS == 1U)
hal_status_t HAL_GFXTIM_RegisterTearingEffectCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback);
hal_status_t HAL_GFXTIM_ABSTIM_RegisterFCmpCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback);
hal_status_t HAL_GFXTIM_ABSTIM_RegisterFCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback);

hal_status_t HAL_GFXTIM_ABSTIM_RegisterLCmpCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_line_cb_t p_callback);
hal_status_t HAL_GFXTIM_ABSTIM_RegisterLCntOverFlowCallback(hal_gfxtim_handle_t *hgfxtim,
                                                            hal_gfxtim_cb_t p_callback);

hal_status_t HAL_GFXTIM_RELTIM_RegisterFCntReloadCallback(hal_gfxtim_handle_t *hgfxtim,
                                                          hal_gfxtim_frame_cb_t p_callback);

hal_status_t HAL_GFXTIM_EVENTGEN_RegisterEventCallback(hal_gfxtim_handle_t *hgfxtim,
                                                       hal_gfxtim_eventgen_cb_t p_callback);

hal_status_t HAL_GFXTIM_WDG_RegisterAlarmCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback);
hal_status_t HAL_GFXTIM_WDG_RegisterPreAlarmCallback(hal_gfxtim_handle_t *hgfxtim, hal_gfxtim_cb_t p_callback);
#endif /* USE_HAL_GFXTIM_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup GFXTIM_Exported_Functions_Group10 Set/Get user data functions
  * @{
  */
#if defined(USE_HAL_GFXTIM_USER_DATA) && (USE_HAL_GFXTIM_USER_DATA == 1U)
void HAL_GFXTIM_SetUserData(hal_gfxtim_handle_t *hgfxtim, const void *p_user_data);
const void *HAL_GFXTIM_GetUserData(const hal_gfxtim_handle_t *hgfxtim);
#endif /* USE_HAL_GFXTIM_USER_DATA */
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

#endif /* GFXTIM */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_GFXTIM_H */
