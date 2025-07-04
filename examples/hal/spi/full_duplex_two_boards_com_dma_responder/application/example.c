/**
  ******************************************************************************
  * file           : example.c
  * brief          : A full-duplex synchronous SPI communication as responder,
  *                  in DMA mode, using the HAL API.
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

/* Functions allowing the user to configure dynamically the SPI callbacks instead of weak functions */
static void TxRxTransferCpltCallback(hal_spi_handle_t *pSPI);
static void TransferErrorCallback(hal_spi_handle_t *pSPI);

/** ########## Step 1 ##########
  * The init of the SPI and DMA instances are triggered by the applicative code.
  * The user callbacks for SPI TX/RX transfer completed and transfer error are registered.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pSPI = mx_example_spi_init();
  if (pSPI == NULL)
  {
    goto _app_init_exit;
  }

  /* Register the SPI callbacks */
  if (HAL_SPI_RegisterTxRxCpltCallback(pSPI, TxRxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_SPI_RegisterErrorCallback(pSPI, TransferErrorCallback) != HAL_OK)
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
  hal_status_t hal_status;   /* memorizes the HAL status of the SPI TX/RX operations */
  uint32_t com_attempts = 0U; /* memorizes the number of attempts made to exchange a message between the boards */
  uint32_t spi_error_code;   /* memorizes the SPI error code limited to the last process */

  UpdateBuffers();

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear the SPI interrupts flags before starting a new transfer */
    TxRxTransferComplete = 0U;
    TransferError = 0U;

    /* Start a new communication attempt */
    com_attempts ++;

    /** ########## Step 2 ##########
      * Initiates the communication with the controller in a full duplex mode, using DMA, by sending and
      * receiving data simultaneously.
      * The SPI messages exchanged are null-terminated strings.
      */
    hal_status = HAL_SPI_TransmitReceive_DMA(pSPI, pTxData, RxBuffer, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      spi_error_code = HAL_SPI_GetLastErrorsCodes(pSPI);
      return_status  = HandleTransferError(hal_status, spi_error_code);
      continue;
    }

    /** ########## Step 3 ##########
      * Waits for one of these SPI interrupts: write-read transfer complete or transfer error.
      */
    while ((TxRxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. A SPI interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the DMA. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* The write-read transfer is not correctly completed. Report the error, then restart the communication */
      spi_error_code = HAL_SPI_GetLastErrorsCodes(pSPI);
      return_status  = HandleTransferError(hal_status, spi_error_code);
      continue;
    }

    /** ########## Step 4 ##########
      * Checks the correctness of the received buffer after the data transfer is completed.
      */
    return_status = HandleTransferCplt();

  } /* end while */

  return return_status;
} /* end app_process */


/** SPI TX/RX Transfer complete callback
  * @user: This implementation of the SPI TX/RX transfer complete callback can be customized.
  * This function is executed if the SPI Tx/Rx transfer complete interrupt is generated.
  */
static void TxRxTransferCpltCallback(hal_spi_handle_t *hspi)
{
  /* Asynchronous processing related to step 3 */
  TxRxTransferComplete = 1U;
}


/** SPI transfer error callback
  * @user: This implementation of the SPI transfer error callback can be customized.
  * This function is executed if the SPI transfer error interrupt is generated.
  */
static void TransferErrorCallback(hal_spi_handle_t *hspi)
{
  /* Asynchronous processing related to step 3 */
  TransferError = 1U;
}


/** Deinitializes the SPI instance before leaving the scenario.
  * In this example, app_deinit is never called and it is provided as a reference only.
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


/** brief: This function is executed in case of a data transfer error.
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
