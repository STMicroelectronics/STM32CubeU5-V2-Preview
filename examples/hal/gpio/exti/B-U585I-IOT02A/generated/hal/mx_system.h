/**
  ******************************************************************************
  * @file           : mx_system.h
  * @brief          : Exporting peripherals initialization
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
#ifndef MX_SYSTEM_H
#define MX_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "mx_def.h"
#include "mx_hal_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief  System initialization
  * @retval Status
  */
system_status_t mx_system_init(void);

system_status_t pre_system_init_hook(void);

system_status_t post_system_init_hook(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_SYSTEM_H */
