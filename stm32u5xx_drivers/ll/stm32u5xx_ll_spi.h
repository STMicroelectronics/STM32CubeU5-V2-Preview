/**
  ******************************************************************************
  * @file    stm32u5xx_ll_spi.h
  * @brief   Header file of SPI LL module.
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
#ifndef STM32U5XX_LL_SPI_H
#define STM32U5XX_LL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(SPI1) || defined(SPI2) || defined(SPI3)

/** @defgroup SPI_LL SPI
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup SPI_LL_Private_Macros SPI Private Macros
  * @{
  */
#if defined(IS_SPI_GRP2_INSTANCE)
#define IS_LL_SPI_GRP1_INSTANCE(__INSTANCE__)    IS_SPI_GRP1_INSTANCE(__INSTANCE__)
#define IS_LL_SPI_GRP2_INSTANCE(__INSTANCE__)    IS_SPI_GRP2_INSTANCE(__INSTANCE__)
#else
#define IS_LL_SPI_GRP1_INSTANCE(__INSTANCE__)    IS_SPI_GRP1_INSTANCE(__INSTANCE__)
#endif /* SPI_TRIG_GRP2 */
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Constants SPI Exported Constants
  * @{
  */

/** @defgroup SPI_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_SPI_ReadReg function
  * @{
  */
#define LL_SPI_FLAG_RXP                            (SPI_SR_RXP)
#define LL_SPI_FLAG_TXP                            (SPI_SR_TXP)
#define LL_SPI_FLAG_DXP                            (SPI_SR_DXP)
#define LL_SPI_FLAG_EOT                            (SPI_SR_EOT)
#define LL_SPI_FLAG_TXTF                           (SPI_SR_TXTF)
#define LL_SPI_FLAG_UDR                            (SPI_SR_UDR)
#define LL_SPI_FLAG_CRCE                           (SPI_SR_CRCE)
#define LL_SPI_FLAG_MODF                           (SPI_SR_MODF)
#define LL_SPI_FLAG_OVR                            (SPI_SR_OVR)
#define LL_SPI_FLAG_TIFRE                          (SPI_SR_TIFRE)
#define LL_SPI_FLAG_SUSP                           (SPI_SR_SUSP)
#define LL_SPI_FLAG_TXC                            (SPI_SR_TXC)
#define LL_SPI_FLAG_RXWNE                          (SPI_SR_RXWNE)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_SPI_ReadReg and  LL_SPI_WriteReg functions
  * @{
  */
#define LL_SPI_IT_RXP                              (SPI_IER_RXPIE)
#define LL_SPI_IT_TXP                              (SPI_IER_TXPIE)
#define LL_SPI_IT_DXP                              (SPI_IER_DXPIE)
#define LL_SPI_IT_EOT                              (SPI_IER_EOTIE)
#define LL_SPI_IT_TXTF                             (SPI_IER_TXTFIE)
#define LL_SPI_IT_UDR                              (SPI_IER_UDRIE)
#define LL_SPI_IT_OVR                              (SPI_IER_OVRIE)
#define LL_SPI_IT_CRCE                             (SPI_IER_CRCEIE)
#define LL_SPI_IT_TIFRE                            (SPI_IER_TIFREIE)
#define LL_SPI_IT_MODF                             (SPI_IER_MODFIE)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_MODE Mode
  * @{
  */
#define LL_SPI_MODE_MASTER                         (SPI_CFG2_MASTER)
#define LL_SPI_MODE_SLAVE                          (0x00000000UL)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_SS_LEVEL SS Level
  * @{
  */
#define LL_SPI_SS_LEVEL_HIGH                       (SPI_CR1_SSI)
#define LL_SPI_SS_LEVEL_LOW                        (0x00000000UL)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSS_MSSI Master Slave Select Idleness
  * @{
  */
#define LL_SPI_MSSI_DELAY_0_CYCLE                  (0x00000000UL)                                         /*!< No extra delay                     */
#define LL_SPI_MSSI_DELAY_1_CYCLE                  (SPI_CFG2_MSSI_0)                                      /*!< 1 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_2_CYCLE                  (SPI_CFG2_MSSI_1)                                      /*!< 2 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_3_CYCLE                  (SPI_CFG2_MSSI_0 | SPI_CFG2_MSSI_1)                    /*!< 3 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_4_CYCLE                  (SPI_CFG2_MSSI_2)                                      /*!< 4 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_5_CYCLE                  (SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_0)                    /*!< 5 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_6_CYCLE                  (SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1)                    /*!< 6 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_7_CYCLE                  (SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1 | SPI_CFG2_MSSI_0)  /*!< 7 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_8_CYCLE                  (SPI_CFG2_MSSI_3)                                      /*!< 8 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_9_CYCLE                  (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_0)                    /*!< 9 clock cycle period delay added   */
#define LL_SPI_MSSI_DELAY_10_CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_1)                    /*!< 10 clock cycle period delay added  */
#define LL_SPI_MSSI_DELAY_11_CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_1 | SPI_CFG2_MSSI_0)  /*!< 11 clock cycle period delay added  */
#define LL_SPI_MSSI_DELAY_12_CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_2)                    /*!< 12 clock cycle period delay added  */
#define LL_SPI_MSSI_DELAY_13_CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_0)  /*!< 13 clock cycle period delay added  */
#define LL_SPI_MSSI_DELAY_14_CYCLE                 (SPI_CFG2_MSSI_3 | SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1)  /*!< 14 clock cycle period delay added  */
#define LL_SPI_MSSI_DELAY_15_CYCLE                 (SPI_CFG2_MSSI_3\
                                                    | SPI_CFG2_MSSI_2 | SPI_CFG2_MSSI_1 | SPI_CFG2_MSSI_0) /*!< 15 clock cycle period delay added  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_ID_IDLENESS Master Inter-Data Idleness
  * @{
  */
#define LL_SPI_MIDI_DELAY_0_CYCLE                  (0x00000000UL)                                          /*!< No delay                      */
#define LL_SPI_MIDI_DELAY_1_CYCLE                  (SPI_CFG2_MIDI_0)                                       /*!< 1 clock cycle period delay    */
#define LL_SPI_MIDI_DELAY_2_CYCLE                  (SPI_CFG2_MIDI_1)                                       /*!< 2 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_3_CYCLE                  (SPI_CFG2_MIDI_0 | SPI_CFG2_MIDI_1)                     /*!< 3 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_4_CYCLE                  (SPI_CFG2_MIDI_2)                                       /*!< 4 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_5_CYCLE                  (SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_0)                     /*!< 5 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_6_CYCLE                  (SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1)                     /*!< 6 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_7_CYCLE                  (SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1 | SPI_CFG2_MIDI_0)   /*!< 7 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_8_CYCLE                  (SPI_CFG2_MIDI_3)                                       /*!< 8 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_9_CYCLE                  (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_0)                     /*!< 9 clock cycles period delay   */
#define LL_SPI_MIDI_DELAY_10_CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_1)                     /*!< 10 clock cycles period delay  */
#define LL_SPI_MIDI_DELAY_11_CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_1 | SPI_CFG2_MIDI_0)   /*!< 11 clock cycles period delay  */
#define LL_SPI_MIDI_DELAY_12_CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_2)                     /*!< 12 clock cycles period delay  */
#define LL_SPI_MIDI_DELAY_13_CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_0)   /*!< 13 clock cycles period delay  */
#define LL_SPI_MIDI_DELAY_14_CYCLE                 (SPI_CFG2_MIDI_3 | SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1)   /*!< 14 clock cycles period delay  */
#define LL_SPI_MIDI_DELAY_15_CYCLE                 (SPI_CFG2_MIDI_3\
                                                    | SPI_CFG2_MIDI_2 | SPI_CFG2_MIDI_1 | SPI_CFG2_MIDI_0) /*!< 15 clock cycles period delay  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TXCRCINIT_ALL TXCRC Init All
  * @{
  */
#define LL_SPI_CRC_TX_INIT_PATTERN_ALL_ZERO        (0x00000000UL)    /*!< CRC TX Initialization patterns configured to zero  */
#define LL_SPI_CRC_TX_INIT_PATTERN_ALL_ONE         (SPI_CR1_TCRCINI) /*!< CRC TX Initialization patterns configured to one   */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_RXCRCINIT_ALL RXCRC Init All
  * @{
  */
#define LL_SPI_CRC_RX_INIT_PATTERN_ALL_ZERO        (0x00000000UL)    /*!< CRC RX Initialization patterns configured to zero  */
#define LL_SPI_CRC_RX_INIT_PATTERN_ALL_ONE         (SPI_CR1_RCRCINI) /*!< CRC RX Initialization patterns configured to one   */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_UDR_CONFIG_REGISTER UDR Config Register
  * @{
  */
#define LL_SPI_UNDERRUN_CONFIG_REGISTER_PATTERN    (0x00000000UL)
#define LL_SPI_UNDERRUN_CONFIG_LAST_RECEIVED       (SPI_CFG1_UDRCFG)    /*!< Slave repeats lastly received data from master */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_PROTOCOL Protocol
  * @{
  */
#define LL_SPI_PROTOCOL_MOTOROLA                   (0x00000000UL)    /*!< MOTOROLA protocol is used (most common protocol)  */
#define LL_SPI_PROTOCOL_TI                         (SPI_CFG2_SP_0)   /*!< TI protocol is used */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_PHASE Phase
  * @{
  */
#define LL_SPI_CLOCK_PHASE_1_EDGE                   (0x00000000UL)    /*!< The first clock transition is the first data capture edge  */
#define LL_SPI_CLOCK_PHASE_2_EDGE                   (SPI_CFG2_CPHA)   /*!< The second clock transition is the first data capture edge  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_POLARITY Polarity
  * @{
  */
#define LL_SPI_CLOCK_POLARITY_LOW                  (0x00000000UL)     /*!< SCK signal is at 0 when idle */
#define LL_SPI_CLOCK_POLARITY_HIGH                 (SPI_CFG2_CPOL)    /*!< SCK signal is at 1 when idle */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSS_POLARITY NSS Polarity
  * @{
  */
#define LL_SPI_NSS_POLARITY_LOW                    (0x00000000UL)     /*!< Low level is active for slave select signal  */
#define LL_SPI_NSS_POLARITY_HIGH                   (SPI_CFG2_SSIOP)   /*!< High level is active for slave select signal */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_BAUDRATEPRESCALER Baud Rate Prescaler
  * @{
  */
#define LL_SPI_BAUD_RATE_PRESCALER_BYPASS           (SPI_CFG1_BPASS)   /*!< Bypass from RCC in Master mode   */
#define LL_SPI_BAUD_RATE_PRESCALER_2                (0x00000000UL)                                     /*!< SPI master clock/2   */
#define LL_SPI_BAUD_RATE_PRESCALER_4                (SPI_CFG1_MBR_0)                                   /*!< SPI master clock/4   */
#define LL_SPI_BAUD_RATE_PRESCALER_8                (SPI_CFG1_MBR_1)                                   /*!< SPI master clock/8   */
#define LL_SPI_BAUD_RATE_PRESCALER_16               (SPI_CFG1_MBR_1 | SPI_CFG1_MBR_0)                  /*!< SPI master clock/16  */
#define LL_SPI_BAUD_RATE_PRESCALER_32               (SPI_CFG1_MBR_2)                                   /*!< SPI master clock/32  */
#define LL_SPI_BAUD_RATE_PRESCALER_64               (SPI_CFG1_MBR_2 | SPI_CFG1_MBR_0)                  /*!< SPI master clock/64  */
#define LL_SPI_BAUD_RATE_PRESCALER_128              (SPI_CFG1_MBR_2 | SPI_CFG1_MBR_1)                  /*!< SPI master clock/128 */
#define LL_SPI_BAUD_RATE_PRESCALER_256              (SPI_CFG1_MBR_2 | SPI_CFG1_MBR_1 | SPI_CFG1_MBR_0) /*!< SPI master clock/256 */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_BIT_ORDER Bit Order
  * @{
  */
#define LL_SPI_LSB_FIRST                           (SPI_CFG2_LSBFRST)      /*!< LSB transmitted first  */
#define LL_SPI_MSB_FIRST                           (0x00000000UL)          /*!< MSB transmitted first  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TRANSFER_DIRECTION Transfer Direction
  * @brief    Direction defines
  * @note     LL_SPI_SetHalfDuplexDirection must be used to select the transfer direction in half duplex
  * @{
  */
#define LL_SPI_FULL_DUPLEX                         (0x00000000UL)                       /*!< Full-duplex communication                  */
#define LL_SPI_SIMPLEX_TX                          (SPI_CFG2_COMM_0)                    /*!< Simplex communication mode: Transmit only  */
#define LL_SPI_SIMPLEX_RX                          (SPI_CFG2_COMM_1)                    /*!< Simplex communication mode: Receive only   */
#define LL_SPI_HALF_DUPLEX                         (SPI_CFG2_COMM_0|SPI_CFG2_COMM_1)    /*!< Half-duplex communication                  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_HALF_DUPLEX_DIRECTION Half Duplex Direction
  * @{
  */
#define  LL_SPI_HALF_DUPLEX_RX                     (0x00000000UL)      /*!< Half-duplex in reception mode    */
#define  LL_SPI_HALF_DUPLEX_TX                     (SPI_CR1_HDDIR)     /*!< Half-duplex in transmission mode */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_DATAWIDTH Data Width
  * @{
  */
#define LL_SPI_DATA_WIDTH_4_BIT                     (SPI_CFG1_DSIZE_0 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_5_BIT                     (SPI_CFG1_DSIZE_2)
#define LL_SPI_DATA_WIDTH_6_BIT                     (SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_7_BIT                     (SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_8_BIT                     (SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_9_BIT                     (SPI_CFG1_DSIZE_3)
#define LL_SPI_DATA_WIDTH_10_BIT                    (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_11_BIT                    (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_12_BIT                    (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_13_BIT                    (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2)
#define LL_SPI_DATA_WIDTH_14_BIT                    (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_15_BIT                    (SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_16_BIT                    (SPI_CFG1_DSIZE_3\
                                                     | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_17_BIT                    (SPI_CFG1_DSIZE_4)
#define LL_SPI_DATA_WIDTH_18_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_19_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_20_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_0 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_21_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_2)
#define LL_SPI_DATA_WIDTH_22_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_23_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_24_BIT                    (SPI_CFG1_DSIZE_4\
                                                     | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_25_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3)
#define LL_SPI_DATA_WIDTH_26_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_27_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_28_BIT                    (SPI_CFG1_DSIZE_4\
                                                     | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_29_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2)
#define LL_SPI_DATA_WIDTH_30_BIT                    (SPI_CFG1_DSIZE_4\
                                                     | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_0)
#define LL_SPI_DATA_WIDTH_31_BIT                    (SPI_CFG1_DSIZE_4\
                                                     | SPI_CFG1_DSIZE_3 | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1)
#define LL_SPI_DATA_WIDTH_32_BIT                    (SPI_CFG1_DSIZE_4 | SPI_CFG1_DSIZE_3\
                                                     | SPI_CFG1_DSIZE_2 | SPI_CFG1_DSIZE_1 | SPI_CFG1_DSIZE_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_FIFO_TH FIFO Threshold
  * @{
  */
#define LL_SPI_FIFO_THRESHOLD_1_DATA               (0x00000000UL)
#define LL_SPI_FIFO_THRESHOLD_2_DATA               (SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_THRESHOLD_3_DATA               (SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_THRESHOLD_4_DATA               (SPI_CFG1_FTHLV_0 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_THRESHOLD_5_DATA               (SPI_CFG1_FTHLV_2)
#define LL_SPI_FIFO_THRESHOLD_6_DATA               (SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_THRESHOLD_7_DATA               (SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_THRESHOLD_8_DATA               (SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_THRESHOLD_9_DATA               (SPI_CFG1_FTHLV_3)
#define LL_SPI_FIFO_THRESHOLD_10_DATA              (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_THRESHOLD_11_DATA              (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_THRESHOLD_12_DATA              (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_1 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_THRESHOLD_13_DATA              (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_2)
#define LL_SPI_FIFO_THRESHOLD_14_DATA              (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_0)
#define LL_SPI_FIFO_THRESHOLD_15_DATA              (SPI_CFG1_FTHLV_3 | SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1)
#define LL_SPI_FIFO_THRESHOLD_16_DATA              (SPI_CFG1_FTHLV_3\
                                                    | SPI_CFG1_FTHLV_2 | SPI_CFG1_FTHLV_1 | SPI_CFG1_FTHLV_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_CRC CRC
  * @{
  */
#define LL_SPI_CRC_LENGTH_4_BIT                     (SPI_CFG1_CRCSIZE_0 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_5_BIT                     (SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_LENGTH_6_BIT                     (SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_7_BIT                     (SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_8_BIT                     (SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_9_BIT                     (SPI_CFG1_CRCSIZE_3)
#define LL_SPI_CRC_LENGTH_10_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_11_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_12_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_13_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_LENGTH_14_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_15_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_16_BIT                    (SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2  \
                                                     | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_17_BIT                    (SPI_CFG1_CRCSIZE_4)
#define LL_SPI_CRC_LENGTH_18_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_19_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_20_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_0 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_21_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_LENGTH_22_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_23_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_24_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_2  \
                                                     | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_25_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3)
#define LL_SPI_CRC_LENGTH_26_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_27_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_28_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3  \
                                                     | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_29_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3 | SPI_CFG1_CRCSIZE_2)
#define LL_SPI_CRC_LENGTH_30_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3  \
                                                     | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_0)
#define LL_SPI_CRC_LENGTH_31_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3  \
                                                     | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1)
#define LL_SPI_CRC_LENGTH_32_BIT                    (SPI_CFG1_CRCSIZE_4 | SPI_CFG1_CRCSIZE_3  \
                                                     | SPI_CFG1_CRCSIZE_2 | SPI_CFG1_CRCSIZE_1 | SPI_CFG1_CRCSIZE_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSS_MODE NSS Mode
  * @{
  */
/** In this configuration the Slave select is driven internally.
  * The external slave select pin is free for other application uses.
  */
#define LL_SPI_NSS_SOFT                            (SPI_CFG2_SSM)

/** In Slave mode, the slave select pin works as a standard chip select input and the slave
  * is selected while the slave select line is at its active level. In Master mode, this
  * configuration allows multi-master capability. If the slave select pin is pulled into
  * an active level in this mode, the SPI enters Master mode fault state and the SPI
  * device is automatically reconfigured in Slave mode (MASTER = 0)
  */
#define LL_SPI_NSS_HARD_INPUT                      (0x00000000UL)

/** This configuration is only used when the MCU is set as master (multi-master not
  * allowed). The slave select pin active level is managed by the hardware. The
  * functionality is tied to CSTART and EOT control.
  */
#define LL_SPI_NSS_HARD_OUTPUT                     (SPI_CFG2_SSOE)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_RX_FIFO RxFIFO Packing LeVel
  * @{
  */
#define LL_SPI_RX_FIFO_0PACKET               (0x00000000UL)    /* 0 or multiple of 4 packet available is the RxFIFO */
#define LL_SPI_RX_FIFO_1PACKET               (SPI_SR_RXPLVL_0)
#define LL_SPI_RX_FIFO_2PACKET               (SPI_SR_RXPLVL_1)
#define LL_SPI_RX_FIFO_3PACKET               (SPI_SR_RXPLVL_1 | SPI_SR_RXPLVL_0)
/**
  * @}
  */

/** @defgroup SPI_LL_EC_AUTOCR_TRIGSEL  Autonomous Trigger selection
  * @brief    SPI Autonomous Trigger selection
  * @{
  */

#define LL_SPI_TRIG_GRP1                   (0x10000000U)                    /*!< Trigger Group for SPI1 and SPI2 */
#if defined(IS_SPI_GRP2_INSTANCE)
#define LL_SPI_TRIG_GRP2                   (0x20000000U)                    /*!< Trigger Group for SPI3 */
#endif /* IS_SPI_GRP2_INSTANCE */


/*!< HW Trigger signal is GPDMA1_CH0_TC      */
#define LL_SPI_TRIG_GRP1_GPDMA1_CH0_TC             (uint32_t)(LL_SPI_TRIG_GRP1 | (0x00000000U))
/*!< HW Trigger signal is GPDMA1_CH1_TC      */
#define LL_SPI_TRIG_GRP1_GPDMA1_CH1_TC             (uint32_t)(LL_SPI_TRIG_GRP1 | (0x1U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is GPDMA1_CH2_TC      */
#define LL_SPI_TRIG_GRP1_GPDMA1_CH2_TC             (uint32_t)(LL_SPI_TRIG_GRP1 | (0x2U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is GPDMA1_CH3_TC      */
#define LL_SPI_TRIG_GRP1_GPDMA1_CH3_TC             (uint32_t)(LL_SPI_TRIG_GRP1 | (0x3U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI4              */
#define LL_SPI_TRIG_GRP1_EXTI4                     (uint32_t)(LL_SPI_TRIG_GRP1 | (0x4U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI9              */
#define LL_SPI_TRIG_GRP1_EXTI9                     (uint32_t)(LL_SPI_TRIG_GRP1 | (0x5U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM1_CH1         */
#define LL_SPI_TRIG_GRP1_LPTIM1_CH1                (uint32_t)(LL_SPI_TRIG_GRP1 | (0x6U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM2_CH1         */
#define LL_SPI_TRIG_GRP1_LPTIM2_CH1                (uint32_t)(LL_SPI_TRIG_GRP1 | (0x7U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP1_OUT          */
#define LL_SPI_TRIG_GRP1_COMP1_OUT                 (uint32_t)(LL_SPI_TRIG_GRP1 | (0x8U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP2_OUT          */
#define LL_SPI_TRIG_GRP1_COMP2_OUT                 (uint32_t)(LL_SPI_TRIG_GRP1 | (0x9U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_ALRA_TRG       */
#define LL_SPI_TRIG_GRP1_RTC_ALRA_TRG              (uint32_t)(LL_SPI_TRIG_GRP1 | (0xAU << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_WUT_TRG        */
#define LL_SPI_TRIG_GRP1_RTC_WUT_TRG               (uint32_t)(LL_SPI_TRIG_GRP1 | (0xBU << SPI_AUTOCR_TRIGSEL_Pos))

#if defined(LL_SPI_TRIG_GRP2)
/*!< HW Trigger signal is LPDMA1_CH0_TC      */
#define LL_SPI_TRIG_GRP2_LPDMA1_CH0_TC             (uint32_t)(LL_SPI_TRIG_GRP2 | (0x00000000U))
/*!< HW Trigger signal is LPDMA1_CH1_TC      */
#define LL_SPI_TRIG_GRP2_LPDMA1_CH1_TC             (uint32_t)(LL_SPI_TRIG_GRP2 | (0x1U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPDMA1_CH2_TC      */
#define LL_SPI_TRIG_GRP2_LPDMA1_CH2_TC             (uint32_t)(LL_SPI_TRIG_GRP2 | (0x2U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPDMA1_CH3_TC      */
#define LL_SPI_TRIG_GRP2_LPDMA1_CH3_TC             (uint32_t)(LL_SPI_TRIG_GRP2 | (0x3U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI4              */
#define LL_SPI_TRIG_GRP2_EXTI4                     (uint32_t)(LL_SPI_TRIG_GRP2 | (0x4U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is EXTI8              */
#define LL_SPI_TRIG_GRP2_EXTI8                     (uint32_t)(LL_SPI_TRIG_GRP2 | (0x5U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM1_CH1         */
#define LL_SPI_TRIG_GRP2_LPTIM1_CH1                (uint32_t)(LL_SPI_TRIG_GRP2 | (0x6U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is LPTIM3_CH1         */
#define LL_SPI_TRIG_GRP2_LPTIM3_CH1                (uint32_t)(LL_SPI_TRIG_GRP2 | (0x7U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP1_OUT          */
#define LL_SPI_TRIG_GRP2_COMP1_OUT                 (uint32_t)(LL_SPI_TRIG_GRP2 | (0x8U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is COMP2_OUT          */
#define LL_SPI_TRIG_GRP2_COMP2_OUT                 (uint32_t)(LL_SPI_TRIG_GRP2 | (0x9U << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_ALRA_TRG       */
#define LL_SPI_TRIG_GRP2_RTC_ALRA_TRG              (uint32_t)(LL_SPI_TRIG_GRP2 | (0xAU << SPI_AUTOCR_TRIGSEL_Pos))
/*!< HW Trigger signal is RTC_WUT_TRG        */
#define LL_SPI_TRIG_GRP2_RTC_WUT_TRG               (uint32_t)(LL_SPI_TRIG_GRP2 | (0xBU << SPI_AUTOCR_TRIGSEL_Pos))
#endif /* LL_SPI_TRIG_GRP2 */

/**
  * @}
  */

/** @defgroup SPI_LL_EC_AUTOCR_TRIGPOL  Autonomous Trigger Polarity
  * @brief    SPI Autonomous Trigger Polarity
  * @{
  */
#define LL_SPI_AM_TRIG_RISING                      0x00000000U
#define LL_SPI_AM_TRIG_FALLING                     SPI_AUTOCR_TRIGPOL
/**
  * @}
  */

/** @defgroup SPI_LL_EC_CR1_MASRX  Master Receiver Automatic Suspension
  * @brief    SPI Master Receiver Automatic Suspension
  * @{
  */
#define LL_SPI_MASTER_RX_AUTO_SUSPEND_DISABLE          0x00000000U
#define LL_SPI_MASTER_RX_AUTO_SUSPEND_ENABLE           SPI_CR1_MASRX
/**
  * @}
  */

/** @defgroup SPI_LL_EC_CFG2_AFCNTR  Keep IO State
  * @brief    SPI Keep IO State
  * @{
  */
#define LL_SPI_MASTER_KEEP_IO_STATE_DISABLE        0x00000000U
#define LL_SPI_MASTER_KEEP_IO_STATE_ENABLE         SPI_CFG2_AFCNTR
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSSP_Mode NSS Pulse Mode
  * @brief    SPI NSS Pulse Mode
  * @{
  */
#define LL_SPI_NSS_PULSE_DISABLE                   (0x00000000UL)  /*!< Slave select IO pin is kept at active level till data transfer is   \
                                                                        completed, it becomes inactive with EOT flag  */
#define LL_SPI_NSS_PULSE_ENABLE                    (SPI_CFG2_SSOM) /*!< SPI data frames are interleaved with slave select IO pin non active \
                                                                        pulses when MIDI[3:0]>1  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_MOSI_MISO_SWAP Swap MISO and MOSI pins
  * @brief    SPI Swap MISO and MOSI pins
  * @{
  */
#define LL_SPI_MOSI_MISO_SWAP_DISABLE           (0x00000000UL)
#define LL_SPI_MOSI_MISO_SWAP_ENABLE            (SPI_CFG2_IOSWP)
/**
  * @}
  */
/** @defgroup SPI_LL_EC_RDY_PIN_POLARITY Ready pin input/output polarity
  * @brief    SPI Ready pin input/output polarity
  * @{
  */
#define LL_SPI_READY_PIN_POLARITY_HIGH          (0x00000000UL)
#define LL_SPI_READY_PIN_POLARITY_LOW           (SPI_CFG2_RDIOP)
/**
  * @}
  */


/** @defgroup SPI_LL_EC_RDY_PIN_MASTER_MANAGEMENT Ready Pin Input Master Management
  * @brief    SPI Ready Pin Input Master Management
  * @{
  */
#define  LL_SPI_READY_PIN_MASTER_MANAGEMENT_INTERNALLY          (0x00000000UL)
#define  LL_SPI_READY_PIN_MASTER_MANAGEMENT_EXTERNALLY          SPI_CFG2_RDIOM
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Macros SPI Exported Macros
  * @{
  */

/** @defgroup SPI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SPI register
  * @param  __INSTANCE__ SPI Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_SPI_WRITE_REG(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in SPI register
  * @param  __INSTANCE__ SPI Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_SPI_READ_REG(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup SPI_LL_Exported_Functions SPI Exported Functions
  * @{
  */

/** @defgroup SPI_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable SPI peripheral
  * @rmtoll
  *  CR1          SPE           LL_SPI_Enable
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_Enable(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Disable SPI peripheral
  * @rmtoll
  *  CR1          SPE           LL_SPI_Disable
  * @param  p_spix SPI Instance
  * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
  */
__STATIC_INLINE void LL_SPI_Disable(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Check if SPI peripheral is enabled
  * @rmtoll
  *  CR1          SPE           LL_SPI_IsEnabled
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabled(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CR1, SPI_CR1_SPE) == (SPI_CR1_SPE)) ? 1UL : 0UL);
}

/**
  * @brief  Swap the MOSI and MISO pin
  * @rmtoll
  *  CFG2         IOSWP         LL_SPI_EnableMosiMisoSwap
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_EnableMosiMisoSwap(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG2, SPI_CFG2_IOSWP);
}

/**
  * @brief  Restore default function for MOSI and MISO pin
  * @rmtoll
  *  CFG2         IOSWP         LL_SPI_DisableMosiMisoSwap
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_DisableMosiMisoSwap(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG2, SPI_CFG2_IOSWP);
}

/**
  * @brief  Check if MOSI and MISO pin are swapped
  * @rmtoll
  *  CFG2         IOSWP         LL_SPI_IsEnabledMosiMisoSwap
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledMosiMisoSwap(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG2, SPI_CFG2_IOSWP) == (SPI_CFG2_IOSWP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO control
  * @rmtoll
  *  CFG2         AFCNTR        LL_SPI_EnableGPIOControl
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_EnableGPIOControl(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG2, SPI_CFG2_AFCNTR);
}

/**
  * @brief  Disable GPIO control
  * @rmtoll
  *  CFG2         AFCNTR        LL_SPI_DisableGPIOControl
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_DisableGPIOControl(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG2, SPI_CFG2_AFCNTR);
}

/**
  * @brief  Check if GPIO control is active
  * @rmtoll
  *  CFG2         AFCNTR        LL_SPI_IsEnabledGPIOControl
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledGPIOControl(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG2, SPI_CFG2_AFCNTR) == (SPI_CFG2_AFCNTR)) ? 1UL : 0UL);
}

/**
  * @brief  Set SPI Mode to Master or Slave
  * @rmtoll
  *  CFG2         MASTER        LL_SPI_SetMode
  * @param  p_spix SPI Instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_SPI_MODE_MASTER
  *         @arg @ref LL_SPI_MODE_SLAVE
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetMode(SPI_TypeDef *p_spix, uint32_t mode)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_MASTER, mode);
}

/**
  * @brief  Get SPI Mode (Master or Slave)
  * @rmtoll
  *  CFG2         MASTER        LL_SPI_GetMode
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_MODE_MASTER
  *         @arg @ref LL_SPI_MODE_SLAVE
  */
__STATIC_INLINE uint32_t LL_SPI_GetMode(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_MASTER));
}

/**
  * @brief  Configure the Idleness applied by master between active edge of SS and first send data
  * @rmtoll
  *  CFG2         MSSI          LL_SPI_SetMasterSSIdleness
  * @param  p_spix SPI Instance
  * @param  master_ss_idleness This parameter can be one of the following values:
  *         @arg @ref LL_SPI_MSSI_DELAY_0_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_1_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_2_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_3_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_4_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_5_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_6_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_7_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_8_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_9_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_10_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_11_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_12_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_13_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_14_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_15_CYCLE
  */
__STATIC_INLINE void LL_SPI_SetMasterSSIdleness(SPI_TypeDef *p_spix, uint32_t master_ss_idleness)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_MSSI, master_ss_idleness);
}

/**
  * @brief  Get the configured Idleness applied by master
  * @rmtoll
  *  CFG2         MSSI          LL_SPI_GetMasterSSIdleness
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_MSSI_DELAY_0_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_1_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_2_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_3_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_4_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_5_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_6_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_7_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_8_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_9_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_10_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_11_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_12_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_13_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_14_CYCLE
  *         @arg @ref LL_SPI_MSSI_DELAY_15_CYCLE
  */
__STATIC_INLINE uint32_t LL_SPI_GetMasterSSIdleness(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_MSSI));
}

/**
  * @brief  Configure the idleness applied by master between data frame
  * @rmtoll
  *  CFG2         MIDI          LL_SPI_SetInterDataIdleness
  * @param  p_spix SPI Instance
  * @param  master_Inter_data_idleness This parameter can be one of the following values:
  *         @arg @ref LL_SPI_MIDI_DELAY_0_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_1_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_2_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_3_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_4_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_5_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_6_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_7_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_8_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_9_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_10_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_11_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_12_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_13_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_14_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_15_CYCLE
  */
__STATIC_INLINE void LL_SPI_SetInterDataIdleness(SPI_TypeDef *p_spix, uint32_t master_Inter_data_idleness)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_MIDI, master_Inter_data_idleness);
}

/**
  * @brief  Get the configured inter data idleness
  * @rmtoll
  *  CFG2         MIDI          LL_SPI_SetInterDataIdleness
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_MIDI_DELAY_0_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_1_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_2_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_3_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_4_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_5_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_6_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_7_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_8_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_9_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_10_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_11_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_12_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_13_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_14_CYCLE
  *         @arg @ref LL_SPI_MIDI_DELAY_15_CYCLE
  */
__STATIC_INLINE uint32_t LL_SPI_GetInterDataIdleness(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_MIDI));
}

/**
  * @brief  Set transfer size
  * @rmtoll
  *  CR2          TSIZE         LL_SPI_SetTransferSize
  * @param  p_spix SPI Instance
  * @param  count 0..0xFFFF
  * @note    count is the number of frame to be transferred
  */
__STATIC_INLINE void LL_SPI_SetTransferSize(SPI_TypeDef *p_spix, uint32_t count)
{
  MODIFY_REG(p_spix->CR2, SPI_CR2_TSIZE, count);
}

/**
  * @brief  Get transfer size
  * @rmtoll
  *  CR2          TSIZE         LL_SPI_GetTransferSize
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferSize(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CR2, SPI_CR2_TSIZE));
}

/**
  * @brief  Lock the AF configuration of associated IOs
  * @rmtoll
  *  CR1          IOLOCK        LL_SPI_EnableIOLock
  * @param  p_spix SPI Instance
  * @note   Once this bit is set, the AF configuration remains locked until a hardware reset occurs.
  *         the reset of the IOLock bit is done by hardware. for that, LL_SPI_DisableIOLock can not exist.
  */
__STATIC_INLINE void LL_SPI_EnableIOLock(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CR1, SPI_CR1_IOLOCK);
}

