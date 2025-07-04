/**
  *********************************************************************************************************************
  * @file    stm32u5xx_hal_pssi.h
  * @brief   Header file of PSSI HAL module.
  *********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *********************************************************************************************************************
  */

/* Define to prevent recursive inclusion ----------------------------------------------------------------------------*/
#ifndef STM32U5XX_HAL_PSSI_H
#define STM32U5XX_HAL_PSSI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
#if defined(PSSI)
/** @defgroup PSSI PSSI
  * @{
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup PSSI_Exported_Constants PSSI Exported Constants
  * @{
  */

/** @defgroup PSSI_Error_Code PSSI Error Code
  * @{
  */
#define HAL_PSSI_ERROR_NONE             (0x00UL << 0U) /*!< No error             */
#define HAL_PSSI_ERROR_UNDER_RUN        (0x01UL << 2U) /*!< FIFO Under-run error */
#define HAL_PSSI_ERROR_OVER_RUN         (0x01UL << 3U) /*!< FIFO Over-run error  */
#define HAL_PSSI_ERROR_DMA              (0x01UL << 4U) /*!< DMA error            */
/**
  * @}
  */

/** @defgroup PSSI_Flags PSSI Flags
  * @{
  */
#define HAL_PSSI_FLAG_RTT1B PSSI_SR_RTT1B /*!< 1 Byte Fifo Flag */
#define HAL_PSSI_FLAG_RTT4B PSSI_SR_RTT4B /*!< 4 Bytes Fifo Flag*/
/**
  * @}
  */
/**
  * @}
 */

/* Exported types ---------------------------------------------------------------------------------------------------*/
/** @defgroup PSSI_Exported_Types PSSI Exported Types
  * @{
  */
/** @brief PSSI Data Width enumeration
  */
typedef enum
{
  HAL_PSSI_DATA_WIDTH_8BIT  = 0U,          /*!< 8 Bits  */
  HAL_PSSI_DATA_WIDTH_16BIT = (1UL << 0U), /*!< 16 Bits */
  HAL_PSSI_DATA_WIDTH_32BIT = (1UL << 1U)  /*!< 32 Bits */
} hal_pssi_data_width_t;

/** @brief PSSI Bus Width enumeration
  */
typedef enum
{
  HAL_PSSI_BUS_WIDTH_8LINE  = 0U,         /*!< 8 data lines  */
  HAL_PSSI_BUS_WIDTH_16LINE = PSSI_CR_EDM /*!< 16 data lines */
} hal_pssi_bus_width_t;

/** @brief Control Signal enumeration
  */
typedef enum
{
  HAL_PSSI_CONTROL_SIGNAL_DE_RDY_DISABLE       = (0x0U << PSSI_CR_DERDYCFG_Pos), /*!< Neither DE nor RDY are enabled              */
  HAL_PSSI_CONTROL_SIGNAL_RDY_ENABLE           = (0x1U << PSSI_CR_DERDYCFG_Pos), /*!< Only RDY enabled                            */
  HAL_PSSI_CONTROL_SIGNAL_DE_ENABLE            = (0x2U << PSSI_CR_DERDYCFG_Pos), /*!< Only DE enabled                             */
  HAL_PSSI_CONTROL_SIGNAL_DE_RDY_ALT_ENABLE    = (0x3U << PSSI_CR_DERDYCFG_Pos), /*!< Both RDY and DE alternate functions enabled */
  HAL_PSSI_CONTROL_SIGNAL_MAP_RDY_BIDIR_ENABLE = (0x4U << PSSI_CR_DERDYCFG_Pos), /*!< Bi-directional on RDY pin                   */
  HAL_PSSI_CONTROL_SIGNAL_RDY_MAP_ENABLE       = (0x5U << PSSI_CR_DERDYCFG_Pos), /*!< Only RDY enabled, mapped to DE pin          */
  HAL_PSSI_CONTROL_SIGNAL_DE_MAP_ENABLE        = (0x6U << PSSI_CR_DERDYCFG_Pos), /*!< Only DE enabled, mapped to RDY pin          */
  HAL_PSSI_CONTROL_SIGNAL_MAP_DE_BIDIR_ENABLE  = (0x7U << PSSI_CR_DERDYCFG_Pos)  /*!< Bi-directional on DE pin                    */
} hal_pssi_control_signal_t;

