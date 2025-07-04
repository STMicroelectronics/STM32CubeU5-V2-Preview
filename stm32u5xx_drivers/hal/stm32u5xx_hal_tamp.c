/**
  ******************************************************************************
  * @file    stm32u5xx_hal_tamp.c
  * @brief   TAMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the TAMP peripheral:
  *           + Passive tamper events
  *           + Active tamper events
  *           + Internal tamper events
  *           + Monotonic counter
  *           + Device secrets protection
  *           + Backup registers
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

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup TAMP
  * @brief TAMP HAL module driver
  * @{
  * The antitamper detection circuit is used to protect sensitive data from external
  * attacks. The detection is made on an event of the different tamper I/O or on internal
  * monitors detecting out-of-range device conditions.
  *
  * The TAMP driver provides:
  * * external tampers that can work in two modes:
  *   * active mode that is a continuous comparison between a tamper output and input
  *   * passive mode that are ultra-low power edge or level detection
  * * internal tampers to protect against transient or environmental perturbation
  * of the microcontroller
  * * monotonic counters
  * * backup registers read/write
  * * configuration of device secret protection
  *
  * The TAMP driver is part of the backup domain. When clocked by the LSE and powered through the VBAT pin,
  * it can be functional in all low-power modes.
  *
  * # TAMP operating condition
  *
  * The antitamper detection circuit is part of the backup domain and
  * can be powered from VBAT when the main VDD supply is powered off.
  * When VDD is turned off, it is possible to retain the content of the TAMP registers and supply the TAMP peripheral.
  * To do so, the VBAT can be connected to an optional standby voltage supplied by a battery or by another source.
  *
  * The TAMP clock also used by the RTC driver, is called RTCCLK and can come from different sources:
  * - HSE with a prescaler
  * - LSE
  * - LSI with a prescaler
  *
  * # Backup domain reset
  *
  * The backup domain reset sets all TAMP registers and the RCC_BDCR register to their reset values.
  * A backup domain reset occurs when:
  * * triggered by setting the BDRST bit in the RCC backup domain control register  (RCC_BDCR).
  * * totally powering off the microcontroller.
  *
  * # Backup domain access
  *
  * After reset, the backup domains are protected against possible unwanted write accesses.
  * To enable access to the TAMP domain and TAMP registers, proceed as follows:
  * * Enable the clock driving the power controller interface using the @ref HAL_RCC_PWR_EnableClock function
  * * Enable access to backup domain using the @ref HAL_PWR_DisableRTCDomainWriteProtection
  * function
  * * Select the RTC clock source using the @ref HAL_RCC_RTC_SetKernelClkSource function
  * * Enable RTCAPB clock using the @ref HAL_RCC_RTCAPB_EnableClock function
  *
  * # TAMP and microcontroller low power modes
  *
  * The MCU can be woken up from a low power mode by a tamper or internal tamper event.
  * These TAMP functions can wake up the system from the all low-power modes.
  * Wake-up from stop and standby mode is possible only when the TAMP clock source is LSE or LSI.
  * For shutdown mode it is only possible when the TAMP clock source is LSE.

Config defines                | Description      | Default value         | Note
------------------------------| -----------------| --------------------- | --------------------------------------------
USE_HAL_TAMP_MODULE           | hal_conf.h       | 1                     | When set, HAL TAMP module is enabled
USE_HAL_CHECK_PARAM           | hal_conf.h       | 0                     | When set, parameters are checked in runtime
USE_ASSERT_DBG_PARAM          | PreProcessor env | NA                    | When defined, enable the params assert

  */

#if defined(USE_HAL_TAMP_MODULE) && (USE_HAL_TAMP_MODULE == 1)

/* Private types -----------------------------------------------------------*/
/** @defgroup TAMP_Private_Types TAMP Private Types
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup TAMP_Private_Constants TAMP Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup TAMP_Private_Macros TAMP Private Macros
  * @{
  */

/** @defgroup TAMP_Private_Macros_Assert_Tampers TAMP private macros for tampers.
  * @{
  */
#define IS_TAMP_TAMPERS(tampers) (((((tampers) & HAL_TAMP_TAMPER_1) == HAL_TAMP_TAMPER_1)     \
                                   || (((tampers) & HAL_TAMP_TAMPER_2) == HAL_TAMP_TAMPER_2)  \
                                   || (((tampers) & HAL_TAMP_TAMPER_3) == HAL_TAMP_TAMPER_3)  \
                                   || (((tampers) & HAL_TAMP_TAMPER_4) == HAL_TAMP_TAMPER_4)  \
                                   || (((tampers) & HAL_TAMP_TAMPER_5) == HAL_TAMP_TAMPER_5)  \
                                   || (((tampers) & HAL_TAMP_TAMPER_6) == HAL_TAMP_TAMPER_6)  \
                                   || (((tampers) & HAL_TAMP_TAMPER_7) == HAL_TAMP_TAMPER_7)  \
                                   || (((tampers) & HAL_TAMP_TAMPER_8) == HAL_TAMP_TAMPER_8)) \
                                  && (((tampers) & (~HAL_TAMP_TAMPER_ALL)) == 0U))
/*!< Tests tampers */

#define IS_TAMP_TAMPERS_IT(interruption) (((((interruption) & HAL_TAMP_IT_TAMPER_1) == HAL_TAMP_IT_TAMPER_1)    \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_2) == HAL_TAMP_IT_TAMPER_2) \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_3) == HAL_TAMP_IT_TAMPER_3) \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_4) == HAL_TAMP_IT_TAMPER_4) \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_5) == HAL_TAMP_IT_TAMPER_5) \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_6) == HAL_TAMP_IT_TAMPER_6) \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_7) == HAL_TAMP_IT_TAMPER_7) \
                                           || (((interruption) & HAL_TAMP_IT_TAMPER_8) == HAL_TAMP_IT_TAMPER_8) \
                                           || (interruption) == HAL_TAMP_IT_NONE)                               \
                                          && (((interruption) & (~HAL_TAMP_IT_ALL))==0U))
/*!< Tests tampers interruption */

/**
  * @}
  */


/** @defgroup TAMP_Private_Macros_Assert_Passive TAMP private macros for passive tampers.
  * @{
  */


#define IS_TAMP_PASSIVE_PRECHARGE_STATE(state) (((state) == HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_DISABLE ) \
                                                || ((state) == HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_ENABLE ))
/*!< Tests passive tamper precharge state */

#define IS_TAMP_PASSIVE_PRECHARGE_DURATION(duration) \
  (((duration) == HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_1_RTCCLK )    \
   || ((duration) == HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_2_RTCCLK ) \
   || ((duration) == HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_4_RTCCLK ) \
   || ((duration) == HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_8_RTCCLK ))
/*!< Tests passive tamper precharge duration */

