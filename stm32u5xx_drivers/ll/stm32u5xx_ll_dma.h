/**
  **********************************************************************************************************************
  * @file    stm32u5xx_ll_dma.h
  * @brief   Header file of DMA LL module.
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
 @verbatim
  ======================================================================================================================
                      ##### LL DMA driver acronyms #####
  ======================================================================================================================
  [..]  Acronyms table :
                   ======================================
                   | Acronym |                          |
                   ======================================
                   | SRC     |  Source                  |
                   | DEST    |  Destination             |
                   | ADDR    |  Address                 |
                   | INC     |  Increment / Incremented |
                   | DEC     |  Decrement / Decremented |
                   | BLK     |  Block                   |
                   | RPT     |  Repeat / Repeated       |
                   | TRIG    |  Trigger                 |
                   ======================================
 @endverbatim
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_LL_DMA_H
#define STM32U5XX_LL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if (defined (GPDMA1) || defined (LPDMA1))

/** @defgroup DMA_LL DMA
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/

/** @defgroup DMA_LL_Private_Variables DMA Private Variables
  * @{
  */
#define LL_DMA_NODE_REGISTER_NUM             8U  /*!< DMA node register number          */
#define LL_DMA_NODE_2D_ADDRESSING_OFFSET     28U /*!< DMA node 2d addressing offset     */
#define LL_DMA_NODE_LINEAR_ADDRESSING_OFFSET 20U /*!< DMA node linear addressing offset */
/**
  * @}
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup DMA_LL_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_LL_EC_CHANNEL channel
  * @{
  */
