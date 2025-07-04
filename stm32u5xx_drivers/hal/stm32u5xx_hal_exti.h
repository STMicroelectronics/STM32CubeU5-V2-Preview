/**
  *********************************************************************************************************************
  * @file    stm32u5xx_hal_exti.h
  * @brief   Header file of EXTI HAL module.
  *********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *********************************************************************************************************************
  */

/* Define to prevent recursive inclusion ----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_EXTI_H
#define STM32U5XX_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_exti.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @{
  */

/* Exported types ---------------------------------------------------------------------------------------------------*/
/** @defgroup  EXTI_Exported_Types EXTI Exported Types
  * @{
  */

/*! EXTI Global State Machine */
typedef enum
{
  HAL_EXTI_STATE_RESET                   =  0U, /*!< Reset state */
  HAL_EXTI_STATE_INIT                    = (1U << 31U), /*!< EXTI initialized but not yet configured */
  HAL_EXTI_STATE_IDLE                    = (1U << 30U), /*!< EXTI initialized and configured */
  HAL_EXTI_STATE_ACTIVE                  = (1U << 29U)  /*!< EXTI initialized, configured and activated */
} hal_exti_state_t;

/*! EXTI Lines */
typedef enum
{
  HAL_EXTI_LINE_0                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x00U), /*!< EXTI Line 0 */
  HAL_EXTI_LINE_1                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x01U), /*!< EXTI Line 1 */
  HAL_EXTI_LINE_2                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x02U), /*!< EXTI Line 2 */
  HAL_EXTI_LINE_3                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x03U), /*!< EXTI Line 3 */
  HAL_EXTI_LINE_4                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x04U), /*!< EXTI Line 4 */
  HAL_EXTI_LINE_5                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x05U), /*!< EXTI Line 5 */
  HAL_EXTI_LINE_6                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x06U), /*!< EXTI Line 6 */
  HAL_EXTI_LINE_7                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x07U), /*!< EXTI Line 7 */
  HAL_EXTI_LINE_8                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x08U), /*!< EXTI Line 8 */
  HAL_EXTI_LINE_9                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x09U), /*!< EXTI Line 9 */
  HAL_EXTI_LINE_10                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x0AU), /*!< EXTI Line 10 */
  HAL_EXTI_LINE_11                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x0BU), /*!< EXTI Line 11 */
  HAL_EXTI_LINE_12                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0CU), /*!< EXTI Line 12 */
  HAL_EXTI_LINE_13                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0DU), /*!< EXTI Line 13 */
  HAL_EXTI_LINE_14                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0EU), /*!< EXTI Line 14 */
  HAL_EXTI_LINE_15                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0FU), /*!< EXTI Line 15 */
  HAL_EXTI_LINE_16                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x10U), /*!< EXTI Line 16 */
  HAL_EXTI_LINE_17                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x11U), /*!< EXTI Line 17 */
#if defined(EXTI_IMR1_IM18)
  HAL_EXTI_LINE_18                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x12U), /*!< EXTI Line 18 */
#endif /* EXTI_IMR1_IM18 */
  HAL_EXTI_LINE_19                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x13U), /*!< EXTI Line 19 */
  HAL_EXTI_LINE_20                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x14U), /*!< EXTI Line 20 */
  HAL_EXTI_LINE_21                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x15U), /*!< EXTI Line 21 */
  HAL_EXTI_LINE_22                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x16U), /*!< EXTI Line 22 */
  HAL_EXTI_LINE_23                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x17U), /*!< EXTI Line 23 */
#if defined(EXTI_IMR1_IM24)
  HAL_EXTI_LINE_24                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x18U), /*!< EXTI Line 24 */
#endif /* EXTI_IMR1_IM24 */
#if defined(EXTI_IMR1_IM25)
  HAL_EXTI_LINE_25                       = (LL_EXTI_CONFIG   | LL_EXTI_REG1 | 0x19U)  /*!< EXTI Line 25 */
#endif /* EXTI_IMR1_IM25 */
} hal_exti_line_t;

/*! EXTI Modes */
typedef enum
{
  HAL_EXTI_MODE_INTERRUPT                = LL_EXTI_MODE_IT,       /*!< Interrupt Mode */
  HAL_EXTI_MODE_EVENT                    = LL_EXTI_MODE_EVENT,    /*!< Event Mode */
  HAL_EXTI_MODE_INTERRUPT_EVENT          = LL_EXTI_MODE_IT_EVENT  /*!< Interrupt/Event Mode */
} hal_exti_mode_t;

