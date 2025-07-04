/**
  ******************************************************************************
  * @file    stm32u5xx_hal_tamp.h
  * @brief   Header file of TAMP HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5XX_HAL_TAMP_H
#define STM32U5XX_HAL_TAMP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_tamp.h"


/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup TAMP TAMP
  * @{
  */

/* Exported enumerations --------------------------------------------------------*/
/** @defgroup TAMP_Exported_Enums TAMP exported enumerations
  * @{
  */

/** @defgroup TAMP_Exported_Enums_Passive TAMP exported passive tamper enumerations
  * @{
  */

/**
  * @brief Passive tampers detection of edge level definition.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_TRIGGER_RISING  = LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL, /*!< Rising edge triggers a tamper detection  */
  HAL_TAMP_PASSIVE_TRIGGER_FALLING = LL_TAMP_ACTIVELEVEL_TAMP,           /*!< Falling edge triggers a tamper detection */
  HAL_TAMP_PASSIVE_TRIGGER_LOW     = LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL, /*!< Low level triggers a tamper detection */
  HAL_TAMP_PASSIVE_TRIGGER_HIGH    = LL_TAMP_ACTIVELEVEL_TAMP,           /*!< High level triggers a tamper detection */
} hal_tamp_passive_trigger_t;

/**
  * @brief Passive tampers erase mode definitions.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_SECRETS_ERASE    = LL_TAMP_ERASE_ACTIVATE_ALL, /*!< Tampers are in confirmed mode: device secrets
                                                                  are erased when a tamper is detected */
  HAL_TAMP_PASSIVE_SECRETS_NO_ERASE = LL_TAMP_NOERASE_TAMPER      /*!< Tampers are in potential mode: some device
                                                                   secrets are not erased when a tamper is detected */
} hal_tamp_passive_secrets_erase_t;


/**
  * @brief Passive tampers masked definition.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_UNMASKED = LL_TAMP_MASK_NONE,  /*!< Tampers are not masked and behave as expected */
  HAL_TAMP_PASSIVE_MASKED   = LL_TAMP_MASK_TAMPER /*!< Tampers are masked: a tamper detection does not trigger */
} hal_tamp_passive_mask_t;

/**
  * @brief Passive tampers pull-up (precharge) definition.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_DISABLE = LL_TAMP_PULL_UP_DISABLE, /*!< Disable tamper pull-up (precharge) */
  HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_ENABLE  = LL_TAMP_PULL_UP_ENABLE,  /*!< Enable tamper pull-up (precharge) */
} hal_tamp_passive_pull_up_precharge_state_t;

/**
  * @brief Passive tampers pull-up precharge duration definition.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_1_RTCCLK = LL_TAMP_DURATION_1RTCCLK, /*!< Tamper pins are precharged before
                                                                              sampling during one RTCCLK cycle*/
  HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_2_RTCCLK = LL_TAMP_DURATION_2RTCCLK, /*!< Tamper pins are precharged before
                                                                               sampling during two RTCCLK cycle */
  HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_4_RTCCLK = LL_TAMP_DURATION_4RTCCLK, /*!< Tamper pins are precharged before
                                                                               sampling during four RTCCLK cycle */
  HAL_TAMP_PASSIVE_PULL_UP_PRECHARGE_8_RTCCLK = LL_TAMP_DURATION_8RTCCLK  /*!< Tamper pins are precharged before
                                                                              sampling during eight RTCCLK cycle */
} hal_tamp_passive_pull_up_precharge_duration_t;

/**
  * @brief Passive tampers filter activation definition.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_FILTER_DISABLE   = LL_TAMP_FILTER_DISABLE,  /*!< Tamper filter is disabled */
  HAL_TAMP_PASSIVE_FILTER_2_SAMPLES = LL_TAMP_FILTER_2SAMPLES, /*!< Tamper is activated after two consecutive
                                                                   samples at the active level */
  HAL_TAMP_PASSIVE_FILTER_4_SAMPLES = LL_TAMP_FILTER_4SAMPLES, /*!< Tamper is activated after four consecutive
                                                                   samples at the active level */
  HAL_TAMP_PASSIVE_FILTER_8_SAMPLES = LL_TAMP_FILTER_8SAMPLES  /*!< Tamper is activated after eight consecutive
                                                                   samples at the active level */
} hal_tamp_passive_filter_t;

