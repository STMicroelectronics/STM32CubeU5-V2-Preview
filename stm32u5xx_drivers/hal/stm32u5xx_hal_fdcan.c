/**
  ******************************************************************************
  * @file    stm32u5xx_hal_fdcan.c
  * @brief   FDCAN HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Flexible DataRate Controller Area Network
  *          (FDCAN) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Configuration and Control functions
  *           + Peripheral State and Error functions
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

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

#if defined(FDCAN1)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup FDCAN FDCAN
  * @{
# How to use this driver

1.Declare a hal_fdcan_handle_t handle structure and initialize the FDCAN driver with an FDCAN instance.

2.Initialize the FDCAN peripheral using HAL_FDCAN_Init() function. The FDCAN clock is enabled inside
   HAL_FDCAN_Init() if USE_HAL_FDCAN_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

3.Configure the low level hardware (GPIO, CLOCK, NVIC...etc)
- Enable the FDCAN clock if USE_HAL_FDCAN_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO
- FDCAN pins configuration:
  - Enable the clock for the FDCAN GPIOs
  - NVIC configuration if you need to use interrupt process

4.Configure the peripheral using the HAL_FDCAN_SetConfig()
- If needed, configure and retrieve the reception filters and optional features using the following configuration
  functions:
  - HAL_FDCAN_SetConfig()
  - HAL_FDCAN_GetConfig()
  - HAL_FDCAN_SetNominalBitTiming()
  - HAL_FDCAN_GetNominalBitTiming()
  - HAL_FDCAN_SetDataBitTiming()
  - HAL_FDCAN_GetDataBitTiming()
  - HAL_FDCAN_SetClockDivider()
  - HAL_FDCAN_GetClockDivider()
  - HAL_FDCAN_SetFilter()
  - HAL_FDCAN_GetFilter()
  - HAL_FDCAN_SetGlobalFilter()
  - HAL_FDCAN_GetGlobalFilter()
  - HAL_FDCAN_SetExtendedIdMask()
  - HAL_FDCAN_GetExtendedIdMask()
  - HAL_FDCAN_SetRxFifoOverwrite()
  - HAL_FDCAN_GetRxFifoOverwrite()
  - HAL_FDCAN_SetRamWatchdog()
  - HAL_FDCAN_GetRamWatchdog()
  - HAL_FDCAN_SetConfigTimestampCounter()
  - HAL_FDCAN_GetConfigTimestampCounter()
  - HAL_FDCAN_GetTimestampCounter()
  - HAL_FDCAN_SetConfigTimeoutCounter()
  - HAL_FDCAN_GetConfigTimeoutCounter()
  - HAL_FDCAN_GetTimeoutCounter()
  - HAL_FDCAN_EnableTimeoutCounter()
  - HAL_FDCAN_DisableTimeoutCounter()
  - HAL_FDCAN_ResetTimeoutCounter()
  - HAL_FDCAN_SetConfigTxDelayCompensation()
  - HAL_FDCAN_GetConfigTxDelayCompensation()
  - HAL_FDCAN_EnableTxDelayCompensation()
  - HAL_FDCAN_DisableTxDelayCompensation()
  - HAL_FDCAN_EnableISOMode()
  - HAL_FDCAN_DisableISOMode()
  - HAL_FDCAN_EnableEdgeFiltering()
  - HAL_FDCAN_DisableEdgeFiltering()
  - HAL_FDCAN_SetMode()
  - HAL_FDCAN_GetMode()
  - HAL_FDCAN_SetFrameFormat()
  - HAL_FDCAN_GetFrameFormat()
  - HAL_FDCAN_SetAutoRetransmission()
  - HAL_FDCAN_GetAutoRetransmission()
  - HAL_FDCAN_SetTransmitPause()
  - HAL_FDCAN_GetTransmitPause()
  - HAL_FDCAN_SetProtocolException()
  - HAL_FDCAN_GetProtocolException()
  - HAL_FDCAN_GetClockFreq()
  - HAL_FDCAN_SetTxMode()
  - HAL_FDCAN_GetTxMode()

5.The control functions allow the user application to initiate Rx/TX transfer over the FDCAN bus, either sending frames
or receiving frames or checking and managing the whole transfer process and resources (status, buffers, events).
Most of the control functions can be called in IDLE, ACTIVE or POWER_DOWN states, however some control functions are
restricted to given states, for example HAL_FDCAN_Start() can be called in IDLE and ACTIVE but not in POWER_DOWN.
The control functions include the following set of functions:

  - HAL_FDCAN_Start()
  - HAL_FDCAN_Stop()
  - HAL_FDCAN_ReqTransmitMsgFromFIFOQ()
  - HAL_FDCAN_GetTxFifoStatus()
  - HAL_FDCAN_GetLatestTxFifoQRequestBuffer()
  - HAL_FDCAN_GetTxFifoFreeLevel()
  - HAL_FDCAN_ReqAbortOfTxBuffer()
  - HAL_FDCAN_GetTxEvent()
  - HAL_FDCAN_GetTxBufferMessageStatus()
  - HAL_FDCAN_GetReceivedMessage()
  - HAL_FDCAN_GetRxFifoFillLevel()
  - HAL_FDCAN_GetHighPriorityMessageStatus()
  - HAL_FDCAN_GetProtocolStatus()
  - HAL_FDCAN_GetErrorCounters()
  - HAL_FDCAN_DisableRestrictedOperationMode()
  - HAL_FDCAN_EnableRestrictedOperationMode()
  - HAL_FDCAN_IsEnabledRestrictedOperationMode()

To start the FDCAN module, the user application must call HAL_FDCAN_Start() function. At this level the node is active
on the bus.
- It can send and receive messages:
  - The following Tx control functions can be called when the FDCAN module is started or in Power Down mode, but it
    must be operating only when the FDCAN is in Active mode.
    - HAL_FDCAN_ReqTransmitMsgFromFIFOQ()
    - HAL_FDCAN_ReqAbortOfTxBuffer()

- After having submitted a Tx request in Tx FIFO or Queue, it is possible to get Tx buffer location used to
 place the Tx request thanks to HAL_FDCAN_GetLatestTxFifoQRequestBuffer() function. It is then possible to abort
 later on the corresponding Tx Request using HAL_FDCAN_ReqAbortOfTxBuffer() function.

- When a message is received into the FDCAN message RAM, it can be retrieved using
 the HAL_FDCAN_GetReceivedMessage() function.

- Calling the HAL_FDCAN_Stop() function stops the FDCAN module by entering it to initialization mode and
 re-enabling access to configuration registers through the configuration functions listed here above.

6.Polling mode operation.
- Reception and transmission states can be monitored through the following functions:
  - HAL_FDCAN_GetTxBufferMessageStatus(): this function checks if a transmission request is pending on the selected
    Tx buffer.
  - HAL_FDCAN_GetRxFifoFillLevel(): this function retrieves the number of elements stored in Rx FIFO 0 or RX FIFO 1
    according to the passed parameter.
  - HAL_FDCAN_GetTxFifoFreeLevel(): this function retrieves the number of consecutive free Tx FIFO elements.

7.Interrupt mode operation.
- The interrupt management process can be configured using the HAL_FDCAN_SetInterruptGroupsToLine() to associate one
  or several interrupt group (the interrupt groups can be OR-ed) to an interrupt line.
  It is also possible to know which interrupt line is connected to an interrupt group using the
  HAL_FDCAN_GetLineFromInterruptGroup() function. The latter function applies to only one interrupt group.

- There are two interrupt lines: line 0 and 1. By default, all interrupt groups are assigned to line 0. Interrupt lines
  can be enabled using HAL_FDCAN_EnableInterruptLines() function. The user can check the status of interrupt Line
  (Enabled or Disabled) using the HAL_FDCAN_IsEnabledInterruptLine() function, the latter applies to only one
  interrupt line: Interrupt Line 0 or Interrupt Line 1.

- Interrupts are enabled using HAL_FDCAN_EnableInterrupts() function, the interrupt sources can be OR-ed.Then, the
  process can be controlled  through one of the available user callbacks: HAL_FDCAN_xxxCallback(). The user can
  check the status of interrupt (Enabled or Disabled) using the HAL_FDCAN_IsEnabledInterrupt() function, the
  latter applies to only one interrupt signal.

- For Transmission Complete Interrupt and Transmission Cancellation Finished interrupt, the buffer(s) on which the
  interrupt applies, has to be enabled with the respective HAL_FDCAN_EnableTxBufferCompleteInterrupts() and
  HAL_FDCAN_EnableTxBufferCancellationInterrupts() functions. The buffer can be a single buffer or a combination of
  several buffers. The same way, those buffers can be disconnected from their respective interrupts signals by using
  HAL_FDCAN_DisableTxBufferCompleteInterrupts() and HAL_FDCAN_DisableTxBufferCancellationInterrupts() functions.
  If the user wants to check the status of the buffer (enabled or disabled), the functions
  HAL_FDCAN_IsEnabledTxBufferCompleteInterrupt() and HAL_FDCAN_IsEnabledTxBufferCancellationInterrupt() have to be
  used, those functions deal with one single buffer only and cannot be OR-ed contrary to the associated previous
  Enable and Disable functions.

- In the same way, interrupt lines and interrupts can be disabled using the dedicated functions respectively
  HAL_FDCAN_DisableInterruptLines() and  HAL_FDCAN_DisableInterrupts() functions.

8.Callback registration
- The compilation define USE_HAL_FDCAN_REGISTER_CALLBACKS when set to 1 allows the user to configure dynamically the
driver callbacks.

- For specific callbacks TxEventFifoCallback, RxFifo0Callback, RxFifo1Callback, TxBufferCompleteCallback,
  TxBufferAbortCallback, HighPriorityMessageCallback, TxFifoEmptyCallback, TimeStampWrapAroundCallback,
  and ErrorCallback(), use dedicated register callbacks, respectively:
  - HAL_FDCAN_RegisterRxFifo0Callback(),
  - HAL_FDCAN_RegisterRxFifo1Callback(),
  - HAL_FDCAN_RegisterTxEventFifoCallback(),
  - HAL_FDCAN_RegisterTxBufferCompleteCallback(),
  - HAL_FDCAN_RegisterTxBufferAbortCallback(),
  - HAL_FDCAN_RegisterTxFifoEmptyCallback(),
  - HAL_FDCAN_RegisterHighPriorityMessageCallback(),
  - HAL_FDCAN_RegisterTimestampWraparoundCallback(),
  - HAL_FDCAN_RegisterErrorCallback(),

- By default, after the HAL_FDCAN_Init() and when the state is HAL_FDCAN_STATE_INIT, all callbacks are set to the
  corresponding weak functions:
    - examples HAL_FDCAN_ErrorCallback().

- Callbacks can be registered in HAL_FDCAN_STATE_INIT or HAL_FDCAN_STATE_IDLE states only.

- When the compilation defines USE_HAL_FDCAN_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
  feature is not available and all callbacks are set to the corresponding weak functions.

9.Acquire/Release the FDCAN bus
- When the compilation flag USE_HAL_MUTEX is set to 1, it allows the user to acquire/reserve the whole FDCAN bus for
  executing process. The HAL_FDCAN_Acquire and HAL_FDCAN_Release are based on the HAL OS abstraction layer
  (stm32_hal_os.c/.h osal):
  - HAL_FDCAN_AcquireBus() for acquiring the bus or wait for it.
  - HAL_FDCAN_ReleaseBus() for releasing the bus.

- When the compilation flag USE_HAL_MUTEX is set to 0 or not defined, HAL_FDCAN_AcquireBus/HAL_FDCAN_ReleaseBus
  are not available.

10.Configuration inside the FDCAN driver

Config defines                  | Description          | Default value      | Note
--------------------------------| ---------------------| ------------------ | ----------------------------------------
USE_HAL_FDCAN_CLK_ENABLE_MODEL  | from hal_conf.h      | HAL_CLK_ENABLE_NO  | Enable the gating of the peripheral clock
USE_HAL_FDCAN_MODULE            | from hal_conf.h      | 1  | When set, HAL FDCAN module is enabled
USE_HAL_FDCAN_GET_LAST_ERRORS   | from hal_conf.h      | 0  | Enable the get last process error
USE_HAL_FDCAN_USER_DATA         | from hal_conf.h      | 0  | Enable the set/get user data
USE_HAL_FDCAN_REGISTER_CALLBACKS| from hal_conf.h      | 0  | Enable the register callbacks assert
USE_HAL_CHECK_PARAM             | from hal_conf.h      | 0  | Parameters (pointers or sizes) are checked in runtime
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h      | 0  | Allows to check the HAL FDCAN state transition in run time
USE_HAL_MUTEX                   | from hal_conf.h      | 0  | Enable the acquire/release bus services
USE_ASSERT_DBG_PARAM            | from PreProcessor env| NA | Enable the params assert
USE_ASSERT_DBG_STATE            | from PreProcessor env| NA | Enable the state assert
 */

#if defined(USE_HAL_FDCAN_MODULE) && (USE_HAL_FDCAN_MODULE == 1)

/* Private constants ---------------------------------------------------------*/
/** @defgroup FDCAN_Private_Constants FDCAN Private Constants
  * @{
  */

#define HAL_FDCAN_IR_MASK           ((uint32_t)0x00FFFFFFU) /*!< FDCAN interrupts mask                       */
#define HAL_FDCAN_IE_MASK           ((uint32_t)0x00FFFFFFU) /*!< FDCAN interrupts enable mask                */
#define HAL_FDCAN_ILS_MASK          ((uint32_t)0x0000007FU) /*!< FDCAN interrupts group mask in ILS register */
#define FDCAN_TIMEOUT_VALUE         (10U)                   /*!< To set a 10ms timeout                       */

#define FDCAN_TX_EVENT_FIFO_MASK (FDCAN_IR_TEFL | FDCAN_IR_TEFF | FDCAN_IR_TEFN) /*!< Define the Tx Event FIFO IT related mask */
#define FDCAN_RX_FIFO0_MASK (FDCAN_IR_RF0L | FDCAN_IR_RF0F | FDCAN_IR_RF0N)      /*!< Define the Rx FIFO0 IT related mask      */
#define FDCAN_RX_FIFO1_MASK (FDCAN_IR_RF1L | FDCAN_IR_RF1F | FDCAN_IR_RF1N)      /*!< Define the Rx FIFO1 IT related mask      */

#define FDCAN_ERROR_MASK (FDCAN_IR_ELO | FDCAN_IR_WDI | FDCAN_IR_PEA | FDCAN_IR_PED | FDCAN_IR_ARA | FDCAN_IR_TOO \
                          | FDCAN_IR_MRAF | FDCAN_IR_BO | FDCAN_IR_EP |  FDCAN_IR_EW) /*!< Define the Error IT related mask */

#define FDCAN_CLOCK_DIVIDER_MASK      (15U) /*!< Mask for clock divider */

#define SRAMCAN_FLS_NBR  (28U)      /*!< Max. Filter List Standard Number      */
#define SRAMCAN_FLE_NBR  (8U)       /*!< Max. Filter List Extended Number      */
#define SRAMCAN_RF0_NBR  (3U)       /*!< RX FIFO 0 Elements Number             */
#define SRAMCAN_RF1_NBR  (3U)       /*!< RX FIFO 1 Elements Number             */
#define SRAMCAN_TEF_NBR  (3U)       /*!< TX Event FIFO Elements Number         */
#define SRAMCAN_TFQ_NBR  (3U)       /*!< TX FIFO/Queue Elements Number         */

#define SRAMCAN_FLS_SIZE (1U * 4U)  /*!< Filter Standard Element Size in bytes */
#define SRAMCAN_FLE_SIZE (2U * 4U)  /*!< Filter Extended Element Size in bytes */
#define SRAMCAN_RF0_SIZE (18U * 4U) /*!< RX FIFO 0 Elements Size in bytes      */
#define SRAMCAN_RF1_SIZE (18U * 4U) /*!< RX FIFO 1 Elements Size in bytes      */
#define SRAMCAN_TEF_SIZE (2U * 4U)  /*!< TX Event FIFO Elements Size in bytes  */
#define SRAMCAN_TFQ_SIZE (18U * 4U) /*!< TX FIFO/Queue Elements Size in bytes  */

#define SRAMCAN_FLSSA ((uint32_t)0)                                                      /*!<  Filter list standard start address */
#define SRAMCAN_FLESA ((uint32_t)(SRAMCAN_FLSSA + (SRAMCAN_FLS_NBR * SRAMCAN_FLS_SIZE))) /*!<  Filter list extended start address */
#define SRAMCAN_RF0SA ((uint32_t)(SRAMCAN_FLESA + (SRAMCAN_FLE_NBR * SRAMCAN_FLE_SIZE))) /*!<  Rx FIFO 0 start address            */
#define SRAMCAN_RF1SA ((uint32_t)(SRAMCAN_RF0SA + (SRAMCAN_RF0_NBR * SRAMCAN_RF0_SIZE))) /*!<  Rx FIFO 1 start address            */
#define SRAMCAN_TEFSA ((uint32_t)(SRAMCAN_RF1SA + (SRAMCAN_RF1_NBR * SRAMCAN_RF1_SIZE))) /*!<  Tx event FIFO start address        */
#define SRAMCAN_TFQSA ((uint32_t)(SRAMCAN_TEFSA + (SRAMCAN_TEF_NBR * SRAMCAN_TEF_SIZE))) /*!<  Tx FIFO/Queue start address        */
#define SRAMCAN_SIZE  ((uint32_t)(SRAMCAN_TFQSA + (SRAMCAN_TFQ_NBR * SRAMCAN_TFQ_SIZE))) /*!<  Message RAM size                   */

#define FDCAN_STD_ID_MAX_VALUE          (0x7FFU)          /*!< Max value id of the standard filter                    */
#define FDCAN_STD_ID_MASK               (0x7FFU)          /*!< Mask for the standard filter id                        */
#define FDCAN_EXT_ID_MAX_VALUE          (0x1FFFFFFFU)     /*!< Max value id of the extended filter                    */
#define FDCAN_EXT_ID_MASK               (0x1FFFFFFFU)     /*!< Mask for the extended filter id                        */
#define FDCAN_STD_FILTER_TYPE_POS       (30U)             /*!< Position of the standard filter type field             */
#define FDCAN_STD_FILTER_CONFIG_POS     (27U)             /*!< Position of the standard filter configuration field    */
#define FDCAN_STD_FILTER_ID1_POS        (16U)             /*!< Position of the standard id1 field                     */
#define FDCAN_STD_FILTER_ID2_POS        (0U)              /*!< Position of the standard id2 field                     */
#define FDCAN_EXT_FILTER_CONFIG_POS     (29U)             /*!< Position of the extended filter configuration field    */
#define FDCAN_EXT_FILTER_TYPE_POS       (30U)             /*!< Position of the extended filter type field             */
#define FDCAN_EXT_FILTER_ID1_POS        (0U)              /*!< Position of the extended id1 field                     */
#define FDCAN_EXT_FILTER_ID2_POS        (0U)              /*!< Position of the extended id2 field                     */
#define FDCAN_STD_FILTER_TYPE_MASK      (3U)              /*!< Extended filter id1 mask field                         */
#define FDCAN_STD_FILTER_CONFIG_MASK    (7U)              /*!< Extended filter id1 mask field                         */
#define FDCAN_STD_ID1_MASK              FDCAN_STD_ID_MASK /*!< Extended filter id1 mask field                         */
#define FDCAN_STD_ID2_MASK              FDCAN_STD_ID_MASK /*!< Extended filter id1 mask field                         */
#define FDCAN_STD_FILTER_ID_POS         (18U)             /*!< ID standard filter position in Tx/Rx/Event header      */
#define FDCAN_EXT_FILTER_CONFIG_MASK    (7U)              /*!< Extended filter id1 mask field                         */
#define FDCAN_EXT_FILTER_TYPE_MASK      (3U)              /*!< Extended filter type mask field                        */
#define FDCAN_EXT_FILTER_ID1_MASK       FDCAN_EXT_ID_MASK /*!< Extended filter id1 mask field                         */
#define FDCAN_EXT_FILTER_ID2_MASK       FDCAN_EXT_ID_MASK /*!< Extended filter id2 mask field                         */
#define FDCAN_WATCHDOG_VALUE_MAX        (0xFFU)           /*!< Max value of the RAM watchdog                          */
#define FDCAN_MESSAGE_MARKER_MAX_VALUE  (0xFFU)           /*!< Max value of the message marker                        */
#define FDCAN_TIMEOUT_VALUE_MAX         (0xFFFFU)         /*!< Max value of the timeout counter                       */
#define FDCAN_TX_DELAY_COMP_VALUE_MAX   (0x7FU)           /*!< Max value for Tx delay compensation offset and
                                                               window length                                          */
#define FDCAN_FRAME_FORMAT_MASK         (0x00000300U)     /*!< mask to read the frame format bits in CCCR             */
#define FDCAN_TX_CPL_BUFFER0_MASK       (0x01U)           /*!< mask all the bits of the field except bit 0            */
#define FDCAN_TX_CPL_BUFFER1_MASK       (0x02U)           /*!< mask all the bits of the field except bit 1            */
#define FDCAN_TX_CPL_BUFFER2_MASK       (0x04U)           /*!< mask all the bits of the field except bit 2            */
#define FDCAN_TX_CPL_BUFFER_ALL_MASK    (FDCAN_TX_CPL_BUFFER0_MASK   \
                                         | FDCAN_TX_CPL_BUFFER1_MASK \
                                         | FDCAN_TX_CPL_BUFFER2_MASK) /*!< mask all the three lsb bits of the field   */