#define LL_DMA_CHANNEL_0  0x00U /*!< LL DMA channel 0  */
#define LL_DMA_CHANNEL_1  0x01U /*!< LL DMA channel 1  */
#define LL_DMA_CHANNEL_2  0x02U /*!< LL DMA channel 2  */
#define LL_DMA_CHANNEL_3  0x03U /*!< LL DMA channel 3  */
#define LL_DMA_CHANNEL_4  0x04U /*!< LL DMA channel 4  */
#define LL_DMA_CHANNEL_5  0x05U /*!< LL DMA channel 5  */
#define LL_DMA_CHANNEL_6  0x06U /*!< LL DMA channel 6  */
#define LL_DMA_CHANNEL_7  0x07U /*!< LL DMA channel 7  */
#define LL_DMA_CHANNEL_8  0x08U /*!< LL DMA channel 8  */
#define LL_DMA_CHANNEL_9  0x09U /*!< LL DMA channel 9  */
#define LL_DMA_CHANNEL_10 0x0AU /*!< LL DMA channel 10 */
#define LL_DMA_CHANNEL_11 0x0BU /*!< LL DMA channel 11 */
#define LL_DMA_CHANNEL_12 0x0CU /*!< LL DMA channel 12 */
#define LL_DMA_CHANNEL_13 0x0DU /*!< LL DMA channel 13 */
#define LL_DMA_CHANNEL_14 0x0EU /*!< LL DMA channel 14 */
#define LL_DMA_CHANNEL_15 0x0FU /*!< LL DMA channel 15 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DMA_CHANNEL_INSTANCE DMA channel instance
  * @{
  */
/* GPDMA channel instances */
#define LL_GPDMA1_CH0  GPDMA1_CH0  /*!< LL GPDMA1 channel 0  */
#define LL_GPDMA1_CH1  GPDMA1_CH1  /*!< LL GPDMA1 channel 1  */
#define LL_GPDMA1_CH2  GPDMA1_CH2  /*!< LL GPDMA1 channel 2  */
#define LL_GPDMA1_CH3  GPDMA1_CH3  /*!< LL GPDMA1 channel 3  */
#define LL_GPDMA1_CH4  GPDMA1_CH4  /*!< LL GPDMA1 channel 4  */
#define LL_GPDMA1_CH5  GPDMA1_CH5  /*!< LL GPDMA1 channel 5  */
#define LL_GPDMA1_CH6  GPDMA1_CH6  /*!< LL GPDMA1 channel 6  */
#define LL_GPDMA1_CH7  GPDMA1_CH7  /*!< LL GPDMA1 channel 7  */
#define LL_GPDMA1_CH8  GPDMA1_CH8  /*!< LL GPDMA1 channel 8  */
#define LL_GPDMA1_CH9  GPDMA1_CH9  /*!< LL GPDMA1 channel 9  */
#define LL_GPDMA1_CH10 GPDMA1_CH10 /*!< LL GPDMA1 channel 10 */
#define LL_GPDMA1_CH11 GPDMA1_CH11 /*!< LL GPDMA1 channel 11 */
#define LL_GPDMA1_CH12 GPDMA1_CH12 /*!< LL GPDMA1 channel 12 */
#define LL_GPDMA1_CH13 GPDMA1_CH13 /*!< LL GPDMA1 channel 13 */
#define LL_GPDMA1_CH14 GPDMA1_CH14 /*!< LL GPDMA1 channel 14 */
#define LL_GPDMA1_CH15 GPDMA1_CH15 /*!< LL GPDMA1 channel 15 */
/* LPDMA channel instances */
#define LL_LPDMA1_CH0  LPDMA1_CH0  /*!< LL LPDMA1 channel 0  */
#define LL_LPDMA1_CH1  LPDMA1_CH1  /*!< LL LPDMA1 channel 1  */
#define LL_LPDMA1_CH2  LPDMA1_CH2  /*!< LL LPDMA1 channel 2  */
#define LL_LPDMA1_CH3  LPDMA1_CH3  /*!< LL LPDMA1 channel 3  */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_CLLR_OFFSET CLLR offset
  * @{
  */
#define LL_DMA_IT_TC   DMA_CCR_TCIE                                                     /*!< Transfer complete
                                                                                             interrupt                */
#define LL_DMA_IT_HT   DMA_CCR_HTIE                                                     /*!< Half transfer complete
                                                                                             interrupt                */
#define LL_DMA_IT_DTE  DMA_CCR_DTEIE                                                    /*!< Data transfer error
                                                                                             interrupt                */
#define LL_DMA_IT_ULE  DMA_CCR_ULEIE                                                    /*!< Update linked-list item
                                                                                             error interrupt          */
#define LL_DMA_IT_USE  DMA_CCR_USEIE                                                    /*!< User setting error
                                                                                             interrupt                */
#define LL_DMA_IT_SUSP DMA_CCR_SUSPIE                                                   /*!< Completed suspension
                                                                                             interrupt                */
#define LL_DMA_IT_TO   DMA_CCR_TOIE                                                     /*!< Trigger overrun
                                                                                             interrupt                */
#define LL_DMA_IT_ALL  (DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_DTEIE | DMA_CCR_ULEIE | \
                        DMA_CCR_USEIE | DMA_CCR_SUSPIE | DMA_CCR_TOIE)                  /*!< All interrupts           */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_CLLR_OFFSET CLLR offset
  * @{
  */
#define LL_DMA_FLAG_IDLE DMA_CSR_IDLEF                                                /*!< Idle flag                  */
#define LL_DMA_FLAG_TC   DMA_CSR_TCF                                                  /*!< Transfer complete flag     */
#define LL_DMA_FLAG_HT   DMA_CSR_HTF                                                  /*!< Half transfer complete
                                                                                           flag                       */
#define LL_DMA_FLAG_DTE  DMA_CSR_DTEF                                                 /*!< Data transfer error flag   */
#define LL_DMA_FLAG_ULE  DMA_CSR_ULEF                                                 /*!< Update linked-list item
                                                                                           error flag                 */
#define LL_DMA_FLAG_USE  DMA_CSR_USEF                                                 /*!< User setting error flag    */
#define LL_DMA_FLAG_SUSP DMA_CSR_SUSPF                                                /*!< Completed suspension flag  */
#define LL_DMA_FLAG_TO   DMA_CSR_TOF                                                  /*!< Trigger overrun flag       */
#define LL_DMA_FLAG_ALL  (DMA_CSR_TCF | DMA_CSR_HTF | DMA_CSR_DTEF | DMA_CSR_ULEF | \
                          DMA_CSR_USEF | DMA_CSR_SUSPF | DMA_CSR_TOF)                 /*!< All flags                  */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_PRIORITY_LEVEL Priority Level
  * @{
  */
#define LL_DMA_PRIORITY_LOW_WEIGHT_LOW  0x00000000U    /*!< Priority level : Low Priority, Low Weight  */
#define LL_DMA_PRIORITY_LOW_WEIGHT_MID  DMA_CCR_PRIO_0 /*!< Priority level : Low Priority, Mid Weight  */
#define LL_DMA_PRIORITY_LOW_WEIGHT_HIGH DMA_CCR_PRIO_1 /*!< Priority level : Low Priority, High Weight */
#define LL_DMA_PRIORITY_HIGH            DMA_CCR_PRIO   /*!< Priority level : High Priority             */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_LINKED_LIST_ALLOCATED_PORT Linked List Allocated Port
  * @{
  */
#define LL_DMA_LINK_ALLOCATED_PORT0 0x00000000U /*!< Linked List Allocated Port 0 */
#define LL_DMA_LINK_ALLOCATED_PORT1 DMA_CCR_LAP /*!< Linked List Allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_LINK_STEP_MODE Link Step Mode
  * @{
  */
#define LL_DMA_LINKEDLIST_EXECUTION_Q    0x00000000U /*!< channel executed for the full linked-list              */
#define LL_DMA_LINKEDLIST_EXECUTION_NODE DMA_CCR_LSM /*!< channel executed once for the current linked-list item */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DEST_HALFWORD_EXCHANGE Destination Half-Word Exchange
  * @{
  */
#define LL_DMA_DEST_HALFWORD_PRESERVED  0x00000000U  /*!< When destination data width > Half-Word, no half-word-based
                                                          exchange within word.                                       */
#define LL_DMA_DEST_HALFWORD_EXCHANGED  DMA_CTR1_DHX /*!< When destination data width > Half-Word, The two consecutive
                                                          half-words are exchanged in each destination word.          */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DEST_BYTE_EXCHANGE Destination Byte Exchange
  * @{
  */
#define LL_DMA_DEST_BYTE_PRESERVED 0x00000000U  /*!< When destination data width > Byte, no byte-based exchange within
                                                     half-word.                                                       */
#define LL_DMA_DEST_BYTE_EXCHANGED DMA_CTR1_DBX /*!< When destination data width > Byte, the two consecutive bytes are
                                                     exchanged in each destination half-word.                         */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SRC_BYTE_EXCHANGE Source Byte Exchange
  * @{
  */
#define LL_DMA_SRC_BYTE_PRESERVED 0x00000000U  /*!< No byte-based exchange within the unaligned half-word of each source
                                                    word.                                                             */
#define LL_DMA_SRC_BYTE_EXCHANGED DMA_CTR1_SBX /*!< The two consecutive bytes within the unaligned half-word of each
                                                    source word are exchanged.                                        */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_ALLOCATED_PORT Source Allocated Port
  * @{
  */
#define LL_DMA_SRC_ALLOCATED_PORT0 0x00000000U  /*!< Source Allocated Port 0 */
#define LL_DMA_SRC_ALLOCATED_PORT1 DMA_CTR1_SAP /*!< Source Allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_ALLOCATED_PORT Destination Allocated Port
  * @{
  */
#define LL_DMA_DEST_ALLOCATED_PORT0 0x00000000U  /*!< Destination Allocated Port 0 */
#define LL_DMA_DEST_ALLOCATED_PORT1 DMA_CTR1_DAP /*!< Destination Allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_INCREMENT_MODE Destination Increment Mode
  * @{
  */
#define LL_DMA_DEST_ADDR_FIXED         0x00000000U   /*!< Destination fixed single/burst       */
#define LL_DMA_DEST_ADDR_INCREMENTED   DMA_CTR1_DINC /*!< Destination incremented single/burst */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_DATA_WIDTH Destination Data Width
  * @{
  */
#define LL_DMA_DEST_DATA_WIDTH_BYTE       0x00000000U         /*!< Destination Data Width : Byte       */
#define LL_DMA_DEST_DATA_WIDTH_HALFWORD   DMA_CTR1_DDW_LOG2_0 /*!< Destination Data Width : HalfWord   */
#define LL_DMA_DEST_DATA_WIDTH_WORD       DMA_CTR1_DDW_LOG2_1 /*!< Destination Data Width : Word       */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_DATA_TRUNCATION_PADDING Destination Data Truncation and Padding
  * @{
  */
#define LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO  0x00000000U    /*!< If src data width < dest data width :
                                                                 => Right Aligned padded with 0 up to destination
                                                                    data width.
                                                                 If src data width > dest data width :
                                                                 => Right Aligned Left Truncated down to destination
                                                                    data width.                                       */
#define LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN DMA_CTR1_PAM_0 /*!< If src data width < dest data width :
                                                                 => Right Aligned padded with sign extended up to
                                                                    destination data width.
                                                                 If src data width > dest data width :
                                                                 => Left Aligned Right Truncated down to the destination
                                                                    data width                                        */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DESTINATION_DATA_PACKING Destination Data Packing
  * @{
  */
#define LL_DMA_DEST_DATA_PRESERVED        0x00000000U   /*!< If src data width < dest data width :
                                                          => Packed at the destination data width
                                                          If src data width > dest data width :
                                                          => Unpacked at the destination data width */
#define LL_DMA_DEST_DATA_PACKED_UNPACKED  DMA_CTR1_PAM_1 /*!< If src data width < dest data width :
                                                          => Packed at the destination data width
                                                          If src data width > dest data width :
                                                          => Unpacked at the destination data width */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_INCREMENT_MODE Source Increment Mode
  * @{
  */
#define LL_DMA_SRC_ADDR_FIXED        0x00000000U   /*!< Source fixed single/burst       */
#define LL_DMA_SRC_ADDR_INCREMENTED  DMA_CTR1_SINC /*!< Source incremented single/burst */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_DATA_WIDTH Source Data Width
  * @{
  */
#define LL_DMA_SRC_DATA_WIDTH_BYTE     0x00000000U         /*!< Source Data Width : Byte       */
#define LL_DMA_SRC_DATA_WIDTH_HALFWORD DMA_CTR1_SDW_LOG2_0 /*!< Source Data Width : HalfWord   */
#define LL_DMA_SRC_DATA_WIDTH_WORD     DMA_CTR1_SDW_LOG2_1 /*!< Source Data Width : Word       */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_BLKHW_REQUEST Block Hardware Request
  * @{
  */
#define LL_DMA_HARDWARE_REQUEST_BURST   0x00000000U   /*!< Hardware request is driven by a peripheral with a hardware
                                                        request/acknowledge protocol at a burst level                 */
#define LL_DMA_HARDWARE_REQUEST_BLOCK   DMA_CTR2_BREQ /*!< Hardware request is driven by a peripheral with a hardware
                                                        request/acknowledge protocol at a block level                 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRANSFER_EVENT_MODE Transfer Event Mode
  * @{
  */
#define LL_DMA_DIRECT_XFER_EVENT_BLOCK              0x00000000U       /*!< The TC (and the HT) event is generated at the
                                                                           (respectively half of the) end of a block  */
#define LL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK     DMA_CTR2_TCEM_0   /*!< The TC (and the HT) event is generated at the
                                                                           end (respectively half of the end) of the
                                                                           2D/repeated block                          */
#define LL_DMA_LINKEDLIST_XFER_EVENT_BLOCK          LL_DMA_DIRECT_XFER_EVENT_BLOCK   /*!< The TC (and the HT) event is
                                                                                          generated at the (respectively
                                                                                          half of the) end of a block */
#define LL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK LL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK /*!< The TC (and the HT)
                                                                                                 event is generated at
                                                                                                 the end (respectively
                                                                                                 half of the end) of the
                                                                                                 2D/repeated block    */
#define LL_DMA_LINKEDLIST_XFER_EVENT_NODE           DMA_CTR2_TCEM_1   /*!< The TC (and the HT) event is generated at the
                                                                           (respectively half) end of each linked-list
                                                                           item                                       */
#define LL_DMA_LINKEDLIST_XFER_EVENT_Q              DMA_CTR2_TCEM   /*!< The TC (and the HT) event is generated at the
                                                                         (respectively half) end of the last linked-list
                                                                         item                                         */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRIGGER_POLARITY Trigger Polarity
  * @{
  */
#define LL_DMA_TRIGGER_POLARITY_MASKED      0x00000000U        /*!< No trigger of the selected DMA request.
                                                                    Masked trigger event                              */
#define LL_DMA_TRIGGER_POLARITY_RISING      DMA_CTR2_TRIGPOL_0 /*!< Trigger of the selected DMA request on the rising
                                                                    edge of the selected trigger event input          */
#define LL_DMA_TRIGGER_POLARITY_FALLING     DMA_CTR2_TRIGPOL_1 /*!< Trigger of the selected DMA request on the falling
                                                                    edge of the selected trigger event input          */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRIGGER_MODE Transfer Trigger Mode
  * @{
  */
#define LL_DMA_TRIGGER_BLOCK_TRANSFER           0x00000000U   /*!< A block transfer is conditioned by (at least) one hit
                                                                   trigger                                            */
#define LL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER  DMA_CTR2_TRIGM_0  /*!< A repeated block transfer is conditioned by
                                                                       (at least) one hit trigger                     */
#define LL_DMA_TRIGGER_NODE_TRANSFER            DMA_CTR2_TRIGM_1  /*!< A LLI link transfer is conditioned by (at least)
                                                                       one hit trigger                                */
#define LL_DMA_TRIGGER_SINGLE_BURST_TRANSFER    DMA_CTR2_TRIGM /*!< A Single/Burst transfer is conditioned by (at least)
                                                                    one hit trigger                                   */
/**
  * @}
  */


/** @defgroup DMA_LL_EC_TRANSFER_DIRECTION Transfer Direction
  * @{
  */
#define LL_DMA_DIRECTION_MEMORY_TO_MEMORY DMA_CTR2_SWREQ /*!< Memory to memory direction     */
#define LL_DMA_DIRECTION_PERIPH_TO_MEMORY 0x00000000U    /*!< Peripheral to memory direction */
#define LL_DMA_DIRECTION_MEMORY_TO_PERIPH DMA_CTR2_DREQ  /*!< Memory to peripheral direction */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_BLK_RPT_SRC_ADDR_UPDATE_MODE Block Repeat Source Address Update Mode
  * @{
  */
#define LL_DMA_BLOCK_SRC_ADDR_INCREMENTED   0x00000000U     /*!< Source address pointer is incremented after each block
                                                                 transfer by source update value                      */
#define LL_DMA_BLOCK_SRC_ADDR_DECREMENTED   DMA_CBR1_BRSDEC /*!< Source address pointer is decremented after each block
                                                                 transfer by source update value                      */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_BLK_RPT_DEST_ADDR_UPDATE_MODE Block Repeat Destination Address Update Mode
  * @{
  */
#define LL_DMA_BLOCK_DEST_ADDR_INCREMENTED  0x00000000U     /*!< Destination address is incremented after each block
                                                                 transfer by destination update value                 */
#define LL_DMA_BLOCK_DEST_ADDR_DECREMENTED  DMA_CBR1_BRDDEC /*!< Destination address is decremented after each block
                                                                 transfer by destination update value                 */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SRC_ADDR_UPDATE_MODE Burst Source Address Update Mode
  * @{
  */
#define LL_DMA_BURST_SRC_ADDR_INCREMENTED   0x00000000U   /*!< Source address pointer is incremented after each burst
                                                               transfer by source update value                        */
#define LL_DMA_BURST_SRC_ADDR_DECREMENTED   DMA_CBR1_SDEC /*!< Source address pointer is decremented after each burst
                                                               transfer by source update value                        */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_DEST_ADDR_UPDATE_MODE Burst Destination Address Update Mode
  * @{
  */
#define LL_DMA_BURST_DEST_ADDR_INCREMENTED  0x00000000U   /*!< Destination address pointer is incremented after each
                                                               burst transfer by destination update value             */
#define LL_DMA_BURST_DEST_ADDR_DECREMENTED  DMA_CBR1_DDEC /*!< Destination address pointer is decremented after each
                                                               burst transfer by destination update value             */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_SECURITY_ATTRIBUTE Source Security Attribute
  * @{
  */
#define LL_DMA_ATTR_NSEC 0x00U /*!< Non Secure channel */
#define LL_DMA_ATTR_SEC  0x01U /*!< Secure channel     */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_SOURCE_PRIVILEGE_ATTRIBUTE Source Privilege Attribute
  * @{
  */
#define LL_DMA_ATTR_NPRIV 0x00U /*!< Non Privileged channel */
#define LL_DMA_ATTR_PRIV  0x01U /*!< Privileged channel     */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_LINKEDLIST_REGISTER_UPDATE Linked list register update
  * @{
  */
#define LL_DMA_UPDATE_CTR1 DMA_CLLR_UT1 /*!< Update CTR1 register from memory : available for all DMA channels        */
#define LL_DMA_UPDATE_CTR2 DMA_CLLR_UT2 /*!< Update CTR2 register from memory : available for all DMA channels        */
#define LL_DMA_UPDATE_CBR1 DMA_CLLR_UB1 /*!< Update CBR1 register from memory : available for all DMA channels        */
#define LL_DMA_UPDATE_CSAR DMA_CLLR_USA /*!< Update CSAR register from memory : available for all DMA channels        */
#define LL_DMA_UPDATE_CDAR DMA_CLLR_UDA /*!< Update CDAR register from memory : available for all DMA channels        */
#define LL_DMA_UPDATE_CTR3 DMA_CLLR_UT3 /*!< Update CTR3 register from memory : available only for 2D addressing DMA
                                             channels                                                                 */
#define LL_DMA_UPDATE_CBR2 DMA_CLLR_UB2 /*!< Update CBR2 register from memory : available only for 2D addressing DMA
                                             channels                                                                 */
#define LL_DMA_UPDATE_CLLR DMA_CLLR_ULL /*!< Update CLLR register from memory : available for all DMA channels        */
#define LL_DMA_UPDATE_ALL  (DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | \
                            DMA_CLLR_UDA | DMA_CLLR_UT3 | DMA_CLLR_UB2 | DMA_CLLR_ULL)
/**
  * @}
  */

/** @defgroup DMA_LL_EC_REQUEST_SELECTION Request Selection
  * @{
  */
/* GPDMA1 Hardware Requests */
#define LL_GPDMA1_REQUEST_ADC1         0U   /*!< GPDMA1 HW Request is ADC1         */
#define LL_GPDMA1_REQUEST_ADC4         1U   /*!< GPDMA1 HW Request is ADC4         */
#define LL_GPDMA1_REQUEST_DAC1_CH1     2U   /*!< GPDMA1 HW Request is DAC1_CH1     */
#define LL_GPDMA1_REQUEST_DAC1_CH2     3U   /*!< GPDMA1 HW Request is DAC1_CH2     */
#define LL_GPDMA1_REQUEST_TIM6_UPD     4U   /*!< GPDMA1 HW Request is TIM6_UPD     */
#define LL_GPDMA1_REQUEST_TIM7_UPD     5U   /*!< GPDMA1 HW Request is TIM7_UPD     */
#define LL_GPDMA1_REQUEST_SPI1_RX      6U   /*!< GPDMA1 HW Request is SPI1_RX      */
#define LL_GPDMA1_REQUEST_SPI1_TX      7U   /*!< GPDMA1 HW Request is SPI1_TX      */
#define LL_GPDMA1_REQUEST_SPI2_RX      8U   /*!< GPDMA1 HW Request is SPI2_RX      */
#define LL_GPDMA1_REQUEST_SPI2_TX      9U   /*!< GPDMA1 HW Request is SPI2_TX      */
#define LL_GPDMA1_REQUEST_SPI3_RX      10U  /*!< GPDMA1 HW Request is SPI3_RX      */
#define LL_GPDMA1_REQUEST_SPI3_TX      11U  /*!< GPDMA1 HW Request is SPI3_TX      */
#define LL_GPDMA1_REQUEST_I2C1_RX      12U  /*!< GPDMA1 HW Request is I2C1_RX      */
#define LL_GPDMA1_REQUEST_I2C1_TX      13U  /*!< GPDMA1 HW Request is I2C1_TX      */
#define LL_GPDMA1_REQUEST_I2C1_EVC     14U  /*!< GPDMA1 HW Request is I2C1_EVC     */
#define LL_GPDMA1_REQUEST_I2C2_RX      15U  /*!< GPDMA1 HW Request is I2C2_RX      */
#define LL_GPDMA1_REQUEST_I2C2_TX      16U  /*!< GPDMA1 HW Request is I2C2_TX      */
#define LL_GPDMA1_REQUEST_I2C2_EVC     17U  /*!< GPDMA1 HW Request is I2C2_EVC     */
#define LL_GPDMA1_REQUEST_I2C3_RX      18U  /*!< GPDMA1 HW Request is I2C3_RX      */
#define LL_GPDMA1_REQUEST_I2C3_TX      19U  /*!< GPDMA1 HW Request is I2C3_TX      */
#define LL_GPDMA1_REQUEST_I2C3_EVC     20U  /*!< GPDMA1 HW Request is I2C3_EVC     */
#define LL_GPDMA1_REQUEST_I2C4_RX      21U  /*!< GPDMA1 HW Request is I2C4_RX      */
#define LL_GPDMA1_REQUEST_I2C4_TX      22U  /*!< GPDMA1 HW Request is I2C4_TX      */
#define LL_GPDMA1_REQUEST_I2C4_EVC     23U  /*!< GPDMA1 HW Request is I2C4_EVC     */
#define LL_GPDMA1_REQUEST_USART1_RX    24U  /*!< GPDMA1 HW Request is USART1_RX    */
#define LL_GPDMA1_REQUEST_USART1_TX    25U  /*!< GPDMA1 HW Request is USART1_TX    */
#define LL_GPDMA1_REQUEST_USART2_RX    26U  /*!< GPDMA1 HW Request is USART2_RX    */
#define LL_GPDMA1_REQUEST_USART2_TX    27U  /*!< GPDMA1 HW Request is USART2_TX    */
#define LL_GPDMA1_REQUEST_USART3_RX    28U  /*!< GPDMA1 HW Request is USART3_RX    */
#define LL_GPDMA1_REQUEST_USART3_TX    29U  /*!< GPDMA1 HW Request is USART3_TX    */
#define LL_GPDMA1_REQUEST_UART4_RX     30U  /*!< GPDMA1 HW Request is UART4_RX     */
#define LL_GPDMA1_REQUEST_UART4_TX     31U  /*!< GPDMA1 HW Request is UART4_TX     */
#define LL_GPDMA1_REQUEST_UART5_RX     32U  /*!< GPDMA1 HW Request is UART5_RX     */
#define LL_GPDMA1_REQUEST_UART5_TX     33U  /*!< GPDMA1 HW Request is UART5_TX     */
#define LL_GPDMA1_REQUEST_LPUART1_RX   34U  /*!< GPDMA1 HW Request is LPUART1_RX   */
#define LL_GPDMA1_REQUEST_LPUART1_TX   35U  /*!< GPDMA1 HW Request is LPUART1_TX   */
#define LL_GPDMA1_REQUEST_SAI1_A       36U  /*!< GPDMA1 HW Request is SAI1_A       */
#define LL_GPDMA1_REQUEST_SAI1_B       37U  /*!< GPDMA1 HW Request is SAI1_B       */
#define LL_GPDMA1_REQUEST_SAI2_A       38U  /*!< GPDMA1 HW Request is SAI2_A       */
#define LL_GPDMA1_REQUEST_SAI2_B       39U  /*!< GPDMA1 HW Request is SAI2_B       */
#define LL_GPDMA1_REQUEST_OCTOSPI1     40U  /*!< GPDMA1 HW Request is OCTOSPI1     */
#define LL_GPDMA1_REQUEST_OCTOSPI2     41U  /*!< GPDMA1 HW Request is OCTOSPI2     */
#define LL_GPDMA1_REQUEST_TIM1_CC1     42U  /*!< GPDMA1 HW Request is TIM1_CC1     */
#define LL_GPDMA1_REQUEST_TIM1_CC2     43U  /*!< GPDMA1 HW Request is TIM1_CC2     */
#define LL_GPDMA1_REQUEST_TIM1_CC3     44U  /*!< GPDMA1 HW Request is TIM1_CC3     */
#define LL_GPDMA1_REQUEST_TIM1_CC4     45U  /*!< GPDMA1 HW Request is TIM1_CC4     */
#define LL_GPDMA1_REQUEST_TIM1_UPD     46U  /*!< GPDMA1 HW Request is TIM1_UPD     */
#define LL_GPDMA1_REQUEST_TIM1_TRGI    47U  /*!< GPDMA1 HW Request is TIM1_TRGI    */
#define LL_GPDMA1_REQUEST_TIM1_COM     48U  /*!< GPDMA1 HW Request is TIM1_COM     */
#define LL_GPDMA1_REQUEST_TIM8_CC1     49U  /*!< GPDMA1 HW Request is TIM8_CC1     */
#define LL_GPDMA1_REQUEST_TIM8_CC2     50U  /*!< GPDMA1 HW Request is TIM8_CC2     */
#define LL_GPDMA1_REQUEST_TIM8_CC3     51U  /*!< GPDMA1 HW Request is TIM8_CC3     */
#define LL_GPDMA1_REQUEST_TIM8_CC4     52U  /*!< GPDMA1 HW Request is TIM8_CC4     */
#define LL_GPDMA1_REQUEST_TIM8_UPD     53U  /*!< GPDMA1 HW Request is TIM8_UPD     */
#define LL_GPDMA1_REQUEST_TIM8_TRGI    54U  /*!< GPDMA1 HW Request is TIM8_TRGI    */
#define LL_GPDMA1_REQUEST_TIM8_COM     55U  /*!< GPDMA1 HW Request is TIM8_COM     */
#define LL_GPDMA1_REQUEST_TIM2_CC1     56U  /*!< GPDMA1 HW Request is TIM2_CC1     */
#define LL_GPDMA1_REQUEST_TIM2_CC2     57U  /*!< GPDMA1 HW Request is TIM2_CC2     */
#define LL_GPDMA1_REQUEST_TIM2_CC3     58U  /*!< GPDMA1 HW Request is TIM2_CC3     */
#define LL_GPDMA1_REQUEST_TIM2_CC4     59U  /*!< GPDMA1 HW Request is TIM2_CC4     */
#define LL_GPDMA1_REQUEST_TIM2_UPD     60U  /*!< GPDMA1 HW Request is TIM2_UPD     */
#define LL_GPDMA1_REQUEST_TIM3_CC1     61U  /*!< GPDMA1 HW Request is TIM3_CC1     */
#define LL_GPDMA1_REQUEST_TIM3_CC2     62U  /*!< GPDMA1 HW Request is TIM3_CC2     */
#define LL_GPDMA1_REQUEST_TIM3_CC3     63U  /*!< GPDMA1 HW Request is TIM3_CC3     */
#define LL_GPDMA1_REQUEST_TIM3_CC4     64U  /*!< GPDMA1 HW Request is TIM3_CC4     */
#define LL_GPDMA1_REQUEST_TIM3_UPD     65U  /*!< GPDMA1 HW Request is TIM3_UPD     */
#define LL_GPDMA1_REQUEST_TIM3_TRGI    66U  /*!< GPDMA1 HW Request is TIM3_TRGI    */
#define LL_GPDMA1_REQUEST_TIM4_CC1     67U  /*!< GPDMA1 HW Request is TIM4_CC1     */
#define LL_GPDMA1_REQUEST_TIM4_CC2     68U  /*!< GPDMA1 HW Request is TIM4_CC2     */
#define LL_GPDMA1_REQUEST_TIM4_CC3     69U  /*!< GPDMA1 HW Request is TIM4_CC3     */
#define LL_GPDMA1_REQUEST_TIM4_CC4     70U  /*!< GPDMA1 HW Request is TIM4_CC4     */
#define LL_GPDMA1_REQUEST_TIM4_UPD     71U  /*!< GPDMA1 HW Request is TIM4_UPD     */
#define LL_GPDMA1_REQUEST_TIM5_CC1     72U  /*!< GPDMA1 HW Request is TIM5_CC1     */
#define LL_GPDMA1_REQUEST_TIM5_CC2     73U  /*!< GPDMA1 HW Request is TIM5_CC2     */
#define LL_GPDMA1_REQUEST_TIM5_CC3     74U  /*!< GPDMA1 HW Request is TIM5_CC3     */
#define LL_GPDMA1_REQUEST_TIM5_CC4     75U  /*!< GPDMA1 HW Request is TIM5_CC4     */
#define LL_GPDMA1_REQUEST_TIM5_UPD     76U  /*!< GPDMA1 HW Request is TIM5_UPD     */
#define LL_GPDMA1_REQUEST_TIM5_TRGI    77U  /*!< GPDMA1 HW Request is TIM5_TRGI    */
#define LL_GPDMA1_REQUEST_TIM15_CC1    78U  /*!< GPDMA1 HW Request is TIM15_CC1    */
#define LL_GPDMA1_REQUEST_TIM15_UPD    79U  /*!< GPDMA1 HW Request is TIM15_UPD    */
#define LL_GPDMA1_REQUEST_TIM15_TRGI   80U  /*!< GPDMA1 HW Request is TIM15_TRGI   */
#define LL_GPDMA1_REQUEST_TIM15_COM    81U  /*!< GPDMA1 HW Request is TIM15_COM    */
#define LL_GPDMA1_REQUEST_TIM16_CC1    82U  /*!< GPDMA1 HW Request is TIM16_CC1    */
#define LL_GPDMA1_REQUEST_TIM16_UPD    83U  /*!< GPDMA1 HW Request is TIM16_UPD    */
#define LL_GPDMA1_REQUEST_TIM17_CC1    84U  /*!< GPDMA1 HW Request is TIM17_CC1    */
#define LL_GPDMA1_REQUEST_TIM17_UPD    85U  /*!< GPDMA1 HW Request is TIM17_UPD    */
#define LL_GPDMA1_REQUEST_DCMI_PSSI    86U  /*!< GPDMA1 HW Request is DCMI_PSSI    */
#define LL_GPDMA1_REQUEST_AES_IN       87U  /*!< GPDMA1 HW Request is AES_IN       */
#define LL_GPDMA1_REQUEST_AES_OUT      88U  /*!< GPDMA1 HW Request is AES_OUT      */
#define LL_GPDMA1_REQUEST_HASH_IN      89U  /*!< GPDMA1 HW Request is HASH_IN      */
#define LL_GPDMA1_REQUEST_UCPD1_TX     90U  /*!< GPDMA1 HW Request is UCPD1_TX     */
#define LL_GPDMA1_REQUEST_UCPD1_RX     91U  /*!< GPDMA1 HW Request is UCPD1_RX     */
#define LL_GPDMA1_REQUEST_MDF1_FLT0    92U  /*!< GPDMA1 HW Request is MDF1_FLT0    */
#define LL_GPDMA1_REQUEST_MDF1_FLT1    93U  /*!< GPDMA1 HW Request is MDF1_FLT1    */
#define LL_GPDMA1_REQUEST_MDF1_FLT2    94U  /*!< GPDMA1 HW Request is MDF1_FLT2    */
#define LL_GPDMA1_REQUEST_MDF1_FLT3    95U  /*!< GPDMA1 HW Request is MDF1_FLT3    */
#define LL_GPDMA1_REQUEST_MDF1_FLT4    96U  /*!< GPDMA1 HW Request is MDF1_FLT4    */
#define LL_GPDMA1_REQUEST_MDF1_FLT5    97U  /*!< GPDMA1 HW Request is MDF1_FLT5    */
#define LL_GPDMA1_REQUEST_ADF1_FLT0    98U  /*!< GPDMA1 HW Request is ADF1_FLT0    */
#define LL_GPDMA1_REQUEST_FMAC_RD      99U  /*!< GPDMA1 HW Request is FMAC_RD      */
#define LL_GPDMA1_REQUEST_FMAC_WR      100U /*!< GPDMA1 HW Request is FMAC_WR      */
#define LL_GPDMA1_REQUEST_CORDIC_RD    101U /*!< GPDMA1 HW Request is CORDIC_RD    */
#define LL_GPDMA1_REQUEST_CORDIC_WR    102U /*!< GPDMA1 HW Request is CORDIC_WR    */
#define LL_GPDMA1_REQUEST_SAES_IN      103U /*!< GPDMA1 HW Request is SAES_IN      */
#define LL_GPDMA1_REQUEST_SAES_OUT     104U /*!< GPDMA1 HW Request is SAES_OUT     */
#define LL_GPDMA1_REQUEST_LPTIM1_IC1   105U /*!< GPDMA1 HW Request is LPTIM1_IC1   */
#define LL_GPDMA1_REQUEST_LPTIM1_IC2   106U /*!< GPDMA1 HW Request is LPTIM1_IC2   */
#define LL_GPDMA1_REQUEST_LPTIM1_UE    107U /*!< GPDMA1 HW Request is LPTIM1_UE    */
#define LL_GPDMA1_REQUEST_LPTIM2_IC1   108U /*!< GPDMA1 HW Request is LPTIM2_IC1   */
#define LL_GPDMA1_REQUEST_LPTIM2_IC2   109U /*!< GPDMA1 HW Request is LPTIM2_IC2   */
#define LL_GPDMA1_REQUEST_LPTIM2_UE    110U /*!< GPDMA1 HW Request is LPTIM2_UE    */
#define LL_GPDMA1_REQUEST_LPTIM3_IC1   111U /*!< GPDMA1 HW Request is LPTIM3_IC1   */
#define LL_GPDMA1_REQUEST_LPTIM3_IC2   112U /*!< GPDMA1 HW Request is LPTIM3_IC2   */
#define LL_GPDMA1_REQUEST_LPTIM3_UE    113U /*!< GPDMA1 HW Request is LPTIM3_UE    */
#if defined (HSPI1_BASE)
#define LL_GPDMA1_REQUEST_HSPI1        114U  /*!< GPDMA1 HW request is HSPI1       */
#endif /* defined (HSPI1_BASE) */
#if defined (I2C5)
#define LL_GPDMA1_REQUEST_I2C5_RX      115U  /*!< GPDMA1 HW request is I2C5_RX     */
#define LL_GPDMA1_REQUEST_I2C5_TX      116U  /*!< GPDMA1 HW request is I2C5_TX     */
#define LL_GPDMA1_REQUEST_I2C5_EVC     117U  /*!< GPDMA1 HW request is I2C5_EVC    */
#endif /* defined (I2C5) */
#if defined (I2C6)
#define LL_GPDMA1_REQUEST_I2C6_RX      118U  /*!< GPDMA1 HW request is I2C6_RX     */
#define LL_GPDMA1_REQUEST_I2C6_TX      119U  /*!< GPDMA1 HW request is I2C6_TX     */
#define LL_GPDMA1_REQUEST_I2C6_EVC     120U  /*!< GPDMA1 HW request is I2C6_EVC    */
#endif /* defined (I2C6) */
#if defined (USART6)
#define LL_GPDMA1_REQUEST_USART6_RX    121U  /*!< GPDMA1 HW request is USART6_RX   */
#define LL_GPDMA1_REQUEST_USART6_TX    122U  /*!< GPDMA1 HW request is USART6_TX   */
#endif /* defined (USART6) */
#if defined (ADC2)
#define LL_GPDMA1_REQUEST_ADC2         123U  /*!< GPDMA1 HW request is ADC2        */
#endif /* defined (ADC2) */
#if defined (JPEG)
#define LL_GPDMA1_REQUEST_JPEG_RX      124U  /*!< GPDMA1 HW request is JPEG_TX     */
#define LL_GPDMA1_REQUEST_JPEG_TX      125U  /*!< GPDMA1 HW request is JPEG_RX     */
#endif /* defined (JPEG) */

/* LPDMA1 Hardware Requests */
#define LL_LPDMA1_REQUEST_LPUART1_RX   0U   /*!< LPDMA1 HW Request is LPUART1_RX   */
#define LL_LPDMA1_REQUEST_LPUART1_TX   1U   /*!< LPDMA1 HW Request is LPUART1_TX   */
#define LL_LPDMA1_REQUEST_SPI3_RX      2U   /*!< LPDMA1 HW Request is SPI3_RX      */
#define LL_LPDMA1_REQUEST_SPI3_TX      3U   /*!< LPDMA1 HW Request is SPI3_TX      */
#define LL_LPDMA1_REQUEST_I2C3_RX      4U   /*!< LPDMA1 HW Request is I2C3_RX      */
#define LL_LPDMA1_REQUEST_I2C3_TX      5U   /*!< LPDMA1 HW Request is I2C3_TX      */
#define LL_LPDMA1_REQUEST_I2C3_EVC     6U   /*!< LPDMA1 HW Request is I2C3_EVC     */
#define LL_LPDMA1_REQUEST_ADC4         7U   /*!< LPDMA1 HW Request is ADC4         */
#define LL_LPDMA1_REQUEST_DAC1_CH1     8U   /*!< LPDMA1 HW Request is DAC1_CH1     */
#define LL_LPDMA1_REQUEST_DAC1_CH2     9U   /*!< LPDMA1 HW Request is DAC1_CH2     */
#define LL_LPDMA1_REQUEST_ADF1_FLT0    10U  /*!< LPDMA1 HW Request is ADF1_FLT0    */
#define LL_LPDMA1_REQUEST_LPTIM1_IC1   11U  /*!< LPDMA1 HW Request is LPTIM1_IC1   */
#define LL_LPDMA1_REQUEST_LPTIM1_IC2   12U  /*!< LPDMA1 HW Request is LPTIM1_IC2   */
#define LL_LPDMA1_REQUEST_LPTIM1_UE    13U  /*!< LPDMA1 HW Request is LPTIM1_UE    */
#define LL_LPDMA1_REQUEST_LPTIM3_IC1   14U  /*!< LPDMA1 HW Request is LPTIM3_IC1   */
#define LL_LPDMA1_REQUEST_LPTIM3_IC2   15U  /*!< LPDMA1 HW Request is LPTIM3_IC2   */
#define LL_LPDMA1_REQUEST_LPTIM3_UE    16U  /*!< LPDMA1 HW Request is LPTIM3_UE    */
/**
  * @}
  */

/** @defgroup DMA_LL_EC_TRIGGER_SELECTION Trigger Selection
  * @{
  */
/* GPDMA1 Hardware Triggers */
#define LL_GPDMA1_TRIGGER_EXTI0           0U  /*!< GPDMA1 HW Trigger is EXTI0           */
#define LL_GPDMA1_TRIGGER_EXTI1           1U  /*!< GPDMA1 HW Trigger is EXTI1           */
#define LL_GPDMA1_TRIGGER_EXTI2           2U  /*!< GPDMA1 HW Trigger is EXTI2           */
#define LL_GPDMA1_TRIGGER_EXTI3           3U  /*!< GPDMA1 HW Trigger is EXTI3           */
#define LL_GPDMA1_TRIGGER_EXTI4           4U  /*!< GPDMA1 HW Trigger is EXTI4           */
#define LL_GPDMA1_TRIGGER_EXTI5           5U  /*!< GPDMA1 HW Trigger is EXTI5           */
#define LL_GPDMA1_TRIGGER_EXTI6           6U  /*!< GPDMA1 HW Trigger is EXTI6           */
#define LL_GPDMA1_TRIGGER_EXTI7           7U  /*!< GPDMA1 HW Trigger is EXTI7           */
#define LL_GPDMA1_TRIGGER_TAMP_TRG1       8U  /*!< GPDMA1 HW Trigger is TAMP_TRG1       */
#define LL_GPDMA1_TRIGGER_TAMP_TRG2       9U  /*!< GPDMA1 HW Trigger is TAMP_TRG2       */
#define LL_GPDMA1_TRIGGER_TAMP_TRG3       10U /*!< GPDMA1 HW Trigger is TAMP_TRG3       */
#define LL_GPDMA1_TRIGGER_LPTIM1_CH1      11U /*!< GPDMA1 HW Trigger is LPTIM1_CH1      */
#define LL_GPDMA1_TRIGGER_LPTIM1_CH2      12U /*!< GPDMA1 HW Trigger is LPTIM1_CH2      */
#define LL_GPDMA1_TRIGGER_LPTIM2_CH1      13U /*!< GPDMA1 HW Trigger is LPTIM2_CH1      */
#define LL_GPDMA1_TRIGGER_LPTIM2_CH2      14U /*!< GPDMA1 HW Trigger is LPTIM2_CH2      */
#define LL_GPDMA1_TRIGGER_LPTIM4_OUT      15U /*!< GPDMA1 HW Trigger is LPTIM4_OUT      */
#define LL_GPDMA1_TRIGGER_COMP1_OUT       16U /*!< GPDMA1 HW Trigger is COMP1_OUT       */
#define LL_GPDMA1_TRIGGER_COMP2_OUT       17U /*!< GPDMA1 HW Trigger is COMP2_OUT       */
#define LL_GPDMA1_TRIGGER_RTC_ALRA_TRG    18U /*!< GPDMA1 HW Trigger is RTC_ALRA_TRG    */
#define LL_GPDMA1_TRIGGER_RTC_ALRB_TRG    19U /*!< GPDMA1 HW Trigger is RTC_ALRB_TRG    */
#define LL_GPDMA1_TRIGGER_RTC_WUT_TRG     20U /*!< GPDMA1 HW Trigger is RTC_WUT_TRG     */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH0_TC   22U /*!< GPDMA1 HW Trigger is GPDMA1_CH0_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH1_TC   23U /*!< GPDMA1 HW Trigger is GPDMA1_CH1_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH2_TC   24U /*!< GPDMA1 HW Trigger is GPDMA1_CH2_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH3_TC   25U /*!< GPDMA1 HW Trigger is GPDMA1_CH3_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH4_TC   26U /*!< GPDMA1 HW Trigger is GPDMA1_CH4_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH5_TC   27U /*!< GPDMA1 HW Trigger is GPDMA1_CH5_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH6_TC   28U /*!< GPDMA1 HW Trigger is GPDMA1_CH6_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH7_TC   29U /*!< GPDMA1 HW Trigger is GPDMA1_CH7_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH8_TC   30U /*!< GPDMA1 HW Trigger is GPDMA1_CH8_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH9_TC   31U /*!< GPDMA1 HW Trigger is GPDMA1_CH9_TC   */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH10_TC  32U /*!< GPDMA1 HW Trigger is GPDMA1_CH10_TC  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH11_TC  33U /*!< GPDMA1 HW Trigger is GPDMA1_CH11_TC  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH12_TC  34U /*!< GPDMA1 HW Trigger is GPDMA1_CH12_TC  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH13_TC  35U /*!< GPDMA1 HW Trigger is GPDMA1_CH13_TC  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH14_TC  36U /*!< GPDMA1 HW Trigger is GPDMA1_CH14_TC  */
#define LL_GPDMA1_TRIGGER_GPDMA1_CH15_TC  37U /*!< GPDMA1 HW Trigger is GPDMA1_CH15_TC  */
#define LL_GPDMA1_TRIGGER_LPDMA1_CH0_TC   38U /*!< GPDMA1 HW Trigger is LPDMA1_CH0_TC   */
#define LL_GPDMA1_TRIGGER_LPDMA1_CH1_TC   39U /*!< GPDMA1 HW Trigger is LPDMA1_CH1_TC   */
#define LL_GPDMA1_TRIGGER_LPDMA1_CH2_TC   40U /*!< GPDMA1 HW Trigger is LPDMA1_CH2_TC   */
#define LL_GPDMA1_TRIGGER_LPDMA1_CH3_TC   41U /*!< GPDMA1 HW Trigger is LPDMA1_CH3_TC   */
#define LL_GPDMA1_TRIGGER_TIM2_TRGO       42U /*!< GPDMA1 HW Trigger is TIM2_TRGO       */
#define LL_GPDMA1_TRIGGER_TIM15_TRGO      43U /*!< GPDMA1 HW Trigger is TIM15_TRGO      */
#define LL_GPDMA1_TRIGGER_ADC4_AWD1       57U /*!< GPDMA1 HW Trigger is ADC4_AWD1       */
#define LL_GPDMA1_TRIGGER_ADC1_AWD1       58U /*!< GPDMA1 HW Trigger is ADC1_AWD1       */
#if defined (TIM3_TRGO_TRIGGER_SUPPORT)
#define LL_GPDMA1_TRIGGER_TIM3_TRGO       44U /*!< GPDMA1 HW Trigger signal is TIM3_TRGO   */
#endif /* defined (TIM3_TRGO_TRIGGER_SUPPORT) */
#if defined (TIM4_TRGO_TRIGGER_SUPPORT)
#define LL_GPDMA1_TRIGGER_TIM4_TRGO       45U /*!< GPDMA1 HW Trigger signal is TIM4_TRGO   */
#endif /* defined (TIM4_TRGO_TRIGGER_SUPPORT) */
#if defined (TIM5_TRGO_TRIGGER_SUPPORT)
#define LL_GPDMA1_TRIGGER_TIM5_TRGO       46U /*!< GPDMA1 HW Trigger signal is TIM5_TRGO   */
#endif /* defined (TIM5_TRGO_TRIGGER_SUPPORT) */
#if defined (LTDC)
#define LL_GPDMA1_TRIGGER_LTDC_LI         47U /*!< GPDMA1 HW Trigger signal is LTDC_LI     */
#endif /* defined (LTDC) */
#if defined (DSI)
#define LL_GPDMA1_TRIGGER_DSI_TE          48U /*!< GPDMA1 HW Trigger signal is DSI_TE      */
#define LL_GPDMA1_TRIGGER_DSI_ER          49U /*!< GPDMA1 HW Trigger signal is DSI_ER      */
#endif /* defined (DSI) */
#if defined (DMA2D_TRIGGER_SUPPORT)
#define LL_GPDMA1_TRIGGER_DMA2D_TC        50U /*!< GPDMA1 HW Trigger signal is DMA2D_TC    */
#define LL_GPDMA1_TRIGGER_DMA2D_CTC       51U /*!< GPDMA1 HW Trigger signal is DMA2D_CTC   */
#define LL_GPDMA1_TRIGGER_DMA2D_TW        52U /*!< GPDMA1 HW Trigger signal is DMA2D_TW    */
#endif /* defined (DMA2D_TRIGGER_SUPPORT) */
#if defined (GPU2D)
#define LL_GPDMA1_TRIGGER_GPU2D_FLAG0     53U /*!< GPDMA1 HW Trigger signal is GPU2D_FLAG0 */
#define LL_GPDMA1_TRIGGER_GPU2D_FLAG1     54U /*!< GPDMA1 HW Trigger signal is GPU2D_FLAG1 */
#define LL_GPDMA1_TRIGGER_GPU2D_FLAG2     55U /*!< GPDMA1 HW Trigger signal is GPU2D_FLAG2 */
#define LL_GPDMA1_TRIGGER_GPU2D_FLAG3     56U /*!< GPDMA1 HW Trigger signal is GPU2D_FLAG3 */
#endif /* defined (GPU2D) */
#if defined (GFXTIM)
#define LL_GPDMA1_TRIGGER_GFXTIM_EVT4     59U /*!< GPDMA1 HW Trigger signal is GFXTIM_EVT4 */
#define LL_GPDMA1_TRIGGER_GFXTIM_EVT3     60U /*!< GPDMA1 HW Trigger signal is GFXTIM_EVT3 */
#define LL_GPDMA1_TRIGGER_GFXTIM_EVT2     61U /*!< GPDMA1 HW Trigger signal is GFXTIM_EVT2 */
#define LL_GPDMA1_TRIGGER_GFXTIM_EVT1     62U /*!< GPDMA1 HW Trigger signal is GFXTIM_EVT1 */
#endif /* defined (GFXTIM) */
#if defined (JPEG)
#define LL_GPDMA1_TRIGGER_JPEG_EOC_TRG    63U /*!< GPDMA1 HW Trigger signal is JPEG_EOC_TRG  */
#define LL_GPDMA1_TRIGGER_JPEG_IFNF_TRG   64U /*!< GPDMA1 HW Trigger signal is JPEG_IFNF_TRG */
#define LL_GPDMA1_TRIGGER_JPEG_IFT_TRG    65U /*!< GPDMA1 HW Trigger signal is JPEG_IFT_TRG  */
#define LL_GPDMA1_TRIGGER_JPEG_OFNE_TRG   66U /*!< GPDMA1 HW Trigger signal is JPEG_OFNE_TRG */
#define LL_GPDMA1_TRIGGER_JPEG_OFT_TRG    67U /*!< GPDMA1 HW Trigger signal is JPEG_OFT_TRG  */
#endif /* defined (JPEG) */

/* GPDMA1 Hardware Triggers Aliases */
#define LL_GPDMA1_TRIGGER_EXTI_LINE0      LL_GPDMA1_TRIGGER_EXTI0
#define LL_GPDMA1_TRIGGER_EXTI_LINE1      LL_GPDMA1_TRIGGER_EXTI1
#define LL_GPDMA1_TRIGGER_EXTI_LINE2      LL_GPDMA1_TRIGGER_EXTI2
#define LL_GPDMA1_TRIGGER_EXTI_LINE3      LL_GPDMA1_TRIGGER_EXTI3
#define LL_GPDMA1_TRIGGER_EXTI_LINE4      LL_GPDMA1_TRIGGER_EXTI4
#define LL_GPDMA1_TRIGGER_EXTI_LINE5      LL_GPDMA1_TRIGGER_EXTI5
#define LL_GPDMA1_TRIGGER_EXTI_LINE6      LL_GPDMA1_TRIGGER_EXTI6
#define LL_GPDMA1_TRIGGER_EXTI_LINE7      LL_GPDMA1_TRIGGER_EXTI7
#define LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH0_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH1_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH2_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH3_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH4_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH5_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH6_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH7_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH8_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH8_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH9_TCF  LL_GPDMA1_TRIGGER_GPDMA1_CH9_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH10_TCF LL_GPDMA1_TRIGGER_GPDMA1_CH10_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH11_TCF LL_GPDMA1_TRIGGER_GPDMA1_CH11_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH12_TCF LL_GPDMA1_TRIGGER_GPDMA1_CH12_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH13_TCF LL_GPDMA1_TRIGGER_GPDMA1_CH13_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH14_TCF LL_GPDMA1_TRIGGER_GPDMA1_CH14_TC
#define LL_GPDMA1_TRIGGER_GPDMA1_CH15_TCF LL_GPDMA1_TRIGGER_GPDMA1_CH15_TC
#define LL_GPDMA1_TRIGGER_LPDMA1_CH0_TCF  LL_GPDMA1_TRIGGER_LPDMA1_CH0_TC
#define LL_GPDMA1_TRIGGER_LPDMA1_CH1_TCF  LL_GPDMA1_TRIGGER_LPDMA1_CH1_TC
#define LL_GPDMA1_TRIGGER_LPDMA1_CH2_TCF  LL_GPDMA1_TRIGGER_LPDMA1_CH2_TC
#define LL_GPDMA1_TRIGGER_LPDMA1_CH3_TCF  LL_GPDMA1_TRIGGER_LPDMA1_CH3_TC
#define LL_GPDMA1_TRIGGER_JPEG_EOC        LL_GPDMA1_TRIGGER_JPEG_EOC_TRG
#define LL_GPDMA1_TRIGGER_JPEG_IFNF       LL_GPDMA1_TRIGGER_JPEG_IFNF_TRG
#define LL_GPDMA1_TRIGGER_JPEG_IFT        LL_GPDMA1_TRIGGER_JPEG_IFT_TRG
#define LL_GPDMA1_TRIGGER_JPEG_OFNE       LL_GPDMA1_TRIGGER_JPEG_OFNE_TRG
#define LL_GPDMA1_TRIGGER_JPEG_OFT        LL_GPDMA1_TRIGGER_JPEG_OFT_TRG

/* LPDMA1 triggers */
#define LL_LPDMA1_TRIGGER_EXTI0           0U  /*!< LPDMA1 HW Trigger is EXTI0           */
#define LL_LPDMA1_TRIGGER_EXTI1           1U  /*!< LPDMA1 HW Trigger is EXTI1           */
#define LL_LPDMA1_TRIGGER_EXTI2           2U  /*!< LPDMA1 HW Trigger is EXTI2           */
#define LL_LPDMA1_TRIGGER_EXTI3           3U  /*!< LPDMA1 HW Trigger is EXTI3           */
#define LL_LPDMA1_TRIGGER_EXTI4           4U  /*!< LPDMA1 HW Trigger is EXTI4           */
#define LL_LPDMA1_TRIGGER_TAMP_TRG1       5U  /*!< LPDMA1 HW Trigger is TAMP_TRG1       */
#define LL_LPDMA1_TRIGGER_TAMP_TRG2       6U  /*!< LPDMA1 HW Trigger is TAMP_TRG2       */
#define LL_LPDMA1_TRIGGER_TAMP_TRG3       7U  /*!< LPDMA1 HW Trigger is TAMP_TRG3       */
#define LL_LPDMA1_TRIGGER_LPTIM1_CH1      8U  /*!< LPDMA1 HW Trigger is LPTIM1_CH1      */
#define LL_LPDMA1_TRIGGER_LPTIM1_CH2      9U  /*!< LPDMA1 HW Trigger is LPTIM1_CH2      */
#define LL_LPDMA1_TRIGGER_LPTIM3_CH1      10U /*!< LPDMA1 HW Trigger is LPTIM3_CH1      */
#define LL_LPDMA1_TRIGGER_LPTIM4_OUT      11U /*!< LPDMA1 HW Trigger is LPTIM4_OUT      */
#define LL_LPDMA1_TRIGGER_COMP1_OUT       12U /*!< LPDMA1 HW Trigger is COMP1_OUT       */
#define LL_LPDMA1_TRIGGER_COMP2_OUT       13U /*!< LPDMA1 HW Trigger is COMP2_OUT       */
#define LL_LPDMA1_TRIGGER_RTC_ALRA_TRG    14U /*!< LPDMA1 HW Trigger is RTC_ALRA_TRG    */
#define LL_LPDMA1_TRIGGER_RTC_ALRB_TRG    15U /*!< LPDMA1 HW Trigger is RTC_ALRB_TRG    */
#define LL_LPDMA1_TRIGGER_RTC_WUT_TRG     16U /*!< LPDMA1 HW Trigger is RTC_WUT_TRG     */
#define LL_LPDMA1_TRIGGER_ADC4_AWD1       17U /*!< LPDMA1 HW Trigger is ADC4_AWD1       */
#define LL_LPDMA1_TRIGGER_LPDMA1_CH0_TC   18U /*!< LPDMA1 HW Trigger is LPDMA1_CH0_TC   */
#define LL_LPDMA1_TRIGGER_LPDMA1_CH1_TC   19U /*!< LPDMA1 HW Trigger is LPDMA1_CH1_TC   */
#define LL_LPDMA1_TRIGGER_LPDMA1_CH2_TC   20U /*!< LPDMA1 HW Trigger is LPDMA1_CH2_TC   */
#define LL_LPDMA1_TRIGGER_LPDMA1_CH3_TC   21U /*!< LPDMA1 HW Trigger is LPDMA1_CH3_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH0_TC   22U /*!< LPDMA1 HW Trigger is GPDMA1_CH0_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH1_TC   23U /*!< LPDMA1 HW Trigger is GPDMA1_CH1_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH4_TC   24U /*!< LPDMA1 HW Trigger is GPDMA1_CH4_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH5_TC   25U /*!< LPDMA1 HW Trigger is GPDMA1_CH5_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH6_TC   26U /*!< LPDMA1 HW Trigger is GPDMA1_CH6_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH7_TC   27U /*!< LPDMA1 HW Trigger is GPDMA1_CH7_TC   */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH12_TC  28U /*!< LPDMA1 HW Trigger is GPDMA1_CH12_TC  */
#define LL_LPDMA1_TRIGGER_GPDMA1_CH13_TC  29U /*!< LPDMA1 HW Trigger is GPDMA1_CH13_TC  */
#define LL_LPDMA1_TRIGGER_TIM2_TRGO       30U /*!< LPDMA1 HW Trigger is TIM2_TRGO       */
#define LL_LPDMA1_TRIGGER_TIM15_TRGO      31U /*!< LPDMA1 HW Trigger is TIM15_TRGO      */

/* LPDMA1 Hardware Triggers Aliases */
#define LL_LPDMA1_TRIGGER_EXTI_LINE0      LL_LPDMA1_TRIGGER_EXTI0
#define LL_LPDMA1_TRIGGER_EXTI_LINE1      LL_LPDMA1_TRIGGER_EXTI1
#define LL_LPDMA1_TRIGGER_EXTI_LINE2      LL_LPDMA1_TRIGGER_EXTI2
#define LL_LPDMA1_TRIGGER_EXTI_LINE3      LL_LPDMA1_TRIGGER_EXTI3
#define LL_LPDMA1_TRIGGER_EXTI_LINE4      LL_LPDMA1_TRIGGER_EXTI4
#define LL_LPDMA1_TRIGGER_LPDMA1_CH0_TCF  LL_LPDMA1_TRIGGER_LPDMA1_CH0_TC
#define LL_LPDMA1_TRIGGER_LPDMA1_CH1_TCF  LL_LPDMA1_TRIGGER_LPDMA1_CH1_TC
#define LL_LPDMA1_TRIGGER_LPDMA1_CH2_TCF  LL_LPDMA1_TRIGGER_LPDMA1_CH2_TC
#define LL_LPDMA1_TRIGGER_LPDMA1_CH3_TCF  LL_LPDMA1_TRIGGER_LPDMA1_CH3_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH0_TCF  LL_LPDMA1_TRIGGER_GPDMA1_CH0_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH1_TCF  LL_LPDMA1_TRIGGER_GPDMA1_CH1_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH4_TCF  LL_LPDMA1_TRIGGER_GPDMA1_CH4_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH5_TCF  LL_LPDMA1_TRIGGER_GPDMA1_CH5_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH6_TCF  LL_LPDMA1_TRIGGER_GPDMA1_CH6_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH7_TCF  LL_LPDMA1_TRIGGER_GPDMA1_CH7_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH12_TCF LL_LPDMA1_TRIGGER_GPDMA1_CH12_TC
#define LL_LPDMA1_TRIGGER_GPDMA1_CH13_TCF LL_LPDMA1_TRIGGER_GPDMA1_CH13_TC
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup DMA_LL_Exported_Macros DMA Exported Macros
  * @{
  */

/** @defgroup DMA_LL_EM_COMMON_WRITE_READ_REGISTERS Common Write and Read Registers macros
  * @{
  */
/**
  * @brief  Write a value in DMA register.
  * @param  instance DMA Instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_DMA_WRITE_REG(instance, reg, value) WRITE_REG(((instance)->reg), (value))

/**
  * @brief  Modify a value in DMA register.
  * @param  instance DMA Instance.
  * @param  reg      Register to be written.
  * @param  mask     Mask to be clearing.
  * @param  value    Value to be written in the register.
  */
#define LL_DMA_MODIFY_REG(instance, reg, mask, value) MODIFY_REG(((instance)->reg), (mask), (value))

/**
  * @brief  Read a value in DMA register.
  * @param  instance DMA Instance.
  * @param  reg      Register to be read.
  * @retval Register value.
  */
#define LL_DMA_READ_REG(instance, reg) READ_REG(instance->reg)
/**
  * @}
  */

/** @defgroup DMA_LL_EM_CONVERT_dmaxCHANNELy Convert dmaxChannely
  * @{
  */
/**
  * @brief  Convert dmax_CHy into dmax.
  * @param  channel_instance dmax_CHy.
  * @retval dmax.
  */
#define LL_DMA_GET_INSTANCE(channel_instance) \
  (((uint32_t)(channel_instance) > ((uint32_t)GPDMA1_CH15)) ?  LPDMA1 : GPDMA1)

/**
  * @brief  Convert dmax_CHy into LL_DMA_CHANNEL_y.
  * @param  channel_instance dmax_CHy.
  * @retval LL_DMA_CHANNEL_y.
  */
#define LL_DMA_GET_CHANNEL_IDX(channel_instance) \
  (((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH0))  ? LL_DMA_CHANNEL_0  : \
   ((uint32_t)(channel_instance) == ((uint32_t)LPDMA1_CH0))  ? LL_DMA_CHANNEL_0  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH1))  ? LL_DMA_CHANNEL_1  : \
   ((uint32_t)(channel_instance) == ((uint32_t)LPDMA1_CH1))  ? LL_DMA_CHANNEL_1  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH2))  ? LL_DMA_CHANNEL_2  : \
   ((uint32_t)(channel_instance) == ((uint32_t)LPDMA1_CH2))  ? LL_DMA_CHANNEL_2  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH3))  ? LL_DMA_CHANNEL_3  : \
   ((uint32_t)(channel_instance) == ((uint32_t)LPDMA1_CH3))  ? LL_DMA_CHANNEL_3  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH4))  ? LL_DMA_CHANNEL_4  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH5))  ? LL_DMA_CHANNEL_5  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH6))  ? LL_DMA_CHANNEL_6  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH7))  ? LL_DMA_CHANNEL_7  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH8))  ? LL_DMA_CHANNEL_8  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH9))  ? LL_DMA_CHANNEL_9  : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH10)) ? LL_DMA_CHANNEL_10 : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH11)) ? LL_DMA_CHANNEL_11 : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH12)) ? LL_DMA_CHANNEL_12 : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH13)) ? LL_DMA_CHANNEL_13 : \
   ((uint32_t)(channel_instance) == ((uint32_t)GPDMA1_CH14)) ? LL_DMA_CHANNEL_14 : \
   LL_DMA_CHANNEL_15)

