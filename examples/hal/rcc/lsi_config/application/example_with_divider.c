/**
  ******************************************************************************
  * file           : example_with_divider.c
  * brief          : LSI configuration with HAL_API
  ******************************************************************************
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

/* Includes ------------------------------------------------------------------*/
#include "example.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Time during the LSI will be enabled at each process loop */
#define LSI_ENABLE_DELAY_MS 2000U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype -----------------------------------------------*/


/** ########## Step 1 ##########
  * In RCC examples, the init has already been triggered by mx_system_init() from main.
  * The MCO pin is configured in the generated code to output the LSI clock.
  */
app_status_t app_init(void)
{
  PRINTF("[INFO] Step 1: MCO pin initialized to output the LSI clock.\n");

  /* The access to the backup domain need to be granted to change the LSI state. */
  if (HAL_PWR_IsEnabledRTCDomainWriteProtection() == HAL_PWR_RTC_DOMAIN_WRP_ENABLED)
  {
    HAL_PWR_DisableRTCDomainWriteProtection();
  }

  /** The backup domain status can impact the LSI state. The reset of this domain disables the LSI clock and prevents
    * an unknown state. The usage of this function might impact other peripherals, the user needs to take care of its
    * abusive use.
    */
  HAL_RCC_ResetBackupDomain();

  return EXEC_STATUS_INIT_OK;
} /* end app_init */


/** ########## Step 2 ##########
  * Enables the LSI during LSI_ENABLE_DELAY_MS ms and then disables it.
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (LL_RCC_LSI_IsReady() != 0U)
  {
    goto _app_process_exit;
  }

  if (HAL_RCC_LSI_Enable(HAL_RCC_LSI_DIV1) != HAL_OK)
  {
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: LSI enabled (%" PRIu32 " Hz) to MCO pin, with a %u divider (MCO freq: %" PRIu32 " Hz).\n",
         (uint32_t)LSI_VALUE,
         MCO_DIVIDER_INT,
         (uint32_t)(LSI_VALUE / MCO_DIVIDER_INT)
        );

  HAL_Delay(LSI_ENABLE_DELAY_MS);

  if (HAL_RCC_LSI_Disable() != HAL_OK)
  {
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: LSI disabled.\n");

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** ########## Step 3 ##########
  * In RCC examples, it is not possible to deinitialize the RCC before leaving the scenario.
  * The LSI is no longer outputted on the MCO pin.
  */
app_status_t app_deinit(void)
{
  PRINTF("[INFO] Step 3: stop to output LSI on MCO pin.\n");
  return EXEC_STATUS_OK;
} /* end app_deinit */