/** @brief Data Enable Polarity enumeration
  */
typedef enum
{
  HAL_PSSI_DATA_ENABLE_POLARITY_LOW  = 0x0U,         /*!< Active Low  */
  HAL_PSSI_DATA_ENABLE_POLARITY_HIGH = PSSI_CR_DEPOL /*!< Active High */
} hal_pssi_data_enable_polarity_t;

/** @brief Ready Polarity enumeration
  */
typedef enum
{
  HAL_PSSI_READY_POLARITY_LOW  = 0x0U,          /*!< Active Low  */
  HAL_PSSI_READY_POLARITY_HIGH = PSSI_CR_RDYPOL /*!< Active High */
} hal_pssi_ready_polarity_t;

/** @brief Clock Polarity enumeration
  */
typedef enum
{
  HAL_PSSI_CLOCK_POLARITY_RX_FALLING_TX_RISING_EDGE = 0x0U,         /*!< Falling edge active for RX or Rising edge active for TX */
  HAL_PSSI_CLOCK_POLARITY_RX_RISING_TX_FALLING_EDGE = PSSI_CR_CKPOL /*!< Rising edge active for RX or Falling edge active for TX */
} hal_pssi_clock_polarity_t;


/**
  * @brief PSSI Global Configuration Structure definition
  */
typedef struct
{
  hal_pssi_bus_width_t             bus_width_line;       /*!< Configures the parallel bus width 8 lines or 16 lines */
  hal_pssi_control_signal_t        control_signal;       /*!< Configures the Control Signal                         */
  hal_pssi_data_enable_polarity_t  data_enable_polarity; /*!< Configures the PSSI Data Enable polarity              */
  hal_pssi_ready_polarity_t        ready_polarity;       /*!< Configures the PSSI Ready polarity                    */
  hal_pssi_data_width_t            data_width_bit;       /*!< Configures the data width 8 bits, 16 bits or 32 bits  */
  hal_pssi_clock_polarity_t        clock_polarity;       /*!< Configures the PSSI Input Clock polarity              */
} hal_pssi_config_t;

/**
  * @brief  HAL PSSI State enumeration definition
  */
typedef enum
{
  HAL_PSSI_STATE_RESET = 0U,          /*!< PSSI not yet initialized or disabled */
  HAL_PSSI_STATE_INIT  = (1UL << 31), /*!< Peripheral initialized               */
  HAL_PSSI_STATE_IDLE  = (1UL << 30), /*!< Peripheral ready for use             */
  HAL_PSSI_STATE_TX    = (1UL << 29), /*!< Transmit process is ongoing          */
  HAL_PSSI_STATE_RX    = (1UL << 28), /*!< Receive process is ongoing           */
  HAL_PSSI_STATE_ABORT = (1UL << 27)  /*!< PSSI process is aborted              */
} hal_pssi_state_t;

/**
  * @brief HAL PSSI instance
  */
typedef enum
{
  HAL_PSSI = (uint32_t)PSSI, /*!< PSSI Peripheral instance */
} hal_pssi_t;

typedef struct hal_pssi_handle_s hal_pssi_handle_t; /*!< PSSI handle structure type */

#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL PSSI Callback pointer definition
  */
typedef void (*hal_pssi_cb_t)(hal_pssi_handle_t *hpssi);  /*!< Pointer to a PSSI common callback function */

#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

/**
  * @brief  PSSI handle Structure definition
  */