/**
  * @brief Passive tampers sampling frequency definitions.
  */
typedef enum
{
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_256   = LL_TAMP_SAMPLFREQDIV_256,   /*!< Each of the tampers inputs are sampled
                                                                        with a frequency =  RTCCLK / 256 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_512   = LL_TAMP_SAMPLFREQDIV_512,   /*!< Each of the tampers inputs are sampled
                                                                        with a frequency =  RTCCLK / 512 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_1024  = LL_TAMP_SAMPLFREQDIV_1024,  /*!< Each of the tampers inputs are sampled
                                                                          with a frequency =  RTCCLK / 1024 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_2048  = LL_TAMP_SAMPLFREQDIV_2048,  /*!< Each of the tampers inputs are sampled
                                                                          with a frequency =  RTCCLK / 2048 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_4096  = LL_TAMP_SAMPLFREQDIV_4096,  /*!< Each of the tampers inputs are sampled
                                                                          with a frequency =  RTCCLK / 4096 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_8192  = LL_TAMP_SAMPLFREQDIV_8192,  /*!< Each of the tampers inputs are sampled
                                                                          with a frequency =  RTCCLK / 8192 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_16384 = LL_TAMP_SAMPLFREQDIV_16384, /*!< Each of the tampers inputs are sampled
                                                                            with a frequency =  RTCCLK / 16384 */
  HAL_TAMP_PASSIVE_SAMPLE_FREQ_DIV_32768 = LL_TAMP_SAMPLFREQDIV_32768, /*!< Each of the tampers inputs are sampled
                                                                            with a frequency =  RTCCLK / 32768 */
} hal_tamp_passive_sample_frequency_t;

/**
  * @}
  */

/** @defgroup TAMP_Exported_Enums_Internal TAMP exported internal tampers enumerations
  * @{
  */

/**
  * @brief Internal tampers erase mode definitions.
  */
typedef enum
{
  HAL_TAMP_INTERNAL_SECRETS_ERASE    = LL_TAMP_ITAMP_ERASE_ACTIVE_ALL, /*!< Tampers are in confirmed mode: device
                                                                         secrets are erased when a tamper is detected */
  HAL_TAMP_INTERNAL_SECRETS_NO_ERASE = LL_TAMP_ITAMP_NOERASE_TAMPER    /*!< Tampers are in potential mode: some device
                                                                          secrets are not erased when
                                                                          a tamper is detected */
} hal_tamp_internal_secrets_erase_t;

/**
  * @}
  */

/** @defgroup TAMP_Exported_Enums_Active TAMP exported active tampers enumerations
  * @{
  */

/**
  * @brief Active tampers filter definitions.
  */
typedef enum
{
  HAL_TAMP_ACTIVE_FILTER_DISABLE = LL_TAMP_ATAMP_FILTERING_DISABLE,  /*!< Active filter is disable */
  HAL_TAMP_ACTIVE_FILTER_ENABLE  = LL_TAMP_ATAMP_FILTERING_ENABLE,   /*!< Active filter is enable, a tamper event is
                                                                         detected when 2 comparison mismatches occur
                                                                         out of 4 consecutive samples.*/
} hal_tamp_active_filter_state_t;

/**
  * @brief Active tampers asynchronous prescaler clock selection definitions.
  */
typedef enum
{
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK         = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK,       /*!< The clock is set to
                                                                                       RTCCLK */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_2   = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2,     /*!< The clock is set to
                                                                                       RTCCLK/2 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_4   = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4,     /*!< The clock is set to
                                                                                       RTCCLK/4 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_8   = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8,     /*!< The clock is set to
                                                                                       RTCCLK/8 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_16  = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16,    /*!< The clock is set to
                                                                                       RTCCLK/16 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_32  = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32,    /*!< The clock is set to
                                                                                       RTCCLK/32 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_64  = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_64,    /*!< The clock is set to
                                                                                       RTCCLK/64 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_128 = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_128,   /*!< The clock is set to
                                                                                       RTCCLK/128 */
  HAL_TAMP_ACTIVE_PRESCALER_RTCCLK_DIV_2048 = LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2048 /*!< The clock is set to
                                                                                       RTCCLK/2048 */
} hal_tamp_active_prescaler_t;