#define FDCAN_TX_ABORT_BUFFER0_MASK     (0x01U)           /*!< mask all the bits of the field except bit 0            */
#define FDCAN_TX_ABORT_BUFFER1_MASK     (0x02U)           /*!< mask all the bits of the field except bit 1            */
#define FDCAN_TX_ABORT_BUFFER2_MASK     (0x04U)           /*!< mask all the bits of the field except bit 2            */
#define FDCAN_TX_ABORT_BUFFER_ALL_MASK  (FDCAN_TX_ABORT_BUFFER0_MASK   \
                                         | FDCAN_TX_ABORT_BUFFER1_MASK \
                                         | FDCAN_TX_ABORT_BUFFER2_MASK) /*!< Mask all the three lsb bits of the field */

#define FDCAN_IT_LINE0_MASK             (0x01UL)          /*!< Mask all the bits of the field except EINT0            */
#define FDCAN_IT_LINE1_MASK             (0x02UL)          /*!< Mask all the bits of the field except EINT1            */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup FDCAN_Private_Macros FDCAN Private Macros
  * @{
  */

/**
  * @brief  Clear the specified FDCAN flags.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t.
  * @param  flag specifies the flags to clear.
  *         This parameter can be any combination of @arg FDCAN_Interrupt_Sources.
  */
#define FDCAN_CLEAR_FLAG(hfdcan, flag)                                       \
  do                                                                         \
  {                                                                          \
    FDCAN_GlobalTypeDef *p_fdcaninstance;                                    \
    p_fdcaninstance = (FDCAN_GlobalTypeDef *)((uint32_t)(hfdcan)->instance); \
    SET_BIT(p_fdcaninstance->IR, (flag));                                    \
  } while(0);

/*! Check if  the frame type value is valid */
#define IS_FDCAN_FRAME_FORMAT(format) (((format) == HAL_FDCAN_FRAME_CLASSIC_CAN)  \
                                       || ((format) == HAL_FDCAN_FRAME_FD_NO_BRS) \
                                       || ((format) == HAL_FDCAN_FRAME_FD_BRS))

/*! Check if  the transmit pause type is valid */
#define IS_FDCAN_TRANSMIT_PAUSE(transmit) (((transmit) == HAL_FDCAN_TRANSMIT_PAUSE_DISABLED)   \
                                           || ((transmit) == HAL_FDCAN_TRANSMIT_PAUSE_ENABLED))

/*! Check if  the protocol exception type is valid */
#define IS_FDCAN_PROTOCOL_EXCEPTION(protocol) (((protocol) == HAL_FDCAN_PROTOCOL_EXCEPTION_DISABLED)   \
                                               || ((protocol) == HAL_FDCAN_PROTOCOL_EXCEPTION_ENABLED))

/*! Check if  the auto retransmission type is valid */
#define IS_FDCAN_AUTO_RETRANSMISSION(transmission) (((transmission) == HAL_FDCAN_AUTO_RETRANSMISSION_DISABLED)   \
                                                    || ((transmission) == HAL_FDCAN_AUTO_RETRANSMISSION_ENABLED))

/*! Check if the mode value is valid */
#define IS_FDCAN_MODE(mode) (((mode) == HAL_FDCAN_MODE_NORMAL)                  \
                             || ((mode) == HAL_FDCAN_MODE_RESTRICTED_OPERATION) \
                             || ((mode) == HAL_FDCAN_MODE_BUS_MONITORING)       \
                             || ((mode) == HAL_FDCAN_MODE_INTERNAL_LOOPBACK)    \
                             || ((mode) == HAL_FDCAN_MODE_EXTERNAL_LOOPBACK))

/*! Check if the Clock Divider value is valid */
#define IS_FDCAN_CKDIV(ckdiv) (((ckdiv) == HAL_FDCAN_CLOCK_DIV1)     \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV2)  \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV4)  \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV6)  \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV8)  \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV10) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV12) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV14) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV16) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV18) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV20) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV22) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV24) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV26) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV28) \
                               || ((ckdiv) == HAL_FDCAN_CLOCK_DIV30))

/*! Check if the Nominal Prescaler value is valid */
#define IS_FDCAN_NOMINAL_PRESCALER(prescaler) (((prescaler) >= 1U) && ((prescaler) <= 512U))

/*! Check if the Nominal Jump Width value is valid */
#define IS_FDCAN_NOMINAL_SJW(sjw) (((sjw) >= 1U) && ((sjw) <= 128U))

/*! Check if the Nominal Time Segment 1 value is valid */
#define IS_FDCAN_NOMINAL_TSEG1(tseg1) (((tseg1) >= 1U) && ((tseg1) <= 256U))

/*! Check if the Nominal Time Segment 2 value is valid */
#define IS_FDCAN_NOMINAL_TSEG2(tseg2) (((tseg2) >= 1U) && ((tseg2) <= 128U))

/*! Check if the Data Prescaler value is valid */
#define IS_FDCAN_DATA_PRESCALER(prescaler) (((prescaler) >= 1U) && ((prescaler) <= 32U))

/*! Check if the Data Jump Width value is valid */
#define IS_FDCAN_DATA_SJW(sjw) (((sjw) >= 1U) && ((sjw) <= 16U))

/*! Check if the Data Time Segment 1 value is valid */
#define IS_FDCAN_DATA_TSEG1(tseg1) (((tseg1) >= 1U) && ((tseg1) <= 32U))

/*! Check if the Data Time Segment 2 value is valid */
#define IS_FDCAN_DATA_TSEG2(tseg2) (((tseg2) >= 1U) && ((tseg2) <= 16U))

/*! Check if the max value is below limits */
#define IS_FDCAN_MAX_VALUE(value, max) ((value) <= (max))

/*! Check if the Buffer Type value is valid */
#define IS_FDCAN_TX_FIFO_QUEUE_MODE(mode) (((mode) == HAL_FDCAN_TX_MODE_FIFO)     \
                                           || ((mode) == HAL_FDCAN_TX_MODE_QUEUE))

/*! Check if the ID (Standard or Extended) type value is valid */
#define IS_FDCAN_ID_TYPE(id_type) (((id_type) == HAL_FDCAN_ID_STANDARD)    \
                                   || ((id_type) == HAL_FDCAN_ID_EXTENDED))

/*! Check if the Tx mode is valid */
#define IS_FDCAN_TX_MODE(tx_mode) (((tx_mode) == HAL_FDCAN_TX_MODE_FIFO)    \
                                   || ((tx_mode) == HAL_FDCAN_TX_MODE_QUEUE))

/*! Check if the Filter configuration is valid */
#define IS_FDCAN_FILTER_CFG(config) (((config) == HAL_FDCAN_FILTER_DISABLE)          \
                                     || ((config) == HAL_FDCAN_FILTER_TO_RXFIFO0)    \
                                     || ((config) == HAL_FDCAN_FILTER_TO_RXFIFO1)    \
                                     || ((config) == HAL_FDCAN_FILTER_REJECT)        \
                                     || ((config) == HAL_FDCAN_FILTER_HP)            \
                                     || ((config) == HAL_FDCAN_FILTER_TO_RXFIFO0_HP) \
                                     || ((config) == HAL_FDCAN_FILTER_TO_RXFIFO1_HP))

/*! Check if the Tx location list is valid */
#define IS_FDCAN_TX_LOCATION_LIST(location) (((location) >= HAL_FDCAN_TX_BUFFER0)         \
                                             && ((location) <= (HAL_FDCAN_TX_BUFFER_ALL)))

/*! Check if the Tx event list is Empty */
#define IS_FDCAN_TX_EVENT_FIFO_NOT_EMPTY(fifo) (((fifo) & FDCAN_TXEFS_EFFL_Msk) != 0U)

/*! Check if the Tx fifo FULL */
#define IS_FDCAN_TX_FIFO_NOT_FULL(fifo) (((fifo) & FDCAN_TXFQS_TFQF_Msk) == 0U)

/*! Check if the Rx FIFO selection is valid */
#define IS_FDCAN_RX_FIFO(fifo) (((fifo) == HAL_FDCAN_RX_FIFO0)    \
                                || ((fifo) == HAL_FDCAN_RX_FIFO1))

/*! Check if the  Rx fifo 0 Fill level is not Empty */
#define IS_FDCAN_RX_EVENT_FIFO0_NOT_EMPTY(fifo) (((fifo) & FDCAN_RXF0S_F0FL_Msk) != 0U)

/*! Check if the  Rx fifo 1 Fill level is not Empty */
#define IS_FDCAN_RX_EVENT_FIFO1_NOT_EMPTY(fifo) (((fifo) & FDCAN_RXF1S_F1FL_Msk) != 0U)

/*! Check if the Rx FIFO Mode is valid */
#define IS_FDCAN_RX_FIFO_MODE(mode) (((mode) == HAL_FDCAN_RX_FIFO_BLOCKING)     \
                                     || ((mode) == HAL_FDCAN_RX_FIFO_OVERWRITE))

/*! Check that the address to retrieve the filter is valid */
#define IS_ADDRESS_VALID(address) ((address) != NULL)

/*! Check if the Standard filter type is valid */
#define IS_FDCAN_STD_FILTER_TYPE(type) (((type) == HAL_FDCAN_FILTER_RANGE)      \
                                        || ((type) == HAL_FDCAN_FILTER_DUAL)    \
                                        || ((type) == HAL_FDCAN_FILTER_CLASSIC))

/*! Check if the Extended filter type is valid */
#define IS_FDCAN_EXT_FILTER_TYPE(type) (((type) == HAL_FDCAN_FILTER_RANGE)            \
                                        || ((type) == HAL_FDCAN_FILTER_DUAL)          \
                                        || ((type) == HAL_FDCAN_FILTER_CLASSIC)       \
                                        || ((type) == HAL_FDCAN_FILTER_RANGE_NO_EIDM))

/*! Check if the Data Length Code value is valid */
#define IS_FDCAN_DLC(dlc) (((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_0BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_1BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_2BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_3BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_4BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_5BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_6BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_7BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_CAN_FDCAN_8BYTE) \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_12BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_16BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_20BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_24BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_32BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_48BYTE)    \
                           || ((dlc) == HAL_FDCAN_DATA_LGTH_FDCAN_64BYTE))

/*! Check if the buffer belongs to the allowed buffers list */
#define IS_FDCAN_TX_BUFFER_COMPLETE_ENABLE(buff) (((buff) > HAL_FDCAN_IT_TX_CPLT_BUFFER_0)         \
                                                  && ((buff) <= (HAL_FDCAN_IT_TX_CPLT_BUFFER_ALL)))

/*! Check if the buffer belongs to the allowed buffers list */
#define IS_FDCAN_TX_BUFFER_ABORT_ENABLE(buff) (((buff) > HAL_FDCAN_IT_TX_ABORT_BUFFER_0)         \
                                               && ((buff) <= (HAL_FDCAN_IT_TX_ABORT_BUFFER_ALL)))

/*! Check if only a single  bit is at 1 in BUFF_SEL */
#define IS_FDCAN_VALID_TX_CPL_BUFFER_SEL(buff_sel)  (IS_BIT_SET(buff_sel, FDCAN_TX_CPL_BUFFER0_MASK)   \
                                                     ^ IS_BIT_SET(buff_sel, FDCAN_TX_CPL_BUFFER1_MASK) \
                                                     ^ IS_BIT_SET(buff_sel, FDCAN_TX_CPL_BUFFER2_MASK))

/*! Check if only a single  bit is at 1 in buff_sel */
#define IS_FDCAN_VALID_TX_ABORT_BUFFER_SEL(buff_sel)  (IS_BIT_SET(buff_sel, FDCAN_TX_ABORT_BUFFER0_MASK)   \
                                                       ^ IS_BIT_SET(buff_sel, FDCAN_TX_ABORT_BUFFER1_MASK) \
                                                       ^ IS_BIT_SET(buff_sel, FDCAN_TX_ABORT_BUFFER2_MASK))

/*! Check if the interrupt line is valid */
#define IS_FDCAN_IT_LINE(it_line) (((it_line) & ~(HAL_FDCAN_IT_LINE_0 | HAL_FDCAN_IT_LINE_1)) == 0U)

/*! Check if only a single  bit is set at 1 in IT_LIST */
#define IS_SINGLE_BIT_SET(it_list) (((it_list) > 0U) && (((it_list) & ((it_list) - 1U)) == 0U))

/*! Check if the interrupt list is valid */
#define IS_FDCAN_IT(it) (((it) != 0U) &&  (((it) & (HAL_FDCAN_IR_MASK)) != 0U))

#define HAL_FDCAN_IT_GROUP_MASK (HAL_FDCAN_IT_GROUP_RX_FIFO0         \
                                 | HAL_FDCAN_IT_GROUP_RX_FIFO1       \
                                 | HAL_FDCAN_IT_GROUP_STATUS_MSG     \
                                 | HAL_FDCAN_IT_GROUP_TX_FIFO_ERROR  \
                                 | HAL_FDCAN_IT_GROUP_MISC           \
                                 | HAL_FDCAN_IT_GROUP_BIT_LINE_ERROR \
                                 | HAL_FDCAN_IT_GROUP_PROTOCOL_ERROR)  /*!< Interrupts group mask */

/*! Check if the group is valid */
#define IS_FDCAN_IT_GROUP(group) (((group) & ~HAL_FDCAN_IT_GROUP_MASK) == 0U)

/*! Check if the destination is valid */
#define IS_FDCAN_NON_MATCHING(destination) (((destination) == HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO0)    \
                                            || ((destination) == HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO1) \
                                            || ((destination) == HAL_FDCAN_NON_MATCHING_REJECT))

/*! Check if the reject mode is valid */
#define IS_FDCAN_REJECT_REMOTE(destination) (((destination) == HAL_FDCAN_REMOTE_ACCEPT)    \
                                             || ((destination) == HAL_FDCAN_REMOTE_REJECT))

/*! Check if the timestamp source is valid */
#define IS_FDCAN_TIMESTAMP_SOURCE(operation) (((operation) == HAL_FDCAN_TIMESTAMP_SOURCE_INTERNAL)       \
                                              || ((operation) == HAL_FDCAN_TIMESTAMP_SOURCE_ZERO)        \
                                              || ((operation) == HAL_FDCAN_TIMESTAMP_SOURCE_EXTERNAL))

/*! Check if the Prescaler value is valid */
#define IS_FDCAN_TIMESTAMP_PRESCALER(prescaler) (((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_1)     \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_2)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_3)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_4)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_5)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_6)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_7)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_8)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_9)  \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_10) \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_11) \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_12) \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_13) \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_14) \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_15) \
                                                 || ((prescaler) == HAL_FDCAN_TIMESTAMP_PRESC_16))

/*! Check if the Timeout operation is valid */
#define IS_FDCAN_TIMEOUT(operation) (((operation) == HAL_FDCAN_TIMEOUT_CONTINUOUS)       \
                                     || ((operation) == HAL_FDCAN_TIMEOUT_TX_EVENT_FIFO) \
                                     || ((operation) == HAL_FDCAN_TIMEOUT_RX_FIFO0)      \
                                     || ((operation) == HAL_FDCAN_TIMEOUT_RX_FIFO1))

/*! Check if the Interrupt flag is valid */
#define FDCAN_CHECK_FLAG(ir, flag) ((((ir) & (flag)) == (flag)) ? SET : RESET)

/*! Check if the Interrupt source is valid */
#define FDCAN_CHECK_IT_SOURCE(ie, it)  ((((ie) & (it)) == (it)) ? SET : RESET)

/*! Check that the fdcan instance is the fist instance */
#define IS_FDCAN_FIRST_INSTANCE(instance) ((instance) == FDCAN1)


/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup FDCAN_Private_Variables FDCAN Private Variables
  * @{
  */

/*! LUT with Data length Code (dlc) values to corresponding number of bytes */
static const uint8_t DLCtoBytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

/**
  * @}
  */

/* Private functions  -----------------------------------------------*/
/** @defgroup FDCAN_Private_Functions FDCAN Private Functions
  * @{
  */

static void FDCAN_calculateRamBlockAddresses(hal_fdcan_handle_t *hfdcan, const hal_fdcan_config_t *p_config);
static void FDCAN_copyMessageToRAM(const hal_fdcan_handle_t *hfdcan,
                                   const hal_fdcan_tx_header_t *p_tx_element_header,
                                   const uint8_t *p_tx_data, uint32_t buffer_index);

/**
  * @}
  */

/* Private types ------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Types FDCAN Private Types
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FDCAN_Exported_Functions
  * @{
  */

/** @addtogroup FDCAN_Exported_Functions_Group1
  * @{
A set of functions allowing to initialize and deinitialize the FDCAN peripheral:
    - HAL_FDCAN_Init()    : Initialize the selected device with the FDCAN instance.
    - HAL_FDCAN_DeInit()  : Restore the default configuration of the selected FDCAN peripheral.
  */

/**
  * @brief  Initializes the FDCAN peripheral according to the associated handle.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  instance HAL FDCAN instance.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR HAL FDCAN semaphore creation has failed (USE_HAL_MUTEX is set to 1).
  */
hal_status_t HAL_FDCAN_Init(hal_fdcan_handle_t *hfdcan, hal_fdcan_t instance)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hfdcan == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_FDCAN_ALL_INSTANCE((FDCAN_GlobalTypeDef *)((uint32_t)instance)));

  /* Instance */
  hfdcan->instance = instance;

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
  /* FDCAN Callbacks to the weak function */
  hfdcan->p_tx_eventfifo_cb         = HAL_FDCAN_TxEventFifoCallback;          /* TxEventFifoCallback             */
  hfdcan->p_rx_fifo0_cb             = HAL_FDCAN_RxFifo0Callback;              /* RxFifo0Callback                 */
  hfdcan->p_rx_fifo1_cb             = HAL_FDCAN_RxFifo1Callback;              /* RxFifo1Callback                 */
  hfdcan->p_tx_fifoempty_cb         = HAL_FDCAN_TxFifoEmptyCallback;          /* TxFifoEmptyCallback             */
  hfdcan->p_tx_buffercomplete_cb    = HAL_FDCAN_TxBufferCompleteCallback;     /* TxBufferCompleteCallback        */
  hfdcan->p_tx_bufferabort_cb       = HAL_FDCAN_TxBufferAbortCallback;        /* TxBufferAbortCallback           */
  hfdcan->p_highpriority_msg_cb     = HAL_FDCAN_HighPriorityMessageCallback;  /* HighPriorityMessageCallback     */
  hfdcan->p_ts_wraparound_cb        = HAL_FDCAN_TimestampWraparoundCallback;  /* TimestampWraparoundCallback     */
  hfdcan->p_error_cb                = HAL_FDCAN_ErrorCallback;                /* ErrorCallback                   */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

  /* Initialize the latest Tx request buffer index */
  hfdcan->latest_tx_fifo_q_request = 0U;

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  /* Initialize the error code */
  hfdcan->last_error_codes = HAL_FDCAN_ERROR_NONE;
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

#if defined(USE_HAL_FDCAN_CLK_ENABLE_MODEL) && (USE_HAL_FDCAN_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable FDCAN Clock */
  HAL_RCC_FDCAN_EnableClock();
#endif /* USE_HAL_FDCAN_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  /* Create the FDCAN semaphore */
  if (HAL_OS_SemaphoreCreate(&hfdcan->semaphore) != HAL_OS_OK)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1U)
  hfdcan->p_user_data = (void *) NULL;
#endif /* USE_HAL_FDCAN_USER_DATA */

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Clear all the potentially pending interrupts */
  FDCAN_CLEAR_FLAG(hfdcan, HAL_FDCAN_IR_MASK);

  /* Clear all interrupts enable */
  CLEAR_BIT(p_fdcanx->IE, HAL_FDCAN_IE_MASK);

  /* Disable Interrupt lines */
  CLEAR_BIT(p_fdcanx->ILE, (HAL_FDCAN_IT_LINE_0 | HAL_FDCAN_IT_LINE_1));

  hfdcan->global_state = HAL_FDCAN_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  Deinitialize the FDCAN driver for the given handle and disable the peripheral.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  */
void HAL_FDCAN_DeInit(hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t tick_start;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Reset clock stop request */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CSR);

  /* Get tick */
  tick_start = HAL_GetTick();

  /* Wait until FDCAN exits sleep mode */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
  {
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      break;
    }
  }

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable Interrupt lines */
  CLEAR_BIT(p_fdcanx->ILE, (HAL_FDCAN_IT_LINE_0 | HAL_FDCAN_IT_LINE_1));

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1)
  /* Reset the user data pointer to NULL */
  hfdcan->p_user_data = NULL;