struct hal_pssi_handle_s
{
  hal_pssi_t                instance;                 /*!< HAL PSSI instance                                       */
  uint8_t                   *p_buf_ptr;               /*!< PSSI Data buffer                                        */
  uint32_t                  xfer_count;               /*!< PSSI transfer count                                     */
  uint32_t                  xfer_size_byte;           /*!< PSSI transfer size                                      */
  hal_pssi_data_width_t     data_width_bit;           /*!< Configures the data width 8 bits, 16 bits or 32 bits    */
  volatile hal_pssi_state_t global_state;             /*!< PSSI transfer state                                     */
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1)
  volatile uint32_t         last_error_codes;         /*!< Errors limited to the last process
                                                       This parameter can be a combination of @ref PSSI_Error_Code */
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1)
  hal_dma_handle_t          *hdma_tx;                 /*!< PSSI Tx DMA Handle parameters                           */
  hal_dma_handle_t          *hdma_rx;                 /*!< PSSI Rx DMA Handle parameters                           */
#endif /*USE_HAL_PSSI_DMA*/

#if defined(USE_HAL_PSSI_USER_DATA) && (USE_HAL_PSSI_USER_DATA == 1)
  const void                *p_user_data;             /*!< User Data Pointer                                       */
#endif /* USE_HAL_PSSI_USER_DATA */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  hal_os_semaphore_t        semaphore;                /*!< PSSI OS semaphore                                       */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1U)
  hal_pssi_cb_t             p_tx_cplt_cb;             /*!< PSSI Tx completed callback                              */
  hal_pssi_cb_t             p_rx_cplt_cb;             /*!< PSSI Rx completed callback                              */
  hal_pssi_cb_t             p_error_cb;               /*!< PSSI Error callback                                     */
  hal_pssi_cb_t             p_abort_cplt_cb;          /*!< PSSI Abort completed callback                           */
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup PSSI_Exported_Functions PSSI Exported Functions
  * @{
  */

/** @defgroup PSSI_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_PSSI_Init(hal_pssi_handle_t *hpssi, hal_pssi_t instance);
void HAL_PSSI_DeInit(hal_pssi_handle_t *hpssi);
/**
  * @}
  */

/** @defgroup PSSI_Exported_Functions_Group2 Configuration functions
  * @{
  */
/* Global configuration */
hal_status_t HAL_PSSI_SetConfig(hal_pssi_handle_t *hpssi, const hal_pssi_config_t *p_config);
void HAL_PSSI_GetConfig(const hal_pssi_handle_t *hpssi, hal_pssi_config_t *p_config);

/* Control signal */
hal_status_t HAL_PSSI_SetControlSignal(hal_pssi_handle_t *hpssi, hal_pssi_control_signal_t control_signal);
hal_pssi_control_signal_t HAL_PSSI_GetControlSignal(const hal_pssi_handle_t *hpssi);

/* Data enable polarity */
hal_status_t HAL_PSSI_SetDataEnablePolarity(hal_pssi_handle_t *hpssi,
                                            hal_pssi_data_enable_polarity_t data_enable_polarity);
hal_pssi_data_enable_polarity_t HAL_PSSI_GetDataEnablePolarity(const hal_pssi_handle_t *hpssi);

/* Ready polarity */
hal_status_t HAL_PSSI_SetReadyPolarity(hal_pssi_handle_t *hpssi, hal_pssi_ready_polarity_t ready_polarity);
hal_pssi_ready_polarity_t HAL_PSSI_GetReadyPolarity(const hal_pssi_handle_t *hpssi);

/* Clock polarity */
hal_status_t HAL_PSSI_SetClockPolarity(hal_pssi_handle_t *hpssi, hal_pssi_clock_polarity_t clock_polarity);
hal_pssi_clock_polarity_t HAL_PSSI_GetClockPolarity(const hal_pssi_handle_t *hpssi);

/* Callbacks Register functions */
#if defined(USE_HAL_PSSI_REGISTER_CALLBACKS) && (USE_HAL_PSSI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_PSSI_RegisterTxCpltCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback);
hal_status_t HAL_PSSI_RegisterRxCpltCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback);
hal_status_t HAL_PSSI_RegisterErrorCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback);
hal_status_t HAL_PSSI_RegisterAbortCpltCallback(hal_pssi_handle_t *hpssi, hal_pssi_cb_t p_callback);
#endif /* USE_HAL_PSSI_REGISTER_CALLBACKS */

