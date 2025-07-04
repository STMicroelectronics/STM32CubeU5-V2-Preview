/**
  ******************************************************************************
  * @file    stm32u5xx_hal_fdcan.h
  * @brief   Header file of FDCAN HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_FDCAN_H
#define STM32U5xx_HAL_FDCAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

#if defined(FDCAN1)

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup FDCAN FDCAN
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Constants FDCAN Exported Constants
  * @{
  */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)

/** @defgroup FDCAN_Error_Codes FDCAN Error Codes
  * @{
  */

#define HAL_FDCAN_ERROR_NONE               (0UL)       /*!< No error                                               */
#define HAL_FDCAN_ERROR_LOG_OVERFLOW       (1UL << 0U) /*!< Overflow of CAN Error Logging Counter                  */
#define HAL_FDCAN_ERROR_RAM_WDG            (1UL << 1U) /*!< Message RAM Watchdog event occurred                    */
#define HAL_FDCAN_ERROR_PROTOCOL_ARBT      (1UL << 2U) /*!< Protocol Error in Arbitration Phase (Nominal Bit Time) */
#define HAL_FDCAN_ERROR_PROTOCOL_DATA      (1UL << 3U) /*!< Protocol Error in Data Phase (Data Bit Time)           */
#define HAL_FDCAN_ERROR_RESERVED_AREA      (1UL << 4U) /*!< Access to Reserved Address                             */
#define HAL_FDCAN_ERROR_TIMEOUT_OCCURED    (1UL << 5U) /*!< Timeout Occurred                                       */
#define HAL_FDCAN_ERROR_RAM_ACCESS_FAILURE (1UL << 6U) /*!< Message RAM access failure occurred                    */
#define HAL_FDCAN_ERROR_BUS_FAULT_OFF      (1UL << 7U) /*!< Bus_Off status changed                                 */
#define HAL_FDCAN_ERROR_BUS_FAULT_PASSIVE  (1UL << 8U) /*!< Error_Passive status changed                           */
#define HAL_FDCAN_ERROR_BUS_FAULT_WARNING  (1UL << 9U) /*!< Error_Warning status changed                           */

/**
  * @}
  */
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

/** @defgroup FDCAN_Interrupt_Groups FDCAN Interrupt Groups
  * @{
  */

/**
  * @brief Rx FIFO0 group.
  *        This group contains the following interrupts:
  *        - Rx FIFO0 new message
  *        - Rx FIFO0 full
  *        - Rx FIFO0 message lost
  */
#define HAL_FDCAN_IT_GROUP_RX_FIFO0       (FDCAN_ILS_RXFIFO0)

/**
  * @brief Rx FIFO1 group.
  *        This group contains the following interrupts:
  *        - Rx FIFO1 new message
  *        - Rx FIFO1 full
  *        - Rx FIFO1 message lost
  */
#define HAL_FDCAN_IT_GROUP_RX_FIFO1       (FDCAN_ILS_RXFIFO1)

/**
  * @brief Status message group.
  *        This group contains the following interrupts:
  *        - Rx high priority message
  *        - Tx complete
  *        - Tx abort complete
  */
#define HAL_FDCAN_IT_GROUP_STATUS_MSG     (FDCAN_ILS_SMSG)

/**
  * @brief Tx FIFO error group.
  *        This group contains the following interrupts:
  *        - Tx FIFO empty
  *        - Tx event FIFO new data
  *        - Tx event FIFO full
  *        - Tx event FIFO element lost
  */
#define HAL_FDCAN_IT_GROUP_TX_FIFO_ERROR  (FDCAN_ILS_TFERR)

/**
  * @brief Miscellaneous group.
  *        This group contains the following interrupts:
  *        - Timestamp wraparound
  *        - Message RAM access failure
  *        - Timeout occurred
  */
#define HAL_FDCAN_IT_GROUP_MISC           (FDCAN_ILS_MISC)

/**
  * @brief Bit and line error group.
  *        This group contains the following interrupts:
  *        - Error logging overflow
  *        - Error passive
  */
#define HAL_FDCAN_IT_GROUP_BIT_LINE_ERROR (FDCAN_ILS_BERR)

/**
  * @brief Protocol error group.
  *        This group contains the following interrupts:
  *        - Error warning
  *        - Bus off
  *        - Message RAM watchdog
  *        - Protocol error in arbitration phase
  *        - Protocol error in data phase
  *        - Reserved address access error
  */
#define HAL_FDCAN_IT_GROUP_PROTOCOL_ERROR (FDCAN_ILS_PERR)

/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Sources FDCAN Interrupt Sources
  * @{
  */

/* FDCAN Interrupt Group Rx FIFO0 */
#define HAL_FDCAN_IT_RX_FIFO0_NEW_MSG        FDCAN_IE_RF0NE /*!< Rx FIFO0 new message interrupt                      */
#define HAL_FDCAN_IT_RX_FIFO0_FULL           FDCAN_IE_RF0FE /*!< Rx FIFO0 full interrupt                             */
#define HAL_FDCAN_IT_RX_FIFO0_MSG_LOST       FDCAN_IE_RF0LE /*!< Rx FIFO0 message lost interrupt                     */

/* FDCAN Interrupt Group Rx FIFO1 */
#define HAL_FDCAN_IT_RX_FIFO1_NEW_MSG        FDCAN_IE_RF1NE /*!< Rx FIFO1 new message interrupt                      */
#define HAL_FDCAN_IT_RX_FIFO1_FULL           FDCAN_IE_RF1FE /*!< Rx FIFO1 full interrupt                             */
#define HAL_FDCAN_IT_RX_FIFO1_MSG_LOST       FDCAN_IE_RF1LE /*!< Rx FIFO1 message lost interrupt                     */

/* FDCAN Interrupt Group status message */
#define HAL_FDCAN_IT_RX_HIGH_PRIORITY_MSG    FDCAN_IE_HPME  /*!< High priority message received                      */
#define HAL_FDCAN_IT_TX_COMPLETE             FDCAN_IE_TCE   /*!< Transmission Completed                              */
#define HAL_FDCAN_IT_TX_ABORT_COMPLETE       FDCAN_IE_TCFE  /*!< Transmission Cancellation Finished                  */

/* FDCAN Interrupt Group Tx FIFO error */
#define HAL_FDCAN_IT_TX_FIFO_EMPTY           FDCAN_IE_TFEE  /*!< Tx FIFO Empty                                       */
#define HAL_FDCAN_IT_TX_EVT_FIFO_NEW_DATA    FDCAN_IE_TEFNE /*!< Tx Handler wrote Tx Event FIFO element              */
#define HAL_FDCAN_IT_TX_EVT_FIFO_FULL        FDCAN_IE_TEFFE /*!< Tx Event FIFO full                                  */
#define HAL_FDCAN_IT_TX_EVT_FIFO_ELT_LOST    FDCAN_IE_TEFLE /*!< Tx Event FIFO element lost                          */

/* FDCAN Interrupt Group MISC */
#define HAL_FDCAN_IT_TIMESTAMP_WRAPAROUND    FDCAN_IE_TSWE  /*!< Timestamp counter wrapped around                    */
#define HAL_FDCAN_IT_RAM_ACCESS_FAILURE      FDCAN_IE_MRAFE /*!< Message RAM access failure occurred                 */
#define HAL_FDCAN_IT_TIMEOUT_OCCURRED        FDCAN_IE_TOOE  /*!< Timeout reached                                     */

/* FDCAN Interrupt Group bit and line error */
#define HAL_FDCAN_IT_ERROR_LOGGING_OVERFLOW  FDCAN_IE_ELOE  /*!< Overflow of FDCAN Error Logging Counter occurred    */
#define HAL_FDCAN_IT_ERROR_PASSIVE           FDCAN_IE_EPE   /*!< Error_Passive status changed                        */

/* FDCAN Interrupt Group protocol error */
#define HAL_FDCAN_IT_ERROR_WARNING           FDCAN_IE_EWE   /*!< Error_Warning status changed                        */
#define HAL_FDCAN_IT_BUS_OFF                 FDCAN_IE_BOE   /*!< Bus_Off status changed                              */
#define HAL_FDCAN_IT_RAM_WATCHDOG            FDCAN_IE_WDIE  /*!< Message RAM Watchdog event due to missing READY     */
#define HAL_FDCAN_IT_ARB_PROTOCOL_ERROR      FDCAN_IE_PEAE  /*!< Protocol error in arbitration phase detected        */
#define HAL_FDCAN_IT_DATA_PROTOCOL_ERROR     FDCAN_IE_PEDE  /*!< Protocol error in data phase detected               */
#define HAL_FDCAN_IT_RESERVED_ADDRESS_ACCESS FDCAN_IE_ARAE  /*!< Access to reserved address occurred                 */

/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Flags FDCAN Interrupt Flags
  * @brief FDCAN interrupt register (FDCAN_IR): The flags are set when one of the listed conditions is detected.
  * @{
  */

#define HAL_FDCAN_FLAG_RX_FIFO0_MSG_LOST       FDCAN_IR_RF0L /*!< Rx FIFO 0 message lost                           */
#define HAL_FDCAN_FLAG_RX_FIFO0_FULL           FDCAN_IR_RF0F /*!< Rx FIFO 0 full                                   */
#define HAL_FDCAN_FLAG_RX_FIFO0_NEW_MSG        FDCAN_IR_RF0N /*!< New message written to Rx FIFO 0                 */
#define HAL_FDCAN_FLAG_RX_FIFO1_MSG_LOST       FDCAN_IR_RF1L /*!< Rx FIFO 1 message lost                           */
#define HAL_FDCAN_FLAG_RX_FIFO1_FULL           FDCAN_IR_RF1F /*!< Rx FIFO 1 full                                   */
#define HAL_FDCAN_FLAG_RX_FIFO1_NEW_MSG        FDCAN_IR_RF1N /*!< New message written to Rx FIFO 1                 */
#define HAL_FDCAN_FLAG_RX_HIGH_PRIORITY_MSG    FDCAN_IR_HPM  /*!< High priority message received                   */
#define HAL_FDCAN_FLAG_TX_COMPLETE             FDCAN_IR_TC   /*!< Transmission Completed                           */
#define HAL_FDCAN_FLAG_TX_ABORT_COMPLETE       FDCAN_IR_TCF  /*!< Transmission Cancellation Finished               */
#define HAL_FDCAN_FLAG_TX_FIFO_EMPTY           FDCAN_IR_TFE  /*!< Tx FIFO Empty                                    */
#define HAL_FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST    FDCAN_IR_TEFL /*!< Tx Event FIFO element lost                       */
#define HAL_FDCAN_FLAG_TX_EVT_FIFO_FULL        FDCAN_IR_TEFF /*!< Tx Event FIFO full                               */
#define HAL_FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA    FDCAN_IR_TEFN /*!< Tx Handler wrote Tx Event FIFO element           */
#define HAL_FDCAN_FLAG_RAM_ACCESS_FAILURE      FDCAN_IR_MRAF /*!< Message RAM access failure occurred              */
#define HAL_FDCAN_FLAG_ERROR_LOGGING_OVERFLOW  FDCAN_IR_ELO  /*!< Overflow of FDCAN Error Logging Counter occurred */
#define HAL_FDCAN_FLAG_ERROR_PASSIVE           FDCAN_IR_EP   /*!< Error_Passive status changed                     */
#define HAL_FDCAN_FLAG_ERROR_WARNING           FDCAN_IR_EW   /*!< Error_Warning status changed                     */
#define HAL_FDCAN_FLAG_BUS_OFF                 FDCAN_IR_BO   /*!< Bus_Off status changed                           */
#define HAL_FDCAN_FLAG_RAM_WATCHDOG            FDCAN_IR_WDI  /*!< Message RAM Watchdog event due to missing READY  */
#define HAL_FDCAN_FLAG_ARB_PROTOCOL_ERROR      FDCAN_IR_PEA  /*!< Protocol error in arbitration phase detected     */
#define HAL_FDCAN_FLAG_DATA_PROTOCOL_ERROR     FDCAN_IR_PED  /*!< Protocol error in data phase detected            */
#define HAL_FDCAN_FLAG_RESERVED_ADDRESS_ACCESS FDCAN_IR_ARA  /*!< Access to reserved address occurred              */
#define HAL_FDCAN_FLAG_TIMESTAMP_WRAPAROUND    FDCAN_IR_TSW  /*!< Timestamp counter wrapped around                 */
#define HAL_FDCAN_FLAG_TIMEOUT_OCCURRED        FDCAN_IR_TOO  /*!< Timeout reached                                  */

/**
  * @}
  */

/** @defgroup FDCAN_IT_Tx_Complete_Buffers_select FDCAN Interrupt Tx Complete Buffers select
  * @{
  */

#define HAL_FDCAN_IT_TX_CPLT_BUFFER_0    (0x01UL << FDCAN_TXBTIE_TIE_Pos)  /*!< Tx complete interrupt on Tx buffer 0      */
#define HAL_FDCAN_IT_TX_CPLT_BUFFER_1    (0x02UL << FDCAN_TXBTIE_TIE_Pos)  /*!< Tx complete interrupt on Tx buffer 1      */
#define HAL_FDCAN_IT_TX_CPLT_BUFFER_2    (0x04UL << FDCAN_TXBTIE_TIE_Pos)  /*!< Tx complete interrupt on Tx buffer 2      */
#define HAL_FDCAN_IT_TX_CPLT_BUFFER_ALL  (HAL_FDCAN_IT_TX_CPLT_BUFFER_0   \
                                          | HAL_FDCAN_IT_TX_CPLT_BUFFER_1 \
                                          | HAL_FDCAN_IT_TX_CPLT_BUFFER_2) /*!< Tx complete interrupt on all Tx buffers   */

/**
  * @}
  */

/**  @defgroup FDCAN_IT_Tx_Abort_Buffers_select FDCAN Interrupt Tx Abort Buffer select
  * @{
  */

#define HAL_FDCAN_IT_TX_ABORT_BUFFER_0     (0x01UL << FDCAN_TXBCIE_CFIE_Pos)  /*!< Tx abort interrupt on Tx buffer 0      */
#define HAL_FDCAN_IT_TX_ABORT_BUFFER_1     (0x02UL << FDCAN_TXBCIE_CFIE_Pos)  /*!< Tx abort interrupt on Tx buffer 1      */
#define HAL_FDCAN_IT_TX_ABORT_BUFFER_2     (0x04UL << FDCAN_TXBCIE_CFIE_Pos)  /*!< Tx abort interrupt on Tx buffer 2      */
#define HAL_FDCAN_IT_TX_ABORT_BUFFER_ALL   (HAL_FDCAN_IT_TX_ABORT_BUFFER_0   \
                                            | HAL_FDCAN_IT_TX_ABORT_BUFFER_1 \
                                            | HAL_FDCAN_IT_TX_ABORT_BUFFER_2) /*!< Tx abort interrupt on all Tx buffers   */

