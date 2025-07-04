/**
  ******************************************************************************
  * @file           : mx_hal_def.h
  * @brief          : Exporting peripherals initialization
  *                   Include entry for the target folder to the application.
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
#ifndef MX_HAL_DEF_H
#define MX_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_tim1.h"
#include "mx_icache.h"
#include "mx_rcc.h"
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_icache_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  * @retval hal_icache_handle_t Pointer on the handle on the ICACHE instance
  */
#define myicache_1_init mx_icache_hal_init


/* *********************************************************** */
/*        gpio_default_MyGPIO_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_gpio_default_hal with HAL layer
  *         Name of the User label:
  *                   MyGPIO_1
  *                   mx_gpio_status_led
  * @retval system_status_t Value based on the system_status_t
  */
#define mygpio_1_init mx_gpio_default_hal_init

#define mx_gpio_status_led_init mx_gpio_default_hal_init


/* *********************************************************** */
/*        RCC_MyRCC_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_rcc_hal with HAL layer
  *         Name of the User label:
  *                   MyRCC_1
  * @retval system_status_t Value based on the system_status_t
  */
#define myrcc_1_init mx_rcc_hal_init


/* *********************************************************** */
/*        TIM1_MyTIM_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_tim1_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   mx_example_tim
  * @retval hal_tim_handle_t Pointer on the handle on the TIM1 instance
  */
#define mytim_1_init mx_tim1_hal_init

#define mx_example_tim_init mx_tim1_hal_init


/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_icache_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  */
#define myicache_1_deinit mx_icache_hal_deinit


/* *********************************************************** */
/*        gpio_default_MyGPIO_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_gpio_default_hal with HAL layer
  *         Name of the User label:
  *                   MyGPIO_1
  *                   mx_gpio_status_led
  */
#define mygpio_1_deinit mx_gpio_default_hal_deinit

#define mx_gpio_status_led_deinit mx_gpio_default_hal_deinit


/* *********************************************************** */
/*        TIM1_MyTIM_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_tim1_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   mx_example_tim
  */
#define mytim_1_deinit mx_tim1_hal_deinit

#define mx_example_tim_deinit mx_tim1_hal_deinit


/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* *********************************************************** */
/*        GPIO: aliases for get EXTI object functions */
/* *********************************************************** */


  /* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for ICACHE
  *         Name of the User label:
  *                   MyICACHE_1
  * @retval hal_icache_handle_t Pointer on the handle on the ICACHE instance
  */
#define myicache_1_gethandle mx_icache_hal_gethandle

/* *********************************************************** */
/*        TIM1_MyTIM_1: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for TIM1
  *         Name of the User label:
  *                   MyTIM_1
  *                   mx_example_tim
  * @retval hal_tim_handle_t Pointer on the handle on the TIM1 instance
  */
#define mytim_1_gethandle mx_tim1_hal_gethandle

#define mx_example_tim_gethandle mx_tim1_hal_gethandle


/* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
