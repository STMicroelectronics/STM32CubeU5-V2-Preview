/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_iwdg.c
  * @brief   IWDG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Independent Watchdog (IWDG) peripheral:
  *           + Initialization and Configuration functions
  *           + IO operation functions
  *
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

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{

  The independent watchdog (IWDG) peripheral offers a high safety level, thanks to its capability to detect
  malfunctions due to software or hardware failures.
  The IWDG is clocked by an independent clock, and stays active even if the main clock fails. In addition, the watchdog
  function is performed on the VDD voltage domain, allowing the IWDG to remain functional even in low-power modes.
  The IWDG is best suited for applications that require the watchdog to run as a totally independent process outside
  the main application, making it very reliable to detect any unexpected behavior.

  ## Main features
  - The IWDG can be started by either software or hardware (configurable through option byte).\n
    Note: If the user has chosen to start the IWDG in hardware mode, USE_HAL_IWDG_HARDWARE_START directive must be set
    to take into account the APIs associated with hardware mode.
  - The IWDG is clocked by the Low-Speed Internal clock (LSI) and thus stays active even if the main clock fails.
  - Once the IWDG is started, the LSI is forced ON and both cannot be disabled except by a system reset.
  - Once enabled the IWDG generates a system reset on expiry of a programmed time period, unless the program refreshes
    the downcounter before reaching 0x000 value (i.e. a reset is generated when the counter value rolls
    down from 0x001 to 0x000).
  - A MCU reset is also generated if the counter value is refreshed before the counter has reached the refresh window
    value. This implies that the counter must be refreshed in a limited window.
  - If required by application, an Early Wakeup Interrupt time can be configured in order to be warned before IWDG
    expiration. The Early Wakeup Interrupt (EWI) can be used if specific safety operations or data logging must be
    performed before the actual reset is generated.
    This mechanism requires IWDG interrupt line to be enabled in NVIC. Once enabled, EWI interrupt cannot be disabled
    except by a system reset.
  - The IWDG is implemented in the VDD voltage domain that is still functional in STOP and STANDBY modes (IWDG reset can
    wake up the CPU from STANDBY).
  - The IWDG counter input clock is derived from LSI clock divided by a programmable prescaler.
  - IWDG clock (Hz) = LSI_clock / (4 * Prescaler)
  - IWDG timeout (ms) = 1000 * (RL[11:0]) / IWDG clock (Hz) where RL[11:0] is the counter reload value.
  - IWDG Counter refresh is allowed between the following limits:
    - min time (ms) = 1000 * (Counter - Window) / IWDG clock  (The min time represents the minimum time before refresh
      is allowed)
    - max time (ms) = 1000 * (Counter) / IWDG clock (The max time represents the maximum time before reset)
  - Typical values @32kHz (LSI)
    - Step range: [125us ; 8ms] (The IWDG step represents the IWDG counter period)
    - Timeout range (with RL[11:0] in [2 ; 4096]): [250us ; ~131s]
  - Typical values @250Hz (LSI / 128)
    - Step range: [16ms ; 4,096s]
    - Timeout range: [~66s ; ~16777s]
  - LSI management
    - The IWDG timeout might vary due to LSI clock frequency dispersion.
      STM32U5xx devices provide the capability to measure the LSI clock frequency (LSI clock is internally
      connected to TIM16 CH1 input capture).
      The measured value can be used to have an IWDG timeout with an acceptable accuracy.
    - Default: Constant LSI_VALUE is defined based on the nominal LSI clock frequency. This frequency being subject to
    variations as mentioned above, default timeout has been specifically adjusted to accommodate the LSI startup time.
    - The IWDG HAL driver gives the user the possibility to calculate his own LSI frequency and use it afterwards
    - Debug mode: When the microcontroller enters debug mode (core halted), the IWDG counter either continues to work
    normally or stops, depending on DBG_IWDG_STOP configuration bit in DBG module, Refer to DBGMCU module services to
    freeze or unfreeze IWDG during system low power modes.

  ## How to use
  The IWDG HAL driver can be used as follows:
  - Select the LSI frequency using the USE_HAL_IWDG_LSI_FREQ, the choice is either static or dynamic depending on this
    define.
  - Configure the allowed refresh period (minimum and maximum time values) and early interrupt time using
   HAL_IWDG_Start() function. The IWDG is automatically enabled and its downcounter is started.
  - HAL_IWDG_Start() computes and initializes prescaler, reload, window and early wake-up registers to values
    corresponding to the nearest achievable minimum, maximum and early interrupt times inputs.
  - HAL_IWDG_GetMaxTime(), HAL_IWDG_GetMinTime() and HAL_IWDG_GetEarlyWakeupInterruptTime() functions permits to
    retrieve the times actually set.
  - HAL_IWDG_GetStep() and HAL_IWDG_SetMinTime() permit to tune the refresh time.
  - HAL_IWDG_SetEarlyWakeupInterruptTime() permits to tune the the early interrupt time.
  - Care must be taken to provide a maximum time value greater than 0 to prevent generation of immediate reset.
  - If the Early Wakeup Interrupt (EWI) feature is enabled (early interrupt time not equal to 0), an interrupt is
    generated when the early wakeup
    time is reached. When HAL_IWDG_IRQHandler() is triggered by the interrupt service routine, Early Wakeup flag
    is automatically cleared
    and HAL_IWDG_EarlyWakeupCallback() callback is executed. User can add his own code by customization of callback
    HAL_IWDG_EarlyWakeupCallback().
  - After IWDG first initialization,
    HAL_IWDG_SetLSIFrequency() can be called to set a more accurate LSI value. The  HAL_IWDG_Start() must be called
    again to re-configure the IWDG. HAL_IWDG_GetLSIFrequency() permits to retrieve the LSI value used by IWDG driver.

  - Then the application program must refresh the IWDG counter at regular intervals during normal operation to prevent
    an MCU reset, using HAL_IWDG_Refresh() function.

  ### Callback registration:
  - The compilation flag USE_HAL_IWDG_REGISTER_CALLBACKS allows the user to configure dynamically the driver callbacks.
  - Use HAL_IWDG_RegisterEarlyWakeupCallback() function to register IWDG Early Wakeup callback.\n
  - This function takes as parameters the HAL peripheral handle and a pointer to the user callback function.

  ## Configuration inside the IWDG driver:
 |Config defines                 |Where            |Default value          |Note                                       |
 |-------------------------------|-----------------|-----------------------|-------------------------------------------|
 |USE_HAL_IWDG_MODULE            |hal_conf.h       |           1           |Enable the HAL IWDG module.                |
 |USE_HAL_IWDG_REGISTER_CALLBACKS|hal_conf.h       |           0           |Enable the register callbacks assert       |
 |USE_HAL_CHECK_PARAM            |hal_conf.h       |           0           |Enable checking of vital parameters at     |
 |                               |                 |                       |runtime                                    |
 |USE_HAL_IWDG_HARDWARE_START    |hal_conf.h       |           0           |IWDG driver starts in HW mode              |
 |USE_HAL_IWDG_USER_DATA         |hal_conf.h       |           0           |Add an user data inside HAL IWDG handle    |
 |USE_HAL_IWDG_TIME_UNIT (*)     |hal_conf.h       | HAL_IWDG_TIME_UNIT_MS |Time unit to be used for IWDG driver       |
 |USE_HAL_IWDG_LSI_FREQ (**)     |hal_conf.h       |        LSI_VALUE      |LSI value to be applied to the IWDG driver |
 |USE_ASSERT_DBG_PARAM           |PreProcessor env |          NA           |Enable the params assert                   |
 |USE_ASSERT_DBG_STATE           |PreProcessor env |          NA           |Enable the state assert                    |

(*) User can choose the value of the time Unit with the USE_HAL_IWDG_TIME_UNIT define:

- HAL_IWDG_TIME_UNIT_US: IWDG driver time unit in microseconds.
- HAL_IWDG_TIME_UNIT_MS: IWDG driver time unit in milliseconds.
- HAL_IWDG_TIME_UNIT_S: IWDG driver time unit in seconds.<br>

The default time unit is milliseconds if not set by the user.\n\n

(**) User can choose the value of the LSI frequency with the USE_HAL_IWDG_LSI_FREQ define:
- LSI_VALUE_DYNAMIC: Dynamic LSI to be computed and set by the user.
- LSI_VALUE: LSI value of 32kHz.
- (LSI_VALUE / 128U): LSI value of 250Hz.<br>
The default LSI value is LSI_VALUE if not set by the user.\n

  ## Allowed Maximum time ranges:
  The selection of prescaler is done as follows: As long as the requested reset time value is lower than the max_time
  of a time range n, algorithm keeps the same prescaler n, once it exceeds the max_time of the range n, algorithm switch
  to the prescaler of the range n+1.
  The next table describes the possible Max time ranges for each prescaler and with both standard values of the LSI
  frequency:\n
  Note:\n
  - For "Not supported" value in s, the user must switch to the ms or us unit.
  Same, for "Not supported" values in us, the user must switch to the ms or s unit.\n
  - In order to cover all the ranges, time unit static configuration has been introduced and can be expressed in us, ms
  or second.

  LSI(Hz) | Prescaler | Step(us) | Max(us)       | Max(ms) | Max(s)
  --------|-----------|----------|---------------|---------|-----------
  32000   | 4         | 125      | 512000        | 512     | Not supported
  32000   | 8         | 250      | 1024000       | 1024    | 1.024
  32000   | 16        | 500      | 2048000       | 2048    | 2.048
  32000   | 32        | 1000     | 4096000       | 4096    | 4.096
  32000   | 64        | 2000     | 8192000       | 8192    | 8.192
  32000   | 128       | 4000     | 16384000      | 16384   | 16.384
  32000   | 256       | 8000     | 32768000      | 32768   | 32.768
  32000   | 512       | 16000    | 65536000      | 65536   | 65.536
  32000   | 1024      | 32000    | 131072000     | 131072  | 131.072
  250     | 4         | 16000    | 65536000      | 65536   | 65.536
  250     | 8         | 32000    | 131072000     | 131072  | 131.072
  250     | 16        | 64000    | 262144000     | 262144  | 262.144
  250     | 32        | 128000   | 524288000     | 524288  | 524.288
  250     | 64        | 256000   | 1048576000    | 1048576 | 1048.576
  250     | 128       | 512000   | 2097152000    | 2097152 | 2097.152
  250     | 256       | 1024000  | 4194304000    | 4194304 | 4194.304
  250     | 512       | 2048000  | Not supported | 8388608 | 8388.608
  250     | 1024      | 4096000  | Not supported | 16777216| 16777.216
  */

#if defined(USE_HAL_IWDG_MODULE) && (USE_HAL_IWDG_MODULE == 1UL)

#if (USE_HAL_IWDG_LSI_FREQ != LSI_VALUE) && (USE_HAL_IWDG_LSI_FREQ != (LSI_VALUE / 128UL)) \
     && (USE_HAL_IWDG_LSI_FREQ != LSI_VALUE_DYNAMIC)
#error "USE_HAL_IWDG_LSI_FREQ not correctly set"
#endif /* USE_HAL_IWDG_LSI_FREQ VERIFICATION */

#if (USE_HAL_IWDG_TIME_UNIT != HAL_IWDG_TIME_UNIT_US) && (USE_HAL_IWDG_TIME_UNIT != HAL_IWDG_TIME_UNIT_MS) \
     && (USE_HAL_IWDG_TIME_UNIT != HAL_IWDG_TIME_UNIT_S)
#error "USE_HAL_IWDG_TIME_UNIT not correctly set"
#endif /* USE_HAL_IWDG_TIME_UNIT VERIFICATION */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup IWDG_Private_Constants IWDG Private Constants
  * @{
  */
/**
  * Status register needs up to 5 LSI clock periods to be updated. However a synchronisation is added on prescaled LSI
  * clock rising edge, so we only consider a higher prescaler cycle.
  * The timeout value is calculated using the highest prescaler (1024) and the (LSI_VALUE / 128). The value of this
  * constant can be changed by the user to take into account possible LSI clock period variations.
  * The timeout value is multiplied by 1000 to be converted in milliseconds.
  * LSI startup time is also considered here by adding LSI_STARTUP_TIME converted in milliseconds.
  */
#define IWDG_DEFAULT_TIMEOUT  (((1UL * 1024UL * 1000UL) / (LSI_VALUE / 128UL)) + \
                               ((LSI_STARTUP_TIME / 1000UL) + 1UL))  /*!< Default value of IWDG timeout */

#define IWDG_KERNEL_UPDATE_FLAGS  (IWDG_SR_EWU | IWDG_SR_WVU | \
                                   IWDG_SR_RVU | IWDG_SR_PVU)  /*!< Flags to be updated in the IWDG status register */