/*! EXTI Triggers */
typedef enum
{
  HAL_EXTI_TRIGGER_NONE                  = LL_EXTI_TRIGGER_NONE,           /*!< No Trigger */
  HAL_EXTI_TRIGGER_RISING                = LL_EXTI_TRIGGER_RISING,         /*!< Rising Trigger */
  HAL_EXTI_TRIGGER_FALLING               = LL_EXTI_TRIGGER_FALLING,        /*!< Falling Trigger */
  HAL_EXTI_TRIGGER_RISING_FALLING        = LL_EXTI_TRIGGER_RISING_FALLING  /*!< Rising/Falling Trigger */
} hal_exti_trigger_t;

/*! EXTI GPIO Ports */
typedef enum
{
  HAL_EXTI_GPIOA                         = LL_EXTI_GPIO_PORTA, /*!< GPIO Port A */
  HAL_EXTI_GPIOB                         = LL_EXTI_GPIO_PORTB, /*!< GPIO Port B */
  HAL_EXTI_GPIOC                         = LL_EXTI_GPIO_PORTC, /*!< GPIO Port C */
  HAL_EXTI_GPIOD                         = LL_EXTI_GPIO_PORTD, /*!< GPIO Port D */
  HAL_EXTI_GPIOE                         = LL_EXTI_GPIO_PORTE, /*!< GPIO Port E */
#if defined(GPIOF)
  HAL_EXTI_GPIOF                         = LL_EXTI_GPIO_PORTF, /*!< GPIO Port F */
#endif /* GPIOF */
  HAL_EXTI_GPIOG                         = LL_EXTI_GPIO_PORTG, /*!< GPIO Port G */
  HAL_EXTI_GPIOH                         = LL_EXTI_GPIO_PORTH, /*!< GPIO Port H */
#if defined(GPIOI)
  HAL_EXTI_GPIOI                         = LL_EXTI_GPIO_PORTI, /*!< GPIO Port I */
#endif /* GPIOI */
#if defined(GPIOJ)
  HAL_EXTI_GPIOJ                         = LL_EXTI_GPIO_PORTJ  /*!< GPIO Port J */
#endif /* GPIOJ */
} hal_exti_gpio_port_t;

typedef struct hal_exti_handle_s hal_exti_handle_t; /*!< EXTI handle structure type */

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
/*! Pointer to an EXTI callback function */
typedef void(*hal_exti_cb_t)(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger); /*!< EXTI callback function pointer definition */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

/*! EXTI handle structure definition */
struct hal_exti_handle_s /*! EXTI handle structure */
{
  hal_exti_line_t line; /*!< EXTI line */
  uint32_t ll_line;     /*!< Corresponding LL EXTI line */

  volatile hal_exti_state_t global_state; /*!< EXTI global state */
  volatile hal_exti_state_t prev_state;   /*!< Previous status of EXTI global state */

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
  hal_exti_cb_t p_trigger_cb;  /*!< EXTI trigger callback */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
  const void *p_user_data; /*!< User data pointer */
#endif /* USE_HAL_EXTI_USER_DATA */
};

/*! EXTI Configuration structure definition */
typedef struct
{
  hal_exti_trigger_t trigger;     /*!< The EXTI Trigger edge to be configured */
  hal_exti_gpio_port_t gpio_port; /*!< The GPIO Port to be configured for the EXTI line */
} hal_exti_config_t;
/**
  * @}
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_Lines_Aliases EXTI Lines Aliases for STM32U5xx series
  * @{
  */