/**
  * @brief Active tamper erase mode definitions.
  */
typedef enum
{
  HAL_TAMP_ACTIVE_SECRETS_ERASE    = LL_TAMP_ERASE_ACTIVATE_ALL, /*!< Active tampers are in confirmed mode: \
                                                                   device secrets are erased when \
                                                                   a tamper is detected */
  HAL_TAMP_ACTIVE_SECRETS_NO_ERASE = LL_TAMP_NOERASE_TAMPER      /*!< Active tampers are in potential mode: \
                                                                   device secrets are not erased when \
                                                                   a tamper is detected */
} hal_tamp_active_secrets_erase_t;


/**
  * @brief Active tamper output shared definitions.
  */
typedef enum
{
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_NOT_SHARED = LL_TAMP_ATAMP_SHARING_DISABLE,     /*!< Active tampers \
                                                                                 outputs are not shared */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_SHARED     = LL_TAMP_ATAMP_SHARING_ENABLE       /*!< Active tampers \
                                                                                 outputs are shared*/
} hal_tamp_active_output_shared_t;

/**
  * @brief Output tampers definitions.
  */
typedef enum
{
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_1 = LL_TAMP_ATAMP1IN_ATAMP1OUT, /*!< Active tamper output 1 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_2 = LL_TAMP_ATAMP1IN_ATAMP2OUT, /*!< Active tamper output 2 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_3 = LL_TAMP_ATAMP1IN_ATAMP3OUT, /*!< Active tamper output 3 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_4 = LL_TAMP_ATAMP1IN_ATAMP4OUT, /*!< Active tamper output 4 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_5 = LL_TAMP_ATAMP1IN_ATAMP5OUT, /*!< Active tamper output 5 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_6 = LL_TAMP_ATAMP1IN_ATAMP6OUT, /*!< Active tamper output 6 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_7 = LL_TAMP_ATAMP1IN_ATAMP7OUT, /*!< Active tamper output 7 */
  HAL_TAMP_ACTIVE_TAMPER_OUTPUT_8 = LL_TAMP_ATAMP1IN_ATAMP8OUT  /*!< Active tamper output 8 */
} hal_tamp_active_output_tampers_t;
/**
  * @}
  */

/** @defgroup TAMP_Exported_Enums_Monotonic_Counters TAMP exported monotonic counters enumerations
  * @{
  */

/**
  * @brief Monotonic counter definitions.
  */
typedef enum
{
  HAL_TAMP_MONOTONIC_1 = 0U, /*!< Monotonic counter number 1 */
} hal_tamp_monotonic_counter_t;

/**
  * @}
  */

/** @defgroup TAMP_Exported_Enums_Device_Secrets TAMP exported secrets enumerations
  * @{
  */

/**
  * @brief Device secrets access status definitions.
  */
typedef enum
{
  HAL_TAMP_SECRETS_ACCESS_UNBLOCKED = 0U, /*!< Device secrets can be accessed if no tamper flag is set. */
  HAL_TAMP_SECRETS_ACCESS_BLOCKED   = 1U  /*!< Device secrets cannot be accessed.*/
} hal_tamp_secrets_status_t;

/**
  * @brief Resource protection status definitions.
  */
typedef enum
{
  HAL_TAMP_PROTECT_RESOURCES_DISABLED = 0U, /*!< Resources protection is disabled. */
  HAL_TAMP_PROTECT_RESOURCES_ENABLED  = 1U  /*!< Resources protections is enabled. */
} hal_tamp_protect_resources_status_t;
/**
  * @}
  */

/** @defgroup TAMP_Exported_Enums_BHK TAMP exported hardware boot key enumerations
  * @{
  */

/**
  * @brief Hardware boot key lock status definitions.
  */