/**
  * @brief  Convert DMA Instance dmax and LL_DMA_CHANNEL_y into dmax_CHy.
  * @param  dma_instance dmax.
  * @param  channel      LL_DMA_CHANNEL_y.
  * @retval dmax_CHy.
  */
#define LL_DMA_GET_CHANNEL_INSTANCE(dma_instance, channel) \
  ((((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_0))) \
   ? GPDMA1_CH0  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)LPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_0))) \
   ? LPDMA1_CH0  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_1))) \
   ? GPDMA1_CH1  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)LPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_1))) \
   ? LPDMA1_CH1  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_2))) \
   ? GPDMA1_CH2  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)LPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_2))) \
   ? LPDMA1_CH2  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_3))) \
   ? GPDMA1_CH3  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)LPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_3))) \
   ? LPDMA1_CH3  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_4))) \
   ? GPDMA1_CH4  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_5))) \
   ? GPDMA1_CH5  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_6))) \
   ? GPDMA1_CH6  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_7))) \
   ? GPDMA1_CH7  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_8))) \
   ? GPDMA1_CH8  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_9))) \
   ? GPDMA1_CH9  :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_10)))\
   ? GPDMA1_CH10 :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_11)))\
   ? GPDMA1_CH11 :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_12)))\
   ? GPDMA1_CH12 :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_13)))\
   ? GPDMA1_CH13 :                                                                                        \
   (((uint32_t)(dma_instance) == ((uint32_t)GPDMA1)) && ((uint32_t)(channel) == ((uint32_t)LL_DMA_CHANNEL_14)))\
   ? GPDMA1_CH14 :  GPDMA1_CH15)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DMA_LL_Exported_Functions DMA Exported Functions
  * @{
  */

/** @defgroup DMA_LL_EF_Configuration Configuration
  * @{
  */
/**
  * @brief  Enable channel.
  * @rmtoll
  *  CCR          EN            LL_DMA_EnableChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableChannel(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_EN);
}

/**
  * @brief  Disable channel.
  * @rmtoll
  *  CCR          EN            LL_DMA_DisableChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableChannel(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, (DMA_CCR_SUSP | DMA_CCR_RESET));
}

/**
  * @brief  Check if channel is enabled or disabled.
  * @rmtoll
  *  CCR          EN            LL_DMA_IsEnabledChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledChannel(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_EN) == (DMA_CCR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Reset channel.
  * @rmtoll
  *  CCR          RESET            LL_DMA_ResetChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ResetChannel(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_RESET);
}

/**
  * @brief  Suspend channel.
  * @rmtoll
  *  CCR          SUSP            LL_DMA_SuspendChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_SuspendChannel(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_SUSP);
}

/**
  * @brief  Resume channel.
  * @rmtoll
  *  CCR          SUSP            LL_DMA_ResumeChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ResumeChannel(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_SUSP);
}

/**
  * @brief  Check if channel is suspended.
  * @rmtoll
  *  CCR          SUSP            LL_DMA_IsSuspendedChannel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsSuspendedChannel(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_SUSP)
           == (DMA_CCR_SUSP)) ? 1UL : 0UL);
}

/**
  * @brief  Set linked-list base address.
  * @rmtoll
  *  CLBAR          LBA           LL_DMA_SetLinkedListBaseAddr
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  linked_list_base_addr Between 0 and 0xFFFF0000 (where the 4 LSB bytes are always 0)
  */
__STATIC_INLINE void LL_DMA_SetLinkedListBaseAddr(DMA_Channel_TypeDef *channel, uint32_t linked_list_base_addr)
{
  MODIFY_REG(channel->CLBAR, DMA_CLBAR_LBA, (linked_list_base_addr & DMA_CLBAR_LBA));
}

/**
  * @brief  Get linked-list base address.
  * @rmtoll
  *  CLBAR          LBA           LL_DMA_GetLinkedListBaseAddr
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Value between 0 and 0xFFFF0000 (where the 4 LSB bytes are always 0)
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkedListBaseAddr(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CLBAR, DMA_CLBAR_LBA));
}

/**
  * @brief  Configure all parameters linked to channel control.
  * @rmtoll
  *  CCR         PRIO           LL_DMA_ConfigControl \n
  *  CCR         LAP            LL_DMA_ConfigControl \n
  *  CCR         LSM            LL_DMA_ConfigControl
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_LOW  or @ref LL_DMA_PRIORITY_LOW_WEIGHT_MID or
  *              @ref LL_DMA_PRIORITY_LOW_WEIGHT_HIGH or @ref LL_DMA_PRIORITY_HIGH
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT0     or @ref LL_DMA_LINK_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_LINKEDLIST_EXECUTION_Q   or @ref LL_DMA_LINKEDLIST_EXECUTION_NODE
  */
__STATIC_INLINE void LL_DMA_ConfigControl(DMA_Channel_TypeDef *channel, uint32_t configuration)
{
  MODIFY_REG(channel->CCR, (DMA_CCR_PRIO | DMA_CCR_LAP | DMA_CCR_LSM), configuration);
}

/**
  * @brief  Set priority level.
  * @rmtoll
  *  CCR          PRIO           LL_DMA_SetChannelPriorityLevel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  priority This parameter can be one of the following values:
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_LOW
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_MID
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_HIGH
  *         @arg @ref LL_DMA_PRIORITY_HIGH
  */
__STATIC_INLINE void LL_DMA_SetChannelPriorityLevel(DMA_Channel_TypeDef *channel, uint32_t priority)
{
  MODIFY_REG(channel->CCR, DMA_CCR_PRIO, priority);
}

/**
  * @brief  Get channel priority level.
  * @rmtoll
  *  CCR          PRIO           LL_DMA_GetChannelPriorityLevel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_LOW
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_MID
  *         @arg @ref LL_DMA_PRIORITY_LOW_WEIGHT_HIGH
  *         @arg @ref LL_DMA_PRIORITY_HIGH
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelPriorityLevel(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CCR, DMA_CCR_PRIO));
}

/**
  * @brief  Set linked-list allocated port.
  * @rmtoll
  *  CCR          LAP           LL_DMA_SetLinkAllocatedPort
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  link_allocated_port This parameter can be one of the following values:
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT1
  */
__STATIC_INLINE void LL_DMA_SetLinkAllocatedPort(DMA_Channel_TypeDef *channel, uint32_t link_allocated_port)
{
  MODIFY_REG(channel->CCR, DMA_CCR_LAP, link_allocated_port);
}

/**
  * @brief  Get linked-list allocated port.
  * @rmtoll
  *  CCR          LAP           LL_DMA_GetLinkAllocatedPort
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_LINK_ALLOCATED_PORT1
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkAllocatedPort(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CCR, DMA_CCR_LAP));
}

/**
  * @brief  Set link step mode.
  * @rmtoll
  *  CCR          LSM           LL_DMA_SetLinkStepMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  link_step_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_LINKEDLIST_EXECUTION_Q
  *         @arg @ref LL_DMA_LINKEDLIST_EXECUTION_NODE
  */
__STATIC_INLINE void LL_DMA_SetLinkStepMode(DMA_Channel_TypeDef *channel, uint32_t link_step_mode)
{
  MODIFY_REG(channel->CCR, DMA_CCR_LSM, link_step_mode);
}

/**
  * @brief  Get Link step mode.
  * @rmtoll
  *  CCR          LSM           LL_DMA_GetLinkStepMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_LINKEDLIST_EXECUTION_Q
  *         @arg @ref LL_DMA_LINKEDLIST_EXECUTION_NODE
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkStepMode(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CCR, DMA_CCR_LSM));
}

/**
  * @brief  Configure transfer.
  * @rmtoll
  *  CTR1          DINC          LL_DMA_ConfigTransfer \n
  *  CTR1          SINC          LL_DMA_ConfigTransfer \n
  *  CTR1          DHX           LL_DMA_ConfigTransfer \n
  *  CTR1          DBX           LL_DMA_ConfigTransfer \n
  *  CTR1          SBX           LL_DMA_ConfigTransfer \n
  *  CTR1          DAP           LL_DMA_ConfigTransfer \n
  *  CTR1          SAP           LL_DMA_ConfigTransfer \n
  *  CTR1          PAM           LL_DMA_ConfigTransfer
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0     or @ref LL_DMA_DEST_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVED  or @ref LL_DMA_DEST_HALFWORD_EXCHANGED
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVED      or @ref LL_DMA_DEST_BYTE_EXCHANGED
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVED       or @ref LL_DMA_SRC_BYTE_EXCHANGED
  *         @arg @ref LL_DMA_DEST_ADDR_FIXED          or @ref LL_DMA_DEST_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_BYTE     or @ref LL_DMA_DEST_DATA_WIDTH_HALFWORD or
  *              @ref LL_DMA_DEST_DATA_WIDTH_WORD
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0      or @ref LL_DMA_SRC_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO or @ref LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN   or
  *              @ref LL_DMA_DEST_DATA_PACKED_UNPACKED
  *         @arg @ref LL_DMA_SRC_ADDR_FIXED           or @ref LL_DMA_SRC_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_BYTE      or @ref LL_DMA_SRC_DATA_WIDTH_HALFWORD  or
  *              @ref LL_DMA_SRC_DATA_WIDTH_WORD
  */
__STATIC_INLINE void LL_DMA_ConfigTransfer(DMA_Channel_TypeDef *channel, uint32_t configuration)
{
  MODIFY_REG(channel->CTR1,
             DMA_CTR1_DAP | DMA_CTR1_SAP |
             DMA_CTR1_DHX | DMA_CTR1_DBX | DMA_CTR1_SBX |
             DMA_CTR1_DINC | DMA_CTR1_SINC | DMA_CTR1_PAM | DMA_CTR1_DDW_LOG2 | DMA_CTR1_SDW_LOG2, configuration);
}

/**
  * @brief  Configure data transfer.
  * @rmtoll
  *  CTR1          DINC          LL_DMA_ConfigDataTransfer \n
  *  CTR1          SINC          LL_DMA_ConfigDataTransfer \n
  *  CTR1          SDW_LOG2      LL_DMA_ConfigDataTransfer \n
  *  CTR1          DDW_LOG2      LL_DMA_ConfigDataTransfer
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DEST_ADDR_FIXED
              or @ref LL_DMA_DEST_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_BYTE
              or @ref LL_DMA_DEST_DATA_WIDTH_HALFWORD
              or @ref LL_DMA_DEST_DATA_WIDTH_WORD
  *         @arg @ref LL_DMA_SRC_ADDR_FIXED
              or @ref LL_DMA_SRC_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_BYTE
              or @ref LL_DMA_SRC_DATA_WIDTH_HALFWORD
              or @ref LL_DMA_SRC_DATA_WIDTH_WORD
  */
__STATIC_INLINE void LL_DMA_ConfigDataTransfer(DMA_Channel_TypeDef *channel, uint32_t configuration)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DINC | DMA_CTR1_SINC | DMA_CTR1_DDW_LOG2 | DMA_CTR1_SDW_LOG2, configuration);
}