#define HAL_EXTI_GPIO_0                  HAL_EXTI_LINE_0  /*!< EXTI GPIO Line 0 */
#define HAL_EXTI_GPIO_1                  HAL_EXTI_LINE_1  /*!< EXTI GPIO Line 1 */
#define HAL_EXTI_GPIO_2                  HAL_EXTI_LINE_2  /*!< EXTI GPIO Line 2 */
#define HAL_EXTI_GPIO_3                  HAL_EXTI_LINE_3  /*!< EXTI GPIO Line 3 */
#define HAL_EXTI_GPIO_4                  HAL_EXTI_LINE_4  /*!< EXTI GPIO Line 4 */
#define HAL_EXTI_GPIO_5                  HAL_EXTI_LINE_5  /*!< EXTI GPIO Line 5 */
#define HAL_EXTI_GPIO_6                  HAL_EXTI_LINE_6  /*!< EXTI GPIO Line 6 */
#define HAL_EXTI_GPIO_7                  HAL_EXTI_LINE_7  /*!< EXTI GPIO Line 7 */
#define HAL_EXTI_GPIO_8                  HAL_EXTI_LINE_8  /*!< EXTI GPIO Line 8 */
#define HAL_EXTI_GPIO_9                  HAL_EXTI_LINE_9  /*!< EXTI GPIO Line 9 */
#define HAL_EXTI_GPIO_10                 HAL_EXTI_LINE_10 /*!< EXTI GPIO Line 10 */
#define HAL_EXTI_GPIO_11                 HAL_EXTI_LINE_11 /*!< EXTI GPIO Line 11 */
#define HAL_EXTI_GPIO_12                 HAL_EXTI_LINE_12 /*!< EXTI GPIO Line 12 */
#define HAL_EXTI_GPIO_13                 HAL_EXTI_LINE_13 /*!< EXTI GPIO Line 13 */
#define HAL_EXTI_GPIO_14                 HAL_EXTI_LINE_14 /*!< EXTI GPIO Line 14 */
#define HAL_EXTI_GPIO_15                 HAL_EXTI_LINE_15 /*!< EXTI GPIO Line 15 */
#define HAL_EXTI_PVD                     HAL_EXTI_LINE_16 /*!< EXTI PVD Line */
#define HAL_EXTI_COMP1                   HAL_EXTI_LINE_17 /*!< EXTI COMP1 Line */
#if defined(EXTI_IMR1_IM18)
#define HAL_EXTI_COMP2                   HAL_EXTI_LINE_18 /*!< EXTI COMP2 Line */
#endif /* EXTI_IMR1_IM18 */
#define HAL_EXTI_VDDUSB                  HAL_EXTI_LINE_19 /*!< EXTI VDDUSB Line */
#define HAL_EXTI_VDDIO2                  HAL_EXTI_LINE_20 /*!< EXTI VDDIO2 Line */
#define HAL_EXTI_VDDA1                   HAL_EXTI_LINE_21 /*!< EXTI VDDA1 Line */
#define HAL_EXTI_VDDA2                   HAL_EXTI_LINE_22 /*!< EXTI VDDA2 Line */
/** *!< EXTI MSI_PLL unlock Line
  *  @note : EXTI line 23 is connected to both LSECSSD and MSI_PLL_UNLOCK in STM32U575/585 */
#if defined(EXTI_IMR1_IM24)
#define HAL_EXTI_MSI_PLL_UNLOCK          HAL_EXTI_LINE_23
#define HAL_EXTI_LSECSSD                 HAL_EXTI_LINE_24 /*!< EXTI LSECSS failure detection Line */
#else
#define HAL_EXTI_LSECSSD                 HAL_EXTI_LINE_23 /*!< EXTI LSECSS failure detection Line*/
#define HAL_EXTI_MSI_PLL_UNLOCK          HAL_EXTI_LINE_23 /*!< EXTI MSI_PLL unlock Line */
#endif /* EXTI_IMR1_IM24 */
#if defined(EXTI_IMR1_IM25)
#define HAL_EXTI_IWDG_EWI                HAL_EXTI_LINE_25 /*!< EXTI IWDG Early wakeup interrupt Line */
#endif /* EXTI_IMR1_IM25 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Initialization/De-Initialization and configuration functions
  * @{
  */
hal_status_t HAL_EXTI_Init(hal_exti_handle_t *hexti, hal_exti_line_t line);
void HAL_EXTI_DeInit(hal_exti_handle_t *hexti);
hal_status_t HAL_EXTI_SetConfig(hal_exti_handle_t *hexti, const hal_exti_config_t *p_exti_config);
void HAL_EXTI_GetConfig(const hal_exti_handle_t *hexti, hal_exti_config_t *p_exti_config);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 I/O Operations functions
  * @{
  */
hal_status_t HAL_EXTI_Enable(hal_exti_handle_t *hexti, hal_exti_mode_t mode);
hal_status_t HAL_EXTI_Disable(hal_exti_handle_t *hexti);
hal_status_t HAL_EXTI_GenerateSWI(hal_exti_handle_t *hexti);
hal_exti_trigger_t HAL_EXTI_GetPending(const hal_exti_handle_t *hexti);
void HAL_EXTI_ClearPending(const hal_exti_handle_t *hexti, hal_exti_trigger_t edge);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group3 IRQHandler and callbacks functions
  * @{
  */
void HAL_EXTI_IRQHandler(hal_exti_handle_t *hexti);

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_EXTI_RegisterTriggerCallback(hal_exti_handle_t *hexti, hal_exti_cb_t p_exti_cb);
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

void HAL_EXTI_TriggerCallback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger);

#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
void HAL_EXTI_SetUserData(hal_exti_handle_t *hexti, const void *p_user_data);
const void *HAL_EXTI_GetUserData(const hal_exti_handle_t *hexti);
#endif /* USE_HAL_EXTI_USER_DATA */
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group4 EXTI state and info functions
  * @{
  */
hal_exti_state_t HAL_EXTI_GetState(const hal_exti_handle_t *hexti);
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
#endif

#endif /* STM32U5XX_HAL_EXTI_H */
