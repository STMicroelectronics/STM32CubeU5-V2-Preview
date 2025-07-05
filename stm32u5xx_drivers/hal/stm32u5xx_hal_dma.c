/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dma.c
  * @brief   This file provides DMA (Direct Memory Access) peripheral services.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
This file provides firmware functions to manage the following functionalities of DMA peripheral:

- Initialization and De-initialization functions
- Configuration functions
- Linked-list node management functions
- Process management functions
- Callbacks functions
- Status functions

The direct memory access (DMA) controller is a bus master and system peripheral. The DMA is used to perform programmable
data transfers between memory-mapped peripherals and/or memories via linked-lists, upon the control of an off-loaded CPU

# DMA main features

- DMA transfer modes are divided to 2 major categories (direct transfer and linked-list transfer)

- The DMA channel can be programmed to allow one-shot transfer by direct mode transfer APIs

- Alternatively to the direct programming mode, a DMA channel can be programmed by a list of transfers, known as
  linked-list (list of Node items).
  - Each node is defined by its data structure
  - Each node specifies a standalone DMA channel transfer
  When enabled, the DMA channel fetch the first linked-list node from SRAM (known as head node). When executed, the
  next linked list node must be fetched and executed. This operation is repeated until the end of the whole
  linked-list queue
  Optionally, the linked-list can be linear where the last linked-list queue node is not linked to another queue node
  or circular where the last linked-list node is linked to any linked-list queue node.

  - Linear linked-list:
    linear linked-list is a finite list where the last node (also called tail node) points to null, a linear linked-list
    transfer execution is finite, ending by the last node.
    The DMA channel fetches and executes all DMA linked-list queue from first node (head node) to last node (tail node)
    ones. When the last node is completed, the DMA channel remains in idle state and another transfer can be lunched.

  - Circular linked-list:
    Circular linked-list where the last node points to one of the previous nodes of the list. a circular linked-list
    transfer execution must end-up looping from the last node (tail node) to the node where the tail node points to.
    The DMA channel fetches and executes all DMA linked-list queue from first node (head node) to last node (tail node).
    When circular node is executed, the DMA channel fetches the next node repeat the same sequence in an infinite loop
    (Circular transfer). To stop the DMA channel, an abort operation is required.

  - Use the stm32tnxx_hal_q module to create a DMA queue based on DMA transfer nodes

- In order to reduce linked-list queue executing time and power consumption, the DMA channel supports executing the
  dynamic linked-list format. In fact, the DMA supports the execution of 2 types of linked-list formats : static and
  dynamic.

  - Static linked-list:
    The static linked-list format refers to the full linked-list node where all DMA channel parameters are fetched and
    executed independently of the redundancy of information.

  - Dynamic linked-list:
    The dynamic linked-list format refer to the customized linked-list node where only DMA channel necessary parameters
    are fetched and executed (Example: data size = 20 on previous node, and data size = 20 on the current node => No
    need to update it).

- For linked-list transfers, the DMA channel can executes the linked-list queue node by node when started, enabling the
  DMA channel first time allows to fetch the head node from memory then it stops. Then, another DMA channel enable is
  needed to execute the node. After that, keeping enabling the DMA channel is needed to execute each node until the end
  of linked-list queue. When the linked-list queue is circular, enabling the DMA channel in an infinite loop is required
  to keep the DMA channel running. This feature is useful for debug purpose or asynchronously executing queue nodes.

- Each DMA channel transfer (direct or linked-list), is highly configurable according to DMA channel instance
  integrated in devices. These configuration can be :

  - Repeated block configuration :
    If the feature is supported, the DMA channel can perform a repeated block transfers. Named also 2 dimension
    addressing transfers, this feature can transfer n iterations of programmed block transfer. Additional to the repeat
    count of a block, DMA channel addresses can jump after at burst and block level. The jump length is a programmable
    parameter defined by DMA user.
    - Jump at burst level : The DMA channel keeps an empty area, between each 2 consecutive bursts transmitted.
    - Jump at block level : The DMA channel keeps an empty area, between each 2 consecutive blocks transmitted.

  - Trigger configuration :
    The DMA channel transfers can be conditioned by hardware signals edges (rising or falling) named hardware triggers.
    Trigger condition can be applied at :
    - Single/Burst level   : Each single/burst data transmission is conditioned by a signal trigger hit.
    - Block level          : Each block data transmission is conditioned by a signal trigger hit.
    - Repeated block level : Each repeated block data transmission is conditioned by a signal trigger hit.
    - Node level           : Each node execution is conditioned by a signal trigger hit.
    The DMA channel can report a trigger overrun when detects more than 2 trigger signal edges before executing the
    current transfer.

  - Data handling configuration :
    The data handling feature can be :
    - Padding pattern : Padding selected pattern (zero padding or sign extension) when the source data width is smaller
                        than the destination data width at single level.
    - Truncation      : Truncate section from the source data single when the source data width is bigger than the
                        destination data width.
    - Pack/Unpack     : Pack a set of data when source data width is smaller than the destination data width.
                        Unpack a set of data when source data width is bigger than the destination data width.
    - Exchange        : Exchange data at byte or half-word level in destination and at byte level in source.

- Each DMA channel transfer (direct or linked-list) when it is active, can be suspended and resumed at run time
  application. When trying to suspend an ongoing transfer, the DMA channel is not suspended instantly but complete
  the current ongoing single/burst then it stops.
  When the DMA channel is suspended, the current transfer can be resumed instantly.

- The DMA channel that supports FIFO, can report in real time the number of beats remains on destination (Output)
  FIFO level.

# How to use the DMA HAL module driver

## Initialization and De-initialization :

- For a given channel, use HAL_DMA_Init() function to initialize the DMA channel handle and associate physical channel
  instance as direct mode by Default.

- Use HAL_DMA_DeInit() function to de-initialize a DMA channel, When called, the DMA channel must be in reset. It is
  mandatory to reinitialize it for next transfer.

## Configuration transfer :

### Set the DMA channel direct transfer configuration

- HAL_DMA_SetConfigDirectXfer() function for the direct transfer mode through the following parameters:

- As optional, set the DMA channel direct transfer feature configuration :

  - Use HAL_DMA_SetConfigDirectXferHardwareRequestMode() function to set the transfer hardware request mode
    configuration
  - Use HAL_DMA_SetConfigDirectXferPort() function to set the transfer ports configuration
  - Use HAL_DMA_SetConfigDirectXferBurst() function to set the transfer burst configuration
  - Use HAL_DMA_SetConfigDirectXferTrigger() function to set the transfer trigger configuration
  - Use HAL_DMA_SetConfigDirectXferDataHandling() function to set the transfer data handling configuration
  - Use HAL_DMA_SetConfigDirectXferRepeatBlock() function to set the transfer repeated block configuration
  - Use HAL_DMA_SetConfigAccessAttributes() function to set the transfer security access attributes configuration

  - Use the reset functions to reset the configuration of each feature (ex : HAL_DMA_ResetConfigDirectXferTrigger)

  - Use the get functions to get the configuration of any features (ex : HAL_DMA_GetConfigDirectXfer)

  - Use HAL_DMA_SetConfigPeriphDirectXfer() function to set the direct peripheral transfer configuration

### Set the DMA channel linked-list transfer configuration

- HAL_DMA_SetConfigLinkedListXfer() function for the linked-list transfer mode

- As optional, set the DMA channel linked-list transfer feature configuration :

  - Use HAL_DMA_SetLinkedListXferEventMode() function to set the transfer event mode configuration
  - Use HAL_DMA_SetLinkedListXferFetchNodePort() function to set the transfer fetch node port configuration
  - Use HAL_DMA_SetLinkedListXferPriority() function to set the transfer priority configuration
  - Use HAL_DMA_SetLinkedListXferExecutionMode() function to set the transfer execution mode configuration

  - Use the reset functions to reset the configuration of each feature ( ex : HAL_DMA_ResetLinkedListXferEventMode)

  - Use the get functions to get the configuration of any features (ex : HAL_DMA_GetConfigLinkedListXfer)

  - Use HAL_DMA_SetConfigPeriphLinkedListCircularXfer() function to set linked-list circular peripheral transfer
    configuration

## Linked-list node management :

- The linked-list node management is a software processing independently of DMA channel hardware. It allows to fill,
  convert (to dynamic or to static) both nodes and use the Q module services to :
  - Initialize the queue
  - Insert node to queue
  - Remove node from queue
  - Replace node from queue
  - Circularize queue in order to perform infinite transfers.
  Linked-list APIs and types are adapted to reduce memory footprint.

- At node level, the operations that can be done are filling a new linked-list node or get a linked-list node
  information from a filled node. The linked-list nodes have two forms according to 2 dimensions addressing capability.
  The linear addressing nodes contains the information of all DMA channel features except the 2 dimension addressing
  features and the 2 dimensions addressing nodes contain the information of all available features.

  - Use HAL_DMA_FillNodeConfig() function to fill the DMA linked-list node according to the specified parameters.
    Fill operation allow to convert the specified parameter in values known by the DMA channel and place them in memory.
    Placing DMA linked-list in SRAM must be done in accordance to product specification to ensure that the link access
    port can access to the specified SRAM.
    The DMA linked-list node parameter address must be 32bit aligned and must not exceed the 64 KByte addressable
    space.

  - Use HAL_DMA_GetNodeConfig() function to get the specified configuration parameter on filling node.
    This API can be used when need to change few parameter to fill new node.

  - As optional, fill the DMA channel linked-list node feature configuration :

    - Use HAL_DMA_FillNodeHardwareRequestMode() function to fill the DMA linked-list node request mode configuration
    - Use HAL_DMA_FillNodePort() function to fill the DMA linked-list node ports configuration
    - Use HAL_DMA_FillNodeBurst() function to fill the DMA linked-list node burst configuration
    - Use HAL_DMA_FillNodeXferEventMode() function to fill the DMA linked-list node transfer event mode configuration
    - Use HAL_DMA_FillNodeTrigger() function to fill the DMA linked-list node trigger configuration
    - Use HAL_DMA_FillNodeDataHandling() function to fill the DMA linked-list node data handling configuration
    - Use HAL_DMA_FillNodeRepeatBlock() function to fill the DMA linked-list node repeated block configuration
    - Use HAL_DMA_FillNodeAccessAttributes() function to fill the DMA linked-list node access attributes configuration
    - Use HAL_DMA_FillNodeData() function to fill the DMA linked-list node data configuration
    - Use HAL_DMA_FillNodeDirectXfer() function to fill the DMA linked-list node direct transfer configuration

  - To have the best DMA channel linked-list queue execution, it is recommended to convert the still built linked-list
    queue to dynamic format (Static is the default format). When linked-list queue becomes dynamic, all queue nodes are
    optimized and only changed parameters must be updated between nodes. So, the DMA must fetch only changes parameters
    instead of the whole node.

     - Use HAL_DMA_ConvertQNodesToDynamic() function to convert a linked-list queue to dynamic format.
      - This API must be called for static queues format.
      - This API must be called as the last API before starting the DMA channel in linked-list mode.

     - Use HAL_DMA_ConvertQNodesToStatic() function to convert a linked-list queue to static format.
       - This API must be called for dynamic queues format.
       - If the execution is dynamic and an update is needed on the linked list queue then :
        - If the execution is linear   : This API must be called as the first API after the full execution of
          linked-list queue.
        - If the execution is circular : This API must be called as the first API after the aborting the execution of
          the current linked-list queue.

  - When converting a circular queue to dynamic format and when the first circular node is the last queue node, it is
    recommended to duplicate the last circular node in order to ensure the full optimization when calling
    HAL_DMA_ConvertQNodesToDynamic() API. In this case, updated information are only addresses which allow to reduce
    4 words of update for linear nodes per node execution and 6 words update for 2 dimensions addressing nodes per
    node execution.

## Process and callback management :

### Silent mode IO operation :

- Use HAL_DMA_StartDirectXfer() function to start a DMA transfer in direct mode after the configuration of source
  address, destination address and the size of data to be transferred.

- Use HAL_DMA_StartLinkedListXfer() function to start a DMA transfer in linked-list mode after the configuration of
  linked-list queue.

- Use HAL_DMA_PollForXfer() function to poll for selected transfer level. In this case a fixed Timeout can be configured
  by User depending on his application.
  Transfer level can be :
  - HAL_DMA_XFER_HALF_COMPLETE
  - HAL_DMA_XFER_FULL_COMPLETE
  For circular transfer, this API returns an HAL_INVALID_PARAM.

- Use HAL_DMA_Suspend() function to suspend any ongoing DMA transfer in Blocking mode.
  This API returns HAL_ERROR when there is no ongoing transfer or timeout is reached when disabling the DMA channel.
  This API must not be called from an interrupt service routine

- Use HAL_DMA_Resume() function to resume instantantly any suspended DMA transfer.

- Use HAL_DMA_Abort() function to abort any ongoing DMA transfer in Blocking mode.
  This API returns HAL_ERROR when there is no ongoing transfer or timeout is reached when disabling the DMA channel.
  This API accepts the idle state when trying to abort a yet finished transfer. It returns an HAL_ERROR in this case.
  This API must not be called from an interrupt service routine

### Interrupt mode IO operation :

- Configure the DMA interrupt priority using HAL_CORTEX_NVIC_SetPriority() function

- Enable the DMA IRQ handler using HAL_CORTEX_NVIC_EnableIRQ() function

- Use HAL_DMA_RegisterXferHalfCpltCallback() function to register half transfer complete user callbacks.
- Use HAL_DMA_RegisterXferCpltCallback() function to register transfer complete user callbacks.
- Use HAL_DMA_RegisterXferAbortCallback() function to register transfer abort user callbacks.
- Use HAL_DMA_RegisterXferSuspendCallback() function to register transfer suspend user callbacks.
- Use HAL_DMA_RegisterXferErrorCallback() function to register transfer error user callbacks.

- Use HAL_DMA_StartDirectXfer_IT() function to start the DMA transfer in direct mode after the enable of DMA
  default optional interrupts and the configuration of source address,destination address and the size of data
  to be transferred.

- Use HAL_DMA_StartDirectXfer_IT_Opt() function to start the DMA transfer in direct mode after the enable of DMA
  customized optional interrupts and the configuration of source address,destination address and the size of data
  to be transferred.

- Use HAL_DMA_StartLinkedListXfer_IT() function to start a DMA transfer in linked-list mode after the enable of DMA
  default optional interrupts and configuration of linked-list queue.

- Use HAL_DMA_StartLinkedListXfer_IT_Opt() function to start a DMA transfer in linked-list mode after the enable of DMA
  customized optional interrupts and configuration of linked-list queue.

- Use HAL_DMA_IRQHandler() function called under DMA_IRQHandler interrupt subroutine to handle any DMA interrupt.

- Use HAL_DMA_Suspend_IT() function to suspend any on-going DMA transfer in interrupt mode.
  This API suspends the DMA channel execution. When the transfer is effectively suspended, an interrupt
  is generated and HAL_DMA_IRQHandler() must reset the channel and executes the transfer suspend user callbacks.
  This API must be called from an interrupt service routine.

- Use HAL_DMA_Resume() function to resume instantantly any suspended DMA transfer.

- Use HAL_DMA_Abort_IT() function to abort any on-going DMA transfer in interrupt mode.
  This API suspends the DMA channel execution.
  When the transfer is effectively suspended, an interrupt is generated and HAL_DMA_IRQHandler() must reset the channel
  and executes the transfer abort user callbacks.
  This API accepts the idle state when trying to abort a yet finished transfer. It returns an HAL_ERROR in this case.
  This is to consider asynchronous update of the DMA state to idle within the IRQHandler when the transfer is completed.
  This API must be called from an interrupt service routine.

## Status and errors

- Use HAL_DMA_SetUserData() function to set the DMA user data
- Use HAL_DMA_GetUserData() function to get the DMA user data
- Use HAL_DMA_GetFifoDataByte() function to Get the DMA remaining data in the FIFO in byte
- Use HAL_DMA_GetDirectXferRemainingDataByte() function to Get the DMA remaining data in the current transfer in byte
- Use HAL_DMA_GetState() function to Get the DMA current state
- Use HAL_DMA_GetLastErrorCodes() function to Get last errors codes

## Configuration inside the DMA driver

Config defines              | Description     | Default value   | Note                                                 |
----------------------------| --------------- | --------------- | -----------------------------------------------------|
PRODUCT                     | from IDE        |        NA       | The selected device (eg STM32U5XXxx)                |
USE_HAL_DMA_MODULE          | from hal_conf.h |        1        | Allows to use HAL DMA module.                        |
USE_ASSERT_DBG_PARAM        | from IDE        |      None       | Allows to use the assert check parameters.           |
USE_ASSERT_DBG_STATE        | from IDE        |      None       | Allows to use the assert check states.               |
USE_HAL_CHECK_PARAM         | from hal_conf.h |        0        | Allows to use the run-time checks parameters.        |
USE_HAL_CHECK_PROCESS_STATE | from hal_conf.h |        0        | Allows to use the load and store exclusive.          |
USE_HAL_DMA_CLK_ENABLE_MODEL| from hal_conf.h |HAL_CLK_ENABLE_NO| Allows to use the clock interface management for DMA.|
USE_HAL_DMA_GET_LAST_ERRORS | from hal_conf.h |        0        | Allows to use error code mechanism.                  |
USE_HAL_DMA_USER_DATA       | from hal_conf.h |        0        | Allows to use user data.                             |
USE_HAL_DMA_LINKEDLIST      | from hal_conf.h |        0        | Allows to use linked-list services.                  |
__ARM_FEATURE_CMSE          | from IDE        |        3        | Allows to use secure access for current context.     |
  */

#if defined (USE_HAL_DMA_MODULE) && (USE_HAL_DMA_MODULE == 1)

/* Private Macros-----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @{
  */

/*! Macro to check DMA resuest */
#if defined (JPEG)
#define IS_DMA_REQUEST(value)                                                          \
  (((value) == (uint32_t)HAL_DMA_REQUEST_SW) || ((value) <= HAL_GPDMA1_REQUEST_JPEG_TX))
#elif defined (ADC2)
#define IS_DMA_REQUEST(value)                                                       \
  (((value) == (uint32_t)HAL_DMA_REQUEST_SW) || ((value) <= HAL_GPDMA1_REQUEST_ADC2))
#else
#define IS_DMA_REQUEST(value)                                                            \
  (((value) == (uint32_t)HAL_DMA_REQUEST_SW) || ((value) <= HAL_GPDMA1_REQUEST_LPTIM3_UE))
#endif /* JPEG // ADC2 */

/*! Macro to check DMA hardware resuest mode */
#define IS_DMA_HARDWARE_REQUEST_MODE(value)               \
  (((value) == (uint32_t)HAL_DMA_HARDWARE_REQUEST_BURST ) \
   || ((value) == (uint32_t)HAL_DMA_HARDWARE_REQUEST_BLOCK))

/*! Macro to check DMA direction */
#define IS_DMA_DIRECTION(value)                                 \
  (((value) == (uint32_t)HAL_DMA_DIRECTION_MEMORY_TO_MEMORY)    \
   || ((value) == (uint32_t)HAL_DMA_DIRECTION_PERIPH_TO_MEMORY) \
   || ((value) == (uint32_t)HAL_DMA_DIRECTION_MEMORY_TO_PERIPH))

/*! Macro to check DMA source increment */
#define IS_DMA_SRC_INC(value)                            \
  (((value) == (uint32_t)HAL_DMA_SRC_ADDR_FIXED)         \
   || ((value) == (uint32_t)HAL_DMA_SRC_ADDR_INCREMENTED))

/*! Macro to check DMA destination increment */
#define IS_DMA_DEST_INC(value)                            \
  (((value) == (uint32_t)HAL_DMA_DEST_ADDR_FIXED)         \
   || ((value) == (uint32_t)HAL_DMA_DEST_ADDR_INCREMENTED))

/*! Macro to check DMA source data width */
#define IS_DMA_SRC_DATA_WIDTH(value)                         \
  (((value) == (uint32_t)HAL_DMA_SRC_DATA_WIDTH_BYTE)        \
   || ((value) == (uint32_t)HAL_DMA_SRC_DATA_WIDTH_HALFWORD) \
   || ((value) == (uint32_t)HAL_DMA_SRC_DATA_WIDTH_WORD))

/*! Macro to check DMA destination data width */
#define IS_DMA_DEST_DATA_WIDTH(value)                         \
  (((value) == (uint32_t)HAL_DMA_DEST_DATA_WIDTH_BYTE)        \
   || ((value) == (uint32_t)HAL_DMA_DEST_DATA_WIDTH_HALFWORD) \
   || ((value) == (uint32_t)HAL_DMA_DEST_DATA_WIDTH_WORD))

/*! Macro to check DMA priority */
#define IS_DMA_PRIORITY(value)                                \
  (((value) == (uint32_t)HAL_DMA_PRIORITY_LOW_WEIGHT_LOW)     \
   || ((value) == (uint32_t)HAL_DMA_PRIORITY_LOW_WEIGHT_MID)  \
   || ((value) == (uint32_t)HAL_DMA_PRIORITY_LOW_WEIGHT_HIGH) \
   || ((value) == (uint32_t)HAL_DMA_PRIORITY_HIGH))

/*! Macro to check DMA port */
#define IS_DMA_PORT(value)                                                     \
  (((value) == (uint32_t)HAL_DMA_PORT0) || ((value) == (uint32_t)HAL_DMA_PORT1))

