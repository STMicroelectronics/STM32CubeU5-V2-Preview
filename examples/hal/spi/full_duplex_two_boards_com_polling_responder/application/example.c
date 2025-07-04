/**
  ******************************************************************************
  * file           : example.c
  * brief          : A full-duplex synchronous SPI communication as responder,
  *                  in polling mode, using the HAL API.
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
#define BUFFER_SIZE 53U
/* @user: Set the timeout period in milliseconds for the transmission and the reception of data */
#define TIMEOUT 1000U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_spi_handle_t *pSPI; /* Pointer referencing the SPI handle from the generated code */

volatile uint8_t TxRxTransferComplete; /* Set to 1 if the write-read transfer is correctly completed */
volatile uint8_t TransferError;        /* Set to 1 if a transmission or a reception error is detected */

/** BufferA, BufferB: fixed-size buffers to transfer alternately.
  * @user: it is possible to modify the messages content and length, update BUFFER_SIZE if necessary.
  */
static const uint8_t BufferA[BUFFER_SIZE] = "SPI Full Duplex Two Boards Communication - Message A";
static const uint8_t BufferB[BUFFER_SIZE] = "SPI Full Duplex Two Boards Communication - Message B";
/* Pointer to the buffer used for transmission */
const uint8_t *pTxData;
/* Buffer used for reception */
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

/* Private functions prototype -----------------------------------------------*/
static inline void UpdateBuffers(void);
static app_status_t HandleTransferCplt(void);
static app_status_t HandleTransferError(uint32_t hal_status, uint32_t spi_error_code);

/** ########## Step 1 ##########
  * The init of the SPI instance is triggered by the applicative code.
  */
app_status_t app_init(void)
{
  app_status_t return_status;

  pSPI = mx_example_spi_init();

  if (pSPI != NULL)
  {
    PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }
  else
  {
    PRINTF("[ERROR] Step 1: Device initialization ERROR.\n");
    return_status = EXEC_STATUS_ERROR;
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  hal_status_t hal_status;   /* memorizes the HAL status of the SPI TX/RX operations */
  uint32_t com_attempts = 0U; /* memorizes the number of attempts made to exchange a message between the boards */
  uint32_t spi_error_code;   /* memorizes the SPI error code limited to the last process */

  UpdateBuffers();

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Start a new communication attempt */
    com_attempts ++;

    /** ########## Step 2 ##########
      * Initiate communication in full duplex blocking mode by exchanging data (transmitting and receiving) with
      * the responder within a specific timeout period.
      */

    hal_status = HAL_SPI_TransmitReceive(pSPI, pTxData, &RxBuffer, BUFFER_SIZE, TIMEOUT);
    if (hal_status != HAL_OK)
    {
      spi_error_code = HAL_SPI_GetLastErrorsCodes(pSPI);
      return_status  = HandleTransferError(hal_status, spi_error_code);
      continue;
    }

    /** ########## Step 3 ##########
      * Checks that the sent and received buffers match.
      */
    return_status = HandleTransferCplt();

  } /* end while */

  return return_status;
} /* end app_process */


/** De-initializes the SPI before leaving the scenario.
  */
app_status_t app_deinit(void)
{

  mx_example_spi_deinit();

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
    PRINTF("[INFO] Responder - Tx/Rx Buffers IDENTICAL. Transfer COMPLETED of %s \n", pTxData);

    return_status = EXEC_STATUS_OK;
  }
  else
  {
    PRINTF("[ERROR] Responder - Tx/Rx Buffers DIFFERENT. TRYING AGAIN.\n");
    HAL_Delay(1000U);
  }

  return return_status;
} /* end HandleTransferCplt */


/** brief:  This function is executed in case of a data transfer error.
  * param hal_status:  HAL status of the SPI TX/RX operations.
  * param spi_error_code:  SPI Error Code.
  * retval: example status
  */
static app_status_t HandleTransferError(uint32_t hal_status, uint32_t spi_error_code)
{
  PRINTF("[ERROR] Responder - Communication ERROR: hal_status = %" PRIu32 ", \
  HAL_SPI_GetLastErrorCodes = %" PRIu32 ". TRYING AGAIN.\n", hal_status, spi_error_code);

  /* Take the time to check the setup before restarting the communication */
  HAL_Delay(1000U);

  return EXEC_STATUS_ERROR;
} /* end HandleTransferError */