#define IS_TAMP_PASSIVE_FILTER(filter) (((filter) == HAL_TAMP_PASSIVE_FILTER_DISABLE )      \
                                        || ((filter) == HAL_TAMP_PASSIVE_FILTER_2_SAMPLES ) \
                                        || ((filter) == HAL_TAMP_PASSIVE_FILTER_4_SAMPLES ) \
                                        || ((filter) == HAL_TAMP_PASSIVE_FILTER_8_SAMPLES ))
/*!< Tests passive tamper filter */

#define IS_TAMP_PASSIVE_SAMPLE_FREQUENCY(frequency) (((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_256 )      \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_512 )   \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_1024 )  \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_2048 )  \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_4096 )  \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_8192 )  \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_16384 ) \
                                                     || ((frequency) == HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_32768 ))
/*!< Tests passive tamper sample frequency*/

#define IS_TAMP_PASSIVE_DETECTION(detection) (((detection) == HAL_TAMP_PASSIVE_TRIGGER_RISING )    \
                                              || ((detection) == HAL_TAMP_PASSIVE_TRIGGER_FALLING) \
                                              || ((detection) == HAL_TAMP_PASSIVE_TRIGGER_LOW)     \
                                              || ((detection) == HAL_TAMP_PASSIVE_TRIGGER_HIGH))
/*!< Tests passive tamper detection */

#define IS_TAMP_PASSIVE_ERASE(mode) (((mode) == HAL_TAMP_PASSIVE_SECRETS_ERASE ) \
                                     || ((mode) == HAL_TAMP_PASSIVE_SECRETS_NO_ERASE ))
/*!< Tests passive tamper erase mode */

#define IS_TAMP_PASSIVE_MASK(mask) (((mask) == HAL_TAMP_PASSIVE_UNMASKED ) \
                                    || ((mask) == HAL_TAMP_PASSIVE_MASKED ))
/*!< Tests passive tamper mask status */

/**
  * @}
  */

/** @defgroup TAMP_Private_Macros_Assert_Internal TAMP private macros for internal tampers.
  * @{
  */
#define IS_TAMP_INTERNAL_TAMPERS(tampers) (((((tampers) & HAL_TAMP_INTERNAL_TAMPER_1)     \
                                             == HAL_TAMP_INTERNAL_TAMPER_1)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_2)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_2)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_3)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_3)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_5)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_5)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_6)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_6)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_7)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_7)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_8)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_8)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_9)  \
                                                == HAL_TAMP_INTERNAL_TAMPER_9)   \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_11) \
                                                == HAL_TAMP_INTERNAL_TAMPER_11)  \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_12) \
                                                == HAL_TAMP_INTERNAL_TAMPER_12)  \
                                            || (((tampers) & HAL_TAMP_INTERNAL_TAMPER_13) \
                                                == HAL_TAMP_INTERNAL_TAMPER_13)) \
                                           && (((tampers) & (~HAL_TAMP_INTERNAL_ALL)) == 0U))
/*!< Tests internal tampers*/

#define IS_TAMP_INTERNAL_TAMPERS_IT(interruption) (((((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_1)     \
                                                     == HAL_TAMP_INTERNAL_IT_TAMPER_1)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_2)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_2)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_3)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_3)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_5)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_5)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_6)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_6)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_7)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_7)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_8)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_8)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_9)  \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_9)  \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_11) \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_11) \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_12) \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_12) \
                                                    || (((interruption) & HAL_TAMP_INTERNAL_IT_TAMPER_13) \
                                                        == HAL_TAMP_INTERNAL_IT_TAMPER_13) \
                                                    || (interruption) == HAL_TAMP_INTERNAL_IT_NONE)       \
                                                   && (((interruption) & (~HAL_TAMP_INTERNAL_IT_ALL)) == 0U))
/*!< Tests internal tampers interruption */

#define IS_TAMP_INTERNAL_ERASE(mode) (((mode) == HAL_TAMP_INTERNAL_SECRETS_ERASE ) \
                                      || ((mode) == HAL_TAMP_INTERNAL_SECRETS_NO_ERASE ))
/*!< Tests internal tamper erase mode */

/**
  * @}
  */

/** @defgroup TAMP_Private_Macros_Assert_Active TAMP private macros for active tampers.
  * @{
  */

#define IS_TAMP_ACTIVE_OUTPUT_PERIOD(period) ((period) <= HAL_TAMP_OUTPUT_PERIOD)
/*!< Tests active tamper output period */

#define IS_TAMP_ACTIVE_FILTER(state) (((state) == HAL_TAMP_ACTIVE_FILTER_DISABLE ) \
                                      || ((state) == HAL_TAMP_ACTIVE_FILTER_ENABLE ))
/*!< Tests active tamper filter state */

#define IS_TAMP_ACTIVE_ASYNCHRONOUS_PRESCALER(division) (((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK)            \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_2)   \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_4)   \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_8)   \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_16)  \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_32)  \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_64)  \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_128) \
                                                         || ((division) == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_2048))
/*!< Tests active tamper asynchronous prescaler */

#define IS_TAMP_ACTIVE_OUTPUT_SHARED(state) (((state) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_NOT_SHARED ) \
                                             || ((state) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_SHARED ))
/*!< Tests active tamper output sharing */

#define IS_TAMP_ACTIVE_ERASE(mode) (((mode) == HAL_TAMP_ACTIVE_SECRETS_ERASE ) \
                                    || ((mode) == HAL_TAMP_ACTIVE_SECRETS_NO_ERASE ))
/*!< Tests active tamper erase mode */

#define IS_TAMP_ACTIVE_TAMPER_OUTPUT(tamper) (((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_1)    \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_2) \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_3) \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_4) \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_5) \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_6) \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_7) \
                                              || ((tamper) == HAL_TAMP_ACTIVE_TAMPER_OUTPUT_8))
/*!< Tests active tamper outputs */

/**
  * @}
  */

/** @defgroup TAMP_Private_Macros_Assert_Monotonic_Counters TAMP private macros for monotonic counters.
  * @{
  */

#define IS_TAMP_MONOTONIC_COUNTER(counter) (((counter) == HAL_TAMP_MONOTONIC_1 ))
/*!< Tests monotonic counters */

/**
  * @}
  */

/** @defgroup TAMP_Private_Macros_Assert_Resources TAMP private macros for resources
  * @{
  */
#define IS_TAMP_RESOURCES(resource) ((((resource) & HAL_TAMP_BACKUP_SRAM) == HAL_TAMP_BACKUP_SRAM) \
                                     && (((resource) & (~HAL_TAMP_RESOURCES_ALL)) == 0U))
/*!< Tests resources */

/**
  * @}
  */

/** @defgroup TAMP_Private_Macros_Assert_Backup_Register TAMP private macros for Backup registers.
  * @{
  */