/*! Macro to check DMA trigger source */
#if defined (JPEG)
#define IS_DMA_TRIGGER_SOURCE(value)                   \
  ((value) <= (uint32_t)HAL_GPDMA1_TRIGGER_JPEG_OFT_TRG)
#else
#define IS_DMA_TRIGGER_SOURCE(value)                \
  ((value) <= (uint32_t)HAL_GPDMA1_TRIGGER_ADC1_AWD1)
#endif /* defined (JPEG) */

/*! Macro to check DMA trigger polarity */
#define IS_DMA_TRIGGER_POLARITY(value)                       \
  (((value) == (uint32_t)HAL_DMA_TRIGGER_POLARITY_MASKED)    \
   || ((value) == (uint32_t)HAL_DMA_TRIGGER_POLARITY_RISING) \
   || ((value) == (uint32_t)HAL_DMA_TRIGGER_POLARITY_FALLING))

/*! Macro to check DMA trigger mode */
#define IS_DMA_TRIGGER_MODE(value)                                   \
  (((value) == (uint32_t)HAL_DMA_TRIGGER_BLOCK_TRANSFER)             \
   || ((value) == (uint32_t)HAL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER) \
   || ((value) == (uint32_t)HAL_DMA_TRIGGER_NODE_TRANSFER)           \
   || ((value) == (uint32_t)HAL_DMA_TRIGGER_SINGLE_BURST_TRANSFER))

/*! Macro to check DMA source byte exchange */
#define IS_DMA_SRC_BYTE_EXCHANGE(value)                \
  (((value) == (uint32_t)HAL_DMA_SRC_BYTE_PRESERVED)   \
   || ((value) == (uint32_t)HAL_DMA_SRC_BYTE_EXCHANGED))

/*! Macro to check DMA destination byte exchange */
#define IS_DMA_DEST_BYTE_EXCHANGE(value)                \
  (((value) == (uint32_t)HAL_DMA_DEST_BYTE_PRESERVED)   \
   || ((value) == (uint32_t)HAL_DMA_DEST_BYTE_EXCHANGED))

/*! Macro to check DMA destination halfword exchange */
#define IS_DMA_DEST_HALFWORD_EXCHANGE(value)                \
  (((value) == (uint32_t)HAL_DMA_DEST_HALFWORD_PRESERVED)   \
   || ((value) == (uint32_t)HAL_DMA_DEST_HALFWORD_EXCHANGED))

/*! Macro to check DMA destination data truncation and padding */
#define IS_DMA_DEST_DATA_TRUNC_PADD(value)                          \
  (((value) == (uint32_t)HAL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO)    \
   || ((value) == (uint32_t)HAL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN))

/*! Macro to check DMA destination data packing */
#define IS_DMA_DEST_DATA_PACK(value)                          \
  (((value) == (uint32_t)HAL_DMA_DEST_DATA_PRESERVED)         \
   || ((value) == (uint32_t)HAL_DMA_DEST_DATA_PACKED_UNPACKED))

/*! Macro to check DMA block count */
#define IS_DMA_BLOCK_COUNT(value) ((value) <= 0x0800U)

/*! Macro to check DMA burst source offset byte */
#define IS_DMA_BURST_SRC_OFFSET_BYTE(value) ((value) <= 0x1FFFU)

/*! Macro to check DMA burst destination offset byte */
#define IS_DMA_BURST_DEST_OFFSET_BYTE(value) ((value) <= 0x1FFFU)

/*! Macro to check DMA block source offset byte */
#define IS_DMA_BLOCK_SRC_OFFSET_BYTE(value) ((value) <= 0xFFFFU)

/*! Macro to check DMA block destination offset byte */
#define IS_DMA_BLOCK_DEST_OFFSET_BYTE(value) ((value) <= 0xFFFFU)

/*! Macro to check DMA busrt source increment */
#define IS_DMA_BURST_SRC_INC(value)                            \
  (((value) == (uint32_t)HAL_DMA_BURST_SRC_ADDR_INCREMENTED)   \
   || ((value) == (uint32_t)HAL_DMA_BURST_SRC_ADDR_DECREMENTED))

/*! Macro to check DMA busrt destination increment */
#define IS_DMA_BURST_DEST_INC(value)                            \
  (((value) == (uint32_t)HAL_DMA_BURST_DEST_ADDR_INCREMENTED)   \
   || ((value) == (uint32_t)HAL_DMA_BURST_DEST_ADDR_DECREMENTED))

/*! Macro to check DMA block source increment */
#define IS_DMA_BLOCK_SRC_INC(value)                            \
  (((value) == (uint32_t)HAL_DMA_BLOCK_SRC_ADDR_INCREMENTED)   \
   || ((value) == (uint32_t)HAL_DMA_BLOCK_SRC_ADDR_DECREMENTED))

/*! Macro to check DMA block destination increment */
#define IS_DMA_BLOCK_DEST_INC(value)                            \
  (((value) == (uint32_t)HAL_DMA_BLOCK_DEST_ADDR_INCREMENTED)   \
   || ((value) == (uint32_t)HAL_DMA_BLOCK_DEST_ADDR_DECREMENTED))

/*! Macro to check DMA event mode */
#define IS_DMA_XFER_EVENT_MODE(value)                                \
  (((value) == (uint32_t)HAL_DMA_DIRECT_XFER_EVENT_BLOCK)            \
   || ((value) == (uint32_t)HAL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK))

/*! Macro to check DMA linked-list event mode */
#define IS_DMA_LINKEDLIST_XFER_EVENT_MODE(value)                          \
  (((value) == (uint32_t)HAL_DMA_LINKEDLIST_XFER_EVENT_BLOCK)             \
   || ((value) == (uint32_t)HAL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK) \
   || ((value) == (uint32_t)HAL_DMA_LINKEDLIST_XFER_EVENT_NODE)           \
   || ((value) == (uint32_t)HAL_DMA_LINKEDLIST_XFER_EVENT_Q))

/*! Macro to check DMA linked-list execution mode */
#define IS_DMA_LINKEDLIST_EXEC_MODE(value)                    \
  (((value) == (uint32_t)HAL_DMA_LINKEDLIST_EXECUTION_Q)      \
   || ((value) == (uint32_t)HAL_DMA_LINKEDLIST_EXECUTION_NODE))

/*! Macro to check DMA secure attribute */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_DMA_SEC_ATTR(value)               \
  (((value) == (uint32_t)HAL_DMA_ATTR_NSEC)  \
   || ((value) == (uint32_t)HAL_DMA_ATTR_SEC))
#endif /* __ARM_FEATURE_CMSE */

/*! Macro to check DMA optional interrupt */
#define IS_DMA_OPT_IT(value)              \
  (((value) == HAL_DMA_OPT_IT_NONE)       \
   || ((value) == HAL_DMA_OPT_IT_HT)      \
   || ((value) == HAL_DMA_OPT_IT_TO)      \
   || ((value) == HAL_DMA_OPT_IT_DEFAULT) \
   || ((value) == HAL_DMA_OPT_IT_SILENT))

/*! Macro to check DMA transfer level */
#define IS_DMA_XFER_LEVEL(value)                       \
  (((value) == (uint32_t)HAL_DMA_XFER_FULL_COMPLETE)   \
   || ((value) == (uint32_t)HAL_DMA_XFER_HALF_COMPLETE))

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/*! Macro to get the node type of selected instance */
#define DMA_GET_NODE_TYPE(instance)                                                          \
  (((hal_dma_channel_t)(instance) < HAL_GPDMA1_CH12) ? HAL_DMA_NODE_LINEAR_ADDRESSING : \
   ((hal_dma_channel_t)(instance) < HAL_LPDMA1_CH0)  ? HAL_DMA_NODE_2D_ADDRESSING     : \
   HAL_DMA_NODE_LINEAR_ADDRESSING)
#endif /* USE_HAL_DMA_LINKEDLIST */

/*! Macro to get the DMA channel instance */
#define DMA_CHANNEL_GET_INSTANCE(handle)                \
  ((DMA_Channel_TypeDef *)((uint32_t)(handle)->instance))

/*! Macro to define DMA CTR1 register offset */
#define DMA_NODE_CTR1_REG_OFFSET 0U

/*! Macro to define DMA CTR2 register offset */
#define DMA_NODE_CTR2_REG_OFFSET 1U

/*! Macro to define DMA CBR1 register offset */
#define DMA_NODE_CBR1_REG_OFFSET 2U

/*! Macro to define DMA CSAR register offset */
#define DMA_NODE_CSAR_REG_OFFSET 3U

/*! Macro to define DMA CDAR register offset */
#define DMA_NODE_CDAR_REG_OFFSET 4U

/*! Macro to define DMA CTR3 register offset */
#define DMA_NODE_CTR3_REG_OFFSET 5U

/*! Macro to define DMA CBR2 register offset */
#define DMA_NODE_CBR2_REG_OFFSET 6U

/**
  * @}
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Constants DMA Private Constants
  * @{
  */
#define DMA_SUSPEND_TIMEOUT (5U)          /*!< 5 ms are need to suspend the DMA channel */

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#define HAL_DMA_FLAG_ERROR (LL_DMA_FLAG_DTE | LL_DMA_FLAG_ULE | LL_DMA_FLAG_USE) /*!< DMA Flag error */
#else
#define HAL_DMA_FLAG_ERROR (LL_DMA_FLAG_DTE | LL_DMA_FLAG_USE)                   /*!< DMA Flag error */
#endif /* USE_HAL_DMA_LINKEDLIST */

#define DMA_NODE_CLLR_IDX            0x0700U                   /*!< DMA channel node CLLR index mask     */
#define DMA_NODE_CLLR_IDX_POS        0x0008U                   /*!< DMA channel node CLLR index position */
#define DMA_NODE_REGISTER_NUM        LL_DMA_NODE_REGISTER_NUM  /*!< DMA channel node register number     */
#define DMA_NODE_STATIC_FORMAT       0x0000U                   /*!< DMA channel node static format       */
#define DMA_NODE_DYNAMIC_FORMAT      0x0001U                   /*!< DMA channel node dynamic format      */
#define DMA_UPDATE_CLLR_POSITION     0x0000U                   /*!< DMA channel update CLLR position     */
#define DMA_UPDATE_CLLR_VALUE        0x0001U                   /*!< DMA channel update CLLR value        */
#define DMA_LASTNODE_ISNOT_CIRCULAR  0x0000U                   /*!< Last node is not first circular node */
#define DMA_LASTNODE_IS_CIRCULAR     0x0001U                   /*!< Last node is first circular node     */
#define DMA_NODE_CSAR_DEFAULT_OFFSET 0x0003U                   /*!< CSAR default offset                  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup DMA_Private_Functions
  * @{
  */
static void DMA_SetConfigDirectXfer(hal_dma_handle_t *hdma, const hal_dma_direct_xfer_config_t *p_config);

static void DMA_GetConfigDirectXfer(hal_dma_handle_t *hdma, hal_dma_direct_xfer_config_t *p_config);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
static void DMA_SetConfigLinkedListXfer(hal_dma_handle_t *hdma, const hal_dma_linkedlist_xfer_config_t *p_config);

static void DMA_GetConfigLinkedListXfer(hal_dma_handle_t *hdma, hal_dma_linkedlist_xfer_config_t *p_config);

static void DMA_FillNodeConfig(hal_dma_node_t *p_node, const hal_dma_node_config_t *p_conf,
                               hal_dma_node_type_t node_type);

static void DMA_GetConfigNode(const hal_dma_node_t *p_node, hal_dma_node_config_t *p_conf,
                              hal_dma_node_type_t *p_node_type);

static void DMA_FillNodeDirectXfer(hal_dma_node_t *p_node, const hal_dma_direct_xfer_config_t *p_config,
                                   hal_dma_node_type_t node_type, hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode);

static void DMA_UpdateDataNode(hal_dma_node_t *p_node, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte);

static void DMA_ConvertQNodesToDynamic(hal_q_t *p_q);

static void DMA_ConvertQNodesToStatic(hal_q_t *p_q);

static void DMA_List_ConvertNodeToDynamic(uint32_t context_node_addr, uint32_t current_node_addr, uint32_t reg_nbr);

static void DMA_List_ConvertNodeToStatic(uint32_t context_node_addr, uint32_t current_node_addr, uint32_t reg_nbr);

static void DMA_List_UpdateDynamicQueueNodesCLLR(const hal_q_t *p_q, uint32_t last_node_is_circular);

static void DMA_List_UpdateStaticQueueNodesCLLR(hal_q_t *p_q, uint32_t operation);

static void DMA_List_GetCLLRNodeInfo(const hal_dma_node_t *p_node, uint32_t *p_cllr_mask, uint32_t *p_cllr_offset);

static void DMA_List_FormatNode(hal_dma_node_t *p_node, uint32_t reg_idx, uint32_t reg_nbr, uint32_t format);

static void DMA_List_ClearUnusedFields(hal_dma_node_t *p_node, uint32_t first_unused_field);
#endif /* USE_HAL_DMA_LINKEDLIST */

static void DMA_StartDirectXfer(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte,
                                uint32_t interrupts);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
static void DMA_StartLinkedListXfer(hal_dma_handle_t *hdma, const void *p_head_node, uint32_t interrupts);
#endif /* USE_HAL_DMA_LINKEDLIST */

static void DMA_HandleErrorIT(hal_dma_handle_t *hdma, uint32_t error_msk);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup DMA_Exported_Functions
  * @{
  */

/** @addtogroup DMA_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and De-initialize a DMA channel peripheral:

- Call the function HAL_DMA_Init() to initialize the DMA channel handle and associate a physical channel instance.
  (As optional, DMA clock is enabled inside the function)

- Call the function HAL_DMA_DeInit() to restore the physical and logical default configuration (after reset) of
  the selected DMA channel peripheral.

  */

/**
  * @brief  Initialize the DMA channel handle and associate physical channel instance.
  * @param  hdma              Pointer to DMA channel handle
  * @param  instance          Specifie the DMA channel instance
  * @retval HAL_INVALID_PARAM Invalid parameter when hdma pointer is NULL
  * @retval HAL_OK            DMA channel is successfully initialized
  */
hal_status_t HAL_DMA_Init(hal_dma_handle_t *hdma, hal_dma_channel_t instance)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_ALL_INSTANCE((DMA_Channel_TypeDef *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma->instance = instance;

#if defined(USE_HAL_DMA_CLK_ENABLE_MODEL) && (USE_HAL_DMA_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  if (LL_DMA_GET_INSTANCE(hdma->instance) == GPDMA1)
  {
    HAL_RCC_GPDMA1_EnableClock();
  }
  else
  {
    HAL_RCC_LPDMA1_EnableClock();
  }
#endif /* USE_HAL_DMA_CLK_ENABLE_MODEL */

  hdma->p_xfer_halfcplt_cb = HAL_DMA_XferHalfCpltCallback;
  hdma->p_xfer_cplt_cb     = HAL_DMA_XferCpltCallback;
  hdma->p_xfer_abort_cb    = HAL_DMA_XferAbortCallback;
  hdma->p_xfer_suspend_cb  = HAL_DMA_XferSuspendCallback;
  hdma->p_xfer_error_cb    = HAL_DMA_XferErrorCallback;

#if defined(USE_HAL_DMA_USER_DATA) && (USE_HAL_DMA_USER_DATA == 1)
  hdma->p_user_data = NULL;
#endif /* USE_HAL_DMA_USER_DATA */

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  hdma->xfer_mode = HAL_DMA_XFER_MODE_DIRECT;
#endif /* USE_HAL_DMA_LINKEDLIST */

  hdma->global_state = HAL_DMA_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief Deinitialize the DMA channel handle by aborting any DMA ongoing transfer.
  * @param hdma Pointer to DMA channel handle
  */
void HAL_DMA_DeInit(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_ALL_INSTANCE(DMA_CHANNEL_GET_INSTANCE(hdma)));

  LL_DMA_DisableChannel(DMA_CHANNEL_GET_INSTANCE(hdma));
  LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_ALL);

  LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CCR, 0U);
  LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CTR1, 0U);
  LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CTR2, 0U);
  LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CBR1, 0U);

  if (IS_DMA_2D_ADDRESSING_INSTANCE(DMA_CHANNEL_GET_INSTANCE(hdma)))
  {
    LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CTR3, 0U);
    LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CBR2, 0U);
  }

  LL_DMA_WRITE_REG(DMA_CHANNEL_GET_INSTANCE(hdma), CLLR, 0U);

  hdma->global_state = HAL_DMA_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group2
  * @{

This subsection provides a set of functions allowing to configure the DMA channel peripheral:

  Basic transfer configuration

- Call the function HAL_DMA_SetConfigDirectXfer() to configure the DMA channel basic transfer according to configured
  parameter within hal_dma_direct_xfer_config_t structure

- Call the function HAL_DMA_GetConfigDirectXfer() to get the current configured basic transfer

  Hardware request mode transfer configuration

- Call the function HAL_DMA_SetConfigDirectXferHardwareRequestMode() to configure the DMA channel transfer hardware
  request mode according to configured parameters

- Call the function HAL_DMA_ResetConfigDirectXferHardwareRequestMode() to reset the DMA channel transfer hardware
  request mode configuration

- Call the function HAL_DMA_GetConfigDirectXferHardwareRequestMode() to get the current configured transfer hardware
  request mode

  Port transfer configuration

- Call the function HAL_DMA_SetConfigDirectXferPort() to configure the DMA channel transfer ports according to
  configured parameters

- Call the function HAL_DMA_ResetConfigDirectXferPort() to reset the DMA channel transfer ports configuration

- Call the function HAL_DMA_GetConfigDirectXferPort() to get the current configured transfer ports

  Burst transfer configuration

- Call the function HAL_DMA_SetConfigDirectXferBurst() to configure the DMA channel burst length according to configured
  parameter

- Call the function HAL_DMA_ResetConfigDirectXferBurst() to reset the DMA channel transfer burst configuration

- Call the function HAL_DMA_GetConfigDirectXferBurst() to get the current configured burst

  Trigger transfer configuration

- Call the function HAL_DMA_SetConfigDirectXferTrigger() to configure the DMA channel trigger according to configured
  parameter within hal_dma_trigger_config_t structure

- Call the function HAL_DMA_ResetConfigDirectXferTrigger() to reset the DMA channel transfer trigger configuration

- Call the function HAL_DMA_GetConfigDirectXferTrigger() to get the current configured trigger

  Data handling transfer configuration

- Call the function HAL_DMA_SetConfigDirectXferDataHandling() to configure the DMA channel data handling according to
  configured parameter within hal_dma_data_handling_config_t structure

- Call the function HAL_DMA_ResetConfigDirectXferDataHandling() to reset the DMA channel transfer data handling
  configuration

- Call the function HAL_DMA_GetConfigDirectXferDataHandling() to get the current configured data handling

  Repeated block transfer configuration

- Call the function HAL_DMA_SetConfigDirectXferRepeatBlock() to configure the DMA channel repeated block according to
  configured parameter within hal_dma_repeat_block_config_t structure

- Call the function HAL_DMA_ResetConfigDirectXferRepeatBlock() to reset the DMA channel transfer repeated block
  configuration

- Call the function HAL_DMA_GetConfigDirectXferRepeatBlock() to get the current configured repeated block

  Security access attributes configuration

- Call the function HAL_DMA_SetConfigAccessAttributes() to configure the DMA channel security access attributes
  according to configured parameters

- Call the function HAL_DMA_ResetConfigAccessAttributes() to reset the DMA channel security access attributes
  configuration

- Call the function HAL_DMA_GetConfigAccessAttributes() to get the current configured security access attributes

  Peripherals direct transfer configuration

- Call the function HAL_DMA_SetConfigPeriphDirectXfer() to configure the DMA channel peripheral direct transfer
  according to configured parameter within hal_dma_direct_xfer_config_t structure:

- Call the function HAL_DMA_GetConfigPeriphDirectXfer() to get the current configured direct transfer

  Linked-list transfer configuration

- Call the function HAL_DMA_SetConfigLinkedListXfer() to configure the DMA channel linked-list transfer according to
  configured parameter within hal_dma_linkedlist_xfer_config_t structure

- Call the function HAL_DMA_GetConfigLinkedListXfer() to get the current configured linked-list transfer

  Event mode transfer configuration

- Call the function HAL_DMA_SetLinkedListXferEventMode() to configure the DMA channel event mode according to
  selected parameter within hal_dma_linkedlist_xfer_event_mode_t enumeration

- Call the function HAL_DMA_ResetLinkedListXferEventMode() to reset the DMA channel event mode configuration

- Call the function HAL_DMA_GetLinkedListXferEventMode() to get the current configured event mode

  Fetch node port transfer configuration

- Call the function HAL_DMA_SetLinkedListXferFetchNodePort() to configure the DMA channel fetch node port according
  to selected parameter within hal_dma_port_t enumeration

- Call the function HAL_DMA_ResetLinkedListXferFetchNodePort() to reset the DMA channel fetch node port configuration

- Call the function HAL_DMA_GetLinkedListXferFetchNodePort() to get the current configured fetch node port

  Priority transfer configuration

- Call the function HAL_DMA_SetLinkedListXferPriority() to configure the DMA channel priority according to selected
  parameter within hal_dma_priority_t enumeration

- Call the function HAL_DMA_ResetLinkedListXferPriority() to reset the DMA channel priority configuration

- Call the function HAL_DMA_GetLinkedListXferPriority() to get the current configured priority

  Execution mode transfer configuration

- Call the function HAL_DMA_SetLinkedListXferExecutionMode() to configure the DMA channel execution mode according to
  selected parameter within hal_dma_linkedlist_execution_mode_t enumeration

- Call the function HAL_DMA_ResetLinkedListXferExecutionMode() to reset the DMA channel execution mode configuration

- Call the function HAL_DMA_GetLinkedListXferExecutionMode() to get the current configured execution mode

  Peripherals linked-list circular transfer configuration

- Call the function HAL_DMA_SetConfigPeriphLinkedListCircularXfer() to configure the DMA channel peripheral linked-list
  circular transfer according to configured parameter within hal_dma_direct_xfer_config_t structure

- Call the function HAL_DMA_GetConfigPeriphLinkedListCircularXfer() to get the current configured peripheral linked-list
  circular transfer
  */

/**
  * @brief  Set the DMA channel direct transfer configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_config          Pointer to hal_dma_direct_xfer_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL
  * @retval HAL_OK            Direct transfer is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXfer(hal_dma_handle_t *hdma, const hal_dma_direct_xfer_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_REQUEST((uint32_t)p_config->request));
  ASSERT_DBG_PARAM(IS_DMA_DIRECTION((uint32_t)p_config->direction));
  ASSERT_DBG_PARAM(IS_DMA_SRC_INC((uint32_t)p_config->src_inc));
  ASSERT_DBG_PARAM(IS_DMA_DEST_INC((uint32_t)p_config->dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_SRC_DATA_WIDTH((uint32_t)p_config->src_data_width));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_WIDTH((uint32_t)p_config->dest_data_width));
  ASSERT_DBG_PARAM(IS_DMA_PRIORITY((uint32_t)p_config->priority));
  ASSERT_DBG_STATE(hdma->global_state, (uint32_t)HAL_DMA_STATE_INIT | (uint32_t)HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_SetConfigDirectXfer(hdma, p_config);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  hdma->xfer_mode = HAL_DMA_XFER_MODE_DIRECT;
#endif /* USE_HAL_DMA_LINKEDLIST */

  hdma->global_state = HAL_DMA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_direct_xfer_config_t configuration structure
  */
void HAL_DMA_GetConfigDirectXfer(hal_dma_handle_t *hdma, hal_dma_direct_xfer_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  DMA_GetConfigDirectXfer(hdma, p_config);
}

/**
  * @brief  Set the DMA channel direct transfer hardware request mode configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  hw_request_mode      Element in @ref hal_dma_hardware_request_mode_t  enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Request mode is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXferHardwareRequestMode(hal_dma_handle_t *hdma,
                                                            hal_dma_hardware_request_mode_t  hw_request_mode)
{
  ASSERT_DBG_PARAM(hdma     != NULL);
  ASSERT_DBG_PARAM(IS_DMA_HARDWARE_REQUEST_MODE((uint32_t)hw_request_mode));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_SetHWRequestMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)hw_request_mode);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel direct transfer hardware request mode configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset direct transfer request mode configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigDirectXferHardwareRequestMode(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_SetHWRequestMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_HARDWARE_REQUEST_BURST);

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer hardware request mode configuration.
  * @param hdma     Pointer to DMA channel handle
  * @retval Returned value can be one of the following values:
  *         @arg @ref HAL_DMA_HARDWARE_REQUEST_BURST
  *         @arg @ref HAL_DMA_HARDWARE_REQUEST_BLOCK
  */
hal_dma_hardware_request_mode_t  HAL_DMA_GetConfigDirectXferHardwareRequestMode(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  return ((hal_dma_hardware_request_mode_t)LL_DMA_GetHWRequestType(DMA_CHANNEL_GET_INSTANCE(hdma)));
}

/**
  * @brief  Set the DMA channel direct transfer source and destination allocated port configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  src_port          Pointer to @ref hal_dma_port_t enumeration
  * @param  dest_port         Pointer to @ref hal_dma_port_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Direct transfer port is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXferPort(hal_dma_handle_t *hdma, hal_dma_port_t src_port, hal_dma_port_t dest_port)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)src_port));
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)dest_port));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_ConfigAccessPorts(DMA_CHANNEL_GET_INSTANCE(hdma), (((uint32_t)src_port << DMA_CTR1_SAP_Pos) |
                                                            ((uint32_t)dest_port << DMA_CTR1_DAP_Pos)));

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel direct transfer port configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset direct transfer port configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigDirectXferPort(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_ConfigAccessPorts(DMA_CHANNEL_GET_INSTANCE(hdma), (((uint32_t)HAL_DMA_PORT0 << DMA_CTR1_SAP_Pos) |
                                                            ((uint32_t)HAL_DMA_PORT0 << DMA_CTR1_DAP_Pos)));

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer port configuration.
  * @param hdma      Pointer to DMA channel handle
  * @param p_src_port  Pointer to @ref hal_dma_port_t enumeration
  * @param p_dest_port Pointer to @ref hal_dma_port_t enumeration
  */
void HAL_DMA_GetConfigDirectXferPort(hal_dma_handle_t *hdma, hal_dma_port_t *p_src_port, hal_dma_port_t *p_dest_port)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_src_port != NULL);
  ASSERT_DBG_PARAM(p_dest_port != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  *p_src_port  =
    (hal_dma_port_t)((uint32_t)(LL_DMA_GetSrcAllocatedPort(DMA_CHANNEL_GET_INSTANCE(hdma)) >> DMA_CTR1_SAP_Pos));
  *p_dest_port =
    (hal_dma_port_t)((uint32_t)(LL_DMA_GetDestAllocatedPort(DMA_CHANNEL_GET_INSTANCE(hdma)) >> DMA_CTR1_DAP_Pos));
}

