/**
  ******************************************************************************
  * file           : example.c
  * brief          : The responder side in a interrupt mode UART communication
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
/* @user: must be equal to the size (in bytes) of the buffer received from the controller */
#define BUFFER_SIZE 42U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_uart_handle_t *pUART; /* Pointer referencing the UART handle from the generated code */

volatile uint8_t TxTransferComplete; /* Set to 1 if the write transfer is correctly completed */
volatile uint8_t RxTransferComplete; /* Set to 1 if the read transfer is correctly completed */
volatile uint8_t TransferError;      /* Set to 1 if a transmission or a reception error is detected */

/* Buffer used for reception (sent back to the controller)*/
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

/* Private functions prototype -----------------------------------------------*/
static app_status_t HandleTransferCplt(void);

/* Functions allowing the user to configure dynamically the UART callbacks instead of weak functions */
static void TxReceiverCpltCallback(hal_uart_handle_t *pUART);
static void RxReceiverCpltCallback(hal_uart_handle_t *pUART, uint32_t size_byte, hal_uart_rx_event_types_t rx_event);
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
  if (HAL_UART_RegisterTxCpltCallback(pUART, TxReceiverCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_UART_RegisterRxCpltCallback(pUART, RxReceiverCpltCallback) != HAL_OK)
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
  uint32_t com_attempts = 0; /* memorizes the number of attempts made to exchange a message between the boards */

  /* Clear the Rx buffer before starting a new transfer */
  memset(RxBuffer, 0U, BUFFER_SIZE);

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear the UART interrupts flags before starting a new transfer */
    TxTransferComplete = 0U;
    RxTransferComplete = 0U;
    TransferError = 0U;

    /* Start a new communication attempt */
    com_attempts ++;

    /** ########## Step 2 ##########
      * Receives in interrupt mode a buffer containing a null-terminated string using UART.
      */

    hal_status = HAL_UART_Receive_IT(pUART, RxBuffer, BUFFER_SIZE);

    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the UART reception. Restart the communication */
      continue;
    }

    /** ########## Step 3 ##########
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
      /* Error when uart reception. Restart the communication */
      continue;
    }

    /** ########## Step 4 ##########
      * Transmits in interrupt mode a buffer using UART.
      */

    hal_status = HAL_UART_Transmit_IT(pUART, RxBuffer, BUFFER_SIZE);

    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the UART transmission. Restart the communication */
      continue;
    }

    /** ########## Step 5 ##########
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
      /* Error when uart transmission. Restart the communication */
      continue;
    }


    /* Report the communication status: Data Transfer completed */

    return_status = HandleTransferCplt();

  } /* end while */

  return return_status;
} /* end app_process */


/** Transmission end of transfer completed callback
  * @user This implementation of the UART Tx transfer complete callback can be customized.
  * This function is executed when the Tx transfer complete interrupt is generated.
  */
static void TxReceiverCpltCallback(hal_uart_handle_t *huart)
{
  TxTransferComplete = 1U;
}


/** Reception end of transfer completed callback
  * @user This implementation of the UART Rx transfer complete callback can be customized.
  * This function is executed when the Rx transfer complete interrupt is generated.
  */

static void RxReceiverCpltCallback(hal_uart_handle_t *huart, uint32_t size_byte, hal_uart_rx_event_types_t rx_event)
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


/** brief:  This function is executed when the data transfer is completed.
  * param:  none
  * retval: example status
  */
static app_status_t HandleTransferCplt(void)
{
  return EXEC_STATUS_OK;
} /* end HandleTransferCplt */