/**
  * @brief  Check if the AF configuration is locked.
  * @rmtoll
  *  CR1          IOLOCK        LL_SPI_IsEnabledIOLock
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIOLock(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CR1, SPI_CR1_IOLOCK) == (SPI_CR1_IOLOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Set Tx CRC Initialization Pattern
  * @rmtoll
  *  CR1          TCRCINI         LL_SPI_SetTxCRCInitPattern
  * @param  p_spix SPI Instance
  * @param  txcrc_init_all This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_TX_INIT_PATTERN_ALL_ZERO
  *         @arg @ref LL_SPI_CRC_TX_INIT_PATTERN_ALL_ONE
  */
__STATIC_INLINE void LL_SPI_SetTxCRCInitPattern(SPI_TypeDef *p_spix, uint32_t txcrc_init_all)
{
  MODIFY_REG(p_spix->CR1, SPI_CR1_TCRCINI, txcrc_init_all);
}

/**
  * @brief  Get Tx CRC Initialization Pattern
  * @rmtoll
  *  CR1          TCRCINI         LL_SPI_GetTxCRCInitPattern
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CRC_TX_INIT_PATTERN_ALL_ZERO
  *         @arg @ref LL_SPI_CRC_TX_INIT_PATTERN_ALL_ONE
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxCRCInitPattern(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CR1, SPI_CR1_TCRCINI));
}

/**
  * @brief  Set Rx CRC Initialization Pattern
  * @rmtoll
  *  CR1          RCRCINI         LL_SPI_SetRxCRCInitPattern
  * @param  p_spix SPI Instance
  * @param  rxcrc_init_all This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_RX_INIT_PATTERN_ALL_ZERO
  *         @arg @ref LL_SPI_CRC_RX_INIT_PATTERN_ALL_ONE
  */