#define IS_TAMP_BACKUP_REGISTER(backup) ((backup) < LL_TAMP_BACKUP_NB )
/*!< Tests backup registers*/

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup TAMP_Private_Variables TAMP Private Variables
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup TAMP_Exported_Functions
  * @{
  */

/** @addtogroup TAMP_Exported_Functions_Passive
  * @{
  *
  * In passive mode the tampers inputs are monitored and a tamper is detected
  * either on edge or level detection. Those different detection types can be configured
  * by changing the parameters of a digital filter that are common for all the passive
  * tampers. This filter is used to avoid false tamper detection.
  * The passive tampers can work in confirmed or potential modes.
  *
  * # Passive tampers
  * ## Edge detection
  *
  * Edge mode consists of a tamper event generation when either a rising or falling edge
  * is observed. To configure the tampers in edge mode, the application must call @ref HAL_TAMP_PASSIVE_SetConfig
  * with @ref hal_tamp_passive_config_t::type_activation set to @ref HAL_TAMP_PASSIVE_FILTER_DISABLE.
  * The parameter @ref hal_tamp_passive_individual_config_t::trigger must be set to the desired edge type
  * by calling the @ref HAL_TAMP_PASSIVE_SetConfigTampers.
  *
  * The user can use this mode of tamper detection with the RTCCLK disabled.
  *
  * ## Level detection
  *
  * Level mode consists of a tamper event generation when two, four or eight consecutive samples are observed
  * at the level configured. Calling the @ref HAL_TAMP_PASSIVE_SetConfigTampers and setting
  * @ref hal_tamp_passive_individual_config_t::trigger enable the configuration of the level.
  * To configure the tampers in level mode, the application must call @ref HAL_TAMP_PASSIVE_SetConfig
  * with @ref hal_tamp_passive_config_t::type_activation set to:
  * * @ref HAL_TAMP_PASSIVE_FILTER_2_SAMPLES, for two samples detection.
  * * @ref HAL_TAMP_PASSIVE_FILTER_4_SAMPLES, for four samples detection.
  * * @ref HAL_TAMP_PASSIVE_FILTER_8_SAMPLES, for eight samples detection.
  *
  * The sampling frequency is chosen by programming the @ref hal_tamp_passive_config_t::sample_frequency
  *
  * The inputs can be precharged before sampled during a certain duration, this is configured by calling
  * @ref HAL_TAMP_PASSIVE_SetConfig and programming the parameters
  * @ref hal_tamp_passive_config_t::precharge and
  * @ref hal_tamp_passive_config_t::precharge_duration
  *
  * # Potential and confirmed mode.
  *
  * Each tamper can work in two modes regarding the device secrets erase. The confirmed mode means
  * that when a tamper event occurs the device secrets are automatically erased. The potential mode
  * does not erase all the device secrets when a tamper event occurs. Instead it blocks the read and write
  * access of the device secrets. The access is unblocked when the tamper event is cleared.
  * To configure the erase mode call @ref HAL_TAMP_PASSIVE_SetConfigTampers and configure
  * the hal_tamp_passive_individual_config_t::erase_secrets parameter.
  *
  * # Masked
  *
  * Some of the tampers can be masked. This means that the application does not need to clear them
  * after a trigger. If a tamper is masked, triggering the tamper event will not affect the device secrets in any way.
  *
  * This feature is only available when using passive tampers in level mode and interruption is disabled.
  *
  */

/**
  * @brief Configure the passive tampers global parameters.
  * @param p_config Pointer to the passive tampers global configuration instance.
  * @retval HAL_OK if the configuration is successful, HAL_INVALID_PARAM if the parameter is invalid.
  */
hal_status_t HAL_TAMP_PASSIVE_SetConfig(const hal_tamp_passive_config_t *p_config)
{

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_PRECHARGE_STATE(p_config->precharge));
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_PRECHARGE_DURATION(p_config->precharge_duration));
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_FILTER(p_config->type_activation));
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_SAMPLE_FREQUENCY(p_config->sample_frequency));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_TAMP_SetConfig((uint32_t) p_config->precharge,
                    (uint32_t) p_config->precharge_duration,
                    (uint32_t) p_config->type_activation,
                    (uint32_t) p_config->sample_frequency);

  return HAL_OK;
}

/**
  * @brief Retrieve the passive tamper global parameters.
  * @param p_config Pointer to the passive tampers global configuration instance.
  */
void HAL_TAMP_PASSIVE_GetConfig(hal_tamp_passive_config_t *p_config)
{
  uint32_t config_tampers = LL_TAMP_GetConfig();

  ASSERT_DBG_PARAM(p_config != NULL);

  p_config->precharge = (hal_tamp_passive_pull_up_precharge_state_t) LL_TAMP_GET_PULL_UP(config_tampers);
  p_config->precharge_duration = (hal_tamp_passive_pull_up_precharge_duration_t) \
                                 LL_TAMP_GET_PRECHARGE_DURATION(config_tampers);
  p_config->type_activation = (hal_tamp_passive_filter_t) LL_TAMP_GET_FILTER_SAMPLE(config_tampers);
  p_config->sample_frequency = (hal_tamp_passive_sample_frequency_t) \
                               LL_TAMP_GET_FILTER_SAMPLE_FREQUENCY(config_tampers);

}

/**
  * @brief Configure the passive tampers individual parameters
  * @param tampers tampers to be configured, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param p_config Pointer to the passive tamper individual configuration instance.
  * @note Only the three first tampers can be masked.
  * @retval HAL_OK, HAL_INVALID_PARAM if the parameter is invalid
  */
hal_status_t HAL_TAMP_PASSIVE_SetConfigTampers(uint32_t tampers,
                                               const hal_tamp_passive_individual_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_DETECTION(p_config->trigger));
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_ERASE(p_config->erase_secrets));
  ASSERT_DBG_PARAM(IS_TAMP_PASSIVE_MASK(p_config->masked));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_TAMP_SetConfigTampers(tampers, (uint32_t) p_config->trigger,
                           (uint32_t) p_config->erase_secrets,
                           (uint32_t) p_config->masked);

  return HAL_OK;
}

/**
  * @brief Retrieve the passive tamper individual parameters
  * @param tamper tamper to retrieve the configuration, can be one of the following values
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param p_config Pointer to the passive tamper individual configuration instance.
  */
void HAL_TAMP_PASSIVE_GetConfigTamper(uint32_t tamper,
                                      hal_tamp_passive_individual_config_t *p_config)
{
  uint32_t config_tamper = LL_TAMP_GetConfigTampers(tamper);

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tamper));

  p_config->trigger = (hal_tamp_passive_trigger_t) LL_TAMP_GET_TRIGGER(config_tamper);
  p_config->erase_secrets = (hal_tamp_passive_secrets_erase_t) LL_TAMP_GET_NOERASE(config_tamper);
  p_config->masked = (hal_tamp_passive_mask_t) LL_TAMP_GET_MASK(config_tamper);

}