typedef enum
{
  HAL_TAMP_HW_BOOTKEY_ACCESS_UNBLOCKED = 0U, /*!< The eight first backup registers can be accessed. */
  HAL_TAMP_HW_BOOTKEY_ACCESS_BLOCKED   = 1U  /*!< The eight first backup registers cannot be accessed. */
} hal_tamp_hardware_bootkey_status_t;
/**
  * @}
  */

/**
  * @}
  */


/* Exported Unions ----------------------------------------------------------*/

/* Exported defines ----------------------------------------------------------*/

/** @defgroup TAMP_Exported_Defines TAMP exported defines
  * @{
  */

/** @defgroup TAMP_Exported_Defines_Tamper_OUTPUT_PERIOD TAMP tamper defines.
  * @{
  */
#define HAL_TAMP_OUTPUT_PERIOD   LL_TAMP_OUTPUT_PERIOD  /*!< Active tamper output period. */
/**
  * @}
  */

/** @defgroup TAMP_Exported_Defines_Tamper TAMP tamper defines for passive and active.
  * @{
  */
#define HAL_TAMP_TAMPER_1    LL_TAMP_1   /*!< Tamper input 1 */
#define HAL_TAMP_TAMPER_2    LL_TAMP_2   /*!< Tamper input 2 */
#define HAL_TAMP_TAMPER_3    LL_TAMP_3   /*!< Tamper input 3 */
#define HAL_TAMP_TAMPER_4    LL_TAMP_4   /*!< Tamper input 4 */
#define HAL_TAMP_TAMPER_5    LL_TAMP_5   /*!< Tamper input 5 */
#define HAL_TAMP_TAMPER_6    LL_TAMP_6   /*!< Tamper input 6 */
#define HAL_TAMP_TAMPER_7    LL_TAMP_7   /*!< Tamper input 7 */
#define HAL_TAMP_TAMPER_8    LL_TAMP_8   /*!< Tamper input 8 */
#define HAL_TAMP_TAMPER_ALL  LL_TAMP_ALL /*!< All tampers inputs */
/**
  * @}
  */

/** @defgroup TAMP_Exported_Defines_Internal_Tamper TAMP internal tamper defines.
  * @{
  */
#define HAL_TAMP_INTERNAL_TAMPER_1   LL_TAMP_ITAMP1    /*!< Internal tamper input 1 */
#define HAL_TAMP_INTERNAL_TAMPER_2   LL_TAMP_ITAMP2    /*!< Internal tamper input 2 */
#define HAL_TAMP_INTERNAL_TAMPER_3   LL_TAMP_ITAMP3    /*!< Internal tamper input 3 */
#define HAL_TAMP_INTERNAL_TAMPER_5   LL_TAMP_ITAMP5    /*!< Internal tamper input 5 */
#define HAL_TAMP_INTERNAL_TAMPER_6   LL_TAMP_ITAMP6    /*!< Internal tamper input 6 */
#define HAL_TAMP_INTERNAL_TAMPER_7   LL_TAMP_ITAMP7    /*!< Internal tamper input 7 */
#define HAL_TAMP_INTERNAL_TAMPER_8   LL_TAMP_ITAMP8    /*!< Internal tamper input 8 */
#define HAL_TAMP_INTERNAL_TAMPER_9   LL_TAMP_ITAMP9    /*!< Internal tamper input 9 */
#define HAL_TAMP_INTERNAL_TAMPER_11  LL_TAMP_ITAMP11   /*!< Internal tamper input 11 */
#define HAL_TAMP_INTERNAL_TAMPER_12  LL_TAMP_ITAMP12   /*!< Internal tamper input 12 */
#define HAL_TAMP_INTERNAL_TAMPER_13  LL_TAMP_ITAMP13   /*!< Internal tamper input 13 */
#define HAL_TAMP_INTERNAL_ALL        LL_TAMP_ITAMP_ALL /*!< All internal tampers inputs */
/**
  * @}
  */

/** @defgroup TAMP_Exported_Defines_Resources TAMP resources defines
  * @{
  */