/**
  * @brief  Configure data handling.
  * @rmtoll
  *  CTR1          DHX           LL_DMA_ConfigDataHandling \n
  *  CTR1          DBX           LL_DMA_ConfigDataHandling \n
  *  CTR1          SBX           LL_DMA_ConfigDataHandling \n
  *  CTR1          PAM           LL_DMA_ConfigDataHandling
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVED         or @ref LL_DMA_DEST_HALFWORD_EXCHANGED
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVED             or @ref LL_DMA_DEST_BYTE_EXCHANGED
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVED              or @ref LL_DMA_SRC_BYTE_EXCHANGED
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO or @ref LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN or
  *              @ref LL_DMA_DEST_DATA_PACKED_UNPACKED
  */
__STATIC_INLINE void LL_DMA_ConfigDataHandling(DMA_Channel_TypeDef *channel, uint32_t configuration)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DHX | DMA_CTR1_DBX | DMA_CTR1_SBX | DMA_CTR1_PAM, configuration);
}

/**
  * @brief  Configure access ports.
  * @rmtoll
  *  CTR1          DAP           LL_DMA_ConfigAccessPorts \n
  *  CTR1          SAP           LL_DMA_ConfigAccessPorts
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  access_ports This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0 or @ref LL_DMA_DEST_ALLOCATED_PORT1
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0  or @ref LL_DMA_SRC_ALLOCATED_PORT1
  */