#endif /* USE_HAL_FDCAN_USER_DATA */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  /* Delete the FDCAN semaphore */
  (void)HAL_OS_SemaphoreDelete(&hfdcan->semaphore);
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  /* Initialize the error code */
  hfdcan->last_error_codes = HAL_FDCAN_ERROR_NONE;
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */
  /* Change FDCAN state */
  hfdcan->global_state = HAL_FDCAN_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group2
  * @{
A set of functions allowing to enter and exit sleep mode for the FDCAN peripheral:
    - HAL_FDCAN_EnterPowerDownMode(): Enter in Power Down (sleep mode).
    - HAL_FDCAN_ExitPowerDownMode():  Exit Power Down (sleep mode).
  */

/**
  * @brief  Set the FDCAN peripheral in power down mode (sleep mode).
  * @note   Called from HAL_FDCAN_STATE_ACTIVE state and sets the fdcan in HAL_FDCAN_STATE_POWER_DOWN state.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_EnterPowerDownMode(hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t tick_start;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  hfdcan->previous_state = hfdcan->global_state;

  /* Request clock stop */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CSR);

  /* Get tick */
  tick_start = HAL_GetTick();

  /* Wait until FDCAN is ready for power down */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_CSA) == 0U)
  {
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Update The HAL State */
  hfdcan->global_state = HAL_FDCAN_STATE_POWER_DOWN;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Exit the FDCAN peripheral power down mode (sleep mode).
  * @note   Called from HAL_FDCAN_STATE_POWER_DOWN state and sets the fdcan in HAL_FDCAN_STATE_ACTIVE state.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_ExitPowerDownMode(hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t tick_start;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Reset clock stop request */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CSR);

  /* Get tick */
  tick_start = HAL_GetTick();

  /* Wait until FDCAN exits sleep mode */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
  {
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Return to normal operation */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_INIT);

  /* Update The HAL State */
  hfdcan->global_state = HAL_FDCAN_STATE_ACTIVE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group3
  * @{
There are two categories of HAL configuration set of functions for the peripheral configuration:

- Global configuration set of functions:
  - HAL_FDCAN_SetConfig(): Allowing to set the HAL FDCAN peripheral instance into a ready to use state (idle) according
    to the user parameters
  - HAL_FDCAN_GetConfig(): Allowing to retrieve the HAL FDCAN peripheral configuration

- Unitary configuration set of functions
  - Apply/Retrieve one single configuration item

These sets of functions are intended to dynamically modify/retrieve a unitary item meaning that a global configuration
has been already applied.
Unitary configuration set of functions must check first if the FDCAN module is in IDLE state (meaning a global
configuration was applied) in order to modify or retrieve a single item. Integrity check must be ensured when setting
an item.

Items that can alter other config parameters must not be handled within unitary set of functions.

   -  This section provides functions allowing:
      - HAL_FDCAN_SetNominalBitTiming()             : Configure the nominal bit timing
      - HAL_FDCAN_GetNominalBitTiming()             : Retrieve the nominal bit timing configuration
      - HAL_FDCAN_SetDataBitTiming()                : Configure the data bit timing
      - HAL_FDCAN_GetDataBitTiming()                : Retrieve the data bit timing configuration
      - HAL_FDCAN_SetFilter()                       : Configure the FDCAN reception filter
      - HAL_FDCAN_GetFilter()                       : Retrieve the FDCAN reception filter configuration
      - HAL_FDCAN_SetGlobalFilter()                 : Configure the FDCAN global filter
      - HAL_FDCAN_GetGlobalFilter()                 : Retrieve the FDCAN global filter configuration
      - HAL_FDCAN_SetExtendedIdMask()               : Configure the extended ID mask
      - HAL_FDCAN_GetExtendedIdMask()               : Retrieve the extended ID mask configuration
      - HAL_FDCAN_SetClockDivider()                 : Configure the clock divider
      - HAL_FDCAN_GetClockDivider()                 : Retrieve the clock divider configuration
      - HAL_FDCAN_SetRxFifoOverwrite()              : Configure the Rx FIFO operation mode
      - HAL_FDCAN_GetRxFifoOverwrite()              : Retrieve the Rx FIFO operation mode configuration
      - HAL_FDCAN_SetRamWatchdog()                  : Configure the RAM watchdog
      - HAL_FDCAN_GetRamWatchdog()                  : Retrieve the RAM watchdog value
      - HAL_FDCAN_SetConfigTimestampCounter()       : Configure the timestamp counter
      - HAL_FDCAN_GetConfigTimestampCounter()       : Retrieve the timestamp counter configuration
      - HAL_FDCAN_GetTimestampCounter()             : Retrieve the timestamp counter value
      - HAL_FDCAN_ResetTimestampCounter()           : Reset the timestamp counter to zero
      - HAL_FDCAN_SetConfigTimeoutCounter()         : Configure the timeout counter
      - HAL_FDCAN_GetConfigTimeoutCounter()         : Retrieve the timeout counter configuration
      - HAL_FDCAN_GetTimeoutCounter()               : Retrieve the timeout counter value
      - HAL_FDCAN_ResetTimeoutCounter()             : Reset the timeout counter to its starting value
      - HAL_FDCAN_EnableTimeoutCounter()            : Enable the timeout counter
      - HAL_FDCAN_DisableTimeoutCounter()           : Disable the timeout counter
      - HAL_FDCAN_IsEnabledTimeoutCounter()         : Check if the timeout counter is enabled
      - HAL_FDCAN_SetConfigTxDelayCompensation()    : Configure the transmitter delay compensation
      - HAL_FDCAN_GetConfigTxDelayCompensation()    : Retrieve the transmitter delay compensation configuration
      - HAL_FDCAN_DisableTxDelayCompensation()      : Disable the transmitter delay compensation
      - HAL_FDCAN_EnableTxDelayCompensation()       : Enable the transmitter delay compensation
      - HAL_FDCAN_IsEnabledTxDelayCompensation()    : Check if the transmitter delay compensation is enabled
      - HAL_FDCAN_DisableISOMode()                  : Disable ISO 11898-1 protocol mode
      - HAL_FDCAN_EnableISOMode()                   : Enable ISO 11898-1 protocol mode
      - HAL_FDCAN_IsEnabledISOMode()                : Check if the ISO mode is enabled
      - HAL_FDCAN_DisableEdgeFiltering()            : Disable edge filtering during bus integration
      - HAL_FDCAN_EnableEdgeFiltering()             : Enable edge filtering during bus integration
      - HAL_FDCAN_IsEnabledEdgeFiltering()          : Check if the Edge Filtering is enabled
      - HAL_FDCAN_SetMode()                         : Configure operating mode
      - HAL_FDCAN_GetMode()                         : Retrieve the current operative mode configuration
      - HAL_FDCAN_SetFrameFormat()                  : Configure the frame format
      - HAL_FDCAN_GetFrameFormat()                  : Retrieve the frame format configuration
      - HAL_FDCAN_SetAutoRetransmission()           : Configure the auto retransmission
      - HAL_FDCAN_GetAutoRetransmission()           : Retrieve the auto retransmission configuration
      - HAL_FDCAN_SetTransmitPause()                : Configure the transmit pause
      - HAL_FDCAN_GetTransmitPause()                : Retrieve the transmit pause configuration
      - HAL_FDCAN_SetProtocolException()            : Configure the protocol exception
      - HAL_FDCAN_GetProtocolException()            : Retrieve the protocol exception configuration
      - HAL_FDCAN_GetClockFreq()                    : Retrieve the current FDCAN kernel clock
      - HAL_FDCAN_SetTxMode()                       : Configure the transmission FIFO/Queue mode
      - HAL_FDCAN_GetTxMode()                       : Retrieve the transmission FIFO/Queue mode configuration
 */

/**
  * @brief  Configures the FDCAN according to the user parameters.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_config Pointer to the configuration structure.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_SetConfig(hal_fdcan_handle_t *hfdcan, const hal_fdcan_config_t *p_config)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;
  uint32_t tick_start;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_CKDIV(p_config->clock_divider));
  ASSERT_DBG_PARAM(IS_FDCAN_FRAME_FORMAT(p_config->frame_format));
  ASSERT_DBG_PARAM(IS_FDCAN_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_FDCAN_AUTO_RETRANSMISSION(p_config->auto_retransmission));
  ASSERT_DBG_PARAM(IS_FDCAN_TRANSMIT_PAUSE(p_config->transmit_pause));
  ASSERT_DBG_PARAM(IS_FDCAN_PROTOCOL_EXCEPTION(p_config->protocol_exception));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_PRESCALER(p_config->nominal_bit_timing.nominal_prescaler));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_SJW(p_config->nominal_bit_timing.nominal_jump_width));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_TSEG1(p_config->nominal_bit_timing.nominal_time_seg1));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_TSEG2(p_config->nominal_bit_timing.nominal_time_seg2));
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_config->std_filters_nbr, SRAMCAN_FLS_NBR));
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_config->ext_filters_nbr, SRAMCAN_FLE_NBR));
  ASSERT_DBG_PARAM(IS_FDCAN_TX_FIFO_QUEUE_MODE(p_config->tx_fifo_queue_mode));
  if (p_config->frame_format == HAL_FDCAN_FRAME_FD_BRS)
  {
    ASSERT_DBG_PARAM(IS_FDCAN_DATA_PRESCALER(p_config->data_bit_timing.data_prescaler));
    ASSERT_DBG_PARAM(IS_FDCAN_DATA_SJW(p_config->data_bit_timing.data_jump_width));
    ASSERT_DBG_PARAM(IS_FDCAN_DATA_TSEG1(p_config->data_bit_timing.data_time_seg1));
    ASSERT_DBG_PARAM(IS_FDCAN_DATA_TSEG2(p_config->data_bit_timing.data_time_seg2));
  }
  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Leave the Power Down mode if set => CSR & CSA set        */
  /* Because setting INIT bit has no effect in PowerDown mode */

  /* Reset clock stop request */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CSR);

  /* Get tick */
  tick_start = HAL_GetTick();

  /* Wait until FDCAN exits sleep mode */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
  {
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Request initialisation - Set the INIT bit from CCCR */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_INIT);

  /* Get tick */
  tick_start = HAL_GetTick();

  /* Wait until the INIT bit into CCCR register is set */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_INIT) == 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Request configuration change - Set CCE bit */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CCE);

  /* Configure Clock divider */
  WRITE_REG(FDCAN_CONFIG->CKDIV, (uint32_t)(p_config->clock_divider));

  /* Set the automatic retransmission */
  MODIFY_REG(p_fdcanx->CCCR, FDCAN_CCCR_DAR_Msk, ((uint32_t)(p_config->auto_retransmission) << FDCAN_CCCR_DAR_Pos));

  /* Set the transmit pause feature */
  MODIFY_REG(p_fdcanx->CCCR, FDCAN_CCCR_TXP_Msk, ((uint32_t)(p_config->transmit_pause) << FDCAN_CCCR_TXP_Pos));

  /* Set the Protocol Exception Handling */
  MODIFY_REG(p_fdcanx->CCCR, FDCAN_CCCR_PXHD_Msk, ((uint32_t)(p_config->protocol_exception) << FDCAN_CCCR_PXHD_Pos));

  /* Set FDCAN Frame Format */
  MODIFY_REG(p_fdcanx->CCCR, (uint32_t)HAL_FDCAN_FRAME_FD_BRS, (uint32_t)(p_config->frame_format));

  /* Reset FDCAN Operation Mode */
  CLEAR_BIT(p_fdcanx->CCCR, (FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM));
  CLEAR_BIT(p_fdcanx->TEST, FDCAN_TEST_LBCK);

  /* Set FDCAN Operating Mode:
               | Normal | Restricted |    Bus     | Internal | External |
               |  mode  | Operation  | Monitoring | LoopBack | LoopBack |
     --------------------------------------------------------------------
     CCCR.TEST |   0    |     0      |     0      |    1     |    1     |
     CCCR.MON  |   0    |     0      |     1      |    1     |    0     |
     TEST.LBCK |   0    |     0      |     0      |    1     |    1     |
     CCCR.ASM  |   0    |     1      |     0      |    0     |    0     |
     --------------------------------------------------------------------
  */
  if (p_config->mode == HAL_FDCAN_MODE_RESTRICTED_OPERATION)
  {
    /* Enable Restricted Operation mode */
    SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM);
  }
  else if (p_config->mode != HAL_FDCAN_MODE_NORMAL)
  {
    if (p_config->mode != HAL_FDCAN_MODE_BUS_MONITORING)
    {
      /* Enable write access to TEST register */
      SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TEST);
      /* Enable LoopBack mode */
      SET_BIT(p_fdcanx->TEST, FDCAN_TEST_LBCK);

      if (p_config->mode == HAL_FDCAN_MODE_INTERNAL_LOOPBACK)
      {
        SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON);
      }
    }
    else
    {
      /* Enable bus monitoring mode */
      SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON);
    }
  }
  else
  {
    /* Nothing to do: normal mode */
  }

  register_value = ((uint32_t)(p_config->nominal_bit_timing.nominal_prescaler - 1U) << FDCAN_NBTP_NBRP_Pos)
                   | ((uint32_t)(p_config->nominal_bit_timing.nominal_jump_width - 1U) << FDCAN_NBTP_NSJW_Pos)
                   | ((uint32_t)(p_config->nominal_bit_timing.nominal_time_seg1 - 1U) << FDCAN_NBTP_NTSEG1_Pos)
                   | ((uint32_t)(p_config->nominal_bit_timing.nominal_time_seg2 - 1U) << FDCAN_NBTP_NTSEG2_Pos);

  /* When INIT and CCE set to 1 then the fields from NBTP can be set */
  WRITE_REG(p_fdcanx->NBTP, register_value);

  /* If FD operation with BRS is selected, set the data bit timing register */
  if (p_config->frame_format == HAL_FDCAN_FRAME_FD_BRS)
  {
    /* Set the data bit timing values */
    register_value = ((uint32_t)(p_config->data_bit_timing.data_prescaler - 1U) << FDCAN_DBTP_DBRP_Pos)
                     | ((uint32_t)(p_config->data_bit_timing.data_jump_width - 1U) << FDCAN_DBTP_DSJW_Pos)
                     | ((uint32_t)(p_config->data_bit_timing.data_time_seg1 - 1U) << FDCAN_DBTP_DTSEG1_Pos)
                     | ((uint32_t)(p_config->data_bit_timing.data_time_seg2 - 1U) << FDCAN_DBTP_DTSEG2_Pos);

    /* Write the Nominal values to DBTP register */
    WRITE_REG(p_fdcanx->DBTP, register_value);
  }

  if (p_config->tx_fifo_queue_mode == HAL_FDCAN_TX_MODE_FIFO)
  {
    /* Select between Tx FIFO and Tx Queue operation modes */
    CLEAR_BIT(p_fdcanx->TXBC, FDCAN_TXBC_TFQM);
  }
  else
  {
    SET_BIT(p_fdcanx->TXBC, FDCAN_TXBC_TFQM);
  }
  /* Calculate each RAM block address */
  FDCAN_calculateRamBlockAddresses(hfdcan, p_config);

  /* Update The HAL State */
  hfdcan->global_state = HAL_FDCAN_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Retrieve the FDCAN global configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_config Pointer to the configuration structure @ref hal_fdcan_config_t.
  */
void HAL_FDCAN_GetConfig(const hal_fdcan_handle_t *hfdcan, hal_fdcan_config_t *p_config)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;
  uint32_t mode_selection;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Get FDCAN Operating Mode:
               | Normal | Restricted |    Bus     | Internal | External |
               |  mode  | Operation  | Monitoring | LoopBack | LoopBack |
     --------------------------------------------------------------------
     CCCR.TEST |   0    |     0      |     0      |    1     |    1     |
     CCCR.MON  |   0    |     0      |     1      |    1     |    0     |
     TEST.LBCK |   0    |     0      |     0      |    1     |    1     |
     CCCR.ASM  |   0    |     1      |     0      |    0     |    0     |
     --------------------------------------------------------------------
  */

  /* Read CCCR register - FDCAN CC control register (FDCAN_CCCR) */
  register_value = READ_REG(p_fdcanx->CCCR);

  /* Create a combined nibble TEST-MON-LBCK-ASM from the 4 read bits */
  mode_selection  = ((register_value & FDCAN_CCCR_ASM) >> 2);
  mode_selection |= ((register_value & FDCAN_CCCR_MON) >> 3);
  mode_selection |= ((register_value & FDCAN_CCCR_TEST) >> 4);

  /* Read test register - FDCAN test register (FDCAN_TEST) */
  mode_selection |= (READ_BIT(p_fdcanx->TEST, FDCAN_TEST_LBCK) >> 3);
  /* Each C statement holds only one access to a volatile variable (iar) */

  switch (mode_selection)
  {
    case 0:
      p_config->mode = (hal_fdcan_mode_t)HAL_FDCAN_MODE_NORMAL;
      break;
    case 1:
      p_config->mode = (hal_fdcan_mode_t) HAL_FDCAN_MODE_RESTRICTED_OPERATION;
      break;
    case 4:
      p_config->mode = (hal_fdcan_mode_t)HAL_FDCAN_MODE_BUS_MONITORING;
      break;
    case 10:
      p_config->mode = (hal_fdcan_mode_t)HAL_FDCAN_MODE_EXTERNAL_LOOPBACK;
      break;
    case 15:
      p_config->mode = (hal_fdcan_mode_t)HAL_FDCAN_MODE_INTERNAL_LOOPBACK;
      break;
    default:
      p_config->mode = (hal_fdcan_mode_t)HAL_FDCAN_MODE_INVALID;
      break;
  }

  /* Get the no automatic retransmission value*/
  p_config->auto_retransmission = (hal_fdcan_auto_retransmission_status_t)(uint32_t)((register_value
                                  & FDCAN_CCCR_DAR_Msk) >> FDCAN_CCCR_DAR_Pos);

  /* Get the transmit pause feature */
  p_config->transmit_pause = (hal_fdcan_transmit_pause_status_t)(uint32_t)((register_value & FDCAN_CCCR_TXP_Msk)
                                                                           >> FDCAN_CCCR_TXP_Pos);

  /* Get the Protocol exception feature */
  p_config->protocol_exception = (hal_fdcan_protocol_exception_status_t)(uint32_t)((register_value
                                 & FDCAN_CCCR_PXHD_Msk) >> FDCAN_CCCR_PXHD_Pos);

  /* Get FDCAN Frame Format */
  p_config->frame_format = (hal_fdcan_frame_format_t)(uint32_t)(register_value & (uint32_t)HAL_FDCAN_FRAME_FD_BRS);

  /* Get the clock divider */
  /* Read the value of the field PDIV[3:0] from FDCAN_CKDIV register */
  p_config->clock_divider = (hal_fdcan_clock_divider_t)(uint32_t)(READ_REG(FDCAN_CONFIG->CKDIV)
                                                                  & FDCAN_CLOCK_DIVIDER_MASK);

  /* Read RXGFC register - FDCAN global filter configuration register (FDCAN_RXGFC) */
  register_value = READ_REG(p_fdcanx->RXGFC);
  /* Get the Standard filter elements number */
  p_config->std_filters_nbr = (register_value & FDCAN_RXGFC_LSS) >> FDCAN_RXGFC_LSS_Pos;
  /* Get the Extended filter elements number */
  p_config->ext_filters_nbr = (register_value & FDCAN_RXGFC_LSE) >> FDCAN_RXGFC_LSE_Pos;

  /* Read TXBC register - FDCAN Tx buffer configuration register (FDCAN_TXBC) */
  register_value = READ_REG(p_fdcanx->TXBC);
  /* Get  Tx FIFO and Tx Queue operation modes */
  p_config->tx_fifo_queue_mode = (hal_fdcan_tx_mode_t)(uint32_t)((register_value & FDCAN_TXBC_TFQM));

  /* Read NBTP register - FDCAN nominal bit timing and prescaler register (FDCAN_NBTP) */
  register_value = READ_REG(p_fdcanx->NBTP);
  /* Get the Nominal time segment after sample point SEG2 */
  p_config->nominal_bit_timing.nominal_time_seg2 = ((register_value & FDCAN_NBTP_NTSEG2_Msk)
                                                    >> FDCAN_NBTP_NTSEG2_Pos) + 1U;

  /* Get the Nominal time segment before sample point SEG1 */
  p_config->nominal_bit_timing.nominal_time_seg1 = ((register_value & FDCAN_NBTP_NTSEG1_Msk)
                                                    >> FDCAN_NBTP_NTSEG1_Pos) + 1U;
  /* Get the Bit rate prescaler */
  p_config->nominal_bit_timing.nominal_prescaler = ((register_value & FDCAN_NBTP_NBRP_Msk)
                                                    >> FDCAN_NBTP_NBRP_Pos) + 1U;
  /* Get the Nominal synchronization jump width */
  p_config->nominal_bit_timing.nominal_jump_width = ((register_value & FDCAN_NBTP_NSJW_Msk)
                                                     >> FDCAN_NBTP_NSJW_Pos) + 1U;

  /* If FD operation with BRS is selected, then get the data bit timing register fields */
  if (p_config->frame_format == HAL_FDCAN_FRAME_FD_BRS)
  {
    /* Read DBTP register - FDCAN data bit timing and prescaler register (FDCAN_DBTP) */
    register_value = READ_REG(p_fdcanx->DBTP);
    /* Get the Data time segment after sample point SEG2 */
    p_config->data_bit_timing.data_time_seg2 = ((register_value & FDCAN_DBTP_DTSEG2_Msk) >> FDCAN_DBTP_DTSEG2_Pos) + 1U;
    /* Get the Data time segment before sample point SEG1 */
    p_config->data_bit_timing.data_time_seg1 = ((register_value & FDCAN_DBTP_DTSEG1_Msk) >> FDCAN_DBTP_DTSEG1_Pos) + 1U;
    /* Get the Data Bit rate prescaler */
    p_config->data_bit_timing.data_prescaler = ((register_value & FDCAN_DBTP_DBRP_Msk) >> FDCAN_DBTP_DBRP_Pos) + 1U;
    /* Get the Data synchronization jump width */
    p_config->data_bit_timing.data_jump_width = ((register_value & FDCAN_DBTP_DSJW_Msk) >> FDCAN_DBTP_DSJW_Pos) + 1U;
  }
}

/**
  * @brief  Set the transmission FIFO/Queue mode.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  tx_mode transmission mode to configure.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetTxMode(const hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_mode_t tx_mode)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_TX_MODE(tx_mode));

  /* Check the peripheral state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  MODIFY_REG(p_fdcanx->TXBC, (uint32_t)FDCAN_TXBC_TFQM_Msk, (uint32_t)tx_mode);

  return HAL_OK;
}

/**
  * @brief  Get the transmission FIFO/Queue mode configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @return value of configured transmission mode.
  */