__STATIC_INLINE void LL_SPI_SetRxCRCInitPattern(SPI_TypeDef *p_spix, uint32_t rxcrc_init_all)
{
  MODIFY_REG(p_spix->CR1, SPI_CR1_RCRCINI, rxcrc_init_all);
}

/**
  * @brief  Get Rx CRC Initialization Pattern
  * @rmtoll
  *  CR1          RCRCINI         LL_SPI_GetRxCRCInitPattern
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CRC_RX_INIT_PATTERN_ALL_ZERO
  *         @arg @ref LL_SPI_CRC_RX_INIT_PATTERN_ALL_ONE
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxCRCInitPattern(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CR1, SPI_CR1_RCRCINI));
}

/**
  * @brief  Set CRC Initialization Pattern
  * @rmtoll
  *  CR1          RCRCINI         LL_SPI_SetCRCInitPattern
  *  CR1          TCRCINI         LL_SPI_SetCRCInitPattern
  * @param  p_spix SPI Instance
  * @param  rxcrc_init_all This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_RX_INIT_PATTERN_ALL_ZERO
  *         @arg @ref LL_SPI_CRC_RX_INIT_PATTERN_ALL_ONE
  * @param  txcrc_init_all This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_TX_INIT_PATTERN_ALL_ZERO
  *         @arg @ref LL_SPI_CRC_TX_INIT_PATTERN_ALL_ONE
  */
