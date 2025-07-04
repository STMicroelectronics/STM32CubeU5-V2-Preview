/**
  ******************************************************************************
  * @file           : mx_seq.h
  * @brief          : header for mx_seq.c
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
#ifndef MX_SEQ_H
#define MX_SEQ_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "sequencer.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/******************************************************************************/
/* Exported defines for mx_seq in sequencer utility          */
/******************************************************************************/
/**
  * @brief  user tasks ID definition
  */
#define  MX_TASK_TOGGLE  SEQ_TASK_0

/* Exported functions ------------------------------------------------------- */

/******************************************************************************/
/* Exported functions for mx_seq in sequencer utility  */
/******************************************************************************/
/**
  * @brief seq initialization function
  * This function call the seq init function
  */
void mx_seq_init(void);

/**
  * @brief task functions definition
  *
  */
void gpio_toggle(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_SEQ_H */