/**
  * @brief  Set the DMA channel direct transfer burst configuration.
  * @param  hdma                   Pointer to DMA channel handle
  * @param  src_burst_length_byte  Source burst length in byte
  * @param  dest_burst_length_byte Destination burst length in byte
  * @retval HAL_INVALID_PARAM      Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK                 Direct transfer burst is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXferBurst(hal_dma_handle_t *hdma, uint32_t src_burst_length_byte,
                                              uint32_t dest_burst_length_byte)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM((src_burst_length_byte > 0U) && (src_burst_length_byte <= 64U));
  ASSERT_DBG_PARAM((dest_burst_length_byte > 0U) && (dest_burst_length_byte <= 64U));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_ConfigBurstLength(DMA_CHANNEL_GET_INSTANCE(hdma), src_burst_length_byte, dest_burst_length_byte);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel direct transfer burst configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset direct transfer burst configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigDirectXferBurst(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_ConfigBurstLength(DMA_CHANNEL_GET_INSTANCE(hdma), 1U, 1U);

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer burst configuration.
  * @param hdma                     Pointer to DMA channel handle
  * @param p_src_burst_length_byte  Source burst length in byte
  * @param p_dest_burst_length_byte Destination burst length in byte
  */
void HAL_DMA_GetConfigDirectXferBurst(hal_dma_handle_t *hdma, uint32_t *p_src_burst_length_byte,
                                      uint32_t *p_dest_burst_length_byte)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_src_burst_length_byte != NULL);
  ASSERT_DBG_PARAM(p_dest_burst_length_byte != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  *p_src_burst_length_byte  = LL_DMA_GetSrcBurstLength(DMA_CHANNEL_GET_INSTANCE(hdma));
  *p_dest_burst_length_byte = LL_DMA_GetDestBurstLength(DMA_CHANNEL_GET_INSTANCE(hdma));
}

/**
  * @brief  Set the DMA channel direct transfer trigger configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_config          Pointer to hal_dma_trigger_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct or p_config pointer is
  *                           NULL
  * @retval HAL_OK            Direct transfer trigger is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXferTrigger(hal_dma_handle_t *hdma, const hal_dma_trigger_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_SOURCE((uint32_t)p_config->source));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_POLARITY((uint32_t)p_config->polarity));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_MODE((uint32_t)p_config->mode));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_ConfigChannelTrigger(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_config->source,
                              ((uint32_t)p_config->mode | (uint32_t)p_config->polarity));

  return HAL_OK;
}

/**
  * @brief Reset the DMA channel direct transfer trigger configuration.
  * @param hdma               Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset direct transfer trigger configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigDirectXferTrigger(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_ConfigChannelTrigger(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_GPDMA1_TRIGGER_EXTI0,
                              ((uint32_t)HAL_DMA_TRIGGER_BLOCK_TRANSFER | (uint32_t)HAL_DMA_TRIGGER_POLARITY_MASKED));

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer trigger configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_trigger_config_t configuration structure
  */
void HAL_DMA_GetConfigDirectXferTrigger(hal_dma_handle_t *hdma, hal_dma_trigger_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  p_config->mode     = (hal_dma_trigger_mode_t)LL_DMA_GetTriggerMode(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->polarity = (hal_dma_trigger_polarity_t)LL_DMA_GetTriggerPolarity(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->source   = (hal_dma_trigger_source_t)LL_DMA_GetHWTrigger(DMA_CHANNEL_GET_INSTANCE(hdma));
}

/**
  * @brief  Set the DMA channel direct transfer data handling configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_config          Pointer to hal_dma_data_handling_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct or p_config pointer is
  *                           NULL
  * @retval HAL_OK            Direct transfer data handling is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXferDataHandling(hal_dma_handle_t *hdma,
                                                     const hal_dma_data_handling_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_SRC_BYTE_EXCHANGE((uint32_t)p_config->src_byte_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_BYTE_EXCHANGE((uint32_t)p_config->dest_byte_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_HALFWORD_EXCHANGE((uint32_t)p_config->dest_halfword_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_TRUNC_PADD((uint32_t)p_config->trunc_padd));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_PACK((uint32_t)p_config->pack));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_ConfigDataHandling(DMA_CHANNEL_GET_INSTANCE(hdma),
                            (uint32_t)p_config->src_byte_exchange      |
                            (uint32_t)p_config->dest_byte_exchange     |
                            (uint32_t)p_config->dest_halfword_exchange |
                            (uint32_t)p_config->pack                   |
                            (uint32_t)p_config->trunc_padd);
  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel direct transfer data handling configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset direct transfer data handling configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigDirectXferDataHandling(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  /* Reset DMA channel data handling configuration */
  LL_DMA_ConfigDataHandling(DMA_CHANNEL_GET_INSTANCE(hdma),
                            (uint32_t)HAL_DMA_SRC_BYTE_PRESERVED             |
                            (uint32_t)HAL_DMA_DEST_BYTE_PRESERVED            |
                            (uint32_t)HAL_DMA_DEST_HALFWORD_PRESERVED        |
                            (uint32_t)HAL_DMA_DEST_DATA_PRESERVED            |
                            (uint32_t)HAL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO);

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer data handling configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_data_handling_config_t configuration structure
  */
void HAL_DMA_GetConfigDirectXferDataHandling(hal_dma_handle_t *hdma, hal_dma_data_handling_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  p_config->src_byte_exchange      =
    (hal_dma_src_byte_exchange_t)LL_DMA_GetSrcByteExchange(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->dest_byte_exchange     =
    (hal_dma_dest_byte_exchange_t)LL_DMA_GetDestByteExchange(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->dest_halfword_exchange =
    (hal_dma_dest_halfword_exchange_t)LL_DMA_GetDestHWordExchange(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->trunc_padd             =
    (hal_dma_dest_data_trunc_padd_t)LL_DMA_GetDataTruncPadd(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->pack                   =
    (hal_dma_dest_data_pack_t)LL_DMA_GetDataPacking(DMA_CHANNEL_GET_INSTANCE(hdma));
}

/**
  * @brief  Set the DMA channel direct transfer repeated block configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_config          Pointer to hal_dma_repeat_block_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct or p_config pointer is
  *                           NULL
  * @retval HAL_OK            Direct transfer repeated block is successfully configured
  */
hal_status_t HAL_DMA_SetConfigDirectXferRepeatBlock(hal_dma_handle_t *hdma,
                                                    const hal_dma_repeat_block_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_COUNT((uint32_t)p_config->block_count));
  ASSERT_DBG_PARAM(IS_DMA_BURST_SRC_OFFSET_BYTE((uint32_t)p_config->burst_src_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BURST_DEST_OFFSET_BYTE((uint32_t)p_config->burst_dest_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_SRC_OFFSET_BYTE((uint32_t)p_config->block_src_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_DEST_OFFSET_BYTE((uint32_t)p_config->block_dest_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BURST_SRC_INC((uint32_t)p_config->burst_src_inc));
  ASSERT_DBG_PARAM(IS_DMA_BURST_DEST_INC((uint32_t)p_config->burst_dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_SRC_INC((uint32_t)p_config->block_src_inc));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_DEST_INC((uint32_t)p_config->block_dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_XFER_EVENT_MODE((uint32_t)p_config->xfer_event_mode));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_ConfigBlkRpt(DMA_CHANNEL_GET_INSTANCE(hdma), p_config->block_count, (uint32_t)p_config->burst_src_inc  |
                      (uint32_t)p_config->burst_dest_inc |
                      (uint32_t)p_config->block_src_inc  |
                      (uint32_t)p_config->block_dest_inc);
  LL_DMA_ConfigAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma), p_config->burst_src_offset_byte,
                               p_config->burst_dest_offset_byte);
  LL_DMA_ConfigBlkRptAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma), p_config->block_src_offset_byte,
                                     p_config->block_dest_offset_byte);
  LL_DMA_SetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_config->xfer_event_mode);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel direct transfer repeated block configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset direct transfer repeated block configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigDirectXferRepeatBlock(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  LL_DMA_ConfigBlkRpt(DMA_CHANNEL_GET_INSTANCE(hdma), 1U, (uint32_t)HAL_DMA_BURST_SRC_ADDR_INCREMENTED  |
                      (uint32_t)HAL_DMA_BURST_DEST_ADDR_INCREMENTED |
                      (uint32_t)HAL_DMA_BLOCK_SRC_ADDR_INCREMENTED  |
                      (uint32_t)HAL_DMA_BLOCK_DEST_ADDR_INCREMENTED);
  LL_DMA_ConfigAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma), 0U, 0U);
  LL_DMA_ConfigBlkRptAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma), 0U, 0U);
  LL_DMA_SetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_DIRECT_XFER_EVENT_BLOCK);

  return HAL_OK;
}

/**
  * @brief Get the DMA channel direct transfer repeated block configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_repeat_block_config_t configuration structure
  */
void HAL_DMA_GetConfigDirectXferRepeatBlock(hal_dma_handle_t *hdma, hal_dma_repeat_block_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  p_config->block_count = LL_DMA_GetBlkRptCount(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->burst_src_inc = (hal_dma_burst_src_increment_t)LL_DMA_GetSrcAddrUpdate(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->burst_src_offset_byte  = LL_DMA_GetSrcAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->burst_dest_inc = (hal_dma_burst_dest_increment_t)LL_DMA_GetDestAddrUpdate(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->burst_dest_offset_byte = LL_DMA_GetDestAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->block_src_inc =
    (hal_dma_block_src_increment_t)LL_DMA_GetBlkRptSrcAddrUpdate(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->block_src_offset_byte = LL_DMA_GetBlkRptSrcAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->block_dest_inc =
    (hal_dma_block_dest_increment_t)LL_DMA_GetBlkRptDestAddrUpdate(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->block_dest_offset_byte = LL_DMA_GetBlkRptDestAddrUpdateValue(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->xfer_event_mode =
    (hal_dma_direct_xfer_event_mode_t)LL_DMA_GetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma));
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the DMA channel security access attributes configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  src_attr          Element in @ref hal_dma_sec_attr_t enumeration
  * @param  dest_attr         Element in @ref hal_dma_sec_attr_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Security access attributes is successfully configured
  */
hal_status_t HAL_DMA_SetConfigAccessAttributes(hal_dma_handle_t *hdma, hal_dma_sec_attr_t src_attr,
                                               hal_dma_sec_attr_t dest_attr)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_SEC_ATTR((uint32_t)src_attr));
  ASSERT_DBG_PARAM(IS_DMA_SEC_ATTR((uint32_t)dest_attr));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_ConfigChannelAccessSecurity(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)src_attr, (uint32_t)dest_attr);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel security access attributes configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_OK            Reset security access attributes configuration is successful
  */
hal_status_t HAL_DMA_ResetConfigAccessAttributes(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_ConfigChannelAccessSecurity(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_ATTR_NSEC,
                                     (uint32_t)HAL_DMA_ATTR_NSEC);

  return HAL_OK;
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief Get the DMA channel security access attributes configuration.
  * @param hdma        Pointer to DMA channel handle
  * @param p_src_attr  Pointer to hal_dma_sec_attr_t enumeration
  * @param p_dest_attr Pointer to hal_dma_sec_attr_t enumeration
  */
void HAL_DMA_GetConfigAccessAttributes(hal_dma_handle_t *hdma, hal_dma_sec_attr_t *p_src_attr,
                                       hal_dma_sec_attr_t *p_dest_attr)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_src_attr != NULL);
  ASSERT_DBG_PARAM(p_dest_attr != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  *p_src_attr  = (hal_dma_sec_attr_t)LL_DMA_GetChannelSrcSecurity(DMA_CHANNEL_GET_INSTANCE(hdma));
  *p_dest_attr = (hal_dma_sec_attr_t)LL_DMA_GetChannelDestSecurity(DMA_CHANNEL_GET_INSTANCE(hdma));

}

/**
  * @brief  Set the DMA channel peripheral direct transfer configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_config          Pointer to hal_dma_direct_xfer_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL
  * @retval HAL_OK            Peripheral direct transfer is successfully configured
  */
hal_status_t HAL_DMA_SetConfigPeriphDirectXfer(hal_dma_handle_t *hdma, const hal_dma_direct_xfer_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_REQUEST((uint32_t)p_config->request));
  ASSERT_DBG_PARAM(IS_DMA_DIRECTION((uint32_t)p_config->direction));
  ASSERT_DBG_PARAM(IS_DMA_SRC_INC((uint32_t)p_config->src_inc));
  ASSERT_DBG_PARAM(IS_DMA_DEST_INC((uint32_t)p_config->dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_SRC_DATA_WIDTH((uint32_t)p_config->src_data_width));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_WIDTH((uint32_t)p_config->dest_data_width));
  ASSERT_DBG_PARAM(IS_DMA_PRIORITY((uint32_t)p_config->priority));
  ASSERT_DBG_STATE(hdma->global_state, (uint32_t)HAL_DMA_STATE_INIT | (uint32_t)HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_SetConfigDirectXfer(hdma, p_config);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  hdma->xfer_mode = HAL_DMA_XFER_MODE_DIRECT;
#endif /* USE_HAL_DMA_LINKEDLIST */

  hdma->global_state = HAL_DMA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the DMA channel peripheral direct transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_direct_xfer_config_t configuration structure
  */
void HAL_DMA_GetConfigPeriphDirectXfer(hal_dma_handle_t *hdma, hal_dma_direct_xfer_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  DMA_GetConfigDirectXfer(hdma, p_config);
}

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/**
  * @brief  Set the DMA channel linked-list transfer configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_config          Pointer to hal_dma_linkedlist_xfer_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_config pointer is NULL
  * @retval HAL_OK            Linked-list transfer is successfully configured
  */
hal_status_t HAL_DMA_SetConfigLinkedListXfer(hal_dma_handle_t *hdma,
                                             const hal_dma_linkedlist_xfer_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma     != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_PRIORITY((uint32_t)p_config->priority));
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)p_config->fetch_port));
  ASSERT_DBG_PARAM(IS_DMA_LINKEDLIST_XFER_EVENT_MODE((uint32_t)p_config->xfer_event_mode));
  ASSERT_DBG_STATE(hdma->global_state, (uint32_t)HAL_DMA_STATE_INIT | (uint32_t)HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_SetConfigLinkedListXfer(hdma, p_config);

  hdma->xfer_mode = HAL_DMA_XFER_MODE_LINKEDLIST_LINEAR;

  hdma->global_state = HAL_DMA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the DMA channel linked-list transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_linkedlist_xfer_config_t configuration structure
  */
void HAL_DMA_GetConfigLinkedListXfer(hal_dma_handle_t *hdma, hal_dma_linkedlist_xfer_config_t *p_config)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  DMA_GetConfigLinkedListXfer(hdma, p_config);
}

/**
  * @brief  Set the DMA channel linked-list transfer event mode configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  xfer_event_mode   Element in @ref hal_dma_linkedlist_xfer_event_mode_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Linked-list transfer event mode is successfully configured
  */
hal_status_t HAL_DMA_SetLinkedListXferEventMode(hal_dma_handle_t *hdma,
                                                hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_LINKEDLIST_XFER_EVENT_MODE((uint32_t)xfer_event_mode));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)xfer_event_mode);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel linked-list transfer event mode configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Reset linked-list transfer event mode configuration is successful
  */
hal_status_t HAL_DMA_ResetLinkedListXferEventMode(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_LINKEDLIST_XFER_EVENT_BLOCK);

  return HAL_OK;
}