__STATIC_INLINE void LL_SPI_SetCRCInitPattern(SPI_TypeDef *p_spix, uint32_t txcrc_init_all, uint32_t rxcrc_init_all)
{
  MODIFY_REG(p_spix->CR1, (SPI_CR1_RCRCINI | SPI_CR1_TCRCINI), txcrc_init_all | rxcrc_init_all);
}

/**
  * @brief  Get CRC Initialization Pattern
  * @rmtoll
  *  CR1          RCRCINI         LL_SPI_GetRxCRCInitPattern
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCInitPattern(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CR1, (SPI_CR1_TCRCINI | SPI_CR1_RCRCINI)));
}

/**
  * @brief  Set internal SS input level ignoring what comes from PIN.
  * @rmtoll
  *  CR1          SSI           LL_SPI_SetInternalSSLevel
  * @param  p_spix SPI Instance
  * @param  ss_level This parameter can be one of the following values:
  *         @arg @ref LL_SPI_SS_LEVEL_HIGH
  *         @arg @ref LL_SPI_SS_LEVEL_LOW
  * @note   This configuration has effect only with config LL_SPI_NSS_SOFT
  */
__STATIC_INLINE void LL_SPI_SetInternalSSLevel(SPI_TypeDef *p_spix, uint32_t ss_level)
{
  MODIFY_REG(p_spix->CR1, SPI_CR1_SSI, ss_level);
}

/**
  * @brief  Get internal SS input level
  * @rmtoll
  *  CR1          SSI           LL_SPI_GetInternalSSLevel
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_SS_LEVEL_HIGH
  *         @arg @ref LL_SPI_SS_LEVEL_LOW
  */
__STATIC_INLINE uint32_t LL_SPI_GetInternalSSLevel(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CR1, SPI_CR1_SSI));
}

/**
  * @brief  Enable CRC computation on 33/17 bits
  * @rmtoll
  *  CR1          CRC33_17      LL_SPI_EnableFullSizeCRC
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableFullSizeCRC(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CR1, SPI_CR1_CRC33_17);
}

/**
  * @brief  Disable CRC computation on 33/17 bits
  * @rmtoll
  *  CR1          CRC33_17      LL_SPI_DisableFullSizeCRC
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableFullSizeCRC(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CR1, SPI_CR1_CRC33_17);
}

/**
  * @brief  Check if Enable CRC computation on 33/17 bits is enabled
  * @rmtoll
  *  CR1          CRC33_17      LL_SPI_IsEnabledFullSizeCRC
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledFullSizeCRC(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CR1, SPI_CR1_CRC33_17) == (SPI_CR1_CRC33_17)) ? 1UL : 0UL);
}

/**
  * @brief  Suspend an ongoing transfer for Master configuration
  * @rmtoll
  *  CR1          CSUSP         LL_SPI_SuspendMasterTransfer
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_SuspendMasterTransfer(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CR1, SPI_CR1_CSUSP);
}

/**
  * @brief  Start effective transfer on wire for Master configuration
  * @rmtoll
  *  CR1          CSTART        LL_SPI_StartMasterTransfer
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_StartMasterTransfer(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CR1, SPI_CR1_CSTART);
}

/**
  * @brief  Check if there is an unfinished master transfer
  * @rmtoll
  *  CR1          CSTART        LL_SPI_IsActiveMasterTransfer
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveMasterTransfer(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CR1, SPI_CR1_CSTART) == (SPI_CR1_CSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Master Rx auto suspend in case of overrun
  * @rmtoll
  *  CR1          MASRX         LL_SPI_EnableMasterRxAutoSuspend
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableMasterRxAutoSuspend(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CR1, SPI_CR1_MASRX);
}

/**
  * @brief  Disable Master Rx auto suspend in case of overrun
  * @rmtoll
  *  CR1          MASRX         LL_SPI_DisableMasterRxAutoSuspend
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableMasterRxAutoSuspend(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CR1, SPI_CR1_MASRX);
}

/**
  * @brief  Check if Master Rx auto suspend is activated
  * @rmtoll
  *  CR1          MASRX         LL_SPI_IsEnabledMasterRxAutoSuspend
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledMasterRxAutoSuspend(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CR1, SPI_CR1_MASRX) == (SPI_CR1_MASRX)) ? 1UL : 0UL);
}

/**
  * @brief  Set Underrun Configuration
  * @rmtoll
  *  CFG1         UDRCFG        LL_SPI_SetUDRConfiguration
  * @param  p_spix SPI Instance
  * @param  udr_config This parameter can be one of the following values:
  *         @arg @ref LL_SPI_UNDERRUN_CONFIG_REGISTER_PATTERN
  *         @arg @ref LL_SPI_UNDERRUN_CONFIG_LAST_RECEIVED
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetUDRConfiguration(SPI_TypeDef *p_spix, uint32_t udr_config)
{
  MODIFY_REG(p_spix->CFG1, SPI_CFG1_UDRCFG, udr_config);
}

/**
  * @brief  Get Underrun Configuration
  * @rmtoll
  *  CFG1         UDRCFG        LL_SPI_GetUDRConfiguration
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_UNDERRUN_CONFIG_REGISTER_PATTERN
  *         @arg @ref LL_SPI_UNDERRUN_CONFIG_LAST_RECEIVED
  */
__STATIC_INLINE uint32_t LL_SPI_GetUDRConfiguration(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG1, SPI_CFG1_UDRCFG));
}


/**
  * @brief  Set Serial protocol used
  * @rmtoll
  *  CFG2         SP            LL_SPI_SetStandard
  * @param  p_spix SPI Instance
  * @param  standard This parameter can be one of the following values:
  *         @arg @ref LL_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref LL_SPI_PROTOCOL_TI
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetStandard(SPI_TypeDef *p_spix, uint32_t standard)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_SP, standard);
}

/**
  * @brief  Get Serial protocol used
  * @rmtoll
  *  CFG2         SP            LL_SPI_GetStandard
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref LL_SPI_PROTOCOL_TI
  */
__STATIC_INLINE uint32_t LL_SPI_GetStandard(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_SP));
}

/**
  * @brief  Set Clock phase
  * @rmtoll
  *  CFG2         CPHA          LL_SPI_SetClockPhase
  * @param  p_spix SPI Instance
  * @param  clock_phase This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CLOCK_PHASE_1_EDGE
  *         @arg @ref LL_SPI_CLOCK_PHASE_2_EDGE
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  */
__STATIC_INLINE void LL_SPI_SetClockPhase(SPI_TypeDef *p_spix, uint32_t clock_phase)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_CPHA, clock_phase);
}

/**
  * @brief  Get Clock phase
  * @rmtoll
  *  CFG2         CPHA          LL_SPI_GetClockPhase
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CLOCK_PHASE_1_EDGE
  *         @arg @ref LL_SPI_CLOCK_PHASE_2_EDGE
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPhase(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_CPHA));
}

/**
  * @brief  Set Clock polarity
  * @rmtoll
  *  CFG2         CPOL          LL_SPI_SetClockPolarity
  * @param  p_spix SPI Instance
  * @param  clock_polarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CLOCK_POLARITY_LOW
  *         @arg @ref LL_SPI_CLOCK_POLARITY_HIGH
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  */
__STATIC_INLINE void LL_SPI_SetClockPolarity(SPI_TypeDef *p_spix, uint32_t clock_polarity)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_CPOL, clock_polarity);
}

/**
  * @brief  Get Clock polarity
  * @rmtoll
  *  CFG2         CPOL          LL_SPI_GetClockPolarity
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CLOCK_POLARITY_LOW
  *         @arg @ref LL_SPI_CLOCK_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPolarity(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_CPOL));
}

/**
  * @brief  Enable ReadyPin
  * @rmtoll
  *  CFG2         RDIOM         LL_SPI_EnableReadyPin
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableReadyPin(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG2, LL_SPI_READY_PIN_MASTER_MANAGEMENT_EXTERNALLY);
}

/**
  * @brief  Disable ReadyPin
  * @rmtoll
  *  CFG2         RDIOM         LL_SPI_DisableReadyPin
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableReadyPin(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG2, LL_SPI_READY_PIN_MASTER_MANAGEMENT_EXTERNALLY);
}

/**
  * @brief  Check if ReadyPin is enabled
  * @rmtoll
  *  CFG2         RDIOM         LL_SPI_IsEnabledReadyPin
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledReadyPin(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG2, SPI_CFG2_RDIOM) == SPI_CFG2_RDIOM) ? 1UL : 0UL);
}

/**
  * @brief  Set ReadyPin polarity
  * @rmtoll
  *  CFG2         RDIOP         LL_SPI_SetReadyPinPolarity
  * @param  p_spix SPI Instance
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_READY_PIN_POLARITY_HIGH
  *         @arg @ref LL_SPI_READY_PIN_POLARITY_LOW
  */
__STATIC_INLINE void LL_SPI_SetReadyPinPolarity(SPI_TypeDef *p_spix, uint32_t polarity)
{
  SET_BIT(p_spix->CFG2, polarity);
}

/**
  * @brief  Get ReadyPin polarity
  * @rmtoll
  *  CFG2         RDIOP         LL_SPI_GetReadyPinPolarity
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_READY_PIN_POLARITY_HIGH
  *         @arg @ref LL_SPI_READY_PIN_POLARITY_LOW
  */
__STATIC_INLINE uint32_t LL_SPI_GetReadyPinPolarity(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_RDIOP));
}

/**
  * @brief  Set NSS polarity
  * @rmtoll
  *  CFG2         SSIOP          LL_SPI_SetNSSPolarity
  * @param  p_spix SPI Instance
  * @param  nss_polarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_NSS_POLARITY_LOW
  *         @arg @ref LL_SPI_NSS_POLARITY_HIGH
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  */
__STATIC_INLINE void LL_SPI_SetNSSPolarity(SPI_TypeDef *p_spix, uint32_t nss_polarity)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_SSIOP, nss_polarity);
}

/**
  * @brief  Get NSS polarity
  * @rmtoll
  *  CFG2         SSIOP          LL_SPI_GetNSSPolarity
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_NSS_POLARITY_LOW
  *         @arg @ref LL_SPI_NSS_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_SPI_GetNSSPolarity(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_SSIOP));
}

/**
  * @brief  Set Baudrate Prescaler
  * @rmtoll
  *  CFG1         MBR      LL_SPI_SetBaudRatePrescaler
  *  CFG1         BPASS    LL_SPI_SetBaudRatePrescaler
  * @param  p_spix SPI Instance
  * @param  baudrate This parameter can be one of the following values:
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_BYPASS
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_2
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_4
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_8
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_16
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_32
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_64
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_128
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_256
  * @note   This configuration can not be changed when SPI is enabled.
  *         SPI BaudRate = fPCLK/Pescaler.
  */
__STATIC_INLINE void LL_SPI_SetBaudRatePrescaler(SPI_TypeDef *p_spix, uint32_t baudrate)
{
  MODIFY_REG(p_spix->CFG1, (SPI_CFG1_MBR | SPI_CFG1_BPASS), baudrate);
}

/**
  * @brief  Get Baudrate Prescaler
  * @rmtoll
  *  CFG1         MBR      LL_SPI_GetBaudRatePrescaler
  *  CFG1         BPASS    LL_SPI_GetBaudRatePrescaler
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_BYPASS
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_2
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_4
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_8
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_16
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_32
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_64
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_128
  *         @arg @ref LL_SPI_BAUD_RATE_PRESCALER_256
  */
