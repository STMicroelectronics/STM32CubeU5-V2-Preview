/**
  ******************************************************************************
  * @file           : mx_hal_def.h
  * @brief          : Exporting peripherals initialization
  *                   Include entry for the target folder to the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "mx_tim6.h"
#include "mx_icache.h"
#include "mx_rcc.h"

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
/*        TIM6_MyTIM_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_tim6_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  *         Name of the Config label:
  *                   1ms
  * @retval hal_tim_handle_t Pointer on the handle on the TIM6 instance
  */
#define mytim_1_1ms_init mx_tim6_cfg1_hal_init

#define tim_timebase_1ms_init mytim_1_1ms_init


/**
  * @brief  Initialize the mx_tim6_cfg2_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  *         Name of the Config label:
  *                   10ms
  * @retval hal_tim_handle_t Pointer on the handle on the TIM6 instance
  */
#define mytim_1_10ms_init mx_tim6_cfg2_hal_init

#define tim_timebase_10ms_init mytim_1_10ms_init


/**
  * @brief  Initialize the mx_tim6_cfg3_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  *         Name of the Config label:
  *                   100ms
  * @retval hal_tim_handle_t Pointer on the handle on the TIM6 instance
  */
#define mytim_1_100ms_init mx_tim6_cfg3_hal_init

#define tim_timebase_100ms_init mytim_1_100ms_init


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
/*        TIM6_MyTIM_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_tim6_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  *         Name of the Config label:
  *                   1ms
  */
#define mytim_1_1ms_deinit mx_tim6_cfg1_hal_deinit

#define tim_timebase_1ms_deinit mytim_1_1ms_deinit


/**
  * @brief  De-Initialize the mx_tim6_cfg2_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  *         Name of the Config label:
  *                   10ms
  */
#define mytim_1_10ms_deinit mx_tim6_cfg2_hal_deinit

#define tim_timebase_10ms_deinit mytim_1_10ms_deinit


/**
  * @brief  De-Initialize the mx_tim6_cfg3_hal with HAL layer
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  *         Name of the Config label:
  *                   100ms
  */
#define mytim_1_100ms_deinit mx_tim6_cfg3_hal_deinit

#define tim_timebase_100ms_deinit mytim_1_100ms_deinit


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
/*        TIM6_MyTIM_1: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for TIM6
  *         Name of the User label:
  *                   MyTIM_1
  *                   tim_timebase
  * @retval hal_tim_handle_t Pointer on the handle on the TIM6 instance
  */
#define mytim_1_gethandle mx_tim6_hal_gethandle

#define tim_timebase_gethandle mytim_1_gethandle


/* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