hal_fdcan_tx_mode_t HAL_FDCAN_GetTxMode(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_tx_mode_t)(uint32_t)(READ_REG(p_fdcanx->TXBC) & FDCAN_TXBC_TFQM_Msk);
}


/**
  * @brief  Set the FDCAN nominal bit timing configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_nominal_bit_timing  Pointer to nominal bit timing structure @ref hal_fdcan_nominal_bit_timing_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  */
hal_status_t HAL_FDCAN_SetNominalBitTiming(const hal_fdcan_handle_t *hfdcan,
                                           const hal_fdcan_nominal_bit_timing_t *p_nominal_bit_timing)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_nominal_bit_timing != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_nominal_bit_timing == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  /* Check the nominal timing function parameter fields */
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_PRESCALER(p_nominal_bit_timing->nominal_prescaler));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_SJW(p_nominal_bit_timing->nominal_jump_width));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_TSEG1(p_nominal_bit_timing->nominal_time_seg1));
  ASSERT_DBG_PARAM(IS_FDCAN_NOMINAL_TSEG2(p_nominal_bit_timing->nominal_time_seg2));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  register_value = ((p_nominal_bit_timing->nominal_prescaler - 1U) << FDCAN_NBTP_NBRP_Pos)
                   | ((p_nominal_bit_timing->nominal_jump_width - 1U) << FDCAN_NBTP_NSJW_Pos)
                   | ((p_nominal_bit_timing->nominal_time_seg1 - 1U) << FDCAN_NBTP_NTSEG1_Pos)
                   | ((p_nominal_bit_timing->nominal_time_seg2 - 1U) << FDCAN_NBTP_NTSEG2_Pos);

  /* When INIT and CCE set to 1 then the fields from NBTP can be set */
  WRITE_REG(p_fdcanx->NBTP, register_value);

  return HAL_OK;
}

/**
  * @brief  Retrieve the FDCAN nominal bit timing configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  nominal_bit_timing Pointer to the nominal bit timing structure @ref hal_fdcan_nominal_bit_timing_t
  */
void HAL_FDCAN_GetNominalBitTiming(const hal_fdcan_handle_t *hfdcan,
                                   hal_fdcan_nominal_bit_timing_t *nominal_bit_timing)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((nominal_bit_timing != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  register_value = READ_REG(p_fdcanx->NBTP);
  /* Get the nominal prescaler */
  nominal_bit_timing->nominal_prescaler = ((register_value & FDCAN_NBTP_NBRP_Msk) >> FDCAN_NBTP_NBRP_Pos) + 1U;
  /* Get the nominal sync jump width value */
  nominal_bit_timing->nominal_jump_width = ((register_value & FDCAN_NBTP_NSJW_Msk) >> FDCAN_NBTP_NSJW_Pos) + 1U;
  /* Get the nominal Time segment1 */
  nominal_bit_timing->nominal_time_seg1 = ((register_value & FDCAN_NBTP_NTSEG1_Msk) >> FDCAN_NBTP_NTSEG1_Pos) + 1U;
  /* Get the nominal Time Segment2 */
  nominal_bit_timing->nominal_time_seg2 = ((register_value & FDCAN_NBTP_NTSEG2_Msk) >> FDCAN_NBTP_NTSEG2_Pos) + 1U;
}

/**
  * @brief  Set the FDCAN data bit timing configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_data_bit_timing  Pointer to data bit timing structure @ref hal_fdcan_data_bit_timing_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  */
hal_status_t HAL_FDCAN_SetDataBitTiming(const hal_fdcan_handle_t *hfdcan,
                                        const hal_fdcan_data_bit_timing_t *p_data_bit_timing)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_data_bit_timing != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data_bit_timing == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the data timing function parameter fields */
  ASSERT_DBG_PARAM(IS_FDCAN_DATA_PRESCALER(p_data_bit_timing->data_prescaler));
  ASSERT_DBG_PARAM(IS_FDCAN_DATA_SJW(p_data_bit_timing->data_jump_width));
  ASSERT_DBG_PARAM(IS_FDCAN_DATA_TSEG1(p_data_bit_timing->data_time_seg1));
  ASSERT_DBG_PARAM(IS_FDCAN_DATA_TSEG2(p_data_bit_timing->data_time_seg2));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set the data bit timing values */
  register_value = ((p_data_bit_timing->data_prescaler - 1U) << FDCAN_DBTP_DBRP_Pos)
                   | ((p_data_bit_timing->data_jump_width - 1U) << FDCAN_DBTP_DSJW_Pos)
                   | ((p_data_bit_timing->data_time_seg1 - 1U) << FDCAN_DBTP_DTSEG1_Pos)
                   | ((p_data_bit_timing->data_time_seg2 - 1U) << FDCAN_DBTP_DTSEG2_Pos);

  /* Write the Nominal values to DBTP register */
  WRITE_REG(p_fdcanx->DBTP, register_value);

  return HAL_OK;
}

/**
  * @brief  Retrieve the FDCAN data Bit Timing configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  data_bit_timing Pointer to the data bit timing structure @ref hal_fdcan_data_bit_timing_t
  */
void HAL_FDCAN_GetDataBitTiming(const hal_fdcan_handle_t *hfdcan, hal_fdcan_data_bit_timing_t  *data_bit_timing)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((data_bit_timing != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  register_value = READ_REG(p_fdcanx->DBTP);
  /* Get the Data prescaler */
  data_bit_timing->data_prescaler = ((register_value & FDCAN_DBTP_DBRP_Msk) >> FDCAN_DBTP_DBRP_Pos) + 1U;
  /* Get the Data sync jump width value */
  data_bit_timing->data_jump_width = ((register_value & FDCAN_DBTP_DSJW_Msk) >> FDCAN_DBTP_DSJW_Pos) + 1U;
  /* Get the Data Time segment1 */
  data_bit_timing->data_time_seg1 = ((register_value & FDCAN_DBTP_DTSEG1_Msk) >> FDCAN_DBTP_DTSEG1_Pos) + 1U;
  /* Get the Data Time Segment2 */
  data_bit_timing->data_time_seg2 = ((register_value & FDCAN_DBTP_DTSEG2_Msk) >> FDCAN_DBTP_DTSEG2_Pos) + 1U;
}

/**
  * @brief  Configure the FDCAN reception filter according to the specified.
  *         parameters in the hal_fdcan_filter_t structure.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_filter_config Pointer to a @ref hal_fdcan_filter_t.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetFilter(const hal_fdcan_handle_t *hfdcan, const hal_fdcan_filter_t *p_filter_config)
{
  uint32_t filter_element_w1;
  uint32_t filter_element_w2;
  uint32_t *filter_address;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_filter_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_filter_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_ID_TYPE(p_filter_config->id_type));
  ASSERT_DBG_PARAM(IS_FDCAN_FILTER_CFG(p_filter_config->filter_config));

  if (p_filter_config->id_type == HAL_FDCAN_ID_STANDARD)
  {
    /* Check function parameters */
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_filter_config->filter_index, SRAMCAN_FLS_NBR - 1U));
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_filter_config->filter_id1, FDCAN_STD_ID_MAX_VALUE));
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_filter_config->filter_id2, FDCAN_STD_ID_MAX_VALUE));
    ASSERT_DBG_PARAM(IS_FDCAN_STD_FILTER_TYPE(p_filter_config->filter_type));

    /* Build filter element */
    filter_element_w1 = (((uint32_t)(p_filter_config->filter_type) << FDCAN_STD_FILTER_TYPE_POS)
                         | ((uint32_t)(p_filter_config->filter_config) << FDCAN_STD_FILTER_CONFIG_POS)
                         | ((uint32_t)(p_filter_config->filter_id1) << FDCAN_STD_FILTER_ID1_POS)
                         |  p_filter_config->filter_id2);

    /* Calculate filter address */
    filter_address = (uint32_t *)(hfdcan->msg_ram.std_filter_start_addr +
                                  (p_filter_config->filter_index * SRAMCAN_FLS_SIZE));

    /* Write filter element to the message RAM */
    *filter_address = filter_element_w1;
  }
  else /* p_filter_config->id_type == FDCAN_EXTENDED_ID */
  {
    /* Check function parameters */
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_filter_config->filter_index, SRAMCAN_FLE_NBR - 1U));
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_filter_config->filter_id1, FDCAN_EXT_ID_MAX_VALUE));
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_filter_config->filter_id2, FDCAN_EXT_ID_MAX_VALUE));
    ASSERT_DBG_PARAM(IS_FDCAN_EXT_FILTER_TYPE(p_filter_config->filter_type));

    /* Build first word of filter element */
    filter_element_w1 = (((uint32_t)(p_filter_config->filter_config) << (uint32_t)FDCAN_EXT_FILTER_CONFIG_POS)
                         | p_filter_config->filter_id1);

    /* Build second word of filter element */
    filter_element_w2 = (((uint32_t)(p_filter_config->filter_type) << (uint32_t)FDCAN_EXT_FILTER_TYPE_POS)
                         | p_filter_config->filter_id2);

    /* Calculate filter address */
    filter_address = (uint32_t *)(hfdcan->msg_ram.ext_filter_start_addr +
                                  (p_filter_config->filter_index * SRAMCAN_FLE_SIZE));

    /* Write filter element to the message RAM */
    *filter_address = filter_element_w1;
    filter_address++;
    *filter_address = filter_element_w2;
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Configure the FDCAN reception filter according to the specified
  *         parameters in the hal_fdcan_filter_t structure.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_filter_config Pointer to a structure based on @ref hal_fdcan_filter_t
  * @param  id_type Specifies the type of filter based on @ref FDCAN_id_type.
  * @param  filter_index Index of the filter to be set.
  */
void HAL_FDCAN_GetFilter(const hal_fdcan_handle_t *hfdcan, hal_fdcan_filter_t *p_filter_config,
                         uint32_t filter_index, uint32_t id_type)
{
  uint32_t *filter_address;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_filter_config != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_ID_TYPE(id_type));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  if (id_type == HAL_FDCAN_ID_STANDARD)
  {
    /* Check parameter */
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(filter_index, SRAMCAN_FLS_NBR - 1U));
    /* Calculate filter address */
    filter_address = (uint32_t *)(hfdcan->msg_ram.std_filter_start_addr + (filter_index * SRAMCAN_FLS_SIZE));
    /* Check that the address is not 0x00000000 */
    ASSERT_DBG_PARAM(IS_ADDRESS_VALID(filter_address));
    /* Process and read the S0 word */
    /* Standard filter type SFT */
    p_filter_config->filter_type = (hal_fdcan_filter_type_t)(uint32_t)((*filter_address >> FDCAN_STD_FILTER_TYPE_POS)
                                                                       & FDCAN_STD_FILTER_TYPE_MASK);
    /* Standard filter element configuration SFEC */
    p_filter_config->filter_config = (hal_fdcan_filter_config_t)(uint32_t)
                                     ((*filter_address >> FDCAN_STD_FILTER_CONFIG_POS) & FDCAN_STD_FILTER_CONFIG_MASK);
    p_filter_config->filter_index  = filter_index;
    /* Standard filter ID1 SFID1 */
    p_filter_config->filter_id1    = (*filter_address >> FDCAN_STD_FILTER_ID1_POS) & FDCAN_STD_ID1_MASK;
    /* Standard filter ID2 SFID2 */
    p_filter_config->filter_id2    = (*filter_address >> FDCAN_STD_FILTER_ID2_POS) & FDCAN_STD_ID2_MASK;
  }
  else /* p_filter_config->id_type == FDCAN_EXTENDED_ID */
  {
    /* Check parameter */
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(filter_index, SRAMCAN_FLE_NBR - 1U));
    /* Calculate filter address */
    filter_address = (uint32_t *)(hfdcan->msg_ram.ext_filter_start_addr + (filter_index * SRAMCAN_FLE_SIZE));
    /* Check that the address is not 0x00000000 */
    ASSERT_DBG_PARAM(IS_ADDRESS_VALID(filter_address));
    /* Process the F0 word */
    /* Extended filter element configuration EFEC */
    p_filter_config->filter_config = (hal_fdcan_filter_config_t)(uint32_t)
                                     ((*filter_address >> FDCAN_EXT_FILTER_CONFIG_POS) & FDCAN_EXT_FILTER_CONFIG_MASK);
    /* Extended filter ID 1 EFID1 */
    p_filter_config->filter_id1 = (*filter_address >> FDCAN_EXT_FILTER_ID1_POS) & FDCAN_EXT_FILTER_ID1_MASK;
    /* Read the next word - F1 word */
    filter_address++;
    /* Extended filter type EFT */
    p_filter_config->filter_type = (hal_fdcan_filter_type_t)(uint32_t)((*filter_address >> FDCAN_EXT_FILTER_TYPE_POS)
                                                                       & FDCAN_EXT_FILTER_TYPE_MASK);

    /* Extended filter ID 2 EFID2 */
    p_filter_config->filter_id2 = (*filter_address >> FDCAN_EXT_FILTER_ID2_POS) & FDCAN_EXT_FILTER_ID2_MASK;
  }
}

/**
  * @brief  Configure the FDCAN global filter.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle. structure
  * @param  p_global_filter_config Pointer to a structure based on @ref hal_fdcan_global_filter_config_t.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetGlobalFilter(const hal_fdcan_handle_t *hfdcan,
                                       const hal_fdcan_global_filter_config_t *p_global_filter_config)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_global_filter_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_global_filter_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_NON_MATCHING(p_global_filter_config->acceptance_non_matching_std));
  ASSERT_DBG_PARAM(IS_FDCAN_NON_MATCHING(p_global_filter_config->acceptance_non_matching_ext));
  ASSERT_DBG_PARAM(IS_FDCAN_REJECT_REMOTE(p_global_filter_config->acceptance_remote_std));
  ASSERT_DBG_PARAM(IS_FDCAN_REJECT_REMOTE(p_global_filter_config->acceptance_remote_ext));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /*if (hfdcan->global_state == HAL_FDCAN_STATE_IDLE)*/
  /* Set global filter */
  MODIFY_REG(p_fdcanx->RXGFC, (FDCAN_RXGFC_ANFS | FDCAN_RXGFC_ANFE | FDCAN_RXGFC_RRFS | FDCAN_RXGFC_RRFE),
             (((uint32_t)(p_global_filter_config->acceptance_non_matching_std) << (uint32_t)FDCAN_RXGFC_ANFS_Pos)
              | ((uint32_t)(p_global_filter_config->acceptance_non_matching_ext) << (uint32_t)FDCAN_RXGFC_ANFE_Pos)
              | ((uint32_t)(p_global_filter_config->acceptance_remote_std) << (uint32_t)FDCAN_RXGFC_RRFS_Pos)
              | ((uint32_t)(p_global_filter_config->acceptance_remote_ext) << (uint32_t)FDCAN_RXGFC_RRFE_Pos)));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the FDCAN global filter.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_global_filter_config Pointer to a structure based on @ref hal_fdcan_global_filter_config_t
  */
void HAL_FDCAN_GetGlobalFilter(const hal_fdcan_handle_t *hfdcan,
                               hal_fdcan_global_filter_config_t *p_global_filter_config)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_global_filter_config != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Get the Accept Non-matching frames standard value */
  p_global_filter_config->acceptance_non_matching_std =
    (hal_fdcan_acceptance_non_matching_frame_t)(uint32_t)((p_fdcanx->RXGFC & FDCAN_RXGFC_ANFS) >> FDCAN_RXGFC_ANFS_Pos);
  /* Get the Accept non-matching frames extended value */
  p_global_filter_config->acceptance_non_matching_ext =
    (hal_fdcan_acceptance_non_matching_frame_t)(uint32_t)((p_fdcanx->RXGFC & FDCAN_RXGFC_ANFE) >> FDCAN_RXGFC_ANFE_Pos);
  /* Get the Reject remote frames standard value */
  p_global_filter_config->acceptance_remote_std =
    (hal_fdcan_acceptance_remote_frame_t)(uint32_t)((p_fdcanx->RXGFC & FDCAN_RXGFC_RRFS) >> FDCAN_RXGFC_RRFS_Pos);
  /* Get the Reject remote frames extended */
  p_global_filter_config->acceptance_remote_ext =
    (hal_fdcan_acceptance_remote_frame_t)(uint32_t)((p_fdcanx->RXGFC & FDCAN_RXGFC_RRFE) >> FDCAN_RXGFC_RRFE_Pos);
}

/**
  * @brief  Set the Extended ID Mask value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  mask value of the Extended ID Mask, this parameter must be a number between 0 and 0x1FFFFFFF.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetExtendedIdMask(const hal_fdcan_handle_t *hfdcan, uint32_t mask)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(mask, FDCAN_EXT_ID_MAX_VALUE));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Configure the extended ID mask */
  WRITE_REG(p_fdcanx->XIDAM, mask);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the extended ID Mask value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval uint32_t Extended ID Mask, this parameter must be a number between 0 and 0x1FFFFFFF.
  */
uint32_t HAL_FDCAN_GetExtendedIdMask(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return ((p_fdcanx->XIDAM) & FDCAN_EXT_ID_MASK);
}

/**
  * @brief  Set the FDCAN clock divider value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  clock_divider Value of the FDCAN clock divider based on @ref hal_fdcan_clock_divider_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetClockDivider(const hal_fdcan_handle_t *hfdcan, hal_fdcan_clock_divider_t clock_divider)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_CKDIV(clock_divider));

  /* Only the first FDCAN instance is allowed to modify the configuration */
  ASSERT_DBG_PARAM(IS_FDCAN_FIRST_INSTANCE((FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance)));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Prevent unused argument(s) compilation warning in case disabled asserts */
  STM32_UNUSED(hfdcan);

  /* Configure Clock divider */
  WRITE_REG(FDCAN_CONFIG->CKDIV, (uint32_t)clock_divider);

  return HAL_OK;
}

/**
  * @brief  Retrieve the clock divider for FDCAN.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval hal_fdcan_clock_divider_t FDCAN Clock divider, this parameter must be a value of
  *         @ref hal_fdcan_clock_divider_t.
  */
hal_fdcan_clock_divider_t HAL_FDCAN_GetClockDivider(const hal_fdcan_handle_t *hfdcan)
{
  /* Variable containing the result of the register FDCAN_CKDIV */
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  STM32_UNUSED(hfdcan);
  /* Read the value of the field PDIV[3:0] from FDCAN_CKDIV register */
  register_value = (READ_REG(FDCAN_CONFIG->CKDIV) & FDCAN_CLOCK_DIVIDER_MASK);

  return (hal_fdcan_clock_divider_t)register_value;
}

/**
  * @brief  Configure the Rx FIFO operation mode.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  rx_fifo_idx Index of the Rx FIFO, this parameter must be a value of @ref hal_fdcan_rx_location_t
  * @param  operation_mode operation mode, this parameter must be a value of @ref hal_fdcan_rx_fifo_operative_mode_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetRxFifoOverwrite(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_idx,
                                          hal_fdcan_rx_fifo_operative_mode_t operation_mode)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_RX_FIFO(rx_fifo_idx));
  ASSERT_DBG_PARAM(IS_FDCAN_RX_FIFO_MODE(operation_mode));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (rx_fifo_idx == HAL_FDCAN_RX_FIFO0)
  {
    /* Select FIFO 0 Operation Mode */
    MODIFY_REG(p_fdcanx->RXGFC, FDCAN_RXGFC_F0OM, ((uint32_t)operation_mode << FDCAN_RXGFC_F0OM_Pos));
  }
  else /* rx_fifo_idx == FDCAN_RX_FIFO1 */
  {
    /* Select FIFO 1 Operation Mode */
    MODIFY_REG(p_fdcanx->RXGFC, FDCAN_RXGFC_F1OM, ((uint32_t)operation_mode << FDCAN_RXGFC_F1OM_Pos));
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the Rx FIFO operation mode.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  rx_fifo_sel Selection of the Rx FIFOis a value of @ref hal_fdcan_rx_location_t
  * @param  p_rx_operation Pointer to structure based  on @ref hal_fdcan_rx_fifo_operative_mode_t

  */
void HAL_FDCAN_GetRxFifoOverwrite(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_sel,
                                  hal_fdcan_rx_fifo_operative_mode_t *p_rx_operation)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_rx_operation != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_RX_FIFO(rx_fifo_sel));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (rx_fifo_sel == HAL_FDCAN_RX_FIFO0)
  {
    *p_rx_operation = (hal_fdcan_rx_fifo_operative_mode_t)(uint32_t)((READ_BIT(p_fdcanx->RXGFC, FDCAN_RXGFC_F0OM)
                                                                      & FDCAN_RXGFC_F0OM_Msk) >> FDCAN_RXGFC_F0OM_Pos);
  }
  else
  {
    *p_rx_operation = (hal_fdcan_rx_fifo_operative_mode_t)(uint32_t)((READ_BIT(p_fdcanx->RXGFC, FDCAN_RXGFC_F1OM)
                                                                      & FDCAN_RXGFC_F1OM_Msk) >> FDCAN_RXGFC_F1OM_Pos);
  }
}