__STATIC_INLINE uint32_t LL_SPI_GetBaudRatePrescaler(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG1, (SPI_CFG1_MBR | SPI_CFG1_BPASS)));
}

/**
  * @brief  Configure the SPI Bus
  * @rmtoll
  *  CR1          SSI           LL_SPI_SetConfig \n
  *  CFG2         MASTER        LL_SPI_SetConfig \n
  *  CFG2         COMM          LL_SPI_SetConfig \n
  *  CFG2         CPOL          LL_SPI_SetConfig \n
  *  CFG2         CPHA          LL_SPI_SetConfig \n
  *  CFG2         LSBFRST       LL_SPI_SetConfig \n
  *  CFG1         DSIZE         LL_SPI_SetConfig \n
  *  CFG1         MBR           LL_SPI_SetConfig \n
  *  CFG1         BPASS         LL_SPI_SetConfig
  * @param  p_spix SPI Instance
  * @param cfg1_config This parameter can be a combination of the following groups:
  *         @arg @ref SPI_LL_EC_DATAWIDTH
  *         @arg @ref SPI_LL_EC_BAUDRATEPRESCALER
  * @param cfg2_config: This parameter must be a combination of mode,direction,clock polarity, clock phase, first bit
  *       and nss management mode from the following groups:
  *         @arg @ref SPI_LL_EC_MODE
  *         @arg @ref SPI_LL_EC_TRANSFER_DIRECTION
  *         @arg @ref SPI_LL_EC_POLARITY
  *         @arg @ref SPI_LL_EC_PHASE
  *         @arg @ref SPI_LL_EC_BIT_ORDER
  *         @arg @ref SPI_LL_EC_NSS_MODE
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetConfig(SPI_TypeDef *p_spix, uint32_t cfg1_config,
                                      uint32_t cfg2_config)
{
  uint32_t cfg2_reg_value = LL_SPI_READ_REG((p_spix), CFG2);

  if (((cfg2_config & (SPI_CFG2_SSOE | SPI_CFG2_SSM)) == LL_SPI_NSS_SOFT)
      && ((((cfg2_config & (SPI_CFG2_MASTER)) == LL_SPI_MODE_MASTER) && (IS_BIT_CLR(cfg2_reg_value, SPI_CFG2_SSIOP)))
          || (((cfg2_config & (SPI_CFG2_MASTER)) == LL_SPI_MODE_SLAVE)
              && (IS_BIT_SET(cfg2_reg_value, SPI_CFG2_SSIOP)))))
  {
    SET_BIT(p_spix->CR1, SPI_CR1_SSI);
  }
  else
  {
    CLEAR_BIT(p_spix->CR1, SPI_CR1_SSI);
  }
  MODIFY_REG(p_spix->CFG1, (SPI_CFG1_DSIZE | SPI_CFG1_MBR | SPI_CFG1_BPASS), cfg1_config);
  MODIFY_REG(p_spix->CFG2, (SPI_CFG2_SSOE | SPI_CFG2_SSM | SPI_CFG2_MASTER | SPI_CFG2_COMM |
                            SPI_CFG2_CPOL | SPI_CFG2_CPHA | SPI_CFG2_LSBFRST), cfg2_config);
}

/**
  * @brief  Set Transfer Bit Order
  * @rmtoll
  *  CFG2         LSBFRST       LL_SPI_SetTransferBitOrder
  * @param  p_spix SPI Instance
  * @param  bit_order This parameter can be one of the following values:
  *         @arg @ref LL_SPI_LSB_FIRST
  *         @arg @ref LL_SPI_MSB_FIRST
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  */
__STATIC_INLINE void LL_SPI_SetTransferBitOrder(SPI_TypeDef *p_spix, uint32_t bit_order)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_LSBFRST, bit_order);
}

/**
  * @brief  Get Transfer Bit Order
  * @rmtoll
  *  CFG2         LSBFRST       LL_SPI_GetTransferBitOrder
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_LSB_FIRST
  *         @arg @ref LL_SPI_MSB_FIRST
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferBitOrder(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_LSBFRST));
}

/**
  * @brief  Set Transfer Mode
  * @rmtoll
  *  CFG2         COMM          LL_SPI_SetTransferDirection
  * @param  p_spix SPI Instance
  * @param  transfer_direction This parameter can be one of the following values:
  *         @arg @ref LL_SPI_FULL_DUPLEX
  *         @arg @ref LL_SPI_SIMPLEX_TX
  *         @arg @ref LL_SPI_SIMPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX
  * @note   This configuration can not be changed when SPI is enabled except for half duplex direction
  *         using LL_SPI_SetHalfDuplexDirection.
  */
__STATIC_INLINE void LL_SPI_SetTransferDirection(SPI_TypeDef *p_spix, uint32_t transfer_direction)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_COMM, transfer_direction & SPI_CFG2_COMM);
}

/**
  * @brief  Get Transfer Mode
  * @rmtoll
  *  CFG2         COMM          LL_SPI_GetTransferDirection
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_FULL_DUPLEX
  *         @arg @ref LL_SPI_SIMPLEX_TX
  *         @arg @ref LL_SPI_SIMPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferDirection(const SPI_TypeDef *p_spix)
{
  return READ_BIT(p_spix->CFG2, SPI_CFG2_COMM);
}

/**
  * @brief  Set direction for Half-Duplex Mode
  * @rmtoll
  *  CR1          HDDIR         LL_SPI_SetHalfDuplexDirection
  * @param  p_spix SPI Instance
  * @param  half_duplex_direction This parameter can be one of the following values:
  *         @arg @ref LL_SPI_HALF_DUPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_TX
  * @note   In master mode the MOSI pin is used and in slave mode the MISO pin is used for Half-Duplex.
  */
__STATIC_INLINE void LL_SPI_SetHalfDuplexDirection(SPI_TypeDef *p_spix, uint32_t half_duplex_direction)
{
  MODIFY_REG(p_spix->CR1, SPI_CR1_HDDIR, half_duplex_direction & SPI_CR1_HDDIR);
}

/**
  * @brief  Get direction for Half-Duplex Mode
  * @rmtoll
  *  CR1          HDDIR         LL_SPI_GetHalfDuplexDirection
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_HALF_DUPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX_TX
  * @note   In master mode the MOSI pin is used and in slave mode the MISO pin is used for Half-Duplex.
  */
__STATIC_INLINE uint32_t LL_SPI_GetHalfDuplexDirection(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CR1, SPI_CR1_HDDIR));
}

/**
  * @brief  Check if the direction is Half duplex
  * @rmtoll
  *  CFG2         COMM          LL_SPI_IsHalfDuplexDirection
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsHalfDuplexDirection(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG2, SPI_CFG2_COMM) == SPI_CFG2_COMM) ? 1UL : 0UL);
}

/**
  * @brief  Set Frame Data Size
  * @rmtoll
  *  CFG1         DSIZE         LL_SPI_SetDataWidth
  * @param  p_spix SPI Instance
  * @param  data_width This parameter can be one of the following values:
  *         @arg @ref LL_SPI_DATA_WIDTH_4_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_5_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_6_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_7_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_8_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_9_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_10_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_11_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_12_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_13_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_14_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_15_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_16_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_17_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_18_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_19_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_20_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_21_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_22_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_23_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_24_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_25_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_26_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_27_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_28_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_29_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_30_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_31_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_32_BIT
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetDataWidth(SPI_TypeDef *p_spix, uint32_t data_width)
{
  MODIFY_REG(p_spix->CFG1, SPI_CFG1_DSIZE, data_width);
}

/**
  * @brief  Get Frame Data Size
  * @rmtoll
  *  CFG1         DSIZE         LL_SPI_GetDataWidth
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_DATA_WIDTH_4_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_5_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_6_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_7_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_8_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_9_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_10_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_11_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_12_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_13_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_14_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_15_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_16_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_17_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_18_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_19_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_20_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_21_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_22_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_23_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_24_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_25_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_26_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_27_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_28_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_29_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_30_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_31_BIT
  *         @arg @ref LL_SPI_DATA_WIDTH_32_BIT
  */
__STATIC_INLINE uint32_t LL_SPI_GetDataWidth(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG1, SPI_CFG1_DSIZE));
}

/**
  * @brief  Set threshold of FIFO that triggers a transfer event
  * @rmtoll
  *  CFG1         FTHLV         LL_SPI_SetFIFOThreshold
  * @param  p_spix SPI Instance
  * @param  threshold This parameter can be one of the following values:
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_1_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_2_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_3_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_4_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_5_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_6_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_7_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_8_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_9_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_10_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_11_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_12_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_13_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_14_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_15_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_16_DATA
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetFIFOThreshold(SPI_TypeDef *p_spix, uint32_t threshold)
{
  MODIFY_REG(p_spix->CFG1, SPI_CFG1_FTHLV, threshold);
}

/**
  * @brief  Get threshold of FIFO that triggers a transfer event
  * @rmtoll
  *  CFG1         FTHLV         LL_SPI_GetFIFOThreshold
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_1_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_2_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_3_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_4_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_5_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_6_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_7_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_8_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_9_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_10_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_11_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_12_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_13_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_14_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_15_DATA
  *         @arg @ref LL_SPI_FIFO_THRESHOLD_16_DATA
  */
__STATIC_INLINE uint32_t LL_SPI_GetFIFOThreshold(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG1, SPI_CFG1_FTHLV));
}

/**
  * @brief  Enable CRC
  * @rmtoll
  *  CFG1         CRCEN         LL_SPI_EnableCRC
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_EnableCRC(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG1, SPI_CFG1_CRCEN);
}

/**
  * @brief  Disable CRC
  * @rmtoll
  *  CFG1         CRCEN         LL_SPI_DisableCRC
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableCRC(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG1, SPI_CFG1_CRCEN);
}

/**
  * @brief  Check if CRC is enabled
  * @rmtoll
  *  CFG1         CRCEN         LL_SPI_IsEnabledCRC
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledCRC(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG1, SPI_CFG1_CRCEN) == SPI_CFG1_CRCEN) ? 1UL : 0UL);
}

/**
  * @brief  Set CRC Length
  * @rmtoll
  *  CFG1         CRCSIZE       LL_SPI_SetCRCWidth
  * @param  p_spix SPI Instance
  * @param  crc_length This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_LENGTH_4_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_5_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_6_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_7_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_8_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_9_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_10_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_11_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_12_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_13_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_14_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_15_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_16_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_17_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_18_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_19_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_20_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_21_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_22_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_23_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_24_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_25_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_26_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_27_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_28_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_29_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_30_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_31_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_32_BIT
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetCRCWidth(SPI_TypeDef *p_spix, uint32_t crc_length)
{
  MODIFY_REG(p_spix->CFG1, SPI_CFG1_CRCSIZE, crc_length);
}

/**
  * @brief  Get CRC Length
  * @rmtoll
  *  CFG1          CRCSIZE       LL_SPI_GetCRCWidth
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CRC_LENGTH_4_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_5_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_6_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_7_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_8_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_9_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_10_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_11_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_12_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_13_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_14_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_15_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_16_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_17_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_18_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_19_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_20_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_21_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_22_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_23_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_24_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_25_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_26_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_27_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_28_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_29_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_30_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_31_BIT
  *         @arg @ref LL_SPI_CRC_LENGTH_32_BIT
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCWidth(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG1, SPI_CFG1_CRCSIZE));
}

/**
  * @brief  Set NSS Mode
  *         This bit is not used in SPI TI mode.
  * @rmtoll
  *  CFG2         SSM           LL_SPI_SetNSSMode \n
  *  CFG2         SSOE          LL_SPI_SetNSSMode
  * @param  p_spix SPI Instance
  * @param  nss This parameter can be one of the following values:
  *         @arg @ref LL_SPI_NSS_SOFT
  *         @arg @ref LL_SPI_NSS_HARD_INPUT
  *         @arg @ref LL_SPI_NSS_HARD_OUTPUT
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_SetNSSMode(SPI_TypeDef *p_spix, uint32_t nss)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_SSM | SPI_CFG2_SSOE, nss);
}

/**
  * @brief  Get NSS Mode
  * @rmtoll
  *  CFG2         SSM           LL_SPI_GetNSSMode \n
  *  CFG2         SSOE          LL_SPI_GetNSSMode
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_NSS_SOFT
  *         @arg @ref LL_SPI_NSS_HARD_INPUT
  *         @arg @ref LL_SPI_NSS_HARD_OUTPUT
  */