#define IWDG_EWI_DISABLE         IWDG_EWCR_EWIE        /*!< IWDG Early Wakeup option disabled          */

#define IWDG_MAX_STEP_NR         4096UL          /*!< IWDG Max step number                              */
#define IWDG_MAX_RELOAD          4095UL          /*!< IWDG Max reload                                   */
#define IWDG_TIME_CONVERSION     1000UL          /*!< Microseconds per millisecond                      */
#define IWDG_TIME_CONVERSION_US  1000000UL       /*!< Microseconds per second                           */
#define IWDG_MAX_TIME_PARAM      0xFFFFUL        /*!< Max time parameter                                */
#define IWDG_MAX_PRESCALER       1024UL          /*!< IWDG Max prescaler                                */

#define IWDG_MAX_TIME_32K_SEC     ((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR) / LSI_VALUE)
/*!< Maximum  time before reset at 32 kHz in seconds */
#define IWDG_MAX_TIME_32K_MSEC    ((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR * IWDG_TIME_CONVERSION) / LSI_VALUE)
/*!< Maximum  time before reset at 32 kHz in milliseconds */
#define IWDG_MAX_TIME_32K_USEC    (IWDG_MAX_TIME_32K_MSEC * IWDG_TIME_CONVERSION)
/*!< Maximum  time before reset at 32 kHz in microseconds */