/**
  * @brief   Configure the RAM watchdog.
  * @param   hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param   counter_start_value Start value of the Message RAM Watchdog Counter,
  *          this parameter must be a number between 0x00 and 0xFF.
  * @warning With the reset value of 0x00 the counter is disabled.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetRamWatchdog(const hal_fdcan_handle_t *hfdcan, uint32_t counter_start_value)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(counter_start_value, FDCAN_WATCHDOG_VALUE_MAX));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Configure the RAM watchdog counter start value */
  MODIFY_REG(p_fdcanx->RWD, FDCAN_RWD_WDC, counter_start_value);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the RAM watchdog actual Ram Watchdog Value - Not the configured value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval uint32_t Message RAM Watchdog Counter start value that must be between 0x00 and 0xFF.
  */
uint32_t HAL_FDCAN_GetRamWatchdog(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Read the WDV value and shift 8 bits to lsb */
  return ((READ_REG(p_fdcanx->RWD) & FDCAN_RWD_WDV) >> FDCAN_RWD_WDV_Pos);
}

/**
  * @brief  Configure the timestamp counter.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_timestamp_config Pointer to a structure based on @ref hal_fdcan_timestamp_config_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  */
hal_status_t HAL_FDCAN_SetConfigTimestampCounter(const hal_fdcan_handle_t *hfdcan,
                                                 const hal_fdcan_timestamp_config_t *p_timestamp_config)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_timestamp_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_timestamp_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_FDCAN_TIMESTAMP_PRESCALER(p_timestamp_config->timestamp_prescaler));
  ASSERT_DBG_PARAM(IS_FDCAN_TIMESTAMP_SOURCE(p_timestamp_config->timestamp_source));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Configure prescaler */
  MODIFY_REG(p_fdcanx->TSCC, FDCAN_TSCC_TCP | FDCAN_TSCC_TSS,
             ((uint32_t)(p_timestamp_config->timestamp_prescaler)
              | ((uint32_t)(p_timestamp_config->timestamp_source))));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Get the timestamp counter configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_timestamp_config Pointer to a structure based on @ref hal_fdcan_timestamp_config_t
  */
void HAL_FDCAN_GetConfigTimestampCounter(const hal_fdcan_handle_t *hfdcan,
                                         hal_fdcan_timestamp_config_t *p_timestamp_config)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_timestamp_config != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  register_value = READ_REG(p_fdcanx->TSCC);

  /* Get the timestamp select mode setting */
  p_timestamp_config->timestamp_source    = (hal_fdcan_timestamp_source_t)(uint32_t)(register_value & FDCAN_TSCC_TSS);

  /* Get the Timestamp counter prescaler */
  p_timestamp_config->timestamp_prescaler = (hal_fdcan_timestamp_prescaler_t)(uint32_t)(register_value
                                            & FDCAN_TSCC_TCP);
}

/**
  * @brief  Retrieve the timestamp counter value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @return Timestamp counter value.
  */
uint16_t HAL_FDCAN_GetTimestampCounter(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return ((uint16_t)(READ_REG(p_fdcanx->TSCV)));
}

/**
  * @brief  Reset the timestamp counter to zero.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_ResetTimestampCounter(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if ((p_fdcanx->TSCC & FDCAN_TSCC_TSS) != (uint32_t)HAL_FDCAN_TIMESTAMP_SOURCE_EXTERNAL)
  {
    /* Reset timestamp counter. Any Write access resets the counter to 0 */
    CLEAR_REG(p_fdcanx->TSCV);
  }
  else
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Configure the timeout counter.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_timeout_param Pointer to a structure based on  @ref hal_fdcan_timeout_config_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  */
hal_status_t HAL_FDCAN_SetConfigTimeoutCounter(const hal_fdcan_handle_t *hfdcan,
                                               const hal_fdcan_timeout_config_t *p_timeout_param)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_timeout_param != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_timeout_param == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_TIMEOUT(p_timeout_param->timeout_operation));
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_timeout_param->timeout_period, FDCAN_TIMEOUT_VALUE_MAX));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Modify the timeout select(TOS) and timeout period (TOP) */
  MODIFY_REG(p_fdcanx->TOCC, (FDCAN_TOCC_TOS | FDCAN_TOCC_TOP),
             ((uint32_t)(p_timeout_param->timeout_operation)
              | ((uint32_t)(p_timeout_param->timeout_period) << (uint32_t)FDCAN_TOCC_TOP_Pos)));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the timeout counter configuration.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_timeout_param Pointer to a structure based on @ref hal_fdcan_timeout_config_t
  */
void HAL_FDCAN_GetConfigTimeoutCounter(const hal_fdcan_handle_t *hfdcan, hal_fdcan_timeout_config_t *p_timeout_param)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t register_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_timeout_param != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  register_value = READ_REG(p_fdcanx->TOCC);

  /* Get the Timeout select mode setting */
  p_timeout_param->timeout_operation = (hal_fdcan_timeout_operation_t)(uint32_t)((register_value & FDCAN_TOCC_TOS)
                                                                                 >> FDCAN_TOCC_TOS_Pos);
  /* Get the Timeout period */
  p_timeout_param->timeout_period = ((register_value & FDCAN_TOCC_TOP) >> FDCAN_TOCC_TOP_Pos);

}

/**
  * @brief  Retrieve the timeout counter value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval Value of the timeout counter that must be between 0x0000 and 0xFFFF.
  */
uint32_t HAL_FDCAN_GetTimeoutCounter(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (READ_REG(p_fdcanx->TOCV) & FDCAN_TOCV_TOC_Msk);
}

/**
  * @brief  Enable the timeout counter.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableTimeoutCounter(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable timeout counter (ETOC) */
  SET_BIT(p_fdcanx->TOCC, FDCAN_TOCC_ETOC);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disable the timeout counter.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableTimeoutCounter(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable timeout counter */
  CLEAR_BIT(p_fdcanx->TOCC, FDCAN_TOCC_ETOC);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Check Timeout Counter status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_TIMEOUT_COUNTER_DISABLED Timeout counter is disabled.
  * @retval HAL_FDCAN_TIMEOUT_COUNTER_ENABLED  Timeout counter is enabled.
  */
hal_fdcan_timeout_counter_status_t HAL_FDCAN_IsEnabledTimeoutCounter(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if ((READ_BIT(p_fdcanx->TOCC, FDCAN_TOCC_ETOC) & FDCAN_TOCC_ETOC_Msk) == 1U)
  {
    return HAL_FDCAN_TIMEOUT_COUNTER_ENABLED;
  }
  else
  {
    return HAL_FDCAN_TIMEOUT_COUNTER_DISABLED;
  }
}

/**
  * @brief  Reset the timeout counter to its start value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_ResetTimeoutCounter(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if ((p_fdcanx->TOCC & FDCAN_TOCC_TOS) == (uint32_t)HAL_FDCAN_TIMEOUT_CONTINUOUS)
  {
    /* Reset timeout counter to start value */
    CLEAR_REG(p_fdcanx->TOCV);
  }
  else
  {
    return HAL_ERROR;
  }

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Configure the transmitter delay compensation.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_tx_delay_param Pointer to a structure based on @ref hal_fdcan_tx_delay_compensation_config_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM One parameter is invalid.
  */
hal_status_t HAL_FDCAN_SetConfigTxDelayCompensation(const hal_fdcan_handle_t *hfdcan,
                                                    const hal_fdcan_tx_delay_compensation_config_t *p_tx_delay_param)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_tx_delay_param != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_tx_delay_param == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_tx_delay_param->tx_delay_comp_offset, FDCAN_TX_DELAY_COMP_VALUE_MAX));
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_tx_delay_param->tx_delay_comp_win_length, FDCAN_TX_DELAY_COMP_VALUE_MAX));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Configure TDC offset and filter window */
  p_fdcanx->TDCR = ((((p_tx_delay_param->tx_delay_comp_win_length) << FDCAN_TDCR_TDCF_Pos) & FDCAN_TDCR_TDCF_Msk)
                    | (((p_tx_delay_param->tx_delay_comp_offset) << FDCAN_TDCR_TDCO_Pos) & FDCAN_TDCR_TDCO_Msk));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve the transmitter delay compensation offset.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_tx_delay_param Pointer to a structure based on @ref hal_fdcan_tx_delay_compensation_config_t
  */
void HAL_FDCAN_GetConfigTxDelayCompensation(const hal_fdcan_handle_t *hfdcan,
                                            hal_fdcan_tx_delay_compensation_config_t *p_tx_delay_param)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_tx_delay_param != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Get TdcOffset Transmitter Delay Compensation Offset */
  p_tx_delay_param->tx_delay_comp_offset = (p_fdcanx->TDCR & FDCAN_TDCR_TDCO) >> FDCAN_TDCR_TDCO_Pos;
  /* Get TdcFilter Transmitter Delay Compensation Filter Window Length */
  p_tx_delay_param->tx_delay_comp_win_length = (p_fdcanx->TDCR & FDCAN_TDCR_TDCF) >> FDCAN_TDCR_TDCF_Pos;
}

/**
  * @brief  Enable the transmitter delay compensation.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableTxDelayCompensation(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable transmitter delay compensation */
  SET_BIT(p_fdcanx->DBTP, FDCAN_DBTP_TDC);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disable the transmitter delay compensation.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableTxDelayCompensation(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable transmitter delay compensation */
  CLEAR_BIT(p_fdcanx->DBTP, FDCAN_DBTP_TDC);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Check Transmitter Delay Compensation status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_TX_DLY_COMPENSATION_DISABLED  Transmitter delay compensation is disabled.
  * @retval HAL_FDCAN_TX_DLY_COMPENSATION_ENABLED   Transmitter delay compensation is enabled.
  */
hal_fdcan_transmitter_delay_comp_status_t HAL_FDCAN_IsEnabledTxDelayCompensation(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);
  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Read the bit TDC from DBTP */
  if (((READ_BIT(p_fdcanx->DBTP, FDCAN_DBTP_TDC) & FDCAN_DBTP_TDC_Msk) >> FDCAN_DBTP_TDC_Pos)  == 1U)
  {
    return HAL_FDCAN_TX_DLY_COMPENSATION_ENABLED;
  }
  else
  {
    return HAL_FDCAN_TX_DLY_COMPENSATION_DISABLED;
  }
}

/**
  * @brief  Enable ISO 11898-1 protocol mode.
  *         CAN FD frame format is according to CAN FD specification V1.0.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableISOMode(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable Non ISO protocol mode */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_NISO);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disable ISO 11898-1 protocol mode.
  *         CAN FD frame format is according to CAN FD specification V1.0.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableISOMode(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable Non ISO protocol mode */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_NISO);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Check ISO 11898-1 Protocol Mode status.
  *         CAN FD frame format is according to CAN FD specification V1.0.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_ISO_MODE_DISABLED ISO Mode is disabled.
  * @retval HAL_FDCAN_ISO_MODE_ENABLED  ISO Mode is disabled.
  */
hal_fdcan_iso_mode_status_t HAL_FDCAN_IsEnabledISOMode(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_iso_mode_status_t)(uint32_t)(READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_NISO) >> FDCAN_CCCR_NISO_Pos);
}

/**
  * @brief  Enable edge filtering during bus integration.
  * @note   Two consecutive dominant tq's are required to detect an edge for hard synchronization.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableEdgeFiltering(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable edge filtering */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_EFBI);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disable edge filtering during bus integration.
  * @note   One dominant tq is required to detect an edge for hard synchronization.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableEdgeFiltering(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable edge filtering */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_EFBI);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Check Edge Filtering during bus integration status.
  * @note   One dominant tq is required to detect an edge for hard synchronization.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_EDGE_FILTERING_ENABLED  Edge filtering is enabled.
  * @retval HAL_FDCAN_EDGE_FILTERING_DISABLED Edge filtering is disabled.
  */
hal_fdcan_edge_filtering_status_t HAL_FDCAN_IsEnabledEdgeFiltering(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_edge_filtering_status_t)(uint32_t)(READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_EFBI)
                                                       >> FDCAN_CCCR_EFBI_Pos);
}

/**
  * @brief   Set the FDCAN mode.
  *          This function can only be called from HAL_FDCAN_STATE_IDLE state.
  * @param   hfdcan Pointer to a hal_fdcan_handle_t
  * @param   mode Value of the mode to set based on @ref hal_fdcan_mode_t.
  * @retval  HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetMode(const hal_fdcan_handle_t *hfdcan, hal_fdcan_mode_t mode)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_MODE(mode));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set FDCAN Operating Mode:
               | Normal | Restricted |    Bus     | Internal | External |
               |  mode  | Operation  | Monitoring | LoopBack | LoopBack |
     --------------------------------------------------------------------
     CCCR.TEST |   0    |     0      |     0      |    1     |    1     |
     CCCR.MON  |   0    |     0      |     1      |    1     |    0     |
     TEST.LBCK |   0    |     0      |     0      |    1     |    1     |
     CCCR.ASM  |   0    |     1      |     0      |    0     |    0     |
     --------------------------------------------------------------------
  */

  /* reset the mode combination bit coding*/
  /* Enable Normal operation */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TEST);
  /* Disable Restricted Operation mode - Enable Normal CAN operation */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM);
  /* Bus monitoring mode disabled */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON);

  if (mode == HAL_FDCAN_MODE_RESTRICTED_OPERATION)
  {
    /* Enable Restricted Operation mode */
    SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM);
  }
  else if (mode != HAL_FDCAN_MODE_NORMAL)
  {
    if (mode != HAL_FDCAN_MODE_BUS_MONITORING)
    {
      /* Enable write access to TEST register */
      SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TEST);
      /* Enable External LoopBack mode */
      SET_BIT(p_fdcanx->TEST, FDCAN_TEST_LBCK);

      if (mode == HAL_FDCAN_MODE_INTERNAL_LOOPBACK)
      {
        /* Enable Internal Loopback mode*/
        SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON);
      }
    }
    else
    {
      /* Enable Bus Monitoring mode */
      SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON);
    }
  }
  else
  {
    /* Enable Normal operation */
    CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TEST);
    /* Disable Restricted Operation mode - Enable Normal CAN operation */
    CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM);
    /* Bus monitoring mode disabled */
    CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the FDCAN mode.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval hal_fdcan_mode_t Mode value, this parameter must be a value of @ref hal_fdcan_mode_t.
  */
hal_fdcan_mode_t HAL_FDCAN_GetMode(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  hal_fdcan_mode_t actual_mode;
  uint32_t mode_selection;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Get FDCAN Operating Mode:
               | Normal | Restricted |    Bus     | Internal | External |
               |  mode  | Operation  | Monitoring | LoopBack | LoopBack |
     --------------------------------------------------------------------
     CCCR.TEST |   0    |     0      |     0      |    1     |    1     |
     CCCR.MON  |   0    |     0      |     1      |    1     |    0     |
     TEST.LBCK |   0    |     0      |     0      |    1     |    1     |
     CCCR.ASM  |   0    |     1      |     0      |    0     |    0     |
     --------------------------------------------------------------------
  */

  /* Create a combined nibble TEST-MON-LBCK-ASM from the 4 read bits */
  mode_selection  = (READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM) >> 2);
  mode_selection |= (READ_BIT(p_fdcanx->TEST, FDCAN_TEST_LBCK) >> 3);
  mode_selection |= (READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_MON) >> 3);
  mode_selection |= (READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TEST) >> 4);
  /* Each C statement holds only one access to a volatile variable (iar) */

  switch (mode_selection)
  {
    case 0:
      actual_mode = HAL_FDCAN_MODE_NORMAL;
      break;
    case 1:
      actual_mode = HAL_FDCAN_MODE_RESTRICTED_OPERATION;
      break;
    case 4:
      actual_mode = HAL_FDCAN_MODE_BUS_MONITORING;
      break;
    case 10:
      actual_mode = HAL_FDCAN_MODE_EXTERNAL_LOOPBACK;
      break;
    case 14:
      actual_mode = HAL_FDCAN_MODE_INTERNAL_LOOPBACK;
      break;
    default:
      actual_mode = HAL_FDCAN_MODE_INVALID;
      break;
  }
  return actual_mode;
}

/**
  * @brief  Set Frame Format.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  frame_format Value of the frame format based on @ref hal_fdcan_frame_format_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetFrameFormat(const hal_fdcan_handle_t *hfdcan, hal_fdcan_frame_format_t frame_format)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_FRAME_FORMAT(frame_format));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set FDCAN Frame Format */
  MODIFY_REG(p_fdcanx->CCCR, (uint32_t)HAL_FDCAN_FRAME_FD_BRS, (uint32_t)frame_format);

  return HAL_OK;
}

/**
  * @brief  Retrieve Frame Format.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_FRAME_CLASSIC_CAN Classical CAN.
  * @retval HAL_FDCAN_FRAME_FD_NO_BRS FDCAN with no Bit Rate Switch.
  * @retval HAL_FDCAN_FRAME_FD_BRS FDCAN with Bit rate Switch.
  */
hal_fdcan_frame_format_t HAL_FDCAN_GetFrameFormat(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_frame_format_t)(uint32_t)(READ_REG(p_fdcanx->CCCR) & FDCAN_FRAME_FORMAT_MASK);
}

/**
  * @brief  Set Auto Retransmission value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  auto_retransmit Value based on @ref hal_fdcan_auto_retransmission_status_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetAutoRetransmission(const hal_fdcan_handle_t *hfdcan,
                                             hal_fdcan_auto_retransmission_status_t auto_retransmit)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_AUTO_RETRANSMISSION(auto_retransmit));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set FDCAN Frame Format */
  if (auto_retransmit == HAL_FDCAN_AUTO_RETRANSMISSION_ENABLED)
  {
    CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_DAR);
  }
  else
  {
    SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_DAR);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve Auto retransmission status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_AUTO_RETRANSMISSION_DISABLED Auto retransmission is disabled.
  * @retval HAL_FDCAN_AUTO_RETRANSMISSION_ENABLED  Auto retransmission is enabled.
  */
hal_fdcan_auto_retransmission_status_t HAL_FDCAN_GetAutoRetransmission(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_auto_retransmission_status_t)(uint32_t)((READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_DAR))
                                                            >> FDCAN_CCCR_DAR_Pos);
}

/**
  * @brief  Set Transmit pause value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  transmit_pause Transmit pause value based on @ref hal_fdcan_transmit_pause_status_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetTransmitPause(const hal_fdcan_handle_t *hfdcan,
                                        hal_fdcan_transmit_pause_status_t transmit_pause)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_TRANSMIT_PAUSE(transmit_pause));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set FDCAN Frame Format */
  if (transmit_pause == HAL_FDCAN_TRANSMIT_PAUSE_DISABLED)
  {
    CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TXP);
  }
  else
  {
    SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TXP);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the Transmit Pause status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_TRANSMIT_PAUSE_DISABLED Transmit pause is disabled.
  * @retval HAL_FDCAN_TRANSMIT_PAUSE_ENABLED  Transmit pause is enabled.
  */
hal_fdcan_transmit_pause_status_t HAL_FDCAN_GetTransmitPause(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_transmit_pause_status_t)(uint32_t)((READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_TXP))
                                                       >> FDCAN_CCCR_TXP_Pos);
}

/**
  * @brief  Set Protocol Exception value.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  protocol_exception value based on @ref hal_fdcan_protocol_exception_status_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetProtocolException(const hal_fdcan_handle_t *hfdcan,
                                            hal_fdcan_protocol_exception_status_t protocol_exception)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_PROTOCOL_EXCEPTION(protocol_exception));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set FDCAN Frame Format */
  if (protocol_exception == HAL_FDCAN_PROTOCOL_EXCEPTION_ENABLED)
  {
    CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_PXHD);
  }
  else
  {
    SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_PXHD);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the Protocol Exception status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_PROTOCOL_EXCEPTION_DISABLED Protocol exception is disabled.
  * @retval HAL_FDCAN_PROTOCOL_EXCEPTION_ENABLED  Protocol exception is enabled.
  */
hal_fdcan_protocol_exception_status_t HAL_FDCAN_GetProtocolException(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return (hal_fdcan_protocol_exception_status_t)(uint32_t)((p_fdcanx->CCCR & FDCAN_CCCR_PXHD) >> FDCAN_CCCR_PXHD_Pos);
}

/** @brief  Return the peripheral clock frequency for FDCAN.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle. structure
  * @retval uint32_t Frequency in Hz.
  * @retval 0 source clock of the FDCAN not configured or not ready.
  */
