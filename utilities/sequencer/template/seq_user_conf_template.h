/**
  **********************************************************************************************************************
  * @file    seq_user_conf.h
  * @author  MCD Application Team
  * @brief   Sequencer configuration file
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */


/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef SEQ_USER_CONF_H
#define SEQ_USER_CONF_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "cmsis_compiler.h"
#include <string.h>

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/**
  * @brief  macro used to init the critical section.
  */
#define SEQ_INIT_CRITICAL_SECTION( )
/**
  * @brief macro used to enter the critical section.
  */
#define SEQ_ENTER_CRITICAL_SECTION( )      uint32_t primask_bit = __get_PRIMASK( );\
  __disable_irq( )
/**
  * @brief  macro used to exit the critical section.
  */
#define SEQ_EXIT_CRITICAL_SECTION( )       __set_PRIMASK( primask_bit )

#define SEQ_CONF_TASK_NBR                  (32U)
#define SEQ_CONF_PRIO_NBR                  (2U)

/**
  * @brief memset macro.
  */
#define SEQ_MEMSET8(dest, value, size)     memset((dest),(value),(size));

/**
  * @brief macro used to enter the critical section before calling the IDLE function
  * @note  in a basic configuration must be identical to the macro
  *        SEQ_ENTER_CRITICAL_SECTION. The redefinition of this macro will allow
  *        to perform specific operation

  */
#define SEQ_ENTER_CRITICAL_SECTION_IDLE( )    SEQ_ENTER_CRITICAL_SECTION( )

/**
  * @brief macro used to exit the critical section when exiting the IDLE function
  * @note  the behavior of the macro must be symmetrical with the macro
  *        SEQ_ENTER_CRITICAL_SECTION_IDLE
  */
#define SEQ_EXIT_CRITICAL_SECTION_IDLE( )     SEQ_EXIT_CRITICAL_SECTION( )

#ifdef __cplusplus
}
#endif

#endif /*SEQ_USER_CONF_H */