#define HAL_TAMP_BACKUP_SRAM      LL_TAMP_RESOURCE_0      /*!< Backup SRAM */
#define HAL_TAMP_RESOURCES_ALL    LL_TAMP_RESOURCES_ALL
/**
  * @}
  */

/** @defgroup TAMP_Exported_Defines_Tamper_Interruption TAMP tamper interruption defines
  * @{
  */
#define HAL_TAMP_IT_NONE       LL_TAMP_IT_NONE       /*!< All external tampers interruptions are disabled */
#define HAL_TAMP_IT_TAMPER_1   LL_TAMP_IT_TAMPER_1   /*!< External tamper 1 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_2   LL_TAMP_IT_TAMPER_2   /*!< External tamper 2 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_3   LL_TAMP_IT_TAMPER_3   /*!< External tamper 3 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_4   LL_TAMP_IT_TAMPER_4   /*!< External tamper 4 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_5   LL_TAMP_IT_TAMPER_5   /*!< External tamper 5 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_6   LL_TAMP_IT_TAMPER_6   /*!< External tamper 6 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_7   LL_TAMP_IT_TAMPER_7   /*!< External tamper 7 interruption is enabled */
#define HAL_TAMP_IT_TAMPER_8   LL_TAMP_IT_TAMPER_8   /*!< External tamper 8 interruption is enabled */
#define HAL_TAMP_IT_ALL        LL_TAMP_IT_ALL        /*!< All external tampers interruptions are enabled */
/**
  * @}
  */

/** @defgroup TAMP_Exported_Defines_Internal_Tamper_Interruption TAMP internal tamper interruption defines
  * @{
  */
#define HAL_TAMP_INTERNAL_IT_NONE       LL_TAMP_INTERNAL_IT_NONE       /*!< All internal tampers interruptions are disabled */
#define HAL_TAMP_INTERNAL_IT_TAMPER_1   LL_TAMP_INTERNAL_IT_TAMPER_1  /*!< Internal tamper 1 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_2   LL_TAMP_INTERNAL_IT_TAMPER_2  /*!< Internal tamper 2 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_3   LL_TAMP_INTERNAL_IT_TAMPER_3  /*!< Internal tamper 3 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_5   LL_TAMP_INTERNAL_IT_TAMPER_5  /*!< Internal tamper 5 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_6   LL_TAMP_INTERNAL_IT_TAMPER_6  /*!< Internal tamper 6 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_7   LL_TAMP_INTERNAL_IT_TAMPER_7  /*!< Internal tamper 7 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_8   LL_TAMP_INTERNAL_IT_TAMPER_8  /*!< Internal tamper 8 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_9   LL_TAMP_INTERNAL_IT_TAMPER_9  /*!< Internal tamper 9 interruption is enabled  */
#define HAL_TAMP_INTERNAL_IT_TAMPER_11  LL_TAMP_INTERNAL_IT_TAMPER_11 /*!< Internal tamper 11 interruption is enabled */
#define HAL_TAMP_INTERNAL_IT_TAMPER_12  LL_TAMP_INTERNAL_IT_TAMPER_12 /*!< Internal tamper 12 interruption is enabled */
#define HAL_TAMP_INTERNAL_IT_TAMPER_13  LL_TAMP_INTERNAL_IT_TAMPER_13 /*!< Internal tamper 13 interruption is enabled */
#define HAL_TAMP_INTERNAL_IT_ALL        LL_TAMP_INTERNAL_IT_ALL        /*!< All internal tampers interruptions are enabled */
/**
  * @}
  */


/**
  * @}
  */


/* Exported structures --------------------------------------------------------*/

/** @defgroup TAMP_Exported_Structures TAMP Exported structures
  * @{
  */

/** @defgroup TAMP_Exported_Structures_Passive TAMP passive tampers exported structures
  * @{
  */

/**
  * @brief Passive tamper configuration.
  */
typedef struct
{
  hal_tamp_passive_pull_up_precharge_state_t precharge; /*!< Specifies the activation of the pull-up (precharge).*/
  hal_tamp_passive_pull_up_precharge_duration_t precharge_duration; /*!< Specifies the duration of \
                                                                        the precharge in RTCCLK units. */
  hal_tamp_passive_filter_t type_activation; /*!< Specifies the activation type of the tamper.*/
  hal_tamp_passive_sample_frequency_t sample_frequency; /*!< Specifies the tamper sample frequency.*/
} hal_tamp_passive_config_t;