/**
  * @}
  */

/** @defgroup FDCAN_Tx_Buffer_location HAL FDCAN Tx Location
  * @{
  */

#define HAL_FDCAN_TX_NO_BUFFER   0U                        /*!< No selected Tx Buffer */
#define HAL_FDCAN_TX_BUFFER0     (1U << 0U)                /*!< Tx Buffer 0           */
#define HAL_FDCAN_TX_BUFFER1     (1U << 1U)                /*!< Tx Buffer 1           */
#define HAL_FDCAN_TX_BUFFER2     (1U << 2U)                /*!< Tx Buffer 2           */
#define HAL_FDCAN_TX_BUFFER_ALL  (HAL_FDCAN_TX_BUFFER0   \
                                  | HAL_FDCAN_TX_BUFFER1 \
                                  | HAL_FDCAN_TX_BUFFER2)  /*!< All Tx Buffers        */

/**
  * @}
  */

/** @defgroup FDCAN_TIMEOUT_SELECT FDCAN Timeout Select Configuration
  * @{
  */

#define HAL_FDCAN_TOCC_TOS_TX_FIFO  (1UL << 1U)                     /*!< Timeout controlled by Tx event FIFO */
#define HAL_FDCAN_TOCC_TOS_RX_FIFO0 (1UL << 2U)                     /*!< Timeout controlled by Rx FIFO 0     */
#define HAL_FDCAN_TOCC_TOS_RX_FIFO1 (HAL_FDCAN_TOCC_TOS_TX_FIFO \
                                     | HAL_FDCAN_TOCC_TOS_RX_FIFO0) /*!< Timeout controlled by Rx FIFO 1     */

