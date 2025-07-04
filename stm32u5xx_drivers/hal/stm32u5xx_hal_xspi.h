/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_xspi.h
  * @brief   Header file of XSPI HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_XSPI_H
#define STM32U5XX_HAL_XSPI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

#if defined(HSPI1) || defined(OCTOSPI1)|| defined(OCTOSPI2)

#include "stm32u5xx_dlyb_core.h"
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
#include "stm32u5xx_otfdec_core.h"
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup XSPI XSPI
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup XSPI_Exported_Constants XSPI Exported Constants
  * @{
  */

#if defined(XSPIM)
/** @defgroup XSPI_Mask XSPI Mask definition
  * @{
  */
#define HAL_XSPI_XSPIM_MUX_MASK_POS 31U                                  /*!< XSPI XSPIM mux mask position */
#define HAL_XSPI_XSPIM_MUX_MASK     (1UL << HAL_XSPI_XSPIM_MUX_MASK_POS) /*!< XSPI XSPIM mux mask          */
/**
  * @}
  */
#endif /* XSPIM */

/** @defgroup XSPI_Flag Flags
  * @{
  */
#define HAL_XSPI_FLAG_BUSY XSPI_SR_BUSY                                                        /*!< Busy flag: operation is ongoing                                                                          */
#define HAL_XSPI_FLAG_TO   XSPI_SR_TOF                                                         /*!< Timeout flag: timeout occurs in memory-mapped mode                                                       */
#define HAL_XSPI_FLAG_SM   XSPI_SR_SMF                                                         /*!< Status match flag: received data matches in autopolling mode                                             */
#define HAL_XSPI_FLAG_FT   XSPI_SR_FTF                                                         /*!< Fifo threshold flag: Fifo threshold reached or data left after read from memory is complete              */
#define HAL_XSPI_FLAG_TC   XSPI_SR_TCF                                                         /*!< Transfer complete flag: programmed number of data have been transferred or the transfer has been aborted */
#define HAL_XSPI_FLAG_TE   XSPI_SR_TEF                                                         /*!< Transfer error flag: invalid address is being accessed                                                   */
#define HAL_XSPI_FLAG_ALL  XSPI_SR_TOF | XSPI_SR_SMF | XSPI_SR_FTF | XSPI_SR_TCF | XSPI_SR_TEF /*!< All flags                                                                                                */
/**
  * @}
  */

/** @defgroup XSPI_Interrupts Interrupts
  * @{
  */
#define HAL_XSPI_IT_TO  XSPI_CR_TOIE                                                             /*!< Interrupt on the timeout flag           */
#define HAL_XSPI_IT_SM  XSPI_CR_SMIE                                                             /*!< Interrupt on the status match flag      */
#define HAL_XSPI_IT_FT  XSPI_CR_FTIE                                                             /*!< Interrupt on the fifo threshold flag    */
#define HAL_XSPI_IT_TC  XSPI_CR_TCIE                                                             /*!< Interrupt on the transfer complete flag */
#define HAL_XSPI_IT_TE  XSPI_CR_TEIE                                                             /*!< Interrupt on the transfer error flag    */
#define HAL_XSPI_IT_ALL XSPI_CR_TOIE | XSPI_CR_SMIE | XSPI_CR_FTIE | XSPI_CR_TCIE | XSPI_CR_TEIE /*!< All Interrupts                          */
/**
  * @}
  */

/** @defgroup XSPI_Optional_Interrupt Optional interrupts
  * @{
  */
#define HAL_XSPI_OPT_IT_NONE    HAL_DMA_OPT_IT_NONE    /*!< DMA channel optional interrupts disabled    */
#define HAL_XSPI_OPT_IT_HT      HAL_DMA_OPT_IT_HT      /*!< DMA channel half transfer interrupt enabled */
#define HAL_XSPI_OPT_IT_DEFAULT HAL_DMA_OPT_IT_DEFAULT /*!< DMA channel all optional interrupts enabled */
/**
  * @}
  */
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
/** @defgroup XSPI_OTFDEC_Interrupts OTFDEC interrupts
  * @{
  */
#define HAL_XSPI_OTFDEC_IT_NONE                       OTFDEC_IT_NONE                       /*!< OTFDEC all interrupts  disabled          */
#define HAL_XSPI_OTFDEC_IT_KEY_ERROR                  OTFDEC_IT_KEY_ERROR                  /*!< OTFDEC key error interrupt enabled       */
#define HAL_XSPI_OTFDEC_IT_SECURITY_ERROR             OTFDEC_IT_SECURITY_ERROR             /*!< OTFDEC security error interrupt enabled  */
#define HAL_XSPI_OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR /*!< OTFDEC execute-only execute-never error  */
#define HAL_XSPI_OTFDEC_IT_ALL                        OTFDEC_IT_ALL                        /*!< OTFDEC all interrupts  enabled           */
/**
  * @}
  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

/** @defgroup XSPI_Error_Code Error Code definition reflecting the processes asynchronous errors
  * @{
  */
#if (defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1))
#define HAL_XSPI_ERROR_NONE      (0x00UL << 0U) /*!< XSPI error none     */
#define HAL_XSPI_ERROR_TRANSFER  (0x01UL << 0U) /*!< XSPI transfer error */
#define HAL_XSPI_ERROR_TIMEOUT   (0x01UL << 2U) /*!< XSPI timeout error  */
#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
#define HAL_XSPI_ERROR_DMA       (0x01UL << 1U) /*!< DMA transfer error  */
#endif /* USE_HAL_XSPI_DMA */
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
/** @defgroup XSPI_OTFDEC_Error_Code OTFDEC Error Code definition reflecting the processes asynchronous errors
  * @{
  */
#if (defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1))
#define HAL_XSPI_ERROR_OTFDEC_NONE                 0UL               /*!< OTFDEC error none                       */
#define HAL_XSPI_ERROR_OTFDEC_KEY                  OTFDEC_ISR_KEIF   /*!< OTFDEC key error                        */
#define HAL_XSPI_ERROR_OTFDEC_SECURITY             OTFDEC_ISR_SEIF   /*!< OTFDEC security error                   */
#define HAL_XSPI_ERROR_OTFDEC_EXEC_ONLY_EXEC_NEVER OTFDEC_ISR_XONEIF /*!< OTFDEC execute only execute never error */
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
/**
  * @}
  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
/** @defgroup XSPI_OTFDEC_Exported_Types XSPI OTFDEC Exported Types
  * @{
  */

/**
  * @brief XSPI OTFDEC region state
  */
typedef enum
{
  HAL_XSPI_OTFDEC_REGION_STATE_RESET      = (1UL  << 31U), /*!< XSPI OTFDEC region reset state           */
  HAL_XSPI_OTFDEC_REGION_STATE_CONFIGURED = (1UL  << 30U), /*!< XSPI OTFDEC region configured            */
  HAL_XSPI_OTFDEC_REGION_STATE_DECRYPT    = (1UL  << 29U)  /*!< XSPI OTFDEC region decryption state      */
} hal_xspi_otfdec_region_state_t;

/**
  * @brief OTFDEC region index
  */
typedef enum
{
  HAL_XSPI_OTFDEC_REGION_1 = 0U, /*!< OTFDEC region index 1 */
  HAL_XSPI_OTFDEC_REGION_2 = 1UL, /*!< OTFDEC region index 2 */
  HAL_XSPI_OTFDEC_REGION_3 = 2UL, /*!< OTFDEC region index 3 */
  HAL_XSPI_OTFDEC_REGION_4 = 3UL  /*!< OTFDEC region index 4 */
} hal_xspi_otfdec_region_t;

/**
  * @brief OTFDEC operation mode
  */
typedef enum
{
  HAL_XSPI_OTFDEC_MODE_ALL_READ_ACCESS     = OTFDEC_MODE_ALL_READ_ACCESS,    /*!< OTFDEC all read access mode         */
  HAL_XSPI_OTFDEC_MODE_ENHANCED_ENCRYPTION = OTFDEC_MODE_ENHANCED_ENCRYPTION /*!< OTFDEC enhanced encryption mode     */
} hal_xspi_otfdec_mode_t;

/**
  * @brief OTFDEC region lock configuration status
  */
typedef enum
{
  HAL_XSPI_OTFDEC_LOCK_CONFIG_ENABLED  = OTFDEC_LOCK_CONFIG_ENABLED, /*!< OTFDEC lock configuration enabled  */
  HAL_XSPI_OTFDEC_LOCK_CONFIG_DISABLED = OTFDEC_LOCK_CONFIG_DISABLED /*!< OTFDEC lock configuration disabled */
} hal_xspi_otfdec_lock_config_status_t;

/**
  * @brief OTFDEC key lock configuration status
  */
typedef enum
{
  HAL_XSPI_OTFDEC_LOCK_KEY_ENABLED  = OTFDEC_REG_CONFIGR_KEYLOCK, /*!< OTFDEC lock key enabled  */
  HAL_XSPI_OTFDEC_LOCK_KEY_DISABLED = 0x00000000U                 /*!< OTFDEC lock key disabled */
} hal_xspi_otfdec_lock_key_status_t;

/**
  * @brief OTFDEC privilege configuration attributes
  */
typedef enum
{
  HAL_XSPI_OTFDEC_ATTRIBUTE_NON_PRIVILEGED = 0x00000000U,          /*!< OTFDEC non-privileged access protection  */
  HAL_XSPI_OTFDEC_ATTRIBUTE_PRIVILEGED     = OTFDEC_PRIVCFGR_PRIV  /*!< OTFDEC privileged access protection      */
} hal_xspi_otfdec_privilege_attr_t;

/**
  * @brief OTFDEC key size
  */
typedef enum
{
  HAL_XSPI_OTFDEC_KEY_SIZE_128BIT                                  /*!< OTFDEC 128-bit key size                   */
} hal_xspi_otfdec_keysize_t;

/**
  * @brief OTFDEC key configuration
  */
typedef struct
{
  uint8_t                  *p_key;             /*!< OTFDEC key value   */
  hal_xspi_otfdec_keysize_t key_size_byte;     /*!< OTFDEC key size    */
} hal_xspi_otfdec_key_t;

/**
  * @brief OTFDEC globale configuration
  */
typedef struct
{
  uint32_t               start_address;   /*!< OTFDEC region start address    */
  uint32_t               end_address;     /*!< OTFDEC region end address      */
  uint32_t               nonce[2];        /*!< OTFDEC region nonce            */
  uint16_t               version;         /*!< OTFDEC region firmware version */
  hal_xspi_otfdec_mode_t mode;            /*!< OTFDEC region mode             */
} hal_xspi_otfdec_config_t;
/**
  * @}
  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

/** @defgroup XSPI_Exported_Types XSPI Exported Types
  * @{
  */

/**
  * @brief HAL XSPI instance enumeration definition
  */
typedef enum
{
  HAL_OCTOSPI1 = (uint32_t)OCTOSPI1, /*!< HAL OCTOSPI instance 1 */
#if defined(OCTOSPI2)
  HAL_OCTOSPI2 = (uint32_t)OCTOSPI2, /*!< HAL OCTOSPI instance 2 */
#endif /* OCTOSPI2 */
#if defined(HSPI1)
  HAL_HSPI1    = (uint32_t)HSPI1     /*!< HAL HSPI instance 1    */
#endif /* HSPI1 */
} hal_xspi_t;

/**
  * @brief HAL XSPI state enumeration definition
  */
typedef enum
{
  HAL_XSPI_STATE_RESET                = 0x00U,        /*!< Reset state                                  */
  HAL_XSPI_STATE_INIT                 = (1U  << 31U), /*!< XSPI is initialized but not yet configured   */
  HAL_XSPI_STATE_IDLE                 = (1U  << 30U), /*!< XSPI initialized and a global config applied */
  HAL_XSPI_STATE_CMD_ACTIVE           = (1U  << 29U), /*!< Command on-going                             */
  HAL_XSPI_STATE_AUTO_POLLING_ACTIVE  = (1U  << 28U), /*!< Auto-polling on-going                        */
  HAL_XSPI_STATE_TX_ACTIVE            = (1U  << 27U), /*!< Indirect Tx on-going                         */
  HAL_XSPI_STATE_RX_ACTIVE            = (1U  << 26U), /*!< Indirect Rx on-going                         */
  HAL_XSPI_STATE_MEMORY_MAPPED_ACTIVE = (1U  << 25U), /*!< Memory-mapped on-going                       */
  HAL_XSPI_STATE_ABORT                = (1U  << 24U), /*!< Abort on-going                               */
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
  HAL_XSPI_OTFDEC_STATE_ENCRYPT       = (1UL  << 23U)  /*!< XSPI OTFDEC encryption is ongoing            */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
} hal_xspi_state_t;

/**
  * @brief HAL XSPI DLYB State
  */
typedef enum
{
  HAL_XSPI_DLYB_DISABLED = DLYB_DISABLED, /*!< XSPI DLYB disabled */
  HAL_XSPI_DLYB_ENABLED  = DLYB_ENABLED   /*!< XSPI DLYB enabled  */
} hal_xspi_dlyb_status_t;

/**
  * @brief HAL XSPI flag state enumeration definition
  */
typedef enum
{
  HAL_XSPI_FLAG_NOT_ACTIVE = 0x00U,   /*!< Flag not active */
  HAL_XSPI_FLAG_ACTIVE                /*!< Flag active     */
} hal_xspi_flag_status_t;

/**
  * @brief HAL XSPI Memory Mode
  */
typedef enum
{
  HAL_XSPI_MEMORY_SINGLE = 0x00U,       /*!< Dual memory mode disabled */
  HAL_XSPI_MEMORY_DUAL   = XSPI_CR_DMM  /*!< Dual memory mode enabled  */
} hal_xspi_memory_mode_t;

/**
  * @brief HAL XSPI Memory Type
  */
typedef enum
{
  HAL_XSPI_MEMORY_TYPE_MICRON       = 0x00U,                                 /*!< Micron mode       */
  HAL_XSPI_MEMORY_TYPE_MACRONIX     = XSPI_DCR1_MTYP_0,                      /*!< Macronix mode     */
  HAL_XSPI_MEMORY_TYPE_APMEM        = XSPI_DCR1_MTYP_1,                      /*!< AP Memory mode    */
  HAL_XSPI_MEMORY_TYPE_MACRONIX_RAM = (XSPI_DCR1_MTYP_1 | XSPI_DCR1_MTYP_0), /*!< Macronix RAM mode */
  HAL_XSPI_MEMORY_TYPE_HYPERBUS     = XSPI_DCR1_MTYP_2,                      /*!< Hyperbus mode     */
  HAL_XSPI_MEMORY_TYPE_APMEM_16BIT  = (XSPI_DCR1_MTYP_2 | XSPI_DCR1_MTYP_1)  /*!< AP Memory mode    */
} hal_xspi_memory_type_t;

/**
  * @brief HAL XSPI Memory Size
  */
typedef enum
{
  HAL_XSPI_MEMORY_SIZE_16BIT   = (0x00U << XSPI_DCR1_DEVSIZE_Pos), /*!<  16 bits  (  2  Bytes = 2^( 0+1)) */
  HAL_XSPI_MEMORY_SIZE_32BIT   = (0x01U << XSPI_DCR1_DEVSIZE_Pos), /*!<  32 bits  (  4  Bytes = 2^( 1+1)) */
  HAL_XSPI_MEMORY_SIZE_64BIT   = (0x02U << XSPI_DCR1_DEVSIZE_Pos), /*!<  64 bits  (  8  Bytes = 2^( 2+1)) */
  HAL_XSPI_MEMORY_SIZE_128BIT  = (0x03U << XSPI_DCR1_DEVSIZE_Pos), /*!< 128 bits  ( 16  Bytes = 2^( 3+1)) */
  HAL_XSPI_MEMORY_SIZE_256BIT  = (0x04U << XSPI_DCR1_DEVSIZE_Pos), /*!< 256 bits  ( 32  Bytes = 2^( 4+1)) */
  HAL_XSPI_MEMORY_SIZE_512BIT  = (0x05U << XSPI_DCR1_DEVSIZE_Pos), /*!< 512 bits  ( 64  Bytes = 2^( 5+1)) */
  HAL_XSPI_MEMORY_SIZE_1KBIT   = (0x06U << XSPI_DCR1_DEVSIZE_Pos), /*!<   1 Kbits (128  Bytes = 2^( 6+1)) */
  HAL_XSPI_MEMORY_SIZE_2KBIT   = (0x07U << XSPI_DCR1_DEVSIZE_Pos), /*!<   2 Kbits (256  Bytes = 2^( 7+1)) */
  HAL_XSPI_MEMORY_SIZE_4KBIT   = (0x08U << XSPI_DCR1_DEVSIZE_Pos), /*!<   4 Kbits (512  Bytes = 2^( 8+1)) */
  HAL_XSPI_MEMORY_SIZE_8KBIT   = (0x09U << XSPI_DCR1_DEVSIZE_Pos), /*!<   8 Kbits (  1 KBytes = 2^( 9+1)) */
  HAL_XSPI_MEMORY_SIZE_16KBIT  = (0x0AU << XSPI_DCR1_DEVSIZE_Pos), /*!<  16 Kbits (  2 KBytes = 2^(10+1)) */
  HAL_XSPI_MEMORY_SIZE_32KBIT  = (0x0BU << XSPI_DCR1_DEVSIZE_Pos), /*!<  32 Kbits (  4 KBytes = 2^(11+1)) */
  HAL_XSPI_MEMORY_SIZE_64KBIT  = (0x0CU << XSPI_DCR1_DEVSIZE_Pos), /*!<  64 Kbits (  8 KBytes = 2^(12+1)) */
  HAL_XSPI_MEMORY_SIZE_128KBIT = (0x0DU << XSPI_DCR1_DEVSIZE_Pos), /*!< 128 Kbits ( 16 KBytes = 2^(13+1)) */
  HAL_XSPI_MEMORY_SIZE_256KBIT = (0x0EU << XSPI_DCR1_DEVSIZE_Pos), /*!< 256 Kbits ( 32 KBytes = 2^(14+1)) */
  HAL_XSPI_MEMORY_SIZE_512KBIT = (0x0FU << XSPI_DCR1_DEVSIZE_Pos), /*!< 512 Kbits ( 64 KBytes = 2^(15+1)) */
  HAL_XSPI_MEMORY_SIZE_1MBIT   = (0x10U << XSPI_DCR1_DEVSIZE_Pos), /*!<   1 Mbits (128 KBytes = 2^(16+1)) */
  HAL_XSPI_MEMORY_SIZE_2MBIT   = (0x11U << XSPI_DCR1_DEVSIZE_Pos), /*!<   2 Mbits (256 KBytes = 2^(17+1)) */
  HAL_XSPI_MEMORY_SIZE_4MBIT   = (0x12U << XSPI_DCR1_DEVSIZE_Pos), /*!<   4 Mbits (512 KBytes = 2^(18+1)) */
  HAL_XSPI_MEMORY_SIZE_8MBIT   = (0x13U << XSPI_DCR1_DEVSIZE_Pos), /*!<   8 Mbits (  1 MBytes = 2^(19+1)) */
  HAL_XSPI_MEMORY_SIZE_16MBIT  = (0x14U << XSPI_DCR1_DEVSIZE_Pos), /*!<  16 Mbits (  2 MBytes = 2^(20+1)) */
  HAL_XSPI_MEMORY_SIZE_32MBIT  = (0x15U << XSPI_DCR1_DEVSIZE_Pos), /*!<  32 Mbits (  4 MBytes = 2^(21+1)) */
  HAL_XSPI_MEMORY_SIZE_64MBIT  = (0x16U << XSPI_DCR1_DEVSIZE_Pos), /*!<  64 Mbits (  8 MBytes = 2^(22+1)) */
  HAL_XSPI_MEMORY_SIZE_128MBIT = (0x17U << XSPI_DCR1_DEVSIZE_Pos), /*!< 128 Mbits ( 16 MBytes = 2^(23+1)) */
  HAL_XSPI_MEMORY_SIZE_256MBIT = (0x18U << XSPI_DCR1_DEVSIZE_Pos), /*!< 256 Mbits ( 32 MBytes = 2^(24+1)) */
  HAL_XSPI_MEMORY_SIZE_512MBIT = (0x19U << XSPI_DCR1_DEVSIZE_Pos), /*!< 512 Mbits ( 64 MBytes = 2^(25+1)) */
  HAL_XSPI_MEMORY_SIZE_1GBIT   = (0x1AU << XSPI_DCR1_DEVSIZE_Pos), /*!<   1 Gbits (128 MBytes = 2^(26+1)) */
  HAL_XSPI_MEMORY_SIZE_2GBIT   = (0x1BU << XSPI_DCR1_DEVSIZE_Pos), /*!<   2 Gbits (256 MBytes = 2^(27+1)) */
  HAL_XSPI_MEMORY_SIZE_4GBIT   = (0x1CU << XSPI_DCR1_DEVSIZE_Pos), /*!<   4 Gbits (512 MBytes = 2^(28+1)) */
  HAL_XSPI_MEMORY_SIZE_8GBIT   = (0x1DU << XSPI_DCR1_DEVSIZE_Pos), /*!<   8 Gbits (  1 GBytes = 2^(29+1)) */
  HAL_XSPI_MEMORY_SIZE_16GBIT  = (0x1EU << XSPI_DCR1_DEVSIZE_Pos), /*!<  16 Gbits (  2 GBytes = 2^(30+1)) */
  HAL_XSPI_MEMORY_SIZE_32GBIT  = (0x1FU << XSPI_DCR1_DEVSIZE_Pos)  /*!<  32 Gbits (  4 GBytes = 2^(31+1)) */
} hal_xspi_memory_size_t;

/**
  * @brief HAL XSPI Free Running Clock
  */
typedef enum
{
  HAL_XSPI_FREE_RUNNING_CLK_DISABLED = 0x00U,         /*!< CLK is not free running          */
  HAL_XSPI_FREE_RUNNING_CLK_ENABLED  = XSPI_DCR1_FRCK /*!< CLK is always provided (running) */
} hal_xspi_free_running_clk_status_t;

/**
  * @brief HAL XSPI SIOO Mode
  */
typedef enum
{
  HAL_XSPI_SIOO_DISABLED = 0x00U,            /*!< In memory-mapped mode, XSPI send instruction on every transaction       */
  HAL_XSPI_SIOO_ENABLED  = XSPI_CCR_SIOO     /*!< In memory-mapped mode, XSPI send instruction only for the first command */
} hal_xspi_sioo_status_t;

/**
  * @brief HAL XSPI Clock Polarity
  */
typedef enum
{
  HAL_XSPI_CLOCK_LOW  = 0x00U,           /*!< Clock must stay low while nCS is high  */
  HAL_XSPI_CLOCK_HIGH = XSPI_DCR1_CKMODE /*!< Clock must stay high while nCS is high */
} hal_xspi_clock_polarity_t;

/**
  * @brief HAL XSPI Wrap Size
  */
typedef enum
{
  HAL_XSPI_WRAP_NOT_SUPPORTED = 0x00U,                                         /*!< wrapped reads are not supported by the memory   */
  HAL_XSPI_WRAP_16BYTE        = XSPI_DCR2_WRAPSIZE_1,                          /*!< external memory supports wrap size of 16 bytes  */
  HAL_XSPI_WRAP_32BYTE        = (XSPI_DCR2_WRAPSIZE_0 | XSPI_DCR2_WRAPSIZE_1), /*!< external memory supports wrap size of 32 bytes  */
  HAL_XSPI_WRAP_64BYTE        = XSPI_DCR2_WRAPSIZE_2,                          /*!< external memory supports wrap size of 64 bytes  */
  HAL_XSPI_WRAP_128BYTE       = (XSPI_DCR2_WRAPSIZE_0 | XSPI_DCR2_WRAPSIZE_2)  /*!< external memory supports wrap size of 128 bytes */
} hal_xspi_wrap_size_t;

/**
  * @brief HAL XSPI Sample Shift
  */
typedef enum
{
  HAL_XSPI_SAMPLE_SHIFT_NONE      = 0x00U,          /*!< No shift        */
  HAL_XSPI_SAMPLE_SHIFT_HALFCYCLE = XSPI_TCR_SSHIFT /*!< 1/2 cycle shift */
} hal_xspi_sample_shift_t;

/**
  * @brief HAL XSPI Delay Hold Quarter Cycle
  */
typedef enum
{
  HAL_XSPI_DELAY_HOLD_NONE       = 0x00U,        /*!< No Delay             */
  HAL_XSPI_DELAY_HOLD_QUARTCYCLE = XSPI_TCR_DHQC /*!< Delay Hold 1/4 cycle */
} hal_xspi_delay_hold_t;

/**
  * @brief HAL XSPI Chip Select Boundary
  */
typedef enum
{
  HAL_XSPI_CS_BOUNDARY_NONE    = 0x00U, /*!< CS boundary disabled           */
  HAL_XSPI_CS_BOUNDARY_16BIT   = 0x01U, /*!<  16 bits  (  2  Bytes = 2^(1))  */
  HAL_XSPI_CS_BOUNDARY_32BIT   = 0x02U, /*!<  32 bits  (  4  Bytes = 2^(2))  */
  HAL_XSPI_CS_BOUNDARY_64BIT   = 0x03U, /*!<  64 bits  (  8  Bytes = 2^(3))  */
  HAL_XSPI_CS_BOUNDARY_128BIT  = 0x04U, /*!< 128 bits  ( 16  Bytes = 2^(4))  */
  HAL_XSPI_CS_BOUNDARY_256BIT  = 0x05U, /*!< 256 bits  ( 32  Bytes = 2^(5))  */
  HAL_XSPI_CS_BOUNDARY_512BIT  = 0x06U, /*!< 512 bits  ( 64  Bytes = 2^(6))  */
  HAL_XSPI_CS_BOUNDARY_1KBIT   = 0x07U, /*!<   1 Kbits (128  Bytes = 2^(7))  */
  HAL_XSPI_CS_BOUNDARY_2KBIT   = 0x08U, /*!<   2 Kbits (256  Bytes = 2^(8))  */
  HAL_XSPI_CS_BOUNDARY_4KBIT   = 0x09U, /*!<   4 Kbits (512  Bytes = 2^(9))  */
  HAL_XSPI_CS_BOUNDARY_8KBIT   = 0x0AU, /*!<   8 Kbits (  1 KBytes = 2^(10)) */
  HAL_XSPI_CS_BOUNDARY_16KBIT  = 0x0BU, /*!<  16 Kbits (  2 KBytes = 2^(11)) */
  HAL_XSPI_CS_BOUNDARY_32KBIT  = 0x0CU, /*!<  32 Kbits (  4 KBytes = 2^(12)) */
  HAL_XSPI_CS_BOUNDARY_64KBIT  = 0x0DU, /*!< 64 Kbits  (  8 KBytes = 2^(13)) */
  HAL_XSPI_CS_BOUNDARY_128KBIT = 0x0EU, /*!< 128 Kbits ( 16 KBytes = 2^(14)) */
  HAL_XSPI_CS_BOUNDARY_256KBIT = 0x0FU, /*!< 256 Kbits ( 32 KBytes = 2^(15)) */
  HAL_XSPI_CS_BOUNDARY_512KBIT = 0x10U, /*!< 512 Kbits ( 64 KBytes = 2^(16)) */
  HAL_XSPI_CS_BOUNDARY_1MBIT   = 0x11U, /*!<   1 Mbits (128 KBytes = 2^(17)) */
  HAL_XSPI_CS_BOUNDARY_2MBIT   = 0x12U, /*!<   2 Mbits (256 KBytes = 2^(18)) */
  HAL_XSPI_CS_BOUNDARY_4MBIT   = 0x13U, /*!<   4 Mbits (512 KBytes = 2^(19)) */
  HAL_XSPI_CS_BOUNDARY_8MBIT   = 0x14U, /*!<   8 Mbits (  1 MBytes = 2^(20)) */
  HAL_XSPI_CS_BOUNDARY_16MBIT  = 0x15U, /*!<  16 Mbits (  2 MBytes = 2^(21)) */
  HAL_XSPI_CS_BOUNDARY_32MBIT  = 0x16U, /*!<  32 Mbits (  4 MBytes = 2^(22)) */
  HAL_XSPI_CS_BOUNDARY_64MBIT  = 0x17U, /*!<  64 Mbits (  8 MBytes = 2^(23)) */
  HAL_XSPI_CS_BOUNDARY_128MBIT = 0x18U, /*!< 128 Mbits ( 16 MBytes = 2^(24)) */
  HAL_XSPI_CS_BOUNDARY_256MBIT = 0x19U, /*!< 256 Mbits ( 32 MBytes = 2^(25)) */
  HAL_XSPI_CS_BOUNDARY_512MBIT = 0x1AU, /*!< 512 Mbits ( 64 MBytes = 2^(26)) */
  HAL_XSPI_CS_BOUNDARY_1GBIT   = 0x1BU, /*!<   1 Gbits (128 MBytes = 2^(27)) */
  HAL_XSPI_CS_BOUNDARY_2GBIT   = 0x1CU, /*!<   2 Gbits (256 MBytes = 2^(28)) */
  HAL_XSPI_CS_BOUNDARY_4GBIT   = 0x1DU, /*!<   4 Gbits (512 MBytes = 2^(29)) */
  HAL_XSPI_CS_BOUNDARY_8GBIT   = 0x1EU, /*!<   8 Gbits (  1 GBytes = 2^(30)) */
  HAL_XSPI_CS_BOUNDARY_16GBIT  = 0x1FU  /*!<  16 Gbits (  2 GBytes = 2^(31)) */
} hal_xspi_cs_boundary_t;

/**
  * @brief HAL XSPI Delay Block Bypass
  */
typedef enum
{
  HAL_XSPI_DLYB_ON     = 0x00U,              /*!< Sampling clock is delayed by the delay block */
  HAL_XSPI_DLYB_BYPASS = XSPI_DCR1_DLYBYP    /*!< Delay block is bypassed                      */
} hal_xspi_dlyb_state_t;

/**
  * @brief HAL XSPI Operation Type
  */
typedef enum
{
  HAL_XSPI_OPERATION_COMMON_CFG = 0x00U, /*!< Common configuration (indirect or auto-polling mode) */
  HAL_XSPI_OPERATION_READ_CFG   = 0x00U, /*!< Read configuration (memory-mapped mode)              */
  HAL_XSPI_OPERATION_WRITE_CFG  = 0x80U, /*!< Write configuration (memory-mapped mode)             */
  HAL_XSPI_OPERATION_WRAP_CFG   = 0x40U  /*!< Wrap configuration (memory-mapped mode)              */
} hal_xspi_operation_type_t;

/**
  * @brief HAL XSPI IO Select
  */
typedef enum
{
  HAL_XSPI_IO_3_0   = 0x00U,                            /*!< Data exchanged over IO[3:0]   */
#if defined(XSPI_CR_MSEL)
  HAL_XSPI_IO_7_4   = XSPI_CR_MSEL_0 | XSPI_CR_FSEL,    /*!< Data exchanged over IO[7:4]   */
  HAL_XSPI_IO_11_8  = XSPI_CR_MSEL_1,                   /*!< Data exchanged over IO[11:8]  */
  HAL_XSPI_IO_15_12 = XSPI_CR_MSEL | XSPI_CR_FSEL,      /*!< Data exchanged over IO[15:12] */
  HAL_XSPI_IO_7_0   = 0x00U,                            /*!< Data exchanged over IO[7:0]   */
  HAL_XSPI_IO_15_8  = XSPI_CR_MSEL_1,                   /*!< Data exchanged over IO[15:8]  */
#else
  HAL_XSPI_IO_7_4   = XSPI_CR_FSEL,                     /*!< Data exchanged over IO[7:4]   */
  HAL_XSPI_IO_7_0   = 0x00U                             /*!< Data exchanged over IO[7:0]   */
#endif /* XSPI_CR_MSEL */
} hal_xspi_io_select_t;

/**
  * @brief HAL XSPI Instruction Mode
  */
typedef enum
{
  HAL_XSPI_INSTRUCTION_NONE   = 0x00U,                                 /*!< No instruction               */
  HAL_XSPI_INSTRUCTION_1LINE  = XSPI_CCR_IMODE_0,                      /*!< Instruction on a single line */
  HAL_XSPI_INSTRUCTION_2LINES = XSPI_CCR_IMODE_1,                      /*!< Instruction on two lines     */
  HAL_XSPI_INSTRUCTION_4LINES = (XSPI_CCR_IMODE_0 | XSPI_CCR_IMODE_1), /*!< Instruction on four lines    */
  HAL_XSPI_INSTRUCTION_8LINES = XSPI_CCR_IMODE_2                       /*!< Instruction on eight lines   */
} hal_xspi_instruction_mode_t;

/**
  * @brief HAL XSPI Instruction Width
  */
typedef enum
{
  HAL_XSPI_INSTRUCTION_8BIT  = 0x00U,            /*!< 8-bit instruction  */
  HAL_XSPI_INSTRUCTION_16BIT = XSPI_CCR_ISIZE_0, /*!< 16-bit instruction */
  HAL_XSPI_INSTRUCTION_24BIT = XSPI_CCR_ISIZE_1, /*!< 24-bit instruction */
  HAL_XSPI_INSTRUCTION_32BIT = XSPI_CCR_ISIZE    /*!< 32-bit instruction */
} hal_xspi_instruction_width_t;

/**
  * @brief HAL XSPI Instruction DTR Mode
  */
typedef enum
{
  HAL_XSPI_INSTRUCTION_DTR_DISABLED = 0x00U,        /*!< DTR mode disabled for instruction phase */
  HAL_XSPI_INSTRUCTION_DTR_ENABLED  = XSPI_CCR_IDTR /*!< DTR mode enabled for instruction phase  */
} hal_xspi_instruction_dtr_status_t;

/**
  * @brief HAL XSPI Address Mode
  */
typedef enum
{
  HAL_XSPI_ADDR_NONE    = 0x00U,                                   /*!< No address               */
  HAL_XSPI_ADDR_1LINE   = XSPI_CCR_ADMODE_0,                       /*!< Address on a single line */
  HAL_XSPI_ADDR_2LINES  = XSPI_CCR_ADMODE_1,                       /*!< Address on two lines     */
  HAL_XSPI_ADDR_4LINES  = (XSPI_CCR_ADMODE_0 | XSPI_CCR_ADMODE_1), /*!< Address on four lines    */
  HAL_XSPI_ADDR_8LINES  = XSPI_CCR_ADMODE_2                        /*!< Address on eight lines   */
} hal_xspi_addr_mode_t;

/**
  * @brief HAL XSPI Address width
  */
typedef enum
{
  HAL_XSPI_ADDR_8BIT  = 0x00U,             /*!< 8-bit address  */
  HAL_XSPI_ADDR_16BIT = XSPI_CCR_ADSIZE_0, /*!< 16-bit address */
  HAL_XSPI_ADDR_24BIT = XSPI_CCR_ADSIZE_1, /*!< 24-bit address */
  HAL_XSPI_ADDR_32BIT = XSPI_CCR_ADSIZE    /*!< 32-bit address */
} hal_xspi_addr_width_t;

/**
  * @brief HAL XSPI Address DTR Mode
  */
typedef enum
{
  HAL_XSPI_ADDR_DTR_DISABLED = 0x00U,         /*!< DTR mode disabled for address phase */
  HAL_XSPI_ADDR_DTR_ENABLED  = XSPI_CCR_ADDTR /*!< DTR mode enabled for address phase  */
} hal_xspi_addr_dtr_status_t;

/**
  * @brief HAL XSPI Alternate Bytes Mode
  */
typedef enum
{
  HAL_XSPI_ALTERNATE_BYTES_NONE   = 0x00U,                                   /*!< No alternate bytes               */
  HAL_XSPI_ALTERNATE_BYTES_1LINE  = XSPI_CCR_ABMODE_0,                       /*!< Alternate bytes on a single line */
  HAL_XSPI_ALTERNATE_BYTES_2LINES = XSPI_CCR_ABMODE_1,                       /*!< Alternate bytes on two lines     */
  HAL_XSPI_ALTERNATE_BYTES_4LINES = (XSPI_CCR_ABMODE_0 | XSPI_CCR_ABMODE_1), /*!< Alternate bytes on four lines    */
  HAL_XSPI_ALTERNATE_BYTES_8LINES = XSPI_CCR_ABMODE_2                        /*!< Alternate bytes on eight lines   */
} hal_xspi_alternate_bytes_mode_t;

/**
  * @brief HAL XSPI Alternate Bytes Width
  */
typedef enum
{
  HAL_XSPI_ALTERNATE_BYTES_8BIT  = 0x00U,             /*!< 8-bit alternate bytes  */
  HAL_XSPI_ALTERNATE_BYTES_16BIT = XSPI_CCR_ABSIZE_0, /*!< 16-bit alternate bytes */
  HAL_XSPI_ALTERNATE_BYTES_24BIT = XSPI_CCR_ABSIZE_1, /*!< 24-bit alternate bytes */
  HAL_XSPI_ALTERNATE_BYTES_32BIT = XSPI_CCR_ABSIZE    /*!< 32-bit alternate bytes */
} hal_xspi_alternate_bytes_width_t;

/**
  * @brief HAL XSPI Alternate Bytes DTR Mode
  */
typedef enum
{
  HAL_XSPI_ALTERNATE_BYTES_DTR_DISABLED = 0x00U,         /*!< DTR mode disabled for alternate bytes phase */
  HAL_XSPI_ALTERNATE_BYTES_DTR_ENABLED  = XSPI_CCR_ABDTR /*!< DTR mode enabled for alternate bytes phase  */
} hal_xspi_alternate_bytes_dtr_status_t;

/**
  * @brief HAL XSPI Regular Data Mode
  */
typedef enum
{
  HAL_XSPI_REGULAR_DATA_NONE     = 0x00U,                                /*!< No data               */
  HAL_XSPI_REGULAR_DATA_1LINE   = XSPI_CCR_DMODE_0,                      /*!< Data on a single line */
  HAL_XSPI_REGULAR_DATA_2LINES  = XSPI_CCR_DMODE_1,                      /*!< Data on two lines     */
  HAL_XSPI_REGULAR_DATA_4LINES  = (XSPI_CCR_DMODE_0 | XSPI_CCR_DMODE_1), /*!< Data on four lines    */
  HAL_XSPI_REGULAR_DATA_8LINES  = XSPI_CCR_DMODE_2,                      /*!< Data on eight lines   */
#if defined(XSPI_CR_MSEL)
  HAL_XSPI_REGULAR_DATA_16LINES = (XSPI_CCR_DMODE_0 | XSPI_CCR_DMODE_2)  /*!< Data on sixteen lines */
#endif /* XSPI_CR_MSEL */
} hal_xspi_regular_data_mode_t;

/**
  * @brief HAL XSPI Data DTR Mode
  */
typedef enum
{
  HAL_XSPI_DATA_DTR_DISABLED = 0x00U,        /*!< DTR mode disabled for data phase */
  HAL_XSPI_DATA_DTR_ENABLED  = XSPI_CCR_DDTR /*!< DTR mode enabled for data phase  */
} hal_xspi_data_dtr_status_t;

/**
  * @brief HAL XSPI DQS Mode
  */
typedef enum
{
  HAL_XSPI_DQS_DISABLED = 0x00U,        /*!< DQS disabled */
  HAL_XSPI_DQS_ENABLED  = XSPI_CCR_DQSE /*!< DQS enabled  */
} hal_xspi_dqs_status_t;

#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
/**
  * @brief HAL XSPI Hyperbus Write Zero Latency Activation
  */
typedef enum
{
  HAL_XSPI_WRITE_ZERO_LATENCY_ENABLED  = 0x00U,        /*!< Latency on write accesses    */
  HAL_XSPI_WRITE_ZERO_LATENCY_DISABLED = XSPI_HLCR_WZL /*!< No latency on write accesses */
} hal_xspi_write_zero_latency_status_t;

/**
  * @brief HAL XSPI Hyperbus Latency Mode
  */
typedef enum
{
  HAL_XSPI_LATENCY_VARIABLE = 0x00U,       /*!< Variable initial latency */
  HAL_XSPI_LATENCY_FIXED    = XSPI_HLCR_LM /*!< Fixed latency            */
} hal_xspi_latency_mode_t;

/**
  * @brief HAL XSPI Hyperbus Address Space
  */
typedef enum
{
  HAL_XSPI_ADDR_MEMORY   = 0x00U,           /*!< HyperBus memory mode   */
  HAL_XSPI_ADDR_REGISTER = XSPI_DCR1_MTYP_0 /*!< HyperBus register mode */
} hal_xspi_addr_space_t;

/**
  * @brief HAL XSPI Hyperbus Data Mode
  */
typedef enum
{
  HAL_XSPI_HYPERBUS_DATA_8LINES  = XSPI_CCR_DMODE_2,                     /*!< Data on eight lines   */
#if defined(XSPI_CR_MSEL)
  HAL_XSPI_HYPERBUS_DATA_16LINES = (XSPI_CCR_DMODE_0 | XSPI_CCR_DMODE_2) /*!< Data on sixteen lines */
#endif /* XSPI_CR_MSEL */
} hal_xspi_hyperbus_data_mode_t;
#endif /* USE_HAL_XSPI_HYPERBUS */

/**
  * @brief HAL XSPI Match Mode
  */
typedef enum
{
  HAL_XSPI_MATCH_MODE_AND = 0x00U,      /*!< AND match mode between unmasked bits */
  HAL_XSPI_MATCH_MODE_OR  = XSPI_CR_PMM /*!< OR match mode between unmasked bits  */
} hal_xspi_match_mode_t;

/**
  * @brief HAL XSPI Automatic Stop
  */
typedef enum
{
  HAL_XSPI_AUTOMATIC_STOP_DISABLED = 0x00U,       /*!< AutoPolling stops only with abort or XSPI disabling */
  HAL_XSPI_AUTOMATIC_STOP_ENABLED  = XSPI_CR_APMS /*!< AutoPolling stops as soon as there is a match       */
} hal_xspi_automatic_stop_status_t;

/**
  * @brief HAL XSPI Timeout Activation
  */
typedef enum
{
  HAL_XSPI_TIMEOUT_DISABLE = 0x00U,       /*!< Timeout counter disabled, nCS remains active               */
  HAL_XSPI_TIMEOUT_ENABLE  = XSPI_CR_TCEN /*!< Timeout counter enabled, nCS released when timeout expires */
} hal_xspi_timeout_activation_t;

#if defined(XSPI_CALFCR_FINE)
/**
  * @brief HAL XSPI Calibration Delay Type
  */
typedef enum
{
  HAL_XSPI_HSIC_DELAY_CAL_FULL_CYCLE   = 0x00U, /*!< Delay value equivalent to full memory-clock cycle                */
  HAL_XSPI_HSIC_DELAY_CAL_FEEDBACK_CLK = 0x01U, /*!< Delay value for the feedback clock when reading without DQS      */
  HAL_XSPI_HSIC_DELAY_CAL_DATA_OUTPUT  = 0x02U, /*!< Delay value for output data in DDR mode for write operations     */
  HAL_XSPI_HSIC_DELAY_CAL_DQS_INPUT    = 0x03U  /*!< Delay value for DQS input when sampling data for read operations */
} hal_xspi_hsic_delay_cal_type_t;

/**
  * @brief HAL XSPI Calibration Maximal Value
  */
typedef enum
{
  HAL_XSPI_HSIC_MAX_CAL_NOT_REACHED = 0x00U,             /*!< Memory-clock period inside the range of DLL master  */
  HAL_XSPI_HSIC_MAX_CAL_REACHED     = XSPI_CALFCR_CALMAX /*!< Memory-clock period outside the range of DLL master */
} hal_xspi_hsic_max_cal_mode_t;
#endif /* XSPI_CALFCR_FINE */

#if defined(XSPIM)
/**
  * @brief HAL XSPI Ports
  */
typedef enum
{
  HAL_XSPI_XSPIM_NONE         = 0x00U,                                           /*!< Port disabled    */
  HAL_XSPI_XSPIM_XSPI1        = (XSPIM_PCR_CLKEN),                               /*!< Port enabled and set the XSPI1
                                                                                      instance         */
  HAL_XSPI_XSPIM_XSPI2        = (XSPIM_PCR_CLKEN | XSPIM_PCR_CLKSRC),            /*!< Port enabled and set the XSPI2
                                                                                      instance         */
  HAL_XSPI_XSPIM_XSPI1_XSPI2  = (HAL_XSPI_XSPIM_XSPI1 | HAL_XSPI_XSPIM_MUX_MASK) /*!< Port enabled and set the
                                                                                      Multiplexed Mode */
} hal_xspi_xspim_port_t;

/**
  * @brief HAL XSPI I/O Ports
  */
typedef enum
{
  HAL_XSPI_XSPIM_IO_NONE             = 0x00U,                                                       /*!< I/O Low Port disabled                              */
  HAL_XSPI_XSPIM_XSPI1_IO_LOW        = (XSPIM_PCR_IOLEN),                                           /*!< I/O Low Port enabled and set the XSPI1 Instance    */
  HAL_XSPI_XSPIM_XSPI2_IO_LOW        = (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC_1),                      /*!< I/O Low Port enabled and set the XSPI2 Instance    */
  HAL_XSPI_XSPIM_XSPI1_IO_HIGH       = (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC_0),                      /*!< I/O High Port enabled and set the XSPI1 Instance   */
  HAL_XSPI_XSPIM_XSPI2_IO_HIGH       = (XSPIM_PCR_IOLEN | XSPIM_PCR_IOLSRC_0 | XSPIM_PCR_IOLSRC_1), /*!< I/O High Port enabled and set the XSPI2 Instance   */
  HAL_XSPI_XSPIM_XSPI1_XSPI2_IO_LOW  = (HAL_XSPI_XSPIM_XSPI1_IO_LOW | HAL_XSPI_XSPIM_MUX_MASK),     /*!< I/O Low Port enabled and set the Multiplexed Mode  */
  HAL_XSPI_XSPIM_XSPI1_XSPI2_IO_HIGH = (HAL_XSPI_XSPIM_XSPI1_IO_HIGH | HAL_XSPI_XSPIM_MUX_MASK)     /*!< I/O High Port enabled and set the Multiplexed Mode */
} hal_xspi_xspim_io_t;

#endif /* XSPIM */
#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
/**
  * @brief HAL XSPI Hyperbus Configuration Structure definition
  */
typedef struct
{
  uint32_t rw_recovery_time_cycle;                         /*!< It indicates the number of cycles for the device
                                                                recovery time.
                                                                This parameter can be a value between 0 and 255    */
  uint32_t access_time_cycle;                              /*!< It indicates the number of cycles for the device access
                                                                time.
                                                                This parameter can be a value between 0 and 255    */
  hal_xspi_write_zero_latency_status_t write_zero_latency; /*!< It enables or not the latency for the write access */
  hal_xspi_latency_mode_t latency_mode;                    /*!< It configures the latency mode.                    */
} hal_xspi_hyperbus_config_t;
#endif /* USE_HAL_XSPI_HYPERBUS */

/**
  * @brief HAL XSPI Timing Config structure definition
  */
typedef struct
{
  uint32_t clk_prescaler;              /*!< It specifies the prescaler factor used for generating
                                            the external clock based on the AHB clock.
                                            This parameter can be a value between 0 and 255        */
  hal_xspi_sample_shift_t shift;       /*!< It allows to delay to 1/2 cycle the data sampling in
                                            order to take in account external signal delays.       */
  hal_xspi_delay_hold_t hold;          /*!< It allows to hold to 1/4 cycle the data                */
  uint32_t cs_high_time_cycle;         /*!< It defines the minimum number of clocks which the chip
                                            select must remain high between commands.
                                            This parameter can be a value between 1 and 64         */
  uint32_t cs_release_time_cycle;      /*!< It enables the communication regulation feature. The
                                            chip select is released every MaxTran+1 bytes when the
                                            other XSPI request the access to the bus.
                                            This parameter can be a value between 0 and 255        */
  uint32_t cs_refresh_time_cycle;      /*!< It enables the refresh rate feature. The chip select is
                                            released every Refresh+1 clock cycles.
                                            This parameter can be a value between 0 and 0xFFFFFFFF */
  hal_xspi_dlyb_state_t dlyb_state;    /*!< It enables the delay block bypass, so the sampling is
                                            not affected by the delay block                        */
} hal_xspi_timing_config_t;

/**
  * @brief HAL XSPI Memory Configuration structure definition
  */
typedef struct
{
  hal_xspi_memory_mode_t mode;              /*!< It Specifies the memory mode                                     */

  hal_xspi_memory_type_t type;              /*!< It indicates the external device type connected to the XSPI      */

  hal_xspi_memory_size_t size_bit;          /*!< It defines the size of the external device connected to the XSPI,
                                                 it corresponds to the number of address bits required to access
                                                 the external device                                              */
  hal_xspi_clock_polarity_t clock_polarity; /*!< It indicates the level of clock when the chip select is released */

  hal_xspi_wrap_size_t wrap_size_byte;      /*!< It indicates the wrap-size corresponding the external device     */

  hal_xspi_cs_boundary_t cs_boundary;       /*!< It enables the transaction boundary feature and
                                                 defines the boundary of bytes to release the chip select         */
} hal_xspi_memory_config_t;

/**
  * @brief HAL XSPI Global Configuration structure definition
  */
typedef struct
{
  hal_xspi_memory_config_t memory;     /*!< It Specifies XSPI Memory Configuration structure definition   */

  hal_xspi_timing_config_t timing;     /*!< It Specifies XSPI Timing Configuration structure definition   */

#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
  hal_xspi_hyperbus_config_t hyperbus; /*!< It Specifies XSPI Hyperbus Configuration structure definition */
#endif /* USE_HAL_XSPI_HYPERBUS */
} hal_xspi_config_t;

/**
  * @brief HAL XSPI Auto Polling mode configuration structure definition
  */
typedef struct
{
  uint32_t match_value;                                   /*!< Specifies the value to be compared with the masked status
                                                               register. This parameter can be any value between
                                                               0 and 0xFFFFFFFFU                                    */
  uint32_t match_mask;                                    /*!< Specifies the mask to be applied to the status bytes
                                                               received. This parameter can be any value between
                                                               0 and 0xFFFFFFFFU                                    */
  hal_xspi_match_mode_t match_mode;                       /*!< Specifies the method used for determining a match    */

  hal_xspi_automatic_stop_status_t automatic_stop_status; /*!< Specifies if automatic polling is stopped after a
                                                               match                                                */
  uint32_t interval_cycle;                                /*!< Specifies the number of clock cycles between two read
                                                               during automatic polling phases.
                                                               This parameter can be any value between 0 and 0xFFFF */
} hal_xspi_auto_polling_config_t;

/**
  * @brief HAL XSPI Regular Command Structure definition
  */
typedef struct
{
  hal_xspi_operation_type_t operation_type;                              /*!< It indicates if the configuration applies
                                                                              to the common registers or
                                                                              to the registers for the write operation
                                                                              (these registers are only used for
                                                                               memory-mapped mode)                    */
  hal_xspi_io_select_t  io_select;                                       /*!< It indicates the IOs used to exchange
                                                                              data with external memory               */

  uint32_t instruction;                                                  /*!< It contains the instruction to be sent to
                                                                              the device.
                                                                              This parameter can be a value between
                                                                              0 and 0xFFFFFFFFU                       */
  hal_xspi_instruction_mode_t instruction_mode;                          /*!< It indicates the mode of the
                                                                              instruction                             */

  hal_xspi_instruction_width_t instruction_width;                        /*!< It indicates the width of the
                                                                              instruction                             */

  hal_xspi_instruction_dtr_status_t instruction_dtr_mode_status;         /*!< It enables or not the DTR mode for the
                                                                              instruction phase                       */

  uint32_t addr;                                                         /*!< It contains the address to be sent to the
                                                                              device.
                                                                              This parameter can be a value between
                                                                              0 and 0xFFFFFFFF                        */
  hal_xspi_addr_mode_t addr_mode;                                        /*!< It indicates the address mode. Address
                                                                              mode precises number of lines
                                                                              for address (except no address)         */
  hal_xspi_addr_width_t addr_width;                                      /*!< It indicates the width of the address   */

  hal_xspi_addr_dtr_status_t addr_dtr_mode_status;                       /*!< It enables or not the DTR mode for the
                                                                              address phase                           */

  uint32_t alternate_bytes;                                              /*!< It contains the alternate bytes to be sent
                                                                              to the device.
                                                                              This parameter can be a value between
                                                                              0 and 0xFFFFFFFF                        */
  hal_xspi_alternate_bytes_mode_t alternate_bytes_mode;                  /*!< It indicates the mode of the alternate
                                                                              bytes                                   */

  hal_xspi_alternate_bytes_width_t alternate_bytes_width;                /*!< It indicates the width of the alternate
                                                                              bytes                                   */

  hal_xspi_alternate_bytes_dtr_status_t alternate_bytes_dtr_mode_status; /*!< It enables or not the DTR mode for the
                                                                              alternate bytes phase                   */

  hal_xspi_regular_data_mode_t data_mode;                                /*!< It indicates the data mode. Data mode
                                                                              precises number of lines
                                                                              for data exchange (except no data)      */
  hal_xspi_data_dtr_status_t data_dtr_mode_status;                       /*!< It enables or not the DTR mode for the
                                                                              data phase                              */

  uint32_t dummy_cycle;                                                  /*!< It indicates the number of dummy cycles
                                                                              inserted before data phase.
                                                                              This parameter can be a value between
                                                                              0 and 31U */
  hal_xspi_dqs_status_t dqs_mode_status;                                 /*!< It enables or not the data strobe
                                                                              management                              */
  uint32_t size_byte;                                                    /*!< It indicates the number of data
                                                                              transferred with this command.
                                                                              This field is only used for indirect mode.
                                                                              This parameter can be a value between
                                                                              1 and 0xFFFFFFFFU                       */
} hal_xspi_regular_cmd_t;

#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
/**
  * @brief HAL XSPI Hyperbus Command Structure definition
  */
typedef struct
{
  hal_xspi_addr_space_t         addr_space;      /*!< It indicates the address space accessed by the command */

  uint32_t                      addr;            /*!< It contains the address to be sent to the device.
                                                      This parameter can be a value between 0 and 0xFFFFFFFF */
  hal_xspi_addr_width_t         addr_width;      /*!< It indicates the width of the address                  */

  uint32_t                      size_byte;       /*!< It indicates the number of data transferred with this command.
                                                      This field is only used for indirect mode.
                                                      This parameter can be a value between 1 and 0xFFFFFFFF */
  hal_xspi_dqs_status_t         dqs_mode_status; /*!< It enables or not the data strobe management           */

  hal_xspi_hyperbus_data_mode_t data_mode;       /*!< It indicates the data mode. Data mode precises number of lines for
                                                      data exchange (except no data)                         */
} hal_xspi_hyperbus_cmd_t;
#endif /* USE_HAL_XSPI_HYPERBUS */

/**
  * @brief HAL XSPI Memory Mapped mode configuration structure definition
  */
typedef struct
{
  hal_xspi_timeout_activation_t timeout_activation; /*!< Specifies if the timeout counter is enabled to release the chip
                                                         select                                               */

  uint32_t timeout_period_cycle;                    /*!< Specifies the number of clock to wait when the FIFO is full
                                                         before to release the chip select.
                                                         This parameter can be any value between 0 and 0xFFFF */
} hal_xspi_memory_mapped_config_t;

#if defined(XSPIM)
/**
  * @brief HAL XSPI IO Manager Configuration structure definition
  */
typedef struct
{
  struct
  {
    hal_xspi_xspim_port_t    clk;     /*!< It indicates which instance in the port1 of the XSPI IO Manager
                                           is used for the CLK pin     */
    hal_xspi_xspim_port_t    dqs;     /*!< It indicates which instance in the port1 of the XSPI IO Manager
                                           is used for the DQS pin     */
    hal_xspi_xspim_port_t    ncs;     /*!< It indicates which instance in the port1 of the XSPI IO Manager
                                           is used for the NCS pin     */
    hal_xspi_xspim_io_t      io_low;  /*!< It indicates which instance in the port1 of the XSPI IO Manager
                                           is used for the IO[3:0] pin */
    hal_xspi_xspim_io_t      io_high; /*!< It indicates which instance in the port1 of the XSPI IO Manager
                                           is used for the IO[7:4] pin */
  } port1;                            /*!< It indicates the IO Configuration of XSPIM port1 */
  struct
  {
    hal_xspi_xspim_port_t    clk;     /*!< It indicates which instance in the port2 of the XSPI IO Manager
                                           is used for the CLK pin     */
    hal_xspi_xspim_port_t    dqs;     /*!< It indicates which instance in the port2 of the XSPI IO Manager
                                           is used for the DQS pin     */
    hal_xspi_xspim_port_t    ncs;     /*!< It indicates which instance in the port2 of the XSPI IO Manager
                                           is used for the NCS pin     */
    hal_xspi_xspim_io_t      io_low;  /*!< It indicates which instance in the port2 of the XSPI IO Manager
                                           is used for the IO[3:0] pin */
    hal_xspi_xspim_io_t      io_high; /*!< It indicates which instance in the port2 of the XSPI IO Manager
                                           is used for the IO[7:4] pin */
  } port2;                            /*!< It indicates the IO Configuration of XSPIM port2 */
  uint32_t                     req_ack_cycle;       /*!< Req to Ack time */
} hal_xspi_xspim_config_t;
#endif /* XSPIM */
#if defined(XSPI_CALFCR_FINE)
/**
  * @brief HAL XSPI High-speed interface calibration structure definition
  */
typedef struct
{
  hal_xspi_hsic_delay_cal_type_t delay_value_type;  /*!< It indicates which calibration is concerned by the
                                                         configuration */
  uint32_t fine_cal_unit;                           /*!< It indicates the fine calibration value of the delay.
                                                         This parameter can be a value between 0 and 0x7F       */
  uint32_t coarse_cal_unit;                         /*!< It indicates the coarse calibration value of the delay.
                                                         This parameter can be a value between 0 and 0x1F       */
  hal_xspi_hsic_max_cal_mode_t max_cal;             /*!< It indicates that the calibration is outside the range
                                                         of DLL master. It applies only when the DelayValueType
                                                         is HAL_XSPI_HSIC_DELAY_CAL_FULL_CYCLE                  */
} hal_xspi_hsic_config_t;
#endif /* XSPI_CALFCR_FINE */

typedef struct hal_xspi_handle_s hal_xspi_handle_t;/*!< XSPI Handle Structure type */

#if defined(USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
typedef void (*hal_xspi_cb_t)(hal_xspi_handle_t *hxspi);/*!< XSPI Callback pointer definition */
#endif /* (USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1) */

/**
  * @brief HAL XSPI handle Structure definition
  */
struct hal_xspi_handle_s
{
  hal_xspi_t                instance;       /*!< XSPI registers base address                 */

  volatile hal_xspi_state_t global_state;   /*!< Internal state of the XSPI HAL driver       */

#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
  volatile hal_xspi_otfdec_region_state_t region_state[4]; /*!< OTFDEC driver region state  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */

  uint8_t                   *p_buffer;      /*!< Address of the XSPI buffer for transfer     */

  volatile uint32_t         xfer_size;      /*!< Number of data to transfer                  */

  volatile uint32_t         xfer_count;     /*!< Counter of data transferred                 */

  hal_xspi_memory_mode_t    mode;           /*!< Specifies the memory mode                   */

  hal_xspi_delay_hold_t     hold;           /*!< It allows to hold to 1/4 cycle the data     */

  hal_xspi_memory_type_t    type;           /*!< Indicates the external device type          */

  uint32_t                  fifo_threshold; /*!< Specifies the fifo configuration value      */

#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
  uint32_t                  is_dma_error;   /*!< Indicates an error occurs in DMA mode       */

  hal_dma_handle_t          *p_dma_tx;      /*!< Handle of the DMA channel used for transmit */

  hal_dma_handle_t          *p_dma_rx;      /*!< Handle of the DMA channel used for receive  */
#endif /* USE_HAL_XSPI_DMA */

#if defined(USE_HAL_XSPI_USER_DATA) && (USE_HAL_XSPI_USER_DATA == 1)
  const void                *p_user_data;   /*!< User Data Pointer                           */
#endif /* USE_HAL_XSPI_USER_DATA */

#if defined(USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
  hal_xspi_cb_t p_error_cb;                 /*!< XSPI error callback                         */
  hal_xspi_cb_t p_abort_cplt_cb;            /*!< XSPI abort callback                         */
  hal_xspi_cb_t p_fifo_threshold_cb;        /*!< XSPI fifo threshold callback                */
  hal_xspi_cb_t p_cmd_cplt_cb;              /*!< XSPI command complete callback              */
  hal_xspi_cb_t p_rx_cplt_cb;               /*!< XSPI receive complete callback              */
  hal_xspi_cb_t p_tx_cplt_cb;               /*!< XSPI transfer complete callback             */
  hal_xspi_cb_t p_rx_half_cplt_cb;          /*!< XSPI half receive complete callback         */
  hal_xspi_cb_t p_tx_half_cplt_cb;          /*!< XSPI half transfer complete callback        */
  hal_xspi_cb_t p_status_match_cb;          /*!< XSPI status match callback                  */
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
  hal_xspi_cb_t p_otfdec_error_cb;          /*!< XSPI OTFDEC error callback                  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
#endif /* USE_HAL_XSPI_REGISTER_CALLBACKS */

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
  /* in case of single process at a time: one single variable storing the last errors */
  volatile uint32_t last_error_codes;       /*!< XSPI error codes                            */
#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
  volatile uint32_t last_otfdec_error_codes; /*!< XSPI OTFDEC error codes                     */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
};

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup XSPI_Exported_Functions XSPI Exported Functions
  * @{
  */

/** @defgroup XSPI_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_XSPI_Init(hal_xspi_handle_t *hxspi, hal_xspi_t instance);
void         HAL_XSPI_DeInit(hal_xspi_handle_t *hxspi);
/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group2 XSPI Configuration functions
  * @{
  */
hal_status_t HAL_XSPI_SetConfig(hal_xspi_handle_t *hxspi, const hal_xspi_config_t *p_config);
void         HAL_XSPI_GetConfig(hal_xspi_handle_t *hxspi, hal_xspi_config_t *p_config);
hal_status_t HAL_XSPI_SetFifoThreshold(hal_xspi_handle_t *hxspi, uint32_t threshold);
uint32_t     HAL_XSPI_GetFifoThreshold(const hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_SetPrescaler(hal_xspi_handle_t *hxspi, uint32_t clk_prescaler);
uint32_t     HAL_XSPI_GetPrescaler(const hal_xspi_handle_t *hxspi);
hal_status_t           HAL_XSPI_SetMemorySize(hal_xspi_handle_t *hxspi, hal_xspi_memory_size_t size);
hal_xspi_memory_size_t HAL_XSPI_GetMemorySize(const hal_xspi_handle_t *hxspi);
hal_status_t           HAL_XSPI_SetMemoryType(hal_xspi_handle_t *hxspi, hal_xspi_memory_type_t type);
hal_xspi_memory_type_t HAL_XSPI_GetMemoryType(const hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_EnableFreeRunningClock(hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_DisableFreeRunningClock(hal_xspi_handle_t *hxspi);
hal_xspi_free_running_clk_status_t HAL_XSPI_IsEnabledFreeRunningClock(const hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_EnableSIOO(hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_DisableSIOO(hal_xspi_handle_t *hxspi);
hal_xspi_sioo_status_t HAL_XSPI_IsEnabledSIOO(const hal_xspi_handle_t *hxspi);
/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group3 XSPI Command and IO operation functions
  * @{
  */
hal_status_t HAL_XSPI_StartMemoryMappedMode(hal_xspi_handle_t *hxspi, const hal_xspi_memory_mapped_config_t *p_config);
hal_status_t HAL_XSPI_StopMemoryMappedMode(hal_xspi_handle_t *hxspi);

/* XSPI command configuration functions */
hal_status_t HAL_XSPI_SendRegularCmd(hal_xspi_handle_t *hxspi, const hal_xspi_regular_cmd_t *p_cmd,
                                     uint32_t timeout_ms);
hal_status_t HAL_XSPI_SendRegularCmd_IT(hal_xspi_handle_t *hxspi, const hal_xspi_regular_cmd_t *p_cmd);

#if defined(USE_HAL_XSPI_HYPERBUS) && (USE_HAL_XSPI_HYPERBUS == 1)
hal_status_t HAL_XSPI_SendHyperbusCmd(hal_xspi_handle_t *hxspi, const hal_xspi_hyperbus_cmd_t *p_cmd,
                                      uint32_t timeout_ms);
#endif /* USE_HAL_XSPI_HYPERBUS */

hal_status_t HAL_XSPI_ExecRegularAutoPoll(hal_xspi_handle_t *hxspi, const hal_xspi_auto_polling_config_t *p_config,
                                          uint32_t timeout_ms);
hal_status_t HAL_XSPI_ExecRegularAutoPoll_IT(hal_xspi_handle_t *hxspi, const hal_xspi_auto_polling_config_t *p_config);

/* IO operation functions */
hal_status_t HAL_XSPI_Transmit(hal_xspi_handle_t *hxspi, const void *p_data, uint32_t timeout_ms);
hal_status_t HAL_XSPI_Receive(hal_xspi_handle_t *hxspi, void *p_data, uint32_t timeout_ms);
hal_status_t HAL_XSPI_Transmit_IT(hal_xspi_handle_t *hxspi, const void *p_data);
hal_status_t HAL_XSPI_Receive_IT(hal_xspi_handle_t *hxspi, void *p_data);
#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
hal_status_t HAL_XSPI_Transmit_DMA(hal_xspi_handle_t *hxspi, const void *p_data);
hal_status_t HAL_XSPI_Receive_DMA(hal_xspi_handle_t *hxspi, void *p_data);
hal_status_t HAL_XSPI_Transmit_DMA_Opt(hal_xspi_handle_t *hxspi, const void *p_data, uint32_t interrupts);
hal_status_t HAL_XSPI_Receive_DMA_Opt(hal_xspi_handle_t *hxspi, void *p_data, uint32_t interrupts);
#endif /* USE_HAL_XSPI_DMA */
hal_status_t HAL_XSPI_Abort(hal_xspi_handle_t *hxspi, uint32_t timeout_ms);
hal_status_t HAL_XSPI_Abort_IT(hal_xspi_handle_t *hxspi);
/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group4 IRQHandler, link DMA and Callbacks functions
  * @{
  */
void HAL_XSPI_IRQHandler(hal_xspi_handle_t *hxspi);
/* Callback functions in non-blocking modes */
void HAL_XSPI_ErrorCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_AbortCpltCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_FifoThresholdCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_CmdCpltCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_RxCpltCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_TxCpltCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_RxHalfCpltCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_TxHalfCpltCallback(hal_xspi_handle_t *hxspi);
void HAL_XSPI_StatusMatchCallback(hal_xspi_handle_t *hxspi);
#if defined(USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
/* XSPI callback registering*/
hal_status_t HAL_XSPI_RegisterErrorCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterCmdCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterRxCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterTxCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterRxHalfCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterTxHalfCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterStatusMatchCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterAbortCpltCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
hal_status_t HAL_XSPI_RegisterFifoThresholdCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
#endif /* USE_HAL_XSPI_REGISTER_CALLBACKS */
#if defined(USE_HAL_XSPI_USER_DATA) && (USE_HAL_XSPI_USER_DATA == 1)
void HAL_XSPI_SetUserData(hal_xspi_handle_t *hxspi, const void *p_user_data);
const void *HAL_XSPI_GetUserData(const hal_xspi_handle_t *hxspi);
#endif /* USE_HAL_XSPI_USER_DATA == 1 */
#if defined(USE_HAL_XSPI_DMA) && (USE_HAL_XSPI_DMA == 1)
hal_status_t HAL_XSPI_SetTxDMA(hal_xspi_handle_t *hxspi, hal_dma_handle_t *p_dma_tx);
hal_status_t HAL_XSPI_SetRxDMA(hal_xspi_handle_t *hxspi, hal_dma_handle_t *p_dma_rx);
#endif /* USE_HAL_XSPI_DMA */
/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group5 Peripheral current frequency, state and errors functions
  * @{
  */
uint32_t         HAL_XSPI_GetClockFreq(const hal_xspi_handle_t *hxspi);
hal_xspi_state_t HAL_XSPI_GetState(const hal_xspi_handle_t *hxspi);
#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
uint32_t         HAL_XSPI_GetLastErrorCodes(const hal_xspi_handle_t *hxspi);
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
/**
  * @}
  */

/** @defgroup XSPI_Exported_Functions_Group6 XSPI Delay Block functions
  * @{
  */
hal_status_t HAL_XSPI_DLYB_SetConfigDelay(hal_xspi_handle_t *hxspi, uint32_t clock_phase_value);
hal_status_t HAL_XSPI_DLYB_GetConfigDelay(const hal_xspi_handle_t *hxspi, uint32_t *p_clock_phase);
hal_status_t HAL_XSPI_DLYB_CalculateMaxClockPhase(hal_xspi_handle_t *hxspi, uint32_t *p_max_clock_phase);
hal_status_t HAL_XSPI_DLYB_Enable(hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_DLYB_Disable(hal_xspi_handle_t *hxspi);
hal_xspi_dlyb_status_t HAL_XSPI_DLYB_IsEnabled(const hal_xspi_handle_t *hxspi);
/**
  * @}
  */

#if defined(XSPI_CALFCR_FINE)
/** @defgroup XSPI_Exported_Functions_Group7 XSPI high-speed interface and calibration functions
  * @{
  */
hal_status_t HAL_XSPI_HSIC_SetConfigDelay(hal_xspi_handle_t *hxspi, const hal_xspi_hsic_config_t *p_config);
hal_status_t HAL_XSPI_HSIC_GetConfigDelay(const hal_xspi_handle_t *hxspi, hal_xspi_hsic_config_t *p_config);
/**
  * @}
  */
#endif /* XSPI_CALFCR_FINE */

#if defined(XSPIM)
/** @defgroup XSPI_Exported_Functions_Group8 XSPI high-speed interface and calibration functions
  * @{
  */
hal_status_t HAL_XSPI_XSPIM_SetConfig(const hal_xspi_xspim_config_t *p_config);
void         HAL_XSPI_XSPIM_GetConfig(hal_xspi_xspim_config_t *p_config);
/**
  * @}
  */
#endif /* XSPIM */

/** @addtogroup XSPI_Exported_Functions_Group9 Interrupt functions
  * @{
  */
/** @brief  Enable the specified XSPI interrupt.
  * @param  hxspi specifies the XSPI Handle.
  * @param  it_source specifies the XSPI interrupt source to enable
  *         This parameter can be any combination of the following values:
  *            @arg HAL_XSPI_IT_TO:  XSPI Timeout interrupt
  *            @arg HAL_XSPI_IT_SM:  XSPI Status match interrupt
  *            @arg HAL_XSPI_IT_FT:  XSPI FIFO threshold interrupt
  *            @arg HAL_XSPI_IT_TC:  XSPI Transfer complete interrupt
  *            @arg HAL_XSPI_IT_TE:  XSPI Transfer error interrupt
  *            @arg HAL_XSPI_IT_ALL: XSPI All interrupts
  */
__STATIC_INLINE void HAL_XSPI_EnableIT(hal_xspi_handle_t *hxspi, uint32_t it_source)
{
  SET_BIT(((XSPI_TypeDef *)((uint32_t) hxspi->instance))->CR, it_source);
}

/** @brief  Disable the specified XSPI interrupt.
  * @param  hxspi specifies the XSPI Handle.
  * @param  it_source specifies the XSPI interrupt source to disable
  *         This parameter can be any combination of the following values:
  *            @arg HAL_XSPI_IT_TO: XSPI Timeout interrupt
  *            @arg HAL_XSPI_IT_SM: XSPI Status match interrupt
  *            @arg HAL_XSPI_IT_FT: XSPI FIFO threshold interrupt
  *            @arg HAL_XSPI_IT_TC: XSPI Transfer complete interrupt
  *            @arg HAL_XSPI_IT_TE: XSPI Transfer error interrupt
  *            @arg HAL_XSPI_IT_ALL: XSPI All interrupts
  */
__STATIC_INLINE void HAL_XSPI_DisableIT(hal_xspi_handle_t *hxspi, uint32_t it_source)
{
  CLEAR_BIT(((XSPI_TypeDef *)((uint32_t) hxspi->instance))->CR, it_source);
}

/** @brief  Check whether the specified XSPI interrupt source is enabled or not.
  * @param  hxspi specifies the XSPI Handle.
  * @param  it_source specifies the XSPI interrupt source to check
  *         This parameter can be one of the following values:
  *            @arg HAL_XSPI_IT_TO: XSPI Timeout interrupt
  *            @arg HAL_XSPI_IT_SM: XSPI Status match interrupt
  *            @arg HAL_XSPI_IT_FT: XSPI FIFO threshold interrupt
  *            @arg HAL_XSPI_IT_TC: XSPI Transfer complete interrupt
  *            @arg HAL_XSPI_IT_TE: XSPI Transfer error interrupt
  * @return retrieve the state of the selected XSPI interrupt.
  */
__STATIC_INLINE uint32_t HAL_XSPI_IsEnabledIT(const hal_xspi_handle_t *hxspi, uint32_t it_source)
{
  return ((READ_BIT(((XSPI_TypeDef *)((uint32_t) hxspi->instance))->CR,
                    it_source) == it_source) ? 1U : 0U);
}

/**
  * @brief  Check whether the selected XSPI flag is set or not.
  * @param  hxspi specifies the XSPI Handle.
  * @param  flag specifies the XSPI flag to check
  *         This parameter can be one of the following values:
  *            @arg HAL_XSPI_FLAG_BUSY: XSPI Busy flag
  *            @arg HAL_XSPI_FLAG_TO:   XSPI Timeout flag
  *            @arg HAL_XSPI_FLAG_SM:   XSPI Status match flag
  *            @arg HAL_XSPI_FLAG_FT:   XSPI FIFO threshold flag
  *            @arg HAL_XSPI_FLAG_TC:   XSPI Transfer complete flag
  *            @arg HAL_XSPI_FLAG_TE:   XSPI Transfer error flag
  * @return retrieve the state of the selected XSPI flag.
  */
__STATIC_INLINE hal_xspi_flag_status_t HAL_XSPI_IsActiveFlag(const hal_xspi_handle_t *hxspi, uint32_t flag)
{
  return ((READ_BIT(((XSPI_TypeDef *)((uint32_t) hxspi->instance))->SR, flag) != 0U) ? HAL_XSPI_FLAG_ACTIVE \
          : HAL_XSPI_FLAG_NOT_ACTIVE);
}

/** @brief  Clears the specified XSPI's flag status.
  * @param  hxspi specifies the XSPI Handle.
  * @param  flag specifies the XSPI clear register flag that needs to be set
  *         This parameter can be any combination of the following values:
  *            @arg HAL_XSPI_FLAG_TO:   XSPI Timeout flag
  *            @arg HAL_XSPI_FLAG_SM:   XSPI Status match flag
  *            @arg HAL_XSPI_FLAG_TC:   XSPI Transfer complete flag
  *            @arg HAL_XSPI_FLAG_TE:   XSPI Transfer error flag
  *            @arg HAL_XSPI_FLAG_ALL:  XSPI All flags
  */
__STATIC_INLINE void HAL_XSPI_ClearFlag(hal_xspi_handle_t *hxspi, uint32_t flag)
{
  WRITE_REG(((XSPI_TypeDef *)((uint32_t) hxspi->instance))->FCR, flag);
}
/**
  * @}
  */

#if defined(USE_HAL_XSPI_OTFDEC) && (USE_HAL_XSPI_OTFDEC == 1)
#if defined(OTFDEC1)
/** @defgroup XSPI_Exported_Functions_Group10 XSPI OTFDEC functions
  * @{
  */
hal_status_t HAL_XSPI_OTFDEC_SetConfigRegion(hal_xspi_handle_t *hxspi,
                                             hal_xspi_otfdec_region_t region,
                                             const hal_xspi_otfdec_config_t *p_config,
                                             const hal_xspi_otfdec_key_t *p_key_config);
void         HAL_XSPI_OTFDEC_GetConfigRegion(hal_xspi_handle_t *hxspi,
                                             hal_xspi_otfdec_region_t region,
                                             hal_xspi_otfdec_config_t *p_config);
hal_status_t HAL_XSPI_OTFDEC_StartRegionDecryption(hal_xspi_handle_t *hxspi,
                                                   hal_xspi_otfdec_region_t region,
                                                   uint32_t interrupts);
hal_status_t HAL_XSPI_OTFDEC_StopRegionDecryption(hal_xspi_handle_t *hxspi,
                                                  hal_xspi_otfdec_region_t region);
hal_status_t HAL_XSPI_OTFDEC_Encrypt(hal_xspi_handle_t *hxspi, hal_xspi_otfdec_region_t region, uint32_t *p_input,
                                     uint32_t *p_output, uint32_t size_byte, uint32_t start_address,
                                     uint32_t interrupts);
hal_status_t HAL_XSPI_OTFDEC_GetRegionKeyCRC(hal_xspi_handle_t *hxspi,
                                             hal_xspi_otfdec_region_t region,
                                             uint8_t *p_key_crc);
hal_status_t HAL_XSPI_OTFDEC_EnablePrivAccess(hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_OTFDEC_DisablePrivAccess(hal_xspi_handle_t *hxspi);
hal_xspi_otfdec_privilege_attr_t HAL_XSPI_OTFDEC_IsEnabledPrivAccess(hal_xspi_handle_t *hxspi);
hal_status_t HAL_XSPI_OTFDEC_LockRegionConfig(hal_xspi_handle_t *hxspi,
                                              hal_xspi_otfdec_region_t region);
hal_xspi_otfdec_lock_config_status_t HAL_XSPI_OTFDEC_IsLockedRegionConfig(hal_xspi_handle_t *hxspi,
                                                                          hal_xspi_otfdec_region_t region);
hal_status_t HAL_XSPI_OTFDEC_LockRegionKey(hal_xspi_handle_t *hxspi, hal_xspi_otfdec_region_t region);
hal_xspi_otfdec_lock_key_status_t HAL_XSPI_OTFDEC_IsLockedRegionKey(hal_xspi_handle_t *hxspi,
                                                                    hal_xspi_otfdec_region_t region);

void HAL_XSPI_OTFDEC_IRQHandler(hal_xspi_handle_t *hxspi);
void HAL_XSPI_OTFDEC_ErrorCallback(hal_xspi_handle_t *hxspi);
#if defined(USE_HAL_XSPI_REGISTER_CALLBACKS) && (USE_HAL_XSPI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_XSPI_OTFDEC_RegisterErrorCallback(hal_xspi_handle_t *hxspi, hal_xspi_cb_t callback);
#endif /* USE_HAL_XSPI_REGISTER_CALLBACKS */

hal_xspi_otfdec_region_state_t HAL_XSPI_OTFDEC_GetRegionState(const hal_xspi_handle_t *hxspi,
                                                              hal_xspi_otfdec_region_t region);

#if defined(USE_HAL_XSPI_GET_LAST_ERRORS) && (USE_HAL_XSPI_GET_LAST_ERRORS == 1)
uint32_t         HAL_XSPI_OTFDEC_GetLastErrorCodes(const hal_xspi_handle_t *hxspi);
#endif /* USE_HAL_XSPI_GET_LAST_ERRORS */
/**
  * @}
  */
#endif /* OTFDEC1 */
#endif /* USE_HAL_XSPI_OTFDEC */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* HSPI1 || OCTOSPI1 || OCTOSPI2 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_XSPI_H */