/* DMA link functions */
#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1)
hal_status_t HAL_PSSI_SetTxDMA(hal_pssi_handle_t *hpssi, hal_dma_handle_t *hdma);
hal_status_t HAL_PSSI_SetRxDMA(hal_pssi_handle_t *hpssi, hal_dma_handle_t *hdma);
#endif /* USE_HAL_PSSI_DMA */
/**
  * @}
  */


/** @defgroup PSSI_Exported_Functions_Group3 Input and Output operation functions
  * @{
  */

/* Blocking mode: Polling */
hal_status_t HAL_PSSI_Transmit(hal_pssi_handle_t *hpssi, const void *p_data, uint32_t size_byte, uint32_t timeout_ms);
hal_status_t HAL_PSSI_Receive(hal_pssi_handle_t *hpssi, void *p_data, uint32_t size_byte, uint32_t timeout_ms);

#if defined(USE_HAL_PSSI_DMA) && (USE_HAL_PSSI_DMA == 1)
/* Non-Blocking mode: DMA */
hal_status_t HAL_PSSI_Transmit_DMA(hal_pssi_handle_t *hpssi, const void *p_data, uint32_t size_byte);
hal_status_t HAL_PSSI_Receive_DMA(hal_pssi_handle_t *hpssi, void *p_data, uint32_t size_byte);
hal_status_t HAL_PSSI_Abort_IT(hal_pssi_handle_t *hpssi);
hal_status_t HAL_PSSI_Abort(hal_pssi_handle_t *hpssi);
#endif /*USE_HAL_PSSI_DMA */
/**
  * @}
  */

/** @defgroup PSSI_Exported_Functions_Group4 IRQ Handler and Weak Callbacks Functions
  * @{
  */

void HAL_PSSI_IRQHandler(hal_pssi_handle_t *hpssi);
void HAL_PSSI_TxCpltCallback(hal_pssi_handle_t *hpssi);
void HAL_PSSI_RxCpltCallback(hal_pssi_handle_t *hpssi);
void HAL_PSSI_ErrorCallback(hal_pssi_handle_t *hpssi);
void HAL_PSSI_AbortCpltCallback(hal_pssi_handle_t *hpssi);
/**
  * @}
  */

/** @defgroup PSSI_Exported_Functions_Group5 Peripheral State and Error functions
  * @{
  */
hal_pssi_state_t HAL_PSSI_GetState(const hal_pssi_handle_t *hpssi);
#if defined(USE_HAL_PSSI_GET_LAST_ERRORS) && (USE_HAL_PSSI_GET_LAST_ERRORS == 1)
uint32_t HAL_PSSI_GetLastErrorCodes(const hal_pssi_handle_t *hpssi);
#endif /* USE_HAL_PSSI_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup PSSI_Exported_Functions_Group6 Peripheral Acquire/Release/Free the bus
  * @{
  */
hal_status_t HAL_PSSI_AcquireBus(hal_pssi_handle_t *hpssi, uint32_t timeout_ms);
hal_status_t HAL_PSSI_ReleaseBus(hal_pssi_handle_t *hpssi);
/**
  * @}
  */
#endif /* USE_HAL_MUTEX */


#if defined(USE_HAL_PSSI_USER_DATA) && (USE_HAL_PSSI_USER_DATA == 1)
/** @defgroup PSSI_Exported_Functions_Group7 Set/Get user data
  * @{
  */
void HAL_PSSI_SetUserData(hal_pssi_handle_t *hpssi, const void *p_user_data);
const void *HAL_PSSI_GetUserData(const hal_pssi_handle_t *hpssi);
/**
  * @}
  */
#endif /* USE_HAL_PSSI_USER_DATA */

/**
  * @}
  */

/** @defgroup PSSI_Exported_Functions_Group8 Low Level configuration functions
  * @{
  */

/* PSSI Status, Interrupt & Flag management */

/**
  * @brief  Get the PSSI data buffer overrun/underrun raw interrupt status.
  * @param  hpssi PSSI handle structure
  * @return The state of flag: 1 or 0.
  */
__STATIC_INLINE uint8_t HAL_PSSI_IsActiveFlag_OVR_UDR_RIS(const hal_pssi_handle_t *hpssi)
{
  return (uint8_t)((READ_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->RIS, PSSI_RIS_OVR_RIS) \
                    == PSSI_RIS_OVR_RIS) ? 1U : 0U);
}