#define IWDG_MAX_TIME_250HZ_SEC   ((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR) / (LSI_VALUE / 128UL))
/*!< Maximum  time before reset at 250 Hz in seconds */
#define IWDG_MAX_TIME_250HZ_MSEC  ((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR * IWDG_TIME_CONVERSION) / \
                                   (LSI_VALUE / 128UL))
/*!< Maximum  time before reset at 250 Hz in milliseconds */
#define IWDG_MAX_TIME_250HZ_USEC  (((256UL * IWDG_MAX_STEP_NR * IWDG_TIME_CONVERSION) / \
                                    (LSI_VALUE / 128UL)) * IWDG_TIME_CONVERSION)
/*!< Maximum  time before reset at 250 Hz in microseconds */
#define IWDG_WINDOW_DISABLE  IWDG_WINR_WIN       /*!< IWDG Window option disabled */
/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup IWDG_Private_Macros IWDG Private Macros
  * @{
  */

/*!< IWDG Macro to retrieve the IWDG instance */
#define IWDG_GET_INSTANCE(handle)  ((IWDG_TypeDef *)((uint32_t)(handle)->instance))

/*!< IWDG allowed max time for LSI = LSI_VALUE           */

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE)
#define IWDG_ALLOWED_MAX_TIME()  ((USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US) ? IWDG_MAX_TIME_32K_USEC : \
                                  ((USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_MS) ? IWDG_MAX_TIME_32K_MSEC : \
                                   IWDG_MAX_TIME_32K_SEC))
/*!< IWDG allowed max time for LSI = (LSI_VALUE / 128UL) */
#elif (USE_HAL_IWDG_LSI_FREQ == (LSI_VALUE / 128UL))
#define IWDG_ALLOWED_MAX_TIME()  ((USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US) ? IWDG_MAX_TIME_250HZ_USEC : \
                                  ((USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_MS) ? IWDG_MAX_TIME_250HZ_MSEC : \
                                   IWDG_MAX_TIME_250HZ_SEC))
/*!< IWDG allowed max time for LSI set by user           */
#elif (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US)
#define IWDG_ALLOWED_MAX_TIME(lsi_freq)  (((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR * IWDG_TIME_CONVERSION) / \
                                           lsi_freq) * IWDG_TIME_CONVERSION)
#elif (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_MS)
#define IWDG_ALLOWED_MAX_TIME(lsi_freq)  ((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR * IWDG_TIME_CONVERSION) / \
                                          lsi_freq)
#elif (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_S)
#define IWDG_ALLOWED_MAX_TIME(lsi_freq)  ((IWDG_MAX_PRESCALER * IWDG_MAX_STEP_NR) / lsi_freq)
#endif /* USE_HAL_IWDG_TIME_UNIT */
#endif /* USE_HAL_IWDG_LSI_FREQ */

/**
  * @brief   Check IWDG max time value.
  * @param   max_time  IWDG max time value.
  * @param   lsi_freq  IWDG LSI frequency value (only if LSI_VALUE_DYNAMIC is defined).
  * @warning max_time  must not exceed IWDG_ALLOWED_MAX_TIME based on the LSI frequency and time unit values
  *          selected by the user.
  */
#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
#define IS_IWDG_MAX_TIME(max_time, lsi_freq)  ((max_time) <= IWDG_ALLOWED_MAX_TIME(lsi_freq))
#else
#define IS_IWDG_MAX_TIME(max_time)            ((max_time) <= IWDG_ALLOWED_MAX_TIME())
#endif /* USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC */

/**
  * @brief Check IWDG min time value.
  * @param min_time  IWDG min time value
  * @param max_time  IWDG max time value
  */
#define IS_IWDG_MIN_TIME(min_time, max_time)  (((min_time) <= (max_time)) || ((min_time) == 0UL))

/**
  * @brief Check IWDG early wakeup time value.
  * @param ewi_time  IWDG early wakeup time value
  * @param min_time  IWDG min time value
  * @param max_time  IWDG max time value
  */
#define IS_IWDG_EWI_TIME(ewi_time, min_time, max_time)  ((((min_time) < (ewi_time)) && ((ewi_time) < (max_time))) \
                                                         || ((ewi_time) == 0UL))