__STATIC_INLINE void LL_DMA_ConfigAccessPorts(DMA_Channel_TypeDef *channel, uint32_t access_ports)
{
  MODIFY_REG(channel->CTR1, (DMA_CTR1_DAP | DMA_CTR1_SAP), access_ports);
}

/**
  * @brief  Configure source and destination burst length.
  * @rmtoll
  *  CTR1          DBL_1           LL_DMA_ConfigBurstLength \n
  *  CTR1          SBL_1           LL_DMA_ConfigBurstLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  src_burst_length Between 1 and 64
  * @param  dest_burst_length Between 1 and 64
  */
__STATIC_INLINE void LL_DMA_ConfigBurstLength(DMA_Channel_TypeDef *channel, uint32_t src_burst_length,
                                              uint32_t dest_burst_length)
{
  MODIFY_REG(channel->CTR1, (DMA_CTR1_SBL_1 | DMA_CTR1_DBL_1),
             (((src_burst_length - 1U) << DMA_CTR1_SBL_1_Pos) & DMA_CTR1_SBL_1) | \
             (((dest_burst_length - 1U) << DMA_CTR1_DBL_1_Pos) & DMA_CTR1_DBL_1));
}

/**
  * @brief  Set destination allocated port.
  * @rmtoll
  *  CTR1          DAP           LL_DMA_SetDestAllocatedPort
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_allocated_port This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT1
  */
__STATIC_INLINE void LL_DMA_SetDestAllocatedPort(DMA_Channel_TypeDef *channel, uint32_t dest_allocated_port)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DAP, dest_allocated_port);
}

/**
  * @brief  Get destination allocated port.
  * @rmtoll
  *  CTR1          DAP           LL_DMA_GetDestAllocatedPort
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_DEST_ALLOCATED_PORT1
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestAllocatedPort(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_DAP));
}

/**
  * @brief  Set destination half-word exchange.
  * @rmtoll
  *  CTR1          DHX            LL_DMA_SetDestHWordExchange
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_halfword_exchange This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVED
  *         @arg @ref LL_DMA_DEST_HALFWORD_EXCHANGED
  */
__STATIC_INLINE void LL_DMA_SetDestHWordExchange(DMA_Channel_TypeDef *channel, uint32_t dest_halfword_exchange)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DHX, dest_halfword_exchange);
}

/**
  * @brief  Get destination half-word exchange.
  * @rmtoll
  *  CTR1          DHX            LL_DMA_GetDestHWordExchange
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_HALFWORD_PRESERVED
  *         @arg @ref LL_DMA_DEST_HALFWORD_EXCHANGED
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestHWordExchange(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_DHX));
}

/**
  * @brief  Set destination byte exchange.
  * @rmtoll
  *  CTR1          DBX            LL_DMA_SetDestByteExchange
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_byte_exchange This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVED
  *         @arg @ref LL_DMA_DEST_BYTE_EXCHANGED
  */
__STATIC_INLINE void LL_DMA_SetDestByteExchange(DMA_Channel_TypeDef *channel, uint32_t dest_byte_exchange)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DBX, dest_byte_exchange);
}

/**
  * @brief  Get destination byte exchange.
  * @rmtoll
  *  CTR1          DBX            LL_DMA_GetDestByteExchange
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_BYTE_PRESERVED
  *         @arg @ref LL_DMA_DEST_BYTE_EXCHANGED
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestByteExchange(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_DBX));
}

/**
  * @brief  Set source byte exchange.
  * @rmtoll
  *  CTR1          SBX            LL_DMA_SetSrcByteExchange
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  src_byte_exchange This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVED
  *         @arg @ref LL_DMA_SRC_BYTE_EXCHANGED
  */
__STATIC_INLINE void LL_DMA_SetSrcByteExchange(DMA_Channel_TypeDef *channel, uint32_t src_byte_exchange)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_SBX, src_byte_exchange);
}

/**
  * @brief  Get source byte exchange.
  * @rmtoll
  *  CTR1          SBX            LL_DMA_GetSrcByteExchange
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_BYTE_PRESERVED
  *         @arg @ref LL_DMA_SRC_BYTE_EXCHANGED
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcByteExchange(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_SBX));
}

/**
  * @brief  Set destination burst length.
  * @rmtoll
  *  CTR1          DBL_1           LL_DMA_SetDestBurstLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_burst_length Between 1 and 64
  */
__STATIC_INLINE void LL_DMA_SetDestBurstLength(DMA_Channel_TypeDef *channel, uint32_t dest_burst_length)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DBL_1, ((dest_burst_length - 1U) << DMA_CTR1_DBL_1_Pos) & DMA_CTR1_DBL_1);
}

/**
  * @brief  Get destination burst length.
  * @rmtoll
  *  CTR1          DBL_1           LL_DMA_GetDestBurstLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 1 and 64.
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestBurstLength(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CTR1, DMA_CTR1_DBL_1) >> DMA_CTR1_DBL_1_Pos) + 1U);
}

/**
  * @brief  Set destination increment mode.
  * @rmtoll
  *  CTR1          DINC           LL_DMA_SetDestIncMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  dest_inc This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_ADDR_FIXED
  *         @arg @ref LL_DMA_DEST_ADDR_INCREMENTED
  */
__STATIC_INLINE void LL_DMA_SetDestIncMode(DMA_Channel_TypeDef *channel, uint32_t dest_inc)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DINC, dest_inc);
}

/**
  * @brief  Get destination increment mode.
  * @rmtoll
  *  CTR1          DINC           LL_DMA_GetDestIncMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_ADDR_FIXED
  *         @arg @ref LL_DMA_DEST_ADDR_INCREMENTED
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestIncMode(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_DINC));
}

/**
  * @brief  Set destination data width.
  * @rmtoll
  *  CTR1          DDW_LOG2           LL_DMA_SetDestDataWidth
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  dest_data_width This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_BYTE
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_HALFWORD
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_WORD
  */
__STATIC_INLINE void LL_DMA_SetDestDataWidth(DMA_Channel_TypeDef *channel, uint32_t dest_data_width)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DDW_LOG2, dest_data_width);
}

/**
  * @brief  Get destination data width.
  * @rmtoll
  *  CTR1          DDW_LOG2           LL_DMA_GetDestDataWidth
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_BYTE
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_HALFWORD
  *         @arg @ref LL_DMA_DEST_DATA_WIDTH_WORD
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestDataWidth(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_DDW_LOG2));
}

/**
  * @brief  Set source allocated port.
  * @rmtoll
  *  CTR1          SAP           LL_DMA_SetSrcAllocatedPort
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  src_allocated_port This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT1
  */
__STATIC_INLINE void LL_DMA_SetSrcAllocatedPort(DMA_Channel_TypeDef *channel, uint32_t src_allocated_port)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_SAP, src_allocated_port);
}

/**
  * @brief  Get source allocated port.
  * @rmtoll
  *  CTR1          SAP           LL_DMA_GetSrcAllocatedPort
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT0
  *         @arg @ref LL_DMA_SRC_ALLOCATED_PORT1
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAllocatedPort(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_SAP));
}

/**
  * @brief  Set DMA channel destination data packing.
  * @rmtoll
  *  CTR1          PAM           LL_DMA_SetDataPacking
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  data_pack This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_PRESERVED
  *         @arg @ref LL_DMA_DEST_DATA_PACKED_UNPACKED
  */
__STATIC_INLINE void LL_DMA_SetDataPacking(DMA_Channel_TypeDef *channel, uint32_t data_pack)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_PAM_1, data_pack);
}

/**
  * @brief  Get DMA channel destination data packing.
  * @rmtoll
  *  CTR1          PAM           LL_DMA_GetDataPacking
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_PRESERVED
  *         @arg @ref LL_DMA_DEST_DATA_PACKED_UNPACKED
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataPacking(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_PAM_1));
}

/**
  * @brief  Set DMA channel destination data truncation and passing.
  * @rmtoll
  *  CTR1          PAM           LL_DMA_SetDataTruncPadd
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  data_trunc_padd This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN
  */
__STATIC_INLINE void LL_DMA_SetDataTruncPadd(DMA_Channel_TypeDef *channel, uint32_t data_trunc_padd)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_PAM_0, data_trunc_padd);
}

/**
  * @brief  Get DMA channel destination data truncation and passing.
  * @rmtoll
  *  CTR1          PAM           LL_DMA_GetDataTruncPadd
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataTruncPadd(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_PAM_0));
}

/**
  * @brief  Set data alignment mode.
  * @rmtoll
  *  CTR1          PAM           LL_DMA_SetDataAlignment
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  data_alignment This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN
  *         @arg @ref LL_DMA_DEST_DATA_PACKED_UNPACKED
  */
__STATIC_INLINE void LL_DMA_SetDataAlignment(DMA_Channel_TypeDef *channel, uint32_t data_alignment)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_PAM, data_alignment);
}

/**
  * @brief  Get data alignment mode.
  * @rmtoll
  *  CTR1          PAM           LL_DMA_GetDataAlignment
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO
  *         @arg @ref LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN
  *         @arg @ref LL_DMA_DEST_DATA_PACKED_UNPACKED
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataAlignment(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_PAM));
}

/**
  * @brief  Set source burst length.
  * @rmtoll
  *  CTR1          SBL_1           LL_DMA_SetSrcBurstLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  src_burst_length Between 1 and 64
  */
__STATIC_INLINE void LL_DMA_SetSrcBurstLength(DMA_Channel_TypeDef *channel, uint32_t src_burst_length)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_SBL_1, ((src_burst_length - 1U) << DMA_CTR1_SBL_1_Pos) & DMA_CTR1_SBL_1);
}

/**
  * @brief  Get source burst length.
  * @rmtoll
  *  CTR1          SBL_1           LL_DMA_GetSrcBurstLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 1 and 64
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcBurstLength(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CTR1, DMA_CTR1_SBL_1) >> DMA_CTR1_SBL_1_Pos) + 1U);
}

/**
  * @brief  Set source increment mode.
  * @rmtoll
  *  CTR1          SINC           LL_DMA_SetSrcIncMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  src_inc This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_ADDR_FIXED
  *         @arg @ref LL_DMA_SRC_ADDR_INCREMENTED
  */
__STATIC_INLINE void LL_DMA_SetSrcIncMode(DMA_Channel_TypeDef *channel, uint32_t src_inc)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_SINC, src_inc);
}

/**
  * @brief  Get source increment mode.
  * @rmtoll
  *  CTR1          SINC           LL_DMA_GetSrcIncMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_ADDR_FIXED
  *         @arg @ref LL_DMA_SRC_ADDR_INCREMENTED
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcIncMode(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_SINC));
}

/**
  * @brief  Set source data width.
  * @rmtoll
  *  CTR1          SDW_LOG2           LL_DMA_SetSrcDataWidth
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  src_data_width This parameter can be one of the following values:
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_BYTE
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_HALFWORD
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_WORD
  */
__STATIC_INLINE void LL_DMA_SetSrcDataWidth(DMA_Channel_TypeDef *channel, uint32_t src_data_width)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_SDW_LOG2, src_data_width);
}

/**
  * @brief  Get Source Data width.
  * @rmtoll
  *  CTR1          SDW_LOG2           LL_DMA_GetSrcDataWidth
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_BYTE
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_HALFWORD
  *         @arg @ref LL_DMA_SRC_DATA_WIDTH_WORD
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcDataWidth(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR1, DMA_CTR1_SDW_LOG2));
}

/**
  * @brief  Configure channel transfer.
  * @rmtoll
  *  CTR2        TCEM               LL_DMA_ConfigChannelTransfer \n
  *  CTR2        TRIGPOL            LL_DMA_ConfigChannelTransfer \n
  *  CTR2        TRIGM              LL_DMA_ConfigChannelTransfer \n
  *  CTR2        BREQ               LL_DMA_ConfigChannelTransfer \n
  *  CTR2        DREQ               LL_DMA_ConfigChannelTransfer \n
  *  CTR2        SWREQ              LL_DMA_ConfigChannelTransfer
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_DIRECT_XFER_EVENT_BLOCK           or @ref LL_DMA_LINKEDLIST_XFER_EVENT_BLOCK
  *              @ref LL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK  or  LL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK
  *              @ref LL_DMA_LINKEDLIST_XFER_EVENT_NODE        or @ref LL_DMA_LINKEDLIST_XFER_EVENT_Q
  *         @arg @ref LL_DMA_HARDWARE_REQUEST_BURST            or @ref LL_DMA_HARDWARE_REQUEST_BLOCK
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_MASKED           or @ref LL_DMA_TRIGGER_POLARITY_RISING         or
  *              @ref LL_DMA_TRIGGER_POLARITY_FALLING
  *         @arg @ref LL_DMA_TRIGGER_BLOCK_TRANSFER            or @ref LL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER or
  *              @ref LL_DMA_TRIGGER_NODE_TRANSFER             or @ref LL_DMA_TRIGGER_SINGLE_BURST_TRANSFER
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY        or @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH      or
  *              @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  */
__STATIC_INLINE void LL_DMA_ConfigChannelTransfer(DMA_Channel_TypeDef *channel, uint32_t configuration)
{
  MODIFY_REG(channel->CTR2, (DMA_CTR2_TCEM | DMA_CTR2_TRIGPOL | DMA_CTR2_TRIGM | DMA_CTR2_DREQ | DMA_CTR2_SWREQ | \
                             DMA_CTR2_BREQ), configuration);
}

/**
  * @brief  Set transfer event mode.
  * @rmtoll
  *  CTR2          TCEM           LL_DMA_SetTransferEventMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  transfer_event_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DIRECT_XFER_EVENT_BLOCK
  *         @arg @ref LL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK
  *         @arg @ref LL_DMA_LINKEDLIST_XFER_EVENT_NODE
  *         @arg @ref LL_DMA_LINKEDLIST_XFER_EVENT_Q
  */
__STATIC_INLINE void LL_DMA_SetTransferEventMode(DMA_Channel_TypeDef *channel, uint32_t transfer_event_mode)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_TCEM, transfer_event_mode);
}

/**
  * @brief  Get transfer event mode.
  * @rmtoll
  *  CTR2          TCEM           LL_DMA_GetTransferEventMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DIRECT_XFER_EVENT_BLOCK
  *         @arg @ref LL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK
  *         @arg @ref LL_DMA_LINKEDLIST_XFER_EVENT_NODE
  *         @arg @ref LL_DMA_LINKEDLIST_XFER_EVENT_Q
  */
__STATIC_INLINE uint32_t LL_DMA_GetTransferEventMode(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_TCEM));
}

/**
  * @brief  Set trigger polarity.
  * @rmtoll
  *  CTR2          TRIGPOL/TRIGM/TRIGSEL            LL_DMA_ConfigChannelTrigger
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  trigger_selection This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM4_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP1_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP2_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH8_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH9_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH10_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH11_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH12_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH13_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH14_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH15_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM15_TRGO
  * @if TIM3_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM3_TRGO
  * @endif
  * @if TIM4_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM4_TRGO
  * @endif
  * @if TIM5_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM5_TRGO
  * @endif
  * @if LTDC
  *         @arg @ref LL_GPDMA1_TRIGGER_LTDC_LI
  * @endif
  * @if DSI
  *         @arg @ref LL_GPDMA1_TRIGGER_DSI_TE
  *         @arg @ref LL_GPDMA1_TRIGGER_DSI_ER
  * @endif
  * @if DMA2D_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_TC
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_CTC
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_TW
  * @endif
  * @if GPU2D
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG0
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG1
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG2
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG3
  * @endif
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC4_AWD1
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC1_AWD1
  *
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE4
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM3_CH1
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM4_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_COMP1_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_COMP2_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH0_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH1_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH2_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH3_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH12_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH13_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_LPDMA1_TRIGGER_TIM15_TRGO
  * @param  trigger_config This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_MASKED
  *           or @ref LL_DMA_TRIGGER_POLARITY_RISING
  *           or @ref LL_DMA_TRIGGER_POLARITY_FALLING
  *         @arg @ref LL_DMA_TRIGGER_BLOCK_TRANSFER
  *           or @ref LL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER
  *           or @ref LL_DMA_TRIGGER_NODE_TRANSFER
  *           or @ref LL_DMA_TRIGGER_SINGLE_BURST_TRANSFER
  */
__STATIC_INLINE void LL_DMA_ConfigChannelTrigger(DMA_Channel_TypeDef *channel, uint32_t trigger_selection,
                                                 uint32_t trigger_config)
{
  MODIFY_REG(channel->CTR2, (DMA_CTR2_TRIGPOL | DMA_CTR2_TRIGM | DMA_CTR2_TRIGSEL),
             (trigger_config | ((trigger_selection << DMA_CTR2_TRIGSEL_Pos) & DMA_CTR2_TRIGSEL)));
}

/**
  * @brief  Set trigger polarity.
  * @rmtoll
  *  CTR2          TRIGPOL            LL_DMA_SetTriggerPolarity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  trigger_polarity This parameter can be one of the following values:
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_MASKED
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_RISING
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_FALLING
  */
__STATIC_INLINE void LL_DMA_SetTriggerPolarity(DMA_Channel_TypeDef *channel, uint32_t trigger_polarity)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_TRIGPOL, trigger_polarity);
}

/**
  * @brief  Get trigger polarity.
  * @rmtoll
  *  CTR2          TRIGPOL            LL_DMA_GetTriggerPolarity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_MASKED
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_RISING
  *         @arg @ref LL_DMA_TRIGGER_POLARITY_FALLING
  */
__STATIC_INLINE uint32_t LL_DMA_GetTriggerPolarity(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_TRIGPOL));
}

/**
  * @brief  Set trigger Mode.
  * @rmtoll
  *  CTR2          TRIGM            LL_DMA_SetTriggerMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  trigger_mode This parameter can be one of the following values:
  *         @arg @ref LL_DMA_TRIGGER_BLOCK_TRANSFER
  *         @arg @ref LL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER (This value is allowed only for 2D addressing channels)
  *         @arg @ref LL_DMA_TRIGGER_NODE_TRANSFER
  *         @arg @ref LL_DMA_TRIGGER_SINGLE_BURST_TRANSFER
  */