/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Lines FDCAN Interrupt Lines
  * @brief    FDCAN Interrupt lines
  * @{
  */

#define HAL_FDCAN_IT_LINE_0 (1U << 0U) /*!< Interrupt line 0 */
#define HAL_FDCAN_IT_LINE_1 (1U << 1U) /*!< Interrupt line 1 */

/**
  * @}
  */

/** @defgroup FDCAN_frame_type FDCAN Frame Type
  * @{
  */

#define HAL_FDCAN_FRAME_DATA   0U /*!< Data frame type   */
#define HAL_FDCAN_FRAME_REMOTE 1U /*!< Remote frame type */

/**
  * @}
  */

/** @defgroup FDCAN_id_type FDCAN ID type
  * @{
  */

#define HAL_FDCAN_ID_STANDARD 0U /*!< Standard ID type */
#define HAL_FDCAN_ID_EXTENDED 1U /*!< Extended ID type */

/**
  * @}
  */

/** @defgroup FDCAN_error_state_indicator FDCAN error state indicator
  * @{
  */

#define HAL_FDCAN_ERROR_STATE_IND_ACTIVE  0U /*!< Active error state indicator  */
#define HAL_FDCAN_ERROR_STATE_IND_PASSIVE 1U /*!< Passive error state indicator */

/**
  * @}
  */

/** @defgroup FDCAN_bit_rate_switching FDCAN bit rate switching
  * @{
  */

#define HAL_FDCAN_BIT_RATE_SWITCH_OFF 0U /*!< Bit rate switching OFF */
#define HAL_FDCAN_BIT_RATE_SWITCH_ON  1U /*!< Bit rate switching ON  */

/**
  * @}
  */

/** @defgroup FDCAN_header_frame_format FDCAN header frame format
  * @{
  */

#define HAL_FDCAN_FRAME_FORMAT_CAN    0U /*!< Standard frame format                       */
#define HAL_FDCAN_FRAME_FORMAT_FD_CAN 1U /*!< FDCAN frame format (new DLC-coding and CRC) */

/**
  * @}
  */

/** @defgroup FDCAN_event_FIFO FDCAN event FIFO
  * @{
  */

#define HAL_FDCAN_FIFO_NO_TX_EVENTS    0U /*!< Do not store Tx event in FIFO */
#define HAL_FDCAN_FIFO_STORE_TX_EVENTS 1U /*!< Store Tx event in FIFO        */

/**
  * @}
  */

/** @defgroup FDCAN_Tx_event_type FDCAN Tx event type
  * @{
  */

#define HAL_FDCAN_TX_EVENT                   1U /*!< Tx event                              */
#define HAL_FDCAN_TX_EVENT_IN_SPITE_OF_ABORT 2U /*!< Transmission in spite of cancellation */

/**
  * @}
  */

/** @defgroup FDCAN_data_length_code FDCAN Data Length Code
  * The definition is the following one:
  *  - 0 to 8:  classic CAN & CAN FD: received frame has 0 to 8 data bytes
  *  - 9 to 15: classic CAN: received frame has 8 data bytes (max)
  *  - 9 to 15: CAN FD: received frame has 12/16/20/24/32/48/64 data bytes
  * @{
  */

#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_0BYTE 0x0U /*!< 0 byte data length code   */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_1BYTE 0x1U /*!< 1 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_2BYTE 0x2U /*!< 2 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_3BYTE 0x3U /*!< 3 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_4BYTE 0x4U /*!< 4 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_5BYTE 0x5U /*!< 5 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_6BYTE 0x6U /*!< 6 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_7BYTE 0x7U /*!< 7 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_CAN_FDCAN_8BYTE 0x8U /*!< 8 bytes data length code  */
#define HAL_FDCAN_DATA_LGTH_FDCAN_12BYTE    0x9U /*!< 12 bytes data length code */
#define HAL_FDCAN_DATA_LGTH_FDCAN_16BYTE    0xAU /*!< 16 bytes data length code */
#define HAL_FDCAN_DATA_LGTH_FDCAN_20BYTE    0xBU /*!< 20 bytes data length code */
#define HAL_FDCAN_DATA_LGTH_FDCAN_24BYTE    0xCU /*!< 24 bytes data length code */
#define HAL_FDCAN_DATA_LGTH_FDCAN_32BYTE    0xDU /*!< 32 bytes data length code */
#define HAL_FDCAN_DATA_LGTH_FDCAN_48BYTE    0xEU /*!< 48 bytes data length code */
#define HAL_FDCAN_DATA_LGTH_FDCAN_64BYTE    0xFU /*!< 64 bytes data length code */

/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Types FDCAN Exported Types
  * @{
  */

/**
  * @brief  FDCAN Frame Format
  */
typedef enum
{
  HAL_FDCAN_FRAME_CLASSIC_CAN = 0U,                                              /*!< Classic mode                      */
  HAL_FDCAN_FRAME_FD_NO_BRS   = FDCAN_CCCR_FDOE,                                 /*!< FD mode without BitRate Switching */
  HAL_FDCAN_FRAME_FD_BRS      = ((uint32_t)(FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE)), /*!< FD mode with BitRate Switching    */
} hal_fdcan_frame_format_t;

/**
  * @brief  FDCAN Timestamp Selection
  */
typedef enum
{
  HAL_FDCAN_TIMESTAMP_SOURCE_ZERO        = 0U,                            /*!< Timestamp counter value is 0x0000                    */
  HAL_FDCAN_TIMESTAMP_SOURCE_INTERNAL    = (0x1UL << FDCAN_TSCC_TSS_Pos), /*!< Timestamp counter value incremented according to TCP */
  HAL_FDCAN_TIMESTAMP_SOURCE_EXTERNAL    = (0x2UL << FDCAN_TSCC_TSS_Pos), /*!< External timestamp counter                           */
} hal_fdcan_timestamp_source_t;

/**
  * @brief  FDCAN High Priority filter list definition
  */
typedef enum
{
  HAL_FDCAN_HIGH_PRIO_FILTER_STANDARD = 0U,              /*!< Standard filter list */
  HAL_FDCAN_HIGH_PRIO_FILTER_EXTENDED = FDCAN_HPMS_FLST, /*!< Extended filter list */
} hal_fdcan_high_prio_filter_list_t;

/**
  * @brief  FDCAN Error Status definition
  */
typedef enum
{
  HAL_FDCAN_ERROR_ACTIVE  = 0U, /*!< Error_Active state  */
  HAL_FDCAN_ERROR_PASSIVE = 1U, /*!< Error_Passive state */
} hal_fdcan_protocol_error_status_t;

/**
  * @brief  FDCAN Receive Error passive level definition
  */
typedef enum
{
  HAL_FDCAN_RX_ERROR_PASSIVE_BELOW_LEVEL = 0U,           /*!< The receive error counter is below the error passive level of 128    */
  HAL_FDCAN_RX_ERROR_PASSIVE_REACH_LEVEL = FDCAN_ECR_RP, /*!< The receive error counter has reached the error passive level of 128 */
} hal_fdcan_rx_error_passive_level_t;

/**
  * @brief  FDCAN State structures definition
  */
typedef enum
{
  HAL_FDCAN_STATE_RESET      = 0U,          /*!< Not yet Initialized                               */
  HAL_FDCAN_STATE_INIT       = (1U << 31U), /*!< Initialized but not yet configured                */
  HAL_FDCAN_STATE_IDLE       = (1U << 30U), /*!< Initialized and a global config applied           */
  HAL_FDCAN_STATE_ACTIVE     = (1U << 29U), /*!< The peripheral is running                         */
  HAL_FDCAN_STATE_POWER_DOWN = (1U << 28U), /*!< The peripheral is in power down mode (sleep mode) */
} hal_fdcan_state_t;

/**
  * @brief  HAL FDCAN mode enumeration definition
  */
typedef enum
{
  HAL_FDCAN_MODE_NORMAL               = 0U, /*!< Normal mode               */
  HAL_FDCAN_MODE_RESTRICTED_OPERATION = 1U, /*!< Restricted Operation mode */
  HAL_FDCAN_MODE_BUS_MONITORING       = 2U, /*!< Bus Monitoring mode       */
  HAL_FDCAN_MODE_INTERNAL_LOOPBACK    = 3U, /*!< Internal LoopBack mode    */
  HAL_FDCAN_MODE_EXTERNAL_LOOPBACK    = 4U, /*!< External LoopBack mode    */
  HAL_FDCAN_MODE_INVALID              = 5U, /*!< FDCAN Invalid mode        */
} hal_fdcan_mode_t;

/**
  * @brief  HAL FDCAN Auto Retransmission setting
  */
typedef enum
{
  HAL_FDCAN_AUTO_RETRANSMISSION_ENABLED  = 0U, /*!< Transmitter Auto retransmission enabled  */
  HAL_FDCAN_AUTO_RETRANSMISSION_DISABLED = 1U, /*!< Transmitter Auto retransmission disabled */
} hal_fdcan_auto_retransmission_status_t;

/**
  * @brief  HAL FDCAN Transmit Pause setting
  */
typedef enum
{
  HAL_FDCAN_TRANSMIT_PAUSE_DISABLED = 0U, /*!< Transmitter transmit pause disabled */
  HAL_FDCAN_TRANSMIT_PAUSE_ENABLED  = 1U, /*!< Transmitter transmit pause enabled  */
} hal_fdcan_transmit_pause_status_t;

/**
  * @brief  HAL FDCAN Protocol exception setting
  */
typedef enum
{
  HAL_FDCAN_PROTOCOL_EXCEPTION_ENABLED  = 0U, /*!< Transmitter protocol exception enabled  */
  HAL_FDCAN_PROTOCOL_EXCEPTION_DISABLED = 1U, /*!< Transmitter protocol exception disabled */
} hal_fdcan_protocol_exception_status_t;

/**
  * @brief  HAL FDCAN Transmitter delay Compensation setting
  */
typedef enum
{
  HAL_FDCAN_TX_DLY_COMPENSATION_DISABLED = 0U, /*!< Transmitter delay compensation disabled */
  HAL_FDCAN_TX_DLY_COMPENSATION_ENABLED  = 1U, /*!< Transmitter delay compensation enabled  */
} hal_fdcan_transmitter_delay_comp_status_t;

/**
  * @brief  HAL FDCAN ISO Mode setting
  */
typedef enum
{
  HAL_FDCAN_ISO_MODE_ENABLED  = 0U, /*!< Protocol configured for ISO mode         */
  HAL_FDCAN_ISO_MODE_DISABLED = 1U, /*!< Protocol configured for CAN FD v2.0 mode */
} hal_fdcan_iso_mode_status_t;

/**
  * @brief  HAL FDCAN Buffer status
  */
typedef enum
{
  HAL_FDCAN_BUFFER_NOT_PENDING = 0U, /*!< No buffer pending           */
  HAL_FDCAN_BUFFER_PENDING     = 1U, /*!< At least one buffer pending */
} hal_fdcan_buffer_status_t;

/**
  * @brief  HAL FDCAN Restricted Operation Mode setting
  */
typedef enum
{
  HAL_FDCAN_RESTRICTED_MODE_DISABLED = 0U, /*!< Restricted mode disabled */
  HAL_FDCAN_RESTRICTED_MODE_ENABLED  = 1U, /*!< Restricted mode enabled  */
} hal_fdcan_restricted_op_mode_status_t;

/**
  * @brief  HAL FDCAN Edge filtering setting
  */
typedef enum
{
  HAL_FDCAN_EDGE_FILTERING_DISABLED = 0U, /*!< Edge Filtering disabled */
  HAL_FDCAN_EDGE_FILTERING_ENABLED  = 1U, /*!< Edge Filtering enabled  */
} hal_fdcan_edge_filtering_status_t;

/**
  * @brief  HAL FDCAN FIFO operation mode
  */
typedef enum
{
  HAL_FDCAN_RX_FIFO_BLOCKING  = 0U, /*!< Rx FIFO blocking mode  */
  HAL_FDCAN_RX_FIFO_OVERWRITE = 1U, /*!< Rx FIFO overwrite mode */
} hal_fdcan_rx_fifo_operative_mode_t;

/**
  * @brief  HAL FDCAN Fifo/Queue status- free or full
  */
typedef enum
{
  HAL_FDCAN_FIFO_STATUS_FREE = 0U,               /*!< Tx FIFO queue not full */
  HAL_FDCAN_FIFO_STATUS_FULL = FDCAN_TXFQS_TFQF, /*!< Tx FIFO queue full     */
} hal_fdcan_fifo_status_t;


/**
  * @brief  FDCAN filter type, used for standard and extended filters.
  * The case HAL_FDCAN_FILTER_RANGE_NO_EIDM must be processed differently depending on standard or extended filter.
  */
typedef enum
{
  HAL_FDCAN_FILTER_RANGE         = 0U, /*!< Range filter from FilterID1 to FilterID2                        */
  HAL_FDCAN_FILTER_DUAL          = 1U, /*!< Dual ID filter for FilterID1 or FilterID2                       */
  HAL_FDCAN_FILTER_CLASSIC       = 2U, /*!< Classic filter: FilterID1 = filter, FilterID2 = mask            */
  HAL_FDCAN_FILTER_RANGE_NO_EIDM = 3U, /*!< Range filter from FilterID1 to FilterID2, EIDM mask not applied */
} hal_fdcan_filter_type_t;

/**
  * @brief  HAL FDCAN Timeout Counter configuration
  */
typedef enum
{
  HAL_FDCAN_TIMEOUT_COUNTER_DISABLED = 0U, /*!< Timeout counter disabled */
  HAL_FDCAN_TIMEOUT_COUNTER_ENABLED  = 1U, /*!< Timeout counter enabled  */
} hal_fdcan_timeout_counter_status_t;

/**
  * @brief  HAL FDCAN Timestamp Counter configuration
  */
typedef enum
{
  HAL_FDCAN_TIMESTAMP_COUNTER_DISABLED = 0U, /*!< Timestamp counter disabled */
  HAL_FDCAN_TIMESTAMP_COUNTER_ENABLED  = 1U, /*!< Timestamp counter enabled  */
} hal_fdcan_timestamp_counter_status_t;

/**
  * @brief  FDCAN kernel clock divider
  */
typedef enum
{
  HAL_FDCAN_CLOCK_DIV1  = 0U,  /*!< Divide kernel clock by 1  */
  HAL_FDCAN_CLOCK_DIV2  = 1U,  /*!< Divide kernel clock by 2  */
  HAL_FDCAN_CLOCK_DIV4  = 2U,  /*!< Divide kernel clock by 4  */
  HAL_FDCAN_CLOCK_DIV6  = 3U,  /*!< Divide kernel clock by 6  */
  HAL_FDCAN_CLOCK_DIV8  = 4U,  /*!< Divide kernel clock by 8  */
  HAL_FDCAN_CLOCK_DIV10 = 5U,  /*!< Divide kernel clock by 10 */
  HAL_FDCAN_CLOCK_DIV12 = 6U,  /*!< Divide kernel clock by 12 */
  HAL_FDCAN_CLOCK_DIV14 = 7U,  /*!< Divide kernel clock by 14 */
  HAL_FDCAN_CLOCK_DIV16 = 8U,  /*!< Divide kernel clock by 16 */
  HAL_FDCAN_CLOCK_DIV18 = 9U,  /*!< Divide kernel clock by 18 */
  HAL_FDCAN_CLOCK_DIV20 = 10U, /*!< Divide kernel clock by 20 */
  HAL_FDCAN_CLOCK_DIV22 = 11U, /*!< Divide kernel clock by 22 */
  HAL_FDCAN_CLOCK_DIV24 = 12U, /*!< Divide kernel clock by 24 */
  HAL_FDCAN_CLOCK_DIV26 = 13U, /*!< Divide kernel clock by 26 */
  HAL_FDCAN_CLOCK_DIV28 = 14U, /*!< Divide kernel clock by 28 */
  HAL_FDCAN_CLOCK_DIV30 = 15U, /*!< Divide kernel clock by 30 */
} hal_fdcan_clock_divider_t;

/**
  * * @brief  FDCAN Tx FIFO/Queue mode
  */
typedef enum
{
  HAL_FDCAN_TX_MODE_FIFO  = 0U,              /*!< Tx FIFO mode  */
  HAL_FDCAN_TX_MODE_QUEUE = FDCAN_TXBC_TFQM, /*!< Tx Queue mode */
} hal_fdcan_tx_mode_t;

/**
  * @brief  FDCAN Interrupts status
  */
typedef enum
{
  HAL_FDCAN_IT_DISABLED = 0U, /*!< Interrupt disabled */
  HAL_FDCAN_IT_ENABLED  = 1U, /*!< Interrupt enabled  */
} hal_fdcan_it_status_t;

/**
  * @brief  FDCAN Interrupt Lines status
  */
typedef enum
{
  HAL_FDCAN_IT_LINE_DISABLED = 0U, /*!< Interrupt line disabled */
  HAL_FDCAN_IT_LINE_ENABLED  = 1U, /*!< Interrupt line enabled  */
} hal_fdcan_it_lines_status_t;

/**
  * @brief  FDCAN Tx buffer transmission complete interrupt status
  */
typedef enum
{
  HAL_FDCAN_IT_TXBUFFER_COMPLETE_DISABLED = 0U, /*!< Tx buffer transmission complete interrupt disabled */
  HAL_FDCAN_IT_TXBUFFER_COMPLETE_ENABLED  = 1U, /*!< Tx buffer transmission complete interrupt enabled  */
} hal_fdcan_it_txbuffer_complete_status_t;

/**
  * @brief  FDCAN Tx buffer abort finished interrupt status
  */
typedef enum
{
  HAL_FDCAN_IT_TXBUFFER_ABORT_DISABLED  = 0U, /*!< Tx buffer abort finished interrupt disabled */
  HAL_FDCAN_IT_TXBUFFER_ABORT_ENABLED   = 1U, /*!< Tx buffer abort finished interrupt enabled  */
} hal_fdcan_it_txbuffer_abort_status_t;

/**
  * @brief  FDCAN High Priority Storage
  */
typedef enum
{
  HAL_FDCAN_HIGH_PRIO_STORAGE_NO_FIFO  = 0U,                            /*!< No FIFO selected         */
  HAL_FDCAN_HIGH_PRIO_STORAGE_MSG_LOST = (0x1UL << FDCAN_HPMS_MSI_Pos), /*!< FIFO message lost        */
  HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO0  = (0x2UL << FDCAN_HPMS_MSI_Pos), /*!< Message stored in FIFO 0 */
  HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO1  = FDCAN_HPMS_MSI,                /*!< Message stored in FIFO 1 */
} hal_fdcan_high_prio_storage_t;

/**
  * @brief  FDCAN Warning Status
  */
typedef enum
{
  HAL_FDCAN_WARNING_ERROR_COUNTERS_UNDER_LIMIT = 0U, /*!< Both error counters are below the Error_Warning of 96                       */
  HAL_FDCAN_WARNING_ERROR_COUNTER_OVER_LIMIT   = 1U, /*!< At least one of the error counter has reached the Error_Warning limit of 96 */
} hal_fdcan_warning_status_t;

/**
  * @brief  FDCAN Bus_Off Status
  */
typedef enum
{
  HAL_FDCAN_BUS_OFF_DISABLED = 0U, /*!< The FDCAN is not in BUS_OFF state */
  HAL_FDCAN_BUS_OFF_ENABLED  = 1U, /*!< The FDCAN is in BUS_OFF state     */
} hal_fdcan_bus_off_status_t;

/**
  * @brief  FDCAN ESI flag of last received FDCAN message
  */
typedef enum
{
  HAL_FDCAN_ESI_FLAG_RESET = 0U, /*!< Last received FDCAN message did not have its ESI flag set */
  HAL_FDCAN_ESI_FLAG_SET   = 1U, /*!< Last received FDCAN message has its ESI flag set          */
} hal_fdcan_esi_flag_status_t;

/**
  * @brief  FDCAN BRS flag of last received FDCAN message
  */
typedef enum
{
  HAL_FDCAN_BRS_FLAG_RESET = 0U, /*!< Last received FDCAN message did not have its BRS flag set */
  HAL_FDCAN_BRS_FLAG_SET   = 1U, /*!< Last received FDCAN message has its BRS flag set          */
} hal_fdcan_brs_flag_status_t;

/**
  * @brief  FDCAN received FDCAN EDL (Extended Data length) message.
  */
typedef enum
{
  HAL_FDCAN_EDL_FLAG_RESET = 0U, /*!< No FDCAN Message has been received since this bit was reset by CPU */
  HAL_FDCAN_EDL_FLAG_SET   = 1U, /*!< Message in FDCAN format with EDL flag                              */
} hal_fdcan_edl_flag_status_t;

/**
  * @brief  FDCAN protocol exception event
  */
typedef enum
{
  HAL_FDCAN_PROTOCOL_NO_EVENT_OCCURRED = 0U, /*!< No protocol event occurred since last read access */
  HAL_FDCAN_PROTOCOL_EVENT_OCCURRED    = 1U, /*!< Protocol event occurred                           */
} hal_fdcan_protocol_exception_event_t;

/**
  * @brief  Filter Configuration
  */
typedef enum
{
  HAL_FDCAN_FILTER_DISABLE       = 0U, /*!< Disable filter element                                     */
  HAL_FDCAN_FILTER_TO_RXFIFO0    = 1U, /*!< Store in Rx FIFO 0 if filter matches                       */
  HAL_FDCAN_FILTER_TO_RXFIFO1    = 2U, /*!< Store in Rx FIFO 1 if filter matches                       */
  HAL_FDCAN_FILTER_REJECT        = 3U, /*!< Reject ID if filter matches                                */
  HAL_FDCAN_FILTER_HP            = 4U, /*!< Set high priority if filter matches                        */
  HAL_FDCAN_FILTER_TO_RXFIFO0_HP = 5U, /*!< Set high priority and store in FIFO 0 if filter matches    */
  HAL_FDCAN_FILTER_TO_RXFIFO1_HP = 6U, /*!< Set high priority and store in FIFO 1 if filter matches    */
} hal_fdcan_filter_config_t;


/**
  * @brief  HAL FDCAN Rx Location
  */
typedef enum
{
  HAL_FDCAN_RX_FIFO0    = 0U, /*!< Index for access to Rx FIFO 0     */
  HAL_FDCAN_RX_FIFO1    = 1U, /*!< Index for access to Rx FIFO 1     */
} hal_fdcan_rx_location_t;

/**
  * @brief  HAL FDCAN protocol error code
  */
typedef enum
{
  HAL_FDCAN_PROTOCOL_ERROR_NONE      = 0U, /*!< No error occurred         */
  HAL_FDCAN_PROTOCOL_ERROR_STUFF     = 1U, /*!< Stuff error               */
  HAL_FDCAN_PROTOCOL_ERROR_FORM      = 2U, /*!< Form error                */
  HAL_FDCAN_PROTOCOL_ERROR_ACK       = 3U, /*!< Acknowledge error         */
  HAL_FDCAN_PROTOCOL_ERROR_BIT1      = 4U, /*!< Bit 1 (recessive) error   */
  HAL_FDCAN_PROTOCOL_ERROR_BIT0      = 5U, /*!< Bit 0 (dominant) error    */
  HAL_FDCAN_PROTOCOL_ERROR_CRC       = 6U, /*!< CRC check sum error       */
  HAL_FDCAN_PROTOCOL_ERROR_NO_CHANGE = 7U, /*!< No change since last read */
} hal_fdcan_protocol_error_code_t;

/**
  * @brief  HAL FDCAN communication state
  */
typedef enum
{
  HAL_FDCAN_COM_STATE_SYNC = 0U,                           /*!< Node is synchronizing on CAN communication */
  HAL_FDCAN_COM_STATE_IDLE = (0x1UL << FDCAN_PSR_ACT_Pos), /*!< Node is neither receiver nor transmitter   */
  HAL_FDCAN_COM_STATE_RX   = (0x2UL << FDCAN_PSR_ACT_Pos), /*!< Node is operating as receiver              */
  HAL_FDCAN_COM_STATE_TX   = FDCAN_PSR_ACT,                /*!< Node is operating as transmitter           */
} hal_fdcan_communication_state_t;

/**
  * @brief  HAL FDCAN non-matching frames - Acceptance can be enabled via RXGFC[ANFS] and RXGFC[ANFE].
  */
typedef enum
{
  HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO0 = 0U, /*!< Accept non-matching frames in Rx FIFO 0 */
  HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO1 = 1U, /*!< Accept non-matching frames in Rx FIFO 1 */
  HAL_FDCAN_NON_MATCHING_REJECT          = 2U, /*!< Reject non-matching frames              */
} hal_fdcan_acceptance_non_matching_frame_t;

/**
  * @brief  HAL FDCAN reject remote frames
  */
typedef enum
{
  HAL_FDCAN_REMOTE_ACCEPT = 0U, /*!< Accept remote frames     */
  HAL_FDCAN_REMOTE_REJECT = 1U, /*!< Reject all remote frames */
} hal_fdcan_acceptance_remote_frame_t;

/**
  * @brief  HAL FDCAN timestamp prescaler FDCAN_TSCC_TCP_Pos
  */
typedef enum
{
  HAL_FDCAN_TIMESTAMP_PRESC_1  = 0U,                            /*!< Timestamp counter time unit equals CAN bit time                 */
  HAL_FDCAN_TIMESTAMP_PRESC_2  = (0x1UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 2 */
  HAL_FDCAN_TIMESTAMP_PRESC_3  = (0x2UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 3 */
  HAL_FDCAN_TIMESTAMP_PRESC_4  = (0x3UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 4 */
  HAL_FDCAN_TIMESTAMP_PRESC_5  = (0x4UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 5 */
  HAL_FDCAN_TIMESTAMP_PRESC_6  = (0x5UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 6 */
  HAL_FDCAN_TIMESTAMP_PRESC_7  = (0x6UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 7 */
  HAL_FDCAN_TIMESTAMP_PRESC_8  = (0x7UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 8 */
  HAL_FDCAN_TIMESTAMP_PRESC_9  = (0x8UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 9 */
  HAL_FDCAN_TIMESTAMP_PRESC_10 = (0x9UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 10 */
  HAL_FDCAN_TIMESTAMP_PRESC_11 = (0xAUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 11 */
  HAL_FDCAN_TIMESTAMP_PRESC_12 = (0xBUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 12 */
  HAL_FDCAN_TIMESTAMP_PRESC_13 = (0xCUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 13 */
  HAL_FDCAN_TIMESTAMP_PRESC_14 = (0xDUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 14 */
  HAL_FDCAN_TIMESTAMP_PRESC_15 = (0xEUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 15 */
  HAL_FDCAN_TIMESTAMP_PRESC_16 = (0xFUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit equals CAN bit time multiplied by 16 */
} hal_fdcan_timestamp_prescaler_t;

/**
  * @brief  HAL FDCAN Tx FIFO free level
  */
typedef enum
{
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_0  = 0U,  /*!< Tx FIFO Full - no free FIFO slot        */
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_1  = 1U,  /*!< 1 free FIFO slot available in Tx FIFO   */
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_2  = 2U,  /*!< 2 free FIFO slots available in Tx FIFO  */
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_3  = 3U,  /*!< 3 free FIFO slots available in Tx FIFO  */
} hal_fdcan_tx_fifo_free_level_t;

/**
  * @brief  HAL FDCAN timeout operation
  */
typedef enum
{
  HAL_FDCAN_TIMEOUT_CONTINUOUS    = 0U,                          /*!< Timeout continuous operation        */
  HAL_FDCAN_TIMEOUT_TX_EVENT_FIFO = HAL_FDCAN_TOCC_TOS_TX_FIFO,  /*!< Timeout controlled by Tx Event FIFO */
  HAL_FDCAN_TIMEOUT_RX_FIFO0      = HAL_FDCAN_TOCC_TOS_RX_FIFO0, /*!< Timeout controlled by Rx FIFO 0     */
  HAL_FDCAN_TIMEOUT_RX_FIFO1      = HAL_FDCAN_TOCC_TOS_RX_FIFO1, /*!< Timeout controlled by Rx FIFO 1     */
} hal_fdcan_timeout_operation_t;

/**
  * @brief  HAL FDCAN instance definition
  */
typedef enum
{
#if defined(FDCAN1)
  HAL_FDCAN1 = (uint32_t)FDCAN1, /*!< Peripheral instance FDCAN1 */
#endif /* FDCAN1 */
#if defined(FDCAN2)
  HAL_FDCAN2 = (uint32_t)FDCAN2, /*!< Peripheral instance FDCAN2 */
#endif /* FDCAN2 */
#if defined(FDCAN3)
  HAL_FDCAN3 = (uint32_t)FDCAN3, /*!< Peripheral instance FDCAN3 */
#endif /* FDCAN3 */
} hal_fdcan_t;

/**
  * @brief  FDCAN Rx element header definition
  */
typedef union
{
  uint64_t d64;  /*!< 64-bit FDCAN Rx element header                                                                */
  struct
  {
    uint32_t identifier : 29; /*!< Received identifier. A standard identifier is stored in bits [28:18]             */

    uint32_t frame_type : 1; /*!< Received frame type.
                                  This field is a value of @ref FDCAN_frame_type :
                                  - @ref HAL_FDCAN_FRAME_DATA :   received frame is a data frame
                                  - @ref HAL_FDCAN_FRAME_REMOTE : received frame is a remote frame                  */

    uint32_t identifier_type : 1; /*!< Received identifier type.
                                       This field is a value of @ref FDCAN_id_type :
                                       - @ref HAL_FDCAN_ID_STANDARD : 11-bit standard identifier
                                       - @ref HAL_FDCAN_ID_EXTENDED : 29-bit extended identifier                    */

    uint32_t error_state_indicator : 1; /*!< Error state indicator
                                             This field is a value of @ref FDCAN_error_state_indicator :
                                             - @ref HAL_FDCAN_ERROR_STATE_IND_ACTIVE :  Tx node is error active
                                             - @ref HAL_FDCAN_ERROR_STATE_IND_PASSIVE : Tx node is error passive    */

    uint32_t rx_timestamp : 16; /*!< Rx timestamp.
                                     Timestamp counter value is captured at the start of frame reception.
                                     Resolution depends on the Timestamp Counter Prescaler                          */

    uint32_t data_length : 4; /*!< Received frame Data Length Code.
                                   This field is a value of @ref FDCAN_data_length_code                             */

    uint32_t bit_rate_switch : 1; /*!< Bit rate switch indicator.
                                       This field is a value of @ref FDCAN_bit_rate_switching :
                                       - @ref HAL_FDCAN_BIT_RATE_SWITCH_OFF : Rx frame without bit rate switching
                                       - @ref HAL_FDCAN_BIT_RATE_SWITCH_ON :  Rx frame with bit rate switching      */

    uint32_t frame_format : 1; /*!< Received frame format.
                                    This field is a value of @ref FDCAN_header_frame_format :
                                    - @ref HAL_FDCAN_FRAME_FORMAT_CAN :    standard CAN frame format
                                    - @ref HAL_FDCAN_FRAME_FORMAT_FD_CAN : CAN FD frame format                      */

    uint32_t : 2; /*!< Rx Reserved                                                                                  */

    uint32_t filter_index : 7; /*!< Filter index.
                                    - 0-27: index of matching Rx acceptance filter element (invalid if ANMF = 1)
                                    - Range is 0 to (RXGFC[LSS] - 1) or (RXGFC[LSE] - 1)                            */

    uint32_t filter_matching_frame_status : 1; /*!< Accepted non-matching frame.
                                                    Possible values are:
                                                    - 0: received frame matches filter index FIDx
                                                    - 1: received frame did not match any Rx filter element         */
  } b; /*!< Bit fields of the 64-bit rx header                                                                      */
} hal_fdcan_rx_header_t;

/**
  * @brief  FDCAN Tx element header definition
  */
typedef union
{
  uint64_t d64; /*!< 64-bit FDCAN Tx element header                                                                 */
  struct
  {
    uint32_t identifier : 29; /*!< Frame identifier. A standard identifier is stored in bits [28:18]                */

    uint32_t frame_type : 1; /*!< Remote transmission request.
                                  - @ref HAL_FDCAN_FRAME_DATA :   frame is a data frame
                                  - @ref HAL_FDCAN_FRAME_REMOTE : frame is a remote frame                           */

    uint32_t identifier_type : 1; /*!< Identifier type - corresponds to bit XTD in reference manual
                                       This field can be a value of @ref FDCAN_id_type :
                                       - @ref HAL_FDCAN_ID_STANDARD : 11-bit standard identifier
                                       - @ref HAL_FDCAN_ID_EXTENDED : 29-bit extended identifier                    */

    uint32_t error_state_indicator : 1; /*!< Error state indicator - corresponds to bit ESI in reference manual
                                             This field can be a value of @ref FDCAN_error_state_indicator :
                                             - @ref HAL_FDCAN_ERROR_STATE_IND_ACTIVE :  Tx node is error active
                                             - @ref HAL_FDCAN_ERROR_STATE_IND_PASSIVE : Tx node is error passive    */

    uint32_t : 16; /*! Tx reserved field                                                                            */

    uint32_t data_length : 4; /*!< Data length code. This field can be a value of @ref FDCAN_data_length_code       */

    uint32_t bit_rate_switch : 1; /*!< Bit rate switch.
                                       This field can be a value of @ref FDCAN_bit_rate_switching :
                                       - @ref HAL_FDCAN_BIT_RATE_SWITCH_OFF : Tx frame without bit rate switching
                                       - @ref HAL_FDCAN_BIT_RATE_SWITCH_ON :  Tx frame with bit rate switching      */

    uint32_t frame_format : 1; /*!< Frame format.
                                    This field can be a value of @ref FDCAN_header_frame_format :
                                    - @ref HAL_FDCAN_FRAME_FORMAT_CAN :    standard CAN frame format
                                    - @ref HAL_FDCAN_FRAME_FORMAT_FD_CAN : CAN FD frame format                      */

    uint32_t : 1; /*!< Tx reserved bit                                                                              */

    uint32_t event_fifo_control : 1; /*!< Event FIFO control.
                                          This field can be a value of @ref FDCAN_event_FIFO
                                          - @ref HAL_FDCAN_FIFO_NO_TX_EVENTS    : Do not store Tx events
                                          - @ref HAL_FDCAN_FIFO_STORE_TX_EVENTS : Store Tx events                   */

    uint32_t message_marker : 8; /*!< Message marker.
                                      Written by CPU during Tx buffer configuration.
                                      Copied into Tx event FIFO element for identification of Tx message status     */

  } b; /*!< Bit fields of the 64-bit tx header                                                                      */
} hal_fdcan_tx_header_t;

/**
  * @brief  FDCAN Tx Event FIFO element header definition
  */
typedef union
{
  uint64_t d64; /*!< 64-bit FDCAN Tx Event FIFO element header                                                      */
  struct
  {
    uint32_t identifier: 29; /*!< Frame identifier, standard or extended. A standard identifier is stored
                                  into ID[28:18] field of Rx element                                                */

    uint32_t frame_type: 1; /*!< Frame type. This field can be a value of @ref FDCAN_frame_type :
                                 - @ref HAL_FDCAN_FRAME_DATA :   received frame is a data frame
                                 - @ref HAL_FDCAN_FRAME_REMOTE : received frame is a remote frame                   */

    uint32_t identifier_type: 1; /*!< Identifier type. This field can be a value of @ref FDCAN_id_type :
                                      - @ref HAL_FDCAN_ID_STANDARD : 11-bit standard identifier
                                      - @ref HAL_FDCAN_ID_EXTENDED : 29-bit extended identifier                     */

    uint32_t error_state_indicator: 1; /*!< Error state indicator. This field can be a value of
                                            @ref FDCAN_error_state_indicator :
                                            - @ref HAL_FDCAN_ERROR_STATE_IND_ACTIVE :  Tx node is error active
                                            - @ref HAL_FDCAN_ERROR_STATE_IND_PASSIVE : Tx node is error passive     */

    uint32_t tx_timestamp: 16; /*!< Tx Timestamp. The timestamp counter value is captured on start of
                                    frame transmission. Resolution depends on the configuration of the
                                    timestamp counter prescaler                                                     */

    uint32_t data_length: 4;    /*!< Data length code.
                                     This field can be a value of @ref FDCAN_data_length_code                       */

    uint32_t bit_rate_switch: 1;  /*!< Bit rate switch.
                                       This field can be a value of @ref FDCAN_bit_rate_switching
                                       - 0: Frames transmitted without bite rate switching
                                       - 1: Frames transmitted with bit rate switching                              */

    uint32_t frame_format: 1; /*!< Frame format.
                                   This field can be a value of @ref FDCAN_header_frame_format :
                                   - @ref HAL_FDCAN_FRAME_FORMAT_CAN :    standard CAN frame format
                                   - @ref HAL_FDCAN_FRAME_FORMAT_FD_CAN : CAN FD frame format                       */

    uint32_t event_type: 2; /*!< Event type.
                                 This field can be a value of @ref FDCAN_Tx_event_type :
                                 - @ref HAL_FDCAN_TX_EVENT                   : Tx event
                                 - @ref HAL_FDCAN_TX_EVENT_IN_SPITE_OF_ABORT : Transmission despite cancellation
                                (always set for transmission in DAR mode)                                           */

    uint32_t message_marker: 8; /*!< Message marker.
                                     Copied from Tx event FIFO element for identification of Tx message status      */

  } b; /*!< Bit fields of the 64-bit tx event fifo header                                                           */
} hal_fdcan_tx_evt_fifo_header_t;

/**
  * @brief  HAL FDCAN Global filter parameters
  */
typedef struct
{
  hal_fdcan_acceptance_non_matching_frame_t acceptance_non_matching_std; /*!< Acceptance of standard non-matching frames */
  hal_fdcan_acceptance_non_matching_frame_t acceptance_non_matching_ext; /*!< Acceptance of extended non-matching frames */
  hal_fdcan_acceptance_remote_frame_t       acceptance_remote_std;       /*!< Acceptance of standard remote frames       */
  hal_fdcan_acceptance_remote_frame_t       acceptance_remote_ext;       /*!< Acceptance of extended remote frames       */
} hal_fdcan_global_filter_config_t;

/**
  * @brief  HAL FDCAN Timestamp parameters
  */
typedef struct
{
  hal_fdcan_timestamp_source_t    timestamp_source;    /*!< Timestamp source                         */
  hal_fdcan_timestamp_prescaler_t timestamp_prescaler; /*!< Value of the timestamp prescaler counter */
}  hal_fdcan_timestamp_config_t;

/**
  * @brief  HAL FDCAN Timeout parameters
  */
typedef struct
{
  hal_fdcan_timeout_operation_t timeout_operation; /*!< Timeout select                              */
  uint32_t                      timeout_period;    /*!< Value of the timeout counter (down-counter) */
}  hal_fdcan_timeout_config_t;

/**
  * @brief  HAL FDCAN Tx Delay Compensation parameters
  */
typedef struct
{
  uint32_t tx_delay_comp_offset;     /*!< Transmitter delay compensation offset between 0 and 0x7F               */
  uint32_t tx_delay_comp_win_length; /*!< Transmitter delay compensation filter window length between 0 and 0x7F */
} hal_fdcan_tx_delay_compensation_config_t;

/**
  * @brief  HAL FDCAN filter structure definition
  */
typedef struct
{
  uint32_t                  id_type;       /*!< Specifies the identifier type                                         */
  uint32_t                  filter_index;  /*!< Specifies the filter index. The range of this parameter depends
                                                on the configured @ref hal_fdcan_filter_t::id_type .
                                                - if @ref HAL_FDCAN_ID_STANDARD : value between 0 and
                                                  (SRAMCAN_FLS_NBR - 1)
                                                - if @ref HAL_FDCAN_ID_EXTENDED : value between 0 and
                                                  (SRAMCAN_FLE_NBR - 1) */
  hal_fdcan_filter_type_t   filter_type;   /*!< Specifies the filter type. The value HAL_FDCAN_FILTER_RANGE_NO_EIDM
                                                is permitted only when id_type is extended filter                     */
  hal_fdcan_filter_config_t filter_config; /*!< Specifies the filter configuration                                    */
  uint32_t                  filter_id1;    /*!< Specifies the filter first identifier. The range of this parameter
                                                depends on the configured @ref hal_fdcan_filter_t::id_type .
                                                - if @ref HAL_FDCAN_ID_STANDARD : value between 0 and 0x7FF,
                                                - if @ref HAL_FDCAN_ID_EXTENDED : value between 0 and 0x1FFFFFFF      */
  uint32_t                  filter_id2;    /*!< Specifies the filter second identifier. The range of this parameter
                                                depends on the configured @ref hal_fdcan_filter_t::id_type .
                                                - if @ref HAL_FDCAN_ID_STANDARD : value between 0 and 0x7FF,
                                                - if @ref HAL_FDCAN_ID_EXTENDED : value between 0 and 0x1FFFFFFF      */
} hal_fdcan_filter_t;

/**
  * @brief  HAL FDCAN High Priority Message Status structure definition
  */
typedef struct
{
  hal_fdcan_high_prio_filter_list_t filter_list;   /*!< Filter list of the matching filter elements                   */
  uint32_t                          filter_index;  /*!< Index of matching filter element. The range of this
                                                        parameter depends on the configured filter list:
                                                        @ref hal_fdcan_high_prio_msg_status_t::filter_list .
                                                        - if @ref HAL_FDCAN_HIGH_PRIO_FILTER_STANDARD :
                                                          value between 0 and (SRAMCAN_FLS_NBR - 1)
                                                        - if @ref HAL_FDCAN_HIGH_PRIO_FILTER_EXTENDED :
                                                          value between 0 and (SRAMCAN_FLE_NBR - 1)                   */
  hal_fdcan_high_prio_storage_t     message_location_status; /*!< High Priority Message Storage                       */
  uint32_t                          message_index; /*!< Index of Rx FIFO element to which the message was stored.
                                                        This parameter is valid only when
                                                        @ref hal_fdcan_high_prio_msg_status_t::message_location_status
                                                        is:
                                                        - @ref HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO0
                                                        - @ref HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO1                    */
} hal_fdcan_high_prio_msg_status_t;

/**
  * @brief  FDCAN Protocol Status structure definition
  */
typedef struct
{
  hal_fdcan_protocol_error_code_t      last_error_code;      /*!< Type of the last error that occurred
                                                                  on the FDCAN bus                                    */
  hal_fdcan_protocol_error_code_t      data_last_error_code; /*!< Type of the last error that occurred in the data
                                                                  phase of a CAN FD format frame with its Bit Rate
                                                                  Switching flag set                                  */
  hal_fdcan_communication_state_t      activity;             /*!< Communication state                                 */
  hal_fdcan_protocol_error_status_t    error_status;         /*!< Error status                                        */
  hal_fdcan_warning_status_t           error_warning;        /*!< Warning status                                      */
  hal_fdcan_bus_off_status_t           bus_off;              /*!< Bus_Off status                                      */
  hal_fdcan_esi_flag_status_t          rx_esi_flag;          /*!< Error State Indicator flag of last received
                                                                  CAN FD message                                      */
  hal_fdcan_brs_flag_status_t          rx_brs_flag;          /*!< Switching flag of last received CAN FD message      */
  hal_fdcan_edl_flag_status_t          rx_fdf_flag;          /*!< Specifies if CAN FD message (FDF flag set) has been
                                                                  received since last protocol status                 */
  hal_fdcan_protocol_exception_event_t protocol_exception;   /*!< Protocol Exception status                           */
  uint32_t                             tdc_value;            /*!< Transmitter Delay Compensation Value.
                                                                  This parameter can be a number between 0 and 127    */
} hal_fdcan_protocol_status_t;

/**
  * @brief  FDCAN Error Counters structure definition
  */
typedef struct
{
  uint32_t                           tx_error_cnt;            /*!< Specifies the Transmit Error Counter Value.
                                                                   This parameter can be a number between 0 and 255 */
  uint32_t                           rx_error_cnt;            /*!< Specifies the Receive Error Counter Value.
                                                                   This parameter can be a number between 0 and 127 */
  hal_fdcan_rx_error_passive_level_t rx_error_passive_status; /*!< Specifies the Receive Error Passive status       */
  uint32_t                           global_cnt;              /*!< Specifies the Transmit/Receive error logging
                                                                   counter value. This parameter can be a number
                                                                   between 0 and 255. This counter is incremented
                                                                   each time when a FDCAN protocol error causes the
                                                                   TxErrorCnt or the RxErrorCnt to be incremented.
                                                                   The counter stops at 255; the next increment of
                                                                   TxErrorCnt or RxErrorCnt sets the interrupt
                                                                   flag HAL_FDCAN_FLAG_ERROR_LOGGING_OVERFLOW       */
} hal_fdcan_error_counters_t;

/**
  * @brief  HAL FDCAN Message RAM blocks
  */
typedef struct
{
  uint32_t std_filter_start_addr;  /*!< Specifies the standard filter list start address */
  uint32_t ext_filter_start_addr;  /*!< Specifies the extended filter list start address */
  uint32_t rx_fifo0_start_addr;    /*!< Specifies the Rx FIFO 0 start address            */
  uint32_t rx_fifo1_start_addr;    /*!< Specifies the Rx FIFO 1 start address            */
  uint32_t tx_event_start_addr;    /*!< Specifies the Tx event FIFO start address        */
  uint32_t tx_fifo_start_addr;     /*!< Specifies the Tx FIFO/Queue start address        */
} hal_fdcan_msg_ram_address_t;

/**
  * @brief  FDCAN Nominal Bit Timing structure definition
  */
typedef struct
{
  uint32_t nominal_prescaler;  /*!< Specifies the value by which the oscillator frequency is divided for generating
                                    the nominal bit time quanta. This parameter must be a number between 1 and 512  */
  uint32_t nominal_jump_width; /*!< Specifies the maximum number of time quanta the FDCAN hardware is allowed to
                                    lengthen or shorten a bit to perform resynchronization.
                                    This parameter must be a number between 1 and 128                               */
  uint32_t nominal_time_seg1;  /*!< Specifies the number of time quanta in Bit Segment 1.
                                    This parameter must be a number between 2 and 256                               */
  uint32_t nominal_time_seg2;  /*!< Specifies the number of time quanta in Bit Segment 2.
                                    This parameter must be a number between 2 and 128                               */
} hal_fdcan_nominal_bit_timing_t;

/**
  * @brief  FDCAN Data Bit Timing structure definition
  */
typedef struct
{
  uint32_t data_prescaler;  /*!< Specifies the value by which the oscillator frequency is divided for generating
                                 the Data bit time quanta. This parameter must be a number between 1 and 32      */
  uint32_t data_jump_width; /*!< Specifies the maximum number of time quanta the FDCAN hardware is allowed to
                                 lengthen or shorten a Data bit to perform resynchronization.
                                 This parameter must be a number between 1 and 16                                */
  uint32_t data_time_seg1;  /*!< Specifies the number of time quanta in Data Bit Segment 1.
                                 This parameter must be a number between 1 and 32                                */
  uint32_t data_time_seg2;  /*!< Specifies the number of time quanta in Data Bit Segment 2.
                                 This parameter must be a number between 1 and 16                                */
} hal_fdcan_data_bit_timing_t;

/**
  * @brief  HAL FDCAN Global Configuration Structure definition
  * After reset, the configuration for CCCR register is as follow:
  *           - NISO = 0: CAN FD frame according to ISO11898-1
  *           - TXP  = 0: FDCAN pauses for 2 CAN bits before next transmission is disabled
  *           - EFBI = 0: Edge Filtering during bus integration is disabled
  *           - PXHD = 0: Protocol Exception handling is enabled
  *           - BRSE = 0: FDCAN bit rate switch is disabled
  *           - FDOE = 0: FD operation is disabled
  *           - TEST = 0: Test Mode is normal mode
  *           - DAR  = 0: Disable Automatic Retransmission is enabled
  *           - MON  = 0: Bus Monitoring mode is disabled
  *           - CSR  = 0: Clock Stop Request: No clock stop request
  *           - CSA  = 0: Clock Stop Acknowledge - No clock stop acknowledged
  *           - ASM  = 0: ASM restricted operation mode - Normal CAN operation
  *           - CCE  = 0: Configuration Change Enable - No write access to the protected registers
  *           - INIT = 1: Initialization started
  */
typedef struct
{
  hal_fdcan_clock_divider_t              clock_divider;       /*!< FDCAN kernel clock divider.
                                                                   The clock is common to all FDCAN instances.
                                                                   This parameter is applied only at initialization of
                                                                   first FDCAN instance                               */
  hal_fdcan_nominal_bit_timing_t         nominal_bit_timing;  /*!< Nominal bit timing                                 */
  hal_fdcan_data_bit_timing_t            data_bit_timing;     /*!< Data Bit Timing                                    */
  hal_fdcan_mode_t                       mode;                /*!< FDCAN mode                                         */
  hal_fdcan_frame_format_t               frame_format;        /*!< FDCAN frame format                                 */
  hal_fdcan_auto_retransmission_status_t auto_retransmission; /*!< FDCAN automatic retransmission mode                */
  hal_fdcan_transmit_pause_status_t      transmit_pause;      /*!< FDCAN Transmit Pause feature                       */
  hal_fdcan_protocol_exception_status_t  protocol_exception;  /*!< FDCAN Protocol Exception Handling                  */
  uint32_t                               std_filters_nbr;     /*!< Number of standard Message ID filters.
                                                                   This parameter must be a number between 0 and 28   */
  uint32_t                               ext_filters_nbr;     /*!< Number of extended Message ID filters.
                                                                   This parameter must be a number between 0 and 8    */
  hal_fdcan_tx_mode_t                    tx_fifo_queue_mode;  /*!< Tx FIFO/Queue mode selection                       */
} hal_fdcan_config_t;

typedef struct hal_fdcan_handle_s hal_fdcan_handle_t; /*!< FDCAN handle Structure type */

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
/**
  * @brief  HAL FDCAN Callback pointer definition
  */

typedef  void (*hal_fdcan_fifo_cb_t)(hal_fdcan_handle_t *hfdcan, uint32_t it_list);             /*!< Pointer to interrupts list FDCAN callback function             */
typedef  void (*hal_fdcan_tx_buffer_cb_t)(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes); /*!< Pointer to IT Tx Buffer Complete/Abort FDCAN callback function */
typedef  void (*hal_fdcan_cb_t)(hal_fdcan_handle_t *hfdcan);                                    /*!< Pointer to a generic FDCAN callback function                   */

#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
/**
  * @brief  HAL FDCAN handle structure definition
  */
struct hal_fdcan_handle_s
{
  hal_fdcan_t                  instance;                 /*!< FDCAN Instance                                  */

  hal_fdcan_msg_ram_address_t  msg_ram;                  /*!< Message RAM blocks                              */
  volatile hal_fdcan_state_t   global_state;             /*!< Communication current state                     */
  hal_fdcan_state_t            previous_state;           /*!< Communication previous state                    */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  volatile uint32_t            last_error_codes;         /*!< Last error codes                                */
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

  uint32_t                     latest_tx_fifo_q_request; /*!< Tx buffer index of latest Tx FIFO/Queue request */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  hal_os_semaphore_t           semaphore;                /*!< FDCAN OS semaphore                              */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1)
  const void                  *p_user_data;              /*!< User Data Pointer                               */
#endif /* USE_HAL_FDCAN_USER_DATA */

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
  hal_fdcan_fifo_cb_t          p_tx_eventfifo_cb;        /*!< Tx Event FIFO callback                          */
  hal_fdcan_fifo_cb_t          p_rx_fifo0_cb;            /*!< Rx FIFO 0 callback                              */
  hal_fdcan_fifo_cb_t          p_rx_fifo1_cb;            /*!< Rx FIFO 1 callback                              */
  hal_fdcan_cb_t               p_tx_fifoempty_cb;        /*!< Tx FIFO Empty callback                          */
  hal_fdcan_tx_buffer_cb_t     p_tx_buffercomplete_cb;   /*!< Tx Buffer complete callback                     */
  hal_fdcan_tx_buffer_cb_t     p_tx_bufferabort_cb;      /*!< Tx Buffer abort callback                        */
  hal_fdcan_cb_t               p_highpriority_msg_cb;    /*!< High priority message callback                  */
  hal_fdcan_cb_t               p_ts_wraparound_cb;       /*!< Timestamp wraparound callback                   */
  hal_fdcan_cb_t               p_error_cb;               /*!< Error callback                                  */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Functions FDCAN Exported Functions
  * @{
  */

/** @defgroup FDCAN_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

hal_status_t HAL_FDCAN_Init(hal_fdcan_handle_t *hfdcan, hal_fdcan_t instance);
void HAL_FDCAN_DeInit(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group2 Enter and Exit Power Down mode
  * @{
  */

/* Power Down Mode */
hal_status_t HAL_FDCAN_EnterPowerDownMode(hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ExitPowerDownMode(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group3 Configuration functions
  * @{
  */

/* Global configuration */
hal_status_t HAL_FDCAN_SetConfig(hal_fdcan_handle_t *hfdcan, const hal_fdcan_config_t *p_config);
void HAL_FDCAN_GetConfig(const hal_fdcan_handle_t *hfdcan, hal_fdcan_config_t *p_config);

/* Nominal Bit Timing */
hal_status_t HAL_FDCAN_SetNominalBitTiming(const hal_fdcan_handle_t *hfdcan,
                                           const hal_fdcan_nominal_bit_timing_t *p_nominal_bit_timing);
void HAL_FDCAN_GetNominalBitTiming(const hal_fdcan_handle_t *hfdcan,
                                   hal_fdcan_nominal_bit_timing_t *nominal_bit_timing);

/* Data Bit Timing */
hal_status_t HAL_FDCAN_SetDataBitTiming(const hal_fdcan_handle_t *hfdcan,
                                        const hal_fdcan_data_bit_timing_t *p_data_bit_timing);
void HAL_FDCAN_GetDataBitTiming(const hal_fdcan_handle_t *hfdcan, hal_fdcan_data_bit_timing_t *data_bit_timing);

/* Filter - To set/get the acceptance filters parameters for standard and extended filters */
hal_status_t HAL_FDCAN_SetFilter(const hal_fdcan_handle_t *hfdcan, const hal_fdcan_filter_t *p_filter_config);
void HAL_FDCAN_GetFilter(const hal_fdcan_handle_t *hfdcan, hal_fdcan_filter_t *p_filter_config,
                         uint32_t filter_index, uint32_t id_type);

/* Global filter configuration */
hal_status_t HAL_FDCAN_SetGlobalFilter(const hal_fdcan_handle_t *hfdcan,
                                       const hal_fdcan_global_filter_config_t *p_global_filter_config);
void HAL_FDCAN_GetGlobalFilter(const hal_fdcan_handle_t *hfdcan,
                               hal_fdcan_global_filter_config_t *p_global_filter_config);

/* Extended ID mask for acceptance filtering */
hal_status_t HAL_FDCAN_SetExtendedIdMask(const hal_fdcan_handle_t *hfdcan, uint32_t mask);
uint32_t     HAL_FDCAN_GetExtendedIdMask(const hal_fdcan_handle_t *hfdcan);

/* Clock divider */
hal_status_t HAL_FDCAN_SetClockDivider(const hal_fdcan_handle_t *hfdcan, hal_fdcan_clock_divider_t clock_divider);
hal_fdcan_clock_divider_t HAL_FDCAN_GetClockDivider(const hal_fdcan_handle_t *hfdcan);

/* Rx FIFO Overwrite */
hal_status_t HAL_FDCAN_SetRxFifoOverwrite(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_idx,
                                          hal_fdcan_rx_fifo_operative_mode_t operation_mode);
void         HAL_FDCAN_GetRxFifoOverwrite(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_sel,
                                          hal_fdcan_rx_fifo_operative_mode_t *p_rx_operation);

/* RAM Watchdog */
hal_status_t HAL_FDCAN_SetRamWatchdog(const hal_fdcan_handle_t *hfdcan, uint32_t counter_start_value);
uint32_t     HAL_FDCAN_GetRamWatchdog(const hal_fdcan_handle_t *hfdcan);

/* TimeStamp counter */
hal_status_t HAL_FDCAN_SetConfigTimestampCounter(const hal_fdcan_handle_t *hfdcan,
                                                 const hal_fdcan_timestamp_config_t *p_timestamp_config);
void         HAL_FDCAN_GetConfigTimestampCounter(const hal_fdcan_handle_t *hfdcan,
                                                 hal_fdcan_timestamp_config_t *p_timestamp_config);
uint16_t     HAL_FDCAN_GetTimestampCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ResetTimestampCounter(const hal_fdcan_handle_t *hfdcan);

/* Timeout counter */
hal_status_t HAL_FDCAN_SetConfigTimeoutCounter(const hal_fdcan_handle_t *hfdcan,
                                               const hal_fdcan_timeout_config_t *p_timeout_param);
void         HAL_FDCAN_GetConfigTimeoutCounter(const hal_fdcan_handle_t *hfdcan,
                                               hal_fdcan_timeout_config_t *p_timeout_param);
uint32_t HAL_FDCAN_GetTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ResetTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_EnableTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_DisableTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_timeout_counter_status_t HAL_FDCAN_IsEnabledTimeoutCounter(const hal_fdcan_handle_t *hfdcan);

/* Delay compensation mechanism to compensate the CAN transmitter loop delay */
hal_status_t HAL_FDCAN_SetConfigTxDelayCompensation(const hal_fdcan_handle_t *hfdcan,
                                                    const hal_fdcan_tx_delay_compensation_config_t *p_tx_delay_param);
void HAL_FDCAN_GetConfigTxDelayCompensation(const hal_fdcan_handle_t *hfdcan,
                                            hal_fdcan_tx_delay_compensation_config_t *p_tx_delay_param);
hal_status_t HAL_FDCAN_DisableTxDelayCompensation(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_EnableTxDelayCompensation(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_transmitter_delay_comp_status_t HAL_FDCAN_IsEnabledTxDelayCompensation(const hal_fdcan_handle_t *hfdcan);

/* ISO Mode - ISO11898-1 or CAN FD Specification V1.0 */
hal_status_t HAL_FDCAN_DisableISOMode(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_EnableISOMode(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_iso_mode_status_t HAL_FDCAN_IsEnabledISOMode(const hal_fdcan_handle_t *hfdcan);

/* Edge filtering */
hal_status_t HAL_FDCAN_DisableEdgeFiltering(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_EnableEdgeFiltering(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_edge_filtering_status_t HAL_FDCAN_IsEnabledEdgeFiltering(const hal_fdcan_handle_t *hfdcan);

/* Operating mode */
hal_status_t HAL_FDCAN_SetMode(const hal_fdcan_handle_t *hfdcan, hal_fdcan_mode_t mode);
hal_fdcan_mode_t HAL_FDCAN_GetMode(const hal_fdcan_handle_t *hfdcan);

/* Frame format */
hal_status_t HAL_FDCAN_SetFrameFormat(const hal_fdcan_handle_t *hfdcan, hal_fdcan_frame_format_t frame_format);
hal_fdcan_frame_format_t HAL_FDCAN_GetFrameFormat(const hal_fdcan_handle_t *hfdcan);

/* Auto retransmission of unsuccessful messages */
hal_status_t HAL_FDCAN_SetAutoRetransmission(const hal_fdcan_handle_t *hfdcan,
                                             hal_fdcan_auto_retransmission_status_t auto_retransmit);
hal_fdcan_auto_retransmission_status_t HAL_FDCAN_GetAutoRetransmission(const hal_fdcan_handle_t *hfdcan);

/* Transmit pause */
hal_status_t HAL_FDCAN_SetTransmitPause(const hal_fdcan_handle_t *hfdcan,
                                        hal_fdcan_transmit_pause_status_t transmit_pause);
hal_fdcan_transmit_pause_status_t HAL_FDCAN_GetTransmitPause(const hal_fdcan_handle_t *hfdcan);

/* Protocol exception */
hal_status_t HAL_FDCAN_SetProtocolException(const hal_fdcan_handle_t *hfdcan,
                                            hal_fdcan_protocol_exception_status_t protocol_exception);
hal_fdcan_protocol_exception_status_t HAL_FDCAN_GetProtocolException(const hal_fdcan_handle_t *hfdcan);

/* Tx mode */
hal_status_t HAL_FDCAN_SetTxMode(const hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_mode_t tx_mode);
hal_fdcan_tx_mode_t HAL_FDCAN_GetTxMode(const hal_fdcan_handle_t *hfdcan);

/* FDCAN current clock frequency */
uint32_t HAL_FDCAN_GetClockFreq(const hal_fdcan_handle_t *hfdcan);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
/* Callbacks registering */
hal_status_t HAL_FDCAN_RegisterTxEventFifoCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterRxFifo0Callback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterRxFifo1Callback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTxBufferCompleteCallback(hal_fdcan_handle_t *hfdcan,
                                                        hal_fdcan_tx_buffer_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTxBufferAbortCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_buffer_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterHighPriorityMessageCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTxFifoEmptyCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTimestampWraparoundCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterErrorCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group4 Control Functions
  * @{
  */

/* Start / Stop the FDCAN module */
hal_status_t HAL_FDCAN_Start(hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_Stop(hal_fdcan_handle_t *hfdcan);

/* Functions involved in Transmission process */
hal_status_t HAL_FDCAN_ReqTransmitMsgFromFIFOQ(hal_fdcan_handle_t *hfdcan,
                                               const hal_fdcan_tx_header_t *p_tx_element_header,
                                               const uint8_t *p_tx_data);
hal_fdcan_fifo_status_t HAL_FDCAN_GetTxFifoStatus(const hal_fdcan_handle_t *hfdcan);
uint32_t HAL_FDCAN_GetLatestTxFifoQRequestBuffer(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_tx_fifo_free_level_t HAL_FDCAN_GetTxFifoFreeLevel(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ReqAbortOfTxBuffer(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_index);
hal_status_t HAL_FDCAN_GetTxEvent(const hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_evt_fifo_header_t *p_tx_event);
hal_fdcan_buffer_status_t HAL_FDCAN_GetTxBufferMessageStatus(const hal_fdcan_handle_t *hfdcan,
                                                             uint32_t tx_buffer_index);

/* Functions involved in Receiving process */
hal_status_t HAL_FDCAN_GetReceivedMessage(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_location,
                                          hal_fdcan_rx_header_t *p_rx_header, uint8_t *p_rx_data);
void HAL_FDCAN_GetRxFifoFillLevel(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_sel,
                                  uint32_t *p_fill_level);

/* Functions involved in general Tx/Rx process */
hal_status_t HAL_FDCAN_GetHighPriorityMessageStatus(const hal_fdcan_handle_t *hfdcan,
                                                    hal_fdcan_high_prio_msg_status_t *p_hp_msg_status);
hal_status_t HAL_FDCAN_GetProtocolStatus(const hal_fdcan_handle_t *hfdcan,
                                         hal_fdcan_protocol_status_t *p_protocol_status);
hal_status_t HAL_FDCAN_GetErrorCounters(const hal_fdcan_handle_t *hfdcan, hal_fdcan_error_counters_t *p_error_counters);

/* Restricted operation mode */
hal_status_t HAL_FDCAN_DisableRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_EnableRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_restricted_op_mode_status_t HAL_FDCAN_IsEnabledRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group5 Interrupts Management Functions
  * @{
  */

void HAL_FDCAN_IRQHandler(hal_fdcan_handle_t *hfdcan);

hal_status_t HAL_FDCAN_SetInterruptGroupsToLine(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt_groups,
                                                uint32_t it_line);
uint32_t HAL_FDCAN_GetLineFromInterruptGroup(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt_group);

hal_status_t HAL_FDCAN_EnableInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t interrupts);
hal_status_t HAL_FDCAN_DisableInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t interrupts);
hal_fdcan_it_status_t HAL_FDCAN_IsEnabledInterrupt(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt);

hal_status_t HAL_FDCAN_EnableInterruptLines(const hal_fdcan_handle_t *hfdcan, uint32_t it_lines);
hal_status_t HAL_FDCAN_DisableInterruptLines(const hal_fdcan_handle_t *hfdcan, uint32_t it_lines);
hal_fdcan_it_lines_status_t HAL_FDCAN_IsEnabledInterruptLine(const hal_fdcan_handle_t *hfdcan, uint32_t it_line);

hal_status_t HAL_FDCAN_EnableTxBufferCompleteInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_status_t HAL_FDCAN_DisableTxBufferCompleteInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_fdcan_it_txbuffer_complete_status_t HAL_FDCAN_IsEnabledTxBufferCompleteInterrupt(const hal_fdcan_handle_t *hfdcan,
    uint32_t buffer_idx);

hal_status_t HAL_FDCAN_EnableTxBufferCancellationInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_status_t HAL_FDCAN_DisableTxBufferCancellationInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_fdcan_it_txbuffer_abort_status_t HAL_FDCAN_IsEnabledTxBufferCancellationInterrupt(const hal_fdcan_handle_t *hfdcan,
    uint32_t buffer_idx);

/**
  * @brief  Check whether the specified FDCAN flag is set or not.
  * @param  hfdcan Pointer to a @ref hal_fdcan_handle_t.
  * @param  flag FDCAN flag.
  *         This parameter can be one of @arg FDCAN_Interrupt_Sources
  * @retval uint32_t FlagStatus
  */
__STATIC_INLINE uint32_t HAL_FDCAN_GetFlag(const hal_fdcan_handle_t *hfdcan, uint32_t flag)
{
  const FDCAN_GlobalTypeDef *p_fdcanx;

  /* Get the FDCANx CMSIS handle */
  p_fdcanx = (FDCAN_GlobalTypeDef *)((uint32_t)hfdcan->instance);

  return READ_BIT(p_fdcanx->IR, (flag));
}

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group6 Weak Callback Functions
  * @{
  */

void HAL_FDCAN_TxEventFifoCallback(hal_fdcan_handle_t *hfdcan, uint32_t tx_event_fifo_its);
void HAL_FDCAN_RxFifo0Callback(hal_fdcan_handle_t *hfdcan, uint32_t rx_fifo0_its);
void HAL_FDCAN_RxFifo1Callback(hal_fdcan_handle_t *hfdcan, uint32_t rx_fifo1_its);
void HAL_FDCAN_TxFifoEmptyCallback(hal_fdcan_handle_t *hfdcan);
void HAL_FDCAN_TxBufferCompleteCallback(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes);
void HAL_FDCAN_TxBufferAbortCallback(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes);
void HAL_FDCAN_HighPriorityMessageCallback(hal_fdcan_handle_t *hfdcan);
void HAL_FDCAN_TimestampWraparoundCallback(hal_fdcan_handle_t *hfdcan);
void HAL_FDCAN_ErrorCallback(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group7 Error and State functions
  * @{
  */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
uint32_t HAL_FDCAN_GetLastErrorCodes(const hal_fdcan_handle_t *hfdcan);
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

hal_fdcan_state_t HAL_FDCAN_GetState(const hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup FDCAN_Exported_Functions_Group8 Peripheral Acquire/Release/Free the bus
  * @{
  */

hal_status_t HAL_FDCAN_AcquireBus(hal_fdcan_handle_t *hfdcan, uint32_t timeout_ms);
hal_status_t HAL_FDCAN_ReleaseBus(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1)
/** @defgroup FDCAN_Exported_Functions_Group9 User data Set/Get
  * @{
  */

void HAL_FDCAN_SetUserData(hal_fdcan_handle_t *hfdcan, const void *p_user_data);
const void *HAL_FDCAN_GetUserData(const hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */
#endif /* USE_HAL_FDCAN_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* FDCAN1 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5xx_HAL_FDCAN_H */