__STATIC_INLINE uint32_t LL_SPI_GetNSSMode(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->CFG2, SPI_CFG2_SSM | SPI_CFG2_SSOE));
}

/**
  * @brief  Enable NSS pulse mgt
  *         This bit is not used in SPI TI mode.
  * @rmtoll
  *  CFG2         SSOM          LL_SPI_EnableNSSPulseMgt
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  */
__STATIC_INLINE void LL_SPI_EnableNSSPulseMgt(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG2, SPI_CFG2_SSOM);
}

/**
  * @brief  Disable NSS pulse mgt
  * @rmtoll
  *  CFG2         SSOM          LL_SPI_DisableNSSPulseMgt
  * @param  p_spix SPI Instance
  * @note   This configuration can not be changed when SPI is enabled.
  *         This bit is not used in SPI TI mode.
  */
__STATIC_INLINE void LL_SPI_DisableNSSPulseMgt(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG2, SPI_CFG2_SSOM);
}

/**
  * @brief  Check if NSS pulse is enabled
  * @rmtoll
  *  CFG2         SSOM          LL_SPI_IsEnabledNSSPulse
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledNSSPulse(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG2, SPI_CFG2_SSOM) == SPI_CFG2_SSOM) ? 1UL : 0UL);
}

/**
  * @brief  Set NSS Config
  * @rmtoll
  *  CFG2         SSIOP          LL_SPI_SetNSSConfig \n
  *  CFG2         SSOM           LL_SPI_SetNSSConfig \n
  *  CFG2         MSSI           LL_SPI_SetNSSConfig
  * @param  p_spix SPI Instance
  * @param  cfg2_config This parameter must be a combinason of the following values :
  *         @arg @ref SPI_LL_EC_NSS_POLARITY
  *         @arg @ref SPI_LL_EC_NSS_MSSI
  *         @arg @ref SPI_LL_EC_NSSP_Mode
  * @note   This configuration can not be changed when SPI is enabled.
  *         Those bits are not used in SPI TI mode.
  */
__STATIC_INLINE void LL_SPI_SetNSSConfig(SPI_TypeDef *p_spix, uint32_t cfg2_config)
{
  MODIFY_REG(p_spix->CFG2, SPI_CFG2_SSIOP | SPI_CFG2_SSOM | SPI_CFG2_MSSI, cfg2_config);
}

/**
  * @brief  Get NSS Config
  * @rmtoll
  *  CFG2         SSIOP          LL_SPI_GetNSSConfig \n
  *  CFG2         SSOM           LL_SPI_GetNSSConfig \n
  *  CFG2         MSSI           LL_SPI_GetNSSConfig
  * @param  p_spix SPI Instance
  * @retval This function returns a combinason of the following values :
  *         @arg @ref SPI_LL_EC_NSS_POLARITY
  *         @arg @ref SPI_LL_EC_NSS_MSSI
  *         @arg @ref SPI_LL_EC_NSSP_Mode
  * @note   This configuration can not be changed when SPI is enabled.
  *         Those bits are not used in SPI TI mode.
  */