/**
  * @brief  Get the DMA channel linked-list transfer event mode configuration.
  * @param  hdma                                         Pointer to DMA channel handle
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_BLOCK          Linked-list transfer event block
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK Linked-list transfer event repeated block
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_NODE           Linked-list transfer event node
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_Q              Linked-list transfer event Q
  */
hal_dma_linkedlist_xfer_event_mode_t HAL_DMA_GetLinkedListXferEventMode(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  return ((hal_dma_linkedlist_xfer_event_mode_t)LL_DMA_GetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma)));
}

/**
  * @brief  Set the DMA channel linked-list transfer fetch node port configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  fetch_port        Element in @ref hal_dma_port_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Linked-list transfer fetch node port is successfully configured
  */
hal_status_t HAL_DMA_SetLinkedListXferFetchNodePort(hal_dma_handle_t *hdma, hal_dma_port_t fetch_port)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)fetch_port));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetLinkAllocatedPort(DMA_CHANNEL_GET_INSTANCE(hdma), ((uint32_t)fetch_port << DMA_CCR_LAP_Pos));

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel linked-list transfer fetch node port configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Reset linked-list transfer fetech node port configuration is successful
  */
hal_status_t HAL_DMA_ResetLinkedListXferFetchNodePort(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetLinkAllocatedPort(DMA_CHANNEL_GET_INSTANCE(hdma), ((uint32_t)HAL_DMA_PORT0 << DMA_CCR_LAP_Pos));

  return HAL_OK;
}

/**
  * @brief  Get the DMA channel linked-list transfer fetch node port configuration.
  * @param  hdma          Pointer to DMA channel handle
  * @retval HAL_DMA_PORT0 DMA channel port 0
  * @retval HAL_DMA_PORT1 DMA channel port 1
  */
hal_dma_port_t HAL_DMA_GetLinkedListXferFetchNodePort(hal_dma_handle_t *hdma)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  dummy = LL_DMA_GetLinkAllocatedPort(DMA_CHANNEL_GET_INSTANCE(hdma)) >> DMA_CCR_LAP_Pos;

  return ((hal_dma_port_t)dummy);
}

/**
  * @brief  Set the DMA channel linked-list transfer priority configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  priority          Element in @ref hal_dma_priority_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Linked-list transfer priority is successfully configured
  */
hal_status_t HAL_DMA_SetLinkedListXferPriority(hal_dma_handle_t *hdma, hal_dma_priority_t priority)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_PRIORITY((uint32_t)priority));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetChannelPriorityLevel(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)priority);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel linked-list transfer priority configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Reset linked-list transfer priority configuration is successful
  */
hal_status_t HAL_DMA_ResetLinkedListXferPriority(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetChannelPriorityLevel(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_PRIORITY_LOW_WEIGHT_LOW);

  return HAL_OK;
}

/**
  * @brief  Get the DMA channel linked-list transfer priority configuration.
  * @param  hdma                             Pointer to DMA channel handle
  * @retval HAL_DMA_PRIORITY_LOW_WEIGHT_LOW  DMA channel priority low and weight low
  * @retval HAL_DMA_PRIORITY_LOW_WEIGHT_MID  DMA channel priority low and weight mid
  * @retval HAL_DMA_PRIORITY_LOW_WEIGHT_HIGH DMA channel priority low and weight high
  * @retval HAL_DMA_PRIORITY_HIGH            DMA channel priority high
  */
hal_dma_priority_t HAL_DMA_GetLinkedListXferPriority(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  return ((hal_dma_priority_t)LL_DMA_GetChannelPriorityLevel(DMA_CHANNEL_GET_INSTANCE(hdma)));
}

/**
  * @brief  Set the DMA channel linked-list transfer execution mode configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  exec_mode         Element in hal_dma_linkedlist_execution_mode_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Linked-list transfer execution mode is successfully configured
  */
hal_status_t HAL_DMA_SetLinkedListXferExecutionMode(hal_dma_handle_t *hdma,
                                                    hal_dma_linkedlist_execution_mode_t exec_mode)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_LINKEDLIST_EXEC_MODE((uint32_t)exec_mode));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetLinkStepMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)exec_mode);

  return HAL_OK;
}

/**
  * @brief  Reset the DMA channel linked-list transfer execution mode configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is direct
  * @retval HAL_OK            Reset linked-list transfer execution mode configuration is successful
  */
hal_status_t HAL_DMA_ResetLinkedListXferExecutionMode(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_DMA_SetLinkStepMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_LINKEDLIST_EXECUTION_Q);

  return HAL_OK;
}

/**
  * @brief  Get the DMA channel linked-list transfer execution mode configuration.
  * @param  hdma                              Pointer to DMA channel handle
  * @retval HAL_DMA_LINKEDLIST_EXECUTION_Q    DMA Channel is executed for the full linked-list
  * @retval HAL_DMA_LINKEDLIST_NODE_EXECUTION DMA Channel is executed once for the current Linked-list
  */
hal_dma_linkedlist_execution_mode_t HAL_DMA_GetLinkedListXferExecutionMode(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  return ((hal_dma_linkedlist_execution_mode_t)LL_DMA_GetLinkStepMode(DMA_CHANNEL_GET_INSTANCE(hdma)));
}

/**
  * @brief  Set the DMA channel peripheral linked-list circular transfer configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_node            Pointer to hal_dma_node_t structure
  * @param  p_node_config     Pointer to hal_dma_direct_xfer_config_t structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when node or node_config pointer is NULL
  * @retval HAL_OK            Peripheral linked-list circular transfer is successfully configured
  */
hal_status_t HAL_DMA_SetConfigPeriphLinkedListCircularXfer(hal_dma_handle_t *hdma, hal_dma_node_t *p_node,
                                                           const hal_dma_direct_xfer_config_t *p_node_config)
{
  hal_dma_node_type_t              node_type;
  hal_dma_linkedlist_xfer_config_t p_config;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_node_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_REQUEST((uint32_t)p_node_config->request));
  ASSERT_DBG_PARAM(IS_DMA_DIRECTION((uint32_t)p_node_config->direction));
  ASSERT_DBG_PARAM(IS_DMA_SRC_INC((uint32_t)p_node_config->src_inc));
  ASSERT_DBG_PARAM(IS_DMA_DEST_INC((uint32_t)p_node_config->dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_SRC_DATA_WIDTH((uint32_t)p_node_config->src_data_width));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_WIDTH((uint32_t)p_node_config->dest_data_width));
  ASSERT_DBG_PARAM(IS_DMA_PRIORITY((uint32_t)p_node_config->priority));
  ASSERT_DBG_STATE(hdma->global_state, (uint32_t)HAL_DMA_STATE_INIT | (uint32_t)HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_node_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  node_type = DMA_GET_NODE_TYPE(hdma->instance);

  hdma->p_head_node = p_node;

  /* Set DMA channel linked-list transfer configuration */
  p_config.priority   = p_node_config->priority;
  p_config.xfer_event_mode = HAL_DMA_LINKEDLIST_XFER_EVENT_Q;
  p_config.fetch_port = HAL_DMA_PORT0;
  DMA_SetConfigLinkedListXfer(hdma, &p_config);

  /* Fill linked-list node for periph circular transfer */
  DMA_FillNodeDirectXfer(p_node, p_node_config, node_type, HAL_DMA_LINKEDLIST_XFER_EVENT_BLOCK);

  /* Set circular link for DMA node */
  p_node->regs[node_type] = (((uint32_t)p_node & DMA_CLLR_LA) | LL_DMA_UPDATE_ALL);

  hdma->xfer_mode = HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR;

  hdma->global_state = HAL_DMA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Get the DMA channel peripheral linked-list circular transfer configuration.
  * @param hdma          Pointer to DMA channel handle
  * @param p_node        Pointer to hal_dma_node_t structure
  * @param p_node_config Pointer to hal_dma_direct_xfer_config_t structure
  */
void HAL_DMA_GetConfigPeriphLinkedListCircularXfer(hal_dma_handle_t *hdma, hal_dma_node_t *p_node,
                                                   hal_dma_direct_xfer_config_t *p_node_config)
{
  hal_dma_linkedlist_xfer_config_t p_config;
  hal_dma_node_type_t              node_type;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_node_config != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  node_type = DMA_GET_NODE_TYPE(hdma->instance);

  /* Get the DMA channel configuration in linked-list mode */
  DMA_GetConfigLinkedListXfer(hdma, &p_config);

  /* Get the linked-list node for direct transfer */
  HAL_DMA_GetNodeDirectXfer(p_node, p_node_config, &node_type);

  /* Get the priority level for the linked-list node */
  p_node_config->priority = p_config.priority;
}
#endif /* USE_HAL_DMA_LINKEDLIST */
/**
  * @}
  */

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/** @addtogroup DMA_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to configure the DMA channel peripheral:

  Node configuration

- Call the function HAL_DMA_FillNodeConfig() to fill the node according to configured parameter within
  hal_dma_node_config_t structure

- Call the function HAL_DMA_GetNodeConfig() to get the current node configuration

  Direct transfer node configuration

- Call the function HAL_DMA_FillNodeDirectXfer() to fill the node direct transfer according to configured parameter
  within hal_dma_direct_xfer_config_t structure

- Call the function HAL_DMA_GetNodeDirectXfer() to get the current node direct transfer configuration

  Hardware request mode node configuration

- Call the function HAL_DMA_FillNodeHardwareRequestMode() to fill the node hardware request mode according to selected
  request mode parameter

- Call the function HAL_DMA_GetNodeHardwareRequestMode() to get the current node hardware request mode selection

  Port node configuration

- Call the function HAL_DMA_FillNodePort() to fill the node port according to selected port parameter

- Call the function HAL_DMA_GetNodePort() to get the current node port selection

  Burst node configuration

- Call the function HAL_DMA_FillNodeBurst() to fill the node burst according to selected burst parameter

- Call the function HAL_DMA_GetNodeBurst() to get the current node burst selection

  Transfer event mode node configuration

- Call the function HAL_DMA_FillNodeXferEventMode() to fill the node transfer event mode according to selected
  transfer event mode parameter

- Call the function HAL_DMA_GetNodeXferEventMode() to get the current node transfer event mode configuration

  Trigger node configuration

- Call the function HAL_DMA_FillNodeTrigger() to fill the node trigger according to configured trigger parameters

- Call the function HAL_DMA_GetNodeTrigger() to get the current node trigger configuration

  Data handling node configuration

- Call the function HAL_DMA_FillNodeDataHandling() to fill the node data handling according to configured data handling
  parameters

- Call the function HAL_DMA_GetNodeDataHandling() to get the current node data handling configuration

  Repeated block node configuration

- Call the function HAL_DMA_FillNodeRepeatBlock() to fill the node repeated block according to configured repeated block
  parameters

- Call the function HAL_DMA_GetNodeRepeatBlock() to get the current node repeated block configuration

  Security access attributes node configuration

- Call the function HAL_DMA_FillNodeAccessAttributes() to fill the node security access attributes according to
  configured security access attributes parameters

- Call the function HAL_DMA_GetNodeAccessAttributes() to get the current node security access attributes configuration

  Data node configuration

- Call the function HAL_DMA_FillNodeData() to fill the node data according to configured data parameters

- Call the function HAL_DMA_GetNodeData() to get the current node data configuration

  Conversion Q nodes

- Call the function HAL_DMA_ConvertQNodesToDynamic() to Convert linked-list queue associated to the handle to dynamic
  format

- Call the function HAL_DMA_ConvertQNodesToStatic() to Convert linked-list queue associated to the handle to static
  format
  */

/**
  * @brief  Fill node configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  p_conf            Pointer to hal_dma_node_config_t configuration structure
  * @param  node_type         Element in @ref hal_dma_node_type_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node or p_conf pointer is NULL
  * @retval HAL_OK            Fill node is successfully configured
  */
hal_status_t HAL_DMA_FillNodeConfig(hal_dma_node_t *p_node, const hal_dma_node_config_t *p_conf,
                                    hal_dma_node_type_t node_type)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_conf != NULL);
  ASSERT_DBG_PARAM(IS_DMA_REQUEST((uint32_t)p_conf->xfer.request));
  ASSERT_DBG_PARAM(IS_DMA_DIRECTION((uint32_t)p_conf->xfer.direction));
  ASSERT_DBG_PARAM(IS_DMA_SRC_INC((uint32_t)p_conf->xfer.src_inc));
  ASSERT_DBG_PARAM(IS_DMA_DEST_INC((uint32_t)p_conf->xfer.dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_SRC_DATA_WIDTH((uint32_t)p_conf->xfer.src_data_width));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_WIDTH((uint32_t)p_conf->xfer.dest_data_width));
  ASSERT_DBG_PARAM(IS_DMA_HARDWARE_REQUEST_MODE((uint32_t)p_conf->hw_request_mode));
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)p_conf->src_port));
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)p_conf->dest_port));
  ASSERT_DBG_PARAM((p_conf->src_burst_length_byte > 0U) && (p_conf->src_burst_length_byte <= 64U));
  ASSERT_DBG_PARAM((p_conf->dest_burst_length_byte > 0U) && (p_conf->dest_burst_length_byte <= 64U));
  ASSERT_DBG_PARAM(IS_DMA_LINKEDLIST_XFER_EVENT_MODE((uint32_t)p_conf->xfer_event_mode));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_SOURCE((uint32_t)p_conf->trigger.source));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_POLARITY((uint32_t)p_conf->trigger.polarity));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_MODE((uint32_t)p_conf->trigger.mode));
  ASSERT_DBG_PARAM(IS_DMA_SRC_BYTE_EXCHANGE((uint32_t)p_conf->data_handling.src_byte_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_BYTE_EXCHANGE((uint32_t)p_conf->data_handling.dest_byte_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_HALFWORD_EXCHANGE((uint32_t)p_conf->data_handling.dest_halfword_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_TRUNC_PADD((uint32_t)p_conf->data_handling.trunc_padd));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_PACK((uint32_t)p_conf->data_handling.pack));
  ASSERT_DBG_PARAM(p_conf->size_byte <= 0xFFFFU);

  if (node_type == HAL_DMA_NODE_2D_ADDRESSING)
  {
    ASSERT_DBG_PARAM(IS_DMA_BLOCK_COUNT((uint32_t)p_conf->repeat_block.block_count));
    ASSERT_DBG_PARAM(IS_DMA_BURST_SRC_OFFSET_BYTE((uint32_t)p_conf->repeat_block.burst_src_offset_byte));
    ASSERT_DBG_PARAM(IS_DMA_BURST_DEST_OFFSET_BYTE((uint32_t)p_conf->repeat_block.burst_dest_offset_byte));
    ASSERT_DBG_PARAM(IS_DMA_BLOCK_SRC_OFFSET_BYTE((uint32_t)p_conf->repeat_block.block_src_offset_byte));
    ASSERT_DBG_PARAM(IS_DMA_BLOCK_DEST_OFFSET_BYTE((uint32_t)p_conf->repeat_block.block_dest_offset_byte));
    ASSERT_DBG_PARAM(IS_DMA_BURST_SRC_INC((uint32_t)p_conf->repeat_block.burst_src_inc));
    ASSERT_DBG_PARAM(IS_DMA_BURST_DEST_INC((uint32_t)p_conf->repeat_block.burst_dest_inc));
    ASSERT_DBG_PARAM(IS_DMA_BLOCK_SRC_INC((uint32_t)p_conf->repeat_block.block_src_inc));
    ASSERT_DBG_PARAM(IS_DMA_BLOCK_DEST_INC((uint32_t)p_conf->repeat_block.block_dest_inc));
  }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  ASSERT_DBG_PARAM(IS_DMA_SEC_ATTR((uint32_t)p_conf->channel_src_sec));
  ASSERT_DBG_PARAM(IS_DMA_SEC_ATTR((uint32_t)p_conf->channel_dest_sec));
#endif /* __ARM_FEATURE_CMSE */

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_conf == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_FillNodeConfig(p_node, p_conf, node_type);

  return HAL_OK;
}

/**
  * @brief Get the configuration of node.
  * @param p_node      Pointer to hal_dma_node_t node structure
  * @param p_conf      Pointer to hal_dma_node_config_t configuration structure
  * @param p_node_type Element in @ref hal_dma_node_type_t enumeration
  */
void HAL_DMA_GetNodeConfig(const hal_dma_node_t *p_node, hal_dma_node_config_t *p_conf,
                           hal_dma_node_type_t *p_node_type)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_conf != NULL);

  DMA_GetConfigNode(p_node, p_conf, p_node_type);
}

/**
  * @brief  Fill node direct transfer configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  p_config          Pointer to hal_dma_direct_xfer_config_t configuration structure
  * @param  node_type         Element in @ref hal_dma_node_type_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node or p_config pointer is NULL
  * @retval HAL_OK            Fill node direct transfer is successfully configured
  */
hal_status_t HAL_DMA_FillNodeDirectXfer(hal_dma_node_t *p_node, const hal_dma_direct_xfer_config_t *p_config,
                                        hal_dma_node_type_t node_type)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_REQUEST((uint32_t)p_config->request));
  ASSERT_DBG_PARAM(IS_DMA_DIRECTION((uint32_t)p_config->direction));
  ASSERT_DBG_PARAM(IS_DMA_SRC_INC((uint32_t)p_config->src_inc));
  ASSERT_DBG_PARAM(IS_DMA_DEST_INC((uint32_t)p_config->dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_SRC_DATA_WIDTH((uint32_t)p_config->src_data_width));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_WIDTH((uint32_t)p_config->dest_data_width));
  ASSERT_DBG_PARAM(IS_DMA_PRIORITY((uint32_t)p_config->priority));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_FillNodeDirectXfer(p_node, p_config, node_type, HAL_DMA_LINKEDLIST_XFER_EVENT_Q);

  return HAL_OK;
}

/**
  * @brief Get the configuration of node direct transfer.
  * @param p_node      Pointer to hal_dma_node_t node structure
  * @param p_config    Pointer to hal_dma_direct_xfer_config_t configuration structure
  * @param p_node_type Element in @ref hal_dma_node_type_t enumeration
  */
void HAL_DMA_GetNodeDirectXfer(const hal_dma_node_t *p_node, hal_dma_direct_xfer_config_t *p_config,
                               hal_dma_node_type_t *p_node_type)
{
  hal_dma_node_config_t p_conf;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  DMA_GetConfigNode(p_node, &p_conf, p_node_type);

  p_config->request         = p_conf.xfer.request;
  p_config->direction       = p_conf.xfer.direction;
  p_config->src_inc         = p_conf.xfer.src_inc;
  p_config->dest_inc        = p_conf.xfer.dest_inc;
  p_config->src_data_width  = p_conf.xfer.src_data_width;
  p_config->dest_data_width = p_conf.xfer.dest_data_width;
}

/**
  * @brief  Fill node hardware request mode configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  hw_request_mode   Element in @ref hal_dma_hardware_request_mode_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node pointer is NULL
  * @retval HAL_OK            Fill node hardware request mode is successfully configured
  */
hal_status_t HAL_DMA_FillNodeHardwareRequestMode(hal_dma_node_t *p_node,
                                                 hal_dma_hardware_request_mode_t hw_request_mode)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(IS_DMA_HARDWARE_REQUEST_MODE((uint32_t)hw_request_mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR2_REG_OFFSET], DMA_CTR2_BREQ, (uint32_t)hw_request_mode);

  return HAL_OK;
}

/**
  * @brief  Get the configuration of node hardware request mode.
  * @param  p_node                         Pointer to hal_dma_node_t node structure
  * @retval HAL_DMA_HARDWARE_REQUEST_BURST DMA Channel hardware request mode is burst
  * @retval HAL_DMA_HARDWARE_REQUEST_BLOCK DMA Channel hardware request mode is block
  */
hal_dma_hardware_request_mode_t HAL_DMA_GetNodeHardwareRequestMode(const hal_dma_node_t *p_node)
{
  ASSERT_DBG_PARAM(p_node != NULL);

  return (hal_dma_hardware_request_mode_t)((uint32_t)(p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_BREQ));
}

/**
  * @brief  Fill node port configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  src_port          Element in @ref hal_dma_port_t enumeration
  * @param  dest_port         Element in @ref hal_dma_port_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node pointer is NULL
  * @retval HAL_OK            Fill node port is successfully configured
  */
hal_status_t HAL_DMA_FillNodePort(hal_dma_node_t *p_node, hal_dma_port_t src_port, hal_dma_port_t dest_port)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)src_port));
  ASSERT_DBG_PARAM(IS_DMA_PORT((uint32_t)dest_port));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR1_REG_OFFSET], (DMA_CTR1_SAP | DMA_CTR1_DAP),
             ((((uint32_t)src_port) << DMA_CTR1_SAP_Pos) & DMA_CTR1_SAP) |
             ((((uint32_t)dest_port) << DMA_CTR1_DAP_Pos) & DMA_CTR1_DAP));

  return HAL_OK;
}

/**
  * @brief Get the configuration of node port.
  * @param p_node      Pointer to hal_dma_node_t node structure
  * @param p_src_port  Element in @ref hal_dma_port_t enumeration
  * @param p_dest_port Element in @ref hal_dma_port_t enumeration
  */
void HAL_DMA_GetNodePort(const hal_dma_node_t *p_node, hal_dma_port_t *p_src_port, hal_dma_port_t *p_dest_port)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_src_port != NULL);
  ASSERT_DBG_PARAM(p_dest_port != NULL);

  dummy = (p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SAP) >> DMA_CTR1_SAP_Pos;
  *p_src_port = (hal_dma_port_t)dummy;
  dummy = (p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DAP) >> DMA_CTR1_DAP_Pos;
  *p_dest_port = (hal_dma_port_t)dummy;
}