/**
  * @brief Passive tamper individual configuration.
  */
typedef struct
{
  hal_tamp_passive_trigger_t trigger; /*!< Specifies the trigger type for edge and \
                                                        level tamper detection. */
  hal_tamp_passive_secrets_erase_t erase_secrets; /*!< Specifies the tamper erase mode. */
  hal_tamp_passive_mask_t masked; /*!< Specifies that the tamper is masked or not.*/

} hal_tamp_passive_individual_config_t;

/**
  * @}
  */

/** @defgroup TAMP_Exported_Structures_Internal TAMP internal tampers exported structures
  * @{
  */

/**
  * @brief Internal tamper individual configuration.
  */
typedef struct
{
  hal_tamp_internal_secrets_erase_t erase_secrets; /*!< Specifies the internal tamper erase mode.*/
} hal_tamp_internal_individual_config_t;

/**
  * @}
  */

/** @defgroup TAMP_Exported_Structures_Active TAMP active tampers exported structures
  * @{
  */

/**
  * @brief Active tamper configuration.
  */
typedef struct
{
  uint32_t output_period; /*!< Specifies the period when the output signals changes. */
  hal_tamp_active_filter_state_t filter; /*!< Specifies the active tamper filter activation. */
  hal_tamp_active_prescaler_t asynchronous_prescaler; /*!< Specifies the asynchronous prescaler clock selection. */
  hal_tamp_active_output_shared_t shared_output; /*!< Specifies that tampers outputs and inputs are shared.*/
}  hal_tamp_active_config_t;

/**
  * @brief Active tamper individual configuration.
  */
typedef struct
{
  hal_tamp_active_secrets_erase_t erase_secrets; /*!< Specifies the active tamper erase mode.*/
  hal_tamp_active_output_tampers_t tamper_output; /*!< Specifies the output tampers used.*/
} hal_tamp_active_individual_config_t;

/**
  * @}
  */

/**
  * @brief Backup registers enumeration definition
  */
