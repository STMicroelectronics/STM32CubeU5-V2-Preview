/**
  ******************************************************************************
  * file           : example.c
  * brief          : The controller side in a interrupt mode USART communication
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
/* @user: set the payload size in bytes. The USART message is a string made of this payload and terminated by '\0'. */
#define USART_PAYLOAD_SIZE 42U
/**
  * Size of the TX and RX buffers in bytes.
  * +1 is used to store the null character as the transmitted USART message is a null-terminated string.
  */
#define BUFFER_SIZE (USART_PAYLOAD_SIZE + 1U)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_usart_handle_t *pUSART; /* Pointer referencing the USART handle from the generated code */

volatile uint8_t TxTransferComplete; /* Set to 1 if the write transfer is correctly completed */
volatile uint8_t RxTransferComplete; /* Set to 1 if the read transfer is correctly completed */
volatile uint8_t TransferError;      /* Set to 1 if a transmission or a reception error is detected */

/** BufferA, BufferB: fixed-size buffers to transfer alternately.
  * @user: it is possible to modify the buffers content and length, update BUFFER_SIZE if necessary.
  */
static const uint8_t BufferA[BUFFER_SIZE] = "USART Two Boards Communication - Message A";
static const uint8_t BufferB[BUFFER_SIZE] = "USART Two Boards Communication - Message B";
/* Pointer to the buffer used for transmission */
const uint8_t *pTxData = NULL;
/* Buffer used for reception */
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

/* Private functions prototype -----------------------------------------------*/
static inline void UpdateBuffers(void);
static app_status_t HandleTransferCplt(void);

/* Functions allowing the user to configure dynamically the USART callbacks instead of weak functions */
static void TxTransferCpltCallback(hal_usart_handle_t *pUSART);
static void RxTransferCpltCallback(hal_usart_handle_t *pUSART);
static void TransferErrorCallback(hal_usart_handle_t *pUSART);


/** ########## Step 1 ##########
  * The init of the USART instance is triggered by the applicative code.
  * The user callbacks for USART TX/RX transfer completed and transfer error are registered.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pUSART = mx_example_usart_init();

  if (pUSART == NULL)
  {
    goto _app_init_exit;
  }

  /* Register the USART callbacks */
  if (HAL_USART_RegisterTxCpltCallback(pUSART, TxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_USART_RegisterRxCpltCallback(pUSART, RxTransferCpltCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_USART_RegisterErrorCallback(pUSART, TransferErrorCallback) != HAL_OK)
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
  hal_status_t hal_status;   /* memorizes the HAL status of the USART TX/RX operations */
  uint32_t com_attempts = 0U; /* memorizes the number of attempts made to exchange a message between the boards */

  UpdateBuffers();

  while ((com_attempts < MAX_COM_ATTEMPTS) && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear the USART interrupts flags before starting a new transfer */
    TxTransferComplete = 0U;
    RxTransferComplete = 0U;
    TransferError = 0U;

    /* Start a new communication attempt */
    com_attempts ++;


    /** ########## Step 2 ##########
      * Transmits in interrupt mode a buffer pointed by pTxData using USART.
      */

    hal_status = HAL_USART_Transmit_IT(pUSART, pTxData, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the USART transmission. Restart the communication */
      continue;
    }


    /** ########## Step 3 ##########
      * Waits for one of these USART interrupts: write transfer complete or transfer error.
      */

    while ((TxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An USART interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* Error while usart transmission. Restart the communication */
      continue;
    }


    /** ########## Step 4 ##########
      * Receives in interrupt mode a buffer using USART.
      */

    hal_status = HAL_USART_Receive_IT(pUSART, RxBuffer, BUFFER_SIZE);
    if (hal_status != HAL_OK)
    {
      /* An error occurs at the startup of the USART reception. Restart the communication */
      continue;
    }


    /** ########## Step 5 ##########
      * Waits for one of these USART interrupts: read transfer complete or transfer error.
      */
    while ((RxTransferComplete == 0) && (TransferError == 0))
    {
      /** Put the CPU in Wait For Interrupt state. An USART interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the interrupts. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError == 1)
    {
      /* Error while usart reception. Restart the communication */
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
  * @user This implementation of the USART Tx transfer complete callback can be customized.
  * This function is executed when the Tx transfer complete interrupt is generated.
  */
static void TxTransferCpltCallback(hal_usart_handle_t *husart)
{
  TxTransferComplete = 1U;
}


/** Reception end of transfer completed callback
  * @user This implementation of the USART Rx transfer complete callback can be customized.
  * This function is executed when the Rx transfer complete interrupt is generated.
  */

static void RxTransferCpltCallback(hal_usart_handle_t *husart)
{
  RxTransferComplete = 1U;
}


/** USART transfer error callback
  * @user This implementation of the USART transfer error callback can be customized.
  * This function is executed when the transfer error interrupt is generated.
  */

static void TransferErrorCallback(hal_usart_handle_t *husart)
{
  TransferError = 1U;
}


/** De-initializes the USART instance before leaving the scenario.
  * In this example, app_deinit is never called and it is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  mx_example_usart_deinit();

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