/**
  * @brief Start the passive tampers
  * @param tampers tampers to be started, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param interruption enable the interruption, can be a combination of
  *        @arg @ref HAL_TAMP_IT_NONE
  *        @arg @ref HAL_TAMP_IT_TAMPER_1
  *        @arg @ref HAL_TAMP_IT_TAMPER_2
  *        @arg @ref HAL_TAMP_IT_TAMPER_3
  *        @arg @ref HAL_TAMP_IT_TAMPER_4
  *        @arg @ref HAL_TAMP_IT_TAMPER_5
  *        @arg @ref HAL_TAMP_IT_TAMPER_6
  *        @arg @ref HAL_TAMP_IT_TAMPER_7
  *        @arg @ref HAL_TAMP_IT_TAMPER_8
  * @retval HAL_OK
  * @retval HAL_ERROR If trying to enable an interruption to a masked tamper.
                      or if trying to start a tamper that is already started as active tamper.
  */
hal_status_t HAL_TAMP_PASSIVE_Start(uint32_t tampers, uint32_t interruption)
{

  uint32_t active_tampers = LL_TAMP_ATAMP_GetActiveMode();
  uint32_t enabled_tampers = LL_TAMP_GetEnabled(LL_TAMP_ALL);
  uint32_t masked_tampers = LL_TAMP_GetMasked((tampers << LL_TAMP_POSITION_FIRST_MASKED));

  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS_IT(interruption));

  if (((active_tampers & enabled_tampers) & tampers) != 0U)
  {
    return HAL_ERROR;
  }

  if ((masked_tampers & (interruption << LL_TAMP_POSITION_FIRST_MASKED)) != 0U)
  {
    return HAL_ERROR;
  }


  LL_TAMP_ATAMP_DisableActiveMode(tampers);
  LL_TAMP_Enable(tampers);
  LL_TAMP_EnableIT(interruption);

  return HAL_OK;
}

/**
  * @brief Stop the passive tampers
  * @param tampers tampers to be stopped, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_PASSIVE_Stop(uint32_t tampers)
{
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));

  LL_TAMP_Disable(tampers);
  LL_TAMP_DisableIT(tampers);
  LL_TAMP_ClearFlag_TAMP(tampers);

  return HAL_OK;
}

/**
  * @brief Poll for a tamper event among tampers given in @p tampers
  * @note  Call HAL_TAMP_PASSIVE_Stop to clear the pending tamper event.
  * @param tampers tampers to be checked, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param timeout_ms Timeout duration
  * @retval HAL_OK
  * @retval HAL_TIMEOUT when reaching the timeout during polling.
  */
hal_status_t HAL_TAMP_PASSIVE_PollForEvent(uint32_t tampers, uint32_t timeout_ms)
{
  uint32_t tickstart = HAL_GetTick();

  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));

  while (LL_TAMP_IsActiveFlag_TAMP(tampers) == 0U)
  {
    if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_TAMP_IsActiveFlag_TAMP(tampers) == 0U)
      {
        return HAL_TIMEOUT;
      }
      else
      {
        break;
      }
    }
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup TAMP_Exported_Functions_Internal
  * @brief Internal tamper exported functions.
  * @{
  *
  * The internal tampers are tampers linked to a specific part of the microcontroller. They protect
  * the microcontroller device secrets in case of transient or environmental perturbation attacks.
  * They can work in potential or confirmed mode.
  *
  * Each tamper can work in two modes regarding the device secrets erase. The confirmed mode means
  * that when a tamper event occurs the device secrets are automatically erased. The potential mode
  * does not erase all the device secrets when a tamper event occurs. Instead it blocks the read and write
  * access of the device secrets. The access is unblocked when the tamper event is cleared.
  *
  * To configure the erase mode call @ref HAL_TAMP_INTERNAL_SetConfigTampers and configure
  * the hal_tamp_internal_individual_config_t::erase_secrets parameter.
  *
  */

/**
  * @brief Configure the internal tampers individual parameters
  * @param internal_tampers tampers to be configured, can be a combination of
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_1
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_2
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_3
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_5
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_6
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_7
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_8
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_9
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_11
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_12
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_13
  * @param p_config Pointer to the internal tamper individual configuration instance.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_INTERNAL_SetConfigTampers(uint32_t internal_tampers,
                                                const hal_tamp_internal_individual_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_TAMPERS(internal_tampers));
  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_ERASE(p_config->erase_secrets));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)

  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_TAMP_SetConfigInternalTampers(internal_tampers, (uint32_t) p_config->erase_secrets);

  return HAL_OK;
}

/**
  * @brief Retrieve the internal tamper individual parameter
  * @param internal_tamper tamper to retrieve the configuration, can be one of the following values
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_1
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_2
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_3
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_5
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_6
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_7
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_8
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_9
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_11
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_12
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_13
  * @param p_config Pointer to the internal tamper individual configuration instance.
  */
void HAL_TAMP_INTERNAL_GetConfigTamper(uint32_t internal_tamper,
                                       hal_tamp_internal_individual_config_t *p_config)
{
  uint32_t config_tamper = LL_TAMP_GetConfigInternalTampers(internal_tamper);

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_TAMPERS(internal_tamper));

  p_config->erase_secrets = (hal_tamp_internal_secrets_erase_t) LL_TAMP_INTERNAL_GET_NOERASE(config_tamper);
}

/**
  * @brief Start the internal tampers
  * @param internal_tampers internal tampers to be started, can be a combination of
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_1
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_2
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_3
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_5
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_6
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_7
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_8
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_9
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_11
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_12
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_13
  * @param interruption enable the interruption, can be a combination of
  *        @arg @ref HAL_TAMP_INTERNAL_IT_NONE
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_1
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_2
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_3
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_5
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_6
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_7
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_8
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_9
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_11
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_12
  *        @arg @ref HAL_TAMP_INTERNAL_IT_TAMPER_13
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_INTERNAL_Start(uint32_t internal_tampers, uint32_t interruption)
{
  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_TAMPERS(internal_tampers));
  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_TAMPERS_IT(interruption));

  LL_TAMP_ITAMP_Enable(internal_tampers);
  LL_TAMP_ITAMP_EnableIT(interruption);

  return HAL_OK;
}

/**
  * @brief Stop the internal tampers
  * @param internal_tampers tampers to be stopped, can be a combination of
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_1
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_2
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_3
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_5
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_6
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_7
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_8
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_9
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_11
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_12
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_13
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_INTERNAL_Stop(uint32_t internal_tampers)
{
  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_TAMPERS(internal_tampers));

  LL_TAMP_ITAMP_Disable(internal_tampers);
  LL_TAMP_ITAMP_DisableIT(internal_tampers);
  LL_TAMP_ClearFlag_ITAMP(internal_tampers);

  return HAL_OK;
}

/**
  * @brief Poll for a internal tamper event among internal tampers given in @p internal_tampers
  * @note  Call HAL_TAMP_INTERNAL_Stop to clear the pending internal tamper event.
  * @param internal_tampers Internal tampers to be checked, can be a combination of
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_1
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_2
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_3
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_5
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_6
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_7
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_8
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_9
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_11
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_12
  *        @arg @ref HAL_TAMP_INTERNAL_TAMPER_13
  * @param timeout_ms Timeout duration
  * @retval HAL_OK
  * @retval HAL_TIMEOUT when reaching the timeout during polling.
  */