__STATIC_INLINE uint32_t LL_SPI_GetNSSConfig(const SPI_TypeDef *p_spix)
{
  return READ_REG(p_spix->CFG2) & (SPI_CFG2_SSIOP | SPI_CFG2_SSOM | SPI_CFG2_MSSI);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Indicate the status of a mask of flags
  * @rmtoll
  *  SR    SPI_SR_RXP        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_TXP        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_DXP        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_EOT        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_TXTF       LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_UDR        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_CRCE       LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_MODF       LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_OVR        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_TIFRE      LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_SUSP       LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_TXC        LL_SPI_IsActiveFlag \n
  *  SR    SPI_SR_RXWNE      LL_SPI_IsActiveFlag
  * @param  p_spix SPI Instance.
  * @param  mask Interrupts sources to check.
  *         This parameter can be a combination of the following values:
  *            @arg @ref  LL_SPI_FLAG_RXP
  *            @arg @ref  LL_SPI_FLAG_TXP
  *            @arg @ref  LL_SPI_FLAG_DXP
  *            @arg @ref  LL_SPI_FLAG_EOT
  *            @arg @ref  LL_SPI_FLAG_TXTF
  *            @arg @ref  LL_SPI_FLAG_UDR
  *            @arg @ref  LL_SPI_FLAG_CRCE
  *            @arg @ref  LL_SPI_FLAG_MODF
  *            @arg @ref  LL_SPI_FLAG_OVR
  *            @arg @ref  LL_SPI_FLAG_TIFRE
  *            @arg @ref  LL_SPI_FLAG_SUSP
  *            @arg @ref  LL_SPI_FLAG_TXC
  *            @arg @ref  LL_SPI_FLAG_RXWNE
  * @retval State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag(const SPI_TypeDef *p_spix, uint32_t mask)
{
  return ((READ_BIT(p_spix->SR, mask) == (mask)) ? 1UL : 0UL);
}

/**
  * @brief  Check if there is enough data in FIFO to read a full packet
  * @rmtoll
  *  SR           RXP           LL_SPI_IsActiveFlag_RXP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_RXP) == (SPI_SR_RXP)) ? 1UL : 0UL);
}

/**
  * @brief  Check if there is enough space in FIFO to hold a full packet
  * @rmtoll
  *  SR           TXP           LL_SPI_IsActiveFlag_TXP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_TXP) == (SPI_SR_TXP)) ? 1UL : 0UL);
}

/**
  * @brief  Check if there enough space in FIFO to hold a full packet, AND enough data to read a full packet
  * @rmtoll
  *  SR           DXP           LL_SPI_IsActiveFlag_DXP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_DXP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_DXP) == (SPI_SR_DXP)) ? 1UL : 0UL);
}

/**
  * @brief  Check that end of transfer event occurred
  * @rmtoll
  *  SR           EOT           LL_SPI_IsActiveFlag_EOT
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_EOT(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_EOT) == (SPI_SR_EOT)) ? 1UL : 0UL);
}

/**
  * @brief  Check that all required data has been filled in the fifo according to transfer size
  * @rmtoll
  *  SR           TXTF          LL_SPI_IsActiveFlag_TXTF
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXTF(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_TXTF) == (SPI_SR_TXTF)) ? 1UL : 0UL);
}

/**
  * @brief  Get Underrun error flag
  * @rmtoll
  *  SR           UDR           LL_SPI_IsActiveFlag_UDR
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_UDR(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_UDR) == (SPI_SR_UDR)) ? 1UL : 0UL);
}

/**
  * @brief  Get CRC error flag
  * @rmtoll
  *  SR           CRCE        LL_SPI_IsActiveFlag_CRCERR
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_CRCERR(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_CRCE) == (SPI_SR_CRCE)) ? 1UL : 0UL);
}

/**
  * @brief  Get Mode fault error flag
  * @rmtoll
  *  SR           MODF          LL_SPI_IsActiveFlag_MODF
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_MODF(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_MODF) == (SPI_SR_MODF)) ? 1UL : 0UL);
}

/**
  * @brief  Get Overrun error flag
  * @rmtoll
  *  SR           OVR           LL_SPI_IsActiveFlag_OVR
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_OVR(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_OVR) == (SPI_SR_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get TI Frame format error flag
  * @rmtoll
  *  SR           TIFRE         LL_SPI_IsActiveFlag_FRE
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_FRE(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_TIFRE) == (SPI_SR_TIFRE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if a suspend operation is done
  * @rmtoll
  *  SR           SUSP          LL_SPI_IsActiveFlag_SUSP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_SUSP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_SUSP) == (SPI_SR_SUSP)) ? 1UL : 0UL);
}

/**
  * @brief  Check if last TxFIFO or CRC frame transmission is completed
  * @rmtoll
  *  SR           TXC           LL_SPI_IsActiveFlag_TXC
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXC(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_TXC) == (SPI_SR_TXC)) ? 1UL : 0UL);
}

/**
  * @brief  Check if at least one 32-bit data is available in RxFIFO
  * @rmtoll
  *  SR           RXWNE         LL_SPI_IsActiveFlag_RXWNE
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXWNE(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->SR, SPI_SR_RXWNE) == (SPI_SR_RXWNE)) ? 1UL : 0UL);
}

/**
  * @brief  Get number of data framed remaining in current TSIZE
  * @rmtoll
  *  SR           CTSIZE           LL_SPI_GetRemainingDataFrames
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetRemainingDataFrames(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->SR, SPI_SR_CTSIZE) >> SPI_SR_CTSIZE_Pos);
}

/**
  * @brief  Get RxFIFO packing Level
  * @rmtoll
  *  SR           RXPLVL        LL_SPI_GetRxFIFOPackingLevel
  * @param  p_spix SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_RX_FIFO_0PACKET
  *         @arg @ref LL_SPI_RX_FIFO_1PACKET
  *         @arg @ref LL_SPI_RX_FIFO_2PACKET
  *         @arg @ref LL_SPI_RX_FIFO_3PACKET
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxFIFOPackingLevel(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->SR, SPI_SR_RXPLVL));
}

/**
  * @brief  Clear the status of a mask of flags
  * @rmtoll
  *  IFCR    SPI_IFCR_EOT    LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_TXTF   LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_UDR    LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_CRCE   LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_MODF   LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_OVR    LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_TIFRE  LL_SPI_ClearFlag \n
  *  IFCR    SPI_IFCR_SUSP   LL_SPI_ClearFlag
  * @param  p_spix SPI Instance.
  * @param  mask Flags to clear.
  *         This parameter can be a combination of the following values:
  *            @arg @ref  LL_SPI_FLAG_EOT
  *            @arg @ref  LL_SPI_FLAG_TXTF
  *            @arg @ref  LL_SPI_FLAG_UDR
  *            @arg @ref  LL_SPI_FLAG_CRCE
  *            @arg @ref  LL_SPI_FLAG_MODF
  *            @arg @ref  LL_SPI_FLAG_OVR
  *            @arg @ref  LL_SPI_FLAG_TIFRE
  *            @arg @ref  LL_SPI_FLAG_SUSP
  */
__STATIC_INLINE void LL_SPI_ClearFlag(SPI_TypeDef *p_spix, uint32_t mask)
{
  SET_BIT(p_spix->IFCR, (mask));
}

/**
  * @brief  Clear End Of Transfer flag
  * @rmtoll
  *  IFCR         EOTC          LL_SPI_ClearFlag_EOT
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_EOT(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_EOTC);
}

/**
  * @brief  Clear TXTF flag
  * @rmtoll
  *  IFCR         TXTFC         LL_SPI_ClearFlag_TXTF
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_TXTF(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_TXTFC);
}

/**
  * @brief  Clear Underrun error flag
  * @rmtoll
  *  IFCR         UDRC          LL_SPI_ClearFlag_UDR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_UDR(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_UDRC);
}

/**
  * @brief  Clear Overrun error flag
  * @rmtoll
  *  IFCR         OVRC          LL_SPI_ClearFlag_OVR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_OVR(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_OVRC);
}

/**
  * @brief  Clear CRC error flag
  * @rmtoll
  *  IFCR         CRCEC        LL_SPI_ClearFlag_CRCERR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_CRCERR(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_CRCEC);
}

/**
  * @brief  Clear Mode fault error flag
  * @rmtoll
  *  IFCR         MODFC         LL_SPI_ClearFlag_MODF
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_MODF(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_MODFC);
}

/**
  * @brief  Clear Frame format error flag
  * @rmtoll
  *  IFCR         TIFREC        LL_SPI_ClearFlag_FRE
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_FRE(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_TIFREC);
}

/**
  * @brief  Clear SUSP flag
  * @rmtoll
  *  IFCR         SUSPC         LL_SPI_ClearFlag_SUSP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_ClearFlag_SUSP(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IFCR, SPI_IFCR_SUSPC);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable masked IT
  * @rmtoll
  *  IER    SPI_IER_RXPIE    LL_SPI_EnableIT \n
  *  IER    SPI_IER_TXPIE    LL_SPI_EnableIT \n
  *  IER    SPI_IER_DXPIE    LL_SPI_EnableIT \n
  *  IER    SPI_IER_EOTIE    LL_SPI_EnableIT \n
  *  IER    SPI_IER_TXTFIE   LL_SPI_EnableIT \n
  *  IER    SPI_IER_UDRIE    LL_SPI_EnableIT \n
  *  IER    SPI_IER_CRCEIE   LL_SPI_EnableIT \n
  *  IER    SPI_IER_MODFIE   LL_SPI_EnableIT \n
  *  IER    SPI_IER_OVRIE    LL_SPI_EnableIT \n
  *  IER    SPI_IER_TIFREIE  LL_SPI_EnableIT
  * @param  p_spix SPI Instance.
  * @param  mask Interrupts sources to Enable.
  *         This parameter can be a combination of the following values:
  *            @arg @ref  LL_SPI_IT_RXP
  *            @arg @ref  LL_SPI_IT_TXP
  *            @arg @ref  LL_SPI_IT_DXP
  *            @arg @ref  LL_SPI_IT_EOT
  *            @arg @ref  LL_SPI_IT_TXTF
  *            @arg @ref  LL_SPI_IT_UDR
  *            @arg @ref  LL_SPI_IT_CRCE
  *            @arg @ref  LL_SPI_IT_MODF
  *            @arg @ref  LL_SPI_IT_OVR
  *            @arg @ref  LL_SPI_IT_TIFRE
  */
__STATIC_INLINE void LL_SPI_EnableIT(SPI_TypeDef *p_spix, uint32_t mask)
{
  SET_BIT(p_spix->IER, (mask));
}

/**
  * @brief  Enable Rx Packet available IT
  * @rmtoll
  *  IER          RXPIE         LL_SPI_EnableIT_RXP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXP(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_RXPIE);
}

/**
  * @brief  Enable Tx Packet space available IT
  * @rmtoll
  *  IER          TXPIE         LL_SPI_EnableIT_TXP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXP(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_TXPIE);
}

/**
  * @brief  Enable Duplex Packet available IT
  * @rmtoll
  *  IER          DXPIE         LL_SPI_EnableIT_DXP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_DXP(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_DXPIE);
}

/**
  * @brief  Enable End Of Transfer IT
  * @rmtoll
  *  IER          EOTIE         LL_SPI_EnableIT_EOT
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_EOT(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_EOTIE);
}

/**
  * @brief  Enable Transmit IT
  * @rmtoll
  *  IER          TXTFIE        LL_SPI_EnableIT_TXTF
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXTF(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_TXTFIE);
}

/**
  * @brief  Enable Underrun IT
  * @rmtoll
  *  IER          UDRIE         LL_SPI_EnableIT_UDR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_UDR(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_UDRIE);
}

/**
  * @brief  Enable Overrun IT
  * @rmtoll
  *  IER          OVRIE         LL_SPI_EnableIT_OVR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_OVR(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_OVRIE);
}

/**
  * @brief  Enable CRC Error IT
  * @rmtoll
  *  IER          CRCEIE        LL_SPI_EnableIT_CRCERR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_CRCERR(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_CRCEIE);
}

/**
  * @brief  Enable TI Frame Format Error IT
  * @rmtoll
  *  IER          TIFREIE       LL_SPI_EnableIT_FRE
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_FRE(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_TIFREIE);
}

/**
  * @brief  Enable Mode Fault IT
  * @rmtoll
  *  IER          MODFIE        LL_SPI_EnableIT_MODF
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableIT_MODF(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->IER, SPI_IER_MODFIE);
}


/**
  * @brief  Disable masked IT
  * @rmtoll
  *  IER    SPI_IER_RXPIE    LL_SPI_DisableIT \n
  *  IER    SPI_IER_TXPIE    LL_SPI_DisableIT \n
  *  IER    SPI_IER_DXPIE    LL_SPI_DisableIT \n
  *  IER    SPI_IER_EOTIE    LL_SPI_DisableIT \n
  *  IER    SPI_IER_TXTFIE   LL_SPI_DisableIT \n
  *  IER    SPI_IER_UDRIE    LL_SPI_DisableIT \n
  *  IER    SPI_IER_CRCEIE   LL_SPI_DisableIT \n
  *  IER    SPI_IER_MODFIE   LL_SPI_DisableIT \n
  *  IER    SPI_IER_OVRIE    LL_SPI_DisableIT \n
  *  IER    SPI_IER_TIFREIE  LL_SPI_DisableIT
  * @param  p_spix SPI Instance.
  * @param  mask Interrupts sources to Disable.
  *         This parameter can be a combination of the following values:
  *            @arg @ref  LL_SPI_IT_RXP
  *            @arg @ref  LL_SPI_IT_TXP
  *            @arg @ref  LL_SPI_IT_DXP
  *            @arg @ref  LL_SPI_IT_EOT
  *            @arg @ref  LL_SPI_IT_TXTF
  *            @arg @ref  LL_SPI_IT_UDR
  *            @arg @ref  LL_SPI_IT_CRCE
  *            @arg @ref  LL_SPI_IT_MODF
  *            @arg @ref  LL_SPI_IT_OVR
  *            @arg @ref  LL_SPI_IT_TIFRE
  */
__STATIC_INLINE void LL_SPI_DisableIT(SPI_TypeDef *p_spix, uint32_t mask)
{
  ATOMIC_CLEAR_BIT(p_spix->IER, (mask));
}

/**
  * @brief  Disable Rx Packet available IT
  * @rmtoll
  *  IER          RXPIE         LL_SPI_DisableIT_RXP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXP(SPI_TypeDef *p_spix)
{
  ATOMIC_CLEAR_BIT(p_spix->IER, SPI_IER_RXPIE);
}

/**
  * @brief  Disable Tx Packet space available IT
  * @rmtoll
  *  IER          TXPIE         LL_SPI_DisableIT_TXP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXP(SPI_TypeDef *p_spix)
{
  ATOMIC_CLEAR_BIT(p_spix->IER, SPI_IER_TXPIE);
}

/**
  * @brief  Disable Duplex Packet available IT
  * @rmtoll
  *  IER          DXPIE         LL_SPI_DisableIT_DXP
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_DXP(SPI_TypeDef *p_spix)
{
  ATOMIC_CLEAR_BIT(p_spix->IER, SPI_IER_DXPIE);
}

/**
  * @brief  Disable End Of Transfer IT
  * @rmtoll
  *  IER          EOTIE         LL_SPI_DisableIT_EOT
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_EOT(SPI_TypeDef *p_spix)
{
  ATOMIC_CLEAR_BIT(p_spix->IER, SPI_IER_EOTIE);
}

/**
  * @brief  Disable TXTF IT
  * @rmtoll
  *  IER          TXTFIE        LL_SPI_DisableIT_TXTF
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXTF(SPI_TypeDef *p_spix)
{
  ATOMIC_CLEAR_BIT(p_spix->IER, SPI_IER_TXTFIE);
}

/**
  * @brief  Disable Underrun IT
  * @rmtoll
  *  IER          UDRIE         LL_SPI_DisableIT_UDR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_UDR(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->IER, SPI_IER_UDRIE);
}

/**
  * @brief  Disable Overrun IT
  * @rmtoll
  *  IER          OVRIE         LL_SPI_DisableIT_OVR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_OVR(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->IER, SPI_IER_OVRIE);
}

/**
  * @brief  Disable CRC Error IT
  * @rmtoll
  *  IER          CRCEIE        LL_SPI_DisableIT_CRCERR
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_CRCERR(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->IER, SPI_IER_CRCEIE);
}

/**
  * @brief  Disable TI Frame Format Error IT
  * @rmtoll
  *  IER          TIFREIE       LL_SPI_DisableIT_FRE
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_FRE(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->IER, SPI_IER_TIFREIE);
}

/**
  * @brief  Disable MODF IT
  * @rmtoll
  *  IER          MODFIE        LL_SPI_DisableIT_MODF
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableIT_MODF(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->IER, SPI_IER_MODFIE);
}


/**
  * @brief  Check if masked IT is Enabled
  * @rmtoll
  *  IER    SPI_IER_RXPIE    LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_TXPIE    LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_DXPIE    LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_EOTIE    LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_TXTFIE   LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_UDRIE    LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_CRCEIE   LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_MODFIE   LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_OVRIE    LL_SPI_IsEnabledIT \n
  *  IER    SPI_IER_TIFREIE  LL_SPI_IsEnabledIT
  * @param  p_spix SPI Instance.
  * @param  mask Interrupts sources to check.
  *         This parameter can be a combination of the following values:
  *            @arg @ref  LL_SPI_IT_RXP
  *            @arg @ref  LL_SPI_IT_TXP
  *            @arg @ref  LL_SPI_IT_DXP
  *            @arg @ref  LL_SPI_IT_EOT
  *            @arg @ref  LL_SPI_IT_TXTF
  *            @arg @ref  LL_SPI_IT_UDR
  *            @arg @ref  LL_SPI_IT_CRCE
  *            @arg @ref  LL_SPI_IT_MODF
  *            @arg @ref  LL_SPI_IT_OVR
  *            @arg @ref  LL_SPI_IT_TIFRE
  * @retval State of masked bits (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT(const SPI_TypeDef *p_spix, uint32_t mask)
{
  return ((READ_BIT(p_spix->IER, mask) == (mask)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx Packet available IT is enabled
  * @rmtoll
  *  IER          RXPIE         LL_SPI_IsEnabledIT_RXP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_RXPIE) == (SPI_IER_RXPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx Packet space available IT is enabled
  * @rmtoll
  *  IER          TXPIE         LL_SPI_IsEnabledIT_TXP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_TXPIE) == (SPI_IER_TXPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Duplex Packet available IT is enabled
  * @rmtoll
  *  IER          DXPIE         LL_SPI_IsEnabledIT_DXP
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_DXP(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_DXPIE) == (SPI_IER_DXPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if End Of Transfer IT is enabled
  * @rmtoll
  *  IER          EOTIE         LL_SPI_IsEnabledIT_EOT
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_EOT(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_EOTIE) == (SPI_IER_EOTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if TXTF IT is enabled
  * @rmtoll
  *  IER          TXTFIE        LL_SPI_IsEnabledIT_TXTF
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXTF(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_TXTFIE) == (SPI_IER_TXTFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Underrun IT is enabled
  * @rmtoll
  *  IER          UDRIE         LL_SPI_IsEnabledIT_UDR
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_UDR(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_UDRIE) == (SPI_IER_UDRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Overrun IT is enabled
  * @rmtoll
  *  IER          OVRIE         LL_SPI_IsEnabledIT_OVR
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_OVR(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_OVRIE) == (SPI_IER_OVRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if CRC Error IT is enabled
  * @rmtoll
  *  IER          CRCEIE        LL_SPI_IsEnabledIT_CRCERR
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_CRCERR(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_CRCEIE) == (SPI_IER_CRCEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if TI Frame Format Error IT is enabled
  * @rmtoll
  *  IER          TIFREIE       LL_SPI_IsEnabledIT_FRE
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_FRE(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_TIFREIE) == (SPI_IER_TIFREIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if MODF IT is enabled
  * @rmtoll
  *  IER          MODFIE        LL_SPI_IsEnabledIT_MODF
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_MODF(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->IER, SPI_IER_MODFIE) == (SPI_IER_MODFIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_DMA_Management DMA Management
  * @{
  */

/**
  * @brief  Enable DMA Rx
  * @rmtoll
  *  CFG1         RXDMAEN       LL_SPI_EnableDMAReq_RX
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_RX(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG1, SPI_CFG1_RXDMAEN);
}

/**
  * @brief  Disable DMA Rx
  * @rmtoll
  *  CFG1         RXDMAEN       LL_SPI_DisableDMAReq_RX
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_RX(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG1, SPI_CFG1_RXDMAEN);
}

/**
  * @brief  Check if DMA Rx is enabled
  * @rmtoll
  *  CFG1         RXDMAEN       LL_SPI_IsEnabledDMAReq_RX
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_RX(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG1, SPI_CFG1_RXDMAEN) == (SPI_CFG1_RXDMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable DMA Tx
  * @rmtoll
  *  CFG1         TXDMAEN       LL_SPI_EnableDMAReq_TX
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_TX(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->CFG1, SPI_CFG1_TXDMAEN);
}

/**
  * @brief  Disable DMA Tx
  * @rmtoll
  *  CFG1         TXDMAEN       LL_SPI_DisableDMAReq_TX
  * @param  p_spix SPI Instance
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_TX(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->CFG1, SPI_CFG1_TXDMAEN);
}

/**
  * @brief  Check if DMA Tx is enabled
  * @rmtoll
  *  CFG1         TXDMAEN       LL_SPI_IsEnabledDMAReq_TX
  * @param  p_spix SPI Instance
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_TX(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->CFG1, SPI_CFG1_TXDMAEN) == (SPI_CFG1_TXDMAEN)) ? 1UL : 0UL);
}
/**
  * @brief  Get the data register address used for DMA transfer
  * @rmtoll
  *  TXDR           TXDR            LL_SPI_DMA_GetTxRegAddr
  * @param  p_spix SPI Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t LL_SPI_DMA_GetTxRegAddr(const SPI_TypeDef *p_spix)
{
  return (uint32_t) &(p_spix->TXDR);
}

/**
  * @brief  Get the data register address used for DMA transfer
  * @rmtoll
  *  RXDR           RXDR            LL_SPI_DMA_GetRxRegAddr
  * @param  p_spix SPI Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t LL_SPI_DMA_GetRxRegAddr(const SPI_TypeDef *p_spix)
{
  return (uint32_t) &(p_spix->RXDR);
}
/**
  * @}
  */

/** @defgroup SPI_LL_EF_DATA_Management DATA_Management
  * @{
  */

/**
  * @brief  Read Data Register
  * @rmtoll
  *  RXDR         .       LL_SPI_ReceiveData8
  * @param  p_spix SPI Instance
  * @retval 0..0xFF
  */
__STATIC_INLINE uint8_t LL_SPI_ReceiveData8(SPI_TypeDef *p_spix)
{
  return (*((__IO uint8_t *)&p_spix->RXDR));
}

/**
  * @brief  Read Data Register
  * @rmtoll
  *  RXDR         .       LL_SPI_ReceiveData16
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint16_t LL_SPI_ReceiveData16(SPI_TypeDef *p_spix)
{
#if defined (__GNUC__)
  __IO uint16_t *p_spirxdr = (__IO uint16_t *)(&(p_spix->RXDR));
  return (*p_spirxdr);
#else
  return (*((__IO uint16_t *)&p_spix->RXDR));
#endif /* __GNUC__ */
}