/**
  * @}
  */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup IWDG_Private_Functions IWDG Private Functions
  * @{
  */
static uint8_t  IWDG_CalculatePrescaler(const hal_iwdg_handle_t *hiwdg, uint32_t max_time);
static uint16_t IWDG_CalculateReload(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t max_time);
static uint16_t IWDG_CalculateParam(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t time);
static uint32_t IWDG_CalculateTime(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t param);
static void IWDG_ConfigureMinTime(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t min_time);
static void IWDG_ConfigureEarlyWakeupInterruptTime(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler,
                                                   uint32_t early_wakeup_time);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup IWDG_Exported_Functions IWDG Exported Functions
  * @{
  */

/** @addtogroup IWDG_Exported_Functions_Group1
  * @{

  This subsection provides a set of functions allowing to initialize and start the IWDG peripheral:
    - Call the function HAL_IWDG_Init() to initialize the IWDG handle and associate an instance.
    - Call the function HAL_IWDG_Start() to start the IWDG according to the parameters provided by the user.
  */

/**
  * @brief    Initialize the IWDG according to the associated handle.
  * @param    hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *           specified IWDG module.
  * @param    instance  IWDG instance.
  * @warning  LSI frequency used in the driver is reinitialized to the default value LSI_VALUE
  *           or LSI_VALUE/128 (if LSI prescaler is enabled)
  *           and then API HAL_IWDG_SetLSIFrequency() can be called to use a more accurate value.
  * @warning  In case of starting IWDG in Hardware mode, make sure that USE_HAL_IWDG_HARDWARE_START is aligned with
  *           the IWDG_SW option byte.
  * @retval   HAL_OK  Operation completed successfully.
  * @retval   HAL_INVALID_PARAM  Invalid parameter.
  */
hal_status_t HAL_IWDG_Init(hal_iwdg_handle_t *hiwdg, hal_iwdg_t instance)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_PARAM(IS_IWDG_ALL_INSTANCE((IWDG_TypeDef *)(uint32_t)instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1UL)
  if (hiwdg == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hiwdg->instance = instance;

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  hiwdg->lsi_frequency_hz = (LL_RCC_LSI_GetPrescaler() == LL_RCC_LSI_DIV_1) ? LSI_VALUE : (LSI_VALUE / 128UL);
#endif /* USE_HAL_IWDG_LSI_FREQ */

#if defined(USE_HAL_IWDG_REGISTER_CALLBACKS) && (USE_HAL_IWDG_REGISTER_CALLBACKS == 1UL)
  hiwdg->p_early_wakeup_cb = (hal_iwdg_cb_t)HAL_IWDG_EarlyWakeupCallback;
#endif /* USE_HAL_IWDG_REGISTER_CALLBACKS */

#if defined (USE_HAL_IWDG_USER_DATA) && (USE_HAL_IWDG_USER_DATA == 1UL)
  hiwdg->p_user_data = NULL;
#endif /* USE_HAL_IWDG_USER_DATA */

#if defined(USE_HAL_IWDG_HARDWARE_START) && (USE_HAL_IWDG_HARDWARE_START == 1UL)
  hiwdg->global_state = HAL_IWDG_STATE_ACTIVE;
#else /* USE_HAL_IWDG_HARDWARE_START == 0UL */
  hiwdg->global_state = HAL_IWDG_STATE_IDLE;
#endif /* USE_HAL_IWDG_HARDWARE_START */

  return HAL_OK;
}

/**
  * @brief   Start the IWDG. Before exiting the function, the watchdog is refreshed to have a correct time base.
  * @param   hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                 specified IWDG module.
  * @param   min_time Minimum time value before refreshing is allowed.
  * @param   max_time Maximum time value before a WWDG reset.
  * @param   early_wakeup_time Early Wakeup Interrupt time value.
  * @warning The min_time and max_time are used to define the window and the reload values, the unit for these
  *          parameters depend on the switch USE_HAL_IWDG_TIME_UNIT.
  * @warning When the Window is not needed, the value of min_time is set to IWDG_WINDOW_DISABLE.
  * @warning The early_wakeup_time is used to set the Early Wakeup Interrupt. When it is not needed, value is
  *          set to IWDG_EWI_DISABLE.
  * @retval  HAL_OK  Operation completed successfully.
  * @retval  HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_IWDG_Start(hal_iwdg_handle_t *hiwdg, uint32_t min_time, uint32_t max_time, uint32_t early_wakeup_time)
{
  uint32_t tickstart;
  uint8_t  prescaler;

  ASSERT_DBG_PARAM(hiwdg != NULL);

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  ASSERT_DBG_PARAM(IS_IWDG_MAX_TIME(max_time, hiwdg->lsi_frequency_hz));
#else
  ASSERT_DBG_PARAM(IS_IWDG_MAX_TIME(max_time));
#endif /* USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC */

  ASSERT_DBG_PARAM(IS_IWDG_MIN_TIME(min_time, max_time));
  ASSERT_DBG_PARAM(IS_IWDG_EWI_TIME(early_wakeup_time, min_time, max_time));

#if defined(USE_HAL_IWDG_HARDWARE_START) && (USE_HAL_IWDG_HARDWARE_START == 1UL)
  ASSERT_DBG_STATE(hiwdg->global_state, (uint32_t)HAL_IWDG_STATE_ACTIVE);
#else
  ASSERT_DBG_STATE(hiwdg->global_state, (uint32_t)HAL_IWDG_STATE_IDLE | (uint32_t)HAL_IWDG_STATE_ACTIVE);
  if (hiwdg->global_state == HAL_IWDG_STATE_IDLE)
  {
    HAL_CHECK_UPDATE_STATE(hiwdg, global_state, HAL_IWDG_STATE_IDLE, HAL_IWDG_STATE_ACTIVE);
  }
#endif /* USE_HAL_IWDG_HARDWARE_START */

  prescaler = IWDG_CalculatePrescaler(hiwdg, max_time);
  hiwdg-> reload = IWDG_CalculateReload(hiwdg, prescaler, max_time);

  LL_IWDG_Enable(IWDG_GET_INSTANCE(hiwdg));

  LL_IWDG_EnableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

  LL_IWDG_SetPrescaler(IWDG_GET_INSTANCE(hiwdg), prescaler);
  LL_IWDG_SetReloadCounter(IWDG_GET_INSTANCE(hiwdg), hiwdg-> reload);

  IWDG_ConfigureEarlyWakeupInterruptTime(hiwdg, prescaler, early_wakeup_time);

  IWDG_ConfigureMinTime(hiwdg, prescaler, min_time);

  /* Check pending flag, if previous update not done, return timeout */
  tickstart = HAL_GetTick();

  while ((LL_IWDG_READ_REG(IWDG_GET_INSTANCE(hiwdg), SR) & IWDG_KERNEL_UPDATE_FLAGS) != 0UL)
  {
    if ((HAL_GetTick() - tickstart) > IWDG_DEFAULT_TIMEOUT)
    {
      if ((LL_IWDG_READ_REG(IWDG_GET_INSTANCE(hiwdg), SR) & IWDG_KERNEL_UPDATE_FLAGS) != 0UL)
      {
        LL_IWDG_DisableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

        return HAL_ERROR;
      }
    }
  }

  LL_IWDG_DisableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group2
  * @{

  This subsection provides a set of functions to manage the IWDG driver:
    - Call the function HAL_IWDG_Refresh() to reload IWDG counter with value defined in the reload register.
  */

/**
  * @brief  Refresh the IWDG.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_IWDG_Refresh(hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  LL_IWDG_ReloadCounter(IWDG_GET_INSTANCE(hiwdg));

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group3
  * @{

  This subsection provides a set of functions to manage the IWDG driver:
    - Call the function HAL_IWDG_GetState() to retrieve the IWDG handle state.
  */

/**
  * @brief  Return the IWDG handle state.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @retval HAL_IWDG_STATE_RESET IWDG driver not initialized and not started.
  * @retval HAL_IWDG_STATE_IDLE IWDG driver initialized and not started.
  * @retval HAL_IWDG_STATE_ACTIVE IWDG driver initialized and started.
  */
hal_iwdg_state_t HAL_IWDG_GetState(const hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);

  return hiwdg->global_state;
}
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group4
  * @{

  This subsection provides a set of functions to set/retrieve configuration items separately for the IWDG driver:
    - Call the function HAL_IWDG_GetMaxTime() to retrieve the current Reset time value.
    - Call the function HAL_IWDG_SetMinTime() to set only the Window time value.
    - Call the function HAL_IWDG_GetMinTime() to retrieve the current Window time value.
    - Call the function  HAL_IWDG_SetEarlyWakeupInterruptTime() to set only the Early Wakeup time value.
    - Call the function  HAL_IWDG_GetEarlyWakeupInterruptTime() to retrieve the current Early Wakeup time value.
    @note The prescaler is calculated from max_time once in the HAL_IWDG_Start() function, to avoid a change of
    prescaler, we did not proceed by a setMaxTime() function because it can modify the prescaler and thus require to
    recalculate the Window and the Early Wakeup Interrupt.
    To modify the max_time, the user must proceed by the HAL_IWDG_Start() function.
  */

/**
  * @brief  Get the reset time value according to the handler instance registers.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @retval uint32_t  Current reset time in the selected USE_HAL_IWDG_TIME_UNIT unit.
  */
uint32_t HAL_IWDG_GetMaxTime(const hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  return IWDG_CalculateTime(hiwdg, (uint8_t)LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg)), IWDG_MAX_TIME_PARAM);
}

/**
  * @brief  Get the step of the IWDG in microseconds.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @note   HAL_IWDG_GetStep is given as informational to allow the user to calculate max_time, min_time and
  *         early_wakeup_time to avoid rounded values.
  * @retval uint32_t Current step value in us.
  */
uint32_t HAL_IWDG_GetStep(const hal_iwdg_handle_t *hiwdg)
{
  uint32_t step;
  uint32_t remainder;

  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);
#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  step = (IWDG_TIME_CONVERSION_US * (4UL * (1UL << LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg))))) /
         (hiwdg->lsi_frequency_hz);

  remainder = (IWDG_TIME_CONVERSION_US * (4UL * (1UL << LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg))))) %
              (hiwdg->lsi_frequency_hz);

  /* Round step to the closest integer value */
  if ((remainder > 0UL) && ((remainder * 2UL) >= (hiwdg->lsi_frequency_hz)))