uint32_t HAL_FDCAN_GetClockFreq(const hal_fdcan_handle_t *hfdcan)
{
  /* Check the FDCAN handle & config allocation */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state, the driver must be at least configured */
  ASSERT_DBG_STATE(hfdcan->global_state, HAL_FDCAN_STATE_INIT | HAL_FDCAN_STATE_IDLE | HAL_FDCAN_STATE_ACTIVE);

#if !defined(USE_ASSERT_DBG_STATE) && !defined(USE_ASSERT_DBG_PARAM)
  STM32_UNUSED(hfdcan);
#endif /* STM32_UNUSED */

  return HAL_RCC_FDCAN_GetKernelClkFreq();
}

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register Tx Event FIFO callback to be used instead of the weak HAL_FDCAN_TxEventFifoCallback()
  *         predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Tx Event FIFO Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterTxEventFifoCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_tx_eventfifo_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Rx FIFO 0 callback to be used instead of the weak HAL_FDCAN_RxFifo0Callback() predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Rx FIFO 0 Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterRxFifo0Callback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_rx_fifo0_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Rx FIFO 1 callback to be used instead of the weak HAL_FDCAN_RxFifo1Callback() predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Rx FIFO 1 Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterRxFifo1Callback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_rx_fifo1_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Tx Buffer Complete callback to be used instead of the weak HAL_FDCAN_TxBufferCompleteCallback()
  *         predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Tx Buffer Complete Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterTxBufferCompleteCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_buffer_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_tx_buffercomplete_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Tx Buffer Abort callback to be used instead of the weak HAL_FDCAN_TxBufferAbortCallback()
  *         predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Tx Buffer Abort Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterTxBufferAbortCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_buffer_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_tx_bufferabort_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register High priority Message callback to be used instead of the weak
  *         HAL_FDCAN_HighPriorityMessageCallback() predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the High priority Message Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterHighPriorityMessageCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_highpriority_msg_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Tx FIFO Empty callback to be used instead of the weak HAL_FDCAN_TxFifoEmptyCallback()
  *         predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Tx FIFO Empty Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterTxFifoEmptyCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_tx_fifoempty_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Timestamp WrapAround callback to be used instead of the weak
  *         HAL_FDCAN_TimestampWraparoundCallback() predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the Timestamp WrapAround Callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterTimestampWraparoundCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);
  hfdcan->p_ts_wraparound_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register Error callback to be used instead of the weak HAL_FDCAN_ErrorCallback() predefined callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_callback Pointer to the FDCAN Error callback function.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_RegisterErrorCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE);

  hfdcan->p_error_cb = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group4
  * @{
A set of functions allowing to control the peripheral and initiate an operation on the bus:
    - HAL_FDCAN_Start()                           : Start the FDCAN module
    - HAL_FDCAN_Stop()                            : Stop the FDCAN module and enable access to configuration registers
    - HAL_FDCAN_ReqTransmitMsgFromFIFOQ()         : Add a message to the Tx FIFO/Queue and activate the corresponding
                                                    transmission request
    - HAL_FDCAN_GetLatestTxFifoQRequestBuffer()   : Retrieve the Tx buffer index of latest Tx FIFO/Queue request
    - HAL_FDCAN_ReqAbortOfTxBuffer()              : Abort transmission request
    - HAL_FDCAN_GetReceivedMessage()              : Retrieve an FDCAN frame from the Rx FIFO zone into the message RAM
    - HAL_FDCAN_GetTxEvent()                      : Retrieve an FDCAN Tx event from the Tx Event FIFO zone
                                                    into the message RAM
    - HAL_FDCAN_GetHighPriorityMessageStatus()    : Retrieve the high priority message status
    - HAL_FDCAN_GetProtocolStatus()               : Retrieve the protocol status
    - HAL_FDCAN_GetErrorCounters()                : Retrieve the error counter values
    - HAL_FDCAN_GetTxBufferMessageStatus()        : Check if a transmission request is pending
                                                    on the selected Tx buffer
    - HAL_FDCAN_GetRxFifoFillLevel()              : Retrieve the Rx FIFO fill level
    - HAL_FDCAN_GetTxFifoFreeLevel()              : Retrieve the Tx FIFO free level
    - HAL_FDCAN_EnableRestrictedOperationMode()   : Enable the restricted operation mode
    - HAL_FDCAN_DisableRestrictedOperationMode()  : Disable the restricted operation mode
    - HAL_FDCAN_IsEnabledRestrictedOperationMode(): Check if the FDCAN peripheral entered Restricted Operation Mode
  */

/**
  * @brief  Start the FDCAN module.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_Start(hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hfdcan == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);
  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Request leave initialisation */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_INIT);

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  /* Reset the FDCAN ErrorCode */
  hfdcan->last_error_codes = HAL_FDCAN_ERROR_NONE;
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

  /* Set the state to Running */
  hfdcan->global_state = HAL_FDCAN_STATE_ACTIVE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Stop the FDCAN module and enable access to configuration registers.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_Stop(hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t tick_start;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hfdcan == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check and update the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Leave the Power Down mode if set => CSR & CSA set        */
  /* Because setting INIT bit has no effect in PowerDown mode */

  /* Reset clock stop request */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CSR);

  /* Get tick */
  tick_start = HAL_GetTick();

  /* Wait until FDCAN exits sleep mode */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
  {
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }

  /* Because HAL_FDCAN_Stop set the global state machine in HAL_FDCAN_STATE_IDLE */
  /* CCCR bits INIT and CCE from CCCR are set to 1                               */
  /* Request initialisation INIT bit from CCCR */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_INIT);
  /* Get tick */
  tick_start = HAL_GetTick();
  /* Wait until the INIT bit into CCCR register is set */
  while ((p_fdcanx->CCCR & FDCAN_CCCR_INIT) == 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tick_start) > FDCAN_TIMEOUT_VALUE)
    {
      return HAL_ERROR;
    }
  }
  /* Enable configuration change CCE bit from CCCR */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_CCE);

  /* Reset Latest Tx FIFO/Queue Request Buffer Index */
  hfdcan->latest_tx_fifo_q_request = 0U;

  /* Change FDCAN peripheral state */
  hfdcan->global_state = HAL_FDCAN_STATE_IDLE;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Add a message to the Tx FIFO/Queue and activate the corresponding transmission request.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_tx_element_header Pointer to a structure based on @ref hal_fdcan_tx_header_t.
  * @param  p_tx_data Pointer to a buffer containing the payload of the Tx frame.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_ReqTransmitMsgFromFIFOQ(hal_fdcan_handle_t *hfdcan,
                                               const hal_fdcan_tx_header_t *p_tx_element_header,
                                               const uint8_t *p_tx_data)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t put_index;
  hal_fdcan_tx_header_t tx_element_header;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_tx_data != NULL));
  ASSERT_DBG_PARAM((p_tx_element_header != NULL));

  /* No assert on the parameters because they are bit fields which binary combinations are all used */
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_tx_element_header == NULL) || (p_tx_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (p_tx_element_header->b.identifier_type == (uint32_t)HAL_FDCAN_ID_STANDARD)
  {
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_tx_element_header->b.identifier, FDCAN_STD_ID_MAX_VALUE));
  }
  else
  {
    ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_tx_element_header->b.identifier, FDCAN_EXT_ID_MAX_VALUE));
  }
  ASSERT_DBG_PARAM(IS_FDCAN_MAX_VALUE(p_tx_element_header->b.message_marker,
                                      FDCAN_MESSAGE_MARKER_MAX_VALUE));
  ASSERT_DBG_PARAM(IS_FDCAN_DLC(p_tx_element_header->b.data_length));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);
  /* Check that the Tx FIFO/Queue is not full */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_FIFO_NOT_FULL(p_fdcanx->TXFQS));

  tx_element_header = *p_tx_element_header;
  /* A standard identifier has to be written to ID[28:18] */
  if (tx_element_header.b.identifier_type == (uint32_t)HAL_FDCAN_ID_STANDARD)
  {
    tx_element_header.b.identifier <<= FDCAN_STD_FILTER_ID_POS;
  }

  /* Retrieve the Tx FIFO put_index */
  put_index = ((p_fdcanx->TXFQS & FDCAN_TXFQS_TFQPI) >> FDCAN_TXFQS_TFQPI_Pos);
  /* Add the message to the Tx FIFO/Queue */
  FDCAN_copyMessageToRAM(hfdcan, &tx_element_header, p_tx_data, put_index);

  /* Activate the corresponding transmission request */
  p_fdcanx->TXBAR = ((uint32_t)1 << put_index);

  /* Store the Latest Tx FIFO/Queue Request Buffer Index */
  hfdcan->latest_tx_fifo_q_request = ((uint32_t)1 << put_index);

  return HAL_OK;
}

/**
  * @brief  Retrieve Tx FIFO status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_FIFO_STATUS_FREE Tx FIFO is not full.
  * @retval HAL_FDCAN_FIFO_STATUS_FULL Tx FIFO is full.
  */
hal_fdcan_fifo_status_t HAL_FDCAN_GetTxFifoStatus(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t tx_fifo_queue_status_register;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Determine if the Tx Buffer is used as FIFO or Queue */
  tx_fifo_queue_status_register = READ_REG(p_fdcanx->TXFQS);

  /* Tx FIFO/queue full is common to FIFO full and queue full */
  if ((tx_fifo_queue_status_register & FDCAN_TXFQS_TFQF) == 0U)
  {
    return HAL_FDCAN_FIFO_STATUS_FREE;
  }
  else
  {
    return HAL_FDCAN_FIFO_STATUS_FULL;
  }
}

/**
  * @brief  Retrieve the Tx buffer index of latest Tx FIFO/Queue request.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval uint32_t Tx buffer index of last Tx FIFO/Queue request.
  *          - Any value of @arg uint32_t if Tx request has been submitted.
  *          - 0 if no Tx FIFO/Queue request have been submitted.
  */
uint32_t HAL_FDCAN_GetLatestTxFifoQRequestBuffer(const hal_fdcan_handle_t *hfdcan)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Return Last Tx FIFO/Queue Request Buffer */
  return (hfdcan->latest_tx_fifo_q_request);
}

/**
  * @brief  Return Tx FIFO free level: number of consecutive free Tx FIFO.
  *         elements starting from Tx FIFO get_index.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval Tx FIFO free level must be a value of @ref hal_fdcan_tx_fifo_free_level_t.
  */
hal_fdcan_tx_fifo_free_level_t HAL_FDCAN_GetTxFifoFreeLevel(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (READ_BIT(p_fdcanx->TXBC, FDCAN_TXBC_TFQM) == (uint32_t)HAL_FDCAN_TX_MODE_QUEUE)
  {
    return HAL_FDCAN_TX_FIFO_FREE_LEVEL_0;
  }
  else
  {
    return (hal_fdcan_tx_fifo_free_level_t)(uint32_t)(p_fdcanx->TXFQS & FDCAN_TXFQS_TFFL);
  }
}

/**
  * @brief  Abort transmission request.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_index buffer index.
  *         This parameter can be any combination of @ref FDCAN_IT_Tx_Abort_Buffers_select.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_ReqAbortOfTxBuffer(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_index)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_TX_LOCATION_LIST(buffer_index));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Add cancellation request */
  p_fdcanx->TXBCR = buffer_index;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Retrieve an FDCAN Tx event from the Tx Event FIFO zone into the message RAM.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_tx_event Pointer to a hal_fdcan_tx_event_fifo_t structure.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR FIFO empty.
  */
hal_status_t HAL_FDCAN_GetTxEvent(const hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_evt_fifo_header_t *p_tx_event)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  const uint32_t *tx_event_address;
  uint32_t get_index;
  uint32_t most_significant_word;
  uint32_t least_significant_word;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_tx_event != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_tx_event == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Check that the Tx event FIFO is not empty */
  if ((p_fdcanx->TXEFS & FDCAN_TXEFS_EFFL) == 0U)
  {
    return HAL_ERROR;
  }

  /* Check if  the Tx event FIFO is not empty */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_EVENT_FIFO_NOT_EMPTY(p_fdcanx->TXEFS));

  /* Calculate Tx event FIFO element address */
  get_index = ((p_fdcanx->TXEFS & FDCAN_TXEFS_EFGI) >> FDCAN_TXEFS_EFGI_Pos);
  tx_event_address = (uint32_t *)(hfdcan->msg_ram.tx_event_start_addr + (get_index * SRAMCAN_TEF_SIZE));

  /* Retrieve the Tx event Element E0 word - esi, xtd, rtr, id fields */
  least_significant_word = (uint32_t)(*tx_event_address);

  /* Increment tx_event_address pointer to second word of Tx Event FIFO element */
  tx_event_address++;

  /* Retrieve the Tx event Element E1 word - mm, et, edl, brs, dlc, txtx fields */
  most_significant_word = (uint32_t)(*tx_event_address);

  /* Build the 64-bit Tx Event header */
  p_tx_event->d64 = ((uint64_t)most_significant_word << 32U) | (uint64_t)least_significant_word;

  /* A standard identifier has to be written to ID[28:18] */
  if (p_tx_event->b.identifier_type == (uint32_t)HAL_FDCAN_ID_STANDARD)
  {
    /* Shift ID */
    p_tx_event->b.identifier >>= FDCAN_STD_FILTER_ID_POS;
  }

  /* Acknowledge the Tx Event FIFO that the oldest element is read so that it increments the get_index */
  p_fdcanx->TXEFA = get_index;

  return HAL_OK;
}

/**
  * @brief  Check if a transmission request is pending on the selected Tx buffer.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  tx_buffer_index Transmission buffer index.
  *         This parameter can be any combination of @ref FDCAN_Tx_Buffer_location.
  * @retval HAL_FDCAN_BUFFER_NOT_PENDING a transmission is still pending.
  * @retval HAL_FDCAN_BUFFER_PENDING     no transmission is pending.
  */
hal_fdcan_buffer_status_t HAL_FDCAN_GetTxBufferMessageStatus(const hal_fdcan_handle_t *hfdcan,
                                                             uint32_t tx_buffer_index)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_LOCATION_LIST((uint32_t)tx_buffer_index));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Check pending transmission request on the selected buffer */
  if ((p_fdcanx->TXBRP & (uint32_t)tx_buffer_index) == 0U)
  {
    return HAL_FDCAN_BUFFER_NOT_PENDING;
  }
  return HAL_FDCAN_BUFFER_PENDING;
}

/**
  * @brief  Retrieve an FDCAN frame from the Rx FIFO zone into the message RAM.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  rx_location Location of the received message to be read.
  * @param  p_rx_header Pointer to the Rx header element to fill.
  * @param  p_rx_data Pointer to a buffer where the payload of the Rx message will be stored.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR Rx FIFO empty.
  */
hal_status_t HAL_FDCAN_GetReceivedMessage(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_location,
                                          hal_fdcan_rx_header_t *p_rx_header, uint8_t *p_rx_data)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t *rx_address;
  uint8_t  *p_data;
  uint32_t byte_count;
  uint32_t get_index = 0;
  uint32_t most_significant_word;
  uint32_t least_significant_word;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_rx_header != NULL));
  ASSERT_DBG_PARAM((p_rx_data != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_RX_FIFO(rx_location));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_rx_header == NULL) || (p_rx_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (rx_location == HAL_FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
  {
    /* Check that the Rx FIFO 0 is not empty */
    if ((p_fdcanx->RXF0S & FDCAN_RXF0S_F0FL) == 0U)
    {
      return HAL_ERROR;
    }
    /* Check if  the Rx FIFO 0 is not empty */
    ASSERT_DBG_PARAM(IS_FDCAN_RX_EVENT_FIFO0_NOT_EMPTY(p_fdcanx->RXF0S));

    /* Check if  the Rx FIFO 0 is full & overwrite mode is on */
    if (((p_fdcanx->RXF0S & FDCAN_RXF0S_F0F) >> FDCAN_RXF0S_F0F_Pos) == 1U)
    {
      if (((p_fdcanx->RXGFC & FDCAN_RXGFC_F0OM) >> FDCAN_RXGFC_F0OM_Pos) == (uint32_t)HAL_FDCAN_RX_FIFO_OVERWRITE)
      {
        /* When overwrite status is on discard first message in FIFO */
        get_index = 1U;
      }
    }
    /* Calculate Rx FIFO 0 element index */
    get_index += ((p_fdcanx->RXF0S & FDCAN_RXF0S_F0GI) >> FDCAN_RXF0S_F0GI_Pos);
    /* Calculate Rx FIFO 0 element address */
    rx_address = (uint32_t *)(hfdcan->msg_ram.rx_fifo0_start_addr + (get_index * SRAMCAN_RF0_SIZE));
  }
  else /* Rx element is assigned to the Rx FIFO 1 */
  {
    /* Check that the Rx FIFO 1 is not empty */
    if ((p_fdcanx->RXF1S & FDCAN_RXF1S_F1FL) == 0U)
    {
      return HAL_ERROR;
    }
    /* Check if  the Rx FIFO 1 is not empty */
    ASSERT_DBG_PARAM(IS_FDCAN_RX_EVENT_FIFO1_NOT_EMPTY(p_fdcanx->RXF1S));

    /* Check if  the Rx FIFO 1 is full & overwrite mode is on */
    if (((p_fdcanx->RXF1S & FDCAN_RXF1S_F1F) >> FDCAN_RXF1S_F1F_Pos) == 1U)
    {
      if (((p_fdcanx->RXGFC & FDCAN_RXGFC_F1OM) >> FDCAN_RXGFC_F1OM_Pos) == (uint32_t)HAL_FDCAN_RX_FIFO_OVERWRITE)
      {
        /* When overwrite status is on discard first message in FIFO */
        get_index = 1U;
      }
    }
    /* Calculate Rx FIFO 1 element index */
    get_index += ((p_fdcanx->RXF1S & FDCAN_RXF1S_F1GI) >> FDCAN_RXF1S_F1GI_Pos);
    /* Calculate Rx FIFO 1 element address */
    rx_address = (uint32_t *)(hfdcan->msg_ram.rx_fifo1_start_addr + (get_index * SRAMCAN_RF1_SIZE));
  }

  /* Read the first word of the Rx FIFO element - R0 */
  least_significant_word = (uint32_t)(*rx_address);

  /* Increment rx_address pointer to payload of Rx FIFO element - R2....Rn */
  rx_address++;

  /* Read the second word of the Rx FIFO element - R1 */
  most_significant_word = (uint32_t)(*rx_address);

  /* Build the 64-bit Tx Event header */
  p_rx_header->d64 = ((uint64_t)most_significant_word << 32U) | (uint64_t)least_significant_word;

  /* A standard identifier has to be written to ID[28:18] */
  if (p_rx_header->b.identifier_type == (uint32_t)HAL_FDCAN_ID_STANDARD)
  {
    p_rx_header->b.identifier >>= FDCAN_STD_FILTER_ID_POS;
  }

  /* Increment rx_address pointer to payload of Rx FIFO element - R2....Rn */
  rx_address++;

  /* Retrieve Rx payload */
  p_data = (uint8_t *)rx_address;
  for (byte_count = 0; byte_count < DLCtoBytes[p_rx_header->b.data_length]; byte_count++)
  {
    p_rx_data[byte_count] = p_data[byte_count];
  }

  if (rx_location == HAL_FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
  {
    /* Acknowledge the Rx FIFO 0 that the oldest element is read so that it increments the get_index */
    p_fdcanx->RXF0A = get_index;
  }
  else /* Rx element is assigned to the Rx FIFO 1 */
  {
    /* Acknowledge the Rx FIFO 1 that the oldest element is read so that it increments the get_index */
    p_fdcanx->RXF1A = get_index;
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the Rx FIFO fill level.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  rx_fifo_sel This parameter must be a value of @ref hal_fdcan_rx_location_t
  * @param  p_fill_level Pointer to the Rx FIFO fill level
  */
void HAL_FDCAN_GetRxFifoFillLevel(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_sel,
                                  uint32_t *p_fill_level)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_fill_level != NULL));
  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_RX_FIFO(rx_fifo_sel));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (rx_fifo_sel == HAL_FDCAN_RX_FIFO0)
  {
    *p_fill_level = (p_fdcanx->RXF0S & FDCAN_RXF0S_F0FL);
  }
  else /* rx_fifo_sel == FDCAN_RX_FIFO1 */
  {
    *p_fill_level = (p_fdcanx->RXF1S & FDCAN_RXF1S_F1FL);
  }
}

/**
  * @brief  Retrieve the high priority message status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_hp_msg_status Pointer to a structure based on @ref hal_fdcan_high_prio_msg_status_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_GetHighPriorityMessageStatus(const hal_fdcan_handle_t *hfdcan,
                                                    hal_fdcan_high_prio_msg_status_t *p_hp_msg_status)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_hp_msg_status != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_hp_msg_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  p_hp_msg_status->filter_list = (hal_fdcan_high_prio_filter_list_t)(uint32_t)((p_fdcanx->HPMS & FDCAN_HPMS_FLST)
                                                                               >> FDCAN_HPMS_FLST_Pos);
  p_hp_msg_status->filter_index = ((p_fdcanx->HPMS & FDCAN_HPMS_FIDX) >> FDCAN_HPMS_FIDX_Pos);
  p_hp_msg_status->message_location_status = (hal_fdcan_high_prio_storage_t)(uint32_t)(p_fdcanx->HPMS
                                             & FDCAN_HPMS_MSI);
  p_hp_msg_status->message_index = (p_fdcanx->HPMS & FDCAN_HPMS_BIDX);

  return HAL_OK;
}

/**
  * @brief  Retrieve the protocol status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_protocol_status Pointer to a structure based on hal_fdcan_protocol_status_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_GetProtocolStatus(const hal_fdcan_handle_t *hfdcan,
                                         hal_fdcan_protocol_status_t *p_protocol_status)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t reg_status;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_protocol_status != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_protocol_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Read the protocol status register */
  reg_status = READ_REG(p_fdcanx->PSR);

  /* Fill the protocol status structure */
  p_protocol_status->last_error_code = (hal_fdcan_protocol_error_code_t)(uint32_t)(reg_status & FDCAN_PSR_LEC);
  p_protocol_status->data_last_error_code = (hal_fdcan_protocol_error_code_t)(uint32_t)((reg_status & FDCAN_PSR_DLEC)
                                            >> FDCAN_PSR_DLEC_Pos);
  p_protocol_status->activity = (hal_fdcan_communication_state_t)(uint32_t)(reg_status & FDCAN_PSR_ACT);
  p_protocol_status->error_status = (hal_fdcan_protocol_error_status_t)(uint32_t)((reg_status & FDCAN_PSR_EP)
                                                                                  >> FDCAN_PSR_EP_Pos);
  p_protocol_status->error_warning = (hal_fdcan_warning_status_t)(uint32_t)((reg_status & FDCAN_PSR_EW)
                                                                            >> FDCAN_PSR_EW_Pos);
  p_protocol_status->bus_off = (hal_fdcan_bus_off_status_t)(uint32_t)((reg_status & FDCAN_PSR_BO) >> FDCAN_PSR_BO_Pos);
  p_protocol_status->rx_esi_flag = (hal_fdcan_esi_flag_status_t)(uint32_t)((reg_status & FDCAN_PSR_RESI)
                                                                           >> FDCAN_PSR_RESI_Pos);
  p_protocol_status->rx_brs_flag = (hal_fdcan_brs_flag_status_t)(uint32_t)((reg_status & FDCAN_PSR_RBRS)
                                                                           >> FDCAN_PSR_RBRS_Pos);
  p_protocol_status->rx_fdf_flag = (hal_fdcan_edl_flag_status_t)(uint32_t)((reg_status & FDCAN_PSR_REDL)
                                                                           >> FDCAN_PSR_REDL_Pos);
  p_protocol_status->protocol_exception = (hal_fdcan_protocol_exception_event_t)(uint32_t)((reg_status & FDCAN_PSR_PXE)
                                          >> FDCAN_PSR_PXE_Pos);
  p_protocol_status->tdc_value = ((reg_status & FDCAN_PSR_TDCV) >> FDCAN_PSR_TDCV_Pos);

  return HAL_OK;
}