__STATIC_INLINE void LL_DMA_SetTriggerMode(DMA_Channel_TypeDef *channel, uint32_t trigger_mode)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_TRIGM, trigger_mode);
}

/**
  * @brief  Get trigger Mode.
  * @rmtoll
  *  CTR2          TRIGM            LL_DMA_GetTriggerMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_TRIGGER_BLOCK_TRANSFER
  *         @arg @ref LL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER (This value is allowed only for 2D addressing channels)
  *         @arg @ref LL_DMA_TRIGGER_NODE_TRANSFER
  *         @arg @ref LL_DMA_TRIGGER_SINGLE_BURST_TRANSFER
  */
__STATIC_INLINE uint32_t LL_DMA_GetTriggerMode(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_TRIGM));
}

/**
  * @brief  Set destination hardware and software transfer request.
  * @rmtoll
  *  CTR2          DREQ           LL_DMA_SetDataTransferDirection \n
  *  CTR2          SWREQ          LL_DMA_SetDataTransferDirection
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  direction This parameter can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  */
__STATIC_INLINE void LL_DMA_SetDataTransferDirection(DMA_Channel_TypeDef *channel, uint32_t direction)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_DREQ | DMA_CTR2_SWREQ, direction);
}

/**
  * @brief  Get destination hardware and software transfer request.
  * @rmtoll
  *  CTR2          DREQ           LL_DMA_GetDataTransferDirection \n
  *  CTR2          SWREQ          LL_DMA_GetDataTransferDirection
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref LL_DMA_DIRECTION_MEMORY_TO_MEMORY
  */
__STATIC_INLINE uint32_t LL_DMA_GetDataTransferDirection(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_DREQ | DMA_CTR2_SWREQ));
}

/**
  * @brief  Set block hardware request.
  * @rmtoll
  *  CTR2          BREQ           LL_DMA_SetHWRequestMode
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  blk_hw_request This parameter can be one of the following values:
  *         @arg @ref LL_DMA_HARDWARE_REQUEST_BURST
  *         @arg @ref LL_DMA_HARDWARE_REQUEST_BLOCK
  */
__STATIC_INLINE void LL_DMA_SetHWRequestMode(DMA_Channel_TypeDef *channel, uint32_t blk_hw_request)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_BREQ, blk_hw_request);
}

/**
  * @brief  Get block hardware request.
  * @rmtoll
  *  CTR2          BREQ           LL_DMA_GetHWRequestType
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_HARDWARE_REQUEST_BURST
  *         @arg @ref LL_DMA_HARDWARE_REQUEST_BLOCK
  */
__STATIC_INLINE uint32_t LL_DMA_GetHWRequestType(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_BREQ));
}

/**
  * @brief  Set hardware request.
  * @rmtoll
  *  CTR2         REQSEL     LL_DMA_SetPeriphRequest
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  request This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_REQUEST_ADC1
  *         @arg @ref LL_GPDMA1_REQUEST_ADC4
  *         @arg @ref LL_GPDMA1_REQUEST_DAC1_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_DAC1_CH2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM6_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM7_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_TX
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_UART4_RX
  *         @arg @ref LL_GPDMA1_REQUEST_UART4_TX
  *         @arg @ref LL_GPDMA1_REQUEST_UART5_RX
  *         @arg @ref LL_GPDMA1_REQUEST_UART5_TX
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_A
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_B
  *         @arg @ref LL_GPDMA1_REQUEST_SAI2_A
  *         @arg @ref LL_GPDMA1_REQUEST_SAI2_B
  *         @arg @ref LL_GPDMA1_REQUEST_OCTOSPI1
  *         @arg @ref LL_GPDMA1_REQUEST_OCTOSPI2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_DCMI_PSSI
  *         @arg @ref LL_GPDMA1_REQUEST_AES_IN
  *         @arg @ref LL_GPDMA1_REQUEST_AES_OUT
  *         @arg @ref LL_GPDMA1_REQUEST_HASH_IN
  *         @arg @ref LL_GPDMA1_REQUEST_UCPD1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_UCPD1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT0
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT1
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT2
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT3
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT4
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT5
  *         @arg @ref LL_GPDMA1_REQUEST_ADF1_FLT0
  *         @arg @ref LL_GPDMA1_REQUEST_FMAC_RD
  *         @arg @ref LL_GPDMA1_REQUEST_FMAC_WR
  *         @arg @ref LL_GPDMA1_REQUEST_CORDIC_RD
  *         @arg @ref LL_GPDMA1_REQUEST_CORDIC_WR
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_IN
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_OUT
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_UE
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_UE
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM3_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM3_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM3_UE
  * @if HSPI1
  *         @arg @ref LL_GPDMA1_REQUEST_HSPI1
  * @endif
  * @if I2C5
  *         @arg @ref LL_GPDMA1_REQUEST_I2C5_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C5_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C5_EVC
  * @endif
  * @if I2C6
  *         @arg @ref LL_GPDMA1_REQUEST_I2C6_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C6_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C6_EVC
  * @endif
  * @if USART6
  *         @arg @ref LL_GPDMA1_REQUEST_USART6_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART6_TX
  * @endif
  * @if ADC2
  *         @arg @ref LL_GPDMA1_REQUEST_ADC2
  * @endif
  *         @arg @ref LL_LPDMA1_REQUEST_LPUART1_RX
  *         @arg @ref LL_LPDMA1_REQUEST_LPUART1_TX
  *         @arg @ref LL_LPDMA1_REQUEST_SPI3_RX
  *         @arg @ref LL_LPDMA1_REQUEST_SPI3_TX
  *         @arg @ref LL_LPDMA1_REQUEST_I2C3_RX
  *         @arg @ref LL_LPDMA1_REQUEST_I2C3_TX
  *         @arg @ref LL_LPDMA1_REQUEST_I2C3_EVC
  *         @arg @ref LL_LPDMA1_REQUEST_ADC4
  *         @arg @ref LL_LPDMA1_REQUEST_DAC1_CH1
  *         @arg @ref LL_LPDMA1_REQUEST_DAC1_CH2
  *         @arg @ref LL_LPDMA1_REQUEST_ADF1_FLT0
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM1_IC1
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM1_IC2
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM1_UE
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM3_IC1
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM3_IC2
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM3_UE
  */
__STATIC_INLINE void LL_DMA_SetPeriphRequest(DMA_Channel_TypeDef *channel, uint32_t request)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_REQSEL, request);
}

/**
  * @brief  Get hardware request.
  * @rmtoll
  *  CTR2         REQSEL     LL_DMA_GetPeriphRequest
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPDMA1_REQUEST_ADC1
  *         @arg @ref LL_GPDMA1_REQUEST_ADC4
  *         @arg @ref LL_GPDMA1_REQUEST_DAC1_CH1
  *         @arg @ref LL_GPDMA1_REQUEST_DAC1_CH2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM6_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM7_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI2_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_SPI3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C1_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C2_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C3_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C4_EVC
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART2_TX
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART3_TX
  *         @arg @ref LL_GPDMA1_REQUEST_UART4_RX
  *         @arg @ref LL_GPDMA1_REQUEST_UART4_TX
  *         @arg @ref LL_GPDMA1_REQUEST_UART5_RX
  *         @arg @ref LL_GPDMA1_REQUEST_UART5_TX
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_LPUART1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_A
  *         @arg @ref LL_GPDMA1_REQUEST_SAI1_B
  *         @arg @ref LL_GPDMA1_REQUEST_SAI2_A
  *         @arg @ref LL_GPDMA1_REQUEST_SAI2_B
  *         @arg @ref LL_GPDMA1_REQUEST_OCTOSPI1
  *         @arg @ref LL_GPDMA1_REQUEST_OCTOSPI2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM1_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM8_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM2_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM3_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM4_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC2
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC3
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_CC4
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM5_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_TRGI
  *         @arg @ref LL_GPDMA1_REQUEST_TIM15_COM
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM16_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_CC1
  *         @arg @ref LL_GPDMA1_REQUEST_TIM17_UPD
  *         @arg @ref LL_GPDMA1_REQUEST_DCMI_PSSI
  *         @arg @ref LL_GPDMA1_REQUEST_AES_IN
  *         @arg @ref LL_GPDMA1_REQUEST_AES_OUT
  *         @arg @ref LL_GPDMA1_REQUEST_HASH_IN
  *         @arg @ref LL_GPDMA1_REQUEST_UCPD1_TX
  *         @arg @ref LL_GPDMA1_REQUEST_UCPD1_RX
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT0
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT1
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT2
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT3
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT4
  *         @arg @ref LL_GPDMA1_REQUEST_MDF1_FLT5
  *         @arg @ref LL_GPDMA1_REQUEST_ADF1_FLT0
  *         @arg @ref LL_GPDMA1_REQUEST_FMAC_RD
  *         @arg @ref LL_GPDMA1_REQUEST_FMAC_WR
  *         @arg @ref LL_GPDMA1_REQUEST_CORDIC_RD
  *         @arg @ref LL_GPDMA1_REQUEST_CORDIC_WR
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_IN
  *         @arg @ref LL_GPDMA1_REQUEST_SAES_OUT
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM1_UE
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM2_UE
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM3_IC1
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM3_IC2
  *         @arg @ref LL_GPDMA1_REQUEST_LPTIM3_UE
  * @if HSPI1
  *         @arg @ref LL_GPDMA1_REQUEST_HSPI1
  * @endif
  * @if I2C5
  *         @arg @ref LL_GPDMA1_REQUEST_I2C5_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C5_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C5_EVC
  * @endif
  * @if I2C6
  *         @arg @ref LL_GPDMA1_REQUEST_I2C6_RX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C6_TX
  *         @arg @ref LL_GPDMA1_REQUEST_I2C6_EVC
  * @endif
  * @if USART6
  *         @arg @ref LL_GPDMA1_REQUEST_USART6_RX
  *         @arg @ref LL_GPDMA1_REQUEST_USART6_TX
  * @endif
  * @if ADC2
  *         @arg @ref LL_GPDMA1_REQUEST_ADC2
  * @endif
  *         @arg @ref LL_LPDMA1_REQUEST_LPUART1_RX
  *         @arg @ref LL_LPDMA1_REQUEST_LPUART1_TX
  *         @arg @ref LL_LPDMA1_REQUEST_SPI3_RX
  *         @arg @ref LL_LPDMA1_REQUEST_SPI3_TX
  *         @arg @ref LL_LPDMA1_REQUEST_I2C3_RX
  *         @arg @ref LL_LPDMA1_REQUEST_I2C3_TX
  *         @arg @ref LL_LPDMA1_REQUEST_I2C3_EVC
  *         @arg @ref LL_LPDMA1_REQUEST_ADC4
  *         @arg @ref LL_LPDMA1_REQUEST_DAC1_CH1
  *         @arg @ref LL_LPDMA1_REQUEST_DAC1_CH2
  *         @arg @ref LL_LPDMA1_REQUEST_ADF1_FLT0
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM1_IC1
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM1_IC2
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM1_UE
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM3_IC1
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM3_IC2
  *         @arg @ref LL_LPDMA1_REQUEST_LPTIM3_UE
  */
__STATIC_INLINE uint32_t LL_DMA_GetPeriphRequest(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_REQSEL));
}

/**
  * @brief  Set hardware trigger.
  * @rmtoll
  *  CTR2         TRIGSEL     LL_DMA_SetHWTrigger
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  trigger This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM4_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP1_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP2_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH8_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH9_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH10_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH11_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH12_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH13_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH14_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH15_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM15_TRGO
  * @if TIM3_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM3_TRGO
  * @endif
  * @if TIM4_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM4_TRGO
  * @endif
  * @if TIM5_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM5_TRGO
  * @endif
  * @if LTDC
  *         @arg @ref LL_GPDMA1_TRIGGER_LTDC_LI
  * @endif
  * @if DSI
  *         @arg @ref LL_GPDMA1_TRIGGER_DSI_TE
  *         @arg @ref LL_GPDMA1_TRIGGER_DSI_ER
  * @endif
  * @if DMA2D_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_TC
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_CTC
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_TW
  * @endif
  * @if GPU2D
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG0
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG1
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG2
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG3
  * @endif
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC4_AWD1
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC1_AWD1
  *
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE4
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM3_CH1
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM4_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_COMP1_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_COMP2_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH0_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH1_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH2_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH3_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH12_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH13_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_LPDMA1_TRIGGER_TIM15_TRGO
  */
__STATIC_INLINE void LL_DMA_SetHWTrigger(DMA_Channel_TypeDef *channel, uint32_t trigger)
{
  MODIFY_REG(channel->CTR2, DMA_CTR2_TRIGSEL, (trigger << DMA_CTR2_TRIGSEL_Pos) & DMA_CTR2_TRIGSEL);
}

/**
  * @brief  Get hardware triggers.
  * @rmtoll
  *  CTR2         TRIGSEL     LL_DMA_GetHWTrigger
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_GPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_GPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH1
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM2_CH2
  *         @arg @ref LL_GPDMA1_TRIGGER_LPTIM4_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP1_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_COMP2_OUT
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH8_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH9_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH10_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH11_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH12_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH13_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH14_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_GPDMA1_CH15_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH0_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH1_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH2_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_LPDMA1_CH3_TCF
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM15_TRGO
  * @if TIM3_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM3_TRGO
  * @endif
  * @if TIM4_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM4_TRGO
  * @endif
  * @if TIM5_TRGO_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_TIM5_TRGO
  * @endif
  * @if LTDC
  *         @arg @ref LL_GPDMA1_TRIGGER_LTDC_LI
  * @endif
  * @if DSI
  *         @arg @ref LL_GPDMA1_TRIGGER_DSI_TE
  *         @arg @ref LL_GPDMA1_TRIGGER_DSI_ER
  * @endif
  * @if DMA2D_TRIGGER_SUPPORT
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_TC
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_CTC
  *         @arg @ref LL_GPDMA1_TRIGGER_DMA2D_TW
  * @endif
  * @if GPU2D
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG0
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG1
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG2
  *         @arg @ref LL_GPDMA1_TRIGGER_GPU2D_FLAG3
  * @endif
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC4_AWD1
  *         @arg @ref LL_GPDMA1_TRIGGER_ADC1_AWD1
  *
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE0
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE1
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE2
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE3
  *         @arg @ref LL_LPDMA1_TRIGGER_EXTI_LINE4
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG1
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG2
  *         @arg @ref LL_LPDMA1_TRIGGER_TAMP_TRG3
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM1_CH1
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM1_CH2
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM3_CH1
  *         @arg @ref LL_LPDMA1_TRIGGER_LPTIM4_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_COMP1_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_COMP2_OUT
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_ALRA_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_ALRB_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_RTC_WUT_TRG
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH0_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH1_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH2_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_LPDMA1_CH3_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH0_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH1_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH4_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH5_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH6_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH7_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH12_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_GPDMA1_CH13_TCF
  *         @arg @ref LL_LPDMA1_TRIGGER_TIM2_TRGO
  *         @arg @ref LL_LPDMA1_TRIGGER_TIM15_TRGO
  */
__STATIC_INLINE  uint32_t LL_DMA_GetHWTrigger(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR2, DMA_CTR2_TRIGSEL) >> DMA_CTR2_TRIGSEL_Pos);
}

/**
  * @brief  Configure addresses update.
  * @rmtoll
  *  CBR1         BRDDEC            LL_DMA_ConfigBlkRpt \n
  *  CBR1         BRSDEC            LL_DMA_ConfigBlkRpt \n
  *  CBR1         DDEC              LL_DMA_ConfigBlkRpt \n
  *  CBR1         SDEC              LL_DMA_ConfigBlkRpt \n
  *  CBR1         BRC               LL_DMA_ConfigBlkRpt
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_count Between 1 and 2048
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_BLOCK_DEST_ADDR_INCREMENTED or @ref LL_DMA_BLOCK_DEST_ADDR_DECREMENTED
  *         @arg @ref LL_DMA_BLOCK_SRC_ADDR_INCREMENTED  or @ref LL_DMA_BLOCK_SRC_ADDR_DECREMENTED
  *         @arg @ref LL_DMA_BURST_DEST_ADDR_INCREMENTED or @ref LL_DMA_BURST_DEST_ADDR_DECREMENTED
  *         @arg @ref LL_DMA_BURST_SRC_ADDR_INCREMENTED  or @ref LL_DMA_BURST_SRC_ADDR_DECREMENTED
  */
__STATIC_INLINE void LL_DMA_ConfigBlkRpt(DMA_Channel_TypeDef *channel, uint32_t blk_rpt_count,
                                         uint32_t configuration)
{
  MODIFY_REG(channel->CBR1, (DMA_CBR1_BRDDEC | DMA_CBR1_BRSDEC | DMA_CBR1_DDEC | DMA_CBR1_SDEC | DMA_CBR1_BRC),
             (configuration | ((blk_rpt_count - 1U) << DMA_CBR1_BRC_Pos)));
}

/**
  * @brief  Configure addresses update.
  * @rmtoll
  *  CBR1         BRDDEC            LL_DMA_ConfigBlkRptAddrUpdate \n
  *  CBR1         BRSDEC            LL_DMA_ConfigBlkRptAddrUpdate \n
  *  CBR1         DDEC              LL_DMA_ConfigBlkRptAddrUpdate \n
  *  CBR1         SDEC              LL_DMA_ConfigBlkRptAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_BLOCK_DEST_ADDR_INCREMENTED or @ref LL_DMA_BLOCK_DEST_ADDR_DECREMENTED
  *         @arg @ref LL_DMA_BLOCK_SRC_ADDR_INCREMENTED  or @ref LL_DMA_BLOCK_SRC_ADDR_DECREMENTED
  *         @arg @ref LL_DMA_BURST_DEST_ADDR_INCREMENTED or @ref LL_DMA_BURST_DEST_ADDR_DECREMENTED
  *         @arg @ref LL_DMA_BURST_SRC_ADDR_INCREMENTED  or @ref LL_DMA_BURST_SRC_ADDR_DECREMENTED
  */
__STATIC_INLINE void LL_DMA_ConfigBlkRptAddrUpdate(DMA_Channel_TypeDef *channel, uint32_t configuration)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_BRDDEC | DMA_CBR1_BRSDEC | DMA_CBR1_DDEC | DMA_CBR1_SDEC, configuration);
}

/**
  * @brief  Configure DMA Block number of data and repeat Count.
  * @rmtoll
  *  CBR1         BNDT                     LL_DMA_ConfigBlkCounters \n
  *  CBR1         BRC                      LL_DMA_ConfigBlkCounters
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_data_length Between 0 and 0x0000FFFF
  * @param  blk_rpt_count Between 0 and 0x000007FF
  */
__STATIC_INLINE void LL_DMA_ConfigBlkCounters(DMA_Channel_TypeDef *channel, uint32_t blk_data_length,
                                              uint32_t blk_rpt_count)
{
  MODIFY_REG(channel->CBR1, (DMA_CBR1_BNDT | DMA_CBR1_BRC), (blk_data_length | (blk_rpt_count << DMA_CBR1_BRC_Pos)));
}

/**
  * @brief  Set block repeat destination address update.
  * @rmtoll
  *  CBR1          BRDDEC           LL_DMA_SetBlkRptDestAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_dest_addr_update This parameter can be one of the following values:
  *         @arg @ref LL_DMA_BLOCK_DEST_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BLOCK_DEST_ADDR_DECREMENTED
  */