#else
  step = (IWDG_TIME_CONVERSION_US * (4UL * (1UL << LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg))))) /
         (USE_HAL_IWDG_LSI_FREQ);

  remainder = (IWDG_TIME_CONVERSION_US * (4UL * (1UL << LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg))))) %
              (USE_HAL_IWDG_LSI_FREQ);

  if ((remainder > 0UL) && ((remainder * 2UL) >= (USE_HAL_IWDG_LSI_FREQ)))
#endif /* USE_HAL_IWDG_LSI_FREQ != LSI_VALUE_DYNAMIC */
  {
    step++;
  }

  return step;
}

/**
  * @brief  Set the Window time value.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @param  time   Window time value to be set.
  * @note   Modifying the IWDG Window register will automatically reload the watchdog counter.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR  Operation completed with error.
  */
hal_status_t HAL_IWDG_SetMinTime(hal_iwdg_handle_t *hiwdg, uint32_t time)
{
  uint32_t tickstart;
  uint8_t prescaler;

  ASSERT_DBG_PARAM(hiwdg != NULL);

  prescaler = (uint8_t)LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg));

  ASSERT_DBG_PARAM(IS_IWDG_MIN_TIME(time, IWDG_CalculateTime(hiwdg, prescaler, IWDG_MAX_TIME_PARAM)));
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  LL_IWDG_EnableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

  IWDG_ConfigureMinTime(hiwdg, prescaler, time);

  tickstart = HAL_GetTick();

  while (LL_IWDG_IsActiveFlag_WVU(IWDG_GET_INSTANCE(hiwdg)) != 0UL)
  {
    /* Recheck the flags in case of interruption during timeout */
    if ((HAL_GetTick() - tickstart) > IWDG_DEFAULT_TIMEOUT)
    {
      if (LL_IWDG_IsActiveFlag_WVU(IWDG_GET_INSTANCE(hiwdg)) != 0UL)
      {
        LL_IWDG_DisableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

        return HAL_ERROR;
      }
    }
  }

  LL_IWDG_DisableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

  return HAL_OK;
}