/**
  * @brief  Retrieve the error counter values.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_error_counters Pointer to a structure based on @ref hal_fdcan_error_counters_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_FDCAN_GetErrorCounters(const hal_fdcan_handle_t *hfdcan,
                                        hal_fdcan_error_counters_t *p_error_counters)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t error_counter_reg;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM((p_error_counters != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_error_counters == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Read the error counters register */
  error_counter_reg = READ_REG(p_fdcanx->ECR);

  /* Fill the error counters structure */
  p_error_counters->tx_error_cnt = ((error_counter_reg & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
  p_error_counters->rx_error_cnt = ((error_counter_reg & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
  p_error_counters->rx_error_passive_status = (hal_fdcan_rx_error_passive_level_t)(uint32_t)
                                              ((error_counter_reg & FDCAN_ECR_RP) >> FDCAN_ECR_RP_Pos);
  p_error_counters->global_cnt = ((error_counter_reg & FDCAN_ECR_CEL) >> FDCAN_ECR_CEL_Pos);

  return HAL_OK;
}

/**
  * @brief  Enable the Restricted Operation Mode.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* When INIT and CCE set to 1 then the bit ASM can be set */
  SET_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disable the Restricted Operation Mode.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* When INIT and CCE set to 1 then the bit ASM can be set */
  CLEAR_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Check the FDCAN Restricted Operation Mode status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval HAL_FDCAN_RESTRICTED_MODE_DISABLED Normal FDCAN operation.
  * @retval HAL_FDCAN_RESTRICTED_MODE_ENABLED Restricted Operation Mode active.
  */
hal_fdcan_restricted_op_mode_status_t HAL_FDCAN_IsEnabledRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t operation_mode;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Get Operation Mode */
  operation_mode = (READ_BIT(p_fdcanx->CCCR, FDCAN_CCCR_ASM) >> FDCAN_CCCR_ASM_Pos);
  if (operation_mode == 0U)
  {
    return HAL_FDCAN_RESTRICTED_MODE_DISABLED;
  }
  else
  {
    return HAL_FDCAN_RESTRICTED_MODE_ENABLED;
  }
}


/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group5
  * @{
A set of functions allowing to deal with interruptions of the peripheral:
    - HAL_FDCAN_SetInterruptGroupsToLine()               : Assign interrupt groups to either interrupt line 0 or 1
    - HAL_FDCAN_GetLineFromInterruptGroup()              : Retrieve the line associated to an interrupt group
    - HAL_FDCAN_EnableInterrupts()                       : Enable interrupt sources
    - HAL_FDCAN_DisableInterrupts()                      : Disable interrupt sources
    - HAL_FDCAN_IsEnabledInterrupt()                     : Check if a given interrupt source is enabled
    - HAL_FDCAN_EnableInterruptLines()                   : Enable the given interrupt line
    - HAL_FDCAN_DisableInterruptLines()                  : Disable the given interrupt line
    - HAL_FDCAN_IsEnabledInterruptLine()                 : Check if a given interrupt line is enabled
    - HAL_FDCAN_EnableTxBufferCompleteInterrupts()       : Enable interrupt for Tx buffer Complete
    - HAL_FDCAN_DisableTxBufferCompleteInterrupts()      : Disable interrupt for Tx buffer Complete
    - HAL_FDCAN_IsEnabledTxBufferCompleteInterrupt()     : Check if interrupt for Tx buffer Complete is enabled
    - HAL_FDCAN_EnableTxBufferCancellationInterrupts()   : Enable interrupt for Tx buffer cancellation finished
    - HAL_FDCAN_DisableTxBufferCancellationInterrupts()  : Disable interrupt for Tx buffer cancellation finished
    - HAL_FDCAN_IsEnabledTxBufferCancellationInterrupt() : Check if interrupt for Tx buffer cancellation finished is
                                                           enabled
    - HAL_FDCAN_IRQHandler()                             : FDCAN interrupt request handler
  */

/**
  * @brief  Processes the FDCAN interrupt requests.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  */
void HAL_FDCAN_IRQHandler(hal_fdcan_handle_t *hfdcan)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  uint32_t ir_reg_value;
  uint32_t ie_reg_value;
  uint32_t tx_event_fifo_its;
  uint32_t rx_fifo0_its;
  uint32_t rx_fifo1_its;
  uint32_t transmitted_buffers;
  uint32_t aborted_buffers;
  uint32_t it_sources;
  uint32_t it_flags;
#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1U)
  uint32_t error_flags;
  uint32_t error_code = HAL_FDCAN_ERROR_NONE;
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);
  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Read the FDCAN interrupt register */
  ir_reg_value = READ_REG(p_fdcanx->IR);
  /* Read the FDCAN interrupt enable register */
  ie_reg_value = READ_REG(p_fdcanx->IE);

  /* Read if there is an IT related to Tx Event Group
        - Tx event FIFO new entry interrupt     - TEFN
        - Tx event FIFO full interrupt          - TEFF
        - Tx event FIFO element lost interrupt  - TEFL          */
  tx_event_fifo_its = ir_reg_value & FDCAN_TX_EVENT_FIFO_MASK;
  /* Filter only the authorized IT                              */
  tx_event_fifo_its &= ie_reg_value;

  /* Read if there is an IT related to Rx FIFO0 Group
        - Rx FIFO 0 new message interrupt       - RF0N
        - Rx FIFO 0 full interrupt              - RF0F
        - Rx FIFO 0 message lost interrupt      - RF0L          */
  rx_fifo0_its = ir_reg_value & FDCAN_RX_FIFO0_MASK;
  /* Filter only the authorized IT                              */
  rx_fifo0_its &= ie_reg_value;

  /* Read if there is an IT related to Rx FIFO1 Group
        - Rx FIFO 1 new message interrupt       - RF1N
        - Rx FIFO 1 full interrupt              - RF1F
        - Rx FIFO 1 message lost interrupt      - RF1L          */
  rx_fifo1_its = ir_reg_value & FDCAN_RX_FIFO1_MASK;
  /* Filter only the authorized IT                              */
  rx_fifo1_its &= ie_reg_value;

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  /* Read if there is an IT related to General Errors (HW) Group + Bus Fault Confinement
        - Error logging overflow interrupt      - ELO
        - Watchdog interrupt                    - WDI
        - Protocol error in arbitration phase   - PEA
        - Protocol error in data phase          - PED
        - Access to reserved address            - ARA
        - Message RAM access failure            - MRAF
        - Timeout occurred                      - TOO
        - Bus_Off                               - BO
        - Warning status                        - EW
        - Error passive                         - EP          */

  error_flags = ir_reg_value & FDCAN_ERROR_MASK;
  /* Filter only the authorized IT                            */
  error_flags &= ie_reg_value;
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

  /* Read if there is any raised Interrupt    */
  it_flags = ir_reg_value;
  /* Read the Interrupt Enable register       */
  it_sources = ie_reg_value;

  /* High Priority Message interrupt management: FDCAN_IR_HPM */
  if (FDCAN_CHECK_IT_SOURCE(it_sources, (HAL_FDCAN_IT_RX_HIGH_PRIORITY_MSG & HAL_FDCAN_IR_MASK)) != RESET)
  {
    if (FDCAN_CHECK_FLAG(it_flags, HAL_FDCAN_FLAG_RX_HIGH_PRIORITY_MSG) != RESET)
    {
      /* Clear the High Priority Message flag */
      FDCAN_CLEAR_FLAG(hfdcan, HAL_FDCAN_FLAG_RX_HIGH_PRIORITY_MSG);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
      /* Call registered callback*/
      hfdcan->p_highpriority_msg_cb(hfdcan);
#else
      /* High Priority Message Callback */
      HAL_FDCAN_HighPriorityMessageCallback(hfdcan);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
    }
  }

  /* Rx FIFO0 interrupts management: FDCAN_IR_RF0L, FDCAN_IR_RF0F, FDCAN_IR_RF0N */
  if (rx_fifo0_its != 0U)
  {
    /* Clear the Rx FIFO 0 flags */
    FDCAN_CLEAR_FLAG(hfdcan, rx_fifo0_its);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
    /* Call registered callback*/
    hfdcan->p_rx_fifo0_cb(hfdcan, rx_fifo0_its);
#else
    /* Rx FIFO 0 Callback */
    HAL_FDCAN_RxFifo0Callback(hfdcan, rx_fifo0_its);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
  }

  /* Rx FIFO1 interrupts management: FDCAN_IR_RF1L, FDCAN_IR_RF1F, FDCAN_IR_RF1N */
  if (rx_fifo1_its != 0U)
  {
    /* Clear the Rx FIFO 1 flags */
    FDCAN_CLEAR_FLAG(hfdcan, rx_fifo1_its);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
    /* Call registered callback*/
    hfdcan->p_rx_fifo1_cb(hfdcan, rx_fifo1_its);
#else
    /* Rx FIFO 1 Callback */
    HAL_FDCAN_RxFifo1Callback(hfdcan, rx_fifo1_its);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
  }

  /* Transmission Abort interrupt management: FDCAN_IE_TCFE */
  if (FDCAN_CHECK_IT_SOURCE(it_sources, (HAL_FDCAN_IT_TX_ABORT_COMPLETE & HAL_FDCAN_IR_MASK)) != RESET)
  {
    if (FDCAN_CHECK_FLAG(it_flags, HAL_FDCAN_FLAG_TX_ABORT_COMPLETE) != RESET)
    {
      /* List of aborted monitored buffers */
      aborted_buffers = p_fdcanx->TXBCF;
      aborted_buffers &= p_fdcanx->TXBCIE;
      /* Clear the Transmission Cancellation flag */
      FDCAN_CLEAR_FLAG(hfdcan, HAL_FDCAN_FLAG_TX_ABORT_COMPLETE);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
      /* Call registered callback*/
      hfdcan->p_tx_bufferabort_cb(hfdcan, aborted_buffers);
#else
      /* Transmission Cancellation Callback */
      HAL_FDCAN_TxBufferAbortCallback(hfdcan, aborted_buffers);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
    }
  }

  /* Tx event FIFO interrupts management: FDCAN_IR_TEFL, FDCAN_IR_TEFF, FDCAN_IR_TEFN */
  if (tx_event_fifo_its != 0U)
  {
    /* Clear the Tx Event FIFO flags */
    FDCAN_CLEAR_FLAG(hfdcan, tx_event_fifo_its);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
    /* Call registered callback*/
    hfdcan->p_tx_eventfifo_cb(hfdcan, tx_event_fifo_its);
#else
    /* Tx Event FIFO Callback */
    HAL_FDCAN_TxEventFifoCallback(hfdcan, tx_event_fifo_its);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
  }

  if (FDCAN_CHECK_IT_SOURCE(it_sources, (HAL_FDCAN_IT_TX_FIFO_EMPTY & HAL_FDCAN_IR_MASK)) != RESET)
  {
    /* Tx FIFO empty interrupt management: FDCAN_IR_TFE */
    if (FDCAN_CHECK_FLAG(it_flags, HAL_FDCAN_FLAG_TX_FIFO_EMPTY) != RESET)
    {
      /* Clear the Tx FIFO empty flag */
      FDCAN_CLEAR_FLAG(hfdcan, HAL_FDCAN_FLAG_TX_FIFO_EMPTY);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
      /* Call registered callback*/
      hfdcan->p_tx_fifoempty_cb(hfdcan);
#else
      /* Tx FIFO empty Callback */
      HAL_FDCAN_TxFifoEmptyCallback(hfdcan);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
    }
  }

  /* Transmission Complete interrupt management: FDCAN_IR_TC */
  if (FDCAN_CHECK_IT_SOURCE(it_sources, (HAL_FDCAN_IT_TX_COMPLETE & HAL_FDCAN_IR_MASK)) != RESET)
  {
    if (FDCAN_CHECK_FLAG(it_flags, HAL_FDCAN_FLAG_TX_COMPLETE) != RESET)
    {
      /* List of transmitted monitored buffers */
      transmitted_buffers = p_fdcanx->TXBTO;
      transmitted_buffers &= p_fdcanx->TXBTIE;
      /* Clear the Transmission Complete flag */
      FDCAN_CLEAR_FLAG(hfdcan, HAL_FDCAN_FLAG_TX_COMPLETE);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
      /* Call registered callback*/
      hfdcan->p_tx_buffercomplete_cb(hfdcan, transmitted_buffers);
#else
      /* Transmission Complete Callback */
      HAL_FDCAN_TxBufferCompleteCallback(hfdcan, transmitted_buffers);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
    }
  }

  /* Timestamp Wraparound interrupt management: FDCAN_IR_TSW */
  if (FDCAN_CHECK_IT_SOURCE(it_sources, (HAL_FDCAN_IT_TIMESTAMP_WRAPAROUND & HAL_FDCAN_IR_MASK)) != RESET)
  {
    if (FDCAN_CHECK_FLAG(it_flags, HAL_FDCAN_FLAG_TIMESTAMP_WRAPAROUND) != RESET)
    {
      /* Clear the Timestamp Wraparound flag */
      FDCAN_CLEAR_FLAG(hfdcan, HAL_FDCAN_FLAG_TIMESTAMP_WRAPAROUND);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
      /* Call registered callback*/
      hfdcan->p_ts_wraparound_cb(hfdcan);
#else
      /* Timestamp Wraparound Callback */
      HAL_FDCAN_TimestampWraparoundCallback(hfdcan);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
    }
  }

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  /* Error FDCAN interrupts management: FDCAN_IR_ELO, FDCAN_IR_WDI, FDCAN_IR_PEA, FDCAN_IR_PED, FDCAN_IR_ARA,
                                        FDCAN_IR_TOO, FDCAN_IR_MRAF, FDCAN_IR_EP, FDCAN_IR_EW, FDCAN_IR_BO            */
  if (error_flags != 0U)
  {
    if ((error_flags & HAL_FDCAN_FLAG_ERROR_PASSIVE) != 0U)
    {
      /* HAL_FDCAN_FLAG_ERROR_PASSIVE           FDCAN_IR_EP   */
      error_code |= HAL_FDCAN_ERROR_BUS_FAULT_PASSIVE;
    }

    if ((error_flags & HAL_FDCAN_FLAG_ERROR_WARNING) != 0U)
    {
      /* HAL_FDCAN_FLAG_ERROR_WARNING           FDCAN_IR_EW   */
      error_code |= HAL_FDCAN_ERROR_BUS_FAULT_WARNING;
    }

    if ((error_flags & HAL_FDCAN_FLAG_BUS_OFF) != 0U)
    {
      /* HAL_FDCAN_FLAG_BUS_OFF                 FDCAN_IR_BO   */
      error_code |= HAL_FDCAN_ERROR_BUS_FAULT_OFF;
    }

    if ((error_flags & HAL_FDCAN_FLAG_ERROR_LOGGING_OVERFLOW) != 0U)
    {
      /* HAL_FDCAN_FLAG_ERROR_LOGGING_OVERFLOW  FDCAN_IR_ELO  */
      error_code |= HAL_FDCAN_ERROR_LOG_OVERFLOW;
    }

    if ((error_flags & HAL_FDCAN_FLAG_RAM_WATCHDOG) != 0U)
    {
      /* HAL_FDCAN_FLAG_RAM_WATCHDOG            FDCAN_IR_WDI  */
      error_code |= HAL_FDCAN_ERROR_RAM_WDG;
    }

    if ((error_flags & HAL_FDCAN_FLAG_ARB_PROTOCOL_ERROR) != 0U)
    {
      /* HAL_FDCAN_FLAG_ARB_PROTOCOL_ERROR      FDCAN_IR_PEA  */
      error_code |= HAL_FDCAN_ERROR_PROTOCOL_ARBT;
    }

    if ((error_flags & HAL_FDCAN_FLAG_DATA_PROTOCOL_ERROR) != 0U)
    {
      /* HAL_FDCAN_FLAG_DATA_PROTOCOL_ERROR     FDCAN_IR_PED  */
      error_code |= HAL_FDCAN_ERROR_PROTOCOL_DATA;
    }

    if ((error_flags & HAL_FDCAN_FLAG_RESERVED_ADDRESS_ACCESS) != 0U)
    {
      /* HAL_FDCAN_FLAG_RESERVED_ADDRESS_ACCESS   FDCAN_IR_ARA  */
      error_code |=  HAL_FDCAN_ERROR_RESERVED_AREA;
    }

    if ((error_flags & HAL_FDCAN_FLAG_TIMEOUT_OCCURRED) != 0U)
    {
      /* HAL_FDCAN_FLAG_TIMEOUT_OCCURRED        FDCAN_IR_TOO  */
      error_code |= HAL_FDCAN_ERROR_TIMEOUT_OCCURED;
    }

    if ((error_flags & HAL_FDCAN_FLAG_RAM_ACCESS_FAILURE) != 0U)
    {
      /* HAL_FDCAN_FLAG_RAM_ACCESS_FAILURE      FDCAN_IR_MRAF */
      error_code |=  HAL_FDCAN_ERROR_RAM_ACCESS_FAILURE;
    }

    /* When all error sources have been processed, clear the Error flags */
    FDCAN_CLEAR_FLAG(hfdcan, error_flags);

    /* Update the last_error_codes according to the detected error flags */
    hfdcan->last_error_codes |= error_code;

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hfdcan->p_error_cb(hfdcan);
#else
    /* Error Callback */
    HAL_FDCAN_ErrorCallback(hfdcan);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

}

/**
  * @brief  Assign the interrupt group(s) to an interrupt Line.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  interrupt_groups interrupt group(s) to connect to the given interrupt line.
  *         This parameter can be any combination of @ref FDCAN_Interrupt_Groups.
  * @param  it_line indicates which interrupt line must be assigned to the interrupt groups.
  *         This parameter must be one unique item of @ref FDCAN_Interrupt_Lines.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_SetInterruptGroupsToLine(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt_groups,
                                                uint32_t it_line)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_IT_GROUP(interrupt_groups));
  ASSERT_DBG_PARAM(IS_FDCAN_IT_LINE(it_line));
  /* Check if the prequested parameter concerns only a single interrupt line */
  ASSERT_DBG_PARAM(IS_SINGLE_BIT_SET(it_line));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (it_line == HAL_FDCAN_IT_LINE_0)
  {
    CLEAR_BIT(p_fdcanx->ILS, (interrupt_groups & HAL_FDCAN_ILS_MASK));
  }
  else
  {
    SET_BIT(p_fdcanx->ILS, (interrupt_groups & HAL_FDCAN_ILS_MASK));
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the interrupt line assigned to an interrupt group - applies to a single interrupt group.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  interrupt_group Interrupt group.
  *         This parameter must be one unique item of @ref FDCAN_Interrupt_Groups.
  * @retval HAL_FDCAN_IT_LINE_0 Interrupt group is assigned to line 0.
  * @retval HAL_FDCAN_IT_LINE_1 Interrupt group is assigned to line 1.
  */
uint32_t HAL_FDCAN_GetLineFromInterruptGroup(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt_group)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_IT_GROUP(interrupt_group));
  /* Ensure only one interrupt group was passed as parameter */
  ASSERT_DBG_PARAM(IS_SINGLE_BIT_SET(interrupt_group));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Read the value of the single interrupt group from the ILS register */
  return ((READ_REG(p_fdcanx->ILS) & HAL_FDCAN_ILS_MASK & interrupt_group) == 0U) ? HAL_FDCAN_IT_LINE_0
         : HAL_FDCAN_IT_LINE_1;
}

/**
  * @brief  Enable the interrupt line.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  it_lines Interrupt line(s) to enable. Can be OR-ed.
  *         This parameter can be a combination of @ref FDCAN_Interrupt_Lines.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableInterruptLines(const hal_fdcan_handle_t *hfdcan, uint32_t it_lines)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check if  the passed interrupt line(s) is valid */
  ASSERT_DBG_PARAM(IS_FDCAN_IT_LINE(it_lines));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable the selected interrupts Line - FDCAN interrupt line enable register (FDCAN_ILE) */
  SET_BIT(p_fdcanx->ILE, it_lines);

  return HAL_OK;
}

/**
  * @brief  Disable the interrupt lines.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  it_lines interrupt line(s) to disable.
  *         This parameter can be any combination of @ref FDCAN_Interrupt_Lines.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableInterruptLines(const hal_fdcan_handle_t *hfdcan, uint32_t it_lines)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check if  the passed interrupt line(s) is valid */
  ASSERT_DBG_PARAM(IS_FDCAN_IT_LINE(it_lines));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable the selected interrupts Line - FDCAN interrupt line enable register (FDCAN_ILE) */
  CLEAR_BIT(p_fdcanx->ILE, it_lines);

  return HAL_OK;
}