/**
  * @brief  Get the PSSI data buffer overrun/underrun masked interrupt status.
  * @param  hpssi PSSI handle structure
  * @return The state of flag: 1 or 0.
  */
__STATIC_INLINE uint8_t HAL_PSSI_IsActiveFlag_OVR_UDR_MIS(const hal_pssi_handle_t *hpssi)
{
  return (uint8_t)((READ_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->MIS, PSSI_MIS_OVR_MIS) \
                    == PSSI_MIS_OVR_MIS) ? 1U : 0U);
}

/**
  * @brief  Get the status of the specified PSSI FIFO transfer.
  * @param  hpssi PSSI handle structure
  * @param  flag PSSI_SR flag can be one of the following values:
  *         @arg HAL_PSSI_FLAG_RTT1B
  *         @arg HAL_PSSI_FLAG_RTT4B
  * @return The state of flag: 1 or 0.
  */
__STATIC_INLINE uint8_t HAL_PSSI_IsActiveFlag_SR(const hal_pssi_handle_t *hpssi, uint32_t flag)
{
  return (uint8_t)((READ_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->SR, flag) == flag) ? 1U : 0U);
}


/**
  * @brief  Clear the PSSI data buffer overrun/underrun interrupt status.
  * @param  hpssi PSSI handle structure
  */
__STATIC_INLINE void HAL_PSSI_ClearFlag_OVR_UDR(hal_pssi_handle_t *hpssi)
{
  SET_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->ICR, PSSI_ICR_OVR_ISC);
}

/**
  * @brief  Enable the PSSI Data buffer overrun/underrun interrupt.
  * @param  hpssi PSSI handle structure
  */
__STATIC_INLINE void HAL_PSSI_EnableIT_OVR_UDR(hal_pssi_handle_t *hpssi)
{
  SET_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->IER, PSSI_IER_OVR_IE);
}

/**
  * @brief  Disable the PSSI Data buffer overrun/underrun interrupt.
  * @param  hpssi PSSI handle structure
  */
__STATIC_INLINE void HAL_PSSI_DisableIT_OVR_UDR(hal_pssi_handle_t *hpssi)
{
  CLEAR_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->IER, PSSI_IER_OVR_IE);
}

/**
  * @brief  Check whether the PSSI Data buffer overrun/underrun interrupt source is enabled or not.
  * @param  hpssi PSSI handle structure
  * @return The state of PSSI_IER_OVR_IE: 1 or 0.
  */
__STATIC_INLINE uint8_t HAL_PSSI_IsEnabledIT_OVR_UDR(const hal_pssi_handle_t *hpssi)
{
  return (uint8_t)((READ_BIT(((PSSI_TypeDef *)(uint32_t)hpssi->instance)->IER, PSSI_IER_OVR_IE) \
                    == (PSSI_IER_OVR_IE)) ? 1UL : 0UL);
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* PSSI */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32U5xx_HAL_PSSI_H */