/**
  * @brief  Get the Window time value according to the handler instance registers.
  * @param  hiwdg    Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                  specified IWDG module.
  * @retval uint32_t Current Window time value.
  */
uint32_t HAL_IWDG_GetMinTime(const hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  return IWDG_CalculateTime(hiwdg, (uint8_t)LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg)),
                            LL_IWDG_GetWindow(IWDG_GET_INSTANCE(hiwdg)));
}

/**
  * @brief  Set the Early Wakeup time value.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @param  time   Early Wakeup time value to be set.
  * @note   Modifying the IWDG early wakeup interrupt register will automatically reload the watchdog counter.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR  Operation completed with error.
  */
hal_status_t HAL_IWDG_SetEarlyWakeupInterruptTime(hal_iwdg_handle_t *hiwdg, uint32_t time)
{
  uint32_t tickstart;
  uint8_t prescaler;

  ASSERT_DBG_PARAM(hiwdg != NULL);

  prescaler = (uint8_t)LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg));

  ASSERT_DBG_PARAM(IS_IWDG_EWI_TIME(time,
                                    IWDG_CalculateTime(hiwdg, prescaler,
                                                       LL_IWDG_GetWindow(IWDG_GET_INSTANCE(hiwdg))),
                                    IWDG_CalculateTime(hiwdg, prescaler, IWDG_MAX_TIME_PARAM)));

  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  LL_IWDG_EnableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

  IWDG_ConfigureEarlyWakeupInterruptTime(hiwdg, prescaler, time);

  tickstart = HAL_GetTick();

  while (LL_IWDG_IsActiveFlag_EWU(IWDG_GET_INSTANCE(hiwdg)) != 0UL)
  {
    if ((HAL_GetTick() - tickstart) > IWDG_DEFAULT_TIMEOUT)
    {
      /* Recheck the flag in case of interruption during timeout */
      if (LL_IWDG_IsActiveFlag_EWU(IWDG_GET_INSTANCE(hiwdg)) != 0UL)
      {
        LL_IWDG_DisableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

        return HAL_ERROR;
      }
    }
  }

  LL_IWDG_DisableWriteAccess(IWDG_GET_INSTANCE(hiwdg));

  return HAL_OK;
}

/**
  * @brief  Get the Window time value according to the handler instance registers.
  * @param  hiwdg     Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                   specified IWDG module.
  * @retval uint32_t  Current Early Wakeup time value.
  */
uint32_t HAL_IWDG_GetEarlyWakeupInterruptTime(const hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  return IWDG_CalculateTime(hiwdg, (uint8_t)LL_IWDG_GetPrescaler(IWDG_GET_INSTANCE(hiwdg)),
                            LL_IWDG_GetEwiTime(IWDG_GET_INSTANCE(hiwdg)));
}

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
/**
  * @brief   Set the LSI frequency for the IWDG driver.
  * @param   hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                 specified IWDG module.
  * @param   lsi_frequency_hz  LSI frequency to be set.
  * @note    This function is available only if USE_HAL_IWDG_LSI_FREQ set to dynamic (LSI_VALUE_DYNAMIC).
  * @warning All parameters must be recomputed after the change of LSI Frequency, a call of HAL_IWDG_Start() must be
  *          done.
  * @retval  HAL_OK Operation completed successfully.
  */
hal_status_t HAL_IWDG_SetLSIFrequency(hal_iwdg_handle_t *hiwdg, uint32_t lsi_frequency_hz)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
#if defined(USE_HAL_IWDG_HARDWARE_START) && (USE_HAL_IWDG_HARDWARE_START == 1UL)
  ASSERT_DBG_STATE(hiwdg->global_state, (uint32_t)HAL_IWDG_STATE_ACTIVE);
#else
  ASSERT_DBG_STATE(hiwdg->global_state, (uint32_t)HAL_IWDG_STATE_IDLE | (uint32_t)HAL_IWDG_STATE_ACTIVE);
#endif /* USE_HAL_IWDG_HARDWARE_START */

  hiwdg->lsi_frequency_hz = lsi_frequency_hz;

  return HAL_OK;
}

/**
  * @brief  Get the current LSI frequency.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @note   This function is available only if USE_HAL_IWDG_LSI_FREQ set to dynamic (LSI_VALUE_DYNAMIC).
  * @retval uint32_t  Current computed LSI frequency value in Hz.
  */
uint32_t HAL_IWDG_GetLSIFrequency(const hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_STATE(hiwdg->global_state, HAL_IWDG_STATE_ACTIVE);

  return hiwdg->lsi_frequency_hz;
}
#endif /* USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC */
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group5
  * @{

  This subsection provides a set of functions allowing to register the IWDG process and callbacks:

    - The function HAL_IWDG_IRQHandler() to handle IWDG interrupts

  There are two ways to use callbacks:\n\n
  Override weak callback function: Call the function HAL_IWDG_EarlyWakeupCallback() to indicate that an early interrupt
  is pending.\n
  Or register callbacks user: Call the function HAL_IWDG_RegisterEarlyWakeupCallback() to register the Early Wakeup
  Callback.
  */

/**
  * @brief  Handle IWDG interrupt request.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @note   The Early Wakeup Interrupt (EWI) can be used if specific safety operations or data logging must be
  *         performed before the actual reset is generated.
  *         The EWI interrupt is enabled by calling HAL_IWDG_Start() function with an early_wakeup_time.
  *         When the downcounter reaches the value EWIT - 1 , an EWI interrupt is generated and the corresponding
  *         Interrupt Service Routine (ISR) can be used to trigger specific actions through the callback,
  *         before the device resets.
  */
void HAL_IWDG_IRQHandler(hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);

  if (LL_IWDG_IsActiveFlag_EWIF(IWDG_GET_INSTANCE(hiwdg)) != 0UL)
  {
    LL_IWDG_ClearFlag_EWIF(IWDG_GET_INSTANCE(hiwdg));

#if defined(USE_HAL_IWDG_REGISTER_CALLBACKS) && (USE_HAL_IWDG_REGISTER_CALLBACKS == 1UL)
    hiwdg->p_early_wakeup_cb(hiwdg);
#else
    HAL_IWDG_EarlyWakeupCallback(hiwdg);
#endif /* USE_HAL_IWDG_REGISTER_CALLBACKS */
  }
}

