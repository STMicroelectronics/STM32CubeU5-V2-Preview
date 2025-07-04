/**
  ******************************************************************************
  * file           : example.c
  * brief          : The controller's application handling a data transfer over
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
/* @user: define the responder 7-bit address */
#define I2C_RESPONDER_ADDR_7BIT 0x3FU
/* The responder 7-bit address must be shifted to the left before calling I2C HAL APIs */
#define I2C_RESPONDER_ADDR_7BIT_SHIFTED (I2C_RESPONDER_ADDR_7BIT << 1U)
/* @user: set the payload size in bytes. The I2C message is a string made of this payload and terminated by '\0'. */
#define I2C_PAYLOAD_SIZE 40U
/**
  * Size of the TX and RX buffers in bytes.
  * +1 is used to store the null character as the transmitted I2C message is a null-terminated string.
  */
#define BUFFER_SIZE (I2C_PAYLOAD_SIZE + 1U)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_i2c_handle_t *pI2C;   /* pointer referencing the I2C handle from the generated code */

volatile uint8_t TxTransferComplete; /* Set to 1 if the write transfer is correctly completed */
volatile uint8_t RxTransferComplete; /* Set to 1 if the read transfer is correctly completed */
volatile uint8_t TransferError;      /* Set to 1 if a transmission or a reception error is detected */

/** BufferA, BufferB: fixed-size buffers to transfer alternately.
  * @user: it is possible to modify the messages content and length, update I2C_PAYLOAD_SIZE if necessary.
  */
static const uint8_t BufferA[BUFFER_SIZE] = "I2C Two Boards Communication - Message A";
static const uint8_t BufferB[BUFFER_SIZE] = "I2C Two Boards Communication - Message B";
/* Pointer to the buffer used for transmission */
const uint8_t *pTxData = NULL;
/* Buffer used for reception */
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

/* Private functions prototype -----------------------------------------------*/
static inline void UpdateBuffers(void);
static app_status_t HandleTransferCplt(void);
static app_status_t HandleTransferError(uint32_t hal_status, uint32_t i2c_error_code);

/* Functions allowing the user to configure dynamically the I2C master callbacks instead of weak functions */
static void MasterTxTransferCpltCallback(hal_i2c_handle_t *pI2C);
static void MasterRxTransferCpltCallback(hal_i2c_handle_t *pI2C);
static void TransferErrorCallback(hal_i2c_handle_t *pI2C);

/** ########## Step 1 ##########
  * The init of the I2C instance is triggered by the applicative code.
  * The user callbacks for I2C master TX/RX transfer completed and transfer error are registered.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pI2C = mx_example_i2c_init();
  if (pI2C == NULL)
  {
    goto _app_init_exit;
  }

  /* Register the I2C master callbacks */
  if (HAL_I2C_MASTER_RegisterTxCpltCallback(pI2C, MasterTxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_I2C_MASTER_RegisterRxCpltCallback(pI2C, MasterRxTransferCpltCallback) != HAL_OK)
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

  UpdateBuffers();

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear the I2C interrupts flags before starting a new transfer */
    TxTransferComplete = 0U;
    RxTransferComplete = 0U;
    TransferError = 0U;

    /* Start a new communication attempt */
    com_attempts ++;

    /** ########## Step 2 ##########
      * Transmits in interrupt mode the buffer pointed by pTxData, containing a null-terminated string, using I2C.
      */
    hal_status = HAL_I2C_MASTER_Transmit_IT(pI2C, I2C_RESPONDER_ADDR_7BIT_SHIFTED, pTxData, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the I2C write transfer. Report it, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 3 ##########
      * Waits for one of these I2C interrupts: write transfer complete or transfer error.
      */
    while ((TxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An I2C interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* The write transfer is not correctly completed. Report the error, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 4 ##########
      * Receives in interrupt mode a buffer containing a null-terminated string using I2C.
      */
    hal_status = HAL_I2C_MASTER_Receive_IT(pI2C, I2C_RESPONDER_ADDR_7BIT_SHIFTED, RxBuffer, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the I2C read transfer. Report it, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 5 ##########
      * Waits for one of these I2C interrupts: read transfer complete or transfer error.
      */
    while ((RxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An I2C interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* The read transfer is not correctly completed. Report the error, then restart the communication */
      i2c_error_code = HAL_I2C_GetLastErrorCodes(pI2C);
      return_status  = HandleTransferError(hal_status, i2c_error_code);
      continue;
    }

    /** ########## Step 6 ##########
      * Checks the correctness of the received buffer after the data transfer is completed.
      */
    return_status = HandleTransferCplt();

  } /* end while */

  return return_status;
} /* end app_process */


/** Master transmission end of transfer callback
  * @user This implementation of the I2C master Tx transfer complete callback can be customized.
  * This function is executed if the master Tx transfer complete interrupt is generated.
  */
static void MasterTxTransferCpltCallback(hal_i2c_handle_t *hi2c)
{
  /* Asynchronous processing related to step 3 */
  TxTransferComplete = 1U;
}


/** Master reception end of transfer callback
  * @user This implementation of the I2C master Rx transfer complete callback can be customized.
  * This function is executed if the master Rx transfer complete interrupt is generated.
  */
static void MasterRxTransferCpltCallback(hal_i2c_handle_t *hi2c)
{
  /* Asynchronous processing related to step 5 */
  RxTransferComplete = 1U;
}


/** I2C transfer error callback
  * @user This implementation of the I2C master transfer error callback can be customized.
  * This function is executed if the master transfer error interrupt is generated.
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


/** brief:  Updates the TX buffer pointer and clears the RX buffer before starting a new transfer.
  * param:  none
  * retval: none
  */
static inline void UpdateBuffers(void)
{
  /* Toggle between BufferA and BufferB to select the message to send */
  if (pTxData == BufferA)
  {
    pTxData = BufferB;
  }
  else
  {
    pTxData = BufferA;
  }

  memset(RxBuffer, 0U, BUFFER_SIZE);
} /* end UpdateBuffers */

/** brief:  Checks the correctness of the data when the transfer is completed.
  * param:  none
  * retval: example status
  */
static app_status_t HandleTransferCplt(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (memcmp(pTxData, RxBuffer, BUFFER_SIZE) == 0)
  {
    PRINTF("[INFO] Controller - Tx/Rx Buffers IDENTICAL. Transfer COMPLETED of %s \n", pTxData);

    return_status = EXEC_STATUS_OK;
  }
  else
  {
    PRINTF("[ERROR] Controller - Tx/Rx Buffers DIFFERENT. TRYING AGAIN.\n");
  }

  return return_status;
} /* end HandleTransferCplt */

/** brief:  This function is executed in case of a data transfer error.
  * param hal_status:  HAL status of the I2C TX/RX operations.
  * param i2c_error_code:  I2C Error Code.
  * retval: example status
  */
static app_status_t HandleTransferError(uint32_t hal_status, uint32_t i2c_error_code)
{
  PRINTF("[ERROR] Controller - Communication ERROR: hal_status = %" PRIu32 ", \
  HAL_I2C_GetLastErrorCodes = %" PRIu32 ". TRYING AGAIN.\n", hal_status, i2c_error_code);

  /* Take the time to check the setup before restarting the communication */
  HAL_Delay(1000U);

  return EXEC_STATUS_ERROR;
} /* end HandleTransferError */