/**
  * @brief  Fill node burst configuration.
  * @param  p_node                 Pointer to hal_dma_node_t node structure
  * @param  src_burst_length_byte  Source burst length in byte
  * @param  dest_burst_length_byte Source burst length in byte
  * @retval HAL_INVALID_PARAM      Invalid parameter return when p_node pointer is NULL
  * @retval HAL_OK                 Fill node burst is successfully configured
  */
hal_status_t HAL_DMA_FillNodeBurst(hal_dma_node_t *p_node, uint32_t src_burst_length_byte,
                                   uint32_t dest_burst_length_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM((src_burst_length_byte > 0U) && (src_burst_length_byte <= 64U));
  ASSERT_DBG_PARAM((dest_burst_length_byte > 0U) && (dest_burst_length_byte <= 64U));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR1_REG_OFFSET], (DMA_CTR1_SBL_1 | DMA_CTR1_DBL_1),
             ((src_burst_length_byte - 1U) << DMA_CTR1_SBL_1_Pos) |
             ((dest_burst_length_byte - 1U) << DMA_CTR1_DBL_1_Pos));

  return HAL_OK;
}

/**
  * @brief Get the configuration of node port.
  * @param p_node                   Pointer to hal_dma_node_t node structure
  * @param p_src_burst_length_byte  Source burst length in byte
  * @param p_dest_burst_length_byte Source burst length in byte
  */
void HAL_DMA_GetNodeBurst(const hal_dma_node_t *p_node,
                          uint32_t *p_src_burst_length_byte,
                          uint32_t *p_dest_burst_length_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_src_burst_length_byte != NULL);
  ASSERT_DBG_PARAM(p_dest_burst_length_byte != NULL);

  *p_src_burst_length_byte  =
    (uint32_t)(((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SBL_1) >> DMA_CTR1_SBL_1_Pos) + 1U);
  *p_dest_burst_length_byte =
    (uint32_t)(((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DBL_1) >> DMA_CTR1_DBL_1_Pos) + 1U);
}

/**
  * @brief  Fill node transfer event mode configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  xfer_event_mode   Element in @ref hal_dma_linkedlist_xfer_event_mode_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node is NULL
  * @retval HAL_OK            Fill node transfer event mode is successfully configured
  */
hal_status_t HAL_DMA_FillNodeXferEventMode(hal_dma_node_t *p_node, hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(IS_DMA_LINKEDLIST_XFER_EVENT_MODE((uint32_t)xfer_event_mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR2_REG_OFFSET], DMA_CTR2_TCEM, (uint32_t)xfer_event_mode);

  return HAL_OK;
}

/**
  * @brief Get the configuration of node transfer event mode.
  * @param p_node  Pointer to hal_dma_node_t node structure
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_BLOCK          DMA Channel transfer event mode is at block level.
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK DMA Channel transfer event mode is at repeated block level.
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_NODE           DMA Channel transfer event mode is at each linked-list item.
  * @retval HAL_DMA_LINKEDLIST_XFER_EVENT_Q              DMA Channel transfer event mode is at last linked-list item.
  */
hal_dma_linkedlist_xfer_event_mode_t HAL_DMA_GetNodeXferEventMode(const hal_dma_node_t *p_node)
{
  ASSERT_DBG_PARAM(p_node != NULL);

  return (hal_dma_linkedlist_xfer_event_mode_t)((uint32_t)(p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TCEM));
}

/**
  * @brief  Fill node trigger configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  p_config          Pointer to hal_dma_trigger_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node or p_config pointer is NULL
  * @retval HAL_OK            Fill node trigger is successfully configured
  */
hal_status_t HAL_DMA_FillNodeTrigger(hal_dma_node_t *p_node, const hal_dma_trigger_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_SOURCE((uint32_t)p_config->source));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_POLARITY((uint32_t)p_config->polarity));
  ASSERT_DBG_PARAM(IS_DMA_TRIGGER_MODE((uint32_t)p_config->mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR2_REG_OFFSET], (DMA_CTR2_TRIGM | DMA_CTR2_TRIGPOL | DMA_CTR2_TRIGSEL),
             (uint32_t)p_config->mode | (uint32_t)p_config->polarity |
             (((uint32_t)p_config->source << DMA_CTR2_TRIGSEL_Pos) & DMA_CTR2_TRIGSEL));

  return HAL_OK;
}

/**
  * @brief Get the configuration of node trigger.
  * @param p_node   Pointer to hal_dma_node_t node structure
  * @param p_config Pointer to hal_dma_trigger_config_t configuration structure
  */
void HAL_DMA_GetNodeTrigger(const hal_dma_node_t *p_node, hal_dma_trigger_config_t *p_config)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TRIGM;
  p_config->mode     = (hal_dma_trigger_mode_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TRIGPOL;
  p_config->polarity = (hal_dma_trigger_polarity_t)dummy;
  dummy = (p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TRIGSEL) >> DMA_CTR2_TRIGSEL_Pos;
  p_config->source   = (hal_dma_trigger_source_t)dummy;
}

/**
  * @brief  Fill node data handling configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  p_config          Pointer to hal_dma_data_handling_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node or p_config pointer is NULL
  * @retval HAL_OK            Fill node data handling is successfully configured
  */
hal_status_t HAL_DMA_FillNodeDataHandling(hal_dma_node_t *p_node, const hal_dma_data_handling_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_DMA_SRC_BYTE_EXCHANGE((uint32_t)p_config->src_byte_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_BYTE_EXCHANGE((uint32_t)p_config->dest_byte_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_HALFWORD_EXCHANGE((uint32_t)p_config->dest_halfword_exchange));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_TRUNC_PADD((uint32_t)p_config->trunc_padd));
  ASSERT_DBG_PARAM(IS_DMA_DEST_DATA_PACK((uint32_t)p_config->pack));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR1_REG_OFFSET],
             DMA_CTR1_SBX | DMA_CTR1_DBX | DMA_CTR1_DHX |
             DMA_CTR1_PAM,
             (uint32_t)p_config->src_byte_exchange      |
             (uint32_t)p_config->dest_byte_exchange     |
             (uint32_t)p_config->dest_halfword_exchange |
             (uint32_t)p_config->pack                   |
             (uint32_t)p_config->trunc_padd);

  return HAL_OK;
}

/**
  * @brief Get the configuration of node data handling.
  * @param p_node   Pointer to hal_dma_node_t node structure
  * @param p_config Pointer to hal_dma_data_handling_config_t configuration structure
  */
void HAL_DMA_GetNodeDataHandling(const hal_dma_node_t *p_node, hal_dma_data_handling_config_t *p_config)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SBX;
  p_config->src_byte_exchange = (hal_dma_src_byte_exchange_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DBX;
  p_config->dest_byte_exchange = (hal_dma_dest_byte_exchange_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DHX;
  p_config->dest_halfword_exchange = (hal_dma_dest_halfword_exchange_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_PAM_0;
  p_config->trunc_padd = (hal_dma_dest_data_trunc_padd_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_PAM_1;
  p_config->pack = (hal_dma_dest_data_pack_t)dummy;
}

/**
  * @brief  Fill node repeated block configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  p_config          Pointer to hal_dma_repeat_block_config_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node or p_config pointer is NULL
  * @retval HAL_OK            Fill node repeated block is successfully configured
  */
hal_status_t HAL_DMA_FillNodeRepeatBlock(hal_dma_node_t *p_node, const hal_dma_repeat_block_config_t *p_config)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_node->info == (uint32_t)HAL_DMA_NODE_2D_ADDRESSING);
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_COUNT((uint32_t)p_config->block_count));
  ASSERT_DBG_PARAM(IS_DMA_BURST_SRC_OFFSET_BYTE((uint32_t)p_config->burst_src_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BURST_DEST_OFFSET_BYTE((uint32_t)p_config->burst_dest_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_SRC_OFFSET_BYTE((uint32_t)p_config->block_src_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_DEST_OFFSET_BYTE((uint32_t)p_config->block_dest_offset_byte));
  ASSERT_DBG_PARAM(IS_DMA_BURST_SRC_INC((uint32_t)p_config->burst_src_inc));
  ASSERT_DBG_PARAM(IS_DMA_BURST_DEST_INC((uint32_t)p_config->burst_dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_SRC_INC((uint32_t)p_config->block_src_inc));
  ASSERT_DBG_PARAM(IS_DMA_BLOCK_DEST_INC((uint32_t)p_config->block_dest_inc));
  ASSERT_DBG_PARAM(IS_DMA_XFER_EVENT_MODE((uint32_t)p_config->xfer_event_mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_node == NULL) || (p_config == NULL) || (p_node->info != (uint32_t)HAL_DMA_NODE_2D_ADDRESSING))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  dummy = (((p_config->block_count - 1U) << DMA_CBR1_BRC_Pos) & DMA_CBR1_BRC) |
          (uint32_t)p_config->burst_src_inc                                   |
          (uint32_t)p_config->burst_dest_inc                                  |
          (uint32_t)p_config->block_src_inc                                   |
          (uint32_t)p_config->block_dest_inc;
  MODIFY_REG(p_node->regs[DMA_NODE_CBR1_REG_OFFSET],
             (DMA_CBR1_SDEC | DMA_CBR1_DDEC | DMA_CBR1_BRSDEC | DMA_CBR1_BRDDEC | DMA_CBR1_BRC),
             dummy);

  dummy = p_config->burst_src_offset_byte | ((p_config->burst_dest_offset_byte << DMA_CTR3_DAO_Pos) & DMA_CTR3_DAO);
  MODIFY_REG(p_node->regs[DMA_NODE_CTR3_REG_OFFSET], (DMA_CTR3_SAO | DMA_CTR3_DAO), dummy);

  dummy = p_config->block_src_offset_byte | ((p_config->block_dest_offset_byte << DMA_CBR2_BRDAO_Pos) & DMA_CBR2_BRDAO);
  WRITE_REG(p_node->regs[DMA_NODE_CBR2_REG_OFFSET], dummy);

  return HAL_OK;
}

/**
  * @brief Get the configuration of node repeated block.
  * @param p_node   Pointer to hal_dma_node_t node structure
  * @param p_config Pointer to hal_dma_repeat_block_config_t configuration structure
  */
void HAL_DMA_GetNodeRepeatBlock(const hal_dma_node_t *p_node, hal_dma_repeat_block_config_t *p_config)
{
  uint32_t dummy;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_node->info == (uint32_t)HAL_DMA_NODE_2D_ADDRESSING);

  p_config->block_count    = ((p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BRC) >> DMA_CBR1_BRC_Pos) + 1U;
  dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_SDEC;
  p_config->burst_src_inc  = (hal_dma_burst_src_increment_t)dummy;
  dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_DDEC;
  p_config->burst_dest_inc = (hal_dma_burst_dest_increment_t)dummy;
  dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BRSDEC;
  p_config->block_src_inc  = (hal_dma_block_src_increment_t)dummy;
  dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BRDDEC;
  p_config->block_dest_inc = (hal_dma_block_dest_increment_t)dummy;

  /* Get CTR3 field */
  p_config->burst_src_offset_byte  = p_node->regs[DMA_NODE_CTR3_REG_OFFSET] & DMA_CTR3_SAO;
  p_config->burst_dest_offset_byte = (p_node->regs[DMA_NODE_CTR3_REG_OFFSET] & DMA_CTR3_DAO) >> DMA_CTR3_DAO_Pos;

  /* Get CBR2 fields */
  p_config->block_src_offset_byte  = p_node->regs[DMA_NODE_CBR2_REG_OFFSET] & DMA_CBR2_BRSAO;
  p_config->block_dest_offset_byte = (p_node->regs[DMA_NODE_CBR2_REG_OFFSET] & DMA_CBR2_BRDAO) >> DMA_CBR2_BRDAO_Pos;
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Fill node access attributes.
  * @param  p_node            Pointer to hal_dma_node_t structure
  * @param  src_attr          Element in hal_dma_sec_attr_t enumeration
  * @param  dest_attr         Element in hal_dma_sec_attr_t enumeration
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node pointer is NULL
  * @retval HAL_OK            Fill node access attributes is successfully configured
  */
hal_status_t HAL_DMA_FillNodeAccessAttributes(hal_dma_node_t *p_node, hal_dma_sec_attr_t src_attr,
                                              hal_dma_sec_attr_t dest_attr)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(IS_DMA_SEC_ATTR((uint32_t)src_attr));
  ASSERT_DBG_PARAM(IS_DMA_SEC_ATTR((uint32_t)dest_attr));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  MODIFY_REG(p_node->regs[DMA_NODE_CTR1_REG_OFFSET], (DMA_CTR1_SSEC | DMA_CTR1_DSEC),
             (((uint32_t)src_attr * DMA_CTR1_SSEC) | ((uint32_t)dest_attr * DMA_CTR1_DSEC)));

  return HAL_OK;
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief Get node access attributes.
  * @param p_node      Pointer to hal_dma_node_t structure
  * @param p_src_attr  Pointer to hal_dma_sec_attr_t enumeration
  * @param p_dest_attr Pointer to hal_dma_sec_attr_t enumeration
  */
void HAL_DMA_GetNodeAccessAttributes(const hal_dma_node_t *p_node, hal_dma_sec_attr_t *p_src_attr,
                                     hal_dma_sec_attr_t *p_dest_attr)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_src_attr != NULL);
  ASSERT_DBG_PARAM(p_dest_attr != NULL);

  if ((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SSEC) != 0U)
  {
    *p_src_attr = HAL_DMA_ATTR_SEC;
  }
  else
  {
    *p_src_attr = HAL_DMA_ATTR_NSEC;
  }

  if ((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DSEC) != 0U)
  {
    *p_dest_attr = HAL_DMA_ATTR_SEC;
  }
  else
  {
    *p_dest_attr = HAL_DMA_ATTR_NSEC;
  }
}

/**
  * @brief  Fill node data configuration.
  * @param  p_node            Pointer to hal_dma_node_t node structure
  * @param  src_addr          Source address
  * @param  dest_addr         Destination address
  * @param  size_byte         Size in byte
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_node pointer is NULL
  * @retval HAL_OK            Fill node data is successfully configured
  */
hal_status_t HAL_DMA_FillNodeData(hal_dma_node_t *p_node, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM((size_byte > 0U) && (size_byte <= 0xFFFFU));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_node == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_UpdateDataNode(p_node, src_addr, dest_addr, size_byte);

  return HAL_OK;
}

/**
  * @brief Get the configuration of node data.
  * @param p_node      Pointer to hal_dma_node_t node structure
  * @param p_src_addr  Source address
  * @param p_dest_addr Destination address
  * @param p_size_byte Size in byte
  */
void HAL_DMA_GetNodeData(const hal_dma_node_t *p_node, uint32_t *p_src_addr, uint32_t *p_dest_addr,
                         uint32_t *p_size_byte)
{
  uint32_t *dummy;

  ASSERT_DBG_PARAM(p_node != NULL);
  ASSERT_DBG_PARAM(p_src_addr != NULL);
  ASSERT_DBG_PARAM(p_dest_addr != NULL);
  ASSERT_DBG_PARAM(p_size_byte != NULL);

  *p_size_byte = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BNDT;
  dummy  = p_src_addr;
  *dummy = p_node->regs[DMA_NODE_CSAR_REG_OFFSET];
  dummy  = p_dest_addr;
  *dummy = p_node->regs[DMA_NODE_CDAR_REG_OFFSET];
}

/**
  * @brief  Convert linked-list queue associated to the handle to dynamic format.
  * @param  p_q               Pointer to hal_q_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_q pointer is NULL
  * @retval HAL_OK            Q nodes to dynamic conversion is successfully configured
  */
hal_status_t HAL_DMA_ConvertQNodesToDynamic(hal_q_t *p_q)
{
  ASSERT_DBG_PARAM(p_q != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_ConvertQNodesToDynamic(p_q);

  return HAL_OK;
}

/**
  * @brief  Convert linked-list queue associated to the handle to static format.
  * @param  p_q               Pointer to hal_q_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_q pointer is NULL
  * @retval HAL_OK            Q nodes to static conversion is successfully configured
  */
hal_status_t HAL_DMA_ConvertQNodesToStatic(hal_q_t *p_q)
{
  ASSERT_DBG_PARAM(p_q != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  DMA_ConvertQNodesToStatic(p_q);

  return HAL_OK;
}
/**
  * @}
  */
#endif /* USE_HAL_DMA_LINKEDLIST */

/** @addtogroup DMA_Exported_Functions_Group4
  * @{

This subsection provides a set of functions allowing to configure the DMA channel peripheral:

- Call the function HAL_DMA_StartDirectXfer() to start direct DMA channel transfer in silent mode

- Call the function HAL_DMA_StartDirectXfer_IT() to start direct DMA channel transfer in interrupt mode
  with default optional interrupts configuration

- Call the function HAL_DMA_StartDirectXfer_IT_Opt() to start direct DMA channel transfer in interrupt mode
  with customized optional interrupts configuration

- Call the function HAL_DMA_StartLinkedListXfer() to start linked-list DMA channel transfer in silent mode

- Call the function HAL_DMA_StartLinkedListXfer_IT() to start linked-list DMA channel transfer in interrupt mode
  with default optional interrupts configuration

- Call the function HAL_DMA_StartLinkedListXfer_IT_Opt() to start linked-list DMA channel transfer in interrupt mode
  with customized optional interrupts configuration

- Call the function HAL_DMA_Abort() to abort any ongoing DMA channel transfer in blocking mode

- Call the function HAL_DMA_Abort_IT() to abort any ongoing DMA channel transfer in interrupt mode

- Call the function HAL_DMA_Suspend() to suspend any ongoing DMA channel transfer in blocking mode

- Call the function HAL_DMA_Suspend_IT() to suspend any ongoing DMA channel transfer in interrupt mode

- Call the function HAL_DMA_Resume() to resume any suspended DMA channel transfer instantly

- Call the function HAL_DMA_PollForXfer() to poll on any finite DMA channel transfer level selected through
  hal_dma_xfer_lvl_t

- Call the function HAL_DMA_IRQHandler() to handle any DMA channel interrupt. This API must executed in handler mode
  */

/**
  * @brief  Start the DMA channel direct transfer in silent mode.
  * @param  hdma              Pointer to DMA channel handle
  * @param  src_addr          Source address
  * @param  dest_addr         Destination address
  * @param  size_byte         Size in byte
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_BUSY          DMA channel state is active when calling this API
  * @retval HAL_OK            Silent direct transfer is successfully started
  */
hal_status_t HAL_DMA_StartDirectXfer(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM((size_byte > 0U) && (size_byte <= 0xFFFFU));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  DMA_StartDirectXfer(hdma, src_addr, dest_addr, size_byte, HAL_DMA_OPT_IT_SILENT);

  return HAL_OK;
}

/**
  * @brief  Start the DMA channel direct transfer in interrupt mode with default optional interrupts configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  src_addr          Source address
  * @param  dest_addr         Destination address
  * @param  size_byte         Size in byte
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_BUSY          DMA channel state is active when calling this API
  * @retval HAL_OK            Interrupt direct transfer is successfully started
  */
hal_status_t HAL_DMA_StartDirectXfer_IT(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr,
                                        uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM((size_byte > 0U) && (size_byte <= 0xFFFFU));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  DMA_StartDirectXfer(hdma, src_addr, dest_addr, size_byte, HAL_DMA_OPT_IT_DEFAULT);

  return HAL_OK;
}

/**
  * @brief  Start the DMA channel direct transfer in interrupt mode with customized optional interrupts configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  src_addr          Source address
  * @param  dest_addr         Destination address
  * @param  size_byte         Size in byte
  * @param  interrupts        Specifies the DMA optional interrupt to be enable.
  *                           This parameter can be one of @ref DMA_Optional_Interrupt group.
  * @retval HAL_INVALID_PARAM Invalid parameter return when transfer mode parameter is not direct
  * @retval HAL_BUSY          DMA channel state is active when calling this API
  * @retval HAL_OK            Interrupt direct transfer is successfully started
  */
hal_status_t HAL_DMA_StartDirectXfer_IT_Opt(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr,
                                            uint32_t size_byte, uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM((size_byte > 0U) && (size_byte <= 0xFFFFU));
  ASSERT_DBG_PARAM(IS_DMA_OPT_IT(interrupts));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode != HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  DMA_StartDirectXfer(hdma, src_addr, dest_addr, size_byte, interrupts);

  return HAL_OK;
}

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/**
  * @brief  Start the DMA channel linked-list transfer in silent mode.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_q               Pointer to hal_q_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_q pointer is NULL or transfer mode parameter is direct
  * @retval HAL_BUSY          DMA channel state is active when calling this API
  * @retval HAL_OK            Silent linked-list transfer is successfully started
  */
hal_status_t HAL_DMA_StartLinkedListXfer(hal_dma_handle_t *hdma, const hal_q_t *p_q)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  if (p_q->p_first_circular_node != NULL)
  {
    hdma->xfer_mode = HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR;
  }

  DMA_StartLinkedListXfer(hdma, p_q->p_head_node, HAL_DMA_OPT_IT_SILENT);

  return HAL_OK;
}

/**
  * @brief  Start the DMA channel linked-list transfer in interrupt mode with default optional interrupts configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_q               Pointer to hal_q_t configuration structure
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_q pointer is NULL or transfer mode parameter is direct
  * @retval HAL_BUSY          DMA channel state is active when calling this API
  * @retval HAL_OK            Interrupt linked-list transfer is successfully started
  */
hal_status_t HAL_DMA_StartLinkedListXfer_IT(hal_dma_handle_t *hdma, const hal_q_t *p_q)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  if (p_q->p_first_circular_node != NULL)
  {
    hdma->xfer_mode = HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR;
  }

  DMA_StartLinkedListXfer(hdma, p_q->p_head_node, HAL_DMA_OPT_IT_DEFAULT);

  return HAL_OK;
}

/**
  * @brief  Start the DMA channel linked-list transfer in interrupt mode with customized optional interrupts
  *         configuration.
  * @param  hdma              Pointer to DMA channel handle
  * @param  p_q               Pointer to hal_q_t configuration structure
  * @param  interrupts        Specifies the DMA optional interrupt to be enable.
  *                           This parameter can be one of @ref DMA_Optional_Interrupt group.
  * @retval HAL_INVALID_PARAM Invalid parameter return when p_q pointer is NULL or transfer mode parameter is direct
  * @retval HAL_BUSY          DMA channel state is active when calling this API
  * @retval HAL_OK            Interrupt linked-list transfer is successfully started
  */
hal_status_t HAL_DMA_StartLinkedListXfer_IT_Opt(hal_dma_handle_t *hdma, const hal_q_t *p_q, uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(p_q != NULL);
  ASSERT_DBG_PARAM(IS_DMA_OPT_IT(interrupts));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_q == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  hdma->last_error_codes = HAL_DMA_ERROR_NONE;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  if (p_q->p_first_circular_node != NULL)
  {
    hdma->xfer_mode = HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR;
  }

  DMA_StartLinkedListXfer(hdma, p_q->p_head_node, interrupts);

  return HAL_OK;
}
#endif /* USE_HAL_DMA_LINKEDLIST */

/**
  * @brief  Abort any ongoing DMA channel transfer in blocking mode.
  * @param  hdma      Pointer to DMA channel handle
  * @retval HAL_ERROR DMA channel not aborted
  * @retval HAL_OK    Transfer in blocking mode is successfully aborted
  */
hal_status_t HAL_DMA_Abort(hal_dma_handle_t *hdma)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, ((uint32_t)HAL_DMA_STATE_IDLE | (uint32_t)HAL_DMA_STATE_ACTIVE));

  if (LL_DMA_IsActiveFlag_IDLE(DMA_CHANNEL_GET_INSTANCE(hdma)) == 0U)
  {
    hdma->global_state = HAL_DMA_STATE_ABORT;

    LL_DMA_SuspendChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

    tickstart = HAL_GetTick();
    while (LL_DMA_IsActiveFlag_SUSP(DMA_CHANNEL_GET_INSTANCE(hdma)) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > DMA_SUSPEND_TIMEOUT)
      {
        if (LL_DMA_IsActiveFlag_IDLE(DMA_CHANNEL_GET_INSTANCE(hdma)) != 0U)
        {
          LL_DMA_ResetChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

          hdma->global_state = HAL_DMA_STATE_IDLE;
        }

        return HAL_ERROR;
      }
    }

    LL_DMA_ResetChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

    LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_ALL);

    hdma->global_state = HAL_DMA_STATE_IDLE;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Abort any ongoing DMA channel transfer in interrupt mode.
  * @param  hdma      Pointer to DMA channel handle
  * @retval HAL_ERROR DMA channel not aborted
  * @retval HAL_OK    Transfer in interrupt mode is successfully aborted
  */