/**
  * @brief   IWDG Early Wakeup callback.
  * @param   hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @warning This function must not be modified, when the callback is needed, the
             HAL_IWDG_EarlyWakeupCallback() can be implemented in the user file
  */
__WEAK void HAL_IWDG_EarlyWakeupCallback(hal_iwdg_handle_t *hiwdg)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hiwdg);

}

#if defined(USE_HAL_IWDG_REGISTER_CALLBACKS) && (USE_HAL_IWDG_REGISTER_CALLBACKS == 1UL)
/**
  * @brief  Register the user IWDG Early Wakeup Callback.
  * @param  hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                specified IWDG module.
  * @param  p_callback pointer to the hal_iwdg_cb_t Callback function
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  */
hal_status_t HAL_IWDG_RegisterEarlyWakeupCallback(hal_iwdg_handle_t *hiwdg, hal_iwdg_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1UL)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hiwdg->p_early_wakeup_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_IWDG_REGISTER_CALLBACKS */
/**
  * @}
  */

#if defined(USE_HAL_IWDG_USER_DATA) && (USE_HAL_IWDG_USER_DATA == 1UL)
/** @addtogroup IWDG_Exported_Functions_Group6
  * @{

  This section provides functions allowing to Set and Get user data:
    - HAL_IWDG_SetUserData() to store the user data into the IWDG handle.
    - HAL_IWDG_GetUserData() retrieve the user data from the IWDG handle.
  */

/**
  * @brief Store the user data into the IWDG handle.
  * @param hiwdg       Pointer to IWDG handle.
  * @param p_user_data Pointer to the user data.
  */
void HAL_IWDG_SetUserData(hal_iwdg_handle_t *hiwdg, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);

  hiwdg->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the IWDG handle.
  * @param  hiwdg Pointer to IWDG handle.
  * @retval Pointer to the user data.
  */
const void *HAL_IWDG_GetUserData(const hal_iwdg_handle_t *hiwdg)
{
  ASSERT_DBG_PARAM(hiwdg != NULL);

  return (hiwdg->p_user_data);
}
/**
  * @}
  */

