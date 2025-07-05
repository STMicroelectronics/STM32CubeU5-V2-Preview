/**
  ******************************************************************************
  * @file    stm32u5xx_hal_opamp.h
  * @brief   Header file of OPAMP HAL module.
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
#ifndef STM32U5XX_HAL_OPAMP_H
#define STM32U5XX_HAL_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

#if defined (OPAMP1) || defined (OPAMP2)

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_opamp.h"


/** @addtogroup OPAMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Types OPAMP Exported Types
  * @{
  */

/** @defgroup OPAMP_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief  HAL OPAMP instance
  */
typedef enum
{
#if defined (OPAMP1)
  HAL_OPAMP1 = (uint32_t)OPAMP1, /*!<  OPAMP1 */
#endif /* OPAMP1 */
#if defined (OPAMP2)
  HAL_OPAMP2 = (uint32_t)OPAMP2, /*!<  OPAMP2 */
#endif /* OPAMP2 */
} hal_opamp_t;

/**
  * @brief  HAL OPAMP state definition
  */
typedef enum
{
  HAL_OPAMP_STATE_RESET     = 0U,           /*!< OPAMP not yet initialized or is de-initialized */
  HAL_OPAMP_STATE_IDLE      = (1U << 31U),  /*!< OPAMP is initialized */
  HAL_OPAMP_STATE_CALIB     = (1U << 30U),  /*!< OPAMP is being calibrated */
  HAL_OPAMP_STATE_ACTIVE    = (1U << 29U),  /*!< OPAMP is active */
} hal_opamp_state_t;

/** @brief  OPAMP configuration mode
  */
typedef enum
{
  HAL_OPAMP_MODE_STANDALONE = LL_OPAMP_MODE_STANDALONE,  /*!< Standalone mode */
  HAL_OPAMP_MODE_PGA        = LL_OPAMP_MODE_PGA,         /*!< PGA mode        */
  HAL_OPAMP_MODE_FOLLOWER   = LL_OPAMP_MODE_FOLLOWER     /*!< Follower mode   */
} hal_opamp_config_mode_t;

/** @brief  OPAMP Non Inverting Input
  */
typedef enum
{
  HAL_OPAMP_NON_INVERTING_INPUT_GPIO = LL_OPAMP_INPUT_NONINVERT_IO0,      /*!< OPAMP non-inverting input connected
                                                                               to dedicated IO pin */
  HAL_OPAMP_NON_INVERTING_INPUT_DAC  = LL_OPAMP_INPUT_NONINVERT_DAC1_CH1  /*!< OPAMP non-inverting input connected
                                                                               internally to DAC channel */
} hal_opamp_non_inverting_input_t;

/** @brief  OPAMP Inverting Input
  */
typedef enum
{
  HAL_OPAMP_INVERTING_INPUT_GPIO_0  = LL_OPAMP_INPUT_INVERT_IO0,  /*!< OPAMP inverting input connected to GPIO */
  HAL_OPAMP_INVERTING_INPUT_GPIO_1  = LL_OPAMP_INPUT_INVERT_IO1,  /*!< OPAMP inverting input connected to dedicated
                                                                       low-leakage input pin available on some device
                                                                       packages */
  HAL_OPAMP_INVERTING_INPUT_NO_EXT_CON = LL_OPAMP_INPUT_INVERT_CONNECT_NO /*!< OPAMP inverting input not externally
                                                                               connected (for PGA and Follower mode) */
} hal_opamp_inverting_input_t;

/** @brief  OPAMP PGA Gain
  */
typedef enum
{
  HAL_OPAMP_PGA_GAIN_2              = LL_OPAMP_PGA_GAIN_2,  /*!< PGA gain = x  2 */
  HAL_OPAMP_PGA_GAIN_4              = LL_OPAMP_PGA_GAIN_4,  /*!< PGA gain = x  4 */
  HAL_OPAMP_PGA_GAIN_8              = LL_OPAMP_PGA_GAIN_8,  /*!< PGA gain = x  8 */
  HAL_OPAMP_PGA_GAIN_16             = LL_OPAMP_PGA_GAIN_16, /*!< PGA gain = x 16 */
} hal_opamp_pga_gain_t;

/** @brief  OPAMP power_mode
  */
typedef enum
{
  HAL_OPAMP_POWER_MODE_NORMAL = LL_OPAMP_POWER_MODE_NORMAL,  /*!< OPAMP in normal power mode */
  HAL_OPAMP_POWER_MODE_LOW    = LL_OPAMP_POWER_MODE_LOW      /*!< OPAMP in low power mode */
} hal_opamp_power_mode_t;

/** @brief  OPAMP speed_mode
  */
typedef enum
{
  HAL_OPAMP_SPEED_MODE_NORMAL = LL_OPAMP_SPEED_MODE_NORMAL,  /*!< OPAMP in normal speed mode */
  HAL_OPAMP_SPEED_MODE_HIGH   = LL_OPAMP_SPEED_MODE_HIGH     /*!< OPAMP in high speed mode */
} hal_opamp_speed_mode_t;


/** @brief  OPAMP trimming mode
  */
