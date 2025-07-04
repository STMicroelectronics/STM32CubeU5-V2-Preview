/**
  ******************************************************************************
  * file           : example.c
  * brief          : The responder's application handling a data transfer over
  *                  I2C in a non-blocking mode with interrupts and HAL API.
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
#include <string.h> /* importing memcmp and memset functions */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* @user: set the maximum number of attempts to complete a data transfer between the two boards */
#define MAX_COM_ATTEMPTS 10U
/* @user: must be equal to the size (in bytes) of the buffer received from the controller */
#define BUFFER_SIZE 41U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_i2c_handle_t *pI2C;  /* pointer referencing the I2C handle from the generated code */

/* Buffer used for reception (sent back to the controller) */
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

volatile uint8_t TxTransferComplete; /* Set to 1 if the write transfer is correctly completed */
volatile uint8_t RxTransferComplete; /* Set to 1 if the read transfer is correctly completed */
volatile uint8_t TransferError;      /* Set to 1 if a transmission or a reception error is detected */

/* Private functions prototype -----------------------------------------------*/
static app_status_t HandleTransferCplt(void);
static app_status_t HandleTransferError(uint32_t hal_status, uint32_t i2c_error_code);

/* Functions allowing the user to configure dynamically the I2C slave callbacks instead of weak functions */
static void SlaveTxTransferCpltCallback(hal_i2c_handle_t *pI2C);
static void SlaveRxTransferCpltCallback(hal_i2c_handle_t *pI2C);
static void TransferErrorCallback(hal_i2c_handle_t *pI2C);

/** ########## Step 1 ##########
  * The init of the I2C instance is triggered by the applicative code.
  * The I2C slave callbacks for TX/RX transfer completed and transfer error are registered.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pI2C = mx_example_i2c_init();
  if (pI2C == NULL)
  {
    goto _app_init_exit;
  }

  /* Register the I2C slave callbacks */
  if (HAL_I2C_SLAVE_RegisterTxCpltCallback(pI2C, SlaveTxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_I2C_SLAVE_RegisterRxCpltCallback(pI2C, SlaveRxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_I2C_RegisterErrorCallback(pI2C, TransferErrorCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }

  PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  hal_status_t hal_status;   /* memorizes the HAL status of the I2C TX/RX operations */
  uint32_t com_attempts = 0U; /* memorizes the number of attempts made to exchange a message between the boards */
  uint32_t i2c_error_code;   /* memorizes the I2C error code limited to the last process */

  /* Clear the Rx buffer before starting a new transfer */
  memset(RxBuffer, 0U, BUFFER_SIZE);

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear the I2C interrupts flags before starting a new transfer */
    TxTransferComplete = 0U;
    RxTransferComplete = 0U;
    TransferError = 0U;

    /* Start a new communication attempt */
    com_attempts ++;

    /** ########## Step 2 ##########
      * Receives in interrupt mode a buffer containing a null-terminated string using I2C.
      */
    hal_status = HAL_I2C_SLAVE_Receive_IT(pI2C, RxBuffer, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the I2C read transfer. Report it, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 3 ##########
      * Waits for one of these I2C interrupts: read transfer complete or transfer error.
      */
    while ((RxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An I2C interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      /* WFI temporarily disabled as a workaround */
      /* __WFI(); */
    }

    if (TransferError == 1)
    {
      /* The read transfer is not correctly completed. Report the error, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 4 ##########
      * Transmits in interrupt mode the received buffer, containing a null-terminated string, using I2C.
      */
    hal_status = HAL_I2C_SLAVE_Transmit_IT(pI2C, RxBuffer, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the I2C write transfer. Report it, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 5 ##########
      * Waits for one of these I2C interrupts: write transfer complete or transfer error.
      */
    while ((TxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An I2C interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      /* WFI temporarily disabled as a workaround */
      /* __WFI(); */
    }

    if (TransferError == 1)
    {
      /* The write transfer is not correctly completed. Report the error, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /* Report the communication status: Data Transfer completed */
    return_status = HandleTransferCplt();

  } /* end while */

  return return_status;
} /* end app_process */


/** Slave reception end of transfer callback
  * @user This implementation of the I2C slave Rx transfer complete callback can be customized.
  * This function is executed if the slave Rx transfer complete interrupt is generated.
  */
static void SlaveRxTransferCpltCallback(hal_i2c_handle_t *hi2c)
{
  /* Asynchronous processing related to step 3 */
  RxTransferComplete = 1U;
}


/** Slave transmission end of transfer callback
  * @user This implementation of the I2C slave Tx transfer complete callback can be customized.
  * This function is executed if the slave Tx transfer complete interrupt is generated.
  */
static void SlaveTxTransferCpltCallback(hal_i2c_handle_t *hi2c)
{
  /* Asynchronous processing related to step 5 */
  TxTransferComplete = 1U;
}


/** I2C transfer error callback
  * @user This implementation of the I2C slave transfer error callback can be customized.
  * This function is executed if the slave transfer error interrupt is generated.
  */
static void TransferErrorCallback(hal_i2c_handle_t *hi2c)
{
  /* Asynchronous processing related to step 3 and 5 */
  TransferError = 1U;
}


/** De-initializes the I2C instance before leaving the scenario.
  * In this example, app_deinit is never called and it is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  mx_example_i2c_deinit();

  return EXEC_STATUS_OK;
} /* end app_deinit */


/** brief:  This function is executed when the data transfer is completed.
  * param:  none
  * retval: example status
  */
static app_status_t HandleTransferCplt(void)
{
  PRINTF("[INFO] Responder - Message received and sent back: %s \n", RxBuffer);

  return EXEC_STATUS_OK;
} /* end HandleTransferCplt */

/** brief:  This function is executed in case of a data transfer error.
  * param hal_status:  HAL status of the I2C TX/RX operations.
  * param i2c_error_code:  I2C Error Code.
  * retval: example status
  */
static app_status_t HandleTransferError(uint32_t hal_status, uint32_t i2c_error_code)
{
  PRINTF("[ERROR] Responder - Communication ERROR: hal_status = %" PRIu32 ", \
  HAL_I2C_GetLastErrorCodes = %" PRIu32 ". TRYING AGAIN.\n", hal_status, i2c_error_code);

  return EXEC_STATUS_ERROR;
} /* end HandleTransferError */