#endif /* USE_HAL_IWDG_USER_DATA */
/**
  * @}
 */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup IWDG_Private_Functions
  * @{
  */


/**
  * @brief   Calculate the IWDG prescaler from the reset time set by the user.
  * @param   hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                 specified IWDG module.
  * @param   max_time Corresponding maximum time in the selected USE_HAL_IWDG_TIME_UNIT unit.
  * @retval  0 for a prescaler = 4.
  * @retval  1 for a prescaler = 8.
  * @retval  2 for a prescaler = 16.
  * @retval  3 for a prescaler = 32.
  * @retval  4 for a prescaler = 64.
  * @retval  5 for a prescaler = 128.
  * @retval  6 for a prescaler = 256.
  * @retval  7 for a prescaler = 512.
  * @retval  [8..15] for a prescaler = 1024.
  */
static uint8_t IWDG_CalculatePrescaler(const hal_iwdg_handle_t *hiwdg, uint32_t max_time)
{
  uint32_t max_period = max_time;

#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US)
  max_period = max_period / IWDG_TIME_CONVERSION;
#elif (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_S)
  max_period = max_period * IWDG_TIME_CONVERSION;
#endif /* USE_HAL_IWDG_TIME_UNIT */

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  max_period = (max_period * hiwdg->lsi_frequency_hz / IWDG_TIME_CONVERSION) / (4UL * IWDG_MAX_STEP_NR);
#else
  STM32_UNUSED(hiwdg);
  max_period = (max_period * USE_HAL_IWDG_LSI_FREQ / IWDG_TIME_CONVERSION) / (4UL * IWDG_MAX_STEP_NR);
#endif /* USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC */

  return (uint8_t)(32UL - __CLZ((uint32_t)max_period));
}

/**
  * @brief   Calculate the IWDG reload parameter from the user-provided maximum time.
  * @param   hiwdg     Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                    specified IWDG module.
  * @param   prescaler IWDG prescaler.
  * @param   max_time  Corresponding maximum time in the selected USE_HAL_IWDG_TIME_UNIT unit.
  * @retval  uint16_t  Current reload parameter.
  */
static uint16_t IWDG_CalculateReload(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t max_time)
{
  uint32_t reload = max_time;
  uint32_t lsi_frequency = USE_HAL_IWDG_LSI_FREQ;

#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_S)
  reload *= IWDG_TIME_CONVERSION;
#endif /* USE_HAL_IWDG_TIME_UNIT */

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  lsi_frequency = hiwdg->lsi_frequency_hz;
#else
  STM32_UNUSED(hiwdg);
#endif /* USE_HAL_IWDG_LSI_FREQ */

#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US)
  reload = (uint32_t)(((((uint64_t)reload * (uint64_t)lsi_frequency /
                         ((uint64_t)IWDG_TIME_CONVERSION * IWDG_TIME_CONVERSION * 2UL *
                          (uint64_t)((uint64_t)1UL << prescaler))) + 1UL) >> 1UL) - 1UL);
#else
  reload = ((reload * lsi_frequency /
             (IWDG_TIME_CONVERSION * 2UL * (1UL << prescaler)) + 1UL) >> 1UL) - 1UL;
#endif /* USE_HAL_IWDG_TIME_UNIT */

  return (uint16_t)(reload);
}

/**
  * @brief   Calculate the IWDG configuration parameters from the user-provided times.
  * @param   hiwdg      Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                     specified IWDG module.
  * @param   prescaler  IWDG prescaler.
  * @param   time       Corresponding maximum time in the selected USE_HAL_IWDG_TIME_UNIT unit.
  * @note    By passing min_time as a parameter, it is converted to Window.
  * @note    By passing early_wakeup_time as a parameter, it is converted to early_wakeup_interrupt.
  * @retval  uint16_t   Converted parameter found.
  */
static uint16_t IWDG_CalculateParam(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t time)
{
  uint32_t param = time;
  uint32_t lsi_freq = USE_HAL_IWDG_LSI_FREQ;

#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_S)
  param = (param * IWDG_TIME_CONVERSION);
#endif /* USE_HAL_IWDG_TIME_UNIT */

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  lsi_freq = hiwdg->lsi_frequency_hz;
#endif /* USE_HAL_IWDG_LSI_FREQ */

#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US)
  param = hiwdg->reload - (uint32_t)((((((uint64_t)param * (uint64_t)lsi_freq) / \
                                        ((uint64_t)IWDG_TIME_CONVERSION * IWDG_TIME_CONVERSION * 2UL * \
                                         (uint64_t)((uint64_t)1UL << prescaler)))) + 1UL) >> 1UL);
#else
  param = hiwdg->reload - ((((param * lsi_freq) / (IWDG_TIME_CONVERSION * 2UL * (1UL << prescaler))) + 1UL) >> 1UL);
#endif /* USE_HAL_IWDG_TIME_UNIT */

  return (uint16_t)(param);
}

/**
  * @brief   Calculate  the timings from the according configuration parameters of the IWDG driver.
  * @param   hiwdg      Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                     specified IWDG module.
  * @param   prescaler  IWDG prescaler.
  * @param   param      Parameter corresponding to a timing.
  * @note    By passing Window as a parameter, it is converted to min_time.
  * @note    By passing early_wakeup_interrupt register value as a parameter, it will be converted to early_wakeup_time.
  * @note    By passing IWDG_MAX_TIME_PARAM as a parameter, it will be converted to max_time.
  * @retval  uint32_t   Converted time found in the selected USE_HAL_IWDG_TIME_UNIT unit.
  */
static uint32_t IWDG_CalculateTime(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t param)
{
  uint32_t returned_time;
  uint32_t remainder;
  uint32_t dividend;
  uint32_t divisor = USE_HAL_IWDG_LSI_FREQ;
  uint32_t reload_value = (hiwdg->reload - param);

  if (param == IWDG_MAX_RELOAD)
  {
    return 0U;
  }

  if (param == IWDG_MAX_TIME_PARAM)
  {
    reload_value = (hiwdg->reload + 1UL);
  }
  dividend = (reload_value * IWDG_TIME_CONVERSION * 4UL * (1UL << prescaler));

#if (USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC)
  divisor = hiwdg->lsi_frequency_hz;
#endif /* USE_HAL_IWDG_LSI_FREQ == LSI_VALUE_DYNAMIC */

  returned_time = dividend / divisor;
  remainder = dividend % divisor;

  if ((remainder * 2UL) >= divisor)
  {
    returned_time++;
  }

  /* Time conversion to selected unit */
#if (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_US)
  return (returned_time * IWDG_TIME_CONVERSION);
#elif (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_MS)
  return returned_time;
#elif (USE_HAL_IWDG_TIME_UNIT == HAL_IWDG_TIME_UNIT_S)
  uint32_t time_in_seconds = returned_time / IWDG_TIME_CONVERSION;
  if (((returned_time % IWDG_TIME_CONVERSION) * 2UL) >= IWDG_TIME_CONVERSION)
  {
    time_in_seconds++;
  }
  return time_in_seconds;
#endif /* USE_HAL_IWDG_TIME_UNIT */
}

/**
  * @brief   Configure the Window time value for the IWDG.
  * @param   hiwdg      Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *                     specified IWDG module.
  * @param   prescaler  Prescaler value.
  * @param   time       Minimum time in the selected USE_HAL_IWDG_TIME_UNIT unit.
  */
static void IWDG_ConfigureMinTime(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler, uint32_t time)
{
  if (time != 0UL)
  {
    uint16_t window = IWDG_CalculateParam(hiwdg, prescaler, time);

    if (LL_IWDG_GetWindow(IWDG_GET_INSTANCE(hiwdg)) != (uint32_t)window)
    {
      /* Write to IWDG WINR the IWDG_Window value to compare with */
      /* In any case, even if Window feature is disabled, watchdog will be reloaded by writing windows register */
      LL_IWDG_SetWindow(IWDG_GET_INSTANCE(hiwdg), (uint32_t)window);
    }
    else
    {
      LL_IWDG_ReloadCounter(IWDG_GET_INSTANCE(hiwdg));
    }
  }
  else
  {
    /* Write to IWDG WINR the IWDG_Window value to compare with */
    /* In any case, even if Window feature is disabled, watchdog will be reloaded by writing windows register */
    LL_IWDG_SetWindow(IWDG_GET_INSTANCE(hiwdg), (uint16_t)IWDG_WINDOW_DISABLE);
  }
}

/**
  * @brief Configure the Early Wakeup Interrupt time for the IWDG.
  * @param hiwdg  Pointer to a hal_iwdg_handle_t structure that contains the configuration information for the
  *               specified IWDG module.
  * @param prescaler           Prescaler value.
  * @param early_wakeup_time   Early Wakeup Interrupt time in the selected USE_HAL_IWDG_TIME_UNIT unit.
  */
static void IWDG_ConfigureEarlyWakeupInterruptTime(const hal_iwdg_handle_t *hiwdg, uint8_t prescaler,
                                                   uint32_t early_wakeup_time)
{
  if (early_wakeup_time == 0UL)
  {
    LL_IWDG_DisableIT_EWI(IWDG_GET_INSTANCE(hiwdg));
  }
  else
  {
    uint16_t early_wakeup = IWDG_CalculateParam(hiwdg, prescaler, early_wakeup_time);

    LL_IWDG_WRITE_REG(IWDG_GET_INSTANCE(hiwdg), EWCR, IWDG_EWCR_EWIE | IWDG_EWCR_EWIC | early_wakeup);
  }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_IWDG_MODULE */
/**
  * @}
  */
