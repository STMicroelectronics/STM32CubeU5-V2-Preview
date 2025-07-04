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
#include "mx_icache.h"
#include "mx_usart2.h"
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_icache_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  * @retval hal_icache_handle_t Pointer on the handle on the ICACHE instance
  */
#define myicache_1_init mx_icache_cfg1_hal_init


/* *********************************************************** */
/*        usart2_instance2: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_usart2_cfg1_hal_usart with HAL layer
  *         Name of the User label:
  *                   mx_example_usart
  *         Name of the Config label:
  *
  * @retval hal_usart_handle_t Pointer on the handle on the USART2 instance
  */
#define mx_example_usart_init mx_usart2_cfg1_hal_usart_init


/* *********************************************************** */
/*        gpio_default_instance3: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_gpio_default_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   GPIO
  *         Name of the Config label:
  *
  * @retval hal_gpio_handle_t Pointer on the handle on the gpio_default instance
  */
#define gpio_init mx_gpio_default_cfg1_hal_init


/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_icache_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  */
#define myicache_1_deinit mx_icache_cfg1_hal_deinit


/* *********************************************************** */
/*        usart2_instance2: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_usart2_cfg1_hal_usart with HAL layer
  *         Name of the User label:
  *                   mx_example_usart
  *         Name of the Config label:
  *
  */
#define mx_example_usart_deinit mx_usart2_cfg1_hal_usart_deinit


/* *********************************************************** */
/*        gpio_default_instance3: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_gpio_default_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   GPIO
  *         Name of the Config label:
  *
  */
#define gpio_deinit mx_gpio_default_cfg1_hal_deinit


/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* *********************************************************** */
/*        GPIO: aliases for get EXTI object functions */
/* *********************************************************** */


/* *********************************************************** */
/*        usart2_instance2: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for USART2
  *         Name of the User label:
  *                   mx_example_usart
  * @retval hal_usart_handle_t Pointer on the handle on the USART2 instance
  */
#define mx_example_usart_gethandle mx_usart2_hal_usart_gethandle


/* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