__STATIC_INLINE void LL_DMA_SetBlkRptDestAddrUpdate(DMA_Channel_TypeDef *channel, uint32_t blk_rpt_dest_addr_update)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_BRDDEC, blk_rpt_dest_addr_update);
}

/**
  * @brief  Get block repeat destination address update.
  * @rmtoll
  *  CBR1          BRDDEC           LL_DMA_GetBlkRptDestAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_BLOCK_DEST_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BLOCK_DEST_ADDR_DECREMENTED
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkRptDestAddrUpdate(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR1, DMA_CBR1_BRDDEC));
}

/**
  * @brief  Set block repeat source address update.
  * @rmtoll
  *  CBR1          BRSDEC           LL_DMA_SetBlkRptSrcAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_src_addr_update This parameter can be one of the following values:
  *         @arg @ref LL_DMA_BLOCK_SRC_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BLOCK_SRC_ADDR_DECREMENTED
  */
__STATIC_INLINE void LL_DMA_SetBlkRptSrcAddrUpdate(DMA_Channel_TypeDef *channel, uint32_t blk_rpt_src_addr_update)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_BRSDEC, blk_rpt_src_addr_update);
}

/**
  * @brief  Get block repeat source address update.
  * @rmtoll
  *  CBR1          BRSDEC           LL_DMA_GetBlkRptSrcAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_BLOCK_SRC_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BLOCK_SRC_ADDR_DECREMENTED
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkRptSrcAddrUpdate(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR1, DMA_CBR1_BRSDEC));
}

/**
  * @brief  Set destination address update.
  * @rmtoll
  *  CBR1          DDEC           LL_DMA_SetDestAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_addr_update This parameter can be one of the following values:
  *         @arg @ref LL_DMA_BURST_DEST_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BURST_DEST_ADDR_DECREMENTED
  */
__STATIC_INLINE void LL_DMA_SetDestAddrUpdate(DMA_Channel_TypeDef *channel, uint32_t dest_addr_update)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_DDEC, dest_addr_update);
}

/**
  * @brief  Get destination address update.
  * @rmtoll
  *  CBR1          DDEC           LL_DMA_GetDestAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_BURST_DEST_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BURST_DEST_ADDR_DECREMENTED
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestAddrUpdate(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR1, DMA_CBR1_DDEC));
}

/**
  * @brief  Set source address update.
  * @rmtoll
  *  CBR1          SDEC           LL_DMA_SetSrcAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  src_addr_update This parameter can be one of the following values:
  *         @arg @ref LL_DMA_BURST_SRC_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BURST_SRC_ADDR_DECREMENTED
  */
__STATIC_INLINE void LL_DMA_SetSrcAddrUpdate(DMA_Channel_TypeDef *channel, uint32_t src_addr_update)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_SDEC, src_addr_update);
}

/**
  * @brief  Get source address update.
  * @rmtoll
  *  CBR1          SDEC           LL_DMA_GetSrcAddrUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DMA_BURST_SRC_ADDR_INCREMENTED
  *         @arg @ref LL_DMA_BURST_SRC_ADDR_DECREMENTED
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAddrUpdate(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR1, DMA_CBR1_SDEC));
}

/**
  * @brief  Set block repeat count.
  * @rmtoll
  *  CBR1        BRC            LL_DMA_SetBlkRptCount
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_count Between 0 and 0x000007FF
  */
__STATIC_INLINE void LL_DMA_SetBlkRptCount(DMA_Channel_TypeDef *channel, uint32_t blk_rpt_count)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_BRC, (blk_rpt_count << DMA_CBR1_BRC_Pos) & DMA_CBR1_BRC);
}

/**
  * @brief  Get block repeat count.
  * @rmtoll
  *  CBR1        BRC            LL_DMA_GetBlkRptCount
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 0 and 0x000007FF
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkRptCount(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR1, DMA_CBR1_BRC) >> DMA_CBR1_BRC_Pos);
}

/**
  * @brief  Set block data length in bytes to transfer.
  * @rmtoll
  *  CBR1        BNDT         LL_DMA_SetBlkDataLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  blk_data_length Between 0 and 0x0000FFFF
  */
__STATIC_INLINE void LL_DMA_SetBlkDataLength(DMA_Channel_TypeDef *channel, uint32_t blk_data_length)
{
  MODIFY_REG(channel->CBR1, DMA_CBR1_BNDT, blk_data_length);
}

/**
  * @brief  Get block data length in bytes to transfer.
  * @rmtoll
  *  CBR1        BNDT         LL_DMA_GetBlkDataLength
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Between 0 and 0x0000FFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkDataLength(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR1, DMA_CBR1_BNDT));
}

/**
  * @brief  Configure the source and destination addresses.
  * @rmtoll
  *  CSAR        SA          LL_DMA_ConfigAddresses \n
  *  CDAR        DA          LL_DMA_ConfigAddresses
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  src_address Between 0 and 0xFFFFFFFF
  * @param  dest_address Between 0 and 0xFFFFFFFF
  * @warning This API must not be called when the DMA channel is enabled.
  */
__STATIC_INLINE void LL_DMA_ConfigAddresses(DMA_Channel_TypeDef *channel, uint32_t src_address, uint32_t dest_address)
{
  WRITE_REG(channel->CSAR, src_address);
  WRITE_REG(channel->CDAR, dest_address);
}

/**
  * @brief  Set source address.
  * @rmtoll
  *  CSAR        SA         LL_DMA_SetSrcAddress
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  src_address Between 0 and 0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA_SetSrcAddress(DMA_Channel_TypeDef *channel, uint32_t src_address)
{
  WRITE_REG(channel->CSAR, src_address);
}

/**
  * @brief  Get source address.
  * @rmtoll
  *  CSAR        SA         LL_DMA_GetSrcAddress
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Between 0 and 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAddress(const DMA_Channel_TypeDef *channel)
{
  return (READ_REG(channel->CSAR));
}

/**
  * @brief  Set destination address.
  * @rmtoll
  *  CDAR        DA         LL_DMA_SetDestAddress
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  dest_address Between 0 and 0xFFFFFFFF
  */
__STATIC_INLINE void LL_DMA_SetDestAddress(DMA_Channel_TypeDef *channel, uint32_t dest_address)
{
  WRITE_REG(channel->CDAR, dest_address);
}

/**
  * @brief  Get destination address.
  * @rmtoll
  *  CDAR        DA         LL_DMA_GetDestAddress
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Between 0 and 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestAddress(const DMA_Channel_TypeDef *channel)
{
  return (READ_REG(channel->CDAR));
}

/**
  * @brief  Configure source and destination addresses offset.
  * @rmtoll
  *  CTR3        DAO          LL_DMA_ConfigAddrUpdateValue \n
  *  CTR3        SAO          LL_DMA_ConfigAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_addr_offset Between 0 and 0x00001FFF
  * @param  src_addr_offset Between 0 and 0x00001FFF
  * @warning This API must not be called when the DMA channel is enabled.
  */
__STATIC_INLINE void LL_DMA_ConfigAddrUpdateValue(DMA_Channel_TypeDef *channel, uint32_t src_addr_offset,
                                                  uint32_t dest_addr_offset)
{
  WRITE_REG(channel->CTR3, (src_addr_offset  & DMA_CTR3_SAO) | ((dest_addr_offset << DMA_CTR3_DAO_Pos) & DMA_CTR3_DAO));
}

/**
  * @brief  Set destination address offset.
  * @rmtoll
  *  CTR3       DAO         LL_DMA_SetDestAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  dest_addr_offset Between 0 and 0x00001FFF
  */
__STATIC_INLINE void LL_DMA_SetDestAddrUpdateValue(DMA_Channel_TypeDef *channel, uint32_t dest_addr_offset)
{
  MODIFY_REG(channel->CTR3, DMA_CTR3_DAO, ((dest_addr_offset << DMA_CTR3_DAO_Pos) & DMA_CTR3_DAO));
}

/**
  * @brief  Get destination address offset.
  * @rmtoll
  *  CDAR        DAO         LL_DMA_GetDestAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 0 and 0x00001FFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetDestAddrUpdateValue(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR3, DMA_CTR3_DAO) >> DMA_CTR3_DAO_Pos);
}

/**
  * @brief  Set source address offset.
  * @rmtoll
  *  CTR3        SAO         LL_DMA_SetSrcAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  src_addr_offset Between 0 and 0x00001FFF
  */
__STATIC_INLINE void LL_DMA_SetSrcAddrUpdateValue(DMA_Channel_TypeDef *channel, uint32_t src_addr_offset)
{
  MODIFY_REG(channel->CTR3, DMA_CTR3_SAO, src_addr_offset & DMA_CTR3_SAO);
}

/**
  * @brief  Get source address offset.
  * @rmtoll
  *  CTR3        SAO         LL_DMA_GetSrcAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 0 and 0x00001FFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetSrcAddrUpdateValue(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CTR3, DMA_CTR3_SAO));
}

/**
  * @brief  Configure the block repeated source and destination addresses offset.
  * @rmtoll
  *  CBR2        BRDAO          LL_DMA_ConfigBlkRptAddrUpdateValue \n
  *  CBR2        BRSAO          LL_DMA_ConfigBlkRptAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_dest_addr_offset Between 0 and 0x0000FFFF
  * @param  blk_rpt_src_addr_offset Between 0 and 0x0000FFFF
  * @warning This API must not be called when the DMA channel is enabled.
  */
__STATIC_INLINE void LL_DMA_ConfigBlkRptAddrUpdateValue(DMA_Channel_TypeDef *channel, uint32_t blk_rpt_src_addr_offset,
                                                        uint32_t blk_rpt_dest_addr_offset)
{
  WRITE_REG(channel->CBR2, ((blk_rpt_dest_addr_offset << DMA_CBR2_BRDAO_Pos) & DMA_CBR2_BRDAO) | \
            (blk_rpt_src_addr_offset  & DMA_CBR2_BRSAO));
}

/**
  * @brief  Set block repeated destination address offset.
  * @rmtoll
  *  CBR2       BRDAO         LL_DMA_SetBlkRptDestAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_dest_addr_offset Between 0 and 0x0000FFFF
  */
__STATIC_INLINE void LL_DMA_SetBlkRptDestAddrUpdateValue(DMA_Channel_TypeDef *channel,
                                                         uint32_t blk_rpt_dest_addr_offset)
{
  MODIFY_REG(channel->CBR2, DMA_CBR2_BRDAO, ((blk_rpt_dest_addr_offset << DMA_CBR2_BRDAO_Pos) & DMA_CBR2_BRDAO));
}

/**
  * @brief  Get block repeated destination address offset.
  * @rmtoll
  *  CBR2        BRDAO         LL_DMA_GetBlkRptDestAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 0 and 0x0000FFFF.
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkRptDestAddrUpdateValue(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR2, DMA_CBR2_BRDAO) >> DMA_CBR2_BRDAO_Pos);
}

/**
  * @brief  Set block repeated source address offset.
  * @rmtoll
  *  CBR2        BRSAO         LL_DMA_SetBlkRptSrcAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @param  blk_rpt_src_addr_offset Between 0 and 0x0000FFFF
  */
__STATIC_INLINE void LL_DMA_SetBlkRptSrcAddrUpdateValue(DMA_Channel_TypeDef *channel, uint32_t blk_rpt_src_addr_offset)
{
  MODIFY_REG(channel->CBR2, DMA_CBR2_BRSAO, blk_rpt_src_addr_offset);
}

/**
  * @brief  Get block repeated source address offset.
  * @rmtoll
  *  CBR2        BRSAO         LL_DMA_GetBlkRptSrcAddrUpdateValue
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 0 and 0x0000FFFF
  */
__STATIC_INLINE uint32_t LL_DMA_GetBlkRptSrcAddrUpdateValue(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CBR2, DMA_CBR2_BRSAO));
}

/**
  * @brief  Configure registers update and node address offset during the link transfer.
  * @rmtoll
  *  CLLR          UT1            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          UT2            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          UB1            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          USA            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          UDA            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          UT3            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          UB2            LL_DMA_ConfigLinkUpdate \n
  *  CLLR          ULL            LL_DMA_ConfigLinkUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  registers_update This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_UPDATE_CTR1
  *         @arg @ref LL_DMA_UPDATE_CTR2
  *         @arg @ref LL_DMA_UPDATE_CBR1
  *         @arg @ref LL_DMA_UPDATE_CSAR
  *         @arg @ref LL_DMA_UPDATE_CDAR
  *         @arg @ref LL_DMA_UPDATE_CTR3  (This value is allowed only for 2D addressing channels)
  *         @arg @ref LL_DMA_UPDATE_CBR2  (This value is allowed only for 2D addressing channels)
  *         @arg @ref LL_DMA_UPDATE_CLLR
  * @param  linked_list_addr_offset Between 0 and 0x0000FFFC
  */
__STATIC_INLINE void LL_DMA_ConfigLinkUpdate(DMA_Channel_TypeDef *channel, uint32_t registers_update,
                                             uint32_t linked_list_addr_offset)
{
  MODIFY_REG(channel->CLLR, (DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_UT3 | \
                             DMA_CLLR_UB2 | DMA_CLLR_ULL | DMA_CLLR_LA),
             (registers_update | (linked_list_addr_offset & DMA_CLLR_LA)));
}

/**
  * @brief  Enable CTR1 update during the link transfer.
  * @rmtoll
  *  CLLR          UT1            LL_DMA_EnableCTR1Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableCTR1Update(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_UT1);
}

/**
  * @brief  Disable CTR1 update during the link transfer.
  * @rmtoll
  *  CLLR          UT1            LL_DMA_DisableCTR1Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableCTR1Update(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_UT1);
}

/**
  * @brief  Check if CTR1 update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          UT1            LL_DMA_IsEnabledCTR1Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCTR1Update(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_UT1) == (DMA_CLLR_UT1)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CTR2 update during the link transfer.
  * @rmtoll
  *  CLLR          UT2            LL_DMA_EnableCTR2Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableCTR2Update(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_UT2);
}

/**
  * @brief  Disable CTR2 update during the link transfer.
  * @rmtoll
  *  CLLR          UT2            LL_DMA_DisableCTR2Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableCTR2Update(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_UT2);
}

/**
  * @brief  Check if CTR2 update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          UT2            LL_DMA_IsEnabledCTR2Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCTR2Update(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_UT2) == (DMA_CLLR_UT2)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CBR1 update during the link transfer.
  * @rmtoll
  *  CLLR          UB1            LL_DMA_EnableCBR1Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableCBR1Update(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_UB1);
}

/**
  * @brief  Disable CBR1 update during the link transfer.
  * @rmtoll
  *  CLLR          UB1            LL_DMA_DisableCBR1Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableCBR1Update(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_UB1);
}

/**
  * @brief  Check if CBR1 update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          UB1            LL_DMA_IsEnabledCBR1Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCBR1Update(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_UB1) == (DMA_CLLR_UB1)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CSAR update during the link transfer.
  * @rmtoll
  *  CLLR          USA            LL_DMA_EnableCSARUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableCSARUpdate(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_USA);
}

/**
  * @brief  Disable CSAR update during the link transfer.
  * @rmtoll
  *  CLLR          USA            LL_DMA_DisableCSARUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableCSARUpdate(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_USA);
}

/**
  * @brief  Check if CSAR update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          USA            LL_DMA_IsEnabledCSARUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCSARUpdate(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_USA) == (DMA_CLLR_USA)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CDAR update during the link transfer.
  * @rmtoll
  *  CLLR          UDA            LL_DMA_EnableCDARUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableCDARUpdate(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_UDA);
}

/**
  * @brief  Disable CDAR update during the link transfer.
  * @rmtoll
  *  CLLR          UDA            LL_DMA_DisableCDARUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableCDARUpdate(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_UDA);
}

/**
  * @brief  Check if CDAR update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          UDA            LL_DMA_IsEnabledCDARUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCDARUpdate(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_UDA) == (DMA_CLLR_UDA)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CTR3 update during the link transfer.
  * @rmtoll
  *  CLLR          UT3            LL_DMA_EnableCTR3Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  */
__STATIC_INLINE void LL_DMA_EnableCTR3Update(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_UT3);
}

/**
  * @brief  Disable CTR3 update during the link transfer.
  * @rmtoll
  *  CLLR          UT3            LL_DMA_DisableCTR3Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  */
__STATIC_INLINE void LL_DMA_DisableCTR3Update(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_UT3);
}

/**
  * @brief  Check if CTR3 update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          UT3            LL_DMA_IsEnabledCTR3Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCTR3Update(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_UT3) == (DMA_CLLR_UT3)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CBR2 update during the link transfer.
  * @rmtoll
  *  CLLR          UB2            LL_DMA_EnableCBR2Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  */
__STATIC_INLINE void LL_DMA_EnableCBR2Update(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_UB2);
}

/**
  * @brief  Disable CBR2 update during the link transfer.
  * @rmtoll
  *  CLLR          UB2            LL_DMA_DisableCBR2Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  */
__STATIC_INLINE void LL_DMA_DisableCBR2Update(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_UB2);
}

/**
  * @brief  Check if CBR2 update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          UB2            LL_DMA_IsEnabledCBR2Update
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCBR2Update(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_UB2) == (DMA_CLLR_UB2)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CLLR update during the link transfer.
  * @rmtoll
  *  CLLR          ULL            LL_DMA_EnableCLLRUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableCLLRUpdate(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CLLR, DMA_CLLR_ULL);
}

/**
  * @brief  Disable CLLR update during the link transfer.
  * @rmtoll
  *  CLLR          ULL            LL_DMA_DisableCLLRUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableCLLRUpdate(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CLLR, DMA_CLLR_ULL);
}

/**
  * @brief  Check if CLLR update during the link transfer is enabled.
  * @rmtoll
  *  CLLR          ULL            LL_DMA_IsEnabledCLLRUpdate
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledCLLRUpdate(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CLLR, DMA_CLLR_ULL) == (DMA_CLLR_ULL)) ? 1UL : 0UL);
}

/**
  * @brief  Set linked list address offset.
  * @rmtoll
  *  CLLR          LA           LL_DMA_SetLinkedListAddrOffset
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  linked_list_addr_offset Between 0 and 0x0000FFFC
  */
__STATIC_INLINE void LL_DMA_SetLinkedListAddrOffset(DMA_Channel_TypeDef *channel, uint32_t linked_list_addr_offset)
{
  MODIFY_REG(channel->CLLR, DMA_CLLR_LA, (linked_list_addr_offset & DMA_CLLR_LA));
}

/**
  * @brief  Get linked list address offset.
  * @rmtoll
  *  CLLR          LA           LL_DMA_GetLinkedListAddrOffset
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval Between 0 and 0x0000FFFC.
  */
__STATIC_INLINE uint32_t LL_DMA_GetLinkedListAddrOffset(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CLLR, DMA_CLLR_LA) >> DMA_CLLR_LA_Pos);
}

/**
  * @brief  Get FIFO level.
  * @rmtoll
  *  CSR          FIFOL           LL_DMA_GetFIFOLevel
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  * @retval Between 0 and 0x000000FF.
  */