hal_status_t HAL_DMA_Abort_IT(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, (uint32_t)HAL_DMA_STATE_IDLE | (uint32_t)HAL_DMA_STATE_ACTIVE);

  if (LL_DMA_IsActiveFlag_IDLE(DMA_CHANNEL_GET_INSTANCE(hdma)) == 0U)
  {
    hdma->global_state = HAL_DMA_STATE_ABORT;

    LL_DMA_EnableIT_SUSP(DMA_CHANNEL_GET_INSTANCE(hdma));

    LL_DMA_SuspendChannel(DMA_CHANNEL_GET_INSTANCE(hdma));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Suspend any ongoing DMA channel transfer in blocking mode.
  * @param  hdma      Pointer to DMA channel handle
  * @retval HAL_ERROR DMA channel not suspended
  * @retval HAL_OK    Transfer in blocking mode is successfully suspended
  */
hal_status_t HAL_DMA_Suspend(hal_dma_handle_t *hdma)
{
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_ACTIVE);

  if (LL_DMA_IsActiveFlag_IDLE(DMA_CHANNEL_GET_INSTANCE(hdma)) == 0U)
  {
    hdma->global_state = HAL_DMA_STATE_SUSPEND;

    LL_DMA_SuspendChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

    tickstart = HAL_GetTick();
    while (LL_DMA_IsActiveFlag_SUSP(DMA_CHANNEL_GET_INSTANCE(hdma)) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > DMA_SUSPEND_TIMEOUT)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Suspend any ongoing DMA channel transfer in interrupt mode.
  * @param  hdma      Pointer to DMA channel handle
  * @retval HAL_ERROR DMA channel not suspended
  * @retval HAL_OK    Transfer in interrupt mode is successfully suspended
  */
hal_status_t HAL_DMA_Suspend_IT(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_ACTIVE);

  if (LL_DMA_IsActiveFlag_IDLE(DMA_CHANNEL_GET_INSTANCE(hdma)) == 0U)
  {
    hdma->global_state = HAL_DMA_STATE_SUSPEND;

    LL_DMA_EnableIT_SUSP(DMA_CHANNEL_GET_INSTANCE(hdma));

    LL_DMA_SuspendChannel(DMA_CHANNEL_GET_INSTANCE(hdma));
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Resume instantantly any suspended DMA channel transfer.
  * @param  hdma     Pointer to DMA channel handle
  * @retval HAL_BUSY DMA channel state is active when calling this API
  * @retval HAL_OK   Transfer is successfully resumed
  */
hal_status_t HAL_DMA_Resume(hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_SUSPEND);

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_SUSPEND, HAL_DMA_STATE_ACTIVE);

  LL_DMA_ResumeChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

  return HAL_OK;
}

/**
  * @brief  Polling for transfer status for finite DMA channel silent transfers.
  * @param  hdma         Pointer to DMA channel handle
  * @param  xfer_level   Specifies the DMA channel transfer level
  * @param  timeout_msec Specifies the user timeout in milli-second
  * @retval HAL_TIMEOUT  User timeout
  * @retval HAL_ERROR    DMA channel error
  * @retval HAL_OK       Polling for transfer is successfully configured
  */
hal_status_t HAL_DMA_PollForXfer(hal_dma_handle_t *hdma, hal_dma_xfer_level_t xfer_level, uint32_t timeout_msec)
{
  uint32_t tickstart;
  uint32_t tmp_csr;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(IS_DMA_XFER_LEVEL((uint32_t)xfer_level));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
#endif /* USE_HAL_DMA_LINKEDLIST */

  tmp_csr = LL_DMA_READ_REG((DMA_CHANNEL_GET_INSTANCE(hdma)), CSR);

  if ((tmp_csr & LL_DMA_FLAG_TO) != 0U)
  {
#if defined(USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
    hdma->last_error_codes |= HAL_DMA_ERROR_TO;
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

    LL_DMA_ClearFlag_TO(DMA_CHANNEL_GET_INSTANCE(hdma));
  }

  /* Wait for transfer level */
  tickstart = HAL_GetTick();
  while ((LL_DMA_READ_REG((DMA_CHANNEL_GET_INSTANCE(hdma)), CSR) & (uint32_t)xfer_level) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > timeout_msec)
    {
      (void)HAL_DMA_Abort(hdma);

      return HAL_TIMEOUT;
    }
  }

#if defined(USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  /* Check the data transfer error flag */
  if ((tmp_csr & LL_DMA_FLAG_DTE) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_DTE;
  }

  /* Check the user setting error flag */
  if ((tmp_csr & LL_DMA_FLAG_USE) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_USE;
  }

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check the update link error flag */
  if ((tmp_csr & LL_DMA_FLAG_ULE) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_ULE;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  if ((tmp_csr & HAL_DMA_FLAG_ERROR) != 0U)
  {
    LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_ALL);

    LL_DMA_ResetChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

    hdma->global_state = HAL_DMA_STATE_IDLE;

    return HAL_ERROR;
  }

  /* Clear transfer level flags */
  if (xfer_level == HAL_DMA_XFER_HALF_COMPLETE)
  {
    LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_HT);
  }
  else
  {
    LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), (LL_DMA_FLAG_TC | LL_DMA_FLAG_HT));
  }

  hdma->global_state = HAL_DMA_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Handle any DMA channel interrupt.
  * @param hdma Pointer to DMA channel handle
  */
void HAL_DMA_IRQHandler(hal_dma_handle_t *hdma)
{
  DMA_TypeDef *instance;
  uint32_t    flags;
  uint32_t    its;
  uint32_t    channel;

  ASSERT_DBG_PARAM(hdma != NULL);

  instance = LL_DMA_GET_INSTANCE(hdma->instance);
  channel  = LL_DMA_GET_CHANNEL_IDX(hdma->instance);
  its      = LL_DMA_READ_REG((DMA_CHANNEL_GET_INSTANCE(hdma)), CCR);

  /* Check DMA channel active interrupts */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if (LL_DMA_IsActiveFlag_SMIS(instance, channel) == 0U)
#endif /* __ARM_FEATURE_CMSE */
  {
    if (LL_DMA_IsActiveFlag_MIS(instance, channel) == 0U)
    {
      return; /* the global interrupt flag for the current channel is down , nothing to do */
    }
  }

  flags = LL_DMA_READ_REG((DMA_CHANNEL_GET_INSTANCE(hdma)), CSR);

  /* Half Transfer Complete Interrupt management **********************************************************************/
  if (READ_BIT((flags & its), LL_DMA_FLAG_HT) != 0U)
  {
    LL_DMA_ClearFlag_HT(DMA_CHANNEL_GET_INSTANCE(hdma));

    hdma->p_xfer_halfcplt_cb(hdma);

    if (READ_BIT((flags & its), LL_DMA_FLAG_TC) == 0U)
    {
      return;
    }
  }

  /* Transfer Complete Interrupt management ***************************************************************************/
  if (READ_BIT((flags & its), LL_DMA_FLAG_TC) != 0U)
  {
    LL_DMA_ClearFlag_TC(DMA_CHANNEL_GET_INSTANCE(hdma));

    /* Check if there are remaining data */
    if (LL_DMA_IsActiveFlag_IDLE(DMA_CHANNEL_GET_INSTANCE(hdma)) != 0U)
    {
      LL_DMA_ClearFlag_HT(DMA_CHANNEL_GET_INSTANCE(hdma));

      LL_DMA_DisableIT(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_IT_ALL);

      hdma->global_state = HAL_DMA_STATE_IDLE;
    }

    hdma->p_xfer_cplt_cb(hdma);

    return;
  }

  /* Suspend Transfer Interrupt management ****************************************************************************/
  if (READ_BIT((flags & its), LL_DMA_FLAG_SUSP) != 0U)
  {
    LL_DMA_ClearFlag_SUSP(DMA_CHANNEL_GET_INSTANCE(hdma));

    if (hdma->global_state == HAL_DMA_STATE_ABORT)
    {
      LL_DMA_ResetChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

      LL_DMA_DisableIT(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_IT_ALL);

      hdma->global_state = HAL_DMA_STATE_IDLE;

      hdma->p_xfer_abort_cb(hdma);
    }
    else
    {
      LL_DMA_DisableIT_SUSP(DMA_CHANNEL_GET_INSTANCE(hdma));

      hdma->global_state = HAL_DMA_STATE_SUSPEND;

      hdma->p_xfer_suspend_cb(hdma);
    }

    return;
  }

  /* Error Interrupt management ***************************************************************************************/
  DMA_HandleErrorIT(hdma, READ_BIT((flags & its), (HAL_DMA_FLAG_ERROR | LL_DMA_FLAG_TO)));
}
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group5
  * @{

This subsection provides a set of functions allowing to register the DMA channel process and error callbacks:

- Call the function HAL_DMA_RegisterXferHalfCpltCallback() to register the DMA channel half transfer complete callback

- Call the function HAL_DMA_RegisterXferCpltCallback() to register the DMA channel transfer complete callback

- Call the function HAL_DMA_RegisterXferAbortCallback() to register the DMA channel abort callback

- Call the function HAL_DMA_RegisterXferSuspendCallback() to register the DMA channel suspend callback

- Call the function HAL_DMA_RegisterXferErrorCallback() to register the DMA channel error callback

- Call the function HAL_DMA_SetUserData() to set a user data in handle

- Call the function HAL_DMA_GetUserData() to get a user data from handle
  */

/**
  * @brief  Store the given callback into the DMA handle.
  * @param  hdma              Pointer to DMA channel handle
  * @param  callback          Specifies the half transfer complete callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK            DMA channel half transfer complete callback is successfully stored
  */
hal_status_t HAL_DMA_RegisterXferHalfCpltCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma->p_xfer_halfcplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Store the given callback into the DMA handle.
  * @param  hdma              Pointer to DMA channel handle
  * @param  callback          Specifies the transfer complete callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK            DMA channel transfer complete callback is successfully stored
  */
hal_status_t HAL_DMA_RegisterXferCpltCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma->p_xfer_cplt_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Store the given callback into the DMA handle.
  * @param  hdma              Pointer to DMA channel handle
  * @param  callback          Specifies the abort callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK            DMA channel abort transfer callback is successfully stored
  */
hal_status_t HAL_DMA_RegisterXferAbortCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma->p_xfer_abort_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Store the given callback into the DMA handle.
  * @param  hdma              Pointer to DMA channel handle
  * @param  callback          Specifies the suspend callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK            DMA channel suspend transfer callback is successfully stored
  */
hal_status_t HAL_DMA_RegisterXferSuspendCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma->p_xfer_suspend_cb = callback;

  return HAL_OK;
}

/**
  * @brief  Store the given callback into the DMA handle.
  * @param  hdma              Pointer to DMA channel handle
  * @param  callback          Specifies the error callback
  * @retval HAL_INVALID_PARAM Invalid parameter return when callback pointer is NULL
  * @retval HAL_OK            DMA channel error transfer callback is successfully stored
  */
hal_status_t HAL_DMA_RegisterXferErrorCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hdma->p_xfer_error_cb = callback;

  return HAL_OK;
}

/**
  * @brief DMA channel half transfer complete default callback.
  * @param hdma Pointer to DMA channel handle
  */
__WEAK void HAL_DMA_XferHalfCpltCallback(hal_dma_handle_t *hdma)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma);

  /*! <b>NOTE:</b> This is a weak function and must not be modified, when the callback is needed, the
                   HAL_DMA_RegisterXferHalfCpltCallback() must be implemented in the user file */
}

/**
  * @brief DMA channel transfer complete default callback.
  * @param hdma Pointer to DMA channel handle
  */
__WEAK void HAL_DMA_XferCpltCallback(hal_dma_handle_t *hdma)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma);

  /*! <b>NOTE:</b> This is a weak function and must not be modified, when the callback is needed, the
                   HAL_DMA_RegisterXferCpltCallback() must be implemented in the user file */
}

/**
  * @brief DMA channel abort default callback.
  * @param hdma Pointer to DMA channel handle
  */
__WEAK void HAL_DMA_XferAbortCallback(hal_dma_handle_t *hdma)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma);

  /*! <b>NOTE:</b> This is a weak function and must not be modified, when the callback is needed, the
                   HAL_DMA_RegisterXferAbortCallback() must be implemented in the user file */
}

/**
  * @brief DMA channel suspend default callback.
  * @param hdma Pointer to DMA channel handle
  */
__WEAK void HAL_DMA_XferSuspendCallback(hal_dma_handle_t *hdma)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma);

  /*! <b>NOTE:</b> This is a weak function and must not be modified, when the callback is needed, the
                   HAL_DMA_RegisterXferSuspendCallback() must be implemented in the user file */
}

/**
  * @brief DMA channel suspend default callback.
  * @param hdma Pointer to DMA channel handle
  */
__WEAK void HAL_DMA_XferErrorCallback(hal_dma_handle_t *hdma)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hdma);

  /*! <b>NOTE:</b> This is a weak function and must not be modified, when the callback is needed, the
                   HAL_DMA_RegisterXferErrorCallback() must be implemented in the user file */
}

#if defined(USE_HAL_DMA_USER_DATA) && (USE_HAL_DMA_USER_DATA == 1)
/**
  * @brief Store the user data into the DMA channel handle.
  * @param hdma        Pointer to DMA channel handle
  * @param p_user_data Pointer to the user data
  */
void HAL_DMA_SetUserData(hal_dma_handle_t *hdma, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hdma != NULL);

  hdma->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data from the DMA channel handle.
  * @param  hdma Pointer to DMA channel handle
  * @retval Pointer to the user data
  */
const void *HAL_DMA_GetUserData(const hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);

  return (hdma->p_user_data);
}
#endif /* USE_HAL_DMA_USER_DATA */
/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group6
  * @{

This subsection provides a set of functions allowing to get the DMA channel data information and status:

- Call the function HAL_DMA_GetFifoDataByte() to get the DMA channel the FIFO when available in byte

- Call the function HAL_DMA_GetDirectXferRemainingDataByte() to get the DMA channel remaining data within the current
  transfer in byte

- Call the function HAL_DMA_GetState() to get the DMA channel current state

- Call the function HAL_DMA_GetLastErrorCodes() to get the DMA channel last errors codes
  */

/**
  * @brief  Get the DMA channel remaining data in the FIFO in byte.
  * @param  hdma     Pointer to DMA channel handle
  * @retval uint32_t FIFO remaining data in byte
  */
uint32_t HAL_DMA_GetFifoDataByte(const hal_dma_handle_t *hdma)
{
  uint32_t dest_data_width;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state,
                   (uint32_t)HAL_DMA_STATE_IDLE | (uint32_t)HAL_DMA_STATE_ACTIVE | (uint32_t)HAL_DMA_STATE_SUSPEND);

  dest_data_width =
    1UL << (LL_DMA_GetDestDataWidth(DMA_CHANNEL_GET_INSTANCE(hdma)) >> (DMA_CTR1_DDW_LOG2_Pos - 1U));

  return (LL_DMA_GetFIFOLevel(DMA_CHANNEL_GET_INSTANCE(hdma)) * dest_data_width);
}

/**
  * @brief  Get the DMA channel remaining data in the current transfer in byte.
  * @param  hdma     Pointer to DMA channel handle
  * @retval uint32_t Direct transfer remaining data in byte
  */
uint32_t HAL_DMA_GetDirectXferRemainingDataByte(const hal_dma_handle_t *hdma)
{
  uint32_t dest_data_width;

  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_STATE(hdma->global_state,
                   (uint32_t)HAL_DMA_STATE_IDLE | (uint32_t)HAL_DMA_STATE_ACTIVE | (uint32_t)HAL_DMA_STATE_SUSPEND);

  dest_data_width = 1UL << (LL_DMA_GetDestDataWidth(DMA_CHANNEL_GET_INSTANCE(hdma)) >> DMA_CTR1_DDW_LOG2_Pos);

  return (LL_DMA_GetBlkDataLength(DMA_CHANNEL_GET_INSTANCE(hdma))
          + (LL_DMA_GetFIFOLevel(DMA_CHANNEL_GET_INSTANCE(hdma)) * dest_data_width)
          + (LL_DMA_GetBlkRptCount(DMA_CHANNEL_GET_INSTANCE(hdma)) * (hdma->block_size_byte))
         );
}

/**
  * @brief  Get the DMA channel current state.
  * @param  hdma            Pointer to DMA channel handle
  * @retval hal_dma_state_t DMA channel state
  */
hal_dma_state_t HAL_DMA_GetState(const hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);

  return (hdma->global_state);
}

#if defined (USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
/**
  * @brief  Get last error codes.
  * @param  hdma     Pointer to DMA channel handle
  * @retval uint32_t Last error codes which can be a combination of @ref DMA_Error_Code
  */
uint32_t HAL_DMA_GetLastErrorCodes(const hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hdma != NULL);

  return (hdma->last_error_codes);
}
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */
/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup DMA_Private_Functions
  * @{
  */

/**
  * @brief Set the DMA channel transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_direct_xfer_config_t configuration structure
  */
static void DMA_SetConfigDirectXfer(hal_dma_handle_t *hdma, const hal_dma_direct_xfer_config_t *p_config)
{
  LL_DMA_SetChannelPriorityLevel(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_config->priority);
  LL_DMA_ConfigTransfer(DMA_CHANNEL_GET_INSTANCE(hdma),
                        ((uint32_t)p_config->dest_inc | (uint32_t)p_config->dest_data_width |
                         (uint32_t)p_config->src_inc  | (uint32_t)p_config->src_data_width));

  if (p_config->direction != HAL_DMA_DIRECTION_MEMORY_TO_MEMORY)
  {
    LL_DMA_SetPeriphRequest(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_config->request);
  }

  LL_DMA_SetDataTransferDirection(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_config->direction);
  LL_DMA_SetHWRequestMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)HAL_DMA_HARDWARE_REQUEST_BURST);
}

