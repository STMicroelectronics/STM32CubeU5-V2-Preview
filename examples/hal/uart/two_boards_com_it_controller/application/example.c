/**
  ******************************************************************************
  * file           : example.c
  * brief          : The controller side in a interrupt mode UART communication
  *                  using HAL API.
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
#include <inttypes.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* @user: set the maximum number of attempts to complete a data transfer between the two boards */
#define MAX_COM_ATTEMPTS 10U
/* @user: set the payload size in bytes. The UART message is a string made of this payload and terminated by '\0'. */
#define UART_PAYLOAD_SIZE 41U
/**
  * Size of the TX and RX buffers in bytes.
  * +1 is used to store the null character as the transmitted UART message is a null-terminated string.
  */
#define BUFFER_SIZE (UART_PAYLOAD_SIZE + 1U)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_uart_handle_t *pUART; /* Pointer referencing the UART handle from the generated code */

volatile uint8_t TxTransferComplete; /* Set to 1 if the write transfer is correctly completed */
volatile uint8_t RxTransferComplete; /* Set to 1 if the read transfer is correctly completed */
volatile uint8_t TransferError;      /* Set to 1 if a transmission or a reception error is detected */

/** BufferA, BufferB: fixed-size buffers to transfer alternately.
  * @user: it is possible to modify the buffers content and length, update BUFFER_SIZE if necessary.
  */
static const uint8_t BufferA[BUFFER_SIZE] = "UART Two Boards Communication - Message A";
static const uint8_t BufferB[BUFFER_SIZE] = "UART Two Boards Communication - Message B";
/* Pointer to the buffer used for transmission */
const uint8_t *pTxData = NULL;
/* Buffer used for reception */
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

/* Private functions prototype -----------------------------------------------*/
static inline void UpdateBuffers(void);
static app_status_t HandleTransferCplt(void);

/* Functions allowing the user to configure dynamically the UART callbacks instead of weak functions */
static void TxTransferCpltCallback(hal_uart_handle_t *pUART);
static void RxTransferCpltCallback(hal_uart_handle_t *pUART, uint32_t size_byte, hal_uart_rx_event_types_t rx_event);
static void TransferErrorCallback(hal_uart_handle_t *pUART);


/** ########## Step 1 ##########
  * The init of the UART instance is triggered by the applicative code.
  * The user callbacks for UART TX/RX transfer completed and transfer error are registered.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pUART = mx_example_uart_init();

  if (pUART == NULL)
  {
    goto _app_init_exit;
  }

  /* Register the UART callbacks */
  if (HAL_UART_RegisterTxCpltCallback(pUART, TxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_UART_RegisterRxCpltCallback(pUART, RxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_UART_RegisterErrorCallback(pUART, TransferErrorCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }

  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  hal_status_t hal_status;   /* memorizes the HAL status of the UART TX/RX operations */
  uint32_t com_attempts = 0U; /* memorizes the number of attempts made to exchange a message between the boards */

  UpdateBuffers();

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear the UART interrupts flags before starting a new transfer */
    TxTransferComplete = 0U;
    RxTransferComplete = 0U;
    TransferError = 0U;

    /* Start a new communication attempt */
    com_attempts ++;


    /** ########## Step 2 ##########
      * Transmits in interrupt mode a buffer pointed by pTxData using UART.
      */

    hal_status = HAL_UART_Transmit_IT(pUART, pTxData, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the UART transmission. Restart the communication */
      continue;
    }


    /** ########## Step 3 ##########
      * Waits for one of these UART interrupts: write transfer complete or transfer error.
      */

    while ((TxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An UART interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* Error while uart transmission. Restart the communication */
      continue;
    }


    /** ########## Step 4 ##########
      * Receives in interrupt mode a buffer using UART.
      */

    hal_status = HAL_UART_Receive_IT(pUART, RxBuffer, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the UART reception. Restart the communication */
      continue;
    }


    /** ########## Step 5 ##########
      * Waits for one of these UART interrupts: read transfer complete or transfer error.
      */
    while ((RxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An UART interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* Error while uart reception. Restart the communication */
      continue;
    }


    /** ########## Step 6 ##########
      * Checks the correctness of the received buffer after the data transfer is completed.
      */
    return_status = HandleTransferCplt();

  } /* end while */

  return return_status;
} /* end app_process */


/** Transmission end of transfer completed callback
  * @user This implementation of the UART Tx transfer complete callback can be customized.
  * This function is executed when the Tx transfer complete interrupt is generated.
  */
static void TxTransferCpltCallback(hal_uart_handle_t *huart)
{
  TxTransferComplete = 1U;
}


/** Reception end of transfer completed callback
  * @user This implementation of the UART Rx transfer complete callback can be customized.
  * This function is executed when the Rx transfer complete interrupt is generated.
  */

static void RxTransferCpltCallback(hal_uart_handle_t *huart, uint32_t size_byte, hal_uart_rx_event_types_t rx_event)
{
  RxTransferComplete = 1U;
}


/** UART transfer error callback
  * @user This implementation of the UART transfer error callback can be customized.
  * This function is executed when the transfer error interrupt is generated.
  */

static void TransferErrorCallback(hal_uart_handle_t *huart)
{
  TransferError = 1U;
}


/** De-initializes the UART instance before leaving the scenario.
  * In this example, app_deinit is never called and it is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  mx_example_uart_deinit();

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
    return_status = EXEC_STATUS_OK;
  }

  return return_status;
} /* end HandleTransferCplt */