/**
  * @brief  Check the interrupt line status.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  it_line Interrupt line to be checked.
  *         This parameter must be unique sample of @ref FDCAN_Interrupt_Lines.
  * @retval HAL_FDCAN_IT_LINE_DISABLED interrupt line is disabled.
  * @retval HAL_FDCAN_IT_LINE_ENABLED interrupt line is enabled.
  */
hal_fdcan_it_lines_status_t HAL_FDCAN_IsEnabledInterruptLine(const hal_fdcan_handle_t *hfdcan, uint32_t it_line)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Check if  the passed interrupt line(s) is valid */
  ASSERT_DBG_PARAM(IS_FDCAN_IT_LINE(it_line));
  /* Check if  the prequested parameter concerns only a single interrupt line */
  ASSERT_DBG_PARAM(IS_SINGLE_BIT_SET(it_line));

  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (it_line == HAL_FDCAN_IT_LINE_0)
  {
    return (hal_fdcan_it_lines_status_t)(uint32_t)(READ_REG(p_fdcanx->ILE) & FDCAN_IT_LINE0_MASK);
  }
  else
  {
    return (hal_fdcan_it_lines_status_t)(uint32_t)((READ_REG(p_fdcanx->ILE) & FDCAN_IT_LINE1_MASK) >> 1U);
  }
}

/**
  * @brief  Enable the interrupts.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  interrupts  Interrupt signal(s) to enable, can be OR-ed with different interrupt signals.
  *         This parameter can be any combination of @ref FDCAN_Interrupt_Sources.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t interrupts)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_FDCAN_IT(interrupts));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Set the required interrupts bits to 1 in FDCAN interrupt enable register (FDCAN_IE) */
  SET_BIT(p_fdcanx->IE, (interrupts & HAL_FDCAN_IR_MASK));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Disable the interrupts.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  interrupts Interrupt signal(s) to disable - Can be OR-ed with other interrupt signals.
  *         This parameter can be any combination of @arg FDCAN_Interrupt_Sources.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t interrupts)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  ASSERT_DBG_PARAM(IS_FDCAN_IT(interrupts));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Clear the required interrupts bits to 0 in FDCAN interrupt enable register (FDCAN_IE) */
  CLEAR_BIT(p_fdcanx->IE, (interrupts & HAL_FDCAN_IR_MASK));

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Check the Interrupt status. Apply to one single interrupt signal.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  interrupt Interrupt signal to check. Only one single interrupt signal can be checked at a time.
  *         This parameter must be one unique sample of @arg FDCAN_Interrupt_Sources.
  * @retval HAL_FDCAN_IT_DISABLED Interrupt is disabled.
  * @retval HAL_FDCAN_IT_ENABLED  Interrupt is enabled.
  */
hal_fdcan_it_status_t HAL_FDCAN_IsEnabledInterrupt(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check that the IT is valid */
  ASSERT_DBG_PARAM(IS_FDCAN_IT(interrupt));
  /* Check if only one it source was passed as parameter */
  ASSERT_DBG_PARAM(IS_SINGLE_BIT_SET(interrupt));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Check if the interrupt is enabled */
  return (READ_BIT(p_fdcanx->IE, interrupt & HAL_FDCAN_IR_MASK) == 0U) ?
         HAL_FDCAN_IT_DISABLED : HAL_FDCAN_IT_ENABLED;
}

/**
  * @brief  Enable the Transmission buffer complete interrupt.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_idx Buffers to select to enable the Transmission Complete interrupt - can be OR-ed.
  *         This parameter can be any combination of @ref FDCAN_IT_Tx_Complete_Buffers_select
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableTxBufferCompleteInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the buffer selection */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_BUFFER_COMPLETE_ENABLE(buffer_idx));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable the selected interrupts - FDCAN  Tx buffer transmission interrupt enable (FDCAN_TXBTIE) */
  MODIFY_REG(p_fdcanx->TXBTIE, ~FDCAN_TX_CPL_BUFFER_ALL_MASK, (buffer_idx & FDCAN_TX_CPL_BUFFER_ALL_MASK));

  return HAL_OK;

}

/**
  * @brief  Disable the Transmission buffer complete interrupt.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_idx Buffers to select to disable the Transmission Complete interrupt - can be OR-ed.
  *         This parameter can be any combination of @ref FDCAN_IT_Tx_Complete_Buffers_select
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableTxBufferCompleteInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the buffer selection */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_BUFFER_COMPLETE_ENABLE(buffer_idx));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Disable the selected interrupts - FDCAN  Tx buffer transmission interrupt enable (FDCAN_TXBTIE) */
  MODIFY_REG(p_fdcanx->TXBTIE, FDCAN_TX_CPL_BUFFER_ALL_MASK, (~buffer_idx & FDCAN_TX_CPL_BUFFER_ALL_MASK));

  return HAL_OK;
}

/**
  * @brief  Check the status of the buffer connected to Transmission Complete interrupt.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_idx Buffer to check with Transmission Complete interrupt status. Apply to a single buffer.
  *         This parameter must be an unique sample of @ref FDCAN_IT_Tx_Complete_Buffers_select
  * @retval HAL_FDCAN_IT_TX_CPLT_BUFFER_DISABLED Buffer is disabled.
  * @retval HAL_FDCAN_IT_TX_CPLT_BUFFER_ENABLED  Buffer is enabled.
  */
hal_fdcan_it_txbuffer_complete_status_t HAL_FDCAN_IsEnabledTxBufferCompleteInterrupt(const hal_fdcan_handle_t *hfdcan,
    uint32_t buffer_idx)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the buffer selection */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_BUFFER_COMPLETE_ENABLE(buffer_idx));
  /* Validate that only one buffer has to be checked */
  ASSERT_DBG_PARAM(IS_FDCAN_VALID_TX_CPL_BUFFER_SEL(buffer_idx));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (IS_BIT_SET(p_fdcanx->TXBTIE, buffer_idx))
  {
    return HAL_FDCAN_IT_TXBUFFER_COMPLETE_ENABLED;
  }
  else
  {
    return HAL_FDCAN_IT_TXBUFFER_COMPLETE_DISABLED;
  }
}

/**
  * @brief  Enable the Transmission Cancellation Finished interrupt.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_idx the Buffers to select to enable the Transmission Cancellation Finished interrupt. Can be OR-ed.
  *         This parameter can be any combination of @ref FDCAN_IT_Tx_Abort_Buffers_select
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_EnableTxBufferCancellationInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));
  /* Check the buffer selection */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_BUFFER_ABORT_ENABLE(buffer_idx));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable the selected interrupts - FDCAN  Tx buffer cancellation interrupt enable (FDCAN_TXBCIE) */
  MODIFY_REG(p_fdcanx->TXBCIE, ~FDCAN_TX_ABORT_BUFFER_ALL_MASK, (buffer_idx & FDCAN_TX_ABORT_BUFFER_ALL_MASK));

  return HAL_OK;
}

/**
  * @brief  Disable the Transmission Cancellation Finished interrupt.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_idx Buffers to select to disable the Transmission Cancellation Finished interrupt. Can be OR-ed.
  *         This parameter can be any combination of @ref FDCAN_IT_Tx_Abort_Buffers_select
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_FDCAN_DisableTxBufferCancellationInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx)
{
  FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);
  /* Check the buffer selection */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_BUFFER_ABORT_ENABLE(buffer_idx));

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  /* Enable the selected interrupts - FDCAN  Tx buffer cancellation interrupt enable (FDCAN_TXBCIE) */
  MODIFY_REG(p_fdcanx->TXBCIE, FDCAN_TX_ABORT_BUFFER_ALL_MASK, (~buffer_idx & FDCAN_TX_ABORT_BUFFER_ALL_MASK));

  return HAL_OK;
}

/**
  * @brief  Check the status of the buffer connected to Transmission Cancellation Finished interrupt.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_idx Buffer to check with Transmission Cancellation Finished status. Apply to a single buffer.
  *         This parameter must be an unique sample of @ref FDCAN_IT_Tx_Abort_Buffers_select
  * @retval HAL_FDCAN_IT_TX_ABORT_BUFFER_DISABLED Buffer is disabled.
  * @retval HAL_FDCAN_IT_TX_ABORT_BUFFER_ENABLED  Buffer is enabled.
  */
hal_fdcan_it_txbuffer_abort_status_t HAL_FDCAN_IsEnabledTxBufferCancellationInterrupt(const hal_fdcan_handle_t *hfdcan,
    uint32_t buffer_idx)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Check function parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the global state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_IDLE | (uint32_t)HAL_FDCAN_STATE_ACTIVE
                   | (uint32_t)HAL_FDCAN_STATE_POWER_DOWN);

  /* Check the buffer selection */
  ASSERT_DBG_PARAM(IS_FDCAN_TX_BUFFER_ABORT_ENABLE(buffer_idx));
  /* Validate that only one buffer has to be checked */
  ASSERT_DBG_PARAM(IS_FDCAN_VALID_TX_ABORT_BUFFER_SEL(buffer_idx));

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  if (IS_BIT_SET(p_fdcanx->TXBCIE, buffer_idx))
  {
    return HAL_FDCAN_IT_TXBUFFER_ABORT_ENABLED;
  }
  else
  {
    return HAL_FDCAN_IT_TXBUFFER_ABORT_DISABLED;
  }
}

/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group6
  * @{
A set of Weak functions if USE_HAL_FDCAN_REGISTER_CALLBACKS is set to 0 (or custom Callbacks functions if
USE_HAL_FDCAN_REGISTER_CALLBACKS is set to 1) which are used to asynchronously informed the application in non-blocking
modes:
    - HAL_FDCAN_TxEventFifoCallback(): Transmission event FIFO callback
    - HAL_FDCAN_RxFifo0Callback(): Reception FIFO 0 callback
    - HAL_FDCAN_RxFifo1Callback(): Reception FIFO 1 callback
    - HAL_FDCAN_TxFifoEmptyCallback(): Transmission FIFO Empty callback
    - HAL_FDCAN_TxBufferCompleteCallback(): Transmission completed callback
    - HAL_FDCAN_TxBufferAbortCallback(): Abort Transmission callback
    - HAL_FDCAN_HighPriorityMessageCallback(): High Priority Message receiving callback
    - HAL_FDCAN_TimestampWraparoundCallback(): Timestamp WrapAround callback
    - HAL_FDCAN_ErrorCallback(): Global Error callback
  */

/**
  * @brief  Tx Event callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  tx_event_fifo_interrupts indicates which Tx Event FIFO interrupts are raised.
  *         This parameter can be any combination of @arg FDCAN_Tx_Event_Fifo_Interrupts
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_TxEventFifoCallback(hal_fdcan_handle_t *hfdcan, uint32_t tx_event_fifo_interrupts)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);
  STM32_UNUSED(tx_event_fifo_interrupts);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_TxEventFifoCallback must be implemented in the user file.
   */
}

/**
  * @brief  Rx FIFO 0 callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  rx_fifo0_interrupts indicates which Rx FIFO 0 interrupts are raised.
  *         This parameter can be any combination of @arg FDCAN_Rx_Fifo0_Interrupts.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_RxFifo0Callback(hal_fdcan_handle_t *hfdcan, uint32_t rx_fifo0_interrupts)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);
  STM32_UNUSED(rx_fifo0_interrupts);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_RxFifo0Callback must be implemented in the user file.
   */
}

/**
  * @brief  Rx FIFO 1 callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  rx_fifo1_interrupts indicates which Rx FIFO 1 interrupts are raised.
  *         This parameter can be any combination of @arg FDCAN_Rx_Fifo1_Interrupts.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_RxFifo1Callback(hal_fdcan_handle_t *hfdcan, uint32_t rx_fifo1_interrupts)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);
  STM32_UNUSED(rx_fifo1_interrupts);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_RxFifo1Callback must be implemented in the user file.
   */
}

/**
  * @brief  Tx FIFO Empty callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_TxFifoEmptyCallback(hal_fdcan_handle_t *hfdcan)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_TxFifoEmptyCallback must be implemented in the user file.
   */
}

/**
  * @brief  Transmission Complete callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_indexes Indexes of the transmitted buffers.
  *         This parameter can be any combination of @arg FDCAN_IT_Tx_Complete_Buffers_select.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_TxBufferCompleteCallback(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);
  STM32_UNUSED(buffer_indexes);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_TxBufferCompleteCallback must be implemented in the user file.
   */
}

/**
  * @brief  Transmission Cancellation callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  buffer_indexes Indexes of the aborted buffers.
  *         This parameter can be any combination of @arg FDCAN_IT_Tx_Abort_Buffers_select.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_TxBufferAbortCallback(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);
  STM32_UNUSED(buffer_indexes);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_TxBufferAbortCallback must be implemented in the user file.
   */
}

/**
  * @brief  High Priority Message callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_HighPriorityMessageCallback(hal_fdcan_handle_t *hfdcan)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_HighPriorityMessageCallback must be implemented in the user file.
   */
}

/**
  * @brief  Timestamp Wraparound callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_TimestampWraparoundCallback(hal_fdcan_handle_t *hfdcan)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_TimestampWraparoundCallback must be implemented in the user file.
   */
}

/**
  * @brief  Error callback.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @warning The hfdcan handle's last_error_codes parameter is updated by the FDCAN processes,
  *          and the user can use HAL_FDCAN_GetLastErrorCodes() to verify the most recent error that occurred.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_FDCAN_ErrorCallback(hal_fdcan_handle_t *hfdcan)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hfdcan);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_FDCAN_ErrorCallback must be implemented in the user file.
   */
}


/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group7
  * @{
A set of functions allowing to process with the state and last process errors.
  - HAL_FDCAN_GetState()            : Retrieve the FDCAN state.
  - HAL_FDCAN_GetLastErrorCodes()   : Retrieve the last error codes limited to the last process.
  */

/**
  * @brief  Return the FDCAN state.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @return Current FDCAN state of type @ref hal_fdcan_state_t.
  */
hal_fdcan_state_t HAL_FDCAN_GetState(const hal_fdcan_handle_t *hfdcan)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Return FDCAN handle state */
  return hfdcan->global_state;
}

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
/**
  * @brief  Return the FDCAN error code.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @retval uint32_t Last error code, this code must be a value of @ref FDCAN_Error_Codes FDCAN.
 */
uint32_t HAL_FDCAN_GetLastErrorCodes(const hal_fdcan_handle_t *hfdcan)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Return FDCAN error code */
  return hfdcan->last_error_codes;
}
#endif  /* USE_HAL_FDCAN_GET_LAST_ERRORS */

/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @addtogroup FDCAN_Exported_Functions_Group8
  * @{
A set of functions allowing to Acquire/Release the bus based on the HAL OS abstraction layer (stm32_hal_os.c/.h osal):
    - HAL_FDCAN_AcquireBus(): Acquire the FDCAN bus.
    - HAL_FDCAN_ReleaseBus(): Release the FDCAN bus.
  */

/**
  * @brief  Acquire the FDCAN bus through the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  timeout_ms Timeout duration in millisecond.
  * @note   HAL_FDCAN_AcquireBus() must be called from thread mode only (not from handler mode i.e from ISR).
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_AcquireBus(hal_fdcan_handle_t *hfdcan, uint32_t timeout_ms)
{
  hal_status_t status = HAL_ERROR;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  if (HAL_OS_SemaphoreTake(&hfdcan->semaphore, timeout_ms) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Release the FDCAN bus through the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @note   HAL_FDCAN_ReleaseBus() can be called from thread mode or from handler mode i.e from ISR.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Operation completed with errors.
  */
hal_status_t HAL_FDCAN_ReleaseBus(hal_fdcan_handle_t *hfdcan)
{
  hal_status_t status = HAL_ERROR;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hfdcan->global_state, (uint32_t)HAL_FDCAN_STATE_INIT | (uint32_t)HAL_FDCAN_STATE_IDLE
                   | (uint32_t)HAL_FDCAN_STATE_ACTIVE);

  if (HAL_OS_SemaphoreRelease(&hfdcan->semaphore) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1)
/** @addtogroup FDCAN_Exported_Functions_Group9
  * @{
A set of functions allowing to manage a user data Pointer stored to the FDCAN handle:
  - HAL_FDCAN_SetUserData() : Configure the user data into the handle
  - HAL_FDCAN_GetUserData() : Retrieve the user data from the handle
  */

/**
  * @brief Set the user data pointer into the handle.
  * @param hfdcan Pointer to a hal_fdcan_handle_t.
  * @param p_user_data Pointer to the user data.
  */
void HAL_FDCAN_SetUserData(hal_fdcan_handle_t *hfdcan, const void *p_user_data)
{
  /* Check the FDCAN handle allocation */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  hfdcan->p_user_data = p_user_data;
}
/**
  * @brief Retrieve the user data pointer from the handle.
  * @param hfdcan Pointer to a hal_fdcan_handle_t.
  * @retval Pointer to the user data.
  */
const void *HAL_FDCAN_GetUserData(const hal_fdcan_handle_t *hfdcan)
{
  /* Check the FDCAN handle allocation */
  ASSERT_DBG_PARAM((hfdcan != NULL));

  return (hfdcan->p_user_data);
}

/**
  * @}
  */
#endif /* USE_HAL_FDCAN_USER_DATA == 1 */

/**
  * @}
  */

/** @addtogroup FDCAN_Private_Functions
  * @{
  */

/**
  * @brief  Calculate each RAM block start address and size.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_config Pointer to a hal_fdcan_config_t.
 */
static void FDCAN_calculateRamBlockAddresses(hal_fdcan_handle_t *hfdcan, const hal_fdcan_config_t *p_config)
{
  FDCAN_GlobalTypeDef *p_fdcanx;
  uint32_t ram_counter;
  uint32_t sram_can_instance_base = SRAMCAN_BASE;

  /* Get the FDCAN hardware instance */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);


  /* Standard filter list start address */
  hfdcan->msg_ram.std_filter_start_addr = sram_can_instance_base + SRAMCAN_FLSSA;
  /* Standard filter elements number */
  MODIFY_REG(p_fdcanx->RXGFC, FDCAN_RXGFC_LSS, (p_config->std_filters_nbr << FDCAN_RXGFC_LSS_Pos));

  /* Extended filter list start address */
  hfdcan->msg_ram.ext_filter_start_addr = sram_can_instance_base + SRAMCAN_FLESA;
  /* Extended filter elements number */
  MODIFY_REG(p_fdcanx->RXGFC, FDCAN_RXGFC_LSE, (p_config->ext_filters_nbr << FDCAN_RXGFC_LSE_Pos));

  /* Rx FIFO 0 start address */
  hfdcan->msg_ram.rx_fifo0_start_addr = sram_can_instance_base + SRAMCAN_RF0SA;

  /* Rx FIFO 1 start address */
  hfdcan->msg_ram.rx_fifo1_start_addr = sram_can_instance_base + SRAMCAN_RF1SA;

  /* Tx event FIFO start address */
  hfdcan->msg_ram.tx_event_start_addr = sram_can_instance_base + SRAMCAN_TEFSA;

  /* Tx FIFO/queue start address */
  hfdcan->msg_ram.tx_fifo_start_addr = sram_can_instance_base + SRAMCAN_TFQSA;

  /* Flush the allocated Message RAM area */
  for (ram_counter = sram_can_instance_base; ram_counter < (sram_can_instance_base + SRAMCAN_SIZE); ram_counter += 4U)
  {
    *(uint32_t *)(ram_counter) = 0x00000000U;
  }
}

/**
  * @brief  Copy Tx message to the message RAM.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t handle.
  * @param  p_tx_element_header Pointer to a hal_fdcan_tx_header_t structure.
  * @param  p_tx_data Pointer to a buffer containing the payload of the Tx frame.
  * @param  buffer_index index of the buffer to be configured.
 */
static void FDCAN_copyMessageToRAM(const hal_fdcan_handle_t *hfdcan,
                                   const hal_fdcan_tx_header_t *p_tx_element_header,
                                   const uint8_t *p_tx_data, uint32_t buffer_index)
{
  uint32_t tx_element_w1;
  uint32_t tx_element_w2;
  uint32_t *tx_address;
  uint32_t byte_count;

  /* Build second word of Tx header element */
  tx_element_w1 = (uint32_t)(p_tx_element_header->d64 >> 32U);
  /* Build second word of Tx header element */
  tx_element_w2 = (uint32_t)(p_tx_element_header->d64 & 0x00000000FFFFFFFFU);
  /* Calculate Tx element address */
  tx_address = (uint32_t *)(hfdcan->msg_ram.tx_fifo_start_addr + (buffer_index * SRAMCAN_TFQ_SIZE));

  /* Write the first word of Tx element header to the message RAM */
  *tx_address = tx_element_w2;
  tx_address++;
  /* Write the second word of Tx element header to the message RAM */
  *tx_address = tx_element_w1;
  tx_address++;

  /* Write Tx payload to the message RAM */
  for (byte_count = 0; byte_count < DLCtoBytes[p_tx_element_header->b.data_length]; byte_count += 4U)
  {
    *tx_address = (((uint32_t)p_tx_data[byte_count + 3U] << 24U) |
                   ((uint32_t)p_tx_data[byte_count + 2U] << 16U) |
                   ((uint32_t)p_tx_data[byte_count + 1U] << 8U)  |
                   (uint32_t)p_tx_data[byte_count]);
    tx_address++;
  }
}

/**
  * @}
  */

#endif /* HAL_FDCAN_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

#endif /* FDCAN1 */