__STATIC_INLINE uint32_t LL_DMA_GetFIFOLevel(const DMA_Channel_TypeDef *channel)
{
  return (READ_BIT(channel->CSR, DMA_CSR_FIFOL) >> DMA_CSR_FIFOL_Pos);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure DMA channel access security attribute.
  * @rmtoll
  *  CTR1          SSEC           LL_DMA_ConfigChannelAccessSecurity \n
  *  CTR1          DSEC           LL_DMA_ConfigChannelAccessSecurity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  src_sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ATTR_SEC
  *         @arg @ref LL_DMA_ATTR_NSEC
  * @param  dest_sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ATTR_SEC
  *         @arg @ref LL_DMA_ATTR_NSEC
  */
__STATIC_INLINE void LL_DMA_ConfigChannelAccessSecurity(DMA_Channel_TypeDef *channel, uint32_t src_sec_attr,
                                                        uint32_t dest_sec_attr)
{
  MODIFY_REG(channel->CTR1, (DMA_CTR1_SSEC | DMA_CTR1_DSEC),
             ((src_sec_attr << DMA_CTR1_SSEC_Pos) | (dest_sec_attr << DMA_CTR1_DSEC_Pos)));
}

/**
  * @brief  Set DMA channel destination security attribute.
  * @rmtoll
  *  CTR1          DSEC           LL_DMA_SetChannelDestSecurity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  dest_sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ATTR_SEC
  *         @arg @ref LL_DMA_ATTR_NSEC
  */
__STATIC_INLINE void LL_DMA_SetChannelDestSecurity(DMA_Channel_TypeDef *channel, uint32_t dest_sec_attr)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_DSEC, (dest_sec_attr << DMA_CTR1_DSEC_Pos));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get DMA channel destination security attribute.
  * @rmtoll
  *  CTR1          DSEC           LL_DMA_GetChannelDestSecurity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelDestSecurity(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CTR1, DMA_CTR1_DSEC) == (DMA_CTR1_DSEC)) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set DMA channel source security attribute.
  * @rmtoll
  *  CTR1          SSEC           LL_DMA_SetChannelSrcSecurity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  src_sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ATTR_SEC
  *         @arg @ref LL_DMA_ATTR_NSEC
  */
__STATIC_INLINE void LL_DMA_SetChannelSrcSecurity(DMA_Channel_TypeDef *channel, uint32_t src_sec_attr)
{
  MODIFY_REG(channel->CTR1, DMA_CTR1_SSEC, (src_sec_attr << DMA_CTR1_SSEC_Pos));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get DMA channel source security attribute.
  * @rmtoll
  *  CTR1          SSEC           LL_DMA_GetChannelSrcSecurity
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelSrcSecurity(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CTR1, DMA_CTR1_SSEC) == (DMA_CTR1_SSEC)) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Set the DMA channel security attribute.
  * @rmtoll
  *  SECCFGR         SECx         LL_DMA_SetChannelSecurity
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  * @param  sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ATTR_SEC
  *         @arg @ref LL_DMA_ATTR_NSEC
  */
__STATIC_INLINE void LL_DMA_SetChannelSecurity(DMA_TypeDef *dmax, uint32_t channel, uint32_t sec_attr)
{
  MODIFY_REG(dmax->SECCFGR, (DMA_SECCFGR_SEC0 << (channel & 0x0000000FU)), (sec_attr << (channel & 0x0000000FU)));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Get the DMA channel security attribute.
  * @rmtoll
  *  SECCFGR         SECx         LL_DMA_GetChannelSecurity
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelSecurity(const DMA_TypeDef *dmax, uint32_t channel)
{
  return ((READ_BIT(dmax->SECCFGR, (DMA_SECCFGR_SEC0 << (channel & 0x0000000FU)))
           == (DMA_SECCFGR_SEC0 << (channel & 0x0000000FU))) ? 1UL : 0UL);
}

/**
  * @brief  Set the DMA channel privilege attribute.
  * @rmtoll
  *  PRIVCFGR          PRIVx      LL_DMA_SetChannelPrivilege
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  * @param  priv_attr This parameter can be one of the following values:
  *         @arg @ref LL_DMA_ATTR_PRIV
  *         @arg @ref LL_DMA_ATTR_NPRIV
  */
__STATIC_INLINE void LL_DMA_SetChannelPrivilege(DMA_TypeDef *dmax, uint32_t channel, uint32_t priv_attr)
{
  MODIFY_REG(dmax->PRIVCFGR, (DMA_PRIVCFGR_PRIV0 << (channel & 0x0000000FU)), (priv_attr << (channel & 0x0000000FU)));
}

/**
  * @brief  Get the DMA channel privilege attribute.
  * @rmtoll
  *  PRIVCFGR          PRIVx      LL_DMA_GetChannelPrivilege
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  */
__STATIC_INLINE uint32_t LL_DMA_GetChannelPrivilege(const DMA_TypeDef *dmax, uint32_t channel)
{
  return ((READ_BIT(dmax->PRIVCFGR, (DMA_PRIVCFGR_PRIV0 << (channel & 0x0000000FU)))
           == (DMA_PRIVCFGR_PRIV0 << (channel & 0x0000000FU))) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock the DMA channel security and privilege attributes.
  * @rmtoll
  *  RCFGLOCKR           LOCKx         LL_DMA_LockChannelAttribute
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  */
__STATIC_INLINE void LL_DMA_LockChannelAttribute(DMA_TypeDef *dmax, uint32_t channel)
{
  SET_BIT(dmax->RCFGLOCKR, (DMA_RCFGLOCKR_LOCK0 << (channel & 0x0000000FU)));
}
#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Check if the DMA channel privilege and security attributes are locked.
  * @rmtoll
  *  SECCFGR            LOCKx       LL_DMA_IsLockedChannelAttribute
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsLockedChannelAttribute(const DMA_TypeDef *dmax, uint32_t channel)
{
  return ((READ_BIT(dmax->RCFGLOCKR, (DMA_RCFGLOCKR_LOCK0 << (channel & 0x0000000FU)))
           == (DMA_RCFGLOCKR_LOCK0 << (channel & 0x0000000FU))) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup DMA_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Clear flag.
  * @rmtoll
  *  CFCR          TOF/SUSPF/USEF/ULEF/DTEF/HTF/TCF        LL_DMA_ClearFlag
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  flag This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_FLAG_TO
  *         @arg @ref LL_DMA_FLAG_SUSP
  *         @arg @ref LL_DMA_FLAG_USE
  *         @arg @ref LL_DMA_FLAG_ULE
  *         @arg @ref LL_DMA_FLAG_DTE
  *         @arg @ref LL_DMA_FLAG_HT
  *         @arg @ref LL_DMA_FLAG_TC
  *         @arg @ref LL_DMA_FLAG_ALL
  */
__STATIC_INLINE void LL_DMA_ClearFlag(DMA_Channel_TypeDef *channel, uint32_t flag)
{
  WRITE_REG(channel->CFCR, flag);
}

/**
  * @brief  Clear trigger overrun flag.
  * @rmtoll
  *  CFCR          TOF        LL_DMA_ClearFlag_TO
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TO(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_TOF);
}

/**
  * @brief  Clear suspension flag.
  * @rmtoll
  *  CFCR          SUSPF        LL_DMA_ClearFlag_SUSP
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_SUSP(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_SUSPF);
}

/**
  * @brief  Clear user setting error flag.
  * @rmtoll
  *  CFCR          USEF         LL_DMA_ClearFlag_USE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_USE(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_USEF);
}

/**
  * @brief  Clear link transfer error flag.
  * @rmtoll
  *  CFCR          ULEF         LL_DMA_ClearFlag_ULE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_ULE(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_ULEF);
}

/**
  * @brief  Clear data transfer error flag.
  * @rmtoll
  *  CFCR          DTEF         LL_DMA_ClearFlag_DTE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_DTE(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_DTEF);
}

/**
  * @brief  Clear half transfer flag.
  * @rmtoll
  *  CFCR          HTF          LL_DMA_ClearFlag_HT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_HT(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_HTF);
}

/**
  * @brief  Clear transfer complete flag.
  * @rmtoll
  *  CFCR          TCF          LL_DMA_ClearFlag_TC
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_ClearFlag_TC(DMA_Channel_TypeDef *channel)
{
  WRITE_REG(channel->CFCR, DMA_CFCR_TCF);
}

/**
  * @brief  Get trigger overrun flag.
  * @rmtoll
  *  CSR           TOF        LL_DMA_IsActiveFlag_TO
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TO(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_TOF) == (DMA_CSR_TOF)) ? 1UL : 0UL);
}

/**
  * @brief  Get suspension flag.
  * @rmtoll
  *  CSR           SUSPF        LL_DMA_IsActiveFlag_SUSP
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_SUSP(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_SUSPF) == (DMA_CSR_SUSPF)) ? 1UL : 0UL);
}

/**
  * @brief  Get user setting error flag.
  * @rmtoll
  *  CSR           USEF         LL_DMA_IsActiveFlag_USE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_USE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_USEF) == (DMA_CSR_USEF)) ? 1UL : 0UL);
}

/**
  * @brief  Get update link transfer error flag.
  * @rmtoll
  *  CSR           ULEF         LL_DMA_IsActiveFlag_ULE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_ULE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_ULEF) == (DMA_CSR_ULEF)) ? 1UL : 0UL);
}

/**
  * @brief  Get data transfer error flag.
  * @rmtoll
  *  CSR           DTEF         LL_DMA_IsActiveFlag_DTE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DTE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_DTEF) == (DMA_CSR_DTEF)) ? 1UL : 0UL);
}

/**
  * @brief  Get half transfer flag.
  * @rmtoll
  *  CSR           HTF          LL_DMA_IsActiveFlag_HT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_HTF) == (DMA_CSR_HTF)) ? 1UL : 0UL);
}

/**
  * @brief  Get transfer complete flag.
  * @rmtoll
  *  CSR           TCF          LL_DMA_IsActiveFlag_TC
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_TCF) == (DMA_CSR_TCF)) ? 1UL : 0UL);
}

/**
  * @brief  Get idle flag.
  * @rmtoll
  *  CSR           IDLEF        LL_DMA_IsActiveFlag_IDLE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_IDLE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CSR, DMA_CSR_IDLEF) == (DMA_CSR_IDLEF)) ? 1UL : 0UL);
}

/**
  * @brief  Check if masked interrupt is active.
  * @rmtoll
  *  MISR  MISx    LL_DMA_IsActiveFlag_MIS
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_MIS(const DMA_TypeDef *dmax, uint32_t channel)
{
  return ((READ_BIT(dmax->MISR, (DMA_MISR_MIS0 << (channel & 0x0FU)))
           == (DMA_MISR_MIS0 << (channel & 0x0FU))) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Check if secure masked interrupt is active.
  * @rmtoll
  *  SMISR  MISx    LL_DMA_IsActiveFlag_SMIS
  * @param  dmax dmax Instance
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_DMA_CHANNEL_0
  *         @arg @ref LL_DMA_CHANNEL_1
  *         @arg @ref LL_DMA_CHANNEL_2
  *         @arg @ref LL_DMA_CHANNEL_3
  *         @arg @ref LL_DMA_CHANNEL_4
  *         @arg @ref LL_DMA_CHANNEL_5
  *         @arg @ref LL_DMA_CHANNEL_6
  *         @arg @ref LL_DMA_CHANNEL_7
  *         @arg @ref LL_DMA_CHANNEL_8
  *         @arg @ref LL_DMA_CHANNEL_9
  *         @arg @ref LL_DMA_CHANNEL_10
  *         @arg @ref LL_DMA_CHANNEL_11
  *         @arg @ref LL_DMA_CHANNEL_12
  *         @arg @ref LL_DMA_CHANNEL_13
  *         @arg @ref LL_DMA_CHANNEL_14
  *         @arg @ref LL_DMA_CHANNEL_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_SMIS(const DMA_TypeDef *dmax, uint32_t channel)
{
  return ((READ_BIT(dmax->SMISR, (DMA_SMISR_MIS0 << (channel & 0x0000000FU)))
           == (DMA_SMISR_MIS0 << (channel & 0x0000000FU))) ? 1UL : 0UL);
}
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @defgroup DMA_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable interrupts.
  * @rmtoll
  *  CCR           TOIF/SUSPIF/USEIF/ULEIF/DTEIF/HTIF/TCIF        LL_DMA_EnableIT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  interrupt This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_IT_TO
  *         @arg @ref LL_DMA_IT_SUSP
  *         @arg @ref LL_DMA_IT_USE
  *         @arg @ref LL_DMA_IT_ULE
  *         @arg @ref LL_DMA_IT_DTE
  *         @arg @ref LL_DMA_IT_HT
  *         @arg @ref LL_DMA_IT_TC
  *         @arg @ref LL_DMA_IT_ALL
  */
__STATIC_INLINE void LL_DMA_EnableIT(DMA_Channel_TypeDef *channel, uint32_t interrupt)
{
  SET_BIT(channel->CCR, interrupt);
}

/**
  * @brief  Enable interrupts.
  * @rmtoll
  *  CCR           TOIF/SUSPIF/USEIF/ULEIF/DTEIF/HTIF/TCIF       LL_DMA_DisableIT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @param  interrupt This parameter must be a combination of all the following values:
  *         @arg @ref LL_DMA_IT_TO
  *         @arg @ref LL_DMA_IT_SUSP
  *         @arg @ref LL_DMA_IT_USE
  *         @arg @ref LL_DMA_IT_ULE
  *         @arg @ref LL_DMA_IT_DTE
  *         @arg @ref LL_DMA_IT_HT
  *         @arg @ref LL_DMA_IT_TC
  *         @arg @ref LL_DMA_IT_ALL
  */
__STATIC_INLINE void LL_DMA_DisableIT(DMA_Channel_TypeDef *channel, uint32_t interrupt)
{
  CLEAR_BIT(channel->CCR, interrupt);
}

/**
  * @brief  Enable trigger overrun interrupt.
  * @rmtoll
  *  CCR           TOIE       LL_DMA_EnableIT_TO
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_TO(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_TOIE);
}

/**
  * @brief  Enable suspension interrupt.
  * @rmtoll
  *  CCR           SUSPIE       LL_DMA_EnableIT_SUSP
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_SUSP(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_SUSPIE);
}

/**
  * @brief  Enable user setting error interrupt.
  * @rmtoll
  *  CCR           USEIE        LL_DMA_EnableIT_USE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_USE(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_USEIE);
}

/**
  * @brief  Enable update link transfer error interrupt.
  * @rmtoll
  *  CCR           ULEIE        LL_DMA_EnableIT_ULE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_ULE(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_ULEIE);
}

/**
  * @brief  Enable data transfer error interrupt.
  * @rmtoll
  *  CCR           DTEIE        LL_DMA_EnableIT_DTE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_DTE(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_DTEIE);
}

/**
  * @brief  Enable half transfer complete interrupt.
  * @rmtoll
  *  CCR           HTIE         LL_DMA_EnableIT_HT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_HT(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_HTIE);
}

/**
  * @brief  Enable transfer complete interrupt.
  * @rmtoll
  *  CCR           TCIE         LL_DMA_EnableIT_TC
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_EnableIT_TC(DMA_Channel_TypeDef *channel)
{
  SET_BIT(channel->CCR, DMA_CCR_TCIE);
}

/**
  * @brief  Disable trigger overrun interrupt.
  * @rmtoll
  *  CCR           TOIE       LL_DMA_DisableIT_TO
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_TO(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_TOIE);
}

/**
  * @brief  Disable suspension interrupt.
  * @rmtoll
  *  CCR           SUSPIE       LL_DMA_DisableIT_SUSP
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_SUSP(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_SUSPIE);
}

/**
  * @brief  Disable user setting error interrupt.
  * @rmtoll
  *  CCR           USEIE        LL_DMA_DisableIT_USE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_USE(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_USEIE);
}

/**
  * @brief  Disable update link transfer error interrupt.
  * @rmtoll
  *  CCR           ULEIE        LL_DMA_DisableIT_ULE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_ULE(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_ULEIE);
}

/**
  * @brief  Disable data transfer error interrupt.
  * @rmtoll
  *  CCR           DTEIE        LL_DMA_DisableIT_DTE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_DTE(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_DTEIE);
}

/**
  * @brief  Disable half transfer complete interrupt.
  * @rmtoll
  *  CCR           HTIE         LL_DMA_DisableIT_HT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_HT(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_HTIE);
}

/**
  * @brief  Disable transfer complete interrupt.
  * @rmtoll
  *  CCR           TCIE         LL_DMA_DisableIT_TC
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  */
__STATIC_INLINE void LL_DMA_DisableIT_TC(DMA_Channel_TypeDef *channel)
{
  CLEAR_BIT(channel->CCR, DMA_CCR_TCIE);
}

/**
  * @brief  Check if trigger overrun interrupt is enabled.
  * @rmtoll
  *  CCR           TOIE       LL_DMA_IsEnabledIT_TO
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TO(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_TOIE) == DMA_CCR_TOIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if suspension interrupt is enabled.
  * @rmtoll
  *  CCR           SUSPIE       LL_DMA_IsEnabledIT_SUSP
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_SUSP(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_SUSPIE) == DMA_CCR_SUSPIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if user setting error interrupt is enabled.
  * @rmtoll
  *  CCR           USEIE        LL_DMA_IsEnabledIT_USE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_USE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_USEIE) == DMA_CCR_USEIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if update link transfer error interrupt is enabled.
  * @rmtoll
  *  CCR        ULEIE         LL_DMA_IsEnabledIT_ULE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_ULE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_ULEIE) == DMA_CCR_ULEIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if data transfer error interrupt is enabled.
  * @rmtoll
  *  CCR        DTEIE         LL_DMA_IsEnabledIT_DTE
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_DTE(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_DTEIE) == DMA_CCR_DTEIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if half transfer complete interrupt is enabled.
  * @rmtoll
  *  CCR        HTIE         LL_DMA_IsEnabledIT_HT
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_HT(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_HTIE) == DMA_CCR_HTIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if transfer complete interrupt is enabled.
  * @rmtoll
  *  CCR        TCIE         LL_DMA_IsEnabledIT_TC
  * @param  channel This parameter can be one of the following values:
  *         @arg @ref LL_GPDMA1_CH0
  *         @arg @ref LL_GPDMA1_CH1
  *         @arg @ref LL_GPDMA1_CH2
  *         @arg @ref LL_GPDMA1_CH3
  *         @arg @ref LL_GPDMA1_CH4
  *         @arg @ref LL_GPDMA1_CH5
  *         @arg @ref LL_GPDMA1_CH6
  *         @arg @ref LL_GPDMA1_CH7
  *         @arg @ref LL_GPDMA1_CH8
  *         @arg @ref LL_GPDMA1_CH9
  *         @arg @ref LL_GPDMA1_CH10
  *         @arg @ref LL_GPDMA1_CH11
  *         @arg @ref LL_GPDMA1_CH12
  *         @arg @ref LL_GPDMA1_CH13
  *         @arg @ref LL_GPDMA1_CH14
  *         @arg @ref LL_GPDMA1_CH15
  *         @arg @ref LL_LPDMA1_CH0
  *         @arg @ref LL_LPDMA1_CH1
  *         @arg @ref LL_LPDMA1_CH2
  *         @arg @ref LL_LPDMA1_CH3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TC(const DMA_Channel_TypeDef *channel)
{
  return ((READ_BIT(channel->CCR, DMA_CCR_TCIE) == DMA_CCR_TCIE) ? 1UL : 0UL);
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* (defined (GPDMA1) || defined (LPDMA1)) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_LL_DMA_H */