hal_status_t HAL_TAMP_INTERNAL_PollForEvent(uint32_t internal_tampers,
                                            uint32_t timeout_ms)
{
  uint32_t tickstart = HAL_GetTick();

  ASSERT_DBG_PARAM(IS_TAMP_INTERNAL_TAMPERS(internal_tampers));

  while (LL_TAMP_IsActiveFlag_ITAMP(internal_tampers) == 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        /* New check to avoid false timeout detection in case of preemption */
        if (LL_TAMP_IsActiveFlag_ITAMP(internal_tampers) == 0U)
        {
          return HAL_TIMEOUT;
        }
        else
        {
          break;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup TAMP_Exported_Functions_Active
  * @{
  *
  * The active mode consists of a continuous comparison between a random signal from a tamper output and
  * the signal input from a tamper input. In case of mismatch between the two signals
  * a tamper event is then triggered to protect the device secrets from physical open-short attacks
  * for example.
  *
  * # Random output signal
  *
  * ## Pseudo random number generator
  *
  * A pseudo random number generator computes the signal output of a tamper level.
  * The seed can be configured by this pseudo random number generator is programmed
  * by using the @ref HAL_TAMP_ACTIVE_SetSeed function.
  *
  * The clock that drives the PRNG change is the RTCCLK passing through a prescaler, called CK_ATPRE.
  * This prescaler can be configured by calling @ref HAL_TAMP_ACTIVE_SetConfig and programming
  * the parameter hal_tamp_active_config_t::asynchronous_prescaler.
  *
  * Programming  hal_tamp_active_config_t::asynchronous_prescaler to @ref HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_2048
  * requires the asynchronous prescaler and synchronous prescaler of the RTC to be set
  * to 128 and a multiple of 16 respectively.
  *
  * Every ninth cycles of CK_ATPRE the value of the PRNG changes. The seed takes 184 APB clock to renew.
  * The application needs to wait for the seed to renew before entering a low power mode or switching
  * off the APB clock.
  *
  * ## Output change
  *
  * Another clock, CK_APER, drives the change in tamper output. CK_APER is generated from the same
  * source as the PRNG, but it is divided by two to the power of @ref hal_tamp_active_config_t::output_period.
  * @ref hal_tamp_active_config_t::output_period is configured by calling @ref HAL_TAMP_ACTIVE_SetConfig.
  *
  * Every two cycles the output value matches the last consumed value of the PRNG.
  * In between the two cycles, so after one cycle the value is the opposite.
  *
  * Depending on the number of outputs used the value of PRNG is consumed every :
  * * sixteen cycles with one output
  * * eight cycles with two outputs.
  * * four cycles with three or four outputs
  * * two cycles with five or more outputs.
  *
  * Choose the value of @ref hal_tamp_active_config_t::output_period according to the number
  * of outputs used and the fact that the PRNG changes only every ninth cycle of CK_ATPRE.
  *
  * # Comparison
  *
  * The comparison between the input and output signals is made every CK_ATPRE cycle. In
  * case a comparison mismatch occurs, a tamper event is triggered.
  *
  * By default the comparison is made between the same tamper input and output indexes. But
  * it is possible to use the same output for several tamper inputs.
  * This is configured by calling the @ref HAL_TAMP_ACTIVE_SetConfig and
  * @ref HAL_TAMP_ACTIVE_SetConfigTampers function.
  *
  * By calling @ref HAL_TAMP_ACTIVE_SetConfig and setting the
  * parameter hal_tamp_active_config_t::shared_output to @ref HAL_TAMP_ACTIVE_TAMPER_OUTPUT_SHARED, enables
  * the output sharing. To choose the output tamper for several input tampers
  * the user needs to call the function @ref HAL_TAMP_ACTIVE_SetConfigTampers by setting the parameter
  * @p tampers_input to the corresponding tampers input and
  * @ref hal_tamp_active_individual_config_t::tamper_output to the corresponding tamper output.
  *
  * The application can also apply a filter by calling @ref HAL_TAMP_ACTIVE_SetConfig and programming
  * @ref hal_tamp_active_config_t::filter with the value @ref  HAL_TAMP_ACTIVE_FILTER_ENABLE.
  * It makes a tamper event trigger only when two comparisons out of four consecutive comparisons are false.
  *
  * # Potential and confirmed mode.
  *
  * Each tamper can work in two modes regarding the device secrets erase. The confirmed mode means
  * that when a tamper event occurs the device secrets are automatically erased. The potential mode
  * does not erase all the device secrets when a tamper event occurs. Instead it blocks the read and write
  * access of the device secrets. The access is unblocked when the tamper event is cleared.
  *
  * To configure the erase mode call @ref HAL_TAMP_INTERNAL_SetConfigTampers and configure
  * the hal_tamp_internal_individual_config_t::erase_secrets parameter.
  *
  */

/**
  * @brief Configure the active tampers global parameters.
  * @param p_config Pointer to the active tampers global configuration instance.
  * @retval HAL_OK
  * @retval HAL_ERROR In STM32U575xx STM32U585xx the active tamper extension
  * is not present. The 2048 prescaler value can't be used.
  */
hal_status_t HAL_TAMP_ACTIVE_SetConfig(const hal_tamp_active_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_ACTIVE_OUTPUT_PERIOD(p_config->output_period));
  ASSERT_DBG_PARAM(IS_TAMP_ACTIVE_FILTER(p_config->filter));
  ASSERT_DBG_PARAM(IS_TAMP_ACTIVE_ASYNCHRONOUS_PRESCALER(p_config->asynchronous_prescaler));
  ASSERT_DBG_PARAM(IS_TAMP_ACTIVE_OUTPUT_SHARED(p_config->shared_output));


#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined(STM32U575xx) || defined(STM32U585xx)
  uint32_t revision_id = LL_DBGMCU_GetRevisionID();

  if ((revision_id == LL_DBGMCU_REV_ID_X)
      && (p_config->asynchronous_prescaler == HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_2048))
  {
    return HAL_ERROR;
  }
#endif /* defined(STM32U575xx) || defined(STM32U585xx) */

  LL_TAMP_ATAMP_SetConfig((uint32_t)p_config->filter, p_config->output_period,
                          (uint32_t)p_config->shared_output,
                          (uint32_t)p_config->asynchronous_prescaler);

  return HAL_OK;
}

/**
  * @brief Retrieve the active tampers global parameters.
  * @param p_config Pointer to the active tampers global configuration instance.
  */
void HAL_TAMP_ACTIVE_GetConfig(hal_tamp_active_config_t *p_config)
{
  uint32_t value_temp = LL_TAMP_ATAMP_GetConfig();

  ASSERT_DBG_PARAM(p_config != NULL);

  p_config->filter = (hal_tamp_active_filter_state_t) LL_TAMP_ACTIVE_GET_FILTER(value_temp);
  p_config->output_period = LL_TAMP_ACTIVE_GET_OUTPUT_PERIOD(value_temp);
  p_config->shared_output = (hal_tamp_active_output_shared_t) LL_TAMP_ACTIVE_GET_SHARING(value_temp);
  p_config->asynchronous_prescaler = (hal_tamp_active_prescaler_t) LL_TAMP_ACTIVE_GET_PRESCALER(value_temp);
}

/**
  * @brief Configure the active tampers individual parameters
  * @param tampers_input tampers input to be configured, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param p_config Pointer to the active tamper individual configuration instance.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_ACTIVE_SetConfigTampers(uint32_t tampers_input,
                                              const hal_tamp_active_individual_config_t *p_config)
{
  uint32_t tamper_index;
  uint32_t tamp_bool;
  uint32_t tamp_pos;
  uint32_t register_value = 0U;
  uint32_t bits_to_change = 0U;
  uint32_t tamper_output;
  uint32_t tamper_erase_secrets;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers_input));
  ASSERT_DBG_PARAM(IS_TAMP_ACTIVE_ERASE(p_config->erase_secrets));
  ASSERT_DBG_PARAM(IS_TAMP_ACTIVE_TAMPER_OUTPUT(p_config->tamper_output));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  tamper_output = (uint32_t)(p_config->tamper_output);
  tamper_erase_secrets = (uint32_t)(p_config->erase_secrets);

  if (LL_TAMP_ATAMP_IsEnabledOutputSharing() == 1U)
  {
    for (tamper_index = 0U; tamper_index < LL_TAMP_NUMBER_TAMPERS; tamper_index++)
    {
      tamp_bool = (tampers_input >> tamper_index) & 1U;

      tamp_pos = (tamper_index * 3U);

      register_value = register_value | ((tamp_bool * tamper_output) << tamp_pos);
      bits_to_change = bits_to_change | ((tamp_bool * 0x700U) << tamp_pos);

    }
    LL_TAMP_ATAMP_SetSharedOutputs(bits_to_change, register_value);
  }

  LL_TAMP_SetConfigTampers(tampers_input, 0, tamper_erase_secrets, 0);

  return HAL_OK;
}

/**
  * @brief Retrieve the active tamper individual configuration
  * @param tamper_input tampers input to be configured, can be one of the following values
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param p_config Pointer to the active tamper individual configuration instance.
  */
void HAL_TAMP_ACTIVE_GetConfigTamper(uint32_t tamper_input, hal_tamp_active_individual_config_t *p_config)
{
  uint32_t value_shared_output;
  uint32_t first_tamper_set_pos;
  uint32_t atamp_pos;

  uint32_t config_tamper = LL_TAMP_GetConfigTampers(tamper_input);
  uint32_t tamper_output;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tamper_input));

  p_config->erase_secrets = (hal_tamp_active_secrets_erase_t) LL_TAMP_GET_NOERASE(config_tamper);

  if (LL_TAMP_ATAMP_IsEnabledOutputSharing() == 1U)
  {
    value_shared_output = LL_TAMP_ATAMP_GetSharedOutputSelection();
    first_tamper_set_pos = (31U - (__CLZ(tamper_input)));
    if (first_tamper_set_pos <= (LL_TAMP_NUMBER_TAMPERS - 1U))
    {
      atamp_pos = (first_tamper_set_pos * 3U);
      tamper_output = ((value_shared_output >> atamp_pos) & 0x700U);
      p_config->tamper_output = (hal_tamp_active_output_tampers_t)tamper_output;
    }
  }
}

/**
  * @brief Start the active tampers.
  * @param tampers active tampers to activate, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param interruption enable the interruption, can be a combination of these values.
  *        @arg @ref HAL_TAMP_IT_NONE
  *        @arg @ref HAL_TAMP_IT_TAMPER_1
  *        @arg @ref HAL_TAMP_IT_TAMPER_2
  *        @arg @ref HAL_TAMP_IT_TAMPER_3
  *        @arg @ref HAL_TAMP_IT_TAMPER_4
  *        @arg @ref HAL_TAMP_IT_TAMPER_5
  *        @arg @ref HAL_TAMP_IT_TAMPER_6
  *        @arg @ref HAL_TAMP_IT_TAMPER_7
  *        @arg @ref HAL_TAMP_IT_TAMPER_8
  * @param p_seeds Pointer to the seed values. It must be a table with 4 elements.
  * @warning All needed active tampers must be started at the same time.
  * @retval HAL_ERROR If trying to start active tampers when they are already passive tampers and enabled.
                      or if trying to start active tampers when active tampers are already enabled.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_ACTIVE_Start(uint32_t tampers, uint32_t interruption, const uint32_t *p_seeds)
{
  ASSERT_DBG_PARAM(p_seeds != NULL);
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS_IT(interruption));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_seeds == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t active_tampers = LL_TAMP_ATAMP_GetActiveMode();
  uint32_t enabled_tampers = LL_TAMP_GetEnabled(LL_TAMP_ALL);

  /* Verify that there is no enabled active tampers */
  if ((active_tampers & enabled_tampers) != 0U)
  {
    return HAL_ERROR;
  }

  if ((((~active_tampers) & enabled_tampers) & tampers) != 0U)
  {
    return HAL_ERROR;
  }

  LL_TAMP_ATAMP_EnableActiveMode(tampers);

  LL_TAMP_Enable(tampers);
  LL_TAMP_EnableIT(interruption);

  for (uint32_t seed_index = 0U; seed_index < 4U; seed_index++)
  {
    LL_TAMP_ATAMP_WriteSeed(p_seeds[seed_index]);
  }

  return HAL_OK;
}