/**
  * @brief  Read Data Register
  * @rmtoll
  *  RXDR         .       LL_SPI_ReceiveData32
  * @param  p_spix SPI Instance
  * @retval  0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_ReceiveData32(SPI_TypeDef *p_spix)
{
  return (*((__IO uint32_t *)&p_spix->RXDR));
}

/**
  * @brief  Write Data Register
  * @rmtoll
  *  TXDR         .       LL_SPI_TransmitData8
  * @param  p_spix SPI Instance
  * @param  tx_data 0..0xFF
  */
__STATIC_INLINE void LL_SPI_TransmitData8(SPI_TypeDef *p_spix, uint8_t tx_data)
{
  *((__IO uint8_t *)&p_spix->TXDR) = tx_data;
}

/**
  * @brief  Write Data Register
  * @rmtoll
  *  TXDR         .       LL_SPI_TransmitData16
  * @param  p_spix SPI Instance
  * @param  tx_data 0..0xFFFF
  */
__STATIC_INLINE void LL_SPI_TransmitData16(SPI_TypeDef *p_spix, uint16_t tx_data)
{
#if defined (__GNUC__)
  __IO uint16_t *p_spitxdr = ((__IO uint16_t *)&p_spix->TXDR);
  *p_spitxdr = tx_data;
#else
  *((__IO uint16_t *)&p_spix->TXDR) = tx_data;
#endif /* __GNUC__ */
}

/**
  * @brief  Write Data Register
  * @rmtoll
  *  TXDR         .       LL_SPI_TransmitData32
  * @param  p_spix SPI Instance
  * @param  tx_data 0..0xFFFFFFFF
  */
__STATIC_INLINE void LL_SPI_TransmitData32(SPI_TypeDef *p_spix, uint32_t tx_data)
{
  *((__IO uint32_t *)&p_spix->TXDR) = tx_data;
}

/**
  * @brief  Set polynomial for CRC calcul
  * @rmtoll
  *  CRCPOLY      CRCPOLY       LL_SPI_SetCRCPolynomial
  * @param  p_spix SPI Instance
  * @param  crc_poly 0..0xFFFFFFFF
  */
__STATIC_INLINE void LL_SPI_SetCRCPolynomial(SPI_TypeDef *p_spix, uint32_t crc_poly)
{
  WRITE_REG(p_spix->CRCPOLY, crc_poly);
}

/**
  * @brief  Get polynomial for CRC calcul
  * @rmtoll
  *  CRCPOLY      CRCPOLY       LL_SPI_GetCRCPolynomial
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCPolynomial(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_REG(p_spix->CRCPOLY));
}

/**
  * @brief  Set the underrun pattern
  * @rmtoll
  *  UDRDR        UDRDR         LL_SPI_SetUDRPattern
  * @param  p_spix SPI Instance
  * @param  pattern 0..0xFFFFFFFF
  */
__STATIC_INLINE void LL_SPI_SetUDRPattern(SPI_TypeDef *p_spix, uint32_t pattern)
{
  WRITE_REG(p_spix->UDRDR, pattern);
}

/**
  * @brief  Get the underrun pattern
  * @rmtoll
  *  UDRDR        UDRDR         LL_SPI_GetUDRPattern
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetUDRPattern(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_REG(p_spix->UDRDR));
}

/**
  * @brief  Get Rx CRC
  * @rmtoll
  *  RXCRC       RXCRC         LL_SPI_GetRxCRC
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxCRC(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_REG(p_spix->RXCRC));
}

/**
  * @brief  Get Tx CRC
  * @rmtoll
  *  TXCRC       TXCRC         LL_SPI_GetTxCRC
  * @param  p_spix SPI Instance
  * @retval 0..0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxCRC(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_REG(p_spix->TXCRC));
}

/**
  * @}
  */

/** @defgroup SPI_LL_AutonomousMode Configuration functions related to Autonomous mode feature
  * @{
  */

/**
  * @brief  Enable Selected Trigger
  * @rmtoll
  *  AUTOCR          TRIGEN          LL_SPI_Enable_SelectedTrigger
  * @param  p_spix SPI Instance.
  */
__STATIC_INLINE void LL_SPI_Enable_SelectedTrigger(SPI_TypeDef *p_spix)
{
  SET_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGEN);
}

/**
  * @brief  Disable Selected Trigger
  * @rmtoll
  *  AUTOCR          TRIGEN          LL_SPI_Disable_SelectedTrigger
  * @param  p_spix SPI Instance.
  */
__STATIC_INLINE void LL_SPI_Disable_SelectedTrigger(SPI_TypeDef *p_spix)
{
  CLEAR_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGEN);
}

/**
  * @brief  Indicate if selected Trigger is disabled or enabled
  * @rmtoll
  *  AUTOCR          TRIGEN          LL_SPI_IsEnabled_SelectedTrigger
  * @param  p_spix SPI Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabled_SelectedTrigger(const SPI_TypeDef *p_spix)
{
  return ((READ_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGEN) == (SPI_AUTOCR_TRIGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the trigger polarity
  * @rmtoll
  *  AUTOCR        TRIGPOL     LL_SPI_SetTriggerPolarity
  * @param  p_spix SPI Instance.
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_AM_TRIG_RISING
  *         @arg @ref LL_SPI_AM_TRIG_FALLING
  */
__STATIC_INLINE void LL_SPI_SetTriggerPolarity(SPI_TypeDef *p_spix, uint32_t polarity)
{
  MODIFY_REG(p_spix->AUTOCR, SPI_AUTOCR_TRIGPOL, polarity);
}

/**
  * @brief  Get the trigger polarity
  * @rmtoll
  *  AUTOCR        TRIGPOL     LL_SPI_GetTriggerPolarity
  * @param  p_spix SPI Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_AM_TRIG_RISING
  *         @arg @ref LL_SPI_AM_TRIG_FALLING
  */
__STATIC_INLINE uint32_t LL_SPI_GetTriggerPolarity(const SPI_TypeDef *p_spix)
{
  return (uint32_t)(READ_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGPOL));
}

/**
  * @brief  Set the selected trigger
  * @rmtoll
  *  AUTOCR        TRIGSEL     LL_SPI_SetSelectedTrigger
  * @param  p_spix SPI Instance.
  * @param  Trigger This parameter can be one of the following values:
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH0_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH1_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH2_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH3_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_EXTI4
  *         @arg @ref  LL_SPI_TRIG_GRP1_EXTI9
  *         @arg @ref  LL_SPI_TRIG_GRP1_LPTIM1_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP1_LPTIM2_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP1_COMP1_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP1_COMP2_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP1_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_TRIG_GRP1_RTC_WUT_TRG
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH0_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH1_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH2_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH3_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_EXTI4
  *         @arg @ref  LL_SPI_TRIG_GRP2_EXTI8
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPTIM1_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPTIM3_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP2_COMP1_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP2_COMP2_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP2_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_TRIG_GRP2_RTC_WUT_TRG
  */
__STATIC_INLINE void LL_SPI_SetSelectedTrigger(SPI_TypeDef *p_spix, uint32_t trigger)
{
  MODIFY_REG(p_spix->AUTOCR, SPI_AUTOCR_TRIGSEL, (trigger & SPI_AUTOCR_TRIGSEL_Msk));
}

/**
  * @brief  Get the selected trigger
  * @rmtoll
  *  AUTOCR        TRIGSEL     LL_SPI_GetSelectedTrigger
  * @param  p_spix SPI Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH0_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH1_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH2_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_GPDMA1_CH3_TC
  *         @arg @ref  LL_SPI_TRIG_GRP1_EXTI4
  *         @arg @ref  LL_SPI_TRIG_GRP1_EXTI9
  *         @arg @ref  LL_SPI_TRIG_GRP1_LPTIM1_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP1_LPTIM2_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP1_COMP1_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP1_COMP2_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP1_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_TRIG_GRP1_RTC_WUT_TRG
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH0_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH1_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH2_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPDMA1_CH3_TC
  *         @arg @ref  LL_SPI_TRIG_GRP2_EXTI4
  *         @arg @ref  LL_SPI_TRIG_GRP2_EXTI8
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPTIM1_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP2_LPTIM3_CH1
  *         @arg @ref  LL_SPI_TRIG_GRP2_COMP1_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP2_COMP2_OUT
  *         @arg @ref  LL_SPI_TRIG_GRP2_RTC_ALRA_TRG
  *         @arg @ref  LL_SPI_TRIG_GRP2_RTC_WUT_TRG
  */
__STATIC_INLINE uint32_t LL_SPI_GetSelectedTrigger(const SPI_TypeDef *p_spix)
{
#if defined(LL_SPI_TRIG_GRP2)
  if (IS_LL_SPI_GRP2_INSTANCE(p_spix))
  {
    return (uint32_t)((READ_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGSEL) | LL_SPI_TRIG_GRP2));
  }
  else
  {
    return (uint32_t)((READ_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGSEL) | LL_SPI_TRIG_GRP1));
  }
#else
  return (uint32_t)((READ_BIT(p_spix->AUTOCR, SPI_AUTOCR_TRIGSEL) | LL_SPI_TRIG_GRP1));
#endif /* LL_SPI_TRIG_GRP2 */
}

/**
  * @brief  Set the trigger polarity
  * @rmtoll
  *  AUTOCR        TRIGPOL |TRIGSEL      LL_SPI_SetAutonomousConfig
  * @param  p_spix SPI Instance.
  * @param  autonomous_config This parameter must be a combination of trigger polarity and trigger source from
  *                           the following groups:
  *         @arg @ref SPI_LL_EC_AUTOCR_TRIGPOL
  *         @arg @ref SPI_LL_EC_AUTOCR_TRIGSEL
  */
__STATIC_INLINE void LL_SPI_SetAutonomousConfig(SPI_TypeDef *p_spix, uint32_t autonomous_config)
{
  MODIFY_REG(p_spix->AUTOCR, SPI_AUTOCR_TRIGPOL | SPI_AUTOCR_TRIGSEL, autonomous_config);
}

/**
  * @}
  */

/**
  * @}
  */


#endif /* defined(SPI1) || defined(SPI2) || defined(SPI3) */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_LL_SPI_H */