typedef enum
{
  HAL_OPAMP_TRIMMING_MODE_FACTORY = LL_OPAMP_TRIMMING_FACTORY,  /*!< Factory trimming mode */
  HAL_OPAMP_TRIMMING_MODE_USER    = LL_OPAMP_TRIMMING_USER      /*!< User trimming mode */
} hal_opamp_trimming_mode_t;

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Types_Group2 Handle Structure
  * @{
  */
typedef struct hal_opamp_handle_s hal_opamp_handle_t; /*!< OPAMP handle type definition */

/**
  * @brief   OPAMP handle,
  *          contains: OPAMP instance, states.
  */
struct hal_opamp_handle_s
{
  hal_opamp_t                 instance;      /*!< Peripheral instance */
  volatile hal_opamp_state_t  global_state;  /*!< OPAMP global_state */
#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
  hal_opamp_handle_t          *p_next_link;  /*!< Next peripheral instance, used as a circular linked list
                                                  of OPAMP handles to be calibrated in parallel */
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */
#if defined(USE_HAL_OPAMP_USER_DATA) && (USE_HAL_OPAMP_USER_DATA == 1)
  const void                  *p_user_data;  /*!< User data pointer */
#endif /* USE_HAL_OPAMP_USER_DATA */
};

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Types_Group4 Configuration Structure
  * @{
  */

/**
  * @brief  OPAMP configuration structure definition
  */
typedef struct
{
  hal_opamp_power_mode_t   power_mode;           /*!< The power mode: normal-power or low-power */
  hal_opamp_speed_mode_t   speed_mode;           /*!< The speed mode: normal-speed or high-speed */
  hal_opamp_config_mode_t  configuration_mode;   /*!< The OPAMP configuration mode: Standalone, Follower or PGA */
} hal_opamp_config_t;

/**
  * @brief  OPAMP input connection configuration structure definition
  */
typedef struct
{
  hal_opamp_inverting_input_t      inverting_input;      /*!< The inverting input in Standalone & PGA modes.
                                                             In Follower mode this parameter is Not Applicable. */
  hal_opamp_non_inverting_input_t  non_inverting_input;  /*!< The non inverting input of the opamp */
} hal_opamp_config_input_connection_t;

/**
  * @brief   OPAMP offset trimming pair structure definition
  */
typedef struct
{
  uint32_t  trim_offset_p;           /*!< The offset trimming value (PMOS) in low-power or normal-power mode.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 31,
                                          typical default value is 16 */
  uint32_t  trim_offset_n;           /*!< The offset trimming value (NMOS) in  low-power or normal-power mode.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 31,
                                          typical default value is 16 */
} hal_opamp_trimming_offset_pair_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMP_Exported_Functions
  * @{
  */

/** @addtogroup OPAMP_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
hal_status_t HAL_OPAMP_Init(hal_opamp_handle_t *hopamp, hal_opamp_t instance);
void HAL_OPAMP_DeInit(hal_opamp_handle_t *hopamp);

hal_status_t HAL_OPAMP_SetConfig(hal_opamp_handle_t *hopamp, const hal_opamp_config_t *p_config);
void HAL_OPAMP_GetConfig(const hal_opamp_handle_t *hopamp, hal_opamp_config_t *p_config);
void HAL_OPAMP_ResetConfig(hal_opamp_handle_t *hopamp);

/* Calibration functions  */
hal_status_t HAL_OPAMP_Calibrate(hal_opamp_handle_t *hopamp, hal_opamp_power_mode_t power_mode);

#if defined(USE_HAL_OPAMP_CALIBRATE_PARALLEL) && (USE_HAL_OPAMP_CALIBRATE_PARALLEL == 1)
hal_status_t HAL_OPAMP_CalibrateParallel(hal_opamp_handle_t *hopamp, hal_opamp_power_mode_t power_mode);
hal_status_t HAL_OPAMP_SetLinkNextHandle(hal_opamp_handle_t *hopamp_x, hal_opamp_handle_t *hopamp_y);
#endif /* USE_HAL_OPAMP_CALIBRATE_PARALLEL */

hal_opamp_trimming_mode_t HAL_OPAMP_GetTrimmingMode(const hal_opamp_handle_t *hopamp);

hal_status_t HAL_OPAMP_SetConfigTrimming(const hal_opamp_handle_t *hopamp,
                                         const hal_opamp_trimming_offset_pair_t *p_config,
                                         hal_opamp_power_mode_t power_mode);

void HAL_OPAMP_GetConfigTrimming(const hal_opamp_handle_t *hopamp,
                                 hal_opamp_trimming_offset_pair_t *p_config,
                                 hal_opamp_power_mode_t power_mode);

/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group2
  * @{
  */

/* I/O operation functions  ***************************************************/
hal_status_t HAL_OPAMP_Start(hal_opamp_handle_t *hopamp);
hal_status_t HAL_OPAMP_Stop(hal_opamp_handle_t *hopamp);

/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group3
  * @{
  */

/* Peripheral Control functions  **********************************************/
hal_status_t HAL_OPAMP_SetConfigInputConnection(const hal_opamp_handle_t *hopamp,
                                                const hal_opamp_config_input_connection_t *p_config);

void HAL_OPAMP_GetConfigInputConnection(const hal_opamp_handle_t *hopamp,
                                        hal_opamp_config_input_connection_t *p_config);

/* gain functions */
hal_status_t HAL_OPAMP_SetGain(const hal_opamp_handle_t *hopamp, hal_opamp_pga_gain_t gain);
hal_opamp_pga_gain_t HAL_OPAMP_GetGain(const hal_opamp_handle_t *hopamp);

/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group4
  * @{
  */

/* Peripheral State functions  ************************************************/
hal_opamp_state_t HAL_OPAMP_GetState(const hal_opamp_handle_t *hopamp);

/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group6
  * @{
  */
/* User Data API functions ***************************************/
#if defined(USE_HAL_OPAMP_USER_DATA) && (USE_HAL_OPAMP_USER_DATA == 1)
void HAL_OPAMP_SetUserData(hal_opamp_handle_t *hopamp, const void *p_user_data);
const void *HAL_OPAMP_GetUserData(const hal_opamp_handle_t *hopamp);
#endif /* USE_HAL_OPAMP_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* OPAMP1 || OPAMP2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_HAL_OPAMP_H */