/**
  * @brief Stop the active tampers.
  * @param tampers active tampers to stop, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @warning All needed active tampers must be stopped at the same time.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_ACTIVE_Stop(uint32_t tampers)
{
  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));

  LL_TAMP_Disable(tampers);
  LL_TAMP_DisableIT(tampers);
  LL_TAMP_ClearFlag_TAMP(tampers);

  return HAL_OK;
}

/**
  * @brief Program a new seed for the pseudo-random number generator (PRNG)
  * @param p_seeds Pointer to the seeds values
  * @retval HAL_OK
  * @retval HAL_INVALID_PARAM when p_seeds is null.
  */
hal_status_t HAL_TAMP_ACTIVE_SetSeed(const uint32_t *p_seeds)
{

  ASSERT_DBG_PARAM(p_seeds != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_seeds == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  for (uint32_t seed_index = 0U; seed_index < 4U; seed_index++)
  {
    LL_TAMP_ATAMP_WriteSeed(p_seeds[seed_index]);
  }

  return HAL_OK;
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Read pseudo-random generator value.
  * @param p_prng Pointer to the pseudo-random generator value
  * @retval HAL_OK
  * @retval HAL_ERROR when read value is not correct
  */
hal_status_t HAL_TAMP_ACTIVE_GetPRNG(uint32_t *p_prng)
{
  /* Due to synchronization delays, PRNG must be read at least twice */
  __IO uint32_t prng_value_1 = LL_TAMP_ReadPRNG();
  __IO uint32_t prng_value_2 = LL_TAMP_ReadPRNG();

  /* Use temporary variables to store the volatile values */
  uint32_t temp_value_1 = prng_value_1;
  uint32_t temp_value_2 = prng_value_2;

  /* Read value is correct if it is equal to previous read value */
  if (temp_value_1 == temp_value_2)
  {
    *p_prng = prng_value_2;
  }
  else
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief Poll for a tamper event among the tampers given in @p tampers
  * @note  Call HAL_TAMP_ACTIVE_Stop to clear the pending tamper event.
  * @param tampers tampers to be checked, can be a combination of
  *        @arg @ref HAL_TAMP_TAMPER_1
  *        @arg @ref HAL_TAMP_TAMPER_2
  *        @arg @ref HAL_TAMP_TAMPER_3
  *        @arg @ref HAL_TAMP_TAMPER_4
  *        @arg @ref HAL_TAMP_TAMPER_5
  *        @arg @ref HAL_TAMP_TAMPER_6
  *        @arg @ref HAL_TAMP_TAMPER_7
  *        @arg @ref HAL_TAMP_TAMPER_8
  * @param timeout_ms Timeout duration
  * @retval HAL_OK
  * @retval HAL_TIMEOUT when reaching the timeout during polling.
  */
hal_status_t HAL_TAMP_ACTIVE_PollForEvent(uint32_t tampers, uint32_t timeout_ms)
{
  uint32_t tickstart = HAL_GetTick();

  ASSERT_DBG_PARAM(IS_TAMP_TAMPERS(tampers));

  while (LL_TAMP_IsActiveFlag_TAMP(tampers) == 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        /* New check to avoid false timeout detection in case of preemption */
        if (LL_TAMP_IsActiveFlag_TAMP(tampers) == 0U)
        {
          return HAL_TIMEOUT;
        }
        else
        {
          break;
        }
      }
    }
  }

  return HAL_OK;
}


/**
  * @}
  */

/** @addtogroup TAMP_Exported_Functions_IRQ
  * @brief TAMPER IRQ handler exported functions
  * @{
  * IRQ handler functions to manage the different tamper event interruptions.
  */

/**
  * @brief IRQ handler of the different tamper interruptions.
  */
void HAL_TAMP_IRQHandler(void)
{
  uint32_t flags = LL_TAMP_READ_REG(SR);
  uint32_t flags_tamper = flags & LL_TAMP_ALL;

  if (flags_tamper != 0U)
  {
    HAL_TAMP_TamperEventCallback(flags_tamper);
    LL_TAMP_ClearFlag_TAMP(flags_tamper);
  }
  else
  {
    uint32_t flags_internal_tamper = flags & LL_TAMP_ITAMP_ALL;
    if (flags_internal_tamper != 0U)
    {
      HAL_TAMP_InternalTamperEventCallback(flags_internal_tamper);
      LL_TAMP_ClearFlag_ITAMP(flags_internal_tamper);
    }
  }
}

/**
  * @brief IRQ handler of the external tampers interruptions.
  */
void HAL_TAMP_TamperIRQHandler(void)
{
  uint32_t flags_tamper = LL_TAMP_READ_REG(SR) & LL_TAMP_ALL;

  if (flags_tamper != 0U)
  {
    HAL_TAMP_TamperEventCallback(flags_tamper);
    LL_TAMP_ClearFlag_TAMP(flags_tamper);
  }
}

/**
  * @brief IRQ handler of the internal tampers interruptions.
  */
void HAL_TAMP_InternalTamperIRQHandler(void)
{
  uint32_t flags_internal_tamper = LL_TAMP_READ_REG(SR) & LL_TAMP_ITAMP_ALL;

  if (flags_internal_tamper != 0U)
  {
    HAL_TAMP_InternalTamperEventCallback(flags_internal_tamper);
    LL_TAMP_ClearFlag_ITAMP(flags_internal_tamper);
  }
}

/**
  * @}
  */

/** @addtogroup TAMP_Exported_Functions_Monotonic_Counters
  * @brief Monotonic counter exported functions.
  * @{
  *
  * The monotonic counter is a simple counter that the user can only increment
  * step by step. To increment the value and read the value the application must call
  * @ref HAL_TAMP_MONOTONIC_IncrementCounter and @ref HAL_TAMP_MONOTONIC_GetCounter.
  *
  */

/**
  * @brief Increment the value of the monotonic counter index
  * @param index monotonic counter index
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_MONOTONIC_IncrementCounter(hal_tamp_monotonic_counter_t index)
{
  ASSERT_DBG_PARAM(IS_TAMP_MONOTONIC_COUNTER(index));

  STM32_UNUSED(index);

  LL_TAMP_IncrementMonotonicCounter1();

  return HAL_OK;
}

/**
  * @brief Retrieves the value of the monotonic counter
  * @param index monotonic counter index.
  * @retval uint32_t Value of the monotonic counter.
  */
uint32_t HAL_TAMP_MONOTONIC_GetCounter(hal_tamp_monotonic_counter_t index)
{
  ASSERT_DBG_PARAM(IS_TAMP_MONOTONIC_COUNTER(index));
  STM32_UNUSED(index);

  return LL_TAMP_GetMonotonicCounter1();
}
/**
  * @}
  */

/** @addtogroup TAMP_Exported_Functions_Device_Secrets
  * @{
  * The device secrets consists of different resources of the microcontroller
  *
  * # Backup registers
  *
  * There are 32 backup registers.
  * The backup registers are registers that the application can write anything it wants by
  * calling @ref HAL_TAMP_WriteBackupRegisterValue .
  *
  * # Hardware boot key block
  *
  * The eight first backup registers can be used to store a boot hardware key (BHK) for the secure AES. For this
  * purpose, they must be defined in the third zone described above. First the user needs to program the third zone
  * accordingly by protecting them and then write the key in the eight first
  * registers.
  * To block the access to the hardware boot key, the application needs
  * to call @ref HAL_TAMP_EnableHardwareBootkeyBlock.
  * These events unblocked the access to the hardware boot key:
  * * a tamper event;
  * * calling @ref HAL_TAMP_EraseDeviceSecrets (BKERASE).
  *
  * In all cases the backup registers are also erased.
  *
  * # Device secrets access and erase.
  *
  * The application can enable and disable the access of the different device secrets by calling
  * @ref HAL_TAMP_UnblockDeviceSecretsAccess and @ref HAL_TAMP_BlockDeviceSecretsAccess respectively.
  * By default they can be accessed.
  *
  * The application can also manually erase the different device secrets by calling
  * the @ref HAL_TAMP_EraseDeviceSecrets function.
  *
  */

/**
  * @brief Program the value of the backup register given by the parameter @p backup_register_index.
  * @param backup_register_index Index of the backup register.
  * @param data_32bit Value to be programmed.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_WriteBackupRegisterValue(hal_tamp_backup_register_idx_t backup_register_index,
                                               uint32_t data_32bit)
{
  ASSERT_DBG_PARAM(IS_TAMP_BACKUP_REGISTER((uint32_t)backup_register_index));

  LL_TAMP_BKP_SetRegister((uint32_t)backup_register_index, data_32bit);

  return HAL_OK;
}

/**
  * @brief Retrieve the value of the backup register given by the parameter @p backup_register_index.
  * @param backup_register_index Index of the backup register.
  * @retval uint32_t Value of the backup register
  */
uint32_t HAL_TAMP_ReadBackupRegisterValue(hal_tamp_backup_register_idx_t backup_register_index)
{
  ASSERT_DBG_PARAM(IS_TAMP_BACKUP_REGISTER((uint32_t)backup_register_index));

  return LL_TAMP_BKP_GetRegister((uint32_t)backup_register_index);
}


/**
  * @brief Unblock access to the backup registers and device secrets.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_UnblockDeviceSecretsAccess(void)
{
  LL_TAMP_UnblockDeviceSecretsAccess();

  return HAL_OK;
}

/**
  * @brief Block access to the backup registers and devices secrets.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_BlockDeviceSecretsAccess(void)
{
  LL_TAMP_BlockDeviceSecretsAccess();

  return HAL_OK;
}

/**
  * @brief Check if the access to the devices secrets is blocked.
  * @retval hal_tamp_secrets_status_t Device secrets access status.
  */
hal_tamp_secrets_status_t HAL_TAMP_IsBlockedDeviceSecretsAccess(void)
{
  return (hal_tamp_secrets_status_t) LL_TAMP_IsBlockedDeviceSecretsAccess();
}

/**
  * @brief Erase the backup registers and device secrets.
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_EraseDeviceSecrets(void)
{
  LL_TAMP_EraseDeviceSecrets();
  return HAL_OK;
}

/**
  * @brief Enable the protection as device secrets of the resource given
  *        by the parameter @p resources.
  * @param resources Resources to be protected, can be a combination of
  *        @arg @ref HAL_TAMP_BACKUP_SRAM
  *        @arg @ref HAL_TAMP_RESOURCES_ALL
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_EnableResourceProtection(uint32_t resources)
{
  ASSERT_DBG_PARAM(IS_TAMP_RESOURCES(resources));

  LL_TAMP_EnableResourceProtection(resources);
  return HAL_OK;
}

/**
  * @brief Disable the protection as device secrets of the resource given
  *        by the parameter @p resources.
  * @param resources Resources to be protected, can be a combination of
  *        @arg @ref HAL_TAMP_BACKUP_SRAM
  *        @arg @ref HAL_TAMP_RESOURCES_ALL
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_DisableResourceProtection(uint32_t resources)
{
  ASSERT_DBG_PARAM(IS_TAMP_RESOURCES(resources));

  LL_TAMP_DisableResourceProtection(resources);
  return HAL_OK;
}

/**
  * @brief Check if the resources given by the parameter @p resources are protected as
  *        device secrets.
  * @param resources Resources to be protected, can be a combination of
  *        @arg @ref HAL_TAMP_BACKUP_SRAM
  *        @arg @ref HAL_TAMP_RESOURCES_ALL
  * @retval hal_tamp_protect_resources_status_t Resource protection status.
  */
hal_tamp_protect_resources_status_t HAL_TAMP_IsEnabledResourceProtection(uint32_t resources)
{
  ASSERT_DBG_PARAM(IS_TAMP_RESOURCES(resources));

  return (hal_tamp_protect_resources_status_t) LL_TAMP_IsEnabledResourceProtection(resources);
}

/**
  * @brief Blocks access to the eight first backup registers corresponding to the hardware boot key.
  * @note The eight first backup registers must be part of the third zone protection
  * @retval HAL_OK
  */
hal_status_t HAL_TAMP_EnableHardwareBootkeyBlock(void)
{
  LL_TAMP_EnableHardwareBootkeyBlock();
  return HAL_OK;
}

/**
  * @brief Check if the eight first backup registers corresponding to the hardware boot key are blocked.
  * @retval hal_tamp_hardware_bootkey_status_t Status of the hardware boot key access
  */
hal_tamp_hardware_bootkey_status_t HAL_TAMP_IsEnabledHardwareBootkeyBlock(void)
{
  return (hal_tamp_hardware_bootkey_status_t) LL_TAMP_IsEnabledHardwareBootkeyBlock();
}

/**
  * @}
  */

/** @addtogroup TAMP_Exported_Functions_Callback TAMP exported callback functions
  * @brief Callback exported functions
  * @{
  *
  * Callback functions that the user can overwrite for the different interruption:
  * * Internal tampers.
  * * External tampers.
  */

/**
  * @brief Internal tamper event callback
  */
__WEAK void HAL_TAMP_InternalTamperEventCallback(uint32_t internal_tampers)
{
  STM32_UNUSED(internal_tampers);
  /* NOTE: This function must not be modified in this file, when the callback is needed,
           the HAL_TAMP_InternalTamperEventCallback() can be implemented in the user file.
   */
}

/**
  * @brief External tamper event callback
  */
__WEAK void HAL_TAMP_TamperEventCallback(uint32_t tampers)
{
  STM32_UNUSED(tampers);
  /* NOTE: This function must not be modified in this file, when the callback is needed,
           the HAL_TAMP_TamperEventCallback() can be implemented in the user file.
   */
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_TAMP_MODULE */

/**
  * @}
  */

/**
  * @}
  */