/**
  * @brief Get the DMA channel transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_direct_xfer_config_t configuration structure
  */
static void DMA_GetConfigDirectXfer(hal_dma_handle_t *hdma, hal_dma_direct_xfer_config_t *p_config)
{
  p_config->request         = (hal_dma_request_source_t)LL_DMA_GetPeriphRequest(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->direction       = (hal_dma_direction_t)LL_DMA_GetDataTransferDirection(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->src_inc         = (hal_dma_src_addr_increment_t)LL_DMA_GetSrcIncMode(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->dest_inc        = (hal_dma_dest_addr_increment_t)LL_DMA_GetDestIncMode(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->src_data_width  = (hal_dma_src_data_width_t)LL_DMA_GetSrcDataWidth(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->dest_data_width = (hal_dma_dest_data_width_t)LL_DMA_GetDestDataWidth(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->priority        = (hal_dma_priority_t)LL_DMA_GetChannelPriorityLevel(DMA_CHANNEL_GET_INSTANCE(hdma));
}

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/**
  * @brief Set the DMA channel linked-list transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_linkedlist_xfer_config_t configuration structure
  */
static void DMA_SetConfigLinkedListXfer(hal_dma_handle_t *hdma, const hal_dma_linkedlist_xfer_config_t *p_config)
{
  uint32_t dummy = (uint32_t)p_config->fetch_port << DMA_CCR_LAP_Pos;

  LL_DMA_ConfigControl(DMA_CHANNEL_GET_INSTANCE(hdma), ((uint32_t)p_config->priority | dummy));
  LL_DMA_SetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_config->xfer_event_mode);
  LL_DMA_SetBlkDataLength(DMA_CHANNEL_GET_INSTANCE(hdma), 0U);
}

/**
  * @brief Get the DMA channel linked-list transfer configuration.
  * @param hdma     Pointer to DMA channel handle
  * @param p_config Pointer to hal_dma_linkedlist_xfer_config_t configuration structure
  */
static void DMA_GetConfigLinkedListXfer(hal_dma_handle_t *hdma, hal_dma_linkedlist_xfer_config_t *p_config)
{
  uint32_t dummy;

  dummy = LL_DMA_GetLinkAllocatedPort(DMA_CHANNEL_GET_INSTANCE(hdma)) >> DMA_CCR_LAP_Pos;
  p_config->fetch_port = (hal_dma_port_t)dummy;
  p_config->priority = (hal_dma_priority_t)LL_DMA_GetChannelPriorityLevel(DMA_CHANNEL_GET_INSTANCE(hdma));
  p_config->xfer_event_mode = (hal_dma_linkedlist_xfer_event_mode_t)
                              LL_DMA_GetTransferEventMode(DMA_CHANNEL_GET_INSTANCE(hdma));
}

/**
  * @brief Fill the DMA channel linked-list node configuration.
  * @param p_conf    Pointer to hal_q_dma_node_config_t configuration structure
  * @param p_node    Pointer to hal_dma_node_t node structure
  * @param node_type Element in @ref hal_dma_node_type_t enumeration
  */
static void DMA_FillNodeConfig(hal_dma_node_t *p_node, const hal_dma_node_config_t *p_conf,
                               hal_dma_node_type_t node_type)
{
  uint32_t idx   = 0U;
  uint32_t dummy;

  /* Update CTR1 register value */
  dummy = (uint32_t)p_conf->xfer.src_inc | (uint32_t)p_conf->xfer.dest_inc | (uint32_t)p_conf->xfer.src_data_width |
          (uint32_t)p_conf->xfer.dest_data_width |
          (uint32_t)p_conf->data_handling.pack |
          (((uint32_t)p_conf->src_port << DMA_CTR1_SAP_Pos) & DMA_CTR1_SAP) |
          (((uint32_t)p_conf->dest_port << DMA_CTR1_DAP_Pos) & DMA_CTR1_DAP) |
          (uint32_t)p_conf->data_handling.src_byte_exchange | (uint32_t)p_conf->data_handling.dest_byte_exchange |
          (uint32_t)p_conf->data_handling.dest_halfword_exchange |
          ((p_conf->src_burst_length_byte - 1U) << DMA_CTR1_SBL_1_Pos)  |
          ((p_conf->dest_burst_length_byte - 1U) << DMA_CTR1_DBL_1_Pos) |
          (uint32_t)p_conf->data_handling.trunc_padd;

  WRITE_REG(p_node->regs[idx], dummy);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  MODIFY_REG(p_node->regs[idx], DMA_CTR1_SSEC | DMA_CTR1_DSEC,
             (((uint32_t)p_conf->channel_src_sec  << DMA_CTR1_SSEC_Pos) |
              ((uint32_t)p_conf->channel_dest_sec << DMA_CTR1_DSEC_Pos)));
#endif /* __ARM_FEATURE_CMSE */

  idx++;

  /* Update CTR2 register value */
  dummy = (uint32_t)p_conf->hw_request_mode                                     |
          (uint32_t)p_conf->xfer_event_mode                                     |
          (uint32_t)p_conf->xfer.direction                                      |
          ((uint32_t)p_conf->xfer.request & (DMA_CTR2_REQSEL | DMA_CTR2_SWREQ)) |
          (uint32_t)p_conf->trigger.mode                                        |
          (uint32_t)p_conf->trigger.polarity                                    |
          (((uint32_t)p_conf->trigger.source << DMA_CTR2_TRIGSEL_Pos) & DMA_CTR2_TRIGSEL);

  WRITE_REG(p_node->regs[idx], dummy);

  idx++;

  /* Update CBR1 register value */
  WRITE_REG(p_node->regs[idx], (uint32_t)(p_conf->size_byte & DMA_CBR1_BNDT));

  /* If 2D addressing is supported by the selected DMA channel */
  if (node_type == HAL_DMA_NODE_2D_ADDRESSING)
  {
    /* Set the new CBR1 Register value */
    dummy = (((p_conf->repeat_block.block_count - 1U) << DMA_CBR1_BRC_Pos) & DMA_CBR1_BRC) |
            (uint32_t)p_conf->repeat_block.burst_src_inc                                   |
            (uint32_t)p_conf->repeat_block.burst_dest_inc                                  |
            (uint32_t)p_conf->repeat_block.block_src_inc                                   |
            (uint32_t)p_conf->repeat_block.block_dest_inc;

    MODIFY_REG(p_node->regs[idx],
               (DMA_CBR1_SDEC | DMA_CBR1_DDEC | DMA_CBR1_BRSDEC | DMA_CBR1_BRDDEC | DMA_CBR1_BRC),
               dummy);
  }

  idx++;

  /* Update CSAR register value */
  p_node->regs[idx] = (uint32_t)p_conf->src_addr;

  idx++;

  /* Update CDAR register value */
  p_node->regs[idx] = (uint32_t)p_conf->dest_addr;

  idx++;

  /* Check if the selected channel is 2D addressing */
  if (node_type == HAL_DMA_NODE_2D_ADDRESSING)
  {
    /* Update CTR3 register value */
    dummy = p_conf->repeat_block.burst_src_offset_byte |
            ((p_conf->repeat_block.burst_dest_offset_byte << DMA_CTR3_DAO_Pos) & DMA_CTR3_DAO);

    WRITE_REG(p_node->regs[idx], dummy);

    idx++;

    /* Update CBR2 register value */
    dummy = p_conf->repeat_block.block_src_offset_byte |
            ((p_conf->repeat_block.block_dest_offset_byte << DMA_CBR2_BRDAO_Pos) & DMA_CBR2_BRDAO);

    WRITE_REG(p_node->regs[idx], dummy);

    idx++;

    /* Reset CLLR register value */
    WRITE_REG(p_node->regs[idx], 0U);
  }
  else
  {
    /* Reset CLLR register value */
    WRITE_REG(p_node->regs[idx], 0U);
  }

  /* Set node type */
  p_node->info = (uint32_t)node_type;
}

/**
  * @brief Get node configuration of DMA channel linked-list.
  * @param p_node      Pointer to hal_dma_node_t node structure
  * @param p_conf      Pointer to hal_q_dma_node_config_t configuration structure
  * @param p_node_type Pointer to @ref hal_dma_node_type_t enumeration
  */
static void DMA_GetConfigNode(const hal_dma_node_t *p_node, hal_dma_node_config_t *p_conf,
                              hal_dma_node_type_t *p_node_type)
{
  uint32_t dummy;

  /* Get node type */
  *p_node_type = (hal_dma_node_type_t)p_node->info;

  /* Get CTR1 fields values */
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SINC;
  p_conf->xfer.src_inc = (hal_dma_src_addr_increment_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DINC;
  p_conf->xfer.dest_inc = (hal_dma_dest_addr_increment_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SDW_LOG2;
  p_conf->xfer.src_data_width = (hal_dma_src_data_width_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DDW_LOG2;
  p_conf->xfer.dest_data_width = (hal_dma_dest_data_width_t)dummy;
  p_conf->src_burst_length_byte =
    (uint32_t)(((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SBL_1) >> DMA_CTR1_SBL_1_Pos) + 1U);
  p_conf->dest_burst_length_byte =
    (uint32_t)(((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DBL_1) >> DMA_CTR1_DBL_1_Pos) + 1U);
  dummy = (p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SAP) >> DMA_CTR1_SAP_Pos;
  p_conf->src_port = (hal_dma_port_t)dummy;
  dummy = (p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DAP) >> DMA_CTR1_DAP_Pos;
  p_conf->dest_port = (hal_dma_port_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SBX;
  p_conf->data_handling.src_byte_exchange = (hal_dma_src_byte_exchange_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DBX;
  p_conf->data_handling.dest_byte_exchange = (hal_dma_dest_byte_exchange_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DHX;
  p_conf->data_handling.dest_halfword_exchange = (hal_dma_dest_halfword_exchange_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_PAM_0;
  p_conf->data_handling.trunc_padd = (hal_dma_dest_data_trunc_padd_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_PAM_1;
  p_conf->data_handling.pack = (hal_dma_dest_data_pack_t)dummy;

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if ((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_SSEC) != 0U)
  {
    p_conf->channel_src_sec = HAL_DMA_ATTR_SEC;
  }
  else
  {
    p_conf->channel_src_sec = HAL_DMA_ATTR_NSEC;
  }

  if ((p_node->regs[DMA_NODE_CTR1_REG_OFFSET] & DMA_CTR1_DSEC) != 0U)
  {
    p_conf->channel_dest_sec = HAL_DMA_ATTR_SEC;
  }
  else
  {
    p_conf->channel_dest_sec = HAL_DMA_ATTR_NSEC;
  }
#endif /* __ARM_FEATURE_CMSE */

  /* Get CTR2 fields values */
  if ((p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_SWREQ) != 0U)
  {
    p_conf->xfer.request   = HAL_DMA_REQUEST_SW;
    p_conf->xfer.direction = HAL_DMA_DIRECTION_MEMORY_TO_MEMORY;
  }
  else
  {
    dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_REQSEL;
    p_conf->xfer.request = (hal_dma_request_source_t)dummy;

    if ((p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_DREQ) != 0U)
    {
      p_conf->xfer.direction = HAL_DMA_DIRECTION_MEMORY_TO_PERIPH;
    }
    else
    {
      p_conf->xfer.direction = HAL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    }
  }

  dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_BREQ;
  p_conf->hw_request_mode = (hal_dma_hardware_request_mode_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TRIGM;
  p_conf->trigger.mode = (hal_dma_trigger_mode_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TRIGPOL;
  p_conf->trigger.polarity = (hal_dma_trigger_polarity_t)dummy;
  dummy = (p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TRIGSEL) >> DMA_CTR2_TRIGSEL_Pos;
  p_conf->trigger.source = (hal_dma_trigger_source_t)dummy;
  dummy = p_node->regs[DMA_NODE_CTR2_REG_OFFSET] & DMA_CTR2_TCEM;
  p_conf->xfer_event_mode = (hal_dma_linkedlist_xfer_event_mode_t)dummy;

  /* Get CBR1 fields */
  p_conf->size_byte = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BNDT;
  if (*p_node_type == HAL_DMA_NODE_2D_ADDRESSING)
  {
    p_conf->repeat_block.block_count    =
      ((p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BRC) >> DMA_CBR1_BRC_Pos) + 1U;
    dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_SDEC;
    p_conf->repeat_block.burst_src_inc  = (hal_dma_burst_src_increment_t)dummy;
    dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_DDEC;
    p_conf->repeat_block.burst_dest_inc = (hal_dma_burst_dest_increment_t)dummy;
    dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BRSDEC;
    p_conf->repeat_block.block_src_inc  = (hal_dma_block_src_increment_t)dummy;
    dummy = p_node->regs[DMA_NODE_CBR1_REG_OFFSET] & DMA_CBR1_BRDDEC;
    p_conf->repeat_block.block_dest_inc = (hal_dma_block_dest_increment_t)dummy;
  }

  /* Get CSAR field */
  p_conf->src_addr  = p_node->regs[DMA_NODE_CSAR_REG_OFFSET];

  /* Get CDAR field */
  p_conf->dest_addr = p_node->regs[DMA_NODE_CDAR_REG_OFFSET];

  if (*p_node_type == HAL_DMA_NODE_2D_ADDRESSING)
  {
    /* Get CTR3 field */
    p_conf->repeat_block.burst_src_offset_byte  = p_node->regs[DMA_NODE_CTR3_REG_OFFSET] & DMA_CTR3_SAO;

    p_conf->repeat_block.burst_dest_offset_byte =
      (p_node->regs[DMA_NODE_CTR3_REG_OFFSET] & DMA_CTR3_DAO) >> DMA_CTR3_DAO_Pos;

    /* Get CBR2 fields */
    p_conf->repeat_block.block_src_offset_byte  = p_node->regs[DMA_NODE_CBR2_REG_OFFSET] & DMA_CBR2_BRSAO;

    p_conf->repeat_block.block_dest_offset_byte =
      (p_node->regs[DMA_NODE_CBR2_REG_OFFSET] & DMA_CBR2_BRDAO) >> DMA_CBR2_BRDAO_Pos;
  }

  STM32_UNUSED(dummy);
}

/**
  * @brief Fill the DMA channel linked-list node direct transfer.
  * @param p_node          Pointer to hal_dma_node_t configuration structure
  * @param p_config        Pointer to hal_dma_direct_xfer_config_t node structure
  * @param node_type       Element in @ref hal_dma_node_type_t enumeration
  * @param xfer_event_mode Element in @ref hal_dma_linkedlist_xfer_event_mode_t enumeration
  */
static void DMA_FillNodeDirectXfer(hal_dma_node_t *p_node, const hal_dma_direct_xfer_config_t *p_config,
                                   hal_dma_node_type_t node_type, hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode)
{

  hal_dma_node_config_t p_conf;

  /* Set direct xfer config */
  p_conf.xfer.request                         = p_config->request;
  p_conf.hw_request_mode                      = HAL_DMA_HARDWARE_REQUEST_BURST;
  p_conf.xfer.direction                       = p_config->direction;
  p_conf.xfer.src_inc                         = p_config->src_inc;
  p_conf.xfer.dest_inc                        = p_config->dest_inc;
  p_conf.xfer.src_data_width                  = p_config->src_data_width;
  p_conf.xfer.dest_data_width                 = p_config->dest_data_width;
  p_conf.src_port                             = HAL_DMA_PORT0;
  p_conf.dest_port                            = HAL_DMA_PORT1;
  p_conf.src_burst_length_byte                = 1U;
  p_conf.dest_burst_length_byte               = 1U;
  p_conf.xfer_event_mode                      = xfer_event_mode;
  p_conf.trigger.source                       = HAL_GPDMA1_TRIGGER_EXTI0;
  p_conf.trigger.mode                         = HAL_DMA_TRIGGER_SINGLE_BURST_TRANSFER;
  p_conf.trigger.polarity                     = HAL_DMA_TRIGGER_POLARITY_MASKED;
  p_conf.data_handling.src_byte_exchange      = HAL_DMA_SRC_BYTE_PRESERVED;
  p_conf.data_handling.dest_byte_exchange     = HAL_DMA_DEST_BYTE_PRESERVED;
  p_conf.data_handling.dest_halfword_exchange = HAL_DMA_DEST_HALFWORD_PRESERVED;
  p_conf.data_handling.trunc_padd             = HAL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO;
  p_conf.data_handling.pack                   = HAL_DMA_DEST_DATA_PRESERVED;
  p_conf.repeat_block.block_count             = 1U;
  p_conf.repeat_block.burst_src_inc           = HAL_DMA_BURST_SRC_ADDR_INCREMENTED;
  p_conf.repeat_block.burst_src_offset_byte   = 0U;
  p_conf.repeat_block.burst_dest_inc          = HAL_DMA_BURST_DEST_ADDR_INCREMENTED;
  p_conf.repeat_block.burst_dest_offset_byte  = 0U;
  p_conf.repeat_block.block_src_inc           = HAL_DMA_BLOCK_SRC_ADDR_INCREMENTED;
  p_conf.repeat_block.block_src_offset_byte   = 0U;
  p_conf.repeat_block.block_dest_inc          = HAL_DMA_BLOCK_DEST_ADDR_INCREMENTED;
  p_conf.repeat_block.block_dest_offset_byte  = 0U;
  p_conf.src_addr                             = 0U;
  p_conf.dest_addr                            = 0U;
  p_conf.size_byte                            = 0U;

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  p_conf.channel_src_sec                      = HAL_DMA_ATTR_SEC;
  p_conf.channel_dest_sec                     = HAL_DMA_ATTR_SEC;
#endif /* __ARM_FEATURE_CMSE */

  DMA_FillNodeConfig(p_node, &p_conf, node_type);
}

/**
  * @brief Update the DMA channel linked-list node.
  * @param p_node    Pointer to hal_dma_node_t node structure
  * @param src_addr  Source address
  * @param dest_addr Destination address
  * @param size_byte Size in byte
  */
static void DMA_UpdateDataNode(hal_dma_node_t *p_node, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte)
{
  p_node->regs[DMA_NODE_CBR1_REG_OFFSET] = size_byte;
  p_node->regs[DMA_NODE_CSAR_REG_OFFSET] = src_addr;
  p_node->regs[DMA_NODE_CDAR_REG_OFFSET] = dest_addr;
}

/**
  * @brief Convert linked-list queue associated to the handle to dynamic format.
  * @param p_q Pointer to hal_q_t configuration structure
  */
static void DMA_ConvertQNodesToDynamic(hal_q_t *p_q)
{
  uint32_t cllr_offset;
  uint32_t currentnode_position = 0U;
  uint32_t currentnode_address  = 0U;

  uint32_t currentnode_addr;
  hal_dma_node_t context_node;

  cllr_offset = ((hal_dma_node_t *)(p_q->p_head_node))->info;

  /* Check queue circularity */
  if (p_q->p_first_circular_node != 0U)
  {
    /* Check that previous node is linked to the selected queue */
    while (currentnode_position < p_q->node_nbr)
    {
      /* Get head node address */
      if (currentnode_position == 0U)
      {
        currentnode_address = (uint32_t)p_q->p_head_node & DMA_CLLR_LA;
      }
      /* Calculate nodes addresses */
      else
      {
        currentnode_address =
          ((hal_dma_node_t *)(currentnode_address + ((uint32_t)p_q->p_head_node & DMA_CLBAR_LBA)))->regs[cllr_offset] &
          DMA_CLLR_LA;
      }

      currentnode_position++;
    }

    currentnode_address = currentnode_address | ((uint32_t)p_q->p_head_node & DMA_CLBAR_LBA);
  }

  currentnode_addr = (uint32_t)p_q->p_head_node;

  /* Store register value */
  for (uint32_t reg_idx = 0U; reg_idx < DMA_NODE_REGISTER_NUM; reg_idx++)
  {
    context_node.regs[reg_idx] = ((hal_dma_node_t *)p_q->p_head_node)->regs[reg_idx];
  }

  context_node.info = ((hal_dma_node_t *)p_q->p_head_node)->info;

  /* Convert all nodes to dyncamic (Bypass head node) */
  for (uint32_t node_count = 1U; node_count < p_q->node_nbr; node_count++)
  {
    MODIFY_REG(currentnode_addr, DMA_CLLR_LA, (context_node.regs[cllr_offset] & DMA_CLLR_LA));

    /* Bypass the first circular node when first circular node is not the last queue node */
    if (((uint32_t)p_q->p_first_circular_node != 0U)
        && ((uint32_t)p_q->p_first_circular_node != currentnode_address)
        && ((uint32_t)p_q->p_first_circular_node == currentnode_addr))
    {
      /* Copy first circular node to context node */
      for (uint32_t reg_idx = 0U; reg_idx < DMA_NODE_REGISTER_NUM; reg_idx++)
      {
        context_node.regs[reg_idx] = ((hal_dma_node_t *)p_q->p_first_circular_node)->regs[reg_idx];
      }

      context_node.info = ((hal_dma_node_t *)p_q->p_first_circular_node)->info;
    }
    else
    {
      DMA_List_ConvertNodeToDynamic((uint32_t)&context_node, currentnode_addr, (cllr_offset + 1U));
    }
  }

  /* Check if first circular node is the last node queue */
  if (((uint32_t)p_q->p_first_circular_node != 0U)
      && ((uint32_t)p_q->p_first_circular_node != currentnode_address))
  {
    DMA_List_UpdateDynamicQueueNodesCLLR(p_q, DMA_LASTNODE_ISNOT_CIRCULAR);
  }
  else
  {
    DMA_List_UpdateDynamicQueueNodesCLLR(p_q, DMA_LASTNODE_IS_CIRCULAR);
  }
}

/**
  * @brief Convert linked-list queue associated to the handle to static format.
  * @param p_q Pointer to hal_q_t configuration structure
  */
static void DMA_ConvertQNodesToStatic(hal_q_t *p_q)
{
  uint32_t cllr_offset;
  uint32_t currentnode_addr;
  hal_dma_node_t context_node;

  currentnode_addr = (uint32_t)p_q->p_head_node;

  cllr_offset = ((hal_dma_node_t *)(p_q->p_head_node))->info;

  DMA_List_UpdateStaticQueueNodesCLLR(p_q, DMA_UPDATE_CLLR_POSITION);

  /* Convert all nodes to static (Bypass head node) */
  for (uint32_t node_count = 1U; node_count < p_q->node_nbr; node_count++)
  {
    /* Update context node register values */
    for (uint32_t reg_idx = 0U; reg_idx < DMA_NODE_REGISTER_NUM; reg_idx++)
    {
      context_node.regs[reg_idx] = ((hal_dma_node_t *)currentnode_addr)->regs[reg_idx];
    }

    context_node.info = ((hal_dma_node_t *)currentnode_addr)->info;

    MODIFY_REG(currentnode_addr, DMA_CLLR_LA, (context_node.regs[cllr_offset] & DMA_CLLR_LA));

    DMA_List_ConvertNodeToStatic((uint32_t)&context_node, currentnode_addr, (cllr_offset + 1U));
  }

  DMA_List_UpdateStaticQueueNodesCLLR(p_q, DMA_UPDATE_CLLR_VALUE);
}

/**
  * @brief Convert node to dynamic.
  * @param context_node_addr The context node address
  * @param current_node_addr The current node address to be converted
  * @param reg_nbr           The register number to be converted
  */
static void DMA_List_ConvertNodeToDynamic(uint32_t context_node_addr, uint32_t current_node_addr, uint32_t reg_nbr)
{
  uint32_t currentnode_reg_counter = 0U;
  uint32_t contextnode_reg_counter = 0U;
  uint32_t cllr_idx = reg_nbr - 1U;
  uint32_t update_link[DMA_NODE_REGISTER_NUM] = {DMA_CLLR_UT1, DMA_CLLR_UT2, DMA_CLLR_UB1, DMA_CLLR_USA,
                                                 DMA_CLLR_UDA, DMA_CLLR_UT3, DMA_CLLR_UB2, DMA_CLLR_ULL
                                                };
  hal_dma_node_t *context_node = (hal_dma_node_t *)context_node_addr;
  hal_dma_node_t *current_node = (hal_dma_node_t *)current_node_addr;

  /* Update ULL position according to register number */
  update_link[cllr_idx] = update_link[DMA_NODE_REGISTER_NUM - 1U];

  /* Repeat for all node registers */
  while (contextnode_reg_counter != reg_nbr)
  {
    /* Check if register values are equal (exception for CSAR, CDAR and CLLR registers) */
    if ((context_node->regs[contextnode_reg_counter]  == current_node->regs[currentnode_reg_counter])
        && (contextnode_reg_counter != DMA_NODE_CSAR_DEFAULT_OFFSET)
        && (contextnode_reg_counter != (reg_nbr - 1U)))
    {
      DMA_List_FormatNode(current_node, currentnode_reg_counter, reg_nbr, DMA_NODE_DYNAMIC_FORMAT);

      cllr_idx --;

      current_node->regs[cllr_idx] &= ~update_link[contextnode_reg_counter];
    }
    else
    {
      context_node->regs[contextnode_reg_counter] = current_node->regs[currentnode_reg_counter];

      current_node->regs[cllr_idx] |= update_link[contextnode_reg_counter];

      currentnode_reg_counter++;
    }

    contextnode_reg_counter++;
  }

  MODIFY_REG(current_node->info, DMA_NODE_CLLR_IDX, ((currentnode_reg_counter - 1U) << DMA_NODE_CLLR_IDX_POS));

  DMA_List_ClearUnusedFields(current_node, currentnode_reg_counter);
}

/**
  * @brief Convert node to static.
  * @param context_node_addr The context node address.
  * @param current_node_addr The current node address to be converted.
  * @param reg_nbr           The register number to be converted.
  */
static void DMA_List_ConvertNodeToStatic(uint32_t context_node_addr, uint32_t current_node_addr, uint32_t reg_nbr)
{
  hal_dma_node_t *context_node = (hal_dma_node_t *)context_node_addr;
  hal_dma_node_t *current_node = (hal_dma_node_t *)current_node_addr;
  uint32_t contextnode_reg_counter = 0U;
  uint32_t update_link[DMA_NODE_REGISTER_NUM] = {DMA_CLLR_UT1, DMA_CLLR_UT2, DMA_CLLR_UB1, DMA_CLLR_USA,
                                                 DMA_CLLR_UDA, DMA_CLLR_UT3, DMA_CLLR_UB2, DMA_CLLR_ULL
                                                };
  uint32_t cllr_mask;
  uint8_t  cllr_idx;

  /* Update ULL position according to register number */
  update_link[reg_nbr - 1U] = update_link[DMA_NODE_REGISTER_NUM - 1U];

  /* Get context node CLLR information */
  cllr_idx  = (uint8_t)context_node->info & 0x7U;
  current_node->info = cllr_idx;
  cllr_mask = (uint32_t)context_node->regs[cllr_idx];

  while (contextnode_reg_counter != reg_nbr)
  {
    /* Check if node field is dynamic */
    if ((cllr_mask & update_link[contextnode_reg_counter]) == 0U)
    {
      DMA_List_FormatNode(current_node, contextnode_reg_counter, reg_nbr, DMA_NODE_STATIC_FORMAT);

      current_node->regs[contextnode_reg_counter] = context_node->regs[contextnode_reg_counter];
    }

    contextnode_reg_counter++;
  }
}

/**
  * @brief Update CLLR for all dynamic queue nodes.
  * @param p_q                   Pointer to a hal_q_t structure that contains queue information
  * @param last_node_is_circular The first circular node is the last queue node or not
  */
static void DMA_List_UpdateDynamicQueueNodesCLLR(const hal_q_t *p_q, uint32_t last_node_is_circular)
{
  uint32_t previous_cllr_offset;
  uint32_t current_cllr_offset = 0U;
  uint32_t previousnode_addr;
  uint32_t currentnode_addr = (uint32_t)p_q->p_head_node;
  uint32_t cllr_mask = LL_DMA_UPDATE_ALL;
  uint32_t node_idx = 0U;

  /*  Repeat for all register nodes */
  while (node_idx < p_q->node_nbr)
  {
    /* Get head node address */
    if (node_idx == 0U)
    {
      current_cllr_offset = ((hal_dma_node_t *)currentnode_addr)->info;
    }
    /* Calculate nodes addresses */
    else
    {
      previousnode_addr = currentnode_addr;
      previous_cllr_offset = current_cllr_offset;

      currentnode_addr = (((hal_dma_node_t *)(previousnode_addr))->regs[previous_cllr_offset] & DMA_CLLR_LA) +
                         ((uint32_t)p_q->p_head_node & DMA_CLBAR_LBA);
      if ((((hal_dma_node_t *)currentnode_addr)->info == (uint32_t)HAL_DMA_NODE_2D_ADDRESSING)
          || (((hal_dma_node_t *)currentnode_addr)->info == (uint32_t)HAL_DMA_NODE_LINEAR_ADDRESSING))
      {
        current_cllr_offset = ((hal_dma_node_t *)currentnode_addr)->info;
      }
      else
      {
        current_cllr_offset = (((hal_dma_node_t *)currentnode_addr)->info >> 8U);
      }

      cllr_mask = (((hal_dma_node_t *)currentnode_addr)->regs[current_cllr_offset] & ~DMA_CLLR_LA) |
                  (((hal_dma_node_t *)(previousnode_addr))->regs[previous_cllr_offset] & DMA_CLLR_LA);

      ((hal_dma_node_t *)(previousnode_addr))->regs[previous_cllr_offset] = cllr_mask;
    }

    node_idx++;
  }

  /* Check queue circularity */
  if (p_q->p_first_circular_node != 0U)
  {
    /* First circular queue is not last queue node */
    if (last_node_is_circular == 0U)
    {
      DMA_List_GetCLLRNodeInfo(((hal_dma_node_t *)currentnode_addr), &cllr_mask, NULL);

      ((hal_dma_node_t *)currentnode_addr)->regs[current_cllr_offset] =
        ((uint32_t)p_q->p_first_circular_node & DMA_CLLR_LA) | cllr_mask;
    }
    /* First circular queue is last queue node */
    else
    {
      /* Disable CLLR updating */
      ((hal_dma_node_t *)currentnode_addr)->regs[current_cllr_offset] &= ~DMA_CLLR_ULL;
    }
  }
  else
  {
    /* Clear CLLR register for last node */
    ((hal_dma_node_t *)currentnode_addr)->regs[current_cllr_offset] = 0U;
  }
}

/**
  * @brief Update CLLR for all static queue nodes.
  * @param p_q       Pointer to a hal_q_t structure that contains queue information
  * @param operation The operation type
  */
static void DMA_List_UpdateStaticQueueNodesCLLR(hal_q_t *p_q, uint32_t operation)
{
  uint32_t currentnode_addr = (uint32_t)p_q->p_head_node;
  uint32_t current_cllr_offset = (uint32_t)((hal_dma_node_t *)p_q->p_head_node)->info;
  uint32_t cllr_default_offset;
  uint32_t cllr_default_mask;
  uint32_t cllr_mask;
  uint32_t node_idx = 0U;

  DMA_List_GetCLLRNodeInfo((const hal_dma_node_t *)p_q->p_head_node, &cllr_default_mask, &cllr_default_offset);

  /*  Repeat for all register nodes (Bypass last queue node) */
  while (node_idx < p_q->node_nbr)
  {
    if (operation == DMA_UPDATE_CLLR_POSITION)
    {
      cllr_mask = ((hal_dma_node_t *)currentnode_addr)->regs[current_cllr_offset];
    }
    else
    {
      cllr_mask = (((hal_dma_node_t *)currentnode_addr)->regs[((hal_dma_node_t *)currentnode_addr)->info] &
                   DMA_CLLR_LA) | cllr_default_mask;
    }

    /* Set new CLLR value to default position */
    if ((node_idx == (p_q->node_nbr - 1U)) && (p_q->p_first_circular_node == NULL))
    {
      ((hal_dma_node_t *)(currentnode_addr))->regs[cllr_default_offset] = 0U;
    }
    else
    {
      ((hal_dma_node_t *)(currentnode_addr))->regs[cllr_default_offset] = cllr_mask;
    }

    currentnode_addr = (currentnode_addr & DMA_CLBAR_LBA) | (cllr_mask & DMA_CLLR_LA);

    /* Update current CLLR offset with next CLLR offset */
    if ((((hal_dma_node_t *)currentnode_addr)->info == (uint32_t)HAL_DMA_NODE_2D_ADDRESSING)
        || (((hal_dma_node_t *)currentnode_addr)->info == (uint32_t)HAL_DMA_NODE_LINEAR_ADDRESSING))
    {
      current_cllr_offset = ((hal_dma_node_t *)currentnode_addr)->info;
    }
    else
    {
      current_cllr_offset = (((hal_dma_node_t *)currentnode_addr)->info >> 8U);
    }

    node_idx++;
  }
}

/**
  * @brief Check nodes types compatibility.
  * @param p_node        Pointer to a hal_dma_node_t structure that contains linked-list node registers configurations
  * @param p_cllr_mask   Pointer to CLLR register mask value
  * @param p_cllr_offset Pointer to CLLR register offset value
  */
static void DMA_List_GetCLLRNodeInfo(const hal_dma_node_t *p_node, uint32_t *p_cllr_mask, uint32_t *p_cllr_offset)
{
  if ((p_node->info & (uint32_t)HAL_DMA_NODE_2D_ADDRESSING) == (uint32_t)HAL_DMA_NODE_2D_ADDRESSING)
  {
    *p_cllr_mask = DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_UT3 |
                   DMA_CLLR_UB2 | DMA_CLLR_ULL;

    if (p_cllr_offset != NULL)
    {
      *p_cllr_offset = (uint32_t)HAL_DMA_NODE_2D_ADDRESSING;
    }
  }
  else
  {
    *p_cllr_mask = DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_ULL;

    if (p_cllr_offset != NULL)
    {
      *p_cllr_offset = (uint32_t)HAL_DMA_NODE_LINEAR_ADDRESSING;
    }
  }
}

/**
  * @brief Format the node according to unused registers.
  * @param p_node  Pointer to a DMA_NodeTypeDef structure that contains linked-list node registers configurations
  * @param reg_idx The first register index to be formatted
  * @param reg_nbr The number of node registers
  * @param format  The format type
  */
static void DMA_List_FormatNode(hal_dma_node_t *p_node, uint32_t reg_idx, uint32_t reg_nbr, uint32_t format)
{
  if (format == DMA_NODE_DYNAMIC_FORMAT)
  {
    for (uint32_t reg_id = reg_idx; reg_id < (reg_nbr - 1U); reg_id++)
    {
      p_node->regs[reg_id] = p_node->regs[reg_id + 1U];
    }
  }
  else
  {
    for (uint32_t reg_id = (reg_nbr - 2U); reg_id > reg_idx; reg_id--)
    {
      p_node->regs[reg_id] = p_node->regs[reg_id - 1U];
    }
  }
}

/**
  * @brief Clear unused register fields.
  * @param p_node             Pointer to a hal_dma_node_t structure that contains linked-list node registers
  *                           configurations
  * @param first_unused_field The first unused field to be cleared
  */
static void DMA_List_ClearUnusedFields(hal_dma_node_t *p_node, uint32_t first_unused_field)
{
  for (uint32_t reg_idx = first_unused_field; reg_idx < DMA_NODE_REGISTER_NUM; reg_idx++)
  {
    p_node->regs[reg_idx] = 0U;
  }
}

#endif /* USE_HAL_DMA_LINKEDLIST */

/**
  * @brief Start the DMA channel direct transfer.
  * @param hdma       Pointer to DMA channel handle
  * @param src_addr   Source address
  * @param dest_addr  Destination address
  * @param size_byte  Size in byte
  * @param interrupts Specifies the DMA optional interrupt to be enable.
  *                   This parameter can be one of @ref DMA_Optional_Interrupt group.
  */
static void DMA_StartDirectXfer(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte,
                                uint32_t interrupts)
{
  hdma->block_size_byte = size_byte;

  LL_DMA_ConfigAddresses(DMA_CHANNEL_GET_INSTANCE(hdma), src_addr, dest_addr);
  LL_DMA_SetBlkDataLength(DMA_CHANNEL_GET_INSTANCE(hdma), size_byte);

  LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_ALL);

  LL_DMA_DisableIT(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_IT_ALL);

  if (interrupts != HAL_DMA_OPT_IT_SILENT)
  {
    LL_DMA_EnableIT(DMA_CHANNEL_GET_INSTANCE(hdma), (LL_DMA_IT_TC  | LL_DMA_IT_DTE | LL_DMA_IT_ULE | LL_DMA_IT_USE |
                                                     interrupts));
  }

  LL_DMA_ConfigLinkUpdate(DMA_CHANNEL_GET_INSTANCE(hdma), 0U, 0U);

  LL_DMA_EnableChannel(DMA_CHANNEL_GET_INSTANCE(hdma));
}

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/**
  * @brief Start the DMA channel linked-list transfer.
  * @param hdma        Pointer to DMA channel handle
  * @param p_head_node Pointer to hal_q_t node structure
  * @param interrupts Specifies the DMA optional interrupt to be enable.
  *                   This parameter can be one of @ref DMA_Optional_Interrupt group.
  */
static void DMA_StartLinkedListXfer(hal_dma_handle_t *hdma, const void *p_head_node, uint32_t interrupts)
{
  const hal_dma_node_t *head_node = (const hal_dma_node_t *)p_head_node;
  uint32_t head_node_info = head_node->info;

  uint32_t update_bits = LL_DMA_UPDATE_CTR1 | LL_DMA_UPDATE_CTR2 | LL_DMA_UPDATE_CBR1 |
                         LL_DMA_UPDATE_CSAR | LL_DMA_UPDATE_CDAR | LL_DMA_UPDATE_CLLR;

  if (head_node_info == (uint32_t)HAL_DMA_NODE_2D_ADDRESSING)
  {
    update_bits |= LL_DMA_UPDATE_CBR2 | LL_DMA_UPDATE_CTR3;
  }

  LL_DMA_SetLinkedListBaseAddr(DMA_CHANNEL_GET_INSTANCE(hdma), (uint32_t)p_head_node);

  LL_DMA_ConfigLinkUpdate(DMA_CHANNEL_GET_INSTANCE(hdma), update_bits, ((uint32_t)p_head_node & DMA_CLLR_LA));

  LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_ALL);

  LL_DMA_DisableIT(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_IT_ALL);

  if (interrupts != HAL_DMA_OPT_IT_SILENT)
  {
    LL_DMA_EnableIT(DMA_CHANNEL_GET_INSTANCE(hdma), (LL_DMA_IT_TC  | LL_DMA_IT_DTE | LL_DMA_IT_ULE | LL_DMA_IT_USE |
                                                     interrupts));
  }

  LL_DMA_SetBlkDataLength(DMA_CHANNEL_GET_INSTANCE(hdma), 0U);

  LL_DMA_EnableChannel(DMA_CHANNEL_GET_INSTANCE(hdma));
}
#endif /* USE_HAL_DMA_LINKEDLIST */

/**
  * @brief  Handle the DMA channel error interrupt.
  * @param  hdma      Pointer to DMA channel handle
  * @param  error_msk Mask of errors flags
  */
static void DMA_HandleErrorIT(hal_dma_handle_t *hdma, uint32_t error_msk)
{
#if defined(USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  /* Check the data transfer error flag */
  if ((error_msk & LL_DMA_FLAG_DTE) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_DTE;
  }

  /* Check the user setting error flag */
  if ((error_msk & LL_DMA_FLAG_USE) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_USE;
  }

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Check the update link error flag */
  if ((error_msk & LL_DMA_FLAG_ULE) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_ULE;
  }
#endif /* USE_HAL_DMA_LINKEDLIST */

  /* Check trigger overrun flag */
  if ((error_msk & LL_DMA_FLAG_TO) != 0U)
  {
    hdma->last_error_codes |= HAL_DMA_ERROR_TO;
  }
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

  LL_DMA_ClearFlag(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_FLAG_ALL);

  hdma->p_xfer_error_cb(hdma);

  /* Check error flags */
  if ((error_msk & HAL_DMA_FLAG_ERROR) != 0U)
  {
    LL_DMA_ResetChannel(DMA_CHANNEL_GET_INSTANCE(hdma));

    LL_DMA_DisableIT(DMA_CHANNEL_GET_INSTANCE(hdma), LL_DMA_IT_ALL);

    hdma->global_state = HAL_DMA_STATE_IDLE;
  }
}

/**
  * @brief  Start the DMA channel peripheral transfer.
  * @param  hdma       Pointer to DMA channel handle
  * @param  src_addr   Source address
  * @param  dest_addr  Destination address
  * @param  size_byte  Size in byte
  * @param  interrupts Specifies the DMA optional interrupts to be enabled.
  *                    This parameter can be one of @ref DMA_Optional_Interrupt group.
  * @retval HAL_ERROR  Transfer mode parameter is linked-list linear
  * @retval HAL_BUSY   DMA channel state is active when calling this API
  * @retval HAL_OK     Peripheral transfer is successfully started
  */
hal_status_t HAL_DMA_StartPeriphXfer_IT_Opt(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr,
                                            uint32_t size_byte, uint32_t interrupts)
{
  ASSERT_DBG_PARAM(hdma != NULL);
  ASSERT_DBG_PARAM((size_byte > 0U) && (size_byte <= 0xFFFFU));
  ASSERT_DBG_PARAM(IS_DMA_OPT_IT(interrupts));
  ASSERT_DBG_STATE(hdma->global_state, HAL_DMA_STATE_IDLE);

  HAL_CHECK_UPDATE_STATE(hdma, global_state, HAL_DMA_STATE_IDLE, HAL_DMA_STATE_ACTIVE);

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  /* Linear linked -list mode is activated */
  if (hdma->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_LINEAR)
  {
    return HAL_ERROR;
  }
  /* Circular linked -list mode is activated */
  else if (hdma->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    DMA_UpdateDataNode(hdma->p_head_node, src_addr, dest_addr, size_byte);
    DMA_StartLinkedListXfer(hdma, hdma->p_head_node, interrupts);
  }
  else
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    DMA_StartDirectXfer(hdma, src_addr, dest_addr, size_byte, interrupts);
  }

  return HAL_OK;
}
/**
  * @}
  */

#endif /* USE_HAL_DMA_MODULE */

/**
  * @}
  */

/**
  * @}
  */
