/**
  **********************************************************************************************************************
  * @file    stm32u5xx_hal_dma.h
  * @brief   Header file of DMA HAL module.
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
#ifndef STM32U5XX_HAL_DMA_H
#define STM32U5XX_HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"
#include "stm32u5xx_ll_dma.h"
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/* Include Q module for linked-list management with associated features */
#define USE_HAL_Q_DIRECT_ADDR_MODE (1U)
#define USE_HAL_Q_CIRCULAR_LINK    (1U)
#include "stm32u5xx_hal_q.h"
#endif /* USE_HAL_DMA_LINKEDLIST */

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup DMA DMA
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @{
  */
#if defined(USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
/** @defgroup DMA_Error_Code Error Code definition reflecting the processes asynchronous errors
  * @{
  */
#define HAL_DMA_ERROR_NONE    0U             /*!< DMA channel error none                            */
#define HAL_DMA_ERROR_DTE     (0x01UL << 0U) /*!< DMA channel data transfer error                   */
#define HAL_DMA_ERROR_USE     (0x01UL << 1U) /*!< DMA channel user setting error                    */
#define HAL_DMA_ERROR_TO      (0x01UL << 2U) /*!< DMA channel trigger overrun error                 */
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
#define HAL_DMA_ERROR_ULE     (0x01UL << 3U) /*!< DMA channel fetch node error                      */
#endif /* USE_HAL_DMA_LINKEDLIST */
/**
  * @}
  */
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */

/** @defgroup DMA_Optional_Interrupt Optional interrupts
  * @{
  */
#define HAL_DMA_OPT_IT_NONE    0U                                      /*!< DMA channel optional interrupts disabled      */
#define HAL_DMA_OPT_IT_HT      (0x01UL << 9U)                          /*!< DMA channel half transfer interrupt enabled   */
#define HAL_DMA_OPT_IT_TO      (0x01UL << 14U)                         /*!< DMA channel trigger overrun interrupt enabled */
#define HAL_DMA_OPT_IT_DEFAULT (HAL_DMA_OPT_IT_HT | HAL_DMA_OPT_IT_TO) /*!< DMA channel all optional interrupts enabled   */
#define HAL_DMA_OPT_IT_SILENT  0xFFFFFFFFU                             /*!< DMA channel all interrupts disabled           */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Types DMA Exported Types
  * @{
  */

/*! DMA channel instances enumeration definition */
typedef enum
{
  /* GPDMA channel instances */
  HAL_GPDMA1_CH0  = (uint32_t)GPDMA1_CH0,  /*!< GPDMA1 Channel 0  */
  HAL_GPDMA1_CH1  = (uint32_t)GPDMA1_CH1,  /*!< GPDMA1 Channel 1  */
  HAL_GPDMA1_CH2  = (uint32_t)GPDMA1_CH2,  /*!< GPDMA1 Channel 2  */
  HAL_GPDMA1_CH3  = (uint32_t)GPDMA1_CH3,  /*!< GPDMA1 Channel 3  */
  HAL_GPDMA1_CH4  = (uint32_t)GPDMA1_CH4,  /*!< GPDMA1 Channel 4  */
  HAL_GPDMA1_CH5  = (uint32_t)GPDMA1_CH5,  /*!< GPDMA1 Channel 5  */
  HAL_GPDMA1_CH6  = (uint32_t)GPDMA1_CH6,  /*!< GPDMA1 Channel 6  */
  HAL_GPDMA1_CH7  = (uint32_t)GPDMA1_CH7,  /*!< GPDMA1 Channel 7  */
  HAL_GPDMA1_CH8  = (uint32_t)GPDMA1_CH8,  /*!< GPDMA1 Channel 8  */
  HAL_GPDMA1_CH9  = (uint32_t)GPDMA1_CH9,  /*!< GPDMA1 Channel 9  */
  HAL_GPDMA1_CH10 = (uint32_t)GPDMA1_CH10, /*!< GPDMA1 Channel 10 */
  HAL_GPDMA1_CH11 = (uint32_t)GPDMA1_CH11, /*!< GPDMA1 Channel 11 */
  HAL_GPDMA1_CH12 = (uint32_t)GPDMA1_CH12, /*!< GPDMA1 Channel 12 */
  HAL_GPDMA1_CH13 = (uint32_t)GPDMA1_CH13, /*!< GPDMA1 Channel 13 */
  HAL_GPDMA1_CH14 = (uint32_t)GPDMA1_CH14, /*!< GPDMA1 Channel 14 */
  HAL_GPDMA1_CH15 = (uint32_t)GPDMA1_CH15, /*!< GPDMA1 Channel 15 */

  /* LPDMA channel instances */
  HAL_LPDMA1_CH0  = (uint32_t)LPDMA1_CH0,  /*!< LPDMA1 Channel 0 */
  HAL_LPDMA1_CH1  = (uint32_t)LPDMA1_CH1,  /*!< LPDMA1 Channel 1 */
  HAL_LPDMA1_CH2  = (uint32_t)LPDMA1_CH2,  /*!< LPDMA1 Channel 2 */
  HAL_LPDMA1_CH3  = (uint32_t)LPDMA1_CH3   /*!< LPDMA1 Channel 3 */
} hal_dma_channel_t;

/*! DMA channel state enumeration definition */
typedef enum
{
  HAL_DMA_STATE_RESET   = 0U,        /*!< DMA channel not initialized                    */
  HAL_DMA_STATE_INIT    = 1U << 31U, /*!< DMA channel initialized but not yet configured */
  HAL_DMA_STATE_IDLE    = 1U << 30U, /*!< DMA channel initialized and configured         */
  HAL_DMA_STATE_ACTIVE  = 1U << 29U, /*!< DMA channel transfer is ongoing                */
  HAL_DMA_STATE_SUSPEND = 1U << 28U, /*!< DMA channel transfer suspended                 */
  HAL_DMA_STATE_ABORT   = 1U << 27U  /*!< DMA channel transfer aborted                   */
} hal_dma_state_t;

/*! HAL DMA channel transfer level complete enumeration definition */
typedef enum
{
  HAL_DMA_XFER_FULL_COMPLETE = LL_DMA_FLAG_IDLE,                 /*!< Full channel transfer */
  HAL_DMA_XFER_HALF_COMPLETE = LL_DMA_FLAG_HT | LL_DMA_FLAG_IDLE /*!< Half channel transfer */
} hal_dma_xfer_level_t;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/*! DMA xfer mode enumeration definition */
typedef enum
{
  HAL_DMA_XFER_MODE_DIRECT              = 0x00U, /*!< DMA Direct mode               */
  HAL_DMA_XFER_MODE_LINKEDLIST_LINEAR   = 0x01U, /*!< DMA Linked-list linear mode   */
  HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR = 0x02U  /*!< DMA Linked-list circular mode */
} hal_dma_xfer_mode_t;
#endif /* USE_HAL_DMA_LINKEDLIST */

/*! HAL DMA channel requests enumeration definition */
typedef enum
{
  /* GPDMA1 requests */
  HAL_GPDMA1_REQUEST_ADC1         = LL_GPDMA1_REQUEST_ADC1,         /*!< GPDMA1 HW request is ADC1         */
  HAL_GPDMA1_REQUEST_ADC4         = LL_GPDMA1_REQUEST_ADC4,         /*!< GPDMA1 HW request is ADC4         */
  HAL_GPDMA1_REQUEST_DAC1_CH1     = LL_GPDMA1_REQUEST_DAC1_CH1,     /*!< GPDMA1 HW request is DAC1_CH1     */
  HAL_GPDMA1_REQUEST_DAC1_CH2     = LL_GPDMA1_REQUEST_DAC1_CH2,     /*!< GPDMA1 HW request is DAC1_CH2     */
  HAL_GPDMA1_REQUEST_TIM6_UPD     = LL_GPDMA1_REQUEST_TIM6_UPD,     /*!< GPDMA1 HW request is TIM6_UPD     */
  HAL_GPDMA1_REQUEST_TIM7_UPD     = LL_GPDMA1_REQUEST_TIM7_UPD,     /*!< GPDMA1 HW request is TIM7_UPD     */
  HAL_GPDMA1_REQUEST_SPI1_RX      = LL_GPDMA1_REQUEST_SPI1_RX,      /*!< GPDMA1 HW request is SPI1_RX      */
  HAL_GPDMA1_REQUEST_SPI1_TX      = LL_GPDMA1_REQUEST_SPI1_TX,      /*!< GPDMA1 HW request is SPI1_TX      */
  HAL_GPDMA1_REQUEST_SPI2_RX      = LL_GPDMA1_REQUEST_SPI2_RX,      /*!< GPDMA1 HW request is SPI2_RX      */
  HAL_GPDMA1_REQUEST_SPI2_TX      = LL_GPDMA1_REQUEST_SPI2_TX,      /*!< GPDMA1 HW request is SPI2_TX      */
  HAL_GPDMA1_REQUEST_SPI3_RX      = LL_GPDMA1_REQUEST_SPI3_RX,      /*!< GPDMA1 HW request is SPI3_RX      */
  HAL_GPDMA1_REQUEST_SPI3_TX      = LL_GPDMA1_REQUEST_SPI3_TX,      /*!< GPDMA1 HW request is SPI3_TX      */
  HAL_GPDMA1_REQUEST_I2C1_RX      = LL_GPDMA1_REQUEST_I2C1_RX,      /*!< GPDMA1 HW request is I2C1_RX      */
  HAL_GPDMA1_REQUEST_I2C1_TX      = LL_GPDMA1_REQUEST_I2C1_TX,      /*!< GPDMA1 HW request is I2C1_TX      */
  HAL_GPDMA1_REQUEST_I2C1_EVC     = LL_GPDMA1_REQUEST_I2C1_EVC,     /*!< GPDMA1 HW request is I2C1_EVC     */
  HAL_GPDMA1_REQUEST_I2C2_RX      = LL_GPDMA1_REQUEST_I2C2_RX,      /*!< GPDMA1 HW request is I2C2_RX      */
  HAL_GPDMA1_REQUEST_I2C2_TX      = LL_GPDMA1_REQUEST_I2C2_TX,      /*!< GPDMA1 HW request is I2C2_TX      */
  HAL_GPDMA1_REQUEST_I2C2_EVC     = LL_GPDMA1_REQUEST_I2C2_EVC,     /*!< GPDMA1 HW request is I2C2_EVC     */
  HAL_GPDMA1_REQUEST_I2C3_RX      = LL_GPDMA1_REQUEST_I2C3_RX,      /*!< GPDMA1 HW request is I2C3_RX      */
  HAL_GPDMA1_REQUEST_I2C3_TX      = LL_GPDMA1_REQUEST_I2C3_TX,      /*!< GPDMA1 HW request is I2C3_TX      */
  HAL_GPDMA1_REQUEST_I2C3_EVC     = LL_GPDMA1_REQUEST_I2C3_EVC,     /*!< GPDMA1 HW request is I2C3_EVC     */
  HAL_GPDMA1_REQUEST_I2C4_RX      = LL_GPDMA1_REQUEST_I2C4_RX,      /*!< GPDMA1 HW request is I2C4_RX      */
  HAL_GPDMA1_REQUEST_I2C4_TX      = LL_GPDMA1_REQUEST_I2C4_TX,      /*!< GPDMA1 HW request is I2C4_TX      */
  HAL_GPDMA1_REQUEST_I2C4_EVC     = LL_GPDMA1_REQUEST_I2C4_EVC,     /*!< GPDMA1 HW request is I2C4_EVC     */
  HAL_GPDMA1_REQUEST_USART1_RX    = LL_GPDMA1_REQUEST_USART1_RX,    /*!< GPDMA1 HW request is USART1_RX    */
  HAL_GPDMA1_REQUEST_USART1_TX    = LL_GPDMA1_REQUEST_USART1_TX,    /*!< GPDMA1 HW request is USART1_TX    */
#if defined (USART2)
  HAL_GPDMA1_REQUEST_USART2_RX    = LL_GPDMA1_REQUEST_USART2_RX,    /*!< GPDMA1 HW request is USART2_RX    */
  HAL_GPDMA1_REQUEST_USART2_TX    = LL_GPDMA1_REQUEST_USART2_TX,    /*!< GPDMA1 HW request is USART2_TX    */
#endif /* USART2 */
  HAL_GPDMA1_REQUEST_USART3_RX    = LL_GPDMA1_REQUEST_USART3_RX,    /*!< GPDMA1 HW request is USART3_RX    */
  HAL_GPDMA1_REQUEST_USART3_TX    = LL_GPDMA1_REQUEST_USART3_TX,    /*!< GPDMA1 HW request is USART3_TX    */
  HAL_GPDMA1_REQUEST_UART4_RX     = LL_GPDMA1_REQUEST_UART4_RX,     /*!< GPDMA1 HW request is UART4_RX     */
  HAL_GPDMA1_REQUEST_UART4_TX     = LL_GPDMA1_REQUEST_UART4_TX,     /*!< GPDMA1 HW request is UART4_TX     */
  HAL_GPDMA1_REQUEST_UART5_RX     = LL_GPDMA1_REQUEST_UART5_RX,     /*!< GPDMA1 HW request is UART5_RX     */
  HAL_GPDMA1_REQUEST_UART5_TX     = LL_GPDMA1_REQUEST_UART5_TX,     /*!< GPDMA1 HW request is UART5_TX     */
  HAL_GPDMA1_REQUEST_LPUART1_RX   = LL_GPDMA1_REQUEST_LPUART1_RX,   /*!< GPDMA1 HW request is LPUART1_RX   */
  HAL_GPDMA1_REQUEST_LPUART1_TX   = LL_GPDMA1_REQUEST_LPUART1_TX,   /*!< GPDMA1 HW request is LPUART1_TX   */
  HAL_GPDMA1_REQUEST_SAI1_A       = LL_GPDMA1_REQUEST_SAI1_A,       /*!< GPDMA1 HW request is SAI1_A       */
  HAL_GPDMA1_REQUEST_SAI1_B       = LL_GPDMA1_REQUEST_SAI1_B,       /*!< GPDMA1 HW request is SAI1_B       */
#if defined (SAI2)
  HAL_GPDMA1_REQUEST_SAI2_A       = LL_GPDMA1_REQUEST_SAI2_A,       /*!< GPDMA1 HW request is SAI2_A       */
  HAL_GPDMA1_REQUEST_SAI2_B       = LL_GPDMA1_REQUEST_SAI2_B,       /*!< GPDMA1 HW request is SAI2_B       */
#endif /* SAI2 */
  HAL_GPDMA1_REQUEST_OCTOSPI1     = LL_GPDMA1_REQUEST_OCTOSPI1,     /*!< GPDMA1 HW request is OCTOSPI1     */
#if defined (OCTOSPI2)
  HAL_GPDMA1_REQUEST_OCTOSPI2     = LL_GPDMA1_REQUEST_OCTOSPI2,     /*!< GPDMA1 HW request is OCTOSPI2     */
#endif /* OCTOSPI2 */
  HAL_GPDMA1_REQUEST_TIM1_CC1     = LL_GPDMA1_REQUEST_TIM1_CC1,     /*!< GPDMA1 HW request is TIM1_CC1     */
  HAL_GPDMA1_REQUEST_TIM1_CC2     = LL_GPDMA1_REQUEST_TIM1_CC2,     /*!< GPDMA1 HW request is TIM1_CC2     */
  HAL_GPDMA1_REQUEST_TIM1_CC3     = LL_GPDMA1_REQUEST_TIM1_CC3,     /*!< GPDMA1 HW request is TIM1_CC3     */
  HAL_GPDMA1_REQUEST_TIM1_CC4     = LL_GPDMA1_REQUEST_TIM1_CC4,     /*!< GPDMA1 HW request is TIM1_CC4     */
  HAL_GPDMA1_REQUEST_TIM1_UPD     = LL_GPDMA1_REQUEST_TIM1_UPD,     /*!< GPDMA1 HW request is TIM1_UPD     */
  HAL_GPDMA1_REQUEST_TIM1_TRGI    = LL_GPDMA1_REQUEST_TIM1_TRGI,    /*!< GPDMA1 HW request is TIM1_TRGI    */
  HAL_GPDMA1_REQUEST_TIM1_COM     = LL_GPDMA1_REQUEST_TIM1_COM,     /*!< GPDMA1 HW request is TIM1_COM     */
  HAL_GPDMA1_REQUEST_TIM8_CC1     = LL_GPDMA1_REQUEST_TIM8_CC1,     /*!< GPDMA1 HW request is TIM8_CC1     */
  HAL_GPDMA1_REQUEST_TIM8_CC2     = LL_GPDMA1_REQUEST_TIM8_CC2,     /*!< GPDMA1 HW request is TIM8_CC2     */
  HAL_GPDMA1_REQUEST_TIM8_CC3     = LL_GPDMA1_REQUEST_TIM8_CC3,     /*!< GPDMA1 HW request is TIM8_CC3     */
  HAL_GPDMA1_REQUEST_TIM8_CC4     = LL_GPDMA1_REQUEST_TIM8_CC4,     /*!< GPDMA1 HW request is TIM8_CC4     */
  HAL_GPDMA1_REQUEST_TIM8_UPD     = LL_GPDMA1_REQUEST_TIM8_UPD,     /*!< GPDMA1 HW request is TIM8_UPD     */
  HAL_GPDMA1_REQUEST_TIM8_TRGI    = LL_GPDMA1_REQUEST_TIM8_TRGI,    /*!< GPDMA1 HW request is TIM8_TRGI    */
  HAL_GPDMA1_REQUEST_TIM8_COM     = LL_GPDMA1_REQUEST_TIM8_COM,     /*!< GPDMA1 HW request is TIM8_COM     */
  HAL_GPDMA1_REQUEST_TIM2_CC1     = LL_GPDMA1_REQUEST_TIM2_CC1,     /*!< GPDMA1 HW request is TIM2_CC1     */
  HAL_GPDMA1_REQUEST_TIM2_CC2     = LL_GPDMA1_REQUEST_TIM2_CC2,     /*!< GPDMA1 HW request is TIM2_CC2     */
  HAL_GPDMA1_REQUEST_TIM2_CC3     = LL_GPDMA1_REQUEST_TIM2_CC3,     /*!< GPDMA1 HW request is TIM2_CC3     */
  HAL_GPDMA1_REQUEST_TIM2_CC4     = LL_GPDMA1_REQUEST_TIM2_CC4,     /*!< GPDMA1 HW request is TIM2_CC4     */
  HAL_GPDMA1_REQUEST_TIM2_UPD     = LL_GPDMA1_REQUEST_TIM2_UPD,     /*!< GPDMA1 HW request is TIM2_UPD     */
  HAL_GPDMA1_REQUEST_TIM3_CC1     = LL_GPDMA1_REQUEST_TIM3_CC1,     /*!< GPDMA1 HW request is TIM3_CC1     */
  HAL_GPDMA1_REQUEST_TIM3_CC2     = LL_GPDMA1_REQUEST_TIM3_CC2,     /*!< GPDMA1 HW request is TIM3_CC2     */
  HAL_GPDMA1_REQUEST_TIM3_CC3     = LL_GPDMA1_REQUEST_TIM3_CC3,     /*!< GPDMA1 HW request is TIM3_CC3     */
  HAL_GPDMA1_REQUEST_TIM3_CC4     = LL_GPDMA1_REQUEST_TIM3_CC4,     /*!< GPDMA1 HW request is TIM3_CC4     */
  HAL_GPDMA1_REQUEST_TIM3_UPD     = LL_GPDMA1_REQUEST_TIM3_UPD,     /*!< GPDMA1 HW request is TIM3_UPD     */
  HAL_GPDMA1_REQUEST_TIM3_TRGI    = LL_GPDMA1_REQUEST_TIM3_TRGI,    /*!< GPDMA1 HW request is TIM3_TRGI    */
  HAL_GPDMA1_REQUEST_TIM4_CC1     = LL_GPDMA1_REQUEST_TIM4_CC1,     /*!< GPDMA1 HW request is TIM4_CC1     */
  HAL_GPDMA1_REQUEST_TIM4_CC2     = LL_GPDMA1_REQUEST_TIM4_CC2,     /*!< GPDMA1 HW request is TIM4_CC2     */
  HAL_GPDMA1_REQUEST_TIM4_CC3     = LL_GPDMA1_REQUEST_TIM4_CC3,     /*!< GPDMA1 HW request is TIM4_CC3     */
  HAL_GPDMA1_REQUEST_TIM4_CC4     = LL_GPDMA1_REQUEST_TIM4_CC4,     /*!< GPDMA1 HW request is TIM4_CC4     */
  HAL_GPDMA1_REQUEST_TIM4_UPD     = LL_GPDMA1_REQUEST_TIM4_UPD,     /*!< GPDMA1 HW request is TIM4_UPD     */
  HAL_GPDMA1_REQUEST_TIM5_CC1     = LL_GPDMA1_REQUEST_TIM5_CC1,     /*!< GPDMA1 HW request is TIM5_CC1     */
  HAL_GPDMA1_REQUEST_TIM5_CC2     = LL_GPDMA1_REQUEST_TIM5_CC2,     /*!< GPDMA1 HW request is TIM5_CC2     */
  HAL_GPDMA1_REQUEST_TIM5_CC3     = LL_GPDMA1_REQUEST_TIM5_CC3,     /*!< GPDMA1 HW request is TIM5_CC3     */
  HAL_GPDMA1_REQUEST_TIM5_CC4     = LL_GPDMA1_REQUEST_TIM5_CC4,     /*!< GPDMA1 HW request is TIM5_CC4     */
  HAL_GPDMA1_REQUEST_TIM5_UPD     = LL_GPDMA1_REQUEST_TIM5_UPD,     /*!< GPDMA1 HW request is TIM5_UPD     */
  HAL_GPDMA1_REQUEST_TIM5_TRGI    = LL_GPDMA1_REQUEST_TIM5_TRGI,    /*!< GPDMA1 HW request is TIM5_TRGI    */
  HAL_GPDMA1_REQUEST_TIM15_CC1    = LL_GPDMA1_REQUEST_TIM15_CC1,    /*!< GPDMA1 HW request is TIM15_CC1    */
  HAL_GPDMA1_REQUEST_TIM15_UPD    = LL_GPDMA1_REQUEST_TIM15_UPD,    /*!< GPDMA1 HW request is TIM15_UPD    */
  HAL_GPDMA1_REQUEST_TIM15_TRGI   = LL_GPDMA1_REQUEST_TIM15_TRGI,   /*!< GPDMA1 HW request is TIM15_TRGI   */
  HAL_GPDMA1_REQUEST_TIM15_COM    = LL_GPDMA1_REQUEST_TIM15_COM,    /*!< GPDMA1 HW request is TIM15_COM    */
  HAL_GPDMA1_REQUEST_TIM16_CC1    = LL_GPDMA1_REQUEST_TIM16_CC1,    /*!< GPDMA1 HW request is TIM16_CC1    */
  HAL_GPDMA1_REQUEST_TIM16_UPD    = LL_GPDMA1_REQUEST_TIM16_UPD,    /*!< GPDMA1 HW request is TIM16_UPD    */
  HAL_GPDMA1_REQUEST_TIM17_CC1    = LL_GPDMA1_REQUEST_TIM17_CC1,    /*!< GPDMA1 HW request is TIM17_CC1    */
  HAL_GPDMA1_REQUEST_TIM17_UPD    = LL_GPDMA1_REQUEST_TIM17_UPD,    /*!< GPDMA1 HW request is TIM17_UPD    */
  HAL_GPDMA1_REQUEST_DCMI_PSSI    = LL_GPDMA1_REQUEST_DCMI_PSSI,    /*!< GPDMA1 HW request is DCMI_PSSI    */
  HAL_GPDMA1_REQUEST_AES_IN       = LL_GPDMA1_REQUEST_AES_IN,       /*!< GPDMA1 HW request is AES_IN       */
  HAL_GPDMA1_REQUEST_AES_OUT      = LL_GPDMA1_REQUEST_AES_OUT,      /*!< GPDMA1 HW request is AES_OUT      */
  HAL_GPDMA1_REQUEST_HASH_IN      = LL_GPDMA1_REQUEST_HASH_IN,      /*!< GPDMA1 HW request is HASH_IN      */
#if defined (UCPD1)
  HAL_GPDMA1_REQUEST_UCPD1_TX     = LL_GPDMA1_REQUEST_UCPD1_TX,     /*!< GPDMA1 HW request is UCPD1_TX     */
  HAL_GPDMA1_REQUEST_UCPD1_RX     = LL_GPDMA1_REQUEST_UCPD1_RX,     /*!< GPDMA1 HW request is UCPD1_RX     */
#endif /* UCPD1 */
  HAL_GPDMA1_REQUEST_MDF1_FLT0    = LL_GPDMA1_REQUEST_MDF1_FLT0,    /*!< GPDMA1 HW request is MDF1_FLT0    */
  HAL_GPDMA1_REQUEST_MDF1_FLT1    = LL_GPDMA1_REQUEST_MDF1_FLT1,    /*!< GPDMA1 HW request is MDF1_FLT1    */
  HAL_GPDMA1_REQUEST_MDF1_FLT2    = LL_GPDMA1_REQUEST_MDF1_FLT2,    /*!< GPDMA1 HW request is MDF1_FLT2    */
  HAL_GPDMA1_REQUEST_MDF1_FLT3    = LL_GPDMA1_REQUEST_MDF1_FLT3,    /*!< GPDMA1 HW request is MDF1_FLT3    */
  HAL_GPDMA1_REQUEST_MDF1_FLT4    = LL_GPDMA1_REQUEST_MDF1_FLT4,    /*!< GPDMA1 HW request is MDF1_FLT4    */
  HAL_GPDMA1_REQUEST_MDF1_FLT5    = LL_GPDMA1_REQUEST_MDF1_FLT5,    /*!< GPDMA1 HW request is MDF1_FLT5    */
  HAL_GPDMA1_REQUEST_ADF1_FLT0    = LL_GPDMA1_REQUEST_ADF1_FLT0,    /*!< GPDMA1 HW request is ADF1_FLT0    */
  HAL_GPDMA1_REQUEST_FMAC_RD      = LL_GPDMA1_REQUEST_FMAC_RD,      /*!< GPDMA1 HW request is FMAC_RD      */
  HAL_GPDMA1_REQUEST_FMAC_WR      = LL_GPDMA1_REQUEST_FMAC_WR,      /*!< GPDMA1 HW request is FMAC_WR      */
  HAL_GPDMA1_REQUEST_CORDIC_RD    = LL_GPDMA1_REQUEST_CORDIC_RD,    /*!< GPDMA1 HW request is CORDIC_RD    */
  HAL_GPDMA1_REQUEST_CORDIC_WR    = LL_GPDMA1_REQUEST_CORDIC_WR,    /*!< GPDMA1 HW request is CORDIC_WR    */
  HAL_GPDMA1_REQUEST_SAES_IN      = LL_GPDMA1_REQUEST_SAES_IN,      /*!< GPDMA1 HW request is SAES_IN      */
  HAL_GPDMA1_REQUEST_SAES_OUT     = LL_GPDMA1_REQUEST_SAES_OUT,     /*!< GPDMA1 HW request is SAES_OUT     */
  HAL_GPDMA1_REQUEST_LPTIM1_IC1   = LL_GPDMA1_REQUEST_LPTIM1_IC1,   /*!< GPDMA1 HW request is LPTIM1_IC1   */
  HAL_GPDMA1_REQUEST_LPTIM1_IC2   = LL_GPDMA1_REQUEST_LPTIM1_IC2,   /*!< GPDMA1 HW request is LPTIM1_IC2   */
  HAL_GPDMA1_REQUEST_LPTIM1_UE    = LL_GPDMA1_REQUEST_LPTIM1_UE,    /*!< GPDMA1 HW request is LPTIM1_UE    */
  HAL_GPDMA1_REQUEST_LPTIM2_IC1   = LL_GPDMA1_REQUEST_LPTIM2_IC1,   /*!< GPDMA1 HW request is LPTIM2_IC1   */
  HAL_GPDMA1_REQUEST_LPTIM2_IC2   = LL_GPDMA1_REQUEST_LPTIM2_IC2,   /*!< GPDMA1 HW request is LPTIM2_IC2   */
  HAL_GPDMA1_REQUEST_LPTIM2_UE    = LL_GPDMA1_REQUEST_LPTIM2_UE,    /*!< GPDMA1 HW request is LPTIM2_UE    */
  HAL_GPDMA1_REQUEST_LPTIM3_IC1   = LL_GPDMA1_REQUEST_LPTIM3_IC1,   /*!< GPDMA1 HW request is LPTIM3_IC1   */
  HAL_GPDMA1_REQUEST_LPTIM3_IC2   = LL_GPDMA1_REQUEST_LPTIM3_IC2,   /*!< GPDMA1 HW request is LPTIM3_IC2   */
  HAL_GPDMA1_REQUEST_LPTIM3_UE    = LL_GPDMA1_REQUEST_LPTIM3_UE,    /*!< GPDMA1 HW request is LPTIM3_UE    */
#if defined (HSPI1_BASE)
  HAL_GPDMA1_REQUEST_HSPI1        = LL_GPDMA1_REQUEST_HSPI1,        /*!< GPDMA1 HW request is HSPI1        */
#endif /* defined (HSPI1_BASE) */
#if defined (I2C5)
  HAL_GPDMA1_REQUEST_I2C5_RX      = LL_GPDMA1_REQUEST_I2C5_RX,      /*!< GPDMA1 HW request is I2C5_RX      */
  HAL_GPDMA1_REQUEST_I2C5_TX      = LL_GPDMA1_REQUEST_I2C5_TX,      /*!< GPDMA1 HW request is I2C5_TX      */
  HAL_GPDMA1_REQUEST_I2C5_EVC     = LL_GPDMA1_REQUEST_I2C5_EVC,     /*!< GPDMA1 HW request is I2C5_EVC     */
#endif /* defined (I2C5) */
#if defined (I2C6)
  HAL_GPDMA1_REQUEST_I2C6_RX      = LL_GPDMA1_REQUEST_I2C6_RX,      /*!< GPDMA1 HW request is I2C6_RX      */
  HAL_GPDMA1_REQUEST_I2C6_TX      = LL_GPDMA1_REQUEST_I2C6_TX,      /*!< GPDMA1 HW request is I2C6_TX      */
  HAL_GPDMA1_REQUEST_I2C6_EVC     = LL_GPDMA1_REQUEST_I2C6_EVC,     /*!< GPDMA1 HW request is I2C6_EVC     */
#endif /* defined (I2C6) */
#if defined (USART6)
  HAL_GPDMA1_REQUEST_USART6_RX    = LL_GPDMA1_REQUEST_USART6_RX,    /*!< GPDMA1 HW request is USART6_RX    */
  HAL_GPDMA1_REQUEST_USART6_TX    = LL_GPDMA1_REQUEST_USART6_TX,    /*!< GPDMA1 HW request is USART6_TX    */
#endif /* defined (USART6) */
#if defined (ADC2)
  HAL_GPDMA1_REQUEST_ADC2         = LL_GPDMA1_REQUEST_ADC2,         /*!< GPDMA1 HW request is ADC2         */
#endif /* defined (ADC2) */
#if defined (JPEG)
  HAL_GPDMA1_REQUEST_JPEG_RX      = LL_GPDMA1_REQUEST_JPEG_RX,      /*!< GPDMA1 HW request is JPEG_TX      */
  HAL_GPDMA1_REQUEST_JPEG_TX      = LL_GPDMA1_REQUEST_JPEG_TX,      /*!< GPDMA1 HW request is JPEG_RX      */
#endif /* defined (JPEG) */

  /* LPDMA1 requests */
  HAL_LPDMA1_REQUEST_LPUART1_RX   = LL_LPDMA1_REQUEST_LPUART1_RX,   /*!< LPDMA1 HW request is LPUART1_RX   */
  HAL_LPDMA1_REQUEST_LPUART1_TX   = LL_LPDMA1_REQUEST_LPUART1_TX,   /*!< LPDMA1 HW request is LPUART1_TX   */
  HAL_LPDMA1_REQUEST_SPI3_RX      = LL_LPDMA1_REQUEST_SPI3_RX,      /*!< LPDMA1 HW request is SPI3_RX      */
  HAL_LPDMA1_REQUEST_SPI3_TX      = LL_LPDMA1_REQUEST_SPI3_TX,      /*!< LPDMA1 HW request is SPI3_TX      */
  HAL_LPDMA1_REQUEST_I2C3_RX      = LL_LPDMA1_REQUEST_I2C3_RX,      /*!< LPDMA1 HW request is I2C3_RX      */
  HAL_LPDMA1_REQUEST_I2C3_TX      = LL_LPDMA1_REQUEST_I2C3_TX,      /*!< LPDMA1 HW request is I2C3_TX      */
  HAL_LPDMA1_REQUEST_I2C3_EVC     = LL_LPDMA1_REQUEST_I2C3_EVC,     /*!< LPDMA1 HW request is I2C3_EVC     */
  HAL_LPDMA1_REQUEST_ADC4         = LL_LPDMA1_REQUEST_ADC4,         /*!< LPDMA1 HW request is ADC4         */
  HAL_LPDMA1_REQUEST_DAC1_CH1     = LL_LPDMA1_REQUEST_DAC1_CH1,     /*!< LPDMA1 HW request is DAC1_CH1     */
  HAL_LPDMA1_REQUEST_DAC1_CH2     = LL_LPDMA1_REQUEST_DAC1_CH2,     /*!< LPDMA1 HW request is DAC1_CH2     */
  HAL_LPDMA1_REQUEST_ADF1_FLT0    = LL_LPDMA1_REQUEST_ADF1_FLT0,    /*!< LPDMA1 HW request is ADF1_FLT0    */
  HAL_LPDMA1_REQUEST_LPTIM1_IC1   = LL_LPDMA1_REQUEST_LPTIM1_IC1,   /*!< LPDMA1 HW request is LPTIM1_IC1   */
  HAL_LPDMA1_REQUEST_LPTIM1_IC2   = LL_LPDMA1_REQUEST_LPTIM1_IC2,   /*!< LPDMA1 HW request is LPTIM1_IC2   */
  HAL_LPDMA1_REQUEST_LPTIM1_UE    = LL_LPDMA1_REQUEST_LPTIM1_UE,    /*!< LPDMA1 HW request is LPTIM1_UE    */
  HAL_LPDMA1_REQUEST_LPTIM3_IC1   = LL_LPDMA1_REQUEST_LPTIM3_IC1,   /*!< LPDMA1 HW request is LPTIM3_IC1   */
  HAL_LPDMA1_REQUEST_LPTIM3_IC2   = LL_LPDMA1_REQUEST_LPTIM3_IC2,   /*!< LPDMA1 HW request is LPTIM3_IC2   */
  HAL_LPDMA1_REQUEST_LPTIM3_UE    = LL_LPDMA1_REQUEST_LPTIM3_UE,    /*!< LPDMA1 HW request is LPTIM3_UE    */

  /* Software request */
  HAL_DMA_REQUEST_SW              = DMA_CTR2_SWREQ                  /*!< DMA SW request                    */
} hal_dma_request_source_t;

/*! DMA channel mode enumeration definition */
typedef enum
{
  HAL_DMA_HARDWARE_REQUEST_BURST = LL_DMA_HARDWARE_REQUEST_BURST, /*!< DMA burst request transfer */
  HAL_DMA_HARDWARE_REQUEST_BLOCK = LL_DMA_HARDWARE_REQUEST_BLOCK  /*!< DMA block request transfer */
} hal_dma_hardware_request_mode_t;

/*! DMA channel direction enumeration definition */
typedef enum
{
  HAL_DMA_DIRECTION_MEMORY_TO_MEMORY = LL_DMA_DIRECTION_MEMORY_TO_MEMORY, /*!< Memory to memory direction     */
  HAL_DMA_DIRECTION_PERIPH_TO_MEMORY = LL_DMA_DIRECTION_PERIPH_TO_MEMORY, /*!< Peripheral to memory direction */
  HAL_DMA_DIRECTION_MEMORY_TO_PERIPH = LL_DMA_DIRECTION_MEMORY_TO_PERIPH  /*!< Memory to peripheral direction */
} hal_dma_direction_t;

/*! DMA channel source increment enumeration definition */
typedef enum
{
  HAL_DMA_SRC_ADDR_FIXED       = LL_DMA_SRC_ADDR_FIXED,       /*!< Source fixed single / burst       */
  HAL_DMA_SRC_ADDR_INCREMENTED = LL_DMA_SRC_ADDR_INCREMENTED  /*!< Source incremented single / burst */
} hal_dma_src_addr_increment_t;

/*! DMA channel destination increment enumeration definition */
typedef enum
{
  HAL_DMA_DEST_ADDR_FIXED       = LL_DMA_DEST_ADDR_FIXED,       /*!< Destination fixed single / burst       */
  HAL_DMA_DEST_ADDR_INCREMENTED = LL_DMA_DEST_ADDR_INCREMENTED  /*!< Destination incremented single / burst */
} hal_dma_dest_addr_increment_t;

/*! DMA channel source data width enumeration definition */
typedef enum
{
  HAL_DMA_SRC_DATA_WIDTH_BYTE       = LL_DMA_SRC_DATA_WIDTH_BYTE,      /*!< Source data width : Byte       */
  HAL_DMA_SRC_DATA_WIDTH_HALFWORD   = LL_DMA_SRC_DATA_WIDTH_HALFWORD,  /*!< Source data width : HalfWord   */
  HAL_DMA_SRC_DATA_WIDTH_WORD       = LL_DMA_SRC_DATA_WIDTH_WORD,      /*!< Source data width : Word       */
} hal_dma_src_data_width_t;

/*! DMA channel destination data width enumeration definition */
typedef enum
{
  HAL_DMA_DEST_DATA_WIDTH_BYTE       = LL_DMA_DEST_DATA_WIDTH_BYTE,      /*!< Destination data width : Byte       */
  HAL_DMA_DEST_DATA_WIDTH_HALFWORD   = LL_DMA_DEST_DATA_WIDTH_HALFWORD,  /*!< Destination data width : HalfWord   */
  HAL_DMA_DEST_DATA_WIDTH_WORD       = LL_DMA_DEST_DATA_WIDTH_WORD,      /*!< Destination data width : Word       */
} hal_dma_dest_data_width_t;

/*! DMA channel priority enumeration definition */
typedef enum
{
  HAL_DMA_PRIORITY_LOW_WEIGHT_LOW  = LL_DMA_PRIORITY_LOW_WEIGHT_LOW,  /*!< Priority level : Low Priority, Low weight  */
  HAL_DMA_PRIORITY_LOW_WEIGHT_MID  = LL_DMA_PRIORITY_LOW_WEIGHT_MID,  /*!< Priority level : Low Priority, Mid weight  */
  HAL_DMA_PRIORITY_LOW_WEIGHT_HIGH = LL_DMA_PRIORITY_LOW_WEIGHT_HIGH, /*!< Priority level : Low Priority, High weight */
  HAL_DMA_PRIORITY_HIGH            = LL_DMA_PRIORITY_HIGH             /*!< Priority level : High Priority             */
} hal_dma_priority_t;

/*! DMA channel transfer configuration structure definition */
typedef struct
{
  hal_dma_request_source_t      request;         /*!< DMA channel transfer request           */
  hal_dma_direction_t           direction;       /*!< DMA channel transfer direction         */
  hal_dma_src_addr_increment_t  src_inc;         /*!< DMA channel source increment mode      */
  hal_dma_dest_addr_increment_t dest_inc;        /*!< DMA channel destination increment mode */
  hal_dma_src_data_width_t      src_data_width;  /*!< DMA channel source data width          */
  hal_dma_dest_data_width_t     dest_data_width; /*!< DMA channel destination data width     */
  hal_dma_priority_t            priority;        /*!< DMA channel priority level             */
} hal_dma_direct_xfer_config_t;

/*! DMA channel port enumeration definition */
typedef enum
{
  HAL_DMA_PORT0 = 0x0U, /*!< DMA channel Port 0 */
  HAL_DMA_PORT1 = 0x1U  /*!< DMA channel Port 1 */
} hal_dma_port_t;

/*! HAL DMA channel trigger hardware signal enumeration definition */
typedef enum
{
  /* GPDMA1 triggers */
  HAL_GPDMA1_TRIGGER_EXTI0           = LL_GPDMA1_TRIGGER_EXTI0,           /*!< GPDMA1 HW Trigger is EXTI0           */
  HAL_GPDMA1_TRIGGER_EXTI1           = LL_GPDMA1_TRIGGER_EXTI1,           /*!< GPDMA1 HW Trigger is EXTI1           */
  HAL_GPDMA1_TRIGGER_EXTI2           = LL_GPDMA1_TRIGGER_EXTI2,           /*!< GPDMA1 HW Trigger is EXTI2           */
  HAL_GPDMA1_TRIGGER_EXTI3           = LL_GPDMA1_TRIGGER_EXTI3,           /*!< GPDMA1 HW Trigger is EXTI3           */
  HAL_GPDMA1_TRIGGER_EXTI4           = LL_GPDMA1_TRIGGER_EXTI4,           /*!< GPDMA1 HW Trigger is EXTI4           */
  HAL_GPDMA1_TRIGGER_EXTI5           = LL_GPDMA1_TRIGGER_EXTI5,           /*!< GPDMA1 HW Trigger is EXTI5           */
  HAL_GPDMA1_TRIGGER_EXTI6           = LL_GPDMA1_TRIGGER_EXTI6,           /*!< GPDMA1 HW Trigger is EXTI6           */
  HAL_GPDMA1_TRIGGER_EXTI7           = LL_GPDMA1_TRIGGER_EXTI7,           /*!< GPDMA1 HW Trigger is EXTI7           */
  HAL_GPDMA1_TRIGGER_TAMP_TRG1       = LL_GPDMA1_TRIGGER_TAMP_TRG1,       /*!< GPDMA1 HW Trigger is TAMP_TRG1       */
  HAL_GPDMA1_TRIGGER_TAMP_TRG2       = LL_GPDMA1_TRIGGER_TAMP_TRG2,       /*!< GPDMA1 HW Trigger is TAMP_TRG2       */
  HAL_GPDMA1_TRIGGER_TAMP_TRG3       = LL_GPDMA1_TRIGGER_TAMP_TRG3,       /*!< GPDMA1 HW Trigger is TAMP_TRG3       */
  HAL_GPDMA1_TRIGGER_LPTIM1_CH1      = LL_GPDMA1_TRIGGER_LPTIM1_CH1,      /*!< GPDMA1 HW Trigger is LPTIM1_CH1      */
  HAL_GPDMA1_TRIGGER_LPTIM1_CH2      = LL_GPDMA1_TRIGGER_LPTIM1_CH2,      /*!< GPDMA1 HW Trigger is LPTIM1_CH2      */
  HAL_GPDMA1_TRIGGER_LPTIM2_CH1      = LL_GPDMA1_TRIGGER_LPTIM2_CH1,      /*!< GPDMA1 HW Trigger is LPTIM2_CH1      */
  HAL_GPDMA1_TRIGGER_LPTIM2_CH2      = LL_GPDMA1_TRIGGER_LPTIM2_CH2,      /*!< GPDMA1 HW Trigger is LPTIM2_CH2      */
  HAL_GPDMA1_TRIGGER_LPTIM4_OUT      = LL_GPDMA1_TRIGGER_LPTIM4_OUT,      /*!< GPDMA1 HW Trigger is LPTIM4_OUT      */
  HAL_GPDMA1_TRIGGER_COMP1_OUT       = LL_GPDMA1_TRIGGER_COMP1_OUT,       /*!< GPDMA1 HW Trigger is COMP1_OUT       */
  HAL_GPDMA1_TRIGGER_COMP2_OUT       = LL_GPDMA1_TRIGGER_COMP2_OUT,       /*!< GPDMA1 HW Trigger is COMP2_OUT       */
  HAL_GPDMA1_TRIGGER_RTC_ALRA_TRG    = LL_GPDMA1_TRIGGER_RTC_ALRA_TRG,    /*!< GPDMA1 HW Trigger is RTC_ALRA_TRG    */
  HAL_GPDMA1_TRIGGER_RTC_ALRB_TRG    = LL_GPDMA1_TRIGGER_RTC_ALRB_TRG,    /*!< GPDMA1 HW Trigger is RTC_ALRB_TRG    */
  HAL_GPDMA1_TRIGGER_RTC_WUT_TRG     = LL_GPDMA1_TRIGGER_RTC_WUT_TRG,     /*!< GPDMA1 HW Trigger is RTC_WUT_TRG     */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH0_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH0_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH0_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH1_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH1_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH1_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH2_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH2_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH2_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH3_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH3_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH3_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH4_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH4_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH4_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH5_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH5_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH5_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH6_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH6_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH6_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH7_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH7_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH7_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH8_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH8_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH8_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH9_TC   = LL_GPDMA1_TRIGGER_GPDMA1_CH9_TC,   /*!< GPDMA1 HW Trigger is GPDMA1_CH9_TC   */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH10_TC  = LL_GPDMA1_TRIGGER_GPDMA1_CH10_TC,  /*!< GPDMA1 HW Trigger is GPDMA1_CH10_TC  */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH11_TC  = LL_GPDMA1_TRIGGER_GPDMA1_CH11_TC,  /*!< GPDMA1 HW Trigger is GPDMA1_CH11_TC  */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH12_TC  = LL_GPDMA1_TRIGGER_GPDMA1_CH12_TC,  /*!< GPDMA1 HW Trigger is GPDMA1_CH12_TC  */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH13_TC  = LL_GPDMA1_TRIGGER_GPDMA1_CH13_TC,  /*!< GPDMA1 HW Trigger is GPDMA1_CH13_TC  */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH14_TC  = LL_GPDMA1_TRIGGER_GPDMA1_CH14_TC,  /*!< GPDMA1 HW Trigger is GPDMA1_CH14_TC  */
  HAL_GPDMA1_TRIGGER_GPDMA1_CH15_TC  = LL_GPDMA1_TRIGGER_GPDMA1_CH15_TC,  /*!< GPDMA1 HW Trigger is GPDMA1_CH15_TC  */
  HAL_GPDMA1_TRIGGER_LPDMA1_CH0_TC   = LL_GPDMA1_TRIGGER_LPDMA1_CH0_TC,   /*!< GPDMA1 HW Trigger is LPDMA1_CH0_TC   */
  HAL_GPDMA1_TRIGGER_LPDMA1_CH1_TC   = LL_GPDMA1_TRIGGER_LPDMA1_CH1_TC,   /*!< GPDMA1 HW Trigger is LPDMA1_CH1_TC   */
  HAL_GPDMA1_TRIGGER_LPDMA1_CH2_TC   = LL_GPDMA1_TRIGGER_LPDMA1_CH2_TC,   /*!< GPDMA1 HW Trigger is LPDMA1_CH2_TC   */
  HAL_GPDMA1_TRIGGER_LPDMA1_CH3_TC   = LL_GPDMA1_TRIGGER_LPDMA1_CH3_TC,   /*!< GPDMA1 HW Trigger is LPDMA1_CH3_TC   */
  HAL_GPDMA1_TRIGGER_TIM2_TRGO       = LL_GPDMA1_TRIGGER_TIM2_TRGO,       /*!< GPDMA1 HW Trigger is TIM2_TRGO       */
  HAL_GPDMA1_TRIGGER_TIM15_TRGO      = LL_GPDMA1_TRIGGER_TIM15_TRGO,      /*!< GPDMA1 HW Trigger is TIM15_TRGO      */
#if defined (TIM3_TRGO_TRIGGER_SUPPORT)
  HAL_GPDMA1_TRIGGER_TIM3_TRGO       = LL_GPDMA1_TRIGGER_TIM3_TRGO,       /*!< GPDMA1 HW Trigger is TIM3_TRGO       */
#endif /* defined (TIM3_TRGO_TRIGGER_SUPPORT) */
#if defined (TIM4_TRGO_TRIGGER_SUPPORT)
  HAL_GPDMA1_TRIGGER_TIM4_TRGO       = LL_GPDMA1_TRIGGER_TIM4_TRGO,       /*!< GPDMA1 HW Trigger is TIM4_TRGO       */
#endif /* defined (TIM4_TRGO_TRIGGER_SUPPORT) */
#if defined (TIM5_TRGO_TRIGGER_SUPPORT)
  HAL_GPDMA1_TRIGGER_TIM5_TRGO       = LL_GPDMA1_TRIGGER_TIM5_TRGO,       /*!< GPDMA1 HW Trigger is TIM5_TRGO       */
#endif /* defined (TIM5_TRGO_TRIGGER_SUPPORT) */
#if defined (LTDC)
  HAL_GPDMA1_TRIGGER_LTDC_LI         = LL_GPDMA1_TRIGGER_LTDC_LI,        /*!< GPDMA1 HW Trigger is LTDC_LI         */
#endif /* defined (LTDC) */
#if defined (DSI)
  HAL_GPDMA1_TRIGGER_DSI_TE          = LL_GPDMA1_TRIGGER_DSI_TE,         /*!< GPDMA1 HW Trigger is DSI_TE          */
  HAL_GPDMA1_TRIGGER_DSI_ER          = LL_GPDMA1_TRIGGER_DSI_ER,         /*!< GPDMA1 HW Trigger is DSI_ER          */
#endif /* defined (DSI) */
#if defined (DMA2D_TRIGGER_SUPPORT)
  HAL_GPDMA1_TRIGGER_DMA2D_TC        = LL_GPDMA1_TRIGGER_DMA2D_TC,        /*!< GPDMA1 HW Trigger is DMA2D_TC        */
  HAL_GPDMA1_TRIGGER_DMA2D_CTC       = LL_GPDMA1_TRIGGER_DMA2D_CTC,       /*!< GPDMA1 HW Trigger is DMA2D_CTC       */
  HAL_GPDMA1_TRIGGER_DMA2D_TW        = LL_GPDMA1_TRIGGER_DMA2D_TW,        /*!< GPDMA1 HW Trigger is DMA2D_TW        */
#endif /* defined (DMA2D_TRIGGER_SUPPORT) */
#if defined (GPU2D)
  HAL_GPDMA1_TRIGGER_GPU2D_FLAG0     = LL_GPDMA1_TRIGGER_GPU2D_FLAG0,     /*!< GPDMA1 HW Trigger is GPU2D_FLAG0     */
  HAL_GPDMA1_TRIGGER_GPU2D_FLAG1     = LL_GPDMA1_TRIGGER_GPU2D_FLAG1,     /*!< GPDMA1 HW Trigger is GPU2D_FLAG1     */
  HAL_GPDMA1_TRIGGER_GPU2D_FLAG2     = LL_GPDMA1_TRIGGER_GPU2D_FLAG2,     /*!< GPDMA1 HW Trigger is GPU2D_FLAG2     */
  HAL_GPDMA1_TRIGGER_GPU2D_FLAG3     = LL_GPDMA1_TRIGGER_GPU2D_FLAG3,     /*!< GPDMA1 HW Trigger is GPU2D_FLAG3     */
#endif /* defined (GPU2D) */
  HAL_GPDMA1_TRIGGER_ADC4_AWD1       = LL_GPDMA1_TRIGGER_ADC4_AWD1,       /*!< GPDMA1 HW Trigger is ADC4_AWD1       */
  HAL_GPDMA1_TRIGGER_ADC1_AWD1       = LL_GPDMA1_TRIGGER_ADC1_AWD1,       /*!< GPDMA1 HW Trigger is ADC1_AWD1       */
#if defined (GFXTIM)
  HAL_GPDMA1_TRIGGER_GFXTIM_EVT4     = LL_GPDMA1_TRIGGER_GFXTIM_EVT4,     /*!< GPDMA1 HW Trigger is GFXTIM_EVT4     */
  HAL_GPDMA1_TRIGGER_GFXTIM_EVT3     = LL_GPDMA1_TRIGGER_GFXTIM_EVT3,     /*!< GPDMA1 HW Trigger is GFXTIM_EVT3     */
  HAL_GPDMA1_TRIGGER_GFXTIM_EVT2     = LL_GPDMA1_TRIGGER_GFXTIM_EVT2,     /*!< GPDMA1 HW Trigger is GFXTIM_EVT2     */
  HAL_GPDMA1_TRIGGER_GFXTIM_EVT1     = LL_GPDMA1_TRIGGER_GFXTIM_EVT1,     /*!< GPDMA1 HW Trigger is GFXTIM_EVT1     */
#endif /* defined (GFXTIM) */
#if defined (JPEG)
  HAL_GPDMA1_TRIGGER_JPEG_EOC_TRG    = LL_GPDMA1_TRIGGER_JPEG_EOC_TRG,    /*!< GPDMA1 HW Trigger is JPEG_EOC_TRG    */
  HAL_GPDMA1_TRIGGER_JPEG_IFNF_TRG   = LL_GPDMA1_TRIGGER_JPEG_IFNF_TRG,   /*!< GPDMA1 HW Trigger is JPEG_IFNF_TRG   */
  HAL_GPDMA1_TRIGGER_JPEG_IFT_TRG    = LL_GPDMA1_TRIGGER_JPEG_IFT_TRG,    /*!< GPDMA1 HW Trigger is JPEG_IFT_TRG    */
  HAL_GPDMA1_TRIGGER_JPEG_OFNE_TRG   = LL_GPDMA1_TRIGGER_JPEG_OFNE_TRG,   /*!< GPDMA1 HW Trigger is JPEG_OFNE_TRG   */
  HAL_GPDMA1_TRIGGER_JPEG_OFT_TRG    = LL_GPDMA1_TRIGGER_JPEG_OFT_TRG,    /*!< GPDMA1 HW Trigger is JPEG_OFT_TRG    */
#endif /* defined (JPEG) */

  /* LPDMA1 triggers */
  HAL_LPDMA1_TRIGGER_EXTI0           = LL_LPDMA1_TRIGGER_EXTI0,           /*!< LPDMA1 HW Trigger is EXTI0           */
  HAL_LPDMA1_TRIGGER_EXTI1           = LL_LPDMA1_TRIGGER_EXTI1,           /*!< LPDMA1 HW Trigger is EXTI1           */
  HAL_LPDMA1_TRIGGER_EXTI2           = LL_LPDMA1_TRIGGER_EXTI2,           /*!< LPDMA1 HW Trigger is EXTI2           */
  HAL_LPDMA1_TRIGGER_EXTI3           = LL_LPDMA1_TRIGGER_EXTI3,           /*!< LPDMA1 HW Trigger is EXTI3           */
  HAL_LPDMA1_TRIGGER_EXTI4           = LL_LPDMA1_TRIGGER_EXTI4,           /*!< LPDMA1 HW Trigger is EXTI4           */
  HAL_LPDMA1_TRIGGER_TAMP_TRG1       = LL_LPDMA1_TRIGGER_TAMP_TRG1,       /*!< LPDMA1 HW Trigger is TAMP_TRG1       */
  HAL_LPDMA1_TRIGGER_TAMP_TRG2       = LL_LPDMA1_TRIGGER_TAMP_TRG2,       /*!< LPDMA1 HW Trigger is TAMP_TRG2       */
  HAL_LPDMA1_TRIGGER_TAMP_TRG3       = LL_LPDMA1_TRIGGER_TAMP_TRG3,       /*!< LPDMA1 HW Trigger is TAMP_TRG3       */
  HAL_LPDMA1_TRIGGER_LPTIM1_CH1      = LL_LPDMA1_TRIGGER_LPTIM1_CH1,      /*!< LPDMA1 HW Trigger is LPTIM1_CH1      */
  HAL_LPDMA1_TRIGGER_LPTIM1_CH2      = LL_LPDMA1_TRIGGER_LPTIM1_CH2,      /*!< LPDMA1 HW Trigger is LPTIM1_CH2      */
  HAL_LPDMA1_TRIGGER_LPTIM3_CH1      = LL_LPDMA1_TRIGGER_LPTIM3_CH1,      /*!< LPDMA1 HW Trigger is LPTIM3_CH1      */
  HAL_LPDMA1_TRIGGER_LPTIM4_OUT      = LL_LPDMA1_TRIGGER_LPTIM4_OUT,      /*!< LPDMA1 HW Trigger is LPTIM4_OUT      */
  HAL_LPDMA1_TRIGGER_COMP1_OUT       = LL_LPDMA1_TRIGGER_COMP1_OUT,       /*!< LPDMA1 HW Trigger is COMP1_OUT       */
  HAL_LPDMA1_TRIGGER_COMP2_OUT       = LL_LPDMA1_TRIGGER_COMP2_OUT,       /*!< LPDMA1 HW Trigger is COMP2_OUT       */
  HAL_LPDMA1_TRIGGER_RTC_ALRA_TRG    = LL_LPDMA1_TRIGGER_RTC_ALRA_TRG,    /*!< LPDMA1 HW Trigger is RTC_ALRA_TRG    */
  HAL_LPDMA1_TRIGGER_RTC_ALRB_TRG    = LL_LPDMA1_TRIGGER_RTC_ALRB_TRG,    /*!< LPDMA1 HW Trigger is RTC_ALRB_TRG    */
  HAL_LPDMA1_TRIGGER_RTC_WUT_TRG     = LL_LPDMA1_TRIGGER_RTC_WUT_TRG,     /*!< LPDMA1 HW Trigger is RTC_WUT_TRG     */
  HAL_LPDMA1_TRIGGER_ADC4_AWD1       = LL_LPDMA1_TRIGGER_ADC4_AWD1,       /*!< LPDMA1 HW Trigger is ADC4_AWD1       */
  HAL_LPDMA1_TRIGGER_LPDMA1_CH0_TC   = LL_LPDMA1_TRIGGER_LPDMA1_CH0_TC,   /*!< LPDMA1 HW Trigger is LPDMA1_CH0_TC   */
  HAL_LPDMA1_TRIGGER_LPDMA1_CH1_TC   = LL_LPDMA1_TRIGGER_LPDMA1_CH1_TC,   /*!< LPDMA1 HW Trigger is LPDMA1_CH1_TC   */
  HAL_LPDMA1_TRIGGER_LPDMA1_CH2_TC   = LL_LPDMA1_TRIGGER_LPDMA1_CH2_TC,   /*!< LPDMA1 HW Trigger is LPDMA1_CH2_TC   */
  HAL_LPDMA1_TRIGGER_LPDMA1_CH3_TC   = LL_LPDMA1_TRIGGER_LPDMA1_CH3_TC,   /*!< LPDMA1 HW Trigger is LPDMA1_CH3_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH0_TC   = LL_LPDMA1_TRIGGER_GPDMA1_CH0_TC,   /*!< LPDMA1 HW Trigger is GPDMA1_CH0_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH1_TC   = LL_LPDMA1_TRIGGER_GPDMA1_CH1_TC,   /*!< LPDMA1 HW Trigger is GPDMA1_CH1_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH4_TC   = LL_LPDMA1_TRIGGER_GPDMA1_CH4_TC,   /*!< LPDMA1 HW Trigger is GPDMA1_CH4_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH5_TC   = LL_LPDMA1_TRIGGER_GPDMA1_CH5_TC,   /*!< LPDMA1 HW Trigger is GPDMA1_CH5_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH6_TC   = LL_LPDMA1_TRIGGER_GPDMA1_CH6_TC,   /*!< LPDMA1 HW Trigger is GPDMA1_CH6_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH7_TC   = LL_LPDMA1_TRIGGER_GPDMA1_CH7_TC,   /*!< LPDMA1 HW Trigger is GPDMA1_CH7_TC   */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH12_TC  = LL_LPDMA1_TRIGGER_GPDMA1_CH12_TC,  /*!< LPDMA1 HW Trigger is GPDMA1_CH12_TC  */
  HAL_LPDMA1_TRIGGER_GPDMA1_CH13_TC  = LL_LPDMA1_TRIGGER_GPDMA1_CH13_TC,  /*!< LPDMA1 HW Trigger is GPDMA1_CH13_TC  */
  HAL_LPDMA1_TRIGGER_TIM2_TRGO       = LL_LPDMA1_TRIGGER_TIM2_TRGO,       /*!< LPDMA1 HW Trigger is TIM2_TRGO       */
  HAL_LPDMA1_TRIGGER_TIM15_TRGO      = LL_LPDMA1_TRIGGER_TIM15_TRGO       /*!< LPDMA1 HW Trigger is TIM15_TRGO      */
} hal_dma_trigger_source_t;

/*! DMA channel trigger polarity enumeration definition */
typedef enum
{
  HAL_DMA_TRIGGER_POLARITY_MASKED  = LL_DMA_TRIGGER_POLARITY_MASKED,  /*!< No trigger of the selected DMA request.
                                                                           Masked trigger event                      */
  HAL_DMA_TRIGGER_POLARITY_RISING  = LL_DMA_TRIGGER_POLARITY_RISING,  /*!< Trigger of the selected DMA request on the
                                                                           rising edge of the selected trigger event
                                                                           input                                     */
  HAL_DMA_TRIGGER_POLARITY_FALLING = LL_DMA_TRIGGER_POLARITY_FALLING  /*!< Trigger of the selected DMA request on the
                                                                           falling edge of the selected trigger event
                                                                           input                                     */
} hal_dma_trigger_polarity_t;

/*! DMA channel trigger mode enumeration definition */
typedef enum
{
  HAL_DMA_TRIGGER_BLOCK_TRANSFER          = LL_DMA_TRIGGER_BLOCK_TRANSFER,         /*!< A block transfer is conditioned
                                                                                        by (at least) one hit trigger */
  HAL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER = LL_DMA_TRIGGER_REPEATED_BLOCK_TRANSFER, /*!< A repeated block transfer is
                                                                                         conditioned by (at least) one
                                                                                         hit trigger                  */
  HAL_DMA_TRIGGER_NODE_TRANSFER           = LL_DMA_TRIGGER_NODE_TRANSFER,     /*!< A LLI link transfer is conditioned by
                                                                                   (at least) one hit trigger         */
  HAL_DMA_TRIGGER_SINGLE_BURST_TRANSFER   = LL_DMA_TRIGGER_SINGLE_BURST_TRANSFER  /*!< A single/burst transfer is
                                                                                       conditioned by (at least) one hit
                                                                                       trigger                        */
} hal_dma_trigger_mode_t;

/*! DMA channel trigger configuration structure definition */
typedef struct
{
  hal_dma_trigger_source_t   source;   /*!< DMA channel trigger event source selection */
  hal_dma_trigger_polarity_t polarity; /*!< DMA channel trigger event polarity         */
  hal_dma_trigger_mode_t     mode;     /*!< DMA channel trigger mode                   */
} hal_dma_trigger_config_t;

/*! DMA channel data source byte exchange enumeration definition */
typedef enum
{
  HAL_DMA_SRC_BYTE_PRESERVED = LL_DMA_SRC_BYTE_PRESERVED, /*!< No byte-based exchange within the unaligned half-word of
                                                               each source word                                       */
  HAL_DMA_SRC_BYTE_EXCHANGED = LL_DMA_SRC_BYTE_EXCHANGED  /*!< The two consecutive bytes within the unaligned half-word
                                                               of each source word are exchanged.                     */
} hal_dma_src_byte_exchange_t;

/*! DMA channel data destination byte exchange enumeration definition */
typedef enum
{
  HAL_DMA_DEST_BYTE_PRESERVED = LL_DMA_DEST_BYTE_PRESERVED, /*!< When destination data width > Byte, no byte-based
                                                                 exchange within half-word.                           */
  HAL_DMA_DEST_BYTE_EXCHANGED = LL_DMA_DEST_BYTE_EXCHANGED  /*!< When destination data width > Byte, the two consecutive
                                                                 bytes are exchanged in each destination half-word.   */
} hal_dma_dest_byte_exchange_t;

/*! DMA channel data destination half word exchange enumeration definition */
typedef enum
{
  HAL_DMA_DEST_HALFWORD_PRESERVED = LL_DMA_DEST_HALFWORD_PRESERVED, /*!< When destination data width > Half-Word,
                                                                         no half-word-based exchange within word.     */
  HAL_DMA_DEST_HALFWORD_EXCHANGED = LL_DMA_DEST_HALFWORD_EXCHANGED  /*!< When destination data width > Half-Word, The
                                                                         two consecutive half-words are exchanged in
                                                                         each destination word.                       */
} hal_dma_dest_halfword_exchange_t;

/*! DMA channel destination data truncation and padding enumeration definition */
typedef enum
{
  HAL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO  = LL_DMA_DEST_DATA_TRUNC_LEFT_PADD_ZERO,  /*!< Destination data left
                                                                                         truncation zero padding  */
  HAL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN = LL_DMA_DEST_DATA_TRUNC_RIGHT_PADD_SIGN  /*!< Destination data right
                                                                                         truncation sign padding  */
} hal_dma_dest_data_trunc_padd_t;

/*! DMA channel destination data packing enumeration definition */
typedef enum
{
  HAL_DMA_DEST_DATA_PRESERVED       = LL_DMA_DEST_DATA_PRESERVED,         /*!< Destination data packing preserved */
  HAL_DMA_DEST_DATA_PACKED_UNPACKED = LL_DMA_DEST_DATA_PACKED_UNPACKED    /*!< Destination data packing unpacked  */
} hal_dma_dest_data_pack_t;

/*! DMA channel data handling configuration structure definition */
typedef struct
{
  hal_dma_src_byte_exchange_t      src_byte_exchange;      /*!< DMA channel source byte exchange mode           */
  hal_dma_dest_byte_exchange_t     dest_byte_exchange;     /*!< DMA channel destination byte exchange mode      */
  hal_dma_dest_halfword_exchange_t dest_halfword_exchange; /*!< DMA channel destination half-word exchange mode */
  hal_dma_dest_data_trunc_padd_t   trunc_padd;             /*!< DMA channel data truncation or padding mode     */
  hal_dma_dest_data_pack_t         pack;                   /*!< DMA channel data packing or unpacking mode      */
} hal_dma_data_handling_config_t;

/*! DMA channel burst source address increment enumeration definition */
typedef enum
{
  HAL_DMA_BURST_SRC_ADDR_INCREMENTED = LL_DMA_BURST_SRC_ADDR_INCREMENTED, /*!< Burst source address incremented */
  HAL_DMA_BURST_SRC_ADDR_DECREMENTED = LL_DMA_BURST_SRC_ADDR_DECREMENTED  /*!< Burst source address decremented */
} hal_dma_burst_src_increment_t;

/*! DMA channel burst destination address increment enumeration definition */
typedef enum
{
  HAL_DMA_BURST_DEST_ADDR_INCREMENTED = LL_DMA_BURST_DEST_ADDR_INCREMENTED,/*!< Burst destination address incremented */
  HAL_DMA_BURST_DEST_ADDR_DECREMENTED = LL_DMA_BURST_DEST_ADDR_DECREMENTED /*!< Burst destination address decremented */
} hal_dma_burst_dest_increment_t;

/*! DMA channel block source address increment enumeration definition */
typedef enum
{
  HAL_DMA_BLOCK_SRC_ADDR_INCREMENTED = LL_DMA_BLOCK_SRC_ADDR_INCREMENTED, /*!< Block source address incremented */
  HAL_DMA_BLOCK_SRC_ADDR_DECREMENTED = LL_DMA_BLOCK_SRC_ADDR_DECREMENTED  /*!< Block source address decremented */
} hal_dma_block_src_increment_t;

/*! DMA channel block destination address increment enumeration definition */
typedef enum
{
  HAL_DMA_BLOCK_DEST_ADDR_INCREMENTED = LL_DMA_BLOCK_DEST_ADDR_INCREMENTED,/*!< Block destination address incremented */
  HAL_DMA_BLOCK_DEST_ADDR_DECREMENTED = LL_DMA_BLOCK_DEST_ADDR_DECREMENTED /*!< Block destination address decremented */
} hal_dma_block_dest_increment_t;

/*! DMA channel half transfer and transfer complete event generation enumeration definition */
typedef enum
{
  HAL_DMA_DIRECT_XFER_EVENT_BLOCK          = LL_DMA_DIRECT_XFER_EVENT_BLOCK,/*!< The TC event is generated at the end of
                                                                                each block and the HT event is generated
                                                                                at the half of each block             */
  HAL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK = LL_DMA_DIRECT_XFER_EVENT_REPEATED_BLOCK  /*!< The TC event is generated at
                                                                                           the end of the repeated block
                                                                                           and the HT event is generated
                                                                                           at the half of the repeated
                                                                                           block                      */
} hal_dma_direct_xfer_event_mode_t;

/*! DMA channel repeated block configuration structure definition */
typedef struct
{
  uint32_t                         block_count;            /*!< DMA channel block count                             */
  uint32_t                         burst_src_offset_byte;  /*!< DMA channel single/burst source address offset      */
  uint32_t                         burst_dest_offset_byte; /*!< DMA channel single/burst destination address offset */
  uint32_t                         block_src_offset_byte;  /*!< DMA channel block source address offset             */
  uint32_t                         block_dest_offset_byte; /*!< DMA channel block destination address offset        */
  hal_dma_burst_src_increment_t    burst_src_inc;          /*!< DMA channel single/burst source address inc         */
  hal_dma_burst_dest_increment_t   burst_dest_inc;         /*!< DMA channel single/burst destination address inc    */
  hal_dma_block_src_increment_t    block_src_inc;          /*!< DMA channel block source address increment          */
  hal_dma_block_dest_increment_t   block_dest_inc;         /*!< DMA channel block destination address increment     */
  hal_dma_direct_xfer_event_mode_t xfer_event_mode;        /*!< DMA channel transfer event mode                     */
} hal_dma_repeat_block_config_t;

/*! DMA channel security attribute enumeration definition */
typedef enum
{
  HAL_DMA_ATTR_NSEC = LL_DMA_ATTR_NSEC, /*!< Non-secure attribute */
  HAL_DMA_ATTR_SEC  = LL_DMA_ATTR_SEC   /*!< Secure attribute     */
} hal_dma_sec_attr_t;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/*! DMA channel half transfer and transfer complete event generation enumeration definition */
typedef enum
{
  HAL_DMA_LINKEDLIST_XFER_EVENT_BLOCK          = LL_DMA_LINKEDLIST_XFER_EVENT_BLOCK,   /*!< The TC event is generated at
                                                                                        the end of each block and the HT
                                                                                        event is generated at the half
                                                                                        of each block                 */
  HAL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK = LL_DMA_LINKEDLIST_XFER_EVENT_REPEATED_BLOCK, /*!< The TC event is
                                                                                         generated at the end of the
                                                                                         repeated block and the HT event
                                                                                         is generated at the half of the
                                                                                         repeated block               */
  HAL_DMA_LINKEDLIST_XFER_EVENT_NODE           = LL_DMA_LINKEDLIST_XFER_EVENT_NODE,/*!< The TC event is generated at the
                                                                                        end of each linked-list item and
                                                                                        the HT event is generated at the
                                                                                        half of each linked-list item */
  HAL_DMA_LINKEDLIST_XFER_EVENT_Q              = LL_DMA_LINKEDLIST_XFER_EVENT_Q    /*!< The TC event is generated at the
                                                                                        end of the last linked-list item
                                                                                        and the HT event is generated at
                                                                                        the half of the last linked-list
                                                                                        item                          */
} hal_dma_linkedlist_xfer_event_mode_t;

/*! DMA channel linked-list configuration structure definition */
typedef struct
{
  hal_dma_priority_t                   priority;   /*!< DMA channel priority level             */
  hal_dma_port_t                       fetch_port; /*!< DMA channel linked-list allocated port */
  hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode; /*!< DMA channel transfer event mode        */
} hal_dma_linkedlist_xfer_config_t;

/*! DMA channel linked-list execution enumeration definition */
typedef enum
{
  HAL_DMA_LINKEDLIST_EXECUTION_Q    = LL_DMA_LINKEDLIST_EXECUTION_Q,   /*!< Channel executed for the full linked-list */
  HAL_DMA_LINKEDLIST_EXECUTION_NODE = LL_DMA_LINKEDLIST_EXECUTION_NODE /*!< Channel executed once for the current LLI */
} hal_dma_linkedlist_execution_mode_t;

/*! DMA channel node configuration enumeration definition */
typedef struct
{
  hal_dma_direct_xfer_config_t         xfer;                    /*!< DMA Channel direct transfer configuration    */
  hal_dma_hardware_request_mode_t      hw_request_mode;         /*!< DMA channel hardware request mode            */
  hal_dma_port_t                       src_port;                /*!< DMA Channel source port                      */
  hal_dma_port_t                       dest_port;               /*!< DMA Channel destination port                 */
  uint32_t                             src_burst_length_byte;   /*!< DMA Channel source burst length in byte      */
  uint32_t                             dest_burst_length_byte;  /*!< DMA Channel destination burst length in byte */
  hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode;         /*!< DMA Channel transfer event mode              */
  hal_dma_trigger_config_t             trigger;                 /*!< DMA Channel trigger configuration            */
  hal_dma_data_handling_config_t       data_handling;           /*!< DMA Channel data handling configuration      */
  hal_dma_repeat_block_config_t        repeat_block;            /*!< DMA Channel repeated block configuration     */
  uint32_t                             src_addr;                /*!< DMA Channel source address                   */
  uint32_t                             dest_addr;               /*!< DMA Channel destination address              */
  uint32_t                             size_byte;               /*!< DMA Channel size in byte                     */
  hal_dma_sec_attr_t                   channel_src_sec;         /*!< DMA Channel source security attribute        */
  hal_dma_sec_attr_t                   channel_dest_sec;        /*!< DMA Channel destination security attribute   */
} hal_dma_node_config_t;

/*! DMA channel node type enumeration definition */
typedef enum
{
  HAL_DMA_NODE_LINEAR_ADDRESSING = 0x05U, /*!< Linear addressing DMA node */
  HAL_DMA_NODE_2D_ADDRESSING     = 0x07U  /*!< 2D addressing DMA node     */
} hal_dma_node_type_t;

/*! DMA linked-list node structure definition */
typedef struct
{
  uint32_t regs[LL_DMA_NODE_REGISTER_NUM]; /*!< Specifies the physical DMA channel node registers description */
  uint32_t info;                           /*!< Specified the physical DMA channel node information           */
} hal_dma_node_t;
#endif /* USE_HAL_DMA_LINKEDLIST */

typedef struct hal_dma_handle_s hal_dma_handle_t; /*!< HAL DMA channel handle structure type */

/*! DMA channel process callback type definition */
typedef void (*hal_dma_cb_t)(hal_dma_handle_t *hdma);

/*! HAL DMA channel handle Structure definition */
struct hal_dma_handle_s
{
  hal_dma_channel_t                instance;          /*!< DMA channel instance                        */
  void                             *p_parent;         /*!< DMA channel parent                          */
  volatile hal_dma_state_t         global_state;      /*!< DMA channel transfer state                  */
  uint32_t                         block_size_byte;   /*!< DMA channel transfer block size             */
#if defined(USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
  volatile uint32_t                last_error_codes; /*!< DMA channel transfer error codes             */
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
  volatile hal_dma_xfer_mode_t     xfer_mode;         /*!< DMA channel transfer mode                   */
  hal_dma_node_t                   *p_head_node;      /*!< DMA channel q                               */
#endif /* USE_HAL_DMA_LINKEDLIST */
  hal_dma_cb_t p_xfer_halfcplt_cb;                    /*!< DMA channel half transfer complete callback */
  hal_dma_cb_t p_xfer_cplt_cb;                        /*!< DMA channel transfer complete callback      */
  hal_dma_cb_t p_xfer_abort_cb;                       /*!< DMA channel transfer Abort callback         */
  hal_dma_cb_t p_xfer_suspend_cb;                     /*!< DMA channel transfer Suspend callback       */
  hal_dma_cb_t p_xfer_error_cb;                       /*!< DMA channel transfer error callback         */
#if defined(USE_HAL_DMA_USER_DATA) && (USE_HAL_DMA_USER_DATA == 1)
  const void                        *p_user_data;     /*!< DMA channel user data                       */
#endif /* USE_HAL_DMA_USER_DATA */
};
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Functions DMA Exported Functions
  * @{
  */

/** @defgroup DMA_Exported_Functions_Group1 Initialization and De-initialization functions
  * @{
  */
/* Initialization and Deinitialization APIs */
hal_status_t HAL_DMA_Init(hal_dma_handle_t *hdma, hal_dma_channel_t instance);
void HAL_DMA_DeInit(hal_dma_handle_t *hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group2 Configuration functions
  * @{
  */
/* Direct xfer config APIs */
hal_status_t HAL_DMA_SetConfigDirectXfer(hal_dma_handle_t *hdma, const hal_dma_direct_xfer_config_t *p_config);
void HAL_DMA_GetConfigDirectXfer(hal_dma_handle_t *hdma, hal_dma_direct_xfer_config_t *p_config);

/* Hardware request mode config APIs */
hal_status_t HAL_DMA_SetConfigDirectXferHardwareRequestMode(hal_dma_handle_t *hdma,
                                                            hal_dma_hardware_request_mode_t hw_request_mode);
hal_status_t HAL_DMA_ResetConfigDirectXferHardwareRequestMode(hal_dma_handle_t *hdma);
hal_dma_hardware_request_mode_t HAL_DMA_GetConfigDirectXferHardwareRequestMode(hal_dma_handle_t *hdma);

/* Transfer ports config APIs */
hal_status_t HAL_DMA_SetConfigDirectXferPort(hal_dma_handle_t *hdma, hal_dma_port_t src_port, hal_dma_port_t dest_port);
hal_status_t HAL_DMA_ResetConfigDirectXferPort(hal_dma_handle_t *hdma);
void HAL_DMA_GetConfigDirectXferPort(hal_dma_handle_t *hdma, hal_dma_port_t *p_src_port, hal_dma_port_t *p_dest_port);

/* Burst config APIs */
hal_status_t HAL_DMA_SetConfigDirectXferBurst(hal_dma_handle_t *hdma, uint32_t src_burst_length_byte,
                                              uint32_t dest_burst_length_byte);
hal_status_t HAL_DMA_ResetConfigDirectXferBurst(hal_dma_handle_t *hdma);
void HAL_DMA_GetConfigDirectXferBurst(hal_dma_handle_t *hdma, uint32_t *p_src_burst_length_byte,
                                      uint32_t *p_dest_burst_length_byte);

/* Trigger config APIs */
hal_status_t HAL_DMA_SetConfigDirectXferTrigger(hal_dma_handle_t *hdma, const hal_dma_trigger_config_t *p_config);
hal_status_t HAL_DMA_ResetConfigDirectXferTrigger(hal_dma_handle_t *hdma);
void HAL_DMA_GetConfigDirectXferTrigger(hal_dma_handle_t *hdma, hal_dma_trigger_config_t *p_config);

/* Data handling config APIs */
hal_status_t HAL_DMA_SetConfigDirectXferDataHandling(hal_dma_handle_t *hdma,
                                                     const hal_dma_data_handling_config_t *p_config);
hal_status_t HAL_DMA_ResetConfigDirectXferDataHandling(hal_dma_handle_t *hdma);
void HAL_DMA_GetConfigDirectXferDataHandling(hal_dma_handle_t *hdma, hal_dma_data_handling_config_t *p_config);

/* Repeated block config APIs */
hal_status_t HAL_DMA_SetConfigDirectXferRepeatBlock(hal_dma_handle_t *hdma,
                                                    const hal_dma_repeat_block_config_t *p_config);
hal_status_t HAL_DMA_ResetConfigDirectXferRepeatBlock(hal_dma_handle_t *hdma);
void HAL_DMA_GetConfigDirectXferRepeatBlock(hal_dma_handle_t *hdma, hal_dma_repeat_block_config_t *p_config);

/* Security access attributes config APIs */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
hal_status_t HAL_DMA_SetConfigAccessAttributes(hal_dma_handle_t *hdma, hal_dma_sec_attr_t src_attr,
                                               hal_dma_sec_attr_t dest_attr);
hal_status_t HAL_DMA_ResetConfigAccessAttributes(hal_dma_handle_t *hdma);
#endif /* __ARM_FEATURE_CMSE */
void HAL_DMA_GetConfigAccessAttributes(hal_dma_handle_t *hdma, hal_dma_sec_attr_t *p_src_attr,
                                       hal_dma_sec_attr_t *p_dest_attr);

/* Direct periph xfer config APIs */
hal_status_t HAL_DMA_SetConfigPeriphDirectXfer(hal_dma_handle_t *hdma, const hal_dma_direct_xfer_config_t *p_config);
void HAL_DMA_GetConfigPeriphDirectXfer(hal_dma_handle_t *hdma, hal_dma_direct_xfer_config_t *p_config);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/* Linked list xfer config APIs */
hal_status_t HAL_DMA_SetConfigLinkedListXfer(hal_dma_handle_t *hdma, const hal_dma_linkedlist_xfer_config_t *p_config);
void HAL_DMA_GetConfigLinkedListXfer(hal_dma_handle_t *hdma, hal_dma_linkedlist_xfer_config_t *p_config);

/* Linked list xfer event mode config APIs */
hal_status_t HAL_DMA_SetLinkedListXferEventMode(hal_dma_handle_t *hdma,
                                                hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode);
hal_status_t HAL_DMA_ResetLinkedListXferEventMode(hal_dma_handle_t *hdma);
hal_dma_linkedlist_xfer_event_mode_t HAL_DMA_GetLinkedListXferEventMode(hal_dma_handle_t *hdma);

/* Linked list xfer fetch node port APIs */
hal_status_t HAL_DMA_SetLinkedListXferFetchNodePort(hal_dma_handle_t *hdma, hal_dma_port_t fetch_port);
hal_status_t HAL_DMA_ResetLinkedListXferFetchNodePort(hal_dma_handle_t *hdma);
hal_dma_port_t HAL_DMA_GetLinkedListXferFetchNodePort(hal_dma_handle_t *hdma);

/* Linked list xfer channel priority APIs */
hal_status_t HAL_DMA_SetLinkedListXferPriority(hal_dma_handle_t *hdma, hal_dma_priority_t priority);
hal_status_t HAL_DMA_ResetLinkedListXferPriority(hal_dma_handle_t *hdma);
hal_dma_priority_t HAL_DMA_GetLinkedListXferPriority(hal_dma_handle_t *hdma);

/* Linked list xfer execution mode APIs */
hal_status_t HAL_DMA_SetLinkedListXferExecutionMode(hal_dma_handle_t *hdma,
                                                    hal_dma_linkedlist_execution_mode_t exec_mode);
hal_status_t HAL_DMA_ResetLinkedListXferExecutionMode(hal_dma_handle_t *hdma);
hal_dma_linkedlist_execution_mode_t HAL_DMA_GetLinkedListXferExecutionMode(hal_dma_handle_t *hdma);

/* Linked list circular periph xfer config APIs */
hal_status_t HAL_DMA_SetConfigPeriphLinkedListCircularXfer(hal_dma_handle_t *hdma, hal_dma_node_t *p_node,
                                                           const hal_dma_direct_xfer_config_t *p_node_config);
void HAL_DMA_GetConfigPeriphLinkedListCircularXfer(hal_dma_handle_t *hdma, hal_dma_node_t *p_node,
                                                   hal_dma_direct_xfer_config_t *p_node_config);
#endif /* USE_HAL_DMA_LINKEDLIST */
/**
  * @}
  */

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/** @defgroup DMA_Exported_Functions_Group3 Linked-list node management functions
  * @{
  */
/* Node building APIs */
hal_status_t HAL_DMA_FillNodeConfig(hal_dma_node_t *p_node, const hal_dma_node_config_t *p_conf,
                                    hal_dma_node_type_t node_type);
void HAL_DMA_GetNodeConfig(const hal_dma_node_t *p_node, hal_dma_node_config_t *p_conf,
                           hal_dma_node_type_t *p_node_type);

hal_status_t HAL_DMA_FillNodeDirectXfer(hal_dma_node_t *p_node, const hal_dma_direct_xfer_config_t *p_config,
                                        hal_dma_node_type_t node_type);
void HAL_DMA_GetNodeDirectXfer(const hal_dma_node_t *p_node, hal_dma_direct_xfer_config_t *p_config,
                               hal_dma_node_type_t *p_node_type);

hal_status_t HAL_DMA_FillNodeHardwareRequestMode(hal_dma_node_t *p_node,
                                                 hal_dma_hardware_request_mode_t hw_request_mode);
hal_dma_hardware_request_mode_t HAL_DMA_GetNodeHardwareRequestMode(const hal_dma_node_t *p_node);

hal_status_t HAL_DMA_FillNodePort(hal_dma_node_t *p_node, hal_dma_port_t src_port, hal_dma_port_t dest_port);
void HAL_DMA_GetNodePort(const hal_dma_node_t *p_node, hal_dma_port_t *p_src_port, hal_dma_port_t *p_dest_port);

hal_status_t HAL_DMA_FillNodeBurst(hal_dma_node_t *p_node, uint32_t src_burst_length_byte,
                                   uint32_t dest_burst_length_byte);
void HAL_DMA_GetNodeBurst(const hal_dma_node_t *p_node, uint32_t *p_src_burst_length_byte,
                          uint32_t *p_dest_burst_length_byte);

hal_status_t HAL_DMA_FillNodeXferEventMode(hal_dma_node_t *p_node,
                                           hal_dma_linkedlist_xfer_event_mode_t xfer_event_mode);
hal_dma_linkedlist_xfer_event_mode_t HAL_DMA_GetNodeXferEventMode(const hal_dma_node_t *p_node);

hal_status_t HAL_DMA_FillNodeTrigger(hal_dma_node_t *p_node, const hal_dma_trigger_config_t *p_config);
void HAL_DMA_GetNodeTrigger(const hal_dma_node_t *p_node, hal_dma_trigger_config_t *p_config);

hal_status_t HAL_DMA_FillNodeDataHandling(hal_dma_node_t *p_node, const hal_dma_data_handling_config_t *p_config);
void HAL_DMA_GetNodeDataHandling(const hal_dma_node_t *p_node, hal_dma_data_handling_config_t *p_config);

hal_status_t HAL_DMA_FillNodeRepeatBlock(hal_dma_node_t *p_node, const hal_dma_repeat_block_config_t *p_config);
void HAL_DMA_GetNodeRepeatBlock(const hal_dma_node_t *p_node, hal_dma_repeat_block_config_t *p_config);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
hal_status_t HAL_DMA_FillNodeAccessAttributes(hal_dma_node_t *p_node, hal_dma_sec_attr_t src_attr,
                                              hal_dma_sec_attr_t dest_attr);
#endif /* __ARM_FEATURE_CMSE */
void HAL_DMA_GetNodeAccessAttributes(const hal_dma_node_t *p_node, hal_dma_sec_attr_t *p_src_attr,
                                     hal_dma_sec_attr_t *p_dest_attr);

hal_status_t HAL_DMA_FillNodeData(hal_dma_node_t *p_node, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte);
void HAL_DMA_GetNodeData(const hal_dma_node_t *p_node, uint32_t *p_src_addr, uint32_t *p_dest_addr,
                         uint32_t *p_size_byte);

/* Conversion queue APIs */
hal_status_t HAL_DMA_ConvertQNodesToDynamic(hal_q_t *p_q);
hal_status_t HAL_DMA_ConvertQNodesToStatic(hal_q_t *p_q);
/**
  * @}
  */
#endif /* USE_HAL_DMA_LINKEDLIST */

/** @defgroup DMA_Exported_Functions_Group4 Process management functions
  * @{
  */
/* Start APIs */
hal_status_t HAL_DMA_StartDirectXfer(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr, uint32_t size_byte);
hal_status_t HAL_DMA_StartDirectXfer_IT(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr,
                                        uint32_t size_byte);
hal_status_t HAL_DMA_StartDirectXfer_IT_Opt(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr,
                                            uint32_t size_byte, uint32_t interrupts);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
hal_status_t HAL_DMA_StartLinkedListXfer(hal_dma_handle_t *hdma, const hal_q_t *p_q);
hal_status_t HAL_DMA_StartLinkedListXfer_IT(hal_dma_handle_t *hdma, const hal_q_t *p_q);
hal_status_t HAL_DMA_StartLinkedListXfer_IT_Opt(hal_dma_handle_t *hdma, const hal_q_t *p_q, uint32_t interrupts);
#endif /* USE_HAL_DMA_LINKEDLIST */

/* Abort APIs */
hal_status_t HAL_DMA_Abort(hal_dma_handle_t *hdma);
hal_status_t HAL_DMA_Abort_IT(hal_dma_handle_t *hdma);

/* Suspend and resume APIs */
hal_status_t HAL_DMA_Suspend(hal_dma_handle_t *hdma);
hal_status_t HAL_DMA_Suspend_IT(hal_dma_handle_t *hdma);
hal_status_t HAL_DMA_Resume(hal_dma_handle_t *hdma);

/* Polling for transfer API */
hal_status_t HAL_DMA_PollForXfer(hal_dma_handle_t *hdma, hal_dma_xfer_level_t xfer_level, uint32_t timeout_msec);

/* IRQHandler API */
void HAL_DMA_IRQHandler(hal_dma_handle_t *hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group5 Callbacks functions
  * @{
  */
/* Register callback APIs */
hal_status_t HAL_DMA_RegisterXferHalfCpltCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback);
hal_status_t HAL_DMA_RegisterXferCpltCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback);
hal_status_t HAL_DMA_RegisterXferAbortCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback);
hal_status_t HAL_DMA_RegisterXferSuspendCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback);
hal_status_t HAL_DMA_RegisterXferErrorCallback(hal_dma_handle_t *hdma, hal_dma_cb_t callback);

/* Callbacks APIs */
void HAL_DMA_XferHalfCpltCallback(hal_dma_handle_t *hdma);
void HAL_DMA_XferCpltCallback(hal_dma_handle_t *hdma);
void HAL_DMA_XferAbortCallback(hal_dma_handle_t *hdma);
void HAL_DMA_XferSuspendCallback(hal_dma_handle_t *hdma);
void HAL_DMA_XferErrorCallback(hal_dma_handle_t *hdma);

#if defined(USE_HAL_DMA_USER_DATA) && (USE_HAL_DMA_USER_DATA == 1)
void HAL_DMA_SetUserData(hal_dma_handle_t *hdma, const void *p_user_data);
const void *HAL_DMA_GetUserData(const hal_dma_handle_t *hdma);
#endif /* USE_HAL_DMA_USER_DATA */
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group6 Status functions
  * @{
  */
/* Get transfer data APIs */
uint32_t HAL_DMA_GetFifoDataByte(const hal_dma_handle_t *hdma);
uint32_t HAL_DMA_GetDirectXferRemainingDataByte(const hal_dma_handle_t *hdma);

/* State APIs */
hal_dma_state_t HAL_DMA_GetState(const hal_dma_handle_t *hdma);

#if defined(USE_HAL_DMA_GET_LAST_ERRORS) && (USE_HAL_DMA_GET_LAST_ERRORS == 1)
uint32_t HAL_DMA_GetLastErrorCodes(const hal_dma_handle_t *hdma);
#endif /* USE_HAL_DMA_GET_LAST_ERRORS */
/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Functions DMA Private Functions
  * @{
  */
hal_status_t HAL_DMA_StartPeriphXfer_IT_Opt(hal_dma_handle_t *hdma, uint32_t src_addr, uint32_t dest_addr,
                                            uint32_t size_byte, uint32_t interrupts);

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/**
  * @brief Get a Node information for a DMA channel 2D addressing
  * @param p_next_offset_addr next node address offset
  * @param p_addressing_mode  node addressing mode
  */
__STATIC_INLINE void HAL_DMA_2DAddr_GetNodeInfo(uint32_t *p_next_offset_addr,
                                                hal_q_addressing_mode_t *p_addressing_mode)
{
  *p_next_offset_addr = (uint32_t)LL_DMA_NODE_2D_ADDRESSING_OFFSET;
  *p_addressing_mode  = HAL_Q_ADDRESSING_DIRECT;
}

/**
  * @brief Get Node information for a DMA channel linear addressing
  * @param p_next_offset_addr next node address offset
  * @param p_addressing_mode  node addressing mode
  */
__STATIC_INLINE void HAL_DMA_LinearAddr_GetNodeInfo(uint32_t *p_next_offset_addr,
                                                    hal_q_addressing_mode_t *p_addressing_mode)
{
  *p_next_offset_addr = (uint32_t)LL_DMA_NODE_LINEAR_ADDRESSING_OFFSET;
  *p_addressing_mode  = HAL_Q_ADDRESSING_DIRECT;
}

/**
  * @brief Set DMA node address
  * @param head_node_addr   Head node address
  * @param prev_node_addr   Previous node address
  * @param next_node_addr   Next node address
  * @param node_addr_offset Node address offset
  */
__STATIC_INLINE void HAL_DMA_SetNodeAddress(uint32_t head_node_addr, uint32_t prev_node_addr, uint32_t next_node_addr,
                                            uint32_t node_addr_offset)
{
  STM32_UNUSED(head_node_addr);

  uint32_t update_bits = LL_DMA_UPDATE_CTR1 | LL_DMA_UPDATE_CTR2 | LL_DMA_UPDATE_CBR1 |
                         LL_DMA_UPDATE_CSAR | LL_DMA_UPDATE_CDAR | LL_DMA_UPDATE_CLLR;

  if (node_addr_offset == LL_DMA_NODE_2D_ADDRESSING_OFFSET)
  {
    update_bits |= LL_DMA_UPDATE_CBR2 | LL_DMA_UPDATE_CTR3;
  }

  MODIFY_REG((*(uint32_t *)(prev_node_addr + node_addr_offset)), (update_bits | DMA_CLLR_LA),
             (next_node_addr & DMA_CLLR_LA) | update_bits);
}

/**
  * @brief  Get DMA node address
  * @param  head_node_addr    Head node address
  * @param  current_node_addr Current node address
  * @param  node_addr_offset  Node address offset
  * @retval uint32_t          DMA node address
  */
__STATIC_INLINE uint32_t HAL_DMA_GetNodeAddress(uint32_t head_node_addr, uint32_t current_node_addr,
                                                uint32_t node_addr_offset)
{
  STM32_UNUSED(head_node_addr);

  return (((uint32_t)current_node_addr & DMA_CLBAR_LBA) \
          + (*(uint32_t *)(((uint32_t)current_node_addr) + node_addr_offset) & DMA_CLLR_LA));
}
#endif /* USE_HAL_DMA_LINKEDLIST */
/**
  * @}
  */

/* Exported variables ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Variables DMA Exported Variables
  * @{
  */
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1)
/*! HAL DMA 2D addressing operation descriptor variables definition */
static const hal_q_desc_ops_t HAL_DMA_2DAddressing_DescOps =
{
  HAL_DMA_2DAddr_GetNodeInfo,
  HAL_DMA_SetNodeAddress,
  HAL_DMA_GetNodeAddress
};

/*!  HAL DMA linear addressing operation descriptor variables definition */
static const hal_q_desc_ops_t HAL_DMA_LinearAddressing_DescOps =
{
  HAL_DMA_LinearAddr_GetNodeInfo,
  HAL_DMA_SetNodeAddress,
  HAL_DMA_GetNodeAddress
};
#endif /* USE_HAL_DMA_LINKEDLIST */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5XX_HAL_DMA_H */
