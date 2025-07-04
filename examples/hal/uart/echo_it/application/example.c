/**
  ******************************************************************************
  * file           : example.c
  * brief   This sample code shows how to use UART HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          IT transfer.
  *          The communication is done with the Hyperterminal PC application.
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

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* USER CODE END EM */

/* Size of Reception buffer */
#define RXBUFFERSIZE              10U
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_uart_handle_t *pUART; /* Pointer referencing the UART handle from the generated code */

volatile uint8_t TxTransferComplete; /* Set to 1 if the transmit sequence is correctly completed */
volatile uint8_t RxTransferComplete; /* Set to 1 if the receive sequence is correctly completed */
volatile uint8_t TransferError;      /* Set to 1 if a transmission or a reception error is detected */

/* Buffers used for reception */
uint8_t BufferA[RXBUFFERSIZE];
uint8_t BufferB[RXBUFFERSIZE];
uint8_t *TxBuffer = BufferA;

/* Message to be sent at the start */
static const uint8_t TxStartMessage[] = "\r\n\nPlease use the input line below to send data to the device\n\r\
[input]<<";

/* Private functions prototype -----------------------------------------------*/
static void TxTransferCpltCallback(hal_uart_handle_t *pUART);
static void RxTransferCpltCallback(hal_uart_handle_t *pUART, uint32_t size_byte, hal_uart_rx_event_types_t rx_event);
static void TransferErrorCallback(hal_uart_handle_t *pUART);

/** ########## Step 1 ##########
  * The init of the UART instance and IT instances is triggered by the applicative code.
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

  /* Clear the UART interrupts flags before starting a new transfer */
  TxTransferComplete = 0U;
  RxTransferComplete = 0U;
  TransferError = 0U;

  /** ########## Step 2 ##########
    * Transmits in interrupt mode a start message using UART.
    */
  hal_status = HAL_UART_Transmit_IT(pUART, TxStartMessage, sizeof(TxStartMessage) - 1);
  if (hal_status != HAL_OK)
  {
    /* An error occurs at the startup of the UART transmission. */
    return return_status;
  }

  /** ########## Step 3 ##########
    * Waits for one of these UART interrupts: transmit sequence complete or transfer error.
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
    /* Error while UART transmission. */
    return return_status;
  }

  /** ########## Step 4 ##########
    * Start the first reception in interrupt mode using UART.
    */

  uint8_t *RxBuffer = BufferA;
  hal_status = HAL_UART_Receive_IT(pUART, RxBuffer, RXBUFFERSIZE);
  if (hal_status != HAL_OK)
  {
    /* An error occurs at the startup of the UART reception. */
    return return_status;
  }

  while (return_status == EXEC_STATUS_ERROR)
  {

    /** ########## Step 5 ##########
      * Waits for one of these UART interrupts: receive sequence complete or transfer error.
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
      /* Error while UART reception. */
      return return_status;
    }

    /* Toggle the buffer pointers */
    uint8_t *TxBuffer = RxBuffer;
    if (RxBuffer == BufferA)
    {
      RxBuffer = BufferB;
    }
    else
    {
      RxBuffer = BufferA;
    }

    /** ########## Step 6 ##########
      * Start reception on the next buffer
      */
    RxTransferComplete = 0U;
    hal_status = HAL_UART_Receive_IT(pUART, RxBuffer, RXBUFFERSIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the UART reception. */
      return return_status;
    }

    /** ########## Step 7 ##########
      * Transmits the received buffer back to the user.
      */
    TxTransferComplete = 0U;
    TransferError = 0U;

    hal_status = HAL_UART_Transmit_IT(pUART, TxBuffer, RXBUFFERSIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the UART transmission. */
      return return_status;
    }

    /** ########## Step 8 ##########
      * Waits for one of these UART interrupts: receive sequence complete or transfer error.
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
      /* Error while UART transmission. */
      return return_status;
    }
  }

  return return_status;
} /* end app_process */


/** Transmission end of transfer completed callback */
static void TxTransferCpltCallback(hal_uart_handle_t *huart)
{
  TxTransferComplete = 1U;
}

/** Reception end of transfer completed callback */
static void RxTransferCpltCallback(hal_uart_handle_t *huart, uint32_t size_byte, hal_uart_rx_event_types_t rx_event)
{
  RxTransferComplete = 1U;
}

/** UART transfer error callback */
static void TransferErrorCallback(hal_uart_handle_t *huart)
{
  TransferError = 1U;
}

/** De-initializes the UART and IT instances before leaving the scenario. */
app_status_t app_deinit(void)
{
  mx_example_uart_deinit();
  return EXEC_STATUS_OK;
} /* end app_deinit */