typedef enum
{
  HAL_TAMP_BACKUP_REG_0 = LL_TAMP_BKP_DR0, /*!< TAMP Backup register 0 */
  HAL_TAMP_BACKUP_REG_1 = LL_TAMP_BKP_DR1, /*!< TAMP Backup register 1 */
  HAL_TAMP_BACKUP_REG_2 = LL_TAMP_BKP_DR2, /*!< TAMP Backup register 2 */
  HAL_TAMP_BACKUP_REG_3 = LL_TAMP_BKP_DR3, /*!< TAMP Backup register 3 */
  HAL_TAMP_BACKUP_REG_4 = LL_TAMP_BKP_DR4, /*!< TAMP Backup register 4 */
  HAL_TAMP_BACKUP_REG_5 = LL_TAMP_BKP_DR5, /*!< TAMP Backup register 5 */
  HAL_TAMP_BACKUP_REG_6 = LL_TAMP_BKP_DR6, /*!< TAMP Backup register 6 */
  HAL_TAMP_BACKUP_REG_7 = LL_TAMP_BKP_DR7, /*!< TAMP Backup register 7 */
  HAL_TAMP_BACKUP_REG_8 = LL_TAMP_BKP_DR8, /*!< TAMP Backup register 8  */
  HAL_TAMP_BACKUP_REG_9 = LL_TAMP_BKP_DR9, /*!< TAMP Backup register 9  */
  HAL_TAMP_BACKUP_REG_10 = LL_TAMP_BKP_DR10, /*!< TAMP Backup register 10 */
  HAL_TAMP_BACKUP_REG_11 = LL_TAMP_BKP_DR11, /*!< TAMP Backup register 11 */
  HAL_TAMP_BACKUP_REG_12 = LL_TAMP_BKP_DR12, /*!< TAMP Backup register 12 */
  HAL_TAMP_BACKUP_REG_13 = LL_TAMP_BKP_DR13, /*!< TAMP Backup register 13 */
  HAL_TAMP_BACKUP_REG_14 = LL_TAMP_BKP_DR14, /*!< TAMP Backup register 14 */
  HAL_TAMP_BACKUP_REG_15 = LL_TAMP_BKP_DR15, /*!< TAMP Backup register 15 */
  HAL_TAMP_BACKUP_REG_16 = LL_TAMP_BKP_DR16, /*!< TAMP Backup register 16 */
  HAL_TAMP_BACKUP_REG_17 = LL_TAMP_BKP_DR17, /*!< TAMP Backup register 17 */
  HAL_TAMP_BACKUP_REG_18 = LL_TAMP_BKP_DR18, /*!< TAMP Backup register 18 */
  HAL_TAMP_BACKUP_REG_19 = LL_TAMP_BKP_DR19, /*!< TAMP Backup register 19 */
  HAL_TAMP_BACKUP_REG_20 = LL_TAMP_BKP_DR20, /*!< TAMP Backup register 20 */
  HAL_TAMP_BACKUP_REG_21 = LL_TAMP_BKP_DR21, /*!< TAMP Backup register 21 */
  HAL_TAMP_BACKUP_REG_22 = LL_TAMP_BKP_DR22, /*!< TAMP Backup register 22 */
  HAL_TAMP_BACKUP_REG_23 = LL_TAMP_BKP_DR23, /*!< TAMP Backup register 23 */
  HAL_TAMP_BACKUP_REG_24 = LL_TAMP_BKP_DR24, /*!< TAMP Backup register 24 */
  HAL_TAMP_BACKUP_REG_25 = LL_TAMP_BKP_DR25, /*!< TAMP Backup register 25 */
  HAL_TAMP_BACKUP_REG_26 = LL_TAMP_BKP_DR26, /*!< TAMP Backup register 26 */
  HAL_TAMP_BACKUP_REG_27 = LL_TAMP_BKP_DR27, /*!< TAMP Backup register 27 */
  HAL_TAMP_BACKUP_REG_28 = LL_TAMP_BKP_DR28, /*!< TAMP Backup register 28 */
  HAL_TAMP_BACKUP_REG_29 = LL_TAMP_BKP_DR29, /*!< TAMP Backup register 29 */
  HAL_TAMP_BACKUP_REG_30 = LL_TAMP_BKP_DR30, /*!< TAMP Backup register 30 */
  HAL_TAMP_BACKUP_REG_31 = LL_TAMP_BKP_DR31, /*!< TAMP Backup register 31 */
} hal_tamp_backup_register_idx_t;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TAMP_Exported_Functions TAMP Exported Functions
  * @{
  */

/** @defgroup TAMP_Exported_Functions_Passive TAMP exported passive tamper mode functions
  * @{
  */

hal_status_t HAL_TAMP_PASSIVE_SetConfig(const hal_tamp_passive_config_t *p_config);
void HAL_TAMP_PASSIVE_GetConfig(hal_tamp_passive_config_t *p_config);

hal_status_t HAL_TAMP_PASSIVE_SetConfigTampers(uint32_t tampers, const hal_tamp_passive_individual_config_t *p_config);
void HAL_TAMP_PASSIVE_GetConfigTamper(uint32_t tamper, hal_tamp_passive_individual_config_t *p_config);

hal_status_t HAL_TAMP_PASSIVE_Start(uint32_t tampers, uint32_t interruption);
hal_status_t HAL_TAMP_PASSIVE_Stop(uint32_t tampers);

hal_status_t HAL_TAMP_PASSIVE_PollForEvent(uint32_t tampers, uint32_t timeout_ms);

/**
  * @}
  */

/** @defgroup TAMP_Exported_Functions_Internal TAMP exported internal tamper mode functions
  * @{
  */

hal_status_t HAL_TAMP_INTERNAL_SetConfigTampers(uint32_t internal_tampers,
                                                const hal_tamp_internal_individual_config_t *p_config);
void HAL_TAMP_INTERNAL_GetConfigTamper(uint32_t internal_tamper, hal_tamp_internal_individual_config_t *p_config);

hal_status_t HAL_TAMP_INTERNAL_Start(uint32_t internal_tampers, uint32_t interruption);
hal_status_t HAL_TAMP_INTERNAL_Stop(uint32_t internal_tampers);

hal_status_t HAL_TAMP_INTERNAL_PollForEvent(uint32_t internal_tampers, uint32_t timeout_ms);

/**
  * @}
  */

/** @defgroup TAMP_Exported_Functions_Active exported active tamper mode functions
  * @{
  */

hal_status_t HAL_TAMP_ACTIVE_SetConfig(const hal_tamp_active_config_t *p_config);
void HAL_TAMP_ACTIVE_GetConfig(hal_tamp_active_config_t *p_config);

hal_status_t HAL_TAMP_ACTIVE_SetConfigTampers(uint32_t tampers_input,
                                              const hal_tamp_active_individual_config_t *p_config);
void HAL_TAMP_ACTIVE_GetConfigTamper(uint32_t tamper_input,
                                     hal_tamp_active_individual_config_t *p_config);

hal_status_t HAL_TAMP_ACTIVE_Start(uint32_t tampers, uint32_t interruption, const uint32_t *p_seeds);
hal_status_t HAL_TAMP_ACTIVE_Stop(uint32_t tampers);

hal_status_t HAL_TAMP_ACTIVE_SetSeed(const uint32_t *p_seeds);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
hal_status_t  HAL_TAMP_ACTIVE_GetPRNG(uint32_t *p_prng);
#endif /* __ARM_FEATURE_CMSE */

hal_status_t HAL_TAMP_ACTIVE_PollForEvent(uint32_t tampers, uint32_t timeout_ms);

/**
  * @}
  */

/** @defgroup TAMP_Exported_Functions_IRQ TAMP exported IRQ functions
  * @{
  */

void HAL_TAMP_IRQHandler(void);
void HAL_TAMP_InternalTamperIRQHandler(void);
void HAL_TAMP_TamperIRQHandler(void);

/**
  * @}
  */

/** @defgroup TAMP_Exported_Functions_Callback TAMP exported callback functions
  * @{
  */

void HAL_TAMP_InternalTamperEventCallback(uint32_t internal_tampers);
void HAL_TAMP_TamperEventCallback(uint32_t tampers);

/**
  * @}
  */

/** @defgroup TAMP_Exported_Functions_Monotonic_Counters TAMP exported monotonic counter functions
  * @{
  */
hal_status_t HAL_TAMP_MONOTONIC_IncrementCounter(hal_tamp_monotonic_counter_t index);
uint32_t HAL_TAMP_MONOTONIC_GetCounter(hal_tamp_monotonic_counter_t index);
/**
  * @}
  */

/** @defgroup TAMP_Exported_Functions_Device_Secrets TAMP exported device secrets functions
  * @{
  */

hal_status_t HAL_TAMP_WriteBackupRegisterValue(hal_tamp_backup_register_idx_t backup_register_index,
                                               uint32_t data_32bit);
uint32_t HAL_TAMP_ReadBackupRegisterValue(hal_tamp_backup_register_idx_t backup_register_index);

hal_status_t HAL_TAMP_UnblockDeviceSecretsAccess(void);
hal_status_t HAL_TAMP_BlockDeviceSecretsAccess(void);
hal_tamp_secrets_status_t HAL_TAMP_IsBlockedDeviceSecretsAccess(void);
hal_status_t HAL_TAMP_EraseDeviceSecrets(void);

hal_status_t HAL_TAMP_EnableResourceProtection(uint32_t resources);
hal_status_t HAL_TAMP_DisableResourceProtection(uint32_t resources);
hal_tamp_protect_resources_status_t HAL_TAMP_IsEnabledResourceProtection(uint32_t resources);

hal_status_t HAL_TAMP_EnableHardwareBootkeyBlock(void);
hal_tamp_hardware_bootkey_status_t HAL_TAMP_IsEnabledHardwareBootkeyBlock(void);

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

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* STM32U5XX_HAL_TAMP_H */
