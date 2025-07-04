/**
  ******************************************************************************
  * @file           : mx_def.h
  * @brief          : Exporting definition
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
#ifndef MX_DEF_H
#define MX_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  SYSTEM_OK = 0,                    /* System initialization successfully       */
  SYSTEM_PRESYSTEM_ERROR,           /* Error during System pre-initialization   */
  SYSTEM_STARTUP_ERROR,             /* Error during startup initialization      */
  SYSTEM_INTERRUPTS_ERROR,          /* Error during interrupts initialization   */
  SYSTEM_CLOCK_ERROR,               /* Error during clock initialization        */
  SYSTEM_RESOURCES_ISOLATION_ERROR, /* Error during Cortex MPU initialization   */
  SYSTEM_POWER_ERROR,               /* Error during power initialization        */
  SYSTEM_PERIPHERAL_ERROR,          /* Error during peripherals initialization  */
  SYSTEM_POSTSYSTEM_ERROR           /* Error during System post-initialization  */
} system_status_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_DEF_H */
